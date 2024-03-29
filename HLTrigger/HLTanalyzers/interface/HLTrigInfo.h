#ifndef HLTRIGINFO_H
#define HLTRIGINFO_H

#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TNamed.h"
#include <vector>
#include <map>
#include "TROOT.h"
#include "TChain.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/L1Trigger/interface/L1EmParticle.h"
#include "DataFormats/L1Trigger/interface/L1EmParticleFwd.h"
#include "DataFormats/L1Trigger/interface/L1MuonParticle.h"
#include "DataFormats/L1Trigger/interface/L1MuonParticleFwd.h"
#include "DataFormats/L1Trigger/interface/L1JetParticle.h"
#include "DataFormats/L1Trigger/interface/L1JetParticleFwd.h"
#include "DataFormats/L1Trigger/interface/L1EtMissParticle.h"
#include "DataFormats/L1Trigger/interface/L1EtMissParticleFwd.h"
# include "DataFormats/L1GlobalCaloTrigger/interface/L1GctHFRingEtSums.h"
# include "DataFormats/L1GlobalCaloTrigger/interface/L1GctHFBitCounts.h"
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTExtendedCand.h"
#include "DataFormats/Candidate/interface/Candidate.h"

#include "L1Trigger/RegionalCaloTrigger/interface/L1RCTProducer.h" 

#include "DataFormats/L1CaloTrigger/interface/L1CaloCollections.h"
#include "DataFormats/EcalDigi/interface/EcalDigiCollections.h"
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"

//ccla
#include "FWCore/Framework/interface/EventPrincipal.h"
#include "DataFormats/Provenance/interface/Provenance.h"

/* #include "CalibFormats/CaloTPG/interface/CaloTPGTranscoder.h" */
/* #include "CalibFormats/CaloTPG/interface/CaloTPGRecord.h" */
/* #include "CondFormats/L1TObjects/interface/L1CaloEtScale.h" */
/* #include "CondFormats/DataRecord/interface/L1EmEtScaleRcd.h" */
/* #include "CondFormats/L1TObjects/interface/L1RCTParameters.h" */
/* #include "CondFormats/DataRecord/interface/L1RCTParametersRcd.h" */
/* #include "L1Trigger/RegionalCaloTrigger/interface/L1RCT.h" */
/* #include "L1Trigger/RegionalCaloTrigger/interface/L1RCTLookupTables.h"  */

#include "HLTrigger/HLTanalyzers/interface/JetUtil.h"
#include "DataFormats/METReco/interface/CaloMETCollection.h"

// #include "DataFormats/L1Trigger/interface/L1ParticleMap.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMap.h"
//#include "DataFormats/L1GlobalTrigger/interface/L1GtLogicParser.h"

#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "L1Trigger/GlobalTriggerAnalyzer/interface/L1GtUtils.h"

typedef std::vector<std::string> MyStrings;

/** \class HLTrigInfo
  *  
  * $Date: November 2006
  * $Revision: 
  * \author P. Bargassa - Rice U.
  */
class HLTrigInfo {
public:
  HLTrigInfo(); 

  void setup(const edm::ParameterSet& pSet, TTree* tree);
  void beginRun(const edm::Run& , const edm::EventSetup& );

  /** Analyze the Data */
  void analyze(const edm::Handle<edm::TriggerResults>                 & hltresults,
//	       const edm::Handle<L1GlobalTriggerReadoutRecord>        & l1GTRR,
	       edm::EventSetup const& eventSetup,
	       edm::Event const& iEvent,
	       TTree* tree);

private:

  // Tree variables
  float *hltppt, *hltpeta;
  float *l1extiemet, *l1extieme, *l1extiemeta, *l1extiemphi;
  float *l1extnemet, *l1extneme, *l1extnemeta, *l1extnemphi;
  float *l1extmupt, *l1extmue, *l1extmueta, *l1extmuphi;
  int *l1extmuchg;
  float *l1extjtcet, *l1extjtce, *l1extjtceta, *l1extjtcphi;
  float *l1extjtfet, *l1extjtfe, *l1extjtfeta, *l1extjtfphi;
  float *l1exttauet, *l1exttaue, *l1exttaueta, *l1exttauphi;
  float met, metphi, ettot;
  float mht, mhtphi, ethad;
  int L1EvtCnt,HltEvtCnt,nhltpart,nl1extiem,nl1extnem,nl1extmu,nl1extjetc,nl1extjetf,nl1extjt,nl1exttau;
  int *trigflag, *l1flag, *l1flag5Bx, *l1techflag, *l1techflag5Bx, *l1extmuiso, *l1extmumip, *l1extmufor, *l1extmurpc, *l1extmuqul;
  int *trigPrescl, *l1Prescl, *l1techPrescl; 
  int l1hfRing1EtSumNegativeEta,l1hfRing2EtSumNegativeEta;
  int l1hfRing1EtSumPositiveEta,l1hfRing2EtSumPositiveEta;
  int l1hfTowerCountPositiveEtaRing1,l1hfTowerCountNegativeEtaRing1;
  int l1hfTowerCountPositiveEtaRing2,l1hfTowerCountNegativeEtaRing2;

  TString * algoBitToName;
  TString * techBitToName;


  HLTConfigProvider hltConfig_; 
  L1GtUtils m_l1GtUtils;
  std::string processName_;

  bool _OR_BXes;
  int UnpackBxInEvent; // save number of BXs unpacked in event

  // input variables
  bool _Debug;
};

#endif
