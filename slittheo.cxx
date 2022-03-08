void slittheo(){
    Double_t a, b, k, R, I0;

    a = 0.04 ;
    b = 0.02 ;
    k = 2*TMath::Pi()/(5.2*0.0001);
    R = 295;
    
    TF1 *theo = new TF1("theo","(sin([0]*x)*cos([1]*x)/x)**2",-10,10);
    //TF1 *theo = new TF1("theo","(cos([1]*x))**2",-2,2);  //理論曲線、単スリット幅ゼロ近似
    theo->SetParameter(0,k*b/2/R);
    theo->SetParameter(1,k*a/2/R);
    //theo->Draw();  //理論曲線

    
    for(Int_t i = 0; i < 100000; i++){
        Double_t x = -10 + 2*i*0.0001;cd ..
        Double_t deriv = theo->Derivative(x);
        if(-0.00002 < deriv && deriv < 0.00002){
            cout << x << " " << deriv << endl;
        } 
    }

    TGraph *tg = new TGraph();

    for(Int_t i = 0; i < 100000; i++){
        Double_t x = -10 + 2*i*0.0001;
        Double_t integ = theo->Integral(x-0.3, x+0.3);
        tg->SetPoint(i, x, integ);
    }

    tg->Draw("AP");  //MPPC幅を考慮した理論曲線

}

//mm単位
//数値計算