{
  //Reset ROOT
  gROOT->Reset();
  
  gROOT->LoadMacro("MyAna.C+");

  TChain chain("data");

  chain.Add("mc_wjets.root");

  TFile *hfile = new TFile("mva_wjets.root","RECREATE","wjets MC");

  MyAna t((TTree *)chain, 24);
  t.Loop();
  t.Terminate();

  hfile->Write();

}
