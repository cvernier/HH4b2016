{
  gSystem->Load("../../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("../../HbbHbb_LMRSelection_chi2_AntiTag_150.cc++");

  HbbHbb_LMRSelection_chi2_AntiTag_150("Data", "BTagTotal");
}
