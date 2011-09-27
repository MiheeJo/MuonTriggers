#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <math.h>

#include <TROOT.h>
#include <TH2.h>
#include <TH1.h>
#include <TMath.h>

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

struct FLAG {
  // Matching parameters  
  bool doGen;
  bool doSim;
  bool doSta;
  bool match_dR;
  float dCut;
  bool jpsi;
  bool dimuTrig;
  string trig;
  string fdir;
  int trigLevel;

  // Trigger cut parameters
  bool doDimuMassCut;
  float mCut;             //in GeV
};

class INFO {
public:
  int tot_NGenMu;
  int tot_NStaMu;
  int tot_NL1Mu;
  int tot_NohMuL2;
  int tot_NohMuL3;
  int tot_NL1ValidEvt;
  int tot_NL2ValidEvt;
  int tot_NL3ValidEvt;
  int tot_NLumiBlock;

  INFO(int init=0);
};

INFO::INFO(int init) {
  tot_NGenMu = init;
  tot_NStaMu = init;
  tot_NL1Mu = init;
  tot_NohMuL2 = init;
  tot_NohMuL3 = init;
  tot_NL1ValidEvt = init;
  tot_NL2ValidEvt = init;
  tot_NL3ValidEvt = init;
  tot_NLumiBlock = init;
}

struct MATCH {
  std::vector<float> deltaR;
  std::vector<float> deltaEta;
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
};

// 'a' is index number of MATCH *mat
// eta, phi, pt, chg are candidate's properties
void matching (bool match_dR, MATCH *mat, unsigned int a, float eta, float phi, float pt, int chg=0) {
  float dR_t = deltaR(mat->ref_eta[a],mat->ref_phi[a],eta,phi);
  float dEta_t = fabs(mat->ref_eta[a]-eta);
  if ( (match_dR && mat->deltaR.size() == a) ||
       (!match_dR && mat->deltaEta.size() ==a) ) {
      mat->deltaR.push_back(dR_t);
      mat->deltaEta.push_back(dEta_t);
      mat->cand_eta.push_back(eta);
      mat->cand_pt.push_back(pt);
      mat->cand_phi.push_back(phi);
      mat->cand_chg.push_back(chg);
  } else if ( (match_dR && dR_t < mat->deltaR[a]) ||
              (!match_dR && dEta_t < mat->deltaEta[a]) ) {
      mat->deltaR[a] = dR_t;
      mat->deltaEta[a] = dEta_t;
      mat->cand_eta[a] = eta;
      mat->cand_pt[a] = pt;
      mat->cand_phi[a] = phi;
      mat->cand_chg[a] = chg;
  }
  return;
}
