{
  gSystem->Load("../../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("../../HbbHbb_LMRSelection_chi2_AntiTag.cc++");
  HbbHbb_LMRSelection_chi2_AntiTag("Data", "RunBv2");
  HbbHbb_LMRSelection_chi2_AntiTag("Data", "RunBv3");
  HbbHbb_LMRSelection_chi2_AntiTag("Data", "RunC");
  HbbHbb_LMRSelection_chi2_AntiTag("Data", "RunD");
  HbbHbb_LMRSelection_chi2_AntiTag("Data", "RunE");
  HbbHbb_LMRSelection_chi2_AntiTag("Data", "RunF");
  HbbHbb_LMRSelection_chi2_AntiTag("Data", "RunG");
  HbbHbb_LMRSelection_chi2_AntiTag("Data", "RunHv1");
  HbbHbb_LMRSelection_chi2_AntiTag("Data", "RunHv2");
//  HbbHbb_LMRSelection_chi2_AntiTag("Data", "RunHv3");
}
