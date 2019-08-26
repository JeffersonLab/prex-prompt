// author: Tao Ye
// date: 05-2019
// description: Macro for checking device events
#include "device_list.h"
void PlotDeviceEvent(const char* device_name, const char* pattern_prefix);
void PlotDeviceEvent(const char* device_name);
void PlotDeviceEvent();


void PlotDeviceEvent(){

  Int_t nbpm = vBPM.size();
  Int_t nsam = vSAM.size();
  Int_t nbcm = vBCM.size();

  /////////////////////////////////////////////////////
  //////////////////   Event   ////////////////////////
  /////////////////////////////////////////////////////

  TCanvas *c1 = new TCanvas("c1","c1",2400,600);
  c1->Divide(2,1);
  TString bpm_channel;
  for(int ibpm=0;ibpm<nbpm;ibpm++){
    c1->cd(1);
    bpm_channel = TString(vBPM[ibpm])+ "X";
    PlotDeviceEvent(bpm_channel.Data());
    c1->cd(2);
    bpm_channel = TString(vBPM[ibpm])+ "Y";
    PlotDeviceEvent(bpm_channel.Data());
      
    plot_title = Form("run%d_event_%s.png",
		      run_number,vBPM[ibpm]);

    TText *t1 = new TText(0.0,0.007,plot_title);
    t1->SetNDC();
    t1->SetTextSize(0.05);
    c1->cd();
    t1->Draw("same");

    c1->SaveAs(output_path+ plot_title);
    c1->Clear("D");
  } // end of BPM Position loop

  for(int ibpm=0;ibpm<nbpm;ibpm++){

    c1->cd(ibpm%2+1);
    TString bpm_ws = TString(vBPM[ibpm])+"WS";
    PlotDeviceEvent(bpm_ws.Data());

    if(ibpm%2==1){
      plot_title = Form("run%d_event_%s_%s_wiresum.png",
			run_number,vBPM[ibpm-1],vBPM[ibpm]);
      TText *t1 = new TText(0.0,0.007,plot_title);
      t1->SetNDC();
      t1->SetTextSize(0.05);
      c1->cd();
      t1->Draw("same");
      c1->SaveAs(output_path+ plot_title);
      c1->Clear("D");
    }// end of plot title block
  } // end of bpm loop

  // for(int isam=0;isam<nsam;isam++){

  //   c1->cd(isam%2+1);
  //   PlotDeviceEvent(vSAM[isam]);

  //   if(isam%2==1){
  //     plot_title = Form("run%d_event_%s_%s.png",
  // 			run_number,vSAM[isam-1],vSAM[isam]);
  //     TText *t1 = new TText(0.0,0.007,plot_title);
  //     t1->SetNDC();
  //     t1->SetTextSize(0.05);
  //     c1->cd();
  //     t1->Draw("same");
  //     c1->SaveAs(output_path+ plot_title);
  //     c1->Clear("D");
  //   }// end of plot title block
  // } // end of lumi loop

  /////////////////////////////////////////////////////////////
  //////////   Asymmetries and Differences   //////////////////
  /////////////////////////////////////////////////////////////

  for(int ibcm=0;ibcm<nbcm;ibcm++){
    c1->cd(ibcm%2+1);
    PlotDeviceEvent(vBCM[ibcm],"asym_");
    if(ibcm%2==1){
      plot_title = Form("run%d_asymmetry_%s_%s.png",
			run_number,vBCM[ibcm-1],vBCM[ibcm]);
      TText *t1 = new TText(0.0,0.007,plot_title);
      t1->SetNDC();
      t1->SetTextSize(0.05);
      c1->cd();
      t1->Draw("same");
      c1->SaveAs(output_path+ plot_title);
      c1->Clear("D");
    }// end of plot title block
  } // end of bcm loop

  for(int ibpm=0;ibpm<nbpm;ibpm++){
    c1->cd(1);
    bpm_channel = TString(vBPM[ibpm])+ "X";
    PlotDeviceEvent(bpm_channel.Data(),"diff_");
    c1->cd(2);
    bpm_channel = TString(vBPM[ibpm])+ "Y";
    PlotDeviceEvent(bpm_channel.Data(),"diff_");
      
    plot_title = Form("run%d_diff_%s.png",
		      run_number,vBPM[ibpm]);

    TText *t1 = new TText(0.0,0.007,plot_title);
    t1->SetNDC();
    t1->SetTextSize(0.05);
    c1->cd();
    t1->Draw("same");

    c1->SaveAs(output_path+ plot_title);
    c1->Clear("D");
  } // end of BPM Position loop

  for(int ibpm=0;ibpm<nbpm;ibpm++){

    c1->cd(ibpm%2+1);
    TString bpm_ws = TString(vBPM[ibpm])+"WS";
    PlotDeviceEvent(bpm_ws.Data(),"asym_");

    if(ibpm%2==1){
      plot_title = Form("run%d_asymmetry_wiresum_%s_%s.png",
			run_number,vBPM[ibpm-1],vBPM[ibpm]);
      TText *t1 = new TText(0.0,0.007,plot_title);
      t1->SetNDC();
      t1->SetTextSize(0.05);
      c1->cd();
      t1->Draw("same");
      c1->SaveAs(output_path+ plot_title);
      c1->Clear("D");
    }// end of plot title block
  } // end of bpm loop

  for(int isam=0;isam<nsam;isam++){

    c1->cd(isam%2+1);
    PlotDeviceEvent(vSAM[isam],"asym_");

    if(isam%2==1){
      plot_title = Form("run%d_asymmetry_%s_%s.png",
			run_number,vSAM[isam-1],vSAM[isam]);
      TText *t1 = new TText(0.0,0.007,plot_title);
      t1->SetNDC();
      t1->SetTextSize(0.05);
      c1->cd();
      t1->Draw("same");
      c1->SaveAs(output_path+ plot_title);
      c1->Clear("D");
    }// end of plot title block
  } // end of lumi loop
  
}

void PlotDeviceEvent(const char* device_name){
  gStyle->SetStatW(0.3);
  gStyle->SetStatH(0.3);

  TTree *evt = (TTree*)gROOT->FindObject("evt");
  TString evtcut = Form("ErrorFlag==0");

  TPad *pad1 = new TPad("pad1","pad1",0.0,0.0,1.0,1.0);
  pad1->Draw();
  pad1->Divide(2,1);
  TH1D *h_buff;
  TVirtualPad* pad_buff;
  TGraph* g_buff;

  pad1->cd(1);
  evt->Draw(Form("%s:Entry$",device_name),evtcut);
  pad_buff=pad1->cd(2);
  evt->Draw(Form("%s",device_name),evtcut);
  h_buff = (TH1D*)pad_buff->FindObject("htemp");
  h_buff->SetName("EvtTree");

  evt->Draw(Form("%s",device_name),
	    evtcut+Form("&& %s.Device_Error_Code!=0",device_name),
	    "same"); 
  h_buff = (TH1D*)pad_buff->FindObject("htemp");
  if(h_buff!=0)
    h_buff->SetLineColor(kRed);

}
void PlotDeviceEvent(const char* device_name, const char* pattern_prefix){
  gStyle->SetStatW(0.3);
  gStyle->SetStatH(0.3);

  TTree *mul = (TTree*)gROOT->FindObject("mul");
  TString mulcut = Form("ErrorFlag==0");

  TPad *pad1 = new TPad("pad1","pad1",0.0,0.0,1.0,1.0);
  pad1->Draw();
  pad1->Divide(2,1);
  TH1D *h_buff;
  TVirtualPad* pad_buff;
  TGraph* g_buff;

  pad_buff=pad1->cd(1);
  mul->Draw(Form("%s%s:pattern_number",pattern_prefix,device_name),mulcut,"COL");
  TH2F* H_history = (TH2F*)pad_buff->FindObject("htemp");
  H_history->Draw("candlex3");

  pad_buff=pad1->cd(2);
  mul->Draw(Form("%s%s",pattern_prefix,device_name),mulcut);
  h_buff = (TH1D*)pad_buff->FindObject("htemp");
  h_buff->SetName("MulTree");

  mul->Draw(Form("%s%s",pattern_prefix,device_name),
  	    mulcut+Form("&& %s%s.Device_Error_Code!=0",pattern_prefix,device_name),
  	    "same");
  h_buff = (TH1D*)pad_buff->FindObject("htemp");
  if(h_buff!=0)
    h_buff->SetLineColor(kRed);

}
