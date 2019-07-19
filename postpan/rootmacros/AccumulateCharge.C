void AccumulateCharge(TString filename){

  TFile *rootfile = TFile::Open(filename);

  Ssiz_t first_t = filename.Last('_')+1;
  Ssiz_t Dot_t = filename.First('.')+1;
  
  TString run = filename(filename,4);
  TString seg = filename(Dot_t,3);
  
  TTree* mul_tree = (TTree*)rootfile->Get("mul");
  
  TString bcm_name = "yield_bcm_an_ds3";
  
  Int_t nGoodPatterns = mul_tree->GetEntries("ErrorFlag==0 && yield_bcm_an_ds3.Device_Error_Code==0");
  
  mul_tree->Draw("yield_bcm_an_ds3","ErrorFlag==0","goff");
  TH1D* h_buff = (TH1D*)gDirectory->FindObject("htemp");
  Double_t current_mean = h_buff->GetMean();
  
  Double_t integral_raw = current_mean*nGoodPatterns;

  Double_t coulomb_charge = 1.6e-19; // Coulomb
  Double_t integration_time = 8.33-e3; //sec // FIXME
  Double_t uA = 1e-6; // Amp

  Double_t charge_in_C = integral_raw*integration_time*uA/coulomb_charge;
  
  cout << run << "\t" << seg << "\t" << charge_in_C << endl;
  
}
