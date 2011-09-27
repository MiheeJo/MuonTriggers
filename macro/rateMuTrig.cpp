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
  const char *fnoh = "/castor/cern.ch/user/m/miheejo/openHLT/cms440p10/HICorePhysics_L1DoubleMuOpen_RAWHLTRECO/v3/hltana_newL1newHLT.root";

  FLAG flag_;
  FLAG &flag = flag_;

  // Trigger cut parameters
  flag.doDimuMassCut = true;
  flag.mCut = 0.0;             //in GeV

  // Triggered object with trigger paths
  vector<string> trigPath;  //TrigPath, read L2/L3 or not
  vector<int> readHLT;
/*  trigPath.push_back("L1_SingleMu3");
  readHLT.push_back(0);
  trigPath.push_back("HLT_HIL1SingleMu3");
  readHLT.push_back(1);
  trigPath.push_back("HLT_HIL2Mu3");
  readHLT.push_back(2);
  trigPath.push_back("HLT_HIL3Mu3");
  readHLT.push_back(3);
  trigPath.push_back("L1_DoubleMuOpen");
  readHLT.push_back(0);*/
  trigPath.push_back("HLT_HIL1DoubleMuOpen");
  readHLT.push_back(1);
  trigPath.push_back("HLT_HIL2DoubleMu0");
  readHLT.push_back(2);
  trigPath.push_back("HLT_HIL2DoubleMu3");
  readHLT.push_back(2);
  trigPath.push_back("HLT_HIL3DoubleMuOpen");
  readHLT.push_back(3);
  trigPath.push_back("HLT_HIL3DoubleMuOpen_Mgt2");
  readHLT.push_back(3);
  trigPath.push_back("HLT_HIL3DoubleMuOpen_Mgt2_SS");
  readHLT.push_back(3);
  trigPath.push_back("HLT_HIL3DoubleMuOpen_Mgt2_OS");
  readHLT.push_back(3);
  trigPath.push_back("HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy");
  readHLT.push_back(3);
  const unsigned int ntrig = trigPath.size();
  Int_t trig[ntrig];
  string title;

  // Number of trigger fired
  int Trig_fired[ntrig];
//  int Trig_lumi[ntrig];
  for (unsigned int idx=0; idx<ntrig; idx++) {
    Trig_fired[idx] = 0;
  }


  // Dimuon
  TH1F *Dimu_mass_L2[ntrig];
  TH1F *Dimu_eta_L2[ntrig];
  TH1F *Dimu_pt_L2[ntrig];
  TH1F *Dimu_phi_L2[ntrig];
  TH1F *DimuMCut_mass_L2[ntrig];
  TH1F *Dimu_mass_L3[ntrig];
  TH1F *Dimu_eta_L3[ntrig];
  TH1F *Dimu_pt_L3[ntrig];
  TH1F *Dimu_phi_L3[ntrig];
  TH1F *DimuMCut_mass_L3[ntrig];

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

  for (unsigned int i=0; i<ntrig; i++) {
    if (readHLT[i] > 2) {
      title = "DimuM_L2_" + trigPath[i];
      Dimu_mass_L2[i] = new TH1F(title.c_str(),title.c_str(),80,0,80);
      Dimu_mass_L2[i]->GetXaxis()->SetTitle("m_{#mu#mu}(GeV/c^{2})");
      title = "DimuMCut_L2_" + trigPath[i];
      DimuMCut_mass_L2[i] = new TH1F(title.c_str(),title.c_str(),80,0,80);
      DimuMCut_mass_L2[i]->GetXaxis()->SetTitle("m_{#mu#mu}(GeV/c^{2})");
      title = "DimuEta_L2_" + trigPath[i];
      Dimu_eta_L2[i] = new TH1F(title.c_str(),title.c_str(),ETA,0,2.4);
      Dimu_eta_L2[i]->GetXaxis()->SetTitle("|#eta|");
      title = "DimuPt_L2_" + trigPath[i];
      Dimu_pt_L2[i] = new TH1F(title.c_str(),title.c_str(),PT,0,20);
      Dimu_pt_L2[i]->GetXaxis()->SetTitle("p_T");
      title = "DimuPhi_L2_" + trigPath[i];
      Dimu_phi_L2[i] = new TH1F(title.c_str(),title.c_str(),PHI,-PI,PI);
      Dimu_phi_L2[i]->GetXaxis()->SetTitle("#phi");
      if (readHLT[i] == 3) {
        title = "DimuM_L3_" + trigPath[i];
        Dimu_mass_L3[i] = new TH1F(title.c_str(),title.c_str(),80,0,80);
        Dimu_mass_L3[i]->GetXaxis()->SetTitle("m_{#mu#mu}(GeV/c^{2})");
        title = "DimuMCut_L3_" + trigPath[i];
        DimuMCut_mass_L3[i] = new TH1F(title.c_str(),title.c_str(),80,0,80);
        DimuMCut_mass_L3[i]->GetXaxis()->SetTitle("m_{#mu#mu}(GeV/c^{2})");
        title = "DimuEta_L3_" + trigPath[i];
        Dimu_eta_L3[i] = new TH1F(title.c_str(),title.c_str(),ETA,0,2.4);
        Dimu_eta_L3[i]->GetXaxis()->SetTitle("|#eta|");
        title = "DimuPt_L3_" + trigPath[i];
        Dimu_pt_L3[i] = new TH1F(title.c_str(),title.c_str(),PT,0,20);
        Dimu_pt_L3[i]->GetXaxis()->SetTitle("p_T");
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
    Frac_2mu_pt[i]->GetXaxis()->SetTitle("Leading p_T");
    Frac_2mu_pt[i]->GetYaxis()->SetTitle("Sub-leading p_T");

    if (readHLT[i] > 2) {
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
      Frac_2mu_pt_L2[i]->GetXaxis()->SetTitle("Leading p_T");
      Frac_2mu_pt_L2[i]->GetYaxis()->SetTitle("Sub-leading p_T");

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
        Frac_2mu_pt_L3[i]->GetXaxis()->SetTitle("Leading p_T");
        Frac_2mu_pt_L3[i]->GetYaxis()->SetTitle("Sub-leading p_T");
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
    Inte_2mu_pt[i]->GetXaxis()->SetTitle("Leading p_T");
    Inte_2mu_pt[i]->GetYaxis()->SetTitle("Sub-leading p_T");

    if (readHLT[i] > 2) {
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
      Inte_2mu_pt_L2[i]->GetXaxis()->SetTitle("Leading p_T");
      Inte_2mu_pt_L2[i]->GetYaxis()->SetTitle("Sub-leading p_T");

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
        Inte_2mu_pt_L3[i]->GetXaxis()->SetTitle("Leading p_T");
        Inte_2mu_pt_L3[i]->GetYaxis()->SetTitle("Sub-leading p_T");
      }

    }
  }


  ////////// Read input file
  cout << "1" << endl;
  HltTree       ohTree_(fnoh,true);
  HltTree       &ohTree = ohTree_;
  TTree *tree;
  cout << "2" << endl;
  if (!ohTree.fChain->GetCurrentFile()) {
    cout << "Failed to open root files\n"; return -1;
  }

  INFO info_;
  INFO &info = info_;

  for (unsigned int i=0; i<ntrig; i++) {
    tree = ohTree.fChain;
    tree->SetBranchAddress(trigPath[i].c_str(),&trig[i]);
  }


  for (int i=0; i<ohTree.fChain->GetEntries(); i++) {
    if (i%1000 == 0) cout << "processing entry: " << i << endl;
    ohTree.GetEntry(i);
    tree->GetEntry(i);
  
    ////////// Get information of muon objects in gen, L1, L2 levels
    info.tot_NL1Mu += ohTree.NL1Mu;
    info.tot_NohMuL2 += ohTree.NohMuL2;
    info.tot_NohMuL3 += ohTree.NohMuL3;
    if (ohTree.NL1Mu > 0 ) info.tot_NL1ValidEvt ++;
    if (ohTree.NohMuL2 > 0) info.tot_NL2ValidEvt ++;
    if (ohTree.NohMuL3 > 0) info.tot_NL3ValidEvt ++;

    for (unsigned int idx=0; idx<ntrig; idx++) {
      if (trig[idx]) {
        /*if (readHLT[idx] == 1 && (ohTree.L1MuEta[0] > 2.1 && ohTree.L1MuEta[1] > 2.1)) {
          Trig_fired[idx]++;    //Trigger fired
        } else if (readHLT[idx] == 2 && (ohTree.ohMuL2Eta[0] > 2.1 && ohTree.ohMuL2Eta[1] > 2.1)) {
          Trig_fired[idx]++;    //Trigger fired
        } else if (readHLT[idx] == 3 && (ohTree.ohMuL3Eta[0] > 2.1 && ohTree.ohMuL3Eta[1] > 2.1)) {
          Trig_fired[idx]++;    //Trigger fired
        }*/

        int nFired=0;
        // |y| < 2.1
        if (readHLT[idx] == 1) {
          for (int a=0; a<ohTree.NL1Mu; a++) {
            if (fabs(ohTree.L1MuEta[a]) < 2.1) nFired++;
          }
          if (nFired > 2) Trig_fired[idx]++;    //Trigger fired
        } else if (readHLT[idx] == 2){
          for (int a=0; a<ohTree.NohMuL2; a++) {
            if (fabs(ohTree.ohMuL2Eta[a]) < 2.1) nFired++;
          }
          if (nFired > 2) Trig_fired[idx]++;    //Trigger fired
        } else if (readHLT[idx] == 3) {
          for (int a=0; a<ohTree.NohMuL3; a++) {
            if (fabs(ohTree.ohMuL3Eta[a]) < 2.1)  nFired++;
          }
          if (nFired > 2) Trig_fired[idx]++;    //Trigger fired
        }

        // |p_T| > 1
/*        if (readHLT[idx] == 1) {
          for (int a=0; a<ohTree.NL1Mu; a++) {
            if (ohTree.L1MuPt[a] > 1) nFired++;
          }
          if (nFired > 2) Trig_fired[idx]++;    //Trigger fired
        } else if (readHLT[idx] == 2){
          for (int a=0; a<ohTree.NohMuL2; a++) {
            if (ohTree.ohMuL2Pt[a] > 1) nFired++;
          }
          if (nFired > 2) Trig_fired[idx]++;    //Trigger fired
        } else if (readHLT[idx] == 3) {
          for (int a=0; a<ohTree.NohMuL3; a++) {
            if (ohTree.ohMuL3Pt[a] > 1)  nFired++;
          }
          if (nFired > 2) Trig_fired[idx]++;    //Trigger fired
        }*/
        
        //        Trig_fired[idx]++;  //No cuts

        if (readHLT[idx] > 2) {
          map<float,int,ptcomp> l2;
          map<float,int>::iterator it;

          for (int a=0; a<ohTree.NohMuL2; a++) {
            float pt = ohTree.ohMuL2Pt[a];
            l2[pt] = a;
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
            
            Frac_2mu_pt_L2[idx]->Fill(ohTree.ohMuL2Pt[a[0]],ohTree.ohMuL2Pt[a[1]]);
            Frac_2mu_eta_L2[idx]->Fill(fabs(ohTree.ohMuL2Eta[a[0]]),fabs(ohTree.ohMuL2Eta[a[1]]));

            TLorentzVector L2mu1, L2mu2, L2dimu;
            L2mu1.SetPtEtaPhiM(ohTree.ohMuL2Pt[a[0]],ohTree.ohMuL2Eta[a[0]],ohTree.ohMuL2Phi[a[0]],Mmu);
            L2mu2.SetPtEtaPhiM(ohTree.ohMuL2Pt[a[1]],ohTree.ohMuL2Eta[a[1]],ohTree.ohMuL2Phi[a[1]],Mmu);

            L2dimu = L2mu1 + L2mu2; // Use only 0th, 1th L1 objects
            Dimu_mass_L2[idx]->Fill(L2dimu.M());
            Dimu_eta_L2[idx]->Fill(L2dimu.Eta());
            Dimu_pt_L2[idx]->Fill(L2dimu.Pt());
            Dimu_phi_L2[idx]->Fill(L2dimu.Phi());
            if (flag.doDimuMassCut && L2dimu.M() > flag.mCut) {
                DimuMCut_mass_L2[idx]->Fill(L2dimu.M());
            }
          }
        
          if (readHLT[idx] == 3) {
            map<float,int,ptcomp> l3;

            for (int a=0; a<ohTree.NohMuL3; a++) {
              float pt = ohTree.ohMuL3Pt[a];
              l3[pt] = a;
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

              TLorentzVector L3mu1, L3mu2, L3dimu;
              L3mu1.SetPtEtaPhiM(ohTree.ohMuL3Pt[b[0]],ohTree.ohMuL3Eta[b[0]],ohTree.ohMuL3Phi[b[0]],Mmu);
              L3mu2.SetPtEtaPhiM(ohTree.ohMuL3Pt[b[1]],ohTree.ohMuL3Eta[b[1]],ohTree.ohMuL3Phi[b[1]],Mmu);

              L3dimu = L3mu1 + L3mu2; // Use only 0th, 1th L1 objects
              Dimu_mass_L3[idx]->Fill(L3dimu.M());
              Dimu_eta_L3[idx]->Fill(L3dimu.Eta());
              Dimu_pt_L3[idx]->Fill(L3dimu.Pt());
              Dimu_phi_L3[idx]->Fill(L3dimu.Phi());
              if (flag.doDimuMassCut && L3dimu.M() > flag.mCut) {
                  DimuMCut_mass_L3[idx]->Fill(L3dimu.M());
              }
            }
          } //end of readHLT == 3

        }


        // Get L1 info
        map<float,int,ptcomp> l1;
        map<float,int>::iterator it;

        for (int b=0; b<ohTree.NL1Mu; b++) {
          if (ohTree.L1MuEta[b] == -999) continue;    //Invalid L1 muon
          float pt = ohTree.L1MuPt[b];
          l1[pt] = b;
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
    if (readHLT[i] > 2) {
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
      if (readHLT[i] > 2) {
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
            if (readHLT[i] > 2) {
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
        if (readHLT[i] > 2) {
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
    if (readHLT[i] > 2) {
      TCanvas *cl2dimu = new TCanvas("dimuL2","dimuL2",1300,1000);
      cl2dimu->Divide(2,2);
      cl2dimu->cd(1);
      Dimu_mass_L2[i]->Draw();
      if (flag.doDimuMassCut) {
        DimuMCut_mass_L2[i]->SetFillColor(kRed);
        DimuMCut_mass_L2[i]->SetFillStyle(3003);
        DimuMCut_mass_L2[i]->Draw("sames");
      }
      cl2dimu->cd(2);   Dimu_eta_L2[i]->Draw();
      cl2dimu->cd(3);   Dimu_pt_L2[i]->Draw();
      cl2dimu->cd(4);
      stmp.str("");  stmp << "Events: " << ohTree.fChain->GetEntries();
      t->DrawLatex(0.1,0.9,stmp.str().c_str());
      stmp.str("");  stmp << "Total sum of NohMuL2: " << info.tot_NohMuL2;
      t->DrawLatex(0.1,0.8,stmp.str().c_str());
      stmp.str("");  stmp << "Total # of L2 events: " << info.tot_NL2ValidEvt;
      t->DrawLatex(0.1,0.7,stmp.str().c_str());
      stmp.str("");  stmp << "Total # of L2 dimuons: " << Dimu_mass_L2[i]->GetEntries();
      t->DrawLatex(0.1,0.6,stmp.str().c_str());
      stmp.str("");  stmp << "Trigger path: " << trigPath[i];
      t->DrawLatex(0.1,0.5,stmp.str().c_str());
      if (flag.doDimuMassCut) {
        stmp.str("");  stmp << "Mass cut on L2 dimuons: " << flag.mCut << " GeV/c^{2}";
        t->DrawLatex(0.1,0.4,stmp.str().c_str());
      }
      title = "DimuHist_L2_" + trigPath[i] + ".png";
      cl2dimu->SaveAs(title.c_str());
      delete cl2dimu;
      if (readHLT[i] == 3) {
        cl2dimu = new TCanvas("dimuL2","dimuL2",1300,1000);
        cl2dimu->Divide(2,2);
        cl2dimu->cd(1);
        Dimu_mass_L3[i]->Draw();
        if (flag.doDimuMassCut) {
          DimuMCut_mass_L3[i]->SetFillColor(kRed);
          DimuMCut_mass_L3[i]->SetFillStyle(3003);
          DimuMCut_mass_L3[i]->Draw("sames");
        }
        cl2dimu->cd(2);   Dimu_eta_L3[i]->Draw();
        cl2dimu->cd(3);   Dimu_pt_L3[i]->Draw();
        cl2dimu->cd(4);
        stmp.str("");  stmp << "Events: " << ohTree.fChain->GetEntries();
        t->DrawLatex(0.1,0.9,stmp.str().c_str());
        stmp.str("");  stmp << "Total sum of NohMuL3: " << info.tot_NohMuL3;
        t->DrawLatex(0.1,0.8,stmp.str().c_str());
        stmp.str("");  stmp << "Total # of L3 events: " << info.tot_NL3ValidEvt;
        t->DrawLatex(0.1,0.7,stmp.str().c_str());
        stmp.str("");  stmp << "Total # of L3 dimuons: " << Dimu_mass_L3[i]->GetEntries();
        t->DrawLatex(0.1,0.6,stmp.str().c_str());
        stmp.str("");  stmp << "Trigger path: " << trigPath[i];
        t->DrawLatex(0.1,0.5,stmp.str().c_str());
        if (flag.doDimuMassCut) {
          stmp.str("");  stmp << "Mass cut on L3 dimuons: " << flag.mCut << " GeV/c^{2}";
          t->DrawLatex(0.1,0.4,stmp.str().c_str());
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
    t->DrawLatex(0.1,0.9,stmp.str().c_str());
    stmp.str("");  stmp << "Total sum of NL1Mu: " << info.tot_NL1Mu;
    t->DrawLatex(0.1,0.8,stmp.str().c_str());
    stmp.str("");  stmp << "Total # of L1 events: " << info.tot_NL1ValidEvt;
    t->DrawLatex(0.1,0.7,stmp.str().c_str());
    stmp.str("");  stmp << "Trigger path: " << trigPath[i];
    t->DrawLatex(0.1,0.6,stmp.str().c_str());
    title = trigPath[i] + ".png";
    ctrig->SaveAs(title.c_str());
    delete ctrig;

    if (readHLT[i] > 2) {
      ctrig = new TCanvas("trig","trig",1300,1000);
      ctrig->Divide(2,2);
      ctrig->cd(1);   Frac_1st_etapt_L2[i]->Draw("colz,text");
      ctrig->cd(2);   Frac_2mu_eta_L2[i]->Draw("colz,text");
      ctrig->cd(3);   Frac_2mu_pt_L2[i]->Draw("colz,text");
      ctrig->cd(4);
      stmp.str("");  stmp << "Events: " << ohTree.fChain->GetEntries();
      t->DrawLatex(0.1,0.9,stmp.str().c_str());
      stmp.str("");  stmp << "Total sum of NL1Mu: " << info.tot_NL1Mu;
      t->DrawLatex(0.1,0.8,stmp.str().c_str());
      stmp.str("");  stmp << "Total # of L1 events: " << info.tot_NL1ValidEvt;
      t->DrawLatex(0.1,0.7,stmp.str().c_str());
      stmp.str("");  stmp << "Total sum of NohMuL2: " << info.tot_NohMuL2;
      t->DrawLatex(0.1,0.6,stmp.str().c_str());
      stmp.str("");  stmp << "Total # of L2 events: " << info.tot_NL2ValidEvt;
      t->DrawLatex(0.1,0.5,stmp.str().c_str());
      stmp.str("");  stmp << "Trigger path: " << trigPath[i];
      t->DrawLatex(0.1,0.4,stmp.str().c_str());
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
        t->DrawLatex(0.1,0.9,stmp.str().c_str());
        stmp.str("");  stmp << "Total sum of NL1Mu: " << info.tot_NL1Mu;
        t->DrawLatex(0.1,0.8,stmp.str().c_str());
        stmp.str("");  stmp << "Total # of L1 events: " << info.tot_NL1ValidEvt;
        t->DrawLatex(0.1,0.7,stmp.str().c_str());
        stmp.str("");  stmp << "Total sum of NohMuL2: " << info.tot_NohMuL2;
        t->DrawLatex(0.1,0.6,stmp.str().c_str());
        stmp.str("");  stmp << "Total # of L2 events: " << info.tot_NL2ValidEvt;
        t->DrawLatex(0.1,0.5,stmp.str().c_str());
        stmp.str("");  stmp << "Total sum of NohMuL3: " << info.tot_NohMuL3;
        t->DrawLatex(0.1,0.4,stmp.str().c_str());
        stmp.str("");  stmp << "Total # of L3 events: " << info.tot_NL3ValidEvt;
        t->DrawLatex(0.1,0.3,stmp.str().c_str());
        stmp.str("");  stmp << "Trigger path: " << trigPath[i];
        t->DrawLatex(0.1,0.2,stmp.str().c_str());
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
    t->DrawLatex(0.1,0.9,stmp.str().c_str());
    stmp.str("");  stmp << "Total sum of NL1Mu: " << info.tot_NL1Mu;
    t->DrawLatex(0.1,0.8,stmp.str().c_str());
    stmp.str("");  stmp << "Total # of L1 events: " << info.tot_NL1ValidEvt;
    t->DrawLatex(0.1,0.7,stmp.str().c_str());
    stmp.str("");  stmp << "Trigger path: " << trigPath[i];
    t->DrawLatex(0.1,0.6,stmp.str().c_str());
    title = trigPath[i] + "_inte.png";
    ctrig->SaveAs(title.c_str());
    delete ctrig;

    if (readHLT[i] > 2) {
      ctrig = new TCanvas("trig","trig",1300,1000);
      ctrig->Divide(2,2);
      ctrig->cd(1);   Inte_1st_etapt_L2[i]->Draw("colz,text");
      ctrig->cd(2);   Inte_2mu_eta_L2[i]->Draw("colz,text");
      ctrig->cd(3);   Inte_2mu_pt_L2[i]->Draw("colz,text");
      ctrig->cd(4);
      stmp.str("");  stmp << "Events: " << ohTree.fChain->GetEntries();
      t->DrawLatex(0.1,0.9,stmp.str().c_str());
      stmp.str("");  stmp << "Total sum of NL1Mu: " << info.tot_NL1Mu;
      t->DrawLatex(0.1,0.8,stmp.str().c_str());
      stmp.str("");  stmp << "Total # of L1 events: " << info.tot_NL1ValidEvt;
      t->DrawLatex(0.1,0.7,stmp.str().c_str());
      stmp.str("");  stmp << "Total sum of NohMuL2: " << info.tot_NohMuL2;
      t->DrawLatex(0.1,0.6,stmp.str().c_str());
      stmp.str("");  stmp << "Total # of L2 events: " << info.tot_NL2ValidEvt;
      t->DrawLatex(0.1,0.5,stmp.str().c_str());
      stmp.str("");  stmp << "Trigger path: " << trigPath[i];
      t->DrawLatex(0.1,0.4,stmp.str().c_str());
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
        t->DrawLatex(0.1,0.9,stmp.str().c_str());
        stmp.str("");  stmp << "Total sum of NL1Mu: " << info.tot_NL1Mu;
        t->DrawLatex(0.1,0.8,stmp.str().c_str());
        stmp.str("");  stmp << "Total # of L1 events: " << info.tot_NL1ValidEvt;
        t->DrawLatex(0.1,0.7,stmp.str().c_str());
        stmp.str("");  stmp << "Total sum of NohMuL2: " << info.tot_NohMuL2;
        t->DrawLatex(0.1,0.6,stmp.str().c_str());
        stmp.str("");  stmp << "Total # of L2 events: " << info.tot_NL2ValidEvt;
        t->DrawLatex(0.1,0.5,stmp.str().c_str());
        stmp.str("");  stmp << "Total sum of NohMuL3: " << info.tot_NohMuL3;
        t->DrawLatex(0.1,0.4,stmp.str().c_str());
        stmp.str("");  stmp << "Total # of L3 events: " << info.tot_NL3ValidEvt;
        t->DrawLatex(0.1,0.3,stmp.str().c_str());
        stmp.str("");  stmp << "Trigger path: " << trigPath[i];
        t->DrawLatex(0.1,0.2,stmp.str().c_str());
        title = trigPath[i] + "_L3_inte.png";
        ctrig->SaveAs(title.c_str());
        delete ctrig;
      }
    }
  }


  return 0;
}
