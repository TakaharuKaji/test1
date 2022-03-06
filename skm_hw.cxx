void skm_hw(/* arguments */) {
  cout << "Hello World" << endl;
  int a=2;
  int b;
  b = a+1;
  int c = a+b;
  cout << c << endl;
  TH1D* Hist01 = new TH1D("h1","h1",300,-15,15);//ルート上の名前,タイトル,ビンの数,下限,上限//
  for(int i = 0; i<100;i++){
    Hist01->Fill(i/10.0);
  }
  Hist01->Draw();
  /* code */
}
