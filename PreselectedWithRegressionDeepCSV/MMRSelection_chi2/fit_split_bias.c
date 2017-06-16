{
    gSystem->Load("PDFs/GaussExp_cxx.so");
    gSystem->Load("PDFs/HZGRooPdfs_cxx.so");
    gSystem->Load("PDFs/RevCrystalBall_cxx.so");
    //gSystem->Load("../../PDFs/LogisticXChebychev3_cxx.so");
    gROOT->LoadMacro("BackgroundPrediction_Kinematic_Split_MMR.c");
    
    BackgroundPrediction_Kinematic_Split_MMR(550, 1200, 10, // range low
                                               550, 1200,    // range hi
                                               "h_mX_SB_kinFit", // histogram
                                               "lin",
                                               "../Histograms_MMR_BTagTotal.root",
                                               "PreselectedWithRegressionDeepCSV/MMRSelection_chi2/fit_bias");
}



