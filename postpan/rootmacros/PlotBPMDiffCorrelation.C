// CheckDiffCorrelation.C : 
//	ROOT script for diff_bpm correlation
//
// author : Tao Ye <tao.ye@stonybrook.edu>
// 	 05-2019

#include "device_list.h"

void PlotBPMDiffCorrelation(){
  
  TTree *mul_tree = (TTree*)gROOT->FindObject("mul");
  TString draw_opts[] = {"COLZ","fit","scat"};
  
  Int_t nbpmXY = vDitherBPM.size();
  TCanvas* c_this = new TCanvas("","",2400,2400);

  c_this->Divide(nbpmXY,nbpmXY);
  for(int iopt=0;iopt<3;iopt++){
    Int_t can_width = 2400/nbpmXY;
    c_this->cd();
    PlotCorrelation(vDitherBPM,vDitherBPM,
		    "mul",
		    "diff_","diff_",
		    draw_opts[iopt],
		    "ErrorFlag==0");
    
    plot_title  = Form("run%s_diff_bpm_mutual_correlation_%s.png",
		       run_seg.Data(),draw_opts[iopt].Data());
    TText *label = new TText(0.0,0.005,plot_title);     
    label->SetTextFont(23);
    label->SetTextSize(70);
    label->SetNDC();
    c_this->cd();
    label->Draw("same");
    c_this->SaveAs(output_path+plot_title);
    c_this->Clear("D");
  }
}
