#include "ScanChain_v2.h"
#include "../Loopers/LeptonAndTriggerSF.h"

using namespace std;

//##############################################################################################################
void babyMaker_v2::ScanChain_v2(TChain* chain, std::string baby_name, int max_events, int index, bool verbose)
{

    // Looper
    RooUtil::Looper<CMS3> looper(chain, &cms3, max_events);

    // Output root file
    CreateOutput(index);

    while (looper.nextEvent())
    {
        try
        {
            if (verbose)
                cout << "[verbose] Processed " << looper.getNEventsProcessed() << " out of " << chain->GetEntries() << endl;

            coreJec.setJECFor(looper.getCurrentFileName());

            setFilename(looper.getCurrentFileName());

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
            tx->clear(); // clear the TTree of any residual stuff
            if (!looper.handleBadEvent())
                break;
        }
    }

    looper.printStatus();

    SaveOutput();
//    t->SetDirectory(0);
}

//##############################################################################################################
void babyMaker_v2::CreateOutput(int index)
{
    ofile = new TFile(Form("output_%d.root", index), "recreate");
    t         = new TTree("t", "All events");
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

    tx->createBranch<int>("mc_HLT_DoubleMu");
    tx->createBranch<int>("mc_HLT_DoubleEl");
    tx->createBranch<int>("mc_HLT_DoubleEl_DZ");
    tx->createBranch<int>("mc_HLT_DoubleEl_DZ_2");
    tx->createBranch<int>("mc_HLT_MuEG");

    tx->createBranch<vector<LorentzVector>>("lep_p4");
    tx->createBranch<vector<float>>("lep_pt");
    tx->createBranch<vector<float>>("lep_eta");
    tx->createBranch<vector<float>>("lep_phi");
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
    tx->createBranch<vector<float>>("lep_ptRatioEA");
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
    tx->createBranch<vector<float>>("lep_jetpt_v0");
    tx->createBranch<vector<float>>("lep_jetpt_v1");
    tx->createBranch<vector<float>>("lep_jetpt_v2");

    tx->createBranch<vector<LorentzVector>>("jets_p4");
    tx->createBranch<vector<LorentzVector>>("jets_up_p4");
    tx->createBranch<vector<LorentzVector>>("jets_dn_p4");
    tx->createBranch<vector<float>>("jets_csv");
    tx->createBranch<vector<float>>("jets_up_csv");
    tx->createBranch<vector<float>>("jets_dn_csv");

    tx->createBranch<float>("met_pt");
    tx->createBranch<float>("met_phi");
    tx->createBranch<float>("met_up_pt");
    tx->createBranch<float>("met_up_phi");
    tx->createBranch<float>("met_dn_pt");
    tx->createBranch<float>("met_dn_phi");

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

    tx->createBranch<int>("Flag_AllEventFilters");
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

    tx->createBranch<int>("nb");
    tx->createBranch<int>("nb_up");
    tx->createBranch<int>("nb_dn");

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
    tx->createBranch<float>("MTmin");
    tx->createBranch<float>("MTmin_up");
    tx->createBranch<float>("MTmin_dn");

    tx->createBranch<float>("MT3rd");
    tx->createBranch<float>("MT3rd_up");
    tx->createBranch<float>("MT3rd_dn");

    tx->createBranch<int>("passSSee");
    tx->createBranch<int>("passSSem");
    tx->createBranch<int>("passSSmm");

    tx->createBranch<int>("lep_idx0_SS");
    tx->createBranch<int>("lep_idx1_SS");

    tx->createBranch<TString>("bkgtype");
    tx->createBranch<int>("vetophoton");

    tx->createBranch<float>("purewgt");
    tx->createBranch<float>("purewgt_up");
    tx->createBranch<float>("purewgt_dn");

    tx->createBranch<float>("ffwgt");
    tx->createBranch<float>("ffwgt_up");
    tx->createBranch<float>("ffwgt_dn");

    tx->createBranch<float>("ffwgtqcd");
    tx->createBranch<float>("ffwgtqcd_up");
    tx->createBranch<float>("ffwgtqcd_dn");

    tx->createBranch<float>("lepsf");
    tx->createBranch<float>("lepsf_up");
    tx->createBranch<float>("lepsf_dn");

    tx->createBranch<float>("trigeff");
    tx->createBranch<float>("trigeff_up");
    tx->createBranch<float>("trigeff_dn");

    tx->clear();
}


//##############################################################################################################
void babyMaker_v2::SaveOutput()
{
    ofile->cd();

    t_www     = t->CopyTree("(bkgtype==\"WWW\")||(bkgtype==\"WHtoWWW\")");
    t_qflip   = t->CopyTree("(bkgtype==\"chargeflips\")");
    t_photon  = t->CopyTree("(bkgtype==\"photonfakes\")");
    t_fakes   = t->CopyTree("(bkgtype==\"fakes\")");
    if (filename.find("wz_") == 0) // to check whether it is a WZ sample
    {
        // This is so that the majority of WZ events go to "lostlep" category
        // This way the histogram can share the same color across SS and 3L to more or less indicate "WZ" bkg
        t_prompt  = t->CopyTree("(nVlep==2&&bkgtype==\"trueSS\")||(nVlep>=3&&bkgtype==\"trueWWW\")");
        t_lostlep = t->CopyTree("(nVlep==2&&bkgtype==\"SSLL\")||(nVlep>=3&&(bkgtype==\"3lLL\"||bkgtype==\"true3L\"))");
    }
    else
    {
        t_prompt  = t->CopyTree("(nVlep==2&&bkgtype==\"trueSS\")||(nVlep>=3&&(bkgtype==\"true3L\"||bkgtype==\"trueWWW\"))");
        t_lostlep = t->CopyTree("(nVlep==2&&bkgtype==\"SSLL\")||(nVlep>=3&&bkgtype==\"3lLL\")");
    }

    t_www->SetName("t_www");
    t_qflip->SetName("t_qflip");
    t_photon->SetName("t_photon");
    t_fakes->SetName("t_fakes");
    t_prompt->SetName("t_prompt");
    t_lostlep->SetName("t_lostlep");

    t_www->SetTitle("Signal Events");
    t_qflip->SetTitle("Charge Flip Events");
    t_photon->SetTitle("Prompt Photon Events");
    t_fakes->SetTitle("Fake Lepton Events");
    t_prompt->SetTitle("Prompt Lepton Events");
    t_lostlep->SetTitle("Lost Lepton Events or WZ in 3-lepton categories");

    t->Write();
    t_www->Write();
    t_qflip->Write();
    t_photon->Write();
    t_fakes->Write();
    t_prompt->Write();
    t_lostlep->Write();
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
            if (cms3.els_p4()[iel].pt() > 20. && passElectronSelection_VVV(iel, VVV_FO_3L))
            {
                nloose++;
                chargesum += cms3.els_charge()[iel];
            }
        }
        for (auto& imu : coreMuon.index)
        {
            if (cms3.mus_p4()[imu].pt() > 20. && passMuonSelection_VVV(imu, VVV_FO_3L))
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
        if (cms3.els_p4()[iel].pt() > 25. && passElectronSelection_VVV(iel, VVV_FO_SS))
            nloose++;
    }
    for (auto& imu : coreMuon.index)
    {
        if (cms3.mus_p4()[imu].pt() > 25. && passMuonSelection_VVV(imu, VVV_FO_SS))
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

    // Fill MET filter info
    FillMETFilter();

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
        float scale1fb = coreDatasetInfo.getScale1fb();
        if (filename.find("www_2l_mia")      != string::npos) scale1fb *= 0.066805 * 91900.  / (91900. + 164800.);
        if (filename.find("www_2l_ext1_mia") != string::npos) scale1fb *= 0.066805 * 164800. / (91900. + 164800.);
        tx->setBranch<float>("evt_scale1fb", scale1fb);
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
        const LorentzVector& temp_jet_p4_v0 = closestJet(cms3.els_p4()[idx], 0.4, 3.0, /*whichCorr = */0);
        const LorentzVector& temp_jet_p4_v1 = closestJet(cms3.els_p4()[idx], 0.4, 3.0, /*whichCorr = */1);
        int jetidx = closestJetIdx(cms3.els_p4()[idx], 0.4, 3.0);
        float area = jetidx >= 0 ? cms3.pfjets_area()[jetidx] : 0;
        float closeJetPt = temp_jet_p4.pt();
        float ptratio = (closeJetPt > 0. ? cms3.els_p4()[idx].pt() / closeJetPt : 1.);
        float ptratioEA = (temp_jet_p4_v0.pt() > 0. ? cms3.els_p4()[idx].pt() / (temp_jet_p4_v0.pt() - (elEA03(idx, 2) * cms3.evt_fixgridfastjet_all_rho() * (cms3.pfjets_area()[jetidx] / 0.3 * 0.3 * TMath::Pi()))) : 1.);
        float conecorrptfactorraw = coreElectron.index.size() + coreMuon.index.size() > 2 ?  0.84 / ptratio : 0.9 / ptratio;
        float conecorrptfactor = max(0., conecorrptfactorraw - 1.) + 1.; // To clip correcting once it passes tight isolation criteria

        if (coreElectron.index.size() + coreMuon.index.size() == 2)
        {
            if (!( passElectronSelection_VVV(idx, VVV_FO_SS) ))
                continue;
        }
        else if (coreElectron.index.size() + coreMuon.index.size() > 2)
        {
            if (!( passElectronSelection_VVV(idx, VVV_FO_3L) ))
                continue;
        }

        tx->pushbackToBranch<LorentzVector> ("lep_p4"                           , cms3.els_p4()[idx]);
        tx->pushbackToBranch<float>         ("lep_pt"                           , cms3.els_p4()[idx].pt());
        tx->pushbackToBranch<float>         ("lep_eta"                          , cms3.els_p4()[idx].eta());
        tx->pushbackToBranch<float>         ("lep_phi"                          , cms3.els_p4()[idx].phi());
        tx->pushbackToBranch<float>         ("lep_coneCorrPt"                   , cms3.els_p4()[idx].pt() * conecorrptfactor);
        tx->pushbackToBranch<float>         ("lep_ip3d"                         , cms3.els_ip3d()[idx]);
        tx->pushbackToBranch<float>         ("lep_ip3derr"                      , cms3.els_ip3derr()[idx]);
        tx->pushbackToBranch<int>           ("lep_isTriggerSafe_v1"             , isTriggerSafe_v1(idx));
        tx->pushbackToBranch<int>           ("lep_lostHits"                     , cms3.els_lostHits()[idx]);
        tx->pushbackToBranch<int>           ("lep_convVeto"                     , !cms3.els_conv_vtx_flag()[idx]);
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_3l_fo"      , cms3.els_p4()[idx].pt() > 20. && passElectronSelection_VVV(idx, VVV_FO_3L));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_3l_tight"   , cms3.els_p4()[idx].pt() > 20. && passElectronSelection_VVV(idx, VVV_TIGHT_3L));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_fo"         , cms3.els_p4()[idx].pt() > 25. && passElectronSelection_VVV(idx, VVV_FO_SS));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_tight"      , cms3.els_p4()[idx].pt() > 25. && passElectronSelection_VVV(idx, VVV_TIGHT_SS));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_veto"       , cms3.els_p4()[idx].pt() > 10. && passElectronSelection_VVV(idx, VVV_VETO));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_fo_noiso"   , cms3.els_p4()[idx].pt() > 25. && passElectronSelection_VVV(idx, VVV_FO_NOISO));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_tight_noiso", cms3.els_p4()[idx].pt() > 25. && passElectronSelection_VVV(idx, VVV_TIGHT_NOISO));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_veto_noiso" , cms3.els_p4()[idx].pt() > 10. && passElectronSelection_VVV(idx, VVV_VETO_NOISO));
        tx->pushbackToBranch<int>           ("lep_pdgId"                        , cms3.els_charge()[idx]*(-11));
        tx->pushbackToBranch<float>         ("lep_dxy"                          , cms3.els_dxyPV()[idx]);
        tx->pushbackToBranch<float>         ("lep_dz"                           , cms3.els_dzPV()[idx]);
        tx->pushbackToBranch<float>         ("lep_ptRatio"                      , ptratio);
        tx->pushbackToBranch<float>         ("lep_ptRatioEA"                    , ptratioEA);
        tx->pushbackToBranch<float>         ("lep_ptRel"                        , ptRel(cms3.els_p4()[idx], temp_jet_p4, true));
        tx->pushbackToBranch<float>         ("lep_pterr"                        , cms3.els_ptErr()[idx]);
        tx->pushbackToBranch<float>         ("lep_relIso03EAv2"                 , eleRelIso03EA(idx, 2));
        tx->pushbackToBranch<int>           ("lep_tightCharge"                  , tightChargeEle(idx));
        tx->pushbackToBranch<float>         ("lep_trk_pt"                       , cms3.els_trk_p4()[idx].pt());
        tx->pushbackToBranch<int>           ("lep_charge"                       , cms3.els_charge()[idx]);
        tx->pushbackToBranch<float>         ("lep_etaSC"                        , cms3.els_etaSC()[idx]);
        tx->pushbackToBranch<float>         ("lep_MVA"                          , getMVAoutput(idx));
        tx->pushbackToBranch<float>         ("lep_jetpt_v0"                     , temp_jet_p4_v0.pt());
        tx->pushbackToBranch<float>         ("lep_jetpt_v1"                     , temp_jet_p4_v1.pt());
        tx->pushbackToBranch<float>         ("lep_jetpt_v2"                     , temp_jet_p4.pt());
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
        const LorentzVector& temp_jet_p4_v0 = closestJet(cms3.mus_p4()[idx], 0.4, 3.0, /*whichCorr = */0);
        const LorentzVector& temp_jet_p4_v1 = closestJet(cms3.mus_p4()[idx], 0.4, 3.0, /*whichCorr = */1);
        int jetidx = closestJetIdx(cms3.mus_p4()[idx], 0.4, 3.0);
        float area = jetidx >= 0 ? cms3.pfjets_area()[jetidx] : 0;
        float closeJetPt = temp_jet_p4.pt();
        float ptratio = (closeJetPt > 0. ? cms3.mus_p4()[idx].pt() / closeJetPt : 1.);
        float ptratioEA = (temp_jet_p4_v0.pt() > 0. ?  cms3.mus_p4()[idx].pt() / (temp_jet_p4_v0.pt() - (muEA03(idx, 2) * cms3.evt_fixgridfastjet_all_rho() * (cms3.pfjets_area()[jetidx] / 0.3 * 0.3 * TMath::Pi()))) : 1.);
        float conecorrptfactorraw = coreElectron.index.size() + coreMuon.index.size() > 2 ?  0.84 / ptratio : 0.9 / ptratio;
        float conecorrptfactor = max(0., conecorrptfactorraw - 1.) + 1.; // To clip correcting once it passes tight isolation criteria

        if (coreMuon.index.size() + coreMuon.index.size() == 2)
        {
            if (!( passMuonSelection_VVV(idx, VVV_FO_SS) ))
                continue;
        }
        else if (coreMuon.index.size() + coreMuon.index.size() > 2)
        {
            if (!( passMuonSelection_VVV(idx, VVV_FO_3L) ))
                continue;
        }

        tx->pushbackToBranch<LorentzVector> ("lep_p4"                           , cms3.mus_p4()[idx]);
        tx->pushbackToBranch<float>         ("lep_pt"                           , cms3.mus_p4()[idx].pt());
        tx->pushbackToBranch<float>         ("lep_eta"                          , cms3.mus_p4()[idx].eta());
        tx->pushbackToBranch<float>         ("lep_phi"                          , cms3.mus_p4()[idx].phi());
        tx->pushbackToBranch<float>         ("lep_coneCorrPt"                   , cms3.mus_p4()[idx].pt() * conecorrptfactor);
        tx->pushbackToBranch<float>         ("lep_ip3d"                         , cms3.mus_ip3d()[idx]);
        tx->pushbackToBranch<float>         ("lep_ip3derr"                      , cms3.mus_ip3derr()[idx]);
        tx->pushbackToBranch<int>           ("lep_isTriggerSafe_v1"             , true); // Electron specific branch. So muons always pass.
        tx->pushbackToBranch<int>           ("lep_lostHits"                     , cms3.mus_lostHits()[idx]);
        tx->pushbackToBranch<int>           ("lep_convVeto"                     , 1);
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_3l_fo"      , cms3.mus_p4()[idx].pt() > 20. && passMuonSelection_VVV(idx, VVV_FO_3L));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_3l_tight"   , cms3.mus_p4()[idx].pt() > 20. && passMuonSelection_VVV(idx, VVV_TIGHT_3L));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_fo"         , cms3.mus_p4()[idx].pt() > 25. && passMuonSelection_VVV(idx, VVV_FO_SS));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_tight"      , cms3.mus_p4()[idx].pt() > 25. && passMuonSelection_VVV(idx, VVV_TIGHT_SS));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_veto"       , cms3.mus_p4()[idx].pt() > 10. && passMuonSelection_VVV(idx, VVV_VETO));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_fo_noiso"   , cms3.mus_p4()[idx].pt() > 25. && passMuonSelection_VVV(idx, VVV_FO_NOISO));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_tight_noiso", cms3.mus_p4()[idx].pt() > 25. && passMuonSelection_VVV(idx, VVV_TIGHT_NOISO));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_veto_noiso" , cms3.mus_p4()[idx].pt() > 10. && passMuonSelection_VVV(idx, VVV_VETO_NOISO));
        tx->pushbackToBranch<int>           ("lep_pdgId"                        , cms3.mus_charge()[idx]*(-13));
        tx->pushbackToBranch<float>         ("lep_dxy"                          , cms3.mus_dxyPV()[idx]);
        tx->pushbackToBranch<float>         ("lep_dz"                           , cms3.mus_dzPV()[idx]);
        tx->pushbackToBranch<float>         ("lep_ptRatio"                      , ptratio);
        tx->pushbackToBranch<float>         ("lep_ptRatioEA"                    , ptratioEA);
        tx->pushbackToBranch<float>         ("lep_ptRel"                        , ptRel(cms3.mus_p4()[idx], temp_jet_p4, true));
        tx->pushbackToBranch<float>         ("lep_pterr"                        , cms3.mus_ptErr()[idx]);
        tx->pushbackToBranch<float>         ("lep_relIso03EAv2"                 , muRelIso03EA(idx, 2));
        tx->pushbackToBranch<int>           ("lep_tightCharge"                  , tightChargeMuon(idx));
        tx->pushbackToBranch<float>         ("lep_trk_pt"                       , cms3.mus_trk_p4()[idx].pt());
        tx->pushbackToBranch<int>           ("lep_charge"                       , cms3.mus_charge()[idx]);
        tx->pushbackToBranch<float>         ("lep_etaSC"                        , cms3.mus_p4()[idx].eta()); // Electron specific branch. Just take muon's regular eta.
        tx->pushbackToBranch<float>         ("lep_MVA"                          , -99);
        tx->pushbackToBranch<float>         ("lep_jetpt_v0"                     , temp_jet_p4_v0.pt());
        tx->pushbackToBranch<float>         ("lep_jetpt_v1"                     , temp_jet_p4_v1.pt());
        tx->pushbackToBranch<float>         ("lep_jetpt_v2"                     , temp_jet_p4.pt());
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
            "lep_pt",
            "lep_eta",
            "lep_phi",
            "lep_dxy",
            "lep_dz",
            "lep_ip3d",
            "lep_ip3derr",
            "lep_ptRatio",
            "lep_ptRatioEA",
            "lep_ptRel",
            "lep_pterr",
            "lep_relIso03EAv2",
            "lep_relIso04EAv2",
            "lep_trk_pt",
            "lep_etaSC",
            "lep_MVA",
            "lep_coneCorrPt",
            "lep_jetpt_v0",
            "lep_jetpt_v1",
            "lep_jetpt_v2",
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
    else
    {
        tx->setBranch<float>("weight_btagsf"         , 1);
        tx->setBranch<float>("weight_btagsf_heavy_DN", 1);
        tx->setBranch<float>("weight_btagsf_heavy_UP", 1);
        tx->setBranch<float>("weight_btagsf_light_DN", 1);
        tx->setBranch<float>("weight_btagsf_light_UP", 1);
    }
}

//##############################################################################################################
void babyMaker_v2::FillMET()
{
    tx->setBranch<float>("met_pt", coreMET.met_pt);
    tx->setBranch<float>("met_phi", coreMET.met_phi);
    tx->setBranch<float>("met_up_pt", coreMET.met_up_pt);
    tx->setBranch<float>("met_up_phi", coreMET.met_up_phi);
    tx->setBranch<float>("met_dn_pt", coreMET.met_dn_pt);
    tx->setBranch<float>("met_dn_phi", coreMET.met_dn_phi);
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
    if (cms3.evt_isRealData())
    {
        tx->setBranch<int>("HLT_DoubleMu", coreTrigger.HLT_DoubleMu);
        tx->setBranch<int>("HLT_DoubleEl", coreTrigger.HLT_DoubleEl);
        tx->setBranch<int>("HLT_DoubleEl_DZ", coreTrigger.HLT_DoubleEl_DZ);
        tx->setBranch<int>("HLT_DoubleEl_DZ_2", coreTrigger.HLT_DoubleEl_DZ_2);
        tx->setBranch<int>("HLT_MuEG", coreTrigger.HLT_MuEG);
    }
    else
    {
        tx->setBranch<int>("HLT_DoubleMu", 1);
        tx->setBranch<int>("HLT_DoubleEl", 1);
        tx->setBranch<int>("HLT_DoubleEl_DZ", 1);
        tx->setBranch<int>("HLT_DoubleEl_DZ_2", 1);
        tx->setBranch<int>("HLT_MuEG", 1);
    }
    tx->setBranch<int>("mc_HLT_DoubleMu", coreTrigger.HLT_DoubleMu);
    tx->setBranch<int>("mc_HLT_DoubleEl", coreTrigger.HLT_DoubleEl);
    tx->setBranch<int>("mc_HLT_DoubleEl_DZ", coreTrigger.HLT_DoubleEl_DZ);
    tx->setBranch<int>("mc_HLT_DoubleEl_DZ_2", coreTrigger.HLT_DoubleEl_DZ_2);
    tx->setBranch<int>("mc_HLT_MuEG", coreTrigger.HLT_MuEG);
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

    // Pass all event filters if it is a data event or just pass it if it is an MC
    tx->setBranch<int>("Flag_AllEventFilters",
            (
                cms3.evt_isRealData() &&
                tx->getBranch<int>("Flag_EcalDeadCellTriggerPrimitiveFilter") &&
                tx->getBranch<int>("Flag_HBHEIsoNoiseFilter") &&
                tx->getBranch<int>("Flag_HBHENoiseFilter") &&
                tx->getBranch<int>("Flag_badChargedCandidateFilter") &&
                tx->getBranch<int>("Flag_badMuonFilter") &&
                tx->getBranch<int>("Flag_eeBadScFilter") &&
                tx->getBranch<int>("Flag_globalTightHalo2016") &&
                tx->getBranch<int>("Flag_goodVertices")
            )
            ||
            (
                !cms3.evt_isRealData()
            )
        );
}

//##############################################################################################################
void babyMaker_v2::FillSummaryVariables()
{
    FillJetVariables(0);
    FillJetVariables(1);
    FillJetVariables(-1);
    FillLeptonVariables();
    FillEventTags();
    FillWeights();
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
    if (!( passMuonSelection_VVV(idx, VVV_FO_3L) )) return false;
    return true;
}

//##############################################################################################################
// Used to overlap remova against jets
bool babyMaker_v2::isLooseElectron(int idx)
{
    if (!( cms3.els_p4()[idx].pt() > 20.                         )) return false;
    if (!( passElectronSelection_VVV(idx, VVV_FO_3L) )) return false;
    return true;
}

//##############################################################################################################
// Used to overlap remova against tracks
bool babyMaker_v2::isVetoMuon(int idx)
{
    if (!( passMuonSelection_VVV(idx, VVV_VETO) )) return false;
    return true;
}

//##############################################################################################################
// Used to overlap remova against tracks
bool babyMaker_v2::isVetoElectron(int idx)
{
    if (!( passElectronSelection_VVV(idx, VVV_VETO) )) return false;
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

            if (!( p4_2.pt() > 30. ))
                continue;

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

    // Fill the same-sign pairs lep id tag
    tx->setBranch<int>("passSSee", (lep_pdgId[idx0] * lep_pdgId[idx1]) == 121);
    tx->setBranch<int>("passSSem", (lep_pdgId[idx0] * lep_pdgId[idx1]) == 143);
    tx->setBranch<int>("passSSmm", (lep_pdgId[idx0] * lep_pdgId[idx1]) == 169);

    // Save the lepton index for later purpose
    tx->setBranch<int>("lep_idx0_SS", idx0);
    tx->setBranch<int>("lep_idx1_SS", idx1);

    tx->setBranch<float>("MllSS", (lep_p4[idx0] + lep_p4[idx1]).mass());
    if (abs(lep_pdgId[idx0]) == 11 && abs(lep_pdgId[idx1]) == 11)
        tx->setBranch<float>("MeeSS", (lep_p4[idx0] + lep_p4[idx1]).mass());

    // Set up MET variables
    const float& met_pt = tx->getBranch<float>("met_pt");
    const float& met_phi = tx->getBranch<float>("met_phi");
    const float& met_up_pt = tx->getBranch<float>("met_up_pt");
    const float& met_up_phi = tx->getBranch<float>("met_up_phi");
    const float& met_dn_pt = tx->getBranch<float>("met_dn_pt");
    const float& met_dn_phi = tx->getBranch<float>("met_dn_phi");
    LV MET;
    LV MET_up;
    LV MET_dn;
    MET.SetPxPyPzE(met_pt * TMath::Cos(met_phi), met_pt * TMath::Sin(met_phi), 0, met_pt);
    MET_up.SetPxPyPzE(met_up_pt * TMath::Cos(met_up_phi), met_up_pt * TMath::Sin(met_up_phi), 0, met_up_pt);
    MET_dn.SetPxPyPzE(met_dn_pt * TMath::Cos(met_dn_phi), met_dn_pt * TMath::Sin(met_dn_phi), 0, met_dn_pt);

    float MT0    = mT(lep_p4[idx0], MET);
    float MT1    = mT(lep_p4[idx1], MET);
    float MT0_up = mT(lep_p4[idx0], MET_up);
    float MT1_up = mT(lep_p4[idx1], MET_up);
    float MT0_dn = mT(lep_p4[idx0], MET_dn);
    float MT1_dn = mT(lep_p4[idx1], MET_dn);

    tx->setBranch<float>("MTmax", MT0 > MT1 ? MT0 : MT1);
    tx->setBranch<float>("MTmax_up", MT0_up > MT1_up ? MT0_up : MT1_up);
    tx->setBranch<float>("MTmax_dn", MT0_dn > MT1_dn ? MT0_dn : MT1_dn);
    tx->setBranch<float>("MTmin", MT0 < MT1 ? MT0 : MT1);
    tx->setBranch<float>("MTmin_up", MT0_up < MT1_up ? MT0_up : MT1_up);
    tx->setBranch<float>("MTmin_dn", MT0_dn < MT1_dn ? MT0_dn : MT1_dn);
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
        if (fabs(tx->getBranch<float>("Mll3L") - 91.1876) < 20.)
            nSFOSinZ = 1;
    }
    else if (nSFOS == 2)
    {
        tx->setBranch<float>("Mll3L", get2SFOSMll0());
        tx->setBranch<float>("Mll3L1", get2SFOSMll1());
        if (fabs(tx->getBranch<float>("Mll3L") - 91.1876) < 20.)
            nSFOSinZ++;
        if (fabs(tx->getBranch<float>("Mll3L1") - 91.1876) < 20.)
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
    const float& met_up_pt = tx->getBranch<float>("met_up_pt");
    const float& met_up_phi = tx->getBranch<float>("met_up_phi");
    const float& met_dn_pt = tx->getBranch<float>("met_dn_pt");
    const float& met_dn_phi = tx->getBranch<float>("met_dn_phi");
    LV MET;
    LV MET_up;
    LV MET_dn;
    MET.SetPxPyPzE( met_pt * TMath::Cos(met_phi), met_pt * TMath::Sin(met_phi), 0, met_pt);
    MET_up.SetPxPyPzE( met_up_pt * TMath::Cos(met_up_phi), met_up_pt * TMath::Sin(met_up_phi), 0, met_up_pt);
    MET_dn.SetPxPyPzE( met_dn_pt * TMath::Cos(met_dn_phi), met_dn_pt * TMath::Sin(met_dn_phi), 0, met_dn_pt);

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
void babyMaker_v2::FillEventTags()
{
    tx->setBranch<TString>("bkgtype", process());
    tx->setBranch<int>("vetophoton", vetophotonprocess());
}

//##############################################################################################################
void babyMaker_v2::FillWeights()
{
    if (cms3.evt_isRealData())
    {
        tx->setBranch<float>("purewgt", 1);
        tx->setBranch<float>("purewgt_up", 1);
        tx->setBranch<float>("purewgt_dn", 1);
    }
    else
    {
        int nTrueInt = cms3.puInfo_trueNumInteractions().at(0);
        tx->setBranch<float>("purewgt", puWeight(nTrueInt));
        tx->setBranch<float>("purewgt_up", puWeight(nTrueInt, 1));
        tx->setBranch<float>("purewgt_dn", puWeight(nTrueInt, -1));
    }

    // fakerate
    float ffwgt;
    float ffwgterr;
    float ffwgtqcd;
    float ffwgtqcderr;
    std::tie(ffwgt, ffwgterr) = getlepFakeRateandError(true);
    std::tie(ffwgtqcd, ffwgtqcderr) = getlepFakeRateandError(false);
    tx->setBranch<float>("ffwgt", ffwgt);
    tx->setBranch<float>("ffwgt_up", ffwgt + ffwgterr);
    tx->setBranch<float>("ffwgt_dn", ffwgt - ffwgterr);
    tx->setBranch<float>("ffwgtqcd", ffwgtqcd);
    tx->setBranch<float>("ffwgtqcd_up", ffwgtqcd + ffwgtqcderr);
    tx->setBranch<float>("ffwgtqcd_dn", ffwgtqcd - ffwgtqcderr);

    // lepsf
    if (!cms3.evt_isRealData())
    {
        float lepsf;
        float lepsferr;
        std::tie(lepsf, lepsferr) = getlepSFWeightandError();
        tx->setBranch<float>("lepsf", lepsf);
        tx->setBranch<float>("lepsf_up", lepsf + lepsferr);
        tx->setBranch<float>("lepsf_dn", lepsf - lepsferr);
    }
    else
    {
        tx->setBranch<float>("lepsf", 1);
        tx->setBranch<float>("lepsf_up", 1);
        tx->setBranch<float>("lepsf_dn", 1);
    }

    // trigger eff
    if (!cms3.evt_isRealData())
    {
        float trigeff;
        float trigefferr;
        std::tie(trigeff, trigefferr) = getTrigEffandError();
        tx->setBranch<float>("trigeff", trigeff);
        tx->setBranch<float>("trigeff_up", trigeff + trigefferr);
        tx->setBranch<float>("trigeff_dn", trigeff - trigefferr);
    }
    else
    {
        tx->setBranch<float>("trigeff", 1);
        tx->setBranch<float>("trigeff_up", 1);
        tx->setBranch<float>("trigeff_dn", 1);
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

//##############################################################################################################
TString babyMaker_v2::process()
{
    if (cms3.evt_isRealData())                             return "Data";
    if (splitVH())                                         return "WHtoWWW";
    if (filename.find("www_2l_")          != string::npos) return "WWW";
    if (filename.find("www_incl_amcnlo_") != string::npos) return "WWWv2";
    if (filename.find("data_")            != string::npos) return "Data";
    if (tx->getBranch<int>("nVlep") == 2 && tx->getBranch<int>("nLlep") == 2)
    {
        if (tx->getBranch<int>("nLlep") < 2) return "not2l";
        int gentype = gentype_v2();
        if      (gentype == 0) return "trueSS";
        else if (gentype == 2) return "chargeflips";
        else if (gentype == 3) return "SSLL";
        else if (gentype == 4) return "fakes";
        else if (gentype == 5) return "photonfakes";
        else                   return "others";
    }
    //this is 3l
    if (tx->getBranch<int>("nLlep") < 3) return "not3l";
    int gentype = gentype_v2();
    if      (gentype == 0) return "trueWWW";
    else if (gentype == 1) return "true3L";
    else if (gentype == 2) return "chargeflips";
    else if (gentype == 3) return "3lLL";
    else if (gentype == 4) return "fakes";
    else if (gentype == 5) return "photonfakes";
    else                   return "others";
}

//##############################################################################################################
bool babyMaker_v2::splitVH()
{
    if (filename.find("vh_nonbb_amcnlo") == string::npos) return false; //file is certainly no WHtoWWW
    bool isHtoWW = false;
    bool isWnotFromH = false;
    for (unsigned int i = 0; i < tx->getBranch<vector<int>>("genPart_pdgId").size(); ++i)
    {
        if (abs(tx->getBranch<vector<int>>("genPart_pdgId")[i]) != 24) continue;
        if (tx->getBranch<vector<int>>("genPart_status")[i] != 22) continue;
        if (abs(tx->getBranch<vector<int>>("genPart_motherId")[i]) == 25)  isHtoWW     = true;
        if (abs(tx->getBranch<vector<int>>("genPart_motherId")[i]) != 2)   isWnotFromH = true;
        if (isHtoWW && isWnotFromH) break;
    }
    return isHtoWW && isWnotFromH;
}

//##############################################################################################################
int babyMaker_v2::gentype_v2()
{
    bool gammafake = false;
    bool jetfake   = false;
    unsigned int ngenlep = tx->getBranch<int>("ngenLepFromTau") + tx->getBranch<int>("ngenLep");
    unsigned int nW(0), nZ(0);
    bool lep1_real = tx->getBranch<vector<int>>("lep_motherIdSS")[0] > 0;
    bool lep2_real = tx->getBranch<vector<int>>("lep_motherIdSS")[1] > 0;
    bool lep3_real = false;
    if (tx->getBranch<int>("nLlep") >= 3) lep3_real = tx->getBranch<vector<int>>("lep_motherIdSS")[2] > 0;
    vector<int> reallepindex;
    for (unsigned int lepindex = 0; lepindex < tx->getBranch<vector<LV>>("lep_p4").size(); ++lepindex)
    {
        if (tx->getBranch<vector<int>>("lep_motherIdSS")[lepindex] > 0)
            reallepindex.push_back(lepindex);
        else if (tx->getBranch<vector<int>>("lep_motherIdSS")[lepindex] == -3)
            gammafake = true;
        else
            jetfake = true;
        if (tx->getBranch<vector<int>>("lep_isFromW")[lepindex]) nW++;
        if (tx->getBranch<vector<int>>("lep_isFromZ")[lepindex]) nZ++;
    }
    //found two real leptons
    if (tx->getBranch<int>("nLlep") == 2)
    {
        bool ischargeflip = false;
        bool isSS = false;
        if (lep1_real && lep2_real)
        {
            int ilep1 = tx->getBranch<vector<int>>("lep_genPart_index").at(0);
            int ilep2 = tx->getBranch<vector<int>>("lep_genPart_index").at(1);
            bool lep1_chargeflip  = tx->getBranch<vector<int>>("genPart_charge").at(ilep1) != tx->getBranch<vector<int>>("lep_charge").at(0);
            bool lep2_chargeflip  = tx->getBranch<vector<int>>("genPart_charge").at(ilep2) != tx->getBranch<vector<int>>("lep_charge").at(1);
            if (!lep1_chargeflip && !lep2_chargeflip && nW == 2) return 0; // true SS
            else if (!lep1_chargeflip && !lep2_chargeflip)        isSS = true; // true SS - but could be still lost lepton WZ
            if (lep1_chargeflip || lep2_chargeflip)        ischargeflip = true;      // charge flip
        }
        if (ngenlep > 2 || reallepindex.size() > 2 || (nW > 0 && nZ > 0)) return 3; // lostlep
        if ((ngenlep < 2 || !lep1_real || !lep2_real) &&       jetfake) return 4; // jetfake - if double fake with one jet fake and one gamma fake call it jet fake
        if ((ngenlep < 2 || !lep1_real || !lep2_real) &&     gammafake) return 5; // gammafake
        if ((ngenlep < 2 || !lep1_real || !lep2_real) &&    !gammafake) return 4; // call all without gamma fake jetfake - safety cut
        if (isSS)         return 0;
        if (ischargeflip) return 2;
        cout << "This event was not classified - 2 lepton event - v2" << endl;
        return 1;
    }
    else
    {
        //found three real leptons
        bool ischargeflip = false;
        bool isthreelep = false;
        if (lep1_real && lep2_real && lep3_real)
        {
            int ilep1 = tx->getBranch<vector<int>>("lep_genPart_index").at(0);
            int ilep2 = tx->getBranch<vector<int>>("lep_genPart_index").at(1);
            int ilep3 = tx->getBranch<vector<int>>("lep_genPart_index").at(2);
            bool lep1_chargeflip  = tx->getBranch<vector<int>>("genPart_charge").at(ilep1) != tx->getBranch<vector<int>>("lep_charge").at(0);
            bool lep2_chargeflip  = tx->getBranch<vector<int>>("genPart_charge").at(ilep2) != tx->getBranch<vector<int>>("lep_charge").at(1);
            bool lep3_chargeflip  = tx->getBranch<vector<int>>("genPart_charge").at(ilep3) != tx->getBranch<vector<int>>("lep_charge").at(2);
            if (!lep1_chargeflip && !lep2_chargeflip && !lep3_chargeflip && nW == 3) return 0; // true WWW
            else if (!lep1_chargeflip && !lep2_chargeflip && !lep3_chargeflip)        isthreelep = true; // true 3l, but could be lost lepton ZZ
            if (lep1_chargeflip || lep2_chargeflip || lep3_chargeflip)        ischargeflip = true;     // charge flip
        }
        if (ngenlep > 3 || reallepindex.size() > 3 || (nW >= 2 && nZ >= 1) || (nZ >= 3)) return 3; // lostlep (2 lep from W and 2 from Z, or 4 from Z)
        //there is the case of having WZZ with two lost leptons --> ngenlep>3 - correctly put has lostlep
        if ((ngenlep < 3 || !lep1_real || !lep2_real || !lep3_real) &&        jetfake) return 4; // jetfake
        if ((ngenlep < 3 || !lep1_real || !lep2_real || !lep3_real) &&      gammafake) return 5; // gammafake
        if ((ngenlep < 3 || !lep1_real || !lep2_real || !lep3_real) &&     !gammafake) return 4; // jetfake
        if (isthreelep)   return 1;
        if (ischargeflip) return 2;
        cout << "This event was not classified - 3 lepton event - v2" << endl;
        return 0;
    }
}

//##############################################################################################################
void babyMaker_v2::setFilename(TString fname)
{
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "dy_m1050_mgmlm";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/"))
         filename = "dy_m50_mgmlm_ht100_ext1";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/DYJetsToLL_M-50_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "dy_m50_mgmlm_ht1200_nonext";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/"))
         filename = "dy_m50_mgmlm_ht200_ext1";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "dy_m50_mgmlm_ht2500_nonext";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17_test/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/"))
         filename = "dy_m50_mgmlm_ht400_ext1";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/V08-00-16/"))
         filename = "dy_m50_mgmlm_ht600_nonext";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "dy_m50_mgmlm_ht800_nonext";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v2/V08-00-16/"))
         filename = "dy_m50_mgmlm_ext1";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/EWKWMinus2Jets_WToLNu_M-50_13TeV-madgraph-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "Wmjj_lnu_madgraph";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/EWKWPlus2Jets_WToLNu_M-50_13TeV-madgraph-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "Wpjj_lnu_madgraph";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/EWKZ2Jets_ZToLL_M-50_13TeV-madgraph-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "Zjj_m50_madgraph";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "sts_4f_leptonic_amcnlo";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "stt_antitop_incdec_powheg";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "stt_top_incdec_powheg";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/ST_tW_antitop_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "sttw_antitop_nofullhaddecay_powheg";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "sttw_top_nofullhaddecay_powheg";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/ST_tWll_5f_LO_13TeV-MadGraph-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "sttwll_madgraph";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/TEST-www_www-Private80X-v1/V08-00-16/"))
         filename = "www_2l_mia";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/TEST-www_wwwext-Private80X-v1/V08-00-16/"))
         filename = "www_2l_ext1_mia";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "ttg_incl_amcnlo";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/"))
         filename = "ttbar_dilep_mgmlm_ext1";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/"))
         filename = "ttbar_1ltop_mgmlm_ext1";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/"))
         filename = "ttbar_1ltbr_mgmlm_ext1";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "vh_nonbb_amcnlo";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "wgjets_incl_mgmlm";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/WGstarToLNuEE_012Jets_13TeV-madgraph_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "wgstar_lnee_012jets_madgraph";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/WGstarToLNuMuMu_012Jets_13TeV-madgraph_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "wgstar_lnmm_012jets_madgraph";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/"))
         filename = "wjets_ht100_mgmlm_ext1";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "wjets_ht1200_mgmlm_nonext";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/"))
         filename = "wjets_ht200_mgmlm_ext1";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/"))
         filename = "wjets_ht2500_mgmlm_ext1";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/"))
         filename = "wjets_ht400_mgmlm_ext1";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/"))
         filename = "wjets_ht600_mgmlm_ext1";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/"))
         filename = "wjets_ht800_mgmlm_ext1";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "wjets_incl_mgmlm";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/WWG_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/"))
         filename = "wwg_incl_amcnlo";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/WWTo2L2Nu_13TeV-powheg_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "ww_2l2nu_powheg";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/WWTo2L2Nu_DoubleScattering_13TeV-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "ww_2l2nu_dbl_scat";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/WWToLNuQQ_13TeV-powheg_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "ww_lnuqq_powheg";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "wwz_incl_amcnlo";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/WZG_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "wzg_incl_amcnlo";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v3/V08-00-16/"))
         filename = "wz_lnqq_amcnlo";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "wz_1l3n_amcnlo";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "wz_3lnu_powheg";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "wzz_incl_amcnlo";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
        filename = "wpwpjj_ewk-qcd_madgraph";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/"))
         filename = "zgamma_2lG_amc";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/ZZTo2L2Nu_13TeV_powheg_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "zz_2l2n_powheg";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "zz_2l2q_powheg";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/ZZTo2Q2Nu_13TeV_amcatnloFXFX_madspin_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "zz_2q2n_amcnlo";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/ZZTo4L_13TeV_powheg_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "zz_4l_powheg";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "zzz_incl_amcnlo";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/tZq_ll_4f_13TeV-amcatnlo-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/"))
         filename = "tzq_ll_amcnlo";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "tth_nonbb_powheg";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/ttHTobb_M125_13TeV_powheg_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "tth_bb_powheg";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/ttWJets_13TeV_madgraphMLM_RunIISummer16MiniAODv2-80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "ttw_incl_mgmlm";
     if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/ttZJets_13TeV_madgraphMLM_RunIISummer16MiniAODv2-80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
         filename = "ttz_incl_mgmlm";
     if (fname.Contains("Run2016"))
         filename = "data";
}

//##############################################################################################################
bool babyMaker_v2::vetophotonprocess()
{
    bool process = tx->getBranch<TString>("bkgtype").EqualTo("photonfakes");
    if (
        (filename.find("wjets_") !=string::npos
       ||filename.find("dy_")    !=string::npos
       ||filename.find("ttbar_") !=string::npos
       ||filename.find("ww_")    !=string::npos
       ||filename.find("wz_")    !=string::npos)
        &&(process)
       ) return true;
    if (
        (filename.find("wgjets_")!=string::npos
       ||filename.find("wgstar_")!=string::npos
       ||filename.find("zgamma_")!=string::npos
       ||filename.find("ttg_")   !=string::npos
       ||filename.find("wwg_")   !=string::npos
       ||filename.find("wzg_")   !=string::npos)
        &&(!process)
       )
        return true;
    return false;
}

//##############################################################################################################
std::tuple<float, float> babyMaker_v2::getlepFakeRateandError(bool data, int lepton_id_version)
{
    // Retrieve relevant variables
    const vector<int>& lep_pdgId = tx->getBranch<vector<int>>("lep_pdgId");
    const vector<LV>& lep_p4 = tx->getBranch<vector<LV>>("lep_p4");
    const vector<float>& lep_coneCorrPt = tx->getBranch<vector<float>>("lep_coneCorrPt");

    // If the lepton counts reveal that it is not even an event in the AR then return 0
    const int& nVlep = tx->getBranch<int>("nVlep");
    const int& nLlep = tx->getBranch<int>("nLlep");
    const int& nTlep = tx->getBranch<int>("nTlep");
    if ((nLlep - 1) != nTlep)
        return make_tuple(0., 0.);

    // Create an int with -1 or 1 to indicate if 3l or ss event
    int version_control = 1;
    if (nLlep >= 3)
        version_control = -1;

    // This is going to take either -1 or 1 (newID) or 0 (oldID).
    int FR_version = version_control * lepton_id_version;

    // Retrieve the flags for the lepton ID
    const vector<int>& istight = nVlep == 2 ? tx->getBranch<vector<int>>("lep_pass_VVV_cutbased_tight") : tx->getBranch<vector<int>>("lep_pass_VVV_cutbased_3l_tight");
    const vector<int>& isloose = nVlep == 2 ? tx->getBranch<vector<int>>("lep_pass_VVV_cutbased_fo")    : tx->getBranch<vector<int>>("lep_pass_VVV_cutbased_3l_fo");

    // Figure out the index by whichever one is the loose but not tight
    int index = -1;
    for (int ilep = 0; ilep < nLlep; ++ilep)
    {
        if (!istight[ilep] && isloose[ilep])
            index = ilep;
    }

    // Sanity check
    if (index < 0)
        cout << "FATAL ERROR: I should never be here" << endl;

    // Variables to read out fake rate
    float error = 0;
    float faker = 0;
    float conept = lep_coneCorrPt[index];

    // Get the actual fakerates
    if (data)
    {
        if (abs(lep_pdgId[index]) == 11)
        {
            error = fakerate_el_data_unc(lep_p4[index].Eta(), conept, FR_version);
            faker = fakerate_el_data    (lep_p4[index].Eta(), conept, FR_version);
        }
        else
        {
            error = fakerate_mu_data_unc(lep_p4[index].Eta(), conept, FR_version);
            faker = fakerate_mu_data    (lep_p4[index].Eta(), conept, FR_version);
        }
    }
    else
    {
        if (abs(lep_pdgId[index]) == 11)
        {
            error = fakerate_el_qcd_unc(lep_p4[index].Eta(), conept, FR_version);
            faker = fakerate_el_qcd    (lep_p4[index].Eta(), conept, FR_version);
        }
        else
        {
            error = fakerate_mu_qcd_unc(lep_p4[index].Eta(), conept, FR_version);
            faker = fakerate_mu_qcd    (lep_p4[index].Eta(), conept, FR_version);
        }
    }

    // return
    return make_tuple(faker, error);
}

//##############################################################################################################
std::tuple<float, float> babyMaker_v2::getlepSFandError(int index, int lepton_id_version)
{
    // Retrieve relevant variables
    const vector<int>& lep_pdgId = tx->getBranch<vector<int>>("lep_pdgId");
    const vector<LV>& lep_p4 = tx->getBranch<vector<LV>>("lep_p4");
    const vector<float>& lep_etaSC = tx->getBranch<vector<float>>("lep_etaSC");

    // If the provided index is out of bound return null
    if (index < 0) return make_tuple(1., 0.);
    if (index >= (int) lep_pdgId.size()) return make_tuple(1., 0.);

    // If electron
    if (abs(lep_pdgId[index]) == 11)
    {
        float effreco  = lepsf_EGammaReco(lep_p4[index].Pt(), lep_etaSC[index]);
        float efftight = lepsf_EGammaTightID(lep_p4[index].Pt(), lep_etaSC[index]);
        float effWWW   = lepsf_EGammaTightPOG_EGammaVVV(lep_p4[index].Pt(), lep_etaSC[index], lepton_id_version);
        float errreco  = lepsf_EGammaReco_unc(lep_p4[index].Pt(), lep_etaSC[index]);
        float errtight = lepsf_EGammaTightID_unc(lep_p4[index].Pt(), lep_etaSC[index]);
        float errWWW   = 0.01 * fabs(1. - effWWW); //add 1% of difference to 1.
        float error = sqrt(pow(errreco * efftight * effWWW, 2) + pow(errtight * effreco * effWWW, 2) + pow(errWWW * effreco * efftight, 2));
//        std::cout <<  " effreco: " << effreco <<  " efftight: " << efftight <<  " effWWW: " << effWWW <<  " effreco*efftight*effWWW: " << effreco*efftight*effWWW <<  std::endl;
        return make_tuple(effreco * efftight * effWWW, error);
    }
    else  //muon
    {
        float effreco   = lepsf_MuReco(lep_p4[index].Pt(), lep_p4[index].Eta());
        float efftight1 = lepsf_MuMediumID_BtoF(lep_p4[index].Pt(), lep_p4[index].Eta());
        float efftight2 = lepsf_MuMediumID_GH(lep_p4[index].Pt(), lep_p4[index].Eta());
        float efftight  = efftight1 * 0.549833 + efftight2 * 0.450167; //luminosity weights B-F vs. G+H
        float effWWW    = lepsf_MuMediumPOG_MuTightVVV(lep_p4[index].Pt(), lep_p4[index].Eta(), lepton_id_version);
        float errreco   = lepsf_MuReco_unc(lep_p4[index].Pt(), lep_p4[index].Eta());
        //recommendation from https://twiki.cern.ch/twiki/bin/view/CMS/MuonWorkInProgressAndPagResults and linked twiki
        float errtight1 = sqrt(pow(lepsf_MuMediumID_BtoF_unc(lep_p4[index].Pt(), lep_p4[index].Eta()), 2) + pow(0.01 * fabs(1. - efftight1), 2));
        float errtight2 = sqrt(pow(lepsf_MuMediumID_GH_unc(lep_p4[index].Pt(), lep_p4[index].Eta()), 2) + pow(0.01 * fabs(1. - efftight2), 2));
        float errtight  = sqrt(pow(errtight1 * 0.549833, 2) + pow(errtight2 * 0.450167, 2));
        float errWWW    = 0.01 * fabs(1. - effWWW); //add 1% of difference to 1.
        float error = sqrt(pow(errreco * efftight * effWWW, 2) + pow(errtight * effreco * effWWW, 2) + pow(errWWW * effreco * efftight, 2));
//        std::cout <<  " effreco: " << effreco <<  " efftight: " << efftight <<  " effWWW: " << effWWW <<  " effreco*efftight*effWWW: " << effreco*efftight*effWWW <<  std::endl;
        return make_tuple(effreco * efftight * effWWW, error);
    }
}

//##############################################################################################################
std::tuple<float, float> babyMaker_v2::getlepSFWeightandError(int lepton_id_version)
{
    // Retrieve relevant variables
    const vector<int>& lep_pdgId = tx->getBranch<vector<int>>("lep_pdgId");

    // Check the bounds
    if (lep_pdgId.size() == 0)
        return make_tuple(1., 0.);

    // Return values
    float SF = 1.;
    float error = 0.;

    // To aggregate the SFs
    vector<float> myeff, myerr;

    // if 3lepton use a different scale factor
    bool is3l = lep_pdgId.size() > 2;
    int multiplier_factor = is3l ? -1 : 1;

    // Loop over leptons and aggregate lepton SFs
    for (unsigned int i = 0; i < lep_pdgId.size(); ++i)
    {
        float tempeff = 0;
        float temperr = 0;
        std::tie(tempeff, temperr) = getlepSFandError(i, multiplier_factor * lepton_id_version);
        myeff.push_back(tempeff);
        myerr.push_back(temperr);
        SF *= tempeff;
    }

    // If SF is = 0
    if (SF == 0)
        return make_tuple(0., 0.); //don't compute error

    // Combine the error by square sum
    for (unsigned int i = 0; i < lep_pdgId.size(); ++i)
        error += pow(SF / myeff[i] * myerr[i], 2);

    // Calculate the error
    error = sqrt(error);

    // Return the result
    return make_tuple(SF, error);
}

//##############################################################################################################
std::tuple<float, float> babyMaker_v2::getTrigEffandError(int lepton_id_version)
{
    // Retrieve relevant variables
    const vector<int>& lep_pdgId = tx->getBranch<vector<int>>("lep_pdgId");
    const vector<LV>& lep_p4 = tx->getBranch<vector<LV>>("lep_p4");

    // If less than two leptons (should never happen anyways)
    // return dummy value
    if (lep_pdgId.size() < 2)
        return make_tuple(0.0, 0.0);

    // Return values
    float eff = 1.0;
    float err = 0.0;

    // even if there are more than 2 leptons apply to the first two only
    float pt0 = lep_p4[0].pt();
    float pt1 = lep_p4[1].pt();
    float eta0 = lep_p4[0].eta();
    float eta1 = lep_p4[1].eta();
    float leadeta  = std::min(fabs(eta0), (float)2.39);
    float traileta = std::min(fabs(eta1), (float)2.39);
    float leadpt   = std::min(pt0, (float)499.);
    float trailpt  = std::min(pt1, (float)499.);

    float bigeta   = leadeta > traileta ? leadeta  : traileta;
    float smalleta = leadeta > traileta ? traileta : leadeta;

    // is ee events
    if (abs(lep_pdgId[0]) == 11 && abs(lep_pdgId[1]) == 11)
    {
        // related to lepton legs
        float e_l0 = trigeff_el_lead(leadeta, leadpt);
        float e_t1 = trigeff_el_trail(traileta, trailpt);
        float e_l1 = trigeff_el_lead(traileta, trailpt);
        float e_t0 = trigeff_el_trail(leadeta, leadpt);
        float d_l0 = trigeff_el_lead(leadeta, leadpt, 1) - trigeff_el_lead(leadeta, leadpt);
        float d_t1 = trigeff_el_trail(traileta, trailpt, 1) - trigeff_el_trail(traileta, trailpt);
        float d_l1 = trigeff_el_lead(traileta, trailpt, 1) - trigeff_el_lead(traileta, trailpt);
        float d_t0 = trigeff_el_trail(leadeta, leadpt, 1) - trigeff_el_trail(leadeta, leadpt);
        float tempeff = 1.0;
        float temperr = 0.0;
        std::tie(tempeff, temperr) = getCombinedTrigEffandError(e_l0, e_l1, e_t0, e_t1, d_l0, d_l1, d_t0, d_t1);
        // dz
        float dzeff = trigeff_diel_dz(smalleta, bigeta);
        float dzerr = trigeff_diel_dz(smalleta, bigeta, 1) - trigeff_diel_dz(smalleta, bigeta, 1);
        eff = tempeff * dzeff;
        err = eff * sqrt(pow(temperr / tempeff, 2) + pow(dzerr / dzeff, 2));
    }

    // emu trigger's DZ filter was near 100% given statistics error also same-sign analysis observes the same.
    // So apply only a flat err of 2%

    // is em events
    if (abs(lep_pdgId[0]) == 11 && abs(lep_pdgId[1]) == 13)
    {
        // related to lepton legs
        float e_l0 = trigeff_el_lead(leadeta, leadpt);
        float e_t1 = trigeff_mu_trail(traileta, trailpt);
        float d_l0 = trigeff_el_lead(leadeta, leadpt, 1) - trigeff_el_lead(leadeta, leadpt);
        float d_t1 = trigeff_mu_trail(traileta, trailpt, 1) - trigeff_mu_trail(traileta, trailpt);
        float tempeff = 1.0;
        float temperr = 0.0;
        std::tie(tempeff, temperr) = getCombinedTrigEffandError(e_l0, 0., 0., e_t1, d_l0, 0., 0., d_t1);
        // dz
        float dzeff = 1.0;
        float dzerr = 0.02;
        eff = tempeff * dzeff;
        err = eff * sqrt(pow(temperr / tempeff, 2) + pow(dzerr / dzeff, 2));
    }

    // is me events
    if (abs(lep_pdgId[0]) == 13 && abs(lep_pdgId[1]) == 11)
    {
        // nominal
        float e_l0 = trigeff_mu_lead(leadeta, leadpt);
        float e_t1 = trigeff_el_trail(traileta, trailpt);
        float d_l0 = trigeff_mu_lead(leadeta, leadpt, 1) - trigeff_mu_lead(leadeta, leadpt);
        float d_t1 = trigeff_el_trail(traileta, trailpt, 1) - trigeff_el_trail(traileta, trailpt);
        float tempeff = 1.0;
        float temperr = 0.0;
        std::tie(tempeff, temperr) = getCombinedTrigEffandError(e_l0, 0., 0., e_t1, d_l0, 0., 0., d_t1);
        // dz
        float dzeff = 1.0;
        float dzerr = 0.02;
        eff = tempeff * dzeff;
        err = eff * sqrt(pow(temperr / tempeff, 2) + pow(dzerr / dzeff, 2));
    }

    // is mm events
    if (abs(lep_pdgId[0]) == 13 && abs(lep_pdgId[1]) == 13)
    {
        // related to lepton legs
        float e_l0 = trigeff_mu_lead(leadeta, leadpt);
        float e_t1 = trigeff_mu_trail(traileta, trailpt);
        float e_l1 = trigeff_mu_lead(traileta, trailpt);
        float e_t0 = trigeff_mu_trail(leadeta, leadpt);
        float d_l0 = trigeff_mu_lead(leadeta, leadpt, 1) - trigeff_mu_lead(leadeta, leadpt);
        float d_t1 = trigeff_mu_trail(traileta, trailpt, 1) - trigeff_mu_trail(traileta, trailpt);
        float d_l1 = trigeff_mu_lead(traileta, trailpt, 1) - trigeff_mu_lead(traileta, trailpt);
        float d_t0 = trigeff_mu_trail(leadeta, leadpt, 1) - trigeff_mu_trail(leadeta, leadpt);
        float tempeff = 1.0;
        float temperr = 0.0;
        std::tie(tempeff, temperr) = getCombinedTrigEffandError(e_l0, e_l1, e_t0, e_t1, d_l0, d_l1, d_t0, d_t1);
        // dz
        float dzeff = 0.241 * trigeff_dimu_dz(smalleta, bigeta) + (1 - 0.241) * 1; // Because DZ filter only affects Period H
        float dzerr = 0.241 * (trigeff_dimu_dz(smalleta, bigeta, 1) - trigeff_dimu_dz(smalleta, bigeta));
        eff = tempeff * dzeff;
        err = eff * sqrt(pow(temperr / tempeff, 2) + pow(dzerr / dzeff, 2));
        // And the fractino of period H is calculated from here: http://www.t2.ucsd.edu/tastwiki/bin/view/CMS/Run2_Data2016
        // 8.636 + 0.221 / 36.814 = 0.241
    }
    
    // Return result
    return make_tuple(eff, err);
}

std::tuple<float, float> babyMaker_v2::getCombinedTrigEffandError(
        float e_l0,
        float e_l1,
        float e_t0,
        float e_t1,
        float d_l0,
        float d_l1,
        float d_t0,
        float d_t1)
{
    bool scheme_that_i_think_is_correct = true;
    if (scheme_that_i_think_is_correct)
    {
        float e_lt = e_l0 * e_t1;
        float f_l0 = e_l0 > 0 ? d_l0 / e_l0 : 0;
        float f_t1 = e_t1 > 0 ? d_t1 / e_t1 : 0;
        float f_lt = sqrt(pow(f_l0, 2) + pow(f_t1, 2));
        float d_lt = e_lt * f_lt;
        float eff = e_lt;
        float err = d_lt;
        return make_tuple(eff, err);
    }
    else
    {
        float e_lt = e_l0 * e_t1;
        float e_tl = e_t0 * e_l1;
        float f_l0 = e_l0 > 0 ? d_l0 / e_l0 : 0;
        float f_l1 = e_l1 > 0 ? d_l1 / e_l1 : 0;
        float f_t0 = e_t0 > 0 ? d_t0 / e_t0 : 0;
        float f_t1 = e_t1 > 0 ? d_t1 / e_t1 : 0;
        float f_lt = sqrt(pow(f_l0, 2) + pow(f_t1, 2));
        float f_tl = sqrt(pow(f_t0, 2) + pow(f_l1, 2));
        float d_lt = e_lt * f_lt;
        float d_tl = e_tl * f_tl;
        float eff = e_lt + (1.0 - e_lt) * e_tl;
        float err2 = pow(d_lt, 2) + pow(d_tl, 2) + pow((e_lt * e_tl) * sqrt(pow(f_lt, 2) + pow(f_tl, 2)), 2);
        float err = sqrt(err2);
        return make_tuple(eff, err);
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
