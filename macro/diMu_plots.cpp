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
#include <TLegend.h>
#include <TGraphAsymmErrors.h>
#include <TMultiGraph.h>
#include <TSystem.h>
#include <TLine.h>

using namespace std;

int diMu_plots() {

  // Parameters  
  FLAG *flag = new FLAG;
  flag->doSta = false;
  flag->doGlb = true;

  string data2010 = "/castor/cern.ch/user/m/miheejo/openHLT/cms413p3/HIRun2010-SDmaker_3SD_1CS_PDHIAllPhysicsZSv2_SD_MuHI-v1/openHLT_L1SingleMu3_L2Mu3.root";
	string data2011 = "/castor/cern.ch/user/m/miheejo/openHLT/RD2011/HIDiMuon_HIRun2011-PromptReco-v1_RECO/openhlt_PromptReco_181611_182099_L2Mu3_NHitQ.root";
  
  // Check trigger list
  vector<string> triglist;
//  triglist.push_back("HLT_HIL1DoubleMu0_HighQ_v1");
//  triglist.push_back("HLT_HIL2DoubleMu3_v1");
//  triglist.push_back("HLT_HIL3DoubleMuOpen_v1");
//  triglist.push_back("HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy_v1");
//  triglist.push_back("HLT_HIL2Mu3_v1");
//  triglist.push_back("HLT_HIL2Mu7_v1");
//  triglist.push_back("HLT_HIL2Mu15_v1");
//  triglist.push_back("HLT_HIL2Mu3_NHitQ_v1");
//  triglist.push_back("HLT_HIL3Mu3_v1");

	char title[256];
	char sub_title[256];

	char* particle_names[] = {"J-Psi","Upsilon","Z"};
	
  // Histograms
	TH1F *SingleGlb_Eta_2010[3];
	TH1F *SingleGlb_Phi_2010[3];
	TH1F *SingleGlb_Pt_2010[3];

	TH1F *SingleGlb_Eta_2011[3];
	TH1F *SingleGlb_Phi_2011[3];
	TH1F *SingleGlb_Pt_2011[3];
	
	TFile *output = new TFile("2011_histos.root","recreate");
	output->cd();
	
	for (int i = 0; i < 3; i++) {

		sprintf(title,"SingleGlb_eta_2010_%s",particle_names[i]);
		sprintf(sub_title,"%s;#eta",title);
		SingleGlb_Eta_2010[i] = new TH1F(title,sub_title,ETA,-2.4,2.4);
		SingleGlb_Eta_2010[i]->SetMarkerStyle(25);
		sprintf(title,"SingleGlb_phi_2010_%s",particle_names[i]);
		sprintf(sub_title,"%s;#phi",title);
		SingleGlb_Phi_2010[i] = new TH1F(title,sub_title,PHI,-PI,PI);
		SingleGlb_Phi_2010[i]->SetMarkerStyle(25);
		sprintf(title,"SingleGlb_pt_2010_%s",particle_names[i]);
		sprintf(sub_title,"%s;p_{T}",title);
		SingleGlb_Pt_2010[i] = new TH1F(title,sub_title,60,0,60);	
		SingleGlb_Pt_2010[i]->SetMarkerStyle(25);

		sprintf(title,"SingleGlb_eta_2011_%s",particle_names[i]);
		sprintf(sub_title,"%s;#eta",title);
		SingleGlb_Eta_2011[i] = new TH1F(title,sub_title,ETA,-2.4,2.4);
		SingleGlb_Eta_2011[i]->SetMarkerStyle(20);
		sprintf(title,"SingleGlb_phi_2011_%s",particle_names[i]);
		sprintf(sub_title,"%s;#phi",title);
		SingleGlb_Phi_2011[i] = new TH1F(title,sub_title,PHI,-PI,PI);
		SingleGlb_Phi_2011[i]->SetMarkerStyle(20);
		sprintf(title,"SingleGlb_pt_2011_%s",particle_names[i]);
		sprintf(sub_title,"%s;p_{T}",title);
		SingleGlb_Pt_2011[i] = new TH1F(title,sub_title,60,0,60);	
		SingleGlb_Pt_2011[i]->SetMarkerStyle(20);

	}

  TH2F *DoubleGlb_Ypt_2010 = new TH2F("DoubleGlb_ypt_2010","DoubleGlb_ypt_2010;double mu y;double mu p_{T}",ETA,-3.0,3.0,40,0,40);
  TH1F *DoubleGlb_Mass_2010 = new TH1F("DoubleGlb_mass_2010","DoubleGlb_mass_2010;double mu mass",110,0,110);
  TH1F *DoubleGlb_Y_2010 = new TH1F("DoubleGlb_y_2010","DoubleGlb_y_2010;double mu y",ETA,-3.0,3.0);
  TH1F *DoubleGlb_Pt_2010 = new TH1F("DoubleGlb_pt_2010","DoubleGlb_pt_2010;double mu p_{T}",40,0,40);
  TH1F *DoubleGlb_Phi_2010 = new TH1F("DoubleGlb_phi_2010","DoubleGlb_phi_2010;double mu #phi",PHI,-PI,PI);

  TH2F *DoubleGlb_Ypt_2011 = new TH2F("DoubleGlb_ypt_2011","DoubleGlb_ypt_2011;double mu y;double mu p_{T}",ETA,-3.0,3.0,40,0,40);
  TH1F *DoubleGlb_Mass_2011 = new TH1F("DoubleGlb_mass_2011","DoubleGlb_mass_2011;double mu mass",110,0,110);
  TH1F *DoubleGlb_Y_2011 = new TH1F("DoubleGlb_y_2011","DoubleGlb_y_2011;double mu y",ETA,-3.0,3.0);
  TH1F *DoubleGlb_Pt_2011 = new TH1F("DoubleGlb_pt_2011","DoubleGlb_pt_2011;double mu p_{T}",40,0,40);
  TH1F *DoubleGlb_Phi_2011 = new TH1F("DoubleGlb_phi_2011","DoubleGlb_phi_2011;double mu #phi",PHI,-PI,PI);

  // 2010 datafile 
  TCastorFile   *input_2010 = new TCastorFile(data2010.c_str());
  FriendMuTree  *mutree_2010 = new FriendMuTree(input_2010,true); // Load HLTMuTree
  HltTree       *ohTree_2010 = new HltTree(input_2010,true,"hltana/HltTree");      // Load HltTree

  TTree         *muon_tree_2010;                             // Hold HLTMuTree
  TTree         *open_tree_2010;                             // Hold HltTree
  MUTREE        *muTree_2010 = new MUTREE;

  // 2011 datafile 
  TCastorFile   *input_2011 = new TCastorFile(data2011.c_str());
  FriendMuTree  *mutree_2011 = new FriendMuTree(input_2011,true); // Load HLTMuTree
  HltTree       *ohTree_2011 = new HltTree(input_2011,true,"hltanalysis/HltTree");      // Load HltTree

  TTree         *muon_tree_2011;                             // Hold HLTMuTree
  TTree         *open_tree_2011;                             // Hold HltTree
  MUTREE        *muTree_2011 = new MUTREE;

  
  const unsigned int ntrig = triglist.size();
  int trig_2010[ntrig];
  int trig_2011[ntrig];
  open_tree_2010 = ohTree_2010->fChain;                           // Get TTree for trigger bits
  open_tree_2011 = ohTree_2011->fChain;                           // Get TTree for trigger bits
  for (int i=0; i < ntrig; i++) {
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

	int max_event_2010 = muon_tree_2010->GetEntries();
	int max_event_2011 = muon_tree_2011->GetEntries();
//	int max_event_2010 = 10000;
//	int max_event_2011 = 100000;

	
  // Loop over trees over 2010 trees
  for (int i=0; i<max_event_2010; i++) {
    muon_tree_2010->GetEntry(i);
    ohTree_2010->GetEntry(i);
    open_tree_2010->GetEntry(i);

/*    ////////// Check muon trigger list
    flag->trig = false;
    for (unsigned int tidx=0; tidx<ntrig; tidx++) {
      if (trig_2010[tidx]) {         // At least one of the muon trigger is fired.
        flag->trig = true;
        break;
      }
    }
    if (!flag->trig) continue;  // If no muon triggers fired, go to the next event!
*/
    TLorentzVector mu1, mu2, dimu;
    
    ////////// Load muons and fill up histograms
    for (int a=0; a < muTree_2010->nptl; a++) {
      if (flag->doGlb) {
        if(!isValidMu(flag, muTree_2010, a)) continue;    //Check glb muons are within acceptance range
      } else if (flag->doSta) {
        if(!isMuInAcc(flag, muTree_2010->eta[a], muTree_2010->pt[a])) continue;    //Check sta muons are within acceptance range
      }
	
		for (int b=a+1; b < muTree_2010->nptl; b++) {
		  if (flag->doGlb) {
				if(!isValidMu(flag, muTree_2010, b)) continue;    //Check glb muons are within acceptance range
		  } else if (flag->doSta) {
				if(!isMuInAcc(flag,muTree_2010->eta[b], muTree_2010->pt[b])) continue;    //Check sta muons are within acceptance range
		  }

			if (muTree_2010->charge[a] + muTree_2010->charge[b] != 0) continue;
			
			mu1.SetPtEtaPhiM(muTree_2010->pt[a],muTree_2010->eta[a],muTree_2010->phi[a],Mmu);
		  mu2.SetPtEtaPhiM(muTree_2010->pt[b],muTree_2010->eta[b],muTree_2010->phi[b],Mmu);

			dimu = mu1 + mu2;

		  DoubleGlb_Ypt_2010->Fill(dimu.Rapidity(),dimu.Pt());
		  DoubleGlb_Mass_2010->Fill(dimu.M());
		  DoubleGlb_Y_2010->Fill(dimu.Rapidity());
		  DoubleGlb_Pt_2010->Fill(dimu.Pt());
		  DoubleGlb_Phi_2010->Fill(dimu.Phi());

			if (dimu.M() > 3 && dimu.M() < 3.2) {
				SingleGlb_Eta_2010[0]->Fill(muTree_2010->eta[a]);
				SingleGlb_Eta_2010[0]->Fill(muTree_2010->eta[b]);
				SingleGlb_Phi_2010[0]->Fill(muTree_2010->phi[a]);
				SingleGlb_Phi_2010[0]->Fill(muTree_2010->phi[b]);
				SingleGlb_Pt_2010[0]->Fill(muTree_2010->pt[a]);
				SingleGlb_Pt_2010[0]->Fill(muTree_2010->pt[b]);
			}

			if (dimu.M() > 9 && dimu.M() < 10) {
				SingleGlb_Eta_2010[1]->Fill(muTree_2010->eta[a]);
				SingleGlb_Eta_2010[1]->Fill(muTree_2010->eta[b]);
				SingleGlb_Phi_2010[1]->Fill(muTree_2010->phi[a]);
				SingleGlb_Phi_2010[1]->Fill(muTree_2010->phi[b]);
				SingleGlb_Pt_2010[1]->Fill(muTree_2010->pt[a]);
				SingleGlb_Pt_2010[1]->Fill(muTree_2010->pt[b]);
			}

			if (dimu.M() > 85 && dimu.M() < 95) {
				SingleGlb_Eta_2010[2]->Fill(muTree_2010->eta[a]);
				SingleGlb_Eta_2010[2]->Fill(muTree_2010->eta[b]);
				SingleGlb_Phi_2010[2]->Fill(muTree_2010->phi[a]);
				SingleGlb_Phi_2010[2]->Fill(muTree_2010->phi[b]);
				SingleGlb_Pt_2010[2]->Fill(muTree_2010->pt[a]);
				SingleGlb_Pt_2010[2]->Fill(muTree_2010->pt[b]);
			}

			
// we want to cut on the mass between 3 and 3.2, and for the upsilon, cut off mass between 9 and 10, for the z, cut off mass between 85 and 95.
// we want to look at the single mu quality distributions, for these mass ranges. we will apply all of the quality cuts for the muons, and check the sign of
// the dimuon
	    }
    }
	if (i%10000 ==0)
    cout << "Event in 2010 datasets: " << i+1 << endl;

  }

  // Loop over trees over 2011 trees
  for (int i=0; i<max_event_2011; i++) {
    muon_tree_2011->GetEntry(i);
    ohTree_2011->GetEntry(i);
    open_tree_2011->GetEntry(i);

/*    ////////// Check muon trigger list
    flag->trig = false;
    for (unsigned int tidx=0; tidx<ntrig; tidx++) {
      if (trig_2011[tidx]) {         // At least one of the muon trigger is fired.
        flag->trig = true;
        break;
      }
    }
    if (!flag->trig) continue;  // If no muon triggers fired, go to the next event!
*/
    TLorentzVector mu1, mu2, dimu;
    
    ////////// Load muons and fill up histograms
    for (int a=0; a < muTree_2011->nptl; a++) {
      if (flag->doGlb) {
        if(!isValidMu(flag, muTree_2011, a)) continue;    //Check glb muons are within acceptance range
      } else if (flag->doSta) {
        if(!isMuInAcc(flag, muTree_2011->eta[a], muTree_2011->pt[a])) continue;    //Check sta muons are within acceptance range
      }
	
		for (int b=a+1; b < muTree_2011->nptl; b++) {
		  if (flag->doGlb) {
			if(!isValidMu(flag, muTree_2011, b)) continue;    //Check glb muons are within acceptance range
		  } else if (flag->doSta) {
			if(!isMuInAcc(flag,muTree_2011->eta[b], muTree_2011->pt[b])) continue;    //Check sta muons are within acceptance range
		  }

			if (muTree_2011->charge[a] + muTree_2011->charge[b] != 0) continue;
			
			mu1.SetPtEtaPhiM(muTree_2011->pt[a],muTree_2011->eta[a],muTree_2011->phi[a],Mmu);
		  mu2.SetPtEtaPhiM(muTree_2011->pt[b],muTree_2011->eta[b],muTree_2011->phi[b],Mmu);

			dimu = mu1 + mu2;

		  DoubleGlb_Ypt_2011->Fill(dimu.Rapidity(),dimu.Pt());
		  DoubleGlb_Mass_2011->Fill(dimu.M());
		  DoubleGlb_Y_2011->Fill(dimu.Rapidity());
		  DoubleGlb_Pt_2011->Fill(dimu.Pt());
		  DoubleGlb_Phi_2011->Fill(dimu.Phi());

			if (dimu.M() > 3 && dimu.M() < 3.2) {
				SingleGlb_Eta_2011[0]->Fill(muTree_2011->eta[a]);
				SingleGlb_Eta_2011[0]->Fill(muTree_2011->eta[b]);
				SingleGlb_Phi_2011[0]->Fill(muTree_2011->phi[a]);
				SingleGlb_Phi_2011[0]->Fill(muTree_2011->phi[b]);
				SingleGlb_Pt_2011[0]->Fill(muTree_2011->pt[a]);
				SingleGlb_Pt_2011[0]->Fill(muTree_2011->pt[b]);
			}

			if (dimu.M() > 9 && dimu.M() < 10) {
				SingleGlb_Eta_2011[1]->Fill(muTree_2011->eta[a]);
				SingleGlb_Eta_2011[1]->Fill(muTree_2011->eta[b]);
				SingleGlb_Phi_2011[1]->Fill(muTree_2011->phi[a]);
				SingleGlb_Phi_2011[1]->Fill(muTree_2011->phi[b]);
				SingleGlb_Pt_2011[1]->Fill(muTree_2011->pt[a]);
				SingleGlb_Pt_2011[1]->Fill(muTree_2011->pt[b]);
			}

			if (dimu.M() > 85 && dimu.M() < 95) {
				SingleGlb_Eta_2011[2]->Fill(muTree_2011->eta[a]);
				SingleGlb_Eta_2011[2]->Fill(muTree_2011->eta[b]);
				SingleGlb_Phi_2011[2]->Fill(muTree_2011->phi[a]);
				SingleGlb_Phi_2011[2]->Fill(muTree_2011->phi[b]);
				SingleGlb_Pt_2011[2]->Fill(muTree_2011->pt[a]);
				SingleGlb_Pt_2011[2]->Fill(muTree_2011->pt[b]);
			}
		  
	    }
    }
	if (i%10000 ==0)
    cout << "Event in 2011 datasets: " << i+1 << endl;

  }
  
  /*
  format_TH2(DoubleGlb_Ypt,"DoubleGlb_ypt","double mu y","double mu p_{T}",1,20);
  format_TH1(DoubleGlb_Mass,"DoubleGlb_mass","double mu mass","counts",1,20);
  format_TH1(DoubleGlb_Y,"DoubleGlb_y","double mu y","counts",1,20);
  format_TH1(DoubleGlb_Phi,"DoubleGlb_phi","double mu #phi","counts",1,20);
  format_TH1(DoubleGlb_Pt,"DoubleGlb_pt","double mu p_{T}","counts",1,20);
  */

  gROOT->Macro("~miheejo/public/HIMuTrig/JpsiStyle.C");    //For plot style
  
  TCanvas* cnv = new TCanvas("cnv","new canvas",1600,1200);
	gStyle->SetPadRightMargin(0.15);
	gStyle->SetOptStat("");
	
  TLegend* legCent = new TLegend(0.5,0.85,0.9,0.95);//top left
  legCent->SetTextSize(0.03);
  legCent->SetBorderSize(0);
  legCent->SetFillColor(0);

  cnv->Divide(3,2);

  double denominator_2010 = muon_tree_2010->GetEntries();
  double denominator_2011 = muon_tree_2011->GetEntries();

  double numerator_2010 = DoubleGlb_Mass_2010->GetEntries();
  double numerator_2011 = DoubleGlb_Mass_2011->GetEntries();

	int entries_2010;
	int entries_2011;
  
  cnv->cd(1);
  gStyle->SetPadRightMargin(0.15);
	gStyle->SetPadTopMargin(0.1);
	gStyle->SetOptTitle(1);
	cnv->Update();
	DoubleGlb_Ypt_2010->DrawNormalized("COLZ",1);

  cnv->cd(2);
  gStyle->SetPadRightMargin(0.15);
	gStyle->SetPadTopMargin(0.1);
	gStyle->SetOptTitle(1);
	cnv->Update();
  DoubleGlb_Ypt_2011->DrawNormalized("COLZ",1);

  cnv->cd(3);  
	gStyle->SetOptStat("");
  gStyle->SetPadRightMargin(0.05);
	entries_2010 = DoubleGlb_Mass_2010->GetEntries();
	entries_2011 = DoubleGlb_Mass_2011->GetEntries();
	sprintf(title,"2010 Data - %i Dimuons",entries_2010);
  legCent->AddEntry(DoubleGlb_Mass_2010,title,"p");
	sprintf(title,"2011 Data - %i Dimuons",entries_2011);
  legCent->AddEntry(DoubleGlb_Mass_2011,title,"p");

  DoubleGlb_Mass_2010->Sumw2();
  DoubleGlb_Mass_2010->SetMarkerStyle(25);
  DoubleGlb_Mass_2010->SetMarkerColor(1);
  DoubleGlb_Mass_2010->DrawNormalized("p e",1);
  DoubleGlb_Mass_2011->Sumw2();
  DoubleGlb_Mass_2011->SetMarkerStyle(20);
  DoubleGlb_Mass_2011->SetMarkerColor(2);
  DoubleGlb_Mass_2011->DrawNormalized("p e same",1);
  legCent->Draw();
  
  cnv->cd(4);
	gStyle->SetOptStat("");
  DoubleGlb_Y_2010->Sumw2();
  DoubleGlb_Y_2010->SetMarkerStyle(25);
  DoubleGlb_Y_2010->SetMarkerColor(1);
  DoubleGlb_Y_2010->DrawNormalized("p e",1);
  DoubleGlb_Y_2011->Sumw2();
  DoubleGlb_Y_2011->SetMarkerStyle(20);
  DoubleGlb_Y_2011->SetMarkerColor(2);
  DoubleGlb_Y_2011->DrawNormalized("p e same",1);
  legCent->Draw();

  cnv->cd(5);  
	gStyle->SetOptStat("");
  DoubleGlb_Pt_2010->Sumw2();
  DoubleGlb_Pt_2010->SetMarkerStyle(25);
  DoubleGlb_Pt_2010->SetMarkerColor(1);
  DoubleGlb_Pt_2010->DrawNormalized("p e",1);
  DoubleGlb_Pt_2011->Sumw2();
  DoubleGlb_Pt_2011->SetMarkerStyle(20);
  DoubleGlb_Pt_2011->SetMarkerColor(2);
  DoubleGlb_Pt_2011->DrawNormalized("p e same",1);
  legCent->Draw();

  cnv->cd(6);  
	gStyle->SetOptStat("");
  DoubleGlb_Phi_2010->Sumw2();
  DoubleGlb_Phi_2010->SetMarkerStyle(25);
  DoubleGlb_Phi_2010->SetMarkerColor(1);
  DoubleGlb_Phi_2010->DrawNormalized("p e",1);
  DoubleGlb_Phi_2011->Sumw2();
  DoubleGlb_Phi_2011->SetMarkerStyle(20);
  DoubleGlb_Phi_2011->SetMarkerColor(2);
  DoubleGlb_Phi_2011->DrawNormalized("p e same",1);
  legCent->Draw();

	cnv->Update();
  
  if (flag->doGlb) {
	cnv->Print("diMu_plots_Global.pdf");
  } else if (flag->doSta) {
	cnv->Print("diMu_plots_STA.pdf");
  }
  
  // Draw final histograms and save it into .png files
	cnv = new TCanvas("cnv","cnv",800,600);

	legCent = new TLegend(0.15,0.90,0.2,1.0);
  legCent->SetFillColor(0);
  legCent->SetBorderSize(0);
  legCent->SetTextSize(0.05);

	double marker_size = 2.0;
	double label_size = 0.05;
	
  TLatex *lax = new TLatex();
  lax->SetTextSize(0.1);
	stringstream lax_title;
	
	TPad *pad1;
	TPad *pad2;

	TH1F *ratio_2011;

	char count_2010[512];
	char count_2011[512];
	
	TLine* l3a;
	
	gStyle->SetPalette(1,0);
	gStyle->SetTitleOffset(0.1);
	//	gStyle->SetPadLeftMargin(0.17);
//	gStyle->SetPadBottomMargin(0.2);
//	gStyle->SetPadTopMargin(0.1);
//	gStyle->SetPadRightMargin(0.02);
//	gStyle->SetOptTitle(1);
//	gStyle->SetTextSize(0.03);
//	gStyle->SetMarkerSize(1);
//	gStyle->SetMarkerStyle(20);

//	gStyle->SetOptTitle(0);
//	gStyle->SetStatX(0.8);
//	gStyle->SetStatY(1.0);
//	gStyle->SetStatW(0.2);
//	gStyle->SetStatH(0.2);
//	gStyle->SetOptStat("mn");
	
	for (int i = 0; i < 3; i++) {
// START Phi	
	cnv = new TCanvas("cnv","cnv",1300,1000);
	
	pad1 = new TPad("pad1", "The pad 70% of the height",0.0,0.3,1.0,1.0,0);
	pad1->SetBottomMargin(0.0);
	pad2 = new TPad("pad2", "The pad 30% of the height",0.0,0.0,1.0,0.3,0);
	pad2->SetTopMargin(0.0);

	pad2->SetBottomMargin(0.4);
	pad1->Draw();
	pad2->Draw();

	pad1->cd();
	pad1->SetLogy(0);

	gStyle->SetMarkerSize(1);
	entries_2010 = SingleGlb_Phi_2010[i]->GetEntries();
	SingleGlb_Phi_2010[i]->GetXaxis()->SetLabelSize(label_size);
	SingleGlb_Phi_2010[i]->GetYaxis()->SetLabelSize(label_size);
	SingleGlb_Phi_2010[i]->SetMinimum(0);
	SingleGlb_Phi_2010[i]->Sumw2();
  SingleGlb_Phi_2010[i]->SetMarkerStyle(25);
  SingleGlb_Phi_2010[i]->SetMarkerSize(marker_size);
	SingleGlb_Phi_2010[i]->Scale(1.0/SingleGlb_Phi_2010[i]->GetEntries());
  SingleGlb_Phi_2010[i]->DrawNormalized("p e",1);
	cnv->Update();
	gStyle->SetStatX(0.8);
	gStyle->SetStatY(1.0);
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.2);
	gStyle->SetOptStat("mn");
	cnv->Update();
	entries_2011 = SingleGlb_Phi_2011[i]->GetEntries();
  SingleGlb_Phi_2011[i]->Sumw2();
  SingleGlb_Phi_2011[i]->SetMarkerStyle(20);
  SingleGlb_Phi_2011[i]->SetMarkerSize(marker_size);
  SingleGlb_Phi_2011[i]->SetMarkerColor(kRed);
	SingleGlb_Phi_2011[i]->Scale(1.0/SingleGlb_Phi_2011[i]->GetEntries());
  SingleGlb_Phi_2011[i]->DrawNormalized("p e sames",1);
	gStyle->SetStatX(1.0);
	cnv->Update();
	sprintf(count_2010,"  2010 Data - %i Muons", entries_2010);
	sprintf(count_2011,"  2011 Data - %i Muons", entries_2011);
	legCent->Clear();
	legCent->AddEntry(SingleGlb_Phi_2010[i],count_2010,"lp");
	legCent->AddEntry(SingleGlb_Phi_2011[i],count_2011,"lp");
  legCent->Draw();
	cnv->Update();

	pad2->cd();

	ratio_2011 = (TH1F*)SingleGlb_Phi_2011[i]->Clone("ratio_2011");
	ratio_2011->Sumw2();
	ratio_2011->Divide(SingleGlb_Phi_2010[i]);
	ratio_2011->SetMarkerStyle(29);
	ratio_2011->SetMarkerColor(kViolet);
	ratio_2011->SetMarkerSize(marker_size*5.0/3.0);

	ratio_2011->SetMinimum(0);
	ratio_2011->SetMaximum(ratio_2011->GetMaximum()+0.1);

	gStyle->SetStatX(0.55);
	gStyle->SetStatY(0.6);
	gStyle->SetStatW(0.1);
	gStyle->SetStatH(0.3);
	gStyle->SetOptStat("");

	gStyle->SetMarkerSize(1);
	ratio_2011->GetYaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011->GetYaxis()->SetNdivisions(505);
	ratio_2011->GetYaxis()->SetTitle("2011/2010");
	ratio_2011->GetYaxis()->SetTitleSize(0.1);

	ratio_2011->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011->GetXaxis()->SetTitleSize(0.15);
	ratio_2011->GetXaxis()->SetTitle("#phi");
	
	gStyle->SetOptTitle(0);
	gPad->SetLogy(0);
	
	ratio_2011->Draw();
	l3a = new TLine(-PI,1.0,PI,1.0);
	l3a->SetHorizontal(1);
	l3a->SetLineStyle(2);
	l3a->SetX2(PI);
	l3a->Draw("same");

	sprintf(title,"SingleGlb_Phi_%s.pdf",particle_names[i]);
	cnv->SaveAs(title);

	cnv->Clear(); cnv->Draw();
// END Phi

// START Pt	
	cnv = new TCanvas("cnv","cnv",1300,1000);
	
	pad1 = new TPad("pad1", "The pad 70% of the height",0.0,0.3,1.0,1.0,0);
	pad1->SetBottomMargin(0.0);
	pad2 = new TPad("pad2", "The pad 30% of the height",0.0,0.0,1.0,0.3,0);
	pad2->SetTopMargin(0.0);

	pad2->SetBottomMargin(0.4);
	pad1->Draw();
	pad2->Draw();

	pad1->cd();
	pad1->SetLogy(1);

	gStyle->SetMarkerSize(1);
	entries_2010 = SingleGlb_Pt_2010[i]->GetEntries();
	SingleGlb_Pt_2010[i]->GetYaxis()->SetLabelSize(label_size);
	SingleGlb_Pt_2010[i]->SetMinimum(1);
	SingleGlb_Pt_2010[i]->Sumw2();
  SingleGlb_Pt_2010[i]->SetMarkerStyle(25);
  SingleGlb_Pt_2010[i]->SetMarkerSize(marker_size);
	SingleGlb_Pt_2010[i]->Scale(1.0/SingleGlb_Pt_2010[i]->GetEntries());
  SingleGlb_Pt_2010[i]->DrawNormalized("p e",1);
	cnv->Update();
	gStyle->SetStatX(0.8);
	gStyle->SetStatY(1.0);
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.2);
	gStyle->SetOptStat("mn");
	cnv->Update();
  SingleGlb_Pt_2011[i]->Sumw2();
  SingleGlb_Pt_2011[i]->SetMarkerStyle(20);
  SingleGlb_Pt_2011[i]->SetMarkerColor(kRed);
  SingleGlb_Pt_2011[i]->SetMarkerSize(marker_size);
	SingleGlb_Pt_2011[i]->Scale(1.0/SingleGlb_Pt_2011[i]->GetEntries());
  SingleGlb_Pt_2011[i]->DrawNormalized("p e sames",1);
	gStyle->SetStatX(1.0);
	entries_2010 = SingleGlb_Pt_2010[i]->GetEntries();
	entries_2011 = SingleGlb_Pt_2011[i]->GetEntries();
	sprintf(count_2010,"  2010 Data - %i Muons", entries_2010);
	sprintf(count_2011,"  2011 Data - %i Muons", entries_2011);
	legCent->Clear();
	legCent->AddEntry(SingleGlb_Pt_2010[i],count_2010,"lp");
	legCent->AddEntry(SingleGlb_Pt_2011[i],count_2011,"lp");
  legCent->Draw();
	cnv->Update();

	pad2->cd();

	ratio_2011 = (TH1F*)SingleGlb_Pt_2011[i]->Clone("ratio_2011");
	ratio_2011->Sumw2();
	ratio_2011->GetYaxis()->SetTitle("2011/2010");
	ratio_2011->GetYaxis()->SetTitleSize(0.1);
	ratio_2011->Divide(SingleGlb_Pt_2010[i]);
	ratio_2011->SetMarkerColor(kViolet);
	ratio_2011->SetMarkerStyle(29);
	ratio_2011->SetMarkerSize(marker_size*5.0/3.0);

	ratio_2011->SetMinimum(0);
	ratio_2011->SetMaximum(ratio_2011->GetMaximum()+0.1);

	gStyle->SetStatX(0.55);
	gStyle->SetStatY(0.6);
	gStyle->SetStatW(0.1);
	gStyle->SetStatH(0.3);
	gStyle->SetOptStat("");

	gStyle->SetMarkerSize(1);
	ratio_2011->GetYaxis()->SetTitle("2011/2010");
	ratio_2011->GetYaxis()->SetTitleSize(0.1);
	ratio_2011->GetYaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011->GetYaxis()->SetNdivisions(505);

	ratio_2011->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011->GetXaxis()->SetTitleSize(0.15);
	ratio_2011->GetXaxis()->SetTitle("p_{T}");
	
	gStyle->SetOptTitle(0);
	gPad->SetLogy(0);
	
	ratio_2011->Draw();
	l3a = new TLine(0,1.0,60,1.0);
	l3a->SetHorizontal(1);
	l3a->SetLineStyle(2);
	l3a->SetX2(60);
	l3a->Draw("same");

	sprintf(title,"SingleGlb_Pt_%s.pdf",particle_names[i]);
	cnv->SaveAs(title);
	cnv->Clear(); cnv->Draw();
// END Pt
	
	// START Eta
	cnv = new TCanvas("cnv","cnv",1300,1000);
	
	pad1 = new TPad("pad1", "The pad 70% of the height",0.0,0.3,1.0,1.0,0);
	pad1->SetBottomMargin(0.0);
	pad2 = new TPad("pad2", "The pad 30% of the height",0.0,0.0,1.0,0.3,0);
	pad2->SetTopMargin(0.0);

	pad2->SetBottomMargin(0.4);
	pad1->Draw();
	pad2->Draw();

	pad1->cd();
	pad1->SetLogy(0);

	gStyle->SetMarkerSize(1);
	SingleGlb_Eta_2010[i]->GetXaxis()->SetLabelSize(label_size);
	SingleGlb_Eta_2010[i]->GetYaxis()->SetLabelSize(label_size);
	SingleGlb_Eta_2010[i]->SetMinimum(0);
	SingleGlb_Eta_2010[i]->Sumw2();
  SingleGlb_Eta_2010[i]->SetMarkerStyle(25);
  SingleGlb_Eta_2010[i]->SetMarkerSize(marker_size);
	SingleGlb_Eta_2010[i]->Scale(1.0/SingleGlb_Eta_2010[i]->GetEntries());
  SingleGlb_Eta_2010[i]->DrawNormalized("p e",1);
	cnv->Update();
	gStyle->SetStatX(0.8);
	gStyle->SetStatY(1.0);
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.2);
	gStyle->SetOptStat("mn");
	cnv->Update();
	entries_2010 = SingleGlb_Eta_2010[i]->GetEntries();
	cnv->Update();
  SingleGlb_Eta_2011[i]->Sumw2();
  SingleGlb_Eta_2011[i]->SetMarkerStyle(20);
  SingleGlb_Eta_2011[i]->SetMarkerColor(kRed);
  SingleGlb_Eta_2011[i]->SetMarkerSize(marker_size);
	SingleGlb_Eta_2011[i]->Scale(1.0/SingleGlb_Eta_2011[i]->GetEntries());
  SingleGlb_Eta_2011[i]->DrawNormalized("p e sames",1);
	gStyle->SetStatX(1.0);
	entries_2010 = SingleGlb_Eta_2010[i]->GetEntries();
	entries_2011 = SingleGlb_Eta_2011[i]->GetEntries();
	sprintf(count_2010,"  2010 Data - %i Muons", entries_2010);
	sprintf(count_2011,"  2011 Data - %i Muons", entries_2011);
	legCent->Clear();
	legCent->AddEntry(SingleGlb_Eta_2010[i],count_2010,"lp");
	legCent->AddEntry(SingleGlb_Eta_2011[i],count_2011,"lp");
  legCent->Draw();
	cnv->Update();

	pad2->cd();

	ratio_2011 = (TH1F*)SingleGlb_Eta_2011[i]->Clone("ratio_2011");
	ratio_2011->Sumw2();
	ratio_2011->GetYaxis()->SetTitle("2011/2010");
	ratio_2011->GetYaxis()->SetTitleSize(0.1);
	ratio_2011->Divide(SingleGlb_Eta_2010[i]);
	ratio_2011->SetMarkerColor(kViolet);
	ratio_2011->SetMarkerStyle(29);
	ratio_2011->SetMarkerSize(marker_size*5.0/3.0);

	ratio_2011->SetMinimum(0);
	ratio_2011->SetMaximum(ratio_2011->GetMaximum()+0.1);

	gStyle->SetStatX(0.55);
	gStyle->SetStatY(0.6);
	gStyle->SetStatW(0.1);
	gStyle->SetStatH(0.3);
	gStyle->SetOptStat("");

	gStyle->SetMarkerSize(1);
	ratio_2011->GetYaxis()->SetTitle("2011/2010");
	ratio_2011->GetYaxis()->SetTitleSize(0.1);
	ratio_2011->GetYaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011->GetYaxis()->SetNdivisions(505);

	ratio_2011->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011->GetXaxis()->SetTitleSize(0.15);
	ratio_2011->GetXaxis()->SetTitle("#eta");
	
	gStyle->SetOptTitle(0);
	gPad->SetLogy(0);
	
	ratio_2011->Draw();
	l3a = new TLine(-2.4,1.0,2.4,1.0);
	l3a->SetHorizontal(1);
	l3a->SetLineStyle(2);
	l3a->SetX2(2.4);
	l3a->Draw("same");

	sprintf(title,"SingleGlb_Eta_%s.pdf",particle_names[i]);
	cnv->SaveAs(title);
	cnv->Clear(); cnv->Draw();
// END Eta
  }

	output->Write();
	output->Close();
	
  return 0;
}
