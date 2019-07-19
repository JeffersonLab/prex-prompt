void GetBeamNoise(Int_t run_num,TString suffix){

  TString output_filename = Form("./summary/run%d/run%d_postpan_summary.txt",run_num,run_num);
  FILE *summary_txt = fopen(output_filename.Data(), "w");

  TFile* rootfile = TFile::Open(Form("./japanOutput/prexRespin2_%d_regress_%s.root",run_num,suffix.Data() ));
  TTree *reg = (TTree*)rootfile ->Get("reg");
  TTree *regcoeffs = (TTree*)rootfile ->Get("regcoeffs");
  
  Double_t to_ppm = 1e6;
  Double_t mm_to_micron = 1e3;

  reg->SetAlias("Aq","asym_bcm_an_ds3");

  TString IVname[] = {
    "diff_bpm4aX","diff_bpm4aY","diff_bpm4eX","diff_bpm4eY","diff_bpm14X"};

  TString DVname[] = { 
    "asym_sam2","asym_sam4","asym_sam6","asym_sam8","asym_bcm_an_ds3","asym_bcm_an_us"};

  Int_t nIV = sizeof(IVname)/sizeof(*IVname);
  Int_t nDV = sizeof(DVname)/sizeof(*DVname);
  Int_t nCoeffs = nIV *nDV;

  Double_t *IVrms = new Double_t [nIV] ;  
  Double_t *DVrms_raw = new Double_t[nDV];
  Double_t *DVrms_reg = new Double_t[nDV];

  Double_t *DVmean_raw = new Double_t[nDV];
  Double_t *DVmean_reg = new Double_t[nDV];

  Double_t *DVrms_norm = new Double_t[nDV];

  Double_t *Coeff = new Double_t[nDV*nIV]; // postpan output
  Double_t *CoeffError = new Double_t[nDV*nIV]; // postpan output
  Double_t *Slope = new Double_t[nDV*nIV]; // converted to ppm/um
  Double_t *SlopeError = new Double_t[nDV*nIV]; // converted to ppm/um

  Double_t *Noise = new Double_t[nDV*nIV]; // in ppm
  Double_t *CoherentNoise = new Double_t[nDV]; // in ppm


  regcoeffs->SetBranchAddress("coeff",Coeff);
  regcoeffs->SetBranchAddress("err_coeff",CoeffError);
  Int_t nMinirun =regcoeffs->GetEntries();
  for(int kMinirun=0; kMinirun<nMinirun;kMinirun++){
    TString my_cut =Form("ok_cut && minirun==%d",kMinirun); 

    for(int kDV=0; kDV<nDV; kDV++){
      reg->Draw(Form("%s >> dv%d%d_raw", DVname[kDV].Data(),kDV,kMinirun), my_cut,"goff");
      TH1D *hraw_buff = (TH1D*)gDirectory->FindObject(Form("dv%d%d_raw",kDV,kMinirun));
      DVrms_raw[kDV] =(hraw_buff->GetRMS() ) * to_ppm;
      DVmean_raw[kDV] =(hraw_buff->GetMean() ) * to_ppm;

      reg->Draw(Form("reg_%s >> dv%d%d_reg", DVname[kDV].Data(),kDV,kMinirun), my_cut,"goff");
      TH1D *hreg_buff = (TH1D*)gDirectory->FindObject(Form("dv%d%d_reg",kDV,kMinirun));
      DVrms_reg[kDV] =(hreg_buff->GetRMS() ) * to_ppm;
      DVmean_reg[kDV] =(hreg_buff->GetMean() ) * to_ppm;

      reg->Draw(Form("reg_%s - Aq >> dv%d%d_norm", DVname[kDV].Data(),kDV,kMinirun), my_cut,"goff");
      TH1D *hnorm_buff = (TH1D*)gDirectory->FindObject(Form("dv%d%d_norm",kDV,kMinirun));
      DVrms_norm[kDV] =(hnorm_buff->GetRMS() ) * to_ppm;
    }

    for(int kIV=0; kIV<nIV; kIV++){
      reg->Draw(Form("%s >> iv%d%d", IVname[kIV].Data(),kIV,kMinirun), my_cut,"goff");
      TH1D *h_buff = (TH1D*)gDirectory->FindObject(Form("iv%d%d",kIV,kMinirun));
      IVrms[kIV] =(h_buff->GetRMS() ) * mm_to_micron;
    }


    regcoeffs->GetEntry(kMinirun);
    for(int kDV=0;kDV<nDV;kDV++){
      for(int kIV=0;kIV<nIV;kIV++){
	Slope[ kDV* nIV + kIV] =  Coeff[ kDV* nIV + kIV] * to_ppm/mm_to_micron;
	SlopeError[ kDV* nIV + kIV] =  CoeffError[ kDV* nIV + kIV] * to_ppm/mm_to_micron;
	Noise[ kDV* nIV + kIV] = Slope[kDV*nIV + kIV] * IVrms[kIV];
      }
    }
  
    for(int kDV=0;kDV<nDV;kDV++){
      TString formula = "0";
      for(int kIV=0;kIV<nIV;kIV++){
	formula += Form("+ %lf * %s ", Slope[kDV*nIV +kIV]*mm_to_micron, IVname[kIV].Data());
      }
      reg->Draw(Form("%s >> coherentNoise%d",formula.Data(),kDV),my_cut,"goff");
      TH1D *h_buff = (TH1D*)gDirectory->FindObject(Form("coherentNoise%d",kDV));
      CoherentNoise[kDV] = h_buff->GetRMS();
    }

    
    fprintf(summary_txt, " == Mini-run: %d == \n", kMinirun);
    
    fprintf(summary_txt, 
	    "%-12s\t%-12s\t%-12s\t%-20s\t%-15s\t%-15s\t%-12s\n",
	    "",
	    "Raw Mean(ppm)","RMS(ppm)",
	    "Regressed Mean(ppm)","RMS (ppm)", 
	    "Correction on Mean(ppm)","RMS of BPM Coherent Sum(ppm)");

    for(int kDV=0;kDV<nDV;kDV++){
      fprintf(summary_txt, 
	      "%-12s\t%-12.2f\t%-12.2f\t%-20.2f\t%-17.2f%-15.2f\t%-12.2f\n",
	      DVname[kDV].Data(), 
	      DVmean_raw[kDV],DVrms_raw[kDV], 
	      DVmean_reg[kDV],DVrms_reg[kDV], 
	      DVmean_raw[kDV]-DVmean_reg[kDV],CoherentNoise[kDV]);
    }


    fprintf(summary_txt, " \n --IV RMS (um): \n" );
    for(int kIV=0; kIV<nIV; kIV++)
      fprintf(summary_txt,"%-15s \t", IVname[kIV].Data());
    fprintf(summary_txt," \n");

    for(int kIV=0; kIV<nIV; kIV++)
      fprintf(summary_txt,"%-15.2f \t", IVrms[kIV]);
    fprintf(summary_txt," \n");

    fprintf(summary_txt, " \n --Slope (ppm/um): \n");
    fprintf(summary_txt, " %-15s\t ","" );
    for(int kIV=0; kIV<nIV; kIV++)
      fprintf(summary_txt,"%-15s \t", IVname[kIV].Data());
    fprintf(summary_txt," \n");

    for(int kDV=0;kDV<nDV;kDV++){
      fprintf(summary_txt,"%-15s \t", DVname[kDV].Data());
      for(int kIV=0;kIV<nIV;kIV++)
	fprintf(summary_txt,"%-.2f +/- %-9.2f\t", Slope[kDV*nIV + kIV],SlopeError[kDV*nIV+kIV]);
      fprintf(summary_txt," \n");
    }

    fprintf(summary_txt, "\n --Noise (ppm): \n");
    fprintf(summary_txt, " %-15s\t ","" );
    for(int kIV=0; kIV<nIV; kIV++)
      fprintf(summary_txt,"%-15s \t", IVname[kIV].Data());
    fprintf(summary_txt," \n");

    for(int kDV=0;kDV<nDV;kDV++){
      fprintf(summary_txt,"%-15s \t", DVname[kDV].Data());
      for(int kIV=0;kIV<nIV;kIV++)
	fprintf(summary_txt,"%-15.2f \t", Noise[kDV*nIV + kIV]);
      fprintf(summary_txt," \n");
    }
  }
  fclose(summary_txt);
}
