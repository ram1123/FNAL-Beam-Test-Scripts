/*

 * =====================================================================================
 *
 *       Filename:  Plot_residual.C
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Friday 25 September 2015 11:40:44  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ramkrishna Sharma (Ram), ramkrishna.sharma71@gmail.com
 *   Organization:  CERN
 *
 * =====================================================================================
 */

#include <iostream>
#include "TGraphErrors.h"
#include "TGraph.h"
#include "TCanvas.h"
//#include "tdrstyle.C"
#include "setTDRStyle.C"
#include "CMS_lumi.C"

void Plot_residual()
{
    setTDRStyle();

    writeExtraText = true;       // if extra text
    extraText  = "Preliminary";  // default extra text is "Preliminary"
    //lumi_8TeV  = "19.1 fb^{-1}"; // default is "19.7 fb^{-1}"
    //lumi_7TeV  = "4.9 fb^{-1}";  // default is "5.1 fb^{-1}"
    //lumi_sqrtS = "13 TeV";       // used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)
    
    int iPeriod = 0;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV, 0=free form (uses lumi_sqrtS)

    ifstream residualFile;
    //residualFile.open("../residual_txtFile/residuals_Position_alignTrackers_R1644.txt");
    //residualFile.open("../mean_txtFile/mean_Position_alignTrackers_R1644.txt");
    residualFile.open("../residual_txtFile/RotationBack_residuals_Position_inclusive_1644.txt");

    vector<double> Res_g1x, Res_g1y, Res_g2x, Res_g2y, Res_g3x, Res_g3y;

    int iteNum;
    double g1xres, g1yres, g2xres, g2yres, g3xres, g3yres;
    while(1)
    {
	residualFile>> iteNum >> g1xres >> g1yres >> g2xres >> g2yres >> g3xres >> g3yres;

	if (!residualFile.good()) break;

	Res_g1x.push_back(g1xres);	Res_g1y.push_back(g1yres);
	Res_g2x.push_back(g2xres);	Res_g2y.push_back(g2yres);
	Res_g3x.push_back(g3xres);	Res_g3y.push_back(g3yres);
    }
    residualFile.close();


    TCanvas *c1 = new TCanvas("c1","c1",1);

    TGraphErrors *gr1 = new TGraphErrors(Res_g1x.size());
    TGraphErrors *gr2 = new TGraphErrors(Res_g1x.size());
    TGraphErrors *gr3 = new TGraphErrors(Res_g1x.size());
    TGraphErrors *gr4 = new TGraphErrors(Res_g1x.size());
    TGraphErrors *gr5 = new TGraphErrors(Res_g1x.size());
    TGraphErrors *gr6 = new TGraphErrors(Res_g1x.size());

    for(int i=0; i<Res_g1x.size(); i++)
    {
	gr1->SetPoint(i,i,Res_g1x[i]);
	gr2->SetPoint(i,i,Res_g1y[i]);
	gr3->SetPoint(i,i,Res_g2x[i]);
	gr4->SetPoint(i,i,Res_g2y[i]);
	gr5->SetPoint(i,i,Res_g3x[i]);
	gr6->SetPoint(i,i,Res_g3y[i]);
    }
    
    gr1->GetYaxis()->SetRangeUser(-0.5,0.50);
    //gr1->GetYaxis()->SetRangeUser(-0.02,0.02);

    //gr1->GetXaxis()->SetRangeUser(0,62);
    gr1->SetTitle("");
    gr1->GetXaxis()->SetTitle("Iteration Number");
    gr1->GetYaxis()->SetTitle("Residual Sigma (mm)");
    //gr1->GetYaxis()->SetTitle("Residual mean (mm)");


    gr1->SetMarkerColor(1);
    gr2->SetMarkerColor(2);
    gr3->SetMarkerColor(3);
    gr4->SetMarkerColor(4);
    gr5->SetMarkerColor(7);
    gr6->SetMarkerColor(6);

    gr1->SetLineColor(1);
    gr2->SetLineColor(2);
    gr3->SetLineColor(3);
    gr4->SetLineColor(4);
    gr5->SetLineColor(7);
    gr6->SetLineColor(6);

    gr1->SetMarkerStyle(20);
    gr2->SetMarkerStyle(24);
    gr3->SetMarkerStyle(21);
    gr4->SetMarkerStyle(25);
    gr5->SetMarkerStyle(22);
    gr6->SetMarkerStyle(26);

    gr1->Draw("AP");
    gr2->Draw("SameP");
    gr3->Draw("SameP");
    //gr3->Draw("AP");
    gr4->Draw("SameP");
    gr5->Draw("SameP");
    gr6->Draw("SameP");

    TLegend *leg = new TLegend(0.65,0.140,0.90,0.35);
    leg->AddEntry(gr1,"Tracker 1X","LPE");
    leg->AddEntry(gr2,"Tracker 1Y","LPE");
    leg->AddEntry(gr3,"Tracker 2X","LPE");
    leg->AddEntry(gr4,"Tracker 2Y","LPE");
    leg->AddEntry(gr5,"Tracker 3X","LPE");
    leg->AddEntry(gr6,"Tracker 3Y","LPE");

    leg->Draw("same");
    CMS_lumi( c1, iPeriod, 0 );
    c1->SaveAs("Residual_Tracker.pdf");
    c1->SaveAs("Residual_Tracker.png");
    //c1->SaveAs("Mean_Tracker.pdf");
    //c1->SaveAs("Mean_Tracker.png");
}
