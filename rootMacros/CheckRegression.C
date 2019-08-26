// CheckRegression.C : 
//	ROOT script for LRB regression plots
//
//  author: Tao Ye 
//  	06-2019

#include "device_list.h"
void CheckRegression(vector<TString> DVar, vector<TString> IVar,
		     TString draw_opt,
		     TString user_cut);  // Generic
void CheckRegression();

void CheckVariables(vector<TString> &inputDV, vector<TString> lrbDV); // Check if input DV match lrbDV
vector<TString> FormCorrectionVector(vector<TString> inputDV);

void CheckRegression(){

  // Get DV and IV list from slope files
  TString run_dot_seg = run_seg;
  run_dot_seg = run_dot_seg.ReplaceAll('_','.'); 

  TString slopefile_name = Form("./LRBoutput/blueR%snew.slope.root",run_dot_seg.Data());
  TFile* slopefile = TFile::Open(slopefile_name);
  
  if(slopefile==NULL){
    cout << " Error: "
	 << " blueR slope rootfile " << slopefile_name
	 << " doesn't exist " << endl;
    return;
  }
  
  TH1D* hist_iv = (TH1D*)slopefile->Get("IVname");
  TH1D* hist_dv = (TH1D*)slopefile->Get("DVname");

  if(hist_iv==NULL || hist_dv==NULL){
    cout << " Error: "
	 << " DV or IV list is not found " << endl;
    return;
  }

  vector< TString > IVlist;
  vector< TString > DVlist;
  
  TAxis *ivAxis = hist_iv->GetXaxis();
  TAxis *dvAxis = hist_dv->GetXaxis();
  
  Int_t nIV_lrb = ivAxis->GetLast(); // " returns fNBins if range not specified "
  Int_t nDV_lrb = dvAxis->GetLast();

  if(nIV_lrb==0 || nDV_lrb==0){
    cout << " Error: "
	 << " DV or IV list is empty " << endl;
    return;
  }

  for(int i=0;i<nIV_lrb;i++){
    const char* c_buff = ivAxis->GetBinLabel(i+1);
    IVlist.push_back(TString(c_buff));
  }

  for(int i=0;i<nDV_lrb;i++){
    const char* c_buff = dvAxis->GetBinLabel(i+1);
    DVlist.push_back(TString(c_buff));
  }
  
  slopefile->Close();

  japanOutput->cd();
  // 
  TString blueRCut = "ErrorFlag==0";
  for(int i=0;i<nDV_lrb;i++){
    blueRCut +=Form("&& %s.Device_Error_Code==0",DVlist[i].Data());
  }
  for(int i=0;i<nIV_lrb;i++){
    blueRCut +=Form("&& %s.Device_Error_Code==0",IVlist[i].Data());
  }

  TString draw_opts[] = {"COLZ","fit","scat"};

  vector<TString> vSAMU = {"asym_sam2","asym_sam4","asym_sam6","asym_sam8"};
  vector<TString> vSAMV = {"asym_sam1","asym_sam3","asym_sam5","asym_sam7"};
  vector<TString> vMain = {"asym_usl","asym_dsl","asym_usr","asym_dsr"};

  // then check if they exist in LRB DVlist, otherwise erase them from plot queue
  CheckVariables(vMain, DVlist);
  CheckVariables(vSAMU, DVlist);
  CheckVariables(vSAMV, DVlist);

  vector<vector<TString> > vDV_plot ={vSAMU,
				      vSAMV,
				      vMain};
  Int_t nplots = vDV_plot.size();

  vector<TString> vtag_dv ={"asym_sam2468",
			    "asym_sam1357",
			    "asym_maindet"};

  TCanvas* c_this = new TCanvas("","",2400,2400);
  for(int iplot=0;iplot<nplots;iplot++){
    for(int iopt=0;iopt<3;iopt++){
      int ny = vDV_plot[iplot].size();
      if(ny==0)
	continue;
      int nx = nIV_lrb;
      Int_t can_width = 2400/(nx+1);
      c_this->SetCanvasSize(2400,can_width*ny);

      c_this->cd();
      CheckRegression(vDV_plot[iplot],IVlist,
  		      draw_opts[iopt],
  		      blueRCut);
      plot_title  = Form("run%s_regression_%s_vs_%s-%s.png",
  			 run_seg.Data(),
			 vtag_dv[iplot].Data(),"diff_bpm",
  			 draw_opts[iopt].Data());
      TText *label = new TText(0.0,0.005,plot_title);     
      label->SetTextFont(23);
      label->SetTextSize(70);
      label->SetNDC();
      c_this->cd();
      label->Draw("same");
      c_this->SaveAs(output_path+plot_title);
      c_this->Clear("D");

      vector<TString> vDV_corr = FormCorrectionVector(vDV_plot[iplot]);
      c_this->cd();
      TString correction_tag = vtag_dv[iplot];

      Ssiz_t pos = correction_tag.First('_');
      Ssiz_t length = correction_tag.Length();
      correction_tag = (correction_tag)(pos,length-pos+1);
      correction_tag = "cor"+correction_tag;

      CheckRegression(vDV_corr,IVlist,
  		      draw_opts[iopt],
  		      blueRCut);
      plot_title  = Form("run%s_regression_%s_vs_%s-%s.png",
  			 run_seg.Data(),
			 correction_tag.Data(),"diff_bpm",
  			 draw_opts[iopt].Data());
      label = new TText(0.0,0.005,plot_title);     
      label->SetTextFont(23);
      label->SetTextSize(70);
      label->SetNDC();
      c_this->cd();
      label->Draw("same");
      c_this->SaveAs(output_path+plot_title);
      c_this->Clear("D");

    } // end of draw_opts loop
  } // end of plots loop
  gSystem->Exec(Form("convert $(ls -rt %s/*regression*sam*.png) %s/run%s_summary_regression_sam.pdf",
		     output_path.Data(),
		     output_path.Data(),
		     run_seg.Data()));
  gSystem->Exec(Form("convert $(ls -rt %s/*regression*maindet*.png) %s/run%s_summary_regression_maindet.pdf",
		     output_path.Data(),
		     output_path.Data(),
		     run_seg.Data()));
  gSystem->Exec(Form("rm %s/*regression*_vs_*.png",output_path.Data()));

}


void CheckRegression(vector<TString > DVar, vector<TString> IVar,
		     TString draw_opt,
		     TString custom_cut){
  // gStyle->SetStatW(0.2);
  // gStyle->SetStatH(0.2);
  // gStyle->SetStatX(1);
  // gStyle->SetStatY(1);

  Int_t nDVar = DVar.size();
  Int_t nIVar = IVar.size();

  TTree *mul_tree = (TTree*)gROOT ->FindObject("mul");
  TTree *mulc_tree = (TTree*)gROOT ->FindObject("mulc_lrb");
  mul_tree->AddFriend(mulc_tree);

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
    mul_tree->Draw(Form("%s/ppm>>hdv%d_lrb",DVar[i].Data(),i),
		   custom_cut,
		   "goff");
    TH1D *hbuff = (TH1D*)gDirectory->FindObject(Form("hdv%d_lrb",i));
    dv_mean.push_back( hbuff->GetMean());
    dv_rms.push_back( hbuff->GetRMS() );
  }

  for(int i=0;i<nIVar;i++){
    mul_tree->Draw(Form("%s/um>>hiv%d_lrb",IVar[i].Data(),i),
		   custom_cut,
		   "goff");
    TH1D *hbuff = (TH1D*)gDirectory->FindObject(Form("hiv%d_lrb",i));
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

      if(draw_opt=="scat"){
	mul_tree->Draw(Form("%s/ppm:%s/um",
			    DVar[irow].Data(),IVar[icol].Data()),
		       custom_cut);
	h_buff = (TH1D*)pad_buff->FindObject("htemp");
	if (h_buff!=NULL)
	  h_buff->SetTitle("");
      }
      else if(draw_opt=="fit"){
	mul_tree->Draw(Form("%s/ppm:%s/um",
			    DVar[irow].Data(),IVar[icol].Data()),
		       custom_cut,"prof");
	h_buff = (TH1D*)pad_buff->FindObject("htemp");
	if (h_buff!=NULL){
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
      }
      else{
	mul_tree->Draw(Form("%s/ppm:%s/um",
			    DVar[irow].Data(),IVar[icol].Data()),
		   custom_cut,draw_opt);
	h_buff = (TH1D*)pad_buff->FindObject("htemp");
	if (h_buff!=NULL)
	  h_buff->SetTitle("");
      }

      iv_txt[icol]->Draw("same");
    }
  }
}


void CheckVariables(vector<TString> &inputDV, vector<TString> lrbDV){

  vector<TString>::iterator it_input = inputDV.begin();
  int nDV_lrb = lrbDV.size();

  while(it_input!= inputDV.end()){
    Bool_t kFound = kFALSE;
    
    for(int i=0;i<nDV_lrb;i++){
      int cmp_result = (*it_input).CompareTo(lrbDV[i]);
      if(cmp_result==0){
	kFound = kTRUE;
	break;
      }
    }

    if(!kFound){
      cout << "-- Warning: "
	   << *it_input << " is not found in LRB DV list." << endl;
      it_input = inputDV.erase(it_input);
      continue;
    }

    it_input++;
  }

}

vector<TString> FormCorrectionVector(vector<TString> inputDV){
  
  vector<TString> vRet;
  vector<TString>::iterator it_input = inputDV.begin();
  
  while(it_input != inputDV.end() ){
    Ssiz_t pos = (*it_input).First('_');
    Ssiz_t length = (*it_input).Length();
    TString str_buff = (*it_input)(pos,length-pos+1);
    str_buff = "cor"+str_buff;
    vRet.push_back(str_buff);
    it_input++;
  }
  return vRet;
}
