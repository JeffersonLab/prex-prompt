void DitAlias_Catherine(TString rootfilenName, TString ditherfileName, Int_t runnum){

  //Try to open the trees 
  TFile* japanOutput = TFile::Open(rootfilenName);
  TFile* ditherOutput = TFile::Open(ditherfileName);

  TTree *mul_tree = (TTree*)japanOutput->Get("mul");
  if(mul_tree==NULL){
    cout << "Error: " 
      << "mul tree doesn't exsit!" << endl;
    return;
  }
  TTree *dit_tree = (TTree*)ditherOutput->Get("dit");
  if(dit_tree==NULL){
    cout << "Error: " 
      << "dit tree doesn't exsit!" << endl;
    return;
  }


  //Dependent variables
  TString maindet_array[]={"asym_usl","asym_usr",
    "asym_dsl","asym_dsr"};

  //Independent variables
  TString bpm_array[5]={"diff_bpm4aX","diff_bpm4aY",
    "diff_bpm4eX","diff_bpm4eY",
    "diff_bpm12X"};

  const Int_t ndet = sizeof(maindet_array)/sizeof(*maindet_array);
  const Int_t nmon = sizeof(bpm_array)/sizeof(*bpm_array);


  //Build variable names
  //div tree variable names go like "usr_4eX"
  TString name_start[4]={"usl","usr","dsl","dsr"};
  TString name_end[5]={"4aX","4aY","4eX","4eY","12X"};
  double slopes [4][5];

  //Find the index in the tree that has run = runnumber
  Int_t irun = 0;
  for(int r = 0; r<dit_tree->GetEntries(); r++){
    dit_tree->GetEntry(r);
    irun = r;
    if(dit_tree->GetLeaf("run")->GetValue()==runnum)
      break;
  }
  //Get the slopes of that run number from the tree
  // In order 4aX, 4aY, 4eX, 4eY, 12X
  // slope unit: fraction / mm
  // ** which is  1e-3(ppm/um)
  TString varname;
  for(int idet = 0; idet<ndet; idet++){
    cout << name_start[idet] << ": ";
    for(int imon = 0; imon < nmon; imon++){
      varname = Form("%s_%s",name_start[idet].Data(),name_end[imon].Data());
      slopes[idet][imon] = dit_tree->GetLeaf(varname)->GetValue()*1.0e-3;
      cout << slopes[idet][imon] << "\t";
    }
    cout << "\n";
  }

  //Plot the results
  TCanvas *c_uncorr = new TCanvas("c_uncorr", "c_uncorr");
  TCanvas *c_corr = new TCanvas("c_corr", "c_corr");
  c_uncorr->Divide(2,2);
  c_corr->Divide(2,2);
  for(int idet=0; idet<ndet;idet++){
    TString this_alias = maindet_array[idet];
    for(int imon=0;imon<nmon;imon++){
      this_alias += Form("-%f*%s",slopes[idet][imon],("asym_"+bpm_array[imon].Data());
    }
    cout << this_alias << endl;
    mul_tree->SetAlias("dit_"+maindet_array[idet],
        this_alias);

    c_uncorr->cd(idet+1);
    mul_tree->Draw(Form("%s*%f",maindet_array[idet].Data(), 1.0e6), "ErrorFlag==0");
    c_corr->cd(idet+1);
    mul_tree->Draw(Form("dit_%s*%f",maindet_array[idet].Data(), 1.0e6), "ErrorFlag==0");
  }

}
