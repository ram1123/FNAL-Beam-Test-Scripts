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
	./RunAiwuSoftware.sh 411 411 No 1		# Will create text file with tracker info only
	./RunAiwuSoftware.sh 411 411 LC1 1		# Will create text file with tracker & one GE11
	./RunAiwuSoftware.sh 411 411 LC1 0		# Run the alignment code

## To Dos

