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

Double_t NumPhoton(adc){
  Double_t a = 0.0129; //エクセルで計算
  Double_t b = -10.57; //エクセルで計算
  Int_t NumP = (a * adc) + b; //adcの値を光子の数に変換
  return NumP;
}

Double_t EnergyPhoton(NumP){
  Double_t h = 6.626e-34; //プランク定数
  Double_t nu = 600.0e+12; //使用した緑色LEDの振動数
  Double_t Energy = h * nu * NumP; //光子一つのエネルギーに個数を乗じる
  return Energy;
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
