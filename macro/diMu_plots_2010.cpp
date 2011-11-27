#ifndef MATCHMU
#define MATCHMU
#include "matchMu.h"
#include "matchMu_tree.h"
#endif

#include <TClonesArray.h>
#include <TLorentzVector.h>
#include <TSystem.h>

using namespace std;

int diMu_plots_2010() {

  int MASS = 20;

	char title[256];
	char sub_title[256];

	char* particle_names[] = {"Jpsi","Upsilon","Z"};
	
  TFile *output = new TFile("2010_histos.root","recreate");
  output->cd();

  // Histograms
  TH1F *SingleGlb_Eta_2010[3];
  TH1F *SingleGlb_Phi_2010[3];
  TH1F *SingleGlb_Pt_2010[3];
  for (int i=0; i<3; i++) {
    sprintf(title,"SingleGlb_eta_2010_%s",particle_names[i]);
    sprintf(sub_title,"%s;#eta;counts",title);
    SingleGlb_Eta_2010[i] = new TH1F(title,sub_title,ETA,-2.4,2.4);
    sprintf(title,"SingleGlb_phi_2010_%s",particle_names[i]);
    sprintf(sub_title,"%s;#phi;counts",title);
    SingleGlb_Phi_2010[i] = new TH1F(title,sub_title,PHI,-PI,PI);
    sprintf(title,"SingleGlb_pt_2010_%s",particle_names[i]);
    sprintf(sub_title,"%s;p_{T};counts",title);
    SingleGlb_Pt_2010[i] = new TH1F(title,sub_title,60,0,60);	
  }

  TH2F *DoubleGlb_Ypt_2010 = new TH2F("DoubleGlb_ypt_2010","DoubleGlb_ypt_2010;double mu y;double mu p_{T}",ETA,-3.0,3.0,40,0,40);
  TH1F *DoubleGlb_Mass_2010 = new TH1F("DoubleGlb_mass_2010","DoubleGlb_mass_2010;double mu mass;counts",110,0,110);
  TH1F *DoubleGlb_Y_2010 = new TH1F("DoubleGlb_y_2010","DoubleGlb_y_2010;double mu y;counts",ETA,-3.0,3.0);
  TH1F *DoubleGlb_Pt_2010 = new TH1F("DoubleGlb_pt_2010","DoubleGlb_pt_2010;double mu p_{T};counts",40,0,40);
  TH1F *DoubleGlb_Phi_2010 = new TH1F("DoubleGlb_phi_2010","DoubleGlb_phi_2010;double mu #phi;counts",PHI,-PI,PI);

/*  for (int i=0; i<3; i++) {
    sprintf(title,"DoubleGlb_ypt_2010_%s",particle_names[i]);
    sprintf(sub_title,"%s;double mu y;double mu p_{T}",title);
    DoubleGlb_Ypt_2010[i]= new TH2F(title,sub_title,ETA,-3.0,3.0,40,0,40);
    sprintf(title,"DoubleGlb_mass_2010_%s",particle_names[i]);
    sprintf(sub_title,"%s;double mu mass;counts",title);
    if (i<2) DoubleGlb_Mass_2010[i]= new TH1F(title,sub_title,MASS,0,20);
    else DoubleGlb_Mass_2010[i]= new TH1F(title,sub_title,MASS,80,100);
    sprintf(title,"DoubleGlb_y_2010_%s",particle_names[i]);
    sprintf(sub_title,"%s;double mu y;counts",title);
    DoubleGlb_Y_2010[i]= new TH1F(title,sub_title,ETA,-3.0,3.0);
    sprintf(title,"DoubleGlb_pt_2010_%s",particle_names[i]);
    sprintf(sub_title,"%s;double mu p_{T};counts",title);
    DoubleGlb_Pt_2010[i]= new TH1F(title,sub_title,PT,0,20);
    sprintf(title,"DoubleGlb_phi_2010_%s",particle_names[i]);
    sprintf(sub_title,"%s;double mu phi;counts",title);
    DoubleGlb_Phi_2010[i]= new TH1F(title,sub_title,PHI,-PI,PI);
  }*/

  TFile *input = new TFile("./Histos_OniaSkim_ReReco_v13_h3_sum.root");

  TTree *Tree = (TTree*)input->Get("myTree");

  Int_t           Reco_QQ_sign[20];   //[Reco_QQ_size]
  TClonesArray    *Reco_QQ_4mom;
  TClonesArray    *Reco_QQ_mupl_4mom;
  TClonesArray    *Reco_QQ_mumi_4mom;
  Int_t           Reco_QQ_size;
  
  TBranch        *b_Reco_QQ_size;   //!
  TBranch        *b_Reco_QQ_sign;   //!
  TBranch        *b_Reco_QQ_4mom;   //!
  TBranch        *b_Reco_QQ_mupl_4mom;   //!
  TBranch        *b_Reco_QQ_mumi_4mom;   //!


  TLorentzVector* JP= new TLorentzVector;
  TLorentzVector* m1P= new TLorentzVector;
  TLorentzVector* m2P= new TLorentzVector;

  Reco_QQ_4mom = 0;
  Reco_QQ_mupl_4mom = 0;
  Reco_QQ_mumi_4mom = 0;

  Tree->SetBranchAddress("Reco_QQ_size", &Reco_QQ_size, &b_Reco_QQ_size);
  Tree->SetBranchAddress("Reco_QQ_sign", Reco_QQ_sign, &b_Reco_QQ_sign);
  Tree->SetBranchAddress("Reco_QQ_4mom", &Reco_QQ_4mom, &b_Reco_QQ_4mom);
  Tree->SetBranchAddress("Reco_QQ_mupl_4mom", &Reco_QQ_mupl_4mom, &b_Reco_QQ_mupl_4mom);
  Tree->SetBranchAddress("Reco_QQ_mumi_4mom", &Reco_QQ_mumi_4mom, &b_Reco_QQ_mumi_4mom);

  int Jq;

  for (int ev=0; ev<Tree->GetEntries(); ++ev) {
    if (ev%5000==0) cout << ">>>>> EVENT " << ev << endl;
    
    Tree->GetEntry(ev);
    for (int i=0; i<Reco_QQ_size; ++i) {
      JP = (TLorentzVector*)Reco_QQ_4mom->At(i);
      m1P = (TLorentzVector*)Reco_QQ_mupl_4mom->At(i);
      m2P = (TLorentzVector*)Reco_QQ_mumi_4mom->At(i);
      Jq = Reco_QQ_sign[i];

      double theMass =JP->M();
      if (theMass > 3.0 && theMass < 3.2 && Jq == 0) {
        DoubleGlb_Ypt_2010->Fill(JP->Rapidity(),JP->Pt());
        DoubleGlb_Mass_2010->Fill(JP->M());
        DoubleGlb_Y_2010->Fill(JP->Rapidity());
        DoubleGlb_Pt_2010->Fill(JP->Pt());
        DoubleGlb_Phi_2010->Fill(JP->Phi());

	      SingleGlb_Eta_2010[0]->Fill(m1P->Eta());
	      SingleGlb_Eta_2010[0]->Fill(m2P->Eta());
	      SingleGlb_Pt_2010[0]->Fill(m1P->Pt());
	      SingleGlb_Pt_2010[0]->Fill(m2P->Pt());
	      SingleGlb_Phi_2010[0]->Fill(m1P->Phi());
	      SingleGlb_Phi_2010[0]->Fill(m2P->Phi());
      }

      if (theMass > 9 && theMass < 10 && Jq == 0) {
        DoubleGlb_Ypt_2010->Fill(JP->Rapidity(),JP->Pt());
        DoubleGlb_Mass_2010->Fill(JP->M());
        DoubleGlb_Y_2010->Fill(JP->Rapidity());
        DoubleGlb_Pt_2010->Fill(JP->Pt());
        DoubleGlb_Phi_2010->Fill(JP->Phi());

	      SingleGlb_Eta_2010[1]->Fill(m1P->Eta());
	      SingleGlb_Eta_2010[1]->Fill(m2P->Eta());
	      SingleGlb_Pt_2010[1]->Fill(m1P->Pt());
	      SingleGlb_Pt_2010[1]->Fill(m2P->Pt());
	      SingleGlb_Phi_2010[1]->Fill(m1P->Phi());
	      SingleGlb_Phi_2010[1]->Fill(m2P->Phi());
      }

      if (theMass > 85 && theMass < 95 && Jq == 0) {
        DoubleGlb_Ypt_2010->Fill(JP->Rapidity(),JP->Pt());
        DoubleGlb_Mass_2010->Fill(JP->M());
        DoubleGlb_Y_2010->Fill(JP->Rapidity());
        DoubleGlb_Pt_2010->Fill(JP->Pt());
        DoubleGlb_Phi_2010->Fill(JP->Phi());

	      SingleGlb_Eta_2010[2]->Fill(m1P->Eta());
	      SingleGlb_Eta_2010[2]->Fill(m2P->Eta());
	      SingleGlb_Pt_2010[2]->Fill(m1P->Pt());
	      SingleGlb_Pt_2010[2]->Fill(m2P->Pt());
	      SingleGlb_Phi_2010[2]->Fill(m1P->Phi());
	      SingleGlb_Phi_2010[2]->Fill(m2P->Phi());
      }

    }
  }


  output->Write();
  output->Close();


  return 0;
}
