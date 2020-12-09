// Open.C
// 	- postpan regression output reader macro
//	author : Tao Ye	
//	Last update :  July 2019

void Open(Int_t run_number, Int_t split=0, TString name_stem=""){
  
  TString name_stems[]={"prexTest","prexPrompt"};
  Bool_t isFound = kFALSE;
  int i= 0;
  int n= sizeof(name_stems)/sizeof(*name_stems);
  TFile* redfile;
  TString filename;
  if(name_stem!=""){
    filename = Form("./results/%s_%d_%03d_regress_postpan.root",
		    name_stem.Data(),run_number,split);
    redfile = TFile::Open(filename);
    if(redfile==NULL){
      cout << filename << "is not found " << endl;
      isFound = kFALSE;
    }
  }else{
    while(!isFound && (i<n)){
      filename = Form("./results/%s_%d_%03d_regress_postpan.root",
		      name_stems[i].Data(),run_number,split);
      redfile = TFile::Open(filename);
      if(redfile!=NULL){
	isFound = kTRUE;
	cout << filename << " is found " << endl;
	break;
      }
      i++;
    }
  }
  if(!isFound){
    cout << " No file matched!" << endl;
    cout << " Have a nice day! " << endl;
    return;
  }
  TVectorD *MyStat = (TVectorD*)redfile->Get("MyStat");
  Int_t nGoodEvents = (*MyStat)(0);
  if(nGoodEvents==0)
    cout << "-- Warning: No Good Event is found in this run !! " << endl;
  else
    cout << nGoodEvents << " good patterns are found " << endl;
  vector<TString> *DVnames = (vector<TString>*)redfile->Get("DVNames");
  vector<TString> *IVnames = (vector<TString>*)redfile->Get("IVNames");
  
  Int_t nDV = (*DVnames).size();
  Int_t nIV = (*IVnames).size();
  TString dv_name, iv_name;
  TTree *mini_tree = (TTree*)redfile->Get("mini");
  for(Int_t idv=0;idv<nDV;idv++){
    for(Int_t iiv=0;iiv<nIV;iiv++){
      dv_name = (*DVnames)[idv];
      iv_name = (*IVnames)[iiv];
      dv_name.ReplaceAll("asym_","");
      iv_name.ReplaceAll("diff_","");
      TString coeff_name = Form("coeff[%d][%d]",idv,iiv);
      // TString err_coeff_name = Form("err_coeff[%d][%d]",idv,iiv); 
      mini_tree->SetAlias(Form("%s_%s",dv_name.Data(),iv_name.Data()),
			  coeff_name);
    }
  }
}
