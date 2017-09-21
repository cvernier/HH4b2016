#!/bin/bash

mass=$1

function=$2
range=$3
background="_${function}_${range}"
range_num=$5

echo $mass $function $range $range_num $location

dir_preselection="PreselectedWithRegressionDeepCSV"
dir_selection="LMRSelection_chi2"
dest_dir="PreselectedWithRegressionDeepCSV/LMRSelection_chi2/fit_bias"
background_type="fit_split_bias.c"
Type="Split"

file_histograms="Histograms_LMR_GluGluToBulkGravitonToHHTo4B_M-"

rm -fr ${dest_dir}"/SignalFits_LMRreg"
mkdir ${dest_dir}"/SignalFits_LMRreg"
folder=${dest_dir}/LMR_${mass}${background}
rm -fr $folder
mkdir $folder
echo $folder

rm -f test.c
echo " { gSystem->Load(\"PDFs/ExpGaussExp_cxx.so\"); gROOT->LoadMacro(\"Display_SignalFits_LMR_bias.cc\"); Display_SignalFits_LMR_bias(\"$dir_preselection\",\"reg\",\"$dir_selection\",\"$dest_dir\",\"$file_histograms\",${mass},\"false\", ${range_num}); }" > test.c

echo 
root -x -b -l -q test.c > $folder/signal${mass}_sig.log
mv ${dest_dir}/SignalFits_LMRreg/*${mass}* $folder/

echo "Done Signal"
echo
echo "root -x -b -l -q " $dir_preselection/$dir_selection/$background_type 
root -x -b -l -q $dir_preselection/$dir_selection/$background_type > $folder/data_bkg.log
echo "Done Background"
echo
echo "PDF"
python PDFSyst.py --mass $1 --location $4> $folder/pdf.log
mv $dest_dir/w_background$background.root $folder/
mv $dest_dir/*BackgroundFit_*${background}*.png* $folder/ 
mv $dest_dir/BackgroundFit_SR_Split* $folder/ 
rm -fr $dest_dir/Background*  
rm -fr $dest_dir/w_background*
echo "end"
