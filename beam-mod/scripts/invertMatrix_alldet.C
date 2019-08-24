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

  const int n=30;
  const int m=24;
  const int t=6;
  string bpm_name[n];
  string detector_name[m];
  string atdet_name[m];

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

  double atdet_cyc[m], atdet_coil1[m],atdet_coil1_error[m],atdetEntry_coil1[m], atdet_coil2[m],atdet_coil2_error[m],atdetEntry_coil2[m], atdet_coil3[m],atdet_coil3_error[m],atdetEntry_coil3[m],atdet_coil4[m],atdet_coil4_error[m],atdetEntry_coil4[m],atdet_coil5[m],atdet_coil5_error[m],atdetEntry_coil5[m],atdet_coil6[m],atdet_coil6_error[m],atdetEntry_coil6[m],atdet_coil7[m],atdet_coil7_error[m],atdetEntry_coil7[m];

  double atl1_cyc[t],atl1_name[t], atl1_coil1[t],atl1_coil1_error[t],atl1Entry_coil1[t], atl1_coil2[t],atl1_coil2_error[t],atl1Entry_coil2[t], atl1_coil3[t],atl1_coil3_error[t],atl1Entry_coil3[t],atl1_coil4[t],atl1_coil4_error[t],atl1Entry_coil4[t],atl1_coil5[t],atl1_coil5_error[t],atl1Entry_coil5[t],atl1_coil6[t],atl1_coil6_error[t],atl1Entry_coil6[t],atl1_coil7[t],atl1_coil7_error[t],atl1Entry_coil7[t];

  double atl2_cyc[t],atl2_name[t],atl2_coil1[t],atl2_coil1_error[t],atl2Entry_coil1[t], atl2_coil2[t],atl2_coil2_error[t],atl2Entry_coil2[t], atl2_coil3[t],atl2_coil3_error[t],atl2Entry_coil3[t],atl2_coil4[t],atl2_coil4_error[t],atl2Entry_coil4[t],atl2_coil5[t],atl2_coil5_error[t],atl2Entry_coil5[t],atl2_coil6[t],atl2_coil6_error[t],atl2Entry_coil6[t],atl2_coil7[t],atl2_coil7_error[t],atl2Entry_coil7[t];

  double atr1_cyc[t],atr1_name[t],atr1_coil1[t],atr1_coil1_error[t],atr1Entry_coil1[t], atr1_coil2[t],atr1_coil2_error[t],atr1Entry_coil2[t], atr1_coil3[t],atr1_coil3_error[t],atr1Entry_coil3[t],atr1_coil4[t],atr1_coil4_error[t],atr1Entry_coil4[t],atr1_coil5[t],atr1_coil5_error[t],atr1Entry_coil5[t],atr1_coil6[t],atr1_coil6_error[t],atr1Entry_coil6[t],atr1_coil7[t],atr1_coil7_error[t],atr1Entry_coil7[t];

  double atr2_cyc[t],atr2_name[t],atr2_coil1[t],atr2_coil1_error[t],atr2Entry_coil1[t], atr2_coil2[t],atr2_coil2_error[t],atr2Entry_coil2[t], atr2_coil3[t],atr2_coil3_error[t],atr2Entry_coil3[t],atr2_coil4[t],atr2_coil4_error[t],atr2Entry_coil4[t],atr2_coil5[t],atr2_coil5_error[t],atr2Entry_coil5[t],atr2_coil6[t],atr2_coil6_error[t],atr2Entry_coil6[t],atr2_coil7[t],atr2_coil7_error[t],atr2Entry_coil7[t];

  for(int i=0;i<n;i++){
    infile>>bpm_cyc[i]>>bpm_name[i]>>bpm_coil1[i]>>bpm_coil1_error[i]>>bpmEntry_coil1[i]>>bpm_coil2[i]>>bpm_coil2_error[i]>>bpmEntry_coil2[i]>>bpm_coil3[i]>>bpm_coil3_error[i]>>bpmEntry_coil3[i]>>bpm_coil4[i]>>bpm_coil4_error[i]>>bpmEntry_coil4[i]>>bpm_coil5[i]>>bpm_coil5_error[i]>>bpmEntry_coil5[i]>>bpm_coil6[i]>>bpm_coil6_error[i]>>bpmEntry_coil6[i]>>bpm_coil7[i]>>bpm_coil7_error[i]>>bpmEntry_coil7[i];

  }

  for(int i=0;i<m;i++){
    infile1>>detector_cyc[i]>>detector_name[i]>>detector_coil1[i]>>detector_coil1_error[i]>>detectorEntry_coil1[i]>>detector_coil2[i]>>detector_coil2_error[i]>>detectorEntry_coil2[i]>>detector_coil3[i]>>detector_coil3_error[i]>>detectorEntry_coil3[i]>>detector_coil4[i]>>detector_coil4_error[i]>>detectorEntry_coil4[i]>>detector_coil5[i]>>detector_coil5_error[i]>>detectorEntry_coil5[i]>>detector_coil6[i]>>detector_coil6_error[i]>>detectorEntry_coil6[i]>>detector_coil7[i]>>detector_coil7_error[i]>>detectorEntry_coil7[i];
  }
  for(int i=0;i<m;i++){
    infile2>>atdet_cyc[i]>>atdet_name[i]>>atdet_coil1[i]>>atdet_coil1_error[i]>>atdetEntry_coil1[i]>>atdet_coil2[i]>>atdet_coil2_error[i]>>atdetEntry_coil2[i]>>atdet_coil3[i]>>atdet_coil3_error[i]>>atdetEntry_coil3[i]>>atdet_coil4[i]>>atdet_coil4_error[i]>>atdetEntry_coil4[i]>>atdet_coil5[i]>>atdet_coil5_error[i]>>atdetEntry_coil5[i]>>atdet_coil6[i]>>atdet_coil6_error[i]>>atdetEntry_coil6[i]>>atdet_coil7[i]>>atdet_coil7_error[i]>>atdetEntry_coil7[i];
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
    bpm4ax_cyc[j]=bpm_cyc[j*5];
    bpm4ax_cyc[j]=bpm_cyc[j*5];
    bpm4ax_cyc[j]=bpm_cyc[j*5];
    bpm4ax_cyc[j]=bpm_cyc[j*5];
    bpm4ax_cyc[j]=bpm_cyc[j*5];
    bpm4ax_cyc[j]=bpm_cyc[j*5];



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


  }

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

  TString det_array[]={"usl","usr","dsl","dsr","atl1","atr1","atl2","atr2"};
  TString bpm_array[]={"4aX","4eX","11X","4aY","4eY"};
  Double_t slope[8][5];
  Int_t run_number = runNo;
  Int_t slug_number = QuerySlugNumber(run_number);
  TString output_path = "~/PREX/prompt/beam-mod/rootfiles_alldet_11X12X/";
  TString slopeFilename = Form("dit_alldet_slopes_slug%d.root",slug_number);
  
  TFile* ditfile = TFile::Open(output_path+slopeFilename,"UPDATE");
  if(ditfile==NULL)
    ditfile = TFile::Open(output_path+slopeFilename,"RECREATE");
  
  TTree* dit_tree = (TTree*)ditfile->Get("dit");
  int evt;
  if(dit_tree==NULL){
    dit_tree = new TTree("dit","dit");
    for(int idet=0;idet<8;idet++)
      for(int ibpm=0;ibpm<5;ibpm++)
	dit_tree->Branch(det_array[idet]+"_"+bpm_array[ibpm],
			 &slope[idet][ibpm]);

    dit_tree->Branch("run",
		     &run_number,
		     "run/I");
    
  }
  else{
    for(int idet=0;idet<8;idet++)
      for(int ibpm=0;ibpm<5;ibpm++)
	dit_tree->SetBranchAddress(det_array[idet]+"_"+bpm_array[ibpm],
				   &slope[idet][ibpm]);

    dit_tree->SetBranchAddress("run",
			       &run_number);

  }


  Int_t nEntries = dit_tree->GetEntries();

  dit_tree->GetEntry(nEntries+1);
  
  for(int ibpm=0;ibpm<5;ibpm++){
    slope[0][ibpm] = Cusl[ibpm][0];
    slope[1][ibpm] = Cusr[ibpm][0];
    slope[2][ibpm] = Cdsl[ibpm][0];
    slope[3][ibpm] = Cdsr[ibpm][0];
    slope[4][ibpm] = Catl1[ibpm][0];
    slope[5][ibpm] = Catr1[ibpm][0];
    slope[6][ibpm] = Catl2[ibpm][0];
    slope[7][ibpm] = Catr2[ibpm][0];
  }
  
  dit_tree->Fill();
  
  if(dit_tree->GetEntries()==1)
    dit_tree->Write();
  else
    dit_tree->Write(0,TObject::kOverwrite);
  
  ditfile->Close();

}

