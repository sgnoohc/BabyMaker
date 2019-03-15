#ifndef TriggerModule_h
#define TriggerModule_h

#include "rooutil/rooutil.h"
#include "hwwBabyMaker.h"

namespace hwwModule
{
    //__________________________________________________________________
    // Trigger module
    class TriggerModule: public RooUtil::Module
    {
        public:
            hwwBabyMaker* babymaker;
            TriggerModule(hwwBabyMaker* parent) { babymaker = parent; }
            virtual void AddOutput();
            virtual void FillOutput();
    };
}

#endif
