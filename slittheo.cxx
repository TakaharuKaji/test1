void slittheo(){
    Double_t a, b, k, R;

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

    //理論曲線の微分
    for(Int_t i = 0; i < 100000; i++){
        Double_t x = -10 + 2*i*0.0001;
        Double_t deriv = theo->Derivative(x);
        if(-0.00002 < deriv && deriv < 0.00002){
            // cout << x << " " << deriv << endl;  //微分係数が十分小さい時の値を表示
        } 
    }

    TGraph *tg = new TGraph();

    //MPPC幅の分を積分
    for(Int_t i = 0; i < 100000; i++){
        Double_t x = -10 + 2*i*0.0001;
        Double_t integ = theo->Integral(x-0.65, x+0.65);
        tg->SetPoint(i, x, integ);

    }

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

}

//mm単位
//数値計算