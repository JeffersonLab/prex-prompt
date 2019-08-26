//////////////////////////////////////////////////////////////////////
//
// PlotSummary.C (Testing script)
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
#include "CheckSAM.C"
#include "CheckSAMCorrelation.C"
#include "CheckRegression.C"
//#include "CheckPairSAM.C"
#include "CheckComboSAM.C"
#include "PlotErrorCounters.C"
#include "Integrated.C"
#include "CheckRegressedDetector.C"
#include "CheckRegNormDetector.C"
#include "RegressionSummary.C"
#include "PlotPairTree.C"
#include "CheckWireSum.C"
void Test(TString filename){
  japanOutput = TFile::Open(filename);
  Ssiz_t pfirst = filename.Last('_')+1;
  Ssiz_t plast = filename.Last('.')-1;
  Ssiz_t plength = plast-pfirst+1;
  run_seg = filename(pfirst,plength);
  run_seg = run_seg.ReplaceAll('.','_');
  output_path = "./";

  // ===Check mulc_lrb before making plots
  // CheckComboSAM();
  // CheckBPM();
  // CheckRegNormDetector();
//  PlotPairTree(vBPMXY);
  CheckWireSum();
}

