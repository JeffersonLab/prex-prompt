  // Function to Get Run list 
  // Author : Tao Ye
void GetProductionRunList();
Int_t ParseSlugNumber(TString);
void GenSlugList();

void UpdateSlugList(){
  GetProductionRunList();
  GenSlugList();
}

void GenSlugList(){
  
  ifstream info_file;
  info_file.open("all_production.list");
  
  TString sline;
  Int_t cur_slug=-1;

  Bool_t is_file_open = kFALSE;
  vector< vector<TString> > fSlugArray(95);
  while(sline.ReadLine(info_file)){
    Int_t my_slug = ParseSlugNumber(sline);
    fSlugArray[my_slug].push_back(sline);
  }

  for(int i=0;i<=94;i++){
    TString new_filename = Form("slug%d_info.list",i);
    FILE* output;
    output=fopen(new_filename.Data(),"w");
    auto iter=(fSlugArray[i]).begin();
    while(iter!=fSlugArray[i].end()){
      fprintf(output,"%s\n",(*iter).Data());
      iter++;
    }
    fclose(output);
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

void GetProductionRunList(){

  TSQLResult* res;
  TSQLRow *row;
  cout << " -- Getting Slug Number from RCDB -- " << endl;
  cout << " -- Connecting to RCDB -- " << endl;
  TSQLServer *rcdb = TSQLServer::Connect("mysql://hallcdb.jlab.org:3306/a-rcdb","rcdb","");
  cout << " -- ServerInfo: " << rcdb->ServerInfo() << endl;
  cout << " -- Host : " << rcdb->GetHost() << endl;
  cout << " -- Query DataBase " << endl;

 TString query[]={"SELECT t1.run_number,t3.int_value, t7.text_value,CASE WHEN tflag.text_value is NULL THEN 'NoFlag' ELSE tflag.text_value END AS flag_res, t1.text_value, t2.text_value,t6.int_value ",
  		   " FROM `a-rcdb`.conditions as t1 INNER JOIN `a-rcdb`.condition_types c1 on c1.id= t1.condition_type_id AND c1.name='ihwp' ",
  		   ", `a-rcdb`.conditions as t2 INNER JOIN `a-rcdb`.condition_types c2 on c2.id=t2.condition_type_id AND c2.name='flip_state' ",
  		   ", `a-rcdb`.conditions as t3 INNER JOIN `a-rcdb`.condition_types c3 on c3.id=t3.condition_type_id AND c3.name='slug' AND t3.int_value BETWEEN 0 AND 94 ",
  		   ", `a-rcdb`.conditions as t4 INNER JOIN `a-rcdb`.condition_types c4 on c4.id=t4.condition_type_id AND c4.name='run_type' AND t4.text_value='Production' ",
  		   " LEFT JOIN ",
		   "( SELECT run_number, text_value ",
		   " FROM `a-rcdb`.conditions t5 INNER JOIN `a-rcdb`.condition_types c5 on c5.id=t5.condition_type_id AND c5.name='run_flag' ) AS tflag ",
		   " ON tflag.run_number = t4.run_number ",
  		   ", `a-rcdb`.conditions as t6 INNER JOIN `a-rcdb`.condition_types c6 on c6.id=t6.condition_type_id AND c6.name='arm_flag' ",
		  ", `a-rcdb`.conditions as t7 INNER JOIN `a-rcdb`.condition_types c7 on c7.id=t7.condition_type_id AND c7.name='run_config' ",
  		   " WHERE t1.run_number=t3.run_number AND t1.run_number=t2.run_number AND t1.run_number=t4.run_number AND t1.run_number=t6.run_number AND t1.run_number=t7.run_number AND t1.run_number<4981",
		   " ORDER BY t1.run_number ASC"};

 TString listName = "all_production.list";
  
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
