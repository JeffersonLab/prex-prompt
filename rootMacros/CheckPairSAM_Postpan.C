void CheckPairSAM(Int_t run_num,TString suffix){

  TString output_dir = Form("./summary_respin/run%d/",run_num);

  TFile* rootfile = TFile::Open(Form("./japanOutput/prexRespin2_%d_regress_%s.root",run_num,suffix.Data()));
  TTree *tree = (TTree*)rootfile ->Get("reg");

  tree->SetAlias("reg_A2", "1e6*reg_asym_sam2");
  tree->SetAlias("reg_A6", "1e6*reg_asym_sam6");
  tree->SetAlias("reg_A4", "1e6*reg_asym_sam4");
  tree->SetAlias("reg_A8", "1e6*reg_asym_sam8");
  tree->SetAlias("AqDS", "1e6*asym_bcm_an_ds");
  tree->SetAlias("AqUS", "1e6*asym_bcm_an_us");
  TString user_cut ="ok_cut";  
  TString filename;
  TText *label;
  TCanvas *c0 = new TCanvas("c0","c0",2400,1200);
  c0->Divide(4,2);
  c0->cd(1);
  tree->Draw("reg_A2:AqDS","ok_cut");
  c0->cd(2);
  tree->Draw("reg_A6:AqDS","ok_cut");
  c0->cd(3);
  tree->Draw("reg_A4:AqDS","ok_cut");
  c0->cd(4);
  tree->Draw("reg_A8:AqDS","ok_cut");

  gStyle->SetOptStat(0);
  gStyle->SetOptFit(1);

  c0->cd(5);

  TH1 *hfit;
  Double_t low, up;


  tree->Draw("reg_A2:AqDS>>ha2","ok_cut","prof");
  hfit = (TH2D*)gDirectory->FindObject("ha2");
  low = hfit->GetMean()-2*hfit->GetRMS();
  up = hfit->GetMean()+2*hfit->GetRMS();
  hfit->Fit("pol1","QR","",low,up);

  c0->cd(6);
  tree->Draw("reg_A6:AqDS>>ha6","ok_cut","prof");
  hfit = (TH2D*)gDirectory->FindObject("ha6");
  low = hfit->GetMean()-2*hfit->GetRMS();
  up = hfit->GetMean()+2*hfit->GetRMS();
  hfit->Fit("pol1","QR","",low,up);

  c0->cd(7);
  tree->Draw("reg_A4:AqDS>>ha4","ok_cut","prof");
  hfit = (TH2D*)gDirectory->FindObject("ha4");
  low = hfit->GetMean()-2*hfit->GetRMS();
  up = hfit->GetMean()+2*hfit->GetRMS();
  hfit->Fit("pol1","QR","",low,up);

  c0->cd(8);
  tree->Draw("reg_A8:AqDS>>ha8","ok_cut","prof");
  hfit = (TH2D*)gDirectory->FindObject("ha8");
  low = hfit->GetMean()-2*hfit->GetRMS();
  up = hfit->GetMean()+2*hfit->GetRMS();
  hfit->Fit("pol1","QR","",low,up);
  
  filename = Form("run%d_paired_sam_AqDS_%s.png",run_num,suffix.Data());
  label = new TText(0.0,0.01,filename);     
  label->SetTextSize(0.03);
  label->SetNDC();
  c0->cd();
  label->Draw("same");
  c0->SaveAs(output_dir+filename);

  // Reg SAM vs Aq US

  c0->Clear("D");
  c0->cd(1);
  tree->Draw("reg_A2:AqUS","ok_cut");
  c0->cd(2);
  tree->Draw("reg_A6:AqUS","ok_cut");
  c0->cd(3);
  tree->Draw("reg_A4:AqUS","ok_cut");
  c0->cd(4);
  tree->Draw("reg_A8:AqUS","ok_cut");

  c0->cd(5);
  tree->Draw("reg_A2:AqUS>>haref2","ok_cut","prof");
  hfit = (TH2D*)gDirectory->FindObject("haref2");
  low = hfit->GetMean()-2*hfit->GetRMS();
  up = hfit->GetMean()+2*hfit->GetRMS();
  hfit->Fit("pol1","QR","",low,up);

  c0->cd(6);
  tree->Draw("reg_A6:AqUS>>haref6","ok_cut","prof");
  hfit = (TH2D*)gDirectory->FindObject("haref6");
  low = hfit->GetMean()-2*hfit->GetRMS();
  up = hfit->GetMean()+2*hfit->GetRMS();
  hfit->Fit("pol1","QR","",low,up);

  c0->cd(7);
  tree->Draw("reg_A4:AqUS>>haref4","ok_cut","prof");
  hfit = (TH2D*)gDirectory->FindObject("haref4");
  low = hfit->GetMean()-2*hfit->GetRMS();
  up = hfit->GetMean()+2*hfit->GetRMS();
  hfit->Fit("pol1","QR","",low,up);

  c0->cd(8);
  tree->Draw("reg_A8:AqUS>>haref8","ok_cut","prof");
  hfit = (TH2D*)gDirectory->FindObject("haref8");
  low = hfit->GetMean()-2*hfit->GetRMS();
  up = hfit->GetMean()+2*hfit->GetRMS();
  hfit->Fit("pol1","QR","",low,up);
  
  filename = Form("run%d_paired_sam_AqUS_%s.png",run_num,suffix.Data());
  label = new TText(0.0,0.01,filename);     
  label->SetTextSize(0.03);
  label->SetNDC();
  c0->cd();
  label->Draw("same");
  c0->SaveAs(output_dir+filename);

  gStyle->SetOptStat(1);
  gStyle->SetOptFit(1);
  gStyle->SetStatW(0.3);
  gStyle->SetStatH(0.25);
  gStyle->SetStatX(0.95);
  gStyle->SetStatY(0.95);

  TCanvas *c1 = new TCanvas("c1","c1",1600,900);
  c1->Divide(3,2);

  c1->cd(1);
  tree->Draw("reg_A4","ok_cut");
  c1->cd(2);
  tree->Draw("reg_A8","ok_cut");
  c1->cd(3);
  tree->Draw("reg_A4 : reg_A8","ok_cut");
  c1->cd(4);
  tree->Draw("reg_A4 : reg_A8","ok_cut","prof");
  c1->cd(5);
  tree->Draw("reg_A4-reg_A8","ok_cut");
  c1->cd(6);
  tree->Draw("(reg_A4+reg_A8)","ok_cut");

  filename = Form("run%d_paired_sam_48_%s.png",run_num,suffix.Data());
  label = new TText(0.0,0.01,filename);     
  label->SetTextSize(0.03);
  label->SetNDC();
  c1->cd();
  label->Draw("same");
  c1->SaveAs(output_dir+filename);

  TCanvas *c2 = new TCanvas("c2","c2",1600,900);
  c2->Divide(3,2);

  c2->cd(1);
  tree->Draw("reg_A2","ok_cut");
  c2->cd(2);
  tree->Draw("reg_A6","ok_cut");
  c2->cd(3);
  tree->Draw("reg_A2 : reg_A6","ok_cut");
  c2->cd(4);
  tree->Draw("reg_A2 : reg_A6","ok_cut","prof");
  c2->cd(5);
  tree->Draw("reg_A2-reg_A6","ok_cut");
  c2->cd(6);
  tree->Draw("(reg_A2+reg_A6)","ok_cut");

  filename = Form("run%d_paired_sam_26_%s.png",run_num,suffix.Data());
  label = new TText(0.0,0.01,filename);     
  label->SetTextSize(0.03);
  label->SetNDC();
  c2->cd();
  label->Draw("same");
  c2->SaveAs(output_dir+filename);

  TCanvas *c4 = new TCanvas("c4","c4",900,900);
  c4->Divide(2,2);
  c4->cd(1);
  tree->Draw("(reg_A2+reg_A6)/2 ","ok_cut");
  c4->cd(2);
  tree->Draw("(reg_A4+reg_A8)/2","ok_cut");
  c4->cd(3);
  tree->Draw("(reg_A2+reg_A6)/2 : (reg_A4+reg_A8)/2 ","ok_cut");
  c4->cd(4);
  tree->Draw("(reg_A2+reg_A6)/2 - (reg_A4+reg_A8)/2 ","ok_cut");

  filename = Form("run%d_paired_sam_dd_%s.png",run_num,suffix.Data());
  label = new TText(0.0,0.01,filename);     
  label->SetTextSize(0.03);
  label->SetNDC();
  c4->cd();
  label->Draw("same");
  c4->SaveAs(output_dir+filename);

  gSystem->Exec(Form("convert %s/*paired_sam*.png %s/run%d_paired_sam_postpan.pdf",
		     output_dir.Data(),
		     output_dir.Data(),run_num));
  gSystem->Exec(Form("rm %s/*paired_sam*.png ",output_dir.Data()));
}

