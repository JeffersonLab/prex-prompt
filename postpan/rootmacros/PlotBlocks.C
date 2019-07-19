// author: Tao Ye
// date: 05-2019
// description: Macro for subBlock correlation

#include "device_list.h"

void PlotBlocks(const char* device_name,TString treeName);
void PlotBlocks();

void PlotBlocks(){
  TCanvas *c2 = new TCanvas("c2","c2",1600,1600);

  Int_t nblkm = vBlkM.size();  
  TString treeNames[] = {"pr","mul"};
  TString treeName;
  ////========== 2D plots
  for(int iTree = 0; iTree<2 ; iTree++){
    treeName= treeNames[iTree];
    for(int idev=0;idev<nblkm;idev++){
      c2->Clear("D");
      c2->cd();
      PlotBlocks(vBlkM[idev],treeName);
      plot_title = Form("run%d_%s_SubBlocks_%sTree.png",
			run_number,vBlkM[idev],
			treeName.Data());
      TText *t1 = new TText(0.0,0.007,plot_title);
      t1->SetNDC();
      t1->SetTextSize(0.02);
      c2->cd();
      t1->Draw("same");
      c2->SaveAs(output_path+plot_title);
    } // end of device loop
  }

  TString pdf_filename = Form("run%d_SubBlocks_%sTree.pdf",
			      run_number,treeName.Data());
  gSystem->Exec(Form("convert %srun%d*SubBlock*.png %s%s",
		     output_path.Data(),
		     run_number,
		     output_path.Data(),
		     pdf_filename.Data()));
  gSystem->Exec(Form("rm %srun%d*SubBlock*.png",
		     output_path.Data(),
		     run_number)); 

}

void PlotBlocks(const char* device_name,TString treeName){
  
  TString draw_opt = "COLZ";
  TTree *tree = (TTree*)gROOT->FindObject(treeName);

  TPad* pad1 = new TPad("pad1","pad1",0.0,0.0,1.0,1.0);
  pad1->Divide(4,4);
  pad1->Draw();

  const char *leaf[]={"block0","block1","block2","block3"};

  TVirtualPad* pad_buff;
  TH1* h_buff;
  TString draw_cmd;
  TPaveText *ptext_buff;
  
  for(int ileaf=0;ileaf<4;ileaf++){
    for(int jleaf=0;jleaf<4;jleaf++){
      pad_buff = pad1->cd(jleaf+1+4*ileaf);
      if(ileaf==jleaf)
	continue;

      draw_cmd = Form("%s.%s:%s.%s",
		      device_name,leaf[ileaf],
		      device_name,leaf[jleaf]);
      tree->Draw(draw_cmd,"ErrorFlag==0",draw_opt);
      h_buff = (TH2D*)pad_buff->FindObject("htemp");
      h_buff->SetTitle( Form(" %sTree , %s :%s vs %s",
      			     treeName.Data(),device_name,
      			     leaf[ileaf],leaf[jleaf]));
    } // end of column loop
  } // end of row loop

}
