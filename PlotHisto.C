#include <TFile.h>
#include <TH1.h>
void PlotHisto(){

	int n=0;
	int m=n+1;
	TFile *f = new TFile(Form("Residual_Rot_Trk_RootFile/RotationBack_Residual_Position_iter%i_exclusive_R411.root",n)); 
	//TFile *f = new TFile(Form("Residual_XY_Trk_RootFile/Residual_Position_iter_%i_R411.root",n)); 

	TCanvas *c1 = new TCanvas("c1","");
	c1->Divide(3,2);

	c1->cd(1);
	TH1F * h1 = (TH1F*)f->Get(Form("posg1xcl_%i",m)); 
//	h1->GetXaxis()->SetRangeUser(-0.5,0.5);
	h1->Draw(); 

	c1->cd(4);
	TH1F * h2 = (TH1F*)f->Get(Form("posg1ycl_%i",m)); 
//	h2->GetXaxis()->SetRangeUser(-0.5,0.5);
	h2->Draw(); 

	c1->cd(2);
	TH1F * h3 = (TH1F*)f->Get(Form("posg2xcl_%i",m)); 
//	h3->GetXaxis()->SetRangeUser(-0.5,0.5);
	h3->Draw(); 

	c1->cd(5);
	TH1F * h4 = (TH1F*)f->Get(Form("posg2ycl_%i",m)); 
//	h4->GetXaxis()->SetRangeUser(-0.5,0.5);
	h4->Draw(); 

	c1->cd(3);
	TH1F * h6 = (TH1F*)f->Get(Form("posg3xcl_%i",m)); 
//	h6->GetXaxis()->SetRangeUser(-0.5,0.5);
	h6->Draw(); 

	c1->cd(6);
	TH1F * h5 = (TH1F*)f->Get(Form("posg3ycl_%i",m)); 
//	h5->GetXaxis()->SetRangeUser(-0.5,0.5);
	h5->Draw(); 

	c1->SaveAs(Form("RotationBack_Residual_Position_iter%i_exclusive_R411.pdf",n));

//	c1-> Clear();
//	h6->Draw(); 

}
