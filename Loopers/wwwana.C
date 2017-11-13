//  .
// ..: P.Chang philip@physics.ucsd.edu

#include "rooutil/cxxopts.h"
#include "rooutil/looper.h"
#include "rooutil/fileutil.h"
#include "rooutil/printutil.h"
#include "rooutil/dorky.h"
#include "rooutil/goodrun.h"
#include "rooutil/eventlist.h"

#include "CMS3_WWW0116.h"
#include "Functions.h"

#include "TString.h"

#include <map>
#include <vector>

//#################################################################################################
int main(int argc, char* argv[]);

//#################################################################################################
class WWWAnalysis
{
public:
    typedef std::vector<int> IdxList;

    //---------------------------------------------------------------------------------------------
    // Data samples related variables
    //---------------------------------------------------------------------------------------------
    TString babydir;
    TString dataset_to_run_over; // This or the following will need to be set.
    TString input_root_file_to_run_over; // This or the option before will need to be set.
    TString output_name;
    TChain* chain;
    std::map<TString, std::vector<TString>> datasetMap;
    RooUtil::Looper<CMS3> looper;

    //---------------------------------------------------------------------------------------------
    // Configurational related variables
    //---------------------------------------------------------------------------------------------
    TString eventlist_file_path;
    bool blindSR;
    bool storeeventnumbers;

    //---------------------------------------------------------------------------------------------
    // Analysis related variables
    //---------------------------------------------------------------------------------------------

    // lepton indices
    IdxList list_tight_ss_lep_idx; // tight
    IdxList list_tight_3l_lep_idx; // tight
    IdxList list_loose_ss_lep_idx; // loose but !tight
    IdxList list_loose_3l_lep_idx; // loose but !tight
    IdxList list_veto_ss_lep_idx;  // veto but !tight
    IdxList list_veto_3l_lep_idx;  // veto but !tight
    IdxList list_looseveto_ss_lep_idx; // veto but !loose
    IdxList list_looseveto_3l_lep_idx; // veto but !loose

    // MET kinematics
    LorentzVector MET;
    LorentzVector MET_up;
    LorentzVector MET_dn;

    // Jet kinematics
    int nj; // Number of central jets.
    int nb; // Number of b-tagged jets.
    int nj30; // Number of jets with abs(eta) up to 5.
    float Mjj; // Mjj with two closest jets.
    float MjjL; // Mjj with two leading jets.
    float Detajj; // Detajj with two leading jets.
    int nj_up; // Number of central jets.
    int nb_up; // Number of b-tagged jets.
    int nj30_up; // Number of jets with abs(eta) up to 5.
    float Mjj_up; // Mjj with two closest jets.
    float MjjL_up; // Mjj with two leading jets.
    float Detajj_up; // Detajj with two leading jets.
    int nj_dn; // Number of central jets.
    int nb_dn; // Number of b-tagged jets.
    int nj30_dn; // Number of jets with abs(eta) dn to 5.
    float Mjj_dn; // Mjj with two closest jets.
    float MjjL_dn; // Mjj with two leading jets.
    float Detajj_dn; // Detajj with two leading jets.

    // Lepton + MET variables
    float MTmax;
    float MTmax_up;
    float MTmax_dn;
    float MTmax3l;

    // Weights
    float weight;
    float btagsf;
    float btagsf_hfup;
    float btagsf_hfdn;
    float btagsf_lfup;
    float btagsf_lfdn;
    float purewgt;
    float purewgt_up;
    float purewgt_dn;
    float lepsf;
    float lepsf_err;
    float trigsf;
    float trigsf_err;

    // Trigger related variables
    bool pass_offline_trig;
    bool pass_online_trig;

    // Event filters
    bool pass_filters;

    // Good runs list
    bool pass_goodrun;

    // Sample reated variables
    TString sample_name;
    TString process_name_ss;
    TString process_name_3l;
    bool isphotonSS;
    bool isphoton3l;

    // Event ID
    int run_number;
    int lumiblock_number;
    int event_number;

    //---------------------------------------------------------------------------------------------
    // Functions
    //---------------------------------------------------------------------------------------------
    WWWAnalysis();
    void run();
    void setDatasetMap();
    void setChain();
    bool setStdVariables();
    void checkEvent();
    TString getSampleNameFromFileName(TString);
};

//#################################################################################################
int main(int argc, char* argv[])
{
    //---------------------------------------------------------------------------------------------
    // Parsing options to the program
    //---------------------------------------------------------------------------------------------
    try
    {
        // cxxopts is a package dealing with command line interface.
        cxxopts::Options options(argv[0], "WWW Analysis Looper");
        options.positional_help("[optional args]");
        options.add_options()
            ("D,babydir", "Directory path to baby ntuples", cxxopts::value<std::string>(), "DIRPATH")
            ("i,input", "Instead of -d,--dataset option one can run over single file using this option.", cxxopts::value<std::string>(), "INPUTROOTFILE")
            ("d,dataset", "Dataset to run over (e.g. WWW, Other, VVV, tt1l, tt2l, singleTop, ttV, Wjets, Zjets, WW, WZ, ZZ, WG, ZG, WGstar, Data)", cxxopts::value<std::string>(), "DATASET")
            ("e,eventlist", "File containing the event list to check", cxxopts::value<std::string>()->default_value("eventlist.txt"), "EVENTLISTFILE")
            ("o,output", "Output name", cxxopts::value<std::string>()->default_value("output.root"), "OUTPUT")
            ("h,help", "Print help")
            ;
        options.parse(argc, argv);

        // Print help message if --help or -h is provided
        if (options.count("help"))
        {
            RooUtil::print(options.help());
            exit(0);
        }

        // Declare the analysis module
        WWWAnalysis wwwanalysis;

        // If no babydir option is given, take the default one
        if (!options.count("babydir"))
        {
            TString default_baby_dir_path = "/hadoop/cms/store/user/phchang/metis/wwwlooper/v16_skim_v2_5/WWW_v0_1_16_v16_skim_v2_5/";
            RooUtil::print(Form("No baby dir path is provided. Using the default one=%s", default_baby_dir_path.Data()));
            wwwanalysis.babydir = default_baby_dir_path;
        }
        else
        {
            wwwanalysis.babydir = options["babydir"].as<std::string>() + "/";
        }

        if (!options.count("dataset") && !options.count("input"))
        {
            RooUtil::error(Form("Both --dataset and --input is not set! Check your arguments! Type ./%s --help for help.", argv[0]));
        }
        else if (options.count("dataset") && options.count("input"))
        {
            RooUtil::error(Form("Both --dataset and --input is set! Set only one of them! Type ./%s --help for help.", argv[0]));
        }

        // Set the dataset or the single input file to run over
        if (options.count("dataset"))
            wwwanalysis.dataset_to_run_over = options["dataset"].as<std::string>();

        // Set the dataset or the single input file to run over
        if (options.count("input"))
            wwwanalysis.input_root_file_to_run_over = options["input"].as<std::string>();

        // Set the output_name string
        wwwanalysis.output_name = options["output"].as<std::string>();

        // Set the eventlist.txt path
        wwwanalysis.eventlist_file_path = options["eventlist"].as<std::string>();

        // Run the looper!
        wwwanalysis.run();

    }
    catch (const cxxopts::OptionException& e)
    {
        std::cout << "error parsing options: " << e.what() << std::endl;
        exit(1);
    }

    return 0;
}

//#################################################################################################
void WWWAnalysis::run()
{
    // Set good runs list
    set_goodrun_file_json("data/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt");
    // Event lists to check
    RooUtil::EventList eventlist(eventlist_file_path);
    // From the options set create the TChain and load all the relevant root files.
    setChain();
    // Set the looper instance
    looper.init(chain, &cms3, -1);
    // Loop over events.
    while (looper.nextEvent())
    {
        // Computes standard variables and returns whether it passes basic selections.
        // If it does not pass basical selections, then skip.
        if (!setStdVariables()) continue;

        // checking events with run/lumi/evt matching in the list provided.
        bool checkevent = eventlist.has(tas::run(), tas::lumi(), tas::evt());
        if (checkevent)
        {
            std::cout << "Checking the event" << std::endl;
            std::cout << tas::run() << " " << tas::lumi() << " " << tas::evt() << std::endl;
        }


    }
}

//#################################################################################################
// Sets standard variables and returns false if fails preselection.
bool WWWAnalysis::setStdVariables()
{
    using namespace tas;

    // Set the event ID
    run_number = tas::run();
    lumiblock_number = tas::lumi();
    event_number = tas::evt();

    // Get all the lepton indices
    getleptonindices( list_tight_ss_lep_idx, list_tight_3l_lep_idx, list_loose_ss_lep_idx, list_loose_3l_lep_idx, list_veto_ss_lep_idx, list_veto_3l_lep_idx, list_looseveto_ss_lep_idx, list_looseveto_3l_lep_idx);

    // Preselection. Events not passing these are never used anywhere.
    if (firstgoodvertex() != 0)   { return false;; }
    if (nVert() < 0)              { return false;; }
    if (looper.getCurrentFileName().Contains("wjets_incl_mgmlm_")  && gen_ht() > 100) { return false;; }
    if (looper.getCurrentFileName().Contains("dy_m50_mgmlm_ext1_") && gen_ht() > 100) { return false;; }
    if (list_tight_3l_lep_idx.size() + list_loose_3l_lep_idx.size() < 2) { return false;; }

    // Set MET
    MET.SetPxPyPzE( met_pt() * TMath::Cos(met_phi()), met_pt() * TMath::Sin(met_phi()), 0, met_pt());
    MET_up.SetPxPyPzE( met_T1CHS_miniAOD_CORE_up_pt() * TMath::Cos(met_T1CHS_miniAOD_CORE_up_phi()), met_T1CHS_miniAOD_CORE_up_pt() * TMath::Sin(met_T1CHS_miniAOD_CORE_up_phi()), 0, met_T1CHS_miniAOD_CORE_up_pt());
    MET_dn.SetPxPyPzE( met_T1CHS_miniAOD_CORE_dn_pt() * TMath::Cos(met_T1CHS_miniAOD_CORE_dn_phi()), met_T1CHS_miniAOD_CORE_dn_pt() * TMath::Sin(met_T1CHS_miniAOD_CORE_dn_phi()), 0, met_T1CHS_miniAOD_CORE_dn_pt());

    // Set jet related variables
    getalljetnumbers(nj, nj30, nb);
    getalljetnumbers(nj_up, nj30_up, nb_up, 1);
    getalljetnumbers(nj_dn, nj30_dn, nb_dn, -1);
    getMjjAndDeta(Mjj, MjjL, Detajj);
    getMjjAndDeta(Mjj_up, MjjL_up, Detajj_up, 1);
    getMjjAndDeta(Mjj_dn, MjjL_dn, Detajj_dn, -1);

    // Set base weights
    weight = isData() ? 1 : evt_scale1fb() * 35.9; // Base weight
    if (looper.getCurrentFileName().Contains("www_2l_mia")     ) { weight *= 0.066805 * 91900. / (91900. + 164800.); } //(208fb/1pb)*BR(WWW>=2l)*combineweight
    if (looper.getCurrentFileName().Contains("www_2l_ext1_mia")) { weight *= 0.066805 * 164800. / (91900. + 164800.); } //(208fb/1pb)*BR(WWW>=2l)*combineweight

    // Set b-tagging weights
    btagsf = isData() ? 1. : weight_btagsf();
    btagsf_hfup = isData() ? 1. : btagsf != 0 ? weight_btagsf_heavy_UP() / weight_btagsf() : 1;
    btagsf_hfdn = isData() ? 1. : btagsf != 0 ? weight_btagsf_heavy_DN() / weight_btagsf() : 1;
    btagsf_lfup = isData() ? 1. : btagsf != 0 ? weight_btagsf_light_UP() / weight_btagsf() : 1;
    btagsf_lfdn = isData() ? 1. : btagsf != 0 ? weight_btagsf_light_DN() / weight_btagsf() : 1;

    // Set PU reweighting
    purewgt = isData() ? 1. : getPUWeightAndError(purewgt_dn, purewgt_up);

    // Set lepton SF
    lepsf = isData() ? 1. : getlepSFWeightandError(lepsf_err, list_tight_3l_lep_idx, list_loose_3l_lep_idx);

    // Set trigger SF
    trigsf = isData() ? 1. : getTriggerWeightandError(trigsf_err, list_tight_3l_lep_idx, list_loose_3l_lep_idx);

    // Offline trigger requirement (To stay on plateau)
    pass_offline_trig = passofflineTriggers(list_tight_3l_lep_idx, list_loose_3l_lep_idx);
    pass_online_trig = passonlineTriggers(list_tight_3l_lep_idx, list_loose_3l_lep_idx);

    // Event filters
    pass_filters = passFilters();

    // Good runs list
    pass_goodrun = !isData() ? 1. : goodrun(tas::run(), tas::lumi());

    // Sample names and types
    sample_name = getSampleNameFromFileName(looper.getCurrentFileName());
    process_name_ss = ((list_tight_ss_lep_idx.size() + list_loose_ss_lep_idx.size()) >= 2) ? process(looper.getCurrentFileName().Data(), true , list_tight_ss_lep_idx, list_loose_ss_lep_idx) : "not2l";
    process_name_3l = ((list_tight_3l_lep_idx.size() + list_loose_3l_lep_idx.size()) >= 3) ? process(looper.getCurrentFileName().Data(), false, list_tight_3l_lep_idx, list_loose_3l_lep_idx) : "not3l";
    isphotonSS = process_name_ss.EqualTo("photonfakes");
    isphoton3l = process_name_3l.EqualTo("photonfakes");

    // Lepton + MET variables
    MTmax = calcMTmax(list_tight_ss_lep_idx, MET);
    MTmax_up = calcMTmax(list_tight_ss_lep_idx, MET_up);
    MTmax_dn = calcMTmax(list_tight_ss_lep_idx, MET_dn);
    MTmax3l = calcMTmax(list_tight_3l_lep_idx, MET, true);

    return true;
}

//#################################################################################################
// Prints various info on the event for debugging purpose
void WWWAnalysis::checkEvent()
{
    using namespace std;
    using namespace tas;
    cout << "nj30 " << nj30 << " nj " << nj << " nb " << nb << " Mjj " << Mjj << " MjjL " << MjjL << " Detajj " << Detajj << endl;
    for (unsigned int i = 0; i < jets_p4().size(); ++i)
    {
        cout << "jet pT " << jets_p4()[i].Pt() << " eta " << jets_p4()[i].Eta() << " CSV " << jets_csv()[i];// << endl;
        for (unsigned int j = i + 1; j < jets_p4().size(); ++j) { cout << " M" << i << j << " " << (jets_p4()[i] + jets_p4()[j]).M() << " (dR " << dR(jets_p4()[i], jets_p4()[j]) << ")"; }
        cout << endl;
    }
    cout << "weight " << weight << " btag  " << weight_btagsf() << " PU " << purewgt << " trig " << trigsf << " lep " << lepsf << endl;
    cout << "nSS " << list_tight_ss_lep_idx.size();
    cout << " n3l " << list_tight_3l_lep_idx.size();
    cout << " naSS " << list_loose_ss_lep_idx.size();
    cout << " na3l " << list_loose_3l_lep_idx.size();
    cout << " nvetoaSS " << list_veto_ss_lep_idx.size();
    cout << " nvetoa3l " << list_veto_3l_lep_idx.size();
    cout << " ntracks " << nisoTrack_mt2_cleaned_VVV_cutbased_veto() << endl;
    for (unsigned int i = 0; i < lep_pdgId().size(); ++i)
    {
        cout << "lep " << lep_pdgId()[i] << " Pt " << lep_p4()[i].Pt() << " eta " << lep_p4()[i].Eta() << " ID t/l/v/trig " << lep_pass_VVV_cutbased_tight_noiso()[i] << "/" << lep_pass_VVV_cutbased_fo_noiso()[i] << "/" << lep_pass_VVV_cutbased_veto_noiso()[i] << "/" << lep_isTriggerSafe_v1()[i] << " iso " << lep_relIso03EAv2()[i] << " ip3d " << lep_ip3d()[i] << " losthits " << lep_lostHits()[i] << " t.q " << lep_tightCharge()[i];
        for (unsigned int j = i + 1; j < lep_pdgId().size(); ++j)
        {
            cout << " M" << i << j << " " << (lep_p4()[i] + lep_p4()[j]).M();
            for (unsigned int k = j + 1; k < lep_pdgId().size(); ++k) { cout << " M" << i << j << k << " " << (lep_p4()[i] + lep_p4()[j] + lep_p4()[k]).M() << " Pt " << (lep_p4()[i] + lep_p4()[j] + lep_p4()[k]).Pt() << " DPhiMET " << dPhi((lep_p4()[i] + lep_p4()[j] + lep_p4()[k]), MET); }
        }
        cout << endl;
    }
    cout << "MET " << MET.Pt() << " MTmax " << MTmax << " MTmax3l " << MTmax3l << endl;
}


//#################################################################################################
void WWWAnalysis::setChain()
{
    if (!chain)
    {
        // Vector to hold the datasets to run over
        std::vector<TString> dataset_paths;

        if (!dataset_to_run_over.IsNull())
        {
            try
            {
                // From the dataSetMap created add the individual root files for this dataset.
                for (auto& dataset_path : datasetMap.at(dataset_to_run_over))
                    dataset_paths.push_back(babydir + dataset_path);
            }
            catch (const std::out_of_range& oor)
            {
                std::cerr << "Unrecognized sample! - What is '" << dataset_to_run_over << "'?" << std::endl;
                exit(1);
            }
        }
        else if (!input_root_file_to_run_over.IsNull())
        {
            dataset_paths.push_back(input_root_file_to_run_over);
        }
        else
        {
            RooUtil::error(Form("Something is wrong. I don't know which root files to loop over! Check your arguments! Type ./wwwana --help for help."));
        }

        // Create at TChain from the list of root files.
        chain = RooUtil::FileUtil::createTChain("t", RooUtil::StringUtil::join(dataset_paths, ","));
    }
}

//#################################################################################################
WWWAnalysis::WWWAnalysis()
{
    chain = 0;
    babydir = "";
    input_root_file_to_run_over = "";
    dataset_to_run_over = "";
    blindSR           = true;
    storeeventnumbers = true;
    setDatasetMap();
}

//#################################################################################################
// Initializes map between dataset name -> list of files to loop over.
void WWWAnalysis::setDatasetMap()
{
    datasetMap["WWW"].push_back("www_2l_mia_*.root");
    datasetMap["WWW"].push_back("www_2l_ext1_mia_*.root");

    datasetMap["Other"].push_back("vh_nonbb_amcnlo*.root");

    datasetMap["VVV"].push_back("wwz_incl_amcnlo*.root");
    datasetMap["VVV"].push_back("wzz_incl_amcnlo*.root");
    datasetMap["VVV"].push_back("zzz_incl_amcnlo*.root");
    datasetMap["VVV"].push_back("wwg_incl_amcnlo*.root");
    datasetMap["VVV"].push_back("wzg_incl_amcnlo*.root");

    datasetMap["tt1l"].push_back("ttbar_1ltbr_mgmlm_ext1*.root");
    datasetMap["tt1l"].push_back("ttbar_1ltop_mgmlm_ext1*.root");

    datasetMap["tt2l"].push_back("ttbar_dilep_mgmlm_ext1*.root");

    datasetMap["singleTop"].push_back("stt_antitop_incdec_powheg*.root");
    datasetMap["singleTop"].push_back("stt_top_incdec_powheg*.root");
    datasetMap["singleTop"].push_back("sttw_antitop_nofullhaddecay_powheg*.root");
    datasetMap["singleTop"].push_back("sttw_top_nofullhaddecay_powheg*.root");
    datasetMap["singleTop"].push_back("sttwll_madgraph*.root");
    datasetMap["singleTop"].push_back("sts_4f_leptonic_amcnlo*.root");
    datasetMap["singleTop"].push_back("tzq_ll_amcnlo*.root");

    datasetMap["ttV"].push_back("ttg_incl_amcnlo*.root");
    datasetMap["ttV"].push_back("tth_bb_powheg*.root");
    datasetMap["ttV"].push_back("tth_nonbb_powheg*.root");
    datasetMap["ttV"].push_back("ttw_incl_mgmlm*.root");
    datasetMap["ttV"].push_back("ttz_incl_mgmlm*.root");

    datasetMap["Wjets"].push_back("wjets_incl_mgmlm*.root");
    datasetMap["Wjets"].push_back("wjets_ht100_mgmlm_ext1*.root");
    datasetMap["Wjets"].push_back("wjets_ht200_mgmlm_ext1*.root");
    datasetMap["Wjets"].push_back("wjets_ht400_mgmlm_ext1*.root");
    datasetMap["Wjets"].push_back("wjets_ht600_mgmlm_ext1*.root");
    datasetMap["Wjets"].push_back("wjets_ht800_mgmlm_ext1*.root");
    datasetMap["Wjets"].push_back("wjets_ht1200_mgmlm_nonext*.root");
    datasetMap["Wjets"].push_back("wjets_ht2500_mgmlm_ext1*.root");
    datasetMap["Wjets"].push_back("Wpjj_lnu_madgraph*.root");
    datasetMap["Wjets"].push_back("Wmjj_lnu_madgraph*.root");

    datasetMap["Zjets"].push_back("dy_m1050_mgmlm*.root");
    datasetMap["Zjets"].push_back("dy_m50_mgmlm_ext1*.root");
    datasetMap["Zjets"].push_back("dy_m50_mgmlm_ht100_ext1*.root");
    datasetMap["Zjets"].push_back("dy_m50_mgmlm_ht200_ext1*.root");
    datasetMap["Zjets"].push_back("dy_m50_mgmlm_ht400_ext1*.root");
    datasetMap["Zjets"].push_back("dy_m50_mgmlm_ht600_nonext*.root");
    datasetMap["Zjets"].push_back("dy_m50_mgmlm_ht800_nonext*.root");
    datasetMap["Zjets"].push_back("dy_m50_mgmlm_ht1200_nonext*.root");
    datasetMap["Zjets"].push_back("dy_m50_mgmlm_ht2500_nonext*.root");
    datasetMap["Zjets"].push_back("Zjj_m50_madgraph*.root");

    datasetMap["WW"].push_back("wpwpjj_ewk-qcd_madgraph*.root");
    datasetMap["WW"].push_back("ww_2l2nu_dbl_scat*.root");
    datasetMap["WW"].push_back("ww_2l2nu_powheg*.root");
    datasetMap["WW"].push_back("ww_lnuqq_powheg*.root");

    datasetMap["WZ"].push_back("wz_1l3n_amcnlo*.root");
    datasetMap["WZ"].push_back("wz_3lnu_powheg*.root");
    datasetMap["WZ"].push_back("wz_lnqq_amcnlo*.root");

    datasetMap["ZZ"].push_back("zz_2l2n_powheg*.root");
    datasetMap["ZZ"].push_back("zz_2l2q_powheg*.root");
    datasetMap["ZZ"].push_back("zz_2q2n_amcnlo*.root");
    datasetMap["ZZ"].push_back("zz_4l_powheg*.root");

    datasetMap["WG"].push_back("wgjets_incl_mgmlm*.root");

    datasetMap["ZG"].push_back("zgamma_2lG_amc*.root");

    datasetMap["WGstar"].push_back("wgstar_lnee_012jets_madgraph*.root");
    datasetMap["WGstar"].push_back("wgstar_lnmm_012jets_madgraph*.root");

    datasetMap["Data"].push_back("data_*ee*.root");
    datasetMap["Data"].push_back("data_*em*.root");
    datasetMap["Data"].push_back("data_*mm*.root");
}

//#################################################################################################
// From the root file name determine which dataset it corresponds to.
TString WWWAnalysis::getSampleNameFromFileName(TString filename)
{
    if (splitVH(filename.Data()))
       return "WHtoWWW";

    for (auto& dataset : datasetMap)
    {
        for (auto& pttn : dataset.second)
        {
            std::vector<TString> tokens = RooUtil::StringUtil::split(pttn, "*");
            TString pttn1 = tokens.at(0);
            TString pttn2 = tokens.size() == 3 ? tokens.at(1) : "";
            if (filename.Contains(pttn1) && filename.Contains(pttn2))
                return dataset.first;
        }
    }
    RooUtil::error(Form("Failed to determine which dataset this rootfile belongs to file=%s", filename.Data()));
    return "";
}

//eof
