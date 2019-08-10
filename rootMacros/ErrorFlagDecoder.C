// Global ErrorFlag decoder 
// author : Tao Ye
// date : 05-2019

#include "TError.h"

Bool_t ErrorFlagDecoder(){

  TPad *pad1 = new TPad("pad1","pad1",0,0,1,1);
  pad1->SetLeftMargin(0.2);
  pad1->SetGridx();
  pad1->Draw();
  pad1->cd();
  // gErrorIgnoreLevel = kWarning+1;   // shut up warnings;
  gStyle->SetOptStat(0);

  // Copied from japan/QwTypes.h 

  static const UInt_t kErrorFlag_EventCut_L = 0x40; // in Decimal 64  check to see ADC failed lower limit of the event cut
  static const UInt_t kErrorFlag_EventCut_U = 0x80; // in Decimal 128 check to see ADC failed upper limit of the event cut

  static const UInt_t kBCMErrorFlag = 0x100; // in Decimal 256 to identify the single event cut is failed for a BCM (regular or combo)
  static const UInt_t kErrorFlag_BlinderFail = 0x200;// in Decimal 512 to identify the blinder flag
  static const UInt_t kBPMErrorFlag = 0x400; // in Decimal 1024 to identify the single event cut is failed for a BPM (Stripline or cavity or comboBPM)
  static const UInt_t kPMTErrorFlag = 0x800; // in Decimal 2048 to identify the single event cut is failed for a PMT (Combined or regular)

  static const UInt_t kBModFFBErrorFlag = 0x1000; // in Decimal 4096 (2^12) to identify the FFB OFF periods for Energy modulation
  static const UInt_t kBModErrorFlag = 0x8000; // in Decimal 32768 (2^15) to identify the single event cut is failed for a BMod channel
  static const UInt_t kErrorFlag_Helicity = 0x20000;  // Any type of helicity decoding problem
  static const UInt_t kErrorFlag_BurpCut =   0x800000;// in Decimal 2^23 to identify a burp cut failure
  static const UInt_t kBeamStabilityError= 0x10000000;//in Decimal 2^28(268435456) to identify the a stability cut
  static const UInt_t kBeamTripError     =  0x8000000;// in Decimal 2^27(134217728) to identify the an event within a beam trip range set by ring parameters
  static const UInt_t kStabilityCut      =  0x1000000;// in Decimal 2^24 (16777216) to i
  static const UInt_t kBadEventRangeError= 0x80000000;//in Decimal 2^31 to identify an event range we don't like anymore


  TTree* evt_tree = (TTree*)gROOT->FindObject("evt");

  const Int_t nErrorTypes = 15; // 12+1; Shifted by 1 for Good counts
  TH1D *hdec = new TH1D("hdec"," Global Error Flag Counter",nErrorTypes,0,nErrorTypes); 
  TH1D *htotal = new TH1D("htotal","Global Error Flag Counter",nErrorTypes,0,nErrorTypes); 
  Int_t ErrorCounter[nErrorTypes];

  Double_t ErrorRatio[nErrorTypes];
  TText* RatioText[nErrorTypes];

  TString ErrorSelection[nErrorTypes];
  TString ErrorLabel[nErrorTypes] = {"Good / Total",
				     "Lower Limit",
				     "Upper Limit",
				     "BCM Failure",
				     "Blinder Failure",
				     "BPM Failure",
				     "PMT Failure",
				     "FFB OFF for Energy Mod",
				     "BMod Channel Failure",
				     "Helicity Error",
				     "Burp Cut",
				     "Stability Error",
				     "Beam Trip",
				     "Stability Cut",
				     "Bad Event Range"};

  UInt_t ErrorCode[nErrorTypes] = {0,
				   kErrorFlag_EventCut_L,
				   kErrorFlag_EventCut_U,
				   kBCMErrorFlag,
				   kErrorFlag_BlinderFail,
				   kBPMErrorFlag,
				   kPMTErrorFlag,
				   kBModFFBErrorFlag,
				   kBModErrorFlag,
				   kErrorFlag_Helicity,
				   kErrorFlag_BurpCut,
				   kBeamStabilityError,
				   kBeamTripError,
				   kStabilityCut,
				   kBadEventRangeError};


  Double_t nTotal = evt_tree->Draw("ErrorFlag","","goff");

  ErrorSelection[0] = "ErrorFlag==0 ";
  for(int i= 1; i<nErrorTypes ; i++)
    ErrorSelection[i] = Form("(ErrorFlag&%d )==%d ",ErrorCode[i],ErrorCode[i]); 

  for(int i=0;i<nErrorTypes;i++){
    int ibin = nErrorTypes-i;
    ErrorCounter[i] = evt_tree->GetEntries(ErrorSelection[i]);
    ErrorRatio[i] = (Double_t)ErrorCounter[i]/nTotal;
    hdec->SetBinContent(ibin,ErrorCounter[i]);
    htotal->GetXaxis()->SetBinLabel(ibin,ErrorLabel[i]);
  }

  htotal->GetYaxis()->SetTitle("Counts");
  htotal->GetXaxis()->SetLabelSize(0.05);
  htotal->SetBarWidth(0.8);
  htotal->SetBarOffset(0.1);
  htotal->SetBinContent(nErrorTypes,nTotal);
  htotal->SetFillColor(38);
  htotal->Draw("hbar");
  
  hdec->SetBarWidth(0.8);
  hdec->SetBarOffset(0.1);
  hdec->SetFillColor(49);
  hdec->Draw("hbar same ");

  for(int i=0;i<nErrorTypes;i++){
    TString mytext = Form("%.1f %%",ErrorRatio[i]*100);
    RatioText[i] = new TText((hdec->GetBinContent(nErrorTypes-i))*1.05,(nErrorTypes-i-1)+0.2,mytext);
    RatioText[i]->SetNDC(0);
    RatioText[i]->Draw("same");
  }

  if (ErrorCounter[0]==0)
    return kFALSE;
  else
    return kTRUE;
}
