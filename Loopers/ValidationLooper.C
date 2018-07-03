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
  
  // Benchmark
  TBenchmark *bmark = new TBenchmark();
  bmark->Start("benchmark");

  const char* json_file = "data/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt";
  set_goodrun_file_json(json_file);

  // Example Histograms
  TDirectory *rootdir = gDirectory->GetDirectory("Rint:");

  vector<string> histonames; histonames.clear();
  vector<int> hbins; hbins.clear();
  vector<float> hlow; hlow.clear();
  vector<float> hup; hup.clear();

  //split ttX/ttV/ttZ
  histonames.push_back("NB_VR3l_Z_ge2j_ge1b");             hbins.push_back(3);  hlow.push_back( 1); hup.push_back(4);
  histonames.push_back("NB_VR3l_noZ_ge2j_ge1b");           hbins.push_back(3);  hlow.push_back( 1); hup.push_back(4);
  histonames.push_back("NB_VR3l_Z_ge2j_ge1bmed");          hbins.push_back(3);  hlow.push_back( 1); hup.push_back(4);
  histonames.push_back("NB_VR3l_noZ_ge2j_ge1bmed");        hbins.push_back(3);  hlow.push_back( 1); hup.push_back(4);
  histonames.push_back("NB_VRSS_MjjW_ge4j_ge1b");          hbins.push_back(3);  hlow.push_back( 1); hup.push_back(4);
  histonames.push_back("NB_VRSS_MjjW_ge4j_ge1bmed");       hbins.push_back(3);  hlow.push_back( 1); hup.push_back(4);
  histonames.push_back("NB0_VR3l_Z_ge2j_ge1b");            hbins.push_back(4);  hlow.push_back( 0); hup.push_back(4);
  histonames.push_back("NB0_VR3l_noZ_ge2j_ge1b");          hbins.push_back(4);  hlow.push_back( 0); hup.push_back(4);
  histonames.push_back("NB0_VR3l_Z_ge2j_ge1bmed");         hbins.push_back(4);  hlow.push_back( 0); hup.push_back(4);
  histonames.push_back("NB0_VR3l_noZ_ge2j_ge1bmed");       hbins.push_back(4);  hlow.push_back( 0); hup.push_back(4);
  histonames.push_back("NB0_VRSS_MjjW_ge4j_ge1b");         hbins.push_back(4);  hlow.push_back( 0); hup.push_back(4);
  histonames.push_back("NB0_VRSS_MjjW_ge4j_ge1bmed");      hbins.push_back(4);  hlow.push_back( 0); hup.push_back(4);


  histonames.push_back("ZPt_VR3l_Z_ge2j_ge1bmed");         hbins.push_back(15); hlow.push_back( 0); hup.push_back(300);
  histonames.push_back("Ptlll_VR3l_Z_ge2j_ge1bmed");       hbins.push_back(15); hlow.push_back( 0); hup.push_back(300);
  histonames.push_back("Ptlll_VR3l_noZ_ge2j_ge1bmed");     hbins.push_back(15); hlow.push_back( 0); hup.push_back(300);
  histonames.push_back("MET_VR3l_Z_ge2j_ge1bmed");         hbins.push_back(15); hlow.push_back( 0); hup.push_back(300);
  histonames.push_back("MET_VR3l_noZ_ge2j_ge1bmed");       hbins.push_back(15); hlow.push_back( 0); hup.push_back(300);
  histonames.push_back("Ptll_VRSS_MjjW_ge4j_ge1bmed");     hbins.push_back(15); hlow.push_back( 0); hup.push_back(300);
  histonames.push_back("MET_VRSS_MjjW_ge4j_ge1bmed");      hbins.push_back(15); hlow.push_back( 0); hup.push_back(300);
  histonames.push_back("MSFOS_VR3l_Z_ge2j_ge1bmed");       hbins.push_back(15); hlow.push_back( 0); hup.push_back(225);
  histonames.push_back("MSFOS_VR3l_noZ_ge2j_ge1bmed");     hbins.push_back(15); hlow.push_back( 0); hup.push_back(225);
  histonames.push_back("ZPt_VR3l_Z_ge2j_ge2bmed");         hbins.push_back(15); hlow.push_back( 0); hup.push_back(300);
  histonames.push_back("Ptlll_VR3l_Z_ge2j_ge2bmed");       hbins.push_back(15); hlow.push_back( 0); hup.push_back(300);
  histonames.push_back("Ptlll_VR3l_noZ_ge2j_ge2bmed");     hbins.push_back(15); hlow.push_back( 0); hup.push_back(300);
  histonames.push_back("MET_VR3l_Z_ge2j_ge2bmed");         hbins.push_back(15); hlow.push_back( 0); hup.push_back(300);
  histonames.push_back("MET_VR3l_noZ_ge2j_ge2bmed");       hbins.push_back(15); hlow.push_back( 0); hup.push_back(300);
  histonames.push_back("Ptll_VRSS_MjjW_ge4j_ge2bmed");     hbins.push_back(15); hlow.push_back( 0); hup.push_back(300);
  histonames.push_back("MET_VRSS_MjjW_ge4j_ge2bmed");      hbins.push_back(15); hlow.push_back( 0); hup.push_back(300);
  histonames.push_back("MSFOS_VR3l_Z_ge2j_ge2bmed");       hbins.push_back(15); hlow.push_back( 0); hup.push_back(225);
  histonames.push_back("MSFOS_VR3l_noZ_ge2j_ge2bmed");     hbins.push_back(15); hlow.push_back( 0); hup.push_back(225);
  histonames.push_back("ZPt_VR3l_Z_ge2j_ge1b");            hbins.push_back(15); hlow.push_back( 0); hup.push_back(300);
  histonames.push_back("Ptlll_VR3l_Z_ge2j_ge1b");          hbins.push_back(15); hlow.push_back( 0); hup.push_back(300);
  histonames.push_back("Ptlll_VR3l_noZ_ge2j_ge1b");        hbins.push_back(15); hlow.push_back( 0); hup.push_back(300);
  histonames.push_back("MET_VR3l_Z_ge2j_ge1b");            hbins.push_back(15); hlow.push_back( 0); hup.push_back(300);
  histonames.push_back("MET_VR3l_noZ_ge2j_ge1b");          hbins.push_back(15); hlow.push_back( 0); hup.push_back(300);
  histonames.push_back("Ptll_VRSS_MjjW_ge4j_ge1b");        hbins.push_back(15); hlow.push_back( 0); hup.push_back(300);
  histonames.push_back("MET_VRSS_MjjW_ge4j_ge1b");         hbins.push_back(15); hlow.push_back( 0); hup.push_back(300);
  histonames.push_back("MSFOS_VR3l_Z_ge2j_ge1b");          hbins.push_back(15); hlow.push_back( 0); hup.push_back(225);
  histonames.push_back("MSFOS_VR3l_noZ_ge2j_ge1b");        hbins.push_back(15); hlow.push_back( 0); hup.push_back(225);
  histonames.push_back("ZPt_VR3l_Z_ge2j_ge2b");            hbins.push_back(15); hlow.push_back( 0); hup.push_back(300);
  histonames.push_back("Ptlll_VR3l_Z_ge2j_ge2b");          hbins.push_back(15); hlow.push_back( 0); hup.push_back(300);
  histonames.push_back("Ptlll_VR3l_noZ_ge2j_ge2b");        hbins.push_back(15); hlow.push_back( 0); hup.push_back(300);
  histonames.push_back("MET_VR3l_Z_ge2j_ge2b");            hbins.push_back(15); hlow.push_back( 0); hup.push_back(300);
  histonames.push_back("MET_VR3l_noZ_ge2j_ge2b");          hbins.push_back(15); hlow.push_back( 0); hup.push_back(300);
  histonames.push_back("Ptll_VRSS_MjjW_ge4j_ge2b");        hbins.push_back(15); hlow.push_back( 0); hup.push_back(300);
  histonames.push_back("MET_VRSS_MjjW_ge4j_ge2b");         hbins.push_back(15); hlow.push_back( 0); hup.push_back(300);
  histonames.push_back("MSFOS_VR3l_Z_ge2j_ge2b");          hbins.push_back(15); hlow.push_back( 0); hup.push_back(225);
  histonames.push_back("MSFOS_VR3l_noZ_ge2j_ge2b");        hbins.push_back(15); hlow.push_back( 0); hup.push_back(225);

  //WW VBS
  histonames.push_back("MjjL_VRSS_Detajj1p5");             hbins.push_back(15); hlow.push_back( 0); hup.push_back(750);
  histonames.push_back("Detajj_VRSS_MjjL400v2");           hbins.push_back(15); hlow.push_back( 0); hup.push_back(5.0);
  histonames.push_back("Detajj_VRSS_MjjL400");             hbins.push_back(15); hlow.push_back( 0); hup.push_back(3.0);
  histonames.push_back("MjjL_VRSS_Detajj1p5_Detajj3");     hbins.push_back(15); hlow.push_back( 0); hup.push_back(750);
  histonames.push_back("Detajj_VRSS_MjjL400_Detajj3");     hbins.push_back(15); hlow.push_back( 0); hup.push_back(5.0);
  histonames.push_back("MjjVBS_VRSS_Detajj1p5");           hbins.push_back(15); hlow.push_back( 0); hup.push_back(750);
  histonames.push_back("MjjVBS_VRSS_MjjL400");             hbins.push_back(15); hlow.push_back( 0); hup.push_back(750);
  histonames.push_back("MjjVBS_VRSS_Detajj1p5_Detajj3");   hbins.push_back(15); hlow.push_back( 0); hup.push_back(750);
  histonames.push_back("MjjVBS_VRSS_MjjL400_Detajj3");     hbins.push_back(15); hlow.push_back( 0); hup.push_back(750);
  //Zg
  histonames.push_back("pTlll_VR3l_noZ_lowMET");           hbins.push_back(10); hlow.push_back( 0); hup.push_back(100);
  histonames.push_back("Mlll_VR3l_noZ_lowMET");            hbins.push_back(13); hlow.push_back(20); hup.push_back(150);

  map<string, TH1D*> histos =  bookhistograms(skimFilePrefix, histonames,hbins, hlow, hup, rootdir,2);
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

      if(firstgoodvertex()!=0)   continue;
      if(nVert()<0)              continue;
      if(nLlep()<2)              continue;
      if(nTlepSS()<1&&nTlep()<2) continue;//preselection can be done already here

      //weight = 1;
      if(string(currentFile->GetTitle()).find("wjets_incl_mgmlm_")!=string::npos){
	if(gen_ht()>100) continue;
      }
      if(string(currentFile->GetTitle()).find("dy_m50_mgmlm_ext1_")!=string::npos){
	if(gen_ht()>100) continue;
      }
      //if(string(currentFile->GetTitle()).find("www_2l_mia")!=string::npos)      weight *= 0.066805* 91900./(91900.+164800.);//(208fb/1pb)*BR(WWW—> >=2l)*combineweight
      //if(string(currentFile->GetTitle()).find("www_2l_ext1_mia")!=string::npos) weight *= 0.066805*164800./(91900.+164800.);//(208fb/1pb)*BR(WWW—> >=2l)*combineweight
      if(weight>100) cout << weight << " " << currentFile->GetTitle() << endl;
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
      if(splitVH(fname)){ sample = "WHtoWWW"; }
      string sn = string(bkgtype().Data());
      if(vetophoton()) continue;
      
      string extrasn = "";
      bool passextra1 = false;
      bool passextra2 = false;
      if(fname.find("wpwpjj_ewk")!=string::npos) { passextra1 = true; extrasn  = "WWVBS"; }
      if(fname.find("ttw_"      )!=string::npos) { passextra2 = true; extrasn  = "ttW";   }
      if(fname.find("ttz_"      )!=string::npos) { passextra2 = true; extrasn  = "ttZ";   }

      int nbmed = numJ(20.,2.4,0.8484);
      vector<string> mynb;
      if(nb() >=1) mynb.push_back("_ge1b");
      if(nb() >=2) mynb.push_back("_ge2b");
      if(nbmed>=1) mynb.push_back("_ge1bmed");
      if(nbmed>=2) mynb.push_back("_ge2bmed");
      
      int VR[10];  int dummy = -1;
      for(int i = 0; i<10; ++i) VR[i] = -1;
      int VR0e(-1), VR1e(-1), VR2e(-1);

      //1: VR3l,   Z, ge2j, ge1b loose
      if(nj30()>=2&&nb()>=1&&nVlep()==3&&Ntight3l()==3&&abs(lep_charge()[0]+lep_charge()[1]+lep_charge()[2])!=3&&Mll3L ()>=20.&&(nSFOS()==1||(nSFOS()>=2&&Mll3L1()>=20.))){
        if(nSFOS()==1){
          if(fabs(Mll3L()-MZ)>20.) VR[0] = 1;
          else                     VR[1] = 1;
        } else if(nSFOS()==2){
          if(fabs(Mll3L ()-MZ)>20.&&fabs(Mll3L1()-MZ)>20.) VR[0] = 2;
          else                                             VR[1] = 2;
        }
      }
      if(nj30()>=2&&nVlep()==3&&Ntight3l()==3&&abs(lep_charge()[0]+lep_charge()[1]+lep_charge()[2])!=3&&Mll3L ()>=20.&&(nSFOS()==1||(nSFOS()>=2&&Mll3L1()>=20.))){
        if(nSFOS()==1){
          if(fabs(Mll3L()-MZ)>20.) VR0e = 1;
          else                     VR1e = 1;
        } else if(nSFOS()==2){
          if(fabs(Mll3L ()-MZ)>20.&&fabs(Mll3L1()-MZ)>20.) VR0e = 2;
          else                                             VR1e = 2;
        }
      }
      //2: VRSS,MjjW,ge4j,ge1b loose
      VR[2] = isSRSS(true,0,true);
      if(VR[2]>=0){
        if(nj30()<4)            VR[2] = -1;
        if(fabs(Mjj()-80.)>15.) VR[2] = -1;
      }
      VR2e = std::max(isSRSS(true,0,true),isSRSS(true,0,false));
      if(VR2e>=0){
        if(nj30()<4)            VR2e = -1;
        if(fabs(Mjj()-80.)>15.) VR2e = -1;
      }
      //3,4: VRSS,ge2j,0b
      VR[3] = isSRSS(true);
      VR[4] = VR[3];
      VR[3] = (MjjL()  <400.) ? -1 : VR[3];
      VR[4] = (DetajjL()<1.5) ? -1 : VR[4];
      //5: VR3l, le1j,0b
      VR[5] = isSR3l(true);
      if(nSFOS()==0&&met_pt()>=30.) VR[5] = -1;
      if(nSFOS()==1&&met_pt()>=40.) VR[5] = -1;
      if(nSFOS()==2&&met_pt()>=55.) VR[5] = -1;
      
      float Mll = (nSFOS()==2&&(fabs(Mll3L()-MZ)>fabs(Mll3L1()-MZ))) ? Mll3L1() : Mll3L();
      float pTll = -1;
      if(nVlep()==2) pTll = (lep_p4()[0]+lep_p4()[1]).Pt();
      else if (nVlep()==3&&nSFOS()>=1){
        float minDeltaM = 1e6;
        if(isSFOS01()&&fabs(M01()-MZ)<minDeltaM) { minDeltaM = fabs(M01()-MZ); pTll = (lep_p4()[0]+lep_p4()[1]).Pt(); }
        if(isSFOS02()&&fabs(M02()-MZ)<minDeltaM) { minDeltaM = fabs(M02()-MZ); pTll = (lep_p4()[0]+lep_p4()[2]).Pt(); }
        if(isSFOS12()&&fabs(M12()-MZ)<minDeltaM) { minDeltaM = fabs(M12()-MZ); pTll = (lep_p4()[1]+lep_p4()[2]).Pt(); }
      }
      if(VR[1]>=1){//have a Z boson
        if(!passextra2)   fillhisto(histos, "NB_VR3l_Z_ge2j_ge1b",           sample, sn,      nb(),        weight);
        else              fillhisto(histos, "NB_VR3l_Z_ge2j_ge1b",           sample, extrasn, nb(),        weight, false);
        if(nbmed>=1){
          if(!passextra2) fillhisto(histos, "NB_VR3l_Z_ge2j_ge1bmed",        sample, sn,      nbmed,       weight);
          else            fillhisto(histos, "NB_VR3l_Z_ge2j_ge1bmed",        sample, extrasn, nbmed,       weight, false);
        }
      }
      if(VR1e>=1){//have a Z boson
        if(!passextra2)   fillhisto(histos, "NB0_VR3l_Z_ge2j_ge1b",           sample, sn,      nb(),        weight);
        else              fillhisto(histos, "NB0_VR3l_Z_ge2j_ge1b",           sample, extrasn, nb(),        weight, false);
        if(!passextra2)   fillhisto(histos, "NB0_VR3l_Z_ge2j_ge1bmed",        sample, sn,      nbmed,       weight);
        else              fillhisto(histos, "NB0_VR3l_Z_ge2j_ge1bmed",        sample, extrasn, nbmed,       weight, false);
      }
      if(VR[0]>=1){//have no Z boson
        if(!passextra2)   fillhisto(histos, "NB_VR3l_noZ_ge2j_ge1b",         sample, sn,      nb(),        weight);
        else              fillhisto(histos, "NB_VR3l_noZ_ge2j_ge1b",         sample, extrasn, nb(),        weight, false);
        if(nbmed>=1){
          if(!passextra2) fillhisto(histos, "NB_VR3l_noZ_ge2j_ge1bmed",      sample, sn,      nbmed,       weight);
          else            fillhisto(histos, "NB_VR3l_noZ_ge2j_ge1bmed",      sample, extrasn, nbmed,       weight, false);
        }
      }
      if(VR0e>=1){//have no Z boson
        if(!passextra2)   fillhisto(histos, "NB0_VR3l_noZ_ge2j_ge1b",         sample, sn,      nb(),        weight);
        else              fillhisto(histos, "NB0_VR3l_noZ_ge2j_ge1b",         sample, extrasn, nb(),        weight, false);
        if(!passextra2)   fillhisto(histos, "NB0_VR3l_noZ_ge2j_ge1bmed",      sample, sn,      nbmed,       weight);
        else              fillhisto(histos, "NB0_VR3l_noZ_ge2j_ge1bmed",      sample, extrasn, nbmed,       weight, false);
      }
      if(VR[2]>=0){
        if(!passextra2)   fillhisto(histos,   "NB_VRSS_MjjW_ge4j_ge1b",      sample, sn,      nb(),      weight);
        else              fillhisto(histos,   "NB_VRSS_MjjW_ge4j_ge1b",      sample, extrasn, nb(),      weight, false);
        if(nbmed>=1){
          if(!passextra2) fillhisto(histos,   "NB_VRSS_MjjW_ge4j_ge1bmed",   sample, sn,      nbmed,     weight);
          else            fillhisto(histos,   "NB_VRSS_MjjW_ge4j_ge1bmed",   sample, extrasn, nbmed,     weight, false);
        }
      }
      if(VR2e>=0){
        if(!passextra2)   fillhisto(histos,   "NB0_VRSS_MjjW_ge4j_ge1b",      sample, sn,      nb(),      weight);
        else              fillhisto(histos,   "NB0_VRSS_MjjW_ge4j_ge1b",      sample, extrasn, nb(),      weight, false);
        if(!passextra2)   fillhisto(histos,   "NB0_VRSS_MjjW_ge4j_ge1bmed",   sample, sn,      nbmed,     weight);
        else              fillhisto(histos,   "NB0_VRSS_MjjW_ge4j_ge1bmed",   sample, extrasn, nbmed,     weight, false);
      }
      for(unsigned int i = 0; i<mynb.size(); ++i){
        if(VR[1]>=1){//have a Z boson
          if(!passextra2)   fillhisto(histos, "MSFOS_VR3l_Z_ge2j"+mynb[i],   sample, sn,      Mll,         weight);
          else              fillhisto(histos, "MSFOS_VR3l_Z_ge2j"+mynb[i],   sample, extrasn, Mll,         weight, false);
          if(!passextra2)   fillhisto(histos, "Ptlll_VR3l_Z_ge2j"+mynb[i],   sample, sn,      Pt3l(),      weight);
          else              fillhisto(histos, "Ptlll_VR3l_Z_ge2j"+mynb[i],   sample, extrasn, Pt3l(),      weight, false);
          if(!passextra2)   fillhisto(histos,   "MET_VR3l_Z_ge2j"+mynb[i],   sample, sn,      met_pt(),    weight);
          else              fillhisto(histos,   "MET_VR3l_Z_ge2j"+mynb[i],   sample, extrasn, met_pt(),    weight, false);
          if(!passextra2)   fillhisto(histos,   "ZPt_VR3l_Z_ge2j"+mynb[i],   sample, sn,      pTll,        weight);
          else              fillhisto(histos,   "ZPt_VR3l_Z_ge2j"+mynb[i],   sample, extrasn, pTll,        weight, false);
        }
        if(VR[0]>=1){//have no Z boson
          if(!passextra2)   fillhisto(histos, "MSFOS_VR3l_noZ_ge2j"+mynb[i], sample, sn,      Mll,       weight);
          else              fillhisto(histos, "MSFOS_VR3l_noZ_ge2j"+mynb[i], sample, extrasn, Mll,       weight, false);
          if(!passextra2)   fillhisto(histos, "Ptlll_VR3l_noZ_ge2j"+mynb[i], sample, sn,      Pt3l(),    weight);
          else              fillhisto(histos, "Ptlll_VR3l_noZ_ge2j"+mynb[i], sample, extrasn, Pt3l(),    weight, false);
          if(!passextra2)   fillhisto(histos,   "MET_VR3l_noZ_ge2j"+mynb[i], sample, sn,      met_pt(),  weight);
          else              fillhisto(histos,   "MET_VR3l_noZ_ge2j"+mynb[i], sample, extrasn, met_pt(),  weight, false);
        }
        if(VR[2]>=0){
          if(!passextra2)   fillhisto(histos, "Ptll_VRSS_MjjW_ge4j"+mynb[i], sample, sn,      pTll,      weight);
          else              fillhisto(histos, "Ptll_VRSS_MjjW_ge4j"+mynb[i], sample, extrasn, pTll,      weight, false);
          if(!passextra2)   fillhisto(histos,  "MET_VRSS_MjjW_ge4j"+mynb[i], sample, sn,      met_pt(),  weight);
          else              fillhisto(histos,  "MET_VRSS_MjjW_ge4j"+mynb[i], sample, extrasn, met_pt(),  weight, false);
        }
      }
      if(VR[3]>=0){
        if(!passextra1)     fillhisto(histos, "Detajj_VRSS_MjjL400",         sample, sn,      DetajjL(), weight);
        else                fillhisto(histos, "Detajj_VRSS_MjjL400",         sample, extrasn, DetajjL(), weight, false);
        if(!passextra1)     fillhisto(histos, "Detajj_VRSS_MjjL400v2",       sample, sn,      DetajjL(), weight);
        else                fillhisto(histos, "Detajj_VRSS_MjjL400v2",       sample, extrasn, DetajjL(), weight, false);
        if(!passextra1&&Detajj()<=3.0)    fillhisto(histos, "Detajj_VRSS_MjjL400_Detajj3", sample, sn,      DetajjL(), weight);
        else if(Detajj()<=3.0)            fillhisto(histos, "Detajj_VRSS_MjjL400_Detajj3", sample, extrasn, DetajjL(), weight, false);
        if(!passextra1)     fillhisto(histos, "MjjVBS_VRSS_MjjL400",         sample, sn,      MjjVBF(), weight);
        else                fillhisto(histos, "MjjVBS_VRSS_MjjL400",         sample, extrasn, MjjVBF(), weight, false);
        if(!passextra1&&Detajj()<=3.0)    fillhisto(histos, "MjjVBS_VRSS_MjjL400_Detajj3", sample, sn,      MjjVBF(), weight);
        else if(Detajj()<=3.0)            fillhisto(histos, "MjjVBS_VRSS_MjjL400_Detajj3", sample, extrasn, MjjVBF(), weight, false);
      }
      if(VR[4]>=0){
        if(!passextra1)     fillhisto(histos, "MjjL_VRSS_Detajj1p5",         sample, sn,      MjjL(),    weight);
        else                fillhisto(histos, "MjjL_VRSS_Detajj1p5",         sample, extrasn, MjjL(),    weight, false);
        if(!passextra1&&Detajj()<=3.0)    fillhisto(histos, "MjjL_VRSS_Detajj1p5_Detajj3", sample, sn,      MjjL(),    weight);
        else if(Detajj()<=3.0)            fillhisto(histos, "MjjL_VRSS_Detajj1p5_Detajj3", sample, extrasn, MjjL(),    weight, false);
        if(!passextra1)     fillhisto(histos, "MjjVBS_VRSS_Detajj1p5",         sample, sn,      MjjVBF(),    weight);
        else                fillhisto(histos, "MjjVBS_VRSS_Detajj1p5",         sample, extrasn, MjjVBF(),    weight, false);
        if(!passextra1&&Detajj()<=3.0)    fillhisto(histos, "MjjVBS_VRSS_Detajj1p5_Detajj3", sample, sn,      MjjVBF(),    weight);
        else if(Detajj()<=3.0)            fillhisto(histos, "MjjVBS_VRSS_Detajj1p5_Detajj3", sample, extrasn, MjjVBF(),    weight, false);
      }
      if(VR[5]>=0){
        fillhisto(                    histos, "pTlll_VR3l_noZ_lowMET",       sample, sn,      Pt3l(),    weight);
        fillhisto(                    histos,  "Mlll_VR3l_noZ_lowMET",       sample, sn,      M3l(),     weight);
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
  
  SaveHistosToFile("rootfiles/Validations.root",histos,true,true,(chainnumber==0));
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
