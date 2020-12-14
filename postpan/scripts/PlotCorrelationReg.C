#include <vector>
void PlotCorrelationReg(Int_t run_num){

  TFile* rootfile = TFile::Open(Form("../ROOTfiles/parity18_%d_regress.root",run_num));
  TTree *reg = (TTree*)rootfile ->Get("reg");

  // iv : independent variabls
  // dv : dependent variabls
  
  TString iv_name[]={"4aX","4aY","4eX","4eY","12X","12Y","10X","10Y"};
  TString dv_name[]={"sam2","sam3","sam4","sam5","sam6","sam7","sam8"};
  TString cuts = "ok_cut";

  Int_t ndvs= sizeof(dv_name)/sizeof(*dv_name);
  Int_t nivs= sizeof(iv_name)/sizeof(*iv_name);
  
  vector<double> iv_mean;
  vector<double> iv_rms;
  vector<double> dv_mean;
  vector<double> dv_rms;

  for(int i=0;i<ndvs;i++){
    reg->Draw(Form("1e6*reg_asym_%s-1e6*asym_bcm_an_ds3>>hdv%d",dv_name[i].Data(),i),cuts);
    TH1D *hbuff = (TH1D*)gDirectory->FindObject(Form("hdv%d",i));
    dv_mean.push_back( hbuff->GetMean());
    dv_rms.push_back( 3*(hbuff->GetRMS()) );
  }
  for(int i=0;i<nivs;i++){
    reg->Draw(Form("diff_bpm%s>>hiv%d",iv_name[i].Data(),i),cuts);
    TH1D *hbuff = (TH1D*)gDirectory->FindObject(Form("hiv%d",i));
    iv_mean.push_back( hbuff->GetMean());
    iv_rms.push_back(3*( hbuff->GetRMS()));
  }

  vector<TText * > dv_txt;
  vector<TText * > iv_txt;
  for(int i=0;i<ndvs;i++){
    TText *txt = new TText(0.1,0.3, dv_name[i]);
    txt->SetTextSize(0.3);
    dv_txt.push_back(txt);
  }

  for(int i=0;i<nivs;i++){
    TText *txt = new TText(0.3,0.3, iv_name[i]);
    txt->SetTextSize(0.3);
    iv_txt.push_back(txt);
  }

  TCanvas *c1  = new TCanvas("c1","c1",900,900);
  c1->Divide(nivs+1,ndvs+1); // columns : iv , row : dv

  for(int icol =0 ; icol<nivs ;icol++){
    c1->cd( icol+2);
    iv_txt[icol]->Draw();
  }

  for(int irow =0 ; irow<ndvs ;irow++){
    c1->cd( (irow+1)*(nivs+1)+1 );
    dv_txt[irow]->Draw();
  }

  for(int irow=0;irow<ndvs; irow++){
    for(int icol=0; icol< nivs; icol++){
      
      c1->cd( (irow+1) * (nivs+1) + icol +2);
      double x_low = iv_mean[icol]-iv_rms[icol];
      double x_up = iv_mean[icol]+iv_rms[icol];
      double y_low = dv_mean[irow]-dv_rms[irow];
      double y_up = dv_mean[irow]+dv_rms[irow];

      reg->Draw(
		Form("1e6*reg_asym_%s-1e6*asym_bcm_an_ds3:diff_bpm%s>>h%d_%d(50,%f,%f,50,%f,%f)", 
		     dv_name[irow].Data(),iv_name[icol].Data(), 
		     icol,irow,x_low,x_up,y_low,y_up ),
		cuts,"COLZ");
    }
  }
  


}
