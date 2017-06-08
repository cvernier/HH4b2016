{
  gSystem->Load("../../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("../../HbbHbb_LMRSelection_chi2_AntiTag.cc++");

  HbbHbb_LMRSelection_chi2_AntiTag("Data", "BTagTotal");
}
