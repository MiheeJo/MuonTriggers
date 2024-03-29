#ifndef HLTMUON_H
#define HLTMUON_H

#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TNamed.h"
#include <vector>
#include <map>
#include "TROOT.h"
#include "TChain.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidate.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidateFwd.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositFwd.h"
//#include "DataFormats/MuonReco/interface/MuonTrackLinks.h"
#include "DataFormats/MuonSeed/interface/L3MuonTrajectorySeed.h"
#include "DataFormats/MuonSeed/interface/L3MuonTrajectorySeedCollection.h"
#include "DataFormats/MuonSeed/interface/L2MuonTrajectorySeed.h" 
#include "DataFormats/MuonSeed/interface/L2MuonTrajectorySeedCollection.h" 
#include "DataFormats/L1Trigger/interface/L1MuonParticle.h" 
#include "DataFormats/L1Trigger/interface/L1MuonParticleFwd.h" 
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "HLTrigger/HLTanalyzers/interface/JetUtil.h"
#include "HLTrigger/HLTanalyzers/interface/CaloTowerBoundries.h"

#include "DataFormats/METReco/interface/CaloMETCollection.h"

#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/Math/interface/Point3D.h"

#include "TrackingTools/PatternTools/interface/ClosestApproachInRPhi.h"
#include "DataFormats/Common/interface/RefToBase.h"
#include "DataFormats/Math/interface/Error.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "MagneticField/Engine/interface/MagneticField.h"

#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "DataFormats/GeometryCommonDetAlgo/interface/GlobalError.h"
#include "TMath.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"


typedef std::vector<std::string> MyStrings;

/** \class HLTMuon
  *  
  * $Date: November 2006
  * $Revision: 
  * \author P. Bargassa - Rice U.
  */
class HLTMuon {
public:
  HLTMuon(); 

  void setup(const edm::ParameterSet& pSet, TTree* tree);

  /** Analyze the Data */
  void analyze(const edm::Handle<reco::MuonCollection>                 & muon,
               const edm::Handle<l1extra::L1MuonParticleCollection>   & mucands1, 
	       const edm::Handle<reco::RecoChargedCandidateCollection> & mucands2,
	       const edm::Handle<edm::ValueMap<bool> >           & isoMap2,
	       const edm::Handle<reco::RecoChargedCandidateCollection> & mucands3,
	       const edm::Handle<edm::ValueMap<bool> >           & isoMap3,
               const edm::Handle<reco::RecoChargedCandidateCollection> & oniaPixelCands,
               const edm::Handle<reco::RecoChargedCandidateCollection> & oniaTrackCands,
	       const edm::Handle<reco::VertexCollection> & dimuvtxcands3,
	       const edm::Handle<reco::RecoChargedCandidateCollection> & munovtxcands2, 
               //const reco::BeamSpot::Point & BSPosition,
	       const edm::ESHandle<MagneticField> & theMagField,
               const edm::Handle<reco::BeamSpot> & recoBeamSpotHandle,
	       TTree* tree);


private:

  // Tree variables
  float *muonpt, *muonphi, *muoneta, *muonet, *muone, *muonchi2NDF, *muoncharge,
  *muonTrkIsoR03, *muonECalIsoR03, *muonHCalIsoR03, *muonD0;
  int *muontype, *muonNValidTrkHits, *muonNValidMuonHits;
  float *muonl2pt, *muonl2eta, *muonl2phi, *muonl2dr, *muonl2dz, *muonl2vtxz;
  float *muonl3pt, *muonl3eta, *muonl3phi, *muonl3dr, *muonl3dz, *muonl3vtxz, *muonl3normchi2;
  float *muonl2novtxpt, *muonl2novtxeta, *muonl2novtxphi, *muonl2novtxdr, *muonl2novtxdz; 
  float *muonl2pterr, *muonl3pterr, *muonl2novtxpterr;
  int nmuon, nmu2cand, nmu3cand, nmu2novtxcand;
  int *muonl2chg, *muonl2iso, *muonl2nhits, *muonl3chg, *muonl3iso, *muonl32idx, *muonl3nhits, *muonl21idx, *muonl2novtxchg, *muonl2novtxiso, *muonl2novtx1idx, *muonl2novtxnhits;
  int *muonl3ntrackerhits, *muonl3nmuonhits;

  int nOniaPixelCand, nOniaTrackCand;
  float *oniaPixelpt, *oniaPixeleta, *oniaPixelphi, *oniaPixeldr, *oniaPixeldz, *oniaPixelNormChi2;
  float *oniaTrackpt, *oniaTracketa, *oniaTrackphi, *oniaTrackdr, *oniaTrackdz, *oniaTrackNormChi2;
  int *oniaPixelchg, *oniaTrackchg, *oniaPixelHits, *oniaTrackHits;
  int nDiMu,nDiMuVtx;
  float *dimudca;
  int *dimu1st,*dimu2nd,*dimuvtx1st,*dimuvtx2nd;
  float *dimuvtxchi2,*dimuvtxr,*dimuvtxrsig,*dimuvtxroversig,*dimuvtxcosalpha;
  float *dimuvtxmu2dipmax, *dimuvtxmu2dipmin, *dimuvtxmu2dipsigmax, *dimuvtxmu2dipsigmin;
 	

  // input variables
  bool _Monte,_Debug;

  int evtCounter;

  const float etaBarrel() {return 1.4;}

};

#endif
