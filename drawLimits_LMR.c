{
  std::vector<double> masses_1={260, 270, 300};
  std::vector<double> masses_2={300, 350, 400, 450, 500, 550, 600};
  gROOT->LoadMacro("DrawLimitPlot.cc++");
  DrawLimitPlot(masses_1, 10, 1e5, "gaus_exp_250_330", 0);
  DrawLimitPlot(masses_2, 10, 1e5, "novo_285_625", 0);
}
