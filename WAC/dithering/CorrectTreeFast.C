/*
Updated by Cameron, based on Tao and Catherine's DitAlias 

-- Example  from shell terminal:
$  root -b 'CorrectTree(3433)'

--with specific segment file 
$  root CorrectTree(3433,1)

Output Directory: 
                 ./DitOutputs/prexPrompt_dither_3454_000.root
 */

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TChain.h>
#include <TLeaf.h>
#include <TH1.h>
#include <TFile.h>
#include <vector>
#include <TString.h>
#include <algorithm>
#include <iostream>
#include <TMatrix.h>
#include <TMatrixD.h>
#include <TChain.h>
#include <TEventList.h>
#include <TCanvas.h>
#include <TTreeReader.h>
#include <cmath>
#include "QuerySlugNumber.C"

using namespace std;
void CorrectTreeFast(Int_t run_number=0, std::string stub="" ){
  // Getting Slug Number from RCDB
  Int_t slug_id = QuerySlugNumber(run_number);
  if(slug_id==-1){
    std::cout << " -- Slug Number not Found " << std::endl;
    std::cout << " -- Correction Aborted " << std::endl;
    return;
  }

  //  Get Slopes From Dit slope Files
  vector<TString> vDet={"asym_usl",
			"asym_usr",
			//"asym_dsl", //PREX 
			//"asym_dsr", //PREX 
			"asym_atl1",
			"asym_atl2",
			"asym_atr1",
			"asym_atr2",
      "asym_sam1",
      "asym_sam2",
      "asym_sam3",
      "asym_sam4",
      "asym_sam5",
      "asym_sam6",
      "asym_sam7",
      "asym_sam8",
  };

  vector<TString> vMon={"diff_bpm4aX",
			"diff_bpm4aY",
			"diff_bpm4eX",
			"diff_bpm4eY",
			"diff_bpm11X",
			"diff_bpm12X"};
  TString rootfile_name = Form("~/PREX/prompt/japanOutput/prexPrompt_pass1_%d.000.root",
  			       run_number);
  TFile *japanOutput = TFile::Open(rootfile_name);
  /*TTree *evt_tree = (TTree*)japanOutput->Get("evt");
  Int_t n_cyc_entries = evt->Draw("bmwcycnum","bmwcycnum>0","goff");
  TH1 *bmwcycnum_hist = (TH1*)gROOT->FindObject("htemp");
  std::vector<Double_t> * cycnumbers = {};
  for (Int_t nBin = 0; nBin < bmwcycnum_hist->GetNBins() ; nBin++){
    if (bmwcycnum_hist->GetBinContent(nBin)>0){
      cycnumbers->push_back(bmwcycnum_hist->GetBinCenter(nBin));
    }
  }
  Int_t starting_cycnum = 0;
  if (cycnumbers.size()>0){
    starting_cycnum = cycnumbers.at(0);
  }
  else { 
    Printf("No good cycles this run, ERROR (for now)");
    return; 
  }*/
  // Want to loop over the cycle numbers and do correction of a run using these slopes
  // This entails collecting the cyclenum based slope parameters and then applying them to any event that comes before/after that cycle number
  //    Start with the first cycle number of the run and change to the following cycle number once the cyclenumber in Japan file increases to the next in the vector of cycle numbers
  //    For now, if no available slopes just error out and leave, later try to get the one before and one after that cycle number and use the average (if available in slope root file)


  if(japanOutput==NULL){
    std::cout << "Error: " 
      << "JAPAN RootFile doesn't exsit!" << std::endl;
    return;
  }
  TTree *mul_tree = (TTree*)japanOutput->Get("mul");

  if(mul_tree==NULL){
    std::cout << "Error: " 
   << "mul tree doesn't exist!" << std::endl;
    return;
  }

  TFile* ditherOutput = TFile::Open(Form("/chafs2/work1/apar/BMODextractor/dit_alldet_slopes%s_slug%d.root",
  					 stub.c_str(),slug_id));
  if(ditherOutput==NULL){
    std::cout << "Error: " 
      << "dit RootFile doesn't exist!" << std::endl;
    return;
  }
  TTree *slope_tree = (TTree*)ditherOutput->Get("dit");

  if(slope_tree==NULL){
    std::cout << "Error: " 
      << "dit slope  tree doesn't exsit!" << std::endl;
    return;
  }

  // Adapting following part from Catherines' DitAlias.C
    //Create a cut for the blacklisted "bad" runs
  /*FILE *blacklist = fopen("./black.list","r");
  TCut run_cut;
  while(!feof(blacklist)){
    Int_t buff;
    fscanf(blacklist,"%d/n",&buff);
    run_cut += Form("run!=%d",buff);
  }*/

  //Build variable names
  //dit tree variable names go like "dv_iv", for example: "usr_4eX"
  TString maindet_array[14]={"usl","usr","atl1","atl2","atr1","atr2","sam1","sam2","sam3","sam4","sam5","sam6","sam7","sam8"}; // CREX
  //TString maindet_array[8]={"usl","usr","dsl","dsr","atl1","atl2","atr1","atr2"}; // PREX 
  TString bpm_array[6]={"4aX","4aY","4eX","4eY","11X12X","11X12X"};
  const Int_t ndet = sizeof(maindet_array)/sizeof(*maindet_array);
  const Int_t nmon= sizeof(bpm_array)/sizeof(*bpm_array);

  //Array for holding slopes. DV (maindets) are the rows, and IV (bpms) are the columns
  double slopes[ndet][nmon]={0};
  // for(int idet=0;idet<ndet;idet++)
  //   for(int imon=0;imon<nmon;imon++)
  //     slopes[idet][imon]=0.0;

  //Get the slopes from the tree
  // In order 4aX, 4aY, 4eX, 4eY, 12X
  // slope unit: fraction / mm
  // ** which is  1e-3(ppm/um)
  
  Int_t nCyc = 0;
  TEventList *elist;// = (TEventList*)gDirectory->Get("elist1");
  TString varname;

  Int_t segment = 1;
  if (slope_tree->GetBranch("segment")) {
    Int_t nEnts = slope_tree->Draw(">>elistSeg",Form("run>=%d && flag==1",run_number));//,run_cut); run>= cut allows for non-existant runs to be included
    TEventList *elistSeg = (TEventList*)gDirectory->Get("elistSeg");
    TLeaf* segmentL = slope_tree->GetLeaf("segment");
    segmentL->GetBranch()->GetEntry(elistSeg->GetEntry(0));
    segment = segmentL->GetValue(); // Got the segment value of the 1st cycle in run run_number
    if (segment == 0) {
      // I can do this kind of time looping test, or I could just add a cut on segment to the above Draw command... I kinda like this loop though
      for (Int_t n = 0 ; n < nEnts ; n++ ) {
        segmentL->GetBranch()->GetEntry(elistSeg->GetEntry(n));
        segment = segmentL->GetValue();
        if (segment != 0) {
          // Grab the first non-zero entry to get the probably accurate segment number
          // This allows us to get corrections for runs with no BMOD cycles in a given slug dithering file
          break;
        }
      }
    }
    if (segment==0) 
    {
      segment=1;
      // Just do the whole slug and use the largest segment number for runs >= the current run number
      Int_t nEnts = slope_tree->Draw(">>elistSeg2","flag==1");//,run_cut); run>= cut allows for non-existant runs to be included
      TEventList *elistSeg2 = (TEventList*)gDirectory->Get("elistSeg2");
      TLeaf* segmentL = slope_tree->GetLeaf("segment");
      TLeaf* runL = slope_tree->GetLeaf("segment");
      segmentL->GetBranch()->GetEntry(elistSeg2->GetEntry(0));
      runL->GetBranch()->GetEntry(elistSeg2->GetEntry(0));
      segment = segmentL->GetValue(); // Got the segment value of the 1st cycle in run run_number
      for (Int_t j = 0; j<nEnts; j++) {
        segmentL->GetBranch()->GetEntry(elistSeg2->GetEntry(j));
        runL->GetBranch()->GetEntry(elistSeg2->GetEntry(j));
        if (runL->GetValue() <= run_number) 
        {
          segment = segmentL->GetValue();
        }
      }
      if (segment == 0) {
        segment = 1;
      }
    }

    Printf("Using segment %d of the slug for slug averaged slope calculation",segment);
    nCyc = slope_tree->Draw(">>elist1",Form("cyclenum>0 && flag==1 && segment==%d",segment));//,run_cut); // Not including run_cut will do slug averaging
    elist = (TEventList*)gDirectory->Get("elist1");
  }
  else {
    nCyc = slope_tree->Draw(">>elist1","cyclenum>0 && flag==1");//,run_cut); // Not including run_cut will do slug averaging
    elist = (TEventList*)gDirectory->Get("elist1");
  }

  //For each run number
  for(int ievt = 0; ievt<nCyc; ievt++){
    Int_t index = elist->GetEntry(ievt);
    slope_tree->GetEntry(index);
    //For each detector
    for(int idet = 0; idet<ndet; idet++){
      // std::cout << maindet_array[idet] << ": ";
      //For each bpm
      for(int imon = 0; imon <nmon; imon++){
        varname = Form("%s_%s",maindet_array[idet].Data(),bpm_array[imon].Data());
        //Get the slope
        slopes[idet][imon] += (slope_tree->GetLeaf(varname)->GetValue()*1.0e-3)/nCyc;
        // std::cout << slopes[idet][imon] << "\t";
      }
      // std::cout << "\n";
    }
  }
  std::cout << " --- Get Slug Averaged Slopes -- " << std::endl;
  for(int idet = 0; idet<ndet; idet++){
    std::cout << maindet_array[idet] << " Correction : ";
    for(int imon = 0; imon <nmon; imon++){
      if(imon!=0 && slopes[idet][imon]>0 )
	std::cout << " + ";
      else
	std::cout << " ";
      std::cout << setprecision(5)
	   << 1000*slopes[idet][imon]  // FIXME
	   << "*" 
	   << bpm_array[imon];
    }
    std::cout << std::endl;
  }
  ditherOutput->Close();
  //================== Done with slope extraction 

  // Doing Correction
  typedef struct {Double_t hw_sum,
      block0,block1,block2,block3,
      num_samples,
      Device_Error_Code;} JCONT;  // JAPAN TREE CONTAINER
  typedef struct {Double_t hw_sum,
      num_samples,
      Device_Error_Code;} JCONT_SMALL;  // SMALL TREE CONTAINER
  //TString leaf_list="hw_sum/D:block0:block1:block2:block3:num_samples:Device_Error_Code";
  TString leaf_list="hw_sum/D:num_samples:Device_Error_Code";
  const int nDet = vDet.size();
  const int nMon = vMon.size();
  JCONT DetArray[nDet];
  JCONT MonArray[nMon];
  JCONT_SMALL DetArray_dit[nDet];

  Double_t fErrorFlag;
  Double_t fCodaEventNumber;

  for(int iDet=0;iDet<nDet;iDet++)
    mul_tree->SetBranchAddress(vDet[iDet],&(DetArray[iDet]));
  for(int iMon=0;iMon<nMon;iMon++)
    mul_tree->SetBranchAddress(vMon[iMon],&(MonArray[iMon]));
  mul_tree->SetBranchAddress("ErrorFlag",&fErrorFlag);
  mul_tree->SetBranchAddress("CodaEventNumber",&fCodaEventNumber);
  TString outputName ;
  Ssiz_t first_t = rootfile_name.Last('_')+1;
  Ssiz_t last_t = rootfile_name.Last('.');
  Ssiz_t length_t = last_t -first_t;
  outputName = rootfile_name(first_t,length_t);
  outputName.ReplaceAll('.','_');
  outputName = "prexPrompt_dither"+ (TString)stub.c_str() + "_" +outputName;
  outputName +=".root";
  TString output_path="./DitOutputs/";
  std::cout << " -- Writing " << output_path+outputName << std::endl;
  
  TFile *output = TFile::Open(output_path+outputName,"RECREATE");
  TTree *dit_tree = new TTree("dit","BeamMod Correction Tree");
  // A corrected asym 
  for(int iDet=0;iDet<nDet;iDet++)
    dit_tree->Branch("dit_"+vDet[iDet],
  		     &(DetArray_dit[iDet]),
  		     leaf_list);
  // A copy of raw asym 
  for(int iDet=0;iDet<nDet;iDet++)
    dit_tree->Branch(vDet[iDet],
  		     &(DetArray[iDet]),
  		     leaf_list);
  // A copy of diff bpm 
  for(int iMon=0;iMon<nMon;iMon++)
    dit_tree->Branch(vMon[iMon],
  		     &(MonArray[iMon]),
  		     leaf_list);

  dit_tree->Branch("ErrorFlag",&fErrorFlag,"ErrorFlag/D");
  dit_tree->Branch("CodaEventNumber",&fCodaEventNumber,"CodaEventNumber/D");
  
  Int_t nEntries = mul_tree->GetEntries();
  Printf("Applying dither corrections, neglecting block level");
  for(int ievt=0;ievt<nEntries;ievt++){
    if (ievt%((nEntries/10)+1)==0) Printf("%d%% done correcting run %d",100*ievt/nEntries,run_number);
    mul_tree->GetEntry(ievt);

    for(int iDet=0;iDet<nDet;iDet++){
      DetArray_dit[iDet].hw_sum = DetArray[iDet].hw_sum;
      /*DetArray_dit[iDet].block0 = DetArray[iDet].block0;
      DetArray_dit[iDet].block1 = DetArray[iDet].block1;
      DetArray_dit[iDet].block2 = DetArray[iDet].block2;
      DetArray_dit[iDet].block3 = DetArray[iDet].block3;*/
      DetArray_dit[iDet].num_samples = DetArray[iDet].num_samples;
      DetArray_dit[iDet].Device_Error_Code = DetArray[iDet].Device_Error_Code;

      Double_t correction = 0.0;
      Double_t scaleFactor = 1.0;
      for(int iMon=0;iMon<nMon;iMon++){
        // PREX Used 0.4x 12X and 1x 11X, CREX uses just 12X 
        if (iMon < nMon-2) {
          scaleFactor = 1.0;
        }
        else if (iMon < nMon-1) {
          if (run_number < 5000) {
            scaleFactor = 1.0; // PREX 
          }
          else {
            scaleFactor = 0.0;   // CREX
          }
        }
        else {
          if (run_number < 5000) {
            scaleFactor = 0.4; // PREX
          }
          else {
            scaleFactor = 1.0;   // CREX 
          }
        }
        DetArray_dit[iDet].hw_sum -= scaleFactor*slopes[iDet][iMon]*MonArray[iMon].hw_sum;
        /*DetArray_dit[iDet].block0 -= scaleFactor*slopes[iDet][iMon]*MonArray[iMon].block0;
          DetArray_dit[iDet].block1 -= scaleFactor*slopes[iDet][iMon]*MonArray[iMon].block1;
          DetArray_dit[iDet].block2 -= scaleFactor*slopes[iDet][iMon]*MonArray[iMon].block2;
          DetArray_dit[iDet].block3 -= scaleFactor*slopes[iDet][iMon]*MonArray[iMon].block3;
          */
      }
    }
    dit_tree->Fill();
  }
  
  japanOutput->Close();
  output->cd();
  std::cout << " -- Writing Dithering Corrected Tree "<< std::endl;
  dit_tree->Write();
  std::cout << " -- Closing " << output_path+outputName << std::endl;
  output->Close();
}

