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
    git clone git@github.com:ram1123/FNAL-Beam-Test-Scripts.git		#(if working  on lxplus)
    git clone https://github.com/ram1123/FNAL-Beam-Test-Scripts.git	#(if working on your pc or lpc)
    cd FNAL-Beam-Test-Scripts
	git checkout B2B_2016TB
 
## How to Get Input Text File For This Software
	./RunAiwuTextFile.sh <InitialRunNumber> <FinalRunNumber>

If you want to run on only one run then put both InitialRunNumber and FinalRunNubmer same.
Also, there are two variables in this script. They are **EfficiencyType** and **TrkOnly**.

EfficiencyType : 
* If want to calculate efficiency of each GE11's independently, using trigger from hardware only put it equal to 0
* If want to trigger it using two of the reference tracker put it = 1
* If want to trigger it only when it passes from all three reference tracker then put it = 2

TrkOnly	    : 
* If you want output text file in which there are hit iff there is hit only in all three tracker then put this = 1
* If you want to get hit iff there is hit in all tracker as well as in GE11's then put this = 0

## How to Run:
	./RunAiwuSoftware.sh <InitialRunNumber> <FinalRunNumber> No 1		# Will create text file with tracker info only
	./RunAiwuSoftware.sh <InitialRunNumber> <FinalRunNumber> LC1 1		# Will create text file with tracker & one GE11
	./RunAiwuSoftware.sh <InitialRunNumber> <FinalRunNumber> LC1 0		# Run the alignment code

If you want to run on only one run then put both InitialRunNumber and FinalRunNubmer same.

**General Command**

	./RunAiwuSoftware.sh <InitialRunNumber> <FinalRunNumber> <Detector> <IfTxtOnly>

Variables Description:
* <Detector>: Available options => No, LC1 and LC2 and LC3
	* Option **No** : If we need text file with hit information only for tracker.
	* Option **LC1** : This is name of first added detector (GE11) in the software. Similarly for LC2 and LC3.

* <IfTxtOnly>: Available option 1 or 0
	* option 1: If you need to get only text file
	* option 0: If you want to run the alignment code



## To Dos

