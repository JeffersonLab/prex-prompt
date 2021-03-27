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
void CorrectTree_EigenVectorRegression_Default(Int_t run_number=0, std::string stub="" ){
  // Getting Slug Number from RCDB
  Int_t slug_id = QuerySlugNumber(run_number);
  if(slug_id==-1){
    std::cout << " -- Slug Number not Found " << std::endl;
    std::cout << " -- Correction Aborted " << std::endl;
    return;
  }

  // Update hardcoded path to environment variable for BMOD slopes files
  TString ditSlopeFileNamebase = gSystem->Getenv("DITHERING_ROOTFILES_SLOPES");
  TString ditStub = gSystem->Getenv("DITHERING_STUB");
  if (stub == "") {
    stub = (std::string)ditStub;
  }
  TString chose_4aX_1X = "4aX";
  if ( ((TString)stub).Contains("1X") ) {
    chose_4aX_1X = "1X";
  }

  //  Get Slopes From Dit slope Files
  vector<TString> eigen_reg_vDet={"asym_usl",
      "asym_usr",
      "asym_us_avg",
  };

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

  // FIXME more hardcoding here - ignores combiner objects
  vector<TString> evMon={
    "diff_evMon0",
    "diff_evMon1",
    "diff_evMon2",
    "diff_evMon3",
    "diff_evMon4"
  };

  vector<TString> bpmMon={
    "diff_bpm1X",
    "diff_bpm4aY",
    "diff_bpm4eX",
    "diff_bpm4eY",
    "diff_bpm12X"
  };

  TFile *japanOutput;
  const char* FILE_PATH = "$QW_ROOTFILES";    //path to folder that contains rootfiles

  TString filename;
  TString stemlist[5] = {"prexPrompt_pass2_",
    "prexPrompt_pass1_", 
    "prexALL_",
    "prexALLminusR_",
    "prexinj_"};
  for  (int i=0; i<5; i++){
    filename = Form("%s/%s%d.000.root",FILE_PATH,
        stemlist[i].Data(),run_number);
    japanOutput = new TFile(filename);
    if (japanOutput->IsOpen()) {break;}
  }
  if (japanOutput->IsOpen()) {
    std::cerr << "Opened file "<< filename << std::endl;
  } else {
    std::cerr << "No file found for run " << run_number << " in path " 
	      << FILE_PATH << std::endl;
    return NULL;
  }
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
      << "JAPAN RootFile doesn't exist!" << std::endl;
    return;
  }
  TTree *mul_tree = (TTree*)japanOutput->Get("mul");

  if(mul_tree==NULL){
    std::cout << "Error: " 
   << "mul tree doesn't exist!" << std::endl;
    return;
  }

  TString ditSlopeFileName = Form("%s/dit_alldet_slopes%s_slug%d.root",
             ditSlopeFileNamebase.Data(),stub.c_str(),slug_id);
  if( gSystem->AccessPathName(ditSlopeFileName) ) {
    Printf("Trying %s",ditSlopeFileName.Data());
    ditSlopeFileName = Form("%s/dit_alldet_slopes%s.root",
             ditSlopeFileNamebase.Data(),stub.c_str());
  }
  if( gSystem->AccessPathName(ditSlopeFileName) ) {
    Printf("Trying %s",ditSlopeFileName.Data());
    ditSlopeFileName = Form("/chafs2/work1/apar/BMODextractor/dit_alldet_slopes%s_slug%d.root",
  					 stub.c_str(),slug_id);
  }
  Printf("Using %s",ditSlopeFileName.Data());
  TFile* ditherOutput = TFile::Open(ditSlopeFileName);

  if(ditherOutput==NULL){
    std::cout << "Error: " 
      << "dit RootFile doesn't exist!" << std::endl;
    return;
  }

  TTree *slope_tree = (TTree*)ditherOutput->Get("dit");

  if(slope_tree==NULL){
    std::cout << "Error: " 
      << "dit slope tree doesn't exist!" << std::endl;
    return;
  }
  Int_t internal_run_number = 0;
  slope_tree->SetBranchAddress("run",&internal_run_number);
  slope_tree->BuildIndex("run","cyclenum");

  // FIXME eigenvector combo definitions are kept in the Eigenvector analysis processed outputs: hardcoded for now
  TFile* eigenvectorOutput = TFile::Open(Form("%s/rcdb_segment_eigenvectors_sorted_seg_slug_avg.root",ditSlopeFileNamebase.Data())); // FIXME needs to be generalized eventually - stub.c_str()

  if(eigenvectorOutput==NULL){
    std::cout << "Error: " 
      << "dit RootFile doesn't exist!" << std::endl;
    return;
  }

  TTree *mini_tree = (TTree*)eigenvectorOutput->Get("mini");
  TString combo_tree_name = "mini_eigen_reg_5bpms_sorted_seg_avg";
  TTree *combo_tree = (TTree*)eigenvectorOutput->Get(combo_tree_name); // FIXME hardcoded to the segment average eigenvector analysis
  mini_tree->AddFriend(combo_tree);

  if(combo_tree==NULL || mini_tree==NULL){
    std::cout << "Error: " 
      << "dit combo tree doesn't exist!" << std::endl;
    return;
  }

  mini_tree->BuildIndex("run","mini");


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
  TString eigen_reg_maindet_array[3]={"usl","usr","us_avg"};
  //TString maindet_array[8]={"usl","usr","dsl","dsr","atl1","atl2","atr1","atr2"}; // PREX 
  //// FIXME needs to not be hardcoded... or smart somehow
  //TString bpm_array[6]={"4aX","4aY","4eX","4eY","11X12X","11X12X"};
  //TString bpm_array[6]={"1X","4aY","4eX","4eY","12X","12X"}; // Extra 12X to placehold for the PREX version's 11X (may return as a 11X12X = EX combo soon)
  TString bpm_array[5]={"evMon0","evMon1","evMon2","evMon3","evMon4"};
  TString bpm_components_array[5]={"bpm1X","bpm4aY","bpm4eX","bpm4eY","bpm12X"};
  const Int_t ndet = sizeof(maindet_array)/sizeof(*maindet_array);
  const Int_t eigen_reg_ndet = sizeof(eigen_reg_maindet_array)/sizeof(*eigen_reg_maindet_array);
  const Int_t nmon= sizeof(bpm_array)/sizeof(*bpm_array);
  const Int_t ncompmon= sizeof(bpm_components_array)/sizeof(*bpm_components_array);

  //Array for holding slopes. DV (maindets) are the rows, and IV (bpms) are the columns
  double slopes[ndet][nmon]={0};
  double eigslopes[eigen_reg_ndet][nmon]={0};
  double combos[nmon][ncompmon]={0};
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
    // Used to be that I would scan through the slug and find the nearest good run's segment number. Now, just get the run's segment directly
    //Int_t nEnts = slope_tree->Draw(">>elistSeg",Form("run>=%d && flag==1",run_number));//,run_cut); run>= cut allows for non-existant runs to be included
    Int_t nEnts = slope_tree->Draw(">>elistSeg",Form("run==%d",run_number));//,run_cut); run>= cut allows for non-existant runs to be included
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
      TLeaf* runL = slope_tree->GetLeaf("run");
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
    // Use the internal run number just obtained from the tree for safety
    Int_t goodbytes = mini_tree->GetEntry(mini_tree->GetEntryNumberWithIndex(internal_run_number,0)); // combos are done minirunwise - take minirun 0 every time ... bursts won't be relevant until later if at all FIXME
    if (goodbytes == 0) {
      Int_t distance = 0;
      while (goodbytes == 0) {
        Printf("Issue with finding a entry with run number = %d",internal_run_number);
        goodbytes = mini_tree->GetEntry(mini_tree->GetEntryNumberWithIndex(run_number-distance,0)); // Use the run_number passed by the user
        if (goodbytes == 0) {
          goodbytes = mini_tree->GetEntry(mini_tree->GetEntryNumberWithIndex(run_number+distance,0));
        }
        distance++;
      }
      Printf("Found a neigboring run %d, %d runs away",internal_run_number,distance);
    }
    //Printf("good bytes 1 = %d",goodbytes);
    //goodbytes = combo_tree->GetEntry(mini_tree->GetEntryNumberWithIndex(internal_run_number,0));
    //Printf("good bytes 2 = %d",goodbytes);
    //For each bpm
    for(int imon = 0; imon <nmon; imon++){
      // std::cout << maindet_array[idet] << ": ";
      //For each detector
      for(int idet = 0; idet<ndet; idet++){
        varname = Form("%s_%s",maindet_array[idet].Data(),bpm_array[imon].Data());
        //Get the slope
        slopes[idet][imon] += (slope_tree->GetLeaf(varname)->GetValue()*1.0e-3)/nCyc;
        // std::cout << slopes[idet][imon] << "\t";
      }
      for(int jmon = 0; jmon<ncompmon; jmon++){
        //Get the combo
        varname = Form("%s.%s_%s_mean",combo_tree_name.Data(),bpm_array[imon].Data(),bpm_components_array[jmon].Data());
        combos[imon][jmon] += (mini_tree->GetLeaf(varname)->GetValue())/nCyc; // Take the averages of combos, in case the above segment cut gets changed later and it isn't the simplistic segment averaging over combos to generate the underlying bmod analysis - minimize assumptions FIXME
        //varname = Form("%s_%s_mean",bpm_array[imon].Data(),bpm_components_array[jmon].Data());
        //combos[imon][jmon] += (combo_tree->GetLeaf(varname)->GetValue())/nCyc; // Take the averages of combos, in case the above segment cut gets changed later and it isn't the simplistic segment averaging over combos to generate the underlying bmod analysis - minimize assumptions FIXME
        //Printf("combos[%d][%d] += (mini_tree->GetLeaf(%s)->GetValue())/%d = %f",imon,jmon,varname.Data(),nCyc,mini_tree->GetLeaf(varname)->GetValue()/nCyc);
      }
      for(int idet = 0; idet<eigen_reg_ndet; idet++){
        varname = Form("%s.%s_%s_mean",combo_tree_name.Data(),eigen_reg_maindet_array[idet].Data(),bpm_array[imon].Data());
        eigslopes[idet][imon] += (mini_tree->GetLeaf(varname)->GetValue()*1.0e-3)/nCyc;
      }
      // std::cout << "\n";
    }
  }
  std::cout << " --- Get Segment Averaged Slopes -- " << std::endl;
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
  const int nMon = evMon.size();
  const int nBPM = bpmMon.size();
  JCONT DetArray[nDet];
  Double_t MonArray[nMon];
  JCONT BPMArray[nBPM];
  JCONT_SMALL DetArray_dit[nDet];
  JCONT_SMALL DetArray_eig[eigen_reg_ndet];
  Double_t ComboMonArray[nMon*nBPM];

  Double_t fErrorFlag;
  Double_t fCodaEventNumber;

  for(int iDet=0;iDet<nDet;iDet++)
    mul_tree->SetBranchAddress(vDet[iDet],&(DetArray[iDet]));
  for(int iMon=0;iMon<nBPM;iMon++)
    mul_tree->SetBranchAddress(bpmMon[iMon],&(BPMArray[iMon]));
  mul_tree->SetBranchAddress("ErrorFlag",&fErrorFlag);
  mul_tree->SetBranchAddress("CodaEventNumber",&fCodaEventNumber);
  TString outputName ;
  Ssiz_t first_t = filename.Last('_')+1;
  Ssiz_t last_t = filename.Last('.');
  Ssiz_t length_t = last_t -first_t;
  outputName = filename(first_t,length_t);
  outputName.ReplaceAll('.','_');
  outputName = "prexPrompt_dither"+ (TString)stub.c_str() + "_" +outputName;
  outputName +=".root";
  TString output_path="./DitOutputs/";
  std::cout << " -- Writing " << output_path+outputName << std::endl;
  
  TFile *output = TFile::Open(output_path+outputName,"RECREATE");
  TTree *dit_tree = new TTree("dit","BeamMod Correction Tree");
  // A dit corrected asym 
  for(int iDet=0;iDet<nDet;iDet++)
    dit_tree->Branch("dit_"+vDet[iDet],
           &(DetArray_dit[iDet]),
           leaf_list);
  // A eigen value regression corrected asym 
  for(int iDet=0;iDet<eigen_reg_ndet;iDet++)
    dit_tree->Branch("eigen_reg_"+eigen_reg_vDet[iDet],
  		     &(DetArray_eig[iDet]),
  		     leaf_list);
  // A copy of raw asym 
  for(int iDet=0;iDet<nDet;iDet++)
    dit_tree->Branch(vDet[iDet],
  		     &(DetArray[iDet]),
  		     leaf_list);
  // A copy of diff bpm 
  for(int iMon=0;iMon<nBPM;iMon++)
    dit_tree->Branch(bpmMon[iMon],
           &(BPMArray[iMon]),
           leaf_list);
  // A copy of corrected evMon's
  for(int iMon=0;iMon<nMon;iMon++)
    dit_tree->Branch(evMon[iMon],
           &(MonArray[iMon]));
  // Entrywise combo values too (for safety)
  for(int iMon=0;iMon<nMon;iMon++) {
    for(int jMon=0;jMon<nBPM;jMon++) {
      dit_tree->Branch(Form("%s_%s",bpm_array[iMon].Data(),bpm_components_array[jMon].Data()),
          &(ComboMonArray[(nMon*iMon)+jMon]));
    }
  }

  dit_tree->Branch("ErrorFlag",&fErrorFlag,"ErrorFlag/D");
  dit_tree->Branch("CodaEventNumber",&fCodaEventNumber,"CodaEventNumber/D");
  
  Int_t nEntries = mul_tree->GetEntries();
  Printf("Applying dither corrections, neglecting block level");
  for(int ievt=0;ievt<nEntries;ievt++){
    if (ievt%((nEntries/10)+1)==0) Printf("%d%% done correcting run %d",100*ievt/nEntries,run_number);
    mul_tree->GetEntry(ievt);

    for(int iMon=0;iMon<nMon;iMon++){
      MonArray[iMon] = 0.0;
      for(int jMon=0;jMon<nBPM;jMon++){
        MonArray[iMon] += combos[iMon][jMon]*BPMArray[jMon].hw_sum;
        ComboMonArray[(nMon*iMon)+jMon] = combos[iMon][jMon];
      }
    }
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
      for(int iMon=0;iMon<nBPM;iMon++){
        // PREX Used 0.4x 12X and 1x 11X, CREX uses just 12X 
        scaleFactor = 1.0;
        DetArray_dit[iDet].hw_sum -= scaleFactor*slopes[iDet][iMon]*MonArray[iMon];
        /*DetArray_dit[iDet].block0 -= scaleFactor*slopes[iDet][iMon]*MonArray[iMon]; // eigen vector monitors just aren't doing non-hw_sum entries - a double now
          DetArray_dit[iDet].block1 -= scaleFactor*slopes[iDet][iMon]*MonArray[iMon];
          DetArray_dit[iDet].block2 -= scaleFactor*slopes[iDet][iMon]*MonArray[iMon];
          DetArray_dit[iDet].block3 -= scaleFactor*slopes[iDet][iMon]*MonArray[iMon];
          */
      }
    }
    for(int iDet=0;iDet<eigen_reg_ndet;iDet++){
      if (iDet == 2) {
        // FIXME FIXME FIXME Hard coding that eigen reg device 2 == (0 + 1)/2 (i.e. the main det us_avg == avg of first two entries in this. only 3 entries long).
        DetArray_eig[iDet].hw_sum = (DetArray[0].hw_sum + DetArray[1].hw_sum)/2;
        /*DetArray_eig[iDet].block0 = DetArray[iDet].block0;
          DetArray_eig[iDet].block1 = DetArray[iDet].block1;
          DetArray_eig[iDet].block2 = DetArray[iDet].block2;
          DetArray_eig[iDet].block3 = DetArray[iDet].block3;*/
        DetArray_eig[iDet].num_samples = DetArray[0].num_samples + DetArray[1].num_samples;
        DetArray_eig[iDet].Device_Error_Code = (Double_t)((Int_t)DetArray[0].Device_Error_Code | (Int_t)DetArray[1].Device_Error_Code);
      }
      else {
        DetArray_eig[iDet].hw_sum = DetArray[iDet].hw_sum;
        /*DetArray_eig[iDet].block0 = DetArray[iDet].block0;
          DetArray_eig[iDet].block1 = DetArray[iDet].block1;
          DetArray_eig[iDet].block2 = DetArray[iDet].block2;
          DetArray_eig[iDet].block3 = DetArray[iDet].block3;*/
        DetArray_eig[iDet].num_samples = DetArray[iDet].num_samples;
        DetArray_eig[iDet].Device_Error_Code = DetArray[iDet].Device_Error_Code;
      }

      Double_t correction = 0.0;
      Double_t scaleFactor = 1.0;
      for(int iMon=0;iMon<nBPM;iMon++){
        scaleFactor = 1.0;
        DetArray_eig[iDet].hw_sum -= scaleFactor*eigslopes[iDet][iMon]*MonArray[iMon];
        /*DetArray_eig[iDet].block0 -= scaleFactor*slopes[iDet][iMon]*MonArray[iMon]; // eigen vector monitors just aren't doing non-hw_sum entries - a double now
          DetArray_eig[iDet].block1 -= scaleFactor*slopes[iDet][iMon]*MonArray[iMon];
          DetArray_eig[iDet].block2 -= scaleFactor*slopes[iDet][iMon]*MonArray[iMon];
          DetArray_eig[iDet].block3 -= scaleFactor*slopes[iDet][iMon]*MonArray[iMon];
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

