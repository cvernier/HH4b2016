{
  gSystem->Load("../../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("../../HbbHbb_LMRSelection_chi2_150.cc++");

  HbbHbb_LMRSelection_chi2_150("Data", "BTagTotal", 300, true);
}
