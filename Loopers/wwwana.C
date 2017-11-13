//  .
// ..: P.Chang philip@physics.ucsd.edu

#include "rooutil/cxxopts.h"
#include "rooutil/looper.h"
#include "rooutil/fileutil.h"
#include "rooutil/printutil.h"
#include "rooutil/dorky.h"
#include "rooutil/goodrun.h"

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
    typedef unsigned int Idx;
    typedef std::vector<Idx> IdxList;

    // Data samples related variables
    TString babydir;
    TString dataset_to_run_over;
    TChain* chain;
    int n_evt_to_proces;
    std::map<TString, std::vector<TString>> datasetMap;

    // Analysis related variables
    IdxList list_tight_ss_lep_idx;
    IdxList list_tight_3l_lep_idx;
    IdxList list_loose_ss_lep_idx;
    IdxList list_loose_3l_lep_idx;
    IdxList list_veto_ss_lep_idx;
    IdxList list_veto_3l_lep_idx;

    // Functions
    WWWAnalysis();
    void run();
    void setDatasetMap();
    void setChain();
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
            ("d,dataset", "Dataset to run over (e.g. WWW, Other, VVV, tt1l, tt2l, singleTop, ttV, Wjets, Zjets, WW, WZ, ZZ, WG, ZG, WGstar, Data)", cxxopts::value<std::string>()->default_value("WWW"), "DATASET")
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

        wwwanalysis.dataset_to_run_over = options["dataset"].as<std::string>();

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
    // From the options set create the TChain and load all the relevant root files.
    setChain();
    // Create a Looper instance.
    RooUtil::Looper<CMS3> looper(chain, &cms3, -1);
    // Event lists to check
    vector<myevt> e;
    addeventtocheck(e,1, 2842, 1443084);
    addeventtocheck(e,1,17341, 8807395);
    addeventtocheck(e,1,15849, 8049420);
    addeventtocheck(e,1,21682,11012507);
    bool blindSR = true;
    bool btagreweighting = true;
    bool applylepSF      = true;
    bool applytrigSF     = true;
    bool applyPUrewgt    = true;
    bool getJECunc       = true;
    bool storeeventnumbers = true;
    std::ostringstream*  SREE    ;
    std::ostringstream*  SREM    ;
    std::ostringstream*  SRMM    ;
    std::ostringstream*  SR0SFOS ;
    std::ostringstream*  SR1SFOS ;
    std::ostringstream*  SR2SFOS ;
    std::ostringstream*  AREE    ;
    std::ostringstream*  AREM    ;
    std::ostringstream*  ARMM    ;
    std::ostringstream*  AR0SFOS ;
    std::ostringstream*  AR1SFOS ;
    std::ostringstream*  AR2SFOS ;
    std::ostringstream*  CREE    ;
    std::ostringstream*  CREM    ;
    std::ostringstream*  CRMM    ;
    std::ostringstream*  CR0SFOS ;
    std::ostringstream*  CR1SFOS ;
    std::ostringstream*  CR2SFOS ;
    if(storeeventnumbers){
        SREE    = new std::ostringstream();
        SREM    = new std::ostringstream();
        SRMM    = new std::ostringstream();
        SR0SFOS = new std::ostringstream();
        SR1SFOS = new std::ostringstream();
        SR2SFOS = new std::ostringstream();
        AREE    = new std::ostringstream();
        AREM    = new std::ostringstream();
        ARMM    = new std::ostringstream();
        AR0SFOS = new std::ostringstream();
        AR1SFOS = new std::ostringstream();
        AR2SFOS = new std::ostringstream();
        CREE    = new std::ostringstream();
        CREM    = new std::ostringstream();
        CRMM    = new std::ostringstream();
        CR0SFOS = new std::ostringstream();
        CR1SFOS = new std::ostringstream();
        CR2SFOS = new std::ostringstream();
    }
    // Example Histograms
    TDirectory *rootdir = gDirectory->GetDirectory("Rint:");

    vector<string> histonames; histonames.clear();
    vector<int> hbins; hbins.clear();
    vector<float> hlow; hlow.clear();
    vector<float> hup; hup.clear();

    histonames.push_back("RawSignalRegion");                     hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
    histonames.push_back("RawApplicationRegion");                hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
    histonames.push_back("RawWZControlRegion");                  hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
    histonames.push_back("RawSignalRegionPresel");               hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
    histonames.push_back("RawApplicationRegionPresel");          hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
    histonames.push_back("RawWZControlRegionPresel");            hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);

    histonames.push_back("SignalRegionPrecleaning");             hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
    histonames.push_back("SignalRegion");                        hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
    histonames.push_back("ApplicationRegion");                   hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
    histonames.push_back("WZControlRegion");                     hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
    histonames.push_back("ApplicationRegionPrecleaning");        hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
    histonames.push_back("WZControlRegionPrecleaning");          hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
    histonames.push_back("SignalRegionPresel");                  hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
    histonames.push_back("SignalRegionPreselPrecleaning");       hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
    histonames.push_back("ApplicationRegionPresel");             hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
    histonames.push_back("WZControlRegionPresel");               hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
    histonames.push_back("ApplicationRegionPreselPrecleaning");  hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
    histonames.push_back("WZControlRegionPreselPrecleaning");    hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);

    histonames.push_back("SignalRegion_JECup");                  hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
    histonames.push_back("SignalRegion_JECdn");                  hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
    histonames.push_back("SignalRegion_lepSFup");                hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
    histonames.push_back("SignalRegion_lepSFdn");                hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
    histonames.push_back("SignalRegion_bHFSFup");                hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
    histonames.push_back("SignalRegion_bHFSFdn");                hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
    histonames.push_back("SignalRegion_bLFSFup");                hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
    histonames.push_back("SignalRegion_bLFSFdn");                hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
    histonames.push_back("SignalRegion_PUup");                   hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);
    histonames.push_back("SignalRegion_PUdn");                   hbins.push_back(6); hlow.push_back(    0); hup.push_back(6);

    map<string, TH1D*> histos =  bookhistograms(dataset_to_run_over.Data(), histonames,hbins, hlow, hup, rootdir);
    cout << "Loaded histograms" << endl;

    // Loop over events.
    while (looper.nextEvent())
    {
        // Do the analysis here.
        using namespace tas;
        double weight = evt_scale1fb() * 35.9;

        if (firstgoodvertex() != 0)   { continue; }
        if (nVert() < 0)              { continue; }
        //if(nlep()<2)               continue;

        //weight = 1;
        if (string(looper.getCurrentFile()->GetTitle()).find("wjets_incl_mgmlm_") != string::npos)
        {
            if (gen_ht() > 100) { continue; }
        }
        if (string(looper.getCurrentFile()->GetTitle()).find("dy_m50_mgmlm_ext1_") != string::npos)
        {
            if (gen_ht() > 100) { continue; }
        }
        if (string(looper.getCurrentFile()->GetTitle()).find("www_2l_mia") != string::npos)      { weight *= 0.066805 * 91900. / (91900. + 164800.); } //(208fb/1pb)*BR(WWW—> >=2l)*combineweight
        if (string(looper.getCurrentFile()->GetTitle()).find("www_2l_ext1_mia") != string::npos) { weight *= 0.066805 * 164800. / (91900. + 164800.); } //(208fb/1pb)*BR(WWW—> >=2l)*combineweight
        if (weight > 100) { cout << weight << " " << looper.getCurrentFile()->GetTitle() << endl; }
        if (isData()) { weight = 1.; }
        double rawweight = weight;
        if (!isData() && btagreweighting) { weight *= weight_btagsf(); }
        float PUweight(1.), PUweightup(1.), PUweightdn(1.);
        if (applyPUrewgt && !isData())
        {
            PUweight = getPUWeightAndError(PUweightdn, PUweightup);
            weight *= PUweight;
        }

        bool checkevent = false;
        for (unsigned int i = 0; i < e.size(); ++i)
        {
            if (e[i].run != tas::run()) { continue; }
            if (e[i].ls != tas::lumi()) { continue; }
            if (e[i].evt != tas::evt()) { continue; }
            checkevent = true;
            cout << "Check event " << tas::run() << ":" << tas::lumi() << ":" << tas::evt() << endl;
            break;
        }
        LorentzVector MET;
        MET.SetPxPyPzE(met_pt()*TMath::Cos(met_phi()), met_pt()*TMath::Sin(met_phi()), 0, met_pt());
        LorentzVector MET_up;
        MET_up.SetPxPyPzE(met_T1CHS_miniAOD_CORE_up_pt()*TMath::Cos(met_T1CHS_miniAOD_CORE_up_phi()), met_T1CHS_miniAOD_CORE_up_pt()*TMath::Sin(met_T1CHS_miniAOD_CORE_up_phi()), 0, met_T1CHS_miniAOD_CORE_up_pt());
        LorentzVector MET_dn;
        MET_dn.SetPxPyPzE(met_T1CHS_miniAOD_CORE_dn_pt()*TMath::Cos(met_T1CHS_miniAOD_CORE_dn_phi()), met_T1CHS_miniAOD_CORE_dn_pt()*TMath::Sin(met_T1CHS_miniAOD_CORE_dn_phi()), 0, met_T1CHS_miniAOD_CORE_dn_pt());

        int nj(0), nb(0), nj30(0);
        getalljetnumbers(nj, nj30, nb);
        float Mjj = -1;
        float MjjL = -1;
        float Detajj = -1;
        getMjjAndDeta(Mjj, MjjL, Detajj);
        if (checkevent) { cout << "nj30 " << nj30 << " nj " << nj << " nb " << nb << " Mjj " << Mjj << " MjjL " << MjjL << " Detajj " << Detajj << endl; }
        if (checkevent)
        {
            for (unsigned int i = 0; i < jets_p4().size(); ++i)
            {
                cout << "jet pT " << jets_p4()[i].Pt() << " eta " << jets_p4()[i].Eta() << " CSV " << jets_csv()[i];// << endl;
                for (unsigned int j = i + 1; j < jets_p4().size(); ++j) { cout << " M" << i << j << " " << (jets_p4()[i] + jets_p4()[j]).M() << " (dR " << dR(jets_p4()[i], jets_p4()[j]) << ")"; }
                cout << endl;
            }
        }

        int nj_up(0), nb_up(0), nj30_up(0);
        if (getJECunc) { getalljetnumbers(nj_up, nj30_up, nb_up, 1); }
        float Mjj_up = -1;
        float MjjL_up = -1;
        float Detajj_up = -1;
        if (getJECunc) { getMjjAndDeta(Mjj_up, MjjL_up, Detajj_up, 1); }

        int nj_dn(0), nb_dn(0), nj30_dn(0);
        if (getJECunc) { getalljetnumbers(nj_dn, nj30_dn, nb_dn, -1); }
        float Mjj_dn = -1;
        float MjjL_dn = -1;
        float Detajj_dn = -1;
        if (getJECunc) { getMjjAndDeta(Mjj_dn, MjjL_dn, Detajj_dn, -1); }

        vector<int> vSS,   v3l,   iSS,   i3l; //lepton indices for both the SS and 3l signal regions
        vector<int> vaSS,  va3l,  iaSS,  ia3l;//loose, but not tight leptons.
        getleptonindices(iSS, i3l, iaSS, ia3l, vSS, v3l, vaSS, va3l);
        float lepSF(1.), lepSFerr(0.);//i3l and iSS have same ID
        if (applylepSF && !isData())
        {
            lepSF = getlepSFWeightandError(lepSFerr, i3l, ia3l);
            weight *= lepSF;
        }
        float trigSF(1.), trigSFerr(1.);
        if (applytrigSF && !isData())
        {
            trigSF    = getTriggerWeightandError(trigSFerr, i3l, ia3l);
            weight *= trigSF;
        }
        float weight_lepSFup = weight;
        float weight_lepSFdn = weight;
        float weight_PUup    = weight;
        float weight_PUdn    = weight;
        float weight_bHFSFup = weight;
        float weight_bHFSFdn = weight;
        float weight_bLFSFup = weight;
        float weight_bLFSFdn = weight;
        if (!isData() && btagreweighting && weight_btagsf() != 0)
        {
            weight_bHFSFup *= weight_btagsf_heavy_UP() / weight_btagsf();
            weight_bHFSFdn *= weight_btagsf_heavy_DN() / weight_btagsf();
            weight_bLFSFup *= weight_btagsf_light_UP() / weight_btagsf();
            weight_bLFSFdn *= weight_btagsf_light_DN() / weight_btagsf();
        }
        if (applyPUrewgt && !isData() && PUweight != 0)
        {
            weight_PUup *= PUweightup / PUweight;
            weight_PUdn *= PUweightdn / PUweight;
        }
        if (applylepSF && !isData() && lepSF != 0)
        {
            weight_lepSFup *= (lepSF + lepSFerr) / lepSF;
            weight_lepSFdn *= (lepSF - lepSFerr) / lepSF;
        }
        if (checkevent) { cout << "weight " << weight << " btag  " << weight_btagsf() << " PU " << PUweight << " trig " << trigSF << " lep " << lepSF << endl; }

        int nvetoSS = vSS.size();
        int nveto3l = v3l.size();
        int nSS = iSS.size();
        int n3l = i3l.size();
        int nvetoaSS = vaSS.size();
        int nvetoa3l = va3l.size();
        int naSS = iaSS.size();
        int na3l = ia3l.size();
        if (checkevent) { cout << "nSS " << nSS << " n3l " << n3l << " naSS " << naSS << " na3l " << na3l << " nvetoaSS " << nvetoaSS << " nvetoa3l " << nvetoa3l << " ntracks " << nisoTrack_mt2_cleaned_VVV_cutbased_veto() << endl; }
        if (checkevent)
        {
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
        }

        if ((n3l + na3l) < 2) { continue; }
        bool passofflineforTrigger = passofflineTriggers(i3l, ia3l);
        if (!passofflineforTrigger) { continue; }
        if (checkevent) { cout << "pass offline" << endl; }

        if (isData())
        {
            if (!passFilters()) { continue; }
            if (checkevent) { cout << "pass filter" << endl; }
            duplicate_removal::DorkyEventIdentifier id(tas::run(), tas::evt(), tas::lumi());
            if (is_duplicate(id)) { continue; }
            if (checkevent) { cout << "pass duplicate" << endl; }
            if (!goodrun(tas::run(), tas::lumi())) { continue; }
            if (checkevent) { cout << "pass goodrun" << endl; }
            bool passonlineTrigger = passonlineTriggers(i3l, ia3l);//currently applied only to data
            if (!passonlineTrigger) { continue; }
        }
        if (checkevent) { cout << "pass online" << endl; }


        string sample   = dataset_to_run_over.Data();
        string sn       = ((iSS.size() + iaSS.size()) >= 2) ? process(looper.getCurrentFile()->GetTitle(), true, iSS, iaSS) : string("not2l");
        string sn2      = ((i3l.size() + ia3l.size()) >= 3) ? process(looper.getCurrentFile()->GetTitle(), false, i3l, ia3l) : string("not3l");
        bool isphotonSS = (sn == "photonfakes");
        bool isphoton3l = (sn2 == "photonfakes");
        if (splitVH(looper.getCurrentFile()->GetTitle())) { sample = "WHtoWWW"; }


        float MTmax = -1;
        if (iSS.size() == 2) { MTmax = calcMTmax(iSS, MET); }
        else if (iSS.size() == 1 && iaSS.size() >= 1)
        {
            vector<int> temp;
            temp.push_back(iSS[0]);
            temp.push_back(iaSS[0]);
            MTmax = calcMTmax(temp, MET);
        }
        float MTmax3l = calcMTmax(i3l, MET, true);
        if (checkevent) { cout << "MET " << MET.Pt() << " MTmax " << MTmax << " MTmax3l " << MTmax3l << endl; }
        float MTmax_up(-1), MTmax_dn(-1), MTmax3l_up(-1), MTmax3l_dn(-1);
        if (getJECunc)
        {
            MTmax_up   = calcMTmax(iSS, MET_up);
            //MTmax3l_up = calcMTmax(i3l,MET_up,true);
            MTmax_dn   = calcMTmax(iSS, MET_dn);
            //MTmax3l_dn = calcMTmax(i3l,MET_dn,true);
        }

        int SRSS[8];
        bool selects3l[8];
        int SR3l[8];
        for (int i = 0; i < 8; ++i) { SRSS[i] = -1; SR3l[i] = -1; selects3l[i] = false; }

        //SS
        //0: SR
        SRSS[0] = isSRSS(iSS,      vSS, false, MTmax,  nj30, nb, Mjj, MjjL, Detajj); //enter variables for quicker calculation
        //1: SR preselect
        SRSS[1] = isSRSS(iSS,      vSS, true, MTmax,  nj30, nb, Mjj, MjjL, Detajj); //enter variables for quicker calculation
        //2: AR
        SRSS[2] = isARSS(iSS, iaSS, vaSS, false, MTmax,  nj30, nb, Mjj, MjjL, Detajj); //enter variables for quicker calculation
        //3: AR preselect
        SRSS[3] = isARSS(iSS, iaSS, vaSS, true, MTmax,  nj30, nb, Mjj, MjjL, Detajj); //enter variables for quicker calculation
        //4: CR
        SRSS[4] = isCRSS(iSS, i3l,  v3l, false, MTmax3l, nj30, nb, Mjj, MjjL, Detajj); //enter variables for quicker calculation
        //5: CR preselect
        SRSS[5] = isCRSS(iSS, i3l,  v3l, true, MTmax3l, nj30, nb, Mjj, MjjL, Detajj); //enter variables for quicker calculation
        //6: SR JEC up
        if (getJECunc) { SRSS[6] = isSRSS(iSS, vSS, false, MTmax_up, nj30_up, nb_up, Mjj_up, MjjL_up, Detajj_up, MET_up, 1); }
        //7: SR JEC dn
        if (getJECunc) { SRSS[7] = isSRSS(iSS, vSS, false, MTmax_dn, nj30_dn, nb_dn, Mjj_dn, MjjL_dn, Detajj_dn, MET_dn, -1); }
        selects3l[4] = true;
        selects3l[5] = true;
        //3l
        //0: SR, 4: CR
        checkbothSRCR3l(SR3l[0], SR3l[4], i3l, false, nj, nb);
        //1: SR preselect, 5: CR preselect
        checkbothSRCR3l(SR3l[1], SR3l[5], i3l, true, nj, nb);
        //2: AR
        SR3l[2] = isAR3l(i3l, ia3l, false, nj, nb);
        //3: AR preselect
        SR3l[3] = isAR3l(i3l, ia3l, true, nj, nb);
        //6: SR JEC up
        if (getJECunc) { SR3l[6] = isSR3l(i3l, false, nj_up, nb_up, MET_up, 1); }
        //7: SR JEC dn
        if (getJECunc) { SR3l[7] = isSR3l(i3l, false, nj_dn, nb_dn, MET_dn, -1); }


        if (!isData() || !blindSR) //SR is blinded
        {
            fillSRhisto(histos, "SignalRegionPrecleaning",            sample, sn, sn2, SRSS[0], SR3l[0], weight, weight);
            fillSRhisto(histos, "SignalRegionPreselPrecleaning",      sample, sn, sn2, SRSS[1], SR3l[1], weight, weight);
        }
        fillSRhisto(histos, "ApplicationRegionPrecleaning",       sample, sn, sn2, SRSS[2], SR3l[2], weight, weight);
        fillSRhisto(histos, "ApplicationRegionPreselPrecleaning", sample, sn, sn2, SRSS[3], SR3l[3], weight, weight);
        fillSRhisto(histos, "WZControlRegionPrecleaning",         sample, sn2, sn2, SRSS[4], SR3l[4], weight, weight);
        fillSRhisto(histos, "WZControlRegionPreselPrecleaning",   sample, sn2, sn2, SRSS[5], SR3l[5], weight, weight);


        if (checkevent) { cout << "passed       SRSS " << SRSS[0] << " SR3l " << SR3l[0] << " ARSS " << SRSS[2] << " AR3l " << SR3l[2] << " CRSS " << SRSS[4] << " CR3l " << SR3l[4] << endl; }
        //if(SRSS[2]==0) cout << __LINE__ << endl;
        for (int i = 0; i < 8; ++i)
        {
            if (!selects3l[i])
            {
                if (vetophotonprocess(looper.getCurrentFile()->GetTitle(), isphotonSS))    { SRSS[i] = -1; }
            }
            else if (vetophotonprocess(looper.getCurrentFile()->GetTitle(), isphoton3l)) { SRSS[i] = -1; }
            if (vetophotonprocess(looper.getCurrentFile()->GetTitle(), isphoton3l))     { SR3l[i] = -1; }
        }
        if (checkevent) { cout << "photonpassed SRSS " << SRSS[0] << " SR3l " << SR3l[0] << " ARSS " << SRSS[2] << " AR3l " << SR3l[2] << " CRSS " << SRSS[4] << " CR3l " << SR3l[4] << endl; }


        if (!isData() || !blindSR) //SR is blinded
        {
            fillSRhisto(histos, "SignalRegion",               sample, sn, sn2, SRSS[0], SR3l[0], weight, weight);
            fillSRhisto(histos, "SignalRegionPresel",         sample, sn, sn2, SRSS[1], SR3l[1], weight, weight);
            fillSRhisto(histos, "SignalRegion_JECup",         sample, sn, sn2, SRSS[6], SR3l[6], weight,         weight);
            fillSRhisto(histos, "SignalRegion_JECdn",         sample, sn, sn2, SRSS[7], SR3l[7], weight,         weight);
            fillSRhisto(histos, "SignalRegion_lepSFup",       sample, sn, sn2, SRSS[0], SR3l[0], weight_lepSFup, weight_lepSFup);
            fillSRhisto(histos, "SignalRegion_lepSFdn",       sample, sn, sn2, SRSS[0], SR3l[0], weight_lepSFdn, weight_lepSFdn);
            fillSRhisto(histos, "SignalRegion_bHFSFup",       sample, sn, sn2, SRSS[0], SR3l[0], weight_bHFSFup, weight_bHFSFup);
            fillSRhisto(histos, "SignalRegion_bHFSFdn",       sample, sn, sn2, SRSS[0], SR3l[0], weight_bHFSFdn, weight_bHFSFdn);
            fillSRhisto(histos, "SignalRegion_bLFSFup",       sample, sn, sn2, SRSS[0], SR3l[0], weight_bLFSFup, weight_bLFSFup);
            fillSRhisto(histos, "SignalRegion_bLFSFdn",       sample, sn, sn2, SRSS[0], SR3l[0], weight_bLFSFdn, weight_bLFSFdn);
            fillSRhisto(histos, "SignalRegion_PUup",          sample, sn, sn2, SRSS[0], SR3l[0], weight_PUup,    weight_PUup);
            fillSRhisto(histos, "SignalRegion_PUdn",          sample, sn, sn2, SRSS[0], SR3l[0], weight_PUdn,    weight_PUdn);
        }
        fillSRhisto(histos, "ApplicationRegion",          sample, sn, sn2, SRSS[2], SR3l[2], weight, weight);
        fillSRhisto(histos, "ApplicationRegionPresel",    sample, sn, sn2, SRSS[3], SR3l[3], weight, weight);
        fillSRhisto(histos, "WZControlRegion",            sample, sn2, sn2, SRSS[4], SR3l[4], weight, weight);
        fillSRhisto(histos, "WZControlRegionPresel",      sample, sn2, sn2, SRSS[5], SR3l[5], weight, weight);

        if (!isData() || !blindSR) //SR is blinded
        {
            fillSRhisto(histos, "RawSignalRegion",            sample, sn, sn2, SRSS[0], SR3l[0], 1., 1.);
            fillSRhisto(histos, "RawSignalRegionPresel",      sample, sn, sn2, SRSS[1], SR3l[1], 1., 1.);
        }
        fillSRhisto(histos, "RawApplicationRegion",       sample, sn, sn2, SRSS[2], SR3l[2], 1., 1.);
        fillSRhisto(histos, "RawApplicationRegionPresel", sample, sn, sn2, SRSS[3], SR3l[3], 1., 1.);
        fillSRhisto(histos, "RawWZControlRegion",         sample, sn2, sn2, SRSS[4], SR3l[4], 1., 1.);
        fillSRhisto(histos, "RawWZControlRegionPresel",   sample, sn2, sn2, SRSS[5], SR3l[5], 1., 1.);

        if (storeeventnumbers)
        {
            addeventtolist(SRSS[0], SR3l[0], SREE, SREM, SRMM, SR0SFOS, SR1SFOS, SR2SFOS);
            addeventtolist(SRSS[2], SR3l[2], AREE, AREM, ARMM, AR0SFOS, AR1SFOS, AR2SFOS);
            addeventtolist(SRSS[4], SR3l[4], CREE, CREM, CRMM, CR0SFOS, CR1SFOS, CR2SFOS);
            //addeventtolist(SRSS[1], SR3l[1], SREE, SREM, SRMM, SR0SFOS, SR1SFOS, SR2SFOS);
            //addeventtolist(SRSS[3], SR3l[3], AREE, AREM, ARMM, AR0SFOS, AR1SFOS, AR2SFOS);
            //addeventtolist(SRSS[5], SR3l[5], CREE, CREM, CRMM, CR0SFOS, CR1SFOS, CR2SFOS);
        }
        if (checkevent) { cout << endl; }
      
    }

    SaveHistosToFile(Form("rootfiles/SRLooper_%s.root", dataset_to_run_over.Data()), histos, true, true, true);
    deleteHistograms(histos);

}

//#################################################################################################
void WWWAnalysis::setChain()
{
    if (!chain)
    {
        // Vector to hold the datasets to run over
        std::vector<TString> dataset_paths;

        // From the dataSetMap created add the individual root files for this dataset.
        for (auto& dataset_path : datasetMap.at(dataset_to_run_over))
            dataset_paths.push_back(babydir + dataset_path);

        // Create at TChain from the list of root files.
        chain = RooUtil::FileUtil::createTChain("t", RooUtil::StringUtil::join(dataset_paths, ","));
    }
}

//#################################################################################################
WWWAnalysis::WWWAnalysis()
{
    chain = 0;
    setDatasetMap();
}

//#################################################################################################
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


//eof
