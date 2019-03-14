#include "hwwBabyMaker.h"

//##############################################################################################################
hwwBabyMaker::hwwBabyMaker() : processor(0) {}
hwwBabyMaker::~hwwBabyMaker() {}

//##############################################################################################################
void hwwBabyMaker::ProcessElectrons()
{
    coreElectron.process(isPt20Electron);
}

//##############################################################################################################
void hwwBabyMaker::ProcessMuons()
{
    coreMuon.process(isPt20Muon);
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
        LV fatjet = cms3.ak8jets_p4()[idx] * cms3.ak8jets_undoJEC()[idx] * corr;
        if (fatjet.pt() > 20)
        {
            n_ak8++;
        }
    }

    // Pass with at least one fat jet and only one lepton
    if (n_ak8 >= 1 && n_reconstructed_leptons == 1)
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
    processor->AddModule(new JetModule(this));
    processor->AddModule(new METModule(this));
    processor->AddModule(new TriggerModule(this));
    if (looper.getCurrentFileName().Contains("HToWWToLNuQQ") or looper.getCurrentFileName().Contains("VHToNonbb"))
        processor->AddModule(new HWWlvjjTruthModule(this));
    processor->AddModule(new HiggsRecoModule(this));
    processor->AddModule(new RecoilModule(this));
    processor->AddModule(new RecoilModule(this, "_allj_1_4", "alljets_p4", TMath::Pi() * 1. / 4.));
    processor->AddModule(new RecoilModule(this, "_j_3_4", "jets_p4", TMath::Pi() * 3. / 4.));
    processor->AddModule(new GenPartModule(this));
    processor->AddModule(new EventModule(this));

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
bool hwwBabyMaker::isPt20Electron(int idx)
{
    if (!( cms3.els_p4()[idx].pt() > 20.          )) return false;
    if (!( isPt10Electron(idx)                    )) return false;
    return true;
}

//##############################################################################################################
// Used to overlap remova against tracks
bool hwwBabyMaker::isPt20Muon(int idx)
{
    if (!( cms3.mus_p4()[idx].pt() > 20.        )) return false;
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

//==============================================================================================================
//
// Lepton Module
//
//==============================================================================================================

//##############################################################################################################
void hwwBabyMaker::LeptonModule::AddOutput()
{
    tx->createBranch<int>("nrecolep");
    tx->createBranch<vector<LV>>("lep_p4");

    // And none of the following will be written to the TTree (hence the second argument being set to false)
    // This is so that we save sapce, there will be a separate branch that actually selects the ak8jets of interest
    // and save the necessary information.
    bool writeToTree = true;
    tx->createBranch<vector<int>>("lep_id", writeToTree);
    tx->createBranch<vector<int>>("lep_idx", writeToTree);
    tx->createBranch<vector<int>>("lep_isTightPOG", writeToTree);
    tx->createBranch<vector<float>>("lep_pt", writeToTree);
    tx->createBranch<vector<float>>("lep_eta", writeToTree);
    tx->createBranch<vector<float>>("lep_phi", writeToTree);
    tx->createBranch<vector<float>>("lep_miniIsoEA", writeToTree);
    tx->createBranch<vector<float>>("lep_relIso03EA", writeToTree);
    tx->createBranch<vector<float>>("lep_relIso04DB", writeToTree);
    tx->createBranch<vector<float>>("lep_customrelIso005EA", writeToTree);
    tx->createBranch<vector<float>>("lep_customrelIso01EA", writeToTree);
    tx->createBranch<vector<float>>("lep_ip3d", writeToTree);
    tx->createBranch<vector<float>>("lep_ip3derr", writeToTree);
    tx->createBranch<vector<float>>("lep_dxy", writeToTree);
    tx->createBranch<vector<float>>("lep_dz", writeToTree);
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
        tx->pushbackToBranch<int>  ("lep_isTightPOG", isTightElectronPOGspring16noIso_v1(idx));
        tx->pushbackToBranch<float>("lep_pt"  , cms3.els_p4()[idx].pt());
        tx->pushbackToBranch<float>("lep_eta" , cms3.els_p4()[idx].eta());
        tx->pushbackToBranch<float>("lep_phi" , cms3.els_p4()[idx].phi());
        tx->pushbackToBranch<float>("lep_miniIsoEA" , elMiniRelIsoCMS3_EA(idx, 2));
        tx->pushbackToBranch<float>("lep_relIso03EA" , eleRelIso03EA(idx, 2));
        tx->pushbackToBranch<float>("lep_relIso04DB" , -999);
        tx->pushbackToBranch<float>("lep_customrelIso005EA" , elRelIsoCustomCone(idx , 0.1  , false , 0.0 , false , true , -1 , 2 , true));
        tx->pushbackToBranch<float>("lep_customrelIso01EA"  , elRelIsoCustomCone(idx , 0.1  , false , 0.0 , false , true , -1 , 2 , true));
        tx->pushbackToBranch<float>("lep_ip3d"  , cms3.els_ip3d()[idx]);
        tx->pushbackToBranch<float>("lep_ip3derr"  , cms3.els_ip3derr()[idx]);
        tx->pushbackToBranch<float>("lep_dxy"  , cms3.els_dxyPV()[idx]);
        tx->pushbackToBranch<float>("lep_dz"  , cms3.els_dzPV()[idx]);
    }

    for (auto& idx : babymaker->coreMuon.index)
    {
        tx->pushbackToBranch<LV>   ("lep_p4"  , cms3.mus_p4()[idx]);
        tx->pushbackToBranch<int>  ("lep_id"  , cms3.mus_charge()[idx]*(-13));
        tx->pushbackToBranch<int>  ("lep_idx" , idx);
        tx->pushbackToBranch<int>  ("lep_isTightPOG", isMediumMuonPOG(idx));
        tx->pushbackToBranch<float>("lep_pt"  , cms3.mus_p4()[idx].pt());
        tx->pushbackToBranch<float>("lep_eta" , cms3.mus_p4()[idx].eta());
        tx->pushbackToBranch<float>("lep_phi" , cms3.mus_p4()[idx].phi());
        tx->pushbackToBranch<float>("lep_miniIsoEA" , muMiniRelIsoCMS3_EA(idx, 2));
        tx->pushbackToBranch<float>("lep_relIso03EA" , muRelIso03EA(idx, 2));
        tx->pushbackToBranch<float>("lep_relIso04DB" , muRelIso04DB(idx));
        tx->pushbackToBranch<float>("lep_customrelIso005EA" , muRelIsoCustomCone(idx , 0.1  , false , 0.5 , false , true , -1 , 2 , true));
        tx->pushbackToBranch<float>("lep_customrelIso01EA"  , muRelIsoCustomCone(idx , 0.1  , false , 0.5 , false , true , -1 , 2 , true));
        tx->pushbackToBranch<float>("lep_ip3d"  , cms3.mus_ip3d()[idx]);
        tx->pushbackToBranch<float>("lep_ip3derr"  , cms3.mus_ip3derr()[idx]);
        tx->pushbackToBranch<float>("lep_dxy"  , cms3.mus_dxyPV()[idx]);
        tx->pushbackToBranch<float>("lep_dz"  , cms3.mus_dzPV()[idx]);
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
            "lep_customrelIso005EA",
            "lep_customrelIso01EA",
            "lep_ip3d",
            "lep_ip3derr",
            "lep_dxy",
            "lep_dz",
            },
            {
            "lep_id",
            "lep_idx",
            "lep_isTightPOG",
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

    tx->createBranch<int>("nak8jets");
    tx->createBranch<vector<LV>>("ak8jets_p4");
    tx->createBranch<vector<float>>("ak8jets_undoJEC");

    // Everything is using PUPPI as default
    // And none of the following will be written to the TTree (hence the second argument being set to false)
    // This is so that we save sapce, there will be a separate branch that actually selects the ak8jets of interest
    // and save the necessary information.
    bool writeToTree = false;
    tx->createBranch<vector<float>>("ak8jets_area", writeToTree);
    tx->createBranch<vector<float>>("ak8jets_pt", writeToTree);
    tx->createBranch<vector<float>>("ak8jets_eta", writeToTree);
    tx->createBranch<vector<float>>("ak8jets_phi", writeToTree);
    tx->createBranch<vector<float>>("ak8jets_energy", writeToTree); // p4.energy()
    tx->createBranch<vector<float>>("ak8jets_mass", writeToTree); // p4.m()
    tx->createBranch<vector<float>>("ak8jets_softdropMass", writeToTree);
    tx->createBranch<vector<float>>("ak8jets_nJettinessTau1", writeToTree);
    tx->createBranch<vector<float>>("ak8jets_nJettinessTau2", writeToTree);
    tx->createBranch<vector<float>>("ak8jets_nJettinessTau3", writeToTree);
    // tx->createBranch<vector<float>>("ak8jets_puppi_pt", writeToTree);
    // tx->createBranch<vector<float>>("ak8jets_puppi_eta", writeToTree);
    // tx->createBranch<vector<float>>("ak8jets_puppi_phi", writeToTree);
    // tx->createBranch<vector<float>>("ak8jets_puppi_mass", writeToTree); // p4.m()
    // tx->createBranch<vector<float>>("ak8jets_puppi_softdropMass", writeToTree);
    // tx->createBranch<vector<float>>("ak8jets_puppi_nJettinessTau1", writeToTree);
    // tx->createBranch<vector<float>>("ak8jets_puppi_nJettinessTau2", writeToTree);
    // tx->createBranch<vector<float>>("ak8jets_puppi_nJettinessTau3", writeToTree);
    tx->createBranch<vector<float>>("ak8jets_deep_rawdisc_h4q", writeToTree);
    tx->createBranch<vector<float>>("ak8jets_deep_rawdisc_hbb", writeToTree);
    tx->createBranch<vector<float>>("ak8jets_deep_rawdisc_qcd", writeToTree);
    tx->createBranch<vector<float>>("ak8jets_deep_rawdisc_top", writeToTree);
    tx->createBranch<vector<float>>("ak8jets_deep_rawdisc_w", writeToTree);
    tx->createBranch<vector<float>>("ak8jets_deep_rawdisc_z", writeToTree);
    tx->createBranch<vector<float>>("ak8jets_deep_rawdisc_zbb", writeToTree);
    tx->createBranch<vector<float>>("ak8jets_deep_bindisc_h4q", writeToTree);
    tx->createBranch<vector<float>>("ak8jets_deep_bindisc_hbb", writeToTree);
    tx->createBranch<vector<float>>("ak8jets_deep_bindisc_top", writeToTree);
    tx->createBranch<vector<float>>("ak8jets_deep_bindisc_w", writeToTree);
    tx->createBranch<vector<float>>("ak8jets_deep_bindisc_z", writeToTree);
    tx->createBranch<vector<float>>("ak8jets_deep_bindisc_zbb", writeToTree);
    tx->createBranch<vector<float>>("ak8jets_softdropPuppiSubjet1_pt", writeToTree);
    tx->createBranch<vector<float>>("ak8jets_softdropPuppiSubjet1_eta", writeToTree);
    tx->createBranch<vector<float>>("ak8jets_softdropPuppiSubjet1_phi", writeToTree);
    tx->createBranch<vector<float>>("ak8jets_softdropPuppiSubjet1_mass", writeToTree);
    tx->createBranch<vector<float>>("ak8jets_softdropPuppiSubjet1_energy", writeToTree);
    tx->createBranch<vector<float>>("ak8jets_softdropPuppiSubjet2_pt", writeToTree);
    tx->createBranch<vector<float>>("ak8jets_softdropPuppiSubjet2_eta", writeToTree);
    tx->createBranch<vector<float>>("ak8jets_softdropPuppiSubjet2_phi", writeToTree);
    tx->createBranch<vector<float>>("ak8jets_softdropPuppiSubjet2_mass", writeToTree);
    tx->createBranch<vector<float>>("ak8jets_softdropPuppiSubjet2_energy", writeToTree);
    tx->createBranch<vector<int>>("ak8jets_npfcands", writeToTree);
    tx->createBranch<vector<int>>("ak8jets_partonFlavour", writeToTree);
    tx->createBranch<vector<float>>("ak8jets_csv", writeToTree);
    tx->createBranch<vector<float>>("ak8jets_dbl", writeToTree);

}

void hwwBabyMaker::FatJetModule::FillOutput()
{

    int nak8jets = 0;
    for (unsigned ijet = 0; ijet < babymaker->coreFatJet.index.size(); ++ijet)
    {
        int idx = babymaker->coreFatJet.index[ijet];
        float corr = babymaker->coreFatJet.corrs[ijet];
        //float shift = babymaker->coreFatJet.shifts[ijet];
        LV fatjet = cms3.ak8jets_p4()[idx] * cms3.ak8jets_undoJEC()[idx] * corr;
        if (fatjet.pt() > 20)
        {
            nak8jets++;
            tx->pushbackToBranch<LV>("ak8jets_p4", fatjet);
            tx->pushbackToBranch<float>("ak8jets_undoJEC", 1 / corr);
            tx->pushbackToBranch<float>("ak8jets_area", cms3.ak8jets_area()[idx]);
            tx->pushbackToBranch<float>("ak8jets_pt", fatjet.pt());
            tx->pushbackToBranch<float>("ak8jets_eta", fatjet.eta());
            tx->pushbackToBranch<float>("ak8jets_phi", fatjet.phi());
            tx->pushbackToBranch<float>("ak8jets_mass", fatjet.mass());
            tx->pushbackToBranch<float>("ak8jets_energy", fatjet.energy());
            if (babymaker->looper.getCurrentFileName().Contains("Summer16MiniAODv3"))
                tx->pushbackToBranch<float>("ak8jets_softdropMass", cms3.ak8jets_puppi_softdropMass()[idx]);
            else
                tx->pushbackToBranch<float>("ak8jets_softdropMass", cms3.ak8jets_softdropMass()[idx]);
            tx->pushbackToBranch<float>("ak8jets_nJettinessTau1", cms3.ak8jets_nJettinessTau1()[idx]);
            tx->pushbackToBranch<float>("ak8jets_nJettinessTau2", cms3.ak8jets_nJettinessTau2()[idx]);
            // if (babymaker->looper.doesBranchExist("ak8jets_puppi_pt"))
            // {
            //     tx->pushbackToBranch<float>("ak8jets_puppi_pt", fatjet.pt());
            //     tx->pushbackToBranch<float>("ak8jets_puppi_eta", fatjet.eta());
            //     tx->pushbackToBranch<float>("ak8jets_puppi_phi", fatjet.phi());
            //     tx->pushbackToBranch<float>("ak8jets_puppi_mass", fatjet.mass());
            //     tx->pushbackToBranch<float>("ak8jets_puppi_softdropMass", cms3.ak8jets_puppi_softdropMass()[idx]);
            //     tx->pushbackToBranch<float>("ak8jets_puppi_nJettinessTau1", cms3.ak8jets_puppi_nJettinessTau1()[idx]);
            //     tx->pushbackToBranch<float>("ak8jets_puppi_nJettinessTau2", cms3.ak8jets_puppi_nJettinessTau2()[idx]);
            //     tx->pushbackToBranch<float>("ak8jets_puppi_nJettinessTau3", cms3.ak8jets_puppi_nJettinessTau3()[idx]);
            // }
            if (babymaker->looper.doesBranchExist("ak8jets_deep_rawdisc_h4q"))
            {
                tx->pushbackToBranch<float>("ak8jets_nJettinessTau3", cms3.ak8jets_nJettinessTau3()[idx]);
                tx->pushbackToBranch<float>("ak8jets_deep_rawdisc_h4q", cms3.ak8jets_deep_rawdisc_h4q()[idx]);
                tx->pushbackToBranch<float>("ak8jets_deep_rawdisc_hbb", cms3.ak8jets_deep_rawdisc_hbb()[idx]);
                tx->pushbackToBranch<float>("ak8jets_deep_rawdisc_qcd", cms3.ak8jets_deep_rawdisc_qcd()[idx]);
                tx->pushbackToBranch<float>("ak8jets_deep_rawdisc_top", cms3.ak8jets_deep_rawdisc_top()[idx]);
                tx->pushbackToBranch<float>("ak8jets_deep_rawdisc_w", cms3.ak8jets_deep_rawdisc_w()[idx]);
                tx->pushbackToBranch<float>("ak8jets_deep_rawdisc_z", cms3.ak8jets_deep_rawdisc_z()[idx]);
                tx->pushbackToBranch<float>("ak8jets_deep_rawdisc_zbb", cms3.ak8jets_deep_rawdisc_zbb()[idx]);
                // tx->pushbackToBranch<float>("ak8jets_deep_bindisc_h4q", cms3.ak8jets_deep_bindisc_h4q()[idx]);
                // tx->pushbackToBranch<float>("ak8jets_deep_bindisc_hbb", cms3.ak8jets_deep_bindisc_hbb()[idx]);
                // tx->pushbackToBranch<float>("ak8jets_deep_bindisc_top", cms3.ak8jets_deep_bindisc_top()[idx]);
                // tx->pushbackToBranch<float>("ak8jets_deep_bindisc_w", cms3.ak8jets_deep_bindisc_w()[idx]);
                // tx->pushbackToBranch<float>("ak8jets_deep_bindisc_z", cms3.ak8jets_deep_bindisc_z()[idx]);
                // tx->pushbackToBranch<float>("ak8jets_deep_bindisc_zbb", cms3.ak8jets_deep_bindisc_zbb()[idx]);
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
                tx->pushbackToBranch<float>("ak8jets_csv", cms3.ak8jets_bDiscriminators()[idx][0]);
                tx->pushbackToBranch<float>("ak8jets_dbl", cms3.ak8jets_bDiscriminators()[idx][1]);
            }
        }
    }
    tx->setBranch<int>("nak8jets", nak8jets);

    tx->sortVecBranchesByPt("ak8jets_p4",
            {
            "ak8jets_undoJEC",
            "ak8jets_area",
            "ak8jets_pt",
            "ak8jets_eta",
            "ak8jets_phi",
            "ak8jets_mass",
            "ak8jets_energy",
            "ak8jets_softdropMass",
            "ak8jets_nJettinessTau1",
            "ak8jets_nJettinessTau2",
            "ak8jets_nJettinessTau3",
            // "ak8jets_puppi_pt",
            // "ak8jets_puppi_eta",
            // "ak8jets_puppi_phi",
            // "ak8jets_puppi_mass",
            // "ak8jets_puppi_softdropMass",
            // "ak8jets_puppi_nJettinessTau1",
            // "ak8jets_puppi_nJettinessTau2",
            // "ak8jets_puppi_nJettinessTau3",
            "ak8jets_deep_rawdisc_h4q",
            "ak8jets_deep_rawdisc_hbb",
            "ak8jets_deep_rawdisc_qcd",
            "ak8jets_deep_rawdisc_top",
            "ak8jets_deep_rawdisc_w",
            "ak8jets_deep_rawdisc_z",
            "ak8jets_deep_rawdisc_zbb",
            // "ak8jets_deep_bindisc_h4q",
            // "ak8jets_deep_bindisc_hbb",
            // "ak8jets_deep_bindisc_top",
            // "ak8jets_deep_bindisc_w",
            // "ak8jets_deep_bindisc_z",
            // "ak8jets_deep_bindisc_zbb",
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
            "ak8jets_csv",
            "ak8jets_dbl",
            },
            {
            "ak8jets_npfcands",
            "ak8jets_partonFlavour",
            },
            {});

}

//==============================================================================================================
//
// Trigger Module
//
//==============================================================================================================

void hwwBabyMaker::TriggerModule::AddOutput()
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

void hwwBabyMaker::TriggerModule::FillOutput()
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

//==============================================================================================================
//
// Jet Module
//
//==============================================================================================================

void hwwBabyMaker::JetModule::AddOutput()
{
    tx->createBranch<int>("nj");
    tx->createBranch<int>("nb");
    tx->createBranch<int>("nbmed");
    tx->createBranch<int>("nbtight");
    tx->createBranch<vector<LV>>("jets_p4");
    tx->createBranch<vector<LV>>("alljets_p4");
    tx->createBranch<vector<int>>("jets_idx");
    tx->createBranch<vector<int>>("alljets_idx");

    // Following will not be written out
    bool writeToTree = false;
    tx->createBranch<vector<float>>("jets_pt", writeToTree);
    tx->createBranch<vector<float>>("jets_eta", writeToTree);
    tx->createBranch<vector<float>>("jets_phi", writeToTree);
    tx->createBranch<vector<float>>("jets_csv", writeToTree);

}

void hwwBabyMaker::JetModule::FillOutput()
{
    int nj = 0;
    int nb = 0;
    int nbmed = 0;
    int nbtight = 0;

    for (unsigned ijet = 0; ijet < babymaker->coreJet.index.size(); ++ijet)
    {
        int idx = babymaker->coreJet.index[ijet];
        float corr = babymaker->coreJet.corrs[ijet];
//        float shift = babymaker->coreJet.shifts[ijet];
        float current_csv_val = cms3.getbtagvalue("pfCombinedInclusiveSecondaryVertexV2BJetTags", idx);
        LV jet = cms3.pfjets_p4()[idx] * cms3.pfjets_undoJEC()[idx] * corr;

        // Check whether this jet overlaps with any of the leptons
        if (babymaker->isLeptonOverlappingWithJet(ijet))
            continue;

        // All jets
        tx->pushbackToBranch<LV>("alljets_p4", jet);
        tx->pushbackToBranch<int>("alljets_idx", idx);

        if (jet.pt() > 30)
        {
            tx->pushbackToBranch<LV>("jets_p4", jet);
            tx->pushbackToBranch<int>("jets_idx", idx);
            tx->pushbackToBranch<float>("jets_pt", jet.pt());
            tx->pushbackToBranch<float>("jets_eta", jet.eta());
            tx->pushbackToBranch<float>("jets_phi", jet.phi());
            tx->pushbackToBranch<float>("jets_csv", current_csv_val);
//            if (!isFastSim())
                babymaker->coreBtagSF.accumulateSF(idx, jet.pt(), jet.eta());
//            else
//                babymaker->coreBtagSFFastSim.accumulateSF(idx, jet.pt(), jet.eta());
            nj++;
        }

//        const double BJET_CSV_TIGHT = 0.9535;
//        const double BJET_CSV_MED = 0.8484;
//        const double BJET_CSV_LOOSE = 0.5426;

        // nb jets
        if (jet.pt() > 20.)
        {
            if (fabs(jet.eta()) < 2.4 && current_csv_val >= 0.5426)
                nb++;
            if (fabs(jet.eta()) < 2.4 && current_csv_val >= 0.8484)
                nbmed++;
            if (fabs(jet.eta()) < 2.4 && current_csv_val >= 0.9535)
                nbtight++;
        }

//        LV jet_up = jet * (1. + shift);
//        if (jet_up.pt() > 30)
//        {
//            tx->pushbackToBranch<LV>("jets_up_p4", jet_up);
//            tx->pushbackToBranch<float>("jets_up_pt", jet_up.pt());
//            tx->pushbackToBranch<float>("jets_up_eta", jet_up.eta());
//            tx->pushbackToBranch<float>("jets_up_phi", jet_up.phi());
//            tx->pushbackToBranch<float>("jets_up_csv", current_csv_val);
//        }
//
//        LV jet_dn = jet * (1. - shift);
//        if (jet_dn.pt() > 30)
//        {
//            tx->pushbackToBranch<LV>("jets_dn_p4", jet_dn);
//            tx->pushbackToBranch<float>("jets_dn_pt", jet_dn.pt());
//            tx->pushbackToBranch<float>("jets_dn_eta", jet_dn.eta());
//            tx->pushbackToBranch<float>("jets_dn_phi", jet_dn.phi());
//            tx->pushbackToBranch<float>("jets_dn_csv", current_csv_val);
//        }

    }

    tx->setBranch<int>("nj", nj);
    tx->setBranch<int>("nb", nb);
    tx->setBranch<int>("nbmed", nbmed);
    tx->setBranch<int>("nbtight", nbtight);
}

//==============================================================================================================
//
// MET Module
//
//==============================================================================================================

void hwwBabyMaker::METModule::AddOutput()
{

    tx->createBranch<float>("met_pt");
    tx->createBranch<float>("met_phi");
    tx->createBranch<float>("met_up_pt");
    tx->createBranch<float>("met_up_phi");
    tx->createBranch<float>("met_dn_pt");
    tx->createBranch<float>("met_dn_phi");
    tx->createBranch<float>("met_gen_pt");
    tx->createBranch<float>("met_gen_phi");

}

void hwwBabyMaker::METModule::FillOutput()
{

    tx->setBranch<float>("met_pt", babymaker->coreMET.met_pt);
    tx->setBranch<float>("met_phi", babymaker->coreMET.met_phi);
    tx->setBranch<float>("met_up_pt", babymaker->coreMET.met_up_pt);
    tx->setBranch<float>("met_up_phi", babymaker->coreMET.met_up_phi);
    tx->setBranch<float>("met_dn_pt", babymaker->coreMET.met_dn_pt);
    tx->setBranch<float>("met_dn_phi", babymaker->coreMET.met_dn_phi);
    tx->setBranch<float>("met_gen_pt", cms3.gen_met());
    tx->setBranch<float>("met_gen_phi", cms3.gen_metPhi());

}

//==============================================================================================================
//
// HWWlvjj Truth Module
//
//==============================================================================================================

void hwwBabyMaker::HWWlvjjTruthModule::AddOutput()
{
//    if (babymaker->looper.getCurrentFileName().Contains("HToWWToLNuQQ"))
//    {
//        AddOutput_ggHToWWToLNuQQ();
//    }
//    else if(babymaker->looper.getCurrentFileName().Contains("VHToNonbb"))
//    {
        AddOutput_HWW();
//    }
}

void hwwBabyMaker::HWWlvjjTruthModule::AddOutput_ggHToWWToLNuQQ()
{

    // Some intermediate variables that do not need to be written out to tree
    bool writeToTree = false;
    tx->createBranch<int>("higgsdecay", writeToTree);
    tx->createBranch<int>("wstar_channel_id", writeToTree);
    tx->createBranch<int>("nlep", writeToTree);
    tx->createBranch<int>("nquark", writeToTree);
    tx->createBranch<int>("wa_id", writeToTree);
    tx->createBranch<float>("isr_pt", writeToTree);
    tx->createBranch<float>("isr_eta", writeToTree);
    tx->createBranch<float>("isr_phi", writeToTree);
    tx->createBranch<vector<LV>>("decay_p4", writeToTree);
    tx->createBranch<vector<int>>("decay_id", writeToTree);
    tx->createBranch<vector<int>>("decay_isstar", writeToTree);
    tx->createBranch<vector<LV>>("lepton_p4", writeToTree);
    tx->createBranch<vector<int>>("lepton_id", writeToTree);
    tx->createBranch<vector<int>>("lepton_isstar", writeToTree);
    tx->createBranch<vector<LV>>("neutrino_p4", writeToTree);
    tx->createBranch<vector<int>>("neutrino_id", writeToTree);
    tx->createBranch<vector<int>>("neutrino_isstar", writeToTree);
    tx->createBranch<vector<LV>>("quark_p4", writeToTree);
    tx->createBranch<vector<int>>("quark_id", writeToTree);
    tx->createBranch<vector<int>>("quark_isstar", writeToTree);

    tx->createBranch<LV>("gen_isr_p4");
    tx->createBranch<int>("gen_isr_id");
    tx->createBranch<LV>("gen_higgs_p4");
    tx->createBranch<LV>("gen_whad_p4");
    tx->createBranch<LV>("gen_wlep_p4");
    tx->createBranch<LV>("gen_q0_p4");
    tx->createBranch<LV>("gen_q1_p4");
    tx->createBranch<LV>("gen_lep_p4");
    tx->createBranch<LV>("gen_neu_p4");
    tx->createBranch<int>("gen_channel");
    tx->createBranch<LV>("gen_wlep_rest_p4");
    tx->createBranch<LV>("gen_whad_rest_p4");
    tx->createBranch<LV>("gen_Vq0_p4");
    tx->createBranch<LV>("gen_Vq1_p4");

    tx->createBranch<float>("lqq_max_dr");
    tx->createBranch<float>("lq0_dr");
    tx->createBranch<float>("lq1_dr");
    tx->createBranch<float>("qq_dr");
    tx->createBranch<float>("decay_dr");
    tx->createBranch<float>("l_qq_dr");
    tx->createBranch<float>("lqq_mass");
    tx->createBranch<float>("lvqq_mt");
    tx->createBranch<float>("lvqq_rest_mt");
    tx->createBranch<float>("lq0_mass");
    tx->createBranch<float>("lq1_mass");
    tx->createBranch<float>("lq0_rho");
    tx->createBranch<float>("lq1_rho");
    tx->createBranch<float>("lq0_deg");
    tx->createBranch<float>("lq1_deg");

}

void hwwBabyMaker::HWWlvjjTruthModule::AddOutput_HWW()
{

    tx->createBranch<LV>("gen_recoil_p4"); // This is the p4 of the associated W/Z
    tx->createBranch<int>("gen_recoil_id"); // This is the id of the associated W/Z
    tx->createBranch<LV>("gen_higgs_p4");
    tx->createBranch<LV>("gen_whad_p4");
    tx->createBranch<LV>("gen_wlep_p4");
    tx->createBranch<LV>("gen_q0_p4");
    tx->createBranch<LV>("gen_q1_p4");
    tx->createBranch<LV>("gen_lep_p4");
    tx->createBranch<LV>("gen_neu_p4");
    tx->createBranch<int>("gen_channel");
    tx->createBranch<LV>("gen_wlep_rest_p4");
    tx->createBranch<LV>("gen_whad_rest_p4");
    tx->createBranch<LV>("gen_Vq0_p4");
    tx->createBranch<LV>("gen_Vq1_p4");
    tx->createBranch<int>("gen_Vq0_id");
    tx->createBranch<int>("gen_Vq1_id");
    tx->createBranch<int>("gen_q0_id");
    tx->createBranch<int>("gen_q1_id");
    tx->createBranch<int>("gen_lep_id");
    tx->createBranch<int>("gen_neu_id");

}

void hwwBabyMaker::HWWlvjjTruthModule::FillOutput()
{
//    if (babymaker->looper.getCurrentFileName().Contains("HToWWToLNuQQ"))
//    {
//        FillOutput_ggHToWWToLNuQQ();
//    }
//    else if(babymaker->looper.getCurrentFileName().Contains("VHToNonbb"))
//    {
        FillOutput_HWW();
//    }
}

void hwwBabyMaker::HWWlvjjTruthModule::FillOutput_HWW()
{

    // Find the ISR particle if it exists and set the ISR variables
    bool recoil_set = false;
    int recoil_idx = -1;
    for (unsigned int i = 0; i < cms3.genps_p4().size(); ++i)
    {

        // If the recoil is based on a vector boson
        if ((abs(cms3.genps_id()[i]) == 24 or abs(cms3.genps_id()[i]) == 23) and cms3.genps_id_simplemother()[i] != 25 and cms3.genps_status()[i] == 22)
        {
            tx->setBranch<LV>("gen_recoil_p4", cms3.genps_p4()[i]);
            tx->setBranch<int>("gen_recoil_id", cms3.genps_id()[i]);
            recoil_set = true;
            recoil_idx = i;
            break;
        }

        // If the recoil is based on jet
        if (cms3.genps_id_simplemother()[i] == 21 and cms3.genps_id_simplegrandma()[i] == 2212 and cms3.genps_status()[i] == 23)
        {
            tx->setBranch<LV>("gen_recoil_p4", cms3.genps_p4()[i]);
            tx->setBranch<int>("gen_recoil_id", cms3.genps_id()[i]);
            recoil_set = true;
            recoil_idx = i;
            break;
        }
    }

    if (recoil_idx >= 0 and (abs(tx->getBranch<int>("gen_recoil_id")) == 24 or abs(tx->getBranch<int>("gen_recoil_id")) == 23))
    {

        int gen_recoil_id = abs(tx->getBranch<int>("gen_recoil_id"));

        int ichild = -1;
        int jchild = -1;
        if (gen_recoil_id == 23) babymaker->coreGenPart.matchDecay(recoil_idx, ichild, jchild, gen_recoil_id, babymaker->coreGenPart.isPairHadronicZDecay);
        if (gen_recoil_id == 24) babymaker->coreGenPart.matchDecay(recoil_idx, ichild, jchild, gen_recoil_id, babymaker->coreGenPart.isPairHadronicWDecay);

        if (ichild >= 0)
        {
            LV VqA_p4 = cms3.genps_p4()[ichild];
            LV VqB_p4 = cms3.genps_p4()[jchild];
            int VqA_id = cms3.genps_id()[ichild];
            int VqB_id = cms3.genps_id()[jchild];

            LV Vq0_p4 = VqA_p4.pt() > VqB_p4.pt() ? VqA_p4 : VqB_p4;
            LV Vq1_p4 = VqA_p4.pt() > VqB_p4.pt() ? VqB_p4 : VqA_p4;
            int Vq0_id = VqA_p4.pt() > VqB_p4.pt() ? VqA_id : VqB_id;
            int Vq1_id = VqA_p4.pt() > VqB_p4.pt() ? VqB_id : VqA_id;

            tx->setBranch<LV>("gen_Vq0_p4", Vq0_p4);
            tx->setBranch<LV>("gen_Vq1_p4", Vq1_p4);
            tx->setBranch<int>("gen_Vq0_id", Vq0_id);
            tx->setBranch<int>("gen_Vq1_id", Vq1_id);

        }

    }

    // From CoreUtil the HWW decay tree is identified
    std::vector<CoreUtil::genpart::Higgs> higgses = babymaker->coreGenPart.reconstructHWW();

    // But still perform a sanity check that the recovered HWW decay tree makes sense
    // Sanity check
    if (higgses.size() != 1)
    {
        std::cout <<  " higgses.size(): " << higgses.size() <<  std::endl;
        babymaker->coreGenPart.printAllParticles();
        exit(255);
    }

    if (higgses[0].HiggsDaughters.size() != 2)
    {
        std::cout <<  " higgses[0].HiggsDaughters.size(): " << higgses[0].HiggsDaughters.size() <<  std::endl;
        babymaker->coreGenPart.printAllParticles();
        exit(255);
    }

    if (higgses[0].HiggsGrandDaughters.size() != 4)
    {
        std::cout <<  " higgses[0].HiggsGrandDaughters.size(): " << higgses[0].HiggsGrandDaughters.size() <<  std::endl;
        babymaker->coreGenPart.printAllParticles();
        exit(255);
    }

    // Now check whether it is H->WW->lvjj decay channels

    // If not WW then return
    if (abs(higgses[0].HiggsDaughters[0].id) != 24 or abs(higgses[0].HiggsDaughters[0].id) != 24)
        return;

    // If WW->4q or WW->lvlv then return
    if (
        (abs(higgses[0].HiggsGrandDaughters[0].id) >= 11 and abs(higgses[0].HiggsGrandDaughters[0].id) <= 16 and abs(higgses[0].HiggsGrandDaughters[2].id) >= 11 and abs(higgses[0].HiggsGrandDaughters[2].id) <= 16)
        or
        (abs(higgses[0].HiggsGrandDaughters[0].id) >=  1 and abs(higgses[0].HiggsGrandDaughters[0].id) <=  6 and abs(higgses[0].HiggsGrandDaughters[2].id) >=  1 and abs(higgses[0].HiggsGrandDaughters[2].id) <=  6)
       )
        return;

    bool is_first_set_whad = abs(higgses[0].HiggsGrandDaughters[0].id) >= 1 and abs(higgses[0].HiggsGrandDaughters[0].id) <= 6;
    int whad_idx = is_first_set_whad ? 0 : 1;
    int wlep_idx = is_first_set_whad ? 1 : 0;
    int qA_idx = is_first_set_whad ? 0 : 2;
    int qB_idx = is_first_set_whad ? 1 : 3;
    int q0_idx = higgses[0].HiggsGrandDaughters[qA_idx].p4.pt() > higgses[0].HiggsGrandDaughters[qB_idx].p4.pt() ? qA_idx : qB_idx;
    int q1_idx = higgses[0].HiggsGrandDaughters[qA_idx].p4.pt() > higgses[0].HiggsGrandDaughters[qB_idx].p4.pt() ? qB_idx : qA_idx;
    bool is_first_lepton_charged = is_first_set_whad ? abs(higgses[0].HiggsGrandDaughters[2].id) % 2 == 1 : abs(higgses[0].HiggsGrandDaughters[0].id) % 2 == 1;
    int lep_idx = is_first_set_whad ? (is_first_lepton_charged ? 2 : 3) : (is_first_lepton_charged ? 0 : 1);
    int neu_idx = is_first_set_whad ? (is_first_lepton_charged ? 3 : 2) : (is_first_lepton_charged ? 1 : 0);

    LV whad_p4 = higgses[0].HiggsDaughters[whad_idx].p4;
    LV wlep_p4 = higgses[0].HiggsDaughters[wlep_idx].p4;
    LV q0_p4   = higgses[0].HiggsGrandDaughters[q0_idx].p4;
    LV q1_p4   = higgses[0].HiggsGrandDaughters[q1_idx].p4;
    LV lep_p4  = higgses[0].HiggsGrandDaughters[lep_idx].p4;
    LV neu_p4  = higgses[0].HiggsGrandDaughters[neu_idx].p4;

    tx->setBranch<LV>("gen_higgs_p4", higgses[0].p4);
    tx->setBranch<LV>("gen_whad_p4", higgses[0].HiggsDaughters[whad_idx].p4);
    tx->setBranch<LV>("gen_wlep_p4", higgses[0].HiggsDaughters[wlep_idx].p4);
    tx->setBranch<LV>("gen_q0_p4", higgses[0].HiggsGrandDaughters[q0_idx].p4);
    tx->setBranch<LV>("gen_q1_p4", higgses[0].HiggsGrandDaughters[q1_idx].p4);
    tx->setBranch<LV>("gen_lep_p4", higgses[0].HiggsGrandDaughters[lep_idx].p4);
    tx->setBranch<LV>("gen_neu_p4", higgses[0].HiggsGrandDaughters[neu_idx].p4);
//    tx->setBranch<int>("gen_channel");
//    tx->setBranch<LV>("gen_wlep_rest_p4");
//    tx->setBranch<LV>("gen_whad_rest_p4");
//    tx->setBranch<LV>("gen_Vq0_p4");
//    tx->setBranch<LV>("gen_Vq1_p4");
    tx->setBranch<int>("gen_q0_id", higgses[0].HiggsGrandDaughters[q0_idx].id);
    tx->setBranch<int>("gen_q1_id", higgses[0].HiggsGrandDaughters[q1_idx].id);
    tx->setBranch<int>("gen_lep_id", higgses[0].HiggsGrandDaughters[lep_idx].id);
    tx->setBranch<int>("gen_neu_id", higgses[0].HiggsGrandDaughters[neu_idx].id);

}

void hwwBabyMaker::HWWlvjjTruthModule::FillOutput_ggHToWWToLNuQQ()
{

    // Find the ISR particle if it exists and set the ISR variables
    for (unsigned int i = 0; i < cms3.genps_p4().size(); ++i)
    {
        if (cms3.genps_id_simplemother()[i] == 21 && cms3.genps_id_simplegrandma()[i] == 2212 && cms3.genps_status()[i] == 23)
        {
            tx->setBranch<LV>("gen_isr_p4", cms3.genps_p4()[i]);
            tx->setBranch<float>("isr_pt", cms3.genps_p4()[i].pt());
            tx->setBranch<float>("isr_eta", cms3.genps_p4()[i].eta());
            tx->setBranch<float>("isr_phi", cms3.genps_p4()[i].phi());
            tx->setBranch<int>("gen_isr_id", cms3.genps_id()[i]);
            break;
        }
    }

    // From CoreUtil the HWWlvjj decay tree is identified
    std::vector<CoreUtil::genpart::Higgs> higgses = babymaker->coreGenPart.reconstructHWWlvjj();

    // But still perform a sanity check that the recovered HWWlvjj decay tree makes sense
    // Sanity check
    if (higgses.size() != 1)
    {
        std::cout <<  " higgses.size(): " << higgses.size() <<  std::endl;
        babymaker->coreGenPart.printAllParticles();
    }

    if (higgses[0].HiggsDaughters.size() != 2)
    {
        std::cout <<  " higgses[0].HiggsDaughters.size(): " << higgses[0].HiggsDaughters.size() <<  std::endl;
        babymaker->coreGenPart.printAllParticles();
    }

    if (higgses[0].HiggsGrandDaughters.size() != 4)
    {
        std::cout <<  " higgses[0].HiggsGrandDaughters.size(): " << higgses[0].HiggsGrandDaughters.size() <<  std::endl;
        babymaker->coreGenPart.printAllParticles();
    }

    // Now write the result into variables
    vector<LV> higgs_p4;

    vector<LV> higgsdecay_p4;
    vector<int> higgsdecay_id;
    vector<int> higgsdecay_isstar;

    vector<LV> lepton_p4;
    vector<int> lepton_id;
    vector<int> lepton_mid;
    vector<int> lepton_isstar;

    vector<LV> neutrino_p4;
    vector<int> neutrino_id;
    vector<int> neutrino_mid;
    vector<int> neutrino_isstar;

    vector<LV> quark_p4;
    vector<int> quark_id;
    vector<int> quark_mid;
    vector<int> quark_isstar;

    higgs_p4.push_back(higgses[0].p4);

    for (unsigned int i = 0; i < higgses[0].HiggsDaughters.size(); ++i)
    {
        higgsdecay_p4.push_back(higgses[0].HiggsDaughters[i].p4);
        higgsdecay_id.push_back(higgses[0].HiggsDaughters[i].id);
        higgsdecay_isstar.push_back(higgses[0].HiggsDaughters[i].isstar);
    }

    for (unsigned int i = 0; i < higgses[0].HiggsGrandDaughters.size(); ++i)
    {
        int absid = abs(higgses[0].HiggsGrandDaughters[i].id);
        if (absid == 11 || absid == 13 || absid == 15)
        {
            lepton_p4.push_back(higgses[0].HiggsGrandDaughters[i].p4);
            lepton_id.push_back(higgses[0].HiggsGrandDaughters[i].id);
            lepton_mid.push_back(higgses[0].HiggsGrandDaughters[i].motherid);
        }
        else if (absid == 12 || absid == 14 || absid == 16)
        {
            neutrino_p4.push_back(higgses[0].HiggsGrandDaughters[i].p4);
            neutrino_id.push_back(higgses[0].HiggsGrandDaughters[i].id);
            neutrino_mid.push_back(higgses[0].HiggsGrandDaughters[i].motherid);
        }
        else if (absid >= 1 && absid <= 5)
        {
            quark_p4.push_back(higgses[0].HiggsGrandDaughters[i].p4);
            quark_id.push_back(higgses[0].HiggsGrandDaughters[i].id);
            quark_mid.push_back(higgses[0].HiggsGrandDaughters[i].motherid);
        }
    }

    if (higgsdecay_isstar[0] == higgsdecay_isstar[1])
    {
        higgsdecay_isstar.clear();
        higgsdecay_isstar.push_back(higgsdecay_p4[0].mass() > higgsdecay_p4[1].mass() ? 0 : 1);
        higgsdecay_isstar.push_back(higgsdecay_p4[0].mass() > higgsdecay_p4[1].mass() ? 1 : 0);
    }


    // Perform a sanity check that we have only two decaying particle directly from higgs
    if (higgsdecay_id.size() != 2)
    {
        std::cout <<  " babymaker->looper.getCurrentEventIndex(): " << babymaker->looper.getCurrentEventIndex() <<  std::endl;
        std::cout <<  " higgsdecay_id.size(): " << higgsdecay_id.size() <<  std::endl;
        babymaker->coreGenPart.printParticleOfInterest();
        exit(255);
    }

    // Perofrm a sanity check that there are one lepton
    if (lepton_id.size() != 1)
    {
        std::cout <<  " babymaker->looper.getCurrentEventIndex(): " << babymaker->looper.getCurrentEventIndex() <<  std::endl;
        std::cout <<  " lepton_id.size(): " << lepton_id.size() <<  " quark_id.size(): " << quark_id.size() <<  std::endl;
        for (unsigned int ii = 0; ii < lepton_id.size(); ++ ii)
            std::cout <<  " lepton_id[ii]: " << lepton_id[ii] <<  " lepton_p4[ii].pt(): " << lepton_p4[ii].pt() <<  std::endl;

        babymaker->coreGenPart.printParticleOfInterest();
        babymaker->coreGenPart.printAllParticles();

        // Sanity Check
        higgses[0].HiggsGrandDaughters[0].print();
        higgses[0].HiggsGrandDaughters[1].print();
        higgses[0].HiggsGrandDaughters[2].print();
        higgses[0].HiggsGrandDaughters[3].print();
        higgses[0].HiggsDaughters[0].print();
        higgses[0].HiggsDaughters[1].print();
        higgses[0].print();
        CoreUtil::genpart::printLorentzVector(higgses[0].HiggsGrandDaughters[0].p4);
        CoreUtil::genpart::printLorentzVector(higgses[0].HiggsGrandDaughters[1].p4);
        CoreUtil::genpart::printLorentzVector(higgses[0].HiggsGrandDaughters[2].p4);
        CoreUtil::genpart::printLorentzVector(higgses[0].HiggsGrandDaughters[3].p4);
        CoreUtil::genpart::printLorentzVector(higgses[0].HiggsGrandDaughters[0].p4 + higgses[0].HiggsGrandDaughters[1].p4);
        CoreUtil::genpart::printLorentzVector(higgses[0].HiggsGrandDaughters[2].p4 + higgses[0].HiggsGrandDaughters[3].p4);
        CoreUtil::genpart::printLorentzVector(higgses[0].HiggsDaughters[0].p4);
        CoreUtil::genpart::printLorentzVector(higgses[0].HiggsDaughters[1].p4);
        CoreUtil::genpart::printLorentzVector(higgses[0].HiggsDaughters[0].p4 + higgses[0].HiggsDaughters[1].p4);
        CoreUtil::genpart::printLorentzVector(higgses[0].p4);

        exit(255);
    }

    // Perform a sanity check that there are only two quarks
    if (quark_id.size() != 2)
    {
        std::cout <<  " babymaker->looper.getCurrentEventIndex(): " << babymaker->looper.getCurrentEventIndex() <<  std::endl;
        std::cout <<  " lepton_id.size(): " << lepton_id.size() <<  " quark_id.size(): " << quark_id.size() <<  std::endl;
        babymaker->coreGenPart.printParticleOfInterest();
        exit(255);
    }

    // Save information for H
    tx->setBranch<LV>("gen_higgs_p4", higgs_p4[0]);

    // Save information for H->XX
    tx->setBranch<int>("higgsdecay", abs(higgsdecay_id[0]));
    tx->setBranch<vector<LV>>("decay_p4", higgsdecay_p4);
    tx->setBranch<vector<int>>("decay_id", higgsdecay_id);
    tx->setBranch<vector<int>>("decay_isstar", higgsdecay_isstar);
    tx->sortVecBranchesByPt("decay_p4", {}, {"decay_id", "decay_isstar"}, {});

//    // Compute and fill the boosted variables as well as toe rotation
//    // This also returns the reference vector
//    float deta0, dphi0;
//    float deta250, dphi250;
//    float deta500, dphi500;
//    float deta1000, dphi1000;
//    float deta1500, dphi1500;
//    std::tie(deta0, dphi0) = FillReBoostedVariables("decay"  , 0  , higgs_p4[0] , higgsdecay_p4 , higgsdecay_id , higgsdecay_isstar );
//    std::tie(deta250, dphi250) = FillReBoostedVariables("decay"  , 250  , higgs_p4[0] , higgsdecay_p4 , higgsdecay_id , higgsdecay_isstar );
//    std::tie(deta500, dphi500) = FillReBoostedVariables("decay"  , 500  , higgs_p4[0] , higgsdecay_p4 , higgsdecay_id , higgsdecay_isstar );
//    std::tie(deta1000, dphi1000) = FillReBoostedVariables("decay"  , 1000 , higgs_p4[0] , higgsdecay_p4 , higgsdecay_id , higgsdecay_isstar );
//    std::tie(deta1500, dphi1500) = FillReBoostedVariables("decay"  , 1500 , higgs_p4[0] , higgsdecay_p4 , higgsdecay_id , higgsdecay_isstar );

    tx->setBranch<float>("decay_dr", RooUtil::Calc::DeltaR(higgsdecay_p4[0], higgsdecay_p4[1]));

    // If not WW stop here and move on
    if (abs(higgsdecay_id[0]) != 24) return;

    // First save the information about the leptonic/hadronic channel information
    tx->setBranch<int>("nlep", lepton_id.size());
    tx->setBranch<int>("nquark", quark_id.size());

    // Determining which lepton or quarks had the mother of off-shell W
    int wstar_id = 0;
    for (unsigned i = 0; i < higgsdecay_id.size(); ++i)
    {
        if (higgsdecay_isstar[i]) // Perhaps you "could" have 62.5 and 62.5 ..? probably very unlikely
        {
            wstar_id = higgsdecay_id[i];
            break;
        }
    }

    // Finding off-shell failed. Sanity check.
    if (wstar_id == 0)
    {
        std::cout << "Failed to find off-shell W" << std::endl;
        babymaker->FATALERROR(__FUNCTION__);
    }

    // Compute whether specific quark or lepton had a off-shell mother or not
    for (auto& id : lepton_mid) lepton_isstar.push_back(id == wstar_id);
    for (auto& id : quark_mid ) quark_isstar .push_back(id == wstar_id);
    for (auto& id : neutrino_mid) neutrino_isstar.push_back(id == wstar_id);

    // Save lepton and quark information
    tx->setBranch<vector<LV>>("lepton_p4", lepton_p4);
    tx->setBranch<vector<int>>("lepton_id", lepton_id);
    tx->setBranch<vector<int>>("lepton_isstar", lepton_isstar);
    tx->setBranch<vector<LV>>("neutrino_p4", neutrino_p4);
    tx->setBranch<vector<int>>("neutrino_id", neutrino_id);
    tx->setBranch<vector<int>>("neutrino_isstar", neutrino_isstar);
    tx->sortVecBranchesByPt("lepton_p4", {}, {"lepton_id", "lepton_isstar"}, {});
    tx->setBranch<vector<LV>>("quark_p4", quark_p4);
    tx->setBranch<vector<int>>("quark_id", quark_id);
    tx->setBranch<vector<int>>("quark_isstar", quark_isstar);
    tx->sortVecBranchesByPt("quark_p4", {}, {"quark_id", "quark_isstar"}, {});

    const vector<LV>& lepton_p4_ = tx->getBranch<vector<LV>>("lepton_p4", true);
    const vector<LV>& quark_p4_ = tx->getBranch<vector<LV>>("quark_p4", true);
    const LV& l_p4 = lepton_p4_[0];
    const LV& q0_p4 = quark_p4_[0];
    const LV& q1_p4 = quark_p4_[1];
    float lq0_dr = RooUtil::Calc::DeltaR(l_p4, q0_p4);
    float lq1_dr = RooUtil::Calc::DeltaR(l_p4, q1_p4);
    float q0q1_dr = RooUtil::Calc::DeltaR(q0_p4, q1_p4);
    float l_qq_dr = RooUtil::Calc::DeltaR(l_p4, (q0_p4 + q1_p4));
    tx->setBranch<float>("lqq_max_dr", max(lq0_dr, max(lq1_dr, q0q1_dr)));
    tx->setBranch<float>("lq0_dr", lq0_dr);
    tx->setBranch<float>("lq1_dr", lq1_dr);
    tx->setBranch<float>("qq_dr", q0q1_dr);
    tx->setBranch<float>("l_qq_dr", l_qq_dr);
    tx->setBranch<float>("lq0_rho", RooUtil::Calc::getRho(l_p4, q0_p4));
    tx->setBranch<float>("lq1_rho", RooUtil::Calc::getRho(l_p4, q1_p4));
    tx->setBranch<float>("lq0_deg", TMath::RadToDeg()*RooUtil::Calc::getRho(l_p4, q0_p4));
    tx->setBranch<float>("lq1_deg", TMath::RadToDeg()*RooUtil::Calc::getRho(l_p4, q1_p4));

    if ((lepton_isstar[0] == 0) && (higgsdecay_isstar[0] == 0))
    {
        tx->setBranch<int>("wstar_channel_id", 0);
        tx->setBranch<int>("gen_channel", -1);
    }
    else if ((lepton_isstar[0] == 1) && (higgsdecay_isstar[0] == 1))
    {
        tx->setBranch<int>("wstar_channel_id", 1);
        tx->setBranch<int>("gen_channel", -2);
    }
    else if ((lepton_isstar[0] == 0) && (higgsdecay_isstar[1] == 0))
    {
        tx->setBranch<int>("wstar_channel_id", 2);
        tx->setBranch<int>("gen_channel", 2);
    }
    else if ((lepton_isstar[0] == 1) && (higgsdecay_isstar[1] == 1))
    {
        tx->setBranch<int>("wstar_channel_id", 3);
        tx->setBranch<int>("gen_channel", 1);
    }
    else
    {
        babymaker->coreGenPart.printParticleOfInterest();
        std::cout <<  " higgsdecay_p4[0].mass(): " << higgsdecay_p4[0].mass() <<  std::endl;
        std::cout <<  " higgsdecay_p4[1].mass(): " << higgsdecay_p4[1].mass() <<  std::endl;
        std::cout <<  " higgsdecay_isstar[0]: " << higgsdecay_isstar[0] <<  std::endl;
        std::cout <<  " higgsdecay_isstar[1]: " << higgsdecay_isstar[1] <<  std::endl;
        std::cout << "Failed to classify events" << std::endl;
        babymaker->FATALERROR(__FUNCTION__);
    }

    // lqq mass
    tx->setBranch<float>("lqq_mass", (lepton_p4[0] + quark_p4[0] + quark_p4[1]).mass());
    tx->setBranch<float>("lvqq_mt", (lepton_p4[0] + neutrino_p4[0] + quark_p4[0] + quark_p4[1]).mt());

    TLorentzVector vpt_tlv;
    vpt_tlv.SetPtEtaPhiM(neutrino_p4[0].pt(), 0, neutrino_p4[0].phi(), 0);
    LV vpt = RooUtil::Calc::getLV(vpt_tlv);
    LV gen_higgs = (lepton_p4[0] + vpt + quark_p4[0] + quark_p4[1]);

    RooUtil::Calc::boost(gen_higgs, -RooUtil::Calc::boostVector(gen_higgs));
    tx->setBranch<float>("lvqq_rest_mt", gen_higgs.mt());

    tx->setBranch<float>("lq0_mass", (lepton_p4[0] + quark_p4[0]).mass());
    tx->setBranch<float>("lq1_mass", (lepton_p4[0] + quark_p4[1]).mass());


    // Summarizing all the 4-vectors and saving them
    tx->setBranch<LV>("gen_lep_p4", lepton_p4[0]);
    tx->setBranch<LV>("gen_neu_p4", neutrino_p4[0]);
    tx->setBranch<LV>("gen_q0_p4", quark_p4[0]);
    tx->setBranch<LV>("gen_q1_p4", quark_p4[1]);
    tx->setBranch<LV>("gen_whad_p4", (quark_p4[0] + quark_p4[1]));
    tx->setBranch<LV>("gen_wlep_p4", (lepton_p4[0] + neutrino_p4[0]));

    LV gen_wlep = (lepton_p4[0] + neutrino_p4[0]);
    RooUtil::Calc::boost(gen_wlep, -RooUtil::Calc::boostVector(gen_wlep));
    tx->setBranch<LV>("gen_wlep_rest_p4", gen_wlep);
    LV gen_whad = (quark_p4[0] + quark_p4[1]);
    RooUtil::Calc::boost(gen_whad, -RooUtil::Calc::boostVector(gen_whad));
    tx->setBranch<LV>("gen_whad_rest_p4", gen_whad);

    return;

}

//==============================================================================================================
//
// Higgs Reco Module
//
//==============================================================================================================

void hwwBabyMaker::HiggsRecoModule::AddOutput()
{
    tx->createBranch<LV>("J_p4");
    tx->createBranch<float>("dphi_met_J");
    tx->createBranch<LV>("Jmet_p4");

    tx->createBranch<LV>("L_p4");
    tx->createBranch<LV>("Lmet_p4");
    tx->createBranch<LV>("QQ_p4"); // this is Fat-jet minus Lepton. (fat-jet is assumed to clustered along with lepton so lepton subtracted fat-jet will be identified as the W->qq)
    tx->createBranch<float>("dr_L_QQ");
    tx->createBranch<LV>("QQp_p4"); // this is Fat-jet minus Lepton only when fat-jet minus lepton has positive mass.
    tx->createBranch<float>("dr_L_QQp");

    tx->createBranch<LV>("LQQ_p4");
    tx->createBranch<LV>("LQQp_p4");

    tx->createBranch<LV>("H_p4");
    tx->createBranch<LV>("Hp_p4");

    tx->createBranch<int>("is_whad_lead");

    tx->createBranch<LV>("neu_p4");
    tx->createBranch<LV>("neu_p4_sol1");
    tx->createBranch<LV>("neu_p4_sol2");
    tx->createBranch<LV>("neu_p4_invsol1");
    tx->createBranch<LV>("neu_p4_invsol2");

    tx->createBranch<LV>("V_p4");

    // Selected ak8jets associated information
    tx->createBranch<float>("J_undoJEC");
    tx->createBranch<float>("J_area");
    tx->createBranch<float>("J_mass");
    tx->createBranch<float>("J_softdropMass");
    tx->createBranch<float>("J_nJettinessTau1");
    tx->createBranch<float>("J_nJettinessTau2");
    tx->createBranch<float>("J_nJettinessTau3");
    tx->createBranch<float>("J_deep_rawdisc_h4q");
    tx->createBranch<float>("J_deep_rawdisc_hbb");
    tx->createBranch<float>("J_deep_rawdisc_qcd");
    tx->createBranch<float>("J_deep_rawdisc_top");
    tx->createBranch<float>("J_deep_rawdisc_w");
    tx->createBranch<float>("J_deep_rawdisc_z");
    tx->createBranch<float>("J_deep_rawdisc_zbb");
    tx->createBranch<float>("J_deep_bindisc_h4q");
    tx->createBranch<float>("J_deep_bindisc_hbb");
    tx->createBranch<float>("J_deep_bindisc_top");
    tx->createBranch<float>("J_deep_bindisc_w");
    tx->createBranch<float>("J_deep_bindisc_z");
    tx->createBranch<float>("J_deep_bindisc_zbb");
    tx->createBranch<float>("J_softdropPuppiSubjet1_pt");
    tx->createBranch<float>("J_softdropPuppiSubjet1_eta");
    tx->createBranch<float>("J_softdropPuppiSubjet1_phi");
    tx->createBranch<float>("J_softdropPuppiSubjet1_mass");
    tx->createBranch<float>("J_softdropPuppiSubjet1_energy");
    tx->createBranch<float>("J_softdropPuppiSubjet2_pt");
    tx->createBranch<float>("J_softdropPuppiSubjet2_eta");
    tx->createBranch<float>("J_softdropPuppiSubjet2_phi");
    tx->createBranch<float>("J_softdropPuppiSubjet2_mass");
    tx->createBranch<float>("J_softdropPuppiSubjet2_energy");
    tx->createBranch<int>("J_npfcands");
    tx->createBranch<int>("J_partonFlavour");

    // Selected lepton associated information
    tx->createBranch<int>("L_id");
    tx->createBranch<int>("L_idx");
    tx->createBranch<int>("L_isTightPOG");
    tx->createBranch<float>("L_miniIsoEA");
    tx->createBranch<float>("L_relIso03EA");
    tx->createBranch<float>("L_relIso04DB");
    tx->createBranch<float>("L_customrelIso005EA");
    tx->createBranch<float>("L_customrelIso01EA");
    tx->createBranch<float>("L_ip3d");
    tx->createBranch<float>("L_ip3derr");
    tx->createBranch<float>("L_dxy");
    tx->createBranch<float>("L_dz");

    // ak4jets nearby fatjet
    tx->createBranch<LV>("J_nearest_ak4jet_p4", false);
    tx->createBranch<vector<LV>>("J_near_ak4jets_p4");

    // Some derived quantities
    tx->createBranch<LV>("L_subjet1_p4");
    tx->createBranch<LV>("L_subjet2_p4");
    tx->createBranch<float>("L_subjet1_dr");
    tx->createBranch<float>("L_subjet2_dr");
    tx->createBranch<float>("L_subjet1_deg");
    tx->createBranch<float>("L_subjet2_deg");

    // Selected ak8jets associated information
    tx->createBranch<float>("V_area");
    tx->createBranch<float>("V_mass");
    tx->createBranch<float>("V_softdropMass");
    tx->createBranch<float>("V_nJettinessTau1");
    tx->createBranch<float>("V_nJettinessTau2");
    tx->createBranch<float>("V_nJettinessTau3");
    tx->createBranch<float>("V_deep_rawdisc_h4q");
    tx->createBranch<float>("V_deep_rawdisc_hbb");
    tx->createBranch<float>("V_deep_rawdisc_qcd");
    tx->createBranch<float>("V_deep_rawdisc_top");
    tx->createBranch<float>("V_deep_rawdisc_w");
    tx->createBranch<float>("V_deep_rawdisc_z");
    tx->createBranch<float>("V_deep_rawdisc_zbb");
    tx->createBranch<float>("V_deep_bindisc_h4q");
    tx->createBranch<float>("V_deep_bindisc_hbb");
    tx->createBranch<float>("V_deep_bindisc_top");
    tx->createBranch<float>("V_deep_bindisc_w");
    tx->createBranch<float>("V_deep_bindisc_z");
    tx->createBranch<float>("V_deep_bindisc_zbb");
    tx->createBranch<float>("V_softdropPuppiSubjet1_pt");
    tx->createBranch<float>("V_softdropPuppiSubjet1_eta");
    tx->createBranch<float>("V_softdropPuppiSubjet1_phi");
    tx->createBranch<float>("V_softdropPuppiSubjet1_mass");
    tx->createBranch<float>("V_softdropPuppiSubjet1_energy");
    tx->createBranch<float>("V_softdropPuppiSubjet2_pt");
    tx->createBranch<float>("V_softdropPuppiSubjet2_eta");
    tx->createBranch<float>("V_softdropPuppiSubjet2_phi");
    tx->createBranch<float>("V_softdropPuppiSubjet2_mass");
    tx->createBranch<float>("V_softdropPuppiSubjet2_energy");
    tx->createBranch<int>("V_npfcands");
    tx->createBranch<int>("V_partonFlavour");

    AddOutput_Htag();
}

void hwwBabyMaker::HiggsRecoModule::AddOutput_Htag()
{

    // Higgs HWWlvjj tagger machine learning inputs
    // PF candidates within R=1.0 centered around the J vector
    tx->createBranch<LV>("Htag_J_p4");
    tx->createBranch<float>("Htag_J_pt");
    tx->createBranch<float>("Htag_J_eta");
    tx->createBranch<float>("Htag_J_phi");
    tx->createBranch<float>("Htag_J_mass");
    tx->createBranch<float>("Htag_J_softdropMass");
    tx->createBranch<LV>("Htag_L_p4");
    tx->createBranch<float>("Htag_L_pt");
    tx->createBranch<float>("Htag_L_eta");
    tx->createBranch<float>("Htag_L_phi");
    tx->createBranch<float>("Htag_L_dr");
    tx->createBranch<float>("Htag_L_alpha");
    tx->createBranch<vector<LV>>("Htag_pf_p4");
    tx->createBranch<vector<float>>("Htag_pf_pt");
    tx->createBranch<vector<float>>("Htag_pf_eta");
    tx->createBranch<vector<float>>("Htag_pf_phi");
    tx->createBranch<vector<int>>("Htag_pf_id");
    tx->createBranch<vector<float>>("Htag_pf_dr");
    tx->createBranch<vector<float>>("Htag_pf_alpha");
    tx->createBranch<vector<float>>("Htag_pf_puppi_wgt");
    tx->createBranch<vector<float>>("Htag_pf_ptfrac");
    tx->createBranch<vector<float>>("Htag_pf_ptrel");
    tx->createBranch<vector<LV>>("Htag_pf_nolep_p4");
    tx->createBranch<vector<float>>("Htag_pf_nolep_pt");
    tx->createBranch<vector<float>>("Htag_pf_nolep_eta");
    tx->createBranch<vector<float>>("Htag_pf_nolep_phi");
    tx->createBranch<vector<int>>("Htag_pf_nolep_id");
    tx->createBranch<vector<float>>("Htag_pf_nolep_dr");
    tx->createBranch<vector<float>>("Htag_pf_nolep_alpha");
    tx->createBranch<vector<float>>("Htag_pf_nolep_puppi_wgt");
    tx->createBranch<vector<float>>("Htag_pf_nolep_ptfrac");
    tx->createBranch<vector<float>>("Htag_pf_nolep_ptrel");
    tx->createBranch<vector<LV>>("Htag_ak4_p4");
    tx->createBranch<vector<float>>("Htag_ak4_pt");
    tx->createBranch<vector<float>>("Htag_ak4_eta");
    tx->createBranch<vector<float>>("Htag_ak4_phi");
    tx->createBranch<vector<float>>("Htag_ak4_dr");
    tx->createBranch<vector<float>>("Htag_ak4_alpha");
    tx->createBranch<vector<float>>("Htag_ak4_L_dr");
    tx->createBranch<vector<float>>("Htag_ak4_L_dpt");
    tx->createBranch<vector<int>>("Htag_fromPV");
    tx->createBranch<vector<int>>("Htag_pv_quality");
    tx->createBranch<int>("Htag_leppffound");
    tx->createBranch<LV>("Htag_subjet1_p4");
    tx->createBranch<float>("Htag_subjet1_pt");
    tx->createBranch<float>("Htag_subjet1_eta");
    tx->createBranch<float>("Htag_subjet1_phi");
    tx->createBranch<float>("Htag_subjet1_dr");
    tx->createBranch<float>("Htag_subjet1_alpha");
    tx->createBranch<LV>("Htag_subjet2_p4");
    tx->createBranch<float>("Htag_subjet2_pt");
    tx->createBranch<float>("Htag_subjet2_eta");
    tx->createBranch<float>("Htag_subjet2_phi");
    tx->createBranch<float>("Htag_subjet2_dr");
    tx->createBranch<float>("Htag_subjet2_alpha");

    // Truth to reco matching study
    if (babymaker->looper.getCurrentFileName().Contains("HToWWToLNuQQ") or babymaker->looper.getCurrentFileName().Contains("VHToNonbb"))
    {
        tx->createBranch<float>("Htag_gen_higgs_dr");
        tx->createBranch<float>("Htag_gen_higgs_alpha");
        tx->createBranch<float>("Htag_gen_whad_dr");
        tx->createBranch<float>("Htag_gen_whad_alpha");
        tx->createBranch<float>("Htag_gen_wlep_dr");
        tx->createBranch<float>("Htag_gen_wlep_alpha");
        tx->createBranch<float>("Htag_gen_q0_dr");
        tx->createBranch<float>("Htag_gen_q0_alpha");
        tx->createBranch<float>("Htag_gen_q1_dr");
        tx->createBranch<float>("Htag_gen_q1_alpha");
        tx->createBranch<float>("Htag_gen_lep_dr");
        tx->createBranch<float>("Htag_gen_lep_alpha");
        tx->createBranch<float>("Htag_gen_neu_dr");
        tx->createBranch<float>("Htag_gen_neu_alpha");
    }

}

void hwwBabyMaker::HiggsRecoModule::FillOutput()
{

    // Get the MET 2-vector
    LV met = RooUtil::Calc::getLV(tx->getBranch<float>("met_pt", true), 0, tx->getBranch<float>("met_phi", true), 0);

    // Select the leptons and fat-jet
    LV L;
    int iL = -1;
    LV J;
    int iJ = -1;
    LV V;
    int iV = -1;
    std::tie(L, iL) = SelectLepton(met);
    // std::tie(J, iJ) = SelectFatJet(met);
    std::tie(J, iJ) = SelectFatJet(L + met);
    std::tie(V, iV) = SelectVbosonJet(J);

    // Found?
    if (iJ >= 0)
    {

        tx->setBranch<LV>("J_p4", J);
        tx->setBranch<LV>("Jmet_p4", J + met);
        tx->setBranch<float>("dphi_met_J", RooUtil::Calc::DeltaPhi(J, met));

    }

    // Found ?
    if (iL >= 0)
    {

        tx->setBranch<LV>("L_p4", L);
        tx->setBranch<LV>("Lmet_p4", L + met);

        if (iJ >= 0)
        {

            LV QQ = J - L;
            LV QQp = QQ.mass() > 0 ? QQ : J;
            tx->setBranch<LV>("QQ_p4", QQ);
            tx->setBranch<float>("dr_L_QQ", RooUtil::Calc::DeltaR(QQ, L));
            tx->setBranch<LV>("QQp_p4", QQp);
            tx->setBranch<float>("dr_L_QQp", RooUtil::Calc::DeltaR(QQp, L));

            // Now reconstructing Higgs
            LV H = QQ + L + met;
            LV Hp = QQp + L + met;
            tx->setBranch<LV>("H_p4", H);
            tx->setBranch<LV>("Hp_p4", Hp);

            // Just visibile system p4
            LV LQQ = QQ + L;
            LV LQQp = QQp + L;
            tx->setBranch<LV>("LQQ_p4", LQQ);
            tx->setBranch<LV>("LQQp_p4", LQQp);

        }

    }

    // Now set the associated information to each object

    if (iJ >= 0)
    {
        // Selected ak8jets associated information
        if (tx->getBranchLazy<vector<float>>("ak8jets_undoJEC"                     ).size() > 0) tx->setBranch<float>("J_undoJEC"                     , tx->getBranchLazy<vector<float>>("ak8jets_undoJEC"                     )[iJ]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_area"                        ).size() > 0) tx->setBranch<float>("J_area"                        , tx->getBranchLazy<vector<float>>("ak8jets_area"                        )[iJ]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_mass"                        ).size() > 0) tx->setBranch<float>("J_mass"                        , tx->getBranchLazy<vector<float>>("ak8jets_mass"                        )[iJ]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_softdropMass"                ).size() > 0) tx->setBranch<float>("J_softdropMass"                , tx->getBranchLazy<vector<float>>("ak8jets_softdropMass"                )[iJ]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_nJettinessTau1"              ).size() > 0) tx->setBranch<float>("J_nJettinessTau1"              , tx->getBranchLazy<vector<float>>("ak8jets_nJettinessTau1"              )[iJ]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_nJettinessTau2"              ).size() > 0) tx->setBranch<float>("J_nJettinessTau2"              , tx->getBranchLazy<vector<float>>("ak8jets_nJettinessTau2"              )[iJ]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_nJettinessTau3"              ).size() > 0) tx->setBranch<float>("J_nJettinessTau3"              , tx->getBranchLazy<vector<float>>("ak8jets_nJettinessTau3"              )[iJ]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_deep_rawdisc_h4q"            ).size() > 0) tx->setBranch<float>("J_deep_rawdisc_h4q"            , tx->getBranchLazy<vector<float>>("ak8jets_deep_rawdisc_h4q"            )[iJ]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_deep_rawdisc_hbb"            ).size() > 0) tx->setBranch<float>("J_deep_rawdisc_hbb"            , tx->getBranchLazy<vector<float>>("ak8jets_deep_rawdisc_hbb"            )[iJ]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_deep_rawdisc_qcd"            ).size() > 0) tx->setBranch<float>("J_deep_rawdisc_qcd"            , tx->getBranchLazy<vector<float>>("ak8jets_deep_rawdisc_qcd"            )[iJ]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_deep_rawdisc_top"            ).size() > 0) tx->setBranch<float>("J_deep_rawdisc_top"            , tx->getBranchLazy<vector<float>>("ak8jets_deep_rawdisc_top"            )[iJ]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_deep_rawdisc_w"              ).size() > 0) tx->setBranch<float>("J_deep_rawdisc_w"              , tx->getBranchLazy<vector<float>>("ak8jets_deep_rawdisc_w"              )[iJ]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_deep_rawdisc_z"              ).size() > 0) tx->setBranch<float>("J_deep_rawdisc_z"              , tx->getBranchLazy<vector<float>>("ak8jets_deep_rawdisc_z"              )[iJ]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_deep_rawdisc_zbb"            ).size() > 0) tx->setBranch<float>("J_deep_rawdisc_zbb"            , tx->getBranchLazy<vector<float>>("ak8jets_deep_rawdisc_zbb"            )[iJ]) ;
        // if (tx->getBranchLazy<vector<float>>("ak8jets_deep_bindisc_h4q"            ).size() > 0) tx->setBranch<float>("J_deep_bindisc_h4q"            , tx->getBranchLazy<vector<float>>("ak8jets_deep_bindisc_h4q"            )[iJ]) ;
        // if (tx->getBranchLazy<vector<float>>("ak8jets_deep_bindisc_hbb"            ).size() > 0) tx->setBranch<float>("J_deep_bindisc_hbb"            , tx->getBranchLazy<vector<float>>("ak8jets_deep_bindisc_hbb"            )[iJ]) ;
        // if (tx->getBranchLazy<vector<float>>("ak8jets_deep_bindisc_top"            ).size() > 0) tx->setBranch<float>("J_deep_bindisc_top"            , tx->getBranchLazy<vector<float>>("ak8jets_deep_bindisc_top"            )[iJ]) ;
        // if (tx->getBranchLazy<vector<float>>("ak8jets_deep_bindisc_w"              ).size() > 0) tx->setBranch<float>("J_deep_bindisc_w"              , tx->getBranchLazy<vector<float>>("ak8jets_deep_bindisc_w"              )[iJ]) ;
        // if (tx->getBranchLazy<vector<float>>("ak8jets_deep_bindisc_z"              ).size() > 0) tx->setBranch<float>("J_deep_bindisc_z"              , tx->getBranchLazy<vector<float>>("ak8jets_deep_bindisc_z"              )[iJ]) ;
        // if (tx->getBranchLazy<vector<float>>("ak8jets_deep_bindisc_zbb"            ).size() > 0) tx->setBranch<float>("J_deep_bindisc_zbb"            , tx->getBranchLazy<vector<float>>("ak8jets_deep_bindisc_zbb"            )[iJ]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet1_pt"     ).size() > 0) tx->setBranch<float>("J_softdropPuppiSubjet1_pt"     , tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet1_pt"     )[iJ]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet1_eta"    ).size() > 0) tx->setBranch<float>("J_softdropPuppiSubjet1_eta"    , tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet1_eta"    )[iJ]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet1_phi"    ).size() > 0) tx->setBranch<float>("J_softdropPuppiSubjet1_phi"    , tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet1_phi"    )[iJ]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet1_mass"   ).size() > 0) tx->setBranch<float>("J_softdropPuppiSubjet1_mass"   , tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet1_mass"   )[iJ]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet1_energy" ).size() > 0) tx->setBranch<float>("J_softdropPuppiSubjet1_energy" , tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet1_energy" )[iJ]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet2_pt"     ).size() > 0) tx->setBranch<float>("J_softdropPuppiSubjet2_pt"     , tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet2_pt"     )[iJ]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet2_eta"    ).size() > 0) tx->setBranch<float>("J_softdropPuppiSubjet2_eta"    , tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet2_eta"    )[iJ]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet2_phi"    ).size() > 0) tx->setBranch<float>("J_softdropPuppiSubjet2_phi"    , tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet2_phi"    )[iJ]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet2_mass"   ).size() > 0) tx->setBranch<float>("J_softdropPuppiSubjet2_mass"   , tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet2_mass"   )[iJ]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet2_energy" ).size() > 0) tx->setBranch<float>("J_softdropPuppiSubjet2_energy" , tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet2_energy" )[iJ]) ;
        if (tx->getBranchLazy<vector<int>>("ak8jets_npfcands"                      ).size() > 0) tx->setBranch<int>("J_npfcands"                      , tx->getBranchLazy<vector<int>>("ak8jets_npfcands"                      )[iJ]) ;
        if (tx->getBranchLazy<vector<int>>("ak8jets_partonFlavour"                 ).size() > 0) tx->setBranch<int>("J_partonFlavour"                 , tx->getBranchLazy<vector<int>>("ak8jets_partonFlavour"                 )[iJ]) ;

        // Aggregating nearby ak4 jets (R = 1.2) also select the nearest one

        // Selecting nearest one
        LV j;
        int ij = -1;
        float dr = 999;

        // Retrieving list of all ak4 jets
        const vector<LV>& alljets_p4 = tx->getBranch<vector<LV>>("alljets_p4", false);

        // Loop over jets
        for (unsigned int ii = 0; ii < alljets_p4.size(); ++ii)
        {

            // Retrieve the ak4 jet
            LV p4 = alljets_p4[ii];

            // Compute the dr
            float tmpdr = RooUtil::Calc::DeltaR(p4, J);

            // if nearby add to the list
            if (tmpdr < 1.2)
                tx->pushbackToBranch<LV>("J_near_ak4jets_p4", p4);

            // Select the nearest
            if (tmpdr < dr)
            {
                dr = tmpdr;
                j = p4;
                ij = ii;
            }

        }

        // Found ?
        if (ij >= 0)
            tx->setBranch<LV>("J_nearest_ak4jet_p4", j);


    }

    if (iL >= 0)
    {
        // Selected lepton associated information
        tx->setBranch<int>("L_id", tx->getBranch<vector<int>>("lep_id")[iL]);
        tx->setBranch<int>("L_idx", tx->getBranch<vector<int>>("lep_idx")[iL]);
        tx->setBranch<int>("L_isTightPOG", tx->getBranch<vector<int>>("lep_isTightPOG")[iL]);
        tx->setBranch<float>("L_miniIsoEA", tx->getBranch<vector<float>>("lep_miniIsoEA")[iL]);
        tx->setBranch<float>("L_relIso03EA", tx->getBranch<vector<float>>("lep_relIso03EA")[iL]);
        tx->setBranch<float>("L_relIso04DB", tx->getBranch<vector<float>>("lep_relIso04DB")[iL]);
        tx->setBranch<float>("L_customrelIso005EA", tx->getBranch<vector<float>>("lep_customrelIso005EA")[iL]);
        tx->setBranch<float>("L_customrelIso01EA", tx->getBranch<vector<float>>("lep_customrelIso01EA")[iL]);
        tx->setBranch<float>("L_ip3d", tx->getBranch<vector<float>>("lep_ip3d")[iL]);
        tx->setBranch<float>("L_ip3derr", tx->getBranch<vector<float>>("lep_ip3derr")[iL]);
        tx->setBranch<float>("L_dxy", tx->getBranch<vector<float>>("lep_dxy")[iL]);
        tx->setBranch<float>("L_dz", tx->getBranch<vector<float>>("lep_dz")[iL]);
    }

    if (iJ >= 0 and iL >= 0)
    {
        float subjet1_pt     = tx->getBranchLazy<float>("J_softdropPuppiSubjet1_pt");
        float subjet1_eta    = tx->getBranchLazy<float>("J_softdropPuppiSubjet1_eta");
        float subjet1_phi    = tx->getBranchLazy<float>("J_softdropPuppiSubjet1_phi");
        float subjet1_mass   = tx->getBranchLazy<float>("J_softdropPuppiSubjet1_mass");
        float subjet2_pt     = tx->getBranchLazy<float>("J_softdropPuppiSubjet2_pt");
        float subjet2_eta    = tx->getBranchLazy<float>("J_softdropPuppiSubjet2_eta");
        float subjet2_phi    = tx->getBranchLazy<float>("J_softdropPuppiSubjet2_phi");
        float subjet2_mass   = tx->getBranchLazy<float>("J_softdropPuppiSubjet2_mass");
        LV subjet1, subjet2;
        subjet1 = RooUtil::Calc::getLV(subjet1_pt, subjet1_eta, subjet1_phi, subjet1_mass);
        subjet2 = RooUtil::Calc::getLV(subjet2_pt, subjet2_eta, subjet2_phi, subjet2_mass);
        tx->setBranch<LV>("L_subjet1_p4", (subjet1 + L));
        tx->setBranch<LV>("L_subjet2_p4", (subjet2 + L));
        tx->setBranch<float>("L_subjet1_dr", RooUtil::Calc::DeltaR(subjet1, L));
        tx->setBranch<float>("L_subjet2_dr", RooUtil::Calc::DeltaR(subjet2, L));
        tx->setBranch<float>("L_subjet1_dr", TMath::RadToDeg()*RooUtil::Calc::getRho(subjet1, L));
        tx->setBranch<float>("L_subjet2_dr", TMath::RadToDeg()*RooUtil::Calc::getRho(subjet2, L));

        tx->setBranch<int>("is_whad_lead", tx->getBranch<LV>("QQ_p4", true).pt() / tx->getBranch<LV>("H_p4", true).pt() > 0.5);

        float mw = tx->getBranch<int>("is_whad_lead", true) ? 35 : 80;

        LV vp4_sol1    = RooUtil::Calc::getNeutrinoP4(L, tx->getBranch<float>("met_pt", true), tx->getBranch<float>("met_phi", true), mw);
        LV vp4_sol2    = RooUtil::Calc::getNeutrinoP4(L, tx->getBranch<float>("met_pt", true), tx->getBranch<float>("met_phi", true), mw, true);
        LV vp4_invsol1 = RooUtil::Calc::getNeutrinoP4(L, tx->getBranch<float>("met_pt", true), tx->getBranch<float>("met_phi", true), mw, false, true);
        LV vp4_invsol2 = RooUtil::Calc::getNeutrinoP4(L, tx->getBranch<float>("met_pt", true), tx->getBranch<float>("met_phi", true), mw, true, true);

        LV vp4 = fabs(vp4_sol1.eta()) < fabs(vp4_sol2.eta()) ? vp4_sol1 : vp4_sol2;

        tx->setBranch<LV>("neu_p4", vp4);
        tx->setBranch<LV>("neu_p4_sol1", vp4_sol1);
        tx->setBranch<LV>("neu_p4_sol2", vp4_sol2);
        tx->setBranch<LV>("neu_p4_invsol1", vp4_invsol1);
        tx->setBranch<LV>("neu_p4_invsol2", vp4_invsol2);

//        float det = RooUtil::Calc::getNeutrinoPzDet(p4, met_pt, met_phi, mw);
//        tx->setBranch<float>("reconeutrino_det", det);
//        tx->setBranch<LV>("reconeutrino_p4", vp4);
//        tx->setBranch<float>("reconeutrino_pt", vp4.pt());
//        tx->setBranch<float>("reconeutrino_eta", vp4.eta());
//        tx->setBranch<float>("reconeutrino_phi", vp4.phi());
//        tx->setBranch<float>("reconeutrino_met_dphi", TVector2::Phi_mpi_pi(met_phi - vp4.phi()));
//        LV vp42 = RooUtil::Calc::getNeutrinoP4(p4, met_pt, met_phi, mw, true);
//        tx->setBranch<LV>("reconeutrino2_p4", vp42);
//        tx->setBranch<float>("reconeutrino2_pt", vp42.pt());
//        tx->setBranch<float>("reconeutrino2_eta", vp42.eta());
//        tx->setBranch<float>("reconeutrino2_phi", vp42.phi());
//        tx->setBranch<float>("reconeutrino2_met_dphi", TVector2::Phi_mpi_pi(met_phi - vp42.phi()));
//        LV vp4inv = RooUtil::Calc::getNeutrinoP4(p4, met_pt, met_phi, mw, false, true);
//        tx->setBranch<LV>("reconeutrinoinv_p4", vp4inv);
//        tx->setBranch<float>("reconeutrinoinv_pt", vp4inv.pt());
//        tx->setBranch<float>("reconeutrinoinv_eta", vp4inv.eta());
//        tx->setBranch<float>("reconeutrinoinv_phi", vp4inv.phi());
//        tx->setBranch<float>("reconeutrinoinv_met_dphi", TVector2::Phi_mpi_pi(met_phi - vp4inv.phi()));

        FillOutput_Htag();

    }

    if (iV >= 0)
    {
        // Selected ak8jets associated information
        tx->setBranch<LV>("V_p4", V);
        if (tx->getBranchLazy<vector<float>>("ak8jets_area"                        ).size() > 0) tx->setBranch<float>("V_area"                        , tx->getBranchLazy<vector<float>>("ak8jets_area"                        )[iV]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_mass"                        ).size() > 0) tx->setBranch<float>("V_mass"                        , tx->getBranchLazy<vector<float>>("ak8jets_mass"                        )[iV]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_softdropMass"                ).size() > 0) tx->setBranch<float>("V_softdropMass"                , tx->getBranchLazy<vector<float>>("ak8jets_softdropMass"                )[iV]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_nJettinessTau1"              ).size() > 0) tx->setBranch<float>("V_nJettinessTau1"              , tx->getBranchLazy<vector<float>>("ak8jets_nJettinessTau1"              )[iV]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_nJettinessTau2"              ).size() > 0) tx->setBranch<float>("V_nJettinessTau2"              , tx->getBranchLazy<vector<float>>("ak8jets_nJettinessTau2"              )[iV]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_nJettinessTau3"              ).size() > 0) tx->setBranch<float>("V_nJettinessTau3"              , tx->getBranchLazy<vector<float>>("ak8jets_nJettinessTau3"              )[iV]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_deep_rawdisc_h4q"            ).size() > 0) tx->setBranch<float>("V_deep_rawdisc_h4q"            , tx->getBranchLazy<vector<float>>("ak8jets_deep_rawdisc_h4q"            )[iV]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_deep_rawdisc_hbb"            ).size() > 0) tx->setBranch<float>("V_deep_rawdisc_hbb"            , tx->getBranchLazy<vector<float>>("ak8jets_deep_rawdisc_hbb"            )[iV]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_deep_rawdisc_qcd"            ).size() > 0) tx->setBranch<float>("V_deep_rawdisc_qcd"            , tx->getBranchLazy<vector<float>>("ak8jets_deep_rawdisc_qcd"            )[iV]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_deep_rawdisc_top"            ).size() > 0) tx->setBranch<float>("V_deep_rawdisc_top"            , tx->getBranchLazy<vector<float>>("ak8jets_deep_rawdisc_top"            )[iV]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_deep_rawdisc_w"              ).size() > 0) tx->setBranch<float>("V_deep_rawdisc_w"              , tx->getBranchLazy<vector<float>>("ak8jets_deep_rawdisc_w"              )[iV]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_deep_rawdisc_z"              ).size() > 0) tx->setBranch<float>("V_deep_rawdisc_z"              , tx->getBranchLazy<vector<float>>("ak8jets_deep_rawdisc_z"              )[iV]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_deep_rawdisc_zbb"            ).size() > 0) tx->setBranch<float>("V_deep_rawdisc_zbb"            , tx->getBranchLazy<vector<float>>("ak8jets_deep_rawdisc_zbb"            )[iV]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_deep_bindisc_h4q"            ).size() > 0) tx->setBranch<float>("V_deep_bindisc_h4q"            , tx->getBranchLazy<vector<float>>("ak8jets_deep_bindisc_h4q"            )[iV]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_deep_bindisc_hbb"            ).size() > 0) tx->setBranch<float>("V_deep_bindisc_hbb"            , tx->getBranchLazy<vector<float>>("ak8jets_deep_bindisc_hbb"            )[iV]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_deep_bindisc_top"            ).size() > 0) tx->setBranch<float>("V_deep_bindisc_top"            , tx->getBranchLazy<vector<float>>("ak8jets_deep_bindisc_top"            )[iV]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_deep_bindisc_w"              ).size() > 0) tx->setBranch<float>("V_deep_bindisc_w"              , tx->getBranchLazy<vector<float>>("ak8jets_deep_bindisc_w"              )[iV]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_deep_bindisc_z"              ).size() > 0) tx->setBranch<float>("V_deep_bindisc_z"              , tx->getBranchLazy<vector<float>>("ak8jets_deep_bindisc_z"              )[iV]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_deep_bindisc_zbb"            ).size() > 0) tx->setBranch<float>("V_deep_bindisc_zbb"            , tx->getBranchLazy<vector<float>>("ak8jets_deep_bindisc_zbb"            )[iV]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet1_pt"     ).size() > 0) tx->setBranch<float>("V_softdropPuppiSubjet1_pt"     , tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet1_pt"     )[iV]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet1_eta"    ).size() > 0) tx->setBranch<float>("V_softdropPuppiSubjet1_eta"    , tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet1_eta"    )[iV]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet1_phi"    ).size() > 0) tx->setBranch<float>("V_softdropPuppiSubjet1_phi"    , tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet1_phi"    )[iV]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet1_mass"   ).size() > 0) tx->setBranch<float>("V_softdropPuppiSubjet1_mass"   , tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet1_mass"   )[iV]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet1_energy" ).size() > 0) tx->setBranch<float>("V_softdropPuppiSubjet1_energy" , tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet1_energy" )[iV]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet2_pt"     ).size() > 0) tx->setBranch<float>("V_softdropPuppiSubjet2_pt"     , tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet2_pt"     )[iV]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet2_eta"    ).size() > 0) tx->setBranch<float>("V_softdropPuppiSubjet2_eta"    , tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet2_eta"    )[iV]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet2_phi"    ).size() > 0) tx->setBranch<float>("V_softdropPuppiSubjet2_phi"    , tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet2_phi"    )[iV]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet2_mass"   ).size() > 0) tx->setBranch<float>("V_softdropPuppiSubjet2_mass"   , tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet2_mass"   )[iV]) ;
        if (tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet2_energy" ).size() > 0) tx->setBranch<float>("V_softdropPuppiSubjet2_energy" , tx->getBranchLazy<vector<float>>("ak8jets_softdropPuppiSubjet2_energy" )[iV]) ;
        if (tx->getBranchLazy<vector<int>>("ak8jets_npfcands"                      ).size() > 0) tx->setBranch<int>("V_npfcands"                      , tx->getBranchLazy<vector<int>>("ak8jets_npfcands"                      )[iV]) ;
        if (tx->getBranchLazy<vector<int>>("ak8jets_partonFlavour"                 ).size() > 0) tx->setBranch<int>("V_partonFlavour"                 , tx->getBranchLazy<vector<int>>("ak8jets_partonFlavour"                 )[iV]) ;
    }


}

void hwwBabyMaker::HiggsRecoModule::FillOutput_Htag()
{

    const LV& J_p4 = tx->getBranchLazy<LV>("J_p4");
    const LV& L_p4 = tx->getBranchLazy<LV>("L_p4");
    const int& L_id = tx->getBranchLazy<int>("L_id");
    const float& J_mass = tx->getBranchLazy<float>("J_mass");
    const float& J_softdropMass = tx->getBranchLazy<float>("J_softdropMass");

    // Higgs HWWlvjj tagger machine learning inputs
    // PF candidates within R=1.0 centered around the J vector
    tx->setBranch<LV>("Htag_J_p4", J_p4);
    tx->setBranch<float>("Htag_J_pt", J_p4.pt());
    tx->setBranch<float>("Htag_J_eta", J_p4.eta());
    tx->setBranch<float>("Htag_J_phi", J_p4.phi());
    tx->setBranch<float>("Htag_J_mass", J_mass);
    tx->setBranch<float>("Htag_J_softdropMass", J_softdropMass);
    tx->setBranch<LV>("Htag_L_p4", L_p4);
    tx->setBranch<float>("Htag_L_pt", L_p4.pt());
    tx->setBranch<float>("Htag_L_eta", L_p4.eta());
    tx->setBranch<float>("Htag_L_phi", L_p4.phi());
    tx->setBranch<float>("Htag_L_dr", RooUtil::Calc::DeltaR(J_p4, L_p4));
    tx->setBranch<float>("Htag_L_alpha", RooUtil::Calc::alpha(J_p4, L_p4));

    bool lepfound = false;
    for (unsigned int ipf = 0; ipf < cms3.pfcands_p4().size(); ++ipf)
    {

        const LV& pf_p4 = cms3.pfcands_p4()[ipf];

        if (RooUtil::Calc::DeltaR(pf_p4, J_p4) < 2.0)
        {

            if (RooUtil::Calc::DeltaR(pf_p4, L_p4) < 0.05 and cms3.pfcands_particleId()[ipf] == L_id)
            {
                lepfound = true;
                // continue;
            }

            if (not (RooUtil::Calc::DeltaR(pf_p4, L_p4) < 0.05 and cms3.pfcands_particleId()[ipf] == L_id))
            {
                tx->pushbackToBranch<LV>("Htag_pf_nolep_p4", pf_p4);
                tx->pushbackToBranch<float>("Htag_pf_nolep_pt", pf_p4.pt());
                tx->pushbackToBranch<float>("Htag_pf_nolep_eta", pf_p4.eta());
                tx->pushbackToBranch<float>("Htag_pf_nolep_phi", pf_p4.phi());
                tx->pushbackToBranch<int>("Htag_pf_nolep_id", cms3.pfcands_particleId()[ipf]);
                tx->pushbackToBranch<float>("Htag_pf_nolep_dr", RooUtil::Calc::DeltaR(J_p4, pf_p4));
                tx->pushbackToBranch<float>("Htag_pf_nolep_alpha", RooUtil::Calc::alpha(J_p4, pf_p4));
                tx->pushbackToBranch<float>("Htag_pf_nolep_puppi_wgt", cms3.pfcands_puppiWeight()[ipf]);
                tx->pushbackToBranch<float>("Htag_pf_nolep_ptfrac", pf_p4.pt() / J_p4.pt());
                tx->pushbackToBranch<float>("Htag_pf_nolep_ptrel", RooUtil::Calc::pPRel(pf_p4, J_p4));
            }

            tx->pushbackToBranch<LV>("Htag_pf_p4", pf_p4);
            tx->pushbackToBranch<float>("Htag_pf_pt", pf_p4.pt());
            tx->pushbackToBranch<float>("Htag_pf_eta", pf_p4.eta());
            tx->pushbackToBranch<float>("Htag_pf_phi", pf_p4.phi());
            tx->pushbackToBranch<int>("Htag_pf_id", cms3.pfcands_particleId()[ipf]);
            tx->pushbackToBranch<float>("Htag_pf_dr", RooUtil::Calc::DeltaR(J_p4, pf_p4));
            tx->pushbackToBranch<float>("Htag_pf_alpha", RooUtil::Calc::alpha(J_p4, pf_p4));
            tx->pushbackToBranch<float>("Htag_pf_puppi_wgt", cms3.pfcands_puppiWeight()[ipf]);
            tx->pushbackToBranch<float>("Htag_pf_ptfrac", pf_p4.pt() / J_p4.pt());
            tx->pushbackToBranch<float>("Htag_pf_ptrel", RooUtil::Calc::pPRel(pf_p4, J_p4));

            tx->pushbackToBranch<int>("Htag_fromPV", cms3.pfcands_fromPV()[ipf]);
            tx->pushbackToBranch<int>("Htag_pv_quality", cms3.pfcands_pvAssociationQuality()[ipf]);

        }

    }

    tx->setBranch<int>("Htag_leppffound", lepfound);

    for (unsigned int ipf = 0; ipf < cms3.pfjets_p4().size(); ++ipf)
    {

        const LV& ak4_p4 = cms3.pfjets_p4()[ipf];

        if (RooUtil::Calc::DeltaR(ak4_p4, L_p4) < 0.4)
        {
            continue;
        }

        if (RooUtil::Calc::DeltaR(ak4_p4, J_p4) < 2.0)
        {

            tx->pushbackToBranch<LV>("Htag_ak4_p4", ak4_p4);
            tx->pushbackToBranch<float>("Htag_ak4_pt", ak4_p4.pt());
            tx->pushbackToBranch<float>("Htag_ak4_eta", ak4_p4.eta());
            tx->pushbackToBranch<float>("Htag_ak4_phi", ak4_p4.phi());
            tx->pushbackToBranch<float>("Htag_ak4_dr", RooUtil::Calc::DeltaR(J_p4, ak4_p4));
            tx->pushbackToBranch<float>("Htag_ak4_alpha", RooUtil::Calc::alpha(J_p4, ak4_p4));
            tx->pushbackToBranch<float>("Htag_ak4_L_dr", RooUtil::Calc::DeltaR(L_p4, ak4_p4));
            tx->pushbackToBranch<float>("Htag_ak4_L_dpt", L_p4.pt() - ak4_p4.pt());

        }

    }

    const float& subjet1_pt = tx->getBranchLazy<float>("J_softdropPuppiSubjet1_pt");
    const float& subjet2_pt = tx->getBranchLazy<float>("J_softdropPuppiSubjet2_pt");

    if (subjet1_pt > 0 and subjet2_pt > 0)
    {
        const float& subjet1_eta = tx->getBranchLazy<float>("J_softdropPuppiSubjet1_eta");
        const float& subjet1_phi = tx->getBranchLazy<float>("J_softdropPuppiSubjet1_phi");
        const float& subjet1_mass = tx->getBranchLazy<float>("J_softdropPuppiSubjet1_mass");
        const float& subjet2_eta = tx->getBranchLazy<float>("J_softdropPuppiSubjet2_eta");
        const float& subjet2_phi = tx->getBranchLazy<float>("J_softdropPuppiSubjet2_phi");
        const float& subjet2_mass = tx->getBranchLazy<float>("J_softdropPuppiSubjet2_mass");

        LV subjet1_p4 = RooUtil::Calc::getLV(subjet1_pt, subjet1_eta, subjet1_phi, subjet1_mass);
        LV subjet2_p4 = RooUtil::Calc::getLV(subjet2_pt, subjet2_eta, subjet2_phi, subjet2_mass);

        tx->setBranch<LV>("Htag_subjet1_p4", subjet1_p4);
        tx->setBranch<float>("Htag_subjet1_pt", subjet1_p4.pt());
        tx->setBranch<float>("Htag_subjet1_eta", subjet1_p4.pt());
        tx->setBranch<float>("Htag_subjet1_phi", subjet1_p4.pt());
        tx->setBranch<float>("Htag_subjet1_dr", RooUtil::Calc::DeltaR(J_p4, subjet1_p4));
        tx->setBranch<float>("Htag_subjet1_alpha", RooUtil::Calc::alpha(J_p4, subjet1_p4));
        tx->setBranch<LV>("Htag_subjet2_p4", subjet2_p4);
        tx->setBranch<float>("Htag_subjet2_pt", subjet2_p4.pt());
        tx->setBranch<float>("Htag_subjet2_eta", subjet2_p4.pt());
        tx->setBranch<float>("Htag_subjet2_phi", subjet2_p4.pt());
        tx->setBranch<float>("Htag_subjet2_dr", RooUtil::Calc::DeltaR(J_p4, subjet2_p4));
        tx->setBranch<float>("Htag_subjet2_alpha", RooUtil::Calc::alpha(J_p4, subjet2_p4));
    }

    // Truth to reco matching study
    if (babymaker->looper.getCurrentFileName().Contains("HToWWToLNuQQ") or babymaker->looper.getCurrentFileName().Contains("VHToNonbb"))
    {
        const LV& gen_higgs_p4 = tx->getBranchLazy<LV>("gen_higgs_p4");
        if (gen_higgs_p4.pt() > 0)
        {
            tx->setBranch<float>("Htag_gen_higgs_dr", RooUtil::Calc::DeltaR(J_p4, tx->getBranch<LV>("gen_higgs_p4")));
            tx->setBranch<float>("Htag_gen_higgs_alpha", RooUtil::Calc::alpha(J_p4, tx->getBranch<LV>("gen_higgs_p4")));
            tx->setBranch<float>("Htag_gen_whad_dr", RooUtil::Calc::DeltaR(J_p4, tx->getBranch<LV>("gen_whad_p4")));
            tx->setBranch<float>("Htag_gen_whad_alpha", RooUtil::Calc::alpha(J_p4, tx->getBranch<LV>("gen_whad_p4")));
            tx->setBranch<float>("Htag_gen_wlep_dr", RooUtil::Calc::DeltaR(J_p4, tx->getBranch<LV>("gen_wlep_p4")));
            tx->setBranch<float>("Htag_gen_wlep_alpha", RooUtil::Calc::alpha(J_p4, tx->getBranch<LV>("gen_wlep_p4")));
            tx->setBranch<float>("Htag_gen_q0_dr", RooUtil::Calc::DeltaR(J_p4, tx->getBranch<LV>("gen_q0_p4")));
            tx->setBranch<float>("Htag_gen_q0_alpha", RooUtil::Calc::alpha(J_p4, tx->getBranch<LV>("gen_q0_p4")));
            tx->setBranch<float>("Htag_gen_q1_dr", RooUtil::Calc::DeltaR(J_p4, tx->getBranch<LV>("gen_q1_p4")));
            tx->setBranch<float>("Htag_gen_q1_alpha", RooUtil::Calc::alpha(J_p4, tx->getBranch<LV>("gen_q1_p4")));
            tx->setBranch<float>("Htag_gen_lep_dr", RooUtil::Calc::DeltaR(J_p4, tx->getBranch<LV>("gen_lep_p4")));
            tx->setBranch<float>("Htag_gen_lep_alpha", RooUtil::Calc::alpha(J_p4, tx->getBranch<LV>("gen_lep_p4")));
            tx->setBranch<float>("Htag_gen_neu_dr", RooUtil::Calc::DeltaR(J_p4, tx->getBranch<LV>("gen_neu_p4")));
            tx->setBranch<float>("Htag_gen_neu_alpha", RooUtil::Calc::alpha(J_p4, tx->getBranch<LV>("gen_neu_p4")));
        }
    }

}

std::tuple<LV, int> hwwBabyMaker::HiggsRecoModule::SelectFatJet(LV ref, float dphithresh)
{

    //
    // Choose the leading fat-jet that is in the correct side
    //

    // Retrieve the ak8jets
    const vector<LV>& ak8jets_p4 = tx->getBranch<vector<LV>>("ak8jets_p4", false);

    // The chosen J
    LV J;
    int iJ = -1; // index of the chosen J

    // If there are only one fat-jet just choose that
    if (tx->getBranch<int>("nak8jets") == 1)
    {
        J = ak8jets_p4[0];
        iJ = 0;
    }
    else
    {

        // Loop over and find the ak8 jet closest to MET
        for (unsigned int ii = 0; ii < ak8jets_p4.size(); ++ii)
        {

            // Retrieve the ak8jet
            const LV& p4 = ak8jets_p4[ii];

            // Compute the Delta Phi between ak8 jets and the reference
            float tmpdphi = RooUtil::Calc::DeltaPhi(p4, ref);

            // If the delta phi is less than 90 degrees and is leading jet in the hemisphere where MET is pointing
            if (fabs(tmpdphi) < dphithresh and p4.pt() > J.pt())
            {

                // Set the ak8 jets p4 and the index
                J = p4;
                iJ = ii;

            }

        }

    }

    return std::make_tuple(J, iJ);

}

std::tuple<LV, int> hwwBabyMaker::HiggsRecoModule::SelectLepton(LV ref, float dphithresh)
{

    //
    // Choose the leading lepton that is in the correct side of J-MET-Hemisphere
    //

    // Retrieve the leptons to loop over to identify which one is the lepton from of interest
    const vector<LV>& lep_p4 = tx->getBranch<vector<LV>>("lep_p4");

    // The chosen L
    LV L;
    int iL = -1; // index of the chosen L

    // If there are only one lepton just choose that
    if (tx->getBranch<int>("nrecolep") == 1)
    {
        L = lep_p4[0];
        iL = 0;
    }
    // If there are more than one loop over and find the one that is leading in the vicinity of fat-jet + MET system
    else
    {

        // Loop over and find the closest to reference
        for (unsigned int ii = 0; ii < lep_p4.size(); ++ii)
        {

            // Retrieve the lepton p4
            const LV& p4 = lep_p4[ii];

            // Compute the Delta Phi between lepton and reference
            float tmpdphi = RooUtil::Calc::DeltaPhi(p4, ref);

            // If the delta phi is less than 90 degrees and is leading lepton in the hemisphere where reference vector is pointing
            if (fabs(tmpdphi) < dphithresh and p4.pt() > L.pt())
            {

                // Set the lepton p4 and the index
                L = p4;
                iL = ii;

            }

        }

    }

    return std::make_tuple(L, iL);

}

std::tuple<LV, int> hwwBabyMaker::HiggsRecoModule::SelectVbosonJet(LV ref, float dphithresh)
{

    //
    // Choose the leading fat-jet as V boson jet
    //

    // Retrieve the ak8jets
    const vector<LV>& ak8jets_p4 = tx->getBranch<vector<LV>>("ak8jets_p4", false);

    // The chosen V
    LV V;
    int iV = -1; // index of the chosen V

    // Loop over and find the ak8 jet closest to MET
    for (unsigned int ii = 0; ii < ak8jets_p4.size(); ++ii)
    {

        // Retrieve the ak8jet
        const LV& p4 = ak8jets_p4[ii];

        // Compute the Delta Phi between ak8 jets and the reference
        float tmpdphi = RooUtil::Calc::DeltaPhi(p4, ref);

        // If the delta phi is less than 90 degrees and is leading jet in the hemisphere where MET is pointing
        if (fabs(tmpdphi) > dphithresh and p4.pt() > V.pt())
        {

            // Set the ak8 jets p4 and the index
            V = p4;
            iV = ii;

        }

    }

    return std::make_tuple(V, iV);

}

//==============================================================================================================
//
// Recoil Module
//
//==============================================================================================================

void hwwBabyMaker::RecoilModule::AddOutput()
{
    AddOutput_v2();
}

void hwwBabyMaker::RecoilModule::AddOutput_v1()
{
    tx->createBranch<LV>(bname);
}

void hwwBabyMaker::RecoilModule::AddOutput_v2()
{

    tx->createBranch<LV>(bname_prefix + "_p4");
    tx->createBranch<LV>(bname_prefix + "_leadak4_p4");
    tx->createBranch<int>(bname_prefix + "_leadak4_npfcands");
    tx->createBranch<int>(bname_prefix + "_leadak4_chargedHadronMultiplicity");
    tx->createBranch<int>(bname_prefix + "_leadak4_chargedMultiplicity");
    tx->createBranch<int>(bname_prefix + "_leadak4_electronMultiplicity");
    tx->createBranch<int>(bname_prefix + "_leadak4_muonMultiplicity");
    tx->createBranch<int>(bname_prefix + "_leadak4_neutralHadronMultiplicity");
    tx->createBranch<int>(bname_prefix + "_leadak4_neutralMultiplicity");
    tx->createBranch<int>(bname_prefix + "_leadak4_photonMultiplicity");
    tx->createBranch<int>(bname_prefix + "_leadak4_totalMultiplicity");
    tx->createBranch<int>(bname_prefix + "_leadak4_puppi_chargedHadronMultiplicity");
    tx->createBranch<int>(bname_prefix + "_leadak4_puppi_chargedMultiplicity");
    tx->createBranch<int>(bname_prefix + "_leadak4_puppi_electronMultiplicity");
    tx->createBranch<int>(bname_prefix + "_leadak4_puppi_muonMultiplicity");
    tx->createBranch<int>(bname_prefix + "_leadak4_puppi_neutralHadronMultiplicity");
    tx->createBranch<int>(bname_prefix + "_leadak4_puppi_neutralMultiplicity");
    tx->createBranch<int>(bname_prefix + "_leadak4_puppi_photonMultiplicity");
    tx->createBranch<int>(bname_prefix + "_leadak4_puppi_totalMultiplicity");

//    pfjets_bDiscriminatorNames
//    pfjets_puppi_bDiscriminatorNames
//    pfjets_mc_p4
//    pfjets_p4
//    pfjets_puppi_p4
//    pfjets_pfcandmup4
//    pfjets_puppi_pfcandmup4
//    pfjets_mc3dr
//    pfjets_mcdr
//    pfjets_area
//    pfjets_axis1
//    pfjets_axis2
//    pfjets_chargedEmE
//    pfjets_chargedHadronE
//    pfjets_electronE
//    pfjets_hfEmE
//    pfjets_hfHadronE
//    pfjets_muonE
//    pfjets_neutralEmE
//    pfjets_neutralHadronE
//    pfjets_pfCombinedInclusiveSecondaryVertexV2BJetTag
//    pfjets_pfDeepCSVJetTagsprobbPlusprobbb
//    pfjets_photonE
//    pfjets_pileupJetId
//    pfjets_ptDistribution
//    pfjets_undoJEC
//    pfjets_puppi_area
//    pfjets_puppi_axis1
//    pfjets_puppi_axis2
//    pfjets_puppi_chargedEmE
//    pfjets_puppi_chargedHadronE
//    pfjets_puppi_electronE
//    pfjets_puppi_hfEmE
//    pfjets_puppi_hfHadronE
//    pfjets_puppi_muonE
//    pfjets_puppi_neutralEmE
//    pfjets_puppi_neutralHadronE
//    pfjets_puppi_pfCombinedInclusiveSecondaryVertexV2BJetTag
//    pfjets_puppi_pfDeepCSVJetTagsprobbPlusprobbb
//    pfjets_puppi_photonE
//    pfjets_puppi_pileupJetId
//    pfjets_puppi_ptDistribution
//    pfjets_puppi_undoJEC
//    pfjets_bDiscriminators
//    pfjets_puppi_bDiscriminators
//    pfjets_mc3_id
//    pfjets_mc3idx
//    pfjets_mc_motherid
//    pfjets_chargedHadronMultiplicity
//    pfjets_chargedMultiplicity
//    pfjets_electronMultiplicity
//    pfjets_hadronFlavour
//    pfjets_muonMultiplicity
//    pfjets_neutralHadronMultiplicity
//    pfjets_neutralMultiplicity
//    pfjets_npfcands
//    pfjets_partonFlavour
//    pfjets_photonMultiplicity
//    pfjets_totalMultiplicity
//    pfjets_puppi_chargedHadronMultiplicity
//    pfjets_puppi_chargedMultiplicity
//    pfjets_puppi_electronMultiplicity
//    pfjets_puppi_hadronFlavour
//    pfjets_puppi_muonMultiplicity
//    pfjets_puppi_neutralHadronMultiplicity
//    pfjets_puppi_neutralMultiplicity
//    pfjets_puppi_npfcands
//    pfjets_puppi_partonFlavour
//    pfjets_puppi_photonMultiplicity
//    pfjets_puppi_totalMultiplicity

}

void hwwBabyMaker::RecoilModule::FillOutput()
{
    FillOutput_v2();
}

// Deprecated WON'T WORK!
void hwwBabyMaker::RecoilModule::FillOutput_v1()
{

    // Get the MET 2-vector
    const float met_pt = tx->getBranch<float>("met_pt", true);
    const float met_phi = tx->getBranch<float>("met_phi", true);
    TLorentzVector met_tlv;
    met_tlv.SetPtEtaPhiM(met_pt, 0, met_phi, 0);
    LV met = RooUtil::Calc::getLV(met_tlv);

    //
    // Sum the ak4 jets that is in the opposite side of the MET-hemisphere and call it the "Recoil"
    //

    // Retrieve the jets
    const vector<LV> jets_p4 = tx->getBranch<vector<LV>>("jets_p4", false);

    // The reconstructed higgs recoil vector
    LV Recoil;

    // Loop over and find the ak8 jet closest to MET
    for (auto& p4 : jets_p4)
    {

        // Compute the Delta Phi between ak8 jets and MET
        float tmpdphi = RooUtil::Calc::DeltaPhi(p4, met);

        // If the delta phi is larger than 90 degrees
        if (fabs(tmpdphi) > TMath::Pi() * 3./ 4.)
        {

            // Set the ak8 jets p4
            Recoil += p4;

        }

    }

    // Found?
    if (Recoil.pt() > 0)
    {

        tx->setBranch<LV>(bname, Recoil);

    }

}

void hwwBabyMaker::RecoilModule::FillOutput_v2()
{

    // First check we even have a selected ak8jet (i.e. J)
    if (!tx->isBranchSet<LV>("Jmet_p4"))
        return;

    // Get the J-MET vector
    LV Jmet = tx->getBranch<LV>("Jmet_p4", true);

    //
    // Sum the ak4 jets that is in the opposite side of the J-MET-hemisphere and call it the "Recoil"
    //

    // Retrieve the jets
    const vector<LV> jets_p4 = tx->getBranchLazy<vector<LV>>(TString(jettype)); // NOTE Need to set TString() in order not to mess with the jettype variable
    const vector<int> jets_idx = tx->getBranchLazy<vector<int>>(TString(jettype).ReplaceAll("p4", "idx")); // NOTE Need to set TString() in order not to mess with the jettype variable

    // The reconstructed higgs recoil vector
    LV Recoil;
    LV leadjet_p4;
    int leadjet_idx = -1;

    // Loop over and find the ak4 jet closest to MET
    for (unsigned int ij = 0; ij < jets_p4.size(); ++ij)
    {

        LV p4 = jets_p4[ij];
        int idx = jets_idx[ij];

        // Compute the Delta Phi between ak4 jets and MET
        float tmpdphi = RooUtil::Calc::DeltaPhi(p4, Jmet);

        // If the delta phi is larger than 90 degrees
        if (fabs(tmpdphi) > threshold)
        {

            // Set the ak4 jets p4
            Recoil += p4;

            // Set the lead ak4 jet idx
            if (p4.pt() > leadjet_p4.pt())
            {
                leadjet_p4 = p4;
                leadjet_idx = idx;
            }

        }

    }

    // Found?
    if (Recoil.pt() > 0 and leadjet_idx >= 0)
    {

        tx->setBranch<LV>(bname_prefix + "_p4", Recoil);
        tx->setBranch<LV>(bname_prefix + "_leadak4_p4", leadjet_p4);
        if (babymaker->looper.doesBranchExist("pfjets_totalMultiplicity"))
        {
            tx->setBranch<int>(bname_prefix + "_leadak4_npfcands", cms3.pfjets_npfcands()[leadjet_idx]);
            tx->setBranch<int>(bname_prefix + "_leadak4_chargedHadronMultiplicity", cms3.pfjets_chargedHadronMultiplicity()[leadjet_idx]);
            tx->setBranch<int>(bname_prefix + "_leadak4_chargedMultiplicity", cms3.pfjets_chargedMultiplicity()[leadjet_idx]);
            tx->setBranch<int>(bname_prefix + "_leadak4_electronMultiplicity", cms3.pfjets_electronMultiplicity()[leadjet_idx]);
            tx->setBranch<int>(bname_prefix + "_leadak4_muonMultiplicity", cms3.pfjets_muonMultiplicity()[leadjet_idx]);
            tx->setBranch<int>(bname_prefix + "_leadak4_neutralHadronMultiplicity", cms3.pfjets_neutralHadronMultiplicity()[leadjet_idx]);
            tx->setBranch<int>(bname_prefix + "_leadak4_neutralMultiplicity", cms3.pfjets_neutralMultiplicity()[leadjet_idx]);
            tx->setBranch<int>(bname_prefix + "_leadak4_photonMultiplicity", cms3.pfjets_photonMultiplicity()[leadjet_idx]);
            tx->setBranch<int>(bname_prefix + "_leadak4_totalMultiplicity", cms3.pfjets_totalMultiplicity()[leadjet_idx]);
            tx->setBranch<int>(bname_prefix + "_leadak4_puppi_chargedHadronMultiplicity", cms3.pfjets_puppi_chargedHadronMultiplicity()[leadjet_idx]);
            tx->setBranch<int>(bname_prefix + "_leadak4_puppi_chargedMultiplicity", cms3.pfjets_puppi_chargedMultiplicity()[leadjet_idx]);
            tx->setBranch<int>(bname_prefix + "_leadak4_puppi_electronMultiplicity", cms3.pfjets_puppi_electronMultiplicity()[leadjet_idx]);
            tx->setBranch<int>(bname_prefix + "_leadak4_puppi_muonMultiplicity", cms3.pfjets_puppi_muonMultiplicity()[leadjet_idx]);
            tx->setBranch<int>(bname_prefix + "_leadak4_puppi_neutralHadronMultiplicity", cms3.pfjets_puppi_neutralHadronMultiplicity()[leadjet_idx]);
            tx->setBranch<int>(bname_prefix + "_leadak4_puppi_neutralMultiplicity", cms3.pfjets_puppi_neutralMultiplicity()[leadjet_idx]);
            tx->setBranch<int>(bname_prefix + "_leadak4_puppi_photonMultiplicity", cms3.pfjets_puppi_photonMultiplicity()[leadjet_idx]);
            tx->setBranch<int>(bname_prefix + "_leadak4_puppi_totalMultiplicity", cms3.pfjets_puppi_totalMultiplicity()[leadjet_idx]);
        }

    }

}

//==============================================================================================================
//
// GenPart Module
//
//==============================================================================================================

void hwwBabyMaker::GenPartModule::AddOutput()
{
    tx->createBranch<float>("gen_ht");
}

void hwwBabyMaker::GenPartModule::FillOutput()
{
    tx->setBranch<float>("gen_ht", babymaker->coreGenPart.gen_ht);
}

//==============================================================================================================
//
// Event Module
//
//==============================================================================================================

void hwwBabyMaker::EventModule::AddOutput()
{
    tx->createBranch<float>("nvtx");
}

void hwwBabyMaker::EventModule::FillOutput()
{
    // Count number of good vertices.
    int nvtx = 0;
    for (unsigned int ivtx = 0; ivtx < cms3.evt_nvtxs(); ivtx++)
    {
        if (!isGoodVertex(ivtx)) { continue; }
        nvtx++;
    }
    tx->setBranch<float>("nvtx", nvtx);
}
