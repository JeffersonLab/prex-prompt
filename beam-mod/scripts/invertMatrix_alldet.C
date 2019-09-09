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
using namespace std;
#include "QuerySlugNumber.C"

void invertMatrix_alldet(int runNo=0){
  Int_t msize=5;
  char inputfile1[300];
  sprintf(inputfile1,"./dit_11X12X_txt/BPMs_sensitivity_run%d.txt",runNo);

  char inputfile2[300];
  sprintf(inputfile2,"./dit_11X12X_txt/Quartz_sensitivity_run%d.txt",runNo);

  char inputfile3[300];
  sprintf(inputfile3,"./dit_11X12X_txt/AT_sensitivity_run%d.txt",runNo);

  ifstream infile2(inputfile3);	 
  ifstream infile(inputfile1);	 
  ifstream infile1(inputfile2);
  if(infile.fail()){
    cout << inputfile1 << " doesn't exist !! " <<endl;
    return;
  }
  if(infile1.fail()){
    cout << inputfile2 << " doesn't exist !! " <<endl;
    return;
  }
  if (msize < 2 || msize > 10) {
    std::cout << "2 <= msize <= 10" <<std::endl;
    return;
  }
  std::cout << "--------------------------------------------------------" <<std::endl;
  std::cout << "Inversion results for a ("<<msize<<","<<msize<<") matrix" <<std::endl;
  std::cout << "For each inversion procedure we check the maximum size  " <<std::endl;
  std::cout << "of the off-diagonal elements of Inv(A) * A              " <<std::endl;
  std::cout << "--------------------------------------------------------" <<std::endl;

  ostringstream sstr0;
  sstr0<<"./dit_txt/maindet_dithering_slope_run"<<runNo<<".txt";
  ofstream outfile0(sstr0.str().c_str());
  sstr0.str("");
  vector<Double_t> cycles;
  const int n=30;
  const int m=24;
  const int t=6;
  string bpm_name[n];
  string detector_name[m];
  string atdet_name[m];
    int bpm4ax_run[t],bpm4ax_flag[t],bpm_run[n],bpm_flag[n],detector_run[m],detector_flag[m],atdet_run[m],atdet_flag[m];
    double bpm_cyc[n],bpm_coil1[n],bpm_coil1_error[n],bpmEntry_coil1[n],bpm_coil2[n],bpm_coil2_error[n],bpmEntry_coil2[n],bpm_coil3[n],bpm_coil3_error[n],bpmEntry_coil3[n],bpm_coil4[n],bpm_coil4_error[n],bpmEntry_coil4[n],bpm_coil5[n],bpm_coil5_error[n],bpmEntry_coil5[n],bpm_coil6[n],bpm_coil6_error[n],bpmEntry_coil6[n],bpm_coil7[n],bpm_coil7_error[n],bpmEntry_coil7[n];

  double bpm4ax_cyc[t],bpm4ax_name[t],bpm4ax_coil1[t],bpm4ax_coil1_error[t],bpm4axEntry_coil1[t],bpm4ax_coil2[t],bpm4ax_coil2_error[t],bpm4axEntry_coil2[t],bpm4ax_coil3[t],bpm4ax_coil3_error[t],bpm4axEntry_coil3[t],bpm4ax_coil4[t],bpm4ax_coil4_error[t],bpm4axEntry_coil4[t],bpm4ax_coil5[t],bpm4ax_coil5_error[t],bpm4axEntry_coil5[t],bpm4ax_coil6[t],bpm4ax_coil6_error[t],bpm4axEntry_coil6[t],bpm4ax_coil7[t],bpm4ax_coil7_error[t],bpm4axEntry_coil7[t];

  double bpm4ex_cyc[t],bpm4ex_name[t],bpm4ex_coil1[t],bpm4ex_coil1_error[t],bpm4exEntry_coil1[t],bpm4ex_coil2[t],bpm4ex_coil2_error[t],bpm4exEntry_coil2[t],bpm4ex_coil3[t],bpm4ex_coil3_error[t],bpm4exEntry_coil3[t],bpm4ex_coil4[t],bpm4ex_coil4_error[t],bpm4exEntry_coil4[t],bpm4ex_coil5[t],bpm4ex_coil5_error[t],bpm4exEntry_coil5[t],bpm4ex_coil6[t],bpm4ex_coil6_error[t],bpm4exEntry_coil6[t],bpm4ex_coil7[t],bpm4ex_coil7_error[t],bpm4exEntry_coil7[t]; 

  double bpm4ay_cyc[t],bpm4ay_name[t],bpm4ay_coil1[t],bpm4ay_coil1_error[t],bpm4ayEntry_coil1[t],bpm4ay_coil2[t],bpm4ay_coil2_error[t],bpm4ayEntry_coil2[t],bpm4ay_coil3[t],bpm4ay_coil3_error[t],bpm4ayEntry_coil3[t],bpm4ay_coil4[t],bpm4ay_coil4_error[t],bpm4ayEntry_coil4[t],bpm4ay_coil5[t],bpm4ay_coil5_error[t],bpm4ayEntry_coil5[t],bpm4ay_coil6[t],bpm4ay_coil6_error[t],bpm4ayEntry_coil6[t],bpm4ay_coil7[t],bpm4ay_coil7_error[t],bpm4ayEntry_coil7[t]; 

  double bpm4ey_cyc[t],bpm4ey_name[t],bpm4ey_coil1[t],bpm4ey_coil1_error[t],bpm4eyEntry_coil1[t],bpm4ey_coil2[t],bpm4ey_coil2_error[t],bpm4eyEntry_coil2[t],bpm4ey_coil3[t],bpm4ey_coil3_error[t],bpm4eyEntry_coil3[t],bpm4ey_coil4[t],bpm4ey_coil4_error[t],bpm4eyEntry_coil4[t],bpm4ey_coil5[t],bpm4ey_coil5_error[t],bpm4eyEntry_coil5[t],bpm4ey_coil6[t],bpm4ey_coil6_error[t],bpm4eyEntry_coil6[t],bpm4ey_coil7[t],bpm4ey_coil7_error[t],bpm4eyEntry_coil7[t]; 

  double bpm12x_cyc[t],bpm12x_name[t],bpm12x_coil1[t],bpm12x_coil1_error[t],bpm12xEntry_coil1[t],bpm12x_coil2[t],bpm12x_coil2_error[t],bpm12xEntry_coil2[t],bpm12x_coil3[t],bpm12x_coil3_error[t],bpm12xEntry_coil3[t],bpm12x_coil4[t],bpm12x_coil4_error[t],bpm12xEntry_coil4[t],bpm12x_coil5[t],bpm12x_coil5_error[t],bpm12xEntry_coil5[t],bpm12x_coil6[t],bpm12x_coil6_error[t],bpm12xEntry_coil6[t],bpm12x_coil7[t],bpm12x_coil7_error[t],bpm12xEntry_coil7[t]; 


  double detector_cyc[m], detector_coil1[m],detector_coil1_error[m],detectorEntry_coil1[m], detector_coil2[m],detector_coil2_error[m],detectorEntry_coil2[m], detector_coil3[m],detector_coil3_error[m],detectorEntry_coil3[m],detector_coil4[m],detector_coil4_error[m],detectorEntry_coil4[m],detector_coil5[m],detector_coil5_error[m],detectorEntry_coil5[m],detector_coil6[m],detector_coil6_error[m],detectorEntry_coil6[m],detector_coil7[m],detector_coil7_error[m],detectorEntry_coil7[m];

  double usl_cyc[t],usl_name[t], usl_coil1[t],usl_coil1_error[t],uslEntry_coil1[t], usl_coil2[t],usl_coil2_error[t],uslEntry_coil2[t], usl_coil3[t],usl_coil3_error[t],uslEntry_coil3[t],usl_coil4[t],usl_coil4_error[t],uslEntry_coil4[t],usl_coil5[t],usl_coil5_error[t],uslEntry_coil5[t],usl_coil6[t],usl_coil6_error[t],uslEntry_coil6[t],usl_coil7[t],usl_coil7_error[t],uslEntry_coil7[t];

  double dsl_cyc[t],dsl_name[t],dsl_coil1[t],dsl_coil1_error[t],dslEntry_coil1[t], dsl_coil2[t],dsl_coil2_error[t],dslEntry_coil2[t], dsl_coil3[t],dsl_coil3_error[t],dslEntry_coil3[t],dsl_coil4[t],dsl_coil4_error[t],dslEntry_coil4[t],dsl_coil5[t],dsl_coil5_error[t],dslEntry_coil5[t],dsl_coil6[t],dsl_coil6_error[t],dslEntry_coil6[t],dsl_coil7[t],dsl_coil7_error[t],dslEntry_coil7[t];

  double usr_cyc[t],usr_name[t],usr_coil1[t],usr_coil1_error[t],usrEntry_coil1[t], usr_coil2[t],usr_coil2_error[t],usrEntry_coil2[t], usr_coil3[t],usr_coil3_error[t],usrEntry_coil3[t],usr_coil4[t],usr_coil4_error[t],usrEntry_coil4[t],usr_coil5[t],usr_coil5_error[t],usrEntry_coil5[t],usr_coil6[t],usr_coil6_error[t],usrEntry_coil6[t],usr_coil7[t],usr_coil7_error[t],usrEntry_coil7[t];

  double dsr_cyc[t],dsr_name[t],dsr_coil1[t],dsr_coil1_error[t],dsrEntry_coil1[t], dsr_coil2[t],dsr_coil2_error[t],dsrEntry_coil2[t], dsr_coil3[t],dsr_coil3_error[t],dsrEntry_coil3[t],dsr_coil4[t],dsr_coil4_error[t],dsrEntry_coil4[t],dsr_coil5[t],dsr_coil5_error[t],dsrEntry_coil5[t],dsr_coil6[t],dsr_coil6_error[t],dsrEntry_coil6[t],dsr_coil7[t],dsr_coil7_error[t],dsrEntry_coil7[t];
  double  atdet_cyc[m], atdet_coil1[m],atdet_coil1_error[m],atdetEntry_coil1[m], atdet_coil2[m],atdet_coil2_error[m],atdetEntry_coil2[m], atdet_coil3[m],atdet_coil3_error[m],atdetEntry_coil3[m],atdet_coil4[m],atdet_coil4_error[m],atdetEntry_coil4[m],atdet_coil5[m],atdet_coil5_error[m],atdetEntry_coil5[m],atdet_coil6[m],atdet_coil6_error[m],atdetEntry_coil6[m],atdet_coil7[m],atdet_coil7_error[m],atdetEntry_coil7[m];

  double atl1_cyc[t],atl1_name[t], atl1_coil1[t],atl1_coil1_error[t],atl1Entry_coil1[t], atl1_coil2[t],atl1_coil2_error[t],atl1Entry_coil2[t], atl1_coil3[t],atl1_coil3_error[t],atl1Entry_coil3[t],atl1_coil4[t],atl1_coil4_error[t],atl1Entry_coil4[t],atl1_coil5[t],atl1_coil5_error[t],atl1Entry_coil5[t],atl1_coil6[t],atl1_coil6_error[t],atl1Entry_coil6[t],atl1_coil7[t],atl1_coil7_error[t],atl1Entry_coil7[t];

  double atl2_cyc[t],atl2_name[t],atl2_coil1[t],atl2_coil1_error[t],atl2Entry_coil1[t], atl2_coil2[t],atl2_coil2_error[t],atl2Entry_coil2[t], atl2_coil3[t],atl2_coil3_error[t],atl2Entry_coil3[t],atl2_coil4[t],atl2_coil4_error[t],atl2Entry_coil4[t],atl2_coil5[t],atl2_coil5_error[t],atl2Entry_coil5[t],atl2_coil6[t],atl2_coil6_error[t],atl2Entry_coil6[t],atl2_coil7[t],atl2_coil7_error[t],atl2Entry_coil7[t];

  double atr1_cyc[t],atr1_name[t],atr1_coil1[t],atr1_coil1_error[t],atr1Entry_coil1[t], atr1_coil2[t],atr1_coil2_error[t],atr1Entry_coil2[t], atr1_coil3[t],atr1_coil3_error[t],atr1Entry_coil3[t],atr1_coil4[t],atr1_coil4_error[t],atr1Entry_coil4[t],atr1_coil5[t],atr1_coil5_error[t],atr1Entry_coil5[t],atr1_coil6[t],atr1_coil6_error[t],atr1Entry_coil6[t],atr1_coil7[t],atr1_coil7_error[t],atr1Entry_coil7[t];

  double atr2_cyc[t],atr2_name[t],atr2_coil1[t],atr2_coil1_error[t],atr2Entry_coil1[t], atr2_coil2[t],atr2_coil2_error[t],atr2Entry_coil2[t], atr2_coil3[t],atr2_coil3_error[t],atr2Entry_coil3[t],atr2_coil4[t],atr2_coil4_error[t],atr2Entry_coil4[t],atr2_coil5[t],atr2_coil5_error[t],atr2Entry_coil5[t],atr2_coil6[t],atr2_coil6_error[t],atr2Entry_coil6[t],atr2_coil7[t],atr2_coil7_error[t],atr2Entry_coil7[t];

  for(int i=0;i<n;i++){
    infile>>bpm_run[i]>>bpm_cyc[i]>>bpm_flag[i]>>bpm_name[i]>>bpm_coil1[i]>>bpm_coil1_error[i]>>bpmEntry_coil1[i]>>bpm_coil2[i]>>bpm_coil2_error[i]>>bpmEntry_coil2[i]>>bpm_coil3[i]>>bpm_coil3_error[i]>>bpmEntry_coil3[i]>>bpm_coil4[i]>>bpm_coil4_error[i]>>bpmEntry_coil4[i]>>bpm_coil5[i]>>bpm_coil5_error[i]>>bpmEntry_coil5[i]>>bpm_coil6[i]>>bpm_coil6_error[i]>>bpmEntry_coil6[i]>>bpm_coil7[i]>>bpm_coil7_error[i]>>bpmEntry_coil7[i];

  }

  for(int i=0;i<m;i++){
    infile1>>detector_run[i]>>detector_cyc[i]>>detector_flag[i]>>detector_name[i]>>detector_coil1[i]>>detector_coil1_error[i]>>detectorEntry_coil1[i]>>detector_coil2[i]>>detector_coil2_error[i]>>detectorEntry_coil2[i]>>detector_coil3[i]>>detector_coil3_error[i]>>detectorEntry_coil3[i]>>detector_coil4[i]>>detector_coil4_error[i]>>detectorEntry_coil4[i]>>detector_coil5[i]>>detector_coil5_error[i]>>detectorEntry_coil5[i]>>detector_coil6[i]>>detector_coil6_error[i]>>detectorEntry_coil6[i]>>detector_coil7[i]>>detector_coil7_error[i]>>detectorEntry_coil7[i];
  }
  for(int i=0;i<m;i++){
    infile2>>atdet_run[i]>>atdet_cyc[i]>>atdet_flag[i]>>atdet_name[i]>>atdet_coil1[i]>>atdet_coil1_error[i]>>atdetEntry_coil1[i]>>atdet_coil2[i]>>atdet_coil2_error[i]>>atdetEntry_coil2[i]>>atdet_coil3[i]>>atdet_coil3_error[i]>>atdetEntry_coil3[i]>>atdet_coil4[i]>>atdet_coil4_error[i]>>atdetEntry_coil4[i]>>atdet_coil5[i]>>atdet_coil5_error[i]>>atdetEntry_coil5[i]>>atdet_coil6[i]>>atdet_coil6_error[i]>>atdetEntry_coil6[i]>>atdet_coil7[i]>>atdet_coil7_error[i]>>atdetEntry_coil7[i];
  }

  for(int j=0;j<t;j++){
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

    bpm4ax_cyc[j]=bpm_cyc[j*5];
    bpm4ex_cyc[j]=bpm_cyc[j*5+1];
    bpm4ay_cyc[j]=bpm_cyc[j*5+2];
    bpm4ey_cyc[j]=bpm_cyc[j*5+3];
    bpm12x_cyc[j]=bpm_cyc[j*5+4];
    bpm4ax_run[j]=bpm_run[j*5];
    bpm4ax_flag[j]=bpm_flag[j*5];
    usl_coil1[j]=detector_coil1[j*4];
    usl_coil2[j]=detector_coil2[j*4];
    usl_coil3[j]=detector_coil3[j*4];
    usl_coil4[j]=detector_coil4[j*4];
    usl_coil5[j]=detector_coil5[j*4];
    usl_coil6[j]=detector_coil6[j*4];
    usl_coil7[j]=detector_coil7[j*4];

    dsl_coil1[j]=detector_coil1[j*4+1];
    dsl_coil2[j]=detector_coil2[j*4+1];
    dsl_coil3[j]=detector_coil3[j*4+1];
    dsl_coil4[j]=detector_coil4[j*4+1];
    dsl_coil5[j]=detector_coil5[j*4+1];
    dsl_coil6[j]=detector_coil6[j*4+1];
    dsl_coil7[j]=detector_coil7[j*4+1];


    usr_coil1[j]=detector_coil1[j*4+2];
    usr_coil2[j]=detector_coil2[j*4+2];
    usr_coil3[j]=detector_coil3[j*4+2];
    usr_coil4[j]=detector_coil4[j*4+2];
    usr_coil5[j]=detector_coil5[j*4+2];
    usr_coil6[j]=detector_coil6[j*4+2];
    usr_coil7[j]=detector_coil7[j*4+2];

    dsr_coil1[j]=detector_coil1[j*4+3];
    dsr_coil2[j]=detector_coil2[j*4+3];
    dsr_coil3[j]=detector_coil3[j*4+3];
    dsr_coil4[j]=detector_coil4[j*4+3];
    dsr_coil5[j]=detector_coil5[j*4+3];
    dsr_coil6[j]=detector_coil6[j*4+3];
    dsr_coil7[j]=detector_coil7[j*4+3];


    usl_coil1_error[j]=detector_coil1_error[j*4];
    usl_coil2_error[j]=detector_coil2_error[j*4];
    usl_coil3_error[j]=detector_coil3_error[j*4];
    usl_coil4_error[j]=detector_coil4_error[j*4];
    usl_coil5_error[j]=detector_coil5_error[j*4];
    usl_coil6_error[j]=detector_coil6_error[j*4];
    usl_coil7_error[j]=detector_coil7_error[j*4];

    dsl_coil1_error[j]=detector_coil1_error[j*4+1];
    dsl_coil2_error[j]=detector_coil2_error[j*4+1];
    dsl_coil3_error[j]=detector_coil3_error[j*4+1];
    dsl_coil4_error[j]=detector_coil4_error[j*4+1];
    dsl_coil5_error[j]=detector_coil5_error[j*4+1];
    dsl_coil6_error[j]=detector_coil6_error[j*4+1];
    dsl_coil7_error[j]=detector_coil7_error[j*4+1];


    usr_coil1_error[j]=detector_coil1_error[j*4+2];
    usr_coil2_error[j]=detector_coil2_error[j*4+2];
    usr_coil3_error[j]=detector_coil3_error[j*4+2];
    usr_coil4_error[j]=detector_coil4_error[j*4+2];
    usr_coil5_error[j]=detector_coil5_error[j*4+2];
    usr_coil6_error[j]=detector_coil6_error[j*4+2];
    usr_coil7_error[j]=detector_coil7_error[j*4+2];

    dsr_coil1_error[j]=detector_coil1_error[j*4+3];
    dsr_coil2_error[j]=detector_coil2_error[j*4+3];
    dsr_coil3_error[j]=detector_coil3_error[j*4+3];
    dsr_coil4_error[j]=detector_coil4_error[j*4+3];
    dsr_coil5_error[j]=detector_coil5_error[j*4+3];
    dsr_coil6_error[j]=detector_coil6_error[j*4+3];
    dsr_coil7_error[j]=detector_coil7_error[j*4+3];

//AT detectors

    atl1_coil1[j]=atdet_coil1[j*4];
    atl1_coil2[j]=atdet_coil2[j*4];
    atl1_coil3[j]=atdet_coil3[j*4];
    atl1_coil4[j]=atdet_coil4[j*4];
    atl1_coil5[j]=atdet_coil5[j*4];
    atl1_coil6[j]=atdet_coil6[j*4];
    atl1_coil7[j]=atdet_coil7[j*4];

    atl2_coil1[j]=atdet_coil1[j*4+1];
    atl2_coil2[j]=atdet_coil2[j*4+1];
    atl2_coil3[j]=atdet_coil3[j*4+1];
    atl2_coil4[j]=atdet_coil4[j*4+1];
    atl2_coil5[j]=atdet_coil5[j*4+1];
    atl2_coil6[j]=atdet_coil6[j*4+1];
    atl2_coil7[j]=atdet_coil7[j*4+1];


    atr1_coil1[j]=atdet_coil1[j*4+2];
    atr1_coil2[j]=atdet_coil2[j*4+2];
    atr1_coil3[j]=atdet_coil3[j*4+2];
    atr1_coil4[j]=atdet_coil4[j*4+2];
    atr1_coil5[j]=atdet_coil5[j*4+2];
    atr1_coil6[j]=atdet_coil6[j*4+2];
    atr1_coil7[j]=atdet_coil7[j*4+2];

    atr2_coil1[j]=atdet_coil1[j*4+3];
    atr2_coil2[j]=atdet_coil2[j*4+3];
    atr2_coil3[j]=atdet_coil3[j*4+3];
    atr2_coil4[j]=atdet_coil4[j*4+3];
    atr2_coil5[j]=atdet_coil5[j*4+3];
    atr2_coil6[j]=atdet_coil6[j*4+3];
    atr2_coil7[j]=atdet_coil7[j*4+3];


    atl1_coil1_error[j]=atdet_coil1_error[j*4];
    atl1_coil2_error[j]=atdet_coil2_error[j*4];
    atl1_coil3_error[j]=atdet_coil3_error[j*4];
    atl1_coil4_error[j]=atdet_coil4_error[j*4];
    atl1_coil5_error[j]=atdet_coil5_error[j*4];
    atl1_coil6_error[j]=atdet_coil6_error[j*4];
    atl1_coil7_error[j]=atdet_coil7_error[j*4];

    atl2_coil1_error[j]=atdet_coil1_error[j*4+1];
    atl2_coil2_error[j]=atdet_coil2_error[j*4+1];
    atl2_coil3_error[j]=atdet_coil3_error[j*4+1];
    atl2_coil4_error[j]=atdet_coil4_error[j*4+1];
    atl2_coil5_error[j]=atdet_coil5_error[j*4+1];
    atl2_coil6_error[j]=atdet_coil6_error[j*4+1];
    atl2_coil7_error[j]=atdet_coil7_error[j*4+1];


    atr1_coil1_error[j]=atdet_coil1_error[j*4+2];
    atr1_coil2_error[j]=atdet_coil2_error[j*4+2];
    atr1_coil3_error[j]=atdet_coil3_error[j*4+2];
    atr1_coil4_error[j]=atdet_coil4_error[j*4+2];
    atr1_coil5_error[j]=atdet_coil5_error[j*4+2];
    atr1_coil6_error[j]=atdet_coil6_error[j*4+2];
    atr1_coil7_error[j]=atdet_coil7_error[j*4+2];

    atr2_coil1_error[j]=atdet_coil1_error[j*4+3];
    atr2_coil2_error[j]=atdet_coil2_error[j*4+3];
    atr2_coil3_error[j]=atdet_coil3_error[j*4+3];
    atr2_coil4_error[j]=atdet_coil4_error[j*4+3];
    atr2_coil5_error[j]=atdet_coil5_error[j*4+3];
    atr2_coil6_error[j]=atdet_coil6_error[j*4+3];
    atr2_coil7_error[j]=atdet_coil7_error[j*4+3];
    if(bpm4ax_cyc[j]>1){
     cycles.push_back(bpm4ax_cyc[j]);
   }

  }
  Int_t flags[cycles.size()];
  //cyc1
  
  TMatrixD H_square(msize,msize);

  H_square[0][0] = bpm4ax_coil1[0];
  H_square[0][1] = bpm4ex_coil1[0];
  H_square[0][2] = bpm12x_coil1[0];
  H_square[0][3] = bpm4ay_coil1[0];
  H_square[0][4] = bpm4ey_coil1[0];
  H_square[1][0] = bpm4ax_coil3[0];
  H_square[1][1] = bpm4ex_coil3[0];
  H_square[1][2] = bpm12x_coil3[0];
  H_square[1][3] = bpm4ay_coil3[0];
  H_square[1][4] = bpm4ey_coil3[0];
  H_square[2][0] = bpm4ax_coil7[0];
  H_square[2][1] = bpm4ex_coil7[0];
  H_square[2][2] = bpm12x_coil7[0];
  H_square[2][3] = bpm4ay_coil7[0];
  H_square[2][4] = bpm4ey_coil7[0];
  H_square[3][0] = bpm4ax_coil4[0];
  H_square[3][1] = bpm4ex_coil4[0];
  H_square[3][2] = bpm12x_coil4[0];
  H_square[3][3] = bpm4ay_coil4[0];
  H_square[3][4] = bpm4ey_coil4[0];
  H_square[4][0] = bpm4ax_coil6[0];
  H_square[4][1] = bpm4ex_coil6[0];
  H_square[4][2] = bpm12x_coil6[0];
  H_square[4][3] = bpm4ay_coil6[0];
  H_square[4][4] = bpm4ey_coil6[0];
    
  TMatrixD H_usl(5,1);
  H_usl[0][0] = usl_coil1[0];
  H_usl[1][0] = usl_coil3[0];
  H_usl[2][0] = usl_coil7[0];
  H_usl[3][0] = usl_coil4[0];
  H_usl[4][0] = usl_coil6[0];

  TMatrixD H_usr(5,1);
  H_usr[0][0] = usr_coil1[0];
  H_usr[1][0] = usr_coil3[0];
  H_usr[2][0] = usr_coil7[0];
  H_usr[3][0] = usr_coil4[0];
  H_usr[4][0] = usr_coil6[0];

  TMatrixD H_dsl(5,1);
  H_dsl[0][0] = dsl_coil1[0];
  H_dsl[1][0] = dsl_coil3[0];
  H_dsl[2][0] = dsl_coil7[0];
  H_dsl[3][0] = dsl_coil4[0];
  H_dsl[4][0] = dsl_coil6[0];

  TMatrixD H_dsr(5,1);
  H_dsr[0][0] = dsr_coil1[0];
  H_dsr[1][0] = dsr_coil3[0];
  H_dsr[2][0] = dsr_coil7[0];
  H_dsr[3][0] = dsr_coil4[0];
  H_dsr[4][0] = dsr_coil6[0];
// AT detector
  TMatrixD H_atl1(5,1);
  H_atl1[0][0] = atl1_coil1[0];
  H_atl1[1][0] = atl1_coil3[0];
  H_atl1[2][0] = atl1_coil7[0];
  H_atl1[3][0] = atl1_coil4[0];
  H_atl1[4][0] = atl1_coil6[0];

  TMatrixD H_atr1(5,1);
  H_atr1[0][0] = atr1_coil1[0];
  H_atr1[1][0] = atr1_coil3[0];
  H_atr1[2][0] = atr1_coil7[0];
  H_atr1[3][0] = atr1_coil4[0];
  H_atr1[4][0] = atr1_coil6[0];

  TMatrixD H_atl2(5,1);
  H_atl2[0][0] = atl2_coil1[0];
  H_atl2[1][0] = atl2_coil3[0];
  H_atl2[2][0] = atl2_coil7[0];
  H_atl2[3][0] = atl2_coil4[0];
  H_atl2[4][0] = atl2_coil6[0];

  TMatrixD H_atr2(5,1);
  H_atr2[0][0] = atr2_coil1[0];
  H_atr2[1][0] = atr2_coil3[0];
  H_atr2[2][0] = atr2_coil7[0];
  H_atr2[3][0] = atr2_coil4[0];
  H_atr2[4][0] = atr2_coil6[0];
  std::cout << "H_square" << std::endl;
  H_square.Print();
  std::cout << "2. Use .Invert(&det)" << std::endl;
  Double_t det2;
  TMatrixD H2 = H_square;
  H2.Invert(&det2);
  H2.Print();
  std::cout << "unity matrix" << std::endl;
  TMatrixD D(msize,msize);
  D.Mult(H_square,H2);
  D.Print();

  std::cout << "detector matrix" << std::endl;
  cout << "--usl: " <<endl;
  H_usl.Print();
  cout << "--usr: " <<endl;
  H_usr.Print();
  cout << "--dsl: " <<endl;
  H_dsl.Print();
  cout << "--dsr: " <<endl;
  H_dsr.Print();

  cout << "--atl1: " <<endl;
  H_atl1.Print();
  cout << "--atr1: " <<endl;
  H_atr2.Print();
  cout << "--atl2: " <<endl;
  H_atl2.Print();
  cout << "--atr2: " <<endl;
  H_atr2.Print();
  std::cout << "slope" << std::endl;
  TMatrixD Cusl(msize,1);
  TMatrixD Cusr(msize,1);
  TMatrixD Cdsl(msize,1);
  TMatrixD Cdsr(msize,1);
  TMatrixD Catl1(msize,1);
  TMatrixD Catr1(msize,1);
  TMatrixD Catl2(msize,1);
  TMatrixD Catr2(msize,1);

  cout << "--usl: " <<endl;
  Cusl.Mult(H2,H_usl);
  Cusl.Print();
 
  cout << "--usr: " <<endl;
  Cusr.Mult(H2,H_usr);
  Cusr.Print();
 
  cout << "--dsl: " <<endl;
  Cdsl.Mult(H2,H_dsl);
  Cdsl.Print();

  cout << "--dsr: " <<endl;
  Cdsr.Mult(H2,H_dsr);
  Cdsr.Print();

  cout << "--atl1: " <<endl;
  Catl1.Mult(H2,H_atl1);
  Catl1.Print();
 
  cout << "--atr1: " <<endl;
  Catr1.Mult(H2,H_atr1);
  Catr1.Print();
 
  cout << "--atl2: " <<endl;
  Catl2.Mult(H2,H_atl2);
  Catl2.Print();

  cout << "--atr2: " <<endl;
  Catr2.Mult(H2,H_atr2);
  Catr2.Print();

// cyc 2 
    TMatrixD H_square2(msize,msize);

		  H_square2[0][0] = bpm4ax_coil1[1];
                  H_square2[0][1] = bpm4ex_coil1[1];
                  H_square2[0][2] = bpm12x_coil1[1];
                  H_square2[0][3] = bpm4ay_coil1[1];
                  H_square2[0][4] = bpm4ey_coil1[1];
		  H_square2[1][0] = bpm4ax_coil3[1];
                  H_square2[1][1] = bpm4ex_coil3[1]; 
                  H_square2[1][2] = bpm12x_coil3[1];
                  H_square2[1][3] = bpm4ay_coil3[1];
                  H_square2[1][4] = bpm4ey_coil3[1];
		  H_square2[2][0] = bpm4ax_coil7[1];
                  H_square2[2][1] = bpm4ex_coil7[1];
                  H_square2[2][2] = bpm12x_coil7[1];
                  H_square2[2][3] = bpm4ay_coil7[1];
                  H_square2[2][4] = bpm4ey_coil7[1];
		  H_square2[3][0] = bpm4ax_coil4[1];
                  H_square2[3][1] = bpm4ex_coil4[1];
                  H_square2[3][2] = bpm12x_coil4[1];
                  H_square2[3][3] = bpm4ay_coil4[1];
                  H_square2[3][4] = bpm4ey_coil4[1];
		  H_square2[4][0] = bpm4ax_coil6[1];
                  H_square2[4][1] = bpm4ex_coil6[1];
                  H_square2[4][2] = bpm12x_coil6[1];
                  H_square2[4][3] = bpm4ay_coil6[1];
                  H_square2[4][4] = bpm4ey_coil6[1];
    
  TMatrixD H_usl1(5,1);
  H_usl1[0][0] = usl_coil1[1];
  H_usl1[1][0] = usl_coil3[1];
  H_usl1[2][0] = usl_coil7[1];
  H_usl1[3][0] = usl_coil4[1];
  H_usl1[4][0] = usl_coil6[1];
  TMatrixD H_usr1(5,1);
  H_usr1[0][0] = usr_coil1[1];
  H_usr1[1][0] = usr_coil3[1];
  H_usr1[2][0] = usr_coil7[1];
  H_usr1[3][0] = usr_coil4[1];
  H_usr1[4][0] = usr_coil6[1];

  TMatrixD H_dsl1(5,1);
  H_dsl1[0][0] = dsl_coil1[1];
  H_dsl1[1][0] = dsl_coil3[1];
  H_dsl1[2][0] = dsl_coil7[1];
  H_dsl1[3][0] = dsl_coil4[1];
  H_dsl1[4][0] = dsl_coil6[1];

  TMatrixD H_dsr1(5,1);
  H_dsr1[0][0] = dsr_coil1[1];
  H_dsr1[1][0] = dsr_coil3[1];
  H_dsr1[2][0] = dsr_coil7[1];
  H_dsr1[3][0] = dsr_coil4[1];
  H_dsr1[4][0] = dsr_coil6[1];
// AT detector
  TMatrixD H_atl11(5,1);
  H_atl11[0][0] = atl1_coil1[1];
  H_atl11[1][0] = atl1_coil3[1];
  H_atl11[2][0] = atl1_coil7[1];
  H_atl11[3][0] = atl1_coil4[1];
  H_atl11[4][0] = atl1_coil6[1];

  TMatrixD H_atr11(5,1);
  H_atr11[0][0] = atr1_coil1[1];
  H_atr11[1][0] = atr1_coil3[1];
  H_atr11[2][0] = atr1_coil7[1];
  H_atr11[3][0] = atr1_coil4[1];
  H_atr11[4][0] = atr1_coil6[1];

  TMatrixD H_atl21(5,1);
  H_atl21[0][0] = atl2_coil1[1];
  H_atl21[1][0] = atl2_coil3[1];
  H_atl21[2][0] = atl2_coil7[1];
  H_atl21[3][0] = atl2_coil4[1];
  H_atl21[4][0] = atl2_coil6[1];

  TMatrixD H_atr21(5,1);
  H_atr21[0][0] = atr2_coil1[1];
  H_atr21[1][0] = atr2_coil3[1];
  H_atr21[2][0] = atr2_coil7[1];
  H_atr21[3][0] = atr2_coil4[1];
  H_atr21[4][0] = atr2_coil6[1];
    std::cout << "H_square" << std::endl;
    H_square2.Print();
    std::cout << "2. Use .Invert(&det)" << std::endl;
    Double_t det2_2;
    TMatrixD H2_2 = H_square2;
    H2_2.Invert(&det2_2);
    H2_2.Print();
    std::cout << "unity matrix" << std::endl;
    TMatrixD D2(msize,msize);
    D2.Mult(H_square2,H2_2);
    D2.Print();
  std::cout << "detector matrix for cyc 2" << std::endl;
  cout << "--usl: " <<endl;
  H_usl1.Print();
  cout << "--usr: " <<endl;
  H_usr1.Print();
  cout << "--dsl: " <<endl;
  H_dsl1.Print();
  cout << "--dsr: " <<endl;
  H_dsr1.Print();

  cout << "--atl1: " <<endl;
  H_atl11.Print();
  cout << "--atr1: " <<endl;
  H_atr21.Print();
  cout << "--atl2: " <<endl;
  H_atl21.Print();
  cout << "--atr2: " <<endl;
  H_atr21.Print();
  std::cout << "slope" << std::endl;
  TMatrixD Cusl1(msize,1);
  TMatrixD Cusr1(msize,1);
  TMatrixD Cdsl1(msize,1);
  TMatrixD Cdsr1(msize,1);
  TMatrixD Catl11(msize,1);
  TMatrixD Catr11(msize,1);
  TMatrixD Catl21(msize,1);
  TMatrixD Catr21(msize,1);

  cout << "--usl: cyc2 " <<endl;
  Cusl1.Mult(H2_2,H_usl1);
  Cusl1.Print();
 
  cout << "--usr: " <<endl;
  Cusr1.Mult(H2_2,H_usr1);
  Cusr1.Print();
 
  cout << "--dsl: " <<endl;
  Cdsl1.Mult(H2_2,H_dsl1);
  Cdsl1.Print();

  cout << "--dsr: " <<endl;
  Cdsr1.Mult(H2_2,H_dsr1);
  Cdsr1.Print();

  cout << "--atl1: " <<endl;
  Catl11.Mult(H2_2,H_atl11);
  Catl11.Print();
 
  cout << "--atr1: " <<endl;
  Catr11.Mult(H2_2,H_atr11);
  Catr11.Print();
 
  cout << "--atl2: " <<endl;
  Catl21.Mult(H2_2,H_atl21);
  Catl21.Print();

  cout << "--atr2: " <<endl;
  Catr21.Mult(H2_2,H_atr21);
  Catr21.Print();


// cyc 3 
    TMatrixD H_square3(msize,msize);

		  H_square3[0][0] = bpm4ax_coil1[2];
                  H_square3[0][1] = bpm4ex_coil1[2];
                  H_square3[0][2] = bpm12x_coil1[2];
                  H_square3[0][3] = bpm4ay_coil1[2];
                  H_square3[0][4] = bpm4ey_coil1[2];
		  H_square3[1][0] = bpm4ax_coil3[2];
                  H_square3[1][1] = bpm4ex_coil3[2];
                  H_square3[1][2] = bpm12x_coil3[2];
                  H_square3[1][3] = bpm4ay_coil3[2];
                  H_square3[1][4] = bpm4ey_coil3[2];
		  H_square3[2][0] = bpm4ax_coil7[2];
                  H_square3[2][1] = bpm4ex_coil7[2];
                  H_square3[2][2] = bpm12x_coil7[2];
                  H_square3[2][3] = bpm4ay_coil7[2];
                  H_square3[2][4] = bpm4ey_coil7[2];
		  H_square3[3][0] = bpm4ax_coil4[2];
                  H_square3[3][1] = bpm4ex_coil4[2];
                  H_square3[3][2] = bpm12x_coil4[2];
                  H_square3[3][3] = bpm4ay_coil4[2];
                  H_square3[3][4] = bpm4ey_coil4[2];
		  H_square3[4][0] = bpm4ax_coil6[2];
                  H_square3[4][1] = bpm4ex_coil6[2];
                  H_square3[4][2] = bpm12x_coil6[2];
                  H_square3[4][3] = bpm4ay_coil6[2];
                  H_square3[4][4] = bpm4ey_coil6[2];
    
  TMatrixD H_usl2(5,1);
  H_usl2[0][0] = usl_coil1[2];
  H_usl2[1][0] = usl_coil3[2];
  H_usl2[2][0] = usl_coil7[2];
  H_usl2[3][0] = usl_coil4[2];
  H_usl2[4][0] = usl_coil6[2];
  TMatrixD H_usr2(5,1);
  H_usr2[0][0] = usr_coil1[2];
  H_usr2[1][0] = usr_coil3[2];
  H_usr2[2][0] = usr_coil7[2];
  H_usr2[3][0] = usr_coil4[2];
  H_usr2[4][0] = usr_coil6[2];

  TMatrixD H_dsl2(5,1);
  H_dsl2[0][0] = dsl_coil1[2];
  H_dsl2[1][0] = dsl_coil3[2];
  H_dsl2[2][0] = dsl_coil7[2];
  H_dsl2[3][0] = dsl_coil4[2];
  H_dsl2[4][0] = dsl_coil6[2];

  TMatrixD H_dsr2(5,1);
  H_dsr2[0][0] = dsr_coil1[2];
  H_dsr2[1][0] = dsr_coil3[2];
  H_dsr2[2][0] = dsr_coil7[2];
  H_dsr2[3][0] = dsr_coil4[2];
  H_dsr2[4][0] = dsr_coil6[2];
// AT detector
  TMatrixD H_atl12(5,1);
  H_atl12[0][0] = atl1_coil1[2];
  H_atl12[1][0] = atl1_coil3[2];
  H_atl12[2][0] = atl1_coil7[2];
  H_atl12[3][0] = atl1_coil4[2];
  H_atl12[4][0] = atl1_coil6[2];

  TMatrixD H_atr12(5,1);
  H_atr12[0][0] = atr1_coil1[2];
  H_atr12[1][0] = atr1_coil3[2];
  H_atr12[2][0] = atr1_coil7[2];
  H_atr12[3][0] = atr1_coil4[2];
  H_atr12[4][0] = atr1_coil6[2];

  TMatrixD H_atl22(5,1);
  H_atl22[0][0] = atl2_coil1[2];
  H_atl22[1][0] = atl2_coil3[2];
  H_atl22[2][0] = atl2_coil7[2];
  H_atl22[3][0] = atl2_coil4[2];
  H_atl22[4][0] = atl2_coil6[2];

  TMatrixD H_atr22(5,1);
  H_atr22[0][0] = atr2_coil1[2];
  H_atr22[1][0] = atr2_coil3[2];
  H_atr22[2][0] = atr2_coil7[2];
  H_atr22[3][0] = atr2_coil4[2];
  H_atr22[4][0] = atr2_coil6[2];
    std::cout << "H_square" << std::endl;
    H_square3.Print();
    std::cout << "2. Use .Invert(&det)" << std::endl;
    Double_t det2_3;
    TMatrixD H2_3 = H_square3;
    H2_3.Invert(&det2_3);
    H2_3.Print();
    std::cout << "unity matrix" << std::endl;
    TMatrixD D3(msize,msize);
    D3.Mult(H_square3,H2_3);
    D3.Print();
  std::cout << "detector matrix for cyc 3" << std::endl;
  cout << "--usl: " <<endl;
  H_usl2.Print();
  cout << "--usr: " <<endl;
  H_usr2.Print();
  cout << "--dsl: " <<endl;
  H_dsl2.Print();
  cout << "--dsr: " <<endl;
  H_dsr2.Print();

  cout << "--atl1: " <<endl;
  H_atl12.Print();
  cout << "--atr1: " <<endl;
  H_atr22.Print();
  cout << "--atl2: " <<endl;
  H_atl22.Print();
  cout << "--atr2: " <<endl;
  H_atr22.Print();
  std::cout << "slope cyc3" << std::endl;
  TMatrixD Cusl2(msize,1);
  TMatrixD Cusr2(msize,1);
  TMatrixD Cdsl2(msize,1);
  TMatrixD Cdsr2(msize,1);
  TMatrixD Catl12(msize,1);
  TMatrixD Catr12(msize,1);
  TMatrixD Catl22(msize,1);
  TMatrixD Catr22(msize,1);

  cout << "--usl: cyc3 " <<endl;
  Cusl2.Mult(H2_3,H_usl2);
  Cusl2.Print();
 
  cout << "--usr: " <<endl;
  Cusr2.Mult(H2_3,H_usr2);
  Cusr2.Print();

  cout << "--dsl: " <<endl;
  Cdsl2.Mult(H2_3,H_dsl2);
  Cdsl2.Print();

  cout << "--dsr: " <<endl;
  Cdsr2.Mult(H2_3,H_dsr2);
  Cdsr2.Print();

  cout << "--atl1: " <<endl;
  Catl12.Mult(H2_3,H_atl12);
  Catl12.Print();
 
  cout << "--atr1: " <<endl;
  Catr12.Mult(H2_3,H_atr12);
  Catr12.Print();
 
  cout << "--atl2: " <<endl;
  Catl22.Mult(H2_3,H_atl22);
  Catl22.Print();

  cout << "--atr2: " <<endl;
  Catr22.Mult(H2_3,H_atr22);
  Catr22.Print();

//cyc4
    TMatrixD H_square4(msize,msize);

		  H_square4[0][0] = bpm4ax_coil1[3];
                  H_square4[0][1] = bpm4ex_coil1[3];
                  H_square4[0][2] = bpm12x_coil1[3];
                  H_square4[0][3] = bpm4ay_coil1[3];
                  H_square4[0][4] = bpm4ey_coil1[3];
		  H_square4[1][0] = bpm4ax_coil3[3];
                  H_square4[1][1] = bpm4ex_coil3[3];
                  H_square4[1][2] = bpm12x_coil3[3];
                  H_square4[1][3] = bpm4ay_coil3[3];
                  H_square4[1][4] = bpm4ey_coil3[3];
		  H_square4[2][0] = bpm4ax_coil7[3];
                  H_square4[2][1] = bpm4ex_coil7[3];
                  H_square4[2][2] = bpm12x_coil7[3];
                  H_square4[2][3] = bpm4ay_coil7[3];
                  H_square4[2][4] = bpm4ey_coil7[3];
		  H_square4[3][0] = bpm4ax_coil4[3];
                  H_square4[3][1] = bpm4ex_coil4[3];
                  H_square4[3][2] = bpm12x_coil4[3];
                  H_square4[3][3] = bpm4ay_coil4[3];
                  H_square4[3][4] = bpm4ey_coil4[3];
		  H_square4[4][0] = bpm4ax_coil6[3];
                  H_square4[4][1] = bpm4ex_coil6[3];
                  H_square4[4][2] = bpm12x_coil6[3];
                  H_square4[4][3] = bpm4ay_coil6[3];
                  H_square4[4][4] = bpm4ey_coil6[3];
    
  TMatrixD H_usl3(5,1);
  H_usl3[0][0] = usl_coil1[3];
  H_usl3[1][0] = usl_coil3[3];
  H_usl3[2][0] = usl_coil7[3];
  H_usl3[3][0] = usl_coil4[3];
  H_usl3[4][0] = usl_coil6[3];
  TMatrixD H_usr3(5,1);
  H_usr3[0][0] = usr_coil1[3];
  H_usr3[1][0] = usr_coil3[3];
  H_usr3[2][0] = usr_coil7[3];
  H_usr3[3][0] = usr_coil4[3];
  H_usr3[4][0] = usr_coil6[3];

  TMatrixD H_dsl3(5,1);
  H_dsl3[0][0] = dsl_coil1[3];
  H_dsl3[1][0] = dsl_coil3[3];
  H_dsl3[2][0] = dsl_coil7[3];
  H_dsl3[3][0] = dsl_coil4[3];
  H_dsl3[4][0] = dsl_coil6[3];

  TMatrixD H_dsr3(5,1);
  H_dsr3[0][0] = dsr_coil1[3];
  H_dsr3[1][0] = dsr_coil3[3];
  H_dsr3[2][0] = dsr_coil7[3];
  H_dsr3[3][0] = dsr_coil4[3];
  H_dsr3[4][0] = dsr_coil6[3];
// AT detector
  TMatrixD H_atl13(5,1);
  H_atl13[0][0] = atl1_coil1[3];
  H_atl13[1][0] = atl1_coil3[3];
  H_atl13[2][0] = atl1_coil7[3];
  H_atl13[3][0] = atl1_coil4[3];
  H_atl13[4][0] = atl1_coil6[3];

  TMatrixD H_atr13(5,1);
  H_atr13[0][0] = atr1_coil1[3];
  H_atr13[1][0] = atr1_coil3[3];
  H_atr13[2][0] = atr1_coil7[3];
  H_atr13[3][0] = atr1_coil4[3];
  H_atr13[4][0] = atr1_coil6[3];

  TMatrixD H_atl23(5,1);
  H_atl23[0][0] = atl2_coil1[3];
  H_atl23[1][0] = atl2_coil3[3];
  H_atl23[2][0] = atl2_coil7[3];
  H_atl23[3][0] = atl2_coil4[3];
  H_atl23[4][0] = atl2_coil6[3];

  TMatrixD H_atr23(5,1);
  H_atr23[0][0] = atr2_coil1[3];
  H_atr23[1][0] = atr2_coil3[3];
  H_atr23[2][0] = atr2_coil7[3];
  H_atr23[3][0] = atr2_coil4[3];
  H_atr23[4][0] = atr2_coil6[3];
    std::cout << "H_square" << std::endl;
    H_square4.Print();
    std::cout << "2. Use .Invert(&det)" << std::endl;
    Double_t det2_4;
    TMatrixD H2_4 = H_square4;
    H2_4.Invert(&det2_4);
    H2_4.Print();
    std::cout << "unity matrix" << std::endl;
    TMatrixD D4(msize,msize);
    D4.Mult(H_square4,H2_4);
    D4.Print();
  std::cout << "detector matrix for cyc 4" << std::endl;
  cout << "--usl: " <<endl;
  H_usl3.Print();
  cout << "--usr: " <<endl;
  H_usr3.Print();
  cout << "--dsl: " <<endl;
  H_dsl3.Print();
  cout << "--dsr: " <<endl;
  H_dsr3.Print();

  cout << "--atl1: " <<endl;
  H_atl13.Print();
  cout << "--atr1: " <<endl;
  H_atr23.Print();
  cout << "--atl2: " <<endl;
  H_atl23.Print();
  cout << "--atr2: " <<endl;
  H_atr23.Print();
  std::cout << "slope cyc4" << std::endl;
  TMatrixD Cusl3(msize,1);
  TMatrixD Cusr3(msize,1);
  TMatrixD Cdsl3(msize,1);
  TMatrixD Cdsr3(msize,1);
  TMatrixD Catl13(msize,1);
  TMatrixD Catr13(msize,1);
  TMatrixD Catl23(msize,1);
  TMatrixD Catr23(msize,1);

  cout << "--usl: cyc4 " <<endl;
  Cusl3.Mult(H2_4,H_usl3);
  Cusl3.Print();
 
  cout << "--usr: " <<endl;
  Cusr3.Mult(H2_4,H_usr3);
  Cusr3.Print();

  cout << "--dsl: " <<endl;
  Cdsl3.Mult(H2_4,H_dsl3);
  Cdsl3.Print();

  cout << "--dsr: " <<endl;
  Cdsr3.Mult(H2_4,H_dsr3);
  Cdsr3.Print();

  cout << "--atl1: " <<endl;
  Catl13.Mult(H2_4,H_atl13);
  Catl13.Print();
 
  cout << "--atr1: " <<endl;
  Catr13.Mult(H2_4,H_atr13);
  Catr13.Print();
 
  cout << "--atl2: " <<endl;
  Catl23.Mult(H2_4,H_atl23);
  Catl23.Print();

  cout << "--atr2: " <<endl;
  Catr23.Mult(H2_4,H_atr23);
  Catr23.Print();

//cyc5
    TMatrixD H_square5(msize,msize);

		  H_square5[0][0] = bpm4ax_coil1[4];
                  H_square5[0][1] = bpm4ex_coil1[4];
                  H_square5[0][2] = bpm12x_coil1[4];
                  H_square5[0][3] = bpm4ay_coil1[4];
                  H_square5[0][4] = bpm4ey_coil1[4];
		  H_square5[1][0] = bpm4ax_coil3[4];
                  H_square5[1][1] = bpm4ex_coil3[4];
                  H_square5[1][2] = bpm12x_coil3[4];
                  H_square5[1][3] = bpm4ay_coil3[4];
                  H_square5[1][4] = bpm4ey_coil3[4];
		  H_square5[2][0] = bpm4ax_coil7[4];
                  H_square5[2][1] = bpm4ex_coil7[4];
                  H_square5[2][2] = bpm12x_coil7[4];
                  H_square5[2][3] = bpm4ay_coil7[4];
                  H_square5[2][4] = bpm4ey_coil7[4];
		  H_square5[3][0] = bpm4ax_coil4[4];
                  H_square5[3][1] = bpm4ex_coil4[4];
                  H_square5[3][2] = bpm12x_coil4[4];
                  H_square5[3][3] = bpm4ay_coil4[4];
                  H_square5[3][4] = bpm4ey_coil4[4];
		  H_square5[4][0] = bpm4ax_coil6[4];
                  H_square5[4][1] = bpm4ex_coil6[4];
                  H_square5[4][2] = bpm12x_coil6[4];
                  H_square5[4][3] = bpm4ay_coil6[4];
                  H_square5[4][4] = bpm4ey_coil6[4];
    
  TMatrixD H_usl4(5,1);
  H_usl4[0][0] = usl_coil1[4];
  H_usl4[1][0] = usl_coil3[4];
  H_usl4[2][0] = usl_coil7[4];
  H_usl4[3][0] = usl_coil4[4];
  H_usl4[4][0] = usl_coil6[4];
  TMatrixD H_usr4(5,1);
  H_usr4[0][0] = usr_coil1[4];
  H_usr4[1][0] = usr_coil3[4];
  H_usr4[2][0] = usr_coil7[4];
  H_usr4[3][0] = usr_coil4[4];
  H_usr4[4][0] = usr_coil6[4];

  TMatrixD H_dsl4(5,1);
  H_dsl4[0][0] = dsl_coil1[4];
  H_dsl4[1][0] = dsl_coil3[4];
  H_dsl4[2][0] = dsl_coil7[4];
  H_dsl4[3][0] = dsl_coil4[4];
  H_dsl4[4][0] = dsl_coil6[4];

  TMatrixD H_dsr4(5,1);
  H_dsr4[0][0] = dsr_coil1[4];
  H_dsr4[1][0] = dsr_coil3[4];
  H_dsr4[2][0] = dsr_coil7[4];
  H_dsr4[3][0] = dsr_coil4[4];
  H_dsr4[4][0] = dsr_coil6[4];
// AT detector
  TMatrixD H_atl14(5,1);
  H_atl14[0][0] = atl1_coil1[4];
  H_atl14[1][0] = atl1_coil3[4];
  H_atl14[2][0] = atl1_coil7[4];
  H_atl14[3][0] = atl1_coil4[4];
  H_atl14[4][0] = atl1_coil6[4];

  TMatrixD H_atr14(5,1);
  H_atr14[0][0] = atr1_coil1[4];
  H_atr14[1][0] = atr1_coil3[4];
  H_atr14[2][0] = atr1_coil7[4];
  H_atr14[3][0] = atr1_coil4[4];
  H_atr14[4][0] = atr1_coil6[4];

  TMatrixD H_atl24(5,1);
  H_atl24[0][0] = atl2_coil1[4];
  H_atl24[1][0] = atl2_coil3[4];
  H_atl24[2][0] = atl2_coil7[4];
  H_atl24[3][0] = atl2_coil4[4];
  H_atl24[4][0] = atl2_coil6[4];

  TMatrixD H_atr24(5,1);
  H_atr24[0][0] = atr2_coil1[4];
  H_atr24[1][0] = atr2_coil3[4];
  H_atr24[2][0] = atr2_coil7[4];
  H_atr24[3][0] = atr2_coil4[4];
  H_atr24[4][0] = atr2_coil6[4];
    std::cout << "H_square" << std::endl;
    H_square5.Print();
    std::cout << "2. Use .Invert(&det)" << std::endl;
    Double_t det2_5;
    TMatrixD H2_5 = H_square5;
    H2_5.Invert(&det2);
    H2_5.Print();
    std::cout << "unity matrix" << std::endl;
    TMatrixD D5(msize,msize);
    D5.Mult(H_square5,H2_5);
    D5.Print();
  std::cout << "detector matrix for cyc 5" << std::endl;
  cout << "--usl: " <<endl;
  H_usl4.Print();
  cout << "--usr: " <<endl;
  H_usr4.Print();
  cout << "--dsl: " <<endl;
  H_dsl4.Print();
  cout << "--dsr: " <<endl;
  H_dsr4.Print();

  cout << "--atl1: " <<endl;
  H_atl14.Print();
  cout << "--atr1: " <<endl;
  H_atr24.Print();
  cout << "--atl2: " <<endl;
  H_atl24.Print();
  cout << "--atr2: " <<endl;
  H_atr24.Print();
  std::cout << "slope cyc5" << std::endl;
  TMatrixD Cusl4(msize,1);
  TMatrixD Cusr4(msize,1);
  TMatrixD Cdsl4(msize,1);
  TMatrixD Cdsr4(msize,1);
  TMatrixD Catl14(msize,1);
  TMatrixD Catr14(msize,1);
  TMatrixD Catl24(msize,1);
  TMatrixD Catr24(msize,1);

  cout << "--usl: cyc4 " <<endl;
  Cusl4.Mult(H2_5,H_usl4);
  Cusl4.Print();
 
  cout << "--usr: " <<endl;
  Cusr4.Mult(H2_5,H_usr4);
  Cusr4.Print();

  cout << "--dsl: " <<endl;
  Cdsl4.Mult(H2_5,H_dsl4);
  Cdsl4.Print();

  cout << "--dsr: " <<endl;
  Cdsr4.Mult(H2_5,H_dsr4);
  Cdsr4.Print();

  cout << "--atl1: " <<endl;
  Catl14.Mult(H2_5,H_atl14);
  Catl14.Print();
 
  cout << "--atr1: " <<endl;
  Catr14.Mult(H2_5,H_atr14);
  Catr14.Print();
 
  cout << "--atl2: " <<endl;
  Catl24.Mult(H2_5,H_atl24);
  Catl24.Print();

  cout << "--atr2: " <<endl;
  Catr24.Mult(H2_5,H_atr24);
  Catr24.Print();

//cyc6
    TMatrixD H_square6(msize,msize);

		  H_square6[0][0] = bpm4ax_coil1[5];
                  H_square6[0][1] = bpm4ex_coil1[5];
                  H_square6[0][2] = bpm12x_coil1[5];
                  H_square6[0][3] = bpm4ay_coil1[5];
                  H_square6[0][4] = bpm4ey_coil1[5];
		  H_square6[1][0] = bpm4ax_coil3[5];
                  H_square6[1][1] = bpm4ex_coil3[5];
                  H_square6[1][2] = bpm12x_coil3[5];
                  H_square6[1][3] = bpm4ay_coil3[5];
                  H_square6[1][4] = bpm4ey_coil3[5];
		  H_square6[2][0] = bpm4ax_coil7[5];
                  H_square6[2][1] = bpm4ex_coil7[5];
                  H_square6[2][2] = bpm12x_coil7[5];
                  H_square6[2][3] = bpm4ay_coil7[5];
                  H_square6[2][4] = bpm4ey_coil7[5];
		  H_square6[3][0] = bpm4ax_coil4[5];
                  H_square6[3][1] = bpm4ex_coil4[5];
                  H_square6[3][2] = bpm12x_coil4[5];
                  H_square6[3][3] = bpm4ay_coil4[5];
                  H_square6[3][4] = bpm4ey_coil4[5];
		  H_square6[4][0] = bpm4ax_coil6[5];
                  H_square6[4][1] = bpm4ex_coil6[5];
                  H_square6[4][2] = bpm12x_coil6[5];
                  H_square6[4][3] = bpm4ay_coil6[5];
                  H_square6[4][4] = bpm4ey_coil6[5];
    
  TMatrixD H_usl5(5,1);
  H_usl5[0][0] = usl_coil1[5];
  H_usl5[1][0] = usl_coil3[5];
  H_usl5[2][0] = usl_coil7[5];
  H_usl5[3][0] = usl_coil4[5];
  H_usl5[4][0] = usl_coil6[5];
  TMatrixD H_usr5(5,1);
  H_usr5[0][0] = usr_coil1[5];
  H_usr5[1][0] = usr_coil3[5];
  H_usr5[2][0] = usr_coil7[5];
  H_usr5[3][0] = usr_coil4[5];
  H_usr5[4][0] = usr_coil6[5];

  TMatrixD H_dsl5(5,1);
  H_dsl5[0][0] = dsl_coil1[5];
  H_dsl5[1][0] = dsl_coil3[5];
  H_dsl5[2][0] = dsl_coil7[5];
  H_dsl5[3][0] = dsl_coil4[5];
  H_dsl5[4][0] = dsl_coil6[5];

  TMatrixD H_dsr5(5,1);
  H_dsr5[0][0] = dsr_coil1[5];
  H_dsr5[1][0] = dsr_coil3[5];
  H_dsr5[2][0] = dsr_coil7[5];
  H_dsr5[3][0] = dsr_coil4[5];
  H_dsr5[4][0] = dsr_coil6[5];
// AT detector
  TMatrixD H_atl15(5,1);
  H_atl15[0][0] = atl1_coil1[5];
  H_atl15[1][0] = atl1_coil3[5];
  H_atl15[2][0] = atl1_coil7[5];
  H_atl15[3][0] = atl1_coil4[5];
  H_atl15[4][0] = atl1_coil6[5];

  TMatrixD H_atr15(5,1);
  H_atr15[0][0] = atr1_coil1[5];
  H_atr15[1][0] = atr1_coil3[5];
  H_atr15[2][0] = atr1_coil7[5];
  H_atr15[3][0] = atr1_coil4[5];
  H_atr15[4][0] = atr1_coil6[5];

  TMatrixD H_atl25(5,1);
  H_atl25[0][0] = atl2_coil1[5];
  H_atl25[1][0] = atl2_coil3[5];
  H_atl25[2][0] = atl2_coil7[5];
  H_atl25[3][0] = atl2_coil4[5];
  H_atl25[4][0] = atl2_coil6[5];

  TMatrixD H_atr25(5,1);
  H_atr25[0][0] = atr2_coil1[5];
  H_atr25[1][0] = atr2_coil3[5];
  H_atr25[2][0] = atr2_coil7[5];
  H_atr25[3][0] = atr2_coil4[5];
  H_atr25[4][0] = atr2_coil6[5];
    std::cout << "H_square" << std::endl;
    H_square6.Print();
    std::cout << "2. Use .Invert(&det)" << std::endl;
    Double_t det2_6;
    TMatrixD H2_6 = H_square6;
    H2_6.Invert(&det2_6);
    H2_6.Print();
    std::cout << "unity matrix" << std::endl;
    TMatrixD D6(msize,msize);
    D6.Mult(H_square6,H2_6);
    D6.Print();
  std::cout << "detector matrix for cyc 6" << std::endl;
  cout << "--usl: " <<endl;
  H_usl5.Print();
  cout << "--usr: " <<endl;
  H_usr5.Print();
  cout << "--dsl: " <<endl;
  H_dsl5.Print();
  cout << "--dsr: " <<endl;
  H_dsr5.Print();

  cout << "--atl1: " <<endl;
  H_atl15.Print();
  cout << "--atr1: " <<endl;
  H_atr25.Print();
  cout << "--atl2: " <<endl;
  H_atl25.Print();
  cout << "--atr2: " <<endl;
  H_atr25.Print();
  std::cout << "slope cyc6" << std::endl;
  TMatrixD Cusl5(msize,1);
  TMatrixD Cusr5(msize,1);
  TMatrixD Cdsl5(msize,1);
  TMatrixD Cdsr5(msize,1);
  TMatrixD Catl15(msize,1);
  TMatrixD Catr15(msize,1);
  TMatrixD Catl25(msize,1);
  TMatrixD Catr25(msize,1);

  cout << "--usl: cyc6 " <<endl;
  Cusl5.Mult(H2_6,H_usl5);
  Cusl5.Print();
 
  cout << "--usr: " <<endl;
  Cusr5.Mult(H2_6,H_usr5);
  Cusr5.Print();

  cout << "--dsl: " <<endl;
  Cdsl5.Mult(H2_6,H_dsl5);
  Cdsl5.Print();

  cout << "--dsr: " <<endl;
  Cdsr5.Mult(H2_6,H_dsr5);
  Cdsr5.Print();

  cout << "--atl1: " <<endl;
  Catl15.Mult(H2_6,H_atl15);
  Catl15.Print();
 
  cout << "--atr1: " <<endl;
  Catr15.Mult(H2_6,H_atr15);
  Catr15.Print();
 
  cout << "--atl2: " <<endl;
  Catl25.Mult(H2_6,H_atl25);
  Catl25.Print();

  cout << "--atr2: " <<endl;
  Catr25.Mult(H2_6,H_atr25);
  Catr25.Print();
//after iversing 

  TString det_array[]={"usl","usr","dsl","dsr","atl1","atr1","atl2","atr2"};
  TString bpm_array[]={"4aX","4eX","11X12X","4aY","4eY"};
  Double_t slope[8][5];
  Int_t run_number = runNo;
  Int_t slug_number = QuerySlugNumber(run_number);
  TString output_path = "../rootfiles_alldet_pass1/";
  TString slopeFilename = Form("dit_alldet_slopes_slug%d.root",slug_number);
  
  TFile* ditfile = TFile::Open(output_path+slopeFilename,"UPDATE");
  if(ditfile==NULL)
    ditfile = TFile::Open(output_path+slopeFilename,"RECREATE");
  
  TTree* dit_tree = (TTree*)ditfile->Get("dit");
  int evt;
 for(int i=0;i<cycles.size();i++){  
  if(dit_tree==NULL){
    dit_tree = new TTree("dit","dit");
     for(int idet=0;idet<8;idet++){
      for(int ibpm=0;ibpm<5;ibpm++){
	     dit_tree->Branch(det_array[idet]+"_"+bpm_array[ibpm],
			 &slope[idet][ibpm]);
        }
      }
    dit_tree->Branch("run",
		     &run_number,
		     "run/I");
    dit_tree->Branch("cyclenum",
                       &bpm4ax_cyc[i],
                       "cyclenum/D");
    dit_tree->Branch("flag",
                       &bpm4ax_flag[i],
                       "flag/I");
   } 
  else{
    for(int idet=0;idet<8;idet++){
      for(int ibpm=0;ibpm<5;ibpm++){
	dit_tree->SetBranchAddress(det_array[idet]+"_"+bpm_array[ibpm],
				   &slope[idet][ibpm]);
      }
    }
    dit_tree->SetBranchAddress("run",
			       &run_number);
    dit_tree->SetBranchAddress("cyclenum",
			       &bpm4ax_cyc[i]);
    dit_tree->SetBranchAddress("flag",
                                 &bpm4ax_flag[i]);
     }
   
  Int_t nEntries = dit_tree->GetEntries();

  //dit_tree->GetEntry(nEntries+1);
 // for(int i=0;i<cycles.size();i++){
  for(int ibpm=0;ibpm<5;ibpm++){
   if(i==0 && Cusl[ibpm][0]!=0 && Cusr[ibpm][0] !=0 && Cdsl[ibpm][0] !=0 && Cdsr[ibpm][0]!=0 && Catl1[ibpm][0]!=0&& Catl2[ibpm][0]!=0 && Catr1[ibpm][0]!=0 && Catr2[ibpm][0]!=0 ){ 
    slope[0][ibpm] = Cusl[ibpm][0];
    slope[1][ibpm] = Cusr[ibpm][0];
    slope[2][ibpm] = Cdsl[ibpm][0];
    slope[3][ibpm] = Cdsr[ibpm][0];
    slope[4][ibpm] = Catl1[ibpm][0];
    slope[5][ibpm] = Catr1[ibpm][0];
    slope[6][ibpm] = Catl2[ibpm][0];
    slope[7][ibpm] = Catr2[ibpm][0];
   // cout <<"slope="<<slope[1][ibpm]<<"bpm4ax_cyc="<<bpm4ax_cyc[i]<<"slope="<<slope[0][ibpm] <<endl; 
   }  
   if(i==1&&Cusl1[ibpm][0]!=0 && Cusr1[ibpm][0] !=0 && Cdsl1[ibpm][0] !=0 && Cdsr1[ibpm][0]!=0 && Catl11[ibpm][0]!=0&& Catl21[ibpm][0]!=0 && Catr11[ibpm][0]!=0 && Catr21[ibpm][0]!=0 ){ 
    slope[0][ibpm] = Cusl1[ibpm][0];
    slope[1][ibpm] = Cusr1[ibpm][0];
    slope[2][ibpm] = Cdsl1[ibpm][0];
    slope[3][ibpm] = Cdsr1[ibpm][0];
    slope[4][ibpm] = Catl11[ibpm][0];
    slope[5][ibpm] = Catr11[ibpm][0];
    slope[6][ibpm] = Catl21[ibpm][0];
    slope[7][ibpm] = Catr21[ibpm][0];
   //cout<<"slope="<<slope[1][ibpm]<<"bpm4ax_cyc="<<bpm4ax_cyc[i]<<"slope="<<slope[0][ibpm] <<endl;
   }
    if( i==2 && Cusl2[ibpm][0]!=0 && Cusr2[ibpm][0] !=0 && Cdsl2[ibpm][0] !=0 && Cdsr2[ibpm][0]!=0 && Catl12[ibpm][0]!=0&& Catl22[ibpm][0]!=0 && Catr12[ibpm][0]!=0 && Catr22[ibpm][0]!=0 ){ 
    slope[0][ibpm] = Cusl2[ibpm][0];
    slope[1][ibpm] = Cusr2[ibpm][0];
    slope[2][ibpm] = Cdsl2[ibpm][0];
    slope[3][ibpm] = Cdsr2[ibpm][0];
    slope[4][ibpm] = Catl12[ibpm][0];
    slope[5][ibpm] = Catr12[ibpm][0];
    slope[6][ibpm] = Catl22[ibpm][0];
    slope[7][ibpm] = Catr22[ibpm][0];
   // cout<<"slope="<<slope[1][ibpm]<<"bpm4ax_cyc="<<bpm4ax_cyc[i]<<"slope="<<slope[0][ibpm] <<endl;
  }
   if(i==3  && Cusl3[ibpm][0]!=0 && Cusr3[ibpm][0] !=0 && Cdsl3[ibpm][0] !=0 && Cdsr3[ibpm][0]!=0 && Catl13[ibpm][0]!=0&& Catl23[ibpm][0]!=0 && Catr13[ibpm][0]!=0 && Catr23[ibpm][0]!=0 ){ 
    slope[0][ibpm] = Cusl3[ibpm][0];
    slope[1][ibpm] = Cusr3[ibpm][0];
    slope[2][ibpm] = Cdsl3[ibpm][0];
    slope[3][ibpm] = Cdsr3[ibpm][0];
    slope[4][ibpm] = Catl13[ibpm][0];
    slope[5][ibpm] = Catr13[ibpm][0];
    slope[6][ibpm] = Catl23[ibpm][0];
    slope[7][ibpm] = Catr23[ibpm][0];
   }
   if(i==4 && Cusl4[ibpm][0]!=0 && Cusr4[ibpm][0] !=0 && Cdsl4[ibpm][0] !=0 && Cdsr4[ibpm][0]!=0 && Catl14[ibpm][0]!=0&& Catl24[ibpm][0]!=0 && Catr14[ibpm][0]!=0 && Catr24[ibpm][0]!=0 ){ 
    slope[0][ibpm] = Cusl4[ibpm][0];
    slope[1][ibpm] = Cusr4[ibpm][0];
    slope[2][ibpm] = Cdsl4[ibpm][0];
    slope[3][ibpm] = Cdsr4[ibpm][0];
    slope[4][ibpm] = Catl14[ibpm][0];
    slope[5][ibpm] = Catr14[ibpm][0];
    slope[6][ibpm] = Catl24[ibpm][0];
    slope[7][ibpm] = Catr24[ibpm][0];
   }
    if(i==5 && Cusl5[ibpm][0]!=0 && Cusr5[ibpm][0] !=0 && Cdsl5[ibpm][0] !=0 && Cdsr5[ibpm][0]!=0 && Catl15[ibpm][0]!=0&& Catl25[ibpm][0]!=0 && Catr15[ibpm][0]!=0 && Catr25[ibpm][0]!=0 ){ 
    slope[0][ibpm] = Cusl5[ibpm][0];
    slope[1][ibpm] = Cusr5[ibpm][0];
    slope[2][ibpm] = Cdsl5[ibpm][0];
    slope[3][ibpm] = Cdsr5[ibpm][0];
    slope[4][ibpm] = Catl15[ibpm][0];
    slope[5][ibpm] = Catr15[ibpm][0];
    slope[6][ibpm] = Catl25[ibpm][0];
    slope[7][ibpm] = Catr25[ibpm][0];

   }
   //cout<<"slope="<< slope[0][ibpm]<<"  "<<slope[1][ibpm]<<"  "<<slope[2][ibpm]<<"  "<<slope[3][ibpm]<<"  "<< slope[4][ibpm]<<"  "<<slope[5][ibpm] <<"  "<<slope[6][ibpm]<<"  " << slope[7][ibpm]<<" flag="<< bpm4ax_flag[i]<<endl;
  }
 if(bpm4ax_cyc[i]>1){
  //cout<<"cyc="<<cycles[i]<<" flag="<<bpm4ax_flag[i]<<endl;
  dit_tree->Fill();
  }
 }
if(dit_tree->GetEntries()==1)
    dit_tree->Write();
  else
    dit_tree->Write(0,TObject::kOverwrite);
  
  ditfile->Close();
 
}

