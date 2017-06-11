{
    gSystem->Load("PDFs/GaussExp_cxx.so");
    gSystem->Load("PDFs/HZGRooPdfs_cxx.so");
    gSystem->Load("PDFs/RevCrystalBall_cxx.so");
    //gSystem->Load("../../PDFs/LogisticXChebychev3_cxx.so");
    gROOT->LoadMacro("BackgroundPrediction_Kinematic_Split.c");
    
    BackgroundPrediction_Kinematic_Split(250, 330, 5, // range low
                                         285, 625,    // range hi
                                         "h_mX_SB_kinFit", // histogram
                                         "lin",
                                         "../Histograms_LMR_BTagTotal.root",
                                         "PreselectedWithRegressionDeepCSV/LMRSelection_chi2/fit");
}



