void CheckPairSAM(Int_t run_num=1391){
  TFile* rootfile = TFile::Open(Form("./ROOTfiles/prexRespin1_%d_regress.root",run_num));
  TTree *tree = (TTree*)rootfile ->Get("reg");

  tree->SetAlias("reg_A2", "1e6*reg_asym_sam2");
  tree->SetAlias("reg_A6", "1e6*reg_asym_sam6");
  tree->SetAlias("reg_A4", "1e6*reg_asym_sam4");
  tree->SetAlias("reg_A8", "1e6*reg_asym_sam8");
  tree->SetAlias("Aq", "1e6*asym_bcm_an_ds3");

  TString user_cut ="ok_cut";  

  TCanvas *c0 = new TCanvas("c0","c0",1600,900);
  c0->Divide(4,2);
  c0->cd(1);
  tree->Draw("reg_A2:Aq","ok_cut");
  c0->cd(2);
  tree->Draw("reg_A6:Aq","ok_cut");
  c0->cd(3);
  tree->Draw("reg_A4:Aq","ok_cut");
  c0->cd(4);
  tree->Draw("reg_A8:Aq","ok_cut");

  gStyle->SetOptStat(0);
  gStyle->SetOptFit(1);

  c0->cd(5);
  tree->Draw("reg_A2:Aq>>ha2","ok_cut","prof");
  ha2->Fit("pol1","Q");
  c0->cd(6);
  tree->Draw("reg_A6:Aq>>ha6","ok_cut","prof");
  ha6->Fit("pol1","Q");
  c0->cd(7);
  tree->Draw("reg_A4:Aq>>ha4","ok_cut","prof");
  ha4->Fit("pol1","Q");
  c0->cd(8);
  tree->Draw("reg_A8:Aq>>ha8","ok_cut","prof");
  ha8->Fit("pol1","Q");

  c0->SaveAs(Form("run%d_paired_sam_Aq.png",run_num));

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

  c1->SaveAs(Form("run%d_paired_sam_48.png",run_num));

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

  c2->SaveAs(Form("run%d_paired_sam_26.png",run_num));

  // TCanvas *c3 = new TCanvas("c3","c3",1500,900);
  // c3->Divide(3,2);
  // c3->cd(1);
  // tree->Draw("(reg_A2+reg_A6)/2","ok_cut");
  // c3->cd(2);
  // tree->Draw("(reg_A4+reg_A8)/2","ok_cut");
  // c3->cd(3);
  // tree->Draw("(reg_A4+reg_A8)/2 : (reg_A2+reg_A6)/2","ok_cut");


  // c2->SaveAs(Form("run%d_paired_sam_26.png",run_num));

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

  c4->SaveAs(Form("run%d_paired_sam_doublediff.png",run_num));

  gSystem->Exec(Form("convert *paired_sam*.png run%d_paired_sam.pdf",run_num));
  gSystem->Exec("rm *paired_sam*.png ");
}
