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
#include <TGraphAsymmErrors.h>
#include <TLatex.h>
bool data_sets=false;

bool signaleff=true;
bool cumeff=true;

int iPeriod = 4;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV 
int iPos = 11;

#include "CMS_lumi.h"
#include <iostream>


void
CMS_lumi( TPad* pad, int iPeriod, int iPosX )
{
  bool outOfFrame    = false;
  if( iPosX/10==0 )
    {
      outOfFrame = true;
    }
  int alignY_=3;
  int alignX_=2;
  if( iPosX/10==0 ) alignX_=1;
  if( iPosX==0    ) alignX_=1;
  if( iPosX==0    ) alignY_=1;
  if( iPosX/10==1 ) alignX_=1;
  if( iPosX/10==2 ) alignX_=2;
  if( iPosX/10==3 ) alignX_=3;
  if( iPosX == 0  ) relPosX = 0.14;
  int align_ = 10*alignX_ + alignY_;

  float H = pad->GetWh();
  float W = pad->GetWw();
  float l = pad->GetLeftMargin();
  float t = pad->GetTopMargin();
  float r = pad->GetRightMargin();
  float b = pad->GetBottomMargin();

  pad->cd();

  TString lumiText;
  if( iPeriod==1 )
    {
      lumiText += lumi_7TeV;
      lumiText += " (7 TeV)";
    }
  else if ( iPeriod==2 )
    {
      lumiText += lumi_8TeV;
      lumiText += " (8 TeV)";
    }
  else if( iPeriod==3 )
    {
      lumiText = lumi_8TeV;
      lumiText += " (8 TeV)";
      lumiText += " + ";
      lumiText += lumi_7TeV;
      lumiText += " (7 TeV)";
    }
  else if ( iPeriod==4 )
    {
      lumiText += lumi_13TeV;
      lumiText += " (13 TeV)";
    }
  else if ( iPeriod==7 )
    {
      if( outOfFrame ) lumiText += "#scale[0.85]{";
      lumiText += lumi_13TeV;
      lumiText += " (13 TeV)";
      lumiText += " + ";
      lumiText += lumi_8TeV;
      lumiText += " (8 TeV)";
      lumiText += " + ";
      lumiText += lumi_7TeV;
      lumiText += " (7 TeV)";
      if( outOfFrame) lumiText += "}";
    }
  else if ( iPeriod==12 )
    {
      lumiText += "8 TeV";
    }
  else if ( iPeriod==0 )
    {
      lumiText += lumi_sqrtS;
    }

  std::cout << lumiText << endl;

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);

  float extraTextSize = extraOverCmsTextSize*cmsTextSize;

  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(lumiTextSize*t);
  latex.DrawLatex(1-r,1-t+lumiTextOffset*t,lumiText);

  if( outOfFrame )
    {
      latex.SetTextFont(cmsTextFont);
      latex.SetTextAlign(11);
      latex.SetTextSize(cmsTextSize*t);
      latex.DrawLatex(l,1-t+lumiTextOffset*t,cmsText);
    }

  pad->cd();

  float posX_=0;
  if( iPosX%10<=1 )
    {
      posX_ =   l + relPosX*(1-l-r);
    }
  else if( iPosX%10==2 )
    {
      posX_ =  l + 0.5*(1-l-r);
    }
  else if( iPosX%10==3 )
    {
      posX_ =  1-r - relPosX*(1-l-r);
    }
  float posY_ = 1-t - relPosY*(1-t-b);
  if( !outOfFrame )
    {
      if( drawLogo )
        {
          posX_ =   l + 0.045*(1-l-r)*W/H;
          posY_ = 1-t - 0.045*(1-t-b);
          float xl_0 = posX_;
          float yl_0 = posY_ - 0.15;
          float xl_1 = posX_ + 0.15*H/W;
          float yl_1 = posY_;
          TASImage* CMS_logo = new TASImage("CMS-BW-label.png");
          TPad* pad_logo = new TPad("logo","logo", xl_0, yl_0, xl_1, yl_1 );
          pad_logo->Draw();
          pad_logo->cd();
          CMS_logo->Draw("X");
          pad_logo->Modified();
          pad->cd();
        }
      else
        {
          latex.SetTextFont(cmsTextFont);
          latex.SetTextSize(cmsTextSize*t);
          latex.SetTextAlign(align_);
          latex.DrawLatex(posX_, posY_, cmsText);
          if( writeExtraText )
            {
              latex.SetTextFont(extraTextFont);
              latex.SetTextAlign(align_);
              latex.SetTextSize(extraTextSize*t);
              latex.DrawLatex(posX_, posY_- relExtraDY*cmsTextSize*t, extraText);
            }
        }
    }
  else if( writeExtraText )
    {
      if( iPosX==0)
        {
          posX_ =   l +  relPosX*(1-l-r);
          posY_ =   1-t+lumiTextOffset*t;
        }
      latex.SetTextFont(extraTextFont);
      latex.SetTextSize(extraTextSize*t);
      latex.SetTextAlign(align_);
      latex.DrawLatex(posX_, posY_, extraText);
    }
  return;
}



struct Samples
{
	std::vector<TH1F *> v_Cuts;
	std::vector<TH1F *> v_CountWithPU;
} signals_lmr, signals_mmr, data;

void pushBackHistograms(Samples &sample, TFile *file, TFile * old, bool MC=true)
{
	if (MC==true)
	{
		sample.v_CountWithPU.push_back((TH1F*)old->Get("Count"));
	}
	sample.v_Cuts.push_back((TH1F*)file->Get("h_Cuts"));
}

void DisplayCutFlow()
{
	gROOT->SetStyle("Plain");
	gStyle->SetPadGridX(0);
	gStyle->SetPadGridY(0);
	gStyle->SetOptStat(0);
  writeExtraText = true;       // if extra text
  extraText  = "Simulation" ; //Preliminary";  // default extra text is "Preliminary"
  lumi_13TeV  = "";  // default is "5.1 fb^{-1}"


  int massL[10]={260, 270, 300, 350, 400, 450, 500, 550, 600, 650};
  //int massM[]={400, 450, 500, 550, 600,  650, 750, 800, 900, 1000, 1200};
  int massM[]={550, 600,  650, 750, 800, 900, 1000, 1200};


  TFile *glugluToX260_lmr=new TFile("PreselectedWithRegressionDeepCSV/LMRSelection_chi2/Histograms_LMR_GluGluToBulkGravitonToHHTo4B_M-260_narrow_13TeV-madgraph.root");
  TFile *glugluToX270_lmr=new TFile("PreselectedWithRegressionDeepCSV/LMRSelection_chi2/Histograms_LMR_GluGluToBulkGravitonToHHTo4B_M-270_narrow_13TeV-madgraph.root");
  TFile *glugluToX300_lmr=new TFile("PreselectedWithRegressionDeepCSV/LMRSelection_chi2/Histograms_LMR_GluGluToBulkGravitonToHHTo4B_M-300_narrow_13TeV-madgraph.root");
  TFile *glugluToX350_lmr=new TFile("PreselectedWithRegressionDeepCSV/LMRSelection_chi2/Histograms_LMR_GluGluToBulkGravitonToHHTo4B_M-350_narrow_13TeV-madgraph.root");
  TFile *glugluToX400_lmr=new TFile("PreselectedWithRegressionDeepCSV/LMRSelection_chi2/Histograms_LMR_GluGluToBulkGravitonToHHTo4B_M-400_narrow_13TeV-madgraph.root");
  TFile *glugluToX450_lmr=new TFile("PreselectedWithRegressionDeepCSV/LMRSelection_chi2/Histograms_LMR_GluGluToBulkGravitonToHHTo4B_M-450_narrow_13TeV-madgraph.root"); 
  TFile *glugluToX500_lmr=new TFile("PreselectedWithRegressionDeepCSV/LMRSelection_chi2/Histograms_LMR_GluGluToBulkGravitonToHHTo4B_M-500_narrow_13TeV-madgraph.root");
  TFile *glugluToX550_lmr=new TFile("PreselectedWithRegressionDeepCSV/LMRSelection_chi2/Histograms_LMR_GluGluToBulkGravitonToHHTo4B_M-550_narrow_13TeV-madgraph.root");
  TFile *glugluToX600_lmr=new TFile("PreselectedWithRegressionDeepCSV/LMRSelection_chi2/Histograms_LMR_GluGluToBulkGravitonToHHTo4B_M-600_narrow_13TeV-madgraph.root");
  TFile *glugluToX650_lmr=new TFile("PreselectedWithRegressionDeepCSV/LMRSelection_chi2/Histograms_LMR_GluGluToBulkGravitonToHHTo4B_M-650_narrow_13TeV-madgraph.root");

  //TFile *glugluToX400_mmr=new TFile("PreselectedWithRegressionDeepCSV/MMRSelection_chi2/Histograms_MMR_GluGluToBulkGravitonToHHTo4B_M-400_narrow_13TeV-madgraph.root");
  //TFile *glugluToX450_mmr=new TFile("PreselectedWithRegressionDeepCSV/MMRSelection_chi2/Histograms_MMR_GluGluToBulkGravitonToHHTo4B_M-450_narrow_13TeV-madgraph.root");
  //TFile *glugluToX500_mmr=new TFile("PreselectedWithRegressionDeepCSV/MMRSelection_chi2/Histograms_MMR_GluGluToBulkGravitonToHHTo4B_M-500_narrow_13TeV-madgraph.root");
  TFile *glugluToX550_mmr=new TFile("PreselectedWithRegressionDeepCSV/MMRSelection_chi2/Histograms_MMR_GluGluToBulkGravitonToHHTo4B_M-550_narrow_13TeV-madgraph.root");
  TFile *glugluToX600_mmr=new TFile("PreselectedWithRegressionDeepCSV/MMRSelection_chi2/Histograms_MMR_GluGluToBulkGravitonToHHTo4B_M-600_narrow_13TeV-madgraph.root");
  TFile *glugluToX650_mmr=new TFile("PreselectedWithRegressionDeepCSV/MMRSelection_chi2/Histograms_MMR_GluGluToBulkGravitonToHHTo4B_M-650_narrow_13TeV-madgraph.root");
  TFile *glugluToX750_mmr=new TFile("PreselectedWithRegressionDeepCSV/MMRSelection_chi2/Histograms_MMR_GluGluToBulkGravitonToHHTo4B_M-750_narrow_13TeV-madgraph.root");
  TFile *glugluToX800_mmr=new TFile("PreselectedWithRegressionDeepCSV/MMRSelection_chi2/Histograms_MMR_GluGluToBulkGravitonToHHTo4B_M-800_narrow_13TeV-madgraph.root");
  TFile *glugluToX900_mmr=new TFile("PreselectedWithRegressionDeepCSV/MMRSelection_chi2/Histograms_MMR_GluGluToBulkGravitonToHHTo4B_M-900_narrow_13TeV-madgraph.root");
  TFile *glugluToX1000_mmr=new TFile("PreselectedWithRegressionDeepCSV/MMRSelection_chi2/Histograms_MMR_BulkGravTohhTohbbhbb_narrow_M-1000_13TeV-madgraph.root");
  TFile *glugluToX1200_mmr=new TFile("PreselectedWithRegressionDeepCSV/MMRSelection_chi2/Histograms_MMR_BulkGravTohhTohbbhbb_narrow_M-1200_13TeV-madgraph.root");

  pushBackHistograms(signals_lmr, glugluToX260_lmr, glugluToX260_lmr);
  pushBackHistograms(signals_lmr, glugluToX270_lmr, glugluToX270_lmr);
  pushBackHistograms(signals_lmr, glugluToX300_lmr, glugluToX300_lmr);
  pushBackHistograms(signals_lmr, glugluToX350_lmr, glugluToX350_lmr);
  pushBackHistograms(signals_lmr, glugluToX400_lmr, glugluToX400_lmr);
  pushBackHistograms(signals_lmr, glugluToX450_lmr, glugluToX450_lmr);
  pushBackHistograms(signals_lmr, glugluToX500_lmr, glugluToX500_lmr);
  pushBackHistograms(signals_lmr, glugluToX550_lmr, glugluToX550_lmr);
  pushBackHistograms(signals_lmr, glugluToX600_lmr, glugluToX600_lmr);
  pushBackHistograms(signals_lmr, glugluToX650_lmr, glugluToX650_lmr);
  //pushBackHistograms(signals_mmr, glugluToX400_mmr, glugluToX400_mmr);
  //pushBackHistograms(signals_mmr, glugluToX450_mmr, glugluToX450_mmr);
  //pushBackHistograms(signals_mmr, glugluToX500_mmr, glugluToX500_mmr);
  pushBackHistograms(signals_mmr, glugluToX550_mmr, glugluToX550_mmr);
  pushBackHistograms(signals_mmr, glugluToX600_mmr, glugluToX600_mmr);
  pushBackHistograms(signals_mmr, glugluToX650_mmr, glugluToX650_mmr);
  pushBackHistograms(signals_mmr, glugluToX750_mmr, glugluToX750_mmr);
  pushBackHistograms(signals_mmr, glugluToX800_mmr, glugluToX800_mmr);
  pushBackHistograms(signals_mmr, glugluToX900_mmr, glugluToX900_mmr);
  pushBackHistograms(signals_mmr, glugluToX1000_mmr, glugluToX1000_mmr);
  pushBackHistograms(signals_mmr, glugluToX1200_mmr, glugluToX1200_mmr);

  //Get the LMR values
  std::vector<TH1F *> h_Cut_lmr;
  TH1F *h_Init_lmr=new TH1F("h_Init_lmr", "h_Init_lmr", 154, 260, 1800);
  TH1F *h_Events3_lmr=(TH1F*)h_Init_lmr->Clone("h_Events3_lmr");
  TH1F *h_Events8_lmr=(TH1F*)h_Init_lmr->Clone("h_Events8_lmr");
  TH1F *h_Events10_lmr=(TH1F*)h_Init_lmr->Clone("h_Events10_lmr");
  TH1F *h_Events16_lmr=(TH1F*)h_Init_lmr->Clone("h_Events16_lmr");
  for (unsigned int i=0; i<10; ++i)
  {
	  h_Init_lmr->SetBinContent(h_Init_lmr->FindBin(massL[i]), signals_lmr.v_CountWithPU.at(i)->GetBinContent(1));
	  std::cout<<massL[i]<<"   "<<signals_lmr.v_CountWithPU.at(i)->GetBinContent(1)<<"   "<<signals_lmr.v_Cuts.at(i)->GetBinContent(4)<< "   "<<signals_lmr.v_Cuts.at(i)->GetBinContent(8)<<"   "<< signals_lmr.v_Cuts.at(i)->GetBinContent(10)<< "  "<< signals_lmr.v_Cuts.at(i)->GetBinContent(12)<<std::endl;
	  h_Events3_lmr->SetBinContent(h_Init_lmr->FindBin(massL[i]), signals_lmr.v_Cuts.at(i)->GetBinContent(4));
	  h_Events8_lmr->SetBinContent(h_Init_lmr->FindBin(massL[i]), signals_lmr.v_Cuts.at(i)->GetBinContent(8));
	  h_Events10_lmr->SetBinContent(h_Init_lmr->FindBin(massL[i]), signals_lmr.v_Cuts.at(i)->GetBinContent(10));
	  h_Events16_lmr->SetBinContent(h_Init_lmr->FindBin(massL[i]), signals_lmr.v_Cuts.at(i)->GetBinContent(12));

  }

  //Get the MMR values
  std::vector<TH1F *> h_Cut_mmr;
  TH1F *h_Init_mmr=new TH1F("h_Init_mmr", "h_Init_mmr", 154, 260, 1800);
  TH1F *h_Events3_mmr=(TH1F*)h_Init_mmr->Clone("h_Events3_mmr");
  TH1F *h_Events8_mmr=(TH1F*)h_Init_mmr->Clone("h_Events8_mmr");
  TH1F *h_Events10_mmr=(TH1F*)h_Init_mmr->Clone("h_Events10_mmr");
  TH1F *h_Events16_mmr=(TH1F*)h_Init_mmr->Clone("h_Events16_mmr");
  for (unsigned int j=0; j<8; ++j)
  {
  h_Init_mmr->SetBinContent(h_Init_mmr->FindBin(massM[j]), signals_mmr.v_CountWithPU.at(j)->GetBinContent(1));

  std::cout<<massM[j]<<"   "<<signals_mmr.v_CountWithPU.at(j)->GetBinContent(1)<<"   "<<signals_mmr.v_Cuts.at(j)->GetBinContent(4)<< "   "<<signals_mmr.v_Cuts.at(j)->GetBinContent(8)<<"   "<< signals_mmr.v_Cuts.at(j)->GetBinContent(10)<< "  "<< signals_mmr.v_Cuts.at(j)->GetBinContent(12)<<std::endl;
  h_Events3_mmr->SetBinContent(h_Init_mmr->FindBin(massM[j]), signals_mmr.v_Cuts.at(j)->GetBinContent(4));
  h_Events8_mmr->SetBinContent(h_Init_mmr->FindBin(massM[j]), signals_mmr.v_Cuts.at(j)->GetBinContent(8));
  h_Events10_mmr->SetBinContent(h_Init_mmr->FindBin(massM[j]), signals_mmr.v_Cuts.at(j)->GetBinContent(10));
  h_Events16_mmr->SetBinContent(h_Init_mmr->FindBin(massM[j]), signals_mmr.v_Cuts.at(j)->GetBinContent(12));
  }

  //Collect the LMR information for the graph
  TGraphAsymmErrors *g_Ae_3_lmr=new TGraphAsymmErrors(h_Events3_lmr, h_Init_lmr); g_Ae_3_lmr->SetTitle("Trigger efficiency"); g_Ae_3_lmr->SetLineColor(kPink+2); g_Ae_3_lmr->SetMarkerColor(kPink+2); g_Ae_3_lmr->SetMarkerStyle(20); g_Ae_3_lmr->SetLineWidth(2);
  TGraphAsymmErrors *g_Ae_8_lmr=new TGraphAsymmErrors(h_Events8_lmr, h_Init_lmr); g_Ae_8_lmr->SetTitle("4 bjets efficiency"); g_Ae_8_lmr->SetLineColor(kBlue+2); g_Ae_8_lmr->SetMarkerColor(kBlue+2); g_Ae_8_lmr->SetMarkerStyle(20); g_Ae_8_lmr->SetLineWidth(2);
  TGraphAsymmErrors *g_Ae_10_lmr=new TGraphAsymmErrors(h_Events10_lmr, h_Init_lmr); g_Ae_10_lmr->SetTitle("HH Candidate efficiency"); g_Ae_10_lmr->SetLineColor(kGreen+2); g_Ae_10_lmr->SetMarkerColor(kGreen+2); g_Ae_10_lmr->SetMarkerStyle(20); g_Ae_10_lmr->SetLineWidth(2);
  TGraphAsymmErrors *g_Ae_16_lmr=new TGraphAsymmErrors(h_Events16_lmr, h_Init_lmr); g_Ae_16_lmr->SetTitle("SR efficiency"); g_Ae_16_lmr->SetLineColor(kRed+2);  g_Ae_16_lmr->SetMarkerColor(kRed+2); g_Ae_16_lmr->SetMarkerStyle(20); g_Ae_16_lmr->SetLineWidth(2);

  //Collect the MMR information for the graph  
  TGraphAsymmErrors *g_Ae_3_mmr=new TGraphAsymmErrors(h_Events3_mmr, h_Init_mmr); g_Ae_3_mmr->SetTitle("Trigger efficiency"); g_Ae_3_mmr->SetLineColor(kPink+2); g_Ae_3_mmr->SetMarkerColor(kPink+2); g_Ae_3_mmr->SetMarkerStyle(20); g_Ae_3_mmr->SetLineWidth(2); g_Ae_3_mmr->SetLineStyle(2);
  TGraphAsymmErrors *g_Ae_8_mmr=new TGraphAsymmErrors(h_Events8_mmr, h_Init_mmr); g_Ae_8_mmr->SetTitle("4 bjets efficiency"); g_Ae_8_mmr->SetLineColor(kBlue+2); g_Ae_8_mmr->SetMarkerColor(kBlue+2); g_Ae_8_mmr->SetMarkerStyle(20); g_Ae_8_mmr->SetLineWidth(2); g_Ae_8_mmr->SetLineStyle(2);
  TGraphAsymmErrors *g_Ae_10_mmr=new TGraphAsymmErrors(h_Events10_mmr, h_Init_mmr); g_Ae_10_mmr->SetTitle("HH Candidate efficiency"); g_Ae_10_mmr->SetLineColor(kGreen+2); g_Ae_10_mmr->SetMarkerColor(kGreen+2); g_Ae_10_mmr->SetMarkerStyle(20); g_Ae_10_mmr->SetLineWidth(2); g_Ae_10_mmr->SetLineStyle(2);
  TGraphAsymmErrors *g_Ae_16_mmr=new TGraphAsymmErrors(h_Events16_mmr, h_Init_mmr); g_Ae_16_mmr->SetTitle("SR efficiency"); g_Ae_16_mmr->SetLineColor(kRed+2);  g_Ae_16_mmr->SetMarkerColor(kRed+2); g_Ae_16_mmr->SetMarkerStyle(20); g_Ae_16_mmr->SetLineWidth(2); g_Ae_16_mmr->SetLineStyle(2);

  TCanvas *c_Ae=new TCanvas("c_Ae", "c_Ae", 700, 700);
  c_Ae->SetTickx(1);
  c_Ae->SetTicky(1);
  c_Ae->SetLogy();

  c_Ae->SetFrameFillStyle(4000);
  c_Ae->SetFrameFillColor(0000);
  g_Ae_3_lmr->SetMaximum(10.);
  g_Ae_3_lmr->SetMinimum(0.001);
  g_Ae_3_lmr->SetTitle("");
  g_Ae_3_lmr->GetXaxis()->SetLimits(100,1300);
  g_Ae_3_lmr->GetYaxis()->SetTitle("Efficiency");
  g_Ae_3_lmr->GetXaxis()->SetTitle("m_{X} (GeV)");
  g_Ae_3_lmr->GetYaxis()->SetTitle("Efficiency");
  g_Ae_3_lmr->GetYaxis()->SetTitleOffset(1.1);
  g_Ae_3_lmr->GetYaxis()->SetTitleFont(42); 	
  g_Ae_3_lmr->GetYaxis()->SetLabelFont(42); 
  g_Ae_3_lmr->GetXaxis()->SetTitleFont(42);   
  g_Ae_3_lmr->GetXaxis()->SetLabelFont(42);	
  g_Ae_3_lmr->GetYaxis()->SetLabelSize(0.03);
  g_Ae_3_lmr->GetXaxis()->SetLabelSize(0.03);
  g_Ae_3_lmr->Draw("ALP");
  g_Ae_8_lmr->Draw("LP same");
  g_Ae_10_lmr->Draw("LP same");
  g_Ae_16_lmr->Draw("LP same");
  g_Ae_3_mmr->Draw("LP same");
  g_Ae_8_mmr->Draw("LP same");
  g_Ae_10_mmr->Draw("LP same");
  g_Ae_16_mmr->Draw("LP same");
  TLine *line_1=new TLine(580, 0, 580, 1);
  line_1->SetLineWidth(1);
  line_1->Draw();

  TH1F* temp_1 = new TH1F("temp_1", "temp_1", 100, 0,1); temp_1->SetLineWidth(2); temp_1->SetLineStyle(1);  temp_1->SetLineColor(kBlack);
  TH1F* temp_2 = new TH1F("temp_2", "temp_2", 100, 0,1); temp_2->SetLineWidth(2); temp_2->SetLineStyle(2);  temp_2->SetLineColor(kBlack);  
  TLegend *leg = new TLegend(0.60,0.15,0.90,0.40,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetTextFont(42);	
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(2);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->AddEntry(g_Ae_3_lmr, "Trigger","lp");
  leg->AddEntry(g_Ae_8_lmr, "4 b-tagged jets", "lp");
  leg->AddEntry(g_Ae_10_lmr, "HH candidate", "lp");
  leg->AddEntry(g_Ae_16_lmr, "Signal Region", "lp");
  leg->AddEntry(temp_1, "LMR", "l");
  leg->AddEntry(temp_2, "MMR", "l");
  leg->Draw("same");
 
  CMS_lumi( c_Ae, iPeriod, iPos );
  
  c_Ae->Update();
  c_Ae->SaveAs("c_Ae_LMR_MMR.pdf");
  c_Ae->SaveAs("c_Ae_LMR_MMR.png");
  c_Ae->SaveAs("c_Ae_LMR_MMR.C");
  c_Ae->SaveAs("c_Ae_LMR_MMR.root");





}
