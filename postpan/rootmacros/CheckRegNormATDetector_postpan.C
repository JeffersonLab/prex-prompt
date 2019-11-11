// CheckRegNormDetector_postpan.C : 
//	ROOT script for checking regressed Detector signal from mulc_lrb tree
//
// author : Tao Ye <tao.ye@stonybrook.edu>
// 	 06-2019


void CheckRegNormATDetector_postpan(){

  gStyle->SetStatW(0.3);
  gStyle->SetStatH(0.4);

//  TTree *reg_tree = (TTree*)gROOT->FindObject("mul");
//  TTree *mulc_lrb_tree = (TTree*)gROOT->FindObject("mulc_lrb");
//  reg_tree->AddFriend(mulc_lrb_tree);
  TTree *reg_tree = (TTree*)gROOT->FindObject("reg");
  reg_tree->SetAlias("AqDS","asym_bcm_dg_ds");
  reg_tree->SetAlias("AqUS","asym_bcm_dg_us");
  reg_tree->SetAlias("ppm","1e-6");
  reg_tree->SetAlias("um","1e-3");
  TCanvas *c1 = new TCanvas("c1","c1",2400,1600);
  c1->Divide(3,2);

  c1->cd(1);
  reg_tree->Draw("asym_atl1/ppm","ok_cut");
  c1->cd(2);
  reg_tree->Draw("asym_atr1/ppm","ok_cut");
  c1->cd(3);
  reg_tree->Draw("asym_atl1/ppm:asym_atr1/ppm","ok_cut");
  c1->cd(4);
  reg_tree->Draw("(asym_atl1/ppm-asym_atr1/ppm)/2","ok_cut");
  c1->cd(5);
  reg_tree->Draw("(asym_atl1/ppm+asym_atr1/ppm)/2","ok_cut");
  c1->cd(6);
  reg_tree->Draw("asym_atl1/ppm:asym_atr1/ppm",
		 "ok_cut","prof");
    
  plot_title = Form("run%s_AT1LR_ratecheck_raw_postpan.png",run_seg.Data());

  TText *t1 = new TText(0.0,0.007,plot_title);
  t1->SetNDC();
  t1->SetTextSize(0.05);
  c1->cd();
  t1->Draw("same");
  c1->SaveAs(output_path+plot_title);
  c1->Clear("D");
  

  // Downstream
  c1->cd(1);
  reg_tree->Draw("asym_atl2/ppm","ok_cut");
  c1->cd(2);
  reg_tree->Draw("asym_atr2/ppm","ok_cut");
  c1->cd(3);
  reg_tree->Draw("asym_atl2/ppm:asym_atr2/ppm","ok_cut");
  c1->cd(4);
  reg_tree->Draw("(asym_atl2/ppm-asym_atr2/ppm)/2","ok_cut");
  c1->cd(5);
  reg_tree->Draw("(asym_atl2/ppm+asym_atr2/ppm)/2","ok_cut");
  c1->cd(6);
  reg_tree->Draw("asym_atl2/ppm:asym_atr2/ppm","ok_cut",
		 "prof");
  plot_title = Form("run%s_AT2LR_ratecheck_raw_postpan.png",run_seg.Data());

  t1 = new TText(0.0,0.007,plot_title);
  t1->SetNDC();
  t1->SetTextSize(0.05);
  c1->cd();
  t1->Draw("same");
  c1->SaveAs(output_path+plot_title);
  c1->Clear("D");


  // Regression Corrected
  c1->SetCanvasSize(2400,1200);
  c1->Clear();
  c1->Divide(4,2);
  c1->cd(1);
  // Upstream
  TH1 *hfit, *h_buff;
  Double_t low,up;
  
  c1->cd(1);
  reg_tree->Draw("reg_asym_atl1/ppm","ok_cut");
  c1->cd(2);
  reg_tree->Draw("reg_asym_atr1/ppm","ok_cut");
  c1->cd(3);
  reg_tree->Draw("reg_asym_atl1/ppm:reg_asym_atr1/ppm","ok_cut");
  c1->cd(4);
  reg_tree->Draw("reg_asym_atl1/ppm:reg_asym_atr1/ppm>>hcoratlr1","ok_cut",
		 "prof");
  gPad->Update();
  hfit = (TH2D*)gDirectory->FindObject("hcoratlr1");
  TPaveStats *psus = (TPaveStats*)hfit->FindObject("stats");
  if(psus!=NULL){
    psus->SetOptFit(1);
    psus->SetOptStat(0);
    psus->SetX1NDC(0.0);
    psus->SetY1NDC(0.95);
    psus->SetX2NDC(0.35);
    psus->SetY2NDC(0.7);
  }
  if(hfit!=NULL){
    low = hfit->GetMean()-2*(hfit->GetRMS());
    up = hfit->GetMean()+2*(hfit->GetRMS());
    hfit->Fit("pol1","QR","",low,up);
  } 
  TVirtualPad *pad_buff;
  pad_buff = c1->cd(5);
  reg_tree->Draw("(reg_asym_atl1/ppm-reg_asym_atr1/ppm)/2","ok_cut");

  pad_buff = c1->cd(6);
  reg_tree->Draw("(reg_asym_atl1/ppm-reg_asym_atr1/ppm)/2:Entry$","ok_cut","COL");
  TH2F *h2dus_buff = (TH2F*)pad_buff->FindObject("htemp");
  if(h2dus_buff!=NULL){
    h2dus_buff->Draw("candlex3");  
  }

  c1->cd(7);
  reg_tree->Draw("(reg_asym_atl1/ppm+reg_asym_atr1/ppm)/2","ok_cut");

  pad_buff= c1->cd(8);
  reg_tree->Draw("(reg_asym_atl1/ppm+reg_asym_atr1/ppm)/2:Entry$","ok_cut","COL");
  TH2F *h2dussum_buff = (TH2F*)pad_buff->FindObject("htemp");
  if(h2dussum_buff!=NULL)
    h2dussum_buff->Draw("candlex3");  

  plot_title = Form("run%s_AT1LR_ratecheck_reg_postpan.png",run_seg.Data());

  t1 = new TText(0.0,0.007,plot_title);
  t1->SetNDC();
  t1->SetTextSize(0.05);
  c1->cd();
  t1->Draw("same");
  c1->SaveAs(output_path+plot_title);
  c1->Clear("D");

  // Downstream
  c1->cd(1);
  reg_tree->Draw("reg_asym_atl2/ppm","ok_cut");
  c1->cd(2);
  reg_tree->Draw("reg_asym_atr2/ppm","ok_cut");
  c1->cd(3);
  reg_tree->Draw("reg_asym_atl2/ppm:reg_asym_atr2/ppm","ok_cut");
  c1->cd(4);
  reg_tree->Draw("reg_asym_atl2/ppm:reg_asym_atr2/ppm>>hcorat2lr","ok_cut",
		 "prof");
  gPad->Update();
  h_buff = (TH2D*)gDirectory->FindObject("hcorat2lr");
  TPaveStats *psds = (TPaveStats*)h_buff->FindObject("stats");
  if(psds!=NULL){
    psds->SetOptFit(1);
    psds->SetOptStat(0);
    psds->SetX1NDC(0.0);
    psds->SetY1NDC(0.95);
    psds->SetX2NDC(0.35);
    psds->SetY2NDC(0.7);
  }
  if(h_buff!=NULL){
    low = h_buff->GetMean()-2*h_buff->GetRMS();
    up = h_buff->GetMean()+2*h_buff->GetRMS();
    h_buff->Fit("pol1","QR","",low,up);
  } 

  c1->cd(5);
  reg_tree->Draw("(reg_asym_atl2/ppm-reg_asym_atr2/ppm)/2","ok_cut");

  pad_buff=c1->cd(6);
  reg_tree->Draw("(reg_asym_atl2/ppm-reg_asym_atr2/ppm)/2:Entry$","ok_cut","COL");
  TH2F *h2dds_buff = (TH2F*)pad_buff->FindObject("htemp");
  if(h2dds_buff!=NULL)
    h2dds_buff->Draw("candlex3");  

  c1->cd(7);
  reg_tree->Draw("(reg_asym_atl2/ppm+reg_asym_atr2/ppm)/2","ok_cut");

  c1->cd(8);
  reg_tree->Draw("(reg_asym_atl2/ppm+reg_asym_atr2/ppm)/2:Entry$","ok_cut","COL");
  TH2F *h2ddssum_buff = (TH2F*)pad_buff->FindObject("htemp");
  if(h2ddssum_buff!=NULL)
    h2ddssum_buff->Draw("candlex3");  
    
  plot_title = Form("run%s_AT2LR_ratecheck_reg_postpan.png",run_seg.Data());

  t1 = new TText(0.0,0.007,plot_title);
  t1->SetNDC();
  t1->SetTextSize(0.05);
  c1->cd();
  t1->Draw("same");
  c1->SaveAs(output_path+plot_title);
  c1->Clear("D");

  gSystem->Exec(Form("convert $(ls -rt %s/*ratecheck*_postpan.png) %s/run%s_summary_ratecheck_AT.pdf",
		     output_path.Data(),
		     output_path.Data(),run_seg.Data()));
  gSystem->Exec(Form("rm %s/*ratecheck*_postpan.png ",output_path.Data()));
  gStyle->SetOptStat(1);    
}
