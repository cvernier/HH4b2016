setenv dir /eos/uscms/store/user/lpchbb/HeppyNtuples/V24/

#root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "TT","JEC","JER","Trig","bTag","grav_all_upTo1400.xml")'
#root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "ST","JEC","JER","Trig","bTag","grav_all_upTo1400.xml")'
root -l -b -q '../HbbHbb_PreSelection.cc++("$dir", "ZZ","JEC","JER","Trig","bTag","grav_all_upTo1400.xml")'

