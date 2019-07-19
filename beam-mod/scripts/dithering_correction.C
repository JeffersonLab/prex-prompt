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
using namespace std;
void dithering_correction(int runNo=0){
        char inputfile1[300];
        sprintf(inputfile1,"./usl_dithering_slope_run%d.txt",runNo);
        char inputfile2[300];
        sprintf(inputfile2,"./usr_dithering_slope_run%d.txt",runNo);
        char inputfile3[300];
        sprintf(inputfile3,"./dsl_dithering_slope_run%d.txt",runNo);
        char inputfile4[300];
       sprintf(inputfile4,"./dsr_dithering_slope_run%d.txt",runNo);
       ifstream infile1(inputfile1);
       ifstream infile2(inputfile2);
       ifstream infile3(inputfile3);
       ifstream infile4(inputfile4);
const int n=2;
double usl_supercyc[n],usl_4ax[n],usl_4ex[n],usl_12x[n],usl_4ay[n],usl_4ey[n];
double dsl_supercyc[n],dsl_4ax[n],dsl_4ex[n],dsl_12x[n],dsl_4ay[n],dsl_4ey[n];
double usr_supercyc[n],usr_4ax[n],usr_4ex[n],usr_12x[n],usr_4ay[n],usr_4ey[n];
double dsr_supercyc[n],dsr_4ax[n],dsr_4ex[n],dsr_12x[n],dsr_4ay[n],dsr_4ey[n];
double avg_usl_4ax, avg_usl_4ex, avg_usl_12x, avg_usl_4ay, avg_usl_4ey;
double avg_usr_4ax, avg_usr_4ex, avg_usr_12x, avg_usr_4ay, avg_usr_4ey;
double avg_dsl_4ax, avg_dsl_4ex, avg_dsl_12x, avg_dsl_4ay, avg_dsl_4ey;
double avg_dsr_4ax, avg_dsr_4ex, avg_dsr_12x, avg_dsr_4ay, avg_dsr_4ey;

double tot_usl_4ax, tot_usl_4ex, tot_usl_12x, tot_usl_4ay, tot_usl_4ey;
double tot_usr_4ax, tot_usr_4ex, tot_usr_12x, tot_usr_4ay, tot_usr_4ey;
double tot_dsl_4ax, tot_dsl_4ex, tot_dsl_12x, tot_dsl_4ay, tot_dsl_4ey;
double tot_dsr_4ax, tot_dsr_4ex, tot_dsr_12x, tot_dsr_4ay, tot_dsr_4ey;
for(int i=0;i<n;i++)
{
infile1>>usl_supercyc[i]>>usl_4ax[i]>>usl_4ex[i]>>usl_12x[i]>>usl_4ay[i]>>usl_4ey[i];
infile2>>usr_supercyc[i]>>usr_4ax[i]>>usr_4ex[i]>>usr_12x[i]>>usr_4ay[i]>>usr_4ey[i];
infile3>>dsl_supercyc[i]>>dsl_4ax[i]>>dsl_4ex[i]>>dsl_12x[i]>>dsl_4ay[i]>>dsl_4ey[i];
infile4>>dsr_supercyc[i]>>dsr_4ax[i]>>dsr_4ex[i]>>dsr_12x[i]>>dsr_4ay[i]>>dsr_4ey[i];

}

for(int i=0;i<n;i++)
{
 tot_usl_4ax +=usl_4ax[i];
 tot_usl_4ex +=usl_4ex[i];
 tot_usl_12x +=usl_12x[i];
 tot_usl_4ay +=usl_4ay[i];
 tot_usl_4ey +=usl_4ey[i];


 tot_dsl_4ax +=dsl_4ax[i];
 tot_dsl_4ex +=dsl_4ex[i];
 tot_dsl_12x +=dsl_12x[i];
 tot_dsl_4ay +=dsl_4ay[i];
 tot_dsl_4ey +=dsl_4ey[i];

 tot_usr_4ax +=usr_4ax[i];
 tot_usr_4ex +=usr_4ex[i];
 tot_usr_12x +=usr_12x[i];
 tot_usr_4ay +=usr_4ay[i];
 tot_usr_4ey +=usr_4ey[i];
 
 tot_dsr_4ax +=dsr_4ax[i];
 tot_dsr_4ex +=dsr_4ex[i];
 tot_dsr_12x +=dsr_12x[i];
 tot_dsr_4ay +=dsr_4ay[i];
 tot_dsr_4ey +=dsr_4ey[i];
}

 avg_usl_4ax =tot_usl_4ax/n;
 avg_usl_4ex =tot_usl_4ex/n;
 avg_usl_12x =tot_usl_12x/n;
 avg_usl_4ay =tot_usl_4ay/n;
 avg_usl_4ey =tot_usl_4ey/n;

 avg_usr_4ax =tot_usr_4ax/n;
 avg_usr_4ex =tot_usr_4ex/n;
 avg_usr_12x =tot_usr_12x/n;
 avg_usr_4ay =tot_usr_4ay/n;
 avg_usr_4ey =tot_usr_4ey/n;

 avg_dsl_4ax =tot_dsl_4ax/n;
 avg_dsl_4ex =tot_dsl_4ex/n;
 avg_dsl_12x =tot_dsl_12x/n;
 avg_dsl_4ay =tot_dsl_4ay/n;
 avg_dsl_4ey =tot_dsl_4ey/n;

 avg_dsr_4ax =tot_dsr_4ax/n;
 avg_dsr_4ex =tot_dsr_4ex/n;
 avg_dsr_12x =tot_dsr_12x/n;
 avg_dsr_4ay =tot_dsr_4ay/n;
 avg_dsr_4ey =tot_dsr_4ey/n;
 cout<<"avg_usl_4ax="<<avg_usl_4ax<<" "<<"avg_usl_4ex="<<avg_usl_4ex<<" "<<"avg_usl_12x="<<avg_usl_12x<<"  "<<"avg_usl_4ay="<<avg_usl_4ay<<" "<<"avg_usl_4ey="<<avg_usl_4ey<<endl;
 cout<<"avg_usr_4ax="<<avg_usr_4ax<<" "<<"avg_usr_4ex="<<avg_usr_4ex<<" "<<"avg_usr_12x="<<avg_usr_12x<<"  "<<"avg_usr_4ay="<<avg_usr_4ay<<" "<<"avg_usr_4ey="<<avg_usr_4ey<<endl;
 cout<<"avg_dsl_4ax="<<avg_dsl_4ax<<" "<<"avg_dsl_4ex="<<avg_dsl_4ex<<" "<<"avg_dsl_12x="<<avg_dsl_12x<<"  "<<"avg_dsl_4ay="<<avg_dsl_4ay<<" "<<"avg_dsl_4ey="<<avg_dsl_4ey<<endl;
 cout<<"avg_dsr_4ax="<<avg_dsr_4ax<<" "<<"avg_dsr_4ex="<<avg_dsr_4ex<<" "<<"avg_dsr_12x="<<avg_dsr_12x<<"  "<<"avg_dsr_4ay="<<avg_dsr_4ay<<" "<<"avg_dsr_4ey="<<avg_dsr_4ey<<endl;


 TH1F *histusl;
 TH1F *histusr;
 TH1F *histdsl;
 TH1F *histdsr;
 TH1F *histusavg;
 TH1F *histusdd;
 TH1F *histdsavg;
 TH1F *histdsdd;


  char infile[300];
 // sprintf(infile,"/chafs2/work1/apar/japanOutput/prexALL_%d.000.root",runNo);
  sprintf(infile,"/chafs2/work1/apar/japanOutput/prexPrompt_pass2_%d.000.root",runNo);
  TFile *file1=new TFile(infile);
  TTree *tree_R = (TTree*) file1->Get("mul");

  Double_t        CodaEventNumber;
   Double_t        diff_bpm4aX_hw_sum;
   Double_t        diff_bpm4aX_block0;
   Double_t        diff_bpm4aX_block1;
   Double_t        diff_bpm4aX_block2;
   Double_t        diff_bpm4aX_block3;
   Double_t        diff_bpm4aX_num_samples;
   Double_t        diff_bpm4aX_Device_Error_Code;
   Double_t        diff_bpm4aY_hw_sum;
   Double_t        diff_bpm4aY_block0;
   Double_t        diff_bpm4aY_block1;
   Double_t        diff_bpm4aY_block2;
   Double_t        diff_bpm4aY_block3;
   Double_t        diff_bpm4aY_num_samples;
   Double_t        diff_bpm4aY_Device_Error_Code;
   Double_t        diff_bpm4eX_hw_sum;
   Double_t        diff_bpm4eX_block0;
   Double_t        diff_bpm4eX_block1;
   Double_t        diff_bpm4eX_block2;
   Double_t        diff_bpm4eX_block3;
   Double_t        diff_bpm4eX_num_samples;
   Double_t        diff_bpm4eX_Device_Error_Code;
   Double_t        diff_bpm4eY_hw_sum;
   Double_t        diff_bpm4eY_block0;
   Double_t        diff_bpm4eY_block1;
   Double_t        diff_bpm4eY_block2;
   Double_t        diff_bpm4eY_block3;
  Double_t        diff_bpm4eY_num_samples;
   Double_t        diff_bpm4eY_Device_Error_Code;
   Double_t        ErrorFlag;
   Double_t        diff_bpm12X_hw_sum;
   Double_t        diff_bpm12X_block0;
   Double_t        diff_bpm12X_block1;
   Double_t        diff_bpm12X_block2;
   Double_t        diff_bpm12X_block3;
   Double_t        diff_bpm12X_num_samples;
   Double_t        diff_bpm12X_Device_Error_Code;
   Double_t        diff_bpm12Y_hw_sum;
   Double_t        diff_bpm12Y_block0;
   Double_t        diff_bpm12Y_block1;
   Double_t        diff_bpm12Y_block2;
   Double_t        diff_bpm12Y_block3;
   Double_t        diff_bpm12Y_num_samples;
   Double_t        diff_bpm12Y_Device_Error_Code;
 
   Double_t        asym_usl_hw_sum;
   Double_t        asym_usl_block0;
   Double_t        asym_usl_block1;
   Double_t        asym_usl_block2;
   Double_t        asym_usl_block3;
   Double_t        asym_usl_num_samples;
   Double_t        asym_usl_Device_Error_Code;
   Double_t        asym_dsl_hw_sum;
   Double_t        asym_dsl_block0;
   Double_t        asym_dsl_block1;
   Double_t        asym_dsl_block2;
   Double_t        asym_dsl_block3;
   Double_t        asym_dsl_num_samples;
   Double_t        asym_dsl_Device_Error_Code;
 
   Double_t        asym_usr_hw_sum;
   Double_t        asym_usr_block0;
   Double_t        asym_usr_block1;
   Double_t        asym_usr_block2;
   Double_t        asym_usr_block3;
   Double_t        asym_usr_num_samples;
   Double_t        asym_usr_Device_Error_Code;
   Double_t        asym_dsr_hw_sum;
   Double_t        asym_dsr_block0;
   Double_t        asym_dsr_block1;
   Double_t        asym_dsr_block2;
   Double_t        asym_dsr_block3;
   Double_t        asym_dsr_num_samples;
   Double_t        asym_dsr_Device_Error_Code;
   TBranch        *b_diff_bpm12X;   //!
   TBranch        *b_diff_bpm4eX;   //!
   TBranch        *b_diff_bpm4eY;   //!
   TBranch        *b_diff_bpm4aX;   //!
   TBranch        *b_diff_bpm4aY;   //!
  TBranch        *b_CodaEventNumber;
  TBranch        *b_ErrorFlag;
   TBranch        *b_asym_usl;   //!
   TBranch        *b_asym_dsl;   //!
   TBranch        *b_asym_usr;   //!
   TBranch        *b_asym_dsr;   //!

   tree_R->SetBranchAddress("asym_usl", &asym_usl_hw_sum, &b_asym_usl);
   tree_R->SetBranchAddress("asym_dsl", &asym_dsl_hw_sum, &b_asym_dsl);
   tree_R->SetBranchAddress("diff_bpm4aX", &diff_bpm4aX_hw_sum, &b_diff_bpm4aX);
   tree_R->SetBranchAddress("diff_bpm4aY", &diff_bpm4aY_hw_sum, &b_diff_bpm4aY);
   tree_R->SetBranchAddress("diff_bpm12X", &diff_bpm12X_hw_sum, &b_diff_bpm12X);
   tree_R->SetBranchAddress("diff_bpm4eX", &diff_bpm4eX_hw_sum, &b_diff_bpm4eX);
   tree_R->SetBranchAddress("diff_bpm4eY", &diff_bpm4eY_hw_sum, &b_diff_bpm4eY);
   tree_R->SetBranchAddress("asym_usr", &asym_usr_hw_sum, &b_asym_usr);
   tree_R->SetBranchAddress("asym_dsr", &asym_dsr_hw_sum, &b_asym_dsr);
TString det_usl = Form("asym_usl/ppm- %f*diff_bpm4aX/um-%f*diff_bpm4eX/um- %f*diff_bpm12X/um - %f*diff_bpm4aY/um -%f*diff_bpm4eY/um",avg_usl_4ax,avg_usl_4ex,avg_usl_12x,avg_usl_4ay,avg_usl_4ey);
TString det_usr = Form("asym_usr/ppm- %f*diff_bpm4aX/um-%f*diff_bpm4eX/um- %f*diff_bpm12X/um - %f*diff_bpm4aY/um -%f*diff_bpm4eY/um",avg_usr_4ax,avg_usr_4ex,avg_usr_12x,avg_usr_4ay,avg_usr_4ey);
TString det_dsl = Form("asym_dsl/ppm- %f*diff_bpm4aX/um-%f*diff_bpm4eX/um- %f*diff_bpm12X/um - %f*diff_bpm4aY/um -%f*diff_bpm4eY/um",avg_dsl_4ax,avg_dsl_4ex,avg_dsl_12x,avg_dsl_4ay,avg_dsl_4ey);
TString det_dsr = Form("asym_dsr/ppm- %f*diff_bpm4aX/um-%f*diff_bpm4eX/um- %f*diff_bpm12X/um - %f*diff_bpm4aY/um -%f*diff_bpm4eY/um",avg_dsr_4ax,avg_dsr_4ex,avg_dsr_12x,avg_dsr_4ay,avg_dsr_4ey);
tree_R->SetAlias("dit_detusl",det_usl);
tree_R->SetAlias("dit_detusr",det_usr);
tree_R->SetAlias("dit_detdsl",det_dsl);
tree_R->SetAlias("dit_detdsr",det_dsr);
//TCanvas *cds = new TCanvas("cds","cds",1000,1000);
tree_R->Draw("dit_detusl>>histusl","ErrorFlag==0");
histusl = (TH1F *)gDirectory->Get("histusl");
// cds->SaveAs("asym_usr_correct.pdf");

//TCanvas *cus = new TCanvas("cus","cus",1000,1000);
tree_R->Draw("dit_detusr>>histusr","ErrorFlag==0");
//cus->SaveAs("asym_usl_correct.pdf");
histusr = (TH1F *)gDirectory->Get("histusr");
tree_R->Draw("dit_detdsl>>histdsl","ErrorFlag==0");
histdsl = (TH1F *)gDirectory->Get("histdsl");
tree_R->Draw("dit_detdsr>>histdsr","ErrorFlag==0");
histdsr = (TH1F *)gDirectory->Get("histdsr");
tree_R->Draw("(dit_detusl+dit_detusr)/2.>>histusavg","ErrorFlag==0");
histusavg= (TH1F *)gDirectory->Get("histusavg");
tree_R->Draw("(dit_detusl-dit_detusr)/2.>>histusdd","ErrorFlag==0");
histusdd= (TH1F *)gDirectory->Get("histusdd");
tree_R->Draw("(dit_detdsl+dit_detdsr)/2.>>histdsavg","ErrorFlag==0");
histdsavg= (TH1F *)gDirectory->Get("histdsavg");
tree_R->Draw("(dit_detdsl-dit_detdsr)/2.>>histdsdd","ErrorFlag==0");
histdsdd= (TH1F *)gDirectory->Get("histdsdd");

 TCanvas *cus = new TCanvas("cus","cus",1000,1000);
  cus->Divide(2,2);
  cus->cd(1);
  histusl->Draw();

  cus->cd(2);
  histusr->Draw();
  
  cus->cd(3);
  histusavg->Draw();
  
  cus->cd(4);
  histusdd->Draw();
  cus->SaveAs(Form("asym_us_correct_run%d.pdf",runNo));
  TCanvas *cds = new TCanvas("cds","cds",1000,1000);
  cds->Divide(2,2);
  cds->cd(1);
  histdsl->Draw();

  cds->cd(2);
  histdsr->Draw();
  
  cds->cd(3);
  histdsavg->Draw();
  
  cds->cd(4);
  histdsdd->Draw();
cds->SaveAs(Form("asym_ds_correct_run%d.pdf",runNo));
 //gSystem->Exec("pdfunite *_correct.pdf all.pdf");
// gSystem->Exec("rm -rf *_correct.pdf");

  }
