void PlotSAMRawAsym(int run_num);
void PlotSAMNormAsym(int run_num);
void PlotSAMRegAsym(int run_num);
void PlotSAMRegNormAsym(int run_num);
void PlotSAM(int run_num);
void PlotBCMCorrelation(int run_num);

void CheckSAM(Int_t run_num){
  gStyle->SetOptFit(1);
  gStyle->SetStatW(0.25);
  gStyle->SetStatH(0.25);
  gStyle->SetStatX(0.9);
  gStyle->SetStatY(0.9);

  // PlotSAMRawAsym(run_num);
  // PlotSAMNormAsym(run_num);
  // PlotSAMRegAsym(run_num);
  // PlotSAMRegNormAsym(run_num);
  PlotBCMCorrelation(run_num);
}

void PlotBCMCorrelation(int run_num){
  TFile* rootfile = TFile::Open(Form("../ROOTfiles/parity18_%d_regress.root",run_num));
  TTree *tree = (TTree*)rootfile ->Get("reg");
  TString user_cut ="ok_cut";  

  TCanvas *c1 = new TCanvas("c1","c1",2000,1000);
  c1->Divide(4,2);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(1);

  gStyle->SetStatW(0.25);
  gStyle->SetStatH(0.2);
  gStyle->SetStatX(0.6);
  gStyle->SetStatY(0.9);

  for(int isam=2;isam<=8;isam++){
    c1->cd(isam);
    tree->Draw(Form("1e6*reg_asym_sam%d : 1e6*asym_bcm_an_ds3>>hsambcm%d",isam,isam),user_cut,"COLZ");
    TH2D *h_buff = (TH2D*)gDirectory->FindObject(Form("hsambcm%d",isam));
    h_buff->GetXaxis()->SetTitle("BCM Charge  Asymmetry (ppm)");
    h_buff->SetTitle(Form("Regressed A_SAM%d vs Aq BCM DSx3 ",isam));
    h_buff->Draw("COLZ");
  }
  
  c1->SaveAs(Form("run%d_reg_sam_vs_bcm.png",run_num));

  tree->Draw("1e6*asym_bcm_an_ds3>>hbcm","ok_cut","goff");
  TH1D *hbcm = (TH1D*)gDirectory->FindObject("hbcm");
  double x_low = hbcm->GetMean()-2*(hbcm->GetRMS());
  double x_up = hbcm->GetMean()+2*(hbcm->GetRMS());
  for(int isam=2;isam<=8;isam++){
    c1->cd(isam);
    tree->Draw(Form("1e6*reg_asym_sam%d : 1e6*asym_bcm_an_ds3>>hsambcm%d",isam,isam),user_cut,"prof");
    TH2D *h_buff = (TH2D*)gDirectory->FindObject(Form("hsambcm%d",isam));
    h_buff->GetXaxis()->SetTitle("BCM Charge  Asymmetry (ppm)");
    h_buff->SetTitle(Form("Regressed A_SAM%d vs Aq BCM DSx3 ",isam));
    h_buff->Fit("pol1","QR","",x_low,x_up);
  }
  
  c1->SaveAs(Form("run%d_reg_sam_vs_bcm_prof.png",run_num));
  
}
void PlotSAMRegAsym(int run_num){
  
  TFile* rootfile = TFile::Open(Form("../ROOTfiles/parity18_%d_regress.root",run_num));
  TTree *tree = (TTree*)rootfile ->Get("reg");

  TString user_cut ="ok_cut";
  TCanvas *c1 = new TCanvas("c1","c1",2000,1000);
  c1->Divide(4,2);

  for(int isam=2;isam<=8;isam++){
    c1->cd(isam);
    tree->Draw(Form("1e6*reg_asym_sam%d>>hsam%d",isam,isam),user_cut);
    TH1D *h_buff = (TH1D*)gDirectory->FindObject(Form("hsam%d",isam));
    h_buff->GetXaxis()->SetTitle("SAM Regressed Asymmetry (ppm)");

    h_buff->GetXaxis()->SetMaxDigits(2); // Only works in ROOT 6
    h_buff->SetTitle(Form("SAM %d, Beam-On Regressed Asymmetry ",isam));
  }
  
  c1->SaveAs(Form("run%d_sam_reg_asym.png",run_num));
}

void PlotSAMNormAsym(int run_num){
  
  TFile* rootfile = TFile::Open(Form("../ROOTfiles/parity18_%d_regress.root",run_num));
  TTree *tree = (TTree*)rootfile ->Get("reg");

  TString user_cut ="ok_cut";
  TCanvas *c1 = new TCanvas("c1","c1",2000,1000);
  c1->Divide(4,2);

  for(int isam=2;isam<=8;isam++){
    c1->cd(isam);
    tree->Draw(Form("1e6*asym_sam%d - 1e6*asym_bcm_an_ds3>>hsam%d",isam,isam),user_cut);
    TH1D *h_buff = (TH1D*)gDirectory->FindObject(Form("hsam%d",isam));
    h_buff->GetXaxis()->SetTitle("SAM Normalized Asymmetry (ppm)");

    h_buff->GetXaxis()->SetMaxDigits(2); // Only works in ROOT 6
    h_buff->SetTitle(Form("SAM %d, Beam-On Normalized Asymmetry ",isam));
  }
  
  c1->SaveAs(Form("run%d_sam_norm_asym.png",run_num));
}
void PlotSAMRegNormAsym(int run_num){
  
  TFile* rootfile = TFile::Open(Form("../ROOTfiles/parity18_%d_regress.root",run_num));
  TTree *tree = (TTree*)rootfile ->Get("reg");

  TString user_cut ="ok_cut";
  TCanvas *c1 = new TCanvas("c1","c1",2000,1000);
  c1->Divide(4,2);

  for(int isam=2;isam<=8;isam++){
    c1->cd(isam);
    tree->Draw(Form("1e6*reg_asym_sam%d - 1e6*asym_bcm_an_ds3>>hsam%d",isam,isam),user_cut);
    TH1D *h_buff = (TH1D*)gDirectory->FindObject(Form("hsam%d",isam));
    h_buff->GetXaxis()->SetTitle("SAM Normalized Asymmetry (ppm)");

    h_buff->GetXaxis()->SetMaxDigits(2); // Only works in ROOT 6
    h_buff->SetTitle(Form("SAM %d, Beam-On Regressed Normalized Asymmetry ",isam));
  }
  
  c1->SaveAs(Form("run%d_sam_reg_norm_asym.png",run_num));
}
void PlotSAMRawAsym(int run_num){
  
  TFile* rootfile = TFile::Open(Form("../ROOTfiles/parity18_%d_regress.root",run_num));
  TTree *tree = (TTree*)rootfile ->Get("reg");

  TString user_cut ="ok_cut";
  TCanvas *c1 = new TCanvas("c1","c1",2000,1000);
  c1->Divide(4,2);

  for(int isam=2;isam<=8;isam++){
    c1->cd(isam);
    tree->Draw(Form("1e6*asym_sam%d>>hsam%d",isam,isam),user_cut);
    TH1D *h_buff = (TH1D*)gDirectory->FindObject(Form("hsam%d",isam));
    h_buff->GetXaxis()->SetTitle("SAM Raw Asymmetry (ppm)");

    h_buff->GetXaxis()->SetMaxDigits(2); // Only works in ROOT 6
    h_buff->SetTitle(Form("SAM %d, Beam-On Raw Asymmetry ",isam));
  }
  
  c1->SaveAs(Form("run%d_sam_raw_asym.png",run_num));
}

void PlotSAM(Int_t run_num){
  TFile* rootfile = TFile::Open(Form("../ROOTfiles/parity18_%d_regress.root",run_num));
  TTree *reg = (TTree*)rootfile ->Get("reg");
  
  TCanvas *c1 = new TCanvas("c1","c1",1200,600);
  c1->Divide(4,2);

  for(int i=2; i<=8;i++){
    c1->cd(i);
    reg->Draw(Form("1e6*reg_asym_sam%d:1e6*asym_bcm_an_ds3",i),"ok_cut","prof");
  }

}

