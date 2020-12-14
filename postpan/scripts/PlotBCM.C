void PlotBCM(int run_num=1391){

  gStyle->SetOptFit(1);

  gStyle->SetStatW(0.2);
  gStyle->SetStatH(0.2);
  gStyle->SetStatX(1);
  gStyle->SetStatY(0.9);


  TFile* rootfile = TFile::Open(Form("../../japanOutput/prexALL_%d.root",run_num));
  TTree *tree = (TTree*)rootfile ->Get("mul");
  
  tree->SetAlias("A_ubcm","1e6*asym_bcm_an_us");
  tree->SetAlias("A_dbcm","1e6*asym_bcm_an_ds");
  tree->SetAlias("A_dbcm3x","1e6*asym_bcm_an_ds3");
  TString user_cut = "yield_bcm_an_ds3>15 && ErrorFlag==0";

  TCanvas *c1 = new TCanvas("c1","c1",1000,1000);
  TH1D *h_buff;
  c1->Divide(2,2);
  c1->cd(1);
  tree->Draw("A_ubcm>>hu(100,-1.2e3,1.2e3)",user_cut);
  h_buff = (TH1D*)gDirectory->FindObject("hu");
  h_buff->SetTitle( " Charge Asymmetry, Upstream Analog  BCM");
  c1->cd(2);
  tree->Draw("A_dbcm>>hd(100,-1.2e3,1.2e3)",user_cut);
  h_buff = (TH1D*)gDirectory->FindObject("hd");
  h_buff->SetTitle( " Charge Asymmetry, Downstream Analog BCM");
  c1->cd(3);
  tree->Draw("A_ubcm : A_dbcm>>hud(100,-1e3,1e3,100,-1e3,1e3)",user_cut);

  c1->cd(4);
  tree->Draw("A_ubcm- A_dbcm>>hdd(100,-100,100)",user_cut);
  h_buff = (TH1D*)gDirectory->FindObject("hdd");
  h_buff->SetTitle( " A_ubcm - A_dbcm");
  h_buff->Fit("gaus","QR","",-80,80);

}
