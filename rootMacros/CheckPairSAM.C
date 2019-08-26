// CheckPairSAM.C : 
//	ROOT script for SAM resolution check for japan Ouputs
//
//  author: Tao Ye 
//  	06-2019

#include "device_list.h"
void CheckPairSAM(vector<TString> vDet, TString tag,TString user_cut);

void CheckPairSAM(){

  vector<TString> vSAMU = {"cor_sam2","cor_sam6","cor_sam4","cor_sam8"};
  vector<TString> vSAMV = {"cor_sam1","cor_sam5","cor_sam3","cor_sam7"};

  CheckPairSAM(vSAMU,"cor_sam2648","ErrorFlag==0");  // FIXME : It should be device_Error_Code  (Maybe ... )
  CheckPairSAM(vSAMV,"cor_sam1537","ErrorFlag==0");

}
void CheckPairSAM(vector<TString> vDet, TString tag, TString user_cut){

  TTree *mul_tree = (TTree*)gROOT ->FindObject("mul");
  TTree *mulc_tree = (TTree*)gROOT ->FindObject("mulc_lrb");
  mulc_tree->AddFriend(mul_tree);

  mulc_tree->SetAlias("AqDS", "asym_bcm_an_ds/ppm");
  mulc_tree->SetAlias("AqUS", "asym_bcm_an_us/ppm");
  mulc_tree->SetAlias("AverageLumi",
		      Form("(%s+%s+%s+%s)/4",
			   vDet[0].Data(),vDet[1].Data(),vDet[2].Data(),vDet[3].Data()));


  // FIXME : Check if mulc_tree exists or if it is empty
  // FIXME : Check if DV exists or if it is empty
  
  TString filename;
  TText *label;
  TH1 *hfit;
  Double_t low, up;

  // Pairing Detectors 

  gStyle->SetOptStat(1);
  gStyle->SetOptFit(1);
  gStyle->SetStatW(0.3);
  gStyle->SetStatH(0.25);
  gStyle->SetStatX(0.95);
  gStyle->SetStatY(0.95);

  TCanvas *c1 = new TCanvas("c1","c1",2400,1600);
  c1->Divide(3,2);
  c1->cd(1);
  mulc_tree->Draw(Form("%s/ppm",vDet[0].Data()),
		  user_cut);
  c1->cd(2);
  mulc_tree->Draw(Form("%s/ppm",vDet[1].Data())
		  ,user_cut);
  c1->cd(3);
  mulc_tree->Draw(Form("%s/ppm : %s/ppm",vDet[0].Data(),vDet[1].Data()),
		  user_cut);
  c1->cd(4);
  mulc_tree->Draw(Form("%s/ppm : %s/ppm",vDet[0].Data(),vDet[1].Data()),
		  user_cut,"prof");

  c1->cd(5);
  mulc_tree->Draw(Form("%s/ppm - %s/ppm",vDet[0].Data(),vDet[1].Data()),
		  user_cut);

  c1->cd(6);  
  mulc_tree->Draw(Form("%s/ppm + %s/ppm",vDet[0].Data(),vDet[1].Data()),
		  user_cut);

  filename = Form("run%s_combo_%s_vs_%s.png",
		  run_seg.Data(),
		  vDet[0].Data(),
		  vDet[1].Data());
  label = new TText(0.0,0.01,filename);     
  label->SetTextSize(0.03);
  label->SetNDC();
  c1->cd();
  label->Draw("same");
  c1->SaveAs(output_path+filename);
  c1->Clear("D");

  // The other pair
  c1->cd(1);
  mulc_tree->Draw(Form("%s/ppm",vDet[2].Data()),
		  user_cut);
  c1->cd(2);
  mulc_tree->Draw(Form("%s/ppm",vDet[3].Data())
		  ,user_cut);
  c1->cd(3);
  mulc_tree->Draw(Form("%s/ppm : %s/ppm",vDet[2].Data(),vDet[3].Data()),
		  user_cut);
  c1->cd(4);
  mulc_tree->Draw(Form("%s/ppm : %s/ppm",vDet[2].Data(),vDet[3].Data()),
		  user_cut,"prof");

  c1->cd(5);
  mulc_tree->Draw(Form("%s/ppm - %s/ppm",vDet[2].Data(),vDet[3].Data()),
		  user_cut);

  c1->cd(6);  
  mulc_tree->Draw(Form("%s/ppm + %s/ppm",vDet[2].Data(),vDet[3].Data()),
		  user_cut);

  filename = Form("run%s_combo_%s_vs_%s.png",
		  run_seg.Data(),
		  vDet[2].Data(),
		  vDet[3].Data());
  label = new TText(0.0,0.01,filename);     
  label->SetTextSize(0.03);
  label->SetNDC();
  c1->cd();
  label->Draw("same");
  c1->SaveAs(output_path+filename);
  c1->Clear("D");

  // Combo Det and double differences

  TCanvas *c4 = new TCanvas("c4","c4",2400,2400);
  c4->Divide(2,2);
  c4->cd(1);
  mulc_tree->Draw(Form("(%s+%s)/2/ppm ",vDet[0].Data(),vDet[1].Data()),
		  user_cut);
  c4->cd(2);
  mulc_tree->Draw(Form("(%s+%s)/2/ppm ",vDet[2].Data(),vDet[3].Data()),
		  user_cut);
  c4->cd(3);
  mulc_tree->Draw(Form("(%s+%s)/2/ppm:(%s+%s)/2/ppm ",
		       vDet[0].Data(),vDet[1].Data(),
		       vDet[2].Data(),vDet[3].Data()),
		  user_cut);

  c4->cd(4);  
  mulc_tree->Draw(Form("(%s+%s)/2/ppm-(%s+%s)/2/ppm ",
		       vDet[0].Data(),vDet[1].Data(),
		       vDet[2].Data(),vDet[3].Data()),
		  user_cut);


  filename = Form("run%s_combo_%s_dd.png",run_seg.Data(),tag.Data());
  label = new TText(0.0,0.01,filename);     
  label->SetTextSize(0.03);
  label->SetNDC();
  c4->cd();
  label->Draw("same");
  c4->SaveAs(output_path+filename);


  // THe other group of plots
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(1);

  TCanvas *c0 = new TCanvas("c0","c0",2400,1200);
  c0->Divide(4,2);

  //  ======== vSAM vs AqDS
  for(int i=0;i<4;i++){
    c0->cd(i+1);
    mulc_tree->Draw(Form("%s/ppm:AqDS",vDet[i].Data())
		    ,user_cut);
    c0->cd(i+5);
    TString hist_name = "hds" +vDet[i];
    mulc_tree->Draw(Form("%s/ppm:AqDS>>%s",
			 vDet[i].Data(),hist_name.Data()),
		    user_cut,"prof");
    hfit = (TH2D*)gDirectory->FindObject(hist_name);
    low = hfit->GetMean()-2*hfit->GetRMS();
    up = hfit->GetMean()+2*hfit->GetRMS();
    hfit->Fit("pol1","QR","",low,up);
  } 
  filename = Form("run%s_combo_%s_vs_AqDS.png",
		  run_seg.Data(),
		  tag.Data());
  label = new TText(0.0,0.01,filename);     
  label->SetTextSize(0.03);
  label->SetNDC();
  c0->cd();
  label->Draw("same");
  c0->SaveAs(output_path+filename);
  c0->Clear("D");
  //  ======== vSAM vs AqUS
  for(int i=0;i<4;i++){

    c0->cd(i+1);
    mulc_tree->Draw(Form("%s/ppm:AqUS",vDet[i].Data())
		    ,user_cut);

    c0->cd(i+5);
    
    TString hist_name = "hus" +vDet[i];
    mulc_tree->Draw(Form("%s/ppm:AqUS>>%s",
			 vDet[i].Data(),hist_name.Data()),
		    user_cut,"prof");
    hfit = (TH2D*)gDirectory->FindObject(hist_name);
    low = hfit->GetMean()-2*hfit->GetRMS();
    up = hfit->GetMean()+2*hfit->GetRMS();
    hfit->Fit("pol1","QR","",low,up);
  } 

  filename = Form("run%s_combo_%s_vs_AqUS.png",
		  run_seg.Data(),
		  tag.Data());
  label = new TText(0.0,0.01,filename);     
  label->SetTextSize(0.03);
  label->SetNDC();
  c0->cd();
  label->Draw("same");
  c0->SaveAs(output_path+filename);
  
  // Double difference bewteen detector and BCM 
  c4->Clear("D");
  c4->cd(1);
  mulc_tree->Draw("AqUS",user_cut);
  c4->cd(2);
  mulc_tree->Draw("AverageLumi",user_cut);
  
  gSystem->Exec(Form("convert $(ls -rt %s/*combo*.png) %s/run%s_summary_combo_%s.pdf",
		     output_path.Data(),
		     output_path.Data(),run_seg.Data(),tag.Data()));
  gSystem->Exec(Form("rm %s/*combo*.png ",output_path.Data()));

}

