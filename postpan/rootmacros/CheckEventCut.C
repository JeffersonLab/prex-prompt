// author : Tao Ye
// date : 05-2019
// description: Macro for checking global event cuts
#include "device_list.h"
#ifndef CHECK_EVENT_CUT
#define CHECK_EVENT_CUT

void CheckEventCut(const char*);
void CheckEventCut();

void CheckEventCut(){
  TCanvas *c1 = new TCanvas("c1","c1",2400,600);
  c1->Divide(2,1);

  Int_t nbcm = vBCM.size();
  Int_t nsam = vSAM.size();
  
  for(int ibcm=0;ibcm<nbcm;ibcm++){
    
    c1->cd(ibcm%2+1);
    CheckEventCut(vBCM[ibcm]);

    if(ibcm%2==1){
      plot_title = Form("run%d_eventcut_%s_%s.png",
			run_number,
			vBCM[ibcm-1],vBCM[ibcm]);
      TText *t1 = new TText(0.0,0.007,plot_title);
      t1->SetNDC();
      t1->SetTextSize(0.05);
      c1->cd();
      t1->Draw("same");
      c1->SaveAs(output_path+ plot_title);
      c1->Clear("D");
    } // end of plot title block
  } // end of BCM loop

    
  for(int isam=0;isam<nsam;isam++){
    
    c1->cd(isam%2+1);
    CheckEventCut(vSAM[isam]);

    if(isam%2==1){
      plot_title = Form("run%d_event_%s_%s.png",
			run_number,
			vSAM[isam-1],vSAM[isam]);
      TText *t1 = new TText(0.0,0.007,plot_title);
      t1->SetNDC();
      t1->SetTextSize(0.05);
      c1->cd();
      t1->Draw("same");
      c1->SaveAs(output_path+ plot_title);
      c1->Clear("D");
    } // end of plot title block
  } // end of SAM loop

  
  // gSystem->Exec(Form("convert $(ls -rt %s*EventCut*.png) %srun%d_bcm_eventcut.pdf",
  // 		     output_path.Data(),output_path.Data(),run_number));
  // gSystem->Exec(Form("rm %s*EventCut*.png",output_path.Data()));

}

void CheckEventCut(const char* device_name){

  gStyle->SetOptStat(1);
  gStyle->SetStatW(0.3);
  gStyle->SetStatH(0.4);

  TTree *evt = (TTree*)gROOT->FindObject("evt");
  
  TPad *pad1 = new TPad("pad1","pad1",0.0,0.0,1.0,1.0);
  pad1->Draw();
  pad1->Divide(2,1);
  TH1D *h_buff;
  TVirtualPad* pad_buff;
  TGraph* g_buff;

  pad_buff = pad1->cd(1);
  evt->Draw(Form("%s:Entry$",device_name),"","l");
  g_buff = (TGraph*)pad_buff->FindObject("Graph");
  g_buff->SetName("GraphAll");
  evt->Draw(Form("%s:Entry$",device_name),"ErrorFlag!=0","* same");
  g_buff = (TGraph*)pad_buff->FindObject("Graph");
  g_buff->SetMarkerColor(kRed);

  pad_buff=pad1->cd(2);
  evt->Draw(Form("%s",device_name),"ErrorFlag==0","");
  h_buff=(TH1D*)pad_buff->FindObject("htemp");
  h_buff->SetName("EvtTree");
    
  evt->Draw(Form("%s",device_name),
	    Form("ErrorFlag==0 && %s.Device_Error_Code!=0",device_name),
	    "same");
  h_buff=(TH1D*)pad_buff->FindObject("htemp");
  if(h_buff!=0)
    h_buff->SetLineColor(kRed);
}


#endif
