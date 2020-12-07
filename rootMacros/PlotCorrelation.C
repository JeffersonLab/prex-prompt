// PlotCorrelation.C : 
//	ROOT script for multiple 2D correlation plots in matrix form
//
// author : Tao Ye <tao.ye@stonybrook.edu>
// 	 05-2019

#include "device_list.h"

void PlotCorrelation(vector<const char*> &DVar, vector<const char*> &IVar,
		     TString treeName, 
		     TString prefix1, TString prefix2,
		     TString draw_opt,
		     TString user_cut);  // Generic

void PlotCorrelation(Int_t magic_switch, 
		     TString treeName, TString draw_opt); // interface to panguin

void PlotCorrelation(); // interface to summary plots

void PlotCorrelation(){

  TString treeNames[] = {"pr","mul"};
  TString treeName;
  TString draw_opts[] = {"COLZ","fit","scat"};
  Int_t nsam = vSAM.size();
  Int_t nbpm = vDitherBPM.size();
  Int_t nDV[3]={nsam,nsam,nbpm};
  Int_t nIV[3]={nsam,nbpm,nbpm};
  vector<const char* > vtag_dv ={"asym_sam","asym_sam","diff_bpm" };
  vector<const char*> vtag_iv ={"asym_sam","diff_bpm","diff_bpm" };
  vector<int> switch_key = {2,1,3};
  Int_t canvas_width = 600;
  TCanvas* c_this = new TCanvas("","",800,800);
  for(int itree=0;itree<2;itree++){
    for(int iplot=0;iplot<3;iplot++){
      for(int iopt=0;iopt<3;iopt++){
	int ny = nDV[iplot];
	int nx = nIV[iplot];
	c_this->SetWindowSize((nx+1)*canvas_width,ny*canvas_width);
	c_this->cd();
	PlotCorrelation(switch_key[iplot],treeNames[itree],draw_opts[iopt]);
	plot_title  = Form("run%d_%s_vs_%s-%s-%sTree.png",
			   run_number,vtag_dv[iplot],vtag_iv[iplot],
			   draw_opts[iopt].Data(),treeNames[itree].Data() );
	TText *label = new TText(0.0,0.005,plot_title);     
	label->SetTextFont(23);
	label->SetTextSize(70);
	label->SetNDC();
	c_this->cd();
	label->Draw("same");
	c_this->SaveAs(output_path+plot_title);
	c_this->Clear("D");
      } // end of draw_opts loop
      gSystem->Exec(Form("convert %s/*%sTree.png %s/run%d_%s_vs_%s_%sTree.pdf",
			 output_path.Data(),treeNames[itree].Data(),
			 output_path.Data(),
			 run_number,vtag_dv[iplot],vtag_iv[iplot],
			 treeNames[itree].Data()));
      gSystem->Exec(Form("rm %s/*_vs_*.png",output_path.Data()));
    } // end of plots loop
  } // end of tree loop
}

void PlotCorrelation(Int_t magic_switch, 
		     TString treeName, TString draw_opt){

  switch(magic_switch){
  case 1:
    PlotCorrelation(vSAM,vDitherBPM,
		    treeName,
		    "asym_","diff_",
		    draw_opt,
		    "ErrorFlag==0");
    break;
  case 2:
    PlotCorrelation(vSAM,vSAM,
		    treeName,
		    "asym_","asym_",
		    draw_opt,
		    "ErrorFlag==0");
    break;
  case 3:
    PlotCorrelation(vDitherBPM,vDitherBPM,
		    treeName,
		    "diff_","diff_",
		    draw_opt,
		    "ErrorFlag==0");
    break;
  
  }
}

void PlotCorrelation(vector<const char* > &DVar_src, vector<const char*> &IVar_src,
		     TString treeName, 
		     TString prefix_dv, TString prefix_iv,
		     TString draw_opt,
		     TString user_cut){
  // gStyle->SetStatW(0.2);
  // gStyle->SetStatH(0.2);
  // gStyle->SetStatX(1);
  // gStyle->SetStatY(1);
  Int_t optFit = gStyle->GetOptFit();
  Int_t optStat = gStyle->GetOptStat();
  if (draw_opt=="fit") {
    gStyle->SetOptFit(1);
    gStyle->SetOptStat(0);
  }
  
  Int_t nDVar = DVar_src.size();
  Int_t nIVar = IVar_src.size();

  vector<TString> DVar;  
  vector<TString> IVar;

  for(int i=0; i<nDVar;i++){
    TString buff = TString(DVar_src[i]);
    if (((TString)DVar_src[i]).Contains("sam_")) {
      buff = "mulc.asym_"+buff;
    }
    else {
      buff = prefix_dv+buff;
    }
    DVar.push_back(buff);
  }
  for(int i=0; i<nIVar;i++){
    TString buff = TString(IVar_src[i]);
    if (((TString)IVar_src[i]).Contains("sam_")) {
      buff = "mulc.asym_"+buff;
    }
    else {
      buff = prefix_iv+buff;
    }
    IVar.push_back(buff);
  }

  TTree *tree = (TTree*)gROOT ->FindObject(treeName);
  TString cuts = user_cut;

  TPad* pad1 = new TPad("pad1","pad1",0,0,1,1);
  pad1->Divide(nIVar+1, nDVar);
  pad1->Draw();
  TVirtualPad *pad_buff;
  TH1D* h_buff;
  TGraph* g_corr_buff;

  vector<double> iv_mean;
  vector<double> iv_rms;
  vector<double> dv_mean;
  vector<double> dv_rms;
  
  for(int i=0;i<nDVar;i++){
    tree->Draw(Form("%s>>hdv%d",DVar[i].Data(),i),cuts,"goff");
    TH1D *hbuff = (TH1D*)gDirectory->FindObject(Form("hdv%d",i));
    if(hbuff!=NULL){
      dv_mean.push_back( hbuff->GetMean());
      dv_rms.push_back( hbuff->GetRMS() );
    }
    else{
      DVar.erase(DVar.begin()+i);
      i--;
    }
  }
  nDVar = DVar.size();
  
  for(int i=0;i<nIVar;i++){
    tree->Draw(Form("%s>>hiv%d",IVar[i].Data(),i),cuts,"goff");
    TH1D *hbuff = (TH1D*)gDirectory->FindObject(Form("hiv%d",i));
    if(hbuff!=NULL){
      iv_mean.push_back( hbuff->GetMean());
      iv_rms.push_back( hbuff->GetRMS());
    }
    else{
      IVar.erase(IVar.begin()+i);
      i--;
    }
  }
  nIVar = IVar.size();

  vector<TText * > dv_txt;
  vector<TText * > iv_txt;

  // Rows
  for(int i=0;i<nDVar;i++){
    TText *txt = new TText(0.0,0.4, DVar[i]);
    txt->SetTextFont(22);
    txt->SetTextSize(0.15);
    dv_txt.push_back(txt);
  }

  // Columns
  for(int i=0;i<nIVar;i++){
    TString tmpTxt = IVar[i];
    if (tmpTxt.Contains("mulc.")) {
      tmpTxt = tmpTxt(5,tmpTxt.Length()-5);
    }
    TText *txt = new TText(0.0,0.92, tmpTxt);
    txt->SetTextFont(22);
    txt->SetTextSize(0.10);
    txt->SetNDC();
    iv_txt.push_back(txt);
  }

  for(int irow=0;irow<nDVar; irow++){
    pad1->cd(1 + irow*(nIVar+1));
    dv_txt[irow]->Draw();
    for(int icol=0; icol< nIVar; icol++){
      pad_buff =pad1->cd(icol+2+irow*(nIVar+1));
      if(draw_opt=="scat"){
	tree->Draw(Form("%s:%s",
			DVar[irow].Data(),IVar[icol].Data()),
		   cuts);
	h_buff = (TH1D*)pad_buff->FindObject("htemp");
	if(h_buff!=NULL)
	  h_buff->SetTitle("");
      }
      else if(draw_opt=="fit"){
	tree->Draw(Form("%s:%s",
			DVar[irow].Data(),IVar[icol].Data()),
        cuts,"l");
  TLatex *cor;
	g_corr_buff = (TGraph*)pad_buff->FindObject("Graph");
  if (g_corr_buff) {
    cor = new TLatex(0,0,Form("Cor factor = %0.4f",g_corr_buff->GetCorrelationFactor()));
    cor->SetTextFont(42);
    cor->SetTextSize(0.035);
    if (abs(g_corr_buff->GetCorrelationFactor())>0.95) {
      cor->SetTextColor(kRed);
    }
  }
  delete g_corr_buff;
	tree->Draw(Form("%s:%s",
			DVar[irow].Data(),IVar[icol].Data()),
		   cuts,"prof");
	h_buff = (TH1D*)pad_buff->FindObject("htemp");
	if(h_buff!=NULL){
	  h_buff->SetTitle("");
	  h_buff->Fit("pol1","QR","",
		    iv_mean[icol]-2*iv_rms[icol],
		    iv_mean[icol]+2*iv_rms[icol]);
	  pad_buff->Update();
	  TF1 *f1 = h_buff->GetFunction("pol1");
	  if (f1!=NULL){
	    Double_t slope = f1->GetParameter(1);
	    //TPaveStats* st = (TPaveStats*)h_buff->FindObject("stats");
	    TPaveStats* lst = (TPaveStats*)pad_buff->GetPrimitive("stats");
      lst->SetName("MyStats");
	    lst->SetOptFit(1);
	    lst->SetOptStat(0);
	    if(slope<0){
	      lst->SetX2NDC(1.0);
	      lst->SetY2NDC(0.9);
	      lst->SetX1NDC(0.5);
	      lst->SetY1NDC(0.6);
	    }
	    else{
	      lst->SetX2NDC(0.5);
	      lst->SetY2NDC(0.6);
	      lst->SetX1NDC(0.0);
	      lst->SetY1NDC(0.9);
	    }
      if (cor) {
        if (DVar[irow] != IVar[icol]) {
          lst->GetListOfLines()->Add(cor);
          h_buff->SetStats(0);
          pad_buff->Modified();
        }
      }
      lst->Draw();
      // delete lst;
	  } // end of if f1!=NULL
	}// end of if h_buff!=NULL
      }
      else{
	tree->Draw(Form("%s:%s",
			DVar[irow].Data(),IVar[icol].Data()),
		   cuts,draw_opt);
	h_buff = (TH1D*)pad_buff->FindObject("htemp");
	if (h_buff!=NULL)
	  h_buff->SetTitle("");
      }

      iv_txt[icol]->Draw("same");
    }
  }
  gStyle->SetOptFit(optFit);
  gStyle->SetOptStat(optStat);
}
