#ifndef ScanChain_v2_h
#define ScanChain_v2_h

// C++
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <mutex>
#include <algorithm>

// ROOT
#include "TChain.h"
#include "TDirectory.h"
#include "TTreeCache.h"
#include "Math/VectorUtil.h"
#include "TVector2.h"
#include "TBenchmark.h"
#include "TLorentzVector.h"
#include "TH2.h"
#include "TH3.h"
#include "TROOT.h"
#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TH2.h"
#include "TString.h"
#include "TMVA/Reader.h"
#include "Math/LorentzVector.h"
#include "Math/GenVector/LorentzVector.h"

// CORE
#include "../CORE/CMS3.h"
#include "../CORE/Base.h"
#include "../CORE/OSSelections.h"
#include "../CORE/SSSelections.h"
#include "../CORE/VVVSelections.h"
#include "../CORE/ElectronSelections.h"
#include "../CORE/IsolationTools.h"
#include "../CORE/JetSelections.h"
#include "../CORE/MuonSelections.h"
#include "../CORE/IsoTrackVeto.h"
#include "../CORE/PhotonSelections.h"
#include "../CORE/TriggerSelections.h"
#include "../CORE/VertexSelections.h"
#include "../CORE/MCSelections.h"
#include "../CORE/MetSelections.h"
#include "../CORE/SimPa.h"
//#include "../CORE/Tools/jetcorr/FactorizedJetCorrector.h"
//#include "../CORE/Tools/JetCorrector.h"
//#include "../CORE/Tools/jetcorr/JetCorrectionUncertainty.h"
#include "../CORE/Tools/MT2/MT2.h"
#include "../CORE/Tools/hemJet.h"
#include "../CORE/Tools/utils.h"
#include "../CORE/Tools/goodrun.h"
#include "../CORE/Tools/btagsf/BTagCalibrationStandalone.h"
#include "../CORE/Tools/btagsf/BTagCalibrationStandalone.h"
#include "../CORE/Tools/datasetinfo/getDatasetInfo.h"

// RooUtil
#include "rooutil/looper.h"
#include "rooutil/ttreex.h"
#include "rooutil/printutil.h"

// CoreUtil
#include "coreutil/jec.h"
#include "coreutil/btag.h"
#include "coreutil/puwgt.h"
#include "coreutil/genpart.h"
#include "coreutil/trigger.h"
#include "coreutil/electron.h"
#include "coreutil/muon.h"
#include "coreutil/grl.h"
#include "coreutil/datasetinfo.h"
#include "coreutil/jet.h"
#include "coreutil/met.h"
#include "coreutil/track.h"
#include "coreutil/fatjet.h"

#define VVV_TIGHT_SS VVV_cutbased_tight_v4
#define VVV_TIGHT_3L VVV_cutbased_3l_tight_v4
#define VVV_TIGHT_NOISO VVV_cutbased_tight_noiso_v4

#define VVV_FO_SS VVV_cutbased_fo_v4
#define VVV_FO_3L VVV_cutbased_3l_fo_v4
#define VVV_FO_NOISO VVV_cutbased_fo_noiso_v4

#define VVV_VETO VVV_cutbased_veto_v4
#define VVV_VETO_NOISO VVV_cutbased_veto_noiso_v4


typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

// `````````````````````````````````````````````````````````````````````````````````````````````````````````````
//
//
//
// Baby Maker Class
//
//
//
// ,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

class babyMaker_v2
{

private:

    SimPa simpa;
    CoreUtil::jec coreJec;
    CoreUtil::grl coreGRL;
    CoreUtil::btag coreBtagSF;
    CoreUtil::btag coreBtagSFFastSim;
    CoreUtil::puwgt corePUWgt;
    CoreUtil::trigger coreTrigger;
    CoreUtil::genpart coreGenPart;
    CoreUtil::electron coreElectron;
    CoreUtil::muon coreMuon;
    CoreUtil::datasetinfo coreDatasetInfo;
    CoreUtil::jet coreJet;
    CoreUtil::fatjet coreFatJet;
    CoreUtil::met coreMET;
    CoreUtil::track coreTrack;

    TFile* ofile;
    TTree* t;
    TTree* t_os;
    TTree* t_ss;
    TTree* t_www;
    TTree* t_prompt;
    TTree* t_qflip;
    TTree* t_photon;
    TTree* t_lostlep;
    TTree* t_fakes;
    TH1F* h_neventsinfile;
    RooUtil::TTreeX* tx;
    RooUtil::Looper<CMS3> looper;

    std::string filename;

    TH3F* h_nevents_SMS;
    TH2F* h_nrawevents_SMS;
    TH1D* hxsec;
    TFile* fxsec;

public:

    babyMaker_v2();
    ~babyMaker_v2();
    void ScanChain_v2(TChain*, std::string = "testSample", int max_events = -1, int index = 1, bool verbose = false);

    void CreateOutput(int index=1);
    void CreateBSMSampleSpecificOutput();

    void SaveOutput();

    void ConfigureGoodRunsList();

    void SlaveBegin(int index=1);

    void ProcessTriggers();
    void ProcessGenParticles();
    void ProcessElectrons();
    void ProcessMuons();
    void ProcessJets();
    void ProcessFatJets();
    void ProcessMET();
    void ProcessTracks();

    bool PassPresel();
    bool PassPresel_v1();
    bool PassPresel_v2();
    bool PassPresel_v3();

    void FillOutput();

    void FillEventInfo();
    void FillElectrons();
    void FillMuons();
    void FillJets();
    void FillFatJets();
    void FillMET();
    void FillTracks();
    void FillGenParticles();
    void SortLeptonBranches();
    void SortJetBranches();
    void FillTrigger();
    void FillVertexInfo();
    void FillMETFilter();
    void FillSummaryVariables();
    void FillTTree();

    bool isLeptonOverlappingWithJet(int ijet);
    bool isLeptonOverlappingWithJet_OldVersion(int ijet);
    bool isLeptonOverlappingWithTrack(int ijet);
    static bool isLooseMuon(int);
    static bool isLooseElectron(int);
    static bool isVetoMuon(int);
    static bool isVetoElectron(int);
    static bool isVetoMuonNoIso_OldVersion(int);
    static bool isVetoElectronNoIso_OldVersion(int);

    // Fill variables
    void FillJetVariables(int variation);
    void FillLeptonVariables();
    void FillSSLeptonVariables(int, int);
    void Fill3LLeptonVariables();
    void FillEventTags();
    void FillWeights();
    void FillGenWeights();

    // Calculator
    static int passCount(const vector<int>& vec);
    int nSFOS();
    float get0SFOSMll();
    float get0SFOSMee();
    float get1SFOSMll();
    float get2SFOSMll0();
    float get2SFOSMll1();
    float calcMTmax(LorentzVector MET, bool compareSSpairs);
    float mT(LV p4, LV met);

    // Event tagging
    void setFilename(TString);
    TString process();
    bool splitVH();
    int gentype_v2();
    bool vetophotonprocess();
    tuple<bool, int, int> isSSCR();

    // special weights
    std::tuple<float, float, int> getlepFakeRateandErrorandLooseLepIdx(bool data, int version=2);
    std::tuple<float, float> getlepSFandError(int index, int lepton_id_version=2);
    std::tuple<float, float> getlepSFWeightandError(int lepton_id_version=2);
    static std::tuple<float, float> getCombinedTrigEffandError(float, float, float, float, float, float, float, float);
    std::tuple<float, float> getTrigEffandError(int lepton_id_version=2);
    std::tuple<float, float> getTrigSFandError(int lepton_id_version=2);

    void FATALERROR(const char* funcname="");

    // Truth level studies

    // WWW signal sample
    bool isSMWWW() { return filename.find("www_2l") != string::npos; }
    bool isVH()    { return filename.find("vh_nonbb") != string::npos; }
    bool isWHWWW() { return splitVH(); }
    bool isWWW() { return isSMWWW() || isWHWWW(); }
    void AddWWWOutput();
    bool studyWWW();

    // Doubly Charged Higgs process related
    bool isDoublyChargedHiggs() { return filename.find("hpmpm_hww") != string::npos; }
    void AddDoublyChargedHiggsOutput();
    bool studyDoublyChargedHiggs();

    // Wprime process related
    bool isWprime() { return filename.find("wprime") != string::npos; }
    void AddWprimeOutput();
    bool studyWprime();

    // WH susy process related
    bool isSMSFastSim() { return filename.find("whsusy") != string::npos; }
    bool isWHSUSY() { return filename.find("whsusy") != string::npos; }
    void AddWHsusyOutput();
    void setWHSMSMassAndWeights();
    void setWHSMSMass();
    bool filterWHMass(float, float);

    static void sortVecP4(std::vector<LV>& p4s);

};


#endif
