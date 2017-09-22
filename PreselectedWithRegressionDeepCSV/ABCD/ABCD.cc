#include <iostream>
#include <TH1F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <TStyle.h>
#include <TPaveText.h>
#include <THStack.h>
#include <TF1.h>
#include <TSystem.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TLine.h>
#include "../../CMS_lumi.c"

using namespace RooFit ;

// Plot cosmetics
int iPeriod = 4;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV 
int iPos = 11;

std::string itoa(int i) 
{
  char res[10];
  sprintf(res, "%d", i);
  std::string ret(res);
  return ret;
}

void ABCD(std::string filename1,std::string  filename2, double plot_lo, 
                                                           double plot_hi, 
                                                           double rebin, std::string mass,
                                                           std::string hist1="h_mX_SB_kinFit", 
                                                           std::string hist2="h_mX_SR_kinFit")
{
  
  gROOT->SetStyle("Plain");
  gStyle->SetPadGridX(0);
  gStyle->SetPadGridY(0);
  gStyle->SetOptStat(0000);
  writeExtraText = true;       // if extra text
  extraText  = "Preliminary";  // default extra text is "Preliminary"
  lumi_13TeV = "35.9 fb^{-1}"; 

  //Save the histograms for the fit

  TFile *f_data_tag=new TFile(filename1.c_str());
  TH1F *h_mX_SB_kinFit=(TH1F*)f_data_tag->Get(hist1.c_str());
  TH1F *h_mX_SR_kinFit=(TH1F*)f_data_tag->Get(hist2.c_str());
  TFile *f_data_antitag=new TFile(filename2.c_str());
  TH1F *h_mX_SB_kinFit_antitag=(TH1F*)f_data_antitag->Get(hist1.c_str());
  TH1F *h_mX_SR_kinFit_antitag=(TH1F*)f_data_antitag->Get(hist2.c_str());
  h_mX_SR_kinFit_antitag->Rebin(rebin);
  h_mX_SB_kinFit_antitag->Rebin(rebin);
  h_mX_SB_kinFit->Rebin(rebin);
  h_mX_SR_kinFit->Rebin(rebin);
  double nEventsSR= h_mX_SR_kinFit->Integral();

  //Calculate prediction A
  h_mX_SB_kinFit->Scale(1./h_mX_SB_kinFit->Integral());
  h_mX_SB_kinFit_antitag->Scale(1./h_mX_SB_kinFit_antitag->Integral());
  h_mX_SR_kinFit_antitag->Scale(1./h_mX_SR_kinFit_antitag->Integral());
  h_mX_SR_kinFit_antitag->Divide(h_mX_SB_kinFit_antitag);
  h_mX_SR_kinFit_antitag->Multiply(h_mX_SB_kinFit);
  h_mX_SR_kinFit_antitag->Scale(nEventsSR);
  h_mX_SR_kinFit_A=(TH1F*)h_mX_SR_kinFit_antitag->Clone("h_mX_SR_kinFit");

  //This is without normalization to 1
  RooRealVar *x;
  x=new RooRealVar("x", "m_{X} (GeV)", plot_lo, plot_hi);
  RooDataHist pred1("pred1", "Data", RooArgList(*x), h_mX_SR_kinFit_A);
  RooDataHist pred2("pred2", "Data", RooArgList(*x), h_mX_SR_kinFit);
  RooPlot *data_plot1=x->frame();
  pred1.plotOn(data_plot1, RooFit::MarkerColor(kBlue));
  RooPlot *data_plot2=x->frame();
  pred2.plotOn(data_plot2, RooFit::MarkerColor(kBlack));

  TCanvas *c_Background=new TCanvas("c_Background", "c_Background", 1200, 1200);
  c_Background->SetFillStyle(4000);
  c_Background->SetFrameFillColor(0);
  c_Background->SetRightMargin(0.01);
  c_Background->SetLeftMargin(0.15);

  TPad *p_1=new TPad("p_1", "p_1", 0, 0, 1, 1);
        p_1->SetFillStyle(4000);
        p_1->SetFrameFillColor(0);
        p_1->SetBottomMargin(0.10);
        p_1->SetLeftMargin(0.15);        
  p_1->Draw();
  p_1->cd();
  data_plot1->Draw();
  data_plot1->SetMaximum(1700);
  data_plot1->GetXaxis()->SetLabelOffset(0.01); 
  data_plot1->GetXaxis()->SetLabelFont(42);
  data_plot1->GetYaxis()->SetLabelFont(42);
  data_plot1->GetYaxis()->SetTitleFont(42);
  data_plot1->GetXaxis()->SetTitleFont(42);
  data_plot2->SetMarkerColor(kBlack);
  data_plot2->Draw("same");
  data_plot1->GetYaxis()->SetTitleOffset(1.7);
  data_plot1->SetTitle("; m_{X} (GeV); Events / 5 GeV ");
  TLegend *leg = new TLegend(0.85625,0.7021654,0.3565625,0.8903839,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.025);
  leg->SetHeader("SR Background Estimation"); 
  leg->SetLineColor(1);
  leg->SetLineWidth(3);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  h_mX_SR_kinFit_A->SetMarkerColor(kBlue);
  h_mX_SR_kinFit_A->SetLineWidth(2);  
  h_mX_SR_kinFit_A->SetLineColor(kBlue);
  h_mX_SR_kinFit->SetMarkerColor(kBlack);
  h_mX_SR_kinFit->SetLineWidth(2);
  h_mX_SR_kinFit->SetLineColor(kBlack);
  leg->AddEntry(h_mX_SR_kinFit_A,Form("Predicted at m_{h}= %s GeV",mass.c_str()) , "lep");
  leg->AddEntry(h_mX_SR_kinFit,Form("Observed at m_{h}= %s GeV",mass.c_str()), "lep");
  leg->Draw();

  CMS_lumi( p_1, iPeriod, iPos );
  c_Background->SaveAs(Form("Background_SR_%s.png", mass.c_str()) );
  c_Background->SaveAs(Form("Background_SR_%s.pdf", mass.c_str()) );

  //Normalized to 1 plot

  h_mX_SR_kinFit_A->GetXaxis()->SetRangeUser(plot_lo, plot_hi);
  h_mX_SR_kinFit->GetXaxis()->SetRangeUser(plot_lo, plot_hi);
  h_mX_SR_kinFit_A->Scale(1. / (h_mX_SR_kinFit_A->Integral()));
  h_mX_SR_kinFit->Scale(1. / (h_mX_SR_kinFit->Integral()));

  RooRealVar *x_1;
  x_1=new RooRealVar("x_1", "m_{X} (GeV)", plot_lo, plot_hi);
  RooDataHist pred1_1("pred1_1", "Data", RooArgList(*x_1), h_mX_SR_kinFit_A);
  RooDataHist pred2_1("pred2_1", "Data", RooArgList(*x_1), h_mX_SR_kinFit);
  RooPlot *data_plot1_1=x_1->frame();
  pred1_1.plotOn(data_plot1_1, RooFit::MarkerColor(kBlue));
  RooPlot *data_plot2_1=x_1->frame();
  pred2_1.plotOn(data_plot2_1, RooFit::MarkerColor(kBlack));

  TCanvas *c_Background_1=new TCanvas("c_Background", "c_Background", 1200, 1200);
  c_Background_1->SetFillStyle(4000);
  c_Background_1->SetFrameFillColor(0);
  c_Background_1->SetRightMargin(0.01);
  c_Background_1->SetLeftMargin(0.15);

  TPad *p_1_1=new TPad("p_1", "p_1", 0, 0, 1, 1);
        p_1_1->SetFillStyle(4000);
        p_1_1->SetFrameFillColor(0);
        p_1_1->SetBottomMargin(0.10);
        p_1_1->SetLeftMargin(0.15);        
  p_1_1->Draw();
  p_1_1->cd();
  data_plot1_1->Draw();
  data_plot1_1->SetMaximum(0.12);
  data_plot1_1->GetXaxis()->SetLabelOffset(0.01); 
  data_plot1_1->GetXaxis()->SetLabelFont(42);
  data_plot1_1->GetYaxis()->SetLabelFont(42);
  data_plot1_1->GetYaxis()->SetTitleFont(42);
  data_plot1_1->GetXaxis()->SetTitleFont(42);
  data_plot2_1->SetMarkerColor(kBlack);
  data_plot2_1->Draw("same");
  data_plot1_1->GetYaxis()->SetTitleOffset(1.7);
  data_plot1_1->SetTitle("; m_{X} (GeV); Normalized Units ");
  TLegend *leg_1 = new TLegend(0.85625,0.7021654,0.3565625,0.8903839,NULL,"brNDC");
  leg_1->SetBorderSize(0);
  leg_1->SetTextSize(0.025);
  leg_1->SetHeader("SR Background Estimation"); 
  leg_1->SetLineColor(1);
  leg_1->SetLineWidth(3);
  leg_1->SetFillColor(0);
  leg_1->SetFillStyle(0);
  h_mX_SR_kinFit_A->SetMarkerColor(kBlue);
  h_mX_SR_kinFit_A->SetLineWidth(2);  
  h_mX_SR_kinFit_A->SetLineColor(kBlue);
  h_mX_SR_kinFit->SetMarkerColor(kBlack);
  h_mX_SR_kinFit->SetLineWidth(2);
  h_mX_SR_kinFit->SetLineColor(kBlack);
  leg_1->AddEntry(h_mX_SR_kinFit_A,Form("Predicted at m_{h}= %s GeV",mass.c_str()) , "lep");
  leg_1->AddEntry(h_mX_SR_kinFit,Form("Observed at m_{h}= %s GeV",mass.c_str()), "lep");
  leg_1->Draw();
  CMS_lumi( p_1_1, iPeriod, iPos );
  c_Background_1->SaveAs(Form("Background_SR_norm1_%s.png", mass.c_str()) );
  c_Background_1->SaveAs(Form("Background_SR_norm1_%s.pdf", mass.c_str()) );

  //Ratio plot
  TH1F *h_mX_SR_ratio=(TH1F*)h_mX_SR_kinFit_A->Clone("h_mX_SR_ratio");
  h_mX_SR_ratio->Divide(h_mX_SR_kinFit);   
  //Kolmogorov test
  double compatibility1 = h_mX_SR_kinFit_A->KolmogorovTest(h_mX_SR_kinFit);
  cout<<"The Kolmogorov compatibility is : "<<compatibility1<<endl;
  double compatibility2 = h_mX_SR_kinFit_A->Chi2Test(h_mX_SR_kinFit,"WU");
  cout<<"The Chi2 compatibility is : "<<compatibility2<<endl;

  RooRealVar *x_2;
  x_2=new RooRealVar("x_2", "m_{X} (GeV)", plot_lo, plot_hi);
  RooDataHist pred1_2("pred1_2", "Data", RooArgList(*x_2), h_mX_SR_kinFit_A);
  RooDataHist pred2_2("pred2_2", "Data", RooArgList(*x_2), h_mX_SR_kinFit);
  RooPlot *data_plot1_2=x_2->frame();
  pred1_2.plotOn(data_plot1_2, RooFit::MarkerColor(kBlue));
  RooPlot *data_plot2_2=x_2->frame();
  pred2_2.plotOn(data_plot2_2, RooFit::MarkerColor(kBlack));
  //Ratio plot variables
  RooDataHist pull_2("pull_2", "Data", RooArgList(*x_2), h_mX_SR_ratio);
  RooPlot* frameR = x_2->frame();  
  pull_2.plotOn(frameR, RooFit::MarkerColor(kBlack));  

  double xPad = 0.3;
//  TCanvas *c_Background_2=new TCanvas("c_Background_2", "c_Background_2", 700*(1.-xPad), 700);
  TCanvas *c_Background_2=new TCanvas("c_Background_2", "c_Background_2", 700, 700);
  c_Background_2->SetFillStyle(4000);
  c_Background_2->SetFrameFillColor(0);

  TPad *p_1_2=new TPad("p_1_2", "p_1_2", 0, xPad, 1, 1);
        p_1_2->SetFillStyle(4000);
        p_1_2->SetFrameFillColor(0);
        p_1_2->SetBottomMargin(0.02);
        p_1_2->SetLeftMargin(0.15); 


  TPad* p_2 = new TPad("p_2", "p_2",0,0,1,xPad);
  p_2->SetBottomMargin((1.-xPad)/xPad*0.13);
  p_2->SetTopMargin(0.03);
  p_2->SetLeftMargin(0.15);   
  p_2->SetFillColor(0);
  p_2->SetBorderMode(0);
  p_2->SetBorderSize(2);
  p_2->SetFrameBorderMode(0);
  p_2->SetFrameBorderMode(0);

  p_1_2->Draw();
  p_2->Draw();
  p_1_2->cd();  

  data_plot1_2->Draw();
  data_plot1_2->SetMaximum(0.12);
  data_plot1_2->GetXaxis()->SetLabelOffset(0.05);
  data_plot1_2->GetXaxis()->SetLabelFont(42);
  data_plot1_2->GetYaxis()->SetLabelFont(42);
  data_plot1_2->GetYaxis()->SetTitleFont(42);
  data_plot1_2->GetXaxis()->SetTitleFont(42); 
  data_plot2_2->SetMarkerColor(kBlue);
  data_plot2_2->Draw("same");
  data_plot1_2->GetYaxis()->SetTitleOffset(1.25);
  data_plot1_2->SetTitle("; m_{X} (GeV); Normalized Units ");
  TLegend *leg_2 = new TLegend(0.85625,0.7021654,0.3565625,0.8903839,NULL,"brNDC");
  leg_2->SetBorderSize(0);
  leg_2->SetTextSize(0.025);
  leg_2->SetHeader("SR Background Estimation"); 
  leg_2->SetLineColor(1);
  leg_2->SetLineWidth(3);
  leg_2->SetFillColor(0);
  leg_2->SetFillStyle(0);
  h_mX_SR_kinFit_A->SetMarkerColor(kBlue);
  h_mX_SR_kinFit_A->SetLineWidth(2);  
  h_mX_SR_kinFit_A->SetLineColor(kBlue);
  h_mX_SR_kinFit->SetMarkerColor(kBlack);
  h_mX_SR_kinFit->SetLineWidth(2);
  h_mX_SR_kinFit->SetLineColor(kBlack);
  leg_2->AddEntry(h_mX_SR_kinFit,"Data in SR", "lep");
  leg_2->AddEntry(h_mX_SR_kinFit_A,"Predicted from ABCD Method", "lep");
  //leg_2->AddEntry(h_mX_SR_kinFit_A,Form("Predicted at m_{h}= %s GeV",mass.c_str()) , "lep");
  //leg_2->AddEntry(h_mX_SR_kinFit,Form("Observed at m_{h}= %s GeV",mass.c_str()), "lep");
  leg_2->Draw();
  CMS_lumi( p_1_2, iPeriod, iPos );

  p_2->cd();
  gPad->SetGridy(1);
  frameR->Draw();
  frameR->SetTitle("; m_{X} (GeV); Predicted / Observed");
  frameR->SetMaximum(2);
  frameR->SetMinimum(0);
  frameR->GetXaxis()->SetLabelFont(42);
  frameR->GetYaxis()->SetLabelFont(42);
  frameR->GetYaxis()->SetTitleFont(42);
  frameR->GetXaxis()->SetTitleFont(42);  
  frameR->GetYaxis()->SetTitleSize(0.07);
  frameR->GetYaxis()->SetTitleOffset(0.5);
  frameR->GetXaxis()->SetTitleSize(0.09);
  frameR->GetXaxis()->SetTitleOffset(1.0);
  frameR->GetXaxis()->SetLabelSize(0.07);
  frameR->GetYaxis()->SetLabelSize(0.06);
  frameR->Draw();
  p_1_2->cd();  

  c_Background_2->SaveAs(Form("Background_SR_norm1_ratio_%s.png", mass.c_str()) );
  c_Background_2->SaveAs(Form("Background_SR_norm1_ratio_%s.pdf", mass.c_str()) );

}


