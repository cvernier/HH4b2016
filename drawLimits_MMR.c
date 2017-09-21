{
  std::vector<double> masses={550, 600, 650, 750, 800, 900, 1000}; 
  gROOT->LoadMacro("DrawLimitPlot.cc++");
  DrawLimitPlot(masses, 1, 1e4, "novo_550_1200", 1);
}
