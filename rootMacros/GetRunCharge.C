void GetRunCharge(TString filename){
  
  FILE *capacitor_txt = fopen("capacitor.log","a");
  TFile *rootfile = TFile::Open(filename);
  
  Ssiz_t first_t = filename.Last('_')+1;
  Ssiz_t last_t = filename.Last('.');

  TString run_dot_seg = filename(first_t,last_t-first_t);
  
  TString run = run_dot_seg(0,4);
  TString seg = run_dot_seg(run_dot_seg.First('.')+1,3);
  
  TTree* mul_tree = (TTree*)rootfile->Get("mul");
  
  TString bcm_name = "yield_bcm_an_ds3";
  
  TCut goodPatternCut = "ErrorFlag==0 && yield_bcm_an_ds3.Device_Error_Code==0";
  Int_t nGoodPatterns = mul_tree->GetEntries(goodPatternCut);
  
  mul_tree->Draw("yield_bcm_an_ds3",goodPatternCut,"goff");
  TH1D* h_buff = (TH1D*)gDirectory->FindObject("htemp");
  Double_t current_mean = h_buff->GetMean();
  
  Double_t integral_raw = current_mean*nGoodPatterns;

  Double_t integration_time = 4*8.2e-3; //sec // FIXME
  Double_t uA = 1e-6; // Amp

  Double_t charge_in_C = integral_raw*integration_time*uA;

  cout << "--nGoodPatterns: " << nGoodPatterns << endl;
  cout << "--Beam Current Mean(uA): " << current_mean << endl;
  cout << "--Integrated Charge(C): " << charge_in_C << endl;
  
  fprintf(capacitor_txt,
	  "%s\t%s\t%f\n",
	  run.Data(),seg.Data(),charge_in_C);

  fclose(capacitor_txt);
}
