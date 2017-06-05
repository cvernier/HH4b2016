{
  gSystem->Load("../../PDFs/GaussExp_cxx.so");
  gROOT->LoadMacro("../../BackgroundPrediction_AntiTag_GaussExp.cc");
  BackgroundPrediction_AntiTag_GaussExp(360, 1200, 10, // range of plot
                                        360, 1200,     // range of fit
                                        300, 650,      // range of gaussExp mean
                                        30, 250,       // range of gaussExp width
                                        0.01, 1.1,     // range of gaussExp exponent
                                        "h_mX_SB_kinFit", "h_mX_SR_kinFit", 
                                        "lin");
}
