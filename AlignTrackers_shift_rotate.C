#include <vector>
#include "doubleGausFit_withHistParameter.C"
#include <iostream>
#include <vector>
#include <fstream>
#include <TTree.h>
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>

void tracking(string InputFileName , int RunNumber, double shiREF1X, double shiREF1Y, double shiREF2X, double shiREF2Y, double shiREF3X, double shiREF3Y, double Trk1Pos, double Trk2Pos, double Trk3Pos, double aREF2REF1, double aREF3REF1 ){

    cout<<"aREF3REF1 = "<<aREF3REF1<<"\taREF2REF1 = "<<aREF2REF1<<endl;

bool verbose = 0;
cout<<"Program Start"<<endl;
  string thestring = {"Position"};
  string txtfilename = InputFileName ;

  string DirResidual = "residual_txtFile/";
  string DirShiftPar = "shiftParameters/";
  string DirRootFile = "Residual_Rot_Trk_RootFile/";

  string shiftHead = "RotationBack_shiftParameters_";
  string rotateHead = "RotationBack_angles_";
  string residualHead = "RotationBack_residuals_";
  string ResidualRHead="RotationBack_Residual_";
  string chi2Head = "ResolutionChi2Angle_";
  string foutname = DirShiftPar+shiftHead+thestring+"_exclusive_"+std::to_string(RunNumber)+".txt";
  string fout1name = DirResidual+residualHead+thestring+"_exclusive_"+std::to_string(RunNumber)+".txt";
  string foutchi2name = DirResidual+chi2Head + thestring + "_exclusive_"+std::to_string(RunNumber)+".txt";
  string foutRotationName = DirResidual+rotateHead + thestring + "_exclusive_"+std::to_string(RunNumber)+".txt";
  fstream fin(txtfilename.c_str(),ios::in);
  if(!fin){cout<<"file not read"<<endl; return;}
  else cout<<"processing "<<txtfilename<<endl;
  fstream fout(foutname.c_str(),ios::out);
  fstream fout1(fout1name.c_str(),ios::out);
  fstream fout2(foutRotationName.c_str(),ios::out);
  fstream fout3(foutchi2name.c_str(),ios::out|ios::app);
  double Pos_g1xcl=0.0, Pos_g1ycl=0.0;
  double Pos_g2xcl=0.0, Pos_g2ycl=0.0;
  double Pos_g3xcl=0.0, Pos_g3ycl=0.0;
  vector<double> vPos_g1xcl; vector<double> vPos_g1ycl;
  vector<double> vPos_g2xcl; vector<double> vPos_g2ycl;
  vector<double> vPos_g3xcl; vector<double> vPos_g3ycl;
 double CalculateCosTheta1(double x, double y, double x1,double y1); 

  Int_t nbLines=0;
  while(fin>>Pos_g1xcl>>Pos_g1ycl>>Pos_g2xcl>>Pos_g2ycl>>/*pUVA3X>>pUVA3Y>>*/Pos_g3xcl>>Pos_g3ycl/*>>pEta5*/){
	vPos_g1xcl.push_back(Pos_g1xcl); vPos_g1ycl.push_back(Pos_g1ycl);
	vPos_g2xcl.push_back(Pos_g2xcl); vPos_g2ycl.push_back(Pos_g2ycl); vPos_g3xcl.push_back(Pos_g3xcl); vPos_g3ycl.push_back(Pos_g3ycl);
    nbLines++;
  }
  fin.close();

  if (verbose)
  	cout<<"ERROR 1 "<<endl;

  //double aEta5REF2;
  double temPos_g2xcl, temPos_g2ycl, temPos_g3xcl, temPos_g3ycl, temPos_g1xcl, temPos_g1ycl;

  double meanREF1X=0.0, meanREF1Y=0.0;
  double meanREF2X=0.0, meanREF2Y=0.0;
  double meanREF3X=0.0, meanREF3Y=0.0;

  double meanAngleREF2=0.0;
  double meanAngleREF3=0.0;

  double sigmag2xcl=0.0,sigmag2ycl=0.0,sigmag3xcl=0.0,sigmag3ycl=0.0,/*sigmaUVA3X=0.0,sigmaUVA3Y=0.0,*/sigmag1xcl=0.0,sigmag1ycl=0.0;
  double totalAngleREF2=0.0,/* totalAngleUVA3=0.0,*/ totalAngleREF3=0.0;
  double meanXChi2=0.0,meanYChi2=0.0; // chi square for tracks.

    fout<<"shift: "<<"shiREF1X"<<"\t"<<"shiREF1Y"<<"\t"<<"shiREF2X"<<"\t"<<"shiREF2Y"<<"\t"<</*shiUVA3X<<"\t"<<shiUVA3Y<<"\t"<<*/"shiREF3X"<<"\t"<<"shiREF3Y"<<endl;
  Int_t iterNb=0;
  while(1){
    char rootfile[50]; sprintf(rootfile,"_iter%i_exclusive_R%i.root",iterNb,RunNumber);
    string outputrootname=DirRootFile+ResidualRHead+thestring+rootfile;
    //if (verbose)
  	cout<<"outputroot file name :  "<< outputrootname <<endl;
    TFile* f = new TFile(outputrootname.c_str(),"recreate");
    iterNb++;
    char name1X[15];sprintf(name1X,"posg1xcl_%i",iterNb); char name1Y[15];sprintf(name1Y,"posg1ycl_%i",iterNb);
    char name2X[15];sprintf(name2X,"posg2xcl_%i",iterNb); char name2Y[15];sprintf(name2Y,"posg2ycl_%i",iterNb);
    char name3X[15];sprintf(name3X,"posg3xcl_%i",iterNb); char name3Y[15];sprintf(name3Y,"posg3ycl_%i",iterNb);

    TH1F *hPos_g1xcl = new TH1F(name1X,"",500,-60,60); hPos_g1xcl->SetXTitle("mm"); hPos_g1xcl->SetYTitle("Frequency");hPos_g1xcl->SetLabelSize(0.045,"XY");hPos_g1xcl->SetTitleSize(0.045,"XY");
    TH1F *hPos_g1ycl = new TH1F(name1Y,"",500,-60,60); hPos_g1ycl->SetXTitle("mm"); hPos_g1ycl->SetYTitle("Frequency");hPos_g1ycl->SetLabelSize(0.045,"XY");hPos_g1ycl->SetTitleSize(0.045,"XY");  
    TH1F* hPos_g2xcl = new TH1F(name2X,"",500,-60,60); hPos_g2xcl->SetXTitle("mm"); hPos_g2xcl->SetYTitle("Frequency");hPos_g2xcl->SetLabelSize(0.045,"XY");hPos_g2xcl->SetTitleSize(0.045,"XY");
    TH1F* hPos_g2ycl = new TH1F(name2Y,"",500,-60,60); hPos_g2ycl->SetXTitle("mm"); hPos_g2ycl->SetYTitle("Frequency");hPos_g2ycl->SetLabelSize(0.045,"XY");hPos_g2ycl->SetTitleSize(0.045,"XY");  
    TH1F* hPos_g3xcl = new TH1F(name3X,"",500,-60,60); hPos_g3xcl->SetXTitle("mm"); hPos_g3xcl->SetYTitle("Frequency");hPos_g3xcl->SetLabelSize(0.045,"XY");hPos_g3xcl->SetTitleSize(0.045,"XY");
    TH1F* hPos_g3ycl = new TH1F(name3Y,"",500,-60,60); hPos_g3ycl->SetXTitle("mm"); hPos_g3ycl->SetYTitle("Frequency");hPos_g3ycl->SetLabelSize(0.045,"XY");hPos_g3ycl->SetTitleSize(0.045,"XY");  

    char nameRes1X[20];sprintf(nameRes1X,"residualg1xcl_%i",iterNb);char nameRes1Y[20];sprintf(nameRes1Y,"residualg1ycl_%i",iterNb);
    char nameRes2X[20];sprintf(nameRes2X,"residualg2xcl_%i",iterNb);char nameRes2Y[20];sprintf(nameRes2Y,"residualg2ycl_%i",iterNb);
    char nameRes3X[20];sprintf(nameRes3X,"residualg3xcl_%i",iterNb);char nameRes3Y[20];sprintf(nameRes3Y,"residualg3ycl_%i",iterNb);

    TH1F* residualg1xcl = new TH1F(nameRes1X,"",200,-2,2); residualg1xcl->SetXTitle("mm"); residualg1xcl->SetYTitle("Frequency");residualg1xcl->SetLabelSize(0.045,"XY");residualg1xcl->SetTitleSize(0.045,"XY");
    TH1F* residualg1ycl = new TH1F(nameRes1Y,"",200,-2,2); residualg1ycl->SetXTitle("mm"); residualg1ycl->SetYTitle("Frequency");residualg1ycl->SetLabelSize(0.045,"XY");residualg1ycl->SetTitleSize(0.045,"XY");
    TH1F* residualg2xcl = new TH1F(nameRes2X,"",200,-2,2); residualg2xcl->SetXTitle("Residual [mm]"); residualg2xcl->SetYTitle("Frequency");residualg2xcl->SetLabelSize(0.045,"XY");residualg2xcl->SetTitleSize(0.045,"XY");
    TH1F* residualg2ycl = new TH1F(nameRes2Y,"",200,-2,2); residualg2ycl->SetXTitle("Residual [mm]"); residualg2ycl->SetYTitle("Frequency");residualg2ycl->SetLabelSize(0.045,"XY");residualg2ycl->SetTitleSize(0.045,"XY");
    TH1F* residualg3xcl = new TH1F(nameRes3X,"",200,-2,2); residualg3xcl->SetXTitle("Residual [mm]"); residualg3xcl->SetYTitle("Frequency");residualg3xcl->SetLabelSize(0.045,"XY");residualg3xcl->SetTitleSize(0.045,"XY");
    TH1F* residualg3ycl = new TH1F(nameRes3Y,"",200,-2,2); residualg3ycl->SetXTitle("Residual [mm]"); residualg3ycl->SetYTitle("Frequency");residualg3ycl->SetLabelSize(0.045,"XY");residualg3ycl->SetTitleSize(0.045,"XY");


    TH1F* angleREF2 = new TH1F("angleREF2","Rotation angle distribution of REF1 and REF2",1000,-0.5,0.5); angleREF2->SetXTitle("Angle [radian]"); angleREF2->SetYTitle("Frequency");
    TH1F* angleREF3 = new TH1F("angleREF3","Rotation angle distribution of REF3 and REF2",1000,-0.5,0.5); angleREF3->SetXTitle("Angle [radian]"); angleREF3->SetYTitle("Frequency");
    
    TH1F* xTrackChi2 = new TH1F("XTrackChi2","Chi square of tracks in X projection",1000,0,10); xTrackChi2->SetXTitle("#chi^{2} of track in X"); xTrackChi2->SetYTitle("Frequency"); xTrackChi2->SetTitleSize(0.04,"XY"); xTrackChi2->SetLabelSize(0.04,"XY");
    TH1F* yTrackChi2 = new TH1F("YTrackChi2","Chi square of tracks in Y projection",1000,0,10); yTrackChi2->SetXTitle("#chi^{2} of track in Y"); yTrackChi2->SetYTitle("Frequency"); yTrackChi2->SetTitleSize(0.04,"XY"); yTrackChi2->SetLabelSize(0.04,"XY");

    if (verbose)
    	cout<<"Successfully Defined all histogram"<<endl;
    
    fout<<"shift: "<<shiREF1X<<"\t"<<shiREF1Y<<"\t"<<shiREF2X<<"\t"<<shiREF2Y<<"\t"<</*shiUVA3X<<"\t"<<shiUVA3Y<<"\t"<<*/shiREF3X<<"\t"<<shiREF3Y<<endl;
    fout2<<"rotation: "<<aREF2REF1<<"\t"<</*aUVA3REF2<<"\t"<<*/aREF3REF1<<endl;
    if (verbose)
    {
    cout<<"shift: "<<shiREF1X<<"\t"<<shiREF1Y<<"\t"<<shiREF2X<<"\t"<<shiREF2Y<<"\t"<</*shiUVA3X<<"\t"<<shiUVA3Y<<"\t"<<*/shiREF3X<<"\t"<<shiREF3Y<<endl;
    cout<<"rotation: "<<aREF2REF1<<"\t"<</*aUVA3REF2<<"\t"<<*/aREF3REF1<<endl;
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
      temPos_g2xcl=vPos_g2xcl[i]; temPos_g2ycl=vPos_g2ycl[i]; temPos_g3xcl=vPos_g3xcl[i]; temPos_g3ycl=vPos_g3ycl[i]; 
      temPos_g1xcl=vPos_g1xcl[i]; temPos_g1ycl=vPos_g1ycl[i]; 

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
      double Measuredg1xcl = intercept1 + slope1*Trk1Pos;
      double Measuredg2xcl = intercept1 + slope1*Trk2Pos;
      double Measuredg3xcl = intercept1 + slope1*Trk3Pos;
      if (verbose)
      cout<<"measured = "<< Measuredg2xcl <<"\tvPos = "<< vPos_g2xcl[i] <<"\tresidualg2xcl = "<<Measuredg2xcl-vPos_g2xcl[i]<<endl;
      residualg2xcl->Fill(Measuredg2xcl-vPos_g2xcl[i]);
      residualg3xcl->Fill(Measuredg3xcl-vPos_g3xcl[i]);
      residualg1xcl->Fill(Measuredg1xcl-vPos_g1xcl[i]);
      xTrackChi2->Fill(f1->GetChisquare());
  if (verbose)
      cout<<f1->GetChisquare()<<"\t";
      delete f1; delete g1;

      TGraph* g2 = new TGraph();
      g2->SetPoint(0,Trk1Pos, vPos_g1ycl[i]);
      g2->SetPoint(1,Trk2Pos, vPos_g2ycl[i]);
      g2->SetPoint(2,Trk3Pos, vPos_g3ycl[i]);
      // inclusive
      //g2->SetPoint(2,2305.5,vpZZ2[i]); //inclusive 1
      //g2->SetPoint(2,2327.5,vpZZ1[i]);  //inclusive 2
      //g2->SetPoint(3,2686.5,vpUVA3Y[i]);

  if (verbose)
cout<<"test"<<  endl;

      TF1* f2 = new TF1("line2","[0]+[1]*x",0,900);
      g2->Fit("line2","Q");
      double intercept2 = f2->GetParameter(0);
      double slope2     = f2->GetParameter(1);
      double Measuredg1ycl = intercept2 + slope2*Trk1Pos;
      double Measuredg2ycl = intercept2 + slope2*Trk2Pos;
      double Measuredg3ycl = intercept2 + slope2*Trk3Pos;

      residualg2ycl->Fill(Measuredg2ycl-vPos_g2ycl[i]);
      residualg3ycl->Fill(Measuredg3ycl-vPos_g3ycl[i]);
      residualg1ycl->Fill(Measuredg1ycl-vPos_g1ycl[i]);

      yTrackChi2->Fill(f2->GetChisquare());
  if (verbose)
      cout<<f2->GetChisquare()<<endl;
      delete f2; delete g2;
      
      double cosineREF2 = CalculateCosTheta1(vPos_g1xcl[i],vPos_g1ycl[i],vPos_g2xcl[i],vPos_g2ycl[i]);
      double cosineREF3 = CalculateCosTheta1(vPos_g1xcl[i],vPos_g1ycl[i],vPos_g3xcl[i],vPos_g3ycl[i]);
     // double cosineEta5 = CalculateCosTheta1(vPos_g2xcl[i],vPos_g2ycl[i],vPos_g2xcl[i],vpEta5[i]);
      angleREF2->Fill(cosineREF2);   //angleREF3_2->Fill(cosineREF3_2);
     // angleUVA3->Fill(cosineUVA3); //angleUVA3_2->Fill(cosineUVA3_2);
      angleREF3->Fill(cosineREF3); //angleREF1_2->Fill(cosineREF1_2);
      //angleEta5->Fill(cosineEta5);
      
      nnnn++;
      //if(nnnn%1000==0) cout<<nnnn<<"......"<<endl;
      //if(nnnn>1000) break;
    } //for loop
    //cout<<"after for loop"<<endl;
    gStyle->SetOptFit(1111);
//
    I2GFvalues myValues;
    if (verbose) cout<<"=========================>Passed 1 "<<endl;

    myValues = I2GFmainLoop(residualg2xcl, 1, 10 , 1);
    if (verbose) cout<<"=========================>Passed 2 "<<endl;
    meanREF2X = myValues.mean; sigmag2xcl=myValues.sigma;
    if (verbose) cout<<"=========================>Passed 2 "<<endl;
    myValues = I2GFmainLoop(residualg2ycl, 1, 10 , 1);
    meanREF2Y = myValues.mean; sigmag2ycl=myValues.sigma;
    if (verbose) cout<<"=========================>Passed 3 "<<endl;
    myValues = I2GFmainLoop(residualg3xcl, 1, 10 , 1);
    meanREF3X = myValues.mean; sigmag3xcl=myValues.sigma;
    if (verbose) cout<<"=========================>Passed 4 "<<endl;
    myValues = I2GFmainLoop(residualg3ycl, 1, 10 , 1);
    meanREF3Y = myValues.mean; sigmag3ycl=myValues.sigma;
    if (verbose) cout<<"=========================>Passed 5 "<<endl;
    myValues = I2GFmainLoop(residualg1xcl, 1, 10 , 1);
    meanREF1X = myValues.mean; sigmag1xcl=myValues.sigma;
    if (verbose) cout<<"=========================>Passed 6 "<<endl;
    myValues = I2GFmainLoop(residualg1ycl, 1, 10 , 1);
    meanREF1Y = myValues.mean; sigmag1ycl=myValues.sigma;
    if (verbose) cout<<"=========================>Passed 7 "<<endl;
//
  if (verbose)
    cout<<"residual mean: "<<meanREF2X<<"\t"<<meanREF2Y<<"\t"<<meanREF3X<<"\t"<<meanREF3Y<<"\t"<</*meanUVA3X<<"\t"<<meanUVA3Y<<"\t"<<*/meanREF1X<<"\t"<<meanREF1Y<<endl;
        //<<meanZZ1<<"\t"<<meanZZ2<<endl;
    fout1<<"residual mean: "<<meanREF2X<<"\t"<<meanREF2Y<<"\t"<<meanREF3X<<"\t"<<meanREF3Y<<"\t"<</*meanUVA3X<<"\t"<<meanUVA3Y<<"\t"<<*/meanREF1X<<"\t"<<meanREF1Y<<endl;
        //<<meanZZ1<<"\t"<<meanZZ2<<endl;

    myValues = I2GFmainLoop(angleREF2, 1, 10 , 1);
    if (verbose) cout<<"=========================>Passed 8 "<<endl;
    meanAngleREF2=myValues.mean;
    myValues = I2GFmainLoop(angleREF3, 1, 10 , 1);
    if (verbose) cout<<"=========================>Passed 9 "<<endl;
    meanAngleREF3=myValues.mean;




    //maximum=angleEta5->GetMean(); rms=angleEta5->GetRMS(1); lRange=maximum-rms*0.7; hRange=maximum+rms*0.7;
    //TF1* funAngleEta5=new TF1("funAngleEta5","gaus",lRange,hRange); angleEta5->Fit("funAngleEta5","RQ");
    //meanAngleEta5=funAngleEta5->GetParameter(1);
    //maximum=xTrackChi2->GetMean(); rms=xTrackChi2->GetRMS(1); lRange=maximum-rms*0.5; hRange=maximum+rms*0.5;
    //TF1* funXTrackChi2=new TF1("funXTrackChi2","gaus",lRange,hRange); xTrackChi2->Fit("funXTrackChi2","RQ");
    meanXChi2=xTrackChi2->GetMean();
    //maximum=yTrackChi2->GetMean(); rms=yTrackChi2->GetRMS(1); lRange=maximum-rms*0.5; hRange=maximum+rms*0.5;
    //TF1* funYTrackChi2=new TF1("funYTrackChi2","gaus",lRange,hRange); yTrackChi2->Fit("funYTrackChi2","RQ");
    meanYChi2=yTrackChi2->GetMean();
    
    totalAngleREF2 += aREF2REF1;
   // totalAngleUVA3 += aUVA3REF2;
    totalAngleREF3 += aREF3REF1;
    fout3<<sigmag1xcl<<"\t"<<sigmag1ycl<<"\t"<<sigmag2xcl<<"\t"<<sigmag2ycl<<"\t"<</*sigmaUVA3X<<"\t"<<sigmaUVA3Y<<*/"\t"<<sigmag3xcl<<"\t"<<sigmag3ycl<<"\t"<<totalAngleREF2<<"\t"<</*totalAngleUVA3<<*/"\t"<<totalAngleREF3<<"\t"<<meanXChi2<<"\t"<<meanYChi2<<endl;
    cout<<sigmag1xcl<<"\t"<<sigmag1ycl<<"\t"<<sigmag2xcl<<"\t"<<sigmag2ycl<<"\t"<</*sigmaUVA3X<<"\t"<<sigmaUVA3Y<<*/"\t"<<sigmag3xcl<<"\t"<<sigmag3ycl<<"\t"<<totalAngleREF2<<"\t"<</*totalAngleUVA3<<*/"\t"<<totalAngleREF3<<"\t"<<meanXChi2<<"\t"<<meanYChi2<<endl;
    
    f->Write();
    f->Close();
    //delete funPosEta5; delete funPosg1ycl; delete funPosUVA3Y; delete funPosg3ycl; delete funPosg2ycl;
    
    double factor = -0.2;
    shiREF1X = meanREF1X*factor; shiREF1Y = meanREF1Y*factor; 
    shiREF2X = meanREF2X*factor; shiREF2Y = meanREF2Y*factor; 
    shiREF3X = meanREF3X*factor; shiREF3Y = meanREF3Y*factor; 
    factor=0.2;
    
    aREF2REF1 = meanAngleREF2*factor;
    aREF3REF1 = meanAngleREF3*factor;
   // aEta5REF2 = meanAngleEta5*factor;
   // if(iterNb>0) break; // only cylce once.
    if((meanREF1X>=-0.05 && meanREF1X<=0.05) && (meanREF1Y>=-0.05 && meanREF1Y<=0.05))
    if((meanREF2X>=-0.05 && meanREF2X<=0.05) && (meanREF2Y>=-0.05 && meanREF2Y<=0.05))
    if((meanREF3X>=-0.05 && meanREF3X<=0.05) && (meanREF3Y>=-0.05 && meanREF3Y<=0.05))
    if(meanAngleREF3>=-0.05 && meanAngleREF3<=0.05 && meanAngleREF2>=-0.05 && meanAngleREF2<=0.05)
          {
            cout<<"find it...iterating "<<iterNb<<" times."<<endl;
            break;
          }
  // break;
    if(iterNb==50) break;

 }//while(1)
 fout.close();
 fout1.close();
 fout2.close();
} // entire script

int AlignTrackers_shift_rotate(string name, int RunNumber, double shiREF1X, double shiREF1Y, double shiREF2X, double shiREF2Y, double shiREF3X, double shiREF3Y, double Trk1Pos, double Trk2Pos, double Trk3Pos, double aREF2REF1, double aREF3REF1  ){
	
//  string name={"Position"}; 
 cout<<"Name of input file = "<<name<<endl;
//  name={"Position"}; 
cout<<"Start of program"<<endl;
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
