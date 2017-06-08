#!/bin/sh                                                                 

run="RunB"
location=$1
if test $location -eq 0
        then folder="/eos/uscms/store/user/lpchbb/HeppyNtuples/V25rereco/BTagCSV/VHBB_HEPPY_V25b_BTagCSV__Run2016B-03Feb2017_ver1-v1/170226_195930/"
elif test $location -eq 1
        then folder="/gpfs/ddn/srm/cms/store/user/arizzi/VHBBHeppyV25b/BTagCSV/VHBB_HEPPY_V25b_BTagCSV__Run2016B-03Feb2017_ver1-v1/170226_195930/"
else
        folder="./"
fi

                                                                            
from=1
to=40
  
mkdir $run
cd $run
mkdir PDFs
cp ../../PDFs/deepCSV_BH_Moriond17.csv PDFs/

for (( i=$from; i<=$to; i++ ))
do
	if test $i -lt 1000
		then subfolder="0000"
	elif test $i -lt 2000
		then subfolder="0001"
	elif test $i -lt 3000
		then subfolder="0002"
	else
		subfolder="0003"
	fi
	file="tree_"$i
	echo $file
	root -l -b -q "../../HbbHbb_PreSelection.cc++(\"$folder$subfolder\", \"$file\", \"JEC\", \"JER\", \"Trig\", \"bTag\", \"../../gravall-v25.weights.xml\")"
done

rm -fr PDFs/

cd ../

