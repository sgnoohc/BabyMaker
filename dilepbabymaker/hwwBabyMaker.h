#ifndef hwwBabyMaker_h
#define hwwBabyMaker_h

#include "babyMaker.h"

class hwwBabyMaker: public babyMaker
{
    public:
        hwwBabyMaker();
        ~hwwBabyMaker();

        RooUtil::Processor* processor;

        virtual void ProcessObjectsPrePassSelection();
        virtual void ProcessObjectsPostPassSelection();
        virtual void ProcessElectrons();
        virtual void ProcessMuons();
        virtual bool PassSelection();

        virtual void AddOutput();
        virtual void FillOutput();

        static bool isPt10Electron(int idx);
        static bool isPt10Muon(int idx);
        bool isLeptonOverlappingWithJet(int ijet);

        // Lepton module
        class LeptonModule: public RooUtil::Module
        {
            public:
                hwwBabyMaker* babymaker;
                LeptonModule(hwwBabyMaker* parent) { babymaker = parent; }
                virtual void AddOutput();
                virtual void FillOutput();
        };

        // FatJet module
        class FatJetModule: public RooUtil::Module
        {
            public:
                hwwBabyMaker* babymaker;
                FatJetModule(hwwBabyMaker* parent) { babymaker = parent; }
                virtual void AddOutput();
                virtual void FillOutput();
        };

        // Trigger module
        class TriggerModule: public RooUtil::Module
        {
            public:
                hwwBabyMaker* babymaker;
                TriggerModule(hwwBabyMaker* parent) { babymaker = parent; }
                virtual void AddOutput();
                virtual void FillOutput();
        };

};

#endif
