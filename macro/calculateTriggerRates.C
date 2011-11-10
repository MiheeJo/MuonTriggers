#if !defined(__CINT__) || defined(__MAKECINT__)
#include <Riostream.h>
#include <TROOT.h>

#include <TH1.h>
#include <TH2D.h>

#include <TCanvas.h>
#include "TChain.h"
#include <TDirectory.h>
#include <TFile.h>
#include <TLatex.h>
#include <TLegend.h>
#include <TMath.h>
#include <TStyle.h>
#include <TSystem.h>
#include "TTree.h"
#include "TString.h"

// miscellaneous  
#include <fstream>
#include <map>
#include <string>
#include <iostream>
#include <stdio.h>

#endif

/*
This macro will calculate and plot different trigger rates vs time (s)

 */

void calculateTriggerRates(
         TString inFile0Name = "/castor/cern.ch/user/v/velicanu/HIHLT_Validation_Test_GRIF_v10.root",
			   Int_t runNum        = 152791,
			   TString outdir      = "output",
			   char *projectTitle  = "HIAllPhy2010",
			   string source       = "data"
			   )
{
  char szBuf[256];
  int scale = 23;


  // event selectoin
  //Form("&&Run==%d&&LumiBlock>%d",runNum,goodLumiStart)
  // trigger under investigation
 //  const int ntrigs = 8;
//   const char* triggerPath[ntrigs] = {"","HLT_HIMinBiasHfOrBSC",
// 				     "L1_SingleMu3_BptxAND","HLT_HIL1SingleMu3","HLT_HIL2Mu3",
// 				     "L1_DoubleMuOpen_BptxAND","HLT_HIL1DoubleMuOpen","HLT_HIL2DoubleMu3"};

  const int ntrigs = 18;
  const char* triggerPath[ntrigs] = {
    "",
    "HLT_HIMinBiasHfOrBSC_v1",
    "HLT_HIL2Mu3_v1",
    "HLT_HIL2Mu7_v1",
    "HLT_HIL2Mu15_v1",
    "HLT_HIL2Mu3_NHitQ_v1",
    "HLT_HIL3Mu3_v1",
    "HLT_HIL1DoubleMuOpen_v1",
    "HLT_HIL1DoubleMu0_HighQ_v1",
    "HLT_HIL2DoubleMu0_v1",
    "HLT_HIL2DoubleMu0_NHitQ_v1",
    "HLT_HIL2DoubleMu0_L1HighQL2NHitQ_v1",
    "HLT_HIL2DoubleMu3_v1",
    "HLT_HIL3DoubleMuOpen_v1",
    "HLT_HIL3DoubleMuOpen_Mgt2_v1",
    "HLT_HIL3DoubleMuOpen_Mgt2_SS_v1",
    "HLT_HIL3DoubleMuOpen_Mgt2_OS_v1",
    "HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy_v1"
  };
  
  TString str;
  TH1D *ahTemp[ntrigs];
  double ahTempRate[ntrigs];  //Rates (Integrated over lumisections)
  // Load input
  TChain * HltTree = new TChain("hltbitnew/HltTree","HI OpenHLT Tree");
  HltTree->Add(inFile0Name);
  cout << inFile0Name << endl;
  cout << " # entries: " << HltTree->GetEntries() << endl;
  int nEvents = HltTree->GetEntries();
  for(int it=1; it<ntrigs; it++)
  {
    
    TH1D *ph  = new TH1D("ph","",1100,0,1100);
    HltTree->Draw("LumiBlock>>ph",str.Format("%s",triggerPath[it]));

    TH1D *phLumi = (TH1D*)gDirectory->Get("ph");
    phLumi->SetDirectory(0);
    phLumi->Scale(1./(phLumi->GetBinWidth(1)*23));// 1lumi unit=23 sec
    ahTempRate[it] = phLumi->Integral()/phLumi->GetNbinsX();
    ahTemp[it] = phLumi;

    cout<< triggerPath[it]<<"\t"<<phLumi->GetEntries()<< "\t" << ahTempRate[it] << endl;
   
  }
     
  //----------------------------
  // drawing part
  // axis
  //  TH1D * phLumiAxis = new TH1D("phLumiAxis",";Lumi Section;dEvt/dLumiSec",1100,0,1100);
  TH1D * phLumiAxis = new TH1D("phLumiAxis",";Lumi Section;Rate [Hz]",1,0,1200);
  phLumiAxis->SetMinimum(0.01);
  phLumiAxis->SetMaximum(1e+3);
  gStyle->SetOptStat(kFALSE);

  // legend
  TLegend *l0= new TLegend(0.2,0.4,0.8,0.9);
  l0->SetHeader(str.Format("HICorePhysics_L1DoubleMuOpen: %d",nEvents));
  l0->SetMargin(0.1);
  l0->SetFillStyle(0);
  l0->SetLineColor(0);
  l0->SetLineWidth(5.0);
  l0->SetTextSize(0.03); 

  // canvas
  TCanvas *pcLumi = new TCanvas("pcLumi","pcLumi");
  pcLumi->cd();
  phLumiAxis->Draw();
  pcLumi->SetLogy();
 
  for(int it=1; it<ntrigs; it++)
    {
      TH1 *phLocal = (TH1 *)(ahTemp[it]->Clone("phLocal"));
      phLocal->SetDirectory(0); 
      phLocal->SetLineColor(it);
      if (it >= 10) phLocal->SetLineColor(it+20);
      if(it==5)	phLocal->SetLineColor(kOrange+2);
      phLocal->Draw("same");

      l0->AddEntry(phLocal,str.Format("%s: %.2f%, %.2f Hz",triggerPath[it],100*phLocal->GetEntries()/nEvents,ahTempRate[it]),"l");;
     
      pcLumi->Update();
     
    }
  l0->Draw("same");
  pcLumi->SaveAs("rate.png");
}
