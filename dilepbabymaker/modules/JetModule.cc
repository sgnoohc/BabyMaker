#include "JetModule.h"

//==============================================================================================================
//
// Jet Module
//
//==============================================================================================================

void hwwModule::JetModule::AddOutput()
{
    // These are the 4 vector sums of the lepton + MET + Fat-jet (without leptons)
    // The _SD subscript indicates that the J has gone through soft drop algorithm
    // The MET vector in this case is set to (pt, eta, phi, m) = (met_pt, 0, met_phi, 0)
    // Which means that the pz is incomplete due to missing information from the MET.

    // The definition of away and same and "in" are defined by the "LXJ" and "J" vectors
    // The "away" are the other side of the hemisphere defined by the direction of "LXJ" in r-phi coordinate
    // The "same" are the same side of the hemisphere defined by the directino of "LXJ" in r-phi coordinate
    // The "in" are the R < 0.8 of the "J" vectors (this may be defined slightly differently, but let's go with this for now)

    tx->createBranch<int>("nj");
    tx->createBranch<int>("nj_in");
    tx->createBranch<int>("nj_same");
    tx->createBranch<int>("nj_away");
    tx->createBranch<int>("nj_SD_in");
    tx->createBranch<int>("nj_SD_same");
    tx->createBranch<int>("nj_SD_away");
    tx->createBranch<int>("nb");
    tx->createBranch<int>("nb_in");
    tx->createBranch<int>("nb_same");
    tx->createBranch<int>("nb_away");
    tx->createBranch<int>("nb_SD_in");
    tx->createBranch<int>("nb_SD_same");
    tx->createBranch<int>("nb_SD_away");
    tx->createBranch<int>("nbmed");
    tx->createBranch<int>("nbmed_in");
    tx->createBranch<int>("nbmed_same");
    tx->createBranch<int>("nbmed_away");
    tx->createBranch<int>("nbmed_SD_in");
    tx->createBranch<int>("nbmed_SD_same");
    tx->createBranch<int>("nbmed_SD_away");
    tx->createBranch<int>("nbtight");
    tx->createBranch<int>("nbtight_in");
    tx->createBranch<int>("nbtight_same");
    tx->createBranch<int>("nbtight_away");
    tx->createBranch<int>("nbtight_SD_in");
    tx->createBranch<int>("nbtight_SD_same");
    tx->createBranch<int>("nbtight_SD_away");
    tx->createBranch<float>("ht");
    tx->createBranch<float>("ht_in");
    tx->createBranch<float>("ht_same");
    tx->createBranch<float>("ht_away");
    tx->createBranch<float>("ht_SD_in");
    tx->createBranch<float>("ht_SD_same");
    tx->createBranch<float>("ht_SD_away");

    tx->createBranch<LV>("R_p4");
    tx->createBranch<float>("R_pt");
    tx->createBranch<float>("R_eta");
    tx->createBranch<float>("R_phi");
    tx->createBranch<float>("R_mass");
    tx->createBranch<float>("R_energy");

    tx->createBranch<LV>("R_cent_p4");
    tx->createBranch<float>("R_cent_pt");
    tx->createBranch<float>("R_cent_eta");
    tx->createBranch<float>("R_cent_phi");
    tx->createBranch<float>("R_cent_mass");
    tx->createBranch<float>("R_cent_energy");

}

void hwwModule::JetModule::FillOutput()
{

    // These are the 4 vector sums of the lepton + MET + Fat-jet (without leptons)
    // The _SD subscript indicates that the J has gone through soft drop algorithm
    // The MET vector in this case is set to (pt, eta, phi, m) = (met_pt, 0, met_phi, 0)
    // Which means that the pz is incomplete due to missing information from the MET.

    const LV& LXJ_p4 = tx->getBranch<LV>("LXJ_p4");
    const LV& LXJ_SD_p4 = tx->getBranch<LV>("LXJ_SD_p4");

    // These are the fat-jet vectors this will define the "in" (i.e. inside fat-jets)
    const LV& J_p4 = tx->getBranch<LV>("J_p4");
    const LV& J_SD_p4 = tx->getBranch<LV>("J_SD_p4");

    // The definition of away and same and "in" are defined by the "LXJ" and "J" vectors
    // The "away" are the other side of the hemisphere defined by the direction of "LXJ" in r-phi coordinate
    // The "same" are the same side of the hemisphere defined by the directino of "LXJ" in r-phi coordinate
    // The "in" are the R < 0.8 of the "J" vectors (this may be defined slightly differently, but let's go with this for now)


    // ----
    // Loop over the jets and compute these variables

    int nj = 0;
    int nj_in = 0;
    int nj_same = 0;
    int nj_away = 0;
    int nj_SD_in = 0;
    int nj_SD_same = 0;
    int nj_SD_away = 0;
    int nb = 0;
    int nb_in = 0;
    int nb_same = 0;
    int nb_away = 0;
    int nb_SD_in = 0;
    int nb_SD_same = 0;
    int nb_SD_away = 0;
    int nbmed = 0;
    int nbmed_in = 0;
    int nbmed_same = 0;
    int nbmed_away = 0;
    int nbmed_SD_in = 0;
    int nbmed_SD_same = 0;
    int nbmed_SD_away = 0;
    int nbtight = 0;
    int nbtight_in = 0;
    int nbtight_same = 0;
    int nbtight_away = 0;
    int nbtight_SD_in = 0;
    int nbtight_SD_same = 0;
    int nbtight_SD_away = 0;
    float ht = 0;
    float ht_in = 0;
    float ht_same = 0;
    float ht_away = 0;
    float ht_SD_in = 0;
    float ht_SD_same = 0;
    float ht_SD_away = 0;

    LV R_p4;
    LV R_cent_p4;

    for (unsigned ijet = 0; ijet < babymaker->coreJet.index.size(); ++ijet)
    {
        int idx = babymaker->coreJet.index[ijet];
        float corr = babymaker->coreJet.corrs[ijet];
        // float shift = babymaker->coreJet.shifts[ijet];
        float current_csv_val = cms3.getbtagvalue("pfCombinedInclusiveSecondaryVertexV2BJetTags", idx);
        LV jet = cms3.pfjets_p4()[idx] * cms3.pfjets_undoJEC()[idx] * corr;

        // Check whether this jet overlaps with any of the leptons
        if (babymaker->isLeptonOverlappingWithJet(ijet))
            continue;

        // Compute dphi to determine which hemisphere the jet is at
        float dphi = RooUtil::Calc::DeltaPhi(jet, LXJ_p4);
        float dphi_SD = RooUtil::Calc::DeltaPhi(jet, LXJ_SD_p4);

        // Compute dR to determine whether the jets are inside the tagged fat-jet
        float dr_J = RooUtil::Calc::DeltaR(jet, J_p4);
        float dr_SD_J = RooUtil::Calc::DeltaR(jet, J_SD_p4);

        // The pt of the jet
        float pt = jet.pt();

        // Require pt minimum requirement of 30 GeV for safety
        if (jet.pt() > 30)
        {

            // Increase the counter for the number of jets
            nj++;
            ht += pt;

            // Sum the "Recoil" jets
            R_p4 += jet;
            if (fabs(jet.eta()) < 2.5)
                R_cent_p4 += jet;

            if (fabs(dphi) < TMath::Pi()/2. and dr_J < 0.8)
            {
                nj_in++;
                ht_in += pt;
            }
            else if (fabs(dphi) < TMath::Pi()/2. and dr_J > 0.8)
            {
                nj_same++;
                ht_same += pt;
            }
            else
            {
                nj_away++;
                ht_away += pt;
            }

            if (fabs(dphi_SD) < TMath::Pi()/2. and dr_SD_J < 0.8)
            {
                nj_SD_in++;
                ht_SD_in += pt;
            }
            else if (fabs(dphi_SD) < TMath::Pi()/2. and dr_SD_J > 0.8)
            {
                nj_SD_same++;
                ht_SD_same += pt;
            }
            else
            {
                nj_SD_away++;
                ht_SD_away += pt;
            }

            babymaker->coreBtagSF.accumulateSF(idx, jet.pt(), jet.eta());

            // if (!isFastSim())
            //     babymaker->coreBtagSF.accumulateSF(idx, jet.pt(), jet.eta());
            // else
            //     babymaker->coreBtagSFFastSim.accumulateSF(idx, jet.pt(), jet.eta());

        }

        const double bjet_CSV_TIGHT = 0.9535;
        const double bjet_CSV_MED = 0.8484;
        const double bjet_CSV_LOOSE = 0.5426;

        // Counting N-btag jets: Require minimum of 20 GeV for increased acceptance
        if (jet.pt() > 20. and fabs(jet.eta()) < 2.4)
        {

            // Increase the counter for the number of b-jets
            if (current_csv_val >= bjet_CSV_LOOSE) nb++;
            if (current_csv_val >= bjet_CSV_MED) nbmed++;
            if (current_csv_val >= bjet_CSV_TIGHT) nbtight++;

            if (fabs(dphi) < TMath::Pi()/2. and dr_J < 0.8)
            {
                if (current_csv_val >= bjet_CSV_LOOSE) nb_in++;
                if (current_csv_val >= bjet_CSV_MED) nbmed_in++;
                if (current_csv_val >= bjet_CSV_TIGHT) nbtight_in++;
            }
            else if (fabs(dphi) < TMath::Pi()/2. and dr_J > 0.8)
            {
                if (current_csv_val >= bjet_CSV_LOOSE) nb_same++;
                if (current_csv_val >= bjet_CSV_MED) nbmed_same++;
                if (current_csv_val >= bjet_CSV_TIGHT) nbtight_same++;
            }
            else
            {
                if (current_csv_val >= bjet_CSV_LOOSE) nb_away++;
                if (current_csv_val >= bjet_CSV_MED) nbmed_away++;
                if (current_csv_val >= bjet_CSV_TIGHT) nbtight_away++;
            }

            if (fabs(dphi_SD) < TMath::Pi()/2. and dr_SD_J < 0.8)
            {
                if (current_csv_val >= bjet_CSV_LOOSE) nb_SD_in++;
                if (current_csv_val >= bjet_CSV_MED) nbmed_SD_in++;
                if (current_csv_val >= bjet_CSV_TIGHT) nbtight_SD_in++;
            }
            else if (fabs(dphi_SD) < TMath::Pi()/2. and dr_SD_J > 0.8)
            {
                if (current_csv_val >= bjet_CSV_LOOSE) nb_SD_same++;
                if (current_csv_val >= bjet_CSV_MED) nbmed_SD_same++;
                if (current_csv_val >= bjet_CSV_TIGHT) nbtight_SD_same++;
            }
            else
            {
                if (current_csv_val >= bjet_CSV_LOOSE) nb_SD_away++;
                if (current_csv_val >= bjet_CSV_MED) nbmed_SD_away++;
                if (current_csv_val >= bjet_CSV_TIGHT) nbtight_SD_away++;
            }

        }

        // LV jet_up = jet * (1. + shift);
        // if (jet_up.pt() > 30)
        // {
        //     tx->pushbackToBranch<LV>("jets_up_p4", jet_up);
        //     tx->pushbackToBranch<float>("jets_up_pt", jet_up.pt());
        //     tx->pushbackToBranch<float>("jets_up_eta", jet_up.eta());
        //     tx->pushbackToBranch<float>("jets_up_phi", jet_up.phi());
        //     tx->pushbackToBranch<float>("jets_up_csv", current_csv_val);
        // }

        // LV jet_dn = jet * (1. - shift);
        // if (jet_dn.pt() > 30)
        // {
        //     tx->pushbackToBranch<LV>("jets_dn_p4", jet_dn);
        //     tx->pushbackToBranch<float>("jets_dn_pt", jet_dn.pt());
        //     tx->pushbackToBranch<float>("jets_dn_eta", jet_dn.eta());
        //     tx->pushbackToBranch<float>("jets_dn_phi", jet_dn.phi());
        //     tx->pushbackToBranch<float>("jets_dn_csv", current_csv_val);
        // }

    }

    tx->setBranch<int>("nj", nj);
    tx->setBranch<int>("nj_in", nj_in);
    tx->setBranch<int>("nj_same", nj_same);
    tx->setBranch<int>("nj_away", nj_away);
    tx->setBranch<int>("nj_SD_in", nj_SD_in);
    tx->setBranch<int>("nj_SD_same", nj_SD_same);
    tx->setBranch<int>("nj_SD_away", nj_SD_away);
    tx->setBranch<int>("nb", nb);
    tx->setBranch<int>("nb_in", nb_in);
    tx->setBranch<int>("nb_same", nb_same);
    tx->setBranch<int>("nb_away", nb_away);
    tx->setBranch<int>("nb_SD_in", nb_SD_in);
    tx->setBranch<int>("nb_SD_same", nb_SD_same);
    tx->setBranch<int>("nb_SD_away", nb_SD_away);
    tx->setBranch<int>("nbmed", nbmed);
    tx->setBranch<int>("nbmed_in", nbmed_in);
    tx->setBranch<int>("nbmed_same", nbmed_same);
    tx->setBranch<int>("nbmed_away", nbmed_away);
    tx->setBranch<int>("nbmed_SD_in", nbmed_SD_in);
    tx->setBranch<int>("nbmed_SD_same", nbmed_SD_same);
    tx->setBranch<int>("nbmed_SD_away", nbmed_SD_away);
    tx->setBranch<int>("nbtight", nbtight);
    tx->setBranch<int>("nbtight_in", nbtight_in);
    tx->setBranch<int>("nbtight_same", nbtight_same);
    tx->setBranch<int>("nbtight_away", nbtight_away);
    tx->setBranch<int>("nbtight_SD_in", nbtight_SD_in);
    tx->setBranch<int>("nbtight_SD_same", nbtight_SD_same);
    tx->setBranch<int>("nbtight_SD_away", nbtight_SD_away);
    tx->setBranch<float>("ht", ht);
    tx->setBranch<float>("ht_in", ht_in);
    tx->setBranch<float>("ht_same", ht_same);
    tx->setBranch<float>("ht_away", ht_away);
    tx->setBranch<float>("ht_SD_in", ht_SD_in);
    tx->setBranch<float>("ht_SD_same", ht_SD_same);
    tx->setBranch<float>("ht_SD_away", ht_SD_away);
    tx->setBranch<LV>("R_p4", R_p4);
    tx->setBranch<float>("R_pt", R_p4.pt());
    tx->setBranch<float>("R_eta", R_p4.eta());
    tx->setBranch<float>("R_phi", R_p4.phi());
    tx->setBranch<float>("R_mass", R_p4.mass());
    tx->setBranch<float>("R_energy", R_p4.energy());
    tx->setBranch<LV>("R_cent_p4", R_cent_p4);
    tx->setBranch<float>("R_cent_pt", R_cent_p4.pt());
    tx->setBranch<float>("R_cent_eta", R_cent_p4.eta());
    tx->setBranch<float>("R_cent_phi", R_cent_p4.phi());
    tx->setBranch<float>("R_cent_mass", R_cent_p4.mass());
    tx->setBranch<float>("R_cent_energy", R_cent_p4.energy());

}
