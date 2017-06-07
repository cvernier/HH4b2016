{
  gSystem->Load("../../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("../../HbbHbb_LMRSelection_chi2.cc++");

  HbbHbb_LMRSelection_chi2("Data", "BTagTotal", 300, true);
}
