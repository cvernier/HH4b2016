#source doLimits.sh gaus_exp 250_330 novo 550_1200 1 1 $1
#source doLimits.sh crystal 250_330 crystal_1 550_1200 1 1 $1
#source doLimits.sh novo 285_625 novo 550_1200 2 2 $1
#source doLimits.sh crystal_1 285_625 crystal_1 550_1200 2 2 $1


#source runLimits.sh gaus_exp 250_330 novo 550_1200 1
#source runLimits.sh novo 285_625 novo 550_1200 2

#cp InterpolateSignal.C PreselectedWithRegressionDeepCSV/limits/LMR/
#cd PreselectedWithRegressionDeepCSV/limits/LMR/ 
#root -l -b -q "InterpolateSignal.C(\"gaus_exp\", \"250_330\",1, 0)"
#rm InterpolateSignal.C
#cd -
#
#
#cp InterpolateSignal.C PreselectedWithRegressionDeepCSV/limits/LMR/
#cd PreselectedWithRegressionDeepCSV/limits/LMR/
#root -l -b -q"InterpolateSignal.C(\"novo\", \"285_625\",2, 0)"
#rm InterpolateSignal.C
#cd -
#
#cp InterpolateSignal.C PreselectedWithRegressionDeepCSV/limits/MMR/
#cd PreselectedWithRegressionDeepCSV/limits/MMR/
#root -l -b -q "InterpolateSignal.C(\"novo\", \"550_1200\",1, 1)"
#rm InterpolateSignal.C
#cd -

#source runLimits_Interpolation.sh gaus_exp 250_330 novo 550_1200 1
source runLimits_Interpolation.sh novo 285_625 novo 550_1200 2

