#source runLimits.sh gaus_exp 250_330 novo 550_1200 1
#source runLimits.sh novo 285_625 novo 550_1200 2

echo "LMR"
cp drawLimits_LMR.c PreselectedWithRegressionDeepCSV/limits/LMR/
cp DrawLimitPlot.cc PreselectedWithRegressionDeepCSV/limits/LMR/
cd PreselectedWithRegressionDeepCSV/limits/LMR/
root -l -b -q drawLimits_LMR.c
rm -fr drawLimits_LMR.c 
rm -fr DrawLimitPlot.cc
cd -

echo "MMR"
cp drawLimits_MMR.c PreselectedWithRegressionDeepCSV/limits/MMR/
cp DrawLimitPlot.cc PreselectedWithRegressionDeepCSV/limits/MMR/
cd PreselectedWithRegressionDeepCSV/limits/MMR/
root -l -b -q drawLimits_MMR.c
rm -fr drawLimits_MMR.c 
rm -fr DrawLimitPlot.cc 
cd -

