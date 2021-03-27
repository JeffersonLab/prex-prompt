  // Function to Get Run list 
  // Author : Tao Ye
typedef struct{Int_t run,slug,arm;
  TString config,flag,ihwp,wien,polarity;} RunInfo;
void ParseLine(TString, RunInfo&) ;
void MakeSimpleList(TString prefix = "crex-respin2/"){
  
  ifstream info_file;
  info_file.open(Form("%sall_production.list",prefix.Data()));
  
  TString sline;
  Int_t cur_slug=-1;
  RunInfo runinfo;
  Bool_t is_file_open = kFALSE;
  map< Int_t, vector<Int_t> > fSlugArray;
  while(sline.ReadLine(info_file)){
    ParseLine(sline,runinfo);
    Int_t my_slug =runinfo.slug;
    Int_t my_run =runinfo.run;
    if(runinfo.flag != "Bad")
      fSlugArray[my_slug].push_back(my_run);
  }

  FILE* all_out = fopen(Form("%ssimple_list/all_crex.list",prefix.Data()),"w");
  auto iter_slug = fSlugArray.begin();
  while(iter_slug!=fSlugArray.end()){
    Int_t mySlug = (*iter_slug).first;
    TString new_filename = Form("%ssimple_list/slug%d.list",prefix.Data(),mySlug);
    FILE* output;
    output=fopen(new_filename.Data(),"w");
    auto iter=(*iter_slug).second.begin();
    while(iter!=(*iter_slug).second.end()){
      fprintf(output,"%d\n",(*iter));
      fprintf(all_out,"%d\n",(*iter));
      iter++;
    }
    fclose(output);
    iter_slug++;
  }
  fclose(all_out);
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
