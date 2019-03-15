#ifndef HWWlvjjTruthModule_h
#define HWWlvjjTruthModule_h

#include "rooutil/rooutil.h"
#include "hwwBabyMaker.h"

namespace hwwModule
{
    //__________________________________________________________________
    // HWWlvjj Truth Module
    class HWWlvjjTruthModule: public RooUtil::Module
    {
        public:
            hwwBabyMaker* babymaker;
            HWWlvjjTruthModule(hwwBabyMaker* parent) { babymaker = parent; }
            virtual void AddOutput();
            virtual void FillOutput();
    };
}

#endif
