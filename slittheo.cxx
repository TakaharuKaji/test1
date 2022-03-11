void plot_integral(Double_t slit_width, Int_t step){
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
        Double_t x = -10 + 2*i*0.0001;
        Double_t deriv = theo->Derivative(x);
        if(-0.00002 < deriv && deriv < 0.00002){
            //cout << x << " " << deriv << endl;  //微分係数が十分小さい時の値を表示
        }
    }

    TGraph *tg = new TGraph();

    TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);

    for(Int_t i = 0; i < 200000; i++){
        Double_t x = -20 + 2*i*0.0001;
        Double_t integ = theo->Integral(x-(slit_width/2.0), x+(slit_width/2.0));
        tg->SetPoint(i, x, integ);
    }
    TString inputfilename = "slittheo_fig/fig";
    TString figname = Form("%s_%d.png",inputfilename.Data(),step);

    tg -> Draw("AP");  //MPPC幅を考慮した理論曲線
    tg->GetXaxis()->SetRangeUser(-20,20);

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
