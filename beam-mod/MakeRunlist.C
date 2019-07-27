void MakeRunlist(int slug_number){

  // Experimenting Function to Get slug number based on run number 
  // Author : Tao Ye

  TSQLResult* res;
  TSQLRow *row;
  cout << " -- Getting Slug Number from RCDB -- " << endl;
  cout << " -- Connecting to RCDB -- " << endl;
  TSQLServer *rcdb = TSQLServer::Connect("mysql://hallcdb.jlab.org:3306/a-rcdb","rcdb","");
  cout << " -- ServerInfo: " << rcdb->ServerInfo() << endl;
  cout << " -- Host : " << rcdb->GetHost() << endl;
  cout << " -- Query DataBase " << endl;
  TString select_q ="SELECT name,int_value,run_number "; 
  TString from_q =  "FROM `a-rcdb`.conditions,`a-rcdb`.condition_types ";
  TString where_q = Form("WHERE conditions.condition_type_id=condition_types.id "
			 "and (name='slug' and int_value='%d')",
			 slug_number);
  vector<Int_t> run_list;
  res = rcdb->Query(select_q + from_q + where_q);
  if(res==NULL){
    cout << " -- Failed to Query " << endl;
    cout << " -- Bye-bye! " << endl;
    cout << " -- Closing Connection to RCDB " << endl;
    rcdb->Close();
    delete res;
    delete row;
    delete rcdb;
    return;
  }

  int nFields =res->GetFieldCount();
  int nRows =res->GetRowCount();
  if(nRows==0){
    cout << " -- Failed to load slug list " << endl;
    cout << " -- Bye-bye! " << endl;
    delete row;
    delete res;
    cout << " -- Closing Connection " << endl;
    rcdb->Close();
    delete rcdb;
    return;
  }
  cout << " ----------------------------- " << endl;
  for(int i=0; i< nRows; i++){
    row = res->Next();
    for(int j=0; j< nFields; j++){
      cout << "\t" << row->GetField(j) ;
    }
    TString run_str= TString(row->GetField(2));
    run_list.push_back(run_str.Atoi());
    cout << endl;
    delete row;
  }
  
  // int  = TString(runNumber_char).Atoi();
  cout << " ----------------------------- " << endl;
  cout << " -- Closing Connection " << endl;
  rcdb->Close();
  delete res;
  delete rcdb;

  vector<int>::iterator itr = run_list.begin();
  while(itr!= run_list.end()){
    cout << *itr<< endl;
    itr++;
  }
}
