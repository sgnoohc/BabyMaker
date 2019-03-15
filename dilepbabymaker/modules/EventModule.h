#ifndef EventModule_h
#define EventModule_h

#include "rooutil/rooutil.h"
#include "hwwBabyMaker.h"

namespace hwwModule
{
    //__________________________________________________________________
    // Event
    class EventModule: public RooUtil::Module
    {
        public:
            hwwBabyMaker* babymaker;
            EventModule(hwwBabyMaker* parent) { babymaker = parent; }
            virtual void AddOutput();
            virtual void FillOutput();
    };
}

#endif
