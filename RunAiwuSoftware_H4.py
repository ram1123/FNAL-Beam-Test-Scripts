import sys
import re
import os
import datetime
import argparse
import string

from DetectorPosition import *	## Import variables from  DetectorPosition.txt 

if __name__ == '__main__':
    parser = argparse.ArgumentParser (description = 'Run the Aiwu software')
    parser.add_argument ('-det', '--Det'      , default = 'LC1'                    , help='No or LC1 or LC2 or LC3')
    parser.add_argument ('-RNum' , '--RunNumber', default = '411'                   , help='Enter Run Number')
    parser.add_argument ('-i'  , '--InputFile', default = 'Hit_Position_Info.txt' , help='Name of Input File')
    parser.add_argument ('-l'  , '--Lxplus'   , default = '0'			  , help='if not working on lxplus then put 0')
    parser.add_argument ('-t'  , '--TextOnly' , default = '0'			  , help='if not working on lxplus then put 0')
    parser.add_argument ('-Run'  , '--RunWhichPart' , default = '0'			  , help='if not working on lxplus then put 0')
    args = parser.parse_args ()

if args.Lxplus=="1":
	print('source /afs/cern.ch/sw/lcg/external/gcc/4.8/x86_64-slc6/setup.sh')
	os.system('source /afs/cern.ch/sw/lcg/external/gcc/4.8/x86_64-slc6/setup.sh')
	print('source /afs/cern.ch/sw/lcg/app/releases/ROOT/6.04.02/x86_64-slc6-gcc48-opt/root/bin/thisroot.sh')
	os.system('source /afs/cern.ch/sw/lcg/app/releases/ROOT/6.04.02/x86_64-slc6-gcc48-opt/root/bin/thisroot.sh')

RunWhichPart = args.RunWhichPart		# This part is not working somehow, Need to manually reset this
print "RunWhichPart = ",RunWhichPart
RunWhichPart = 1

Dir_Shift_Par="FinalShiftPar_LinShiftTrk/ShiftPar_LinearShiftTrkOnly_alignTrackers_R"+args.RunNumber+".txt"
Dir_Shift_Rot_Par="FinalShiftPar_RotShiftTrk/Shift_Rotate_Parameter_R"+args.RunNumber+".txt"

print Dir_Shift_Par
print Dir_Shift_Rot_Par

def getVarFromFile(filename):
    import imp
    f = open(filename)
    global data
    data = imp.load_source('data', '', f)
    f.close()

if RunWhichPart==2 or RunWhichPart==3:
	getVarFromFile(Dir_Shift_Par)
if RunWhichPart==3:
	getVarFromFile(Dir_Shift_Rot_Par)

print '========================================================================='
print 'args.TextOnly = ',args.TextOnly
RunName = re.sub('_HitInfo.txt','',args.InputFile)	# Remove _HitInfo.txt part from string InputFile
RunName = re.sub('FirstStage_textFile/','',RunName)		# Remove HitTxtFiles/ part from string RunName
print '=========>  ',RunName
if args.TextOnly=="1":
    print 'Start Running SelectTrackerEvents.C...'
    if args.RunNumber < 1587:
    	print('root -l -b -q SelectTrackerEvents_H2.C\(\\"'+args.InputFile+'\\",\\"'+RunName+'\\",'+args.RunNumber+',\\"'+args.Det+'\\"\)')
    	os.system('root -l -b -q SelectTrackerEvents_H2.C\(\\"'+args.InputFile+'\\",'+args.RunNumber+',\\"'+args.Det+'\\"\)')
    else:
    	print('root -l -b -q SelectTrackerEvents_H4.C\(\\"'+args.InputFile+'\\",\\"'+RunName+'\\",'+args.RunNumber+',\\"'+args.Det+'\\"\)')
    	os.system('root -l -b -q SelectTrackerEvents_H4.C\(\\"'+args.InputFile+'\\",\\"'+RunName+'\\",'+args.RunNumber+',\\"'+args.Det+'\\"\)')
    print '\n\nSelectTrackerEvents.C DONE...\n\n'
else:
    print "Don't re-run SelectTrackerEvents.C macro......"
    print '\n\n======== Start::CALCULATING SHIFT PARAMETERS    =================================\n\n'
    import ROOT
    import math
    from ROOT import TFile, TH1F, TObject
    ROOT.gROOT.SetBatch(True)  # This will prevent histogram to show
    RootFile = 'CoarsedAligned/'+RunName+'_CoarseAligned.root'
    print 'Input Root File : ',RootFile
    if os.path.isfile(RootFile):
    	f = TFile(RootFile)
    	g1x = f.Get("h_Pos_g1xcl")  
    	g1y = f.Get("h_Pos_g1ycl")  
    	g2x = f.Get("h_Pos_g2xcl")  
    	g2y = f.Get("h_Pos_g2ycl")  
    	g3x = f.Get("h_Pos_g3xcl")  
    	g3y = f.Get("h_Pos_g3ycl")  
    	LC1 = f.Get("h_Pos_GE11_IV_GIF")  
    	LC2 = f.Get("h_Pos_GE11_IV")  
    	LC3 = f.Get("h_Pos_sCMSNS2LC3")  
    	Mean_g1x = g1x.GetMean()
    	Mean_g1y = g1y.GetMean()
    	Mean_g2x = g2x.GetMean()
    	Mean_g2y = g2y.GetMean()
    	Mean_g3x = g3x.GetMean()
    	Mean_g3y = g3y.GetMean()
    	Mean_LC1 = LC1.GetMean()
    	Mean_LC2 = LC2.GetMean()
    	Mean_LC3 = LC3.GetMean()
    	print "Mean values : ",Mean_g1x,"\t",Mean_g1y,"\t",Mean_g2x,"\t",Mean_g2y,"\t",Mean_g3x,"\t",Mean_g3y
    	Mean_angle_g1g2 = math.asin((Mean_g2x*Mean_g1y-Mean_g1x*Mean_g2y)/(Mean_g1x*Mean_g1x+Mean_g1y*Mean_g1y))
    	Mean_angle_g1g3 = math.asin((Mean_g3x*Mean_g1y-Mean_g1x*Mean_g3y)/(Mean_g1x*Mean_g1x+Mean_g1y*Mean_g1y))
    	print "Angles : ",Mean_angle_g1g2,"\t",Mean_angle_g1g3
    else:
        print '\n================\n\n\tInput Root File ',RootFile,' does not exits\n\n=====================\n\n'
        sys.exit(0)
    print '\n\n======== END::CALCULATING SHIFT PARAMETERS    =================================\n\n'
    #=====================  START:: Running AlignTrackers_Shift.C	=================================
    if (RunWhichPart==1 or RunWhichPart>3):
        print '\n\n============ START:: Running AlignTrackers_Shift.C...    ================================\n\n'
        print 'This code will align trackers only\n\n'
        print('root -l -b -q AlignTrackers_Shift.C\(\\"SecondStage_TextFile/'+RunName+'_TrackerOnly_Position.txt\\",'+args.RunNumber+','+str(Mean_g1x)+','+str(Mean_g1y)+','+str(Mean_g2x) + ','+str(Mean_g2y) +','+str(Mean_g3x) +','+str(Mean_g3y)+','+str(H4_Trk1_Pos)+','+str(H4_Trk2_Pos)+','+str(H4_Trk3_Pos)+'\)')
        os.system('root -l -b -q AlignTrackers_Shift.C\(\\"SecondStage_TextFile/'+RunName+'_TrackerOnly_Position.txt\\",'+args.RunNumber+','+str(Mean_g1x)+','+str(Mean_g1y)+','+str(Mean_g2x) + ','+str(Mean_g2y) +','+str(Mean_g3x) +','+str(Mean_g3y)+','+str(H4_Trk1_Pos)+','+str(H4_Trk2_Pos)+','+str(H4_Trk3_Pos)+'\)')
        print '\n\nAlignTrackers_Shift.C...  DONE'
    #=====================  END:: Running AlignTrackers_Shift.C	=================================
    #=====================  START:: Running AlignTrackers_shift_rotate.C	=================================
    print "========>  RunWhichPart = ",RunWhichPart
    if (RunWhichPart==2 or RunWhichPart>3) :
        print('root -l -b -q AlignTrackers_shift_rotate.C\(\\"SecondStage_TextFile/'+RunName+'_TrackerOnly_Position.txt\\",'+args.RunNumber+','+str(Mean_g1x)+','+str(Mean_g1y)+','+str(Mean_g2x)+ ','+str(data.Shift_2X)+ ','+str(Mean_g2y)+','+str(data.Shift_2Y)+',' +str(Mean_g3x)+','+str(data.Shift_3X)+','+str(Mean_g3y)+','+str(data.Shift_3Y)+','+str(H4_Trk1_Pos)+','+str(H4_Trk2_Pos)+','+str(H4_Trk3_Pos)+','+str(Mean_angle_g1g2)+','+str(Mean_angle_g1g3)+'\)')
        os.system('root -l -b -q AlignTrackers_shift_rotate.C\(\\"SecondStage_TextFile/'+RunName+'_TrackerOnly_Position.txt\\",'+args.RunNumber+','+str(Mean_g1x)+','+str(Mean_g1y)+','+str(Mean_g2x)+ ','+str(data.Shift_2X)+ ','+str(Mean_g2y)+','+str(data.Shift_2Y)+',' +str(Mean_g3x)+','+str(data.Shift_3X)+','+str(Mean_g3y)+','+str(data.Shift_3Y)+','+str(H4_Trk1_Pos)+','+str(H4_Trk2_Pos)+','+str(H4_Trk3_Pos)+','+str(Mean_angle_g1g2)+','+str(Mean_angle_g1g3)+'\)')
    ##=====================  END:: Running AlignTrackers_shift_rotate.C	=================================
    ##=====================  START:: Running AlignGEM_XYoffsets.C	=================================
    if (RunWhichPart==3 or RunWhichPart>3) :
        print '\n\n============		START:: Running AlignGEM_XYoffsets.C	================\n\n'
	print('root -l -b -q AlignGEM_XYoffsets.C\(\\"SecondStage_TextFile/'+RunName+'_TrackerAndLC2_Position.txt\\",'+args.RunNumber+','+str(Mean_g1x)+','+str(Mean_g1y)+','+str(Mean_g2x) + ','+str(data.Shift_2X+data.Shift_2X_Rot) + ','+str(Mean_g2y) +','+str(data.Shift_2Y+data.Shift_2Y_Rot) +','+str(Mean_g3x) +','+str(data.Shift_3X+data.Shift_3X_Rot) +','+str(Mean_g3y) +','+str(data.Shift_3Y+data.Shift_3Y_Rot) +','+str(LC2.GetMean())+','+str(H4_Trk1_Pos)+','+str(H4_Trk2_Pos)+','+str(H4_Trk3_Pos)+','+str(H4_GE11_IV_Pos)+','+str(Mean_angle_g1g2) +','+ str(data.TotalAngleREF2)+','+str(Mean_angle_g1g3)+','+str(data.TotalAngleREF3)+'\)')
	os.system('root -l -b -q AlignGEM_XYoffsets.C\(\\"SecondStage_TextFile/'+RunName+'_TrackerAndLC2_Position.txt\\",'+args.RunNumber+','+str(Mean_g1x)+','+str(Mean_g1y)+','+str(Mean_g2x) + ','+str(data.Shift_2X+data.Shift_2X_Rot) + ','+str(Mean_g2y) +','+str(data.Shift_2Y+data.Shift_2Y_Rot) +','+str(Mean_g3x) +','+str(data.Shift_3X+data.Shift_3X_Rot) +','+str(Mean_g3y) +','+str(data.Shift_3Y+data.Shift_3Y_Rot) +','+str(LC2.GetMean())+','+str(H4_Trk1_Pos)+','+str(H4_Trk2_Pos)+','+str(H4_Trk3_Pos)+','+str(H4_GE11_IV_Pos)+','+str(Mean_angle_g1g2) +','+ str(data.TotalAngleREF2)+','+str(Mean_angle_g1g3)+','+str(data.TotalAngleREF3)+'\)')
        print '\n\n=============	END:: Running AlignGEM_XYoffsets.C	=================\n\n'
