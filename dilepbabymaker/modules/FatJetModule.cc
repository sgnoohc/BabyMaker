#include "FatJetModule.h"

//==============================================================================================================
//
// Fat Jet Module
//
//==============================================================================================================

void hwwModule::FatJetModule::AddOutput()
{

    tx->createBranch<LV>("J_p4");
    tx->createBranch<float>("J_pt");
    tx->createBranch<float>("J_eta");
    tx->createBranch<float>("J_phi");
    tx->createBranch<float>("J_mass");
    tx->createBranch<float>("J_energy");
    tx->createBranch<float>("J_tau31");
    tx->createBranch<float>("J_tau32");
    tx->createBranch<float>("J_tau21");
    tx->createBranch<float>("J_tau1");
    tx->createBranch<float>("J_tau2");
    tx->createBranch<float>("J_tau3");

    tx->createBranch<LV>("J_SD_p4");
    tx->createBranch<float>("J_SD_pt");
    tx->createBranch<float>("J_SD_eta");
    tx->createBranch<float>("J_SD_phi");
    tx->createBranch<float>("J_SD_mass");
    tx->createBranch<float>("J_SD_energy");
    tx->createBranch<float>("J_SD_tau31");
    tx->createBranch<float>("J_SD_tau32");
    tx->createBranch<float>("J_SD_tau21");
    tx->createBranch<float>("J_SD_tau1");
    tx->createBranch<float>("J_SD_tau2");
    tx->createBranch<float>("J_SD_tau3");

    tx->createBranch<LV>("q0_p4");
    tx->createBranch<float>("q0_pt");
    tx->createBranch<float>("q0_eta");
    tx->createBranch<float>("q0_phi");
    tx->createBranch<float>("q0_mass");
    tx->createBranch<float>("q0_energy");

    tx->createBranch<LV>("q1_p4");
    tx->createBranch<float>("q1_pt");
    tx->createBranch<float>("q1_eta");
    tx->createBranch<float>("q1_phi");
    tx->createBranch<float>("q1_mass");
    tx->createBranch<float>("q1_energy");

}

void hwwModule::FatJetModule::FillOutput()
{

    tx->setBranch<LV>("J_p4", babymaker->recl.J_p4);
    tx->setBranch<float>("J_pt", babymaker->recl.J_p4.pt());
    tx->setBranch<float>("J_eta", babymaker->recl.J_p4.eta());
    tx->setBranch<float>("J_phi", babymaker->recl.J_p4.phi());
    tx->setBranch<float>("J_mass", babymaker->recl.J_p4.mass());
    tx->setBranch<float>("J_energy", babymaker->recl.J_p4.energy());
    tx->setBranch<float>("J_tau31", babymaker->recl.tau31);
    tx->setBranch<float>("J_tau32", babymaker->recl.tau32);
    tx->setBranch<float>("J_tau21", babymaker->recl.tau21);
    tx->setBranch<float>("J_tau1", babymaker->recl.tau1);
    tx->setBranch<float>("J_tau2", babymaker->recl.tau2);
    tx->setBranch<float>("J_tau3", babymaker->recl.tau3);

    tx->setBranch<LV>("J_SD_p4", babymaker->recl.J_SD_p4);
    tx->setBranch<float>("J_SD_pt", babymaker->recl.J_SD_p4.pt());
    tx->setBranch<float>("J_SD_eta", babymaker->recl.J_SD_p4.eta());
    tx->setBranch<float>("J_SD_phi", babymaker->recl.J_SD_p4.phi());
    tx->setBranch<float>("J_SD_mass", babymaker->recl.J_SD_p4.mass());
    tx->setBranch<float>("J_SD_energy", babymaker->recl.J_SD_p4.energy());
    tx->setBranch<float>("J_SD_tau31", babymaker->recl.SD_tau31);
    tx->setBranch<float>("J_SD_tau32", babymaker->recl.SD_tau32);
    tx->setBranch<float>("J_SD_tau21", babymaker->recl.SD_tau21);
    tx->setBranch<float>("J_SD_tau1", babymaker->recl.SD_tau1);
    tx->setBranch<float>("J_SD_tau2", babymaker->recl.SD_tau2);
    tx->setBranch<float>("J_SD_tau3", babymaker->recl.SD_tau3);

    tx->setBranch<LV>("q0_p4", babymaker->recl.q0_p4);
    tx->setBranch<float>("q0_pt", babymaker->recl.q0_p4.pt());
    tx->setBranch<float>("q0_eta", babymaker->recl.q0_p4.eta());
    tx->setBranch<float>("q0_phi", babymaker->recl.q0_p4.phi());
    tx->setBranch<float>("q0_mass", babymaker->recl.q0_p4.mass());
    tx->setBranch<float>("q0_energy", babymaker->recl.q0_p4.energy());

    tx->setBranch<LV>("q1_p4", babymaker->recl.q1_p4);
    tx->setBranch<float>("q1_pt", babymaker->recl.q1_p4.pt());
    tx->setBranch<float>("q1_eta", babymaker->recl.q1_p4.eta());
    tx->setBranch<float>("q1_phi", babymaker->recl.q1_p4.phi());
    tx->setBranch<float>("q1_mass", babymaker->recl.q1_p4.mass());
    tx->setBranch<float>("q1_energy", babymaker->recl.q1_p4.energy());

}
