//#include "Riostream.h"
//#include "vector.h"
#include "TGraphErrors.h"
#include "setTDRStyle.C"


void SpaceResolution_vs_HV() {

   ifstream in;
   in.open("SpaceResolutionInfo.txt");

   TGaxis::SetMaxDigits(3);
   gStyle->SetOptStat(0);
   // Set TDR Style
   setTDRStyle();


   Float_t HighVoltage, SpaceResolution, ErrorSpaceResolution;
   vector<float> v_HighVoltage, v_SpaceResolution, E_SpaceResolution;

   Int_t nlines = 0;
   TFile *f = new TFile("SpaceResolution_R1592_R1646.root","RECREATE");
   TNtuple *ntuple = new TNtuple("ntuple","data from ascii file","HV:SpaceResolution:ErrorSpaceResolution");
//   TCanvas *c1 = new TCanvas("c1","HighVoltage_vs_SpaceResolution");
   TCanvas* c1 = new TCanvas("c1","",1);
   c1->Range(0,0,1,1);
   TPad *pad = new TPad("pad","",0,0,1,1);
   pad->SetGrid();
   pad->Draw();
   pad->cd();


string line;
while(getline(in,line))
{
        if(line[0] == '#') continue;

	stringstream(line) >> HighVoltage >> SpaceResolution >> ErrorSpaceResolution;
	
	cout<<"===> "<<HighVoltage <<"\t "<<SpaceResolution<<"\t"<<ErrorSpaceResolution<<endl;
	v_HighVoltage.push_back(HighVoltage);
	v_SpaceResolution.push_back(SpaceResolution);
	E_SpaceResolution.push_back(ErrorSpaceResolution);
	ntuple->Fill(HighVoltage,SpaceResolution,ErrorSpaceResolution);
}
   printf(" found %zu points\n",v_HighVoltage.size());
   in.close();

   TGraphErrors * gr = new TGraphErrors(v_HighVoltage.size()); 
    
   for (unsigned int i = 0; i<v_HighVoltage.size();i++)
{
	gr->SetPoint(i,v_HighVoltage[i],v_SpaceResolution[i]);
	gr->SetPointError(i,0,E_SpaceResolution[i]);
}

   gr->SetTitle("");
   //gr->SetTitle("High Voltage vs Cluster Size");
   gr->GetXaxis()->SetTitle("High Voltage supplied to divider (kV)");
   gr->GetYaxis()->SetTitle("Space Resolution");
   gr->GetYaxis()->SetTitleOffset(1.0);
   gr->GetXaxis()->SetTitleOffset(0.9);
   gr->GetYaxis()->SetTitleSize(0.05);
   gr->GetXaxis()->SetTitleSize(0.05);
   //gr->GetXaxis()->SetLabelSize(0.05);
   gr->GetYaxis()->SetRangeUser(1140,1380);
   gr->SetMarkerSize(1);
   gr->SetMarkerColor(2);
   gr->SetMarkerStyle(21);

   gr->Draw("ALP");

   TLatex *text1 = new TLatex(770,1252.107,"Threshold = 1.2 fC");
   TLatex *text2 = new TLatex(770,1232.104,"Beam: Muon");
   TLatex *text3 = new TLatex(770,1212.101,"Gap Config: 3/1/2/1 mm");
   TLatex *text5 = new TLatex(770,1192.098,"Gas: Ar/CO2/CF4 (45/15/40)");
   TLatex *text4 = new TLatex(770,1172.000,"Run Range: 1592-1646");
   TLatex *text6 = new TLatex(770,1152.000,"(i#eta,i#phi)=(5,2)");
//   TLatex *text5 = new TLatex(3250,0.64,ClockMode);


   text1->SetTextFont(42);
   text2->SetTextFont(42);
   text3->SetTextFont(42);
   text4->SetTextFont(42);
   text5->SetTextFont(42);
   text6->SetTextFont(42);
   text1->SetTextSize(0.05);
   text2->SetTextSize(0.05);
   text3->SetTextSize(0.05);
   text4->SetTextSize(0.05);
   text5->SetTextSize(0.05);
   text6->SetTextSize(0.05);
   TLatex *cmsprem = new TLatex(560,2.110,"#it{CMS Preliminary}");

   TLatex *gen = new TLatex(795,2.110,"GE1/1");

   text1->Draw("same");
   text2->Draw("same");
   text3->Draw("same");
   text4->Draw("same");
   text5->Draw("same");
   text6->Draw("same");
   cmsprem->Draw("same");
   gen->Draw("same");



   c1->Write();
   c1->SaveAs("HighVoltage_Vs_SpaceResolution.pdf");
   c1->SaveAs("HighVoltage_Vs_SpaceResolution.png");
   c1->SaveAs("HighVoltage_Vs_SpaceResolution.root");
   c1->SaveAs("HighVoltage_Vs_SpaceResolution.C");
   f->Write();
}
