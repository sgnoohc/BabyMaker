#include "TriggerModule.h"

//==============================================================================================================
//
// Trigger Module
//
//==============================================================================================================

void hwwModule::TriggerModule::AddOutput()
{
    // Triggers

    // Electron
    tx->createBranch<int>("HLT_Ele27_WPLoose_Gsf");
    tx->createBranch<int>("HLT_Ele30_WPLoose_Gsf");
    tx->createBranch<int>("HLT_Ele45_WPLoose_Gsf");
    tx->createBranch<int>("HLT_Ele105_CaloIdVT_GsfTrkIdT");
    tx->createBranch<int>("HLT_Ele115_CaloIdVT_GsfTrkIdT");

    // Muon
    tx->createBranch<int>("HLT_IsoTkMu24");
    tx->createBranch<int>("HLT_IsoMu24");

    // Triggers
    tx->createBranch<int>("HLT_SingleMu50");
    tx->createBranch<int>("HLT_SingleEl40");
    tx->createBranch<int>("HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165");
    tx->createBranch<int>("HLT_Mu50");
    tx->createBranch<int>("HLT_TkMu50");
    tx->createBranch<int>("HLT_AK8PFHT700_TrimR0p1PT0p03Mass50");
    tx->createBranch<int>("HLT_AK8PFJet360_TrimMass30");
    tx->createBranch<int>("HLT_PFHT800");
    tx->createBranch<int>("HLT_PFHT900");
    tx->createBranch<int>("HLT_PFHT650_WideJetMJJ900DEtaJJ1p5");
    tx->createBranch<int>("HLT_PFHT650_WideJetMJJ950DEtaJJ1p5");
    tx->createBranch<int>("HLT_AK8PFDiJet280_200_TrimMass30_CSVM_0p20");

    // duplicate removal bits
    tx->createBranch<int>("pass_duplicate_se_sm");
    tx->createBranch<int>("pass_duplicate_sm_se");
}

void hwwModule::TriggerModule::FillOutput()
{
    tx->setBranch<int>("HLT_Ele27_WPLoose_Gsf", passHLTTriggerPattern("HLT_Ele27_WPLoose_Gsf_v"));
    tx->setBranch<int>("HLT_Ele30_WPLoose_Gsf", passHLTTriggerPattern("HLT_Ele30_WPLoose_Gsf_v"));
    tx->setBranch<int>("HLT_Ele45_WPLoose_Gsf", passHLTTriggerPattern("HLT_Ele45_WPLoose_Gsf_v"));
    tx->setBranch<int>("HLT_Ele105_CaloIdVT_GsfTrkIdT", passHLTTriggerPattern("HLT_Ele105_CaloIdVT_GsfTrkIdT_v"));
    tx->setBranch<int>("HLT_Ele115_CaloIdVT_GsfTrkIdT", passHLTTriggerPattern("HLT_Ele115_CaloIdVT_GsfTrkIdT_v"));

    // Muon
    tx->setBranch<int>("HLT_IsoTkMu24", passHLTTriggerPattern("HLT_IsoTkMu24_v"));
    tx->setBranch<int>("HLT_IsoMu24", passHLTTriggerPattern("HLT_IsoMu24_v"));

    // Triggers
    int HLT_Ele40_WPTight_Gsf                      = passHLTTriggerPattern("HLT_Ele40_WPTight_Gsf_v");
    int HLT_Mu50                                   = passHLTTriggerPattern("HLT_Mu50_v");
    int HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165      = passHLTTriggerPattern("HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165_v");
    int HLT_TkMu50                                 = passHLTTriggerPattern("HLT_TkMu50_v");
    int HLT_AK8PFHT700_TrimR0p1PT0p03Mass50        = passHLTTriggerPattern("HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v");
    int HLT_AK8PFJet360_TrimMass30                 = passHLTTriggerPattern("HLT_AK8PFJet360_TrimMass30_v");
    int HLT_PFHT800                                = passHLTTriggerPattern("HLT_PFHT800_v");
    int HLT_PFHT900                                = passHLTTriggerPattern("HLT_PFHT900_v");
    int HLT_PFHT650_WideJetMJJ900DEtaJJ1p5         = passHLTTriggerPattern("HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_v");
    int HLT_PFHT650_WideJetMJJ950DEtaJJ1p5         = passHLTTriggerPattern("HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_v");
    int HLT_AK8PFDiJet280_200_TrimMass30_CSVM_0p20 = passHLTTriggerPattern("HLT_AK8PFDiJet280_200_TrimMass30_CSVM_0p20_v");

    tx->setBranch<int>("HLT_SingleEl40"                             , HLT_Ele40_WPTight_Gsf);
    tx->setBranch<int>("HLT_SingleMu50"                             , HLT_Mu50);
    tx->setBranch<int>("HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165"      , HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165);
    tx->setBranch<int>("HLT_Mu50"                                   , HLT_Mu50);
    tx->setBranch<int>("HLT_TkMu50"                                 , HLT_TkMu50);
    tx->setBranch<int>("HLT_AK8PFHT700_TrimR0p1PT0p03Mass50"        , HLT_AK8PFHT700_TrimR0p1PT0p03Mass50);
    tx->setBranch<int>("HLT_AK8PFJet360_TrimMass30"                 , HLT_AK8PFJet360_TrimMass30);
    tx->setBranch<int>("HLT_PFHT800"                                , HLT_PFHT800);
    tx->setBranch<int>("HLT_PFHT900"                                , HLT_PFHT900);
    tx->setBranch<int>("HLT_PFHT650_WideJetMJJ900DEtaJJ1p5"         , HLT_PFHT650_WideJetMJJ900DEtaJJ1p5);
    tx->setBranch<int>("HLT_PFHT650_WideJetMJJ950DEtaJJ1p5"         , HLT_PFHT650_WideJetMJJ950DEtaJJ1p5);
    tx->setBranch<int>("HLT_AK8PFDiJet280_200_TrimMass30_CSVM_0p20" , HLT_AK8PFDiJet280_200_TrimMass30_CSVM_0p20);

    int pass_duplicate_se_sm = 0;
    int pass_duplicate_sm_se = 0;
    tx->setBranch<int>("pass_duplicate_se_sm", pass_duplicate_se_sm);
    tx->setBranch<int>("pass_duplicate_sm_se", pass_duplicate_sm_se);
}
