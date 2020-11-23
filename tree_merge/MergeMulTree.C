void MergeMulTree(Int_t slug);
void MergeMulTree(TString label);

void MergeMulTree(Int_t slug){
  TString label = Form("slug%d",slug);
  MergeMulTree(label);
}

void MergeMulTree(TString label){
  TString filename  = label+".list";
  TString path = "./prex-runlist/simple_list/";
  FILE *runlist = fopen((path+filename).Data(),"r");

  vector<TString> tree_name_array={"burst","burst_mulc","burst_mulc_dit","burst_mulc_dit_combo"};
  vector<TTree*> output_tree_array;
  Int_t nTree = tree_name_array.size();
  map<TString,TList*> list_map;
  map<TString, vector<Int_t> >  runID_map;
  for(int i=0;i<nTree;i++){
    list_map[tree_name_array[i]]= new TList();
    output_tree_array.push_back( new TTree() );
  }

  if(runlist!=NULL){
    TFile *output = TFile::Open("./rootfiles/MulTreeMerged_"+label+".root","RECREATE");
    while(!feof(runlist)){
      Int_t run_number=0;
      fscanf(runlist,"%d/n",&run_number);
      if(run_number==0)
	continue;

      TFile *this_file = TFile::Open(Form("$QW_ROOTFILES/prexPrompt_pass1_%d.000.root",run_number));
      if(this_file==NULL)
	continue;
      cout << this_file->GetName() << endl;
      vector<TString>::iterator it_tree  = tree_name_array.begin();
      while(it_tree!=tree_name_array.end()){
	TTree *aTree_ptr = (TTree*)this_file->Get(*it_tree);
	if(aTree_ptr!=NULL){
	  list_map[*it_tree]->Add(aTree_ptr);
	  Int_t nburst = aTree_ptr->GetEntries();
	  for(int i=0;i<nburst;i++)
	    runID_map[*it_tree].push_back(run_number);
	}
	it_tree++;
      } //end of tree loop
    } // end of the loop over run in a list 
    fclose(runlist);
    output->cd();
    
    for(int i =0;i<nTree;i++){
      output_tree_array[i] = TTree::MergeTrees( list_map[tree_name_array[i]] );
      Int_t run;
      TTree *this_tree =output_tree_array[i];
      TBranch *branch_run = this_tree->Branch("run",&run,"run/I");
      Int_t nevt = this_tree->GetEntries();
      vector<Int_t> runlist = runID_map[tree_name_array[i]];
      for(int i = 0; i<nevt;i++){
	this_tree->GetEntry(i);
	run = runlist[i];
	branch_run->Fill();
      }
      this_tree->SetMarkerStyle(20);
      this_tree->Write();
    }
    cout << "-- Closing " << output->GetName()<< endl;
    output->Close();
  } // end of if runlist exists
}

