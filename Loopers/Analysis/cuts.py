#!/bin/env python

import os
import sys
import ROOT
from QFramework import TQSampleFolder, TQXSecParser, TQCut, TQAnalysisSampleVisitor, TQSampleInitializer, TQCutflowAnalysisJob, TQCutflowPrinter, TQHistoMakerAnalysisJob, TQHWWPlotter, TQEventlistAnalysisJob
from rooutil.qutils import *

def getWWWAnalysisCuts(lepsfvar_suffix="",trigsfvar_suffix="",jecvar_suffix="",btagsfvar_suffix=""): #define _up _dn etc.

    #
    #
    # Define cuts
    #
    #
    PreselCuts = [
    ["1"                                          , "evt_scale1fb"                  ] ,
    ["1"                                          , "purewgt"                       ] ,
    ["1"                                          , "{$(usefakeweight)?ffwgt:35.9}" ] , # ffwgt is wrong here (it is not fr / fr - 1)
    ["firstgoodvertex==0"                         , "1"                             ] ,
    ["Flag_AllEventFilters"                       , "1"                             ] ,
    ["vetophoton==0"                              , "1"                             ] ,
    ["MllSS > 20"                                 , "1"                             ] ,
    ["evt_passgoodrunlist"                        , "1"                               ] ,
    ]
    PreselCutExpr, PreselWgtExpr = combexpr(PreselCuts)

    tqcuts = {}
    tqcuts["Presel"]         = TQCut("Presel", "Presel", PreselCutExpr, PreselWgtExpr)

    tqcuts["CutDilep"]       = TQCut("CutDilep"       , "CutDilep"               , "{$(usefakeweight)?(nVlep==2)*(nLlep==2)*(nTlep==1):(nVlep==2)*(nLlep==2)*(nTlep==2)}" , "{$(usefakeweight)?1.:lepsf"+lepsfvar_suffix+"}")
    tqcuts["CutSSee"]        = TQCut("CutSSee"        , "SSee:"                  , "(passSSee)*(mc_HLT_DoubleEl_DZ_2==1)"                                                 , "trigsf"+trigsfvar_suffix)
    tqcuts["CutSSem"]        = TQCut("CutSSem"        , "SSem:"                  , "(passSSem)*(mc_HLT_MuEG==1)"                                                          , "trigsf"+trigsfvar_suffix)
    tqcuts["CutSSmm"]        = TQCut("CutSSmm"        , "SSmm:"                  , "(passSSmm)*(mc_HLT_DoubleMu==1)"                                                      , "trigsf"+trigsfvar_suffix)
    tqcuts["CutSSeeNj2"]     = TQCut("CutSSeeNj2"     , "SSee: 1. n_{j} #geq 2"  , "nj30"+jecvar_suffix+">= 2"                                                            , "1")
    tqcuts["CutSSemNj2"]     = TQCut("CutSSemNj2"     , "SSem: 1. n_{j} #geq 2"  , "nj30"+jecvar_suffix+">= 2"                                                            , "1")
    tqcuts["CutSSmmNj2"]     = TQCut("CutSSmmNj2"     , "SSmm: 1. n_{j} #geq 2"  , "nj30"+jecvar_suffix+">= 2"                                                            , "1")
    tqcuts["CutSSeeNb0"]     = TQCut("CutSSeeNb0"     , "SSee: 2. n_{b} = 0"     , "nb"+jecvar_suffix+"==0"                                                               , "weight_btagsf"+btagsfvar_suffix)
    tqcuts["CutSSemNb0"]     = TQCut("CutSSemNb0"     , "SSem: 2. n_{b} = 0"     , "nb"+jecvar_suffix+"==0"                                                               , "weight_btagsf"+btagsfvar_suffix)
    tqcuts["CutSSmmNb0"]     = TQCut("CutSSmmNb0"     , "SSmm: 2. n_{b} = 0"     , "nb"+jecvar_suffix+"==0"                                                               , "weight_btagsf"+btagsfvar_suffix)
    tqcuts["CutSSeeMjjW"]    = TQCut("CutSSeeMjjW"    , "SSee: 3. |Mjj-80| < 15" , "abs(Mjj"+jecvar_suffix+"-80.)<15."                                                    , "1")
    tqcuts["CutSSemMjjW"]    = TQCut("CutSSemMjjW"    , "SSem: 3. |Mjj-80| < 15" , "abs(Mjj"+jecvar_suffix+"-80.)<15."                                                    , "1")
    tqcuts["CutSSmmMjjW"]    = TQCut("CutSSmmMjjW"    , "SSmm: 3. |Mjj-80| < 15" , "abs(Mjj"+jecvar_suffix+"-80.)<15."                                                    , "1")
#    tqcuts["CutSSeeMjjL"]    = TQCut("CutSSeeMjjL"    , "SSee: 4. MjjL < 400"    , "MjjL<400."                                                                            , "1")
#    tqcuts["CutSSemMjjL"]    = TQCut("CutSSemMjjL"    , "SSem: 4. MjjL < 400"    , "MjjL<400."                                                                            , "1")
#    tqcuts["CutSSmmMjjL"]    = TQCut("CutSSmmMjjL"    , "SSmm: 4. MjjL < 400"    , "MjjL<400."                                                                            , "1")
#    tqcuts["CutSSeeDetajjL"] = TQCut("CutSSeeDetajjL" , "SSee: 5. DetajjL < 1.5" , "DetajjL<1.5"                                                                          , "1")
#    tqcuts["CutSSemDetajjL"] = TQCut("CutSSemDetajjL" , "SSem: 5. DetajjL < 1.5" , "DetajjL<1.5"                                                                          , "1")
#    tqcuts["CutSSmmDetajjL"] = TQCut("CutSSmmDetajjL" , "SSmm: 5. DetajjL < 1.5" , "DetajjL<1.5"                                                                          , "1")
    tqcuts["CutSSeeMjjL"]    = TQCut("CutSSeeMjjL"    , "SSee: 4. MjjL < 400"    , "1"                                                                                    , "1")
    tqcuts["CutSSemMjjL"]    = TQCut("CutSSemMjjL"    , "SSem: 4. MjjL < 400"    , "1"                                                                                    , "1")
    tqcuts["CutSSmmMjjL"]    = TQCut("CutSSmmMjjL"    , "SSmm: 4. MjjL < 400"    , "1"                                                                                    , "1")
    tqcuts["CutSSeeDetajjL"] = TQCut("CutSSeeDetajjL" , "SSee: 5. DetajjL < 1.5" , "1"                                                                                    , "1")
    tqcuts["CutSSemDetajjL"] = TQCut("CutSSemDetajjL" , "SSem: 5. DetajjL < 1.5" , "1"                                                                                    , "1")
    tqcuts["CutSSmmDetajjL"] = TQCut("CutSSmmDetajjL" , "SSmm: 5. DetajjL < 1.5" , "1"                                                                                    , "1")
    tqcuts["CutSSeeMET"]     = TQCut("CutSSeeMET"     , "SSee: 6. MET > 60"      , "met_pt>60."                                                                           , "1")
    tqcuts["CutSSemMET"]     = TQCut("CutSSemMET"     , "SSem: 6. MET > 60"      , "met_pt>60."                                                                           , "1")
    tqcuts["CutSSmmMET"]     = TQCut("CutSSmmMET"     , "SSmm: 6. MET > 0"       , "1."                                                                                   , "1")
    tqcuts["CutSSeeMllSS"]   = TQCut("CutSSeeMllSS"   , "SSee: 7. MllSS > 40"    , "MllSS>60."                                                                            , "1")
    tqcuts["CutSSemMllSS"]   = TQCut("CutSSemMllSS"   , "SSem: 7. MllSS > 40"    , "MllSS>60."                                                                            , "1")
    tqcuts["CutSSmmMllSS"]   = TQCut("CutSSmmMllSS"   , "SSmm: 7. MllSS > 40"    , "MllSS>40."                                                                            , "1")

    tqcuts["CutSSeeZeeVt"] = TQCut("CutSSeeZeeVt", "SSee0: Z veto" , "abs(MllSS-91.1876)>10.", "1");
    tqcuts["CutSSemMTmax"] = TQCut("CutSSemMTmax", "SSem0: MTmax" , "MTmax>90.", "1");

    tqcuts["CutTrilep"]        = TQCut("CutTrilep"        , "CutTrilep"                , "{$(usefakeweight)?(nVlep==3)*(nLlep==3)*(nTlep==2):(nVlep==3)*(nLlep==3)*(nTlep==3)}" , "{$(usefakeweight)?1.:lepsf"+lepsfvar_suffix+"}")
    tqcuts["CutSSWZee"]        = TQCut("CutSSWZee"        , "SSWZee: "                 , "(passSSee)*(mc_HLT_DoubleEl_DZ_2==1)"                                                 , "trigsf"+trigsfvar_suffix)
    tqcuts["CutSSWZem"]        = TQCut("CutSSWZem"        , "SSWZem: "                 , "(passSSem)*(mc_HLT_MuEG==1)"                                                          , "trigsf"+trigsfvar_suffix)
    tqcuts["CutSSWZmm"]        = TQCut("CutSSWZmm"        , "SSWZmm: "                 , "(passSSmm)*(mc_HLT_DoubleMu==1)"                                                      , "trigsf"+trigsfvar_suffix)
    tqcuts["CutSSWZeeNj2"]     = TQCut("CutSSWZeeNj2"     , "SSWZee: 1. n_{j} #geq 2"  , "nj30"+jecvar_suffix+">= 2"                                                            , "1")
    tqcuts["CutSSWZemNj2"]     = TQCut("CutSSWZemNj2"     , "SSWZem: 1. n_{j} #geq 2"  , "nj30"+jecvar_suffix+">= 2"                                                            , "1")
    tqcuts["CutSSWZmmNj2"]     = TQCut("CutSSWZmmNj2"     , "SSWZmm: 1. n_{j} #geq 2"  , "nj30"+jecvar_suffix+">= 2"                                                            , "1")
    tqcuts["CutSSWZeeNb0"]     = TQCut("CutSSWZeeNb0"     , "SSWZee: 2. n_{b} = 0"     , "nb"+jecvar_suffix+"==0"                                                               , "weight_btagsf"+btagsfvar_suffix)
    tqcuts["CutSSWZemNb0"]     = TQCut("CutSSWZemNb0"     , "SSWZem: 2. n_{b} = 0"     , "nb"+jecvar_suffix+"==0"                                                               , "weight_btagsf"+btagsfvar_suffix)
    tqcuts["CutSSWZmmNb0"]     = TQCut("CutSSWZmmNb0"     , "SSWZmm: 2. n_{b} = 0"     , "nb"+jecvar_suffix+"==0"                                                               , "weight_btagsf"+btagsfvar_suffix)
#    tqcuts["CutSSWZeeMjjW"]    = TQCut("CutSSWZeeMjjW"    , "SSWZee: 3. |Mjj-80| < 15" , "abs(Mjj-80.)<15."                                                                     , "1")
#    tqcuts["CutSSWZemMjjW"]    = TQCut("CutSSWZemMjjW"    , "SSWZem: 3. |Mjj-80| < 15" , "abs(Mjj-80.)<15."                                                                     , "1")
#    tqcuts["CutSSWZmmMjjW"]    = TQCut("CutSSWZmmMjjW"    , "SSWZmm: 3. |Mjj-80| < 15" , "abs(Mjj-80.)<15."                                                                     , "1")
#    tqcuts["CutSSWZeeMjjL"]    = TQCut("CutSSWZeeMjjL"    , "SSWZee: 4. MjjL < 400"    , "MjjL<400."                                                                            , "1")
#    tqcuts["CutSSWZemMjjL"]    = TQCut("CutSSWZemMjjL"    , "SSWZem: 4. MjjL < 400"    , "MjjL<400."                                                                            , "1")
#    tqcuts["CutSSWZmmMjjL"]    = TQCut("CutSSWZmmMjjL"    , "SSWZmm: 4. MjjL < 400"    , "MjjL<400."                                                                            , "1")
#    tqcuts["CutSSWZeeDetajjL"] = TQCut("CutSSWZeeDetajjL" , "SSWZee: 5. DetajjL < 1.5" , "DetajjL<1.5"                                                                          , "1")
#    tqcuts["CutSSWZemDetajjL"] = TQCut("CutSSWZemDetajjL" , "SSWZem: 5. DetajjL < 1.5" , "DetajjL<1.5"                                                                          , "1")
#    tqcuts["CutSSWZmmDetajjL"] = TQCut("CutSSWZmmDetajjL" , "SSWZmm: 5. DetajjL < 1.5" , "DetajjL<1.5"                                                                          , "1")
    tqcuts["CutSSWZeeMjjW"]    = TQCut("CutSSWZeeMjjW"    , "SSWZee: 3. |Mjj-80| < 15" , "1"                                                                                    , "1")
    tqcuts["CutSSWZemMjjW"]    = TQCut("CutSSWZemMjjW"    , "SSWZem: 3. |Mjj-80| < 15" , "1"                                                                                    , "1")
    tqcuts["CutSSWZmmMjjW"]    = TQCut("CutSSWZmmMjjW"    , "SSWZmm: 3. |Mjj-80| < 15" , "1"                                                                                    , "1")
    tqcuts["CutSSWZeeMjjL"]    = TQCut("CutSSWZeeMjjL"    , "SSWZee: 4. MjjL < 400"    , "1"                                                                                    , "1")
    tqcuts["CutSSWZemMjjL"]    = TQCut("CutSSWZemMjjL"    , "SSWZem: 4. MjjL < 400"    , "1"                                                                                    , "1")
    tqcuts["CutSSWZmmMjjL"]    = TQCut("CutSSWZmmMjjL"    , "SSWZmm: 4. MjjL < 400"    , "1"                                                                                    , "1")
    tqcuts["CutSSWZeeDetajjL"] = TQCut("CutSSWZeeDetajjL" , "SSWZee: 5. DetajjL < 1.5" , "1"                                                                                    , "1")
    tqcuts["CutSSWZemDetajjL"] = TQCut("CutSSWZemDetajjL" , "SSWZem: 5. DetajjL < 1.5" , "1"                                                                                    , "1")
    tqcuts["CutSSWZmmDetajjL"] = TQCut("CutSSWZmmDetajjL" , "SSWZmm: 5. DetajjL < 1.5" , "1"                                                                                    , "1")
    tqcuts["CutSSWZeeMET"]     = TQCut("CutSSWZeeMET"     , "SSWZee: 6. MET > 60"      , "met_pt>60."                                                                           , "1")
    tqcuts["CutSSWZemMET"]     = TQCut("CutSSWZemMET"     , "SSWZem: 6. MET > 60"      , "met_pt>60."                                                                           , "1")
    tqcuts["CutSSWZmmMET"]     = TQCut("CutSSWZmmMET"     , "SSWZmm: 6. MET > 0"       , "1."                                                                                   , "1")
    tqcuts["CutSSWZeeMllSS"]   = TQCut("CutSSWZeeMllSS"   , "SSWZee: 7. MllSS > 60"    , "MllSS>60."                                                                            , "1")
    tqcuts["CutSSWZemMllSS"]   = TQCut("CutSSWZemMllSS"   , "SSWZem: 7. MllSS > 60"    , "MllSS>60."                                                                            , "1")
    tqcuts["CutSSWZmmMllSS"]   = TQCut("CutSSWZmmMllSS"   , "SSWZmm: 7. MllSS > 40"    , "MllSS>40."                                                                            , "1")
    tqcuts["CutSSWZeeMjjWin"]  = TQCut("CutSSWZeeMjjWin"  , "SSWZee: 8. |Mjj-80| < 15" , "abs(Mjj-80.)<15."                                                                     , "1")
    tqcuts["CutSSWZemMjjWin"]  = TQCut("CutSSWZemMjjWin"  , "SSWZem: 8. |Mjj-80| < 15" , "abs(Mjj-80.)<15."                                                                     , "1")
    tqcuts["CutSSWZmmMjjWin"]  = TQCut("CutSSWZmmMjjWin"  , "SSWZmm: 8. |Mjj-80| < 15" , "abs(Mjj-80.)<15."                                                                     , "1")
    tqcuts["CutSSWZeeMjjWout"] = TQCut("CutSSWZeeMjjWout" , "SSWZee: 9. |Mjj-80| > 15" , "abs(Mjj-80.)>15."                                                                     , "1")
    tqcuts["CutSSWZemMjjWout"] = TQCut("CutSSWZemMjjWout" , "SSWZem: 9. |Mjj-80| > 15" , "abs(Mjj-80.)>15."                                                                     , "1")
    tqcuts["CutSSWZmmMjjWout"] = TQCut("CutSSWZmmMjjWout" , "SSWZmm: 9. |Mjj-80| > 15" , "abs(Mjj-80.)>15."                                                                     , "1")

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
    tqcuts["CutSSWZeeMllSS"].addCut(tqcuts["CutSSWZeeMjjWin"])
    tqcuts["CutSSWZemMllSS"].addCut(tqcuts["CutSSWZemMjjWin"])
    tqcuts["CutSSWZmmMllSS"].addCut(tqcuts["CutSSWZmmMjjWin"])
    tqcuts["CutSSWZeeMllSS"].addCut(tqcuts["CutSSWZeeMjjWout"])
    tqcuts["CutSSWZemMllSS"].addCut(tqcuts["CutSSWZemMjjWout"])
    tqcuts["CutSSWZmmMllSS"].addCut(tqcuts["CutSSWZmmMjjWout"])

    return cuts
