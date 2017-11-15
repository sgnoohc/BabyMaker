//  .
// ..: P.Chang philip@physics.ucsd.edu

#include "rooutil/cxxopts.h"
#include "rooutil/looper.h"
#include "rooutil/multidraw.h"
#include "rooutil/fileutil.h"
#include "rooutil/printutil.h"
#include "rooutil/dorky.h"
#include "rooutil/goodrun.h"
#include "rooutil/eventlist.h"
#include "rooutil/ttreex.h"

#include "CMS3_WWW0116.h"
#include "Functions.h"

#include "Math/VectorUtil.h"
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
    // I/O related variables
    //---------------------------------------------------------------------------------------------
    TString babydir;
    TString dataset_to_run_over; // This or the following will need to be set.
    TString input_root_file_to_run_over; // This or the option before will need to be set.
    TString output_name;
    TFile* ofile;
    TTree* otree;
    TChain* chain;
    std::map<TString, std::vector<TString>> datasetMap;
    RooUtil::Looper<CMS3> looper;
    RooUtil::EventList eventlist;
    RooUtil::TTreeX ttreex;

    //---------------------------------------------------------------------------------------------
    // Configurational related variables
    //---------------------------------------------------------------------------------------------
    bool is_initialized;
    TString eventlist_file_path;
    bool blindSR;
    bool storeeventnumbers;

    //---------------------------------------------------------------------------------------------
    // Analysis related variables
    //---------------------------------------------------------------------------------------------

    // lepton indices (The convention is a bit more "exclusively" defined.)
    IdxList list_tight_ss_lep_idx; // tight
    IdxList list_tight_3l_lep_idx; // tight
    IdxList list_loose_ss_lep_idx; // loose but !tight
    IdxList list_loose_3l_lep_idx; // loose but !tight
    IdxList list_veto_ss_lep_idx;  // veto but !tight
    IdxList list_veto_3l_lep_idx;  // veto but !tight
    IdxList list_looseveto_ss_lep_idx; // veto but !loose
    IdxList list_looseveto_3l_lep_idx; // veto but !loose

    // lepton indices
    IdxList list_incl_tight_ss_lep_idx; // tight
    IdxList list_incl_tight_3l_lep_idx; // tight
    IdxList list_incl_loose_ss_lep_idx; // loose
    IdxList list_incl_loose_3l_lep_idx; // loose
    IdxList list_incl_veto_ss_lep_idx;  // veto
    IdxList list_incl_veto_3l_lep_idx;  // veto

    // track multiplicity
    int ntrk;

    // SFOS
    int nSFOS;

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

    float MjjBal;

    // Lepton + MET variables
    float MTmax;
    float MTmax_up;
    float MTmax_dn;
    float MTmax3l;
    float MT1SFOS;

    // Lepton + Lepton variables
    float MllSS;
    float MeeSS;
    float Mll0SFOS;
    float Mee0SFOS;
    float Mll1SFOS;
    float Mll2SFOS0;
    float Mll2SFOS1;

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

    // Generator level variables for signal
    IdxList list_gen_quarks; // generatore level quarks from W boson in the WWW signal sample
    IdxList list_gen_leptons; // generatore level light-leptons from W boson (or the subsequent decay from the tau) in the WWW signal sample
    float gen_Mjj;
    float gen_DEtajj;
    float gen_DRjj;

    //---------------------------------------------------------------------------------------------
    // Functions
    //---------------------------------------------------------------------------------------------
    WWWAnalysis();
    void init();
    void createBranches();
    void run();
    void setBranches();
    void setDatasetMap();
    void setChain();
    bool calcStdVariables();
    void processLeptonIndices();
    void checkEvent();
    TString getSampleNameFromFileName(TString);

    void cutflow();
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
            ("c,cutflow", "Do cutflow")
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
        if (!options.count("babydir") && !options.count("input"))
        {
            TString default_baby_dir_path = "/hadoop/cms/store/user/phchang/metis/wwwlooper/v16_skim_v2_5/WWW_v0_1_16_v16_skim_v2_5/";
            RooUtil::print(Form("No baby dir path is provided. Using the default one=%s", default_baby_dir_path.Data()));
            wwwanalysis.babydir = default_baby_dir_path;
        }
        else
        {
            wwwanalysis.babydir = options["babydir"].as<std::string>() + "/";
        }

        // Sanity check on the options provided.
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

        // Initialize the analysis module
        wwwanalysis.init();

        if (options.count("cutflow"))
        {
            // Run the cutflow!
            wwwanalysis.cutflow();
        }
        else
        {
            // Run the looper!
            wwwanalysis.run();
        }

    }
    catch (const cxxopts::OptionException& e)
    {
        std::cout << "error parsing options: " << e.what() << std::endl;
        exit(1);
    }

    return 0;
}

//#################################################################################################
void WWWAnalysis::init()
{
    if (!is_initialized)
    {
        // Set good runs list
        set_goodrun_file_json("data/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt");

        // Event lists to check
        eventlist.load(eventlist_file_path);

        // From the options set create the TChain and load all the relevant root files.
        setChain();

        // Set the looper instance
        looper.init(chain, &cms3, -1);

        // Set the output file
        ofile = new TFile(output_name, "recreate");

        // Create output TTree
        otree = new TTree("t", "WWWAnalysis Output TTree");

        // Hook the otree to TTreeX
        ttreex.setTree(otree);

        // Create branches to the output TTree
        createBranches();

        // Set the is_initialized
        is_initialized = true;
    }
    else
    {
        RooUtil::warning("[WWWAnalysis::init()] WWWAnalysis is already initialized! Why are you asking to initialize again?");
    }
}

//#################################################################################################
// Create variables to output to the TTree
void WWWAnalysis::createBranches()
{
    ttreex.createBranch<LV>("veto_ss_lep0");
    ttreex.createBranch<LV>("veto_ss_lep1");

    ttreex.createBranch<LV>("veto_3l_lep0");
    ttreex.createBranch<LV>("veto_3l_lep1");
    ttreex.createBranch<LV>("veto_3l_lep2");

    ttreex.createBranch<int>("veto_ss_lep0_pdgid");
    ttreex.createBranch<int>("veto_ss_lep1_pdgid");

    ttreex.createBranch<int>("veto_3l_lep0_pdgid");
    ttreex.createBranch<int>("veto_3l_lep1_pdgid");
    ttreex.createBranch<int>("veto_3l_lep2_pdgid");

    ttreex.createBranch<int>("n_tight_ss_lep");
    ttreex.createBranch<int>("n_tight_3l_lep");
    ttreex.createBranch<int>("n_loose_ss_lep");
    ttreex.createBranch<int>("n_loose_3l_lep");
    ttreex.createBranch<int>("n_veto_ss_lep");
    ttreex.createBranch<int>("n_veto_3l_lep");

    ttreex.createBranch<int>("ntrk");
    ttreex.createBranch<int>("nSFOS");

    ttreex.createBranch<LV>("MET");
    ttreex.createBranch<LV>("MET_up");
    ttreex.createBranch<LV>("MET_dn");

    ttreex.createBranch<int>("nj");
    ttreex.createBranch<int>("nb");
    ttreex.createBranch<int>("nj30");
    ttreex.createBranch<float>("Mjj");
    ttreex.createBranch<float>("MjjL");
    ttreex.createBranch<float>("Detajj");

    ttreex.createBranch<int>("nj_up");
    ttreex.createBranch<int>("nb_up");
    ttreex.createBranch<int>("nj30_up");
    ttreex.createBranch<float>("Mjj_up");
    ttreex.createBranch<float>("MjjL_up");
    ttreex.createBranch<float>("Detajj_up");

    ttreex.createBranch<int>("nj_dn");
    ttreex.createBranch<int>("nb_dn");
    ttreex.createBranch<int>("nj30_dn");
    ttreex.createBranch<float>("Mjj_dn");
    ttreex.createBranch<float>("MjjL_dn");
    ttreex.createBranch<float>("Detajj_dn");

    ttreex.createBranch<float>("MTmax");
    ttreex.createBranch<float>("MTmax_up");
    ttreex.createBranch<float>("MTmax_dn");
    ttreex.createBranch<float>("MTmax3l");
    ttreex.createBranch<float>("MT1SFOS");

    ttreex.createBranch<float>("MllSS");
    ttreex.createBranch<float>("MeeSS");
    ttreex.createBranch<float>("Mll0SFOS");
    ttreex.createBranch<float>("Mee0SFOS");
    ttreex.createBranch<float>("Mll1SFOS");
    ttreex.createBranch<float>("Mll2SFOS0");
    ttreex.createBranch<float>("Mll2SFOS1");

    ttreex.createBranch<float>("weight");
    ttreex.createBranch<float>("btagsf");
    ttreex.createBranch<float>("btagsf_hfup");
    ttreex.createBranch<float>("btagsf_hfdn");
    ttreex.createBranch<float>("btagsf_lfup");
    ttreex.createBranch<float>("btagsf_lfdn");
    ttreex.createBranch<float>("purewgt");
    ttreex.createBranch<float>("purewgt_up");
    ttreex.createBranch<float>("purewgt_dn");
    ttreex.createBranch<float>("lepsf");
    ttreex.createBranch<float>("lepsf_err");
    ttreex.createBranch<float>("trigsf");
    ttreex.createBranch<float>("trigsf_err");

    ttreex.createBranch<bool>("pass_offline_trig");
    ttreex.createBranch<bool>("pass_online_trig");
    ttreex.createBranch<bool>("pass_filters");
    ttreex.createBranch<bool>("pass_goodrun");

    ttreex.createBranch<TString>("sample_name");
    ttreex.createBranch<TString>("process_name_ss");
    ttreex.createBranch<TString>("process_name_3l");
    ttreex.createBranch<bool>("isphotonSS");
    ttreex.createBranch<bool>("isphoton3l");

    ttreex.createBranch<int>("run_number");
    ttreex.createBranch<int>("lumiblock_number");
    ttreex.createBranch<int>("event_number");

    ttreex.createBranch<float>("gen_Mjj");
    ttreex.createBranch<float>("gen_DEtajj");
    ttreex.createBranch<float>("gen_DRjj");

    ttreex.createBranch<LV>("gen_quark0");
    ttreex.createBranch<LV>("gen_quark1");
}

//#################################################################################################
void WWWAnalysis::run()
{
    // Loop over events.
    while (looper.nextEvent())
    {
        // Computes standard variables and returns whether it passes basic selections.
        // If it does not pass basical selections, then skip.
        if (!calcStdVariables()) continue;

        // Set the branches to TTree
        setBranches();

        // Fill the TTree
        ttreex.fill();

        // checking events with run/lumi/evt matching in the list provided.
        if (eventlist.has(tas::run(), tas::lumi(), tas::evt())) checkEvent();
    }

    // Save the TTree
    ttreex.save(ofile);
}

//#################################################################################################
// Sets standard variables and returns false if fails preselection.
bool WWWAnalysis::calcStdVariables()
{
    using namespace tas;

    // Set the event ID
    run_number = tas::run();
    lumiblock_number = tas::lumi();
    event_number = tas::evt();

    // Get all the lepton indices
    getleptonindices(list_tight_ss_lep_idx, list_tight_3l_lep_idx, list_loose_ss_lep_idx, list_loose_3l_lep_idx, list_veto_ss_lep_idx, list_veto_3l_lep_idx, list_looseveto_ss_lep_idx, list_looseveto_3l_lep_idx);

    // I like to keep the lepton indices to be more about what they actually mean.
    processLeptonIndices();

    // Preselection. Events not passing these are never used anywhere.
    if (firstgoodvertex() != 0)   { return false;; }
    if (nVert() < 0)              { return false;; }
    if (looper.getCurrentFileName().Contains("wjets_incl_mgmlm_")  && gen_ht() > 100) { return false;; }
    if (looper.getCurrentFileName().Contains("dy_m50_mgmlm_ext1_") && gen_ht() > 100) { return false;; }
    if (list_tight_3l_lep_idx.size() < 1) { return false; }
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

    // Lepton + Lepton variables
    MllSS = -999;
    MeeSS = -999;
    if (list_incl_veto_ss_lep_idx.size() >= 2)
    {
        MllSS = (lep_p4()[list_incl_veto_ss_lep_idx[0]] + lep_p4()[list_incl_veto_ss_lep_idx[1]]).mass();
        if (abs(lep_pdgId()[list_incl_veto_ss_lep_idx[0]]) == 11 && abs(lep_pdgId()[list_incl_veto_ss_lep_idx[1]]) == 11)
            MeeSS = (lep_p4()[list_incl_veto_ss_lep_idx[0]] + lep_p4()[list_incl_veto_ss_lep_idx[1]]).mass();

    }

    ntrk = nisoTrack_mt2_cleaned_VVV_cutbased_veto();

    nSFOS = -1;
    if (list_incl_veto_3l_lep_idx.size() >= 3) nSFOS = calcNSFOS(list_incl_veto_3l_lep_idx);

    MT1SFOS = -999;
    if (nSFOS == 1)
    {
        int idx = -1;
        if (lep_pdgId()[list_incl_veto_3l_lep_idx[0]] == -lep_pdgId()[list_incl_veto_3l_lep_idx[1]]) idx = 2;
        if (lep_pdgId()[list_incl_veto_3l_lep_idx[0]] == -lep_pdgId()[list_incl_veto_3l_lep_idx[2]]) idx = 1;
        if (lep_pdgId()[list_incl_veto_3l_lep_idx[1]] == -lep_pdgId()[list_incl_veto_3l_lep_idx[2]]) idx = 0;
        MT1SFOS = mT(lep_p4()[idx], MET);
    }

    Mll0SFOS = -999;
    Mee0SFOS = -999;
    Mll1SFOS = -999;
    Mll2SFOS0 = -999;
    Mll2SFOS1 = -999;
    if (list_incl_veto_3l_lep_idx.size() >= 3)
    {
        if (nSFOS == 0)
        {
            Mll0SFOS = get0SFOSMll(list_incl_veto_3l_lep_idx);
            Mee0SFOS = get0SFOSMee(list_incl_veto_3l_lep_idx);;
        }
        else if (nSFOS == 1)
        {
            Mll1SFOS = get1SFOSMll(list_incl_veto_3l_lep_idx);;
        }
        else if (nSFOS == 2)
        {
            Mll2SFOS0 = get2SFOSMll0(list_incl_veto_3l_lep_idx);;
            Mll2SFOS1 = get2SFOSMll1(list_incl_veto_3l_lep_idx);;
        }
    }

    gen_Mjj = -999;
    gen_DEtajj = -999;
    gen_DRjj = -999;
    if (sample_name.Contains("WWW"))
    {
        std::tie(list_gen_quarks, list_gen_leptons) = getGenIndices();
        if (list_gen_quarks.size() == 2 && list_gen_leptons.size() == 2)
        {
            gen_Mjj = (genPart_p4()[list_gen_quarks[0]] + genPart_p4()[list_gen_quarks[1]]).mass();
            gen_DEtajj = fabs(genPart_p4()[list_gen_quarks[0]].eta() - genPart_p4()[list_gen_quarks[1]].eta());
            gen_DRjj = ROOT::Math::VectorUtil::DeltaR(genPart_p4()[list_gen_quarks[0]], genPart_p4()[list_gen_quarks[1]]);
        }
    }

    return true;
}

//#################################################################################################
// The standard lepton indices obtained from the function getleptonindices from Functions.h are set in an exclusive way.
// i.e. in 'list_loose_ss_lep_idx' only the loose but not tight are saved.
// I like to keep it such that they are selected by what they actually mean.
// So with this function I set indices like 'list_incl_loose_ss_lep_idx'.
void WWWAnalysis::processLeptonIndices()
{
    list_incl_tight_ss_lep_idx.clear();
    list_incl_tight_3l_lep_idx.clear();
    list_incl_loose_ss_lep_idx.clear();
    list_incl_loose_3l_lep_idx.clear();
    list_incl_veto_ss_lep_idx.clear();
    list_incl_veto_3l_lep_idx.clear();

    // Tights just need to be a copy of itself.
    list_incl_tight_ss_lep_idx.insert(list_incl_tight_ss_lep_idx.end(), list_tight_ss_lep_idx.begin(), list_tight_ss_lep_idx.end());
    list_incl_tight_3l_lep_idx.insert(list_incl_tight_3l_lep_idx.end(), list_tight_3l_lep_idx.begin(), list_tight_3l_lep_idx.end());

    // The loose needs to have tight + loose
    list_incl_loose_ss_lep_idx.insert(list_incl_loose_ss_lep_idx.end(), list_tight_ss_lep_idx.begin(), list_tight_ss_lep_idx.end());
    list_incl_loose_ss_lep_idx.insert(list_incl_loose_ss_lep_idx.end(), list_loose_ss_lep_idx.begin(), list_loose_ss_lep_idx.end());
    list_incl_loose_3l_lep_idx.insert(list_incl_loose_3l_lep_idx.end(), list_tight_3l_lep_idx.begin(), list_tight_3l_lep_idx.end());
    list_incl_loose_3l_lep_idx.insert(list_incl_loose_3l_lep_idx.end(), list_loose_3l_lep_idx.begin(), list_loose_3l_lep_idx.end());

    // The loose needs to have tight + veto
    list_incl_veto_ss_lep_idx.insert(list_incl_veto_ss_lep_idx.end(), list_tight_ss_lep_idx.begin(), list_tight_ss_lep_idx.end());
    list_incl_veto_ss_lep_idx.insert(list_incl_veto_ss_lep_idx.end(), list_veto_ss_lep_idx.begin(), list_veto_ss_lep_idx.end());
    list_incl_veto_3l_lep_idx.insert(list_incl_veto_3l_lep_idx.end(), list_tight_3l_lep_idx.begin(), list_tight_3l_lep_idx.end());
    list_incl_veto_3l_lep_idx.insert(list_incl_veto_3l_lep_idx.end(), list_veto_3l_lep_idx.begin(), list_veto_3l_lep_idx.end());

    // Then sort them
    sort(list_incl_loose_ss_lep_idx.begin(), list_incl_loose_ss_lep_idx.end(), sortPt);
    sort(list_incl_loose_3l_lep_idx.begin(), list_incl_loose_3l_lep_idx.end(), sortPt);
    sort(list_incl_veto_ss_lep_idx.begin(), list_incl_veto_ss_lep_idx.end(), sortPt);
    sort(list_incl_veto_3l_lep_idx.begin(), list_incl_veto_3l_lep_idx.end(), sortPt);
}


//#################################################################################################
// Set the TTreeX branches with the variables calculated from calcStdVariables()(
void WWWAnalysis::setBranches()
{
    using namespace tas;
    ttreex.setBranch<LV>("veto_ss_lep0" , list_incl_veto_ss_lep_idx.size() > 0 ? lep_p4()[list_incl_veto_ss_lep_idx[0]] : LV());
    ttreex.setBranch<LV>("veto_ss_lep1" , list_incl_veto_ss_lep_idx.size() > 1 ? lep_p4()[list_incl_veto_ss_lep_idx[1]] : LV());

    ttreex.setBranch<LV>("veto_3l_lep0" , list_incl_veto_3l_lep_idx.size() > 0 ? lep_p4()[list_incl_veto_3l_lep_idx[0]] : LV());
    ttreex.setBranch<LV>("veto_3l_lep1" , list_incl_veto_3l_lep_idx.size() > 1 ? lep_p4()[list_incl_veto_3l_lep_idx[1]] : LV());
    ttreex.setBranch<LV>("veto_3l_lep2" , list_incl_veto_3l_lep_idx.size() > 2 ? lep_p4()[list_incl_veto_3l_lep_idx[2]] : LV());

    ttreex.setBranch<int>("veto_ss_lep0_pdgid" , list_incl_veto_ss_lep_idx.size() > 0 ? lep_pdgId()[list_incl_veto_ss_lep_idx[0]] : 0);
    ttreex.setBranch<int>("veto_ss_lep1_pdgid" , list_incl_veto_ss_lep_idx.size() > 1 ? lep_pdgId()[list_incl_veto_ss_lep_idx[1]] : 0);

    ttreex.setBranch<int>("veto_3l_lep0_pdgid" , list_incl_veto_3l_lep_idx.size() > 0 ? lep_pdgId()[list_incl_veto_3l_lep_idx[0]] : 0);
    ttreex.setBranch<int>("veto_3l_lep1_pdgid" , list_incl_veto_3l_lep_idx.size() > 1 ? lep_pdgId()[list_incl_veto_3l_lep_idx[1]] : 0);
    ttreex.setBranch<int>("veto_3l_lep2_pdgid" , list_incl_veto_3l_lep_idx.size() > 2 ? lep_pdgId()[list_incl_veto_3l_lep_idx[2]] : 0);

    ttreex.setBranch<int>("n_tight_ss_lep", list_incl_tight_ss_lep_idx.size());
    ttreex.setBranch<int>("n_tight_3l_lep", list_incl_tight_3l_lep_idx.size());
    ttreex.setBranch<int>("n_loose_ss_lep", list_incl_loose_ss_lep_idx.size());
    ttreex.setBranch<int>("n_loose_3l_lep", list_incl_loose_3l_lep_idx.size());
    ttreex.setBranch<int>("n_veto_ss_lep", list_incl_veto_ss_lep_idx.size());
    ttreex.setBranch<int>("n_veto_3l_lep", list_incl_veto_3l_lep_idx.size());

    ttreex.setBranch<int>("ntrk", ntrk);
    ttreex.setBranch<int>("nSFOS", nSFOS);

    ttreex.setBranch<LV>("MET", MET);
    ttreex.setBranch<LV>("MET_up", MET_up);
    ttreex.setBranch<LV>("MET_dn", MET_dn);

    ttreex.setBranch<int>("nj", nj);
    ttreex.setBranch<int>("nb", nb);
    ttreex.setBranch<int>("nj30", nj30);
    ttreex.setBranch<float>("Mjj", Mjj);
    ttreex.setBranch<float>("MjjL", MjjL);
    ttreex.setBranch<float>("Detajj", Detajj);

    ttreex.setBranch<int>("nj_up", nj_up);
    ttreex.setBranch<int>("nb_up", nb_up);
    ttreex.setBranch<int>("nj30_up", nj30_up);
    ttreex.setBranch<float>("Mjj_up", Mjj_up);
    ttreex.setBranch<float>("MjjL_up", MjjL_up);
    ttreex.setBranch<float>("Detajj_up", Detajj_up);

    ttreex.setBranch<int>("nj_dn", nj_dn);
    ttreex.setBranch<int>("nb_dn", nb_dn);
    ttreex.setBranch<int>("nj30_dn", nj30_dn);
    ttreex.setBranch<float>("Mjj_dn", Mjj_dn);
    ttreex.setBranch<float>("MjjL_dn", MjjL_dn);
    ttreex.setBranch<float>("Detajj_dn", Detajj_dn);

    ttreex.setBranch<float>("MTmax", MTmax);
    ttreex.setBranch<float>("MTmax_up", MTmax_up);
    ttreex.setBranch<float>("MTmax_dn", MTmax_dn);
    ttreex.setBranch<float>("MTmax3l", MTmax3l);
    ttreex.setBranch<float>("MT1SFOS", MT1SFOS);

    ttreex.setBranch<float>("MllSS", MllSS);
    ttreex.setBranch<float>("MeeSS", MeeSS);
    ttreex.setBranch<float>("Mll0SFOS", Mll0SFOS);
    ttreex.setBranch<float>("Mee0SFOS", Mee0SFOS);
    ttreex.setBranch<float>("Mll1SFOS", Mll1SFOS);
    ttreex.setBranch<float>("Mll2SFOS0", Mll2SFOS0);
    ttreex.setBranch<float>("Mll2SFOS1", Mll2SFOS1);

    ttreex.setBranch<float>("weight", weight);
    ttreex.setBranch<float>("btagsf", btagsf);
    ttreex.setBranch<float>("btagsf_hfup", btagsf_hfup);
    ttreex.setBranch<float>("btagsf_hfdn", btagsf_hfdn);
    ttreex.setBranch<float>("btagsf_lfup", btagsf_lfup);
    ttreex.setBranch<float>("btagsf_lfdn", btagsf_lfdn);
    ttreex.setBranch<float>("purewgt", purewgt);
    ttreex.setBranch<float>("purewgt_up", purewgt_up);
    ttreex.setBranch<float>("purewgt_dn", purewgt_dn);
    ttreex.setBranch<float>("lepsf", lepsf);
    ttreex.setBranch<float>("lepsf_err", lepsf_err);
    ttreex.setBranch<float>("trigsf", trigsf);
    ttreex.setBranch<float>("trigsf_err", trigsf_err);

    ttreex.setBranch<bool>("pass_offline_trig", pass_offline_trig);
    ttreex.setBranch<bool>("pass_online_trig", pass_online_trig);
    ttreex.setBranch<bool>("pass_filters", pass_filters);
    ttreex.setBranch<bool>("pass_goodrun", pass_goodrun);

    ttreex.setBranch<TString>("sample_name", sample_name);
    ttreex.setBranch<TString>("process_name_ss", process_name_ss);
    ttreex.setBranch<TString>("process_name_3l", process_name_3l);
    ttreex.setBranch<bool>("isphotonSS", isphotonSS);
    ttreex.setBranch<bool>("isphoton3l", isphoton3l);

    ttreex.setBranch<int>("run_number", run_number);
    ttreex.setBranch<int>("lumiblock_number", lumiblock_number);
    ttreex.setBranch<int>("event_number", event_number);

    ttreex.setBranch<float>("gen_Mjj", gen_Mjj);
    ttreex.setBranch<float>("gen_DEtajj", gen_DEtajj);
    ttreex.setBranch<float>("gen_DRjj", gen_DRjj);

    ttreex.setBranch<LV>("gen_quark0", list_gen_quarks.size() > 0 ? genPart_p4()[list_gen_quarks[0]] : LV());
    ttreex.setBranch<LV>("gen_quark1", list_gen_quarks.size() > 1 ? genPart_p4()[list_gen_quarks[1]] : LV());
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
    is_initialized = false;
    blindSR = true;
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
    return "NotUsed";
}

//#################################################################################################
// From the output of the WWWAnalysis main functions run cutflow
void WWWAnalysis::cutflow()
{
//    TMultiDrawTreePlayer* p = RooUtil::FileUtil::createTMulti(chain);
    TMultiDrawTreePlayer* p = RooUtil::FileUtil::createTMulti("t", "/hadoop/cms/store/user/phchang/metis/wwwlooper/v2/WWW_v0_1_16_v2/www_2l_*mia_skim_1.root");
    if (!p)
        RooUtil::error("Failed to create TMulti");
    std::cout << p << std::endl;
    std::vector<TString> cuts;
    cuts.push_back("ntrk == 0");
    cuts.push_back("pass_offline_trig>0");
    cuts.push_back("(veto_ss_lep0_pdgid*veto_ss_lep1_pdgid)==169");
    cuts.push_back("n_tight_ss_lep>=2");
    cuts.push_back("n_veto_ss_lep==2");
//    cuts.push_back("sample_name==\"WHtoWWW\"");
    cuts.push_back("nj30>=2");
    cuts.push_back("(Mjj<100.&&Mjj>60.)");
    cuts.push_back("nb==0");
    cuts.push_back("MllSS > 40.");
    cuts.push_back("MjjL < 400.");
    cuts.push_back("Detajj < 1.5");

    std::map<TString, TString> hists;
    hists["count"] = "0>>%s%zu(1, 0, 1)";
    hists["gen_DRjj"] = "gen_DRjj>>%s%zu(50, 0, 9)";
    hists["Mjj"] = "Mjj>>%s%zu(30, 0, 150)";
    hists["gen_quark0_pt"] = "((gen_quark0.pt() > gen_quark1.pt())*(gen_quark0.pt()) + (gen_quark1.pt() > gen_quark0.pt())*(gen_quark1.pt()))>>%s%zu(30, 0, 150)";
    hists["gen_quark1_pt"] = "((gen_quark0.pt() > gen_quark1.pt())*(gen_quark1.pt()) + (gen_quark1.pt() > gen_quark0.pt())*(gen_quark0.pt()))>>%s%zu(30, 0, 150)";
    hists["gen_quark0_eta"] = "((gen_quark0.pt() > gen_quark1.pt())*(gen_quark0.eta()) + (gen_quark1.pt() > gen_quark0.pt())*(gen_quark1.eta()))>>%s%zu(30, -5, 5)";
    hists["gen_quark1_eta"] = "((gen_quark0.pt() > gen_quark1.pt())*(gen_quark1.eta()) + (gen_quark1.pt() > gen_quark0.pt())*(gen_quark0.eta()))>>%s%zu(30, -5, 5)";
    hists["Mjj_v_gen_quark1_pt"] = "Mjj:((gen_quark0.pt() > gen_quark1.pt())*(gen_quark1.pt()) + (gen_quark1.pt() > gen_quark0.pt())*(gen_quark0.pt()))>>%s%zu(30, 0, 150, 30, 0, 150)";
    hists["Mjj_v_gen_quark1_pt"] = "Mjj:((gen_quark0.pt() > gen_quark1.pt())*(gen_quark1.pt()) + (gen_quark1.pt() > gen_quark0.pt())*(gen_quark0.pt()))>>%s%zu(30, 0, 150, 30, 0, 150)";

    for (size_t i = 0; i < cuts.size(); ++i)
    {
        for (auto& hist : hists)
        {
            TString bookHist = Form(hist.second.Data(), hist.first.Data(), i);
            TString cut = Form("(%s)*(weight*btagsf*lepsf*trigsf*purewgt)", RooUtil::StringUtil::join(std::vector<TString>(cuts.begin(), cuts.begin() + i + 1), ")*(").Data());
//            std::cout << bookHist << " " << cut << std::endl;
            p->queueDraw(bookHist.Data(), cut.Data(), "goffe");
        }
    }

    p->execute();

    std::cout << " " << std::endl;

    std::map<TString, TH1*> ret_hists;
    for (size_t i = 0; i < cuts.size(); ++i)
    {
        for (auto& hist : hists)
        {
            TString histname = Form("%s%zu", hist.first.Data(), i);
            TH1* h = RooUtil::FileUtil::get(histname);
            if (h)
                ret_hists[histname] = h;
            if (hist.first.EqualTo("count"))
                std::cout << h->GetBinContent(1) << " +/- " << h->GetBinError(1) << " " << cuts.at(i) << std::endl;
        }
    }

    // Set the output file
    ofile = new TFile(output_name, "recreate"); 
    for (auto& hist : ret_hists)
        if (hist.second)
            hist.second->Write();
}

//eof
