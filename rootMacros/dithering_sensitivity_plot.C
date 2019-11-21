#include <iostream>
#include "TMath.h"
#include "TMatrixD.h"
#include "TMatrixDLazy.h"
#include "TVectorD.h"
#include "TDecompLU.h"
#include "TDecompSVD.h"
#include "TArrayD.h"
#include "TMatrixD.h"
#include "TMatrixDBase.h"
#include <sstream>
#include <iostream>
#include<TRandom.h>
void dithering_sensitivity_plot(int slugNo=0){
  tString promptdir = gSystem->Getenv("$PROMPT_DIR");
  char inputfile[300];
  sprintf(inputfile,"%s/beam-mod/scripts/dit_11X12X_txt/BPMs_sensitivity_slug%d.txt",promptdir,slugNo);
  ifstream infile(inputfile);

  const int n=1000;
  const int t=n/5;
  string bpm_name[n];
  int bpm4ax_run[t],bpm4ax_flag[t],bpm_run[n],bpm_flag[n];
  double bpm_cyc[n],bpm_coil1[n],bpm_coil1_error[n],bpmEntry_coil1[n],bpm_coil2[n],bpm_coil2_error[n],bpmEntry_coil2[n],bpm_coil3[n],bpm_coil3_error[n],bpmEntry_coil3[n],bpm_coil4[n],bpm_coil4_error[n],bpmEntry_coil4[n],bpm_coil5[n],bpm_coil5_error[n],bpmEntry_coil5[n],bpm_coil6[n],bpm_coil6_error[n],bpmEntry_coil6[n],bpm_coil7[n],bpm_coil7_error[n],bpmEntry_coil7[n]; 


  double bpm4ax_cyc[t],bpm4ax_name[t],bpm4ax_coil1[t],bpm4ax_coil1_error[t],bpm4axEntry_coil1[t],bpm4ax_coil2[t],bpm4ax_coil2_error[t],bpm4axEntry_coil2[t],bpm4ax_coil3[t],bpm4ax_coil3_error[t],bpm4axEntry_coil3[t],bpm4ax_coil4[t],bpm4ax_coil4_error[t],bpm4axEntry_coil4[t],bpm4ax_coil5[t],bpm4ax_coil5_error[t],bpm4axEntry_coil5[t],bpm4ax_coil6[t],bpm4ax_coil6_error[t],bpm4axEntry_coil6[t],bpm4ax_coil7[t],bpm4ax_coil7_error[t],bpm4axEntry_coil7[t]; 

  double bpm4ex_cyc[t],bpm4ex_name[t],bpm4ex_coil1[t],bpm4ex_coil1_error[t],bpm4exEntry_coil1[t],bpm4ex_coil2[t],bpm4ex_coil2_error[t],bpm4exEntry_coil2[t],bpm4ex_coil3[t],bpm4ex_coil3_error[t],bpm4exEntry_coil3[t],bpm4ex_coil4[t],bpm4ex_coil4_error[t],bpm4exEntry_coil4[t],bpm4ex_coil5[t],bpm4ex_coil5_error[t],bpm4exEntry_coil5[t],bpm4ex_coil6[t],bpm4ex_coil6_error[t],bpm4exEntry_coil6[t],bpm4ex_coil7[t],bpm4ex_coil7_error[t],bpm4exEntry_coil7[t]; 

  double bpm4ay_cyc[t],bpm4ay_name[t],bpm4ay_coil1[t],bpm4ay_coil1_error[t],bpm4ayEntry_coil1[t],bpm4ay_coil2[t],bpm4ay_coil2_error[t],bpm4ayEntry_coil2[t],bpm4ay_coil3[t],bpm4ay_coil3_error[t],bpm4ayEntry_coil3[t],bpm4ay_coil4[t],bpm4ay_coil4_error[t],bpm4ayEntry_coil4[t],bpm4ay_coil5[t],bpm4ay_coil5_error[t],bpm4ayEntry_coil5[t],bpm4ay_coil6[t],bpm4ay_coil6_error[t],bpm4ayEntry_coil6[t],bpm4ay_coil7[t],bpm4ay_coil7_error[t],bpm4ayEntry_coil7[t]; 

  double bpm4ey_cyc[t],bpm4ey_name[t],bpm4ey_coil1[t],bpm4ey_coil1_error[t],bpm4eyEntry_coil1[t],bpm4ey_coil2[t],bpm4ey_coil2_error[t],bpm4eyEntry_coil2[t],bpm4ey_coil3[t],bpm4ey_coil3_error[t],bpm4eyEntry_coil3[t],bpm4ey_coil4[t],bpm4ey_coil4_error[t],bpm4eyEntry_coil4[t],bpm4ey_coil5[t],bpm4ey_coil5_error[t],bpm4eyEntry_coil5[t],bpm4ey_coil6[t],bpm4ey_coil6_error[t],bpm4eyEntry_coil6[t],bpm4ey_coil7[t],bpm4ey_coil7_error[t],bpm4eyEntry_coil7[t]; 

  double bpm12x_cyc[t],bpm12x_name[t],bpm12x_coil1[t],bpm12x_coil1_error[t],bpm12xEntry_coil1[t],bpm12x_coil2[t],bpm12x_coil2_error[t],bpm12xEntry_coil2[t],bpm12x_coil3[t],bpm12x_coil3_error[t],bpm12xEntry_coil3[t],bpm12x_coil4[t],bpm12x_coil4_error[t],bpm12xEntry_coil4[t],bpm12x_coil5[t],bpm12x_coil5_error[t],bpm12xEntry_coil5[t],bpm12x_coil6[t],bpm12x_coil6_error[t],bpm12xEntry_coil6[t],bpm12x_coil7[t],bpm12x_coil7_error[t],bpm12xEntry_coil7[t]; 

  for(int i=0;i<n;i++){
    infile>>bpm_run[i]>>bpm_cyc[i]>>bpm_flag[i]>>bpm_name[i]>>bpm_coil1[i]>>bpm_coil1_error[i]>>bpmEntry_coil1[i]>>bpm_coil2[i]>>bpm_coil2_error[i]>>bpmEntry_coil2[i]>>bpm_coil3[i]>>bpm_coil3_error[i]>>bpmEntry_coil3[i]>>bpm_coil4[i]>>bpm_coil4_error[i]>>bpmEntry_coil4[i]>>bpm_coil5[i]>>bpm_coil5_error[i]>>bpmEntry_coil5[i]>>bpm_coil6[i]>>bpm_coil6_error[i]>>bpmEntry_coil6[i]>>bpm_coil7[i]>>bpm_coil7_error[i]>>bpmEntry_coil7[i];

  }


  double supercyc_err[t];
  for(int j=0;j<t;j++){
    supercyc_err[j]=0;
    bpm4ax_coil1[j]=bpm_coil1[j*5];
    bpm4ax_coil2[j]=bpm_coil2[j*5];
    bpm4ax_coil3[j]=bpm_coil3[j*5];
    bpm4ax_coil4[j]=bpm_coil4[j*5];
    bpm4ax_coil5[j]=bpm_coil5[j*5];
    bpm4ax_coil6[j]=bpm_coil6[j*5];
    bpm4ax_coil7[j]=bpm_coil7[j*5];

    bpm4ex_coil1[j]=bpm_coil1[j*5+1];
    bpm4ex_coil2[j]=bpm_coil2[j*5+1];
    bpm4ex_coil3[j]=bpm_coil3[j*5+1];
    bpm4ex_coil4[j]=bpm_coil4[j*5+1];
    bpm4ex_coil5[j]=bpm_coil5[j*5+1];
    bpm4ex_coil6[j]=bpm_coil6[j*5+1];
    bpm4ex_coil7[j]=bpm_coil7[j*5+1];

    bpm4ay_coil1[j]=bpm_coil1[j*5+2];
    bpm4ay_coil2[j]=bpm_coil2[j*5+2];
    bpm4ay_coil3[j]=bpm_coil3[j*5+2];
    bpm4ay_coil4[j]=bpm_coil4[j*5+2];
    bpm4ay_coil5[j]=bpm_coil5[j*5+2];
    bpm4ay_coil6[j]=bpm_coil6[j*5+2];
    bpm4ay_coil7[j]=bpm_coil7[j*5+2];

    bpm4ey_coil1[j]=bpm_coil1[j*5+3];
    bpm4ey_coil2[j]=bpm_coil2[j*5+3];
    bpm4ey_coil3[j]=bpm_coil3[j*5+3];
    bpm4ey_coil4[j]=bpm_coil4[j*5+3];
    bpm4ey_coil5[j]=bpm_coil5[j*5+3];
    bpm4ey_coil6[j]=bpm_coil6[j*5+3];
    bpm4ey_coil7[j]=bpm_coil7[j*5+3];

    bpm12x_coil1[j]=bpm_coil1[j*5+4];
    bpm12x_coil2[j]=bpm_coil2[j*5+4];
    bpm12x_coil3[j]=bpm_coil3[j*5+4];
    bpm12x_coil4[j]=bpm_coil4[j*5+4];
    bpm12x_coil5[j]=bpm_coil5[j*5+4];
    bpm12x_coil6[j]=bpm_coil6[j*5+4];
    bpm12x_coil7[j]=bpm_coil7[j*5+4];


    bpm4ax_cyc[j]=bpm_cyc[j*5];
    bpm4ex_cyc[j]=bpm_cyc[j*5+1];
    bpm4ay_cyc[j]=bpm_cyc[j*5+2];
    bpm4ey_cyc[j]=bpm_cyc[j*5+3];
    bpm12x_cyc[j]=bpm_cyc[j*5+4];
    bpm4ax_run[j]=bpm_run[j*5];
    bpm4ax_flag[j]=bpm_flag[j*5];


    bpm4ax_coil1_error[j]=bpm_coil1_error[j*5];
    bpm4ax_coil2_error[j]=bpm_coil2_error[j*5];
    bpm4ax_coil3_error[j]=bpm_coil3_error[j*5];
    bpm4ax_coil4_error[j]=bpm_coil4_error[j*5];
    bpm4ax_coil5_error[j]=bpm_coil5_error[j*5];
    bpm4ax_coil6_error[j]=bpm_coil6_error[j*5];
    bpm4ax_coil7_error[j]=bpm_coil7_error[j*5];

    bpm4ex_coil1_error[j]=bpm_coil1_error[j*5+1];
    bpm4ex_coil2_error[j]=bpm_coil2_error[j*5+1];
    bpm4ex_coil3_error[j]=bpm_coil3_error[j*5+1];
    bpm4ex_coil4_error[j]=bpm_coil4_error[j*5+1];
    bpm4ex_coil5_error[j]=bpm_coil5_error[j*5+1];
    bpm4ex_coil6_error[j]=bpm_coil6_error[j*5+1];
    bpm4ex_coil7_error[j]=bpm_coil7_error[j*5+1];

    bpm4ay_coil1_error[j]=bpm_coil1_error[j*5+2];
    bpm4ay_coil2_error[j]=bpm_coil2_error[j*5+2];
    bpm4ay_coil3_error[j]=bpm_coil3_error[j*5+2];
    bpm4ay_coil4_error[j]=bpm_coil4_error[j*5+2];
    bpm4ay_coil5_error[j]=bpm_coil5_error[j*5+2];
    bpm4ay_coil6_error[j]=bpm_coil6_error[j*5+2];
    bpm4ay_coil7_error[j]=bpm_coil7_error[j*5+2];

    bpm4ey_coil1_error[j]=bpm_coil1_error[j*5+3];
    bpm4ey_coil2_error[j]=bpm_coil2_error[j*5+3];
    bpm4ey_coil3_error[j]=bpm_coil3_error[j*5+3];
    bpm4ey_coil4_error[j]=bpm_coil4_error[j*5+3];
    bpm4ey_coil5_error[j]=bpm_coil5_error[j*5+3];
    bpm4ey_coil6_error[j]=bpm_coil6_error[j*5+3];
    bpm4ey_coil7_error[j]=bpm_coil7_error[j*5+3];

    bpm12x_coil1_error[j]=bpm_coil1_error[j*5+4];
    bpm12x_coil2_error[j]=bpm_coil2_error[j*5+4];
    bpm12x_coil3_error[j]=bpm_coil3_error[j*5+4];
    bpm12x_coil4_error[j]=bpm_coil4_error[j*5+4];
    bpm12x_coil5_error[j]=bpm_coil5_error[j*5+4];
    bpm12x_coil6_error[j]=bpm_coil6_error[j*5+4];
    bpm12x_coil7_error[j]=bpm_coil7_error[j*5+4];

  }

  TGraphErrors *slopx[9];
  TGraphErrors *slopy[8];
  slopx[0]=new TGraphErrors(t,bpm4ax_cyc,bpm4ax_coil1,supercyc_err,bpm4ax_coil1_error);
  slopx[0]->SetTitle("#partialB_{4ax}/#partialC_{1}");
  slopx[1]=new TGraphErrors(t,bpm4ax_cyc,bpm4ex_coil1,supercyc_err,bpm4ex_coil1_error);
  slopx[1]->SetTitle("#partialB_{4ex}/#partialC_{1}");
  slopx[2]=new TGraphErrors(t,bpm4ax_cyc,bpm4ax_coil3,supercyc_err,bpm4ax_coil3_error);
  slopx[2]->SetTitle("#partialB_{4ax}/#partialC_{3}");
  slopx[3]=new TGraphErrors(t,bpm4ax_cyc,bpm4ex_coil3,supercyc_err,bpm4ex_coil3_error);
  slopx[3]->SetTitle("#partialB_{4ex}/#partialC_{3}");
  slopx[4]=new TGraphErrors(t,bpm4ax_cyc,bpm4ax_coil5,supercyc_err,bpm4ax_coil5_error);
  slopx[4]->SetTitle("#partialB_{4ax}/#partialC_{5}");
  slopx[5]=new TGraphErrors(t,bpm4ax_cyc,bpm4ex_coil5,supercyc_err,bpm4ex_coil5_error);
  slopx[5]->SetTitle("#partialB_{4ex}/#partialC_{5}");
  slopx[6]=new TGraphErrors(t,bpm4ax_cyc,bpm12x_coil7,supercyc_err,bpm12x_coil7_error);
  slopx[6]->SetTitle("#partialB_{12x}/#partialC_{7}");
  slopx[7]=new TGraphErrors(t,bpm4ax_cyc,bpm4ax_coil7,supercyc_err,bpm4ax_coil7_error);
  slopx[7]->SetTitle("#partialB_{4ax}/#partialC_{7}");
  slopx[8]=new TGraphErrors(t,bpm4ax_cyc,bpm4ex_coil7,supercyc_err,bpm4ex_coil7_error);
  slopx[8]->SetTitle("#partialB_{4ex}/#partialC_{7}");



  slopy[0]=new TGraphErrors(t,bpm4ax_cyc,bpm4ay_coil2,supercyc_err,bpm4ay_coil2_error);
  slopy[0]->SetTitle("#partialB_{4ay}/#partialC_{2}");
  slopy[1]=new TGraphErrors(t,bpm4ax_cyc,bpm4ey_coil2,supercyc_err,bpm4ey_coil2_error);
  slopy[1]->SetTitle("#partialB_{4ey}/#partialC_{2}");
  slopy[2]=new TGraphErrors(t,bpm4ax_cyc,bpm4ay_coil4,supercyc_err,bpm4ay_coil4_error);
  slopy[2]->SetTitle("#partialB_{4ay}/#partialC_{4}");
  slopy[3]=new TGraphErrors(t,bpm4ax_cyc,bpm4ey_coil4,supercyc_err,bpm4ey_coil4_error);
  slopy[3]->SetTitle("#partialB_{4ey}/#partialC_{4}");
  slopy[4]=new TGraphErrors(t,bpm4ax_cyc,bpm4ay_coil6,supercyc_err,bpm4ay_coil6_error);
  slopy[4]->SetTitle("#partialB_{4ay}/#partialC_{6}");
  slopy[5]=new TGraphErrors(t,bpm4ax_cyc,bpm4ey_coil6,supercyc_err,bpm4ey_coil6_error);
  slopy[5]->SetTitle("#partialB_{4ey}/#partialC_{6}");
  slopy[6]=new TGraphErrors(t,bpm4ax_cyc,bpm4ay_coil7,supercyc_err,bpm4ay_coil7_error);
  slopy[6]->SetTitle("#partialB_{4ay}/#partialC_{7}");
  slopy[7]=new TGraphErrors(t,bpm4ax_cyc,bpm4ey_coil7,supercyc_err,bpm4ey_coil7_error);
  slopy[7]->SetTitle("#partialB_{4ey}/#partialC_{7}");

  double alpha15_val[t];
  double alpha15_val_err[t];
  double alpha35_val[t];
  double alpha35_val_err[t];
  double alpha13_val[t];
  double alpha13_val_err[t];
  double alpha24_val[t];
  double alpha24_val_err[t];
  double alpha26_val[t];
  double alpha26_val_err[t];
  double alpha46_val[t];
  double alpha46_val_err[t];
  int a=0;
  int b=0;
  int c=0;
  int d=0;
  int e=0;
  int g=0;
  int h=0;
  int j=0;
  int ay=0;
  int by=0;
  int cy=0;
  int dy=0;
  int ey=0;
  int gy=0;


  int cay=0;
  int day=0;
  int eay=0;
  int gay=0;

  for(int k=0;k<t;k++){
    if(bpm4ax_coil5[k]==0){
      slopx[4]->RemovePoint(k-a);
      a=a+1;
    }
    if(bpm4ex_coil5[k]==0){
      slopx[5]->RemovePoint(k-b);
      b=b+1;
    }
    if(bpm4ay_coil6[k]==0){
      slopy[4]->RemovePoint(k-c);
      c=c+1;
    }
    if(bpm4ey_coil6[k]==0){
      slopy[5]->RemovePoint(k-d);
      d=d+1;
    }

    if(bpm4ax_coil7[k]==0){
      slopx[7]->RemovePoint(k-cay);
      cay=cay+1;
    }
    if(bpm4ex_coil7[k]==0){
      slopx[8]->RemovePoint(k-day);
      day=day+1;
    }
    if(bpm4ay_coil7[k]==0){
      slopy[6]->RemovePoint(k-eay);
      eay=eay+1;
    }
    if(bpm4ey_coil7[k]==0){
      slopy[7]->RemovePoint(k-gay);
      gay=gay+1;
    }

    if(bpm4ax_coil3[k]==0){
      slopx[2]->RemovePoint(k-e);
      e=e+1;
    }
    if(bpm4ex_coil3[k]==0){
      slopx[3]->RemovePoint(k-g);
      g=g+1;
    }

    if(bpm4ax_coil1[k]==0){
      slopx[0]->RemovePoint(k-h);
      h=h+1;
    } 
    if(bpm4ex_coil1[k]==0){
      slopx[1]->RemovePoint(k-j);
      j=j+1;
    } 

    if(bpm4ay_coil2[k]==0){
      slopy[0]->RemovePoint(k-ay);
      ay=ay+1;
    }
    if(bpm4ey_coil2[k]==0){
      slopy[1]->RemovePoint(k-by);
      by=by+1;
    }


    if(bpm4ay_coil4[k]==0){
      slopy[2]->RemovePoint(k-cy);
      cy=cy+1;
    }
    if(bpm4ey_coil4[k]==0){
      slopy[3]->RemovePoint(k-dy);
      dy=dy+1;
    }


    if(bpm12x_coil7[k]==0){
      slopx[6]->RemovePoint(k-ey);
      ey=ey+1;
    }
  }

  for(int i=0;i<t;i++){
    alpha15_val_err[i]=0;
    if(bpm4ax_coil1[i]!=0 && bpm4ex_coil1[i]!=0 && bpm4ax_coil5[i]!=0 && bpm4ex_coil5[i]!=0){
      alpha15_val[i]=1-(bpm4ex_coil1[i]*bpm4ax_coil5[i])/(bpm4ax_coil1[i]*bpm4ex_coil5[i]);
    }else{
      alpha15_val[i]=0;
    }
    alpha35_val_err[i]=0;
    if(bpm4ex_coil5[i]!=0 && bpm4ax_coil3[i]!=0 && bpm4ax_coil5[i]!=0 && bpm4ex_coil3[i]!=0){
      alpha35_val[i]=1-(bpm4ex_coil3[i]*bpm4ax_coil5[i])/(bpm4ax_coil3[i]*bpm4ex_coil5[i]);
    }else{
      alpha35_val[i]=0;
    }
    alpha13_val_err[i]=0;
    if(bpm4ax_coil1[i]!=0 && bpm4ex_coil1[i]!=0 && bpm4ax_coil3[i]!=0 && bpm4ex_coil3[i]!=0){
      alpha13_val[i]=1-(bpm4ex_coil1[i]*bpm4ax_coil3[i])/(bpm4ax_coil1[i]*bpm4ex_coil3[i]);
    }else{
      alpha13_val[i]=0;
    }
  }


  TGraphErrors *g1_alpha15;
  g1_alpha15=new TGraphErrors(t,bpm4ax_cyc,alpha15_val,supercyc_err,alpha15_val_err);
  g1_alpha15->SetTitle(Form("#alpha_{coil15}_slug%d",slugNo));

  TGraphErrors *g1_alpha35;
  g1_alpha35=new TGraphErrors(t,bpm4ax_cyc,alpha35_val,supercyc_err,alpha35_val_err);
  g1_alpha35->SetTitle(Form("#alpha_{coil35}_slug%d",slugNo));

  TGraphErrors *g1_alpha13;
  g1_alpha13=new TGraphErrors(t,bpm4ax_cyc,alpha13_val,supercyc_err,alpha13_val_err);
  g1_alpha13->SetTitle(Form("#alpha_{coil13}_slug%d",slugNo));

  int alpha=0;
  int alphb=0;
  int alphc=0;
  for(int k=0;k<t;k++){
    if(alpha15_val[k]==0){
      g1_alpha15->RemovePoint(k-alpha);
      alpha=alpha+1;
    }
    if(alpha35_val[k]==0){
      g1_alpha35->RemovePoint(k-alphb);
      alphb=alphb+1;
    }
    if(alpha13_val[k]==0){
      g1_alpha13->RemovePoint(k-alphc);
      alphc=alphc+1;
    }


  }
  // Y coils alph

  for(int i=0;i<t;i++){
    alpha24_val_err[i]=0;
    if(bpm4ay_coil2[i]!=0 && bpm4ey_coil2[i]!=0 && bpm4ay_coil4[i]!=0 && bpm4ey_coil4[i]!=0){
      alpha24_val[i]=1-(bpm4ey_coil2[i]*bpm4ay_coil4[i])/(bpm4ay_coil2[i]*bpm4ey_coil4[i]);
    }else{
      alpha24_val[i]=0;
    }
    alpha26_val_err[i]=0;
    if(bpm4ey_coil2[i]!=0 && bpm4ay_coil2[i]!=0 && bpm4ay_coil6[i]!=0 && bpm4ey_coil6[i]!=0){
      alpha26_val[i]=1-(bpm4ey_coil2[i]*bpm4ay_coil6[i])/(bpm4ay_coil2[i]*bpm4ey_coil6[i]);
    }else{
      alpha26_val[i]=0;
    }
    alpha46_val_err[i]=0;
    if(bpm4ay_coil4[i]!=0 && bpm4ey_coil4[i]!=0 && bpm4ay_coil6[i]!=0 && bpm4ey_coil6[i]!=0){
      alpha46_val[i]=1-(bpm4ey_coil4[i]*bpm4ay_coil6[i])/(bpm4ay_coil4[i]*bpm4ey_coil6[i]);
    }else{
      alpha46_val[i]=0;
    }
    if(i==830){
      cout<<"bpm4ay_coil4="<<bpm4ay_coil4[i]<<"bpm4ey_coil4="<<bpm4ey_coil4[i]<<"bpm4ay_coil6="<<bpm4ay_coil6[i]<<"bpm4ey_coil6="<<bpm4ey_coil6[i]<<endl;
    }
  }


  TGraphErrors *g1_alpha26;
  g1_alpha26=new TGraphErrors(t,bpm4ax_cyc,alpha26_val,supercyc_err,alpha26_val_err);
  g1_alpha26->SetTitle(Form("#alpha_{coil26}_slug%d",slugNo));

  TGraphErrors *g1_alpha46;
  g1_alpha46=new TGraphErrors(t,bpm4ax_cyc,alpha46_val,supercyc_err,alpha46_val_err);
  g1_alpha46->SetTitle(Form("#alpha_{coil46}_slug%d",slugNo));

  TGraphErrors *g1_alpha24;
  g1_alpha24=new TGraphErrors(t,bpm4ax_cyc,alpha24_val,supercyc_err,alpha24_val_err);
  g1_alpha24->SetTitle(Form("#alpha_{coil24}_slug%d",slugNo));

  int alpha2=0;
  int alphb2=0;
  int alphc2=0;
  for(int k=0;k<t;k++){
    if(alpha26_val[k]==0){
      g1_alpha26->RemovePoint(k-alpha2);
      alpha2=alpha2+1;
    }
    if(alpha46_val[k]==0){
      g1_alpha46->RemovePoint(k-alphb2);
      alphb2=alphb2+1;
    }
    if(alpha24_val[k]==0){
      g1_alpha24->RemovePoint(k-alphc2);
      alphc2=alphc2+1;
    }


  }

  //delta

  double delta15_val[t];
  double delta15_val_err[t];
  double delta35_val[t];
  double delta35_val_err[t];
  double delta13_val[t];
  double delta13_val_err[t];

  double ratio15_val[t];
  double ratio15_val_err[t];
  double ratio35_val[t];
  double ratio35_val_err[t];
  double ratio13_val[t];
  double ratio13_val_err[t];

  for(int i=0;i<t;i++){
    delta15_val_err[i]=0;
    if(bpm4ax_coil5[i]!=0 && bpm4ax_coil1[i]!=0 && bpm12x_coil5[i]!=0 && bpm12x_coil1[i]!=0){
      delta15_val[i]=(bpm12x_coil5[i]/bpm4ax_coil5[i])-(bpm12x_coil1[i]/bpm4ax_coil1[i]);
    }else{
      delta15_val[i]=0;
    }
    delta35_val_err[i]=0;
    if(bpm4ax_coil5[i]!=0 && bpm4ax_coil3[i]!=0 && bpm12x_coil5[i]!=0 && bpm12x_coil3[i]!=0){
      delta35_val[i]=(bpm12x_coil5[i]/bpm4ax_coil5[i])-(bpm12x_coil3[i]/bpm4ax_coil3[i]);
    }else{
      delta35_val[i]=0;
    }
    delta13_val_err[i]=0;
    if(bpm4ax_coil1[i]!=0 && bpm4ax_coil3[i]!=0 && bpm12x_coil3[i]!=0 && bpm12x_coil1[i]!=0){
      delta13_val[i]=(bpm12x_coil3[i]/bpm4ax_coil3[i])-(bpm12x_coil1[i]/bpm4ax_coil1[i]);
    }else{
      delta13_val[i]=0;
    }
  }

  TGraphErrors *g1_delta15;
  g1_delta15=new TGraphErrors(t,bpm4ax_cyc,delta15_val,supercyc_err,delta15_val_err);
  g1_delta15->SetTitle("#delta_{coil15}");

  TGraphErrors *g1_delta35;
  g1_delta35=new TGraphErrors(t,bpm4ax_cyc,delta35_val,supercyc_err,delta35_val_err);
  g1_delta35->SetTitle("#delta_{coil35}");

  TGraphErrors *g1_delta13;
  g1_delta13=new TGraphErrors(t,bpm4ax_cyc,delta13_val,supercyc_err,delta13_val_err);
  g1_delta13->SetTitle("#delta_{coil13}");

  int dda=0;
  int ddb=0;
  int ddc=0;
  for(int k=0;k<t;k++){
    if(delta15_val[k]==0){
      g1_delta15->RemovePoint(k-dda);
      dda=dda+1;
    }
    if(delta35_val[k]==0){
      g1_delta35->RemovePoint(k-ddb);
      ddb=ddb+1;
    }
    if(delta13_val[k]==0){
      g1_delta13->RemovePoint(k-ddc);
      ddc=ddc+1;
    }


  }

  // ycoils
  double delta26_val[t];
  double delta26_val_err[t];
  double delta46_val[t];
  double delta46_val_err[t];
  double delta24_val[t];
  double delta24_val_err[t];

  double ratio26_val[t];
  double ratio26_val_err[t];
  double ratio46_val[t];
  double ratio46_val_err[t];
  double ratio24_val[t];
  double ratio24_val_err[t];

  for(int i=0;i<t;i++){
    delta26_val_err[i]=0;
    if(bpm4ay_coil6[i]!=0 && bpm4ay_coil2[i]!=0 && bpm12x_coil6[i]!=0 && bpm12x_coil2[i]!=0){
      delta26_val[i]=(bpm12x_coil6[i]/bpm4ay_coil6[i])-(bpm12x_coil2[i]/bpm4ay_coil2[i]);
    }else{
      delta26_val[i]=0;
    }
    delta46_val_err[i]=0;
    if(bpm4ay_coil4[i]!=0 && bpm4ay_coil6[i]!=0 && bpm12x_coil4[i]!=0 && bpm12x_coil6[i]!=0){
      delta46_val[i]=(bpm12x_coil6[i]/bpm4ay_coil6[i])-(bpm12x_coil4[i]/bpm4ay_coil4[i]);
    }else{
      delta46_val[i]=0;
    }
    delta24_val_err[i]=0;
    if(bpm4ay_coil2[i]!=0 && bpm4ay_coil4[i]!=0 && bpm12x_coil2[i]!=0 && bpm12x_coil4[i]!=0){
      delta24_val[i]=(bpm12x_coil4[i]/bpm4ay_coil4[i])-(bpm12x_coil2[i]/bpm4ay_coil2[i]);
    }else{
      delta24_val[i]=0;
    }
  }

  TGraphErrors *g1_delta26;
  g1_delta26=new TGraphErrors(t,bpm4ax_cyc,delta26_val,supercyc_err,delta26_val_err);
  g1_delta26->SetTitle("#delta_{coil26}");

  TGraphErrors *g1_delta46;
  g1_delta46=new TGraphErrors(t,bpm4ax_cyc,delta46_val,supercyc_err,delta46_val_err);
  g1_delta46->SetTitle("#delta_{coil46}");

  TGraphErrors *g1_delta24;
  g1_delta24=new TGraphErrors(t,bpm4ax_cyc,delta24_val,supercyc_err,delta24_val_err);
  g1_delta24->SetTitle("#delta_{coil24}");

  int dda2=0;
  int ddb2=0;
  int ddc2=0;
  for(int k=0;k<t;k++){
    if(delta26_val[k]==0){
      g1_delta26->RemovePoint(k-dda2);
      dda2=dda2+1;
    }
    if(delta46_val[k]==0){
      g1_delta46->RemovePoint(k-ddb2);
      ddb2=ddb2+1;
    }
    if(delta24_val[k]==0){
      g1_delta24->RemovePoint(k-ddc2);
      ddc2=ddc2+1;
    }


  }
  //ratio

  for(int i=0;i<t;i++){
    if(alpha15_val[i] !=0 && delta15_val[i]!=0 ){
      ratio15_val[i]= delta15_val[i]/alpha15_val[i];
    }else{ratio15_val[i]=0;}
    if(alpha35_val[i] !=0 && delta35_val[i]!=0 ){
      ratio35_val[i]= delta35_val[i]/alpha35_val[i];
    }else{ratio35_val[i]=0;}
    if(alpha13_val[i] !=0 && delta13_val[i]!=0 ){
      ratio13_val[i]= delta13_val[i]/alpha13_val[i];
    }else{ratio13_val[i]=0;}
  }
  TGraphErrors *g1_ratio15;
  g1_ratio15=new TGraphErrors(t,bpm4ax_cyc,ratio15_val,supercyc_err,ratio15_val_err);
  g1_ratio15->SetTitle("(#delta/#alpha)_{coil15}");

  TGraphErrors *g1_ratio35;
  g1_ratio35=new TGraphErrors(t,bpm4ax_cyc,ratio35_val,supercyc_err,ratio35_val_err);
  g1_ratio35->SetTitle("(#delta/#alpha)_{coil35}");

  TGraphErrors *g1_ratio13;
  g1_ratio13=new TGraphErrors(t,bpm4ax_cyc,ratio13_val,supercyc_err,ratio13_val_err);
  g1_ratio13->SetTitle("(#delta/#alpha)_{coil13}");

  int raa=0;
  int rab=0;
  int rac=0;
  for(int k=0;k<t;k++){
    if(ratio15_val[k]==0){
      g1_ratio15->RemovePoint(k-raa);
      raa=raa+1;
    }
    if(ratio35_val[k]==0){
      g1_ratio35->RemovePoint(k-rab);
      rab=rab+1;
    }
    if(ratio13_val[k]==0){
      g1_ratio13->RemovePoint(k-rac);
      rac=rac+1;
    }

  }

  //y coils

  for(int i=0;i<t;i++){
    if(alpha26_val[i] !=0 && delta26_val[i]!=0 ){
      ratio26_val[i]= delta26_val[i]/alpha26_val[i];
    }else{ratio26_val[i]=0;}
    if(alpha46_val[i] !=0 && delta46_val[i]!=0 ){
      ratio46_val[i]= delta46_val[i]/alpha46_val[i];
    }else{ratio46_val[i]=0;}
    if(alpha24_val[i] !=0 && delta24_val[i]!=0 ){
      ratio24_val[i]= delta24_val[i]/alpha24_val[i];
    }else{ratio24_val[i]=0;}
  }
  TGraphErrors *g1_ratio26;
  g1_ratio26=new TGraphErrors(t,bpm4ax_cyc,ratio26_val,supercyc_err,ratio26_val_err);
  g1_ratio26->SetTitle("(#delta/#alpha)_{coil26}");

  TGraphErrors *g1_ratio46;
  g1_ratio46=new TGraphErrors(t,bpm4ax_cyc,ratio46_val,supercyc_err,ratio46_val_err);
  g1_ratio46->SetTitle("(#delta/#alpha)_{coil46}");

  TGraphErrors *g1_ratio24;
  g1_ratio24=new TGraphErrors(t,bpm4ax_cyc,ratio24_val,supercyc_err,ratio24_val_err);
  g1_ratio24->SetTitle("(#delta/#alpha)_{coil24}");

  int raa2=0;
  int rab2=0;
  int rac2=0;
  for(int k=0;k<t;k++){
    if(ratio26_val[k]==0){
      g1_ratio26->RemovePoint(k-raa2);
      raa2=raa2+1;
    }
    if(ratio46_val[k]==0){
      g1_ratio46->RemovePoint(k-rab2);
      rab2=rab2+1;
    }
    if(ratio24_val[k]==0){
      g1_ratio24->RemovePoint(k-rac2);
      rac2=rac2+1;
    }

  }

  TLine *xmeanLine[8];
  TLine *ymeanLine[8];
  double xmean[8];
  double ymean[8];
  double corfactorX[8];
  double corfactorY[8];
  double corfactorXcal[8];
  double corfactorYcal[8];
  double valRMSXX[8];
  double valRMSYX[8];
  double avaX[8];
  double avaY[8];
  double avaXY[8];
  double valcovarX[8];
  TLatex *lX[8];
  TLatex *lX1[8];
  TLatex *lY[8];
  TCanvas *c41 = new TCanvas("c41","c41",1000,1000);

  c41->Divide(2,3);
  for(int i=0;i<6;i++){
    c41->cd(i+1);

    slopx[i]->SetMarkerStyle(20);
    slopx[i]->SetMarkerSize(0.01); 
    slopx[i]->SetMarkerColor(1);
    slopx[i]->GetXaxis()->SetTitle("super cycle");
    slopx[i]->GetYaxis()->SetTitle("#partial_{B_{i}}/#partial_{C_{i}} (micron/count)");
    slopx[i]->GetXaxis()->SetLabelSize(0.06);
    slopx[i]->GetYaxis()->SetLabelSize(0.06);
    slopx[i]->GetXaxis()->SetTitleSize(0.06);
    slopx[i]->GetYaxis()->SetTitleSize(0.06);
    slopx[i]->GetYaxis()->SetTitleOffset(0.6);
    slopx[i]->GetXaxis()->SetTitleOffset(0.8);
    slopx[i]->Draw("A p");
    slopx[i]->SetMarkerStyle(20);
    slopx[i]->SetMarkerSize(1);
    slopx[i]->SetMarkerColor(1);
    corfactorX[i]=slopx[i]->GetCorrelationFactor();
    lX[i]= new TLatex();
    lX[i]->SetTextSize(0.1);
    lX[i]->SetTextFont(72);
    xmean[i] = slopx[i]->GetMean(2);
    gPad->SetGrid(1); 
    gPad->SetGridx(1);
    xmeanLine[i]=new TLine(13,xmean[i],26,xmean[i]);
    xmeanLine[i]->SetLineColor(1);
    xmeanLine[i]->SetLineStyle(7);
    xmeanLine[i]->Draw("same");
    gPad->SetGridy(1);
  }
  c41->SaveAs(Form("plots/sensitivity_plots_slug%d.pdf(",slugNo));

  TCanvas *c42 = new TCanvas("c42","c42",1000,1000);
  c42->Divide(2,3);
  for(int i=0;i<6;i++){
    c42->cd(i+1);
    slopy[i]->SetMarkerStyle(20);
    slopy[i]->SetMarkerSize(0.01);
    slopy[i]->SetMarkerColor(1);
    slopy[i]->GetXaxis()->SetTitle("super cycle");
    slopy[i]->GetYaxis()->SetTitle("#partial_{B_{i}}/#partial_{C_{i}} (micron/count)");
    slopy[i]->GetXaxis()->SetLabelSize(0.06);
    slopy[i]->GetYaxis()->SetLabelSize(0.06);
    slopy[i]->GetXaxis()->SetTitleSize(0.06);
    slopy[i]->GetYaxis()->SetTitleSize(0.06);
    slopy[i]->GetYaxis()->SetTitleOffset(0.6);
    slopy[i]->GetXaxis()->SetTitleOffset(0.8);

    slopy[i]->SetMarkerStyle(20);
    slopy[i]->SetMarkerSize(1);
    slopy[i]->SetMarkerColor(1);
    slopy[i]->GetXaxis()->SetTitle("super cycle");
    slopy[i]->GetYaxis()->SetTitle("#partial_{B_{i}}/#partial_{C_{i}} (micron/count)");
    slopy[i]->GetXaxis()->SetLabelSize(0.05);
    slopy[i]->GetYaxis()->SetLabelSize(0.05);
    slopy[i]->GetXaxis()->SetTitleSize(0.05);
    slopy[i]->GetYaxis()->SetTitleSize(0.05);
    slopy[i]->Draw("Ap");
    corfactorY[i]=slopy[i]->GetCorrelationFactor();
    lY[i]= new TLatex();
    lY[i]->SetTextSize(0.1);
    lY[i]->SetTextFont(72);
    ymean[i] = slopy[i]->GetMean(2);
    ymeanLine[i]=new TLine(13,ymean[i],26,ymean[i]);
    ymeanLine[i]->SetLineColor(1);
    ymeanLine[i]->SetLineStyle(7);
    ymeanLine[i]->Draw("same");

    gPad->SetGrid(1); 
    gPad->SetGridx(1);
    gPad->SetGridy(1);
  }

  c42->SaveAs(Form("plots/sensitivity_plots_slug%d.pdf",slugNo));

  TCanvas *c12x = new TCanvas("c12x","c12x",1000,1000);
  c12x->Divide(2,3);
  for(int i=6;i<9;i++){
    c12x->cd(i-5);
    slopx[i]->SetMarkerStyle(20);
    slopx[i]->SetMarkerSize(1);
    slopx[i]->SetMarkerColor(1);
    slopx[i]->GetXaxis()->SetTitle("super cycle");
    slopx[i]->GetYaxis()->SetTitle("#partial_{B_{i}}/#partial_{C_{i}} (micron/count)");
    slopx[i]->GetYaxis()->SetTitleOffset(0.6);
    slopx[i]->GetXaxis()->SetTitleOffset(0.8);
    slopx[i]->GetXaxis()->SetLabelSize(0.05);
    slopx[i]->GetYaxis()->SetLabelSize(0.05);
    slopx[i]->GetXaxis()->SetTitleSize(0.05);
    slopx[i]->GetYaxis()->SetTitleSize(0.05);
    slopx[i]->Draw("Ap");
    gPad->SetGrid(1);
    gPad->SetGridx(1);
    gPad->SetGridy(1);
  }

  for(int i=6;i<8;i++){
    c12x->cd(i-2);
    slopy[i]->SetMarkerStyle(20);
    slopy[i]->SetMarkerSize(1);
    slopy[i]->SetMarkerColor(1);
    slopy[i]->GetXaxis()->SetTitle("super cycle");
    slopy[i]->GetYaxis()->SetTitle("#partial_{B_{i}}/#partial_{C_{i}} (micron/count)");
    slopy[i]->GetXaxis()->SetLabelSize(0.05);
    slopy[i]->GetYaxis()->SetLabelSize(0.05);
    slopy[i]->GetXaxis()->SetTitleSize(0.05);
    slopy[i]->GetYaxis()->SetTitleSize(0.05);
    slopy[i]->GetYaxis()->SetTitleOffset(0.6);
    slopy[i]->GetXaxis()->SetTitleOffset(0.8);
    slopy[i]->Draw("Ap");
    gPad->SetGrid(1);
    gPad->SetGridx(1);
    gPad->SetGridy(1);

  }

  c12x->SaveAs(Form("plots/sensitivity_plots_slug%d.pdf",slugNo));


  TLine *xmeanLine15;
  TLine *xmeanLine13;
  TLine *xmeanLine35;
  double xmean15;
  double xmean35;
  double xmean13;
  TCanvas *c44 = new TCanvas("c44","c44",1000,1000);
  c44->Divide(2,3); 
  c44->cd(1);

  g1_alpha15->SetMarkerStyle(20);
  g1_alpha15->SetMarkerSize(1); 
  g1_alpha15->GetXaxis()->SetTitle("super cycle");
  g1_alpha15->GetYaxis()->SetTitle("#alpha_{coil15}");
  g1_alpha15->GetXaxis()->SetLabelSize(0.05);
  g1_alpha15->GetYaxis()->SetLabelSize(0.05);
  g1_alpha15->GetXaxis()->SetTitleSize(0.05);
  g1_alpha15->GetYaxis()->SetTitleSize(0.05);
  g1_alpha15->GetYaxis()->SetTitleOffset(0.8);
  g1_alpha15->GetXaxis()->SetTitleOffset(0.8);

  g1_alpha15->Draw("A p");
  xmean15 = g1_alpha15->GetMean(2);
  gPad->SetGrid(1); // both axes get a grid, don't forget the gPad->Modified() (see below)
  gPad->SetGridx(1);
  xmeanLine15=new TLine(13,xmean15,26,xmean15);
  xmeanLine15->SetLineColor(1);
  xmeanLine15->SetLineStyle(7);
  xmeanLine15->Draw("same");

  c44->cd(3);

  g1_delta15->SetMarkerStyle(20);
  g1_delta15->SetMarkerSize(1); 
  g1_delta15->GetXaxis()->SetTitle("super cycle");
  g1_delta15->GetYaxis()->SetTitle("#delta_{coil15}");
  g1_delta15->GetXaxis()->SetLabelSize(0.05);
  g1_delta15->GetYaxis()->SetLabelSize(0.05);
  g1_delta15->GetXaxis()->SetTitleSize(0.05);
  g1_delta15->GetYaxis()->SetTitleSize(0.05);
  g1_delta15->GetYaxis()->SetTitleOffset(0.8);
  g1_delta15->GetXaxis()->SetTitleOffset(0.8);
  g1_delta15->Draw("a p");
  gPad->SetGrid(1); // both axes get a grid, don't forget the gpad->modified() (see below)
  gPad->SetGridx(1);
  c44->cd(5);

  g1_ratio15->SetMarkerStyle(20);
  g1_ratio15->SetMarkerSize(1); 
  g1_ratio15->GetXaxis()->SetTitle("super cycle");
  g1_ratio15->GetYaxis()->SetTitle("(#alpha/#delta)_{coil15}");
  g1_ratio15->GetXaxis()->SetLabelSize(0.05);
  g1_ratio15->GetYaxis()->SetLabelSize(0.05);
  g1_ratio15->GetXaxis()->SetTitleSize(0.05);
  g1_ratio15->GetYaxis()->SetTitleSize(0.05);
  g1_ratio15->GetYaxis()->SetTitleOffset(0.8);
  g1_ratio15->GetXaxis()->SetTitleOffset(0.8);
  g1_ratio15->Draw("A p");
  gPad->SetGrid(1); // both axes get a grid, don't forget the gPad->Modified() (see below)
  gPad->SetGridx(1);


  c44->cd(2);

  g1_alpha26->SetMarkerStyle(20);
  g1_alpha26->SetMarkerSize(1); 
  g1_alpha26->GetXaxis()->SetTitle("super cycle");
  g1_alpha26->GetYaxis()->SetTitle("#alpha_{coil26}");
  g1_alpha26->GetXaxis()->SetLabelSize(0.05);
  g1_alpha26->GetYaxis()->SetLabelSize(0.05);
  g1_alpha26->GetXaxis()->SetTitleSize(0.05);
  g1_alpha26->GetYaxis()->SetTitleSize(0.05);
  g1_alpha26->GetYaxis()->SetTitleOffset(0.8);
  g1_alpha26->GetXaxis()->SetTitleOffset(0.8);

  g1_alpha26->Draw("A p");
  gPad->SetGrid(1); // both axes get a grid, don't forget the gPad->Modified() (see below)
  gPad->SetGridx(1);

  c44->cd(4);

  g1_delta26->SetMarkerStyle(20);
  g1_delta26->SetMarkerSize(1); 
  g1_delta26->GetXaxis()->SetTitle("super cycle");
  g1_delta26->GetYaxis()->SetTitle("#delta_{coil26}");
  g1_delta26->GetXaxis()->SetLabelSize(0.05);
  g1_delta26->GetYaxis()->SetLabelSize(0.05);
  g1_delta26->GetXaxis()->SetTitleSize(0.05);
  g1_delta26->GetYaxis()->SetTitleSize(0.05);
  g1_delta26->GetYaxis()->SetTitleOffset(0.8);
  g1_delta26->GetXaxis()->SetTitleOffset(0.8);
  g1_delta26->Draw("a p");
  gPad->SetGrid(1); // both axes get a grid, don't forget the gpad->modified() (see below)
  gPad->SetGridx(1);
  c44->cd(6);

  g1_ratio26->SetMarkerStyle(20);
  g1_ratio26->SetMarkerSize(1); 
  g1_ratio26->GetXaxis()->SetTitle("super cycle");
  g1_ratio26->GetYaxis()->SetTitle("(#alpha/#delta)_{coil26}");
  g1_ratio26->GetXaxis()->SetLabelSize(0.05);
  g1_ratio26->GetYaxis()->SetLabelSize(0.05);
  g1_ratio26->GetXaxis()->SetTitleSize(0.05);
  g1_ratio26->GetYaxis()->SetTitleSize(0.05);
  g1_ratio26->GetYaxis()->SetTitleOffset(0.8);
  g1_ratio26->GetXaxis()->SetTitleOffset(0.8);
  g1_ratio26->Draw("A p");
  gPad->SetGrid(1); // both axes get a grid, don't forget the gPad->Modified() (see below)
  gPad->SetGridx(1);

  c44->SaveAs(Form("plots/sensitivity_plots_slug%d.pdf",slugNo));

  TCanvas *c45 = new TCanvas("c45","c45",1000,1000);
  c45->Divide(2,3);
  c45->cd(1);
  g1_alpha13->SetMarkerStyle(20);
  g1_alpha13->SetMarkerSize(1); 
  g1_alpha13->GetXaxis()->SetTitle("super cycle");
  g1_alpha13->GetYaxis()->SetTitle("#alpha_{coil13}");
  g1_alpha13->GetXaxis()->SetLabelSize(0.05);
  g1_alpha13->GetYaxis()->SetLabelSize(0.05);
  g1_alpha13->GetXaxis()->SetTitleSize(0.05);
  g1_alpha13->GetYaxis()->SetTitleSize(0.05);
  g1_alpha13->GetYaxis()->SetTitleOffset(0.8);
  g1_alpha13->GetXaxis()->SetTitleOffset(0.8);

  g1_alpha13->Draw("A p");
  xmean13 = g1_alpha13->GetMean(2);
  gPad->SetGrid(1); // both axes get a grid, don't forget the gPad->Modified() (see below)
  gPad->SetGridx(1);
  xmeanLine13=new TLine(13,xmean13,26,xmean13);
  xmeanLine13->SetLineColor(1);
  xmeanLine13->SetLineStyle(7);

  xmeanLine13->Draw("same");
  c45->cd(3);

  g1_delta13->SetMarkerStyle(20);
  g1_delta13->SetMarkerSize(1); 
  g1_delta13->GetXaxis()->SetTitle("super cycle");
  g1_delta13->GetYaxis()->SetTitle("#delta_{coil13}");
  g1_delta13->GetXaxis()->SetLabelSize(0.05);
  g1_delta13->GetYaxis()->SetLabelSize(0.05);
  g1_delta13->GetXaxis()->SetTitleSize(0.05);
  g1_delta13->GetYaxis()->SetTitleSize(0.05);
  g1_delta13->GetYaxis()->SetTitleOffset(0.8);
  g1_delta13->GetXaxis()->SetTitleOffset(0.8);
  g1_delta13->Draw("A p");
  gPad->SetGrid(1); // both axes get a grid, don't forget the gPad->Modified() (see below)
  gPad->SetGridx(1);
  c45->cd(5);
  g1_ratio13->SetMarkerStyle(20);
  g1_ratio13->SetMarkerSize(1); 
  g1_ratio13->GetXaxis()->SetTitle("super cycle");
  g1_ratio13->GetYaxis()->SetTitle("(#alpha/#delta)_{coil13}");
  g1_ratio13->GetXaxis()->SetLabelSize(0.05);
  g1_ratio13->GetYaxis()->SetLabelSize(0.05);
  g1_ratio13->GetXaxis()->SetTitleSize(0.05);
  g1_ratio13->GetYaxis()->SetTitleSize(0.05);
  g1_ratio13->GetYaxis()->SetTitleOffset(0.8);
  g1_ratio13->GetXaxis()->SetTitleOffset(0.8);
  g1_ratio13->Draw("A p");
  gPad->SetGrid(1); // both axes get a grid, don't forget the gPad->Modified() (see below)
  gPad->SetGridx(1);
  c45->cd(2);

  g1_alpha46->SetMarkerStyle(20);
  g1_alpha46->SetMarkerSize(1); 
  g1_alpha46->GetXaxis()->SetTitle("super cycle");
  g1_alpha46->GetYaxis()->SetTitle("#alpha_{coil46}");
  g1_alpha46->GetXaxis()->SetLabelSize(0.05);
  g1_alpha46->GetYaxis()->SetLabelSize(0.05);
  g1_alpha46->GetXaxis()->SetTitleSize(0.05);
  g1_alpha46->GetYaxis()->SetTitleSize(0.05);
  g1_alpha46->GetYaxis()->SetTitleOffset(0.8);
  g1_alpha46->GetXaxis()->SetTitleOffset(0.8);

  g1_alpha46->Draw("A p");
  gPad->SetGrid(1); // both axes get a grid, don't forget the gPad->Modified() (see below)
  gPad->SetGridx(1);

  c45->cd(4);

  g1_delta46->SetMarkerStyle(20);
  g1_delta46->SetMarkerSize(1); 
  g1_delta46->GetXaxis()->SetTitle("super cycle");
  g1_delta46->GetYaxis()->SetTitle("#delta_{coil46}");
  g1_delta46->GetXaxis()->SetLabelSize(0.05);
  g1_delta46->GetYaxis()->SetLabelSize(0.05);
  g1_delta46->GetXaxis()->SetTitleSize(0.05);
  g1_delta46->GetYaxis()->SetTitleSize(0.05);
  g1_delta46->GetYaxis()->SetTitleOffset(0.8);
  g1_delta46->GetXaxis()->SetTitleOffset(0.8);
  g1_delta46->Draw("a p");
  gPad->SetGrid(1); // both axes get a grid, don't forget the gpad->modified() (see below)
  gPad->SetGridx(1);
  c45->cd(6);

  g1_ratio46->SetMarkerStyle(20);
  g1_ratio46->SetMarkerSize(1); 
  g1_ratio46->GetXaxis()->SetTitle("super cycle");
  g1_ratio46->GetYaxis()->SetTitle("(#alpha/#delta)_{coil46}");
  g1_ratio46->GetXaxis()->SetLabelSize(0.05);
  g1_ratio46->GetYaxis()->SetLabelSize(0.05);
  g1_ratio46->GetXaxis()->SetTitleSize(0.05);
  g1_ratio46->GetYaxis()->SetTitleSize(0.05);
  g1_ratio46->GetYaxis()->SetTitleOffset(0.8);
  g1_ratio46->GetXaxis()->SetTitleOffset(0.8);
  g1_ratio46->Draw("A p");
  gPad->SetGrid(1); // both axes get a grid, don't forget the gPad->Modified() (see below)
  gPad->SetGridx(1);

  c45->SaveAs(Form("plots/sensitivity_plots_slug%d.pdf",slugNo));

  TCanvas *c43 = new TCanvas("c43","c43",1000,1000);
  c43->Divide(2,3);
  c43->cd(1);

  g1_alpha35->SetMarkerStyle(20);
  g1_alpha35->SetMarkerSize(1); 
  g1_alpha35->GetXaxis()->SetTitle("super cycle");
  g1_alpha35->GetYaxis()->SetTitle("#alpha_{coil35}");
  g1_alpha35->GetXaxis()->SetLabelSize(0.05);
  g1_alpha35->GetYaxis()->SetLabelSize(0.05);
  g1_alpha35->GetXaxis()->SetTitleSize(0.05);
  g1_alpha35->GetYaxis()->SetTitleSize(0.05);
  g1_alpha35->GetYaxis()->SetTitleOffset(0.8);
  g1_alpha35->GetXaxis()->SetTitleOffset(0.8);

  g1_alpha35->Draw("A p");
  xmean35 = g1_alpha35->GetMean(2);
  gPad->SetGrid(1); // both axes get a grid, don't forget the gPad->Modified() (see below)
  gPad->SetGridx(1);
  xmeanLine35=new TLine(13,xmean35,26,xmean35);
  xmeanLine35->SetLineColor(1);
  xmeanLine35->SetLineStyle(7);
  xmeanLine35->Draw("same");
  c43->cd(3);
  g1_delta35->SetMarkerStyle(20);
  g1_delta35->SetMarkerSize(1); 
  g1_delta35->GetXaxis()->SetTitle("super cycle");
  g1_delta35->GetYaxis()->SetTitle("#delta_{coil35}");
  g1_delta35->GetXaxis()->SetLabelSize(0.05);
  g1_delta35->GetYaxis()->SetLabelSize(0.05);
  g1_delta35->GetXaxis()->SetTitleSize(0.05);
  g1_delta35->GetYaxis()->SetTitleSize(0.05);
  g1_delta35->GetYaxis()->SetTitleOffset(0.8);
  g1_delta35->GetXaxis()->SetTitleOffset(0.8);
  g1_delta35->Draw("A p");
  gPad->SetGrid(1); // both axes get a grid, don't forget the gPad->Modified() (see below)
  gPad->SetGridx(1);
  c43->cd(5);
  g1_ratio35->SetMarkerStyle(20);
  g1_ratio35->SetMarkerSize(1); 
  g1_ratio35->GetXaxis()->SetTitle("super cycle");
  g1_ratio35->GetYaxis()->SetTitle("(#alpha/#delta)_{coil35}");
  g1_ratio35->GetXaxis()->SetLabelSize(0.05);
  g1_ratio35->GetYaxis()->SetLabelSize(0.05);
  g1_ratio35->GetXaxis()->SetTitleSize(0.05);
  g1_ratio35->GetYaxis()->SetTitleSize(0.05);
  g1_ratio35->GetYaxis()->SetTitleOffset(0.8);
  g1_ratio35->GetXaxis()->SetTitleOffset(0.8);
  g1_ratio35->Draw("A p");
  gPad->SetGrid(1); // both axes get a grid, don't forget the gPad->Modified() (see below)
  gPad->SetGridx(1);

  c43->cd(2);

  g1_alpha24->SetMarkerStyle(20);
  g1_alpha24->SetMarkerSize(1); 
  g1_alpha24->GetXaxis()->SetTitle("super cycle");
  g1_alpha24->GetYaxis()->SetTitle("#alpha_{coil24}");
  g1_alpha24->GetXaxis()->SetLabelSize(0.05);
  g1_alpha24->GetYaxis()->SetLabelSize(0.05);
  g1_alpha24->GetXaxis()->SetTitleSize(0.05);
  g1_alpha24->GetYaxis()->SetTitleSize(0.05);
  g1_alpha24->GetYaxis()->SetTitleOffset(0.8);
  g1_alpha24->GetXaxis()->SetTitleOffset(0.8);

  g1_alpha24->Draw("A p");
  gPad->SetGrid(1); // both axes get a grid, don't forget the gPad->Modified() (see below)
  gPad->SetGridx(1);

  c43->cd(4);

  g1_delta24->SetMarkerStyle(20);
  g1_delta24->SetMarkerSize(1); 
  g1_delta24->GetXaxis()->SetTitle("super cycle");
  g1_delta24->GetYaxis()->SetTitle("#delta_{coil24}");
  g1_delta24->GetXaxis()->SetLabelSize(0.05);
  g1_delta24->GetYaxis()->SetLabelSize(0.05);
  g1_delta24->GetXaxis()->SetTitleSize(0.05);
  g1_delta24->GetYaxis()->SetTitleSize(0.05);
  g1_delta24->GetYaxis()->SetTitleOffset(0.8);
  g1_delta24->GetXaxis()->SetTitleOffset(0.8);
  g1_delta24->Draw("a p");
  gPad->SetGrid(1); // both axes get a grid, don't forget the gpad->modified() (see below)
  gPad->SetGridx(1);
  c43->cd(6);

  g1_ratio24->SetMarkerStyle(20);
  g1_ratio24->SetMarkerSize(1); 
  g1_ratio24->GetXaxis()->SetTitle("super cycle");
  g1_ratio24->GetYaxis()->SetTitle("(#alpha/#delta)_{coil24}");
  g1_ratio24->GetXaxis()->SetLabelSize(0.05);
  g1_ratio24->GetYaxis()->SetLabelSize(0.05);
  g1_ratio24->GetXaxis()->SetTitleSize(0.05);
  g1_ratio24->GetYaxis()->SetTitleSize(0.05);
  g1_ratio24->GetYaxis()->SetTitleOffset(0.8);
  g1_ratio24->GetXaxis()->SetTitleOffset(0.8);
  g1_ratio24->Draw("A p");
  gPad->SetGrid(1); // both axes get a grid, don't forget the gPad->Modified() (see below)
  gPad->SetGridx(1);

  c43->SaveAs(Form("plots/sensitivity_plots_slug%d.pdf)",slugNo));

}

