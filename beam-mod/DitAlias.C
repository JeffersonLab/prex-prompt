/*
  Example 
  in prompt/beam-mod/ directory
  root -b 

 */
void AliasGenerator(TString rootfilenName, Int_t slug_id=11, TCut user_cut="run!=3500"){
  
// In order 4aX, 4aY, 4eX, 4eY, 12X
// slope unit: fraction / mm
// ** which is  1e-3(ppm/um)
  TFile* slopefile = TFile::Open(Form("rootfiles/dit_slopes_slug%d.root",
				      slug_id));

  TString maindet_array[]={"asym_usl","asym_usr",
			    "asym_dsl","asym_dsr"};
  TString bpm_array[5]={"diff_bpm4aX","diff_bpm4aY",
			"diff_bpm4eX","diff_bpm4eY",
			"diff_bpm12X"};
  
  Int_t ndet = sizeof(maindet_array)/sizeof(*maindet_array);
  Int_t nmon = sizeof(bpm_array)/sizeof(*bpm_array);
  double slopes[ndet][nmon];
  
  TFile* japanOutput = TFile::Open(rootfilenName);
  TTree *mul_tree = (TTree*)japanOutput->Get("mul");
  if(mul_tree==NULL){
    cout << "Error: " 
  	 << "mul tree doesn't exsit!" << endl;
    return;
  }
  else{
    for(int idet=0; idet<ndet;idet++){
      TString this_alias = maindet_array[idet];
      for(int imon=0;imon<nmon;imon++){
	this_alias += Form("+%f*%s",slopes[idet][imon],bpm_array[imon].Data());
      }
      cout << this_alias << endl;
      mul_tree->SetAlias("dit_"+maindet_array[idet],
			 this_alias);
    }
  }
}
