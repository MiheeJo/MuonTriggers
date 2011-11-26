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
#include <TLine.h>

using namespace std;

int singleMu_quality_separate_modified() {

  // Parameters  
  FLAG *flag = new FLAG;
  flag->doSta = false;
  flag->doGlb = true;

//	string data2010 = "/castor/cern.ch/user/m/miheejo/openHLT/cms413p3/HIRun2010-SDmaker_3SD_1CS_PDHIAllPhysicsZSv2_SD_MuHI-v1/openHLT_rootv1.root";
//  string data2010 = "/castor/cern.ch/user/m/miheejo/openHLT/cms413p3/HIRun2010-SDmaker_3SD_1CS_PDHIAllPhysicsZSv2_SD_MuHI-v1/openHLT_noTrgFilter_rootv1.root";
  string data2010 = "/castor/cern.ch/user/m/miheejo/openHLT/cms413p3/HIRun2010-SDmaker_3SD_1CS_PDHIAllPhysicsZSv2_SD_MuHI-v1/openHLT_L1SingleMu3_L2Mu3.root";
	//  string data2011 = "/castor/cern.ch/user/m/miheejo/openHLT/RD2011/HIDiMuon_HIRun2011-PromptReco-v1_RECO/openhlt_PromptReco_181611_181778.root";
//  string data2011 = "/castor/cern.ch/user/m/miheejo/openHLT/RD2011/HIDiMuon_HIRun2011-PromptReco-v1_RECO/openHLT_PromptReco_181611_181778_noTrgFilter.root";

	string data2011 = "/castor/cern.ch/user/m/miheejo/openHLT/RD2011/HIDiMuon_HIRun2011-PromptReco-v1_RECO/openhlt_PromptReco_181611_182099_L2Mu3_NHitQ.root";
//	string data2011 = "/castor/cern.ch/user/m/miheejo/openHLT/RD2011/HIDiMuon_HIRun2011-PromptReco-v1_RECO/openhlt_PromptReco_182124_L2Mu3_NHitQ.root";
//	string data2011 = "/castor/cern.ch/user/m/miheejo/openHLT/RD2011/HIDiMuon_HIRun2011-PromptReco-v1_RECO/openhlt_PromptReco_182124_L2Mu3_NHitQ.root";
//  string data2010  = "/castor/cern.ch/user/m/miheejo/openHLT/cms442p5/HICorePhysics_Skim_MinimumBias_RAW/openhlt_2010HICorePhysicsMB.root";
//  string data2011  = "/castor/cern.ch/user/m/miheejo/openHLT/RD2011/HIData2011_rawToRecoV3_LSF/openhlt_HIData2011_rawToRecoV3_LSF.root";
//  string data2011 = "/castor/cern.ch/user/m/miheejo/openHLT/RD2011/HIDiMuon_HIRun2011-PromptReco-v1_RECO/openhlt_PromptReco_181611_181758.root";

  // Check trigger list
  vector<string> triglist;
//	triglist.push_back("HLT_HIL1SingleMu3");
	triglist.push_back("HLT_HIL2Mu3");
	triglist.push_back("HLT_HIL2Mu3_NHitQ_v1");
	triglist.push_back("HLT_HIL2Mu3_NHitQ_v2");
//  triglist.push_back("HLT_HIL1DoubleMu0_HighQ_v1");
//  triglist.push_back("HLT_HIL2DoubleMu3_v1");
//  triglist.push_back("HLT_HIL3DoubleMuOpen_v1");
//  triglist.push_back("HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy_v1");
//  triglist.push_back("HLT_HIL2Mu3_v1");
//  triglist.push_back("HLT_HIL2Mu7_v1");
//  triglist.push_back("HLT_HIL2Mu15_v1");
//  triglist.push_back("HLT_HIL2Mu3_NHitQ_v1");
//  triglist.push_back("HLT_HIL3Mu3_v1");


  // Histograms
  TH2F *SingleGlb_Etapt_2010 = new TH2F("etapt_2010","etapt_2010;single mu #eta;single mu p_{T}",ETA,-2.4,2.4,60,0,60);
  TH2F *SingleGlb_Etapt_2011 = new TH2F("etapt_2011","etapt_2011;single mu #eta;single mu p_{T}",ETA,-2.4,2.4,60,0,60);
  TH2F *SingleGlb_Etaphi_2010 = new TH2F("etaphi_2010","etaphi_2010;single mu #eta;single mu #phi",ETA,-2.4,2.4,20,-PI,PI);
  TH2F *SingleGlb_Etaphi_2011 = new TH2F("etaphi_2011","etaphi_2011;single mu #eta;single mu #phi",ETA,-2.4,2.4,20,-PI,PI);

  TH1F *SingleGlb_Eta_2010 = new TH1F("eta_2010","eta_2010;single mu #eta",ETA,-2.4,2.4);
  TH1F *SingleGlb_Eta_2011 = new TH1F("eta_2011","eta_2011;single mu #eta",ETA,-2.4,2.4);
  TH1F *SingleGlb_Phi_2010 = new TH1F("phi_2010","phi_2010;single mu #phi",20,-PI,PI);
  TH1F *SingleGlb_Phi_2011 = new TH1F("phi_2011","phi_2011;single mu #phi",20,-PI,PI);
  TH1F *SingleGlb_Pt_2010 = new TH1F("pt_2010","pt_2010;single mu p_{T}",60,0,60);
  TH1F *SingleGlb_Pt_2011 = new TH1F("pt_2011","pt_2011;single mu p_{T}",60,0,60);

	TH2F *SingleGlb_nValMuHits_eta_2010 = new TH2F("nValMuHits_eta_2010","nValMuHits_eta_2010;nValMuHits;#eta",55,0,55,ETA,-2.4,2.4);
  TH2F *SingleGlb_nValTrkHits_eta_2010 = new TH2F("nValTrkHits_eta_2010","nValTrkHits_eta_2010;nValTrkHits;#eta",27,0,27,ETA,-2.4,2.4);
  TH2F *SingleGlb_glbChi2_ndof_eta_2010 = new TH2F("glbChi2_ndof_eta_2010","glbChi2_ndof_eta_2010;glbChi2_ndof;#eta",100,0,25,ETA,-2.4,2.4);
  TH2F *SingleGlb_trkChi2_ndof_eta_2010 = new TH2F("trkChi2_ndof_eta_2010","trkChi2_ndof_eta_2010;trkChi2_ndof;#eta",100,0,10,ETA,-2.4,2.4);
  TH2F *SingleGlb_pixLayerWMeas_eta_2010 = new TH2F("pixLayerWMeas_eta_2010","pixLayerWMeas_eta_2010;pixLayerWMeas;#eta",5,0,5,ETA,-2.4,2.4);
  TH2F *SingleGlb_trkDz_eta_2010 = new TH2F("trkDz_eta_2010","trkDz_eta_2010;trkDz;#eta",100,0,2,ETA,-2.4,2.4);
  TH2F *SingleGlb_trkDxy_eta_2010 = new TH2F("trkDxy_eta_2010","trkDxy_eta_2010;trkDxy;#eta",100,0,2,ETA,-2.4,2.4);

	TH2F *SingleGlb_nValMuHits_pt_2010 = new TH2F("nValMuHits_pt_2010","nValMuHits_pt_2010;nValMuHits;p_{T}",55,0,55,60,0,60);
  TH2F *SingleGlb_nValTrkHits_pt_2010 = new TH2F("nValTrkHits_pt_2010","nValTrkHits_pt_2010;nValTrkHits;p_{T}",27,0,27,60,0,60);
  TH2F *SingleGlb_glbChi2_ndof_pt_2010 = new TH2F("glbChi2_ndof_pt_2010","glbChi2_ndof_pt_2010;glbChi2_ndof;p_{T}",100,0,25,60,0,60);
  TH2F *SingleGlb_trkChi2_ndof_pt_2010 = new TH2F("trkChi2_ndof_pt_2010","trkChi2_ndof_pt_2010;trkChi2_ndof;p_{T}",100,0,10,60,0,60);
  TH2F *SingleGlb_pixLayerWMeas_pt_2010 = new TH2F("pixLayerWMeas_pt_2010","pixLayerWMeas_pt_2010;pixLayerWMeas;p_{T}",5,0,5,60,0,60);
  TH2F *SingleGlb_trkDz_pt_2010 = new TH2F("trkDz_pt_2010","trkDz_pt_2010;trkDz;p_{T}",100,0,2,60,0,60);
  TH2F *SingleGlb_trkDxy_pt_2010 = new TH2F("trkDxy_pt_2010","trkDxy_pt_2010;trkDxy;p_{T}",100,0,2,60,0,60);

	TH2F *SingleGlb_nValMuHits_phi_2010 = new TH2F("nValMuHits_phi_2010","nValMuHits_phi_2010;nValMuHits;#phi",55,0,55,PHI,-PI,PI);
  TH2F *SingleGlb_nValTrkHits_phi_2010 = new TH2F("nValTrkHits_phi_2010","nValTrkHits_phi_2010;nValTrkHits;#phi",27,0,27,PHI,-PI,PI);
  TH2F *SingleGlb_glbChi2_ndof_phi_2010 = new TH2F("glbChi2_ndof_phi_2010","glbChi2_ndof_phi_2010;glbChi2_ndof;#phi",100,0,25,PHI,-PI,PI);
  TH2F *SingleGlb_trkChi2_ndof_phi_2010 = new TH2F("trkChi2_ndof_phi_2010","trkChi2_ndof_phi_2010;trkChi2_ndof;#phi",100,0,10,PHI,-PI,PI);
  TH2F *SingleGlb_pixLayerWMeas_phi_2010 = new TH2F("pixLayerWMeas_phi_2010","pixLayerWMeas_phi_2010;pixLayerWMeas;#phi",5,0,5,PHI,-PI,PI);
  TH2F *SingleGlb_trkDz_phi_2010 = new TH2F("trkDz_phi_2010","trkDz_phi_2010;trkDz;#phi",100,0,2,PHI,-PI,PI);
  TH2F *SingleGlb_trkDxy_phi_2010 = new TH2F("trkDxy_phi_2010","trkDxy_phi_2010;trkDxy;#phi",100,0,2,PHI,-PI,PI);
	
	TH1F *SingleGlb_nValMuHits_2010 = new TH1F("nValMuHits_2010","nValMuHits_2010;nValMuHits",55,0,55);
  TH1F *SingleGlb_nValTrkHits_2010 = new TH1F("nValTrkHits_2010","nValTrkHits_2010;nValTrkHits",27,0,27);
  TH1F *SingleGlb_glbChi2_ndof_2010 = new TH1F("glbChi2_ndof_2010","glbChi2_ndof_2010;glbChi2_ndof",100,0,25);
  TH1F *SingleGlb_trkChi2_ndof_2010 = new TH1F("trkChi2_ndof_2010","trkChi2_ndof_2010;trkChi2_ndof",100,0,10);
  TH1F *SingleGlb_pixLayerWMeas_2010 = new TH1F("pixLayerWMeas_2010","pixLayerWMeas_2010;pixLayerWMeas",5,0,5);
  TH1F *SingleGlb_trkDz_2010 = new TH1F("trkDz_2010","trkDz_2010;trkDz",100,0,2);
  TH1F *SingleGlb_trkDxy_2010 = new TH1F("trkDxy_2010","trkDxy_2010;trkDxy",100,0,2);

	TH2F *SingleGlb_nValMuHits_eta_2011 = new TH2F("nValMuHits_eta_2011","nValMuHits_eta_2011;nValMuHits;#eta",55,0,55,ETA,-2.4,2.4);
  TH2F *SingleGlb_nValTrkHits_eta_2011 = new TH2F("nValTrkHits_eta_2011","nValTrkHits_eta_2011;nValTrkHits;#eta",27,0,27,ETA,-2.4,2.4);
  TH2F *SingleGlb_glbChi2_ndof_eta_2011 = new TH2F("glbChi2_ndof_eta_2011","glbChi2_ndof_eta_2011;glbChi2_ndof;#eta",100,0,25,ETA,-2.4,2.4);
  TH2F *SingleGlb_trkChi2_ndof_eta_2011 = new TH2F("trkChi2_ndof_eta_2011","trkChi2_ndof_eta_2011;trkChi2_ndof;#eta",100,0,10,ETA,-2.4,2.4);
  TH2F *SingleGlb_pixLayerWMeas_eta_2011 = new TH2F("pixLayerWMeas_eta_2011","pixLayerWMeas_eta_2011;pixLayerWMeas;#eta",5,0,5,ETA,-2.4,2.4);
  TH2F *SingleGlb_trkDz_eta_2011 = new TH2F("trkDz_eta_2011","trkDz_eta_2011;trkDz;#eta",100,0,2,ETA,-2.4,2.4);
  TH2F *SingleGlb_trkDxy_eta_2011 = new TH2F("trkDxy_eta_2011","trkDxy_eta_2011;trkDxy;#eta",100,0,2,ETA,-2.4,2.4);

	TH2F *SingleGlb_nValMuHits_pt_2011 = new TH2F("nValMuHits_pt_2011","nValMuHits_pt_2011;nValMuHits;p_{T}",55,0,55,60,0,60);
  TH2F *SingleGlb_nValTrkHits_pt_2011 = new TH2F("nValTrkHits_pt_2011","nValTrkHits_pt_2011;nValTrkHits;p_{T}",27,0,27,60,0,60);
  TH2F *SingleGlb_glbChi2_ndof_pt_2011 = new TH2F("glbChi2_ndof_pt_2011","glbChi2_ndof_pt_2011;glbChi2_ndof;p_{T}",100,0,25,60,0,60);
  TH2F *SingleGlb_trkChi2_ndof_pt_2011 = new TH2F("trkChi2_ndof_pt_2011","trkChi2_ndof_pt_2011;trkChi2_ndof;p_{T}",100,0,10,60,0,60);
  TH2F *SingleGlb_pixLayerWMeas_pt_2011 = new TH2F("pixLayerWMeas_pt_2011","pixLayerWMeas_pt_2011;pixLayerWMeas;p_{T}",5,0,5,60,0,60);
  TH2F *SingleGlb_trkDz_pt_2011 = new TH2F("trkDz_pt_2011","trkDz_pt_2011;trkDz;p_{T}",100,0,2,60,0,60);
  TH2F *SingleGlb_trkDxy_pt_2011 = new TH2F("trkDxy_pt_2011","trkDxy_pt_2011;trkDxy;p_{T}",100,0,2,60,0,60);

	TH2F *SingleGlb_nValMuHits_phi_2011 = new TH2F("nValMuHits_phi_2011","nValMuHits_phi_2011;nValMuHits;#phi",55,0,55,PHI,-PI,PI);
  TH2F *SingleGlb_nValTrkHits_phi_2011 = new TH2F("nValTrkHits_phi_2011","nValTrkHits_phi_2011;nValTrkHits;#phi",27,0,27,PHI,-PI,PI);
  TH2F *SingleGlb_glbChi2_ndof_phi_2011 = new TH2F("glbChi2_ndof_phi_2011","glbChi2_ndof_phi_2011;glbChi2_ndof;#phi",100,0,25,PHI,-PI,PI);
  TH2F *SingleGlb_trkChi2_ndof_phi_2011 = new TH2F("trkChi2_ndof_phi_2011","trkChi2_ndof_phi_2011;trkChi2_ndof;#phi",100,0,10,PHI,-PI,PI);
  TH2F *SingleGlb_pixLayerWMeas_phi_2011 = new TH2F("pixLayerWMeas_phi_2011","pixLayerWMeas_phi_2011;pixLayerWMeas;#phi",5,0,5,PHI,-PI,PI);
  TH2F *SingleGlb_trkDz_phi_2011 = new TH2F("trkDz_phi_2011","trkDz_phi_2011;trkDz;#phi",100,0,2,PHI,-PI,PI);
  TH2F *SingleGlb_trkDxy_phi_2011 = new TH2F("trkDxy_phi_2011","trkDxy_phi_2011;trkDxy;#phi",100,0,2,PHI,-PI,PI);

	TH1F *SingleGlb_nValMuHits_2011 = new TH1F("nValMuHits_2011","nValMuHits_2011;nValMuHits",55,0,55);
  TH1F *SingleGlb_nValTrkHits_2011 = new TH1F("nValTrkHits_2011","nValTrkHits_2011;nValTrkHits",27,0,27);
  TH1F *SingleGlb_glbChi2_ndof_2011 = new TH1F("glbChi2_ndof_2011","glbChi2_ndof_2011;glbChi2_ndof",100,0,25);
  TH1F *SingleGlb_trkChi2_ndof_2011 = new TH1F("trkChi2_ndof_2011","trkChi2_ndof_2011;trkChi2_ndof",100,0,10);
  TH1F *SingleGlb_pixLayerWMeas_2011 = new TH1F("pixLayerWMeas_2011","pixLayerWMeas_2011;pixLayerWMeas",5,0,5);
  TH1F *SingleGlb_trkDz_2011 = new TH1F("trkDz_2011","trkDz_2011;trkDz",100,0,2);
  TH1F *SingleGlb_trkDxy_2011 = new TH1F("trkDxy_2011","trkDxy_2011;trkDxy",100,0,2);

	TH2F *SingleGlb_nValMuHits_eta_2010_qual = new TH2F("nValMuHits_eta_2010_qual","nValMuHits_eta_2010_qual;nValMuHits;#eta",55,0,55,ETA,-2.4,2.4);
  TH2F *SingleGlb_nValTrkHits_eta_2010_qual = new TH2F("nValTrkHits_eta_2010_qual","nValTrkHits_eta_2010_qual;nValTrkHits;#eta",27,0,27,ETA,-2.4,2.4);
  TH2F *SingleGlb_glbChi2_ndof_eta_2010_qual = new TH2F("glbChi2_ndof_eta_2010_qual","glbChi2_ndof_eta_2010_qual;glbChi2_ndof;#eta",100,0,25,ETA,-2.4,2.4);
  TH2F *SingleGlb_trkChi2_ndof_eta_2010_qual = new TH2F("trkChi2_ndof_eta_2010_qual","trkChi2_ndof_eta_2010_qual;trkChi2_ndof;#eta",100,0,10,ETA,-2.4,2.4);
  TH2F *SingleGlb_pixLayerWMeas_eta_2010_qual = new TH2F("pixLayerWMeas_eta_2010_qual","pixLayerWMeas_eta_2010_qual;pixLayerWMeas;#eta",5,0,5,ETA,-2.4,2.4);
  TH2F *SingleGlb_trkDz_eta_2010_qual = new TH2F("trkDz_eta_2010_qual","trkDz_eta_2010_qual;trkDz;#eta",100,0,2,ETA,-2.4,2.4);
  TH2F *SingleGlb_trkDxy_eta_2010_qual = new TH2F("trkDxy_eta_2010_qual","trkDxy_eta_2010_qual;trkDxy;#eta",100,0,2,ETA,-2.4,2.4);

	TH2F *SingleGlb_nValMuHits_pt_2010_qual = new TH2F("nValMuHits_pt_2010_qual","nValMuHits_pt_2010_qual;nValMuHits;p_{T}",55,0,55,60,0,60);
  TH2F *SingleGlb_nValTrkHits_pt_2010_qual = new TH2F("nValTrkHits_pt_2010_qual","nValTrkHits_pt_2010_qual;nValTrkHits;p_{T}",27,0,27,60,0,60);
  TH2F *SingleGlb_glbChi2_ndof_pt_2010_qual = new TH2F("glbChi2_ndof_pt_2010_qual","glbChi2_ndof_pt_2010_qual;glbChi2_ndof;p_{T}",100,0,25,60,0,60);
  TH2F *SingleGlb_trkChi2_ndof_pt_2010_qual = new TH2F("trkChi2_ndof_pt_2010_qual","trkChi2_ndof_pt_2010_qual;trkChi2_ndof;p_{T}",100,0,10,60,0,60);
  TH2F *SingleGlb_pixLayerWMeas_pt_2010_qual = new TH2F("pixLayerWMeas_pt_2010_qual","pixLayerWMeas_pt_2010_qual;pixLayerWMeas;p_{T}",5,0,5,60,0,60);
  TH2F *SingleGlb_trkDz_pt_2010_qual = new TH2F("trkDz_pt_2010_qual","trkDz_pt_2010_qual;trkDz;p_{T}",100,0,2,60,0,60);
  TH2F *SingleGlb_trkDxy_pt_2010_qual = new TH2F("trkDxy_pt_2010_qual","trkDxy_pt_2010_qual;trkDxy;p_{T}",100,0,2,60,0,60);

	TH2F *SingleGlb_nValMuHits_phi_2010_qual = new TH2F("nValMuHits_phi_2010_qual","nValMuHits_phi_2010_qual;nValMuHits;#phi",55,0,55,PHI,-PI,PI);
  TH2F *SingleGlb_nValTrkHits_phi_2010_qual = new TH2F("nValTrkHits_phi_2010_qual","nValTrkHits_phi_2010_qual;nValTrkHits;#phi",27,0,27,PHI,-PI,PI);
  TH2F *SingleGlb_glbChi2_ndof_phi_2010_qual = new TH2F("glbChi2_ndof_phi_2010_qual","glbChi2_ndof_phi_2010_qual;glbChi2_ndof;#phi",100,0,25,PHI,-PI,PI);
  TH2F *SingleGlb_trkChi2_ndof_phi_2010_qual = new TH2F("trkChi2_ndof_phi_2010_qual","trkChi2_ndof_phi_2010_qual;trkChi2_ndof;#phi",100,0,10,PHI,-PI,PI);
  TH2F *SingleGlb_pixLayerWMeas_phi_2010_qual = new TH2F("pixLayerWMeas_phi_2010_qual","pixLayerWMeas_phi_2010_qual;pixLayerWMeas;#phi",5,0,5,PHI,-PI,PI);
  TH2F *SingleGlb_trkDz_phi_2010_qual = new TH2F("trkDz_phi_2010_qual","trkDz_phi_2010_qual;trkDz;#phi",100,0,2,PHI,-PI,PI);
  TH2F *SingleGlb_trkDxy_phi_2010_qual = new TH2F("trkDxy_phi_2010_qual","trkDxy_phi_2010_qual;trkDxy;#phi",100,0,2,PHI,-PI,PI);

	TH1F *SingleGlb_nValMuHits_2010_qual = new TH1F("nValMuHits_2010_qual","nValMuHits_2010_qual;nValMuHits",55,0,55);
  TH1F *SingleGlb_nValTrkHits_2010_qual = new TH1F("nValTrkHits_2010_qual","nValTrkHits_2010_qual;nValTrkHits",27,0,27);
  TH1F *SingleGlb_glbChi2_ndof_2010_qual = new TH1F("glbChi2_ndof_2010_qual","glbChi2_ndof_2010_qual;glbChi2_ndof",100,0,25);
  TH1F *SingleGlb_trkChi2_ndof_2010_qual = new TH1F("trkChi2_ndof_2010_qual","trkChi2_ndof_2010_qual;trkChi2_ndof",100,0,10);
  TH1F *SingleGlb_pixLayerWMeas_2010_qual = new TH1F("pixLayerWMeas_2010_qual","pixLayerWMeas_2010_qual;pixLayerWMeas",5,0,5);
  TH1F *SingleGlb_trkDz_2010_qual = new TH1F("trkDz_2010_qual","trkDz_2010_qual;trkDz",100,0,2);
  TH1F *SingleGlb_trkDxy_2010_qual = new TH1F("trkDxy_2010_qual","trkDxy_2010_qual;trkDxy",100,0,2);

	TH2F *SingleGlb_nValMuHits_eta_2011_qual = new TH2F("nValMuHits_eta_2011_qual","nValMuHits_eta_2011_qual;nValMuHits;#eta",55,0,55,ETA,-2.4,2.4);
  TH2F *SingleGlb_nValTrkHits_eta_2011_qual = new TH2F("nValTrkHits_eta_2011_qual","nValTrkHits_eta_2011_qual;nValTrkHits;#eta",27,0,27,ETA,-2.4,2.4);
  TH2F *SingleGlb_glbChi2_ndof_eta_2011_qual = new TH2F("glbChi2_ndof_eta_2011_qual","glbChi2_ndof_eta_2011_qual;glbChi2_ndof;#eta",100,0,25,ETA,-2.4,2.4);
  TH2F *SingleGlb_trkChi2_ndof_eta_2011_qual = new TH2F("trkChi2_ndof_eta_2011_qual","trkChi2_ndof_eta_2011_qual;trkChi2_ndof;#eta",100,0,10,ETA,-2.4,2.4);
  TH2F *SingleGlb_pixLayerWMeas_eta_2011_qual = new TH2F("pixLayerWMeas_eta_2011_qual","pixLayerWMeas_eta_2011_qual;pixLayerWMeas;#eta",5,0,5,ETA,-2.4,2.4);
  TH2F *SingleGlb_trkDz_eta_2011_qual = new TH2F("trkDz_eta_2011_qual","trkDz_eta_2011_qual;trkDz;#eta",100,0,2,ETA,-2.4,2.4);
  TH2F *SingleGlb_trkDxy_eta_2011_qual = new TH2F("trkDxy_eta_2011_qual","trkDxy_eta_2011_qual;trkDxy;#eta",100,0,2,ETA,-2.4,2.4);

	TH2F *SingleGlb_nValMuHits_pt_2011_qual = new TH2F("nValMuHits_pt_2011_qual","nValMuHits_pt_2011_qual;nValMuHits;p_{T}",55,0,55,60,0,60);
  TH2F *SingleGlb_nValTrkHits_pt_2011_qual = new TH2F("nValTrkHits_pt_2011_qual","nValTrkHits_pt_2011_qual;nValTrkHits;p_{T}",27,0,27,60,0,60);
  TH2F *SingleGlb_glbChi2_ndof_pt_2011_qual = new TH2F("glbChi2_ndof_pt_2011_qual","glbChi2_ndof_pt_2011_qual;glbChi2_ndof;p_{T}",100,0,25,60,0,60);
  TH2F *SingleGlb_trkChi2_ndof_pt_2011_qual = new TH2F("trkChi2_ndof_pt_2011_qual","trkChi2_ndof_pt_2011_qual;trkChi2_ndof;p_{T}",100,0,10,60,0,60);
  TH2F *SingleGlb_pixLayerWMeas_pt_2011_qual = new TH2F("pixLayerWMeas_pt_2011_qual","pixLayerWMeas_pt_2011_qual;pixLayerWMeas;p_{T}",5,0,5,60,0,60);
  TH2F *SingleGlb_trkDz_pt_2011_qual = new TH2F("trkDz_pt_2011_qual","trkDz_pt_2011_qual;trkDz;p_{T}",100,0,2,60,0,60);
  TH2F *SingleGlb_trkDxy_pt_2011_qual = new TH2F("trkDxy_pt_2011_qual","trkDxy_pt_2011_qual;trkDxy;p_{T}",100,0,2,60,0,60);	
	
	TH2F *SingleGlb_nValMuHits_phi_2011_qual = new TH2F("nValMuHits_phi_2011_qual","nValMuHits_phi_2011_qual;nValMuHits;#phi",55,0,55,PHI,-PI,PI);
  TH2F *SingleGlb_nValTrkHits_phi_2011_qual = new TH2F("nValTrkHits_phi_2011_qual","nValTrkHits_phi_2011_qual;nValTrkHits;#phi",27,0,27,PHI,-PI,PI);
  TH2F *SingleGlb_glbChi2_ndof_phi_2011_qual = new TH2F("glbChi2_ndof_phi_2011_qual","glbChi2_ndof_phi_2011_qual;glbChi2_ndof;#phi",100,0,25,PHI,-PI,PI);
  TH2F *SingleGlb_trkChi2_ndof_phi_2011_qual = new TH2F("trkChi2_ndof_phi_2011_qual","trkChi2_ndof_phi_2011_qual;trkChi2_ndof;#phi",100,0,10,PHI,-PI,PI);
  TH2F *SingleGlb_pixLayerWMeas_phi_2011_qual = new TH2F("pixLayerWMeas_phi_2011_qual","pixLayerWMeas_phi_2011_qual;pixLayerWMeas;#phi",5,0,5,PHI,-PI,PI);
  TH2F *SingleGlb_trkDz_phi_2011_qual = new TH2F("trkDz_phi_2011_qual","trkDz_phi_2011_qual;trkDz;#phi",100,0,2,PHI,-PI,PI);
  TH2F *SingleGlb_trkDxy_phi_2011_qual = new TH2F("trkDxy_phi_2011_qual","trkDxy_phi_2011_qual;trkDxy;#phi",100,0,2,PHI,-PI,PI);

	TH1F *SingleGlb_nValMuHits_2011_qual = new TH1F("nValMuHits_2011_qual","nValMuHits_2011_qual;nValMuHits",55,0,55);
  TH1F *SingleGlb_nValTrkHits_2011_qual = new TH1F("nValTrkHits_2011_qual","nValTrkHits_2011_qual;nValTrkHits",27,0,27);
  TH1F *SingleGlb_glbChi2_ndof_2011_qual = new TH1F("glbChi2_ndof_2011_qual","glbChi2_ndof_2011_qual;glbChi2_ndof",100,0,25);
  TH1F *SingleGlb_trkChi2_ndof_2011_qual = new TH1F("trkChi2_ndof_2011_qual","trkChi2_ndof_2011_qual;trkChi2_ndof",100,0,10);
  TH1F *SingleGlb_pixLayerWMeas_2011_qual = new TH1F("pixLayerWMeas_2011_qual","pixLayerWMeas_2011_qual;pixLayerWMeas",5,0,5);
  TH1F *SingleGlb_trkDz_2011_qual = new TH1F("trkDz_2011_qual","trkDz_2011_qual;trkDz",100,0,2);
  TH1F *SingleGlb_trkDxy_2011_qual = new TH1F("trkDxy_2011_qual","trkDxy_2011_qual;trkDxy",100,0,2);
	
  TH2F *SingleGlb_Etapt_2010_qual = new TH2F("etapt_2010_qual","etapt_2010_qual;single mu #eta;single mu p_{T}",ETA,-2.4,2.4,60,0,60);
  TH2F *SingleGlb_Etapt_2011_qual = new TH2F("etapt_2011_qual","etapt_2011_qual;single mu #eta;single mu p_{T}",ETA,-2.4,2.4,60,0,60);
  TH2F *SingleGlb_Etaphi_2010_qual = new TH2F("etaphi_2010_qual","etaphi_2010_qual;single mu #eta;single mu #phi",ETA,-2.4,2.4,20,-PI,PI);
  TH2F *SingleGlb_Etaphi_2011_qual = new TH2F("etaphi_2011_qual","etaphi_2011_qual;single mu #eta;single mu #phi",ETA,-2.4,2.4,20,-PI,PI);

  TH1F *SingleGlb_Eta_2010_qual = new TH1F("eta_2010_qual","eta_2010_qual;single mu #eta",ETA,-2.4,2.4);
  TH1F *SingleGlb_Eta_2011_qual = new TH1F("eta_2011_qual","eta_2011_qual;single mu #eta",ETA,-2.4,2.4);
  TH1F *SingleGlb_Phi_2010_qual = new TH1F("phi_2010_qual","phi_2010_qual;single mu #phi",20,-PI,PI);
  TH1F *SingleGlb_Phi_2011_qual = new TH1F("phi_2011_qual","phi_2011_qual;single mu #phi",20,-PI,PI);
  TH1F *SingleGlb_Pt_2010_qual = new TH1F("pt_2010_qual","pt_2010_qual;single mu p_{T}",60,0,60);
  TH1F *SingleGlb_Pt_2011_qual = new TH1F("pt_2011_qual","pt_2011_qual;single mu p_{T}",60,0,60);
	
  // Input files
  // 2010 datafile
	cout << "Opening 2010 input file..." << endl;
  TCastorFile   *input_2010 = new TCastorFile(data2010.c_str());
	cout << "2010 input file opened" << endl;
  FriendMuTree  *mutree_2010 = new FriendMuTree(input_2010,true); // Load HLTMuTree
  HltTree       *ohTree_2010 = new HltTree(input_2010,true,"hltana/HltTree");      // Load HltTree


  TTree         *muon_tree_2010;                             // Hold HLTMuTree
  TTree         *open_tree_2010;                             // Hold HltTree
  MUTREE        *muTree_2010 = new MUTREE;

  // 2011 datafile
	cout << "Opening 2011 input file..." << endl;
  TCastorFile   *input_2011 = new TCastorFile(data2011.c_str());
	cout << "2011 input file opened" << endl;
  FriendMuTree  *mutree_2011 = new FriendMuTree(input_2011,true); // Load HLTMuTree
  HltTree       *ohTree_2011 = new HltTree(input_2011,true,"hltanalysis/HltTree");      // Load HltTree
//  HltTree       *ohTree_2011 = new HltTree(input_2011,true,"hltana/HltTree");      // Load HltTree

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

  int nevt_2010=0;             			     // # of events that has at least 1 muon trigger fired
  int nevt_2010_qual=0;                  // # of events that has at least 1 muon trigger fired
  // Loop over trees over 2010 trees
	int max_event_2010 = muon_tree_2010->GetEntries();
	int max_event_2011 = muon_tree_2011->GetEntries();
//	int max_event_2010 = 1000;
//	int max_event_2011 = 10000;

  for (int i=0; i<max_event_2010; i++) {
    muon_tree_2010->GetEntry(i);
    ohTree_2010->GetEntry(i);
    open_tree_2010->GetEntry(i);

    ////////// Check muon trigger list
    nevt_2010++;
    bool qual=false;
    ////////// Load muons and fill up histograms
    for (int a=0; a < muTree_2010->nptl; a++) {

      flag->trig = false;
			for (unsigned int tidx=0; tidx<ntrig; tidx++) {
				if (trig_2010[tidx]) {         // At least one of the muon trigger is fired.
					flag->trig = true;
				break;
				}
			}
			
	  if (!flag->trig) continue;  // If no muon triggers fired, go to the next event!    

/*		if (ohTree_2010->L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND_instance1 ||
			ohTree_2010->L1_NotBsc2_BscMinBiasOR ||
			ohTree_2010->L1_NotBsc2_HcalHfMmOrPpOrPm) {  // Check MB gating
			cout << "MB gating passed" << endl;
		} else { 
			continue;
		}
		*/
		
		if (flag->doGlb) {
//      if(!isMuInAcc(flag, muTree_2010->eta[a], muTree_2010->pt[a])) continue;    //Check glb muons are within acceptance range
//      if(!isValidMu(flag, muTree_2010, a)) continue;    //Check glb muons are within acceptance range
//				if (muTree_2010->pt[a] >= 3) continue;
			} else if (flag->doSta) {
        if(!isMuInAcc(flag, muTree_2010->eta[a], muTree_2010->pt[a])) continue;    //Check sta muons are within acceptance range
      }
			
//		if (muTree_2010->pt[a] < 5) continue;
		if (abs(muTree_2010->eta[a]) > 0.9) continue;
		qual = true;
			
      SingleGlb_Etapt_2010->Fill(muTree_2010->eta[a],muTree_2010->pt[a]);
      SingleGlb_Etaphi_2010->Fill(muTree_2010->eta[a],muTree_2010->phi[a]);
      SingleGlb_Eta_2010->Fill(muTree_2010->eta[a]);
      SingleGlb_Pt_2010->Fill(muTree_2010->pt[a]);
      SingleGlb_Phi_2010->Fill(muTree_2010->phi[a]);

			SingleGlb_nValMuHits_eta_2010->Fill(muTree_2010->nValMuHits[a],muTree_2010->eta[a]);
			SingleGlb_nValTrkHits_eta_2010->Fill(muTree_2010->nValTrkHits[a],muTree_2010->eta[a]);
			SingleGlb_glbChi2_ndof_eta_2010->Fill(muTree_2010->glbChi2_ndof[a],muTree_2010->eta[a]);
			SingleGlb_trkChi2_ndof_eta_2010->Fill(muTree_2010->trkChi2_ndof[a],muTree_2010->eta[a]);
			SingleGlb_pixLayerWMeas_eta_2010->Fill(muTree_2010->pixLayerWMeas[a],muTree_2010->eta[a]);
			SingleGlb_trkDz_eta_2010->Fill(muTree_2010->trkDz[a],muTree_2010->eta[a]);
			SingleGlb_trkDxy_eta_2010->Fill(muTree_2010->trkDxy[a],muTree_2010->eta[a]);

			SingleGlb_nValMuHits_pt_2010->Fill(muTree_2010->nValMuHits[a],muTree_2010->pt[a]);
			SingleGlb_nValTrkHits_pt_2010->Fill(muTree_2010->nValTrkHits[a],muTree_2010->pt[a]);
			SingleGlb_glbChi2_ndof_pt_2010->Fill(muTree_2010->glbChi2_ndof[a],muTree_2010->pt[a]);
			SingleGlb_trkChi2_ndof_pt_2010->Fill(muTree_2010->trkChi2_ndof[a],muTree_2010->pt[a]);
			SingleGlb_pixLayerWMeas_pt_2010->Fill(muTree_2010->pixLayerWMeas[a],muTree_2010->pt[a]);
			SingleGlb_trkDz_pt_2010->Fill(muTree_2010->trkDz[a],muTree_2010->pt[a]);
			SingleGlb_trkDxy_pt_2010->Fill(muTree_2010->trkDxy[a],muTree_2010->pt[a]);

			SingleGlb_nValMuHits_phi_2010->Fill(muTree_2010->nValMuHits[a],muTree_2010->phi[a]);
			SingleGlb_nValTrkHits_phi_2010->Fill(muTree_2010->nValTrkHits[a],muTree_2010->phi[a]);
			SingleGlb_glbChi2_ndof_phi_2010->Fill(muTree_2010->glbChi2_ndof[a],muTree_2010->phi[a]);
			SingleGlb_trkChi2_ndof_phi_2010->Fill(muTree_2010->trkChi2_ndof[a],muTree_2010->phi[a]);
			SingleGlb_pixLayerWMeas_phi_2010->Fill(muTree_2010->pixLayerWMeas[a],muTree_2010->phi[a]);
			SingleGlb_trkDz_phi_2010->Fill(muTree_2010->trkDz[a],muTree_2010->phi[a]);
			SingleGlb_trkDxy_phi_2010->Fill(muTree_2010->trkDxy[a],muTree_2010->phi[a]);
			
			SingleGlb_nValMuHits_2010->Fill(muTree_2010->nValMuHits[a]);
			SingleGlb_nValTrkHits_2010->Fill(muTree_2010->nValTrkHits[a]);
			SingleGlb_glbChi2_ndof_2010->Fill(muTree_2010->glbChi2_ndof[a]);
			SingleGlb_trkChi2_ndof_2010->Fill(muTree_2010->trkChi2_ndof[a]);
			SingleGlb_pixLayerWMeas_2010->Fill(muTree_2010->pixLayerWMeas[a]);
			SingleGlb_trkDz_2010->Fill(muTree_2010->trkDz[a]);
			SingleGlb_trkDxy_2010->Fill(muTree_2010->trkDxy[a]);
			
      if(isValidMu(flag, muTree_2010, a,"")) SingleGlb_Etapt_2010_qual->Fill(muTree_2010->eta[a],muTree_2010->pt[a]);
      if(isValidMu(flag, muTree_2010, a,"")) SingleGlb_Etaphi_2010_qual->Fill(muTree_2010->eta[a],muTree_2010->phi[a]);
      if(isValidMu(flag, muTree_2010, a,"")) SingleGlb_Eta_2010_qual->Fill(muTree_2010->eta[a]);
      if(isValidMu(flag, muTree_2010, a,"")) SingleGlb_Pt_2010_qual->Fill(muTree_2010->pt[a]);
      if(isValidMu(flag, muTree_2010, a,"")) SingleGlb_Phi_2010_qual->Fill(muTree_2010->phi[a]);

			if(isValidMu(flag, muTree_2010, a,"nValMuHits")) SingleGlb_nValMuHits_pt_2010_qual->Fill(muTree_2010->nValMuHits[a],muTree_2010->pt[a]);
			if(isValidMu(flag, muTree_2010, a,"nValTrkHits")) SingleGlb_nValTrkHits_pt_2010_qual->Fill(muTree_2010->nValTrkHits[a],muTree_2010->pt[a]);
			if(isValidMu(flag, muTree_2010, a,"glbChi2_ndof")) SingleGlb_glbChi2_ndof_pt_2010_qual->Fill(muTree_2010->glbChi2_ndof[a],muTree_2010->pt[a]);
			if(isValidMu(flag, muTree_2010, a,"trkChi2_ndof")) SingleGlb_trkChi2_ndof_pt_2010_qual->Fill(muTree_2010->trkChi2_ndof[a],muTree_2010->pt[a]);
			if(isValidMu(flag, muTree_2010, a,"pixLayerWMeas")) SingleGlb_pixLayerWMeas_pt_2010_qual->Fill(muTree_2010->pixLayerWMeas[a],muTree_2010->pt[a]);
			if(isValidMu(flag, muTree_2010, a,"trkDz")) SingleGlb_trkDz_pt_2010_qual->Fill(muTree_2010->trkDz[a],muTree_2010->pt[a]);
			if(isValidMu(flag, muTree_2010, a,"trkDxy")) SingleGlb_trkDxy_pt_2010_qual->Fill(muTree_2010->trkDxy[a],muTree_2010->pt[a]);

			if(isValidMu(flag, muTree_2010, a,"nValMuHits")) SingleGlb_nValMuHits_eta_2010_qual->Fill(muTree_2010->nValMuHits[a],muTree_2010->eta[a]);
			if(isValidMu(flag, muTree_2010, a,"nValTrkHits")) SingleGlb_nValTrkHits_eta_2010_qual->Fill(muTree_2010->nValTrkHits[a],muTree_2010->eta[a]);
			if(isValidMu(flag, muTree_2010, a,"glbChi2_ndof")) SingleGlb_glbChi2_ndof_eta_2010_qual->Fill(muTree_2010->glbChi2_ndof[a],muTree_2010->eta[a]);
			if(isValidMu(flag, muTree_2010, a,"trkChi2_ndof")) SingleGlb_trkChi2_ndof_eta_2010_qual->Fill(muTree_2010->trkChi2_ndof[a],muTree_2010->eta[a]);
			if(isValidMu(flag, muTree_2010, a,"pixLayerWMeas")) SingleGlb_pixLayerWMeas_eta_2010_qual->Fill(muTree_2010->pixLayerWMeas[a],muTree_2010->eta[a]);
			if(isValidMu(flag, muTree_2010, a,"trkDz")) SingleGlb_trkDz_eta_2010_qual->Fill(muTree_2010->trkDz[a],muTree_2010->eta[a]);
			if(isValidMu(flag, muTree_2010, a,"trkDxy")) SingleGlb_trkDxy_eta_2010_qual->Fill(muTree_2010->trkDxy[a],muTree_2010->eta[a]);

			if(isValidMu(flag, muTree_2010, a,"nValMuHits")) SingleGlb_nValMuHits_phi_2010_qual->Fill(muTree_2010->nValMuHits[a],muTree_2010->phi[a]);
			if(isValidMu(flag, muTree_2010, a,"nValTrkHits")) SingleGlb_nValTrkHits_phi_2010_qual->Fill(muTree_2010->nValTrkHits[a],muTree_2010->phi[a]);
			if(isValidMu(flag, muTree_2010, a,"glbChi2_ndof")) SingleGlb_glbChi2_ndof_phi_2010_qual->Fill(muTree_2010->glbChi2_ndof[a],muTree_2010->phi[a]);
			if(isValidMu(flag, muTree_2010, a,"trkChi2_ndof")) SingleGlb_trkChi2_ndof_phi_2010_qual->Fill(muTree_2010->trkChi2_ndof[a],muTree_2010->phi[a]);
			if(isValidMu(flag, muTree_2010, a,"pixLayerWMeas")) SingleGlb_pixLayerWMeas_phi_2010_qual->Fill(muTree_2010->pixLayerWMeas[a],muTree_2010->phi[a]);
			if(isValidMu(flag, muTree_2010, a,"trkDz")) SingleGlb_trkDz_phi_2010_qual->Fill(muTree_2010->trkDz[a],muTree_2010->phi[a]);
			if(isValidMu(flag, muTree_2010, a,"trkDxy")) SingleGlb_trkDxy_phi_2010_qual->Fill(muTree_2010->trkDxy[a],muTree_2010->phi[a]);
			
			if(isValidMu(flag, muTree_2010, a,"nValMuHits")) SingleGlb_nValMuHits_2010_qual->Fill(muTree_2010->nValMuHits[a]);
			if(isValidMu(flag, muTree_2010, a,"nValTrkHits")) SingleGlb_nValTrkHits_2010_qual->Fill(muTree_2010->nValTrkHits[a]);
			if(isValidMu(flag, muTree_2010, a,"glbChi2_ndof")) SingleGlb_glbChi2_ndof_2010_qual->Fill(muTree_2010->glbChi2_ndof[a]);
			if(isValidMu(flag, muTree_2010, a,"trkChi2_ndof")) SingleGlb_trkChi2_ndof_2010_qual->Fill(muTree_2010->trkChi2_ndof[a]);
			if(isValidMu(flag, muTree_2010, a,"pixLayerWMeas")) SingleGlb_pixLayerWMeas_2010_qual->Fill(muTree_2010->pixLayerWMeas[a]);
			if(isValidMu(flag, muTree_2010, a,"trkDz")) SingleGlb_trkDz_2010_qual->Fill(muTree_2010->trkDz[a]);
			if(isValidMu(flag, muTree_2010, a,"trkDxy")) SingleGlb_trkDxy_2010_qual->Fill(muTree_2010->trkDxy[a]);
			
    }
    if (qual) nevt_2010_qual++;


    if (i%1000 ==0)
    cout << "Event in 2010 datasets: " << i+1 << endl;
  }

  int nevt_2011=0;                  // # of events that has at least 1 muon trigger fired
  int nevt_2011_qual=0;                  // # of events that has at least 1 muon trigger fired
  // Loop over trees over 2011 trees
  for (int i=0; i<max_event_2011; i++) {
    muon_tree_2011->GetEntry(i);
    ohTree_2011->GetEntry(i);
    open_tree_2011->GetEntry(i);


    nevt_2011++;
    bool qual=false;
    ////////// Load muons and fill up histograms
    for (int a=0; a < muTree_2011->nptl; a++) {
			////////// Check muon trigger list
			flag->trig = false;
			for (unsigned int tidx=0; tidx<ntrig; tidx++) {
				if (trig_2011[tidx]) {         // At least one of the muon trigger is fired.
				flag->trig = true;
				break;
				}
			}

			if (!flag->trig) continue;  // If no muon triggers fired, go to the next event!			
			
      if (flag->doGlb) {
//      if(!isMuInAcc(flag, muTree_2010->eta[a], muTree_2010->pt[a])) continue;    //Check glb muons are within acceptance range
//      if(!isValidMu(flag, muTree_2010, a)) continue;    //Check glb muons are within acceptance range
//				if (muTree_2011->pt[a] >= 3) continue;
      } else if (flag->doSta) {
        if(!isMuInAcc(flag, muTree_2011->eta[a], muTree_2011->pt[a])) continue;    //Check sta muons are within acceptance range
      }
			
//			if (muTree_2011->pt[a] < 5) continue;
			if (abs(muTree_2011->eta[a]) > 0.9) continue;

      qual = true;
				
				SingleGlb_Etapt_2011->Fill(muTree_2011->eta[a],muTree_2011->pt[a]);
				SingleGlb_Etaphi_2011->Fill(muTree_2011->eta[a],muTree_2011->phi[a]);
				SingleGlb_Eta_2011->Fill(muTree_2011->eta[a]);
				SingleGlb_Pt_2011->Fill(muTree_2011->pt[a]);
				SingleGlb_Phi_2011->Fill(muTree_2011->phi[a]);

				SingleGlb_nValMuHits_eta_2011->Fill(muTree_2011->nValMuHits[a],muTree_2011->eta[a]);
				SingleGlb_nValTrkHits_eta_2011->Fill(muTree_2011->nValTrkHits[a],muTree_2011->eta[a]);
				SingleGlb_glbChi2_ndof_eta_2011->Fill(muTree_2011->glbChi2_ndof[a],muTree_2011->eta[a]);
				SingleGlb_trkChi2_ndof_eta_2011->Fill(muTree_2011->trkChi2_ndof[a],muTree_2011->eta[a]);
				SingleGlb_pixLayerWMeas_eta_2011->Fill(muTree_2011->pixLayerWMeas[a],muTree_2011->eta[a]);
				SingleGlb_trkDz_eta_2011->Fill(muTree_2011->trkDz[a],muTree_2011->eta[a]);
				SingleGlb_trkDxy_eta_2011->Fill(muTree_2011->trkDxy[a],muTree_2011->eta[a]);

				SingleGlb_nValMuHits_pt_2011->Fill(muTree_2011->nValMuHits[a],muTree_2011->pt[a]);
				SingleGlb_nValTrkHits_pt_2011->Fill(muTree_2011->nValTrkHits[a],muTree_2011->pt[a]);
				SingleGlb_glbChi2_ndof_pt_2011->Fill(muTree_2011->glbChi2_ndof[a],muTree_2011->pt[a]);
				SingleGlb_trkChi2_ndof_pt_2011->Fill(muTree_2011->trkChi2_ndof[a],muTree_2011->pt[a]);
				SingleGlb_pixLayerWMeas_pt_2011->Fill(muTree_2011->pixLayerWMeas[a],muTree_2011->pt[a]);
				SingleGlb_trkDz_pt_2011->Fill(muTree_2011->trkDz[a],muTree_2011->pt[a]);
				SingleGlb_trkDxy_pt_2011->Fill(muTree_2011->trkDxy[a],muTree_2011->pt[a]);

				SingleGlb_nValMuHits_phi_2011->Fill(muTree_2011->nValMuHits[a],muTree_2011->phi[a]);
				SingleGlb_nValTrkHits_phi_2011->Fill(muTree_2011->nValTrkHits[a],muTree_2011->phi[a]);
				SingleGlb_glbChi2_ndof_phi_2011->Fill(muTree_2011->glbChi2_ndof[a],muTree_2011->phi[a]);
				SingleGlb_trkChi2_ndof_phi_2011->Fill(muTree_2011->trkChi2_ndof[a],muTree_2011->phi[a]);
				SingleGlb_pixLayerWMeas_phi_2011->Fill(muTree_2011->pixLayerWMeas[a],muTree_2011->phi[a]);
				SingleGlb_trkDz_phi_2011->Fill(muTree_2011->trkDz[a],muTree_2011->phi[a]);
				SingleGlb_trkDxy_phi_2011->Fill(muTree_2011->trkDxy[a],muTree_2011->phi[a]);
				
				SingleGlb_nValMuHits_2011->Fill(muTree_2011->nValMuHits[a]);
				SingleGlb_nValTrkHits_2011->Fill(muTree_2011->nValTrkHits[a]);
				SingleGlb_glbChi2_ndof_2011->Fill(muTree_2011->glbChi2_ndof[a]);
				SingleGlb_trkChi2_ndof_2011->Fill(muTree_2011->trkChi2_ndof[a]);
				SingleGlb_pixLayerWMeas_2011->Fill(muTree_2011->pixLayerWMeas[a]);
				SingleGlb_trkDz_2011->Fill(muTree_2011->trkDz[a]);
				SingleGlb_trkDxy_2011->Fill(muTree_2011->trkDxy[a]);
      
/*		if (ohTree_2011->L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND_instance1 ||
			ohTree_2011->L1_NotBsc2_BscMinBiasOR ||
			ohTree_2011->L1_NotBsc2_HcalHfMmOrPpOrPm) {  // Check MB gating
//			cout << "MB gating passed" << endl;
		} else { 
			continue;
		}
*/
				if(isValidMu(flag, muTree_2011, a,"")) SingleGlb_Etapt_2011_qual->Fill(muTree_2011->eta[a],muTree_2011->pt[a]);
				if(isValidMu(flag, muTree_2011, a,"")) SingleGlb_Etaphi_2011_qual->Fill(muTree_2011->eta[a],muTree_2011->phi[a]);
				if(isValidMu(flag, muTree_2011, a,"")) SingleGlb_Eta_2011_qual->Fill(muTree_2011->eta[a]);
				if(isValidMu(flag, muTree_2011, a,"")) SingleGlb_Pt_2011_qual->Fill(muTree_2011->pt[a]);
				if(isValidMu(flag, muTree_2011, a,"")) SingleGlb_Phi_2011_qual->Fill(muTree_2011->phi[a]);

				if(isValidMu(flag, muTree_2011, a,"nValMuHits")) SingleGlb_nValMuHits_pt_2011_qual->Fill(muTree_2011->nValMuHits[a],muTree_2011->pt[a]);
				if(isValidMu(flag, muTree_2011, a,"nValTrkHits")) SingleGlb_nValTrkHits_pt_2011_qual->Fill(muTree_2011->nValTrkHits[a],muTree_2011->pt[a]);
				if(isValidMu(flag, muTree_2011, a,"glbChi2_ndof")) SingleGlb_glbChi2_ndof_pt_2011_qual->Fill(muTree_2011->glbChi2_ndof[a],muTree_2011->pt[a]);
				if(isValidMu(flag, muTree_2011, a,"trkChi2_ndof")) SingleGlb_trkChi2_ndof_pt_2011_qual->Fill(muTree_2011->trkChi2_ndof[a],muTree_2011->pt[a]);
				if(isValidMu(flag, muTree_2011, a,"pixLayerWMeas")) SingleGlb_pixLayerWMeas_pt_2011_qual->Fill(muTree_2011->pixLayerWMeas[a],muTree_2011->pt[a]);
				if(isValidMu(flag, muTree_2011, a,"trkDz")) SingleGlb_trkDz_pt_2011_qual->Fill(muTree_2011->trkDz[a],muTree_2011->pt[a]);
				if(isValidMu(flag, muTree_2011, a,"trkDxy")) SingleGlb_trkDxy_pt_2011_qual->Fill(muTree_2011->trkDxy[a],muTree_2011->pt[a]);
				
				if(isValidMu(flag, muTree_2011, a,"nValMuHits")) SingleGlb_nValMuHits_eta_2011_qual->Fill(muTree_2011->nValMuHits[a],muTree_2011->eta[a]);
				if(isValidMu(flag, muTree_2011, a,"nValTrkHits")) SingleGlb_nValTrkHits_eta_2011_qual->Fill(muTree_2011->nValTrkHits[a],muTree_2011->eta[a]);
				if(isValidMu(flag, muTree_2011, a,"glbChi2_ndof")) SingleGlb_glbChi2_ndof_eta_2011_qual->Fill(muTree_2011->glbChi2_ndof[a],muTree_2011->eta[a]);
				if(isValidMu(flag, muTree_2011, a,"trkChi2_ndof")) SingleGlb_trkChi2_ndof_eta_2011_qual->Fill(muTree_2011->trkChi2_ndof[a],muTree_2011->eta[a]);
				if(isValidMu(flag, muTree_2011, a,"pixLayerWMeas")) SingleGlb_pixLayerWMeas_eta_2011_qual->Fill(muTree_2011->pixLayerWMeas[a],muTree_2011->eta[a]);
				if(isValidMu(flag, muTree_2011, a,"trkDz")) SingleGlb_trkDz_eta_2011_qual->Fill(muTree_2011->trkDz[a],muTree_2011->eta[a]);
				if(isValidMu(flag, muTree_2011, a,"trkDxy")) SingleGlb_trkDxy_eta_2011_qual->Fill(muTree_2011->trkDxy[a],muTree_2011->eta[a]);

				if(isValidMu(flag, muTree_2011, a,"nValMuHits")) SingleGlb_nValMuHits_phi_2011_qual->Fill(muTree_2011->nValMuHits[a],muTree_2011->phi[a]);
				if(isValidMu(flag, muTree_2011, a,"nValTrkHits")) SingleGlb_nValTrkHits_phi_2011_qual->Fill(muTree_2011->nValTrkHits[a],muTree_2011->phi[a]);
				if(isValidMu(flag, muTree_2011, a,"glbChi2_ndof")) SingleGlb_glbChi2_ndof_phi_2011_qual->Fill(muTree_2011->glbChi2_ndof[a],muTree_2011->phi[a]);
				if(isValidMu(flag, muTree_2011, a,"trkChi2_ndof")) SingleGlb_trkChi2_ndof_phi_2011_qual->Fill(muTree_2011->trkChi2_ndof[a],muTree_2011->phi[a]);
				if(isValidMu(flag, muTree_2011, a,"pixLayerWMeas")) SingleGlb_pixLayerWMeas_phi_2011_qual->Fill(muTree_2011->pixLayerWMeas[a],muTree_2011->phi[a]);
				if(isValidMu(flag, muTree_2011, a,"trkDz")) SingleGlb_trkDz_phi_2011_qual->Fill(muTree_2011->trkDz[a],muTree_2011->phi[a]);
				if(isValidMu(flag, muTree_2011, a,"trkDxy")) SingleGlb_trkDxy_phi_2011_qual->Fill(muTree_2011->trkDxy[a],muTree_2011->phi[a]);
				
				if(isValidMu(flag, muTree_2011, a,"nValMuHits")) SingleGlb_nValMuHits_2011_qual->Fill(muTree_2011->nValMuHits[a]);
				if(isValidMu(flag, muTree_2011, a,"nValTrkHits")) SingleGlb_nValTrkHits_2011_qual->Fill(muTree_2011->nValTrkHits[a]);
				if(isValidMu(flag, muTree_2011, a,"glbChi2_ndof")) SingleGlb_glbChi2_ndof_2011_qual->Fill(muTree_2011->glbChi2_ndof[a]);
				if(isValidMu(flag, muTree_2011, a,"trkChi2_ndof")) SingleGlb_trkChi2_ndof_2011_qual->Fill(muTree_2011->trkChi2_ndof[a]);
				if(isValidMu(flag, muTree_2011, a,"pixLayerWMeas")) SingleGlb_pixLayerWMeas_2011_qual->Fill(muTree_2011->pixLayerWMeas[a]);
				if(isValidMu(flag, muTree_2011, a,"trkDz")) SingleGlb_trkDz_2011_qual->Fill(muTree_2011->trkDz[a]);
				if(isValidMu(flag, muTree_2011, a,"trkDxy")) SingleGlb_trkDxy_2011_qual->Fill(muTree_2011->trkDxy[a]);
    }
    if (qual) nevt_2011_qual++;

    if (i%1000 ==0)
    cout << "Event in 2011 datasets: " << i+1 << endl;

  }

	double numerator_2010 = SingleGlb_Eta_2010->GetEntries();
	double numerator_2010_qual = SingleGlb_Eta_2010_qual->GetEntries();
	double numerator_2011 = SingleGlb_Eta_2011->GetEntries();
	double numerator_2011_qual = SingleGlb_Eta_2011_qual->GetEntries();
  
  // Draw final histograms and save it into .png files
  gROOT->Macro("~miheejo/public/HIMuTrig/TrigStyle.C");    //For plot style
  TCanvas *canv = new TCanvas("canv","canv",800,600);

  TLegend *leg = new TLegend(0.15,0.90,0.2,1.0);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.05);

	double marker_size = 2.0;
	double label_size = 0.05;
	
  TLatex *lax = new TLatex();
  lax->SetTextSize(0.1);
	stringstream title;
	
	TPad *pad1;
	TPad *pad2;

	TH1F *ratio_2011;
	TH1F *ratio_2011_qual;

	char count_2010[512];
	char count_2011[512];

	int entries_2010;
	int entries_2011;

	char count_2010_qual[512];
	char count_2011_qual[512];

	int entries_2010_qual;
	int entries_2011_qual;
	
	TLine* l3a;
	
	gStyle->SetPalette(1,0);
	gStyle->SetPadLeftMargin(0.07);
	gStyle->SetPadBottomMargin(0.2);
	gStyle->SetPadTopMargin(0.1);
	gStyle->SetPadRightMargin(0.02);
	gStyle->SetOptTitle(1);
	gStyle->SetTextSize(0.03);
	gStyle->SetMarkerSize(1);

	gStyle->SetOptTitle(0);
	gStyle->SetStatX(0.8);
	gStyle->SetStatY(1.0);
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.2);
	gStyle->SetOptStat("mn");

	// START Eta	
	canv = new TCanvas("canv","canv",1300,1000);
	
	pad1 = new TPad("pad1", "The pad 70% of the height",0.0,0.3,1.0,1.0,0);
	pad1->SetTopMargin(0.1);
	pad1->SetBottomMargin(0.0);
	pad2 = new TPad("pad2", "The pad 30% of the height",0.0,0.0,1.0,0.3,0);
	pad2->SetTopMargin(0.0);
	pad2->SetBottomMargin(0.35);



	pad1->Draw();
	pad2->Draw();

	pad1->cd();
	pad1->SetLogy(0);

	gStyle->SetMarkerSize(1);
	SingleGlb_Eta_2010->GetXaxis()->SetLabelSize(label_size);
	SingleGlb_Eta_2010->GetYaxis()->SetLabelSize(label_size);
	SingleGlb_Eta_2010->SetMinimum(0);
	SingleGlb_Eta_2010->Sumw2();
  SingleGlb_Eta_2010->SetMarkerStyle(25);
  SingleGlb_Eta_2010->SetMarkerSize(marker_size);
	SingleGlb_Eta_2010->Scale(1.0/SingleGlb_Eta_2010->GetEntries());
  SingleGlb_Eta_2010->DrawNormalized("p e",1);
	gStyle->SetStatX(0.8);
	gStyle->SetStatY(1.0);
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.2);
	gStyle->SetOptStat("mn");
	entries_2010 = SingleGlb_Eta_2010->GetEntries();
	canv->Update();
  SingleGlb_Eta_2011->Sumw2();
  SingleGlb_Eta_2011->SetMarkerColor(kRed);
  SingleGlb_Eta_2011->SetMarkerStyle(20);
  SingleGlb_Eta_2011->SetMarkerSize(marker_size);
	SingleGlb_Eta_2011->Scale(1.0/SingleGlb_Eta_2011->GetEntries());
  SingleGlb_Eta_2011->DrawNormalized("p e sames",1);
	gStyle->SetStatX(1.0);
	entries_2010 = SingleGlb_Eta_2010->GetEntries();
	entries_2011 = SingleGlb_Eta_2011->GetEntries();
	sprintf(count_2010,"  2010 Data - %i Muons", entries_2010);
	sprintf(count_2011,"  2011 Data - %i Muons", entries_2011);
	leg->Clear();
	leg->AddEntry(SingleGlb_Eta_2010,count_2010,"lp");
	leg->AddEntry(SingleGlb_Eta_2011,count_2011,"lp");
  leg->Draw();
	canv->Update();

	pad2->cd();

	ratio_2011 = (TH1F*)SingleGlb_Eta_2011->Clone("ratio_2011");
	ratio_2011->Divide(SingleGlb_Eta_2010);
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
	
	canv->SaveAs("SingleGlb_Eta.pdf");
	canv->Clear(); canv->Draw();
// END Eta	

	// START Pt	
	canv = new TCanvas("canv","canv",1300,1000);
	
	pad1 = new TPad("pad1", "The pad 70% of the height",0.0,0.3,1.0,1.0,0);
	pad1->SetBottomMargin(0.0);
	pad2 = new TPad("pad2", "The pad 30% of the height",0.0,0.0,1.0,0.3,0);
	pad2->SetTopMargin(0.0);
	pad2->SetBottomMargin(0.35);

	pad1->Draw();
	pad2->Draw();

	pad1->cd();
	pad1->SetLogy(1);

	gStyle->SetMarkerSize(1);
	SingleGlb_Pt_2010->GetXaxis()->SetLabelSize(label_size);
	SingleGlb_Pt_2010->GetYaxis()->SetLabelSize(label_size);
	SingleGlb_Pt_2010->SetMinimum(1);
	SingleGlb_Pt_2010->Sumw2();
  SingleGlb_Pt_2010->SetMarkerStyle(25);
  SingleGlb_Pt_2010->SetMarkerSize(marker_size);
	SingleGlb_Pt_2010->Scale(1.0/SingleGlb_Pt_2010->GetEntries());
  SingleGlb_Pt_2010->DrawNormalized("p e",1);
	gStyle->SetStatX(0.8);
	gStyle->SetStatY(1.0);
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.2);
	gStyle->SetOptStat("mn");
	entries_2010 = SingleGlb_Pt_2010->GetEntries();
	canv->Update();
  SingleGlb_Pt_2011->Sumw2();
  SingleGlb_Pt_2011->SetMarkerColor(kRed);
  SingleGlb_Pt_2011->SetMarkerStyle(20);
  SingleGlb_Pt_2011->SetMarkerSize(marker_size);
	SingleGlb_Pt_2011->Scale(1.0/SingleGlb_Pt_2011->GetEntries());
  SingleGlb_Pt_2011->DrawNormalized("p e sames",1);
	gStyle->SetStatX(1.0);
	entries_2010 = SingleGlb_Pt_2010->GetEntries();
	entries_2011 = SingleGlb_Pt_2011->GetEntries();
	sprintf(count_2010,"  2010 Data - %i Muons", entries_2010);
	sprintf(count_2011,"  2011 Data - %i Muons", entries_2011);
	leg->Clear();
	leg->AddEntry(SingleGlb_Pt_2010,count_2010,"lp");
	leg->AddEntry(SingleGlb_Pt_2011,count_2011,"lp");
  leg->Draw();
	canv->Update();

	pad2->cd();

	ratio_2011 = (TH1F*)SingleGlb_Pt_2011->Clone("ratio_2011");
	ratio_2011->Divide(SingleGlb_Pt_2010);
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
	ratio_2011->GetYaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011->GetYaxis()->SetNdivisions(505);

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
	
	canv->SaveAs("SingleGlb_Pt.pdf");
	canv->Clear(); canv->Draw();
// END Pt	

	// START Phi	
	canv = new TCanvas("canv","canv",1300,1000);
	
	pad1 = new TPad("pad1", "The pad 70% of the height",0.0,0.3,1.0,1.0,0);
	pad1->SetBottomMargin(0.0);
	pad2 = new TPad("pad2", "The pad 30% of the height",0.0,0.0,1.0,0.3,0);
	pad2->SetTopMargin(0.0);
	pad2->SetBottomMargin(0.35);


	pad1->Draw();
	pad2->Draw();

	pad1->cd();
	pad1->SetLogy(0);

	gStyle->SetMarkerSize(1);
	SingleGlb_Phi_2010->GetXaxis()->SetLabelSize(label_size);
	SingleGlb_Phi_2010->GetYaxis()->SetLabelSize(label_size);
	SingleGlb_Phi_2010->SetMinimum(0);
	SingleGlb_Phi_2010->Sumw2();
  SingleGlb_Phi_2010->SetMarkerStyle(25);
  SingleGlb_Phi_2010->SetMarkerSize(marker_size);
	SingleGlb_Phi_2010->Scale(1.0/SingleGlb_Phi_2010->GetEntries());
  SingleGlb_Phi_2010->DrawNormalized("p e",1);
	gStyle->SetStatX(0.8);
	gStyle->SetStatY(1.0);
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.2);
	gStyle->SetOptStat("mn");
	entries_2010 = SingleGlb_Phi_2010->GetEntries();
	canv->Update();
  SingleGlb_Phi_2011->Sumw2();
  SingleGlb_Phi_2011->SetMarkerColor(kRed);
  SingleGlb_Phi_2011->SetMarkerStyle(20);
  SingleGlb_Phi_2011->SetMarkerSize(marker_size);
	SingleGlb_Phi_2011->Scale(1.0/SingleGlb_Phi_2011->GetEntries());
  SingleGlb_Phi_2011->DrawNormalized("p e sames",1);
	gStyle->SetStatX(1.0);
	entries_2010 = SingleGlb_Phi_2010->GetEntries();
	entries_2011 = SingleGlb_Phi_2011->GetEntries();
	sprintf(count_2010,"  2010 Data - %i Muons", entries_2010);
	sprintf(count_2011,"  2011 Data - %i Muons", entries_2011);
	leg->Clear();
	leg->AddEntry(SingleGlb_Phi_2010,count_2010,"lp");
	leg->AddEntry(SingleGlb_Phi_2011,count_2011,"lp");
  leg->Draw();
	canv->Update();

	pad2->cd();

	ratio_2011 = (TH1F*)SingleGlb_Phi_2011->Clone("ratio_2011");
	ratio_2011->Divide(SingleGlb_Phi_2010);
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
	ratio_2011->GetYaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011->GetYaxis()->SetNdivisions(505);

	ratio_2011->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
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
	
	canv->SaveAs("SingleGlb_Phi.pdf");
	canv->Clear(); canv->Draw();
// END Phi	
	
	// START nValMuHits	
	canv = new TCanvas("canv","canv",1300,1000);
	
	pad1 = new TPad("pad1", "The pad 70% of the height",0.0,0.3,1.0,1.0,0);
	pad1->SetBottomMargin(0.0);
	pad2 = new TPad("pad2", "The pad 30% of the height",0.0,0.0,1.0,0.3,0);
	pad2->SetTopMargin(0.0);
	pad2->SetBottomMargin(0.35);



	pad1->Draw();
	pad2->Draw();

	pad1->cd();
	pad1->SetLogy(0);

	gStyle->SetMarkerSize(1);
	SingleGlb_nValMuHits_2010->GetXaxis()->SetLabelSize(label_size);
	SingleGlb_nValMuHits_2010->GetYaxis()->SetLabelSize(label_size);
	SingleGlb_nValMuHits_2010->SetMinimum(0);
	SingleGlb_nValMuHits_2010->Sumw2();
  SingleGlb_nValMuHits_2010->SetMarkerStyle(25);
  SingleGlb_nValMuHits_2010->SetMarkerSize(marker_size);
	SingleGlb_nValMuHits_2010->Scale(1.0/SingleGlb_nValMuHits_2010->GetEntries());
  SingleGlb_nValMuHits_2010->DrawNormalized("p e",1);
	gStyle->SetStatX(0.8);
	gStyle->SetStatY(1.0);
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.2);
	gStyle->SetOptStat("mn");
	entries_2010 = SingleGlb_nValMuHits_2010->GetEntries();
	canv->Update();
  SingleGlb_nValMuHits_2011->Sumw2();
  SingleGlb_nValMuHits_2011->SetMarkerColor(kRed);
  SingleGlb_nValMuHits_2011->SetMarkerStyle(20);
  SingleGlb_nValMuHits_2011->SetMarkerSize(marker_size);
	SingleGlb_nValMuHits_2011->Scale(1.0/SingleGlb_nValMuHits_2011->GetEntries());
  SingleGlb_nValMuHits_2011->DrawNormalized("p e sames",1);
	gStyle->SetStatX(1.0);
	entries_2010 = SingleGlb_nValMuHits_2010->GetEntries();
	entries_2011 = SingleGlb_nValMuHits_2011->GetEntries();
	sprintf(count_2010,"  2010 Data - %i Muons", entries_2010);
	sprintf(count_2011,"  2011 Data - %i Muons", entries_2011);
	leg->Clear();
	leg->AddEntry(SingleGlb_nValMuHits_2010,count_2010,"lp");
	leg->AddEntry(SingleGlb_nValMuHits_2011,count_2011,"lp");
  leg->Draw();
	canv->Update();

	pad2->cd();

	ratio_2011 = (TH1F*)SingleGlb_nValMuHits_2011->Clone("ratio_2011");
	ratio_2011->Divide(SingleGlb_nValMuHits_2010);
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
	ratio_2011->GetYaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011->GetYaxis()->SetNdivisions(505);

	ratio_2011->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011->GetXaxis()->SetTitleSize(0.15);
	ratio_2011->GetXaxis()->SetTitle("Number of Valid Muon Hits");
	
	gStyle->SetOptTitle(0);
	gPad->SetLogy(0);
	
	ratio_2011->Draw();

	l3a = new TLine(0,1.0,60,1.0);
	l3a->SetHorizontal(1);
	l3a->SetLineStyle(2);
	l3a->SetX2(60);
	l3a->Draw("same");
	
	canv->SaveAs("SingleGlb_nValMuHits.pdf");
	canv->Clear(); canv->Draw();
// END nValMuHits	
	
// START nValTrkHits	
	canv = new TCanvas("canv","canv",1300,1000);
	
	pad1 = new TPad("pad1", "The pad 70% of the height",0.0,0.3,1.0,1.0,0);
	pad1->SetBottomMargin(0.0);
	pad2 = new TPad("pad2", "The pad 30% of the height",0.0,0.0,1.0,0.3,0);
	pad2->SetTopMargin(0.0);
	pad2->SetBottomMargin(0.35);



	pad1->Draw();
	pad2->Draw();

	pad1->cd();
	pad1->SetLogy(0);

	gStyle->SetMarkerSize(1);
	SingleGlb_nValTrkHits_2010->GetXaxis()->SetLabelSize(label_size);
	SingleGlb_nValTrkHits_2010->GetYaxis()->SetLabelSize(label_size);
	SingleGlb_nValTrkHits_2010->SetMinimum(0);
	SingleGlb_nValTrkHits_2010->Sumw2();
  SingleGlb_nValTrkHits_2010->SetMarkerStyle(25);
  SingleGlb_nValTrkHits_2010->SetMarkerSize(marker_size);
	SingleGlb_nValTrkHits_2010->Scale(1.0/SingleGlb_nValTrkHits_2010->GetEntries());
  SingleGlb_nValTrkHits_2010->DrawNormalized("p e",1);
	canv->Update();
	gStyle->SetStatX(0.8);
	gStyle->SetStatY(1.0);
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.2);
	gStyle->SetOptStat("mn");
	entries_2010 = SingleGlb_nValTrkHits_2010->GetEntries();
	canv->Update();
  SingleGlb_nValTrkHits_2011->Sumw2();
  SingleGlb_nValTrkHits_2011->SetMarkerColor(kRed);
  SingleGlb_nValTrkHits_2011->SetMarkerStyle(20);
  SingleGlb_nValTrkHits_2011->SetMarkerSize(marker_size);
	SingleGlb_nValTrkHits_2011->Scale(1.0/SingleGlb_nValTrkHits_2011->GetEntries());
  SingleGlb_nValTrkHits_2011->DrawNormalized("p e sames",1);
	gStyle->SetStatX(1.0);
	entries_2010 = SingleGlb_nValTrkHits_2010->GetEntries();
	entries_2011 = SingleGlb_nValTrkHits_2011->GetEntries();
	sprintf(count_2010,"  2010 Data - %i Muons", entries_2010);
	sprintf(count_2011,"  2011 Data - %i Muons", entries_2011);
	leg->Clear();
	leg->AddEntry(SingleGlb_nValTrkHits_2010,count_2010,"lp");
	leg->AddEntry(SingleGlb_nValTrkHits_2011,count_2011,"lp");
  leg->Draw();
	canv->Update();

	pad2->cd();

	ratio_2011 = (TH1F*)SingleGlb_nValTrkHits_2011->Clone("ratio_2011");
	ratio_2011->Divide(SingleGlb_nValTrkHits_2010);
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
	ratio_2011->GetYaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011->GetYaxis()->SetNdivisions(505);

	ratio_2011->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011->GetXaxis()->SetTitleSize(0.15);
	ratio_2011->GetXaxis()->SetTitle("Number of Valid Tracker Hits");
	
	gStyle->SetOptTitle(0);
	gPad->SetLogy(0);
	
	ratio_2011->Draw();
	l3a = new TLine(0,1.0,30,1.0);
	l3a->SetHorizontal(1);
	l3a->SetLineStyle(2);
	l3a->SetX2(30);
	l3a->Draw("same");

	canv->SaveAs("SingleGlb_nValTrkHits.pdf");
	canv->Clear(); canv->Draw();
// END nValTrkHits	

// START glbChi2_ndof	
	canv = new TCanvas("canv","canv",1300,1000);
	
	pad1 = new TPad("pad1", "The pad 70% of the height",0.0,0.3,1.0,1.0,0);
	pad1->SetBottomMargin(0.0);
	pad2 = new TPad("pad2", "The pad 30% of the height",0.0,0.0,1.0,0.3,0);
	pad2->SetTopMargin(0.0);
	pad2->SetBottomMargin(0.35);



	pad1->Draw();
	pad2->Draw();

	pad1->cd();
	pad1->SetLogy(1);

	gStyle->SetMarkerSize(1);
	SingleGlb_glbChi2_ndof_2010->GetXaxis()->SetLabelSize(label_size);
	SingleGlb_glbChi2_ndof_2010->GetYaxis()->SetLabelSize(label_size);
	SingleGlb_glbChi2_ndof_2010->SetMinimum(1);
	SingleGlb_glbChi2_ndof_2010->Sumw2();
  SingleGlb_glbChi2_ndof_2010->SetMarkerStyle(25);
  SingleGlb_glbChi2_ndof_2010->SetMarkerSize(marker_size);
	SingleGlb_glbChi2_ndof_2010->Scale(1.0/SingleGlb_glbChi2_ndof_2010->GetEntries());
  SingleGlb_glbChi2_ndof_2010->DrawNormalized("p e",1);
	canv->Update();
	gStyle->SetStatX(0.8);
	gStyle->SetStatY(1.0);
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.2);
	gStyle->SetOptStat("mn");
	entries_2010 = SingleGlb_glbChi2_ndof_2010->GetEntries();
	canv->Update();
  SingleGlb_glbChi2_ndof_2011->Sumw2();
  SingleGlb_glbChi2_ndof_2011->SetMarkerColor(kRed);
  SingleGlb_glbChi2_ndof_2011->SetMarkerStyle(20);
  SingleGlb_glbChi2_ndof_2011->SetMarkerSize(marker_size);
	SingleGlb_glbChi2_ndof_2011->Scale(1.0/SingleGlb_glbChi2_ndof_2011->GetEntries());
  SingleGlb_glbChi2_ndof_2011->DrawNormalized("p e sames",1);
	gStyle->SetStatX(1.0);
	entries_2010 = SingleGlb_glbChi2_ndof_2010->GetEntries();
	entries_2011 = SingleGlb_glbChi2_ndof_2011->GetEntries();
	sprintf(count_2010,"  2010 Data - %i Muons", entries_2010);
	sprintf(count_2011,"  2011 Data - %i Muons", entries_2011);
	leg->Clear();
	leg->AddEntry(SingleGlb_glbChi2_ndof_2010,count_2010,"lp");
	leg->AddEntry(SingleGlb_glbChi2_ndof_2011,count_2011,"lp");
  leg->Draw();
	canv->Update();

	pad2->cd();

	ratio_2011 = (TH1F*)SingleGlb_glbChi2_ndof_2011->Clone("ratio_2011");
	ratio_2011->Divide(SingleGlb_glbChi2_ndof_2010);
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
	ratio_2011->GetYaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011->GetYaxis()->SetNdivisions(505);

	ratio_2011->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011->GetXaxis()->SetTitleSize(0.15);
	ratio_2011->GetXaxis()->SetTitle("Global #chi^{2}");
	
	gStyle->SetOptTitle(0);
	gPad->SetLogy(0);
	
	ratio_2011->Draw();
	l3a = new TLine(0,1.0,25,1.0);
	l3a->SetHorizontal(1);
	l3a->SetLineStyle(2);
	l3a->SetX2(25);
	l3a->Draw("same");

	canv->SaveAs("SingleGlb_glbChi2_ndof.pdf");
	canv->Clear(); canv->Draw();
// END glbChi2_ndof

// START trkChi2_ndof	
	canv = new TCanvas("canv","canv",1300,1000);
	
	pad1 = new TPad("pad1", "The pad 70% of the height",0.0,0.3,1.0,1.0,0);
	pad1->SetBottomMargin(0.0);
	pad2 = new TPad("pad2", "The pad 30% of the height",0.0,0.0,1.0,0.3,0);
	pad2->SetTopMargin(0.0);
	pad2->SetBottomMargin(0.35);



	pad1->Draw();
	pad2->Draw();

	pad1->cd();
	pad1->SetLogy(1);

	gStyle->SetMarkerSize(1);
	SingleGlb_trkChi2_ndof_2010->GetXaxis()->SetLabelSize(label_size);
	SingleGlb_trkChi2_ndof_2010->GetYaxis()->SetLabelSize(label_size);
	SingleGlb_trkChi2_ndof_2010->SetMinimum(1);
	SingleGlb_trkChi2_ndof_2010->Sumw2();
  SingleGlb_trkChi2_ndof_2010->SetMarkerStyle(25);
  SingleGlb_trkChi2_ndof_2010->SetMarkerSize(marker_size);
	SingleGlb_trkChi2_ndof_2010->Scale(1.0/SingleGlb_trkChi2_ndof_2010->GetEntries());
  SingleGlb_trkChi2_ndof_2010->DrawNormalized("p e",1);
	canv->Update();
	gStyle->SetStatX(0.8);
	gStyle->SetStatY(1.0);
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.2);
	gStyle->SetOptStat("mn");
	entries_2010 = SingleGlb_trkChi2_ndof_2010->GetEntries();
	canv->Update();
  SingleGlb_trkChi2_ndof_2011->Sumw2();
  SingleGlb_trkChi2_ndof_2011->SetMarkerColor(kRed);
  SingleGlb_trkChi2_ndof_2011->SetMarkerStyle(20);
  SingleGlb_trkChi2_ndof_2011->SetMarkerSize(marker_size);
	SingleGlb_trkChi2_ndof_2011->Scale(1.0/SingleGlb_trkChi2_ndof_2011->GetEntries());
  SingleGlb_trkChi2_ndof_2011->DrawNormalized("p e sames",1);
	gStyle->SetStatX(1.0);
	entries_2010 = SingleGlb_trkChi2_ndof_2010->GetEntries();
	entries_2011 = SingleGlb_trkChi2_ndof_2011->GetEntries();
	sprintf(count_2010,"  2010 Data - %i Muons", entries_2010);
	sprintf(count_2011,"  2011 Data - %i Muons", entries_2011);
	leg->Clear();
	leg->AddEntry(SingleGlb_trkChi2_ndof_2010,count_2010,"lp");
	leg->AddEntry(SingleGlb_trkChi2_ndof_2011,count_2011,"lp");
  leg->Draw();
	canv->Update();

	pad2->cd();

	ratio_2011 = (TH1F*)SingleGlb_trkChi2_ndof_2011->Clone("ratio_2011");
	ratio_2011->Divide(SingleGlb_trkChi2_ndof_2010);
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
	ratio_2011->GetYaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011->GetYaxis()->SetNdivisions(505);

	ratio_2011->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011->GetXaxis()->SetTitleSize(0.15);
	ratio_2011->GetXaxis()->SetTitle("Tracker #chi^{2}");
	
	gStyle->SetOptTitle(0);
	gPad->SetLogy(0);
	
	ratio_2011->Draw();
	l3a = new TLine(0,1.0,10,1.0);
	l3a->SetHorizontal(1);
	l3a->SetLineStyle(2);
	l3a->SetX2(10);
	l3a->Draw("same");

	canv->SaveAs("SingleGlb_trkChi2_ndof.pdf");
	canv->Clear(); canv->Draw();
// END trkChi2_ndof

// START pixLayerWMeas	
	canv = new TCanvas("canv","canv",1300,1000);
	
	pad1 = new TPad("pad1", "The pad 70% of the height",0.0,0.3,1.0,1.0,0);
	pad1->SetBottomMargin(0.0);
	pad2 = new TPad("pad2", "The pad 30% of the height",0.0,0.0,1.0,0.3,0);
	pad2->SetTopMargin(0.0);
	pad2->SetBottomMargin(0.35);



	pad1->Draw();
	pad2->Draw();

	pad1->cd();
	pad1->SetLogy(0);

	gStyle->SetMarkerSize(1);
	SingleGlb_pixLayerWMeas_2010->GetXaxis()->SetLabelSize(label_size);
	SingleGlb_pixLayerWMeas_2010->GetYaxis()->SetLabelSize(label_size);
	SingleGlb_pixLayerWMeas_2010->SetMinimum(0);
	SingleGlb_pixLayerWMeas_2010->Sumw2();
  SingleGlb_pixLayerWMeas_2010->SetMarkerStyle(25);
  SingleGlb_pixLayerWMeas_2010->SetMarkerSize(marker_size);
	SingleGlb_pixLayerWMeas_2010->Scale(1.0/SingleGlb_pixLayerWMeas_2010->GetEntries());
  SingleGlb_pixLayerWMeas_2010->DrawNormalized("p e",1);
	canv->Update();
	gStyle->SetStatX(0.8);
	gStyle->SetStatY(1.0);
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.2);
	gStyle->SetOptStat("mn");
	entries_2010 = SingleGlb_pixLayerWMeas_2010->GetEntries();
	canv->Update();
  SingleGlb_pixLayerWMeas_2011->Sumw2();
  SingleGlb_pixLayerWMeas_2011->SetMarkerColor(kRed);
  SingleGlb_pixLayerWMeas_2011->SetMarkerStyle(20);
  SingleGlb_pixLayerWMeas_2011->SetMarkerSize(marker_size);
	SingleGlb_pixLayerWMeas_2011->Scale(1.0/SingleGlb_pixLayerWMeas_2011->GetEntries());
  SingleGlb_pixLayerWMeas_2011->DrawNormalized("p e sames",1);
	gStyle->SetStatX(1.0);
	entries_2010 = SingleGlb_pixLayerWMeas_2010->GetEntries();
	entries_2011 = SingleGlb_pixLayerWMeas_2011->GetEntries();
	sprintf(count_2010,"  2010 Data - %i Muons", entries_2010);
	sprintf(count_2011,"  2011 Data - %i Muons", entries_2011);
	leg->Clear();
	leg->AddEntry(SingleGlb_pixLayerWMeas_2010,count_2010,"lp");
	leg->AddEntry(SingleGlb_pixLayerWMeas_2011,count_2011,"lp");
  leg->Draw();
	canv->Update();

	pad2->cd();

	ratio_2011 = (TH1F*)SingleGlb_pixLayerWMeas_2011->Clone("ratio_2011");
	ratio_2011->Divide(SingleGlb_pixLayerWMeas_2010);
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
	ratio_2011->GetYaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011->GetYaxis()->SetNdivisions(505);

	ratio_2011->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011->GetXaxis()->SetTitleSize(0.15);
	ratio_2011->GetXaxis()->SetTitle("Number of Pixel Layers with Measurement");
	
	gStyle->SetOptTitle(0);
	gPad->SetLogy(0);
	
	ratio_2011->Draw();
	l3a = new TLine(0,1.0,5,1.0);
	l3a->SetHorizontal(1);
	l3a->SetLineStyle(2);
	l3a->SetX2(5);
	l3a->Draw("same");

	canv->SaveAs("SingleGlb_pixLayerWMeas.pdf");
	canv->Clear(); canv->Draw();
// END pixLayerWMeas

// START trkDz	
	canv = new TCanvas("canv","canv",1300,1000);
	
	pad1 = new TPad("pad1", "The pad 70% of the height",0.0,0.3,1.0,1.0,0);
	pad1->SetBottomMargin(0.0);
	pad2 = new TPad("pad2", "The pad 30% of the height",0.0,0.0,1.0,0.3,0);
	pad2->SetTopMargin(0.0);
	pad2->SetBottomMargin(0.35);



	pad1->Draw();
	pad2->Draw();

	pad1->cd();
	pad1->SetLogy(1);

	gStyle->SetMarkerSize(1);
	SingleGlb_trkDz_2010->GetXaxis()->SetLabelSize(label_size);
	SingleGlb_trkDz_2010->GetYaxis()->SetLabelSize(label_size);
	SingleGlb_trkDz_2010->SetMinimum(1);
	SingleGlb_trkDz_2010->Sumw2();
  SingleGlb_trkDz_2010->SetMarkerStyle(25);
  SingleGlb_trkDz_2010->SetMarkerSize(marker_size);
	SingleGlb_trkDz_2010->Scale(1.0/SingleGlb_trkDz_2010->GetEntries());
  SingleGlb_trkDz_2010->DrawNormalized("p e",1);
	canv->Update();
	gStyle->SetStatX(0.8);
	gStyle->SetStatY(1.0);
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.2);
	gStyle->SetOptStat("mn");
	entries_2010 = SingleGlb_trkDz_2010->GetEntries();
	canv->Update();
  SingleGlb_trkDz_2011->Sumw2();
  SingleGlb_trkDz_2011->SetMarkerColor(kRed);
  SingleGlb_trkDz_2011->SetMarkerStyle(20);
  SingleGlb_trkDz_2011->SetMarkerSize(marker_size);
	SingleGlb_trkDz_2011->Scale(1.0/SingleGlb_trkDz_2011->GetEntries());
  SingleGlb_trkDz_2011->DrawNormalized("p e sames",1);
	gStyle->SetStatX(1.0);
	entries_2010 = SingleGlb_trkDz_2010->GetEntries();
	entries_2011 = SingleGlb_trkDz_2011->GetEntries();
	sprintf(count_2010,"  2010 Data - %i Muons", entries_2010);
	sprintf(count_2011,"  2011 Data - %i Muons", entries_2011);
	leg->Clear();
	leg->AddEntry(SingleGlb_trkDz_2010,count_2010,"lp");
	leg->AddEntry(SingleGlb_trkDz_2011,count_2011,"lp");
  leg->Draw();
	canv->Update();

	pad2->cd();

	ratio_2011 = (TH1F*)SingleGlb_trkDz_2011->Clone("ratio_2011");
	ratio_2011->Divide(SingleGlb_trkDz_2010);
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
	ratio_2011->GetYaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011->GetYaxis()->SetNdivisions(505);

	ratio_2011->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011->GetXaxis()->SetTitleSize(0.15);
	ratio_2011->GetXaxis()->SetTitle("Track Dz (cm)");
	
	gStyle->SetOptTitle(0);
	gPad->SetLogy(0);
	
	ratio_2011->Draw();
	l3a = new TLine(0,1.0,2,1.0);
	l3a->SetHorizontal(1);
	l3a->SetLineStyle(2);
	l3a->SetX2(2);
	l3a->Draw("same");

	canv->SaveAs("SingleGlb_trkDz.pdf");
	canv->Clear(); canv->Draw();
// END trkDz

// START trkDxy	
	canv = new TCanvas("canv","canv",1300,1000);
	
	pad1 = new TPad("pad1", "The pad 70% of the height",0.0,0.3,1.0,1.0,0);
	pad1->SetBottomMargin(0.0);
	pad2 = new TPad("pad2", "The pad 30% of the height",0.0,0.0,1.0,0.3,0);
	pad2->SetTopMargin(0.0);
	pad2->SetBottomMargin(0.35);



	pad2->SetBottomMargin(0.1);
	pad1->Draw();
	pad2->Draw();

	pad1->cd();
	pad1->SetLogy(1);

	gStyle->SetMarkerSize(1);
	SingleGlb_trkDxy_2010->GetXaxis()->SetLabelSize(label_size);
	SingleGlb_trkDxy_2010->GetYaxis()->SetLabelSize(label_size);
	SingleGlb_trkDxy_2010->SetMinimum(1);
	SingleGlb_trkDxy_2010->Sumw2();
  SingleGlb_trkDxy_2010->SetMarkerStyle(25);
  SingleGlb_trkDxy_2010->SetMarkerSize(marker_size);
	SingleGlb_trkDxy_2010->Scale(1.0/SingleGlb_trkDxy_2010->GetEntries());
  SingleGlb_trkDxy_2010->DrawNormalized("p e",1);
	canv->Update();
	gStyle->SetStatX(0.8);
	gStyle->SetStatY(1.0);
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.2);
	gStyle->SetOptStat("mn");
	entries_2010 = SingleGlb_trkDxy_2010->GetEntries();
	canv->Update();
  SingleGlb_trkDxy_2011->Sumw2();
  SingleGlb_trkDxy_2011->SetMarkerColor(kRed);
  SingleGlb_trkDxy_2011->SetMarkerStyle(20);
  SingleGlb_trkDxy_2011->SetMarkerStyle(marker_size);
	SingleGlb_trkDxy_2011->Scale(1.0/SingleGlb_trkDxy_2011->GetEntries());
  SingleGlb_trkDxy_2011->DrawNormalized("p e sames",1);
	gStyle->SetStatX(1.0);
	canv->Update();
	entries_2010 = SingleGlb_trkDxy_2010->GetEntries();
	entries_2011 = SingleGlb_trkDxy_2011->GetEntries();
	sprintf(count_2010,"  2010 Data - %i Muons", entries_2010);
	sprintf(count_2011,"  2011 Data - %i Muons", entries_2011);
	leg->Clear();
	leg->AddEntry(SingleGlb_trkDxy_2010,count_2010,"lp");
	leg->AddEntry(SingleGlb_trkDxy_2011,count_2011,"lp");
  leg->Draw();
	canv->Update();

	pad2->cd();

	ratio_2011 = (TH1F*)SingleGlb_trkDxy_2011->Clone("ratio_2011");
	ratio_2011->Divide(SingleGlb_trkDxy_2010);
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
	ratio_2011->GetYaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011->GetYaxis()->SetNdivisions(505);

	ratio_2011->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011->GetXaxis()->SetTitleSize(0.15);
	ratio_2011->GetXaxis()->SetTitle("Track Dxy (cm)");
	
	gStyle->SetOptTitle(0);
	gPad->SetLogy(0);
	
	ratio_2011->Draw();
	l3a = new TLine(0,1.0,2,1.0);
	l3a->SetHorizontal(1);
	l3a->SetLineStyle(2);
	l3a->SetX2(2);
	l3a->Draw("same");

	canv->SaveAs("SingleGlb_trkDxy.pdf");
	canv->Clear(); canv->Draw();
// END trkDxy

	// START Eta	
	canv = new TCanvas("canv","canv",1300,1000);
	
	pad1 = new TPad("pad1", "The pad 70% of the height",0.0,0.3,1.0,1.0,0);
	pad1->SetTopMargin(0.1);
	pad1->SetBottomMargin(0.0);
	pad2 = new TPad("pad2", "The pad 30% of the height",0.0,0.0,1.0,0.3,0);
	pad2->SetTopMargin(0.0);
	pad2->SetBottomMargin(0.35);



	pad1->Draw();
	pad2->Draw();

	pad1->cd();
	pad1->SetLogy(0);

	gStyle->SetMarkerSize(1);
	SingleGlb_Eta_2010_qual->GetXaxis()->SetLabelSize(label_size);
	SingleGlb_Eta_2010_qual->GetYaxis()->SetLabelSize(label_size);
	SingleGlb_Eta_2010_qual->SetMinimum(0);
	SingleGlb_Eta_2010_qual->Sumw2();
  SingleGlb_Eta_2010_qual->SetMarkerStyle(25);
  SingleGlb_Eta_2010_qual->SetMarkerSize(marker_size);
	SingleGlb_Eta_2010_qual->Scale(1.0/SingleGlb_Eta_2010_qual->GetEntries());
  SingleGlb_Eta_2010_qual->DrawNormalized("p e",1);
	gStyle->SetStatX(0.8);
	gStyle->SetStatY(1.0);
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.2);
	gStyle->SetOptStat("mn");
	entries_2010_qual = SingleGlb_Eta_2010_qual->GetEntries();
	canv->Update();
  SingleGlb_Eta_2011_qual->Sumw2();
  SingleGlb_Eta_2011_qual->SetMarkerColor(kRed);
  SingleGlb_Eta_2011_qual->SetMarkerStyle(20);
  SingleGlb_Eta_2011_qual->SetMarkerSize(marker_size);
	SingleGlb_Eta_2011_qual->Scale(1.0/SingleGlb_Eta_2011_qual->GetEntries());
  SingleGlb_Eta_2011_qual->DrawNormalized("p e sames",1);
	gStyle->SetStatX(1.0);
	entries_2010_qual = SingleGlb_Eta_2010_qual->GetEntries();
	entries_2011_qual = SingleGlb_Eta_2011_qual->GetEntries();
	sprintf(count_2010_qual,"  2010_qual Data - %i Muons", entries_2010_qual);
	sprintf(count_2011_qual,"  2011_qual Data - %i Muons", entries_2011_qual);
	leg->Clear();
	leg->AddEntry(SingleGlb_Eta_2010_qual,count_2010_qual,"lp");
	leg->AddEntry(SingleGlb_Eta_2011_qual,count_2011_qual,"lp");
  leg->Draw();
	canv->Update();

	pad2->cd();

	ratio_2011_qual = (TH1F*)SingleGlb_Eta_2011_qual->Clone("ratio_2011_qual");
	ratio_2011_qual->Divide(SingleGlb_Eta_2010_qual);
	ratio_2011_qual->SetMarkerColor(kViolet);
	ratio_2011_qual->SetMarkerStyle(29);
	ratio_2011_qual->SetMarkerSize(marker_size*5.0/3.0);

	ratio_2011_qual->SetMinimum(0);
	ratio_2011_qual->SetMaximum(ratio_2011_qual->GetMaximum()+0.1);

	gStyle->SetStatX(0.55);
	gStyle->SetStatY(0.6);
	gStyle->SetStatW(0.1);
	gStyle->SetStatH(0.3);
	gStyle->SetOptStat("");

	gStyle->SetMarkerSize(1);
	ratio_2011_qual->GetYaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011_qual->GetYaxis()->SetNdivisions(505);

	ratio_2011_qual->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011_qual->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011_qual->GetXaxis()->SetTitleSize(0.15);
	ratio_2011_qual->GetXaxis()->SetTitle("#eta");
	
	gStyle->SetOptTitle(0);
	gPad->SetLogy(0);
	
	ratio_2011_qual->Draw();

	l3a = new TLine(-2.4,1.0,2.4,1.0);
	l3a->SetHorizontal(1);
	l3a->SetLineStyle(2);
	l3a->SetX2(2.4);
	l3a->Draw("same");
	
	canv->SaveAs("SingleGlb_Eta_qual.pdf");
	canv->Clear(); canv->Draw();
// END Eta	

	// START Pt	
	canv = new TCanvas("canv","canv",1300,1000);
	
	pad1 = new TPad("pad1", "The pad 70% of the height",0.0,0.3,1.0,1.0,0);
	pad1->SetBottomMargin(0.0);
	pad2 = new TPad("pad2", "The pad 30% of the height",0.0,0.0,1.0,0.3,0);
	pad2->SetTopMargin(0.0);
	pad2->SetBottomMargin(0.35);

	pad1->Draw();
	pad2->Draw();

	pad1->cd();
	pad1->SetLogy(1);

	gStyle->SetMarkerSize(1);
	SingleGlb_Pt_2010_qual->GetXaxis()->SetLabelSize(label_size);
	SingleGlb_Pt_2010_qual->GetYaxis()->SetLabelSize(label_size);
	SingleGlb_Pt_2010_qual->SetMinimum(1);
	SingleGlb_Pt_2010_qual->Sumw2();
  SingleGlb_Pt_2010_qual->SetMarkerStyle(25);
  SingleGlb_Pt_2010_qual->SetMarkerSize(marker_size);
	SingleGlb_Pt_2010_qual->Scale(1.0/SingleGlb_Pt_2010_qual->GetEntries());
  SingleGlb_Pt_2010_qual->DrawNormalized("p e",1);
	gStyle->SetStatX(0.8);
	gStyle->SetStatY(1.0);
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.2);
	gStyle->SetOptStat("mn");
	entries_2010_qual = SingleGlb_Pt_2010_qual->GetEntries();
	canv->Update();
  SingleGlb_Pt_2011_qual->Sumw2();
  SingleGlb_Pt_2011_qual->SetMarkerColor(kRed);
  SingleGlb_Pt_2011_qual->SetMarkerStyle(20);
  SingleGlb_Pt_2011_qual->SetMarkerSize(marker_size);
	SingleGlb_Pt_2011_qual->Scale(1.0/SingleGlb_Pt_2011_qual->GetEntries());
  SingleGlb_Pt_2011_qual->DrawNormalized("p e sames",1);
	gStyle->SetStatX(1.0);
	entries_2010_qual = SingleGlb_Pt_2010_qual->GetEntries();
	entries_2011_qual = SingleGlb_Pt_2011_qual->GetEntries();
	sprintf(count_2010_qual,"  2010_qual Data - %i Muons", entries_2010_qual);
	sprintf(count_2011_qual,"  2011_qual Data - %i Muons", entries_2011_qual);
	leg->Clear();
	leg->AddEntry(SingleGlb_Pt_2010_qual,count_2010_qual,"lp");
	leg->AddEntry(SingleGlb_Pt_2011_qual,count_2011_qual,"lp");
  leg->Draw();
	canv->Update();

	pad2->cd();

	ratio_2011_qual = (TH1F*)SingleGlb_Pt_2011_qual->Clone("ratio_2011_qual");
	ratio_2011_qual->Divide(SingleGlb_Pt_2010_qual);
	ratio_2011_qual->SetMarkerColor(kViolet);
	ratio_2011_qual->SetMarkerStyle(29);
	ratio_2011_qual->SetMarkerSize(marker_size*5.0/3.0);

	ratio_2011_qual->SetMinimum(0);
	ratio_2011_qual->SetMaximum(ratio_2011_qual->GetMaximum()+0.1);

	gStyle->SetStatX(0.55);
	gStyle->SetStatY(0.6);
	gStyle->SetStatW(0.1);
	gStyle->SetStatH(0.3);
	gStyle->SetOptStat("");

	gStyle->SetMarkerSize(1);
	ratio_2011_qual->GetYaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011_qual->GetYaxis()->SetNdivisions(505);

	ratio_2011_qual->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011_qual->GetXaxis()->SetTitleSize(0.15);
	ratio_2011_qual->GetXaxis()->SetTitle("p_{T}");
	
	gStyle->SetOptTitle(0);
	gPad->SetLogy(0);
	
	ratio_2011_qual->Draw();

	l3a = new TLine(0,1.0,60,1.0);
	l3a->SetHorizontal(1);
	l3a->SetLineStyle(2);
	l3a->SetX2(60);
	l3a->Draw("same");
	
	canv->SaveAs("SingleGlb_Pt_qual.pdf");
	canv->Clear(); canv->Draw();
// END Pt	

	// START Phi	
	canv = new TCanvas("canv","canv",1300,1000);
	
	pad1 = new TPad("pad1", "The pad 70% of the height",0.0,0.3,1.0,1.0,0);
	pad1->SetBottomMargin(0.0);
	pad2 = new TPad("pad2", "The pad 30% of the height",0.0,0.0,1.0,0.3,0);
	pad2->SetTopMargin(0.0);
	pad2->SetBottomMargin(0.35);


	pad1->Draw();
	pad2->Draw();

	pad1->cd();
	pad1->SetLogy(0);

	gStyle->SetMarkerSize(1);
	SingleGlb_Phi_2010_qual->GetXaxis()->SetLabelSize(label_size);
	SingleGlb_Phi_2010_qual->GetYaxis()->SetLabelSize(label_size);
	SingleGlb_Phi_2010_qual->SetMinimum(0);
	SingleGlb_Phi_2010_qual->Sumw2();
  SingleGlb_Phi_2010_qual->SetMarkerStyle(25);
  SingleGlb_Phi_2010_qual->SetMarkerSize(marker_size);
	SingleGlb_Phi_2010_qual->Scale(1.0/SingleGlb_Phi_2010_qual->GetEntries());
  SingleGlb_Phi_2010_qual->DrawNormalized("p e",1);
	gStyle->SetStatX(0.8);
	gStyle->SetStatY(1.0);
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.2);
	gStyle->SetOptStat("mn");
	entries_2010_qual = SingleGlb_Phi_2010_qual->GetEntries();
	canv->Update();
  SingleGlb_Phi_2011_qual->Sumw2();
  SingleGlb_Phi_2011_qual->SetMarkerColor(kRed);
  SingleGlb_Phi_2011_qual->SetMarkerStyle(20);
  SingleGlb_Phi_2011_qual->SetMarkerSize(marker_size);
	SingleGlb_Phi_2011_qual->Scale(1.0/SingleGlb_Phi_2011_qual->GetEntries());
  SingleGlb_Phi_2011_qual->DrawNormalized("p e sames",1);
	gStyle->SetStatX(1.0);
	entries_2010_qual = SingleGlb_Phi_2010_qual->GetEntries();
	entries_2011_qual = SingleGlb_Phi_2011_qual->GetEntries();
	sprintf(count_2010_qual,"  2010_qual Data - %i Muons", entries_2010_qual);
	sprintf(count_2011_qual,"  2011_qual Data - %i Muons", entries_2011_qual);
	leg->Clear();
	leg->AddEntry(SingleGlb_Phi_2010_qual,count_2010_qual,"lp");
	leg->AddEntry(SingleGlb_Phi_2011_qual,count_2011_qual,"lp");
  leg->Draw();
	canv->Update();

	pad2->cd();

	ratio_2011_qual = (TH1F*)SingleGlb_Phi_2011_qual->Clone("ratio_2011_qual");
	ratio_2011_qual->Divide(SingleGlb_Phi_2010_qual);
	ratio_2011_qual->SetMarkerColor(kViolet);
	ratio_2011_qual->SetMarkerStyle(29);
	ratio_2011_qual->SetMarkerSize(marker_size*5.0/3.0);

	ratio_2011_qual->SetMinimum(0);
	ratio_2011_qual->SetMaximum(ratio_2011_qual->GetMaximum()+0.1);

	gStyle->SetStatX(0.55);
	gStyle->SetStatY(0.6);
	gStyle->SetStatW(0.1);
	gStyle->SetStatH(0.3);
	gStyle->SetOptStat("");

	gStyle->SetMarkerSize(1);
	ratio_2011_qual->GetYaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011_qual->GetYaxis()->SetNdivisions(505);

	ratio_2011_qual->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011_qual->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011_qual->GetXaxis()->SetTitleSize(0.15);
	ratio_2011_qual->GetXaxis()->SetTitle("#phi");
	
	gStyle->SetOptTitle(0);
	gPad->SetLogy(0);
	
	ratio_2011_qual->Draw();

	l3a = new TLine(-PI,1.0,PI,1.0);
	l3a->SetHorizontal(1);
	l3a->SetLineStyle(2);
	l3a->SetX2(PI);
	l3a->Draw("same");
	
	canv->SaveAs("SingleGlb_Phi_qual.pdf");
	canv->Clear(); canv->Draw();
// END Phi	
	
	// START nValMuHits	
	canv = new TCanvas("canv","canv",1300,1000);
	
	pad1 = new TPad("pad1", "The pad 70% of the height",0.0,0.3,1.0,1.0,0);
	pad1->SetBottomMargin(0.0);
	pad2 = new TPad("pad2", "The pad 30% of the height",0.0,0.0,1.0,0.3,0);
	pad2->SetTopMargin(0.0);
	pad2->SetBottomMargin(0.35);



	pad1->Draw();
	pad2->Draw();

	pad1->cd();
	pad1->SetLogy(0);

	gStyle->SetMarkerSize(1);
	SingleGlb_nValMuHits_2010_qual->GetXaxis()->SetLabelSize(label_size);
	SingleGlb_nValMuHits_2010_qual->GetYaxis()->SetLabelSize(label_size);
	SingleGlb_nValMuHits_2010_qual->SetMinimum(0);
	SingleGlb_nValMuHits_2010_qual->Sumw2();
  SingleGlb_nValMuHits_2010_qual->SetMarkerStyle(25);
  SingleGlb_nValMuHits_2010_qual->SetMarkerSize(marker_size);
	SingleGlb_nValMuHits_2010_qual->Scale(1.0/SingleGlb_nValMuHits_2010_qual->GetEntries());
  SingleGlb_nValMuHits_2010_qual->DrawNormalized("p e",1);
	gStyle->SetStatX(0.8);
	gStyle->SetStatY(1.0);
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.2);
	gStyle->SetOptStat("mn");
	entries_2010_qual = SingleGlb_nValMuHits_2010_qual->GetEntries();
	canv->Update();
  SingleGlb_nValMuHits_2011_qual->Sumw2();
  SingleGlb_nValMuHits_2011_qual->SetMarkerColor(kRed);
  SingleGlb_nValMuHits_2011_qual->SetMarkerStyle(20);
  SingleGlb_nValMuHits_2011_qual->SetMarkerSize(marker_size);
	SingleGlb_nValMuHits_2011_qual->Scale(1.0/SingleGlb_nValMuHits_2011_qual->GetEntries());
  SingleGlb_nValMuHits_2011_qual->DrawNormalized("p e sames",1);
	gStyle->SetStatX(1.0);
	entries_2010_qual = SingleGlb_nValMuHits_2010_qual->GetEntries();
	entries_2011_qual = SingleGlb_nValMuHits_2011_qual->GetEntries();
	sprintf(count_2010_qual,"  2010_qual Data - %i Muons", entries_2010_qual);
	sprintf(count_2011_qual,"  2011_qual Data - %i Muons", entries_2011_qual);
	leg->Clear();
	leg->AddEntry(SingleGlb_nValMuHits_2010_qual,count_2010_qual,"lp");
	leg->AddEntry(SingleGlb_nValMuHits_2011_qual,count_2011_qual,"lp");
  leg->Draw();
	canv->Update();

	pad2->cd();

	ratio_2011_qual = (TH1F*)SingleGlb_nValMuHits_2011_qual->Clone("ratio_2011_qual");
	ratio_2011_qual->Divide(SingleGlb_nValMuHits_2010_qual);
	ratio_2011_qual->SetMarkerColor(kViolet);
	ratio_2011_qual->SetMarkerStyle(29);
	ratio_2011_qual->SetMarkerSize(marker_size*5.0/3.0);

	ratio_2011_qual->SetMinimum(0);
	ratio_2011_qual->SetMaximum(ratio_2011_qual->GetMaximum()+0.1);

	gStyle->SetStatX(0.55);
	gStyle->SetStatY(0.6);
	gStyle->SetStatW(0.1);
	gStyle->SetStatH(0.3);
	gStyle->SetOptStat("");

	gStyle->SetMarkerSize(1);
	ratio_2011_qual->GetYaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011_qual->GetYaxis()->SetNdivisions(505);

	ratio_2011_qual->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011_qual->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011_qual->GetXaxis()->SetTitleSize(0.15);
	ratio_2011_qual->GetXaxis()->SetTitle("Number of Valid Muon Hits");
	
	gStyle->SetOptTitle(0);
	gPad->SetLogy(0);
	
	ratio_2011_qual->Draw();

	l3a = new TLine(0,1.0,60,1.0);
	l3a->SetHorizontal(1);
	l3a->SetLineStyle(2);
	l3a->SetX2(60);
	l3a->Draw("same");
	
	canv->SaveAs("SingleGlb_nValMuHits_qual.pdf");
	canv->Clear(); canv->Draw();
// END nValMuHits	
	
// START nValTrkHits	
	canv = new TCanvas("canv","canv",1300,1000);
	
	pad1 = new TPad("pad1", "The pad 70% of the height",0.0,0.3,1.0,1.0,0);
	pad1->SetBottomMargin(0.0);
	pad2 = new TPad("pad2", "The pad 30% of the height",0.0,0.0,1.0,0.3,0);
	pad2->SetTopMargin(0.0);
	pad2->SetBottomMargin(0.35);



	pad1->Draw();
	pad2->Draw();

	pad1->cd();
	pad1->SetLogy(0);

	gStyle->SetMarkerSize(1);
	SingleGlb_nValTrkHits_2010_qual->GetXaxis()->SetLabelSize(label_size);
	SingleGlb_nValTrkHits_2010_qual->GetYaxis()->SetLabelSize(label_size);
	SingleGlb_nValTrkHits_2010_qual->SetMinimum(0);
	SingleGlb_nValTrkHits_2010_qual->Sumw2();
  SingleGlb_nValTrkHits_2010_qual->SetMarkerStyle(25);
  SingleGlb_nValTrkHits_2010_qual->SetMarkerSize(marker_size);
	SingleGlb_nValTrkHits_2010_qual->Scale(1.0/SingleGlb_nValTrkHits_2010_qual->GetEntries());
  SingleGlb_nValTrkHits_2010_qual->DrawNormalized("p e",1);
	canv->Update();
	gStyle->SetStatX(0.8);
	gStyle->SetStatY(1.0);
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.2);
	gStyle->SetOptStat("mn");
	entries_2010_qual = SingleGlb_nValTrkHits_2010_qual->GetEntries();
	canv->Update();
  SingleGlb_nValTrkHits_2011_qual->Sumw2();
  SingleGlb_nValTrkHits_2011_qual->SetMarkerColor(kRed);
  SingleGlb_nValTrkHits_2011_qual->SetMarkerStyle(20);
  SingleGlb_nValTrkHits_2011_qual->SetMarkerSize(marker_size);
	SingleGlb_nValTrkHits_2011_qual->Scale(1.0/SingleGlb_nValTrkHits_2011_qual->GetEntries());
  SingleGlb_nValTrkHits_2011_qual->DrawNormalized("p e sames",1);
	gStyle->SetStatX(1.0);
	entries_2010_qual = SingleGlb_nValTrkHits_2010_qual->GetEntries();
	entries_2011_qual = SingleGlb_nValTrkHits_2011_qual->GetEntries();
	sprintf(count_2010_qual,"  2010_qual Data - %i Muons", entries_2010_qual);
	sprintf(count_2011_qual,"  2011_qual Data - %i Muons", entries_2011_qual);
	leg->Clear();
	leg->AddEntry(SingleGlb_nValTrkHits_2010_qual,count_2010_qual,"lp");
	leg->AddEntry(SingleGlb_nValTrkHits_2011_qual,count_2011_qual,"lp");
  leg->Draw();
	canv->Update();

	pad2->cd();

	ratio_2011_qual = (TH1F*)SingleGlb_nValTrkHits_2011_qual->Clone("ratio_2011_qual");
	ratio_2011_qual->Divide(SingleGlb_nValTrkHits_2010_qual);
	ratio_2011_qual->SetMarkerColor(kViolet);
	ratio_2011_qual->SetMarkerStyle(29);
	ratio_2011_qual->SetMarkerSize(marker_size*5.0/3.0);

	ratio_2011_qual->SetMinimum(0);
	ratio_2011_qual->SetMaximum(ratio_2011_qual->GetMaximum()+0.1);

	gStyle->SetStatX(0.55);
	gStyle->SetStatY(0.6);
	gStyle->SetStatW(0.1);
	gStyle->SetStatH(0.3);
	gStyle->SetOptStat("");

	gStyle->SetMarkerSize(1);
	ratio_2011_qual->GetYaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011_qual->GetYaxis()->SetNdivisions(505);

	ratio_2011_qual->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011_qual->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011_qual->GetXaxis()->SetTitleSize(0.15);
	ratio_2011_qual->GetXaxis()->SetTitle("Number of Valid Tracker Hits");
	
	gStyle->SetOptTitle(0);
	gPad->SetLogy(0);
	
	ratio_2011_qual->Draw();
	l3a = new TLine(0,1.0,30,1.0);
	l3a->SetHorizontal(1);
	l3a->SetLineStyle(2);
	l3a->SetX2(30);
	l3a->Draw("same");

	canv->SaveAs("SingleGlb_nValTrkHits_qual.pdf");
	canv->Clear(); canv->Draw();
// END nValTrkHits	

// START glbChi2_ndof	
	canv = new TCanvas("canv","canv",1300,1000);
	
	pad1 = new TPad("pad1", "The pad 70% of the height",0.0,0.3,1.0,1.0,0);
	pad1->SetBottomMargin(0.0);
	pad2 = new TPad("pad2", "The pad 30% of the height",0.0,0.0,1.0,0.3,0);
	pad2->SetTopMargin(0.0);
	pad2->SetBottomMargin(0.35);



	pad1->Draw();
	pad2->Draw();

	pad1->cd();
	pad1->SetLogy(1);

	gStyle->SetMarkerSize(1);
	SingleGlb_glbChi2_ndof_2010_qual->GetXaxis()->SetLabelSize(label_size);
	SingleGlb_glbChi2_ndof_2010_qual->GetYaxis()->SetLabelSize(label_size);
	SingleGlb_glbChi2_ndof_2010_qual->SetMinimum(1);
	SingleGlb_glbChi2_ndof_2010_qual->Sumw2();
  SingleGlb_glbChi2_ndof_2010_qual->SetMarkerStyle(25);
  SingleGlb_glbChi2_ndof_2010_qual->SetMarkerSize(marker_size);
	SingleGlb_glbChi2_ndof_2010_qual->Scale(1.0/SingleGlb_glbChi2_ndof_2010_qual->GetEntries());
  SingleGlb_glbChi2_ndof_2010_qual->DrawNormalized("p e",1);
	canv->Update();
	gStyle->SetStatX(0.8);
	gStyle->SetStatY(1.0);
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.2);
	gStyle->SetOptStat("mn");
	entries_2010_qual = SingleGlb_glbChi2_ndof_2010_qual->GetEntries();
	canv->Update();
  SingleGlb_glbChi2_ndof_2011_qual->Sumw2();
  SingleGlb_glbChi2_ndof_2011_qual->SetMarkerColor(kRed);
  SingleGlb_glbChi2_ndof_2011_qual->SetMarkerStyle(20);
  SingleGlb_glbChi2_ndof_2011_qual->SetMarkerSize(marker_size);
	SingleGlb_glbChi2_ndof_2011_qual->Scale(1.0/SingleGlb_glbChi2_ndof_2011_qual->GetEntries());
  SingleGlb_glbChi2_ndof_2011_qual->DrawNormalized("p e sames",1);
	gStyle->SetStatX(1.0);
	entries_2010_qual = SingleGlb_glbChi2_ndof_2010_qual->GetEntries();
	entries_2011_qual = SingleGlb_glbChi2_ndof_2011_qual->GetEntries();
	sprintf(count_2010_qual,"  2010_qual Data - %i Muons", entries_2010_qual);
	sprintf(count_2011_qual,"  2011_qual Data - %i Muons", entries_2011_qual);
	leg->Clear();
	leg->AddEntry(SingleGlb_glbChi2_ndof_2010_qual,count_2010_qual,"lp");
	leg->AddEntry(SingleGlb_glbChi2_ndof_2011_qual,count_2011_qual,"lp");
  leg->Draw();
	canv->Update();

	pad2->cd();

	ratio_2011_qual = (TH1F*)SingleGlb_glbChi2_ndof_2011_qual->Clone("ratio_2011_qual");
	ratio_2011_qual->Divide(SingleGlb_glbChi2_ndof_2010_qual);
	ratio_2011_qual->SetMarkerColor(kViolet);
	ratio_2011_qual->SetMarkerStyle(29);
	ratio_2011_qual->SetMarkerSize(marker_size*5.0/3.0);

	ratio_2011_qual->SetMinimum(0);
	ratio_2011_qual->SetMaximum(ratio_2011_qual->GetMaximum()+0.1);

	gStyle->SetStatX(0.55);
	gStyle->SetStatY(0.6);
	gStyle->SetStatW(0.1);
	gStyle->SetStatH(0.3);
	gStyle->SetOptStat("");

	gStyle->SetMarkerSize(1);
	ratio_2011_qual->GetYaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011_qual->GetYaxis()->SetNdivisions(505);

	ratio_2011_qual->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011_qual->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011_qual->GetXaxis()->SetTitleSize(0.15);
	ratio_2011_qual->GetXaxis()->SetTitle("Global #chi^{2}");
	
	gStyle->SetOptTitle(0);
	gPad->SetLogy(0);
	
	ratio_2011_qual->Draw();
	l3a = new TLine(0,1.0,25,1.0);
	l3a->SetHorizontal(1);
	l3a->SetLineStyle(2);
	l3a->SetX2(25);
	l3a->Draw("same");

	canv->SaveAs("SingleGlb_glbChi2_ndof_qual.pdf");
	canv->Clear(); canv->Draw();
// END glbChi2_ndof

// START trkChi2_ndof	
	canv = new TCanvas("canv","canv",1300,1000);
	
	pad1 = new TPad("pad1", "The pad 70% of the height",0.0,0.3,1.0,1.0,0);
	pad1->SetBottomMargin(0.0);
	pad2 = new TPad("pad2", "The pad 30% of the height",0.0,0.0,1.0,0.3,0);
	pad2->SetTopMargin(0.0);
	pad2->SetBottomMargin(0.35);



	pad1->Draw();
	pad2->Draw();

	pad1->cd();
	pad1->SetLogy(1);

	gStyle->SetMarkerSize(1);
	SingleGlb_trkChi2_ndof_2010_qual->GetXaxis()->SetLabelSize(label_size);
	SingleGlb_trkChi2_ndof_2010_qual->GetYaxis()->SetLabelSize(label_size);
	SingleGlb_trkChi2_ndof_2010_qual->SetMinimum(1);
	SingleGlb_trkChi2_ndof_2010_qual->Sumw2();
  SingleGlb_trkChi2_ndof_2010_qual->SetMarkerStyle(25);
  SingleGlb_trkChi2_ndof_2010_qual->SetMarkerSize(marker_size);
	SingleGlb_trkChi2_ndof_2010_qual->Scale(1.0/SingleGlb_trkChi2_ndof_2010_qual->GetEntries());
  SingleGlb_trkChi2_ndof_2010_qual->DrawNormalized("p e",1);
	canv->Update();
	gStyle->SetStatX(0.8);
	gStyle->SetStatY(1.0);
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.2);
	gStyle->SetOptStat("mn");
	entries_2010_qual = SingleGlb_trkChi2_ndof_2010_qual->GetEntries();
	canv->Update();
  SingleGlb_trkChi2_ndof_2011_qual->Sumw2();
  SingleGlb_trkChi2_ndof_2011_qual->SetMarkerColor(kRed);
  SingleGlb_trkChi2_ndof_2011_qual->SetMarkerStyle(20);
  SingleGlb_trkChi2_ndof_2011_qual->SetMarkerSize(marker_size);
	SingleGlb_trkChi2_ndof_2011_qual->Scale(1.0/SingleGlb_trkChi2_ndof_2011_qual->GetEntries());
  SingleGlb_trkChi2_ndof_2011_qual->DrawNormalized("p e sames",1);
	gStyle->SetStatX(1.0);
	entries_2010_qual = SingleGlb_trkChi2_ndof_2010_qual->GetEntries();
	entries_2011_qual = SingleGlb_trkChi2_ndof_2011_qual->GetEntries();
	sprintf(count_2010_qual,"  2010_qual Data - %i Muons", entries_2010_qual);
	sprintf(count_2011_qual,"  2011_qual Data - %i Muons", entries_2011_qual);
	leg->Clear();
	leg->AddEntry(SingleGlb_trkChi2_ndof_2010_qual,count_2010_qual,"lp");
	leg->AddEntry(SingleGlb_trkChi2_ndof_2011_qual,count_2011_qual,"lp");
  leg->Draw();
	canv->Update();

	pad2->cd();

	ratio_2011_qual = (TH1F*)SingleGlb_trkChi2_ndof_2011_qual->Clone("ratio_2011_qual");
	ratio_2011_qual->Divide(SingleGlb_trkChi2_ndof_2010_qual);
	ratio_2011_qual->SetMarkerColor(kViolet);
	ratio_2011_qual->SetMarkerStyle(29);
	ratio_2011_qual->SetMarkerSize(marker_size*5.0/3.0);

	ratio_2011_qual->SetMinimum(0);
	ratio_2011_qual->SetMaximum(ratio_2011_qual->GetMaximum()+0.1);

	gStyle->SetStatX(0.55);
	gStyle->SetStatY(0.6);
	gStyle->SetStatW(0.1);
	gStyle->SetStatH(0.3);
	gStyle->SetOptStat("");

	gStyle->SetMarkerSize(1);
	ratio_2011_qual->GetYaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011_qual->GetYaxis()->SetNdivisions(505);

	ratio_2011_qual->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011_qual->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011_qual->GetXaxis()->SetTitleSize(0.15);
	ratio_2011_qual->GetXaxis()->SetTitle("Tracker #chi^{2}");
	
	gStyle->SetOptTitle(0);
	gPad->SetLogy(0);
	
	ratio_2011_qual->Draw();
	l3a = new TLine(0,1.0,10,1.0);
	l3a->SetHorizontal(1);
	l3a->SetLineStyle(2);
	l3a->SetX2(10);
	l3a->Draw("same");

	canv->SaveAs("SingleGlb_trkChi2_ndof_qual.pdf");
	canv->Clear(); canv->Draw();
// END trkChi2_ndof

// START pixLayerWMeas	
	canv = new TCanvas("canv","canv",1300,1000);
	
	pad1 = new TPad("pad1", "The pad 70% of the height",0.0,0.3,1.0,1.0,0);
	pad1->SetBottomMargin(0.0);
	pad2 = new TPad("pad2", "The pad 30% of the height",0.0,0.0,1.0,0.3,0);
	pad2->SetTopMargin(0.0);
	pad2->SetBottomMargin(0.35);



	pad1->Draw();
	pad2->Draw();

	pad1->cd();
	pad1->SetLogy(0);

	gStyle->SetMarkerSize(1);
	SingleGlb_pixLayerWMeas_2010_qual->GetXaxis()->SetLabelSize(label_size);
	SingleGlb_pixLayerWMeas_2010_qual->GetYaxis()->SetLabelSize(label_size);
	SingleGlb_pixLayerWMeas_2010_qual->SetMinimum(0);
	SingleGlb_pixLayerWMeas_2010_qual->Sumw2();
  SingleGlb_pixLayerWMeas_2010_qual->SetMarkerStyle(25);
  SingleGlb_pixLayerWMeas_2010_qual->SetMarkerSize(marker_size);
	SingleGlb_pixLayerWMeas_2010_qual->Scale(1.0/SingleGlb_pixLayerWMeas_2010_qual->GetEntries());
  SingleGlb_pixLayerWMeas_2010_qual->DrawNormalized("p e",1);
	canv->Update();
	gStyle->SetStatX(0.8);
	gStyle->SetStatY(1.0);
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.2);
	gStyle->SetOptStat("mn");
	canv->Update();
	entries_2010_qual = SingleGlb_pixLayerWMeas_2010_qual->GetEntries();
	canv->Update();
  SingleGlb_pixLayerWMeas_2011_qual->Sumw2();
  SingleGlb_pixLayerWMeas_2011_qual->SetMarkerColor(kRed);
  SingleGlb_pixLayerWMeas_2011_qual->SetMarkerStyle(20);
  SingleGlb_pixLayerWMeas_2011_qual->SetMarkerSize(marker_size);
	SingleGlb_pixLayerWMeas_2011_qual->Scale(1.0/SingleGlb_pixLayerWMeas_2011_qual->GetEntries());
  SingleGlb_pixLayerWMeas_2011_qual->DrawNormalized("p e sames",1);
	gStyle->SetStatX(1.0);
	entries_2010_qual = SingleGlb_pixLayerWMeas_2010_qual->GetEntries();
	entries_2011_qual = SingleGlb_pixLayerWMeas_2011_qual->GetEntries();
	sprintf(count_2010_qual,"  2010_qual Data - %i Muons", entries_2010_qual);
	sprintf(count_2011_qual,"  2011_qual Data - %i Muons", entries_2011_qual);
	leg->Clear();
	leg->AddEntry(SingleGlb_pixLayerWMeas_2010_qual,count_2010_qual,"lp");
	leg->AddEntry(SingleGlb_pixLayerWMeas_2011_qual,count_2011_qual,"lp");
  leg->Draw();
	canv->Update();

	pad2->cd();

	ratio_2011_qual = (TH1F*)SingleGlb_pixLayerWMeas_2011_qual->Clone("ratio_2011_qual");
	ratio_2011_qual->Divide(SingleGlb_pixLayerWMeas_2010_qual);
	ratio_2011_qual->SetMarkerColor(kViolet);
		ratio_2011_qual->SetMarkerStyle(29);
	ratio_2011_qual->SetMarkerSize(marker_size*5.0/3.0);

	ratio_2011_qual->SetMinimum(0);
	ratio_2011_qual->SetMaximum(ratio_2011_qual->GetMaximum()+0.1);

	gStyle->SetStatX(0.55);
	gStyle->SetStatY(0.6);
	gStyle->SetStatW(0.1);
	gStyle->SetStatH(0.3);
	gStyle->SetOptStat("");

	gStyle->SetMarkerSize(1);
	ratio_2011_qual->GetYaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011_qual->GetYaxis()->SetNdivisions(505);

	ratio_2011_qual->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011_qual->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011_qual->GetXaxis()->SetTitleSize(0.15);
	ratio_2011_qual->GetXaxis()->SetTitle("Number of Pixel Layers with Measurement");
	
	gStyle->SetOptTitle(0);
	gPad->SetLogy(0);
	
	ratio_2011_qual->Draw();
	l3a = new TLine(0,1.0,5,1.0);
	l3a->SetHorizontal(1);
	l3a->SetLineStyle(2);
	l3a->SetX2(5);
	l3a->Draw("same");

	canv->SaveAs("SingleGlb_pixLayerWMeas_qual.pdf");
	canv->Clear(); canv->Draw();
// END pixLayerWMeas

// START trkDz	
	canv = new TCanvas("canv","canv",1300,1000);
	
	pad1 = new TPad("pad1", "The pad 70% of the height",0.0,0.3,1.0,1.0,0);
	pad1->SetBottomMargin(0.0);
	pad2 = new TPad("pad2", "The pad 30% of the height",0.0,0.0,1.0,0.3,0);
	pad2->SetTopMargin(0.0);
	pad2->SetBottomMargin(0.35);



	pad1->Draw();
	pad2->Draw();

	pad1->cd();
	pad1->SetLogy(1);

	gStyle->SetMarkerSize(1);
	SingleGlb_trkDz_2010_qual->GetXaxis()->SetLabelSize(label_size);
	SingleGlb_trkDz_2010_qual->GetYaxis()->SetLabelSize(label_size);
	SingleGlb_trkDz_2010_qual->SetMinimum(1);
	SingleGlb_trkDz_2010_qual->Sumw2();
  SingleGlb_trkDz_2010_qual->SetMarkerStyle(25);
  SingleGlb_trkDz_2010_qual->SetMarkerSize(marker_size);
	SingleGlb_trkDz_2010_qual->Scale(1.0/SingleGlb_trkDz_2010_qual->GetEntries());
  SingleGlb_trkDz_2010_qual->DrawNormalized("p e",1);
	canv->Update();
	gStyle->SetStatX(0.8);
	gStyle->SetStatY(1.0);
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.2);
	gStyle->SetOptStat("mn");
	canv->Update();
	entries_2010_qual = SingleGlb_trkDz_2010_qual->GetEntries();
	canv->Update();
  SingleGlb_trkDz_2011_qual->Sumw2();
  SingleGlb_trkDz_2011_qual->SetMarkerColor(kRed);
  SingleGlb_trkDz_2011_qual->SetMarkerStyle(20);
  SingleGlb_trkDz_2011_qual->SetMarkerSize(marker_size);
	SingleGlb_trkDz_2011_qual->Scale(1.0/SingleGlb_trkDz_2011_qual->GetEntries());
  SingleGlb_trkDz_2011_qual->DrawNormalized("p e sames",1);
	gStyle->SetStatX(1.0);
	entries_2010_qual = SingleGlb_trkDz_2010_qual->GetEntries();
	entries_2011_qual = SingleGlb_trkDz_2011_qual->GetEntries();
	sprintf(count_2010_qual,"  2010_qual Data - %i Muons", entries_2010_qual);
	sprintf(count_2011_qual,"  2011_qual Data - %i Muons", entries_2011_qual);
	leg->Clear();
	leg->AddEntry(SingleGlb_trkDz_2010_qual,count_2010_qual,"lp");
	leg->AddEntry(SingleGlb_trkDz_2011_qual,count_2011_qual,"lp");
  leg->Draw();
	canv->Update();

	pad2->cd();

	ratio_2011_qual = (TH1F*)SingleGlb_trkDz_2011_qual->Clone("ratio_2011_qual");
	ratio_2011_qual->Divide(SingleGlb_trkDz_2010_qual);
	ratio_2011_qual->SetMarkerColor(kViolet);
	ratio_2011_qual->SetMarkerStyle(29);
	ratio_2011_qual->SetMarkerSize(marker_size*5.0/3.0);

	ratio_2011_qual->SetMinimum(0);
	ratio_2011_qual->SetMaximum(ratio_2011_qual->GetMaximum()+0.1);

	gStyle->SetStatX(0.55);
	gStyle->SetStatY(0.6);
	gStyle->SetStatW(0.1);
	gStyle->SetStatH(0.3);
	gStyle->SetOptStat("");

	gStyle->SetMarkerSize(1);
	ratio_2011_qual->GetYaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011_qual->GetYaxis()->SetNdivisions(505);

	ratio_2011_qual->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011_qual->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011_qual->GetXaxis()->SetTitleSize(0.15);
	ratio_2011_qual->GetXaxis()->SetTitle("Track Dz (cm)");
	
	gStyle->SetOptTitle(0);
	gPad->SetLogy(0);
	
	ratio_2011_qual->Draw();
	l3a = new TLine(0,1.0,2,1.0);
	l3a->SetHorizontal(1);
	l3a->SetLineStyle(2);
	l3a->SetX2(2);
	l3a->Draw("same");

	canv->SaveAs("SingleGlb_trkDz_qual.pdf");
	canv->Clear(); canv->Draw();
// END trkDz

// START trkDxy	
	canv = new TCanvas("canv","canv",1300,1000);
	
	pad1 = new TPad("pad1", "The pad 70% of the height",0.0,0.3,1.0,1.0,0);
	pad1->SetBottomMargin(0.0);
	pad2 = new TPad("pad2", "The pad 30% of the height",0.0,0.0,1.0,0.3,0);
	pad2->SetTopMargin(0.0);
	pad2->SetBottomMargin(0.35);



	pad2->SetBottomMargin(0.1);
	pad1->Draw();
	pad2->Draw();

	pad1->cd();
	pad1->SetLogy(1);

	gStyle->SetMarkerSize(1);
	SingleGlb_trkDxy_2010_qual->GetXaxis()->SetLabelSize(label_size);
	SingleGlb_trkDxy_2010_qual->GetYaxis()->SetLabelSize(label_size);
	SingleGlb_trkDxy_2010_qual->SetMinimum(1);
	SingleGlb_trkDxy_2010_qual->Sumw2();
  SingleGlb_trkDxy_2010_qual->SetMarkerStyle(25);
  SingleGlb_trkDxy_2010_qual->SetMarkerSize(marker_size);
	SingleGlb_trkDxy_2010_qual->Scale(1.0/SingleGlb_trkDxy_2010_qual->GetEntries());
  SingleGlb_trkDxy_2010_qual->DrawNormalized("p e",1);
	canv->Update();
	gStyle->SetStatX(0.8);
	gStyle->SetStatY(1.0);
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.2);
	gStyle->SetOptStat("mn");
	canv->Update();
	entries_2010_qual = SingleGlb_trkDxy_2010_qual->GetEntries();
	canv->Update();
  SingleGlb_trkDxy_2011_qual->Sumw2();
  SingleGlb_trkDxy_2011_qual->SetMarkerColor(kRed);
  SingleGlb_trkDxy_2011_qual->SetMarkerStyle(20);
  SingleGlb_trkDxy_2011_qual->SetMarkerStyle(marker_size);
	SingleGlb_trkDxy_2011_qual->Scale(1.0/SingleGlb_trkDxy_2011_qual->GetEntries());
  SingleGlb_trkDxy_2011_qual->DrawNormalized("p e sames",1);
	gStyle->SetStatX(1.0);
	canv->Update();
	entries_2010_qual = SingleGlb_trkDxy_2010_qual->GetEntries();
	entries_2011_qual = SingleGlb_trkDxy_2011_qual->GetEntries();
	sprintf(count_2010_qual,"  2010_qual Data - %i Muons", entries_2010_qual);
	sprintf(count_2011_qual,"  2011_qual Data - %i Muons", entries_2011_qual);
	leg->Clear();
	leg->AddEntry(SingleGlb_trkDxy_2010_qual,count_2010_qual,"lp");
	leg->AddEntry(SingleGlb_trkDxy_2011_qual,count_2011_qual,"lp");
  leg->Draw();
	canv->Update();

	pad2->cd();

	ratio_2011_qual = (TH1F*)SingleGlb_trkDxy_2011_qual->Clone("ratio_2011_qual");
	ratio_2011_qual->Divide(SingleGlb_trkDxy_2010_qual);
	ratio_2011_qual->SetMarkerColor(kViolet);
	ratio_2011_qual->SetMarkerStyle(29);
	ratio_2011_qual->SetMarkerSize(marker_size*5.0/3.0);

	ratio_2011_qual->SetMinimum(0);
	ratio_2011_qual->SetMaximum(ratio_2011_qual->GetMaximum()+0.1);

	gStyle->SetStatX(0.55);
	gStyle->SetStatY(0.6);
	gStyle->SetStatW(0.1);
	gStyle->SetStatH(0.3);
	gStyle->SetOptStat("");

	gStyle->SetMarkerSize(1);
	ratio_2011_qual->GetYaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011_qual->GetYaxis()->SetNdivisions(505);

	ratio_2011_qual->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011_qual->GetXaxis()->SetLabelSize(label_size*8.0/3.0);
	ratio_2011_qual->GetXaxis()->SetTitleSize(0.15);
	ratio_2011_qual->GetXaxis()->SetTitle("Track Dxy (cm)");
	
	gStyle->SetOptTitle(0);
	gPad->SetLogy(0);
	
	ratio_2011_qual->Draw();
	l3a = new TLine(0,1.0,2,1.0);
	l3a->SetHorizontal(1);
	l3a->SetLineStyle(2);
	l3a->SetX2(2);
	l3a->Draw("same");

	canv->SaveAs("SingleGlb_trkDxy_qual.pdf");
	canv->Clear(); canv->Draw();
// END trkDxy


//	gStyle->SetOptStat("mn");
//	gStyle->SetOptTitle(1);

	gStyle->SetPadTopMargin(0.10);
	gStyle->SetPadRightMargin(0.15);
	gStyle->SetPadLeftMargin(0.10);
	gStyle->SetPadBottomMargin(0.1);

	gStyle->SetStatX(1.0);
	gStyle->SetStatY(1.0);
	gStyle->SetStatW(0.3);
	gStyle->SetStatH(0.2);
	gStyle->SetOptStat("em");
	canv->Update();
	
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
  SingleGlb_Etaphi_2010_qual->DrawNormalized("colz",1);
	canv->cd(9);
  title.str("");
	title << "2010 # muons: " << SingleGlb_Eta_2010_qual->GetEntries();
  lax->DrawLatex(0.0,0.90,title.str().c_str());
  title.str("");
  title << "2010 # events: " << nevt_2010_qual;
  lax->DrawLatex(0.0,0.8,title.str().c_str());

	canv->SaveAs("SingleGlb_2d_distributions_phi_2010_qual.pdf");
	
  canv->Clear(); 

	canv = new TCanvas("canv","canv",1300,1000);
  canv->Divide(3,3);
	
  canv->cd(1);
  SingleGlb_nValMuHits_pt_2010_qual->DrawNormalized("colz",1);
	canv->cd(2);
  SingleGlb_nValTrkHits_pt_2010_qual->DrawNormalized("colz",1);
	canv->cd(3);
  SingleGlb_glbChi2_ndof_pt_2010_qual->DrawNormalized("colz",1);
	canv->cd(4);
  SingleGlb_trkChi2_ndof_pt_2010_qual->DrawNormalized("colz",1);
	canv->cd(5);
  SingleGlb_pixLayerWMeas_pt_2010_qual->DrawNormalized("colz",1);
	canv->cd(6);
  SingleGlb_trkDz_pt_2010_qual->DrawNormalized("colz",1);
	canv->cd(7);
  SingleGlb_trkDxy_pt_2010_qual->DrawNormalized("colz",1);
	canv->cd(8);
  SingleGlb_Etapt_2010_qual->DrawNormalized("colz",1);
	canv->cd(9);
  title.str("");
	title << "2010 # muons: " << SingleGlb_Eta_2010_qual->GetEntries();
  lax->DrawLatex(0.0,0.90,title.str().c_str());
  title.str("");
  title << "2010 # events: " << nevt_2010_qual;
  lax->DrawLatex(0.0,0.8,title.str().c_str());

	canv->SaveAs("SingleGlb_2d_distributions_pt_2010_qual.pdf");
	
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
  SingleGlb_Etapt_2010_qual->DrawNormalized("colz",1);
	canv->cd(9);
  title.str("");
	title << "2010 # muons: " << SingleGlb_Eta_2010_qual->GetEntries();
  lax->DrawLatex(0.0,0.90,title.str().c_str());
  title.str("");
  title << "2010 # events: " << nevt_2010_qual;
  lax->DrawLatex(0.0,0.8,title.str().c_str());

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
  SingleGlb_Etaphi_2010->DrawNormalized("colz",1);
	canv->cd(9);
  title.str("");
	title << "2010 # muons: " << SingleGlb_Eta_2010->GetEntries();
  lax->DrawLatex(0.0,0.90,title.str().c_str());
  title.str("");
  title << "2010 # events: " << nevt_2010;
  lax->DrawLatex(0.0,0.8,title.str().c_str());

	canv->SaveAs("SingleGlb_2d_distributions_phi_2010.pdf");
	
  canv->Clear(); 

	canv = new TCanvas("canv","canv",1300,1000);
  canv->Divide(3,3);
	
  canv->cd(1);
  SingleGlb_nValMuHits_pt_2010->DrawNormalized("colz",1);
	canv->cd(2);
  SingleGlb_nValTrkHits_pt_2010->DrawNormalized("colz",1);
	canv->cd(3);
  SingleGlb_glbChi2_ndof_pt_2010->DrawNormalized("colz",1);
	canv->cd(4);
  SingleGlb_trkChi2_ndof_pt_2010->DrawNormalized("colz",1);
	canv->cd(5);
  SingleGlb_pixLayerWMeas_pt_2010->DrawNormalized("colz",1);
	canv->cd(6);
  SingleGlb_trkDz_pt_2010->DrawNormalized("colz",1);
	canv->cd(7);
  SingleGlb_trkDxy_pt_2010->DrawNormalized("colz",1);
	canv->cd(8);
  SingleGlb_Etapt_2010->DrawNormalized("colz",1);
	canv->cd(9);
  title.str("");
	title << "2010 # muons: " << SingleGlb_Eta_2010->GetEntries();
  lax->DrawLatex(0.0,0.90,title.str().c_str());
  title.str("");
  title << "2010 # events: " << nevt_2010;
  lax->DrawLatex(0.0,0.8,title.str().c_str());

	canv->SaveAs("SingleGlb_2d_distributions_pt_2010.pdf");
	
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
  SingleGlb_Etapt_2010->DrawNormalized("colz",1);
	canv->cd(9);
  title.str("");
	title << "2010 # muons: " << SingleGlb_Eta_2010->GetEntries();
  lax->DrawLatex(0.0,0.90,title.str().c_str());
  title.str("");
  title << "2010 # events: " << nevt_2010;
  lax->DrawLatex(0.0,0.8,title.str().c_str());

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
  SingleGlb_Etaphi_2011_qual->DrawNormalized("colz",1);
	canv->cd(9);
  title.str("");
	title << "2011 # muons: " << SingleGlb_Eta_2011_qual->GetEntries();
  lax->DrawLatex(0.0,0.90,title.str().c_str());
  title.str("");
  title << "2011 # events: " << nevt_2011_qual;
  lax->DrawLatex(0.0,0.8,title.str().c_str());

	canv->SaveAs("SingleGlb_2d_distributions_phi_2011_qual.pdf");
	
  canv->Clear(); 

	canv = new TCanvas("canv","canv",1300,1000);
  canv->Divide(3,3);
	
  canv->cd(1);
  SingleGlb_nValMuHits_pt_2011_qual->DrawNormalized("colz",1);
	canv->cd(2);
  SingleGlb_nValTrkHits_pt_2011_qual->DrawNormalized("colz",1);
	canv->cd(3);
  SingleGlb_glbChi2_ndof_pt_2011_qual->DrawNormalized("colz",1);
	canv->cd(4);
  SingleGlb_trkChi2_ndof_pt_2011_qual->DrawNormalized("colz",1);
	canv->cd(5);
  SingleGlb_pixLayerWMeas_pt_2011_qual->DrawNormalized("colz",1);
	canv->cd(6);
  SingleGlb_trkDz_pt_2011_qual->DrawNormalized("colz",1);
	canv->cd(7);
  SingleGlb_trkDxy_pt_2011_qual->DrawNormalized("colz",1);
	canv->cd(8);
  SingleGlb_Etapt_2011_qual->DrawNormalized("colz",1);
	canv->cd(9);
  title.str("");
	title << "2011 # muons: " << SingleGlb_Eta_2011_qual->GetEntries();
  lax->DrawLatex(0.0,0.90,title.str().c_str());
  title.str("");
  title << "2011 # events: " << nevt_2011_qual;
  lax->DrawLatex(0.0,0.8,title.str().c_str());

	canv->SaveAs("SingleGlb_2d_distributions_pt_2011_qual.pdf");
	
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
  SingleGlb_Etapt_2011_qual->DrawNormalized("colz",1);
	canv->cd(9);
  title.str("");
	title << "2011 # muons: " << SingleGlb_Eta_2011_qual->GetEntries();
  lax->DrawLatex(0.0,0.90,title.str().c_str());
  title.str("");
  title << "2011 # events: " << nevt_2011_qual;
  lax->DrawLatex(0.0,0.8,title.str().c_str());

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
  SingleGlb_Etapt_2011->DrawNormalized("colz",1);
	canv->cd(9);
  title.str("");
	title << "2011 # muons: " << SingleGlb_Eta_2011->GetEntries();
  lax->DrawLatex(0.0,0.90,title.str().c_str());
  title.str("");
  title << "2011 # events: " << nevt_2011;
  lax->DrawLatex(0.0,0.8,title.str().c_str());

	canv->SaveAs("SingleGlb_2d_distributions_phi_2011.pdf");
	
  canv->Clear(); 

	canv = new TCanvas("canv","canv",1300,1000);
  canv->Divide(3,3);
	
  canv->cd(1);
  SingleGlb_nValMuHits_pt_2011->DrawNormalized("colz",1);
	canv->cd(2);
  SingleGlb_nValTrkHits_pt_2011->DrawNormalized("colz",1);
	canv->cd(3);
  SingleGlb_glbChi2_ndof_pt_2011->DrawNormalized("colz",1);
	canv->cd(4);
  SingleGlb_trkChi2_ndof_pt_2011->DrawNormalized("colz",1);
	canv->cd(5);
  SingleGlb_pixLayerWMeas_pt_2011->DrawNormalized("colz",1);
	canv->cd(6);
  SingleGlb_trkDz_pt_2011->DrawNormalized("colz",1);
	canv->cd(7);
  SingleGlb_trkDxy_pt_2011->DrawNormalized("colz",1);
	canv->cd(8);
  SingleGlb_Etapt_2011->DrawNormalized("colz",1);
	canv->cd(9);
  title.str("");
	title << "2011 # muons: " << SingleGlb_Eta_2011->GetEntries();
  lax->DrawLatex(0.0,0.90,title.str().c_str());
  title.str("");
  title << "2011 # events: " << nevt_2011;
  lax->DrawLatex(0.0,0.8,title.str().c_str());

	canv->SaveAs("SingleGlb_2d_distributions_pt_2011.pdf");
	
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
  SingleGlb_Etapt_2011->DrawNormalized("colz",1);
	canv->cd(9);
  title.str("");
	title << "2011 # muons: " << SingleGlb_Eta_2011->GetEntries();
  lax->DrawLatex(0.0,0.90,title.str().c_str());
  title.str("");
  title << "2011 # events: " << nevt_2011;
  lax->DrawLatex(0.0,0.8,title.str().c_str());

	canv->SaveAs("SingleGlb_2d_distributions_eta_2011.pdf");

  canv->Clear(); 
  
  return 0;
}
