#include <TMath.h>
#include <TStyle.h>
#include <TPaveStats.h>
#include <TLine.h>
#include <TLegend.h>
#include <TVector2.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TProfile.h>
#include <sstream>
#include <iostream>
#include <TGraphErrors.h>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;
void dithering_plot_cycles_pass2(int slugNo=0){

  char infile[300];
  sprintf(infile,"~/PREX/prompt/beam-mod/rootfiles_alldet_pass2/dit_alldet_slopes_slug%d.root",slugNo);
  TFile *file1=new TFile(infile);
  TTree *tree_R = (TTree*) file1->Get("dit");
  Double_t        usl_4aX;
  Double_t        usl_4eX;
  Double_t        usl_11X12X;
  Double_t        usl_4aY;
  Double_t        usl_4eY;
  Double_t        usr_4aX;
  Double_t        usr_4eX;
  Double_t        usr_11X12X;
  Double_t        usr_4aY;
  Double_t        usr_4eY;
  Double_t        dsl_4aX;
  Double_t        dsl_4eX;
  Double_t        dsl_11X12X;
  Double_t        dsl_4aY;
  Double_t        dsl_4eY;
  Double_t        dsr_4aX;
  Double_t        dsr_4eX;
  Double_t        dsr_11X12X;
  Double_t        dsr_4aY;
  Double_t        dsr_4eY;
  Int_t           run;
  Double_t        cyclenum;
  Int_t           flag;

  // List of branches
  TBranch        *b_usl_4aX;   //!
  TBranch        *b_usl_4eX;   //!
  TBranch        *b_usl_11X12X;   //!
  TBranch        *b_usl_4aY;   //!
  TBranch        *b_usl_4eY;   //!
  TBranch        *b_usr_4aX;   //!
  TBranch        *b_usr_4eX;   //!
  TBranch        *b_usr_11X12X;   //!
  TBranch        *b_usr_4aY;   //!
  TBranch        *b_usr_4eY;   //!
  TBranch        *b_dsl_4aX;   //!
  TBranch        *b_dsl_4eX;   //!
  TBranch        *b_dsl_11X12X;   //!
  TBranch        *b_dsl_4aY;   //!
  TBranch        *b_dsl_4eY;   //!
  TBranch        *b_dsr_4aX;   //!
  TBranch        *b_dsr_4eX;   //!
  TBranch        *b_dsr_11X12X;   //!
  TBranch        *b_dsr_4aY;   //!
  TBranch        *b_dsr_4eY;   //!
  TBranch        *b_run;   //!
  TBranch        *b_cyclenum;   //!
  TBranch        *b_flag;   //!

  tree_R->SetBranchAddress("usl_4aX", &usl_4aX, &b_usl_4aX);
  tree_R->SetBranchAddress("usl_4eX", &usl_4eX, &b_usl_4eX);
  tree_R->SetBranchAddress("usl_11X12X", &usl_11X12X, &b_usl_11X12X);
  tree_R->SetBranchAddress("usl_4aY", &usl_4aY, &b_usl_4aY);
  tree_R->SetBranchAddress("usl_4eY", &usl_4eY, &b_usl_4eY);
  tree_R->SetBranchAddress("usr_4aX", &usr_4aX, &b_usr_4aX);
  tree_R->SetBranchAddress("usr_4eX", &usr_4eX, &b_usr_4eX);
  tree_R->SetBranchAddress("usr_11X12X", &usr_11X12X, &b_usr_11X12X);
  tree_R->SetBranchAddress("usr_4aY", &usr_4aY, &b_usr_4aY);
  tree_R->SetBranchAddress("usr_4eY", &usr_4eY, &b_usr_4eY);
  tree_R->SetBranchAddress("dsl_4aX", &dsl_4aX, &b_dsl_4aX);
  tree_R->SetBranchAddress("dsl_4eX", &dsl_4eX, &b_dsl_4eX);
  tree_R->SetBranchAddress("dsl_11X12X", &dsl_11X12X, &b_dsl_11X12X);
  tree_R->SetBranchAddress("dsl_4aY", &dsl_4aY, &b_dsl_4aY);
  tree_R->SetBranchAddress("dsl_4eY", &dsl_4eY, &b_dsl_4eY);
  tree_R->SetBranchAddress("dsr_4aX", &dsr_4aX, &b_dsr_4aX);
  tree_R->SetBranchAddress("dsr_4eX", &dsr_4eX, &b_dsr_4eX);
  tree_R->SetBranchAddress("dsr_11X12X", &dsr_11X12X, &b_dsr_11X12X);
  tree_R->SetBranchAddress("dsr_4aY", &dsr_4aY, &b_dsr_4aY);
  tree_R->SetBranchAddress("dsr_4eY", &dsr_4eY, &b_dsr_4eY);
  tree_R->SetBranchAddress("run", &run, &b_run);
  tree_R->SetBranchAddress("cyclenum", &cyclenum, &b_cyclenum);
  tree_R->SetBranchAddress("flag", &flag, &b_flag);

  TGraph * usl_hist[5];
  TGraph * dsl_hist[5];
  TGraph * usr_hist[5];
  TGraph * dsr_hist[5];
  TGraph * avg_us_hist[5];
  TGraph * avg_ds_hist[5];
  TGraph * dd_us_hist[5];
  TGraph * dd_ds_hist[5];
  TString wire1[5]={"usl_4aX","usl_4eX","usl_4aY","usl_4eY","usl_11X12X"};
  TString wire2[5]={"usr_4aX","usr_4eX","usr_4aY","usr_4eY","usr_11X12X"};
  TString wire3[5]={"dsl_4aX","dsl_4eX","dsl_4aY","dsl_4eY","dsl_11X12X"};
  TString wire4[5]={"dsr_4aX","dsr_4eX","dsr_4aY","dsr_4eY","dsr_11X12X"};

  TString wire11[5]={"usl_4aX","usl_4eX","usl_4aY","usl_4eY","usl_11X12X"};
  TString wire12[5]={"usr_4aX","usr_4eX","usr_4aY","usr_4eY","usr_11X12X"};
  TString wire13[5]={"dsl_4aX","dsl_4eX","dsl_4aY","dsl_4eY","dsl_11X12X"};
  TString wire14[5]={"dsr_4aX","dsr_4eX","dsr_4aY","dsr_4eY","dsr_11X12X"};


  /*TString wire5[5]={"avg_us_bpm4aX","avg_us_bpm4eX","avg_us_bpm4aY","avg_us_bpm4eY","avg_us_bpm11X12X"};
    TString wire6[5]={"avg_ds_bpm4aX","avg_ds_bpm4eX","avg_ds_bpm4aY","avg_ds_bpm4eY","avg_ds_bpm11X12X"};
    TString wire7[5]={"dd_us_bpm4aX","dd_us_bpm4eX","dd_us_bpm4aY","dd_us_bpm4eY","dd_us_bpm11X12X"};
    TString wire8[5]={"dd_ds_bpm4aX","dd_ds_bpm4eX","dd_ds_bpm4aY","dd_ds_bpm4eY","dd_ds_bpm11X12X"};*/
  TString wireavg_us[5]={"0.5*(usl_4aX+usr_4aX)","0.5*(usl_4eX+usr_4eX)","0.5*(usl_4aY+usr_4aY)","0.5*(usl_4eY+usr_4eY)","0.5*(usl_11X12X+usr_11X12X)"};
  TString wiredd_us[5]={"0.5*(usl_4aX-usr_4aX)","0.5*(usl_4eX-usr_4eX)","0.5*(usl_4aY-usr_4aY)","0.5*(usl_4eY-usr_4eY)","0.5*(usl_11X12X-usr_11X12X)"};
  TString wireavg_ds[5]={"0.5*(dsl_4aX+dsr_4aX)","0.5*(dsl_4eX+dsr_4eX)","0.5*(dsl_4aY+dsr_4aY)","0.5*(dsl_4eY+dsr_4eY)","0.5*(dsl_11X12X+dsr_11X12X)"};
  TString wiredd_ds[5]={"0.5*(dsl_4aX-dsr_4aX)","0.5*(dsl_4eX-dsr_4eX)","0.5*(dsl_4aY-dsr_4aY)","0.5*(dsl_4eY-dsr_4eY)","0.5*(dsl_11X12X-dsr_11X12X)"};

  TString wireavg_us1[5]={"avg_us_4ax","avg_us_4ex","avg_us_4ay","avg_us_4ey","avg_us_11X12X"};
  TString wiredd_us1[5]={"dd_us_4ax","dd_us_4ex","dd_us_4ay","dd_us_4ey","dd_us_11X12X"};
  TString wireavg_ds1[5]={"avg_ds_4ax","avg_ds_4ex","avg_ds_4ay","avg_ds_4ey","avg_ds_11X12X"};
  TString wiredd_ds1[5]={"dd_ds_4ax","dd_ds_4ex","dd_ds_4ay","dd_ds_4ey","dd_ds_11X12X"};
  /*TString avg_us = Form("%f*(usl_4ax+usr_4ax)",0.5);
    TString avg_ds = Form("%f*(dsl_4ax+dsr_4ax)",0.5);
    TString dd_us = Form("%f*(usl_4ax-usr_4ax)",0.5);
    TString dd_ds = Form("%f*(dsl_4ax-dsr_4ax)",0.5);
    tree_R->SetAlias("dit_avg_us",avg_us);
    tree_R->SetAlias("dit_avg_ds",avg_ds);
    tree_R->SetAlias("dit_dd_us",dd_us);
    tree_R->SetAlias("dit_dd_ds",dd_ds);*/
  double mean_us4ax[5];
  double mean_us4ex[5];
  double mean_us4ay[5];
  double mean_us4ey[5];

  double mean_ds4ax[5];
  double mean_ds4ex[5];
  double mean_ds4ay[5];
  double mean_ds4ey[5];

  double mean_dsdd[5];
  double mean_usdd[5];
  double mean_dsavg[5];
  double mean_usavg[5];


  for(int n=0;n<5;n++){
    int num_us4ax = tree_R->Draw(Form("%s:cyclenum",wire1[n].Data()),"flag==1","goff");
    usl_hist[n]= new TGraph(num_us4ax, tree_R->GetV2(),tree_R->GetV1());
    usl_hist[n]->SetTitle(Form("%s",wire11[n].Data()));
    usl_hist[n]->GetXaxis()->SetTitle("super cyclenumle");
    usl_hist[n]->GetXaxis()->SetTitleSize(0.05);
    usl_hist[n]->GetYaxis()->SetTitleSize(0.05);
    mean_us4ax[n]= usl_hist[n]->GetMean(2);
    int num_us4ex = tree_R->Draw(Form("%s:cyclenum",wire2[n].Data()),"flag==1","goff");
    usr_hist[n]= new TGraph(num_us4ex, tree_R->GetV2(),tree_R->GetV1());
    usr_hist[n]->SetTitle(Form("%s",wire12[n].Data()));
    usr_hist[n]->GetXaxis()->SetTitle("super cyclenumle");
    usr_hist[n]->GetXaxis()->SetTitleSize(0.05);
    usr_hist[n]->GetYaxis()->SetTitleSize(0.05);
    mean_us4ex[n]= usr_hist[n]->GetMean(2);
    int num_us4ay = tree_R->Draw(Form("%s:cyclenum",wire3[n].Data()),"flag==1","goff");
    dsl_hist[n]= new TGraph(num_us4ay, tree_R->GetV2(),tree_R->GetV1());
    dsl_hist[n]->SetTitle(Form("%s",wire13[n].Data()));
    dsl_hist[n]->GetXaxis()->SetTitle("super cyclenumle");
    dsl_hist[n]->GetXaxis()->SetTitleSize(0.05);
    dsl_hist[n]->GetYaxis()->SetTitleSize(0.05);
    mean_us4ay[n]= dsl_hist[n]->GetMean(2);
    int num_us4ey = tree_R->Draw(Form("%s:cyclenum",wire4[n].Data()),"flag==1","goff");
    dsr_hist[n]= new TGraph(num_us4ey, tree_R->GetV2(),tree_R->GetV1());
    dsr_hist[n]->SetTitle(Form("%s",wire14[n].Data()));
    dsr_hist[n]->GetXaxis()->SetTitle("super cyclenumle");
    dsr_hist[n]->GetXaxis()->SetTitleSize(0.05);
    dsr_hist[n]->GetYaxis()->SetTitleSize(0.05);
    mean_us4ey[n]= dsr_hist[n]->GetMean(2);

    int num_ds4ax = tree_R->Draw(Form("%s:cyclenum",wireavg_us[n].Data()),"flag==1","goff");
    avg_us_hist[n]= new TGraph(num_ds4ax, tree_R->GetV2(),tree_R->GetV1());
    avg_us_hist[n]->SetTitle(Form("%s",wireavg_us1[n].Data()));
    avg_us_hist[n]->GetXaxis()->SetTitle("super cyclenumle");
    avg_us_hist[n]->GetXaxis()->SetTitleSize(0.05);
    avg_us_hist[n]->GetYaxis()->SetTitleSize(0.05);
    mean_usavg[n]= avg_us_hist[n]->GetMean(2);

    int num_ds4ex = tree_R->Draw(Form("%s:cyclenum",wiredd_us[n].Data()),"flag==1","goff");
    dd_us_hist[n]= new TGraph(num_ds4ex, tree_R->GetV2(),tree_R->GetV1());
    dd_us_hist[n]->SetTitle(Form("%s",wiredd_us1[n].Data()));
    dd_us_hist[n]->GetXaxis()->SetTitle("super cyclenumle");
    dd_us_hist[n]->GetXaxis()->SetTitleSize(0.05);
    dd_us_hist[n]->GetYaxis()->SetTitleSize(0.05);
    mean_usdd[n]= dd_us_hist[n]->GetMean(2);
    int num_ds4ay = tree_R->Draw(Form("%s:cyclenum",wireavg_ds[n].Data()),"flag==1","goff");
    avg_ds_hist[n]= new TGraph(num_ds4ay, tree_R->GetV2(),tree_R->GetV1());
    avg_ds_hist[n]->SetTitle(Form("%s",wireavg_ds1[n].Data()));
    avg_ds_hist[n]->GetXaxis()->SetTitle("super cyclenumle");
    avg_ds_hist[n]->GetXaxis()->SetTitleSize(0.05);
    avg_ds_hist[n]->GetYaxis()->SetTitleSize(0.05);
    mean_dsavg[n]= avg_ds_hist[n]->GetMean(2);

    int num_ds4ey = tree_R->Draw(Form("%s:cyclenum",wiredd_ds[n].Data()),"flag==1","goff");
    dd_ds_hist[n]= new TGraph(num_ds4ey, tree_R->GetV2(),tree_R->GetV1());
    dd_ds_hist[n]->SetTitle(Form("%s",wiredd_ds1[n].Data()));
    dd_ds_hist[n]->GetXaxis()->SetTitle("super cyclenumle");
    dd_ds_hist[n]->GetXaxis()->SetTitleSize(0.05);
    dd_ds_hist[n]->GetYaxis()->SetTitleSize(0.05);
    mean_dsdd[n]= dd_ds_hist[n]->GetMean(2);
  }
  TLine *targetLine[5];
  targetLine[0]=new TLine(797,-80,797,80);
  targetLine[1]=new TLine(1361,-80,1361,80);
  targetLine[2]=new TLine(2139,-80,2139,80);
  targetLine[4]=new TLine(2500,-80,2500,80);
  targetLine[3]=new TLine(2701,-80,2701,80);
  TLatex *lX[5];
  for(int i=0;i<5;i++){
    targetLine[i]->SetLineColor(4);
    targetLine[i]->SetLineWidth(2);
    targetLine[i]->SetLineStyle(1);
    lX[i]= new TLatex();
    lX[i]->SetTextSize(0.04);
    lX[i]->SetTextFont(72);
  }

  TLine *Lineusl[5];
  TLine *Lineusr[5];
  TLine *Linedsl[5];
  TLine *Linedsr[5];
  TLine *Lineddds[5];
  TLine *Lineddus[5];
  TLine *Lineavgds[5];
  TLine *Lineavgus[5];

  TCanvas *cus = new TCanvas("cus","cus",1000,1000);
  cus->Divide(2,3);
  for(int i=0;i<5;i++){
    cus->cd(i+1);
    usl_hist[i]->SetTitle(Form("%s : slug %d",usl_hist[i]->GetTitle(), slugNo));
    usl_hist[i]->GetYaxis()->SetRangeUser(-100,100);
    usl_hist[i]->Draw("Ap*");
    Lineusl[i]=new TLine(4290,mean_us4ax[i],4301,mean_us4ax[i]);
    Lineusl[i]->SetLineColor(2);
    Lineusl[i]->Draw("same");
    gPad->SetGrid(1);
    gPad->SetGridx(1);
    gPad->SetGridy(1);

    targetLine[0]->Draw("same");
    targetLine[1]->Draw("same");
    targetLine[2]->Draw("same");
    targetLine[3]->Draw("same");
    lX[0]->DrawLatex(50,80,"#splitline{run 3134-3636}{D-208Pb2-D}");
    lX[1]->DrawLatex(800,80,"#splitline{run 3644-3821}{D-208Pb10-D}");
    lX[2]->DrawLatex(1400,80,"#splitline{run 3822-4146}{D-208Pb9-D}");
    lX[3]->DrawLatex(2200,80,"#splitline{run 4148-4370}{D-208Pb8-D}");
    lX[4]->DrawLatex(2702,80,"#splitline{run 4372-}{D-208Pb5-D}");
  }  
  //cus->SaveAs(Form("usl_cyclenum_slug%d_pass2.pdf",slugNo));
  cus->SaveAs(Form("plots/cyclenum_slug%d_pass2.pdf[",slugNo));
  TCanvas *cds = new TCanvas("cds","cds",1000,1000);
  cds->Divide(2,3);
  for(int i=0;i<5;i++){
    cds->cd(i+1);
    usr_hist[i]->SetTitle(Form("%s : slug %d",usr_hist[i]->GetTitle(), slugNo));
    usr_hist[i]->GetYaxis()->SetRangeUser(-100,100);
    usr_hist[i]->Draw("Ap*");
    Lineusr[i]=new TLine(4290,mean_us4ex[i],4301,mean_us4ex[i]);
    Lineusr[i]->SetLineColor(2);
    Lineusr[i]->Draw("same");
    gPad->SetGrid(1);
    gPad->SetGridx(1);
    gPad->SetGridy(1);

    lX[0]->DrawLatex(50,80,"#splitline{run 3134-3636}{D-208Pb2-D}");
    lX[1]->DrawLatex(800,80,"#splitline{run 3644-3821}{D-208Pb10-D}");
    lX[2]->DrawLatex(1400,80,"#splitline{run 3822-4146}{D-208Pb9-D}");
    lX[3]->DrawLatex(2200,80,"#splitline{run 4148-4370}{D-208Pb8-D}");
    lX[4]->DrawLatex(2702,80,"#splitline{run 4372-}{D-208Pb5-D}");
    targetLine[0]->Draw("same");
    targetLine[1]->Draw("same");
    targetLine[2]->Draw("same");
    targetLine[3]->Draw("same");
  }
  //cds->SaveAs(Form("usr_cyclenum_slug%d_pass2.pdf",slugNo));
  cds->SaveAs(Form("plots/cyclenum_slug%d_pass2.pdf",slugNo));

  TCanvas *c2 = new TCanvas("c2","c2",1000,1000);
  c2->Divide(2,3);
  for(int i=0;i<5;i++){
    c2->cd(i+1);
    dsl_hist[i]->SetTitle(Form("%s : slug %d",dsl_hist[i]->GetTitle(), slugNo));
    dsl_hist[i]->GetYaxis()->SetRangeUser(-100,100);
    dsl_hist[i]->Draw("Ap*");
    Linedsl[i]=new TLine(4290,mean_us4ay[i],4301,mean_us4ay[i]);
    Linedsl[i]->SetLineColor(2);
    Linedsl[i]->Draw("same");
    gPad->SetGrid(1);
    gPad->SetGridx(1);
    gPad->SetGridy(1);

    targetLine[0]->Draw("same");
    targetLine[1]->Draw("same");
    targetLine[2]->Draw("same");
    targetLine[3]->Draw("same");
    lX[0]->DrawLatex(50,80,"#splitline{run 3134-3636}{D-208Pb2-D}");
    lX[1]->DrawLatex(800,80,"#splitline{run 3644-3821}{D-208Pb10-D}");
    lX[2]->DrawLatex(1400,80,"#splitline{run 3822-4146}{D-208Pb9-D}");
    lX[3]->DrawLatex(2200,80,"#splitline{run 4148-4370}{D-208Pb8-D}");
    lX[4]->DrawLatex(2702,80,"#splitline{run 4372-}{D-208Pb5-D}");
  }  
  // c2->SaveAs(Form("dsl_cyclenum_slug%d_pass2.pdf",slugNo));
  c2->SaveAs(Form("plots/cyclenum_slug%d_pass2.pdf",slugNo));
  TCanvas *c3 = new TCanvas("c3","c3",1000,1000);
  c3->Divide(2,3);
  for(int i=0;i<5;i++){
    c3->cd(i+1);
    dsr_hist[i]->SetTitle(Form("%s : slug %d",dsr_hist[i]->GetTitle(), slugNo));
    dsr_hist[i]->GetYaxis()->SetRangeUser(-100,100);
    dsr_hist[i]->Draw("Ap*");
    Linedsr[i]=new TLine(4290,mean_us4ey[i],4301,mean_us4ey[i]);
    Linedsr[i]->SetLineColor(2);
    Linedsr[i]->Draw("same");
    gPad->SetGrid(1);
    gPad->SetGridx(1);
    gPad->SetGridy(1);

    targetLine[0]->Draw("same");
    targetLine[1]->Draw("same");
    targetLine[2]->Draw("same");
    targetLine[3]->Draw("same");

    lX[0]->DrawLatex(50,80,"#splitline{run 3134-3636}{D-208Pb2-D}");
    lX[1]->DrawLatex(800,80,"#splitline{run 3644-3821}{D-208Pb10-D}");
    lX[2]->DrawLatex(1400,80,"#splitline{run 3822-4146}{D-208Pb9-D}");
    lX[3]->DrawLatex(2200,80,"#splitline{run 4148-4370}{D-208Pb8-D}");
    lX[4]->DrawLatex(2702,80,"#splitline{run 4372-}{D-208Pb5-D}");
  }  

  c3->SaveAs(Form("plots/cyclenum_slug%d_pass2.pdf]",slugNo));
  /* TCanvas *c4 = new TCanvas("c4","c4",1000,1000);
     c4->Divide(2,3);
     for(int i=0;i<5;i++){
     c4->cd(i+1);
     avg_us_hist[i]->SetTitle(Form("%s : slug %d",avg_us_hist[i]->GetTitle(), slugNo));
     avg_us_hist[i]->Draw("Ap*");
     Lineavgus[i]=new TLine(4290,mean_usavg[i],4301,mean_usavg[i]);
     Lineavgus[i]->SetLineColor(2);
     Lineavgus[i]->Draw("same");
     gPad->SetGrid(1);
     gPad->SetGridx(1);
     gPad->SetGridy(1);
     }  
  //c4->SaveAs(Form("avgus_cyclenum_slug%d_pass2.pdf",slugNo));
  TCanvas *c5 = new TCanvas("c5","c5",1000,1000);
  c5->Divide(2,3);
  for(int i=0;i<5;i++){
  c5->cd(i+1);
  dd_us_hist[i]->Draw("Ap*");
  Lineddus[i]=new TLine(4290,mean_usdd[i],4301,mean_usdd[i]);
  Lineddus[i]->SetLineColor(2);
  Lineddus[i]->Draw("same");
  gPad->SetGrid(1);
  gPad->SetGridx(1);
  gPad->SetGridy(1);
  }  

  //c5->SaveAs(Form("ddus_cyclenum_slug%d_pass2.pdf",slugNo));
  TCanvas *c6 = new TCanvas("c6","c6",1000,1000);
  c6->Divide(2,3);
  for(int i=0;i<5;i++){
  c6->cd(i+1);
  avg_ds_hist[i]->SetTitle(Form("%s : slug %d",avg_ds_hist[i]->GetTitle(), slugNo));
  avg_ds_hist[i]->Draw("Ap*");
  Lineavgds[i]=new TLine(4290,mean_dsavg[i],4301,mean_dsavg[i]);
  Lineavgds[i]->SetLineColor(2);
  Lineavgds[i]->Draw("same");
  gPad->SetGrid(1);
  gPad->SetGridx(1);
  gPad->SetGridy(1);
  }  
  //c6->SaveAs(Form("avgds_cyclenum_slug%d_pass2.pdf",slugNo));
  TCanvas *c7 = new TCanvas("c7","c7",1000,1000);
  c7->Divide(2,3);
  for(int i=0;i<5;i++){
  c7->cd(i+1);
  dd_ds_hist[i]->SetTitle(Form("%s : slug %d",dd_ds_hist[i]->GetTitle(), slugNo));
  dd_ds_hist[i]->Draw("Ap*");
  Lineddds[i]=new TLine(4290,mean_dsdd[i],4301,mean_dsdd[i]);
  Lineddds[i]->SetLineColor(2);
  Lineddds[i]->Draw("same");
  gPad->SetGrid(1);
  gPad->SetGridx(1);
  gPad->SetGridy(1);
  } */ 

  //  c7->SaveAs(Form("ddds_cyclenum_slug%d_pass2.pdf",slugNo));
  // gSystem->Exec("pdfunite *cyclenum_slug17.pdf all_cyclenum_slug.pdf");
  // gSystem->Exec("rm -rf *cyclenum_slug17.pdf");
}
