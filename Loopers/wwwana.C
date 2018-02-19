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
#include "rooutil/json.h"
#include "rooutil/draw.h"

#include "CMS3_WWW0118.h"
#include "Functions.h"

#include "Math/VectorUtil.h"
#include "TString.h"

#include <map>
#include <vector>

using json = nlohmann::json;
using namespace RooUtil::StringUtil;

using namespace tas;

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
    TTree* otree_www;
    TTree* otree_prompt;
    TTree* otree_qflip;
    TTree* otree_lostlep;
    TTree* otree_fakes;
    TTree* otree_photon;
    TTree* otree_others;
    TChain* chain;
    std::map<TString, std::vector<TString>> datasetMap;
    RooUtil::Looper<CMS3> looper;
    RooUtil::EventList eventlist;
    RooUtil::TTreeX ttreex;
    RooUtil::TTreeX ttreex_www;
    RooUtil::TTreeX ttreex_prompt;
    RooUtil::TTreeX ttreex_qflip;
    RooUtil::TTreeX ttreex_lostlep;
    RooUtil::TTreeX ttreex_fakes;
    RooUtil::TTreeX ttreex_photon;
    RooUtil::TTreeX ttreex_others;

    //---------------------------------------------------------------------------------------------
    // Configurational related variables
    //---------------------------------------------------------------------------------------------
    bool is_initialized;
    TString eventlist_file_path;
    bool blindSR;
    bool storeeventnumbers;
    json _j;

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

    // lepton flavor product
    int lep_flav_prod_ss;
    int lep_flav_prod_3l;

    // track multiplicity
    int ntrk;

    // SFOS
    int nSFOS;
    int nSFOSinZ;

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
    float MT1SFOS;

    // Lepton + Lepton variables
    float MllSS;
    float MeeSS;
    float Mll0SFOS;
    float Mee0SFOS;
    float Mll1SFOS;
    float Mll2SFOS0;
    float Mll2SFOS1;
    float Pt3l;
    float DPhi3lMET;
    float M3l;

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
    float ffwgtss;
    float ffwgt3l;
    float ffwgtss_err;
    float ffwgt3l_err;
    float ffwgtss_nocone;
    float ffwgt3l_nocone;
    float ffwgtss_nocone_err;
    float ffwgt3l_nocone_err;
    float ffwgtss_closerr;
    float ffwgt3l_closerr;
    float qcdffwgtss;
    float qcdffwgt3l;
    float qcdffwgtss_err;
    float qcdffwgt3l_err;
    float qcdffwgtss_nocone;
    float qcdffwgt3l_nocone;
    float qcdffwgtss_nocone_err;
    float qcdffwgt3l_nocone_err;
    float qcdffwgtss_closerr;
    float qcdffwgt3l_closerr;

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
    bool vetophotonss;
    bool vetophoton3l;

    // Event ID
    int run_number;
    int lumiblock_number;
    unsigned long long event_number;

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
    void createBranches(RooUtil::TTreeX& ttreex);
    void run();
    void setBranches(RooUtil::TTreeX& ttreex);
    void setDatasetMap();
    void setChain();
    bool calcStdVariables();
    void processLeptonIndices();
    void checkEvent();
    TString getSampleNameFromFileName(TString);

    void runAnalysis();
    void readAnalysis();

    void sandbox();

    bool getleptonindices_lepopt(vector<int> &iSS, vector<int> &i3l, vector<int> &iaSS, vector<int> &ia3l, vector<int> &vSS, vector<int> &v3l, vector<int> &vaSS, vector<int> &va3l);
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

//        // Default configuration file
//        ifstream default_config(".wwwana.json");
//        default_config >> wwwanalysis._j;

        // If no babydir option is given, take the default one
        if (!options.count("babydir") && !options.count("input"))
        {
            TString default_baby_dir_path = wwwanalysis._j["default_baby_dir_path"];
            //RooUtil::print(Form("No baby dir path is provided. Using the default one=%s", default_baby_dir_path.Data()));
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
        otree         = new TTree("t"         , "WWWAnalysis Output TTree");
        otree_www     = new TTree("t_www"     , "WWWAnalysis Output TTree WWW signal events only");
        otree_prompt  = new TTree("t_prompt"  , "WWWAnalysis Output TTree Prompt background events only");
        otree_qflip   = new TTree("t_qflip"   , "WWWAnalysis Output TTree Q-flip background events only");
        otree_lostlep = new TTree("t_lostlep" , "WWWAnalysis Output TTree lost-lep background events only");
        otree_fakes   = new TTree("t_fakes"   , "WWWAnalysis Output TTree fake backgrounds only");
        otree_photon  = new TTree("t_photon"  , "WWWAnalysis Output TTree photon-fakes backgrounds only");
        otree_others  = new TTree("t_others"  , "WWWAnalysis Output TTree other backgrounds");

        // Hook the otree to TTreeX
        ttreex        .setTree(otree);
        ttreex_www    .setTree(otree_www);
        ttreex_prompt .setTree(otree_prompt);
        ttreex_qflip  .setTree(otree_qflip);
        ttreex_lostlep.setTree(otree_lostlep);
        ttreex_fakes  .setTree(otree_fakes);
        ttreex_photon .setTree(otree_photon);
        ttreex_others .setTree(otree_others);

        // Create branches to the output TTree
        createBranches(ttreex);
        createBranches(ttreex_www);
        createBranches(ttreex_prompt);
        createBranches(ttreex_qflip);
        createBranches(ttreex_lostlep);
        createBranches(ttreex_fakes);
        createBranches(ttreex_photon);
        createBranches(ttreex_others);

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
void WWWAnalysis::createBranches(RooUtil::TTreeX& t)
{
    t.createBranch<LV>("veto_ss_lep0");
    t.createBranch<LV>("veto_ss_lep1");

    t.createBranch<LV>("veto_3l_lep0");
    t.createBranch<LV>("veto_3l_lep1");
    t.createBranch<LV>("veto_3l_lep2");

    t.createBranch<int>("veto_ss_lep0_pdgid");
    t.createBranch<int>("veto_ss_lep1_pdgid");

    t.createBranch<float>("veto_ss_lep0_bdt1");
    t.createBranch<float>("veto_ss_lep1_bdt1");

    t.createBranch<float>("veto_ss_lep0_bdt2");
    t.createBranch<float>("veto_ss_lep1_bdt2");

    t.createBranch<float>("veto_ss_lep0_bdt3");
    t.createBranch<float>("veto_ss_lep1_bdt3");

    t.createBranch<float>("veto_ss_lep0_pterr");
    t.createBranch<float>("veto_ss_lep1_pterr");

    t.createBranch<float>("veto_ss_lep0_trkpt");
    t.createBranch<float>("veto_ss_lep1_trkpt");

    t.createBranch<float>("veto_ss_lep0_reliso");
    t.createBranch<float>("veto_ss_lep1_reliso");

    t.createBranch<float>("veto_ss_lep0_ptrel");
    t.createBranch<float>("veto_ss_lep1_ptrel");

    t.createBranch<float>("veto_ss_lep0_ptratio");
    t.createBranch<float>("veto_ss_lep1_ptratio");

    t.createBranch<float>("veto_ss_lep0_ip3d");
    t.createBranch<float>("veto_ss_lep1_ip3d");

    t.createBranch<float>("veto_ss_lep0_ip3derr");
    t.createBranch<float>("veto_ss_lep1_ip3derr");

    t.createBranch<float>("veto_ss_lep0_conecorrpt");
    t.createBranch<float>("veto_ss_lep1_conecorrpt");

    t.createBranch<int>("veto_ss_lep0_motheridss");
    t.createBranch<int>("veto_ss_lep1_motheridss");

    t.createBranch<bool>("veto_ss_lep0_medium");
    t.createBranch<bool>("veto_ss_lep1_medium");

    t.createBranch<bool>("veto_ss_lep0_loose");
    t.createBranch<bool>("veto_ss_lep1_loose");

    t.createBranch<bool>("veto_ss_lep0_tight");
    t.createBranch<bool>("veto_ss_lep1_tight");

    t.createBranch<int>("veto_3l_lep0_pdgid");
    t.createBranch<int>("veto_3l_lep1_pdgid");
    t.createBranch<int>("veto_3l_lep2_pdgid");

    t.createBranch<int>("n_tight_ss_lep");
    t.createBranch<int>("n_tight_3l_lep");
    t.createBranch<int>("n_loose_ss_lep");
    t.createBranch<int>("n_loose_3l_lep");
    t.createBranch<int>("n_veto_ss_lep");
    t.createBranch<int>("n_veto_3l_lep");

    t.createBranch<int>("lep_flav_prod_ss");
    t.createBranch<int>("lep_flav_prod_3l");

    t.createBranch<int>("ntrk");
    t.createBranch<int>("nSFOS");
    t.createBranch<int>("nSFOSinZ");

    t.createBranch<LV>("MET");
    t.createBranch<LV>("MET_up");
    t.createBranch<LV>("MET_dn");

    t.createBranch<int>("nj");
    t.createBranch<int>("nb");
    t.createBranch<int>("nj30");
    t.createBranch<float>("Mjj");
    t.createBranch<float>("MjjL");
    t.createBranch<float>("Detajj");

    t.createBranch<int>("nj_up");
    t.createBranch<int>("nb_up");
    t.createBranch<int>("nj30_up");
    t.createBranch<float>("Mjj_up");
    t.createBranch<float>("MjjL_up");
    t.createBranch<float>("Detajj_up");

    t.createBranch<int>("nj_dn");
    t.createBranch<int>("nb_dn");
    t.createBranch<int>("nj30_dn");
    t.createBranch<float>("Mjj_dn");
    t.createBranch<float>("MjjL_dn");
    t.createBranch<float>("Detajj_dn");

    t.createBranch<float>("MTmax");
    t.createBranch<float>("MTmax_up");
    t.createBranch<float>("MTmax_dn");
    t.createBranch<float>("MTmax3l");
    t.createBranch<float>("MT1SFOS");

    t.createBranch<float>("MllSS");
    t.createBranch<float>("MeeSS");
    t.createBranch<float>("Mll0SFOS");
    t.createBranch<float>("Mee0SFOS");
    t.createBranch<float>("Mll1SFOS");
    t.createBranch<float>("Mll2SFOS0");
    t.createBranch<float>("Mll2SFOS1");
    t.createBranch<float>("Pt3l");
    t.createBranch<float>("DPhi3lMET");
    t.createBranch<float>("M3l");

    t.createBranch<float>("weight");
    t.createBranch<float>("btagsf");
    t.createBranch<float>("btagsf_hfup");
    t.createBranch<float>("btagsf_hfdn");
    t.createBranch<float>("btagsf_lfup");
    t.createBranch<float>("btagsf_lfdn");
    t.createBranch<float>("purewgt");
    t.createBranch<float>("purewgt_up");
    t.createBranch<float>("purewgt_dn");
    t.createBranch<float>("lepsf");
    t.createBranch<float>("lepsf_err");
    t.createBranch<float>("trigsf");
    t.createBranch<float>("trigsf_err");
    t.createBranch<float>("ffwgtss");
    t.createBranch<float>("ffwgt3l");
    t.createBranch<float>("ffwgtss_err");
    t.createBranch<float>("ffwgt3l_err");
    t.createBranch<float>("ffwgtss_nocone");
    t.createBranch<float>("ffwgt3l_nocone");
    t.createBranch<float>("ffwgtss_nocone_noerr");
    t.createBranch<float>("ffwgt3l_nocone_noerr");
    t.createBranch<float>("ffwgtss_closerr");
    t.createBranch<float>("ffwgt3l_closerr");
    t.createBranch<float>("qcdffwgtss");
    t.createBranch<float>("qcdffwgt3l");
    t.createBranch<float>("qcdffwgtss_err");
    t.createBranch<float>("qcdffwgt3l_err");
    t.createBranch<float>("qcdffwgtss_nocone");
    t.createBranch<float>("qcdffwgt3l_nocone");
    t.createBranch<float>("qcdffwgtss_nocone_noerr");
    t.createBranch<float>("qcdffwgt3l_nocone_noerr");
    t.createBranch<float>("qcdffwgtss_closerr");
    t.createBranch<float>("qcdffwgt3l_closerr");

    t.createBranch<bool>("pass_offline_trig");
    t.createBranch<bool>("pass_online_trig");
    t.createBranch<bool>("pass_filters");
    t.createBranch<bool>("pass_goodrun");

    t.createBranch<TString>("sample_name");
    t.createBranch<TString>("process_name_ss");
    t.createBranch<TString>("process_name_3l");
    t.createBranch<bool>("isphotonSS");
    t.createBranch<bool>("isphoton3l");
    t.createBranch<bool>("vetophotonss");
    t.createBranch<bool>("vetophoton3l");

    t.createBranch<int>("run_number");
    t.createBranch<int>("lumiblock_number");
    t.createBranch<unsigned long long>("event_number");

    t.createBranch<float>("gen_Mjj");
    t.createBranch<float>("gen_DEtajj");
    t.createBranch<float>("gen_DRjj");

    t.createBranch<LV>("gen_quark0");
    t.createBranch<LV>("gen_quark1");
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

        // Fill the TTree
        setBranches(ttreex);
        ttreex.fill();
        if (process_name_ss.EqualTo("WWW") || process_name_3l.EqualTo("WHtoWWW"))
        {
            setBranches(ttreex_www);
            ttreex_www.fill();
        }
        if (process_name_ss.EqualTo("trueSS") || process_name_3l.EqualTo("true3L") || process_name_3l.EqualTo("trueWWW"))
        {
            setBranches(ttreex_prompt);
            ttreex_prompt.fill();
        }
        if (process_name_ss.EqualTo("chargeflips") || process_name_3l.EqualTo("chargeflips"))
        {
            setBranches(ttreex_qflip);
            ttreex_qflip.fill();
        }
        if (process_name_ss.EqualTo("SSLL") || process_name_3l.EqualTo("3lLL"))
        {
            setBranches(ttreex_lostlep);
            ttreex_lostlep.fill();
        }
        if (process_name_ss.EqualTo("fakes") || process_name_3l.EqualTo("fakes"))
        {
            setBranches(ttreex_fakes);
            ttreex_fakes.fill();
        }
        if (process_name_ss.EqualTo("photonfakes") || process_name_3l.EqualTo("photonfakes"))
        {
            setBranches(ttreex_photon);
            ttreex_photon.fill();
        }
        if (process_name_ss.EqualTo("others") || process_name_3l.EqualTo("others"))
        {
            setBranches(ttreex_others);
            ttreex_others.fill();
        }

        // checking events with run/lumi/evt matching in the list provided.
        if (eventlist.has(tas::run(), tas::lumi(), tas::evt())) checkEvent();
    }

    // Save the TTree
    ttreex.save(ofile);
    ttreex_www.save(ofile);
    ttreex_prompt.save(ofile);
    ttreex_qflip.save(ofile);
    ttreex_lostlep.save(ofile);
    ttreex_fakes.save(ofile);
    ttreex_photon.save(ofile);
    ttreex_others.save(ofile);
}

//#################################################################################################
// Compute mgammapt
float gammapt()
{
    using namespace tas;

    // Compute mgammapt
    for (unsigned int igen = 0; igen < tas::genPart_pdgId().size(); ++igen)
    {
        if (abs(genPart_pdgId()[igen]) == 22 && abs(genPart_status()[igen]) == 23)
        {
            return genPart_p4()[igen].pt();
        }
    }

    // If no gamma found try finding a status 1 with 24 as mother
    for (unsigned int igen = 0; igen < tas::genPart_pdgId().size(); ++igen)
    {
        if (abs(genPart_pdgId()[igen]) == 22 && abs(genPart_motherId()[igen]) == 24 && abs(genPart_status()[igen]) == 1)
        {
            return genPart_p4()[igen].pt();
        }
    }
    return -999;
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
    getleptonindices(list_tight_ss_lep_idx, list_tight_3l_lep_idx, list_loose_ss_lep_idx, list_loose_3l_lep_idx, list_veto_ss_lep_idx, list_veto_3l_lep_idx, list_looseveto_ss_lep_idx, list_looseveto_3l_lep_idx, 1, 25., 20.);
    //getleptonindices_lepopt(list_tight_ss_lep_idx, list_tight_3l_lep_idx, list_loose_ss_lep_idx, list_loose_3l_lep_idx, list_veto_ss_lep_idx, list_veto_3l_lep_idx, list_looseveto_ss_lep_idx, list_looseveto_3l_lep_idx);

    // I like to keep the lepton indices to be more about what they actually mean.
    processLeptonIndices();

    // Preselection. Events not passing these are never used anywhere.
    if (firstgoodvertex() != 0)   { return false; }
    if (nVert() < 0)              { return false; }
    if (looper.getCurrentFileName().Contains("wjets_incl_mgmlm_")  && gen_ht() > 100) { return false; }
    if (looper.getCurrentFileName().Contains("dy_m50_mgmlm_ext1_") && gen_ht() > 100) { return false; }
    if (list_tight_3l_lep_idx.size() < 1) { return false; }
    if (list_tight_3l_lep_idx.size() + list_loose_3l_lep_idx.size() < 2) { return false; }
    if (list_incl_veto_3l_lep_idx.size() != 2 && list_incl_veto_3l_lep_idx.size() != 3) { return false; }
    int totalcharge = 0;
    for (auto& idx : list_incl_veto_3l_lep_idx)
    {
        if (lep_pdgId()[idx] > 0)
            totalcharge--;
        else
            totalcharge++;
    }
    if (list_incl_veto_3l_lep_idx.size() == 3 && abs(totalcharge) != 1) { return false; }

    // Sample names and types
    sample_name = "";
    process_name_ss = "";
    process_name_3l = "";
    sample_name = getSampleNameFromFileName(looper.getCurrentFileBaseName());
    process_name_ss = ((list_tight_ss_lep_idx.size() + list_loose_ss_lep_idx.size()) >= 2) ? process(looper.getCurrentFileName().Data(), true , list_tight_ss_lep_idx, list_loose_ss_lep_idx) : "not2l";
    process_name_3l = ((list_tight_3l_lep_idx.size() + list_loose_3l_lep_idx.size()) >= 3) ? process(looper.getCurrentFileName().Data(), false, list_tight_3l_lep_idx, list_loose_3l_lep_idx) : "not3l";
    isphotonSS = process_name_ss.EqualTo("photonfakes");
    isphoton3l = process_name_3l.EqualTo("photonfakes");

    // veto events with photon fakes
    vetophotonss = vetophotonprocess(looper.getCurrentFileBaseName().Data(), isphotonSS);
    vetophoton3l = vetophotonprocess(looper.getCurrentFileBaseName().Data(), isphoton3l);

    // lepton flavor product
    lep_flav_prod_ss = 0;
    lep_flav_prod_3l = 0;
    if (list_incl_veto_ss_lep_idx.size() == 2)
    {
        lep_flav_prod_ss = lep_pdgId()[list_incl_veto_ss_lep_idx[0]] * lep_pdgId()[list_incl_veto_ss_lep_idx[1]];
    }
    else if (list_incl_veto_3l_lep_idx.size() == 3)
    {
        if (lep_pdgId()[list_incl_veto_3l_lep_idx[0]] * lep_pdgId()[list_incl_veto_3l_lep_idx[1]] > 0)
            lep_flav_prod_3l = lep_pdgId()[list_incl_veto_3l_lep_idx[0]] * lep_pdgId()[list_incl_veto_3l_lep_idx[1]];
        else if (lep_pdgId()[list_incl_veto_3l_lep_idx[0]] * lep_pdgId()[list_incl_veto_3l_lep_idx[2]] > 0)
            lep_flav_prod_3l = lep_pdgId()[list_incl_veto_3l_lep_idx[0]] * lep_pdgId()[list_incl_veto_3l_lep_idx[2]];
        else if (lep_pdgId()[list_incl_veto_3l_lep_idx[1]] * lep_pdgId()[list_incl_veto_3l_lep_idx[2]] > 0)
            lep_flav_prod_3l = lep_pdgId()[list_incl_veto_3l_lep_idx[1]] * lep_pdgId()[list_incl_veto_3l_lep_idx[2]];
    }

    // Set MET
    MET.SetPxPyPzE( met_pt() * TMath::Cos(met_phi()), met_pt() * TMath::Sin(met_phi()), 0, met_pt());
    MET_up.SetPxPyPzE( met_T1CHS_miniAOD_CORE_up_pt() * TMath::Cos(met_T1CHS_miniAOD_CORE_up_phi()), met_T1CHS_miniAOD_CORE_up_pt() * TMath::Sin(met_T1CHS_miniAOD_CORE_up_phi()), 0, met_T1CHS_miniAOD_CORE_up_pt());
    MET_dn.SetPxPyPzE( met_T1CHS_miniAOD_CORE_dn_pt() * TMath::Cos(met_T1CHS_miniAOD_CORE_dn_phi()), met_T1CHS_miniAOD_CORE_dn_pt() * TMath::Sin(met_T1CHS_miniAOD_CORE_dn_phi()), 0, met_T1CHS_miniAOD_CORE_dn_pt());

    // Set jet related variables
    nj = -1; // Number of central jets.
    nb = -1; // Number of b-tagged jets.
    nj30 = -1; // Number of jets with abs(eta) up to 5.
    Mjj = -1; // Mjj with two closest jets.
    MjjL = -1; // Mjj with two leading jets.
    Detajj = -1; // Detajj with two leading jets.
    nj_up = -1; // Number of central jets.
    nb_up = -1; // Number of b-tagged jets.
    nj30_up = -1; // Number of jets with abs(eta) up to 5.
    Mjj_up = -1; // Mjj with two closest jets.
    MjjL_up = -1; // Mjj with two leading jets.
    Detajj_up = -1; // Detajj with two leading jets.
    nj_dn = -1; // Number of central jets.
    nb_dn = -1; // Number of b-tagged jets.
    nj30_dn = -1; // Number of jets with abs(eta) dn to 5.
    Mjj_dn = -1; // Mjj with two closest jets.
    MjjL_dn = -1; // Mjj with two leading jets.
    Detajj_dn = -1; // Detajj with two leading jets.
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

    ffwgtss = 0;
    ffwgt3l = 0;
    ffwgtss_err = 0;
    ffwgt3l_err = 0;
    ffwgtss_nocone = 0;
    ffwgt3l_nocone = 0;
    ffwgtss_nocone_err = 0;
    ffwgt3l_nocone_err = 0;
    ffwgtss_closerr = 0;
    ffwgt3l_closerr = 0;
    qcdffwgtss = 0;
    qcdffwgt3l = 0;
    qcdffwgtss_err = 0;
    qcdffwgt3l_err = 0;
    qcdffwgtss_nocone = 0;
    qcdffwgt3l_nocone = 0;
    qcdffwgtss_nocone_err = 0;
    qcdffwgt3l_nocone_err = 0;
    qcdffwgtss_closerr = 0;
    qcdffwgt3l_closerr = 0;

    if (list_loose_ss_lep_idx.size() > 0)
    {
        ffwgtss_closerr    = getlepFRClosureError(list_loose_ss_lep_idx[0], true, true, 1);
        qcdffwgtss_closerr = getlepFRClosureError(list_loose_ss_lep_idx[0], false, true, 1);
        ffwgtss            = getlepFRWeightandError(ffwgtss_err,        list_loose_ss_lep_idx[0], true,  true, false, 1);
        ffwgtss_nocone     = getlepFRWeightandError(ffwgtss_nocone_err, list_loose_ss_lep_idx[0], true, false, false, 1);
        qcdffwgtss         = getlepFRWeightandError(qcdffwgtss_err,        list_loose_ss_lep_idx[0], false, true, false, 1);
        qcdffwgtss_nocone  = getlepFRWeightandError(qcdffwgtss_nocone_err, list_loose_ss_lep_idx[0], false, false, false, 1);
    }
    if (list_loose_3l_lep_idx.size() > 0)
    {
        ffwgt3l_closerr    = getlepFRClosureError(list_loose_3l_lep_idx[0], true, true, -1);
        qcdffwgt3l_closerr = getlepFRClosureError(list_loose_3l_lep_idx[0], false, true, -1);
        ffwgt3l            = getlepFRWeightandError(ffwgt3l_err,        list_loose_3l_lep_idx[0], true,  true, false, -1);
        ffwgt3l_nocone     = getlepFRWeightandError(ffwgt3l_nocone_err, list_loose_3l_lep_idx[0], true, false, false, -1);
        qcdffwgt3l         = getlepFRWeightandError(qcdffwgt3l_err,        list_loose_3l_lep_idx[0], false,  true, false, -1);
        qcdffwgt3l_nocone  = getlepFRWeightandError(qcdffwgt3l_nocone_err, list_loose_3l_lep_idx[0], false, false, false, -1);
    }

    // Offline trigger requirement (To stay on plateau)
    pass_offline_trig = passofflineTriggers(list_tight_3l_lep_idx, list_loose_3l_lep_idx);
    pass_online_trig = passonlineTriggers(list_tight_3l_lep_idx, list_loose_3l_lep_idx);

    // Event filters
    pass_filters = passFilters();

    // Good runs list
    pass_goodrun = !isData() ? 1. : goodrun(tas::run(), tas::lumi());

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

    ntrk = -1;
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
    nSFOSinZ = 0;
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
            if (fabs(Mll1SFOS-91.1876)<10.)
                nSFOSinZ = 1;
        }
        else if (nSFOS == 2)
        {
            Mll2SFOS0 = get2SFOSMll0(list_incl_veto_3l_lep_idx);;
            Mll2SFOS1 = get2SFOSMll1(list_incl_veto_3l_lep_idx);;
            if (fabs(Mll2SFOS0-91.1876)<10.)
                nSFOSinZ++;
            if (fabs(Mll2SFOS1-91.1876)<10.)
                nSFOSinZ++;
        }
    }

    Pt3l = -999;
    DPhi3lMET = -999;
    M3l = -999;
    if (list_incl_veto_3l_lep_idx.size() >= 3)
    {
        Pt3l = (lep_p4()[list_incl_veto_3l_lep_idx[0]]
                + lep_p4()[list_incl_veto_3l_lep_idx[1]]
                + lep_p4()[list_incl_veto_3l_lep_idx[2]]).Pt();
        DPhi3lMET =
            deltaPhi(
                (lep_p4()[list_incl_veto_3l_lep_idx[0]]
                 + lep_p4()[list_incl_veto_3l_lep_idx[1]]
                 + lep_p4()[list_incl_veto_3l_lep_idx[2]]).Phi(),
                MET.Phi());
        M3l = (lep_p4()[list_incl_veto_3l_lep_idx[0]]
                + lep_p4()[list_incl_veto_3l_lep_idx[1]]
                + lep_p4()[list_incl_veto_3l_lep_idx[2]]).M();

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
void WWWAnalysis::setBranches(RooUtil::TTreeX& t)
{
    using namespace tas;
    t.setBranch<LV>("veto_ss_lep0" , list_incl_veto_ss_lep_idx.size() > 0 ? lep_p4()[list_incl_veto_ss_lep_idx[0]] : LV());
    t.setBranch<LV>("veto_ss_lep1" , list_incl_veto_ss_lep_idx.size() > 1 ? lep_p4()[list_incl_veto_ss_lep_idx[1]] : LV());

    t.setBranch<LV>("veto_3l_lep0" , list_incl_veto_3l_lep_idx.size() > 0 ? lep_p4()[list_incl_veto_3l_lep_idx[0]] : LV());
    t.setBranch<LV>("veto_3l_lep1" , list_incl_veto_3l_lep_idx.size() > 1 ? lep_p4()[list_incl_veto_3l_lep_idx[1]] : LV());
    t.setBranch<LV>("veto_3l_lep2" , list_incl_veto_3l_lep_idx.size() > 2 ? lep_p4()[list_incl_veto_3l_lep_idx[2]] : LV());

    t.setBranch<int>("veto_ss_lep0_pdgid" , list_incl_veto_ss_lep_idx.size() > 0 ? lep_pdgId()[list_incl_veto_ss_lep_idx[0]] : 0);
    t.setBranch<int>("veto_ss_lep1_pdgid" , list_incl_veto_ss_lep_idx.size() > 1 ? lep_pdgId()[list_incl_veto_ss_lep_idx[1]] : 0);

    t.setBranch<float>("veto_ss_lep0_bdt1" , list_incl_veto_ss_lep_idx.size() > 0 ? lep_bdt1()[list_incl_veto_ss_lep_idx[0]] : -999);
    t.setBranch<float>("veto_ss_lep1_bdt1" , list_incl_veto_ss_lep_idx.size() > 1 ? lep_bdt1()[list_incl_veto_ss_lep_idx[1]] : -999);

    t.setBranch<float>("veto_ss_lep0_bdt2" , list_incl_veto_ss_lep_idx.size() > 0 ? lep_bdt2()[list_incl_veto_ss_lep_idx[0]] : -999);
    t.setBranch<float>("veto_ss_lep1_bdt2" , list_incl_veto_ss_lep_idx.size() > 1 ? lep_bdt2()[list_incl_veto_ss_lep_idx[1]] : -999);

    t.setBranch<float>("veto_ss_lep0_bdt3" , list_incl_veto_ss_lep_idx.size() > 0 ? lep_bdt3()[list_incl_veto_ss_lep_idx[0]] : -999);
    t.setBranch<float>("veto_ss_lep1_bdt3" , list_incl_veto_ss_lep_idx.size() > 1 ? lep_bdt3()[list_incl_veto_ss_lep_idx[1]] : -999);

    t.setBranch<float>("veto_ss_lep0_pterr", list_incl_veto_ss_lep_idx.size() > 0 ? lep_pterr()[list_incl_veto_ss_lep_idx[0]] : -999);
    t.setBranch<float>("veto_ss_lep1_pterr", list_incl_veto_ss_lep_idx.size() > 1 ? lep_pterr()[list_incl_veto_ss_lep_idx[1]] : -999);

    t.setBranch<float>("veto_ss_lep0_trkpt", list_incl_veto_ss_lep_idx.size() > 0 ? lep_trk_pt()[list_incl_veto_ss_lep_idx[0]] : -999);
    t.setBranch<float>("veto_ss_lep1_trkpt", list_incl_veto_ss_lep_idx.size() > 1 ? lep_trk_pt()[list_incl_veto_ss_lep_idx[1]] : -999);

    t.setBranch<float>("veto_ss_lep0_reliso", list_incl_veto_ss_lep_idx.size() > 0 ? lep_relIso03EAv2()[list_incl_veto_ss_lep_idx[0]] : -999);
    t.setBranch<float>("veto_ss_lep1_reliso", list_incl_veto_ss_lep_idx.size() > 1 ? lep_relIso03EAv2()[list_incl_veto_ss_lep_idx[1]] : -999);

    t.setBranch<float>("veto_ss_lep0_ptrel", list_incl_veto_ss_lep_idx.size() > 0 ? lep_ptRel()[list_incl_veto_ss_lep_idx[0]] : -999);
    t.setBranch<float>("veto_ss_lep1_ptrel", list_incl_veto_ss_lep_idx.size() > 1 ? lep_ptRel()[list_incl_veto_ss_lep_idx[1]] : -999);

    t.setBranch<float>("veto_ss_lep0_ptratio", list_incl_veto_ss_lep_idx.size() > 0 ? lep_ptRatio()[list_incl_veto_ss_lep_idx[0]] : -999);
    t.setBranch<float>("veto_ss_lep1_ptratio", list_incl_veto_ss_lep_idx.size() > 1 ? lep_ptRatio()[list_incl_veto_ss_lep_idx[1]] : -999);

    t.setBranch<float>("veto_ss_lep0_ip3d", list_incl_veto_ss_lep_idx.size() > 0 ? lep_ip3d()[list_incl_veto_ss_lep_idx[0]] : -999);
    t.setBranch<float>("veto_ss_lep1_ip3d", list_incl_veto_ss_lep_idx.size() > 1 ? lep_ip3d()[list_incl_veto_ss_lep_idx[1]] : -999);

    t.setBranch<float>("veto_ss_lep0_ip3derr", list_incl_veto_ss_lep_idx.size() > 0 ? lep_ip3derr()[list_incl_veto_ss_lep_idx[0]] : -999);
    t.setBranch<float>("veto_ss_lep1_ip3derr", list_incl_veto_ss_lep_idx.size() > 1 ? lep_ip3derr()[list_incl_veto_ss_lep_idx[1]] : -999);

    t.setBranch<float>("veto_ss_lep0_conecorrpt", list_incl_veto_ss_lep_idx.size() > 0 ? coneCorrPt(list_incl_veto_ss_lep_idx[0]) : -999);
    t.setBranch<float>("veto_ss_lep1_conecorrpt", list_incl_veto_ss_lep_idx.size() > 1 ? coneCorrPt(list_incl_veto_ss_lep_idx[1]) : -999);

    t.setBranch<int>("veto_ss_lep0_motheridss", list_incl_veto_ss_lep_idx.size() > 0 ? lep_motherIdSS()[list_incl_veto_ss_lep_idx[0]] : -999);
    t.setBranch<int>("veto_ss_lep1_motheridss", list_incl_veto_ss_lep_idx.size() > 1 ? lep_motherIdSS()[list_incl_veto_ss_lep_idx[1]] : -999);

    t.setBranch<bool>("veto_ss_lep0_medium", list_incl_veto_ss_lep_idx.size() > 0 ? lep_pass_POG_medium_noiso()[list_incl_veto_ss_lep_idx[0]] : 0);
    t.setBranch<bool>("veto_ss_lep1_medium", list_incl_veto_ss_lep_idx.size() > 1 ? lep_pass_POG_medium_noiso()[list_incl_veto_ss_lep_idx[1]] : 0);

    t.setBranch<bool>("veto_ss_lep0_loose", list_incl_veto_ss_lep_idx.size() > 0 ? lep_pass_POG_loose_noiso()[list_incl_veto_ss_lep_idx[0]] : 0);
    t.setBranch<bool>("veto_ss_lep1_loose", list_incl_veto_ss_lep_idx.size() > 1 ? lep_pass_POG_loose_noiso()[list_incl_veto_ss_lep_idx[1]] : 0);

    t.setBranch<bool>("veto_ss_lep0_tight", list_incl_veto_ss_lep_idx.size() > 0 ? lep_pass_POG_tight_noiso()[list_incl_veto_ss_lep_idx[0]] : 0);
    t.setBranch<bool>("veto_ss_lep1_tight", list_incl_veto_ss_lep_idx.size() > 1 ? lep_pass_POG_tight_noiso()[list_incl_veto_ss_lep_idx[1]] : 0);

    t.setBranch<int>("veto_3l_lep0_pdgid" , list_incl_veto_3l_lep_idx.size() > 0 ? lep_pdgId()[list_incl_veto_3l_lep_idx[0]] : 0);
    t.setBranch<int>("veto_3l_lep1_pdgid" , list_incl_veto_3l_lep_idx.size() > 1 ? lep_pdgId()[list_incl_veto_3l_lep_idx[1]] : 0);
    t.setBranch<int>("veto_3l_lep2_pdgid" , list_incl_veto_3l_lep_idx.size() > 2 ? lep_pdgId()[list_incl_veto_3l_lep_idx[2]] : 0);

    t.setBranch<int>("n_tight_ss_lep", list_incl_tight_ss_lep_idx.size());
    t.setBranch<int>("n_tight_3l_lep", list_incl_tight_3l_lep_idx.size());
    t.setBranch<int>("n_loose_ss_lep", list_incl_loose_ss_lep_idx.size());
    t.setBranch<int>("n_loose_3l_lep", list_incl_loose_3l_lep_idx.size());
    t.setBranch<int>("n_veto_ss_lep", list_incl_veto_ss_lep_idx.size());
    t.setBranch<int>("n_veto_3l_lep", list_incl_veto_3l_lep_idx.size());

    t.setBranch<int>("lep_flav_prod_ss", lep_flav_prod_ss);
    t.setBranch<int>("lep_flav_prod_3l", lep_flav_prod_3l);

    t.setBranch<int>("ntrk", ntrk);
    t.setBranch<int>("nSFOS", nSFOS);
    t.setBranch<int>("nSFOSinZ", nSFOSinZ);

    t.setBranch<LV>("MET", MET);
    t.setBranch<LV>("MET_up", MET_up);
    t.setBranch<LV>("MET_dn", MET_dn);

    t.setBranch<int>("nj", nj);
    t.setBranch<int>("nb", nb);
    t.setBranch<int>("nj30", nj30);
    t.setBranch<float>("Mjj", Mjj);
    t.setBranch<float>("MjjL", MjjL);
    t.setBranch<float>("Detajj", Detajj);

    t.setBranch<int>("nj_up", nj_up);
    t.setBranch<int>("nb_up", nb_up);
    t.setBranch<int>("nj30_up", nj30_up);
    t.setBranch<float>("Mjj_up", Mjj_up);
    t.setBranch<float>("MjjL_up", MjjL_up);
    t.setBranch<float>("Detajj_up", Detajj_up);

    t.setBranch<int>("nj_dn", nj_dn);
    t.setBranch<int>("nb_dn", nb_dn);
    t.setBranch<int>("nj30_dn", nj30_dn);
    t.setBranch<float>("Mjj_dn", Mjj_dn);
    t.setBranch<float>("MjjL_dn", MjjL_dn);
    t.setBranch<float>("Detajj_dn", Detajj_dn);

    t.setBranch<float>("MTmax", MTmax);
    t.setBranch<float>("MTmax_up", MTmax_up);
    t.setBranch<float>("MTmax_dn", MTmax_dn);
    t.setBranch<float>("MTmax3l", MTmax3l);
    t.setBranch<float>("MT1SFOS", MT1SFOS);

    t.setBranch<float>("MllSS", MllSS);
    t.setBranch<float>("MeeSS", MeeSS);
    t.setBranch<float>("Mll0SFOS", Mll0SFOS);
    t.setBranch<float>("Mee0SFOS", Mee0SFOS);
    t.setBranch<float>("Mll1SFOS", Mll1SFOS);
    t.setBranch<float>("Mll2SFOS0", Mll2SFOS0);
    t.setBranch<float>("Mll2SFOS1", Mll2SFOS1);
    t.setBranch<float>("Pt3l", Pt3l);
    t.setBranch<float>("DPhi3lMET", DPhi3lMET);
    t.setBranch<float>("M3l", M3l);

    t.setBranch<float>("weight", weight);
    t.setBranch<float>("btagsf", btagsf);
    t.setBranch<float>("btagsf_hfup", btagsf_hfup);
    t.setBranch<float>("btagsf_hfdn", btagsf_hfdn);
    t.setBranch<float>("btagsf_lfup", btagsf_lfup);
    t.setBranch<float>("btagsf_lfdn", btagsf_lfdn);
    t.setBranch<float>("purewgt", purewgt);
    t.setBranch<float>("purewgt_up", purewgt_up);
    t.setBranch<float>("purewgt_dn", purewgt_dn);
    t.setBranch<float>("lepsf", lepsf);
    t.setBranch<float>("lepsf_err", lepsf_err);
    t.setBranch<float>("trigsf", trigsf);
    t.setBranch<float>("trigsf_err", trigsf_err);
    t.setBranch<float>("ffwgtss", ffwgtss);
    t.setBranch<float>("ffwgt3l", ffwgt3l);
    t.setBranch<float>("ffwgtss_err", ffwgtss_err);
    t.setBranch<float>("ffwgt3l_err", ffwgt3l_err);
    t.setBranch<float>("ffwgtss_nocone", ffwgtss_nocone);
    t.setBranch<float>("ffwgt3l_nocone", ffwgt3l_nocone);
    t.setBranch<float>("ffwgtss_nocone_err", ffwgtss_nocone_err);
    t.setBranch<float>("ffwgt3l_nocone_err", ffwgt3l_nocone_err);
    t.setBranch<float>("ffwgtss_closerr", ffwgtss_closerr);
    t.setBranch<float>("ffwgt3l_closerr", ffwgt3l_closerr);
    t.setBranch<float>("qcdffwgtss", qcdffwgtss);
    t.setBranch<float>("qcdffwgt3l", qcdffwgt3l);
    t.setBranch<float>("qcdffwgtss_err", qcdffwgtss_err);
    t.setBranch<float>("qcdffwgt3l_err", qcdffwgt3l_err);
    t.setBranch<float>("qcdffwgtss_nocone", qcdffwgtss_nocone);
    t.setBranch<float>("qcdffwgt3l_nocone", qcdffwgt3l_nocone);
    t.setBranch<float>("qcdffwgtss_nocone_err", qcdffwgtss_nocone_err);
    t.setBranch<float>("qcdffwgt3l_nocone_err", qcdffwgt3l_nocone_err);
    t.setBranch<float>("qcdffwgtss_closerr", qcdffwgtss_closerr);
    t.setBranch<float>("qcdffwgt3l_closerr", qcdffwgt3l_closerr);


    t.setBranch<bool>("pass_offline_trig", pass_offline_trig);
    t.setBranch<bool>("pass_online_trig", pass_online_trig);
    t.setBranch<bool>("pass_filters", pass_filters);
    t.setBranch<bool>("pass_goodrun", pass_goodrun);

    t.setBranch<TString>("sample_name", sample_name);
    t.setBranch<TString>("process_name_ss", process_name_ss);
    t.setBranch<TString>("process_name_3l", process_name_3l);
    t.setBranch<bool>("isphotonSS", isphotonSS);
    t.setBranch<bool>("isphoton3l", isphoton3l);
    t.setBranch<bool>("vetophotonss", vetophotonss);
    t.setBranch<bool>("vetophoton3l", vetophoton3l);

    t.setBranch<int>("run_number", run_number);
    t.setBranch<int>("lumiblock_number", lumiblock_number);
    t.setBranch<unsigned long long>("event_number", event_number);

    t.setBranch<float>("gen_Mjj", gen_Mjj);
    t.setBranch<float>("gen_DEtajj", gen_DEtajj);
    t.setBranch<float>("gen_DRjj", gen_DRjj);

    t.setBranch<LV>("gen_quark0", list_gen_quarks.size() > 0 ? genPart_p4()[list_gen_quarks[0]] : LV());
    t.setBranch<LV>("gen_quark1", list_gen_quarks.size() > 1 ? genPart_p4()[list_gen_quarks[1]] : LV());
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
        chain = RooUtil::FileUtil::createTChain("t", join(dataset_paths));
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
    datasetMap["WG"].push_back("wgjets_pt*.root");
    datasetMap["WG"].push_back("wgjets_pt*.root");

    datasetMap["ZG"].push_back("zgamma_2lG_amc*.root");

    datasetMap["WGstar"].push_back("wgstar_lnee_012jets_madgraph*.root");
    datasetMap["WGstar"].push_back("wgstar_lnmm_012jets_madgraph*.root");

    datasetMap["DataEE"].push_back("data_*ee*.root");
    datasetMap["DataEM"].push_back("data_*em*.root");
    datasetMap["DataMM"].push_back("data_*mm*.root");
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
            std::vector<TString> tokens = split(pttn, "*");
            TString pttn1 = tokens.at(0);
            TString pttn2 = tokens.size() == 3 ? tokens.at(1) : "";
            if (filename.Contains(pttn1) && filename.Contains(pttn2))
                return dataset.first;
        }
    }
    return "NotUsed";
}

//#################################################################################################
// Get lepton indices for lepton optimization
bool WWWAnalysis::getleptonindices_lepopt(vector<int> &iSS, vector<int> &i3l, vector<int> &iaSS, vector<int> &ia3l, vector<int> &vSS, vector<int> &v3l, vector<int> &vaSS, vector<int> &va3l)
{
    // Fills in the lepton indicies for the all the different classes of lepton ID
    // But uses the BDT based isolation variables instead of relIso.
    iSS.clear();
    i3l.clear();
    iaSS.clear();
    ia3l.clear();
    vSS.clear();
    v3l.clear();
    vaSS.clear();
    va3l.clear();
    for (unsigned int i = 0; i < lep_pdgId().size(); ++i)
    {
        bool isSS    = false;
        bool is3l    = false;
        bool isaSS   = false;
        bool isa3l   = false;

        if (fabs(lep_p4()[i].Eta()) >= 2.4)
            continue;

        if (abs(lep_pdgId()[i]) == 11)
        {
            //tight ID
            if (lep_isTriggerSafe_v1()[i] && lep_pass_VVV_cutbased_tight()[i] && lep_lostHits()[i] == 0 && lep_tightCharge()[i] == 2)
            {
                if (lep_p4()[i].Pt() > 20) { i3l.push_back(i); is3l = true; }
                if (lep_p4()[i].Pt() > 30) { iSS.push_back(i); isSS = true; }
            }
            //loose ID
            if (lep_pass_VVV_cutbased_fo()[i] && lep_isTriggerSafe_v1()[i] && lep_lostHits()[i] == 0 && lep_tightCharge()[i] == 2)
            {
                if (!is3l && lep_p4()[i].Pt() > 20) { ia3l.push_back(i); isa3l = true; }
                if (!isSS && lep_p4()[i].Pt() > 30) { iaSS.push_back(i); isaSS = true; }
            }
            //vetoID
            if (lep_pass_VVV_cutbased_veto()[i])
            {
                if (!isSS &&           lep_p4()[i].Pt() > 10) { vSS  .push_back(i); }
                if (!is3l &&           lep_p4()[i].Pt() > 10) { v3l  .push_back(i); }
                if (!isSS && !isaSS && lep_p4()[i].Pt() > 10) { vaSS .push_back(i); }
                if (!is3l && !isa3l && lep_p4()[i].Pt() > 10) { va3l .push_back(i); }
            }
        }
        else if (abs(lep_pdgId()[i]) == 13)
        {
            //tight ID
            if (lep_pass_VVV_cutbased_veto()[i] && lep_pterr()[i] / lep_trk_pt()[i] < 0.2 && lep_pass_POG_medium_noiso()[i])
            {
                if (lep_p4()[i].Pt() > 20) { i3l.push_back(i); is3l = true; }
                if (lep_p4()[i].Pt() > 20) { iSS.push_back(i); isSS = true; }
            }
            //loose ID
            if (lep_pass_VVV_cutbased_veto()[i] && lep_pterr()[i] / lep_trk_pt()[i] < 0.2 && lep_pass_POG_medium_noiso()[i])
            {
                if (!is3l && lep_p4()[i].Pt() > 20) { ia3l.push_back(i); isa3l = true; }
                if (!isSS && lep_p4()[i].Pt() > 20) { iaSS.push_back(i); isaSS = true; }
            }
            //vetoID
            if (lep_pass_VVV_cutbased_veto()[i])
            {
                if (!isSS &&           lep_p4()[i].Pt() > 10) { vSS  .push_back(i); }
                if (!is3l &&           lep_p4()[i].Pt() > 10) { v3l  .push_back(i); }
                if (!isSS && !isaSS && lep_p4()[i].Pt() > 10) { vaSS .push_back(i); }
                if (!is3l && !isa3l && lep_p4()[i].Pt() > 10) { va3l .push_back(i); }
            }
        }
    }
    return true;
}

//eof
