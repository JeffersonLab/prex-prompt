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

#include "CheckRegNormDetector.C"
#include "CheckRegressedDetector.C"

#include "CheckSAMCorrelation.C"
#include "CheckRegression.C"
#include "RegressionSummary.C"
#include "CheckPairSAM.C"

#include "CheckNormalizedComboSAM.C"
#include "CheckComboSAM.C"

#include "PlotErrorCounters.C"
#include "Integrated.C"
#include "PlotPairTree.C"
#include "CheckWireSum.C"
void fastPlotSummary(TString filename){

  Bool_t isNormalized=kTRUE;

  japanOutput = TFile::Open(filename);
  Ssiz_t pfirst = filename.Last('_')+1;
  Ssiz_t plast = filename.Last('.')-1;
  Ssiz_t plength = plast-pfirst+1;
  run_seg = filename(pfirst,plength);
  run_seg = run_seg.ReplaceAll('.','_');
  output_path = Form("./FastPlots/run%s/",run_seg.Data());

  //===== BCM  Plots =====
  CheckBCM();
  gSystem->Exec(Form("convert $(ls -rt %s*bcm*.png) %srun%s_summary_bcm.pdf",
  		     output_path.Data(),
		     output_path.Data(),
  		     run_seg.Data()));

  gSystem->Exec(Form("rm %s*bcm*.png",output_path.Data()));

  //===== BPM Plots =======
  CheckBPM();
  gsystem->Exec(Form("convert $(ls -rt %s*bpm*.png ) %srun%s_summary_bpm.pdf",
  		     output_path.Data(),
		     output_path.Data(),
  		     run_seg.Data()));
  gSystem->Exec(Form("rm %s*bpm*.png",output_path.Data()));

  //===== Main Detector Plots =======
  if(isNormalized)
    CheckNormalizedDetector();
  else
    CheckDetector();
  gSystem->Exec(Form("rm %s*maindet*.png %s*[ud]s[lr]*.png",
		     output_path.Data(),
		     output_path.Data()));
}

