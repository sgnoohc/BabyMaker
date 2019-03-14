
//==============================================================================================================
//
// Fat Jet Module
//
//==============================================================================================================

void hwwBabyMaker::FatJetModule::AddOutput()
{

    tx->createBranch<LV>("J_p4");
    tx->createBranch<float>("J_pt");
    tx->createBranch<float>("J_eta");
    tx->createBranch<float>("J_phi");
    tx->createBranch<float>("J_mass");
    tx->createBranch<float>("J_energy");

}

void hwwBabyMaker::FatJetModule::FillOutput()
{


}
