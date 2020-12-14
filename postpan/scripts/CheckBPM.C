#include <vector>
void PlotRegBPM(Int_t );
void  PlotBPMRawCorrelation(Int_t );
void PlotBPMRawProf(Int_t );
TString bpm_name[]={"4aX","4aY","4eX","4eY","14X","14Y","18X","18Y"};

void CheckBPM(Int_t run_number=1391){

  PlotBPMRawCorrelation(run_number);
  PlotBPMRawProf(run_number);

  // PlotBPMRegCorrelation(run_number);
  // PlotBPMRegProf(run_number);
}

void PlotRegBPM(Int_t run_num){
  gStyle->SetStatW(0.3);
  gStyle->SetStatH(0.3);
  gStyle->SetStatX(0.95);
  gStyle->SetStatY(0.95);

  Int_t nbpm = (sizeof(bpm_name)/sizeof(*bpm_name));
  Int_t can_width = 500;
  TCanvas *c1 = new TCanvas("c1","c1", can_width*(nbpm/2),can_width*2);
  c1->Divide(nbpm/2,2);
  TH1D *h_buff;

  for(int ibpm =0 ;ibpm<nbpm;ibpm++){
    TFile* rootfile = TFile::Open(Form("../ROOTfiles/prexRespin1_%d_%s.root",
				       run_num, bpm_name[ibpm].Data()));
    TTree *reg = (TTree*)rootfile ->Get("reg");
    c1->cd(ibpm+1);

    reg->Draw(Form("1e3*reg_diff_bpm%s>>h%s",bpm_name[ibpm].Data(),
		   bpm_name[ibpm].Data()),"ok_cut");
    h_buff = (TH1D*)gDirectory->FindObject(Form("h%s",bpm_name[ibpm].Data()));
    h_buff->GetXaxis()->SetTitle(" Position Difference (um)");
  }

  c1->SaveAs(Form("run%d_diff_bpm_reg.png",run_num));
}
void PlotRawBPM(Int_t run_num=1391){
  gStyle->SetStatW(0.3);
  gStyle->SetStatH(0.3);
  gStyle->SetStatX(0.95);
  gStyle->SetStatY(0.95);
  TFile* rootfile = TFile::Open(Form("../ROOTfiles/prexRespin1_%d_regress.root",run_num));
  TTree *reg = (TTree*)rootfile ->Get("reg");
  
  Int_t nbpm = (sizeof(bpm_name)/sizeof(*bpm_name));

  Int_t can_width = 500;
  TCanvas *c1 = new TCanvas("c1","c1", can_width*(nbpm/2),can_width*2);
  c1->Divide(nbpm/2,2);
  TH1D *h_buff;
  for(int ibpm =0;ibpm<nbpm;ibpm++){
    c1->cd(ibpm+1);
    reg->Draw(Form("1e3*diff_bpm%s>>h%s",bpm_name[ibpm].Data(),
		   bpm_name[ibpm].Data()),"ok_cut");
    h_buff = (TH1D*)gDirectory->FindObject(Form("h%s",bpm_name[ibpm].Data()));
    h_buff->GetXaxis()->SetTitle(" Position Difference (um)");

  }
  c1->SaveAs(Form("run%d_diff_bpm_raw.png",run_num));
}

void PlotBPMRawProf(Int_t run_num){
  gStyle->SetStatW(0.3);
  gStyle->SetOptFit(1);
  gStyle->SetOptStat(0);
  gStyle->SetStatH(0.3);
  gStyle->SetStatX(1);
  gStyle->SetStatY(1);
  TFile* rootfile = TFile::Open(Form("./ROOTfiles/prexRespin1_%d_regress.root",run_num));
  TTree *reg = (TTree*)rootfile ->Get("reg");

  TString cuts = "ok_cut";

  Int_t nbpms= sizeof(bpm_name)/sizeof(*bpm_name);
  vector<TText * > bpm_txt;
  vector<TText * > col_txt;

  for(int i=0;i<nbpms;i++){
    TText *txt = new TText(0.1,0.5, "diff_"+bpm_name[i]);
    TText *col = new TText(0.0,0.95, "diff_"+bpm_name[i]);
    txt->SetTextSize(0.2);
    txt->SetNDC();
    col->SetTextSize(0.2);
    col->SetNDC();
    bpm_txt.push_back(txt);
    col_txt.push_back(col);
  }

  Int_t c_height = 500;
  TCanvas *c1  = new TCanvas("c1","c1",c_height*(nbpms+1), c_height);
  c1->Divide(nbpms+1,1); // columns : iv 

  for(int ibpm=0;ibpm<nbpms; ibpm++){
    c1->Clear( "D");
    c1->cd(1);
    bpm_txt[ibpm]->Draw();
    for(int jbpm=0; jbpm< nbpms; jbpm++){
      c1->cd( jbpm +2);
      reg->Draw(
		Form("1e3*diff_bpm%s: 1e3*diff_bpm%s>>h%d_%d",
		     bpm_name[ibpm].Data(),bpm_name[jbpm].Data(), 
		     ibpm,jbpm),cuts,"prof"); 
      TH2D* h_buff = (TH2D*)gDirectory->FindObject(Form("h%d_%d",ibpm,jbpm));
      double fit_low = h_buff->GetMean() - h_buff->GetRMS();
      double fit_up = h_buff->GetMean() + h_buff->GetRMS();

      h_buff->SetTitle("");
      h_buff->GetXaxis()->SetTitle("Position Difference (um)");
      h_buff->Fit("pol1","QR","",fit_low,fit_up);
      col_txt[jbpm]->Draw("same");
    }
    c1->SaveAs(Form("run%d_raw_bpm_prof%d.png",run_num,ibpm));
  }
  
  gSystem->Exec(Form("convert run%d_raw_bpm_prof*.png run%d_raw_bpm_prof.pdf",
		     run_num, run_num));
  gSystem->Exec(Form("rm run%d_raw_bpm_prof*.png", run_num));

}

void PlotBPMRawCorrelation(Int_t run_num){
  gStyle->SetOptStat(0);
  gStyle->SetStatW(0.2);
  gStyle->SetStatH(0.2);
  gStyle->SetStatX(1);
  gStyle->SetStatY(1);
  TFile* rootfile = TFile::Open(Form("./ROOTfiles/prexRespin1_%d_regress.root",run_num));
  TTree *reg = (TTree*)rootfile ->Get("reg");

  TString cuts = "ok_cut";

  Int_t nbpms= sizeof(bpm_name)/sizeof(*bpm_name);
  vector<TText * > bpm_txt;
  vector<TText * > col_txt;

  for(int i=0;i<nbpms;i++){
    TText *txt = new TText(0.1,0.5, "diff_"+bpm_name[i]);
    TText *col = new TText(0.0,0.85, "diff_"+bpm_name[i]);
    txt->SetTextSize(0.2);
    txt->SetNDC();
    col->SetTextSize(0.2);
    col->SetNDC();
    bpm_txt.push_back(txt);
    col_txt.push_back(col);
  }

  Int_t c_height = 500;
  TCanvas *c1  = new TCanvas("c1","c1",c_height*(nbpms+1), c_height);
  c1->Divide(nbpms+1,1); // columns : iv 
  TH1D* h_buff;
  for(int ibpm=0;ibpm<nbpms; ibpm++){
    c1->Clear( "D");
    c1->cd(1);
    bpm_txt[ibpm]->Draw();
    for(int jbpm=0; jbpm< nbpms; jbpm++){
      c1->cd( jbpm +2);
      reg->Draw(
		Form("1e3*diff_bpm%s: 1e3*diff_bpm%s>>h%d_%d",
		     bpm_name[ibpm].Data(),bpm_name[jbpm].Data(), 
		     ibpm,jbpm),cuts); 
      h_buff=(TH1D*)gDirectory->FindObject(Form("h%d_%d",ibpm,jbpm));
      h_buff->SetTitle("");
      col_txt[jbpm]->Draw("same");
    }
    c1->SaveAs(Form("run%d_raw_bpm_correlation%d.png",run_num,ibpm));
  }
  
  gSystem->Exec(Form("convert run%d_raw_bpm_correlation*.png run%d_raw_bpm_correlation.pdf",
		     run_num, run_num));
  gSystem->Exec(Form("rm run%d_raw_bpm_correlation*.png", run_num));

}
void PlotBPMRegCorrelation(Int_t run_num){
  gStyle->SetOptStat(0);
  gStyle->SetStatW(0.2);
  gStyle->SetStatH(0.2);
  gStyle->SetStatX(1);
  gStyle->SetStatY(1);

  TString bpm_name[]={"4aX","4aY","4eX","4eY","12X","12Y","10X","10Y"};
  TString cuts = "ok_cut";
  Int_t nbpms= sizeof(bpm_name)/sizeof(*bpm_name);
  vector<TText * > bpm_txt;
  vector<TText * > col_txt;

  for(int i=0;i<nbpms;i++){
    TText *txt = new TText(0.1,0.3, "reg diff_"+bpm_name[i]);
    TText *col = new TText(0.3,0.05, "diff_"+bpm_name[i]);
    txt->SetTextSize(0.2);
    txt->SetNDC();
    col->SetTextSize(0.2);
    col->SetNDC();
    bpm_txt.push_back(txt);
    col_txt.push_back(col);
  }

  Int_t c_height = 500;
  TCanvas *c1  = new TCanvas("c1","c1",c_height*(nbpms+1), c_height);
  c1->Divide(nbpms+1,1); // columns : iv 
  TH1D *h_buff;
  for(int ibpm =0 ;ibpm<nbpms;ibpm++){
    TFile* rootfile = TFile::Open(Form("../ROOTfiles/prexRespin1_%d_%s.root",
				       run_num, bpm_name[ibpm].Data()));
    TTree *reg = (TTree*)rootfile ->Get("reg");
    c1->Clear( "D");
    c1->cd(1);
    bpm_txt[ibpm]->Draw();
    for(int jbpm=0; jbpm< nbpms; jbpm++){
      c1->cd( jbpm +2);
      reg->Draw(
		Form("1e3*reg_diff_bpm%s: 1e3*diff_bpm%s>>h%d_%d",
		     bpm_name[ibpm].Data(),bpm_name[jbpm].Data(), 
		     ibpm,jbpm),cuts); 
      h_buff=(TH1D*)gDirectory->FindObject(Form("h%d_%d",ibpm,jbpm));
      h_buff->SetTitle("");
      h_buff->GetXaxis()->SetTitle("Position Difference (um)");
      col_txt[jbpm]->Draw("same");
    }
    c1->SaveAs(Form("run%d_reg_bpm_correlation%d.png",run_num,ibpm));
  }


  gSystem->Exec(Form("convert run%d_reg_bpm_correlation*.png run%d_reg_bpm_correlation.pdf",
		     run_num, run_num));
  gSystem->Exec(Form("rm run%d_reg_bpm_correlation*.png", run_num));

}
void PlotBPMRegProf(Int_t run_num){

  gStyle->SetStatW(0.3);
  gStyle->SetOptFit(1);
  gStyle->SetOptStat(0);
  gStyle->SetStatH(0.2);
  gStyle->SetStatX(0.95);
  gStyle->SetStatY(1);

  TString bpm_name[]={"4aX","4aY","4eX","4eY","12X","12Y","10X","10Y"};
  TString cuts = "ok_cut";
  Int_t nbpms= sizeof(bpm_name)/sizeof(*bpm_name);
  vector<TText * > bpm_txt;
  vector<TText * > col_txt;

  for(int i=0;i<nbpms;i++){
    TText *txt = new TText(0.1,0.3, "reg diff_ "+bpm_name[i]);
    TText *col = new TText(0.2,0.05, "diff_"+bpm_name[i]);
    txt->SetTextSize(0.2);
    txt->SetNDC();
    col->SetTextSize(0.2);
    col->SetNDC();
    bpm_txt.push_back(txt);
    col_txt.push_back(col);
  }

  Int_t c_height = 500;
  TCanvas *c1  = new TCanvas("c1","c1",c_height*(nbpms+1), c_height);
  c1->Divide(nbpms+1,1); // columns : iv 

  for(int ibpm =0 ;ibpm<nbpms;ibpm++){
    TFile* rootfile = TFile::Open(Form("../ROOTfiles/prexRespin1_%d_%s.root",
				       run_num, bpm_name[ibpm].Data()));
    TTree *reg = (TTree*)rootfile ->Get("reg");
    c1->Clear( "D");
    c1->cd(1);
    bpm_txt[ibpm]->Draw();
    for(int jbpm=0; jbpm< nbpms; jbpm++){
      c1->cd( jbpm +2);
      reg->Draw(
		Form("1e3*reg_diff_bpm%s: 1e3*diff_bpm%s>>h%d_%d",
		     bpm_name[ibpm].Data(),bpm_name[jbpm].Data(), 
		     ibpm,jbpm),cuts,"prof"); 

      TH2D* h_buff = (TH2D*)gDirectory->FindObject(Form("h%d_%d",ibpm,jbpm));
      double fit_low = h_buff->GetMean() - h_buff->GetRMS();
      double fit_up = h_buff->GetMean() + h_buff->GetRMS();
      h_buff->SetTitle("");
      h_buff->GetXaxis()->SetTitle("Position Difference (um)");
      h_buff->Fit("pol1","QR","",fit_low,fit_up);

      col_txt[jbpm]->Draw("same");
    }
    c1->SaveAs(Form("run%d_reg_bpm_prof%d.png",run_num,ibpm));
  }


  gSystem->Exec(Form("convert run%d_reg_bpm_prof*.png run%d_reg_bpm_prof.pdf",
		     run_num, run_num));
  gSystem->Exec(Form("rm run%d_reg_bpm_prof*.png", run_num));

}
