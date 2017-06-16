#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd /scratch/malara/WorkingArea/release/CMSSW_7_4_7/src/HiggsAnalysis/CombinedLimit 
cmsenv
cd $DIR

function_LMR=$1
range_LMR=$2
background_LMR="_${function_LMR}_${range_LMR}"

function_MMR=$3
range_MMR=$4
background_MMR="_${function_MMR}_${range_MMR}"

if [ $5 -eq 1 ];
        then
        masses_LMR=(260 270 300 350)
        else masses_LMR=(270 300 350 400 450 500 550 600 650)
fi

if [ $5 -eq 1 ];
        then
        masses_MMR=(550 600 650 750 800 900 1000)
        else masses_MMR=() #550 600 650 750 800 900 1000)
fi

echo 'MMR'
for i in ${masses_MMR[@]}

do
        cd $DIR
        folder="PreselectedWithRegressionDeepCSV/limits_bias/MMR/MMR_${i}${background_MMR}"
	if [ -d $folder ]
	then
	rm -fr $folder 
	fi	
        echo "mass point $i"
        cp -r PreselectedWithRegressionDeepCSV/MMRSelection_chi2/fit_bias/MMR_${i}${background_MMR} ${folder} 
	cd $folder 
	mkdir out
        #text2workspace.py datacard_${i}${background_MMR}.txt  -o datacard_${i}${background_MMR}.root
	#sed -i '/PDF.*/d' datacard_${i}${background_MMR}.txt
        echo "Asymptotic"
        combine -M Asymptotic datacard_${i}${background_MMR}.txt -t -1 &> CMS_HH4b_$i\_13TeV_asymptoticCLs.out
        echo "MaxLikelihoodFit"
        combine -M MaxLikelihoodFit datacard_${i}${background_MMR}.txt -t -1 --minimizerTolerance=0.001 --rMin=0 --rMax=3 &> CMS_HH4b_$i\_13TeV_MaxLikelihood.out
        echo "Plot"
        combine -M MaxLikelihoodFit datacard_${i}${background_MMR}.txt -t -1 --minimizerTolerance=0.001 --rMin=0 --rMax=3 --saveNormalizations --plot --out out 
done

cd $DIR

echo 'LMR'

for i in ${masses_LMR[@]}

do
        cd $DIR
        folder="PreselectedWithRegressionDeepCSV/limits_bias/LMR/LMR_${i}${background_LMR}"
        if [ -d $folder ]
        then
        rm -fr $folder
        fi
        echo "mass point $i"
        cp -r PreselectedWithRegressionDeepCSV/LMRSelection_chi2/fit_bias/LMR_${i}${background_LMR} ${folder}
        cd $folder
        mkdir out
        #text2workspace.py datacard_${i}${background_LMR}.txt  -o datacard_${i}${background_LMR}.root
	#sed -i '/PDF.*/d' datacard_${i}${background_LMR}.txt
        echo "Asymptotic"
        combine -M Asymptotic datacard_${i}${background_LMR}.txt -t -1 &> CMS_HH4b_$i\_13TeV_asymptoticCLs.out
        echo "MaxLikelihoodFit"
        combine -M MaxLikelihoodFit datacard_${i}${background_LMR}.txt -t -1 --minimizerTolerance=0.001 --rMin=0 --rMax=3 &> CMS_HH4b_$i\_13TeV_MaxLikelihood.out
        echo "Plot"
        combine -M MaxLikelihoodFit datacard_${i}${background_LMR}.txt -t -1 --minimizerTolerance=0.001 --rMin=0 --rMax=3 --saveNormalizations --plot --out out
done

cd $DIR

