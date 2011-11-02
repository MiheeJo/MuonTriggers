// File: HLTrigAnalyzer.cc
// Description:  Example of Analysis driver originally from Jeremy Mans, 
// Date:  13-October-2006

#include <boost/foreach.hpp>

#include "HLTrigger/HLTanalyzers/interface/HLTrigAnalyzer.h"
#include "HLTMessages.h"

typedef std::pair<const char *, const edm::InputTag *> MissingCollectionInfo;
  
template <class T>
static inline
bool getCollection(const edm::Event & event, std::vector<MissingCollectionInfo> & missing, edm::Handle<T> & handle, const edm::InputTag & name, const char * description) 
{
  event.getByLabel(name, handle);
  bool valid = handle.isValid();
  if (not valid) {
    missing.push_back( std::make_pair(description, & name) );
    handle.clear();
  }
  return valid;
}

// Boiler-plate constructor definition of an analyzer module:
HLTrigAnalyzer::HLTrigAnalyzer(edm::ParameterSet const& conf) {

  // If your module takes parameters, here is where you would define
  // their names and types, and access them to initialize internal
  // variables. Example as follows:
  std::cout << " Beginning HLTrigAnalyzer Analysis " << std::endl;

  // read the L1Extra collection name, and add the instance names as needed

  hltresults_       = conf.getParameter<edm::InputTag> ("hltresults");
  gtReadoutRecord_  = conf.getParameter<edm::InputTag> ("l1GtReadoutRecord");

  m_file = 0;   // set to null
  errCnt = 0;

  // read run parameters with a default value
  edm::ParameterSet runParameters = conf.getParameter<edm::ParameterSet>("RunParameters");
  _HistName = runParameters.getUntrackedParameter<std::string>("HistogramFile", "test.root");

  // open the tree file
  m_file = new TFile(_HistName.c_str(), "RECREATE");
  if (m_file)
    m_file->cd();

  // Initialize the tree
  HltTree = new TTree("HltTree", "");

  // Setup the different analysis
  hlt_analysis_.setup(conf, HltTree);
  evt_header_.setup(HltTree);
}

// Boiler-plate "analyze" method declaration for an analyzer module.
void HLTrigAnalyzer::analyze(edm::Event const& iEvent, edm::EventSetup const& iSetup) {

  edm::Handle<edm::TriggerResults>                  hltresults;
//  edm::Handle<L1GlobalTriggerReadoutRecord>         l1GtRR;

  // extract the collections from the event, check their validity and log which are missing
  std::vector<MissingCollectionInfo> missing;

  getCollection( iEvent, missing, hltresults,      hltresults_,        kHltresults );
//  getCollection( iEvent, missing, l1GtRR,          gtReadoutRecord_,   kL1GtRR );


  // print missing collections
  if (not missing.empty() and (errCnt < errMax())) {
    errCnt++;
    std::stringstream out;       
    out <<  "OpenHLT analyser - missing collections:";
    BOOST_FOREACH(const MissingCollectionInfo & entry, missing)
      out << "\n\t" << entry.first << ": " << entry.second->encode();
    edm::LogPrint("OpenHLT") << out.str() << std::endl; 
    if (errCnt == errMax())
      edm::LogWarning("OpenHLT") << "Maximum error count reached -- No more messages will be printed.";
  }

  // run the analysis, passing required event fragments
  hlt_analysis_.analyze(
    hltresults,
//    l1GtRR,
    iSetup,
    iEvent,
    HltTree);

  evt_header_.analyze(iEvent, HltTree);

  // std::cout << " Ending Event Analysis" << std::endl;
  // After analysis, fill the variables tree
  if (m_file)
    m_file->cd();
  HltTree->Fill();
}

// "endJob" is an inherited method that you may implement to do post-EOF processing and produce final output.
void HLTrigAnalyzer::endJob() {

  if (m_file)
    m_file->cd();
  
  HltTree->Write();
  delete HltTree;
  HltTree = 0;

  if (m_file) {         // if there was a tree file...
    m_file->Write();    // write out the branches
    delete m_file;      // close and delete the file
    m_file = 0;         // set to zero to clean up
  }

}
