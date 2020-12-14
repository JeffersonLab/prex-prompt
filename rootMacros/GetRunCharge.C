void GetRunCharge(Int_t run_nubmer){
  TString filename = Form("$QW_ROOTFILES/prexPrompt_pass1_%d.000.root",run_nubmer);
  TFile *rootfile = TFile::Open(filename);
  TTree* mul_tree = (TTree*)rootfile->Get("mul");
  TCut goodPatternCut = "(ErrorFlag&0xda7e6bff)==0";
  Int_t nGoodPatterns = mul_tree->GetEntries(goodPatternCut);
  Int_t nTotal = mul_tree->GetEntries();
  mul_tree->Draw("yield_bcm_an_us",goodPatternCut,"goff");
  TH1D* h_buff = (TH1D*)gDirectory->FindObject("htemp");
  Double_t current_mean = h_buff->GetMean();
  Double_t integral_raw = current_mean*nGoodPatterns;
  Double_t pattern_freq = 1.0/30.0; // Hz
  Double_t uA = 1e-6; // Amp
  Double_t charge_in_C = integral_raw*pattern_freq*uA;

  cout << "--nGoodPatterns: " << nGoodPatterns << endl;
  cout << "--Good Minutes: " << nGoodPatterns*pattern_freq/60 << endl;
  cout << "--Total Minutes: " << nTotal*pattern_freq/60 << endl;
  cout << "--Beam Current Mean(uA): " << current_mean << endl;
  cout << "--Integrated Charge(C): " << charge_in_C << endl;
  
}
