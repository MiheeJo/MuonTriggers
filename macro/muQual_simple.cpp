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

int muQual_simple() {

  // Parameters  
  FLAG *flag = new FLAG;
  flag->doSta = true;
  flag->doGlb = false;
  flag->match_dR = false;
  flag->fdir = "/castor/cern.ch/user/m/miheejo/openHLT/cms442p5/HICorePhysics_Skim_MinimumBias_RAW/openhlt_2010HICorePhysicsMB";

  // Check trigger list
  vector<string> *triglist = new vector<string>;
  triglist->push_back("HLT_HIL1DoubleMu0_HighQ_v1");
  triglist->push_back("HLT_HIL2DoubleMu3_v1");
  triglist->push_back("HLT_HIL3DoubleMuOpen_v1");
  triglist->push_back("HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy_v1");
  triglist->push_back("HLT_HIL2Mu3_v1");
  triglist->push_back("HLT_HIL2Mu7_v1");
  triglist->push_back("HLT_HIL2Mu15_v1");
  triglist->push_back("HLT_HIL2Mu3_NHitQ_v1");
  triglist->push_back("HLT_HIL3Mu3_v1");


  // Histograms
  TH2F *SingleGlb_Etapt = new TH2F("SingleGlb_etapt","SingleGlb_etapt;single mu #eta;single mu p_{T}",ETA,-2.4,2.4,PT,0,20);

  TCastorFile   *input = new TCastorFile(flag->fdir.c_str());
  FriendMuTree  *mutree = new FriendMuTree(input,true); // Load HLTMuTree
  HltTree       *ohTree = new HltTree(input,true);      // Load HltTree

  TTree         *muon_tree;                             // Hold HLTMuTree
  TTree         *open_tree;                             // Hold HltTree
  MUTREE        *muTree = new MUTREE;


  open_tree = ohTree->fChain;                           // Get TTree for trigger bits
  open_tree->SetBranchAddress(flag->trigPath.c_str(),&flag->trig);    // SetBranchAddress for trigger bits

  muon_tree = mutree->fChain;                           // Get TTree for muon objects
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


  // Loop over trees
  for (int i=0; i<muon_tree->GetEntries(); i++) {
    muon_tree->GetEntry(i);
    ohTree->GetEntry(i);
    open_tree->GetEntry(i);

    ////////// Check muon trigger list
    
    
    ////////// Load muons and fill up histograms
    for (int a=0; a < muTree->nptl; a++) {
      if (flag->doGlb) {
        if(!isValidMu(flag, muTree, a)) continue;    //Check glb muons are within acceptance range
      } else if (flag->doSta) {
        if(!isMuInAcc(flag,muTree->eta[a], muTree->pt[a])) continue;    //Check sta muons are within acceptance range
      }
      
      SingleGlb_Etapt->Fill(muTree->eta[a],muTree->pt[a]);

    }


  }



  return 0;
}
