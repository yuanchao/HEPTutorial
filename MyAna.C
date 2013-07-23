#define MyAna_cxx
#include "MyAna.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void MyAna::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L MyAna.C
//      Root > MyAna t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      EventSum = EventSum + 1.; //EventWeight;

      if(triggerIsoMu24!=1) continue;

      MET_pt = sqrt(MET_px*MET_px+MET_py*MET_py);
      HT = 0;
      NBJet =0;

      Jet_Pt[0]=Jet_Pt[1]=0;
      Electron_Pt[0]=Electron_Pt[1]=0;
      Muon_Pt[0]=Muon_Pt[1]=0;

      for(int it=0; it < NJet; it++){
	Jet_Pt[it] = sqrt(Jet_Px[it]*Jet_Px[it]+Jet_Py[it]*Jet_Py[it]);

	HT += Jet_Pt[it];
	if(Jet_Pt[it] > 30. && Jet_btag[it] > 2.1) NBJet++;
      }

      for(int it=0; it < NElectron; it++){
	Electron_Pt[it] = sqrt(Electron_Px[it]*Electron_Px[it]+
			       Electron_Py[it]*Electron_Py[it]);
	HT += Electron_Pt[it];
      }

      for(int it=0; it < NMuon; it++){
	Muon_Pt[it] = sqrt(Muon_Px[it]*Muon_Px[it]+
			   Muon_Py[it]*Muon_Py[it]);
	HT += Muon_Pt[it];
      }

      mvaTree->Fill();
   }
}

void MyAna::Terminate()
{
   cout << "\n\nVoila! C'est fini.\n";
   cout << "Total events: " << EventSum << endl;
}
