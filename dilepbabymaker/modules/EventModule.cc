#include "EventModule.h"

//==============================================================================================================
//
// Event Module
//
//==============================================================================================================

void hwwModule::EventModule::AddOutput()
{
    tx->createBranch<float>("nvtx");
}

void hwwModule::EventModule::FillOutput()
{
    // Count number of good vertices.
    int nvtx = 0;
    for (unsigned int ivtx = 0; ivtx < cms3.evt_nvtxs(); ivtx++)
    {
        if (!isGoodVertex(ivtx)) { continue; }
        nvtx++;
    }
    tx->setBranch<float>("nvtx", nvtx);
}
