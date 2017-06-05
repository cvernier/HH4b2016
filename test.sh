#!/bin/sh
location=$1
run="RunE"
#folder="VHBB_HEPPY_V24_JetHT__Run2016B-PromptReco-v2/160910_205020/"
#folder="VHBB_HEPPY_V24_JetHT__Run2016B-PromptReco-v2/160912_07022/"
if test $location='pisa'
        then folder="/eos/uscms/store/user/lpchbb/HeppyNtuples/V25rereco/BTagCSV/VHBB_HEPPY_V25b_BTagCSV__Run2016E-03Feb2017-v1/170226_200249/"
else folder="/gpfs/ddn/srm/cms/store/user/cvernier/VHBBHeppyV25/BTagCSV/"

echo $folder
