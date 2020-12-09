void PlotSAMYield(int run_num=1391){

  gStyle->SetOptFit(1);
  gStyle->SetStatW(0.25);
  gStyle->SetStatH(0.25);
  gStyle->SetStatX(0.9);
  gStyle->SetStatY(0.9);

  TFile* rootfile = TFile::Open(Form("../../japanOutput/prexALL_%d.root",run_num));
  TTree *tree = (TTree*)rootfile ->Get("mul");
  TString user_cut = "yield_bcm_an_ds3>20 && ( (pattern_number>4e3 && pattern_number<6e3) || ( pattern_number>15e3 && pattern_number<20e3) )";
  TCanvas *c1 = new TCanvas("c1","c1",1600,800);
  c1->Divide(4,2);

  for(int isam=1;isam<=8;isam++){
    c1->cd(isam);
    tree->Draw(Form("yield_sam%d>>hsam%d",isam,isam),user_cut);
    TH1D *h_buff = (TH1D*)gDirectory->FindObject(Form("hsam%d",isam));
    h_buff->GetXaxis()->SetTitle("SAM yield voltage (V)");
    h_buff->GetXaxis()->SetMaxDigits(2);
    h_buff->SetTitle(Form("SAM %d, Beam-On Yield ",isam));
  }
  
  c1->SaveAs(Form("run%d_sam_yield.png",run_num));
}
