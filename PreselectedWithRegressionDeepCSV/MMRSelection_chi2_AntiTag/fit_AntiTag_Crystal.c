{
    gSystem->Load("../../PDFs/RevCrystalBall_cxx.so");
  gROOT->LoadMacro("../../BackgroundPrediction_AntiTag_CrystalBall.cc");
  BackgroundPrediction_AntiTag_CrystalBall(360, 1200, 10, // range of plot
                                        360, 1200,     // range of fit
  					  400, 600,    // range of crystalBall mean
                                             5, 300,       // range of crystalBall width
                                             0.01, 5.1,   // range of crystalBall exponent
                                             0.01, 5.1, // range of crystalBall switch

                                        "h_mX_SB_kinFit", "h_mX_SR_kinFit", 
                                        "lin");
}
