{
  std::vector<std::string> files={
                                   "Histograms_GluGluToBulkGravitonToHHTo4B_M-500_narrow_13TeV-madgraph.root",
                                   "Histograms_GluGluToBulkGravitonToHHTo4B_M-550_narrow_13TeV-madgraph.root",
                                   "Histograms_GluGluToBulkGravitonToHHTo4B_M-650_narrow_13TeV-madgraph.root",
                                   "Histograms_GluGluToBulkGravitonToHHTo4B_M-750_narrow_13TeV-madgraph.root",
                                   "Histograms_GluGluToBulkGravitonToHHTo4B_M-800_narrow_13TeV-madgraph.root"
                                 };
                                 
  std::vector<double> mean_gen={500, 550, 650, 750, 800};
  
  gROOT->LoadMacro("../../DisplaymHmX.cc");
  DisplaymHmX(files, mean_gen, 125, 20, 125, 20);
}
