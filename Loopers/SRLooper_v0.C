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
#define USE_CMS3_WWW100 

#include "Functions_v0.h"
#ifdef USE_CMS3_WWW100
#include "CMS3_WWW100.cc"
#else
#include "CMS3_WWW0118.cc"
#endif
#include "../CORE/Tools/dorky/dorky.h"
#include "../CORE/Tools/dorky/dorky.cc"
#include "../CORE/Tools/goodrun.h"
#include "../CORE/Tools/goodrun.cc"

using namespace std;
using namespace tas;

int ScanChain( TChain* chain, bool fast = true, int nEvents = -1, string skimFilePrefix = "test", int chainnumber=1) {

  vector<myevt> e;
  addeventtocheck(e,1, 2842, 1443084);
  addeventtocheck(e,1,17341, 8807395);
  addeventtocheck(e,1,15849, 8049420);
  addeventtocheck(e,1,21682,11012507);

  bool blindSR = true;
  bool btagreweighting = true;
  bool applylepSF      = false;
  bool applytrigSF     = false;
  bool applyPUrewgt    = true;
  bool getJECunc       = false;
  
  const char* json_file = "data/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt";
  set_goodrun_file_json(json_file);

  // Benchmark
  TBenchmark *bmark = new TBenchmark();
  bmark->Start("benchmark");

  bool storeeventnumbers = true;
  std::ostringstream*  SREE    ;
  std::ostringstream*  SREM    ;
  std::ostringstream*  SRMM    ;
  std::ostringstream*  SR0SFOS ;
  std::ostringstream*  SR1SFOS ;
  std::ostringstream*  SR2SFOS ;
  std::ostringstream*  AREE    ;
  std::ostringstream*  AREM    ;
  std::ostringstream*  ARMM    ;
  std::ostringstream*  AR0SFOS ;
  std::ostringstream*  AR1SFOS ;
  std::ostringstream*  AR2SFOS ;
  std::ostringstream*  CREE    ;
  std::ostringstream*  CREM    ;
  std::ostringstream*  CRMM    ;
  std::ostringstream*  CR0SFOS ;
  std::ostringstream*  CR1SFOS ;
  std::ostringstream*  CR2SFOS ;
  if(storeeventnumbers){
    SREE    = new std::ostringstream();
    SREM    = new std::ostringstream();
    SRMM    = new std::ostringstream();
    SR0SFOS = new std::ostringstream();
    SR1SFOS = new std::ostringstream();
    SR2SFOS = new std::ostringstream();
    AREE    = new std::ostringstream();
    AREM    = new std::ostringstream();
    ARMM    = new std::ostringstream();
    AR0SFOS = new std::ostringstream();
    AR1SFOS = new std::ostringstream();
    AR2SFOS = new std::ostringstream();
    CREE    = new std::ostringstream();
    CREM    = new std::ostringstream();
    CRMM    = new std::ostringstream();
    CR0SFOS = new std::ostringstream();
    CR1SFOS = new std::ostringstream();
    CR2SFOS = new std::ostringstream();
  }
  // Example Histograms
  TDirectory *rootdir = gDirectory->GetDirectory("Rint:");

  vector<string> histonames; histonames.clear();
  vector<int> hbins; hbins.clear();
  vector<float> hlow; hlow.clear();
  vector<float> hup; hup.clear();

  histonames.push_back("RawSignalRegion");                     hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("RawApplicationRegion");                hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("RawWZControlRegion");                  hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("RawSignalRegionPresel");               hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("RawApplicationRegionPresel");          hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("RawWZControlRegionPresel");            hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);

  histonames.push_back("SignalRegionPrecleaning");             hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("SignalRegion");                        hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("ApplicationRegion");                   hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("WZControlRegion");                     hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("ApplicationRegionPrecleaning");        hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("WZControlRegionPrecleaning");          hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("SignalRegionPresel");                  hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("SignalRegionPreselPrecleaning");       hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("ApplicationRegionPresel");             hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("WZControlRegionPresel");               hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("ApplicationRegionPreselPrecleaning");  hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("WZControlRegionPreselPrecleaning");    hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);

  histonames.push_back("SignalRegionNew");                     hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("ApplicationRegionNew");                hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("WZControlRegionNew");                  hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("SignalRegionPreselNew");               hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("ApplicationRegionPreselNew");          hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("WZControlRegionPreselNew");            hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
  
  histonames.push_back("SignalRegion_JECup");                  hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("SignalRegion_JECdn");                  hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("SignalRegion_lepSFup");                hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("SignalRegion_lepSFdn");                hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("SignalRegion_bHFSFup");                hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("SignalRegion_bHFSFdn");                hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("SignalRegion_bLFSFup");                hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("SignalRegion_bLFSFdn");                hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("SignalRegion_PUup");                   hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
  histonames.push_back("SignalRegion_PUdn");                   hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);

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
      if(firstgoodvertex()!=0)   continue;
      if(nVert()<0)              continue;
      //if(nlep()<2)               continue;

      //weight = 1;
      if(string(currentFile->GetTitle()).find("wjets_incl_mgmlm_")!=string::npos){
	if(gen_ht()>100) continue;
      }
      if(string(currentFile->GetTitle()).find("dy_m50_mgmlm_ext1_")!=string::npos){
	if(gen_ht()>100) continue;
      }
      if(string(currentFile->GetTitle()).find("www_2l_mia")!=string::npos)      weight *= 0.066805* 91900./(91900.+164800.);//(208fb/1pb)*BR(WWW—> >=2l)*combineweight
      if(string(currentFile->GetTitle()).find("www_2l_ext1_mia")!=string::npos) weight *= 0.066805*164800./(91900.+164800.);//(208fb/1pb)*BR(WWW—> >=2l)*combineweight
      if(weight>100) cout << weight << " " << currentFile->GetTitle() << endl;
      if(isData()) weight = 1.;
      double rawweight = weight;
      if(!isData()&&btagreweighting) weight *= weight_btagsf();
      float PUweight(1.), PUweightup(1.), PUweightdn(1.);
      if(applyPUrewgt&&!isData()){
	PUweight = getPUWeightAndError(PUweightdn,PUweightup);
	weight *= PUweight;
      }
      
      bool checkevent = false;
      for(unsigned int i = 0; i<e.size();++i){
	if(e[i].run!=tas::run() ) continue;
	if(e[i].ls !=tas::lumi()) continue;
	if(e[i].evt!=tas::evt() ) continue;
	checkevent = true;
	cout << "Check event " << tas::run() << ":" << tas::lumi() << ":" << tas::evt() << endl;
	break;
      }
      LorentzVector MET; MET.SetPxPyPzE(met_pt()*TMath::Cos(met_phi()),met_pt()*TMath::Sin(met_phi()),0,met_pt());
      LorentzVector MET_up; MET_up.SetPxPyPzE(met_T1CHS_miniAOD_CORE_up_pt()*TMath::Cos(met_T1CHS_miniAOD_CORE_up_phi()),met_T1CHS_miniAOD_CORE_up_pt()*TMath::Sin(met_T1CHS_miniAOD_CORE_up_phi()),0,met_T1CHS_miniAOD_CORE_up_pt());
      LorentzVector MET_dn; MET_dn.SetPxPyPzE(met_T1CHS_miniAOD_CORE_dn_pt()*TMath::Cos(met_T1CHS_miniAOD_CORE_dn_phi()),met_T1CHS_miniAOD_CORE_dn_pt()*TMath::Sin(met_T1CHS_miniAOD_CORE_dn_phi()),0,met_T1CHS_miniAOD_CORE_dn_pt());

      int nj(0), nb(0), nj30(0);
      getalljetnumbers(nj,nj30,nb);
      float Mjj = -1;
      float MjjL = -1; float Detajj = -1;
      getMjjAndDeta(Mjj,MjjL,Detajj);
      if(checkevent) cout << "nj30 " << nj30 << " nj " << nj << " nb " << nb << " Mjj " << Mjj << " MjjL " << MjjL << " Detajj " << Detajj << endl;
      if(checkevent){
	for(unsigned int i = 0; i<jets_p4().size(); ++i){
	  cout << "jet pT " << jets_p4()[i].Pt() << " eta " << jets_p4()[i].Eta() << " CSV " << jets_csv()[i];// << endl;
	  for(unsigned int j = i+1; j<jets_p4().size(); ++j) cout << " M"<<i<<j<< " " << (jets_p4()[i]+jets_p4()[j]).M() << " (dR " << dR(jets_p4()[i],jets_p4()[j]) << ")";
	  cout << endl;
	}
      }

      int nj_up(0), nb_up(0), nj30_up(0);
      if(getJECunc) getalljetnumbers(nj_up,nj30_up,nb_up,1);
      float Mjj_up = -1;
      float MjjL_up = -1; float Detajj_up = -1;
      if(getJECunc) getMjjAndDeta(Mjj_up,MjjL_up,Detajj_up,1);

      int nj_dn(0), nb_dn(0), nj30_dn(0);
      if(getJECunc) getalljetnumbers(nj_dn,nj30_dn,nb_dn,-1);
      float Mjj_dn = -1;
      float MjjL_dn = -1; float Detajj_dn = -1;
      if(getJECunc) getMjjAndDeta(Mjj_dn,MjjL_dn,Detajj_dn,-1);

      vector<int> vSS,   v3l,   iSS,   i3l; //lepton indices for both the SS and 3l signal regions
      vector<int> vaSS,  va3l,  iaSS,  ia3l;//loose, but not tight leptons.
      //getleptonindices_BDT(iSS, i3l, iaSS, ia3l, vSS, v3l, vaSS, va3l, 1, 0.85);
      //getleptonindices(iSS, i3l, iaSS, ia3l, vSS, v3l, vaSS, va3l,1,25,20);
      getleptonindices_v2(iSS, i3l, iaSS, ia3l, vSS, v3l, vaSS, va3l,25,20);
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
      float weight_lepSFup = weight;
      float weight_lepSFdn = weight;
      float weight_PUup    = weight;
      float weight_PUdn    = weight;
      float weight_bHFSFup = weight;
      float weight_bHFSFdn = weight;
      float weight_bLFSFup = weight;
      float weight_bLFSFdn = weight;
      if(!isData()&&btagreweighting&&weight_btagsf()!=0){
	weight_bHFSFup *= weight_btagsf_heavy_UP()/weight_btagsf();
	weight_bHFSFdn *= weight_btagsf_heavy_DN()/weight_btagsf();
	weight_bLFSFup *= weight_btagsf_light_UP()/weight_btagsf();
	weight_bLFSFdn *= weight_btagsf_light_DN()/weight_btagsf();
      }
      if(applyPUrewgt&&!isData()&&PUweight!=0){
	weight_PUup *= PUweightup/PUweight;
	weight_PUdn *= PUweightdn/PUweight;
      }
      if(applylepSF&&!isData()&&lepSF!=0){
	weight_lepSFup *= (lepSF+lepSFerr)/lepSF;
	weight_lepSFdn *= (lepSF-lepSFerr)/lepSF;
      }
      if(checkevent) cout << "weight " << weight << " btag  " << weight_btagsf() << " PU " << PUweight << " trig " << trigSF << " lep " << lepSF << endl;

      int nvetoSS = vSS.size();
      int nveto3l = v3l.size();
      int nSS = iSS.size();
      int n3l = i3l.size();
      int nvetoaSS = vaSS.size();
      int nvetoa3l = va3l.size();
      int naSS = iaSS.size();
      int na3l = ia3l.size();
      if(checkevent) cout << "nSS " << nSS << " n3l " << n3l << " naSS " << naSS << " na3l " << na3l << " nvetoaSS " << nvetoaSS << " nvetoa3l " << nvetoa3l << " ntracks " << nisoTrack_mt2_cleaned_VVV_cutbased_veto() << endl;
      if(checkevent){
	for(unsigned int i = 0; i<lep_pdgId().size();++i){
	  cout << "lep " << lep_pdgId()[i] << " Pt " << lep_p4()[i].Pt() << " eta " << lep_p4()[i].Eta() << " ID t/l/v/trig " << lep_pass_VVV_cutbased_tight_noiso()[i] << "/" << lep_pass_VVV_cutbased_fo_noiso()[i] << "/" << lep_pass_VVV_cutbased_veto_noiso()[i] << "/" << lep_isTriggerSafe_v1()[i] << " iso " << lep_relIso03EAv2()[i] << " ip3d " << lep_ip3d()[i] << " losthits " << lep_lostHits()[i] << " t.q " << lep_tightCharge()[i];
	  for(unsigned int j = i+1; j<lep_pdgId().size();++j) { cout << " M" << i << j << " " << (lep_p4()[i]+lep_p4()[j]).M();
	    for(unsigned int k = j+1; k<lep_pdgId().size();++k) cout << " M" << i << j << k << " " << (lep_p4()[i]+lep_p4()[j]+lep_p4()[k]).M() << " Pt " <<  (lep_p4()[i]+lep_p4()[j]+lep_p4()[k]).Pt() << " DPhiMET " << dPhi( (lep_p4()[i]+lep_p4()[j]+lep_p4()[k]),MET); }
	  cout << endl;
	}
      }
      
      if((n3l+na3l)<2) continue;
      bool passofflineforTrigger = passofflineTriggers(i3l, ia3l);
      if(!passofflineforTrigger) continue;
      if(checkevent) cout << "pass offline" << endl;
      
      if(isData()){
	if(!passFilters()) continue;
	if(checkevent) cout << "pass filter" << endl;
	duplicate_removal::DorkyEventIdentifier id(tas::run(), tas::evt(), tas::lumi());
	if( is_duplicate(id)        ) { continue; }
	if(checkevent) cout << "pass duplicate" << endl;
	if( !goodrun(tas::run(), tas::lumi()) ) continue;
	if(checkevent) cout << "pass goodrun" << endl;
	bool passonlineTrigger = passonlineTriggers(i3l, ia3l);//currently applied only to data
	if(!passonlineTrigger) continue;
      }
      if(checkevent) cout << "pass online" << endl;

      
      string sample   = skimFilePrefix;
      string sn       = ((iSS.size()+iaSS.size())>=2) ? process(fname,true ,iSS,iaSS) : string("not2l");
      string sn2      = ((i3l.size()+ia3l.size())>=3) ? process(fname,false,i3l,ia3l) : string("not3l");
      bool isphotonSS = (sn =="photonfakes");
      bool isphoton3l = (sn2=="photonfakes");
      if(splitVH(fname)){ sample = "WHtoWWW"; }


      float MTmax = -1;
      if(iSS.size()==2) MTmax = calcMTmax(iSS,MET);
      else if(iSS.size()==1&&iaSS.size()>=1){
	vector<int> temp; temp.push_back(iSS[0]); temp.push_back(iaSS[0]);
	MTmax = calcMTmax(temp,MET);
      }
      if(checkevent) cout << "MET " << MET.Pt() << " MTmax " << MTmax << " MTmax3l " << MTmax3l << endl;
      float MTmax_up(-1), MTmax_dn(-1), MTmax3l_up(-1), MTmax3l_dn(-1);
      if(getJECunc) {
	MTmax_up   = calcMTmax(iSS,MET_up);
	MTmax_dn   = calcMTmax(iSS,MET_dn);
      }
      
      int SRSS[20]; bool selects3l[20];
      int SR3l[20];
      for(int i = 0; i<20; ++i) { SRSS[i] = -1; SR3l[i] = -1; selects3l[i] = false; }

      //SS
      //0: SR
      SRSS[0] = isSRSS(iSS,      vSS,false,MTmax,  nj30,nb,Mjj,MjjL,Detajj);//enter variables for quicker calculation
      //1: SR preselect
      SRSS[1] = isSRSS(iSS,      vSS,true ,MTmax,  nj30,nb,Mjj,MjjL,Detajj);//enter variables for quicker calculation
      //2: AR
      SRSS[2] = isARSS(iSS,iaSS,vaSS,false,MTmax,  nj30,nb,Mjj,MjjL,Detajj);//enter variables for quicker calculation
      //3: AR preselect
      SRSS[3] = isARSS(iSS,iaSS,vaSS,true ,MTmax,  nj30,nb,Mjj,MjjL,Detajj);//enter variables for quicker calculation
      //4: CR
      SRSS[4] = isCRSS(iSS,i3l,  v3l,false,-1,nj30,nb,Mjj,MjjL,Detajj);//enter variables for quicker calculation
      //5: CR preselect
      SRSS[5] = isCRSS(iSS,i3l,  v3l,true ,-1,nj30,nb,Mjj,MjjL,Detajj);//enter variables for quicker calculation
      //6: SR JEC up
      if(getJECunc) SRSS[6] = isSRSS(iSS, vSS,false,MTmax_up, nj30_up,nb_up,Mjj_up,MjjL_up,Detajj_up,MET_up,1);
      //7: SR JEC dn
      if(getJECunc) SRSS[7]= isSRSS(iSS, vSS,false,MTmax_dn, nj30_dn,nb_dn,Mjj_dn,MjjL_dn,Detajj_dn,MET_dn,-1);
      selects3l[4] = true; selects3l[5] = true;
      //3l
      //0: SR, 4: CR
      checkbothSRCR3l(SR3l[0],SR3l[4],i3l,false,nj,nb);
      //1: SR preselect, 5: CR preselect
      checkbothSRCR3l(SR3l[1],SR3l[5],i3l,true ,nj,nb);
      //2: AR
      SR3l[2] = isAR3l(i3l,ia3l,false,nj,nb);
      //3: AR preselect
      SR3l[3] = isAR3l(i3l,ia3l,true ,nj,nb);
      //6: SR JEC up
      if(getJECunc) SR3l[6] = isSR3l(i3l,false,nj_up,nb_up,MET_up,1);
      //7: SR JEC dn
      if(getJECunc) SR3l[7] = isSR3l(i3l,false,nj_dn,nb_dn,MET_dn,-1);

      
      //10: SR
      SRSS[10] = isSRSS(iSS,      vSS,false,MTmax,  nj30,nb,Mjj,MjjL,Detajj,MET,0,false,false,1);//enter variables for quicker calculation
      //11: SR preselect
      SRSS[11] = isSRSS(iSS,      vSS,true ,MTmax,  nj30,nb,Mjj,MjjL,Detajj,MET,0,false,false,1);//enter variables for quicker calculation
      //12: AR
      SRSS[12] = isARSS(iSS,iaSS,vaSS,false,MTmax,  nj30,nb,Mjj,MjjL,Detajj,MET,0,false,false,1);//enter variables for quicker calculation
      //13: AR preselect
      SRSS[13] = isARSS(iSS,iaSS,vaSS,true ,MTmax,  nj30,nb,Mjj,MjjL,Detajj,MET,0,false,false,1);//enter variables for quicker calculation
      //14: CR
      SRSS[14] = isCRSS(iSS,i3l,  v3l,false,-1,nj30,nb,Mjj,MjjL,Detajj,MET,0,false,false,false,1);//enter variables for quicker calculation
      //15: CR preselect
      SRSS[15] = isCRSS(iSS,i3l,  v3l,true ,-1,nj30,nb,Mjj,MjjL,Detajj,MET,0,false,false,false,1);//enter variables for quicker calculation
      //10: SR, 14: CR
      checkbothSRCR3l(SR3l[10],SR3l[14],i3l,false,nj,nb,MET,0,false,1);
      //11: SR preselect, 15: CR preselect
      checkbothSRCR3l(SR3l[11],SR3l[15],i3l,true ,nj,nb,MET,0,false,1);
      //12: AR
      SR3l[12] = isAR3l(i3l,ia3l,false,nj,nb,MET,0,false,1);
      //13: AR preselect
      SR3l[13] = isAR3l(i3l,ia3l,true ,nj,nb,MET,0,false,1);
      
      if(!isData()||!blindSR){//SR is blinded
	fillSRhisto(histos, "SignalRegionPrecleaning",            sample, sn, sn2, SRSS[0], SR3l[0], weight, weight);
	fillSRhisto(histos, "SignalRegionPreselPrecleaning",      sample, sn, sn2, SRSS[1], SR3l[1], weight, weight);
      }
      fillSRhisto(  histos, "ApplicationRegionPrecleaning",       sample, sn, sn2, SRSS[2], SR3l[2], weight, weight);
      fillSRhisto(  histos, "ApplicationRegionPreselPrecleaning", sample, sn, sn2, SRSS[3], SR3l[3], weight, weight);
      fillSRhisto(  histos, "WZControlRegionPrecleaning",         sample, sn2,sn2, SRSS[4], SR3l[4], weight, weight);
      fillSRhisto(  histos, "WZControlRegionPreselPrecleaning",   sample, sn2,sn2, SRSS[5], SR3l[5], weight, weight);


      if(checkevent) cout << "passed       SRSS " << SRSS[0] << " SR3l " << SR3l[0] << " ARSS " << SRSS[2] << " AR3l " << SR3l[2] << " CRSS " << SRSS[4] << " CR3l " << SR3l[4] << endl;
      for(int i = 0; i<20; ++i) {
	if(!selects3l[i]){
	  if(vetophotonprocess(fname,isphotonSS))    { SRSS[i] = -1; }
	}
	else if(vetophotonprocess(fname,isphoton3l)){ SRSS[i] = -1; }
	if(vetophotonprocess(fname,isphoton3l))     { SR3l[i] = -1; }
      }
      if(checkevent) cout << "photonpassed SRSS " << SRSS[0] << " SR3l " << SR3l[0] << " ARSS " << SRSS[2] << " AR3l " << SR3l[2] << " CRSS " << SRSS[4] << " CR3l " << SR3l[4] << endl;

      if(!isData()||!blindSR){//SR is blinded
	fillSRhisto(histos, "SignalRegion",               sample, sn, sn2, SRSS[0], SR3l[0], weight, weight);
	fillSRhisto(histos, "SignalRegionPresel",         sample, sn, sn2, SRSS[1], SR3l[1], weight, weight);
	fillSRhisto(histos, "SignalRegion_JECup",         sample, sn, sn2, SRSS[6], SR3l[6], weight,         weight);
	fillSRhisto(histos, "SignalRegion_JECdn",         sample, sn, sn2, SRSS[7], SR3l[7], weight,         weight);
	fillSRhisto(histos, "SignalRegion_lepSFup",       sample, sn, sn2, SRSS[0], SR3l[0], weight_lepSFup, weight_lepSFup);
	fillSRhisto(histos, "SignalRegion_lepSFdn",       sample, sn, sn2, SRSS[0], SR3l[0], weight_lepSFdn, weight_lepSFdn);
	fillSRhisto(histos, "SignalRegion_bHFSFup",       sample, sn, sn2, SRSS[0], SR3l[0], weight_bHFSFup, weight_bHFSFup);
	fillSRhisto(histos, "SignalRegion_bHFSFdn",       sample, sn, sn2, SRSS[0], SR3l[0], weight_bHFSFdn, weight_bHFSFdn);
	fillSRhisto(histos, "SignalRegion_bLFSFup",       sample, sn, sn2, SRSS[0], SR3l[0], weight_bLFSFup, weight_bLFSFup);
	fillSRhisto(histos, "SignalRegion_bLFSFdn",       sample, sn, sn2, SRSS[0], SR3l[0], weight_bLFSFdn, weight_bLFSFdn);
	fillSRhisto(histos, "SignalRegion_PUup",          sample, sn, sn2, SRSS[0], SR3l[0], weight_PUup,    weight_PUup);
	fillSRhisto(histos, "SignalRegion_PUdn",          sample, sn, sn2, SRSS[0], SR3l[0], weight_PUdn,    weight_PUdn);

	fillSRhisto(histos, "SignalRegionNew",            sample, sn, sn2, SRSS[10], SR3l[10], weight, weight);
	fillSRhisto(histos, "SignalRegionPreselNew",      sample, sn, sn2, SRSS[11], SR3l[11], weight, weight);	
      }
      fillSRhisto(  histos, "ApplicationRegion",          sample, sn, sn2, SRSS[2], SR3l[2], weight, weight);
      fillSRhisto(  histos, "ApplicationRegionPresel",    sample, sn, sn2, SRSS[3], SR3l[3], weight, weight);
      fillSRhisto(  histos, "WZControlRegion",            sample, sn2,sn2, SRSS[4], SR3l[4], weight, weight);
      fillSRhisto(  histos, "WZControlRegionPresel",      sample, sn2,sn2, SRSS[5], SR3l[5], weight, weight);
      
      fillSRhisto(  histos, "ApplicationRegionNew",       sample, sn, sn2, SRSS[12], SR3l[12], weight, weight);
      fillSRhisto(  histos, "ApplicationRegionPreselNew", sample, sn, sn2, SRSS[13], SR3l[13], weight, weight);
      fillSRhisto(  histos, "WZControlRegionNew",         sample, sn2,sn2, SRSS[14], SR3l[14], weight, weight);
      fillSRhisto(  histos, "WZControlRegionPreselNew",   sample, sn2,sn2, SRSS[15], SR3l[15], weight, weight);

      if(!isData()||!blindSR){//SR is blinded
	fillSRhisto(histos, "RawSignalRegion",            sample, sn, sn2, SRSS[0], SR3l[0], 1., 1.);
	fillSRhisto(histos, "RawSignalRegionPresel",      sample, sn, sn2, SRSS[1], SR3l[1], 1., 1.);
      }
      fillSRhisto(  histos, "RawApplicationRegion",       sample, sn, sn2, SRSS[2], SR3l[2], 1., 1.);
      fillSRhisto(  histos, "RawApplicationRegionPresel", sample, sn, sn2, SRSS[3], SR3l[3], 1., 1.);
      fillSRhisto(  histos, "RawWZControlRegion",         sample, sn2,sn2, SRSS[4], SR3l[4], 1., 1.);
      fillSRhisto(  histos, "RawWZControlRegionPresel",   sample, sn2,sn2, SRSS[5], SR3l[5], 1., 1.);

      if(storeeventnumbers){
	addeventtolist(SRSS[0], SR3l[0], SREE, SREM, SRMM, SR0SFOS, SR1SFOS, SR2SFOS);
	addeventtolist(SRSS[2], SR3l[2], AREE, AREM, ARMM, AR0SFOS, AR1SFOS, AR2SFOS);
	addeventtolist(SRSS[4], SR3l[4], CREE, CREM, CRMM, CR0SFOS, CR1SFOS, CR2SFOS);
	//addeventtolist(SRSS[1], SR3l[1], SREE, SREM, SRMM, SR0SFOS, SR1SFOS, SR2SFOS);
	//addeventtolist(SRSS[3], SR3l[3], AREE, AREM, ARMM, AR0SFOS, AR1SFOS, AR2SFOS);
	//addeventtolist(SRSS[5], SR3l[5], CREE, CREM, CRMM, CR0SFOS, CR1SFOS, CR2SFOS);
      }
      if(checkevent) cout << endl;
      
    }//event loop
  
    // Clean Up
    delete tree;
    file->Close();
    delete file;
  }//file loop
  if ( nEventsChain != nEventsTotal ) {
    cout << Form( "ERROR: number of events from files (%d) is not equal to total number of events (%d)", nEventsChain, nEventsTotal ) << endl;
  }
  if(storeeventnumbers){
    storeeventlist("data/SR", skimFilePrefix, SREE, SREM, SRMM, SR0SFOS, SR1SFOS, SR2SFOS);
    storeeventlist("data/AR", skimFilePrefix, AREE, AREM, ARMM, AR0SFOS, AR1SFOS, AR2SFOS);
    storeeventlist("data/CR", skimFilePrefix, CREE, CREM, CRMM, CR0SFOS, CR1SFOS, CR2SFOS);
  }
  
  SaveHistosToFile("rootfiles/SRLooper.root",histos,true,true,(chainnumber==0));
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
