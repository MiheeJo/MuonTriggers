// system include files
#include <memory>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "HepMC/GenEvent.h"
#include "HepMC/GenParticle.h"
#include "HepMC/GenVertex.h"
#include "HepMC/HeavyIon.h"

// data formats
#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/Common/interface/RefToBase.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/MuonTrackLinks.h"
#include "DataFormats/RecoCandidate/interface/TrackAssociation.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include "DataFormats/HeavyIonEvent/interface/CentralityProvider.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticleFwd.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidate.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidateFwd.h"
#include "DataFormats/L1Trigger/interface/L1MuonParticle.h" 
#include "DataFormats/L1Trigger/interface/L1MuonParticleFwd.h" 
#include "TrackingTools/PatternTools/interface/ClosestApproachInRPhi.h"



// root include files
#include "TROOT.h"
#include "TTree.h"
#include "TLorentzVector.h"

//
// class declaration
//

using namespace std;
using namespace reco;
using namespace edm;


class HLTMuTree : public edm::EDAnalyzer {
  public:
    explicit HLTMuTree(const edm::ParameterSet&);
    ~HLTMuTree();


  private:
    virtual void beginJob() ;
    virtual void analyze(const edm::Event&, const edm::EventSetup&);
    virtual void endJob() ;

  // ----------member data ---------------------------
    edm::InputTag   tagRecoMu;
    edm::InputTag   tagGenPtl;
    edm::InputTag   tagSimTrk;
    edm::InputTag   tagVtx;
    edm::InputTag   MuCandTag1;
    edm::InputTag   MuCandTag2;
    edm::InputTag   MuCandTag3;

    Bool_t    doReco;
    Bool_t    doGen;
    Bool_t    doHLT;

    CentralityProvider *centrality;

    TTree     *treeMu;
    edm::Service<TFileService>     foutput;

    int run, event, lumi, cbin;
    float vx, vy, vz;
    
    static const int nmax = 1000000;
    typedef struct {
      int nptl;
      int pid[nmax];
      int status[nmax];
      int mom[nmax];
      float pt[nmax];
      float p[nmax];
      float eta[nmax];
      float phi[nmax];
    } GENMU;

    typedef struct {
      int nptl;
      int charge[nmax];
      float pt[nmax];
      float p[nmax];
      float eta[nmax];
      float phi[nmax];
      float dxy[nmax];
      float dz[nmax];
      int nValMuHits[nmax];
      int nValTrkHits[nmax];
      int nTrkFound[nmax];
      float glbChi2_ndof[nmax];
      float trkChi2_ndof[nmax];
      int pixLayerWMeas[nmax];
      float trkDxy[nmax];
      float trkDz[nmax];
    } GLBMU;

    typedef struct {
      int nptl;
      int charge[nmax];
      float pt[nmax];
      float p[nmax];
      float eta[nmax];
      float phi[nmax];
      float dxy[nmax];
      float dz[nmax];
    } STAMU;

    GENMU GenMu;
    GLBMU GlbMu;
    STAMU StaMu;

    float muonl2pt[nmax], muonl2eta[nmax], muonl2phi[nmax], muonl2dr[nmax], muonl2dz[nmax], muonl2vtxz[nmax];
    float muonl3pt[nmax], muonl3eta[nmax], muonl3phi[nmax], muonl3dr[nmax], muonl3dz[nmax], muonl3vtxz[nmax], muonl3normchi2[nmax];
    float muonl2pterr[nmax], muonl3pterr[nmax];
    int nmu2cand, nmu3cand;
    int muonl2chg[nmax], muonl2nhits[nmax], muonl3chg[nmax], muonl3nhits[nmax];
    int muonl3ntrackerhits[nmax], muonl3nmuonhits[nmax];


};
//
// constants, enums and typedefs 
//
