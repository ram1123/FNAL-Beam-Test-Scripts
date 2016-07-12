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

### Step 1: Get the text file to process in step 2.
	./RunAiwuTextFile.sh <Initial Run Number>  <Final Run Number>

You may need to modify the path of input root files. Also, there are two variables named **EfficiencyType** and **TrkOnly**. Need to choose the values of this variable in code. Description of these variables given in code itself.

### Step 2:
	./RunAiwuSoftware.sh <Initial Run Number>  <Final Run Number> No 1		# Will create text file with tracker info only
	./RunAiwuSoftware.sh <Initial Run Number>  <Final Run Number> LC1 1		# Will create text file with tracker & one GE11
	./RunAiwuSoftware.sh <Initial Run Number>  <Final Run Number> LC1 0		# Run the alignment code
