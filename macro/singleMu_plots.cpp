#ifndef MATCHMU
#define MATCHMU
#include "matchMu.h"
#include "matchMu_tree.h"
#endif

#include <sstream>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLatex.h>
#include <TLegend.h>

using namespace std;

int singleMu_plots() {

  // Parameters  
  FLAG *flag = new FLAG;
  flag->doSta = true;
  flag->doGlb = false;
  
  string data2010  = "/castor/cern.ch/user/m/miheejo/openHLT/cms442p5/HICorePhysics_Skim_MinimumBias_RAW/openhlt_2010HICorePhysicsMB.root";
  string data2011  = "/castor/cern.ch/user/m/miheejo/openHLT/RD2011/HIData2011_rawToRecoV3_LSF/openhlt_HIData2011_rawToRecoV3_LSF.root";

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
  TH2F *SingleGlb_Etaphi_2010 = new TH2F("SingleGlb_etaphi_2010","SingleGlb_etaphi_2010;single mu #eta;single mu #phi",ETA,-2.4,2.4,20,-PI,PI);
  TH2F *SingleGlb_Etaphi_2011 = new TH2F("SingleGlb_etaphi_2011","SingleGlb_etaphi_2011;single mu #eta;single mu #phi",ETA,-2.4,2.4,20,-PI,PI);

  TH1F *SingleGlb_Eta_2010 = new TH1F("SingleGlb_eta_2010","SingleGlb_eta_2010;single mu #eta",ETA,-2.4,2.4);
  TH1F *SingleGlb_Eta_2011 = new TH1F("SingleGlb_eta_2011","SingleGlb_eta_2011;single mu #eta",ETA,-2.4,2.4);
  TH1F *SingleGlb_Phi_2010 = new TH1F("SingleGlb_phi_2010","SingleGlb_phi_2010;single mu #phi",20,-PI,PI);
  TH1F *SingleGlb_Phi_2011 = new TH1F("SingleGlb_phi_2011","SingleGlb_phi_2011;single mu #phi",20,-PI,PI);
  TH1F *SingleGlb_Pt_2010 = new TH1F("SingleGlb_pt_2010","SingleGlb_pt_2010;single mu p_{T}",PT,0,20);
  TH1F *SingleGlb_Pt_2011 = new TH1F("SingleGlb_pt_2011","SingleGlb_pt_2011;single mu p_{T}",PT,0,20);

  TH2F *SingleGlb_Etapt_2010_qual = new TH2F("SingleGlb_etapt_2010_qual","SingleGlb_etapt_2010_qual;single mu #eta;single mu p_{T}",ETA,-2.4,2.4,PT,0,20);
  TH2F *SingleGlb_Etapt_2011_qual = new TH2F("SingleGlb_etapt_2011_qual","SingleGlb_etapt_2011_qual;single mu #eta;single mu p_{T}",ETA,-2.4,2.4,PT,0,20);
  TH2F *SingleGlb_Etaphi_2010_qual = new TH2F("SingleGlb_etaphi_2010_qual","SingleGlb_etaphi_2010_qual;single mu #eta;single mu #phi",ETA,-2.4,2.4,20,-PI,PI);
  TH2F *SingleGlb_Etaphi_2011_qual = new TH2F("SingleGlb_etaphi_2011_qual","SingleGlb_etaphi_2011_qual;single mu #eta;single mu #phi",ETA,-2.4,2.4,20,-PI,PI);

  TH1F *SingleGlb_Eta_2010_qual = new TH1F("SingleGlb_eta_2010_qual","SingleGlb_eta_2010_qual;single mu #eta",ETA,-2.4,2.4);
  TH1F *SingleGlb_Eta_2011_qual = new TH1F("SingleGlb_eta_2011_qual","SingleGlb_eta_2011_qual;single mu #eta",ETA,-2.4,2.4);
  TH1F *SingleGlb_Phi_2010_qual = new TH1F("SingleGlb_phi_2010_qual","SingleGlb_phi_2010_qual;single mu #phi",20,-PI,PI);
  TH1F *SingleGlb_Phi_2011_qual = new TH1F("SingleGlb_phi_2011_qual","SingleGlb_phi_2011_qual;single mu #phi",20,-PI,PI);
  TH1F *SingleGlb_Pt_2010_qual = new TH1F("SingleGlb_pt_2010_qual","SingleGlb_pt_2010_qual;single mu p_{T}",PT,0,20);
  TH1F *SingleGlb_Pt_2011_qual = new TH1F("SingleGlb_pt_2011_qual","SingleGlb_pt_2011_qual;single mu p_{T}",PT,0,20);


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


  int nevt_2010=0;                  // # of events that has at least 1 muon trigger fired
  int nevt_2010_qual=0;                  // # of events that has at least 1 muon trigger fired
  // Loop over trees over 2010 trees
  for (int i=0; i<muon_tree_2010->GetEntries(); i++) {
    muon_tree_2010->GetEntry(i);
    ohTree_2010->GetEntry(i);
    open_tree_2010->GetEntry(i);

    ////////// Check muon trigger list
/*    flag->trig = false;
    for (unsigned int tidx=0; tidx<ntrig; tidx++) {
      if (trig_2010[tidx]) {         // At least one of the muon trigger is fired.
        flag->trig = true;
        break;
      }
    }
    if (!flag->trig) continue;  // If no muon triggers fired, go to the next event!
*/    
    nevt_2010++;
    bool qual=false;
    ////////// Load muons and fill up histograms
    for (int a=0; a < muTree_2010->nptl; a++) {

      SingleGlb_Etapt_2010->Fill(muTree_2010->eta[a],muTree_2010->pt[a]);
      SingleGlb_Etaphi_2010->Fill(muTree_2010->eta[a],muTree_2010->phi[a]);
      SingleGlb_Eta_2010->Fill(muTree_2010->eta[a]);
      SingleGlb_Pt_2010->Fill(muTree_2010->pt[a]);
      SingleGlb_Phi_2010->Fill(muTree_2010->phi[a]);

      if (flag->doGlb) {
        if(!isValidMu(flag, muTree_2010, a)) continue;    //Check glb muons are within acceptance range
      } else if (flag->doSta) {
        if(!isMuInAcc(flag, muTree_2010->eta[a], muTree_2010->pt[a])) continue;    //Check sta muons are within acceptance range
      }
      
      qual = true;

      SingleGlb_Etapt_2010_qual->Fill(muTree_2010->eta[a],muTree_2010->pt[a]);
      SingleGlb_Etaphi_2010_qual->Fill(muTree_2010->eta[a],muTree_2010->phi[a]);
      SingleGlb_Eta_2010_qual->Fill(muTree_2010->eta[a]);
      SingleGlb_Pt_2010_qual->Fill(muTree_2010->pt[a]);
      SingleGlb_Phi_2010_qual->Fill(muTree_2010->phi[a]);

    }
    if (qual) nevt_2010_qual++;

    if (i%1000 ==0)
    cout << "Event in 2010 datasets: " << i+1 << endl;
  }

  int nevt_2011=0;                  // # of events that has at least 1 muon trigger fired
  int nevt_2011_qual=0;                  // # of events that has at least 1 muon trigger fired
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

    nevt_2011++;
    bool qual=false;
    ////////// Load muons and fill up histograms
    for (int a=0; a < muTree_2011->nptl; a++) {
      SingleGlb_Etapt_2011->Fill(muTree_2011->eta[a],muTree_2011->pt[a]);
      SingleGlb_Etaphi_2011->Fill(muTree_2011->eta[a],muTree_2011->phi[a]);
      SingleGlb_Eta_2011->Fill(muTree_2011->eta[a]);
      SingleGlb_Pt_2011->Fill(muTree_2011->pt[a]);
      SingleGlb_Phi_2011->Fill(muTree_2011->phi[a]);

      if (flag->doGlb) {
        if(!isValidMu(flag, muTree_2011, a)) continue;    //Check glb muons are within acceptance range
      } else if (flag->doSta) {
        if(!isMuInAcc(flag, muTree_2011->eta[a], muTree_2011->pt[a])) continue;    //Check sta muons are within acceptance range
      }
      qual = true;
      
      SingleGlb_Etapt_2011_qual->Fill(muTree_2011->eta[a],muTree_2011->pt[a]);
      SingleGlb_Etaphi_2011_qual->Fill(muTree_2011->eta[a],muTree_2011->phi[a]);
      SingleGlb_Eta_2011_qual->Fill(muTree_2011->eta[a]);
      SingleGlb_Pt_2011_qual->Fill(muTree_2011->pt[a]);
      SingleGlb_Phi_2011_qual->Fill(muTree_2011->phi[a]);

    }
    if (qual) nevt_2011_qual++;

    if (i%1000 ==0)
    cout << "Event in 2011 datasets: " << i+1 << endl;

  }

  double ratio_2010 = SingleGlb_Eta_2010->GetEntries()/nevt_2010;
  double ratio_2011 = SingleGlb_Eta_2011->GetEntries()/nevt_2011;
  double ratio_2010_qual = SingleGlb_Eta_2010_qual->GetEntries()/nevt_2010_qual;
  double ratio_2011_qual = SingleGlb_Eta_2011_qual->GetEntries()/nevt_2011_qual;
  
  // Draw final histograms and save it into .png files
  gROOT->Macro("~miheejo/public/HIMuTrig/TrigStyle.C");    //For plot style
  TCanvas *canv = new TCanvas("canv","canv",800,600);
  canv->Draw();
  SingleGlb_Etapt_2010->DrawNormalized("colz",ratio_2010);
  canv->SaveAs("SingleGlb_Etapt_2010.png");
  canv->Clear();  canv->Draw();
  SingleGlb_Etapt_2011->DrawNormalized("colz",ratio_2011);
  canv->SaveAs("SingleGlb_Etapt_2011.png");
  canv->Clear();  canv->Draw();
  SingleGlb_Etaphi_2010->DrawNormalized("colz",ratio_2010);
  canv->SaveAs("SingleGlb_Etaphi_2010.png");
  canv->Clear();  canv->Draw();
  SingleGlb_Etaphi_2011->DrawNormalized("colz",ratio_2011);
  canv->SaveAs("SingleGlb_Etaphi_2011.png");
  canv->Clear();  canv->Draw();
  SingleGlb_Etapt_2010_qual->DrawNormalized("colz",ratio_2010_qual);
  canv->SaveAs("SingleGlb_Etapt_2010_qual.png");
  canv->Clear();  canv->Draw();
  SingleGlb_Etapt_2011_qual->DrawNormalized("colz",ratio_2011_qual);
  canv->SaveAs("SingleGlb_Etapt_2011_qual.png");
  canv->Clear();  canv->Draw();
  SingleGlb_Etaphi_2010_qual->DrawNormalized("colz",ratio_2010_qual);
  canv->SaveAs("SingleGlb_Etaphi_2010_qual.png");
  canv->Clear();  canv->Draw();
  SingleGlb_Etaphi_2011_qual->DrawNormalized("colz",ratio_2011_qual);
  canv->SaveAs("SingleGlb_Etaphi_2011_qual.png");
  delete canv;


  TLegend *leg = new TLegend(0.5,0.70,0.65,0.83);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.05);

  TLegend *leg2 = new TLegend(0.35,0.50,0.45,0.63);
  leg2->SetFillColor(0);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.05);

  TLatex *lax = new TLatex();
  lax->SetTextSize(0.04);

  canv = new TCanvas("canv","canv",1300,1000);
  canv->Divide(2,2);
  canv->cd(1);
  SingleGlb_Eta_2010_qual->Sumw2();
  SingleGlb_Eta_2010_qual->SetMarkerStyle(20);
  SingleGlb_Eta_2010_qual->DrawNormalized("p e",ratio_2010_qual);
  SingleGlb_Eta_2011_qual->Sumw2();
  SingleGlb_Eta_2011_qual->SetMarkerColor(kRed);
  SingleGlb_Eta_2011_qual->SetMarkerStyle(20);
  SingleGlb_Eta_2011_qual->DrawNormalized("p e same",ratio_2011_qual);
  leg->AddEntry(SingleGlb_Eta_2010_qual,"2010 data","lp");
  leg->AddEntry(SingleGlb_Eta_2011_qual,"2011 data","lp");
  leg2->AddEntry(SingleGlb_Eta_2010_qual,"2010 data","lp");
  leg2->AddEntry(SingleGlb_Eta_2011_qual,"2011 data","lp");
  leg->Draw();
  canv->cd(2);
  SingleGlb_Pt_2010_qual->Sumw2();
  SingleGlb_Pt_2010_qual->SetMarkerStyle(20);
  SingleGlb_Pt_2010_qual->DrawNormalized("p e",ratio_2010_qual);
  SingleGlb_Pt_2011_qual->Sumw2();
  SingleGlb_Pt_2011_qual->SetMarkerColor(kRed);
  SingleGlb_Pt_2011_qual->SetMarkerStyle(20);
  SingleGlb_Pt_2011_qual->DrawNormalized("p e same",ratio_2011_qual);
  leg->Draw();
  canv->cd(3);
  SingleGlb_Phi_2011_qual->Sumw2();
  SingleGlb_Phi_2011_qual->SetMarkerColor(kRed);
  SingleGlb_Phi_2011_qual->SetMarkerStyle(20);
  SingleGlb_Phi_2011_qual->DrawNormalized("p e",ratio_2011_qual);
  SingleGlb_Phi_2010_qual->Sumw2();
  SingleGlb_Phi_2010_qual->SetMarkerStyle(20);
  SingleGlb_Phi_2010_qual->DrawNormalized("p e same",ratio_2010_qual);
  leg->Draw();
  canv->cd(4);
  stringstream title;
  title.str("");
  title << "2010 # muons (mu trig fired + quality cuts): " << SingleGlb_Eta_2010_qual->GetEntries();
  lax->DrawLatex(0.0,0.95,title.str().c_str());
  title.str("");
  title << "2010 # events (mu trig fired + quality cuts): " << nevt_2010_qual;
  lax->DrawLatex(0.0,0.90,title.str().c_str());
  title.str("");
  title << "2011 # muons (mu trig fired + quality cuts): " << SingleGlb_Eta_2011_qual->GetEntries();
  lax->DrawLatex(0.0,0.85,title.str().c_str());
  title.str("");
  title << "2011 # events (mu trig fired + quality cuts): " << nevt_2011_qual;
  lax->DrawLatex(0.0,0.80,title.str().c_str());
  canv->SaveAs("SingleGlb_qual.png");

  canv->Clear();  canv->Divide(2,2);
  canv->cd(1);

  SingleGlb_Eta_2011->Sumw2();
  SingleGlb_Eta_2011->SetMarkerColor(kRed);
  SingleGlb_Eta_2011->SetMarkerStyle(20);
  SingleGlb_Eta_2011->DrawNormalized("p e",ratio_2011);
  SingleGlb_Eta_2010->Sumw2();
  SingleGlb_Eta_2010->SetMarkerStyle(20);
  SingleGlb_Eta_2010->DrawNormalized("p e same",ratio_2010);
  leg->Draw();

  canv->cd(2);
  SingleGlb_Pt_2011->Sumw2();
  SingleGlb_Pt_2011->SetMarkerColor(kRed);
  SingleGlb_Pt_2011->SetMarkerStyle(20);
  SingleGlb_Pt_2011->DrawNormalized("p e",ratio_2011);
  SingleGlb_Pt_2010->Sumw2();
  SingleGlb_Pt_2010->SetMarkerStyle(20);
  SingleGlb_Pt_2010->DrawNormalized("p e same",ratio_2010);
  leg->Draw();

  canv->cd(3);
  SingleGlb_Phi_2011->Sumw2();
  SingleGlb_Phi_2011->SetMarkerColor(kRed);
  SingleGlb_Phi_2011->SetMarkerStyle(20);
  SingleGlb_Phi_2011->DrawNormalized("p e",ratio_2011);
  SingleGlb_Phi_2010->Sumw2();
  SingleGlb_Phi_2010->SetMarkerStyle(20);
  SingleGlb_Phi_2010->DrawNormalized("p e same",ratio_2010);
  leg2->Draw();
  canv->cd(4);
  title.str("");
  title << "2010 # muons (mu trig fired): " << SingleGlb_Eta_2010->GetEntries();
  lax->DrawLatex(0.0,0.95,title.str().c_str());
  title.str("");
  title << "2010 # events (mu trig fired): " << nevt_2010;
  lax->DrawLatex(0.0,0.90,title.str().c_str());
  title.str("");
  title << "2011 # muons (mu trig fired): " << SingleGlb_Eta_2011->GetEntries();
  lax->DrawLatex(0.0,0.85,title.str().c_str());
  title.str("");
  title << "2011 # events (mu trig fired): " << nevt_2011;
  lax->DrawLatex(0.0,0.80,title.str().c_str());
  canv->SaveAs("SingleGlb_noqual.png");

  
  return 0;
}
