#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <math.h>

#include <TROOT.h>
#include <TH2.h>
#include <TH1.h>
#include <TMath.h>


static const int nmax =10000;
const float PI = 3.1415926535897932385;
const float Mmu = 0.105658369;
// Number of bins
const int ETA = 20;
const int PT = 20;
const int PHI = 20;

struct ptcomp {
  bool operator()(const float &v1, const float &v2) const
  {return v1>v2;}
};

float deltaPhi(float phi1,float phi2) {
  float res = phi1 - phi2;
  while (res >= PI) res -= 2*PI;
  while (res < -PI) res += 2*PI;
  return res;
}

float deltaR(Float_t gen_eta, Float_t gen_phi, Float_t l2_eta, Float_t l2_phi) {
  return ( 
      sqrt( (gen_eta-l2_eta)*(gen_eta-l2_eta) + deltaPhi(gen_phi,l2_phi)*deltaPhi(gen_phi,l2_phi) )
        );
}

class FLAG {
public:
  // Matching parameters  
  bool doGen;         // Get efficiency with gen muons
  bool doSim;         // Get efficiency with gen + sim muons
  bool doSta;         // Get efficiency with standalone muons
  bool doGlb;         // Get efficiency with global muons
  bool match_dR;      // deltaR matching(true) or not
  float dCut;         // deltaR cut for matching trigger object and gen/reco muons
  bool jpsi;          // Is this MC sample composed of J/psi(true) or Y(false)?
  bool dimuTrig;      // Is this trigger a dimuon trigger? : true for dimuon trigger, false for single muon trigger
  string fdir;        // file directory
  string trigPath;    // name of trigger path
  int trigLevel;      // Trigger level
  int trig;           // Trigger bit : 1 for fired, 0 for not fired
  string refTrigPath; // Trigger name for reference trigger
  int refTrig;        // Trigger bit for reference trigger

  // Trigger cut parameters
  bool doDimuMassCut;     // cut off dimuons below mass < mCut (with true)
  float mCut;             //in GeV
  bool doSinglemuPtCut;   // cut off single muons below pT < pTCut (with true)
  float pTCut;            //in GeV

  FLAG(void);
};

FLAG::FLAG(void) {
  doGen = false;
  doSim = false;
  doSta = false;
  doGlb = true;
  match_dR = false;
  dCut = 0.4;
  jpsi = true;
  dimuTrig = true;
  fdir = "";
  trigPath = "";
  trigLevel = 2;
  trig = 0;
  refTrigPath = "";
  refTrig = 0;
  doDimuMassCut = false;
  mCut = 2;
  doSinglemuPtCut = false;
  pTCut = 1;
}

class INFO {
public:
  int tot_NGenMu;
  int tot_NStaMu;
  int tot_NGlbMu;
  int tot_NL1Mu;
  int tot_NohMuL2;
  int tot_NohMuL3;
  int tot_NL1ValidEvt;
  int tot_NL2ValidEvt;
  int tot_NL3ValidEvt;
  int tot_NGlbValidEvt;   // total # of events that global muons passing acc & qual muon id cuts
  int tot_NLumiBlock;

  INFO(int init=0);
};

INFO::INFO(int init) {
  tot_NGenMu = init;
  tot_NStaMu = init;
  tot_NGlbMu = init;
  tot_NL1Mu = init;
  tot_NohMuL2 = init;
  tot_NohMuL3 = init;
  tot_NL1ValidEvt = init;
  tot_NL2ValidEvt = init;
  tot_NL3ValidEvt = init;
  tot_NGlbValidEvt = init;
  tot_NLumiBlock = init;
}

struct MATCH {
  // deltaR or deltaEta from reference muon and candidate muon
  std::vector<float> deltaR;
  // Used as reference during matching 
  std::vector<float> ref_eta;
  std::vector<float> ref_phi;
  std::vector<float> ref_pt;
  std::vector<float> ref_chg;
  // Compared to ref_* during matching
  std::vector<float> cand_eta;
  std::vector<float> cand_phi;
  std::vector<float> cand_pt;
  std::vector<float> cand_chg;
  // Cand index number for already matched muons
  std::vector<int> cand_idx;
};

struct MUTREE {
  Int_t run;
  Int_t event;
  Int_t nptl;
  Float_t eta[nmax];
  Float_t pt[nmax];
  Float_t phi[nmax];
  Int_t charge[nmax];
  Int_t mom[nmax];
  Int_t status[nmax];
  Int_t nValMuHits[nmax];
  Int_t nValTrkHits[nmax];
  Int_t nTrkFound[nmax];
  Float_t glbChi2_ndof[nmax];
  Float_t trkChi2_ndof[nmax];
  Int_t pixLayerWMeas[nmax];
  Float_t trkDxy[nmax];
  Float_t trkDz[nmax];
};


// Find best matching between reference and candidate muon by getting the loweset deltaR
// 'a' is index number of MATCH *mat
// eta, phi, pt, chg are candidate's properties
void matching (MATCH *mat, unsigned int a, unsigned int b, float eta, float phi) {
  float dR_t = deltaR(mat->ref_eta[a],mat->ref_phi[a],eta,phi);
  if (mat->deltaR.size() == a) {
      mat->deltaR.push_back(dR_t);
      mat->cand_eta.push_back(eta);
      mat->cand_phi.push_back(phi);
      mat->cand_idx.push_back(b);
  } else if (dR_t < mat->deltaR[a]) {
      mat->deltaR[a] = dR_t;
      mat->cand_eta[a] = eta;
      mat->cand_phi[a] = phi;
      mat->cand_idx[a] = b;
  }

  return;
}


// Muon id cuts used for Quakonia analysis
bool isMuInAcc(FLAG *flag, float eta, float pt){
  bool value = false;
  if (flag->doGlb || flag->doGen) {
    if ( fabs(eta) < 2.4 &&
           ( (fabs(eta) < 1.0 && pt >= 3.4) ||
              (1.0 <= fabs(eta) && fabs(eta) < 1.5 && pt >= 5.8-2.4*fabs(eta)) ||
              (1.5 <= fabs(eta) && pt >= 3.3667-7.0/9.0*fabs(eta)) ) 
           )
      value = true;
  }
  if (flag->doSta) {
    if (fabs(eta) < 2.4) value = true;
  }

  return value;
}

bool isValidMu(FLAG *flag,MUTREE *mutree, int idx, string quality = "") {

		double nTrkFound = !(quality.compare("nValTrkHits")) ? -1 : 10;
		double glbChi2_ndof = !(quality.compare("glbChi2_ndof")) ? 999 : 20.0;
		double trkChi2_ndof = !(quality.compare("trkChi2_ndof")) ? 999 : 4.0;
		double pixLayerWMeas = !(quality.compare("pixLayerWMeas")) ? -1 : 0;
		double trkDxy = !(quality.compare("trkDxy")) ? 999 : 3.0;
		double trkDz = !(quality.compare("trkDz")) ? 999 : 15.0;

    return (isMuInAcc(flag,mutree->eta[idx], mutree->pt[idx]) &&
            mutree->nTrkFound[idx] > nTrkFound &&
            mutree->glbChi2_ndof[idx] < glbChi2_ndof &&
            mutree->trkChi2_ndof[idx] < trkChi2_ndof &&
            mutree->pixLayerWMeas[idx] > pixLayerWMeas &&
            mutree->trkDxy[idx] < trkDxy &&
            mutree->trkDz[idx] < trkDz );
}
