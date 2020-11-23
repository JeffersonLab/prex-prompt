  // Function to Get Run list 
  // Author : Tao Ye
	//-- Choose one good run randomly from each slug 

typedef struct{Int_t run,slug,arm;
  TString config,flag,ihwp,wien,polarity;} RunInfo;
void ParseLine(TString, RunInfo&) ;
void MakeTestList(){
  
  ifstream info_file;
  info_file.open("all_production.list");
  
  TString sline;
  Int_t cur_slug=-1;
  RunInfo runinfo;
  Bool_t is_file_open = kFALSE;
  vector< vector<Int_t> > fSlugArray(95);
  while(sline.ReadLine(info_file)){
    ParseLine(sline,runinfo);
    Int_t my_slug =runinfo.slug;
    Int_t my_run =runinfo.run;
    if(runinfo.flag == "Good")
      fSlugArray[my_slug].push_back(my_run);
  }
  FILE* output_txt = fopen("./good_list/test.list","w");
  for(int i=0;i<=94;i++){
    Int_t nLength = fSlugArray[i].size();
    Int_t iMiddle = (Int_t)nLength/2.0;
    fprintf(output_txt,"%d\n",fSlugArray[i][iMiddle]);
  }
  fclose(output_txt);
}


void ParseLine(TString sline, RunInfo &ret){
  TObjArray *token =sline.Tokenize(',');
  ret.run = (((TObjString*)token->At(0))->GetString()).Atoi();
  ret.slug = (((TObjString*)token->At(1))->GetString()).Atoi();
  ret.config = ((TObjString*)token->At(2))->GetString();
  ret.flag = ((TObjString*)token->At(3))->GetString();
  ret.ihwp = ((TObjString*)token->At(4))->GetString();
  ret.wien = ((TObjString*)token->At(5))->GetString();
  ret.arm = (((TObjString*)token->At(6))->GetString()).Atoi();
  
  Double_t fPolarity;
  
  if(ret.ihwp=="IN" )
    fPolarity =1;
  else if(ret.ihwp=="OUT")
    fPolarity =-1;

  if(ret.wien.Contains("RIGHT"))
    fPolarity *=1;
  else if(ret.wien.Contains("LEFT"))
    fPolarity *=-1;

  if(fPolarity==1)
    ret.polarity="+";
  else if (fPolarity==-1)
    ret.polarity="-";
  
}
