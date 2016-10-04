#include <vector>
#include "doubleGausFit_withHistParameter.C"
#include <iostream>
#include <vector>
#include <fstream>
#include <TTree.h>
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>

void tracking(string InputFileName , int RunNumber, double shiREF1X, double shiREF1Y, double shiREF2X, double shiREF2Y, double shiREF3X, double shiREF3Y, double Trk1Pos, double Trk2Pos, double Trk3Pos, double aREF2REF1, double aREF3REF1 )
{

	bool verbose = 0;
	bool IncludeFirstTracker = 1;

	string thestring = {"Position"};
	
	string txtfilename = InputFileName ;

	string DirResidual = "residual_txtFile/";
	string DirShiftPar = "shiftParameters/";
	string DirRootFile = "Residual_Rot_Trk_RootFile/";
    	string DirName_FinalShiftPar_RotShiftTrk = "FinalShiftPar_RotShiftTrk/";

	string shiftHead = "RotationBack_shiftParameters_";
	string rotateHead = "RotationBack_angles_";
	string residualHead = "RotationBack_residuals_";
	string ResidualRHead="RotationBack_Residual_";
	string chi2Head = "ResolutionChi2Angle_";

	string foutname = DirShiftPar+shiftHead+thestring+"_inclusive_"+std::to_string(RunNumber)+".txt";
	string fout1name = DirResidual+residualHead+thestring+"_inclusive_"+std::to_string(RunNumber)+".txt";
	string foutchi2name = DirResidual+chi2Head + thestring + "_inclusive_"+std::to_string(RunNumber)+".txt";
	string foutRotationName = DirResidual+rotateHead + thestring + "_inclusive_"+std::to_string(RunNumber)+".txt";
    	string foutFinalShiftPar = DirName_FinalShiftPar_RotShiftTrk+"Shift_Rotate_Parameter_R"+std::to_string(RunNumber)+".txt";

	fstream fin(txtfilename.c_str(),ios::in);
		if(!fin){cout<<"file not read"<<endl; return;}
		else cout<<"processing "<<txtfilename<<endl;

	fstream fout(foutname.c_str(),ios::out);
	fstream fout1(fout1name.c_str(),ios::out);
	fstream fout2(foutRotationName.c_str(),ios::out);
	fstream fout3(foutchi2name.c_str(),ios::out|ios::app);
    	fstream foutFshiPar(foutFinalShiftPar.c_str(),ios::out);

	// Define the variable for hit position
	double Pos_g1xcl=0.0, Pos_g1ycl=0.0;
	double Pos_g2xcl=0.0, Pos_g2ycl=0.0;
	double Pos_g3xcl=0.0, Pos_g3ycl=0.0;
	
	// Define vector to store all hit positions
	vector<double> vPos_g1xcl; vector<double> vPos_g1ycl;
	vector<double> vPos_g2xcl; vector<double> vPos_g2ycl;
	vector<double> vPos_g3xcl; vector<double> vPos_g3ycl;

	double CalculateCosTheta1(double x, double y, double x1,double y1); 

	Int_t nbLines=0;
	
    double Tot_Shift_2X = 0.0, Tot_Shift_2Y = 0.0;
    double Tot_Shift_3X = 0.0, Tot_Shift_3Y = 0.0;

	while(fin>>Pos_g1xcl>>Pos_g1ycl>>Pos_g2xcl>>Pos_g2ycl>>Pos_g3xcl>>Pos_g3ycl){	// Start of while loop
		vPos_g1xcl.push_back(Pos_g1xcl); vPos_g1ycl.push_back(Pos_g1ycl);
		vPos_g2xcl.push_back(Pos_g2xcl); vPos_g2ycl.push_back(Pos_g2ycl); 
		vPos_g3xcl.push_back(Pos_g3xcl); vPos_g3ycl.push_back(Pos_g3ycl);
		nbLines++;
	}		// End of while loop
	fin.close();	// Close the input file

	if (verbose)
		cout<<"ERROR 1 "<<endl;

	//double aEta5REF2;
	double temPos_g2xcl, temPos_g2ycl, temPos_g3xcl, temPos_g3ycl, temPos_g1xcl, temPos_g1ycl;

	double meanREF1X=0.0, meanREF1Y=0.0;
	double meanREF2X=0.0, meanREF2Y=0.0;
	double meanREF3X=0.0, meanREF3Y=0.0;
	double meanAngleREF2=0.0;
	double meanAngleREF3=0.0;

	double sigmag2xcl=0.0,sigmag2ycl=0.0,sigmag3xcl=0.0,sigmag3ycl=0.0,sigmag1xcl=0.0,sigmag1ycl=0.0;
	double totalAngleREF2=0.0, totalAngleREF3=0.0;
	double meanXChi2=0.0,meanYChi2=0.0; // chi square for tracks.

    fout<<"shift: "<<"shiREF1X"<<"\t"<<"shiREF1Y"<<"\t"<<"shiREF2X"<<"\t"<<"shiREF2Y"<<"\t"<<"shiREF3X"<<"\t"<<"shiREF3Y"<<endl;
	
	Int_t iterNb=0;
	while(1){
    	char rootfile[50]; sprintf(rootfile,"_iter%i_inclusive_R%i.root",iterNb,RunNumber);
		string outputrootname=DirRootFile+ResidualRHead+thestring+rootfile;
		//if (verbose)
			cout<<"outputroot file name :  "<< outputrootname <<endl;
		TFile* f = new TFile(outputrootname.c_str(),"recreate");
		iterNb++;
		char name1X[15];sprintf(name1X,"posg1xcl_%i",iterNb); char name1Y[15];sprintf(name1Y,"posg1ycl_%i",iterNb);
		char name2X[15];sprintf(name2X,"posg2xcl_%i",iterNb); char name2Y[15];sprintf(name2Y,"posg2ycl_%i",iterNb);
		char name3X[15];sprintf(name3X,"posg3xcl_%i",iterNb); char name3Y[15];sprintf(name3Y,"posg3ycl_%i",iterNb);
		
		TH1F *hPos_g1xcl = new TH1F(name1X,"",500,-60,100); hPos_g1xcl->SetXTitle("mm"); hPos_g1xcl->SetYTitle("Frequency");hPos_g1xcl->SetLabelSize(0.045,"XY");hPos_g1xcl->SetTitleSize(0.045,"XY");
		TH1F *hPos_g1ycl = new TH1F(name1Y,"",500,-60,100); hPos_g1ycl->SetXTitle("mm"); hPos_g1ycl->SetYTitle("Frequency");hPos_g1ycl->SetLabelSize(0.045,"XY");hPos_g1ycl->SetTitleSize(0.045,"XY");  
		TH1F* hPos_g2xcl = new TH1F(name2X,"",500,-60,100); hPos_g2xcl->SetXTitle("mm"); hPos_g2xcl->SetYTitle("Frequency");hPos_g2xcl->SetLabelSize(0.045,"XY");hPos_g2xcl->SetTitleSize(0.045,"XY");
		TH1F* hPos_g2ycl = new TH1F(name2Y,"",500,-60,100); hPos_g2ycl->SetXTitle("mm"); hPos_g2ycl->SetYTitle("Frequency");hPos_g2ycl->SetLabelSize(0.045,"XY");hPos_g2ycl->SetTitleSize(0.045,"XY");  
		TH1F* hPos_g3xcl = new TH1F(name3X,"",500,-60,100); hPos_g3xcl->SetXTitle("mm"); hPos_g3xcl->SetYTitle("Frequency");hPos_g3xcl->SetLabelSize(0.045,"XY");hPos_g3xcl->SetTitleSize(0.045,"XY");
		TH1F* hPos_g3ycl = new TH1F(name3Y,"",500,-60,100); hPos_g3ycl->SetXTitle("mm"); hPos_g3ycl->SetYTitle("Frequency");hPos_g3ycl->SetLabelSize(0.045,"XY");hPos_g3ycl->SetTitleSize(0.045,"XY");  
		
		char nameRes1X[20];sprintf(nameRes1X,"residualg1xcl_%i",iterNb);char nameRes1Y[20];sprintf(nameRes1Y,"residualg1ycl_%i",iterNb);
		char nameRes2X[20];sprintf(nameRes2X,"residualg2xcl_%i",iterNb);char nameRes2Y[20];sprintf(nameRes2Y,"residualg2ycl_%i",iterNb);
		char nameRes3X[20];sprintf(nameRes3X,"residualg3xcl_%i",iterNb);char nameRes3Y[20];sprintf(nameRes3Y,"residualg3ycl_%i",iterNb);
		
		TH1F* residualg1xcl = new TH1F(nameRes1X,"",200,-2.0,2.0); residualg1xcl->SetXTitle("mm"); residualg1xcl->SetYTitle("Frequency");residualg1xcl->SetLabelSize(0.045,"XY");residualg1xcl->SetTitleSize(0.045,"XY");
		TH1F* residualg1ycl = new TH1F(nameRes1Y,"",200,-2.0,2.0); residualg1ycl->SetXTitle("mm"); residualg1ycl->SetYTitle("Frequency");residualg1ycl->SetLabelSize(0.045,"XY");residualg1ycl->SetTitleSize(0.045,"XY");
		TH1F* residualg2xcl = new TH1F(nameRes2X,"",100,-2.0,2.0); residualg2xcl->SetXTitle("Residual [mm]"); residualg2xcl->SetYTitle("Frequency");residualg2xcl->SetLabelSize(0.045,"XY");residualg2xcl->SetTitleSize(0.045,"XY");
		TH1F* residualg2ycl = new TH1F(nameRes2Y,"",100,-2.0,2.0); residualg2ycl->SetXTitle("Residual [mm]"); residualg2ycl->SetYTitle("Frequency");residualg2ycl->SetLabelSize(0.045,"XY");residualg2ycl->SetTitleSize(0.045,"XY");
		TH1F* residualg3xcl = new TH1F(nameRes3X,"",100,-2.0,2.0); residualg3xcl->SetXTitle("Residual [mm]"); residualg3xcl->SetYTitle("Frequency");residualg3xcl->SetLabelSize(0.045,"XY");residualg3xcl->SetTitleSize(0.045,"XY");
		TH1F* residualg3ycl = new TH1F(nameRes3Y,"",100,-2.0,2.0); residualg3ycl->SetXTitle("Residual [mm]"); residualg3ycl->SetYTitle("Frequency");residualg3ycl->SetLabelSize(0.045,"XY");residualg3ycl->SetTitleSize(0.045,"XY");
		
		
		TH1F* angleREF2 = new TH1F("angleREF2","Rotation angle distribution of REF1 and REF2",200,-2.0,2.0); angleREF2->SetXTitle("Angle [radian]"); angleREF2->SetYTitle("Frequency");
		TH1F* angleREF3 = new TH1F("angleREF3","Rotation angle distribution of REF3 and REF2",200,-2.0,2.0); angleREF3->SetXTitle("Angle [radian]"); angleREF3->SetYTitle("Frequency");
		
		TH1F* xTrackChi2 = new TH1F("XTrackChi2","Chi square of tracks in X projection",200,0,10); xTrackChi2->SetXTitle("#chi^{2} of track in X"); xTrackChi2->SetYTitle("Frequency"); xTrackChi2->SetTitleSize(0.04,"XY"); xTrackChi2->SetLabelSize(0.04,"XY");
		TH1F* yTrackChi2 = new TH1F("YTrackChi2","Chi square of tracks in Y projection",200,0,10); yTrackChi2->SetXTitle("#chi^{2} of track in Y"); yTrackChi2->SetYTitle("Frequency"); yTrackChi2->SetTitleSize(0.04,"XY"); yTrackChi2->SetLabelSize(0.04,"XY");
		
		if (verbose)
			cout<<"Successfully Defined all histogram"<<endl;
		
		fout<<"shift: "<<shiREF1X<<"\t"<<shiREF1Y<<"\t"<<shiREF2X<<"\t"<<shiREF2Y<<"\t"<<shiREF3X<<"\t"<<shiREF3Y<<endl;
		fout2<<"rotation: "<<aREF2REF1<<"\t"<<aREF3REF1<<endl;

		if (verbose){
			cout<<"shift: "<<shiREF1X<<"\t"<<shiREF1Y<<"\t"<<shiREF2X<<"\t"<<shiREF2Y<<"\t"<<shiREF3X<<"\t"<<shiREF3Y<<endl;
			cout<<"rotation: "<<aREF2REF1<<"\t"<<aREF3REF1<<endl;
			cout<<"===============================>vPos size = "<< vPos_g1xcl.size() <<endl;
		}
		int nnnn=0;
		for(Int_t i=0;i<vPos_g1xcl.size();i++){
		//shift
			if (verbose)
			cout<<"ERROR 2 "<<endl;
			vPos_g1xcl[i] = vPos_g1xcl[i] - shiREF1X; vPos_g1ycl[i] = vPos_g1ycl[i] - shiREF1Y;
			vPos_g2xcl[i] = vPos_g2xcl[i] - shiREF2X; vPos_g2ycl[i] = vPos_g2ycl[i] - shiREF2Y;      
			vPos_g3xcl[i] = vPos_g3xcl[i] - shiREF3X; vPos_g3ycl[i] = vPos_g3ycl[i] - shiREF3Y;

			temPos_g1xcl = vPos_g1xcl[i]; temPos_g1ycl = vPos_g1ycl[i]; 
			temPos_g2xcl = vPos_g2xcl[i]; temPos_g2ycl = vPos_g2ycl[i]; 
			temPos_g3xcl = vPos_g3xcl[i]; temPos_g3ycl = vPos_g3ycl[i]; 
		
			//rotate back
			vPos_g2xcl[i]=temPos_g2xcl*cos(aREF2REF1)-temPos_g2ycl*sin(aREF2REF1);
			vPos_g2ycl[i]=temPos_g2xcl*sin(aREF2REF1)+temPos_g2ycl*cos(aREF2REF1);
			vPos_g3xcl[i]=temPos_g3xcl*cos(aREF3REF1)-temPos_g3ycl*sin(aREF3REF1);
			vPos_g3ycl[i]=temPos_g3xcl*sin(aREF3REF1)+temPos_g3ycl*cos(aREF3REF1);
		
			hPos_g1xcl->Fill(vPos_g1xcl[i]); hPos_g1ycl->Fill(vPos_g1ycl[i]);
			hPos_g2xcl->Fill(vPos_g2xcl[i]); hPos_g2ycl->Fill(vPos_g2ycl[i]);
			hPos_g3xcl->Fill(vPos_g3xcl[i]); hPos_g3ycl->Fill(vPos_g3ycl[i]);
		
			TGraph* g1 = new TGraph();
			g1->SetPoint(0,Trk1Pos, vPos_g1xcl[i]);
			g1->SetPoint(1,Trk2Pos, vPos_g2xcl[i]);
			g1->SetPoint(2,Trk3Pos, vPos_g3xcl[i]);
		
			TF1* f1 = new TF1("line1","[0]+[1]*x",0,900);
			g1->Fit("line1","Q");
			double intercept1 = f1->GetParameter(0);
			double slope1     = f1->GetParameter(1);
			double Measuredg1xcl;
			if (IncludeFirstTracker)
				Measuredg1xcl = intercept1 + slope1*Trk1Pos;
			else
				Measuredg1xcl = vPos_g1xcl[i];
			double Measuredg2xcl = intercept1 + slope1*Trk2Pos;
			double Measuredg3xcl = intercept1 + slope1*Trk3Pos;
			if (verbose)
				cout<<"measured = "<< Measuredg2xcl <<"\tvPos = "<< vPos_g2xcl[i] <<"\tresidualg2xcl = "<<Measuredg2xcl-vPos_g2xcl[i]<<endl;
			residualg1xcl->Fill(Measuredg1xcl-vPos_g1xcl[i]);
			residualg2xcl->Fill(Measuredg2xcl-vPos_g2xcl[i] );
			residualg3xcl->Fill(Measuredg3xcl-vPos_g3xcl[i] );
			xTrackChi2->Fill(f1->GetChisquare());
			if (verbose)
				cout<<f1->GetChisquare()<<"\t";
			delete f1; delete g1;
		
			TGraph* g2 = new TGraph();
			g2->SetPoint(0,Trk1Pos, vPos_g1ycl[i]);
			g2->SetPoint(1,Trk2Pos, vPos_g2ycl[i] );
			g2->SetPoint(2,Trk3Pos, vPos_g3ycl[i] );
		
			if (verbose)
				cout<<"test"<<  endl;
		
			TF1* f2 = new TF1("line2","[0]+[1]*x",0,900);
			g2->Fit("line2","Q");
			double intercept2 = f2->GetParameter(0);
			double slope2     = f2->GetParameter(1);
			double Measuredg1ycl;
			if (IncludeFirstTracker)
				Measuredg1ycl = intercept2 + slope2*Trk1Pos;
			else
				Measuredg1ycl = vPos_g1ycl[i];
			double Measuredg2ycl = intercept2 + slope2*Trk2Pos;
			double Measuredg3ycl = intercept2 + slope2*Trk3Pos;
			
			residualg1ycl->Fill(Measuredg1ycl-vPos_g1ycl[i]);
			residualg2ycl->Fill(Measuredg2ycl-vPos_g2ycl[i] );
			residualg3ycl->Fill(Measuredg3ycl-vPos_g3ycl[i] );
		
			yTrackChi2->Fill(f2->GetChisquare());
		
			if (verbose)
				cout<<f2->GetChisquare()<<endl;
			delete f2; delete g2;
		
			double cosineREF2 = CalculateCosTheta1(vPos_g1xcl[i],vPos_g1ycl[i],vPos_g2xcl[i],vPos_g2ycl[i]);
			double cosineREF3 = CalculateCosTheta1(vPos_g1xcl[i],vPos_g1ycl[i],vPos_g3xcl[i],vPos_g3ycl[i]);
			angleREF2->Fill(cosineREF2);
			angleREF3->Fill(cosineREF3); 
			
			nnnn++;
		} //for loop

		//cout<<"after for loop"<<endl;
		gStyle->SetOptFit(1111);
		
		I2GFvalues myValues;
		
		myValues = I2GFmainLoop(residualg1xcl, 1, 3, 1);
		meanREF1X = myValues.mean; sigmag1xcl=myValues.sigma;
		if (verbose) cout<<"=========================>Passed 1 "<<endl;
		
		myValues = I2GFmainLoop(residualg1ycl, 1, 3, 1);
		meanREF1Y = myValues.mean; sigmag1ycl=myValues.sigma;
		if (verbose) cout<<"=========================>Passed 2 "<<endl;
		
		
		myValues = I2GFmainLoop(residualg2xcl, 8, 3, 1);
		meanREF2X = myValues.mean; sigmag2xcl=myValues.sigma;
		if (verbose) cout<<"=========================>Passed 3 "<<endl;
		
		myValues = I2GFmainLoop(residualg2ycl, 8, 3, 1);
		meanREF2Y = myValues.mean; sigmag2ycl=myValues.sigma;
		if (verbose) cout<<"=========================>Passed 4 "<<endl;
		
		myValues = I2GFmainLoop(residualg3xcl, 8, 3, 1);
		meanREF3X = myValues.mean; sigmag3xcl=myValues.sigma;
		if (verbose) cout<<"=========================>Passed 5 "<<endl;
		
		myValues = I2GFmainLoop(residualg3ycl, 8, 3, 1);
		meanREF3Y = myValues.mean; sigmag3ycl=myValues.sigma;
		if (verbose) cout<<"=========================>Passed 6 "<<endl;
		
		myValues = I2GFmainLoop(angleREF2, 8, 3, 1);
		if (verbose) cout<<"=========================>Passed 8 "<<endl;

		meanAngleREF2=myValues.mean;
		myValues = I2GFmainLoop(angleREF3, 8, 3, 1);
		if (verbose) cout<<"=========================>Passed 9 "<<endl;

		meanAngleREF3=myValues.mean;
		
		meanXChi2=xTrackChi2->GetMean();
		meanYChi2=yTrackChi2->GetMean();
		
		
		//if (verbose)
		cout<<"residual mean: "<<meanREF1X<<"\t"<<meanREF1Y<<"\t"<<meanREF2X<<"\t"<<meanREF2Y<<"\t"<<meanREF3X<<"\t"<<meanREF3Y<<"\t"<<meanAngleREF3<<"\t"<<meanAngleREF2<<endl;
		fout1<<meanREF1X<<"\t"<<meanREF1Y<<"\t"<<meanREF2X<<"\t"<<meanREF2Y<<"\t"<<meanREF3X<<"\t"<<meanREF3Y<<endl;
		if (iterNb != 1)
		{
		Tot_Shift_2X +=shiREF2X;
    		Tot_Shift_2Y +=shiREF2Y;
    		Tot_Shift_3X +=shiREF3X;
    		Tot_Shift_3Y +=shiREF3Y;
		totalAngleREF2 += aREF2REF1;
		totalAngleREF3 += aREF3REF1;
		}

		fout3<<sigmag1xcl<<"\t"<<sigmag1ycl<<"\t"<<sigmag2xcl<<"\t"<<sigmag2ycl<<"\t"<</*sigmaUVA3X<<"\t"<<sigmaUVA3Y<<*/"\t"<<sigmag3xcl<<"\t"<<sigmag3ycl<<"\t"<<totalAngleREF2<<"\t"<</*totalAngleUVA3<<*/"\t"<<totalAngleREF3<<"\t"<<meanXChi2<<"\t"<<meanYChi2<<endl;
		 if (verbose) 
		cout<<sigmag1xcl<<"\t"<<sigmag1ycl<<"\t"<<sigmag2xcl<<"\t"<<sigmag2ycl<<"\t"<</*sigmaUVA3X<<"\t"<<sigmaUVA3Y<<*/"\t"<<sigmag3xcl<<"\t"<<sigmag3ycl<<"\t"<<totalAngleREF2<<"\t"<</*totalAngleUVA3<<*/"\t"<<totalAngleREF3<<"\t"<<meanXChi2<<"\t"<<meanYChi2<<endl;

		 if (verbose) 
			cout<<"\n\n++++++++++++++++++++++++++++++++++++++++++\n\n"<<endl;
		 //if (verbose) 
		//	cout<<"meanREF2X = "<<meanREF2X <<"\tmeanREF2Y = "<<meanREF2Y<<"\tmeanREF3X = "<<meanREF3X<<"\tmeanREF3Y = "<<meanREF3Y<<"\tmeanAngleREF3 = "<<meanAngleREF3<<"\tmeanAngleREF2 = "<<meanAngleREF2<<endl;
		 //if (verbose) 
		//	cout<<"\n\n++++++++++++++++++++++++++++++++++++++++++\n\n"<<endl;

		
		f->Write();
		f->Close();
		
		if (IncludeFirstTracker)
		{
			if((meanREF1X>=-0.005 && meanREF1X<=0.005) && (meanREF1Y>=-0.005 && meanREF1Y<=0.005))
			if((meanREF2X>=-0.005 && meanREF2X<=0.005) && (meanREF2Y>=-0.005 && meanREF2Y<=0.005))
			if((meanREF3X>=-0.005 && meanREF3X<=0.005) && (meanREF3Y>=-0.005 && meanREF3Y<=0.005))
			if(meanAngleREF3>=-0.005 && meanAngleREF3<=0.005 && meanAngleREF2>=-0.005 && meanAngleREF2<=0.005)
			{
			cout<<"find it...iterating "<<iterNb<<" times."<<endl;
			break;
			}
		}
		else
		{
			if((meanREF2X>=-0.005 && meanREF2X<=0.005) && (meanREF2Y>=-0.005 && meanREF2Y<=0.005))
			if((meanREF3X>=-0.005 && meanREF3X<=0.005) && (meanREF3Y>=-0.005 && meanREF3Y<=0.005))
			if(meanAngleREF3>=-0.005 && meanAngleREF3<=0.005 && meanAngleREF2>=-0.005 && meanAngleREF2<=0.005)
			{
			cout<<"find it...iterating "<<iterNb<<" times."<<endl;
			break;
			}
		}
		if(iterNb==500) break;
		cout<<"iterating "<<iterNb<<" time done."<<endl;

		double factor = -0.1;
		if (IncludeFirstTracker)
		{		shiREF1X = meanREF1X*factor; 		shiREF1Y = meanREF1Y*factor; 	}
		else
		{		shiREF1X = 0.0;				shiREF1Y = 0.0; 		}
		shiREF2X = meanREF2X*factor; shiREF2Y = meanREF2Y*factor; 
		shiREF3X = meanREF3X*factor; shiREF3Y = meanREF3Y*factor; 
		aREF2REF1 = meanAngleREF2;
		aREF3REF1 = meanAngleREF3;
		
	}//while(1)
	fout.close();
	fout1.close();
	fout2.close();


    cout<<"Shift in 2X = "<<Tot_Shift_2X<<endl;
    cout<<"Shift in 2Y = "<<Tot_Shift_2Y<<endl;
    cout<<"Shift in 3X = "<<Tot_Shift_3X<<endl;
    cout<<"Shift in 3Y = "<<Tot_Shift_3Y<<endl;
    cout<<"totalAngleREF2 = "<<totalAngleREF2<<endl;
    cout<<"totalAngleREF3 = "<<totalAngleREF3<<endl;

    foutFshiPar<<"Shift_2X_Rot = "<<Tot_Shift_2X<<endl;
    foutFshiPar<<"Shift_2Y_Rot = "<<Tot_Shift_2Y<<endl;
    foutFshiPar<<"Shift_3X_Rot = "<<Tot_Shift_3X<<endl;
    foutFshiPar<<"Shift_3Y_Rot = "<<Tot_Shift_3Y<<endl;
    foutFshiPar<<"TotalAngleREF2 = "<<totalAngleREF2<<endl;
    foutFshiPar<<"TotalAngleREF3 = "<<totalAngleREF3<<endl;

} // entire script
		
int AlignTrackers_shift_rotate(string name, int RunNumber, double shiREF1X, double shiREF1Y, double shiREF2X, double shiREF2X_TrkAlign, double shiREF2Y, double shiREF2Y_TrkAlign, double shiREF3X, double shiREF3X_TrkAlign, double shiREF3Y, double shiREF3Y_TrkAlign, double Trk1Pos, double Trk2Pos, double Trk3Pos, double aREF2REF1, double aREF3REF1  )
{
    	bool shiftOrigin = 1;

	cout<<"\n=================================================\n"<<endl;
	cout<<"\tPrint Input Parameters:"<<endl;
	cout<<"\n================================================="<<endl;
	cout<<"Name of input file = "<<name<<endl;
	cout<<"Run Number = "<<RunNumber<<endl;
	cout<<"Detector Positions (in mm):"<<endl;
	cout<<"\tTracker 1 position = "<<Trk1Pos<<endl;
	cout<<"\tTracker 2 position = "<<Trk2Pos<<endl;
	cout<<"\tTracker 3 position = "<<Trk3Pos<<endl<<endl;
	cout<<"Shift Parameters (in mm):"<<endl;
	cout<<"\tTrk 1X: Mean = "<<shiREF1X<<endl;
	cout<<"\tTrk 1Y: Mean = "<<shiREF1Y<<endl;
	cout<<"\tTrk 2X: Mean = "<<shiREF2X<<"\tDetector Shift = "<<shiREF2X_TrkAlign<<endl;
	cout<<"\tTrk 2Y: Mean = "<<shiREF2Y<<"\tDetector Shift = "<<shiREF2Y_TrkAlign<<endl;
	cout<<"\tTrk 3X: Mean = "<<shiREF3X<<"\tDetector Shift = "<<shiREF3X_TrkAlign<<endl;
	cout<<"\tTrk 3Y: Mean = "<<shiREF3Y<<"\tDetector Shift = "<<shiREF3Y_TrkAlign<<endl;
	cout<<"\tAngle between Trk 2 and 1 = "<<aREF2REF1<<endl;
	cout<<"\tAngle between Trk 3 and 1 = "<<aREF3REF1<<endl;
	cout<<"\n================================================="<<endl;

	if(shiftOrigin)
	{
		shiREF1X += 0.0;
		shiREF1Y += 0.0;
		shiREF2X += 0.0+shiREF2X_TrkAlign;
		shiREF2Y += 0.0+shiREF2Y_TrkAlign;
		shiREF3X += 0.0+shiREF3X_TrkAlign;
		shiREF3Y += 0.0+shiREF3Y_TrkAlign;
		aREF2REF1+= 0.0;
		aREF3REF1+= 0.0;
	}

	for(int i=0;i<1;i++) tracking(name, RunNumber, shiREF1X, shiREF1Y, shiREF2X, shiREF2Y, shiREF3X, shiREF3Y, Trk1Pos, Trk2Pos, Trk3Pos, aREF2REF1, aREF3REF1 );  
	return 0;
}

double CalculateCosTheta1(double x, double y, double x1,double y1){
	//double cosineTheta = ( x*x1 + y*y1 )/(x*x+y*y);
	double sineTheta = (x1*y - x*y1)/(x*x + y*y);
	//if(cosineTheta>1) cosineTheta=2-cosineTheta;
	//cout<<sineTheta<<endl;
	return asin(sineTheta);
}
