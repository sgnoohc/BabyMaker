#ifndef JetModule_h
#define JetModule_h

#include "rooutil/rooutil.h"
#include "hwwBabyMaker.h"

namespace hwwModule
{
    //__________________________________________________________________
    // Jet module
    class JetModule: public RooUtil::Module
    {
        public:
            hwwBabyMaker* babymaker;
            JetModule(hwwBabyMaker* parent) { babymaker = parent; }
            virtual void AddOutput();
            virtual void FillOutput();
    };
}

#endif
