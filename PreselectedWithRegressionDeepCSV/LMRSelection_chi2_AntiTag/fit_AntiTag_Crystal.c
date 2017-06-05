{
    gSystem->Load("../../PDFs/RevCrystalBall_cxx.so");
  gROOT->LoadMacro("../../BackgroundPrediction_AntiTag_CrystalBall.cc");
  BackgroundPrediction_AntiTag_CrystalBall(252, 500,3, // range of plot, binning
                                           252, 500, // range of plot
                  		         250, 280,    // range of crystalBall mean
                                          3, 70,       // range of crystalBall width
                                          0.01, 7.1,   // range of crystalBall exponent
                                          0.01, 7.1, // range of crystalBall switch
                                        "h_mX_SB_kinFit", "h_mX_SR_kinFit", 
                                        "lin");
}
