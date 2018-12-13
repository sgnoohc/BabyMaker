#include "babyMaker.h"
#include "puWeight.h"

using namespace std;

//##############################################################################################################
babyMaker::babyMaker() : coreBtagSFFastSim(true), babymode(kHWWBaby)
{
}

//##############################################################################################################
babyMaker::~babyMaker()
{
}

//##############################################################################################################
int babyMaker::ProcessCMS4(TString filepaths, int max_events, int idx, bool verbose)
{
    // Create TChain to process
    TChain* chain = RooUtil::FileUtil::createTChain("Events", filepaths);

    // Initialize Looper
    looper.init(chain, &cms3, max_events);

    // Initialize Looper
    looper.setNbadEventThreshold(0);

    // Initializer job index
    job_index = idx;

    // Run the loop
    ScanChain(verbose);

    // Exit
    return 0;
}

//##############################################################################################################
std::once_flag flag_init; // a flag for std::call_once
void babyMaker::ScanChain(bool verbose)
{
    while (looper.nextEvent())
    {
        try
        {
            if (verbose)
                cout << "[verbose] Processed " << looper.getNEventsProcessed() << " out of " << looper.getTChain()->GetEntries() << endl;

            // Some of the sample specific things need to be set prior to processing the very first event
            // Those are called inside Init, they have explicit "call_once" feature
            // The reason this is inside the loop is because it first need to access the file name before
            std::call_once(flag_init, &babyMaker::Init, this);

            // Now process the baby ntuples
            Process();

        }
        catch (const std::ios_base::failure& e)
        {
            if (coreSample.is2016Data(looper.getCurrentFileName()) || coreSample.is2017Data(looper.getCurrentFileName()))
            {
                std::cout << "Found bad event in data" << std::endl;
                FATALERROR(__FUNCTION__);
                exit(2);
            }
            tx->clear(); // clear the TTree of any residual stuff
            if (!looper.handleBadEvent())
                break;
        }
    }

    looper.printStatus();

    if (looper.getNEventsProcessed() == 0)
    {
        CreateOutput();
    }

    SaveOutput();
}

//##############################################################################################################
void babyMaker::Init()
{
    // Set year via "GlobalConfig gconf"
    SetYear();

    // Provide which file it is and whether it is fast sim or not to JEC to determine which file to load
    coreJec.setJECFor(looper.getCurrentFileName(), isFastSim());

    // Output root file
    CreateOutput();

    // Signal or BSM samples need some specifics things to be set prior to starting the processing
    AddOutput();

    // Set lepton ID configuration via "GlobalConfig gconf"
    SetLeptonID();
}

//##############################################################################################################
void babyMaker::SetYear()
{
    TString filename = looper.getCurrentFileName();
    if (
            filename.Contains("Run2016")
            || filename.Contains("Moriond17")
            || filename.Contains("RunIISummer16")
            || filename.Contains("run2_data2016")
            || filename.Contains("run2_moriond17")
       ) gconf.year = 2016;
    if (
            filename.Contains("Run2017")
            || filename.Contains("RunIIFall17")
            || filename.Contains("_mc2017_")
            || filename.Contains("run2_mc2017")
       ) gconf.year = 2017;
    if (
            filename.Contains("Run2018")
            || filename.Contains("RunIISpring18")
            || filename.Contains("RunIISummer18")
            || filename.Contains("run2_mc2018")
       ) gconf.year = 2018;
}

//##############################################################################################################
void babyMaker::CreateOutput()
{
    ofile = new TFile(Form("output_%d.root", job_index), "recreate");
    t = new TTree("t", "All events");
    tx = new RooUtil::TTreeX(t);

    h_neventsinfile = new TH1F("h_neventsinfile", "", 15, 0, 15);
    h_neventsinfile->SetBinContent(0, looper.getTChain()->GetEntries()); // this is the bin with value = -1 underflow
}

//##############################################################################################################
void babyMaker::AddOutput()
{
    // The main branches are created
    AddBabyOutput();
}

//##############################################################################################################
void babyMaker::AddBabyOutput()
{
    // Based on the baby mode now preselect and if it doesn't pass return
    switch (babymode)
    {
        case kHWWBaby: AddHWWBabyOutput(); return; break;
        default: return;
    }
}

//##############################################################################################################
void babyMaker::AddHWWBabyOutput()
{
    AddEventInfoOutput();

    AddLeptonOutput();

    AddJetOutput();

    AddMETOutput();

    AddGenVariablesOutput();

    AddGenRecoMatchingOutput();

    AddHiggsMassRecoOutput();

    AddRecoISROutput();

    AddRecoLeptonOutput();

    AddRecoWhadOutput();

    AddRecoWlepOutput();

    AddRecoLeadJetOutput();

    AddRecoVariablesOutput();

    AddHiggsTruthStudyOutput();

    AddEtaPhiPlaneVariablesOutput();

    AddDeepIsoVariablesOutput();

    AddIsolatedSingleLeptonTriggerOutput();

    AddHighPtSingleLeptonTriggerOutput();

    AddOverlapRemovedBvetoOutput();

    tx->clear();
}

//##############################################################################################################
void babyMaker::AddEventInfoOutput()
{
    tx->createBranch<Int_t>("run");
    tx->createBranch<Int_t>("lumi");
    tx->createBranch<unsigned long long>("evt");
    tx->createBranch<int>("isData");
    tx->createBranch<float>("evt_scale1fb");
    tx->createBranch<float>("genps_weight");
    tx->createBranch<float>("xsec_br");
    tx->createBranch<int>("evt_passgoodrunlist");
    tx->createBranch<TString>("CMS4path");
    tx->createBranch<int>("CMS4index");

    // Below are things related to event weights which must be done before skipping events
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
    tx->createBranch<float>("weight_isr");
    tx->createBranch<float>("weight_isr_up");
    tx->createBranch<float>("weight_isr_down");
}

//##############################################################################################################
void babyMaker::AddIsolatedSingleLeptonTriggerOutput()
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
}

//##############################################################################################################
void babyMaker::AddHighPtSingleLeptonTriggerOutput()
{
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
    tx->createBranch<int>("pass_duplicate_se_sm");
    tx->createBranch<int>("pass_duplicate_sm_se");
}

//##############################################################################################################
void babyMaker::AddLeptonOutput()
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
    tx->createBranch<vector<float>>("lep_customrelIso005EA");
    tx->createBranch<vector<float>>("lep_customrelIso01EA");
    tx->createBranch<vector<float>>("lep_customrelIso015EA");
    tx->createBranch<vector<float>>("lep_customrelIso02EA");
    tx->createBranch<vector<float>>("lep_customrelIso025EA");
    tx->createBranch<vector<float>>("lep_customrelIso03EA");
    tx->createBranch<vector<float>>("lep_customrelIso035EA");
    tx->createBranch<vector<float>>("lep_customrelIso04EA");
    tx->createBranch<vector<float>>("lep_customrelIso045EA");
    tx->createBranch<vector<float>>("lep_customrelIso05EA");
    tx->createBranch<vector<float>>("lep_customrelIso055EA");
    tx->createBranch<vector<float>>("lep_customrelIso06EA");
    tx->createBranch<vector<float>>("lep_customrelIso065EA");
    tx->createBranch<vector<float>>("lep_customrelIso07EA");
    tx->createBranch<vector<float>>("lep_customrelIso075EA");
    tx->createBranch<vector<float>>("lep_customrelIso08EA");
    tx->createBranch<int>("nrecolep");

    tx->createFlatBranch(
            {
            "lep_p4",
            },
            {
            "lep_pt",
            "lep_eta",
            "lep_phi",
            "lep_miniIsoEA",
            "lep_relIso03EA",
            "lep_relIso04DB",
            },
            {
            "lep_id",
            "lep_idx",
            },
            {},
            3);

}

//##############################################################################################################
void babyMaker::AddJetOutput()
{
    tx->createBranch<int>("nj");
    tx->createBranch<int>("nb");
    tx->createBranch<int>("nbmed");
    tx->createBranch<int>("nbtight");
    tx->createBranch<int>("nj50");
    tx->createBranch<int>("nb50");
    tx->createBranch<int>("nb50med");
    tx->createBranch<int>("nb50tight");
    tx->createBranch<int>("nb30");
    tx->createBranch<int>("nb30med");
    tx->createBranch<int>("nb30tight");
    tx->createBranch<int>("nb40");
    tx->createBranch<int>("nb40med");
    tx->createBranch<int>("nb40tight");
    tx->createBranch<float>("ht");
    tx->createBranch<float>("ht40");
    tx->createBranch<float>("ht50");
    tx->createBranch<float>("mh");
    tx->createBranch<float>("mh40");
    tx->createBranch<float>("mh50");
    tx->createBranch<vector<LV>>("alljets_p4");
    tx->createBranch<vector<float>>("alljets_pt");
    tx->createBranch<vector<float>>("alljets_eta");
    tx->createBranch<vector<float>>("alljets_phi");
    tx->createBranch<vector<float>>("alljets_csv");
    tx->createBranch<vector<LV>>("jets_p4");
    tx->createBranch<vector<float>>("jets_pt");
    tx->createBranch<vector<float>>("jets_eta");
    tx->createBranch<vector<float>>("jets_phi");
    tx->createBranch<vector<float>>("jets_csv");
    tx->createBranch<vector<LV>>("jets_up_p4");
    tx->createBranch<vector<float>>("jets_up_pt");
    tx->createBranch<vector<float>>("jets_up_eta");
    tx->createBranch<vector<float>>("jets_up_phi");
    tx->createBranch<vector<float>>("jets_up_csv");
    tx->createBranch<vector<LV>>("jets_dn_p4");
    tx->createBranch<vector<float>>("jets_dn_pt");
    tx->createBranch<vector<float>>("jets_dn_eta");
    tx->createBranch<vector<float>>("jets_dn_phi");
    tx->createBranch<vector<float>>("jets_dn_csv");

    tx->createBranch<int>("nak8jets");
    tx->createBranch<vector<LV>>("ak8jets_p4");
    tx->createBranch<vector<float>>("ak8jets_pt");
    tx->createBranch<vector<float>>("ak8jets_eta");
    tx->createBranch<vector<float>>("ak8jets_phi");
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

    tx->createFlatBranch(
            {
            "jets_p4",
            "jets_up_p4",
            "jets_dn_p4",
            "ak8jets_p4"
            },
            {
            "jets_pt",
            "jets_eta",
            "jets_phi",
            "jets_csv",
            "jets_up_pt",
            "jets_up_eta",
            "jets_up_phi",
            "jets_up_csv",
            "jets_dn_pt",
            "jets_dn_eta",
            "jets_dn_phi",
            "jets_dn_csv",
            "ak8jets_pt",
            "ak8jets_eta",
            "ak8jets_phi",
            "ak8jets_softdropMass",
            "ak8jets_prunedMass",
            "ak8jets_trimmedMass",
            "ak8jets_mass",
            "ak8jets_nJettinessTau1",
            "ak8jets_nJettinessTau2",
            "ak8jets_softdropPuppiSubjet1",
            "ak8jets_softdropPuppiSubjet2",
            "ak8jets_puppi_softdropMass",
            "ak8jets_puppi_nJettinessTau1",
            "ak8jets_puppi_nJettinessTau2",
            "ak8jets_puppi_eta",
            "ak8jets_puppi_phi",
            "ak8jets_puppi_pt",
            "ak8jets_puppi_mass",
            },
            {},
            {},
            3);

    tx->createBranch<float>("weight_btagsf"         );
    tx->createBranch<float>("weight_btagsf_heavy_DN");
    tx->createBranch<float>("weight_btagsf_heavy_UP");
    tx->createBranch<float>("weight_btagsf_light_DN");
    tx->createBranch<float>("weight_btagsf_light_UP");
}

//##############################################################################################################
void babyMaker::AddOverlapRemovedBvetoOutput()
{
    tx->createBranch<int>("nbOR");
    tx->createBranch<int>("nbORmed");
    tx->createBranch<int>("nbORtight");
    tx->createBranch<int>("nbOR30");
    tx->createBranch<int>("nbOR30med");
    tx->createBranch<int>("nbOR30tight");
    tx->createBranch<int>("nbOR40");
    tx->createBranch<int>("nbOR40med");
    tx->createBranch<int>("nbOR40tight");
    tx->createBranch<int>("nbOR50");
    tx->createBranch<int>("nbOR50med");
    tx->createBranch<int>("nbOR50tight");
    tx->createBranch<float>("htOR");
    tx->createBranch<float>("htOR40");
    tx->createBranch<float>("htOR50");
    tx->createBranch<float>("mhOR");
    tx->createBranch<float>("mhOR40");
    tx->createBranch<float>("mhOR50");
}

//##############################################################################################################
void babyMaker::AddMETOutput()
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

//##############################################################################################################
void babyMaker::AddGenVariablesOutput()
{
    tx->createBranch<float>("gen_ht");
}

//##############################################################################################################
void babyMaker::AddGenRecoMatchingOutput()
{
    tx->createBranch<float>("isr_leadjet_dr");
    tx->createBranch<float>("higgs_met_dphi");
    tx->createBranch<float>("isr_recoisr_dr");
    tx->createBranch<float>("isr_recoisrmegajet_dr");
    tx->createBranch<float>("lepton_met_dphi");
    tx->createBranch<float>("quark0_met_dphi");
    tx->createBranch<float>("quark1_met_dphi");
    tx->createBranch<float>("wlep_met_dphi");
    tx->createBranch<float>("whad_met_dphi");
    tx->createBranch<float>("whad_recowhad_dr");
    tx->createBranch<float>("whad_recowhad_dphi");
    tx->createBranch<float>("whad_recowhad_deta");
    tx->createBranch<float>("whad_recowhad_ptratio");
    tx->createBranch<float>("higgs_recowhad_dr");
    tx->createBranch<float>("higgs_recowhad_dphi");
    tx->createBranch<float>("higgs_recowhad_deta");
    tx->createBranch<float>("higgs_recowhad_ptratio");
    tx->createBranch<float>("whad_leadak8_dr");
    tx->createBranch<float>("whad_leadak8_dphi");
    tx->createBranch<float>("whad_leadak8_deta");
    tx->createBranch<float>("whad_leadak8_ptratio");
    tx->createBranch<float>("higgs_leadak8_dr");
    tx->createBranch<float>("higgs_leadak8_dphi");
    tx->createBranch<float>("higgs_leadak8_deta");
    tx->createBranch<float>("higgs_leadak8_ptratio");
    tx->createBranch<float>("lepton_recolep_dr");
    tx->createBranch<float>("lepton_recolep_deta");
    tx->createBranch<float>("lepton_recolep_dphi");
    tx->createBranch<float>("lepton_recolep_ptratio");
    tx->createBranch<float>("neutrino_reconeutrino_dr");
    tx->createBranch<float>("neutrino_reconeutrino_deta");
    tx->createBranch<float>("neutrino_reconeutrino_dphi");
    tx->createBranch<float>("neutrino_reconeutrino_dpz");
    tx->createBranch<float>("neutrino_reconeutrino_dabspz");
    tx->createBranch<float>("neutrino_reconeutrino_ptratio");
}

//##############################################################################################################
void babyMaker::AddHiggsMassRecoOutput()
{
    tx->createBranch<LV>("recohiggs_p4");
    tx->createBranch<float>("recohiggs_pt");
    tx->createBranch<float>("recohiggs_eta");
    tx->createBranch<float>("recohiggs_phi");
    tx->createBranch<float>("recohiggs_mass");
    tx->createBranch<float>("recohiggs_mt");
    tx->createBranch<LV>("recohiggs2_p4");
    tx->createBranch<float>("recohiggs2_pt");
    tx->createBranch<float>("recohiggs2_eta");
    tx->createBranch<float>("recohiggs2_phi");
    tx->createBranch<float>("recohiggs2_mass");
    tx->createBranch<float>("recohiggs2_mt");
    tx->createBranch<LV>("recohiggsinv_p4");
    tx->createBranch<float>("recohiggsinv_pt");
    tx->createBranch<float>("recohiggsinv_eta");
    tx->createBranch<float>("recohiggsinv_phi");
    tx->createBranch<float>("recohiggsinv_mass");
    tx->createBranch<float>("recohiggsinv_mt");
    tx->createBranch<LV>("recohiggsmin_p4");
    tx->createBranch<float>("recohiggsmin_pt");
    tx->createBranch<float>("recohiggsmin_eta");
    tx->createBranch<float>("recohiggsmin_phi");
    tx->createBranch<float>("recohiggsmin_mass");
    tx->createBranch<float>("recohiggsmin_mt");
    tx->createBranch<LV>("recohiggsmin12_p4");
    tx->createBranch<float>("recohiggsmin12_pt");
    tx->createBranch<float>("recohiggsmin12_eta");
    tx->createBranch<float>("recohiggsmin12_phi");
    tx->createBranch<float>("recohiggsmin12_mass");
    tx->createBranch<float>("recohiggsmin12_mt");
}

//##############################################################################################################
void babyMaker::AddRecoISROutput()
{
    tx->createBranch<LV>("recoisr_p4");
    tx->createBranch<float>("recoisr_pt");
    tx->createBranch<float>("recoisr_eta");
    tx->createBranch<float>("recoisr_phi");
    tx->createBranch<LV>("recoisrmegajet_p4");
    tx->createBranch<float>("recoisrmegajet_pt");
    tx->createBranch<float>("recoisrmegajet_eta");
    tx->createBranch<float>("recoisrmegajet_phi");
    tx->createBranch<LV>("recoisrmegajet_n2_p4");
    tx->createBranch<float>("recoisrmegajet_n2_pt");
    tx->createBranch<float>("recoisrmegajet_n2_eta");
    tx->createBranch<float>("recoisrmegajet_n2_phi");
}

//##############################################################################################################
void babyMaker::AddRecoWhadOutput()
{
    tx->createBranch<LV>("recowhad_p4");
    tx->createBranch<float>("recowhad_pt");
    tx->createBranch<float>("recowhad_eta");
    tx->createBranch<float>("recowhad_phi");
    tx->createBranch<float>("recowhad_mass");
    tx->createBranch<float>("recowhad_softdropMass");
    tx->createBranch<float>("recowhad_prunedMass");
    tx->createBranch<float>("recowhad_nJettinessTau1");
    tx->createBranch<float>("recowhad_nJettinessTau2");
    tx->createBranch<float>("recowhad_puppi_softdropMass");
    tx->createBranch<float>("recowhad_puppi_pt");
    tx->createBranch<float>("recowhad_puppi_eta");
    tx->createBranch<float>("recowhad_puppi_phi");
    tx->createBranch<float>("recowhad_puppi_mass");
    tx->createBranch<float>("recowhad_puppi_nJettinessTau1");
    tx->createBranch<float>("recowhad_puppi_nJettinessTau2");
    tx->createBranch<float>("recowhad_softdropPuppiSubjet1");
    tx->createBranch<float>("recowhad_softdropPuppiSubjet2");
}

//##############################################################################################################
void babyMaker::AddRecoWlepOutput()
{
    tx->createBranch<LV>("recowlep_p4");
    tx->createBranch<float>("recowlep_pt");
    tx->createBranch<float>("recowlep_eta");
    tx->createBranch<float>("recowlep_phi");
    tx->createBranch<float>("recowlep_mass");
}

//##############################################################################################################
void babyMaker::AddRecoLeadJetOutput()
{
    tx->createBranch<LV>("recoleadjet_p4");
    tx->createBranch<float>("recoleadjet_pt");
    tx->createBranch<float>("recoleadjet_eta");
    tx->createBranch<float>("recoleadjet_phi");
}

//##############################################################################################################
void babyMaker::AddRecoLeptonOutput()
{
    tx->createBranch<LV>("recolepton_p4");
    tx->createBranch<int>("recolepton_id");
    tx->createBranch<float>("recolepton_pt");
    tx->createBranch<float>("recolepton_eta");
    tx->createBranch<float>("recolepton_phi");
    tx->createBranch<float>("recolepton_mt");
    tx->createBranch<float>("recolepton_met_dphi");
    tx->createBranch<int>("recoiswleplead");
    tx->createBranch<float>("reconeutrino_det");
    tx->createBranch<LV>("reconeutrino_p4");
    tx->createBranch<float>("reconeutrino_pt");
    tx->createBranch<float>("reconeutrino_eta");
    tx->createBranch<float>("reconeutrino_phi");
    tx->createBranch<float>("reconeutrino_met_dphi");
    tx->createBranch<LV>("reconeutrino2_p4");
    tx->createBranch<float>("reconeutrino2_pt");
    tx->createBranch<float>("reconeutrino2_eta");
    tx->createBranch<float>("reconeutrino2_phi");
    tx->createBranch<float>("reconeutrino2_met_dphi");
    tx->createBranch<LV>("reconeutrinoinv_p4");
    tx->createBranch<float>("reconeutrinoinv_pt");
    tx->createBranch<float>("reconeutrinoinv_eta");
    tx->createBranch<float>("reconeutrinoinv_phi");
    tx->createBranch<float>("reconeutrinoinv_met_dphi");
}

//##############################################################################################################
void babyMaker::AddRecoVariablesOutput()
{
    tx->createBranch<float>("recolepton_recowhad_dr");
    tx->createBranch<float>("recoleadjet_recolepton_dr");
    tx->createBranch<float>("recoleadjet_met_dphi");
    tx->createBranch<float>("recoleadjet_recowhad_dr");
    tx->createBranch<LV>("recowhad_minus_recolepton_p4");
    tx->createBranch<float>("recowhad_minus_recolepton_pt");
    tx->createBranch<float>("recowhad_minus_recolepton_eta");
    tx->createBranch<float>("recowhad_minus_recolepton_phi");
    tx->createBranch<float>("recowhad_minus_recolepton_mass");
    tx->createBranch<LV>("recowhad_minus_recolepton_positive_p4");
    tx->createBranch<float>("recowhad_minus_recolepton_positive_pt");
    tx->createBranch<float>("recowhad_minus_recolepton_positive_eta");
    tx->createBranch<float>("recowhad_minus_recolepton_positive_phi");
    tx->createBranch<float>("recowhad_minus_recolepton_positive_mass");
}

//##############################################################################################################
void babyMaker::AddHiggsTruthStudyOutput()
{
    tx->createBranch<int>("higgsdecay");
    tx->createBranch<int>("wstar_channel_id");
    tx->createBranch<int>("nlep");
    tx->createBranch<int>("nquark");
    tx->createBranch<int>("wa_id");
    tx->createBranch<LV>("isr_p4");
    tx->createBranch<float>("isr_pt");
    tx->createBranch<float>("isr_eta");
    tx->createBranch<float>("isr_phi");
    tx->createBranch<LV>("higgs_p4");
    tx->createBranch<vector<LV>>("decay_p4");
    tx->createBranch<vector<int>>("decay_id");
    tx->createBranch<vector<int>>("decay_isstar");
    tx->createBranch<vector<LV>>("lepton_p4");
    tx->createBranch<vector<int>>("lepton_id");
    tx->createBranch<vector<int>>("lepton_isstar");
    tx->createBranch<vector<LV>>("neutrino_p4");
    tx->createBranch<vector<int>>("neutrino_id");
    tx->createBranch<vector<int>>("neutrino_isstar");
    tx->createBranch<vector<LV>>("quark_p4");
    tx->createBranch<vector<int>>("quark_id");
    tx->createBranch<vector<int>>("quark_isstar");
    tx->createBranch<float>("lqq_max_dr");
    tx->createBranch<float>("lq0_dr");
    tx->createBranch<float>("lq1_dr");
    tx->createBranch<float>("qq_dr");
    tx->createBranch<float>("decay_dr");
    tx->createBranch<float>("l_qq_dr");
    tx->createBranch<float>("lqq_mass");
    tx->createBranch<float>("lvqq_mt");

//    tx->createBranch<vector<LV>>("boosted0_decay_p4");
//    tx->createBranch<vector<int>>("boosted0_decay_id");
//    tx->createBranch<vector<int>>("boosted0_decay_isstar");
//    tx->createBranch<vector<float>>("boosted0_decay_h_dr");
//    tx->createBranch<vector<float>>("boosted0_decay_h_deta");
//    tx->createBranch<vector<float>>("boosted0_decay_h_dphi");
//    tx->createBranch<vector<float>>("boosted0_decay_h_deta_rotated");
//    tx->createBranch<vector<float>>("boosted0_decay_h_dphi_rotated");
//
//    tx->createBranch<vector<LV>>("boosted0_lepton_p4");
//    tx->createBranch<vector<int>>("boosted0_lepton_id");
//    tx->createBranch<vector<int>>("boosted0_lepton_isstar");
//    tx->createBranch<vector<float>>("boosted0_lepton_h_dr");
//    tx->createBranch<vector<float>>("boosted0_lepton_h_deta");
//    tx->createBranch<vector<float>>("boosted0_lepton_h_dphi");
//    tx->createBranch<vector<float>>("boosted0_lepton_h_deta_rotated");
//    tx->createBranch<vector<float>>("boosted0_lepton_h_dphi_rotated");
//
//    tx->createBranch<vector<LV>>("boosted0_quark_p4");
//    tx->createBranch<vector<int>>("boosted0_quark_id");
//    tx->createBranch<vector<int>>("boosted0_quark_isstar");
//    tx->createBranch<vector<float>>("boosted0_quark_h_dr");
//    tx->createBranch<vector<float>>("boosted0_quark_h_deta");
//    tx->createBranch<vector<float>>("boosted0_quark_h_dphi");
//    tx->createBranch<vector<float>>("boosted0_quark_h_deta_rotated");
//    tx->createBranch<vector<float>>("boosted0_quark_h_dphi_rotated");
//
//    tx->createBranch<vector<LV>>("boosted250_decay_p4");
//    tx->createBranch<vector<int>>("boosted250_decay_id");
//    tx->createBranch<vector<int>>("boosted250_decay_isstar");
//    tx->createBranch<vector<float>>("boosted250_decay_h_dr");
//    tx->createBranch<vector<float>>("boosted250_decay_h_deta");
//    tx->createBranch<vector<float>>("boosted250_decay_h_dphi");
//    tx->createBranch<vector<float>>("boosted250_decay_h_deta_rotated");
//    tx->createBranch<vector<float>>("boosted250_decay_h_dphi_rotated");
//
//    tx->createBranch<vector<LV>>("boosted250_lepton_p4");
//    tx->createBranch<vector<int>>("boosted250_lepton_id");
//    tx->createBranch<vector<int>>("boosted250_lepton_isstar");
//    tx->createBranch<vector<float>>("boosted250_lepton_h_dr");
//    tx->createBranch<vector<float>>("boosted250_lepton_h_deta");
//    tx->createBranch<vector<float>>("boosted250_lepton_h_dphi");
//    tx->createBranch<vector<float>>("boosted250_lepton_h_deta_rotated");
//    tx->createBranch<vector<float>>("boosted250_lepton_h_dphi_rotated");
//
//    tx->createBranch<vector<LV>>("boosted250_quark_p4");
//    tx->createBranch<vector<int>>("boosted250_quark_id");
//    tx->createBranch<vector<int>>("boosted250_quark_isstar");
//    tx->createBranch<vector<float>>("boosted250_quark_h_dr");
//    tx->createBranch<vector<float>>("boosted250_quark_h_deta");
//    tx->createBranch<vector<float>>("boosted250_quark_h_dphi");
//    tx->createBranch<vector<float>>("boosted250_quark_h_deta_rotated");
//    tx->createBranch<vector<float>>("boosted250_quark_h_dphi_rotated");
//
//    tx->createBranch<float>("boosted250_lqq_max_dr");
//    tx->createBranch<float>("boosted250_lq0_dr");
//    tx->createBranch<float>("boosted250_lq1_dr");
//    tx->createBranch<float>("boosted250_qq_dr");
//
//    tx->createBranch<vector<LV>>("boosted500_decay_p4");
//    tx->createBranch<vector<int>>("boosted500_decay_id");
//    tx->createBranch<vector<int>>("boosted500_decay_isstar");
//    tx->createBranch<vector<float>>("boosted500_decay_h_dr");
//    tx->createBranch<vector<float>>("boosted500_decay_h_deta");
//    tx->createBranch<vector<float>>("boosted500_decay_h_dphi");
//    tx->createBranch<vector<float>>("boosted500_decay_h_deta_rotated");
//    tx->createBranch<vector<float>>("boosted500_decay_h_dphi_rotated");
//
//    tx->createBranch<vector<LV>>("boosted500_lepton_p4");
//    tx->createBranch<vector<int>>("boosted500_lepton_id");
//    tx->createBranch<vector<int>>("boosted500_lepton_isstar");
//    tx->createBranch<vector<float>>("boosted500_lepton_h_dr");
//    tx->createBranch<vector<float>>("boosted500_lepton_h_deta");
//    tx->createBranch<vector<float>>("boosted500_lepton_h_dphi");
//    tx->createBranch<vector<float>>("boosted500_lepton_h_deta_rotated");
//    tx->createBranch<vector<float>>("boosted500_lepton_h_dphi_rotated");
//
//    tx->createBranch<vector<LV>>("boosted500_quark_p4");
//    tx->createBranch<vector<int>>("boosted500_quark_id");
//    tx->createBranch<vector<int>>("boosted500_quark_isstar");
//    tx->createBranch<vector<float>>("boosted500_quark_h_dr");
//    tx->createBranch<vector<float>>("boosted500_quark_h_deta");
//    tx->createBranch<vector<float>>("boosted500_quark_h_dphi");
//    tx->createBranch<vector<float>>("boosted500_quark_h_deta_rotated");
//    tx->createBranch<vector<float>>("boosted500_quark_h_dphi_rotated");
//
//    tx->createBranch<float>("boosted500_lqq_max_dr");
//    tx->createBranch<float>("boosted500_lq0_dr");
//    tx->createBranch<float>("boosted500_lq1_dr");
//    tx->createBranch<float>("boosted500_qq_dr");
//
//    tx->createBranch<vector<LV>>("boosted1000_decay_p4");
//    tx->createBranch<vector<int>>("boosted1000_decay_id");
//    tx->createBranch<vector<int>>("boosted1000_decay_isstar");
//    tx->createBranch<vector<float>>("boosted1000_decay_h_dr");
//    tx->createBranch<vector<float>>("boosted1000_decay_h_deta");
//    tx->createBranch<vector<float>>("boosted1000_decay_h_dphi");
//    tx->createBranch<vector<float>>("boosted1000_decay_h_deta_rotated");
//    tx->createBranch<vector<float>>("boosted1000_decay_h_dphi_rotated");
//
//    tx->createBranch<vector<LV>>("boosted1000_lepton_p4");
//    tx->createBranch<vector<int>>("boosted1000_lepton_id");
//    tx->createBranch<vector<int>>("boosted1000_lepton_isstar");
//    tx->createBranch<vector<float>>("boosted1000_lepton_h_dr");
//    tx->createBranch<vector<float>>("boosted1000_lepton_h_deta");
//    tx->createBranch<vector<float>>("boosted1000_lepton_h_dphi");
//    tx->createBranch<vector<float>>("boosted1000_lepton_h_deta_rotated");
//    tx->createBranch<vector<float>>("boosted1000_lepton_h_dphi_rotated");
//
//    tx->createBranch<vector<LV>>("boosted1000_quark_p4");
//    tx->createBranch<vector<int>>("boosted1000_quark_id");
//    tx->createBranch<vector<int>>("boosted1000_quark_isstar");
//    tx->createBranch<vector<float>>("boosted1000_quark_h_dr");
//    tx->createBranch<vector<float>>("boosted1000_quark_h_deta");
//    tx->createBranch<vector<float>>("boosted1000_quark_h_dphi");
//    tx->createBranch<vector<float>>("boosted1000_quark_h_deta_rotated");
//    tx->createBranch<vector<float>>("boosted1000_quark_h_dphi_rotated");
//
//    tx->createBranch<float>("boosted1000_lqq_max_dr");
//    tx->createBranch<float>("boosted1000_lq0_dr");
//    tx->createBranch<float>("boosted1000_lq1_dr");
//    tx->createBranch<float>("boosted1000_qq_dr");
//
//    tx->createBranch<vector<LV>>("boosted1500_decay_p4");
//    tx->createBranch<vector<int>>("boosted1500_decay_id");
//    tx->createBranch<vector<int>>("boosted1500_decay_isstar");
//    tx->createBranch<vector<float>>("boosted1500_decay_h_dr");
//    tx->createBranch<vector<float>>("boosted1500_decay_h_deta");
//    tx->createBranch<vector<float>>("boosted1500_decay_h_dphi");
//    tx->createBranch<vector<float>>("boosted1500_decay_h_deta_rotated");
//    tx->createBranch<vector<float>>("boosted1500_decay_h_dphi_rotated");
//
//    tx->createBranch<vector<LV>>("boosted1500_lepton_p4");
//    tx->createBranch<vector<int>>("boosted1500_lepton_id");
//    tx->createBranch<vector<int>>("boosted1500_lepton_isstar");
//    tx->createBranch<vector<float>>("boosted1500_lepton_h_dr");
//    tx->createBranch<vector<float>>("boosted1500_lepton_h_deta");
//    tx->createBranch<vector<float>>("boosted1500_lepton_h_dphi");
//    tx->createBranch<vector<float>>("boosted1500_lepton_h_deta_rotated");
//    tx->createBranch<vector<float>>("boosted1500_lepton_h_dphi_rotated");
//
//    tx->createBranch<vector<LV>>("boosted1500_quark_p4");
//    tx->createBranch<vector<int>>("boosted1500_quark_id");
//    tx->createBranch<vector<int>>("boosted1500_quark_isstar");
//    tx->createBranch<vector<float>>("boosted1500_quark_h_dr");
//    tx->createBranch<vector<float>>("boosted1500_quark_h_deta");
//    tx->createBranch<vector<float>>("boosted1500_quark_h_dphi");
//    tx->createBranch<vector<float>>("boosted1500_quark_h_deta_rotated");
//    tx->createBranch<vector<float>>("boosted1500_quark_h_dphi_rotated");
//
//    tx->createBranch<float>("boosted1500_lqq_max_dr");
//    tx->createBranch<float>("boosted1500_lq0_dr");
//    tx->createBranch<float>("boosted1500_lq1_dr");
//    tx->createBranch<float>("boosted1500_qq_dr");

    tx->clear();

}

//##############################################################################################################
void babyMaker::AddEtaPhiPlaneVariablesOutput()
{
    tx->createBranch<float>("inneriso");
    tx->createBranch<vector<LV>>("pf_p4s");
    tx->createBranch<vector<float>>("pf_drs");
    tx->createBranch<float>("sumpt_oppo_r15");
    tx->createBranch<int>("njet5_oppo_r15");
    tx->createBranch<int>("njet10_oppo_r15");
    tx->createBranch<int>("njet20_oppo_r15");
    tx->createBranch<int>("njet30_oppo_r15");
    tx->createBranch<int>("njet50_oppo_r15");
    tx->createBranch<float>("sumpt_oppo");
    tx->createBranch<int>("njet5_oppo");
    tx->createBranch<int>("njet10_oppo");
    tx->createBranch<int>("njet20_oppo");
    tx->createBranch<int>("njet30_oppo");
    tx->createBranch<int>("njet50_oppo");
    tx->createBranch<float>("sumpt_in_fatjet");
    tx->createBranch<int>("njet5_in_fatjet");
}

//##############################################################################################################
void babyMaker::AddDeepIsoVariablesOutput()
{
    tx->createBranch<float>("lepton_eta");
    tx->createBranch<float>("lepton_phi");
    tx->createBranch<float>("lepton_pt");
    tx->createBranch<float>("lepton_relIso03EA");
    tx->createBranch<float>("lepton_relIso04DB");
    tx->createBranch<float>("lepton_miniIsoEA");
    tx->createBranch<float>("lepton_chiso");
    tx->createBranch<float>("lepton_nhiso");
    tx->createBranch<float>("lepton_emiso");
    tx->createBranch<float>("lepton_ncorriso");
    tx->createBranch<int>("lepton_nChargedPf");
    tx->createBranch<int>("lepton_nPhotonPf");
    tx->createBranch<int>("lepton_nNeutralHadPf");
    tx->createBranch<int>("lepton_isFromW");
    tx->createBranch<int>("lepton_flavor");
    tx->createBranch<int>("nvtx");
    tx->createBranch<vector<float>>("pf_annuli_energy");
    tx->createBranch<vector<float>>("pf_pt");
    tx->createBranch<vector<int>>("pf_id");
    tx->createBranch<vector<float>>("pf_reta");
    tx->createBranch<vector<float>>("pf_rphi");
}

//##############################################################################################################
void babyMaker::SetLeptonID()
{
    // Set lepton ID based on baby mode
    switch (babymode)
    {
        case kHWWBaby: SetHWWAnalysisLeptonID(); break;
        default: return;
    }
}

//##############################################################################################################
void babyMaker::SetHWWAnalysisLeptonID()
{
}

//##############################################################################################################
void babyMaker::Process()
{

    // For Gen-level weights the total weights need to be saved so must be called before skipping events (i.e. before PassSelection() exists Process())
    FillGenWeights();

    // Process objects needed to determine preselection
    ProcessObjectsPrePassSelection();

    if (!PassSelection())
        return;

    // Process other non-lepton objects via CoreUtil
    ProcessObjectsPostPassSelection();

    // Fill the output ttree
    FillBaby();

}

//##############################################################################################################
void babyMaker::FillGenWeights()
{
    if (cms3.evt_isRealData())
        return;

    FillGenWeightsNominal();
}

//##############################################################################################################
void babyMaker::FillGenWeightsNominal()
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
        h_neventsinfile->Fill(0., 1.); // event count
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

//##############################################################################################################
void babyMaker::ProcessLeptons()
{
    // Loop over electrons
    ProcessElectrons();

    // Loop over muons
    ProcessMuons();

}

//##############################################################################################################
void babyMaker::ProcessElectrons()
{
    // Based on the baby mode Process different set of electrons
    switch (babymode)
    {
        case kHWWBaby: ProcessHWWElectrons();     return; break;
        default: return;
    }
}

//##############################################################################################################
void babyMaker::ProcessHWWElectrons() { coreElectron.process(isPt10Electron); }

//##############################################################################################################
void babyMaker::ProcessMuons()
{
    // Based on the baby mode now preselect and if it doesn't pass return
    switch (babymode)
    {
        case kHWWBaby: ProcessHWWMuons();     return; break;
        default: return;
    }
}

//##############################################################################################################
void babyMaker::ProcessHWWMuons() { coreMuon.process(isPt10Muon); }

//##############################################################################################################
bool babyMaker::PassSelection()
{
    // Based on the baby mode now preselect and if it doesn't pass return
    switch (babymode)
    {
        case kHWWBaby: if (!PassHWWPreselection()) return false; break;
        default: return false;
    }

    // If it passed then accept
    return true;
}

//##############################################################################################################
bool babyMaker::PassHWWPreselection()
{
//    if (isHWWlvjj())
//    {
//        return true;
//    }
    int n_reconstructed_leptons = coreElectron.index.size() + coreMuon.index.size();
    int n_ak8 = 0;
    for (unsigned ijet = 0; ijet < coreFatJet.index.size(); ++ijet)
    {
        int idx = coreFatJet.index[ijet];
        float corr = coreFatJet.corrs[ijet];
        float shift = coreFatJet.shifts[ijet];
        LorentzVector fatjet = cms3.ak8jets_p4()[idx] * cms3.ak8jets_undoJEC()[idx] * corr;
        if (fatjet.pt() > 20)
        {
            n_ak8++;
        }
    }

    if (n_ak8 >= 1 && n_reconstructed_leptons >= 1)
        return true;
    else
        return false;
}

//##############################################################################################################
void babyMaker::ProcessObjectsPrePassSelection()
{
    // Process leptons via CoreUtil
    ProcessLeptons();

    // Loop over fatJets
    ProcessFatJets();
}

//##############################################################################################################
void babyMaker::ProcessObjectsPostPassSelection()
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
void babyMaker::ProcessTriggers() { coreTrigger.process(); }

//##############################################################################################################
void babyMaker::ProcessGenParticles() { coreGenPart.process(); }

//##############################################################################################################
void babyMaker::ProcessJets() { coreJet.process(coreJec); }

//##############################################################################################################
void babyMaker::ProcessFatJets() { coreFatJet.process(coreJec); }

//##############################################################################################################
void babyMaker::ProcessMET() { coreMET.process(coreJec); }

//##############################################################################################################
void babyMaker::ProcessTracks() { coreTrack.process(); }

//##############################################################################################################
void babyMaker::FillBaby()
{
    // Now process the rest of the stuff
    switch (babymode)
    {
        case kHWWBaby: FillHWWBaby(); break;
    }
}

//##############################################################################################################
void babyMaker::FillHWWBaby()
{

    // Fill baby ntuple branches with event information (evt, lumi etc.)
    // These are always created and filled
    FillEventInfo();

    // Fill lepton related information
    FillLepton();

    // Fill jet related information
    FillJet();

    // Fill met related information
    FillMET();

    // Fill gen variables
    FillGenVariables();

    // Fill reconstructed ISR variable
    FillRecoISR();

    // Fill reconstructed whad variable
    FillRecoWhad();

    // Fill reconstructed lepton variable
    FillRecoLepton();

    // Fill reconstructed lepton variable
    FillRecoLeadJet();

    // Fill reconstructed kinematic variables
    FillRecoVariables();

    // Truth level variables studies for WWW
    FillTruthLevelStudyVariables();

    // Fill met related information
    FillGenRecoMatching();

    // Fill higgs mass reconstruction related information
    FillHiggsMassReco();

    // Fill Eta Phi plane variables
    FillEtaPhiPlaneVariables();

    // Fill DeepIso variables
    FillDeepIsoVariables();

    // Fill high pt lepton triggers
    FillHighPtSingleLeptonTrigger();

    // Fill high pt lepton triggers
    FillIsolatedSingleLeptonTrigger();

    // Fill high pt lepton triggers
    FillOverlapRemovedBveto();

    // Fill reconstructed whad variable
    FillRecoWlep();

    // Fill TTree (NOTE: also clears internal variables)
    FillTTree();
}

//##############################################################################################################
void babyMaker::FillEventInfo()
{
    tx->setBranch<Int_t>("run", cms3.evt_run());
    tx->setBranch<Int_t>("lumi", cms3.evt_lumiBlock());
    tx->setBranch<unsigned long long>("evt", cms3.evt_event());
    tx->setBranch<int>("isData", cms3.evt_isRealData());
    if (cms3.evt_isRealData())
    {
        tx->setBranch<float>("evt_scale1fb", 1);
        tx->setBranch<float>("genps_weight", 1);
        tx->setBranch<float>("xsec_br", 1);
        tx->setBranch<int>("evt_passgoodrunlist", goodrun(cms3.evt_run(), cms3.evt_lumiBlock()));
    }
    else
    {
        float scale1fb = coreDatasetInfo.getScale1fb();
        float xsec = coreDatasetInfo.getXsec();
        tx->setBranch<float>("evt_scale1fb", scale1fb);
        tx->setBranch<float>("genps_weight", cms3.genps_weight());
        tx->setBranch<float>("xsec_br", xsec);
        tx->setBranch<int>("evt_passgoodrunlist", true);
    }
    tx->setBranch<TString>("CMS4path", looper.getCurrentFileName());
    tx->setBranch<int>("CMS4index", looper.getCurrentEventIndex());
}

//##############################################################################################################
void babyMaker::FillLepton()
{
    std::cout.setstate(std::ios_base::failbit); // To suppress warning about CMS4 not having PF candidates
    // Lepton absolute isolations
    for (auto& idx : coreElectron.index)
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
        tx->pushbackToBranch<float>("lep_customrelIso005EA" , elRelIsoCustomCone(idx , 0.05 , false , 0.0 , false , true , -1 , 2 , true));
        tx->pushbackToBranch<float>("lep_customrelIso01EA"  , elRelIsoCustomCone(idx , 0.1  , false , 0.0 , false , true , -1 , 2 , true));
        tx->pushbackToBranch<float>("lep_customrelIso015EA" , elRelIsoCustomCone(idx , 0.15 , false , 0.0 , false , true , -1 , 2 , true));
        tx->pushbackToBranch<float>("lep_customrelIso02EA"  , elRelIsoCustomCone(idx , 0.2  , false , 0.0 , false , true , -1 , 2 , true));
        tx->pushbackToBranch<float>("lep_customrelIso025EA" , elRelIsoCustomCone(idx , 0.25 , false , 0.0 , false , true , -1 , 2 , true));
        tx->pushbackToBranch<float>("lep_customrelIso03EA"  , elRelIsoCustomCone(idx , 0.3  , false , 0.0 , false , true , -1 , 2 , true));
        tx->pushbackToBranch<float>("lep_customrelIso035EA" , elRelIsoCustomCone(idx , 0.35 , false , 0.0 , false , true , -1 , 2 , true));
        tx->pushbackToBranch<float>("lep_customrelIso04EA"  , elRelIsoCustomCone(idx , 0.4  , false , 0.0 , false , true , -1 , 2 , true));
        tx->pushbackToBranch<float>("lep_customrelIso045EA" , elRelIsoCustomCone(idx , 0.45 , false , 0.0 , false , true , -1 , 2 , true));
        tx->pushbackToBranch<float>("lep_customrelIso05EA"  , elRelIsoCustomCone(idx , 0.5  , false , 0.0 , false , true , -1 , 2 , true));
        tx->pushbackToBranch<float>("lep_customrelIso055EA" , elRelIsoCustomCone(idx , 0.55 , false , 0.0 , false , true , -1 , 2 , true));
        tx->pushbackToBranch<float>("lep_customrelIso06EA"  , elRelIsoCustomCone(idx , 0.6  , false , 0.0 , false , true , -1 , 2 , true));
        tx->pushbackToBranch<float>("lep_customrelIso065EA" , elRelIsoCustomCone(idx , 0.65 , false , 0.0 , false , true , -1 , 2 , true));
        tx->pushbackToBranch<float>("lep_customrelIso07EA"  , elRelIsoCustomCone(idx , 0.7  , false , 0.0 , false , true , -1 , 2 , true));
        tx->pushbackToBranch<float>("lep_customrelIso075EA" , elRelIsoCustomCone(idx , 0.75 , false , 0.0 , false , true , -1 , 2 , true));
        tx->pushbackToBranch<float>("lep_customrelIso08EA"  , elRelIsoCustomCone(idx , 0.8  , false , 0.0 , false , true , -1 , 2 , true));
    }

    for (auto& idx : coreMuon.index)
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
        tx->pushbackToBranch<float>("lep_customrelIso005EA" , muRelIsoCustomCone(idx , 0.05 , false , 0.5 , false , true , -1 , 2 , true));
        tx->pushbackToBranch<float>("lep_customrelIso01EA"  , muRelIsoCustomCone(idx , 0.1  , false , 0.5 , false , true , -1 , 2 , true));
        tx->pushbackToBranch<float>("lep_customrelIso015EA" , muRelIsoCustomCone(idx , 0.15 , false , 0.5 , false , true , -1 , 2 , true));
        tx->pushbackToBranch<float>("lep_customrelIso02EA"  , muRelIsoCustomCone(idx , 0.2  , false , 0.5 , false , true , -1 , 2 , true));
        tx->pushbackToBranch<float>("lep_customrelIso025EA" , muRelIsoCustomCone(idx , 0.25 , false , 0.5 , false , true , -1 , 2 , true));
        tx->pushbackToBranch<float>("lep_customrelIso03EA"  , muRelIsoCustomCone(idx , 0.3  , false , 0.5 , false , true , -1 , 2 , true));
        tx->pushbackToBranch<float>("lep_customrelIso035EA" , muRelIsoCustomCone(idx , 0.35 , false , 0.5 , false , true , -1 , 2 , true));
        tx->pushbackToBranch<float>("lep_customrelIso04EA"  , muRelIsoCustomCone(idx , 0.4  , false , 0.5 , false , true , -1 , 2 , true));
        tx->pushbackToBranch<float>("lep_customrelIso045EA" , muRelIsoCustomCone(idx , 0.45 , false , 0.5 , false , true , -1 , 2 , true));
        tx->pushbackToBranch<float>("lep_customrelIso05EA"  , muRelIsoCustomCone(idx , 0.5  , false , 0.5 , false , true , -1 , 2 , true));
        tx->pushbackToBranch<float>("lep_customrelIso055EA" , muRelIsoCustomCone(idx , 0.55 , false , 0.5 , false , true , -1 , 2 , true));
        tx->pushbackToBranch<float>("lep_customrelIso06EA"  , muRelIsoCustomCone(idx , 0.6  , false , 0.5 , false , true , -1 , 2 , true));
        tx->pushbackToBranch<float>("lep_customrelIso065EA" , muRelIsoCustomCone(idx , 0.65 , false , 0.5 , false , true , -1 , 2 , true));
        tx->pushbackToBranch<float>("lep_customrelIso07EA"  , muRelIsoCustomCone(idx , 0.7  , false , 0.5 , false , true , -1 , 2 , true));
        tx->pushbackToBranch<float>("lep_customrelIso075EA" , muRelIsoCustomCone(idx , 0.75 , false , 0.5 , false , true , -1 , 2 , true));
        tx->pushbackToBranch<float>("lep_customrelIso08EA"  , muRelIsoCustomCone(idx , 0.8  , false , 0.5 , false , true , -1 , 2 , true));
    }
    tx->setBranch<int>("nrecolep", coreElectron.index.size() + coreMuon.index.size());
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
            "lep_customrelIso015EA",
            "lep_customrelIso02EA",
            "lep_customrelIso025EA",
            "lep_customrelIso03EA",
            "lep_customrelIso035EA",
            "lep_customrelIso04EA",
            "lep_customrelIso045EA",
            "lep_customrelIso05EA",
            "lep_customrelIso055EA",
            "lep_customrelIso06EA",
            "lep_customrelIso065EA",
            "lep_customrelIso07EA",
            "lep_customrelIso075EA",
            "lep_customrelIso08EA",
            },
            {
            "lep_id",
            "lep_idx",
            },
            {});

    tx->setFlatBranch(
            {
            "lep_p4",
            },
            {
            "lep_pt",
            "lep_eta",
            "lep_phi",
            "lep_miniIsoEA",
            "lep_relIso03EA",
            "lep_relIso04DB",
            },
            {
            "lep_id",
            "lep_idx",
            },
            {},
            3);

}

//##############################################################################################################
void babyMaker::FillJet()
{
    coreBtagSF.clearSF();
    coreBtagSFFastSim.clearSF();

    int nj = 0;
    int nj50 = 0;
    int nb = 0;
    int nbmed = 0;
    int nbtight = 0;
    int nb50 = 0;
    int nb50med = 0;
    int nb50tight = 0;
    int nb40 = 0;
    int nb40med = 0;
    int nb40tight = 0;
    int nb30 = 0;
    int nb30med = 0;
    int nb30tight = 0;
    float ht = 0;
    float ht40 = 0;
    float ht50 = 0;
    LV v_mh;
    LV v_mh40;
    LV v_mh50;

    for (unsigned ijet = 0; ijet < coreJet.index.size(); ++ijet)
    {
        int idx = coreJet.index[ijet];
        float corr = coreJet.corrs[ijet];
        float shift = coreJet.shifts[ijet];
        float current_csv_val = cms3.getbtagvalue("pfCombinedInclusiveSecondaryVertexV2BJetTags", idx);
        LorentzVector jet = cms3.pfjets_p4()[idx] * cms3.pfjets_undoJEC()[idx] * corr;

        tx->pushbackToBranch<LorentzVector>("alljets_p4", jet);
        tx->pushbackToBranch<float>("alljets_pt", jet.pt());
        tx->pushbackToBranch<float>("alljets_eta", jet.eta());
        tx->pushbackToBranch<float>("alljets_phi", jet.phi());
        tx->pushbackToBranch<float>("alljets_csv", current_csv_val);

        // Check whether this jet overlaps with any of the leptons
        if (isLeptonOverlappingWithJet(ijet))
            continue;

        //if (jet.pt() > 30 && fabs(jet.eta()) < 2.4)
        if (jet.pt() > 30)
        {
            tx->pushbackToBranch<LorentzVector>("jets_p4", jet);
            tx->pushbackToBranch<float>("jets_pt", jet.pt());
            tx->pushbackToBranch<float>("jets_eta", jet.eta());
            tx->pushbackToBranch<float>("jets_phi", jet.phi());
            tx->pushbackToBranch<float>("jets_csv", current_csv_val);
            if (!isFastSim())
                coreBtagSF.accumulateSF(idx, jet.pt(), jet.eta());
            else
                coreBtagSFFastSim.accumulateSF(idx, jet.pt(), jet.eta());
            if (fabs(jet.eta()) < 2.4)
            {
                nj++;
                ht += jet.pt();
                v_mh += jet;
                if (jet.pt() > 40.)
                {
                    ht40 += jet.pt();
                    v_mh40 += jet;
                }
                if (jet.pt() > 50.)
                {
                    ht50 += jet.pt();
                    v_mh50 += jet;
                }
            }
            if (fabs(jet.eta()) < 2.4 && jet.pt() > 50)
                nj50++;
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

        // nb jets
        if (jet.pt() > 30.)
        {
            if (fabs(jet.eta()) < 2.4 && current_csv_val >= 0.5426)
                nb30++;
            if (fabs(jet.eta()) < 2.4 && current_csv_val >= 0.8484)
                nb30med++;
            if (fabs(jet.eta()) < 2.4 && current_csv_val >= 0.9535)
                nb30tight++;
        }

        // nb jets
        if (jet.pt() > 40.)
        {
            if (fabs(jet.eta()) < 2.4 && current_csv_val >= 0.5426)
                nb40++;
            if (fabs(jet.eta()) < 2.4 && current_csv_val >= 0.8484)
                nb40med++;
            if (fabs(jet.eta()) < 2.4 && current_csv_val >= 0.9535)
                nb40tight++;
        }

        // nb jets
        if (jet.pt() > 50.)
        {
            if (fabs(jet.eta()) < 2.4 && current_csv_val >= 0.5426)
                nb50++;
            if (fabs(jet.eta()) < 2.4 && current_csv_val >= 0.8484)
                nb50med++;
            if (fabs(jet.eta()) < 2.4 && current_csv_val >= 0.9535)
                nb50tight++;
        }


        LorentzVector jet_up = jet * (1. + shift);
        //if (jet_up.pt() > 30 && fabs(jet.eta()) < 2.4)
        if (jet_up.pt() > 30)
        {
            tx->pushbackToBranch<LorentzVector>("jets_up_p4", jet_up);
            tx->pushbackToBranch<float>("jets_up_pt", jet_up.pt());
            tx->pushbackToBranch<float>("jets_up_eta", jet_up.eta());
            tx->pushbackToBranch<float>("jets_up_phi", jet_up.phi());
            tx->pushbackToBranch<float>("jets_up_csv", current_csv_val);
        }

        LorentzVector jet_dn = jet * (1. - shift);
        //if (jet_dn.pt() > 30 && fabs(jet.eta()) < 2.4)
        if (jet_dn.pt() > 30)
        {
            tx->pushbackToBranch<LorentzVector>("jets_dn_p4", jet_dn);
            tx->pushbackToBranch<float>("jets_dn_pt", jet_dn.pt());
            tx->pushbackToBranch<float>("jets_dn_eta", jet_dn.eta());
            tx->pushbackToBranch<float>("jets_dn_phi", jet_dn.phi());
            tx->pushbackToBranch<float>("jets_dn_csv", current_csv_val);
        }
    }

    tx->setBranch<int>("nb", nb);
    tx->setBranch<int>("nbmed", nbmed);
    tx->setBranch<int>("nbtight", nbtight);
    tx->setBranch<int>("nb30", nb30);
    tx->setBranch<int>("nb30med", nb30med);
    tx->setBranch<int>("nb30tight", nb30tight);
    tx->setBranch<int>("nb40", nb40);
    tx->setBranch<int>("nb40med", nb40med);
    tx->setBranch<int>("nb40tight", nb40tight);
    tx->setBranch<int>("nb50", nb50);
    tx->setBranch<int>("nb50med", nb50med);
    tx->setBranch<int>("nb50tight", nb50tight);
    tx->setBranch<int>("nj", nj);
    tx->setBranch<int>("nj50", nj50);
    tx->setBranch<float>("ht", ht);
    tx->setBranch<float>("ht40", ht40);
    tx->setBranch<float>("ht50", ht50);
    tx->setBranch<float>("mh", v_mh.mass());
    tx->setBranch<float>("mh40", v_mh40.mass());
    tx->setBranch<float>("mh50", v_mh50.mass());

    int nak8jets = 0;
    for (unsigned ijet = 0; ijet < coreFatJet.index.size(); ++ijet)
    {
        int idx = coreFatJet.index[ijet];
        float corr = coreFatJet.corrs[ijet];
        float shift = coreFatJet.shifts[ijet];
        LorentzVector fatjet = cms3.ak8jets_p4()[idx] * cms3.ak8jets_undoJEC()[idx] * corr;
        if (fatjet.pt() > 20)
        {
            nak8jets++;
            tx->pushbackToBranch<LorentzVector>("ak8jets_p4", fatjet);
            tx->pushbackToBranch<float>("ak8jets_pt", fatjet.pt());
            tx->pushbackToBranch<float>("ak8jets_eta", fatjet.eta());
            tx->pushbackToBranch<float>("ak8jets_phi", fatjet.phi());
            // 2016 CMS4 has a different naming scheme
            if (coreSample.is2016(looper.getCurrentFileName()))
            {
                tx->pushbackToBranch<float>("ak8jets_softdropMass", cms3.ak8jets_softdropMass()[idx]);
                tx->pushbackToBranch<float>("ak8jets_prunedMass", cms3.ak8jets_prunedMass()[idx]);
                tx->pushbackToBranch<float>("ak8jets_nJettinessTau1", cms3.ak8jets_nJettinessTau1()[idx]);
                tx->pushbackToBranch<float>("ak8jets_nJettinessTau2", cms3.ak8jets_nJettinessTau2()[idx]);
                tx->pushbackToBranch<float>("ak8jets_mass", cms3.ak8jets_mass()[idx]);
                tx->pushbackToBranch<float>("ak8jets_puppi_nJettinessTau1", cms3.ak8jets_puppi_nJettinessTau1()[idx]);
                tx->pushbackToBranch<float>("ak8jets_puppi_nJettinessTau2", cms3.ak8jets_puppi_nJettinessTau2()[idx]);
                tx->pushbackToBranch<float>("ak8jets_puppi_softdropMass", cms3.ak8jets_puppi_softdropMass()[idx]);
                tx->pushbackToBranch<float>("ak8jets_puppi_eta", cms3.ak8jets_puppi_eta()[idx]);
                tx->pushbackToBranch<float>("ak8jets_puppi_phi", cms3.ak8jets_puppi_phi()[idx]);
                tx->pushbackToBranch<float>("ak8jets_puppi_pt", cms3.ak8jets_puppi_pt()[idx]);
                tx->pushbackToBranch<float>("ak8jets_puppi_mass", cms3.ak8jets_puppi_mass()[idx]);
                tx->pushbackToBranch<float>("ak8jets_softdropPuppiSubjet1", cms3.ak8jets_softdropPuppiSubjet1()[idx].M());
                tx->pushbackToBranch<float>("ak8jets_softdropPuppiSubjet2", cms3.ak8jets_softdropPuppiSubjet2()[idx].M());
            }
            // 2017 uses PUPPI for default and several of these mass variables are not even provided
            else if (coreSample.is2017(looper.getCurrentFileName()))
            {
                tx->pushbackToBranch<float>("ak8jets_softdropMass", cms3.ak8jets_puppi_softdropMass()[idx]);
                tx->pushbackToBranch<float>("ak8jets_softdropPuppiSubjet1", cms3.ak8jets_softdropPuppiSubjet1()[idx].M());
                tx->pushbackToBranch<float>("ak8jets_softdropPuppiSubjet2", cms3.ak8jets_softdropPuppiSubjet2()[idx].M());
            }
        }
    }
    tx->setBranch<int>("nak8jets", nak8jets);

    tx->setFlatBranch(
            {
            "jets_p4",
            "jets_up_p4",
            "jets_dn_p4",
            "ak8jets_p4"
            },
            {
            "jets_pt",
            "jets_eta",
            "jets_phi",
            "jets_csv",
            "jets_up_pt",
            "jets_up_eta",
            "jets_up_phi",
            "jets_up_csv",
            "jets_dn_pt",
            "jets_dn_eta",
            "jets_dn_phi",
            "jets_dn_csv",
            "ak8jets_pt",
            "ak8jets_eta",
            "ak8jets_phi",
            "ak8jets_softdropMass",
            "ak8jets_prunedMass",
            "ak8jets_trimmedMass",
            "ak8jets_mass",
            "ak8jets_nJettinessTau1",
            "ak8jets_nJettinessTau2",
            "ak8jets_softdropPuppiSubjet1",
            "ak8jets_softdropPuppiSubjet2",
            "ak8jets_puppi_softdropMass",
            "ak8jets_puppi_nJettinessTau1",
            "ak8jets_puppi_nJettinessTau2",
            "ak8jets_puppi_eta",
            "ak8jets_puppi_phi",
            "ak8jets_puppi_pt",
            "ak8jets_puppi_mass",
            },
            {},
            {},
            3);


    if (!cms3.evt_isRealData())
    {
        if (!isFastSim())
        {
            tx->setBranch<float>("weight_btagsf"         , coreBtagSF.btagprob_data     / coreBtagSF.btagprob_mc);
            tx->setBranch<float>("weight_btagsf_heavy_DN", coreBtagSF.btagprob_heavy_DN / coreBtagSF.btagprob_mc);
            tx->setBranch<float>("weight_btagsf_heavy_UP", coreBtagSF.btagprob_heavy_UP / coreBtagSF.btagprob_mc);
            tx->setBranch<float>("weight_btagsf_light_DN", coreBtagSF.btagprob_light_DN / coreBtagSF.btagprob_mc);
            tx->setBranch<float>("weight_btagsf_light_UP", coreBtagSF.btagprob_light_UP / coreBtagSF.btagprob_mc);
        }
        else
        {
            tx->setBranch<float>("weight_btagsf"         , coreBtagSFFastSim.btagprob_data     / coreBtagSFFastSim.btagprob_mc);
            tx->setBranch<float>("weight_btagsf_heavy_DN", coreBtagSFFastSim.btagprob_heavy_DN / coreBtagSFFastSim.btagprob_mc);
            tx->setBranch<float>("weight_btagsf_heavy_UP", coreBtagSFFastSim.btagprob_heavy_UP / coreBtagSFFastSim.btagprob_mc);
            tx->setBranch<float>("weight_btagsf_light_DN", coreBtagSFFastSim.btagprob_light_DN / coreBtagSFFastSim.btagprob_mc);
            tx->setBranch<float>("weight_btagsf_light_UP", coreBtagSFFastSim.btagprob_light_UP / coreBtagSFFastSim.btagprob_mc);
        }
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
void babyMaker::FillMET()
{
    tx->setBranch<float>("met_pt", coreMET.met_pt);
    tx->setBranch<float>("met_phi", coreMET.met_phi);
    tx->setBranch<float>("met_up_pt", coreMET.met_up_pt);
    tx->setBranch<float>("met_up_phi", coreMET.met_up_phi);
    tx->setBranch<float>("met_dn_pt", coreMET.met_dn_pt);
    tx->setBranch<float>("met_dn_phi", coreMET.met_dn_phi);
    tx->setBranch<float>("met_gen_pt", cms3.gen_met());
    tx->setBranch<float>("met_gen_phi", cms3.gen_metPhi());
}

//##############################################################################################################
void babyMaker::FillGenVariables()
{
    tx->setBranch<float>("gen_ht", coreGenPart.gen_ht);
}

//##############################################################################################################
void babyMaker::FillGenRecoMatching()
{
    if (!isHWWlvjj() && !isHbb())
        return;
    // ISR parton to leading jet matching test
    const LV& isr_p4 = tx->getBranch<LV>("isr_p4", false);
    const float& isr_pt = tx->getBranch<float>("isr_pt", false);
    const vector<LV>& jets_p4 = tx->getBranch<vector<LV>>("jets_p4", false);
    if (isr_pt > 0 && jets_p4.size() > 0)
    {
        float dr = RooUtil::Calc::DeltaR(isr_p4, jets_p4[0]);
        tx->setBranch<float>("isr_leadjet_dr", dr);
    }

    // Testing higgs met dphi
    const LV& higgs_p4 = tx->getBranch<LV>("higgs_p4");
    const float& met_phi = tx->getBranch<float>("met_phi");
    float dphi = TVector2::Phi_mpi_pi(met_phi-higgs_p4.phi());
    tx->setBranch<float>("higgs_met_dphi", dphi);

    // Testing if opposite hemi-sphere lead jet selection works as expected
    const LV& recoisr_p4 = tx->getBranch<LV>("recoisr_p4", false);
    const float& recoisr_pt = tx->getBranch<float>("recoisr_pt", false);
    if (isr_pt > 0 && recoisr_pt > 0)
    {
        float dr = RooUtil::Calc::DeltaR(isr_p4, recoisr_p4);
        tx->setBranch<float>("isr_recoisr_dr", dr);
    }

    // Testing if opposite hemi-sphere lead jet selection works as expected
    const LV& recoisrmegajet_p4 = tx->getBranch<LV>("recoisrmegajet_p4", false);
    const float& recoisrmegajet_pt = tx->getBranch<float>("recoisrmegajet_pt", false);
    if (isr_pt > 0 && recoisrmegajet_pt > 0)
    {
        float dr = RooUtil::Calc::DeltaR(isr_p4, recoisrmegajet_p4);
        tx->setBranch<float>("isr_recoisrmegajet_dr", dr);
    }

    if (isHWWlvjj())
    {
        const vector<LV>& lepton_p4 = tx->getBranch<vector<LV>>("lepton_p4");
        const vector<LV>& neutrino_p4 = tx->getBranch<vector<LV>>("neutrino_p4");
        const vector<LV>& quark_p4 = tx->getBranch<vector<LV>>("quark_p4");
        const vector<LV>& decay_p4 = tx->getBranch<vector<LV>>("decay_p4");
        const vector<int>& decay_isstar = tx->getBranch<vector<int>>("decay_isstar");
        const vector<int>& lepton_isstar = tx->getBranch<vector<int>>("lepton_isstar");
        const vector<int>& quark_isstar = tx->getBranch<vector<int>>("quark_isstar");

        float lepton_met_dphi = TVector2::Phi_mpi_pi(met_phi-lepton_p4[0].phi());
        tx->setBranch<float>("lepton_met_dphi", lepton_met_dphi);

        float quark0_met_dphi = TVector2::Phi_mpi_pi(met_phi-quark_p4[0].phi());
        float quark1_met_dphi = TVector2::Phi_mpi_pi(met_phi-quark_p4[1].phi());
        tx->setBranch<float>("quark0_met_dphi", quark0_met_dphi);
        tx->setBranch<float>("quark1_met_dphi", quark1_met_dphi);

        int wlep_index = decay_isstar[0] == lepton_isstar[0] ? 0 : 1;
        int whad_index = decay_isstar[0] == lepton_isstar[0] ? 1 : 0;
        float wlep_met_dphi = TVector2::Phi_mpi_pi(met_phi-decay_p4[wlep_index].phi());
        float whad_met_dphi = TVector2::Phi_mpi_pi(met_phi-decay_p4[whad_index].phi());
        tx->setBranch<float>("wlep_met_dphi", wlep_met_dphi);
        tx->setBranch<float>("whad_met_dphi", whad_met_dphi);

        const LV& recowhad_p4 = tx->getBranch<LV>("recowhad_p4", false);
        const float& recowhad_pt = tx->getBranch<float>("recowhad_pt", false);
        if (recowhad_pt > 0)
        {
            float dr = RooUtil::Calc::DeltaR(decay_p4[whad_index], recowhad_p4);
            float deta = RooUtil::Calc::DeltaEta(decay_p4[whad_index], recowhad_p4);
            float dphi = RooUtil::Calc::DeltaPhi(decay_p4[whad_index], recowhad_p4);
            float ptratio = recowhad_p4.pt() / decay_p4[whad_index].pt();
            tx->setBranch<float>("whad_recowhad_dr", dr);
            tx->setBranch<float>("whad_recowhad_deta", deta);
            tx->setBranch<float>("whad_recowhad_dphi", dphi);
            tx->setBranch<float>("whad_recowhad_ptratio", ptratio);
            dr = RooUtil::Calc::DeltaR(higgs_p4, recowhad_p4);
            deta = RooUtil::Calc::DeltaEta(higgs_p4, recowhad_p4);
            dphi = RooUtil::Calc::DeltaPhi(higgs_p4, recowhad_p4);
            ptratio = recowhad_p4.pt() / higgs_p4.pt();
            tx->setBranch<float>("higgs_recowhad_dr", dr);
            tx->setBranch<float>("higgs_recowhad_deta", deta);
            tx->setBranch<float>("higgs_recowhad_dphi", dphi);
            tx->setBranch<float>("higgs_recowhad_ptratio", ptratio);
        }

        const vector<LV>& ak8jets_p4 = tx->getBranch<vector<LV>>("ak8jets_p4", false);
        if (ak8jets_p4.size() > 0)
        {
            const LV& leadak8 = ak8jets_p4[0];
            float dr = RooUtil::Calc::DeltaR(decay_p4[whad_index], leadak8);
            float deta = RooUtil::Calc::DeltaEta(decay_p4[whad_index], leadak8);
            float dphi = RooUtil::Calc::DeltaPhi(decay_p4[whad_index], leadak8);
            float ptratio = leadak8.pt() / decay_p4[whad_index].pt();
            tx->setBranch<float>("whad_leadak8_dr", dr);
            tx->setBranch<float>("whad_leadak8_deta", deta);
            tx->setBranch<float>("whad_leadak8_dphi", dphi);
            tx->setBranch<float>("whad_leadak8_ptratio", ptratio);
            dr = RooUtil::Calc::DeltaR(higgs_p4, leadak8);
            deta = RooUtil::Calc::DeltaEta(higgs_p4, leadak8);
            dphi = RooUtil::Calc::DeltaPhi(higgs_p4, leadak8);
            ptratio = leadak8.pt() / higgs_p4.pt();
            tx->setBranch<float>("higgs_leadak8_dr", dr);
            tx->setBranch<float>("higgs_leadak8_deta", deta);
            tx->setBranch<float>("higgs_leadak8_dphi", dphi);
            tx->setBranch<float>("higgs_leadak8_ptratio", ptratio);
        }

        const LV& recolepton_p4 = tx->getBranch<LV>("recolepton_p4", false);
        const float& recolepton_pt = tx->getBranch<float>("recolepton_pt", false);
        if (recolepton_pt > 0)
        {
            float dr = RooUtil::Calc::DeltaR(lepton_p4[0], recolepton_p4);
            float deta = RooUtil::Calc::DeltaEta(lepton_p4[0], recolepton_p4);
            float dphi = RooUtil::Calc::DeltaPhi(lepton_p4[0], recolepton_p4);
            float ptratio = recolepton_p4.pt() / lepton_p4[0].pt();
            tx->setBranch<float>("lepton_recolep_dr", dr);
            tx->setBranch<float>("lepton_recolep_deta", deta);
            tx->setBranch<float>("lepton_recolep_dphi", dphi);
            tx->setBranch<float>("lepton_recolep_ptratio", ptratio);
        }

        const LV& reconeutrino_p4 = tx->getBranch<LV>("reconeutrino_p4", false);
        const float& reconeutrino_pt = tx->getBranch<float>("reconeutrino_pt", false);
        if (reconeutrino_pt > 0)
        {
            float dr = RooUtil::Calc::DeltaR(neutrino_p4[0], reconeutrino_p4);
            float deta = RooUtil::Calc::DeltaEta(neutrino_p4[0], reconeutrino_p4);
            float dphi = RooUtil::Calc::DeltaPhi(neutrino_p4[0], reconeutrino_p4);
            float dpz = neutrino_p4[0].pz() - reconeutrino_p4.pz();
            float dabspz = fabs(neutrino_p4[0].pz()) - fabs(reconeutrino_p4.pz());
            float ptratio = reconeutrino_p4.pt() / neutrino_p4[0].pt();
            tx->setBranch<float>("neutrino_reconeutrino_dr", dr);
            tx->setBranch<float>("neutrino_reconeutrino_deta", deta);
            tx->setBranch<float>("neutrino_reconeutrino_dphi", dphi);
            tx->setBranch<float>("neutrino_reconeutrino_dpz", dpz);
            tx->setBranch<float>("neutrino_reconeutrino_dabspz", dabspz);
            tx->setBranch<float>("neutrino_reconeutrino_ptratio", ptratio);
        }
    }
}

//##############################################################################################################
void babyMaker::FillHiggsMassReco()
{
    const float& met_pt = tx->getBranch<float>("met_pt");
    const float& met_phi = tx->getBranch<float>("met_phi");
    const LV& p4 = tx->getBranch<LV>("recowhad_p4", false);
    const float& pt = tx->getBranch<float>("recowhad_pt", false);
    if (pt > 0)
    {
        const LV& reconeutrino_p4 = tx->getBranch<LV>("reconeutrino_p4", false);
        const float& reconeutrino_pt = tx->getBranch<float>("reconeutrino_pt", false);
        if (reconeutrino_pt > 0)
        {
            LV sum_p4 = p4 + reconeutrino_p4;
            tx->setBranch<LV>("recohiggs_p4", sum_p4);
            tx->setBranch<float>("recohiggs_pt", sum_p4.pt());
            tx->setBranch<float>("recohiggs_eta", sum_p4.eta());
            tx->setBranch<float>("recohiggs_phi", sum_p4.phi());
            tx->setBranch<float>("recohiggs_mass", sum_p4.mass());
            tx->setBranch<float>("recohiggs_mt", sum_p4.mt());
            const LV& reconeutrino2_p4 = tx->getBranch<LV>("reconeutrino2_p4", false);
            LV sum_p42 = p4 + reconeutrino2_p4;
            tx->setBranch<LV>("recohiggs2_p4", sum_p42);
            tx->setBranch<float>("recohiggs2_pt", sum_p42.pt());
            tx->setBranch<float>("recohiggs2_eta", sum_p42.eta());
            tx->setBranch<float>("recohiggs2_phi", sum_p42.phi());
            tx->setBranch<float>("recohiggs2_mass", sum_p42.mass());
            tx->setBranch<float>("recohiggs2_mt", sum_p42.mt());
            const LV& reconeutrinoinv_p4 = tx->getBranch<LV>("reconeutrinoinv_p4", false);
            LV sum_p4inv = p4 + reconeutrinoinv_p4;
            tx->setBranch<LV>("recohiggsinv_p4", sum_p4inv);
            tx->setBranch<float>("recohiggsinv_pt", sum_p4inv.pt());
            tx->setBranch<float>("recohiggsinv_eta", sum_p4inv.eta());
            tx->setBranch<float>("recohiggsinv_phi", sum_p4inv.phi());
            tx->setBranch<float>("recohiggsinv_mass", sum_p4inv.mass());
            tx->setBranch<float>("recohiggsinv_mt", sum_p4inv.mt());


            // Choose the p4 with the minimum mass
            LV sum_p4min;
            if (sum_p4.mass() < sum_p42.mass() && sum_p4.mass() < sum_p4inv.mass())
                sum_p4min = sum_p4;
            else if (sum_p42.mass() < sum_p4.mass() && sum_p42.mass() < sum_p4inv.mass())
                sum_p4min = sum_p42;
            else if (sum_p4inv.mass() < sum_p4.mass() && sum_p4inv.mass() < sum_p42.mass())
                sum_p4min = sum_p4inv;
            else
                sum_p4min = sum_p4;
            tx->setBranch<LV>("recohiggsmin_p4", sum_p4min);
            tx->setBranch<float>("recohiggsmin_pt", sum_p4min.pt());
            tx->setBranch<float>("recohiggsmin_eta", sum_p4min.eta());
            tx->setBranch<float>("recohiggsmin_phi", sum_p4min.phi());
            tx->setBranch<float>("recohiggsmin_mass", sum_p4min.mass());
            tx->setBranch<float>("recohiggsmin_mt", sum_p4min.mt());

            LV sum_p4min12 = sum_p4.mass() < sum_p42.mass() ? sum_p4 : sum_p42;
            tx->setBranch<LV>("recohiggsmin12_p4", sum_p4min12);
            tx->setBranch<float>("recohiggsmin12_pt", sum_p4min12.pt());
            tx->setBranch<float>("recohiggsmin12_eta", sum_p4min12.eta());
            tx->setBranch<float>("recohiggsmin12_phi", sum_p4min12.phi());
            tx->setBranch<float>("recohiggsmin12_mass", sum_p4min12.mass());
            tx->setBranch<float>("recohiggsmin12_mt", sum_p4min12.mt());
        }
        else
        {
            TLorentzVector met_tlv;
            met_tlv.SetPtEtaPhiM(met_pt, 0, met_phi, 0);
            LV met = RooUtil::Calc::getLV(met_tlv);
            LV sum_p4 = p4 + met;
            tx->setBranch<LV>("recohiggs_p4", sum_p4);
            tx->setBranch<float>("recohiggs_pt", sum_p4.pt());
            tx->setBranch<float>("recohiggs_eta", sum_p4.eta());
            tx->setBranch<float>("recohiggs_phi", sum_p4.phi());
            tx->setBranch<float>("recohiggs_mass", sum_p4.mass());
            tx->setBranch<float>("recohiggs_mt", sum_p4.mt());
            tx->setBranch<LV>("recohiggs2_p4", sum_p4);
            tx->setBranch<float>("recohiggs2_pt", sum_p4.pt());
            tx->setBranch<float>("recohiggs2_eta", sum_p4.eta());
            tx->setBranch<float>("recohiggs2_phi", sum_p4.phi());
            tx->setBranch<float>("recohiggs2_mass", sum_p4.mass());
            tx->setBranch<float>("recohiggs2_mt", sum_p4.mt());
            tx->setBranch<LV>("recohiggsinv_p4", sum_p4);
            tx->setBranch<float>("recohiggsinv_pt", sum_p4.pt());
            tx->setBranch<float>("recohiggsinv_eta", sum_p4.eta());
            tx->setBranch<float>("recohiggsinv_phi", sum_p4.phi());
            tx->setBranch<float>("recohiggsinv_mass", sum_p4.mass());
            tx->setBranch<float>("recohiggsinv_mt", sum_p4.mt());
            tx->setBranch<LV>("recohiggsmin_p4", sum_p4);
            tx->setBranch<float>("recohiggsmin_pt", sum_p4.pt());
            tx->setBranch<float>("recohiggsmin_eta", sum_p4.eta());
            tx->setBranch<float>("recohiggsmin_phi", sum_p4.phi());
            tx->setBranch<float>("recohiggsmin_mass", sum_p4.mass());
            tx->setBranch<float>("recohiggsmin_mt", sum_p4.mt());
        }

    }
}

//##############################################################################################################
void babyMaker::FillEtaPhiPlaneVariables()
{
    const LV& recolepton_p4 = tx->getBranch<LV>("recolepton_p4", false);
    const float& recolepton_pt = tx->getBranch<float>("recolepton_pt", false);

    const vector<LV>& alljets_p4 = tx->getBranch<vector<LV>>("alljets_p4", false);
    const vector<float>& alljets_csv = tx->getBranch<vector<float>>("alljets_csv", false);

    const vector<LV>& jets_p4 = tx->getBranch<vector<LV>>("jets_p4", false);
    const vector<float>& jets_csv = tx->getBranch<vector<float>>("jets_csv", false);

    const LV& recowhad_p4 = tx->getBranch<LV>("recowhad_p4", false);
    const float& recowhad_pt = tx->getBranch<float>("recowhad_pt", false);

    if (recolepton_pt > 0 && recowhad_pt > 0)
    {
        float sumpt_oppo_r15 = 0;
        int njet5_oppo_r15 = 0;
        int njet10_oppo_r15 = 0;
        int njet20_oppo_r15 = 0;
        int njet30_oppo_r15 = 0;
        int njet50_oppo_r15 = 0;
        float sumpt_oppo = 0;
        int njet5_oppo = 0;
        int njet10_oppo = 0;
        int njet20_oppo = 0;
        int njet30_oppo = 0;
        int njet50_oppo = 0;
        float sumpt_in_fatjet = 0;
        int njet5_in_fatjet = 0;
        for (unsigned int ijet = 0; ijet < alljets_p4.size(); ++ijet)
        {
            const LV& jet_p4 =  alljets_p4[ijet];
            float dr_lep = RooUtil::Calc::DeltaR(jet_p4, recolepton_p4);
            float dr_jet = RooUtil::Calc::DeltaR(jet_p4, recowhad_p4);
            if (dr_lep < 1.5 && dr_jet > 0.8)
            {
                sumpt_oppo_r15 = jet_p4.pt();
                if (jet_p4.pt() > 5) njet5_oppo_r15++;
                if (jet_p4.pt() > 10) njet10_oppo_r15++;
                if (jet_p4.pt() > 20) njet20_oppo_r15++;
                if (jet_p4.pt() > 30) njet30_oppo_r15++;
                if (jet_p4.pt() > 50) njet50_oppo_r15++;
            }
            if (dr_lep < 2.0 && dr_jet > 0.8)
            {
                sumpt_oppo = jet_p4.pt();
                if (jet_p4.pt() > 5) njet5_oppo++;
                if (jet_p4.pt() > 10) njet10_oppo++;
                if (jet_p4.pt() > 20) njet20_oppo++;
                if (jet_p4.pt() > 30) njet30_oppo++;
                if (jet_p4.pt() > 50) njet50_oppo++;
            }
            if (dr_jet < 0.8 && dr_lep > 0.1)
            {
                sumpt_in_fatjet = jet_p4.pt();
                njet5_in_fatjet++;
            }
        }
        tx->setBranch<float>("sumpt_oppo_r15", sumpt_oppo_r15);
        tx->setBranch<int>("njet5_oppo_r15", njet5_oppo_r15);
        tx->setBranch<int>("njet10_oppo_r15", njet10_oppo_r15);
        tx->setBranch<int>("njet20_oppo_r15", njet20_oppo_r15);
        tx->setBranch<int>("njet30_oppo_r15", njet30_oppo_r15);
        tx->setBranch<int>("njet50_oppo_r15", njet50_oppo_r15);
        tx->setBranch<float>("sumpt_oppo", sumpt_oppo);
        tx->setBranch<int>("njet5_oppo", njet5_oppo);
        tx->setBranch<int>("njet10_oppo", njet10_oppo);
        tx->setBranch<int>("njet20_oppo", njet20_oppo);
        tx->setBranch<int>("njet30_oppo", njet30_oppo);
        tx->setBranch<int>("njet50_oppo", njet50_oppo);
        tx->setBranch<float>("sumpt_in_fatjet", sumpt_in_fatjet);
        tx->setBranch<int>("njet5_in_fatjet", njet5_in_fatjet);
    }

//    std::cout <<  " recolepton_p4.pt(): " << recolepton_p4.pt() <<  std::endl;
//    std::cout <<  " recolepton_p4.eta(): " << recolepton_p4.eta() <<  std::endl;
//    std::cout <<  " recolepton_p4.phi(): " << recolepton_p4.phi() <<  std::endl;
//    std::cout <<  " recolepton_p4.mass(): " << recolepton_p4.mass() <<  std::endl;

//    if (isHWWlvjj())
//    {
//        const vector<LV>&  lepton_p4       = tx->getBranch<vector<LV> >("lepton_p4"       );
//        const vector<int>& lepton_id       = tx->getBranch<vector<int>>("lepton_id"       );
//        const vector<int>& lepton_isstar   = tx->getBranch<vector<int>>("lepton_isstar"   );
//        const vector<LV>&  neutrino_p4     = tx->getBranch<vector<LV> >("neutrino_p4"     );
//        const vector<int>& neutrino_id     = tx->getBranch<vector<int>>("neutrino_id"     );
//        const vector<int>& neutrino_isstar = tx->getBranch<vector<int>>("neutrino_isstar" );
//        const vector<LV>&  quark_p4        = tx->getBranch<vector<LV> >("quark_p4"        );
//        const vector<int>& quark_id        = tx->getBranch<vector<int>>("quark_id"        );
//        const vector<int>& quark_isstar    = tx->getBranch<vector<int>>("quark_isstar"    );
//        const float&       lqq_max_dr      = tx->getBranch<float      >("lqq_max_dr"      );
//        const float&       lq0_dr          = tx->getBranch<float      >("lq0_dr"          );
//        const float&       lq1_dr          = tx->getBranch<float      >("lq1_dr"          );
//        const float&       qq_dr           = tx->getBranch<float      >("qq_dr"           );
//        const float&       decay_dr        = tx->getBranch<float      >("decay_dr"        );
//        const float&       l_qq_dr         = tx->getBranch<float      >("l_qq_dr"         );
//        const float&       lqq_mass        = tx->getBranch<float      >("lqq_mass"        );
//        const float&       lvqq_mt         = tx->getBranch<float      >("lvqq_mt"         );
//
//        std::cout <<  " lepton_p4[0].pt(): " << lepton_p4[0].pt() <<  std::endl;
//        std::cout <<  " lepton_p4[0].eta(): " << lepton_p4[0].eta() <<  std::endl;
//        std::cout <<  " lepton_p4[0].phi(): " << lepton_p4[0].phi() <<  std::endl;
//        std::cout << " lepton_id[0]: " << lepton_id[0] << std::endl;
//        std::cout << " lepton_isstar[0]: " << lepton_isstar[0] << std::endl;
//        std::cout <<  " neutrino_p4[0].pt(): " << neutrino_p4[0].pt() <<  std::endl;
//        std::cout <<  " neutrino_p4[0].eta(): " << neutrino_p4[0].eta() <<  std::endl;
//        std::cout <<  " neutrino_p4[0].phi(): " << neutrino_p4[0].phi() <<  std::endl;
//        std::cout << " neutrino_id[0]: " << neutrino_id[0] << std::endl;
//        std::cout << " neutrino_isstar[0]: " << neutrino_isstar[0] << std::endl;
//        std::cout <<  " quark_p4[0].pt(): " << quark_p4[0].pt() <<  std::endl;
//        std::cout <<  " quark_p4[0].eta(): " << quark_p4[0].eta() <<  std::endl;
//        std::cout <<  " quark_p4[0].phi(): " << quark_p4[0].phi() <<  std::endl;
//        std::cout << " quark_id[0]: " << quark_id[0] << std::endl;
//        std::cout << " quark_isstar[0]: " << quark_isstar[0] << std::endl;
//        std::cout <<  " quark_p4[1].pt(): " << quark_p4[1].pt() <<  std::endl;
//        std::cout <<  " quark_p4[1].eta(): " << quark_p4[1].eta() <<  std::endl;
//        std::cout <<  " quark_p4[1].phi(): " << quark_p4[1].phi() <<  std::endl;
//        std::cout << " quark_id[1]: " << quark_id[1] << std::endl;
//        std::cout << " quark_isstar[1]: " << quark_isstar[1] << std::endl;
//        std::cout << " lqq_max_dr: " << lqq_max_dr << std::endl;
//        std::cout << " lq0_dr: " << lq0_dr << std::endl;
//        std::cout << " lq1_dr: " << lq1_dr << std::endl;
//        std::cout << " qq_dr: " << qq_dr << std::endl;
//        std::cout << " decay_dr: " << decay_dr << std::endl;
//        std::cout << " l_qq_dr: " << l_qq_dr << std::endl;
//        std::cout << " lqq_mass: " << lqq_mass << std::endl;
//        std::cout << " lvqq_mt: " << lvqq_mt << std::endl;
//    }

//    for (unsigned ipf = 0; ipf < cms3.pfcands_p4().size(); ++ipf)
//    {
//        const LV& pf_p4 = cms3.pfcands_p4()[ipf];
//        float dr = RooUtil::Calc::DeltaR(pf_p4, recolepton_p4);
//        if (dr < 1.0)
//        {
//            tx->pushbackToBranch<LV>("pf_p4s", pf_p4);
//            tx->pushbackToBranch<float>("pf_drs", dr);
//            std::cout <<  " pf_p4.pt(): " << pf_p4.pt() <<  std::endl;
//            std::cout <<  " pf_p4.eta(): " << pf_p4.eta() <<  std::endl;
//            std::cout <<  " pf_p4.phi(): " << pf_p4.phi() <<  std::endl;
//            std::cout <<  " pf_p4.energy(): " << pf_p4.energy() <<  std::endl;
//            std::cout <<  " pf_p4.mass(): " << pf_p4.mass() <<  std::endl;
//        }
//    }
}

//##############################################################################################################
void babyMaker::FillDeepIsoVariables()
{
    const LV& recolepton_p4 = tx->getBranch<LV>("recolepton_p4", false);
    const float& recolepton_pt = tx->getBranch<float>("recolepton_pt", false);

    const LV& recowhad_p4 = tx->getBranch<LV>("recowhad_p4", false);
    const float& recowhad_pt = tx->getBranch<float>("recowhad_pt", false);

    if (recolepton_pt > 0 && recowhad_pt > 0)
    {
        // Get lepton variables
        const vector<int>& lep_id = tx->getBranch<vector<int>>("lep_id");
        const vector<int>& lep_idx = tx->getBranch<vector<int>>("lep_idx");
        const vector<float>& lep_relIso03EA = tx->getBranch<vector<float>>("lep_relIso03EA");
        const vector<float>& lep_relIso04DB = tx->getBranch<vector<float>>("lep_relIso04DB");
        const vector<float>& lep_miniIsoEA = tx->getBranch<vector<float>>("lep_miniIsoEA");
        bool isMu = abs(lep_id[0]) == 13;
        int lepIdx = lep_idx[0];

        // Fill lepton variables
        tx->setBranch<float>("lepton_eta", recolepton_p4.eta());
        tx->setBranch<float>("lepton_phi", recolepton_p4.phi());
        tx->setBranch<float>("lepton_pt", recolepton_p4.pt());
        tx->setBranch<float>("lepton_relIso03EA", lep_relIso03EA[0]);
        tx->setBranch<float>("lepton_relIso04DB", lep_relIso04DB[0]);
        tx->setBranch<float>("lepton_miniIsoEA", lep_miniIsoEA[0]);
        tx->setBranch<float>("lepton_chiso", isMu ? cms3.mus_isoR03_pf_ChargedHadronPt()[lepIdx] : cms3.els_pfChargedHadronIso()[lepIdx]);
        tx->setBranch<float>("lepton_nhiso", isMu ? cms3.mus_isoR03_pf_NeutralHadronEt()[lepIdx] : cms3.els_pfNeutralHadronIso()[lepIdx]);
        tx->setBranch<float>("lepton_emiso", isMu ? cms3.mus_isoR03_pf_PhotonEt()[lepIdx] : cms3.els_pfPhotonIso()[lepIdx]);
        tx->setBranch<float>("lepton_ncorriso", tx->getBranch<float>("lepton_nhiso") + tx->getBranch<float>("lepton_emiso") - cms3.evt_fixgridfastjet_all_rho() * (isMu ? muEA03(lepIdx, 2) : elEA03(lepIdx, 2)));

        // Configurable variables
        const double coneSize = 0.5;
        const double coneSizeOuter = 1.0;
        const int nAnnuli = 8;
        const double coneSizeAnnuli = 1.0;

        // Variables for output
        vector<float> pf_annuli_energy;
        int lepton_nOuterPf = 0;
        int lepton_nChargedPf = 0;
        int lepton_nPhotonPf = 0;
        int lepton_nNeutralHadPf = 0;

        // Initialization
        for (int i = 0; i < nAnnuli; i++)
            pf_annuli_energy.push_back(0);

        // For finding the bin position
        TH1D* hR = new TH1D("hR", "", nAnnuli, 0.0, coneSizeAnnuli);

        // Begin pf cand loop
        for ( unsigned int pIdx = 0; pIdx < cms3.pfcands_p4().size(); pIdx++ )
        {
            const LV& pCand = cms3.pfcands_p4()[pIdx];
            const LV& pLep = recolepton_p4;
            const double dR = RooUtil::Calc::DeltaR(pLep, pCand);

            if (dR < coneSizeAnnuli)
            {
                int idx = (hR->FindBin(dR))-1;
                pf_annuli_energy[idx] += pCand.pt();
            }

            if (dR > coneSizeOuter)
                continue;

            int pf_pdg_id = cms3.pfcands_particleId()[pIdx];
            int pf_charge = cms3.pfcands_charge()[pIdx];

            // Check if pf cand is lepton itself
            if (abs(pf_pdg_id) == (isMu ? 13 : 11 ) && dR < 0.05)
                continue;

            // Identify charged/photon/neutral hadron
            int candIdx = -1; // 0 = charged, 1 = photon, 2 = neutral hadron
            if (abs(pf_charge) > 0)
                candIdx = 0;
            else if (abs(pf_pdg_id) == 22)
                candIdx = 1;
            else
                candIdx = 2;

            // Count
            if (dR >= coneSize)
            { // outer
                lepton_nOuterPf++;
            }
            else if (candIdx == 0)
            { // inner charged
                lepton_nChargedPf++;
            }
            else if (candIdx == 1)
            { // inner photons
                lepton_nPhotonPf++;
            }
            else if (candIdx == 2)
            { // inner neutral hadrons
                lepton_nNeutralHadPf++;
            }

            // Compute the angle of rotation wrt to lepton and fatjet
            TVector2 new_vec = RooUtil::Calc::getEtaPhiVecRotated(pCand, pLep, recowhad_p4);

            tx->pushbackToBranch<float>("pf_pt", pCand.pt());
            tx->pushbackToBranch<int>("pf_id", candIdx);
            tx->pushbackToBranch<float>("pf_reta", new_vec.Px());
            tx->pushbackToBranch<float>("pf_rphi", new_vec.Py());

        } // end pf cand loop 
        delete hR;

        tx->setBranch<int>("lepton_nChargedPf", lepton_nChargedPf);
        tx->setBranch<int>("lepton_nPhotonPf", lepton_nPhotonPf);
        tx->setBranch<int>("lepton_nNeutralHadPf", lepton_nNeutralHadPf);
        tx->setBranch<vector<float>>("pf_annuli_energy", pf_annuli_energy);

        int nvtx = 0;
        for ( unsigned int ivtx = 0; ivtx < cms3.evt_nvtxs(); ivtx++ )
            if ( isGoodVertex( ivtx ) ) nvtx++;
        tx->setBranch<int>("nvtx", nvtx);
    }
}

//##############################################################################################################
void babyMaker::FillHighPtSingleLeptonTrigger()
{
    // Triggers
    int HLT_Ele40_WPTight_Gsf = passHLTTriggerPattern("HLT_Ele40_WPTight_Gsf_v");
    int HLT_Mu50 = passHLTTriggerPattern("HLT_Mu50_v");
    int HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165 = passHLTTriggerPattern("HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165_v");
    int HLT_TkMu50 = passHLTTriggerPattern("HLT_TkMu50_v");
    int HLT_AK8PFHT700_TrimR0p1PT0p03Mass50 = passHLTTriggerPattern("HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v");
    int HLT_AK8PFJet360_TrimMass30 = passHLTTriggerPattern("HLT_AK8PFJet360_TrimMass30_v");
    int HLT_PFHT800 = passHLTTriggerPattern("HLT_PFHT800_v");
    int HLT_PFHT900 = passHLTTriggerPattern("HLT_PFHT900_v");
    int HLT_PFHT650_WideJetMJJ900DEtaJJ1p5 = passHLTTriggerPattern("HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_v");
    int HLT_PFHT650_WideJetMJJ950DEtaJJ1p5 = passHLTTriggerPattern("HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_v");
    int HLT_AK8PFDiJet280_200_TrimMass30_CSVM_0p20 = passHLTTriggerPattern("HLT_AK8PFDiJet280_200_TrimMass30_CSVM_0p20_v");

    tx->setBranch<int>("HLT_SingleEl40", HLT_Ele40_WPTight_Gsf);
    tx->setBranch<int>("HLT_SingleMu50", HLT_Mu50);
    tx->setBranch<int>("HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165", HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165);
    tx->setBranch<int>("HLT_TkMu50", HLT_TkMu50);
    tx->setBranch<int>("HLT_AK8PFHT700_TrimR0p1PT0p03Mass50", HLT_AK8PFHT700_TrimR0p1PT0p03Mass50);
    tx->setBranch<int>("HLT_AK8PFJet360_TrimMass30", HLT_AK8PFJet360_TrimMass30);
    tx->setBranch<int>("HLT_PFHT800", HLT_PFHT800);
    tx->setBranch<int>("HLT_PFHT900", HLT_PFHT900);
    tx->setBranch<int>("HLT_PFHT650_WideJetMJJ900DEtaJJ1p5", HLT_PFHT650_WideJetMJJ900DEtaJJ1p5);
    tx->setBranch<int>("HLT_PFHT650_WideJetMJJ950DEtaJJ1p5", HLT_PFHT650_WideJetMJJ950DEtaJJ1p5);
    tx->setBranch<int>("HLT_AK8PFDiJet280_200_TrimMass30_CSVM_0p20", HLT_AK8PFDiJet280_200_TrimMass30_CSVM_0p20);

    int pass_duplicate_se_sm = 0;
    int pass_duplicate_sm_se = 0;
    tx->setBranch<int>("pass_duplicate_se_sm", pass_duplicate_se_sm);
    tx->setBranch<int>("pass_duplicate_sm_se", pass_duplicate_sm_se);
}

//##############################################################################################################
void babyMaker::FillIsolatedSingleLeptonTrigger()
{
    tx->setBranch<int>("HLT_Ele27_WPLoose_Gsf", passHLTTriggerPattern("HLT_Ele27_WPLoose_Gsf_v"));
    tx->setBranch<int>("HLT_Ele30_WPLoose_Gsf", passHLTTriggerPattern("HLT_Ele30_WPLoose_Gsf_v"));
    tx->setBranch<int>("HLT_Ele45_WPLoose_Gsf", passHLTTriggerPattern("HLT_Ele45_WPLoose_Gsf_v"));
    tx->setBranch<int>("HLT_Ele105_CaloIdVT_GsfTrkIdT", passHLTTriggerPattern("HLT_Ele105_CaloIdVT_GsfTrkIdT_v"));
    tx->setBranch<int>("HLT_Ele115_CaloIdVT_GsfTrkIdT", passHLTTriggerPattern("HLT_Ele115_CaloIdVT_GsfTrkIdT_v"));

    // Muon
    tx->setBranch<int>("HLT_IsoTkMu24", passHLTTriggerPattern("HLT_IsoTkMu24_v"));
    tx->setBranch<int>("HLT_IsoMu24", passHLTTriggerPattern("HLT_IsoMu24_v"));
}

//##############################################################################################################
void babyMaker::FillOverlapRemovedBveto()
{

    const LV& recowhad_p4 = tx->getBranch<LV>("recowhad_p4", false);
    const float& recowhad_pt = tx->getBranch<float>("recowhad_pt", false);

    const LV& recolepton_p4 = tx->getBranch<LV>("recolepton_p4", false);
    const float& recolepton_pt = tx->getBranch<float>("recolepton_pt", false);

    if (recowhad_pt > 0 && recolepton_pt > 0)
    {

        int nbOR = 0;
        int nbORmed = 0;
        int nbORtight = 0;
        int nbOR50 = 0;
        int nbOR50med = 0;
        int nbOR50tight = 0;
        int nbOR40 = 0;
        int nbOR40med = 0;
        int nbOR40tight = 0;
        int nbOR30 = 0;
        int nbOR30med = 0;
        int nbOR30tight = 0;
        float htOR = 0;
        float htOR40 = 0;
        float htOR50 = 0;
        LV v_mhOR;
        LV v_mhOR40;
        LV v_mhOR50;
        bool overlapping_lepton_found = false;

        for (unsigned ijet = 0; ijet < coreJet.index.size(); ++ijet)
        {
            int idx = coreJet.index[ijet];
            float corr = coreJet.corrs[ijet];
            float shift = coreJet.shifts[ijet];
            float current_csv_val = cms3.getbtagvalue("pfCombinedInclusiveSecondaryVertexV2BJetTags", idx);
            LorentzVector jet = cms3.pfjets_p4()[idx] * cms3.pfjets_undoJEC()[idx] * corr;

            // Check whether this jet overlaps with any of the leptons
            if (isLeptonOverlappingWithJet(ijet))
                continue;

            if (RooUtil::Calc::DeltaR(recowhad_p4, jet) > 0.8)
            {
                // nbOR jets
                if (jet.pt() > 20.)
                {
                    if (fabs(jet.eta()) < 2.4 && current_csv_val >= 0.5426)
                        nbOR++;
                    if (fabs(jet.eta()) < 2.4 && current_csv_val >= 0.8484)
                        nbORmed++;
                    if (fabs(jet.eta()) < 2.4 && current_csv_val >= 0.9535)
                        nbORtight++;
                }

                // nbOR jets
                if (jet.pt() > 30.)
                {
                    if (fabs(jet.eta()) < 2.4 && current_csv_val >= 0.5426)
                        nbOR30++;
                    if (fabs(jet.eta()) < 2.4 && current_csv_val >= 0.8484)
                        nbOR30med++;
                    if (fabs(jet.eta()) < 2.4 && current_csv_val >= 0.9535)
                        nbOR30tight++;
                }

                // nbOR jets
                if (jet.pt() > 40.)
                {
                    if (fabs(jet.eta()) < 2.4 && current_csv_val >= 0.5426)
                        nbOR40++;
                    if (fabs(jet.eta()) < 2.4 && current_csv_val >= 0.8484)
                        nbOR40med++;
                    if (fabs(jet.eta()) < 2.4 && current_csv_val >= 0.9535)
                        nbOR40tight++;
                }

                // nbOR jets
                if (jet.pt() > 50.)
                {
                    if (fabs(jet.eta()) < 2.4 && current_csv_val >= 0.5426)
                        nbOR50++;
                    if (fabs(jet.eta()) < 2.4 && current_csv_val >= 0.8484)
                        nbOR50med++;
                    if (fabs(jet.eta()) < 2.4 && current_csv_val >= 0.9535)
                        nbOR50tight++;
                }
            }

            if (jet.pt() > 30 && fabs(jet.eta()) < 2.4)
            {
                htOR += jet.pt();
                v_mhOR += jet;
            }
            if (jet.pt() > 40 && fabs(jet.eta()) < 2.4)
            {
                htOR40 += jet.pt();
                v_mhOR40 += jet;
            }
            if (jet.pt() > 50 && fabs(jet.eta()) < 2.4)
            {
                htOR50 += jet.pt();
                v_mhOR50 += jet;
            }

            if (RooUtil::Calc::DeltaR(recolepton_p4, jet) < 0.3)
            {
                overlapping_lepton_found = true;
            }

        }

        if (overlapping_lepton_found)
        {
            htOR -= recolepton_pt;
            htOR40 -= recolepton_pt;
            htOR50 -= recolepton_pt;
        }

        tx->setBranch<int>("nbOR", nbOR);
        tx->setBranch<int>("nbORmed", nbORmed);
        tx->setBranch<int>("nbORtight", nbORtight);
        tx->setBranch<int>("nbOR30", nbOR30);
        tx->setBranch<int>("nbOR30med", nbOR30med);
        tx->setBranch<int>("nbOR30tight", nbOR30tight);
        tx->setBranch<int>("nbOR40", nbOR40);
        tx->setBranch<int>("nbOR40med", nbOR40med);
        tx->setBranch<int>("nbOR40tight", nbOR40tight);
        tx->setBranch<int>("nbOR50", nbOR50);
        tx->setBranch<int>("nbOR50med", nbOR50med);
        tx->setBranch<int>("nbOR50tight", nbOR50tight);
        tx->setBranch<float>("htOR", htOR);
        tx->setBranch<float>("htOR40", htOR40);
        tx->setBranch<float>("htOR50", htOR50);
        tx->setBranch<float>("mhOR", v_mhOR.mass());
        tx->setBranch<float>("mhOR40", v_mhOR40.mass());
        tx->setBranch<float>("mhOR50", v_mhOR50.mass());
    }
}

//##############################################################################################################
void babyMaker::FillRecoISR()
{
    float met_pt = tx->getBranch<float>("met_pt");
    float met_phi = tx->getBranch<float>("met_phi");
    const vector<LV>& jets_p4 = tx->getBranch<vector<LV>>("jets_p4", false);
    if (jets_p4.size() > 0)
    {
        // Choose leading jet with delta phi at least 90 degrees away (i.e. other hemi-sphere)
        LV single_isr_jet;
        bool single_isr_jet_found = false;
        for (unsigned int ijet = 0; ijet < jets_p4.size(); ++ijet)
        {
            const LV& jet_p4 = jets_p4[ijet];
            float dphi = fabs(TVector2::Phi_mpi_pi(met_phi-jet_p4.phi()));
            if (dphi > TMath::Pi() / 2.)
            {
                single_isr_jet = jet_p4;
                single_isr_jet_found = true;
                break;
            }
        }

        if (single_isr_jet_found)
        {
            tx->setBranch<LV>("recoisr_p4", single_isr_jet);
            tx->setBranch<float>("recoisr_pt", single_isr_jet.pt());
            tx->setBranch<float>("recoisr_eta", single_isr_jet.eta());
            tx->setBranch<float>("recoisr_phi", single_isr_jet.phi());
        }
        else
        {
            LV leadjet = jets_p4[0];
            tx->setBranch<LV>("recoisr_p4", leadjet);
            tx->setBranch<float>("recoisr_pt", leadjet.pt());
            tx->setBranch<float>("recoisr_eta", leadjet.eta());
            tx->setBranch<float>("recoisr_phi", leadjet.phi());
        }

        // Choose leading jet with delta phi at least 90 degrees away (i.e. other hemi-sphere)
        LV megajet;
        LV megajet_n2;
        int megajet_multiplicity = 0;
        for (unsigned int ijet = 0; ijet < jets_p4.size(); ++ijet)
        {
            const LV& jet_p4 = jets_p4[ijet];
            float dphi = fabs(TVector2::Phi_mpi_pi(met_phi-jet_p4.phi()));
            if (dphi > TMath::Pi() / 2.)
            {
                megajet += jet_p4;
                if (megajet_multiplicity < 2)
                {
                    megajet_n2 += jet_p4;
                    megajet_multiplicity++;
                }
            }
        }

        if (single_isr_jet_found)
        {
            tx->setBranch<LV>("recoisrmegajet_p4", megajet);
            tx->setBranch<float>("recoisrmegajet_pt", megajet.pt());
            tx->setBranch<float>("recoisrmegajet_eta", megajet.eta());
            tx->setBranch<float>("recoisrmegajet_phi", megajet.phi());
            tx->setBranch<LV>("recoisrmegajet_n2_p4", megajet_n2);
            tx->setBranch<float>("recoisrmegajet_n2_pt", megajet_n2.pt());
            tx->setBranch<float>("recoisrmegajet_n2_eta", megajet_n2.eta());
            tx->setBranch<float>("recoisrmegajet_n2_phi", megajet_n2.phi());
        }
        else
        {
            LV leadjet = jets_p4[0];
            tx->setBranch<LV>("recoisrmegajet_p4", leadjet);
            tx->setBranch<float>("recoisrmegajet_pt", leadjet.pt());
            tx->setBranch<float>("recoisrmegajet_eta", leadjet.eta());
            tx->setBranch<float>("recoisrmegajet_phi", leadjet.phi());
            tx->setBranch<LV>("recoisrmegajet_n2_p4", leadjet);
            tx->setBranch<float>("recoisrmegajet_n2_pt", leadjet.pt());
            tx->setBranch<float>("recoisrmegajet_n2_eta", leadjet.eta());
            tx->setBranch<float>("recoisrmegajet_n2_phi", leadjet.phi());
        }
    }
}

//##############################################################################################################
void babyMaker::FillRecoWhad()
{

    const vector<LV>& ak8jets_p4 = tx->getBranch<vector<LV>>("ak8jets_p4", false);
    const float& met_phi = tx->getBranch<float>("met_phi");

    if (ak8jets_p4.size() == 0)
        return;

    int fatjetidx = -1;
    float max_pt = 0;
    float min_dphi = 999;
    for (unsigned int ifatjet = 0; ifatjet < ak8jets_p4.size(); ++ifatjet)
    {
        const LV& p4 = ak8jets_p4[ifatjet];
        float dphi = fabs(TVector2::Phi_mpi_pi(met_phi - p4.phi()));
//        if (dphi < TMath::Pi() / 2. && max_pt < p4.pt())
//        {
//            fatjetidx = ifatjet;
//            max_pt = p4.pt();
//        }
        if (min_dphi > dphi)
        {
            fatjetidx = ifatjet;
            max_pt = p4.pt();
            min_dphi = dphi;
        }
    }

    if (fatjetidx >= 0)
    {
        const LV& p4 = ak8jets_p4[fatjetidx];
        tx->setBranch<LV>("recowhad_p4", p4);
        tx->setBranch<float>("recowhad_pt", p4.pt());
        tx->setBranch<float>("recowhad_eta", p4.eta());
        tx->setBranch<float>("recowhad_phi", p4.phi());
        tx->setBranch<float>("recowhad_mass", tx->getBranch<vector<float>>("ak8jets_mass")[fatjetidx]);
        tx->setBranch<float>("recowhad_softdropMass", tx->getBranch<vector<float>>("ak8jets_softdropMass")[fatjetidx]);
        tx->setBranch<float>("recowhad_prunedMass", tx->getBranch<vector<float>>("ak8jets_prunedMass")[fatjetidx]);
        tx->setBranch<float>("recowhad_nJettinessTau1", tx->getBranch<vector<float>>("ak8jets_nJettinessTau1")[fatjetidx]);
        tx->setBranch<float>("recowhad_nJettinessTau2", tx->getBranch<vector<float>>("ak8jets_nJettinessTau2")[fatjetidx]);
        tx->setBranch<float>("recowhad_puppi_softdropMass", tx->getBranch<vector<float>>("ak8jets_puppi_softdropMass")[fatjetidx]);
        tx->setBranch<float>("recowhad_puppi_pt", tx->getBranch<vector<float>>("ak8jets_puppi_pt")[fatjetidx]);
        tx->setBranch<float>("recowhad_puppi_eta", tx->getBranch<vector<float>>("ak8jets_puppi_eta")[fatjetidx]);
        tx->setBranch<float>("recowhad_puppi_phi", tx->getBranch<vector<float>>("ak8jets_puppi_phi")[fatjetidx]);
        tx->setBranch<float>("recowhad_puppi_mass", tx->getBranch<vector<float>>("ak8jets_puppi_mass")[fatjetidx]);
        tx->setBranch<float>("recowhad_puppi_nJettinessTau1", tx->getBranch<vector<float>>("ak8jets_puppi_nJettinessTau1")[fatjetidx]);
        tx->setBranch<float>("recowhad_puppi_nJettinessTau2", tx->getBranch<vector<float>>("ak8jets_puppi_nJettinessTau2")[fatjetidx]);
        tx->setBranch<float>("recowhad_softdropPuppiSubjet1", tx->getBranch<vector<float>>("ak8jets_softdropPuppiSubjet1")[fatjetidx]);
        tx->setBranch<float>("recowhad_softdropPuppiSubjet2", tx->getBranch<vector<float>>("ak8jets_softdropPuppiSubjet2")[fatjetidx]);
    }
}

//##############################################################################################################
void babyMaker::FillRecoLepton()
{

    const vector<LV>& lep_p4 = tx->getBranch<vector<LV>>("lep_p4", false);
    const vector<int>& lep_id = tx->getBranch<vector<int>>("lep_id", false);
    const float& met_phi = tx->getBranch<float>("met_phi", false);
    const float& met_pt = tx->getBranch<float>("met_pt", false);

    if (lep_p4.size() == 0)
        return;

    int lepidx = -1;
//    float max_pt = 0;
//    for (unsigned int ilep = 0; ilep < lep_p4.size(); ++ilep)
//    {
//        const LV& p4 = lep_p4[ilep];
//        float dphi = fabs(TVector2::Phi_mpi_pi(met_phi - p4.phi()));
//        if (dphi < TMath::Pi() / 2. && max_pt < p4.pt())
//        {
//            lepidx = ilep;
//            max_pt = p4.pt();
//        }
//    }

    lepidx = 0; // just choose leading

    if (lepidx >= 0)
    {
        const LV& p4 = lep_p4[lepidx];
        tx->setBranch<LV>("recolepton_p4", p4);
        tx->setBranch<int>("recolepton_id", lep_id[lepidx]);
        tx->setBranch<float>("recolepton_pt", p4.pt());
        tx->setBranch<float>("recolepton_eta", p4.eta());
        tx->setBranch<float>("recolepton_phi", p4.phi());
        float phi1 = p4.phi();
        float phi2 = met_phi;
        float Et1  = p4.pt();
        float Et2  = met_pt;
        float mt = sqrt(2*Et1*Et2*(1.0 - cos(phi1-phi2)));
        tx->setBranch<float>("recolepton_mt", mt);
        tx->setBranch<float>("recolepton_met_dphi", TVector2::Phi_mpi_pi(met_phi - p4.phi()));

        // Determination of the Wlep mass
        // The recoisrmegajet_p4 is the proxy for the Higgs pt.
        // Then from the Higgs proxy pt, check whether met_pt + lepton_pt < recoisrmegajet_pt / 2
        const float& recoisrmegajet_pt = tx->getBranch<float>("recoisrmegajet_pt", false);
        if (recoisrmegajet_pt > 0)
        {
            float ratio = (p4.pt() + met_pt) / recoisrmegajet_pt;
            int recoiswleplead = ratio > 0.5;
            tx->setBranch<int>("recoiswleplead", recoiswleplead);
        }

        const int& recoiswleplead = tx->getBranch<int>("recoiswleplead", false);
        float mw = recoiswleplead == 0 ? 45 : 80.385;
        LV vp4 = RooUtil::Calc::getNeutrinoP4(p4, met_pt, met_phi, mw);
        float det = RooUtil::Calc::getNeutrinoPzDet(p4, met_pt, met_phi, mw);
        tx->setBranch<float>("reconeutrino_det", det);
        tx->setBranch<LV>("reconeutrino_p4", vp4);
        tx->setBranch<float>("reconeutrino_pt", vp4.pt());
        tx->setBranch<float>("reconeutrino_eta", vp4.eta());
        tx->setBranch<float>("reconeutrino_phi", vp4.phi());
        tx->setBranch<float>("reconeutrino_met_dphi", TVector2::Phi_mpi_pi(met_phi - vp4.phi()));
        LV vp42 = RooUtil::Calc::getNeutrinoP4(p4, met_pt, met_phi, mw, true);
        tx->setBranch<LV>("reconeutrino2_p4", vp42);
        tx->setBranch<float>("reconeutrino2_pt", vp42.pt());
        tx->setBranch<float>("reconeutrino2_eta", vp42.eta());
        tx->setBranch<float>("reconeutrino2_phi", vp42.phi());
        tx->setBranch<float>("reconeutrino2_met_dphi", TVector2::Phi_mpi_pi(met_phi - vp42.phi()));
        LV vp4inv = RooUtil::Calc::getNeutrinoP4(p4, met_pt, met_phi, mw, false, true);
        tx->setBranch<LV>("reconeutrinoinv_p4", vp4inv);
        tx->setBranch<float>("reconeutrinoinv_pt", vp4inv.pt());
        tx->setBranch<float>("reconeutrinoinv_eta", vp4inv.eta());
        tx->setBranch<float>("reconeutrinoinv_phi", vp4inv.phi());
        tx->setBranch<float>("reconeutrinoinv_met_dphi", TVector2::Phi_mpi_pi(met_phi - vp4inv.phi()));
    }
}

//##############################################################################################################
void babyMaker::FillRecoLeadJet()
{

    return;

//    const vector<LV>& jets_p4 = tx->getBranch<vector<LV>>("jets_p4", false);
//    const float& met_phi = tx->getBranch<float>("met_phi", false);
//    const float& met_pt = tx->getBranch<float>("met_pt", false);
//
//    if (jets_p4.size() == 0)
//        return;
//
//    int jetidx = -1;
//
//    lepidx = 0; // just choose leading
//
//    if (lepidx >= 0)
//    {
//        const LV& p4 = lep_p4[lepidx];
//        tx->setBranch<LV>("recolepton_p4", p4);
//        tx->setBranch<int>("recolepton_id", lep_id[lepidx]);
//        tx->setBranch<float>("recolepton_pt", p4.pt());
//        tx->setBranch<float>("recolepton_eta", p4.eta());
//        tx->setBranch<float>("recolepton_phi", p4.phi());
//        float phi1 = p4.phi();
//        float phi2 = met_phi;
//        float Et1  = p4.pt();
//        float Et2  = met_pt;
//        float mt = sqrt(2*Et1*Et2*(1.0 - cos(phi1-phi2)));
//        tx->setBranch<float>("recolepton_mt", mt);
//        tx->setBranch<float>("recolepton_met_dphi", TVector2::Phi_mpi_pi(met_phi - p4.phi()));
//
//        // Determination of the Wlep mass
//        // The recoisrmegajet_p4 is the proxy for the Higgs pt.
//        // Then from the Higgs proxy pt, check whether met_pt + lepton_pt < recoisrmegajet_pt / 2
//        const float& recoisrmegajet_pt = tx->getBranch<float>("recoisrmegajet_pt", false);
//        if (recoisrmegajet_pt > 0)
//        {
//            float ratio = p4.pt() + met_pt / recoisrmegajet_pt;
//            int recoiswleplead = ratio > 0.5;
//            tx->setBranch<int>("recoiswleplead", recoiswleplead);
//        }
//
//        const int& recoiswleplead = tx->getBranch<int>("recoiswleplead", false);
//        float mw = recoiswleplead == 0 ? 45 : 80.385;
//        LV vp4 = RooUtil::Calc::getNeutrinoP4(p4, met_pt, met_phi, mw);
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
//    }
}

//##############################################################################################################
void babyMaker::FillRecoVariables()
{
    const LV& recolepton_p4 = tx->getBranch<LV>("recolepton_p4", false);
    const LV& recowhad_p4 = tx->getBranch<LV>("recowhad_p4", false);
    const float& recolepton_pt = tx->getBranch<float>("recolepton_pt", false);
    const float& recowhad_pt = tx->getBranch<float>("recowhad_pt", false);
    const float& recowhad_mass = tx->getBranch<float>("recowhad_mass", false);
    if (recowhad_pt > 0 && recolepton_pt > 0)
    {
        float dr = RooUtil::Calc::DeltaR(recolepton_p4, recowhad_p4);
        tx->setBranch<float>("recolepton_recowhad_dr", dr);

        LV recowhad_minus_recolepton_p4 = recowhad_p4 - recolepton_p4;
        tx->setBranch<LV>("recowhad_minus_recolepton_p4", recowhad_minus_recolepton_p4);
        tx->setBranch<float>("recowhad_minus_recolepton_pt", recowhad_minus_recolepton_p4.pt());
        tx->setBranch<float>("recowhad_minus_recolepton_eta", recowhad_minus_recolepton_p4.eta());
        tx->setBranch<float>("recowhad_minus_recolepton_phi", recowhad_minus_recolepton_p4.phi());
        tx->setBranch<float>("recowhad_minus_recolepton_mass", recowhad_minus_recolepton_p4.mass());

        LV recowhad_minus_recolepton_positive_p4 = recowhad_minus_recolepton_p4.mass() > 0 ? recowhad_minus_recolepton_p4 : recowhad_p4;
        float recowhad_minus_recolepton_positive_mass = recowhad_minus_recolepton_positive_p4.mass() > 0 ? recowhad_minus_recolepton_positive_p4.mass() : recowhad_mass;
        tx->setBranch<LV>("recowhad_minus_recolepton_positive_p4", recowhad_minus_recolepton_positive_p4);
        tx->setBranch<float>("recowhad_minus_recolepton_positive_pt", recowhad_minus_recolepton_positive_p4.pt());
        tx->setBranch<float>("recowhad_minus_recolepton_positive_eta", recowhad_minus_recolepton_positive_p4.eta());
        tx->setBranch<float>("recowhad_minus_recolepton_positive_phi", recowhad_minus_recolepton_positive_p4.phi());
        tx->setBranch<float>("recowhad_minus_recolepton_positive_mass", recowhad_minus_recolepton_positive_mass);
    }
}

//##############################################################################################################
void babyMaker::FillRecoWlep()
{
    const LV& recolepton_p4 = tx->getBranch<LV>("recolepton_p4", false);
    const float& recolepton_pt = tx->getBranch<float>("recolepton_pt", false);
    const float& met_phi = tx->getBranch<float>("met_phi", false);
    const float& met_pt = tx->getBranch<float>("met_pt", false);
    if (recolepton_pt > 0)
    {
        TLorentzVector met_tlv;
        met_tlv.SetPtEtaPhiM(met_pt, 0, met_phi, 0);
        LV met = RooUtil::Calc::getLV(met_tlv);
        const LV recowlep_p4 = recolepton_p4 + met;
        tx->setBranch<LV>("recowlep_p4", recowlep_p4);
        tx->setBranch<float>("recowlep_pt", recowlep_p4.pt());
        tx->setBranch<float>("recowlep_eta", recowlep_p4.eta());
        tx->setBranch<float>("recowlep_phi", recowlep_p4.phi());
        tx->setBranch<float>("recowlep_mass", recowlep_p4.mass());
    }
}

//##############################################################################################################
void babyMaker::FillTruthLevelStudyVariables()
{
    ProcessGenParticles();
    if (isHWWlvjj())
    {
        FillTruthLevelStudyVariables_HWWlvjj();
    }
    if (isHbb())
    {
        FillTruthLevelStudyVariables_Hbb();
    }
}

//##############################################################################################################
bool babyMaker::FillTruthLevelStudyVariables_HWWlvjj()
{
    const vector<int>& genPart_idx = coreGenPart.genPart_idx;
    const vector<int>& genPart_pdgId = coreGenPart.genPart_pdgId;
    const vector<int>& genPart_status = coreGenPart.genPart_status;
    const vector<int>& genPart_motherId = coreGenPart.genPart_motherId;
    const vector<int>& genPart_grandmaId = coreGenPart.genPart_grandmaId;
    const vector<LV>& genPart_p4 = coreGenPart.genPart_p4;

    for (unsigned int i = 0; i < cms3.genps_p4().size(); ++i)
    {
        if (cms3.genps_id_simplemother()[i] == 21 && cms3.genps_id_simplegrandma()[i] == 2212 && cms3.genps_status()[i] == 23)
        {
//            coreGenPart.printParticle(i);
//            coreGenPart.printAllParticles();
            tx->setBranch<LV>("isr_p4", cms3.genps_p4()[i]);
            tx->setBranch<float>("isr_pt", cms3.genps_p4()[i].pt());
            tx->setBranch<float>("isr_eta", cms3.genps_p4()[i].eta());
            tx->setBranch<float>("isr_phi", cms3.genps_p4()[i].phi());
            break;
        }
    }

    std::vector<CoreUtil::genpart::Higgs> higgses = coreGenPart.reconstructHWWlvjj();

    // Sanity check
    if (higgses.size() != 1)
    {
        std::cout <<  " higgses.size(): " << higgses.size() <<  std::endl;
        coreGenPart.printAllParticles();
    }

    if (higgses[0].HiggsDaughters.size() != 2)
    {
        std::cout <<  " higgses[0].HiggsDaughters.size(): " << higgses[0].HiggsDaughters.size() <<  std::endl;
        coreGenPart.printAllParticles();
    }

    if (higgses[0].HiggsGrandDaughters.size() != 4)
    {
        std::cout <<  " higgses[0].HiggsGrandDaughters.size(): " << higgses[0].HiggsGrandDaughters.size() <<  std::endl;
        coreGenPart.printAllParticles();
    }

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


    if (higgsdecay_id.size() != 2)
    {
        std::cout <<  " looper.getCurrentEventIndex(): " << looper.getCurrentEventIndex() <<  std::endl;
        std::cout <<  " higgsdecay_id.size(): " << higgsdecay_id.size() <<  std::endl;
        coreGenPart.printParticleOfInterest();
        exit(255);
    }

    if (lepton_id.size() != 1)
    {
        std::cout <<  " looper.getCurrentEventIndex(): " << looper.getCurrentEventIndex() <<  std::endl;
        std::cout <<  " lepton_id.size(): " << lepton_id.size() <<  " quark_id.size(): " << quark_id.size() <<  std::endl;
        for (unsigned int ii = 0; ii < lepton_id.size(); ++ ii)
            std::cout <<  " lepton_id[ii]: " << lepton_id[ii] <<  " lepton_p4[ii].pt(): " << lepton_p4[ii].pt() <<  std::endl;

        coreGenPart.printParticleOfInterest();
        coreGenPart.printAllParticles();

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

    if (quark_id.size() != 2)
    {
        std::cout <<  " looper.getCurrentEventIndex(): " << looper.getCurrentEventIndex() <<  std::endl;
        std::cout <<  " lepton_id.size(): " << lepton_id.size() <<  " quark_id.size(): " << quark_id.size() <<  std::endl;
        coreGenPart.printParticleOfInterest();
        exit(255);
    }

    // Save information for H
    tx->setBranch<LV>("higgs_p4", higgs_p4[0]);

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
    if (abs(higgsdecay_id[0]) != 24) return true;

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
        FATALERROR(__FUNCTION__);
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

//    // Now start boosting things to normalize to certain set higgs pt
//    FillReBoostedVariables("lepton" , 0    , higgs_p4[0] , lepton_p4     , lepton_id     , lepton_isstar    , deta0   , dphi0   );
//    FillReBoostedVariables("lepton" , 250  , higgs_p4[0] , lepton_p4     , lepton_id     , lepton_isstar    , deta250 , dphi250 );
//    FillReBoostedVariables("lepton" , 500  , higgs_p4[0] , lepton_p4     , lepton_id     , lepton_isstar    , deta500 , dphi500 );
//    FillReBoostedVariables("lepton" , 1000 , higgs_p4[0] , lepton_p4     , lepton_id     , lepton_isstar    , deta1000, dphi1000);
//    FillReBoostedVariables("lepton" , 1500 , higgs_p4[0] , lepton_p4     , lepton_id     , lepton_isstar    , deta1500, dphi1500);
//    FillReBoostedVariables("quark"  , 0    , higgs_p4[0] , quark_p4      , quark_id      , quark_isstar     , deta0   , dphi0    );
//    FillReBoostedVariables("quark"  , 250  , higgs_p4[0] , quark_p4      , quark_id      , quark_isstar     , deta250 , dphi250  );
//    FillReBoostedVariables("quark"  , 500  , higgs_p4[0] , quark_p4      , quark_id      , quark_isstar     , deta500 , dphi500  );
//    FillReBoostedVariables("quark"  , 1000 , higgs_p4[0] , quark_p4      , quark_id      , quark_isstar     , deta1000, dphi1000 );
//    FillReBoostedVariables("quark"  , 1500 , higgs_p4[0] , quark_p4      , quark_id      , quark_isstar     , deta1500, dphi1500 );

    FillDecayProductsDRVariables(-1); // nominal
//    FillDecayProductsDRVariables(250);
//    FillDecayProductsDRVariables(500);
//    FillDecayProductsDRVariables(1000);
//    FillDecayProductsDRVariables(1500);

    if ((lepton_isstar[0] == 0) && (higgsdecay_isstar[0] == 0))
    {
        tx->setBranch<int>("wstar_channel_id", 0);
    }
    else if ((lepton_isstar[0] == 1) && (higgsdecay_isstar[0] == 1))
    {
        tx->setBranch<int>("wstar_channel_id", 1);
    }
    else if ((lepton_isstar[0] == 0) && (higgsdecay_isstar[1] == 0))
    {
        tx->setBranch<int>("wstar_channel_id", 2);
    }
    else if ((lepton_isstar[0] == 1) && (higgsdecay_isstar[1] == 1))
    {
        tx->setBranch<int>("wstar_channel_id", 3);
    }
    else
    {
        coreGenPart.printParticleOfInterest();
        std::cout <<  " higgsdecay_p4[0].mass(): " << higgsdecay_p4[0].mass() <<  std::endl;
        std::cout <<  " higgsdecay_p4[1].mass(): " << higgsdecay_p4[1].mass() <<  std::endl;
        std::cout <<  " higgsdecay_isstar[0]: " << higgsdecay_isstar[0] <<  std::endl;
        std::cout <<  " higgsdecay_isstar[1]: " << higgsdecay_isstar[1] <<  std::endl;
        std::cout << "Failed to classify events" << std::endl;
        FATALERROR(__FUNCTION__);
    }

    // lqq mass
    tx->setBranch<float>("lqq_mass", (lepton_p4[0] + quark_p4[0] + quark_p4[1]).mass());
    tx->setBranch<float>("lvqq_mt", (lepton_p4[0] + neutrino_p4[0] + quark_p4[0] + quark_p4[1]).mt());


    return true;

}

//##############################################################################################################
bool babyMaker::FillTruthLevelStudyVariables_Hbb()
{
    const vector<int>& genPart_idx = coreGenPart.genPart_idx;
    const vector<int>& genPart_pdgId = coreGenPart.genPart_pdgId;
    const vector<int>& genPart_status = coreGenPart.genPart_status;
    const vector<int>& genPart_motherId = coreGenPart.genPart_motherId;
    const vector<int>& genPart_grandmaId = coreGenPart.genPart_grandmaId;
    const vector<LV>& genPart_p4 = coreGenPart.genPart_p4;

    std::vector<CoreUtil::genpart::Higgs> higgses = coreGenPart.reconstructHbb();

    // Sanity check
    if (higgses.size() != 1)
    {
        std::cout <<  " higgses.size(): " << higgses.size() <<  std::endl;
        coreGenPart.printAllParticles();
    }

    if (higgses[0].HiggsDaughters.size() != 2)
    {
        std::cout <<  " higgses[0].HiggsDaughters.size(): " << higgses[0].HiggsDaughters.size() <<  std::endl;
        coreGenPart.printAllParticles();
    }

    vector<LV> higgs_p4;

    vector<LV> higgsdecay_p4;
    vector<int> higgsdecay_id;
    vector<int> higgsdecay_isstar;

    higgs_p4.push_back(higgses[0].p4);

    for (unsigned int i = 0; i < higgses[0].HiggsDaughters.size(); ++i)
    {
        higgsdecay_p4.push_back(higgses[0].HiggsDaughters[i].p4);
        higgsdecay_id.push_back(higgses[0].HiggsDaughters[i].id);
        higgsdecay_isstar.push_back(higgses[0].HiggsDaughters[i].isstar);
    }

    if (higgsdecay_id.size() != 2)
    {
        std::cout <<  " looper.getCurrentEventIndex(): " << looper.getCurrentEventIndex() <<  std::endl;
        std::cout <<  " higgsdecay_id.size(): " << higgsdecay_id.size() <<  std::endl;
        coreGenPart.printParticleOfInterest();
        exit(255);
    }

    // Save information for H
    tx->setBranch<LV>("higgs_p4", higgs_p4[0]);

    // Save information for H->XX
    tx->setBranch<int>("higgsdecay", abs(higgsdecay_id[0]));
    tx->setBranch<vector<LV>>("decay_p4", higgsdecay_p4);
    tx->setBranch<vector<int>>("decay_id", higgsdecay_id);
    tx->setBranch<vector<int>>("decay_isstar", higgsdecay_isstar);
    tx->sortVecBranchesByPt("decay_p4", {}, {"decay_id", "decay_isstar"}, {});

    // Compute and fill the boosted variables as well as toe rotation
    // This also returns the reference vector
    float deta0, dphi0;
    float deta250, dphi250;
    float deta500, dphi500;
    float deta1000, dphi1000;
    float deta1500, dphi1500;
    std::tie(deta0, dphi0) = FillReBoostedVariables("decay"  , 0  , higgs_p4[0] , higgsdecay_p4 , higgsdecay_id , higgsdecay_isstar );
    std::tie(deta250, dphi250) = FillReBoostedVariables("decay"  , 250  , higgs_p4[0] , higgsdecay_p4 , higgsdecay_id , higgsdecay_isstar );
    std::tie(deta500, dphi500) = FillReBoostedVariables("decay"  , 500  , higgs_p4[0] , higgsdecay_p4 , higgsdecay_id , higgsdecay_isstar );
    std::tie(deta1000, dphi1000) = FillReBoostedVariables("decay"  , 1000 , higgs_p4[0] , higgsdecay_p4 , higgsdecay_id , higgsdecay_isstar );
    std::tie(deta1500, dphi1500) = FillReBoostedVariables("decay"  , 1500 , higgs_p4[0] , higgsdecay_p4 , higgsdecay_id , higgsdecay_isstar );

    tx->setBranch<float>("decay_dr", RooUtil::Calc::DeltaR(higgsdecay_p4[0], higgsdecay_p4[1]));

    return true;

}

//##############################################################################################################
std::tuple<float, float> babyMaker::FillReBoostedVariables(TString bname, int ptBoost, const LV& higgs_p4, const vector<LV>& decay_p4, const vector<int>& decay_id, const vector<int>& decay_isstar, float ref_deta, float ref_dphi)
{
    vector<LV> decay_boosted_p4;
    vector<float> decay_h_dr;
    vector<float> decay_h_deta;
    vector<float> decay_h_dphi;
    vector<float> decay_h_deta_rotated;
    vector<float> decay_h_dphi_rotated;
    float ref_vec_deta;
    float ref_vec_dphi;

    // Get all the various re-boosted p4, dr, deta, dphi values
    std::tie(decay_boosted_p4, decay_h_dr, decay_h_deta, decay_h_dphi, decay_h_deta_rotated, decay_h_dphi_rotated, ref_vec_deta, ref_vec_dphi) = getReBoostedDRDEtaDPhi(ptBoost, higgs_p4, decay_p4, ref_deta, ref_dphi);

    // Set branches
    tx->setBranch<vector<LV>>   (TString::Format("boosted%d_%s_p4"    , ptBoost, bname.Data()), decay_boosted_p4);
    tx->setBranch<vector<int>>  (TString::Format("boosted%d_%s_id"    , ptBoost, bname.Data()), decay_id);
    tx->setBranch<vector<int>>  (TString::Format("boosted%d_%s_isstar", ptBoost, bname.Data()), decay_isstar);
    tx->setBranch<vector<float>>(TString::Format("boosted%d_%s_h_dr"  , ptBoost, bname.Data()), decay_h_dr);
    tx->setBranch<vector<float>>(TString::Format("boosted%d_%s_h_deta", ptBoost, bname.Data()), decay_h_deta);
    tx->setBranch<vector<float>>(TString::Format("boosted%d_%s_h_dphi", ptBoost, bname.Data()), decay_h_dphi);
    tx->setBranch<vector<float>>(TString::Format("boosted%d_%s_h_deta_rotated", ptBoost, bname.Data()), decay_h_deta_rotated);
    tx->setBranch<vector<float>>(TString::Format("boosted%d_%s_h_dphi_rotated", ptBoost, bname.Data()), decay_h_dphi_rotated);

    tx->sortVecBranchesByPt(
            TString::Format("boosted%d_%s_p4", ptBoost, bname.Data()),
            {
                TString::Format("boosted%d_%s_h_dr", ptBoost, bname.Data()),
                TString::Format("boosted%d_%s_h_deta", ptBoost, bname.Data()),
                TString::Format("boosted%d_%s_h_dphi", ptBoost, bname.Data()),
                TString::Format("boosted%d_%s_h_deta_rotated", ptBoost, bname.Data()),
                TString::Format("boosted%d_%s_h_dphi_rotated", ptBoost, bname.Data())
            },
            {
                TString::Format("boosted%d_%s_id", ptBoost, bname.Data()),
                TString::Format("boosted%d_%s_isstar", ptBoost, bname.Data())
            },
            {});

    return make_tuple(ref_vec_deta, ref_vec_dphi);
}

//##############################################################################################################
std::tuple<std::vector<LV>, std::vector<float>, std::vector<float>, std::vector<float>, std::vector<float>, std::vector<float>, float, float> babyMaker::getReBoostedDRDEtaDPhi(int ptBoost, const LV& higgs_p4, const vector<LV>& higgsdecay_p4, float ref_deta, float ref_dphi)
{

    // Return the values
    if (higgsdecay_p4.size() == 0)
        return make_tuple(std::vector<LV>(), std::vector<float>(), std::vector<float>(), std::vector<float>(), std::vector<float>(), std::vector<float>(), -999, -999);

    // Compute the boost vectors
    TLorentzVector target_tlv = RooUtil::Calc::getTLV(higgs_p4);
    if (ptBoost == 0)
        target_tlv.SetPtEtaPhiM(target_tlv.Pt(), target_tlv.Eta(), target_tlv.Phi(), target_tlv.M());
    else
        target_tlv.SetPtEtaPhiM(ptBoost, target_tlv.Eta(), target_tlv.Phi(), target_tlv.M());
    TVector3 to_target = target_tlv.BoostVector();
    TVector3 to_higgs = RooUtil::Calc::boostVector(higgs_p4);

    // Re-compute all the decay product with the provided boost vector
    vector<LV> boosted_decay_p4;
    for (unsigned int i = 0; i < higgsdecay_p4.size(); ++i)
    {
        LV decay = RooUtil::Calc::getBoosted(higgsdecay_p4[i], -to_higgs);
        RooUtil::Calc::boost(decay, to_target);
        boosted_decay_p4.push_back(decay);
    }

    // Compute the higgs and re-boosted objects' dr, deta, dphi
    vector<float> boosted_decay_h_dr;
    vector<float> boosted_decay_h_deta;
    vector<float> boosted_decay_h_dphi;

    //for (auto& p4 : boosted_decay_p4)
    for (unsigned int i = 0; i < boosted_decay_p4.size(); ++i)
    {
        LV p4 = boosted_decay_p4[i];
        boosted_decay_h_dr.push_back(RooUtil::Calc::DeltaR(p4, higgs_p4));
        boosted_decay_h_deta.push_back(RooUtil::Calc::DeltaEta(p4, higgs_p4));
        boosted_decay_h_dphi.push_back(RooUtil::Calc::DeltaPhi(p4, higgs_p4));
    }

    // Compute the rotation angle based off of the leading decay particle
    int lead_idx = boosted_decay_p4[0].pt() > boosted_decay_p4[1].pt() ? 0 : 1;
    TVector2 ref_vec(boosted_decay_h_deta[lead_idx], boosted_decay_h_dphi[lead_idx]);
    if (ref_dphi != -999)
        ref_vec.Set(ref_deta, ref_dphi);

    vector<float> boosted_decay_h_deta_rotated;
    vector<float> boosted_decay_h_dphi_rotated;
    for (unsigned i = 0; i < boosted_decay_h_deta.size(); ++i)
    {
        TVector2 ang_vec;
        ang_vec.Set(boosted_decay_h_deta[i], boosted_decay_h_dphi[i]);
        TVector2 new_vec = ang_vec.Rotate(-ref_vec.Phi() + TMath::Pi() / 2.);
        boosted_decay_h_deta_rotated.push_back(new_vec.Px());
        boosted_decay_h_dphi_rotated.push_back(new_vec.Py());
    }

    // Return the values
    return make_tuple(boosted_decay_p4, boosted_decay_h_dr, boosted_decay_h_deta, boosted_decay_h_dphi, boosted_decay_h_deta_rotated, boosted_decay_h_dphi_rotated, (float) ref_vec.Px(), (float) ref_vec.Py());
}

//##############################################################################################################
void babyMaker::FillDecayProductsDRVariables(int pt)
{
    // if not lvqq decay then no point of calculating this max dr
    if (tx->getBranch<int>("nlep", true) != 1)
        return;
    if (pt > 0)
    {
        const vector<LV>& lepton_p4 = tx->getBranch<vector<LV>>(TString::Format("boosted%d_lepton_p4", pt), true);
        const vector<LV>& quark_p4 = tx->getBranch<vector<LV>>(TString::Format("boosted%d_quark_p4", pt), true);
        const LV& l_p4 = lepton_p4[0];
        const LV& q0_p4 = quark_p4[0];
        const LV& q1_p4 = quark_p4[1];
        float lq0_dr = RooUtil::Calc::DeltaR(l_p4, q0_p4);
        float lq1_dr = RooUtil::Calc::DeltaR(l_p4, q1_p4);
        float q0q1_dr = RooUtil::Calc::DeltaR(q0_p4, q1_p4);
        tx->setBranch<float>(TString::Format("boosted%d_lqq_max_dr", pt), max(lq0_dr, max(lq1_dr, q0q1_dr)));
        tx->setBranch<float>(TString::Format("boosted%d_lq0_dr", pt), lq0_dr);
        tx->setBranch<float>(TString::Format("boosted%d_lq1_dr", pt), lq1_dr);
        tx->setBranch<float>(TString::Format("boosted%d_qq_dr", pt), q0q1_dr);
    }
    else if (pt < 0)
    {
        const vector<LV>& lepton_p4 = tx->getBranch<vector<LV>>("lepton_p4", true);
        const vector<LV>& quark_p4 = tx->getBranch<vector<LV>>("quark_p4", true);
        const LV& l_p4 = lepton_p4[0];
        const LV& q0_p4 = quark_p4[0];
        const LV& q1_p4 = quark_p4[1];
        float lq0_dr = RooUtil::Calc::DeltaR(l_p4, q0_p4);
        float lq1_dr = RooUtil::Calc::DeltaR(l_p4, q1_p4);
        float q0q1_dr = RooUtil::Calc::DeltaR(q0_p4, q1_p4);
        float l_qq_dr = RooUtil::Calc::DeltaR(l_p4, (q0_p4 + q1_p4));
        tx->setBranch<float>("lqq_max_dr", max(lq0_dr, max(lq1_dr, q0q1_dr)));
        tx->setBranch<float>("lq0_dr", lq0_dr);
        tx->setBranch<float>("lq1_dr", lq1_dr);
        tx->setBranch<float>("qq_dr", q0q1_dr);
        tx->setBranch<float>("l_qq_dr", l_qq_dr);
    }
}

//##############################################################################################################
void babyMaker::FillTTree()
{
    tx->fill();
    tx->clear();
}

//##############################################################################################################
void babyMaker::SaveOutput()
{
    // This is always saved
    h_neventsinfile->Write();

    // Based on the baby mode now preselect and if it doesn't pass return
    switch (babymode)
    {
        case kHWWBaby: SaveHWWBaby(); break;
        default: return;
    }
}

//##############################################################################################################
void babyMaker::SaveHWWBaby()
{
    ofile->cd();
    t->Write();
}

//---------------==================-----------------==================-----------------=================----------
//---------------==================-----------------==================-----------------=================----------
//---------------==================-----------------==================-----------------=================----------
//---------------==================-----------------==================-----------------=================----------
//---------------==================-----------------==================-----------------=================----------

//##############################################################################################################
// FATAL error code
void babyMaker::FATALERROR(const char* funcname)
{
    std::cout <<  " cms3.evt_run(): " << cms3.evt_run() <<  " cms3.evt_lumiBlock(): " << cms3.evt_lumiBlock() <<  " cms3.evt_event(): " << cms3.evt_event() <<  std::endl;
    cout << "FATAL ERROR: I Should never be here! In function : " << funcname << endl;
}

//##############################################################################################################
// Used to overlap remova against tracks
bool babyMaker::isPt10Electron(int idx)
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
bool babyMaker::isPt10Muon(int idx)
{
    if (!( cms3.mus_p4()[idx].pt() > 10.        )) return false;
    if (!( isLooseMuonPOG(idx)                  )) return false;
    if (!( fabs(cms3.mus_p4()[idx].eta()) < 2.5 )) return false;
//    if (!( muRelIso03EA(idx, 2) > 0.1           )) return false;
//    if (!( muMiniRelIsoCMS3_EA(idx, 2) < 0.1    )) return false;
    return true;
}

//##############################################################################################################
int babyMaker::passCount(const vector<int>& v)
{
    return std::count_if(v.begin(), v.end(), [](int i){return i > 0;});
}

//##############################################################################################################
void babyMaker::sortVecP4(vector<LV>& v)
{
    std::sort(v.begin(), v.end(), [](const LV& a, const LV& b){return a.pt() > b.pt();});
}

//##############################################################################################################
bool babyMaker::isLeptonOverlappingWithJet(int ijet)
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

//    const vector<LV>& lep_p4 = tx->getBranch<vector<LV>>("lep_p4", false);
//    const vector<int>& lep_id = tx->getBranch<vector<int>>("lep_id", false);
//
//    int idx = coreJet.index[ijet];
//
//    for (unsigned ilep = 0; ilep < lep_id.size(); ++ilep)
//    {
//        const LV& p4 = lep_p4[ilep];
//        const int& id = lep_id[ilep];
//        if (id == 0) continue;
//        if (ROOT::Math::VectorUtil::DeltaR(cms3.pfjets_p4()[idx], p4) < 0.4)
//        {
//            is_overlapping = true;
//            break;
//        }
//    }

    if (is_overlapping)
        return true;

    return false;
}

//eof
