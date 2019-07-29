// Device error code decoder Marco 
// author : Tao Ye
// date : 05-2019

#include "TError.h"

void DeviceErrorCounter(TString device){

  TPad *pad1 = new TPad("pad1","pad1",0,0,1,1);
  pad1->SetLeftMargin(0.2);
  pad1->SetRightMargin(0.02);
  pad1->SetGridx();
  pad1->Draw();
  pad1->cd();
  // gErrorIgnoreLevel = kWarning+1;   // shut up warnings;
  gStyle->SetOptStat(0);

  // Copied from japan/QwTypes.h 
  static const UInt_t kErrorFlag_VQWK_Sat   = 0x01; // in Decimal 1 to identify a VQWK is saturating
  static const UInt_t kErrorFlag_sample     = 0x2;  // in Decimal 2   for sample size check
  static const UInt_t kErrorFlag_SW_HW      = 0x4;  // in Decimal 4   HW_sum==SW_sum check
  static const UInt_t kErrorFlag_Sequence   = 0x8;  // in Decimal 8   sequence number check
  static const UInt_t kErrorFlag_SameHW     = 0x10; // in Decimal 16  check to see ADC returning same HW value
  static const UInt_t kErrorFlag_ZeroHW     = 0x20; // in Decimal 32  check to see ADC returning zero
  static const UInt_t kErrorFlag_EventCut_L = 0x40; // in Decimal 64  check to see ADC failed lower limit of the event cut
  static const UInt_t kErrorFlag_EventCut_U = 0x80; // in Decimal 128 check to see ADC failed upper limit of the event cut

  TTree* evt_tree = (TTree*)gROOT->FindObject("evt");

  const Int_t nErrorTypes = 9; // 8+1; Shifted by 1 for Good counts
  TH1D *hdec = new TH1D("hdec_"+device,device+" Device  Error Counter",nErrorTypes,0,nErrorTypes); 
  Int_t ErrorCounter[nErrorTypes];
  TString ErrorSelection[nErrorTypes];
  TString ErrorLabel[nErrorTypes] = {"Good",
				     "Saturation",
				     "Sample Size",
				     "Software Sum",
				     "Sequence",
				     "Same HW",
				     "Zero HW",
				     "Lower Limit",
				     "Upper Limit"};

  UInt_t ErrorCode[nErrorTypes] = {0,
				   kErrorFlag_VQWK_Sat,
				   kErrorFlag_sample,
				   kErrorFlag_SW_HW,
				   kErrorFlag_Sequence,
				   kErrorFlag_SameHW,
				   kErrorFlag_ZeroHW,
				   kErrorFlag_EventCut_L,
				   kErrorFlag_EventCut_U};

  ErrorSelection[0] = Form("%s.Device_Error_Code==0 ",
			   device.Data());
  
  if(ErrorSelection[0]==0)
    return;
  else{
    for(int i= 1; i<nErrorTypes ; i++)
      ErrorSelection[i] = Form("(%s.Device_Error_Code & %d )== %d ",
			       device.Data(),ErrorCode[i],ErrorCode[i]); 

    Double_t nTotal = evt_tree->GetEntries();
    for(int i=0;i<nErrorTypes;i++){
      int ibin = nErrorTypes-i;
      ErrorCounter[i] = evt_tree->GetEntries(ErrorSelection[i]);
      if(nTotal==0)
	hdec->SetBinContent(ibin,0.0);
      else
	hdec->SetBinContent(ibin,ErrorCounter[i]/nTotal*100.0);
      hdec->GetXaxis()->SetBinLabel(ibin,ErrorLabel[i]);
    }
  
    hdec->SetBarWidth(0.8);
    hdec->SetBarOffset(0.1);
    hdec->GetYaxis()->SetTitle("in Percentage");
    hdec->GetXaxis()->SetLabelSize(0.06);
    hdec->SetFillColor(49);
    hdec->Draw("hbar");
   }
}
