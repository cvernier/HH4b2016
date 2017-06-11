source launchBias_LMR.sh crystal 252_330 crystal 252_330 1 &> /dev/null & 
source launchBias_LMR.sh crystal 252_330 gaus_exp 252_330 1 &> /dev/null &
source launchBias_LMR.sh gaus_exp 252_330 crystal 252_330 1 &> /dev/null &
source launchBias_LMR.sh gaus_exp 252_330 gaus_exp 252_330 1 &> /dev/null &

source launchBias_LMR.sh crystal_1 285_624 crystal_1 285_624 2 &> /dev/null & 
source launchBias_LMR.sh crystal_1 285_624 novo 285_624 2 &> /dev/null &
source launchBias_LMR.sh novo 285_624 crystal_1 285_624 2 &> /dev/null &
source launchBias_LMR.sh novo 285_624 novo 285_624 2 &> /dev/null &

source launchBias_MMR.sh crystal_1 550_1200 crystal_1 550_1200 1 &> /dev/null &
source launchBias_MMR.sh crystal_1 550_1200 novo 550_1200 1 &> /dev/null &
source launchBias_MMR.sh novo 550_1200 crystal_1 550_1200 1 &> /dev/null &
source launchBias_MMR.sh novo 550_1200 novo 550_1200 1 &> /dev/null &

