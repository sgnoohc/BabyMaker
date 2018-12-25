#ifndef hwwBabyMaker_h
#define hwwBabyMaker_h

#include "babyMaker.h"

class hwwBabyMaker: public babyMaker
{
    public:
        hwwBabyMaker();
        ~hwwBabyMaker();

        RooUtil::Processor* processor;

        virtual void ProcessElectrons();
        virtual void ProcessMuons();
        virtual bool PassSelection();

        virtual void AddOutput();
        virtual void FillOutput();

        static bool isPt10Electron(int idx);
        static bool isPt10Muon(int idx);
        bool isLeptonOverlappingWithJet(int ijet);

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

        //__________________________________________________________________
        // HWWlvjj Truth Module
        class HWWlvjjTruthModule: public RooUtil::Module
        {
            public:
                hwwBabyMaker* babymaker;
                HWWlvjjTruthModule(hwwBabyMaker* parent) { babymaker = parent; }
                virtual void AddOutput();
                virtual void FillOutput();
                void AddOutput_ggHToWWToLNuQQ();
                void AddOutput_HWW();
                void FillOutput_ggHToWWToLNuQQ();
                void FillOutput_HWW();
        };

        //__________________________________________________________________
        // Higgs Reconstruction Module
        class HiggsRecoModule: public RooUtil::Module
        {
            public:
                hwwBabyMaker* babymaker;
                HiggsRecoModule(hwwBabyMaker* parent) { babymaker = parent; }
                virtual void AddOutput();
                virtual void FillOutput();
                std::tuple<LV, int> SelectLepton(LV ref, float dphithresh=TMath::Pi()/2.);
                std::tuple<LV, int> SelectFatJet(LV ref, float dphithresh=TMath::Pi()/2.);
        };

        //__________________________________________________________________
        // Recoil module
        class RecoilModule: public RooUtil::Module
        {
            public:
                hwwBabyMaker* babymaker;
                TString suffix;
                TString jettype;
                float threshold;
                TString bname;
                TString bname_prefix;
                RecoilModule(hwwBabyMaker* parent, TString sfx="", TString jt="jets_p4", float thr=(TMath::Pi() * 2./4.))
                {
                    babymaker = parent;
                    suffix = sfx;
                    jettype = jt;
                    threshold = thr;
                    bname_prefix = TString::Format("Recoil%s", suffix.Data());
                    bname = TString::Format("Recoil%s_p4", suffix.Data());
                }
                virtual void AddOutput();
                virtual void FillOutput();
                void AddOutput_v1();
                void AddOutput_v2();
                void FillOutput_v1();
                void FillOutput_v2();
        };

};

#endif
