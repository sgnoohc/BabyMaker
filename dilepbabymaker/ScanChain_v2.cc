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

        // Triggers
        ProcessTriggers();

        // Loop over gen particles
        ProcessGenParticles();

        // Loop over electrons
        ProcessElectrons();

        // Loop over muons
        ProcessMuons();

        // Check preselection
        if (!PassPresel())
            continue;

        // Fill baby ntuple branches corresponding to lepton indices
        FillElectrons();

        // Fill baby ntuple branches corresponding to lepton indices
        FillMuons();

        // Fill generatore level particles
        FillGenParticles();

        // Organize leptons by sorting
        SortLeptonBranches();

        // Fill TTree (NOTE: also clears internal variables)
        FillOutput();

        // Photons Not needed

        // Select based on two leptons

        // Loop over jets (keep track of good ones for removal)

        // jet lepton overlap

        // Loop over good jets after removal and select

        // kinematic variables for pf cands (isotrack)

        coreJec.setJECFor(looper.getCurrentFileName());
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
    tx->createBranch<vector<LorentzVector>>("lep_p4");

    tx->createBranch<Int_t>("run");
    tx->createBranch<Int_t>("lumi");
    tx->createBranch<unsigned long long>("evt");
    tx->createBranch<int>("isData");
    tx->createBranch<float>("evt_scale1fb");

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

    tx->createBranch<vector<LorentzVector>>("jets_p4");
    tx->createBranch<vector<LorentzVector>>("jets_up_p4");
    tx->createBranch<vector<LorentzVector>>("jets_dn_p4");
    tx->createBranch<vector<float>>("jets_csv");
    tx->createBranch<vector<float>>("jets_up_csv");
    tx->createBranch<vector<float>>("jets_dn_csv");

    tx->createBranch<float>("met_pt");
    tx->createBranch<float>("met_phi");
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
bool babyMaker_v2::PassPresel()
{
    if (!(coreElectron.index.size() + coreMuon.index.size() >= 2)) return false;
    return true;
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
        //tx->pushbackToBranch<float>         ("lep_relIso04EAv2"                 , elRelIsoCustomCone(idx, 0.4, false, 0.0, /*useDBCorr=*/false, /*useEACorr=*/true, /*mindr=*/ -1, /*eaversion=*/2));
        tx->pushbackToBranch<float>         ("lep_relIso04EAv2"                 , eleRelIso03EA(idx, 2));
        tx->pushbackToBranch<int>           ("lep_tightCharge"                  , tightChargeEle(idx));
        tx->pushbackToBranch<float>         ("lep_trk_pt"                       , cms3.els_trk_p4()[idx].pt());
        tx->pushbackToBranch<int>           ("lep_charge"                       , cms3.els_charge()[idx]);
        tx->pushbackToBranch<float>         ("lep_etaSC"                        , cms3.els_etaSC()[idx]);
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
        //tx->pushbackToBranch<float>         ("lep_relIso04EAv2"                 , muRelIsoCustomCone(idx, 0.4, /*useVetoCones=*/false, 0.5, false, true, -1, 2));
        tx->pushbackToBranch<float>         ("lep_relIso04EAv2"                 , muRelIso03EA(idx, 2));
        tx->pushbackToBranch<int>           ("lep_tightCharge"                  , tightChargeMuon(idx));
        tx->pushbackToBranch<float>         ("lep_trk_pt"                       , cms3.mus_trk_p4()[idx].pt());
        tx->pushbackToBranch<int>           ("lep_charge"                       , cms3.mus_charge()[idx]);
        tx->pushbackToBranch<float>         ("lep_etaSC"                        , cms3.mus_p4()[idx].eta()); // Electron specific branch. Just take muon's regular eta.
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
void babyMaker_v2::FillOutput()
{
    tx->fill();
    tx->clear();
}
