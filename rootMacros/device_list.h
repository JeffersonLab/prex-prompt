#ifndef _DEVICE_LIST_H_
#define _DEVICE_LIST_H_

// File IO control variable
TString path;
TString prefix;
TString file_name;
TString output_path;
TString plot_title;
Int_t run_number;
TString run_seg;
TFile *japanOutput;

//  Beamline Monitors

vector<const char*> vBCM={"bcm_an_us", "bcm_an_ds", 
			  "bcm_an_ds3","bcm0l02",
			  "bcm_dg_us","bcm_dg_ds"};

vector<const char*> vBPM={"bpm4a","bpm4e",
			  "bpm4ac","bpm4ec","bpm1",
			  "bpm11","bpm12","bpm16",
			  "bpm0l01","bpm2i01","bpm2i02","bpm1i02","bpm0i02","bpm0i01a"};
// BPM 11 was 14 before 7/16/2019
// BPM 16 was 8 before 7/16/2019
vector<const char*> vBPMXY={"bpm4aX","bpm4aY",
			    "bpm4eX","bpm4eY",
			    "bpm4acX","bpm4acY",
			    "bpm4ecX","bpm4ecY",
          "bpm1X","bpm1Y",
          "bpm11X","bpm11Y", 
			    "bpm12X","bpm12Y",
			    "bpm16X","bpm16Y",
          "bpm0l01X","bpm0l01Y"};


vector<const char*> vDitherBPM={"bpm4aX","bpm4aY",
				"bpm4eX","bpm4eY",
				"bpm12X"};

vector<const char*> vCavBPM={"cav4b","cav4c","cav4d"};

vector<const char*> vSAM={"sam2","sam4","sam6","sam8"};

vector<const char*> vSAMUnity={"sam1","sam3","sam5","sam7"};

vector<const char*> vMainDet={"usl","dsl","usr","dsr"};

vector<const char*> vAT={"atl1","atl2","atr1","atr2"};

vector<const char*> vBlkM = {"asym_bcm_an_ds3","asym_sam2","asym_sam4"};  // Block Monitors


//Injector Plots
//make matrix to hold data points, injector daq can only hold 22 bpms max. 

vector<const char*> vInjBPM = {"bpm2i01","bpm2i02","bpm1i02","bpm1i04",
			       "bpm1i06", "bpm0i01","bpm0i01a","bpm0i02",
			       "bpm0i02a","bpm0i05","bpm0i07","bpm0l01",
			       "bpm0l02","bpm0l03","bpm0l04","bpm0l05",
			       "bpm0l06","bpm0l07","bpm0l10", "bpm0r02",
			       "bpm0r05"};
  
/* vector<const char*> detnams = {"bpm2i01","bpm2i02","bpm1i02","bpm1i04", */
/* 			 "bpm1i06","bpm0i01","bpm0i01a","bpm0i02", */
/* 			 "bpm0i02a","bpm0i05", "bpm0i07","bpm0l01", */
/* 			 "bpm0l02","bpm0l03","bpm0l04","bpm0l05", */
/* 			 "bpm0l06","bpm0l07","bpm0l08","bpm0l09", */
/* 			 "bpm0l10","bpm0r03","bpm0r05"}; */


#endif

