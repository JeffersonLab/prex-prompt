#include "device_list.h"
using namespace std;

void CheckSuperCycle(){

  gStyle->SetOptStat(0);
  gStyle->SetPaintTextFormat("1.1f");
  TTree *evt_tree = (TTree*)gROOT->FindObject("evt");
  if(evt_tree==NULL)
    return;
  Int_t nCoils=7;
  Double_t bmwcycnum;
  evt_tree->SetBranchAddress("bmwcycnum",&bmwcycnum);
  TEventList *elist = new TEventList("elist");
  evt_tree->Draw(">>+elist","bmwcycnum>0 && bmod_ramp>0 && bmwobj>0");
  evt_tree->SetEventList(elist);
  TH1D *hcyc = new TH1D("hcyc","",15000,-0.5,14999.5);
  evt_tree->Draw("bmwcycnum>>hcyc","","goff");
  Int_t bin_first = hcyc->FindFirstBinAbove(0);
  Int_t bin_last = hcyc->FindLastBinAbove(0);
  Int_t cycID_first = hcyc->GetBinCenter(bin_first);
  Int_t cycID_last = hcyc->GetBinCenter(bin_last);
  Int_t nCycle = cycID_last-cycID_first+1;
  TString *cycle_label = new TString[7*nCycle];
  for(int icyc=0;icyc<nCycle;icyc++)
    for(int icoil=0;icoil<nCoils;icoil++)
      cycle_label[icoil+icyc*nCoils]=Form("%d:%d",cycID_first+icyc,icoil+1);
  
  TCanvas *c1 = new TCanvas("c1","c1",2400,700);
  c1->cd();
  c1->SetLogz();
  Bool_t kFound =kFALSE;
  TH2D *h2d = new TH2D("h2d","",7*nCycle,-0.5,7*nCycle-0.5,7,0.5,7+0.5);
  for(int icyc=0;icyc<nCycle;icyc++){
    for(int icoil=0;icoil<nCoils;icoil++){
      for(int iobj=0;iobj<nCoils;iobj++){
	evt_tree->Draw(Form("bmod_trim%d",icoil+1),
		       Form("bmwobj==%d && bmwcycnum==%d",iobj+1,cycID_first+icyc),
		       "goff");
	TH1D* htemp=(TH1D*)gDirectory->FindObject("htemp");
	double rms=htemp->GetRMS();
	h2d->Fill(cycle_label[iobj+nCoils*icyc],icoil+1,rms);
      }
    }
  }
  h2d->SetMarkerSize(1.5);
  h2d->SetTitle(Form("run %s : bmod_trim vs bmwobj ;bmwcycnum:bmwobj ; trimcard #",run_seg.Data()));
  h2d->GetYaxis()->SetNdivisions(7);
  h2d->GetXaxis()->SetNdivisions(700+nCycle);
  h2d->GetXaxis()->SetLabelSize(0.04);
  h2d->GetXaxis()->SetTitleSize(0.04);
  h2d->Draw("COL TEXT");

  plot_title = Form("run%s_supercyle.png",run_seg.Data());
  c1->SaveAs(output_path+plot_title);

}
