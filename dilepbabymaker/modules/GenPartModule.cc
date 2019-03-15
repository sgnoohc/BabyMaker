#include "GenPartModule.h"

//==============================================================================================================
//
// GenPart Module
//
//==============================================================================================================

void hwwModule::GenPartModule::AddOutput()
{
    tx->createBranch<float>("gen_ht");
}

void hwwModule::GenPartModule::FillOutput()
{
    tx->setBranch<float>("gen_ht", babymaker->coreGenPart.gen_ht);
}

