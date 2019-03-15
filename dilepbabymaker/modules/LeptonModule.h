#ifndef LeptonModule_h
#define LeptonModule_h

#include "rooutil/rooutil.h"
#include "hwwBabyMaker.h"

namespace hwwModule
{
    //__________________________________________________________________
    // Lepton module
    class LeptonModule: public RooUtil::Module
    {
        public:
            hwwBabyMaker* babymaker;
            LeptonModule(hwwBabyMaker* parent) { babymaker = parent; }
            virtual void AddOutput();
            virtual void FillOutput();
    };
}

#endif
