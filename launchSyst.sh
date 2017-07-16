location=$1

cd PreselectedWithRegressionDeepCSV_JECm1
echo "JEC +"
./processPreSelection_Radion.sh ${location}
echo "JEC LMR"
cd LMRSelection_chi2 
./processLMRSelection.sh
echo "JEC MMR"
cd ../MMRSelection_chi2
./processMMRSelection.sh
cd ../../
cd PreselectedWithRegressionDeepCSV_JECp1
echo "JEC -"
./processPreSelection_Radion.sh
cd LMRSelection_chi2
echo "JEC LMR"
./processLMRSelection.sh
cd ../MMRSelection_chi2
echo "JEC MMR"
./processMMRSelection.sh
cd ../../
echo "JER -"
cd PreselectedWithRegressionDeepCSV_JERm1
./processPreSelection_Radion.sh ${location}
echo "JER LMR"
cd LMRSelection_chi2
./processLMRSelection.sh
echo "JER MMR"
cd ../MMRSelection_chi2
./processMMRSelection.sh
cd ../../
echo "JER +"
cd PreselectedWithRegressionDeepCSV_JERp1
./processPreSelection_Radion.sh ${location}
cd LMRSelection_chi2
echo "JER LMR"
./processLMRSelection.sh
cd ../MMRSelection_chi2
echo "JER MMR"
./processMMRSelection.sh
cd ../../

echo "bTag -"
cd PreselectedWithRegressionDeepCSV_bTagm1
./processPreSelection_Radion.sh ${location}
echo "bTag LMR"
cd LMRSelection_chi2
./processLMRSelection.sh
echo "bTag MMR"
cd ../MMRSelection_chi2
./processMMRSelection.sh
cd ../../
echo "bTag +"
cd PreselectedWithRegressionDeepCSV_bTagp1
./processPreSelection_Radion.sh ${location}
cd LMRSelection_chi2
echo "bTag LMR"
./processLMRSelection.sh
cd ../MMRSelection_chi2
echo "bTag MMR"
./processMMRSelection.sh
cd ../../

