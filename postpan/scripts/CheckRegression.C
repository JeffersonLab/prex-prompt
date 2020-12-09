// CheckRegression.C : 
//	ROOT script for LRB regression plots
//
//  author: Tao Ye 
//  	06-2019

#include "device_list.h"
void CheckRegression(vector<const char*> &DVar, vector<const char*> &IVar,
		     TString draw_opt,
		     TString user_cut);  // Generic
void CheckRegression();


void CheckRegression(){

  TString draw_opts[] = {"COLZ","fit","scat"};

  vector<const char*> vSAM_raw = {"asym_sam2","asym_sam4","asym_sam6","asym_sam8"};
  vector<const char*> vSAM_corr = {"cor_sam2","cor_sam4","cor_sam6","cor_sam8"};
  vector<const char*> vDiffBPM = {"diff_bpm4aX","diff_bpm4aY",
				  "diff_bpm4eX","diff_bpm4eY",
				  "diff_bpm14X"};

  vector<vector<const char*> > vDV ={vSAM_raw,vSAM_corr};
  vector<vector<const char*> > vIV ={vDiffBPM,vDiffBPM};
  Int_t nplots = vDV.size();

  Int_t nsam = vSAM_raw.size();
  Int_t nbpm = vDiffBPM.size();

  Int_t nDV[]={nsam,nsam};
  Int_t nIV[]={nsam,nbpm};

  vector<const char* > vtag_dv ={"asym_sam","corr_sam"};
  vector<const char*> vtag_iv ={"diff_bpm","diff_bpm"};

  TCanvas* c_this = new TCanvas("","",2400,2400);
  for(int iplot=0;iplot<nplots;iplot++){
    for(int iopt=0;iopt<3;iopt++){
      int ny = nDV[iplot];
      int nx = nIV[iplot];
      Int_t can_width = 2400/(nx+1);
      c_this->SetCanvasSize(2400,can_width*ny);

      c_this->cd();

      CheckRegression(vDV[iplot],vIV[iplot],
  		      draw_opts[iopt],
  		      "ErrorFlag==0");

      plot_title  = Form("run%d_regression_%s_vs_%s-%s.png",
  			 run_number,vtag_dv[iplot],vtag_iv[iplot],
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
  } // end of plots loop
  gSystem->Exec(Form("convert $(ls -rt %s/*regression*.png) %s/run%d_summary_regression.pdf",
		     output_path.Data(),
		     output_path.Data(),
		     run_number));
  gSystem->Exec(Form("rm %s/*regression*_vs_*.png",output_path.Data()));

}


void CheckRegression(vector<const char* > &DVar, vector<const char*> &IVar,
		     TString draw_opt,
		     TString user_cut){
  // gStyle->SetStatW(0.2);
  // gStyle->SetStatH(0.2);
  // gStyle->SetStatX(1);
  // gStyle->SetStatY(1);
  
  Int_t nDVar = DVar.size();
  Int_t nIVar = IVar.size();

  TTree *mul_tree = (TTree*)gROOT ->FindObject("mul");
  TTree *mulc_tree = (TTree*)gROOT ->FindObject("mulc_lrb");
  mul_tree->AddFriend(mulc_tree);

  TString cuts = user_cut;

  TPad* pad1 = new TPad("pad1","pad1",0,0,1,1);
  pad1->Divide(nIVar+1, nDVar);
  pad1->Draw();
  TVirtualPad *pad_buff;
  TH1D* h_buff;

  vector<double> iv_mean;
  vector<double> iv_rms;
  vector<double> dv_mean;
  vector<double> dv_rms;
  
  for(int i=0;i<nDVar;i++){
    mul_tree->Draw(Form("%s>>hdv%d",DVar[i],i),
	       cuts+Form("&& %s.Device_Error_Code==0",DVar[i]),
	       "goff");
    TH1D *hbuff = (TH1D*)gDirectory->FindObject(Form("hdv%d",i));
    dv_mean.push_back( hbuff->GetMean());
    dv_rms.push_back( hbuff->GetRMS() );
  }

  for(int i=0;i<nIVar;i++){
    mul_tree->Draw(Form("%s>>hiv%d",IVar[i],i),
	       cuts+Form("&& %s.Device_Error_Code==0",IVar[i]),
	       "goff");
    TH1D *hbuff = (TH1D*)gDirectory->FindObject(Form("hiv%d",i));
    iv_mean.push_back( hbuff->GetMean());
    iv_rms.push_back( hbuff->GetRMS());
  }

  vector<TText * > dv_txt;
  vector<TText * > iv_txt;

  for(int i=0;i<nDVar;i++){
    TText *txt = new TText(0.0,0.4, DVar[i]);
    txt->SetTextFont(22);
    txt->SetTextSize(0.15);
    dv_txt.push_back(txt);
  }

  for(int i=0;i<nIVar;i++){
    TText *txt = new TText(0.0,0.90, IVar[i]);
    txt->SetTextFont(22);
    txt->SetTextSize(0.15);
    txt->SetNDC();
    iv_txt.push_back(txt);
  }

  for(int irow=0;irow<nDVar; irow++){
    pad1->cd(1 + irow*(nIVar+1));
    dv_txt[irow]->Draw();
    for(int icol=0; icol< nIVar; icol++){
      pad_buff =pad1->cd(icol+2+irow*(nIVar+1));
      TString device_error_cut = Form("&& %s.Device_Error_Code==0 && %s.Device_Error_Code==0",
				      IVar[icol],DVar[irow]);
      if(draw_opt=="scat"){
	mul_tree->Draw(Form("%s:%s",
			DVar[irow],IVar[icol]),
		   cuts+device_error_cut);
	h_buff = (TH1D*)pad_buff->FindObject("htemp");
	h_buff->SetTitle("");
      }
      else if(draw_opt=="fit"){
	mul_tree->Draw(Form("%s:%s",
			     DVar[irow],IVar[icol]),
			cuts+device_error_cut,"prof");
	h_buff = (TH1D*)pad_buff->FindObject("htemp");
	h_buff->SetTitle("");
	h_buff->Fit("pol1","QR","",
		    iv_mean[icol]-2*iv_rms[icol],
		    iv_mean[icol]+2*iv_rms[icol]);
	pad_buff->Update();
	TF1 *f1 = h_buff->GetFunction("pol1");
	Double_t slope = f1->GetParameter(1);
	TPaveStats* st = (TPaveStats*)h_buff->FindObject("stats");
	st->SetOptFit(1);
	st->SetOptStat(0);
	if(slope<0){
	  st->SetX2NDC(1.0);
	  st->SetY2NDC(0.9);
	  st->SetX1NDC(0.5);
	  st->SetY1NDC(0.6);
	}
	else{
	  st->SetX2NDC(0.5);
	  st->SetY2NDC(0.6);
	  st->SetX1NDC(0.0);
	  st->SetY1NDC(0.9);
	}
      }
      else{
	mul_tree->Draw(Form("%s:%s",
			DVar[irow],IVar[icol]),
		   cuts,draw_opt);
	h_buff = (TH1D*)pad_buff->FindObject("htemp");
	h_buff->SetTitle("");
      }

      iv_txt[icol]->Draw("same");
    }
  }
}
