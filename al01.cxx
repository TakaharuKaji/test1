Double_t GetPara(TString inputfilename) {
  TFile *file = new TFile(inputfilename, "read");
  TTree *tree = (TTree*)file->Get("tree");
  if (tree==nullptr) {
    return 0;
  }
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
  Hist01->Fit("name","","",842,4000); //842->一番0点に近づいた画像から判断
  Double_t p1 = f->GetParameter(1);
  cout<<p1<<endl;
  TCanvas *cl = new TCanvas("c1", "c1", 400, 300);
  Hist01->GetYaxis()->SetRangeUser(0,1200);
  Hist01->GetXaxis()->SetRangeUser(500,3500);
  Hist01->Draw();
  inputfilename.ReplaceAll("root","png");
  TString figname = Form("%s",inputfilename.Data());
  cl -> SaveAs(figname);
  return p1;
}

Double_t NumPhoton(Double_t adc){
  Double_t a = 0.0129; //エクセルで計算
  Double_t b = -10.57; //エクセルで計算
  Int_t NumP = (a * adc) + b; //adcの値を光子の数に変換
  return NumP;
}

Double_t EnergyPhoton(Int_t NumP){
  Double_t h = 6.626e-34; //プランク定数
  Double_t nu = 520.0e+12; //使用した緑色LEDの振動数
  Double_t Energy = h * nu * NumP; //光子一つのエネルギーに個数を乗じる
  return Energy;
}

void al01(){
  //gROOT->SetBatch(1);
  Int_t N =20 ;
  vector<Double_t> v(N);
  vector<Double_t> Num(N);
  vector<Double_t> Energy(N);
  vector<Double_t> x(N);

  for (Int_t i = 1; i <= N; i++){
    TString filename = Form("data/sokutei_2/sokutei_%d.root",i);
    v.at(i-1) = GetPara(filename);
    Num.at(i-1) = NumPhoton(v.at(i-1));
    Energy.at(i-1) = EnergyPhoton(v.at(i-1));
    x.at(i-1) = 58.16 +(i-1)*2;

  }

  TGraph *tgl = new TGraph(v.size(), &(x.at(0)), &(Energy.at(0)));
  tgl->SetMarkerStyle(8);
  tgl->Draw("AP");

  for (int i = 0; i < v.size(); i++){
      std::cout << "Vadc:"<< v.at(i) << ", Num:" << Num.at(i) << ", Energy:" << Energy.at(i) << "\n";
  }
}
