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
#include "CMS3_WWW0116.cc"
#include "../CORE/Tools/dorky/dorky.h"
#include "../CORE/Tools/dorky/dorky.cc"
#include "../CORE/Tools/goodrun.h"
#include "../CORE/Tools/goodrun.cc"

using namespace std;
using namespace tas;
//using namespace mt2_bisect;

int ScanChain( TChain* chain, bool fast = true, int nEvents = -1, string skimFilePrefix = "test") {

  bool blindSR = true;
  bool btagreweighting = true;
  bool applylepSF      = true;
  bool applytrigSF     = true;
  bool applyPUrewgt    = true;
  bool closuretest     = false;//if true use QCD fake rate
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
  histonames.push_back("FakeEstimationEvsMu");                          hbins.push_back( 2); hlow.push_back(    0); hup.push_back(2);
  histonames.push_back("SRyieldEvsMu");                                 hbins.push_back( 2); hlow.push_back(    0); hup.push_back(2);
  histonames.push_back("RawSRyieldEvsMu");                              hbins.push_back( 2); hlow.push_back(    0); hup.push_back(2);
  histonames.push_back("ARyieldEvsMu");                                 hbins.push_back( 2); hlow.push_back(    0); hup.push_back(2);
  histonames.push_back("RawARyieldEvsMu");                              hbins.push_back( 2); hlow.push_back(    0); hup.push_back(2);
  histonames.push_back("PreselFakeEstimationEvsMu");                    hbins.push_back( 2); hlow.push_back(    0); hup.push_back(2);
  histonames.push_back("PreselSRyieldEvsMu");                           hbins.push_back( 2); hlow.push_back(    0); hup.push_back(2);
  histonames.push_back("RawPreselSRyieldEvsMu");                        hbins.push_back( 2); hlow.push_back(    0); hup.push_back(2);
  histonames.push_back("PreselARyieldEvsMu");                           hbins.push_back( 2); hlow.push_back(    0); hup.push_back(2);
  histonames.push_back("RawPreselARyieldEvsMu");                        hbins.push_back( 2); hlow.push_back(    0); hup.push_back(2);

  histonames.push_back("SRyield");                                      hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("PreselSRyield");                                hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  //use cone correction only to extract fake rate
  histonames.push_back("ARyield");                                      hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("FakeEstimation");                               hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("FakeEstimationFRup");                           hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("FakeEstimationFRdn");                           hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("FakeEstimationClosureup");                      hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("FakeEstimationClosuredn");                      hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  //do not use cone corrections to extract fake rate
  histonames.push_back("NoConeCorrARyield");                            hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("NoConeCorrFakeEstimation");                     hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("NoConeCorrFakeEstimationFRup");                 hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("NoConeCorrFakeEstimationFRdn");                 hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("NoConeCorrFakeEstimationClosureup");            hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("NoConeCorrFakeEstimationClosuredn");            hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  //use cone correction only to extract fake rate - preselection
  histonames.push_back("PreselARyield");                                hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("PreselFakeEstimation");                         hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("PreselFakeEstimationFRup");                     hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("PreselFakeEstimationFRdn");                     hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("PreselFakeEstimationClosureup");                hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("PreselFakeEstimationClosuredn");                hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);

  histonames.push_back("SRyield_Mjjsideband");                          hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("PreselSRyield_Mjjsideband");                    hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("ARyield_Mjjsideband");                          hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("FakeEstimation_Mjjsideband");                   hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("FakeEstimationFRup_Mjjsideband");               hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("FakeEstimationFRdn_Mjjsideband");               hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("PreselARyield_Mjjsideband");                    hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("PreselFakeEstimation_Mjjsideband");             hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("PreselFakeEstimationFRup_Mjjsideband");         hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("PreselFakeEstimationFRdn_Mjjsideband");         hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("SRyield_MjjsidebandlowMET");                    hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("PreselSRyield_MjjsidebandlowMET");              hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("ARyield_MjjsidebandlowMET");                    hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("FakeEstimation_MjjsidebandlowMET");             hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("FakeEstimationFRup_MjjsidebandlowMET");         hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("FakeEstimationFRdn_MjjsidebandlowMET");         hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("PreselARyield_MjjsidebandlowMET");              hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("PreselFakeEstimation_MjjsidebandlowMET");       hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("PreselFakeEstimationFRup_MjjsidebandlowMET");   hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("PreselFakeEstimationFRdn_MjjsidebandlowMET");   hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  
  map<string, TH1D*> histos =  bookhistograms(skimFilePrefix, histonames,hbins, hlow, hup, rootdir);
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
      
      if((n3l+na3l)<2) continue;
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

      string sn = skimFilePrefix;
      string sn2 = skimFilePrefix;
      string temp = process(fname,true ,iSS,iaSS);
      string temp2 = process(fname,false,i3l,ia3l);
      bool isphotonSS = (temp =="photonfakes");
      bool isphoton3l = (temp2=="photonfakes");   
      bool isfakeSS = (temp =="fakes");
      bool isfake3l = (temp2=="fakes");
      if(sn.find("Other")!=string::npos&&splitVH(fname)){ sn = "WHtoWWW"; sn2 = sn; }
      else if(sn.find("Background")!=string::npos&&splitVH(fname)) continue;
      else if(sn.find("Background")!=string::npos&&!splitVH(fname)){
	sn  = temp;
	sn2 = temp2;
      }


      float MTmax = -1;
      if(iSS.size()==2) MTmax = calcMTmax(iSS,MET);
      else if(iSS.size()==1&&iaSS.size()>=1){
	vector<int> temp; temp.push_back(iSS[0]); temp.push_back(iaSS[0]);
	MTmax = calcMTmax(temp,MET);
      }
      float MTmax3l = calcMTmax(i3l,MET,true);

      int SRSS[4]; bool selects3l[4];
      int SR3l[4];
      for(int i = 0; i<4; ++i) { SRSS[i] = -1; SR3l[i] = -1; selects3l[i] = false; }
      //SS
      //0: SR
      SRSS[0] = isSRSS(iSS,      vSS,false,MTmax,  nj30,nb,Mjj,MjjL,Detajj, MET);
      //1: SR preselect
      SRSS[1] = isSRSS(iSS,      vSS,true ,MTmax,  nj30,nb,Mjj,MjjL,Detajj, MET);
      //2: AR
      SRSS[2] = isARSS(iSS,iaSS,vaSS,false,MTmax,  nj30,nb,Mjj,MjjL,Detajj, MET);
      //3: AR preselect
      SRSS[3] = isARSS(iSS,iaSS,vaSS,true ,MTmax,  nj30,nb,Mjj,MjjL,Detajj, MET);
      //3l
      //0: SR
      SR3l[0] = isSR3l(i3l,     false,nj,nb,MET);
      //1: SR preselect
      SR3l[1] = isSR3l(i3l,     true ,nj,nb,MET);
      //2: AR
      SR3l[2] = isAR3l(i3l,ia3l,false,nj,nb,MET);
      //3: AR preselect
      SR3l[3] = isAR3l(i3l,ia3l,true ,nj,nb,MET);
      
      for(int i = 0; i<4; ++i) {
        if(!selects3l[i]){
          if(vetophotonprocess(fname,isphotonSS))    { SRSS[i] = -1; }
        }
        else if(vetophotonprocess(fname,isphoton3l)){ SRSS[i] = -1; }
        if(vetophotonprocess(fname,isphoton3l))     { SR3l[i] = -1; }
      }

      float closureSSerr = 0.;
      float closure3lerr = 0.;
      if(iaSS.size()>0) closureSSerr = getlepFRClosureError(iaSS[0],!closuretest,true);
      if(ia3l.size()>0) closure3lerr = getlepFRClosureError(ia3l[0],!closuretest,true);
      
      float SFSS(0.), SFSSerr(0.), SF3l(0.), SF3lerr(0.);
      float noconeSFSS(0.), noconeSFSSerr(0.), noconeSF3l(0.), noconeSF3lerr(0.);
      if(SRSS[3]>=0){
	SFSS       = getlepFRWeightandError(SFSSerr,      iaSS[0],!closuretest);
	noconeSFSS = getlepFRWeightandError(noconeSFSSerr,iaSS[0],!closuretest,false);
      }
      if(SR3l[3]>=0){
	SF3l       = getlepFRWeightandError(SF3lerr,      ia3l[0],!closuretest);
	noconeSF3l = getlepFRWeightandError(noconeSF3lerr,ia3l[0],!closuretest,false);
      }

      if(iaSS.size()>=1&&abs(lep_pdgId()[iaSS[0] ])==11){
	if(SRSS[ 2]>=0) histos["FakeEstimationEvsMu_"        +sn]->Fill(0.,    weight*SFSS);
	if(SRSS[ 2]>=0) histos["ARyieldEvsMu_"               +sn]->Fill(0.,    weight);
	if(SRSS[ 2]>=0) histos["RawARyieldEvsMu_"            +sn]->Fill(0.,    1.);
	if(SRSS[ 3]>=0) histos["PreselFakeEstimationEvsMu_"  +sn]->Fill(0.,    weight*SFSS);
	if(SRSS[ 3]>=0) histos["PreselARyieldEvsMu_"         +sn]->Fill(0.,    weight);
	if(SRSS[ 3]>=0) histos["RawPreselARyieldEvsMu_"      +sn]->Fill(0.,    1.);
      }
      if(iaSS.size()>=1&&abs(lep_pdgId()[iaSS[0] ])==13){
	if(SRSS[ 2]>=0) histos["FakeEstimationEvsMu_"        +sn]->Fill(1.,    weight*SFSS);
	if(SRSS[ 2]>=0) histos["RawARyieldEvsMu_"            +sn]->Fill(1.,    1.);
	if(SRSS[ 2]>=0) histos["ARyieldEvsMu_"               +sn]->Fill(1.,    weight);
	if(SRSS[ 3]>=0) histos["PreselFakeEstimationEvsMu_"  +sn]->Fill(1.,    weight*SFSS);
	if(SRSS[ 3]>=0) histos["PreselARyieldEvsMu_"         +sn]->Fill(1.,    weight);
	if(SRSS[ 3]>=0) histos["RawPreselARyieldEvsMu_"      +sn]->Fill(1.,    1.);
      }
      if(iSS.size()==2&&isfakeSS){
	int id = -1;
	for (unsigned int lepindex = 0;lepindex<iSS.size();++lepindex){
	  if(lep_motherIdSS().at(iSS[lepindex]) > 0) continue;
	  else if(lep_motherIdSS().at(iSS[lepindex]) == -3) continue;
	  id = lep_pdgId()[iSS[lepindex] ];
	  break;
	}
	if(abs(id)==11){
	  if(SRSS[ 0]>=0) histos["SRyieldEvsMu_"         +sn]->Fill(0.,    weight);
	  if(SRSS[ 0]>=0) histos["RawSRyieldEvsMu_"      +sn]->Fill(0.,    1.);
	  if(SRSS[ 1]>=0) histos["PreselSRyieldEvsMu_"   +sn]->Fill(0.,    weight);
	  if(SRSS[ 1]>=0) histos["RawPreselSRyieldEvsMu_"+sn]->Fill(0.,    1.);
	}
	if(abs(id)==13){
	  if(SRSS[ 0]>=0) histos["SRyieldEvsMu_"         +sn]->Fill(1.,    weight);
	  if(SRSS[ 0]>=0) histos["RawSRyieldEvsMu_"      +sn]->Fill(1.,    1.);
	  if(SRSS[ 1]>=0) histos["PreselSRyieldEvsMu_"   +sn]->Fill(1.,    weight);
	  if(SRSS[ 1]>=0) histos["RawPreselSRyieldEvsMu_"+sn]->Fill(1.,    1.);
	}
      }
	 
      if(!(blindSR&&isData())){
	fillSRhisto(histos, "SRyield",           sn, sn2, SRSS[ 0], SR3l[ 0], weight, weight);
	fillSRhisto(histos, "PreselSRyield",     sn, sn2, SRSS[ 1], SR3l[ 1], weight, weight);
      }
      fillSRhisto(histos, "ARyield",                           sn, sn2, SRSS[ 2], SR3l[ 2], weight, weight);
      fillSRhisto(histos, "FakeEstimation",                    sn, sn2, SRSS[ 2], SR3l[ 2], weight*SFSS, weight*SF3l);
      fillSRhisto(histos, "FakeEstimationFRup",                sn, sn2, SRSS[ 2], SR3l[ 2], weight*(SFSS+SFSSerr), weight*(SF3l+SF3lerr));
      fillSRhisto(histos, "FakeEstimationFRdn",                sn, sn2, SRSS[ 2], SR3l[ 2], weight*(SFSS-SFSSerr), weight*(SF3l-SF3lerr));
      fillSRhisto(histos, "FakeEstimationClosureup",           sn, sn2, SRSS[ 2], SR3l[ 2], weight*(SFSS+closureSSerr), weight*(SF3l+closure3lerr));
      fillSRhisto(histos, "FakeEstimationClosuredn",           sn, sn2, SRSS[ 2], SR3l[ 2], weight*(SFSS-closureSSerr), weight*(SF3l-closure3lerr));
      fillSRhisto(histos, "NoConeCorrARyield",                 sn, sn2, SRSS[ 2], SR3l[ 2], weight, weight);
      fillSRhisto(histos, "NoConeCorrFakeEstimation",          sn, sn2, SRSS[ 2], SR3l[ 2], weight*noconeSFSS, weight*noconeSF3l);
      fillSRhisto(histos, "NoConeCorrFakeEstimationFRup",      sn, sn2, SRSS[ 2], SR3l[ 2], weight*(noconeSFSS+noconeSFSSerr), weight*(noconeSF3l+noconeSF3lerr));
      fillSRhisto(histos, "NoConeCorrFakeEstimationFRdn",      sn, sn2, SRSS[ 2], SR3l[ 2], weight*(noconeSFSS-noconeSFSSerr), weight*(noconeSF3l-noconeSF3lerr));
      fillSRhisto(histos, "NoConeCorrFakeEstimationClosureup", sn, sn2, SRSS[ 2], SR3l[ 2], weight*(noconeSFSS+closureSSerr), weight*(noconeSF3l+closure3lerr));
      fillSRhisto(histos, "NoConeCorrFakeEstimationClosuredn", sn, sn2, SRSS[ 2], SR3l[ 2], weight*(noconeSFSS-closureSSerr), weight*(noconeSF3l-closure3lerr));
      fillSRhisto(histos, "PreselARyield",                     sn, sn2, SRSS[ 3], SR3l[ 3], weight, weight);
      fillSRhisto(histos, "PreselFakeEstimation",              sn, sn2, SRSS[ 3], SR3l[ 3], weight*SFSS, weight*SF3l);
      fillSRhisto(histos, "PreselFakeEstimationFRup",          sn, sn2, SRSS[ 3], SR3l[ 3], weight*(SFSS+SFSSerr), weight*(SF3l+SF3lerr));
      fillSRhisto(histos, "PreselFakeEstimationFRdn",          sn, sn2, SRSS[ 3], SR3l[ 3], weight*(SFSS-SFSSerr), weight*(SF3l-SF3lerr));
      fillSRhisto(histos, "PreselFakeEstimationClosureup",     sn, sn2, SRSS[ 3], SR3l[ 3], weight*(SFSS+closureSSerr), weight*(SF3l+closure3lerr));
      fillSRhisto(histos, "PreselFakeEstimationClosuredn",     sn, sn2, SRSS[ 3], SR3l[ 3], weight*(SFSS-closureSSerr), weight*(SF3l-closure3lerr));
      if(SRSS[ 1]>=0){
	int t = SRSS[ 1];
	if(fabs(Mjj   -80.)<20.)  t = -1;
	fillSRhisto(histos, "PreselSRyield_Mjjsideband",   sn, sn2, t, -1, weight, weight);
	if(MjjL>400.||Detajj>1.5) t = -1;
	if(SRSS[ 1]==0&&(MET.Pt()<=40.||(lep_p4()[iSS[0] ]+lep_p4()[iSS[1] ]).M()<=40.)            ) t = -1;
	if(SRSS[ 1]==1&&(MET.Pt()<=40.||(lep_p4()[iSS[0] ]+lep_p4()[iSS[1] ]).M()<=30.||MTmax<=90.)) t = -1;
	if(SRSS[ 1]==2&&(               (lep_p4()[iSS[0] ]+lep_p4()[iSS[1] ]).M()<=40.)            ) t = -1;
	fillSRhisto(histos, "SRyield_Mjjsideband",   sn, sn2, t, -1, weight, weight);
	t = SRSS[ 1];
	if(MET.Pt()>40.) t = -1;
	if(fabs(Mjj   -80.)<20.)  t = -1;
	fillSRhisto(histos, "PreselSRyield_MjjsidebandlowMET",   sn, sn2, t, -1, weight, weight);
	if(MjjL>400.||Detajj>1.5) t = -1;
	if(SRSS[ 1]==0&&(MET.Pt()>40.||(lep_p4()[iSS[0] ]+lep_p4()[iSS[1] ]).M()<=40.)            ) t = -1;
	if(SRSS[ 1]==1&&(MET.Pt()>40.||(lep_p4()[iSS[0] ]+lep_p4()[iSS[1] ]).M()<=30.||MTmax<=90.)) t = -1;
	if(SRSS[ 1]==2&&(MET.Pt()>40.||(lep_p4()[iSS[0] ]+lep_p4()[iSS[1] ]).M()<=40.)            ) t = -1;
	fillSRhisto(histos, "SRyield_MjjsidebandlowMET",   sn, sn2, t, -1, weight, weight);
      }
      if(SRSS[ 3]>=0){
	int t = SRSS[ 3];
	if(fabs(Mjj   -80.)<20.)  t = -1;
	fillSRhisto(histos, "PreselARyield_Mjjsideband",              sn, sn2, t, -1, weight, weight);
	fillSRhisto(histos, "PreselFakeEstimation_Mjjsideband",       sn, sn2, t, -1, weight*SFSS, weight*SF3l);
	fillSRhisto(histos, "PreselFakeEstimationFRup_Mjjsideband",   sn, sn2, t, -1, weight*(SFSS+SFSSerr), weight*(SF3l+SF3lerr));
	fillSRhisto(histos, "PreselFakeEstimationFRdn_Mjjsideband",   sn, sn2, t, -1, weight*(SFSS-SFSSerr), weight*(SF3l-SF3lerr));
	if(MjjL>400.||Detajj>1.5) t = -1;
	if(SRSS[ 3]==0&&(MET.Pt()<=40.||(lep_p4()[iSS[0] ]+lep_p4()[iaSS[0] ]).M()<=40.)            ) t = -1;
	if(SRSS[ 3]==1&&(MET.Pt()<=40.||(lep_p4()[iSS[0] ]+lep_p4()[iaSS[0] ]).M()<=30.||MTmax<=90.)) t = -1;
	if(SRSS[ 3]==2&&(               (lep_p4()[iSS[0] ]+lep_p4()[iaSS[0] ]).M()<=40.)            ) t = -1;
	fillSRhisto(histos, "ARyield_Mjjsideband",              sn, sn2, t, -1, weight, weight);
	fillSRhisto(histos, "FakeEstimation_Mjjsideband",       sn, sn2, t, -1, weight*SFSS, weight*SF3l);
	fillSRhisto(histos, "FakeEstimationFRup_Mjjsideband",   sn, sn2, t, -1, weight*(SFSS+SFSSerr), weight*(SF3l+SF3lerr));
	fillSRhisto(histos, "FakeEstimationFRdn_Mjjsideband",   sn, sn2, t, -1, weight*(SFSS-SFSSerr), weight*(SF3l-SF3lerr));
	t = SRSS[ 3];
	if(MET.Pt()>40.) t = -1;
	if(fabs(Mjj   -80.)<20.)  t = -1;
	fillSRhisto(histos, "PreselARyield_MjjsidebandlowMET",              sn, sn2, t, -1, weight, weight);
	fillSRhisto(histos, "PreselFakeEstimation_MjjsidebandlowMET",       sn, sn2, t, -1, weight*SFSS, weight*SF3l);
	fillSRhisto(histos, "PreselFakeEstimationFRup_MjjsidebandlowMET",   sn, sn2, t, -1, weight*(SFSS+SFSSerr), weight*(SF3l+SF3lerr));
	fillSRhisto(histos, "PreselFakeEstimationFRdn_MjjsidebandlowMET",   sn, sn2, t, -1, weight*(SFSS-SFSSerr), weight*(SF3l-SF3lerr));
	if(MjjL>400.||Detajj>1.5) t = -1;
	if(SRSS[ 3]==0&&(MET.Pt()>40.||(lep_p4()[iSS[0] ]+lep_p4()[iaSS[0] ]).M()<=40.)            ) t = -1;
	if(SRSS[ 3]==1&&(MET.Pt()>40.||(lep_p4()[iSS[0] ]+lep_p4()[iaSS[0] ]).M()<=30.||MTmax<=90.)) t = -1;
	if(SRSS[ 3]==2&&(MET.Pt()>40.||(lep_p4()[iSS[0] ]+lep_p4()[iaSS[0] ]).M()<=40.)            ) t = -1;
	fillSRhisto(histos, "ARyield_MjjsidebandlowMET",              sn, sn2, t, -1, weight, weight);
	fillSRhisto(histos, "FakeEstimation_MjjsidebandlowMET",       sn, sn2, t, -1, weight*SFSS, weight*SF3l);
	fillSRhisto(histos, "FakeEstimationFRup_MjjsidebandlowMET",   sn, sn2, t, -1, weight*(SFSS+SFSSerr), weight*(SF3l+SF3lerr));
	fillSRhisto(histos, "FakeEstimationFRdn_MjjsidebandlowMET",   sn, sn2, t, -1, weight*(SFSS-SFSSerr), weight*(SF3l-SF3lerr));
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

  SaveHistosToFile("rootfiles/FakeRateHistograms.root",histos,true,true);

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
