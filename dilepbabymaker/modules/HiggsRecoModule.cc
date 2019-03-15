#include "HiggsRecoModule.h"

//==============================================================================================================
//
// Higgs Reco Module
//
//==============================================================================================================

void hwwModule::HiggsRecoModule::AddOutput()
{

    // These are the 4 vector sums of the lepton + MET + Fat-jet (without leptons)
    // The _SD subscript indicates that the J has gone through soft drop algorithm
    // The MET vector in this case is set to (pt, eta, phi, m) = (met_pt, 0, met_phi, 0)
    // Which means that the pz is incomplete due to missing information from the MET.

    tx->createBranch<LV>("LXJ_p4");
    tx->createBranch<float>("LXJ_pt");
    tx->createBranch<float>("LXJ_eta");
    tx->createBranch<float>("LXJ_phi");
    tx->createBranch<float>("LXJ_mass");
    tx->createBranch<float>("LXJ_energy");

    tx->createBranch<LV>("LXJ_SD_p4");
    tx->createBranch<float>("LXJ_SD_pt");
    tx->createBranch<float>("LXJ_SD_eta");
    tx->createBranch<float>("LXJ_SD_phi");
    tx->createBranch<float>("LXJ_SD_mass");
    tx->createBranch<float>("LXJ_SD_energy");

    tx->createBranch<float>("LX_pt");
    tx->createBranch<float>("LX_mt");
    tx->createBranch<float>("LX_mass");
    tx->createBranch<float>("LX_dphi");

    tx->createBranch<float>("LJ_pt");
    tx->createBranch<float>("LJ_mt");
    tx->createBranch<float>("LJ_mass");
    tx->createBranch<float>("LJ_dphi");
    tx->createBranch<float>("LJ_deta");
    tx->createBranch<float>("LJ_dr");
    tx->createBranch<float>("LJ_dptf");

    tx->createBranch<float>("LJ_SD_pt");
    tx->createBranch<float>("LJ_SD_mt");
    tx->createBranch<float>("LJ_SD_mass");
    tx->createBranch<float>("LJ_SD_dphi");
    tx->createBranch<float>("LJ_SD_deta");
    tx->createBranch<float>("LJ_SD_dr");
    tx->createBranch<float>("LJ_SD_dptf");

    tx->createBranch<float>("Lq0_pt");
    tx->createBranch<float>("Lq0_mt");
    tx->createBranch<float>("Lq0_mass");
    tx->createBranch<float>("Lq0_dphi");
    tx->createBranch<float>("Lq0_deta");
    tx->createBranch<float>("Lq0_dr");
    tx->createBranch<float>("Lq0_dptf");

    tx->createBranch<float>("Lq1_pt");
    tx->createBranch<float>("Lq1_mt");
    tx->createBranch<float>("Lq1_mass");
    tx->createBranch<float>("Lq1_dphi");
    tx->createBranch<float>("Lq1_deta");
    tx->createBranch<float>("Lq1_dr");
    tx->createBranch<float>("Lq1_dptf");

    tx->createBranch<float>("Lqmax_pt");
    tx->createBranch<float>("Lqmax_mt");
    tx->createBranch<float>("Lqmax_mass");
    tx->createBranch<float>("Lqmax_dphi");
    tx->createBranch<float>("Lqmax_deta");
    tx->createBranch<float>("Lqmax_dr");
    tx->createBranch<float>("Lqmax_dptf");

    tx->createBranch<float>("LHRatio");
    tx->createBranch<float>("LHRatio_SD");

    tx->createBranch<LV>("neu_p4");
    tx->createBranch<LV>("neu_p4_sol1");
    tx->createBranch<LV>("neu_p4_sol2");
    tx->createBranch<LV>("neu_p4_invsol1");
    tx->createBranch<LV>("neu_p4_invsol2");

}

void hwwModule::HiggsRecoModule::FillOutput()
{

    // These are the 4 vector sums of the lepton + MET + Fat-jet (without leptons)
    // The _SD subscript indicates that the J has gone through soft drop algorithm
    // The MET vector in this case is set to (pt, eta, phi, m) = (met_pt, 0, met_phi, 0)
    // Which means that the pz is incomplete due to missing information from the MET.

    const LV& L_p4    = tx->getBranch<LV>("L_p4");
    const LV& J_p4    = tx->getBranch<LV>("J_p4");
    const LV& J_SD_p4 = tx->getBranch<LV>("J_SD_p4");
    const LV& X_p4    = tx->getBranch<LV>("X_p4");
    const LV& q0_p4   = tx->getBranch<LV>("q0_p4");
    const LV& q1_p4   = tx->getBranch<LV>("q1_p4");

    LV LXJ_p4 = L_p4 + J_p4 + X_p4;
    LV LXJ_SD_p4 = L_p4 + J_SD_p4 + X_p4;

    tx->setBranch<LV>("LXJ_p4", LXJ_p4);
    tx->setBranch<float>("LXJ_pt", LXJ_p4.pt());
    tx->setBranch<float>("LXJ_eta", LXJ_p4.eta());
    tx->setBranch<float>("LXJ_phi", LXJ_p4.phi());
    tx->setBranch<float>("LXJ_mass", LXJ_p4.mass());
    tx->setBranch<float>("LXJ_energy", LXJ_p4.energy());

    tx->setBranch<LV>("LXJ_SD_p4", LXJ_SD_p4);
    tx->setBranch<float>("LXJ_SD_pt", LXJ_SD_p4.pt());
    tx->setBranch<float>("LXJ_SD_eta", LXJ_SD_p4.eta());
    tx->setBranch<float>("LXJ_SD_phi", LXJ_SD_p4.phi());
    tx->setBranch<float>("LXJ_SD_mass", LXJ_SD_p4.mass());
    tx->setBranch<float>("LXJ_SD_energy", LXJ_SD_p4.energy());

    LV LX_p4 = L_p4 + X_p4;
    tx->setBranch<float>("LX_pt", LX_p4.pt());
    tx->setBranch<float>("LX_mt", LX_p4.mt());
    tx->setBranch<float>("LX_mass", LX_p4.mass());
    tx->setBranch<float>("LX_dphi", RooUtil::Calc::DeltaPhi(L_p4, X_p4));

    LV LJ_p4 = L_p4 + J_p4;
    tx->setBranch<float>("LJ_pt", LJ_p4.pt());
    tx->setBranch<float>("LJ_mt", LJ_p4.mt());
    tx->setBranch<float>("LJ_mass", LJ_p4.mass());
    tx->setBranch<float>("LJ_dphi", RooUtil::Calc::DeltaPhi(L_p4, J_p4));
    tx->setBranch<float>("LJ_deta", RooUtil::Calc::DeltaEta(L_p4, J_p4));
    tx->setBranch<float>("LJ_dr", RooUtil::Calc::DeltaR(L_p4, J_p4));
    tx->setBranch<float>("LJ_dptf", (L_p4.pt() - J_p4.pt()) / LJ_p4.pt());

    LV LJ_SD_p4 = L_p4 + J_SD_p4;
    tx->setBranch<float>("LJ_SD_pt", LJ_SD_p4.pt());
    tx->setBranch<float>("LJ_SD_mt", LJ_SD_p4.mt());
    tx->setBranch<float>("LJ_SD_mass", LJ_SD_p4.mass());
    tx->setBranch<float>("LJ_SD_dphi", RooUtil::Calc::DeltaPhi(L_p4, J_SD_p4));
    tx->setBranch<float>("LJ_SD_deta", RooUtil::Calc::DeltaEta(L_p4, J_SD_p4));
    tx->setBranch<float>("LJ_SD_dr", RooUtil::Calc::DeltaR(L_p4, J_SD_p4));
    tx->setBranch<float>("LJ_SD_dptf", (L_p4.pt() - J_SD_p4.pt()) / LJ_SD_p4.pt());

    LV Lq0_p4 = L_p4 + q0_p4;
    tx->setBranch<float>("Lq0_pt", Lq0_p4.pt());
    tx->setBranch<float>("Lq0_mt", Lq0_p4.mt());
    tx->setBranch<float>("Lq0_mass", Lq0_p4.mass());
    tx->setBranch<float>("Lq0_dphi", RooUtil::Calc::DeltaPhi(L_p4, q0_p4));
    tx->setBranch<float>("Lq0_deta", RooUtil::Calc::DeltaEta(L_p4, q0_p4));
    tx->setBranch<float>("Lq0_dr", RooUtil::Calc::DeltaR(L_p4, q0_p4));
    tx->setBranch<float>("Lq0_dptf", (L_p4.pt() - q0_p4.pt()) / Lq0_p4.pt());

    LV Lq1_p4 = L_p4 + q1_p4;
    tx->setBranch<float>("Lq1_pt", Lq1_p4.pt());
    tx->setBranch<float>("Lq1_mt", Lq1_p4.mt());
    tx->setBranch<float>("Lq1_mass", Lq1_p4.mass());
    tx->setBranch<float>("Lq1_dphi", RooUtil::Calc::DeltaPhi(L_p4, q1_p4));
    tx->setBranch<float>("Lq1_deta", RooUtil::Calc::DeltaEta(L_p4, q1_p4));
    tx->setBranch<float>("Lq1_dr", RooUtil::Calc::DeltaR(L_p4, q1_p4));
    tx->setBranch<float>("Lq1_dptf", (L_p4.pt() - q1_p4.pt()) / Lq1_p4.pt());

    LV Lqmax_p4 = Lq0_p4.mass() > Lq1_p4.mass() ? Lq0_p4 : Lq1_p4;
    LV qmax_p4 = Lq0_p4.mass() > Lq1_p4.mass() ? q0_p4 : q1_p4;
    tx->setBranch<float>("Lqmax_pt", Lqmax_p4.pt());
    tx->setBranch<float>("Lqmax_mt", Lqmax_p4.mt());
    tx->setBranch<float>("Lqmax_mass", Lqmax_p4.mass());
    tx->setBranch<float>("Lqmax_dphi", RooUtil::Calc::DeltaPhi(L_p4, qmax_p4));
    tx->setBranch<float>("Lqmax_deta", RooUtil::Calc::DeltaEta(L_p4, qmax_p4));
    tx->setBranch<float>("Lqmax_dr", RooUtil::Calc::DeltaR(L_p4, qmax_p4));
    tx->setBranch<float>("Lqmax_dptf", (L_p4.pt() - qmax_p4.pt()) / Lqmax_p4.pt());

    tx->setBranch<float>("LHRatio", LX_p4.pt() / LXJ_p4.pt() - J_p4.pt() / LXJ_p4.pt());
    tx->setBranch<float>("LHRatio_SD", LX_p4.pt() / LXJ_SD_p4.pt() - J_SD_p4.pt() / LXJ_SD_p4.pt());

}
