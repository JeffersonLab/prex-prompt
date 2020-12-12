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
  static const UInt_t kErrorFlag_ADC_Glitch = 0x2e; // merge sample size, software sum
  static const UInt_t kErrorFlag_Burp       = 0x20000000; // Burp cut flag
  static const UInt_t kErrorFlag_Stability  = 0x1000000;  // Stability cut flag
  static const UInt_t kErrorFlag_LocalGlobal= 0x4000000;  // Global (4)
  

  TTree* evt_tree = (TTree*)gROOT->FindObject("evt");

  const Int_t nErrorTypes = 8; // 7+1; Shifted by 1 for Good counts
  TH1D *hdec = new TH1D("hdec_"+device,device+"'s Device Error Counter && Not (Trip || BMOD)",nErrorTypes,0,nErrorTypes); 
  Int_t ErrorCounter[nErrorTypes];
  TString ErrorSelection[nErrorTypes];
  TString ErrorLabel[nErrorTypes] = {
             "Good non-Trip",
				     "Any ADC Glitch",
				     "ADC Saturation",
				     "Same HW",
             //"Sample Size",
				     //"Software Sum",
				     //"Sequence",
				     //"Zero HW",
				     "Lower Limit",
				     "Upper Limit",
             "Burp Cut",
				     "Stability Cut",
				     //"In Global",
            };

  UInt_t ErrorCode[nErrorTypes] = {0,
				     kErrorFlag_ADC_Glitch,
				     kErrorFlag_VQWK_Sat,
				     kErrorFlag_SameHW,
				     kErrorFlag_EventCut_L,
				     kErrorFlag_EventCut_U,
             kErrorFlag_Burp,
             kErrorFlag_Stability,
             //kErrorFlag_LocalGlobal,
            };

  // NOT BMOD or Beam Trip cut
  ErrorSelection[0] = Form("%s.Device_Error_Code==0 && (ErrorFlag&0x8008000) == 0",
      device.Data());
  ErrorSelection[1] = Form("(%s.Device_Error_Code & %d )!=0 && (ErrorFlag&0x8008000) == 0",
      device.Data(),ErrorCode[1]);
  
  if(ErrorSelection[0]==0)
    return;
  else{
      for(int i= 2; i<nErrorTypes ; i++){
        ErrorSelection[i] = Form("(%s.Device_Error_Code & %d )==%d && (ErrorFlag&0x8008000) == 0",
                    device.Data(),ErrorCode[i],ErrorCode[i]);
      }
    Double_t nTotal = evt_tree->GetEntries();
    for(int i=0;i<nErrorTypes;i++){
      int ibin = nErrorTypes-i;
      ErrorCounter[i] = evt_tree->GetEntries(ErrorSelection[i]);
      if(nTotal==0)
	hdec->SetBinContent(ibin,0.0);
      else
	hdec->SetBinContent(ibin,ErrorCounter[i]); // Numbers instead of percents
	//hdec->SetBinContent(ibin,ErrorCounter[i]/nTotal*100.0);
      hdec->GetXaxis()->SetBinLabel(ibin,ErrorLabel[i]);
    }
  
    hdec->SetBarWidth(0.8);
    hdec->SetBarOffset(0.1);
    hdec->GetYaxis()->SetTitle("Error counts, non-(trip or bmod)");
    hdec->GetXaxis()->SetLabelSize(0.06);
    hdec->SetFillColor(49);
    hdec->Draw("hbar");

    TText* RatioText[nErrorTypes];
    for(int i=0;i<nErrorTypes;i++){
      TString mytext = "";
      if (i == 0) {
        mytext = Form("%.2f %% of %d total events",ErrorCounter[i]*100.0/nTotal,(Int_t)nTotal);
      }
      else{
        mytext = Form("%d",ErrorCounter[i]);
      }
      // OLD
      //TString mytext = Form("%.2f %%",ErrorCounter[i]*100.0/nTotal);
      RatioText[i]= new TText(5,(nErrorTypes-i-1)+0.2,mytext);
      RatioText[i]->SetNDC(0);
      RatioText[i]->Draw("same");
    }

   }
}
