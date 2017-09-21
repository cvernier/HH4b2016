#include <TH1F.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TArrow.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TFile.h>

#include <iostream>

#include "TDRStyle.h"

bool first;

std::string itoa(int i) 
{
  char res[4];
  sprintf(res, "%d", i);
  std::string ret(res);
  return ret;
}

// Display histogram for file 
TH1* DisplayHistogram_forFile(TFile *file, std::string histogramName, int color)
{
  TH1F *h=(TH1F*)file->Get(histogramName.c_str());

  h->Scale(1./h->GetSumOfWeights());
  h->SetLineColor(color);
  h->SetLineWidth(2);
  if (first)
  {
    h->SetMaximum(h->GetMaximum()*1.5);
    h->GetYaxis()->SetTitleOffset(1.6);
    //h->SetLineStyle(2);
    h->Draw("P");

    first=false;
  }
  h->Draw("hist same");

  return h;
}

void DisplayJetProperties()
{
  std::vector<TFile*> v_files;
  v_files.push_back(new TFile("PreselectedWithRegressionDeepCSV/Histograms_Preselected_GluGluToBulkGravitonToHHTo4B_M-300_narrow_13TeV-madgraph.root"));
  v_files.push_back(new TFile("PreselectedWithRegressionDeepCSV/Histograms_Preselected_GluGluToBulkGravitonToHHTo4B_M-400_narrow_13TeV-madgraph.root"));
  v_files.push_back(new TFile("PreselectedWithRegressionDeepCSV/Histograms_Preselected_GluGluToBulkGravitonToHHTo4B_M-500_narrow_13TeV-madgraph.root"));
  v_files.push_back(new TFile("PreselectedWithRegressionDeepCSV/Histograms_Preselected_GluGluToBulkGravitonToHHTo4B_M-600_narrow_13TeV-madgraph.root"));
  v_files.push_back(new TFile("PreselectedWithRegressionDeepCSV/Histograms_Preselected_GluGluToBulkGravitonToHHTo4B_M-800_narrow_13TeV-madgraph.root"));
  v_files.push_back(new TFile("PreselectedWithRegressionDeepCSV/Histograms_Preselected_GluGluToBulkGravitonToHHTo4B_M-900_narrow_13TeV-madgraph.root"));
  TFile *f_data=new TFile("PreselectedWithRegressionDeepCSV/Histograms_Preselected_BTagTotal.root");
  std::vector <double> mean_gen={300, 400, 500, 600, 800, 900};
  std::vector<int> v_colors = {kAzure+1, kAzure+3, kRed+1, kPink+1, kPink+3, kGreen+2, kGreen+3, kBlue+1, kGray+2, kCyan, kCyan+2, kRed-4, kRed-7, kYellow-4, kGreen-4, kGreen };
  
  gROOT->SetStyle("Plain");
  TStyle *myStyle=setTDRStyle();
  myStyle->cd();
  myStyle->SetOptTitle(0);
  myStyle->SetOptStat(0);
  

  TLegend *leg=new TLegend(0.55, 0.5, 0.84, 0.89);
  leg->AddEntry(f_data->Get("h_pTreg_JetpT_1"), "13 TeV Data");
  for (unsigned int i=0; i<v_files.size(); ++i)
  {
    leg->AddEntry(v_files.at(i)->Get("h_pTreg_JetpT_1"), ("Signal m_{X} = "+itoa(mean_gen.at(i))+" GeV").c_str());
  }

  TLegend *leg2=new TLegend(0.6, 0.5, 0.89, 0.89);
  for (unsigned int i=0; i<v_files.size(); ++i)
  {
    leg2->AddEntry(v_files.at(i)->Get("h_pTreg_JetpT_1"), ("Signal m_{X} = "+itoa(mean_gen.at(i))+" GeV").c_str());
  }
  
  // Plot the 1st highest pT jets with |eta| < 2.5  
  first=true;
  TCanvas *c_pTreg_JetpT_1=new TCanvas("c_pTreg_JetpT_1", "c_pTreg_JetpT_1", 700, 700);
  DisplayHistogram_forFile(f_data, "h_pTreg_JetpT_1", kBlack);
  for (unsigned int i=0; i<v_files.size(); ++i)
  {
    DisplayHistogram_forFile(v_files.at(i), "h_pTreg_JetpT_1", v_colors.at(i));
  }
  leg->Draw();
  TArrow *line=new TArrow(30., 0.14, 30., 0); line->SetLineWidth(3);
  line->Draw();
  c_pTreg_JetpT_1->SaveAs("c_pTreg_JetpT_1.pdf");
  
  // Plot the 2nd highest pT jets with |eta| < 2.5
  first=true;
  TCanvas *c_pTreg_JetpT_2=new TCanvas("c_pTreg_JetpT_2", "c_pTreg_JetpT_2", 700, 700);
  DisplayHistogram_forFile(f_data, "h_pTreg_JetpT_2", kBlack);
  for (unsigned int i=0; i<v_files.size(); ++i)
  {
    DisplayHistogram_forFile(v_files.at(i), "h_pTreg_JetpT_2", v_colors.at(i));
  }
  leg->Draw();
  line->Draw();
  c_pTreg_JetpT_2->SaveAs("c_pTreg_JetpT_2.pdf");
  
  // Plot the 3rd highest pT jets with |eta| < 2.5
  first=true;
  TCanvas *c_pTreg_JetpT_3=new TCanvas("c_pTreg_JetpT_3", "c_pTreg_JetpT_3", 700, 700);
  DisplayHistogram_forFile(f_data, "h_pTreg_JetpT_3", kBlack);
  for (unsigned int i=0; i<v_files.size(); ++i)
  {
    DisplayHistogram_forFile(v_files.at(i), "h_pTreg_JetpT_3", v_colors.at(i));
  }
  leg->Draw();
  line->Draw();
  c_pTreg_JetpT_3->SaveAs("c_pTreg_JetpT_3.pdf");
  
  // Plot the 4th highest pT jets with |eta| < 2.5
  first=true;
  TCanvas *c_pTreg_JetpT_4=new TCanvas("c_pTreg_JetpT_4", "c_pTreg_JetpT_4", 700, 700);
  DisplayHistogram_forFile(f_data, "h_pTreg_JetpT_4", kBlack);
  for (unsigned int i=0; i<v_files.size(); ++i)
  {
    DisplayHistogram_forFile(v_files.at(i), "h_pTreg_JetpT_4", v_colors.at(i));
  }
  leg->Draw();
  line->Draw();
  c_pTreg_JetpT_4->SaveAs("c_pTreg_JetpT_4.pdf");
  
  // Plot the 5th highest pT jets with |eta| < 2.5
  first=true;
  TCanvas *c_pTreg_JetpT_5=new TCanvas("c_pTreg_JetpT_5", "c_pTreg_JetpT_5", 700, 700);
  DisplayHistogram_forFile(f_data, "h_pTreg_JetpT_5", kBlack);
  for (unsigned int i=0; i<v_files.size(); ++i)
  {
    DisplayHistogram_forFile(v_files.at(i), "h_pTreg_JetpT_5", v_colors.at(i));
  }
  leg->Draw();
  c_pTreg_JetpT_5->SaveAs("c_pTreg_JetpT_5.pdf");
  
  
  // Plot the 1st highest CSV jets with |eta| < 2.5, pT > 40 GeV  
  first=true;
  TCanvas *c_CMVAOrder_JetCMVA_1=new TCanvas("c_CMVAOrder_JetCMVA_1", "c_CMVAOrder_JetCMVA_1", 700, 700);
   DisplayHistogram_forFile(f_data, "h_CMVAOrder_JetCMVA_1", kBlack);
  for (unsigned int i=0; i<v_files.size(); ++i)
  {
    DisplayHistogram_forFile(v_files.at(i), "h_CMVAOrder_JetCMVA_1", v_colors.at(i));
  }
  leg->Draw();
  line=new TArrow(0.6324, 0.6, 0.6324, 0); line->SetLineWidth(3);
  line->Draw();
  c_CMVAOrder_JetCMVA_1->SaveAs("c_CMVAOrder_JetCMVA_1.pdf");
  
  // Plot the 2nd highest CSV jets with |eta| < 2.5, pT > 40 GeV  
  first=true;
  TCanvas *c_CMVAOrder_JetCMVA_2=new TCanvas("c_CMVAOrder_JetCMVA_2", "c_CMVAOrder_JetCMVA_2", 700, 700);
  DisplayHistogram_forFile(f_data, "h_CMVAOrder_JetCMVA_2", kBlack);
  for (unsigned int i=0; i<v_files.size(); ++i)
  {
    DisplayHistogram_forFile(v_files.at(i), "h_CMVAOrder_JetCMVA_2", v_colors.at(i));
  }
  leg->Draw();
  line=new TArrow(0.6324, 0.4, 0.6324, 0); line->SetLineWidth(3);
  line->Draw();
  c_CMVAOrder_JetCMVA_2->SaveAs("c_CMVAOrder_JetCMVA_2.pdf");
  
  // Plot the 3rd highest CSV jets with |eta| < 2.5, pT > 40 GeV  
  first=true;
  TCanvas *c_CMVAOrder_JetCMVA_3=new TCanvas("c_CMVAOrder_JetCMVA_3", "c_CMVAOrder_JetCMVA_3", 700, 700);
  DisplayHistogram_forFile(f_data, "h_CMVAOrder_JetCMVA_3", kBlack);
  for (unsigned int i=0; i<v_files.size(); ++i)
  {
    DisplayHistogram_forFile(v_files.at(i), "h_CMVAOrder_JetCMVA_3", v_colors.at(i));
  }
  leg->Draw();
  line=new TArrow(0.6324, 0.1, 0.6324, 0); line->SetLineWidth(3);
  line->Draw();
  c_CMVAOrder_JetCMVA_3->SaveAs("c_CMVAOrder_JetCMVA_3.pdf");
  
  // Plot the 4th highest CSV jets with |eta| < 2.5, pT > 40 GeV  
  first=true;
  TCanvas *c_CMVAOrder_JetCMVA_4=new TCanvas("c_CMVAOrder_JetCMVA_4", "c_CMVAOrder_JetCMVA_4", 700, 700);
  DisplayHistogram_forFile(f_data, "h_CMVAOrder_JetCMVA_4", kBlack);
  for (unsigned int i=0; i<v_files.size(); ++i)
  {
    DisplayHistogram_forFile(v_files.at(i), "h_CMVAOrder_JetCMVA_4", v_colors.at(i));
  }
  leg->Draw();
  line=new TArrow(0.6324, 0.1, 0.6324, 0); line->SetLineWidth(3);
  line->Draw();
  c_CMVAOrder_JetCMVA_4->SaveAs("c_CMVAOrder_JetCMVA_4.pdf");
  
  
  // Plot the nCbJets distribution
  first=true;
  TCanvas *c_nCbJets=new TCanvas("c_nCbJets", "c_nCbJets", 700, 700);
  DisplayHistogram_forFile(f_data, "h_nCbJets", kBlack);
  for (unsigned int i=0; i<v_files.size(); ++i)
  {
    DisplayHistogram_forFile(v_files.at(i), "h_nCbJets", v_colors.at(i));
  }
  leg->Draw();
  line=new TArrow(5, 0.5, 5, 0); line->SetLineWidth(3);
  line->Draw();
  c_nCbJets->SaveAs("c_nCbJets.pdf");
  
  
  // Plot the dR distribution between gen b quarks from a Higgs
  first=true;
  TCanvas *c_dR_genHbb=new TCanvas("c_dR_genHbb", "c_dR_genHbb", 700, 700);
  for (int i=v_files.size()-1; i>=0; --i)
  {
    ((TH1F*)(v_files.at(i)->Get("h_dR_genHbb")))->Rebin(4);
    ((TH1F*)(v_files.at(i)->Get("h_dR_genHbb")))->GetXaxis()->SetRangeUser(0, 4.);
    DisplayHistogram_forFile(v_files.at(i), "h_dR_genHbb", v_colors.at(i));
    int binx0=((TH1F*)(v_files.at(i)->Get("h_dR_genHbb")))->FindBin(0.);
    int binx1=((TH1F*)(v_files.at(i)->Get("h_dR_genHbb")))->FindBin(0.4);
    int binx2=((TH1F*)(v_files.at(i)->Get("h_dR_genHbb")))->FindBin(2.0);
    double integral1 = ((TH1F*)(v_files.at(i)->Get("h_dR_genHbb")))->Integral(binx0, binx2);
    double integral2 = ((TH1F*)(v_files.at(i)->Get("h_dR_genHbb")))->Integral(binx1, binx2);
    std::cout<<"mX = "<<mean_gen.at(i)<<", % of events with dR > 0.4 = "<<integral2/integral1*100.<<"%"<<std::endl;
  }
  leg2->Draw();
  line=new TArrow(1.5, 0.02, 1.5, 0); line->SetLineWidth(3);
  line->Draw();
  c_dR_genHbb->SaveAs("c_dR_genHbb.pdf");
  
}
  
  
  
  
  
