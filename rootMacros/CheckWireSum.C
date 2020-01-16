// CheckBPM.C : 
//	ROOT script for checking BPM function
//
// author : Tao Ye <tao.ye@stonybrook.edu>
// 	 05-2019

#include "device_list.h"

void CheckWireSum(){

  gStyle->SetStatW(0.3);
  gStyle->SetStatH(0.4);

  TTree *mul_tree = (TTree*)gROOT->FindObject("mul");
  
  TString injBPMs[] = {"asym_bpm2i01WS","asym_bpm2i02WS","asym_bpm1i02","asym_bpm0i07WS","asym_bpm0l01WS","asym_bcm0l02","asym_bcm_an_us"};
  int nBPM = sizeof(injBPMs)/sizeof(*injBPMs);
  
  TCanvas *c1 = new TCanvas("c1","c1",2400,800);
  c1->Divide(3,1);
  for(int ibpm=0;ibpm<nBPM;ibpm++){
    TString device_name = injBPMs[ibpm];
    
    c1->cd(1);
    mul_tree->Draw(device_name+"/ppm","ErrorFlag==0");
    c1->cd(2);
    mul_tree->Draw(device_name+"/ppm:Entry$","ErrorFlag==0");
    c1->cd(3);
    mul_tree->Draw(device_name+"/ppm:Entry$","ErrorFlag==0","COL");
    TH2F* h2d_buff = (TH2F*)gPad->FindObject("htemp");
    if (h2d_buff!=NULL)
      h2d_buff->Draw("candlex3");
    
    plot_title = Form("run%s_bpm_%s.png",
		      run_seg.Data(),
		      device_name.Data());
    
    TText *t1 = new TText(0.0,0.007,plot_title);
    t1->SetNDC();
    t1->SetTextSize(0.05);
    c1->cd();
    t1->Draw("same");
    c1->SaveAs(output_path+plot_title);
    c1->Clear("D");

  }
  
}
