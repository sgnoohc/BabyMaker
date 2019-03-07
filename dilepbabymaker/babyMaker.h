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
#include "rooutil/module.h"

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

    CoreUtil::jec coreJec;
    CoreUtil::jec coreFatJec;
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

    // Job
    int job_index;

    babyMaker();
    virtual ~babyMaker();

    int ProcessCMS4(TString filepaths, int max_events = -1, int index = 1, bool verbose = false);

    void ScanChain(bool verbose = false);
    void Init();
    void SetYear();
    void CreateOutput();
    virtual void AddOutput();
    void SetLeptonID();

    void Process();
    void FillGenWeights();
    void FillGenWeightsNominal();
    void ProcessLeptons();
    virtual void ProcessElectrons();
    virtual void ProcessMuons();

    virtual bool PassSelection();

    virtual void ProcessObjectsPrePassSelection();
    virtual void ProcessObjectsPostPassSelection();
    void ProcessTriggers();
    void ProcessGenParticles();
    void ProcessJets();
    void ProcessFatJets();
    void ProcessMET();
    void ProcessTracks();

    virtual void FillOutput();
    virtual void FillEventInfo();

    void SaveOutput();

    // Tools
    static void sortVecP4(std::vector<LV>& p4s);
    void FATALERROR(const char* funcname="");

    // Sample handling
    TString SampleNiceName() { return coreSample.nicename(looper.getCurrentFileName()); }

    //
    // Processor units
    //

};


#endif
