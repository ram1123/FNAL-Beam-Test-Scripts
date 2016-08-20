import re
import os
import ROOT
from ROOT import TFile, TH1F, TObject

os.system('mkdir -p plots/')

ROOT.gROOT.SetBatch(True)  # This will prevent histogram to show

path="/afs/cern.ch/user/r/rasharma/public/FNAL-Beam-Test-Scripts/"
RootFiles=["CoarseAligned_1869.root"]

c=ROOT.TCanvas("c","c",800,600)
c.Divide(3,2)
c.SetRightMargin(0.15)      # right margin for canvas
c.SetGridx()
c.SetGridy()
#c.SetLogz()

countf=0

for files in RootFiles:		# Loops over all the root files defined in varialbe ROOTFiles in line number 11
	filename=re.sub('.root','',RootFiles[countf])	# remove .root from root file name
	f1=ROOT.TFile(path+files,"READ")		# Read root files
	#print filename,"\n",files

	h1x=f1.Get("h_Pos_g1xcl");	c.cd(1);	h1x.Draw()
	h2x=f1.Get("h_Pos_g2xcl");	c.cd(2);        h2x.Draw()
	h3x=f1.Get("h_Pos_g3xcl");	c.cd(3);        h3x.Draw()
	h1y=f1.Get("h_Pos_g1ycl");	c.cd(4);        h1y.Draw()
	h2y=f1.Get("h_Pos_g2ycl");	c.cd(5);        h2y.Draw()
	h3y=f1.Get("h_Pos_g3ycl");	c.cd(6);        h3y.Draw()

	c.Print("plots/"+filename+".pdf")
