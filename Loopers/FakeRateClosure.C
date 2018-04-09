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
#include "CMS3_WWW106.cc"
#include "../CORE/Tools/dorky/dorky.h"
#include "../CORE/Tools/dorky/dorky.cc"
#include "../CORE/Tools/goodrun.h"
#include "../CORE/Tools/goodrun.cc"

using namespace std;
using namespace tas;
//using namespace mt2_bisect;

int ScanChain( TChain* chain, bool fast = true, int nEvents = -1, string skimFilePrefix = "test", int chainnumber=1) {

  bool blindSR         = false;
  bool btagreweighting = true;
  bool applylepSF      = true;
  bool applytrigSF     = true;
  bool applyPUrewgt    = true;
  bool closuretest     = true;//if true use QCD fake rate

  bool isBtagSB        = false;

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

  histonames.push_back("njets");                              hbins.push_back( 6);  hlow.push_back( 0); hup.push_back(6);
  histonames.push_back("nbjets");                             hbins.push_back( 6);  hlow.push_back( 0); hup.push_back(6);
  histonames.push_back("pTl1");                               hbins.push_back(15);  hlow.push_back( 0); hup.push_back(225);
  histonames.push_back("pTl2");                               hbins.push_back(15);  hlow.push_back( 0); hup.push_back(225);
  histonames.push_back("Mjj");                                hbins.push_back(15);  hlow.push_back( 0); hup.push_back(300);
  histonames.push_back("Mll");                                hbins.push_back(15);  hlow.push_back( 0); hup.push_back(225);
  histonames.push_back("MET");                                hbins.push_back(15);  hlow.push_back( 0); hup.push_back(150);
  histonames.push_back("MTmax");                              hbins.push_back(15);  hlow.push_back( 0); hup.push_back(225);
  int nhistoc = histonames.size();
  for(int i = 0; i<nhistoc; ++i){
    histonames.push_back(      histonames[i]+"_fakesPred");   hbins.push_back(hbins[i]);  hlow.push_back(hlow[i]); hup.push_back(hup[i]);
    histonames.push_back("el_"+histonames[i]);                hbins.push_back(hbins[i]);  hlow.push_back(hlow[i]); hup.push_back(hup[i]);
    histonames.push_back("el_"+histonames[i]+"_fakesPred");   hbins.push_back(hbins[i]);  hlow.push_back(hlow[i]); hup.push_back(hup[i]);
    histonames.push_back("mu_"+histonames[i]);                hbins.push_back(hbins[i]);  hlow.push_back(hlow[i]); hup.push_back(hup[i]);
    histonames.push_back("mu_"+histonames[i]+"_fakesPred");   hbins.push_back(hbins[i]);  hlow.push_back(hlow[i]); hup.push_back(hup[i]);
  }

  histonames.push_back("SRyield");                            hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("ARyield");                            hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("FakeEstimation");                     hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("FakeEstimationFRup");                 hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("FakeEstimationFRdn");                 hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("PreselSRyield");                      hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("PreselARyield");                      hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("PreselFakeEstimation");               hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("PreselFakeEstimationFRup");           hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("PreselFakeEstimationFRdn");           hbins.push_back( 6); hlow.push_back(    0); hup.push_back(6);
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

      if(isData())               continue;//closure not done on data
      if(firstgoodvertex()!=0)   continue;
      if(nVert()<0)              continue;
      if(nLlep()<2)              continue;
      if(nTlepSS()<1)            continue;//check only SS
      if(nj30()<2)               continue;//check only SS
      if(!isBtagSB&&nb() >0)     continue;
      if( isBtagSB&&nb()==0)     continue;
      
      //weight = 1;
      if(string(currentFile->GetTitle()).find("wjets_incl_mgmlm_")!=string::npos){
	if(gen_ht()>100) continue;
      }
      if(string(currentFile->GetTitle()).find("dy_m50_mgmlm_ext1_")!=string::npos){
	if(gen_ht()>100) continue;
      }
      //if(string(currentFile->GetTitle()).find("www_2l_mia")!=string::npos) weight *= 0.066805*91900./(91900.+164800.);//(208fb/1pb)*BR(WWW—> >=2l)*combineweight
      //if(string(currentFile->GetTitle()).find("www_2l_ext1_mia")!=string::npos) weight *= 0.066805*164800./(91900.+164800.);//(208fb/1pb)*BR(WWW—> >=2l)*combineweight
      if(weight>100) cout << weight << " " << currentFile->GetTitle() << endl;
      if(isData()) weight = 1.;
      //double rawweight = weight;
      if(!isData()&&btagreweighting) weight *= weight_btagsf();
      if(!isData()&&applyPUrewgt)    weight *= purewgt();
      if(!isData()&&applylepSF)      weight *= lepsf();
      if(!isData()&&applytrigSF)     weight *= trigeff();
      

      if(isData()){
	if(!passFilters())                      continue;
	duplicate_removal::DorkyEventIdentifier id(tas::run(), tas::evt(), tas::lumi());
	if( is_duplicate(id) )                  continue; 
	if( !goodrun(tas::run(), tas::lumi()) ) continue;
      } 
      if(!passTriggers()) continue;//pass trigger for data, and offline lepton kinematic cuts for data/simulation

      //continue here;
      string sample   = skimFilePrefix;
      if(splitVH(fname)){ sample = "WHtoWWW"; }
      if(vetophoton()) continue;

      string sn1("unknown"),sn2("unknown"),sn_fo("unknown");
      int ridx1(-1), ridx2(-1), foidx(-1);
      for(int i = 0; i< nLlep(); ++i){
	if(lep_pass_VVV_cutbased_tight()[i]&&lep_p4()[i].Pt()>25.){
	  if(     ridx1<0) { sn1   = leptype(i); ridx1 = i; }
	  else if(ridx2<0) { sn2   = leptype(i); ridx2 = i; }
	}
	if(lep_pass_VVV_cutbased_fo()[i]&&!lep_pass_VVV_cutbased_tight()[i]&&lep_p4()[i].Pt()>25.){
	  if(     foidx<0) { sn_fo = leptype(i); foidx = i; }
	}
      }
      bool   fake1  = (sn1.find("fake")!=string::npos);
      bool   fake2  = (sn2.find("fake")!=string::npos);
      string sn_evt = fake1 ? sn1 : sn2;
      //int    tfidx  = fake1 ? ridx1 : (fake2 ? ridx2 : -1);
      int    tfidx  = fake1 ? ridx1 : ridx2;
      if(sn_evt.find("fake")==string::npos && sn_fo.find("fake")==string::npos) continue; //none of selected leptons are fake
 
      int SRSS[4];
      int SR3l[4];
      int dummy = -1;
      for(int i = 0; i<4; ++i) { SRSS[i] = -1; SR3l[i] = -1; }
      //SS
      passAnySS(SRSS[ 0],SRSS[ 2],dummy,false,0,false,isBtagSB,false,1); //full:         0: SR,  2: AR
      passAnySS(SRSS[ 1],SRSS[ 3],dummy,true, 0,false,isBtagSB,false,1); //preselection: 1: SR,  3: AR
      //3l
      passAny3l(SR3l[ 0],SR3l[ 2],dummy,false,0,isBtagSB,1);             //full:         0: SR,  2: AR
      passAny3l(SR3l[ 1],SR3l[ 3],dummy,true, 0,isBtagSB,1);             //preselection: 1: SR,  3: AR

      // skip event if it's not preselection SS SR or AR
      if(SRSS[1]<0 && SRSS[3]<0) continue;      

      float SF(0.), SFerr(0.), closureerr(0.);
      float subtract = 1.;//dummy
      if(!closuretest){
	float FR = ffwgt();
	float FRerr = fabs(ffwgt_up()-ffwgt());
	SF = FR/(1.-FR) * subtract;
	SFerr = FRerr/pow(1-FR,2) * subtract;
      } else {
	float FR = ffwgtqcd();
	float FRerr = fabs(ffwgtqcd_up()-ffwgtqcd());
	SF = FR/(1.-FR) * subtract;
	SFerr = FRerr/pow(1-FR,2) * subtract;
      }
      
      // fill in fake leptons in the SR
      string fakelep = "";
      if(SRSS[ 1]>=0&&(fake1||fake2)){
	if(     abs(lep_pdgId()[tfidx])==11) fakelep = "el_";
	else if(abs(lep_pdgId()[tfidx])==13) fakelep = "mu_";
        // it always fill the histogram with _sample. this is ok?
	if(fake1) fillhisto(histos,         "pTl1",   sample, sn1, lep_p4()[ridx1].pt(), weight);
        if(fake2) fillhisto(histos,         "pTl2",   sample, sn2, lep_p4()[ridx2].pt(), weight);
	fillhisto(          histos,         "Mjj",    sample, sn_evt, Mjj(),             weight);
	fillhisto(          histos,         "njets",  sample, sn_evt, nj30(),            weight);
	fillhisto(          histos,         "nbjets", sample, sn_evt, nb(),              weight);
	fillhisto(          histos,         "Mll",    sample, sn_evt, MllSS(),           weight);
	fillhisto(          histos,         "MTmax",  sample, sn_evt, MTmax(),           weight);
	fillhisto(          histos,         "MET",    sample, sn_evt, met_pt(),          weight);
	if(fake1) fillhisto(histos, fakelep+"pTl1",   sample, sn1, lep_p4()[ridx1].pt(), weight);
	if(fake2) fillhisto(histos, fakelep+"pTl2",   sample, sn2, lep_p4()[ridx2].pt(), weight);
	fillhisto(          histos, fakelep+"Mjj",    sample, sn_evt, Mjj(),             weight);
	fillhisto(          histos, fakelep+"njets",  sample, sn_evt, nj30(),            weight);
	fillhisto(          histos, fakelep+"nbjets", sample, sn_evt, nb(),              weight);
	fillhisto(          histos, fakelep+"Mll",    sample, sn_evt, MllSS(),           weight);
	fillhisto(          histos, fakelep+"MTmax",  sample, sn_evt, MTmax(),           weight);
	fillhisto(          histos, fakelep+"MET",    sample, sn_evt, met_pt(),          weight);
      }
      if(SRSS[3]>=0) {
	if(     abs(lep_pdgId()[foidx])==11) fakelep = "el_";
	else if(abs(lep_pdgId()[foidx])==13) fakelep = "mu_";
	if(lep_p4()[ridx1].pt()>lep_p4()[foidx].pt() ) fillhisto(histos, "pTl2_fakesPred",         sample, sn_fo, lep_p4()[foidx].pt(), weight*SF);
	if(lep_p4()[ridx1].pt()<lep_p4()[foidx].pt() ) fillhisto(histos, "pTl1_fakesPred",         sample, sn_fo, lep_p4()[foidx].pt(), weight*SF);
	fillhisto(histos,         "Mjj_fakesPred",    sample, sn_fo, Mjj(),    weight*SF);
	fillhisto(histos,         "njets_fakesPred",  sample, sn_fo, nj30(),   weight*SF);
	fillhisto(histos,         "nbjets_fakesPred", sample, sn_fo, nb(),     weight*SF);
	fillhisto(histos,         "Mll_fakesPred",    sample, sn_fo, MllSS(),  weight*SF);
	fillhisto(histos,         "MTmax_fakesPred",  sample, sn_fo, MTmax(),  weight*SF);
	fillhisto(histos,         "MET_fakesPred",    sample, sn_fo, met_pt(), weight*SF);
	if(lep_p4()[ridx1].pt()>lep_p4()[foidx].pt() ) fillhisto(histos, fakelep+"pTl2_fakesPred", sample, sn_fo, lep_p4()[foidx].pt(), weight*SF);
	if(lep_p4()[ridx1].pt()<lep_p4()[foidx].pt() ) fillhisto(histos, fakelep+"pTl1_fakesPred", sample, sn_fo, lep_p4()[foidx].pt(), weight*SF);
	fillhisto(histos, fakelep+"Mjj_fakesPred",    sample, sn_fo, Mjj(),    weight*SF);
	fillhisto(histos, fakelep+"njets_fakesPred",  sample, sn_fo, nj30(),   weight*SF);
	fillhisto(histos, fakelep+"nbjets_fakesPred", sample, sn_fo, nb(),     weight*SF);
	fillhisto(histos, fakelep+"Mll_fakesPred",    sample, sn_fo, MllSS(),  weight*SF);
	fillhisto(histos, fakelep+"MTmax_fakesPred",  sample, sn_fo, MTmax(),  weight*SF);
	fillhisto(histos, fakelep+"MET_fakesPred",    sample, sn_fo, met_pt(), weight*SF);
     }

      if(!(blindSR&&isData())){
	fillSRhisto(histos, "SRyield",                         sample, sn_evt, SRSS[ 0], -1, weight);
	fillSRhisto(histos, "PreselSRyield",                   sample, sn_evt, SRSS[ 1], -1, weight);
      }
      fillSRhisto(histos, "ARyield",                           sample, sn_fo,  SRSS[ 2], -1, weight);
      fillSRhisto(histos, "FakeEstimation",                    sample, sn_fo,  SRSS[ 2], -1, weight* SF);
      fillSRhisto(histos, "FakeEstimationFRup",                sample, sn_fo,  SRSS[ 2], -1, weight*(SF+SFerr));
      fillSRhisto(histos, "FakeEstimationFRdn",                sample, sn_fo,  SRSS[ 2], -1, weight*(SF-SFerr));
      fillSRhisto(histos, "PreselARyield",                     sample, sn_fo,  SRSS[ 3], -1, weight);
      fillSRhisto(histos, "PreselFakeEstimation",              sample, sn_fo,  SRSS[ 3], -1, weight* SF);
      fillSRhisto(histos, "PreselFakeEstimationFRup",          sample, sn_fo,  SRSS[ 3], -1, weight*(SF+SFerr));
      fillSRhisto(histos, "PreselFakeEstimationFRdn",          sample, sn_fo,  SRSS[ 3], -1, weight*(SF-SFerr));

      
    }//event loop
    // Clean Up
    delete tree;
    file->Close();
    delete file;
  }//file loop
  if ( nEventsChain != nEventsTotal ) {
    cout << Form( "ERROR: number of events from files (%d) is not equal to total number of events (%d)", nEventsChain, nEventsTotal ) << endl;
  }

  string savename = "rootfiles/FakeRateClosureHistograms";
  if(!closuretest) savename = savename + "_dataFR.root";
  else             savename = savename + ".root";
  SaveHistosToFile(savename,histos,true,true,(chainnumber==0));
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
