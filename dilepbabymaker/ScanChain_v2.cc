#include "ScanChain_v2.h"
#include "LeptonScaleFactors.h"
#include "fakerate_v3.h"
#include "puWeight.h"

using namespace std;

//##############################################################################################################
void babyMaker_v2::ScanChain_v2(TChain* chain, std::string baby_name, int max_events, int index, bool verbose)
{

    // Looper
    looper.init(chain, &cms3, max_events);
    looper.setSilent(); // The coreJec.setJECFor function will clash with progress bar otherwise.

    // Output root file
    CreateOutput(index);

    while (looper.nextEvent())
    {
        try
        {
            if (verbose)
                cout << "[verbose] Processed " << looper.getNEventsProcessed() << " out of " << chain->GetEntries() << endl;

            coreJec.setJECFor(looper.getCurrentFileName());
            looper.setSilent(false); // Once JEC is set the message will not clash with progress bar.

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

            // Loop over fatJets
            ProcessFatJets();

            // Process MET (recalculate etc.)
            ProcessMET();

            // Loop over charged particle candidates
            ProcessTracks();

            // Fill baby ntuple
            FillOutput();
        }
        catch (const std::ios_base::failure& e)
        {
            break;
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
    t = new TTree("t", "All events");
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
    tx->createBranch<int>("HLT_SingleIsoEl8");
    tx->createBranch<int>("HLT_SingleIsoEl17");
    tx->createBranch<int>("HLT_SingleIsoMu8");
    tx->createBranch<int>("HLT_SingleIsoMu17");

    tx->createBranch<int>("mc_HLT_DoubleMu");
    tx->createBranch<int>("mc_HLT_DoubleEl");
    tx->createBranch<int>("mc_HLT_DoubleEl_DZ");
    tx->createBranch<int>("mc_HLT_DoubleEl_DZ_2");
    tx->createBranch<int>("mc_HLT_MuEG");
    tx->createBranch<int>("mc_HLT_SingleIsoEl8");
    tx->createBranch<int>("mc_HLT_SingleIsoEl17");
    tx->createBranch<int>("mc_HLT_SingleIsoMu8");
    tx->createBranch<int>("mc_HLT_SingleIsoMu17");

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
    //tx->createBranch<vector<float>>("lep_ptRatioEA");
    tx->createBranch<vector<float>>("lep_ptRel");
    tx->createBranch<vector<float>>("lep_pterr");
    tx->createBranch<vector<float>>("lep_relIso03EAv2");
    tx->createBranch<vector<float>>("lep_relIso04EAv2");
    tx->createBranch<vector<float>>("lep_relIso03EAv2Lep");
    tx->createBranch<vector<int>>("lep_tightCharge");
    tx->createBranch<vector<float>>("lep_trk_pt");
    tx->createBranch<vector<int>>("lep_charge");
    tx->createBranch<vector<float>>("lep_etaSC");
    tx->createBranch<vector<float>>("lep_MVA");
    tx->createBranch<vector<int>>("lep_isMediumPOG");
    tx->createBranch<vector<int>>("lep_isTightPOG");
    tx->createBranch<vector<int>>("lep_isFromW");
    tx->createBranch<vector<int>>("lep_isFromZ");
    tx->createBranch<vector<int>>("lep_isFromB");
    tx->createBranch<vector<int>>("lep_isFromC");
    tx->createBranch<vector<int>>("lep_isFromL");
    tx->createBranch<vector<int>>("lep_isFromLF");
    tx->createBranch<vector<int>>("lep_genPart_index");
    tx->createBranch<vector<float>>("lep_r9");
    tx->createBranch<vector<int>>("lep_nlayers");

    tx->createBranch<vector<LorentzVector>>("jets_p4");
    tx->createBranch<vector<LorentzVector>>("jets_up_p4");
    tx->createBranch<vector<LorentzVector>>("jets_dn_p4");
    tx->createBranch<vector<float>>("jets_csv");
    tx->createBranch<vector<float>>("jets_up_csv");
    tx->createBranch<vector<float>>("jets_dn_csv");

    tx->createBranch<vector<LorentzVector>>("ak8jets_p4");
    tx->createBranch<vector<float>>("ak8jets_softdropMass");
    tx->createBranch<vector<float>>("ak8jets_prunedMass");
    tx->createBranch<vector<float>>("ak8jets_trimmedMass");
    tx->createBranch<vector<float>>("ak8jets_mass");
    tx->createBranch<vector<float>>("ak8jets_nJettinessTau1");
    tx->createBranch<vector<float>>("ak8jets_nJettinessTau2");
    tx->createBranch<vector<float>>("ak8jets_softdropPuppiSubjet1");
    tx->createBranch<vector<float>>("ak8jets_softdropPuppiSubjet2");
    tx->createBranch<vector<float>>("ak8jets_puppi_softdropMass");
    tx->createBranch<vector<float>>("ak8jets_puppi_nJettinessTau1");
    tx->createBranch<vector<float>>("ak8jets_puppi_nJettinessTau2");
    tx->createBranch<vector<float>>("ak8jets_puppi_eta");
    tx->createBranch<vector<float>>("ak8jets_puppi_phi");
    tx->createBranch<vector<float>>("ak8jets_puppi_pt");
    tx->createBranch<vector<float>>("ak8jets_puppi_mass");

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
    tx->createBranch<int>("Flag_badMuonFilterv2");
    tx->createBranch<int>("Flag_badChargedCandidateFilterv2");
    tx->createBranch<int>("Flag_eeBadScFilter");
    tx->createBranch<int>("Flag_globalTightHalo2016");
    tx->createBranch<int>("Flag_goodVertices");
    tx->createBranch<int>("Flag_ecalLaserCorrFilter");
    tx->createBranch<int>("Flag_hcalLaserEventFilter");
    tx->createBranch<int>("Flag_trackingFailureFilter");
    tx->createBranch<int>("Flag_CSCTightHaloFilter");
    tx->createBranch<int>("Flag_CSCTightHalo2015Filter");
    tx->createBranch<int>("Flag_badMuons");
    tx->createBranch<int>("Flag_duplicateMuons");
    tx->createBranch<int>("Flag_noBadMuons");

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
    tx->createBranch<float>("MTmax3L");
    tx->createBranch<float>("MTmax3L_up");
    tx->createBranch<float>("MTmax3L_dn");

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
    tx->createBranch<float>("ffwgt_el_up");
    tx->createBranch<float>("ffwgt_el_dn");
    tx->createBranch<float>("ffwgt_mu_up");
    tx->createBranch<float>("ffwgt_mu_dn");
    tx->createBranch<float>("ffwgt_closure_up");
    tx->createBranch<float>("ffwgt_closure_dn");
    tx->createBranch<float>("ffwgt_closure_el_up");
    tx->createBranch<float>("ffwgt_closure_el_dn");
    tx->createBranch<float>("ffwgt_closure_mu_up");
    tx->createBranch<float>("ffwgt_closure_mu_dn");
    tx->createBranch<float>("ffwgt_full_up");
    tx->createBranch<float>("ffwgt_full_dn");

    tx->createBranch<float>("ffwgtqcd");
    tx->createBranch<float>("ffwgtqcd_up");
    tx->createBranch<float>("ffwgtqcd_dn");

    tx->createBranch<float>("lepsf");
    tx->createBranch<float>("lepsf_up");
    tx->createBranch<float>("lepsf_dn");

    tx->createBranch<float>("trigeff");
    tx->createBranch<float>("trigeff_up");
    tx->createBranch<float>("trigeff_dn");

    tx->createBranch<float>("trigsf");
    tx->createBranch<float>("trigsf_up");
    tx->createBranch<float>("trigsf_dn");

    tx->createBranch<float>("weight_fr_r1_f1");
    tx->createBranch<float>("weight_fr_r1_f2");
    tx->createBranch<float>("weight_fr_r1_f0p5");
    tx->createBranch<float>("weight_fr_r2_f1");
    tx->createBranch<float>("weight_fr_r2_f2");
    tx->createBranch<float>("weight_fr_r2_f0p5");
    tx->createBranch<float>("weight_fr_r0p5_f1");
    tx->createBranch<float>("weight_fr_r0p5_f2");
    tx->createBranch<float>("weight_fr_r0p5_f0p5");
    tx->createBranch<float>("weight_pdf_up");
    tx->createBranch<float>("weight_pdf_down");
    tx->createBranch<float>("weight_alphas_down");
    tx->createBranch<float>("weight_alphas_up");

    tx->clear();

    h_neventsinfile = new TH1F("h_neventsinfile", "", 15, 0, 15);
    h_neventsinfile->SetBinContent(1, looper.getTChain()->GetEntries()); // this is the bin with value = 0
}


//##############################################################################################################
void babyMaker_v2::SaveOutput()
{
    ofile->cd();

    t_os      = t->CopyTree("((nVlep==2)&&(lep_pdgId[0]*lep_pdgId[1]<0))");
    t_ss      = t->CopyTree("((nVlep>=3)||((nVlep==2)&&(lep_pdgId[0]*lep_pdgId[1]>0)))");

    t_www     = t->CopyTree("((nVlep>=3)||((nVlep==2)&&(lep_pdgId[0]*lep_pdgId[1]>0)))*(bkgtype==\"WWW\")||(bkgtype==\"WHtoWWW\")");
    t_qflip   = t->CopyTree("((nVlep>=3)||((nVlep==2)&&(lep_pdgId[0]*lep_pdgId[1]>0)))*(bkgtype==\"chargeflips\")");
    t_photon  = t->CopyTree("((nVlep>=3)||((nVlep==2)&&(lep_pdgId[0]*lep_pdgId[1]>0)))*(bkgtype==\"photonfakes\")");
    t_fakes   = t->CopyTree("((nVlep>=3)||((nVlep==2)&&(lep_pdgId[0]*lep_pdgId[1]>0)))*(bkgtype==\"fakes\")");
    t_prompt  = t->CopyTree("((nVlep>=3)||((nVlep==2)&&(lep_pdgId[0]*lep_pdgId[1]>0)))*((nVlep==2&&bkgtype==\"trueSS\")||(nVlep>=3&&bkgtype==\"trueWWW\"))");
    t_lostlep = t->CopyTree("((nVlep>=3)||((nVlep==2)&&(lep_pdgId[0]*lep_pdgId[1]>0)))*((nVlep==2&&bkgtype==\"SSLL\")||(nVlep>=3&&(bkgtype==\"3lLL\"||bkgtype==\"true3L\")))");

    t_os->SetName("t_os");
    t_ss->SetName("t_ss");
    t_www->SetName("t_www");
    t_qflip->SetName("t_qflip");
    t_photon->SetName("t_photon");
    t_fakes->SetName("t_fakes");
    t_prompt->SetName("t_prompt");
    t_lostlep->SetName("t_lostlep");

    t_os->SetTitle("Opposite Sign Events");
    t_ss->SetTitle("Same Sign Events");
    t_www->SetTitle("Signal Events");
    t_qflip->SetTitle("Charge Flip Events");
    t_photon->SetTitle("Prompt Photon Events");
    t_fakes->SetTitle("Fake Lepton Events");
    t_prompt->SetTitle("Prompt Lepton Events");
    t_lostlep->SetTitle("Lost Lepton Events or WZ in 3-lepton categories");

    t->Write();
    t_os->Write();
    t_ss->Write();
    t_www->Write();
    t_qflip->Write();
    t_photon->Write();
    t_fakes->Write();
    t_prompt->Write();
    t_lostlep->Write();

    h_neventsinfile->Write();
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
void babyMaker_v2::ProcessFatJets() { coreFatJet.process(coreJec); }

//##############################################################################################################
void babyMaker_v2::ProcessMET() { coreMET.process(coreJec); }

//##############################################################################################################
void babyMaker_v2::ProcessTracks() { coreTrack.process(); }

//##############################################################################################################
bool babyMaker_v2::PassPresel()
{
    return PassPresel_v3();
}

//##############################################################################################################
bool babyMaker_v2::PassPresel_v1()
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
        if (cms3.els_p4()[iel].pt() > 20. && passElectronSelection_VVV(iel, VVV_FO_SS))
            nloose++;
    }
    for (auto& imu : coreMuon.index)
    {
        if (cms3.mus_p4()[imu].pt() > 20. && passMuonSelection_VVV(imu, VVV_FO_SS))
            nloose++;
    }
    if (nloose != 2)
        return false;
    return true;
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
        FATALERROR(__FUNCTION__);
        return false;
    }
}

//##############################################################################################################
bool babyMaker_v2::PassPresel_v2()
{
    // Select 2 SS lepton events or 3 or more lepton events
    vector<int> el_idx = coreElectron.index;
    vector<int> mu_idx = coreMuon.index;

    int nveto = el_idx.size() + mu_idx.size();

    // If more than 3 veto lepton events, then dump.
    if (nveto > 3)
        return false;

    // If 3 veto lepton events, then require at least 2 tight 3lid leptons (n.b. double fakes are not possible.)
    // Also, require that it is total charge == 1
    if (nveto == 3)
    {
        int ntight = 0;
        int chargesum = 0;
        for (auto& iel : coreElectron.index)
        {
            if (cms3.els_p4()[iel].pt() > 20. && passElectronSelection_VVV(iel, VVV_TIGHT_3L))
                ntight++;
            chargesum += cms3.els_charge()[iel];
        }
        for (auto& imu : coreMuon.index)
        {
            if (cms3.mus_p4()[imu].pt() > 20. && passMuonSelection_VVV(imu, VVV_TIGHT_3L))
                ntight++;
            chargesum += cms3.mus_charge()[imu];
        }
        if (ntight >= 2)
            return abs(chargesum) == 1;
        else
            return false;
    }

    // If 2 veto lepton events, then require at least one tight ss lepton (n.b. double fakes are not possible.)
    if (nveto == 2)
    {
        int ntight = 0;
        int chargesum = 0;
        for (auto& iel : coreElectron.index)
        {
            if (cms3.els_p4()[iel].pt() > 25. && passElectronSelection_VVV(iel, VVV_TIGHT_SS))
                ntight++;
            chargesum += cms3.els_charge()[iel];
        }
        for (auto& imu : coreMuon.index)
        {
            if (cms3.mus_p4()[imu].pt() > 25. && passMuonSelection_VVV(imu, VVV_TIGHT_SS))
                ntight++;
            chargesum += cms3.mus_charge()[imu];
        }
        if (ntight >= 1)
        {
            if (abs(chargesum) == 2) // If same-sign accept
                return true;
            else if (ntight == 2) // If two-tight accept
                return true;
            else
                return false; // If not same-sign and not two-tight discard
        }
        else
        {
            return false;
        }
    }

    // If 1 veto lepton events, then write out the whole thing
    if (nveto == 1)
    {
        // Check if data,
        bool isdata = filename.compare(0, 4, "data") == 0;
        if (isdata)
        {
            // If data then check the triggers
            // These triggers are checked in coreutil, but to optimize the code performance I hand check them if data
            // I don't wish to run coreTrigger.process() for all events
            if (el_idx.size() == 1)
            {
                int HLT_SingleIsoEl17 = passHLTTriggerPattern("HLT_Ele17_CaloIdL_TrackIdL_IsoVL_PFJet30_v");
                if (HLT_SingleIsoEl17 > 0) return true;
                int HLT_SingleIsoEl8 = passHLTTriggerPattern("HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30_v");
                if (HLT_SingleIsoEl8 > 0) return true;
            }
            else if (mu_idx.size() == 1)
            {
                int HLT_SingleIsoMu17 = passHLTTriggerPattern("HLT_Mu17_TrkIsoVVL_v");
                if (HLT_SingleIsoMu17 > 0) return true;
                int HLT_SingleIsoMu8 = passHLTTriggerPattern("HLT_Mu8_TrkIsoVVL_v");
                if (HLT_SingleIsoMu8 > 0) return true;
            }
            // If it reaches this point, then it means that none of the trigger passed
            return false;
        }
        bool isqcd = filename.compare(0, 4, "qcd_") == 0;
        bool isttbar = filename.compare(0, 6, "ttbar_") == 0;
        bool isW = filename.compare(0, 6, "wjets_") == 0;
        bool isZ = filename.compare(0, 3, "dy_") == 0;
        bool isWW = filename.compare(0, 3, "ww_") == 0;
        bool isWZ = filename.compare(0, 3, "wz_") == 0;
        bool isZZ = filename.compare(0, 3, "zz_") == 0;
        return isqcd || isttbar || isW || isZ || isWW || isWZ || isZZ;
    }

    // Anything else dump
    return false;
}

//##############################################################################################################
bool babyMaker_v2::PassPresel_v3()
{
    // Select 2 SS lepton events or 3 or more lepton events
    vector<int> el_idx = coreElectron.index;
    vector<int> mu_idx = coreMuon.index;

    // If 3 or more veto lepton events. then require the event contains 3 loose and 2 or more tight leptons
    // Such requirement ensures simplicity in various things like SFOS counter and fake rate application
    // Also, require that it is total charge == 1
    if (el_idx.size() + mu_idx.size() > 2)
    {
        int nloose = 0;
        int ntight = 0;
        int chargesum = 0;
        for (auto& iel : coreElectron.index)
        {
            if (cms3.els_p4()[iel].pt() > 20. && passElectronSelection_VVV(iel, VVV_FO_3L))
            {
                nloose++;
                chargesum += cms3.els_charge()[iel];
            }
            if (cms3.els_p4()[iel].pt() > 20. && passElectronSelection_VVV(iel, VVV_TIGHT_3L))
            {
                ntight++;
            }
        }
        for (auto& imu : coreMuon.index)
        {
            if (cms3.mus_p4()[imu].pt() > 20. && passMuonSelection_VVV(imu, VVV_FO_3L))
            {
                nloose++;
                chargesum += cms3.mus_charge()[imu];
            }
            if (cms3.mus_p4()[imu].pt() > 20. && passMuonSelection_VVV(imu, VVV_TIGHT_3L))
            {
                ntight++;
            }
        }
        if (nloose == 3 && ntight >= 2)
            return abs(chargesum) == 1;
        else
            return false;
    }
    // If less than 2 leptons skip
    if (el_idx.size() + mu_idx.size() < 2) return false;
    // If equal to 2 leptons then must be a same-sign and at must have two loose lepton and one or more tight lepton
    int nloose = 0;
    int ntight = 0;
    for (auto& iel : coreElectron.index)
    {
        if (cms3.els_p4()[iel].pt() > 25. && passElectronSelection_VVV(iel, VVV_FO_SS))
            nloose++;
        if (cms3.els_p4()[iel].pt() > 25. && passElectronSelection_VVV(iel, VVV_TIGHT_SS))
            ntight++;
    }
    for (auto& imu : coreMuon.index)
    {
        if (cms3.mus_p4()[imu].pt() > 25. && passMuonSelection_VVV(imu, VVV_FO_SS))
            nloose++;
        if (cms3.mus_p4()[imu].pt() > 25. && passMuonSelection_VVV(imu, VVV_TIGHT_SS))
            ntight++;
    }
    if (nloose != 2 || ntight < 1)
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
        FATALERROR(__FUNCTION__);
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

    // Fill baby ntuple branches for fat-jets
    FillFatJets();

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

    // Fill Weights
    FillWeights();

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
        //const LorentzVector& temp_jet_p4_v0 = closestJet(cms3.els_p4()[idx], 0.4, 3.0, /*whichCorr = */0);
        //const LorentzVector& temp_jet_p4_v1 = closestJet(cms3.els_p4()[idx], 0.4, 3.0, /*whichCorr = */1);
        int jetidx = closestJetIdx(cms3.els_p4()[idx], 0.4, 3.0);
        float closeJetPt = temp_jet_p4.pt();
        float ptratio = (closeJetPt > 0. ? cms3.els_p4()[idx].pt() / closeJetPt : 1.);
        //float ptratioEA = (temp_jet_p4_v0.pt() > 0. ? cms3.els_p4()[idx].pt() / (temp_jet_p4_v0.pt() - (elEA03(idx, 2) * cms3.evt_fixgridfastjet_all_rho() * (cms3.pfjets_area()[jetidx] / 0.3 * 0.3 * TMath::Pi()))) : 1.);
        //float conecorrptfactorraw = coreElectron.index.size() + coreMuon.index.size() > 2 ?  0.84 / ptratio : 0.9 / ptratio;
        //float conecorrptfactor = max(0., conecorrptfactorraw - 1.) + 1.; // To clip correcting once it passes tight isolation criteria
        float conecorrptfactorraw = coreElectron.index.size() + coreMuon.index.size() > 2 ? eleRelIso03EA(idx, 2, true) - 0.03: eleRelIso03EA(idx, 2, true) - 0.05;
        float conecorrptfactor = max(0., (double) conecorrptfactorraw) + 1.; // To clip correcting once it passes tight isolation criteria

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
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_fo_noiso"   , cms3.els_p4()[idx].pt() > 20. && passElectronSelection_VVV(idx, VVV_FO_NOISO));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_tight_noiso", cms3.els_p4()[idx].pt() > 25. && passElectronSelection_VVV(idx, VVV_TIGHT_NOISO));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_veto_noiso" , cms3.els_p4()[idx].pt() > 10. && passElectronSelection_VVV(idx, VVV_VETO_NOISO));
        tx->pushbackToBranch<int>           ("lep_pdgId"                        , cms3.els_charge()[idx]*(-11));
        tx->pushbackToBranch<float>         ("lep_dxy"                          , cms3.els_dxyPV()[idx]);
        tx->pushbackToBranch<float>         ("lep_dz"                           , cms3.els_dzPV()[idx]);
        tx->pushbackToBranch<float>         ("lep_ptRatio"                      , ptratio);
        //tx->pushbackToBranch<float>         ("lep_ptRatioEA"                    , ptratioEA);
        tx->pushbackToBranch<float>         ("lep_ptRel"                        , ptRel(cms3.els_p4()[idx], temp_jet_p4, true));
        tx->pushbackToBranch<float>         ("lep_pterr"                        , cms3.els_ptErr()[idx]);
        tx->pushbackToBranch<float>         ("lep_relIso03EAv2"                 , eleRelIso03EA(idx, 2));
        tx->pushbackToBranch<float>         ("lep_relIso03EAv2Lep"              , eleRelIso03EA(idx, 2, true));
        tx->pushbackToBranch<int>           ("lep_tightCharge"                  , tightChargeEle(idx));
        tx->pushbackToBranch<float>         ("lep_trk_pt"                       , cms3.els_trk_p4()[idx].pt());
        tx->pushbackToBranch<int>           ("lep_charge"                       , cms3.els_charge()[idx]);
        tx->pushbackToBranch<float>         ("lep_etaSC"                        , cms3.els_etaSC()[idx]);
        tx->pushbackToBranch<float>         ("lep_MVA"                          , getMVAoutput(idx));
        tx->pushbackToBranch<int>           ("lep_isMediumPOG"                  , 1);
        tx->pushbackToBranch<int>           ("lep_isTightPOG"                   , 1);
        tx->pushbackToBranch<float>         ("lep_r9"                           , cms3.els_r9()[idx]);
        tx->pushbackToBranch<int>           ("lep_nlayers"                      , -1);
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
        //const LorentzVector& temp_jet_p4_v0 = closestJet(cms3.mus_p4()[idx], 0.4, 3.0, /*whichCorr = */0);
        //const LorentzVector& temp_jet_p4_v1 = closestJet(cms3.mus_p4()[idx], 0.4, 3.0, /*whichCorr = */1);
        int jetidx = closestJetIdx(cms3.mus_p4()[idx], 0.4, 3.0);
        float closeJetPt = temp_jet_p4.pt();
        float ptratio = (closeJetPt > 0. ? cms3.mus_p4()[idx].pt() / closeJetPt : 1.);
        //float ptratioEA = (temp_jet_p4_v0.pt() > 0. ?  cms3.mus_p4()[idx].pt() / (temp_jet_p4_v0.pt() - (muEA03(idx, 2) * cms3.evt_fixgridfastjet_all_rho() * (cms3.pfjets_area()[jetidx] / 0.3 * 0.3 * TMath::Pi()))) : 1.);
        //float conecorrptfactorraw = coreElectron.index.size() + coreMuon.index.size() > 2 ?  0.84 / ptratio : 0.9 / ptratio;
        //float conecorrptfactor = max(0., conecorrptfactorraw - 1.) + 1.; // To clip correcting once it passes tight isolation criteria
        float conecorrptfactorraw = coreElectron.index.size() + coreMuon.index.size() > 2 ? muRelIso03EA(idx, 2, true) - 0.03: muRelIso03EA(idx, 2, true) - 0.07;
        float conecorrptfactor = max(0., (double) conecorrptfactorraw) + 1.; // To clip correcting once it passes tight isolation criteria

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
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_fo_noiso"   , cms3.mus_p4()[idx].pt() > 20. && passMuonSelection_VVV(idx, VVV_FO_NOISO));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_tight_noiso", cms3.mus_p4()[idx].pt() > 25. && passMuonSelection_VVV(idx, VVV_TIGHT_NOISO));
        tx->pushbackToBranch<int>           ("lep_pass_VVV_cutbased_veto_noiso" , cms3.mus_p4()[idx].pt() > 10. && passMuonSelection_VVV(idx, VVV_VETO_NOISO));
        tx->pushbackToBranch<int>           ("lep_pdgId"                        , cms3.mus_charge()[idx]*(-13));
        tx->pushbackToBranch<float>         ("lep_dxy"                          , cms3.mus_dxyPV()[idx]);
        tx->pushbackToBranch<float>         ("lep_dz"                           , cms3.mus_dzPV()[idx]);
        tx->pushbackToBranch<float>         ("lep_ptRatio"                      , ptratio);
        //tx->pushbackToBranch<float>         ("lep_ptRatioEA"                    , ptratioEA);
        tx->pushbackToBranch<float>         ("lep_ptRel"                        , ptRel(cms3.mus_p4()[idx], temp_jet_p4, true));
        tx->pushbackToBranch<float>         ("lep_pterr"                        , cms3.mus_ptErr()[idx]);
        tx->pushbackToBranch<float>         ("lep_relIso03EAv2"                 , muRelIso03EA(idx, 2));
        tx->pushbackToBranch<float>         ("lep_relIso03EAv2Lep"              , muRelIso03EA(idx, 2, true));
        tx->pushbackToBranch<int>           ("lep_tightCharge"                  , tightChargeMuon(idx));
        tx->pushbackToBranch<float>         ("lep_trk_pt"                       , cms3.mus_trk_p4()[idx].pt());
        tx->pushbackToBranch<int>           ("lep_charge"                       , cms3.mus_charge()[idx]);
        tx->pushbackToBranch<float>         ("lep_etaSC"                        , cms3.mus_p4()[idx].eta()); // Electron specific branch. Just take muon's regular eta.
        tx->pushbackToBranch<float>         ("lep_MVA"                          , -99);
        tx->pushbackToBranch<int>           ("lep_isMediumPOG"                  , isMediumMuonPOG(idx));
        tx->pushbackToBranch<int>           ("lep_isTightPOG"                   , isTightMuonPOG(idx));
        tx->pushbackToBranch<float>         ("lep_r9"                           , 0);
        tx->pushbackToBranch<int>           ("lep_nlayers"                      , cms3.mus_nlayers()[idx]);
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
            //"lep_ptRatioEA",
            "lep_ptRel",
            "lep_pterr",
            "lep_relIso03EAv2",
            "lep_relIso03EAv2Lep",
            "lep_relIso04EAv2",
            "lep_trk_pt",
            "lep_etaSC",
            "lep_MVA",
            "lep_coneCorrPt",
            "lep_r9",
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
            "lep_isMediumPOG",
            "lep_isTightPOG",
            "lep_isFromW",
            "lep_isFromZ",
            "lep_isFromB",
            "lep_isFromC",
            "lep_isFromL",
            "lep_isFromLF",
            "lep_nlayers",
            },
            {});
}

//##############################################################################################################
void babyMaker_v2::FillJets()
{
    coreBtagSF.clearSF();
    //std::cout << "coreJet.index.size() = " << coreJet.index.size() << std::endl;
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

void babyMaker_v2::FillFatJets()
{
  for (unsigned ijet = 0; ijet < coreFatJet.index.size(); ++ijet)
  {
    int idx = coreJet.index[ijet];
    float corr = coreJet.corrs[ijet];
    float shift = coreJet.shifts[ijet];
    LorentzVector fatjet = cms3.ak8jets_p4()[idx] * cms3.ak8jets_undoJEC()[idx] * corr;
    if (fatjet.pt() > 20)
    {
      tx->pushbackToBranch<LorentzVector>("ak8jets_p4", fatjet);
      tx->pushbackToBranch<float>("ak8jets_softdropMass", cms3.ak8jets_softdropMass()[idx]);
      tx->pushbackToBranch<float>("ak8jets_prunedMass", cms3.ak8jets_prunedMass()[idx]);
      tx->pushbackToBranch<float>("ak8jets_trimmedMass", cms3.ak8jets_trimmedMass()[idx]);
      tx->pushbackToBranch<float>("ak8jets_nJettinessTau1", cms3.ak8jets_nJettinessTau1()[idx]); 
      tx->pushbackToBranch<float>("ak8jets_nJettinessTau2", cms3.ak8jets_nJettinessTau2()[idx]);
      tx->pushbackToBranch<float>("ak8jets_mass", cms3.ak8jets_mass()[idx]);
      tx->pushbackToBranch<float>("ak8jets_softdropPuppiSubjet1", cms3.ak8jets_softdropPuppiSubjet1()[idx].M());
      tx->pushbackToBranch<float>("ak8jets_softdropPuppiSubjet2", cms3.ak8jets_softdropPuppiSubjet2()[idx].M());     
      tx->pushbackToBranch<float>("ak8jets_puppi_nJettinessTau1", cms3.ak8jets_puppi_nJettinessTau1()[idx]);
      tx->pushbackToBranch<float>("ak8jets_puppi_nJettinessTau2", cms3.ak8jets_puppi_nJettinessTau2()[idx]);
      tx->pushbackToBranch<float>("ak8jets_puppi_softdropMass", cms3.ak8jets_puppi_softdropMass()[idx]);
      tx->pushbackToBranch<float>("ak8jets_puppi_eta", cms3.ak8jets_puppi_eta()[idx]);
      tx->pushbackToBranch<float>("ak8jets_puppi_phi", cms3.ak8jets_puppi_phi()[idx]);
      tx->pushbackToBranch<float>("ak8jets_puppi_pt", cms3.ak8jets_puppi_pt()[idx]);
      tx->pushbackToBranch<float>("ak8jets_puppi_mass", cms3.ak8jets_puppi_mass()[idx]);
    }
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
        tx->setBranch<int>("HLT_SingleIsoEl8", coreTrigger.HLT_SingleIsoEl8);
        tx->setBranch<int>("HLT_SingleIsoEl17", coreTrigger.HLT_SingleIsoEl17);
        tx->setBranch<int>("HLT_SingleIsoMu8", coreTrigger.HLT_SingleIsoMu8);
        tx->setBranch<int>("HLT_SingleIsoMu17", coreTrigger.HLT_SingleIsoMu17);
    }
    else
    {
        tx->setBranch<int>("HLT_DoubleMu", 1);
        tx->setBranch<int>("HLT_DoubleEl", 1);
        tx->setBranch<int>("HLT_DoubleEl_DZ", 1);
        tx->setBranch<int>("HLT_DoubleEl_DZ_2", 1);
        tx->setBranch<int>("HLT_MuEG", 1);
        tx->setBranch<int>("HLT_SingleIsoEl8", 1);
        tx->setBranch<int>("HLT_SingleIsoEl17", 1);
        tx->setBranch<int>("HLT_SingleIsoMu8", 1);
        tx->setBranch<int>("HLT_SingleIsoMu17", 1);
    }
    tx->setBranch<int>("mc_HLT_DoubleMu", coreTrigger.HLT_DoubleMu);
    tx->setBranch<int>("mc_HLT_DoubleEl", coreTrigger.HLT_DoubleEl);
    tx->setBranch<int>("mc_HLT_DoubleEl_DZ", coreTrigger.HLT_DoubleEl_DZ);
    tx->setBranch<int>("mc_HLT_DoubleEl_DZ_2", coreTrigger.HLT_DoubleEl_DZ_2);
    tx->setBranch<int>("mc_HLT_MuEG", coreTrigger.HLT_MuEG);
    tx->setBranch<int>("mc_HLT_SingleIsoEl8", coreTrigger.HLT_SingleIsoEl8);
    tx->setBranch<int>("mc_HLT_SingleIsoEl17", coreTrigger.HLT_SingleIsoEl17);
    tx->setBranch<int>("mc_HLT_SingleIsoMu8", coreTrigger.HLT_SingleIsoMu8);
    tx->setBranch<int>("mc_HLT_SingleIsoMu17", coreTrigger.HLT_SingleIsoMu17);
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

    // Is it CMS4?
    bool is_cms4 = cms3_version.Contains("CMS4");

    if (cms3.evt_isRealData())
    {
        tx->setBranch<int>("Flag_ecalLaserCorrFilter", cms3.filt_ecalLaser());
        tx->setBranch<int>("Flag_hcalLaserEventFilter", cms3.filt_hcalLaser());
        tx->setBranch<int>("Flag_trackingFailureFilter", cms3.filt_trackingFailure());
        tx->setBranch<int>("Flag_CSCTightHaloFilter", cms3.filt_cscBeamHalo());
    }
    else
    {
        tx->setBranch<int>("Flag_ecalLaserCorrFilter", 1);
        tx->setBranch<int>("Flag_hcalLaserEventFilter", 1);
        tx->setBranch<int>("Flag_trackingFailureFilter", 1);
        tx->setBranch<int>("Flag_CSCTightHaloFilter", 1);
    }

    // in data and MC
    tx->setBranch<int>("Flag_HBHENoiseFilter", cms3.filt_hbheNoise());
    tx->setBranch<int>("Flag_HBHEIsoNoiseFilter", cms3.filt_hbheNoiseIso());
    tx->setBranch<int>("Flag_CSCTightHalo2015Filter", cms3.filt_cscBeamHalo2015());
    tx->setBranch<int>("Flag_EcalDeadCellTriggerPrimitiveFilter", cms3.filt_ecalTP());
    tx->setBranch<int>("Flag_goodVertices", cms3.filt_goodVertices());
    tx->setBranch<int>("Flag_eeBadScFilter", cms3.filt_eeBadSc());
    if (!is_cms4)
        tx->setBranch<int>("Flag_badChargedCandidateFilter", badChargedCandidateFilter());
    else
        tx->setBranch<int>("Flag_badChargedCandidateFilter", 1);

    // inputs for badMuonFilters in latest cms3 tags
    if (recent_cms3_version)
    {
        tx->setBranch<int>("Flag_globalTightHalo2016", cms3.filt_globalTightHalo2016());
        if (!is_cms4)
            tx->setBranch<int>("Flag_badMuonFilter", badMuonFilter());
        else
            tx->setBranch<int>("Flag_badMuonFilter", 1);
        tx->setBranch<int>("Flag_badMuonFilterv2", badMuonFilterV2());
        tx->setBranch<int>("Flag_badChargedCandidateFilterv2", badChargedCandidateFilterV2());
        if (small_cms3_version >= 18 && !is_cms4)
        {
            tx->setBranch<int>("Flag_badMuons", cms3.filt_badMuons());
            tx->setBranch<int>("Flag_duplicateMuons", cms3.filt_duplicateMuons());
            tx->setBranch<int>("Flag_noBadMuons", cms3.filt_noBadMuons());
        }
        else
        {
            tx->setBranch<int>("Flag_badMuons", 1);
            tx->setBranch<int>("Flag_duplicateMuons", 1);
            tx->setBranch<int>("Flag_noBadMuons", 1);
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

    //bool isSS = (nVlep == 2 && nLlep == 2);
    //bool is3L = (nVlep >= 3 && nLlep == 3);
    bool isSS = (nVlep == 2);
    bool is3L = (nVlep == 3);

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

    float MT0    = mT(lep_p4[0], MET);
    float MT1    = mT(lep_p4[1], MET);
    float MT2    = mT(lep_p4[2], MET);
    float MT0_up = mT(lep_p4[0], MET_up);
    float MT1_up = mT(lep_p4[1], MET_up);
    float MT2_up = mT(lep_p4[2], MET_up);
    float MT0_dn = mT(lep_p4[0], MET_dn);
    float MT1_dn = mT(lep_p4[1], MET_dn);
    float MT2_dn = mT(lep_p4[2], MET_dn);

    tx->setBranch<float>("MTmax3L", TMath::Max(MT0, TMath::Max(MT1, MT2)));
    tx->setBranch<float>("MTmax3L_up", TMath::Max(MT0_up, TMath::Max(MT1_up, MT2_up)));
    tx->setBranch<float>("MTmax3L_dn", TMath::Max(MT0_dn, TMath::Max(MT1_dn, MT2_dn)));
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
    const vector<int>& lep_pdgId = tx->getBranch<vector<int>>("lep_pdgId");
    float ffwgt;
    float ffwgterr;
    int loose_lep_idx;
    int loose_lep_idx_qcd;
    float ffwgtqcd;
    float ffwgtqcderr;
    std::tie(ffwgt, ffwgterr, loose_lep_idx) = getlepFakeRateandErrorandLooseLepIdx(true);
    std::tie(ffwgtqcd, ffwgtqcderr, loose_lep_idx_qcd) = getlepFakeRateandErrorandLooseLepIdx(false);
    // The closure is taken from the statistical uncertainty of the closure test
    // The closure central values are better than 27% and 28%
    // electron closure fSumw[1]=1, x=0.5, error=0.279466 
    // muon closure     fSumw[1]=1, x=0.5, error=0.268032
    const double el_closure = 0.279466;
    const double mu_closure = 0.268032;
    tx->setBranch<float>("ffwgt", ffwgt);
    tx->setBranch<float>("ffwgt_up", ffwgt + ffwgterr);
    tx->setBranch<float>("ffwgt_dn", ffwgt - ffwgterr);
    tx->setBranch<float>("ffwgt_el_up", loose_lep_idx >= 0 ? (abs(lep_pdgId[loose_lep_idx]) == 11 ? ffwgt + ffwgterr : ffwgt) : 0);
    tx->setBranch<float>("ffwgt_el_dn", loose_lep_idx >= 0 ? (abs(lep_pdgId[loose_lep_idx]) == 11 ? ffwgt - ffwgterr : ffwgt) : 0);
    tx->setBranch<float>("ffwgt_mu_up", loose_lep_idx >= 0 ? (abs(lep_pdgId[loose_lep_idx]) == 13 ? ffwgt + ffwgterr : ffwgt) : 0);
    tx->setBranch<float>("ffwgt_mu_dn", loose_lep_idx >= 0 ? (abs(lep_pdgId[loose_lep_idx]) == 13 ? ffwgt - ffwgterr : ffwgt) : 0);
    tx->setBranch<float>("ffwgt_closure_el_up", loose_lep_idx >= 0 ? (abs(lep_pdgId[loose_lep_idx]) == 11 ? ffwgt + (ffwgt * el_closure) : ffwgt) : 0);
    tx->setBranch<float>("ffwgt_closure_el_dn", loose_lep_idx >= 0 ? (abs(lep_pdgId[loose_lep_idx]) == 11 ? ffwgt - (ffwgt * el_closure) : ffwgt) : 0);
    tx->setBranch<float>("ffwgt_closure_mu_up", loose_lep_idx >= 0 ? (abs(lep_pdgId[loose_lep_idx]) == 13 ? ffwgt + (ffwgt * mu_closure) : ffwgt) : 0);
    tx->setBranch<float>("ffwgt_closure_mu_dn", loose_lep_idx >= 0 ? (abs(lep_pdgId[loose_lep_idx]) == 13 ? ffwgt - (ffwgt * mu_closure) : ffwgt) : 0);
    tx->setBranch<float>("ffwgt_closure_up", loose_lep_idx >= 0 ? (abs(lep_pdgId[loose_lep_idx]) == 11 ? ffwgt + (ffwgt * el_closure) : ffwgt + (ffwgt * mu_closure)) : 0);
    tx->setBranch<float>("ffwgt_closure_dn", loose_lep_idx >= 0 ? (abs(lep_pdgId[loose_lep_idx]) == 11 ? ffwgt - (ffwgt * el_closure) : ffwgt - (ffwgt * mu_closure)) : 0);
    tx->setBranch<float>("ffwgt_full_up", loose_lep_idx >= 0 ? (abs(lep_pdgId[loose_lep_idx]) == 11 ? ffwgt + sqrt(pow(ffwgt * el_closure, 2) + pow(ffwgterr, 2)) : ffwgt + sqrt(pow(ffwgt * mu_closure, 2) + pow(ffwgterr, 2))) : 0);
    tx->setBranch<float>("ffwgt_full_dn", loose_lep_idx >= 0 ? (abs(lep_pdgId[loose_lep_idx]) == 11 ? ffwgt - sqrt(pow(ffwgt * el_closure, 2) + pow(ffwgterr, 2)) : ffwgt - sqrt(pow(ffwgt * mu_closure, 2) + pow(ffwgterr, 2))) : 0);
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
//        float trigeff;
//        float trigefferr;
//        std::tie(trigeff, trigefferr) = getTrigEffandError();
//        tx->setBranch<float>("trigeff", trigeff);
//        tx->setBranch<float>("trigeff_up", trigeff + trigefferr);
//        tx->setBranch<float>("trigeff_dn", trigeff - trigefferr);
        tx->setBranch<float>("trigeff", 1);
        tx->setBranch<float>("trigeff_up", 1);
        tx->setBranch<float>("trigeff_dn", 1);
        float trigsf;
        float trigsferr;
        std::tie(trigsf, trigsferr) = getTrigSFandError();
        tx->setBranch<float>("trigsf", trigsf);
        tx->setBranch<float>("trigsf_up", trigsf + trigsferr);
        tx->setBranch<float>("trigsf_dn", trigsf - trigsferr);
    }
    else
    {
        tx->setBranch<float>("trigeff", 1);
        tx->setBranch<float>("trigeff_up", 1);
        tx->setBranch<float>("trigeff_dn", 1);
        tx->setBranch<float>("trigsf", 1);
        tx->setBranch<float>("trigsf_up", 1);
        tx->setBranch<float>("trigsf_dn", 1);
    }

    // scale pdf variation
    if (!cms3.evt_isRealData())
    {
        float sum_of_pdf_weights = 0;
        float average_of_pdf_weights = 0;
        //error on pdf replicas
        if (cms3.genweights().size() > 110)
        {
            // average of weights
            for (int ipdf = 9; ipdf < 109; ipdf++)
            {
                average_of_pdf_weights += cms3.genweights().at(ipdf);
            }
            average_of_pdf_weights =  average_of_pdf_weights / 100;
            //std of weights.
            for (int ipdf = 9; ipdf < 109; ipdf++)
            {
                sum_of_pdf_weights += (cms3.genweights().at(ipdf) - average_of_pdf_weights) * (cms3.genweights().at(ipdf) - average_of_pdf_weights);
            }
            tx->setBranch<float>("weight_fr_r1_f1", cms3.genweights()[0]);
            tx->setBranch<float>("weight_fr_r1_f2", cms3.genweights()[1]);
            tx->setBranch<float>("weight_fr_r1_f0p5", cms3.genweights()[2]);
            tx->setBranch<float>("weight_fr_r2_f1", cms3.genweights()[3]);
            tx->setBranch<float>("weight_fr_r2_f2", cms3.genweights()[4]);
            tx->setBranch<float>("weight_fr_r2_f0p5", cms3.genweights()[5]);
            tx->setBranch<float>("weight_fr_r0p5_f1", cms3.genweights()[6]);
            tx->setBranch<float>("weight_fr_r0p5_f2", cms3.genweights()[7]);
            tx->setBranch<float>("weight_fr_r0p5_f0p5", cms3.genweights()[8]);
            tx->setBranch<float>("weight_pdf_up", (average_of_pdf_weights + sqrt(sum_of_pdf_weights / 99)));
            tx->setBranch<float>("weight_pdf_down", (average_of_pdf_weights - sqrt(sum_of_pdf_weights / 99)));
            tx->setBranch<float>("weight_alphas_down", cms3.genweights()[109]);
            tx->setBranch<float>("weight_alphas_up", cms3.genweights()[110]);
            h_neventsinfile->Fill(1, tx->getBranch<float>("weight_fr_r1_f1"));
            h_neventsinfile->Fill(2, tx->getBranch<float>("weight_fr_r1_f2"));
            h_neventsinfile->Fill(3, tx->getBranch<float>("weight_fr_r1_f0p5"));
            h_neventsinfile->Fill(4, tx->getBranch<float>("weight_fr_r2_f1"));
            h_neventsinfile->Fill(5, tx->getBranch<float>("weight_fr_r2_f2"));
            h_neventsinfile->Fill(6, tx->getBranch<float>("weight_fr_r2_f0p5"));
            h_neventsinfile->Fill(7, tx->getBranch<float>("weight_fr_r0p5_f1"));
            h_neventsinfile->Fill(8, tx->getBranch<float>("weight_fr_r0p5_f2"));
            h_neventsinfile->Fill(9, tx->getBranch<float>("weight_fr_r0p5_f0p5"));
            h_neventsinfile->Fill(10, tx->getBranch<float>("weight_pdf_up"));
            h_neventsinfile->Fill(11, tx->getBranch<float>("weight_pdf_down"));
            h_neventsinfile->Fill(12, tx->getBranch<float>("weight_alphas_down"));
            h_neventsinfile->Fill(13, tx->getBranch<float>("weight_alphas_up"));
        }
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
        FATALERROR(__FUNCTION__);
        return make_tuple(false, -1, -1);
    }
}

//##############################################################################################################
TString babyMaker_v2::process()
{
    if (cms3.evt_isRealData())                            return "Data";
    if (splitVH())                                        return "WHtoWWW";
    if (filename.find("www_2l_")         != string::npos) return "WWW";
    if (filename.find("www_incl_amcnlo") != string::npos) return "WWWv2";
    if (filename.find("data_")           != string::npos) return "Data";
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
    // 2016
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
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
        filename = "ttbar_incl_powheg";
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
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-15to20_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
        filename = "qcd_mu_pt15";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-20to30_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
        filename = "qcd_mu_pt20";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-30to50_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
        filename = "qcd_mu_pt30";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-50to80_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
        filename = "qcd_mu_pt50";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-80to120_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v3/V08-00-16/"))
        filename = "qcd_mu_pt80";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-120to170_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
        filename = "qcd_mu_pt120";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-170to300_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/"))
        filename = "qcd_mu_pt170";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-300to470_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/V08-00-16/"))
        filename = "qcd_mu_pt300";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-470to600_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/"))
        filename = "qcd_mu_pt470";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-600to800_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
        filename = "qcd_mu_pt600";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-800to1000_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
        filename = "qcd_mu_pt800";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-1000toInf_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v3/V08-00-16/"))
        filename = "qcd_mu_pt1000";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-20to30_EMEnriched_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
        filename = "qcd_em_pt20";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-30to50_EMEnriched_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/"))
        filename = "qcd_em_pt30";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-50to80_EMEnriched_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/"))
        filename = "qcd_em_pt50";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-80to120_EMEnriched_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/"))
        filename = "qcd_em_pt80";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-120to170_EMEnriched_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/"))
        filename = "qcd_em_pt120";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-170to300_EMEnriched_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
        filename = "qcd_em_pt170";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-300toInf_EMEnriched_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
        filename = "qcd_em_pt300";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt_15to20_bcToE_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
        filename = "qcd_bctoe_pt15";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt_20to30_bcToE_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
        filename = "qcd_bctoe_pt20";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt_30to80_bcToE_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
        filename = "qcd_bctoe_pt30";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt_80to170_bcToE_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_backup_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
        filename = "qcd_bctoe_pt80";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt_170to250_bcToE_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
        filename = "qcd_bctoe_pt170";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt_250toInf_bcToE_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"))
        filename = "qcd_bctoe_pt250";

    // 2017
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_mc2017//DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2_MINIAODSIM_CMS4_V09-04-13/"))
        filename = "dy_m1050_madgraph";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_mc2017//DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/"))
        filename = "dy_m50_madgraph";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_mc2017//DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14_ext1-v1_MINIAODSIM_CMS4_V09-04-13/"))
        filename = "dy_m50_madgraph_ext1";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_mc2017//ST_tW_antitop_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/"))
        filename = "sttw_incltop_powheg";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_mc2017//ST_tW_top_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/"))
        filename = "sttw_incltbr_powheg";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_mc2017//TTGamma_SingleLeptFromT_TuneCP5_PSweights_13TeV_madgraph_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/"))
        filename = "ttg_1ltop_madgraph";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_mc2017//TTGamma_SingleLeptFromTbar_TuneCP5_PSweights_13TeV_madgraph_pythia8_RunIIFall17MiniAOD-PU2017_94X_mc2017_realistic_v11-v1_MINIAODSIM_CMS4_V09-04-13/"))
        filename = "ttg_1ltbr_madgraph";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_mc2017//TTHH_TuneCP5_13TeV-madgraph-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/"))
        filename = "tthh_madgraph";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_mc2017//TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/"))
        filename = "ttbar_incl_amcnlo";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_mc2017//TTTJ_TuneCP5_13TeV-madgraph-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/"))
        filename = "tttj_incl_madgraph";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_mc2017//TTTT_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_pilot_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/"))
        filename = "tttt_incl_amcnlo";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_mc2017//TTTW_TuneCP5_13TeV-madgraph-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/"))
        filename = "tttw_incl_madgraph";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_mc2017//TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/"))
        filename = "ttbar_1l_powheg";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_mc2017//TTWH_TuneCP5_13TeV-madgraph-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/"))
        filename = "ttwh_incl_madgraph";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_mc2017//TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/"))
        filename = "ttw_ln_amcnlo";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_mc2017//TTWW_TuneCP5_13TeV-madgraph-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1_MINIAODSIM_CMS4_V09-04-13/"))
        filename = "ttww_incl_madgraph_ext1";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_mc2017//TTWZ_TuneCP5_13TeV-madgraph-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/"))
        filename = "ttwz_incl_madgraph";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_mc2017//TTZH_TuneCP5_13TeV-madgraph-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/"))
        filename = "ttzh_incl_madgraph";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_mc2017//TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/"))
        filename = "ttz_m10llnn_amcnlo";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_mc2017//TTZToLL_M-1to10_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/"))
        filename = "ttz_m1to10ll_amcnlo";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_mc2017//TTZZ_TuneCP5_13TeV-madgraph-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/"))
        filename = "ttzz_incl_madgraph";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_mc2017//WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2_MINIAODSIM_CMS4_V09-04-13/"))
        filename = "wjets_ln_madgraph_ext1";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_mc2017//WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/"))
        filename = "www_incl_amcnlo";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_mc2017//WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/"))
        filename = "wwz_incl_amcnlo";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_mc2017//WW_DoubleScattering_13TeV-pythia8_TuneCP5_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/"))
        filename = "ww_dblsctincl_pythia";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_mc2017//WW_TuneCP5_13TeV-pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1_MINIAODSIM_CMS4_V09-04-13/"))
        filename = "ww_incl_pythia";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_mc2017//WZG_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/"))
        filename = "wzg_incl_amcnlo";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_mc2017//WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/"))
        filename = "wz_3lnu_amcnlo";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_mc2017//WZZ_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/"))
        filename = "wzz_incl_amcnlo";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_mc2017//WZ_TuneCP5_13TeV-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/"))
        filename = "wz_incl_pythia";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_mc2017//ZZTo4L_13TeV_powheg_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/"))
        filename = "zz_4l_powheg";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_mc2017//ZZZ_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/"))
        filename = "zzz_incl_amcnlo";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_mc2017//tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/"))
        filename = "tzq_ll_amcnlo";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_mc2017//ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1_MINIAODSIM_CMS4_V09-04-13/"))
        filename = "tth_nonbb_powheg";

    if (fname.Contains("/hadoop/cms/store/group/snt/run2_data2017//DoubleEG_Run2017B-31Mar2018-v1_MINIAOD_CMS4_V09-04-12/"))
        filename = "data_Run2017B_ee";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_data2017//DoubleEG_Run2017C-31Mar2018-v1_MINIAOD_CMS4_V09-04-12/"))
        filename = "data_Run2017C_ee";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_data2017//DoubleEG_Run2017D-31Mar2018-v1_MINIAOD_CMS4_V09-04-12/"))
        filename = "data_Run2017D_ee";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_data2017//DoubleEG_Run2017E-31Mar2018-v1_MINIAOD_CMS4_V09-04-12/"))
        filename = "data_Run2017E_ee";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_data2017//DoubleEG_Run2017F-31Mar2018-v1_MINIAOD_CMS4_V09-04-12/"))
        filename = "data_Run2017F_ee";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_data2017//DoubleMuon_Run2017B-31Mar2018-v1_MINIAOD_CMS4_V09-04-12/"))
        filename = "data_Run2017B_mm";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_data2017//DoubleMuon_Run2017C-31Mar2018-v1_MINIAOD_CMS4_V09-04-12/"))
        filename = "data_Run2017C_mm";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_data2017//DoubleMuon_Run2017D-31Mar2018-v1_MINIAOD_CMS4_V09-04-12/"))
        filename = "data_Run2017D_mm";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_data2017//DoubleMuon_Run2017E-31Mar2018-v1_MINIAOD_CMS4_V09-04-12/"))
        filename = "data_Run2017E_mm";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_data2017//DoubleMuon_Run2017F-31Mar2018-v1_MINIAOD_CMS4_V09-04-12/"))
        filename = "data_Run2017F_mm";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_data2017//MuonEG_Run2017B-31Mar2018-v1_MINIAOD_CMS4_V09-04-12/"))
        filename = "data_Run2017B_em";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_data2017//MuonEG_Run2017C-31Mar2018-v1_MINIAOD_CMS4_V09-04-12/"))
        filename = "data_Run2017C_em";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_data2017//MuonEG_Run2017D-31Mar2018-v1_MINIAOD_CMS4_V09-04-12/"))
        filename = "data_Run2017D_em";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_data2017//MuonEG_Run2017E-31Mar2018-v1_MINIAOD_CMS4_V09-04-12/"))
        filename = "data_Run2017E_em";
    if (fname.Contains("/hadoop/cms/store/group/snt/run2_data2017//MuonEG_Run2017F-31Mar2018-v1_MINIAOD_CMS4_V09-04-12/"))
        filename = "data_Run2017F_em";

}

//##############################################################################################################
bool babyMaker_v2::vetophotonprocess()
{
    bool process = tx->getBranch<TString>("bkgtype").EqualTo("photonfakes");
    if (
        (filename.find("wjets_") == 0
       ||filename.find("dy_")    == 0
       ||filename.find("ttbar_") == 0
       ||filename.find("ww_")    == 0
       ||filename.find("wz_")    == 0)
        &&(process)
       ) return true;
    if (
        (filename.find("wgjets_") == 0
       ||filename.find("wgstar_") == 0
       ||filename.find("zgamma_") == 0
       ||filename.find("ttg_")    == 0
       ||filename.find("wwg_")    == 0
       ||filename.find("wzg_")    == 0)
        &&(!process)
       )
        return true;
    return false;
}

//##############################################################################################################
std::tuple<float, float, int> babyMaker_v2::getlepFakeRateandErrorandLooseLepIdx(bool data, int lepton_id_version)
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
        return make_tuple(0., 0., -1);

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
    {
        std::cout <<  " passCount(tx->getBranch<vector<int>>('lep_pass_VVV_cutbased_3l_fo')): " << passCount(tx->getBranch<vector<int>>("lep_pass_VVV_cutbased_3l_fo")) <<  std::endl;
        std::cout <<  " nVlep: " << nVlep <<  std::endl;
        vector<int> el_idx = coreElectron.index;
        vector<int> mu_idx = coreMuon.index;
        std::cout <<  " el_idx.size(): " << el_idx.size() <<  " mu_idx.size(): " << mu_idx.size() <<  std::endl;
        std::cout <<  " isloose.size(): " << isloose.size() <<  std::endl;
        for (int ilep = 0; ilep < nVlep; ++ilep)
            std::cout <<  " istight[ilep]: " << istight[ilep] <<  " isloose[ilep]: " << isloose[ilep] <<  std::endl;
        FATALERROR(__FUNCTION__);
    }

    // Variables to read out fake rate
    float error = 0;
    float faker = 0;
    float conept = lep_coneCorrPt[index];

    // Get the actual fakerates
    if (data)
    {
        if (abs(lep_pdgId[index]) == 11)
        {
            error = fakerate_el_data_unc(conept, lep_p4[index].Eta(), FR_version);
            faker = fakerate_el_data    (conept, lep_p4[index].Eta(), FR_version);
        }
        else
        {
            error = fakerate_mu_data_unc(conept, lep_p4[index].Eta(), FR_version);
            faker = fakerate_mu_data    (conept, lep_p4[index].Eta(), FR_version);
        }
    }
    else
    {
        if (abs(lep_pdgId[index]) == 11)
        {
            error = fakerate_el_qcd_unc(conept, lep_p4[index].Eta(), FR_version);
            faker = fakerate_el_qcd    (conept, lep_p4[index].Eta(), FR_version);
        }
        else
        {
            error = fakerate_mu_qcd_unc(conept, lep_p4[index].Eta(), FR_version);
            faker = fakerate_mu_qcd    (conept, lep_p4[index].Eta(), FR_version);
        }
    }

    // return
    return make_tuple(faker, error, index);
}

////##############################################################################################################
//std::tuple<float, float> babyMaker_v2::getlepSFandError(int index, int lepton_id_version) // deprecated
//{
//    // Retrieve relevant variables
//    const vector<int>&   lep_pdgId = tx->getBranch<vector<int>>  ("lep_pdgId");
//    const vector<LV>&    lep_p4    = tx->getBranch<vector<LV>>   ("lep_p4");
//    const vector<float>& lep_etaSC = tx->getBranch<vector<float>>("lep_etaSC");
//
//    // If the provided index is out of bound return null
//    if (index < 0) return make_tuple(1., 0.);
//    if (index >= (int) lep_pdgId.size()) return make_tuple(1., 0.);
//
//    // If electron
//    if (abs(lep_pdgId[index]) == 11)
//    {
//        // Parametrized kinematic quantity for scale factors
//        float pt = lep_p4[index].Pt();
//        float eta = lep_etaSC[index];
//        // Scale Factors
//        float sfreco   = lepsf_EGammaReco               (pt, eta);
//        float sftight  = lepsf_EGammaTightID            (pt, eta);
//        float sfWWW    = lepsf_EGammaTightPOG_EGammaVVV (pt, eta, lepton_id_version);
//        float sfWWWIso = lepsf_EGammaVVV_Isolation      (pt, eta, lepton_id_version);
//        float sf       = sfreco * sftight * sfWWW * sfWWWIso;
//        // Errors
//        float errreco   = lepsf_EGammaReco_unc           (pt, eta);
//        float errtight  = lepsf_EGammaTightID_unc        (pt, eta);
//        float errWWW    = fabs(lepsf_EGammaTightPOG_EGammaVVV(pt, eta, lepton_id_version, 1) - sfWWW   ); // difference against syst = +1 is the error
//        float errWWWIso = fabs(lepsf_EGammaVVV_Isolation     (pt, eta, lepton_id_version, 1) - sfWWWIso); // difference against syst = +1 is the error 
//        // Following the formula from https://en.wikipedia.org/wiki/Propagation_of_uncertainty#Example_formulas, cause I always forget
//        float fracerrreco   = sfreco   > 0 ? errreco   / sfreco   : 0;
//        float fracerrtight  = sftight  > 0 ? errtight  / sftight  : 0;
//        float fracerrWWW    = sfWWW    > 0 ? errWWW    / sfWWW    : 0;
//        float fracerrWWWIso = sfWWWIso > 0 ? errWWWIso / sfWWWIso : 0;
//        float fracerrtotal  = sqrt(pow(fracerrreco, 2) + pow(fracerrtight, 2) + pow(fracerrWWW, 2) + pow(fracerrWWWIso, 2));
//        // Assume the "tight" and "WWW" error (which are MVA based for lepton_id_version >= 2) are 100% correlated
//        if (lepton_id_version >= 2)
//            fracerrtotal = sqrt(pow(fracerrreco, 2) + pow(fracerrtight + fracerrWWW, 2) + pow(fracerrWWWIso, 2));
//        float error         = fracerrtotal * sf;
//        // Return the value
//        return make_tuple(sf, error);
//    }
//    else  //muon
//    {
//        // Parametrized kinematic quantity for scale factors
//        float pt = lep_p4[index].Pt();
//        float eta = lep_p4[index].Eta();
//        // Scale Factors
//        float sfreco   = lepsf_MuReco                (pt, eta);
//        float sftight1 = lepsf_MuMediumID_BtoF       (pt, eta);
//        float sftight2 = lepsf_MuMediumID_GH         (pt, eta);
//        float sfWWW    = lepsf_MuMediumPOG_MuTightVVV(pt, eta, lepton_id_version);
//        float sftight  = sftight1 * 0.549833 + sftight2 * 0.450167; //luminosity weights B-F vs. G+H
//        float sf       = sftight * sfWWW;
//        // Errors
//        // Recommendation from https://twiki.cern.ch/twiki/bin/view/CMS/MuonWorkInProgressAndPagResults and linked twiki
//        // From the recommendations what we conclude is to add is a 1% additional uncertainty.
//        float errreco   = lepsf_MuReco_unc         (pt, eta);
//        float errtight1 = lepsf_MuMediumID_BtoF_unc(pt, eta); // Additional 1%
//        float errtight2 = lepsf_MuMediumID_GH_unc  (pt, eta); // Additional 1%
//        float errWWW    = fabs(lepsf_MuMediumPOG_MuTightVVV(pt, eta, lepton_id_version, 1) - sfWWW); // difference against syst = +1 is the error 
//        float errtight  = sqrt(pow(errtight1 * 0.549833, 2) + pow(errtight2 * 0.450167, 2));
//        // Following the formula from https://en.wikipedia.org/wiki/Propagation_of_uncertainty#Example_formulas, cause I always forget
//        float fracerrreco  = sfreco  > 0 ? errreco  / sfreco : 0;
//        float fracerrtight = sftight > 0 ? errtight / sftight : 0;
//        float fracerrWWW   = sfWWW   > 0 ? errWWW   / sfWWW   : 0;
//        float fracerrtotal = sqrt(pow(fracerrreco, 2) + pow(fracerrtight, 2) + pow(fracerrWWW, 2) + pow(0.01, 2)); // flat additional 1% uncertainty
//        float error        = fracerrtotal * sf;
//        // Return the value
//        return make_tuple(sf, error);
//    }
//}

//##############################################################################################################
std::tuple<float, float> babyMaker_v2::getlepSFandError(int index, int lepton_id_version)
{
    // Retrieve relevant variables
    const vector<int>&   lep_pdgId = tx->getBranch<vector<int>>  ("lep_pdgId");
    const vector<LV>&    lep_p4    = tx->getBranch<vector<LV>>   ("lep_p4");
    const vector<float>& lep_etaSC = tx->getBranch<vector<float>>("lep_etaSC");

    // If the provided index is out of bound return null
    if (index < 0) return make_tuple(1., 0.);
    if (index >= (int) lep_pdgId.size()) return make_tuple(1., 0.);

    // Warning message if the leptonid version is not 2
    if (abs(lepton_id_version) != 2)
        RooUtil::error("getlepSFandError: lepton_id_version != 2");

    // If electron
    if (abs(lep_pdgId[index]) == 11)
    {
        // Parametrized kinematic quantity for scale factors
        float pt = lep_p4[index].Pt();
        float eta = lep_etaSC[index];
        // Scale Factors
        float sfreco   = lepsf_elec_reco(pt, eta);
        float sfpogid  = lepton_id_version > 0 ? lepsf_elec_mva80 (pt, eta) : lepsf_elec_mva90 (pt, eta);
        float sfWWW    = lepton_id_version > 0 ? lepsf_elec_ss_id (pt, eta) : lepsf_elec_3l_id (pt, eta);
        float sfWWWIso = lepton_id_version > 0 ? lepsf_elec_ss_iso(pt, eta) : lepsf_elec_3l_iso(pt, eta);
        float sf       = sfreco * sfpogid * sfWWW * sfWWWIso;
        // Errors
        float errreco   = lepsf_elec_reco(pt, eta, 1) - sfreco;
        float errpogid  = (lepton_id_version > 0 ? lepsf_elec_mva80 (pt, eta, 1) : lepsf_elec_mva90 (pt, eta, 1)) - sfpogid;
        float errWWW    = (lepton_id_version > 0 ? lepsf_elec_ss_id (pt, eta, 1) : lepsf_elec_3l_id (pt, eta, 1)) - sfWWW; // difference against syst = +1 is the error
        float errWWWIso = (lepton_id_version > 0 ? lepsf_elec_ss_iso(pt, eta, 1) : lepsf_elec_3l_iso(pt, eta, 1)) - sfWWWIso; // difference against syst = +1 is the error 
        // Following the formula from https://en.wikipedia.org/wiki/Propagation_of_uncertainty#Example_formulas, cause I always forget
        float fracerrreco   = sfreco   > 0 ? errreco   / sfreco   : 0;
        float fracerrpogid  = sfpogid  > 0 ? errpogid  / sfpogid  : 0;
        float fracerrWWW    = sfWWW    > 0 ? errWWW    / sfWWW    : 0;
        float fracerrWWWIso = sfWWWIso > 0 ? errWWWIso / sfWWWIso : 0;
        float fracerrtotal  = sqrt(pow(fracerrreco, 2) + pow(fracerrpogid, 2) + pow(fracerrWWW, 2) + pow(fracerrWWWIso, 2));
        // Assume the "tight" and "WWW" error (which are MVA based for lepton_id_version >= 2) are 100% correlated
        if (lepton_id_version >= 2)
            fracerrtotal = sqrt(pow(fracerrreco, 2) + pow(fracerrpogid + fracerrWWW, 2) + pow(fracerrWWWIso, 2));
        float error         = fracerrtotal * sf;
        // Return the value
        return make_tuple(sf, error);
    }
    else  //muon
    {
        // Parametrized kinematic quantity for scale factors
        float pt = lep_p4[index].Pt();
        float eta = lep_p4[index].Eta();
        // Scale Factors
        float sftrk    = lepsf_muon_trk(pt, eta);
        float sfpogid  = lepsf_muon_id (pt, eta);
        float sfWWW    = lepton_id_version > 0 ? lepsf_muon_ss(pt, eta) : lepsf_muon_3l(pt, eta);
        float sf       = sftrk * sfpogid * sfWWW;
        // Errors
        // Recommendation from https://twiki.cern.ch/twiki/bin/view/CMS/MuonWorkInProgressAndPagResults and linked twiki
        // From the recommendations what we conclude is to add is a 1% additional uncertainty.
        float errtrk    = lepsf_muon_trk(pt, eta, 1) - sftrk;
        float errpogid  = lepsf_muon_id (pt, eta, 1) - sfpogid;
        float errWWW    = (lepton_id_version > 0 ? lepsf_muon_ss(pt, eta, 1) : lepsf_muon_3l(pt, eta, 1)) - sfWWW;
        // Following the formula from https://en.wikipedia.org/wiki/Propagation_of_uncertainty#Example_formulas, cause I always forget
        float fracerrtrk   = sftrk   > 0 ? errtrk   / sftrk   : 0;
        float fracerrpogid = sfpogid > 0 ? errpogid / sfpogid : 0;
        float fracerrWWW   = sfWWW   > 0 ? errWWW   / sfWWW   : 0;
        float fracerrtotal = sqrt(pow(fracerrtrk, 2) + pow(fracerrpogid, 2) + pow(fracerrWWW, 2) + pow(0.01, 2)); // flat additional 1% uncertainty
        float error        = fracerrtotal * sf;
        // Return the value
        return make_tuple(sf, error);
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
std::tuple<float, float> babyMaker_v2::getTrigEffandError(int lepton_id_version) // Deprecated
{
    return make_tuple(0.0, 0.0);
//    // Retrieve relevant variables
//    const vector<int>& lep_pdgId = tx->getBranch<vector<int>>("lep_pdgId");
//    const vector<LV>& lep_p4 = tx->getBranch<vector<LV>>("lep_p4");
//
//    // If less than two leptons (should never happen anyways)
//    // return dummy value
//    if (lep_pdgId.size() < 2)
//        return make_tuple(0.0, 0.0);
//
//    // Return values
//    float eff = 1.0;
//    float err = 0.0;
//
//    // even if there are more than 2 leptons apply to the first two only
//    float pt0 = lep_p4[0].pt();
//    float pt1 = lep_p4[1].pt();
//    float eta0 = lep_p4[0].eta();
//    float eta1 = lep_p4[1].eta();
//    float leadeta  = std::min(fabs(eta0), (float)2.39);
//    float traileta = std::min(fabs(eta1), (float)2.39);
//    float leadpt   = std::min(pt0, (float)499.);
//    float trailpt  = std::min(pt1, (float)499.);
//
//    float bigeta   = leadeta > traileta ? leadeta  : traileta;
//    float smalleta = leadeta > traileta ? traileta : leadeta;
//
//    // is ee events
//    if (abs(lep_pdgId[0]) == 11 && abs(lep_pdgId[1]) == 11)
//    {
//        // related to lepton legs
//        float e_l0 = trigeff_el_lead(leadeta, leadpt);
//        float e_t1 = trigeff_el_trail(traileta, trailpt);
//        float e_l1 = trigeff_el_lead(traileta, trailpt);
//        float e_t0 = trigeff_el_trail(leadeta, leadpt);
//        float d_l0 = trigeff_el_lead(leadeta, leadpt, 1) - trigeff_el_lead(leadeta, leadpt);
//        float d_t1 = trigeff_el_trail(traileta, trailpt, 1) - trigeff_el_trail(traileta, trailpt);
//        float d_l1 = trigeff_el_lead(traileta, trailpt, 1) - trigeff_el_lead(traileta, trailpt);
//        float d_t0 = trigeff_el_trail(leadeta, leadpt, 1) - trigeff_el_trail(leadeta, leadpt);
//        float tempeff = 1.0;
//        float temperr = 0.0;
//        std::tie(tempeff, temperr) = getCombinedTrigEffandError(e_l0, e_l1, e_t0, e_t1, d_l0, d_l1, d_t0, d_t1);
//        // dz
//        float dzeff = trigeff_diel_dz(smalleta, bigeta);
//        float dzerr = trigeff_diel_dz(smalleta, bigeta, 1) - trigeff_diel_dz(smalleta, bigeta, 1);
//        eff = tempeff * dzeff;
//        err = eff * sqrt(pow(temperr / tempeff, 2) + pow(dzerr / dzeff, 2));
//    }
//
//    // emu trigger's DZ filter was near 100% given statistics error also same-sign analysis observes the same.
//    // So apply only a flat err of 2%
//
//    // is em events
//    if (abs(lep_pdgId[0]) == 11 && abs(lep_pdgId[1]) == 13)
//    {
//        // related to lepton legs
//        float e_l0 = trigeff_el_lead(leadeta, leadpt);
//        float e_t1 = trigeff_mu_trail(traileta, trailpt);
//        float d_l0 = trigeff_el_lead(leadeta, leadpt, 1) - trigeff_el_lead(leadeta, leadpt);
//        float d_t1 = trigeff_mu_trail(traileta, trailpt, 1) - trigeff_mu_trail(traileta, trailpt);
//        float tempeff = 1.0;
//        float temperr = 0.0;
//        std::tie(tempeff, temperr) = getCombinedTrigEffandError(e_l0, 0., 0., e_t1, d_l0, 0., 0., d_t1);
//        // dz
//        float dzeff = 1.0;
//        float dzerr = 0.02;
//        eff = tempeff * dzeff;
//        err = eff * sqrt(pow(temperr / tempeff, 2) + pow(dzerr / dzeff, 2));
//    }
//
//    // is me events
//    if (abs(lep_pdgId[0]) == 13 && abs(lep_pdgId[1]) == 11)
//    {
//        // nominal
//        float e_l0 = trigeff_mu_lead(leadeta, leadpt);
//        float e_t1 = trigeff_el_trail(traileta, trailpt);
//        float d_l0 = trigeff_mu_lead(leadeta, leadpt, 1) - trigeff_mu_lead(leadeta, leadpt);
//        float d_t1 = trigeff_el_trail(traileta, trailpt, 1) - trigeff_el_trail(traileta, trailpt);
//        float tempeff = 1.0;
//        float temperr = 0.0;
//        std::tie(tempeff, temperr) = getCombinedTrigEffandError(e_l0, 0., 0., e_t1, d_l0, 0., 0., d_t1);
//        // dz
//        float dzeff = 1.0;
//        float dzerr = 0.02;
//        eff = tempeff * dzeff;
//        err = eff * sqrt(pow(temperr / tempeff, 2) + pow(dzerr / dzeff, 2));
//    }
//
//    // is mm events
//    if (abs(lep_pdgId[0]) == 13 && abs(lep_pdgId[1]) == 13)
//    {
//        // related to lepton legs
//        float e_l0 = trigeff_mu_lead(leadeta, leadpt);
//        float e_t1 = trigeff_mu_trail(traileta, trailpt);
//        float e_l1 = trigeff_mu_lead(traileta, trailpt);
//        float e_t0 = trigeff_mu_trail(leadeta, leadpt);
//        float d_l0 = trigeff_mu_lead(leadeta, leadpt, 1) - trigeff_mu_lead(leadeta, leadpt);
//        float d_t1 = trigeff_mu_trail(traileta, trailpt, 1) - trigeff_mu_trail(traileta, trailpt);
//        float d_l1 = trigeff_mu_lead(traileta, trailpt, 1) - trigeff_mu_lead(traileta, trailpt);
//        float d_t0 = trigeff_mu_trail(leadeta, leadpt, 1) - trigeff_mu_trail(leadeta, leadpt);
//        float tempeff = 1.0;
//        float temperr = 0.0;
//        std::tie(tempeff, temperr) = getCombinedTrigEffandError(e_l0, e_l1, e_t0, e_t1, d_l0, d_l1, d_t0, d_t1);
//        // dz
//        float dzeff = 0.241 * trigeff_dimu_dz(smalleta, bigeta) + (1 - 0.241) * 1; // Because DZ filter only affects Period H
//        float dzerr = 0.241 * (trigeff_dimu_dz(smalleta, bigeta, 1) - trigeff_dimu_dz(smalleta, bigeta));
//        eff = tempeff * dzeff;
//        err = eff * sqrt(pow(temperr / tempeff, 2) + pow(dzerr / dzeff, 2));
//        // And the fractino of period H is calculated from here: http://www.t2.ucsd.edu/tastwiki/bin/view/CMS/Run2_Data2016
//        // 8.636 + 0.221 / 36.814 = 0.241
//    }
//    
//    // Return result
//    return make_tuple(eff, err);
}

//##############################################################################################################
std::tuple<float, float> babyMaker_v2::getTrigSFandError(int lepton_id_version)
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
    float leadpt   = std::min(pt0, (float)199.);
    float trailpt  = std::min(pt1, (float)199.);

    float bigeta   = leadeta > traileta ? leadeta  : traileta;
    float smalleta = leadeta > traileta ? traileta : leadeta;

    // NOTE: "eff" variable names are really "efficiency scale factors"

    // is ee events
    if (abs(lep_pdgId[0]) == 11 && abs(lep_pdgId[1]) == 11)
    {
        // related to lepton legs
        float e_l0 = trigsf_el_lead(leadpt, leadeta);
        float e_t1 = trigsf_el_trail(trailpt, traileta);
        float d_l0 = trigsf_el_lead(leadpt, leadeta, 1) - trigsf_el_lead(leadpt, leadeta);
        float d_t1 = trigsf_el_trail(trailpt, traileta, 1) - trigsf_el_trail(trailpt, traileta);
        float tempeff = 1.0;
        float temperr = 0.0;
        std::tie(tempeff, temperr) = getCombinedTrigEffandError(e_l0, 0., 0., e_t1, d_l0, 0., 0., d_t1);
        // dz
        float dzeff = trigsf_diel_dz(smalleta, bigeta);
        float dzerr = trigsf_diel_dz(smalleta, bigeta, 1) - trigsf_diel_dz(smalleta, bigeta);
        eff = tempeff * dzeff;
        err = eff * sqrt(pow(temperr / tempeff, 2) + pow(dzerr / dzeff, 2));
    }

    // emu trigger's DZ filter was near 100% given statistics error also same-sign analysis observes the same.
    // So apply only a flat err of 2%

    // is em events
    if (abs(lep_pdgId[0]) == 11 && abs(lep_pdgId[1]) == 13)
    {
        // related to lepton legs
        float e_l0 = trigsf_el_lead(leadpt, leadeta);
        float e_t1 = trigsf_mu_trail(trailpt, traileta);
        float d_l0 = trigsf_el_lead(leadpt, leadeta, 1) - trigsf_el_lead(leadpt, leadeta);
        float d_t1 = trigsf_mu_trail(trailpt, traileta, 1) - trigsf_mu_trail(trailpt, traileta);
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
        float e_l0 = trigsf_mu_lead(leadpt, leadeta);
        float e_t1 = trigsf_el_trail(trailpt, traileta);
        float d_l0 = trigsf_mu_lead(leadpt, leadeta, 1) - trigsf_mu_lead(leadpt, leadeta);
        float d_t1 = trigsf_el_trail(trailpt, traileta, 1) - trigsf_el_trail(trailpt, traileta);
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
        float e_l0 = trigsf_mu_lead(leadpt, leadeta);
        float e_t1 = trigsf_mu_trail(trailpt, traileta);
        float d_l0 = trigsf_mu_lead(leadpt, leadeta, 1) - trigsf_mu_lead(leadpt, leadeta);
        float d_t1 = trigsf_mu_trail(trailpt, traileta, 1) - trigsf_mu_trail(trailpt, traileta);
        float tempeff = 1.0;
        float temperr = 0.0;
        std::tie(tempeff, temperr) = getCombinedTrigEffandError(e_l0, 0., 0., e_t1, d_l0, 0., 0., d_t1);
        // dz
        float dzeff = 0.241 * trigsf_dimu_dz(smalleta, bigeta) + (1 - 0.241) * 1; // Because DZ filter only affects Period H
        float dzerr = 0.241 * (trigsf_dimu_dz(smalleta, bigeta, 1) - trigsf_dimu_dz(smalleta, bigeta));
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

//##############################################################################################################
// FATAL error code
void babyMaker_v2::FATALERROR(const char* funcname)
{
    std::cout <<  " cms3.evt_run(): " << cms3.evt_run() <<  " cms3.evt_lumiBlock(): " << cms3.evt_lumiBlock() <<  " cms3.evt_event(): " << cms3.evt_event() <<  std::endl;
    cout << "FATAL ERROR: I Should never be here! In function : " << funcname << endl;
}

//eof
