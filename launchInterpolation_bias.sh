echo "LMR 1 interpolation"
cp InterpolateSignal_bias.C PreselectedWithRegressionDeepCSV/limits_bias/LMR/
cd PreselectedWithRegressionDeepCSV/limits_bias/LMR/
root -l -b -q "InterpolateSignal_bias.C(\"gaus_exp\", \"250_330\",1, 0)"
rm InterpolateSignal_bias.C
cd -

echo "LMR 2 interpolation"
cp InterpolateSignal_bias.C PreselectedWithRegressionDeepCSV/limits_bias/LMR/
cd PreselectedWithRegressionDeepCSV/limits_bias/LMR/
root -l -b -q "InterpolateSignal_bias.C(\"novo\", \"285_625\",2, 0)"
rm InterpolateSignal_bias.C
cd -

echo "MMR 1 interpolation"
cp InterpolateSignal_bias.C PreselectedWithRegressionDeepCSV/limits_bias/MMR/
cd PreselectedWithRegressionDeepCSV/limits_bias/MMR/
root -l -b -q "InterpolateSignal_bias.C(\"novo\", \"550_1200\",1, 1)"
rm InterpolateSignal_bias.C
cd -

./runLimits_Interpolation_bias.sh gaus_exp 250_330 novo 550_1200 1
./runLimits_Interpolation_bias.sh novo 285_625 novo 550_1200 2

echo "LMR limits plot"
cp drawLimits_LMR_interpolated.c PreselectedWithRegressionDeepCSV/limits_bias/LMR/
cp DrawLimitPlot.cc PreselectedWithRegressionDeepCSV/limits_bias/LMR/
cd PreselectedWithRegressionDeepCSV/limits_bias/LMR/
root -l -b -q drawLimits_LMR_interpolated.c 
rm -fr drawLimits_LMR_interpolated.c 
rm -fr DrawLimitPlot*
cd -

echo "MMR limits plot"
cp drawLimits_MMR_interpolated.c  PreselectedWithRegressionDeepCSV/limits_bias/MMR/
cp DrawLimitPlot.cc PreselectedWithRegressionDeepCSV/limits_bias/MMR/
cd PreselectedWithRegressionDeepCSV/limits_bias/MMR/
root -l -b -q drawLimits_MMR_interpolated.c 
rm -fr drawLimits_MMR_interpolated.c 
rm -fr DrawLimitPlot*
cd -

#Here the brazilian plot is performed with overlapping and taking information from limits_bias folder

cp drawLimits_All.c PreselectedWithRegressionDeepCSV/limits_bias/
cp DrawLimitPlot_All.cc PreselectedWithRegressionDeepCSV/limits_bias/
cd PreselectedWithRegressionDeepCSV/limits_bias/
root -l -b -q drawLimits_All.c
mv UpperLimit_all.png UpperLimit_combined_bias.png
mv UpperLimit_all.pdf UpperLimit_combined_bias.pdf
rm -fr drawLimits_All.c
rm -fr DrawLimitPlot_All*
cd -

#Here the brazilian plot is performed combining the three regions and taking information from limits_bias folder (limits_bias_graviton and limits_bias_radion in github)

cp drawLimits_Combined.c PreselectedWithRegressionDeepCSV/limits_bias/
cp DrawLimitPlot_Combined.cc PreselectedWithRegressionDeepCSV/limits_bias/
cd PreselectedWithRegressionDeepCSV/limits_bias/
root -l -b -q drawLimits_Combined.c
mv UpperLimit_combined.png UpperLimit_combined_bias.png
mv UpperLimit_combined.pdf UpperLimit_combined_bias.pdf
rm -fr drawLimits_Combined.c
rm -fr DrawLimitPlot_Combined*
cd -

