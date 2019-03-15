#include "METModule.h"

//==============================================================================================================
//
// MET Module
//
//==============================================================================================================

void hwwModule::METModule::AddOutput()
{

    tx->createBranch<LV>("X_p4");
    tx->createBranch<float>("X_pt");
    tx->createBranch<float>("X_phi");
    tx->createBranch<float>("X_up_pt");
    tx->createBranch<float>("X_up_phi");
    tx->createBranch<float>("X_dn_pt");
    tx->createBranch<float>("X_dn_phi");
    tx->createBranch<float>("X_gen_pt");
    tx->createBranch<float>("X_gen_phi");

}

void hwwModule::METModule::FillOutput()
{

    tx->setBranch<LV>("X_p4", RooUtil::Calc::getLV(babymaker->coreMET.met_pt, 0, babymaker->coreMET.met_phi, 0));
    tx->setBranch<float>("X_pt", babymaker->coreMET.met_pt);
    tx->setBranch<float>("X_phi", babymaker->coreMET.met_phi);
    tx->setBranch<float>("X_up_pt", babymaker->coreMET.met_up_pt);
    tx->setBranch<float>("X_up_phi", babymaker->coreMET.met_up_phi);
    tx->setBranch<float>("X_dn_pt", babymaker->coreMET.met_dn_pt);
    tx->setBranch<float>("X_dn_phi", babymaker->coreMET.met_dn_phi);
    tx->setBranch<float>("X_gen_pt", cms3.gen_met());
    tx->setBranch<float>("X_gen_phi", cms3.gen_metPhi());

}
