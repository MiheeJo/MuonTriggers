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



int effTrig() {

  // Trigger path name and it's trigger level pair is needed!
  // e.g) [L1 path name] = 1; [L2 path name] = 2; [L3 path name] = 3;
  map<string,int>::iterator it_trig;

  // Dimuon triggers
  map<string,int> *triglist = new map<string,int>;
  (*triglist)["L1_DoubleMuOpen_BptxAND"] = 1;
  (*triglist)["HLT_HIL1DoubleMuOpen_HighQ_v1"] = 1;
  (*triglist)["HLT_HIL2DoubleMu3_v1"] = 2;
  (*triglist)["HLT_HIL3DoubleMuOpen_v1"] = 3;
  (*triglist)["HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy_v1"] = 3;

  // Single muon triggers
  map<string,int> *triglist_single = new map<string,int>;
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
  flag->fdir = "/castor/cern.ch/user/k/kimy/openHLT/";//"//"/castor/cern.ch/user/m/miheejo/openHLT/cms440p10/MC425/jpsi/";
  flag->refTrigPath = "HLT_HIMinBiasHfOrBSC_v1";

  //Array for input file names
  const int nFiles = 1;
  const char *filelist[nFiles] =  {"openhlt_run181531.root"};

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
    sys->Exec(Form("mv HLT_* L1_* %s",filelist[f]));
  } // End of all trigger paths processing


  output->Close();
  return 0;
}

int match(const char *file_name, FLAG *flag, TFile *output) {
  // Efficiency
  TH2F *Eff_etapt = new TH2F("eff_etapt","eff_etapt;single mu #eta;single mu p_{T}",ETA,-2.4,2.4,PT,0,20);
  TH2F *Eff_acc_etapt = new TH2F("eff_acc_etapt","eff_acc_etapt;single mu #eta;single mu p_{T}",ETA,-2.4,2.4,PT,0,20);
  TH2F *Eff_match_etapt = new TH2F("eff_match_etapt","eff_match_etapt;single mu #eta;single mu p_{T}",ETA,-2.4,2.4,PT,0,20);

  TH1F *Eff_eta = new TH1F("eff_eta","eff_eta;single mu #eta",ETA,-2.4,2.4);
  TH1F *Eff_phi = new TH1F("eff_phi","eff_phi;single mu #phi",PHI,-PI,PI);
  TH1F *Eff_pt = new TH1F("eff_pt","eff_pt;single mu p_{T}",PT,0,20);
  TH1F *Eff_acc_eta = new TH1F("eff_acc_eta","eff_acc_eta;single mu #eta",ETA,-2.4,2.4);
  TH1F *Eff_acc_phi = new TH1F("eff_acc_phi","eff_acc_phi;single mu #phi",PHI,-PI,PI);
  TH1F *Eff_acc_pt = new TH1F("eff_acc_pt","eff_acc_pt;single mu p_{T}",PT,0,20);
  TH1F *Eff_match_eta = new TH1F("eff_match_eta","eff_match_eta;single mu #eta",ETA,-2.4,2.4);
  TH1F *Eff_match_phi = new TH1F("eff_match_phi","eff_match_phi;single mu #phi",PHI,-PI,PI);
  TH1F *Eff_match_pt = new TH1F("eff_match_pt","eff_match_pt;single mu p_{T}",PT,0,20);

  TH2F *Eff_etapt_di = new TH2F("eff_etapt_di","eff_etapt_di;dimu #eta;dimu p_{T}",ETA,-2.4,2.4,PT,0,20);
  TH2F *Eff_acc_etapt_di = new TH2F("eff_acc_etapt_di","eff_acc_etapt_di;dimu #eta;dimu p_{T}",ETA,-2.4,2.4,PT,0,20);
  TH2F *Eff_match_etapt_di = new TH2F("eff_match_etapt_di","eff_match_etapt_di;dimu #eta;dimu p_{T}",ETA,-2.4,2.4,PT,0,20);

  TH1F *Eff_eta_di = new TH1F("eff_eta_di","eff_eta_di;dimu #eta",ETA,-2.4,2.4);
  TH1F *Eff_phi_di = new TH1F("eff_phi_di","eff_phi_di;dimu #phi",PHI,-PI,PI);
  TH1F *Eff_pt_di = new TH1F("eff_pt_di","eff_pt_di;dimu p_{T}",PT,0,20);
  TH1F *Eff_mass_di = new TH1F("eff_mass_di","eff_mass_di;dimu mass",40,0,20);
  TH1F *Eff_acc_eta_di = new TH1F("eff_acc_eta_di","eff_acc_eta_di;dimu #eta",ETA,-2.4,2.4);
  TH1F *Eff_acc_phi_di = new TH1F("eff_acc_phi_di","eff_acc_phi_di;dimu #phi",PHI,-PI,PI);
  TH1F *Eff_acc_pt_di = new TH1F("eff_acc_pt_di","eff_acc_pt_di;dimu p_{T}",PT,0,20);
  TH1F *Eff_acc_mass_di = new TH1F("eff_acc_mass_di","eff_acc_mass_di;dimu mass",40,0,20);
  TH1F *Eff_match_eta_di = new TH1F("eff_match_eta_di","eff_match_eta_di;dimu #eta",ETA,-2.4,2.4);
  TH1F *Eff_match_phi_di = new TH1F("eff_match_phi_di","eff_match_phi_di;dimu #phi",PHI,-PI,PI);
  TH1F *Eff_match_pt_di = new TH1F("eff_match_pt_di","eff_match_pt_di;dimu p_{T}",PT,0,20);
  TH1F *Eff_match_mass_di = new TH1F("eff_match_mass_di","eff_match_mass_di;dimu mass",40,0,20);

  ////////// Read input file
  string ftmp;
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
  open_tree->SetBranchAddress(flag->refTrigPath.c_str(),&flag->refTrig);

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
        ( (flag->dimuTrig && (gen_<2)) || (!flag->dimuTrig && (gen_<1)) ) && gen_<gen.size() && flag->refTrig;
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
      if (gen.size()>=2 && flag->refTrig) {
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
/*    it = cand.begin();
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
*/

    ////////// Fill efficiency numerator
    TLorentzVector L2mu[2];
    L2mu[0].SetPtEtaPhiM(0,0,0,0);
    L2mu[1].SetPtEtaPhiM(0,0,0,0);
    // For single muons
    for (unsigned int a=0; a<EffGenL2->ref_eta.size(); a++) {
      if ( flag->trig && flag->refTrig){
          Eff_match_eta->Fill(EffGenL2->ref_eta[a]);
          Eff_match_phi->Fill(EffGenL2->ref_phi[a]);
          Eff_match_pt->Fill(EffGenL2->ref_pt[a]);
          Eff_match_etapt->Fill(EffGenL2->ref_eta[a],EffGenL2->ref_pt[a]);
        if (flag->dimuTrig) {
          L2mu[a].SetPtEtaPhiM(EffGenL2->ref_pt[a],EffGenL2->ref_eta[a],EffGenL2->ref_phi[a],Mmu);
        }
      }
    }

    // For di-muons
    if (!flag->match_dR && flag->dimuTrig && flag->trig && flag->refTrig && (L2mu[0].Pt()!=0 && L2mu[1].Pt()!=0) ){
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


    if (i%1000 == 0)
      cout << "End of processing entry: " << i << endl;
  } // End of processing 1 entry in trees
  // End of reading entire entries in trees

  Eff_eta->Divide(Eff_match_eta,Eff_acc_eta);
  Eff_phi->Divide(Eff_match_phi,Eff_acc_phi);
  Eff_pt->Divide(Eff_match_pt,Eff_acc_pt);
  Eff_etapt->Divide(Eff_match_etapt,Eff_acc_etapt);
  Eff_eta_di->Divide(Eff_match_eta_di,Eff_acc_eta_di);
  Eff_mass_di->Divide(Eff_match_mass_di,Eff_acc_mass_di);
  Eff_pt_di->Divide(Eff_match_pt_di,Eff_acc_pt_di);
  Eff_etapt_di->Divide(Eff_match_etapt_di,Eff_acc_etapt_di);

  ////////// Efficiency
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  TLatex *t = new TLatex(); t->SetNDC(kTRUE);
  TPaletteAxis *paxis;
  stringstream stmp;


  TCanvas *ceff = new TCanvas("eff","eff",1300,1000);
  ceff->Divide(2,2);
  ceff->cd(1);    Eff_eta->Draw();
  ceff->cd(2);    Eff_phi->Draw();
  ceff->cd(3);    Eff_pt->Draw();
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
  ceff->cd(1);    Eff_eta_di->Draw();
  ceff->cd(2);    Eff_mass_di->Draw();
  ceff->cd(3);    Eff_pt_di->Draw();
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


  output->cd();
  output->Write();

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


  delete info;
  return 0;
}
