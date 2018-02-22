#include "ScanChain_v2.h"

using namespace std;

//##############################################################################################################
void babyMaker_v2::ScanChain_v2(TChain* chain, std::string baby_name, int max_events)
{

    // Looper
    RooUtil::Looper<CMS3> looper(chain, &cms3, max_events);

    // Output root file
    CreateOutput();

    while (looper.nextEvent())
    {
        coreJec.setJECFor(looper.getCurrentFileName());

        // Loop over electrons
        ProcessElectrons();

        // Loop over muons
        ProcessMuons();

        // Check preselection
        if (!PassPresel())
            continue;

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

        // Fill baby ntuple
        FillOutput();

        // Photons Not needed

        // Select based on two leptons

        // Loop over jets (keep track of good ones for removal)

        // jet lepton overlap

        // Loop over good jets after removal and select

        // kinematic variables for pf cands (isotrack)
    }

    ofile->cd();
    t->Write();
}

//##############################################################################################################
void babyMaker_v2::CreateOutput()
{
    ofile = new TFile("output.root", "recreate");
    t = new TTree("t", "t");
    tx = new RooUtil::TTreeX(t);

    tx->createBranch<Int_t>("run");
    tx->createBranch<Int_t>("lumi");
    tx->createBranch<unsigned long long>("evt");
    tx->createBranch<int>("isData");
    tx->createBranch<float>("evt_scale1fb");

    tx->createBranch<int>("HLT_DoubleMu");
    tx->createBranch<int>("HLT_DoubleEl");
    tx->createBranch<int>("HLT_DoubleEl_DZ");
    tx->createBranch<int>("HLT_DoubleEl_DZ_2");
    tx->createBranch<int>("HLT_MuEG");

    tx->createBranch<vector<LorentzVector>>("lep_p4");
    tx->createBranch<vector<float>>("lep_ip3d");
    tx->createBranch<vector<float>>("lep_ip3derr");
    tx->createBranch<vector<int>>("lep_isTriggerSafe_v1");
    tx->createBranch<vector<int>>("lep_lostHits");
    tx->createBranch<vector<int>>("lep_motherIdSS");
    tx->createBranch<vector<int>>("lep_pass_VVV_cutbased_fo_noiso");
    tx->createBranch<vector<int>>("lep_pass_VVV_cutbased_tight_noiso");
    tx->createBranch<vector<int>>("lep_pass_VVV_cutbased_veto_noiso");
    tx->createBranch<vector<int>>("lep_pdgId");
    tx->createBranch<vector<float>>("lep_ptRatio");
    tx->createBranch<vector<float>>("lep_ptRel");
    tx->createBranch<vector<float>>("lep_pterr");
    tx->createBranch<vector<float>>("lep_relIso03EAv2");
    tx->createBranch<vector<float>>("lep_relIso04EAv2");
    tx->createBranch<vector<int>>("lep_tightCharge");
    tx->createBranch<vector<float>>("lep_trk_pt");
    tx->createBranch<vector<int>>("lep_charge");
    tx->createBranch<vector<float>>("lep_etaSC");
    tx->createBranch<vector<float>>("lep_MVA");

    tx->createBranch<vector<LorentzVector>>("jets_p4");
    tx->createBranch<vector<LorentzVector>>("jets_up_p4");
    tx->createBranch<vector<LorentzVector>>("jets_dn_p4");
    tx->createBranch<vector<float>>("jets_csv");
    tx->createBranch<vector<float>>("jets_up_csv");
    tx->createBranch<vector<float>>("jets_dn_csv");

    tx->createBranch<float>("met_pt");
    tx->createBranch<float>("met_phi");
    tx->createBranch<float>("met_T1CHS_miniAOD_CORE_pt");
    tx->createBranch<float>("met_T1CHS_miniAOD_CORE_phi");
    tx->createBranch<float>("met_T1CHS_miniAOD_CORE_up_pt");
    tx->createBranch<float>("met_T1CHS_miniAOD_CORE_up_phi");
    tx->createBranch<float>("met_T1CHS_miniAOD_CORE_dn_pt");
    tx->createBranch<float>("met_T1CHS_miniAOD_CORE_dn_phi");

    tx->createBranch<int>("firstgoodvertex");
    tx->createBranch<int>("nTrueInt");
    tx->createBranch<int>("nVert");

    tx->createBranch<int>("nisoTrack_mt2_cleaned_VVV_cutbased_veto");

    tx->createBranch<float>("weight_btagsf");
    tx->createBranch<float>("weight_btagsf_heavy_DN");
    tx->createBranch<float>("weight_btagsf_heavy_UP");
    tx->createBranch<float>("weight_btagsf_light_DN");
    tx->createBranch<float>("weight_btagsf_light_UP");

    tx->createBranch<float>("gen_ht");

    tx->createBranch<vector<LorentzVector>>("genPart_p4");
    tx->createBranch<vector<int>>("genPart_motherId");
    tx->createBranch<vector<int>>("genPart_pdgId");

    tx->createBranch<int>("Flag_EcalDeadCellTriggerPrimitiveFilter");
    tx->createBranch<int>("Flag_HBHEIsoNoiseFilter");
    tx->createBranch<int>("Flag_HBHENoiseFilter");
    tx->createBranch<int>("Flag_badChargedCandidateFilter");
    tx->createBranch<int>("Flag_badMuonFilter");
    tx->createBranch<int>("Flag_eeBadScFilter");
    tx->createBranch<int>("Flag_globalTightHalo2016");
    tx->createBranch<int>("Flag_goodVertices");

    tx->clear();
}

//##############################################################################################################
void babyMaker_v2::ProcessTriggers() { coreTrigger.process(); }

//##############################################################################################################
void babyMaker_v2::ProcessGenParticles() { coreGenPart.process(); }

//##############################################################################################################
void babyMaker_v2::ProcessElectrons() { coreElectron.process(); }

//##############################################################################################################
void babyMaker_v2::ProcessMuons() { coreMuon.process(); }

//##############################################################################################################
void babyMaker_v2::ProcessJets() { coreJet.process(coreJec); }

//##############################################################################################################
void babyMaker_v2::ProcessMET() { coreMET.process(coreJec); }

//##############################################################################################################
void babyMaker_v2::ProcessTracks() { coreTrack.process(); }

//##############################################################################################################
bool babyMaker_v2::PassPresel()
{
    if (!((coreElectron.index.size() + coreMuon.index.size()) >= 2)) return false;
    return true;
}

//##############################################################################################################
void babyMaker_v2::FillOutput()
{

    // Fill baby ntuple branches with event information (evt, lumi etc.)
    FillEventInfo();

    // Fill baby ntuple branches corresponding to lepton indices
    FillElectrons();

    // Fill baby ntuple branches corresponding to lepton indices
    FillMuons();

    // Organize leptons by sorting by their pt
    SortLeptonBranches();

    // Fill baby ntuple branches for jets
    FillJets();

    // Organize jets by sorting by their pt
    SortJetBranches();

    // Fill baby ntuple branches for MET
    FillMET();

    // Fill baby ntuple branches for track related variables (iso track veto)
    FillTracks();

    // Fill generatore level particles
    FillGenParticles();

    // Fill trigger bits
    FillTrigger();

    // Fill vertex info
    FillVertexInfo();

    // Fill TTree (NOTE: also clears internal variables)
    FillTTree();
}

//##############################################################################################################
void babyMaker_v2::FillEventInfo()
{
    tx->setBranch<Int_t>("run", cms3.evt_run());
    tx->setBranch<Int_t>("lumi", cms3.evt_lumiBlock());
    tx->setBranch<unsigned long long>("evt", cms3.evt_event());
    tx->setBranch<int>("isData", cms3.evt_isRealData());
    tx->setBranch<float>("evt_scale1fb", coreDatasetInfo.getScale1fb());
}

//##############################################################################################################
void babyMaker_v2::FillElectrons()
{
    for (auto& idx : coreElectron.index)
    {
        // Some variables that need to call another functions...
        pair<int, int> motherId_genIdx = lepMotherID_v2(Lep(cms3.els_charge()[idx] * (-11), idx)); //don't forget the sign
        const LorentzVector& temp_jet_p4 = closestJet(cms3.els_p4()[idx], 0.4, 3.0, /*whichCorr = */2);
        float closeJetPt = temp_jet_p4.pt();

        tx->pushbackToBranch<LorentzVector> ("lep_p4"                           , cms3.els_p4()[idx]);
        tx->pushbackToBranch<float>         ("lep_ip3d"                         , cms3.els_ip3d()[idx]);
        tx->pushbackToBranch<float>         ("lep_ip3derr"                      , cms3.els_ip3derr()[idx]);
        tx->pushbackToBranch<int>           ("lep_isTriggerSafe_v1"             , isTriggerSafe_v1(idx));
        tx->pushbackToBranch<int>           ("lep_lostHits"                     , cms3.els_lostHits()[idx]);
        tx->pushbackToBranch<int>           ("lep_motherIdSS"                   , motherId_genIdx.first);
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_fo_noiso"   , passElectronSelection_VVV(idx, VVV_cutbased_fo_noiso));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_tight_noiso", passElectronSelection_VVV(idx, VVV_cutbased_tight_noiso));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_veto_noiso" , passElectronSelection_VVV(idx, VVV_cutbased_veto_noiso));
        tx->pushbackToBranch<int>           ("lep_pdgId"                        , cms3.els_charge()[idx]*(-11));
        tx->pushbackToBranch<float>         ("lep_ptRatio"                      , (closeJetPt > 0. ? cms3.els_p4()[idx].pt() / closeJetPt : 1.));
        tx->pushbackToBranch<float>         ("lep_ptRel"                        , ptRel(cms3.els_p4()[idx], temp_jet_p4, true));
        tx->pushbackToBranch<float>         ("lep_pterr"                        , cms3.els_ptErr()[idx]);
        tx->pushbackToBranch<float>         ("lep_relIso03EAv2"                 , eleRelIso03EA(idx, 2));
        tx->pushbackToBranch<int>           ("lep_tightCharge"                  , tightChargeEle(idx));
        tx->pushbackToBranch<float>         ("lep_trk_pt"                       , cms3.els_trk_p4()[idx].pt());
        tx->pushbackToBranch<int>           ("lep_charge"                       , cms3.els_charge()[idx]);
        tx->pushbackToBranch<float>         ("lep_etaSC"                        , cms3.els_etaSC()[idx]);
        tx->pushbackToBranch<float>         ("lep_MVA"                          , getMVAoutput(idx));

        // Due to CMS4 not having pf candidates...
        std::cout.setstate(std::ios_base::failbit); // To suppress warning about CMS4 not having PF candidates
        if (cms3.evt_CMS3tag()[0].Contains("CMS3"))
            tx->pushbackToBranch<float>     ("lep_relIso04EAv2"                 , elRelIsoCustomCone(idx, 0.4, false, 0.0, /*useDBCorr=*/false, /*useEACorr=*/true, /*mindr=*/ -1, /*eaversion=*/2));
        else
            tx->pushbackToBranch<float>     ("lep_relIso04EAv2"                 , eleRelIso03EA(idx, 2));
        std::cout.clear();
    }
}

//##############################################################################################################
void babyMaker_v2::FillMuons()
{
    for (auto& idx : coreMuon.index)
    {
        // Some variables that need to call another functions...
        pair<int, int> motherId_genIdx = lepMotherID_v2(Lep(cms3.mus_charge()[idx] * (-13), idx)); //don't forget the sign
        const LorentzVector& temp_jet_p4 = closestJet(cms3.mus_p4()[idx], 0.4, 3.0, /*whichCorr = */2);
        float closeJetPt = temp_jet_p4.pt();

        tx->pushbackToBranch<LorentzVector> ("lep_p4"                           , cms3.mus_p4()[idx]);
        tx->pushbackToBranch<float>         ("lep_ip3d"                         , cms3.mus_ip3d()[idx]);
        tx->pushbackToBranch<float>         ("lep_ip3derr"                      , cms3.mus_ip3derr()[idx]);
        tx->pushbackToBranch<int>           ("lep_isTriggerSafe_v1"             , true); // Electron specific branch. So muons always pass.
        tx->pushbackToBranch<int>           ("lep_lostHits"                     , cms3.mus_lostHits()[idx]);
        tx->pushbackToBranch<int>           ("lep_motherIdSS"                   , motherId_genIdx.first);
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_fo_noiso"   , passMuonSelection_VVV(idx, VVV_cutbased_fo_noiso));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_tight_noiso", passMuonSelection_VVV(idx, VVV_cutbased_tight_noiso));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_veto_noiso" , passMuonSelection_VVV(idx, VVV_cutbased_veto_noiso));
        tx->pushbackToBranch<int>           ("lep_pdgId"                        , cms3.mus_charge()[idx]*(-13));
        tx->pushbackToBranch<float>         ("lep_ptRatio"                      , (closeJetPt > 0. ? cms3.mus_p4()[idx].pt() / closeJetPt : 1.));
        tx->pushbackToBranch<float>         ("lep_ptRel"                        , ptRel(cms3.mus_p4()[idx], temp_jet_p4, true));
        tx->pushbackToBranch<float>         ("lep_pterr"                        , cms3.mus_ptErr()[idx]);
        tx->pushbackToBranch<float>         ("lep_relIso03EAv2"                 , muRelIso03EA(idx, 2));
        tx->pushbackToBranch<int>           ("lep_tightCharge"                  , tightChargeMuon(idx));
        tx->pushbackToBranch<float>         ("lep_trk_pt"                       , cms3.mus_trk_p4()[idx].pt());
        tx->pushbackToBranch<int>           ("lep_charge"                       , cms3.mus_charge()[idx]);
        tx->pushbackToBranch<float>         ("lep_etaSC"                        , cms3.mus_p4()[idx].eta()); // Electron specific branch. Just take muon's regular eta.
        tx->pushbackToBranch<float>         ("lep_MVA"                          , -99);

        // Due to CMS4 not having pf candidates...
        std::cout.setstate(std::ios_base::failbit); // To suppress warning about CMS4 not having PF candidates
        if (cms3.evt_CMS3tag()[0].Contains("CMS3"))
            tx->pushbackToBranch<float>     ("lep_relIso04EAv2"                 , muRelIsoCustomCone(idx, 0.4, /*useVetoCones=*/false, 0.5, false, true, -1, 2));
        else
            tx->pushbackToBranch<float>     ("lep_relIso04EAv2"                 , muRelIso03EA(idx, 2));
        std::cout.clear();
    }
}

//##############################################################################################################
void babyMaker_v2::FillGenParticles()
{
    tx->setBranch<float>("gen_ht", coreGenPart.gen_ht);
    tx->setBranch<vector<LorentzVector>>("genPart_p4", coreGenPart.genPart_p4);
    tx->setBranch<vector<int>>("genPart_motherId", coreGenPart.genPart_motherId);
    tx->setBranch<vector<int>>("genPart_pdgId", coreGenPart.genPart_pdgId);
}

//##############################################################################################################
void babyMaker_v2::SortLeptonBranches()
{
    tx->sortVecBranchesByPt("lep_p4",
            {
            "lep_ip3d",
            "lep_ip3derr",
            "lep_ptRatio",
            "lep_ptRel",
            "lep_pterr",
            "lep_relIso03EAv2",
            "lep_relIso04EAv2",
            "lep_trk_pt",
            "lep_etaSC",
            },
            {
            "lep_pass_VVV_cutbased_fo_noiso",
            "lep_pass_VVV_cutbased_tight_noiso",
            "lep_pass_VVV_cutbased_veto_noiso",
            "lep_isTriggerSafe_v1",
            "lep_lostHits",
            "lep_motherIdSS",
            "lep_pdgId",
            "lep_tightCharge",
            "lep_charge",
            },
            {});
}

//##############################################################################################################
void babyMaker_v2::FillJets()
{
    coreBtagSF.clearSF();
    for (unsigned ijet = 0; ijet < coreJet.index.size(); ++ijet)
    {
        int idx = coreJet.index[ijet];
        float corr = coreJet.corrs[ijet];
        float shift = coreJet.shifts[ijet];
        float current_csv_val = cms3.getbtagvalue("pfCombinedInclusiveSecondaryVertexV2BJetTags", idx);

        // Check whether this jet overlaps with any of the leptons
        if (isLeptonOverlappingWithJet(idx))
            continue;

        LorentzVector jet = cms3.pfjets_p4()[idx] * cms3.pfjets_undoJEC()[idx] * corr;
        if (jet.pt() > 20)
        {
            tx->pushbackToBranch<LorentzVector>("jets_p4", jet);
            tx->pushbackToBranch<float>("jets_csv", current_csv_val);
            coreBtagSF.accumulateSF(idx, jet.pt(), jet.eta());
        }

        LorentzVector jet_up = jet * (1. + shift);
        if (jet_up.pt() > 20)
        {
            tx->pushbackToBranch<LorentzVector>("jets_up_p4", jet_up);
            tx->pushbackToBranch<float>("jets_up_csv", current_csv_val);
        }

        LorentzVector jet_dn = jet * (1. - shift);
        if (jet_dn.pt() > 20)
        {
            tx->pushbackToBranch<LorentzVector>("jets_dn_p4", jet_dn);
            tx->pushbackToBranch<float>("jets_dn_csv", current_csv_val);
        }
    }

    if (!cms3.evt_isRealData())
    {
        tx->setBranch<float>("weight_btagsf"         , coreBtagSF.btagprob_data     / coreBtagSF.btagprob_mc);
        tx->setBranch<float>("weight_btagsf_heavy_DN", coreBtagSF.btagprob_heavy_DN / coreBtagSF.btagprob_mc);
        tx->setBranch<float>("weight_btagsf_heavy_UP", coreBtagSF.btagprob_heavy_UP / coreBtagSF.btagprob_mc);
        tx->setBranch<float>("weight_btagsf_light_DN", coreBtagSF.btagprob_light_DN / coreBtagSF.btagprob_mc);
        tx->setBranch<float>("weight_btagsf_light_UP", coreBtagSF.btagprob_light_UP / coreBtagSF.btagprob_mc);
    }
}

//##############################################################################################################
void babyMaker_v2::FillMET()
{
    tx->setBranch<float>("met_pt", cms3.evt_pfmet());
    tx->setBranch<float>("met_phi", cms3.evt_pfmetPhi());
    tx->setBranch<float>("met_T1CHS_miniAOD_CORE_pt", coreMET.met_pt);
    tx->setBranch<float>("met_T1CHS_miniAOD_CORE_phi", coreMET.met_phi);
    tx->setBranch<float>("met_T1CHS_miniAOD_CORE_up_pt", coreMET.met_up_pt);
    tx->setBranch<float>("met_T1CHS_miniAOD_CORE_up_phi", coreMET.met_up_phi);
    tx->setBranch<float>("met_T1CHS_miniAOD_CORE_dn_pt", coreMET.met_dn_pt);
    tx->setBranch<float>("met_T1CHS_miniAOD_CORE_dn_phi", coreMET.met_dn_phi);
}

//##############################################################################################################
void babyMaker_v2::FillTracks()
{
    int nisotrack = 0;
    for (auto& idx : coreTrack.index)
    {
        // Check whether this track overlaps with any of the veto leptons
        if (isLeptonOverlappingWithTrack(idx))
            continue;
        nisotrack++;
    }

    // Set the branch
    tx->setBranch<int>("nisoTrack_mt2_cleaned_VVV_cutbased_veto", nisotrack);
}

//##############################################################################################################
void babyMaker_v2::SortJetBranches()
{
    tx->sortVecBranchesByPt("jets_p4", {"jets_csv"}, {}, {});
    tx->sortVecBranchesByPt("jets_up_p4", {"jets_up_csv"}, {}, {});
    tx->sortVecBranchesByPt("jets_dn_p4", {"jets_dn_csv"}, {}, {});
}

//##############################################################################################################
void babyMaker_v2::FillTrigger()
{
    tx->setBranch<int>("HLT_DoubleMu", coreTrigger.HLT_DoubleMu);
    tx->setBranch<int>("HLT_DoubleEl", coreTrigger.HLT_DoubleEl);
    tx->setBranch<int>("HLT_DoubleEl_DZ", coreTrigger.HLT_DoubleEl_DZ);
    tx->setBranch<int>("HLT_DoubleEl_DZ_2", coreTrigger.HLT_DoubleEl_DZ_2);
    tx->setBranch<int>("HLT_MuEG", coreTrigger.HLT_MuEG);
}

//##############################################################################################################
void babyMaker_v2::FillVertexInfo()
{
    tx->setBranch<int>("firstgoodvertex", firstGoodVertex());
    if (!cms3.evt_isRealData())
        tx->setBranch<int>("nTrueInt", cms3.puInfo_trueNumInteractions().at(0));
    else
        tx->setBranch<int>("nTrueInt", -999);
    int nVert = 0;
    for (unsigned int ivtx = 0; ivtx < cms3.evt_nvtxs(); ivtx++)
        if (isGoodVertex(ivtx)) nVert++;
    tx->setBranch<int>("nVert", nVert);
}

//##############################################################################################################
void babyMaker_v2::FillMETFilter()
{
    // get CMS3 version number to use later
    TString cms3_version = cms3.evt_CMS3tag()[0];

    // convert last two digits of version number to int
    int small_cms3_version = TString(cms3_version(cms3_version.Length() - 2, cms3_version.Length())).Atoi();

    // Compute whether this is a recent cms3 version
    bool recent_cms3_version = (cms3_version.Contains("V08-00") && small_cms3_version <= 12) ? false : true;

    if (cms3.evt_isRealData())
    {
        tx->setBranch<int>("Flag_ecalLaserCorrFilter", cms3.filt_ecalLaser());
        tx->setBranch<int>("Flag_hcalLaserEventFilter", cms3.filt_hcalLaser());
        tx->setBranch<int>("Flag_trackingFailureFilter", cms3.filt_trackingFailure());
        tx->setBranch<int>("Flag_CSCTightHaloFilter", cms3.filt_cscBeamHalo());
    }

    // in data and MC
    tx->setBranch<int>("Flag_HBHENoiseFilter", cms3.filt_hbheNoise());
    tx->setBranch<int>("Flag_HBHEIsoNoiseFilter", cms3.filt_hbheNoiseIso());
    tx->setBranch<int>("Flag_CSCTightHalo2015Filter", cms3.filt_cscBeamHalo2015());
    tx->setBranch<int>("Flag_EcalDeadCellTriggerPrimitiveFilter", cms3.filt_ecalTP());
    tx->setBranch<int>("Flag_goodVertices", cms3.filt_goodVertices());
    tx->setBranch<int>("Flag_eeBadScFilter", cms3.filt_eeBadSc());
    tx->setBranch<int>("Flag_badChargedCandidateFilter", badChargedCandidateFilter());

    // inputs for badMuonFilters in latest cms3 tags
    if (recent_cms3_version)
    {
        tx->setBranch<int>("Flag_globalTightHalo2016", cms3.filt_globalTightHalo2016());
        tx->setBranch<int>("Flag_badMuonFilter", badMuonFilter());
        tx->setBranch<int>("Flag_badMuonFilterv2", badMuonFilterV2());
        tx->setBranch<int>("Flag_badChargedCandidateFilterv2", badChargedCandidateFilterV2());
        if (small_cms3_version >= 18)
        {
            tx->setBranch<int>("Flag_badMuons", cms3.filt_badMuons());
            tx->setBranch<int>("Flag_duplicateMuons", cms3.filt_duplicateMuons());
            tx->setBranch<int>("Flag_noBadMuons", cms3.filt_noBadMuons());
        }
    }
}

//##############################################################################################################
void babyMaker_v2::FillTTree()
{
    tx->fill();
    tx->clear();
}

//##############################################################################################################
bool babyMaker_v2::isLeptonOverlappingWithJet(int idx)
{
    bool is_overlapping = false;

//    int idx = coreJet.index[ijet];
//    float corr = coreJet.corrs[ijet];
//    float shift = coreJet.shifts[ijet];
//    float pt = (cms3.pfjets_p4()[idx] * corr).pt();
//    float eta = (cms3.pfjets_p4()[idx] * corr).eta();

//    if (!(pt > JET_PT_MIN || (pt > BJET_PT_MIN && cms3.getbtagvalue("pfCombinedInclusiveSecondaryVertexV2BJetTags", idx) >= BJET_CSV_MED))) { return false; }
//    if (fabs(eta) > JET_ETA_MAX) { return false; }
//    if (!(isLoosePFJet_Summer16_v1(idx))) { return false; }

    for (auto& imu : coreMuon.index)
    {
        if (!(isLooseMuon(imu)))
            continue;

        if (ROOT::Math::VectorUtil::DeltaR(cms3.pfjets_p4()[idx], cms3.mus_p4()[imu]) < 0.4)
        {
            is_overlapping = true;
            break;
        }
    }

    if (is_overlapping)
        return true;

    for (auto& iel : coreElectron.index)
    {
        if (!(isLooseElectron(iel)))
            continue;

        if (ROOT::Math::VectorUtil::DeltaR(cms3.pfjets_p4()[idx], cms3.els_p4()[iel]) < 0.4)
        {
            is_overlapping = true;
            break;
        }
    }

    if (is_overlapping)
        return true;

    return false;
}

//##############################################################################################################
bool babyMaker_v2::isLeptonOverlappingWithTrack(int idx)
{
    bool is_overlapping = false;

    for (auto& imu : coreMuon.index)
    {
        if (!(isVetoMuon(imu)))
            continue;

        if (ROOT::Math::VectorUtil::DeltaR(cms3.pfcands_p4()[idx], cms3.mus_p4()[imu]) < 0.01)
        {
            is_overlapping = true;
            break;
        }
    }

    if (is_overlapping)
        return true;

    for (auto& iel : coreElectron.index)
    {
        if (!(isVetoElectron(iel)))
            continue;

        if (ROOT::Math::VectorUtil::DeltaR(cms3.pfcands_p4()[idx], cms3.els_p4()[iel]) < 0.01)
        {
            is_overlapping = true;
            break;
        }
    }

    if (is_overlapping)
        return true;

    return false;
}

////##############################################################################################################
//bool babyMaker_v2::isLooseMuon(int idx)
//{
//    if (!(coreMuon.pass(idx) && cms3.mus_p4()[idx].pt() > 20.)) return false;
//    return true;
//}
//
////##############################################################################################################
//bool babyMaker_v2::isLooseElectron(int idx)
//{
//    if (!(coreElectron.pass(idx) && cms3.els_p4()[idx].pt() > 20.)) return false;
//    return true;
//}

//##############################################################################################################
bool babyMaker_v2::isLooseMuon(int idx)
{
    const LorentzVector& temp_jet_p4 = closestJet(cms3.mus_p4()[idx], 0.4, 3.0, /*whichCorr = */2);
    float closeJetPt = temp_jet_p4.pt();
    float ptratio = (closeJetPt > 0. ? cms3.mus_p4()[idx].pt() / closeJetPt : 1.);
    if (!(passMuonSelection_VVV(idx, VVV_cutbased_fo_noiso)
                && fabs(cms3.mus_ip3d()[idx]) < 0.015
                && ptratio > 0.65
                && cms3.mus_p4()[idx].pt() > 20.))
        return false;
    return true;
}

//##############################################################################################################
bool babyMaker_v2::isLooseElectron(int idx)
{
    if (!(passElectronSelection_VVV(idx, VVV_cutbased_fo_noiso)
                && isTriggerSafe_v1(idx)
                && cms3.els_lostHits()[idx] == 0
                && tightChargeEle(idx) == 2
                && fabs(cms3.els_ip3d()[idx]) < 0.015
                && eleRelIso03EA(idx, 2) < 0.4
                && cms3.els_p4()[idx].pt() > 20.))
        return false;
    return true;
}

//##############################################################################################################
bool babyMaker_v2::isVetoMuon(int idx)
{
    if (!(passMuonSelection_VVV(idx, VVV_cutbased_veto)
                && cms3.mus_p4()[idx].pt() > 10.))
        return false;
    return true;
}

//##############################################################################################################
bool babyMaker_v2::isVetoElectron(int idx)
{
    if (!(passElectronSelection_VVV(idx, VVV_cutbased_veto)
                && cms3.els_p4()[idx].pt() > 10.))
        return false;
    return true;
}

