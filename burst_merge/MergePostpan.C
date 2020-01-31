void MergePostpan(TString label="prod"){
  TString filename  = label+".list";
  TString path = "./runlist/";
  FILE *runlist = fopen((path+filename).Data(),"r");
  if(runlist!=NULL){
    TFile *output = TFile::Open("./rootfiles/PostpanMerged_"+label+".root","RECREATE");
    TTree* output_tree = new TTree("mini","mini");
    TList* list = new TList();
    while(!feof(runlist)){
      Int_t run_number=0;
      fscanf(runlist,"%d/n",&run_number);
      if(run_number!=0){
	TFile *this_file = TFile::Open(Form("/chafs2/work1/apar/postpan-outputs/prexPrompt_%d_000_regress_postpan.root",run_number));
	if(this_file!=NULL){
	  TTree *this_tree = (TTree*)this_file->Get("mini");
	  if(this_tree!=NULL){
	    list->Add(this_tree);
	  }
	}
      }
    }
    fclose(runlist);
    output->cd();
    output_tree = TTree::MergeTrees(list);
    output_tree->Write();
    cout << " -- Closing output " << output->GetName() << endl;
    output->Close();
  }
}
