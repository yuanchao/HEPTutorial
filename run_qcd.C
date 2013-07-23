{
  //Reset ROOT
  gROOT->Reset();
  
  gROOT->LoadMacro("MyAna.C+");

  TChain chain("data");

  chain.Add("mc_qcd.root");

  TFile *hfile = new TFile("mva_qcd.root","RECREATE","qcd MC");

  MyAna t((TTree *)chain, 21);
  t.Loop();
  t.Terminate();

  hfile->Write();

}
