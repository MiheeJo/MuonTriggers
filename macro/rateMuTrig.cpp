#ifndef MATCHMU
#define MATCHMU
#include "matchMu.h"
#include "matchMu_tree.h"
#endif

#include <sstream>
#include <TLorentzVector.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLatex.h>
#include <TPaletteAxis.h>

using namespace std;

int rateMuTrig() {
  const char *fnoh = "/castor/cern.ch/user/m/miheejo/openHLT/cms440p10/HICorePhysics_L1DoubleMuOpen_RAWHLTRECO/newL2newL1/hltana_newL1newL2.root";
  const char *fnMu = "/castor/cern.ch/user/m/miheejo/openHLT/cms440p10/HICorePhysics_L1DoubleMuOpen_RAWHLTRECO/newL2newL1/muTree_newL1newL2.root";

  FLAG flag_;
  FLAG &flag = flag_;

  // Trigger cut parameters
  flag.doDimuMassCut = true;
  flag.mCut = 2.0;             //in GeV
  flag.doSinglemuPtCut = true;
  flag.pTCut = 1.0;             //in GeV
  flag.doGen = false;
  flag.doSta = false;
  flag.doGlb = true;

  // Triggered object with trigger paths
  vector<string> trigPath;  //TrigPath, read L2/L3 or not
  vector<int> readHLT;
//  trigPath.push_back("L1_SingleMu3");
//  readHLT.push_back(0);
/*    trigPath.push_back("HLT_HIMinBiasHfOrBSC_v1");
    readHLT.push_back(1);
    trigPath.push_back("HLT_HIL1SingleMu3_v1");
    readHLT.push_back(1);
    trigPath.push_back("HLT_HIL1SingleMu5_v1");
    readHLT.push_back(1);
    trigPath.push_back("HLT_HIL1SingleMu7_v1");
    readHLT.push_back(1);
    trigPath.push_back("HLT_HIL2Mu3_v1");
    readHLT.push_back(2);
    trigPath.push_back("HLT_HIL2Mu5Tight_v1");
    readHLT.push_back(2);*/
    trigPath.push_back("HLT_HIL1DoubleMuOpen_v1");
    readHLT.push_back(1);
    trigPath.push_back("HLT_HIL1DoubleMu0_HighQ");
    readHLT.push_back(1);
    trigPath.push_back("HLT_HIL2DoubleMu0_NHitQ");
    readHLT.push_back(2);
    trigPath.push_back("HLT_HIL2DoubleMu0_L1HighQL2NHitQ");
    readHLT.push_back(2);
    trigPath.push_back("HLT_HIL2DoubleMu0_v1");
    readHLT.push_back(2);
    trigPath.push_back("HLT_HIL2DoubleMu3_v1");
    readHLT.push_back(2);
/*    trigPath.push_back("HLT_HIL3DoubleMuOpen_Mgt2");
    readHLT.push_back(3);
    trigPath.push_back("HLT_HIL3DoubleMuOpen_Mgt2_SS");
    readHLT.push_back(3);
    trigPath.push_back("HLT_HIL3DoubleMuOpen_Mgt2_OS");
    readHLT.push_back(3);
    trigPath.push_back("HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy");
    readHLT.push_back(3);*/
/*  trigPath.push_back("HLT_HIL1SingleMu3");
  readHLT.push_back(1);
  trigPath.push_back("HLT_HIL2Mu3");
  readHLT.push_back(2);
//  trigPath.push_back("HLT_HIL3Mu3");
//  readHLT.push_back(3);
//  trigPath.push_back("L1_DoubleMuOpen");
//  readHLT.push_back(0);
  trigPath.push_back("HLT_HIL1DoubleMuOpen");
  readHLT.push_back(1);
  trigPath.push_back("HLT_HIL2DoubleMu0");
  readHLT.push_back(2);
  trigPath.push_back("HLT_HIL2DoubleMu3");
  readHLT.push_back(2);*/

  const unsigned int ntrig = trigPath.size();
  Int_t trig[ntrig];
  string title;

  // Number of trigger fired
  int Trig_fired[ntrig];
  for (unsigned int idx=0; idx<ntrig; idx++) {
    Trig_fired[idx] = 0;
  }


  // Dimuon mass
  const int massMax = 50;
  TH1F *Dimu_mass_glb[ntrig];
  TH1F *Dimu_eta_glb[ntrig];
  TH1F *Dimu_pt_glb[ntrig];
  TH1F *Dimu_phi_glb[ntrig];
  TH1F *DimuMCut_mass_glb[ntrig];
  TH1F *DimuPtCut_mass_glb[ntrig];    //pT cut applied to single muons and they form a dimuon
  TH1F *DimuMPtCut_mass_glb[ntrig];    //pT cut applied to single muons and they form a dimuon
  TH1F *Dimu_mass_L2[ntrig];
  TH1F *Dimu_eta_L2[ntrig];
  TH1F *Dimu_pt_L2[ntrig];
  TH1F *Dimu_phi_L2[ntrig];
  TH1F *DimuMCut_mass_L2[ntrig];
  TH1F *DimuPtCut_mass_L2[ntrig];    //pT cut applied to single muons and they form a dimuon
  TH1F *DimuMPtCut_mass_L2[ntrig];    //pT cut applied to single muons and they form a dimuon
  TH1F *Dimu_mass_L3[ntrig];
  TH1F *Dimu_eta_L3[ntrig];
  TH1F *Dimu_pt_L3[ntrig];
  TH1F *Dimu_phi_L3[ntrig];
  TH1F *DimuMCut_mass_L3[ntrig];
  TH1F *DimuPtCut_mass_L3[ntrig];    //pT cut applied to single muons and they form a dimuon
  TH1F *DimuMPtCut_mass_L3[ntrig];    //pT cut applied to single muons and they form a dimuon

  // Leading and sub-leading L1/L2 muon kinematics
  TH2F *Frac_1st_etapt[ntrig];
  TH2F *Frac_2mu_eta[ntrig];
  TH2F *Frac_2mu_pt[ntrig];
  TH2F *Frac_1st_etapt_L2[ntrig];
  TH2F *Frac_2mu_eta_L2[ntrig];
  TH2F *Frac_2mu_pt_L2[ntrig];
  TH2F *Frac_1st_etapt_L3[ntrig];
  TH2F *Frac_2mu_eta_L3[ntrig];
  TH2F *Frac_2mu_pt_L3[ntrig];
  // Leading and sub-leading L1/L2 muon kinematics integrated histograms
  TH2F *Inte_1st_etapt[ntrig];
  TH2F *Inte_2mu_eta[ntrig];
  TH2F *Inte_2mu_pt[ntrig];
  TH2F *Inte_1st_etapt_L2[ntrig];
  TH2F *Inte_2mu_eta_L2[ntrig];
  TH2F *Inte_2mu_pt_L2[ntrig];
  TH2F *Inte_1st_etapt_L3[ntrig];
  TH2F *Inte_2mu_eta_L3[ntrig];
  TH2F *Inte_2mu_pt_L3[ntrig];

  // Dimuon mass, charge
  for (unsigned int i=0; i<ntrig; i++) {
    title = "DimuM_glb_" + trigPath[i];
    Dimu_mass_glb[i] = new TH1F(title.c_str(),title.c_str(),massMax,0,massMax);
    Dimu_mass_glb[i]->GetXaxis()->SetTitle("m_{#mu#mu}(GeV/c^{2})");
    title = "DimuMCut_glb_" + trigPath[i];
    DimuMCut_mass_glb[i] = new TH1F(title.c_str(),title.c_str(),massMax,0,massMax);
    DimuMCut_mass_glb[i]->GetXaxis()->SetTitle("m_{#mu#mu}(GeV/c^{2})");
    title = "DimuPtCut_glb_" + trigPath[i];
    DimuPtCut_mass_glb[i] = new TH1F(title.c_str(),title.c_str(),massMax,0,massMax);
    DimuPtCut_mass_glb[i]->GetXaxis()->SetTitle("m_{#mu#mu}(GeV/c^{2})");
    title = "DimuMPtCut_glb_" + trigPath[i];
    DimuMPtCut_mass_glb[i] = new TH1F(title.c_str(),title.c_str(),massMax,0,massMax);
    DimuMPtCut_mass_glb[i]->GetXaxis()->SetTitle("m_{#mu#mu}(GeV/c^{2})");
    title = "DimuEta_glb_" + trigPath[i];
    Dimu_eta_glb[i] = new TH1F(title.c_str(),title.c_str(),ETA,0,2.4);
    Dimu_eta_glb[i]->GetXaxis()->SetTitle("|#eta|");
    title = "DimuPt_glb_" + trigPath[i];
    Dimu_pt_glb[i] = new TH1F(title.c_str(),title.c_str(),PT,0,20);
    Dimu_pt_glb[i]->GetXaxis()->SetTitle("p_{T}");
    title = "DimuPhi_glb_" + trigPath[i];
    Dimu_phi_glb[i] = new TH1F(title.c_str(),title.c_str(),PHI,-PI,PI);
    Dimu_phi_glb[i]->GetXaxis()->SetTitle("#phi");
    if (readHLT[i] >= 2) {
      title = "DimuM_L2_" + trigPath[i];
      Dimu_mass_L2[i] = new TH1F(title.c_str(),title.c_str(),massMax,0,massMax);
      Dimu_mass_L2[i]->GetXaxis()->SetTitle("m_{#mu#mu}(GeV/c^{2})");
      title = "DimuMCut_L2_" + trigPath[i];
      DimuMCut_mass_L2[i] = new TH1F(title.c_str(),title.c_str(),massMax,0,massMax);
      DimuMCut_mass_L2[i]->GetXaxis()->SetTitle("m_{#mu#mu}(GeV/c^{2})");
      title = "DimuPtCut_L2_" + trigPath[i];
      DimuPtCut_mass_L2[i] = new TH1F(title.c_str(),title.c_str(),massMax,0,massMax);
      DimuPtCut_mass_L2[i]->GetXaxis()->SetTitle("m_{#mu#mu}(GeV/c^{2})");
      title = "DimuMPtCut_L2_" + trigPath[i];
      DimuMPtCut_mass_L2[i] = new TH1F(title.c_str(),title.c_str(),massMax,0,massMax);
      DimuMPtCut_mass_L2[i]->GetXaxis()->SetTitle("m_{#mu#mu}(GeV/c^{2})");
      title = "DimuEta_L2_" + trigPath[i];
      Dimu_eta_L2[i] = new TH1F(title.c_str(),title.c_str(),ETA,0,2.4);
      Dimu_eta_L2[i]->GetXaxis()->SetTitle("|#eta|");
      title = "DimuPt_L2_" + trigPath[i];
      Dimu_pt_L2[i] = new TH1F(title.c_str(),title.c_str(),PT,0,20);
      Dimu_pt_L2[i]->GetXaxis()->SetTitle("p_{T}");
      title = "DimuPhi_L2_" + trigPath[i];
      Dimu_phi_L2[i] = new TH1F(title.c_str(),title.c_str(),PHI,-PI,PI);
      Dimu_phi_L2[i]->GetXaxis()->SetTitle("#phi");
      if (readHLT[i] == 3) {
        title = "DimuM_L3_" + trigPath[i];
        Dimu_mass_L3[i] = new TH1F(title.c_str(),title.c_str(),massMax,0,massMax);
        Dimu_mass_L3[i]->GetXaxis()->SetTitle("m_{#mu#mu}(GeV/c^{2})");
        title = "DimuMCut_L3_" + trigPath[i];
        DimuMCut_mass_L3[i] = new TH1F(title.c_str(),title.c_str(),massMax,0,massMax);
        DimuMCut_mass_L3[i]->GetXaxis()->SetTitle("m_{#mu#mu}(GeV/c^{2})");
        title = "DimuPtCut_L3_" + trigPath[i];
        DimuPtCut_mass_L3[i] = new TH1F(title.c_str(),title.c_str(),massMax,0,massMax);
        DimuPtCut_mass_L3[i]->GetXaxis()->SetTitle("m_{#mu#mu}(GeV/c^{2})");
        title = "DimuMPtCut_L3_" + trigPath[i];
        DimuMPtCut_mass_L3[i] = new TH1F(title.c_str(),title.c_str(),massMax,0,massMax);
        DimuMPtCut_mass_L3[i]->GetXaxis()->SetTitle("m_{#mu#mu}(GeV/c^{2})");
        title = "DimuEta_L3_" + trigPath[i];
        Dimu_eta_L3[i] = new TH1F(title.c_str(),title.c_str(),ETA,0,2.4);
        Dimu_eta_L3[i]->GetXaxis()->SetTitle("|#eta|");
        title = "DimuPt_L3_" + trigPath[i];
        Dimu_pt_L3[i] = new TH1F(title.c_str(),title.c_str(),PT,0,20);
        Dimu_pt_L3[i]->GetXaxis()->SetTitle("p_{T}");
        title = "DimuPhi_L3_" + trigPath[i];
        Dimu_phi_L3[i] = new TH1F(title.c_str(),title.c_str(),PHI,-PI,PI);
        Dimu_phi_L3[i]->GetXaxis()->SetTitle("#phi");
      }
  }

    title = "Frac_1st_etapt_" + trigPath[i];
    Frac_1st_etapt[i] = new TH2F(title.c_str(),title.c_str(),ETA,0,2.4,PT,0,20);
    Frac_1st_etapt[i]->GetXaxis()->SetTitle("Leading |#eta|");
    Frac_1st_etapt[i]->GetYaxis()->SetTitle("Leading p_{T}");
    title = "Frac_2mu_eta_" + trigPath[i];
    Frac_2mu_eta[i] = new TH2F(title.c_str(),title.c_str(),ETA,0,2.4,ETA,0,2.4);
    Frac_2mu_eta[i]->GetXaxis()->SetTitle("Leading |#eta|");
    Frac_2mu_eta[i]->GetYaxis()->SetTitle("Sub-leading |#eta|");
    title = "Frac_2mu_pt_" + trigPath[i];
    Frac_2mu_pt[i] = new TH2F(title.c_str(),title.c_str(),PT,0,20,PT,0,20);
    Frac_2mu_pt[i]->GetXaxis()->SetTitle("Leading p_{T}");
    Frac_2mu_pt[i]->GetYaxis()->SetTitle("Sub-leading p_{T}");

    if (readHLT[i] >= 2) {
      title = "Frac_1st_etapt_L2_" + trigPath[i];
      Frac_1st_etapt_L2[i] = new TH2F(title.c_str(),title.c_str(),ETA,0,2.4,PT,0,20);
      Frac_1st_etapt_L2[i]->GetXaxis()->SetTitle("Leading |#eta|");
      Frac_1st_etapt_L2[i]->GetYaxis()->SetTitle("Leading p_{T}");
      title = "Frac_2mu_eta_L2_" + trigPath[i];
      Frac_2mu_eta_L2[i] = new TH2F(title.c_str(),title.c_str(),ETA,0,2.4,ETA,0,2.4);
      Frac_2mu_eta_L2[i]->GetXaxis()->SetTitle("Leading |#eta|");
      Frac_2mu_eta_L2[i]->GetYaxis()->SetTitle("Sub-leading |#eta|");
      title = "Frac_2mu_pt_L2_" + trigPath[i];
      Frac_2mu_pt_L2[i] = new TH2F(title.c_str(),title.c_str(),PT,0,20,PT,0,20);
      Frac_2mu_pt_L2[i]->GetXaxis()->SetTitle("Leading p_{T}");
      Frac_2mu_pt_L2[i]->GetYaxis()->SetTitle("Sub-leading p_{T}");

      if (readHLT[i] == 3) {
        title = "Frac_1st_etapt_L3_" + trigPath[i];
        Frac_1st_etapt_L3[i] = new TH2F(title.c_str(),title.c_str(),ETA,0,2.4,PT,0,20);
        Frac_1st_etapt_L3[i]->GetXaxis()->SetTitle("Leading |#eta|");
        Frac_1st_etapt_L3[i]->GetYaxis()->SetTitle("Leading p_{T}");
        title = "Frac_2mu_eta_L3_" + trigPath[i];
        Frac_2mu_eta_L3[i] = new TH2F(title.c_str(),title.c_str(),ETA,0,2.4,ETA,0,2.4);
        Frac_2mu_eta_L3[i]->GetXaxis()->SetTitle("Leading |#eta|");
        Frac_2mu_eta_L3[i]->GetYaxis()->SetTitle("Sub-leading |#eta|");
        title = "Frac_2mu_pt_L3_" + trigPath[i];
        Frac_2mu_pt_L3[i] = new TH2F(title.c_str(),title.c_str(),PT,0,20,PT,0,20);
        Frac_2mu_pt_L3[i]->GetXaxis()->SetTitle("Leading p_{T}");
        Frac_2mu_pt_L3[i]->GetYaxis()->SetTitle("Sub-leading p_{T}");
      }
    }

    title = "Inte_1st_etapt_" + trigPath[i];
    Inte_1st_etapt[i] = new TH2F(title.c_str(),title.c_str(),ETA,0,2.4,PT,0,20);
    Inte_1st_etapt[i]->GetXaxis()->SetTitle("Leading |#eta|");
    Inte_1st_etapt[i]->GetYaxis()->SetTitle("Leading p_{T}");
    title = "Inte_2mu_eta_" + trigPath[i];
    Inte_2mu_eta[i] = new TH2F(title.c_str(),title.c_str(),ETA,0,2.4,ETA,0,2.4);
    Inte_2mu_eta[i]->GetXaxis()->SetTitle("Leading |#eta|");
    Inte_2mu_eta[i]->GetYaxis()->SetTitle("Sub-leading |#eta|");
    title = "Inte_2mu_pt_" + trigPath[i];
    Inte_2mu_pt[i] = new TH2F(title.c_str(),title.c_str(),PT,0,20,PT,0,20);
    Inte_2mu_pt[i]->GetXaxis()->SetTitle("Leading p_{T}");
    Inte_2mu_pt[i]->GetYaxis()->SetTitle("Sub-leading p_{T}");

    if (readHLT[i] >= 2) {
      title = "Inte_1st_etapt_L2_" + trigPath[i];
      Inte_1st_etapt_L2[i] = new TH2F(title.c_str(),title.c_str(),ETA,0,2.4,PT,0,20);
      Inte_1st_etapt_L2[i]->GetXaxis()->SetTitle("Leading |#eta|");
      Inte_1st_etapt_L2[i]->GetYaxis()->SetTitle("Leading p_{T}");
      title = "Inte_2mu_eta_L2_" + trigPath[i];
      Inte_2mu_eta_L2[i] = new TH2F(title.c_str(),title.c_str(),ETA,0,2.4,ETA,0,2.4);
      Inte_2mu_eta_L2[i]->GetXaxis()->SetTitle("Leading |#eta|");
      Inte_2mu_eta_L2[i]->GetYaxis()->SetTitle("Sub-leading |#eta|");
      title = "Inte_2mu_pt_L2_" + trigPath[i];
      Inte_2mu_pt_L2[i] = new TH2F(title.c_str(),title.c_str(),PT,0,20,PT,0,20);
      Inte_2mu_pt_L2[i]->GetXaxis()->SetTitle("Leading p_{T}");
      Inte_2mu_pt_L2[i]->GetYaxis()->SetTitle("Sub-leading p_{T}");

      if (readHLT[i] == 3) {
        title = "Inte_1st_etapt_L3_" + trigPath[i];
        Inte_1st_etapt_L3[i] = new TH2F(title.c_str(),title.c_str(),ETA,0,2.4,PT,0,20);
        Inte_1st_etapt_L3[i]->GetXaxis()->SetTitle("Leading |#eta|");
        Inte_1st_etapt_L3[i]->GetYaxis()->SetTitle("Leading p_{T}");
        title = "Inte_2mu_eta_L3_" + trigPath[i];
        Inte_2mu_eta_L3[i] = new TH2F(title.c_str(),title.c_str(),ETA,0,2.4,ETA,0,2.4);
        Inte_2mu_eta_L3[i]->GetXaxis()->SetTitle("Leading |#eta|");
        Inte_2mu_eta_L3[i]->GetYaxis()->SetTitle("Sub-leading |#eta|");
        title = "Inte_2mu_pt_L3_" + trigPath[i];
        Inte_2mu_pt_L3[i] = new TH2F(title.c_str(),title.c_str(),PT,0,20,PT,0,20);
        Inte_2mu_pt_L3[i]->GetXaxis()->SetTitle("Leading p_{T}");
        Inte_2mu_pt_L3[i]->GetYaxis()->SetTitle("Sub-leading p_{T}");
      }

    }
  }


  ////////// Read input file
  cout << "1" << endl;
  HltTree       ohTree_(fnoh,true);
  HltTree       &ohTree = ohTree_;
  TTree *tree;
  FriendMuTree  muTree_(fnMu,true);
  cout << "2" << endl;
  if (!muTree_.fChain->GetCurrentFile() || !ohTree.fChain->GetCurrentFile()) {
    cout << "Failed to open root files\n"; return -1;
  }

  TTree *mutree;
  MUTREE muTree;
  mutree = muTree_.fChain;
  mutree->SetBranchAddress("Run",&muTree.run);
  mutree->SetBranchAddress("Event",&muTree.event);
  if (flag.doGen && !flag.doSta && !flag.doGlb) {
   mutree->SetBranchAddress("Gen_eta",muTree.eta);
   mutree->SetBranchAddress("Gen_pt",muTree.pt);
   mutree->SetBranchAddress("Gen_phi",muTree.phi);
   mutree->SetBranchAddress("Gen_nptl",&muTree.nptl);
   mutree->SetBranchAddress("Gen_pid",muTree.charge);
   mutree->SetBranchAddress("Gen_mom",muTree.mom);
   mutree->SetBranchAddress("Gen_status",muTree.status);
  } else if (flag.doSta && !flag.doGen && !flag.doGlb) {
   mutree->SetBranchAddress("Sta_eta",muTree.eta);
   mutree->SetBranchAddress("Sta_pt",muTree.pt);
   mutree->SetBranchAddress("Sta_phi",muTree.phi);
   mutree->SetBranchAddress("Sta_nptl",&muTree.nptl);
   mutree->SetBranchAddress("Sta_charge",muTree.charge);
  } else if (flag.doGlb && !flag.doGen && !flag.doSta) {
   mutree->SetBranchAddress("Glb_eta",muTree.eta);
   mutree->SetBranchAddress("Glb_pt",muTree.pt);
   mutree->SetBranchAddress("Glb_phi",muTree.phi);
   mutree->SetBranchAddress("Glb_nptl",&muTree.nptl);
   mutree->SetBranchAddress("Glb_charge",muTree.charge);
  } else {
    cout << "Choose doSta or doGlb or doGen!\n";
    return -1;
  }


  INFO info_;
  INFO &info = info_;

  for (unsigned int i=0; i<ntrig; i++) {
    tree = ohTree.fChain;
    tree->SetBranchAddress(trigPath[i].c_str(),&trig[i]);
  }


  for (int i=0; i<ohTree.fChain->GetEntries(); i++) {
    if (i%1000 == 0) cout << "processing entry: " << i << endl;
    mutree->GetEntry(i);
    ohTree.GetEntry(i);
    tree->GetEntry(i);

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

//    cout << "Run: " << ohTree.Run << "\tEvent: " << ohTree.Event << endl;
  
    ////////// Get information of muon objects in gen, L1, L2 levels
    info.tot_NL1Mu += ohTree.NL1Mu;
    info.tot_NohMuL2 += ohTree.NohMuL2;
    info.tot_NohMuL3 += ohTree.NohMuL3;
    if (ohTree.NL1Mu > 0 ) info.tot_NL1ValidEvt ++;
    if (ohTree.NohMuL2 > 0) info.tot_NL2ValidEvt ++;
    if (ohTree.NohMuL3 > 0) info.tot_NL3ValidEvt ++;

    for (unsigned int idx=0; idx<ntrig; idx++) {
      if (trig[idx]) {
        Trig_fired[idx]++;    //Trigger fired
/*        // |y| < 2.1
        int nFired=0;
        if (readHLT[idx] == 1) {
          for (int a=0; a<ohTree.NL1Mu; a++) {
            if (fabs(ohTree.L1MuEta[a]) < 2.1) nFired++;
          }
          if (nFired > 1) Trig_fired[idx]++;    //Trigger fired
        } else if (readHLT[idx] == 2){
          for (int a=0; a<ohTree.NohMuL2; a++) {
            if (fabs(ohTree.ohMuL2Eta[a]) < 2.1) nFired++;
          }
          if (nFired > 1) Trig_fired[idx]++;    //Trigger fired
        } else if (readHLT[idx] == 3) {
          for (int a=0; a<ohTree.NohMuL3; a++) {
            if (fabs(ohTree.ohMuL3Eta[a]) < 2.1)  nFired++;
          }
          if (nFired > 1) Trig_fired[idx]++;    //Trigger fired
        }

        // |p_T| > 1
        int nFired=0;
        if (readHLT[idx] == 1) {
          for (int a=0; a<ohTree.NL1Mu; a++) {
            if (ohTree.L1MuPt[a] > 1) nFired++;
          }
          if (nFired > 1) Trig_fired[idx]++;    //Trigger fired
        } else if (readHLT[idx] == 2){
          for (int a=0; a<ohTree.NohMuL2; a++) {
            if (ohTree.ohMuL2Pt[a] > 1) nFired++;
          }
          if (nFired > 1) Trig_fired[idx]++;    //Trigger fired
        } else if (readHLT[idx] == 3) {
          for (int a=0; a<ohTree.NohMuL3; a++) {
            if (ohTree.ohMuL3Pt[a] > 1)  nFired++;
          }
          if (nFired > 1) Trig_fired[idx]++;    //Trigger fired
        }*/
        

        ////////// Global di-muon counting
        if (muTree.nptl >= 2) {
          map<float,int,ptcomp> l2;
          map<float,int>::iterator it;

          for (int a=0; a<muTree.nptl; a++) {
            float pt = muTree.pt[a];
            l2[pt] = a;
          }

          it = l2.begin();
          int a[2] ={0};
          a[0] = it->second; //Get 1st index in a ohTree
          it++;
          a[1] = it->second; //Get 2nd index in a ohTree
          
          if (muTree.charge[a[0]]*muTree.charge[a[1]] < 0) {  //only opposite muon pairs will be considered
            TLorentzVector L2mu1, L2mu2, L2dimu;
            L2mu1.SetPtEtaPhiM(muTree.pt[a[0]],muTree.eta[a[0]],muTree.phi[a[0]],Mmu);
            L2mu2.SetPtEtaPhiM(muTree.pt[a[1]],muTree.eta[a[1]],muTree.phi[a[1]],Mmu);

            L2dimu = L2mu1 + L2mu2; // Use only 0th, 1th L1 objects
            Dimu_mass_glb[idx]->Fill(L2dimu.M());
            Dimu_eta_glb[idx]->Fill(L2dimu.Eta());
            Dimu_pt_glb[idx]->Fill(L2dimu.Pt());
            Dimu_phi_glb[idx]->Fill(L2dimu.Phi());
            if (flag.doSinglemuPtCut && (L2mu1.Pt() > flag.pTCut && L2mu2.Pt() > flag.pTCut)) {
              DimuPtCut_mass_glb[idx]->Fill(L2dimu.M());
            }
            if (flag.doDimuMassCut && (L2dimu.M() > flag.mCut)) {
              DimuMCut_mass_glb[idx]->Fill(L2dimu.M());
            }
            if (flag.doDimuMassCut && flag.doSinglemuPtCut) { 
              if ((L2dimu.M() > flag.mCut) && (L2mu1.Pt() > flag.pTCut && L2mu2.Pt() > flag.pTCut)) {
                  DimuMPtCut_mass_glb[idx]->Fill(L2dimu.M());
              }
            }
          }
        }


        ////////// online di-muon counting
        if (readHLT[idx] >= 2) {
          map<float,int,ptcomp> l2, l2_eta;
          map<float,int>::iterator it;

          for (int a=0; a<ohTree.NohMuL2; a++) {
            float pt = ohTree.ohMuL2Pt[a];
            l2[pt] = a;
          }
          for (int a=0; a<ohTree.NohMuL2; a++) {
            float eta = fabs(ohTree.ohMuL2Eta[a]);
            l2_eta[eta] = a;
          }

          it = l2.begin();
          int a[2] ={0};
          a[0] = it->second; //Get 1st index in a ohTree
          if (!l2.empty())
            Frac_1st_etapt_L2[idx]->Fill(fabs(ohTree.ohMuL2Eta[a[0]]),ohTree.ohMuL2Pt[a[0]]);

          // Get 2nd element
          if (l2.size()>=2) {
            it++;
            a[1] = it->second; //Get 2nd index in a ohTree
            
            // p_T order
            Frac_2mu_pt_L2[idx]->Fill(ohTree.ohMuL2Pt[a[0]],ohTree.ohMuL2Pt[a[1]]);
            Frac_2mu_eta_L2[idx]->Fill(fabs(ohTree.ohMuL2Eta[a[0]]),fabs(ohTree.ohMuL2Eta[a[1]]));

            if (muTree.charge[a[0]]*muTree.charge[a[1]] < 0) {  //only opposite muon pairs will be considered
              TLorentzVector L2mu1, L2mu2, L2dimu;
              L2mu1.SetPtEtaPhiM(ohTree.ohMuL2Pt[a[0]],ohTree.ohMuL2Eta[a[0]],ohTree.ohMuL2Phi[a[0]],Mmu);
              L2mu2.SetPtEtaPhiM(ohTree.ohMuL2Pt[a[1]],ohTree.ohMuL2Eta[a[1]],ohTree.ohMuL2Phi[a[1]],Mmu);

              L2dimu = L2mu1 + L2mu2; // Use only 0th, 1th L1 objects
              Dimu_mass_L2[idx]->Fill(L2dimu.M());
              Dimu_eta_L2[idx]->Fill(L2dimu.Eta());
              Dimu_pt_L2[idx]->Fill(L2dimu.Pt());
              Dimu_phi_L2[idx]->Fill(L2dimu.Phi());
              if (flag.doSinglemuPtCut && (L2mu1.Pt() > flag.pTCut && L2mu2.Pt() > flag.pTCut) ) {
                  DimuPtCut_mass_L2[idx]->Fill(L2dimu.M());
              }
              if (flag.doDimuMassCut && L2dimu.M() > flag.mCut) {
                  DimuMCut_mass_L2[idx]->Fill(L2dimu.M());
              }
              if (flag.doDimuMassCut && flag.doSinglemuPtCut) {
                if ((L2dimu.M() > flag.mCut) && (L2mu1.Pt() > flag.pTCut && L2mu2.Pt() > flag.pTCut) ) {
                    DimuMPtCut_mass_L2[idx]->Fill(L2dimu.M());
                }
              }
            }
          }

/*          if (l2_eta.size()>=2) {
            //y order
            it = l2_eta.begin();
            a[0] = it->second;
            it++;
            a[1] = it->second;
            Frac_2mu_eta_L2[idx]->Fill(fabs(ohTree.ohMuL2Eta[a[0]]),fabs(ohTree.ohMuL2Eta[a[1]]));
          }*/
        
          if (readHLT[idx] == 3) {
            map<float,int,ptcomp> l3, l3_eta;

            for (int b=0; b<ohTree.NohMuL3; b++) {
              float pt = ohTree.ohMuL3Pt[b];
              l3[pt] = b;
            }
            for (int b=0; b<ohTree.NohMuL3; b++) {
              float eta = fabs(ohTree.ohMuL3Eta[b]);
              l3_eta[eta] = b;
            }

            it = l3.begin();
            int b[2];
            b[0] = it->second; //Get 1st index in a ohTree
            if (!l3.empty())
              Frac_1st_etapt_L3[idx]->Fill(fabs(ohTree.ohMuL3Eta[b[0]]),ohTree.ohMuL3Pt[b[0]]);

            // Get 2nd element
            if (l3.size()>=2) {
              it++;
              b[1] = it->second; //Get 2nd index in a ohTree
              
              Frac_2mu_pt_L3[idx]->Fill(ohTree.ohMuL3Pt[b[0]],ohTree.ohMuL3Pt[b[1]]);
              Frac_2mu_eta_L3[idx]->Fill(fabs(ohTree.ohMuL3Eta[b[0]]),fabs(ohTree.ohMuL3Eta[b[1]]));

              if (muTree.charge[b[0]]*muTree.charge[b[1]] < 0) {  //only opposite muon pairs will be considered
                TLorentzVector L3mu1, L3mu2, L3dimu;
                L3mu1.SetPtEtaPhiM(ohTree.ohMuL3Pt[b[0]],ohTree.ohMuL3Eta[b[0]],ohTree.ohMuL3Phi[b[0]],Mmu);
                L3mu2.SetPtEtaPhiM(ohTree.ohMuL3Pt[b[1]],ohTree.ohMuL3Eta[b[1]],ohTree.ohMuL3Phi[b[1]],Mmu);

                L3dimu = L3mu1 + L3mu2; // Use only 0th, 1th L1 objects
                Dimu_mass_L3[idx]->Fill(L3dimu.M());
                Dimu_eta_L3[idx]->Fill(L3dimu.Eta());
                Dimu_pt_L3[idx]->Fill(L3dimu.Pt());
                Dimu_phi_L3[idx]->Fill(L3dimu.Phi());
                if (flag.doSinglemuPtCut && (L3mu1.Pt() > flag.pTCut && L3mu2.Pt() > flag.pTCut) ) {
                    DimuPtCut_mass_L3[idx]->Fill(L3dimu.M());
                }
                if (flag.doDimuMassCut && L3dimu.M() > flag.mCut) {
                    DimuMCut_mass_L3[idx]->Fill(L3dimu.M());
                }
                if (flag.doDimuMassCut && flag.doSinglemuPtCut) {
                  if ( (L3dimu.M() > flag.mCut) && (L3mu1.Pt() > flag.pTCut && L3mu2.Pt() > flag.pTCut) ) {
                      DimuMPtCut_mass_L3[idx]->Fill(L3dimu.M());
                  }
                }
              }
            }

/*            if (l3.size()>=2) {
              it = l3_eta.begin();
              b[0] = it->second;
              it++;
              b[1] = it->second;
              Frac_2mu_eta_L3[idx]->Fill(fabs(ohTree.ohMuL3Eta[b[0]]),fabs(ohTree.ohMuL3Eta[b[1]]));
            }*/

          } //end of readHLT == 3

        }


        // Get L1 info
        map<float,int,ptcomp> l1, l1_eta;
        map<float,int>::iterator it;

        for (int b=0; b<ohTree.NL1Mu; b++) {
          if (ohTree.L1MuEta[b] == -999) continue;    //Invalid L1 muon
          float pt = ohTree.L1MuPt[b];
          l1[pt] = b;
        }
        for (int b=0; b<ohTree.NL1Mu; b++) {
          if (ohTree.L1MuEta[b] == -999) continue;    //Invalid L1 muon
          float eta = fabs(ohTree.L1MuEta[b]);
          l1_eta[eta] = b;
        }

        it = l1.begin();
        int a[2];
        a[0] = it->second; //Get 1st index in a ohTree
        if (!l1.empty())
          Frac_1st_etapt[idx]->Fill(fabs(ohTree.L1MuEta[a[0]]),ohTree.L1MuPt[a[0]]);

        if (l1.size()>=2) {
          it++;
          a[1] = it->second; //Get 2nd index in a ohTree
          
          //1st and 2nd elements are filled
          Frac_2mu_pt[idx]->Fill(ohTree.L1MuPt[a[0]],ohTree.L1MuPt[a[1]]);
          Frac_2mu_eta[idx]->Fill(fabs(ohTree.L1MuEta[a[0]]),fabs(ohTree.L1MuEta[a[1]]));
        }
/*        if (l1_eta.size()>=2) {
          it = l1_eta.begin();
          a[0] = it->second;
          it++;
          a[1] = it->second; //Get 2nd index in a ohTree
          Frac_2mu_eta[idx]->Fill(fabs(ohTree.L1MuEta[a[0]]),fabs(ohTree.L1MuEta[a[1]]));
        }*/

      } //End of a trig
    } //End of trig loop
     
  } //End of reading 1entry in a tree


  ////////// Prints out how many triggers are fired
  TH1D *ph  = new TH1D("ph","",1100,0,1100);
  ohTree.fChain->Draw("LumiBlock>>ph");
  TH1D *phLumi = (TH1D*)gDirectory->Get("ph");

  cout << " # entries: " << ohTree.fChain->GetEntries() << endl;
  for (unsigned int idx=0; idx<ntrig; idx++) {
    cout << trigPath[idx] << "\t" << Trig_fired[idx] << "\t"
         << (float)Trig_fired[idx]/phLumi->GetNbinsX()/23 << endl;    //Trigger fired
  }


  for (unsigned int i=0; i<ntrig; i++) {
    Frac_1st_etapt[i]->Scale((float)100/Frac_1st_etapt[i]->GetEntries());
    Frac_2mu_eta[i]->Scale((float)100/Frac_2mu_eta[i]->GetEntries());
    Frac_2mu_pt[i]->Scale((float)100/Frac_2mu_pt[i]->GetEntries());
    if (readHLT[i] >= 2) {
      Frac_1st_etapt_L2[i]->Scale((float)100/Frac_1st_etapt_L2[i]->GetEntries());
      Frac_2mu_eta_L2[i]->Scale((float)100/Frac_2mu_eta_L2[i]->GetEntries());
      Frac_2mu_pt_L2[i]->Scale((float)100/Frac_2mu_pt_L2[i]->GetEntries());
      if (readHLT[i] == 3) {
        Frac_1st_etapt_L3[i]->Scale((float)100/Frac_1st_etapt_L3[i]->GetEntries());
        Frac_2mu_eta_L3[i]->Scale((float)100/Frac_2mu_eta_L3[i]->GetEntries());
        Frac_2mu_pt_L3[i]->Scale((float)100/Frac_2mu_pt_L3[i]->GetEntries());
      }
    }

    ////////// Integrated histos
    const int nXBins = Frac_1st_etapt[i]->GetNbinsX();
    const int nYBins = Frac_1st_etapt[i]->GetNbinsY();

    float overflow[9][20] = {{0}};
    for (int bin = (nYBins+2)*(nXBins+2)-2; bin>(nYBins+1)*(nXBins+2); bin--) {
      int x_, y_, z_;
      int &x = x_;
      int &y = y_;
      int &z = z_;
      Frac_1st_etapt[i]->GetBinXYZ(bin,x,y,z);
      overflow[0][x] = overflow[0][x+1]+Frac_1st_etapt[i]->GetBinContent(bin);
      overflow[1][x] = overflow[1][x+1]+Frac_2mu_eta[i]->GetBinContent(bin);
      overflow[2][x] = overflow[2][x+1]+Frac_2mu_pt[i]->GetBinContent(bin);
      if (readHLT[i] >= 2) {
        overflow[3][x] = overflow[3][x+1]+Frac_1st_etapt_L2[i]->GetBinContent(bin);
        overflow[4][x] = overflow[4][x+1]+Frac_2mu_eta_L2[i]->GetBinContent(bin);
        overflow[5][x] = overflow[5][x+1]+Frac_2mu_pt_L2[i]->GetBinContent(bin);
        if (readHLT[i] == 3) {
          overflow[6][x] = overflow[6][x+1]+Frac_1st_etapt_L3[i]->GetBinContent(bin);
          overflow[7][x] = overflow[7][x+1]+Frac_2mu_eta_L3[i]->GetBinContent(bin);
          overflow[8][x] = overflow[8][x+1]+Frac_2mu_pt_L3[i]->GetBinContent(bin);
        }
      }
  /*    overflow[0][x] = overflow[0][x+1]+Frac_1st_HLT_HIL1DoubleMuOpen_etapt->GetBinContent(bin);
      overflow[1][x] = overflow[1][x+1]+Frac_2mu_HLT_HIL1DoubleMuOpen_eta->GetBinContent(bin);
      overflow[2][x] = overflow[2][x+1]+Frac_2mu_HLT_HIL1DoubleMuOpen_pt->GetBinContent(bin);
      overflow[3][x] = overflow[3][x+1]+Frac_1st_HLT_HIL2DoubleMu0_etapt->GetBinContent(bin);
      overflow[4][x] = overflow[4][x+1]+Frac_2mu_HLT_HIL2DoubleMu0_eta->GetBinContent(bin);
      overflow[5][x] = overflow[5][x+1]+Frac_2mu_HLT_HIL2DoubleMu0_pt->GetBinContent(bin);
      cout << x << endl;
      cout <<  "0 overflow x-bins: " << bin << "\t" << overflow[0][x] << endl;
      cout <<  "1 overflow x-bins: " << bin << "\t" << overflow[1][x] << endl;
      cout <<  "2 overflow x-bins: " << bin << "\t" << overflow[2][x] << endl;
      cout <<  "3 overflow x-bins: " << bin << "\t" << overflow[3][x] << endl;
      cout <<  "4 overflow x-bins: " << bin << "\t" << overflow[4][x] << endl;
      cout <<  "5 overflow x-bins: " << bin << "\t" << overflow[5][x] << endl;*/
    }

    // X-axis: from pT highest(top), Y-axis: from eta highest(right)
    for (int a=nYBins; a>0 ; a--) {
      for (int b=1; b<=nXBins; b++) {
        //Get current bin content (2 more bins are underflow and overflow)
        const int numbin = (a+1)*(nXBins+2)-(b+1);
        int xc_, yc_, zc_;
        int &xc = xc_;
        int &yc = yc_;
        int &zc = zc_;
        Frac_1st_etapt[i]->GetBinXYZ(numbin,xc,yc,zc);

        float bincont[9] ={0};
  /*      bincont[0] = Frac_1st_HLT_HIL1DoubleMuOpen_etapt->GetBinContent(numbin);
        bincont[1] = Frac_2mu_HLT_HIL1DoubleMuOpen_eta->GetBinContent(numbin);
        bincont[2] = Frac_2mu_HLT_HIL1DoubleMuOpen_pt->GetBinContent(numbin);
        bincont[3] = Frac_1st_HLT_HIL2DoubleMu0_etapt->GetBinContent(numbin);
        bincont[4] = Frac_2mu_HLT_HIL2DoubleMu0_eta->GetBinContent(numbin);
        bincont[5] = Frac_2mu_HLT_HIL2DoubleMu0_pt->GetBinContent(numbin);
        cout << "0 current: " << numbin << "\t" << bincont[0] << endl;
        cout << "1 current: " << numbin << "\t" << bincont[1] << endl;
        cout << "2 current: " << numbin << "\t" << bincont[2] << endl;
        cout << "3 current: " << numbin << "\t" << bincont[3] << endl;
        cout << "4 current: " << numbin << "\t" << bincont[4] << endl;
        cout << "5 current: " << numbin << "\t" << bincont[5] << endl;*/

        //(sum up all previous x-axis bin contents) + (take previous y-axis bin content) with current bin
        float prevcont[9] = {0};
        for (int bin = (nYBins+1)*(nXBins+2) ; bin >= numbin ; bin--) {
          int x_, y_, z_;
          int &x = x_;
          int &y = y_;
          int &z = z_;
          Frac_1st_etapt[i]->GetBinXYZ(bin,x,y,z);
          if (x >= xc ) {
            prevcont[0] += Frac_1st_etapt[i]->GetBinContent(bin);
            prevcont[1] += Frac_2mu_eta[i]->GetBinContent(bin);
            prevcont[2] += Frac_2mu_pt[i]->GetBinContent(bin);
            if (readHLT[i] >= 2) {
              prevcont[3] += Frac_1st_etapt_L2[i]->GetBinContent(bin);
              prevcont[4] += Frac_2mu_eta_L2[i]->GetBinContent(bin);
              prevcont[5] += Frac_2mu_pt_L2[i]->GetBinContent(bin);
              if (readHLT[i] == 3) {
                prevcont[6] += Frac_1st_etapt_L3[i]->GetBinContent(bin);
                prevcont[7] += Frac_2mu_eta_L3[i]->GetBinContent(bin);
                prevcont[8] += Frac_2mu_pt_L3[i]->GetBinContent(bin);
              }
            }
  /*          cout <<  "0 prev frac bins: " << bin << "\t" << prevcont[0] << endl;
            cout <<  "1 prev frac bins: " << bin << "\t" << prevcont[1] << endl;
            cout <<  "2 prev frac bins: " << bin << "\t" << prevcont[2] << endl;
            cout <<  "3 prev frac bins: " << bin << "\t" << prevcont[3] << endl;
            cout <<  "4 prev frac bins: " << bin << "\t" << prevcont[4] << endl;
            cout <<  "5 prev frac bins: " << bin << "\t" << prevcont[5] << endl;*/
          }
        }
        for (int c=0; c<9; c++) {
          int x_, y_, z_;
          int &x = x_;
          int &y = y_;
          int &z = z_;
          Frac_1st_etapt[i]->GetBinXYZ(numbin,x,y,z);
          bincont[c] = prevcont[c] + overflow[c][x];
        }

  /*      cout << "0 inte: " << numbin << "\t" << bincont[0] << endl;
        cout << "1 inte: " << numbin << "\t" << bincont[1] << endl;
        cout << "2 inte: " << numbin << "\t" << bincont[2] << endl;
        cout << "3 inte: " << numbin << "\t" << bincont[3] << endl;
        cout << "4 inte: " << numbin << "\t" << bincont[4] << endl;
        cout << "5 inte: " << numbin << "\t" << bincont[5] << endl;*/
        
        Inte_1st_etapt[i]->SetBinContent(numbin,bincont[0]);
        Inte_2mu_eta[i]->SetBinContent(numbin,bincont[1]);
        Inte_2mu_pt[i]->SetBinContent(numbin,bincont[2]);
        if (readHLT[i] >= 2) {
          Inte_1st_etapt_L2[i]->SetBinContent(numbin,bincont[3]);
          Inte_2mu_eta_L2[i]->SetBinContent(numbin,bincont[4]);
          Inte_2mu_pt_L2[i]->SetBinContent(numbin,bincont[5]);
          if (readHLT[i] == 3) {
            Inte_1st_etapt_L3[i]->SetBinContent(numbin,bincont[6]);
            Inte_2mu_eta_L3[i]->SetBinContent(numbin,bincont[7]);
            Inte_2mu_pt_L3[i]->SetBinContent(numbin,bincont[8]);
          }
        }
      }//End of x-axis bin loop
    }//End of y-axis bin loop
  }//End of trigger path loop




  ////////// Get trigger rates for each trigger path (23 sec for 1 lumiblock)
  gROOT->SetStyle("Plain");
  gStyle->SetPaintTextFormat(".0f");
  gStyle->SetPalette(1);
  stringstream stmp;
  TLatex *t = new TLatex(); t->SetNDC(kTRUE);

  for (unsigned int i=0; i<ntrig; i++) {
    TCanvas *cl2dimu = new TCanvas("dimuL2","dimuL2",1300,1000);
    cl2dimu->Divide(2,2);
    cl2dimu->cd(1);
    Dimu_mass_glb[i]->GetYaxis()->SetRangeUser(0,150);
    Dimu_mass_glb[i]->Draw();
    if (flag.doDimuMassCut) {
      DimuMCut_mass_glb[i]->SetFillColor(kRed);
      DimuMCut_mass_glb[i]->SetFillStyle(3345);
      DimuMCut_mass_glb[i]->Draw("same");
    }
    if (flag.doSinglemuPtCut) {
      DimuPtCut_mass_glb[i]->SetFillColor(kBlue);
      DimuPtCut_mass_glb[i]->SetFillStyle(3354);
      DimuPtCut_mass_glb[i]->Draw("same");
    }
    if (flag.doSinglemuPtCut && flag.doDimuMassCut) {
      DimuMPtCut_mass_glb[i]->SetFillColor(kGreen);
      DimuMPtCut_mass_glb[i]->SetFillStyle(3305);
      DimuMPtCut_mass_glb[i]->Draw("same");
    }
    cl2dimu->cd(2);   Dimu_eta_glb[i]->Draw();
    cl2dimu->cd(3);   Dimu_pt_glb[i]->Draw();
    cl2dimu->cd(4);
    stmp.str("");  stmp << "Events: " << ohTree.fChain->GetEntries();
    t->DrawLatex(0.0,0.9,stmp.str().c_str());
    stmp.str("");  stmp << "Total # of triggered events: " << Trig_fired[i];
    t->DrawLatex(0.0,0.85,stmp.str().c_str());
    stmp.str("");  stmp << "Total # of glb dimuons: " << Dimu_mass_glb[i]->GetEntries();
    t->DrawLatex(0.0,0.8,stmp.str().c_str());
    stmp.str("");  stmp << "Trigger path: " << trigPath[i];
    t->DrawLatex(0.0,0.75,stmp.str().c_str());
    if (flag.doDimuMassCut && !flag.doSinglemuPtCut) {
      stmp.str("");  stmp << "Total # of glb dimuons w/ dimuon mass cut: " << DimuMCut_mass_glb[i]->GetEntries();
      t->DrawLatex(0.0,0.7,stmp.str().c_str());
      stmp.str("");  stmp << "Mass cut on glb dimuons (Red): " << flag.mCut << " GeV/c^{2}";
      t->DrawLatex(0.0,0.65,stmp.str().c_str());
    }
    if (flag.doSinglemuPtCut && !flag.doDimuMassCut) {
      stmp.str("");  stmp << "Total # of glb dimuons w/ single mu pT cut: " << DimuPtCut_mass_glb[i]->GetEntries();
      t->DrawLatex(0.0,0.7,stmp.str().c_str());
      stmp.str("");  stmp << "pT cut on a glb muon (Blue): " << flag.pTCut << " GeV/c";
      t->DrawLatex(0.0,0.65,stmp.str().c_str());
    }
    if (flag.doSinglemuPtCut && flag.doDimuMassCut) {
      stmp.str("");  stmp << "Total # of glb dimuons w/ dimuon mass cut (Red): " << DimuMCut_mass_glb[i]->GetEntries();
      t->DrawLatex(0.0,0.7,stmp.str().c_str());
      stmp.str("");  stmp << "Total # of glb dimuons w/ single mu pT cut (Blue): " << DimuPtCut_mass_glb[i]->GetEntries();
      t->DrawLatex(0.0,0.65,stmp.str().c_str());
      stmp.str("");  stmp << "Total # of glb dimuons w/ dimu mass" ;
      t->DrawLatex(0.0,0.6,stmp.str().c_str());
      stmp.str("");  stmp << "\t& single mu pT cut (Green): " << DimuMPtCut_mass_glb[i]->GetEntries();
      t->DrawLatex(0.0,0.55,stmp.str().c_str());
      stmp.str("");  stmp << "Mass cut on glb dimuons : " << flag.mCut << " GeV/c^{2}";
      t->DrawLatex(0.0,0.5,stmp.str().c_str());
      stmp.str("");  stmp << "pT cut on a glb muon : " << flag.pTCut << " GeV/c";
      t->DrawLatex(0.0,0.45,stmp.str().c_str());
    }
    title = "DimuHist_glb_" + trigPath[i] + ".png";
    cl2dimu->SaveAs(title.c_str());
    delete cl2dimu;

    if (readHLT[i] >= 2) {
      cl2dimu = new TCanvas("dimuL2","dimuL2",1300,1000);
      cl2dimu->Divide(2,2);
      cl2dimu->cd(1);
      Dimu_mass_L2[i]->GetYaxis()->SetRangeUser(0,150);
      Dimu_mass_L2[i]->Draw();
      if (flag.doDimuMassCut) {
        DimuMCut_mass_L2[i]->SetFillColor(kRed);
        DimuMCut_mass_L2[i]->SetFillStyle(3345);
        DimuMCut_mass_L2[i]->Draw("same");
      }
      if (flag.doSinglemuPtCut) {
        DimuPtCut_mass_L2[i]->SetFillColor(kBlue);
        DimuPtCut_mass_L2[i]->SetFillStyle(3354);
        DimuPtCut_mass_L2[i]->Draw("same");
      }
      if (flag.doSinglemuPtCut && flag.doDimuMassCut) {
        DimuMPtCut_mass_L2[i]->SetFillColor(kGreen);
        DimuMPtCut_mass_L2[i]->SetFillStyle(3305);
        DimuMPtCut_mass_L2[i]->Draw("same");
      }
      cl2dimu->cd(2);   Dimu_eta_L2[i]->Draw();
      cl2dimu->cd(3);   Dimu_pt_L2[i]->Draw();
      cl2dimu->cd(4);
      stmp.str("");  stmp << "Events: " << ohTree.fChain->GetEntries();
      t->DrawLatex(0.0,0.9,stmp.str().c_str());
      stmp.str("");  stmp << "Total # of L2 events: " << info.tot_NL2ValidEvt;
      t->DrawLatex(0.0,0.85,stmp.str().c_str());
      stmp.str("");  stmp << "Total # of L2 dimuons: " << Dimu_mass_L2[i]->GetEntries();
      t->DrawLatex(0.0,0.8,stmp.str().c_str());
      stmp.str("");  stmp << "Trigger path: " << trigPath[i];
      t->DrawLatex(0.0,0.75,stmp.str().c_str());
      if (flag.doDimuMassCut && !flag.doSinglemuPtCut) {
        stmp.str("");  stmp << "Total # of L2 dimuons w/ dimuon mass cut: " << DimuMCut_mass_L2[i]->GetEntries();
        t->DrawLatex(0.0,0.7,stmp.str().c_str());
        stmp.str("");  stmp << "Mass cut on L2 dimuons (Red): " << flag.mCut << " GeV/c^{2}";
        t->DrawLatex(0.0,0.65,stmp.str().c_str());
      }
      if (flag.doSinglemuPtCut && !flag.doDimuMassCut) {
        stmp.str("");  stmp << "Total # of L2 dimuons w/ single mu pT cut: " << DimuPtCut_mass_L2[i]->GetEntries();
        t->DrawLatex(0.0,0.7,stmp.str().c_str());
        stmp.str("");  stmp << "pT cut on a L2 muon (Blue): " << flag.pTCut << " GeV/c";
        t->DrawLatex(0.0,0.65,stmp.str().c_str());
      }
      if (flag.doSinglemuPtCut && flag.doDimuMassCut) {
        stmp.str("");  stmp << "Total # of L2 dimuons w/ dimuon mass cut (Red): " << DimuMCut_mass_L2[i]->GetEntries();
        t->DrawLatex(0.0,0.7,stmp.str().c_str());
        stmp.str("");  stmp << "Total # of L2 dimuons w/ single mu pT cut (Blue): " << DimuPtCut_mass_L2[i]->GetEntries();
        t->DrawLatex(0.0,0.65,stmp.str().c_str());
        stmp.str("");  stmp << "Total # of L2 dimuons w/ dimu mass" ;
        t->DrawLatex(0.0,0.6,stmp.str().c_str());
        stmp.str("");  stmp << "      & single mu pT cut (Green): " << DimuMPtCut_mass_L2[i]->GetEntries();
        t->DrawLatex(0.0,0.55,stmp.str().c_str());
        stmp.str("");  stmp << "Mass cut on L2 dimuons: " << flag.mCut << " GeV/c^{2}";
        t->DrawLatex(0.0,0.5,stmp.str().c_str());
        stmp.str("");  stmp << "pT cut on a L2 muon: " << flag.pTCut << " GeV/c";
        t->DrawLatex(0.0,0.45,stmp.str().c_str());
      }
      title = "DimuHist_L2_" + trigPath[i] + ".png";
      cl2dimu->SaveAs(title.c_str());
      delete cl2dimu;
      if (readHLT[i] == 3) {
        cl2dimu = new TCanvas("dimuL2","dimuL2",1300,1000);
        cl2dimu->Divide(2,2);
        cl2dimu->cd(1);
        Dimu_mass_L3[i]->GetYaxis()->SetRangeUser(0,150);
        Dimu_mass_L3[i]->Draw();
        if (flag.doDimuMassCut) {
          DimuMCut_mass_L3[i]->SetFillColor(kRed);
          DimuMCut_mass_L3[i]->SetFillStyle(3345);
          DimuMCut_mass_L3[i]->Draw("same");
        }
        if (flag.doSinglemuPtCut) {
          DimuPtCut_mass_L3[i]->SetFillColor(kBlue);
          DimuPtCut_mass_L3[i]->SetFillStyle(3354);
          DimuPtCut_mass_L3[i]->Draw("same");
        }
        if (flag.doSinglemuPtCut && flag.doDimuMassCut) {
          DimuMPtCut_mass_L3[i]->SetFillColor(kGreen);
          DimuMPtCut_mass_L3[i]->SetFillStyle(3305);
          DimuMPtCut_mass_L3[i]->Draw("same");
        }
        cl2dimu->cd(2);   Dimu_eta_L3[i]->Draw();
        cl2dimu->cd(3);   Dimu_pt_L3[i]->Draw();
        cl2dimu->cd(4);
        stmp.str("");  stmp << "Events: " << ohTree.fChain->GetEntries();
        t->DrawLatex(0.0,0.9,stmp.str().c_str());
        stmp.str("");  stmp << "Total # of L3 events: " << info.tot_NL3ValidEvt;
        t->DrawLatex(0.0,0.85,stmp.str().c_str());
        stmp.str("");  stmp << "Total # of L3 dimuons: " << Dimu_mass_L3[i]->GetEntries();
        t->DrawLatex(0.0,0.8,stmp.str().c_str());
        stmp.str("");  stmp << "Trigger path: " << trigPath[i];
        t->DrawLatex(0.0,0.75,stmp.str().c_str());
        if (flag.doDimuMassCut && !flag.doSinglemuPtCut) {
          stmp.str("");  stmp << "Total # of L3 dimuons w/ dimuon mass cut: " << DimuMCut_mass_L3[i]->GetEntries();
          t->DrawLatex(0.0,0.7,stmp.str().c_str());
          stmp.str("");  stmp << "Mass cut on L3 dimuons (Red): " << flag.mCut << " GeV/c^{2}";
          t->DrawLatex(0.0,0.65,stmp.str().c_str());
        }
        if (flag.doSinglemuPtCut && !flag.doDimuMassCut) {
          stmp.str("");  stmp << "Total # of L3 dimuons w/ single mu pT cut: " << DimuPtCut_mass_L3[i]->GetEntries();
          t->DrawLatex(0.0,0.7,stmp.str().c_str());
          stmp.str("");  stmp << "pT cut on a L3 muon (Blue): " << flag.pTCut << " GeV/c";
          t->DrawLatex(0.0,0.65,stmp.str().c_str());
        }
        if (flag.doSinglemuPtCut && flag.doDimuMassCut) {
          stmp.str("");  stmp << "Total # of L3 dimuons w/ dimuon mass cut (Red): " << DimuMCut_mass_L3[i]->GetEntries();
          t->DrawLatex(0.0,0.7,stmp.str().c_str());
          stmp.str("");  stmp << "Total # of L3 dimuons w/ single mu pT cut (Blue): " << DimuPtCut_mass_L3[i]->GetEntries();
          t->DrawLatex(0.0,0.65,stmp.str().c_str());
          stmp.str("");  stmp << "Total # of L3 dimuons w/ dimu mass" ;
          t->DrawLatex(0.0,0.6,stmp.str().c_str());
          stmp.str("");  stmp << "        & single mu pT cut (Green): " << DimuMPtCut_mass_L3[i]->GetEntries();
          t->DrawLatex(0.0,0.55,stmp.str().c_str());
          stmp.str("");  stmp << "Mass cut on L3 dimuons : " << flag.mCut << " GeV/c^{2}";
          t->DrawLatex(0.0,0.5,stmp.str().c_str());
          stmp.str("");  stmp << "pT cut on a L3 muon : " << flag.pTCut << " GeV/c";
          t->DrawLatex(0.0,0.45,stmp.str().c_str());
        }
        title = "DimuHist_L3_" + trigPath[i] + ".png";
        cl2dimu->SaveAs(title.c_str());
        delete cl2dimu;
      }
    }

    gStyle->SetOptStat("e");
    TCanvas *ctrig = new TCanvas("trig","trig",1300,1000);
    ctrig->Divide(2,2);
    ctrig->cd(1);   Frac_1st_etapt[i]->Draw("colz,text");
    ctrig->cd(2);   Frac_2mu_eta[i]->Draw("colz,text");
    ctrig->cd(3);   Frac_2mu_pt[i]->Draw("colz,text");
    ctrig->cd(4);
    stmp.str("");  stmp << "Events: " << ohTree.fChain->GetEntries();
    t->DrawLatex(0.0,0.9,stmp.str().c_str());
    stmp.str("");  stmp << "Total sum of NL1Mu: " << info.tot_NL1Mu;
    t->DrawLatex(0.0,0.8,stmp.str().c_str());
    stmp.str("");  stmp << "Total # of L1 events: " << info.tot_NL1ValidEvt;
    t->DrawLatex(0.0,0.7,stmp.str().c_str());
    stmp.str("");  stmp << "Trigger path: " << trigPath[i];
    t->DrawLatex(0.0,0.6,stmp.str().c_str());
    title = trigPath[i] + ".png";
    ctrig->SaveAs(title.c_str());
    delete ctrig;

    if (readHLT[i] >= 2) {
      ctrig = new TCanvas("trig","trig",1300,1000);
      ctrig->Divide(2,2);
      ctrig->cd(1);   Frac_1st_etapt_L2[i]->Draw("colz,text");
      ctrig->cd(2);   Frac_2mu_eta_L2[i]->Draw("colz,text");
      ctrig->cd(3);   Frac_2mu_pt_L2[i]->Draw("colz,text");
      ctrig->cd(4);
      stmp.str("");  stmp << "Events: " << ohTree.fChain->GetEntries();
      t->DrawLatex(0.0,0.9,stmp.str().c_str());
      stmp.str("");  stmp << "Total sum of NL1Mu: " << info.tot_NL1Mu;
      t->DrawLatex(0.0,0.8,stmp.str().c_str());
      stmp.str("");  stmp << "Total # of L1 events: " << info.tot_NL1ValidEvt;
      t->DrawLatex(0.0,0.7,stmp.str().c_str());
      stmp.str("");  stmp << "Total sum of NohMuL2: " << info.tot_NohMuL2;
      t->DrawLatex(0.0,0.6,stmp.str().c_str());
      stmp.str("");  stmp << "Total # of L2 events: " << info.tot_NL2ValidEvt;
      t->DrawLatex(0.0,0.5,stmp.str().c_str());
      stmp.str("");  stmp << "Trigger path: " << trigPath[i];
      t->DrawLatex(0.0,0.4,stmp.str().c_str());
      title = trigPath[i] + "_L2.png";
      ctrig->SaveAs(title.c_str());
      delete ctrig;
      if (readHLT[i] == 3) {
        ctrig = new TCanvas("trig","trig",1300,1000);
        ctrig->Divide(2,2);
        ctrig->cd(1);   Frac_1st_etapt_L3[i]->Draw("colz,text");
        ctrig->cd(2);   Frac_2mu_eta_L3[i]->Draw("colz,text");
        ctrig->cd(3);   Frac_2mu_pt_L3[i]->Draw("colz,text");
        ctrig->cd(4);
        stmp.str("");  stmp << "Events: " << ohTree.fChain->GetEntries();
        t->DrawLatex(0.0,0.9,stmp.str().c_str());
        stmp.str("");  stmp << "Total sum of NL1Mu: " << info.tot_NL1Mu;
        t->DrawLatex(0.0,0.8,stmp.str().c_str());
        stmp.str("");  stmp << "Total # of L1 events: " << info.tot_NL1ValidEvt;
        t->DrawLatex(0.0,0.7,stmp.str().c_str());
        stmp.str("");  stmp << "Total sum of NohMuL2: " << info.tot_NohMuL2;
        t->DrawLatex(0.0,0.6,stmp.str().c_str());
        stmp.str("");  stmp << "Total # of L2 events: " << info.tot_NL2ValidEvt;
        t->DrawLatex(0.0,0.5,stmp.str().c_str());
        stmp.str("");  stmp << "Total sum of NohMuL3: " << info.tot_NohMuL3;
        t->DrawLatex(0.0,0.4,stmp.str().c_str());
        stmp.str("");  stmp << "Total # of L3 events: " << info.tot_NL3ValidEvt;
        t->DrawLatex(0.0,0.3,stmp.str().c_str());
        stmp.str("");  stmp << "Trigger path: " << trigPath[i];
        t->DrawLatex(0.0,0.2,stmp.str().c_str());
        title = trigPath[i] + "_L3.png";
        ctrig->SaveAs(title.c_str());
        delete ctrig;
      }
    }

    ctrig = new TCanvas("trig","trig",1300,1000);
    ctrig->Divide(2,2);
    ctrig->cd(1);   Inte_1st_etapt[i]->Draw("colz,text");
    ctrig->cd(2);   Inte_2mu_eta[i]->Draw("colz,text");
    ctrig->cd(3);   Inte_2mu_pt[i]->Draw("colz,text");
    ctrig->cd(4);
    stmp.str("");  stmp << "Events: " << ohTree.fChain->GetEntries();
    t->DrawLatex(0.0,0.9,stmp.str().c_str());
    stmp.str("");  stmp << "Total sum of NL1Mu: " << info.tot_NL1Mu;
    t->DrawLatex(0.0,0.8,stmp.str().c_str());
    stmp.str("");  stmp << "Total # of L1 events: " << info.tot_NL1ValidEvt;
    t->DrawLatex(0.0,0.7,stmp.str().c_str());
    stmp.str("");  stmp << "Trigger path: " << trigPath[i];
    t->DrawLatex(0.0,0.6,stmp.str().c_str());
    title = trigPath[i] + "_inte.png";
    ctrig->SaveAs(title.c_str());
    delete ctrig;

    if (readHLT[i] >= 2) {
      ctrig = new TCanvas("trig","trig",1300,1000);
      ctrig->Divide(2,2);
      ctrig->cd(1);   Inte_1st_etapt_L2[i]->Draw("colz,text");
      ctrig->cd(2);   Inte_2mu_eta_L2[i]->Draw("colz,text");
      ctrig->cd(3);   Inte_2mu_pt_L2[i]->Draw("colz,text");
      ctrig->cd(4);
      stmp.str("");  stmp << "Events: " << ohTree.fChain->GetEntries();
      t->DrawLatex(0.0,0.9,stmp.str().c_str());
      stmp.str("");  stmp << "Total sum of NL1Mu: " << info.tot_NL1Mu;
      t->DrawLatex(0.0,0.8,stmp.str().c_str());
      stmp.str("");  stmp << "Total # of L1 events: " << info.tot_NL1ValidEvt;
      t->DrawLatex(0.0,0.7,stmp.str().c_str());
      stmp.str("");  stmp << "Total sum of NohMuL2: " << info.tot_NohMuL2;
      t->DrawLatex(0.0,0.6,stmp.str().c_str());
      stmp.str("");  stmp << "Total # of L2 events: " << info.tot_NL2ValidEvt;
      t->DrawLatex(0.0,0.5,stmp.str().c_str());
      stmp.str("");  stmp << "Trigger path: " << trigPath[i];
      t->DrawLatex(0.0,0.4,stmp.str().c_str());
      title = trigPath[i] + "_L2_inte.png";
      ctrig->SaveAs(title.c_str());
      delete ctrig;
      if (readHLT[i] == 3) {
        ctrig = new TCanvas("trig","trig",1300,1000);
        ctrig->Divide(2,2);
        ctrig->cd(1);   Inte_1st_etapt_L3[i]->Draw("colz,text");
        ctrig->cd(2);   Inte_2mu_eta_L3[i]->Draw("colz,text");
        ctrig->cd(3);   Inte_2mu_pt_L3[i]->Draw("colz,text");
        ctrig->cd(4);
        stmp.str("");  stmp << "Events: " << ohTree.fChain->GetEntries();
        t->DrawLatex(0.0,0.9,stmp.str().c_str());
        stmp.str("");  stmp << "Total sum of NL1Mu: " << info.tot_NL1Mu;
        t->DrawLatex(0.0,0.8,stmp.str().c_str());
        stmp.str("");  stmp << "Total # of L1 events: " << info.tot_NL1ValidEvt;
        t->DrawLatex(0.0,0.7,stmp.str().c_str());
        stmp.str("");  stmp << "Total sum of NohMuL2: " << info.tot_NohMuL2;
        t->DrawLatex(0.0,0.6,stmp.str().c_str());
        stmp.str("");  stmp << "Total # of L2 events: " << info.tot_NL2ValidEvt;
        t->DrawLatex(0.0,0.5,stmp.str().c_str());
        stmp.str("");  stmp << "Total sum of NohMuL3: " << info.tot_NohMuL3;
        t->DrawLatex(0.0,0.4,stmp.str().c_str());
        stmp.str("");  stmp << "Total # of L3 events: " << info.tot_NL3ValidEvt;
        t->DrawLatex(0.0,0.3,stmp.str().c_str());
        stmp.str("");  stmp << "Trigger path: " << trigPath[i];
        t->DrawLatex(0.0,0.2,stmp.str().c_str());
        title = trigPath[i] + "_L3_inte.png";
        ctrig->SaveAs(title.c_str());
        delete ctrig;
      }
    }
  }


  return 0;
}
