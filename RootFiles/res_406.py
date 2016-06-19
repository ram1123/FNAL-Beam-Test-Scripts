###################################################################
#
#	This code plots histogram from a root file
#
###################################################################
import ROOT
from ROOT import *

ROOT.gROOT.SetBatch(True)  # This will prevent histogram to show

canv = ROOT.TCanvas()

#RootFile_NoShift = 'rPhi_residual_PositionLC1_X_-2400.00_Y_-415.00_inclusive_doubleGaussian_NoShift.root'
RootFile_NoShift = 'rPhi_residual_NoShift_PositionLC1_X_-2400.00_Y_-415.00_inclusive_doubleGaussian.root'
#RootFile_Shift = 'rPhi_residual_PositionLC1_X_-2400.00_Y_-415.00_inclusive_doubleGaussian_Shift.root'
RootFile_Shift = 'rPhi_residual_Shift_PositionLC1_X_-2400.00_Y_-415.00_inclusive_doubleGaussian.root'
RootFile_Shift = 'rPhi_residual_Shift_X64.8225_Y56.8621_PositionLC1_X_-2400.00_Y_-415.00_inclusive_doubleGaussian.root'
RootFile_Shift = 'rPhi_residual_Shift_X64.8225_Y58.8621_PositionLC1_X_-2400.00_Y_-415.00_inclusive_doubleGaussian.root'
RootFile_Shift = 'rPhi_residual_Shift_X64.8225_Y60.8621_PositionLC1_X_-2400.00_Y_-415.00_inclusive_doubleGaussian.root'
RootFile_Shift = 'rPhi_residual_Shift_X64.8225_Y62.8621_PositionLC1_X_-2400.00_Y_-415.00_inclusive_doubleGaussian.root'
RootFile_Shift = 'rPhi_residual_Shift_X64.8225_Y64.8225_PositionLC1_X_-2400.00_Y_-415.00_inclusive_doubleGaussian.root'
RootFile_Shift = 'rPhi_residual_Shift_X54.8225_Y56.8621_PositionLC1_X_-2400.00_Y_-415.00_inclusive_doubleGaussian.root'
RootFile_Shift = 'rPhi_residual_Shift_X64.8225_Y56.8621_PositionLC1_X_-2400.00_Y_-415.00_inclusive_doubleGaussian.root'

f_NoShift = ROOT.TFile(RootFile_NoShift)
f_Shift = ROOT.TFile(RootFile_Shift)

leg = TLegend(0.55,0.80,0.76,0.90)

#print ('#############################################################')
#f_Shift.ls()
#print ('#############################################################')

gStyle.SetOptStat(110)

canv.SaveAs("Test.pdf[")
histograms = [  'residualREF1_r_X_-2400.0_Y_-415.0', 'residualREF1_phi_X_-2400.0_Y_-415.0', 
                'residualREF2_r_X_-2400.0_Y_-415.0', 'residualREF2_phi_X_-2400.0_Y_-415.0', 
                'residualREF3_r_X_-2400.0_Y_-415.0', 'residualREF3_phi_X_-2400.0_Y_-415.0', 
                'residualEta5_phi_X_-2400.0_Y_-415.0' ]

XRange = [  -3.5,3.5,   -10,10,
            -0.8,0.8,   -2,2,
            -0.3,0.3,   -10,10,
            -20,20
        ]

YRange = [  0,500,0,300,
            0,800,0,1200,
            0,800,0,800,
            0,840
        ]

hbin = [1, 4,
        2, 2,
        1, 8,
        1
        ]

count = 0
nbin = 0

for histo in histograms:
    g1x = ROOT.TH1F()
    g1x = f_NoShift.Get(histo)
    g1x.Rebin(hbin[nbin]);
    g1x.SetTitle(histo)
    g1x.SetLineColor(1)
    g1x.SetLineWidth(2)
    g1x.GetXaxis().SetRangeUser(XRange[2*count],XRange[2*count+1])
    g1x.GetYaxis().SetRangeUser(YRange[2*count],YRange[2*count+1])
    leg.AddEntry(g1x,"Before Shifting Origin")
    g1x.Draw()
    canv.Modified()
    canv.Update()
    gPad.Update()
    
    ps =  g1x.GetListOfFunctions().FindObject("stats")
    print ps
    ps.SetName('Stat1')
    ps.SetY1NDC(0.80)
    ps.SetY2NDC(0.90)
    ps.SetX1NDC(0.10)
    ps.SetX2NDC(0.35)
    ps.SetTextColor(1)
    ps.SetLineColor(1)
    
    gPad.Modified()
    gPad.Update() 
    
    
    
    g2x = ROOT.TH1F()
    g2x = f_Shift.Get(histo)
    g2x.Rebin(hbin[nbin]);
    g2x.SetLineColor(2);
    g2x.SetLineWidth(2);
    g2x.GetXaxis().SetRangeUser(XRange[2*count],XRange[2*count+1])
    g2x.GetYaxis().SetRangeUser(YRange[2*count],YRange[2*count+1])
    #g2x.GetXaxis().SetRangeUser(-0.5,0.5)
    #g2x.GetYaxis().SetRangeUser(0,400)
    leg.AddEntry(g2x,"After Shifting Origin")
    g2x.Draw("Sames")
    canv.Update()
    gPad.Update()
    
    ps2 =  g2x.GetListOfFunctions().FindObject("stats")
    ps2.SetName('Stat2')
    ps2.SetY1NDC(0.80)
    ps2.SetY2NDC(0.90)
    ps2.SetX1NDC(0.35)
    ps2.SetX2NDC(0.55)
    ps2.SetTextColor(2)
    ps2.SetLineColor(2)
    
    print '========> ',ps2.GetTitle()
    print '========> ',ps2.GetIconName()
    print '========> ',ps2.GetLabel()
    
    leg.Draw()
    
    #output = histo+".pdf" 
    #canv.SaveAs(output)
    canv.SaveAs("Test.pdf")
    canv.Clear()
    leg.Clear()
    count = count + 1
    nbin = nbin + 1

canv.SaveAs("Test.pdf]")
