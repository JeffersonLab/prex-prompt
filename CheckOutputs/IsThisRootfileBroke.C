int IsThisRootfileBroke(TString name = ""){
	TFile *f = new TFile(name);
	if(f->IsZombie()){
		cout << name << "zombieflag" << endl;
    		return 0;
	}else{
		cout << name << "goodflag" << endl;
    		return 1;
	}
}
