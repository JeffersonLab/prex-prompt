// 	postpan regression output reader macro
//	author : Tao Ye	
//	Last update :  July 2019

void rootlogon(){
  cout << " ----------------------------------------------" <<endl;
  cout << "PREX-II postpan Regression Output Reader" << endl;
  cout << "	\t macro author: Tao Ye" << endl;
  cout << "	\t <tao.ye@stonybrook.edu> " << endl;
  cout << "	\t Last update: July 2019" << endl;
  cout << "Usage : "<< endl;
  cout << "	\t Open(<run_number>) "<< endl;
  cout << " ----------------------------------------------\n" <<endl;
  
  gROOT->LoadMacro("./scripts/Open.C");

}
