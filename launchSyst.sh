cd PreselectedWithRegressionDeepCSV_JECm1
echo "JEC +"
source processPreSelection_Graviton.sh
echo "JEC LMR"
cd LMRSelection_chi2 
root -l -b -q processLMRSelection_Graviton.c  &
echo "JEC MMR"
cd ../MMRSelection_chi2
root -l -b -q processMMRSelection_Graviton.c  &
cd ../../
cd PreselectedWithRegressionDeepCSV_JECp1
echo "JEC -"
source processPreSelection_Graviton.sh
cd LMRSelection_chi2
echo "JEC LMR"
root -l -b -q processLMRSelection_Graviton.c  &
cd ../MMRSelection_chi2
echo "JEC MMR"
root -l -b -q processMMRSelection_Graviton.c  &
cd ../../
echo "JER -"
cd PreselectedWithRegressionDeepCSV_JERm1
source processPreSelection_Graviton.sh
echo "JER LMR"
cd LMRSelection_chi2
root -l -b -q processLMRSelection_Graviton.c  &
echo "JER MMR"
cd ../MMRSelection_chi2
root -l -b -q processMMRSelection_Graviton.c  &
cd ../../
echo "JER +"
cd PreselectedWithRegressionDeepCSV_JERp1
source processPreSelection_Graviton.sh
cd LMRSelection_chi2
echo "JER LMR"
root -l -b -q processLMRSelection_Graviton.c  &
cd ../MMRSelection_chi2
echo "JER MMR"
root -l -b -q processMMRSelection_Graviton.c  &
cd ../../

