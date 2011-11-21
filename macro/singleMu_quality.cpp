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

int singleMu_quality() {

  // Parameters  
  FLAG *flag = new FLAG;
  flag->doSta = false;
  flag->doGlb = true;
  
  string data2010  = "/castor/cern.ch/user/m/miheejo/openHLT/cms442p5/HICorePhysics_Skim_MinimumBias_RAW/openhlt_2010HICorePhysicsMB.root";
  string data2011  = "/castor/cern.ch/user/m/miheejo/openHLT/RD2011/HIData2011_rawToRecoV3_LSF/openhlt_HIData2011_rawToRecoV3_LSF.root";

  // Check trigger list
  vector<string> triglist;
//  triglist.push_back("HLT_HIL1DoubleMu0_HighQ_v1");
  triglist.push_back("HLT_HIL2DoubleMu3_v1");
//  triglist.push_back("HLT_HIL3DoubleMuOpen_v1");
//  triglist.push_back("HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy_v1");
//  triglist.push_back("HLT_HIL2Mu3_v1");
//  triglist.push_back("HLT_HIL2Mu7_v1");
//  triglist.push_back("HLT_HIL2Mu15_v1");
//  triglist.push_back("HLT_HIL2Mu3_NHitQ_v1");
//  triglist.push_back("HLT_HIL3Mu3_v1");

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

	TH2F *SingleGlb_nValMuHits_eta_2010 = new TH2F("SingleGlb_nValMuHits_eta_2010","SingleGlb_nValMuHits_eta_2010;nValMuHits;#eta",55,0,55,ETA,-2.4,2.4);
  TH2F *SingleGlb_nValTrkHits_eta_2010 = new TH2F("SingleGlb_nValTrkHits_eta_2010","SingleGlb_nValTrkHits_eta_2010;nValTrkHits;#eta",27,0,27,ETA,-2.4,2.4);
  TH2F *SingleGlb_glbChi2_ndof_eta_2010 = new TH2F("SingleGlb_glbChi2_ndof_eta_2010","SingleGlb_glbChi2_ndof_eta_2010;glbChi2_ndof;#eta",100,0,25,ETA,-2.4,2.4);
  TH2F *SingleGlb_trkChi2_ndof_eta_2010 = new TH2F("SingleGlb_trkChi2_ndof_eta_2010","SingleGlb_trkChi2_ndof_eta_2010;trkChi2_ndof;#eta",100,0,10,ETA,-2.4,2.4);
  TH2F *SingleGlb_pixLayerWMeas_eta_2010 = new TH2F("SingleGlb_pixLayerWMeas_eta_2010","SingleGlb_pixLayerWMeas_eta_2010;pixLayerWMeas;#eta",5,0,5,ETA,-2.4,2.4);
  TH2F *SingleGlb_trkDz_eta_2010 = new TH2F("SingleGlb_trkDz_eta_2010","SingleGlb_trkDz_eta_2010;trkDz;#eta",100,0,2,ETA,-2.4,2.4);
  TH2F *SingleGlb_trkDxy_eta_2010 = new TH2F("SingleGlb_trkDxy_eta_2010","SingleGlb_trkDxy_eta_2010;trkDxy;#eta",100,0,2,ETA,-2.4,2.4);

	TH2F *SingleGlb_nValMuHits_phi_2010 = new TH2F("SingleGlb_nValMuHits_phi_2010","SingleGlb_nValMuHits_phi_2010;nValMuHits;#phi",55,0,55,PHI,-PI,PI);
  TH2F *SingleGlb_nValTrkHits_phi_2010 = new TH2F("SingleGlb_nValTrkHits_phi_2010","SingleGlb_nValTrkHits_phi_2010;nValTrkHits;#phi",27,0,27,PHI,-PI,PI);
  TH2F *SingleGlb_glbChi2_ndof_phi_2010 = new TH2F("SingleGlb_glbChi2_ndof_phi_2010","SingleGlb_glbChi2_ndof_phi_2010;glbChi2_ndof;#phi",100,0,25,PHI,-PI,PI);
  TH2F *SingleGlb_trkChi2_ndof_phi_2010 = new TH2F("SingleGlb_trkChi2_ndof_phi_2010","SingleGlb_trkChi2_ndof_phi_2010;trkChi2_ndof;#phi",100,0,10,PHI,-PI,PI);
  TH2F *SingleGlb_pixLayerWMeas_phi_2010 = new TH2F("SingleGlb_pixLayerWMeas_phi_2010","SingleGlb_pixLayerWMeas_phi_2010;pixLayerWMeas;#phi",5,0,5,PHI,-PI,PI);
  TH2F *SingleGlb_trkDz_phi_2010 = new TH2F("SingleGlb_trkDz_phi_2010","SingleGlb_trkDz_phi_2010;trkDz;#phi",100,0,2,PHI,-PI,PI);
  TH2F *SingleGlb_trkDxy_phi_2010 = new TH2F("SingleGlb_trkDxy_phi_2010","SingleGlb_trkDxy_phi_2010;trkDxy;#phi",100,0,2,PHI,-PI,PI);
	
	TH1F *SingleGlb_nValMuHits_2010 = new TH1F("SingleGlb_nValMuHits_2010","SingleGlb_nValMuHits_2010;nValMuHits",55,0,55);
  TH1F *SingleGlb_nValTrkHits_2010 = new TH1F("SingleGlb_nValTrkHits_2010","SingleGlb_nValTrkHits_2010;nValTrkHits",27,0,27);
  TH1F *SingleGlb_glbChi2_ndof_2010 = new TH1F("SingleGlb_glbChi2_ndof_2010","SingleGlb_glbChi2_ndof_2010;glbChi2_ndof",100,0,25);
  TH1F *SingleGlb_trkChi2_ndof_2010 = new TH1F("SingleGlb_trkChi2_ndof_2010","SingleGlb_trkChi2_ndof_2010;trkChi2_ndof",100,0,10);
  TH1F *SingleGlb_pixLayerWMeas_2010 = new TH1F("SingleGlb_pixLayerWMeas_2010","SingleGlb_pixLayerWMeas_2010;pixLayerWMeas",5,0,5);
  TH1F *SingleGlb_trkDz_2010 = new TH1F("SingleGlb_trkDz_2010","SingleGlb_trkDz_2010;trkDz",100,0,2);
  TH1F *SingleGlb_trkDxy_2010 = new TH1F("SingleGlb_trkDxy_2010","SingleGlb_trkDxy_2010;trkDxy",100,0,2);

	TH2F *SingleGlb_nValMuHits_eta_2011 = new TH2F("SingleGlb_nValMuHits_eta_2011","SingleGlb_nValMuHits_eta_2011;nValMuHits;#eta",55,0,55,ETA,-2.4,2.4);
  TH2F *SingleGlb_nValTrkHits_eta_2011 = new TH2F("SingleGlb_nValTrkHits_eta_2011","SingleGlb_nValTrkHits_eta_2011;nValTrkHits;#eta",27,0,27,ETA,-2.4,2.4);
  TH2F *SingleGlb_glbChi2_ndof_eta_2011 = new TH2F("SingleGlb_glbChi2_ndof_eta_2011","SingleGlb_glbChi2_ndof_eta_2011;glbChi2_ndof;#eta",100,0,25,ETA,-2.4,2.4);
  TH2F *SingleGlb_trkChi2_ndof_eta_2011 = new TH2F("SingleGlb_trkChi2_ndof_eta_2011","SingleGlb_trkChi2_ndof_eta_2011;trkChi2_ndof;#eta",100,0,10,ETA,-2.4,2.4);
  TH2F *SingleGlb_pixLayerWMeas_eta_2011 = new TH2F("SingleGlb_pixLayerWMeas_eta_2011","SingleGlb_pixLayerWMeas_eta_2011;pixLayerWMeas;#eta",5,0,5,ETA,-2.4,2.4);
  TH2F *SingleGlb_trkDz_eta_2011 = new TH2F("SingleGlb_trkDz_eta_2011","SingleGlb_trkDz_eta_2011;trkDz;#eta",100,0,2,ETA,-2.4,2.4);
  TH2F *SingleGlb_trkDxy_eta_2011 = new TH2F("SingleGlb_trkDxy_eta_2011","SingleGlb_trkDxy_eta_2011;trkDxy;#eta",100,0,2,ETA,-2.4,2.4);

	TH2F *SingleGlb_nValMuHits_phi_2011 = new TH2F("SingleGlb_nValMuHits_phi_2011","SingleGlb_nValMuHits_phi_2011;nValMuHits;#phi",55,0,55,PHI,-PI,PI);
  TH2F *SingleGlb_nValTrkHits_phi_2011 = new TH2F("SingleGlb_nValTrkHits_phi_2011","SingleGlb_nValTrkHits_phi_2011;nValTrkHits;#phi",27,0,27,PHI,-PI,PI);
  TH2F *SingleGlb_glbChi2_ndof_phi_2011 = new TH2F("SingleGlb_glbChi2_ndof_phi_2011","SingleGlb_glbChi2_ndof_phi_2011;glbChi2_ndof;#phi",100,0,25,PHI,-PI,PI);
  TH2F *SingleGlb_trkChi2_ndof_phi_2011 = new TH2F("SingleGlb_trkChi2_ndof_phi_2011","SingleGlb_trkChi2_ndof_phi_2011;trkChi2_ndof;#phi",100,0,10,PHI,-PI,PI);
  TH2F *SingleGlb_pixLayerWMeas_phi_2011 = new TH2F("SingleGlb_pixLayerWMeas_phi_2011","SingleGlb_pixLayerWMeas_phi_2011;pixLayerWMeas;#phi",5,0,5,PHI,-PI,PI);
  TH2F *SingleGlb_trkDz_phi_2011 = new TH2F("SingleGlb_trkDz_phi_2011","SingleGlb_trkDz_phi_2011;trkDz;#phi",100,0,2,PHI,-PI,PI);
  TH2F *SingleGlb_trkDxy_phi_2011 = new TH2F("SingleGlb_trkDxy_phi_2011","SingleGlb_trkDxy_phi_2011;trkDxy;#phi",100,0,2,PHI,-PI,PI);

	TH1F *SingleGlb_nValMuHits_2011 = new TH1F("SingleGlb_nValMuHits_2011","SingleGlb_nValMuHits_2011;nValMuHits",55,0,55);
  TH1F *SingleGlb_nValTrkHits_2011 = new TH1F("SingleGlb_nValTrkHits_2011","SingleGlb_nValTrkHits_2011;nValTrkHits",27,0,27);
  TH1F *SingleGlb_glbChi2_ndof_2011 = new TH1F("SingleGlb_glbChi2_ndof_2011","SingleGlb_glbChi2_ndof_2011;glbChi2_ndof",100,0,25);
  TH1F *SingleGlb_trkChi2_ndof_2011 = new TH1F("SingleGlb_trkChi2_ndof_2011","SingleGlb_trkChi2_ndof_2011;trkChi2_ndof",100,0,10);
  TH1F *SingleGlb_pixLayerWMeas_2011 = new TH1F("SingleGlb_pixLayerWMeas_2011","SingleGlb_pixLayerWMeas_2011;pixLayerWMeas",5,0,5);
  TH1F *SingleGlb_trkDz_2011 = new TH1F("SingleGlb_trkDz_2011","SingleGlb_trkDz_2011;trkDz",100,0,2);
  TH1F *SingleGlb_trkDxy_2011 = new TH1F("SingleGlb_trkDxy_2011","SingleGlb_trkDxy_2011;trkDxy",100,0,2);

	TH2F *SingleGlb_nValMuHits_eta_2010_qual = new TH2F("SingleGlb_nValMuHits_eta_2010_qual","SingleGlb_nValMuHits_eta_2010_qual;nValMuHits;#eta",55,0,55,ETA,-2.4,2.4);
  TH2F *SingleGlb_nValTrkHits_eta_2010_qual = new TH2F("SingleGlb_nValTrkHits_eta_2010_qual","SingleGlb_nValTrkHits_eta_2010_qual;nValTrkHits;#eta",27,0,27,ETA,-2.4,2.4);
  TH2F *SingleGlb_glbChi2_ndof_eta_2010_qual = new TH2F("SingleGlb_glbChi2_ndof_eta_2010_qual","SingleGlb_glbChi2_ndof_eta_2010_qual;glbChi2_ndof;#eta",100,0,25,ETA,-2.4,2.4);
  TH2F *SingleGlb_trkChi2_ndof_eta_2010_qual = new TH2F("SingleGlb_trkChi2_ndof_eta_2010_qual","SingleGlb_trkChi2_ndof_eta_2010_qual;trkChi2_ndof;#eta",100,0,10,ETA,-2.4,2.4);
  TH2F *SingleGlb_pixLayerWMeas_eta_2010_qual = new TH2F("SingleGlb_pixLayerWMeas_eta_2010_qual","SingleGlb_pixLayerWMeas_eta_2010_qual;pixLayerWMeas;#eta",5,0,5,ETA,-2.4,2.4);
  TH2F *SingleGlb_trkDz_eta_2010_qual = new TH2F("SingleGlb_trkDz_eta_2010_qual","SingleGlb_trkDz_eta_2010_qual;trkDz;#eta",100,0,2,ETA,-2.4,2.4);
  TH2F *SingleGlb_trkDxy_eta_2010_qual = new TH2F("SingleGlb_trkDxy_eta_2010_qual","SingleGlb_trkDxy_eta_2010_qual;trkDxy;#eta",100,0,2,ETA,-2.4,2.4);

	TH2F *SingleGlb_nValMuHits_phi_2010_qual = new TH2F("SingleGlb_nValMuHits_phi_2010_qual","SingleGlb_nValMuHits_phi_2010_qual;nValMuHits;#phi",55,0,55,PHI,-PI,PI);
  TH2F *SingleGlb_nValTrkHits_phi_2010_qual = new TH2F("SingleGlb_nValTrkHits_phi_2010_qual","SingleGlb_nValTrkHits_phi_2010_qual;nValTrkHits;#phi",27,0,27,PHI,-PI,PI);
  TH2F *SingleGlb_glbChi2_ndof_phi_2010_qual = new TH2F("SingleGlb_glbChi2_ndof_phi_2010_qual","SingleGlb_glbChi2_ndof_phi_2010_qual;glbChi2_ndof;#phi",100,0,25,PHI,-PI,PI);
  TH2F *SingleGlb_trkChi2_ndof_phi_2010_qual = new TH2F("SingleGlb_trkChi2_ndof_phi_2010_qual","SingleGlb_trkChi2_ndof_phi_2010_qual;trkChi2_ndof;#phi",100,0,10,PHI,-PI,PI);
  TH2F *SingleGlb_pixLayerWMeas_phi_2010_qual = new TH2F("SingleGlb_pixLayerWMeas_phi_2010_qual","SingleGlb_pixLayerWMeas_phi_2010_qual;pixLayerWMeas;#phi",5,0,5,PHI,-PI,PI);
  TH2F *SingleGlb_trkDz_phi_2010_qual = new TH2F("SingleGlb_trkDz_phi_2010_qual","SingleGlb_trkDz_phi_2010_qual;trkDz;#phi",100,0,2,PHI,-PI,PI);
  TH2F *SingleGlb_trkDxy_phi_2010_qual = new TH2F("SingleGlb_trkDxy_phi_2010_qual","SingleGlb_trkDxy_phi_2010_qual;trkDxy;#phi",100,0,2,PHI,-PI,PI);

	TH1F *SingleGlb_nValMuHits_2010_qual = new TH1F("SingleGlb_nValMuHits_2010_qual","SingleGlb_nValMuHits_2010_qual;nValMuHits",55,0,55);
  TH1F *SingleGlb_nValTrkHits_2010_qual = new TH1F("SingleGlb_nValTrkHits_2010_qual","SingleGlb_nValTrkHits_2010_qual;nValTrkHits",27,0,27);
  TH1F *SingleGlb_glbChi2_ndof_2010_qual = new TH1F("SingleGlb_glbChi2_ndof_2010_qual","SingleGlb_glbChi2_ndof_2010_qual;glbChi2_ndof",100,0,25);
  TH1F *SingleGlb_trkChi2_ndof_2010_qual = new TH1F("SingleGlb_trkChi2_ndof_2010_qual","SingleGlb_trkChi2_ndof_2010_qual;trkChi2_ndof",100,0,10);
  TH1F *SingleGlb_pixLayerWMeas_2010_qual = new TH1F("SingleGlb_pixLayerWMeas_2010_qual","SingleGlb_pixLayerWMeas_2010_qual;pixLayerWMeas",5,0,5);
  TH1F *SingleGlb_trkDz_2010_qual = new TH1F("SingleGlb_trkDz_2010_qual","SingleGlb_trkDz_2010_qual;trkDz",100,0,2);
  TH1F *SingleGlb_trkDxy_2010_qual = new TH1F("SingleGlb_trkDxy_2010_qual","SingleGlb_trkDxy_2010_qual;trkDxy",100,0,2);

	TH2F *SingleGlb_nValMuHits_eta_2011_qual = new TH2F("SingleGlb_nValMuHits_eta_2011_qual","SingleGlb_nValMuHits_eta_2011_qual;nValMuHits;#eta",55,0,55,ETA,-2.4,2.4);
  TH2F *SingleGlb_nValTrkHits_eta_2011_qual = new TH2F("SingleGlb_nValTrkHits_eta_2011_qual","SingleGlb_nValTrkHits_eta_2011_qual;nValTrkHits;#eta",27,0,27,ETA,-2.4,2.4);
  TH2F *SingleGlb_glbChi2_ndof_eta_2011_qual = new TH2F("SingleGlb_glbChi2_ndof_eta_2011_qual","SingleGlb_glbChi2_ndof_eta_2011_qual;glbChi2_ndof;#eta",100,0,25,ETA,-2.4,2.4);
  TH2F *SingleGlb_trkChi2_ndof_eta_2011_qual = new TH2F("SingleGlb_trkChi2_ndof_eta_2011_qual","SingleGlb_trkChi2_ndof_eta_2011_qual;trkChi2_ndof;#eta",100,0,10,ETA,-2.4,2.4);
  TH2F *SingleGlb_pixLayerWMeas_eta_2011_qual = new TH2F("SingleGlb_pixLayerWMeas_eta_2011_qual","SingleGlb_pixLayerWMeas_eta_2011_qual;pixLayerWMeas;#eta",5,0,5,ETA,-2.4,2.4);
  TH2F *SingleGlb_trkDz_eta_2011_qual = new TH2F("SingleGlb_trkDz_eta_2011_qual","SingleGlb_trkDz_eta_2011_qual;trkDz;#eta",100,0,2,ETA,-2.4,2.4);
  TH2F *SingleGlb_trkDxy_eta_2011_qual = new TH2F("SingleGlb_trkDxy_eta_2011_qual","SingleGlb_trkDxy_eta_2011_qual;trkDxy;#eta",100,0,2,ETA,-2.4,2.4);

	TH2F *SingleGlb_nValMuHits_phi_2011_qual = new TH2F("SingleGlb_nValMuHits_phi_2011_qual","SingleGlb_nValMuHits_phi_2011_qual;nValMuHits;#phi",55,0,55,PHI,-PI,PI);
  TH2F *SingleGlb_nValTrkHits_phi_2011_qual = new TH2F("SingleGlb_nValTrkHits_phi_2011_qual","SingleGlb_nValTrkHits_phi_2011_qual;nValTrkHits;#phi",27,0,27,PHI,-PI,PI);
  TH2F *SingleGlb_glbChi2_ndof_phi_2011_qual = new TH2F("SingleGlb_glbChi2_ndof_phi_2011_qual","SingleGlb_glbChi2_ndof_phi_2011_qual;glbChi2_ndof;#phi",100,0,25,PHI,-PI,PI);
  TH2F *SingleGlb_trkChi2_ndof_phi_2011_qual = new TH2F("SingleGlb_trkChi2_ndof_phi_2011_qual","SingleGlb_trkChi2_ndof_phi_2011_qual;trkChi2_ndof;#phi",100,0,10,PHI,-PI,PI);
  TH2F *SingleGlb_pixLayerWMeas_phi_2011_qual = new TH2F("SingleGlb_pixLayerWMeas_phi_2011_qual","SingleGlb_pixLayerWMeas_phi_2011_qual;pixLayerWMeas;#phi",5,0,5,PHI,-PI,PI);
  TH2F *SingleGlb_trkDz_phi_2011_qual = new TH2F("SingleGlb_trkDz_phi_2011_qual","SingleGlb_trkDz_phi_2011_qual;trkDz;#phi",100,0,2,PHI,-PI,PI);
  TH2F *SingleGlb_trkDxy_phi_2011_qual = new TH2F("SingleGlb_trkDxy_phi_2011_qual","SingleGlb_trkDxy_phi_2011_qual;trkDxy;#phi",100,0,2,PHI,-PI,PI);

	TH1F *SingleGlb_nValMuHits_2011_qual = new TH1F("SingleGlb_nValMuHits_2011_qual","SingleGlb_nValMuHits_2011_qual;nValMuHits",55,0,55);
  TH1F *SingleGlb_nValTrkHits_2011_qual = new TH1F("SingleGlb_nValTrkHits_2011_qual","SingleGlb_nValTrkHits_2011_qual;nValTrkHits",27,0,27);
  TH1F *SingleGlb_glbChi2_ndof_2011_qual = new TH1F("SingleGlb_glbChi2_ndof_2011_qual","SingleGlb_glbChi2_ndof_2011_qual;glbChi2_ndof",100,0,25);
  TH1F *SingleGlb_trkChi2_ndof_2011_qual = new TH1F("SingleGlb_trkChi2_ndof_2011_qual","SingleGlb_trkChi2_ndof_2011_qual;trkChi2_ndof",100,0,10);
  TH1F *SingleGlb_pixLayerWMeas_2011_qual = new TH1F("SingleGlb_pixLayerWMeas_2011_qual","SingleGlb_pixLayerWMeas_2011_qual;pixLayerWMeas",5,0,5);
  TH1F *SingleGlb_trkDz_2011_qual = new TH1F("SingleGlb_trkDz_2011_qual","SingleGlb_trkDz_2011_qual;trkDz",100,0,2);
  TH1F *SingleGlb_trkDxy_2011_qual = new TH1F("SingleGlb_trkDxy_2011_qual","SingleGlb_trkDxy_2011_qual;trkDxy",100,0,2);
	
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
	cout << "Opening 2010 input file..." << endl;
  TCastorFile   *input_2010 = new TCastorFile(data2010.c_str());
	cout << "2010 input file opened" << endl;
  FriendMuTree  *mutree_2010 = new FriendMuTree(input_2010,true); // Load HLTMuTree
  HltTree       *ohTree_2010 = new HltTree(input_2010,true);      // Load HltTree

  TTree         *muon_tree_2010;                             // Hold HLTMuTree
  TTree         *open_tree_2010;                             // Hold HltTree
  MUTREE        *muTree_2010 = new MUTREE;

  // 2011 datafile
	cout << "Opening 2011 input file..." << endl;
  TCastorFile   *input_2011 = new TCastorFile(data2011.c_str());
	cout << "2011 input file opened" << endl;
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

  int nevt_2010=0;                  // # of events that has at least 1 muon trigger fired
  int nevt_2010_qual=0;                  // # of events that has at least 1 muon trigger fired
  // Loop over trees over 2010 trees
  for (int i=0; i<muon_tree_2010->GetEntries(); i++) {
    muon_tree_2010->GetEntry(i);
    ohTree_2010->GetEntry(i);
    open_tree_2010->GetEntry(i);

    ////////// Check muon trigger list
    nevt_2010++;
    bool qual=false;
    ////////// Load muons and fill up histograms
    for (int a=0; a < muTree_2010->nptl; a++) {
			if (flag->doGlb) {
        if(!isMuInAcc(flag, muTree_2010->eta[a], muTree_2010->pt[a])) continue;    //Check glb muons are within acceptance range
      } else if (flag->doSta) {
        if(!isMuInAcc(flag, muTree_2010->eta[a], muTree_2010->pt[a])) continue;    //Check sta muons are within acceptance range
      }

      SingleGlb_Etapt_2010->Fill(muTree_2010->eta[a],muTree_2010->pt[a]);
      SingleGlb_Etaphi_2010->Fill(muTree_2010->eta[a],muTree_2010->phi[a]);
      SingleGlb_Eta_2010->Fill(muTree_2010->eta[a]);
      SingleGlb_Pt_2010->Fill(muTree_2010->pt[a]);
      SingleGlb_Phi_2010->Fill(muTree_2010->phi[a]);

			SingleGlb_nValMuHits_eta_2010->Fill(muTree_2010->nValMuHits[a],muTree_2010->eta[a]);
			SingleGlb_nValTrkHits_eta_2010->Fill(muTree_2010->nValMuHits[a],muTree_2010->eta[a]);
			SingleGlb_glbChi2_ndof_eta_2010->Fill(muTree_2010->glbChi2_ndof[a],muTree_2010->eta[a]);
			SingleGlb_trkChi2_ndof_eta_2010->Fill(muTree_2010->trkChi2_ndof[a],muTree_2010->eta[a]);
			SingleGlb_pixLayerWMeas_eta_2010->Fill(muTree_2010->pixLayerWMeas[a],muTree_2010->eta[a]);
			SingleGlb_trkDz_eta_2010->Fill(muTree_2010->trkDz[a],muTree_2010->eta[a]);
			SingleGlb_trkDxy_eta_2010->Fill(muTree_2010->trkDxy[a],muTree_2010->eta[a]);

			SingleGlb_nValMuHits_phi_2010->Fill(muTree_2010->nValMuHits[a],muTree_2010->phi[a]);
			SingleGlb_nValTrkHits_phi_2010->Fill(muTree_2010->nValMuHits[a],muTree_2010->phi[a]);
			SingleGlb_glbChi2_ndof_phi_2010->Fill(muTree_2010->glbChi2_ndof[a],muTree_2010->phi[a]);
			SingleGlb_trkChi2_ndof_phi_2010->Fill(muTree_2010->trkChi2_ndof[a],muTree_2010->phi[a]);
			SingleGlb_pixLayerWMeas_phi_2010->Fill(muTree_2010->pixLayerWMeas[a],muTree_2010->phi[a]);
			SingleGlb_trkDz_phi_2010->Fill(muTree_2010->trkDz[a],muTree_2010->phi[a]);
			SingleGlb_trkDxy_phi_2010->Fill(muTree_2010->trkDxy[a],muTree_2010->phi[a]);
			
			SingleGlb_nValMuHits_2010->Fill(muTree_2010->nValMuHits[a]);
			SingleGlb_nValTrkHits_2010->Fill(muTree_2010->nValMuHits[a]);
			SingleGlb_glbChi2_ndof_2010->Fill(muTree_2010->glbChi2_ndof[a]);
			SingleGlb_trkChi2_ndof_2010->Fill(muTree_2010->trkChi2_ndof[a]);
			SingleGlb_pixLayerWMeas_2010->Fill(muTree_2010->pixLayerWMeas[a]);
			SingleGlb_trkDz_2010->Fill(muTree_2010->trkDz[a]);
			SingleGlb_trkDxy_2010->Fill(muTree_2010->trkDxy[a]);
	
      flag->trig = false;
	  for (unsigned int tidx=0; tidx<ntrig; tidx++) {
	    if (trig_2010[tidx]) {         // At least one of the muon trigger is fired.
				flag->trig = true;
		  break;
	    }
	  }

      qual = true;
	  
	  if (!flag->trig) continue;  // If no muon triggers fired, go to the next event!    
		
      SingleGlb_Etapt_2010_qual->Fill(muTree_2010->eta[a],muTree_2010->pt[a]);
      SingleGlb_Etaphi_2010_qual->Fill(muTree_2010->eta[a],muTree_2010->phi[a]);
      SingleGlb_Eta_2010_qual->Fill(muTree_2010->eta[a]);
      SingleGlb_Pt_2010_qual->Fill(muTree_2010->pt[a]);
      SingleGlb_Phi_2010_qual->Fill(muTree_2010->phi[a]);

			SingleGlb_nValMuHits_eta_2010_qual->Fill(muTree_2010->nValMuHits[a],muTree_2010->eta[a]);
			SingleGlb_nValTrkHits_eta_2010_qual->Fill(muTree_2010->nValMuHits[a],muTree_2010->eta[a]);
			SingleGlb_glbChi2_ndof_eta_2010_qual->Fill(muTree_2010->glbChi2_ndof[a],muTree_2010->eta[a]);
			SingleGlb_trkChi2_ndof_eta_2010_qual->Fill(muTree_2010->trkChi2_ndof[a],muTree_2010->eta[a]);
			SingleGlb_pixLayerWMeas_eta_2010_qual->Fill(muTree_2010->pixLayerWMeas[a],muTree_2010->eta[a]);
			SingleGlb_trkDz_eta_2010_qual->Fill(muTree_2010->trkDz[a],muTree_2010->eta[a]);
			SingleGlb_trkDxy_eta_2010_qual->Fill(muTree_2010->trkDxy[a],muTree_2010->eta[a]);

			SingleGlb_nValMuHits_phi_2010_qual->Fill(muTree_2010->nValMuHits[a],muTree_2010->phi[a]);
			SingleGlb_nValTrkHits_phi_2010_qual->Fill(muTree_2010->nValMuHits[a],muTree_2010->phi[a]);
			SingleGlb_glbChi2_ndof_phi_2010_qual->Fill(muTree_2010->glbChi2_ndof[a],muTree_2010->phi[a]);
			SingleGlb_trkChi2_ndof_phi_2010_qual->Fill(muTree_2010->trkChi2_ndof[a],muTree_2010->phi[a]);
			SingleGlb_pixLayerWMeas_phi_2010_qual->Fill(muTree_2010->pixLayerWMeas[a],muTree_2010->phi[a]);
			SingleGlb_trkDz_phi_2010_qual->Fill(muTree_2010->trkDz[a],muTree_2010->phi[a]);
			SingleGlb_trkDxy_phi_2010_qual->Fill(muTree_2010->trkDxy[a],muTree_2010->phi[a]);
			
			SingleGlb_nValMuHits_2010_qual->Fill(muTree_2010->nValMuHits[a]);
			SingleGlb_nValTrkHits_2010_qual->Fill(muTree_2010->nValMuHits[a]);
			SingleGlb_glbChi2_ndof_2010_qual->Fill(muTree_2010->glbChi2_ndof[a]);
			SingleGlb_trkChi2_ndof_2010_qual->Fill(muTree_2010->trkChi2_ndof[a]);
			SingleGlb_pixLayerWMeas_2010_qual->Fill(muTree_2010->pixLayerWMeas[a]);
			SingleGlb_trkDz_2010_qual->Fill(muTree_2010->trkDz[a]);
			SingleGlb_trkDxy_2010_qual->Fill(muTree_2010->trkDxy[a]);
			
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


    nevt_2011++;
    bool qual=false;
    ////////// Load muons and fill up histograms
    for (int a=0; a < muTree_2011->nptl; a++) {
      if (flag->doGlb) {
        if(!isValidMu(flag, muTree_2011, a)) continue;    //Check glb muons are within acceptance range
      } else if (flag->doSta) {
        if(!isMuInAcc(flag, muTree_2011->eta[a], muTree_2011->pt[a])) continue;    //Check sta muons are within acceptance range
      }

      SingleGlb_Etapt_2011->Fill(muTree_2011->eta[a],muTree_2011->pt[a]);
      SingleGlb_Etaphi_2011->Fill(muTree_2011->eta[a],muTree_2011->phi[a]);
      SingleGlb_Eta_2011->Fill(muTree_2011->eta[a]);
      SingleGlb_Pt_2011->Fill(muTree_2011->pt[a]);
      SingleGlb_Phi_2011->Fill(muTree_2011->phi[a]);

			SingleGlb_nValMuHits_eta_2011->Fill(muTree_2011->nValMuHits[a],muTree_2011->eta[a]);
			SingleGlb_nValTrkHits_eta_2011->Fill(muTree_2011->nValMuHits[a],muTree_2011->eta[a]);
			SingleGlb_glbChi2_ndof_eta_2011->Fill(muTree_2011->glbChi2_ndof[a],muTree_2011->eta[a]);
			SingleGlb_trkChi2_ndof_eta_2011->Fill(muTree_2011->trkChi2_ndof[a],muTree_2011->eta[a]);
			SingleGlb_pixLayerWMeas_eta_2011->Fill(muTree_2011->pixLayerWMeas[a],muTree_2011->eta[a]);
			SingleGlb_trkDz_eta_2011->Fill(muTree_2011->trkDz[a],muTree_2011->eta[a]);
			SingleGlb_trkDxy_eta_2011->Fill(muTree_2011->trkDxy[a],muTree_2011->eta[a]);

			SingleGlb_nValMuHits_phi_2011->Fill(muTree_2011->nValMuHits[a],muTree_2011->phi[a]);
			SingleGlb_nValTrkHits_phi_2011->Fill(muTree_2011->nValMuHits[a],muTree_2011->phi[a]);
			SingleGlb_glbChi2_ndof_phi_2011->Fill(muTree_2011->glbChi2_ndof[a],muTree_2011->phi[a]);
			SingleGlb_trkChi2_ndof_phi_2011->Fill(muTree_2011->trkChi2_ndof[a],muTree_2011->phi[a]);
			SingleGlb_pixLayerWMeas_phi_2011->Fill(muTree_2011->pixLayerWMeas[a],muTree_2011->phi[a]);
			SingleGlb_trkDz_phi_2011->Fill(muTree_2011->trkDz[a],muTree_2011->phi[a]);
			SingleGlb_trkDxy_phi_2011->Fill(muTree_2011->trkDxy[a],muTree_2011->phi[a]);
			
			SingleGlb_nValMuHits_2011->Fill(muTree_2011->nValMuHits[a]);
			SingleGlb_nValTrkHits_2011->Fill(muTree_2011->nValMuHits[a]);
			SingleGlb_glbChi2_ndof_2011->Fill(muTree_2011->glbChi2_ndof[a]);
			SingleGlb_trkChi2_ndof_2011->Fill(muTree_2011->trkChi2_ndof[a]);
			SingleGlb_pixLayerWMeas_2011->Fill(muTree_2011->pixLayerWMeas[a]);
			SingleGlb_trkDz_2011->Fill(muTree_2011->trkDz[a]);
			SingleGlb_trkDxy_2011->Fill(muTree_2011->trkDxy[a]);
			
			////////// Check muon trigger list
			flag->trig = false;
			for (unsigned int tidx=0; tidx<ntrig; tidx++) {
				if (trig_2011[tidx]) {         // At least one of the muon trigger is fired.
				flag->trig = true;
				break;
				}
			}
			if (!flag->trig) continue;  // If no muon triggers fired, go to the next event!

      qual = true;
      
      SingleGlb_Etapt_2011_qual->Fill(muTree_2011->eta[a],muTree_2011->pt[a]);
      SingleGlb_Etaphi_2011_qual->Fill(muTree_2011->eta[a],muTree_2011->phi[a]);
      SingleGlb_Eta_2011_qual->Fill(muTree_2011->eta[a]);
      SingleGlb_Pt_2011_qual->Fill(muTree_2011->pt[a]);
      SingleGlb_Phi_2011_qual->Fill(muTree_2011->phi[a]);

			SingleGlb_nValMuHits_eta_2011_qual->Fill(muTree_2011->nValMuHits[a],muTree_2011->eta[a]);
			SingleGlb_nValTrkHits_eta_2011_qual->Fill(muTree_2011->nValMuHits[a],muTree_2011->eta[a]);
			SingleGlb_glbChi2_ndof_eta_2011_qual->Fill(muTree_2011->glbChi2_ndof[a],muTree_2011->eta[a]);
			SingleGlb_trkChi2_ndof_eta_2011_qual->Fill(muTree_2011->trkChi2_ndof[a],muTree_2011->eta[a]);
			SingleGlb_pixLayerWMeas_eta_2011_qual->Fill(muTree_2011->pixLayerWMeas[a],muTree_2011->eta[a]);
			SingleGlb_trkDz_eta_2011_qual->Fill(muTree_2011->trkDz[a],muTree_2011->eta[a]);
			SingleGlb_trkDxy_eta_2011_qual->Fill(muTree_2011->trkDxy[a],muTree_2011->eta[a]);

			SingleGlb_nValMuHits_phi_2011_qual->Fill(muTree_2011->nValMuHits[a],muTree_2011->phi[a]);
			SingleGlb_nValTrkHits_phi_2011_qual->Fill(muTree_2011->nValMuHits[a],muTree_2011->phi[a]);
			SingleGlb_glbChi2_ndof_phi_2011_qual->Fill(muTree_2011->glbChi2_ndof[a],muTree_2011->phi[a]);
			SingleGlb_trkChi2_ndof_phi_2011_qual->Fill(muTree_2011->trkChi2_ndof[a],muTree_2011->phi[a]);
			SingleGlb_pixLayerWMeas_phi_2011_qual->Fill(muTree_2011->pixLayerWMeas[a],muTree_2011->phi[a]);
			SingleGlb_trkDz_phi_2011_qual->Fill(muTree_2011->trkDz[a],muTree_2011->phi[a]);
			SingleGlb_trkDxy_phi_2011_qual->Fill(muTree_2011->trkDxy[a],muTree_2011->phi[a]);
			
			SingleGlb_nValMuHits_2011_qual->Fill(muTree_2011->nValMuHits[a]);
			SingleGlb_nValTrkHits_2011_qual->Fill(muTree_2011->nValMuHits[a]);
			SingleGlb_glbChi2_ndof_2011_qual->Fill(muTree_2011->glbChi2_ndof[a]);
			SingleGlb_trkChi2_ndof_2011_qual->Fill(muTree_2011->trkChi2_ndof[a]);
			SingleGlb_pixLayerWMeas_2011_qual->Fill(muTree_2011->pixLayerWMeas[a]);
			SingleGlb_trkDz_2011_qual->Fill(muTree_2011->trkDz[a]);
			SingleGlb_trkDxy_2011_qual->Fill(muTree_2011->trkDxy[a]);

    }
    if (qual) nevt_2011_qual++;

    if (i%1000 ==0)
    cout << "Event in 2011 datasets: " << i+1 << endl;

  }

	double numerator_2010 = SingleGlb_Eta_2010->GetEntries();
	double numerator_2010_qual = SingleGlb_Eta_2010_qual->GetEntries();
	double numerator_2011 = SingleGlb_Eta_2011->GetEntries();
	double numerator_2011_qual = SingleGlb_Eta_2011_qual->GetEntries();
  double ratio_2010 = SingleGlb_Eta_2010->GetEntries()/nevt_2010;
  double ratio_2011 = SingleGlb_Eta_2011->GetEntries()/nevt_2011;
  double ratio_2010_qual = SingleGlb_Eta_2010_qual->GetEntries()/nevt_2010_qual;
  double ratio_2011_qual = SingleGlb_Eta_2011_qual->GetEntries()/nevt_2011_qual;
  
  // Draw final histograms and save it into .png files
  gROOT->Macro("~miheejo/public/HIMuTrig/TrigStyle.C");    //For plot style
  TCanvas *canv = new TCanvas("canv","canv",800,600);

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
	stringstream title;
	
	gStyle->SetOptStat("m");
	gStyle->SetOptTitle(1);

	canv = new TCanvas("canv","canv",1300,1000);
  canv->Divide(3,3);
	
  canv->cd(1);
  SingleGlb_nValMuHits_phi_2010_qual->DrawNormalized("colz",1);
	canv->cd(2);
  SingleGlb_nValTrkHits_phi_2010_qual->DrawNormalized("colz",1);
	canv->cd(3);
  SingleGlb_glbChi2_ndof_phi_2010_qual->DrawNormalized("colz",1);
	canv->cd(4);
  SingleGlb_trkChi2_ndof_phi_2010_qual->DrawNormalized("colz",1);
	canv->cd(5);
  SingleGlb_pixLayerWMeas_phi_2010_qual->DrawNormalized("colz",1);
	canv->cd(6);
  SingleGlb_trkDz_phi_2010_qual->DrawNormalized("colz",1);
	canv->cd(7);
  SingleGlb_trkDxy_phi_2010_qual->DrawNormalized("colz",1);
	canv->cd(8);
  title.str("");
	title << "2010 # muons (pass L2_DoubleMu3): " << SingleGlb_Eta_2010_qual->GetEntries();
  lax->DrawLatex(0.0,0.95,title.str().c_str());
  title.str("");
  title << "2010 # events (pass L2_DoubleMu3): " << nevt_2010_qual;
  lax->DrawLatex(0.0,0.90,title.str().c_str());

	canv->SaveAs("SingleGlb_2d_distributions_phi_2010_qual.pdf");
	
  canv->Clear(); 
	
	canv = new TCanvas("canv","canv",1300,1000);
  canv->Divide(3,3);
	
  canv->cd(1);
  SingleGlb_nValMuHits_eta_2010_qual->DrawNormalized("colz",1);
	canv->cd(2);
  SingleGlb_nValTrkHits_eta_2010_qual->DrawNormalized("colz",1);
	canv->cd(3);
  SingleGlb_glbChi2_ndof_eta_2010_qual->DrawNormalized("colz",1);
	canv->cd(4);
  SingleGlb_trkChi2_ndof_eta_2010_qual->DrawNormalized("colz",1);
	canv->cd(5);
  SingleGlb_pixLayerWMeas_eta_2010_qual->DrawNormalized("colz",1);
	canv->cd(6);
  SingleGlb_trkDz_eta_2010_qual->DrawNormalized("colz",1);
	canv->cd(7);
  SingleGlb_trkDxy_eta_2010_qual->DrawNormalized("colz",1);
	canv->cd(8);
  title.str("");
	title << "2010 # muons (pass L2_DoubleMu3): " << SingleGlb_Eta_2010_qual->GetEntries();
  lax->DrawLatex(0.0,0.95,title.str().c_str());
  title.str("");
  title << "2010 # events (pass L2_DoubleMu3): " << nevt_2010_qual;
  lax->DrawLatex(0.0,0.90,title.str().c_str());

	canv->SaveAs("SingleGlb_2d_distributions_eta_2010_qual.pdf");

  canv->Clear(); 
	
	canv = new TCanvas("canv","canv",1300,1000);
  canv->Divide(3,3);
	
  canv->cd(1);
  SingleGlb_nValMuHits_phi_2010->DrawNormalized("colz",1);
	canv->cd(2);
  SingleGlb_nValTrkHits_phi_2010->DrawNormalized("colz",1);
	canv->cd(3);
  SingleGlb_glbChi2_ndof_phi_2010->DrawNormalized("colz",1);
	canv->cd(4);
  SingleGlb_trkChi2_ndof_phi_2010->DrawNormalized("colz",1);
	canv->cd(5);
  SingleGlb_pixLayerWMeas_phi_2010->DrawNormalized("colz",1);
	canv->cd(6);
  SingleGlb_trkDz_phi_2010->DrawNormalized("colz",1);
	canv->cd(7);
  SingleGlb_trkDxy_phi_2010->DrawNormalized("colz",1);
	canv->cd(8);
  title.str("");
	title << "2010 # muons (pass L2_DoubleMu3): " << SingleGlb_Eta_2010->GetEntries();
  lax->DrawLatex(0.0,0.95,title.str().c_str());
  title.str("");
  title << "2010 # events (pass L2_DoubleMu3): " << nevt_2010;
  lax->DrawLatex(0.0,0.90,title.str().c_str());

	canv->SaveAs("SingleGlb_2d_distributions_phi_2010.pdf");
	
  canv->Clear(); 
	
	canv = new TCanvas("canv","canv",1300,1000);
  canv->Divide(3,3);
	
  canv->cd(1);
  SingleGlb_nValMuHits_eta_2010->DrawNormalized("colz",1);
	canv->cd(2);
  SingleGlb_nValTrkHits_eta_2010->DrawNormalized("colz",1);
	canv->cd(3);
  SingleGlb_glbChi2_ndof_eta_2010->DrawNormalized("colz",1);
	canv->cd(4);
  SingleGlb_trkChi2_ndof_eta_2010->DrawNormalized("colz",1);
	canv->cd(5);
  SingleGlb_pixLayerWMeas_eta_2010->DrawNormalized("colz",1);
	canv->cd(6);
  SingleGlb_trkDz_eta_2010->DrawNormalized("colz",1);
	canv->cd(7);
  SingleGlb_trkDxy_eta_2010->DrawNormalized("colz",1);
	canv->cd(8);
  title.str("");
	title << "2010 # muons (pass L2_DoubleMu3): " << SingleGlb_Eta_2010->GetEntries();
  lax->DrawLatex(0.0,0.95,title.str().c_str());
  title.str("");
  title << "2010 # events (pass L2_DoubleMu3): " << nevt_2010;
  lax->DrawLatex(0.0,0.90,title.str().c_str());

	canv->SaveAs("SingleGlb_2d_distributions_eta_2010.pdf");

  canv->Clear(); 

	canv = new TCanvas("canv","canv",1300,1000);
  canv->Divide(3,3);
	
  canv->cd(1);
  SingleGlb_nValMuHits_phi_2011_qual->DrawNormalized("colz",1);
	canv->cd(2);
  SingleGlb_nValTrkHits_phi_2011_qual->DrawNormalized("colz",1);
	canv->cd(3);
  SingleGlb_glbChi2_ndof_phi_2011_qual->DrawNormalized("colz",1);
	canv->cd(4);
  SingleGlb_trkChi2_ndof_phi_2011_qual->DrawNormalized("colz",1);
	canv->cd(5);
  SingleGlb_pixLayerWMeas_phi_2011_qual->DrawNormalized("colz",1);
	canv->cd(6);
  SingleGlb_trkDz_phi_2011_qual->DrawNormalized("colz",1);
	canv->cd(7);
  SingleGlb_trkDxy_phi_2011_qual->DrawNormalized("colz",1);
	canv->cd(8);
  title.str("");
	title << "2011 # muons (pass L2_DoubleMu3): " << SingleGlb_Eta_2011_qual->GetEntries();
  lax->DrawLatex(0.0,0.95,title.str().c_str());
  title.str("");
  title << "2011 # events (pass L2_DoubleMu3): " << nevt_2011_qual;
  lax->DrawLatex(0.0,0.90,title.str().c_str());

	canv->SaveAs("SingleGlb_2d_distributions_phi_2011_qual.pdf");
	
  canv->Clear(); 
	
	canv = new TCanvas("canv","canv",1300,1000);
  canv->Divide(3,3);
	
  canv->cd(1);
  SingleGlb_nValMuHits_eta_2011_qual->DrawNormalized("colz",1);
	canv->cd(2);
  SingleGlb_nValTrkHits_eta_2011_qual->DrawNormalized("colz",1);
	canv->cd(3);
  SingleGlb_glbChi2_ndof_eta_2011_qual->DrawNormalized("colz",1);
	canv->cd(4);
  SingleGlb_trkChi2_ndof_eta_2011_qual->DrawNormalized("colz",1);
	canv->cd(5);
  SingleGlb_pixLayerWMeas_eta_2011_qual->DrawNormalized("colz",1);
	canv->cd(6);
  SingleGlb_trkDz_eta_2011_qual->DrawNormalized("colz",1);
	canv->cd(7);
  SingleGlb_trkDxy_eta_2011_qual->DrawNormalized("colz",1);
	canv->cd(8);
  title.str("");
	title << "2011 # muons (pass L2_DoubleMu3): " << SingleGlb_Eta_2011_qual->GetEntries();
  lax->DrawLatex(0.0,0.95,title.str().c_str());
  title.str("");
  title << "2011 # events (pass L2_DoubleMu3): " << nevt_2011_qual;
  lax->DrawLatex(0.0,0.90,title.str().c_str());

	canv->SaveAs("SingleGlb_2d_distributions_eta_2011_qual.pdf");

  canv->Clear(); 
	
	canv = new TCanvas("canv","canv",1300,1000);
  canv->Divide(3,3);
	
  canv->cd(1);
  SingleGlb_nValMuHits_phi_2011->DrawNormalized("colz",1);
	canv->cd(2);
  SingleGlb_nValTrkHits_phi_2011->DrawNormalized("colz",1);
	canv->cd(3);
  SingleGlb_glbChi2_ndof_phi_2011->DrawNormalized("colz",1);
	canv->cd(4);
  SingleGlb_trkChi2_ndof_phi_2011->DrawNormalized("colz",1);
	canv->cd(5);
  SingleGlb_pixLayerWMeas_phi_2011->DrawNormalized("colz",1);
	canv->cd(6);
  SingleGlb_trkDz_phi_2011->DrawNormalized("colz",1);
	canv->cd(7);
  SingleGlb_trkDxy_phi_2011->DrawNormalized("colz",1);
	canv->cd(8);
  title.str("");
	title << "2011 # muons (pass L2_DoubleMu3): " << SingleGlb_Eta_2011->GetEntries();
  lax->DrawLatex(0.0,0.95,title.str().c_str());
  title.str("");
  title << "2011 # events (pass L2_DoubleMu3): " << nevt_2011;
  lax->DrawLatex(0.0,0.90,title.str().c_str());

	canv->SaveAs("SingleGlb_2d_distributions_phi_2011.pdf");
	
  canv->Clear(); 
	
	canv = new TCanvas("canv","canv",1300,1000);
  canv->Divide(3,3);
	
  canv->cd(1);
  SingleGlb_nValMuHits_eta_2011->DrawNormalized("colz",1);
	canv->cd(2);
  SingleGlb_nValTrkHits_eta_2011->DrawNormalized("colz",1);
	canv->cd(3);
  SingleGlb_glbChi2_ndof_eta_2011->DrawNormalized("colz",1);
	canv->cd(4);
  SingleGlb_trkChi2_ndof_eta_2011->DrawNormalized("colz",1);
	canv->cd(5);
  SingleGlb_pixLayerWMeas_eta_2011->DrawNormalized("colz",1);
	canv->cd(6);
  SingleGlb_trkDz_eta_2011->DrawNormalized("colz",1);
	canv->cd(7);
  SingleGlb_trkDxy_eta_2011->DrawNormalized("colz",1);
	canv->cd(8);
  title.str("");
	title << "2011 # muons (pass L2_DoubleMu3): " << SingleGlb_Eta_2011->GetEntries();
  lax->DrawLatex(0.0,0.95,title.str().c_str());
  title.str("");
  title << "2011 # events (pass L2_DoubleMu3): " << nevt_2011;
  lax->DrawLatex(0.0,0.90,title.str().c_str());

	canv->SaveAs("SingleGlb_2d_distributions_eta_2011.pdf");

  canv->Clear(); 
	
	canv = new TCanvas("canv","canv",1300,1000);
  canv->Divide(3,3);

  canv->cd(1);
	SingleGlb_nValMuHits_2010_qual->Sumw2();
  SingleGlb_nValMuHits_2010_qual->SetMarkerStyle(20);
  SingleGlb_nValMuHits_2010_qual->DrawNormalized("p e",1);
  SingleGlb_nValMuHits_2011_qual->Sumw2();
  SingleGlb_nValMuHits_2011_qual->SetMarkerColor(kRed);
  SingleGlb_nValMuHits_2011_qual->SetMarkerStyle(20);
  SingleGlb_nValMuHits_2011_qual->DrawNormalized("p e same",1);
  leg->AddEntry(SingleGlb_nValMuHits_2010_qual,"2010 data","lp");
  leg->AddEntry(SingleGlb_nValMuHits_2011_qual,"2011 data","lp");
  leg2->AddEntry(SingleGlb_nValMuHits_2010_qual,"2010 data","lp");
  leg2->AddEntry(SingleGlb_nValMuHits_2011_qual,"2011 data","lp");
  leg->Draw();

	canv->cd(2);
  SingleGlb_nValTrkHits_2010_qual->Sumw2();
  SingleGlb_nValTrkHits_2010_qual->SetMarkerStyle(20);
  SingleGlb_nValTrkHits_2010_qual->DrawNormalized("p e",1);
  SingleGlb_nValTrkHits_2011_qual->Sumw2();
  SingleGlb_nValTrkHits_2011_qual->SetMarkerColor(kRed);
  SingleGlb_nValTrkHits_2011_qual->SetMarkerStyle(20);
  SingleGlb_nValTrkHits_2011_qual->DrawNormalized("p e same",1);
  leg->Draw();

	canv->cd(3);
  SingleGlb_glbChi2_ndof_2010_qual->Sumw2();
  SingleGlb_glbChi2_ndof_2010_qual->SetMarkerStyle(20);
  SingleGlb_glbChi2_ndof_2010_qual->DrawNormalized("p e",1);
  SingleGlb_glbChi2_ndof_2011_qual->Sumw2();
  SingleGlb_glbChi2_ndof_2011_qual->SetMarkerColor(kRed);
  SingleGlb_glbChi2_ndof_2011_qual->SetMarkerStyle(20);
  SingleGlb_glbChi2_ndof_2011_qual->DrawNormalized("p e same",1);
  leg->Draw();

	canv->cd(4);
  SingleGlb_trkChi2_ndof_2010_qual->Sumw2();
  SingleGlb_trkChi2_ndof_2010_qual->SetMarkerStyle(20);
  SingleGlb_trkChi2_ndof_2010_qual->DrawNormalized("p e",1);
  SingleGlb_trkChi2_ndof_2011_qual->Sumw2();
  SingleGlb_trkChi2_ndof_2011_qual->SetMarkerColor(kRed);
  SingleGlb_trkChi2_ndof_2011_qual->SetMarkerStyle(20);
  SingleGlb_trkChi2_ndof_2011_qual->DrawNormalized("p e same",1);
  leg->Draw();

	canv->cd(5);
  SingleGlb_pixLayerWMeas_2010_qual->Sumw2();
  SingleGlb_pixLayerWMeas_2010_qual->SetMarkerStyle(20);
  SingleGlb_pixLayerWMeas_2010_qual->DrawNormalized("p e",1);
  SingleGlb_pixLayerWMeas_2011_qual->Sumw2();
  SingleGlb_pixLayerWMeas_2011_qual->SetMarkerColor(kRed);
  SingleGlb_pixLayerWMeas_2011_qual->SetMarkerStyle(20);
  SingleGlb_pixLayerWMeas_2011_qual->DrawNormalized("p e same",1);
  leg->Draw();

	canv->cd(6);
  SingleGlb_trkDz_2010_qual->Sumw2();
  SingleGlb_trkDz_2010_qual->SetMarkerStyle(20);
  SingleGlb_trkDz_2010_qual->DrawNormalized("p e",1);
  SingleGlb_trkDz_2011_qual->Sumw2();
  SingleGlb_trkDz_2011_qual->SetMarkerColor(kRed);
  SingleGlb_trkDz_2011_qual->SetMarkerStyle(20);
  SingleGlb_trkDz_2011_qual->DrawNormalized("p e same",1);
  leg->Draw();

	canv->cd(7);
  SingleGlb_trkDxy_2010_qual->Sumw2();
  SingleGlb_trkDxy_2010_qual->SetMarkerStyle(20);
  SingleGlb_trkDxy_2010_qual->DrawNormalized("p e",1);
  SingleGlb_trkDxy_2011_qual->Sumw2();
  SingleGlb_trkDxy_2011_qual->SetMarkerColor(kRed);
  SingleGlb_trkDxy_2011_qual->SetMarkerStyle(20);
  SingleGlb_trkDxy_2011_qual->DrawNormalized("p e same",1);
  leg->Draw();
	
	canv->cd(8);
	title.str("");
	title << "2010 # muons (pass L2_DoubleMu3): " << SingleGlb_Eta_2010_qual->GetEntries();
  lax->DrawLatex(0.0,0.95,title.str().c_str());
  title.str("");
  title << "2010 # events (pass L2_DoubleMu3): " << nevt_2010_qual;
  lax->DrawLatex(0.0,0.90,title.str().c_str());
  title.str("");
  title << "2011 # muons (pass L2_DoubleMu3): " << SingleGlb_Eta_2011_qual->GetEntries();
  lax->DrawLatex(0.0,0.85,title.str().c_str());
  title.str("");
  title << "2011 # events (pass L2_DoubleMu3): " << nevt_2011_qual;
  lax->DrawLatex(0.0,0.80,title.str().c_str());

	canv->SaveAs("SingleGlb_distributions_qual.pdf");
	
  canv->Clear(); 
	
	canv = new TCanvas("canv","canv",1300,1000);
  canv->Divide(3,3);

  canv->cd(1);
	SingleGlb_nValMuHits_2010->Sumw2();
  SingleGlb_nValMuHits_2010->SetMarkerStyle(20);
  SingleGlb_nValMuHits_2010->DrawNormalized("p e",1);
  SingleGlb_nValMuHits_2011->Sumw2();
  SingleGlb_nValMuHits_2011->SetMarkerColor(kRed);
  SingleGlb_nValMuHits_2011->SetMarkerStyle(20);
  SingleGlb_nValMuHits_2011->DrawNormalized("p e same",1);
  leg->Draw();

	canv->cd(2);
  SingleGlb_nValTrkHits_2010->Sumw2();
  SingleGlb_nValTrkHits_2010->SetMarkerStyle(20);
  SingleGlb_nValTrkHits_2010->DrawNormalized("p e",1);
  SingleGlb_nValTrkHits_2011->Sumw2();
  SingleGlb_nValTrkHits_2011->SetMarkerColor(kRed);
  SingleGlb_nValTrkHits_2011->SetMarkerStyle(20);
  SingleGlb_nValTrkHits_2011->DrawNormalized("p e same",1);
  leg->Draw();

	canv->cd(3);
  SingleGlb_glbChi2_ndof_2010->Sumw2();
  SingleGlb_glbChi2_ndof_2010->SetMarkerStyle(20);
  SingleGlb_glbChi2_ndof_2010->DrawNormalized("p e",1);
  SingleGlb_glbChi2_ndof_2011->Sumw2();
  SingleGlb_glbChi2_ndof_2011->SetMarkerColor(kRed);
  SingleGlb_glbChi2_ndof_2011->SetMarkerStyle(20);
  SingleGlb_glbChi2_ndof_2011->DrawNormalized("p e same",1);
  leg->Draw();

	canv->cd(4);
  SingleGlb_trkChi2_ndof_2010->Sumw2();
  SingleGlb_trkChi2_ndof_2010->SetMarkerStyle(20);
  SingleGlb_trkChi2_ndof_2010->DrawNormalized("p e",1);
  SingleGlb_trkChi2_ndof_2011->Sumw2();
  SingleGlb_trkChi2_ndof_2011->SetMarkerColor(kRed);
  SingleGlb_trkChi2_ndof_2011->SetMarkerStyle(20);
  SingleGlb_trkChi2_ndof_2011->DrawNormalized("p e same",1);
  leg->Draw();

	canv->cd(5);
  SingleGlb_pixLayerWMeas_2010->Sumw2();
  SingleGlb_pixLayerWMeas_2010->SetMarkerStyle(20);
  SingleGlb_pixLayerWMeas_2010->DrawNormalized("p e",1);
  SingleGlb_pixLayerWMeas_2011->Sumw2();
  SingleGlb_pixLayerWMeas_2011->SetMarkerColor(kRed);
  SingleGlb_pixLayerWMeas_2011->SetMarkerStyle(20);
  SingleGlb_pixLayerWMeas_2011->DrawNormalized("p e same",1);
  leg->Draw();

	canv->cd(6);
  SingleGlb_trkDz_2010->Sumw2();
  SingleGlb_trkDz_2010->SetMarkerStyle(20);
  SingleGlb_trkDz_2010->DrawNormalized("p e",1);
  SingleGlb_trkDz_2011->Sumw2();
  SingleGlb_trkDz_2011->SetMarkerColor(kRed);
  SingleGlb_trkDz_2011->SetMarkerStyle(20);
  SingleGlb_trkDz_2011->DrawNormalized("p e same",1);
  leg->Draw();

	canv->cd(7);
  SingleGlb_trkDxy_2010->Sumw2();
  SingleGlb_trkDxy_2010->SetMarkerStyle(20);
  SingleGlb_trkDxy_2010->DrawNormalized("p e",1);
  SingleGlb_trkDxy_2011->Sumw2();
  SingleGlb_trkDxy_2011->SetMarkerColor(kRed);
  SingleGlb_trkDxy_2011->SetMarkerStyle(20);
  SingleGlb_trkDxy_2011->DrawNormalized("p e same",1);
  leg->Draw();
	
	canv->cd(8);
  title.str("");
	title << "2010 # muons (within |eta| < 2.4): " << SingleGlb_Eta_2010->GetEntries();
  lax->DrawLatex(0.0,0.95,title.str().c_str());
  title.str("");
  title << "2010 # events: " << nevt_2010;
  lax->DrawLatex(0.0,0.90,title.str().c_str());
  title.str("");
  title << "2011 # muons (within |eta| < 2.4): " << SingleGlb_Eta_2011->GetEntries();
  lax->DrawLatex(0.0,0.85,title.str().c_str());
  title.str("");
  title << "2011 # events: " << nevt_2011;
  lax->DrawLatex(0.0,0.80,title.str().c_str());

	canv->SaveAs("SingleGlb_distributions.pdf");
	
  canv->Clear(); 
  
  return 0;
}
