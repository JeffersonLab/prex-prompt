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
#include <vector>
#include <string.h>
#include <TEntryList.h>
#include <TTreeReader.h>
using namespace std; 

class TF1 *f1trap[42];
int japan_plot_beammod_Sam_cyc(string inputfile_name){ 
  //gStyle->SetOptStat(0);
  gStyle->SetOptFit();
  int filenum=1;
  if (inputfile_name.find("_",0) != string::npos) {
    filenum=atof(inputfile_name.substr(inputfile_name.find("_")+1,inputfile_name.find("_")).c_str());
    cout << "run num " << filenum <<"  "<< "make sure this is run for the beam modulation" <<  endl;
  }else{
    cout << "this file has no run number, please check the file name" << endl;
  }
  ostringstream sstr0,sstr1,sstr2,sstr3,sstr4,sstr5,sstr6,sstr7,sstr8,sstr9,sstr10,sstr11,sstr12,sstr13;
  sstr0<<"samtrim1_run"<<filenum<<".txt";
  ofstream outfile0(sstr0.str().c_str());
  sstr1<<"samtrim2_run"<<filenum<<".txt";
  ofstream outfile1(sstr1.str().c_str());
  sstr2<<"samtrim3_run"<<filenum<<".txt";
  ofstream outfile2(sstr2.str().c_str());
  sstr3<<"samtrim4_run"<<filenum<<".txt";
  ofstream outfile3(sstr3.str().c_str());
  sstr4<<"samtrim5_run"<<filenum<<".txt";
  ofstream outfile4(sstr4.str().c_str());
  sstr5<<"samtrim6_run"<<filenum<<".txt";
  ofstream outfile5(sstr5.str().c_str());
  sstr6<<"samtrim7_run"<<filenum<<".txt";
  ofstream outfile6(sstr6.str().c_str());

  sstr0.str("");
  sstr1.str("");
  sstr2.str("");
  sstr3.str("");
  sstr4.str("");
  sstr5.str("");
  sstr6.str("");
  sstr7.str("");

  TFile *file1=new TFile(inputfile_name.c_str());
  TGraphErrors *test;
  TTree *tree_R = (TTree*) file1->Get("evt");
  Double_t        CodaEventNumber;
  Double_t        bpm4eX_hw_sum;
  Double_t        bpm4eY_hw_sum;
  Double_t        bpm4aX_hw_sum;
  Double_t        bpm4aY_hw_sum;
  Double_t        bcm_an_us_hw_sum;
  Double_t        bcm_an_ds3_hw_sum;
  Double_t        bcm_an_ds_hw_sum;
  Double_t        bcm_an_ds;
  Double_t        bcm_an_us;
  Double_t        bcm_an_ds3;
  Double_t        ErrorFlag;
  Double_t        sam1_hw_sum;
  Double_t        sam2_hw_sum;
  Double_t        sam3_hw_sum;
  Double_t        sam4_hw_sum;
  Double_t        sam5_hw_sum;
  Double_t        sam6_hw_sum;
  Double_t        sam7_hw_sum;
  Double_t        sam8_hw_sum;
  Double_t        bmwphase;
  Double_t        bmwperiod;
  Double_t        bmwobj;
  Double_t        bmwfreq;
  Double_t        bmwcycnum;
  Double_t        bmod_trim1_value;
  Double_t        bmod_trim2_value;
  Double_t        bmod_trim3_value;
  Double_t        bmod_trim4_value;
  Double_t        bmod_trim5_value;
  Double_t        bmod_trim6_value;
  Double_t        bmod_trim7_value;
  Double_t        bmod_trim8_value;
  TBranch        *b_CodaEventNumber;
  TBranch        *b_cav4bx;   //!
  TBranch        *b_cav4by;   //!
  TBranch        *b_cav4bq;   //!
  TBranch        *b_cav4cx;   //!
  TBranch        *b_cav4cy;   //!
  TBranch        *b_cav4cq;   //!
  TBranch        *b_qwk_3_6;   //!
  TBranch        *b_unser;   //!
  TBranch        *b_bpm4aX;   //!
  TBranch        *b_bpm4aY;   //!
  TBranch        *b_bpm4eX;   //!
  TBranch        *b_bpm4eY;   //!
  TBranch        *b_bcm_an_us;   //!
  TBranch        *b_bcm_an_ds;   //!
  TBranch        *b_bcm_an_ds3;   //!
  TBranch        *b_sam1;   //!
  TBranch        *b_sam2;   //!
  TBranch        *b_sam3;   //!
  TBranch        *b_sam4;   //!
  TBranch        *b_sam5;   //!
  TBranch        *b_sam6;   //!
  TBranch        *b_sam7;   //!
  TBranch        *b_sam8;   //
  TBranch        *b_bmod_trim1;   //!
  TBranch        *b_bmod_trim2;   //!
  TBranch        *b_bmod_trim3;   //!
  TBranch        *b_bmod_trim4;   //!
  TBranch        *b_bmod_trim5;   //!
  TBranch        *b_bmod_trim6;   //!
  TBranch        *b_bmod_trim7;   //!
  TBranch        *b_bmod_trim8;   //!
  
  TBranch        *b_bmwphase;   //!
  TBranch        *b_bmwperiod;   //!
  TBranch        *b_bmwobj;   //!cavity_japan_plot_beammod_1473_samcheck1.C
  TBranch        *b_bmwfreq;   //!
  TBranch        *b_bmwcycnum;   //!
  
  TBranch        *b_ErrorFlag;
  tree_R->SetBranchAddress("CodaEventNumber", &CodaEventNumber, &b_CodaEventNumber);
  tree_R->SetBranchAddress("ErrorFlag", &ErrorFlag, &b_ErrorFlag);
  tree_R->SetBranchAddress("bpm4aX", &bpm4aX_hw_sum, &b_bpm4aX);
  tree_R->SetBranchAddress("bpm4aY", &bpm4aY_hw_sum, &b_bpm4aY);
  tree_R->SetBranchAddress("bpm4eX", &bpm4eX_hw_sum, &b_bpm4eX);
  tree_R->SetBranchAddress("bpm4eY", &bpm4eY_hw_sum, &b_bpm4eY);
  tree_R->SetBranchAddress("bcm_an_us", &bcm_an_us_hw_sum, &b_bcm_an_us);
  tree_R->SetBranchAddress("bcm_an_ds", &bcm_an_ds_hw_sum, &b_bcm_an_ds);
  tree_R->SetBranchAddress("bcm_an_ds3", &bcm_an_ds3_hw_sum, &b_bcm_an_ds3);
  tree_R->SetBranchAddress("sam1", &sam1_hw_sum, &b_sam1);
  tree_R->SetBranchAddress("sam2", &sam2_hw_sum, &b_sam2);
  tree_R->SetBranchAddress("sam3", &sam3_hw_sum, &b_sam3);
  tree_R->SetBranchAddress("sam4", &sam4_hw_sum, &b_sam4);
  tree_R->SetBranchAddress("sam5", &sam5_hw_sum, &b_sam5);
  tree_R->SetBranchAddress("sam6", &sam6_hw_sum, &b_sam6);
  tree_R->SetBranchAddress("sam7", &sam7_hw_sum, &b_sam7);
  tree_R->SetBranchAddress("sam8", &sam8_hw_sum, &b_sam8);
  
  
  tree_R->SetBranchAddress("bmwphase", &bmwphase, &b_bmwphase);
  tree_R->SetBranchAddress("bmwperiod", &bmwperiod, &b_bmwperiod);
  tree_R->SetBranchAddress("bmwobj", &bmwobj, &b_bmwobj);
  tree_R->SetBranchAddress("bmwfreq", &bmwfreq, &b_bmwfreq);
  tree_R->SetBranchAddress("bmwcycnum", &bmwcycnum, &b_bmwcycnum);
  tree_R->SetBranchAddress("bmod_trim1", &bmod_trim1_value, &b_bmod_trim1);
  tree_R->SetBranchAddress("bmod_trim2", &bmod_trim2_value, &b_bmod_trim2);
  tree_R->SetBranchAddress("bmod_trim3", &bmod_trim3_value, &b_bmod_trim3);
  tree_R->SetBranchAddress("bmod_trim4", &bmod_trim4_value, &b_bmod_trim4);
  tree_R->SetBranchAddress("bmod_trim5", &bmod_trim5_value, &b_bmod_trim5);
  tree_R->SetBranchAddress("bmod_trim6", &bmod_trim6_value, &b_bmod_trim6);
  tree_R->SetBranchAddress("bmod_trim7", &bmod_trim7_value, &b_bmod_trim7);

  tree_R->Draw(">>elist","bmwcycnum>0","entrylist");  //picks out unique cycle numbers
  TEntryList *elist = (TEntryList*)gDirectory->Get("elist");
  tree_R->SetEntryList(elist);
  TLeaf *l_bmwcycnum = tree_R->GetLeaf("bmwcycnum");
  int nonzero = tree_R->Draw("bmwcycnum","bmwcycnum>0","goff");
  vector<Double_t> cycles;
  for(int i=0;i<nonzero;i++){
    l_bmwcycnum->GetBranch()->GetEntry(elist->GetEntry(i));
    Double_t cyclenum = l_bmwcycnum->GetValue();
    if(i==0){
      cycles.push_back(cyclenum);
    }    
    else{
      int sizeVec = cycles.size();
      if(cyclenum != cycles[sizeVec-1]){
	cycles.push_back(cyclenum);
      }
    }    
  }    

  int n=cycles.size();
                  
  Double_t supercyc[n];
  for(int i=0;i<n;i++){
    supercyc[i]=cycles[i]; 
    cout<<"i="<<i<<"  "<<"supercyc="<<supercyc[i]<<endl;
  }    
  Double_t supercycslope[n];
  Double_t supercyc_err[n];
  for(int i=0;i<n;i++ ){
    supercycslope[i]=/*filenum*100+*/supercyc[i];
    supercyc_err[i]=0;
    cout<<"supercycslope="<<supercycslope[i]<<endl;
  }


  Double_t trim_base[7] = {6831,6730,6967,6820,6690,6870,6830};
  Double_t trim_obj[7] = {1,2,3,4,5,6,7};

  const double trimmin=0.38;
  const double trimmax=0.7;
  const double bpmmax=3;
  const double bpmmin=1;
  const double chtov=7.62939453125000000e-05;
  const double factor = 1000.0;
  Double_t coil_slop[8][8];
  Double_t coil_slop_err[8][8];
  Double_t trim1_slop[8][n];
  Double_t trim1_slop_err[8][n];
  Double_t trim2_slop[8][n];
  Double_t trim2_slop_err[8][n];
  Double_t trim3_slop[8][n];
  Double_t trim3_slop_err[8][n];
  Double_t trim4_slop[8][n];
  Double_t trim4_slop_err[8][n];
  Double_t trim5_slop[8][n];
  Double_t trim5_slop_err[8][n];
  Double_t trim6_slop[8][n];
  Double_t trim6_slop_err[8][n];
  Double_t trim7_slop[8][n];
  Double_t trim7_slop_err[8][n];
  Double_t trim8_slop[8][n];
  Double_t trim8_slop_err[8][n]; 
  TGraphErrors *slopx[8];
  TGraphErrors *slopy[8];
  TGraphErrors *rslopx[8];
  TGraphErrors *rslopy[8];
  double meany_coil1[8];
  double meany_coil2[8];
  double meany_coil3[8];
  double meany_coil4[8];
  double meany_coil5[8];
  double meany_coil6[8];
  double meany_coil7[8];
  double meany_coil8[8];
  double meany_coil1_cyc[8][n];
  double meany_coil2_cyc[8][n];
  double meany_coil3_cyc[8][n];
  double meany_coil4_cyc[8][n];
  double meany_coil5_cyc[8][n];
  double meany_coil6_cyc[8][n];
  double meany_coil7_cyc[8][n];



  TGraph * hist_4ax_coil[8];
  TGraph * hist_trim3_normalized[8];
  TGraph * hist_4ex_coil[8];
  TGraph * hist_trim2_normalized[8];
  TGraph * hist_4ay_coil[8];
  TGraph * hist_trim4_normalized[8];
  TGraph * hist_4ey_coil[8];
  TGraph * hist_trim5_normalized[8];
  TH2F * hist_cyc_coil[8];
  TH1F * trim_hist[8];
  TH2F * hist[8];
  TH1F * sam_hist[8];
  TGraph * hist_4ad_coil[8];
  TGraph * hist_trim6_normalized[8];
  TGraph * hist_4ed_coil[8];
  TGraph * hist_trim7_normalized[8];
  TGraph * hist_4cd_coil[8];
  TGraph * hist_trim8_normalized[8];
  TGraph * hist_4dd_coil[8];
  TGraph * hist_trim1_normalized[8];

  TCanvas *c[8];
  TGraph * hist_coil1_normalized[8];
  TGraph * hist_coil2_normalized[8];
  TGraph * hist_coil3_normalized[8];
  TGraph * hist_coil4_normalized[8];
  TGraph * hist_coil5_normalized[8];
  TGraph * hist_coil6_normalized[8];
  TGraph * hist_coil7_normalized[8];
  TGraph * hist_coil8_normalized[8];

  TH2F * hist_ratioX_coil[8];
  TH2F * hist_ratioY_coil[8];
  TH2F * hist_4ax_coil5_cyc[n];
  TH2F * hist_4ax_coil5_cyc_clone[n];
  TH2F * hist_4ex_coil5_cyc[n];
  TH2F * hist_4ax_coil1_cyc[n];
  TH2F * hist_4ex_coil1_cyc[n];
  TH2F * hist_4ax_coil3_cyc[n];
  TH2F * hist_4ex_coil3_cyc[n];
  TH2F * hist_4ax_coil6_cyc[n];
  TH2F * hist_4ex_coil6_cyc[n];
  
  TH2F * hist_4ay_coil2_cyc[n];
  TH2F * hist_4ey_coil2_cyc[n];
  TH2F * hist_4ay_coil4_cyc[n];
  TH2F * hist_4ey_coil4_cyc[n];
  TH2F * hist_4ay_coil7_cyc[n];
  TH2F * hist_4ey_coil7_cyc[n];
  TH2F * hist_sam2_cyc[8][n];
  TGraph * gtrim1[8][n];
  TGraph * gtrim2[8][n];
  TGraph * gtrim3[8][n];
  TGraph * gtrim3_cyc[8][n];
  TGraph * gtrim4[8][n];
  TGraph * gtrim5[8][n];
  TGraph * gtrim6[8][n];
  TGraph * gtrim7[8][n];
  TGraph * gtrim8[8][n]; 
  TF1 *fun = new TF1("fun","[0]+[1]*x",0.3,0.7);  
  TF1 *funsloptrim1[8][n];
  TF1 *funsloptrim2[8][n];
  TF1 *funsloptrim3[8][n];
  TF1 *funsloptrim4[8][n];
  TF1 *funsloptrim5[8][n];
  TF1 *funsloptrim6[8][n];
  TF1 *funsloptrim7[8][n];
  TF1 *funsloptrim8[8][n];
  TF1 *funtest[8][n];

  TF1 *funcoil[8][8];
  char name_coil[50];
  TCanvas *trim2_sam[9];
  TCanvas *trim3_sam[9];
  TCanvas *trim4_sam[9];
  TCanvas *trim5_sam[9];
  TCanvas *trim6_sam[9];
  TCanvas *trim7_sam[9];
  TCanvas *trim8_sam[9];
  int entrysam_coil[2][8];
  int entry_coil[8][8];
  char name_trim1[50];
  char name_trim2[50];
  char name_trim3[50];
  char name_trim4[50];
  char name_trim5[50];
  char name_trim6[50];
  char name_trim7[50];
  char name_trim8[50];
  char name_test[50];
  for(int j=0;j<8;j++){
 
    for(int i=0;i<8;i++){
      sprintf(name_coil,"funcoil%d_sam%d",j,i);
      funcoil[j][i]= new TF1(name_coil,"[0]+[1]*x",0,0.01);
    }
    for(int i=0;i<n;i++){
      
      sprintf(name_trim1,"funsloptrim1_sam%d_cyc%d",j,i);
      sprintf(name_trim2,"funsloptrim2_sam%d_cyc%d",j,i);
      sprintf(name_trim3,"funsloptrim3_sam%d_cyc%d",j,i);
      sprintf(name_trim4,"funsloptrim4_sam%d_cyc%d",j,i);
      sprintf(name_trim5,"funsloptrim5_sam%d_cyc%d",j,i);
      sprintf(name_trim6,"funsloptrim6_sam%d_cyc%d",j,i);
      sprintf(name_trim7,"funsloptrim7_sam%d_cyc%d",j,i);
      sprintf(name_trim8,"funsloptrim8_sam%d_cyc%d",j,i);
      sprintf(name_test,"funsloptest_sam%d_cyc%d",j,i);
      funsloptrim1[j][i]= new TF1(name_trim1,"[0]+[1]*x",0.35,0.6);
      funsloptrim2[j][i]= new TF1(name_trim2,"[0]+[1]*x",0.35,0.6);
      funsloptrim3[j][i]= new TF1(name_trim3,"[0]+[1]*x",0.35,0.6);
      funsloptrim4[j][i]= new TF1(name_trim4,"[0]+[1]*x",0.35,0.6);
      funsloptrim5[j][i]= new TF1(name_trim5,"[0]+[1]*x",0.35,0.6);
      funsloptrim6[j][i]= new TF1(name_trim6,"[0]+[1]*x",0.35,0.6);
      funsloptrim7[j][i]= new TF1(name_trim7,"[0]+[1]*x",0.35,0.6);
      funsloptrim8[j][i]= new TF1(name_trim8,"[0]+[1]*x",0.35,0.6);
      funtest[j][i]= new TF1(name_test,"[0]+[1]*x",0.35,0.6);
    }
  }
  int xnbins=0.0;
  int ynbins=0;
  double ibincon=0;
  int ibin=0;
  double xbincon=0.0;
  int coilnum=0;
  TH2F *hist_bcm_ds;
  TH2F *hist_bcm_us;
  // tree_R->Draw("bpm4ax.block0:Entry$"," bcm_an_ds3>5.32&& bcm_an_ds3<5.55&& bmwobj==5 && bmwcycnum==16");
  tree_R->Draw("bcm_an_ds:CodaEventNumber>>hist_bcm_ds","bcm_an_ds3>5.32&& bcm_an_ds3<5.55");
  hist_bcm_ds= (TH2F *)gDirectory->Get("hist_bcm_ds");
  tree_R->Draw("bcm_an_us:CodaEventNumber>>hist_bcm_us","bcm_an_ds3>5.32&& bcm_an_ds3<5.55");
  hist_bcm_us= (TH2F *)gDirectory->Get("hist_bcm_us");
  TString wire[7]={"bmod_trim1","bmod_trim2","bmod_trim3","bmod_trim4","bmod_trim5","bmod_trim6","bmod_trim7"};
  TString sam_wire[8]={"sam1","sam2","sam3","sam4","sam5","sam6","sam7","sam8"};
  for(int i=0;i<8;i++){
    int num_trim3 = tree_R->Draw(Form("(bmod_trim3*%lf):(%s)",chtov,sam_wire[i].Data()),Form("bcm_an_ds3>5.32&& bcm_an_ds3<5.55 && bmwobj==3 && abs(bmod_trim3-%f)>20",trim_base[2]));
    hist_4ax_coil[i]= new TGraph(num_trim3, tree_R->GetV1(),tree_R->GetV2());
    hist_4ax_coil[i]->SetMarkerStyle(20);
    hist_4ax_coil[i]->SetMarkerSize(2);
    hist_4ax_coil[i]->GetYaxis()->SetTitle(Form("%s/bcm",sam_wire[i].Data()));
    hist_4ax_coil[i]->GetXaxis()->SetTitle("trim3 [V]");
    hist_4ax_coil[i]->GetXaxis()->SetTitleSize(0.05);
    hist_4ax_coil[i]->GetYaxis()->SetTitleSize(0.05);
    meany_coil3[i]= hist_4ax_coil[i]->GetMean(2);
    int num_trim2 = tree_R->Draw(Form("(bmod_trim2*%lf):(%s)",chtov,sam_wire[i].Data()),Form("bcm_an_ds3>5.32&& bcm_an_ds3<5.55 && bmwobj==2 && abs(bmod_trim2-%f)>20",trim_base[1]));
    hist_4ex_coil[i]= new TGraph(num_trim2, tree_R->GetV1(),tree_R->GetV2()); 
    hist_4ex_coil[i]->SetMarkerStyle(20);
    hist_4ex_coil[i]->SetMarkerSize(2);
    hist_4ex_coil[i]->GetXaxis()->SetTitle(Form("%s/bcm",sam_wire[i].Data()));
    hist_4ex_coil[i]->GetYaxis()->SetTitle("trim2 [V]");
    hist_4ex_coil[i]->GetXaxis()->SetTitleSize(0.05);
    hist_4ex_coil[i]->GetYaxis()->SetTitleSize(0.05);
    meany_coil2[i]= hist_4ex_coil[i]->GetMean(2);
    int num_trim4 = tree_R->Draw(Form("(bmod_trim4*%lf):(%s)",chtov,sam_wire[i].Data()),Form("bcm_an_ds3>5.32&& bcm_an_ds3<5.55 && bmwobj==4 && abs(bmod_trim4-%f)>20",trim_base[3]));
    hist_4ay_coil[i]= new TGraph(num_trim4, tree_R->GetV1(),tree_R->GetV2()); 
    hist_4ay_coil[i]->SetMarkerStyle(20);
    hist_4ay_coil[i]->SetMarkerSize(2);
    hist_4ay_coil[i]->GetXaxis()->SetTitle(Form("%s/bcm",sam_wire[i].Data()));
    hist_4ay_coil[i]->GetYaxis()->SetTitle("trim4 [V]");
    hist_4ay_coil[i]->GetXaxis()->SetTitleSize(0.05);
    hist_4ay_coil[i]->GetYaxis()->SetTitleSize(0.05);
    meany_coil4[i]= hist_4ay_coil[i]->GetMean(2);
    
    int num_trim5 = tree_R->Draw(Form("(bmod_trim5*%lf):(%s)",chtov,sam_wire[i].Data()),Form("bcm_an_ds3>5.32&& bcm_an_ds3<5.55 && bmwobj==5 && abs(bmod_trim5-%f)>20",trim_base[4]));
    hist_4ey_coil[i]= new TGraph(num_trim5, tree_R->GetV1(),tree_R->GetV2()); 
    hist_4ey_coil[i]->SetMarkerStyle(20);
    hist_4ey_coil[i]->SetMarkerSize(2);
    hist_4ey_coil[i]->GetXaxis()->SetTitle(Form("%s/bcm",sam_wire[i].Data()));
    hist_4ey_coil[i]->GetYaxis()->SetTitle("trim5 [V]");
    hist_4ey_coil[i]->GetXaxis()->SetTitleSize(0.05);
    hist_4ey_coil[i]->GetYaxis()->SetTitleSize(0.05);
    meany_coil5[i]= hist_4ey_coil[i]->GetMean(2);
    int num_trim6 = tree_R->Draw(Form("(bmod_trim6*%lf):(%s)",chtov,sam_wire[i].Data()),Form("bcm_an_ds3>5.32&& bcm_an_ds3<5.55 && bmwobj==6 && abs(bmod_trim6-%f)>20",trim_base[5]));
    hist_4ed_coil[i]= new TGraph(num_trim6, tree_R->GetV1(),tree_R->GetV2()); 
    hist_4ed_coil[i]->SetMarkerStyle(20);
    hist_4ed_coil[i]->SetMarkerSize(2);
    hist_4ed_coil[i]->GetXaxis()->SetTitle(Form("%s/bcm",sam_wire[i].Data()));
    hist_4ed_coil[i]->GetYaxis()->SetTitle("trim6 [V]");
    hist_4ed_coil[i]->GetXaxis()->SetTitleSize(0.05);
    hist_4ed_coil[i]->GetYaxis()->SetTitleSize(0.05); 
    meany_coil6[i]= hist_4ed_coil[i]->GetMean(2);
    int num_trim7 = tree_R->Draw(Form("(bmod_trim7*%lf):(%s)",chtov,sam_wire[i].Data()),Form("bcm_an_ds3>5.32&& bcm_an_ds3<5.55 && bmwobj==7 && abs(bmod_trim7-%f)>20",trim_base[6]));
    hist_4ad_coil[i]= new TGraph(num_trim7, tree_R->GetV1(),tree_R->GetV2()); 
    hist_4ad_coil[i]->SetMarkerStyle(20);
    hist_4ad_coil[i]->SetMarkerSize(2);
    hist_4ad_coil[i]->GetXaxis()->SetTitle(Form("%s/bcm",sam_wire[i].Data()));
    hist_4ad_coil[i]->GetYaxis()->SetTitle("trim7");
    hist_4ad_coil[i]->GetXaxis()->SetTitleSize(0.05);
    hist_4ad_coil[i]->GetYaxis()->SetTitleSize(0.05);  
    meany_coil7[i]= hist_4ad_coil[i]->GetMean(2);
    int num_trim1 = tree_R->Draw(Form("(bmod_trim1*%lf):(%s)",chtov,sam_wire[i].Data()),Form("bcm_an_ds3>5.32&& bcm_an_ds3<5.55 && bmwobj==1 && abs(bmod_trim1-%f)>20",trim_base[0]));
    hist_4dd_coil[i]= new TGraph(num_trim1, tree_R->GetV1(),tree_R->GetV2()); 
    hist_4dd_coil[i]->SetMarkerStyle(20);
    hist_4dd_coil[i]->SetMarkerSize(2);
    hist_4dd_coil[i]->GetXaxis()->SetTitle(Form("%s/bcm",sam_wire[i].Data()));
    hist_4dd_coil[i]->GetYaxis()->SetTitle("trim1");
    hist_4dd_coil[i]->GetXaxis()->SetTitleSize(0.05);
    hist_4dd_coil[i]->GetYaxis()->SetTitleSize(0.05);
    meany_coil1[i]= hist_4dd_coil[i]->GetMean(2);
  }
  // super cycle analysis 
  for(int j=0;j<8;j++){
    for(int i=0;i<n;i++){
      tree_R->Draw(Form("(%s/bcm_an_ds):(bmod_trim3)>>hist_sam2_cyc%d%d",sam_wire[j].Data(),j,i),Form("bcm_an_ds3>5.32&& bcm_an_ds3<5.55 && bmwobj==3 && abs(bmod_trim3-%f)>20 && bmwcycnum==%f",trim_base[2],supercyc[i]));
      hist_sam2_cyc[j][i] = (TH2F *)gDirectory->Get(Form("hist_sam2_cyc%d%d",j,i));
      hist_sam2_cyc[j][i]->SetMarkerStyle(20);
      hist_sam2_cyc[j][i]->SetMarkerSize(2);
      hist_sam2_cyc[j][i]->GetXaxis()->SetTitle("bmwcoil [v]");
      hist_sam2_cyc[j][i]->GetYaxis()->SetTitle("sam/bcm_an_us");
      hist_sam2_cyc[j][i]->GetXaxis()->SetTitleSize(0.05);
      hist_sam2_cyc[j][i]->GetYaxis()->SetTitleSize(0.05);
      int npt = tree_R->Draw(Form("(bmod_trim3*%lf):(%s)",chtov,sam_wire[j].Data()),Form("bcm_an_ds3>5.32&& bcm_an_ds3<5.55 && bmwobj==3 && abs(bmod_trim3-%f)>20 && bmwcycnum==%f",trim_base[2],supercyc[i]));
      gtrim3[j][i]= new TGraph(npt, tree_R->GetV1(),tree_R->GetV2()); 
      gtrim3[j][i]->SetMarkerStyle(20);
      gtrim3[j][i]->SetMarkerSize(2);
      gtrim3[j][i]->SetMarkerColor(1);    
      int npa = tree_R->Draw(Form("(bmod_trim1*%lf):(%s)",chtov,sam_wire[j].Data()),Form("bcm_an_ds3>5.32&& bcm_an_ds3<5.55 && bmwobj==1 && abs(bmod_trim1-%f)>20 && bmwcycnum==%f",trim_base[0],supercyc[i]));
      gtrim1[j][i]= new TGraph(npa, tree_R->GetV1(),tree_R->GetV2()); 
      gtrim1[j][i]->SetMarkerStyle(20);
      gtrim1[j][i]->SetMarkerSize(2);
      gtrim1[j][i]->SetMarkerColor(1);
      int npb = tree_R->Draw(Form("(bmod_trim2*%lf):(%s)",chtov,sam_wire[j].Data()),Form("bcm_an_ds3>5.32&& bcm_an_ds3<5.55 && bmwobj==2 && abs(bmod_trim2-%f)>20 && bmwcycnum==%f",trim_base[1],supercyc[i]));
      gtrim2[j][i]= new TGraph(npb, tree_R->GetV1(),tree_R->GetV2()); 
      gtrim2[j][i]->SetMarkerStyle(20);
      gtrim2[j][i]->SetMarkerSize(2);
      gtrim2[j][i]->SetMarkerColor(1);
      int npc = tree_R->Draw(Form("(bmod_trim4*%lf):(%s)",chtov,sam_wire[j].Data()),Form("bcm_an_ds3>5.32&& bcm_an_ds3<5.55 && bmwobj==4 && abs(bmod_trim4-%f)>20 && bmwcycnum==%f",trim_base[3],supercyc[i]));
      gtrim4[j][i]= new TGraph(npc, tree_R->GetV1(),tree_R->GetV2()); 
      gtrim4[j][i]->SetMarkerStyle(20);
      gtrim4[j][i]->SetMarkerSize(2);
      gtrim4[j][i]->SetMarkerColor(1);
      
      int npd = tree_R->Draw(Form("(bmod_trim5*%lf):(%s)",chtov,sam_wire[j].Data()),Form("bcm_an_ds3>5.32&& bcm_an_ds3<5.55 && bmwobj==5 && abs(bmod_trim5-%f)>20 && bmwcycnum==%f",trim_base[4],supercyc[i]));
      gtrim5[j][i]= new TGraph(npd, tree_R->GetV1(),tree_R->GetV2()); 
      gtrim5[j][i]->SetMarkerStyle(20);
      gtrim5[j][i]->SetMarkerSize(2);
      gtrim5[j][i]->SetMarkerColor(1);
      int npe = tree_R->Draw(Form("(bmod_trim6*%lf):(%s)",chtov,sam_wire[j].Data()),Form("bcm_an_ds3>5.32&& bcm_an_ds3<5.55 && bmwobj==6 && abs(bmod_trim6-%f)>20 && bmwcycnum==%f",trim_base[5],supercyc[i]));
      gtrim6[j][i]= new TGraph(npe, tree_R->GetV1(),tree_R->GetV2()); 
      gtrim6[j][i]->SetMarkerStyle(20);
      gtrim6[j][i]->SetMarkerSize(2);
      gtrim6[j][i]->SetMarkerColor(1);
      int npf = tree_R->Draw(Form("(bmod_trim7*%lf):(%s)",chtov,sam_wire[j].Data()),Form("bcm_an_ds3>5.32&& bcm_an_ds3<5.55 && bmwobj==7 && abs(bmod_trim7-%f)>20 && bmwcycnum==%f",trim_base[6],supercyc[i]));
      gtrim7[j][i]= new TGraph(npf, tree_R->GetV1(),tree_R->GetV2()); 
      gtrim7[j][i]->SetMarkerStyle(20);
      gtrim7[j][i]->SetMarkerSize(2);
      gtrim7[j][i]->SetMarkerColor(1);
      
    }
  }

  // Normalized sam
  for(int i=0;i<8;i++){
    tree_R->Draw(Form("(bmod_trim3*%lf):(%s/%lf)>>hist%d",chtov,sam_wire[i].Data(),meany_coil3[i],i),Form("bcm_an_ds3>5.32&& bcm_an_ds3<5.55 && bmwobj==3 && abs(bmod_trim3-%f)>20",trim_base[2]));
    hist[i] = (TH2F *)gDirectory->Get(Form("hist%d",i));
    int num_trim3 = tree_R->Draw(Form("(bmod_trim3*%lf):(%s/%lf)",chtov,sam_wire[i].Data(),meany_coil3[i]),Form("bcm_an_ds3>5.32&& bcm_an_ds3<5.55 && bmwobj==3 && abs(bmod_trim3-%f)>20",trim_base[2]));
    hist_coil3_normalized[i]= new TGraph(num_trim3, tree_R->GetV1(),tree_R->GetV2());
    hist_coil3_normalized[i]->SetMarkerStyle(20);
    hist_coil3_normalized[i]->SetMarkerSize(2);
    hist_coil3_normalized[i]->GetYaxis()->SetTitle(Form("%s/mean",sam_wire[i].Data()));
    hist_coil3_normalized[i]->GetXaxis()->SetTitle("trim3 [V]");
    hist_coil3_normalized[i]->GetXaxis()->SetTitleSize(0.05);
    hist_coil3_normalized[i]->GetYaxis()->SetTitleSize(0.05);
    int num_trim2 = tree_R->Draw(Form("(bmod_trim2*%lf):(%s/%lf)",chtov,sam_wire[i].Data(),meany_coil2[i]),Form("bcm_an_ds3>5.32&& bcm_an_ds3<5.55 && bmwobj==2 && abs(bmod_trim2-%f)>20",trim_base[1]));
    hist_coil2_normalized[i]= new TGraph(num_trim2, tree_R->GetV1(),tree_R->GetV2()); 
    hist_coil2_normalized[i]->SetMarkerStyle(20);
    hist_coil2_normalized[i]->SetMarkerSize(2);
    hist_coil2_normalized[i]->GetXaxis()->SetTitle(Form("%s/mean",sam_wire[i].Data()));
    hist_coil2_normalized[i]->GetYaxis()->SetTitle("trim2 [V]");
    hist_coil2_normalized[i]->GetXaxis()->SetTitleSize(0.05);
    hist_coil2_normalized[i]->GetYaxis()->SetTitleSize(0.05);
    
    int num_trim4 = tree_R->Draw(Form("(bmod_trim4*%lf):(%s/%lf)",chtov,sam_wire[i].Data(),meany_coil4[i]),Form("bcm_an_ds3>5.32&& bcm_an_ds3<5.55 && bmwobj==4 && abs(bmod_trim4-%f)>20",trim_base[3]));
    hist_coil4_normalized[i]= new TGraph(num_trim4, tree_R->GetV1(),tree_R->GetV2()); 
    hist_coil4_normalized[i]->SetMarkerStyle(20);
    hist_coil4_normalized[i]->SetMarkerSize(2);
    hist_coil4_normalized[i]->GetXaxis()->SetTitle(Form("%s/mean",sam_wire[i].Data()));
    hist_coil4_normalized[i]->GetYaxis()->SetTitle("trim4 [V]");
    hist_coil4_normalized[i]->GetXaxis()->SetTitleSize(0.05);
    hist_coil4_normalized[i]->GetYaxis()->SetTitleSize(0.05);
    
    
    int num_trim5 = tree_R->Draw(Form("(bmod_trim5*%lf):(%s/%lf)",chtov,sam_wire[i].Data(),meany_coil5[i]),Form("bcm_an_ds3>5.32&& bcm_an_ds3<5.55 && bmwobj==5 && abs(bmod_trim5-%f)>20",trim_base[4]));
    hist_coil5_normalized[i]= new TGraph(num_trim5, tree_R->GetV1(),tree_R->GetV2()); 
    hist_coil5_normalized[i]->SetMarkerStyle(20);
    hist_coil5_normalized[i]->SetMarkerSize(2);
    hist_coil5_normalized[i]->GetXaxis()->SetTitle(Form("%s/mean",sam_wire[i].Data()));
    hist_coil5_normalized[i]->GetYaxis()->SetTitle("trim5 [V]");
    hist_coil5_normalized[i]->GetXaxis()->SetTitleSize(0.05);
    hist_coil5_normalized[i]->GetYaxis()->SetTitleSize(0.05);
    
    int num_trim6 = tree_R->Draw(Form("(bmod_trim6*%lf):(%s/%lf)",chtov,sam_wire[i].Data(),meany_coil6[i]),Form(" bcm_an_ds3>5.32&& bcm_an_ds3<5.55 && bmwobj==6 && abs(bmod_trim6-%f)>20",trim_base[5]));
    hist_coil6_normalized[i]= new TGraph(num_trim6, tree_R->GetV1(),tree_R->GetV2()); 
    hist_coil6_normalized[i]->SetMarkerStyle(20);
    hist_coil6_normalized[i]->SetMarkerSize(2);
    hist_coil6_normalized[i]->GetXaxis()->SetTitle(Form("%s/mean",sam_wire[i].Data()));
    hist_coil6_normalized[i]->GetYaxis()->SetTitle("trim6 [V]");
    hist_coil6_normalized[i]->GetXaxis()->SetTitleSize(0.05);
    hist_coil6_normalized[i]->GetYaxis()->SetTitleSize(0.05); 
    
    int num_trim7 = tree_R->Draw(Form("(bmod_trim7*%lf):(%s/%lf)",chtov,sam_wire[i].Data(),meany_coil7[i]),Form(" bcm_an_ds3>5.32&& bcm_an_ds3<5.55 && bmwobj==7 && abs(bmod_trim7-%f)>20",trim_base[6]));
    hist_coil7_normalized[i]= new TGraph(num_trim7, tree_R->GetV1(),tree_R->GetV2()); 
    hist_coil7_normalized[i]->SetMarkerStyle(20);
    hist_coil7_normalized[i]->SetMarkerSize(2);
    hist_coil7_normalized[i]->GetXaxis()->SetTitle(Form("%s/mean",sam_wire[i].Data()));
    hist_coil7_normalized[i]->GetYaxis()->SetTitle("trim7");
    hist_coil7_normalized[i]->GetXaxis()->SetTitleSize(0.05);
    hist_coil7_normalized[i]->GetYaxis()->SetTitleSize(0.05);  
    
    
    int num_trim1 = tree_R->Draw(Form("(bmod_trim1*%lf):(%s/%lf)",chtov,sam_wire[i].Data(),meany_coil1[i]),Form(" bcm_an_ds3>5.32&& bcm_an_ds3<5.55 && bmwobj==1 && abs(bmod_trim1-%f)>20",trim_base[0]));
    hist_coil1_normalized[i]= new TGraph(num_trim1, tree_R->GetV1(),tree_R->GetV2()); 
    hist_coil1_normalized[i]->SetMarkerStyle(20);
    hist_coil1_normalized[i]->SetMarkerSize(2);
    hist_coil1_normalized[i]->GetXaxis()->SetTitle(Form("%s/mean",sam_wire[i].Data()));
    hist_coil1_normalized[i]->GetYaxis()->SetTitle("trim1");
    hist_coil1_normalized[i]->GetXaxis()->SetTitleSize(0.05);
    hist_coil1_normalized[i]->GetYaxis()->SetTitleSize(0.05);
  }

  TCanvas *ctest = new TCanvas("ctest","ctest",800,800);
  ctest->Divide(2,4);
  for(int i=0;i<8;i++){
    ctest->cd(i+1);
    hist[i]->Draw();
  }
  // Difference sami-sami+4
  //coil1
  meany_coil1[1]= hist_4dd_coil[1]->GetMean(2);
  meany_coil1[5]= hist_4dd_coil[5]->GetMean(2);
  int  num_trim1_26 = tree_R->Draw(Form("(bmod_trim1*%lf):(sam2/%lf-sam6/%lf)",chtov,meany_coil1[1],meany_coil1[5]),Form(" bcm_an_ds3>5.32&& bcm_an_ds3<5.55&& bmwobj==1 && abs(bmod_trim1-%f)>20",trim_base[0]));   
  hist_trim1_normalized[0]= new TGraph(num_trim1_26,tree_R->GetV1(),tree_R->GetV2());
  hist_trim1_normalized[0]->SetMarkerStyle(20);
  hist_trim1_normalized[0]->SetMarkerSize(2);
  hist_trim1_normalized[0]->GetYaxis()->SetTitle("Nsam2-Nsam6");
  hist_trim1_normalized[0]->GetXaxis()->SetTitle("trim1 [V]");
  meany_coil1[3]= hist_4dd_coil[3]->GetMean(2);
  meany_coil1[7]= hist_4dd_coil[7]->GetMean(2);
  int  num_trim1_48 = tree_R->Draw(Form("(bmod_trim1*%lf):(sam4/%lf-sam8/%lf)",chtov,meany_coil1[3],meany_coil1[7]),Form("bcm_an_ds3>5.32&& bcm_an_ds3<5.55 && bmwobj==1 && abs(bmod_trim1-%f)>20",trim_base[0]));
  hist_trim1_normalized[1]= new TGraph(num_trim1_48,tree_R->GetV1(),tree_R->GetV2());
  hist_trim1_normalized[1]->SetMarkerStyle(20);
  hist_trim1_normalized[1]->SetMarkerSize(2);
  hist_trim1_normalized[1]->GetYaxis()->SetTitle("Nsam4-Nsam8");
  hist_trim1_normalized[1]->GetXaxis()->SetTitle("trim1 [V]");

  //coil2
  meany_coil2[1]= hist_4ex_coil[1]->GetMean(2);
  meany_coil2[5]= hist_4ex_coil[5]->GetMean(2);
  
  int  num_trim2_26 = tree_R->Draw(Form("(bmod_trim2*%lf):(sam2/%lf-sam6/%lf)",chtov,meany_coil2[1],meany_coil2[5]),Form("bcm_an_ds3>5.32&& bcm_an_ds3<5.55 && bmwobj==2 && abs(bmod_trim2-%f)>20",trim_base[1]));   
  hist_trim2_normalized[0]= new TGraph(num_trim2_26,tree_R->GetV1(),tree_R->GetV2());
  hist_trim2_normalized[0]->SetMarkerStyle(20);
  hist_trim2_normalized[0]->SetMarkerSize(2);
  hist_trim2_normalized[0]->GetYaxis()->SetTitle("Nsam2-Nsam6");
  hist_trim2_normalized[0]->GetXaxis()->SetTitle("trim2 [V]");
  hist_trim2_normalized[0]->GetXaxis()->SetTitleSize(0.05);
  hist_trim2_normalized[0]->GetYaxis()->SetTitleSize(0.05);
  meany_coil2[3]= hist_4ex_coil[3]->GetMean(2);
  meany_coil2[7]= hist_4ex_coil[7]->GetMean(2);
  int  num_trim2_48 = tree_R->Draw(Form("(bmod_trim2*%lf):(sam4/%lf-sam8/%lf)",chtov,meany_coil2[3],meany_coil2[7]),Form("bcm_an_ds3>5.32&& bcm_an_ds3<5.55 && bmwobj==2 && abs(bmod_trim2-%f)>20",trim_base[1]));
  hist_trim2_normalized[1]= new TGraph(num_trim2_48,tree_R->GetV1(),tree_R->GetV2());
  hist_trim2_normalized[1]->SetMarkerStyle(20);
  hist_trim2_normalized[1]->SetMarkerSize(2);
  hist_trim2_normalized[1]->GetYaxis()->SetTitle("Nsam4-Nsam8");
  hist_trim2_normalized[1]->GetXaxis()->SetTitle("trim2 [V]");
  hist_trim2_normalized[1]->GetXaxis()->SetTitleSize(0.05);
  hist_trim2_normalized[1]->GetYaxis()->SetTitleSize(0.05);
  //coil3
  meany_coil3[1]= hist_4ax_coil[1]->GetMean(2);
  meany_coil3[5]= hist_4ax_coil[5]->GetMean(2);
  int  num_trim3_26 = tree_R->Draw(Form("(bmod_trim3*%lf):(sam2/%lf-sam6/%lf)",chtov,meany_coil3[1],meany_coil3[5]),Form("bcm_an_ds3>5.32&& bcm_an_ds3<5.55 && bmwobj==3 && abs(bmod_trim3-%f)>20",trim_base[2]));   
  hist_trim3_normalized[0]= new TGraph(num_trim3_26,tree_R->GetV1(),tree_R->GetV2());
  hist_trim3_normalized[0]->SetMarkerStyle(20);
  hist_trim3_normalized[0]->SetMarkerSize(2);
  hist_trim3_normalized[0]->GetYaxis()->SetTitle("Nsam2-Nsam6");
  hist_trim3_normalized[0]->GetXaxis()->SetTitle("trim3 [V]");
  hist_trim3_normalized[0]->GetXaxis()->SetTitleSize(0.05);
  hist_trim3_normalized[0]->GetYaxis()->SetTitleSize(0.05);
  meany_coil3[3]= hist_4ax_coil[3]->GetMean(2);
  meany_coil3[7]= hist_4ax_coil[7]->GetMean(2);
  int  num_trim3_48 = tree_R->Draw(Form("(bmod_trim3*%lf):(sam4/%lf-sam8/%lf)",chtov,meany_coil3[3],meany_coil3[7]),Form(" bcm_an_ds3>5.32&& bcm_an_ds3<5.55&& bmwobj==3 && abs(bmod_trim3-%f)>20",trim_base[2]));
  hist_trim3_normalized[1]= new TGraph(num_trim3_48,tree_R->GetV1(),tree_R->GetV2());
  hist_trim3_normalized[1]->SetMarkerStyle(20);
  hist_trim3_normalized[1]->SetMarkerSize(2);
  hist_trim3_normalized[1]->GetYaxis()->SetTitle("Nsam4-Nsam8");
  hist_trim3_normalized[1]->GetXaxis()->SetTitle("trim3 [V]");
  hist_trim3_normalized[1]->GetXaxis()->SetTitleSize(0.05);
  hist_trim3_normalized[1]->GetYaxis()->SetTitleSize(0.05);
  //coil4
  meany_coil4[1]= hist_4ay_coil[1]->GetMean(2);
  meany_coil4[5]= hist_4ay_coil[5]->GetMean(2);
  int  num_trim4_26 = tree_R->Draw(Form("(bmod_trim4*%lf):(sam2/%lf-sam6/%lf)",chtov,meany_coil4[1],meany_coil4[5]),Form(" bcm_an_ds3>5.32&& bcm_an_ds3<5.55&& bmwobj==4 && abs(bmod_trim4-%f)>20",trim_base[3]));   
  hist_trim4_normalized[0]= new TGraph(num_trim4_26,tree_R->GetV1(),tree_R->GetV2());
  hist_trim4_normalized[0]->SetMarkerStyle(20);
  hist_trim4_normalized[0]->SetMarkerSize(2);
  hist_trim4_normalized[0]->GetYaxis()->SetTitle("Nsam2-Nsam6");
  hist_trim4_normalized[0]->GetXaxis()->SetTitle("trim4 [V]");
  hist_trim4_normalized[0]->GetXaxis()->SetTitleSize(0.05);
  hist_trim4_normalized[0]->GetYaxis()->SetTitleSize(0.05);
  meany_coil4[3]= hist_4ay_coil[3]->GetMean(2);
  meany_coil4[7]= hist_4ay_coil[7]->GetMean(2);
  int  num_trim4_48 = tree_R->Draw(Form("(bmod_trim4*%lf):(sam4/%lf-sam8/%lf)",chtov,meany_coil4[3],meany_coil4[7]),Form("bcm_an_ds3>5.32&& bcm_an_ds3<5.55 && bmwobj==4 && abs(bmod_trim4-%f)>20",trim_base[3]));
  hist_trim4_normalized[1]= new TGraph(num_trim4_48,tree_R->GetV1(),tree_R->GetV2());
  hist_trim4_normalized[1]->SetMarkerStyle(20);
  hist_trim4_normalized[1]->SetMarkerSize(2);
  hist_trim4_normalized[1]->GetYaxis()->SetTitle("Nsam4-Nsam8");
  hist_trim4_normalized[1]->GetXaxis()->SetTitle("trim4 [V]");
  hist_trim4_normalized[1]->GetXaxis()->SetTitleSize(0.05);
  hist_trim4_normalized[1]->GetYaxis()->SetTitleSize(0.05);
  //coil5
  meany_coil5[1]= hist_4ey_coil[1]->GetMean(2);
  meany_coil5[5]= hist_4ey_coil[5]->GetMean(2);
  int  num_trim5_26 = tree_R->Draw(Form("(bmod_trim5*%lf):(sam2/%lf-sam6/%lf)",chtov,meany_coil5[1],meany_coil5[5]),Form("bcm_an_ds3>5.32&& bcm_an_ds3<5.55 && bmwobj==5 && abs(bmod_trim5-%f)>20",trim_base[4]));   
  hist_trim5_normalized[0]= new TGraph(num_trim5_26,tree_R->GetV1(),tree_R->GetV2());
  hist_trim5_normalized[0]->SetMarkerStyle(20);
  hist_trim5_normalized[0]->SetMarkerSize(2);
  hist_trim5_normalized[0]->GetYaxis()->SetTitle("Nsam2-Nsam6");
  hist_trim5_normalized[0]->GetXaxis()->SetTitle("trim5 [V]");
  hist_trim5_normalized[0]->GetXaxis()->SetTitleSize(0.05);
  hist_trim5_normalized[0]->GetYaxis()->SetTitleSize(0.05);
  meany_coil5[3]= hist_4ey_coil[3]->GetMean(2);
  meany_coil5[7]= hist_4ey_coil[7]->GetMean(2);
  int  num_trim5_48 = tree_R->Draw(Form("(bmod_trim5*%lf):(sam4/%lf-sam8/%lf)",chtov,meany_coil5[3],meany_coil5[7]),Form(" bcm_an_ds3>5.32&& bcm_an_ds3<5.55&& bmwobj==5 && abs(bmod_trim5-%f)>20",trim_base[4]));
  hist_trim5_normalized[1]= new TGraph(num_trim5_48,tree_R->GetV1(),tree_R->GetV2());
  hist_trim5_normalized[1]->SetMarkerStyle(20);
  hist_trim5_normalized[1]->SetMarkerSize(2);
  hist_trim5_normalized[1]->GetYaxis()->SetTitle("Nsam4-Nsam8");
  hist_trim5_normalized[1]->GetXaxis()->SetTitle("trim5 [V]");
  hist_trim5_normalized[1]->GetXaxis()->SetTitleSize(0.05);
  hist_trim5_normalized[1]->GetYaxis()->SetTitleSize(0.05);
  //coil6
  meany_coil6[1]= hist_4ed_coil[1]->GetMean(2);
  meany_coil6[5]= hist_4ed_coil[5]->GetMean(2);
  int  num_trim6_26 = tree_R->Draw(Form("(bmod_trim6*%lf):(sam2/%lf-sam6/%lf)",chtov,meany_coil6[1],meany_coil6[5]),Form(" bcm_an_ds3>5.32&& bcm_an_ds3<5.55&& bmwobj==6 && abs(bmod_trim6-%f)>20",trim_base[5]));   
  hist_trim6_normalized[0]= new TGraph(num_trim6_26,tree_R->GetV1(),tree_R->GetV2());
  hist_trim6_normalized[0]->SetMarkerStyle(20);
  hist_trim6_normalized[0]->SetMarkerSize(2);
  hist_trim6_normalized[0]->GetYaxis()->SetTitle("Nsam2-Nsam6");
  hist_trim6_normalized[0]->GetXaxis()->SetTitle("trim6 [V]");
  hist_trim6_normalized[0]->GetXaxis()->SetTitleSize(0.05);
  hist_trim6_normalized[0]->GetYaxis()->SetTitleSize(0.05);
  meany_coil6[3]= hist_4ed_coil[3]->GetMean(2);
  meany_coil6[7]= hist_4ed_coil[7]->GetMean(2);
  int  num_trim6_48 = tree_R->Draw(Form("(bmod_trim6*%lf):(sam4/%lf-sam8/%lf)",chtov,meany_coil6[3],meany_coil6[7]),Form("bcm_an_ds3>5.32&& bcm_an_ds3<5.55 && bmwobj==6 && abs(bmod_trim6-%f)>20",trim_base[5]));
  hist_trim6_normalized[1]= new TGraph(num_trim6_48,tree_R->GetV1(),tree_R->GetV2());
  hist_trim6_normalized[1]->SetMarkerStyle(20);
  hist_trim6_normalized[1]->SetMarkerSize(2);
  hist_trim6_normalized[1]->GetYaxis()->SetTitle("Nsam4-Nsam8");
  hist_trim6_normalized[1]->GetXaxis()->SetTitle("trim6 [V]");
  hist_trim6_normalized[1]->GetXaxis()->SetTitleSize(0.05);
  hist_trim6_normalized[1]->GetYaxis()->SetTitleSize(0.05);
  //coil7
  meany_coil7[1]= hist_4ad_coil[1]->GetMean(2);
  meany_coil7[5]= hist_4ad_coil[5]->GetMean(2);
  int  num_trim7_26 = tree_R->Draw(Form("(bmod_trim7*%lf):(sam2/%lf-sam6/%lf)",chtov,meany_coil7[1],meany_coil7[5]),Form(" bcm_an_ds3>5.32&& bcm_an_ds3<5.55 && bmwobj==7 && abs(bmod_trim7-%f)>20",trim_base[6]));   
  hist_trim7_normalized[0]= new TGraph(num_trim7_26,tree_R->GetV1(),tree_R->GetV2());
  hist_trim7_normalized[0]->SetMarkerStyle(20);
  hist_trim7_normalized[0]->SetMarkerSize(2);
  hist_trim7_normalized[0]->GetYaxis()->SetTitle("Nsam2-Nsam6");
  hist_trim7_normalized[0]->GetXaxis()->SetTitle("trim7 [V]");
  hist_trim7_normalized[0]->GetXaxis()->SetTitleSize(0.05);
  hist_trim7_normalized[0]->GetYaxis()->SetTitleSize(0.05);
  meany_coil7[3]= hist_4ad_coil[3]->GetMean(2);
  meany_coil7[7]= hist_4ad_coil[7]->GetMean(2);
  int  num_trim7_48 = tree_R->Draw(Form("(bmod_trim7*%lf):(sam4/%lf-sam8/%lf)",chtov,meany_coil7[3],meany_coil7[7]),Form("bcm_an_ds3>5.32&& bcm_an_ds3<5.55 && bmwobj==7 && abs(bmod_trim7-%f)>20",trim_base[6]));
  hist_trim7_normalized[1]= new TGraph(num_trim7_48,tree_R->GetV1(),tree_R->GetV2());
  hist_trim7_normalized[1]->SetMarkerStyle(20);
  hist_trim7_normalized[1]->SetMarkerSize(2);
  hist_trim7_normalized[1]->GetYaxis()->SetTitle("Nsam4-Nsam8");
  hist_trim7_normalized[1]->GetXaxis()->SetTitle("trim7 [V]");
  hist_trim7_normalized[1]->GetXaxis()->SetTitleSize(0.05);
  hist_trim7_normalized[1]->GetYaxis()->SetTitleSize(0.05);


  for(int i=0;i<2;i++){
    
    hist_trim7_normalized[i]->SetTitle("sam_{i} normalized to <sam_{i}>");
    hist_trim7_normalized[i]->GetYaxis()->SetTitleOffset(1.3);
    hist_trim7_normalized[i]->GetXaxis()->SetTitleSize(0.05);
    hist_trim7_normalized[i]->GetYaxis()->SetTitleSize(0.04);
    hist_trim7_normalized[i]->GetYaxis()->SetLabelSize(0.03);
    
    hist_trim6_normalized[i]->SetTitle("sam_{i} normalized to <sam_{i}>");
    hist_trim6_normalized[i]->GetYaxis()->SetTitleOffset(1.3);
    hist_trim6_normalized[i]->GetXaxis()->SetTitleSize(0.05);
    hist_trim6_normalized[i]->GetYaxis()->SetTitleSize(0.04);
    hist_trim6_normalized[i]->GetYaxis()->SetLabelSize(0.03);
    
    
    
    hist_trim5_normalized[i]->SetTitle("sam_{i} normalized to <sam_{i}>");
    hist_trim5_normalized[i]->GetYaxis()->SetTitleOffset(1.3);
    hist_trim5_normalized[i]->GetXaxis()->SetTitleSize(0.05);
    hist_trim5_normalized[i]->GetYaxis()->SetTitleSize(0.04);
    hist_trim5_normalized[i]->GetYaxis()->SetLabelSize(0.03);
    
    
    hist_trim4_normalized[i]->SetTitle("sam_{i} normalized to <sam_{i}>");
    hist_trim4_normalized[i]->GetYaxis()->SetTitleOffset(1.3);
    hist_trim4_normalized[i]->GetXaxis()->SetTitleSize(0.05);
    hist_trim4_normalized[i]->GetYaxis()->SetTitleSize(0.04);
    hist_trim4_normalized[i]->GetYaxis()->SetLabelSize(0.03);
    
    hist_trim3_normalized[i]->SetTitle("sam_{i} normalized to <sam_{i}>");
    hist_trim3_normalized[i]->GetYaxis()->SetTitleOffset(1.3);
    hist_trim3_normalized[i]->GetXaxis()->SetTitleSize(0.05);
    hist_trim3_normalized[i]->GetYaxis()->SetTitleSize(0.04);
    hist_trim3_normalized[i]->GetYaxis()->SetLabelSize(0.03);
    
    hist_trim2_normalized[i]->SetTitle("sam_{i} normalized to <sam_{i}>");
    hist_trim2_normalized[i]->GetYaxis()->SetTitleOffset(1.3);
    hist_trim2_normalized[i]->GetXaxis()->SetTitleSize(0.05);
    hist_trim2_normalized[i]->GetYaxis()->SetTitleSize(0.04);
    hist_trim2_normalized[i]->GetYaxis()->SetLabelSize(0.03);
    
    hist_trim1_normalized[i]->SetTitle("sam_{i} normalized to <sam_{i}>");
    hist_trim1_normalized[i]->GetYaxis()->SetTitleOffset(1.3);
    hist_trim1_normalized[i]->GetXaxis()->SetTitleSize(0.05);
    hist_trim1_normalized[i]->GetYaxis()->SetTitleSize(0.04);
    hist_trim1_normalized[i]->GetYaxis()->SetLabelSize(0.03);  
    
  }
  
  
  char name_canvas[50];
  for(int i=0;i<8;i++){
    sprintf(name_canvas,"c%d",i);
    c[i]= new TCanvas(name_canvas,name_canvas,1000,1000);
    c[i]->Divide(n,8);
  }
  for(int i=0;i<n;i++){
    for(int j=0;j<8;j++){
      c[0]->cd(i*8+j+1);
      trim1_slop[j][i]=0;
      trim1_slop_err[j][i]=0;
      gtrim1[j][i]->Draw("A p");
      gtrim1[j][i]->Fit(funsloptrim1[j][i]);
      gtrim1[j][i]->Fit(funsloptrim1[j][i]);
      trim1_slop[j][i]=funsloptrim1[j][i]->GetParameter(1);
      trim1_slop_err[j][i]=funsloptrim1[j][i]->GetParError(1);
    }
    outfile0<<setw(20)<<setiosflags(ios::left)<<supercycslope[i]<<setw(20)<<setiosflags(ios::left)<<supercyc_err[i]
	    <<setw(20)<<setiosflags(ios::left)<<trim1_slop[0][i]<<setw(20)<<setiosflags(ios::left)<<trim1_slop_err[0][i]<<setw(20)<<setiosflags(ios::left)<<trim1_slop[1][i]<<setw(20)<<setiosflags(ios::left)<<trim1_slop_err[1][i]<<setw(20)<<setiosflags(ios::left)<<trim1_slop[2][i]<<setw(20)<<setiosflags(ios::left)<<trim1_slop_err[2][i]<<setw(20)<<setiosflags(ios::left)<<trim1_slop[3][i]<<setw(20)<<setiosflags(ios::left)<<trim1_slop_err[3][i]<<setw(20)<<setiosflags(ios::left)<<trim1_slop[4][i]<<setw(20)<<setiosflags(ios::left)<<trim1_slop_err[4][i]<<setw(20)<<setiosflags(ios::left)<<trim1_slop[5][i]<<setw(20)<<setiosflags(ios::left)<<trim1_slop_err[5][i]<<setw(20)<<setiosflags(ios::left)<<trim1_slop[6][i]<<setw(20)<<setiosflags(ios::left)<<trim1_slop_err[6][i]<<setw(20)<<setiosflags(ios::left)<<trim1_slop[7][i]<<setw(20)<<setiosflags(ios::left)<<trim1_slop_err[7][i]<<endl;
  }

  for(int i=0;i<n;i++){
    for(int j=0;j<8;j++){
      c[1]->cd(i*8+j+1);
      trim2_slop[j][i]=0;
      trim2_slop_err[j][i]=0;
      gtrim2[j][i]->Draw("A p");
      // gtrim2[j][i]->Fit(funtest[j][i]);
      // funsloptrim2[j][i]->SetParameters(funtest[j][i]->GetParameter(0),funtest[j][i]->GetParameter(1));
      gtrim2[j][i]->Fit(funsloptrim2[j][i]);
      trim2_slop[j][i]=funsloptrim2[j][i]->GetParameter(1);
      trim2_slop_err[j][i]=funsloptrim2[j][i]->GetParError(1);
    }
    outfile1<<setw(20)<<setiosflags(ios::left)<<supercycslope[i]<<setw(20)<<setiosflags(ios::left)<<supercyc_err[i]
	    <<setw(20)<<setiosflags(ios::left)<<trim2_slop[0][i]<<setw(20)<<setiosflags(ios::left)<<trim2_slop_err[0][i]<<setw(20)<<setiosflags(ios::left)<<trim2_slop[1][i]<<setw(20)<<setiosflags(ios::left)<<trim2_slop_err[1][i]<<setw(20)<<setiosflags(ios::left)<<trim2_slop[2][i]<<setw(20)<<setiosflags(ios::left)<<trim2_slop_err[2][i]<<setw(20)<<setiosflags(ios::left)<<trim2_slop[3][i]<<setw(20)<<setiosflags(ios::left)<<trim2_slop_err[3][i]<<setw(20)<<setiosflags(ios::left)<<trim2_slop[4][i]<<setw(20)<<setiosflags(ios::left)<<trim2_slop_err[4][i]<<setw(20)<<setiosflags(ios::left)<<trim2_slop[5][i]<<setw(20)<<setiosflags(ios::left)<<trim2_slop_err[5][i]<<setw(20)<<setiosflags(ios::left)<<trim2_slop[6][i]<<setw(20)<<setiosflags(ios::left)<<trim2_slop_err[6][i]<<setw(20)<<setiosflags(ios::left)<<trim2_slop[7][i]<<setw(20)<<setiosflags(ios::left)<<trim2_slop_err[7][i]<<endl;
  }

  for(int i=0;i<n;i++){
    for(int j=0;j<8;j++){
      c[2]->cd(i*8+j+1);
      trim3_slop[j][i]=0;
      trim3_slop_err[j][i]=0;
      gtrim3[j][i]->Draw("A p");
      gtrim3[j][i]->Fit(funsloptrim3[j][i]);
      gtrim3[j][i]->Fit(funsloptrim3[j][i]);
      trim3_slop[j][i]=funsloptrim3[j][i]->GetParameter(1);
      trim3_slop_err[j][i]=funsloptrim3[j][i]->GetParError(1);
    }
    outfile2<<setw(20)<<setiosflags(ios::left)<<supercycslope[i]<<setw(20)<<setiosflags(ios::left)<<supercyc_err[i]
	    <<setw(20)<<setiosflags(ios::left)<<trim3_slop[0][i]<<setw(20)<<setiosflags(ios::left)<<trim3_slop_err[0][i]<<setw(20)<<setiosflags(ios::left)<<trim3_slop[1][i]<<setw(20)<<setiosflags(ios::left)<<trim3_slop_err[1][i]<<setw(20)<<setiosflags(ios::left)<<trim3_slop[2][i]<<setw(20)<<setiosflags(ios::left)<<trim3_slop_err[2][i]<<setw(20)<<setiosflags(ios::left)<<trim3_slop[3][i]<<setw(20)<<setiosflags(ios::left)<<trim3_slop_err[3][i]<<setw(20)<<setiosflags(ios::left)<<trim3_slop[4][i]<<setw(20)<<setiosflags(ios::left)<<trim3_slop_err[4][i]<<setw(20)<<setiosflags(ios::left)<<trim3_slop[5][i]<<setw(20)<<setiosflags(ios::left)<<trim3_slop_err[5][i]<<setw(20)<<setiosflags(ios::left)<<trim3_slop[6][i]<<setw(20)<<setiosflags(ios::left)<<trim3_slop_err[6][i]<<setw(20)<<setiosflags(ios::left)<<trim3_slop[7][i]<<setw(20)<<setiosflags(ios::left)<<trim3_slop_err[7][i]<<endl;
  }

  for(int i=0;i<n;i++){
    for(int j=0;j<8;j++){
      c[3]->cd(i*8+j+1);
      trim4_slop[j][i]=0;
      trim4_slop_err[j][i]=0;
      gtrim4[j][i]->Draw("A p");
      gtrim4[j][i]->Fit(funsloptrim4[j][i]);
      gtrim4[j][i]->Fit(funsloptrim4[j][i]);
      trim4_slop[j][i]=funsloptrim4[j][i]->GetParameter(1);
      trim4_slop_err[j][i]=funsloptrim4[j][i]->GetParError(1);
    }
    outfile3<<setw(20)<<setiosflags(ios::left)<<supercycslope[i]<<setw(20)<<setiosflags(ios::left)<<supercyc_err[i]
	    <<setw(20)<<setiosflags(ios::left)<<trim4_slop[0][i]<<setw(20)<<setiosflags(ios::left)<<trim4_slop_err[0][i]<<setw(20)<<setiosflags(ios::left)<<trim4_slop[1][i]<<setw(20)<<setiosflags(ios::left)<<trim4_slop_err[1][i]<<setw(20)<<setiosflags(ios::left)<<trim4_slop[2][i]<<setw(20)<<setiosflags(ios::left)<<trim4_slop_err[2][i]<<setw(20)<<setiosflags(ios::left)<<trim4_slop[3][i]<<setw(20)<<setiosflags(ios::left)<<trim4_slop_err[3][i]<<setw(20)<<setiosflags(ios::left)<<trim4_slop[4][i]<<setw(20)<<setiosflags(ios::left)<<trim4_slop_err[4][i]<<setw(20)<<setiosflags(ios::left)<<trim4_slop[5][i]<<setw(20)<<setiosflags(ios::left)<<trim4_slop_err[5][i]<<setw(20)<<setiosflags(ios::left)<<trim4_slop[6][i]<<setw(20)<<setiosflags(ios::left)<<trim4_slop_err[6][i]<<setw(20)<<setiosflags(ios::left)<<trim4_slop[7][i]<<setw(20)<<setiosflags(ios::left)<<trim4_slop_err[7][i]<<endl;
  }


  for(int i=0;i<n;i++){
    for(int j=0;j<8;j++){
      c[4]->cd(i*8+j+1);
      trim5_slop[j][i]=0;
      trim5_slop_err[j][i]=0;
      gtrim5[j][i]->Draw("A p");
      gtrim5[j][i]->Fit(funsloptrim5[j][i]);
      gtrim5[j][i]->Fit(funsloptrim5[j][i]);
      trim5_slop[j][i]=funsloptrim5[j][i]->GetParameter(1);
      trim5_slop_err[j][i]=funsloptrim5[j][i]->GetParError(1);
    }
    outfile4<<setw(20)<<setiosflags(ios::left)<<supercycslope[i]<<setw(20)<<setiosflags(ios::left)<<supercyc_err[i]
	    <<setw(20)<<setiosflags(ios::left)<<trim5_slop[0][i]<<setw(20)<<setiosflags(ios::left)<<trim5_slop_err[0][i]<<setw(20)<<setiosflags(ios::left)<<trim5_slop[1][i]<<setw(20)<<setiosflags(ios::left)<<trim5_slop_err[1][i]<<setw(20)<<setiosflags(ios::left)<<trim5_slop[2][i]<<setw(20)<<setiosflags(ios::left)<<trim5_slop_err[2][i]<<setw(20)<<setiosflags(ios::left)<<trim5_slop[3][i]<<setw(20)<<setiosflags(ios::left)<<trim5_slop_err[3][i]<<setw(20)<<setiosflags(ios::left)<<trim5_slop[4][i]<<setw(20)<<setiosflags(ios::left)<<trim5_slop_err[4][i]<<setw(20)<<setiosflags(ios::left)<<trim5_slop[5][i]<<setw(20)<<setiosflags(ios::left)<<trim5_slop_err[5][i]<<setw(20)<<setiosflags(ios::left)<<trim5_slop[6][i]<<setw(20)<<setiosflags(ios::left)<<trim5_slop_err[6][i]<<setw(20)<<setiosflags(ios::left)<<trim5_slop[7][i]<<setw(20)<<setiosflags(ios::left)<<trim5_slop_err[7][i]<<endl;
  }


  for(int i=0;i<n;i++){
    for(int j=0;j<8;j++){
      c[5]->cd(i*8+j+1);
      trim6_slop[j][i]=0;
      trim6_slop_err[j][i]=0;
      gtrim6[j][i]->Draw("A p");
      gtrim6[j][i]->Fit(funsloptrim6[j][i]);
      gtrim6[j][i]->Fit(funsloptrim6[j][i]);
      trim6_slop[j][i]=funsloptrim6[j][i]->GetParameter(1);
      trim6_slop_err[j][i]=funsloptrim6[j][i]->GetParError(1);
    }
    outfile5<<setw(20)<<setiosflags(ios::left)<<supercycslope[i]<<setw(20)<<setiosflags(ios::left)<<supercyc_err[i]
	    <<setw(20)<<setiosflags(ios::left)<<trim6_slop[0][i]<<setw(20)<<setiosflags(ios::left)<<trim6_slop_err[0][i]<<setw(20)<<setiosflags(ios::left)<<trim6_slop[1][i]<<setw(20)<<setiosflags(ios::left)<<trim6_slop_err[1][i]<<setw(20)<<setiosflags(ios::left)<<trim6_slop[2][i]<<setw(20)<<setiosflags(ios::left)<<trim6_slop_err[2][i]<<setw(20)<<setiosflags(ios::left)<<trim6_slop[3][i]<<setw(20)<<setiosflags(ios::left)<<trim6_slop_err[3][i]<<setw(20)<<setiosflags(ios::left)<<trim6_slop[4][i]<<setw(20)<<setiosflags(ios::left)<<trim6_slop_err[4][i]<<setw(20)<<setiosflags(ios::left)<<trim6_slop[5][i]<<setw(20)<<setiosflags(ios::left)<<trim6_slop_err[5][i]<<setw(20)<<setiosflags(ios::left)<<trim6_slop[6][i]<<setw(20)<<setiosflags(ios::left)<<trim6_slop_err[6][i]<<setw(20)<<setiosflags(ios::left)<<trim6_slop[7][i]<<setw(20)<<setiosflags(ios::left)<<trim6_slop_err[7][i]<<endl;
  }
  for(int i=0;i<n;i++){
    for(int j=0;j<8;j++){
      c[6]->cd(i*8+j+1);
      trim7_slop[j][i]=0;
      trim7_slop_err[j][i]=0;
      gtrim7[j][i]->Draw("A p");
      gtrim7[j][i]->Fit(funsloptrim7[j][i]);
      gtrim7[j][i]->Fit(funsloptrim7[j][i]);
      trim7_slop[j][i]=funsloptrim7[j][i]->GetParameter(1);
      trim7_slop_err[j][i]=funsloptrim7[j][i]->GetParError(1);
    }
    outfile6<<setw(20)<<setiosflags(ios::left)<<supercycslope[i]<<setw(20)<<setiosflags(ios::left)<<supercyc_err[i]
	    <<setw(20)<<setiosflags(ios::left)<<trim7_slop[0][i]<<setw(20)<<setiosflags(ios::left)<<trim7_slop_err[0][i]<<setw(20)<<setiosflags(ios::left)<<trim7_slop[1][i]<<setw(20)<<setiosflags(ios::left)<<trim7_slop_err[1][i]<<setw(20)<<setiosflags(ios::left)<<trim7_slop[2][i]<<setw(20)<<setiosflags(ios::left)<<trim7_slop_err[2][i]<<setw(20)<<setiosflags(ios::left)<<trim7_slop[3][i]<<setw(20)<<setiosflags(ios::left)<<trim7_slop_err[3][i]<<setw(20)<<setiosflags(ios::left)<<trim7_slop[4][i]<<setw(20)<<setiosflags(ios::left)<<trim7_slop_err[4][i]<<setw(20)<<setiosflags(ios::left)<<trim7_slop[5][i]<<setw(20)<<setiosflags(ios::left)<<trim7_slop_err[5][i]<<setw(20)<<setiosflags(ios::left)<<trim7_slop[6][i]<<setw(20)<<setiosflags(ios::left)<<trim7_slop_err[6][i]<<setw(20)<<setiosflags(ios::left)<<trim7_slop[7][i]<<setw(20)<<setiosflags(ios::left)<<trim7_slop_err[7][i]<<endl;
  }



  double coil3_x[n];
  double coil3_y[n];
  int npt_coil3=0;
  for(int i=0;i<n;i++){
    coil3_x[i]=0;
    coil3_y[i]=0;
    meany_coil3_cyc[1][i]=gtrim3[1][i]->GetMean(2);
    //cout<<"meany="<<meany_coil3_cyc[1][i]<<endl;
    npt_coil3 = tree_R->Draw(Form("(bmod_trim3*%lf):(%s/%lf)",chtov,sam_wire[1].Data(),meany_coil3_cyc[1][i]),Form("ErrorFlag==0 && bmwobj==3 && abs(bmod_trim3-%f)>20 && bmwcycnum==%f",trim_base[2],supercyc[i]));
    gtrim3_cyc[1][i]= new TGraph(npt_coil3, tree_R->GetV1(),tree_R->GetV2()); 
    gtrim3_cyc[1][i]->SetMarkerStyle(20);
    gtrim3_cyc[1][i]->SetMarkerSize(2);
    gtrim3_cyc[1][i]->SetMarkerColor(1); 
    //  cout<<"i="<<i<<"print "<<endl;
    //  gtrim3_cyc[1][i]->Print();
  }
  const int point_coil3=npt_coil3;
  double coil3_totalcycy[point_coil3];
  double coil3_totalcycx[point_coil3];
  double coil3_avgcycy[point_coil3];
  double coil3_avgcycx[point_coil3];   
  for(int m=0;m<npt_coil3+1;m++){
    coil3_totalcycx[m]=0;
    coil3_totalcycy[m]=0;
    int valid_point=0;
    for(int i=0;i<n;i++){
      gtrim3_cyc[1][i]->GetPoint(m,coil3_x[i],coil3_y[i]);
      coil3_totalcycy[m]+=coil3_y[i];
      coil3_totalcycx[m]+=coil3_x[i];
      if(coil3_y[i]>0){
	valid_point++;
      }
    }
    coil3_avgcycy[m]=coil3_totalcycy[m]/valid_point;
    coil3_avgcycx[m]=coil3_totalcycx[m]/valid_point;
    cout<<"m="<<m<<"  "<<"averagx="<<coil3_avgcycx[m]<<"   "<<"averagy="<<coil3_avgcycy[m]<<endl;
  }
  TGraph *coil3_average = new TGraph(point_coil3,coil3_avgcycx,coil3_avgcycy);
  coil3_average->Print();
  TCanvas *test1 = new TCanvas("test1","test1",1000,1000);
  coil3_average->Draw("Ap");
  coil3_average->Fit(fun);
  TCanvas *c1 = new TCanvas("c1","c1",1000,1000);
  c1->Divide(2,4);
  for(int i=0;i<n;i++){
    c1->cd(i+1);
    gtrim3_cyc[1][i]->Draw("Ap");
  } 
  
  char name_trim1_sam[50];
  char name_trim2_sam[50];
  char name_trim3_sam[50];
  char name_trim4_sam[50];
  char name_trim5_sam[50];
  char name_trim6_sam[50];
  char name_trim7_sam[50];
  char name_trim8_sam[50];
  

  for(int j=0;j<8;j++){
    sprintf(name_trim1_sam,"cantrim1_sam%d",j+1);
    sprintf(name_trim2_sam,"cantrim2_sam%d",j+1);
    sprintf(name_trim3_sam,"cantrim3_sam%d",j+1);
    sprintf(name_trim4_sam,"cantrim4_sam%d",j+1);
    sprintf(name_trim5_sam,"cantrim5_sam%d",j+1);
    sprintf(name_trim6_sam,"cantrim6_sam%d",j+1);
    sprintf(name_trim7_sam,"cantrim7_sam%d",j+1);
    sprintf(name_trim8_sam,"cantrim8_sam%d",j+1);
    trim7_sam[j] =  new TCanvas(name_trim7_sam,name_trim7_sam,1000,1000);
    trim7_sam[j]->Divide(2,4);
    for(int i=0;i<n;i++){
      trim7_sam[j]->cd(i+1);
      gtrim1[j][i]->SetTitle(Form("cycle==%f",supercyc[i]));
      gtrim1[j][i]->GetXaxis()->SetTitle("coil 1");
      gtrim1[j][i]->GetYaxis()->SetTitle(Form("sam%d",j+1));
      gtrim1[j][i]->Draw("A p*");
      //gtrim2[j][i]->Fit(funsloptrim2[j][i]);
      //gtrim2[j][i]->Fit(funsloptrim2[j][i]);
      //gtrim2[j][i]->Fit(funsloptrim7[j][i]);
    }
  }
  trim7_sam[0]->Print("trim1.pdf[","pdf");
  trim7_sam[0]->Print("trim1.pdf","pdf");
  for(int j=1;j<8;j++){
    trim7_sam[j]->Print("trim1.pdf","pdf");
  }
  trim7_sam[0]->Print("trim1.pdf]","pdf");

}  
