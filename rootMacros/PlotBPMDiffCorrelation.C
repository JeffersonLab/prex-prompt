// CheckDiffCorrelation.C : 
//	ROOT script for diff_bpm correlation
//
// author : Tao Ye <tao.ye@stonybrook.edu>
// 	 05-2019

#include "device_list.h"

void PlotBPMDiffCorrelation(){
  
  TTree *mul_tree = (TTree*)gROOT->FindObject("mul");
  TTree *mulc_tree = (TTree*)gROOT->FindObject("mulc");
  mul_tree->AddFriend(mulc_tree);
  TString draw_opts[] = {"COLZ","fit","scat"};

  vector<const char*> vDBPMnames;
  vDBPMnames.push_back("default");
  vector<const char*> vIBPM={
    "bpm4aX","bpm4aY",
    "bpm4eX","bpm4eY",
    "bpm12X"
  };
  vDBPMnames.push_back("upstream");
  vector<const char*> vBPM1 =  {
    "bpm1p02bX","bpm1p03aX",
    "bpm1X","bpm1Y"
  };
  vDBPMnames.push_back("ArcA");
  vector<const char*> vBPM2 = {
    "bpm11X",
    "bpm16X",
    "bpmE_11X12X"
  };
  vDBPMnames.push_back("sam_dds");
  vector<const char*> vBPM3 = {
    "sam_15_dd",
    "sam_37_dd",
    "sam_26_dd",
    "sam_48_dd",
  };
  vDBPMnames.push_back("sam_avgs");
  vector<const char*> vBPM4 =  {
    "sam_15_avg",
    "sam_37_avg",
    "sam_26_avg",
    "sam_48_avg",
  };
  vDBPMnames.push_back("sam_cross_dds");
  vector<const char*> vBPM5 =  {
    "sam_15_37_dd",
    "sam_13_57_dd",
    "sam_26_48_dd",
    "sam_24_68_dd",
  };
  vDBPMnames.push_back("sam_combos");
  vector<const char*> vBPM6 =  {
    "sam_1357_avg",
    "sam_2468_avg",
    "sam_1357_2468_dd",
    "sam_12345678_avg",
  };
  vector<vector<const char*>> vDBPM;
  vDBPM.push_back(vIBPM);
  vDBPM.push_back(vBPM1);
  vDBPM.push_back(vBPM2);
  vDBPM.push_back(vBPM3);
  vDBPM.push_back(vBPM4);
  vDBPM.push_back(vBPM5);
  vDBPM.push_back(vBPM6);

  Int_t nbpmX = vIBPM.size();

  for (int index = 0 ; index<vDBPM.size(); index++){
  for(int iopt=0;iopt<3;iopt++){
    TCanvas* c_this = new TCanvas("c1","c1",2400,2400);
    Int_t nbpmY = vDBPM.at(index).size();
    c_this->Divide(nbpmX,nbpmY);
    Int_t can_width = 2400/nbpmX;
    c_this->cd();
    PlotCorrelation(vIBPM,vDBPM.at(index),
		    "mul",
		    "diff_","diff_",
		    draw_opts[iopt],
		    "ErrorFlag==0");

    
    plot_title  = Form("run%s_diff_bpm_mutual_correlation_%s_%s.png",
        run_seg.Data(),draw_opts[iopt].Data(),vDBPMnames.at(index));
    TText *label = new TText(0.0,0.005,plot_title);     
    label->SetTextFont(23);
    label->SetTextSize(70);
    label->SetNDC();
    c_this->cd();
    label->Draw("same");
    c_this->SaveAs(output_path+plot_title);
    c_this->Clear("D");
    delete label;
    delete c_this;
  }
}
}
