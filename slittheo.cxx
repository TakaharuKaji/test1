<<<<<<< HEAD
void plot_integral(Double_t slit_width, Int_t step){
    Double_t a, b, k, R, I0;
=======
void slittheo(){
    Double_t a, b, k, R;
>>>>>>> ab21fdbfc264bbd52b2370dd435b09424ca521b0

    a = 0.04 ;
    b = 0.02 ;
    k = 2*TMath::Pi()/(5.2*0.0001);
    R = 295;

    TF1 *theo = new TF1("theo","(sin([0]*x)*cos([1]*x)/x)**2",-10,10);
    //TF1 *theo = new TF1("theo","(cos([1]*x))**2",-10,10);  //理論曲線、単スリット幅ゼロ近似
    theo->SetParameter(0,k*b/2/R);
    theo->SetParameter(1,k*a/2/R);
    theo->GetXaxis()->SetTitle("[mm]"); //x軸ラベル 
    gStyle->SetOptTitle(0);//Title を書かない場合、０を入れる（１を入れれば書いてくれる）
	//theo->SetXaxis("(mm");
    //theo->SetStats(0);

    //theo->Draw();  //理論曲線

<<<<<<< HEAD

=======
    //理論曲線の微分
>>>>>>> ab21fdbfc264bbd52b2370dd435b09424ca521b0
    for(Int_t i = 0; i < 100000; i++){
        Double_t x = -10 + 2*i*0.0001;
        Double_t deriv = theo->Derivative(x);
        if(-0.00002 < deriv && deriv < 0.00002){
<<<<<<< HEAD
            //cout << x << " " << deriv << endl;  //微分係数が十分小さい時の値を表示
        }
=======
            // cout << x << " " << deriv << endl;  //微分係数が十分小さい時の値を表示
        } 
>>>>>>> ab21fdbfc264bbd52b2370dd435b09424ca521b0
    }

    TGraph *tg = new TGraph();

<<<<<<< HEAD
    TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);

    for(Int_t i = 0; i < 200000; i++){
        Double_t x = -20 + 2*i*0.0001;
        Double_t integ = theo->Integral(x-(slit_width/2.0), x+(slit_width/2.0));
=======
    //MPPC幅の分を積分
    for(Int_t i = 0; i < 100000; i++){
        Double_t x = -10 + 2*i*0.0001;
        Double_t integ = theo->Integral(x-0.65, x+0.65);
>>>>>>> ab21fdbfc264bbd52b2370dd435b09424ca521b0
        tg->SetPoint(i, x, integ);

    }
    //Hist01->GetYaxis()->SetRangeUser(0,1200);
    //Hist01->GetXaxis()->SetRangeUser(500,3500);
    //Hist01->Draw();
    TString inputfilename = "slittheo_fig/fig";
    //inputfilename.ReplaceAll(".root","_Ene.png");
    TString figname = Form("%s_%d.png",inputfilename.Data(),step);

<<<<<<< HEAD
    tg -> Draw("AP");  //MPPC幅を考慮した理論曲線
    //tg->GetYaxis()->SetRangeUser(0,0.2);
    tg->GetXaxis()->SetRangeUser(-20,20);
=======
    //さらに微分
    TGraph *tg2 = new TGraph();
    for(Int_t i = 0; i < 100000; i++){
        Double_t y = -10 + 2*i*0.0001;
        Double_t integ2 = theo->Integral(y-0.65, y+0.65);
        Double_t integ3 = theo->Integral(y-0.65+0.002, y+0.65+0.002);
        tg2->SetPoint(i, y, (integ3-integ2)/0.0002);
        if(-6<y && y<6 && -0.0000002 < integ3-integ2 && integ3-integ2 < 0.0000002){
        cout << y << " " << integ3-integ2 << endl ;   //微分係数が十分小さい時の値を表示(xの範囲限定)
        }
    }  

    tg->Draw("AP");  //MPPC幅を考慮した理論曲線
>>>>>>> ab21fdbfc264bbd52b2370dd435b09424ca521b0

    c1 -> SaveAs(figname);
}

//mm単位
//数値計算

void slittheo(){
  Double_t slit_width = 0.1;
  for(Int_t i = 0; i < 10; i++){
    Int_t step = 1;
    cout << slit_width << endl;
    plot_integral(slit_width, i);
    slit_width += 0.1;
  }
}
