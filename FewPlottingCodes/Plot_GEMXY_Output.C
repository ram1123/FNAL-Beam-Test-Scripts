#include <TFile.h>
#include <TH1F.h>
void Plot_GEMXY_Output(){

  TGaxis::SetMaxDigits(3);
  
	//TFile *f = new TFile("/home/ramkrishna/PhD_New_Dir_16July2016/GEM/GEM_TB/TB_2014/Temp_PPT/plots/rPhi_residual_PostionLC1_Ite0__R1892_inclusive_doubleGaussian.root"); 
	TFile *f = new TFile("../RootFiles/rPhi_residual_PostionLC1_Ite99__R1644_inclusive_doubleGaussian.root"); 
	f->ls();

	TCanvas *c1 = new TCanvas("c1","");

	TH1F *h1 = new TH1F("h1","",100,-1,1);
	h1 = (TH1F*)f->Get("residualEta5_phi"); 
	h1->Draw(); 
	c1->SaveAs("test.pdf");
}
