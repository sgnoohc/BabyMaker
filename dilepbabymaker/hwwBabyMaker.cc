#include "hwwBabyMaker.h"

//##############################################################################################################
hwwBabyMaker::hwwBabyMaker() : processor(0) {}
hwwBabyMaker::~hwwBabyMaker() {}

//##############################################################################################################
void hwwBabyMaker::ProcessObjectsPrePassSelection()
{
    // Process leptons via CoreUtil
    ProcessLeptons();

    // Loop over fatJets
    ProcessFatJets();
}

//##############################################################################################################
void hwwBabyMaker::ProcessObjectsPostPassSelection()
{
    // Triggers
    ProcessTriggers();

    // Loop over gen particles
    ProcessGenParticles();

    // Loop over Jets
    ProcessJets();

    // Process MET (recalculate etc.)
    ProcessMET();

    // Loop over charged particle candidates
    ProcessTracks();
}

//##############################################################################################################
void hwwBabyMaker::ProcessElectrons()
{
    coreElectron.process(isPt10Electron);
}

//##############################################################################################################
void hwwBabyMaker::ProcessMuons()
{
    coreMuon.process(isPt10Muon);
}

//##############################################################################################################
// Goal is to pass events with at least one fat jet and one lepton
bool hwwBabyMaker::PassSelection()
{

    // lepton counter
    int n_reconstructed_leptons = coreElectron.index.size() + coreMuon.index.size();

    // Fat jet counter
    int n_ak8 = 0;

    // Loop over fat jets and count the ones with minimum pt of 20 GeV
    for (unsigned ijet = 0; ijet < coreFatJet.index.size(); ++ijet)
    {
        int idx = coreFatJet.index[ijet];
        float corr = coreFatJet.corrs[ijet];
        LorentzVector fatjet = cms3.ak8jets_p4()[idx] * cms3.ak8jets_undoJEC()[idx] * corr;
        if (fatjet.pt() > 20)
        {
            n_ak8++;
        }
    }

    // Pass with at least one fat jet and at least one lepton
    if (n_ak8 >= 1 && n_reconstructed_leptons >= 1)
        return true;
    else
        return false;
}

//##############################################################################################################
void hwwBabyMaker::AddOutput()
{

    // initialize the processor connected to the main output TTreeX=tx.
    processor = new RooUtil::Processor(tx);

    // Add the lepton module which handles what variables to write, and how.
    processor->AddModule(new LeptonModule(this));
    processor->AddModule(new FatJetModule(this));

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
bool hwwBabyMaker::isPt10Electron(int idx)
{
    if (!( cms3.els_p4()[idx].pt() > 10.          )) return false;
    if (!( isVetoElectronPOGspring16noIso_v1(idx) )) return false;
    if (!( fabs(cms3.els_p4()[idx].eta()) < 2.5   )) return false;
//    if (!( eleRelIso03EA(idx, 2) > 0.1            )) return false;
//    if (!( elMiniRelIsoCMS3_EA(idx, 2) < 0.1      )) return false;
    return true;
}

//##############################################################################################################
// Used to overlap remova against tracks
bool hwwBabyMaker::isPt10Muon(int idx)
{
    if (!( cms3.mus_p4()[idx].pt() > 10.        )) return false;
    if (!( isLooseMuonPOG(idx)                  )) return false;
    if (!( fabs(cms3.mus_p4()[idx].eta()) < 2.5 )) return false;
//    if (!( muRelIso03EA(idx, 2) > 0.1           )) return false;
//    if (!( muMiniRelIsoCMS3_EA(idx, 2) < 0.1    )) return false;
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

//==============================================================================================================
//
// Lepton Module
//
//==============================================================================================================

//##############################################################################################################
void hwwBabyMaker::LeptonModule::AddOutput()
{
    tx->createBranch<vector<LV>>("lep_p4");
    tx->createBranch<vector<int>>("lep_id");
    tx->createBranch<vector<int>>("lep_idx");
    tx->createBranch<vector<float>>("lep_pt");
    tx->createBranch<vector<float>>("lep_eta");
    tx->createBranch<vector<float>>("lep_phi");
    tx->createBranch<vector<float>>("lep_miniIsoEA");
    tx->createBranch<vector<float>>("lep_relIso03EA");
    tx->createBranch<vector<float>>("lep_relIso04DB");
    tx->createBranch<vector<float>>("lep_customrelIso01EA");
    tx->createBranch<int>("nrecolep");
}

//##############################################################################################################
void hwwBabyMaker::LeptonModule::FillOutput()
{
    std::cout.setstate(std::ios_base::failbit); // To suppress warning about CMS4 not having PF candidates
    // Lepton absolute isolations
    for (auto& idx : babymaker->coreElectron.index)
    {
        tx->pushbackToBranch<LV>   ("lep_p4"  , cms3.els_p4()[idx]);
        tx->pushbackToBranch<int>  ("lep_id"  , cms3.els_charge()[idx]*(-11));
        tx->pushbackToBranch<int>  ("lep_idx" , idx);
        tx->pushbackToBranch<float>("lep_pt"  , cms3.els_p4()[idx].pt());
        tx->pushbackToBranch<float>("lep_eta" , cms3.els_p4()[idx].eta());
        tx->pushbackToBranch<float>("lep_phi" , cms3.els_p4()[idx].phi());
        tx->pushbackToBranch<float>("lep_miniIsoEA" , elMiniRelIsoCMS3_EA(idx, 2));
        tx->pushbackToBranch<float>("lep_relIso03EA" , eleRelIso03EA(idx, 2));
        tx->pushbackToBranch<float>("lep_relIso04DB" , -999);
        tx->pushbackToBranch<float>("lep_customrelIso01EA"  , elRelIsoCustomCone(idx , 0.1  , false , 0.0 , false , true , -1 , 2 , true));
    }

    for (auto& idx : babymaker->coreMuon.index)
    {
        tx->pushbackToBranch<LV>   ("lep_p4"  , cms3.mus_p4()[idx]);
        tx->pushbackToBranch<int>  ("lep_id"  , cms3.mus_charge()[idx]*(-13));
        tx->pushbackToBranch<int>  ("lep_idx" , idx);
        tx->pushbackToBranch<float>("lep_pt"  , cms3.mus_p4()[idx].pt());
        tx->pushbackToBranch<float>("lep_eta" , cms3.mus_p4()[idx].eta());
        tx->pushbackToBranch<float>("lep_phi" , cms3.mus_p4()[idx].phi());
        tx->pushbackToBranch<float>("lep_miniIsoEA" , muMiniRelIsoCMS3_EA(idx, 2));
        tx->pushbackToBranch<float>("lep_relIso03EA" , muRelIso03EA(idx, 2));
        tx->pushbackToBranch<float>("lep_relIso04DB" , muRelIso04DB(idx));
        tx->pushbackToBranch<float>("lep_customrelIso01EA"  , muRelIsoCustomCone(idx , 0.1  , false , 0.5 , false , true , -1 , 2 , true));
    }
    tx->setBranch<int>("nrecolep", babymaker->coreElectron.index.size() + babymaker->coreMuon.index.size());
    std::cout.clear();

    tx->sortVecBranchesByPt("lep_p4",
            {
            "lep_pt",
            "lep_eta",
            "lep_phi",
            "lep_miniIsoEA",
            "lep_relIso03EA",
            "lep_relIso04DB",
            "lep_customrelIso01EA",
            },
            {
            "lep_id",
            "lep_idx",
            },
            {});

}


//==============================================================================================================
//
// Fat Jet Module
//
//==============================================================================================================

void hwwBabyMaker::FatJetModule::AddOutput()
{

    // Everything is using PUPPI as default
    tx->createBranch<int>("nak8jets");
    tx->createBranch<vector<LV>>("ak8jets_p4");
    tx->createBranch<vector<float>>("ak8jets_area");
    tx->createBranch<vector<float>>("ak8jets_pt");
    tx->createBranch<vector<float>>("ak8jets_eta");
    tx->createBranch<vector<float>>("ak8jets_phi");
    tx->createBranch<vector<float>>("ak8jets_energy"); // p4.energy()
    tx->createBranch<vector<float>>("ak8jets_mass"); // p4.m()
    tx->createBranch<vector<float>>("ak8jets_softdropMass");
    tx->createBranch<vector<float>>("ak8jets_prunedMass");
    tx->createBranch<vector<float>>("ak8jets_nJettinessTau1");
    tx->createBranch<vector<float>>("ak8jets_nJettinessTau2");
    tx->createBranch<vector<float>>("ak8jets_nJettinessTau3");
    tx->createBranch<vector<float>>("ak8jets_deep_bindisc_h4q");
    tx->createBranch<vector<float>>("ak8jets_deep_bindisc_hbb");
    tx->createBranch<vector<float>>("ak8jets_deep_bindisc_top");
    tx->createBranch<vector<float>>("ak8jets_deep_bindisc_w");
    tx->createBranch<vector<float>>("ak8jets_deep_bindisc_z");
    tx->createBranch<vector<float>>("ak8jets_deep_bindisc_zbb");
    tx->createBranch<vector<float>>("ak8jets_deep_rawdisc_h4q");
    tx->createBranch<vector<float>>("ak8jets_deep_rawdisc_hbb");
    tx->createBranch<vector<float>>("ak8jets_deep_rawdisc_qcd");
    tx->createBranch<vector<float>>("ak8jets_deep_rawdisc_top");
    tx->createBranch<vector<float>>("ak8jets_deep_rawdisc_w");
    tx->createBranch<vector<float>>("ak8jets_deep_rawdisc_z");
    tx->createBranch<vector<float>>("ak8jets_deep_rawdisc_zbb");
    tx->createBranch<vector<float>>("ak8jets_softdropPuppiSubjet1_pt");
    tx->createBranch<vector<float>>("ak8jets_softdropPuppiSubjet1_eta");
    tx->createBranch<vector<float>>("ak8jets_softdropPuppiSubjet1_phi");
    tx->createBranch<vector<float>>("ak8jets_softdropPuppiSubjet1_mass");
    tx->createBranch<vector<float>>("ak8jets_softdropPuppiSubjet1_energy");
    tx->createBranch<vector<float>>("ak8jets_softdropPuppiSubjet2_pt");
    tx->createBranch<vector<float>>("ak8jets_softdropPuppiSubjet2_eta");
    tx->createBranch<vector<float>>("ak8jets_softdropPuppiSubjet2_phi");
    tx->createBranch<vector<float>>("ak8jets_softdropPuppiSubjet2_mass");
    tx->createBranch<vector<float>>("ak8jets_softdropPuppiSubjet2_energy");
    tx->createBranch<vector<int>>("ak8jets_npfcands");
    tx->createBranch<vector<int>>("ak8jets_partonFlavour");

}

void hwwBabyMaker::FatJetModule::FillOutput()
{

    int nak8jets = 0;
    for (unsigned ijet = 0; ijet < babymaker->coreFatJet.index.size(); ++ijet)
    {
        int idx = babymaker->coreFatJet.index[ijet];
        float corr = babymaker->coreFatJet.corrs[ijet];
        //float shift = babymaker->coreFatJet.shifts[ijet];
        LorentzVector fatjet = cms3.ak8jets_p4()[idx] * cms3.ak8jets_undoJEC()[idx] * corr;
        if (fatjet.pt() > 20)
        {
            nak8jets++;
            tx->pushbackToBranch<LV>("ak8jets_p4", fatjet);
            tx->pushbackToBranch<float>("ak8jets_area", cms3.ak8jets_area()[idx]);
            tx->pushbackToBranch<float>("ak8jets_pt", fatjet.pt());
            tx->pushbackToBranch<float>("ak8jets_eta", fatjet.eta());
            tx->pushbackToBranch<float>("ak8jets_phi", fatjet.phi());
            tx->pushbackToBranch<float>("ak8jets_mass", fatjet.mass());
            tx->pushbackToBranch<float>("ak8jets_energy", fatjet.energy());
            tx->pushbackToBranch<float>("ak8jets_softdropMass", cms3.ak8jets_puppi_softdropMass()[idx]);
            tx->pushbackToBranch<float>("ak8jets_prunedMass", cms3.ak8jets_prunedMass()[idx]);
            tx->pushbackToBranch<float>("ak8jets_nJettinessTau1", cms3.ak8jets_nJettinessTau1()[idx]);
            tx->pushbackToBranch<float>("ak8jets_nJettinessTau2", cms3.ak8jets_nJettinessTau2()[idx]);
            tx->pushbackToBranch<float>("ak8jets_nJettinessTau3", cms3.ak8jets_nJettinessTau3()[idx]);
            tx->pushbackToBranch<float>("ak8jets_deep_bindisc_h4q", cms3.ak8jets_deep_bindisc_h4q()[idx]);
            tx->pushbackToBranch<float>("ak8jets_deep_bindisc_hbb", cms3.ak8jets_deep_bindisc_hbb()[idx]);
            tx->pushbackToBranch<float>("ak8jets_deep_bindisc_top", cms3.ak8jets_deep_bindisc_top()[idx]);
            tx->pushbackToBranch<float>("ak8jets_deep_bindisc_w", cms3.ak8jets_deep_bindisc_w()[idx]);
            tx->pushbackToBranch<float>("ak8jets_deep_bindisc_z", cms3.ak8jets_deep_bindisc_z()[idx]);
            tx->pushbackToBranch<float>("ak8jets_deep_bindisc_zbb", cms3.ak8jets_deep_bindisc_zbb()[idx]);
            tx->pushbackToBranch<float>("ak8jets_deep_rawdisc_h4q", cms3.ak8jets_deep_rawdisc_h4q()[idx]);
            tx->pushbackToBranch<float>("ak8jets_deep_rawdisc_hbb", cms3.ak8jets_deep_rawdisc_hbb()[idx]);
            tx->pushbackToBranch<float>("ak8jets_deep_rawdisc_qcd", cms3.ak8jets_deep_rawdisc_qcd()[idx]);
            tx->pushbackToBranch<float>("ak8jets_deep_rawdisc_top", cms3.ak8jets_deep_rawdisc_top()[idx]);
            tx->pushbackToBranch<float>("ak8jets_deep_rawdisc_w", cms3.ak8jets_deep_rawdisc_w()[idx]);
            tx->pushbackToBranch<float>("ak8jets_deep_rawdisc_z", cms3.ak8jets_deep_rawdisc_z()[idx]);
            tx->pushbackToBranch<float>("ak8jets_deep_rawdisc_zbb", cms3.ak8jets_deep_rawdisc_zbb()[idx]);
            tx->pushbackToBranch<float>("ak8jets_softdropPuppiSubjet1_pt", cms3.ak8jets_softdropPuppiSubjet1()[idx].pt());
            tx->pushbackToBranch<float>("ak8jets_softdropPuppiSubjet1_eta", cms3.ak8jets_softdropPuppiSubjet1()[idx].eta());
            tx->pushbackToBranch<float>("ak8jets_softdropPuppiSubjet1_phi", cms3.ak8jets_softdropPuppiSubjet1()[idx].phi());
            tx->pushbackToBranch<float>("ak8jets_softdropPuppiSubjet1_mass", cms3.ak8jets_softdropPuppiSubjet1()[idx].mass());
            tx->pushbackToBranch<float>("ak8jets_softdropPuppiSubjet1_energy", cms3.ak8jets_softdropPuppiSubjet1()[idx].energy());
            tx->pushbackToBranch<float>("ak8jets_softdropPuppiSubjet2_pt", cms3.ak8jets_softdropPuppiSubjet2()[idx].pt());
            tx->pushbackToBranch<float>("ak8jets_softdropPuppiSubjet2_eta", cms3.ak8jets_softdropPuppiSubjet2()[idx].eta());
            tx->pushbackToBranch<float>("ak8jets_softdropPuppiSubjet2_phi", cms3.ak8jets_softdropPuppiSubjet2()[idx].phi());
            tx->pushbackToBranch<float>("ak8jets_softdropPuppiSubjet2_mass", cms3.ak8jets_softdropPuppiSubjet2()[idx].mass());
            tx->pushbackToBranch<float>("ak8jets_softdropPuppiSubjet2_energy", cms3.ak8jets_softdropPuppiSubjet2()[idx].energy());
            tx->pushbackToBranch<int>("ak8jets_npfcands", cms3.ak8jets_npfcands()[idx]);
            tx->pushbackToBranch<int>("ak8jets_partonFlavour", cms3.ak8jets_partonFlavour()[idx]);
        }
    }
    tx->setBranch<int>("nak8jets", nak8jets);

    tx->sortVecBranchesByPt("ak8jets_p4",
            {
            "ak8jets_area",
            "ak8jets_pt",
            "ak8jets_eta",
            "ak8jets_phi",
            "ak8jets_mass",
            "ak8jets_energy",
            "ak8jets_softdropMass",
            "ak8jets_prunedMass",
            "ak8jets_nJettinessTau1",
            "ak8jets_nJettinessTau2",
            "ak8jets_nJettinessTau3",
            "ak8jets_deep_bindisc_h4q",
            "ak8jets_deep_bindisc_hbb",
            "ak8jets_deep_bindisc_top",
            "ak8jets_deep_bindisc_w",
            "ak8jets_deep_bindisc_z",
            "ak8jets_deep_bindisc_zbb",
            "ak8jets_deep_rawdisc_h4q",
            "ak8jets_deep_rawdisc_hbb",
            "ak8jets_deep_rawdisc_qcd",
            "ak8jets_deep_rawdisc_top",
            "ak8jets_deep_rawdisc_w",
            "ak8jets_deep_rawdisc_z",
            "ak8jets_deep_rawdisc_zbb",
            "ak8jets_softdropPuppiSubjet1_pt",
            "ak8jets_softdropPuppiSubjet1_eta",
            "ak8jets_softdropPuppiSubjet1_phi",
            "ak8jets_softdropPuppiSubjet1_mass",
            "ak8jets_softdropPuppiSubjet1_energy",
            "ak8jets_softdropPuppiSubjet2_pt",
            "ak8jets_softdropPuppiSubjet2_eta",
            "ak8jets_softdropPuppiSubjet2_phi",
            "ak8jets_softdropPuppiSubjet2_mass",
            "ak8jets_softdropPuppiSubjet2_energy",
            },
            {
            "ak8jets_npfcands",
            "ak8jets_partonFlavour",
            },
            {});

}

