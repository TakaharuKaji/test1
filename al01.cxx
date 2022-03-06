void al01(TString inputfilename) {
  TFile *file = new TFile(inputfilename, "read");
  TTree *tree = (TTree*)file->Get("tree");

  int VadcHigh[64];
  tree->SetBranchAddress("VadcHigh", &VadcHigh);

  TH1D* Hist01 = new TH1D("h1","h1",1000,0,4096);//ルート上の名前,タイトル,ビンの数,下限,上限//

  const Int_t N = tree->GetEntries();
  for (Int_t ientry = 0; ientry < N; ientry++){
    tree->GetEntry(ientry);
    Hist01->Fill(VadcHigh[44]);
    //cout<<ientry<<"  "<<VadcHigh[44]<<endl;
  }
  Hist01->Draw();

}
