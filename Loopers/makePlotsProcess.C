void makePlotsProcess(){

    string outdir = "plots/";
    bool data = true;
    bool twosig = false;
    bool addsig = true;
    bool addlostlepto3l = true;
    bool plotsimErrorHashed = false;
    gStyle->SetOptStat(0);
    bool logy = false;
    map<string, TH1D*> h;
    map<string, TH1D*> rat;
    map<string, THStack*> stack;
    vector<string> histonames;
    vector<string> axisnames;
    //vector<Color_t> cols;
    vector<int> cols;
    vector<int> plottogether;
    vector<string> samples;
    vector<string> samplesleg;
    vector<int> onlySSSFOS;
    
    
    /*
    TFile *f = TFile::Open("rootfiles/NminusOnePlots.root");
    histonames.push_back("DetajjL_SRSS_NmO");       axisnames.push_back("#Delta#eta_{JJ} | full selection");                              onlySSSFOS.push_back(1);
    histonames.push_back("DetajjL_SRSS_presel");    axisnames.push_back("#Delta#eta_{JJ} | preselection");                                onlySSSFOS.push_back(1);
    histonames.push_back("MET_SRSS_NmO");           axisnames.push_back("E_{T}^{miss} [GeV] | full selection");                           onlySSSFOS.push_back(1);
    histonames.push_back("MET_SRSS_presel");        axisnames.push_back("E_{T}^{miss} [GeV] | preselection");                             onlySSSFOS.push_back(1);
    histonames.push_back("Mjj_SRSS_NmO");           axisnames.push_back("M_{jj} [GeV] | full selection");                                 onlySSSFOS.push_back(1);
    histonames.push_back("Mjj_SRSS_presel");        axisnames.push_back("M_{jj} [GeV] | preselection");                                   onlySSSFOS.push_back(1);
    histonames.push_back("MjjL_SRSS_NmO");          axisnames.push_back("M_{JJ} [GeV] | full selection");                                 onlySSSFOS.push_back(1);
    histonames.push_back("MjjL_SRSS_presel");       axisnames.push_back("M_{JJ} [GeV] | preselection");                                   onlySSSFOS.push_back(1);
    histonames.push_back("Mll_SRSS_NmO");           axisnames.push_back("M_{ll} [GeV] | full selection");                                 onlySSSFOS.push_back(1);
    histonames.push_back("Mll_SRSS_presel");        axisnames.push_back("M_{ll} [GeV] | preselection");                                   onlySSSFOS.push_back(1);
    histonames.push_back("MTmax_SRSS_NmO");         axisnames.push_back("M_{T}^{max} [GeV] | full selection");                            onlySSSFOS.push_back(1);
    histonames.push_back("MTmax_SRSS_presel");      axisnames.push_back("M_{T}^{max} [GeV] | preselection");                              onlySSSFOS.push_back(1);
    histonames.push_back("pTll_SRSS_NmO");          axisnames.push_back("p_{T}(ll) [GeV] | full selection");                              onlySSSFOS.push_back(1);
    histonames.push_back("pTll_SRSS_presel");       axisnames.push_back("p_{T}(ll) [GeV] | preselection");                                onlySSSFOS.push_back(1);
    histonames.push_back("DPhilllMET_SR3l_NmO");    axisnames.push_back("#Delta#phi(lll,#vec{p}_{T}^{miss}) | full selection");           onlySSSFOS.push_back(2);
    histonames.push_back("DPhilllMET_SR3l_presel"); axisnames.push_back("#Delta#phi(lll,#vec{p}_{T}^{miss}) | preselection");             onlySSSFOS.push_back(2);
    histonames.push_back("MET_SR3l_NmO");           axisnames.push_back("E_{T}^{miss} [GeV] | full selection");                           onlySSSFOS.push_back(2);
    histonames.push_back("MET_SR3l_presel");        axisnames.push_back("E_{T}^{miss} [GeV] | preselection");                             onlySSSFOS.push_back(2);
    histonames.push_back("Mlll_SR3l_NmO");          axisnames.push_back("M_{lll} [GeV] | full selection");                                onlySSSFOS.push_back(2);
    histonames.push_back("Mlll_SR3l_presel");       axisnames.push_back("M_{lll} [GeV] | preselection");                                  onlySSSFOS.push_back(2);
    histonames.push_back("MSFOSZlike_SR3l_NmO");    axisnames.push_back("M_{SFOS} (most Z-like) [GeV] | preselection | full selection");  onlySSSFOS.push_back(2);
    histonames.push_back("MSFOSZlike_SR3l_presel"); axisnames.push_back("M_{SFOS} (most Z-like) [GeV] | preselection");                   onlySSSFOS.push_back(2);
    histonames.push_back("PTlll_SR3l_NmO");         axisnames.push_back("p_{T}(lll) [GeV] | full selection");                             onlySSSFOS.push_back(2);
    histonames.push_back("PTlll_SR3l_presel");      axisnames.push_back("p_{T}(lll) [GeV] | preselection");                               onlySSSFOS.push_back(2);
    */
    /*
    TFile *f = TFile::Open("rootfiles/Validations.root");
    //VBS
    histonames.push_back("Detajj_VRSS_MjjL400");         axisnames.push_back("#Delta#eta_{jj} | validation of VBS WW");                              onlySSSFOS.push_back(1);
    histonames.push_back("MjjL_VRSS_Detajj1p5");         axisnames.push_back("M_{JJ} [GeV] | validation of VBS WW");                                 onlySSSFOS.push_back(1);
    //ttX
    histonames.push_back("MET_VR3l_noZ_ge2j_ge1bmed");   axisnames.push_back("E_{T}^{miss} [GeV] | validation of ttV, 3l w/o Z, N_{B}^{med}#geq1");  onlySSSFOS.push_back(2);
    histonames.push_back("MET_VR3l_Z_ge2j_ge1bmed");     axisnames.push_back("E_{T}^{miss} [GeV] | validation of ttV, 3l w/ Z, N_{B}^{med}#geq1");   onlySSSFOS.push_back(2);
    histonames.push_back("MET_VRSS_MjjW_ge4j_ge1bmed");  axisnames.push_back("M_{T}^{max} [GeV] | validation of ttV, 2l SS");                        onlySSSFOS.push_back(1);
    histonames.push_back("MSFOS_VR3l_noZ_ge2j_ge1bmed"); axisnames.push_back("M_{SFOS} [GeV] | validation of ttV, 3l w/o Z, N_{B}^{med}#geq1");      onlySSSFOS.push_back(2);
    histonames.push_back("MSFOS_VR3l_Z_ge2j_ge1bmed");   axisnames.push_back("M_{SFOS} [GeV] | validation of ttV, 3l w/ Z, N_{B}^{med}#geq1");       onlySSSFOS.push_back(2);
    histonames.push_back("NB_VR3l_noZ_ge2j_ge1b");       axisnames.push_back("N_{B} | validation of ttV, 3l w/o Z, N_{B}#geq1");                     onlySSSFOS.push_back(2);
    histonames.push_back("NB_VR3l_noZ_ge2j_ge1bmed");    axisnames.push_back("N_{B}^{med} | validation of ttV, 3l w/o Z, N_{B}^{med}#geq1");         onlySSSFOS.push_back(2);
    histonames.push_back("NB_VR3l_Z_ge2j_ge1b");         axisnames.push_back("N_{B} | validation of ttV, 3l w/ Z, N_{B}#geq1");                      onlySSSFOS.push_back(2);
    histonames.push_back("NB_VR3l_Z_ge2j_ge1bmed");      axisnames.push_back("N_{B}^{med} | validation of ttV, 3l w/ Z, N_{B}^{med}#geq1");          onlySSSFOS.push_back(2);
    histonames.push_back("NB_VRSS_MjjW_ge4j_ge1b");      axisnames.push_back("N_{B} | validation of ttV, 2l SS");                                    onlySSSFOS.push_back(1);
    histonames.push_back("NB_VRSS_MjjW_ge4j_ge1bmed");   axisnames.push_back("N_{B}^{med} | validation of ttV, 2l SS");                              onlySSSFOS.push_back(1);
    histonames.push_back("Ptll_VRSS_MjjW_ge4j_ge1bmed"); axisnames.push_back("p_{T}(ll) [GeV] | validation of ttV, 2l SS");                          onlySSSFOS.push_back(1);
    histonames.push_back("Ptlll_VR3l_noZ_ge2j_ge1bmed"); axisnames.push_back("p_{T}(lll) [GeV] | validation of ttV, 3l w/o Z, N_{B}^{med}#geq1");    onlySSSFOS.push_back(2);
    histonames.push_back("Ptlll_VR3l_Z_ge2j_ge1bmed");   axisnames.push_back("p_{T}(lll) [GeV] | validation of ttV, 3l w/ Z, N_{B}^{med}#geq1");     onlySSSFOS.push_back(2);
    histonames.push_back("ZPt_VR3l_Z_ge2j_ge1bmed");     axisnames.push_back("p_{T}(Z) [GeV] | validation of ttV, 3l w/ Z, N_{B}^{med}#geq1");       onlySSSFOS.push_back(2);
    //Zg
    //histonames.push_back("Mlll_VR3l_noZ_METleq50");      axisnames.push_back("M_{lll} [GeV] | validation of Z#gamma");                               onlySSSFOS.push_back(2);
    //histonames.push_back("pTlll_VR3l_noZ_METleq50");     axisnames.push_back("p_{T}(lll) [GeV] | validation of Z#gamma");                            onlySSSFOS.push_back(2);
    */
    /*
    TFile *f = TFile::Open("rootfiles/Check3lWZCR.root");
    histonames.push_back("YieldsCR");                             axisnames.push_back("three-lepton / lost-lepton control region");                               onlySSSFOS.push_back(2);
    histonames.push_back("YieldsCR_cutonMjj");                    axisnames.push_back("three-lepton / lost-lepton control region | selection on M_{jj}");         onlySSSFOS.push_back(2);
    histonames.push_back("Mjj_CRlike_allSS");                     axisnames.push_back("M_{jj} [GeV] | lost-lepton control region");                               onlySSSFOS.push_back(2);
    histonames.push_back("MSFOS_CRlike_allSS");                   axisnames.push_back("M_{SFOS} (most Z-like) [GeV] | lost-lepton control region");               onlySSSFOS.push_back(2);
    histonames.push_back("MSFOSall_CRlike_allSS");                axisnames.push_back("M_{SFOS} [GeV] | lost-lepton control region");                             onlySSSFOS.push_back(2);
    histonames.push_back("MSFOS_1SFOS_inverteitherMETdPhiPt");    axisnames.push_back("M_{SFOS} (most Z-like) [GeV] | 1 SFOS three-lepton validation region 2");  onlySSSFOS.push_back(2);
    histonames.push_back("MSFOS_1SFOS_invertMETdPhiPt");          axisnames.push_back("M_{SFOS} (most Z-like) [GeV] | 1 SFOS three-lepton validation region 1");  onlySSSFOS.push_back(2);
    histonames.push_back("MSFOS_2SFOS_inverteitherMETdPhiPt");    axisnames.push_back("M_{SFOS} (most Z-like) [GeV] | 2 SFOS three-lepton validation region 2");  onlySSSFOS.push_back(2);
    histonames.push_back("MSFOS_2SFOS_invertMETdPhiPt");          axisnames.push_back("M_{SFOS} (most Z-like) [GeV] | 2 SFOS three-lepton validation region 1");  onlySSSFOS.push_back(2);
    histonames.push_back("MSFOSall_2SFOS_inverteitherMETdPhiPt"); axisnames.push_back("M_{SFOS} [GeV] | 2 SFOS three-lepton validation region 2");                onlySSSFOS.push_back(2);
    histonames.push_back("MSFOSall_2SFOS_invertMETdPhiPt");       axisnames.push_back("M_{SFOS} [GeV] | 2 SFOS three-lepton validation region 1");                onlySSSFOS.push_back(2);
    histonames.push_back("MSFOS_all3l_inverteitherMETdPhiPt");    axisnames.push_back("M_{SFOS} (most Z-like) [GeV] | three-lepton validation region 2");         onlySSSFOS.push_back(2);
    histonames.push_back("MSFOS_all3l_invertMETdPhiPt");          axisnames.push_back("M_{SFOS} (most Z-like) [GeV] | three-lepton validation region 2");         onlySSSFOS.push_back(2);
    histonames.push_back("MSFOSall_all3l_inverteitherMETdPhiPt"); axisnames.push_back("M_{SFOS} [GeV] | three-lepton validation region 2");                       onlySSSFOS.push_back(2);
    histonames.push_back("MSFOSall_all3l_invertMETdPhiPt");       axisnames.push_back("M_{SFOS} [GeV] | three-lepton validation region 2");                       onlySSSFOS.push_back(2);
    */

    TColor *lightblue  = new TColor(2001,91/255.,187/255.,241/255.);
    TColor *blue       = new TColor(2002,60/255.,144/255.,196/255.);
    TColor *orange     = new TColor(2003,230/255.,159/255.,0/255.);
    TColor *brown      = new TColor(2004,180/255.,117/255.,0/255.);
    TColor *yellow     = new TColor(2005,245/255.,236/255.,69/255.);
    TColor *darkyellow = new TColor(2006,215/255.,200/255.,0/255.);
    TColor *blueviolet = new TColor(2007,70/255.,109/255.,171/255.);
    TColor *violet     = new TColor(2008,70/255.,90/255.,134/255.);
    TColor *darkviolet = new TColor(2009,55/255.,65/255.,100/255.);
    TColor *lightgreen = new TColor(2010,120/255.,160/255.,0/255.);
    TColor *green      = new TColor(2011,0/255.,158/255.,115/255.);
    TColor *pink       = new TColor(2012,204/255.,121/255.,167/255.);


    vector<int> is3lSS;
    samples.push_back("WWW");         samplesleg.push_back("WWW signal");                      is3lSS.push_back(0);
    if(twosig) { samples.push_back("WHtoWWW");     samplesleg.push_back("WH#rightarrowWWW");   is3lSS.push_back(0); }
    //samples.push_back("others");      samplesleg.push_back("Other");                           is3lSS.push_back(0);
    samples.push_back("photonfakes"); samplesleg.push_back("#gamma #rightarrow l");            is3lSS.push_back(0);
    samples.push_back("chargeflips"); samplesleg.push_back("charge misassignment");            is3lSS.push_back(0);
    //samples.push_back("doublefakes"); samplesleg.push_back("double fakes");                    is3lSS.push_back(0);
    samples.push_back("fakes");       samplesleg.push_back("non-prompt leptons");              is3lSS.push_back(0);
    //samples.push_back("fakesPred");    samplesleg.push_back("fakes from data");                 is3lSS.push_back(0);
    if(!addlostlepto3l) { samples.push_back("3lLL");        samplesleg.push_back("lost leptons");                     is3lSS.push_back(2);}
    samples.push_back("SSLL");        samplesleg.push_back("lost leptons");                    is3lSS.push_back(1);
    samples.push_back("true3L");      samplesleg.push_back("three leptons");                   is3lSS.push_back(2);
    samples.push_back("trueWWW");     samplesleg.push_back("irreducible");                     is3lSS.push_back(2);
    samples.push_back("trueSS");      samplesleg.push_back("irreducible");                     is3lSS.push_back(1);
    //samples.push_back("WWVBS");       samplesleg.push_back("W^{#pm}W^{#pm} VBS");              is3lSS.push_back(1);
    //samples.push_back("ttZ");         samplesleg.push_back("t#bar{t}Z");                       is3lSS.push_back(0);
    //samples.push_back("ttW");         samplesleg.push_back("t#bar{t}W");                       is3lSS.push_back(0);
    samples.push_back("bg");          samplesleg.push_back("background");                      is3lSS.push_back(-1);
    if(addlostlepto3l){
        for(unsigned int i = 0; i<samples.size();++i){
            if(samples[i].find("true3L")!=string::npos) samplesleg[i] = "three leptons/lost leptons";
        }
    }
    
    cols.push_back(632);//kRed
    if(twosig) cols.push_back(kBlue);//kRed
    //cols.push_back(2012);
    cols.push_back(kGray);
    cols.push_back(2007);
    //cols.push_back(2006);
    cols.push_back(2005);
    if(!addlostlepto3l)     cols.push_back(2011);
    cols.push_back(2003);
    cols.push_back(2003);
    cols.push_back(2001);
    cols.push_back(2001);
    //cols.push_back(kCyan);//VBS
    //cols.push_back(kCyan+2);//ttZ
    //cols.push_back(kCyan);//ttW
    cols.push_back(kBlack);
    int nsig = 1;
    if(twosig) ++nsig;
    for(unsigned int n = 0; n<histonames.size();++n){
      string bgname = histonames[n] + "_bg";
      string stackname = histonames[n];
      //cout << stackname << endl;
      stack[stackname] = new THStack();
      stack[stackname]->SetName(stackname.c_str());
      string mapname = "";
      if(data) {
	mapname = histonames[n] + "_Data";
	string  mapnameX = histonames[n] + "_X";
	h[mapnameX ]=(TH1D*)f->Get(mapname.c_str());
	h[mapnameX]->SetName(mapnameX.c_str());
	h[mapname] = new TH1D(mapname.c_str(),"",h[mapnameX]->GetNbinsX(), h[mapnameX]->GetXaxis()->GetBinLowEdge(1), h[mapnameX]->GetXaxis()->GetBinLowEdge(h[mapnameX]->GetNbinsX()+1));
	h[mapname]->SetBinErrorOption(TH1::kPoisson);
	for(int i = 1; i<=h[mapname]->GetNbinsX(); ++i){
	  //cout << h[mapnameX]->GetBinContent(i) << endl;
	  for(int n = 1; n<=h[mapnameX]->GetBinContent(i); ++n){
	    h[mapname]->Fill(h[mapnameX]->GetXaxis()->GetBinCenter(i),1);
	  }
	}
	h[mapname ]=(TH1D*)f->Get(mapname.c_str());
	h[mapname]->SetLineColor(kBlack);
	h[mapname]->SetLineWidth(2);
	h[mapname]->SetMarkerStyle(20);
      }
      for(unsigned int s = 0; s<samples.size()-1; ++s){
	mapname = histonames[n] + "_" + samples[s];
	cout << mapname << endl;
	h[mapname ]=(TH1D*)f->Get(mapname.c_str());
	h[mapname]->GetXaxis()->SetTitle(axisnames[n].c_str());
	h[mapname]->GetYaxis()->SetTitle("Events");
	h[mapname]->GetXaxis()->SetTitleSize(0.);
	if(addsig&&s==0){
	  string addname = histonames[n] + "_WHtoWWW";
	  h[addname ]=(TH1D*)f->Get(addname.c_str());
	  h[mapname ]->Add(h[addname ],1.);
	}
	if(addlostlepto3l&&samples[s].find("true3L")!=string::npos){
	  string mapname2 =histonames[n] + "_3lLL";
	  h[mapname2 ]=(TH1D*)f->Get(mapname2.c_str());
	  for(int i = 1; i<=h[mapname]->GetNbinsX();++i) h[mapname2]->GetXaxis()->SetBinLabel(i,h[mapname]->GetXaxis()->GetBinLabel(i));
	  h[mapname]->Add(h[mapname2],1.);
	}
	for(int b = 0; b<h[mapname]->GetNbinsX();++b){ if(h[mapname]->GetBinContent(b)<0){h[mapname]->SetBinContent(b,0); h[mapname]->SetBinError(b,0); } }
	if(s==nsig) h[bgname] = (TH1D*)h[mapname]->Clone(bgname.c_str());
	else if(s>nsig) {
	  h[bgname]->Add(h[mapname],1.);
	}
	if(s==0) {
	  h[mapname]->SetLineColor(cols[s]); h[mapname]->SetLineWidth(3);
	}
	else if(!addsig&&twosig&&s==1) {
	  h[mapname]->SetLineColor(cols[s]); h[mapname]->SetLineWidth(3); h[mapname]->SetLineStyle(7);
	}
	else { h[mapname]->SetFillColor(cols[s]); h[mapname]->SetLineColor(kBlack); h[mapname]->SetMarkerSize(0); }
	if(s==nsig){
	  h[bgname]->SetFillColor(cols[samples.size()-1]); h[bgname]->SetLineColor(cols[samples.size()-1]); h[bgname]->SetFillStyle(3544); h[bgname]->SetMarkerSize(0);
	}
	if(s>=nsig){
	  stack[stackname]->Add(h[mapname],"");
	}
      }
      if(data){
	for(int i = 1; i<=h[stackname + "_Data"        ]->GetNbinsX();++i){
	  //if(((h[stackname + "_"+samples[0] ]->GetBinContent(i)/h[stackname + "_bg"]->GetBinContent(i)>0.1) || (h[stackname + "_"+samples[0] ]->GetBinContent(i)/h[stackname + "_bg"]->GetBinContent(i)>0.5*h[stackname + "_bg"]->GetBinError(i)))&&h[stackname + "_"+samples[0] ]->GetBinContent(i)>0.5 ) h[stackname + "_Data"]->SetBinContent(i,-999);
	}
      }
      if(data&&h[stackname+"_Data"]->Integral()!=0) rat[stackname] = (TH1D*)h[stackname + "_Data"        ]->Clone(stackname.c_str());
      else                                          rat[stackname] = (TH1D*)h[stackname + "_"+samples[0] ]->Clone(stackname.c_str());
      h[stackname+"BGnoErr"] = (TH1D*)h[stackname + "_bg"]->Clone((stackname+"BGnoErr").c_str());
      if(plotsimErrorHashed) { for(int i = 1; i<=h[stackname+"BGnoErr"]->GetNbinsX();++i) h[stackname+"BGnoErr"]->SetBinError(i,0.); }//don't put sim error on both data and MC ratio
        
      rat[stackname]->Divide(h[stackname + "BGnoErr"]);
      rat[stackname+"BG"] = (TH1D*)h[stackname + "_bg"]->Clone((stackname+"BG").c_str());
      rat[stackname+"BG"]->Divide(h[stackname +"BGnoErr"]);

      if(!addsig&&twosig&&!data){
	rat[stackname+"v2"] = (TH1D*)h[stackname + "_"+samples[1] ]->Clone(stackname.c_str());
	rat[stackname+"v2"]->Divide(h[stackname + "_BGnoErr"]);
      }
    }
    
    TLatex *tLumi = new TLatex(0.95,0.955,"35.9 fb^{-1} (13 TeV)");
    tLumi->SetNDC();
    tLumi->SetTextAlign(31);
    tLumi->SetTextFont(42);
    tLumi->SetTextSize(0.042);
    tLumi->SetLineWidth(2);
    TLatex *tECM = new TLatex(0.95,0.955,"(13 TeV)");
    tECM->SetNDC();
    tECM->SetTextAlign(31);
    tECM->SetTextFont(42);
    tECM->SetTextSize(0.042);
    tECM->SetLineWidth(2);
    //tLumi->Draw();
    TLatex *tCMS = new TLatex(0.125,0.955,"CMS");
    tCMS->SetNDC();
    tCMS->SetTextAlign(11);
    tCMS->SetTextFont(61);
    tCMS->SetTextSize(0.0525);
    tCMS->SetLineWidth(2);
    //tCMS->Draw();
    TLatex *tSim = new TLatex(0.225,0.955,"Simulation");
    tSim->SetNDC();
    tSim->SetTextAlign(11);
    tSim->SetTextFont(52);
    tSim->SetTextSize(0.042);
    tSim->SetLineWidth(2);
    TLatex *tPrel = new TLatex(0.295,0.955,"Preliminary");
    tPrel->SetNDC();
    tPrel->SetTextAlign(11);
    tPrel->SetTextFont(52);
    tPrel->SetTextSize(0.042);
    tPrel->SetLineWidth(2);
    TLatex *tComment = new TLatex(0.185,0.90,"Last bin scaled x0.2");
    tComment->SetNDC();
    tComment->SetTextAlign(11);
    tComment->SetTextFont(42);
    tComment->SetTextSize(0.035);
    tComment->SetLineWidth(2);
    TLatex *tlx = new TLatex();
    tlx->SetTextFont(42);
    tlx->SetNDC();
    tlx->SetTextAlign(11);
    tlx->SetTextSize(0.042);
    tlx->SetTextColor(1);
    


    TLegend *leg1 = new TLegend(0.1667,0.63,0.5,0.9075,NULL,"brNDC");
    leg1->SetBorderSize(0);
    leg1->SetTextSize(0.033);
    leg1->SetLineColor(1);
    leg1->SetLineStyle(1);
    leg1->SetLineWidth(2);
    leg1->SetFillColor(0);
    leg1->SetFillStyle(1001);
    TLegend *leg1SS = new TLegend(0.1667,0.67,0.5,0.89,NULL,"brNDC");
    leg1SS->SetBorderSize(0);
    leg1SS->SetTextSize(0.035);
    leg1SS->SetLineColor(1);
    leg1SS->SetLineStyle(1);
    leg1SS->SetLineWidth(2);
    leg1SS->SetFillColor(0);
    leg1SS->SetFillStyle(1001);
    TLegend *leg13l = new TLegend(0.1667,0.67,0.5,0.89,NULL,"brNDC");
    leg13l->SetBorderSize(0);
    leg13l->SetTextSize(0.035);
    leg13l->SetLineColor(1);
    leg13l->SetLineStyle(1);
    leg13l->SetLineWidth(2);
    leg13l->SetFillColor(0);
    leg13l->SetFillStyle(1001);
    int legcount(0);
    int legcountSS(0);
    int legcount3l(0);
    unsigned int legSStot(0);
    unsigned int leg3ltot(0);
    for(unsigned int s = 0; s<samples.size();++s){
      if(is3lSS[s]==0||is3lSS[s]==1) ++legSStot;
      if(is3lSS[s]==0||is3lSS[s]==2) ++leg3ltot;
    }
    if(data){ ++legSStot; ++leg3ltot; }
    for(unsigned int s = nsig; s<(samples.size()-1);++s){
      if(is3lSS[s]==0||is3lSS[s]==1) {
	leg1->AddEntry(h[histonames[0]+"_"+samples[s] ],samplesleg[s].c_str(), "f");
	legcount = s;
      }
    }
    for(unsigned int s = nsig; s<=legSStot/2+nsig;++s){
      if(is3lSS[s]==0||is3lSS[s]==1) {
	leg1SS->AddEntry(h[histonames[0]+"_"+samples[s] ],samplesleg[s].c_str(), "f");
	legcountSS = s;
      }
    }
    for(unsigned int s = nsig; s<=leg3ltot/2+nsig;++s){
      if(is3lSS[s]==0||is3lSS[s]==2) {
	leg13l->AddEntry(h[histonames[0]+"_"+samples[s] ],samplesleg[s].c_str(), "f");
	legcount3l = s;
      }
    }
    TLegend *leg2 = new TLegend(0.55,0.63,0.85,0.9075,NULL,"brNDC");
    leg2->SetBorderSize(0);
    leg2->SetTextSize(0.033);
    leg2->SetLineColor(1);
    leg2->SetLineStyle(1);
    leg2->SetLineWidth(2);
    leg2->SetFillColor(0);
    leg2->SetFillStyle(1001);
    TLegend *leg2SS = new TLegend(0.55,0.67,0.85,0.89,NULL,"brNDC");
    leg2SS->SetBorderSize(0);
    leg2SS->SetTextSize(0.035);
    leg2SS->SetLineColor(1);
    leg2SS->SetLineStyle(1);
    leg2SS->SetLineWidth(2);
    leg2SS->SetFillColor(0);
    leg2SS->SetFillStyle(1001);
    TLegend *leg23l = new TLegend(0.55,0.67,0.85,0.89,NULL,"brNDC");
    leg23l->SetBorderSize(0);
    leg23l->SetTextSize(0.035);
    leg23l->SetLineColor(1);
    leg23l->SetLineStyle(1);
    leg23l->SetLineWidth(2);
    leg23l->SetFillColor(0);
    leg23l->SetFillStyle(1001);
    for(unsigned int s = nsig; s<(samples.size()-1);++s){
        if(is3lSS[s]==0||is3lSS[s]==2) {
            leg2->AddEntry(h[histonames[0]+"_"+samples[s] ],samplesleg[s].c_str(), "f");
            legcount = s;
        }
    }
    for(unsigned int s = legcountSS+1; s<samples.size()-1;++s){
        if(is3lSS[s]==0||is3lSS[s]==1) leg2SS->AddEntry(h[histonames[0]+"_"+samples[s] ],samplesleg[s].c_str(), "f");
    }
    for(unsigned int s = legcount3l+1; s<samples.size()-1;++s){
        if(is3lSS[s]==0||is3lSS[s]==2) leg23l->AddEntry(h[histonames[0]+"_"+samples[s] ],samplesleg[s].c_str(), "f");
    }
    leg1->AddEntry(h[histonames[0]+"_"+samples[0] ],samplesleg[0].c_str(), "l");
    leg2->AddEntry(h[histonames[0]+"_"+samples[0] ],samplesleg[0].c_str(), "l");
    leg2SS->AddEntry(h[histonames[0]+"_"+samples[0] ],samplesleg[0].c_str(), "l");
    leg23l->AddEntry(h[histonames[0]+"_"+samples[0] ],samplesleg[0].c_str(), "l");
    if(twosig&&!addsig){
        leg1->AddEntry(h[histonames[0]+"_"+samples[1] ],samplesleg[1].c_str(), "l");
        leg2->AddEntry(h[histonames[0]+"_"+samples[1] ],samplesleg[1].c_str(), "l");
        leg2SS->AddEntry(h[histonames[0]+"_"+samples[1] ],samplesleg[1].c_str(), "l");
        leg23l->AddEntry(h[histonames[0]+"_"+samples[1] ],samplesleg[1].c_str(), "l");
    }
    if(data){
        leg1->AddEntry(h[histonames[0]+"_Data" ],"Data", "ep");
        leg2->AddEntry(h[histonames[0]+"_Data" ],"Data", "ep");
        leg2SS->AddEntry(h[histonames[0]+"_Data" ],"Data", "ep");
        leg23l->AddEntry(h[histonames[0]+"_Data" ],"Data", "ep");
    }

    for(unsigned int n = 0; n<histonames.size();++n){
      TCanvas *c1 = new TCanvas("c1", "",334,192,600,600);
      c1->SetFillColor(0);
      c1->SetBorderMode(0);
      c1->SetBorderSize(2);
      //if(logy) c1->SetLogy();    // Log y
      c1->SetTickx(1);
      c1->SetTicky(1);
      c1->SetLeftMargin(0.18);
      c1->SetRightMargin(0.05);
      c1->SetTopMargin(0.07);
      c1->SetBottomMargin(0.15);
      c1->SetFrameFillStyle(0);
      c1->SetFrameBorderMode(0);
      c1->SetFrameFillStyle(0);
      c1->SetFrameBorderMode(0);
      TPad *plotpad = new TPad("plotpad", "Pad containing the overlay plot",0,0.165,1,1);//0,0.18,1,1);
      plotpad->Draw();
      plotpad->cd();
      plotpad->Range(-85.71429,-3.864499,628.5714,6.791402);//(133.1169,-3.101927,782.4675,0.7583922);
      plotpad->SetFillColor(0);
      plotpad->SetBorderMode(0);
      plotpad->SetBorderSize(2);
      if(logy) plotpad->SetLogy();
      plotpad->SetTickx(1);
      plotpad->SetTicky(1);
      plotpad->SetLeftMargin(0.12);
      plotpad->SetRightMargin(0.04);
      plotpad->SetTopMargin(0.05);
      // plotpad->SetBottomMargin(0.15);
      plotpad->SetFrameFillStyle(0);
      plotpad->SetFrameBorderMode(0);
      plotpad->SetFrameFillStyle(0);
      plotpad->SetFrameBorderMode(0);
        
      plotpad->cd();
    
      string stackname = histonames[n];
      string bgname = stackname + "_bg";
      //cout << stackname << endl;
      double max;
      if(data) max = TMath::Max((h[bgname]->GetBinContent(h[bgname]->GetMaximumBin() )+0.5*h[bgname]->GetBinError(h[bgname]->GetMaximumBin() ) ),(h[stackname+"_Data"]->GetBinContent(h[stackname+"_Data"]->GetMaximumBin() )+0.5*h[stackname+"_Data"]->GetBinError(h[stackname+"_Data"]->GetMaximumBin() ) ) )*1.667;
      else max = (h[bgname]->GetBinContent(h[bgname]->GetMaximumBin() )+0.5*h[bgname]->GetBinError(h[bgname]->GetMaximumBin()))*1.667;
      stack[stackname]->SetMaximum(max);
      stack[stackname]->Draw("hist");
      h[bgname]->Draw("sameE2");
      if(data&&h[stackname+"_Data"]->Integral()!=0) h[stackname+"_Data"]->Draw("sameE0X0");
      string signame = stackname + "_"+ samples[0];
      h[signame]->Draw("histsame");
      signame = stackname + "_"+ samples[1];
      if(twosig) h[signame]->Draw("histsame");
      string outname = stackname + ".pdf";
      if(logy) outname = outdir + "log/" + outname;
      else     outname = outdir + outname;

      if(onlySSSFOS[n]==0){ leg1  ->Draw(); leg2  ->Draw(); }
      if(onlySSSFOS[n]==1){ leg1SS->Draw(); leg2SS->Draw(); }
      if(onlySSSFOS[n]==2){ leg13l->Draw(); leg23l->Draw(); }
      tLumi->Draw();
      tCMS->Draw();
      tSim->Draw();
      /*
	if(stackname.find("SSee" )  !=string::npos) tlx->DrawLatex(0.45,0.955,"e^{#pm}e^{#pm}");
	if(stackname.find("SSem" )  !=string::npos) tlx->DrawLatex(0.45,0.955,"e^{#pm}#mu^{#pm}");
	if(stackname.find("SSmm" )  !=string::npos) tlx->DrawLatex(0.45,0.955,"#mu^{#pm}#mu^{#pm}");
	if(stackname.find("allSS")  !=string::npos) tlx->DrawLatex(0.45,0.955,"SS region");
	if(stackname.find("0SFOS")  !=string::npos) tlx->DrawLatex(0.45,0.955,"0 SFOS pairs");
	if(stackname.find("1SFOS")  !=string::npos) tlx->DrawLatex(0.45,0.955,"1 SFOS pair");
	if(stackname.find("2SFOS")  !=string::npos) tlx->DrawLatex(0.45,0.955,"2 SFOS pairs");
	if(stackname.find("allSFOS")!=string::npos) tlx->DrawLatex(0.45,0.955,"3l region");
      */
      c1->cd();
      TPad *ratiopad = new TPad("ratiopad", "Pad containing the ratio",0,0,1,0.21); //0,0,1,0.26);
      ratiopad->Draw();
      ratiopad->cd();
      ratiopad->SetFillColor(0);
      ratiopad->SetBorderMode(0);
      ratiopad->SetBorderSize(2);
      ratiopad->SetTickx(1);
      ratiopad->SetTicky(1);
      ratiopad->SetLeftMargin(0.12);
      ratiopad->SetRightMargin(0.04);
      //  ratiopad->SetTopMargin(0.04);
      ratiopad->SetBottomMargin(0.3);
      ratiopad->SetFrameFillStyle(0);
      ratiopad->SetFrameBorderMode(0);
      ratiopad->SetFrameFillStyle(0);
      ratiopad->SetFrameBorderMode(0);
      if(data&&h[stackname+"_Data"]->Integral()!=0){
	rat[stackname]->SetMinimum(0.);
	rat[stackname]->SetMaximum(2.);
	rat[stackname+"BG"]->SetMinimum(0.);
	rat[stackname+"BG"]->SetMaximum(2.);
      }
      else {
	rat[stackname]->SetMinimum(0.);
	rat[stackname]->SetMaximum(0.3333);
	rat[stackname+"BG"]->SetMinimum(0.);
	rat[stackname+"BG"]->SetMaximum(0.3333);
      }
      rat[stackname]->GetXaxis()->SetTitle(axisnames[n].c_str());
      rat[stackname]->GetXaxis()->SetTitleSize(0.16);
      rat[stackname]->GetXaxis()->SetTitleOffset(0.76);
      rat[stackname]->GetXaxis()->SetLabelSize(0.0);
      rat[stackname]->GetYaxis()->SetNdivisions(504);
      rat[stackname]->GetYaxis()->SetTitle("signal / bgd");
      if(data&&h[stackname+"_Data"]->Integral()!=0) rat[stackname]->GetYaxis()->SetTitle("data / bgd");
      rat[stackname]->GetYaxis()->SetTitleSize(0.14);
      rat[stackname]->GetYaxis()->SetTitleOffset(0.28);
      rat[stackname]->GetYaxis()->SetLabelSize(0.14);
      rat[stackname+"BG"]->GetXaxis()->SetTitle(axisnames[n].c_str());
      rat[stackname+"BG"]->GetXaxis()->SetTitleSize(0.16);
      rat[stackname+"BG"]->GetXaxis()->SetTitleOffset(0.76);
      rat[stackname+"BG"]->GetXaxis()->SetLabelSize(0.0);
      rat[stackname+"BG"]->GetYaxis()->SetNdivisions(504);
      rat[stackname+"BG"]->GetYaxis()->SetTitle("signal / bgd");
      if(data&&h[stackname+"_Data"]->Integral()!=0) rat[stackname+"BG"]->GetYaxis()->SetTitle("data / bgd");
      rat[stackname+"BG"]->GetYaxis()->SetTitleSize(0.14);
      rat[stackname+"BG"]->GetYaxis()->SetTitleOffset(0.28);
      rat[stackname+"BG"]->GetYaxis()->SetLabelSize(0.14);
      if(plotsimErrorHashed){
	if(data&&h[stackname+"_Data"]->Integral()!=0) rat[stackname+"BG"]->Draw("E2");
	if(data&&h[stackname+"_Data"]->Integral()!=0) rat[stackname]->Draw("sameE0X0");
	else                                          rat[stackname]->Draw("samehist");
      } else {
	if(data&&h[stackname+"_Data"]->Integral()!=0) rat[stackname]->Draw("E0X0");
	else                                          rat[stackname]->Draw("hist");
      }
      if(!addsig&&twosig&&!data){
	rat[stackname+"v2"]->SetMinimum(0.);
	rat[stackname+"v2"]->SetMaximum(0.2);
	rat[stackname+"v2"]->GetXaxis()->SetTitle(axisnames[n].c_str());
	rat[stackname+"v2"]->GetXaxis()->SetTitleSize(0.16);
	rat[stackname+"v2"]->GetXaxis()->SetTitleOffset(0.76);
	rat[stackname+"v2"]->GetXaxis()->SetLabelSize(0.0);
	rat[stackname+"v2"]->GetYaxis()->SetNdivisions(504);
	rat[stackname+"v2"]->GetYaxis()->SetTitle("signal / bgd");
	if(data) rat[stackname+"v2"]->GetYaxis()->SetTitle("data / bgd");
	rat[stackname+"v2"]->GetYaxis()->SetTitleSize(0.14);
	rat[stackname+"v2"]->GetYaxis()->SetTitleOffset(0.28);
	rat[stackname+"v2"]->GetYaxis()->SetLabelSize(0.14);
	rat[stackname+"v2"]->Draw("same");
      }
      if(data&&h[stackname+"_Data"]->Integral()!=0){
	TLine *rline = new TLine(rat[stackname]->GetXaxis()->GetBinLowEdge(1),1.,rat[stackname]->GetXaxis()->GetBinLowEdge(rat[stackname]->GetNbinsX()+1),1.);
	rline->SetLineWidth(2);
	rline->SetLineStyle(7);
	rline->Draw();
      }
      c1->cd();
      c1->SaveAs(outname.c_str());
      //c1->Clear();
      c1->cd();
    }
}
