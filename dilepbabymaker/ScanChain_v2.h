#ifndef ScanChain_h
#define ScanChain_h

// C++
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <vector>

// ROOT
#include "TChain.h"
#include "TDirectory.h"
#include "TTreeCache.h"
#include "Math/VectorUtil.h"
#include "TVector2.h"
#include "TBenchmark.h"
#include "TLorentzVector.h"
#include "TH2.h"
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

// RooUtil
#include "rooutil/looper.h"

// CoreUtil
#include "coreutil/jec.h"

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
    const char* json_file;
    CoreUtil::jec coreJec;

    bool isData;

    bool HLT_DoubleMu;
    bool HLT_MuEG;
    bool HLT_DoubleEl;
    bool HLT_DoubleEl_DZ;

public:

    babyMaker_v2() {}
    ~babyMaker_v2() {}
    void ScanChain_v2(TChain*, std::string = "testSample", int max_events = -1);
    void Configure();
    void ConfigureElectronMVA();
    void ConfigureMuonMVA();
    void ConfigurePileUpReweighting();
    void ConfigureGoodRunsList();
    void ConfigureBtagging();
    void ConfigureJEC();
};


#endif
