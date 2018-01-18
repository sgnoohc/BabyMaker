// Outputs latex code for table that prints the yields for two different sets of cuts 
// 

float Zbi_(float sig, float bg, float bgrelunc=0.3){
    
    double bgunc = bgrelunc*bg;
    double tau = bg/pow(bgunc,2);//bgunc is absolute
    double n_on = sig+bg;//total yield in SR = sig + bg
    double n_off = tau*bg;
    double P_Bi = TMath::BetaIncomplete(1./(1.+tau),n_on,n_off+1);
    double Z_Bi = sqrt(2.)*TMath::ErfInverse(1.-2.*P_Bi);
    return Z_Bi;
}

void makeCutComparisonTable(TString histogram_location_1 = "rootfiles/SRLooper.root", TString histogram_location_2 = "rootfiles/SRLooper.root"){
    
    bool SoverB = true;
    bool twosig = false;
    bool addsig = true;
    bool showsamples = true;
    bool showprocess = true;
    map<string, TH1D*> h1;
    map<string, TH1D*> h2;
    vector<string> histonames;
    vector<string> caption;
    vector<string> samples;
    vector<string> samples2;
    TFile *f1 = TFile::Open(histogram_location_1);
    TFile *f2 = TFile::Open(histogram_location_2);
    histonames.push_back("SignalRegion");                  caption.push_back("signal region");
    histonames.push_back("ApplicationRegion");             caption.push_back("application region");
    histonames.push_back("WZControlRegion");               caption.push_back("lost lepton / 3l-with-Z control region");
    histonames.push_back("SignalRegionPresel");            caption.push_back("signal region - preselection");
    histonames.push_back("ApplicationRegionPresel");       caption.push_back("application region - preselection");
    histonames.push_back("WZControlRegionPresel");         caption.push_back("lost lepton / 3l-with-Z control region - preselection");


    samples.push_back("WWW");
    if(twosig) samples.push_back("WHtoWWW");
    samples.push_back("VVV");
    samples.push_back("WZ");
    samples.push_back("WW");
    samples.push_back("ZZ");
    samples.push_back("Wjets");
    samples.push_back("Zjets");
    samples.push_back("ttV");
    samples.push_back("tt2l");
    samples.push_back("tt1l");
    samples.push_back("singleTop");
    samples.push_back("WG");
    samples.push_back("ZG");
    samples.push_back("Other");
    samples.push_back("bg");

    samples2.push_back("Data");
    samples2.push_back("trueSS");
    samples2.push_back("trueWWW");
    samples2.push_back("true3L");
    samples2.push_back("SSLL");
    samples2.push_back("3lLL");
    samples2.push_back("chargeflips");
    samples2.push_back("fakes");
    samples2.push_back("photonfakes");
    samples2.push_back("others");

    int nsig = 1;
    if(twosig) ++nsig;

    for(unsigned int n = 0; n<histonames.size();++n){
        for(unsigned int s = 0; s<samples.size()-1; ++s){
	  if(!showsamples&&s>=nsig) break;
            string mapname = histonames[n] + "_" + samples[s];
            string bgname = histonames[n] + "_bg";
            //cout << mapname << endl;
            h1[mapname ]=(TH1D*)f1->Get(mapname.c_str());
            h2[mapname ]=(TH1D*)f2->Get(mapname.c_str());
            if(s==0&&addsig){
                string addname = histonames[n] + "_WHtoWWW";
                //First File
                h1[addname ]=(TH1D*)f1->Get(addname.c_str());
                h1[mapname ]->Add(h1[addname],1.);
                //Second File
                h2[addname ]=(TH1D*)f2->Get(addname.c_str());
                h2[mapname ]->Add(h2[addname],1.);
            }
            //First File
            for(int b = 0; b<h1[mapname]->GetNbinsX();++b){ if(h1[mapname]->GetBinContent(b)<0){h1[mapname]->SetBinContent(b,0); h1[mapname]->SetBinError(b,0); } }
            if(s==nsig)  h1[bgname] = (TH1D*)h1[mapname]->Clone(bgname.c_str());
            else if(s>0) h1[bgname]->Add(h1[mapname],1.);
            //Second File
            for(int b = 0; b<h2[mapname]->GetNbinsX();++b){ if(h2[mapname]->GetBinContent(b)<0){h2[mapname]->SetBinContent(b,0); h2[mapname]->SetBinError(b,0); } }
            if(s==nsig)  h2[bgname] = (TH1D*)h2[mapname]->Clone(bgname.c_str());
            else if(s>0) h2[bgname]->Add(h2[mapname],1.);
        }
        for(unsigned int s = 0; s<samples2.size(); ++s){
            if(!showprocess) break;
            string mapname = histonames[n] + "_" + samples2[s];
            //First File
            h1[mapname ]=(TH1D*)f1->Get(mapname.c_str());
            for(int b = 0; b<h1[mapname]->GetNbinsX();++b){ if(h1[mapname]->GetBinContent(b)<0){h1[mapname]->SetBinContent(b,0); h1[mapname]->SetBinError(b,0); } }
            //Second File
            h2[mapname ]=(TH1D*)f2->Get(mapname.c_str());
            for(int b = 0; b<h2[mapname]->GetNbinsX();++b){ if(h2[mapname]->GetBinContent(b)<0){h2[mapname]->SetBinContent(b,0); h2[mapname]->SetBinError(b,0); } }

    	    if(!showsamples){
    	      string bgname = histonames[n] + "_bg";
              //First File
    	      if(s==nsig)  h1[bgname] = (TH1D*)h1[mapname]->Clone(bgname.c_str());
    	      else if(s>0) h1[bgname]->Add(h1[mapname],1.);
              //Second File
              if(s==nsig)  h2[bgname] = (TH1D*)h2[mapname]->Clone(bgname.c_str());
              else if(s>0) h2[bgname]->Add(h2[mapname],1.);
    	    }
        }
    }
    string ss;
    cout << "\\begin{table}" << endl
    << "\\centering" << endl
    << "\\tiny" << endl
    << "\\begin{tabular}{|r|ccc|ccc|}" << endl;
    for(unsigned int n = 0; n<histonames.size(); ++n){
    cout << "\\hline" << endl
    << "\\multicolumn{7}{|c|}{"<<caption[n] <<"} \\\\" << endl
    << " & \\multicolumn{3}{|c|}{SS} & \\multicolumn{3}{|c|}{3$\\ell$} \\\\" << endl
    << " & $ee$ & $e\\mu$ & $\\mu\\mu$ & 0SFOS & 1SFOS & 2SFOS \\\\" << endl
    << "\\hline" << endl;
    for(unsigned int s = nsig; s<samples.size(); ++s){
        if(!showsamples) break;
        ss = histonames[n] + "_" + samples[s];
        cout << samples[s];
        for(int b =1; b<=h1[ss]->GetNbinsX();++b) cout << " & " << fixed << setprecision(2) << h1[ss]->GetBinContent(b) << "$\\pm$" << h1[ss]->GetBinError(b) << " (" <<h2[ss]->GetBinContent(b) << "$\\pm$" << h2[ss]->GetBinError(b)<<") ";
        cout << " \\\\" << endl;
    }
    cout << "\\hline" << endl;
    ss = histonames[n] + "_WWW";
    cout << "WWW";
    for(int b =1; b<=h1[ss]->GetNbinsX();++b) cout << " & " << fixed << setprecision(2) << h1[ss]->GetBinContent(b) << "$\\pm$" << h1[ss]->GetBinError(b) << " (" <<h2[ss]->GetBinContent(b) << "$\\pm$" << h2[ss]->GetBinError(b)<<") ";
        cout << " \\\\" << endl;
        if(twosig){
        ss = histonames[n] + "_WHtoWWW";
        cout << "WH$\\to$WWW";
        for(int b =1; b<=h1[ss]->GetNbinsX();++b) cout << " & " << fixed << setprecision(2) << h1[ss]->GetBinContent(b) << "$\\pm$" << h1[ss]->GetBinError(b) << " (" <<h2[ss]->GetBinContent(b) << "$\\pm$" << h2[ss]->GetBinError(b)<<") ";
            cout << " \\\\" << endl;
        }
    cout << "\\hline" << endl;
    if(SoverB){
    string ssb =histonames[n] + "_bg";
    cout << "S/B ";
    for(int b =1; b<=h1[ss]->GetNbinsX();++b) cout << " & " << fixed << setprecision(2) << h1[ss]->GetBinContent(b)/h1[ssb]->GetBinContent(b) << "$\\pm$" << sqrt(pow(h1[ss]->GetBinError(b)/h1[ssb]->GetBinContent(b),2)+pow(h1[ss]->GetBinContent(b)*h1[ssb]->GetBinError(b)/pow(h1[ssb]->GetBinContent(b),2),2)) <<" (" << h2[ss]->GetBinContent(b)/h2[ssb]->GetBinContent(b) << "$\\pm$" << sqrt(pow(h2[ss]->GetBinError(b)/h2[ssb]->GetBinContent(b),2)+pow(h2[ss]->GetBinContent(b)*h2[ssb]->GetBinError(b)/pow(h2[ssb]->GetBinContent(b),2),2)) <<") ";
    cout << "\\\\" << endl;
    cout << "S/$\\sqrt{\\mathrm{B}}$ ";
    for(int b =1; b<=h1[ss]->GetNbinsX();++b) cout << " & " << fixed << setprecision(2) << h1[ss]->GetBinContent(b)/sqrt(h1[ssb]->GetBinContent(b)) << "$\\pm$" << sqrt(pow(h1[ss]->GetBinError(b)/sqrt(h1[ssb]->GetBinContent(b)),2)+pow(h1[ss]->GetBinContent(b)*h1[ssb]->GetBinError(b)/pow(h1[ssb]->GetBinContent(b),1.5),2))<< " (" << h2[ss]->GetBinContent(b)/sqrt(h2[ssb]->GetBinContent(b)) << "$\\pm$" << sqrt(pow(h2[ss]->GetBinError(b)/sqrt(h2[ssb]->GetBinContent(b)),2)+pow(h2[ss]->GetBinContent(b)*h2[ssb]->GetBinError(b)/pow(h2[ssb]->GetBinContent(b),1.5),2))<<") ";
    cout << "\\\\" << endl;
    cout << "$Z_\\mathrm{bi}$ ";
    for(int b =1; b<=h1[ss]->GetNbinsX();++b) cout << " & " << fixed << setprecision(2) << Zbi_(h1[ss]->GetBinContent(b),h1[ssb]->GetBinContent(b),sqrt(pow(h1[ssb]->GetBinError(b)/h1[ssb]->GetBinContent(b),2)+pow(0.3,2)) )<<" (" << Zbi_(h2[ss]->GetBinContent(b),h2[ssb]->GetBinContent(b),sqrt(pow(h2[ssb]->GetBinError(b)/h2[ssb]->GetBinContent(b),2)+pow(0.3,2)) )<<") ";
    cout << "\\\\" << endl
    << "\\hline" << endl;
    }
    ss = histonames[n] + "_Data";
    cout << "Data";
    for(int b =1; b<=h1[ss]->GetNbinsX();++b) cout << " & " << fixed << setprecision(2) << h1[ss]->GetBinContent(b) << "$\\pm$" << h1[ss]->GetBinError(b)<< " ("<< h2[ss]->GetBinContent(b) << "$\\pm$" << h2[ss]->GetBinError(b)<<") ";
    cout << " \\\\" << endl
    << "\\hline" << endl;
    for(unsigned int s = 1; s<samples2.size(); ++s){
        if(!showprocess) break;
        ss = histonames[n] + "_" + samples2[s];
        cout << samples2[s];
        for(int b =1; b<=h1[ss]->GetNbinsX();++b) cout << " & " << fixed << setprecision(2) << h1[ss]->GetBinContent(b) << "$\\pm$" << h1[ss]->GetBinError(b)<< " (" << h2[ss]->GetBinContent(b) << "$\\pm$" << h2[ss]->GetBinError(b) <<") ";
        cout << " \\\\" << endl;
    }
        cout << "\\hline" << endl;
    }
    cout << "\\end{tabular}" << endl
    << "\\end{table}" << endl;


}
