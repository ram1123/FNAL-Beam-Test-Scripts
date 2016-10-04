/*
 * 1. Make range external variable
 * 2. 
 */

#include <vector>
#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include <fstream>
#include <TH1.h>
#include <TH2.h>
#include <TString.h>
#include <TAxis.h>
#include "doubleGausFit_withHistParameter.C"

void  AlignTrackers_Shift( string txtfilename, int RunNumber, double shi_g1xcl, double shi_g1ycl, double shi_g2xcl, double shi_g2ycl, double shi_g3xcl, double shi_g3ycl , double Trk1Pos, double Trk2Pos, double Trk3Pos)
{

    bool verbose = 0;
    bool IncludeFirstTracker = 1;

	cout<<"\n=================================================\n"<<endl;
	cout<<"\tPrint Input Parameters:"<<endl;
	cout<<"\n================================================="<<endl;
	cout<<"Name of input file = "<<txtfilename<<endl;
	cout<<"Run Number = "<<RunNumber<<endl;
	cout<<"Detector Positions (in mm):"<<endl;
	cout<<"\tTracker 1 position = "<<Trk1Pos<<endl;
	cout<<"\tTracker 2 position = "<<Trk2Pos<<endl;
	cout<<"\tTracker 3 position = "<<Trk3Pos<<endl<<endl;
	cout<<"Shift Parameters (in mm):"<<endl;
	cout<<"\tTrk 1X: Mean = "<<shi_g1xcl<<endl;
	cout<<"\tTrk 1Y: Mean = "<<shi_g1ycl<<endl;
	cout<<"\tTrk 2X: Mean = "<<shi_g2xcl<<endl;
	cout<<"\tTrk 2Y: Mean = "<<shi_g2ycl<<endl;
	cout<<"\tTrk 3X: Mean = "<<shi_g3xcl<<endl;
	cout<<"\tTrk 3Y: Mean = "<<shi_g3ycl<<endl;
	cout<<"\n================================================="<<endl;

    string thestring = "Position";
    cout<<"Input text file = "<< txtfilename <<endl;

    string shiftHead	= "shiftParameters_";
    string residualHead	= "residuals_";
    string meanHead	= "mean_";
    string ResidualRHead= "Residual_";
    string FinalShiftParameters = "ShiftPar_LinearShiftTrkOnly";

    string DirName = "Residual_XY_Trk_RootFile/";
    string DirName_FinalShiftPar_LinShiftTrk = "FinalShiftPar_LinShiftTrk/";
    string DirNameShiftPar = "shiftParameters/";
    string DirNameResidual = "residual_txtFile/";
    string DirNameMean = "mean_txtFile/";

    char runname[50]; sprintf(runname,"_alignTrackers_R%i.txt",RunNumber);
    string foutname	= DirNameShiftPar+shiftHead+thestring+runname;	// Shift parameter will go in this text file
    string fout1name	= DirNameResidual+residualHead+thestring+runname;	// Residual will go into this
    string fout2name	= DirNameMean+meanHead+thestring+runname;	// Residual will go into this
    string foutFinalShiftPar = DirName_FinalShiftPar_LinShiftTrk+FinalShiftParameters+runname;	// Final shift parameter will go this this file

    fstream fin(txtfilename.c_str(),ios::in);
    if(!fin)	{cout<<"file not read"<<endl;}

    fstream fout(foutname.c_str(),ios::out);
    fstream fout1(fout1name.c_str(),ios::out);
    fstream fout2(fout2name.c_str(),ios::out);
    fstream foutFshiPar(foutFinalShiftPar.c_str(),ios::out);
    fstream foutChiSqr1("ShiftLinear_Shift_vs_Chi2_TrkX.dat",ios::out);
    fstream foutChiSqr2("ShiftLinear_Shift_vs_Chi2_TrkY.dat",ios::out);

    double Pos_g2xcl=0.0, Pos_g2ycl=0.0;
    double Pos_g3xcl=0.0, Pos_g3ycl=0.0;
    double Pos_g1xcl=0.0, Pos_g1ycl=0.0;
    std::vector<double> vPos_g2xcl; std::vector<double> vPos_g2ycl;
    std::vector<double> vPos_g3xcl; std::vector<double> vPos_g3ycl;
    std::vector<double> vPos_g1xcl; std::vector<double> vPos_g1ycl;
    
    
    Int_t nbLines=0;
    //
    // Read all events and put each hits in a vector
    //
    while(fin>>Pos_g1xcl>>Pos_g1ycl>>Pos_g2xcl>>Pos_g2ycl>>Pos_g3xcl>>Pos_g3ycl){
	vPos_g2xcl.push_back(Pos_g2xcl); vPos_g2ycl.push_back(Pos_g2ycl); 
	vPos_g3xcl.push_back(Pos_g3xcl); vPos_g3ycl.push_back(Pos_g3ycl);
	vPos_g1xcl.push_back(Pos_g1xcl); vPos_g1ycl.push_back(Pos_g1ycl);
	nbLines++;
    } // getting input
    fin.close();
    //
    //	File read completed and file closed 
    //
    
    if (verbose)
	cout << "................................................"<<endl;
    
    
    double mean_g2xcl=10.0, mean_g2ycl=10.0;
    double mean_g3xcl=10.0, mean_g3ycl=10.0;
    double mean_g1xcl=10.0, mean_g1ycl=10.0;
    double sigma_g2xcl=0.0, sigma_g2ycl=0.0;
    double sigma_g3xcl=0.0, sigma_g3ycl=0.0;
    double sigma_g1xcl=0.0, sigma_g1ycl=0.0;

TH1F* h_residual_g1xcl;
TH1F* h_residual_g1ycl;
TH1F* h_residual_g2xcl;
TH1F* h_residual_g2ycl;
TH1F* h_residual_g3xcl;
TH1F* h_residual_g3ycl;

    
    if (verbose)
	cout << "****************************************************"<<endl;
    
    Int_t iterNb=0;
    
    if (verbose)
	cout<<"DEBUG  1"<<endl;
    
    double Tot_Shift_2X = 0.0, Tot_Shift_2Y = 0.0;
    double Tot_Shift_3X = 0.0, Tot_Shift_3Y = 0.0;

    fout<<"# shi_g1xcl"<<"\t"<<"shi_g1ycl"<<"\t"<<"shi_g2xcl"<<"\t"<<"shi_g2ycl"<<"\t"<<"shi_g3xcl"<<"\t"<<"shi_g3ycl"<<endl;
    while(1){
	if (verbose)
	    cout<<"DEBUG  2"<<endl;
	char rootfile[50]; sprintf(rootfile,"_iter_%i_R%i.root",iterNb,RunNumber);
	string outputrootname=DirName+ResidualRHead+thestring+rootfile;

	cout <<"++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    cout<<"\nOutput Root File Name: "<<outputrootname<<endl<<endl;

	TFile* f = new TFile(outputrootname.c_str(),"recreate");  
	iterNb++;
	char name1X[15];sprintf(name1X,"Pos_g1xcl_%i",iterNb); char name1Y[15];sprintf(name1Y,"Pos_g1ycl_%i",iterNb);
	char name2X[15];sprintf(name2X,"Pos_g2xcl_%i",iterNb); char name2Y[15];sprintf(name2Y,"Pos_g2ycl_%i",iterNb);
	char name3X[15];sprintf(name3X,"Pos_g3xcl_%i",iterNb); char name3Y[15];sprintf(name3Y,"Pos_g3ycl_%i",iterNb);

	TH2F* Trk1_ResXPosY = new TH2F("Trk1_ResXPosY","",20,-50,50,20,-1,1);
	TH2F* Trk1_ResXPosX = new TH2F("Trk1_ResXPosX","",20,-50,50,20,-1,1);
	TH2F* Trk1_ResYPosX = new TH2F("Trk1_ResYPosX","",20,-50,50,20,-1,1);
	TH2F* Trk1_ResYPosY = new TH2F("Trk1_ResYPosY","",20,-50,50,20,-1,1);

	TH2F* Trk2_ResXPosY = new TH2F("Trk2_ResXPosY","",20,-50,50,20,-1,1);
	TH2F* Trk2_ResXPosX = new TH2F("Trk2_ResXPosX","",20,-50,50,20,-1,1);
	TH2F* Trk2_ResYPosX = new TH2F("Trk2_ResYPosX","",20,-50,50,20,-1,1);
	TH2F* Trk2_ResYPosY = new TH2F("Trk2_ResYPosY","",20,-50,50,20,-1,1);
	
	TH2F* Trk3_ResXPosY = new TH2F("Trk3_ResXPosY","",20,-50,50,20,-1,1);
	TH2F* Trk3_ResXPosX = new TH2F("Trk3_ResXPosX","",20,-50,50,20,-1,1);
	TH2F* Trk3_ResYPosX = new TH2F("Trk3_ResYPosX","",20,-50,50,20,-1,1);
	TH2F* Trk3_ResYPosY = new TH2F("Trk3_ResYPosY","",20,-50,50,20,-1,1);
	
	TH1F* TrkX_Slope = new TH1F("TrkX_Slope","Tracker-X: Slope",200,-.03,.03);
	TH1F* TrkY_Slope = new TH1F("TrkY_Slope","Tracker-Y: Slope",200,-.03,.03);
	
	TH1F* TrkX_Intercept = new TH1F("TrkX_Intercept","Tracker-X: Intercept",200,-50.00,50.00);
	TH1F* TrkY_Intercept = new TH1F("TrkY_Intercept","Tracker-Y: Intercept",200,-50.00,50.00);
	
	if (verbose)
	    cout<<"DEBUG  3"<<endl;
        TH1F* h_Pos_g1xcl = new TH1F(name3X,"",100,-60,70); h_Pos_g1xcl->SetXTitle("Cluster position [mm]"); h_Pos_g1xcl->SetYTitle("Frequency");h_Pos_g1xcl->SetLabelSize(0.045,"XY");h_Pos_g1xcl->SetTitleSize(0.045,"XY");
        TH1F* h_Pos_g1ycl = new TH1F(name3Y,"",100,-60,70); h_Pos_g1ycl->SetXTitle("Cluster position [mm]"); h_Pos_g1ycl->SetYTitle("Frequency");h_Pos_g1ycl->SetLabelSize(0.045,"XY");h_Pos_g1ycl->SetTitleSize(0.045,"XY");  
		TH1F* h_Pos_g2xcl = new TH1F(name2X,"",100,-60,70); h_Pos_g2xcl->SetXTitle("Cluster position [mm]"); h_Pos_g2xcl->SetYTitle("Frequency");h_Pos_g2xcl->SetLabelSize(0.045,"XY");h_Pos_g2xcl->SetTitleSize(0.045,"XY");
        TH1F* h_Pos_g2ycl = new TH1F(name2Y,"",100,-60,70); h_Pos_g2ycl->SetXTitle("Cluster position [mm]"); h_Pos_g2ycl->SetYTitle("Frequency");h_Pos_g2ycl->SetLabelSize(0.045,"XY");h_Pos_g2ycl->SetTitleSize(0.045,"XY");  
        TH1F* h_Pos_g3xcl = new TH1F(name1X,"",100,-60,70); h_Pos_g3xcl->SetXTitle("Cluster position [mm]"); h_Pos_g3xcl->SetYTitle("Frequency");h_Pos_g3xcl->SetLabelSize(0.045,"XY");h_Pos_g3xcl->SetTitleSize(0.045,"XY");
        TH1F* h_Pos_g3ycl = new TH1F(name1Y,"",100,-60,70); h_Pos_g3ycl->SetXTitle("Cluster position [mm]"); h_Pos_g3ycl->SetYTitle("Frequency");h_Pos_g3ycl->SetLabelSize(0.045,"XY");h_Pos_g3ycl->SetTitleSize(0.045,"XY");  

	
	if (verbose)
	    cout<<"DEBUG  4"<<endl;
	char nameRes1X[30];sprintf(nameRes1X,"residual_g1xcl_%i",iterNb);char nameRes1Y[30];sprintf(nameRes1Y,"residual_g1ycl_%i",iterNb);
	char nameRes2X[30];sprintf(nameRes2X,"residual_g2xcl_%i",iterNb);char nameRes2Y[30];sprintf(nameRes2Y,"residual_g2ycl_%i",iterNb);
	char nameRes3X[30];sprintf(nameRes3X,"residual_g3xcl_%i",iterNb);char nameRes3Y[30];sprintf(nameRes3Y,"residual_g3ycl_%i",iterNb);
	


	if( fabs(mean_g2xcl)<0.05 && fabs(mean_g2ycl)<0.05 && fabs(mean_g3xcl)<0.05 && fabs(mean_g3ycl)<0.5)
	    {
	    cout<<"==========> Fourth Loop"<<endl;
         h_residual_g1xcl = new TH1F(nameRes1X,"",40,-1,1); h_residual_g1xcl->SetXTitle("Residual [mm]"); h_residual_g1xcl->SetYTitle("Frequency");h_residual_g1xcl->SetLabelSize(0.045,"XY");h_residual_g1xcl->SetTitleSize(0.045,"XY");
         h_residual_g1ycl = new TH1F(nameRes1Y,"",40,-1,1); h_residual_g1ycl->SetXTitle("Residual [mm]"); h_residual_g1ycl->SetYTitle("Frequency");h_residual_g1ycl->SetLabelSize(0.045,"XY");h_residual_g1ycl->SetTitleSize(0.045,"XY");
         h_residual_g2xcl = new TH1F(nameRes2X,"",40,-1,1); h_residual_g2xcl->SetXTitle("Residual [mm]"); h_residual_g2xcl->SetYTitle("Frequency");h_residual_g2xcl->SetLabelSize(0.045,"XY");h_residual_g2xcl->SetTitleSize(0.045,"XY");
         h_residual_g2ycl = new TH1F(nameRes2Y,"",40,-1,1); h_residual_g2ycl->SetXTitle("Residual [mm]"); h_residual_g2ycl->SetYTitle("Frequency");h_residual_g2ycl->SetLabelSize(0.045,"XY");h_residual_g2ycl->SetTitleSize(0.045,"XY");
         h_residual_g3xcl = new TH1F(nameRes3X,"",40,-1,1); h_residual_g3xcl->SetXTitle("Residual [mm]"); h_residual_g3xcl->SetYTitle("Frequency");h_residual_g3xcl->SetLabelSize(0.045,"XY");h_residual_g3xcl->SetTitleSize(0.045,"XY");
         h_residual_g3ycl = new TH1F(nameRes3Y,"",40,-1,1); h_residual_g3ycl->SetXTitle("Residual [mm]"); h_residual_g3ycl->SetYTitle("Frequency");h_residual_g3ycl->SetLabelSize(0.045,"XY");h_residual_g3ycl->SetTitleSize(0.045,"XY");
	}
	else
	if( fabs(mean_g2xcl)<0.5 && fabs(mean_g2ycl)<0.5 && fabs(mean_g3xcl)<0.5 && fabs(mean_g3ycl)<0.5)
	    {
	    cout<<"==========> Fourth Loop"<<endl;
         h_residual_g1xcl = new TH1F(nameRes1X,"",50,-2,2); h_residual_g1xcl->SetXTitle("Residual [mm]"); h_residual_g1xcl->SetYTitle("Frequency");h_residual_g1xcl->SetLabelSize(0.045,"XY");h_residual_g1xcl->SetTitleSize(0.045,"XY");
         h_residual_g1ycl = new TH1F(nameRes1Y,"",50,-2,2); h_residual_g1ycl->SetXTitle("Residual [mm]"); h_residual_g1ycl->SetYTitle("Frequency");h_residual_g1ycl->SetLabelSize(0.045,"XY");h_residual_g1ycl->SetTitleSize(0.045,"XY");
         h_residual_g2xcl = new TH1F(nameRes2X,"",50,-2,2); h_residual_g2xcl->SetXTitle("Residual [mm]"); h_residual_g2xcl->SetYTitle("Frequency");h_residual_g2xcl->SetLabelSize(0.045,"XY");h_residual_g2xcl->SetTitleSize(0.045,"XY");
         h_residual_g2ycl = new TH1F(nameRes2Y,"",50,-2,2); h_residual_g2ycl->SetXTitle("Residual [mm]"); h_residual_g2ycl->SetYTitle("Frequency");h_residual_g2ycl->SetLabelSize(0.045,"XY");h_residual_g2ycl->SetTitleSize(0.045,"XY");
         h_residual_g3xcl = new TH1F(nameRes3X,"",50,-2,2); h_residual_g3xcl->SetXTitle("Residual [mm]"); h_residual_g3xcl->SetYTitle("Frequency");h_residual_g3xcl->SetLabelSize(0.045,"XY");h_residual_g3xcl->SetTitleSize(0.045,"XY");
         h_residual_g3ycl = new TH1F(nameRes3Y,"",50,-2,2); h_residual_g3ycl->SetXTitle("Residual [mm]"); h_residual_g3ycl->SetYTitle("Frequency");h_residual_g3ycl->SetLabelSize(0.045,"XY");h_residual_g3ycl->SetTitleSize(0.045,"XY");
	}
	else
	if( fabs(mean_g2xcl)<1.0 && fabs(mean_g2ycl)<1.0 && fabs(mean_g3xcl)<1.0 && fabs(mean_g3ycl)<1.0)
	    {
	    cout<<"==========> Third Loop"<<endl;
         h_residual_g1xcl = new TH1F(nameRes1X,"",100,-3,3); h_residual_g1xcl->SetXTitle("Residual [mm]"); h_residual_g1xcl->SetYTitle("Frequency");h_residual_g1xcl->SetLabelSize(0.045,"XY");h_residual_g1xcl->SetTitleSize(0.045,"XY");
         h_residual_g1ycl = new TH1F(nameRes1Y,"",100,-3,3); h_residual_g1ycl->SetXTitle("Residual [mm]"); h_residual_g1ycl->SetYTitle("Frequency");h_residual_g1ycl->SetLabelSize(0.045,"XY");h_residual_g1ycl->SetTitleSize(0.045,"XY");
         h_residual_g2xcl = new TH1F(nameRes2X,"",100,-3,3); h_residual_g2xcl->SetXTitle("Residual [mm]"); h_residual_g2xcl->SetYTitle("Frequency");h_residual_g2xcl->SetLabelSize(0.045,"XY");h_residual_g2xcl->SetTitleSize(0.045,"XY");
         h_residual_g2ycl = new TH1F(nameRes2Y,"",100,-3,3); h_residual_g2ycl->SetXTitle("Residual [mm]"); h_residual_g2ycl->SetYTitle("Frequency");h_residual_g2ycl->SetLabelSize(0.045,"XY");h_residual_g2ycl->SetTitleSize(0.045,"XY");
         h_residual_g3xcl = new TH1F(nameRes3X,"",100,-3,3); h_residual_g3xcl->SetXTitle("Residual [mm]"); h_residual_g3xcl->SetYTitle("Frequency");h_residual_g3xcl->SetLabelSize(0.045,"XY");h_residual_g3xcl->SetTitleSize(0.045,"XY");
         h_residual_g3ycl = new TH1F(nameRes3Y,"",100,-3,3); h_residual_g3ycl->SetXTitle("Residual [mm]"); h_residual_g3ycl->SetYTitle("Frequency");h_residual_g3ycl->SetLabelSize(0.045,"XY");h_residual_g3ycl->SetTitleSize(0.045,"XY");
	}
	else
	if( fabs(mean_g2xcl)<2.0 && fabs(mean_g2ycl)<2.0 && fabs(mean_g3xcl)<2.0 && fabs(mean_g3ycl)<2.0)
	    {
	    cout<<"==========> Second Loop"<<endl;
         h_residual_g1xcl = new TH1F(nameRes1X,"",100,-4,3); h_residual_g1xcl->SetXTitle("Residual [mm]"); h_residual_g1xcl->SetYTitle("Frequency");h_residual_g1xcl->SetLabelSize(0.045,"XY");h_residual_g1xcl->SetTitleSize(0.045,"XY");
         h_residual_g1ycl = new TH1F(nameRes1Y,"",100,-4,3); h_residual_g1ycl->SetXTitle("Residual [mm]"); h_residual_g1ycl->SetYTitle("Frequency");h_residual_g1ycl->SetLabelSize(0.045,"XY");h_residual_g1ycl->SetTitleSize(0.045,"XY");
         h_residual_g2xcl = new TH1F(nameRes2X,"",100,-4,3); h_residual_g2xcl->SetXTitle("Residual [mm]"); h_residual_g2xcl->SetYTitle("Frequency");h_residual_g2xcl->SetLabelSize(0.045,"XY");h_residual_g2xcl->SetTitleSize(0.045,"XY");
         h_residual_g2ycl = new TH1F(nameRes2Y,"",100,-4,3); h_residual_g2ycl->SetXTitle("Residual [mm]"); h_residual_g2ycl->SetYTitle("Frequency");h_residual_g2ycl->SetLabelSize(0.045,"XY");h_residual_g2ycl->SetTitleSize(0.045,"XY");
         h_residual_g3xcl = new TH1F(nameRes3X,"",100,-4,3); h_residual_g3xcl->SetXTitle("Residual [mm]"); h_residual_g3xcl->SetYTitle("Frequency");h_residual_g3xcl->SetLabelSize(0.045,"XY");h_residual_g3xcl->SetTitleSize(0.045,"XY");
         h_residual_g3ycl = new TH1F(nameRes3Y,"",100,-4,3); h_residual_g3ycl->SetXTitle("Residual [mm]"); h_residual_g3ycl->SetYTitle("Frequency");h_residual_g3ycl->SetLabelSize(0.045,"XY");h_residual_g3ycl->SetTitleSize(0.045,"XY");
	}
	else
	    {
	    cout<<"==========> First Loop"<<endl;
         h_residual_g1xcl = new TH1F(nameRes1X,"",100,-6,3); h_residual_g1xcl->SetXTitle("Residual [mm]"); h_residual_g1xcl->SetYTitle("Frequency");h_residual_g1xcl->SetLabelSize(0.045,"XY");h_residual_g1xcl->SetTitleSize(0.045,"XY");
         h_residual_g1ycl = new TH1F(nameRes1Y,"",100,-6,3); h_residual_g1ycl->SetXTitle("Residual [mm]"); h_residual_g1ycl->SetYTitle("Frequency");h_residual_g1ycl->SetLabelSize(0.045,"XY");h_residual_g1ycl->SetTitleSize(0.045,"XY");
         h_residual_g2xcl = new TH1F(nameRes2X,"",100,-6,3); h_residual_g2xcl->SetXTitle("Residual [mm]"); h_residual_g2xcl->SetYTitle("Frequency");h_residual_g2xcl->SetLabelSize(0.045,"XY");h_residual_g2xcl->SetTitleSize(0.045,"XY");
         h_residual_g2ycl = new TH1F(nameRes2Y,"",100,-6,3); h_residual_g2ycl->SetXTitle("Residual [mm]"); h_residual_g2ycl->SetYTitle("Frequency");h_residual_g2ycl->SetLabelSize(0.045,"XY");h_residual_g2ycl->SetTitleSize(0.045,"XY");
         h_residual_g3xcl = new TH1F(nameRes3X,"",100,-6,3); h_residual_g3xcl->SetXTitle("Residual [mm]"); h_residual_g3xcl->SetYTitle("Frequency");h_residual_g3xcl->SetLabelSize(0.045,"XY");h_residual_g3xcl->SetTitleSize(0.045,"XY");
         h_residual_g3ycl = new TH1F(nameRes3Y,"",100,-6,3); h_residual_g3ycl->SetXTitle("Residual [mm]"); h_residual_g3ycl->SetYTitle("Frequency");h_residual_g3ycl->SetLabelSize(0.045,"XY");h_residual_g3ycl->SetTitleSize(0.045,"XY");
}

	// Print the mean position of each Detector
	fout<<shi_g1xcl<<"\t"<<shi_g1ycl<<"\t"<<shi_g2xcl<<"\t"<<shi_g2ycl<<"\t"<<shi_g3xcl<<"\t"<<shi_g3ycl<<"\t"<<endl;
	if (verbose)
	    cout<<"DEBUG  5"<<endl;
	
	
	int nnnn=0;
	
	
	if (verbose)
	    cout<<"DEBUG  6"<<endl;
	
	double 	tmpChiSquare1=0.0,tmpIntercept1=0.0 ;
	double 	tmpChiSquare2=0.0,tmpIntercept2=0.0 ;

	for(unsigned int i=0;i<vPos_g2xcl.size();i++){

	    TGraph* g1 = new TGraph();
	    TF1* f1 = new TF1("line1","[0]+[1]*x",0,900);
	    TGraph* g2 = new TGraph();
	    TF1* f2 = new TF1("line2","[0]+[1]*x",0,900);

	    
	    //cout<<"===========> "<<shi_g1xcl<<"\t"<<shi_g1ycl<<endl;
	    vPos_g1xcl[i] = vPos_g1xcl[i] - shi_g1xcl; vPos_g1ycl[i] = vPos_g1ycl[i] - shi_g1ycl;
	    vPos_g2xcl[i] = vPos_g2xcl[i] - shi_g2xcl; vPos_g2ycl[i] = vPos_g2ycl[i] - shi_g2ycl;      
	    vPos_g3xcl[i] = vPos_g3xcl[i] - shi_g3xcl; vPos_g3ycl[i] = vPos_g3ycl[i] - shi_g3ycl;
	    
	    h_Pos_g1xcl->Fill(vPos_g1xcl[i]); h_Pos_g1ycl->Fill(vPos_g1ycl[i]);
	    h_Pos_g2xcl->Fill(vPos_g2xcl[i]); h_Pos_g2ycl->Fill(vPos_g2ycl[i]);
	    h_Pos_g3xcl->Fill(vPos_g3xcl[i]); h_Pos_g3ycl->Fill(vPos_g3ycl[i]);

	    if (verbose)
		cout<<"DEBUG  7"<<endl;
	    
	    
	    g1->SetPoint(0, Trk1Pos, vPos_g1xcl[i]);
	    g1->SetPoint(1, Trk2Pos, vPos_g2xcl[i]);
	    g1->SetPoint(2, Trk3Pos, vPos_g3xcl[i]);
	    
	    if (verbose)
		cout<<"vPos_g1xcl["<<i<<"] = "<<vPos_g1xcl[i]<<"\tvPos_g2xcl["<<i<<"] = "<<vPos_g2xcl[i]<<"\tvPos_g3xcl["<<i<<"] = "<<vPos_g3xcl[i]<<endl;
	    
	    g1->Fit("line1","Q");
	    
	    double intercept1 = f1->GetParameter(0);
	    double slope1     = f1->GetParameter(1);
	    TrkX_Slope->Fill(slope1);
	    TrkX_Intercept->Fill(intercept1);
	    double Measured_g1xcl;
	    if (IncludeFirstTracker == 1)
	    	Measured_g1xcl = intercept1 + slope1*Trk1Pos;
	    else
	    	Measured_g1xcl = vPos_g1xcl[i];		// Reference Tracker position should not be changed.
	    double Measured_g2xcl = intercept1 + slope1*Trk2Pos;
	    double Measured_g3xcl = intercept1 + slope1*Trk3Pos;
	    
	    if (verbose)
		cout<<"intercept1 = "<<intercept1<<"\tslope1 = "<<slope1 <<endl;
	    
	    
	    h_residual_g1xcl->Fill(Measured_g1xcl-vPos_g1xcl[i]);
	    h_residual_g2xcl->Fill(Measured_g2xcl-vPos_g2xcl[i]);
	    h_residual_g3xcl->Fill(Measured_g3xcl-vPos_g3xcl[i]);

	    Trk1_ResXPosY->Fill(vPos_g1ycl[i],Measured_g1xcl-vPos_g1xcl[i]);
	    Trk1_ResXPosX->Fill(vPos_g1xcl[i],Measured_g1xcl-vPos_g1xcl[i]);

	    Trk2_ResXPosY->Fill(vPos_g2ycl[i],Measured_g2xcl-vPos_g2xcl[i]);
	    Trk2_ResXPosX->Fill(vPos_g2xcl[i],Measured_g2xcl-vPos_g2xcl[i]);

	    Trk3_ResXPosY->Fill(vPos_g3ycl[i],Measured_g3xcl-vPos_g3xcl[i]);
	    Trk3_ResXPosX->Fill(vPos_g3xcl[i],Measured_g3xcl-vPos_g3xcl[i]);

	    if (verbose)
		cout<<"Measured_g1xcl = "<<Measured_g1xcl<<"\t vPos_g2xcl = "<<vPos_g2xcl[i]<<"\tDifference = "<<Measured_g2xcl-vPos_g2xcl[i]<<endl;
	    delete f1; delete g1;
	    
	    if (verbose)
		cout<<"DEBUG  8"<<endl;
	    
	    g2->SetPoint(0,Trk1Pos,vPos_g1ycl[i]);
	    g2->SetPoint(1,Trk2Pos,vPos_g2ycl[i]);
	    g2->SetPoint(2,Trk3Pos,vPos_g3ycl[i]);
	    
	    // inclusive
	    
	    g2->Fit("line2","Q");
	    double intercept2 = f2->GetParameter(0);
	    double slope2     = f2->GetParameter(1);
	    TrkY_Slope->Fill(slope2);
	    TrkY_Intercept->Fill(intercept2);

	    double Measured_g1ycl;
	    if (IncludeFirstTracker == 1)
	    	Measured_g1ycl = intercept2 + slope2*Trk1Pos;
	    else
	    	Measured_g1ycl = vPos_g1ycl[i];	// Reference Tracker position should not be changed.
	    double Measured_g2ycl = intercept2 + slope2*Trk2Pos;
	    double Measured_g3ycl = intercept2 + slope2*Trk3Pos;
	    
	    if (verbose)
		cout<<"DEBUG  9"<<endl;

	    h_residual_g1ycl->Fill(Measured_g1ycl-vPos_g1ycl[i]);
	    h_residual_g2ycl->Fill(Measured_g2ycl-vPos_g2ycl[i]);
	    h_residual_g3ycl->Fill(Measured_g3ycl-vPos_g3ycl[i]);

	    Trk1_ResYPosY->Fill(vPos_g1ycl[i],Measured_g1ycl-vPos_g1ycl[i]);
	    Trk1_ResYPosX->Fill(vPos_g1xcl[i],Measured_g1ycl-vPos_g1ycl[i]);
	    
	    Trk2_ResYPosY->Fill(vPos_g2ycl[i],Measured_g2ycl-vPos_g2ycl[i]);
	    Trk2_ResYPosX->Fill(vPos_g2xcl[i],Measured_g2ycl-vPos_g2ycl[i]);
	    
	    Trk3_ResYPosY->Fill(vPos_g3ycl[i],Measured_g3ycl-vPos_g3ycl[i]);
	    Trk3_ResYPosX->Fill(vPos_g3xcl[i],Measured_g3ycl-vPos_g3ycl[i]);
	    

	    delete f2; delete g2;
	    
	    if (verbose)
		cout<<"DEBUG  11"<<endl;
	    
	    nnnn++;
	    

	tmpChiSquare1 += f1->GetChisquare();
	tmpIntercept1 += intercept1;
	tmpChiSquare2 += f2->GetChisquare();
	tmpIntercept2 += intercept2;
	}//for loop g2xcl size
	    
	foutChiSqr2<< tmpIntercept2/((double)(vPos_g2xcl.size())) <<"\t"<< tmpChiSquare2/((double)(vPos_g2xcl.size())) << "\t"<<0.0<<endl;
	foutChiSqr1<< tmpIntercept1/((double)(vPos_g2xcl.size())) <<"\t"<< tmpChiSquare1/((double)(vPos_g2xcl.size())) << "\t"<<0.0<<endl;
	
	gStyle->SetOptFit(1111);
	
	if (verbose)	    cout<<"DEBUG  13"<<endl;


	TH1F *residual_g1xcl_NoFit = (TH1F*) h_residual_g1xcl->Clone("residual_g1xcl_NoFit");
	TH1F *residual_g1ycl_NoFit = (TH1F*) h_residual_g1ycl->Clone("residual_g1ycl_NoFit");
	TH1F *residual_g2xcl_NoFit = (TH1F*) h_residual_g2xcl->Clone("residual_g2xcl_NoFit");
	TH1F *residual_g2ycl_NoFit = (TH1F*) h_residual_g2ycl->Clone("residual_g2ycl_NoFit");
	TH1F *residual_g3xcl_NoFit = (TH1F*) h_residual_g3xcl->Clone("residual_g3xcl_NoFit");
	TH1F *residual_g3ycl_NoFit = (TH1F*) h_residual_g3ycl->Clone("residual_g3ycl_NoFit");
	
	I2GFvalues myValues;
	
	myValues = I2GFmainLoop(h_residual_g1xcl,8,3,1);
	mean_g1xcl = myValues.mean; //
	sigma_g1xcl = myValues.sigma; //
	if (verbose)	    cout<<"DEBUG  17"<<endl;

	myValues = I2GFmainLoop(h_residual_g1ycl,8,3,1);
	mean_g1ycl = myValues.mean;
	sigma_g1ycl = myValues.sigma;
	if (verbose)	    cout<<"DEBUG  18"<<endl;

	myValues = I2GFmainLoop(h_residual_g2xcl,8,3,1);
	mean_g2xcl = myValues.mean; //sigmaEta5=myValues.sigma;
	sigma_g2xcl = myValues.sigma; //sigmaEta5=myValues.sigma;
	if (verbose)	    cout<<"DEBUG  13c"<<endl;

	myValues = I2GFmainLoop(h_residual_g2ycl,8,3,1);
	mean_g2ycl = myValues.mean; //
	sigma_g2ycl = myValues.sigma; //
	if (verbose)	    cout<<"DEBUG  14"<<endl;

	myValues = I2GFmainLoop(h_residual_g3xcl,8,3,1);
	mean_g3xcl = myValues.mean; //
	sigma_g3xcl = myValues.sigma; //
	if (verbose)	    cout<<"DEBUG  15"<<endl;

	myValues = I2GFmainLoop(h_residual_g3ycl,8,3,1);
	mean_g3ycl = myValues.mean;
	sigma_g3ycl = myValues.sigma;
	if (verbose)	    cout<<"DEBUG  16"<<endl;

	cout<<"residual mean: "<<mean_g1xcl<<"\t"<<mean_g1ycl<<"\t"<<mean_g2xcl<<"\t"<<mean_g2ycl<<"\t"<<mean_g3xcl<<"\t"<<mean_g3ycl<<endl;
	fout1<<sigma_g1xcl<<"\t"<<sigma_g1ycl<<"\t"<<sigma_g2xcl<<"\t"<<sigma_g2ycl<<"\t"<<sigma_g3xcl<<"\t"<<sigma_g3ycl<<endl;
	fout2<<mean_g1xcl<<"\t"<<mean_g1ycl<<"\t"<<mean_g2xcl<<"\t"<<mean_g2ycl<<"\t"<<mean_g3xcl<<"\t"<<mean_g3ycl<<endl;
	//fout1<<"residual mean: "<<mean_g1xcl<<"\t"<<mean_g1ycl<<"\t"<<mean_g2xcl<<"\t"<<mean_g2ycl<<"\t"<<mean_g3xcl<<"\t"<<mean_g3ycl<<endl;
	
	f->Write();
	f->Close();
	
	double factor = -0.1;
	
	if (IncludeFirstTracker == 1)
		{shi_g1xcl = mean_g1xcl*factor; shi_g1ycl = mean_g1ycl*factor; }
	else
		{shi_g1xcl = 0.0; shi_g1ycl = 0.0; }
	shi_g2xcl = mean_g2xcl*factor; shi_g2ycl = mean_g2ycl*factor; 
	shi_g3xcl = mean_g3xcl*factor; shi_g3ycl = mean_g3ycl*factor; 

	Tot_Shift_2X +=shi_g2xcl;
	Tot_Shift_2Y +=shi_g2ycl;
	Tot_Shift_3X +=shi_g3xcl;
	Tot_Shift_3Y +=shi_g3ycl;
	
	if (IncludeFirstTracker == 1)
	{
	if((mean_g1xcl>=-0.001 && mean_g1xcl<=0.001) && (mean_g1ycl>=-0.001 && mean_g1ycl<=0.001))
	if((mean_g2xcl>=-0.001 && mean_g2xcl<=0.001) && (mean_g2ycl>=-0.001 && mean_g2ycl<=0.001))
	    if((mean_g3xcl>=-0.001 && mean_g3xcl<=0.001) && (mean_g3ycl>=-0.001 && mean_g3ycl<=0.001))
		{
		    cout<<"find it...iterating "<<iterNb<<" times."<<endl;
		    break;
		}
	}
	else
	{
	if((mean_g2xcl>=-0.001 && mean_g2xcl<=0.001) && (mean_g2ycl>=-0.001 && mean_g2ycl<=0.001))
	    if((mean_g3xcl>=-0.001 && mean_g3xcl<=0.001) && (mean_g3ycl>=-0.001 && mean_g3ycl<=0.001))
		{
		    cout<<"find it...iterating "<<iterNb<<" times."<<endl;
		    break;
		}
	}
	//h_residual_g2xcl->Reset();
	//h_residual_g1xcl->Reset();
	//h_residual_g3xcl->Reset();
	
	if(iterNb>500) break;
	
	cout<<"iterating "<<iterNb<<" time done."<<endl;
    }//while(1)

    cout<<"Shift in 2X = "<<Tot_Shift_2X<<endl; 
    cout<<"Shift in 2Y = "<<Tot_Shift_2Y<<endl; 
    cout<<"Shift in 3X = "<<Tot_Shift_3X<<endl; 
    cout<<"Shift in 3Y = "<<Tot_Shift_3Y<<endl; 

    foutFshiPar<<"Shift_2X = "<<Tot_Shift_2X<<endl; 
    foutFshiPar<<"Shift_2Y = "<<Tot_Shift_2Y<<endl; 
    foutFshiPar<<"Shift_3X = "<<Tot_Shift_3X<<endl; 
    foutFshiPar<<"Shift_3Y = "<<Tot_Shift_3Y<<endl; 

    fout.close();
    fout1.close();
    fout2.close();
    foutChiSqr1.close();
    foutChiSqr2.close();
    foutFshiPar.close();
    // return 0;
} // entire script
