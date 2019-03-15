#include "HWWlvjjTruthModule.h"

//==============================================================================================================
//
// HWWlvjj Truth Module
//
//==============================================================================================================

void hwwModule::HWWlvjjTruthModule::AddOutput()
{

    tx->createBranch<LV>("gen_recoil_p4"); // This is the p4 of the associated W/Z
    tx->createBranch<int>("gen_recoil_id"); // This is the id of the associated W/Z
    tx->createBranch<LV>("gen_higgs_p4");
    tx->createBranch<LV>("gen_whad_p4");
    tx->createBranch<LV>("gen_wlep_p4");
    tx->createBranch<LV>("gen_q0_p4");
    tx->createBranch<LV>("gen_q1_p4");
    tx->createBranch<LV>("gen_lep_p4");
    tx->createBranch<LV>("gen_neu_p4");
    tx->createBranch<int>("gen_channel");
    tx->createBranch<LV>("gen_wlep_rest_p4");
    tx->createBranch<LV>("gen_whad_rest_p4");
    tx->createBranch<LV>("gen_Vq0_p4");
    tx->createBranch<LV>("gen_Vq1_p4");
    tx->createBranch<int>("gen_Vq0_id");
    tx->createBranch<int>("gen_Vq1_id");
    tx->createBranch<int>("gen_q0_id");
    tx->createBranch<int>("gen_q1_id");
    tx->createBranch<int>("gen_lep_id");
    tx->createBranch<int>("gen_neu_id");

}

void hwwModule::HWWlvjjTruthModule::FillOutput()
{

    // Find the ISR particle if it exists and set the ISR variables
    bool recoil_set = false;
    int recoil_idx = -1;
    for (unsigned int i = 0; i < cms3.genps_p4().size(); ++i)
    {

        // If the recoil is based on a vector boson
        if ((abs(cms3.genps_id()[i]) == 24 or abs(cms3.genps_id()[i]) == 23) and cms3.genps_id_simplemother()[i] != 25 and cms3.genps_status()[i] == 22)
        {
            tx->setBranch<LV>("gen_recoil_p4", cms3.genps_p4()[i]);
            tx->setBranch<int>("gen_recoil_id", cms3.genps_id()[i]);
            recoil_set = true;
            recoil_idx = i;
            break;
        }

        // If the recoil is based on jet
        if (cms3.genps_id_simplemother()[i] == 21 and cms3.genps_id_simplegrandma()[i] == 2212 and cms3.genps_status()[i] == 23)
        {
            tx->setBranch<LV>("gen_recoil_p4", cms3.genps_p4()[i]);
            tx->setBranch<int>("gen_recoil_id", cms3.genps_id()[i]);
            recoil_set = true;
            recoil_idx = i;
            break;
        }
    }

    if (recoil_idx >= 0 and (abs(tx->getBranch<int>("gen_recoil_id")) == 24 or abs(tx->getBranch<int>("gen_recoil_id")) == 23))
    {

        int gen_recoil_id = abs(tx->getBranch<int>("gen_recoil_id"));

        int ichild = -1;
        int jchild = -1;
        if (gen_recoil_id == 23) babymaker->coreGenPart.matchDecay(recoil_idx, ichild, jchild, gen_recoil_id, babymaker->coreGenPart.isPairHadronicZDecay);
        if (gen_recoil_id == 24) babymaker->coreGenPart.matchDecay(recoil_idx, ichild, jchild, gen_recoil_id, babymaker->coreGenPart.isPairHadronicWDecay);

        if (ichild >= 0)
        {
            LV VqA_p4 = cms3.genps_p4()[ichild];
            LV VqB_p4 = cms3.genps_p4()[jchild];
            int VqA_id = cms3.genps_id()[ichild];
            int VqB_id = cms3.genps_id()[jchild];

            LV Vq0_p4 = VqA_p4.pt() > VqB_p4.pt() ? VqA_p4 : VqB_p4;
            LV Vq1_p4 = VqA_p4.pt() > VqB_p4.pt() ? VqB_p4 : VqA_p4;
            int Vq0_id = VqA_p4.pt() > VqB_p4.pt() ? VqA_id : VqB_id;
            int Vq1_id = VqA_p4.pt() > VqB_p4.pt() ? VqB_id : VqA_id;

            tx->setBranch<LV>("gen_Vq0_p4", Vq0_p4);
            tx->setBranch<LV>("gen_Vq1_p4", Vq1_p4);
            tx->setBranch<int>("gen_Vq0_id", Vq0_id);
            tx->setBranch<int>("gen_Vq1_id", Vq1_id);

        }

    }

    // From CoreUtil the HWW decay tree is identified
    std::vector<CoreUtil::genpart::Higgs> higgses = babymaker->coreGenPart.reconstructHWW();

    // But still perform a sanity check that the recovered HWW decay tree makes sense
    // Sanity check
    if (higgses.size() != 1)
    {
        std::cout <<  " higgses.size(): " << higgses.size() <<  std::endl;
        babymaker->coreGenPart.printAllParticles();
        exit(255);
    }

    if (higgses[0].HiggsDaughters.size() != 2)
    {
        std::cout <<  " higgses[0].HiggsDaughters.size(): " << higgses[0].HiggsDaughters.size() <<  std::endl;
        babymaker->coreGenPart.printAllParticles();
        exit(255);
    }

    if (higgses[0].HiggsGrandDaughters.size() != 4)
    {
        std::cout <<  " higgses[0].HiggsGrandDaughters.size(): " << higgses[0].HiggsGrandDaughters.size() <<  std::endl;
        babymaker->coreGenPart.printAllParticles();
        exit(255);
    }

    // Now check whether it is H->WW->lvjj decay channels

    // If not WW then return
    if (abs(higgses[0].HiggsDaughters[0].id) != 24 or abs(higgses[0].HiggsDaughters[0].id) != 24)
        return;

    // If WW->4q or WW->lvlv then return
    if (
        (abs(higgses[0].HiggsGrandDaughters[0].id) >= 11 and abs(higgses[0].HiggsGrandDaughters[0].id) <= 16 and abs(higgses[0].HiggsGrandDaughters[2].id) >= 11 and abs(higgses[0].HiggsGrandDaughters[2].id) <= 16)
        or
        (abs(higgses[0].HiggsGrandDaughters[0].id) >=  1 and abs(higgses[0].HiggsGrandDaughters[0].id) <=  6 and abs(higgses[0].HiggsGrandDaughters[2].id) >=  1 and abs(higgses[0].HiggsGrandDaughters[2].id) <=  6)
       )
        return;

    bool is_first_set_whad = abs(higgses[0].HiggsGrandDaughters[0].id) >= 1 and abs(higgses[0].HiggsGrandDaughters[0].id) <= 6;
    int whad_idx = is_first_set_whad ? 0 : 1;
    int wlep_idx = is_first_set_whad ? 1 : 0;
    int qA_idx = is_first_set_whad ? 0 : 2;
    int qB_idx = is_first_set_whad ? 1 : 3;
    int q0_idx = higgses[0].HiggsGrandDaughters[qA_idx].p4.pt() > higgses[0].HiggsGrandDaughters[qB_idx].p4.pt() ? qA_idx : qB_idx;
    int q1_idx = higgses[0].HiggsGrandDaughters[qA_idx].p4.pt() > higgses[0].HiggsGrandDaughters[qB_idx].p4.pt() ? qB_idx : qA_idx;
    bool is_first_lepton_charged = is_first_set_whad ? abs(higgses[0].HiggsGrandDaughters[2].id) % 2 == 1 : abs(higgses[0].HiggsGrandDaughters[0].id) % 2 == 1;
    int lep_idx = is_first_set_whad ? (is_first_lepton_charged ? 2 : 3) : (is_first_lepton_charged ? 0 : 1);
    int neu_idx = is_first_set_whad ? (is_first_lepton_charged ? 3 : 2) : (is_first_lepton_charged ? 1 : 0);

    LV whad_p4 = higgses[0].HiggsDaughters[whad_idx].p4;
    LV wlep_p4 = higgses[0].HiggsDaughters[wlep_idx].p4;
    LV q0_p4   = higgses[0].HiggsGrandDaughters[q0_idx].p4;
    LV q1_p4   = higgses[0].HiggsGrandDaughters[q1_idx].p4;
    LV lep_p4  = higgses[0].HiggsGrandDaughters[lep_idx].p4;
    LV neu_p4  = higgses[0].HiggsGrandDaughters[neu_idx].p4;

    tx->setBranch<LV>("gen_higgs_p4", higgses[0].p4);
    tx->setBranch<LV>("gen_whad_p4", higgses[0].HiggsDaughters[whad_idx].p4);
    tx->setBranch<LV>("gen_wlep_p4", higgses[0].HiggsDaughters[wlep_idx].p4);
    tx->setBranch<LV>("gen_q0_p4", higgses[0].HiggsGrandDaughters[q0_idx].p4);
    tx->setBranch<LV>("gen_q1_p4", higgses[0].HiggsGrandDaughters[q1_idx].p4);
    tx->setBranch<LV>("gen_lep_p4", higgses[0].HiggsGrandDaughters[lep_idx].p4);
    tx->setBranch<LV>("gen_neu_p4", higgses[0].HiggsGrandDaughters[neu_idx].p4);
//    tx->setBranch<int>("gen_channel");
//    tx->setBranch<LV>("gen_wlep_rest_p4");
//    tx->setBranch<LV>("gen_whad_rest_p4");
//    tx->setBranch<LV>("gen_Vq0_p4");
//    tx->setBranch<LV>("gen_Vq1_p4");
    tx->setBranch<int>("gen_q0_id", higgses[0].HiggsGrandDaughters[q0_idx].id);
    tx->setBranch<int>("gen_q1_id", higgses[0].HiggsGrandDaughters[q1_idx].id);
    tx->setBranch<int>("gen_lep_id", higgses[0].HiggsGrandDaughters[lep_idx].id);
    tx->setBranch<int>("gen_neu_id", higgses[0].HiggsGrandDaughters[neu_idx].id);

}


