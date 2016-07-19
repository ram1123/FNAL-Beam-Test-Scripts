 //this v-1 is only used to output histograms with number of strips > 1
#include <TString.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <TTree.h>
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>

//#include "tdrstyle.C"
//#include "CMS_lumi.C"


void SelectTrackerEvents_H4(const char * InputTextFile, const int RunNumber, string LargeGEM)
{
/*	setTDRStyle();

	writeExtraText = true;       // if extra text
	extraText  = "Preliminary";  // default extra text is "Preliminary"
	lumi_8TeV  = "19.1 fb^{-1}"; // default is "19.7 fb^{-1}"
	lumi_7TeV  = "4.9 fb^{-1}";  // default is "5.1 fb^{-1}"
	lumi_sqrtS = "13 TeV";       // used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)
	
	int iPeriod = 3;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV, 0=free form (uses lumi_sqrtS)
*/
//   InputTextFile = InputTextFile+".txt";
    cout<<"Input file = "<<InputTextFile<<endl;
    cout<<"Run Number = "<<RunNumber<<endl;

    fstream fin(InputTextFile,ios::in);
    //fstream fin("Hit_Position_Info.txt",ios::in);
    fstream fout_1("Eff.txt",ios::out);
      
    bool verbose = 0;
    bool verbose_forLoop = 1;

   float NHits_g2 =0; float NHits_g3 =0; float NHits_g1 =0; float NHits_LC1=0; float NHits_LC2=0; float NHits_LC3 =0; float Pos_g2X=0; float Pos_g2Y=0; float Pos_g3X=0; float Pos_g1X=0; float Pos_g1Y=0;

    //number of hits
    vector <int> NHits_g2xcl, NHits_g2ycl, NHits_g3xcl, NHits_g3ycl, NHits_g1xcl, NHits_g1ycl;
    vector <int> NHits_GE11_IV_GIF, NHits_GE11_IV, NHits_sCMSNS2LC3;
    
    //positions on detectors
    vector <double> Pos_g2xcl, Pos_g2ycl, Pos_g3xcl, Pos_g3ycl, Pos_g1xcl, Pos_g1ycl;
    vector <double> Pos_GE11_IV_GIF, Pos_GE11_IV, Pos_sCMSNS2LC3;

    //charges in detectors
    vector <double> Chrg_g2xcl, Chrg_g2ycl, Chrg_g3xcl, Chrg_g3ycl, Chrg_g1xcl, Chrg_g1ycl;
    vector <double> Chrg_GE11_IV_GIF, Chrg_GE11_IV, Chrg_sCMSNS2LC3;
   
    //strips in detectors
    vector <double> Strip_g2xcl, Strip_g2ycl, Strip_g3xcl, Strip_g3ycl, Strip_g1xcl, Strip_g1ycl;
    vector <double> Strip_GE11_IV_GIF, Strip_GE11_IV, Strip_sCMSNS2LC3;

    //initialize all the variables
    NHits_g2xcl.clear();
    NHits_g2ycl.clear();
    NHits_g3xcl.clear();
    NHits_g3ycl.clear();
    NHits_g1xcl.clear();
    NHits_g1ycl.clear();
    NHits_GE11_IV_GIF.clear();
    NHits_GE11_IV.clear();
    NHits_sCMSNS2LC3.clear();
    Pos_g2xcl.clear();
    Pos_g2ycl.clear();
    Pos_g3xcl.clear();
    Pos_g3ycl.clear();
    Pos_g1xcl.clear();
    Pos_g1ycl.clear();
    Pos_GE11_IV_GIF.clear();
    Pos_GE11_IV.clear();
    Pos_sCMSNS2LC3.clear();
    Chrg_g2xcl.clear();
    Chrg_g2ycl.clear();
    Chrg_g3xcl.clear();
    Chrg_g3ycl.clear();
    Chrg_g1xcl.clear();
    Chrg_g1ycl.clear();
    Chrg_GE11_IV_GIF.clear();
    Chrg_GE11_IV.clear();
    Chrg_sCMSNS2LC3.clear();
    Strip_g2xcl.clear();
    Strip_g2ycl.clear();
    Strip_g3xcl.clear();
    Strip_g3ycl.clear();
    Strip_g1xcl.clear();
    Strip_g1ycl.clear();
    Strip_GE11_IV_GIF.clear();
    Strip_GE11_IV.clear();
    Strip_sCMSNS2LC3.clear();
    //read the file, write values to array
    
    int evtNb=0;
    int count=0;
    TString firstString;
    int nbHits;
    double charge,position,strip;
    int aSingleStrip; double aSingleCharge;
    fout_1<<"RunNo\tTotal\t   cutNHits_g2\t   cutNHits_g3\t   cutNHits_g1\t   cutNHits_LC1\t   cutNHits_LC2\t   cutNHits_LC3\t   cutPos_g2X\t   cutPos_g2Y\t   cutPos_g3X\t   cutPos_g1X\t   cutPos_g1Y"<<endl;
    while(fin.good()) 
    {
	fin>>firstString;
	if (firstString == "") continue;
	if(firstString.EqualTo("EventNb"))
	{
	    fin>>count;
	    evtNb++;
	    if (verbose)
		cout<<"==================================================================\nevnt nb = "<<evtNb<< "\t firstString = "<< firstString << "\t count = "<< count <<endl;	    
	    if(evtNb%5000==0) 
	      cout<<"event number "<<evtNb<<endl;
	    continue;
	}
	//if (evtNb++ > 1) continue;	// Just added this line to read only one event
	fin>>nbHits>>charge>>position>>strip;
	if (verbose)
	    cout<<"det name = "<<firstString<<"\tnbHits = "<<nbHits << "\t charge = "<< charge << "\t position = "<< position << "\t strip = "<<strip<<endl;
	for(int i=0;i<nbHits;i++)
	{
	    fin>>aSingleStrip>>aSingleCharge;
	}
	    if(firstString.EqualTo("GE11_IV_GIF"))
	      {
		NHits_GE11_IV_GIF.push_back(nbHits);
		Pos_GE11_IV_GIF.push_back(position);
		Chrg_GE11_IV_GIF.push_back(charge);
		Strip_GE11_IV_GIF.push_back(strip);
	      }
	    if(firstString.EqualTo("GE11_IV"))
              {
                NHits_GE11_IV.push_back(nbHits);
                Pos_GE11_IV.push_back(position);
                Chrg_GE11_IV.push_back(charge);
                Strip_GE11_IV.push_back(strip);
              }
	    if(firstString.EqualTo("sCMSNS2LC3"))
              {
                NHits_sCMSNS2LC3.push_back(nbHits);
                Pos_sCMSNS2LC3.push_back(position);
                Chrg_sCMSNS2LC3.push_back(charge);
                Strip_sCMSNS2LC3.push_back(strip);
              }
	    if(firstString.EqualTo("g1xcl"))
	      {
		NHits_g1xcl.push_back(nbHits);
		Pos_g1xcl.push_back(position);
		Chrg_g1xcl.push_back(charge);
		Strip_g1xcl.push_back(strip);
	      }
	    if(firstString.EqualTo("g1ycl"))
	      {
		NHits_g1ycl.push_back(nbHits);
		Pos_g1ycl.push_back(position);
		Chrg_g1ycl.push_back(charge);
		Strip_g1ycl.push_back(strip);
	      }
	    if(firstString.EqualTo("g2xcl"))
              {
                NHits_g2xcl.push_back(nbHits);
                Pos_g2xcl.push_back(position);
                Chrg_g2xcl.push_back(charge);
                Strip_g2xcl.push_back(strip);
              }
            if(firstString.EqualTo("g2ycl"))
              {
                NHits_g2ycl.push_back(nbHits);
                Pos_g2ycl.push_back(position);
                Chrg_g2ycl.push_back(charge);
                Strip_g2ycl.push_back(strip);
              }
	    if(firstString.EqualTo("g3xcl"))
              {
                NHits_g3xcl.push_back(nbHits);
                Pos_g3xcl.push_back(position);
                Chrg_g3xcl.push_back(charge);
                Strip_g3xcl.push_back(strip);
              }
            if(firstString.EqualTo("g3ycl"))
              {
                NHits_g3ycl.push_back(nbHits);
                Pos_g3ycl.push_back(position);
                Chrg_g3ycl.push_back(charge);
                Strip_g3ycl.push_back(strip);
              }

	    if (verbose)
	    {
		cout<< aSingleStrip << "\t" << aSingleCharge << "\t";
		//cout<<"aSingleStrip = " << aSingleStrip << "\taSingleCharge = "<< aSingleCharge ;
	    }
	    if (verbose)
	      cout<<endl;
    }
if (verbose)
    cout<<"=========================\n\n\t\tWhile Loop ends\n\n===========================================\n\n"<<endl;

    TString outputfile;
    if ( LargeGEM == "No")
        outputfile = Form("TrackerOnly_Position_RunNumber%i.txt",RunNumber);
    if ( LargeGEM == "LC1")
        outputfile = Form("TrackerAndLC1_Position_RunNumber%i.txt",RunNumber);
    if ( LargeGEM == "LC2")
        outputfile = Form("TrackerAndLC2_Position_RunNumber%i.txt",RunNumber);
    if ( LargeGEM == "LC3")
        outputfile = Form("TrackerAndLC3_Position_RunNumber%i.txt",RunNumber);

    TString rootfile = Form("CoarseAligned_%i.root",RunNumber);
    //TString rootfile = Form("RootFiles/CoarseAligned.root");
    fstream fout(outputfile.Data(),ios::out);
    TFile* f = new TFile(rootfile.Data(),"recreate");
    /*    TCanvas *can1= new TCanvas("can1","",800,700);
    cmsprem = new TLatex(0,101,"CMS Preliminary");
    cmsprem->SetTextSize(0.04);
    gStyle->SetOptStat("ne");*/
    TH1F* h_Pos_g2xcl=new TH1F("h_Pos_g2xcl","",100, -10, 110);h_Pos_g2xcl->SetXTitle("Cluster position [mm]");h_Pos_g2xcl->SetYTitle("Frequency");h_Pos_g2xcl->SetTitleSize(0.04,"XY");h_Pos_g2xcl->SetLabelSize(0.04,"XY");									
    TH1F* h_Pos_g2ycl=new TH1F("h_Pos_g2ycl","",100, -10, 110);h_Pos_g2ycl->SetXTitle("Cluster position [mm]");h_Pos_g2ycl->SetYTitle("Frequency");h_Pos_g2ycl->SetTitleSize(0.04,"XY");h_Pos_g2ycl->SetLabelSize(0.04,"XY");
    TH1F* h_Pos_g3xcl=new TH1F("h_Pos_g3xcl","",100, -10, 110);h_Pos_g3xcl->SetXTitle("Cluster position [mm]");h_Pos_g3xcl->SetYTitle("Frequency");h_Pos_g3xcl->SetTitleSize(0.04,"XY");h_Pos_g3xcl->SetLabelSize(0.04,"XY");
    TH1F* h_Pos_g3ycl=new TH1F("h_Pos_g3ycl","",100, -10, 110);h_Pos_g3ycl->SetXTitle("Cluster position [mm]");h_Pos_g3ycl->SetYTitle("Frequency");h_Pos_g3ycl->SetTitleSize(0.04,"XY");h_Pos_g3ycl->SetLabelSize(0.04,"XY");
    TH1F* h_Pos_g1xcl=new TH1F("h_Pos_g1xcl","",100, -10, 110);h_Pos_g1xcl->SetXTitle("Cluster position [mm]");h_Pos_g1xcl->SetYTitle("Frequency");h_Pos_g1xcl->SetTitleSize(0.04,"XY");h_Pos_g1xcl->SetLabelSize(0.04,"XY");
    TH1F* h_Pos_g1ycl=new TH1F("h_Pos_g1ycl","",100, -10, 110);h_Pos_g1ycl->SetXTitle("Cluster position [mm]");h_Pos_g1ycl->SetYTitle("Frequency");h_Pos_g1ycl->SetTitleSize(0.04,"XY");h_Pos_g1ycl->SetLabelSize(0.04,"XY");
    TH1F* h_Pos_GE11_IV_GIF=new TH1F("h_Pos_GE11_IV_GIF","",100, 0, 100);h_Pos_GE11_IV_GIF->SetXTitle("Cluster position [mm]");h_Pos_GE11_IV_GIF->SetYTitle("Frequency");h_Pos_GE11_IV_GIF->SetTitleSize(0.04,"XY");h_Pos_GE11_IV_GIF->SetLabelSize(0.04,"XY");
    TH1F* h_Pos_GE11_IV=new TH1F("h_Pos_GE11_IV","",100, 0, 100);h_Pos_GE11_IV->SetXTitle("Cluster position [mm]");h_Pos_GE11_IV->SetYTitle("Frequency");h_Pos_GE11_IV->SetTitleSize(0.04,"XY");h_Pos_GE11_IV->SetLabelSize(0.04,"XY");
    TH1F* h_Pos_sCMSNS2LC3=new TH1F("h_Pos_sCMSNS2LC3","",100, 0, 100);h_Pos_sCMSNS2LC3->SetXTitle("Cluster position [mm]");h_Pos_sCMSNS2LC3->SetYTitle("Frequency");h_Pos_sCMSNS2LC3->SetTitleSize(0.04,"XY");h_Pos_sCMSNS2LC3->SetLabelSize(0.04,"XY");
    TH1F* h_Strip_g2xcl=new TH1F("h_Strip_g2xcl","",100, -10, 275);h_Strip_g2xcl->SetXTitle("Cluster position in terms of strip");h_Strip_g2xcl->SetYTitle("Frequency");h_Strip_g2xcl->SetTitleSize(0.04,"XY");h_Strip_g2xcl->SetLabelSize(0.04,"XY");
    TH1F* h_Strip_g2ycl=new TH1F("h_Strip_g2ycl","",100, -10, 275);h_Strip_g2ycl->SetXTitle("Cluster position in terms of strip");h_Strip_g2ycl->SetYTitle("Frequency");h_Strip_g2ycl->SetTitleSize(0.04,"XY");h_Strip_g2ycl->SetLabelSize(0.04,"XY");
    TH1F* h_Strip_g3xcl=new TH1F("h_Strip_g3xcl","",100, -10, 275);h_Strip_g3xcl->SetXTitle("Cluster position in terms of strip");h_Strip_g3xcl->SetYTitle("Frequency");h_Strip_g3xcl->SetTitleSize(0.04,"XY");h_Strip_g3xcl->SetLabelSize(0.04,"XY");
    TH1F* h_Strip_g3ycl=new TH1F("h_Strip_g3ycl","",100, -10, 275);h_Strip_g3ycl->SetXTitle("Cluster position in terms of strip");h_Strip_g3ycl->SetYTitle("Frequency");h_Strip_g3ycl->SetTitleSize(0.04,"XY");h_Strip_g3ycl->SetLabelSize(0.04,"XY");
    TH1F* h_Strip_g1xcl=new TH1F("h_Strip_g1xcl","",100, -10, 275);h_Strip_g1xcl->SetXTitle("Cluster position in terms of strip");h_Strip_g1xcl->SetYTitle("Frequency");h_Strip_g1xcl->SetTitleSize(0.04,"XY");h_Strip_g1xcl->SetLabelSize(0.04,"XY");
    TH1F* h_Strip_g1ycl=new TH1F("h_Strip_g1ycl","",100, -10, 275);h_Strip_g1ycl->SetXTitle("Cluster position in terms of strip");h_Strip_g1ycl->SetYTitle("Frequency");h_Strip_g1ycl->SetTitleSize(0.04,"XY");h_Strip_g1ycl->SetLabelSize(0.04,"XY");
    TH1F* h_Strip_GE11_IV_GIF=new TH1F("h_Strip_GE11_IV_GIF","",100, -10, 275);h_Strip_GE11_IV_GIF->SetXTitle("Cluster position in terms of strip");h_Strip_GE11_IV_GIF->SetYTitle("Frequency");h_Strip_GE11_IV_GIF->SetTitleSize(0.04,"XY");h_Strip_GE11_IV_GIF->SetLabelSize(0.04,"XY");
    TH1F* h_Strip_GE11_IV=new TH1F("h_Strip_GE11_IV","",100, -10, 275);h_Strip_GE11_IV->SetXTitle("Cluster position in terms of strip");h_Strip_GE11_IV->SetYTitle("Frequency");h_Strip_GE11_IV->SetTitleSize(0.04,"XY");h_Strip_GE11_IV->SetLabelSize(0.04,"XY");
    TH1F* h_Strip_sCMSNS2LC3=new TH1F("h_Strip_sCMSNS2LC3","",100, -10, 275);h_Strip_sCMSNS2LC3->SetXTitle("Cluster position in terms of strip");h_Strip_sCMSNS2LC3->SetYTitle("Frequency");h_Strip_sCMSNS2LC3->SetTitleSize(0.04,"XY");h_Strip_sCMSNS2LC3->SetLabelSize(0.04,"XY");
    TH1F* h_NHits_g1xcl=new TH1F("h_NHits_g1xcl","",500, -1, 10);h_NHits_g1xcl->SetXTitle("Number of Hits");h_NHits_g1xcl->SetYTitle("Frequency");h_NHits_g1xcl->SetTitleSize(0.04,"XY");h_NHits_g1xcl->SetLabelSize(0.04,"XY");
    TH1F* h_NHits_g1ycl=new TH1F("h_NHits_g1ycl","",500, -1, 10);h_NHits_g1ycl->SetXTitle("Number of Hits");h_NHits_g1ycl->SetYTitle("Frequency");h_NHits_g1ycl->SetTitleSize(0.04,"XY");h_NHits_g1ycl->SetLabelSize(0.04,"XY");
    TH1F* h_NHits_g2xcl=new TH1F("h_NHits_g2xcl","",500, -1, 10);h_NHits_g2xcl->SetXTitle("Number of Hits");h_NHits_g2xcl->SetYTitle("Frequency");h_NHits_g2xcl->SetTitleSize(0.04,"XY");h_NHits_g2xcl->SetLabelSize(0.04,"XY");
    TH1F* h_NHits_g2ycl=new TH1F("h_NHits_g2ycl","",500, -1, 10);h_NHits_g2ycl->SetXTitle("Number of Hits");h_NHits_g2ycl->SetYTitle("Frequency");h_NHits_g2ycl->SetTitleSize(0.04,"XY");h_NHits_g2ycl->SetLabelSize(0.04,"XY");
    TH1F* h_NHits_g3xcl=new TH1F("h_NHits_g3xcl","",500, -1, 10);h_NHits_g3xcl->SetXTitle("Number of Hits");h_NHits_g3xcl->SetYTitle("Frequency");h_NHits_g3xcl->SetTitleSize(0.04,"XY");h_NHits_g3xcl->SetLabelSize(0.04,"XY");
    TH1F* h_NHits_g3ycl=new TH1F("h_NHits_g3ycl","",500, -1, 10);h_NHits_g3ycl->SetXTitle("Number of Hits");h_NHits_g3ycl->SetYTitle("Frequency");h_NHits_g3ycl->SetTitleSize(0.04,"XY");h_NHits_g3ycl->SetLabelSize(0.04,"XY");
    TH1F* h_NHits_GE11_IV_GIF=new TH1F("h_NHits_GE11_IV_GIF","",500, -1, 10);h_NHits_GE11_IV_GIF->SetXTitle("Number of Hits");h_NHits_GE11_IV_GIF->SetYTitle("Frequency");h_NHits_GE11_IV_GIF->SetTitleSize(0.04,"XY");h_NHits_GE11_IV_GIF->SetLabelSize(0.04,"XY");
    TH1F* h_NHits_GE11_IV=new TH1F("h_NHits_GE11_IV","",500, -1, 10);h_NHits_GE11_IV->SetXTitle("Number of Hits");h_NHits_GE11_IV->SetYTitle("Frequency");h_NHits_GE11_IV->SetTitleSize(0.04,"XY");h_NHits_GE11_IV->SetLabelSize(0.04,"XY");
    TH1F* h_NHits_sCMSNS2LC3=new TH1F("h_NHits_sCMSNS2LC3","",500, -1, 10);h_NHits_sCMSNS2LC3->SetXTitle("Number of Hits");h_NHits_sCMSNS2LC3->SetYTitle("Freqency");h_NHits_sCMSNS2LC3->SetTitleSize(0.04,"XY");h_NHits_sCMSNS2LC3->SetLabelSize(0.04,"XY");
    //    cout << " ####################" <<endl;
    //////////////////////////////////////////////////////////////////////////////

    //     PROFILE PLOTS

    //////////////////////////////////////////////////////////////////////////////

    //    cout<<"entries before : "<<Pos_g1xcl.size()<<endl;
    TH2F *BeamProfile_Tracker_1=new TH2F("BeamProfile_Tracker_1","",32,0,100,32,0,100);
    TH2F *BeamProfile_Tracker_2=new TH2F("BeamProfile_Tracker_2","",32,0,100,32,0,100);
    TH2F *BeamProfile_Tracker_3=new TH2F("BeamProfile_Tracker_3","",32,0,100,32,0,100);

    //    cout<<"entries : "<<Pos_g1xcl.size()<<endl;
    // int icut1 =0; int icut2=0; int icut3=0; int icut4=0; int icut5=0; int icut6 =0; int icut7=0; int icut8=0; int icut9=0; int icut10=0; int icut11=0;
	int totalEvents = 0;

if (verbose){
    cout<<"=========================\n\n\t\tEvent Loop Starts\n\n===========================================\n\n"<<endl;
    cout<<"Total number of events = "<<evtNb<<endl;
    }
	for(int i=0; i<evtNb; i++){
	//set number of hits cut conditions    
	  //	  cout<<"entries after: "<<Pos_g1xcl.size()<<endl;                                                                                                 
	if (verbose_forLoop)
		cout<<i<<"\tStart Reading Hit Info..."<<endl;
	Bool_t cutNHits_g2 = false;
	if(NHits_g2xcl.at(i)>0 && NHits_g2ycl.at(i)>0)
	  {	
	    cutNHits_g2 = true;
	    NHits_g2++;
	  }

	cout<<"DEBUG 1"<<endl;	
	Bool_t cutNHits_g3 = false;
	cout<<"g3x = "<<NHits_g3xcl.at(i)<<"\tg3y = "<<NHits_g3ycl.at(i)<<endl;
        if(NHits_g3xcl.at(i)>0 && NHits_g3ycl.at(i)>0)
          {
            cutNHits_g3 = true;
	    NHits_g3++;
	  }
	
	cout<<"DEBUG 2"<<endl;	
	Bool_t cutNHits_g1 = false;
        if(NHits_g1xcl.at(i)>0 && NHits_g1ycl.at(i)>0)
          {
            cutNHits_g1 = true;
	    NHits_g1++;
	  }
	
	Bool_t cutNHits_LC1 = false;
	if(NHits_GE11_IV_GIF.at(i) > 0) 
	  {
	    cutNHits_LC1 = true;
	    NHits_LC1++;
	  }
	
	Bool_t cutNHits_LC2 = false;
        if(NHits_GE11_IV.at(i) > 0) 
	  {
	    cutNHits_LC2 = true;
	    NHits_LC2++;
	  }
	Bool_t cutNHits_LC3 = false;
        if(NHits_sCMSNS2LC3.at(i) > 0)
	  {
	    cutNHits_LC3 = true;
	    NHits_LC3++;
	  }
	if (verbose_forLoop)
		cout<<i<<"\tHits read, now reading positons..."<<endl;
	//set position cut consitions
	Bool_t cutPos_g2X = false;
        if(Pos_g2xcl.at(i)>=0. && Pos_g2xcl.at(i)<=120.)
          {
            cutPos_g2X = true;
	    Pos_g2X++;
	  }

	Bool_t cutPos_g2Y = false;
        if(Pos_g2ycl.at(i)>=0 && Pos_g2ycl.at(i)<=120)
          {
            cutPos_g2Y = true;
	    Pos_g2Y++;
	  }
	
	Bool_t cutPos_g3X = false;
	if(Pos_g3xcl.at(i)>=0 && Pos_g3xcl.at(i)<=120)
          {
            cutPos_g3X = true;
	    Pos_g3X++;
	  }
	
	Bool_t cutPos_g1X = false;
	if(Pos_g1xcl.at(i)>=0 && Pos_g1xcl.at(i)<=120)
          {
            cutPos_g1X = true;
	    Pos_g1X++;
	  }
	
	Bool_t cutPos_g1Y = false;
        if(Pos_g1ycl.at(i)>=0 && Pos_g1ycl.at(i)<=120)
          {
            cutPos_g1Y = true;
	    Pos_g1Y++;
	  }
	if (verbose_forLoop)
		cout<<i<<"\tEnd reading position info.."<<endl;
	
	//	cout << "######################"<<endl;
	
	//then combine the cut conditions & fill histograms
	Bool_t trigger=false;
	if ( LargeGEM == "No")
	    if(cutNHits_g2==true && cutNHits_g3==true && cutNHits_g1==true )
		trigger = true;
	if ( LargeGEM == "LC1")
	    if(cutNHits_g2==true && cutNHits_g3==true && cutNHits_g1==true && cutNHits_LC1==true ) 
		trigger = true;
	if ( LargeGEM == "LC2")
	    if(cutNHits_g2==true && cutNHits_g3==true && cutNHits_g1==true && cutNHits_LC2==true ) 
		trigger = true;
	if ( LargeGEM == "LC3")
	    if(cutNHits_g2==true && cutNHits_g3==true && cutNHits_g1==true && cutNHits_LC3==true ) 
		trigger = true;



	if(trigger){
	  totalEvents++;

	if ( LargeGEM == "No")
	    fout<<Pos_g2xcl.at(i)<<"\t"<<Pos_g2ycl.at(i)<<"\t"<<Pos_g3xcl.at(i)<<"\t"<<Pos_g3ycl.at(i)<<"\t"<<Pos_g1xcl.at(i)<<"\t"<<Pos_g1ycl.at(i)<<endl;
	if ( LargeGEM == "LC1")
	    fout<<Pos_g2xcl.at(i)<<"\t"<<Pos_g2ycl.at(i)<<"\t"<<Pos_g3xcl.at(i)<<"\t"<<Pos_g3ycl.at(i)<<"\t"<<Pos_g1xcl.at(i)<<"\t"<<Pos_g1ycl.at(i)<< "\t"<< Pos_GE11_IV_GIF.at(i)<<endl;
	if ( LargeGEM == "LC2")
	    fout<<Pos_g2xcl.at(i)<<"\t"<<Pos_g2ycl.at(i)<<"\t"<<Pos_g3xcl.at(i)<<"\t"<<Pos_g3ycl.at(i)<<"\t"<<Pos_g1xcl.at(i)<<"\t"<<Pos_g1ycl.at(i)<< "\t"<< Pos_GE11_IV.at(i)<<endl;
	if ( LargeGEM == "LC3")
	    fout<<Pos_g2xcl.at(i)<<"\t"<<Pos_g2ycl.at(i)<<"\t"<<Pos_g3xcl.at(i)<<"\t"<<Pos_g3ycl.at(i)<<"\t"<<Pos_g1xcl.at(i)<<"\t"<<Pos_g1ycl.at(i)<< "\t"<< Pos_sCMSNS2LC3.at(i)<<endl;

	  h_Pos_g2xcl->Fill(Pos_g2xcl.at(i));
	  h_Pos_g2ycl->Fill(Pos_g2ycl.at(i));
	  h_Pos_g3xcl->Fill(Pos_g3xcl.at(i));
	  h_Pos_g3ycl->Fill(Pos_g3ycl.at(i));
	  h_Pos_g1xcl->Fill(Pos_g1xcl.at(i));
	  h_Pos_g1ycl->Fill(Pos_g1ycl.at(i));
	  if(NHits_GE11_IV_GIF.at(i) > 0){
	    h_Pos_GE11_IV_GIF->Fill(Pos_GE11_IV_GIF.at(i));}
	  if(NHits_GE11_IV.at(i) > 0){
	    h_Pos_GE11_IV->Fill(Pos_GE11_IV.at(i));}
	  if(NHits_sCMSNS2LC3.at(i) > 0){
	    h_Pos_sCMSNS2LC3->Fill(Pos_sCMSNS2LC3.at(i));}
	  h_Strip_g2xcl->Fill(Strip_g2xcl.at(i));
	  h_Strip_g2ycl->Fill(Strip_g2ycl.at(i));
	  h_Strip_g3xcl->Fill(Strip_g3xcl.at(i));
	  h_Strip_g3ycl->Fill(Strip_g3ycl.at(i));
	  h_Strip_g1xcl->Fill(Strip_g1xcl.at(i));
	  h_Strip_g1ycl->Fill(Strip_g1ycl.at(i));
	  if(NHits_GE11_IV_GIF.at(i) > 0){
	    h_Strip_GE11_IV_GIF->Fill(Strip_GE11_IV_GIF.at(i));}
	  if(NHits_GE11_IV.at(i) > 0){
	    h_Strip_GE11_IV->Fill(Strip_GE11_IV.at(i));}
	  if(NHits_sCMSNS2LC3.at(i) > 0){
	    h_Strip_sCMSNS2LC3->Fill(Strip_sCMSNS2LC3.at(i));}
	  h_NHits_g2xcl->Fill(NHits_g2xcl.at(i));
	  h_NHits_g2ycl->Fill(NHits_g2ycl.at(i));
	  h_NHits_g3xcl->Fill(NHits_g3xcl.at(i));
	  h_NHits_g3ycl->Fill(NHits_g3ycl.at(i));
	  h_NHits_g1xcl->Fill(NHits_g1xcl.at(i));
	  h_NHits_g1ycl->Fill(NHits_g1ycl.at(i));
	  h_NHits_GE11_IV_GIF->Fill(NHits_GE11_IV_GIF.at(i));
	  h_NHits_GE11_IV->Fill(NHits_GE11_IV.at(i));
	  h_NHits_sCMSNS2LC3->Fill(NHits_sCMSNS2LC3.at(i));
	 
	  //       	  cout<<"totalEvents = "<<totalEvents<<endl;
	//trigger loop
	  //	  for(unsigned int i=0;i<Pos_g1xcl.size();i++)
	    //	    cout<<"chk thi :"<<Pos_g1xcl.at(i)<<endl;

	  // gStyle->SetPalette(1);  
	  BeamProfile_Tracker_1->Fill(Pos_g1xcl.at(i),Pos_g1ycl.at(i)); // BeamProfile_Tracker_1->Draw("colz");
	  BeamProfile_Tracker_2->Fill(Pos_g2xcl.at(i),Pos_g2ycl.at(i)); // BeamProfile_Tracker_2->Draw("colz");
	  BeamProfile_Tracker_3->Fill(Pos_g3xcl.at(i),Pos_g3ycl.at(i)); //  BeamProfile_Tracker_3->Draw("colz");
	  
	  
	}// trigger loop
	}	    
if (verbose)	
    cout<<"=========================\n\n\t\tEvent Loop ends\n\n===========================================\n\n"<<endl;
	  //BeamProfile_Tracker_1->Draw("COLZ");
	  //BeamProfile_Tracker_2->Draw("COLZ");
	  //BeamProfile_Tracker_3->Draw("COLZ");  
	
	
	// no of events
	// BeamProfile_Tracker_1->Write();
	float Eff[11];
       
	  Eff[0] = NHits_g2/evtNb,
	  Eff[1] = NHits_g3/evtNb,
	  Eff[2] = NHits_g1/evtNb,
	  Eff[3] = NHits_LC1/evtNb,
	  Eff[4] = NHits_LC2/evtNb,
	  Eff[5] = NHits_LC3/evtNb,
	  Eff[6] = Pos_g2X/evtNb,
	  Eff[7] = Pos_g2Y/evtNb,
	  Eff[8] = Pos_g3X/evtNb,
	  Eff[9] = Pos_g1X/evtNb,
	  Eff[10] = Pos_g1Y/evtNb,
	    /* for(unsigned int i=0; i<11; i++){
	      cout<<"efficiency :"<< Eff[i]<<endl;
	      }*/
	  cout<<"efficiency 1 :"<<Eff[0]<<endl;
	  cout<<"efficiency 2 :"<<Eff[1]<<endl;
	  cout<<"efficiency 3 :"<<Eff[2]<<endl;
	  cout<<"efficiency 4 :"<<Eff[3]<<endl;
	  cout<<"efficiency 5 :"<<Eff[4]<<endl;
	  cout<<"efficiency 6 :"<<Eff[5]<<endl;
	  cout<<"efficiency 7 :"<<Eff[6]<<endl;
	  cout<<"efficiency 8 :"<<Eff[7]<<endl;
	  cout<<"efficiency 9 :"<<Eff[8]<<endl;
	  cout<<"efficiency 10 :"<<Eff[9]<<endl;
	  cout<<"efficiency 11 :"<<Eff[10]<<endl;
	    

	  fout_1<<"\t"<<"\t"<<"\t"<<Eff[0]<<"\t"<<"\t"<<Eff[1]<<"\t"<<"\t"<<Eff[2]<<"\t"<<"\t"<<Eff[3]<<"\t"<<Eff[4]<<"\t"<<Eff[5]<<"\t"<<Eff[6]<<"\t"<<"\t"<<Eff[7]<<"\t"<<"\t"<<Eff[8]<<"\t"<<"\t"<<Eff[9]<<"\t"<<"\t"<<Eff[10]<<endl;
	cout<< "cutNHits_g2 : "<< NHits_g2<<endl;
	cout<< "cutNHits_g3 : "<< NHits_g3<<endl;
	cout<< "cutNHits_g1 : "<< NHits_g1<<endl;
	cout<< "cutNHits_LC1 : "<< NHits_LC1<<endl;
	cout<< "cutNHits_LC2 : "<< NHits_LC2<<endl;
	cout<< "cutNHits_LC3 : "<< NHits_LC3<<endl;
	cout<< "cutPos_g2X : "<< Pos_g2X<<endl;
	cout<< "cutPos_g2Y : "<< Pos_g2Y<<endl;
	cout<< "cutPos_g1X : "<< Pos_g3X<<endl;
	cout<< "cutPos_g3X : "<< Pos_g1X<<endl;
	cout<< "cutPos_g3Y : "<< Pos_g1Y<<endl;

	fout.close();
	fout_1.close();
	f->Write();
	f->Close();
}//SelectTrackerEvents
