#include <TFile.h>
#include <TH1F.h>
void Plot_GEMXY_Output(){

  TGaxis::SetMaxDigits(3);
  
	TFile *f = new TFile("../RootFiles/rPhi_residual_PostionLC1_Ite0__R1593_inclusive_doubleGaussian.root"); 
	f->ls();

	TCanvas *c1 = new TCanvas("c1","");

	TH1F *h1 = new TH1F("h1","",100,-1,1);
	h1 = (TH1F*)f->Get("residualREF1_r"); 
	h1->Draw(); 
	c1->SaveAs("test.pdf");
}
