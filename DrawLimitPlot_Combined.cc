#include <TROOT.h>
#include "TSystem.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "TGraphAsymmErrors.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TFile.h"
#include "TAxis.h"
#include "TLatex.h"
#include "../../TDRStyle.h"
#include "../../CMS_lumi.h"
#include <iostream>
int iPeriod = 4;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV 
int iPos = 11;

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


std::string itoa(int i) 
{
  char res[4];
  sprintf(res, "%d", i);
  std::string ret(res);
  return ret;
}

void DrawLimitPlot_Combined(std::vector<double> mass_1,
	std::vector<double> mass_2,
	std::vector<double> mass_3, std::vector<double> mass_c, 
	double ymin, double ymax, 
	std::string background_1,
	std::string background_2,
	std::string background_3){
    writeExtraText = true;       
	extraText  = "";  
	lumi_13TeV  = "35.9 fb^{-1}";

	// LMR1 definitions
	const unsigned int nPoints_1=mass_1.size();
	double norm_1=1000;
	// LMR2 definitions
	const unsigned int nPoints_2=mass_2.size();
	double norm_2=1000;
	// MMR1 definitions
	const unsigned int nPoints_3=mass_3.size();
	double norm_3=2;	
    // All definitions for LMR 1 and 2
    const unsigned int nPoints_c=nPoints_1 + nPoints_2;
    double xsec_c[nPoints_c], xsecNeg1_c[nPoints_c], xsecPos1_c[nPoints_c], xsecNeg2_c[nPoints_c], xsecPos2_c[nPoints_c];
    double obs_c[nPoints_c];
    double expNeg2_c[nPoints_c], expNeg1_c[nPoints_c], expPos1_c[nPoints_c], expPos2_c[nPoints_c];
    // All definitions for MMR
    double xsec_3[nPoints_3], xsecNeg1_3[nPoints_3], xsecPos1_3[nPoints_3], xsecNeg2_3[nPoints_3], xsecPos2_3[nPoints_3];
    double obs_3[nPoints_3];
    double expNeg2_3[nPoints_3], expNeg1_3[nPoints_3], expPos1_3[nPoints_3], expPos2_3[nPoints_3];

    // LOOP over all LMR
	for (unsigned int i=0; i<nPoints_1; ++i)
	{
		std::string mass_string_1=itoa(mass_1[i]);
		std::string filename_1;
		filename_1="LMR/LMR_"+mass_string_1+"_"+background_1+"/CMS_HH4b_"+mass_string_1+"_13TeV_asymptoticCLs.out";
		std::ifstream file_1(filename_1.c_str(), ios::in);
		std::string line_1;
        bool found_1= false;
        while (!found_1 && !file_1.eof() && !gSystem->AccessPathName(filename_1.c_str())) {
                          getline(file_1, line_1);
                          std::size_t pos = line_1.find("-- Asymptotic --");  
                          if (pos!=std::string::npos){
                          found_1=true;
                          }
        }
		getline(file_1, line_1); obs_c[i]=atof(line_1.substr(line_1.find("<")+1).c_str())*norm_1;
		getline(file_1, line_1); xsecNeg2_c[i]=atof(line_1.substr(line_1.find("<")+1).c_str())*norm_1;
		getline(file_1, line_1); xsecNeg1_c[i]=atof(line_1.substr(line_1.find("<")+1).c_str())*norm_1;
		getline(file_1, line_1); xsec_c[i]=atof(line_1.substr(line_1.find("<")+1).c_str())*norm_1;
		getline(file_1, line_1); xsecPos1_c[i]=atof(line_1.substr(line_1.find("<")+1).c_str())*norm_1;
		getline(file_1, line_1); xsecPos2_c[i]=atof(line_1.substr(line_1.find("<")+1).c_str())*norm_1;
		expNeg2_c[i]=xsec_c[i]-xsecNeg2_c[i];
		expNeg1_c[i]=xsec_c[i]-xsecNeg1_c[i];
		expPos1_c[i]=xsecPos1_c[i]-xsec_c[i];
		expPos2_c[i]=xsecPos2_c[i]-xsec_c[i];
        cout<<mass_string_1<<" & "<<obs_c[i]<<" & "<<xsec_c[i]<<" & "<<expNeg1_c[i]<<" & "<<expPos1_c[i]<<" \\\\"<<endl; 
   }

   for (unsigned int i=0; i<nPoints_2; ++i)
	{  
		std::string mass_string_2=itoa(mass_2[i]);
		std::string filename_2;
		filename_2="LMR/LMR_"+mass_string_2+"_"+background_2+"/CMS_HH4b_"+mass_string_2+"_13TeV_asymptoticCLs.out";
		std::ifstream file_2(filename_2.c_str(), ios::in);
		std::string line_2;
        bool found_2= false;
        while (!found_2 && !file_2.eof() && !gSystem->AccessPathName(filename_2.c_str())) {
                          getline(file_2, line_2);
                          std::size_t pos = line_2.find("-- Asymptotic --");  
                          if (pos!=std::string::npos){
                          found_2=true;
                          }
        }
		getline(file_2, line_2); obs_c[i+nPoints_1]=atof(line_2.substr(line_2.find("<")+1).c_str())*norm_2;
		getline(file_2, line_2); xsecNeg2_c[i+nPoints_1]=atof(line_2.substr(line_2.find("<")+1).c_str())*norm_2;
		getline(file_2, line_2); xsecNeg1_c[i+nPoints_1]=atof(line_2.substr(line_2.find("<")+1).c_str())*norm_2;
		getline(file_2, line_2); xsec_c[i+nPoints_1]=atof(line_2.substr(line_2.find("<")+1).c_str())*norm_2;
		getline(file_2, line_2); xsecPos1_c[i+nPoints_1]=atof(line_2.substr(line_2.find("<")+1).c_str())*norm_2;
		getline(file_2, line_2); xsecPos2_c[i+nPoints_1]=atof(line_2.substr(line_2.find("<")+1).c_str())*norm_2;
		expNeg2_c[i+nPoints_1]=xsec_c[i+nPoints_1]-xsecNeg2_c[i+nPoints_1];
		expNeg1_c[i+nPoints_1]=xsec_c[i+nPoints_1]-xsecNeg1_c[i+nPoints_1];
		expPos1_c[i+nPoints_1]=xsecPos1_c[i+nPoints_1]-xsec_c[i+nPoints_1];
		expPos2_c[i+nPoints_1]=xsecPos2_c[i+nPoints_1]-xsec_c[i+nPoints_1];
                cout<<mass_string_2<<" & "<<obs_c[i+nPoints_1]<<" & "<<xsec_c[i+nPoints_1]<<" & "<<expNeg1_c[i+nPoints_1]<<" & "<<expPos1_c[i+nPoints_1]<<" \\\\"<<endl;
}
        
for (unsigned int i=0; i<nPoints_3; ++i)
        {
                std::string mass_string_3=itoa(mass_3[i]);
                std::string filename_3;
                filename_3="MMR/MMR_"+mass_string_3+"_"+background_3+"/CMS_HH4b_"+mass_string_3+"_13TeV_asymptoticCLs.out";
                std::ifstream file_3(filename_3.c_str(), ios::in);
                std::string line_3;
        bool found_3= false;
        while (!found_3 && !file_3.eof() && !gSystem->AccessPathName(filename_3.c_str())) {
                          getline(file_3, line_3);
                          std::size_t pos = line_3.find("-- Asymptotic --");
                          if (pos!=std::string::npos){
                          found_3=true;
                          }
        }
                getline(file_3, line_3); obs_3[i]=atof(line_3.substr(line_3.find("<")+1).c_str())*norm_3;
                getline(file_3, line_3); xsecNeg2_3[i]=atof(line_3.substr(line_3.find("<")+1).c_str())*norm_3;
                getline(file_3, line_3); xsecNeg1_3[i]=atof(line_3.substr(line_3.find("<")+1).c_str())*norm_3;
                getline(file_3, line_3); xsec_3[i]=atof(line_3.substr(line_3.find("<")+1).c_str())*norm_3;
                getline(file_3, line_3); xsecPos1_3[i]=atof(line_3.substr(line_3.find("<")+1).c_str())*norm_3;
                getline(file_3, line_3); xsecPos2_3[i]=atof(line_3.substr(line_3.find("<")+1).c_str())*norm_3;
                expNeg2_3[i]=xsec_3[i]-xsecNeg2_3[i];
                expNeg1_3[i]=xsec_3[i]-xsecNeg1_3[i];
                expPos1_3[i]=xsecPos1_3[i]-xsec_3[i];
                expPos2_3[i]=xsecPos2_3[i]-xsec_3[i];
                cout<<mass_string_3<<" & "<<obs_3[i]<<" & "<<xsec_3[i]<<" & "<<expNeg1_3[i]<<" & "<<expPos1_3[i]<<" \\\\"<<endl;
        }



//Bulk model
// Graviton curve K=0.5 from github reference
std::vector<double> masses_graviton_new={260, 300, 400, 500, 600, 700, 750, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500};
std::vector<double> x_graviton_new={6.87, 136.0, 232.0, 123.0, 57.3, 28.4, 20.4, 15.0, 8.16, 4.74, 3.0, 1.9, 1.2, 0.763, 0.483};

// Graviton curve K=0.1 from github reference (scale from 0.5 to 0.1 by (0.1/0.5)^2)
std::vector<double> masses_graviton_new2={260, 300, 400, 500, 600, 700, 750, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500};
std::vector<double> x_graviton_new2={0.2748, 5.44, 9.28, 4.92, 2.29, 1.14, 0.08, 0.6, 0.33, 0.19, 0.12, 0.08, 0.05, 0.03, 0.02};

//Radion curve 1 TeV from github reference
std::vector<double> masses_radion_new={260, 300, 400, 500, 600, 700, 750, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500};
std::vector<double> x_radion_new={7.64e+03, 7.13e+03, 2.92e+03, 1.50e+03, 9.08e+02, 5.84e+02, 4.74e+02, 3.93e+02, 2.70e+02, 1.90e+02, 1.38e+02, 1.01e+02, 7.38e+01, 5.39e+01, 3.93e+01};

//Radion curve 3 TeV  from github reference (divide by 9)
std::vector<double> masses_radion_new2={260, 300, 400, 500, 600, 700, 750, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500};
std::vector<double> x_radion_new2={848.88, 792.22, 324.44, 166.66, 100.88, 64.88, 52.66, 43.66, 30.0, 21.11, 15.33, 11.22, 8.20, 5.98, 4.36};


// RS1 model
//Radion curve from github reference
double masses_radion[11]={260, 300, 400, 500, 600, 700, 750, 800, 900, 1000, 1500};
double x_radion[11]= { 7.0000671104779855,	
4.843380339233729,	
2.2033362626321535,	
1.2884373572757672,	
0.815930653669519,	
0.5326974432791105,	
0.4342318406630251,	
0.3600098167141369,	
0.24694197195075712,	
0.17295592620253558,	
0.0354691843409431
};
for(int i=0; i<11; i++ ) x_radion[i]=x_radion[i]*0.23*0.57*0.57*1000*9; // Line=xsec*BR(X->HH)*BR(HH->4b)*units*Lambda_R(3TeV->1TeV)
 	

//RunI paper
//TGraph *g_graviton_0=new TGraph(18, masses_graviton, x_graviton); g_graviton_0->SetLineWidth(2); g_graviton_0->SetLineColor(kBlue+1); g_graviton_0->SetFillColor(kWhite);
TGraph *g_radion_0=new TGraph(11, masses_radion, x_radion); g_radion_0->SetLineWidth(2); g_radion_0->SetLineColor(kOrange+2); g_radion_0->SetFillColor(kWhite);

//RunII paper
TGraph *g_graviton=new TGraph(masses_graviton_new.size(), &(masses_graviton_new[0]), &(x_graviton_new[0])); g_graviton->SetLineWidth(2); g_graviton->SetLineColor(kBlue+1); g_graviton->SetFillColor(kWhite);
TGraph *g_radion=new TGraph(masses_radion_new.size(), &(masses_radion_new[0]), &(x_radion_new[0])); g_radion->SetLineWidth(2); g_radion->SetLineColor(kBlue+1); g_radion->SetFillColor(kWhite);
TGraph *g_radion2=new TGraph(masses_radion_new2.size(), &(masses_radion_new2[0]), &(x_radion_new2[0])); g_radion2->SetLineWidth(2); g_radion2->SetLineColor(kRed+1); g_radion2->SetFillColor(kWhite);
TStyle *tdrStyle=setTDRStyle();
gROOT->SetStyle("Plain");

// Big LMR flag 
TGraphErrors *g_xsec_c=new TGraphErrors(nPoints_c, &(mass_c[0]), xsec_c);
g_xsec_c->SetTitle("; m_{X} (GeV); #sigma(pp#rightarrowX) #times Br(X#rightarrowH(b#bar{b}) H(b#bar{b})) (fb)");
g_xsec_c->SetLineWidth(2);
g_xsec_c->SetLineStyle(2);
TGraphAsymmErrors *g_xsec_1sigma_c=new TGraphAsymmErrors(nPoints_c, &(mass_c[0]), xsec_c, 0, 0, expNeg1_c, expPos1_c);
g_xsec_1sigma_c->SetLineColor(kGreen+1);
g_xsec_1sigma_c->SetFillColor(kGreen+1);
TGraphAsymmErrors *g_xsec_2sigma_c=new TGraphAsymmErrors(nPoints_c, &(mass_c[0]), xsec_c, 0, 0, expNeg2_c, expPos2_c);
g_xsec_2sigma_c->SetLineColor(kOrange);
g_xsec_2sigma_c->SetFillColor(kOrange);
TGraph *g_obs_c=new TGraph(nPoints_c, &(mass_c[0]), obs_c);
g_obs_c->SetLineWidth(2);
g_obs_c->SetLineStyle(1);


// MMR flag
TGraphErrors *g_xsec_3=new TGraphErrors(nPoints_3, &(mass_3[0]), xsec_3);
g_xsec_3->SetTitle("; m_{X} (GeV); #sigma(pp#rightarrowX) #times Br(X#rightarrowH(b#bar{b}) H(b#bar{b})) (fb)");
g_xsec_3->SetLineWidth(2);
//g_xsec_3->SetTextFont(42);
g_xsec_3->SetLineStyle(2);
TGraphAsymmErrors *g_xsec_1sigma_3=new TGraphAsymmErrors(nPoints_3, &(mass_3[0]), xsec_3, 0, 0, expNeg1_3, expPos1_3);
g_xsec_1sigma_3->SetLineColor(kGreen+1);
g_xsec_1sigma_3->SetFillColor(kGreen+1);
TGraphAsymmErrors *g_xsec_2sigma_3=new TGraphAsymmErrors(nPoints_3, &(mass_3[0]), xsec_3, 0, 0, expNeg2_3, expPos2_3);
g_xsec_2sigma_3->SetLineColor(kOrange);
g_xsec_2sigma_3->SetFillColor(kOrange);
TGraph *g_obs_3=new TGraph(nPoints_3, &(mass_3[0]), obs_3);
g_obs_3->SetLineWidth(2);
g_obs_3->SetLineStyle(1);



TCanvas *c_xsec=new TCanvas("c_xsec", "c_xsec", 1000, 700);
c_xsec->SetLogy();
g_xsec_c->SetMaximum(ymax); 
g_xsec_c->SetMinimum(ymin);
g_xsec_c->Draw("AL axis");
g_xsec_2sigma_c->Draw("3");
g_xsec_1sigma_c->Draw("3");
g_xsec_c->GetXaxis()->SetLimits(260,1200);
g_xsec_c->Draw("L");
g_xsec_3->Draw("L same");
g_xsec_2sigma_3->Draw("3 same");
g_xsec_1sigma_3->Draw("3 same");
g_xsec_3->Draw("L same");
//g_graviton->Draw("C same");
g_radion_0->Draw("C same");
g_radion->Draw("C same");
g_radion2->Draw("C same");


g_obs_c->SetMarkerStyle(20);
g_obs_c->SetMarkerColor(kBlack);	
g_obs_c->Draw("CP SAME");
g_obs_3->SetMarkerStyle(20);
g_obs_3->SetMarkerColor(kBlack);	
g_obs_3->Draw("CP SAME");
gPad->RedrawAxis("g");
g_xsec_c->GetXaxis()->SetLabelFont(42);
g_xsec_c->GetXaxis()->SetTitleFont(42);
g_xsec_c->GetYaxis()->SetLabelFont(42);
g_xsec_c->GetYaxis()->SetTitleFont(42);
c_xsec->Update();

TLegend *leg=new TLegend(0.45, 0.55, 0.90, 0.85);
leg->SetFillStyle(1); leg->SetFillColor(kWhite);
leg->SetTextFont(42);
//leg->SetHeader("Spin-2");
leg->SetHeader("Spin-0");
leg->AddEntry(g_obs_c, "Observed Upper Limit", "LP");
leg->AddEntry(g_xsec_c, "Expected Upper Limit", "L");
leg->AddEntry(g_xsec_1sigma_c, "68% Expected", "F");
leg->AddEntry(g_xsec_2sigma_c, "95% Expected", "F");
//leg->AddEntry(g_graviton,"Bulk Graviton k=0.5","L");
leg->AddEntry(g_radion_0,"RS1 Radion #Lambda= 1 TeV, kl=35","L");
leg->AddEntry(g_radion,"Bulk Radion #Lambda= 1 TeV, kl=35","L");
leg->AddEntry(g_radion2,"Bulk Radion #Lambda= 3 TeV, kl=35","L");	
leg->SetFillColor(kWhite);
leg->SetFillStyle(0);
leg->SetTextSize(0.03);
leg->SetTextFont(42);
leg->SetBorderSize(0);
leg->Draw();

CMS_lumi( c_xsec, iPeriod, iPos );
c_xsec->Update();
c_xsec->SaveAs("UpperLimit_combined.png");
c_xsec->SaveAs("UpperLimit_combined.pdf");
c_xsec->SaveAs("UpperLimit_combined.root");
c_xsec->SaveAs("UpperLimit_combined.C");

}
