#Environment Setting for Lxplus
This code is check for only root version 6.04. So, its recommended that one should run this on root 6.04.

Lxplus setting for root 6.04:

    For tcsh shell:
    source /afs/cern.ch/sw/lcg/external/gcc/4.8/x86_64-slc6/setup.csh
    source /afs/cern.ch/sw/lcg/app/releases/ROOT/6.04.02/x86_64-slc6-gcc48-opt/root/bin/thisroot.csh

    For bash shell:
    source /afs/cern.ch/sw/lcg/external/gcc/4.8/x86_64-slc6/setup.sh
    source /afs/cern.ch/sw/lcg/app/releases/ROOT/6.04.02/x86_64-slc6-gcc48-opt/root/bin/thisroot.sh

# How to Get This Software
    git clone git@github.com:ram1123/FNAL-Beam-Test-Scripts.git		(if working  on lxplus)
    git clone https://github.com/ram1123/FNAL-Beam-Test-Scripts.git	(if working on your pc or lpc)
    cd FNAL-Beam-Test-Scripts
	git checkout Develop
 
## How to Run:
First you need to run the **TurboSoftware** to get the root file from EventBuilder step (root file should be of type CRC\*.root). Then there are two steps in the alignment framework. First step is to get the text file with hit information. Then, in next step takes this text file with hit info and tries to align the detector.

### Step 1: Get the text file to process in step 2.
	./RunAiwuTextFile.sh <Initial Run Number>  <Final Run Number>

You may need to modify the path of input root files. Also, there are two variables named **EfficiencyType** and **TrkOnly**. Need to choose the values of this variable in code. Description of these variables given in code itself.

### Step 2: Alignment part
Few things to keep in mind:
1. s

	./RunAiwuSoftware.sh <Initial Run Number>  <Final Run Number> No 1 0		# Will create text file with tracker info only
	./RunAiwuSoftware.sh <Initial Run Number>  <Final Run Number> LC1 1 0		# Will create text file with tracker & one GE11
	./RunAiwuSoftware.sh <Initial Run Number>  <Final Run Number> LC1 0 1		# Run the alignment code

**Some time you may get error**, stating following error
	Warning in <Fit>: Fit data is empty 
	*** Break *** segmentation violation

This is because while aligning the detector it is going outside the range of defined histogram. So, you need to see carefully and set range or initial parameter carefully.

## Some Additional Codes
These codes are in dierctory named **FewPlottingCodes**.

1. **Plot_TrackerAlign_Lin.py**: This macro plots the residual from the root file of first step of code.
2. **Plot_residual.C**: This takes input the file that contains mean/residual of all trackers with iteration. And gives us plot for mean or sigma with iteration.
3. SpaceResolution_vs_HV.C
3. EfficiencyTxtFileSplitBOLat.sh: This splits text file w.r.t. the latency.
4. Plot_GEMXY_Output.C: Plotting code from output of GEM align code.
5. Plot_Trk_Linear.C: Plotting code from out of Linear shift tracker.
6. CoarseAnalyze.py: This is to analyze the root file named CoarseAligned\_\*.root
