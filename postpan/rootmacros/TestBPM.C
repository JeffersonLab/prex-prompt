#include "device_list.h"
#include "PlotInjBPMS.C"
#include "PlotInjBPMSAq.C"
#include "PlotInjBPMSDr.C"
#include "PlotInjBPMSAelli.C"

void TestBPM(Int_t run_num){

  run_number = run_num;
  path = "../japanOutput/";
  prefix = "prexRespin1";
  file_name = Form("%s_%d.root",prefix.Data(),run_number);
  TFile* rootfile = TFile::Open(path+file_name);
  output_path = "./";
  
  PlotInjBPMS();  
  PlotInjBPMSAq();
  PlotInjBPMSDr();
  PlotInjBPMSAelli();
}

