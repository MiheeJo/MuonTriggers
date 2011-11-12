#ifndef MATCHMU
#define MATCHMU
#include "matchMu.h"
#include "matchMu_tree.h"
#endif

#include <map>
#include <sstream>
#include <fstream>
#include <TMath.h>
#include <TLorentzVector.h>
#include <TPaletteAxis.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLatex.h>
#include <TGraphAsymmErrors.h>
#include <TMultiGraph.h>
#include <TSystem.h>

using namespace std;

// Get efficiency for all trigger pahts
int match(const char *file_name, FLAG *flag, TFile *output);
// Draw efficiency ratio (=eff of a trig paths / eff of a basic paths) plot
int ratio(TFile *output, map<string,int> *triglist, const char* refTrig, FLAG *flag);



int matchMu() {

  // Trigger path name and it's trigger level pair is needed!
  // e.g) [L1 path name] = 1; [L2 path name] = 2; [L3 path name] = 3;
  map<string,int>::iterator it_trig;

  // Dimuon triggers
  map<string,int> *triglist = new map<string,int>;
  (*triglist)["HLT_HIL1DoubleMuOpen_HighQ_v1"] = 1;
  (*triglist)["HLT_HIL2DoubleMu0_v1"] = 2;
  (*triglist)["HLT_HIL2DoubleMu3_v1"] = 2;
  (*triglist)["HLT_HIL2DoubleMu0_NHitQ_v1"] = 2;
/*  (*triglist)["HLT_HIL2DoubleMu0_L1HighQL2NHitQ_v1"] = 2;
  (*triglist)["HLT_HIL3DoubleMuOpen_v1"] = 3;
  (*triglist)["HLT_HIL3DoubleMuOpen_Mgt2_v1"] = 3;
  (*triglist)["HLT_HIL3DoubleMuOpen_Mgt2_SS_v1"] = 3;
  (*triglist)["HLT_HIL3DoubleMuOpen_Mgt2_OS_v1"] = 3;
  (*triglist)["HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy_v1"] = 3;
*/
  // Single muon triggers
  map<string,int> *triglist_single = new map<string,int>;
  (*triglist_single)["HLT_HIL2Mu3_v1"] = 2;
/*  (*triglist_single)["HLT_HIL2Mu7_v1"] = 2;
  (*triglist_single)["HLT_HIL2Mu15_v1"] = 2;
  (*triglist_single)["HLT_HIL2Mu3_NHitQ_v1"] = 2;
  (*triglist_single)["HLT_HIL3Mu3_v1"] = 3;*/

  const int nTrig = triglist->size() + triglist_single->size();

  FLAG *flag = new FLAG;
  // Matching parameters  
  flag->doGlb = true;
  flag->fdir = "/castor/cern.ch/user/m/miheejo/openHLT/cms440p10/MC425/jpsi/";

  //Array for input file names
  const int nFiles = 1;
  const char *filelist[nFiles] =  {"hltana_jpsi.root"};

  TFile *output = new TFile("./trig_eff.root","RECREATE");
  TSystem *sys = gSystem;

  for (int f=0; f<nFiles; f++) {
    ///// Dimuon triggers
    for (it_trig=triglist->begin(); it_trig!=triglist->end(); it_trig++) {
      flag->trigPath = (*it_trig).first;
      flag->trigLevel = (*it_trig).second;
      flag->dimuTrig = true;

      if (match(filelist[f],flag,output) != 0) {
        cout << filelist[f] << endl;
        return -1;
      } else {
        string tmp = "mkdir " + flag->trigPath;
        sys->Exec(tmp.c_str());
        tmp = "mv *.png " + flag->trigPath;
        sys->Exec(tmp.c_str());
      }
    }

    ///// Single muon triggers
    for (it_trig=triglist_single->begin(); it_trig!=triglist_single->end(); it_trig++) {
      flag->trigPath = (*it_trig).first;
      flag->trigLevel = (*it_trig).second;
      flag->dimuTrig = false;

      if (match(filelist[f],flag,output) != 0) {
        cout << filelist[f] << endl;
        return -1;
      } else {
        string tmp = "mkdir " + flag->trigPath;
        sys->Exec(tmp.c_str());
        tmp = "mv *.png " + flag->trigPath;
        sys->Exec(tmp.c_str());
      }
    }

    sys->Exec(Form("mkdir %s",filelist[f]));
    sys->Exec(Form("mv HLT_* %s",filelist[f]));
  } // End of all trigger paths processing

  //// Read output file to make efficiency ratio plot
  string refTrig = "HLT_HIL2DoubleMu3_v1";   //Reference trigger for efficiency ratio plot
  if (ratio(output, triglist, refTrig.c_str(), flag) != 0) {
    cout << "Cannot get efficiency ratio plot! Exit." << endl;
    return -1;
  }
  refTrig = "HLT_HIL2Mu3_v1";   //Reference trigger for efficiency ratio plot
  if (ratio(output, triglist_single, refTrig.c_str(), flag) != 0) {
    cout << "Cannot get efficiency ratio plot! Exit." << endl;
    return -1;
  }

  output->Close();
  return 0;
}

int ratio(TFile *output, map<string,int> *triglist, const char *refTrig, FLAG *flag){
  const unsigned int nTrig = triglist->size();

  ///// Get efficiency graphs
  TGraphAsymmErrors *Eff_eta[nTrig];
  TGraphAsymmErrors *Eff_phi[nTrig];
  TGraphAsymmErrors *Eff_pt[nTrig];
  TGraphAsymmErrors *Eff_eta_di[nTrig];
  TGraphAsymmErrors *Eff_phi_di[nTrig];
  TGraphAsymmErrors *Eff_pt_di[nTrig];
  TGraphAsymmErrors *Eff_mass_di[nTrig];

  int i = 0;
  int refTrigNum = 0;
  map<string,int>::iterator it_trig;
  for (it_trig=triglist->begin(); it_trig!=triglist->end(); it_trig++) {
    string title = "Eff_eta_" + (*it_trig).first;
    output->GetObject( title.c_str() , Eff_eta[i] );
    title = "Eff_phi_" + (*it_trig).first;
    output->GetObject( title.c_str() , Eff_phi[i] );
    title = "Eff_pt_" + (*it_trig).first;
    output->GetObject( title.c_str() , Eff_pt[i] );

    if (flag->dimuTrig) {
      title = "Eff_eta_di_" + (*it_trig).first;
      output->GetObject( title.c_str() , Eff_eta_di[i] );
      title = "Eff_phi_di_" + (*it_trig).first;
      output->GetObject( title.c_str() , Eff_phi_di[i] );
      title = "Eff_pt_di_" + (*it_trig).first;
      output->GetObject( title.c_str() , Eff_pt_di[i] );
      title = "Eff_mass_di_" + (*it_trig).first;
      output->GetObject( title.c_str() , Eff_mass_di[i] );
    }

    if ( (*it_trig).first.compare(refTrig) == 0 ) { // If this trigger is the reference trigger
      refTrigNum = i;    
    }

    i++;
  }

  ///// Get efficiency ratio
  TGraph *Ratio_eta[nTrig];
  TGraph *Ratio_phi[nTrig];
  TGraph *Ratio_pt[nTrig];
  TGraph *Ratio_eta_di[nTrig];
  TGraph *Ratio_phi_di[nTrig];
  TGraph *Ratio_pt_di[nTrig];
  TGraph *Ratio_mass_di[nTrig];

  ///// Number of bins for graphs
  const int nBins_eta  = Eff_eta[i]->GetN();
  const int nBins_phi  = Eff_phi[i]->GetN();
  const int nBins_pt   = Eff_pt[i]->GetN();
  const int nBins_mass = Eff_mass_di[i]->GetN();

  ///// Final efficiency ratio values
  double Eff_eta_Y[nTrig][nBins_eta];
  double Eff_phi_Y[nTrig][nBins_phi];
  double Eff_pt_Y[nTrig][nBins_pt];
  double Eff_eta_di_Y[nTrig][nBins_eta];
  double Eff_phi_di_Y[nTrig][nBins_phi];
  double Eff_pt_di_Y[nTrig][nBins_pt];
  double Eff_mass_di_Y[nTrig][nBins_mass];

  ///// Efficiency values for the reference trigger path
  const double *Eff_eta_refX = Eff_eta[refTrigNum]->GetX();
  const double *Eff_eta_refY = Eff_eta[refTrigNum]->GetY();
  double *Eff_phi_refX = Eff_phi[refTrigNum]->GetX();
  double *Eff_phi_refY = Eff_phi[refTrigNum]->GetY();
  double *Eff_pt_refX = Eff_pt[refTrigNum]->GetX();
  double *Eff_pt_refY = Eff_pt[refTrigNum]->GetY();
  double *Eff_eta_di_refX;
  double *Eff_eta_di_refY;
  double *Eff_phi_di_refX;
  double *Eff_phi_di_refY;
  double *Eff_pt_di_refX;
  double *Eff_pt_di_refY;
  double *Eff_mass_di_refX;
  double *Eff_mass_di_refY;

  if (flag->dimuTrig) {
    Eff_eta_di_refX = Eff_eta_di[refTrigNum]->GetX();
    Eff_eta_di_refY = Eff_eta_di[refTrigNum]->GetY();
    Eff_phi_di_refX = Eff_phi_di[refTrigNum]->GetX();
    Eff_phi_di_refY = Eff_phi_di[refTrigNum]->GetY();
    Eff_pt_di_refX = Eff_pt_di[refTrigNum]->GetX();
    Eff_pt_di_refY = Eff_pt_di[refTrigNum]->GetY();
    Eff_mass_di_refX = Eff_mass_di[refTrigNum]->GetX();
    Eff_mass_di_refY = Eff_mass_di[refTrigNum]->GetY();
  }

  // Calculate effciency ratio for all triggers
  for (unsigned int idx = 0 ; idx < nTrig; idx++) {
    if (idx == refTrigNum) continue;    // Skip reference trigger
    
    double *Eff_eta_newY = Eff_eta[i]->GetY();
    double *Eff_phi_newY = Eff_phi[i]->GetY();
    double *Eff_pt_newY = Eff_pt[i]->GetY();
    double *Eff_eta_di_newY;
    double *Eff_phi_di_newY;
    double *Eff_pt_di_newY;
    double *Eff_mass_di_newY;

    if (flag->dimuTrig) {
      Eff_eta_di_newY = Eff_eta_di[i]->GetY();
      Eff_phi_di_newY = Eff_phi_di[i]->GetY();
      Eff_pt_di_newY = Eff_pt_di[i]->GetY();
      Eff_mass_di_newY = Eff_mass_di[i]->GetY();
    }

    for (int bin=0; bin < nBins_eta; bin++) {
      if (Eff_eta_refY[bin] == 0) Eff_eta_Y[i][bin] = 0;
      else Eff_eta_Y[i][bin] = Eff_eta_newY[bin]/Eff_eta_refY[bin]; 
      if (Eff_eta_di_refY[bin] == 0) Eff_eta_di_Y[i][bin] = 0;
      else Eff_eta_di_Y[i][bin] = Eff_eta_di_newY[bin]/Eff_eta_di_refY[bin]; 
    }
    for (int bin=0; bin < nBins_phi; bin++) {
      if (Eff_phi_refY[bin] == 0) Eff_phi_Y[i][bin] = 0;
      else Eff_phi_Y[i][bin] = Eff_phi_newY[bin]/Eff_phi_refY[bin]; 
      if (Eff_phi_di_refY[bin] == 0) Eff_phi_di_Y[i][bin] = 0;
      else Eff_phi_di_Y[i][bin] = Eff_phi_di_newY[bin]/Eff_phi_di_refY[bin]; 
    }
    for (int bin=0; bin < nBins_pt; bin++) {
      if (Eff_pt_refY[bin] == 0) Eff_pt_Y[i][bin] = 0;
      else Eff_pt_Y[i][bin] = Eff_pt_newY[bin]/Eff_pt_refY[bin]; 
      if (Eff_pt_di_refY[bin] == 0) Eff_pt_di_Y[i][bin] = 0;
      else Eff_pt_di_Y[i][bin] = Eff_pt_di_newY[bin]/Eff_pt_di_refY[bin]; 
    }
    for (int bin=0; bin < nBins_mass; bin++) {
      if (Eff_mass_di_refY[bin] == 0) Eff_mass_di_Y[i][bin] = 0;
      else Eff_mass_di_Y[i][bin] = Eff_mass_di_newY[bin]/Eff_mass_di_refY[bin]; 
    }

  } // End of calculating effciency ratio


  TCanvas *canv = new TCanvas("ratio","ratio",800,600);
  canv->Draw();

  for (unsigned int idx = 0 ; idx < nTrig; idx++) {
    Ratio_eta[idx] = new TGraph( nBins_eta , Eff_eta_refX[refTrigNum] , Eff_eta_Y[idx] );
    Ratio_pt[idx] = new TGraph( nBins_pt , Eff_pt_refX[refTrigNum] , Eff_pt_Y[idx] );
    Ratio_phi[idx] = new TGraph( nBins_phi , Eff_phi_refX[refTrigNum] , Eff_phi_Y[idx] );
    if (flag->dimuTrig) {
      Ratio_eta_di[idx] = new TGraph( nBins_eta , Eff_eta_refX[refTrigNum] , Eff_eta_Y[idx] );
      Ratio_phi_di[idx] = new TGraph( nBins_phi , Eff_phi_refX[refTrigNum] , Eff_phi_Y[idx] );
      Ratio_pt_di[idx] = new TGraph( nBins_pt , Eff_pt_refX[refTrigNum] , Eff_pt_Y[idx] );
      Ratio_mass_di[idx] = new TGraph( nBins_mass , Eff_mass_refX[refTrigNum] , Eff_mass_Y[idx] );
    }

    if (idx == 0) {
      Ratio_eta[idx]->Draw("ap");
      Ratio_pt[idx]->Draw("ap");
      Ratio_phi[idx]->Draw("ap");
      if (flag->dimuTrig) {
        Ratio_eta_di[idx]->Draw("ap");
        Ratio_phi_di[idx]->Draw("ap");
        Ratio_pt_di[idx]->Draw("ap");
        Ratio_mass_di[idx]->Draw("ap");
      }
    } else {
      Ratio_eta[idx]->Draw("p");
      Ratio_pt[idx]->Draw("p");
      Ratio_phi[idx]->Draw("p");
      if (flag->dimuTrig) {
        Ratio_eta_di[idx]->Draw("p");
        Ratio_phi_di[idx]->Draw("p");
        Ratio_pt_di[idx]->Draw("p");
        Ratio_mass_di[idx]->Draw("p");
      }
    }
  }

  canv->SaveAs("Ratio_efficiency.png");

  delete canv;

  for (int idx = 0 ; idx < nTrig; idx++) {
    delete Ratio_eta[idx];
    delete Ratio_phi[idx];
    delete Ratio_pt[idx];

    if (flag->dimuTrig) {
      delete Ratio_eta_di[idx];
      delete Ratio_phi_di[idx];
      delete Ratio_pt_di[idx];
      delete Ratio_mass_di[idx];
    }
  }

  return 0;
}

int match(const char *file_name, FLAG *flag, TFile *output) {
  // Efficiency
  TH2F *Eff_etapt = new TH2F("eff_etapt","eff_etapt;single mu #eta;single mu p_{T}",ETA,-2.4,2.4,PT,0,20);
  TH2F *Eff_acc_etapt = new TH2F("eff_acc_etapt","eff_acc_etapt;single mu #eta;single mu p_{T}",ETA,-2.4,2.4,PT,0,20);
  TH2F *Eff_match_etapt = new TH2F("eff_match_etapt","eff_match_etap;single mu #eta;single mu p_{T}",ETA,-2.4,2.4,PT,0,20);

  TGraphAsymmErrors *Eff_eta = new TGraphAsymmErrors();
  TGraphAsymmErrors *Eff_phi = new TGraphAsymmErrors();
  TGraphAsymmErrors *Eff_pt = new TGraphAsymmErrors();
  TH1F *Eff_acc_eta = new TH1F("eff_acc_eta","eff_acc_eta;single mu #eta",ETA,-2.4,2.4);
  TH1F *Eff_acc_phi = new TH1F("eff_acc_phi","eff_acc_phi;single mu #phi",PHI,-PI,PI);
  TH1F *Eff_acc_pt = new TH1F("eff_acc_pt","eff_acc_pt;single mu p_{T}",PT,0,20);
  TH1F *Eff_match_eta = new TH1F("eff_match_eta","eff_match_eta;single mu #eta",ETA,-2.4,2.4);
  TH1F *Eff_match_phi = new TH1F("eff_match_phi","eff_match_phi;single mu #phi",PHI,-PI,PI);
  TH1F *Eff_match_pt = new TH1F("eff_match_pt","eff_match_pt;single mu p_{T}",PT,0,20);

  TH2F *Eff_etapt_di = new TH2F("eff_etapt_di","eff_etapt_di;dimu #eta;dimu p_{T}",ETA,-2.4,2.4,PT,0,20);
  TH2F *Eff_acc_etapt_di = new TH2F("eff_acc_etapt_di","eff_acc_etapt_di;dimu #eta;dimu p_{T}",ETA,-2.4,2.4,PT,0,20);
  TH2F *Eff_match_etapt_di = new TH2F("eff_match_etapt_di","eff_match_etapt_di;dimu #eta;dimu p_{T}",ETA,-2.4,2.4,PT,0,20);

  TGraphAsymmErrors *Eff_eta_di = new TGraphAsymmErrors();
  TGraphAsymmErrors *Eff_phi_di = new TGraphAsymmErrors();
  TGraphAsymmErrors *Eff_pt_di = new TGraphAsymmErrors();
  TGraphAsymmErrors *Eff_mass_di = new TGraphAsymmErrors();
  TH1F *Eff_acc_eta_di = new TH1F("eff_acc_eta_di","eff_acc_eta_di;dimu #eta",ETA,-2.4,2.4);
  TH1F *Eff_acc_phi_di = new TH1F("eff_acc_phi_di","eff_acc_phi_di;dimu #phi",PHI,-PI,PI);
  TH1F *Eff_acc_pt_di = new TH1F("eff_acc_pt_di","eff_acc_pt_di;dimu p_{T}",PT,0,20);
  TH1F *Eff_acc_mass_di = new TH1F("eff_acc_mass_di","eff_acc_mass_di;dimu mass",40,0,20);
  TH1F *Eff_match_eta_di = new TH1F("eff_match_eta_di","eff_match_eta_di;dimu #eta",ETA,-2.4,2.4);
  TH1F *Eff_match_phi_di = new TH1F("eff_match_phi_di","eff_match_phi_di;dimu #phi",PHI,-PI,PI);
  TH1F *Eff_match_pt_di = new TH1F("eff_match_pt_di","eff_match_pt_di;dimu p_{T}",PT,0,20);
  TH1F *Eff_match_mass_di = new TH1F("eff_match_mass_di","eff_match_mass_di;dimu mass",40,0,20);

  // Fake -> is turned off now
/*  TH2F *Fake_etapt = new TH2F("Fake_etapt","Fake_etapt;single mu #eta;single mu p_{T}",ETA,-2.4,2.4,PT,0,20);
  TH2F *Fake_L2_fired_etapt = new TH2F("Fake_fired_etapt","Fake_fired_etapt;single mu #eta;single mu p_{T}",ETA,-2.4,2.4,PT,0,20);
  TH2F *Fake_L2_noMatch_etapt = new TH2F("Fake_L2_noMatch_etapt","Fake_L2_noMatch_etapt;single mu #eta;single mu p_{T}",ETA,-2.4,2.4,PT,0,20);

  TGraphAsymmErrors *Fake_eta = new TGraphAsymmErrors(); 
  TGraphAsymmErrors *Fake_phi = new TGraphAsymmErrors();
  TGraphAsymmErrors *Fake_pt = new TGraphAsymmErrors();
  TH1F *Fake_L2_fired_eta = new TH1F("fake_L2_fired_eta","fake_L2_fired_eta;single mu #eta",ETA,-2.4,2.4);
  TH1F *Fake_L2_fired_phi = new TH1F("fake_L2_fired_phi","fake_L2_fired_phi;single mu #phi",PHI,-PI,PI);
  TH1F *Fake_L2_fired_pt = new TH1F("fake_L2_fired_pt","fake_L2_fired_pt;single mu p_{T}",PT,0,20);
  TH1F *Fake_L2_noMatch_eta = new TH1F("fake_L2_noMatch_eta","fake_L2_noMatch_eta;single mu #eta",ETA,-2.4,2.4);
  TH1F *Fake_L2_noMatch_phi = new TH1F("fake_L2_noMatch_phi","fake_L2_noMatch_phi;single mu #phi",PHI,-PI,PI);
  TH1F *Fake_L2_noMatch_pt = new TH1F("fake_L2_noMatch_pt","fake_L2_noMatch_pt;single mu p_{T}",PT,0,20);

  TGraphAsymmErrors *Fake_eta_di = new TGraphAsymmErrors(); 
  TGraphAsymmErrors *Fake_phi_di = new TGraphAsymmErrors();
  TGraphAsymmErrors *Fake_pt_di = new TGraphAsymmErrors();
  TGraphAsymmErrors *Fake_mass_di = new TGraphAsymmErrors();
  TH1F *Fake_L2_fired_eta_di = new TH1F("fake_L2_fired_eta_di","fake_L2_fired_eta_di;dimu #eta",ETA,-2.4,2.4);
  TH1F *Fake_L2_fired_phi_di = new TH1F("fake_L2_fired_phi_di","fake_L2_fired_phi_di;dimu #phi",PHI,-PI,PI);
  TH1F *Fake_L2_fired_pt_di = new TH1F("fake_L2_fired_pt_di","fake_L2_fired_pt_di;dimu p_{T}",PT,0,20);
  TH1F *Fake_L2_fired_mass_di = new TH1F("fake_L2_fired_mass_di","fake_L2_fired_mass_di;dimu mass",40,0,20);
  TH1F *Fake_L2_noMatch_eta_di = new TH1F("fake_L2_noMatch_eta_di","fake_L2_noMatch_eta_di;dimu #eta",ETA,-2.4,2.4);
  TH1F *Fake_L2_noMatch_phi_di = new TH1F("fake_L2_noMatch_phi_di","fake_L2_noMatch_phi_di;dimu #phi",PHI,-PI,PI);
  TH1F *Fake_L2_noMatch_pt_di = new TH1F("fake_L2_noMatch_pt_di","fake_L2_noMatch_pt_di;dimu p_{T}",PT,0,20);
  TH1F *Fake_L2_noMatch_mass_di = new TH1F("fake_L2_noMatch_mass_di","fake_L2_noMatch_mass_di;dimu mass",40,0,20);*/

  ////////// Read input file
  string ftmp;
  ftmp = flag->fdir + "muTree_jpsi.root"; //file_name;
  FriendMuTree  *mutree = new FriendMuTree(ftmp.c_str(),true);
  TTree         *muon_tree;
  MUTREE        *muTree = new MUTREE;

  ftmp = flag->fdir + file_name;
  HltTree       *ohTree = new HltTree(ftmp.c_str(),true);
  TTree         *open_tree;

  if (!mutree->fChain->GetCurrentFile() || !ohTree->fChain->GetCurrentFile()) {
    cout << "Failed to open root files\n"; return -1;
  }

  open_tree = ohTree->fChain;
  open_tree->SetBranchAddress(flag->trigPath.c_str(),&flag->trig);

  muon_tree = mutree->fChain;
  muon_tree->SetBranchAddress("Run",&muTree->run);
  muon_tree->SetBranchAddress("Event",&muTree->event);
  if (flag->doGen && !flag->doSta && !flag->doGlb) {
   muon_tree->SetBranchAddress("Gen_eta",muTree->eta);
   muon_tree->SetBranchAddress("Gen_pt",muTree->pt);
   muon_tree->SetBranchAddress("Gen_phi",muTree->phi);
   muon_tree->SetBranchAddress("Gen_nptl",&muTree->nptl);
   muon_tree->SetBranchAddress("Gen_pid",muTree->charge);
   muon_tree->SetBranchAddress("Gen_mom",muTree->mom);
   muon_tree->SetBranchAddress("Gen_status",muTree->status);
  } else if (flag->doSta && !flag->doGen && !flag->doGlb) {
   muon_tree->SetBranchAddress("Sta_eta",muTree->eta);
   muon_tree->SetBranchAddress("Sta_pt",muTree->pt);
   muon_tree->SetBranchAddress("Sta_phi",muTree->phi);
   muon_tree->SetBranchAddress("Sta_nptl",&muTree->nptl);
   muon_tree->SetBranchAddress("Sta_charge",muTree->charge);
  } else if (flag->doGlb && !flag->doGen && !flag->doSta) {
   muon_tree->SetBranchAddress("Glb_eta",muTree->eta);
   muon_tree->SetBranchAddress("Glb_pt",muTree->pt);
   muon_tree->SetBranchAddress("Glb_phi",muTree->phi);
   muon_tree->SetBranchAddress("Glb_nptl",&muTree->nptl);
   muon_tree->SetBranchAddress("Glb_charge",muTree->charge);
   muon_tree->SetBranchAddress("Glb_nValMuHits",muTree->nValMuHits);
   muon_tree->SetBranchAddress("Glb_nValTrkHits",muTree->nValTrkHits);
   muon_tree->SetBranchAddress("Glb_nTrkFound",muTree->nTrkFound);
   muon_tree->SetBranchAddress("Glb_glbChi2_ndof",muTree->glbChi2_ndof);
   muon_tree->SetBranchAddress("Glb_trkChi2_ndof",muTree->trkChi2_ndof);
   muon_tree->SetBranchAddress("Glb_pixLayerWMeas",muTree->pixLayerWMeas);
   muon_tree->SetBranchAddress("Glb_trkDxy",muTree->trkDxy);
   muon_tree->SetBranchAddress("Glb_trkDz",muTree->trkDz);

  } else {
    cout << "Choose doSta or doGlb or doGen!\n";
    return -1;
  }

  INFO *info = new INFO;

  for (int i=0; i<muon_tree->GetEntries(); i++) {
    muon_tree->GetEntry(i);
    ohTree->GetEntry(i);
    open_tree->GetEntry(i);

    ////////// Compare event number
    bool noExist = false;
    for (int a=0; (muTree->run != ohTree->Run) || (muTree->event != ohTree->Event); a++ ) {
      if (a < muon_tree->GetEntries()) {
        muon_tree->GetEntry(a);
      } else {
        noExist = true;
        break;
      }
    }
    if (noExist) {
      cout << "muTree and ohTree->don't have same run/event number. Strange." << endl;
      cout << "muTree->Run: " << muTree->run << "\tohTree->Run: " << ohTree->Run << endl;
      cout << "muTree->Event: " << muTree->event << "\tohTree->Event: " << ohTree->Event << endl;
      continue;
    }

    ////////// Get information of muon objects in gen, L1, L2 levels
    info->tot_NohMuL2 += ohTree->NohMuL2;
    info->tot_NohMuL3 += ohTree->NohMuL3;

    if (flag->trig && flag->trigLevel == 1) info->tot_NL1ValidEvt++;
    else if (flag->trig && flag->trigLevel == 2) info->tot_NL2ValidEvt++;
    else if (flag->trig && flag->trigLevel == 3) info->tot_NL3ValidEvt++;

    ////////// Matching Gen, L2 muons and get eff, fake
    ////////// Check single muon acceptance
    MATCH *EffGenL2 = new MATCH;
    map<float,int,ptcomp> gen, cand;
    map<float,int>::iterator it;

    // Get reference muons (==Gen/Reco muons)
    for (int a=0; a < muTree->nptl; a++) {
      if (flag->doGen) {
        if (!flag->doSim && muTree->status[a] == -99) continue;    //skip sim muon
        if ( (!flag->jpsi && muTree->mom[a] != 553) || (flag->jpsi && muTree->mom[a] != 443) ) continue;
      } else if (flag->doGlb) {
        if(!isValidMu(muTree, a)) continue;    //Check glb muons are within acceptance range
      } else if (flag->doSta) {
        if(!isMuInAcc(muTree->eta[a], muTree->pt[a])) continue;    //Check sta muons are within acceptance range
      }
      if (fabs(muTree->eta[a]) <= 2.4) { 
        float pt = muTree->pt[a];
        gen[pt] = a;
      }

    }
    
    if (flag->doGlb && !gen.empty())
      info->tot_NGlbValidEvt++;

    // Get candidate muons (==HLT muons)
    if (flag->trigLevel == 2) {
      for (int a=0; a<ohTree->NohMuL2; a++) {
        float pt = ohTree->ohMuL2Pt[a];
        cand[pt] = a;
      }
    } else if (flag->trigLevel == 3) {
      for (int a=0; a<ohTree->NohMuL3; a++) {
        float pt = ohTree->ohMuL3Pt[a];
        cand[pt] = a;
      }
    }

    // Get 1st and 2nd highest pT muon
    it=gen.begin();
    for (unsigned int gen_=0;
        ( (flag->dimuTrig && (gen_<2)) || (!flag->dimuTrig && (gen_<1)) ) && (gen_<gen.size());
        gen_++) {
      int a = it->second;
      EffGenL2->ref_eta.push_back(muTree->eta[a]);
      EffGenL2->ref_pt.push_back(muTree->pt[a]);
      EffGenL2->ref_phi.push_back(muTree->phi[a]);
      EffGenL2->ref_chg.push_back(muTree->charge[a]);
      Eff_acc_eta->Fill(muTree->eta[a]);
      Eff_acc_phi->Fill(muTree->phi[a]);
      Eff_acc_pt->Fill(muTree->pt[a]);
      Eff_acc_etapt->Fill(muTree->eta[a],muTree->pt[a]);
      it++;
    }

    TLorentzVector L2mu1, L2mu2, L2dimu;
    if (flag->dimuTrig) {
      if (gen.size()>=2) {
        L2mu1.SetPtEtaPhiM(EffGenL2->ref_pt[0],EffGenL2->ref_eta[0],EffGenL2->ref_phi[0],Mmu);
        L2mu2.SetPtEtaPhiM(EffGenL2->ref_pt[1],EffGenL2->ref_eta[1],EffGenL2->ref_phi[1],Mmu);
        L2dimu = L2mu1 + L2mu2; // Use only 0th, 1th L1 objects
        if ((flag->jpsi && (L2dimu.M() > 2 && L2dimu.M() < 5)) ||
           (!flag->jpsi && (L2dimu.M() > 8 && L2dimu.M() < 11))) {
          Eff_acc_mass_di->Fill(L2dimu.M());
          Eff_acc_phi_di->Fill(L2dimu.Phi());
          Eff_acc_eta_di->Fill(L2dimu.Eta());
          Eff_acc_pt_di->Fill(L2dimu.Pt());
          Eff_acc_etapt_di->Fill(L2dimu.Eta(),L2dimu.Pt());
        }
      }
    }

    
    ////////// Check L2 object and gen mu are matched
    it = cand.begin();
    for (unsigned int a=0; a<EffGenL2->ref_eta.size(); a++) {
      if (flag->trigLevel == 1) {
        EffGenL2->deltaR.push_back(0.001);    //Because there are no L1 muons, not apply dCut for L1 object matching
      } else if (flag->trigLevel == 2) {
        for (int b=0; b<ohTree->NohMuL2; b++) {
          matching(flag->match_dR,EffGenL2,a,ohTree->ohMuL2Eta[b],ohTree->ohMuL2Phi[b],ohTree->ohMuL2Pt[b],ohTree->ohMuL2Chg[b]);
        }
      } else if (flag->trigLevel == 3) {
        for (int b=0; b<ohTree->NohMuL3; b++) {
          matching(flag->match_dR,EffGenL2,a,ohTree->ohMuL3Eta[b],ohTree->ohMuL3Phi[b],ohTree->ohMuL3Pt[b],ohTree->ohMuL3Chg[b]);
        }
      }
    }

    // End of matching


    ////////// Fill efficiency numerator
    TLorentzVector L2mu[2];
    L2mu[0].SetPtEtaPhiM(0,0,0,0);
    L2mu[1].SetPtEtaPhiM(0,0,0,0);
    // For single muons
    for (unsigned int a=0; a<EffGenL2->ref_eta.size(); a++) {
      if ( ((flag->match_dR && !EffGenL2->deltaR.empty() && (EffGenL2->deltaR[a] < flag->dCut)) ||
           (!flag->match_dR && !EffGenL2->deltaEta.empty() && (EffGenL2->deltaEta[a] < flag->dCut))) && 
           flag->trig
         ){
          Eff_match_eta->Fill(EffGenL2->ref_eta[a]);
          Eff_match_phi->Fill(EffGenL2->ref_phi[a]);
          Eff_match_pt->Fill(EffGenL2->ref_pt[a]);
          Eff_match_etapt->Fill(EffGenL2->ref_eta[a],EffGenL2->ref_pt[a]);
          }
        if (flag->dimuTrig) {
          L2mu[a].SetPtEtaPhiM(EffGenL2->ref_pt[a],EffGenL2->ref_eta[a],EffGenL2->ref_phi[a],Mmu);
        }
    }

    // For di-muons
    if (flag->dimuTrig && (L2mu[0].Pt()!=0 && L2mu[1].Pt()!=0) ){
      L2dimu = L2mu[0] + L2mu[1]; // Use only 0th, 1th L1 objects
      if ((flag->jpsi && (L2dimu.M() > 2 && L2dimu.M() < 5)) ||
         (!flag->jpsi && (L2dimu.M() > 8 && L2dimu.M() < 11))) {
          Eff_match_mass_di->Fill(L2dimu.M());
          Eff_match_phi_di->Fill(L2dimu.Phi());
          Eff_match_eta_di->Fill(L2dimu.Eta());
          Eff_match_pt_di->Fill(L2dimu.Pt());
          Eff_match_etapt_di->Fill(L2dimu.Eta(),L2dimu.Pt());
      }
    }


    ////////// Check L2 trigger fired
/*    MATCH *FakeGenL2 = new MATCH;
    ////////// Fill fake numerator and denomiator
    if (flag->trig) {
      // Get 1st and 2nd highest pT muon
      map<float,int,ptcomp> l2;
      if (flag->trigLevel == 2) {
        for (int a=0; a<ohTree->NohMuL2; a++) {
          float pt = ohTree->ohMuL2Pt[a];
          l2[pt] = a;
        }
      } else if (flag->trigLevel == 3) {
        for (int a=0; a<ohTree->NohMuL3; a++) {
          float pt = ohTree->ohMuL3Pt[a];
          l2[pt] = a;
        }
      }
      it=l2.begin();
      for (unsigned int l2_=0;
          ( (flag->dimuTrig && (l2_<2)) || (!flag->dimuTrig && (l2_<1)) ) && (l2_<l2.size());
          l2_++) {
        int a = it->second;
        if (flag->trigLevel == 2) {
          FakeGenL2->ref_eta.push_back(ohTree->ohMuL2Eta[a]);
          FakeGenL2->ref_pt.push_back(ohTree->ohMuL2Pt[a]);
          FakeGenL2->ref_phi.push_back(ohTree->ohMuL2Phi[a]);
          FakeGenL2->ref_chg.push_back(ohTree->ohMuL2Chg[a]);
          Fake_L2_fired_eta->Fill(ohTree->ohMuL2Eta[a]);
          Fake_L2_fired_phi->Fill(ohTree->ohMuL2Phi[a]);
          Fake_L2_fired_pt->Fill(ohTree->ohMuL2Pt[a]);
          Fake_L2_fired_etapt->Fill(ohTree->ohMuL2Eta[a],ohTree->ohMuL2Pt[a]);
        } else if (flag->trigLevel == 3) {
          FakeGenL2->ref_eta.push_back(ohTree->ohMuL3Eta[a]);
          FakeGenL2->ref_pt.push_back(ohTree->ohMuL3Pt[a]);
          FakeGenL2->ref_phi.push_back(ohTree->ohMuL3Phi[a]);
          FakeGenL2->ref_chg.push_back(ohTree->ohMuL3Chg[a]);
          Fake_L2_fired_eta->Fill(ohTree->ohMuL3Eta[a]);
          Fake_L2_fired_phi->Fill(ohTree->ohMuL3Phi[a]);
          Fake_L2_fired_pt->Fill(ohTree->ohMuL3Pt[a]);
          Fake_L2_fired_etapt->Fill(ohTree->ohMuL3Eta[a],ohTree->ohMuL3Pt[a]);
        }
        it++;
      }

      if (flag->dimuTrig) {
        if (l2.size()>=2) {
          L2mu1.SetPtEtaPhiM(FakeGenL2->ref_pt[0],FakeGenL2->ref_eta[0],FakeGenL2->ref_phi[0],Mmu);
          L2mu2.SetPtEtaPhiM(FakeGenL2->ref_pt[1],FakeGenL2->ref_eta[1],FakeGenL2->ref_phi[1],Mmu);

          L2dimu = L2mu1 + L2mu2; // Use only 0th, 1th L1 objects
          Fake_L2_fired_mass_di->Fill(L2dimu.M());
          Fake_L2_fired_phi_di->Fill(L2dimu.Phi());
          Fake_L2_fired_eta_di->Fill(L2dimu.Eta());
          Fake_L2_fired_pt_di->Fill(L2dimu.Pt());
        }
      }


      // Get deltaR, deltaEta
      for (unsigned int a=0; a<FakeGenL2->ref_eta.size(); a++) {
        for (int b=0; b<muTree->nptl; b++) {
          if (flag->doGen) {
            if (!flag->doSim && muTree->status[b] == -99) continue;    //skip sim muon
            if ( (!flag->jpsi && muTree->mom[b] != 553) || (flag->jpsi && muTree->mom[b] != 443) ) continue;
          }
          matching(flag->match_dR,FakeGenL2,a,muTree->eta[b],muTree->phi[b],muTree->pt[b],muTree->charge[b]);
        }
      } // End of matching


      ////////// Fill fake numerator
      TLorentzVector L2match;
      L2mu[0].SetPtEtaPhiM(0,0,0,0);
      L2mu[1].SetPtEtaPhiM(0,0,0,0);
      int nUnmatch =0;
      for (unsigned int a=0; a<FakeGenL2->ref_eta.size() && l2.size() >= 2; a++) {
        if ( (flag->match_dR && !FakeGenL2->deltaR.empty() && FakeGenL2->deltaR[a] > flag->dCut ) ||
             (!flag->match_dR && !FakeGenL2->deltaEta.empty() && FakeGenL2->deltaEta[a] > flag->dCut) ) {
          Fake_L2_noMatch_eta->Fill(FakeGenL2->ref_eta[a]);
          Fake_L2_noMatch_phi->Fill(FakeGenL2->ref_phi[a]);
          Fake_L2_noMatch_pt->Fill(FakeGenL2->ref_pt[a]);
          Fake_L2_noMatch_etapt->Fill(FakeGenL2->ref_eta[a],FakeGenL2->ref_pt[a]);
          if (flag->dimuTrig) {
            L2mu[nUnmatch].SetPtEtaPhiM(FakeGenL2->ref_pt[a],FakeGenL2->ref_eta[a],FakeGenL2->ref_phi[a],Mmu);
            nUnmatch++;
          }
        } else {
          L2match.SetPtEtaPhiM(FakeGenL2->ref_pt[a],FakeGenL2->ref_eta[a],FakeGenL2->ref_phi[a],Mmu);
        }
      }

      if (flag->dimuTrig && nUnmatch > 0) {
        if (nUnmatch == 1) L2dimu = L2mu[0] + L2match;
        else L2dimu = L2mu[0] + L2mu[1]; // Use only 0th, 1th L1 objects
        Fake_L2_noMatch_mass_di->Fill(L2dimu.M());
        Fake_L2_noMatch_phi_di->Fill(L2dimu.Phi());
        Fake_L2_noMatch_eta_di->Fill(L2dimu.Eta());
        Fake_L2_noMatch_pt_di->Fill(L2dimu.Pt());
      }
    } // End of flag->dimuTrig conditions*/


    if (i%1000 == 0)
      cout << "End of processing entry: " << i << endl;
  } // End of processing 1 entry in trees
  // End of reading entire entries in trees


  ////////// Efficiency
  Eff_eta->SetMarkerStyle(kFullCircle); Eff_eta->SetMarkerSize(1.2);
  Eff_phi->SetMarkerStyle(kFullCircle); Eff_phi->SetMarkerSize(1.2);
  Eff_pt->SetMarkerStyle(kFullCircle);  Eff_pt->SetMarkerSize(1.2);

  Eff_eta->Divide(Eff_match_eta,Eff_acc_eta,"cl=0.683 b(1,1) mode");
  Eff_phi->Divide(Eff_match_phi,Eff_acc_phi,"cl=0.683 b(1,1) mode");
  Eff_pt->Divide(Eff_match_pt,Eff_acc_pt,"cl=0.683 b(1,1) mode");
  Eff_etapt->Divide(Eff_match_etapt,Eff_acc_etapt);

  if (flag->doGen) {
    string title = "Efficiency with gen muon, " + flag->trigPath;
    Eff_eta->SetTitle(title.c_str());
    Eff_phi->SetTitle(title.c_str());
    Eff_pt->SetTitle(title.c_str());
    Eff_etapt->SetTitle(title.c_str());
  } else {
    string title = "Efficiency with reco muon, " + flag->trigPath;
    Eff_eta->SetTitle(title.c_str());
    Eff_phi->SetTitle(title.c_str());
    Eff_pt->SetTitle(title.c_str());
    Eff_etapt->SetTitle(title.c_str());
  }
  string title;
  title = "Eff_eta_" + flag->trigPath;
  Eff_eta->SetName(title.c_str());
  title = "Eff_phi_" + flag->trigPath;
  Eff_phi->SetName(title.c_str());
  title = "Eff_pt_" + flag->trigPath;
  Eff_pt->SetName(title.c_str());
  title = "Eff_etapt_" + flag->trigPath;
  Eff_etapt->SetName(title.c_str());

  Eff_eta->GetXaxis()->SetTitle("single mu #eta");
  Eff_phi->GetXaxis()->SetTitle("single mu #phi");
  Eff_pt->GetXaxis()->SetTitle("single mu p_{T}");
  Eff_etapt->GetXaxis()->SetTitle("single mu #eta");
  Eff_etapt->GetYaxis()->SetTitle("single mu p_{T}");

  Eff_eta->SetMaximum(1.2);
  Eff_phi->SetMaximum(1.2);
  Eff_pt->SetMaximum(1.2);

  output->cd();
  Eff_eta->Write();
  Eff_phi->Write();
  Eff_pt->Write();
  Eff_etapt->Write();

  Eff_eta_di->SetMarkerStyle(kFullCircle); Eff_eta_di->SetMarkerSize(1.2);
  Eff_mass_di->SetMarkerStyle(kFullCircle); Eff_mass_di->SetMarkerSize(1.2);
  Eff_pt_di->SetMarkerStyle(kFullCircle);  Eff_pt_di->SetMarkerSize(1.2);

  Eff_eta_di->Divide(Eff_match_eta_di,Eff_acc_eta_di,"cl=0.683 b(1,1) mode");
  Eff_mass_di->Divide(Eff_match_mass_di,Eff_acc_mass_di,"cl=0.683 b(1,1) mode");
  Eff_pt_di->Divide(Eff_match_pt_di,Eff_acc_pt_di,"cl=0.683 b(1,1) mode");
  Eff_etapt_di->Divide(Eff_match_etapt_di,Eff_acc_etapt_di);


  if (flag->doGen) {
    title = "Efficiency with gen muon, " + flag->trigPath;
    Eff_eta_di->SetTitle(title.c_str());
    Eff_mass_di->SetTitle(title.c_str());
    Eff_pt_di->SetTitle(title.c_str());
    Eff_etapt_di->SetTitle(title.c_str());
  } else {
    title = "Efficiency with reco muon, " + flag->trigPath;
    Eff_eta_di->SetTitle(title.c_str());
    Eff_mass_di->SetTitle(title.c_str());
    Eff_pt_di->SetTitle(title.c_str());
    Eff_etapt_di->SetTitle(title.c_str());
  }
  title = "Eff_eta_di_" + flag->trigPath;
  Eff_eta_di->SetName(title.c_str());
  title = "Eff_mass_di_" + flag->trigPath;
  Eff_mass_di->SetName(title.c_str());
  title = "Eff_pt_di_" + flag->trigPath;
  Eff_pt_di->SetName(title.c_str());
  title = "Eff_etapt_di_" + flag->trigPath;
  Eff_etapt_di->SetName(title.c_str());

  Eff_eta_di->GetXaxis()->SetTitle("dimu #eta");
  Eff_mass_di->GetXaxis()->SetTitle("dimu mass");
  Eff_pt_di->GetXaxis()->SetTitle("dimu p_{T}");
  Eff_etapt_di->GetXaxis()->SetTitle("dimu #eta");
  Eff_etapt_di->GetYaxis()->SetTitle("dimu p_{T}");

  Eff_eta_di->SetMaximum(1.2);
  Eff_mass_di->SetMaximum(1.2);
  Eff_pt_di->SetMaximum(1.2);

  output->cd();
  Eff_eta_di->Write();
  Eff_mass_di->Write();
  Eff_pt_di->Write();
  Eff_etapt_di->Write();


  ////////// Fake 
/*  Fake_eta->SetMarkerStyle(kFullCircle);  Fake_eta->SetMarkerSize(1.2);
  Fake_phi->SetMarkerStyle(kFullCircle);  Fake_phi->SetMarkerSize(1.2);
  Fake_pt->SetMarkerStyle(kFullCircle);   Fake_pt->SetMarkerSize(1.2);

  Fake_eta->Divide(Fake_L2_noMatch_eta,Fake_L2_fired_eta,"cl=0.683 b(1,1) mode");
  Fake_phi->Divide(Fake_L2_noMatch_phi,Fake_L2_fired_phi,"cl=0.683 b(1,1) mode");
  Fake_pt->Divide(Fake_L2_noMatch_pt,Fake_L2_fired_pt,"cl=0.683 b(1,1) mode");

  if (flag->doGen) {
    Fake_eta->SetTitle("Fake with L2 muon info (gen matching)");
    Fake_phi->SetTitle("Fake with L2 muon info (gen matching)");
    Fake_pt->SetTitle("Fake with L2 muon info (gen matching)");
  } else {
    Fake_eta->SetTitle("Fake with L2 muon info (reco matching)");
    Fake_phi->SetTitle("Fake with L2 muon info (reco matching)");
    Fake_pt->SetTitle("Fake with L2 muon info (reco matching)");
  }

  Fake_eta->GetXaxis()->SetTitle("single mu #eta");
  Fake_phi->GetXaxis()->SetTitle("single mu #phi");
  Fake_pt->GetXaxis()->SetTitle("single mu p_{T}");

  Fake_eta->SetMaximum(1.2);
  Fake_phi->SetMaximum(1.2);
  Fake_pt->SetMaximum(1.2);


  Fake_eta_di->SetMarkerStyle(kFullCircle);  Fake_eta_di->SetMarkerSize(1.2);
  Fake_mass_di->SetMarkerStyle(kFullCircle);  Fake_mass_di->SetMarkerSize(1.2);
  Fake_pt_di->SetMarkerStyle(kFullCircle);   Fake_pt_di->SetMarkerSize(1.2);

  Fake_eta_di->Divide(Fake_L2_noMatch_eta_di,Fake_L2_fired_eta_di,"cl=0.683 b(1,1) mode");
  Fake_mass_di->Divide(Fake_L2_noMatch_mass_di,Fake_L2_fired_mass_di,"cl=0.683 b(1,1) mode");
  Fake_pt_di->Divide(Fake_L2_noMatch_pt_di,Fake_L2_fired_pt_di,"cl=0.683 b(1,1) mode");

  if (flag->doGen) {
    Fake_eta_di->SetTitle("Fake with L2 muon info (gen matching)");
    Fake_mass_di->SetTitle("Fake with L2 muon info (gen matching)");
    Fake_pt_di->SetTitle("Fake with L2 muon info (gen matching)");
  } else {
    Fake_eta_di->SetTitle("Fake with L2 muon info (reco matching)");
    Fake_mass_di->SetTitle("Fake with L2 muon info (reco matching)");
    Fake_pt_di->SetTitle("Fake with L2 muon info (reco matching)");
  }

  Fake_eta_di->GetXaxis()->SetTitle("dimu #eta");
  Fake_mass_di->GetXaxis()->SetTitle("dimu mass");
  Fake_pt_di->GetXaxis()->SetTitle("dimu p_{T}");

  Fake_eta_di->SetMaximum(1.2);
  Fake_mass_di->SetMaximum(1.2);
  Fake_pt_di->SetMaximum(1.2);

  Fake_etapt->Divide(Fake_L2_noMatch_etapt,Fake_L2_fired_etapt);*/

  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  TLatex *t = new TLatex(); t->SetNDC(kTRUE);
  TPaletteAxis *paxis;
  stringstream stmp;


  TCanvas *ceff = new TCanvas("eff","eff",1300,1000);
  ceff->Divide(2,2);
  ceff->cd(1);    Eff_eta->Draw("ap");
  ceff->cd(2);    Eff_phi->Draw("ap");
  ceff->cd(3);    Eff_pt->Draw("ap");
  ceff->cd(4);
  stmp.str("");  stmp << "Events: " << muon_tree->GetEntries();
  t->DrawLatex(0.0,0.9,stmp.str().c_str());
  if (flag->trigLevel == 1) {
    stmp.str("");  stmp << "L1 fired events: " << info->tot_NL1ValidEvt;
    t->DrawLatex(0.0,0.8,stmp.str().c_str());
  } else if (flag->trigLevel == 2) {
    stmp.str("");  stmp << "L2 fired events: " << info->tot_NL2ValidEvt;
    t->DrawLatex(0.0,0.8,stmp.str().c_str());
  } else if (flag->trigLevel == 3) {
    stmp.str("");  stmp << "L3 fired events: " << info->tot_NL3ValidEvt;
    t->DrawLatex(0.0,0.8,stmp.str().c_str());
  }
  stmp.str("");  stmp << "Total # of accepted #mu: " << Eff_acc_eta->GetEntries();
  t->DrawLatex(0.0,0.7,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of matched #mu: " << Eff_match_eta->GetEntries();
  t->DrawLatex(0.0,0.6,stmp.str().c_str());
  stmp.str("");  stmp << "Eff: " << Eff_match_eta->GetEntries()/Eff_acc_eta->GetEntries();
  t->DrawLatex(0.0,0.5,stmp.str().c_str());
  stmp.str("");  stmp << "Input file : " << file_name;
  t->DrawLatex(0.0,0.4,stmp.str().c_str());
  stmp.str("");  stmp << "Trigger path: " << flag->trigPath;
  t->DrawLatex(0.0,0.3,stmp.str().c_str());
  ceff->SaveAs("eff.png");
  ceff->Clear();  ceff->Divide(2,2);
  ceff->cd(1);    Eff_acc_eta->Draw();
  ceff->cd(2);    Eff_acc_phi->Draw();
  ceff->cd(3);    Eff_acc_pt->Draw();
  ceff->SaveAs("eff_acc.png");
  ceff->Clear();  ceff->Divide(2,2);
  ceff->cd(1);    Eff_match_eta->Draw();
  ceff->cd(2);    Eff_match_phi->Draw();
  ceff->cd(3);    Eff_match_pt->Draw();
  ceff->SaveAs("eff_match.png");
  delete ceff;
  ceff = new TCanvas("eff","eff",1300,1000);
  ceff->Divide(2,2);
  ceff->cd(1);    Eff_eta_di->Draw("ap");
  ceff->cd(2);    Eff_mass_di->Draw("ap");
  ceff->cd(3);    Eff_pt_di->Draw("ap");
  ceff->cd(4);
  stmp.str("");  stmp << "Events: " << muon_tree->GetEntries();
  t->DrawLatex(0.0,0.9,stmp.str().c_str());
  if (flag->trigLevel == 1) {
    stmp.str("");  stmp << "L1 fired events: " << info->tot_NL1ValidEvt;
    t->DrawLatex(0.0,0.8,stmp.str().c_str());
  } else if (flag->trigLevel == 2) {
    stmp.str("");  stmp << "L2 fired events: " << info->tot_NL2ValidEvt;
    t->DrawLatex(0.0,0.8,stmp.str().c_str());
  } else if (flag->trigLevel == 3) {
    stmp.str("");  stmp << "L3 fired events: " << info->tot_NL3ValidEvt;
    t->DrawLatex(0.0,0.8,stmp.str().c_str());
  }
  stmp.str("");  stmp << "Total # of accepted di #mu: " << Eff_acc_eta_di->GetEntries();
  t->DrawLatex(0.0,0.7,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of matched di #mu: " << Eff_match_eta_di->GetEntries();
  t->DrawLatex(0.0,0.6,stmp.str().c_str());
  stmp.str("");  stmp << "Eff: " << Eff_match_eta_di->GetEntries()/Eff_acc_eta_di->GetEntries();
  t->DrawLatex(0.0,0.5,stmp.str().c_str());
  stmp.str("");  stmp << "Input file : " << file_name;
  t->DrawLatex(0.0,0.4,stmp.str().c_str());
  stmp.str("");  stmp << "Trigger path: " << flag->trigPath;
  t->DrawLatex(0.0,0.3,stmp.str().c_str());
  ceff->SaveAs("eff_dimu.png");
  ceff->Clear();  ceff->Divide(2,2);
  ceff->cd(1);    Eff_acc_eta_di->Draw();
  ceff->cd(2);    Eff_acc_mass_di->Draw();
  ceff->cd(3);    Eff_acc_pt_di->Draw();
  ceff->SaveAs("eff_acc_dimu.png");
  ceff->Clear();  ceff->Divide(2,2);
  ceff->cd(1);    Eff_match_eta_di->Draw();
  ceff->cd(2);    Eff_match_mass_di->Draw();
  ceff->cd(3);    Eff_match_pt_di->Draw();
  ceff->SaveAs("eff_match_dimu.png");
  delete ceff;
  ceff = new TCanvas("eff","eff",1300,1000);
  ceff->Divide(2,2);
  ceff->cd(1);    Eff_etapt->Draw("colz");
  gPad->Update();
  paxis = (TPaletteAxis*)Eff_etapt->GetListOfFunctions()->FindObject("palette");
  if (paxis != NULL) {paxis->SetY2NDC(0.7); paxis->SetLabelSize(0.03);}
  ceff->cd(2);    Eff_acc_etapt->Draw("colz");
  gPad->Update();
  paxis = (TPaletteAxis*)Eff_acc_etapt->GetListOfFunctions()->FindObject("palette");
  if (paxis != NULL) {paxis->SetY2NDC(0.7); paxis->SetLabelSize(0.03);}
  ceff->cd(3);    Eff_match_etapt->Draw("colz");
  gPad->Update();
  paxis = (TPaletteAxis*)Eff_match_etapt->GetListOfFunctions()->FindObject("palette");
  if (paxis != NULL) {paxis->SetY2NDC(0.7); paxis->SetLabelSize(0.03);}
  ceff->cd(4);
  stmp.str("");  stmp << "Events: " << muon_tree->GetEntries();
  t->DrawLatex(0.0,0.9,stmp.str().c_str());
  if (flag->trigLevel == 1) {
    stmp.str("");  stmp << "L1 fired events: " << info->tot_NL1ValidEvt;
    t->DrawLatex(0.0,0.8,stmp.str().c_str());
  } else if (flag->trigLevel == 2) {
    stmp.str("");  stmp << "L2 fired events: " << info->tot_NL2ValidEvt;
    t->DrawLatex(0.0,0.8,stmp.str().c_str());
  } else if (flag->trigLevel == 3) {
    stmp.str("");  stmp << "L3 fired events: " << info->tot_NL3ValidEvt;
    t->DrawLatex(0.0,0.8,stmp.str().c_str());
  }
  stmp.str("");  stmp << "Total # of accepted #mu: " << Eff_acc_etapt->GetEntries();
  t->DrawLatex(0.0,0.7,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of matched #mu: " << Eff_match_etapt->GetEntries();
  t->DrawLatex(0.0,0.6,stmp.str().c_str());
  stmp.str("");  stmp << "Eff: " << Eff_match_etapt->GetEntries()/Eff_acc_etapt->GetEntries();
  t->DrawLatex(0.0,0.5,stmp.str().c_str());
  stmp.str("");  stmp << "Input file : " << file_name;
  t->DrawLatex(0.0,0.4,stmp.str().c_str());
  stmp.str("");  stmp << "Trigger path: " << flag->trigPath;
  t->DrawLatex(0.0,0.3,stmp.str().c_str());
  ceff->SaveAs("eff_2D.png");
  delete ceff;
  ceff = new TCanvas("eff","eff",1300,1000);
  ceff->Divide(2,2);
  ceff->cd(1);    Eff_etapt_di->Draw("colz");
  gPad->Update();
  paxis = (TPaletteAxis*)Eff_etapt_di->GetListOfFunctions()->FindObject("palette");
  if (paxis != NULL) {paxis->SetY2NDC(0.7); paxis->SetLabelSize(0.03);}
  ceff->cd(2);    Eff_acc_etapt_di->Draw("colz");
  gPad->Update();
  paxis = (TPaletteAxis*)Eff_acc_etapt_di->GetListOfFunctions()->FindObject("palette");
  if (paxis != NULL) {paxis->SetY2NDC(0.7); paxis->SetLabelSize(0.03);}
  ceff->cd(3);    Eff_match_etapt_di->Draw("colz");
  gPad->Update();
  paxis = (TPaletteAxis*)Eff_match_etapt_di->GetListOfFunctions()->FindObject("palette");
  if (paxis != NULL) {paxis->SetY2NDC(0.7); paxis->SetLabelSize(0.03);}
  ceff->cd(4);
  stmp.str("");  stmp << "Events: " << muon_tree->GetEntries();
  t->DrawLatex(0.0,0.9,stmp.str().c_str());
  if (flag->trigLevel == 1) {
    stmp.str("");  stmp << "L1 fired events: " << info->tot_NL1ValidEvt;
    t->DrawLatex(0.0,0.8,stmp.str().c_str());
  } else if (flag->trigLevel == 2) {
    stmp.str("");  stmp << "L2 fired events: " << info->tot_NL2ValidEvt;
    t->DrawLatex(0.0,0.8,stmp.str().c_str());
  } else if (flag->trigLevel == 3) {
    stmp.str("");  stmp << "L3 fired events: " << info->tot_NL3ValidEvt;
    t->DrawLatex(0.0,0.8,stmp.str().c_str());
  }
  stmp.str("");  stmp << "Total # of accepted di#mu: " << Eff_acc_etapt_di->GetEntries();
  t->DrawLatex(0.0,0.7,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of matched di#mu: " << Eff_match_etapt_di->GetEntries();
  t->DrawLatex(0.0,0.6,stmp.str().c_str());
  stmp.str("");  stmp << "Eff: " << Eff_match_etapt_di->GetEntries()/Eff_acc_etapt_di->GetEntries();
  t->DrawLatex(0.0,0.5,stmp.str().c_str());
  stmp.str("");  stmp << "Input file : " << file_name;
  t->DrawLatex(0.0,0.4,stmp.str().c_str());
  stmp.str("");  stmp << "Trigger path: " << flag->trigPath;
  t->DrawLatex(0.0,0.3,stmp.str().c_str());
  ceff->SaveAs("eff_di_2D.png");
  delete ceff;


  // Not execute Fake
/*  TCanvas *cfake = new TCanvas("fake","fake",1300,1000);
  cfake->Divide(2,2);
  cfake->cd(1);    Fake_eta->Draw("ap");
  cfake->cd(2);    Fake_phi->Draw("ap");
  cfake->cd(3);    Fake_pt->Draw("ap");
  cfake->cd(4);
  stmp.str("");  stmp << "Events: " << muon_tree->GetEntries();
  t->DrawLatex(0.0,0.9,stmp.str().c_str());
  if (flag->trigLevel == 1) {
    stmp.str("");  stmp << "L1 fired events: " << info->tot_NL1ValidEvt;
    t->DrawLatex(0.0,0.8,stmp.str().c_str());
  } else if (flag->trigLevel == 2) {
    stmp.str("");  stmp << "L2 fired events: " << info->tot_NL2ValidEvt;
    t->DrawLatex(0.0,0.8,stmp.str().c_str());
  } else if (flag->trigLevel == 3) {
    stmp.str("");  stmp << "L3 fired events: " << info->tot_NL3ValidEvt;
    t->DrawLatex(0.0,0.8,stmp.str().c_str());
  }
  stmp.str("");  stmp << "Total # of fired L2(or L3) #mu: " << Fake_L2_fired_eta->GetEntries();
  t->DrawLatex(0.0,0.7,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of NOT matched L2(or L3) #mu: " << Fake_L2_noMatch_eta->GetEntries();
  t->DrawLatex(0.0,0.6,stmp.str().c_str());
  stmp.str("");  stmp << "Fake: " << Fake_L2_noMatch_eta->GetEntries()/Fake_L2_fired_eta->GetEntries();
  t->DrawLatex(0.0,0.5,stmp.str().c_str());
  stmp.str("");  stmp << "Input file : " << file_name;
  t->DrawLatex(0.0,0.4,stmp.str().c_str());
  stmp.str("");  stmp << "Trigger path: " << flag->trigPath;
  t->DrawLatex(0.0,0.3,stmp.str().c_str());
  cfake->SaveAs("fake.png");
  cfake->Clear();  cfake->Divide(2,2);
  cfake->cd(1);    Fake_L2_fired_eta->Draw();
  cfake->cd(2);    Fake_L2_fired_phi->Draw();
  cfake->cd(3);    Fake_L2_fired_pt->Draw();
  cfake->SaveAs("fake_fired.png");
  cfake->Clear();  cfake->Divide(2,2);
  cfake->cd(1);    Fake_L2_noMatch_eta->Draw();
  cfake->cd(2);    Fake_L2_noMatch_phi->Draw();
  cfake->cd(3);    Fake_L2_noMatch_pt->Draw();
  cfake->SaveAs("fake_noMatch.png");
  delete cfake;
  cfake = new TCanvas("fake","fake",1300,1000);
  cfake->Divide(2,2);
  cfake->cd(1);    Fake_eta_di->Draw("ap");
  cfake->cd(2);    Fake_mass_di->Draw("ap");
  cfake->cd(3);    Fake_pt_di->Draw("ap");
  cfake->cd(4);
  stmp.str("");  stmp << "Events: " << muon_tree->GetEntries();
  t->DrawLatex(0.0,0.9,stmp.str().c_str());
  if (flag->trigLevel == 1) {
    stmp.str("");  stmp << "L1 fired events: " << info->tot_NL1ValidEvt;
    t->DrawLatex(0.0,0.8,stmp.str().c_str());
  } else if (flag->trigLevel == 2) {
    stmp.str("");  stmp << "L2 fired events: " << info->tot_NL2ValidEvt;
    t->DrawLatex(0.0,0.8,stmp.str().c_str());
  } else if (flag->trigLevel == 3) {
    stmp.str("");  stmp << "L3 fired events: " << info->tot_NL3ValidEvt;
    t->DrawLatex(0.0,0.8,stmp.str().c_str());
  }
  stmp.str("");  stmp << "Total # of fired L2(or L3) di #mu: " << Fake_L2_fired_eta_di->GetEntries();
  t->DrawLatex(0.0,0.7,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of NOT matched L2(or L3) di #mu: " << Fake_L2_noMatch_eta_di->GetEntries();
  t->DrawLatex(0.0,0.6,stmp.str().c_str());
  stmp.str("");  stmp << "Fake: " << Fake_L2_noMatch_eta_di->GetEntries()/Fake_L2_fired_eta_di->GetEntries();
  t->DrawLatex(0.0,0.5,stmp.str().c_str());
  stmp.str("");  stmp << "Input file : " << file_name;
  t->DrawLatex(0.0,0.4,stmp.str().c_str());
  stmp.str("");  stmp << "Trigger path: " << flag->trigPath;
  t->DrawLatex(0.0,0.3,stmp.str().c_str());
  cfake->SaveAs("fake_dimu.png");
  cfake->Clear();  cfake->Divide(2,2);
  cfake->cd(1);    Fake_L2_fired_eta_di->Draw();
  cfake->cd(2);    Fake_L2_fired_mass_di->Draw();
  cfake->cd(3);    Fake_L2_fired_pt_di->Draw();
  cfake->SaveAs("fake_fired_dimu.png");
  cfake->Clear();  cfake->Divide(2,2);
  cfake->cd(1);    Fake_L2_noMatch_eta_di->Draw();
  cfake->cd(2);    Fake_L2_noMatch_mass_di->Draw();
  cfake->cd(3);    Fake_L2_noMatch_pt_di->Draw();
  cfake->SaveAs("fake_noMatch_dimu.png");
  delete cfake;
  cfake = new TCanvas("fake","fake",1300,1000);
  cfake->Divide(2,2);
  cfake->cd(1);    Fake_etapt->Draw("colz");
  gPad->Update();
  paxis = (TPaletteAxis*)Fake_etapt->GetListOfFunctions()->FindObject("palette");
  if (paxis != NULL) {paxis->SetY2NDC(0.7); paxis->SetLabelSize(0.03);}
  cfake->cd(2);    Fake_L2_fired_etapt->Draw("colz");
  gPad->Update();
  paxis = (TPaletteAxis*)Fake_L2_fired_etapt->GetListOfFunctions()->FindObject("palette");
  if (paxis != NULL) {paxis->SetY2NDC(0.7); paxis->SetLabelSize(0.03);}
  cfake->cd(3);    Fake_L2_noMatch_etapt->Draw("colz");
  gPad->Update();
  paxis = (TPaletteAxis*)Fake_L2_noMatch_etapt->GetListOfFunctions()->FindObject("palette");
  if (paxis != NULL) {paxis->SetY2NDC(0.7); paxis->SetLabelSize(0.03);}
  cfake->cd(4);
  stmp.str("");  stmp << "Events: " << muon_tree->GetEntries();
  t->DrawLatex(0.0,0.9,stmp.str().c_str());
  if (flag->trigLevel == 1) {
    stmp.str("");  stmp << "L1 fired events: " << info->tot_NL1ValidEvt;
    t->DrawLatex(0.0,0.8,stmp.str().c_str());
  } else if (flag->trigLevel == 2) {
    stmp.str("");  stmp << "L2 fired events: " << info->tot_NL2ValidEvt;
    t->DrawLatex(0.0,0.8,stmp.str().c_str());
  } else if (flag->trigLevel == 3) {
    stmp.str("");  stmp << "L3 fired events: " << info->tot_NL3ValidEvt;
    t->DrawLatex(0.0,0.8,stmp.str().c_str());
  }
  stmp.str("");  stmp << "Total # of fired L2(or L3) #mu: " << Fake_L2_fired_etapt->GetEntries();
  t->DrawLatex(0.0,0.7,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of NOT matched L2(or L3) #mu: " << Fake_L2_noMatch_etapt->GetEntries();
  t->DrawLatex(0.0,0.6,stmp.str().c_str());
  stmp.str("");  stmp << "Fake: " << Fake_L2_noMatch_etapt->GetEntries()/Fake_L2_fired_etapt->GetEntries();
  t->DrawLatex(0.0,0.5,stmp.str().c_str());
  stmp.str("");  stmp << "Input file : " << file_name;
  t->DrawLatex(0.0,0.4,stmp.str().c_str());
  stmp.str("");  stmp << "Trigger path: " << flag->trigPath;
  t->DrawLatex(0.0,0.3,stmp.str().c_str());
  cfake->SaveAs("fake_2D.png");
  delete cfake;
  } // Fake calculation is not executed now
*/



  delete Eff_etapt;
  delete Eff_acc_etapt;
  delete Eff_match_etapt;
  delete Eff_etapt_di;
  delete Eff_acc_etapt_di;
  delete Eff_match_etapt_di;

  delete Eff_eta;
  delete Eff_phi;
  delete Eff_pt;
  delete Eff_acc_eta;
  delete Eff_acc_phi;
  delete Eff_acc_pt;
  delete Eff_match_eta;
  delete Eff_match_phi;
  delete Eff_match_pt;

  delete Eff_eta_di;
  delete Eff_phi_di;
  delete Eff_pt_di;
  delete Eff_mass_di;
  delete Eff_acc_eta_di;
  delete Eff_acc_phi_di;
  delete Eff_acc_pt_di;
  delete Eff_acc_mass_di;
  delete Eff_match_eta_di;
  delete Eff_match_phi_di;
  delete Eff_match_pt_di;
  delete Eff_match_mass_di;

  // Fake
/*  delete Fake_etapt;
  delete Fake_L2_fired_etapt;
  delete Fake_L2_noMatch_etapt;

  delete Fake_eta;
  delete Fake_phi;
  delete Fake_pt;
  delete Fake_L2_fired_eta;
  delete Fake_L2_fired_phi;
  delete Fake_L2_fired_pt;
  delete Fake_L2_noMatch_eta;
  delete Fake_L2_noMatch_phi;
  delete Fake_L2_noMatch_pt;

  delete Fake_eta_di;
  delete Fake_phi_di;
  delete Fake_pt_di;
  delete Fake_mass_di;
  delete Fake_L2_fired_eta_di;
  delete Fake_L2_fired_phi_di;
  delete Fake_L2_fired_pt_di;
  delete Fake_L2_fired_mass_di;
  delete Fake_L2_noMatch_eta_di;
  delete Fake_L2_noMatch_phi_di;
  delete Fake_L2_noMatch_pt_di;
  delete Fake_L2_noMatch_mass_di;*/

  delete info;
  return 0;
}
