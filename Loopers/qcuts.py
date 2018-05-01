#!/bin/env python

import sys
import ROOT
from QFramework import TQCut
from qutils import *

########################################################################################
# background type categorization
########################################################################################
BkgTypeCuts = [
["{\"$(path)\"==\"/bkg/VVV/whwww\"?bkgtype!=\"WHtoWWW\":1}","1"],
["{\"$(path)\"==\"/bkg/W/wjets_incl_mgmlm\"?gen_ht>100.:1}","1"],
["{\"$(path)\"==\"/bkg/Z/dy_m50_mgmlm_ext1\"?gen_ht>100.:1}","1"],
]
BkgTypeCutExpr, BkgTypeWgtExpr = combexpr(BkgTypeCuts)

BaseCuts = [
["1"                    , "evt_scale1fb"                   ] , 
["1"                    , "purewgt"                        ] , 
#["1"                    , "lepsf"                          ] , 
["1"                    , "trigeff"                        ] , 
["1"                    , "{$(usefakeweight)?ffwgt:35.9}"  ] , 
["Flag_AllEventFilters" , "1"                              ] , 
]
BaseCutExpr, BaseWgtExpr = combexpr(BaseCuts)

########################################################################################
# Preselection
########################################################################################

#
# Same Sign Preselection
#

# Common Cuts and weights
SSpreselCuts = [
[BkgTypeCutExpr                               , BkgTypeWgtExpr] , 
[BaseCutExpr                                  , BaseWgtExpr]    , 
["nVlep==2"                                   , "1"]            , 
["nLlep==2"                                   , "1"]            , 
["nTlep=={$(usefakeweight)?1:2}"              , "1"]            , 
["nisoTrack_mt2_cleaned_VVV_cutbased_veto==0" , "1"]            , 
["vetophoton==0"                              , "1"]            , 
#["(abs(lep_p4[0].eta())<1.6)*(lep_ptRatio[0]>0.9)+(abs(lep_p4[0].eta())>=1.6)*(lep_ptRatio[0]>0.85)" , "1"], 
#["(abs(lep_p4[1].eta())<1.6)*(lep_ptRatio[1]>0.9)+(abs(lep_p4[1].eta())>=1.6)*(lep_ptRatio[1]>0.85)" , "1"], 
#["((abs(lep_pdgId[1]) == 11) * (abs(lep_eta[1])) + (abs(lep_pdgId[0]) == 11) * (abs(lep_eta[0])))<1.6", "1"],
#["(abs(lep_p4[0].eta())<1.6)*(lep_ptRatio[0]>0.9)+(abs(lep_p4[0].eta())>=1.6)*(1)" , "1"], 
#["(abs(lep_p4[1].eta())<1.6)*(lep_ptRatio[1]>0.9)+(abs(lep_p4[1].eta())>=1.6)*(1)" , "1"], 
#["((abs(lep_pdgId[1]) == 13) * (lep_ptRatio[1]) + (abs(lep_pdgId[0]) == 13) * (lep_ptRatio[0]))>0.9", "1"],
#["((abs(lep_pdgId[1]) == 11) * ((abs(lep_p4[1].eta())<1.6)*(lep_ptRatio[1]>0.9)+(abs(lep_p4[1].eta())>=1.6)*(lep_ptRatio[1]>0.8)) + (abs(lep_pdgId[0]) == 11) * ((abs(lep_eta[0])<1.6)*(lep_ptRatio[0]>0.9)+(abs(lep_eta[0])>=1.6)*(lep_ptRatio[0]>0.8)))", "1"],
]
SSpreselCutExpr, SSpreselWgtExpr = combexpr(SSpreselCuts)

# Get the cut expression for the SSee preselection
SSeePreselCuts = []
SSeePreselCuts.extend([
["SSPresel"   , "SS:   presel" , SSpreselCutExpr        , SSpreselWgtExpr],
["SSeeChannel", "SSee: channel", "passSSee==1"          , "1"            ],
["SSeeTrigger", "SSee: trigger", "HLT_DoubleEl_DZ_2==1" , "1"            ],
])

# Get the cut expression for the SSem preselection
SSemPreselCuts = []
SSemPreselCuts.extend([
["SSPresel"   , "SS:   presel"  , SSpreselCutExpr , SSpreselWgtExpr] , 
["SSemChannel", "SSem: channel" , "passSSem==1"   , "1"]             , 
["SSemTrigger", "SSem: trigger" , "HLT_MuEG==1"   , "1"]             , 
])

# Get the cut expression for the SSmm preselection
SSmmPreselCuts = []
SSmmPreselCuts.extend([
["SSPresel"    , "SS:   presel"  , SSpreselCutExpr   , SSpreselWgtExpr] , 
["SSmmChannel" , "SSmm: channel" , "passSSmm==1"     , "1"]             , 
["SSmmTrigger" , "SSmm: trigger" , "HLT_DoubleMu==1" , "1"]             , 
])

#
# Three Lepton Preselection
#

# Common Cuts and weights
TLpreselCuts = [
[BkgTypeCutExpr                              , BkgTypeWgtExpr] , 
[BaseCutExpr                                 , BaseWgtExpr   ] , 
["(HLT_DoubleEl_DZ_2==1)||(HLT_MuEG==1)||(HLT_DoubleMu==1)" , "1"           ] , 
["nVlep==3"                                  , "1"           ] , 
["nLlep==3"                                  , "1"           ] , 
#["nTlep=={$(usefakeweight)?2:3}"             , "1"           ] , 
["nTlep>=2"                                  , "1"           ] , 
["vetophoton==0"                             , "1"           ] , 
["met_pt>30."                                , "1"           ] , 
["nb==0"                                     , "weight_btagsf"] , 
]
TLpreselCutExpr, TLpreselWgtExpr = combexpr(TLpreselCuts)

# Get the cut expression for the TL0SFOS preselection
TL0SFOSPreselCuts = []
TL0SFOSPreselCuts.extend([
["TLPresel"      , "TL: presel"     , TLpreselCutExpr , TLpreselWgtExpr] , 
["TL0SFOSChannel", "TL0SFOS: nSFOS" , "nSFOS==0"      , "1"]             , 
])

# Get the cut expression for the TL1SFOS preselection
TL1SFOSPreselCuts = []
TL1SFOSPreselCuts.extend([
["TLPresel"      , "TL: presel"     , TLpreselCutExpr , TLpreselWgtExpr] , 
["TL1SFOSChannel", "TL1SFOS: nSFOS" , "nSFOS==1"      , "1"]             , 
])

# Get the cut expression for the TL2SFOS preselection
TL2SFOSPreselCuts = []
TL2SFOSPreselCuts.extend([
["TLPresel"      , "TL: presel"     , TLpreselCutExpr , TLpreselWgtExpr] , 
["TL2SFOSChannel", "TL2SFOS: nSFOS" , "nSFOS==2"      , "1"]             , 
])

#
# SS Lost Lepton CR Preselection
#

# Common Cuts and weights
SSWZpreselCuts = [
[BkgTypeCutExpr                               , BkgTypeWgtExpr] , 
[BaseCutExpr                                  , BaseWgtExpr   ] , 
["HLT_DoubleEl_DZ_2||HLT_MuEG||HLT_DoubleMu"  , "1"           ] , 
["nVlep==3"                                   , "1"           ] , 
["nLlep==3"                                   , "1"           ] , 
["nTlepSS>=2"                                 , "1"           ] , 
["nisoTrack_mt2_cleaned_VVV_cutbased_veto==0" , "1"           ] , 
["vetophoton==0"                              , "1"           ] , 
]
SSWZpreselCutExpr, SSWZpreselWgtExpr = combexpr(SSWZpreselCuts)

# Get the cut expression for the SSWZee preselection
SSWZeePreselCuts = []
SSWZeePreselCuts.extend([
["SSWZPresel"   , "SSWZ: presel"    , SSWZpreselCutExpr , SSWZpreselWgtExpr] , 
["SSWZeeChannel", "SSWZee: channel" , "passSSee"        , "1"]               , 
])

# Get the cut expression for the SSWZem preselection
SSWZemPreselCuts = []
SSWZemPreselCuts.extend([
["SSWZPresel"   , "SSWZ: presel"    , SSWZpreselCutExpr , SSWZpreselWgtExpr] , 
["SSWZemChannel", "SSWZem: channel" , "passSSem"        , "1"]               , 
])

# Get the cut expression for the SSWZmm preselection
SSWZmmPreselCuts = []
SSWZmmPreselCuts.extend([
["SSWZPresel"   , "SSWZ: presel"    , SSWZpreselCutExpr , SSWZpreselWgtExpr] , 
["SSWZmmChannel", "SSWZmm: channel" , "passSSmm"        , "1"]               , 
])

########################################################################################
# Same Sign Regions
########################################################################################

SSeeCuts = []
SSeeCuts.extend(SSeePreselCuts)
SSeeCuts.append(["SSeeZeeVt", "SSee: Mee-MZ veto"   , "abs(MeeSS-91.1876)>10" , "1"])
SSeeCuts.append(["SSeeMll40", "SSee: Mll > 40"      , "MllSS>40."             , "1"])
SSeeCuts.append(["SSeeNjet2", "SSee: njet #geq 2"   , "nj30>=2"               , "1"])
SSeeCuts.append(["SSeeBVeto", "SSee: nb = 0"        , "nb==0"                 , "weight_btagsf"])
SSeeCuts.append(["SSeeWmass", "SSee: |Mjj-MW| < 15" , "abs(Mjj-80)<15."       , "1"])
SSeeCuts.append(["SSeeMET60", "SSee: MET > 60"      , "met_pt>60."            , "1"])
SSeeCuts.append(["SSeeMjj"  , "SSee: MjjL < 400"    , "MjjL<400."             , "1"])
SSeeCuts.append(["SSeeDEta" , "SSee: DetajjL < 1.5" , "DetajjL<1.5"           , "1"])

SSemCuts = []
SSemCuts.extend(SSemPreselCuts)
SSemCuts.append(["SSemMll40", "SSem: Mll > 40"      , "MllSS>40."            , "1"])
SSemCuts.append(["SSemNjet2", "SSem: njet #geq 2"   , "nj30>=2"              , "1"])
SSemCuts.append(["SSemBVeto", "SSem: nb = 0"        , "nb==0"                , "weight_btagsf"])
SSemCuts.append(["SSemWmass", "SSem: |Mjj-MW| < 15" , "abs(Mjj-80)<15."      , "1"])
SSemCuts.append(["SSemMET60", "SSem: MET > 60"      , "met_pt>60."           , "1"])
SSemCuts.append(["SSemMTmax", "SSem: MTmax > 90"    , "MTmax>90."            , "1"])
SSemCuts.append(["SSemMjj"  , "SSem: MjjL < 400"    , "MjjL<400."            , "1"])
SSemCuts.append(["SSemDEta" , "SSem: DetajjL < 1.5" , "DetajjL<1.5"          , "1"])

SSmmCuts = []
SSmmCuts.extend(SSmmPreselCuts)
SSmmCuts.append(["SSmmMll40", "SSmm: Mll > 40"      , "MllSS>40."            , "1"])
SSmmCuts.append(["SSmmNjet2", "SSmm: njet #geq 2"   , "nj30>=2"              , "1"])
SSmmCuts.append(["SSmmBVeto", "SSmm: nb = 0"        , "nb==0"                , "weight_btagsf"])
SSmmCuts.append(["SSmmWmass", "SSmm: |Mjj-MW| < 15" , "abs(Mjj-80)<15."      , "1"])
SSmmCuts.append(["SSmmMjj"  , "SSmm: MjjL < 400"    , "MjjL<400."            , "1"])
SSmmCuts.append(["SSmmDEta" , "SSmm: DetajjL < 1.5" , "DetajjL<1.5"          , "1"])

SSWZeeCuts = []
SSWZeeCuts.extend(SSWZeePreselCuts)
SSWZeeCuts.append(["SSWZeeZeeVt", "SSWZee: Mee-MZ veto"   , "abs(MeeSS-91.1876)>10" , "1"])
SSWZeeCuts.append(["SSWZeeMll40", "SSWZee: Mll > 40"      , "MllSS>40."             , "1"])
SSWZeeCuts.append(["SSWZeeNjet2", "SSWZee: njet #geq 2"   , "nj30>=2"               , "1"])
SSWZeeCuts.append(["SSWZeeBVeto", "SSWZee: nb = 0"        , "nb==0"                 , "weight_btagsf"])
SSWZeeCuts.append(["SSWZeeWmass", "SSWZee: |Mjj-MW| < 15" , "abs(Mjj-80)<15."       , "1"])
SSWZeeCuts.append(["SSWZeeMET60", "SSWZee: MET > 60"      , "met_pt>60."            , "1"])
SSWZeeCuts.append(["SSWZeeMjj"  , "SSWZee: MjjL < 400"    , "MjjL<400."             , "1"])
SSWZeeCuts.append(["SSWZeeDEta" , "SSWZee: DetajjL < 1.5" , "DetajjL<1.5"           , "1"])
SSWZeeCuts.append(["SSWZeeZVeto", "SSWZee: Z veto"        , "nSFOSinZ>0"            , "1"])

SSWZemCuts = []
SSWZemCuts.extend(SSWZemPreselCuts)
SSWZemCuts.append(["SSWZemMll40", "SSWZem: Mll > 40"      , "MllSS>40."            , "1"])
SSWZemCuts.append(["SSWZemNjet2", "SSWZem: njet #geq 2"   , "nj30>=2"              , "1"])
SSWZemCuts.append(["SSWZemBVeto", "SSWZem: nb = 0"        , "nb==0"                , "weight_btagsf"])
SSWZemCuts.append(["SSWZemWMass", "SSWZem: |Mjj-MW| < 15" , "abs(Mjj-80)<15."      , "1"])
SSWZemCuts.append(["SSWZemMET60", "SSWZem: MET > 60"      , "met_pt>60."           , "1"])
SSWZemCuts.append(["SSWZemMTmax", "SSWZem: MTmax > 90"    , "MTmax>90."            , "1"])
SSWZemCuts.append(["SSWZemMjj"  , "SSWZem: MjjL < 400"    , "MjjL<400."            , "1"])
SSWZemCuts.append(["SSWZemDEta" , "SSWZem: DetajjL < 1.5" , "DetajjL<1.5"          , "1"])
SSWZemCuts.append(["SSWZemZVeto", "SSWZem: Z veto"        , "nSFOSinZ>0"           , "1"])

SSWZmmCuts = []
SSWZmmCuts.extend(SSWZmmPreselCuts)
SSWZmmCuts.append(["SSWZmmMll40", "SSWZmm: Mll > 40"      , "MllSS>40."            , "1"])
SSWZmmCuts.append(["SSWZmmNjet2", "SSWZmm: njet #geq 2"   , "nj30>=2"              , "1"])
SSWZmmCuts.append(["SSWZmmBveto", "SSWZmm: nb = 0"        , "nb==0"                , "weight_btagsf"])
SSWZmmCuts.append(["SSWZmmWmass", "SSWZmm: |Mjj-MW| < 15" , "abs(Mjj-80)<15."      , "1"])
SSWZmmCuts.append(["SSWZmmMjj"  , "SSWZmm: MjjL < 400"    , "MjjL<400."            , "1"])
SSWZmmCuts.append(["SSWZmmDEta" , "SSWZmm: DetajjL < 1.5" , "DetajjL<1.5"          , "1"])
SSWZmmCuts.append(["SSWZmmZVeto", "SSWZmm: Z veto"        , "nSFOSinZ>0"           , "1"])

SSincleeCuts = []
SSincleeCuts.extend(SSeePreselCuts)
SSincleeCuts.append(["SSincleeZeeVt", "SSinclee: Mee-MZ veto" , "abs(MeeSS-91.1876)>10" , "1"])
SSincleeCuts.append(["SSincleeMll40", "SSinclee: Mll > 40"    , "MllSS>40."             , "1"])
SSincleeCuts.append(["SSincleeBVeto", "SSinclee: nb = 0"      , "nb==0"                 , "weight_btagsf"])

SSinclemCuts = []
SSinclemCuts.extend(SSemPreselCuts)
SSinclemCuts.append(["SSinclemMll40", "SSinclem: Mll > 40"    , "MllSS>40." , "1"])
SSinclemCuts.append(["SSinclemBVeto", "SSinclem: nb = 0"      , "nb==0"     , "weight_btagsf"])

SSinclmmCuts = []
SSinclmmCuts.extend(SSmmPreselCuts)
SSinclmmCuts.append(["SSinclmmMll40", "SSinclmm: Mll > 40"    , "MllSS>40." , "1"])
SSinclmmCuts.append(["SSinclmmBVeto", "SSinclmm: nb = 0"      , "nb==0"     , "weight_btagsf"])

########################################################################################
# Three Lepton Regions
########################################################################################

TL0SFOSCuts = []
TL0SFOSCuts.extend(TL0SFOSPreselCuts)
TL0SFOSCuts.append(["TL0SFOSNjet1", "TL0SFOS: njet #leq 1"     , "nj<=1"                  , "1"])
TL0SFOSCuts.append(["TL0SFOSBVeto", "TL0SFOS: nb = 0"          , "nb==0"                  , "weight_btagsf"])
TL0SFOSCuts.append(["TL0SFOSMET30", "TL0SFOS: MET > 30"        , "met_pt>30."             , "1"])
TL0SFOSCuts.append(["TL0SFOSDPhiM", "TL0SFOS: dPhi3lMET > 2.7" , "DPhi3lMET>2.7"          , "1"])
TL0SFOSCuts.append(["TL0SFOSM3lVt", "TL0SFOS: M3l Z veto"      , "abs(M3l-91.1876)>10."   , "1"])
TL0SFOSCuts.append(["TL0SFOSMll20", "TL0SFOS: Mll > 20"        , "Mll3L>20."              , "1"])
TL0SFOSCuts.append(["TL0SFOSMee15", "TL0SFOS: Mee3L > 15"      , "abs(Mee3L-91.1876)>15." , "1"])

TL1SFOSCuts = []
TL1SFOSCuts.extend(TL1SFOSPreselCuts)
TL1SFOSCuts.append(["TL1SFOSNjet1", "TL1SFOS: njet #leq 1"     , "nj<=1"                   , "1"])
TL1SFOSCuts.append(["TL1SFOSBVeto", "TL1SFOS: nb = 0"          , "nb==0"                   , "weight_btagsf"])
TL1SFOSCuts.append(["TL1SFOSPt3l" , "TL1SFOS: PT3l > 60"       , "Pt3l>60."                , "1"])
TL1SFOSCuts.append(["TL1SFOSDPhiM", "TL1SFOS: dPhi3lMET > 2.5" , "DPhi3lMET>2.5"           , "1"])
TL1SFOSCuts.append(["TL1SFOSMT3rd", "TL1SFOS: MT3rd > 90"      , "MT3rd>90."               , "1"])
TL1SFOSCuts.append(["TL1SFOSM3lVt", "TL1SFOS: M3l Z veto"      , "abs(M3l-91.1876)>10."    , "1"])
TL1SFOSCuts.append(["TL1SFOSMET45", "TL1SFOS: MET > 45"        , "met_pt>45."              , "1"])
TL1SFOSCuts.append(["TL1SFOSMll20", "TL1SFOS: Mll3L > 20"      , "Mll3L>20."               , "1"])
TL1SFOSCuts.append(["TL1SFOSZVeto", "TL1SFOS: Z veto"          , "nSFOSinZ==0"             , "1"])

TL2SFOSCuts = []
TL2SFOSCuts.extend(TL2SFOSPreselCuts)
TL2SFOSCuts.append(["TL2SFOSNjet1"  , "TL2SFOS: njet #leq 1"     , "nj<=1"                , "1"])
TL2SFOSCuts.append(["TL2SFOSBVeto"  , "TL2SFOS: nb = 0"          , "nb==0"                , "weight_btagsf"])
TL2SFOSCuts.append(["TL2SFOSPt3l"   , "TL2SFOS: PT3l > 60"       , "Pt3l>60."             , "1"])
TL2SFOSCuts.append(["TL2SFOSDPhiM"  , "TL2SFOS: dPhi3lMET > 2.5" , "DPhi3lMET>2.5"        , "1"])
TL2SFOSCuts.append(["TL2SFOSM3lVt"  , "TL2SFOS: M3l Z veto"      , "abs(M3l-91.1876)>10." , "1"])
TL2SFOSCuts.append(["TL2SFOSMET55"  , "TL2SFOS: MET > 55"        , "met_pt>55."           , "1"])
TL2SFOSCuts.append(["TL2SFOSMll3L"  , "TL2SFOS: Mll3L > 20"      , "Mll3L>20."            , "1"])
TL2SFOSCuts.append(["TL2SFOSMll3L1" , "TL2SFOS: Mll3L1 > 20"     , "Mll3L1>20."           , "1"])
TL2SFOSCuts.append(["TL2SFOSZVeto"  , "TL2SFOS: Z veto"          , "nSFOSinZ==0"          , "1"])

########################################################################################
# Same Sign WZ CR
########################################################################################

#
# Up to this point has all been defining strings
#

########################################################################################
# Create TQCut objects
########################################################################################

SSeeCut = createTQCut("SSee", SSeeCuts)
SSemCut = createTQCut("SSem", SSemCuts)
SSmmCut = createTQCut("SSmm", SSmmCuts)
SSincleeCut = createTQCut("SSinclee", SSincleeCuts)
SSinclemCut = createTQCut("SSinclem", SSinclemCuts)
SSinclmmCut = createTQCut("SSinclmm", SSinclmmCuts)
SSWZeeCut = createTQCut("SSWZee", SSWZeeCuts)
SSWZemCut = createTQCut("SSWZem", SSWZemCuts)
SSWZmmCut = createTQCut("SSWZmm", SSWZmmCuts)
TL0SFOSCut = createTQCut("TL0SFOS", TL0SFOSCuts)
TL1SFOSCut = createTQCut("TL1SFOS", TL1SFOSCuts)
TL2SFOSCut = createTQCut("TL2SFOS", TL2SFOSCuts)

cuts = TQCut("BaseCut", "BaseCut", "1", "1")
cuts.addCut(SSeeCut)
cuts.addCut(SSemCut)
cuts.addCut(SSmmCut)
cuts.addCut(SSincleeCut)
cuts.addCut(SSinclemCut)
cuts.addCut(SSinclmmCut)
cuts.addCut(SSWZeeCut)
cuts.addCut(SSWZemCut)
cuts.addCut(SSWZmmCut)
cuts.addCut(TL0SFOSCut)
cuts.addCut(TL1SFOSCut)
cuts.addCut(TL2SFOSCut)
cuts.printCuts("trd")
