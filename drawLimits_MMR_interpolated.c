{
  std::vector<double> masses={550, 570, 600, 620, 650, 670, 700, 720, 750, 770, 800, 820, 840, 860, 880, 900, 920, 940, 960, 980, 1000, 1050, 1100, 1150, 1200};
  gROOT->LoadMacro("DrawLimitPlot.cc++");
  DrawLimitPlot(masses, 1, 1e4, "novo_550_1200", 1);
}
