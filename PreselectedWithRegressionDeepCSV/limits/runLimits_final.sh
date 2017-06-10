#!/bin/bash
#cd ../../../../../DiH_13TeV/CMSSW_7_1_5/src/ 
#cmsenv
#cd -
#for i in 260 270 300 350 400 450 500
#do
#	echo "mass point $i"
#	cd /uscms_data/d3/cvernier/4b/HbbHbb_2016/HbbHbb_Run2/Datacards/22fb_regression/LMR_$i
#	text2workspace.py datacard_$i\.txt  -o datacard_$i\.root
#	combine -M Asymptotic datacard_$i\.root  --noFitAsimov -t -1 > CMS_HH4b_$i\_13TeV_asymptoticCLs.out
	#combine HbbHbb_$i\.txt -M Asymptotic -v2 -t -1 -m $i -n CMSHH4b --rMax 1000 --rMin 0.01 &> CMS_HH4b_$i\_13TeV_asymptoticCLs.out
	#mv higgsCombineCMSHH4b.Asymptotic.mH$i\.root Limits/CMS_$i\_HH4b_13TeV_asymptoticCLs.root
	# combine -M MaxLikelihoodFit --robustFit=1 --rMin=0 --rMax=5 -t -1 --plots --out Limits/sig$i bias_study/HbbHbb_$i\.txt &> CMS_HH4b_$i\_13TeV_MaxLikelihood.out	
	
#done

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd /scratch/malara/WorkingArea/release/CMSSW_7_4_7/src/HiggsAnalysis/CombinedLimit 
cmsenv
cd $DIR

background="_crystal_1_550_1200"

masses_MMR=(
   #550 600 650 750 800 900
#400 410 420 430 440 450 460 470 480 490 500 510 520 530 540 550 560 570 580 590 600 610 620 630 640 650 660 670 680 690 700 710 720 730 740 750 760 770 780 790 800 810 820 830 840 850 860 870 880 890 900
#500 520 550 570 600 620 650 670 700 720 750 770 800 820 850 870 900
#400 420 450 470 500 520 550 570 600 620 650 670 700 720 740 750 770 790 800 820 840 850 870 900
#520 640 710 720 760 770 780 810 880
#540 560 590 610 630 730 740 830 860 890
#800 820 850 870 900
#500 550
1000
)

masses_LMR=(
    #260 270 300 350 400 450 500 550
#260 265 270 275 280 285 290 295 300 310 320 330 340 350 360 370 380 390 400 410 420 430 440 450 460 470 480 490 500 510 520 530 540 550
#320 370 420 430 470
#370 420 460 510 520 540
#510 520
#260 270 300
#300 350 400 450 500 550 600 
#400 450 500 600 
#400 
)

echo 'MMR'
for i in ${masses_MMR[@]}

do
        folder="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/limits_final/MMR_final/MMR_${i}${background}"
	if [ -d $folder ]
	then
        echo "mass point $i"
	cd $folder 
        sed -i "/PDF.*/d" datacard_$i${background}.txt
        which text2workspace.py
        text2workspace.py datacard_${i}${background}.txt  -o datacard_${i}${background}.root
	echo "here"
        combine -M Asymptotic datacard_${i}${background}.txt -t -1 &> CMS_HH4b_$i\_13TeV_asymptoticCLs.out
        combine -M MaxLikelihoodFit -t -1 --minimizerTolerance=0.001 --rMin=0 --rMax=3 datacard_${i}${background}.txt --saveNormalizations --plot &> CMS_HH4b_$i\_13TeV_MaxLikelihood.out
        #combine datacard_${i}${background}.txt -M MaxLikelihoodFit -m $i --expectSignal=$signal_strenght --rMin=-10 --rMax=10 -t ${n_toys} --toysFile=higgsCombine${name}.GenerateOnly.mH$i.${seed}.root -s ${seed} -n ${name}_${i} --robustFit=1  #--saveNormalizations --plot --out out
        #combine -M MaxLikelihoodFit --minimizerStrategy=2 --minimizerTolerance=0.001 --robustFit=1 --rMin=0 --rMax=5 datacard_$i\.txt --saveNormalizations --plot &> CMS_HH4b_$i\_13TeV_MaxLikelihood.out
	fi	
done

cd $DIR

#background_1="_gaus_exp_252_330"
background_1="_crystal_1_285_624"

echo 'LMR'
for i in ${masses_LMR[@]}

do
        folder="/scratch/malara/WorkingArea/IO_file/output_file/DeepCSV/limits_final/LMR_final1/LMR_${i}${background_1}"
	echo ${folder}
        if [ -d $folder ]
        then
        echo "mass point $i"
        echo "datacard_${i}${background_1}.txt"
        cd $folder
        sed -i "/PDF.*/d" datacard_$i${background_1}.txt
        which text2workspace.py
        text2workspace.py datacard_${i}${background_1}.txt  -o datacard_${i}${background_1}.root
        echo "here"
        mkdir out
        combine -M Asymptotic datacard_${i}${background_1}.root -t -1 &> CMS_HH4b_$i\_13TeV_asymptoticCLs.out
        combine -M MaxLikelihoodFit -t -1 --minimizerTolerance=0.001 --rMin=0 --rMax=3 datacard_${i}${background_1}.txt --saveNormalizations --plot --out out &> CMS_HH4b_$i\_13TeV_MaxLikelihood.out
        
        #combine datacard_${i}${background_1}.txt -M GenerateOnly -m $i -t 1 --saveToys -s 33447 --expectSignal=0.5 -n prova --toysNoSystematic
        #combine datacard_${i}${background_1}.txt -M MaxLikelihoodFit -m $i --expectSignal=0.5 --rMin=-10 --rMax=10 -t 1 --toysFile=higgsCombineprova.GenerateOnly.mH$i.33447.root -s 33447 -n prova_${i} --robustFit=1  --saveNormalizations --plot --out out
#	combine datacard_${i}${background_1}.txt -M GenerateOnly -m $i -t ${n_toys} --saveToys -s ${seed} --expectSignal=$signal_strenght -n ${name} --toysNoSystematic
 #               combine datacard_${i}${background}.txt -M MaxLikelihoodFit -m $i --expectSignal=$signal_strenght --rMin=-10 --rMax=10 -t ${n_toys} --toysFile=higgsCombine${name}.GenerateOnly.mH$i.${seed}.root -s ${seed} -n ${name}_${i} --robustFit=1  #--saveNormalizations --plot --out out


        #combine -M MaxLikelihoodFit -t -1 --minimizerTolerance=0.001 --rMin=0 --rMax=3 datacard_${i}${background_1}.txt --saveNormalizations --plot &> CMS_HH4b_$i\_13TeV_MaxLikelihood.out
        fi
done\

cd $DIR
