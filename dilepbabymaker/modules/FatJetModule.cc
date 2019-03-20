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
    tx->createBranch<float>("J_undoJEC");
    tx->createBranch<float>("J_shift");

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

    tx->createBranch<LV>("V_p4");
    tx->createBranch<float>("V_pt");
    tx->createBranch<float>("V_eta");
    tx->createBranch<float>("V_phi");
    tx->createBranch<float>("V_mass");
    tx->createBranch<float>("V_energy");
    tx->createBranch<float>("V_SD_mass");
    tx->createBranch<float>("V_tau31");
    tx->createBranch<float>("V_tau32");
    tx->createBranch<float>("V_tau21");
    tx->createBranch<float>("V_tau1");
    tx->createBranch<float>("V_tau2");
    tx->createBranch<float>("V_tau3");
    tx->createBranch<float>("V_undoJEC");
    tx->createBranch<float>("V_shift");
    tx->createBranch<float>("V_deep_rawdisc_h4q");
    tx->createBranch<float>("V_deep_rawdisc_hbb");
    tx->createBranch<float>("V_deep_rawdisc_qcd");
    tx->createBranch<float>("V_deep_rawdisc_top");
    tx->createBranch<float>("V_deep_rawdisc_w");
    tx->createBranch<float>("V_deep_rawdisc_z");
    tx->createBranch<float>("V_deep_rawdisc_zbb");
    tx->createBranch<float>("V_softdropPuppiSubjet1_pt");
    tx->createBranch<float>("V_softdropPuppiSubjet1_eta");
    tx->createBranch<float>("V_softdropPuppiSubjet1_phi");
    tx->createBranch<float>("V_softdropPuppiSubjet1_mass");
    tx->createBranch<float>("V_softdropPuppiSubjet1_energy");
    tx->createBranch<float>("V_softdropPuppiSubjet2_pt");
    tx->createBranch<float>("V_softdropPuppiSubjet2_eta");
    tx->createBranch<float>("V_softdropPuppiSubjet2_phi");
    tx->createBranch<float>("V_softdropPuppiSubjet2_mass");
    tx->createBranch<float>("V_softdropPuppiSubjet2_energy");

}

void hwwModule::FatJetModule::FillOutput()
{

    tx->setBranch<LV>("J_p4", recl.J_p4);
    tx->setBranch<float>("J_pt", recl.J_p4.pt());
    tx->setBranch<float>("J_eta", recl.J_p4.eta());
    tx->setBranch<float>("J_phi", recl.J_p4.phi());
    tx->setBranch<float>("J_mass", recl.J_p4.mass());
    tx->setBranch<float>("J_energy", recl.J_p4.energy());
    tx->setBranch<float>("J_tau31", recl.tau31);
    tx->setBranch<float>("J_tau32", recl.tau32);
    tx->setBranch<float>("J_tau21", recl.tau21);
    tx->setBranch<float>("J_tau1", recl.tau1);
    tx->setBranch<float>("J_tau2", recl.tau2);
    tx->setBranch<float>("J_tau3", recl.tau3);
    tx->setBranch<float>("J_undoJEC", 1. / recl.corr);
    tx->setBranch<float>("J_shift", recl.shift);

    tx->setBranch<LV>("J_SD_p4", recl.J_SD_p4);
    tx->setBranch<float>("J_SD_pt", recl.J_SD_p4.pt());
    tx->setBranch<float>("J_SD_eta", recl.J_SD_p4.eta());
    tx->setBranch<float>("J_SD_phi", recl.J_SD_p4.phi());
    tx->setBranch<float>("J_SD_mass", recl.J_SD_p4.mass());
    tx->setBranch<float>("J_SD_energy", recl.J_SD_p4.energy());
    tx->setBranch<float>("J_SD_tau31", recl.SD_tau31);
    tx->setBranch<float>("J_SD_tau32", recl.SD_tau32);
    tx->setBranch<float>("J_SD_tau21", recl.SD_tau21);
    tx->setBranch<float>("J_SD_tau1", recl.SD_tau1);
    tx->setBranch<float>("J_SD_tau2", recl.SD_tau2);
    tx->setBranch<float>("J_SD_tau3", recl.SD_tau3);

    tx->setBranch<LV>("q0_p4", recl.q0_p4);
    tx->setBranch<float>("q0_pt", recl.q0_p4.pt());
    tx->setBranch<float>("q0_eta", recl.q0_p4.eta());
    tx->setBranch<float>("q0_phi", recl.q0_p4.phi());
    tx->setBranch<float>("q0_mass", recl.q0_p4.mass());
    tx->setBranch<float>("q0_energy", recl.q0_p4.energy());

    tx->setBranch<LV>("q1_p4", recl.q1_p4);
    tx->setBranch<float>("q1_pt", recl.q1_p4.pt());
    tx->setBranch<float>("q1_eta", recl.q1_p4.eta());
    tx->setBranch<float>("q1_phi", recl.q1_p4.phi());
    tx->setBranch<float>("q1_mass", recl.q1_p4.mass());
    tx->setBranch<float>("q1_energy", recl.q1_p4.energy());

    const LV& L_p4 = tx->getBranch<LV>("L_p4");
    const LV& J_p4 = tx->getBranch<LV>("J_p4");
    const LV& X_p4 = tx->getBranch<LV>("X_p4");
    LV LXJ_p4 = L_p4 + J_p4 + X_p4;

    // Find the jet for V boson
    // If there are only two ak8jets, one must be the higgs, and the other is the V
    // So use J_p4 vector to anchor the one ak8jet to higgs, and pick the other as V

    if (babymaker->coreFatJet.index.size() == 2)
    {

        int i0 = babymaker->coreFatJet.index[0];
        int i1 = babymaker->coreFatJet.index[1];

        LV j0 = cms3.ak8jets_p4()[i0];
        LV j1 = cms3.ak8jets_p4()[i1];

        float dr0 = RooUtil::Calc::DeltaR(j0, J_p4);
        float dr1 = RooUtil::Calc::DeltaR(j1, J_p4);

        int ih = dr0 > dr1 ? i0 : i1;

        SetVBosonJet(ih);

    }
    else
    {

        // Loop over the jets and find the leading jet on the away side hemisphere
        float maxPt = 0;
        for (unsigned ijet = 0; ijet < babymaker->coreFatJet.index.size(); ++ijet)
        {
            int idx = babymaker->coreFatJet.index[ijet];
            float corr = babymaker->coreFatJet.corrs[ijet];
            float shift = babymaker->coreFatJet.shifts[ijet];
            LV fatjet = cms3.ak8jets_p4()[idx] * cms3.ak8jets_undoJEC()[idx] * corr;

            float dphi = RooUtil::Calc::DeltaPhi(fatjet, LXJ_p4);
            float pt = fatjet.pt();

            if (pt > maxPt and dphi > TMath::Pi() / 2.)
            {

                maxPt = pt;

                SetVBosonJet(ijet);

            }

        }

    }

}

void hwwModule::FatJetModule::SetVBosonJet(int ijet)
{

    int idx = babymaker->coreFatJet.index[ijet];
    float corr = babymaker->coreFatJet.corrs[ijet];
    float shift = babymaker->coreFatJet.shifts[ijet];
    LV fatjet = cms3.ak8jets_p4()[idx] * cms3.ak8jets_undoJEC()[idx] * corr;

    tx->setBranch<LV>("V_p4", fatjet);
    tx->setBranch<float>("V_pt", fatjet.pt());
    tx->setBranch<float>("V_eta", fatjet.eta());
    tx->setBranch<float>("V_phi", fatjet.phi());
    tx->setBranch<float>("V_mass", fatjet.mass());
    tx->setBranch<float>("V_energy", fatjet.energy());
    tx->setBranch<float>("V_SD_mass", cms3.ak8jets_softdropMass()[idx]);
    tx->setBranch<float>("V_tau31", cms3.ak8jets_nJettinessTau3()[idx] / cms3.ak8jets_nJettinessTau1()[idx]);
    tx->setBranch<float>("V_tau32", cms3.ak8jets_nJettinessTau3()[idx] / cms3.ak8jets_nJettinessTau2()[idx]);
    tx->setBranch<float>("V_tau21", cms3.ak8jets_nJettinessTau2()[idx] / cms3.ak8jets_nJettinessTau1()[idx]);
    tx->setBranch<float>("V_tau1", cms3.ak8jets_nJettinessTau1()[idx]);
    tx->setBranch<float>("V_tau2", cms3.ak8jets_nJettinessTau2()[idx]);
    tx->setBranch<float>("V_tau3", cms3.ak8jets_nJettinessTau3()[idx]);
    tx->setBranch<float>("V_undoJEC", 1. / corr);
    tx->setBranch<float>("V_shift", shift);
    tx->setBranch<float>("V_deep_rawdisc_h4q", cms3.ak8jets_deep_rawdisc_h4q()[idx]);
    tx->setBranch<float>("V_deep_rawdisc_hbb", cms3.ak8jets_deep_rawdisc_hbb()[idx]);
    tx->setBranch<float>("V_deep_rawdisc_qcd", cms3.ak8jets_deep_rawdisc_qcd()[idx]);
    tx->setBranch<float>("V_deep_rawdisc_top", cms3.ak8jets_deep_rawdisc_top()[idx]);
    tx->setBranch<float>("V_deep_rawdisc_w", cms3.ak8jets_deep_rawdisc_w()[idx]);
    tx->setBranch<float>("V_deep_rawdisc_z", cms3.ak8jets_deep_rawdisc_z()[idx]);
    tx->setBranch<float>("V_deep_rawdisc_zbb", cms3.ak8jets_deep_rawdisc_zbb()[idx]);
    tx->setBranch<float>("V_softdropPuppiSubjet1_pt", cms3.ak8jets_softdropPuppiSubjet1()[idx].pt());
    tx->setBranch<float>("V_softdropPuppiSubjet1_eta", cms3.ak8jets_softdropPuppiSubjet1()[idx].eta());
    tx->setBranch<float>("V_softdropPuppiSubjet1_phi", cms3.ak8jets_softdropPuppiSubjet1()[idx].phi());
    tx->setBranch<float>("V_softdropPuppiSubjet1_mass", cms3.ak8jets_softdropPuppiSubjet1()[idx].mass());
    tx->setBranch<float>("V_softdropPuppiSubjet1_energy", cms3.ak8jets_softdropPuppiSubjet1()[idx].energy());
    tx->setBranch<float>("V_softdropPuppiSubjet2_pt", cms3.ak8jets_softdropPuppiSubjet2()[idx].pt());
    tx->setBranch<float>("V_softdropPuppiSubjet2_eta", cms3.ak8jets_softdropPuppiSubjet2()[idx].eta());
    tx->setBranch<float>("V_softdropPuppiSubjet2_phi", cms3.ak8jets_softdropPuppiSubjet2()[idx].phi());
    tx->setBranch<float>("V_softdropPuppiSubjet2_mass", cms3.ak8jets_softdropPuppiSubjet2()[idx].mass());
    tx->setBranch<float>("V_softdropPuppiSubjet2_energy", cms3.ak8jets_softdropPuppiSubjet2()[idx].energy());

}

