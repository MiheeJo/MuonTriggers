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
  triglist.push_back("HLT_HIL1DoubleMu0_HighQ_v1");
  triglist.push_back("HLT_HIL2DoubleMu3_v1");
  triglist.push_back("HLT_HIL3DoubleMuOpen_v1");
  triglist.push_back("HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy_v1");
  triglist.push_back("HLT_HIL2Mu3_v1");
  triglist.push_back("HLT_HIL2Mu7_v1");
  triglist.push_back("HLT_HIL2Mu15_v1");
  triglist.push_back("HLT_HIL2Mu3_NHitQ_v1");
  triglist.push_back("HLT_HIL3Mu3_v1");

  int MASS = 20;
  double Xaxis[20] = {0,1,2,3,4,5,6,7,8,9,10,20,30,40,50,60,70,80,90,100};

	char title[256];
	char sub_title[256];

	char* particle_names[] = {"J/Psi","Upsilon","Z"};
	
  // Histograms
	TH1F *SingleGlb_Eta_2010[3];
	TH1F *SingleGlb_Phi_2010[3];
	TH1F *SingleGlb_Pt_2010[3];

	TH1F *SingleGlb_Eta_2011[3];
	TH1F *SingleGlb_Phi_2011[3];
	TH1F *SingleGlb_Pt_2011[3];
	
	for (int i = 0; i < 3; i++) {

		sprintf(title,"SingleGlb_eta_2010_%s",particle_names[i]);
		sprintf(sub_title,"%s;#eta;counts",title);
		SingleGlb_Eta_2010[i] = new TH1F(title,sub_title,ETA,-2.4,2.4);
		sprintf(title,"SingleGlb_phi_2010_%s",particle_names[i]);
		sprintf(sub_title,"%s;#phi;counts",title);
		SingleGlb_Phi_2010[i] = new TH1F(title,sub_title,PHI,-PI,PI);
		sprintf(title,"SingleGlb_pt_2010_%s",particle_names[i]);
		sprintf(sub_title,"%s;p_{T};counts",title);
		SingleGlb_Pt_2010[i] = new TH1F(title,sub_title,60,0,60);	

		sprintf(title,"SingleGlb_eta_2011_%s",particle_names[i]);
		sprintf(sub_title,"%s;#eta;counts",title);
		SingleGlb_Eta_2011[i] = new TH1F(title,sub_title,ETA,-2.4,2.4);
		sprintf(title,"SingleGlb_phi_2011_%s",particle_names[i]);
		sprintf(sub_title,"%s;#phi;counts",title);
		SingleGlb_Phi_2011[i] = new TH1F(title,sub_title,PHI,-PI,PI);
		sprintf(title,"SingleGlb_pt_2011_%s",particle_names[i]);
		sprintf(sub_title,"%s;p_{T};counts",title);
		SingleGlb_Pt_2011[i] = new TH1F(title,sub_title,60,0,60);	

	}

  TH2F *DoubleGlb_Ypt_2010 = new TH2F("DoubleGlb_ypt_2010","DoubleGlb_ypt_2010;double mu y;double mu p_{T}",ETA,-3.0,3.0,PT,0,20);
  TH1F *DoubleGlb_Mass_2010 = new TH1F("DoubleGlb_mass_2010","DoubleGlb_mass_2010;double mu mass;counts",MASS,0,20);
  TH1F *DoubleGlb_Y_2010 = new TH1F("DoubleGlb_y_2010","DoubleGlb_y_2010;double mu y;counts",ETA,-3.0,3.0);
  TH1F *DoubleGlb_Pt_2010 = new TH1F("DoubleGlb_pt_2010","DoubleGlb_pt_2010;double mu p_{T};counts",PT,0,20);
  TH1F *DoubleGlb_Phi_2010 = new TH1F("DoubleGlb_phi_2010","DoubleGlb_phi_2010;double mu #phi;counts",PHI,-PI,PI);

  TH2F *DoubleGlb_Ypt_2011 = new TH2F("DoubleGlb_ypt_2011","DoubleGlb_ypt_2011;double mu y;double mu p_{T}",ETA,-3.0,3.0,PT,0,20);
  TH1F *DoubleGlb_Mass_2011 = new TH1F("DoubleGlb_mass_2011","DoubleGlb_mass_2011;double mu mass;counts",MASS,0,20);
  TH1F *DoubleGlb_Y_2011 = new TH1F("DoubleGlb_y_2011","DoubleGlb_y_2011;double mu y;counts",ETA,-3.0,3.0);
  TH1F *DoubleGlb_Pt_2011 = new TH1F("DoubleGlb_pt_2011","DoubleGlb_pt_2011;double mu p_{T};counts",PT,0,20);
  TH1F *DoubleGlb_Phi_2011 = new TH1F("DoubleGlb_phi_2011","DoubleGlb_phi_2011;double mu #phi;counts",PHI,-PI,PI);

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

//	int max_event_2010 = muon_tree_2010->GetEntries();
//	int max_event_2011 = muon_tree_2011->GetEntries();
	int max_event_2010 = 1000;
	int max_event_2011 = 10000;

	
  // Loop over trees over 2010 trees
  for (int i=0; i<max_event_2010; i++) {
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

    ////////// Check muon trigger list
    flag->trig = false;
    for (unsigned int tidx=0; tidx<ntrig; tidx++) {
      if (trig_2011[tidx]) {         // At least one of the muon trigger is fired.
        flag->trig = true;
        break;
      }
    }
    if (!flag->trig) continue;  // If no muon triggers fired, go to the next event!

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

			if (muTree_2010->charge[a] + muTree_2010->charge[b] != 0) continue;
			
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

  TLegend* legCent = new TLegend(0.7,0.85,0.9,0.95);//top left
//  legCent->SetTextSize();
  legCent->SetBorderSize(0);
  legCent->SetFillColor(0);

  cnv->Divide(3,2);

  double denominator_2010 = muon_tree_2010->GetEntries();
  double denominator_2011 = muon_tree_2011->GetEntries();

  double numerator_2010 = DoubleGlb_Mass_2010->GetEntries();
  double numerator_2011 = DoubleGlb_Mass_2011->GetEntries();

  double ratio_2010 = numerator_2010 / denominator_2010;
  double ratio_2011 = numerator_2011 / denominator_2011;
  
  cout << "Denominator_2010 is " << denominator_2010 << ", Numerator_2010 is " << numerator_2010 << " and Ratio_2010 is " << ratio_2010 << endl;
  cout << "Denominator_2011 is " << denominator_2011 << ", Numerator_2011 is " << numerator_2011 << " and Ratio_2011 is " << ratio_2011 << endl;
  
  cnv->cd(1);
  gStyle->SetPadRightMargin(0.15);
    DoubleGlb_Ypt_2010->DrawNormalized("COLZ",1);
//  DoubleGlb_Ypt_2010->Draw("COLZ");

  cnv->cd(2);
  DoubleGlb_Ypt_2011->DrawNormalized("COLZ",1);
//  DoubleGlb_Ypt_2011->Draw("COLZ");

  cnv->cd(3);  
  gStyle->SetPadRightMargin(0.05);
  legCent->AddEntry(DoubleGlb_Mass_2010,"2010 Data","p");
  legCent->AddEntry(DoubleGlb_Mass_2011,"2011 Data","p");

//  DoubleGlb_Mass_2010->Sumw2();
  DoubleGlb_Mass_2010->SetMarkerStyle(20);
  DoubleGlb_Mass_2010->SetMarkerColor(1);
//  DoubleGlb_Mass_2010->DrawNormalized("p e",1);
//  DoubleGlb_Mass_2010->Draw("p e");
  DoubleGlb_Mass_2011->Sumw2();
  DoubleGlb_Mass_2011->SetMarkerStyle(20);
  DoubleGlb_Mass_2011->SetMarkerColor(2);
  DoubleGlb_Mass_2011->DrawNormalized("p e",1);
//  DoubleGlb_Mass_2011->DrawNormalized("p e same",1);
//  DoubleGlb_Mass_2011->Draw("p e");
  legCent->Draw();
  
  cnv->cd(4);
  DoubleGlb_Y_2010->Sumw2();
  DoubleGlb_Y_2010->SetMarkerStyle(20);
  DoubleGlb_Y_2010->SetMarkerColor(1);
//  DoubleGlb_Y_2010->DrawNormalized("p e",1);
//  DoubleGlb_Y_2010->Draw("p e");
  DoubleGlb_Y_2011->Sumw2();
  DoubleGlb_Y_2011->SetMarkerStyle(20);
  DoubleGlb_Y_2011->SetMarkerColor(2);
  DoubleGlb_Y_2011->DrawNormalized("p e",1);
//  DoubleGlb_Y_2011->DrawNormalized("p e same",1);
//  DoubleGlb_Y_2011->Draw("p e");
  legCent->Draw();

  cnv->cd(5);  
  DoubleGlb_Pt_2010->Sumw2();
  DoubleGlb_Pt_2010->SetMarkerStyle(20);
  DoubleGlb_Pt_2010->SetMarkerColor(1);
//  DoubleGlb_Pt_2010->DrawNormalized("p e",1);
//  DoubleGlb_Pt_2010->Draw("p e");
  DoubleGlb_Pt_2011->Sumw2();
  DoubleGlb_Pt_2011->SetMarkerStyle(20);
  DoubleGlb_Pt_2011->SetMarkerColor(2);
  DoubleGlb_Pt_2011->DrawNormalized("p e",1);
//  DoubleGlb_Pt_2011->DrawNormalized("p e same",1);
//  DoubleGlb_Pt_2011->Draw("p e");
  legCent->Draw();

  cnv->cd(6);  
  DoubleGlb_Phi_2010->Sumw2();
  DoubleGlb_Phi_2010->SetMarkerStyle(20);
  DoubleGlb_Phi_2010->SetMarkerColor(1);
//  DoubleGlb_Phi_2010->DrawNormalized("p e",1);
//  DoubleGlb_Phi_2010->Draw("p e");
  DoubleGlb_Phi_2011->Sumw2();
  DoubleGlb_Phi_2011->SetMarkerStyle(20);
  DoubleGlb_Phi_2011->SetMarkerColor(2);
  DoubleGlb_Phi_2011->DrawNormalized("p e",1);
//  DoubleGlb_Phi_2011->DrawNormalized("p e same",1);
//  DoubleGlb_Phi_2011->Draw("p e");
  legCent->Draw();
  
  if (flag->doGlb) {
	cnv->Print("diMu_plots_Global.pdf");
  } else if (flag->doSta) {
	cnv->Print("diMu_plots_STA.pdf");
  }
  
  return 0;
}

/*
void format_TH1 (TH1& th1, string title_name = "", string xaxis = "", string yaxis = "", int marker_color = 0, int marker_style = 0) {
	th1.Sumw2();
	th1.SetTitle(title_name);
	th1.SetMarkerColor(marker_color);
	th1.SetMarkerStyle(marker_style);
	th1.SetLineColor(marker_color);
	th1.GetXaxis()->SetTitle(xaxis);
	th1.GetXaxis()->CenterTitle();
	th1.GetYaxis()->SetTitle(yaxis);
	th1.GetYaxis()->CenterTitle();
	
	return;
}

void format_TH2 (TH2& th2, string title_name = "", string xaxis = "", string yaxis = "", int marker_color = 0, int marker_style = 0) {
//	th2.Sumw2();
	th2.SetTitle(title_name);
	th2.SetMarkerColor(marker_color);
	th2.SetMarkerStyle(marker_style);
	th2.SetLineColor(marker_color);
	th2.GetXaxis()->SetTitle(xaxis);
	th2.GetXaxis()->CenterTitle();
	th2.GetYaxis()->SetTitle(yaxis);
	th2.GetYaxis()->CenterTitle();
	
	return;
}
*/