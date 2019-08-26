//////////////////////////////////////////////////////////////////////
//
// Integrated.C
//   Bryan Moffit - June 2005
//
// edited by Caryn Palatchi 3/2019 for japan
//
// edited by Tao Ye 5/2019 
//
//  Provides a means to determine the convergence (or lack of) of
//   a given parameter (branch of a tree) vs time.
//

#include "device_list.h"
void Integrated(TString treename, 
		TString parameter,
		TString usercut,
		UInt_t nbins); // interface to panguin

void Integrated(); // interface to summary plots


void Integrated(){
  Int_t can_width = 1200;
  TCanvas *this_can;

  Int_t nBPM = vDitherBPM.size();
  this_can = new TCanvas("","",2*can_width,can_width);
  this_can->Divide(2,1);

  // ========= BCM =============
  this_can->cd(1);
  Integrated("mul",
	     "asym_bcm_an_us",
	     "ErrorFlag==0",
	     20);
  this_can->cd(2);
  Integrated("mul",
	     "asym_bcm_an_ds",
	     "ErrorFlag==0",
	     20);
  plot_title = Form("run%s_integrated_convergence_analog_bcm.png",
		    run_seg.Data());
  TText *label = new TText(0.0,0.01,plot_title);      
  label->SetNDC();
  this_can->cd();
  label->Draw("same");
  this_can->SaveAs(output_path+ plot_title);
  this_can->Clear("D");

  // ========= BPM =============
  for(int ibpm=0;ibpm<nBPM;ibpm++){
    this_can->cd(ibpm%2+1);
    Integrated("mul",
	       "diff_"+TString(vDitherBPM[ibpm]),
	       "ErrorFlag==0",
	       20);
    if(ibpm%2==1){
      plot_title = Form("run%s_integrated_convergence_%s_%s.png",
			run_seg.Data(),vDitherBPM[ibpm-1],vDitherBPM[ibpm]);
      TText *label = new TText(0.0,0.01,plot_title);      
      label->SetNDC();
      this_can->cd();
      label->Draw("same");
      this_can->SaveAs(output_path+ plot_title);
      this_can->Clear("D");
    }
  }
  // ========= SAM =============

  const char* sam_array[]={"sam2","sam6","sam4","sam8",
			   "sam1","sam3","sam5","sam7"};
  for(int isam=0;isam<8;isam++){
    this_can->cd(isam%2+1);
    Integrated("mul",
	       "asym_"+TString(sam_array[isam]),
	       "ErrorFlag==0",
	       20);

    if(isam%2==1){
      plot_title = Form("run%s_integrated_convergence_%s_%s.png",
			run_seg.Data(),sam_array[isam-1],sam_array[isam]);
      TText *label = new TText(0.0,0.01,plot_title);      
      label->SetNDC();
      this_can->cd();
      label->Draw("same");
      this_can->SaveAs(output_path+ plot_title);
      this_can->Clear("D");
    }
  }
  // ========= Detector =============
  const char* maindet_array[]={"usl","usr","dsl","dsr"};

  for(int idet=0;idet<4;idet++){
    this_can->cd(idet%2+1);
    Integrated("mul",
	       "asym_"+TString(maindet_array[idet]),
	       "ErrorFlag==0",
	       20);

    if(idet%2==1){
      plot_title = Form("run%s_integrated_convergence_%s_%s.png",
			run_seg.Data(),maindet_array[idet-1],maindet_array[idet]);
      TText *label = new TText(0.0,0.01,plot_title);      
      label->SetNDC();
      this_can->cd();
      label->Draw("same");
      this_can->SaveAs(output_path+ plot_title);
      this_can->Clear("D");
    }
  }

  gSystem->Exec(Form("convert $(ls -rt %s*integrated_convergence*.png) %srun%s_convergence.pdf",
		     output_path.Data(),output_path.Data(),run_seg.Data()));

  gSystem->Exec(Form("rm %s*integrated_convergence*.png",output_path.Data()));
  
}

void Integrated(TString treename, 
		TString parameter,
		TString usercut,
		UInt_t nbins) {

  // Check to make sure input arguments are okay.
  TTree* tree = (TTree*)gROOT->FindObject(treename);
  TPad* pad1 = new TPad("pad1","",0,0,1,1);
  pad1->Draw();  
  pad1->cd();
  pad1->SetGridy();
  if(!tree) {
    cout << "Integrated: " << endl
	 << "\t Input tree does not exist." << endl;
    return 0;
  }
  if(!tree->FindBranch(parameter)) {
    cout << "Integrated: " << endl
	 << "\t Input parameter (" << parameter 
	 << ") does not exist in tree." << endl;
    return 0;
  }
  
  // Make sure nbins!=0
  if(nbins==0) return 0;

  // Grab the parameter entries from the tree
  
  Long64_t total_entries = tree->Draw(parameter,usercut,"goff");
  if(total_entries==-1) {
    cout << "Integrated: " << endl
	 << "\t Could not process.  Check variables within provided cut:" 
	 << endl
	 << "\t\t" << usercut << endl;
    return 0;
  }

  // Redraw, with higher fEstimate, if necessary
  if(total_entries>tree->GetEstimate()) {
    tree->SetEstimate(total_entries);
    tree->Draw(parameter,usercut,"goff");
  }

  // Determine the number of entries per bin (ent_per_bin)
  Double_t ent_per_bin = tree->GetSelectedRows()/nbins;

  TGraphErrors *graph = new TGraphErrors(nbins);

  // Go through each bin (accumulating statistics), 
  // and add it to the TGraphErrors

  TStatistic  *stat = new TStatistic();
  UInt_t current_bin = 0;
  UInt_t entries_in_bin = 0;
  for(UInt_t ient = 0; ient<tree->GetSelectedRows(); ient++) {
    if(entries_in_bin==ent_per_bin) {
      // Set current bin in TGraph, and move on to next bin
      graph->SetPoint(current_bin,(current_bin+1)*ent_per_bin,stat->GetMean());
      graph->SetPointError(current_bin,0,stat->GetMeanErr());
      current_bin++; entries_in_bin=0;
    }
    Double_t value = tree->GetV1()[ient];
    stat->Fill(value);
    entries_in_bin++;
  }
    
  // Set default titles for graph, x-axis, y-axis
  graph->SetTitle(parameter+" Integrated Convergence;Pattern Number ;"+parameter);

  graph->SetMarkerStyle(20);
  graph->SetMarkerSize(2);
  graph->Draw("AP");
 
}
