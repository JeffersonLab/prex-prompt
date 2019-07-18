// author: Tao Ye
// date: 05-2019
// decription: Macro for showing BCM correlation and double difference 

#include "device_list.h"

void CheckBCMdd(const char* bcm1 , const char* bcm2, TString treeName);  //interface to panguin
void CheckBCMdd(TString treeName="mul"); // interface to summary plot

void CheckBCMdd(TString treeName){

  Int_t nbcm = vBCM.size();

  TCanvas *c3 = new TCanvas("c3","c3",2400,600);
  c3->cd();
  
  vector<const char*> vBCM1={"bcm_an_us","bcm_an_us","bcm_an_ds","bcm_dg_us","bcm_dg_us","bcm_dg_us","bcm_dg_ds"};
  vector<const char*> vBCM2={"bcm_an_ds","bcm_an_ds3","bcm_an_ds3","bcm_dg_ds","bcm_an_ds3","bcm_an_ds","bcm_an_us"};
  Int_t nplot = vBCM1.size();
  for(int ibcm=0; ibcm<nplot;ibcm++){

    c3->Clear("D");
    c3->cd();
    CheckBCMdd(vBCM1[ibcm],vBCM2[ibcm],treeName);

    plot_title = Form("run%s_asym_%s_vs_asym_%s_%s.png",
		      run_seg.Data(),vBCM1[ibcm],vBCM2[ibcm],
		      treeName.Data());
    TText *label = new TText(0.0,0.01,plot_title);      
    label->SetNDC();
    c3->cd();
    label->Draw("same");
    c3->SaveAs(output_path+plot_title);
  }
  
  // gSystem->Exec(Form("convert $(ls -rt %s*bcm*DD*.png) %srun%d_bcm_double_diff.pdf",
  // 		     output_path.Data(),output_path.Data(),
  // 		     run_number));
  // gSystem->Exec(Form("rm %s*bcm*DD*.png",output_path.Data()));

}

void CheckBCMdd(const char* bcm1 , const char* bcm2, TString treeName){
  gStyle->SetOptStat(1);
  TString asym_bcm1 = "asym_"+TString(bcm1)+"/ppm";
  TString asym_bcm2 = "asym_"+TString(bcm2)+"/ppm";
  TTree* tree = (TTree*)gROOT->FindObject(treeName);

  TPad *pad1 = new TPad("pad1","pad1",0,0,1,1);
  pad1->Divide(4,1);
  pad1->Draw();
  TVirtualPad *pad_buff;
  TProfile *prof_buff;
  TH1D *h_buff;

  pad_buff =pad1->cd(1);
  
  tree->Draw(Form("%s:%s",asym_bcm1.Data(),asym_bcm2.Data()),"ErrorFlag==0","prof");
  gPad->Update();
  prof_buff=(TProfile*)pad_buff->FindObject("htemp");
  if (prof_buff!=NULL){
    TPaveStats* st = (TPaveStats*)prof_buff->FindObject("stats");
    st->SetOptFit(1);
    st->SetOptStat(0);
    st->SetX1NDC(0.1);
    st->SetY1NDC(0.9);
    st->SetY2NDC(0.7);
    st->SetX2NDC(0.6);
    prof_buff->Fit("pol1","Q");
  }
  
  pad1->cd(2);
  tree->Draw(Form("%s:%s",asym_bcm1.Data(),asym_bcm2.Data()),"ErrorFlag==0");

  pad_buff = pad1->cd(3);
  tree->Draw(Form("%s-%s",asym_bcm1.Data(),asym_bcm2.Data()),"ErrorFlag==0");
  h_buff=(TH1D*)pad_buff->FindObject("htemp");
  if (h_buff!=NULL){
    h_buff->SetName(treeName+"Tree");
    pad_buff->Update();
    TPaveStats* st_hist = (TPaveStats*)h_buff->FindObject("stats");
    st_hist->SetX1NDC(0.7);
    st_hist->SetY1NDC(0.6);
    st_hist->SetY2NDC(0.9);
    st_hist->SetX2NDC(1.0);
  }

  pad_buff = pad1->cd(4);
  tree->Draw(Form("%s-%s:pattern_number",asym_bcm1.Data(),asym_bcm2.Data()),
	     "ErrorFlag==0",
	     "COL");
  TH2F* H_history = (TH2F*)pad_buff->FindObject("htemp");
  if (H_history!=NULL)
    H_history->Draw("candlex3");


}
