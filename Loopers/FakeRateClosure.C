// Usage:
// > root -b doAll.C

// C++
#include <iostream>
#include <vector>
#include <map>

// ROOT
#include "TBenchmark.h"
#include "TChain.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TH3D.h"
#include "TH2F.h"
#include "TROOT.h"
#include "TTreeCache.h"
#include "TLorentzVector.h"
#include <sstream>
#include <iostream>
#include <fstream>

// CMS3
#include "Functions.h"
#include "CMS3_WWW0117.cc"
#include "../CORE/Tools/dorky/dorky.h"
#include "../CORE/Tools/dorky/dorky.cc"
#include "../CORE/Tools/goodrun.h"
#include "../CORE/Tools/goodrun.cc"

using namespace std;
using namespace tas;
//using namespace mt2_bisect;

int ScanChain( TChain* chain, bool fast = true, int nEvents = -1, string skimFilePrefix = "test", int chainnumber=1) {

  bool blindSR = false;
  bool btagreweighting = true;
  bool applylepSF      = true;
  bool applytrigSF     = true;
  bool applyPUrewgt    = true;
  bool closuretest     = true;//if true use QCD fake rate
  const char* json_file = "data/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt";
  set_goodrun_file_json(json_file);

  // Benchmark
  TBenchmark *bmark = new TBenchmark();
  bmark->Start("benchmark");

  // Example Histograms
  TDirectory *rootdir = gDirectory->GetDirectory("Rint:");

  vector<string> histonames; histonames.clear();
  vector<int> hbins; hbins.clear();
  vector<float> hlow; hlow.clear();
  vector<float> hup; hup.clear();
  histonames.push_back("SRyield");                                      hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  //use cone correction only to extract fake rate
  histonames.push_back("ARyield");                                      hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("FakeEstimation");                               hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("FakeEstimationFRup");                           hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("FakeEstimationFRdn");                           hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("FakeEstimationClosureup");                      hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("FakeEstimationClosuredn");                      hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);

  histonames.push_back("njets");                              hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("nbjets");                             hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("pTl1");                               hbins.push_back(15);  hlow.push_back( 0); hup.push_back(225);
  histonames.push_back("pTl2");                               hbins.push_back(15);  hlow.push_back( 0); hup.push_back(225);
  histonames.push_back("Mjj");                                hbins.push_back(15);  hlow.push_back( 0); hup.push_back(300);
  histonames.push_back("Mll");                                hbins.push_back(15);  hlow.push_back( 0); hup.push_back(225);
  histonames.push_back("MET");                                hbins.push_back(15);  hlow.push_back( 0); hup.push_back(150);
  histonames.push_back("MTmax");                              hbins.push_back(15);  hlow.push_back( 0); hup.push_back(225);
  histonames.push_back("njets_fakesPred");                              hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("nbjets_fakesPred");                             hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("pTl1_fakesPred");                               hbins.push_back(15);  hlow.push_back( 0); hup.push_back(225);
  histonames.push_back("pTl2_fakesPred");                               hbins.push_back(15);  hlow.push_back( 0); hup.push_back(225);
  histonames.push_back("Mjj_fakesPred");                                hbins.push_back(15);  hlow.push_back( 0); hup.push_back(300);
  histonames.push_back("Mll_fakesPred");                                hbins.push_back(15);  hlow.push_back( 0); hup.push_back(225);
  histonames.push_back("MET_fakesPred");                                hbins.push_back(15);  hlow.push_back( 0); hup.push_back(150);
  histonames.push_back("MTmax_fakesPred");                              hbins.push_back(15);  hlow.push_back( 0); hup.push_back(225);

  histonames.push_back("el_njets");                              hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("el_nbjets");                             hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("el_pTl1");                               hbins.push_back(15);  hlow.push_back( 0); hup.push_back(225);
  histonames.push_back("el_pTl2");                               hbins.push_back(15);  hlow.push_back( 0); hup.push_back(225);
  histonames.push_back("el_Mjj");                                hbins.push_back(15);  hlow.push_back( 0); hup.push_back(300);
  histonames.push_back("el_Mll");                                hbins.push_back(15);  hlow.push_back( 0); hup.push_back(225);
  histonames.push_back("el_MET");                                hbins.push_back(15);  hlow.push_back( 0); hup.push_back(150);
  histonames.push_back("el_MTmax");                              hbins.push_back(15);  hlow.push_back( 0); hup.push_back(225);
  histonames.push_back("el_njets_fakesPred");                              hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("el_nbjets_fakesPred");                             hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("el_pTl1_fakesPred");                               hbins.push_back(15);  hlow.push_back( 0); hup.push_back(225);
  histonames.push_back("el_pTl2_fakesPred");                               hbins.push_back(15);  hlow.push_back( 0); hup.push_back(225);
  histonames.push_back("el_Mjj_fakesPred");                                hbins.push_back(15);  hlow.push_back( 0); hup.push_back(300);
  histonames.push_back("el_Mll_fakesPred");                                hbins.push_back(15);  hlow.push_back( 0); hup.push_back(225);
  histonames.push_back("el_MET_fakesPred");                                hbins.push_back(15);  hlow.push_back( 0); hup.push_back(150);
  histonames.push_back("el_MTmax_fakesPred");                              hbins.push_back(15);  hlow.push_back( 0); hup.push_back(225);

  histonames.push_back("mu_njets");                              hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("mu_nbjets");                             hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("mu_pTl1");                               hbins.push_back(15);  hlow.push_back( 0); hup.push_back(225);
  histonames.push_back("mu_pTl2");                               hbins.push_back(15);  hlow.push_back( 0); hup.push_back(225);
  histonames.push_back("mu_Mjj");                                hbins.push_back(15);  hlow.push_back( 0); hup.push_back(300);
  histonames.push_back("mu_Mll");                                hbins.push_back(15);  hlow.push_back( 0); hup.push_back(225);
  histonames.push_back("mu_MET");                                hbins.push_back(15);  hlow.push_back( 0); hup.push_back(150);
  histonames.push_back("mu_MTmax");                              hbins.push_back(15);  hlow.push_back( 0); hup.push_back(225);
  histonames.push_back("mu_njets_fakesPred");                              hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("mu_nbjets_fakesPred");                             hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("mu_pTl1_fakesPred");                               hbins.push_back(15);  hlow.push_back( 0); hup.push_back(225);
  histonames.push_back("mu_pTl2_fakesPred");                               hbins.push_back(15);  hlow.push_back( 0); hup.push_back(225);
  histonames.push_back("mu_Mjj_fakesPred");                                hbins.push_back(15);  hlow.push_back( 0); hup.push_back(300);
  histonames.push_back("mu_Mll_fakesPred");                                hbins.push_back(15);  hlow.push_back( 0); hup.push_back(225);
  histonames.push_back("mu_MET_fakesPred");                                hbins.push_back(15);  hlow.push_back( 0); hup.push_back(150);
  histonames.push_back("mu_MTmax_fakesPred");                              hbins.push_back(15);  hlow.push_back( 0); hup.push_back(225);
  map<string, TH1D*> histos =  bookhistclosure(skimFilePrefix, histonames,hbins, hlow, hup, rootdir);
  cout << "Loaded histograms" << endl;

  unsigned int nEventsRunning = 0;
  // Loop over events to Analyze
  unsigned int nEventsTotal = 0;
  unsigned int nEventsChain = chain->GetEntries();
  if( nEvents >= 0 ) nEventsChain = nEvents;
  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;

  // File Loop
  while ( (currentFile = (TFile*)fileIter.Next()) ) {

    // Get File Content
    TFile *file = new TFile( currentFile->GetTitle() );
    string fname = currentFile->GetTitle();

    TTree *tree = (TTree*)file->Get("t");
    if(fast) TTreeCache::SetLearnEntries(10);
    if(fast) tree->SetCacheSize(128*1024*1024);
    cms3.Init(tree);
    cout << "File " <<  currentFile->GetTitle() << endl;
    // Loop over Events in current file
    if( nEventsTotal >= nEventsChain ) continue;
    unsigned int nEventsTree = tree->GetEntriesFast();
    for( unsigned int event = 0; event < nEventsTree; ++event) {
 
      // Get Event Content
      if( nEventsTotal >= nEventsChain ) continue;
      if(fast) tree->LoadTree(event);
      cms3.GetEntry(event);
      ++nEventsTotal;

      // Progress
      CMS3::progress( nEventsTotal, nEventsChain );
      
      double weight = evt_scale1fb()*35.9;
      //if(nEventsTotal==0) cout << weight << endl; 

      if(nVert()<0)              continue;
      //if(nlep()<2)               continue;

      //weight = 1;
      if(string(currentFile->GetTitle()).find("wjets_incl_mgmlm_")!=string::npos){
	if(gen_ht()>100) continue;
      }
      if(string(currentFile->GetTitle()).find("dy_m50_mgmlm_ext1_")!=string::npos){
	if(gen_ht()>100) continue;
      }
      if(string(currentFile->GetTitle()).find("www_2l_mia")!=string::npos) weight *= 0.066805*91900./(91900.+164800.);//(208fb/1pb)*BR(WWW—> >=2l)*combineweight
      if(string(currentFile->GetTitle()).find("www_2l_ext1_mia")!=string::npos) weight *= 0.066805*164800./(91900.+164800.);//(208fb/1pb)*BR(WWW—> >=2l)*combineweight
      if(weight>100) cout << weight << " " << currentFile->GetTitle() << endl;
      if(isData()) weight = 1.;
      if(!isData()&&btagreweighting) weight *= weight_btagsf();
      float PUweight(1.), PUweightup(1.), PUweightdn(1.);
      if(applyPUrewgt&&!isData()){
	PUweight = getPUWeightAndError(PUweightdn,PUweightup);
	weight *= PUweight;
      }
      
      LorentzVector MET; MET.SetPxPyPzE(met_pt()*TMath::Cos(met_phi()),met_pt()*TMath::Sin(met_phi()),0,met_pt());
      int nj(0), nb(0), nj30(0);
      getalljetnumbers(nj,nj30,nb);
      float Mjj = -1;
      float MjjL = -1; float Detajj = -1;
      getMjjAndDeta(Mjj,MjjL,Detajj);

      vector<int> vSS,   v3l,   iSS,   i3l; //lepton indices for both the SS and 3l signal regions
      vector<int> vaSS,  va3l,  iaSS,  ia3l;//loose, but not tight leptons.
      getleptonindices(iSS, i3l, iaSS, ia3l, vSS, v3l, vaSS, va3l);
      float lepSF(1.), lepSFerr(0.);//i3l and iSS have same ID
      if(applylepSF&&!isData()){
	lepSF = getlepSFWeightandError(lepSFerr,i3l,ia3l);
	weight *= lepSF;
      }
      float trigSF(1.), trigSFerr(1.);
      if(applytrigSF&&!isData()){
	trigSF    = getTriggerWeightandError(trigSFerr, i3l,ia3l);
	weight *= trigSF;
      }
      int nvetoSS = vSS.size();
      int nveto3l = v3l.size();
      int nSS = iSS.size();
      int n3l = i3l.size();
      int nvetoaSS = vaSS.size();
      int nvetoa3l = va3l.size();
      int naSS = iaSS.size();
      int na3l = ia3l.size();
      
      bool passofflineforTrigger = passofflineTriggers(i3l, ia3l);
      if(!passofflineforTrigger) continue;
      
      if(isData()){
	if(!passFilters()) continue;
	duplicate_removal::DorkyEventIdentifier id(tas::run(), tas::evt(), tas::lumi());
	if( is_duplicate(id)        ) { /*cout << "Event " << tas::run() << ":" << tas::lumi() << ":" << tas::run() << " is duplicated." << endl;*/ continue; }
	if( !goodrun(tas::run(), tas::lumi()) ) continue;
	bool passonlineTrigger = passonlineTriggers(i3l, ia3l);//currently applied only to data
	if(!passonlineTrigger) continue;
      }

      string sample   = skimFilePrefix;
      string sn       = iSS.size() >=2  ? leptype(iSS[0]) : string("unknown");
      string sn2      = iSS.size() >=2  ? leptype(iSS[1]) : string("unknown");
      string sn3      = iaSS.size() >0  ? leptype(iaSS[0]): string("unknown");
      if(!TString(sn).Contains("fake") && !TString(sn2).Contains("fake") && !TString(sn3).Contains("fake")) continue;//none of selected leptons are fakes
      string sn_event = TString(sn).Contains("fake") ? sn : sn2;

      bool isphotonSS = (sn =="photonfakes");
      bool isphoton3l = (sn2=="photonfakes");
      bool isfakeSS   = (sn =="fakes");
      bool isfake3l   = (sn2=="fakes");
      int subtract = 1;
      //if( !isData()&&(!isfakeSS&&!isfake3l)) subtract = -1;
      if(splitVH(fname)){ sample = "WHtoWWW"; }

      float MTmax = -1;
      if(iSS.size()==2) MTmax = calcMTmax(iSS,MET);
      else if(iSS.size()==1&&iaSS.size()>=1){
	vector<int> temp; temp.push_back(iSS[0]); temp.push_back(iaSS[0]);
	MTmax = calcMTmax(temp,MET);
      }
      float MTmax3l = calcMTmax(i3l,MET,true);

      int SRSS[4]; bool selects3l[4];
      int SR3l[4]; bool btag = false;
      for(int i = 0; i<4; ++i) { SRSS[i] = -1; SR3l[i] = -1; selects3l[i] = false; }
      //SS
      //0: SR
      SRSS[0] = isSRSS(iSS,      vSS,false,MTmax,  nj30,nb,Mjj,MjjL,Detajj, MET,0,btag);
      //1: SR preselect
      SRSS[1] = isSRSS(iSS,      vSS,true ,MTmax,  nj30,nb,Mjj,MjjL,Detajj, MET,0,btag);
      //2: AR
      SRSS[2] = isARSS(iSS,iaSS,vaSS,false,MTmax,  nj30,nb,Mjj,MjjL,Detajj, MET,0, btag);
      //3: AR preselect
      SRSS[3] = isARSS(iSS,iaSS,vaSS,true ,MTmax,  nj30,nb,Mjj,MjjL,Detajj, MET,0,btag);
      //3l
      //0: SR
      SR3l[0] = isSR3l(i3l,     false,nj,nb,MET,0,btag);
      //1: SR preselect
      SR3l[1] = isSR3l(i3l,     true ,nj,nb,MET,0,btag);
      //2: AR
      SR3l[2] = isAR3l(i3l,ia3l,false,nj,nb,MET,0,btag);
      //3: AR preselect
      SR3l[3] = isAR3l(i3l,ia3l,true ,nj,nb,MET,0,btag);

      // skip event if it's not preselection SS SR or AR
      if(SRSS[1]<0 && SRSS[3]<0) continue;      
 
      for(int i = 0; i<4; ++i) {
        if(!selects3l[i]){
          if(vetophotonprocess(fname,isphotonSS))    { SRSS[i] = -1; }
        }
        else if(vetophotonprocess(fname,isphoton3l)){ SRSS[i] = -1; }
        if(vetophotonprocess(fname,isphoton3l))     { SR3l[i] = -1; }
      }

      float closureSSerr = 0.;
      if(iaSS.size()>0) closureSSerr = getlepFRClosureError(iaSS[0],!closuretest,true) * subtract;
      
      float SFSS(0.), SFSSerr(0.), SF3l(0.), SF3lerr(0.);
      float noconeSFSS(0.), noconeSFSSerr(0.), noconeSF3l(0.), noconeSF3lerr(0.);
      if(SRSS[3]>=0){
	SFSS       = getlepFRWeightandError(SFSSerr,      iaSS[0],!closuretest) * subtract;
	noconeSFSS = getlepFRWeightandError(noconeSFSSerr,iaSS[0],!closuretest,false)* subtract;
      }
      
      float Mll = -999; 
      // fill in fake leptons in the SR
      int fakelep =  TString(sn).Contains("fake") ? 0:1;
      if(SRSS[ 1]>=0){
        // it always fill the histogram with _sample. this is ok?
	if( TString(sn).Contains("fake"))  fillhisto(histos, "pTl1",   sample, sn, lep_p4()[iSS[0] ].pt(),                          weight);
        if( TString(sn2).Contains("fake")) fillhisto(histos, "pTl2",   sample, sn2, lep_p4()[iSS[1] ].pt(),                         weight);
	fillhisto(histos, "Mjj",    sample, sn_event, Mjj,                                       weight);
	fillhisto(histos, "njets",  sample, sn_event, nj30,                                      weight);
	fillhisto(histos, "nbjets", sample, sn_event, nb,                                        weight);
	fillhisto(histos, "Mll",    sample, sn_event, (lep_p4()[iSS[0] ]+lep_p4()[iSS[1] ]).M(), weight);
	fillhisto(histos, "MTmax",  sample, sn_event, MTmax,                                     weight);
	fillhisto(histos, "MET",    sample, sn_event, met_pt(),                                  weight);
      if(abs(lep_pdgId().at(iSS[fakelep])) == 11) { 
	if( TString(sn).Contains("fake")) fillhisto(histos, "el_pTl1",   sample, sn, lep_p4()[iSS[0] ].pt(),                          weight);
        if( TString(sn2).Contains("fake"))fillhisto(histos, "el_pTl2",   sample, sn2, lep_p4()[iSS[1] ].pt(),                         weight);
	fillhisto(histos, "el_Mjj",    sample, sn_event, Mjj,                                       weight);
	fillhisto(histos, "el_njets",  sample, sn_event, nj30,                                      weight);
	fillhisto(histos, "el_nbjets", sample, sn_event, nb,                                        weight);
	fillhisto(histos, "el_Mll",    sample, sn_event, (lep_p4()[iSS[0] ]+lep_p4()[iSS[1] ]).M(), weight);
	fillhisto(histos, "el_MTmax",  sample, sn_event, MTmax,                                     weight);
	fillhisto(histos, "el_MET",    sample, sn_event, met_pt(),                                  weight);
         }   
      if(abs(lep_pdgId().at(iSS[fakelep])) == 13) {
	if( TString(sn).Contains("fake"))  fillhisto(histos, "mu_pTl1",   sample, sn, lep_p4()[iSS[0] ].pt(),                          weight);
        if( TString(sn2).Contains("fake")) fillhisto(histos, "mu_pTl2",   sample, sn2, lep_p4()[iSS[1] ].pt(),                         weight);
	fillhisto(histos, "mu_Mjj",    sample, sn_event, Mjj,                                       weight);
	fillhisto(histos, "mu_njets",  sample, sn_event, nj30,                                      weight);
	fillhisto(histos, "mu_nbjets", sample, sn_event, nb,                                        weight);
	fillhisto(histos, "mu_Mll",    sample, sn_event, (lep_p4()[iSS[0] ]+lep_p4()[iSS[1] ]).M(), weight);
	fillhisto(histos, "mu_MTmax",  sample, sn_event, MTmax,                                     weight);
	fillhisto(histos, "mu_MET",    sample, sn_event, met_pt(),                                  weight);
        }
        }
	if(SRSS[3]>=0) {
	  if(lep_p4()[iSS[0] ].pt()>lep_p4()[iaSS[0] ].pt() ) fillhisto(histos, "pTl2_fakesPred",   sample, sn3, lep_p4()[iaSS[0] ].pt(),                     weight*SFSS);
	  if(lep_p4()[iSS[0] ].pt()<lep_p4()[iaSS[0] ].pt() ) fillhisto(histos, "pTl1_fakesPred",   sample, sn3, lep_p4()[iaSS[0] ].pt(),                     weight*SFSS);
	  fillhisto(histos, "Mjj_fakesPred",    sample, sn3, Mjj,                                        weight*SFSS);
	  fillhisto(histos, "njets_fakesPred",  sample, sn3, nj30,                                       weight*SFSS);
	  fillhisto(histos, "nbjets_fakesPred", sample, sn3, nb,                                         weight*SFSS);
	  fillhisto(histos, "Mll_fakesPred",    sample, sn3, (lep_p4()[iSS[0] ]+lep_p4()[iaSS[0] ]).M(), weight*SFSS);
	  fillhisto(histos, "MTmax_fakesPred",  sample, sn3, MTmax,                                      weight*SFSS);
	  fillhisto(histos, "MET_fakesPred",    sample, sn3, met_pt(),                                   weight*SFSS);

          if(abs(lep_pdgId().at(iaSS[0])) == 11){
	  if(lep_p4()[iSS[0] ].pt()>lep_p4()[iaSS[0] ].pt() ) fillhisto(histos, "el_pTl2_fakesPred",   sample, sn3, lep_p4()[iaSS[0] ].pt(),                     weight*SFSS);
	  if(lep_p4()[iSS[0] ].pt()<lep_p4()[iaSS[0] ].pt() ) fillhisto(histos, "el_pTl1_fakesPred",   sample, sn3, lep_p4()[iaSS[0] ].pt(),                     weight*SFSS);
	  fillhisto(histos, "el_Mjj_fakesPred",    sample, sn3, Mjj,                                        weight*SFSS);
	  fillhisto(histos, "el_njets_fakesPred",  sample, sn3, nj30,                                       weight*SFSS);
	  fillhisto(histos, "el_nbjets_fakesPred", sample, sn3, nb,                                         weight*SFSS);
	  fillhisto(histos, "el_Mll_fakesPred",    sample, sn3, (lep_p4()[iSS[0] ]+lep_p4()[iaSS[0] ]).M(), weight*SFSS);
	  fillhisto(histos, "el_MTmax_fakesPred",  sample, sn3, MTmax,                                      weight*SFSS);
	  fillhisto(histos, "el_MET_fakesPred",    sample, sn3, met_pt(),                                   weight*SFSS);
          }
          if(abs(lep_pdgId().at(iaSS[0])) == 13){
	  if(lep_p4()[iSS[0] ].pt()>lep_p4()[iaSS[0] ].pt() ) fillhisto(histos, "mu_pTl2_fakesPred",   sample, sn3, lep_p4()[iaSS[0] ].pt(),                     weight*SFSS);
	  if(lep_p4()[iSS[0] ].pt()<lep_p4()[iaSS[0] ].pt() ) fillhisto(histos, "mu_pTl1_fakesPred",   sample, sn3, lep_p4()[iaSS[0] ].pt(),                     weight*SFSS);
	  fillhisto(histos, "mu_Mjj_fakesPred",    sample, sn3, Mjj,                                        weight*SFSS);
	  fillhisto(histos, "mu_njets_fakesPred",  sample, sn3, nj30,                                       weight*SFSS);
	  fillhisto(histos, "mu_nbjets_fakesPred", sample, sn3, nb,                                         weight*SFSS);
	  fillhisto(histos, "mu_Mll_fakesPred",    sample, sn3, (lep_p4()[iSS[0] ]+lep_p4()[iaSS[0] ]).M(), weight*SFSS);
	  fillhisto(histos, "mu_MTmax_fakesPred",  sample, sn3, MTmax,                                      weight*SFSS);
	  fillhisto(histos, "mu_MET_fakesPred",    sample, sn3, met_pt(),                                   weight*SFSS);
          }
	}
    }//event loop
    // Clean Up
    delete tree;
    file->Close();
    delete file;
  }//file loop
  if ( nEventsChain != nEventsTotal ) {
    cout << Form( "ERROR: number of events from files (%d) is not equal to total number of events (%d)", nEventsChain, nEventsTotal ) << endl;
  }

  SaveHistosToFile("rootfiles/FakeRateClosureHistograms.root",histos,true,true,(chainnumber==0));
  deleteHistograms(histos);

  // return
  bmark->Stop("benchmark");
  cout << endl;
  cout << nEventsTotal << " Events Processed" << endl;
  cout << "------------------------------" << endl;
  cout << "CPU  Time:	" << Form( "%.01f", bmark->GetCpuTime("benchmark")  ) << endl;
  cout << "Real Time:	" << Form( "%.01f", bmark->GetRealTime("benchmark") ) << endl;
  cout << endl;
  delete bmark;
  return 0;
}
