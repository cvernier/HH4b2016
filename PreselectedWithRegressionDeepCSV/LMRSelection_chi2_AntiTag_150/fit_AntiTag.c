{
  gSystem->Load("../../PDFs/GaussExp_cxx.so");
  gROOT->LoadMacro("../../BackgroundPrediction_AntiTag_GaussExp.cc");
  BackgroundPrediction_AntiTag_GaussExp(250, 500,10, // range of plot, binning
                                        250, 500, // range of fit
                                        255.1, 300.1,  // range of gaussExp mean
                                        6.1, 30.1,   // range of gaussExp width
                                        0.01, 3.5, // range of gaussExp exponent
                                        /*300, 500,  // range of gaussExp mean
                                        10, 70,   // range of gaussExp width
                                        0.01, 3.1, // range of gaussExp exponent
					*/"h_mX_SB_kinFit", "h_mX_SR_kinFit", 
                                        "lin");
}
