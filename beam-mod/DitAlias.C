void DitAlias(TString rootfilenName){
  
// In order 4aX, 4aY, 4eX, 4eY, 12X
// slope unit: fraction / mm
// ** which is  1e-3(ppm/um)
  TFile* japanOutput = TFile::Open(rootfilenName);
  double slope_usl[5]={-144.14e-3, 
		       1e-3, 
		       71.345e-3, 
		       -14.104e-3,
		       56.145e-3};
  double slope_usr[5]={-108.03e-3,
		       0.1818e-3, 
		       -22.7314e-3, 
		       -11.3323e-3 ,
		       57.0824e-3};
  double slope_dsl[5]={-147.066e-3,
		       0.832e-3,
		       75.594e-3,
		       -13.646e-3,
		       56.439e-3};
  double slope_dsr[5]={-118.3035e-3,
		       0.4085e-3,
		       -14.3978e-3,
		       -12.8514e-3,
		       61.5153e-3 };
  

  TString maindet_array[]={"asym_usl","asym_usr",
			    "asym_dsl","asym_dsr"};

  double* slopes[]={slope_usl,slope_usr,
		    slope_dsl,slope_dsr};

  TString bpm_array[5]={"diff_bpm4aX","diff_bpm4aY",
			"diff_bpm4eX","diff_bpm4eY",
			"diff_bpm12X"};
  
  Int_t ndet = sizeof(maindet_array)/sizeof(*maindet_array);
  Int_t nmon = sizeof(bpm_array)/sizeof(*bpm_array);
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
