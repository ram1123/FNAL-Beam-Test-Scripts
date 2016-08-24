import re
import sys
import os
import ROOT
from ROOT import TFile, TH1F, TObject, TLatex

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
c.Divide(3,2)
c.SetRightMargin(0.15)      # right margin for canvas
c.SetGridx()
c.SetGridy()
#c.SetLogz()

countf=0

print "\n\n===> Input Root File: ",path+RootFiles,"\n\n"
filename=re.sub('.root','',RootFiles)	# remove .root from root file name
f1=ROOT.TFile(path+RootFiles,"READ")		# Read root files

h1x=f1.Get("residual_g1xcl_"+str(itern+1));	      h1x.SetStats(0); h1x.SetTitle("residual_g1xcl")	
h2x=f1.Get("residual_g2xcl_"+str(itern+1));	      h2x.SetStats(0); h2x.SetTitle("residual_g2xcl") 	
h3x=f1.Get("residual_g3xcl_"+str(itern+1));	      h3x.SetStats(0); h3x.SetTitle("residual_g3xcl")	
h1y=f1.Get("residual_g1ycl_"+str(itern+1));	      h1y.SetStats(0); h1y.SetTitle("residual_g1ycl")	
h2y=f1.Get("residual_g2ycl_"+str(itern+1));	      h2y.SetStats(0); h2y.SetTitle("residual_g2ycl")	
h3y=f1.Get("residual_g3ycl_"+str(itern+1));	      h3y.SetStats(0); h3y.SetTitle("residual_g3ycl")	

fitresult_1x =  h1x.GetFunction("func3")
fitresult_2x =  h2x.GetFunction("func3")
fitresult_3x =  h3x.GetFunction("func3")
fitresult_1y =  h1y.GetFunction("func3")
fitresult_2y =  h2y.GetFunction("func3")
fitresult_3y =  h3y.GetFunction("func3")

c.cd(1);  text1 = TLatex(h1x.GetXaxis().GetXmin(),h1x.GetMaximum()-100,"  Sigma = "+str(fitresult_1x.GetParameter(2))[:7]+"#pm"+str(fitresult_1x.GetParError(2))[:5]); h1x.Draw(); text1.SetTextSize(0.07);	text1.Draw("sames")
c.cd(2);  text2 = TLatex(h2x.GetXaxis().GetXmin(),h2x.GetMaximum()-100,"  Sigma = "+str(fitresult_2x.GetParameter(2))[:7]+"#pm"+str(fitresult_2x.GetParError(2))[:5]); h2x.Draw(); text2.SetTextSize(0.07);	text2.Draw("sames")
c.cd(3);  text3 = TLatex(h3x.GetXaxis().GetXmin(),h3x.GetMaximum()-100,"  Sigma = "+str(fitresult_3x.GetParameter(2))[:7]+"#pm"+str(fitresult_3x.GetParError(2))[:5]); h3x.Draw(); text3.SetTextSize(0.07);	text3.Draw("sames")
c.cd(4);  text4 = TLatex(h1y.GetXaxis().GetXmin(),h1y.GetMaximum()-100,"  Sigma = "+str(fitresult_1y.GetParameter(2))[:7]+"#pm"+str(fitresult_1y.GetParError(2))[:5]); h1y.Draw(); text4.SetTextSize(0.07);	text4.Draw("sames")
c.cd(5);  text5 = TLatex(h2y.GetXaxis().GetXmin(),h2y.GetMaximum()-100,"  Sigma = "+str(fitresult_2y.GetParameter(2))[:7]+"#pm"+str(fitresult_2y.GetParError(2))[:5]); h2y.Draw(); text5.SetTextSize(0.07);	text5.Draw("sames") 
c.cd(6);  text6 = TLatex(h3y.GetXaxis().GetXmin(),h3y.GetMaximum()-100,"  Sigma = "+str(fitresult_3y.GetParameter(2))[:7]+"#pm"+str(fitresult_3y.GetParError(2))[:5]); h3y.Draw(); text6.SetTextSize(0.07);	text6.Draw("sames")

#print "==> OutPut ROOT File: ",

c.Print("plots/"+filename+".pdf")
c.Print("plots/"+filename+".png")
c.Print("plots/test.pdf")
c.Print("plots/test.png")
