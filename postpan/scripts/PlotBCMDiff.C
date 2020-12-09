void PlotBCMDiff(int run_num=1391){

  gStyle->SetOptFit(1);
  gStyle->SetStatW(0.2);
  gStyle->SetStatH(0.2);
  gStyle->SetStatX(0.9);
  gStyle->SetStatY(0.9);


  TFile* rootfile = TFile::Open(Form("../../japanOutput/prexALL_%d.root",run_num));
  TTree *tree = (TTree*)rootfile ->Get("mul");
  TString user_cut = "(pattern_number>13.5e3  && pattern_number< 14.5e3) || (pattern_number>700 && pattern_number<1300) || ( pattern_number>22.5e3 && pattern_number<23e3)";
  TCanvas *c1 = new TCanvas("c1","c1",800,800);

  c1->cd();
  tree->Draw("diff_bcm_an_ds>>hdiff(100,-2e-3,2e-3)",user_cut);
  TH1D *h_buff = (TH1D*)gDirectory->FindObject("hdiff");
  h_buff->GetXaxis()->SetTitle("Difference (uA)");
  h_buff->GetXaxis()->SetMaxDigits(2);
  h_buff->SetTitle("Downstream Analog BCM, Beam off Difference (uA)");

}
