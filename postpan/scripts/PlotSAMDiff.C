void PlotSAMDiff(int run_num=1391){

  gStyle->SetOptFit(1);
  gStyle->SetStatW(0.25);
  gStyle->SetStatH(0.25);
  gStyle->SetStatX(0.9);
  gStyle->SetStatY(0.9);

  TFile* rootfile = TFile::Open(Form("../../japanOutput/prexALL_%d.root",run_num));
  TTree *tree = (TTree*)rootfile ->Get("mul");
  TString user_cut = "(pattern_number>13.5e3  && pattern_number< 14.5e3) || (pattern_number>700 && pattern_number<1300) || ( pattern_number>22.5e3 && pattern_number<23e3)";
  TCanvas *c1 = new TCanvas("c1","c1",1600,800);
  c1->Divide(4,2);

  for(int isam=1;isam<=8;isam++){
    c1->cd(isam);
    tree->Draw(Form("1e6*diff_sam%d>>hsam%d",isam,isam),user_cut);
    TH1D *h_buff = (TH1D*)gDirectory->FindObject(Form("hsam%d",isam));
    h_buff->GetXaxis()->SetTitle("SAM voltage diff (uV)");
    h_buff->GetXaxis()->SetMaxDigits(2);
    h_buff->SetTitle(Form("SAM %d, Beam-off Difference ",isam));
  }
  
  c1->SaveAs(Form("run%d_sam_pedestal_diff.png",run_num));
}
