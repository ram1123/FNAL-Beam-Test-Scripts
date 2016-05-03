############################################################
#		 To Do List	
#
#	1. 
#
#
#
############################################################
#		Basic Info about this Macro
#
#
#
#
############################################################


clear   	# Clear the screen
source /afs/cern.ch/sw/lcg/external/gcc/4.8/x86_64-slc6/setup.sh
source /afs/cern.ch/sw/lcg/app/releases/ROOT/6.04.02/x86_64-slc6-gcc48-opt/root/bin/thisroot.sh
IRunNo=$1
FRunNo=$2
ILat=15
FLat=30
RunCounter=$IRunNo
PathOfInputData=HitTxtFiles
Detector=$3  # options: No, LC1 and LC2 and LC3

function make_dir
{
#	------------------------------------------------------------------------
#	It Checks IF the output data directory exists or not
#	No Arguments
#	------------------------------------------------------------------------

	if [ -d "${1}" ]; then
		echo -n "          "
		echo -e "\E[34mDirectory ${1} Exists.......\E[0m"
	else
		echo -n "          "
		mkdir ${1}
		echo -e "\E[34mDirectory ${1} Created.................\E[0m"
	fi
}	# end of make_dir

clear   	# Clear the screen
echo -e "\E[33mcreate dir starts:\E[0m"
make_dir Residual_XY_Trk_RootFile
make_dir shiftParameters
make_dir residual_txtFile
make_dir Residual_Rot_Trk_RootFile
echo -e "\E[33mcreate dir ends:\E[0m"

while [ $RunCounter -le $FRunNo ]
do
    if [[(($RunCounter -le 9))]]; then
        file=000$RunCounter
    else
        if [[(($RunCounter -le 99))]]; then
            file=00$RunCounter
        else
            if [[(($RunCounter -le 999))]]; then
                file=0$RunCounter
            else
                file=$RunCounter
            fi
        fi
    fi
    for dir in ${PathOfInputData}/Run$file*; do	    # Start of dir for loop
    	echo ${dir}
	echo $(basename $dir)
	echo -e "\E[33mStarted Running the Python Code.\E[0m"
    	python RunAiwuSoftware.py -RN ${RunCounter} -i ${dir} -det ${Detector} 
	echo -e "\E[33mCompleted Running the Python Code.\E[0m"
    done	# END of dir for loop
    ((++RunCounter))	# increment counter for while loop
done			# while loop ends
