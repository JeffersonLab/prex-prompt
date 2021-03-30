// Function to Get Run list 
// Author : Tao Ye
void GetProductionRunList(TString,TString);
Int_t ParseSlugNumber(TString);
void GenSlugList(TString,TString);

void UpdateSlugList(TString prefix = "crex-respin2/", TString analysis = "production"){
  GetProductionRunList(prefix,analysis);
  GenSlugList(prefix,analysis);
}

void GenSlugList(TString prefix = "crex-respin2/", TString analysis = "production"){

  ifstream info_file;
  info_file.open(Form("%sall_%s.list",prefix.Data(),analysis.Data()));

  TString sline;
  Int_t cur_slug=-1;

  Bool_t is_file_open = kFALSE;
  map< Int_t, vector<TString> > fSlugArray;
  while(sline.ReadLine(info_file)){
    Int_t my_slug = ParseSlugNumber(sline);
    fSlugArray[my_slug].push_back(sline);
  }
  Int_t nslug = fSlugArray.size();
  auto iter_slug = fSlugArray.begin();
  while(iter_slug!=fSlugArray.end()){
    Int_t mySlug = (*iter_slug).first;
    TString new_filename = Form("%sslug%d_info.list",prefix.Data(),mySlug);
    FILE* output;
    output=fopen(new_filename.Data(),"w");
    auto iter=(*iter_slug).second.begin();
    while(iter!=(*iter_slug).second.end()){
      fprintf(output,"%s\n",(*iter).Data());
      iter++;
    }
    fclose(output);
    iter_slug++;
  }
}

Int_t ParseSlugNumber(TString input){
  Ssiz_t dot_pos = input.First(',');
  input.Remove(0,dot_pos+1);
  dot_pos = input.First(',');
  TString slug_str = input(0,dot_pos);
  Int_t slug_number = slug_str.Atoi();

  return slug_number;
}

void GetProductionRunList(TString prefix = "crex-respin2/", TString analysis = "production"){

  TSQLResult* res;
  TSQLRow *row;
  cout << " -- Getting Slug Number from RCDB -- " << endl;
  cout << " -- Connecting to RCDB -- " << endl;
  TSQLServer *rcdb = TSQLServer::Connect("mysql://hallcdb.jlab.org:3306/a-rcdb","rcdb","");
  cout << " -- ServerInfo: " << rcdb->ServerInfo() << endl;
  cout << " -- Host : " << rcdb->GetHost() << endl;
  cout << " -- Query DataBase " << endl;

  TString slugrange = ">99";
  if (prefix.Contains("AT")) {
    slugrange = ">3999";
  }
  if (prefix.Contains("prex")) {
    slugrange = "BETWEEN 0 AND 94";
    if (prefix.Contains("AT")) {
      slugrange = "BETWEEN 500 AND 550";
    }
  }
  TString cutinfo  = "test" ; 
  TString cutinfo2 = "test" ; 
  TString flagSubstitute = "NoFlag";
  if (prefix.Contains("prex")) {
    cutinfo  = " WHERE t1.run_number=t3.run_number AND t1.run_number=t2.run_number AND t1.run_number=t4.run_number AND t1.run_number=t6.run_number AND t1.run_number=t7.run_number AND t1.run_number<4981";
    cutinfo2 = "";
  }
  if (prefix.Contains("crex")) {
    cutinfo  = ", `a-rcdb`.conditions as t8 INNER JOIN `a-rcdb`.condition_types c8 on c8.id=t8.condition_type_id AND c8.name='target_type'";
    cutinfo2 = " WHERE t1.run_number=t3.run_number AND t1.run_number=t2.run_number AND t1.run_number=t4.run_number AND t1.run_number=t6.run_number AND t1.run_number=t7.run_number  AND t1.run_number=t8.run_number AND ((t3.int_value BETWEEN 100 and 250) OR t3.int_value>=4000) ";
    // Include cut on 48Ca Target here
    //cutinfo2 = " WHERE t1.run_number=t3.run_number AND t1.run_number=t2.run_number AND t1.run_number=t4.run_number AND t1.run_number=t6.run_number AND t1.run_number=t7.run_number  AND t1.run_number=t8.run_number AND (t8.text_value='48Ca' OR t3.int_value>=4000) ";
  }

  TString analysis_str = "";
  if (analysis == "production"){
    flagSubstitute = "NoFlag";
    analysis_str = ", `a-rcdb`.conditions as t4 INNER JOIN `a-rcdb`.condition_types c4 on c4.id=t4.condition_type_id AND c4.name='run_type' AND t4.text_value='Production' ";
  }
  if (analysis == "nonJunk") {
    flagSubstitute = "Bad";
    analysis_str = ", `a-rcdb`.conditions as t4 INNER JOIN `a-rcdb`.condition_types c4 on c4.id=t4.condition_type_id AND c4.name='run_type' AND ( t4.text_value='Calibration' OR t4.text_value='Pedestal' OR t4.text_value='Parityscan' OR t4.text_value='Production' ) ";
    //analysis_str = ", `a-rcdb`.conditions as t4 INNER JOIN `a-rcdb`.condition_types c4 on c4.id=t4.condition_type_id AND c4.name='run_type' AND t4.text_value!='Junk' ";
  }

  TString query[]={Form("SELECT t1.run_number,t3.int_value, t7.text_value,CASE WHEN tflag.text_value is NULL THEN '%s' ELSE tflag.text_value END AS flag_res, t1.text_value, t2.text_value,t6.int_value ",flagSubstitute.Data()),
    " FROM `a-rcdb`.conditions as t1 INNER JOIN `a-rcdb`.condition_types c1 on c1.id= t1.condition_type_id AND c1.name='ihwp' ",
    ", `a-rcdb`.conditions as t2 INNER JOIN `a-rcdb`.condition_types c2 on c2.id=t2.condition_type_id AND c2.name='flip_state' ",
    Form(", `a-rcdb`.conditions as t3 INNER JOIN `a-rcdb`.condition_types c3 on c3.id=t3.condition_type_id AND c3.name='slug' AND t3.int_value %s ",slugrange.Data()),
    analysis_str,
    " LEFT JOIN ",
    "( SELECT run_number, text_value ",
    //" FROM `a-rcdb`.conditions t5 INNER JOIN `a-rcdb`.condition_types c5 on c5.id=t5.condition_type_id AND c5.name='run_flag' ) ",
    " FROM `a-rcdb`.conditions t5 INNER JOIN `a-rcdb`.condition_types c5 on c5.id=t5.condition_type_id AND c5.name='run_flag' AND (t5.text_value='Good' OR t5.text_value='Suspicious' OR t5.text_value='NeedCut') ) AS tflag ",
    " ON tflag.run_number = t4.run_number ",
    ", `a-rcdb`.conditions as t6 INNER JOIN `a-rcdb`.condition_types c6 on c6.id=t6.condition_type_id AND c6.name='arm_flag' ",
    ", `a-rcdb`.conditions as t7 INNER JOIN `a-rcdb`.condition_types c7 on c7.id=t7.condition_type_id AND c7.name='run_config' ",
    cutinfo,
    cutinfo2,
    " ORDER BY t1.run_number ASC"
  };

  TString listName = Form("%sall_%s.list",prefix.Data(),analysis.Data());

  int n=sizeof(query)/sizeof(*query);
  TString cmd;
  for(int  i=0;i<n;i++){
    cmd+=query[i];
  }
  res = rcdb->Query(cmd);

  if(res==NULL){
    cout << " -- Failed to Query " << endl;
    cout << " -- Bye-bye! " << endl;
    delete res;
    cout << " -- Closing Connection to RCDB " << endl;

    rcdb->Close();
    delete rcdb;
    return -1;
  }

  int nFields =res->GetFieldCount();
  int nRows = res->GetRowCount();
  if(nRows==0){
    cout << " -- Failed to load Results " << endl;
    cout << " -- Bye-bye! " << endl;
    delete res;
    cout << " -- Closing Connection " << endl;
    rcdb->Close();
    delete rcdb;
    return ;
  }
  cout << " ----------------------------- " << endl;

  FILE*runlist = fopen(listName.Data(),"w");
  for(int irow=0;irow<nRows;irow++){
    row=res->Next();
    for(int j=0; j< nFields; j++){
      cout << "\t" << row->GetField(j) ;
      TString row_ret = TString(row->GetField(j));
      row_ret.ReplaceAll("\n",";");
      fprintf(runlist,"%s",row_ret.Data());
      if(j!=nFields-1)
        fprintf(runlist,",");
    }
    fprintf(runlist,"\n");
    cout << endl;
  }
  delete row;
  cout << " ----------------------------- " << endl;
  cout << " -- Closing Connection " << endl;
  rcdb->Close();
  fclose(runlist);
  delete res;
  delete rcdb;
}
