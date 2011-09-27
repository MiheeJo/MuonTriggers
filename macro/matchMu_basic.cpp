#ifndef MATCHMU
#define MATCHMU
#include "matchMu.h"
#include "matchMu_tree.h"
#endif

#include <TLorentzVector.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLatex.h>

#include <sstream>
#include <TPaletteAxis.h>

int matchMu_basic(FriendMuTree &muTree, HltTree &ohTree, FLAG &flag, INFO &info) {
  cout << "Processing basic distributions ... "<< endl;
  // All L2 muon objects
  TH2F *h_All_L2_etapt = new TH2F("All_L2_etapt","All_L2_etapt;#eta;p_{T}",20,-2.4,2.4,PT,0,20);

  // Phi distribution
  TH1F *h_gen_phi = new TH1F("h_gen_phi","h_gen_phi;#phi",PHI,0,PI);
  TH1F *h_L1_phi = new TH1F("h_L1_phi","h_L1_phi;#phi",PHI,0,PI);
  TH1F *h_L2_phi = new TH1F("h_L2_phi","h_L2_phi;#phi",PHI,0,PI);

  // L1 and L2 muon's deltaR distribution
  TH1F *h_L1L2_dEta = new TH1F("L1L2_dEta","L1L2_dEta;#eta",ETA,0,2.4);
  TH1F *h_L1L2_dPhi = new TH1F("L1L2_dPhi","L1L2_dPhi;#phi",PHI,0,PI);
  TH1F *h_L1L2_dR = new TH1F("L1L2_dR","L1L2_dR;dR",50,0,5);

  // Gen-Sim and L1 muon's deltaR distribution
  TH1F *h_GenL1_dEta = new TH1F("GenL1_dEta","GenL1_dEta;#eta",ETA,0,2.4);
  TH1F *h_GenL1_dPhi = new TH1F("GenL1_dPhi","GenL1_dPhi;#phi",PHI,0,PI);
  TH1F *h_GenL1_dR = new TH1F("GenL1_dR","GenL1_dR;dR",50,0,5);
  // Gen-Sim and L2 muon's deltaR distribution
  TH1F *h_GenL2_dEta = new TH1F("GenL2_dEta","GenL2_dEta;#eta",ETA,0,2.4);
  TH1F *h_GenL2_dPhi = new TH1F("GenL2_dPhi","GenL2_dPhi;#phi",PHI,0,PI);
  TH1F *h_GenL2_dR = new TH1F("GenL2_dR","GenL2_dR;dR",50,0,5);

  // STA and L1 muon's deltaR distribution
  TH1F *h_StaL1_dEta = new TH1F("StaL1_dEta","StaL1_dEta;#eta",ETA,0,2.4);
  TH1F *h_StaL1_dPhi = new TH1F("StaL1_dPhi","StaL1_dPhi;#phi",PHI,0,PI);
  TH1F *h_StaL1_dR = new TH1F("StaL1_dR","StaL1_dR;dR",50,0,5);
  // STA and L2 muon's deltaR distribution
  TH1F *h_StaL2_dEta = new TH1F("StaL2_dEta","StaL2_dEta;#eta",ETA,0,2.4);
  TH1F *h_StaL2_dPhi = new TH1F("StaL2_dPhi","StaL2_dPhi;#phi",PHI,0,PI);
  TH1F *h_StaL2_dR = new TH1F("StaL2_dR","StaL2_dR;dR",50,0,5);

  for (int i=0; i<muTree.fChain->GetEntries(); i++) {
      muTree.GetEntry(i);
      ohTree.GetEntry(i);

      ////////// Compare event number
    if ((muTree.Run != ohTree.Run) || (muTree.Event != ohTree.Event)) {
      cout << "muTree and ohTree don't have same run/event number. Strange." << endl;
      return -1;;
    }

    ////////// All L2 muon objects are filled
    for (int b=0; b<ohTree.NohMuL2; b++) 
      h_All_L2_etapt->Fill(ohTree.ohMuL2Eta[b],ohTree.ohMuL2Pt[b]);

    ////////// Muon phi distributions are filled
    if (flag.doGen) {
      for (int b=0; b<muTree.Gen_nptl; b++) {
        float phi_t = muTree.Gen_phi[b];
        while (phi_t > PI) phi_t -= 2*PI;
        while (phi_t <= -PI) phi_t += 2*PI;
        h_gen_phi->Fill(fabs(phi_t));
      }
    }
    for (int b=0; b<ohTree.NL1Mu; b++) {
      if (ohTree.L1MuPhi[b] == -999) continue;    //Invalid L1 muon
      float phi_t = ohTree.L1MuPhi[b];
      while (phi_t > PI) phi_t -= 2*PI;
      while (phi_t <= -PI) phi_t += 2*PI;
      h_L1_phi->Fill(fabs(phi_t));
    }
    for (int b=0; b<ohTree.NohMuL2; b++) {
      float phi_t = ohTree.ohMuL2Phi[b];
      while (phi_t > PI) phi_t -= 2*PI;
      while (phi_t <= -PI) phi_t += 2*PI;
      h_L2_phi->Fill(fabs(phi_t));
    }
    
    ////////// Draw Delta_Eta, Delta_Phi, Delta_R distribution
    for (int b=0; b<ohTree.NohMuL2; b++) {
      float l1l2_deltaR = 100;
      float l1l2_deltaEta = 100;
      float l1l2_deltaPhi = 100;

      for (int a=0; a<ohTree.NL1Mu; a++) {
        if (ohTree.L1MuEta[a] == -999) continue;    //Invalid L1 muon

        float l1l2_deltaR_t = deltaR(ohTree.L1MuEta[a],ohTree.L1MuPhi[a],ohTree.ohMuL2Eta[b],ohTree.ohMuL2Phi[b]);
        float l1l2_deltaEta_t = ohTree.L1MuEta[a] - ohTree.ohMuL2Eta[b];
        float l1l2_deltaPhi_t = deltaPhi(ohTree.L1MuPhi[a],ohTree.ohMuL2Phi[b]);
        if (l1l2_deltaR_t <= l1l2_deltaR) l1l2_deltaR = l1l2_deltaR_t;
        if (fabs(l1l2_deltaEta_t) <= fabs(l1l2_deltaEta)) l1l2_deltaEta = l1l2_deltaEta_t;
        if (fabs(l1l2_deltaPhi_t) <= fabs(l1l2_deltaPhi)) l1l2_deltaPhi = l1l2_deltaPhi_t;
      }

      if (l1l2_deltaR != 100 && l1l2_deltaEta != 100 && l1l2_deltaPhi != 100) {
        h_L1L2_dEta->Fill(l1l2_deltaEta);
        h_L1L2_dPhi->Fill(l1l2_deltaPhi);
        h_L1L2_dR->Fill(l1l2_deltaR);
      }
    }

    /***************If doSta is true ******************/
    if (flag.doSta) {
      ////////// Draw Delta_Eta, Delta_Phi, Delta_R distribution
      for (int a=0; a<muTree.Sta_nptl; a++) {
        float l1_deltaR = 100;
        float l1_deltaEta = 100;
        float l1_deltaPhi = 100;
 
        for (int b=0; b<ohTree.NL1Mu; b++) {
          if (ohTree.L1MuEta[b] == -999) continue;    //Invalid L1 muon
          float l1_deltaR_t = deltaR(muTree.Sta_eta[a],muTree.Sta_phi[a],ohTree.L1MuEta[b],ohTree.L1MuPhi[b]);
          float l1_deltaEta_t = muTree.Sta_eta[a] - ohTree.L1MuEta[b];
          float l1_deltaPhi_t = deltaPhi(muTree.Sta_phi[a],ohTree.L1MuPhi[b]);

          if (l1_deltaR_t <= l1_deltaR) l1_deltaR = l1_deltaR_t;
          if (fabs(l1_deltaEta_t) <= fabs(l1_deltaEta)) l1_deltaEta = l1_deltaEta_t;
          if (fabs(l1_deltaPhi_t) <= fabs(l1_deltaPhi)) l1_deltaPhi = l1_deltaPhi_t;
        }

        if (l1_deltaR != 100 && l1_deltaEta != 100 && l1_deltaPhi != 100) {
          h_StaL1_dEta->Fill(l1_deltaEta);
          h_StaL1_dPhi->Fill(l1_deltaPhi);
          h_StaL1_dR->Fill(l1_deltaR);
        }
      }
      
      for (int a=0; a<muTree.Sta_nptl; a++) {
        float l2_deltaR = 100;
        float l2_deltaEta = 100;
        float l2_deltaPhi = 100;

        for (int b=0; b<ohTree.NohMuL2; b++) {
          float l2_deltaR_t = deltaR(muTree.Sta_eta[a],muTree.Sta_phi[a],ohTree.ohMuL2Eta[b],ohTree.ohMuL2Phi[b]);
          float l2_deltaEta_t = muTree.Sta_eta[a] - ohTree.ohMuL2Eta[b];
          float l2_deltaPhi_t = deltaPhi(muTree.Sta_phi[a],ohTree.ohMuL2Phi[b]);

          if (l2_deltaR_t <= l2_deltaR) l2_deltaR = l2_deltaR_t;
          if (fabs(l2_deltaEta_t) <= fabs(l2_deltaEta)) l2_deltaEta = l2_deltaEta_t;
          if (fabs(l2_deltaPhi_t) <= fabs(l2_deltaPhi)) l2_deltaPhi = l2_deltaPhi_t;
        }

        if (l2_deltaR != 100 && l2_deltaEta != 100 && l2_deltaPhi != 100) {
          h_StaL2_dEta->Fill(l2_deltaEta);
          h_StaL2_dPhi->Fill(l2_deltaPhi);
          h_StaL2_dR->Fill(l2_deltaR);
        }
      }
    }

    /***************If doGen is true ******************/
    if (flag.doGen) {
      ////////// Draw Delta_Eta, Delta_Phi, Delta_R distribution
      for (int b=0; b<ohTree.NL1Mu; b++) {
        if (ohTree.L1MuEta[b] == -999) continue;    //Invalid L1 muon
        float l1_deltaR = 100;
        float l1_deltaEta = 100;
        float l1_deltaPhi = 100;
        for (int a=0; a<muTree.Gen_nptl; a++) {
          if (!flag.doSim && muTree.Gen_status[a] == -99) continue;    //skip sim muon
          float l1_deltaR_t = deltaR(muTree.Gen_eta[a],muTree.Gen_phi[a],ohTree.L1MuEta[b],ohTree.L1MuPhi[b]);
          float l1_deltaEta_t = muTree.Gen_eta[a] - ohTree.L1MuEta[b];
          float l1_deltaPhi_t = deltaPhi(muTree.Gen_phi[a],ohTree.L1MuPhi[b]);

          if (l1_deltaR_t <= l1_deltaR) l1_deltaR = l1_deltaR_t;
          if (fabs(l1_deltaEta_t) <= fabs(l1_deltaEta)) l1_deltaEta = l1_deltaEta_t;
          if (fabs(l1_deltaPhi_t) <= fabs(l1_deltaPhi)) l1_deltaPhi = l1_deltaPhi_t;
        }
        if (l1_deltaR != 100 && l1_deltaEta != 100 && l1_deltaPhi != 100) {
          h_GenL1_dEta->Fill(l1_deltaEta);
          h_GenL1_dPhi->Fill(l1_deltaPhi);
          h_GenL1_dR->Fill(l1_deltaR);
        }
      }

      for (int b=0; b<ohTree.NohMuL2; b++) {
        float l2_deltaR = 100;
        float l2_deltaEta = 100;
        float l2_deltaPhi = 100;
        for (int a=0; a<muTree.Gen_nptl; a++) {
          if (!flag.doSim && muTree.Gen_status[a] == -99) continue;    //skip sim muon
          float l2_deltaR_t = deltaR(muTree.Gen_eta[a],muTree.Gen_phi[a],ohTree.ohMuL2Eta[b],ohTree.ohMuL2Phi[b]);
          float l2_deltaEta_t = muTree.Gen_eta[a] - ohTree.ohMuL2Eta[b];
          float l2_deltaPhi_t = deltaPhi(muTree.Gen_phi[a],ohTree.ohMuL2Phi[b]);

          if (l2_deltaR_t <= l2_deltaR) l2_deltaR = l2_deltaR_t;
          if (fabs(l2_deltaEta_t) <= fabs(l2_deltaEta)) l2_deltaEta = l2_deltaEta_t;
          if (fabs(l2_deltaPhi_t) <= fabs(l2_deltaPhi)) l2_deltaPhi = l2_deltaPhi_t;
        }
        if (l2_deltaR != 100 && l2_deltaEta != 100 && l2_deltaPhi != 100) {
          h_GenL2_dEta->Fill(l2_deltaEta);
          h_GenL2_dPhi->Fill(l2_deltaPhi);
          h_GenL2_dR->Fill(l2_deltaR);
        }
      }
    }

  }
  // End of reading entire entries in trees

  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  stringstream stmp;
  TLatex *t = new TLatex(); t->SetNDC(kTRUE);
  TPaletteAxis *paxis;

  TCanvas *call = new TCanvas("all","all",650,600);
  call->Draw();   call->cd();   h_All_L2_etapt->Draw("colz");
  gPad->Update();
  paxis = (TPaletteAxis*)h_All_L2_etapt->GetListOfFunctions()->FindObject("palette");
  if (paxis != NULL) {paxis->SetY2NDC(0.7); paxis->SetLabelSize(0.03);}
  call->SaveAs("all_L2.png");
    
  TCanvas *cphi = new TCanvas("phi","phi",1300,1000);
  cphi->Divide(2,2);
  cphi->cd(1);  h_gen_phi->Draw();
  cphi->cd(2);  h_L1_phi->Draw();
  cphi->cd(3);  h_L2_phi->Draw();
  cphi->SaveAs("phi_distribution.png");

  TCanvas *cdl1l2 = new TCanvas("l1l2","l1l2",1300,1000);
  cdl1l2->Divide(2,2);
  cdl1l2->cd(1);   h_L1L2_dEta->Draw();
  cdl1l2->cd(2);   h_L1L2_dPhi->Draw();
  cdl1l2->cd(3);   h_L1L2_dR->Draw();
  cdl1l2->cd(4);
  stmp.str("");  stmp << "Events: " << muTree.fChain->GetEntries();
  t->DrawLatex(0.1,0.9,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of GenMu,SimMu: " << info.tot_NGenMu;
  t->DrawLatex(0.1,0.8,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of StaMu: " << info.tot_NStaMu;
  t->DrawLatex(0.1,0.7,stmp.str().c_str());
  stmp.str("");  stmp << "Total sum of NL1Mu: " << info.tot_NL1Mu;
  t->DrawLatex(0.1,0.6,stmp.str().c_str());
  stmp.str("");  stmp << "Total sum of NohMuL2: " << info.tot_NohMuL2;
  t->DrawLatex(0.1,0.5,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of L1 events: " << info.tot_NL1ValidEvt;
  t->DrawLatex(0.1,0.4,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of L2 events: " << info.tot_NL2ValidEvt;
  t->DrawLatex(0.1,0.3,stmp.str().c_str());
  cdl1l2->SaveAs("delta_L1L2.png");

  if (flag.doSta) {
  TCanvas *cdstal1 = new TCanvas("stal1","stal1",1300,1000);
  cdstal1->Divide(2,2);
  cdstal1->cd(1);   h_StaL1_dEta->Draw();
  cdstal1->cd(2);   h_StaL1_dPhi->Draw();
  cdstal1->cd(3);   h_StaL1_dR->Draw();
  cdstal1->cd(4);
  stmp.str("");  stmp << "Events: " << muTree.fChain->GetEntries();
  t->DrawLatex(0.1,0.9,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of GenMu,SimMu: " << info.tot_NGenMu;
  t->DrawLatex(0.1,0.8,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of StaMu: " << info.tot_NStaMu;
  t->DrawLatex(0.1,0.7,stmp.str().c_str());
  stmp.str("");  stmp << "Total sum of NL1Mu: " << info.tot_NL1Mu;
  t->DrawLatex(0.1,0.6,stmp.str().c_str());
  stmp.str("");  stmp << "Total sum of NohMuL2: " << info.tot_NohMuL2;
  t->DrawLatex(0.1,0.5,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of L1 events: " << info.tot_NL1ValidEvt;
  t->DrawLatex(0.1,0.4,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of L2 events: " << info.tot_NL2ValidEvt;
  t->DrawLatex(0.1,0.3,stmp.str().c_str());
  cdstal1->SaveAs("delta_StaL1.png");

  TCanvas *cdstal2 = new TCanvas("stal2","stal2",1300,1000);
  cdstal2->Divide(2,2);
  cdstal2->cd(1);   h_StaL2_dEta->Draw();
  cdstal2->cd(2);   h_StaL2_dPhi->Draw();
  cdstal2->cd(3);   h_StaL2_dR->Draw();
  cdstal2->cd(4);
  stmp.str("");  stmp << "Events: " << muTree.fChain->GetEntries();
  t->DrawLatex(0.1,0.9,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of GenMu,SimMu: " << info.tot_NGenMu;
  t->DrawLatex(0.1,0.8,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of StaMu: " << info.tot_NStaMu;
  t->DrawLatex(0.1,0.7,stmp.str().c_str());
  stmp.str("");  stmp << "Total sum of NL1Mu: " << info.tot_NL1Mu;
  t->DrawLatex(0.1,0.6,stmp.str().c_str());
  stmp.str("");  stmp << "Total sum of NohMuL2: " << info.tot_NohMuL2;
  t->DrawLatex(0.1,0.5,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of L1 events: " << info.tot_NL1ValidEvt;
  t->DrawLatex(0.1,0.4,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of L2 events: " << info.tot_NL2ValidEvt;
  t->DrawLatex(0.1,0.3,stmp.str().c_str());
  cdstal2->SaveAs("delta_StaL2.png");
  }

  if (flag.doGen) {
  TCanvas *cdl1 = new TCanvas("genl1","genl1",1300,1000);
  cdl1->Divide(2,2);
  cdl1->cd(1);    h_GenL1_dEta->Draw();
  cdl1->cd(2);    h_GenL1_dPhi->Draw();
  cdl1->cd(3);    h_GenL1_dR->Draw();
  cdl1->cd(4);
  stmp.str("");  stmp << "Events: " << muTree.fChain->GetEntries();
  t->DrawLatex(0.1,0.9,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of GenMu,SimMu: " << info.tot_NGenMu;
  t->DrawLatex(0.1,0.8,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of StaMu: " << info.tot_NStaMu;
  t->DrawLatex(0.1,0.7,stmp.str().c_str());
  stmp.str("");  stmp << "Total sum of NL1Mu: " << info.tot_NL1Mu;
  t->DrawLatex(0.1,0.6,stmp.str().c_str());
  stmp.str("");  stmp << "Total sum of NohMuL2: " << info.tot_NohMuL2;
  t->DrawLatex(0.1,0.5,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of L1 events: " << info.tot_NL1ValidEvt;
  t->DrawLatex(0.1,0.4,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of L2 events: " << info.tot_NL2ValidEvt;
  t->DrawLatex(0.1,0.3,stmp.str().c_str());
  cdl1->SaveAs("delta_GenL1.png");

  TCanvas *cdl2 = new TCanvas("genl2","genl2",1300,1000);
  cdl2->Divide(2,2);
  cdl2->cd(1);    h_GenL2_dEta->Draw();
  cdl2->cd(2);    h_GenL2_dPhi->Draw();
  cdl2->cd(3);    h_GenL2_dR->Draw();
  cdl2->cd(4);
  stmp.str("");  stmp << "Events: " << muTree.fChain->GetEntries();
  t->DrawLatex(0.1,0.9,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of GenMu,SimMu: " << info.tot_NGenMu;
  t->DrawLatex(0.1,0.8,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of StaMu: " << info.tot_NStaMu;
  t->DrawLatex(0.1,0.7,stmp.str().c_str());
  stmp.str("");  stmp << "Total sum of NL1Mu: " << info.tot_NL1Mu;
  t->DrawLatex(0.1,0.6,stmp.str().c_str());
  stmp.str("");  stmp << "Total sum of NohMuL2: " << info.tot_NohMuL2;
  t->DrawLatex(0.1,0.5,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of L1 events: " << info.tot_NL1ValidEvt;
  t->DrawLatex(0.1,0.4,stmp.str().c_str());
  stmp.str("");  stmp << "Total # of L2 events: " << info.tot_NL2ValidEvt;
  t->DrawLatex(0.1,0.3,stmp.str().c_str());
  cdl2->SaveAs("delta_GenL2.png");
  }


  return 0;
}
