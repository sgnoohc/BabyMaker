#!/bin/env python

import os
import sys
import ROOT
from QFramework import TQSampleFolder, TQXSecParser, TQCut, TQAnalysisSampleVisitor, TQSampleInitializer, TQCutflowAnalysisJob, TQCutflowPrinter, TQHistoMakerAnalysisJob, TQHWWPlotter, TQEventlistAnalysisJob
from qutils import *

def main(index):

    #
    #
    # Redirect stdout to log the parallel jobs
    #
    #
    #sys.stdout = open("." + str(os.getpid()) + ".out", "w", buffering=0)

    #
    #
    # Create the master TQSampleFolder
    #
    #
    samples = TQSampleFolder("samples")

    #
    #
    # Connect input baby ntuple
    #
    #
    connectNtuples(samples, "samples.cfg", "/nfs-7/userdata/phchang/WWW_babies/WWW_v1.0.23/skim/", "<0")

    #
    #
    # Define cuts
    #
    #
    PreselCuts = [
    ["1"                                          , "evt_scale1fb"                  ] ,
    ["1"                                          , "purewgt"                       ] ,
    ["1"                                          , "{$(usefakeweight)?ffwgt:35.9}" ] ,
    ["Flag_AllEventFilters"                       , "1"                             ] ,
    ["vetophoton==0"                              , "1"                             ] ,
    ["MllSS > 10"                                 , "1"                             ] ,
    ]
    PreselCutExpr, PreselWgtExpr = combexpr(PreselCuts)

    tqcuts = {}
    tqcuts["Presel"]         = TQCut("Presel", "Presel", PreselCutExpr, PreselWgtExpr)

    tqcuts["CutDilep"]       = TQCut("CutDilep"       , "CutDilep"               , "{$(usefakeweight)?(nVlep==2)*(nLlep==2)*(nTlep==1):(nVlep==2)*(nLlep==2)*(nTlep==2)}" , "{$(usefakeweight)?1.:lepsf}")
    tqcuts["CutSSee"]        = TQCut("CutSSee"        , "SSee:"                  , "(passSSee)*(mc_HLT_DoubleEl_DZ_2==1)"                                                 , "trigsf")
    tqcuts["CutSSem"]        = TQCut("CutSSem"        , "SSem:"                  , "(passSSem)*(mc_HLT_MuEG==1)"                                                          , "trigsf")
    tqcuts["CutSSmm"]        = TQCut("CutSSmm"        , "SSmm:"                  , "(passSSmm)*(mc_HLT_DoubleMu==1)"                                                      , "trigsf")
    tqcuts["CutSSeeNj2"]     = TQCut("CutSSeeNj2"     , "SSee: 1. n_{j} #geq 2"  , "nj30>= 2"                                                                             , "1")
    tqcuts["CutSSemNj2"]     = TQCut("CutSSemNj2"     , "SSem: 1. n_{j} #geq 2"  , "nj30>= 2"                                                                             , "1")
    tqcuts["CutSSmmNj2"]     = TQCut("CutSSmmNj2"     , "SSmm: 1. n_{j} #geq 2"  , "nj30>= 2"                                                                             , "1")
    tqcuts["CutSSeeNb0"]     = TQCut("CutSSeeNb0"     , "SSee: 2. n_{b} = 0"     , "nb==0"                                                                                , "weight_btagsf")
    tqcuts["CutSSemNb0"]     = TQCut("CutSSemNb0"     , "SSem: 2. n_{b} = 0"     , "nb==0"                                                                                , "weight_btagsf")
    tqcuts["CutSSmmNb0"]     = TQCut("CutSSmmNb0"     , "SSmm: 2. n_{b} = 0"     , "nb==0"                                                                                , "weight_btagsf")
    tqcuts["CutSSeeMjjW"]    = TQCut("CutSSeeMjjW"    , "SSee: 3. |Mjj-80| < 15" , "abs(Mjj-80.)<15."                                                                     , "1")
    tqcuts["CutSSemMjjW"]    = TQCut("CutSSemMjjW"    , "SSem: 3. |Mjj-80| < 15" , "abs(Mjj-80.)<15."                                                                     , "1")
    tqcuts["CutSSmmMjjW"]    = TQCut("CutSSmmMjjW"    , "SSmm: 3. |Mjj-80| < 15" , "abs(Mjj-80.)<15."                                                                     , "1")
    tqcuts["CutSSeeMjjL"]    = TQCut("CutSSeeMjjL"    , "SSee: 4. MjjL < 400"    , "MjjL<400."                                                                            , "1")
    tqcuts["CutSSemMjjL"]    = TQCut("CutSSemMjjL"    , "SSem: 4. MjjL < 400"    , "MjjL<400."                                                                            , "1")
    tqcuts["CutSSmmMjjL"]    = TQCut("CutSSmmMjjL"    , "SSmm: 4. MjjL < 400"    , "MjjL<400."                                                                            , "1")
    tqcuts["CutSSeeDetajjL"] = TQCut("CutSSeeDetajjL" , "SSee: 5. DetajjL < 1.5" , "DetajjL<1.5"                                                                          , "1")
    tqcuts["CutSSemDetajjL"] = TQCut("CutSSemDetajjL" , "SSem: 5. DetajjL < 1.5" , "DetajjL<1.5"                                                                          , "1")
    tqcuts["CutSSmmDetajjL"] = TQCut("CutSSmmDetajjL" , "SSmm: 5. DetajjL < 1.5" , "DetajjL<1.5"                                                                          , "1")
    tqcuts["CutSSeeMET"]     = TQCut("CutSSeeMET"     , "SSee: 6. MET > 60"      , "met_pt>60."                                                                           , "1")
    tqcuts["CutSSemMET"]     = TQCut("CutSSemMET"     , "SSem: 6. MET > 60"      , "met_pt>60."                                                                           , "1")
    tqcuts["CutSSmmMET"]     = TQCut("CutSSmmMET"     , "SSmm: 6. MET > 0"       , "1."                                                                                   , "1")
    tqcuts["CutSSeeMllSS"]   = TQCut("CutSSeeMllSS"   , "SSee: 7. MllSS > 40"    , "MllSS>60."                                                                            , "1")
    tqcuts["CutSSemMllSS"]   = TQCut("CutSSemMllSS"   , "SSem: 7. MllSS > 40"    , "MllSS>60."                                                                            , "1")
    tqcuts["CutSSmmMllSS"]   = TQCut("CutSSmmMllSS"   , "SSmm: 7. MllSS > 40"    , "MllSS>40."                                                                            , "1")

    tqcuts["CutSSeeZeeVt"] = TQCut("CutSSeeZeeVt", "SSee0: Z veto" , "abs(MllSS-91.1876)>10.", "1");
    tqcuts["CutSSemMTmax"] = TQCut("CutSSemMTmax", "SSem0: MTmax" , "MTmax>90.", "1");

    tqcuts["CutTrilep"]        = TQCut("CutTrilep"        , "CutTrilep"                , "{$(usefakeweight)?(nVlep==3)*(nLlep==3)*(nTlep==2):(nVlep==3)*(nLlep==3)*(nTlep==3)}" , "{$(usefakeweight)?1.:lepsf}")
    tqcuts["CutSSWZee"]        = TQCut("CutSSWZee"        , "SSWZee: "                 , "(passSSee)*(mc_HLT_DoubleEl_DZ_2==1)"                                                 , "trigsf")
    tqcuts["CutSSWZem"]        = TQCut("CutSSWZem"        , "SSWZem: "                 , "(passSSem)*(mc_HLT_MuEG==1)"                                                          , "trigsf")
    tqcuts["CutSSWZmm"]        = TQCut("CutSSWZmm"        , "SSWZmm: "                 , "(passSSmm)*(mc_HLT_DoubleMu==1)"                                                      , "trigsf")
    tqcuts["CutSSWZeeNj2"]     = TQCut("CutSSWZeeNj2"     , "SSWZee: 1. n_{j} #geq 2"  , "nj30>= 2"                                                                             , "1")
    tqcuts["CutSSWZemNj2"]     = TQCut("CutSSWZemNj2"     , "SSWZem: 1. n_{j} #geq 2"  , "nj30>= 2"                                                                             , "1")
    tqcuts["CutSSWZmmNj2"]     = TQCut("CutSSWZmmNj2"     , "SSWZmm: 1. n_{j} #geq 2"  , "nj30>= 2"                                                                             , "1")
    tqcuts["CutSSWZeeNb0"]     = TQCut("CutSSWZeeNb0"     , "SSWZee: 2. n_{b} = 0"     , "nb==0"                                                                                , "weight_btagsf")
    tqcuts["CutSSWZemNb0"]     = TQCut("CutSSWZemNb0"     , "SSWZem: 2. n_{b} = 0"     , "nb==0"                                                                                , "weight_btagsf")
    tqcuts["CutSSWZmmNb0"]     = TQCut("CutSSWZmmNb0"     , "SSWZmm: 2. n_{b} = 0"     , "nb==0"                                                                                , "weight_btagsf")
    tqcuts["CutSSWZeeMjjW"]    = TQCut("CutSSWZeeMjjW"    , "SSWZee: 3. |Mjj-80| < 15" , "abs(Mjj-80.)<15."                                                                     , "1")
    tqcuts["CutSSWZemMjjW"]    = TQCut("CutSSWZemMjjW"    , "SSWZem: 3. |Mjj-80| < 15" , "abs(Mjj-80.)<15."                                                                     , "1")
    tqcuts["CutSSWZmmMjjW"]    = TQCut("CutSSWZmmMjjW"    , "SSWZmm: 3. |Mjj-80| < 15" , "abs(Mjj-80.)<15."                                                                     , "1")
    tqcuts["CutSSWZeeMjjL"]    = TQCut("CutSSWZeeMjjL"    , "SSWZee: 4. MjjL < 400"    , "MjjL<400."                                                                            , "1")
    tqcuts["CutSSWZemMjjL"]    = TQCut("CutSSWZemMjjL"    , "SSWZem: 4. MjjL < 400"    , "MjjL<400."                                                                            , "1")
    tqcuts["CutSSWZmmMjjL"]    = TQCut("CutSSWZmmMjjL"    , "SSWZmm: 4. MjjL < 400"    , "MjjL<400."                                                                            , "1")
    tqcuts["CutSSWZeeDetajjL"] = TQCut("CutSSWZeeDetajjL" , "SSWZee: 5. DetajjL < 1.5" , "DetajjL<1.5"                                                                          , "1")
    tqcuts["CutSSWZemDetajjL"] = TQCut("CutSSWZemDetajjL" , "SSWZem: 5. DetajjL < 1.5" , "DetajjL<1.5"                                                                          , "1")
    tqcuts["CutSSWZmmDetajjL"] = TQCut("CutSSWZmmDetajjL" , "SSWZmm: 5. DetajjL < 1.5" , "DetajjL<1.5"                                                                          , "1")
    tqcuts["CutSSWZeeMET"]     = TQCut("CutSSWZeeMET"     , "SSWZee: 6. MET > 60"      , "met_pt>60."                                                                           , "1")
    tqcuts["CutSSWZemMET"]     = TQCut("CutSSWZemMET"     , "SSWZem: 6. MET > 60"      , "met_pt>60."                                                                           , "1")
    tqcuts["CutSSWZmmMET"]     = TQCut("CutSSWZmmMET"     , "SSWZmm: 6. MET > 0"       , "1."                                                                                   , "1")
    tqcuts["CutSSWZeeMllSS"]   = TQCut("CutSSWZeeMllSS"   , "SSWZee: 7. MllSS > 40"    , "MllSS>60."                                                                            , "1")
    tqcuts["CutSSWZemMllSS"]   = TQCut("CutSSWZemMllSS"   , "SSWZem: 7. MllSS > 40"    , "MllSS>60."                                                                            , "1")
    tqcuts["CutSSWZmmMllSS"]   = TQCut("CutSSWZmmMllSS"   , "SSWZmm: 7. MllSS > 40"    , "MllSS>40."                                                                            , "1")

    tqcuts["CutSSWZeeZeeVt"] = TQCut("CutSSWZeeZeeVt", "SSWZee: 0. Z veto" , "abs(MllSS-91.1876)>10.", "1");
    tqcuts["CutSSWZemMTmax"] = TQCut("CutSSWZemMTmax", "SSWZem: 0. MTmax" , "MTmax>90.", "1");

    cuts = tqcuts["Presel"]
    tqcuts["Presel"].addCut(tqcuts["CutDilep"])
    tqcuts["CutDilep"].addCut(tqcuts["CutSSeeZeeVt"])
    tqcuts["CutDilep"].addCut(tqcuts["CutSSemMTmax"])
    tqcuts["CutSSeeZeeVt"].addCut(tqcuts["CutSSee"])
    tqcuts["CutSSemMTmax"].addCut(tqcuts["CutSSem"])
    tqcuts["CutDilep"].addCut(tqcuts["CutSSmm"])
    tqcuts["CutSSee"].addCut(tqcuts["CutSSeeNj2"])
    tqcuts["CutSSem"].addCut(tqcuts["CutSSemNj2"])
    tqcuts["CutSSmm"].addCut(tqcuts["CutSSmmNj2"])
    tqcuts["CutSSeeNj2"].addCut(tqcuts["CutSSeeNb0"])
    tqcuts["CutSSemNj2"].addCut(tqcuts["CutSSemNb0"])
    tqcuts["CutSSmmNj2"].addCut(tqcuts["CutSSmmNb0"])
    tqcuts["CutSSeeNb0"].addCut(tqcuts["CutSSeeMjjW"])
    tqcuts["CutSSemNb0"].addCut(tqcuts["CutSSemMjjW"])
    tqcuts["CutSSmmNb0"].addCut(tqcuts["CutSSmmMjjW"])
    tqcuts["CutSSeeMjjW"].addCut(tqcuts["CutSSeeMjjL"])
    tqcuts["CutSSemMjjW"].addCut(tqcuts["CutSSemMjjL"])
    tqcuts["CutSSmmMjjW"].addCut(tqcuts["CutSSmmMjjL"])
    tqcuts["CutSSeeMjjL"].addCut(tqcuts["CutSSeeDetajjL"])
    tqcuts["CutSSemMjjL"].addCut(tqcuts["CutSSemDetajjL"])
    tqcuts["CutSSmmMjjL"].addCut(tqcuts["CutSSmmDetajjL"])
    tqcuts["CutSSeeDetajjL"].addCut(tqcuts["CutSSeeMET"])
    tqcuts["CutSSemDetajjL"].addCut(tqcuts["CutSSemMET"])
    tqcuts["CutSSmmDetajjL"].addCut(tqcuts["CutSSmmMET"])
    tqcuts["CutSSeeMET"].addCut(tqcuts["CutSSeeMllSS"])
    tqcuts["CutSSemMET"].addCut(tqcuts["CutSSemMllSS"])
    tqcuts["CutSSmmMET"].addCut(tqcuts["CutSSmmMllSS"])

    tqcuts["Presel"].addCut(tqcuts["CutTrilep"])
    tqcuts["CutTrilep"].addCut(tqcuts["CutSSWZeeZeeVt"])
    tqcuts["CutTrilep"].addCut(tqcuts["CutSSWZemMTmax"])
    tqcuts["CutSSWZeeZeeVt"].addCut(tqcuts["CutSSWZee"])
    tqcuts["CutSSWZemMTmax"].addCut(tqcuts["CutSSWZem"])
    tqcuts["CutTrilep"].addCut(tqcuts["CutSSWZmm"])
    tqcuts["CutSSWZee"].addCut(tqcuts["CutSSWZeeNj2"])
    tqcuts["CutSSWZem"].addCut(tqcuts["CutSSWZemNj2"])
    tqcuts["CutSSWZmm"].addCut(tqcuts["CutSSWZmmNj2"])
    tqcuts["CutSSWZeeNj2"].addCut(tqcuts["CutSSWZeeNb0"])
    tqcuts["CutSSWZemNj2"].addCut(tqcuts["CutSSWZemNb0"])
    tqcuts["CutSSWZmmNj2"].addCut(tqcuts["CutSSWZmmNb0"])
    tqcuts["CutSSWZeeNb0"].addCut(tqcuts["CutSSWZeeMjjW"])
    tqcuts["CutSSWZemNb0"].addCut(tqcuts["CutSSWZemMjjW"])
    tqcuts["CutSSWZmmNb0"].addCut(tqcuts["CutSSWZmmMjjW"])
    tqcuts["CutSSWZeeMjjW"].addCut(tqcuts["CutSSWZeeMjjL"])
    tqcuts["CutSSWZemMjjW"].addCut(tqcuts["CutSSWZemMjjL"])
    tqcuts["CutSSWZmmMjjW"].addCut(tqcuts["CutSSWZmmMjjL"])
    tqcuts["CutSSWZeeMjjL"].addCut(tqcuts["CutSSWZeeDetajjL"])
    tqcuts["CutSSWZemMjjL"].addCut(tqcuts["CutSSWZemDetajjL"])
    tqcuts["CutSSWZmmMjjL"].addCut(tqcuts["CutSSWZmmDetajjL"])
    tqcuts["CutSSWZeeDetajjL"].addCut(tqcuts["CutSSWZeeMET"])
    tqcuts["CutSSWZemDetajjL"].addCut(tqcuts["CutSSWZemMET"])
    tqcuts["CutSSWZmmDetajjL"].addCut(tqcuts["CutSSWZmmMET"])
    tqcuts["CutSSWZeeMET"].addCut(tqcuts["CutSSWZeeMllSS"])
    tqcuts["CutSSWZemMET"].addCut(tqcuts["CutSSWZemMllSS"])
    tqcuts["CutSSWZmmMET"].addCut(tqcuts["CutSSWZmmMllSS"])

    #
    #
    # Define histograms
    #
    #
    f = open(".histo.os.{}.cfg".format(index), "w")
    f.write("""
    TH1F('MllSS' , '' , 180 , 0. , 300.) << (MllSS : '\#it{m}_{ll} [GeV]');
    @*/*: MllSS;

    TH1F('MllZ' , '' , 180 , 60. , 120.) << (MllSS : '\#it{m}_{ll} [GeV]');
    @*/*: MllZ;

    TH1F('MllZZoom' , '' , 180 , 80. , 100.) << (MllSS : '\#it{m}_{ll} [GeV]');
    @*/*: MllZZoom;

    TH1F('nvtx' , '' , 60 , 0. , 60. ) << (nVert : 'Nvtx');
    @*/*: nvtx;

    TH1F('Mjj' , '' , 180 , 0. , 300.) << (Mjj : '\#it{m}_{jj} [GeV]');
    @*/*: Mjj;

    TH1F('MET' , '' , 180 , 0. , 180.) << (met_pt : 'MET [GeV]');
    @*/*: MET;

    TH2F('lep0_pt_vs_eta' , '' , {0, 0.9, 1.6, 1.9, 2.4}, {20, 30, 40, 50, 60, 70, 150, 2000} ) << (lep_eta[0] : '\#eta_{lead-lep}', lep_pt[0] : '\#it{p}_{T, lead-lep} [GeV]');
    @*/*: lep0_pt_vs_eta;

    TH2F('lep1_pt_vs_eta' , '' , {0, 0.9, 1.6, 1.9, 2.4}, {20, 30, 40, 50, 60, 70, 150, 2000} ) << (lep_eta[1] : '\#eta_{trail-lep}', lep_pt[1] : '\#it{p}_{T, trail-lep} [GeV]');
    @*/*: lep1_pt_vs_eta;

    TH1F('lep_pt0' , '' , 180 , 0. , 250 ) << (lep_pt[0] : '\#it{p}_{T, lead-lep} [GeV]');
    @*/*: lep_pt0;

    TH1F('lep_pt1' , '' , 180 , 0. , 150 ) << (lep_pt[1] : '\#it{p}_{T, trail-lep} [GeV]');
    @*/*: lep_pt1;

    #TH1F('lep_pt2' , '' , 180 , 0. , 150 ) << (lep_pt[2] : '\#it{p}_{T, trail-lep} [GeV]');
    #@*/*: lep_pt1;

    TH1F('lep_eta0' , '' , 180 , -2.5 , 2.5 ) << (lep_eta[0] : '\#eta_{lead-lep}');
    @*/*: lep_eta0;

    TH1F('lep_eta1' , '' , 180 , -2.5 , 2.5 ) << (lep_eta[1] : '\#eta_{trail-lep}');
    @*/*: lep_eta1;

    TH1F('lep_phi0' , '' , 180 , -3.1416 , 3.1416 ) << (lep_phi[0] : '\#phi_{lead-lep}');
    @*/*: lep_phi0;

    TH1F('lep_phi1' , '' , 180 , -3.1416, 3.1416 ) << (lep_phi[1] : '\#phi_{trail-lep}');
    @*/*: lep_phi1;

    TH1F('lep_relIso03EAv2Lep0' , '' , 180 , 0.6 , 1.2 ) << (lep_relIso03EAv2Lep[0] : 'I_{R=0.3,EA,Lep, lead-lep}');
    @*/*: lep_relIso03EAv2Lep0;

    TH1F('lep_relIso03EAv2Lep1' , '' , 180 , 0.6 , 1.2 ) << (lep_relIso03EAv2Lep[1] : 'I_{R=0.3,EA,Lep, trail-lep}');
    @*/*: lep_relIso03EAv2Lep1;

    TH1F('nj' , '' , 7 , 0. , 7. ) << (nj : 'N_{jet}');
    @*/*: nj;

    TH1F('nj30' , '' , 7 , 0. , 7. ) << (nj30 : 'N_{jet}');
    @*/*: nj30;

    TH1F('nb' , '' , 5 , 0. , 5. ) << (nb : 'N_{b-jet}');
    @*/*: nb;

    #TH1F('jets_pt0' , '' , 180 , 0. , 250 ) << (jets_p4[0].pt() : '\#it{p}_{T, lead-jet} [GeV]');
    #@*/*: jets_pt0;
    #
    #TH1F('jets_pt1' , '' , 180 , 0. , 150 ) << (jets_p4[1].pt() : '\#it{p}_{T, trail-jet} [GeV]');
    #@*/*: jets_pt1;
    #
    #TH1F('jets_eta0' , '' , 180 , -5.0 , 5.0 ) << (jets_p4[0].eta() : '\#eta_{lead-jet}');
    #@*/*: jets_eta0;
    #
    #TH1F('jets_eta1' , '' , 180 , -5.0 , 5.0 ) << (jets_p4[1].eta() : '\#eta_{trail-jet}');
    #@*/*: jets_eta1;
    #
    #TH1F('jets_phi0' , '' , 180 , -3.1416, 3.1416 ) << (jets_p4[0].phi() : '\#phi_{lead-jet}');
    #@*/*: jets_phi0;
    #
    #TH1F('jets_phi1' , '' , 180 , -3.1416, 3.1416 ) << (jets_p4[1].phi() : '\#phi_{trail-jet}');
    #@*/*: jets_phi1;

    """)
    f.close()

    #
    #
    # Book Analysis Jobs (Histogramming, Cutflow, Event lists)
    #
    #
    histojob = TQHistoMakerAnalysisJob()
    histojob.importJobsFromTextFiles(".histo.os.{}.cfg".format(index), cuts, "*", True if index < 0 else False)

    # Analysis jobs
    cutflowjob = TQCutflowAnalysisJob("cutflow")
    cuts.addAnalysisJob(cutflowjob, "*")

    # Eventlist jobs
    #eventlistjob = TQEventlistAnalysisJob("eventlist")
    #eventlistjob.importJobsFromTextFiles("eventlist.cfg", cuts, "*", True)

    # Print cuts and numebr of booked analysis jobs for debugging purpose
    if index < 0:
        cuts.printCut("trd")

    #
    #
    # Loop over the samples
    #
    #

    # setup a visitor to actually loop over ROOT files
    vis = TQAnalysisSampleVisitor(cuts,True)

    if index >= 0:

        # Get all sample lists
        sample_names, sample_full_names = getSampleLists(samples)

        # Select the job based on the index
        sample_name = sample_names[index]
        sample_full_name = sample_full_names[sample_name]

        # Run the job!
        samples.visitSampleFolders(vis, "/*/{}".format(sample_full_name))

        # Write the output histograms and cutflow cut values and etc.
        samples.writeToFile(".qss_output_{}.root".format(sample_name), True)

    else:
        # Run the job!
        samples.visitSampleFolders(vis)

        # Write the output histograms and cutflow cut values and etc.
        samples.writeToFile("output.root", True)

if __name__ == "__main__":

    main(-1)

    #if len(sys.argv) < 2:

    #    import multiprocessing

    #    jobs = []
    #    for i in range(55):
    #        p = multiprocessing.Process(target=main, args=(i,))
    #        jobs.append(p)
    #        p.start()

    #    for index, job in enumerate(jobs):
    #        #print "{} jobs done out of {}".format(index, len(jobs))
    #        job.join()

    #    os.system("rooutil/qframework/share/tqmerge -o output.root -t analysis .qss_output_*.root")

    #else:

    #    main(int(sys.argv[1]))
#
