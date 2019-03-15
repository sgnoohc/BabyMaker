#include "hwwBabyMaker.h"

//##############################################################################################################
hwwBabyMaker::hwwBabyMaker() : processor(0) {}
hwwBabyMaker::~hwwBabyMaker() {}

//##############################################################################################################
void hwwBabyMaker::ProcessObjectsPrePassSelection()
{
    // Process leptons via CoreUtil
    ProcessLeptons();

    // ReClusterFatJets
    ReClusterFatJets();

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

    // Process MET (recalculate etc.)
    ProcessMET();

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
    LV L_p4 =
        coreElectron.index.size() > 0 ?
        cms3.els_p4()[coreElectron.index[0]] :
        coreMuon.index.size() > 0 ?
        cms3.mus_p4()[coreMuon.index[0]] : LV();

    if (L_p4.pt() == 0)
    {
        std::cout << "I should have found a lepton but it doesn't seem like I found one." << std::endl;
        FATALERROR(__FUNCTION__);
    }

    // Re-clustered jets and put together the information for the fat jets
    recl.ReClusterFatJets(L_p4);
}

//##############################################################################################################
void hwwBabyMaker::ReCluster::ReClusterFatJets(LV& L_p4)
{

    // Set the boolean for the result to false
    found_jet = false;

    //
    // Aggregating PF candidates around the lepton
    //

    // Vector to hold the list of PF candidates
    std::vector<fastjet::PseudoJet> particles;

    // Loop over PF candidates
    for (unsigned int ipf = 0; ipf < cms3.pfcands_p4().size(); ++ipf)
    {

        // Retrieve pf candidate 4 vector
        const LV& pf_p4 = cms3.pfcands_p4()[ipf];

        // If the delta R is < 2.5 of the lepton then consider it
        if (RooUtil::Calc::DeltaR(pf_p4, L_p4) < 2.5)
        {

            // puppi_wgt is a wgt that assigns probability that a given pf cand is from a primary intearction
            float puppi_wgt = cms3.pfcands_puppiWeight()[ipf];

            // If the weight is 0 then just remove it, (i.e. no chance it's from primary vertex)
            // This is important not to be too slow
            // (if not puppi there is also fromPV or other ways to associate to primary vertex)
            if (puppi_wgt == 0)
                continue;

            // The p4 needs to be multiplied by the weight for pile up suppression
            LV mod_pf_p4 = pf_p4;
            mod_pf_p4 *= puppi_wgt;

            // Get 4 vector components
            float px = mod_pf_p4.px();
            float py = mod_pf_p4.py();
            float pz = mod_pf_p4.pz();
            float E  = mod_pf_p4.energy();

            // Push to the vector
            particles.push_back(fastjet::PseudoJet(px, py, pz, E));
        }

    }

    //
    // Cluster jets
    //

    // Setting of the jet clustering
    double R = 0.8;
    fastjet::JetAlgorithm jetalgo = fastjet::antikt_algorithm;

    // choose a jet definition
    fastjet::JetDefinition jet_def(jetalgo, R);

    // give the soft drop groomer a short name
    // Use a symmetry cut z > z_cut R^beta
    // By default, there is no mass-drop requirement
    double z_cut = 0.10;
    double beta  = 0.0;
    fastjet::contrib::SoftDrop sd(beta, z_cut);

    // run the clustering, extract the jets
    fastjet::ClusterSequence cs(particles, jet_def);

    // Get a list of jets
    std::vector<fastjet::PseudoJet> jets_wo_lep = fastjet::sorted_by_pt(cs.inclusive_jets());

    // Choose the jet with closest distance to the lepton with a substructure where the subjets have at least 20 GeV pT
    float minDR = 999;
    for (auto& pjet : jets_wo_lep)
    {

        // get 4-vector
        LV jet = getLV(pjet);

        // Compute DR
        float tmpDR = RooUtil::Calc::DeltaR(jet, L_p4);

        // If DR is the smallest consider the jet
        if (tmpDR < minDR)
        {

            // Now compute the softdrop and see whether it has a substructure
            fastjet::PseudoJet sd_jet = sd(pjet);

            // Check whether it found a substructure
            if (sd_jet.has_pieces())
            {

                std::vector<fastjet::PseudoJet> subjets = fastjet::sorted_by_pt(sd_jet.pieces());

                // Check that the subjets have at least 20 GeV pt
                if (subjets[0].pt() > 20. and subjets[1].pt() > 20.)
                {

                    // Save the DR value
                    minDR = tmpDR;

                    // Save the results
                    J_p4 = jet;
                    J_pj = pjet;
                    J_SD_p4 = getLV(sd_jet);
                    J_SD_pj = sd_jet;
                    q0_p4 = getLV(subjets[0]);
                    q0_pj = subjets[0];
                    q1_p4 = getLV(subjets[1]);
                    q1_pj = subjets[1];

                    // Set the found_jet flag to true
                    found_jet = true;

                    // Now compute NSubjettiness variables

                    // https://github.com/cms-sw/cmssw/blob/CMSSW_8_0_3_patchX/RecoJets/JetProducers/python/nJettinessAdder_cfi.py
                    // https://github.com/cms-sw/cmssw/blob/76f5d38567bfc85949371c5b46d2a597cd2b128e/RecoJets/JetProducers/plugins/NjettinessAdder.cc
                    // https://github.com/cms-sw/cmssw/blob/76f5d38567bfc85949371c5b46d2a597cd2b128e/RecoJets/JetProducers/interface/NjettinessAdder.h
                    fastjet::contrib::Nsubjettiness      nSub1_beta1(1, fastjet::contrib::OnePass_KT_Axes(), fastjet::contrib::NormalizedMeasure(1.0, 0.8));
                    fastjet::contrib::Nsubjettiness      nSub2_beta1(2, fastjet::contrib::OnePass_KT_Axes(), fastjet::contrib::NormalizedMeasure(1.0, 0.8));
                    fastjet::contrib::Nsubjettiness      nSub3_beta1(3, fastjet::contrib::OnePass_KT_Axes(), fastjet::contrib::NormalizedMeasure(1.0, 0.8));
                    fastjet::contrib::NsubjettinessRatio nSub31_beta1(3, 1, fastjet::contrib::OnePass_KT_Axes(), fastjet::contrib::NormalizedMeasure(1.0, 0.8));
                    fastjet::contrib::NsubjettinessRatio nSub32_beta1(3, 2, fastjet::contrib::OnePass_KT_Axes(), fastjet::contrib::NormalizedMeasure(1.0, 0.8));
                    fastjet::contrib::NsubjettinessRatio nSub21_beta1(2, 1, fastjet::contrib::OnePass_KT_Axes(), fastjet::contrib::NormalizedMeasure(1.0, 0.8));

                    // Re-compute nsubjettiness variables with unpruned jet
                    tau1  = nSub1_beta1(pjet);
                    tau2  = nSub2_beta1(pjet);
                    tau3  = nSub3_beta1(pjet);
                    tau31 = nSub31_beta1(pjet);
                    tau32 = nSub32_beta1(pjet);
                    tau21 = nSub21_beta1(pjet);

                    // tau1 tau2 tau3 tau31 tau32 tau21 

                    // Re-compute nsubjettiness variables with pruned jet
                    SD_tau1  = nSub1_beta1(sd_jet);
                    SD_tau2  = nSub2_beta1(sd_jet);
                    SD_tau3  = nSub3_beta1(sd_jet);
                    SD_tau31 = nSub31_beta1(sd_jet);
                    SD_tau32 = nSub32_beta1(sd_jet);
                    SD_tau21 = nSub21_beta1(sd_jet);

                    // SD_tau1 SD_tau2 SD_tau3 SD_tau31 SD_tau32 SD_tau21 

                }

            }
        }
    }

}

//##############################################################################################################
LV hwwBabyMaker::ReCluster::getLV(fastjet::PseudoJet& jet)
{
    return RooUtil::Calc::getLV(jet.pt(), jet.eta(), jet.phi(), jet.m());
}


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

    // Pass with at least one fat jet and only one lepton
    if (n_reconstructed_leptons != 1) return false;
    if (not recl.found_jet) return false;

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
