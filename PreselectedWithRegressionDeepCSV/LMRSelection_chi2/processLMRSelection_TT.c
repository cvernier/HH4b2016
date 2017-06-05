{
  gSystem->Load("../../libPhysicsToolsKinFitter.so");
  gROOT->LoadMacro("../../HbbHbb_LMRSelection_chi2.cc++");
  //HbbHbb_LMRSelection_chi2("TT", "TT", 260, true );
  //HbbHbb_LMRSelection_chi2("TT", "ST", 270, true );
  HbbHbb_LMRSelection_chi2("TT", "ZZ", 270, true );
  /*HbbHbb_LMRSelection_chi2("TT", "GluGluToBulkGravitonToHHTo4B_M-600_narrow_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2("TT", "GluGluToBulkGravitonToHHTo4B_M-650_narrow_13TeV-madgraph", 260, true );
  HbbHbb_LMRSelection_chi2("TT", "GluGluToBulkGravitonToHHTo4B_M-700_narrow_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2("TT", "GluGluToBulkGravitonToHHTo4B_M-750_narrow_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2("TT", "GluGluToBulkGravitonToHHTo4B_M-800_narrow_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2("TT", "GluGluToBulkGravitonToHHTo4B_M-900_narrow_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2("TT", "BulkGravTohhTohbbhbb_narrow_M-1000_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2("TT", "BulkGravTohhTohbbhbb_narrow_M-1200_13TeV-madgraph");
  HbbHbb_LMRSelection_chi2("TT", "BulkGravTohhTohbbhbb_narrow_M-1400_13TeV-madgraph");
*/
}
