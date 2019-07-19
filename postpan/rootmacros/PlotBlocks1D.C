#include "device_list.h"
void PlotBlocks1D(const char* device_name ,TString treeName);
void PlotBlocks1D();

void PlotBlocks1D(){
  TCanvas *c2 = new TCanvas("c2","c2",1600,1600);

  Int_t nblkm = vBlkM.size();  
  TString treeNames[] = {"pr","mul"};
  TString treeName;
  ////========== 1D Blocks plots
  for(int iTree = 0; iTree<2 ; iTree++){
    treeName = treeNames[iTree];
    for(int idev=0;idev<nblkm;idev++){
      c2->Clear("D");
      c2->cd();
      PlotBlocks1D(vBlkM[idev],treeName);
      plot_title = Form("run%d_%s_SubBlocks1D_%sTree.png",
			run_number,vBlkM[idev],
			treeName.Data());
      TText *t1 = new TText(0.0,0.007,plot_title);
      t1->SetNDC();
      t1->SetTextSize(0.02);
      c2->cd();
      t1->Draw("same");
      c2->SaveAs(output_path+plot_title);
    } // end of device loop
  }// end of tree loop
}

void PlotBlocks1D(const char* device_name ,TString treeName){

  TString draw_opt = "COLZ";
  TTree *tree = (TTree*)gROOT->FindObject(treeName);

  TPad* pad1 = new TPad("pad1","pad1",0.0,0.0,1.0,1.0);
  pad1->Divide(2,2);
  pad1->Draw();

  const char *leaf[]={"block0","block1","block2","block3"};

  TVirtualPad* pad_buff;
  TH1* h_buff;
  TString draw_cmd;

  TPaveText *ptext_buff;

  gStyle->SetStatW(.3);
  gStyle->SetStatH(.4);

  for(int ileaf=0;ileaf<4;ileaf++){
    pad_buff = pad1->cd(ileaf+1);
    draw_cmd = Form("%s.%s",device_name,leaf[ileaf]);
    tree->Draw(draw_cmd.Data(),"ErrorFlag==0");	
    h_buff = (TH1D*)pad_buff->FindObject("htemp");
    h_buff->SetTitle( Form(" %sTree , %s :%s",
			   treeName.Data(),device_name,
			   leaf[ileaf]));
  }

}
