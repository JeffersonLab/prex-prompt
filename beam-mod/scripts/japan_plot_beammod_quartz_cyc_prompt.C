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
using namespace std;

int japan_plot_beammod_quartz_cyc_prompt(TString src, int runNo=0) { 
  gStyle->SetOptStat(0); 
  char infile[300];
  sprintf(infile,"%s/prexPrompt_pass2_%d.000.root",src.Data(),runNo);
  TFile *file1=TFile::Open(infile);
    if(file1==NULL){
      cout << infile << "doesn't exist!!!" << endl;
      return 1;
    }
  TTree *tree_R = (TTree*) file1->Get("evt");
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

  const int n=cycles.size();//number of cycle
  Double_t supercyc[n];
  Int_t Is_fill[n];
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
 // Double_t trim_base[7] = {1683,1582,1708,1670,1662,1709,1686};
  const double trimmin=0.38;
  const double trimmax=0.7;
  const double bpmmax=3;
  const double bpmmin=1;
  const double chtov=1.0e-3;//7.62939453125000000e-05; //10V*(1/pow(2,17))
  const double factor=1.0e+6;
  const int cutflag=1;
  TF1 *fun = new TF1("fun","[0]+[1]*x",-1e6,1e6);
  Double_t init_par[2] = {0,0};
  fun->SetParameters(init_par);

  int xnbins=0.0;
  int ynbins=0;
  double ibincon=0;
  int ibin=0;
  double xbincon=0.0;
  int coilnum=0;
  ostringstream sstr0;
  sstr0<<"/lustre/expphy/volatile/halla/parity/prex-respin2/ditherOutput/dit_11X12X_txt/Quartz_sensitivity_run"<<runNo<<".txt";
  ofstream outfile0(sstr0.str().c_str());
  sstr0.str("");

  double tab_width = 20;
  
  const int nCoil =7;
  TString wire[nCoil]={"bmod_trim1","bmod_trim2","bmod_trim3","bmod_trim4","bmod_trim5","bmod_trim6","bmod_trim7"};
  TH1F * hist_trim[7];
  Double_t trim_base[7]={0};
 for(int icoil=0;icoil<nCoil;icoil++){
   tree_R->Draw(Form("%s>>hist_trim%d",wire[icoil].Data(),icoil),"bmod_ramp<0","");
   hist_trim[icoil] = (TH1F *)gDirectory->Get(Form("hist_trim%d",icoil));
   int maxbin = hist_trim[icoil]->GetMaximumBin();
   trim_base[icoil] = hist_trim[icoil]->GetXaxis()->GetBinCenter(maxbin);
   cout<<"trim_base="<<trim_base[icoil]<<endl;  
 } 
  TString detname; // A BUFF
  // Replace with input config file for generalization and multiple script-avoidance
  TString det_array[] = {"usl","dsl","usr","dsr"};
  const int nDet = 4;

  // Replace with std::vectors
  double sens[nDet][nCoil];
  double sens_err[nDet][nCoil];
  double fNdata[nDet][nCoil]; // [idet][icoil]
  for(int idet=0;idet<nDet;idet++){
    for(int icoil=0;icoil<nCoil;icoil++){
      sens[idet][icoil] = 0.0;
      sens_err[idet][icoil] = -1.0;
      fNdata[idet][icoil]=0.0;
    }
  }

  for(int i=0;i<n;i++){
    for(int idet=0;idet<nDet;idet++){
      detname= det_array[idet];
      for(int icoil=0;icoil<nCoil;icoil++){
	int ndata = tree_R->Draw(Form("%s:(%s*%lf)",
				      detname.Data(),wire[icoil].Data(),chtov),
				 Form("(ErrorFlag & 0xda7e6bff)==0 && bmod_ramp>0 && bmwobj==%d && abs(%s-%f)>20 && bmwcycnum==%f",
				      icoil+1,wire[icoil].Data(),trim_base[icoil],supercyc[i]));
	if(ndata<50){
	  // cout << "-- CycleNumber: " << supercyc[i] <<  endl;
	  // cout << "-- Coil ID: " << icoil+1 <<  endl;
	  // cout << "-- NData: " << ndata << endl;;
	  // cout << "-- Not enough data Discarding this cycle " << endl;
	}
	TGraph *g1 = new TGraph(ndata, tree_R->GetV2(),tree_R->GetV1());
	g1->GetXaxis()->SetTitle(wire[icoil]);
	g1->GetYaxis()->SetTitle(detname);
	g1->GetXaxis()->SetTitleSize(0.05);
	g1->GetYaxis()->SetTitleSize(0.05);
	double this_mean= g1->GetMean(2);

	ndata = tree_R->Draw(Form("(%lf/%lf)*%s:(%s*%lf)",
				  factor,this_mean, detname.Data(),
				  wire[icoil].Data(),chtov),
			     Form("(ErrorFlag & 0xda7e6bff)==0 && bmod_ramp>0 && bmwobj==%d && abs(%s-%f)>20 && bmwcycnum==%f",
				  icoil+1,wire[icoil].Data(),trim_base[icoil],supercyc[i]));

	double this_slope,this_error;
	if(ndata>50){
	  TGraph* g2 = new TGraph(ndata, tree_R->GetV2(),tree_R->GetV1());
	  fun->SetParameters(init_par);
	  g2->Fit("fun","Q0");
	  this_slope = fun->GetParameter(1);
	  this_error = fun->GetParError(1);
	  // cout << "Det " << idet 
	  //      << " vs Coil " << icoil+1<< " : "
	  //      << this_slope << "+/-" << this_error << endl;

	  g2->GetXaxis()->SetTitle(wire[icoil]);
	  g2->GetYaxis()->SetTitle(detname);
	  g2->GetXaxis()->SetTitleSize(0.05);
	  g2->GetYaxis()->SetTitleSize(0.05);
	  
	  fNdata[idet][icoil]+=ndata;


	    sens[idet][icoil]=this_slope;
	    sens_err[idet][icoil]=this_error;

	}

      } // end of coil loop
    } // end of Det loop

  for(int idet=0;idet<nDet;idet++)
    for(int icoil=0;icoil<nCoil;icoil++)
      if(sens_err[idet][icoil]==-1){
	cout << "-- Incomplete dithering coil " << icoil 
	     << " is found. No sensitivity output for this cycle "
	     << endl;
//	return 1;
      }
   
  // Replace with nested for loop

   if(sens_err[0][0]==-1 || sens_err[0][1]==-1|| sens_err[0][2]==-1 || sens_err[0][3]==-1 || sens_err[0][4]==-1 || sens_err[0][5]==-1 || sens_err[0][6]==-1 || sens_err[1][0]==-1 || sens_err[1][1]==-1|| sens_err[1][2]==-1 || sens_err[1][3]==-1 || sens_err[1][4]==-1 || sens_err[1][5]==-1 || sens_err[1][6]==-1 || sens_err[2][0]==-1 || sens_err[2][1]==-1|| sens_err[2][2]==-1 || sens_err[2][3]==-1 || sens_err[2][4]==-1 || sens_err[2][5]==-1 || sens_err[2][6]==-1 || sens_err[3][0]==-1 || sens_err[3][1]==-1|| sens_err[3][2]==-1 || sens_err[3][3]==-1 || sens_err[3][4]==-1 || sens_err[3][5]==-1 || sens_err[3][6]==-1 ){
     Is_fill[i]=0;
   }else{
    Is_fill[i]=1;
   }

  if(Is_fill[i]==1){
  for(int idet=0;idet<nDet;idet++){
    outfile0<< setw(tab_width) << setiosflags(ios::left) << runNo<<setw(tab_width) << setiosflags(ios::left)<<supercyc[i]<<setw(tab_width) << setiosflags(ios::left) <<cutflag // Now , just one o   
     << setw(tab_width) << setiosflags(ios::left) <<  det_array[idet];
    for(int icoil=0;icoil<nCoil;icoil++){
      outfile0<<setw(tab_width) << setiosflags(ios::left)
	      << setprecision(5) << sens[idet][icoil]
	      << setw(tab_width) << setiosflags(ios::left)
	      <<  setprecision(3) <<sens_err[idet][icoil]
	      << setw(tab_width) << setiosflags(ios::left) 
	      <<  setprecision(4)<< fNdata[idet][icoil];
    } // end of coil loop
    outfile0 << endl;
  } // end of detector loop
 }//end of cyc
}
  return 0;
}
  
