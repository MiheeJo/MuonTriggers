#include <TProfile.h>
#include <TROOT.h>
#include <TNtuple.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <sstream>

void draw2D(){
    TFile* inf = TFile::Open("rfio:/castor/cern.ch/user/m/miheejo/HIMuTrig/HAZS/hazsv2-run152791to152957-unfiltered-jetoh-v1.root");

    const int nTrig = 2;
    string triggers[nTrig] = {"HLT_HIL1SingleMu5","HLT_HIL2Mu3"};
    string vers[4] = {"hiHF","hiBin","Ncharged","hiNtracks"};

    double bins [4] = {170,40,240,140};
    double limits[4] = {170000,40,24000,1400};

    TCanvas* c1 = new TCanvas("c1","c1",1200,800);
    c1->Divide(2,2);
    TNtuple* nt = (TNtuple*)inf->Get("hltanalysis/HltTree");
    TProfile* prof[4];

    for(int trig=0; trig < nTrig; trig++){
      for(int i=0; i<4 ; i++){
          c1->cd(i+1);
          stringstream stmp;
          stmp.str(""); stmp << "pro" << vers[i].c_str();
          prof[i] = new TProfile(stmp.str().c_str(),Form(";%s;%s",vers[i].data(),triggers[trig].data()),bins[i],0,limits[i]);
          nt->SetAlias("trigger",triggers[trig].data());
          nt->SetAlias("versus",vers[i].data());
          stmp.str(""); stmp << "trigger:versus>>pro" << vers[i].c_str();
          nt->Draw(stmp.str().c_str(),"","prof");
//          nt->Draw("trigger:versus>>p1","","prof");
      }
      // save the plot current directory
      c1->Print(Form("%s.png",triggers[trig].data()));
      for (int i=0; i<4; i++) delete prof[i];
    }
}
