void testAgg(TString fileName = "NULL"){
  if (fileName == "NULL"){
    Printf("Error, must input a filename for checking");
  }
  else{
    TChain *chain = new TChain("agg");
    chain->Add(fileName);
    Int_t num_entries = 0;
    num_entries = chain->Scan("run_number");
    if (num_entries == 0){
      Printf("\n\nError, agg tree is dead for %s\n\n",fileName.Data());
    }
  }
}
