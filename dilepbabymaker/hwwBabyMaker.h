#ifndef hwwBabyMaker_h
#define hwwBabyMaker_h

#include "babyMaker.h"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/contrib/SoftDrop.hh"
#include "fastjet/contrib/Nsubjettiness.hh"
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/GhostedAreaSpec.hh"

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

        virtual void AddOutput();
        virtual void FillOutput();

        static bool isPt25Electron(int idx);
        static bool isPt25Muon(int idx);
        static bool isPt10Electron(int idx);
        static bool isPt10Muon(int idx);
        bool isLeptonOverlappingWithJet(int ijet);

};

#include "modules/TriggerModule.h"
#include "modules/GenPartModule.h"
#include "modules/EventModule.h"
#include "modules/LeptonModule.h"
#include "modules/METModule.h"
#include "modules/FatJetModule.h"
#include "modules/HiggsRecoModule.h"
#include "modules/JetModule.h"
#include "modules/HWWlvjjTruthModule.h"
#include "modules/TTBarModule.h"

#include "modules/ReCluster.h"


#endif
