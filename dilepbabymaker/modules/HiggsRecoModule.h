#ifndef HiggsRecoModule_h
#define HiggsRecoModule_h

#include "rooutil/rooutil.h"
#include "hwwBabyMaker.h"

namespace hwwModule
{
    //__________________________________________________________________
    // Higgs Reconstruction Module
    class HiggsRecoModule: public RooUtil::Module
    {
        public:
            hwwBabyMaker* babymaker;
            HiggsRecoModule(hwwBabyMaker* parent) { babymaker = parent; }
            virtual void AddOutput();
            // virtual void AddOutput_Htag();
            virtual void FillOutput();
            // virtual void FillOutput_Htag();
            // std::tuple<LV, int> SelectLepton(LV ref, float dphithresh=TMath::Pi()/2.);
            // std::tuple<LV, int> SelectFatJet(LV ref, float dphithresh=TMath::Pi()/2.);
            // std::tuple<LV, int> SelectVbosonJet(LV ref, float dphithresh=0.1);
    };
}

#endif
