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
  
  string data2010  = "/castor/cern.ch/user/m/miheejo/openHLT/cms442p5/HICorePhysics_Skim_MinimumBias_RAW/openhlt_2010HICorePhysicsMB.root";
  // 2011 file will be updated.
  string data2011  = "/castor/cern.ch/user/m/miheejo/openHLT/cms442p5/HICorePhysics_Skim_MinimumBias_RAW/openhlt_2010HICorePhysicsMB.root";

  // Check trigger list
  vector<string> triglist;
  triglist.push_back("HLT_HIL1DoubleMu0_HighQ_v1");
  triglist.push_back("HLT_HIL2DoubleMu3_v1");
  triglist.push_back("HLT_HIL3DoubleMuOpen_v1");
  triglist.push_back("HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy_v1");
  triglist.push_back("HLT_HIL2Mu3_v1");
  triglist.push_back("HLT_HIL2Mu7_v1");
  triglist.push_back("HLT_HIL2Mu15_v1");
  triglist.push_back("HLT_HIL2Mu3_NHitQ_v1");
  triglist.push_back("HLT_HIL3Mu3_v1");

  // Histograms
  TH2F *SingleGlb_Etapt_2010 = new TH2F("SingleGlb_etapt_2010","SingleGlb_etapt_2010;single mu #eta;single mu p_{T}",ETA,-2.4,2.4,PT,0,20);
  TH2F *SingleGlb_Etapt_2011 = new TH2F("SingleGlb_etapt_2011","SingleGlb_etapt_2011;single mu #eta;single mu p_{T}",ETA,-2.4,2.4,PT,0,20);


  // Input files
  // 2010 datafile
  TCastorFile   *input_2010 = new TCastorFile(data2010.c_str());
  FriendMuTree  *mutree_2010 = new FriendMuTree(input_2010,true); // Load HLTMuTree
  HltTree       *ohTree_2010 = new HltTree(input_2010,true);      // Load HltTree

  TTree         *muon_tree_2010;                             // Hold HLTMuTree
  TTree         *open_tree_2010;                             // Hold HltTree
  MUTREE        *muTree_2010 = new MUTREE;

  // 2011 datafile
  TCastorFile   *input_2011 = new TCastorFile(data2011.c_str());
  FriendMuTree  *mutree_2011 = new FriendMuTree(input_2011,true); // Load HLTMuTree
  HltTree       *ohTree_2011 = new HltTree(input_2011,true);      // Load HltTree

  TTree         *muon_tree_2011;                             // Hold HLTMuTree
  TTree         *open_tree_2011;                             // Hold HltTree
  MUTREE        *muTree_2011 = new MUTREE;


  const unsigned int ntrig = triglist.size();
  int trig_2010[ntrig];                                // Trigger bits for muons
  int trig_2011[ntrig];                                // Trigger bits for muons
  open_tree_2010 = ohTree_2010->fChain;                           // Get TTree for trigger bits
  open_tree_2011 = ohTree_2011->fChain;                           // Get TTree for trigger bits
  for (unsigned int i=0; i < ntrig; i++) {
    string tmptrig = triglist[i];
    open_tree_2010->SetBranchAddress(tmptrig.c_str(),&trig_2010[i]);    // SetBranchAddress for trigger bits
    open_tree_2011->SetBranchAddress(tmptrig.c_str(),&trig_2011[i]);    // SetBranchAddress for trigger bits
  }

  muon_tree_2010 = mutree_2010->fChain;                           // Get TTree for muon objects
  muon_tree_2010->SetBranchAddress("Run",&muTree_2010->run);
  muon_tree_2010->SetBranchAddress("Event",&muTree_2010->event);
  muon_tree_2011 = mutree_2011->fChain;                           // Get TTree for muon objects
  muon_tree_2011->SetBranchAddress("Run",&muTree_2011->run);
  muon_tree_2011->SetBranchAddress("Event",&muTree_2011->event);
  if (flag->doSta && !flag->doGlb) {
   muon_tree_2010->SetBranchAddress("Sta_eta",muTree_2010->eta);
   muon_tree_2010->SetBranchAddress("Sta_pt",muTree_2010->pt);
   muon_tree_2010->SetBranchAddress("Sta_phi",muTree_2010->phi);
   muon_tree_2010->SetBranchAddress("Sta_nptl",&muTree_2010->nptl);
   muon_tree_2010->SetBranchAddress("Sta_charge",muTree_2010->charge);
   muon_tree_2011->SetBranchAddress("Sta_eta",muTree_2011->eta);
   muon_tree_2011->SetBranchAddress("Sta_pt",muTree_2011->pt);
   muon_tree_2011->SetBranchAddress("Sta_phi",muTree_2011->phi);
   muon_tree_2011->SetBranchAddress("Sta_nptl",&muTree_2011->nptl);
   muon_tree_2011->SetBranchAddress("Sta_charge",muTree_2011->charge);
  } else if (flag->doGlb && !flag->doSta) {
   muon_tree_2011->SetBranchAddress("Glb_eta",muTree_2011->eta);
   muon_tree_2011->SetBranchAddress("Glb_pt",muTree_2011->pt);
   muon_tree_2011->SetBranchAddress("Glb_phi",muTree_2011->phi);
   muon_tree_2011->SetBranchAddress("Glb_nptl",&muTree_2011->nptl);
   muon_tree_2011->SetBranchAddress("Glb_charge",muTree_2011->charge);
   muon_tree_2011->SetBranchAddress("Glb_nValMuHits",muTree_2011->nValMuHits);
   muon_tree_2011->SetBranchAddress("Glb_nValTrkHits",muTree_2011->nValTrkHits);
   muon_tree_2011->SetBranchAddress("Glb_nTrkFound",muTree_2011->nTrkFound);
   muon_tree_2011->SetBranchAddress("Glb_glbChi2_ndof",muTree_2011->glbChi2_ndof);
   muon_tree_2011->SetBranchAddress("Glb_trkChi2_ndof",muTree_2011->trkChi2_ndof);
   muon_tree_2011->SetBranchAddress("Glb_pixLayerWMeas",muTree_2011->pixLayerWMeas);
   muon_tree_2011->SetBranchAddress("Glb_trkDxy",muTree_2011->trkDxy);
   muon_tree_2011->SetBranchAddress("Glb_trkDz",muTree_2011->trkDz);

   muon_tree_2010->SetBranchAddress("Glb_eta",muTree_2010->eta);
   muon_tree_2010->SetBranchAddress("Glb_pt",muTree_2010->pt);
   muon_tree_2010->SetBranchAddress("Glb_phi",muTree_2010->phi);
   muon_tree_2010->SetBranchAddress("Glb_nptl",&muTree_2010->nptl);
   muon_tree_2010->SetBranchAddress("Glb_charge",muTree_2010->charge);
   muon_tree_2010->SetBranchAddress("Glb_nValMuHits",muTree_2010->nValMuHits);
   muon_tree_2010->SetBranchAddress("Glb_nValTrkHits",muTree_2010->nValTrkHits);
   muon_tree_2010->SetBranchAddress("Glb_nTrkFound",muTree_2010->nTrkFound);
   muon_tree_2010->SetBranchAddress("Glb_glbChi2_ndof",muTree_2010->glbChi2_ndof);
   muon_tree_2010->SetBranchAddress("Glb_trkChi2_ndof",muTree_2010->trkChi2_ndof);
   muon_tree_2010->SetBranchAddress("Glb_pixLayerWMeas",muTree_2010->pixLayerWMeas);
   muon_tree_2010->SetBranchAddress("Glb_trkDxy",muTree_2010->trkDxy);
   muon_tree_2010->SetBranchAddress("Glb_trkDz",muTree_2010->trkDz);
  } else {
    cout << "Choose doSta or doGlb or doGen!\n";
    return -1;
  }


  // Loop over trees over 2010 trees
  for (int i=0; i<muon_tree_2010->GetEntries(); i++) {
    muon_tree_2010->GetEntry(i);
    ohTree_2010->GetEntry(i);
    open_tree_2010->GetEntry(i);

    ////////// Check muon trigger list
    flag->trig = false;
    for (unsigned int tidx=0; tidx<ntrig; tidx++) {
      if (trig_2010[tidx]) {         // At least one of the muon trigger is fired.
        flag->trig = true;
        break;
      }
    }
    if (!flag->trig) continue;  // If no muon triggers fired, go to the next event!
    
    ////////// Load muons and fill up histograms
    for (int a=0; a < muTree_2010->nptl; a++) {
      if (flag->doGlb) {
        if(!isValidMu(flag, muTree_2010, a)) continue;    //Check glb muons are within acceptance range
      } else if (flag->doSta) {
        if(!isMuInAcc(flag, muTree_2010->eta[a], muTree_2010->pt[a])) continue;    //Check sta muons are within acceptance range
      }
      
      SingleGlb_Etapt_2010->Fill(muTree_2010->eta[a],muTree_2010->pt[a]);

    }

    if (i%10000 ==0)
    cout << "Event in 2010 datasets: " << i+1 << endl;
  }

  // Loop over trees over 2011 trees
  for (int i=0; i<muon_tree_2011->GetEntries(); i++) {
    muon_tree_2011->GetEntry(i);
    ohTree_2011->GetEntry(i);
    open_tree_2011->GetEntry(i);

    ////////// Check muon trigger list
    flag->trig = false;
    for (unsigned int tidx=0; tidx<ntrig; tidx++) {
      if (trig_2011[tidx]) {         // At least one of the muon trigger is fired.
        flag->trig = true;
        break;
      }
    }
    if (!flag->trig) continue;  // If no muon triggers fired, go to the next event!
    
    ////////// Load muons and fill up histograms
    for (int a=0; a < muTree_2011->nptl; a++) {
      if (flag->doGlb) {
        if(!isValidMu(flag, muTree_2011, a)) continue;    //Check glb muons are within acceptance range
      } else if (flag->doSta) {
        if(!isMuInAcc(flag, muTree_2011->eta[a], muTree_2011->pt[a])) continue;    //Check sta muons are within acceptance range
      }
      
      SingleGlb_Etapt_2011->Fill(muTree_2011->eta[a],muTree_2011->pt[a]);

    }

    if (i%10000 ==0)
    cout << "Event in 2011 datasets: " << i+1 << endl;

  }

  // Draw final histograms and save it into .png files
  gROOT->Macro("~miheejo/public/HIMuTrig/JpsiStyle.C");    //For plot style
  TCanvas *canv = new TCanvas("canv","canv",800,600);
  canv->Draw();
  SingleGlb_Etapt_2010->Draw("colz");
  canv->SaveAs("SingleGlb_Etapt_2010.png");
  canv->Clear();  canv->Draw();
  SingleGlb_Etapt_2011->Draw("colz");
  canv->SaveAs("SingleGlb_Etapt_2011.png");

  return 0;
}
