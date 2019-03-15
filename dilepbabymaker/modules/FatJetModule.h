#ifndef FatJetModule_h
#define FatJetModule_h

#include "rooutil/rooutil.h"
#include "hwwBabyMaker.h"

namespace hwwModule
{
    //__________________________________________________________________
    // FatJet module
    class FatJetModule: public RooUtil::Module
    {
        public:
            hwwBabyMaker* babymaker;
            FatJetModule(hwwBabyMaker* parent) { babymaker = parent; }
            virtual void AddOutput();
            virtual void FillOutput();
    };
}

#endif
