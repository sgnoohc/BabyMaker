#ifndef babyMaker_h
#define babyMaker_h

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
#include "rooutil/fileutil.h"
#include "rooutil/calc.h"

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
#include "coreutil/sample.h"

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

class babyMaker
{

public:

    enum BabyMode
    {
         kHWWBaby = 0
    };

private:

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
    CoreUtil::sample coreSample;

    TFile* ofile;
    TTree* t;
    TH1F* h_neventsinfile;
    RooUtil::TTreeX* tx;
    RooUtil::Looper<CMS3> looper;

    std::string filename;

    // BabyMode
    BabyMode babymode;

    // Job
    int job_index;

public:

    babyMaker();
    ~babyMaker();

    void SetBabyMode(BabyMode bm) { babymode = bm; }
    int ProcessCMS4(TString filepaths, int max_events = -1, int index = 1, bool verbose = false);

private:
    void ScanChain(bool verbose = false);
    void Init();
    void SetYear();
    void CreateOutput();
    void AddOutput();
    void AddBabyOutput();
    void AddHWWBabyOutput();
    void SetLeptonID();
    void SetHWWAnalysisLeptonID();

    void Process();
    void FillGenWeights();
    void FillGenWeightsNominal();
    void ProcessLeptons();
    void ProcessElectrons();
    void ProcessHWWElectrons();
    void ProcessMuons();
    void ProcessHWWMuons();

    bool PassSelection();
    bool PassHWWPreselection();

    void ProcessObjectsPrePassSelection();
    void ProcessObjectsPostPassSelection();
    void ProcessTriggers();
    void ProcessGenParticles();
    void ProcessJets();
    void ProcessFatJets();
    void ProcessMET();
    void ProcessTracks();

    void FillBaby();
    void FillHWWBaby();
    void FillTTree();

    void SaveOutput();
    void SaveHWWBaby();

    // Tools
    static bool isPt10Electron(int);
    static bool isPt10Muon(int);
    static int passCount(const vector<int>& vec);
    static void sortVecP4(std::vector<LV>& p4s);
    void FATALERROR(const char* funcname="");
    bool isLeptonOverlappingWithJet(int ijet);

    // Sample handling
    TString SampleNiceName() { return coreSample.nicename(looper.getCurrentFileName()); }
    bool isHWWlvjj(){ return looper.getCurrentFileName().Contains("HToWWToLNuQQ"); }
    bool isHbb() { return looper.getCurrentFileName().Contains("GluGluHToBB"); }
    bool isFastSim() { return false; }

    //
    // Processor units
    //

    // --- Event Info Processor Unit ---
    void AddEventInfoOutput();
    void FillEventInfo();

    // --- Lepton Processor Unit ---
    void AddLeptonOutput();
    void FillLepton();

    // --- Jet Processor Unit ---
    void AddJetOutput();
    void FillJet();

    // --- MET Processor Unit ---
    void AddMETOutput();
    void FillMET();

    // --- Gen to Reco Processor Unit ---
    void AddGenVariablesOutput();
    void FillGenVariables();

    // --- Gen to Reco Processor Unit ---
    void AddGenRecoMatchingOutput();
    void FillGenRecoMatching();

    // --- Higgs Mass Reco Processor Unit ---
    void AddHiggsMassRecoOutput();
    void FillHiggsMassReco();

    // --- Reconstructing ISR vector ---
    void AddRecoISROutput();
    void FillRecoISR();

    // --- Reconstructing Whad vector ---
    void AddRecoWhadOutput();
    void FillRecoWhad();

    // --- Reconstructing Wlep vector ---
    void AddRecoWlepOutput();
    void FillRecoWlep();

    // --- Reconstructing lepton vector ---
    void AddRecoLeptonOutput();
    void FillRecoLepton();

    // --- Reconstructing leading AK4 jet ---
    void AddRecoLeadJetOutput();
    void FillRecoLeadJet();

    // --- Combination variables ---
    void AddRecoVariablesOutput();
    void FillRecoVariables();

    // --- Eta-Phi plane PF deposits variables ---
    void AddEtaPhiPlaneVariablesOutput();
    void FillEtaPhiPlaneVariables();

    // --- DeepIso inputs
    void AddDeepIsoVariablesOutput();
    void FillDeepIsoVariables();

    // --- Isolated Lepton Trigger Processor Unit ---
    void AddIsolatedSingleLeptonTriggerOutput();
    void FillIsolatedSingleLeptonTrigger();

    // --- High Pt Single Lepton Trigger Processor Unit ---
    void AddHighPtSingleLeptonTriggerOutput();
    void FillHighPtSingleLeptonTrigger();

    // --- Overlap removed B-veto variables ---
    void AddOverlapRemovedBvetoOutput();
    void FillOverlapRemovedBveto();

    // --- Higgs Truth Study Processor Unit ---
    void AddHiggsTruthStudyOutput();
    void FillTruthLevelStudyVariables();
    bool FillTruthLevelStudyVariables_HWWlvjj();
    bool FillTruthLevelStudyVariables_Hbb();
    std::tuple<std::vector<LV>, std::vector<float>, std::vector<float>, std::vector<float>, std::vector<float>, std::vector<float>, float, float> getReBoostedDRDEtaDPhi(int ptBoost, const LV& higgs_p4, const vector<LV>& higgsdecay_p4, float ref_deta=-999, float ref_dphi=-999);
    std::tuple<float, float> FillReBoostedVariables(TString bname, int ptBoost, const LV& higgs_p4, const vector<LV>& decay_p4, const vector<int>& decay_id, const vector<int>& decay_isstar, float ref_deta=-999, float ref_dphi=-999);
    void FillDecayProductsDRVariables(int pt);
};


#endif
