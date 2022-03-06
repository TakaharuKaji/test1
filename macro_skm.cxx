void macro_skm(TString inputfilename) {
  TFile *file = new TFile(inputfilename, "read");
  TTree *tree = (TTree*)file->Get("tree");

  Double_t VadcHigh[64];
  tree->SetBranchAddress("VadcHigh", &VadcHigh);

  const Int_t N = tree->GetEntries();
  for (Int_t ientry = 0; ientry < N; ientry++){
    tree->GetEntry(ientry);
    //cout<<ientry<<"  "<<VadcHigh[44]<<endl;
  }
}
