#include "matchMu_basic.cpp"

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
#include <TSystem.h>

using namespace std;

int match(const char *file_name,FLAG &flag);

int matchMu() {
//  const char *fnoh = "/castor/cern.ch/user/m/miheejo/openHLT/cms417/weimix_full/merged/hltana_jpsi03.root";
//  const char *fnMu = "/castor/cern.ch/user/m/miheejo/openHLT/cms417/weimix_full/merged/muTree_jpsi03.root";

  TSystem *sys = gSystem;

  //Array for input file names
//  const char *filelist[8] = {"jpsi03","jpsi36","jpsi69","jpsi912","ups03","ups36","ups69","ups912"};
  const char *filelist[1] = {"oldL1newL2"}; //"newL1newHLT"};
  const char *triglist[9] = {"HLT_HIL2DoubleMu0","HLT_HIL2DoubleMu3","HLT_HIL3DoubleMuOpen","HLT_HIL3DoubleMuOpen_Mgt2","HLT_HIL3DoubleMuOpen_Mgt2_SS","HLT_HIL3DoubleMuOpen_Mgt2_OS","HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy","HLT_HIL2Mu3","HLT_HIL3Mu3"};

  FLAG flag_;
  FLAG &flag = flag_;
  // Matching parameters  
  flag.doSim= false;
  flag.doGen= false;
  flag.doSta= true;
  flag.match_dR = true;
  flag.dCut = 0.4;
  flag.fdir = "/castor/cern.ch/user/m/miheejo/openHLT/cms440p10/HICorePhysics_L1DoubleMuOpen_RAWHLTRECO/newL2oldL1/";

  //Does this sample for Jpsi or not?
  for (int f=0; f<1; f++) {
/*    if (f<4) {
      flag.jpsi = true;
    } else {
      flag.jpsi = false;
    }*/

    for (int t=0; t<9; t++) {
      if (t<7) {
        flag.dimuTrig = true;
      } else {
        flag.dimuTrig = false;
      }
      flag.trig = triglist[t];

      if (match(filelist[f],flag) == -1) {
        cout << filelist[f] << endl;
        return -1;
      } else {
        sys->Exec(Form("mkdir %s",triglist[t]));
        sys->Exec(Form("mv *.png log %s",triglist[t]));
      }
    }

    sys->Exec(Form("mkdir %s",filelist[f]));
    sys->Exec(Form("mv HLT_* %s",filelist[f]));
  }
  return 0;
}

int match(const char *file_name, FLAG &flag) {
  //Directory name that contains input files
  fstream out("log", fstream::out);
  fstream res("result", fstream::out | fstream::app);

  Bool_t trig;

  // Efficiency
  TH2F *Eff_etapt = new TH2F("eff_etapt","eff_etapt;single mu #eta;single mu p_{T}",ETA,-2.4,2.4,PT,0,20);
  TH2F *Eff_acc_etapt = new TH2F("eff_acc_etapt","eff_acc_etapt;single mu #eta;single mu p_{T}",ETA,-2.4,2.4,PT,0,20);
  TH2F *Eff_match_etapt = new TH2F("eff_match_etapt","eff_match_etapt;single mu #eta;single mu p_{T}",ETA,-2.4,2.4,PT,0,20);
  TH2F *Eff_L2_match_etapt = new TH2F("eff_L2_match_etapt","eff_L2_match_etapt;single mu #eta;single mu p_{T}",ETA,-2.4,2.4,PT,0,20);

  TGraphAsymmErrors *Eff_eta = new TGraphAsymmErrors();
  TGraphAsymmErrors *Eff_phi = new TGraphAsymmErrors();
  TGraphAsymmErrors *Eff_pt = new TGraphAsymmErrors();
  TH1F *Eff_acc_eta = new TH1F("eff_acc_eta","eff_acc_eta;single mu #eta",ETA,-2.4,2.4);
  TH1F *Eff_acc_phi = new TH1F("eff_acc_phi","eff_acc_phi;single mu #phi",PHI,-PI,PI);
  TH1F *Eff_acc_pt = new TH1F("eff_acc_pt","eff_acc_pt;single mu p_{T}",PT,0,20);
  TH1F *Eff_match_eta = new TH1F("eff_match_eta","eff_match_eta;single mu #eta",ETA,-2.4,2.4);
  TH1F *Eff_match_phi = new TH1F("eff_match_phi","eff_match_phi;single mu #phi",PHI,-PI,PI);
  TH1F *Eff_match_pt = new TH1F("eff_match_pt","eff_match_pt;single mu p_{T}",PT,0,20);
  TH1F *Eff_L2_match_eta = new TH1F("eff_L2_match_eta","eff_L2_match_eta;single mu #eta",ETA,-2.4,2.4);
  TH1F *Eff_L2_match_phi = new TH1F("eff_L2_match_phi","eff_L2_match_phi;single mu #phi",PHI,-PI,PI);
  TH1F *Eff_L2_match_pt = new TH1F("eff_L2_match_pt","eff_L2_match_pt;single mu p_{T}",PT,0,20);

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
  TH1F *Eff_L2_match_eta_di = new TH1F("eff_L2_match_eta_di","eff_L2_match_eta_di;dimu #eta",ETA,-2.4,2.4);
  TH1F *Eff_L2_match_phi_di = new TH1F("eff_L2_match_phi_di","eff_L2_match_phi_di;dimu #phi",PHI,-PI,PI);
  TH1F *Eff_L2_match_pt_di = new TH1F("eff_L2_match_pt_di","eff_L2_match_pt_di;dimu p_{T}",PT,0,20);

  // Fake
  TH2F *Fake_etapt = new TH2F("Fake_etapt","Fake_etapt;single mu #eta;single mu p_{T}",ETA,-2.4,2.4,PT,0,20);
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
  TH1F *Fake_L2_noMatch_mass_di = new TH1F("fake_L2_noMatch_mass_di","fake_L2_noMatch_mass_di;dimu mass",40,0,20);



  ////////// Read input file
  string ftmp;
  ftmp = flag.fdir + "/muTree_" + file_name + ".root";
  out << ftmp << endl;
  FriendMuTree  muTree_(ftmp.c_str(),true);

  ftmp = flag.fdir + "/hltana_" + file_name + ".root";
  out << ftmp << endl;
  HltTree       ohTree_(ftmp.c_str(),true);
  HltTree       &ohTree = ohTree_;

  if (!muTree_.fChain->GetCurrentFile() || !ohTree.fChain->GetCurrentFile()) {
    cout << "Failed to open root files\n"; return -1;
  }

  TTree *mutree;
  MUTREE muTree;
  mutree = muTree_.fChain;
  mutree->SetBranchAddress("Run",&muTree.run);
  mutree->SetBranchAddress("Event",&muTree.event);
  if (flag.doGen && !flag.doSta) {
   mutree->SetBranchAddress("Gen_eta",muTree.eta);
   mutree->SetBranchAddress("Gen_pt",muTree.pt);
   mutree->SetBranchAddress("Gen_phi",muTree.phi);
   mutree->SetBranchAddress("Gen_nptl",&muTree.nptl);
   mutree->SetBranchAddress("Gen_pid",muTree.charge);
   mutree->SetBranchAddress("Gen_mom",muTree.mom);
   mutree->SetBranchAddress("Gen_status",muTree.status);
  } else if (flag.doSta && !flag.doGen) {
   mutree->SetBranchAddress("Sta_eta",muTree.eta);
   mutree->SetBranchAddress("Sta_pt",muTree.pt);
   mutree->SetBranchAddress("Sta_phi",muTree.phi);
   mutree->SetBranchAddress("Sta_nptl",&muTree.nptl);
   mutree->SetBranchAddress("Sta_charge",muTree.charge);
  } else {
    cout << "Choose doSta or doGen, not both!\n";
    return -1;
  }


  stringstream stmp;
  INFO info_;
  INFO &info = info_;
  for (int i=0; i<mutree->GetEntries(); i++) {
    mutree->GetEntry(i);
    ohTree.GetEntry(i);

    ////////// Compare event number
    bool noExist = false;
    for (int a=0; (muTree.run != ohTree.Run) || (muTree.event != ohTree.Event); a++ ) {
      if (a < mutree->GetEntries()) {
        mutree->GetEntry(a);
      } else {
        noExist = true;
        break;
      }
    }
    if (noExist) {
      cout << "muTree and ohTree don't have same run/event number. Strange." << endl;
      cout << "muTree.Run: " << muTree.run << "\tohTree.Run: " << ohTree.Run << endl;
      cout << "muTree.Event: " << muTree.event << "\tohTree.Event: " << ohTree.Event << endl;
      continue;
    }

    out << "Run: " << ohTree.Run << "\tEvent: " << ohTree.Event << endl;

    ////////// Get information of muon objects in gen, L1, L2 levels
    info.tot_NohMuL2 += ohTree.NohMuL2;
    info.tot_NohMuL3 += ohTree.NohMuL3;
//    if (ohTree.NohMuL2 > 0) info.tot_NL2ValidEvt ++;
  
    if (flag.trig.compare("HLT_HIL2DoubleMu0") == 0) {
      trig = ohTree.HLT_HIL2DoubleMu0;
      flag.trigLevel = 2;
    } else if (flag.trig.compare("HLT_HIL2DoubleMu3") == 0) {
      trig = ohTree.HLT_HIL2DoubleMu3;
      flag.trigLevel = 2;
    } else if (flag.trig.compare("HLT_HIL3DoubleMuOpen") == 0) {
      trig = ohTree.HLT_HIL3DoubleMuOpen;
      flag.trigLevel = 3;
    } else if (flag.trig.compare("HLT_HIL3DoubleMuOpen_Mgt2") == 0) {
      trig = ohTree.HLT_HIL3DoubleMuOpen_Mgt2;
      flag.trigLevel = 3;
    } else if (flag.trig.compare("HLT_HIL3DoubleMuOpen_Mgt2_SS") == 0) {
      trig = ohTree.HLT_HIL3DoubleMuOpen_Mgt2_SS;
      flag.trigLevel = 3;
    } else if (flag.trig.compare("HLT_HIL3DoubleMuOpen_Mgt2_OS") == 0) {
      trig = ohTree.HLT_HIL3DoubleMuOpen_Mgt2_OS;
      flag.trigLevel = 3;
    } else if (flag.trig.compare("HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy") == 0) {
      trig = ohTree.HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy;
      flag.trigLevel = 3;
    } else if (flag.trig.compare("HLT_HIL2Mu3") == 0) {
      trig = ohTree.HLT_HIL2Mu3;
      flag.trigLevel = 2;
    } else if (flag.trig.compare("HLT_HIL3Mu3") == 0) {
      trig = ohTree.HLT_HIL3Mu3;
      flag.trigLevel = 3;
    }

    if (flag.dimuTrig && trig) info.tot_NL2ValidEvt++;
    else if (!flag.dimuTrig && trig) info.tot_NL2ValidEvt++;

    ////////// Matching Gen, L2 muons and get eff, fake
    ////////// Check single muon acceptance
    MATCH *EffGenL2 = new MATCH;
    map<float,int,ptcomp> gen, cand;
    map<float,int>::iterator it;
    for (int a=0; a < muTree.nptl; a++) {
      if (flag.doGen) {
        if (!flag.doSim && muTree.status[a] == -99) continue;    //skip sim muon
        if ( (!flag.jpsi && muTree.mom[a] != 553) || (flag.jpsi && muTree.mom[a] != 443) ) continue;
      }
      if (fabs(muTree.eta[a]) <= 2.4) { 
        float pt = muTree.pt[a];
        gen[pt] = a;
      }
    }

    if (flag.trigLevel == 2) {
      for (int a=0; a<ohTree.NohMuL2; a++) {
        float pt = ohTree.ohMuL2Pt[a];
        cand[pt] = a;
      }
    } else if (flag.trigLevel == 3) {
      for (int a=0; a<ohTree.NohMuL3; a++) {
        float pt = ohTree.ohMuL3Pt[a];
        cand[pt] = a;
      }
    }

    // Get 1st and 2nd highest pT muon
    it=gen.begin();
    for (unsigned int gen_=0;
        ( (flag.dimuTrig && (gen_<2)) || (!flag.dimuTrig && (gen_<1)) ) && (gen_<gen.size());
        gen_++) {
      int a = it->second;
      EffGenL2->ref_eta.push_back(muTree.eta[a]);
      EffGenL2->ref_pt.push_back(muTree.pt[a]);
      EffGenL2->ref_phi.push_back(muTree.phi[a]);
      Eff_acc_eta->Fill(muTree.eta[a]);
      Eff_acc_phi->Fill(muTree.phi[a]);
      Eff_acc_pt->Fill(muTree.pt[a]);
      Eff_acc_etapt->Fill(muTree.eta[a],muTree.pt[a]);
//      out << "muTree.eta[" << a << "]: " << muTree.eta[a] << endl;
//      out << "muTree.pt[" << a << "]: " << muTree.pt[a] << endl;
      it++;
    }

    TLorentzVector L2mu1, L2mu2, L2dimu;
    if (flag.dimuTrig) {
      if (gen.size()>=2) {
        L2mu1.SetPtEtaPhiM(EffGenL2->ref_pt[0],EffGenL2->ref_eta[0],EffGenL2->ref_phi[0],Mmu);
        L2mu2.SetPtEtaPhiM(EffGenL2->ref_pt[1],EffGenL2->ref_eta[1],EffGenL2->ref_phi[1],Mmu);
        L2dimu = L2mu1 + L2mu2; // Use only 0th, 1th L1 objects
        out << "Acc L2dimu.M(): " << L2dimu.M() << endl;
        out << "Acc L2dimu.Eta(): " << L2dimu.Eta() << endl;
        out << "Acc L2dimu.Pt(): " << L2dimu.Pt() << endl;
        Eff_acc_mass_di->Fill(L2dimu.M());
        Eff_acc_phi_di->Fill(L2dimu.Phi());
        Eff_acc_eta_di->Fill(L2dimu.Eta());
        Eff_acc_pt_di->Fill(L2dimu.Pt());
      }
    }

    

    ////////// Check L2 object and gen mu are matched
    it = cand.begin();
    for (unsigned int a=0; a<EffGenL2->ref_eta.size(); a++) {
      if (flag.trigLevel == 2) {
        for (int b=0; b<ohTree.NohMuL2; b++) {
          matching(flag.match_dR,EffGenL2,a,ohTree.ohMuL2Eta[b],ohTree.ohMuL2Phi[b],ohTree.ohMuL2Pt[b]);
        }
      } else if (flag.trigLevel == 3) {
        for (int b=0; b<ohTree.NohMuL3; b++) {
          matching(flag.match_dR,EffGenL2,a,ohTree.ohMuL3Eta[b],ohTree.ohMuL3Phi[b],ohTree.ohMuL3Pt[b]);
        }
      }
      if (!EffGenL2->deltaR.empty()) {
//      out << "EffGenL2->ref_pt[" << a << "]: " << EffGenL2->ref_pt[a] << endl;
//      out << "EffGenL2->cand_pt[" << a << "]: " << EffGenL2->cand_pt[a] << endl;
//      out << "EffGenL2->dR[" << a << "]: " << EffGenL2->deltaR[a] << endl;
      }
    }

    // End of matching

    ////////// Fill efficiency numerator
    TLorentzVector L2mu[2];
    L2mu[0].SetPtEtaPhiM(0,0,0,0);
    L2mu[1].SetPtEtaPhiM(0,0,0,0);
    for (unsigned int a=0; a<EffGenL2->ref_eta.size(); a++) {
      if ( ((flag.match_dR && !EffGenL2->deltaR.empty() && (EffGenL2->deltaR[a] < flag.dCut)) ||
           (!flag.match_dR && !EffGenL2->deltaEta.empty() && (EffGenL2->deltaEta[a] < flag.dCut))) && 
           trig
         ){
          Eff_match_eta->Fill(EffGenL2->ref_eta[a]);
          Eff_match_phi->Fill(EffGenL2->ref_phi[a]);
          Eff_match_pt->Fill(EffGenL2->ref_pt[a]);
          Eff_match_etapt->Fill(EffGenL2->ref_eta[a],EffGenL2->ref_pt[a]);
          Eff_L2_match_eta->Fill(EffGenL2->cand_eta[a]);
          Eff_L2_match_phi->Fill(EffGenL2->cand_phi[a]);
          Eff_L2_match_pt->Fill(EffGenL2->cand_pt[a]);
          Eff_L2_match_etapt->Fill(EffGenL2->cand_eta[a],EffGenL2->cand_pt[a]);
        if (flag.dimuTrig) {
          L2mu[a].SetPtEtaPhiM(EffGenL2->ref_pt[a],EffGenL2->ref_eta[a],EffGenL2->ref_phi[a],Mmu);
//          out << "L2mu[" << a << "].Eta(): " << L2mu[a].Eta() << endl;
//          out << "L2mu[" << a << "].Pt(): " << L2mu[a].Pt() << endl;
        }
      }
    }
    if (flag.dimuTrig && (L2mu[0].Pt()!=0 && L2mu[1].Pt()!=0) ){
      L2dimu = L2mu[0] + L2mu[1]; // Use only 0th, 1th L1 objects
      out << "Match L2dimu.M(): " << L2dimu.M() << endl;
      out << "Match L2dimu.Eta(): " << L2dimu.Eta() << endl;
      out << "Match L2dimu.Pt(): " << L2dimu.Pt() << endl;
      Eff_match_mass_di->Fill(L2dimu.M());
      Eff_match_phi_di->Fill(L2dimu.Phi());
      Eff_match_eta_di->Fill(L2dimu.Eta());
      Eff_match_pt_di->Fill(L2dimu.Pt());
    }


    ////////// Check L2 trigger fired
    MATCH *FakeGenL2 = new MATCH;
    ////////// Fill fake numerator and denomiator
    if (trig) {
      // Get 1st and 2nd highest pT muon
      map<float,int,ptcomp> l2;
      if (flag.trigLevel == 2) {
        for (int a=0; a<ohTree.NohMuL2; a++) {
          float pt = ohTree.ohMuL2Pt[a];
          l2[pt] = a;
        }
      } else if (flag.trigLevel == 3) {
        for (int a=0; a<ohTree.NohMuL3; a++) {
          float pt = ohTree.ohMuL3Pt[a];
          l2[pt] = a;
        }
      }
      it=l2.begin();
      for (unsigned int l2_=0;
          ( (flag.dimuTrig && (l2_<2)) || (!flag.dimuTrig && (l2_<1)) ) && (l2_<l2.size())
          ;l2_++) {
        int a = it->second;
        if (flag.trigLevel == 2) {
          FakeGenL2->ref_eta.push_back(ohTree.ohMuL2Eta[a]);
          FakeGenL2->ref_pt.push_back(ohTree.ohMuL2Pt[a]);
          FakeGenL2->ref_phi.push_back(ohTree.ohMuL2Phi[a]);
          FakeGenL2->ref_chg.push_back(ohTree.ohMuL2Chg[a]);
          Fake_L2_fired_eta->Fill(ohTree.ohMuL2Eta[a]);
          Fake_L2_fired_phi->Fill(ohTree.ohMuL2Phi[a]);
          Fake_L2_fired_pt->Fill(ohTree.ohMuL2Pt[a]);
          Fake_L2_fired_etapt->Fill(ohTree.ohMuL2Eta[a],ohTree.ohMuL2Pt[a]);
        } else if (flag.trigLevel == 3) {
          FakeGenL2->ref_eta.push_back(ohTree.ohMuL3Eta[a]);
          FakeGenL2->ref_pt.push_back(ohTree.ohMuL3Pt[a]);
          FakeGenL2->ref_phi.push_back(ohTree.ohMuL3Phi[a]);
          FakeGenL2->ref_chg.push_back(ohTree.ohMuL3Chg[a]);
          Fake_L2_fired_eta->Fill(ohTree.ohMuL3Eta[a]);
          Fake_L2_fired_phi->Fill(ohTree.ohMuL3Phi[a]);
          Fake_L2_fired_pt->Fill(ohTree.ohMuL3Pt[a]);
          Fake_L2_fired_etapt->Fill(ohTree.ohMuL3Eta[a],ohTree.ohMuL3Pt[a]);
        }
//        out << "ohTree.eta[" << a << "]: " << ohTree.ohMuL2Eta[a] << endl;
//        out << "ohTree.pt[" << a << "]: " << ohTree.ohMuL2Pt[a] << endl;
        it++;
      }

//      TLorentzVector L2mu1, L2mu2, L2dimu;
      if (flag.dimuTrig) {
        if (l2.size()>=2) {
          L2mu1.SetPtEtaPhiM(FakeGenL2->ref_pt[0],FakeGenL2->ref_eta[0],FakeGenL2->ref_phi[0],Mmu);
          L2mu2.SetPtEtaPhiM(FakeGenL2->ref_pt[1],FakeGenL2->ref_eta[1],FakeGenL2->ref_phi[1],Mmu);

          L2dimu = L2mu1 + L2mu2; // Use only 0th, 1th L1 objects
          out << "Fired L2dimu.M(): " << L2dimu.M() << endl;
          out << "Fired L2dimu.Eta(): " << L2dimu.Eta() << endl;
          out << "Fired L2dimu.Pt(): " << L2dimu.Pt() << endl;
          Fake_L2_fired_mass_di->Fill(L2dimu.M());
          Fake_L2_fired_phi_di->Fill(L2dimu.Phi());
          Fake_L2_fired_eta_di->Fill(L2dimu.Eta());
          Fake_L2_fired_pt_di->Fill(L2dimu.Pt());
        }
      }


      // Get deltaR, deltaEta
      for (unsigned int a=0; a<FakeGenL2->ref_eta.size(); a++) {
        for (int b=0; b<muTree.nptl; b++) {
          if (flag.doGen) {
            if (!flag.doSim && muTree.status[b] == -99) continue;    //skip sim muon
            if ( (!flag.jpsi && muTree.mom[b] != 553) || (flag.jpsi && muTree.mom[b] != 443) ) continue;
          }
          matching(flag.match_dR,FakeGenL2,a,muTree.eta[b],muTree.phi[b],muTree.pt[b],muTree.charge[b]);
        }
        if (!FakeGenL2->deltaR.empty()) {
//        out << "FakeGenL2->ref_pt[" << a << "]: " << FakeGenL2->ref_pt[a] << endl;
//        out << "FakeGenL2->ref_chg[" << a << "]: " << FakeGenL2->ref_chg[a] << endl;
//        out << "FakeGenL2->cand_pt[" << a << "]: " << FakeGenL2->cand_pt[a] << endl;
//        out << "FakeGenL2->cand_chg[" << a << "]: " << FakeGenL2->cand_chg[a] << endl;
//        out << "FakeGenL2->dR[" << a << "]: " << FakeGenL2->deltaR[a] << endl;
        }
      } // End of matching


      ////////// Fill fake numerator
      TLorentzVector L2match;
      L2mu[0].SetPtEtaPhiM(0,0,0,0);
      L2mu[1].SetPtEtaPhiM(0,0,0,0);
      int nUnmatch =0;
      for (unsigned int a=0; a<FakeGenL2->ref_eta.size(); a++) {
        if ( (flag.match_dR && !FakeGenL2->deltaR.empty() && FakeGenL2->deltaR[a] > flag.dCut ) ||
             (!flag.match_dR && !FakeGenL2->deltaEta.empty() && FakeGenL2->deltaEta[a] > flag.dCut) ) {
          Fake_L2_noMatch_eta->Fill(FakeGenL2->ref_eta[a]);
          Fake_L2_noMatch_phi->Fill(FakeGenL2->ref_phi[a]);
          Fake_L2_noMatch_pt->Fill(FakeGenL2->ref_pt[a]);
          Fake_L2_noMatch_etapt->Fill(FakeGenL2->ref_eta[a],FakeGenL2->ref_pt[a]);
          if (flag.dimuTrig) {
            L2mu[nUnmatch].SetPtEtaPhiM(FakeGenL2->ref_pt[a],FakeGenL2->ref_eta[a],FakeGenL2->ref_phi[a],Mmu);
//            out << "L2mu[" << nUnmatch  << "].Eta(): " << L2mu[nUnmatch].Eta() << endl;
//            out << "L2mu[" << nUnmatch << "].Pt(): " << L2mu[nUnmatch].Pt() << endl;
            nUnmatch++;
          }
        } else {
          L2match.SetPtEtaPhiM(FakeGenL2->ref_pt[a],FakeGenL2->ref_eta[a],FakeGenL2->ref_phi[a],Mmu);
          out << "L2matchmu.Eta(): " << L2match.Eta() << endl;
          out << "L2match.Pt(): " << L2match.Pt() << endl;
        }
      }

      if (flag.dimuTrig && nUnmatch > 0) {
        if (nUnmatch == 1) L2mu[1] = L2match;
        L2dimu = L2mu[0] + L2mu[1]; // Use only 0th, 1th L1 objects
        out << "noMatched L2dimu.M(): " << L2dimu.M() << endl;
        out << "noMatched L2dimu.Eta(): " << L2dimu.Eta() << endl;
        out << "noMatched L2dimu.Pt(): " << L2dimu.Pt() << endl;
        Fake_L2_noMatch_mass_di->Fill(L2dimu.M());
        Fake_L2_noMatch_phi_di->Fill(L2dimu.Phi());
        Fake_L2_noMatch_eta_di->Fill(L2dimu.Eta());
        Fake_L2_noMatch_pt_di->Fill(L2dimu.Pt());
      }

    } // End of flag.dimuTrig conditions

    out << "End of processing entry: " << i << endl;
  } // End of processing 1 entry in trees
  // End of reading entire entries in trees


  ////////// Efficiency
  Eff_eta->SetMarkerStyle(kFullCircle); Eff_eta->SetMarkerSize(1.2);
  Eff_phi->SetMarkerStyle(kFullCircle); Eff_phi->SetMarkerSize(1.2);
  Eff_pt->SetMarkerStyle(kFullCircle);  Eff_pt->SetMarkerSize(1.2);

  Eff_eta->Divide(Eff_match_eta,Eff_acc_eta,"cl=0.683 b(1,1) mode");
  Eff_phi->Divide(Eff_match_phi,Eff_acc_phi,"cl=0.683 b(1,1) mode");
  Eff_pt->Divide(Eff_match_pt,Eff_acc_pt,"cl=0.683 b(1,1) mode");

  if (flag.doGen) {
    Eff_eta->SetTitle("Efficiency with gen muon info");
    Eff_phi->SetTitle("Efficiency with gen muon info");
    Eff_pt->SetTitle("Efficiency with gen muon info");
  } else {
    Eff_eta->SetTitle("Efficiency with sta muon info");
    Eff_phi->SetTitle("Efficiency with sta muon info");
    Eff_pt->SetTitle("Efficiency with sta muon info");
  }

  Eff_eta->GetXaxis()->SetTitle("single mu #eta");
  Eff_phi->GetXaxis()->SetTitle("single mu #phi");
  Eff_pt->GetXaxis()->SetTitle("single mu p_{T}");

  Eff_eta->SetMaximum(1.2);
  Eff_phi->SetMaximum(1.2);
  Eff_pt->SetMaximum(1.2);

  Eff_eta_di->SetMarkerStyle(kFullCircle); Eff_eta_di->SetMarkerSize(1.2);
  Eff_mass_di->SetMarkerStyle(kFullCircle); Eff_mass_di->SetMarkerSize(1.2);
  Eff_pt_di->SetMarkerStyle(kFullCircle);  Eff_pt_di->SetMarkerSize(1.2);

  Eff_eta_di->Divide(Eff_match_eta_di,Eff_acc_eta_di,"cl=0.683 b(1,1) mode");
  Eff_mass_di->Divide(Eff_match_mass_di,Eff_acc_mass_di,"cl=0.683 b(1,1) mode");
  Eff_pt_di->Divide(Eff_match_pt_di,Eff_acc_pt_di,"cl=0.683 b(1,1) mode");

  if (flag.doGen) {
    Eff_eta_di->SetTitle("Efficiency with gen muon info");
    Eff_mass_di->SetTitle("Efficiency with gen muon info");
    Eff_pt_di->SetTitle("Efficiency with gen muon info");
  } else {
    Eff_eta_di->SetTitle("Efficiency with sta muon info");
    Eff_mass_di->SetTitle("Efficiency with sta muon info");
    Eff_pt_di->SetTitle("Efficiency with sta muon info");
  }

  Eff_eta_di->GetXaxis()->SetTitle("dimu #eta");
  Eff_mass_di->GetXaxis()->SetTitle("dimu mass");
  Eff_pt_di->GetXaxis()->SetTitle("dimu p_{T}");

  Eff_eta_di->SetMaximum(1.2);
  Eff_mass_di->SetMaximum(1.2);
  Eff_pt_di->SetMaximum(1.2);

  Eff_etapt->Divide(Eff_match_etapt,Eff_acc_etapt);

  ////////// Fake 
  Fake_eta->SetMarkerStyle(kFullCircle);  Fake_eta->SetMarkerSize(1.2);
  Fake_phi->SetMarkerStyle(kFullCircle);  Fake_phi->SetMarkerSize(1.2);
  Fake_pt->SetMarkerStyle(kFullCircle);   Fake_pt->SetMarkerSize(1.2);

  Fake_eta->Divide(Fake_L2_noMatch_eta,Fake_L2_fired_eta,"cl=0.683 b(1,1) mode");
  Fake_phi->Divide(Fake_L2_noMatch_phi,Fake_L2_fired_phi,"cl=0.683 b(1,1) mode");
  Fake_pt->Divide(Fake_L2_noMatch_pt,Fake_L2_fired_pt,"cl=0.683 b(1,1) mode");

  if (flag.doGen) {
    Fake_eta->SetTitle("Fake with L2 muon info (gen matching)");
    Fake_phi->SetTitle("Fake with L2 muon info (gen matching)");
    Fake_pt->SetTitle("Fake with L2 muon info (gen matching)");
  } else {
    Fake_eta->SetTitle("Fake with L2 muon info (sta matching)");
    Fake_phi->SetTitle("Fake with L2 muon info (sta matching)");
    Fake_pt->SetTitle("Fake with L2 muon info (sta matching)");
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

  if (flag.doGen) {
    Fake_eta_di->SetTitle("Fake with L2 muon info (gen matching)");
    Fake_mass_di->SetTitle("Fake with L2 muon info (gen matching)");
    Fake_pt_di->SetTitle("Fake with L2 muon info (gen matching)");
  } else {
    Fake_eta_di->SetTitle("Fake with L2 muon info (sta matching)");
    Fake_mass_di->SetTitle("Fake with L2 muon info (sta matching)");
    Fake_pt_di->SetTitle("Fake with L2 muon info (sta matching)");
  }

  Fake_eta_di->GetXaxis()->SetTitle("dimu #eta");
  Fake_mass_di->GetXaxis()->SetTitle("dimu mass");
  Fake_pt_di->GetXaxis()->SetTitle("dimu p_{T}");

  Fake_eta_di->SetMaximum(1.2);
  Fake_mass_di->SetMaximum(1.2);
  Fake_pt_di->SetMaximum(1.2);

  Fake_etapt->Divide(Fake_L2_noMatch_etapt,Fake_L2_fired_etapt);
  

  ////////// If basic muon distributions are needed
//  matchMu_basic(muTree,ohTree,flag,info);


  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  TLatex *t = new TLatex(); t->SetNDC(kTRUE);
  TPaletteAxis *paxis;


  TCanvas *ceff = new TCanvas("eff","eff",1300,1000);
  ceff->Divide(2,2);
  ceff->cd(1);    Eff_eta->Draw("ap");
  ceff->cd(2);    Eff_phi->Draw("ap");
  ceff->cd(3);    Eff_pt->Draw("ap");
  ceff->cd(4);
  stmp.str("");  stmp << "Events: " << mutree->GetEntries();
  t->DrawLatex(0.1,0.9,stmp.str().c_str());
  stmp.str("");  stmp << "L2 fired events: " << info.tot_NL2ValidEvt;
  t->DrawLatex(0.1,0.8,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of accepted #mu: " << Eff_acc_eta->GetEntries();
  t->DrawLatex(0.1,0.7,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of matched #mu: " << Eff_match_eta->GetEntries();
  t->DrawLatex(0.1,0.6,stmp.str().c_str());
  stmp.str("");  stmp << "Eff: " << Eff_match_eta->GetEntries()/Eff_acc_eta->GetEntries();
  t->DrawLatex(0.1,0.5,stmp.str().c_str());
  stmp.str("");  stmp << "Input file : " << file_name;
  t->DrawLatex(0.1,0.4,stmp.str().c_str());
  stmp.str("");  stmp << "Trigger path: " << flag.trig;
  t->DrawLatex(0.1,0.3,stmp.str().c_str());
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
  stmp.str("");  stmp << "Events: " << mutree->GetEntries();
  t->DrawLatex(0.1,0.9,stmp.str().c_str());
  stmp.str("");  stmp << "L2 fired events: " << info.tot_NL2ValidEvt;
  t->DrawLatex(0.1,0.8,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of accepted di#mu: " << Eff_acc_eta_di->GetEntries();
  t->DrawLatex(0.1,0.7,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of matched di#mu: " << Eff_match_eta_di->GetEntries();
  t->DrawLatex(0.1,0.6,stmp.str().c_str());
  stmp.str("");  stmp << "Eff: " << Eff_match_eta_di->GetEntries()/Eff_acc_eta_di->GetEntries();
  t->DrawLatex(0.1,0.5,stmp.str().c_str());
  stmp.str("");  stmp << "Input file : " << file_name;
  t->DrawLatex(0.1,0.4,stmp.str().c_str());
  stmp.str("");  stmp << "Trigger path: " << flag.trig;
  t->DrawLatex(0.1,0.3,stmp.str().c_str());
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
  stmp.str("");  stmp << "Events: " << mutree->GetEntries();
  t->DrawLatex(0.1,0.9,stmp.str().c_str());
  stmp.str("");  stmp << "L2 fired events: " << info.tot_NL2ValidEvt;
  t->DrawLatex(0.1,0.8,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of accepted #mu: " << Eff_acc_etapt->GetEntries();
  t->DrawLatex(0.1,0.7,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of matched #mu: " << Eff_match_etapt->GetEntries();
  t->DrawLatex(0.1,0.6,stmp.str().c_str());
  stmp.str("");  stmp << "Eff: " << Eff_match_etapt->GetEntries()/Eff_acc_etapt->GetEntries();
  t->DrawLatex(0.1,0.5,stmp.str().c_str());
  stmp.str("");  stmp << "Input file : " << file_name;
  t->DrawLatex(0.1,0.4,stmp.str().c_str());
  stmp.str("");  stmp << "Trigger path: " << flag.trig;
  t->DrawLatex(0.1,0.3,stmp.str().c_str());
  ceff->SaveAs("eff_2D.png");
  delete ceff;

  TCanvas *cfake = new TCanvas("fake","fake",1300,1000);
  cfake->Divide(2,2);
  cfake->cd(1);    Fake_eta->Draw("ap");
  cfake->cd(2);    Fake_phi->Draw("ap");
  cfake->cd(3);    Fake_pt->Draw("ap");
  cfake->cd(4);
  stmp.str("");  stmp << "Events: " << mutree->GetEntries();
  t->DrawLatex(0.1,0.9,stmp.str().c_str());
  stmp.str("");  stmp << "L2 fired events: " << info.tot_NL2ValidEvt;
  t->DrawLatex(0.1,0.8,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of fired L2 #mu: " << Fake_L2_fired_eta->GetEntries();
  t->DrawLatex(0.1,0.7,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of NOT matched L2 #mu: " << Fake_L2_noMatch_eta->GetEntries();
  t->DrawLatex(0.1,0.6,stmp.str().c_str());
  stmp.str("");  stmp << "Fake: " << Fake_L2_noMatch_eta->GetEntries()/Fake_L2_fired_eta->GetEntries();
  t->DrawLatex(0.1,0.5,stmp.str().c_str());
  stmp.str("");  stmp << "Input file : " << file_name;
  t->DrawLatex(0.1,0.4,stmp.str().c_str());
  stmp.str("");  stmp << "Trigger path: " << flag.trig;
  t->DrawLatex(0.1,0.3,stmp.str().c_str());
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
  stmp.str("");  stmp << "Events: " << mutree->GetEntries();
  t->DrawLatex(0.1,0.9,stmp.str().c_str());
  stmp.str("");  stmp << "L2 fired events: " << info.tot_NL2ValidEvt;
  t->DrawLatex(0.1,0.8,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of fired L2 di#mu: " << Fake_L2_fired_eta_di->GetEntries();
  t->DrawLatex(0.1,0.7,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of NOT matched L2 di#mu: " << Fake_L2_noMatch_eta_di->GetEntries();
  t->DrawLatex(0.1,0.6,stmp.str().c_str());
  stmp.str("");  stmp << "Fake: " << Fake_L2_noMatch_eta_di->GetEntries()/Fake_L2_fired_eta_di->GetEntries();
  t->DrawLatex(0.1,0.5,stmp.str().c_str());
  stmp.str("");  stmp << "Input file : " << file_name;
  t->DrawLatex(0.1,0.4,stmp.str().c_str());
  stmp.str("");  stmp << "Trigger path: " << flag.trig;
  t->DrawLatex(0.1,0.3,stmp.str().c_str());
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
  stmp.str("");  stmp << "Events: " << mutree->GetEntries();
  t->DrawLatex(0.1,0.9,stmp.str().c_str());
  stmp.str("");  stmp << "L2 fired events: " << info.tot_NL2ValidEvt;
  t->DrawLatex(0.1,0.8,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of fired L2 #mu: " << Fake_L2_fired_etapt->GetEntries();
  t->DrawLatex(0.1,0.7,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of NOT matched L2 #mu: " << Fake_L2_noMatch_etapt->GetEntries();
  t->DrawLatex(0.1,0.6,stmp.str().c_str());
  stmp.str("");  stmp << "Fake: " << Fake_L2_noMatch_etapt->GetEntries()/Fake_L2_fired_etapt->GetEntries();
  t->DrawLatex(0.1,0.5,stmp.str().c_str());
  stmp.str("");  stmp << "Input file : " << file_name;
  t->DrawLatex(0.1,0.4,stmp.str().c_str());
  stmp.str("");  stmp << "Trigger path: " << flag.trig;
  t->DrawLatex(0.1,0.3,stmp.str().c_str());
  cfake->SaveAs("fake_2D.png");
  delete cfake;


  res << file_name << "\t" << mutree->GetEntries() << endl;
  res << flag.trig << "\t" << info.tot_NL2ValidEvt << endl;
  res << "Eff" << endl;
  res << Eff_acc_eta->GetEntries() << "\t" << Eff_match_eta->GetEntries() << "\t" << Eff_match_eta->GetEntries()/Eff_acc_eta->GetEntries() << endl;
  res << Eff_acc_eta_di->GetEntries() << "\t" << Eff_match_eta_di->GetEntries() << "\t" << Eff_match_eta_di->GetEntries()/Eff_acc_eta_di->GetEntries() << endl;
  res << "Fake" << endl;
  res << Fake_L2_fired_eta->GetEntries() << "\t" << Fake_L2_noMatch_eta->GetEntries() << "\t" << Fake_L2_noMatch_eta->GetEntries()/Fake_L2_fired_eta->GetEntries() << endl;
  res << Fake_L2_fired_eta_di->GetEntries() << "\t" << Fake_L2_noMatch_eta_di->GetEntries() << "\t" << Fake_L2_noMatch_eta_di->GetEntries()/Fake_L2_fired_eta_di->GetEntries() << endl;


  delete Eff_etapt;
  delete Eff_acc_etapt;
  delete Eff_match_etapt;
  delete Eff_L2_match_etapt;

  delete Eff_eta;
  delete Eff_phi;
  delete Eff_pt;
  delete Eff_acc_eta;
  delete Eff_acc_phi;
  delete Eff_acc_pt;
  delete Eff_match_eta;
  delete Eff_match_phi;
  delete Eff_match_pt;
  delete Eff_L2_match_eta;
  delete Eff_L2_match_phi;
  delete Eff_L2_match_pt;

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
  delete Eff_L2_match_eta_di;
  delete Eff_L2_match_phi_di;
  delete Eff_L2_match_pt_di;

  // Fake
  delete Fake_etapt;
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
  delete Fake_L2_noMatch_mass_di;

  res.close();
  out.close();

  return 0;
}
