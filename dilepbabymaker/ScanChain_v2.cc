#include "ScanChain_v2.h"

using namespace std;

//##############################################################################################################
void babyMaker_v2::ScanChain_v2(TChain* chain, std::string baby_name, int max_events, int index, bool verbose)
{

    // Looper
    RooUtil::Looper<CMS3> looper(chain, &cms3, max_events);

    // Output root file
    CreateOutput(index);

    int nskipped_batch = 0;
    int nskipped = 0;
    while (looper.nextEvent())
    {
        try
        {
            if (verbose)
                cout << "[verbose] Processed " << looper.getNEventsProcessed() << " out of " << chain->GetEntries() << endl;

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
        }
        catch (const std::ios_base::failure& e)
        {
            cout << endl;
            cout << "[CheckCorrupt] Caught an I/O failure in the ROOT file." << endl;
            cout << "[CheckCorrupt] Possibly corrupted hadoop file." << endl;
            cout << "[CheckCorrupt] event index = " << looper.getCurrentEventIndex() << " out of " << chain->GetEntries() << endl;
            cout << e.what() << endl;
            cout << endl;
            tx->clear(); // clear the TTree of any residual stuff

            nskipped_batch++;

            // If the nskipped is quite large than skip the entire file
            if (nskipped_batch > 500)
            {
                nskipped += nskipped_batch;
                nskipped_batch = 0;
                for (int i = 0; i < 10000; ++i)
                {
                    if (!looper.nextEvent())
                        break;
                    nskipped++;
                }
            }
        }
    }

    nskipped += nskipped_batch;

    looper.getTree()->PrintCacheStats();

    if (nskipped)
    {
        cout << "[CheckCorrupt] Skipped " << nskipped << " events out of " << chain->GetEntries() << " [" << float(nskipped) / float(chain->GetEntries()) << "%% loss]" << endl;
    }

    ofile->cd();
    t->Write();
//    t->SetDirectory(0);
}

//##############################################################################################################
void babyMaker_v2::CreateOutput(int index)
{
    ofile = new TFile(Form("output_%d.root", index), "recreate");
    t = new TTree("t", "t");
    tx = new RooUtil::TTreeX(t);

    tx->createBranch<Int_t>("run");
    tx->createBranch<Int_t>("lumi");
    tx->createBranch<unsigned long long>("evt");
    tx->createBranch<int>("isData");
    tx->createBranch<float>("evt_scale1fb");
    tx->createBranch<int>("evt_passgoodrunlist");

    tx->createBranch<int>("HLT_DoubleMu");
    tx->createBranch<int>("HLT_DoubleEl");
    tx->createBranch<int>("HLT_DoubleEl_DZ");
    tx->createBranch<int>("HLT_DoubleEl_DZ_2");
    tx->createBranch<int>("HLT_MuEG");

    tx->createBranch<vector<LorentzVector>>("lep_p4");
    tx->createBranch<vector<float>>("lep_coneCorrPt");
    tx->createBranch<vector<float>>("lep_ip3d");
    tx->createBranch<vector<float>>("lep_ip3derr");
    tx->createBranch<vector<int>>("lep_isTriggerSafe_v1");
    tx->createBranch<vector<int>>("lep_lostHits");
    tx->createBranch<vector<int>>("lep_convVeto");
    tx->createBranch<vector<int>>("lep_motherIdSS");
    tx->createBranch<vector<int>>("lep_pass_VVV_cutbased_3l_fo");
    tx->createBranch<vector<int>>("lep_pass_VVV_cutbased_3l_tight");
    tx->createBranch<vector<int>>("lep_pass_VVV_cutbased_fo");
    tx->createBranch<vector<int>>("lep_pass_VVV_cutbased_tight");
    tx->createBranch<vector<int>>("lep_pass_VVV_cutbased_veto");
    tx->createBranch<vector<int>>("lep_pass_VVV_cutbased_fo_noiso");
    tx->createBranch<vector<int>>("lep_pass_VVV_cutbased_tight_noiso");
    tx->createBranch<vector<int>>("lep_pass_VVV_cutbased_veto_noiso");
    tx->createBranch<vector<int>>("lep_pdgId");
    tx->createBranch<vector<float>>("lep_dxy");
    tx->createBranch<vector<float>>("lep_dz");
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
    tx->createBranch<vector<int>>("lep_isFromW");
    tx->createBranch<vector<int>>("lep_isFromZ");
    tx->createBranch<vector<int>>("lep_isFromB");
    tx->createBranch<vector<int>>("lep_isFromC");
    tx->createBranch<vector<int>>("lep_isFromL");
    tx->createBranch<vector<int>>("lep_isFromLF");
    tx->createBranch<vector<int>>("lep_genPart_index");

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
    tx->createBranch<vector<int>>("genPart_charge");
    tx->createBranch<vector<int>>("genPart_status");
    tx->createBranch<int>("ngenLep");
    tx->createBranch<int>("ngenLepFromTau");

    tx->createBranch<int>("Flag_EcalDeadCellTriggerPrimitiveFilter");
    tx->createBranch<int>("Flag_HBHEIsoNoiseFilter");
    tx->createBranch<int>("Flag_HBHENoiseFilter");
    tx->createBranch<int>("Flag_badChargedCandidateFilter");
    tx->createBranch<int>("Flag_badMuonFilter");
    tx->createBranch<int>("Flag_eeBadScFilter");
    tx->createBranch<int>("Flag_globalTightHalo2016");
    tx->createBranch<int>("Flag_goodVertices");

    // Summary variables
    tx->createBranch<int>("nVlep");
    tx->createBranch<int>("nTlep");
    tx->createBranch<int>("nTlepSS");
    tx->createBranch<int>("nLlep");

    tx->createBranch<int>("nSFOS");
    tx->createBranch<int>("nSFOSinZ");

    tx->createBranch<int>("nj");
    tx->createBranch<int>("nj_up");
    tx->createBranch<int>("nj_dn");

    tx->createBranch<int>("nj30");
    tx->createBranch<int>("nj30_up");
    tx->createBranch<int>("nj30_dn");

    tx->createBranch<float>("Mjj");
    tx->createBranch<float>("Mjj_up");
    tx->createBranch<float>("Mjj_dn");

    tx->createBranch<float>("MjjVBF");
    tx->createBranch<float>("MjjVBF_up");
    tx->createBranch<float>("MjjVBF_dn");

    tx->createBranch<float>("DetajjVBF");
    tx->createBranch<float>("DetajjVBF_up");
    tx->createBranch<float>("DetajjVBF_dn");

    tx->createBranch<float>("MjjL");
    tx->createBranch<float>("MjjL_up");
    tx->createBranch<float>("MjjL_dn");

    tx->createBranch<float>("DetajjL");
    tx->createBranch<float>("DetajjL_up");
    tx->createBranch<float>("DetajjL_dn");

    tx->createBranch<float>("MllSS");
    tx->createBranch<float>("MeeSS");
    tx->createBranch<float>("Mll3L");
    tx->createBranch<float>("Mee3L");
    tx->createBranch<float>("Mll3L1");
    tx->createBranch<float>("M3l");
    tx->createBranch<float>("Pt3l");
    tx->createBranch<float>("M01");
    tx->createBranch<float>("M02");
    tx->createBranch<float>("M12");
    tx->createBranch<int>("isSFOS01");
    tx->createBranch<int>("isSFOS02");
    tx->createBranch<int>("isSFOS12");

    tx->createBranch<float>("DPhi3lMET");
    tx->createBranch<float>("DPhi3lMET_up");
    tx->createBranch<float>("DPhi3lMET_dn");
    tx->createBranch<float>("MTmax");
    tx->createBranch<float>("MTmax_up");
    tx->createBranch<float>("MTmax_dn");

    tx->createBranch<float>("MT3rd");
    tx->createBranch<float>("MT3rd_up");
    tx->createBranch<float>("MT3rd_dn");


    tx->clear();
}

//##############################################################################################################
void babyMaker_v2::ProcessTriggers() { coreTrigger.process(); }

//##############################################################################################################
void babyMaker_v2::ProcessGenParticles() { coreGenPart.process(); }

//##############################################################################################################
void babyMaker_v2::ProcessElectrons() { coreElectron.process(isVetoElectron); }

//##############################################################################################################
void babyMaker_v2::ProcessMuons() { coreMuon.process(isVetoMuon); }

//##############################################################################################################
void babyMaker_v2::ProcessJets() { coreJet.process(coreJec); }

//##############################################################################################################
void babyMaker_v2::ProcessMET() { coreMET.process(coreJec); }

//##############################################################################################################
void babyMaker_v2::ProcessTracks() { coreTrack.process(); }

//##############################################################################################################
bool babyMaker_v2::PassPresel()
{
    // Select 2 SS lepton events or 3 or more lepton events
    vector<int> el_idx = coreElectron.index;
    vector<int> mu_idx = coreMuon.index;

    // If 3 or more veto lepton events. then require 3 and only 3 loose lepton events
    // Such requirement ensures simplicity in various things like SFOS counter and fake rate application
    // Also, require that it is total charge == 1
    if (el_idx.size() + mu_idx.size() > 2)
    {
        int nloose = 0;
        int chargesum = 0;
        for (auto& iel : coreElectron.index)
        {
            if (passElectronSelection_VVV(iel, VVV_cutbased_3l_fo_v2))
            {
                nloose++;
                chargesum += cms3.els_charge()[iel];
            }
        }
        for (auto& imu : coreMuon.index)
        {
            if (passMuonSelection_VVV(imu, VVV_cutbased_3l_fo_v2))
            {
                nloose++;
                chargesum += cms3.mus_charge()[imu];
            }
        }
        if (nloose == 3)
            return abs(chargesum) == 1;
        else
            return false;
    }
    // If less than 2 leptons skip
    if (el_idx.size() + mu_idx.size() < 2) return false;
    // If equal to 2 leptons then must be a same-sign and at must have two loose lepton
    int nloose = 0;
    for (auto& iel : coreElectron.index)
    {
        if (passElectronSelection_VVV(iel, VVV_cutbased_fo_v2))
            nloose++;
    }
    for (auto& imu : coreMuon.index)
    {
        if (passMuonSelection_VVV(imu, VVV_cutbased_fo_v2))
            nloose++;
    }
    if (nloose != 2)
        return false;
    if (mu_idx.size() == 2)
    {
        if (cms3.mus_charge()[mu_idx[0]] * cms3.mus_charge()[mu_idx[1]] > 0)
            return true;
        else
            return false;
    }
    else if (el_idx.size() == 2)
    {
        if (cms3.els_charge()[el_idx[0]] * cms3.els_charge()[el_idx[1]] > 0)
            return true;
        else
            return false;
    }
    else if (mu_idx.size() == 1 && el_idx.size() == 1)
    {
        if (cms3.mus_charge()[mu_idx[0]] * cms3.els_charge()[el_idx[0]] > 0)
            return true;
        else
            return false;
    }
    else
    {
        cout << "FATAL ERROR: I Should never be here!" << endl;
        return false;
    }
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

    // Fill summary variables
    FillSummaryVariables();

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
    if (cms3.evt_isRealData())
    {
        tx->setBranch<float>("evt_scale1fb", 1);
        tx->setBranch<int>("evt_passgoodrunlist", goodrun(cms3.evt_run(), cms3.evt_lumiBlock()));
    }
    else
    {
        tx->setBranch<float>("evt_scale1fb", coreDatasetInfo.getScale1fb());
        tx->setBranch<int>("evt_passgoodrunlist", true);
    }
}

//##############################################################################################################
void babyMaker_v2::FillElectrons()
{
    for (auto& idx : coreElectron.index)
    {
        // Some variables that need to call another functions...
        const LorentzVector& temp_jet_p4 = closestJet(cms3.els_p4()[idx], 0.4, 3.0, /*whichCorr = */2);
        float closeJetPt = temp_jet_p4.pt();
        float ptratio = (closeJetPt > 0. ? cms3.els_p4()[idx].pt() / closeJetPt : 1.);
        float conecorrptfactorraw = coreElectron.index.size() + coreMuon.index.size() > 2 ?  0.84 / ptratio : 0.9 / ptratio;
        float conecorrptfactor = max(0., conecorrptfactorraw - 1.) + 1.; // To clip correcting once it passes tight isolation criteria

        if (coreElectron.index.size() + coreMuon.index.size() == 2)
        {
            if (!( passElectronSelection_VVV(idx, VVV_cutbased_fo_v2) ))
                continue;
        }
        else if (coreElectron.index.size() + coreMuon.index.size() > 2)
        {
            if (!( passElectronSelection_VVV(idx, VVV_cutbased_3l_fo_v2) ))
                continue;
        }

        tx->pushbackToBranch<LorentzVector> ("lep_p4"                           , cms3.els_p4()[idx]);
        tx->pushbackToBranch<float>         ("lep_coneCorrPt"                   , cms3.els_p4()[idx].pt() * conecorrptfactor);
        tx->pushbackToBranch<float>         ("lep_ip3d"                         , cms3.els_ip3d()[idx]);
        tx->pushbackToBranch<float>         ("lep_ip3derr"                      , cms3.els_ip3derr()[idx]);
        tx->pushbackToBranch<int>           ("lep_isTriggerSafe_v1"             , isTriggerSafe_v1(idx));
        tx->pushbackToBranch<int>           ("lep_lostHits"                     , cms3.els_lostHits()[idx]);
        tx->pushbackToBranch<int>           ("lep_convVeto"                     , !cms3.els_conv_vtx_flag()[idx]);
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_3l_fo"      , passElectronSelection_VVV(idx, VVV_cutbased_3l_fo_v2));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_3l_tight"   , passElectronSelection_VVV(idx, VVV_cutbased_3l_tight_v2));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_fo"         , passElectronSelection_VVV(idx, VVV_cutbased_fo_v2));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_tight"      , passElectronSelection_VVV(idx, VVV_cutbased_tight_v2));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_veto"       , passElectronSelection_VVV(idx, VVV_cutbased_veto_v2));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_fo_noiso"   , passElectronSelection_VVV(idx, VVV_cutbased_fo_noiso_v2));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_tight_noiso", passElectronSelection_VVV(idx, VVV_cutbased_tight_noiso_v2));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_veto_noiso" , passElectronSelection_VVV(idx, VVV_cutbased_veto_noiso_v2));
        tx->pushbackToBranch<int>           ("lep_pdgId"                        , cms3.els_charge()[idx]*(-11));
        tx->pushbackToBranch<float>         ("lep_dxy"                          , cms3.els_dxyPV()[idx]);
        tx->pushbackToBranch<float>         ("lep_dz"                           , cms3.els_dzPV()[idx]);
        tx->pushbackToBranch<float>         ("lep_ptRatio"                      , ptratio);
        tx->pushbackToBranch<float>         ("lep_ptRel"                        , ptRel(cms3.els_p4()[idx], temp_jet_p4, true));
        tx->pushbackToBranch<float>         ("lep_pterr"                        , cms3.els_ptErr()[idx]);
        tx->pushbackToBranch<float>         ("lep_relIso03EAv2"                 , eleRelIso03EA(idx, 2));
        tx->pushbackToBranch<int>           ("lep_tightCharge"                  , tightChargeEle(idx));
        tx->pushbackToBranch<float>         ("lep_trk_pt"                       , cms3.els_trk_p4()[idx].pt());
        tx->pushbackToBranch<int>           ("lep_charge"                       , cms3.els_charge()[idx]);
        tx->pushbackToBranch<float>         ("lep_etaSC"                        , cms3.els_etaSC()[idx]);
        tx->pushbackToBranch<float>         ("lep_MVA"                          , getMVAoutput(idx));
        if (!cms3.evt_isRealData())
        {
            pair<int, int> motherId_genIdx = lepMotherID_v2(Lep(cms3.els_charge()[idx] * (-11), idx)); //don't forget the sign
            tx->pushbackToBranch<int>       ("lep_motherIdSS"                   , motherId_genIdx.first);
            tx->pushbackToBranch<int>       ("lep_genPart_index"                , motherId_genIdx.second);
            tx->pushbackToBranch<int>       ("lep_isFromW"                      , isFromW(11, idx));
            tx->pushbackToBranch<int>       ("lep_isFromZ"                      , isFromZ(11, idx));
            tx->pushbackToBranch<int>       ("lep_isFromB"                      , isFromB(11, idx));
            tx->pushbackToBranch<int>       ("lep_isFromC"                      , isFromC(11, idx));
            tx->pushbackToBranch<int>       ("lep_isFromL"                      , isFromLight(11, idx));
            tx->pushbackToBranch<int>       ("lep_isFromLF"                     , isFromLightFake(11, idx));
        }
        else
        {
            tx->pushbackToBranch<int>       ("lep_motherIdSS"                   , 99);
            tx->pushbackToBranch<int>       ("lep_genPart_index"                , -1);
            tx->pushbackToBranch<int>       ("lep_isFromW"                      , -1);
            tx->pushbackToBranch<int>       ("lep_isFromZ"                      , -1);
            tx->pushbackToBranch<int>       ("lep_isFromB"                      , -1);
            tx->pushbackToBranch<int>       ("lep_isFromC"                      , -1);
            tx->pushbackToBranch<int>       ("lep_isFromL"                      , -1);
            tx->pushbackToBranch<int>       ("lep_isFromLF"                     , -1);
        }

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
        const LorentzVector& temp_jet_p4 = closestJet(cms3.mus_p4()[idx], 0.4, 3.0, /*whichCorr = */2);
        float closeJetPt = temp_jet_p4.pt();
        float ptratio = (closeJetPt > 0. ? cms3.mus_p4()[idx].pt() / closeJetPt : 1.);
        float conecorrptfactorraw = coreElectron.index.size() + coreMuon.index.size() > 2 ?  0.84 / ptratio : 0.9 / ptratio;
        float conecorrptfactor = max(0., conecorrptfactorraw - 1.) + 1.; // To clip correcting once it passes tight isolation criteria

        if (coreMuon.index.size() + coreMuon.index.size() == 2)
        {
            if (!( passMuonSelection_VVV(idx, VVV_cutbased_fo_v2) ))
                continue;
        }
        else if (coreMuon.index.size() + coreMuon.index.size() > 2)
        {
            if (!( passMuonSelection_VVV(idx, VVV_cutbased_3l_fo_v2) ))
                continue;
        }

        tx->pushbackToBranch<LorentzVector> ("lep_p4"                           , cms3.mus_p4()[idx]);
        tx->pushbackToBranch<float>         ("lep_coneCorrPt"                   , cms3.mus_p4()[idx].pt() * conecorrptfactor);
        tx->pushbackToBranch<float>         ("lep_ip3d"                         , cms3.mus_ip3d()[idx]);
        tx->pushbackToBranch<float>         ("lep_ip3derr"                      , cms3.mus_ip3derr()[idx]);
        tx->pushbackToBranch<int>           ("lep_isTriggerSafe_v1"             , true); // Electron specific branch. So muons always pass.
        tx->pushbackToBranch<int>           ("lep_lostHits"                     , cms3.mus_lostHits()[idx]);
        tx->pushbackToBranch<int>           ("lep_convVeto"                     , 1);
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_3l_fo"      , passMuonSelection_VVV(idx, VVV_cutbased_3l_fo_v2));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_3l_tight"   , passMuonSelection_VVV(idx, VVV_cutbased_3l_tight_v2));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_fo"         , passMuonSelection_VVV(idx, VVV_cutbased_fo_v2));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_tight"      , passMuonSelection_VVV(idx, VVV_cutbased_tight_v2));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_veto"       , passMuonSelection_VVV(idx, VVV_cutbased_veto_v2));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_fo_noiso"   , passMuonSelection_VVV(idx, VVV_cutbased_fo_noiso_v2));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_tight_noiso", passMuonSelection_VVV(idx, VVV_cutbased_tight_noiso_v2));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_veto_noiso" , passMuonSelection_VVV(idx, VVV_cutbased_veto_noiso_v2));
        tx->pushbackToBranch<int>           ("lep_pdgId"                        , cms3.mus_charge()[idx]*(-13));
        tx->pushbackToBranch<float>         ("lep_dxy"                          , cms3.mus_dxyPV()[idx]);
        tx->pushbackToBranch<float>         ("lep_dz"                           , cms3.mus_dzPV()[idx]);
        tx->pushbackToBranch<float>         ("lep_ptRatio"                      , ptratio);
        tx->pushbackToBranch<float>         ("lep_ptRel"                        , ptRel(cms3.mus_p4()[idx], temp_jet_p4, true));
        tx->pushbackToBranch<float>         ("lep_pterr"                        , cms3.mus_ptErr()[idx]);
        tx->pushbackToBranch<float>         ("lep_relIso03EAv2"                 , muRelIso03EA(idx, 2));
        tx->pushbackToBranch<int>           ("lep_tightCharge"                  , tightChargeMuon(idx));
        tx->pushbackToBranch<float>         ("lep_trk_pt"                       , cms3.mus_trk_p4()[idx].pt());
        tx->pushbackToBranch<int>           ("lep_charge"                       , cms3.mus_charge()[idx]);
        tx->pushbackToBranch<float>         ("lep_etaSC"                        , cms3.mus_p4()[idx].eta()); // Electron specific branch. Just take muon's regular eta.
        tx->pushbackToBranch<float>         ("lep_MVA"                          , -99);
        if (!cms3.evt_isRealData())
        {
            pair<int, int> motherId_genIdx = lepMotherID_v2(Lep(cms3.mus_charge()[idx] * (-13), idx)); //don't forget the sign
            tx->pushbackToBranch<int>       ("lep_motherIdSS"                   , motherId_genIdx.first);
            tx->pushbackToBranch<int>       ("lep_genPart_index"                , motherId_genIdx.second);
            tx->pushbackToBranch<int>       ("lep_isFromW"                      , isFromW(13, idx));
            tx->pushbackToBranch<int>       ("lep_isFromZ"                      , isFromZ(13, idx));
            tx->pushbackToBranch<int>       ("lep_isFromB"                      , isFromB(13, idx));
            tx->pushbackToBranch<int>       ("lep_isFromC"                      , isFromC(13, idx));
            tx->pushbackToBranch<int>       ("lep_isFromL"                      , isFromLight(13, idx));
            tx->pushbackToBranch<int>       ("lep_isFromLF"                     , isFromLightFake(13, idx));
        }
        else
        {
            tx->pushbackToBranch<int>       ("lep_motherIdSS"                   , 99);
            tx->pushbackToBranch<int>       ("lep_genPart_index"                , -1);
            tx->pushbackToBranch<int>       ("lep_isFromW"                      , -1);
            tx->pushbackToBranch<int>       ("lep_isFromZ"                      , -1);
            tx->pushbackToBranch<int>       ("lep_isFromB"                      , -1);
            tx->pushbackToBranch<int>       ("lep_isFromC"                      , -1);
            tx->pushbackToBranch<int>       ("lep_isFromL"                      , -1);
            tx->pushbackToBranch<int>       ("lep_isFromLF"                     , -1);
        }

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
    if (cms3.evt_isRealData())
        return;
    tx->setBranch<float>("gen_ht", coreGenPart.gen_ht);
    tx->setBranch<vector<LorentzVector>>("genPart_p4", coreGenPart.genPart_p4);
    tx->setBranch<vector<int>>("genPart_motherId", coreGenPart.genPart_motherId);
    tx->setBranch<vector<int>>("genPart_pdgId", coreGenPart.genPart_pdgId);
    tx->setBranch<vector<int>>("genPart_charge", coreGenPart.genPart_charge);
    tx->setBranch<vector<int>>("genPart_status", coreGenPart.genPart_status);
    tx->setBranch<int>("ngenLep", coreGenPart.ngenLep);
    tx->setBranch<int>("ngenLepFromTau", coreGenPart.ngenLepFromTau);
}

//##############################################################################################################
void babyMaker_v2::SortLeptonBranches()
{
    tx->sortVecBranchesByPt("lep_p4",
            {
            "lep_dxy",
            "lep_dz",
            "lep_ip3d",
            "lep_ip3derr",
            "lep_ptRatio",
            "lep_ptRel",
            "lep_pterr",
            "lep_relIso03EAv2",
            "lep_relIso04EAv2",
            "lep_trk_pt",
            "lep_etaSC",
            "lep_MVA",
            "lep_coneCorrPt",
            },
            {
            "lep_pass_VVV_cutbased_3l_fo",
            "lep_pass_VVV_cutbased_3l_tight",
            "lep_pass_VVV_cutbased_fo",
            "lep_pass_VVV_cutbased_tight",
            "lep_pass_VVV_cutbased_veto",
            "lep_pass_VVV_cutbased_fo_noiso",
            "lep_pass_VVV_cutbased_tight_noiso",
            "lep_pass_VVV_cutbased_veto_noiso",
            "lep_isTriggerSafe_v1",
            "lep_lostHits",
            "lep_convVeto",
            "lep_motherIdSS",
            "lep_genPart_index",
            "lep_pdgId",
            "lep_tightCharge",
            "lep_charge",
            "lep_isFromW",
            "lep_isFromZ",
            "lep_isFromB",
            "lep_isFromC",
            "lep_isFromL",
            "lep_isFromLF",
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
        if (isLeptonOverlappingWithJet(ijet))
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
void babyMaker_v2::FillSummaryVariables()
{
    FillJetVariables(0);
    FillJetVariables(1);
    FillJetVariables(-1);
    FillLeptonVariables();
}

//##############################################################################################################
void babyMaker_v2::FillTTree()
{
    tx->fill();
    tx->clear();
}

//##############################################################################################################
bool babyMaker_v2::isLeptonOverlappingWithJet(int ijet)
{
    bool is_overlapping = false;

    int idx = coreJet.index[ijet];

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

//##############################################################################################################
// Used to overlap remova against jets
bool babyMaker_v2::isLooseMuon(int idx)
{
    if (!( cms3.mus_p4()[idx].pt() > 20.                     )) return false;
    if (!( passMuonSelection_VVV(idx, VVV_cutbased_3l_fo_v2) )) return false;
    return true;
}

//##############################################################################################################
// Used to overlap remova against jets
bool babyMaker_v2::isLooseElectron(int idx)
{
    if (!( cms3.els_p4()[idx].pt() > 20.                         )) return false;
    if (!( passElectronSelection_VVV(idx, VVV_cutbased_3l_fo_v2) )) return false;
    return true;
}

//##############################################################################################################
// Used to overlap remova against tracks
bool babyMaker_v2::isVetoMuon(int idx)
{
    if (!( passMuonSelection_VVV(idx, VVV_cutbased_veto_v2) )) return false;
    return true;
}

//##############################################################################################################
// Used to overlap remova against tracks
bool babyMaker_v2::isVetoElectron(int idx)
{
    if (!( passElectronSelection_VVV(idx, VVV_cutbased_veto_v2) )) return false;
    return true;
}

//##############################################################################################################
int babyMaker_v2::passCount(const vector<int>& v)
{
    return std::count_if(v.begin(), v.end(), [](int i){return i > 0;});
}

//##############################################################################################################
int babyMaker_v2::nSFOS()
{
    int nSFOS = 0;
    for (auto& pdgid0 : tx->getBranch<vector<int>>("lep_pdgId"))
        for (auto& pdgid1 : tx->getBranch<vector<int>>("lep_pdgId"))
            if (pdgid0 == -pdgid1)
                nSFOS++;
    return nSFOS/2; // Because the nested for loop double counts
}

//##############################################################################################################
void babyMaker_v2::FillJetVariables(int variation)
{
    //
    // Assumes FillJets and SortJetBranches are already called
    //

    TString jets_csv     = variation == 0 ? "jets_csv"   : variation == 1 ? "jets_up_csv"   : "jets_dn_csv";
    TString jets_p4      = variation == 0 ? "jets_p4"    : variation == 1 ? "jets_up_p4"    : "jets_dn_p4";
    TString nj_bn        = variation == 0 ? "nj"         : variation == 1 ? "nj_up"         : "nj_dn";
    TString nj30_bn      = variation == 0 ? "nj30"       : variation == 1 ? "nj30_up"       : "nj30_dn";
    TString nb_bn        = variation == 0 ? "nb"         : variation == 1 ? "nb_up"         : "nb_dn";
    TString Mjj_bn       = variation == 0 ? "Mjj"        : variation == 1 ? "Mjj_up"        : "Mjj_dn";
    TString MjjL_bn      = variation == 0 ? "MjjL"       : variation == 1 ? "MjjL_up"       : "MjjL_dn";
    TString DetajjL_bn   = variation == 0 ? "DetajjL"    : variation == 1 ? "DetajjL_up"    : "DetajjL_dn";
    TString MjjVBF_bn    = variation == 0 ? "MjjVBF"     : variation == 1 ? "MjjVBF_up"     : "MjjVBF_dn";
    TString DetajjVBF_bn = variation == 0 ? "DetajjVBF"  : variation == 1 ? "DetajjVBF_up"  : "DetajjVBF_dn";

    int nj = 0;
    int nj30 = 0;
    int nb = 0;
    float Mjj = 0;
    float MjjL = -999;
    float DetajjL = -999;
    float MjjVBF = -999;
    float DetajjVBF = -999;
    float tmpDR = 9999;
    for (unsigned int i = 0; i < tx->getBranch<vector<float>>(jets_csv).size(); ++i)
    {
        const LV& p4 = tx->getBranch<vector<LV>>(jets_p4)[i];
        const float& csv= tx->getBranch<vector<float>>(jets_csv)[i];

        // nb jets
        if (!( p4.pt() > 20. ))
            continue;
        if (fabs(p4.eta()) < 2.4 && csv >= 0.5426)
            nb++;

        // njets across all eta
        if (!( p4.pt() > 30. ))
            continue;
        if (fabs(p4.eta()) < 5.0)
            nj++;

        // njets for central for SS
        if (fabs(p4.eta()) < 2.5)
            nj30++;

        // Compute Mjj using the closest two jets
        for (unsigned int j = i + 1; j < tx->getBranch<vector<float>>(jets_csv).size(); ++j)
        {
            const LV& p4_2 = tx->getBranch<vector<LV>>(jets_p4)[j];

            // central eta
            if (fabs(p4.eta()) < 2.5 && fabs(p4_2.eta()) < 2.5)
            {
                // Choose the closest two jets
                float this_dR = ROOT::Math::VectorUtil::DeltaR(p4, p4_2);
                if (this_dR < tmpDR)
                {
                    tmpDR = this_dR;
                    Mjj = (p4 + p4_2).M();
                }

                // If they were not set then set (this makes it choose two leading ones)
                if (MjjL < 0)
                {
                    MjjL = (p4 + p4_2).M();
                    DetajjL = fabs(p4.eta() - p4_2.eta());
                }
            }

            // all eta
            if (fabs(p4.eta()) < 5.0 && fabs(p4_2.eta()) < 5.0)
            {
                // If they were not set then set (this makes it choose two leading ones)
                if (MjjVBF < 0)
                {
                    MjjVBF = (p4 + p4_2).M();
                    DetajjVBF = fabs(p4.eta() - p4_2.eta());
                }
            }
        }
    }
    tx->setBranch<int>(nj_bn, nj);
    tx->setBranch<int>(nj30_bn, nj30);
    tx->setBranch<int>(nb_bn, nb);
    tx->setBranch<float>(Mjj_bn, Mjj);
    tx->setBranch<float>(MjjL_bn, MjjL);
    tx->setBranch<float>(DetajjL_bn, DetajjL);
    tx->setBranch<float>(MjjVBF_bn, MjjVBF);
    tx->setBranch<float>(DetajjVBF_bn, DetajjVBF);
}

//##############################################################################################################
void babyMaker_v2::FillLeptonVariables()
{

    //
    // Assumes FillElectrons and FillLeptons as well as SortLeptonBranches are called
    //

    // Calculate tight and loose lepton based on number of veto leptons
    int nVlep = coreElectron.index.size() + coreMuon.index.size();
    int nTlep = nVlep == 2 ? passCount(tx->getBranch<vector<int>>("lep_pass_VVV_cutbased_tight")) : passCount(tx->getBranch<vector<int>>("lep_pass_VVV_cutbased_3l_tight"));
    int nLlep = nVlep == 2 ? passCount(tx->getBranch<vector<int>>("lep_pass_VVV_cutbased_fo")) : passCount(tx->getBranch<vector<int>>("lep_pass_VVV_cutbased_3l_fo"));
    int nTlepSS = passCount(tx->getBranch<vector<int>>("lep_pass_VVV_cutbased_tight"));

    // Set the number of lepton counter
    tx->setBranch<int>("nVlep", nVlep);
    tx->setBranch<int>("nTlep", nTlep);
    tx->setBranch<int>("nTlepSS", nTlepSS);
    tx->setBranch<int>("nLlep", nLlep);

    // nVlep == 2
    //  nLlep == 2 isSS
    // nVlep >= 3
    //  nLlep == 3 is3l
    //    nLlepSS >= 2 (is the pair a same-sign?) need idx isSS3lCR

    bool isSS = (nVlep == 2 && nLlep == 2);
    bool is3L = (nVlep >= 3 && nLlep == 3);

    // is SS events then set the SS related variables
    if (isSS)
    {
        FillSSLeptonVariables(0, 1);
    }
    // is 3L events then set the 3L related variables
    else if (is3L)
    {
        Fill3LLeptonVariables();

        // If it additionally passes isSSCR then set the "Same-sign" variables for the 3L events
        bool issscr;
        int index0;
        int index1;
        tie(issscr, index0, index1) = isSSCR();
        if (issscr)
        {
            FillSSLeptonVariables(index0, index1);
        }
    }
}

//##############################################################################################################
void babyMaker_v2::FillSSLeptonVariables(int idx0, int idx1)
{
    const vector<LV>& lep_p4 = tx->getBranch<vector<LV>>("lep_p4");
    const vector<int>& lep_pdgId = tx->getBranch<vector<int>>("lep_pdgId");

    tx->setBranch<float>("MllSS", (lep_p4[idx0] + lep_p4[idx1]).mass());
    if (abs(lep_pdgId[idx0]) == 11 && abs(lep_pdgId[idx1]) == 11)
        tx->setBranch<float>("MeeSS", (lep_p4[idx0] + lep_p4[idx1]).mass());

    // Set up MET variables
    const float& met_pt = tx->getBranch<float>("met_pt");
    const float& met_phi = tx->getBranch<float>("met_phi");
    const float& met_T1CHS_miniAOD_CORE_up_pt = tx->getBranch<float>("met_T1CHS_miniAOD_CORE_up_pt");
    const float& met_T1CHS_miniAOD_CORE_up_phi = tx->getBranch<float>("met_T1CHS_miniAOD_CORE_up_phi");
    const float& met_T1CHS_miniAOD_CORE_dn_pt = tx->getBranch<float>("met_T1CHS_miniAOD_CORE_dn_pt");
    const float& met_T1CHS_miniAOD_CORE_dn_phi = tx->getBranch<float>("met_T1CHS_miniAOD_CORE_dn_phi");
    LV MET;
    LV MET_up;
    LV MET_dn;
    MET.SetPxPyPzE( met_pt * TMath::Cos(met_phi), met_pt * TMath::Sin(met_phi), 0, met_pt);
    MET_up.SetPxPyPzE( met_T1CHS_miniAOD_CORE_up_pt * TMath::Cos(met_T1CHS_miniAOD_CORE_up_phi), met_T1CHS_miniAOD_CORE_up_pt * TMath::Sin(met_T1CHS_miniAOD_CORE_up_phi), 0, met_T1CHS_miniAOD_CORE_up_pt);
    MET_dn.SetPxPyPzE( met_T1CHS_miniAOD_CORE_dn_pt * TMath::Cos(met_T1CHS_miniAOD_CORE_dn_phi), met_T1CHS_miniAOD_CORE_dn_pt * TMath::Sin(met_T1CHS_miniAOD_CORE_dn_phi), 0, met_T1CHS_miniAOD_CORE_dn_pt);

    float MT0    = mT(lep_p4[idx0], MET);
    float MT1    = mT(lep_p4[idx1], MET);
    float MT0_up = mT(lep_p4[idx0], MET_up);
    float MT1_up = mT(lep_p4[idx1], MET_up);
    float MT0_dn = mT(lep_p4[idx0], MET_dn);
    float MT1_dn = mT(lep_p4[idx1], MET_dn);

    tx->setBranch<float>("MTmax", MT0 > MT1 ? MT0 : MT1);
    tx->setBranch<float>("MTmax_up", MT0_up > MT1_up ? MT0_up : MT1_up);
    tx->setBranch<float>("MTmax_dn", MT0_dn > MT1_dn ? MT0_dn : MT1_dn);
}

//##############################################################################################################
void babyMaker_v2::Fill3LLeptonVariables()
{
    int nSFOS = babyMaker_v2::nSFOS();
    int nSFOSinZ = 0;
    if (nSFOS == 0)
    {
        tx->setBranch<float>("Mll3L", get0SFOSMll());
        tx->setBranch<float>("Mee3L", get0SFOSMee());
    }
    else if (nSFOS == 1)
    {
        tx->setBranch<float>("Mll3L", get1SFOSMll());
        if (fabs(tx->getBranch<float>("Mll3L") - 91.1876) < 10.)
            nSFOSinZ = 1;
    }
    else if (nSFOS == 2)
    {
        tx->setBranch<float>("Mll3L", get2SFOSMll0());
        tx->setBranch<float>("Mll3L1", get2SFOSMll1());
        if (fabs(tx->getBranch<float>("Mll3L") - 91.1876) < 10.)
            nSFOSinZ++;
        if (fabs(tx->getBranch<float>("Mll3L1") - 91.1876) < 10.)
            nSFOSinZ++;
    }
    tx->setBranch<int>("nSFOS", nSFOS);
    tx->setBranch<int>("nSFOSinZ", nSFOSinZ);

    const vector<LV>& lep_p4 = tx->getBranch<vector<LV>>("lep_p4");
    const vector<int>& lep_pdgId = tx->getBranch<vector<int>>("lep_pdgId");

    // Extra variables related to the three leptons
    tx->setBranch<float>("M3l", (lep_p4[0] + lep_p4[1] + lep_p4[2]).mass());
    tx->setBranch<float>("Pt3l", (lep_p4[0] + lep_p4[1] + lep_p4[2]).pt());
    tx->setBranch<float>("M01", (lep_p4[0] + lep_p4[1]).mass());
    tx->setBranch<float>("M02", (lep_p4[0] + lep_p4[2]).mass());
    tx->setBranch<float>("M12", (lep_p4[1] + lep_p4[2]).mass());
    tx->setBranch<int>("isSFOS01", lep_pdgId[0] == -lep_pdgId[1]);
    tx->setBranch<int>("isSFOS02", lep_pdgId[0] == -lep_pdgId[2]);
    tx->setBranch<int>("isSFOS12", lep_pdgId[1] == -lep_pdgId[2]);

    // Set up MET variables
    const float& met_pt = tx->getBranch<float>("met_pt");
    const float& met_phi = tx->getBranch<float>("met_phi");
    const float& met_T1CHS_miniAOD_CORE_up_pt = tx->getBranch<float>("met_T1CHS_miniAOD_CORE_up_pt");
    const float& met_T1CHS_miniAOD_CORE_up_phi = tx->getBranch<float>("met_T1CHS_miniAOD_CORE_up_phi");
    const float& met_T1CHS_miniAOD_CORE_dn_pt = tx->getBranch<float>("met_T1CHS_miniAOD_CORE_dn_pt");
    const float& met_T1CHS_miniAOD_CORE_dn_phi = tx->getBranch<float>("met_T1CHS_miniAOD_CORE_dn_phi");
    LV MET;
    LV MET_up;
    LV MET_dn;
    MET.SetPxPyPzE( met_pt * TMath::Cos(met_phi), met_pt * TMath::Sin(met_phi), 0, met_pt);
    MET_up.SetPxPyPzE( met_T1CHS_miniAOD_CORE_up_pt * TMath::Cos(met_T1CHS_miniAOD_CORE_up_phi), met_T1CHS_miniAOD_CORE_up_pt * TMath::Sin(met_T1CHS_miniAOD_CORE_up_phi), 0, met_T1CHS_miniAOD_CORE_up_pt);
    MET_dn.SetPxPyPzE( met_T1CHS_miniAOD_CORE_dn_pt * TMath::Cos(met_T1CHS_miniAOD_CORE_dn_phi), met_T1CHS_miniAOD_CORE_dn_pt * TMath::Sin(met_T1CHS_miniAOD_CORE_dn_phi), 0, met_T1CHS_miniAOD_CORE_dn_pt);

    // Set MET lep related variables
    tx->setBranch<float>("DPhi3lMET"   , fabs(ROOT::Math::VectorUtil::DeltaPhi((lep_p4[0] + lep_p4[1] + lep_p4[2]), MET   )));
    tx->setBranch<float>("DPhi3lMET_up", fabs(ROOT::Math::VectorUtil::DeltaPhi((lep_p4[0] + lep_p4[1] + lep_p4[2]), MET_up)));
    tx->setBranch<float>("DPhi3lMET_dn", fabs(ROOT::Math::VectorUtil::DeltaPhi((lep_p4[0] + lep_p4[1] + lep_p4[2]), MET_dn)));

    if (nSFOS == 1)
    {
        int idx = -1;
        if (lep_pdgId[0] == -lep_pdgId[1]) idx = 2;
        if (lep_pdgId[0] == -lep_pdgId[2]) idx = 1;
        if (lep_pdgId[1] == -lep_pdgId[2]) idx = 0;
        tx->setBranch<float>("MT3rd"   , mT(lep_p4[idx], MET   ));
        tx->setBranch<float>("MT3rd_up", mT(lep_p4[idx], MET_up));
        tx->setBranch<float>("MT3rd_dn", mT(lep_p4[idx], MET_dn));
    }
}

//##############################################################################################################
float babyMaker_v2::get0SFOSMll()
{
    const vector<int>& lep_pdgId = tx->getBranch<vector<int>>("lep_pdgId");
    const vector<LV>& lep_p4 = tx->getBranch<vector<LV>>("lep_p4");

    int pdgid0 = lep_pdgId[0];
    int pdgid1 = lep_pdgId[1];
    int pdgid2 = lep_pdgId[2];

    if (pdgid0 == pdgid1)
        return (lep_p4[0] + lep_p4[1]).mass();
    else if (pdgid0 == pdgid2)
        return (lep_p4[0] + lep_p4[2]).mass();
    else if (pdgid1 == pdgid2)
        return (lep_p4[1] + lep_p4[2]).mass();

    cout << "Warning: Shouldn't be here if function call are at the right places." << endl;

    return -999;
}

//##############################################################################################################
float babyMaker_v2::get0SFOSMee()
{
    const vector<int>& lep_pdgId = tx->getBranch<vector<int>>("lep_pdgId");
    const vector<LV>& lep_p4 = tx->getBranch<vector<LV>>("lep_p4");

    int pdgid0 = lep_pdgId[0];
    int pdgid1 = lep_pdgId[1];
    int pdgid2 = lep_pdgId[2];

    if (pdgid0 == pdgid1 && abs(pdgid0) == 11)
        return (lep_p4[0] + lep_p4[1]).mass();
    else if (pdgid0 == pdgid2 && abs(pdgid0) == 11)
        return (lep_p4[0] + lep_p4[2]).mass();
    else if (pdgid1 == pdgid2 && abs(pdgid1) == 11)
        return (lep_p4[1] + lep_p4[2]).mass();
    return -999;
}

//##############################################################################################################
float babyMaker_v2::get1SFOSMll()
{
    const vector<int>& lep_pdgId = tx->getBranch<vector<int>>("lep_pdgId");
    const vector<LV>& lep_p4 = tx->getBranch<vector<LV>>("lep_p4");

    int pdgid0 = lep_pdgId[0];
    int pdgid1 = lep_pdgId[1];
    int pdgid2 = lep_pdgId[2];

    if (pdgid0 == -pdgid1)
        return (lep_p4[0] + lep_p4[1]).mass();
    else if (pdgid0 == -pdgid2)
        return (lep_p4[0] + lep_p4[2]).mass();
    else if (pdgid1 == -pdgid2)
        return (lep_p4[1] + lep_p4[2]).mass();

    cout << "Warning: Shouldn't be here if function call are at the right places." << endl;

    return -999;
}

//##############################################################################################################
float babyMaker_v2::get2SFOSMll0()
{
    const vector<int>& lep_pdgId = tx->getBranch<vector<int>>("lep_pdgId");
    const vector<LV>& lep_p4 = tx->getBranch<vector<LV>>("lep_p4");

    int pdgid0 = lep_pdgId[0];
    int pdgid1 = lep_pdgId[1];
    int pdgid2 = lep_pdgId[2];

    if (pdgid0 == -pdgid1)
        return (lep_p4[0] + lep_p4[1]).mass();
    else if (pdgid0 == -pdgid2)
        return (lep_p4[0] + lep_p4[2]).mass();
    else if (pdgid1 == -pdgid2)
        return (lep_p4[1] + lep_p4[2]).mass();

    cout << "Warning: Shouldn't be here if function call are at the right places." << endl;

    return -999;
}

//##############################################################################################################
float babyMaker_v2::get2SFOSMll1()
{
    const vector<int>& lep_pdgId = tx->getBranch<vector<int>>("lep_pdgId");
    const vector<LV>& lep_p4 = tx->getBranch<vector<LV>>("lep_p4");

    int pdgid0 = lep_pdgId[0];
    int pdgid1 = lep_pdgId[1];
    int pdgid2 = lep_pdgId[2];

    if (pdgid2 == -pdgid1)
        return (lep_p4[1] + lep_p4[2]).mass();
    else if (pdgid0 == -pdgid2)
        return (lep_p4[0] + lep_p4[2]).mass();
    else if (pdgid1 == -pdgid0)
        return (lep_p4[0] + lep_p4[1]).mass();

    cout << "Warning: Shouldn't be here if function call are at the right places." << endl;

    return -999;
}

//##############################################################################################################
float babyMaker_v2::mT(LV p4, LV met)
{
    float phi1 = p4.Phi();
    float phi2 = met.Phi();
    float Et1  = p4.Et();
    float Et2  = met.Et();
    return sqrt(2*Et1*Et2*(1.0 - cos(phi1-phi2)));
}

//##############################################################################################################
// Returns true + indices of the SSID passing leptons that makes a SS pair.
tuple<bool, int, int> babyMaker_v2::isSSCR()
{
    // Assumes that the FillElectron/FillMuon is done
    // Retrieve some info we need from the lepton containers
    const vector<int>& lep_pdgId  = tx->getBranch<vector<int>>("lep_pdgId");
    const vector<int>& lep_charge = tx->getBranch<vector<int>>("lep_charge");
    const vector<int>& lep_tight  = tx->getBranch<vector<int>>("lep_pass_VVV_cutbased_tight");

    // Count the number of tight "SSID" leptons
    int ntight = passCount(lep_tight);

    // If there are no two "SSID" passing leptons then return false, and -1 indices
    if (ntight < 2)
    {
        return make_tuple(false, -1, -1);
    }
    else if (ntight >= 2)
    {
        // Determine whether I have two positive or two negative
        // Assumes abs charge == 1 ensured
        int totalcharge = lep_charge[0] + lep_charge[1] + lep_charge[2];

        // Save the indices here
        vector<int> lep_index;

        // Loop over leptons and pick the two indices that passes tight ID and are "same-sign"
        for (unsigned int i = 0; i < lep_pdgId.size(); ++i)
        {
            if (totalcharge == 1 ? lep_pdgId[i] < 0 && lep_tight[i] : lep_pdgId[i] > 0 && lep_tight[i])
                lep_index.push_back(i);
        }

        // If the lep_index does not have two leptons
        // this event did not pass the SSCR requirement from the 3L region
        if (lep_index.size() != 2)
            return make_tuple(false, -1, -1);
        else
            return make_tuple(true, lep_index[0], lep_index[1]);
    }
    else
    {
        cout << "FATAL ERROR: I Should never be here!" << endl;
        return make_tuple(false, -1, -1);
    }
}



//---------------==================-----------------==================-----------------=================----------
//---------------==================-----------------==================-----------------=================----------
//---------------==================-----------------==================-----------------=================----------
//---------------==================-----------------==================-----------------=================----------
//---------------==================-----------------==================-----------------=================----------




//
//
// Old version overlap removal settings and the lepton definition used to perform the overlap removal
// This is kept only for documentation purpose only
//
//


//##############################################################################################################
bool babyMaker_v2::isLeptonOverlappingWithJet_OldVersion(int ijet)
{
    bool is_overlapping = false;

    int idx = coreJet.index[ijet];
    float corr = coreJet.corrs[ijet];
    float pt = (cms3.pfjets_p4()[idx] * corr).pt();
    float eta = (cms3.pfjets_p4()[idx] * corr).eta();

    if (!(pt > JET_PT_MIN || (pt > BJET_PT_MIN && cms3.getbtagvalue("pfCombinedInclusiveSecondaryVertexV2BJetTags", idx) >= BJET_CSV_MED))) { return false; }
    if (fabs(eta) > JET_ETA_MAX) { return false; }
    if (!(isLoosePFJet_Summer16_v1(idx))) { return false; }

    for (auto& imu : coreMuon.index)
    {
        if (!(cms3.mus_p4()[imu].pt() > 20))
            continue;

        if (!(isVetoMuonNoIso_OldVersion(imu)))
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
        if (!(cms3.els_p4()[iel].pt() > 20))
            continue;

        if (!(isVetoElectronNoIso_OldVersion(iel)))
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
// Used to "pre"select leptons from CMS3
bool babyMaker_v2::isVetoMuonNoIso_OldVersion(int idx)
{
    if (!( cms3.mus_p4()[idx].pt()            > 10.    )) return false;
    if (!( isLooseMuonPOG(idx)                         )) return false;
    return true;
}

//##############################################################################################################
// Used to "pre"select leptons from CMS3
bool babyMaker_v2::isVetoElectronNoIso_OldVersion(int idx)
{
    if (!( cms3.els_p4()[idx].pt()            >  10.   )) return false;
    if (!(isVetoElectronPOGspring16noIso_v1(idx) || passElectronSelection_VVV(idx, VVV_MVAbased_tight_noiso))) return false;
    return true;
}


//eof
