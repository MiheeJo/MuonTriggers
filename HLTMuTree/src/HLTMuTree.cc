// Package:    HLTMuTree
// Class:      HLTMuTree
// 
// Original Author:  Mihee Jo
// $Id: HLTMuTree.cc,v 1.6 2011/11/15 23:34:23 miheejo Exp $
//

#include "HiMuonAlgos/HLTMuTree/interface/HLTMuTree.h"
//#include "UserCode/HLTMuTree/interface/HLTMuTree.h"

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
  tagGenPtl = iConfig.getParameter<edm::InputTag>("genparticle");
  tagSimTrk = iConfig.getParameter<edm::InputTag>("simtrack");
  MuCandTag2 = iConfig.getParameter<edm::InputTag>("MuCandTag2");
  MuCandTag3 = iConfig.getParameter<edm::InputTag>("MuCandTag3");
  doReco = iConfig.getUntrackedParameter<bool>("doReco");
  doGen = iConfig.getUntrackedParameter<bool>("doGen");
  doHLT = iConfig.getUntrackedParameter<bool>("doHLT");
}


HLTMuTree::~HLTMuTree()
{
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
  nmu2cand = nmu3cand = 0;
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
    GlbMu.nValMuHits[i] = 0;
    GlbMu.nValTrkHits[i] = 0; 
    GlbMu.nTrkFound[i] = 0;
    GlbMu.glbChi2_ndof[i] = 0;
    GlbMu.trkChi2_ndof[i] = 0;
    GlbMu.pixLayerWMeas[i] = 0;
    GlbMu.trkDxy[i] = 0;
    GlbMu.trkDz[i] = 0;
    StaMu.charge[i] = 0;
    StaMu.pt[i] = 0;
    StaMu.p[i] = 0;
    StaMu.eta[i] = 0;
    StaMu.phi[i] = 0;
    StaMu.dxy[i] = 0;
    StaMu.dz[i] = 0;
    muonl2pt[i] = 0; muonl2eta[i] = 0; muonl2phi[i] = 0; muonl2dr[i] = 0; muonl2dz[i] = 0; muonl2vtxz[i] = 0;
    muonl3pt[i] = 0; muonl3eta[i] = 0; muonl3phi[i] = 0; muonl3dr[i] = 0; muonl3dz[i] = 0; muonl3vtxz[i] = 0; muonl3normchi2[i] = 0;
    muonl2pterr[i] = 0; muonl3pterr[i] = 0;
    muonl2chg[i] = 0; muonl2nhits[i] = 0; muonl3chg[i] = 0; muonl3nhits[i] = 0;
    muonl3ntrackerhits[i] = 0; muonl3nmuonhits[i] = 0;

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
          GenMu.pt[nGen] = genPtl->pt();
          GenMu.p[nGen] = genPtl->p();
          GenMu.eta[nGen] = genPtl->eta();
          GenMu.phi[nGen] = genPtl->phi();
          GenMu.status[nGen] = genPtl->status();
          GenMu.pid[nGen] = genPtl->pdgId();
          
          GenMu.mom[nGen] = 10; 
          if (genPtl->numberOfMothers() > 0 ) {
            vector<int> momid;
            vector<int>::iterator it_jpsi, it_ups;
            for (unsigned int mom = 0; mom < genPtl->numberOfMothers(); mom++) {
              cout << "mom pid: " << genPtl->mother(mom)->pdgId() << endl;
              momid.push_back(genPtl->mother(mom)->pdgId());
            }

            if (!momid.empty()) {
              it_jpsi = find(momid.begin(),momid.end(),443);
              it_ups = find(momid.begin(),momid.end(),553);
              if (it_jpsi != momid.end()) GenMu.mom[nGen] = 443;
              if (it_ups != momid.end()) GenMu.mom[nGen] = 553;
              
              //No J/psi, Y mother -> Should check grandmother
              if (it_jpsi == momid.end() && it_ups == momid.end()) {
                const Candidate *mother = genPtl->mother(0);
                momid.clear();
                for (unsigned int mom = 0; mom < mother->numberOfMothers(); mom++) {
                  cout << "grand mom pid: " << mother->mother(mom)->pdgId() << endl;
                  momid.push_back(mother->mother(mom)->pdgId());
                }

                if (!momid.empty()) {
                  it_jpsi = find(momid.begin(),momid.end(),443);
                  it_ups = find(momid.begin(),momid.end(),553);
                  if (it_jpsi != momid.end()) GenMu.mom[nGen] = 443;
                  if (it_ups != momid.end()) GenMu.mom[nGen] = 553;
                  if (it_jpsi == momid.end() && it_ups == momid.end()) GenMu.mom[nGen] = momid[0];
                }
              } //End of no J/psi, Y mother -> Should check grandmother
            }

          }
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
      if (muCand->globalTrack().isNonnull() && muCand->innerTrack().isNonnull()) {
        if (muCand->isGlobalMuon() && muCand->isTrackerMuon() && fabs(muCand->combinedMuon()->eta()) < 2.4) {
 cout << "|y| < 2.4" <<endl;
          edm::RefToBase<reco::Track> trk = edm::RefToBase<reco::Track>(muCand->innerTrack());
          edm::RefToBase<reco::Track> glb = edm::RefToBase<reco::Track>(muCand->combinedMuon());
          const reco::HitPattern& p = trk->hitPattern();

          GlbMu.nValMuHits[nGlb] = muCand->combinedMuon().get()->hitPattern().numberOfValidMuonHits();
          GlbMu.nValTrkHits[nGlb] = muCand->innerTrack().get()->hitPattern().numberOfValidTrackerHits();

          GlbMu.nTrkFound[nGlb] = trk->found();
          GlbMu.glbChi2_ndof[nGlb] = glb->chi2()/glb->ndof();
          GlbMu.trkChi2_ndof[nGlb] = trk->chi2()/trk->ndof();
          GlbMu.pixLayerWMeas[nGlb] = p.pixelLayersWithMeasurement();
          GlbMu.trkDxy[nGlb] = fabs(trk->dxy(vertex->begin()->position()));
          GlbMu.trkDz[nGlb] = fabs(trk->dz(vertex->begin()->position()));

          GlbMu.charge[nGlb] = glb->charge();
          GlbMu.pt[nGlb] = glb->pt();
          GlbMu.p[nGlb] = glb->p();
          GlbMu.eta[nGlb] = glb->eta();
          GlbMu.phi[nGlb] = glb->phi();
          GlbMu.dxy[nGlb] = glb->dxy(vertex->begin()->position()); 
          GlbMu.dz[nGlb] = glb->dz(vertex->begin()->position());
          nGlb++;
        }
        
      }
      if (muCand->isStandAloneMuon() && muCand->outerTrack().isNonnull()) {
        if (muCand->standAloneMuon().get()->hitPattern().numberOfValidMuonHits()>0 && fabs(muCand->standAloneMuon()->eta())<2.4) {
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

    if (doHLT) {
      edm::Handle<reco::RecoChargedCandidateCollection> MuCands2;
      iEvent.getByLabel(MuCandTag2,MuCands2);
      if (MuCands2.isValid()) {
        const reco::RecoChargedCandidateCollection myMucands2 = *MuCands2;
        typedef reco::RecoChargedCandidateCollection::const_iterator cand;
        nmu2cand = myMucands2.size();
cout << "nmu2cand  " << nmu2cand << endl;
        int imu2c=0;
        for (cand i=myMucands2.begin(); i!=myMucands2.end(); i++) {
          reco::TrackRef tk = i->get<reco::TrackRef>();

          muonl2pt[imu2c] = tk->pt();
          muonl2eta[imu2c] = tk->eta();
          muonl2phi[imu2c] = tk->phi();
          muonl2dr[imu2c] = fabs(tk->dxy(vertex->begin()->position())); //fabs(tk->dxy(BSPosition));
          muonl2dz[imu2c] = tk->dz(vertex->begin()->position());
          muonl2vtxz[imu2c] = tk->dz();
          muonl2nhits[imu2c] = tk->numberOfValidHits(); 

          double l2_err0 = tk->error(0); // error on q/p
          double l2_abspar0 = fabs(tk->parameter(0)); // |q/p|

          muonl2pterr[imu2c] = l2_err0/l2_abspar0;
          muonl2chg[imu2c] = tk->charge();

          imu2c++;
        } // End of l2 muon loop
      } else {nmu2cand = 0;} // End of l2 muon is valid

      edm::Handle<reco::RecoChargedCandidateCollection> MuCands3;
      iEvent.getByLabel(MuCandTag3,MuCands3);
      if (MuCands3.isValid()) {
        const reco::RecoChargedCandidateCollection myMucands3 = *MuCands3;
        nmu3cand = myMucands3.size();
        
        typedef reco::RecoChargedCandidateCollection::const_iterator cand;
        int imu3c=0;
        for (cand i=myMucands3.begin(); i!=myMucands3.end(); i++) {
          reco::TrackRef tk = i->get<reco::TrackRef>();

          muonl3pt[imu3c] = tk->pt();
          muonl3eta[imu3c] = tk->eta();
          muonl3phi[imu3c] = tk->phi();

          muonl3dr[imu3c] = fabs(tk->dxy(vertex->begin()->position()));
          muonl3dz[imu3c] = tk->dz(vertex->begin()->position());
          muonl3vtxz[imu3c] = tk->dz();
          muonl3nhits[imu3c] = tk->numberOfValidHits();  

          double l3_err0 = tk->error(0); // error on q/p
          double l3_abspar0 = fabs(tk->parameter(0)); // |q/p|

          muonl3pterr[imu3c] = l3_err0/l3_abspar0;
          muonl3chg[imu3c] = tk->charge();

          muonl3normchi2[imu3c] = tk->normalizedChi2();
          muonl3ntrackerhits[imu3c] = tk->hitPattern().numberOfValidTrackerHits();
          muonl3nmuonhits[imu3c] = tk->hitPattern().numberOfValidMuonHits();

          imu3c++;
        }
      } else {nmu3cand = 0;}

    } else {
      nmu2cand=0; nmu3cand=0;
    } // End of doHLT


  } else {
    vx = -1;
    vy = -1;
    vz = -1; 
    cbin = -1;
  } // End of doReco

  // Get trigger objects


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

  treeMu->Branch("Glb_nValMuHits",GlbMu.nValMuHits,"Glb_nValMuHits[Glb_nptl]/I");
  treeMu->Branch("Glb_nValTrkHits",GlbMu.nValTrkHits,"Glb_nValTrkHits[Glb_nptl]/I");
  treeMu->Branch("Glb_nTrkFound",GlbMu.nTrkFound,"Glb_nTrkFound[Glb_nptl]/I");
  treeMu->Branch("Glb_glbChi2_ndof",GlbMu.glbChi2_ndof,"Glb_glbChi2_ndof[Glb_nptl]/F");
  treeMu->Branch("Glb_trkChi2_ndof",GlbMu.trkChi2_ndof,"Glb_trkChi2_ndof[Glb_nptl]/F");
  treeMu->Branch("Glb_pixLayerWMeas",GlbMu.pixLayerWMeas,"Glb_pixLayerWMeas[Glb_nptl]/I");
  treeMu->Branch("Glb_trkDxy",GlbMu.trkDxy,"Glb_trkDxy[Glb_nptl]/F");
  treeMu->Branch("Glb_trkDz",GlbMu.trkDz,"Glb_trkDz[Glb_nptl]/F");

  treeMu->Branch("Sta_nptl",&StaMu.nptl,"Sta_nptl/I");
  treeMu->Branch("Sta_charge",StaMu.charge,"Sta_charge[Sta_nptl]/I");
  treeMu->Branch("Sta_p",StaMu.p,"Sta_p[Sta_nptl]/F");
  treeMu->Branch("Sta_pt",StaMu.pt,"Sta_pt[Sta_nptl]/F");
  treeMu->Branch("Sta_eta",StaMu.eta,"Sta_eta[Sta_nptl]/F");
  treeMu->Branch("Sta_phi",StaMu.phi,"Sta_phi[Sta_nptl]/F");
  treeMu->Branch("Sta_dxy",StaMu.dxy,"Sta_dx[Sta_nptl]/F");
  treeMu->Branch("Sta_dz",StaMu.dz,"Sta_dz[Sta_nptl]/F");

  treeMu->Branch("NohMuL2",&nmu2cand,"NohMuL2/I");
  treeMu->Branch("ohMuL2Pt",muonl2pt,"ohMuL2Pt[NohMuL2]/F");
  treeMu->Branch("ohMuL2Phi",muonl2phi,"ohMuL2Phi[NohMuL2]/F");
  treeMu->Branch("ohMuL2Eta",muonl2eta,"ohMuL2Eta[NohMuL2]/F");
  treeMu->Branch("ohMuL2Chg",muonl2chg,"ohMuL2Chg[NohMuL2]/I");
  treeMu->Branch("ohMuL2PtErr",muonl2pterr,"ohMuL2PtErr[NohMuL2]/F");
  treeMu->Branch("ohMuL2Dr",muonl2dr,"ohMuL2Dr[NohMuL2]/F");
  treeMu->Branch("ohMuL2Dz",muonl2dz,"ohMuL2Dz[NohMuL2]/F");
  treeMu->Branch("ohMuL2VtxZ",muonl2vtxz,"ohMuL2VtxZ[NohMuL2]/F");
  treeMu->Branch("ohMuL2Nhits",muonl2nhits,"ohMuL2Nhits[NohMuL2]/I");   
  treeMu->Branch("NohMuL3",&nmu3cand,"NohMuL3/I");
  treeMu->Branch("ohMuL3Pt",muonl3pt,"ohMuL3Pt[NohMuL3]/F");
  treeMu->Branch("ohMuL3Phi",muonl3phi,"ohMuL3Phi[NohMuL3]/F");
  treeMu->Branch("ohMuL3Eta",muonl3eta,"ohMuL3Eta[NohMuL3]/F");
  treeMu->Branch("ohMuL3Chg",muonl3chg,"ohMuL3Chg[NohMuL3]/I");
  treeMu->Branch("ohMuL3PtErr",muonl3pterr,"ohMuL3PtErr[NohMuL3]/F");
  treeMu->Branch("ohMuL3Dr",muonl3dr,"ohMuL3Dr[NohMuL3]/F");
  treeMu->Branch("ohMuL3Dz",muonl3dz,"ohMuL3Dz[NohMuL3]/F");
  treeMu->Branch("ohMuL3VtxZ",muonl3vtxz,"ohMuL3VtxZ[NohMuL3]/F");
  treeMu->Branch("ohMuL3Nhits",muonl3nhits,"ohMuL3Nhits[NohMuL3]/I");    
  treeMu->Branch("ohMuL3NormChi2", muonl3normchi2, "ohMuL3NormChi2[NohMuL3]/F");
  treeMu->Branch("ohMuL3Ntrackerhits", muonl3ntrackerhits, "ohMuL3Ntrackerhits[NohMuL3]/I"); 
  treeMu->Branch("ohMuL3Nmuonhits", muonl3nmuonhits, "ohMuL3Nmuonhits[NohMuL3]/I"); 

}

// ------------ method called once each job just after ending the event loop  ------------
void 
HLTMuTree::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(HLTMuTree);
