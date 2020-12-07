//////////////////////////////////////////////////////////////////////
//
// PlotSummary.C
//   Tao Ye - May 2019
//
//////////////////////////////////////////////////////////////////////

#include "device_list.h"

#include "PlotCorrelation.C"

#include "PlotInjBPMS.C"
#include "PlotInjBPMSAq.C"
#include "PlotInjBPMSDr.C"
#include "PlotInjBPMSAelli.C"

#include "CheckBCM.C"
#include "CheckBCMdd.C"
#include "CheckBPM.C"
#include "PlotBPMDiffCorrelation.C"

#include "CheckNormalizedSAM.C"
#include "CheckSAM.C"

#include "CheckDetector.C"
#include "CheckNormalizedDetector.C"
#include "CheckDetectorCorrelation.C"

#include "CheckAT.C"
#include "CheckNormalizedAT.C"
#include "CheckATCorrelation.C"

#include "CheckRegNormDetector.C"
#include "CheckRegressedDetector.C"

#include "CheckSAMCorrelation.C"
#include "CheckRegression.C"
#include "RegressionSummary.C"
#include "CheckPairSAM.C"

#include "CheckNormalizedComboSAM.C"
#include "CheckComboSAM.C"
#include "CheckSuperCycle.C"
#include "PlotErrorCounters.C"
#include "Integrated.C"
#include "PlotPairTree.C"
#include "CheckWireSum.C"
void Err(TString filename,TString output_dir="./tmp"){

  Bool_t isNormalized=kTRUE;

  japanOutput = TFile::Open(filename);
  Ssiz_t pfirst = filename.Last('_')+1;
  Ssiz_t plast = filename.Last('.')-1;
  Ssiz_t plength = plast-pfirst+1;
  run_seg = filename(pfirst,plength);
  run_seg = run_seg.ReplaceAll('.','_');
  if(output_dir=="")
    output_dir="./tmp/";
  output_path = output_dir + Form("/run%s/",run_seg.Data());
  cout << " -- output_path " << output_path << endl;
  //  Make sure we have the trees before proceeding.
  TTree *evt_tree = (TTree*)gROOT->FindObject("evt");
  if (evt_tree==NULL){
    std::cout << "WARNING:  The event tree was not found for file "
	      << filename << "!" << std::endl;
    return;
  }
  TTree *mul_tree = (TTree*)gROOT->FindObject("mul");
  if (mul_tree==NULL){
    std::cout << "WARNING:  The multiplet tree was not found for file "
	      << filename << "!" << std::endl;
    return;
  }

  TTree *pair_tree = (TTree*)gROOT->FindObject("pr");
  if (pair_tree==NULL){
    std::cout << "WARNING:  The pair tree was not found for file "
	      << filename << "!" << std::endl;
    return;
  }

  //===== Error Counter from Evt Tree =====   
  PlotErrorCounters();

}

