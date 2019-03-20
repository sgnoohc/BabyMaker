#include "LeptonModule.h"

//==============================================================================================================
//
// Lepton Module
//
//==============================================================================================================

//##############################################################################################################
void hwwModule::LeptonModule::AddOutput()
{

    tx->createBranch<LV>("L_p4");
    tx->createBranch<float>("L_pt");
    tx->createBranch<float>("L_eta");
    tx->createBranch<float>("L_phi");
    tx->createBranch<float>("L_mass");
    tx->createBranch<float>("L_energy");

    // And none of the following will be written to the TTree (hence the second argument being set to false)
    // This is so that we save sapce, there will be a separate branch that actually selects the ak8jets of interest
    // and save the necessary information.
    bool writeToTree = true;
    tx->createBranch<int>("L_id", writeToTree);
    tx->createBranch<int>("L_idx", writeToTree);
    tx->createBranch<int>("L_isTightPOG", writeToTree);
    tx->createBranch<float>("L_miniIsoEA", writeToTree);
    tx->createBranch<float>("L_relIso03EA", writeToTree);
    tx->createBranch<float>("L_relIso04DB", writeToTree);
    tx->createBranch<float>("L_relIso0025EA", writeToTree);
    tx->createBranch<float>("L_relIso005EA", writeToTree);
    tx->createBranch<float>("L_relIso01EA", writeToTree);
    tx->createBranch<float>("L_relIso02EA", writeToTree);
    tx->createBranch<float>("L_relIso04EA", writeToTree);
    tx->createBranch<float>("L_relIso08EA", writeToTree);
    tx->createBranch<float>("L_relIso0025EAwLep", writeToTree);
    tx->createBranch<float>("L_relIso005EAwLep", writeToTree);
    tx->createBranch<float>("L_relIso01EAwLep", writeToTree);
    tx->createBranch<float>("L_relIso02EAwLep", writeToTree);
    tx->createBranch<float>("L_relIso04EAwLep", writeToTree);
    tx->createBranch<float>("L_relIso08EAwLep", writeToTree);
    tx->createBranch<float>("L_ip3d", writeToTree);
    tx->createBranch<float>("L_ip3derr", writeToTree);
    tx->createBranch<float>("L_dxy", writeToTree);
    tx->createBranch<float>("L_dz", writeToTree);
    tx->createBranch<int>("L_isFromW", writeToTree);

}

//##############################################################################################################
void hwwModule::LeptonModule::FillOutput()
{

    std::cout.setstate(std::ios_base::failbit); // To suppress warning about CMS4 not having PF candidates

    // I expect either one electron or one muon so it's ok to loop over
    for (auto& idx : babymaker->coreElectron.index)
    {
        tx->setBranch<LV>   ("L_p4"  , cms3.els_p4()[idx]);
        tx->setBranch<float>("L_pt"  , cms3.els_p4()[idx].pt());
        tx->setBranch<float>("L_eta" , cms3.els_p4()[idx].eta());
        tx->setBranch<float>("L_phi" , cms3.els_p4()[idx].phi());
        tx->setBranch<float>("L_mass", cms3.els_p4()[idx].mass());
        tx->setBranch<float>("L_energy", cms3.els_p4()[idx].energy());
        tx->setBranch<int>  ("L_id"  , cms3.els_charge()[idx]*(-11));
        tx->setBranch<int>  ("L_idx" , idx);
        tx->setBranch<int>  ("L_isTightPOG", isTightElectronPOGspring16noIso_v1(idx));
        tx->setBranch<float>("L_miniIsoEA" , elMiniRelIsoCMS3_EA(idx, 2));
        tx->setBranch<float>("L_relIso03EA" , eleRelIso03EA(idx, 2));
        tx->setBranch<float>("L_relIso04DB" , -999);
        tx->setBranch<float>("L_relIso0025EA", elRelIsoCustomCone(idx , 0.025 , false , 0.0 , false , true , -1 , 2 , false));
        tx->setBranch<float>("L_relIso005EA" , elRelIsoCustomCone(idx , 0.05  , false , 0.0 , false , true , -1 , 2 , false));
        tx->setBranch<float>("L_relIso01EA"  , elRelIsoCustomCone(idx , 0.1   , false , 0.0 , false , true , -1 , 2 , false));
        tx->setBranch<float>("L_relIso02EA"  , elRelIsoCustomCone(idx , 0.2   , false , 0.0 , false , true , -1 , 2 , false));
        tx->setBranch<float>("L_relIso04EA"  , elRelIsoCustomCone(idx , 0.4   , false , 0.0 , false , true , -1 , 2 , false));
        tx->setBranch<float>("L_relIso08EA"  , elRelIsoCustomCone(idx , 0.8   , false , 0.0 , false , true , -1 , 2 , false));
        tx->setBranch<float>("L_relIso0025EAwLep", elRelIsoCustomCone(idx , 0.025 , false , 0.0 , false , true , -1 , 2 , true));
        tx->setBranch<float>("L_relIso005EAwLep" , elRelIsoCustomCone(idx , 0.05  , false , 0.0 , false , true , -1 , 2 , true));
        tx->setBranch<float>("L_relIso01EAwLep"  , elRelIsoCustomCone(idx , 0.1   , false , 0.0 , false , true , -1 , 2 , true));
        tx->setBranch<float>("L_relIso02EAwLep"  , elRelIsoCustomCone(idx , 0.2   , false , 0.0 , false , true , -1 , 2 , true));
        tx->setBranch<float>("L_relIso04EAwLep"  , elRelIsoCustomCone(idx , 0.4   , false , 0.0 , false , true , -1 , 2 , true));
        tx->setBranch<float>("L_relIso08EAwLep"  , elRelIsoCustomCone(idx , 0.8   , false , 0.0 , false , true , -1 , 2 , true));
        tx->setBranch<float>("L_ip3d"  , cms3.els_ip3d()[idx]);
        tx->setBranch<float>("L_ip3derr"  , cms3.els_ip3derr()[idx]);
        tx->setBranch<float>("L_dxy"  , cms3.els_dxyPV()[idx]);
        tx->setBranch<float>("L_dz"  , cms3.els_dzPV()[idx]);
        tx->setBranch<int>("L_isFromW"  , isFromW(11, idx));
    }

    // I expect either one electron or one muon so it's ok to loop over
    for (auto& idx : babymaker->coreMuon.index)
    {
        tx->setBranch<LV>   ("L_p4"  , cms3.mus_p4()[idx]);
        tx->setBranch<float>("L_pt"  , cms3.mus_p4()[idx].pt());
        tx->setBranch<float>("L_eta" , cms3.mus_p4()[idx].eta());
        tx->setBranch<float>("L_phi" , cms3.mus_p4()[idx].phi());
        tx->setBranch<float>("L_mass", cms3.mus_p4()[idx].mass());
        tx->setBranch<float>("L_energy", cms3.mus_p4()[idx].energy());
        tx->setBranch<int>  ("L_id"  , cms3.mus_charge()[idx]*(-13));
        tx->setBranch<int>  ("L_idx" , idx);
        tx->setBranch<int>  ("L_isTightPOG", isMediumMuonPOG(idx));
        tx->setBranch<float>("L_miniIsoEA" , muMiniRelIsoCMS3_EA(idx, 2));
        tx->setBranch<float>("L_relIso03EA" , muRelIso03EA(idx, 2));
        tx->setBranch<float>("L_relIso04DB" , muRelIso04DB(idx));
        tx->setBranch<float>("L_relIso0025EA" , muRelIsoCustomCone(idx , 0.025, false , 0.5 , false , true , -1 , 2 , false));
        tx->setBranch<float>("L_relIso005EA"  , muRelIsoCustomCone(idx , 0.05 , false , 0.5 , false , true , -1 , 2 , false));
        tx->setBranch<float>("L_relIso01EA"   , muRelIsoCustomCone(idx , 0.1  , false , 0.5 , false , true , -1 , 2 , false));
        tx->setBranch<float>("L_relIso02EA"   , muRelIsoCustomCone(idx , 0.2  , false , 0.5 , false , true , -1 , 2 , false));
        tx->setBranch<float>("L_relIso04EA"   , muRelIsoCustomCone(idx , 0.4  , false , 0.5 , false , true , -1 , 2 , false));
        tx->setBranch<float>("L_relIso08EA"   , muRelIsoCustomCone(idx , 0.8  , false , 0.5 , false , true , -1 , 2 , false));
        tx->setBranch<float>("L_relIso0025EAwLep" , muRelIsoCustomCone(idx , 0.025, false , 0.5 , false , true , -1 , 2 , true));
        tx->setBranch<float>("L_relIso005EAwLep"  , muRelIsoCustomCone(idx , 0.05 , false , 0.5 , false , true , -1 , 2 , true));
        tx->setBranch<float>("L_relIso01EAwLep"   , muRelIsoCustomCone(idx , 0.1  , false , 0.5 , false , true , -1 , 2 , true));
        tx->setBranch<float>("L_relIso02EAwLep"   , muRelIsoCustomCone(idx , 0.2  , false , 0.5 , false , true , -1 , 2 , true));
        tx->setBranch<float>("L_relIso04EAwLep"   , muRelIsoCustomCone(idx , 0.4  , false , 0.5 , false , true , -1 , 2 , true));
        tx->setBranch<float>("L_relIso08EAwLep"   , muRelIsoCustomCone(idx , 0.8  , false , 0.5 , false , true , -1 , 2 , true));
        tx->setBranch<float>("L_ip3d"  , cms3.mus_ip3d()[idx]);
        tx->setBranch<float>("L_ip3derr"  , cms3.mus_ip3derr()[idx]);
        tx->setBranch<float>("L_dxy"  , cms3.mus_dxyPV()[idx]);
        tx->setBranch<float>("L_dz"  , cms3.mus_dzPV()[idx]);
        tx->setBranch<int>("L_isFromW"  , isFromW(13, idx));
    }

    std::cout.clear();

}
