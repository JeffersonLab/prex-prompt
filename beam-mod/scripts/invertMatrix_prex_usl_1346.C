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
 void invertMatrix_prex_usl_1346(int runNo=0){
     Int_t msize=5;
     char inputfile1[300];
     sprintf(inputfile1,"./BPMs_sensitivity_run%d.txt",runNo);

     char inputfile2[300];
     sprintf(inputfile2,"./Quartz_sensitivity_run%d.txt",runNo);
    // ifstream infile("./BPMs_sensitivity_run3322.txt");	 
   //  ifstream infile1("./Quartz_sensitivity_run3322.txt");	 
    ifstream infile(inputfile1);	 
    ifstream infile1(inputfile2);	 
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
  sstr0<<"usl_dithering_slope_run"<<runNo<<".txt";
  ofstream outfile0(sstr0.str().c_str());
  sstr0.str("");

const int n=30;
const int m=24;
const int t=6;
string bpm_name[n];
string detector_name[m];

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


for(int i=0;i<n;i++){
infile>>bpm_cyc[i]>>bpm_name[i]>>bpm_coil1[i]>>bpm_coil1_error[i]>>bpmEntry_coil1[i]>>bpm_coil2[i]>>bpm_coil2_error[i]>>bpmEntry_coil2[i]>>bpm_coil3[i]>>bpm_coil3_error[i]>>bpmEntry_coil3[i]>>bpm_coil4[i]>>bpm_coil4_error[i]>>bpmEntry_coil4[i]>>bpm_coil5[i]>>bpm_coil5_error[i]>>bpmEntry_coil5[i]>>bpm_coil6[i]>>bpm_coil6_error[i]>>bpmEntry_coil6[i]>>bpm_coil7[i]>>bpm_coil7_error[i]>>bpmEntry_coil7[i];

}

for(int i=0;i<m;i++){
infile1>>detector_cyc[i]>>detector_name[i]>>detector_coil1[i]>>detector_coil1_error[i]>>detectorEntry_coil1[i]>>detector_coil2[i]>>detector_coil2_error[i]>>detectorEntry_coil2[i]>>detector_coil3[i]>>detector_coil3_error[i]>>detectorEntry_coil3[i]>>detector_coil4[i]>>detector_coil4_error[i]>>detectorEntry_coil4[i]>>detector_coil5[i]>>detector_coil5_error[i]>>detectorEntry_coil5[i]>>detector_coil6[i]>>detector_coil6_error[i]>>detectorEntry_coil6[i]>>detector_coil7[i]>>detector_coil7_error[i]>>detectorEntry_coil7[i];
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
    
                  TMatrixD H_no(5,1);
		  H_no[0][0] = usl_coil1[0];
		  H_no[1][0] = usl_coil3[0];
		  H_no[2][0] = usl_coil7[0];
		  H_no[3][0] = usl_coil4[0];
		  H_no[4][0] = usl_coil6[0];
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
    H_no.Print();

    std::cout << "slope" << std::endl;
    TMatrixD C(msize,1);
    C.Mult(H2,H_no);
    C.Print();

    std::cout << "Cyc 2" << std::endl;
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
    
                  TMatrixD H_no2(5,1);
		  H_no2[0][0] = usl_coil1[1];
		  H_no2[1][0] = usl_coil3[1];
		  H_no2[2][0] = usl_coil7[1];
		  H_no2[3][0] = usl_coil4[1];
		  H_no2[4][0] = usl_coil6[1];
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
   std::cout << "detector matrix" << std::endl;
    H_no2.Print();

    std::cout << "slope" << std::endl;
    TMatrixD C2(msize,1);
    C2.Mult(H2_2,H_no2);
    C2.Print();
std::cout << "Cyc 3" << std::endl;
//cyc3
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
    
                  TMatrixD H_no3(5,1);
		  H_no3[0][0] = usl_coil1[2];
		  H_no3[1][0] = usl_coil3[2];
		  H_no3[2][0] = usl_coil7[2];
		  H_no3[3][0] = usl_coil4[2];
		  H_no3[4][0] = usl_coil6[2];
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
   std::cout << "detector matrix" << std::endl;
    H_no3.Print();

    std::cout << "slope" << std::endl;
    TMatrixD C3(msize,1);
    C3.Mult(H2_3,H_no3);
    C3.Print();
std::cout << "Cyc 4" << std::endl;
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
    
                  TMatrixD H_no4(5,1);
		  H_no4[0][0] = usl_coil1[3];
		  H_no4[1][0] = usl_coil3[3];
		  H_no4[2][0] = usl_coil7[3];
		  H_no4[3][0] = usl_coil4[3];
		  H_no4[4][0] = usl_coil6[3];
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
   std::cout << "detector matrix" << std::endl;
    H_no4.Print();

    std::cout << "slope" << std::endl;
    TMatrixD C4(msize,1);
    C4.Mult(H2_4,H_no4);
    C4.Print();
std::cout << "Cyc 5" << std::endl;
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
    
                  TMatrixD H_no5(5,1);
		  H_no5[0][0] = usl_coil1[4];
		  H_no5[1][0] = usl_coil3[4];
		  H_no5[2][0] = usl_coil7[4];
		  H_no5[3][0] = usl_coil4[4];
		  H_no5[4][0] = usl_coil6[4];
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
   std::cout << "detector matrix" << std::endl;
    H_no5.Print();

    std::cout << "slope" << std::endl;
    TMatrixD C5(msize,1);
    C5.Mult(H2_5,H_no5);
    C5.Print();
std::cout << "Cyc 6" << std::endl;
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
    
                  TMatrixD H_no6(5,1);
		  H_no6[0][0] = usl_coil1[5];
		  H_no6[1][0] = usl_coil3[5];
		  H_no6[2][0] = usl_coil7[5];
		  H_no6[3][0] = usl_coil4[5];
		  H_no6[4][0] = usl_coil6[5];
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
   std::cout << "detector matrix" << std::endl;
    H_no6.Print();

    std::cout << "slope" << std::endl;
    TMatrixD C6(msize,1);
    C6.Mult(H2_6,H_no6);
    C6.Print();
    outfile0<<setw(20)<<setiosflags(ios::left)<<"cyc_number"<<setw(20)<<setiosflags(ios::left)<<"usl:4ax="<<setw(20)<<setiosflags(ios::left)<<"usl:4ex="<<setw(20)<<setiosflags(ios::left)<<"usl:12x="<<setw(20)<<setiosflags(ios::left)<<"usl:4ay="<<setw(20)<<setiosflags(ios::left)<<"usl:4ey="<<endl;

    if(C[0][0]!=0 && C[1][0] !=0 && C[2][0] !=0 && C[3][0]!=0 && C[4][0]!=0 ){
    outfile0<<setw(20)<<setiosflags(ios::left)<<bpm4ax_cyc[0]<<setw(20)<<setiosflags(ios::left)<<C[0][0]<<setw(20)<<setiosflags(ios::left)<<C[1][0]<<setw(20)<<setiosflags(ios::left)<<C[2][0]<<setw(20)<<setiosflags(ios::left)<<C[3][0]<<setw(20)<<setiosflags(ios::left)<<C[4][0]<<endl;
    }
    if(C2[0][0]!=0 && C2[1][0] !=0 && C2[2][0] !=0 && C2[3][0]!=0 && C2[4][0]!=0 ){
    outfile0<<setw(20)<<setiosflags(ios::left)<<bpm4ax_cyc[1]<<setw(20)<<setiosflags(ios::left)<<C2[0][0]<<setw(20)<<setiosflags(ios::left)<<C2[1][0]<<setw(20)<<setiosflags(ios::left)<<C2[2][0]<<setw(20)<<setiosflags(ios::left)<<C2[3][0]<<setw(20)<<setiosflags(ios::left)<<C2[4][0]<<endl;
  }
    if(C3[0][0]!=0 && C3[1][0] !=0 && C3[2][0] !=0 && C3[3][0]!=0 && C3[4][0]!=0 ){
    outfile0<<setw(20)<<setiosflags(ios::left)<<bpm4ax_cyc[2]<<setw(20)<<setiosflags(ios::left)<<C3[0][0]<<setw(20)<<setiosflags(ios::left)<<C3[1][0]<<setw(20)<<setiosflags(ios::left)<<C3[2][0]<<setw(20)<<setiosflags(ios::left)<<C3[3][0]<<setw(20)<<setiosflags(ios::left)<<C3[4][0]<<endl;
}
    if(C4[0][0]!=0 && C4[1][0] !=0 && C4[2][0] !=0 && C4[3][0]!=0 && C4[4][0]!=0 ){
    outfile0<<setw(20)<<setiosflags(ios::left)<<bpm4ax_cyc[3]<<setw(20)<<setiosflags(ios::left)<<C4[0][0]<<setw(20)<<setiosflags(ios::left)<<C4[1][0]<<setw(20)<<setiosflags(ios::left)<<C4[2][0]<<setw(20)<<setiosflags(ios::left)<<C4[3][0]<<setw(20)<<setiosflags(ios::left)<<C4[4][0]<<endl;
}
    if(C5[0][0]!=0 && C5[1][0] !=0 && C5[2][0] !=0 && C5[3][0]!=0 && C5[4][0]!=0 ){
    outfile0<<setw(20)<<setiosflags(ios::left)<<bpm4ax_cyc[4]<<setw(20)<<setiosflags(ios::left)<<C5[0][0]<<setw(20)<<setiosflags(ios::left)<<C5[1][0]<<setw(20)<<setiosflags(ios::left)<<C5[2][0]<<setw(20)<<setiosflags(ios::left)<<C5[3][0]<<setw(20)<<setiosflags(ios::left)<<C5[4][0]<<endl;
}
    if(C6[0][0]!=0 && C6[1][0] !=0 && C6[2][0] !=0 && C6[3][0]!=0 && C6[4][0]!=0 ){
    outfile0<<setw(20)<<setiosflags(ios::left)<<bpm4ax_cyc[5]<<setw(20)<<setiosflags(ios::left)<<C6[0][0]<<setw(20)<<setiosflags(ios::left)<<C6[1][0]<<setw(20)<<setiosflags(ios::left)<<C6[2][0]<<setw(20)<<setiosflags(ios::left)<<C6[3][0]<<setw(20)<<setiosflags(ios::left)<<C6[4][0]<<endl;
}
   cout<<"cyc="<<1<<"  "<<"usl:4ax="<<C[0][0]<<"  "<<"usl:4ex="<<C[1][0]<<"  "<<"usl:12x="<<C[2][0]<<"  "<<"usl:4ay="<<C[3][0]<<"  "<<"usl:4ey="<<C[4][0]<<endl;
   cout<<"cyc="<<2<<"  "<<"usl:4ax="<<C2[0][0]<<"  "<<"usl:4ex="<<C2[1][0]<<"  "<<"usl:12x="<<C2[2][0]<<"  "<<"usl:4ay="<<C2[3][0]<<"  "<<"usl:4ey="<<C2[4][0]<<endl;
   cout<<"cyc="<<3<<"  "<<"usl:4ax="<<C3[0][0]<<"  "<<"usl:4ex="<<C3[1][0]<<"  "<<"usl:12x="<<C3[2][0]<<"  "<<"usl:4ay="<<C3[3][0]<<"  "<<"usl:4ey="<<C3[4][0]<<endl;
   cout<<"cyc="<<4<<"  "<<"usl:4ax="<<C4[0][0]<<"  "<<"usl:4ex="<<C4[1][0]<<"  "<<"usl:12x="<<C4[2][0]<<"  "<<"usl:4ay="<<C4[3][0]<<"  "<<"usl:4ey="<<C4[4][0]<<endl;
   cout<<"cyc="<<5<<"  "<<"usl:4ax="<<C5[0][0]<<"  "<<"usl:4ex="<<C5[1][0]<<"  "<<"usl:12x="<<C5[2][0]<<"  "<<"usl:4ay="<<C5[3][0]<<"  "<<"usl:4ey="<<C5[4][0]<<endl;
   cout<<"cyc="<<6<<"  "<<"usl:4ax="<<C6[0][0]<<"  "<<"usl:4ex="<<C6[1][0]<<"  "<<"usl:12x="<<C6[2][0]<<"  "<<"usl:4ay="<<C6[3][0]<<"  "<<"usl:4ey="<<C6[4][0]<<endl;




    /* TMatrixD H2by2(2,2);
     H2by2[0][0] = BPMS_coil3[0];
     H2by2[0][0] = BPMS_coil3[1];
     H2by2[1][0] = BPMS_coil3[0];
     H2by2[1][1] = BPMS_coil3[1];
    double alphv = 1-(BPMS_coil3[1]*BPMS_coil3[0])/(BPMS_coil3[0]*BPMS_coil3[1]);
     cout<<"alph="<<alphv<<endl;
     TMatrixD H2by2(3,3);
     H2by2[0][0] = BPMS_coil3[4];
     H2by2[0][1] = BPMS_coil3[0];
     H2by2[0][2] = BPMS_coil3[1];
     H2by2[1][0] = BPMS_coil3[4];
     H2by2[1][1] = BPMS_coil3[0];
     H2by2[1][2] = BPMS_coil3[1];
     H2by2[2][0] = BPMS_coil8[4];
     H2by2[2][1] = BPMS_coil8[0];
     H2by2[2][2] = BPMS_coil8[1];
    double deltav=BPMS_coil3[4]/BPMS_coil3[0]-BPMS_coil3[4]/BPMS_coil3[0];
    double ratio = deltav/alphv;
    cout<<"delta="<<deltav<<"ratio="<<ratio<<endl;*/
    
 }

