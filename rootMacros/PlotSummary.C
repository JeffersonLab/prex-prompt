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
void PlotSummary(TString filename){

  Bool_t isNormalized=kTRUE;

  japanOutput = TFile::Open(filename);
  Ssiz_t pfirst = filename.Last('_')+1;
  Ssiz_t plast = filename.Last('.')-1;
  Ssiz_t plength = plast-pfirst+1;
  run_seg = filename(pfirst,plength);
  run_seg = run_seg.ReplaceAll('.','_');
  output_path = Form("./tmp/run%s/",run_seg.Data());

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

  if (evt_tree->GetEntries("ErrorFlag==0")==0){
    std::cout << "WARNING:  The event tree has no good events in file "
	      << filename << "!" << std::endl;
    // Make plots from BCM without ErrorFlag cuts
    PlotErrorCounters();
    CheckBCM();
    gSystem->Exec(Form("convert $(ls -rt %s*bcm*.png) %srun%s_summary_bcm.pdf",
		       output_path.Data(),
		       output_path.Data(),
		       run_seg.Data()));

    gSystem->Exec(Form("rm %s*bcm*.png",output_path.Data()));

    return;
  }
  if (mul_tree->GetEntries("ErrorFlag==0")==0){
    std::cout << "WARNING:  The multiplet tree has no good events in file "
	      << filename << "!" << std::endl;
    // Make plots from BCM without ErrorFlag cuts
    CheckBCM();
    gSystem->Exec(Form("convert $(ls -rt %s*bcm*.png) %srun%s_summary_bcm.pdf",
		       output_path.Data(),
		       output_path.Data(),
		       run_seg.Data()));

    gSystem->Exec(Form("rm %s*bcm*.png",output_path.Data()));

    return;
  }
  
  //===== BCM  Plots =====
  CheckBCM();
  CheckBCMdd("mul");
  PlotPairTree(vBCM);
  CheckBCMdd("pr");
  gSystem->Exec(Form("convert $(ls -rt %s*bcm*.png) %srun%s_summary_bcm.pdf",
  		     output_path.Data(),
		     output_path.Data(),
  		     run_seg.Data()));

  gSystem->Exec(Form("rm %s*bcm*.png",output_path.Data()));

  //===== BPM Plots =======
  CheckBPM();
  CheckWireSum();
  PlotPairTree(vBPMXY);
  PlotBPMDiffCorrelation();

  gSystem->Exec(Form("convert $(ls -rt %s*bpm*.png ) %srun%s_summary_bpm.pdf",
  		     output_path.Data(),
		     output_path.Data(),
  		     run_seg.Data()));

  gSystem->Exec(Form("rm %s*bpm*.png",output_path.Data()));

  //===== Main Detector Plots =======
  if(isNormalized)
    CheckNormalizedDetector();
  else
    CheckDetector();

  PlotPairTree(vMainDet);
  CheckDetectorCorrelation();
  gSystem->Exec(Form("convert $(ls -rt %s*maindet*.png %s*pairTree*[ud]s[lr]*.png)  %srun%s_summary_main_detector.pdf",
  		     output_path.Data(),
  		     output_path.Data(),
		     output_path.Data(),
  		     run_seg.Data()));

  gSystem->Exec(Form("rm %s*maindet*.png %s*[ud]s[lr]*.png",
		     output_path.Data(),
		     output_path.Data()));

   //===== AT Detector Plots =======
  if(isNormalized)
    CheckNormalizedAT();		
  else
    CheckAT();
  CheckATCorrelation();

  gSystem->Exec(Form("convert $(ls -rt %s*at*.png)  %srun%s_summary_at_detector.pdf",
  		     output_path.Data(),
		     output_path.Data(),
  		     run_seg.Data()));

  gSystem->Exec(Form("rm %s*at*.png",
		     output_path.Data()));

  //===== SAM Plots =======
  if(isNormalized)
    CheckNormalizedSAM();
  else
    CheckSAM();
  PlotPairTree(vSAM);
  PlotPairTree(vSAMUnity);
  CheckSAMCorrelation();
  gSystem->Exec(Form("convert $(ls -rt %s*sam*.png) %srun%s_summary_sam.pdf",
  		     output_path.Data(),
		     output_path.Data(),
  		     run_seg.Data()));

  gSystem->Exec(Form("rm %s*sam*.png",output_path.Data()));

  //===== Check Regression =====   

  // TTree *mulc_lrb_tree = (TTree*)gROOT->FindObject("mulc_lrb");
  // if (mulc_lrb_tree==NULL){
  //   std::cout << "WARNING: The LRB correction tree was not found for file "
  // 	      << filename << "!" << std::endl;
  // }
  // else{
  //   RegressionSummary();
  //   CheckRegression();
  //   if(isNormalized)
  //     CheckNormalizedComboSAM();
  //   else
  //     CheckComboSAM();
    
  //   if(isNormalized)
  //     CheckRegNormDetector();
  //   else
  //     CheckRegressedDetector();

  //   gSystem->Exec(Form("convert $(ls -rt %s*ratecheck*.png) %srun%s_summary_ratecheck.pdf",
  // 		       output_path.Data(),
  // 		       output_path.Data(),
  // 		       run_seg.Data()));

  //   gSystem->Exec(Form("rm %s*ratecheck*.png",output_path.Data()));

  // }

  // ===== Integrated Convergence 
  Integrated();
  CheckSuperCycle();
  
  //==== Injector BPMs Dx Dy Dr and Ellipticity ====
  // PlotInjBPMS();
  // PlotInjBPMSAq();
  // PlotInjBPMSDr();
  // PlotInjBPMSAelli();
  // TString pdf_filename = Form("run%s_injector_BPM.pdf",run_seg.Data());
  // gSystem->Exec(Form("convert $(ls -rt %srun%s*injector_BPM*.png) %s%s",
  // 		     output_path.Data(),
  // 		     run_seg.Data(),
  // 		     output_path.Data(),
  // 		     pdf_filename.Data()));

  // gSystem->Exec(Form("rm %srun%s*injector_BPM*.png",
  // 		     output_path.Data(),
  // 		     run_seg.Data())); 

  // gSystem->Exec(Form("pdfunite $(ls -rt %s/*_summary_*.pdf) %s/run%s_all.pdf",
  // 		     output_path.Data(),
  // 		     output_path.Data(),run_seg.Data()));

}

