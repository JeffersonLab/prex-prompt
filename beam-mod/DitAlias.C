void DitAlias_Catherine(TString rootfilenName, TString ditherfileName, Int_t runnum = -1){
//rootfilenName = the japan output file that you want to perform corrections on (pass1 or pass2)
//ditherfileName = the dither root file whose slopes will be used to perform corrections
//runnum = the run number of the slopes you want to use to perform calculations. 
//Default: uses the average slopes of the slug. If runnum is not in the dither root file (ie -1), then all of the slopes from that slug (except the outlier "blacklisted" runs) will be averaged and then used for correction

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
  //Create a cut for the blacklisted "bad" runs
  FILE *blacklist = fopen("./black.list","r");
  TCut run_cut;
  while(!feof(blacklist)){
    Int_t buff;
    fscanf(blacklist,"%d/n",&buff);
    run_cut += Form("run!=%d",buff);
  }
  cout << "-- Blacklist  cut " << endl;
  run_cut.Print();

  //Build variable names
  //  //dit tree variable names go like "dv_iv", for example: "usr_4eX"
  TString maindet_array[4]={"usl","usr","dsl","dsr"};
  TString bpm_array[5]={"4aX","4aY","4eX","4eY","12X"};
  Int_t ndet = sizeof(maindet_array)/sizeof(*maindet_array);
  Int_t nmon= sizeof(bpm_array)/sizeof(*bpm_array);


  //Array for holding slopes. DV (maindets) are the rows, and IV (bpms) are the columns
  double slopes[ndet][nmon];
  for(int idet=0;idet<ndet;idet++)
    for(int imon=0;imon<nmon;imon++)
      slopes[idet][imon]=0.0;


  //Find the index in the tree that has run = runnumber
  //If the runnumber is in the tree, only use slopes from that one run
  //If it is not in the tree, use the average slope of the entire run

  Int_t irun = 0;
  Bool_t kFound = kFALSE;
  for(int r = 0; r<dit_tree->GetEntries(); r++){
    dit_tree->GetEntry(r);
    irun = r;
    if(dit_tree->GetLeaf("run")->GetValue()==runnum){
      kFound=kTRUE;
      run_cut = Form("run==%d",runnum);
      break;
    }
  }
  if(!kFound){
    cout << "Run number is not in this file. \n";
  }
  //Get the slopes from the tree
  //In order 4aX, 4aY, 4eX, 4eY, 12X
  //slope unit: fraction / mm
  //** which is  1e-3(ppm/um)

  Int_t nEntries =dit_tree->Draw(">>elist1",run_cut);
  TEventList *elist = (TEventList*)gDirectory->Get("elist1");
  TString varname;
  //For each run number
  for(int ievt = 0; ievt<nEntries; ievt++){
    Int_t index = elist->GetEntry(ievt);
    dit_tree->GetEntry(index);
    cout << dit_tree->GetLeaf("run")->GetValue() << endl;
    //For each detector
    for(int idet = 0; idet<ndet; idet++){
      cout << maindet_array[idet] << ": ";
      //For each bpm
      for(int imon = 0; imon <nmon; imon++){
        varname = Form("%s_%s",maindet_array[idet].Data(),bpm_array[imon].Data());
        //Get the running_average slope
        slopes[idet][imon] += (dit_tree->GetLeaf(varname)->GetValue()*1.0e-3)/nEntries;
        cout << slopes[idet][imon] << "\t";
      }
      cout << "\n";
    }
  }
  //Plot the maindets before and after correction
  TCanvas *c_uncorr = new TCanvas("c_uncorr", "c_uncorr");
  TCanvas *c_corr = new TCanvas("c_corr", "c_corr");
  c_uncorr->Divide(2,2);
  c_corr->Divide(2,2);
  //Perform corrections
  for(int idet=0; idet<ndet;idet++){
    TString this_alias = "asym_"+maindet_array[idet];
    for(int imon=0;imon<nmon;imon++){
      this_alias += Form("-%f*diff_bpm%s",slopes[idet][imon],bpm_array[imon].Data());
    }
    cout << this_alias << endl;
    mul_tree->SetAlias("dit_"+maindet_array[idet],
        this_alias);

    c_uncorr->cd(idet+1);
    mul_tree->Draw(Form("asym_%s*%f",maindet_array[idet].Data(), 1.0e6), "ErrorFlag==0");
    c_corr->cd(idet+1);
    mul_tree->Draw(Form("dit_%s*%f",maindet_array[idet].Data(), 1.0e6), "ErrorFlag==0");
  }

  c_uncorr -> SaveAs("plots/Run"+runnum+"_UncorrectedRMS.pdf");
  c_corr -> SaveAs("plots/Run"+runnum+"_CorrectedRMS_run"+runnum+"Slopes.pdf");
  c_corr -> SaveAs("plots/Run"+runnum+"_CorrectedRMS_slug"+_+"AvgSlopes.pdf");

}
