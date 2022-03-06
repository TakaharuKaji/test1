void macro_skm(TString inputfilename) {
  TFile *file = new TFile(inputfilename, "read");
  TFile *tree = (TTree*)file->Get("tree");

  Double_t adc[32]
  tree->SetBranchAddress("adc", &adc);

  const Int_t N = tin->GetEntries();
  for (Int_t ienty = 0; ientry < N; ientry++){
    tree->GetEntry(ienty);
    cout<<ientry<<"  "<<adc[30]<<endl;
  }
}
