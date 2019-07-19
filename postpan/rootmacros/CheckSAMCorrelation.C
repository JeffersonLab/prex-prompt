// CheckSAMCorrelation.C : 
//	ROOT script for checking SAM correlation
//
// author : Tao Ye <tao.ye@stonybrook.edu>
// 	 05-2019

#include "device_list.h"
void CheckSAMCorrelation(vector<const char*> SAM_vec, TString stag);
void CheckSAMCorrelation();

void CheckSAMCorrelation(){
  
  CheckSAMCorrelation(vSAM,"asym_sam2468");
  CheckSAMCorrelation(vSAMUnity,"asym_sam1357");

}

void CheckSAMCorrelation(vector<const char*> SAM_vec, TString stag){
  
  TString treeName = "mul";
  TString draw_opts[] = {"COLZ","fit","scat"};

  Int_t nsam = vSAM.size();
  const char* tag =stag.Data();
  TCanvas* c_this = new TCanvas("","",2400,2400);

  for(int iopt=0;iopt<3;iopt++){
    int ny = nsam;
    int nx = nsam;
    Int_t canvas_width = 2400/(nx+1);
    c_this->SetCanvasSize(2400,ny*canvas_width);
    c_this->cd();

    PlotCorrelation(SAM_vec,SAM_vec,
		    treeName,
		    "asym_","asym_",
		    draw_opts[iopt],
		    "ErrorFlag==0");

    plot_title  = Form("run%s_%s_mutual_correlation-%s.png",
		       run_seg.Data(),tag,
		       draw_opts[iopt].Data());
    TText *label = new TText(0.0,0.005,plot_title);     
    label->SetTextFont(23);
    label->SetTextSize(70);
    label->SetNDC();
    c_this->cd();
    label->Draw("same");
    c_this->SaveAs(output_path+plot_title);
    c_this->Clear("D");
  } // end of draw_opts loop

}
