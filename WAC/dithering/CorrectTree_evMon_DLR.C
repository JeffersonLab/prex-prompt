/*
Updated by Cameron, based on Tao and Catherine's DitAlias 
June 2021 - removed averaged regression slope correction, added dithering slope save/outputting, added dit us_avg and us_dd slopes and correction

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

using namespace std;
void CorrectTree_evMon_DLR(Int_t run_number, TString stub, TString inputFilePath, TString ditSlopeFileName, TString ditTreeName, TString regLagFileName, TString regTreeName, TString lagTreeName, TString comboFileName, TString comboTreeName){
  Int_t do_dit = 1;
  // Getting Slug Number from RCDB

  //  Get Slopes From Dit slope Files
  vector<TString> reg_lagr_vDet={"asym_usl",
      "asym_usr",
			"asym_atl1",
			"asym_atl2",
			"asym_atr1",
			"asym_atr2",
      "asym_us_avg",
      "asym_us_dd",
  };

  vector<TString> tree_dit_vDet={"asym_usl",
      "asym_usr",
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
      "mulc.asym_us_avg",
      "mulc.asym_us_dd",
  };
  vector<TString> dit_vDet={"asym_usl",
			"asym_usr",
			"asym_atl1",
			"asym_atl2",
			//"asym_dsl", //PREX 
			//"asym_dsr", //PREX 
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
      "asym_us_avg",
      "asym_us_dd",
  };

  // FIXME more hardcoding here - ignores combiner objects
  vector<TString> evMon_new;
  vector<TString> bpmMon;

  if ( comboTreeName.Contains("allbpms") ){
    do_dit = 0;
    bpmMon = {
      "diff_bpm4aX","diff_bpm4aY","diff_bpm4eX","diff_bpm4eY",
      "diff_bpm16X","diff_bpm16Y","diff_bpm12X","diff_bpm12Y","diff_bpm11X","diff_bpm11Y",
      "diff_bpm1X","diff_bpm1Y"};
    evMon_new ={
      "diff_evMon0_new",
      "diff_evMon1_new",
      "diff_evMon2_new",
      "diff_evMon3_new",
      "diff_evMon4_new",
      "diff_evMon5_new",
      "diff_evMon6_new",
      "diff_evMon7_new",
      "diff_evMon8_new",
      "diff_evMon9_new",
      "diff_evMon10_new",
      "diff_evMon11_new",
    };
  }
  else {
    bpmMon = {
      "diff_bpm1X",
      "diff_bpm4aY",
      "diff_bpm4eX",
      "diff_bpm4eY",
      "diff_bpm12X"
    };
    evMon_new ={
      "diff_evMon0_new",
      "diff_evMon1_new",
      "diff_evMon2_new",
      "diff_evMon3_new",
      "diff_evMon4_new"
    };
  }

  TFile *japanOutput;
  const char* FILE_PATH = inputFilePath.Data();    //path to folder that contains rootfiles

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

  if(japanOutput==NULL){
    std::cout << "Error: " 
      << "JAPAN RootFile doesn't exist!" << std::endl;
    return;
  }
  TTree *mul_tree = (TTree*)japanOutput->Get("mul");
  TTree *mulc_tree = (TTree*)japanOutput->Get("mulc");

  if(mul_tree==NULL || mulc_tree==NULL){
    std::cout << "Error: " 
   << "mul or mulc tree doesn't exist!" << std::endl;
    return;
  }
  mul_tree->AddFriend(mulc_tree); // Add mulc as friend to automatically allow for us_avg and us_dd grabbing. 
  // WARNING Be careful about the evMon definitions that are in mulc being OLD!!

  TFile* ditherInput;
  TTree *dit_slope_tree;
  if (do_dit) {
    ditherInput = TFile::Open(ditSlopeFileName);

    if(ditherInput==NULL){
      std::cout << "Error: " 
        << "dit rootfile " << ditSlopeFileName << " doesn't exist!" << std::endl;
      return;
    }
    dit_slope_tree = (TTree*)ditherInput->Get(ditTreeName);

    if(dit_slope_tree==NULL){
      std::cout << "Error: " 
        << "dit slope tree " << ditTreeName << " doesn't exist!" << std::endl;
      return;
    }
    dit_slope_tree->BuildIndex("run","mini");
  }

  TFile* evMonRegLagSlopesInput = TFile::Open(regLagFileName);
  TFile* eigenvectorComboInput = TFile::Open(comboFileName);

  if(eigenvectorComboInput==NULL){
    std::cout << "Error: " 
      << "evMon combo RootFile doesn't exist!" << std::endl;
    return;
  }

  if(evMonRegLagSlopesInput==NULL){
    std::cout << "Error: " 
      << "reg/lagr RootFile doesn't exist!" << std::endl;
    return;
  }

  TTree *mini_tree = (TTree*)evMonRegLagSlopesInput->Get("mini");
  TString combo_tree_name = comboTreeName;
  TString reg_slope_tree_name = regTreeName;
  TString lagr_slope_tree_name = lagTreeName;
  TTree *combo_tree = (TTree*)eigenvectorComboInput->Get(combo_tree_name); // FIXME hardcoded to the segment average eigenvector analysis
  TTree *reg_slope_tree = (TTree*)evMonRegLagSlopesInput->Get(reg_slope_tree_name); // FIXME hardcoded to the segment average eigenvector analysis
  TTree *lagr_slope_tree = (TTree*)evMonRegLagSlopesInput->Get(lagr_slope_tree_name); // FIXME hardcoded to the segment average eigenvector analysis
  mini_tree->AddFriend(combo_tree);
  mini_tree->AddFriend(reg_slope_tree);
  mini_tree->AddFriend(lagr_slope_tree); // Be careful to always specify which tree name in the setBranchAddress etc. commands

  if(combo_tree==NULL || reg_slope_tree==NULL || lagr_slope_tree==NULL || mini_tree==NULL){
    std::cout << "Error: " 
      << "dit combo, reg, lagr, or mini tree doesn't exist!" << std::endl;
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
  //// FIXME FIXME FIXME FIXME FIXME FIXME FIXME FIXME 
  TString dit_maindet_array[16]={"usl","usr","atl1","atl2","atr1","atr2","sam1","sam2","sam3","sam4","sam5","sam6","sam7","sam8","us_avg","us_dd"}; // CREX
  TString reg_lagr_maindet_array[8]={"usl","usr","atl1","atl2","atr1","atr2","us_avg","us_dd"};
  //TString maindet_array[8]={"usl","usr","dsl","dsr","atl1","atl2","atr1","atr2"}; // PREX 
  //// FIXME needs to not be hardcoded... or smart somehow
  //TString bpm_array[6]={"4aX","4aY","4eX","4eY","11X12X","11X12X"};
  //TString bpm_array[6]={"1X","4aY","4eX","4eY","12X","12X"}; // Extra 12X to placehold for the PREX version's 11X (may return as a 11X12X = EX combo soon)
  std::vector <TString> monitor_array;
  std::vector <TString> monitor_array_new;
  std::vector <TString> bpm_components_array;
  if ( comboTreeName.Contains("allbpms") ){
    // 12 BPM case
    monitor_array        = {"evMon0","evMon1","evMon2","evMon3","evMon4","evMon5","evMon6","evMon7","evMon8","evMon9","evMon10","evMon11"};
    monitor_array_new    = {"evMon0_new","evMon1_new","evMon2_new","evMon3_new","evMon4_new","evMon5_new","evMon6_new","evMon7_new","evMon8_new","evMon9_new","evMon10_new","evMon11_new"};
    bpm_components_array = {
    "bpm4aX","bpm4aY","bpm4eX","bpm4eY",
    "bpm16X","bpm16Y","bpm12X","bpm12Y","bpm11X","bpm11Y",
    "bpm1X","bpm1Y"};
  }
  else {
    // 5 BPM case
    monitor_array        = {"evMon0","evMon1","evMon2","evMon3","evMon4"};
    monitor_array_new    = {"evMon0_new","evMon1_new","evMon2_new","evMon3_new","evMon4_new"};
    bpm_components_array = {"bpm1X","bpm4aY","bpm4eX","bpm4eY","bpm12X"};
  }
  const Int_t dit_nDet = sizeof(dit_maindet_array)/sizeof(*dit_maindet_array);
  const Int_t eigen_reg_lagr_nDet = sizeof(reg_lagr_maindet_array)/sizeof(*reg_lagr_maindet_array);
  const Int_t nMon = monitor_array.size();
  const Int_t nBPM = bpm_components_array.size();

  //Array for holding slopes. DV (maindets) are the rows, and IV (bpms) are the columns
  double dit_slopes[dit_nDet][55]={0};   // FIXME replaced "nMon" anf "nBPM" with 25 as an arbitrarily large placeholder array length
  double reg_slopes[eigen_reg_lagr_nDet][55]={0};
  double lagr_slopes[eigen_reg_lagr_nDet][55]={0};
  double combos[55][55]={0};
  // for(int idet=0;idet<dit_nDet;idet++)
  //   for(int imon=0;imon<nMon;imon++)
  //     dit_slopes[idet][imon]=0.0;

  //Get the dit_slopes from the tree
  // In order 4aX, 4aY, 4eX, 4eY, 12X
  // slope unit: fraction / mm
  // ** which is  1e-3(ppm/um)
  typedef struct {
    Double_t hw_sum;
  } slope_struct ;
  std::vector<std::vector<slope_struct>> reg_slope_matrix;
  std::vector<std::vector<slope_struct>> lagr_slope_matrix;
  std::vector<std::vector<Double_t>> dit_slope_matrix;
  std::vector<Double_t> tmp_slopes;
  std::vector<slope_struct> tmp_slopes_b;
  std::vector<slope_struct> tmp_slopes_c;
  Double_t rcdb_arm_flag = 0.0;

  for(int imon = 0; imon<nMon; imon++){
    for(int iBPM = 0; iBPM<nBPM; iBPM++){
      combo_tree->SetBranchAddress(Form("%s_%s_mean",monitor_array[imon].Data(),bpm_components_array[iBPM].Data()),&combos[imon][iBPM]);
    }
  }
  for(int idet = 0; idet<dit_nDet; idet++){
    tmp_slopes.clear();
    for(int imon = 0; imon <nMon; imon++){
      Double_t tmp_slope;
      tmp_slopes.push_back(tmp_slope);
    }
    dit_slope_matrix.push_back(tmp_slopes);
  }
  if (do_dit) {
    for(int idet = 0; idet<dit_nDet; idet++){
      for(int imon = 0; imon <nMon; imon++){
        TString slope_varname = "";
        slope_varname = Form("%s_%s_mean",dit_maindet_array[idet].Data(),monitor_array[imon].Data());
        dit_slope_tree->SetBranchAddress(slope_varname,&dit_slope_matrix.at(idet).at(imon));
      }
    }
  }
  for(int idet = 0; idet<dit_nDet; idet++){
    tmp_slopes_b.clear();
    tmp_slopes_c.clear();
    for(int imon = 0; imon <nMon; imon++){
      slope_struct tmp_slope_b;
      slope_struct tmp_slope_c;
      tmp_slopes_b.push_back(tmp_slope_b);
      tmp_slopes_c.push_back(tmp_slope_c);
    }
    reg_slope_matrix.push_back(tmp_slopes_b);
    lagr_slope_matrix.push_back(tmp_slopes_c);
  }
  for(int idet = 0; idet<eigen_reg_lagr_nDet; idet++){
    for(int imon = 0; imon <nMon; imon++){
      TString slope_varname = "";
      slope_varname = Form("%s.%s_%s",reg_slope_tree_name.Data(),reg_lagr_maindet_array[idet].Data(),monitor_array_new[imon].Data());
      mini_tree->SetBranchAddress(slope_varname,&reg_slope_matrix.at(idet).at(imon));
      slope_varname = Form("%s.%s_%s",lagr_slope_tree_name.Data(),reg_lagr_maindet_array[idet].Data(),monitor_array_new[imon].Data());
      mini_tree->SetBranchAddress(slope_varname,&lagr_slope_matrix.at(idet).at(imon));
    }
  }
  mini_tree->SetBranchAddress("rcdb_arm_flag",&rcdb_arm_flag);
  
  //================== Done with slope extraction 

  // Doing Correction
  typedef struct {Double_t hw_sum,
      block0,block1,block2,block3,
      num_samples,
      Device_Error_Code;} JCONT;  // JAPAN TREE CONTAINER
  typedef struct {Double_t hw_sum,
      num_samples,
      Device_Error_Code;} JCONT_SMALL;  // SMALL TREE CONTAINER
  TString leaf_list="hw_sum/D:block0:block1:block2:block3:num_samples:Device_Error_Code";
  //TString leaf_list="hw_sum/D:num_samples:Device_Error_Code";
  //const int dit_nDet = dit_vDet.size();
  //const int nMon = evMon_new.size();
  //const int nBPM = bpmMon.size();
  JCONT DetArray[dit_nDet];
  JCONT MonArray[nMon];
  JCONT BPMArray[nBPM];
  JCONT DetArray_dit[dit_nDet];
  JCONT DetArray_reg[eigen_reg_lagr_nDet];
  JCONT DetArray_lagr[eigen_reg_lagr_nDet];
  Double_t ComboMonArray[nMon*nBPM];

  Double_t fErrorFlag;
  Double_t fCodaEventNumber;
  Short_t minirun_number;

  //if (do_dit) {
    for(int iDet=0;iDet<dit_nDet;iDet++) {
      Printf("Finding %s in mul/mulc trees",tree_dit_vDet[iDet].Data());
      mul_tree->SetBranchAddress(tree_dit_vDet[iDet],&(DetArray[iDet]));
    }
  //}
  for(int iMon=0;iMon<nBPM;iMon++) {
    mul_tree->SetBranchAddress(bpmMon[iMon],&(BPMArray[iMon]));
  }
  mul_tree->SetBranchAddress("ErrorFlag",&fErrorFlag);
  mul_tree->SetBranchAddress("CodaEventNumber",&fCodaEventNumber);
  mul_tree->SetBranchAddress("BurstCounter",&minirun_number);
  TString outputName ;
  Ssiz_t first_t = filename.Last('_')+1;
  Ssiz_t last_t = filename.Last('.');
  Ssiz_t length_t = last_t -first_t;
  outputName = filename(first_t,length_t);
  outputName.ReplaceAll('.','_');
  outputName = "prexPrompt_drl_"+ stub + "_" +outputName;
  outputName +=".root";
  TString output_path="./DitOutputs/";
  std::cout << " -- Writing " << output_path+outputName << std::endl;
  
  TFile *output = TFile::Open(output_path+outputName,"RECREATE");
  TTree *out_drl_tree = new TTree("drl","BeamMod Correction Tree");
  // Dither slopes (averaged)
  if (do_dit) {
    for(int iDet=0;iDet<dit_nDet;iDet++) {
      for(int iMon=0;iMon<nMon;iMon++) {
        out_drl_tree->Branch("eigen_dit_"+dit_maindet_array[iDet]+"_"+monitor_array_new[iMon]+"_slope",
            &(dit_slopes[iDet][iMon]));
      }
    }
  }
  // Reg slopes (direct)
  for(int iDet=0;iDet<eigen_reg_lagr_nDet;iDet++) {
    for(int iMon=0;iMon<nMon;iMon++) {
      out_drl_tree->Branch("eigen_reg_"+reg_lagr_maindet_array[iDet]+"_"+monitor_array_new[iMon]+"_slope",
          &(reg_slopes[iDet][iMon]));
    }
  }
  // Lagr slopes (direct)
  for(int iDet=0;iDet<eigen_reg_lagr_nDet;iDet++) {
    for(int iMon=0;iMon<nMon;iMon++) {
      out_drl_tree->Branch("eigen_lagr_"+reg_lagr_maindet_array[iDet]+"_"+monitor_array_new[iMon]+"_slope",
          &(lagr_slopes[iDet][iMon]));
    }
  }
  // Entrywise combo values too (for safety)
  for(int iMon=0;iMon<nMon;iMon++) {
    for(int jBPM=0;jBPM<nBPM;jBPM++) {
      out_drl_tree->Branch(Form("%s_%s",monitor_array_new[iMon].Data(),bpm_components_array[jBPM].Data()),
          &(ComboMonArray[(nMon*iMon)+jBPM]));
    }
  }
  // A dit corrected asym 
  if (do_dit) {
    for(int iDet=0;iDet<dit_nDet;iDet++)
      out_drl_tree->Branch("eigen_dit_"+dit_vDet[iDet],
          &(DetArray_dit[iDet]),
          leaf_list);
  }
  // A eigen value regression corrected asym 
  for(int iDet=0;iDet<eigen_reg_lagr_nDet;iDet++)
    out_drl_tree->Branch("eigen_reg_"+reg_lagr_vDet[iDet],
          &(DetArray_reg[iDet]),
          leaf_list);
  // A eigen value lagrange corrected asym 
  for(int iDet=0;iDet<eigen_reg_lagr_nDet;iDet++)
    out_drl_tree->Branch("eigen_lagr_"+reg_lagr_vDet[iDet],
          &(DetArray_lagr[iDet]),
          leaf_list);
  // A copy of raw asym 
  for(int iDet=0;iDet<dit_nDet;iDet++)
    out_drl_tree->Branch(dit_vDet[iDet],
           &(DetArray[iDet]),
           leaf_list);
  // A copy of diff bpm 
  for(int iBPM=0;iBPM<nBPM;iBPM++) {
    out_drl_tree->Branch(bpmMon[iBPM],
           &(BPMArray[iBPM]),
           leaf_list);
  }
  // A copy of corrected evMon's
  for(int iMon=0;iMon<nMon;iMon++) {
    out_drl_tree->Branch(evMon_new.at(iMon),
           &(MonArray[iMon]),
           leaf_list);
  }

  out_drl_tree->Branch("ErrorFlag",&fErrorFlag,"ErrorFlag/D");
  out_drl_tree->Branch("CodaEventNumber",&fCodaEventNumber,"CodaEventNumber/D");
  out_drl_tree->Branch("BurstCounter",&minirun_number);
  
  Short_t old_minirun_number = -1;
  Int_t nEntries = mul_tree->GetEntries();
  Printf("Applying dither corrections, neglecting block level");
  for(int ievt=0;ievt<nEntries;ievt++){
    if (ievt%((nEntries/10)+1)==0) Printf("%d%% done correcting run %d",100*ievt/nEntries,run_number);
    mul_tree->GetEntry(ievt);
    if (minirun_number != old_minirun_number) {
      // Then we have moved to the next minirun and need to grab the fresh slopes from dit, reg, and lagr trees (dit should stay static per run... but anyway)
      old_minirun_number = minirun_number;
      Printf("Filling slopes and combo definitions with minirun %d info, beginning at multiplet %d",minirun_number,ievt);
      mini_tree->GetEntry(mini_tree->GetEntryNumberWithIndex(run_number,minirun_number));
      if (do_dit) {
        dit_slope_tree->GetEntry(dit_slope_tree->GetEntryNumberWithIndex(run_number,minirun_number));
      }
      reg_slope_tree->GetEntry(reg_slope_tree->GetEntryNumberWithIndex(run_number,minirun_number));
      lagr_slope_tree->GetEntry(lagr_slope_tree->GetEntryNumberWithIndex(run_number,minirun_number));
      combo_tree->GetEntry(combo_tree->GetEntryNumberWithIndex(run_number,minirun_number));

      if (do_dit) {
        for(int iDet=0;iDet<dit_nDet;iDet++) {
          for(int iMon=0;iMon<nMon;iMon++) {
            // Dither slopes (averaged)
            dit_slope_matrix.at(iDet).at(iMon) = dit_slope_matrix.at(iDet).at(iMon)*1e-3;
            dit_slopes[iDet][iMon]=dit_slope_matrix.at(iDet).at(iMon);
          }
        }
      }
      for(int iDet=0;iDet<eigen_reg_lagr_nDet;iDet++) {
        for(int iMon=0;iMon<nMon;iMon++) {
          // Reg slopes (direct)
          reg_slopes[iDet][iMon]=reg_slope_matrix.at(iDet).at(iMon).hw_sum;
          // Lagr slopes (direct)
          lagr_slopes[iDet][iMon]=lagr_slope_matrix.at(iDet).at(iMon).hw_sum;
        }
      }
      // Entrywise combo values too (for safety)
      for(int iMon=0;iMon<nMon;iMon++) {
        for(int jBPM=0;jBPM<nBPM;jBPM++) {
          ComboMonArray[(nMon*iMon)+jBPM] = combos[iMon][jBPM];
        }
      }
    }
    Double_t scaleFactor = 1.0;

    // Calculate the corrections per event
    for(int iMon=0;iMon<nMon;iMon++){
      MonArray[iMon].hw_sum = 0.0;
      MonArray[iMon].block0 = 0.0;
      MonArray[iMon].block1 = 0.0;
      MonArray[iMon].block2 = 0.0;
      MonArray[iMon].block3 = 0.0;
      MonArray[iMon].num_samples = BPMArray[0].num_samples;
      MonArray[iMon].Device_Error_Code = BPMArray[0].Device_Error_Code;
      for(int jBPM=0;jBPM<nBPM;jBPM++){
        MonArray[iMon].hw_sum += combos[iMon][jBPM]*BPMArray[jBPM].hw_sum;
        MonArray[iMon].block0 += combos[iMon][jBPM]*BPMArray[jBPM].block0;
        MonArray[iMon].block1 += combos[iMon][jBPM]*BPMArray[jBPM].block1;
        MonArray[iMon].block2 += combos[iMon][jBPM]*BPMArray[jBPM].block2;
        MonArray[iMon].block3 += combos[iMon][jBPM]*BPMArray[jBPM].block3;
      }
    }
    if (do_dit) {
      for(int iDet=0;iDet<dit_nDet;iDet++){
        DetArray_dit[iDet].hw_sum = DetArray[iDet].hw_sum;
        DetArray_dit[iDet].block0 = DetArray[iDet].block0;
        DetArray_dit[iDet].block1 = DetArray[iDet].block1;
        DetArray_dit[iDet].block2 = DetArray[iDet].block2;
        DetArray_dit[iDet].block3 = DetArray[iDet].block3;
        DetArray_dit[iDet].num_samples = DetArray[iDet].num_samples;
        DetArray_dit[iDet].Device_Error_Code = DetArray[iDet].Device_Error_Code;

        for(int iMon=0;iMon<nMon;iMon++){
          // PREX Used 0.4x 12X and 1x 11X, CREX uses just 12X 
          scaleFactor = 1.0;
          DetArray_dit[iDet].hw_sum -= scaleFactor*dit_slopes[iDet][iMon]*MonArray[iMon].hw_sum;
          DetArray_dit[iDet].block0 -= scaleFactor*dit_slopes[iDet][iMon]*MonArray[iMon].block0;
          DetArray_dit[iDet].block1 -= scaleFactor*dit_slopes[iDet][iMon]*MonArray[iMon].block1;
          DetArray_dit[iDet].block2 -= scaleFactor*dit_slopes[iDet][iMon]*MonArray[iMon].block2;
          DetArray_dit[iDet].block3 -= scaleFactor*dit_slopes[iDet][iMon]*MonArray[iMon].block3;
        }
      }
    }

    for(int iDet=0;iDet<eigen_reg_lagr_nDet;iDet++){
      DetArray_reg[iDet].hw_sum = DetArray[iDet].hw_sum;
      DetArray_reg[iDet].block0 = DetArray[iDet].block0;
      DetArray_reg[iDet].block1 = DetArray[iDet].block1;
      DetArray_reg[iDet].block2 = DetArray[iDet].block2;
      DetArray_reg[iDet].block3 = DetArray[iDet].block3;
      DetArray_reg[iDet].num_samples = DetArray[iDet].num_samples;
      DetArray_reg[iDet].Device_Error_Code = DetArray[iDet].Device_Error_Code;

      DetArray_lagr[iDet].hw_sum = DetArray[iDet].hw_sum;
      DetArray_lagr[iDet].block0 = DetArray[iDet].block0;
      DetArray_lagr[iDet].block1 = DetArray[iDet].block1;
      DetArray_lagr[iDet].block2 = DetArray[iDet].block2;
      DetArray_lagr[iDet].block3 = DetArray[iDet].block3;
      DetArray_lagr[iDet].num_samples = DetArray[iDet].num_samples;
      DetArray_lagr[iDet].Device_Error_Code = DetArray[iDet].Device_Error_Code;
    }

    for(int iDet=0;iDet<eigen_reg_lagr_nDet;iDet++){
      for(int iMon=0;iMon<nMon;iMon++){
        scaleFactor = 1.0;
        DetArray_reg[iDet].hw_sum -= scaleFactor*reg_slopes[iDet][iMon]*MonArray[iMon].hw_sum;
        DetArray_reg[iDet].block0 -= scaleFactor*reg_slopes[iDet][iMon]*MonArray[iMon].block0; // eigen vector monitors just aren't doing non-hw_sum entries - a double now
        DetArray_reg[iDet].block1 -= scaleFactor*reg_slopes[iDet][iMon]*MonArray[iMon].block1;
        DetArray_reg[iDet].block2 -= scaleFactor*reg_slopes[iDet][iMon]*MonArray[iMon].block2;
        DetArray_reg[iDet].block3 -= scaleFactor*reg_slopes[iDet][iMon]*MonArray[iMon].block3;

        DetArray_lagr[iDet].hw_sum -= scaleFactor*lagr_slopes[iDet][iMon]*MonArray[iMon].hw_sum;
        DetArray_lagr[iDet].block0 -= scaleFactor*lagr_slopes[iDet][iMon]*MonArray[iMon].block0; // eigen vector monitors just aren't doing non-hw_sum entries - a double now
        DetArray_lagr[iDet].block1 -= scaleFactor*lagr_slopes[iDet][iMon]*MonArray[iMon].block1;
        DetArray_lagr[iDet].block2 -= scaleFactor*lagr_slopes[iDet][iMon]*MonArray[iMon].block2;
        DetArray_lagr[iDet].block3 -= scaleFactor*lagr_slopes[iDet][iMon]*MonArray[iMon].block3;
      }
    }
    out_drl_tree->Fill();
  }
  
  japanOutput->Close();
  if (do_dit) {
    ditherInput->Close();
  }
  output->cd();
  std::cout << " -- Writing Dithering Corrected Tree "<< std::endl;
  out_drl_tree->Write();
  std::cout << " -- Closing " << output_path+outputName << std::endl;
  output->Close();
}

