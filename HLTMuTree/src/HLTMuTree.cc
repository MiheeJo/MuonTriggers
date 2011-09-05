// -*- C++ -*-
//
// Package:    HLTMuTree
// Class:      HLTMuTree
// 
/**\class HLTMuTree HLTMuTree.cc UserCode/HLTMuTree/src/HLTMuTree.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Mihee Jo,588 R-012,+41227673278,
//         Created:  Thu Jul  7 11:47:28 CEST 2011
// $Id$
//
//

#include "UserCode/HLTMuTree/interface/HLTMuTree.h"

using namespace std;
using namespace reco;
using namespace edm;
using namespace HepMC;

//
// constructors and destructor
//
HLTMuTree::HLTMuTree(const edm::ParameterSet& iConfig)
{
  //now do what ever initialization is needed
  tagRecoMu = iConfig.getParameter<edm::InputTag>("muons");
  tagVtx = iConfig.getParameter<edm::InputTag>("vertices");
  doReco = iConfig.getUntrackedParameter<bool>("doReco");
  doGen = iConfig.getUntrackedParameter<bool>("doGen");
  tagGenPtl = iConfig.getParameter<edm::InputTag>("genparticle");
  tagSimTrk = iConfig.getParameter<edm::InputTag>("simtrack");
/*  if (!doGen) {
    tagL1gtReadout = iConfig.getParameter<edm::InputTag>("L1gtReadout");
    hltResName = iConfig.getUntrackedParameter<string>("hltTrgResults","TriggerResults::HLT");

    if (iConfig.exists("hltTrgNames"))
      hltTrgNames = iConfig.getUntrackedParameter<vector<string> >("hltTrgNames");

    if (iConfig.exists("hltProcNames"))
      hltProcNames = iConfig.getUntrackedParameter<vector<string> >("hltProcNames");
    else {
      hltProcNames.push_back("FU");
      hltProcNames.push_back("HLT");
    }
  }*/

}


HLTMuTree::~HLTMuTree()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
HLTMuTree::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;
  
  //Initialization
  GenMu.nptl = GlbMu.nptl = StaMu.nptl = 0;
  for (int i=0; i<nmax; i++) {
    GenMu.pid[i] = 10;
    GenMu.status[i] = 0;
    GenMu.mom[i] = 10;
    GenMu.pt[i] = 0;
    GenMu.p[i] = 0;
    GenMu.eta[i] = 0;
    GenMu.phi[i] = 0;
    GlbMu.charge[i] = 0;
    GlbMu.pt[i] = 0;
    GlbMu.p[i] = 0;
    GlbMu.eta[i] = 0;
    GlbMu.phi[i] = 0;
    GlbMu.dxy[i] = 0;
    GlbMu.dz[i] = 0;
    StaMu.charge[i] = 0;
    StaMu.pt[i] = 0;
    StaMu.p[i] = 0;
    StaMu.eta[i] = 0;
    StaMu.phi[i] = 0;
    StaMu.dxy[i] = 0;
    StaMu.dz[i] = 0;
  }

  //Get run, event, centrality
  event = iEvent.id().event();
  run = iEvent.id().run();
  lumi = iEvent.id().luminosityBlock();

  //Loop over GenParticles, g4SimHits
  if (doGen) {
    int nGen = 0;

    edm::Handle<reco::GenParticleCollection> genColl;
    iEvent.getByLabel(tagGenPtl,genColl);
    if (genColl.isValid()) {
      for (reco::GenParticleCollection::size_type i=0; i+1<genColl.product()->size(); i++) {
        const GenParticleRef genPtl(genColl,i);
        if (abs(genPtl->pdgId()) == 13 && genPtl->status() == 1) {

          GenMu.pid[nGen] = genPtl->pdgId();
          if (genPtl->numberOfMothers() > 0 ) {
            GenMu.mom[nGen] = genPtl->mother(0)->pdgId();
            cout << "mom pid: " << genPtl->mother(0)->pdgId() << endl;
          } else {
            GenMu.mom[nGen] = 10; 
          }

          GenMu.pt[nGen] = genPtl->pt();
          GenMu.p[nGen] = genPtl->p();
          GenMu.eta[nGen] = genPtl->eta();
          GenMu.phi[nGen] = genPtl->phi();
          GenMu.status[nGen] = genPtl->status();
          nGen++;
        }
      }
    } //End of gen collection
    
/*    edm::Handle<TrackingParticleCollection> simColl;
    iEvent.getByLabel(tagSimTrk,simColl);
    if (simColl.isValid()) {
      for (TrackingParticleCollection::size_type i=0; i+1<simColl.product()->size(); i++) {
        const TrackingParticleRef simTrk(simColl,i);
        if (simTrk.isNull()) continue;
        if (abs(simTrk->pdgId()) == 13 && simTrk->status() == -99) {

          GenMu.pid[nGen] = simTrk->pdgId();
          GenMu.mom[nGen] = 10; 
          for (TrackingParticle::genp_iterator it=simTrk->genParticle_begin();
              it!=simTrk->genParticle_end(); ++it) {
            if ((*it)->status() == 1) GenMu.mom[nGen] = (*it)->pdg_id();
            cout << "sim track mom pid: " << (*it)->pdg_id() <<"\t"  << (*it)->status() << endl;
          }

          GenMu.pt[nGen] = simTrk->pt();
          GenMu.p[nGen] = simTrk->p();
          GenMu.eta[nGen] = simTrk->eta();
          GenMu.phi[nGen] = simTrk->phi();
          GenMu.status[nGen] = simTrk->status();
          nGen++;
        }
      }
    } //End of sim tracks
*/
    GenMu.nptl = nGen;
    cout << "gen_nptl: " << GenMu.nptl << endl;
    if (nGen >= nmax) {
      cout << "Gen muons in a event exceeded maximum. \n";
      return ;
    }

  } //End of doGen

  //Loop over reco::muon
  if (doReco) {
    //Put centrality information
    centrality = new CentralityProvider(iSetup);
    centrality->newEvent(iEvent,iSetup);
    cbin = centrality->getBin();

    //Get vertex position
    edm::Handle< vector<reco::Vertex> > vertex;
    iEvent.getByLabel(tagVtx,vertex);
    if(vertex->size() > 0){
      vx = vertex->begin()->x();
      vy = vertex->begin()->y();
      vz = vertex->begin()->z();
    } else {
      vx = -1;
      vy = -1;
      vz = -1; 
    }

    edm::Handle< edm::View<reco::Muon> > muons;
    iEvent.getByLabel(tagRecoMu,muons);
    int nGlb = 0;
    int nSta = 0;
    for (unsigned int i=0; i<muons->size(); i++) {
      edm::RefToBase<reco::Muon> muCand(muons,i);
      if (muCand.isNull()) continue;
      if (muCand->isGlobalMuon()) {
        edm::RefToBase<reco::Track> glb = edm::RefToBase<reco::Track>(muCand->combinedMuon());
//        edm::RefToBase<reco::Track> glb = edm::RefToBase<reco::Track>(muCand->globalTrack());
        GlbMu.charge[nGlb] = glb->charge();
        GlbMu.pt[nGlb] = glb->pt();
        GlbMu.p[nGlb] = glb->p();
        GlbMu.eta[nGlb] = glb->eta();
        GlbMu.phi[nGlb] = glb->phi();
        GlbMu.dxy[nGlb] = glb->dxy(vertex->begin()->position()); 
        GlbMu.dz[nGlb] = glb->dz(vertex->begin()->position());
        nGlb++;
      }
      if (muCand->isStandAloneMuon()) {
        edm::RefToBase<reco::Track> sta = edm::RefToBase<reco::Track>(muCand->standAloneMuon());
        StaMu.charge[nSta] = sta->charge();
        StaMu.pt[nSta] = sta->pt();
        StaMu.p[nSta] = sta->p();
        StaMu.eta[nSta] = sta->eta();
        StaMu.phi[nSta] = sta->phi();
        StaMu.dxy[nSta] = sta->dxy(vertex->begin()->position()); 
        StaMu.dz[nSta] = sta->dz(vertex->begin()->position()); 
        nSta++;
      }
      if (nGlb >= nmax) {
        cout << "Global muons in a event exceeded maximum. \n";
        return ;
      }
      if (nSta >= nmax) {
        cout << "Standalone muons in a event exceeded maximum. \n";
        return ;
      }
    }
    GlbMu.nptl = nGlb;
    StaMu.nptl = nSta;
  } // End of doReco
  else {
    vx = -1;
    vy = -1;
    vz = -1; 
    cbin = -1;
  }

  // Fill a muon tree
  treeMu->Fill();
}


// ------------ method called once each job just before starting event loop  ------------
void 
HLTMuTree::beginJob()
{
  treeMu = foutput->make<TTree>("HLTMuTree","HLTMuTree");
  treeMu->Branch("Run",&run,"run/I");
  treeMu->Branch("Event",&event,"event/I");
  treeMu->Branch("Lumi",&lumi,"lumi/I");
  treeMu->Branch("CentBin",&cbin,"cbin/I");
  treeMu->Branch("vx",&vx,"vx/F");
  treeMu->Branch("vy",&vy,"vy/F");
  treeMu->Branch("vz",&vz,"vz/F");

  treeMu->Branch("Gen_nptl",&GenMu.nptl,"Gen_nptl/I");
  treeMu->Branch("Gen_pid",GenMu.pid,"Gen_pid[Gen_nptl]/I");
  treeMu->Branch("Gen_mom",GenMu.mom,"Gen_mom[Gen_nptl]/I");
  treeMu->Branch("Gen_status",GenMu.status,"Gen_status[Gen_nptl]/I");
  treeMu->Branch("Gen_p",GenMu.p,"Gen_p[Gen_nptl]/F");
  treeMu->Branch("Gen_pt",GenMu.pt,"Gen_pt[Gen_nptl]/F");
  treeMu->Branch("Gen_eta",GenMu.eta,"Gen_eta[Gen_nptl]/F");
  treeMu->Branch("Gen_phi",GenMu.phi,"Gen_phi[Gen_nptl]/F");

  treeMu->Branch("Glb_nptl",&GlbMu.nptl,"Glb_nptl/I");
  treeMu->Branch("Glb_charge",GlbMu.charge,"Glb_charge[Glb_nptl]/I");
  treeMu->Branch("Glb_p",GlbMu.p,"Glb_p[Glb_nptl]/F");
  treeMu->Branch("Glb_pt",GlbMu.pt,"Glb_pt[Glb_nptl]/F");
  treeMu->Branch("Glb_eta",GlbMu.eta,"Glb_eta[Glb_nptl]/F");
  treeMu->Branch("Glb_phi",GlbMu.phi,"Glb_phi[Glb_nptl]/F");
  treeMu->Branch("Glb_dxy",GlbMu.dxy,"Glb_dx[Glb_nptl]/F");
  treeMu->Branch("Glb_dz",GlbMu.dz,"Glb_dz[Glb_nptl]/F");

  treeMu->Branch("Sta_nptl",&StaMu.nptl,"Sta_nptl/I");
  treeMu->Branch("Sta_charge",StaMu.charge,"Sta_charge[Sta_nptl]/I");
  treeMu->Branch("Sta_p",StaMu.p,"Sta_p[Sta_nptl]/F");
  treeMu->Branch("Sta_pt",StaMu.pt,"Sta_pt[Sta_nptl]/F");
  treeMu->Branch("Sta_eta",StaMu.eta,"Sta_eta[Sta_nptl]/F");
  treeMu->Branch("Sta_phi",StaMu.phi,"Sta_phi[Sta_nptl]/F");
  treeMu->Branch("Sta_dxy",StaMu.dxy,"Sta_dx[Sta_nptl]/F");
  treeMu->Branch("Sta_dz",StaMu.dz,"Sta_dz[Sta_nptl]/F");
}

// ------------ method called once each job just after ending the event loop  ------------
void 
HLTMuTree::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(HLTMuTree);
