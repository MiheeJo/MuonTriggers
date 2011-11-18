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

// Get fake for all trigger pahts
int match(const char *file_name, FLAG *flag, TFile *output);



int fakeTrig() {

  // Trigger path name and it's trigger level pair is needed!
  // e.g) [L1 path name] = 1; [L2 path name] = 2; [L3 path name] = 3;
  map<string,int>::iterator it_trig;

  // Dimuon triggers
  map<string,int> *triglist = new map<string,int>;
/*  (*triglist)["HLT_HIL1DoubleMuOpen"] = 1;
  (*triglist)["HLT_HIL2DoubleMu0"] = 2;
  (*triglist)["HLT_HIL2DoubleMu3"] = 2;
  (*triglist)["HLT_HIL3DoubleMuOpen"] = 3;
  (*triglist)["HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy"] = 3;*/
/*  (*triglist)["L1_DoubleMuOpen_BptxAND"] = 1;
  (*triglist)["HLT_HIL1DoubleMu0_HighQ_v1"] = 1;
  (*triglist)["HLT_HIL2DoubleMu3_v1"] = 2;
  (*triglist)["HLT_HIL3DoubleMuOpen_v1"] = 3;
  (*triglist)["HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy_v1"] = 3;*/

  // Single muon triggers
  map<string,int> *triglist_single = new map<string,int>;
//  (*triglist_single)["HLT_HIL1SingleMu3"] = 1;
//  (*triglist_single)["HLT_HIL1SingleMu5"] = 1;
//  (*triglist_single)["HLT_HIL1SingleMu7"] = 1;
//  (*triglist_single)["HLT_HIL2Mu3"] = 2;
//  (*triglist_single)["HLT_HIL2Mu7"] = 2;
//  (*triglist_single)["HLT_HIL2Mu15"] = 2;
//  (*triglist_single)["HLT_HIL2Mu3_NHitQ"] = 2;
//  (*triglist_single)["HLT_HIL3Mu3"] = 3;

  (*triglist_single)["L1_SingleMu3_BptxAND"] = 1;
  (*triglist_single)["HLT_HIL2Mu3_v1"] = 2;
  (*triglist_single)["HLT_HIL2Mu7_v1"] = 2;
  (*triglist_single)["HLT_HIL2Mu15_v1"] = 2;
  (*triglist_single)["HLT_HIL2Mu3_NHitQ_v1"] = 2;
  (*triglist_single)["HLT_HIL3Mu3_v1"] = 3;

  const int nTrig = triglist->size() + triglist_single->size();

  FLAG *flag = new FLAG;
  // Matching parameters  
  flag->doSta = true;
  flag->doGlb = false;
  flag->match_dR = true;
  flag->fdir = "/castor/cern.ch/user/m/miheejo/openHLT/cms442p5/HICorePhysics_Skim_MinimumBias_RAW/";
/*"/castor/cern.ch/user/m/miheejo/openHLT/RD2011/";
  flag->refTrigPath = "HLT_HIMinBiasHfOrBSC_v1";*/
//"/castor/cern.ch/user/m/miheejo/openHLT/cms442/";  
//  flag->refTrigPath = "HLT_HIMinBiasBSC";

  //Array for input file names
  const int nFiles = 1;
  const char *filelist[nFiles] = {"openhlt_2010HICorePhysicsMB.root"};
  //{"openhlt_r181611_reco_v1.root"};
  //{"openHLT181531_181532.root"};
  //{"HIHLT_HIDiMuonv2_RECO_GRIF_v10.root"};
  
  

  TFile *output = new TFile("./trig_fake.root","RECREATE");
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
    sys->Exec(Form("mv HLT_* L1_* %s",filelist[f]));
  } // End of all trigger paths processing


  output->Close();
  return 0;
}

int match(const char *file_name, FLAG *flag, TFile *output) {
  // Fake
  TH2F *Fake_etapt = new TH2F("Fake_etapt","Fake_etapt;single mu #eta;single mu p_{T}",ETA,-2.4,2.4,PT,0,20);
  TH2F *Fake_fired_etapt = new TH2F("Fake_fired_etapt","Fake_fired_etapt;single mu #eta;single mu p_{T}",ETA,-2.4,2.4,PT,0,20);
  TH2F *Fake_noMatch_etapt = new TH2F("Fake_noMatch_etapt","Fake_noMatch_etapt;single mu #eta;single mu p_{T}",ETA,-2.4,2.4,PT,0,20);

  TGraphAsymmErrors *Fake_eta = new TGraphAsymmErrors(); 
  TGraphAsymmErrors *Fake_phi = new TGraphAsymmErrors();
  TGraphAsymmErrors *Fake_pt = new TGraphAsymmErrors();
  TH1F *Fake_fired_eta = new TH1F("fake_fired_eta","fake_fired_eta;single mu #eta",ETA,-2.4,2.4);
  TH1F *Fake_fired_phi = new TH1F("fake_fired_phi","fake_fired_phi;single mu #phi",PHI,-PI,PI);
  TH1F *Fake_fired_pt = new TH1F("fake_fired_pt","fake_fired_pt;single mu p_{T}",PT,0,20);
  TH1F *Fake_noMatch_eta = new TH1F("fake_noMatch_eta","fake_noMatch_eta;single mu #eta",ETA,-2.4,2.4);
  TH1F *Fake_noMatch_phi = new TH1F("fake_noMatch_phi","fake_noMatch_phi;single mu #phi",PHI,-PI,PI);
  TH1F *Fake_noMatch_pt = new TH1F("fake_noMatch_pt","fake_noMatch_pt;single mu p_{T}",PT,0,20);

  TH2F *Fake_etapt_di = new TH2F("Fake_etapt_di","Fake_etapt_di;dimu #eta;dimu p_{T}",ETA,-2.4,2.4,PT,0,20);
  TH2F *Fake_fired_etapt_di = new TH2F("Fake_fired_etapt_di","Fake_fired_etapt_di;dimu #eta;dimu p_{T}",ETA,-2.4,2.4,PT,0,20);
  TH2F *Fake_noMatch_etapt_di = new TH2F("Fake_noMatch_etapt_di","Fake_noMatch_etapt_di;dimu #eta;dimu p_{T}",ETA,-2.4,2.4,PT,0,20);

  TGraphAsymmErrors *Fake_eta_di = new TGraphAsymmErrors(); 
  TGraphAsymmErrors *Fake_phi_di = new TGraphAsymmErrors();
  TGraphAsymmErrors *Fake_pt_di = new TGraphAsymmErrors();
  TGraphAsymmErrors *Fake_mass_di = new TGraphAsymmErrors();
  TH1F *Fake_fired_eta_di = new TH1F("fake_fired_eta_di","fake_fired_eta_di;dimu #eta",ETA,-2.4,2.4);
  TH1F *Fake_fired_phi_di = new TH1F("fake_fired_phi_di","fake_fired_phi_di;dimu #phi",PHI,-PI,PI);
  TH1F *Fake_fired_pt_di = new TH1F("fake_fired_pt_di","fake_fired_pt_di;dimu p_{T}",PT,0,20);
  TH1F *Fake_fired_mass_di = new TH1F("fake_fired_mass_di","fake_fired_mass_di;dimu mass",40,0,20);
  TH1F *Fake_noMatch_eta_di = new TH1F("fake_noMatch_eta_di","fake_noMatch_eta_di;dimu #eta",ETA,-2.4,2.4);
  TH1F *Fake_noMatch_phi_di = new TH1F("fake_noMatch_phi_di","fake_noMatch_phi_di;dimu #phi",PHI,-PI,PI);
  TH1F *Fake_noMatch_pt_di = new TH1F("fake_noMatch_pt_di","fake_noMatch_pt_di;dimu p_{T}",PT,0,20);
  TH1F *Fake_noMatch_mass_di = new TH1F("fake_noMatch_mass_di","fake_noMatch_mass_di;dimu mass",40,0,20);


  ////////// Read input file
  string ftmp;
/*  ftmp = "/castor/cern.ch/user/m/miheejo//openHLT/cms440p10/HICorePhysics_L1DoubleMuOpen_RAWHLTRECO/v3/muTree_newL1newHLT.root";
  TCastorFile   *input = new TCastorFile(ftmp.c_str());
  ftmp = "/castor/cern.ch/user/m/miheejo//openHLT/cms440p10/HICorePhysics_L1DoubleMuOpen_RAWHLTRECO/v3/hltana_newL1newHLT.root";
  TCastorFile   *input2 = new TCastorFile(ftmp.c_str());*/
  ftmp = flag->fdir + file_name;
  TCastorFile   *input = new TCastorFile(ftmp.c_str());
  FriendMuTree  *mutree = new FriendMuTree(input,true);
  HltTree       *ohTree = new HltTree(input,true);

  TTree         *muon_tree;
  TTree         *open_tree;
  MUTREE        *muTree = new MUTREE;

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
      cout << "muTree and ohTree don't have same run/event number. Strange." << endl;
      cout << "muTree->Run: " << muTree->run << "\tohTree->Run: " << ohTree->Run << endl;
      cout << "muTree->Event: " << muTree->event << "\tohTree->Event: " << ohTree->Event << endl;
      continue;
    }

    ////////// Get information of muon objects in gen, L1, L2 levels
    info->tot_NohMuL2 += mutree->NohMuL2;
    info->tot_NohMuL3 += mutree->NohMuL3;

    if (flag->trig && flag->trigLevel == 1) info->tot_NL1ValidEvt++;
    else if (flag->trig && flag->trigLevel == 2) info->tot_NL2ValidEvt++;
    else if (flag->trig && flag->trigLevel == 3) info->tot_NL3ValidEvt++;

    ////////// Matching Gen, L2 muons and get fake
    MATCH *fakeGenL2 = new MATCH;
    map<float,int,ptcomp> hltmu;
    map<float,int>::iterator it;

    if (!flag->trig) continue;  // Process if this trigger is fired
    // Get reference muons (==L1/L2/L3 muons)
    if (flag->trigLevel == 1) {
      for (int a=0; a<ohTree->NL1Mu; a++) {
        hltmu[ohTree->L1MuPt[a]] = a;
        fakeGenL2->ref_eta.push_back(ohTree->L1MuEta[a]);
        fakeGenL2->ref_pt.push_back(ohTree->L1MuPt[a]);
        fakeGenL2->ref_phi.push_back(ohTree->L1MuPhi[a]);
        Fake_fired_eta->Fill(ohTree->L1MuEta[a]);
        Fake_fired_phi->Fill(ohTree->L1MuPhi[a]);
        Fake_fired_pt->Fill(ohTree->L1MuPt[a]);
        Fake_fired_etapt->Fill(ohTree->L1MuEta[a],ohTree->L1MuPt[a]);
      }
    } else if (flag->trigLevel == 2) {
      for (int a=0; a<mutree->NohMuL2; a++) {
        hltmu[mutree->ohMuL2Pt[a]] = a;
        fakeGenL2->ref_eta.push_back(mutree->ohMuL2Eta[a]);
        fakeGenL2->ref_pt.push_back(mutree->ohMuL2Pt[a]);
        fakeGenL2->ref_phi.push_back(mutree->ohMuL2Phi[a]);
        Fake_fired_eta->Fill(mutree->ohMuL2Eta[a]);
        Fake_fired_phi->Fill(mutree->ohMuL2Phi[a]);
        Fake_fired_pt->Fill(mutree->ohMuL2Pt[a]);
        Fake_fired_etapt->Fill(mutree->ohMuL2Eta[a],mutree->ohMuL2Pt[a]);
      }
    } else if (flag->trigLevel == 3) {
      for (int a=0; a<mutree->NohMuL3; a++) {
        hltmu[mutree->ohMuL3Pt[a]] = a;
        fakeGenL2->ref_eta.push_back(mutree->ohMuL3Eta[a]);
        fakeGenL2->ref_pt.push_back(mutree->ohMuL3Pt[a]);
        fakeGenL2->ref_phi.push_back(mutree->ohMuL3Phi[a]);
        Fake_fired_eta->Fill(mutree->ohMuL3Eta[a]);
        Fake_fired_phi->Fill(mutree->ohMuL3Phi[a]);
        Fake_fired_pt->Fill(mutree->ohMuL3Pt[a]);
        Fake_fired_etapt->Fill(mutree->ohMuL3Eta[a],mutree->ohMuL3Pt[a]);
      }
    }


    
/*      if (flag->doGen) {
          if (!flag->doSim && muTree->status[a] == -99) continue;    //skip sim muon
          if ( (!flag->jpsi && muTree->mom[a] != 553) || (flag->jpsi && muTree->mom[a] != 443) ) continue;
        }
      */

    
//    if (flag->doGlb && !gen.empty())
//      info->tot_NGlbValidEvt++;


    ////////// Check L2 object and gen mu are matched
    vector<int>::iterator icand;
    if (flag->match_dR) {
      for (unsigned int a=0; a < fakeGenL2->ref_eta.size(); a++) {
        for (int b=0; b< muTree->nptl; b++) {
          icand = find(fakeGenL2->cand_idx.begin(), fakeGenL2->cand_idx.end(),a);
          if (icand == fakeGenL2->cand_idx.end())
            matching(fakeGenL2,a,b,muTree->eta[b],muTree->phi[b]);
            cout << "i " << i << " a " << a << " b " << b << " dR  " << fakeGenL2->deltaR[a] << endl;
        }
      }
    } else {
      for (unsigned int a=0; a<fakeGenL2->ref_eta.size(); a++) {
        fakeGenL2->deltaR.push_back(0.0);    //Because there are no L1 muons, not apply dCut for L1 object matching
      }
    }  // End of matching


    ////////// Fill efficiency numerator
    // For single muons
    for (unsigned int a=0; a<fakeGenL2->ref_eta.size(); a++) {
      if ( flag->trig && !fakeGenL2->deltaR.empty() && (fakeGenL2->deltaR[a] > flag->dCut) ){
          Fake_noMatch_eta->Fill(fakeGenL2->ref_eta[a]);
          Fake_noMatch_phi->Fill(fakeGenL2->ref_phi[a]);
          Fake_noMatch_pt->Fill(fakeGenL2->ref_pt[a]);
          Fake_noMatch_etapt->Fill(fakeGenL2->ref_eta[a],fakeGenL2->ref_pt[a]);
      }
    }

    ///////// For di-muons
/*    if (flag->dimuTrig && gen.size()==2) {  //Consider only there are 2 muons in a event
      TLorentzVector L2mu1, L2mu2, L2dimu;
      L2mu1.SetPtEtaPhiM(fakeGenL2->ref_pt[0],fakeGenL2->ref_eta[0],fakeGenL2->ref_phi[0],Mmu);
      L2mu2.SetPtEtaPhiM(fakeGenL2->ref_pt[1],fakeGenL2->ref_eta[1],fakeGenL2->ref_phi[1],Mmu);
      L2dimu = L2mu1 + L2mu2; // Use only 0th, 1th L1 objects
      // Fill denominator
      Fake_fired_mass_di->Fill(L2dimu.M());
      Fake_fired_phi_di->Fill(L2dimu.Phi());
      Fake_fired_eta_di->Fill(L2dimu.Eta());
      Fake_fired_pt_di->Fill(L2dimu.Pt());
      Fake_fired_etapt_di->Fill(L2dimu.Eta(),L2dimu.Pt());

      // Fill numerator
      if (flag->trig && (fakeGenL2->deltaR[0] < flag->dCut && fakeGenL2->deltaR[1] > flag->dCut)){
        Fake_noMatch_mass_di->Fill(L2dimu.M());
        Fake_noMatch_phi_di->Fill(L2dimu.Phi());
        Fake_noMatch_eta_di->Fill(L2dimu.Eta());
        Fake_noMatch_pt_di->Fill(L2dimu.Pt());
        Fake_noMatch_etapt_di->Fill(L2dimu.Eta(),L2dimu.Pt());
      }
    }*/

    delete fakeGenL2;

    if (i%100 == 0)
      cout << "End of processing entry: " << i << endl;
  } // End of processing 1 entry in trees
  // End of reading entire entries in trees


  Fake_eta->SetMarkerStyle(kFullCircle); Fake_eta->SetMarkerSize(1.2);
  Fake_phi->SetMarkerStyle(kFullCircle); Fake_phi->SetMarkerSize(1.2);
  Fake_pt->SetMarkerStyle(kFullCircle);  Fake_pt->SetMarkerSize(1.2);

  Fake_eta->Divide(Fake_noMatch_eta,Fake_fired_eta,"cl=0.683 b(1,1) mode");
  Fake_phi->Divide(Fake_noMatch_phi,Fake_fired_phi,"cl=0.683 b(1,1) mode");
  Fake_pt->Divide(Fake_noMatch_pt,Fake_fired_pt,"cl=0.683 b(1,1) mode");
  Fake_etapt->Divide(Fake_noMatch_etapt,Fake_fired_etapt);

  if (flag->doGen) {
    string title = "fake with gen muon, " + flag->trigPath;
    Fake_eta->SetTitle(title.c_str());
    Fake_phi->SetTitle(title.c_str());
    Fake_pt->SetTitle(title.c_str());
    Fake_etapt->SetTitle(title.c_str());
  } else {
    string title = "fake with sta muon, " + flag->trigPath;
    Fake_eta->SetTitle(title.c_str());
    Fake_phi->SetTitle(title.c_str());
    Fake_pt->SetTitle(title.c_str());
    Fake_etapt->SetTitle(title.c_str());
  }
  string title;
  title = "Fake_eta_" + flag->trigPath;
  Fake_eta->SetName(title.c_str());
  title = "Fake_phi_" + flag->trigPath;
  Fake_phi->SetName(title.c_str());
  title = "Fake_pt_" + flag->trigPath;
  Fake_pt->SetName(title.c_str());
  title = "Fake_etapt_" + flag->trigPath;
  Fake_etapt->SetName(title.c_str());

  Fake_eta->GetXaxis()->SetTitle("single mu #eta");
  Fake_phi->GetXaxis()->SetTitle("single mu #phi");
  Fake_pt->GetXaxis()->SetTitle("single mu p_{T}");
  Fake_etapt->GetXaxis()->SetTitle("single mu #eta");
  Fake_etapt->GetYaxis()->SetTitle("single mu p_{T}");

  Fake_eta->SetMaximum(1.2);
  Fake_phi->SetMaximum(1.2);
  Fake_pt->SetMaximum(1.2);

  output->cd();
  Fake_eta->Write();
  Fake_phi->Write();
  Fake_pt->Write();
  Fake_etapt->Write();

  Fake_eta_di->SetMarkerStyle(kFullCircle); Fake_eta_di->SetMarkerSize(1.2);
  Fake_mass_di->SetMarkerStyle(kFullCircle); Fake_mass_di->SetMarkerSize(1.2);
  Fake_pt_di->SetMarkerStyle(kFullCircle);  Fake_pt_di->SetMarkerSize(1.2);

  Fake_eta_di->Divide(Fake_noMatch_eta_di,Fake_fired_eta_di,"cl=0.683 b(1,1) mode");
  Fake_mass_di->Divide(Fake_noMatch_mass_di,Fake_fired_mass_di,"cl=0.683 b(1,1) mode");
  Fake_pt_di->Divide(Fake_noMatch_pt_di,Fake_fired_pt_di,"cl=0.683 b(1,1) mode");
  Fake_etapt_di->Divide(Fake_noMatch_etapt_di,Fake_fired_etapt_di);


  if (flag->doGen) {
    title = "fake with gen muon, " + flag->trigPath;
    Fake_eta_di->SetTitle(title.c_str());
    Fake_mass_di->SetTitle(title.c_str());
    Fake_pt_di->SetTitle(title.c_str());
    Fake_etapt_di->SetTitle(title.c_str());
  } else {
    title = "fake with sta muon, " + flag->trigPath;
    Fake_eta_di->SetTitle(title.c_str());
    Fake_mass_di->SetTitle(title.c_str());
    Fake_pt_di->SetTitle(title.c_str());
    Fake_etapt_di->SetTitle(title.c_str());
  }
  title = "Fake_eta_di_" + flag->trigPath;
  Fake_eta_di->SetName(title.c_str());
  title = "Fake_mass_di_" + flag->trigPath;
  Fake_mass_di->SetName(title.c_str());
  title = "Fake_pt_di_" + flag->trigPath;
  Fake_pt_di->SetName(title.c_str());
  title = "Fake_etapt_di_" + flag->trigPath;
  Fake_etapt_di->SetName(title.c_str());

  Fake_eta_di->GetXaxis()->SetTitle("dimu #eta");
  Fake_mass_di->GetXaxis()->SetTitle("dimu mass");
  Fake_pt_di->GetXaxis()->SetTitle("dimu p_{T}");
  Fake_etapt_di->GetXaxis()->SetTitle("dimu #eta");
  Fake_etapt_di->GetYaxis()->SetTitle("dimu p_{T}");

  Fake_eta_di->SetMaximum(1.2);
  Fake_mass_di->SetMaximum(1.2);
  Fake_pt_di->SetMaximum(1.2);

  output->cd();
  Fake_eta_di->Write();
  Fake_mass_di->Write();
  Fake_pt_di->Write();
  Fake_etapt_di->Write();



  ////////// fakeiciency
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  TLatex *t = new TLatex(); t->SetNDC(kTRUE);
  TPaletteAxis *paxis;
  stringstream stmp;

  TCanvas *cfake = new TCanvas("fake","fake",1300,1000);
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
  stmp.str("");  stmp << "Total # of fired #mu: " << Fake_fired_eta->GetEntries();
  t->DrawLatex(0.0,0.7,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of not matched #mu: " << Fake_noMatch_eta->GetEntries();
  t->DrawLatex(0.0,0.6,stmp.str().c_str());
  stmp.str("");  stmp << "fake: " << Fake_noMatch_eta->GetEntries()/Fake_fired_eta->GetEntries();
  t->DrawLatex(0.0,0.5,stmp.str().c_str());
  stmp.str("");  stmp << "Input file : " << file_name;
  t->DrawLatex(0.0,0.4,stmp.str().c_str());
  stmp.str("");  stmp << "Trigger path: " << flag->trigPath;
  t->DrawLatex(0.0,0.3,stmp.str().c_str());
  cfake->SaveAs("fake.png");
  cfake->Clear();  cfake->Divide(2,2);
  cfake->cd(1);    Fake_fired_eta->Draw();
  cfake->cd(2);    Fake_fired_phi->Draw();
  cfake->cd(3);    Fake_fired_pt->Draw();
  cfake->SaveAs("fake_fired.png");
  cfake->Clear();  cfake->Divide(2,2);
  cfake->cd(1);    Fake_noMatch_eta->Draw();
  cfake->cd(2);    Fake_noMatch_phi->Draw();
  cfake->cd(3);    Fake_noMatch_pt->Draw();
  cfake->SaveAs("fake_noMatch.png");
  delete cfake;
  if (flag->dimuTrig) {
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
  stmp.str("");  stmp << "Total # of fired di #mu: " << Fake_fired_eta_di->GetEntries();
  t->DrawLatex(0.0,0.7,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of not matched di #mu: " << Fake_noMatch_eta_di->GetEntries();
  t->DrawLatex(0.0,0.6,stmp.str().c_str());
  stmp.str("");  stmp << "fake: " << Fake_noMatch_eta_di->GetEntries()/Fake_fired_eta_di->GetEntries();
  t->DrawLatex(0.0,0.5,stmp.str().c_str());
  stmp.str("");  stmp << "Input file : " << file_name;
  t->DrawLatex(0.0,0.4,stmp.str().c_str());
  stmp.str("");  stmp << "Trigger path: " << flag->trigPath;
  t->DrawLatex(0.0,0.3,stmp.str().c_str());
  cfake->SaveAs("fake_dimu.png");
  cfake->Clear();  cfake->Divide(2,2);
  cfake->cd(1);    Fake_fired_eta_di->Draw();
  cfake->cd(2);    Fake_fired_mass_di->Draw();
  cfake->cd(3);    Fake_fired_pt_di->Draw();
  cfake->SaveAs("fake_fired_dimu.png");
  cfake->Clear();  cfake->Divide(2,2);
  cfake->cd(1);    Fake_noMatch_eta_di->Draw();
  cfake->cd(2);    Fake_noMatch_mass_di->Draw();
  cfake->cd(3);    Fake_noMatch_pt_di->Draw();
  cfake->SaveAs("fake_noMatch_dimu.png");
  delete cfake;
  }
  cfake = new TCanvas("fake","fake",1300,1000);
  cfake->Divide(2,2);
  cfake->cd(1);    Fake_etapt->Draw("colz");
  gPad->Update();
  paxis = (TPaletteAxis*)Fake_etapt->GetListOfFunctions()->FindObject("palette");
  if (paxis != NULL) {paxis->SetY2NDC(0.7); paxis->SetLabelSize(0.03);}
  cfake->cd(2);    Fake_fired_etapt->Draw("colz");
  gPad->Update();
  paxis = (TPaletteAxis*)Fake_fired_etapt->GetListOfFunctions()->FindObject("palette");
  if (paxis != NULL) {paxis->SetY2NDC(0.7); paxis->SetLabelSize(0.03);}
  cfake->cd(3);    Fake_noMatch_etapt->Draw("colz");
  gPad->Update();
  paxis = (TPaletteAxis*)Fake_noMatch_etapt->GetListOfFunctions()->FindObject("palette");
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
  stmp.str("");  stmp << "Total # of fired #mu: " << Fake_fired_etapt->GetEntries();
  t->DrawLatex(0.0,0.7,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of not matched #mu: " << Fake_noMatch_etapt->GetEntries();
  t->DrawLatex(0.0,0.6,stmp.str().c_str());
  stmp.str("");  stmp << "fake: " << Fake_noMatch_etapt->GetEntries()/Fake_fired_etapt->GetEntries();
  t->DrawLatex(0.0,0.5,stmp.str().c_str());
  stmp.str("");  stmp << "Input file : " << file_name;
  t->DrawLatex(0.0,0.4,stmp.str().c_str());
  stmp.str("");  stmp << "Trigger path: " << flag->trigPath;
  t->DrawLatex(0.0,0.3,stmp.str().c_str());
  cfake->SaveAs("fake_2D.png");
  delete cfake;
  if (flag->dimuTrig) {
  cfake = new TCanvas("fake","fake",1300,1000);
  cfake->Divide(2,2);
  cfake->cd(1);    Fake_etapt_di->Draw("colz");
  gPad->Update();
  paxis = (TPaletteAxis*)Fake_etapt_di->GetListOfFunctions()->FindObject("palette");
  if (paxis != NULL) {paxis->SetY2NDC(0.7); paxis->SetLabelSize(0.03);}
  cfake->cd(2);    Fake_fired_etapt_di->Draw("colz");
  gPad->Update();
  paxis = (TPaletteAxis*)Fake_fired_etapt_di->GetListOfFunctions()->FindObject("palette");
  if (paxis != NULL) {paxis->SetY2NDC(0.7); paxis->SetLabelSize(0.03);}
  cfake->cd(3);    Fake_noMatch_etapt_di->Draw("colz");
  gPad->Update();
  paxis = (TPaletteAxis*)Fake_noMatch_etapt_di->GetListOfFunctions()->FindObject("palette");
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
  stmp.str("");  stmp << "Total # of fired di#mu: " << Fake_fired_etapt_di->GetEntries();
  t->DrawLatex(0.0,0.7,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of not matched di#mu: " << Fake_noMatch_etapt_di->GetEntries();
  t->DrawLatex(0.0,0.6,stmp.str().c_str());
  stmp.str("");  stmp << "fake: " << Fake_noMatch_etapt_di->GetEntries()/Fake_fired_etapt_di->GetEntries();
  t->DrawLatex(0.0,0.5,stmp.str().c_str());
  stmp.str("");  stmp << "Input file : " << file_name;
  t->DrawLatex(0.0,0.4,stmp.str().c_str());
  stmp.str("");  stmp << "Trigger path: " << flag->trigPath;
  t->DrawLatex(0.0,0.3,stmp.str().c_str());
  cfake->SaveAs("fake_di_2D.png");
  delete cfake;
  }

  output->cd();
  output->Write();

  delete Fake_etapt;
  delete Fake_fired_etapt;
  delete Fake_noMatch_etapt;
  delete Fake_etapt_di;
  delete Fake_fired_etapt_di;
  delete Fake_noMatch_etapt_di;

  delete Fake_eta;
  delete Fake_phi;
  delete Fake_pt;
  delete Fake_fired_eta;
  delete Fake_fired_phi;
  delete Fake_fired_pt;
  delete Fake_noMatch_eta;
  delete Fake_noMatch_phi;
  delete Fake_noMatch_pt;

  delete Fake_eta_di;
  delete Fake_phi_di;
  delete Fake_pt_di;
  delete Fake_mass_di;
  delete Fake_fired_eta_di;
  delete Fake_fired_phi_di;
  delete Fake_fired_pt_di;
  delete Fake_fired_mass_di;
  delete Fake_noMatch_eta_di;
  delete Fake_noMatch_phi_di;
  delete Fake_noMatch_pt_di;
  delete Fake_noMatch_mass_di;


  delete info;
  return 0;
}
