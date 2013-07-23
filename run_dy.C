{
  //Reset ROOT
  gROOT->Reset();
  
  gROOT->LoadMacro("MyAna.C+");

  TChain chain("data");

  chain.Add("mc_dy.root");

  TFile *hfile = new TFile("mva_dy.root","RECREATE","dy MC");

  MyAna t((TTree *)chain, 23);
  t.Loop();
  t.Terminate();

  hfile->Write();

}
