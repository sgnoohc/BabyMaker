#include "hwwBabyMaker.h"

// #define USE_LEAD_JET_SCHEME

//##############################################################################################################
hwwBabyMaker::hwwBabyMaker() : processor(0)
{
    recl.babyMaker = this;
}

hwwBabyMaker::~hwwBabyMaker() {}

//##############################################################################################################
void hwwBabyMaker::ProcessObjectsPrePassSelection()
{
    // Process leptons via CoreUtil
    ProcessLeptons();

    // ReClusterFatJets
    ReClusterFatJets();

    // Process MET (recalculate etc.)
    ProcessMET();

}

//##############################################################################################################
void hwwBabyMaker::ProcessObjectsPostPassSelection()
{

    // Fat jet
    ProcessFatJets();

    // Triggers
    ProcessTriggers();

    // Loop over gen particles
    ProcessGenParticles();

    // Loop over Jets
    ProcessJets();

    // Loop over charged particle candidates
    ProcessTracks();

}

//##############################################################################################################
void hwwBabyMaker::ReClusterFatJets()
{

    // If not a single lepton event forget about it
    if (coreElectron.index.size() + coreMuon.index.size() != 1)
    {
        // If we are going to skip, be sure to not use the old found_jet variable
        recl.found_jet = false;
        return;
    }

    // Access the one and only one lepton that I have
    recl.L_p4 =
        coreElectron.index.size() > 0 ?
        cms3.els_p4()[coreElectron.index[0]] :
        coreMuon.index.size() > 0 ?
        cms3.mus_p4()[coreMuon.index[0]] : LV();

    // Get the pdgid
    if (coreElectron.index.size() > 0)
        recl.pdgid = cms3.els_charge()[coreElectron.index[0]]*(-11);
    else if (coreMuon.index.size() > 0)
        recl.pdgid = cms3.mus_charge()[coreMuon.index[0]]*(-13);

    if (recl.L_p4.pt() == 0)
    {
        std::cout << "I should have found a lepton but it doesn't seem like I found one." << std::endl;
        FATALERROR(__FUNCTION__);
    }

    // Re-clustered jets and put together the information for the fat jets
    recl.ReClusterFatJets();
}



//##############################################################################################################
void hwwBabyMaker::ProcessElectrons()
{
    coreElectron.process(isPt25Electron);
}

//##############################################################################################################
void hwwBabyMaker::ProcessMuons()
{
    coreMuon.process(isPt25Muon);
}

//##############################################################################################################
// Goal is to pass events with at least one fat jet and one lepton
bool hwwBabyMaker::PassSelection()
{
    // lepton counter
    int n_reconstructed_leptons = coreElectron.index.size() + coreMuon.index.size();

    // Pass with at least one fat jet and only one lepton
    if (n_reconstructed_leptons != 1) return false;
    if (not recl.found_jet) return false;

    // Check that the lepton + met + (lepton subtracted) fat-jet has pt > 200 GeV
    LV X_p4 = RooUtil::Calc::getLV(coreMET.met_pt, 0, coreMET.met_phi, 0);
    if ((recl.J_p4 + recl.L_p4 + X_p4).pt() < 200) return false;

    return true;

}

//##############################################################################################################
void hwwBabyMaker::AddOutput()
{

    // initialize the processor connected to the main output TTreeX=tx.
    processor = new RooUtil::Processor(tx);

    // Add the lepton module which handles what variables to write, and how.
    processor->AddModule(new hwwModule::TriggerModule(this));
    processor->AddModule(new hwwModule::GenPartModule(this));
    processor->AddModule(new hwwModule::EventModule(this));
    processor->AddModule(new hwwModule::LeptonModule(this));
    processor->AddModule(new hwwModule::METModule(this));
    processor->AddModule(new hwwModule::FatJetModule(this));
    processor->AddModule(new hwwModule::HiggsRecoModule(this));
    processor->AddModule(new hwwModule::JetModule(this));
    processor->AddModule(new hwwModule::HWWlvjjTruthModule(this));
    processor->AddModule(new hwwModule::TTBarModule(this));

    // Now create the outputs to the ttree
    processor->AddOutputs();

}

//##############################################################################################################
void hwwBabyMaker::FillOutput()
{
    processor->FillOutputs();
}

//##############################################################################################################
// Used to overlap remova against tracks
bool hwwBabyMaker::isPt25Electron(int idx)
{
    if (!( cms3.els_p4()[idx].pt() > 25.          )) return false;
    if (!( isPt10Electron(idx)                    )) return false;
    return true;
}

//##############################################################################################################
// Used to overlap remova against tracks
bool hwwBabyMaker::isPt25Muon(int idx)
{
    if (!( cms3.mus_p4()[idx].pt() > 25.        )) return false;
    if (!( isPt10Muon(idx)                      )) return false;
    return true;
}

//##############################################################################################################
// Used to overlap remova against tracks
bool hwwBabyMaker::isPt10Electron(int idx)
{
    if (!( cms3.els_p4()[idx].pt() > 10.          )) return false;
    if (!( isVetoElectronPOGspring16noIso_v1(idx) )) return false;
    if (!( fabs(cms3.els_p4()[idx].eta()) < 2.5   )) return false;
    if (!( elMiniRelIsoCMS3_EA(idx, 2) < 0.2      )) return false;
    if (!( fabs(cms3.els_dzPV()[idx]) < 0.1       )) return false;
    if (!( fabs(cms3.els_dxyPV()[idx]) < 0.05     )) return false;
    return true;
}

//##############################################################################################################
// Used to overlap remova against tracks
bool hwwBabyMaker::isPt10Muon(int idx)
{
    if (!( cms3.mus_p4()[idx].pt() > 10.        )) return false;
    if (!( isLooseMuonPOG(idx)                  )) return false;
    if (!( fabs(cms3.mus_p4()[idx].eta()) < 2.5 )) return false;
    if (!( muMiniRelIsoCMS3_EA(idx, 2) < 0.2    )) return false;
    if (!( fabs(cms3.mus_dzPV()[idx]) < 0.1     )) return false;
    if (!( fabs(cms3.mus_dxyPV()[idx]) < 0.05   )) return false;
    return true;
}

//##############################################################################################################
bool hwwBabyMaker::isLeptonOverlappingWithJet(int ijet)
{
    bool is_overlapping = false;
    int idx = coreJet.index[ijet];
    const LV& jet_p4 = cms3.pfjets_p4()[idx];

    for (unsigned ilep = 0; ilep < cms3.els_p4().size(); ++ilep)
    {
        const LV& p4 = cms3.els_p4()[ilep];
        if (!( isPt10Electron(ilep) )) continue;
        if (!( eleRelIso03EA(ilep, 2) < 0.4 )) continue;
        if (ROOT::Math::VectorUtil::DeltaR(jet_p4, p4) < 0.4)
        {
            is_overlapping = true;
            break;
        }
    }

    for (unsigned ilep = 0; ilep < cms3.mus_p4().size(); ++ilep)
    {
        const LV& p4 = cms3.mus_p4()[ilep];
        if (!( isPt10Muon(ilep) )) continue;
        if (!( muRelIso03EA(ilep, 2) < 0.4 )) continue;
        if (ROOT::Math::VectorUtil::DeltaR(jet_p4, p4) < 0.4)
        {
            is_overlapping = true;
            break;
        }
    }

    if (is_overlapping)
        return true;

    return false;
}
