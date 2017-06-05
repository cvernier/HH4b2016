{
  gSystem->Load("../../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("../../HbbHbb_MMRSelection_chi2.cc++");
  HbbHbb_MMRSelection_chi2("TT", "TT", 260, true );
  HbbHbb_MMRSelection_chi2("TT", "ST", 270, true );
  HbbHbb_MMRSelection_chi2("TT", "ZZ", 270, true );
}
