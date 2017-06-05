{
  gSystem->Load("../../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("../../HbbHbb_MMRSelection_chi2_AntiTag.cc++");
  HbbHbb_MMRSelection_chi2_AntiTag("Data", "RunBv2");
  HbbHbb_MMRSelection_chi2_AntiTag("Data", "RunBv3");
  HbbHbb_MMRSelection_chi2_AntiTag("Data", "RunC");
  HbbHbb_MMRSelection_chi2_AntiTag("Data", "RunD");
  HbbHbb_MMRSelection_chi2_AntiTag("Data", "RunE");
  HbbHbb_MMRSelection_chi2_AntiTag("Data", "RunF");
  HbbHbb_MMRSelection_chi2_AntiTag("Data", "RunG");
  HbbHbb_MMRSelection_chi2_AntiTag("Data", "RunHv1");
  HbbHbb_MMRSelection_chi2_AntiTag("Data", "RunHv2");

}
