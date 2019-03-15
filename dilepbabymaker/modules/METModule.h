#ifndef METModule_h
#define METModule_h

#include "rooutil/rooutil.h"
#include "hwwBabyMaker.h"

namespace hwwModule
{
    //__________________________________________________________________
    // MET module
    class METModule: public RooUtil::Module
    {
        public:
            hwwBabyMaker* babymaker;
            METModule(hwwBabyMaker* parent) { babymaker = parent; }
            virtual void AddOutput();
            virtual void FillOutput();
    };
}

#endif
