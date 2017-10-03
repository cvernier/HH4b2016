#include <TH1F.h>
#include <TH2F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TChain.h>
#include <TLorentzVector.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <iostream>
#include <TFractionFitter.h>
#include <TStyle.h>
#include <TPaveText.h>
#include <THStack.h>
#include <TArrow.h>
#include <TArc.h>

#include "TDRStyle.h"

#include "CMS_lumi.c"

double chi_1=1;
double chi_2=2;

double marg=19;

bool signalpoints=true;
bool data=false;
bool ttbar=false;
bool blind=false; //!!! 

bool first;

std::string itoa(int i) 
{
  char res[4];
  sprintf(res, "%d", i);
  std::string ret(res);
  return ret;
}

// Display histogram for file 
void DisplayHistogram_mH_forFile(TFile *file, std::string histogramName, int color)
{
  TH1F *h=(TH1F*)file->Get(histogramName.c_str());
  h->Scale(1./h->GetSumOfWeights());
  h->SetLineColor(color);
  h->SetLineWidth(2);
  h->Rebin(2);
  h->GetXaxis()->SetRangeUser(50, 200);
  if (first)
  {
    h->SetMaximum(h->GetMaximum()*1.2);
    h->GetYaxis()->SetTitleOffset(1.6);
    h->Draw("hist");
    first=false;
  }
  h->Draw("hist same");
}

void Plot_Purity_forFile(TFile *file, TString smass = "600", int mass = 600 )
{
  std::vector<int> v_colors = {kRed+1, kRed+3, kGreen+2, kOrange+2, kAzure+1, kAzure+3, kPink+2};//, kGray+2,kBlue+1};
  std::vector<TString> v_leg = { "Purity = 4",  "Purity = 3",  "Purity = 2",  "Purity = 1",  "Purity = 0",  "Purity = -1" };
  TCanvas c( "c", "c"+smass ); c.cd();
  c.SetLogy();
  std::vector<TString> histogramNames = { "h_mX_SR_purity4", "h_mX_SR_purity3", "h_mX_SR_purity2", "h_mX_SR_purity1", "h_mX_SR_purity0", "h_mX_SR_purity5" };
  TH1 *h;
  TLegend *leg=new TLegend(0.6, 0.7, 0.89, 0.89);
  bool _first = true;
  for( int i = 0; i < 6; i++ )
  {
      h=(TH1F*)file->Get( histogramNames.at(i) );
      //h->Scale(1./h->GetSumOfWeights());
      h->SetLineColor( v_colors.at(i) );
      h->SetLineWidth(2);
      h->Rebin(10);
      h->GetXaxis()->SetRangeUser( mass - 250, mass + 250 );
      leg->AddEntry( h, v_leg.at(i) );
      if (_first)
      {
          h->SetMaximum(h->GetMaximum()*5);
          h->GetYaxis()->SetTitleOffset(1.6);
          h->Draw("hist");
          _first=false;
      }
      h->Draw("hist same");
  }
  leg->Draw();
  c.SaveAs( "c_pur_mx"+smass+".pdf" );
}


void drawRegion(bool isData=false, double mean_H1_mass=125, double sigma_H1_mass=20, double mean_H2_mass=125, double sigma_H2_mass=20)
{
  TEllipse *circle1=new TEllipse(mean_H1_mass, mean_H2_mass, sigma_H1_mass*chi_1, sigma_H2_mass*chi_1); 
  circle1->SetLineWidth(3); 
  circle1->SetLineColor(kBlack);
  circle1->SetFillColor(kRed);
  circle1->SetFillStyle(0);
  if( isData&&blind ) circle1->SetFillStyle(1);
  circle1->Draw();
  
  TEllipse *circle2=new TEllipse(mean_H1_mass, mean_H2_mass, sigma_H1_mass*chi_2, sigma_H2_mass*chi_2, 90., 180.); circle2->SetLineWidth(3); circle2->SetNoEdges(); circle2->SetLineColor(kBlack); circle2->SetFillStyle(0); circle2->Draw();
  TEllipse *circle3=new TEllipse(mean_H1_mass, mean_H2_mass, sigma_H1_mass*chi_2, sigma_H2_mass*chi_2, 270., 360.); circle3->SetLineWidth(3); circle3->SetNoEdges(); circle3->SetLineColor(kBlack); circle3->SetFillStyle(0); circle3->Draw();
  TLine *line1=new TLine(mean_H1_mass-sigma_H1_mass*chi_2, mean_H2_mass, mean_H1_mass-sigma_H1_mass*chi_1, mean_H2_mass); line1->SetLineWidth(3); line1->SetLineColor(kBlack); line1->Draw();
  TLine *line2=new TLine(mean_H1_mass+sigma_H1_mass*chi_2, mean_H2_mass, mean_H1_mass+sigma_H1_mass*chi_1, mean_H2_mass); line2->SetLineWidth(3); line2->SetLineColor(kBlack); line2->Draw();
  TLine *line3=new TLine(mean_H1_mass, mean_H2_mass-sigma_H2_mass*chi_2, mean_H1_mass, mean_H2_mass-sigma_H2_mass*chi_1); line3->SetLineWidth(3); line3->SetLineColor(kBlack); line3->Draw();
  TLine *line4=new TLine(mean_H1_mass, mean_H2_mass+sigma_H2_mass*chi_2, mean_H1_mass, mean_H2_mass+sigma_H2_mass*chi_1); line4->SetLineWidth(3); line4->SetLineColor(kBlack); line4->Draw();
  
  TArrow *arrow1=new TArrow(mean_H1_mass, mean_H2_mass+sigma_H2_mass*chi_2*3., mean_H1_mass, mean_H2_mass, 0.02); arrow1->SetLineWidth(3); arrow1->SetLineColor(kBlack); arrow1->Draw();
  TPaveText *mod1=new TPaveText(mean_H1_mass-marg, mean_H2_mass+sigma_H2_mass*chi_2*3.-marg, mean_H1_mass+marg, mean_H2_mass+sigma_H2_mass*chi_2*3+marg);
  mod1->SetBorderSize(0); mod1->SetFillColor(0); mod1->AddText("SR"); mod1->SetLineColor(kBlack); mod1->Draw("ARC");
  TArrow *arrow2_1=new TArrow(mean_H1_mass+sigma_H1_mass*chi_2*2.5, mean_H2_mass, mean_H1_mass-sigma_H1_mass*chi_2/2., mean_H2_mass+sigma_H2_mass*chi_2/2., 0.02); arrow2_1->SetLineWidth(3); arrow2_1->SetLineColor(kBlack);     
  TArrow *arrow2_2=new TArrow(mean_H1_mass+sigma_H1_mass*chi_2*2.5, mean_H2_mass, mean_H1_mass+sigma_H1_mass*chi_2/2., mean_H2_mass-sigma_H2_mass*chi_2/2., 0.02); arrow2_2->SetLineWidth(3); arrow2_2->SetLineColor(kBlack);
  TLine *arrow2_3=new TLine(mean_H1_mass+sigma_H1_mass*chi_2*2.5, mean_H2_mass, mean_H1_mass+sigma_H1_mass*chi_2*3., mean_H2_mass); arrow2_3->SetLineWidth(3); arrow2_3->SetLineColor(kBlack);
  arrow2_1->Draw(); arrow2_2->Draw(); arrow2_3->Draw();
  TPaveText *mod2=new TPaveText(mean_H1_mass+sigma_H1_mass*chi_2*3.-marg, mean_H2_mass+marg, mean_H1_mass+sigma_H1_mass*chi_2*3.+marg, mean_H2_mass-marg);

  mod2->SetBorderSize(0); mod2->SetFillColor(0); mod2->AddText("SB"); mod2->SetLineColor(kBlack); mod2->Draw("ARC");
  
}

void DisplaymH1vsmH2_ForFile(TFile *file, bool isData=false, double mean_H1_mass=125, double sigma_H1_mass=20, double mean_H2_mass=125, double sigma_H2_mass=20)
{
  TH2F *h_mH1_mH2_asym=(TH2F*)file->Get("h_mH1_mH2_asym");
  h_mH1_mH2_asym->RebinX(4);
  h_mH1_mH2_asym->RebinY(4);
  h_mH1_mH2_asym->GetYaxis()->SetTitleOffset(1.5);
  h_mH1_mH2_asym->Draw("box");
  
  drawRegion(isData, mean_H1_mass, sigma_H1_mass, mean_H1_mass, sigma_H1_mass);
}

void DisplaymHmX(std::vector<std::string> files, std::vector<double> mean_gen,  double mean_H1_mass, double sigma_H1_mass, double mean_H2_mass, double sigma_H2_mass)
{
  std::vector<TFile*> v_files;
  for (unsigned int i=0; i<files.size(); ++i) v_files.push_back(new TFile(files.at(i).c_str()));
  //TFile *f_data=new TFile("Histograms_LMR_BTagTotal.root");
  TFile *f_data=new TFile("Histograms_MMR_BTagTotal.root");
  std::vector<int> v_colors = {kRed+1, kRed+3, kGreen+2, kOrange+2, kAzure+1, kAzure+3, kPink+2};//, kGray+2,kBlue+1};
  
  gROOT->SetStyle("Plain");
  TStyle *myStyle=setTDRStyle();
  myStyle->cd();
  myStyle->SetOptTitle(0);
  myStyle->SetOptStat(0);
  
  TLegend *leg=new TLegend(0.6, 0.7, 0.89, 0.89);
  for (unsigned int i=0; i<v_files.size(); ++i)
  {
    TH1F *h_pTOrder_JetpT_1=(TH1F*)v_files.at(i)->Get("h_pTOrder_JetpT_1");
    h_pTOrder_JetpT_1->SetLineColor(v_colors.at(i));
    h_pTOrder_JetpT_1->SetLineWidth(2);
    leg->AddEntry(h_pTOrder_JetpT_1, ("Signal m_{X} = "+itoa(mean_gen.at(i))+" GeV").c_str());
  }
  h_pTOrder_JetpT_1=(TH1F*)f_data->Get("h_pTOrder_JetpT_1");
  h_pTOrder_JetpT_1->SetLineColor(kBlack);
  h_pTOrder_JetpT_1->SetLineWidth(2);
  //leg->AddEntry(h_pTOrder_JetpT_1, "13 TeV Data");

  // Plot mH1
  first=true;
  TCanvas *c_H1_mass=new TCanvas("c_H1_mass", "c_H1_mass", 700, 700);

  for (int i=v_files.size()-1; i>=0; --i)
  {
   //  std::cout<<" here "<<std::endl;	
    DisplayHistogram_mH_forFile(v_files.at(i), "h_H1_mass", v_colors.at(i));
  }
  //DisplayHistogram_mH_forFile(f_data, "h_H1_mass", kBlack);
  //DisplayHistogram_mH_forFile(f_ttbar, "h_H1_mass", kRed);
  leg->Draw();
  c_H1_mass->SaveAs("c_H1_mass.png");
  delete c_H1_mass;
 // std::cout<<" here "<<std::endl; 
  // Plot mH2
  first=true;
  TCanvas *c_H2_mass=new TCanvas("c_H2_mass", "c_H2_mass", 700, 700);
  for (int i=v_files.size()-1; i>=0; --i)
  {
    DisplayHistogram_mH_forFile(v_files.at(i), "h_H2_mass", v_colors.at(i));
  }
  //DisplayHistogram_mH_forFile(f_data, "h_H2_mass", kBlack);
  //DisplayHistogram_mH_forFile(f_ttbar, "h_H2_mass", kRed);
  leg->Draw();
  c_H2_mass->SaveAs("c_H2_mass.png");
  delete c_H2_mass;
  
 // Plot mH1

  for (int i=v_files.size()-1; i>=0; --i)
  {
   //  std::cout<<" here "<<std::endl;	
    //Plot_Purity_forFile(v_files.at(i), s_mean_gen.at(i), mean_gen.at(i) );//, "h_mX_SR_purity0", v_colors.at(i));
  }



  // Plot mH1 vs mH2
  writeExtraText = true;       // if extra text
	extraText  = "Preliminary";  // default extra text is "Preliminary"
	lumi_13TeV  = "35.9 fb^{-1}";  // default is "5.1 fb^{-1}"
  for (unsigned int i=0; i<v_files.size(); ++i)
  {
    TCanvas *c_mH1_mH2_asym=new TCanvas("c_mH1_mH2_asym", "c_mH1_mH2_asym", 700, 700);
    DisplaymH1vsmH2_ForFile(v_files.at(i), false, mean_H1_mass, sigma_H1_mass, mean_H2_mass, sigma_H2_mass);
    CMS_lumi(c_mH1_mH2_asym, 4, 11, false );
    c_mH1_mH2_asym->SaveAs(("c_mH1_mH2_asym_"+files.at(i)+".png").c_str());
    delete c_mH1_mH2_asym;
  }
  TCanvas *c_mH1_mH2_asym_Data=new TCanvas("c_mH1_mH2_asym_Data", "c_mH1_mH2_asym_Data", 700, 700);
  DisplaymH1vsmH2_ForFile(f_data, true, mean_H1_mass, sigma_H1_mass, mean_H2_mass, sigma_H2_mass);
  CMS_lumi(c_mH1_mH2_asym_Data, 4, 11);
  c_mH1_mH2_asym_Data->SaveAs("c_mH1_mH2_asym_Data.png");
  c_mH1_mH2_asym_Data->SaveAs("c_mH1_mH2_asym_Data.pdf");
  c_mH1_mH2_asym_Data->SaveAs("c_mH1_mH2_asym_Data.root");
  c_mH1_mH2_asym_Data->SaveAs("c_mH1_mH2_asym_Data.C");

  delete c_mH1_mH2_asym_Data;
 
}    
  

