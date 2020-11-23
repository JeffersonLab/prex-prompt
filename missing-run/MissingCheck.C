void MissingCheck(){
  vector<TString> japan_pass1={"japan_pass1",
			       "/lustre/expphy/volatile/halla/parity/japanOutput/",
			       "prexPrompt_pass1_%d.000.root"};

  vector<TString> postpan_std={"postpan-std",
			       "/lustre/expphy/volatile/halla/parity/postpan_respin/",
			       "prexPrompt_%d_000_regress_postpan.root"};

  vector<TString> postpan_bpm_combo={"postpan-combo",
				     "/lustre/expphy/volatile/halla/parity/postpan_respin/",
				     "prexPrompt_%d_000_regress_comboBPM.root"};

  vector<TString> postpan_ovl={"postpan-overloaded",
			       "/lustre/expphy/volatile/halla/parity/postpan_respin/",
			       "prexPrompt_%d_000_regress_overload.root"};

  vector<TString> dit_coeff={"dit-coeff",
			     "/lustre/expphy/volatile/halla/parity/LagrangeOutput/dit_coeffs/",
			     "prexPrompt_ditcoeffs_%d.root"};
  
  vector< vector<TString>  > fModArray={japan_pass1,
  					postpan_std,
  					postpan_bpm_combo,
  					postpan_ovl,
  					dit_coeff};
  vector<Int_t> fStartRun={0,0,3390,0,0};

  FILE* runlist = fopen("./prex-runlist/simple_list/all.list","r");
  vector<Int_t> fRunArray;
  while(!feof(runlist)){
    int run_number =0;
    fscanf(runlist,"%d/n",&run_number);
    if(run_number!=0)
      fRunArray.push_back(run_number);
  }
  fclose(runlist);
  TDatime fDatTime;
  TString output_filename = Form("missing_%d.list",fDatTime.GetDate());
  ofstream missing_log;
  missing_log.open(output_filename);
  Int_t nRun =fRunArray.size();
  Int_t nMod = fModArray.size();
  vector< vector<Int_t> > fMissList(nMod);
  missing_log << " Total Number of run " << nRun << endl;
  for(int imod=0;imod<nMod;imod++){
    vector<TString> fMod = fModArray[imod];
    cout << " Analysis Module " << fMod[0] << endl;
    TString file_path=fMod[1];
    TString file_format=fMod[2];
    for(int i=0;i<nRun;i++){
      if(fRunArray[i]<fStartRun[imod])
	continue;
      printf("\r checking run number: %d  ",fRunArray[i]);
      fflush(stdout);
      TString filename=Form(file_format,fRunArray[i]);
      TFile *file_ptr = TFile::Open(file_path+filename);
      if(file_ptr==NULL)
	fMissList[imod].push_back(fRunArray[i]);
      else
	file_ptr->Close();
    }
    cout << endl;

    missing_log<<  " -------- " << endl;
    missing_log<<  " -- " << fMod[0] << " missing " 
	       << fMissList[imod].size() <<  " runs" << endl;
    missing_log << fMod[1] << endl;
    missing_log << fMod[2] << endl;
    auto iter_ml = fMissList[imod].begin();
    while(iter_ml!=fMissList[imod].end()){
      missing_log<< "\t" << *iter_ml << endl;
      iter_ml++;
    }
    missing_log<<  " -------- " << endl;
  } // end of loop over mod

  missing_log.close();
}

