#include <iostream>
#include <sstream>
#include <istream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <functional>
#include <stdlib.h>
#include <string.h>

#include "HLTrigger/HLTanalyzers/interface/HLTrigInfo.h"
#include "FWCore/Common/interface/TriggerNames.h"

// L1 related
#include "L1Trigger/GlobalTriggerAnalyzer/interface/L1GtUtils.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"


HLTrigInfo::HLTrigInfo() {

  //set parameter defaults 
  _Debug=false;
  _OR_BXes=false;
  UnpackBxInEvent=1;
}

void HLTrigInfo::beginRun(const edm::Run& run, const edm::EventSetup& c){ 


  bool changed(true);
  if (hltConfig_.init(run,c,processName_,changed)) {
    // if init returns TRUE, initialisation has succeeded!
    if (changed) {
      // The HLT config has actually changed wrt the previous Run, hence rebook your
      // histograms or do anything else dependent on the revised HLT config
      std::cout << "Initalizing HLTConfigProvider"  << std::endl;
    }
  } else {
    // if init returns FALSE, initialisation has NOT succeeded, which indicates a problem
    // with the file and/or code and needs to be investigated!
    std::cout << " HLT config extraction failure with process name " << processName_ << std::endl;
    // In this case, all access methods will return empty values!
  }

}

/*  Setup the analysis to put the branch-variables into the tree. */
void HLTrigInfo::setup(const edm::ParameterSet& pSet, TTree* HltTree) {


  processName_ = pSet.getParameter<std::string>("HLTProcessName") ;

  edm::ParameterSet myHltParams = pSet.getParameter<edm::ParameterSet>("RunParameters") ;
  std::vector<std::string> parameterNames = myHltParams.getParameterNames() ;
  
  for ( std::vector<std::string>::iterator iParam = parameterNames.begin();
        iParam != parameterNames.end(); iParam++ ){
    if ( (*iParam) == "Debug" ) _Debug =  myHltParams.getParameter<bool>( *iParam );
  }

  HltEvtCnt = 0;
  const int kMaxTrigFlag = 10000;
  trigflag = new int[kMaxTrigFlag];
  trigPrescl = new int[kMaxTrigFlag];
  L1EvtCnt = 0;
  const int kMaxL1Flag = 10000;
  l1flag = new int[kMaxL1Flag];
  l1flag5Bx = new int[kMaxTrigFlag];
  l1Prescl = new int[kMaxL1Flag];
  l1techflag = new int[kMaxL1Flag];
  l1techflag5Bx = new int[kMaxTrigFlag];
  l1techPrescl = new int[kMaxTrigFlag];
  const int kMaxHLTPart = 10000;
  hltppt = new float[kMaxHLTPart];
  hltpeta = new float[kMaxHLTPart];

  algoBitToName = new TString[128];
  techBitToName = new TString[128];

}

/* **Analyze the event** */
void HLTrigInfo::analyze(const edm::Handle<edm::TriggerResults>                 & hltresults,
//          const edm::Handle<L1GlobalTriggerReadoutRecord>        & L1GTRR,
		      edm::EventSetup const& eventSetup,
		      edm::Event const& iEvent,
                      TTree* HltTree) {

//   std::cout << " Beginning HLTrigInfo " << std::endl;


  /////////// Analyzing HLT Trigger Results (TriggerResults) //////////
  if (hltresults.isValid()) {
    int ntrigs = hltresults->size();
    if (ntrigs==0){std::cout << "%HLTrigInfo -- No trigger name given in TriggerResults of the input " << std::endl;}

    edm::TriggerNames const& triggerNames = iEvent.triggerNames(*hltresults);

    // 1st event : Book as many branches as trigger paths provided in the input...
    if (HltEvtCnt==0){
      for (int itrig = 0; itrig != ntrigs; ++itrig) {
        TString trigName = triggerNames.triggerName(itrig);
        HltTree->Branch(trigName,trigflag+itrig,trigName+"/I");
        HltTree->Branch(trigName+"_Prescl",trigPrescl+itrig,trigName+"_Prescl/I");
      }
      HltEvtCnt++;
    }
    // ...Fill the corresponding accepts in branch-variables

    //std::cout << "Number of prescale sets: " << hltConfig_.prescaleSize() << std::endl;
    //std::cout << "Number of HLT paths: " << hltConfig_.size() << std::endl;
    //int presclSet = hltConfig_.prescaleSet(iEvent, eventSetup);
    //std::cout<<"\tPrescale set number: "<< presclSet <<std::endl; 

    for (int itrig = 0; itrig != ntrigs; ++itrig){

      std::string trigName=triggerNames.triggerName(itrig);
      bool accept = hltresults->accept(itrig);

      trigPrescl[itrig] = hltConfig_.prescaleValue(iEvent, eventSetup, trigName);


      if (accept){trigflag[itrig] = 1;}
      else {trigflag[itrig] = 0;}

      if (_Debug){
        if (_Debug) std::cout << "%HLTrigInfo --  Number of HLT Triggers: " << ntrigs << std::endl;
        std::cout << "%HLTrigInfo --  HLTTrigger(" << itrig << "): " << trigName << " = " << accept << std::endl;
      }
    }
  }
  else { if (_Debug) std::cout << "%HLTrigInfo -- No Trigger Result" << std::endl;}

  //==============L1 information=======================================

  // L1 Triggers from Menu
  /*
  m_l1GtUtils.retrieveL1EventSetup(eventSetup);
  edm::ESHandle<L1GtTriggerMenu> menuRcd;
  eventSetup.get<L1GtTriggerMenuRcd>().get(menuRcd) ;
  const L1GtTriggerMenu* menu = menuRcd.product();

  int iErrorCode = -1;
  L1GtUtils::TriggerCategory trigCategory = L1GtUtils::AlgorithmTrigger;
  const int pfSetIndexAlgorithmTrigger = m_l1GtUtils.prescaleFactorSetIndex(
             iEvent, trigCategory, iErrorCode);
  if (iErrorCode == 0) {
    if (_Debug) std::cout << "%Prescale set index: " << pfSetIndexAlgorithmTrigger  << std::endl;
  }else{
    std::cout << "%Could not extract Prescale set index from event record. Error code: " << iErrorCode << std::endl;
  }

  // 1st event : Book as many branches as trigger paths provided in the input...
  if (L1GTRR.isValid()) {  

    DecisionWord gtDecisionWord = L1GTRR->decisionWord();
    const unsigned int numberTriggerBits(gtDecisionWord.size());
    const TechnicalTriggerWord&  technicalTriggerWordBeforeMask = L1GTRR->technicalTriggerWord();
    const unsigned int numberTechnicalTriggerBits(technicalTriggerWordBeforeMask.size());

    // 1st event : Book as many branches as trigger paths provided in the input...
    if (L1EvtCnt==0){

 
      //ccla determine if more than 1 bx was unpacked in event; add OR all bx's if so
      const edm::Provenance& prov = iEvent.getProvenance(L1GTRR.id());
      //const string& procName = prov.processName();
      edm::ParameterSetID setId = prov.psetID();
      //std::cout << "procName:" << procName << std::endl;
      //std::cout << "provinfo:" << prov << std::endl;
      //std::cout << "setid:" << setId << std::endl;
      edm::ParameterSet pSet=getParameterSet(setId);
      //std::cout << "pset:" << pSet << std::endl;
      if (pSet.exists("UnpackBxInEvent")){
	UnpackBxInEvent = pSet.getParameter<int>("UnpackBxInEvent");
      }
      if (_Debug) std::cout << "Number of beam crossings unpacked by GT: " << UnpackBxInEvent << std::endl;
      if (UnpackBxInEvent == 5) _OR_BXes = true;

      // get L1 menu from event setup
      for (CItAlgo algo = menu->gtAlgorithmMap().begin(); algo!=menu->gtAlgorithmMap().end(); ++algo) {
	if (_Debug) std::cout << "Name: " << (algo->second).algoName() << " Alias: " << (algo->second).algoAlias() << std::endl;
        int itrig = (algo->second).algoBitNumber();
        algoBitToName[itrig] = TString( (algo->second).algoName() );
        HltTree->Branch(algoBitToName[itrig],l1flag+itrig,algoBitToName[itrig]+"/I");
        HltTree->Branch(algoBitToName[itrig]+"_Prescl",l1Prescl+itrig,algoBitToName[itrig]+"_Prescl/I");
	if (_OR_BXes)
	  HltTree->Branch(algoBitToName[itrig]+"_5bx",l1flag5Bx+itrig,algoBitToName[itrig]+"_5bx/I");
      }

      // Book branches for tech bits
      for (CItAlgo techTrig = menu->gtTechnicalTriggerMap().begin(); techTrig != menu->gtTechnicalTriggerMap().end(); ++techTrig) {
        int itrig = (techTrig->second).algoBitNumber();
	techBitToName[itrig] = TString( (techTrig->second).algoName() );
	if (_Debug) std::cout << "tech bit " << itrig << ": " << techBitToName[itrig] << " " << std::endl;
	HltTree->Branch(techBitToName[itrig],l1techflag+itrig,techBitToName[itrig]+"/I");
        HltTree->Branch(techBitToName[itrig]+"_Prescl",l1techPrescl+itrig,techBitToName[itrig]+"_Prescl/I");
	if (_OR_BXes)
	  HltTree->Branch(techBitToName[itrig]+"_5bx",l1techflag5Bx+itrig,techBitToName[itrig]+"_5bx/I");
      }
    }

    std::string triggerAlgTechTrig = "PhysicsAlgorithms";
    for (unsigned int iBit = 0; iBit < numberTriggerBits; ++iBit) {     
      // ...Fill the corresponding accepts in branch-variables
      l1flag[iBit] = gtDecisionWord[iBit];

      std::string l1triggername= std::string (algoBitToName[iBit]);
      l1Prescl[iBit] = m_l1GtUtils.prescaleFactor(iEvent, 
					       l1triggername,
					       iErrorCode);
      
      if (_Debug) std::cout << "L1 TD: "<<iBit<<" "<<algoBitToName[iBit]<<" "
			    << gtDecisionWord[iBit]<<" "
			    << l1Prescl[iBit] << std::endl;

    }

    triggerAlgTechTrig = "TechnicalTriggers";
    for (unsigned int iBit = 0; iBit < numberTechnicalTriggerBits; ++iBit) {
      l1techflag[iBit] = (int) technicalTriggerWordBeforeMask.at(iBit);

      std::string l1triggername= std::string (techBitToName[iBit]);
      l1techPrescl[iBit] = m_l1GtUtils.prescaleFactor(iEvent, 
					       l1triggername,
					       iErrorCode);

      if (_Debug) std::cout << "L1 TD: "<<iBit<<" "<<techBitToName[iBit]<<" "
			    << l1techflag[iBit]<<" "
			    << l1Prescl[iBit] << std::endl;

    }

    if (_OR_BXes){
      // look at all 5 bx window in case gt timing is off
      // get Field Decision Logic
      std::vector<DecisionWord> m_gtDecisionWord5Bx;
      std::vector<TechnicalTriggerWord> m_gtTechDecisionWord5Bx;
      std::vector<int> m_ibxn;

      const std::vector<L1GtFdlWord> &m_gtFdlWord(L1GTRR->gtFdlVector());
      for (std::vector<L1GtFdlWord>::const_iterator itBx = m_gtFdlWord.begin();
	   itBx != m_gtFdlWord.end(); ++itBx) {
	if (_Debug && L1EvtCnt==0) std::cout << "bx: " << (*itBx).bxInEvent() << " ";
	m_gtDecisionWord5Bx.push_back((*itBx).gtDecisionWord());
	m_gtTechDecisionWord5Bx.push_back((*itBx).gtTechnicalTriggerWord());
      }
      // --- Fill algo bits ---
      for (unsigned int iBit = 0; iBit < numberTriggerBits; ++iBit) {     
	// ...Fill the corresponding accepts in branch-variables
	if (_Debug) std::cout << std::endl << " L1 TD: "<<iBit<<" "<<algoBitToName[iBit]<<" ";
	int result=0;
	int bitword=0; 
	for (unsigned int jbx=0; jbx<m_gtDecisionWord5Bx.size(); ++jbx) {
	  if (_Debug) std::cout << m_gtDecisionWord5Bx[jbx][iBit]<< " ";
	  result += m_gtDecisionWord5Bx[jbx][iBit];
	  if (m_gtDecisionWord5Bx[jbx][iBit]>0) bitword |= 1 << jbx;
	}
	if (_Debug && result>1) {std::cout << "5BxOr=" << result << "  Bitword= "<< bitword <<std::endl;
	  std::cout << "Unpacking: " ;
	  for (int i = 0; i<UnpackBxInEvent ; ++i){
	    bool bitOn=bitword & (1 << i);
	    std::cout << bitOn << " ";
	  }
	  std::cout << "\n";
	}
	l1flag5Bx[iBit] = bitword;
      }
      // --- Fill tech bits ---
      for (unsigned int iBit = 0; iBit < m_gtTechDecisionWord5Bx[2].size(); ++iBit) {     
	// ...Fill the corresponding accepts in branch-variables
	if (_Debug) std::cout << std::endl << " L1 TD: "<<iBit<<" "<<techBitToName[iBit]<<" ";
	int result=0;
	int bitword=0;       
	for (unsigned int jbx=0; jbx<m_gtTechDecisionWord5Bx.size(); ++jbx) {
	  if (_Debug) std::cout << m_gtTechDecisionWord5Bx[jbx][iBit]<< " ";
	  result += m_gtTechDecisionWord5Bx[jbx][iBit];
	  if (m_gtTechDecisionWord5Bx[jbx][iBit]>0) bitword |= 1 << jbx;
	}
	if (_Debug && result>1) {std::cout << "5BxOr=" << result << "  Bitword= "<< bitword  << std::endl;
	  std::cout << "Unpacking: " ;
	  for (int i = 0; i<UnpackBxInEvent ; ++i){
	    bool bitOn=bitword & (1 << i);
	    std::cout << bitOn << " ";
	  }
	  std::cout << "\n";
	}
	l1techflag5Bx[iBit] = bitword;
      }
    } // end of OR_BX

    L1EvtCnt++;
  }
  else {
    if (_Debug) std::cout << "%HLTrigInfo -- No L1 GT ReadoutRecord " << std::endl;
  }
  */

  if (_Debug) std::cout << "%HLTrigInfo -- Done with routine" << std::endl;
}
