//////////////////////////////////////////////////////////////////////
//
// PlotSummary_postpan.C ( script)
//   Devi Adhikari
//	- May 2019
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
#include "CheckSAM.C"
#include "CheckSAMCorrelation.C"
#include "CheckRegression_postpan.C"
//#include "CheckPairSAM.C"
#include "CheckComboSAM_postpan.C"
#include "PlotErrorCounters.C"
#include "Integrated.C"
#include "CheckRegressedDetector_postpan.C"
#include "CheckRegNormDetector_postpan.C"
#include "RegressionSummary.C"
#include "PlotPairTree.C"
#include "CheckNormalizedComboSAM_postpan.C"
#include "CheckRegNormATDetector_postpan.C"

void PlotSummary_postpan(TString filename){
  results = TFile::Open(filename);
  Ssiz_t pfirst = filename.Last('_')-16;
  Ssiz_t plast = filename.Last('.')-17;
  Ssiz_t plength = plast-pfirst+1;
  run_seg = filename(pfirst,plength);
  run_seg = run_seg.ReplaceAll('.','_');
  output_path = Form("./tmp/run%s/",run_seg.Data());

  
  // ===Check mulc_lrb before making plots
  // CheckComboSAM_postpan();
  // CheckBPM();
  // CheckRegNormDetector_postpan();
  //  PlotPairTree(CheckRegression_postpan);
  TTree *red_tree = (TTree*)gROOT->FindObject("reg");
  if (red_tree==NULL){
    std::cout << "WARNING:  The ReD tree was not found for file "
	      << filename << "!" << std::endl;
    return;
  }
  
  if (red_tree->GetEntries("ok_cut")==0){
    std::cout << "WARNING:  The ReD tree has no good events in file "
	      << filename << "!" << std::endl;
  }
  else{
    CheckRegression_postpan();
    CheckNormalizedComboSAM_postpan(); 
    CheckRegNormATDetector_postpan();
    CheckRegNormDetector_postpan();
  }
  //CheckRegressedDetector_postpan();
}

