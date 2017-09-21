echo "LMR 1 interpolation"
cp InterpolateSignal.C PreselectedWithRegressionDeepCSV/limits/LMR/
cd PreselectedWithRegressionDeepCSV/limits/LMR/
root -l -b -q "InterpolateSignal.C(\"gaus_exp\", \"250_330\",1, 0)"
rm InterpolateSignal.C
cd -

echo "LMR 2 interpolation"
cp InterpolateSignal.C PreselectedWithRegressionDeepCSV/limits/LMR/
cd PreselectedWithRegressionDeepCSV/limits/LMR/
root -l -b -q "InterpolateSignal.C(\"novo\", \"285_625\",2, 0)"
rm InterpolateSignal.C
cd -

echo "MMR 1 interpolation"
cp InterpolateSignal.C PreselectedWithRegressionDeepCSV/limits/MMR/
cd PreselectedWithRegressionDeepCSV/limits/MMR/
root -l -b -q "InterpolateSignal.C(\"novo\", \"550_1200\",1, 1)"
rm InterpolateSignal.C
cd -

./runLimits_Interpolation.sh gaus_exp 250_330 novo 550_1200 1
./runLimits_Interpolation.sh novo 285_625 novo 550_1200 2

echo "LMR limits plot"
cp drawLimits_LMR_interpolated.c PreselectedWithRegressionDeepCSV/limits/LMR/
cp DrawLimitPlot.cc PreselectedWithRegressionDeepCSV/limits/LMR/
cd PreselectedWithRegressionDeepCSV/limits/LMR/
root -l -b -q drawLimits_LMR_interpolated.c 
rm -fr drawLimits_LMR_interpolated.c 
rm -fr DrawLimitPlot.cc
cd -

echo "MMR limits plot"
cp drawLimits_MMR_interpolated.c  PreselectedWithRegressionDeepCSV/limits/MMR/
cp DrawLimitPlot.cc PreselectedWithRegressionDeepCSV/limits/MMR/
cd PreselectedWithRegressionDeepCSV/limits/MMR/
root -l -b -q drawLimits_MMR_interpolated.c 
rm -fr drawLimits_MMR_interpolated.c 
rm -fr DrawLimitPlot.cc
cd -

#Here the brazilian plot is performed with overlapping and taking information from limits folder

cp drawLimits_All.c PreselectedWithRegressionDeepCSV/limits/
cp DrawLimitPlot_All.cc PreselectedWithRegressionDeepCSV/limits/
cd PreselectedWithRegressionDeepCSV/limits/
root -l -b -q drawLimits_All.c
rm -fr drawLimits_All.c
rm -fr DrawLimitPlot.cc
cd -



