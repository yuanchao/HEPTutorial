{
  //Reset ROOT
  gROOT->Reset();
  
  gROOT->LoadMacro("MyAna.C+");

  TChain chain("data");

  chain.Add("data.root");

  TFile *hfile = new TFile("mva_data.root","RECREATE","data MC");

  MyAna t((TTree *)chain);
  t.Loop();
  t.Terminate();

  hfile->Write();

}
