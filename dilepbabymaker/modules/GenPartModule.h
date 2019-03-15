#ifndef GenPartModule_h
#define GenPartModule_h

#include "rooutil/rooutil.h"
#include "hwwBabyMaker.h"

namespace hwwModule
{
    //__________________________________________________________________
    // GenPart
    class GenPartModule: public RooUtil::Module
    {
        public:
            hwwBabyMaker* babymaker;
            GenPartModule(hwwBabyMaker* parent) { babymaker = parent; }
            virtual void AddOutput();
            virtual void FillOutput();
    };
}

#endif
