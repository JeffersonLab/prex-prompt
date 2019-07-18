#include "device_list.h"

void PlotPairTree();
void PlotPairTree(TString device_name);

void PlotPairTree( vector< const char*> device_array){
  TCanvas *c1 = new TCanvas("c1","c1",2400,600);
  
  Int_t ndevice = device_array.size();
  for(int idev=0;idev<ndevice;idev++){
    TString device1 = device_array[idev];
    PlotPairTree(device1);
    plot_title = Form("run%s_pairTree_%s.png",
		      run_seg.Data(),
		      device1.Data());
  
    TText *t1 = new TText(0.0,0.007,plot_title);
    t1->SetNDC();
    t1->SetTextSize(0.05);
    c1->cd();
    t1->Draw("same");
    c1->SaveAs(output_path+plot_title);
    c1->Clear("D");
  }
}
void PlotPairTree(TString device_name){
  gStyle->SetStatW(0.3);
  gStyle->SetStatH(0.4);

  TTree *pair_tree = (TTree*)gROOT->FindObject("pr");
  TPad *pad1 = new TPad("pad1","pad1",0,0,1,1);
  TH1D* h_buff;
  TVirtualPad *pad_buff;
  TString unit_str="";
  if(device_name.Contains("bpm"))
    unit_str = "/mm";

  TString prefix_str="";

  pad1->Divide(4,1);
  pad1->Draw();
  pad_buff = pad1->cd(1);
  pair_tree->Draw(Form("yield_%s%s:pattern_number",
		       device_name.Data(),
		       unit_str.Data()),
		  "ErrorFlag==0");
  pad_buff = pad1->cd(2);
  pair_tree->Draw(Form("yield_%s%s",
		       device_name.Data(),
		       unit_str.Data()),
		  "ErrorFlag==0");

  if(device_name.Contains("bpm")){
    unit_str = "/um";
    prefix_str = "diff_";
  }
  else{
    unit_str = "/ppm";
    prefix_str = "asym_";
  }
  pad_buff = pad1->cd(3);
  pair_tree->Draw(Form("%s%s%s:pattern_number",
		       prefix_str.Data(),
		       device_name.Data(),
		       unit_str.Data()),
		  "ErrorFlag==0","COL");
  TH2F* h2d_buff = (TH2F*)pad_buff->FindObject("htemp");
  if (h2d_buff!=NULL)
    h2d_buff->Draw("candlex3");

  pad_buff = pad1->cd(4);
  pair_tree->Draw(prefix_str+device_name+unit_str,
		  "ErrorFlag==0");
  h_buff=(TH1D*)pad_buff->FindObject("htemp");
  if(h_buff!=NULL)
    h_buff->SetName("PairTree");
  
}
