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

   #550 600 650 750 800 900 1000
#400 410 420 430 440 450 460 470 480 490 500 510 520 530 540 550 560 570 580 590 600 610 620 630 640 650 660 670 680 690 700 710 720 730 740 750 760 770 780 790 800 810 820 830 840 850 860 870 880 890 900
#500 520 550 570 600 620 650 670 700 720 750 770 800 820 850 870 900
#400 420 450 470 500 520 550 570 600 620 650 670 700 720 740 750 770 790 800 820 840 850 870 900
#520 640 710 720 760 770 780 810 880
#540 560 590 610 630 730 740 830 860 890
#800 820 850 870 900
#500 550

if [ $5 -eq 1 ];
        then
        masses_LMR=(260 270 300 350)
        else masses_LMR=(270 300 350 400 450 500 550 600 650)
fi

if [ $5 -eq 1 ];
        then
        masses_MMR=(550 600 650 750 800 900 1000)
        else masses_MMR=(550 600 650 750 800 900 1000)
fi

    #260 270 300 350 400 450 500 550
#260 265 270 275 280 285 290 295 300 310 320 330 340 350 360 370 380 390 400 410 420 430 440 450 460 470 480 490 500 510 520 530 540 550
#320 370 420 430 470
#370 420 460 510 520 540
#510 520
#260

echo 'MMR'
for i in ${masses_MMR[@]}

do
        cd $DIR
        folder="PreselectedWithRegressionDeepCSV/limits/MMR/MMR_${i}${background_MMR}"
	if [ -d $folder ]
	then
	rm -fr $folder 
	fi	
        echo "mass point $i"
        cp -r PreselectedWithRegressionDeepCSV/MMRSelection_chi2/fit/MMR_${i}${background_MMR} ${folder} 
	cd $folder 
	mkdir out
        #text2workspace.py datacard_${i}${background_MMR}.txt  -o datacard_${i}${background_MMR}.root
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
        folder="PreselectedWithRegressionDeepCSV/limits/LMR/LMR_${i}${background_LMR}"
        if [ -d $folder ]
        then
        rm -fr $folder
        fi
        echo "mass point $i"
        cp -r PreselectedWithRegressionDeepCSV/LMRSelection_chi2/fit/LMR_${i}${background_LMR} ${folder}
        cd $folder
        mkdir out
        #text2workspace.py datacard_${i}${background_LMR}.txt  -o datacard_${i}${background_LMR}.root
        echo "Asymptotic"
        combine -M Asymptotic datacard_${i}${background_LMR}.txt -t -1 &> CMS_HH4b_$i\_13TeV_asymptoticCLs.out
        echo "MaxLikelihoodFit"
        combine -M MaxLikelihoodFit datacard_${i}${background_LMR}.txt -t -1 --minimizerTolerance=0.001 --rMin=0 --rMax=3 &> CMS_HH4b_$i\_13TeV_MaxLikelihood.out
        echo "Plot"
        combine -M MaxLikelihoodFit datacard_${i}${background_LMR}.txt -t -1 --minimizerTolerance=0.001 --rMin=0 --rMax=3 --saveNormalizations --plot --out out
done

cd $DIR

#
#for i in ${masses_LMR[@]}
#
#do
#        folder="PreselectedWithRegressionDeepCSV/limits/LMR/LMR_${i}_bern"
#        if [ -d $folder ]
#        then
#        echo "mass point $i"
#        cd $folder
#        sed -i "/PDF.*/d" datacard_${i}_bern.txt
#        sed -i "/bTag.*/d" datacard_${i}_bern.txt
#        text2workspace.py datacard_$i\_bern.txt  -o datacard_$i\_bern.root
#	echo "here"
#        combine -M Asymptotic datacard_$i\_bern.root -t -1 &> CMS_HH4b_$i\_13TeV_asymptoticCLs.out
#        #combine -M MaxLikelihoodFit --robustFit=1 --rMin=-5 --rMax=5 --plots --out out datacard_270.txt 
#        #combine -M MaxLikelihoodFit --robustFit=1 --rMin=-5 --rMax=5 datacard_$i\.root --saveNormalizations --plot &> CMS_HH4b_$i\_13TeV_MaxLikelihood.out
#        combine -M MaxLikelihoodFit --robustFit=1 --rMin=-5 --rMax=5 --plots datacard_$i\.txt &> CMS_HH4b_$i\_13TeV_MaxLikelihood.out
#        #combine -M MaxLikelihoodFit --minimizerTolerance=0.001 --rMin=0 --rMax=3 datacard_$i\.root --saveNormalizations --plot &> CMS_HH4b_$i\_13TeV_MaxLikelihood.out
#        #combine -M MaxLikelihoodFit --minimizerStrategy=2 --minimizerTolerance=0.001 --robustFit=1 --rMin=0 --rMax=5 datacard_$i\.root --saveNormalizations --plot &> CMS_HH4b_$i\_13TeV_MaxLikelihood.out
#        fi
#done\
#
#cd $DIR
