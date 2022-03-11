Double_t GetPara(TString inputfilename, Double_t x) {
  TFile *file = new TFile(inputfilename, "read");
  TTree *tree = (TTree*)file->Get("tree");
  if (tree==nullptr) {
    return 0;
  }
  int VadcHigh[64];
  tree->SetBranchAddress("VadcHigh", &VadcHigh);
  TString title = Form("x= %5.2f mm",x);
  cout << title << endl;
  TH1D* Hist01 = new TH1D("h1",title,1000,0,4096);//ルート上の名前,タイトル,ビンの数,下限,上限//

  const Int_t N = tree->GetEntries();
  Int_t count = 0;
  Double_t sum = 0;
  for (Int_t ientry = 0; ientry < N; ientry++){
    tree->GetEntry(ientry);
    Hist01->Fill(VadcHigh[44]);
    if (VadcHigh[44]>820) {
      sum += VadcHigh[44];
      count += 1;
    }
    //cout<<ientry<<"  "<<VadcHigh[44]<<endl;
  }
  Double_t Ave = sum/count;
  //cout<<Ave<<endl;

  TCanvas *cl = new TCanvas("c1", "c1", 400, 300);
  Hist01->GetYaxis()->SetRangeUser(0,25000);
  Hist01->GetXaxis()->SetRangeUser(500,1300);
  Hist01->Draw();
  inputfilename.ReplaceAll("root","png");
  TString figname = Form("%s",inputfilename.Data());
  cl -> SaveAs(figname);
  return Ave;
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

void al02(){
  //gROOT->SetBatch(1);
  Int_t N =60 ; //測定データ数
  Double_t start_pos = 68.0;//スタート位置
  Double_t step = 0.4;//刻み幅
  vector<Double_t> v={};
  vector<Double_t> Num={};
  vector<Double_t> Energy={};
  vector<Double_t> x={};

  for (Int_t i = 1; i <= N; i++){
    TString filename = Form("data/sokutei_20/sokutei_%d.root",i);
    Double_t xi = start_pos +(i-1)*step;
    Double_t para = GetPara(filename, xi);
    if (para > 0){
      v.push_back(para);
      x.push_back(xi);
      Int_t vlength = v.size();
      Num.push_back(NumPhoton(v.at(vlength-1)));
      Energy.push_back(EnergyPhoton(v.at(vlength-1)));
    }
  }

  TGraph *tgl = new TGraph(v.size(), &(x.at(0)), &(v.at(0)));
  tgl->SetMarkerStyle(8);
  tgl->Draw("AP");

  for (int i = 0; i < v.size(); i++){
      std::cout << "Vadc:"<< v.at(i) << ", Num:" << Num.at(i) << ", Energy:" << Energy.at(i) << "\n";
  }
}
