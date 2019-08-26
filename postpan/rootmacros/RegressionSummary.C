#include "device_list.h"

void RegressionSummary(){

  TTree *mul_tree = (TTree*)gROOT->FindObject("mul");
  TTree *mulc_lrb_tree = (TTree*)gROOT->FindObject("mulc_lrb");
  mul_tree->AddFriend(mulc_lrb_tree);
  
  double ppm = 1.0e-6;
  double um = 1.0e-3;

  TString run_dot_seg = run_seg;
  run_dot_seg = run_dot_seg.ReplaceAll('_','.'); 

  TString slopefile_name = Form("./LRBoutput/blueR%snew.slope.root",run_dot_seg.Data());
  TFile* slopefile = TFile::Open(slopefile_name);

  FILE *summary_txt = fopen(Form("%s/blueR%s_slope.txt",
				 output_path.Data(),
				 run_dot_seg.Data()), "w");
  
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
  
  TMatrixT<double> Mslope = *((TMatrixT<double>*)slopefile->Get("slopes"));
  TMatrixT<double> MslopeErr = *((TMatrixT<double>*)slopefile->Get("sigSlopes"));

  TMatrixT<double> MyStat = *((TMatrixT<double>*)slopefile->Get("MyStat"));
  Double_t nentries = MyStat(0,0);
  Double_t sqrtn = sqrt(nentries);

  TVectorT<double> VrawDV_mean = *((TVectorT<double>*)slopefile->Get("DV_mean"));
  TVectorT<double> VrawDV_sigma = *((TVectorT<double>*)slopefile->Get("DV_sigma"));


  TVectorT<double> VcorDV_mean = *((TVectorT<double>*)slopefile->Get("DV_mean_prime"));
  TVectorT<double> VcorDV_sigma = *((TVectorT<double>*)slopefile->Get("DV_sigma_prime"));

  TVectorT<double> VIV_mean = *((TVectorT<double>*)slopefile->Get("IV_mean"));
  TVectorT<double> VIV_sigma = *((TVectorT<double>*)slopefile->Get("IV_sigma"));

      
  int nDV = DVlist.size();
  int nIV = IVlist.size();

  fprintf(summary_txt," ---- LRB Correction Summary ---- \n \n");

  fprintf(summary_txt, 
	  "%-12s\t%-12s\t%-12s\t%-20s\t%-15s\t%-15s\t\n",
	  "",
	  "Raw Mean+/-err(ppm)","RMS(ppm)",
	  "Regressed Mean+/-err(ppm)","RMS (ppm)", 
	  "Correction on Mean(ppm)");
  
  for(int kDV=0;kDV<nDV;kDV++){
    fprintf(summary_txt, 
	    "%-12s\t%-3.2f+/-%-9.2f\t%-12.2f\t%-3.2f+/-%-17.2f\t%-17.2f%-15.2f\n",
	    DVlist[kDV].Data(), 
	    VrawDV_mean(kDV)/ppm,VrawDV_sigma(kDV)/sqrtn/ppm,VrawDV_sigma(kDV)/ppm,
	    VcorDV_mean(kDV)/ppm,VcorDV_sigma(kDV)/sqrtn/ppm,VcorDV_sigma(kDV)/ppm,
	    (VrawDV_mean(kDV)-VcorDV_mean(kDV))/ppm);
  }

  fprintf(summary_txt, " \n --IV (um): \n" );
  fprintf(summary_txt,"%-15s \t", "");
  for(int kIV=0; kIV<nIV; kIV++)
    fprintf(summary_txt,"%-15s \t", IVlist[kIV].Data());
  fprintf(summary_txt," \n");
  
  fprintf(summary_txt,"%-15s \t", "Mean+/-Err(um)");
  for(int kIV=0; kIV<nIV; kIV++)
    fprintf(summary_txt,"%-3.2f+/-%-12.2f \t", 
	    VIV_mean(kIV)/um,VIV_sigma(kIV)/sqrtn/um);
  fprintf(summary_txt," \n");

  fprintf(summary_txt,"%-15s \t", "RMS(um)");
  for(int kIV=0; kIV<nIV; kIV++)
    fprintf(summary_txt,"%-15.2f \t", VIV_sigma(kIV)/um);
  fprintf(summary_txt," \n");


  fprintf(summary_txt, " \n --Regression Slope (ppm/um): \n");
  fprintf(summary_txt, " %-15s\t ","" );
  for(int kIV=0; kIV<nIV; kIV++)
    fprintf(summary_txt,"%-15s \t", IVlist[kIV].Data());
  fprintf(summary_txt," \n");

  for(int kDV=0;kDV<nDV;kDV++){
    fprintf(summary_txt,"%-15s \t", DVlist[kDV].Data());
    for(int kIV=0;kIV<nIV;kIV++)
      fprintf(summary_txt,"%-.2f +/- %-9.2f\t", 
	      Mslope(kIV,kDV)/(ppm/um),
	      MslopeErr(kIV,kDV)/(ppm/um));
    fprintf(summary_txt," \n");
  }

  fclose(summary_txt);
  slopefile->Close();
  results->cd();
}


