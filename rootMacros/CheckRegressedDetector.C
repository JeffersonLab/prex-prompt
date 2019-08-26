// CheckRegressedDetector.C : 
//	ROOT script for checking regressed Detector signal from mulc_lrb tree
//
// author : Tao Ye <tao.ye@stonybrook.edu>
// 	 06-2019


void CheckRegressedDetector(){

  gStyle->SetStatW(0.3);
  gStyle->SetStatH(0.4);

  TTree *mul_tree = (TTree*)gROOT->FindObject("mul");
  TTree *mulc_lrb_tree = (TTree*)gROOT->FindObject("mulc_lrb");
  mul_tree->AddFriend(mulc_lrb_tree);
  mul_tree->SetAlias("Aq","asym_bcm_an_ds3");
  mul_tree->SetAlias("AqDS3","asym_bcm_an_ds3");
  mul_tree->SetAlias("AqUS","asym_bcm_an_us");

  TCanvas *c1 = new TCanvas("c1","c1",2400,1600);
  c1->Divide(3,2);

  c1->cd(1);
  mul_tree->Draw("asym_usl/ppm-Aq/ppm","ErrorFlag==0");
  c1->cd(2);
  mul_tree->Draw("asym_usr/ppm-Aq/ppm","ErrorFlag==0");
  c1->cd(3);
  mul_tree->Draw("asym_usl/ppm-Aq/ppm:asym_usr/ppm-Aq/ppm","ErrorFlag==0");
  c1->cd(4);
  mul_tree->Draw("asym_usl/ppm-asym_usr/ppm","ErrorFlag==0");
  c1->cd(5);
  mul_tree->Draw("asym_usl/ppm+asym_usr/ppm-2*Aq","ErrorFlag==0");
  c1->cd(6);
  mul_tree->Draw("asym_usl/ppm-Aq/ppm:asym_usr/ppm-Aq/ppm",
		 "ErrorFlag==0","prof");
    
  plot_title = Form("run%s_upstreamLR_ratecheck_raw.png",run_seg.Data());

  TText *t1 = new TText(0.0,0.007,plot_title);
  t1->SetNDC();
  t1->SetTextSize(0.05);
  c1->cd();
  t1->Draw("same");
  c1->SaveAs(output_path+plot_title);
  c1->Clear("D");
  

  // Downstream
  c1->cd(1);
  mul_tree->Draw("asym_dsl/ppm-Aq/ppm","ErrorFlag==0");
  c1->cd(2);
  mul_tree->Draw("asym_dsr/ppm-Aq/ppm","ErrorFlag==0");
  c1->cd(3);
  mul_tree->Draw("asym_dsl/ppm-Aq/ppm:asym_dsr/ppm-Aq/ppm","ErrorFlag==0");
  c1->cd(4);
  mul_tree->Draw("asym_dsl/ppm-asym_dsr/ppm","ErrorFlag==0");
  c1->cd(5);
  mul_tree->Draw("asym_dsl/ppm+asym_dsr/ppm-2*Aq/ppm","ErrorFlag==0");
  c1->cd(6);
  mul_tree->Draw("asym_dsl/ppm-Aq/ppm:asym_dsr/ppm-Aq/ppm","ErrorFlag==0",
		 "prof");
  plot_title = Form("run%s_downstreamLR_ratecheck_raw.png",run_seg.Data());

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
  mul_tree->Draw("cor_usl/ppm-Aq/ppm","ErrorFlag==0");
  c1->cd(2);
  mul_tree->Draw("cor_usr/ppm-Aq/ppm","ErrorFlag==0");
  c1->cd(3);
  mul_tree->Draw("cor_usl/ppm-Aq/ppm:cor_usr/ppm-Aq/ppm","ErrorFlag==0");
  c1->cd(4);
  mul_tree->Draw("cor_usl/ppm-Aq/ppm:cor_usr/ppm-Aq/ppm>>hcoruslr","ErrorFlag==0",
		 "prof");
  gPad->Update();
  hfit = (TH2D*)gDirectory->FindObject("hcoruslr");
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
  mul_tree->Draw("(cor_usl/ppm-cor_usr/ppm)/2","ErrorFlag==0");

  pad_buff = c1->cd(6);
  mul_tree->Draw("(cor_usl/ppm-cor_usr/ppm)/2:pattern_number","ErrorFlag==0","COL");
  TH2F *h2dus_buff = (TH2F*)pad_buff->FindObject("htemp");
  if(h2dus_buff!=NULL)
    h2dus_buff->Draw("candlex3");  

  c1->cd(7);
  mul_tree->Draw("(cor_usl/ppm+cor_usr/ppm)/2-Aq/ppm","ErrorFlag==0");

  pad_buff= c1->cd(8);
  mul_tree->Draw("(cor_usl/ppm+cor_usr/ppm)/2-Aq/ppm:Entry$","ErrorFlag==0","COL");
  TH2F *h2dussum_buff = (TH2F*)pad_buff->FindObject("htemp");
  if(h2dussum_buff!=NULL)
    h2dussum_buff->Draw("candlex3");  

  plot_title = Form("run%s_upstreamLR_ratecheck_reg.png",run_seg.Data());

  t1 = new TText(0.0,0.007,plot_title);
  t1->SetNDC();
  t1->SetTextSize(0.05);
  c1->cd();
  t1->Draw("same");
  c1->SaveAs(output_path+plot_title);
  c1->Clear("D");

  // Downstream
  c1->cd(1);
  mul_tree->Draw("cor_dsl/ppm-Aq/ppm","ErrorFlag==0");
  c1->cd(2);
  mul_tree->Draw("cor_dsr/ppm-Aq/ppm","ErrorFlag==0");
  c1->cd(3);
  mul_tree->Draw("cor_dsl/ppm-Aq/ppm:cor_dsr/ppm-Aq/ppm","ErrorFlag==0");
  c1->cd(4);
  mul_tree->Draw("cor_dsl/ppm-Aq/ppm:cor_dsr/ppm-Aq/ppm>>hcordslr","ErrorFlag==0",
		 "prof");
  gPad->Update();
  hfit = (TH2D*)gDirectory->FindObject("hcordslr");
  TPaveStats *psds = (TPaveStats*)hfit->FindObject("stats");
  if(psds!=NULL){
    psds->SetOptFit(1);
    psds->SetOptStat(0);
    psds->SetX1NDC(0.0);
    psds->SetY1NDC(0.95);
    psds->SetX2NDC(0.35);
    psds->SetY2NDC(0.7);
  }
  if(hfit!=NULL){
    low = hfit->GetMean()-2*hfit->GetRMS();
    up = hfit->GetMean()+2*hfit->GetRMS();
    hfit->Fit("pol1","QR","",low,up);

  } 

  c1->cd(5);
  mul_tree->Draw("(cor_dsl/ppm-cor_dsr/ppm)/2","ErrorFlag==0");

  pad_buff=c1->cd(6);
  mul_tree->Draw("(cor_dsl/ppm-cor_dsr/ppm)/2:Entry$","ErrorFlag==0","COL");
  TH2F *h2dds_buff = (TH2F*)pad_buff->FindObject("htemp");
  if(h2dds_buff!=NULL)
    h2dds_buff->Draw("candlex3");  

  c1->cd(7);
  mul_tree->Draw("(cor_dsl/ppm+cor_dsr/ppm)/2-Aq/ppm","ErrorFlag==0");

  c1->cd(8);
  mul_tree->Draw("(cor_dsl/ppm+cor_dsr/ppm)/2-Aq/ppm:Entry$","ErrorFlag==0","COL");
  TH2F *h2ddssum_buff = (TH2F*)pad_buff->FindObject("htemp");
  if(h2ddssum_buff!=NULL)
    h2ddssum_buff->Draw("candlex3");  
    
  plot_title = Form("run%s_downstreamLR_ratecheck_reg.png",run_seg.Data());

  t1 = new TText(0.0,0.007,plot_title);
  t1->SetNDC();
  t1->SetTextSize(0.05);
  c1->cd();
  t1->Draw("same");
  c1->SaveAs(output_path+plot_title);
  c1->Clear("D");

  //  ======== vMainDet vs AqDS3
  gStyle->SetOptFit(1);
  gStyle->SetOptStat(0);
  gStyle->SetStatW(0.3);
  gStyle->SetStatH(0.25);
  TCanvas *c0 = new TCanvas("c0","c0",2400,1200);
  c0->Divide(4,2);
  TString filename;
  TText *label;


  TString user_cut = "ErrorFlag==0";
  for(int i=0;i<4;i++){
    c0->cd(i+1);
    mul_tree->Draw(Form("cor_%s/ppm:AqDS3/ppm",vMainDet[i])
		    ,user_cut);
    c0->cd(i+5);
    TString hist_name = "hds" +TString(vMainDet[i]);
    mul_tree->Draw(Form("cor_%s/ppm:AqDS3/ppm>>%s",
			 vMainDet[i],hist_name.Data()),
		    user_cut,"prof");
    hfit = (TH2D*)gDirectory->FindObject(hist_name);
    if(hfit!=NULL){
      low = hfit->GetMean()-2*hfit->GetRMS();
      up = hfit->GetMean()+2*hfit->GetRMS();
      hfit->Fit("pol1","QR","",low,up);
    }
  } 
  filename = Form("run%s_main_vs_AqDS3_ratecheck_reg.png",
		  run_seg.Data());
  label = new TText(0.0,0.01,filename);     
  label->SetTextSize(0.03);
  label->SetNDC();
  c0->cd();
  label->Draw("same");
  c0->SaveAs(output_path+filename);
  c0->Clear("D");
  //  ======== vMainDet vs AqUS
  for(int i=0;i<4;i++){
    c0->cd(i+1);
    mul_tree->Draw(Form("cor_%s/ppm:AqUS/ppm",vMainDet[i])
		    ,user_cut);
    c0->cd(i+5);
    TString hist_name = "hus" +TString(vMainDet[i]);
    mul_tree->Draw(Form("cor_%s/ppm:AqUS/ppm>>%s",
			 vMainDet[i],hist_name.Data()),
		    user_cut,"prof");
    hfit = (TH2D*)gDirectory->FindObject(hist_name);
    if(hfit!=NULL){
      low = hfit->GetMean()-2*hfit->GetRMS();
      up = hfit->GetMean()+2*hfit->GetRMS();
      hfit->Fit("pol1","QR","",low,up);
    }
  } 
  filename = Form("run%s_main_vs_AqUS_ratecheck_reg.png",
		  run_seg.Data());
  label = new TText(0.0,0.01,filename);     
  label->SetTextSize(0.03);
  label->SetNDC();
  c0->cd();
  label->Draw("same");
  c0->SaveAs(output_path+filename);
  c0->Clear("D");

  gStyle->SetOptStat(1);    
}
