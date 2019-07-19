// Injector BPMs Plot Macro 
// Source from Caryn Palatchi
// Adapted by Tao Ye for JAPAN 
// Last Update : 05-2019

#include "device_list.h"

void PlotInjBPMSAelli(vector<const char*> &vBPM, 
		   Int_t IHWPstatus, TString ucut); // generic
void PlotInjBPMSAelli(Int_t IHWPstatus, TString ucut); // interface to panguin
void PlotInjBPMSAelli(); // interface to summary plots

void PlotInjBPMSAelli(){
  TCanvas *c1 = new TCanvas("c1","c1",3600,2400);
  c1->cd();
  PlotInjBPMSAelli(vInjBPM,1,"ErrorFlag==0");  
  plot_title = Form("run%s_injector_BPM_Aelli.png",run_seg.Data());
  c1->SaveAs(output_path+plot_title);
}

void PlotInjBPMSAelli(Int_t IHWPstatus, TString ucut){
  PlotInjBPMSAelli(vInjBPM,IHWPstatus,ucut);
}
void PlotInjBPMSAelli(vector<const char*> &vBPM, 
		   Int_t IHWPstatus, TString ucut){

  //open first run file
  TTree* evt_tree = (TTree*)gROOT->FindObject("evt");
  TTree* pair_tree = (TTree*)gROOT->FindObject("pr");
  TTree* mul_tree = (TTree*)gROOT->FindObject("mul");

  Int_t nBPM = vBPM.size();
  const Int_t ndeti = nBPM;
  Double_t Aelli[ndeti];
  Double_t eAelli[ndeti];
  Double_t rmsAelli[ndeti];
  Double_t zero[ndeti];
  
  TPad *pad1= new TPad("pad1","pad1",0,0,1,1);
  pad1->Divide(1,2);
  pad1->Draw();

  TString objnam;
  TH1D* thishist;
  for(Int_t dd=0;dd<ndeti;dd++)
    {

      mul_tree->Draw(Form("asym_%sElli/ppm>>histe%d",vBPM[dd],dd),ucut,"goff");
      objnam = Form("histe%d",dd);
      thishist = (TH1D*)gDirectory->FindObject(objnam);
      Aelli[dd] = thishist->GetMean();
      eAelli[dd]= thishist->GetMeanError();
      rmsAelli[dd]= thishist->GetRMS();
      zero[dd] = 0.0;
      //      cout<<vBPM[dd]<<" Aq:"<<Aq[dd]<<"("<<rmsAq[dd]<<")+-"<<eAq[dd]<<"ppm Dx:"<<Dx[dd]<<"("<<rmsDx[dd]<<")+-"<<eDx[dd]<<"um Dy:"<<Dy[dd]<<"("<<rmsDy[dd]<<")+-"<<eDy[dd]<<"um "<<endl;
      // cout<<vBPM[dd]<<" Aq[ppm](RMS)+-error,Dx[nm](RMS)+-err,Dy[nm](RMS)+-err,Aelli(RMS*10^3)+-error,Dr[nm]+-err,theta[deg]: "<<Aq[dd]<<" "<<rmsAq[dd]<<" "<<eAq[dd]<<" "<<1e3*Dx[dd]<<" "<<1e3*rmsDx[dd]<<" "<<1e3*eDx[dd]<<" "<<1e3*Dy[dd]<<" "<<1e3*rmsDy[dd]<<" "<<1e3*eDy[dd]<<" "<<Aelli[dd]<<" "<<rmsAelli[dd]<<" "<<eAelli[dd]<<" "<<1e3*Dr[dd]<<" "<<1e3*eDr[dd]<<" "<<theta[dd]<<endl;
    }

 
  const Int_t numchains=ndeti;
  Double_t chain[numchains];
  Double_t chainerr[numchains];
  for (Int_t i=0;i<numchains;i++){
    chain[i]=i+1;
    chainerr[i]=0.0;
  };

  TGraphErrors *Aelligraph;
  TGraphErrors *Aellirmsgraph;
  Aelligraph = new TGraphErrors(numchains,chain,&(Aelli[0]),chainerr,&(eAelli[0]));
  Aellirmsgraph = new TGraphErrors(numchains,chain,&(rmsAelli[0]),chainerr,&(zero[0]));

  Double_t x1 = chain[0]-0.5;
  Double_t x2 = chain[numchains-1]+0.5;
 
  pad1->cd(1);

  Aelligraph->GetHistogram()->GetXaxis()->Set(numchains,x1,x2);
  for(Int_t k=0;k<numchains;k++){
    Aelligraph->GetHistogram()->GetXaxis()->SetBinLabel(k+1,vBPM[k]);
  }

  Aelligraph->SetMarkerStyle(21);
  Aelligraph->SetMarkerSize(3);
  Aelligraph->SetMarkerColor(1);
  Aelligraph->SetLineColor(1);
  Aelligraph->Draw("AP");
  Aelligraph->SetTitle(Form("IHWP=%d, %s ",IHWPstatus,ucut.Data()));
  Aelligraph->GetYaxis()->SetTitle("Aelli(ppm)");
  Aelligraph->GetYaxis()->SetTitleOffset(1.5);
  Aelligraph->GetXaxis()->SetLabelSize(0.045);
  pad1->cd(1)->SetGrid();

  
  pad1->cd(2);
  Aellirmsgraph->GetHistogram()->GetXaxis()->Set(numchains,x1,x2);
  for(Int_t k=0;k<numchains;k++){
    Aellirmsgraph->GetHistogram()->GetXaxis()->SetBinLabel(k+1,vBPM[k]);
  }

  Aellirmsgraph->SetMarkerStyle(21);
  Aellirmsgraph->SetMarkerSize(3);
  Aellirmsgraph->SetMarkerColor(1);
  Aellirmsgraph->SetLineColor(1);
  Aellirmsgraph->Draw("AP");
  Aellirmsgraph->SetTitle(Form("IHWP=%d, %s ",IHWPstatus, ucut.Data()));
  Aellirmsgraph->GetYaxis()->SetTitle("RMS(ppm)");
  Aellirmsgraph->GetYaxis()->SetTitleOffset(1.5);
  Aellirmsgraph->GetXaxis()->SetLabelSize(0.045);
  pad1->cd(2)->SetGrid();

}

