{
  //Reset ROOT
  gROOT->Reset();
  
  gROOT->LoadMacro("MyAna.C+");

  TChain chain("data");

  chain.Add("mc_ttbar.root");

  TFile *hfile = new TFile("mva_ttbar.root","RECREATE","ttbar MC");

  MyAna t((TTree *)chain, 6);
  t.Loop();
  t.Terminate();

  hfile->Write();

}
