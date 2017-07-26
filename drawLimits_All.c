{
  std::vector<double> masses_LMR1={260, 265, 270, 275, 280, 285, 290, 295, 300, 310, 320};
  std::vector<double> masses_LMR2={290, 295, 300, 310, 320, 330, 340, 350, 360, 370, 380, 390, 400, 410, 420, 430, 440, 450, 460, 470, 480, 490, 500, 510, 520, 530, 540, 550, 560, 570, 580, 590, 600, 610, 620};
  std::vector<double> masses_MMR={550, 570, 600, 620, 650, 670, 700, 720, 750, 770, 800, 820, 840, 860, 880, 900, 920, 940, 960, 980, 1000, 1050, 1100, 1150, 1200};  

  gROOT->LoadMacro("DrawLimitPlot_All.cc++");
  DrawLimitPlot_All(masses_LMR1,masses_LMR2,masses_MMR, 1, 1e4,"gaus_exp_250_330","novo_285_625","novo_550_1200");
}
