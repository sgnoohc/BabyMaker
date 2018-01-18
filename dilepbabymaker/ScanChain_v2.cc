#include "ScanChain_v2.h"

using namespace std;

//##############################################################################################################
void babyMaker_v2::ScanChain_v2(TChain* chain, std::string baby_name, int max_events)
{
    // Configure the event loop
    Configure();

    // Looper
    RooUtil::Looper<CMS3> looper(chain, &cms3, max_events);

    while (looper.nextEvent())
    {
        isData = tas::evt_isRealData();

        //======================================================
        // Triggers
        //======================================================
        HLT_DoubleMu = (passHLTTriggerPattern("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v") ||
                        passHLTTriggerPattern("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v") ||
                        passHLTTriggerPattern("HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v") ||
                        passHLTTriggerPattern("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v") ||
                        passHLTTriggerPattern("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v"));

        HLT_MuEG = (passHLTTriggerPattern("HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v") ||
                    passHLTTriggerPattern("HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v") ||
                    passHLTTriggerPattern("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v") ||
                    passHLTTriggerPattern("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v") ||
                    passHLTTriggerPattern("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v") ||
                    passHLTTriggerPattern("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v") ||
                    passHLTTriggerPattern("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v") ||
                    passHLTTriggerPattern("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_v") ||
                    passHLTTriggerPattern("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"));

        HLT_DoubleEl = (passHLTTriggerPattern("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_v") ||
                        passHLTTriggerPattern("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v")); // prescaled - turned off

        HLT_DoubleEl_DZ = passHLTTriggerPattern("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"); // prescaled

        // Loop over gen particles

        // Loop over electrons

        // Loop over muons

        // Organize leptons by sorting

        // Photons Not needed

        // Select based on two leptons

        // Loop over jets (keep track of good ones for removal)

        // jet lepton overlap

        // Loop over good jets after removal and select

        // kinematic variables for pf cands (isotrack)

        coreJec.setJECFor(looper.getCurrentFileName());
    }
}

//##############################################################################################################
// Configuring before running the event loop
void babyMaker_v2::Configure()
{
    ConfigureElectronMVA();
    ConfigureMuonMVA();
    ConfigureGoodRunsList();
    ConfigurePileUpReweighting();
    ConfigureBtagging();
}

//##############################################################################################################
void babyMaker_v2::ConfigureElectronMVA()
{
    cout << "Creating electron MVA instance" << endl;
    createAndInitMVA("MVAinput", true, false, 80); // for electrons
}

//##############################################################################################################
void babyMaker_v2::ConfigureGoodRunsList()
{
    json_file = "Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON_snt.txt"; // 26p4 fb
    cout << "Setting grl: " << json_file << endl;
    set_goodrun_file(json_file);
}

//##############################################################################################################
void babyMaker_v2::ConfigurePileUpReweighting()
{
//    TH1F * h_vtxweight = NULL;
//    TFile * f_vtx = NULL;
//    f_vtx = TFile::Open("puWeight2016.root", "READ");
//    h_vtxweight = (TH1F*)f_vtx->Get("pileupWeight")->Clone("h_vtxweight");
//    h_vtxweight->SetDirectory(rootdir);
//    f_vtx->Close();
}

//##############################################################################################################
void babyMaker_v2::ConfigureMuonMVA()
{
//    reader1 = new TMVA::Reader("!Color:!Silent");
//    reader2 = new TMVA::Reader("!Color:!Silent");
//    reader3 = new TMVA::Reader("!Color:!Silent");
//    reader1->AddVariable("lepton_eta", &lepton_eta);
//    reader1->AddVariable("lepton_phi", &lepton_phi);
//    reader1->AddVariable("lepton_pt", &lepton_pt);
//    reader1->AddVariable("lepton_relIso03EA", &lepton_relIso03EA);
//    reader1->AddVariable("lepton_chiso", &lepton_chiso);
//    reader1->AddVariable("lepton_nhiso", &lepton_nhiso);
//    reader1->AddVariable("lepton_emiso", &lepton_emiso);
//    reader1->AddVariable("lepton_ncorriso", &lepton_ncorriso);
//    reader1->AddVariable("lepton_dxy", &lepton_dxy);
//    reader1->AddVariable("lepton_dz", &lepton_dz);
//    reader1->AddVariable("lepton_ip3d", &lepton_ip3d);
//    reader1->BookMVA("BDT1", "/hadoop/cms/store/user/phchang/mlp/weights_BDTbaseline_v0.0.2__preliminary_11lepvec_1Msig_100Kbkg_events/TMVA_BDT.weights.xml");
//    reader2->AddVariable("lepton_relIso03EA", &lepton_relIso03EA);
//    reader2->AddVariable("lepton_chiso", &lepton_chiso);
//    reader2->AddVariable("lepton_nhiso", &lepton_nhiso);
//    reader2->AddVariable("lepton_emiso", &lepton_emiso);
//    reader2->AddVariable("lepton_ncorriso", &lepton_ncorriso);
//    reader2->AddVariable("lepton_dxy", &lepton_dxy);
//    reader2->AddVariable("lepton_dz", &lepton_dz);
//    reader2->AddVariable("lepton_ip3d", &lepton_ip3d);
//    reader2->BookMVA("BDT2", "/hadoop/cms/store/user/phchang/mlp/weights_BDTbaseline_v0.0.4__nolepp4/TMVA_BDT.weights.xml");
//    reader3->AddVariable("lepton_relIso03EA", &lepton_relIso03EA);
//    reader3->AddVariable("lepton_chiso", &lepton_chiso);
//    reader3->AddVariable("lepton_nhiso", &lepton_nhiso);
//    reader3->AddVariable("lepton_emiso", &lepton_emiso);
//    reader3->AddVariable("lepton_ncorriso", &lepton_ncorriso);
//    reader3->BookMVA("BDT3", "/hadoop/cms/store/user/phchang/mlp/weights_BDTbaseline_v0.0.5__nop4noip/TMVA_BDT.weights.xml");
}

//##############################################################################################################
void babyMaker_v2::ConfigureBtagging()
{
//    // setup btag calibration readers
//    calib           = new BTagCalibration("csvv2", "btagsf/CSVv2_Moriond17_B_H.csv"); // Moriond17 version of SFs
//    reader_heavy    = new BTagCalibrationReader(calib, BTagEntry::OP_LOOSE, "comb", "central"); // central
//    reader_heavy_UP = new BTagCalibrationReader(calib, BTagEntry::OP_LOOSE, "comb", "up");      // sys up
//    reader_heavy_DN = new BTagCalibrationReader(calib, BTagEntry::OP_LOOSE, "comb", "down");    // sys down
//    reader_light    = new BTagCalibrationReader(calib, BTagEntry::OP_LOOSE, "incl", "central"); // central
//    reader_light_UP = new BTagCalibrationReader(calib, BTagEntry::OP_LOOSE, "incl", "up");      // sys up
//    reader_light_DN = new BTagCalibrationReader(calib, BTagEntry::OP_LOOSE, "incl", "down");    // sys down
//    // get btag efficiencies
//    TFile * f_btag_eff           = new TFile("btagsf/btageff__ttbar_powheg_pythia8_25ns_Moriond17.root");
//    TH2D  * h_btag_eff_b_temp    = (TH2D*) f_btag_eff->Get("h2_BTaggingEff_csv_loose_Eff_b");
//    TH2D  * h_btag_eff_c_temp    = (TH2D*) f_btag_eff->Get("h2_BTaggingEff_csv_loose_Eff_c");
//    TH2D  * h_btag_eff_udsg_temp = (TH2D*) f_btag_eff->Get("h2_BTaggingEff_csv_loose_Eff_udsg");
//    BabyFile_->cd();
//    h_btag_eff_b    = (TH2D*) h_btag_eff_b_temp    -> Clone("h_btag_eff_b");
//    h_btag_eff_c    = (TH2D*) h_btag_eff_c_temp    -> Clone("h_btag_eff_c");
//    h_btag_eff_udsg = (TH2D*) h_btag_eff_udsg_temp -> Clone("h_btag_eff_udsg");
//    // f_btag_eff->Close();
//    std::cout << "loaded fullsim btag SFs" << std::endl;
}

