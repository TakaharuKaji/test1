Double_t GetPara(TString inputfilename) {
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

  //TF1 *f1 = new TF1("f1", "[0] + [1] * x",min, max);
  TF1 *f = new TF1("name","gaus",0,3000);
  Hist01->Fit("name","","",800,850);
  Double_t p1 = f->GetParameter(1);
  cout<<p1<<endl;
  Hist01->Draw();
  return p1;
}

void al01(){
  gROOT->SetBatch(1);
  Int_t N = 9;
  vector<Double_t> v(N);
  for (Int_t i = 1; i <= N; i++){
    TString filename = Form("data/ta0%d.root",i);
    v.at(i-1) = GetPara(filename);
  }

  for (int i = 0; i < v.size(); i++)
  {
      std::cout << v.at(i) << "\n";
  }
}
