// CheckBPM.C : 
//	ROOT script for checking BPM function
//
// author : Tao Ye <tao.ye@stonybrook.edu>
// 	 05-2019

#include "device_list.h"

void CheckBPM(){

  gStyle->SetStatW(0.3);
  gStyle->SetStatH(0.4);

  TTree *evt_tree = (TTree*)gROOT->FindObject("evt");
  TTree *mul_tree = (TTree*)gROOT->FindObject("mul");
  Int_t nbpm = vBPM.size();

  TCanvas *cbpm = new TCanvas("cbpm","cbpm",2400,1200);
  cbpm->Divide(4,2);
  TCanvas *cwiresum = new TCanvas("cwiresum","cwiresum",2400,1200);
  cwiresum->Divide(4,2);

  TString evt_cut = "ErrorFlag==0";
  TString mul_cut = "ErrorFlag==0";  

  TH1D *h_buff;
  TH1D *hAq = new TH1D("hAq","",100,-1500,1500);
  TH2D *h2d_buff;
  TVirtualPad* pad_buff;
  TGraph* g_buff;
  
  pad_buff=cwiresum->cd(1);  
  mul_tree->SetAlias("Aq","asym_bcm_an_ds3");
  mul_tree->Draw("Aq/ppm",mul_cut);
  TH1D* h1d_buff = (TH1D*)pad_buff->FindObject("htemp");
  Double_t Aq_mean = h1d_buff->GetMean();
  Double_t Aq_rms = h1d_buff->GetRMS();
  TString suffix[2]={"X","Y"};
  
  for(int ibpm=0;ibpm<nbpm;ibpm++){
    ///////____BPM  X and Y ( Event and Multiplet Tree)____ ///////
    for(int ix=0;ix<2;ix++){
      const char* device_name = (TString(vBPM[ibpm])+suffix[ix]).Data();
    
      cbpm->cd(4*ix+1);
      evt_tree->Draw(Form("%s/mm:Entry$",device_name),"ErrorFlag==0","");
    
      pad_buff=cbpm->cd(4*ix+2);
      evt_tree->Draw(Form("%s/mm",device_name),"ErrorFlag==0");
      h_buff=(TH1D*)pad_buff->FindObject("htemp");
      h_buff->SetName("evtTree");
      evt_tree->Draw(Form("%s",device_name),
		     Form("ErrorFlag==0 && %s.Device_Error_Code!=0",device_name),
		     "same");
      h_buff=(TH1D*)pad_buff->FindObject("htemp");
      if(h_buff!=0)
	h_buff->SetLineColor(kRed);

      pad_buff=cbpm->cd(4*ix+3);
      mul_tree->Draw(Form("diff_%s/um:pattern_number",
			  device_name),
		     "ErrorFlag==0","COL");
      TH2F* h2d_buff = (TH2F*)pad_buff->FindObject("htemp");
      h2d_buff->Draw("candlex3");

      pad_buff=cbpm->cd(4*ix+4);
      mul_tree->Draw(Form("diff_%s/um",device_name),
		     "ErrorFlag==0");
      h_buff = (TH1D*)pad_buff->FindObject("htemp");
      h_buff->SetName(device_name);

      mul_tree->Draw(Form("diff_%s/um",device_name),
		     Form("ErrorFlag==0 && diff_%s.Device_Error_Code!=0",
			  device_name),"same");
      h_buff = (TH1D*)pad_buff->FindObject("htemp");
      if(h_buff!=0)
	h_buff->SetLineColor(kRed);

    
    } // end of XY loop
    
    plot_title  = Form("run%s_%s.png",
		       run_seg.Data(),
		       vBPM[ibpm]);

    TText *label = new TText(0.0,0.005,plot_title);     
    label->SetTextFont(23);
    label->SetTextSize(50);
    label->SetNDC();
    cbpm->cd();
    label->Draw("same");
    cbpm->SaveAs(output_path+plot_title);
    cbpm->Clear("D");


    cwiresum->cd(1);
    evt_tree->Draw(Form("%sX/mm:%sY/mm",vBPM[ibpm],vBPM[ibpm]),
		   evt_cut,"COLZ");
    
    cwiresum->cd(2);
    evt_tree->Draw(Form("%sX/mm:%sY/mm",vBPM[ibpm],vBPM[ibpm]),
		   evt_cut,"");

    /////// BPM wiresum asymmetry vs DS BCM  asymmetry  ///////
    cwiresum->cd(3);
    mul_tree->Draw(Form("asym_%sWS/ppm:Aq/ppm",vBPM[ibpm]),
		   mul_cut,"COLZ");

    pad_buff = cwiresum->cd(4);
    mul_tree->Draw(Form("asym_%sWS/ppm:Aq/ppm",vBPM[ibpm]),
		   mul_cut,"prof");
    
    h2d_buff = (TH2D*)pad_buff->FindObject("htemp");

    h2d_buff->Fit("pol1","QR","",
		Aq_mean-2*Aq_rms,
		Aq_mean+2*Aq_rms);

    pad_buff->Update();
    TPaveStats* st = (TPaveStats*)h2d_buff->FindObject("stats");
    st->SetOptFit(1);
    st->SetOptStat(0);
    st->SetTextSize(0.03);
    st->SetX1NDC(0.1);
    st->SetX2NDC(0.5);
    st->SetY1NDC(0.9);
    st->SetY2NDC(0.7);
    
    cwiresum->cd(5);
    evt_tree->Draw(Form("%sXP.hw_sum_raw/%sXP.num_samples*76.29e-6:Entry$",
			vBPM[ibpm],vBPM[ibpm]),
		   "","l");
    cwiresum->cd(6);
    evt_tree->Draw(Form("%sXM.hw_sum_raw/%sXM.num_samples*76.29e-6:Entry$",
			vBPM[ibpm],vBPM[ibpm]),
		   "","l");
    cwiresum->cd(7);
    evt_tree->Draw(Form("%sYP.hw_sum_raw/%sYP.num_samples*76.29e-6:Entry$",
			vBPM[ibpm],vBPM[ibpm]),
		   "","l");
    cwiresum->cd(8);
    evt_tree->Draw(Form("%sYM.hw_sum_raw/%sYM.num_samples*76.29e-6:Entry$",
			vBPM[ibpm],vBPM[ibpm]),
		   "","l");

    plot_title  = Form("run%s_%s_XY_Awiresum.png",
		       run_seg.Data(),vBPM[ibpm]);
    label = new TText(0.0,0.005,plot_title);     
    label->SetTextFont(23);
    label->SetTextSize(50);
    label->SetNDC();
    cwiresum->cd();
    label->Draw("same");
    cwiresum->SaveAs(output_path+plot_title);
    cwiresum->Clear("D");

  } // end of BPM loop

}
