void Open(Int_t slug_number){
  TFile* _file = TFile::Open(Form("rootfiles/slug%d_merged.root",slug_number));
  TTree *burst_tree = (TTree*)_file->Get("burst");
  TTree *mini_tree = (TTree*)_file->Get("mini");
  burst_tree->BuildIndex("run");
  mini_tree->BuildIndex("run_number");
  burst_tree->AddFriend(mini_tree);
}
