#include <TFile.h>
#include <TH1.h>
//void Plot_GEMXY_Output(TString InputRootFile){
void Plot_GEMXY_Output(){

  TGaxis::SetMaxDigits(3);
  
//gStyle->SetOptStat(111);
//gStyle->SetOptFit(0);
	int n=0;
	int m=n+1;
	//TFile *f = new TFile(Form("Residual_Rot_Trk_RootFile/RotationBack_Residual_Position_iter%i_exclusive_R411.root",n)); 
	//TFile *f = new TFile(Form("Residual_XY_Trk_RootFile/Residual_Position_iter_%i_R411.root",n)); 
	TFile *f = new TFile("RootFiles/rPhi_residual_PostionLC1_X_-2549.00_Y_0.00_R1613_inclusive_doubleGaussian.root"); 

	TCanvas *c1 = new TCanvas("c1","");
	TCanvas *c2 = new TCanvas("c2","");
	c1->Divide(3,2);

	c1->cd(1);
	TH1F * h1 = (TH1F*)f->Get("residualREF1_r_X_-2549.0_Y_0.0"); 
//	h1->GetXaxis()->SetRangeUser(-0.5,0.5);
	h1->Draw(); 

	c1->cd(4);
	TH1F * h2 = (TH1F*)f->Get("residualREF1_phi_X_-2549.0_Y_0.0"); 
//	h2->GetXaxis()->SetRangeUser(-0.5,0.5);
	h2->Draw(); 

	c1->cd(2);
	TH1F * h3 = (TH1F*)f->Get("residualREF2_r_X_-2549.0_Y_0.0");
//	h3->GetXaxis()->SetRangeUser(-0.5,0.5);
	h3->Draw(); 

	c1->cd(5);
	TH1F * h4 = (TH1F*)f->Get("residualREF2_phi_X_-2549.0_Y_0.0"); 
//	h4->GetXaxis()->SetRangeUser(-0.5,0.5);
	h4->Draw(); 

	c1->cd(3);
	TH1F * h6 = (TH1F*)f->Get("residualREF3_r_X_-2549.0_Y_0.0"); 
//	h6->GetXaxis()->SetRangeUser(-0.5,0.5);
	h6->Draw(); 

	c1->cd(6);
	TH1F * h5 = (TH1F*)f->Get("residualREF3_phi_X_-2549.0_Y_0.0"); 
//	h5->GetXaxis()->SetRangeUser(-0.5,0.5);
	h5->Draw(); 

	c1->SaveAs("rPhi_residual_PostionLC1_TrkOnly.pdf");

	c2->cd();
	TH1F * h7 = (TH1F*)f->Get("residualEta5_phi_X_-2549.0_Y_0.0"); 
//	h5->GetXaxis()->SetRangeUser(-0.5,0.5);
	h7->Draw(); 
	c2->SaveAs("rPhi_residual_PostionLC1_GE11.pdf");
//	c1-> Clear();
//	h6->Draw(); 

}
