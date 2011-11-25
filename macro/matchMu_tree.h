#include <iostream>
#include <vector>
#include <string>

#include <TROOT.h>
#include <TChain.h>
#include <TCastorFile.h>
#include <TFile.h>




class FriendMuTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           Run;
   Int_t           Event;
   Int_t           Lumi;
   Int_t           CentBin;
   Float_t         vx;
   Float_t         vy;
   Float_t         vz;
   Int_t           Gen_nptl;
   Int_t           Gen_pid[nmax];   //[Gen_nptl]
   Int_t           Gen_status[nmax];   //[Gen_nptl]
   Int_t           Gen_mom[nmax];   //[Gen_nptl]
   Float_t         Gen_p[nmax];   //[Gen_nptl]
   Float_t         Gen_pt[nmax];   //[Gen_nptl]
   Float_t         Gen_eta[nmax];   //[Gen_nptl]
   Float_t         Gen_phi[nmax];   //[Gen_nptl]
   Int_t           Glb_nptl;
   Int_t           Glb_charge[nmax];   //[Glb_nptl]
   Float_t         Glb_p[nmax];   //[Glb_nptl]
   Float_t         Glb_pt[nmax];   //[Glb_nptl]
   Float_t         Glb_eta[nmax];   //[Glb_nptl]
   Float_t         Glb_phi[nmax];   //[Glb_nptl]
   Float_t         Glb_dxy[nmax];   //[Glb_nptl]
   Float_t         Glb_dz[nmax];   //[Glb_nptl]
   Int_t           Glb_nValMuHits[nmax];
   Int_t           Glb_nValTrkHits[nmax];
   Int_t           Glb_nTrkFound[nmax];
   Float_t         Glb_glbChi2_ndof[nmax];
   Float_t         Glb_trkChi2_ndof[nmax];
   Int_t           Glb_pixLayerWMeas[nmax];
   Float_t         Glb_trkDxy[nmax];
   Float_t         Glb_trkDz[nmax];
   Int_t           Sta_nptl;
   Int_t           Sta_charge[nmax];   //[Sta_nptl]
   Float_t         Sta_p[nmax];   //[Sta_nptl]
   Float_t         Sta_pt[nmax];   //[Sta_nptl]
   Float_t         Sta_eta[nmax];   //[Sta_nptl]
   Float_t         Sta_phi[nmax];   //[Sta_nptl]
   Float_t         Sta_dxy[nmax];   //[Sta_nptl]
   Float_t         Sta_dz[nmax];   //[Sta_nptl]
   Int_t           NohMuL2;
   Float_t         ohMuL2Pt[nmax];   //[NohMuL2]
   Float_t         ohMuL2Phi[nmax];   //[NohMuL2]
   Float_t         ohMuL2Eta[nmax];   //[NohMuL2]
   Int_t           ohMuL2Chg[nmax];   //[NohMuL2]
   Float_t         ohMuL2PtErr[nmax];   //[NohMuL2]
   Int_t           ohMuL2Iso[nmax];   //[NohMuL2]
   Float_t         ohMuL2Dr[nmax];   //[NohMuL2]
   Float_t         ohMuL2Dz[nmax];   //[NohMuL2]
   Int_t           NohMuL3;
   Float_t         ohMuL3Pt[nmax];   //[NohMuL3]
   Float_t         ohMuL3Phi[nmax];   //[NohMuL3]
   Float_t         ohMuL3Eta[nmax];   //[NohMuL3]
   Int_t           ohMuL3Chg[nmax];   //[NohMuL3]
   Float_t         ohMuL3PtErr[nmax];   //[NohMuL3]
   Int_t           ohMuL3Iso[nmax];   //[NohMuL3]
   Float_t         ohMuL3Dr[nmax];   //[NohMuL3]
   Float_t         ohMuL3Dz[nmax];   //[NohMuL3]
   Float_t         ohMuL3VtxZ[nmax];
   Int_t           ohMuL3Nhits[nmax];
   Float_t         ohMuL3NormChi2[nmax];
   Int_t           ohMuL3Ntrackerhits[nmax];
   Int_t           ohMuL3Nmuonhits[nmax];

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_cbin;   //!
   TBranch        *b_vx;   //!
   TBranch        *b_vy;   //!
   TBranch        *b_vz;   //!
   TBranch        *b_Gen_nptl;   //!
   TBranch        *b_Gen_pid;   //!
   TBranch        *b_Gen_status;   //!
   TBranch        *b_Gen_mom;   //!
   TBranch        *b_Gen_p;   //!
   TBranch        *b_Gen_pt;   //!
   TBranch        *b_Gen_eta;   //!
   TBranch        *b_Gen_phi;   //!
   TBranch        *b_Glb_nptl;   //!
   TBranch        *b_Glb_charge;   //!
   TBranch        *b_Glb_p;   //!
   TBranch        *b_Glb_pt;   //!
   TBranch        *b_Glb_eta;   //!
   TBranch        *b_Glb_phi;   //!
   TBranch        *b_Glb_dxy;   //!
   TBranch        *b_Glb_dz;   //!
   TBranch        *b_Glb_nValMuHits;
   TBranch        *b_Glb_nValTrkHits;
   TBranch        *b_Glb_nTrkFound;
   TBranch        *b_Glb_glbChi2_ndof;
   TBranch        *b_Glb_trkChi2_ndof;
   TBranch        *b_Glb_pixLayerWMeas;
   TBranch        *b_Glb_trkDxy;
   TBranch        *b_Glb_trkDz;
   TBranch        *b_Sta_nptl;   //!
   TBranch        *b_Sta_charge;   //!
   TBranch        *b_Sta_p;   //!
   TBranch        *b_Sta_pt;   //!
   TBranch        *b_Sta_eta;   //!
   TBranch        *b_Sta_phi;   //!
   TBranch        *b_Sta_dxy;   //!
   TBranch        *b_Sta_dz;   //!
   TBranch        *b_NohMuL2;   //!
   TBranch        *b_ohMuL2Pt;   //!
   TBranch        *b_ohMuL2Phi;   //!
   TBranch        *b_ohMuL2Eta;   //!
   TBranch        *b_ohMuL2Chg;   //!
   TBranch        *b_ohMuL2PtErr;   //!
   TBranch        *b_ohMuL2Iso;   //!
   TBranch        *b_ohMuL2Dr;   //!
   TBranch        *b_ohMuL2Dz;   //!
   TBranch        *b_NohMuL3;
   TBranch        *b_ohMuL3Pt;
   TBranch        *b_ohMuL3Phi;
   TBranch        *b_ohMuL3Eta;
   TBranch        *b_ohMuL3Chg;
   TBranch        *b_ohMuL3PtErr;
   TBranch        *b_ohMuL3Iso;
   TBranch        *b_ohMuL3Dr;
   TBranch        *b_ohMuL3Dz;
   TBranch        *b_ohMuL3VtxZ;
   TBranch        *b_ohMuL3Nhits;
   TBranch        *b_ohMuL3NormChi2;
   TBranch        *b_ohMuL3Ntrackerhits;
   TBranch        *b_ohMuL3Nmuonhits;

   FriendMuTree(TCastorFile *f, bool castor);
   virtual ~FriendMuTree();
   virtual Int_t    GetEntry(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Show(Long64_t entry = -1);
};



FriendMuTree::FriendMuTree(TCastorFile *f, bool castor)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (castor) {
     if (f == 0) { std::cout << "Cannot load file\n"; }

//     fChain = (TTree*)f->Get("analysis/HLTMuTree");
     fChain = (TTree*)f->Get("hltMuTree/HLTMuTree");
     if (!fChain) { std::cout << "Cannot load HLTMuTree\n"; }
     else Init(fChain);
   } else {
     std::cout << "Cannot load HLTMuTree\n";
   }
}

FriendMuTree::~FriendMuTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t FriendMuTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}

void FriendMuTree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Run", &Run, &b_run);
   fChain->SetBranchAddress("Event", &Event, &b_event);
   fChain->SetBranchAddress("Lumi", &Lumi, &b_lumi);
   fChain->SetBranchAddress("CentBin", &CentBin, &b_cbin);
   fChain->SetBranchAddress("vx", &vx, &b_vx);
   fChain->SetBranchAddress("vy", &vy, &b_vy);
   fChain->SetBranchAddress("vz", &vz, &b_vz);
   fChain->SetBranchAddress("Gen_nptl", &Gen_nptl, &b_Gen_nptl);
   fChain->SetBranchAddress("Gen_pid", Gen_pid, &b_Gen_pid);
   fChain->SetBranchAddress("Gen_status", Gen_status, &b_Gen_status);
   fChain->SetBranchAddress("Gen_mom", Gen_mom, &b_Gen_mom);
   fChain->SetBranchAddress("Gen_p", Gen_p, &b_Gen_p);
   fChain->SetBranchAddress("Gen_pt", Gen_pt, &b_Gen_pt);
   fChain->SetBranchAddress("Gen_eta", Gen_eta, &b_Gen_eta);
   fChain->SetBranchAddress("Gen_phi", Gen_phi, &b_Gen_phi);
   fChain->SetBranchAddress("Glb_nptl", &Glb_nptl, &b_Glb_nptl);
   fChain->SetBranchAddress("Glb_charge", Glb_charge, &b_Glb_charge);
   fChain->SetBranchAddress("Glb_p", Glb_p, &b_Glb_p);
   fChain->SetBranchAddress("Glb_pt", Glb_pt, &b_Glb_pt);
   fChain->SetBranchAddress("Glb_eta", Glb_eta, &b_Glb_eta);
   fChain->SetBranchAddress("Glb_phi", Glb_phi, &b_Glb_phi);
   fChain->SetBranchAddress("Glb_dxy", Glb_dxy, &b_Glb_dxy);
   fChain->SetBranchAddress("Glb_dz", Glb_dz, &b_Glb_dz);
   fChain->SetBranchAddress("Glb_nValMuHits", Glb_nValMuHits, &b_Glb_nValMuHits);
   fChain->SetBranchAddress("Glb_nValTrkHits", Glb_nValTrkHits, &b_Glb_nValTrkHits);
   fChain->SetBranchAddress("Glb_nTrkFound", Glb_nTrkFound, &b_Glb_nTrkFound);
   fChain->SetBranchAddress("Glb_glbChi2_ndof", Glb_glbChi2_ndof, &b_Glb_glbChi2_ndof);
   fChain->SetBranchAddress("Glb_trkChi2_ndof", Glb_trkChi2_ndof, &b_Glb_trkChi2_ndof);
   fChain->SetBranchAddress("Glb_pixLayerWMeas", Glb_pixLayerWMeas, &b_Glb_pixLayerWMeas);
   fChain->SetBranchAddress("Glb_trkDxy", Glb_trkDxy, &b_Glb_trkDxy);
   fChain->SetBranchAddress("Glb_trkDz", Glb_trkDz, &b_Glb_trkDz);
   fChain->SetBranchAddress("Sta_nptl", &Sta_nptl, &b_Sta_nptl);
   fChain->SetBranchAddress("Sta_charge", Sta_charge, &b_Sta_charge);
   fChain->SetBranchAddress("Sta_p", Sta_p, &b_Sta_p);
   fChain->SetBranchAddress("Sta_pt", Sta_pt, &b_Sta_pt);
   fChain->SetBranchAddress("Sta_eta", Sta_eta, &b_Sta_eta);
   fChain->SetBranchAddress("Sta_phi", Sta_phi, &b_Sta_phi);
   fChain->SetBranchAddress("Sta_dxy", Sta_dxy, &b_Sta_dxy);
   fChain->SetBranchAddress("Sta_dz", Sta_dz, &b_Sta_dz);
   fChain->SetBranchAddress("NohMuL2", &NohMuL2, &b_NohMuL2);
   fChain->SetBranchAddress("ohMuL2Pt", &ohMuL2Pt, &b_ohMuL2Pt);
   fChain->SetBranchAddress("ohMuL2Phi", &ohMuL2Phi, &b_ohMuL2Phi);
   fChain->SetBranchAddress("ohMuL2Eta", &ohMuL2Eta, &b_ohMuL2Eta);
   fChain->SetBranchAddress("ohMuL2Chg", &ohMuL2Chg, &b_ohMuL2Chg);
   fChain->SetBranchAddress("ohMuL2PtErr", &ohMuL2PtErr, &b_ohMuL2PtErr);
   fChain->SetBranchAddress("ohMuL2Iso", &ohMuL2Iso, &b_ohMuL2Iso);
   fChain->SetBranchAddress("ohMuL2Dr", &ohMuL2Dr, &b_ohMuL2Dr);
   fChain->SetBranchAddress("ohMuL2Dz", &ohMuL2Dz, &b_ohMuL2Dz);
   fChain->SetBranchAddress("NohMuL3",&NohMuL3,&b_NohMuL3);
   fChain->SetBranchAddress("ohMuL3Pt",&ohMuL3Pt,&b_ohMuL3Pt);
   fChain->SetBranchAddress("ohMuL3Phi",&ohMuL3Phi,&b_ohMuL3Phi);
   fChain->SetBranchAddress("ohMuL3Eta",&ohMuL3Eta,&b_ohMuL3Eta);
   fChain->SetBranchAddress("ohMuL3Chg",&ohMuL3Chg,&b_ohMuL3Chg);
   fChain->SetBranchAddress("ohMuL3PtErr",&ohMuL3PtErr,&b_ohMuL3PtErr);
   fChain->SetBranchAddress("ohMuL3Iso",&ohMuL3Iso,&b_ohMuL3Iso);
   fChain->SetBranchAddress("ohMuL3Dr",&ohMuL3Dr,&b_ohMuL3Dr);
   fChain->SetBranchAddress("ohMuL3Dz",&ohMuL3Dz,&b_ohMuL3Dz);
   fChain->SetBranchAddress("ohMuL3VtxZ",&ohMuL3VtxZ,&b_ohMuL3VtxZ);
   fChain->SetBranchAddress("ohMuL3Nhits",&ohMuL3Nhits,&b_ohMuL3Nhits);
   fChain->SetBranchAddress("ohMuL3NormChi2",&ohMuL3NormChi2,&b_ohMuL3NormChi2);
   fChain->SetBranchAddress("ohMuL3Ntrackerhits",&ohMuL3Ntrackerhits,&b_ohMuL3Ntrackerhits);
   fChain->SetBranchAddress("ohMuL3Nmuonhits",&ohMuL3Nmuonhits,&b_ohMuL3Nmuonhits);
}

void FriendMuTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}



//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jul 27 09:54:32 2011 by ROOT version 5.27/06b
// from TTree HltTree/
// found on file: hltana.root
//////////////////////////////////////////////////////////
class HltTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain
   
   // Declaration of leaf types
   Float_t         Npart;
   Float_t         Ncoll;
   Int_t           hiBin;
   Int_t           NrecoMuon;
   Float_t         recoMuonPt[nmax];   //[NrecoMuon]
   Float_t         recoMuonPhi[nmax];   //[NrecoMuon]
   Float_t         recoMuonEta[nmax];   //[NrecoMuon]
   Float_t         recoMuonEt[nmax];   //[NrecoMuon]
   Float_t         recoMuonE[nmax];   //[NrecoMuon]
   Int_t           NohMuL2;
   Float_t         ohMuL2Pt[nmax];   //[NohMuL2]
   Float_t         ohMuL2Phi[nmax];   //[NohMuL2]
   Float_t         ohMuL2Eta[nmax];   //[NohMuL2]
   Int_t           ohMuL2Chg[nmax];   //[NohMuL2]
   Float_t         ohMuL2PtErr[nmax];   //[NohMuL2]
   Float_t         ohMuL2Dr[nmax];   //[NohMuL2]
   Float_t         ohMuL2Dz[nmax];   //[NohMuL2]
   Int_t           NohMuL3;
   Float_t         ohMuL3Pt[nmax];   //[NohMuL3]
   Float_t         ohMuL3Phi[nmax];   //[NohMuL3]
   Float_t         ohMuL3Eta[nmax];   //[NohMuL3]
   Int_t           ohMuL3Chg[nmax];   //[NohMuL3]
   Float_t         ohMuL3PtErr[nmax];   //[NohMuL3]
   Float_t         ohMuL3Dr[nmax];   //[NohMuL3]
   Float_t         ohMuL3Dz[nmax];   //[NohMuL3]
   Float_t         ohMuL3VtxZ[nmax];
   Int_t           ohMuL3Nhits[nmax];
   Float_t         ohMuL3NormChi2[nmax];
   Int_t           ohMuL3Ntrackerhits[nmax];
   Int_t           ohMuL3Nmuonhits[nmax];
   Int_t           NL1Mu;
   Float_t         L1MuPt[nmax];   //[NL1Mu]
   Float_t         L1MuE[nmax];   //[NL1Mu]
   Float_t         L1MuEta[nmax];   //[NL1Mu]
   Float_t         L1MuPhi[nmax];   //[NL1Mu]
   Int_t           L1MuIsol[nmax];   //[NL1Mu]
   Int_t           L1MuMip[nmax];   //[NL1Mu]
   Int_t           L1MuFor[nmax];   //[NL1Mu]
   Int_t           L1MuRPC[nmax];   //[NL1Mu]
   Int_t           L1MuQal[nmax];   //[NL1Mu]
   Int_t           recoNVrt;
   Float_t         recoVrtX[nmax];   //[NVrtx]
   Float_t         recoVrtY[nmax];   //[NVrtx]
   Float_t         recoVrtZ[nmax];   //[NVrtx]
   Int_t           recoVrtNtrk[nmax];   //[NVrtx]
   Float_t         recoVrtChi2[nmax];   //[NVrtx]
   Float_t         recoVrtNdof[nmax];   //[NVrtx]
   Int_t           Run;
   Int_t           Event;
   Int_t           LumiBlock;
   Int_t           Bx;
   Int_t           Orbit;
   Float_t         AvgInstLumi;
   Int_t           HLT_HIL3DoubleMuOpen;
   Int_t           HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy;
   Int_t           HLT_HIL3DoubleMuOpen_Mgt2_OS;
   Int_t           HLT_HIL3DoubleMuOpen_Mgt2_SS;
   Int_t           HLT_HIL3DoubleMuOpen_Mgt2;
   Int_t           HLT_HIL2DoubleMu0_NHitQ;
   Int_t           HLT_HIL2DoubleMu0_L1HighQL2NHitQ;
   Int_t           HLT_HIL2DoubleMu0;
   Int_t           HLT_HIL2DoubleMu3;
   Int_t           HLT_HIL1DoubleMuOpen;
   Int_t           HLT_HIL1DoubleMu0_HighQ;
   Int_t           HLT_HIL3Mu3;
   Int_t           HLT_HIL2Mu3;
   Int_t           HLT_HIL2Mu7;
   Int_t           HLT_HIL2Mu15;
   Int_t           HLT_HIL1SingleMu3;
   Int_t           HLT_HIL3DoubleMuOpen_v1;
   Int_t           HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy_v1;
   Int_t           HLT_HIL3DoubleMuOpen_Mgt2_OS_v1;
   Int_t           HLT_HIL3DoubleMuOpen_Mgt2_SS_v1;
   Int_t           HLT_HIL3DoubleMuOpen_Mgt2_v1;
   Int_t           HLT_HIL2DoubleMu0_NHitQ_v1;
   Int_t           HLT_HIL2DoubleMu0_L1HighQL2NHitQ_v1;
   Int_t           HLT_HIL2DoubleMu0_v1;
   Int_t           HLT_HIL2DoubleMu3_v1;
   Int_t           HLT_HIL1DoubleMuOpen_v1;
   Int_t           HLT_HIL1DoubleMu0_HighQ_v1;
   Int_t           HLT_HIL3Mu3_v1;
   Int_t           HLT_HIL2Mu3_v1;
   Int_t           HLT_HIL2Mu7_v1;
   Int_t           HLT_HIL2Mu15_v1;
   Int_t           HLT_HIL3DoubleMuOpen_v2;
   Int_t           HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy_v2;
   Int_t           HLT_HIL3DoubleMuOpen_Mgt2_OS_v2;
   Int_t           HLT_HIL3DoubleMuOpen_Mgt2_SS_v2;
   Int_t           HLT_HIL3DoubleMuOpen_Mgt2_v2;
   Int_t           HLT_HIL2DoubleMu0_NHitQ_v2;
   Int_t           HLT_HIL2DoubleMu0_L1HighQL2NHitQ_v2;
   Int_t           HLT_HIL2DoubleMu0_v2;
   Int_t           HLT_HIL2DoubleMu3_v2;
   Int_t           HLT_HIL1DoubleMuOpen_v2;
   Int_t           HLT_HIL1DoubleMu0_HighQ_v2;
   Int_t           HLT_HIL3Mu3_v2;
   Int_t           HLT_HIL2Mu3_v2;
   Int_t           HLT_HIL2Mu7_v2;
   Int_t           HLT_HIL2Mu15_v2;
   Int_t           L1_DoubleMu3;
   Int_t           L1_DoubleMuOpen;
   Int_t           L1_DoubleMuOpen_BptxAND;
   Int_t           L1_SingleMu0;
   Int_t           L1_SingleMu10;
   Int_t           L1_SingleMu14;
   Int_t           L1_SingleMu20;
   Int_t           L1_SingleMu3;
   Int_t           L1_SingleMu3_BptxAND;   //!
   Int_t           L1_SingleMu5;
   Int_t           L1_SingleMu7;
   Int_t           L1_SingleMuBeamHalo;
   Int_t           L1_SingleMuOpen;

   // List of branches
   TBranch        *b_Npart;   //!
   TBranch        *b_Ncoll;   //!
   TBranch        *b_Ncharged;   //!
   TBranch        *b_NchargedMR;   //!
   TBranch        *b_MeanPt;   //!
   TBranch        *b_MeanPtMR;   //!
   TBranch        *b_EtMR;   //!
   TBranch        *b_NchargedPtCut;   //!
   TBranch        *b_NchargedPtCutMR;   //!
   TBranch        *b_hiBin;   //!
   TBranch        *b_hiNpix;   //!
   TBranch        *b_hiNpixelTracks;   //!
   TBranch        *b_hiNtracks;   //!
   TBranch        *b_hiNtracksPtCut;   //!
   TBranch        *b_hiNtracksEtaCut;   //!
   TBranch        *b_hiNtracksEtaPtCut;   //!
   TBranch        *b_NrecoMuon;   //!
   TBranch        *b_recoMuonPt;   //!
   TBranch        *b_recoMuonPhi;   //!
   TBranch        *b_recoMuonEta;   //!
   TBranch        *b_recoMuonEt;   //!
   TBranch        *b_recoMuonE;   //!
   TBranch        *b_NohMuL2;   //!
   TBranch        *b_ohMuL2Pt;   //!
   TBranch        *b_ohMuL2Phi;   //!
   TBranch        *b_ohMuL2Eta;   //!
   TBranch        *b_ohMuL2Chg;   //!
   TBranch        *b_ohMuL2PtErr;   //!
   TBranch        *b_ohMuL2Dr;   //!
   TBranch        *b_ohMuL2Dz;   //!
   TBranch        *b_NohMuL3;
   TBranch        *b_ohMuL3Pt;
   TBranch        *b_ohMuL3Phi;
   TBranch        *b_ohMuL3Eta;
   TBranch        *b_ohMuL3Chg;
   TBranch        *b_ohMuL3PtErr;
   TBranch        *b_ohMuL3Dr;
   TBranch        *b_ohMuL3Dz;
   TBranch        *b_ohMuL3VtxZ;
   TBranch        *b_ohMuL3Nhits;
   TBranch        *b_ohMuL3NormChi2;
   TBranch        *b_ohMuL3Ntrackerhits;
   TBranch        *b_ohMuL3Nmuonhits;
   TBranch        *b_NL1Mu;   //!
   TBranch        *b_L1MuPt;   //!
   TBranch        *b_L1MuE;   //!
   TBranch        *b_L1MuEta;   //!
   TBranch        *b_L1MuPhi;   //!
   TBranch        *b_L1MuIsol;   //!
   TBranch        *b_L1MuMip;   //!
   TBranch        *b_L1MuFor;   //!
   TBranch        *b_L1MuRPC;   //!
   TBranch        *b_L1MuQal;   //!
   TBranch        *b_NVrtx;   //!
   TBranch        *b_recoVrtX;   //!
   TBranch        *b_recoVrtY;   //!
   TBranch        *b_recoVrtZ;   //!
   TBranch        *b_recoVrtNtrk;   //!
   TBranch        *b_recoVrtChi2;   //!
   TBranch        *b_recoVrtNdof;   //!
   TBranch        *b_Run;   //!
   TBranch        *b_Event;   //!
   TBranch        *b_LumiBlock;   //!
   TBranch        *b_Bx;   //!
   TBranch        *b_Orbit;   //!
   TBranch        *b_AvgInstLumi;   //!
   TBranch        *b_HLT_HIL3DoubleMuOpen;
   TBranch        *b_HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy;
   TBranch        *b_HLT_HIL3DoubleMuOpen_Mgt2_OS;
   TBranch        *b_HLT_HIL3DoubleMuOpen_Mgt2_SS;
   TBranch        *b_HLT_HIL3DoubleMuOpen_Mgt2;
   TBranch        *b_HLT_HIL2DoubleMu0_NHitQ;
   TBranch        *b_HLT_HIL2DoubleMu0_L1HighQL2NHitQ;
   TBranch        *b_HLT_HIL2DoubleMu0;   //!
   TBranch        *b_HLT_HIL2DoubleMu3;   //!
   TBranch        *b_HLT_HIL1DoubleMuOpen;
   TBranch        *b_HLT_HIL1DoubleMu0_HighQ;
   TBranch        *b_HLT_HIL3Mu3;
   TBranch        *b_HLT_HIL2Mu3;   //!
   TBranch        *b_HLT_HIL2Mu7;   //!
   TBranch        *b_HLT_HIL2Mu15;   //!
   TBranch        *b_HLT_HIL1SingleMu3;   //!
   TBranch        *b_HLT_HIL3DoubleMuOpen_v1;
   TBranch        *b_HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy_v1;
   TBranch        *b_HLT_HIL3DoubleMuOpen_Mgt2_OS_v1;
   TBranch        *b_HLT_HIL3DoubleMuOpen_Mgt2_SS_v1;
   TBranch        *b_HLT_HIL3DoubleMuOpen_Mgt2_v1;
   TBranch        *b_HLT_HIL2DoubleMu0_NHitQ_v1;
   TBranch        *b_HLT_HIL2DoubleMu0_L1HighQL2NHitQ_v1;
   TBranch        *b_HLT_HIL2DoubleMu0_v1;   //!
   TBranch        *b_HLT_HIL2DoubleMu3_v1;   //!
   TBranch        *b_HLT_HIL1DoubleMuOpen_v1;
   TBranch        *b_HLT_HIL1DoubleMu0_HighQ_v1;
   TBranch        *b_HLT_HIL3Mu3_v1;
   TBranch        *b_HLT_HIL2Mu3_v1;   //!
   TBranch        *b_HLT_HIL2Mu7_v1;   //!
   TBranch        *b_HLT_HIL2Mu15_v1;   //!
   TBranch        *b_HLT_HIL3DoubleMuOpen_v2;
   TBranch        *b_HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy_v2;
   TBranch        *b_HLT_HIL3DoubleMuOpen_Mgt2_OS_v2;
   TBranch        *b_HLT_HIL3DoubleMuOpen_Mgt2_SS_v2;
   TBranch        *b_HLT_HIL3DoubleMuOpen_Mgt2_v2;
   TBranch        *b_HLT_HIL2DoubleMu0_NHitQ_v2;
   TBranch        *b_HLT_HIL2DoubleMu0_L1HighQL2NHitQ_v2;
   TBranch        *b_HLT_HIL2DoubleMu0_v2;   //!
   TBranch        *b_HLT_HIL2DoubleMu3_v2;   //!
   TBranch        *b_HLT_HIL1DoubleMuOpen_v2;
   TBranch        *b_HLT_HIL1DoubleMu0_HighQ_v2;
   TBranch        *b_HLT_HIL3Mu3_v2;
   TBranch        *b_HLT_HIL2Mu3_v2;   //!
   TBranch        *b_HLT_HIL2Mu7_v2;   //!
   TBranch        *b_HLT_HIL2Mu15_v2;   //!
   TBranch        *b_L1_DoubleMu3;   //!
   TBranch        *b_L1_DoubleMuOpen;   //!
   TBranch        *b_L1_DoubleMuOpen_BptxAND;   //!
   TBranch        *b_L1_SingleMu0;   //!
   TBranch        *b_L1_SingleMu10;   //!
   TBranch        *b_L1_SingleMu14;   //!
   TBranch        *b_L1_SingleMu20;   //!
   TBranch        *b_L1_SingleMu3;   //!
   TBranch        *b_L1_SingleMu3_BptxAND;   //!
   TBranch        *b_L1_SingleMu5;   //!
   TBranch        *b_L1_SingleMu7;   //!
   TBranch        *b_L1_SingleMuBeamHalo;   //!
   TBranch        *b_L1_SingleMuOpen;   //!

   HltTree(TCastorFile *f, bool castor = true, string dir = "hltanalysis/HltTree");
   virtual ~HltTree();
   virtual Int_t    GetEntry(Long64_t entry);
   virtual bool     Exceed();
   virtual void     Init(TTree *tree);
   virtual void     Show(Long64_t entry = -1);
};

HltTree::HltTree(TCastorFile *f, bool castor, string dir)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.

   if (castor) {
     if (f == 0) { std::cout << "Cannot load file\n"; }

//     string strdir = dir + "/HltTree";
     fChain = (TTree*)f->Get(dir.c_str());
     if (!fChain) { std::cout << "Cannot load HltTree\n"; }
     else Init(fChain);
   } else {
     std::cout << "Cannot load HltTree\n";
   }

}

HltTree::~HltTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t HltTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}

bool HltTree::Exceed()
{
  std::vector<string> exceedB;
  if (NrecoMuon > nmax) { exceedB.push_back("NrecoMuon"); }
  if (NohMuL2 > nmax) { exceedB.push_back("NohMuL2"); }
  if (NL1Mu > nmax) { exceedB.push_back("NL1Mu"); }
  if (recoNVrt > nmax) { exceedB.push_back("recoNVrt"); }

  if (exceedB.size() > 0) {
    for (vector<string>::size_type i=0; i<exceedB.size(); i++) {
      std::cout << exceedB[i] << endl;
    }
    return true;
  } else return false;
}

void HltTree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Npart", &Npart, &b_Npart);
   fChain->SetBranchAddress("Ncoll", &Ncoll, &b_Ncoll);
   fChain->SetBranchAddress("hiBin", &hiBin, &b_hiBin);
   fChain->SetBranchAddress("NrecoMuon", &NrecoMuon, &b_NrecoMuon);
   fChain->SetBranchAddress("recoMuonPt", &recoMuonPt, &b_recoMuonPt);
   fChain->SetBranchAddress("recoMuonPhi", &recoMuonPhi, &b_recoMuonPhi);
   fChain->SetBranchAddress("recoMuonEta", &recoMuonEta, &b_recoMuonEta);
   fChain->SetBranchAddress("recoMuonEt", &recoMuonEt, &b_recoMuonEt);
   fChain->SetBranchAddress("recoMuonE", &recoMuonE, &b_recoMuonE);
   fChain->SetBranchAddress("NohMuL2", &NohMuL2, &b_NohMuL2);
   fChain->SetBranchAddress("ohMuL2Pt", &ohMuL2Pt, &b_ohMuL2Pt);
   fChain->SetBranchAddress("ohMuL2Phi", &ohMuL2Phi, &b_ohMuL2Phi);
   fChain->SetBranchAddress("ohMuL2Eta", &ohMuL2Eta, &b_ohMuL2Eta);
   fChain->SetBranchAddress("ohMuL2Chg", &ohMuL2Chg, &b_ohMuL2Chg);
   fChain->SetBranchAddress("ohMuL2PtErr", &ohMuL2PtErr, &b_ohMuL2PtErr);
   fChain->SetBranchAddress("ohMuL2Dr", &ohMuL2Dr, &b_ohMuL2Dr);
   fChain->SetBranchAddress("ohMuL2Dz", &ohMuL2Dz, &b_ohMuL2Dz);
   fChain->SetBranchAddress("NohMuL3",&NohMuL3,&b_NohMuL3);
   fChain->SetBranchAddress("ohMuL3Pt",&ohMuL3Pt,&b_ohMuL3Pt);
   fChain->SetBranchAddress("ohMuL3Phi",&ohMuL3Phi,&b_ohMuL3Phi);
   fChain->SetBranchAddress("ohMuL3Eta",&ohMuL3Eta,&b_ohMuL3Eta);
   fChain->SetBranchAddress("ohMuL3Chg",&ohMuL3Chg,&b_ohMuL3Chg);
   fChain->SetBranchAddress("ohMuL3PtErr",&ohMuL3PtErr,&b_ohMuL3PtErr);
   fChain->SetBranchAddress("ohMuL3Dr",&ohMuL3Dr,&b_ohMuL3Dr);
   fChain->SetBranchAddress("ohMuL3Dz",&ohMuL3Dz,&b_ohMuL3Dz);
   fChain->SetBranchAddress("ohMuL3VtxZ",&ohMuL3VtxZ,&b_ohMuL3VtxZ);
   fChain->SetBranchAddress("ohMuL3Nhits",&ohMuL3Nhits,&b_ohMuL3Nhits);
   fChain->SetBranchAddress("ohMuL3NormChi2",&ohMuL3NormChi2,&b_ohMuL3NormChi2);
   fChain->SetBranchAddress("ohMuL3Ntrackerhits",&ohMuL3Ntrackerhits,&b_ohMuL3Ntrackerhits);
   fChain->SetBranchAddress("ohMuL3Nmuonhits",&ohMuL3Nmuonhits,&b_ohMuL3Nmuonhits);
   fChain->SetBranchAddress("NL1Mu", &NL1Mu, &b_NL1Mu);
   fChain->SetBranchAddress("L1MuPt", &L1MuPt, &b_L1MuPt);
   fChain->SetBranchAddress("L1MuE", &L1MuE, &b_L1MuE);
   fChain->SetBranchAddress("L1MuEta", &L1MuEta, &b_L1MuEta);
   fChain->SetBranchAddress("L1MuPhi", &L1MuPhi, &b_L1MuPhi);
   fChain->SetBranchAddress("L1MuIsol", &L1MuIsol, &b_L1MuIsol);
   fChain->SetBranchAddress("L1MuMip", &L1MuMip, &b_L1MuMip);
   fChain->SetBranchAddress("L1MuFor", &L1MuFor, &b_L1MuFor);
   fChain->SetBranchAddress("L1MuRPC", &L1MuRPC, &b_L1MuRPC);
   fChain->SetBranchAddress("L1MuQal", &L1MuQal, &b_L1MuQal);
   fChain->SetBranchAddress("recoNVrt", &recoNVrt, &b_NVrtx);
   fChain->SetBranchAddress("recoVrtX", &recoVrtX, &b_recoVrtX);
   fChain->SetBranchAddress("recoVrtY", &recoVrtY, &b_recoVrtY);
   fChain->SetBranchAddress("recoVrtZ", &recoVrtZ, &b_recoVrtZ);
   fChain->SetBranchAddress("recoVrtNtrk", &recoVrtNtrk, &b_recoVrtNtrk);
   fChain->SetBranchAddress("recoVrtChi2", &recoVrtChi2, &b_recoVrtChi2);
   fChain->SetBranchAddress("recoVrtNdof", &recoVrtNdof, &b_recoVrtNdof);
   fChain->SetBranchAddress("Run", &Run, &b_Run);
   fChain->SetBranchAddress("Event", &Event, &b_Event);
   fChain->SetBranchAddress("LumiBlock", &LumiBlock, &b_LumiBlock);
   fChain->SetBranchAddress("Bx", &Bx, &b_Bx);
   fChain->SetBranchAddress("Orbit", &Orbit, &b_Orbit);
   fChain->SetBranchAddress("AvgInstLumi", &AvgInstLumi, &b_AvgInstLumi);
   fChain->SetBranchAddress("HLT_HIL3DoubleMuOpen",&HLT_HIL3DoubleMuOpen,&b_HLT_HIL3DoubleMuOpen);
   fChain->SetBranchAddress("HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy",&HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy,&b_HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy);
   fChain->SetBranchAddress("HLT_HIL3DoubleMuOpen_Mgt2_OS",&HLT_HIL3DoubleMuOpen_Mgt2_OS,&b_HLT_HIL3DoubleMuOpen_Mgt2_OS);
   fChain->SetBranchAddress("HLT_HIL3DoubleMuOpen_Mgt2_SS",&HLT_HIL3DoubleMuOpen_Mgt2_SS,&b_HLT_HIL3DoubleMuOpen_Mgt2_SS);
   fChain->SetBranchAddress("HLT_HIL3DoubleMuOpen_Mgt2",&HLT_HIL3DoubleMuOpen_Mgt2,&b_HLT_HIL3DoubleMuOpen_Mgt2);
   fChain->SetBranchAddress("HLT_HIL2DoubleMu0_NHitQ",&HLT_HIL2DoubleMu0_NHitQ,&b_HLT_HIL2DoubleMu0_NHitQ);
   fChain->SetBranchAddress("HLT_HIL2DoubleMu0_L1HighQL2NHitQ",&HLT_HIL2DoubleMu0_L1HighQL2NHitQ,&b_HLT_HIL2DoubleMu0_L1HighQL2NHitQ);
   fChain->SetBranchAddress("HLT_HIL2DoubleMu0",&HLT_HIL2DoubleMu0,&b_HLT_HIL2DoubleMu0);
   fChain->SetBranchAddress("HLT_HIL2DoubleMu3",&HLT_HIL2DoubleMu3,&b_HLT_HIL2DoubleMu3);
   fChain->SetBranchAddress("HLT_HIL1DoubleMuOpen",&HLT_HIL1DoubleMuOpen,&b_HLT_HIL1DoubleMuOpen);
   fChain->SetBranchAddress("HLT_HIL1DoubleMu0_HighQ",&HLT_HIL1DoubleMu0_HighQ,&b_HLT_HIL1DoubleMu0_HighQ);
   fChain->SetBranchAddress("HLT_HIL3Mu3",&HLT_HIL3Mu3,&b_HLT_HIL3Mu3);
   fChain->SetBranchAddress("HLT_HIL2Mu3",&HLT_HIL2Mu3,&b_HLT_HIL2Mu3);
   fChain->SetBranchAddress("HLT_HIL2Mu7",&HLT_HIL2Mu7,&b_HLT_HIL2Mu7);
   fChain->SetBranchAddress("HLT_HIL2Mu15",&HLT_HIL2Mu15,&b_HLT_HIL2Mu15);
   fChain->SetBranchAddress("HLT_HIL1SingleMu3",&HLT_HIL1SingleMu3,&b_HLT_HIL1SingleMu3);
   fChain->SetBranchAddress("HLT_HIL3DoubleMuOpen_v1",&HLT_HIL3DoubleMuOpen_v1,&b_HLT_HIL3DoubleMuOpen_v1);
   fChain->SetBranchAddress("HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy_v1",&HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy_v1,&b_HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy_v1);
   fChain->SetBranchAddress("HLT_HIL3DoubleMuOpen_Mgt2_OS_v1",&HLT_HIL3DoubleMuOpen_Mgt2_OS_v1,&b_HLT_HIL3DoubleMuOpen_Mgt2_OS_v1);
   fChain->SetBranchAddress("HLT_HIL3DoubleMuOpen_Mgt2_SS_v1",&HLT_HIL3DoubleMuOpen_Mgt2_SS_v1,&b_HLT_HIL3DoubleMuOpen_Mgt2_SS_v1);
   fChain->SetBranchAddress("HLT_HIL3DoubleMuOpen_Mgt2_v1",&HLT_HIL3DoubleMuOpen_Mgt2_v1,&b_HLT_HIL3DoubleMuOpen_Mgt2_v1);
   fChain->SetBranchAddress("HLT_HIL2DoubleMu0_NHitQ_v1",&HLT_HIL2DoubleMu0_NHitQ_v1,&b_HLT_HIL2DoubleMu0_NHitQ_v1);
   fChain->SetBranchAddress("HLT_HIL2DoubleMu0_L1HighQL2NHitQ_v1",&HLT_HIL2DoubleMu0_L1HighQL2NHitQ_v1,&b_HLT_HIL2DoubleMu0_L1HighQL2NHitQ_v1);
   fChain->SetBranchAddress("HLT_HIL2DoubleMu0_v1",&HLT_HIL2DoubleMu0_v1,&b_HLT_HIL2DoubleMu0_v1);
   fChain->SetBranchAddress("HLT_HIL2DoubleMu3_v1",&HLT_HIL2DoubleMu3_v1,&b_HLT_HIL2DoubleMu3_v1);
   fChain->SetBranchAddress("HLT_HIL1DoubleMuOpen_v1",&HLT_HIL1DoubleMuOpen_v1,&b_HLT_HIL1DoubleMuOpen_v1);
   fChain->SetBranchAddress("HLT_HIL1DoubleMu0_HighQ_v1",&HLT_HIL1DoubleMu0_HighQ_v1,&b_HLT_HIL1DoubleMu0_HighQ_v1);
   fChain->SetBranchAddress("HLT_HIL3Mu3_v1",&HLT_HIL3Mu3_v1,&b_HLT_HIL3Mu3_v1);
   fChain->SetBranchAddress("HLT_HIL2Mu3_v1",&HLT_HIL2Mu3_v1,&b_HLT_HIL2Mu3_v1);
   fChain->SetBranchAddress("HLT_HIL2Mu7_v1",&HLT_HIL2Mu7_v1,&b_HLT_HIL2Mu7_v1);
   fChain->SetBranchAddress("HLT_HIL2Mu15_v1",&HLT_HIL2Mu15_v1,&b_HLT_HIL2Mu15_v1);
   fChain->SetBranchAddress("HLT_HIL3DoubleMuOpen_v2",&HLT_HIL3DoubleMuOpen_v2,&b_HLT_HIL3DoubleMuOpen_v2);
   fChain->SetBranchAddress("HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy_v2",&HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy_v2,&b_HLT_HIL3DoubleMuOpen_Mgt2_OS_NoCowboy_v2);
   fChain->SetBranchAddress("HLT_HIL3DoubleMuOpen_Mgt2_OS_v2",&HLT_HIL3DoubleMuOpen_Mgt2_OS_v2,&b_HLT_HIL3DoubleMuOpen_Mgt2_OS_v2);
   fChain->SetBranchAddress("HLT_HIL3DoubleMuOpen_Mgt2_SS_v2",&HLT_HIL3DoubleMuOpen_Mgt2_SS_v2,&b_HLT_HIL3DoubleMuOpen_Mgt2_SS_v2);
   fChain->SetBranchAddress("HLT_HIL3DoubleMuOpen_Mgt2_v2",&HLT_HIL3DoubleMuOpen_Mgt2_v2,&b_HLT_HIL3DoubleMuOpen_Mgt2_v2);
   fChain->SetBranchAddress("HLT_HIL2DoubleMu0_NHitQ_v2",&HLT_HIL2DoubleMu0_NHitQ_v2,&b_HLT_HIL2DoubleMu0_NHitQ_v2);
   fChain->SetBranchAddress("HLT_HIL2DoubleMu0_L1HighQL2NHitQ_v2",&HLT_HIL2DoubleMu0_L1HighQL2NHitQ_v2,&b_HLT_HIL2DoubleMu0_L1HighQL2NHitQ_v2);
   fChain->SetBranchAddress("HLT_HIL2DoubleMu0_v2",&HLT_HIL2DoubleMu0_v2,&b_HLT_HIL2DoubleMu0_v2);
   fChain->SetBranchAddress("HLT_HIL2DoubleMu3_v2",&HLT_HIL2DoubleMu3_v2,&b_HLT_HIL2DoubleMu3_v2);
   fChain->SetBranchAddress("HLT_HIL1DoubleMuOpen_v2",&HLT_HIL1DoubleMuOpen_v2,&b_HLT_HIL1DoubleMuOpen_v2);
   fChain->SetBranchAddress("HLT_HIL1DoubleMu0_HighQ_v2",&HLT_HIL1DoubleMu0_HighQ_v2,&b_HLT_HIL1DoubleMu0_HighQ_v2);
   fChain->SetBranchAddress("HLT_HIL3Mu3_v2",&HLT_HIL3Mu3_v2,&b_HLT_HIL3Mu3_v2);
   fChain->SetBranchAddress("HLT_HIL2Mu3_v2",&HLT_HIL2Mu3_v2,&b_HLT_HIL2Mu3_v2);
   fChain->SetBranchAddress("HLT_HIL2Mu7_v2",&HLT_HIL2Mu7_v2,&b_HLT_HIL2Mu7_v2);
   fChain->SetBranchAddress("HLT_HIL2Mu15_v2",&HLT_HIL2Mu15_v2,&b_HLT_HIL2Mu15_v2);
   fChain->SetBranchAddress("L1_DoubleMu3", &L1_DoubleMu3, &b_L1_DoubleMu3);
   fChain->SetBranchAddress("L1_DoubleMuOpen", &L1_DoubleMuOpen, &b_L1_DoubleMuOpen);
   fChain->SetBranchAddress("L1_DoubleMuOpen_BptxAND", &L1_DoubleMuOpen_BptxAND, &b_L1_DoubleMuOpen_BptxAND);
   fChain->SetBranchAddress("L1_SingleMu0", &L1_SingleMu0, &b_L1_SingleMu0);
   fChain->SetBranchAddress("L1_SingleMu10", &L1_SingleMu10, &b_L1_SingleMu10);
   fChain->SetBranchAddress("L1_SingleMu14", &L1_SingleMu14, &b_L1_SingleMu14);
   fChain->SetBranchAddress("L1_SingleMu20", &L1_SingleMu20, &b_L1_SingleMu20);
   fChain->SetBranchAddress("L1_SingleMu3", &L1_SingleMu3, &b_L1_SingleMu3);
   fChain->SetBranchAddress("L1_SingleMu3_BptxAND", &L1_SingleMu3_BptxAND, &b_L1_SingleMu3_BptxAND);
   fChain->SetBranchAddress("L1_SingleMu5", &L1_SingleMu5, &b_L1_SingleMu5);
   fChain->SetBranchAddress("L1_SingleMu7", &L1_SingleMu7, &b_L1_SingleMu7);
   fChain->SetBranchAddress("L1_SingleMuBeamHalo", &L1_SingleMuBeamHalo, &b_L1_SingleMuBeamHalo);
   fChain->SetBranchAddress("L1_SingleMuOpen", &L1_SingleMuOpen, &b_L1_SingleMuOpen);
}


void HltTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
