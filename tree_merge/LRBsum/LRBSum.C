vector<Int_t> LoadRunListBySlug(Int_t slug);
void LRBSum(Int_t slug_id);
void LoadStatFromFile(TFile* input, TTree *output);
TString GetNameBase(TString input){
  input.ReplaceAll("asym_","");
  input.ReplaceAll("diff_","");
  return input;
};
void LRBSum();
typedef struct{Double_t mean,error,rms,nsample;} STAT;

void LRBSum(){
  for(int i=0;i<=94;i++){
    LRBSum(i);
  }
}
void LRBSum(Int_t slug_id){
  vector<Int_t> fRunlist = LoadRunListBySlug(slug_id);
  TString path="/lustre19/expphy/volatile/halla/parity/treeMergeOutput/LRBsum/";
  TString filename = Form("LRBsum_slug%d.root",slug_id);
  TFile *output = TFile::Open(path+filename,"RECREATE");
  TTree *mini_tree = new TTree("mini"," lrb Burst Summary");
  Int_t fRun; 
  mini_tree->Branch("run",&fRun);
  typedef struct { Double_t ppm,ppb,um,nm;}UNIT;
  UNIT parity_unit;
  parity_unit.ppm = 1e-6;
  parity_unit.ppb = 1e-9;
  parity_unit.um = 1e-3;
  parity_unit.nm = 1e-6;
  mini_tree->Branch("unit",&parity_unit,"ppm/D:ppb:um:nm");

  Int_t nRun = fRunlist.size();
  for(int irun=0;irun<nRun;irun++){
    fRun = fRunlist[irun];
    TString lrb_filename = Form("./LRBoutput/burst_blueR%d.000alldet.slope.root",fRun);
    TFile *lrb_file = TFile::Open(lrb_filename);
    if(lrb_file==NULL)
      continue;
    cout << fRun << endl;
    LoadStatFromFile(lrb_file,mini_tree);
    
  }
  output->cd();
  cout << " Writing output " << path+filename << endl;
  mini_tree->Write();
  output->Close();
}

void LoadStatFromFile(TFile* lrb_file, TTree *mini_tree){
  if((TMatrixD*)lrb_file->Get("MyStat")==NULL)
    return;
  TH1D* hist_iv = (TH1D*)lrb_file->Get("IVname");
  TH1D* hist_dv = (TH1D*)lrb_file->Get("DVname");
  vector< TString > IVlist;
  vector< TString > DVlist;
  TAxis *ivAxis = hist_iv->GetXaxis();
  TAxis *dvAxis = hist_dv->GetXaxis();
  Int_t nIV = ivAxis->GetLast();
  Int_t nDV = dvAxis->GetLast();
  for(int i=0;i<nIV;i++){
    const char* char_buff = ivAxis->GetBinLabel(i+1);
    IVlist.push_back(TString(char_buff));
  }

  for(int i=0;i<nDV;i++){
    const char* char_buff = dvAxis->GetBinLabel(i+1);
    DVlist.push_back(TString(char_buff));
  }
  ////////////////////////////////////

  Int_t burst_counter=0;
  if(mini_tree->GetBranch("mini")==NULL){
    mini_tree->Branch("mini",&burst_counter);
  }else{
    mini_tree->SetBranchAddress("mini",&burst_counter);
  }
  vector<STAT> fDVstat_raw(nDV);
  vector<STAT> fDVstat_reg(nDV);
  vector<STAT> fIVstat(nIV);
  vector<Double_t> fSlope(nDV*nIV);
  vector<Double_t> fSlope_err(nDV*nIV);

  for(int idv=0;idv<nDV;idv++){
    if(mini_tree->GetBranch(DVlist[idv])==NULL){
      mini_tree->Branch(DVlist[idv],&fDVstat_raw[idv],
			"mean/D:err:rms:nsamp");
      mini_tree->Branch("reg_"+DVlist[idv],&fDVstat_reg[idv],
			"mean/D:err:rms:nsamp");

    }else{
      mini_tree->SetBranchAddress(DVlist[idv],&fDVstat_raw[idv]);
      mini_tree->SetBranchAddress("reg_"+DVlist[idv],&fDVstat_reg[idv]);
    }
  }
  for(int iiv=0;iiv<nIV;iiv++){
    if(mini_tree->GetBranch(IVlist[iiv])==NULL)
      mini_tree->Branch(IVlist[iiv],&fIVstat[iiv],
			"mean/D:err:rms:nsamp");
    else
      mini_tree->SetBranchAddress(IVlist[iiv],&fIVstat[iiv]);
  }
  for(int idv=0;idv<nDV;idv++){
    TString dv_base = DVlist[idv];
    dv_base = GetNameBase(dv_base);
    for(int iiv=0;iiv<nIV;iiv++){
      TString iv_base = IVlist[iiv];
      iv_base = GetNameBase(iv_base);
      if(mini_tree->GetBranch(dv_base+"_"+iv_base)==NULL){
	mini_tree->Branch(dv_base+"_"+iv_base, &fSlope[idv*nIV+iiv]);
	mini_tree->Branch(dv_base+"_"+iv_base+"_err", &fSlope_err[idv*nIV+iiv]);
      }
      else{
	mini_tree->SetBranchAddress(dv_base+"_"+iv_base, &fSlope[idv*nIV+iiv]);
	mini_tree->SetBranchAddress(dv_base+"_"+iv_base+"_err", &fSlope_err[idv*nIV+iiv]);
      }
    }
  }
  ////////////////////////////////////

  Int_t cycle=1;
  TString cycle_tag = Form(";%d",cycle);
  while( ((TMatrixD*)lrb_file->Get("MyStat"+cycle_tag)!=NULL)){

    TMatrixT<double> MyStat = *((TMatrixT<double>*)lrb_file->Get("MyStat"+cycle_tag));
    Double_t sqrtN =   sqrt(MyStat(0,0));
    TMatrixT<double> slope = *((TMatrixT<double>*)lrb_file->Get("slopes"+cycle_tag));
    TMatrixT<double> slope_err = *((TMatrixT<double>*)lrb_file->Get("sigSlopes"+cycle_tag));
    TVectorT<double> DV_mean = *((TVectorT<double>*)lrb_file->Get("DV_mean"+cycle_tag));
    TVectorT<double> DV_sigma = *((TVectorT<double>*)lrb_file->Get("DV_sigma"+cycle_tag));
    TVectorT<double> DV_normVar = *((TVectorT<double>*)lrb_file->Get("DV_normVariance"+cycle_tag));

    TVectorT<double> DV_mean_prime = *((TVectorT<double>*)lrb_file->Get("DV_mean_prime"+cycle_tag));
    TVectorT<double> DV_sigma_prime = *((TVectorT<double>*)lrb_file->Get("DV_sigma_prime"+cycle_tag));
    TVectorT<double> DV_normVar_prime = *((TVectorT<double>*)lrb_file->Get("DV_normVariance_prime"+cycle_tag));

    TVectorT<double> IV_mean = *((TVectorT<double>*)lrb_file->Get("IV_mean"+cycle_tag));
    TVectorT<double> IV_sigma = *((TVectorT<double>*)lrb_file->Get("IV_sigma"+cycle_tag));
    TVectorT<double> IV_normVar = *((TVectorT<double>*)lrb_file->Get("IV_normVariance"+cycle_tag));

    for(int idv=0;idv<nDV;idv++)
      for(int iiv=0;iiv<nIV;iiv++){
	fSlope[idv*nIV+iiv] = slope[iiv][idv];
	fSlope_err[idv*nIV+iiv] = slope_err[iiv][idv];
      }
    for(int idv=0;idv<nDV;idv++){
      fDVstat_raw[idv].mean = DV_mean[idv];
      fDVstat_raw[idv].error = DV_sigma[idv]/sqrtN;
      fDVstat_raw[idv].nsample = MyStat(0,0);
      fDVstat_raw[idv].rms = sqrt(DV_normVar[idv]);

      fDVstat_reg[idv].mean = DV_mean_prime[idv];
      fDVstat_reg[idv].error = DV_sigma_prime[idv]/sqrtN;
      fDVstat_reg[idv].nsample = MyStat(0,0);
      fDVstat_reg[idv].rms = sqrt(DV_normVar_prime[idv]);
    }
    for(int iiv=0;iiv<nIV;iiv++){
      fIVstat[iiv].mean = IV_mean[iiv];
      fIVstat[iiv].error = IV_sigma[iiv]/sqrtN;
      fIVstat[iiv].nsample = MyStat(0,0);
      fIVstat[iiv].rms = sqrt(IV_normVar[iiv]);
    }

    burst_counter++;
    mini_tree->Fill();
    cycle++;
    cycle_tag = Form(";%d",cycle);
  }

}

vector<Int_t> LoadRunListBySlug(Int_t slug_id){
  TString full_path = "/u/group/halla/parity/software/japan_offline/prompt/prex-prompt/prex-runlist/";
  TString filename= Form("/simple_list/slug%d.list",slug_id);
  filename = full_path+filename;
  vector<Int_t> fRet;
  FILE *file = fopen(filename.Data(),"r");
  while(!feof(file)){
    Int_t run_number = 0;
    fscanf(file,"%d\n",&run_number);
    if(run_number!=0)
      fRet.push_back(run_number);
  }
  return fRet;
}
