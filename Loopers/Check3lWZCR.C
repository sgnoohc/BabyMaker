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
//#include "Functions112.h"
//#include "CMS3_WWW112.cc"
#include "Functions.h"
#include "CMS3_WWW121.cc"
#include "../CORE/Tools/dorky/dorky.h"
#include "../CORE/Tools/dorky/dorky.cc"
#include "../CORE/Tools/goodrun.h"
#include "../CORE/Tools/goodrun.cc"

using namespace std;
using namespace tas;

int ScanChain( TChain* chain, bool fast = true, int nEvents = -1, string skimFilePrefix = "test", int chainnumber=1) {

  bool blindSR         = true;
  bool btagreweighting = true;
  bool applylepSF      = true;
  bool applytrigSF     = true;
  bool applyPUrewgt    = true;
  
  const char* json_file = "data/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt";
  set_goodrun_file_json(json_file);

  // Benchmark
  TBenchmark *bmark = new TBenchmark();
  bmark->Start("benchmark");

  // Example Histograms
  TDirectory *rootdir = gDirectory->GetDirectory("Rint:");

  vector<string> histonames; histonames.clear();
  vector<int>   hbins;       hbins.clear();
  vector<float> hlow;        hlow.clear();
  vector<float> hup;         hup.clear();

  //SR
  histonames.push_back("YieldsSR");                                   hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsSR_raw");                               hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsSR_rawweight");                         hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsSR_Mjjside");                           hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsSR_Mjjside_raw");                       hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsSR_Mjjside_rawweight");                 hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsCR");                                   hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsCR_noMSFOSsel_SS");                     hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  //SS JEC uncertainty
  histonames.push_back("YieldsSR_jesup");                             hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsSR_jesdn");                             hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsSR_Mjjside_jesup");                     hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsSR_Mjjside_jesdn");                     hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsSR_dropMjj");                           hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsSR_dropMjj_jesup");                     hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsSR_dropMjj_jesdn");                     hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsCR_jesup");                             hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsCR_jesdn");                             hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsCR_cutonMjj");                          hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsCR_cutonMjj_jesup");                    hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsCR_cutonMjj_jesdn");                    hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsCR_anticutonMjj");                      hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsCR_anticutonMjj_jesup");                hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsCR_anticutonMjj_jesdn");                hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("Mjj_CRlike_allSS_jesup");                     hbins.push_back(10);hlow.push_back( 5);hup.push_back(155);
  histonames.push_back("Mjj_CRlike_allSS_jesdn");                     hbins.push_back(10);hlow.push_back( 5);hup.push_back(155);
  histonames.push_back("Mjj_CRlike_allSS");                           hbins.push_back(10);hlow.push_back( 5);hup.push_back(155);
  //PU unc
  histonames.push_back("YieldsSR_PUup");                              hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsSR_PUdn");                              hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsSR_dropMjj_PUup");                      hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsSR_dropMjj_PUdn");                      hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsCR_PUup");                              hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsCR_PUdn");                              hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsSR_Mjjside_PUup");                      hbins.push_back(6); hlow.push_back(0); hup.push_back(6);//xx
  histonames.push_back("YieldsSR_Mjjside_PUdn");                      hbins.push_back(6); hlow.push_back(0); hup.push_back(6);//xx
  //MSFOS/lep SF uncertainty
  histonames.push_back("YieldsCR_lepSFup");                           hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsCR_lepSFdn");                           hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsSR_lepSFup");                           hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsSR_lepSFdn");                           hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsSR_Mjjside_lepSFup");                   hbins.push_back(6); hlow.push_back(0); hup.push_back(6);//xx
  histonames.push_back("YieldsSR_Mjjside_lepSFdn");                   hbins.push_back(6); hlow.push_back(0); hup.push_back(6);//xx
  histonames.push_back("MSFOS_CRlike_allSS");                         hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOS_CRlike_allSS_lepSFup");                 hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOS_CRlike_allSS_lepSFdn");                 hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOSall_CRlike_allSS");                      hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOSall_CRlike_allSS_lepSFup");              hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOSall_CRlike_allSS_lepSFdn");              hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOS_CRlike_allSS_lowMET");                  hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOSall_CRlike_allSS_lowMET");               hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOS_CRlike_allSS_lowMllSS");                hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOSall_CRlike_allSS_lowMllSS");             hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOS_CRlike_allSS_lowMETMllSS");             hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOSall_CRlike_allSS_lowMETMllSS");          hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOS_CRlike_allSS_lowMETorMllSS");           hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOSall_CRlike_allSS_lowMETorMllSS");        hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  //ttZ/WZ uncertainty
  histonames.push_back("YieldsSR_ttZup");                             hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsSR_ttZdn");                             hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsSR_WZup");                              hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsSR_WZdn");                              hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsCR_ttZup");                             hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsCR_ttZdn");                             hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsCR_WZup");                              hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsCR_WZdn");                              hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsSR_Mjjside_ttZup");                     hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsSR_Mjjside_ttZdn");                     hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsSR_Mjjside_WZup");                      hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsSR_Mjjside_WZdn");                      hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  //validation SS
  histonames.push_back("YieldsSR_Mjjside_lowMET");                    hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsSR_Mjjside_lowMTmax");                  hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsSR_lowMET");                            hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsSR_lowMTmax");                          hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  
  //validation 3l
  histonames.push_back("YieldsSR_inverteitherMETdPhiPt");             hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsSR_invertMETdPhiPt");                   hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsCR_inverteitherMETdPhiPt");             hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsCR_invertMETdPhiPt");                   hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsSR_invertMT3rd");                       hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsSR_inverteitherMT3rdMETdPhiPt");        hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsSR_invertMT3rdMETdPhiPt");              hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsCR_invertMT3rd");                       hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsCR_inverteitherMT3rdMETdPhiPt");        hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsCR_invertMT3rdMETdPhiPt");              hbins.push_back(6); hlow.push_back(0); hup.push_back(6);
  histonames.push_back("YieldsSR_inverteitherMT3rdMETPt");            hbins.push_back(6); hlow.push_back(0); hup.push_back(6);//new
  histonames.push_back("YieldsSR_inverteitherMT3rdMETdPhi");          hbins.push_back(6); hlow.push_back(0); hup.push_back(6);//new
  histonames.push_back("YieldsSR_inverteitherMT3rddPhiPt");           hbins.push_back(6); hlow.push_back(0); hup.push_back(6);//new
  histonames.push_back("YieldsCR_inverteitherMT3rdMETPt");            hbins.push_back(6); hlow.push_back(0); hup.push_back(6);//new
  histonames.push_back("YieldsCR_inverteitherMT3rdMETdPhi");          hbins.push_back(6); hlow.push_back(0); hup.push_back(6);//new
  histonames.push_back("YieldsCR_inverteitherMT3rddPhiPt");           hbins.push_back(6); hlow.push_back(0); hup.push_back(6);//new
  histonames.push_back("MSFOS_all3l");                                hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOS_all3l_lepSFup");                        hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOS_all3l_lepSFdn");                        hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOS_all3l_inverteitherMETdPhiPt");          hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOS_all3l_invertMETdPhiPt");                hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOSall_all3l");                             hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOSall_all3l_lepSFup");                     hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOSall_all3l_lepSFdn");                     hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOSall_all3l_inverteitherMETdPhiPt");       hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOSall_all3l_invertMETdPhiPt");             hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOS_1SFOS");                                hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOS_1SFOS_lepSFup");                        hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOS_1SFOS_lepSFdn");                        hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOS_1SFOS_inverteitherMETdPhiPt");          hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOS_1SFOS_invertMETdPhiPt");                hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOS_1SFOS_invertMT3rd");                    hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOS_1SFOS_inverteitherMT3rdMETdPhiPt");     hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOS_1SFOS_invertMT3rdMETdPhiPt");           hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOS_2SFOS");                                hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOS_2SFOS_lepSFup");                        hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOS_2SFOS_lepSFdn");                        hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOS_2SFOS_inverteitherMETdPhiPt");          hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOS_2SFOS_invertMETdPhiPt");                hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOSall_2SFOS");                             hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOSall_2SFOS_lepSFup");                     hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOSall_2SFOS_lepSFdn");                     hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOSall_2SFOS_inverteitherMETdPhiPt");       hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOSall_2SFOS_invertMETdPhiPt");             hbins.push_back(12);hlow.push_back(30);hup.push_back(150);

  histonames.push_back("MSFOS_2SFOS_inverteitherMT3rdMETdPhiPt");     hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOSall_2SFOS_inverteitherMT3rdMETdPhiPt");  hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOS_all3l_inverteitherMT3rdMETdPhiPt");     hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOSall_all3l_inverteitherMT3rdMETdPhiPt");  hbins.push_back(12);hlow.push_back(30);hup.push_back(150);

  histonames.push_back("MSFOS_1SFOS_inverteitherMT3rdMETPt");         hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOS_1SFOS_inverteitherMT3rdMETdPhi");       hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOS_1SFOS_inverteitherMT3rddPhiPt");        hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOS_2SFOS_inverteitherMT3rdMETPt");         hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOS_2SFOS_inverteitherMT3rdMETdPhi");       hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOS_2SFOS_inverteitherMT3rddPhiPt");        hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOSall_2SFOS_inverteitherMT3rdMETPt");      hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOSall_2SFOS_inverteitherMT3rdMETdPhi");    hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOSall_2SFOS_inverteitherMT3rddPhiPt");     hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOS_all3l_inverteitherMT3rdMETPt");         hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOS_all3l_inverteitherMT3rdMETdPhi");       hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOS_all3l_inverteitherMT3rddPhiPt");        hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOSall_all3l_inverteitherMT3rdMETPt");      hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOSall_all3l_inverteitherMT3rdMETdPhi");    hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  histonames.push_back("MSFOSall_all3l_inverteitherMT3rddPhiPt");     hbins.push_back(12);hlow.push_back(30);hup.push_back(150);
  
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
      if(firstgoodvertex()!=0)   continue;
      if(nLlep()<2)              continue;
      if(nTlepSS()<2&&nTlep()<3) continue;//preselection can be done already here
      if(nb()!=0)                continue;//preselection can be done already here

      if(string(currentFile->GetTitle()).find("wjets_incl_mgmlm_") !=string::npos && gen_ht()>100.) continue;
      if(string(currentFile->GetTitle()).find("dy_m50_mgmlm_ext1_")!=string::npos && gen_ht()>100.) continue;
      //if(string(currentFile->GetTitle()).find("www_2l_mia")        !=string::npos) weight *= 0.066805* 91900./(91900.+164800.);//(208fb/1pb)*BR(WWW—> >=2l)*combineweight
      //if(string(currentFile->GetTitle()).find("www_2l_ext1_mia")   !=string::npos) weight *= 0.066805*164800./(91900.+164800.);//(208fb/1pb)*BR(WWW—> >=2l)*combineweight
      if(isData()) weight = 1.;
      double rawweight = weight;
      if(!isData()&&btagreweighting) weight *= weight_btagsf();
      if(!isData()&&applyPUrewgt)    weight *= purewgt();
      if(!isData()&&applylepSF)      weight *= lepsf();
      if(!isData()&&applytrigSF)     weight *= trigsf();

      if(isData()){
        if(!passFilters())                      continue;
        duplicate_removal::DorkyEventIdentifier id(tas::run(), tas::evt(), tas::lumi());
        if( is_duplicate(id) )                  continue; 
        if( !goodrun(tas::run(), tas::lumi()) ) continue;
      } 
      if(!passTriggers()) continue;//pass trigger for data, and offline lepton kinematic cuts for data/simulation

      string sample   = skimFilePrefix;
      if(splitVH(fname)) sample = "WHtoWWW"; 
      string sn = string(bkgtype().Data());
      if(vetophoton()) continue;
      bool ttZ(false), WZ(false);
      if(fname.find("ttz_"     )!=string::npos) { ttZ = true; }
      if(fname.find("wz_"      )!=string::npos) { WZ  = true; }
      if(fname.find("zz_"      )!=string::npos) { WZ  = true; }
      double xsecweightttZ(0.), xsecweightWZ(0.);
      //if(ttZ) xsecweightttZ = 0.197896;
      //if(WZ)  xsecweightWZ  = 0.0579957;
      if(ttZ) xsecweightttZ = 0.04;
      if(WZ)  xsecweightWZ  = 0.04;
      
      int SRSS[40], SR3l[40];
      int dummy = -1;
      for(int i = 0; i<40; ++i) { SRSS[i] = -1; SR3l[i] = -1; }
      //SS
      passAnySS(SRSS[ 0],dummy,SRSS[ 2]);      //full:         0: SR, 2: CR
      passAnySS(SRSS[ 1],dummy,SRSS[ 3],true); //preselection: 1: SR, 3: CR
      SRSS[4] = isCRSS(false,0, true);//full CR - noZ
      SRSS[5] = isCRSS(true ,0, true);//preselection CR - noZ
      passAnySS(SRSS[ 6],dummy,SRSS[ 8],false, 1);//JEC UP
      passAnySS(SRSS[ 7],dummy,SRSS[ 9],true,  1);
      passAnySS(SRSS[10],dummy,SRSS[12],false,-1);//JEC DOWN
      passAnySS(SRSS[11],dummy,SRSS[13],true, -1);
      //Mjj sideband - like SR id + 20. - only useful for full selection
      passAnySS(SRSS[20],dummy,SRSS[22],false, 0,false,false,true,1);
      passAnySS(SRSS[26],dummy,SRSS[28],false, 1,false,false,true,1);
      passAnySS(SRSS[30],dummy,SRSS[32],false,-1,false,false,true,1);
 
      //3l
      passAny3l(SR3l[ 0],dummy,SR3l[ 2]);      //full:         0: SR, 2 CR
      passAny3l(SR3l[ 1],dummy,SR3l[ 3],true); //preselection: 1: SR, 3 CR
      passAny3l(SR3l[ 6],dummy,SR3l[ 8],false, 1);//JEC UP
      passAny3l(SR3l[ 7],dummy,SR3l[ 9],true,  1);
      passAny3l(SR3l[10],dummy,SR3l[12],false,-1);//JEC DOWN
      passAny3l(SR3l[11],dummy,SR3l[13],true, -1);
      float maxMT = -1;
      LorentzVector METlv; METlv.SetPxPyPzE(met_pt()*TMath::Cos(met_phi()),met_pt()*TMath::Sin(met_phi()),0,met_pt());
      if(nVlep()==3){
        for(int i = 0; i<nVlep();++i){
          if((lep_pass_VVV_cutbased_3l_fo()[i] || lep_pass_VVV_cutbased_3l_tight()[i]) && lep_p4()[i].Pt()>20.) {
            if(mT(lep_p4()[i],METlv)>maxMT) maxMT = mT(lep_p4()[i],METlv);
          }
        }
      }
      if(maxMT<=90.){
        if(SR3l[ 0]==0) SR3l[ 0] = -1;
        if(SR3l[ 1]==0) SR3l[ 1] = -1;
        if(SR3l[ 2]==0) SR3l[ 2] = -1;
        if(SR3l[ 3]==0) SR3l[ 3] = -1;
        if(SR3l[ 4]==0) SR3l[ 4] = -1;
        if(SR3l[ 5]==0) SR3l[ 5] = -1;
        if(SR3l[ 6]==0) SR3l[ 6] = -1;
        if(SR3l[ 7]==0) SR3l[ 7] = -1;
        if(SR3l[ 8]==0) SR3l[ 8] = -1;
        if(SR3l[ 9]==0) SR3l[ 9] = -1;
        if(SR3l[10]==0) SR3l[10] = -1;
        if(SR3l[11]==0) SR3l[11] = -1;
        if(SR3l[12]==0) SR3l[12] = -1;
        if(SR3l[13]==0) SR3l[13] = -1;
      }
      if(met_pt()<=60.){
        if(SRSS[20]==2) SRSS[20] = -1;
        //if(SRSS[22]==2) SRSS[22] = -1;
        if(SRSS[26]==2) SRSS[26] = -1;
        //if(SRSS[28]==2) SRSS[28] = -1;
        if(SRSS[30]==2) SRSS[30] = -1;
        //if(SRSS[32]==2) SRSS[32] = -1;
      }
      vector <float> MSFOSvec = allMSFOS();
      //cout << sn << endl;
      if(!(blindSR&&isData())){
        fillSRhisto(histos, "YieldsSR",           sample, sn, SRSS[ 0], SR3l[ 0], weight);
        fillSRhisto(histos, "YieldsSR_raw",       sample, sn, SRSS[ 0], SR3l[ 0], 1.);
        fillSRhisto(histos, "YieldsSR_rawweight", sample, sn, SRSS[ 0], SR3l[ 0], rawweight);
        fillSRhisto(histos, "YieldsSR_jesup",     sample, sn, SRSS[ 6], SR3l[ 6], weight);
        fillSRhisto(histos, "YieldsSR_jesdn",     sample, sn, SRSS[10], SR3l[10], weight);
        if(purewgt()>0) fillSRhisto(histos, "YieldsSR_PUup",      sample, sn, SRSS[ 0], SR3l[ 0], weight*purewgt_up()/purewgt());
        if(purewgt()>0) fillSRhisto(histos, "YieldsSR_PUdn",      sample, sn, SRSS[ 0], SR3l[ 0], weight*purewgt_dn()/purewgt());
        if(lepsf()>0) fillSRhisto(histos, "YieldsSR_lepSFup",   sample, sn, SRSS[ 0], SR3l[ 0], weight*lepsf_up()/lepsf());
        if(lepsf()>0) fillSRhisto(histos, "YieldsSR_lepSFdn",   sample, sn, SRSS[ 0], SR3l[ 0], weight*lepsf_dn()/lepsf());
        fillSRhisto(histos, "YieldsSR_dropMjj",        sample, sn, (SRSS[0]>=0 ? SRSS[0] : SRSS[20]), SR3l[ 0], weight);
        if(purewgt()>0) fillSRhisto(histos, "YieldsSR_dropMjj_PUup",   sample, sn, (SRSS[0]>=0 ? SRSS[0] : SRSS[20]), SR3l[ 0], weight*purewgt_up()/purewgt());
        if(purewgt()>0) fillSRhisto(histos, "YieldsSR_dropMjj_PUdn",   sample, sn, (SRSS[0]>=0 ? SRSS[0] : SRSS[20]), SR3l[ 0], weight*purewgt_dn()/purewgt());
        fillSRhisto(histos, "YieldsSR_dropMjj_jesup",  sample, sn, (SRSS[6]>=0 ? SRSS[6] : SRSS[26]), SR3l[ 6], weight);
        fillSRhisto(histos, "YieldsSR_dropMjj_jesdn",  sample, sn, (SRSS[10]>=0 ? SRSS[10] : SRSS[30]), SR3l[10], weight);
        fillSRhisto(histos, "YieldsSR_WZup",      sample, sn, SRSS[ 0], SR3l[ 0], weight*(1.+xsecweightWZ));
        fillSRhisto(histos, "YieldsSR_WZdn",      sample, sn, SRSS[ 0], SR3l[ 0], weight*(1.-xsecweightWZ));
        fillSRhisto(histos, "YieldsSR_ttZup",     sample, sn, SRSS[ 0], SR3l[ 0], weight*(1.+xsecweightttZ));
        fillSRhisto(histos, "YieldsSR_ttZdn",     sample, sn, SRSS[ 0], SR3l[ 0], weight*(1.-xsecweightttZ));

        //MSFOS - SR blinded
        if(SR3l[ 0]>=0&&MSFOSvec.size()>0){
          fillhisto(    histos, "MSFOS_all3l",            sample, sn, MSFOSvec[0], weight);
          if(lepsf()>0) fillhisto(    histos, "MSFOS_all3l_lepSFup",    sample, sn, MSFOSvec[0], weight*lepsf_up()/lepsf());
          if(lepsf()>0) fillhisto(    histos, "MSFOS_all3l_lepSFdn",    sample, sn, MSFOSvec[0], weight*lepsf_dn()/lepsf());
          if(SR3l[ 0]==1){
            fillhisto(  histos, "MSFOS_1SFOS",            sample, sn, MSFOSvec[0], weight);
            if(lepsf()>0) fillhisto(  histos, "MSFOS_1SFOS_lepSFup",    sample, sn, MSFOSvec[0], weight*lepsf_up()/lepsf());
            if(lepsf()>0) fillhisto(  histos, "MSFOS_1SFOS_lepSFdn",    sample, sn, MSFOSvec[0], weight*lepsf_dn()/lepsf());
          }
          if(SR3l[ 0]==2){
            fillhisto(  histos, "MSFOS_2SFOS",            sample, sn, MSFOSvec[0], weight);
            if(lepsf()>0) fillhisto(  histos, "MSFOS_2SFOS_lepSFup",    sample, sn, MSFOSvec[0], weight*lepsf_up()/lepsf());
            if(lepsf()>0) fillhisto(  histos, "MSFOS_2SFOS_lepSFdn",    sample, sn, MSFOSvec[0], weight*lepsf_dn()/lepsf());
          }
          for(unsigned int i = 0; i<MSFOSvec.size();++i){
            fillhisto(  histos, "MSFOSall_all3l",         sample, sn, MSFOSvec[i], weight);
            if(lepsf()>0) fillhisto(  histos, "MSFOSall_all3l_lepSFup", sample, sn, MSFOSvec[i], weight*lepsf_up()/lepsf());
            if(lepsf()>0) fillhisto(  histos, "MSFOSall_all3l_lepSFdn", sample, sn, MSFOSvec[i], weight*lepsf_dn()/lepsf());
            if(SR3l[ 0]==2){
              fillhisto(histos, "MSFOSall_2SFOS",         sample, sn, MSFOSvec[i], weight);
              if(lepsf()>0) fillhisto(histos, "MSFOSall_2SFOS_lepSFup", sample, sn, MSFOSvec[i], weight*lepsf_up()/lepsf());
              if(lepsf()>0) fillhisto(histos, "MSFOSall_2SFOS_lepSFdn", sample, sn, MSFOSvec[i], weight*lepsf_dn()/lepsf());
            }
          }//for MSFOS
        }//MSFOS>=0
      }//blind data
      //MSFOS - CR not blinded
      if(SR3l[ 2]>=0&&MSFOSvec.size()>0){
        fillhisto(    histos, "MSFOS_all3l",            sample, sn, MSFOSvec[0], weight);
        if(lepsf()>0) fillhisto(    histos, "MSFOS_all3l_lepSFup",    sample, sn, MSFOSvec[0], weight*lepsf_up()/lepsf());
        if(lepsf()>0) fillhisto(    histos, "MSFOS_all3l_lepSFdn",    sample, sn, MSFOSvec[0], weight*lepsf_dn()/lepsf());
        if(SR3l[ 2]==1){
          fillhisto(  histos, "MSFOS_1SFOS",            sample, sn, MSFOSvec[0], weight);
          if(lepsf()>0) fillhisto(  histos, "MSFOS_1SFOS_lepSFup",    sample, sn, MSFOSvec[0], weight*lepsf_up()/lepsf());
          if(lepsf()>0) fillhisto(  histos, "MSFOS_1SFOS_lepSFdn",    sample, sn, MSFOSvec[0], weight*lepsf_dn()/lepsf());
        }
        if(SR3l[ 2]==2){
          fillhisto(  histos, "MSFOS_2SFOS",            sample, sn, MSFOSvec[0], weight);
          if(lepsf()>0) fillhisto(  histos, "MSFOS_2SFOS_lepSFup",    sample, sn, MSFOSvec[0], weight*lepsf_up()/lepsf());
          if(lepsf()>0) fillhisto(  histos, "MSFOS_2SFOS_lepSFdn",    sample, sn, MSFOSvec[0], weight*lepsf_dn()/lepsf());
        }
        for(unsigned int i = 0; i<MSFOSvec.size();++i){
          fillhisto(  histos, "MSFOSall_all3l",         sample, sn, MSFOSvec[i], weight);
          if(lepsf()>0) fillhisto(  histos, "MSFOSall_all3l_lepSFup", sample, sn, MSFOSvec[i], weight*lepsf_up()/lepsf());
          if(lepsf()>0) fillhisto(  histos, "MSFOSall_all3l_lepSFdn", sample, sn, MSFOSvec[i], weight*lepsf_dn()/lepsf());
          if(SR3l[ 2]==2){
            fillhisto(histos, "MSFOSall_2SFOS",         sample, sn, MSFOSvec[i], weight);
            if(lepsf()>0) fillhisto(histos, "MSFOSall_2SFOS_lepSFup", sample, sn, MSFOSvec[i], weight*lepsf_up()/lepsf());
            if(lepsf()>0) fillhisto(histos, "MSFOSall_2SFOS_lepSFdn", sample, sn, MSFOSvec[i], weight*lepsf_dn()/lepsf());
          }
        }//for MSFOS
      }//MSFOS>=0
      
      //Mjj sideband
      fillSRhisto(histos, "YieldsSR_Mjjside",             sample, sn, SRSS[20], -1, weight);
      fillSRhisto(histos, "YieldsSR_Mjjside_rawweight",   sample, sn, SRSS[20], -1, rawweight);
      fillSRhisto(histos, "YieldsSR_Mjjside_raw",         sample, sn, SRSS[20], -1, 1.);
      fillSRhisto(histos, "YieldsSR_Mjjside_WZup",        sample, sn, SRSS[20], -1, weight*(1.+xsecweightWZ));
      fillSRhisto(histos, "YieldsSR_Mjjside_WZdn",        sample, sn, SRSS[20], -1, weight*(1.-xsecweightWZ));
      fillSRhisto(histos, "YieldsSR_Mjjside_ttZup",       sample, sn, SRSS[20], -1, weight*(1.+xsecweightttZ));
      fillSRhisto(histos, "YieldsSR_Mjjside_ttZdn",       sample, sn, SRSS[20], -1, weight*(1.-xsecweightttZ));    
      fillSRhisto(histos, "YieldsSR_Mjjside_jesup",       sample, sn, SRSS[26], -1, weight);
      fillSRhisto(histos, "YieldsSR_Mjjside_jesdn",       sample, sn, SRSS[30], -1, weight);
      if(purewgt()>0) fillSRhisto(histos, "YieldsSR_Mjjside_PUup",        sample, sn, SRSS[20], -1, weight*purewgt_up()/purewgt());
      if(purewgt()>0) fillSRhisto(histos, "YieldsSR_Mjjside_PUdn",        sample, sn, SRSS[20], -1, weight*purewgt_dn()/purewgt());
      if(lepsf()>0) fillSRhisto(histos, "YieldsSR_Mjjside_lepSFup",     sample, sn, SRSS[20], -1, weight*lepsf_up()/lepsf());
      if(lepsf()>0) fillSRhisto(histos, "YieldsSR_Mjjside_lepSFdn",     sample, sn, SRSS[20], -1, weight*lepsf_dn()/lepsf());
      if(SRSS[ 1]>=0){
        int t = SRSS[ 1];
        if(MjjL()>400.||DetajjL()>1.5) t = -1;
        if(fabs(Mjj()     -80.)<=15.)  t = -1;
        if(SRSS[ 1]==0&&(met_pt()>40.||MllSS()<=40.)              ) t = -1;
        if(SRSS[ 1]==1&&(met_pt()>40.||MllSS()<=30.||MTmax()<=90.)) t = -1;
        if(SRSS[ 1]==2&&(met_pt()>40.||MllSS()<=40.)              ) t = -1;
        fillSRhisto(histos, "YieldsSR_Mjjside_lowMET",   sample, sn, t, -1, weight);
        t = ((SRSS[ 1]==1) ? SRSS[ 1] : -1);
        if(MjjL()>400.||DetajjL()>1.5) t = -1;
        if(fabs(Mjj()     -80.)<=15.)  t = -1;
        if(SRSS[ 1]==1&&(met_pt()<=60.||MllSS()<=30.||MTmax()>90.)) t = -1;
        fillSRhisto(histos, "YieldsSR_Mjjside_lowMTmax", sample, sn, t, -1, weight);
      }

      if(SRSS[ 1]>=0){
        int t = SRSS[ 1];
        if(MjjL()>400.||DetajjL()>1.5) t = -1;
        if(fabs(Mjj()     -80.)> 15.)  t = -1;
        if(SRSS[ 1]==0&&(met_pt()>60.||MllSS()<=40.)              ) t = -1;
        if(SRSS[ 1]==1&&(met_pt()>60.||MllSS()<=30.||MTmax()<=90.)) t = -1;
        if(SRSS[ 1]==2&&(met_pt()> 0.||MllSS()<=40.)              ) t = -1;
        fillSRhisto(histos, "YieldsSR_lowMET",   sample, sn, t, -1, weight);
        t = ((SRSS[ 1]==1) ? SRSS[ 1] : -1);
        if(MjjL()>400.||DetajjL()>1.5) t = -1;
        if(fabs(Mjj()     -80.)> 15.)  t = -1;
        if(SRSS[ 1]==1&&(met_pt()<=60.||MllSS()<=30.||MTmax()>90.)) t = -1;
        fillSRhisto(histos, "YieldsSR_lowMTmax", sample, sn, t, -1, weight);
      }
      
      fillSRhisto(histos, "YieldsCR",           sample, sn, SRSS[ 2], SR3l[ 2], weight);
      fillSRhisto(histos, "YieldsCR_jesup",     sample, sn, SRSS[ 8], SR3l[ 8], weight);
      fillSRhisto(histos, "YieldsCR_jesdn",     sample, sn, SRSS[12], SR3l[12], weight);
      if(purewgt()>0) fillSRhisto(histos, "YieldsCR_PUup",      sample, sn, SRSS[ 8], SR3l[ 8], weight*purewgt_up()/purewgt());
      if(purewgt()>0) fillSRhisto(histos, "YieldsCR_PUdn",      sample, sn, SRSS[12], SR3l[12], weight*purewgt_dn()/purewgt());
      if(lepsf()>0) fillSRhisto(histos, "YieldsCR_lepSFup",   sample, sn, SRSS[ 2], SR3l[ 2], weight*lepsf_up()/lepsf());
      if(lepsf()>0) fillSRhisto(histos, "YieldsCR_lepSFdn",   sample, sn, SRSS[ 2], SR3l[ 2], weight*lepsf_dn()/lepsf());
      //if((SRSS[2]>=0||SR3l>=0)&&lepsf()<=0) cout << "lepSF " << lepsf() << " " << lepsf_up() << " " << lepsf_dn() << endl;
      //if((SRSS[2]>=0||SR3l>=0)&&lepsf()>0) cout << "lepSF " << lepsf() << " " << lepsf_up() << " " << lepsf_dn() << endl;
      if(fabs(Mjj()   -80.)<15.||SR3l[ 2]>=0)  fillSRhisto(histos, "YieldsCR_cutonMjj",           sample, sn, SRSS[ 2], SR3l[ 2], weight);
      if(fabs(Mjj_up()-80.)<15.||SR3l[ 8]>=0)  fillSRhisto(histos, "YieldsCR_cutonMjj_jesup",     sample, sn, SRSS[ 8], SR3l[ 8], weight);
      if(fabs(Mjj_dn()-80.)<15.||SR3l[12]>=0)  fillSRhisto(histos, "YieldsCR_cutonMjj_jesdn",     sample, sn, SRSS[12], SR3l[12], weight);
      if(fabs(Mjj()   -80.)>=15.||SR3l[ 2]>=0) fillSRhisto(histos, "YieldsCR_anticutonMjj",       sample, sn, SRSS[ 2], SR3l[ 2], weight);
      if(fabs(Mjj_up()-80.)>=15.||SR3l[ 8]>=0) fillSRhisto(histos, "YieldsCR_anticutonMjj_jesup", sample, sn, SRSS[ 8], SR3l[ 8], weight);
      if(fabs(Mjj_dn()-80.)>=15.||SR3l[12]>=0) fillSRhisto(histos, "YieldsCR_anticutonMjj_jesdn", sample, sn, SRSS[12], SR3l[12], weight);
      fillSRhisto(histos, "YieldsCR_WZup",      sample, sn, SRSS[ 2], SR3l[ 2], weight*(1.+xsecweightWZ));
      fillSRhisto(histos, "YieldsCR_WZdn",      sample, sn, SRSS[ 2], SR3l[ 2], weight*(1.-xsecweightWZ));
      fillSRhisto(histos, "YieldsCR_ttZup",     sample, sn, SRSS[ 2], SR3l[ 2], weight*(1.+xsecweightttZ));
      fillSRhisto(histos, "YieldsCR_ttZdn",     sample, sn, SRSS[ 2], SR3l[ 2], weight*(1.-xsecweightttZ));
      if(SRSS[ 2]>=0) fillhisto(histos, "Mjj_CRlike_allSS",       sample, sn, Mjj(),    weight);
      if(SRSS[ 8]>=0) fillhisto(histos, "Mjj_CRlike_allSS_jesup", sample, sn, Mjj_up(), weight);
      if(SRSS[12]>=0) fillhisto(histos, "Mjj_CRlike_allSS_jesdn", sample, sn, Mjj_dn(), weight);
      if(SRSS[ 4]>=0&&MSFOSvec.size()>0){
        bool lowMETSS = (SRSS[4]==2 ? false : (met_pt()<60.));
        bool lowMllSS = (SRSS[4]==1 ? (MllSS()<30.) : (MllSS()<40.));
        fillSRhisto(histos, "YieldsCR_noMSFOSsel_SS",        sample, sn, SRSS[ 4], -1, weight);
        fillhisto(  histos, "MSFOS_CRlike_allSS",            sample, sn, MSFOSvec[0],  weight);
        if(lepsf()>0) fillhisto(  histos, "MSFOS_CRlike_allSS_lepSFup",    sample, sn, MSFOSvec[0],  weight*lepsf_up()/lepsf());
        if(lepsf()>0) fillhisto(  histos, "MSFOS_CRlike_allSS_lepSFdn",    sample, sn, MSFOSvec[0],  weight*lepsf_dn()/lepsf());
        for(unsigned int i = 0; i<MSFOSvec.size();++i){
          fillhisto(histos, "MSFOSall_CRlike_allSS",         sample, sn, MSFOSvec[i], weight);
          if(lepsf()>0) fillhisto(histos, "MSFOSall_CRlike_allSS_lepSFup", sample, sn, MSFOSvec[i], weight*lepsf_up()/lepsf());
          if(lepsf()>0) fillhisto(histos, "MSFOSall_CRlike_allSS_lepSFdn", sample, sn, MSFOSvec[i], weight*lepsf_dn()/lepsf());
        }
      }
      if(SRSS[ 5]>=0&&MSFOSvec.size()>0){
        bool highMETSS = (SRSS[5]==2 ? true : (met_pt()>60.));
        bool highMllSS = (SRSS[5]==1 ? (MllSS()>30.) : (MllSS()>40.));
        bool highMTmax = (SRSS[5]==1 ? (MTmax()>90.) : true);
        if(highMTmax){
          if(!highMETSS&& highMllSS) fillhisto(  histos, "MSFOS_CRlike_allSS_lowMET",        sample, sn, MSFOSvec[0],  weight);
          if( highMETSS&&!highMllSS) fillhisto(  histos, "MSFOS_CRlike_allSS_lowMllSS",      sample, sn, MSFOSvec[0],  weight);
          if(!highMETSS&&!highMllSS) fillhisto(  histos, "MSFOS_CRlike_allSS_lowMETMllSS",   sample, sn, MSFOSvec[0],  weight);
          if(!highMETSS||!highMllSS) fillhisto(  histos, "MSFOS_CRlike_allSS_lowMETorMllSS", sample, sn, MSFOSvec[0],  weight);
          for(unsigned int i = 0; i<MSFOSvec.size();++i){
            if(!highMETSS&& highMllSS) fillhisto(  histos, "MSFOSall_CRlike_allSS_lowMET",        sample, sn, MSFOSvec[i],  weight);
            if( highMETSS&&!highMllSS) fillhisto(  histos, "MSFOSall_CRlike_allSS_lowMllSS",      sample, sn, MSFOSvec[i],  weight);
            if(!highMETSS&&!highMllSS) fillhisto(  histos, "MSFOSall_CRlike_allSS_lowMETMllSS",   sample, sn, MSFOSvec[i],  weight);
            if(!highMETSS||!highMllSS) fillhisto(  histos, "MSFOSall_CRlike_allSS_lowMETorMllSS", sample, sn, MSFOSvec[i],  weight);
          }
        }
      }
      if((SR3l[ 1]>=0||SR3l[ 3]>=0)&&MSFOSvec.size()>0&&fabs(M3l()-90.)>10.){
        bool passMET = true;
        if((SR3l[ 1]==0||SR3l[ 3]==0)&&met_pt()<30.) passMET = false;
        if((SR3l[ 1]==1||SR3l[ 3]==1)&&met_pt()<40.) passMET = false;
        if((SR3l[ 1]==2||SR3l[ 3]==2)&&met_pt()<55.) passMET = false;
        bool passPTlll             = ((SR3l[ 1]==0||SR3l[ 3]==0) ? (true) : (Pt3l()>=60.));
        bool passDPhilllMET        = (DPhi3lMET()>=2.5);
        bool passMT3rd             = ((SR3l[ 1]==1||SR3l[ 3]==1)&&MT3rd()>90);
        bool passneither           =  !passMET&&!passPTlll&&!passDPhilllMET&& passMT3rd;
        bool passnotall            = !(passMET&& passPTlll&& passDPhilllMET)&&passMT3rd;
        bool passneitherInclMT3rd  =  !passMET&&!passPTlll&&!passDPhilllMET&&!passMT3rd;
        bool passnotallInclMT3rd   = !(passMET&& passPTlll&& passDPhilllMET&& passMT3rd);
        bool invertMT3rd           =   passMET&& passPTlll&& passDPhilllMET&&!passMT3rd;
	
        if(passneither){
          fillSRhisto(histos, "YieldsSR_invertMETdPhiPt",         sample, sn, -1, SR3l[ 1],      weight);
          fillSRhisto(histos, "YieldsCR_invertMETdPhiPt",         sample, sn, -1, SR3l[ 3],      weight);
          fillhisto(  histos, "MSFOS_all3l_invertMETdPhiPt",      sample, sn, MSFOSvec[0],       weight);
          if((SR3l[ 1]==1)||(SR3l[ 3]==1))   fillhisto(histos, "MSFOS_1SFOS_invertMETdPhiPt",    sample, sn, MSFOSvec[0], weight);
          if((SR3l[ 1]==2)||(SR3l[ 3]==2))   fillhisto(histos, "MSFOS_2SFOS_invertMETdPhiPt",    sample, sn, MSFOSvec[0], weight);
          for(unsigned int i = 0; i<MSFOSvec.size();++i){
            fillhisto(histos, "MSFOSall_all3l_invertMETdPhiPt",   sample, sn, MSFOSvec[i],       weight);
            if((SR3l[ 1]==2)||(SR3l[ 3]==2)) fillhisto(histos, "MSFOSall_2SFOS_invertMETdPhiPt", sample, sn, MSFOSvec[i], weight);
          }
        }
        if(passnotall){
          fillSRhisto(histos, "YieldsSR_inverteitherMETdPhiPt",            sample, sn, -1, SR3l[ 1],     weight);
          fillSRhisto(histos, "YieldsCR_inverteitherMETdPhiPt",            sample, sn, -1, SR3l[ 3],     weight);
          fillhisto(  histos, "MSFOS_all3l_inverteitherMETdPhiPt",         sample, sn, MSFOSvec[0],      weight);
          if((SR3l[ 1]==1)||(SR3l[ 3]==1))   fillhisto(histos, "MSFOS_1SFOS_inverteitherMETdPhiPt",      sample, sn, MSFOSvec[0], weight);
          if((SR3l[ 1]==2)||(SR3l[ 3]==2))   fillhisto(histos, "MSFOS_2SFOS_inverteitherMETdPhiPt",      sample, sn, MSFOSvec[0], weight);
          for(unsigned int i = 0; i<MSFOSvec.size();++i){
            fillhisto(histos, "MSFOSall_all3l_inverteitherMETdPhiPt",      sample, sn, MSFOSvec[i],      weight);
            if((SR3l[ 1]==2)||(SR3l[ 3]==2)) fillhisto(histos, "MSFOSall_2SFOS_inverteitherMETdPhiPt",   sample, sn, MSFOSvec[i], weight);
          }
        }
        if(passnotallInclMT3rd){
          fillSRhisto(histos, "YieldsSR_inverteitherMT3rdMETdPhiPt",    sample, sn, -1, SR3l[ 1], weight);
          fillSRhisto(histos, "YieldsCR_inverteitherMT3rdMETdPhiPt",    sample, sn, -1, SR3l[ 3], weight);
          fillhisto(  histos, "MSFOS_all3l_inverteitherMT3rdMETdPhiPt",  sample, sn, MSFOSvec[0],  weight);
          fillhisto(  histos, "MSFOS_1SFOS_inverteitherMT3rdMETdPhiPt", sample, sn, MSFOSvec[0],  weight);
          if((SR3l[ 1]==1)||(SR3l[ 3]==1))   fillhisto(histos, "MSFOS_1SFOS_inverteitherMT3rdMETdPhiPt", sample, sn, MSFOSvec[0], weight);
          if((SR3l[ 1]==2)||(SR3l[ 3]==2))   fillhisto(histos, "MSFOS_2SFOS_inverteitherMT3rdMETdPhiPt", sample, sn, MSFOSvec[0], weight);
          for(unsigned int i = 0; i<MSFOSvec.size();++i){
            fillhisto(histos, "MSFOSall_all3l_inverteitherMT3rdMETdPhiPt",      sample, sn, MSFOSvec[i],      weight);
            if((SR3l[ 1]==2)||(SR3l[ 3]==2)) fillhisto(histos, "MSFOSall_2SFOS_inverteitherMT3rdMETdPhiPt",   sample, sn, MSFOSvec[i], weight);
          }
          if(passMET){
            fillSRhisto(histos, "YieldsSR_inverteitherMT3rddPhiPt",    sample, sn, -1, SR3l[ 1], weight);
            fillSRhisto(histos, "YieldsCR_inverteitherMT3rddPhiPt",    sample, sn, -1, SR3l[ 3], weight);
            fillhisto(  histos, "MSFOS_all3l_inverteitherMT3rddPhiPt",  sample, sn, MSFOSvec[0],  weight);
            fillhisto(  histos, "MSFOS_1SFOS_inverteitherMT3rddPhiPt", sample, sn, MSFOSvec[0],  weight);
            if((SR3l[ 1]==1)||(SR3l[ 3]==1))   fillhisto(histos, "MSFOS_1SFOS_inverteitherMT3rddPhiPt", sample, sn, MSFOSvec[0], weight);
            if((SR3l[ 1]==2)||(SR3l[ 3]==2))   fillhisto(histos, "MSFOS_2SFOS_inverteitherMT3rddPhiPt", sample, sn, MSFOSvec[0], weight);
            for(unsigned int i = 0; i<MSFOSvec.size();++i){
              fillhisto(histos, "MSFOSall_all3l_inverteitherMT3rddPhiPt",      sample, sn, MSFOSvec[i],      weight);
              if((SR3l[ 1]==2)||(SR3l[ 3]==2)) fillhisto(histos, "MSFOSall_2SFOS_inverteitherMT3rddPhiPt",   sample, sn, MSFOSvec[i], weight);
            }
          }
          if(passDPhilllMET){
            fillSRhisto(histos, "YieldsSR_inverteitherMT3rdMETPt",    sample, sn, -1, SR3l[ 1], weight);
            fillSRhisto(histos, "YieldsCR_inverteitherMT3rdMETPt",    sample, sn, -1, SR3l[ 3], weight);
            fillhisto(  histos, "MSFOS_all3l_inverteitherMT3rdMETPt",  sample, sn, MSFOSvec[0],  weight);
            fillhisto(  histos, "MSFOS_1SFOS_inverteitherMT3rdMETPt", sample, sn, MSFOSvec[0],  weight);
            if((SR3l[ 1]==1)||(SR3l[ 3]==1))   fillhisto(histos, "MSFOS_1SFOS_inverteitherMT3rdMETPt", sample, sn, MSFOSvec[0], weight);
            if((SR3l[ 1]==2)||(SR3l[ 3]==2))   fillhisto(histos, "MSFOS_2SFOS_inverteitherMT3rdMETPt", sample, sn, MSFOSvec[0], weight);
            for(unsigned int i = 0; i<MSFOSvec.size();++i){
              fillhisto(histos, "MSFOSall_all3l_inverteitherMT3rdMETPt",      sample, sn, MSFOSvec[i],      weight);
              if((SR3l[ 1]==2)||(SR3l[ 3]==2)) fillhisto(histos, "MSFOSall_2SFOS_inverteitherMT3rdMETPt",   sample, sn, MSFOSvec[i], weight);
            }
          }
          if(passPTlll){
            fillSRhisto(histos, "YieldsSR_inverteitherMT3rdMETdPhi",    sample, sn, -1, SR3l[ 1], weight);
            fillSRhisto(histos, "YieldsCR_inverteitherMT3rdMETdPhi",    sample, sn, -1, SR3l[ 3], weight);
            fillhisto(  histos, "MSFOS_all3l_inverteitherMT3rdMETdPhi",  sample, sn, MSFOSvec[0],  weight);
            fillhisto(  histos, "MSFOS_1SFOS_inverteitherMT3rdMETdPhi", sample, sn, MSFOSvec[0],  weight);
            if((SR3l[ 1]==1)||(SR3l[ 3]==1))   fillhisto(histos, "MSFOS_1SFOS_inverteitherMT3rdMETdPhi", sample, sn, MSFOSvec[0], weight);
            if((SR3l[ 1]==2)||(SR3l[ 3]==2))   fillhisto(histos, "MSFOS_2SFOS_inverteitherMT3rdMETdPhi", sample, sn, MSFOSvec[0], weight);
            for(unsigned int i = 0; i<MSFOSvec.size();++i){
              fillhisto(histos, "MSFOSall_all3l_inverteitherMT3rdMETdPhi",      sample, sn, MSFOSvec[i],      weight);
              if((SR3l[ 1]==2)||(SR3l[ 3]==2)) fillhisto(histos, "MSFOSall_2SFOS_inverteitherMT3rdMETdPhi",   sample, sn, MSFOSvec[i], weight);
            }
          }
        }
        if((SR3l[ 1]==1)||(SR3l[ 3]==1)){
          if(invertMT3rd){
            fillSRhisto(histos, "YieldsSR_invertMT3rd",                   sample, sn, -1, SR3l[ 1], weight);
            fillSRhisto(histos, "YieldsCR_invertMT3rd",                   sample, sn, -1, SR3l[ 3], weight);
            fillhisto(  histos, "MSFOS_1SFOS_invertMT3rd",                sample, sn, MSFOSvec[0],  weight);
          }
          if(passneitherInclMT3rd){
            fillSRhisto(histos, "YieldsSR_invertMT3rdMETdPhiPt",          sample, sn, -1, SR3l[ 1], weight);
            fillSRhisto(histos, "YieldsCR_invertMT3rdMETdPhiPt",          sample, sn, -1, SR3l[ 3], weight);
            fillhisto(  histos, "MSFOS_1SFOS_invertMT3rdMETdPhiPt",       sample, sn, MSFOSvec[0],  weight);
          }
        }
        //new end
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

  SaveHistosToFile("rootfiles/Check3lWZCR.root",histos,true,true,(chainnumber==0));
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
