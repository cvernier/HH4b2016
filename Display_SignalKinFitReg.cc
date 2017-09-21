#include <TH1F.h>
#include <TH2F.h>
#include <TH3F.h>
#include <TH1D.h>
#include <TF1.h>
#include <TGraph.h>
#include <TLegend.h>
#include <TPaveStats.h>
#include <TLine.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TFile.h>
#include <TArrow.h>
#include <iostream>
#include "TDRStyle.h"
#include "CMS_lumi.c"
int iPeriod = 4; 
int iPos = 11;


bool first=true;

std::string itoa(int i) 
{
  char res[4];
  sprintf(res, "%d", i);
  std::string ret(res);
  return ret;
}

std::string ftoa(double i) 
{
  char res[10];
  sprintf(res, "%2.1f", i);
  std::string ret(res);
  return ret;
}

void DisplayKinFitForFile(TFile *file, TFile *fileR, double xLine)
{
  TH1F *h_mX_SR=(TH1F*)file->Get("h_mX_SR");
  TH1F *h_mX_SR_kf=(TH1F*)file->Get("h_mX_SR_kinFit")->Clone("h_mX_SR_kf");
  TH1F *h_mX_SR_kf_reg=(TH1F*)fileR->Get("h_mX_SR_kinFit")->Clone("h_mX_SR_kf_reg");

  
  h_mX_SR->Rebin(8);
  h_mX_SR_kf->Rebin(8);
  h_mX_SR_kf_reg->Rebin(8);
  h_mX_SR->GetXaxis()->SetRangeUser(200, 1400 );
  h_mX_SR_kf->GetXaxis()->SetRangeUser(200, 1400 );
  h_mX_SR_kf_reg->GetXaxis()->SetRangeUser(200, 1400 );
  h_mX_SR->Smooth(12,"R");
  h_mX_SR_kf->Smooth(12,"R");
  h_mX_SR_kf_reg->Smooth(12,"R");


  h_mX_SR->SetLineWidth(3);
  h_mX_SR_kf->SetLineWidth(3);
  h_mX_SR_kf_reg->SetLineWidth(3);
  
  h_mX_SR->SetLineColor(kGray+1);
  h_mX_SR->SetLineStyle(7);
  h_mX_SR_kf->SetLineColor(kAzure+1);
  h_mX_SR_kf->SetLineStyle(5);
  h_mX_SR_kf_reg->SetLineColor(kRed+1);
  
  if (first)
  {
    h_mX_SR_kf_reg->GetYaxis()->SetTitle("Normalized Units");
    h_mX_SR_kf_reg->GetYaxis()->SetTitleOffset(1.4);
    TH1* tmp = h_mX_SR_kf_reg->DrawNormalized("histo C");
    tmp->SetMaximum(0.25);  
    h_mX_SR_kf_reg->SetMaximum(h_mX_SR_kf_reg->GetMaximum()*1.4);
    TLegend *leg=new TLegend(0.4, 0.75, 0.89, 0.89);
    leg->SetLineColor(0);
    leg->SetFillColor(0);
    leg->AddEntry(h_mX_SR, "m_{X} Signal Peak");
    leg->AddEntry(h_mX_SR_kf, "m_{X} w/ Kinematic Fit");
    leg->AddEntry(h_mX_SR_kf_reg, "m_{X} w/ Kinematic Fit + Reg.");
    leg->Draw();
    first=false;
  }
  else h_mX_SR_kf_reg->DrawNormalized("histo same C");
  h_mX_SR_kf->DrawNormalized("histo same C");
  h_mX_SR->DrawNormalized("histo same C");
  
  TLine *line=new TLine(xLine, 0, xLine, 0.20);
  line->Draw();
  
}

void Display_SignalKinFitReg()
{
  std::vector<TFile*> v_files;  
  v_files.push_back(new TFile("PreselectedWithoutRegressionDeepCSV/LMRSelection_chi2/Histograms_LMR_GluGluToBulkGravitonToHHTo4B_M-300_narrow_13TeV-madgraph.root"));
  v_files.push_back(new TFile("PreselectedWithoutRegressionDeepCSV/LMRSelection_chi2/Histograms_LMR_GluGluToBulkGravitonToHHTo4B_M-450_narrow_13TeV-madgraph.root"));
  v_files.push_back(new TFile("PreselectedWithoutRegressionDeepCSV/MMRSelection_chi2/Histograms_MMR_GluGluToBulkGravitonToHHTo4B_M-600_narrow_13TeV-madgraph.root"));
  v_files.push_back(new TFile("PreselectedWithoutRegressionDeepCSV/MMRSelection_chi2/Histograms_MMR_GluGluToBulkGravitonToHHTo4B_M-800_narrow_13TeV-madgraph.root"));  
  v_files.push_back(new TFile("PreselectedWithoutRegressionDeepCSV/MMRSelection_chi2/Histograms_MMR_BulkGravTohhTohbbhbb_narrow_M-1000_13TeV-madgraph.root"));
  v_files.push_back(new TFile("PreselectedWithoutRegressionDeepCSV/MMRSelection_chi2/Histograms_MMR_BulkGravTohhTohbbhbb_narrow_M-1200_13TeV-madgraph.root"));

  std::vector<TFile*> v_files_reg;
  v_files_reg.push_back(new TFile("PreselectedWithRegressionDeepCSV/LMRSelection_chi2/Histograms_LMR_GluGluToBulkGravitonToHHTo4B_M-300_narrow_13TeV-madgraph.root"));
  v_files_reg.push_back(new TFile("PreselectedWithRegressionDeepCSV/LMRSelection_chi2/Histograms_LMR_GluGluToBulkGravitonToHHTo4B_M-450_narrow_13TeV-madgraph.root"));
  v_files_reg.push_back(new TFile("PreselectedWithRegressionDeepCSV/MMRSelection_chi2/Histograms_MMR_GluGluToBulkGravitonToHHTo4B_M-600_narrow_13TeV-madgraph.root"));
  v_files_reg.push_back(new TFile("PreselectedWithRegressionDeepCSV/MMRSelection_chi2/Histograms_MMR_GluGluToBulkGravitonToHHTo4B_M-800_narrow_13TeV-madgraph.root"));
  v_files_reg.push_back(new TFile("PreselectedWithRegressionDeepCSV/MMRSelection_chi2/Histograms_MMR_BulkGravTohhTohbbhbb_narrow_M-1000_13TeV-madgraph.root"));
  v_files_reg.push_back(new TFile("PreselectedWithRegressionDeepCSV/MMRSelection_chi2/Histograms_MMR_BulkGravTohhTohbbhbb_narrow_M-1200_13TeV-madgraph.root"));
  TFile *f_data_reg=new TFile("PreselectedWithRegressionDeepCSV/Histograms_Preselected_BTagTotal.root");
  std::vector <double> mean_gen={300, 450, 600, 800, 1000, 1200};
 
  gROOT->SetStyle("Plain");
  TStyle *myStyle=setTDRStyle();
  myStyle->cd();
  myStyle->SetOptTitle(0);
  myStyle->SetOptStat(0);
  
  //PAS plot
  TCanvas *c_KinFit=new TCanvas("c_KinFit", "c_KinFit", 1400, 1000);
  TPad *p_1=new TPad("p_1", "p_1", 0, 0, 1, 1);
        p_1->SetFillStyle(4000);
        p_1->SetFrameFillColor(0);
        p_1->SetBottomMargin(0.10);
        p_1->SetLeftMargin(0.15);        
  p_1->Draw();
  p_1->cd();
  writeExtraText = true;     
  extraText  = "Simulation";  
  lumi_13TeV = ""; 

  std::vector<int> choice = { 0, 1, 2, 3, 4, 5};
  for (unsigned int i=0; i<choice.size(); ++i)
  {
    DisplayKinFitForFile(v_files.at( choice.at(i) ), v_files_reg.at( choice.at(i) ), mean_gen.at( choice.at(i) ) );
  }
  CMS_lumi( p_1, iPeriod, iPos );
  c_KinFit->SaveAs("c_KinFit.pdf");
  c_KinFit->SaveAs("c_KinFit.png");
}

 
