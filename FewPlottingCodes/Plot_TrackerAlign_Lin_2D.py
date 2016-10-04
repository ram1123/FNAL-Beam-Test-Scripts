import re
import sys
import os
import ROOT
from ROOT import TFile, TH1F, TObject, TLatex
import gRootColorPalette

os.system('mkdir -p plots/')

ROOT.gROOT.SetBatch(True)  # This will prevent histogram to show
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptFit(0)

print 'Number of arguments:', len(sys.argv), 'arguments.'
print 'Argument List:', str(sys.argv)
if len(sys.argv) != 3:
	
	print "\n\n\tCommand Should Look like this:"
	print "\n\tpython Plot_TrackerAlign_Lin.py <RunNumber> <IterationNumber>\n\n"
	sys.exit(1)

print 'first arg = ',sys.argv[1]
path="../Residual_XY_Trk_RootFile/"
itern=int(sys.argv[2])
runnumber=int(sys.argv[1])

RootFiles="Residual_Position_iter_"+str(itern)+"_R"+str(runnumber)+".root"
c=ROOT.TCanvas("c","c",800,600)
c.SetRightMargin(0.05)      # right margin for canvas
c.SetLeftMargin(0.25)      # right margin for canvas
c.SetGridx()
c.SetGridy()
c.Divide(2,2)
#c.SetLogz()

countf=0

print "\n\n===> Input Root File: ",path+RootFiles,"\n\n"
filename=re.sub('.root','',RootFiles)	# remove .root from root file name
f1=ROOT.TFile(path+RootFiles,"READ")		# Read root files

#h1y=f1.Get("residual_g2ycl_NoFit");	h1y.SetStats(0); h1y.SetTitle("residual_g2ycl")	
#h2x=f1.Get("Pos_g2xcl_"+str(itern+1));	h2x.SetStats(0); h2x.SetTitle("Pos_g2xcl")	
h1 =f1.Get("Trk2_ResXPosY");			h1.SetStats(0);	 h1.SetTitle("ResidualX vs Y Pos for Trk2");	h1.GetXaxis().SetTitle("Cluster Position (mm)");	h1.GetYaxis().SetTitle("Residual (mm)")
h2 =f1.Get("Trk2_ResXPosX");			h2.SetStats(0);	 h2.SetTitle("ResidualX vs X Pos for Trk2");	h2.GetXaxis().SetTitle("Cluster Position (mm)");	h2.GetYaxis().SetTitle("Residual (mm)")
h3 =f1.Get("Trk2_ResYPosY");			h3.SetStats(0);	 h3.SetTitle("ResidualY vs Y Pos for Trk2");	h3.GetXaxis().SetTitle("Cluster Position (mm)");	h3.GetYaxis().SetTitle("Residual (mm)")
h4 =f1.Get("Trk2_ResYPosX");			h4.SetStats(0);	 h4.SetTitle("ResidualY vs X Pos for Trk2");	h4.GetXaxis().SetTitle("Cluster Position (mm)");	h4.GetYaxis().SetTitle("Residual (mm)")

#fitresult_1x =  h2x.GetFunction("func3")

#c.cd(1);  text1 = TLatex(h1x.GetXaxis().GetXmin(),h1x.GetMaximum()-100,"  Sigma = "+str(fitresult_1x.GetParameter(2))[:7]+"#pm"+str(fitresult_1x.GetParError(2))[:5]); h1x.Draw(); text1.SetTextSize(0.07);	text1.Draw("sames")
#c.cd(1);	h1y.Draw();
#c.cd(2);	h2x.Draw();
c.cd(1);	h1.Draw("colz");
c.cd(2);	h2.Draw("colz");
c.cd(3);	h3.Draw("colz");
c.cd(4);	h4.Draw("colz");
#c.cd(3);	h3.GetYaxis().Set(20,-1,1); h3.GetXaxis().Set(20,-50,50); h3.Draw("colz");



#print "==> OutPut ROOT File: ",

c.Print("plots/"+filename+".pdf")
c.Print("plots/"+filename+".png")
c.Print("plots/test.pdf")
c.Print("plots/test.png")
