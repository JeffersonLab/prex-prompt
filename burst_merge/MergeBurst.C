void MergeBurst(TString label){
  TString filename  = label+".list";
  TString path = "./runlist/";
  FILE *runlist = fopen((path+filename).Data(),"r");
  vector<Int_t> run_array;
  if(runlist!=NULL){
    TFile *output = TFile::Open("./rootfiles/BurstMerged_"+label+".root","RECREATE");
    TTree* merge_burst = new TTree("burst","burst");

    TTree* merge_lrb = new TTree("lrb","lrb");
    TList* list_burst = new TList();
    TList* list_lrb = new TList();
    while(!feof(runlist)){
      Int_t run_number=0;
      fscanf(runlist,"%d/n",&run_number);
      if(run_number!=0){
	TFile *this_file = TFile::Open(Form("$QW_ROOTFILES/prexPrompt_pass2_%d.000.root",run_number));
	if(this_file!=NULL){
	  TTree *burst_tree = (TTree*)this_file->Get("burst");
	  TTree *lrb_tree = (TTree*)this_file->Get("burst_mulc_lrb_alldet_burst");
	  if(burst_tree!=NULL && lrb_tree!=NULL){
	    list_burst->Add(burst_tree);
	    list_lrb->Add(lrb_tree);
	    Int_t nburst  = burst_tree->GetEntries();
	    for(int i=0;i<nburst;i++)
	      run_array.push_back(run_number);
	  }
	}
      }
    }
    fclose(runlist);
    output->cd();
    merge_burst = TTree::MergeTrees(list_burst);
    merge_lrb = TTree::MergeTrees(list_lrb);
    Int_t run;
    TBranch *branch_run = merge_burst->Branch("run",&run,"run/I");
    Int_t nevt = merge_burst->GetEntries();
    for(int i = 0; i<nevt;i++){
      merge_burst->GetEntry(i);
      run = run_array[i];
      branch_run->Fill();
    }
    merge_burst->SetMarkerStyle(20);
    merge_lrb->Write();
    merge_burst->Write();
    cout << "-- Closing " << output->GetName()<< endl;
    output->Close();
  }
}
