#ifndef hwwBabyMaker_h
#define hwwBabyMaker_h

#include "babyMaker.h"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/contrib/SoftDrop.hh"
#include "fastjet/contrib/Nsubjettiness.hh"

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

        void ReClusterFatJets();

        class ReCluster
        {
            public:
                LV J_p4;
                LV J_SD_p4;
                LV q0_p4;
                LV q1_p4;
                fastjet::PseudoJet J_pj;
                fastjet::PseudoJet J_SD_pj;
                fastjet::PseudoJet q0_pj;
                fastjet::PseudoJet q1_pj;
                float tau1;
                float tau2;
                float tau3;
                float tau31;
                float tau32;
                float tau21;
                float SD_tau1;
                float SD_tau2;
                float SD_tau3;
                float SD_tau31;
                float SD_tau32;
                float SD_tau21;
                bool found_jet;
                void ReClusterFatJets(LV&);
                static LV getLV(fastjet::PseudoJet&);

        };

        ReCluster recl;

        virtual void AddOutput();
        virtual void FillOutput();

        static bool isPt20Electron(int idx);
        static bool isPt20Muon(int idx);
        static bool isPt10Electron(int idx);
        static bool isPt10Muon(int idx);
        bool isLeptonOverlappingWithJet(int ijet);

};

#include "modules/EventModule.h"
#include "modules/FatJetModule.h"
#include "modules/GenPartModule.h"
#include "modules/HWWlvjjTruthModule.h"
#include "modules/HiggsRecoModule.h"
#include "modules/JetModule.h"
#include "modules/LeptonModule.h"
#include "modules/METModule.h"
#include "modules/TriggerModule.h"



#endif
