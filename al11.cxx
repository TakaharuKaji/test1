
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

Double_t GetPara(TString inputfilename, Double_t x) {
  TFile *file = new TFile(inputfilename, "read");
  TTree *tree = (TTree*)file->Get("tree");
  if (tree==nullptr) {
    return 0;
  }
  int VadcHigh[64];
  tree->SetBranchAddress("VadcHigh", &VadcHigh);

  TH1D* Hist01 = new TH1D("h1","h1",1000,0,4096);//ルート上の名前,タイトル,ビンの数,下限,上限//

  const Int_t N = tree->GetEntries();
  Int_t count = 0;
  Double_t sum = 0;
  for (Int_t ientry = 0; ientry < N; ientry++){
    tree->GetEntry(ientry);
    Double_t Num = NumPhoton(VadcHigh[44]);
    Double_t Ene = EnergyPhoton(Num);
    Hist01->Fill(Num);
    if (VadcHigh[44]>854) {  //カウントするADCの下限
      sum += Num;
      count += 1;
    }
    //cout<<ientry<<"  "<<VadcHigh[44]<<endl;
  }
  //cout << count << endl;
  return count;

  Double_t Ave = sum/count;
  //cout<<Ave<<endl;

  //TCanvas *cl = new TCanvas("c1", "c1", 800, 600);
  //Hist01->GetYaxis()->SetRangeUser(0,1200);
  //Hist01->GetXaxis()->SetRangeUser(500,3500);
  //Hist01->Draw();
  //inputfilename.ReplaceAll(".root","_Num.png");
  //TString figname = Form("%s",inputfilename.Data());
  //cl -> SaveAs(figname);
  //return Ave;
}

void al11(){
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
    Double_t xi = start_pos + (i-1)*step;
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
  tgl->SetTitle(" ;[mm];count");  //title

  Double_t a, b, k, R;

    a = 0.04 ;
    b = 0.02 ;
    k = 2*TMath::Pi()/(5.2*0.0001);
    R = 295;
    
    TF1 *theo = new TF1("theo","[2]*(sin([0]*(x-[3]))*cos([1]*(x-[3]))/(x-[3]))**2+[4]",68,92);
    theo->SetParameter(0,k*b/2/R);
    theo->SetParameter(1,k*a/2/R);
    theo->SetParameter(2,100000);
    theo->SetParameter(3,78);
    theo->SetParameter(4,7500);

    TGraph *theor = new TGraph(theo);
    theor->SetMarkerColor(kRed);
    theor->SetMarkerStyle(8);

  TMultiGraph *mg = new TMultiGraph();
  mg->Add(tgl);
  mg->Add(theor);

  mg->Draw("AP");

  
}
