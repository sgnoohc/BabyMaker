#!/bin/env python

import sys
import ROOT
from QFramework import TQCut
from qutils import *

#
# TQCut object is used to define cuts
# Everything until the creation of TQCut is simply defining list of string objects
#
# cuts = [
#    [ "CutVariable0 == 0", "(Weight To Apply for this cut)" ],
#    [ "CutVariable1 > 50", "(Weight To Apply for this cut)" ],
#    ...
#    ...
#    ...
# ]
#
# Later you call the createTQCut("nameOfTheCut", cuts)
# The createTQCut function returns the TQCut with each cuts nested
#
#  e.g. 
#       cut0_nameOfTheCut : CutVariable0 == 0
#         cut1_nameOfTheCut : CutVariable1 > 50
#           cut2_nameOfTheCut : ...
#             cut3_nameOfTheCut : ...
#               nameOfTheCut : ...
#
# Where the final "nameOfTheCut" is a selection which applies everything above
#

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
["1"                    , "evt_scale1fb"  ] , 
["1"                    , "35.9"          ] , 
["1"                    , "purewgt"       ] , 
["1"                    , "weight_btagsf" ] , 
["1"                    , "lepsf"         ] , 
["1"                    , "trigeff"       ] , 
["Flag_AllEventFilters" , "1"             ] , 
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
[BkgTypeCutExpr                               , BkgTypeWgtExpr],
[BaseCutExpr                                  , BaseWgtExpr],
["nVlep==2"                                   , "1"],
["nTlep=={$(usefakeweight)?1:2}"              , "1"],
["nLlep==2"                                   , "1"],
["nisoTrack_mt2_cleaned_VVV_cutbased_veto==0" , "1"],
["vetophoton==0"                              , "1"],
]

# Get the cut expression for the SSee preselection
SSeePreselCuts = [
["passSSee"     , "1"],
["HLT_DoubleMu" , "1"],
]
SSeePreselCuts.extend(SSpreselCuts)

# Get the cut expression for the SSem preselection
SSemPreselCuts = [
["passSSem" , "1"],
["HLT_MuEG" , "1"],
]
SSemPreselCuts.extend(SSpreselCuts)

# Get the cut expression for the SSmm preselection
SSmmPreselCuts = [
["passSSmm" , "1"],
["HLT_DoubleEl_DZ_2" , "1"],
]
SSmmPreselCuts.extend(SSpreselCuts)

#
# Three Lepton Preselection
#

# Common Cuts and weights
TLpreselCuts = [
[BkgTypeCutExpr                              , BkgTypeWgtExpr] , 
[BaseCutExpr                                 , BaseWgtExpr   ] , 
["HLT_DoubleEl_DZ_2||HLT_MuEG||HLT_DoubleMu" , "1"           ] , 
["nVlep==3"                                  , "1"           ] , 
["nTlep=={$(usefakeweight)?2:3}"             , "1"           ] , 
["nLlep==3"                                  , "1"           ] , 
["vetophoton==0"                             , "1"           ] , 
]

# Get the cut expression for the TL0SFOS preselection
TL0SFOSPreselCuts = [ ["nSFOS==0" , "1"], ]
TL0SFOSPreselCuts.extend(TLpreselCuts)

# Get the cut expression for the TL1SFOS preselection
TL1SFOSPreselCuts = [ ["nSFOS==1" , "1"], ]
TL1SFOSPreselCuts.extend(TLpreselCuts)

# Get the cut expression for the TL2SFOS preselection
TL2SFOSPreselCuts = [ ["nSFOS==2" , "1"], ]
TL2SFOSPreselCuts.extend(TLpreselCuts)

#
# SS Lost Lepton CR Preselection
#

# Common Cuts and weights
SSWZpreselCuts = [
[BkgTypeCutExpr                                  , BkgTypeWgtExpr] , 
[BaseCutExpr                                     , BaseWgtExpr   ] , 
["HLT_DoubleEl_DZ_2||HLT_MuEG||HLT_DoubleMu"     , "1"           ] , 
["nVlep==3"                                      , "1"           ] , 
["nTlepSS>=2"                                    , "1"           ] , 
["nLlep==3"                                      , "1"           ] , 
["nisoTrack_mt2_cleaned_VVV_cutbased_veto==0"    , "1"           ] , 
["vetophoton==0"                                 , "1"           ] , 
]

# Get the cut expression for the SSWZee preselection
SSWZeePreselCuts = [ ["passSSee", "1"], ]
SSWZeePreselCuts.extend(SSWZpreselCuts)

# Get the cut expression for the SSWZem preselection
SSWZemPreselCuts = [ ["passSSem", "1"], ]
SSWZemPreselCuts.extend(SSWZpreselCuts)

# Get the cut expression for the SSWZmm preselection
SSWZmmPreselCuts = [ ["passSSmm", "1"], ]
SSWZmmPreselCuts.extend(SSWZpreselCuts)

########################################################################################
# Same Sign Regions
########################################################################################

SSeeCuts = []
SSeeCuts.extend(SSeePreselCuts)
SSeeCuts.append(["abs(MeeSS-91.1876)>10" , "1"])
SSeeCuts.append(["nj30>=2"               , "1"])
SSeeCuts.append(["nb==0"                 , "1"])
SSeeCuts.append(["MllSS>40."             , "1"])
SSeeCuts.append(["met_pt>60."            , "1"])
SSeeCuts.append(["MjjL<400."             , "1"])
SSeeCuts.append(["DetajjL<1.5"           , "1"])
SSeeCuts.append(["abs(Mjj-80)<15."       , "1"])

SSemCuts = []
SSemCuts.extend(SSemPreselCuts)
SSemCuts.append(["nj30>=2"              , "1"])
SSemCuts.append(["nb==0"                , "1"])
SSemCuts.append(["MllSS>40."            , "1"])
SSemCuts.append(["met_pt>60."           , "1"])
SSemCuts.append(["MTmax>90."            , "1"])
SSemCuts.append(["MjjL<400."            , "1"])
SSemCuts.append(["DetajjL<1.5"          , "1"])
SSemCuts.append(["abs(Mjj-80)<15."      , "1"])

SSmmCuts = []
SSmmCuts.extend(SSmmPreselCuts)
SSmmCuts.append(["nj30>=2"              , "1"])
SSmmCuts.append(["nb==0"                , "1"])
SSmmCuts.append(["MllSS>40."            , "1"])
SSmmCuts.append(["MjjL<400."            , "1"])
SSmmCuts.append(["DetajjL<1.5"          , "1"])
SSmmCuts.append(["abs(Mjj-80)<15."      , "1"])

SSWZeeCuts = []
SSWZeeCuts.extend(SSWZeePreselCuts)
SSWZeeCuts.append(["abs(MeeSS-91.1876)>10" , "1"])
SSWZeeCuts.append(["nj30>=2"               , "1"])
SSWZeeCuts.append(["nb==0"                 , "1"])
SSWZeeCuts.append(["MllSS>40."             , "1"])
SSWZeeCuts.append(["met_pt>60."            , "1"])
SSWZeeCuts.append(["MjjL<400."             , "1"])
SSWZeeCuts.append(["DetajjL<1.5"           , "1"])
SSWZeeCuts.append(["abs(Mjj-80)<15."       , "1"])
SSWZeeCuts.append(["nSFOSinZ>0"            , "1"])

SSWZemCuts = []
SSWZemCuts.extend(SSWZemPreselCuts)
SSWZemCuts.append(["nj30>=2"              , "1"])
SSWZemCuts.append(["nb==0"                , "1"])
SSWZemCuts.append(["MllSS>40."            , "1"])
SSWZemCuts.append(["met_pt>60."           , "1"])
SSWZemCuts.append(["MTmax>90."            , "1"])
SSWZemCuts.append(["MjjL<400."            , "1"])
SSWZemCuts.append(["DetajjL<1.5"          , "1"])
SSWZemCuts.append(["abs(Mjj-80)<15."      , "1"])
SSWZemCuts.append(["nSFOSinZ>0"           , "1"])

SSWZmmCuts = []
SSWZmmCuts.extend(SSWZmmPreselCuts)
SSWZmmCuts.append(["nj30>=2"              , "1"])
SSWZmmCuts.append(["nb==0"                , "1"])
SSWZmmCuts.append(["MllSS>40."            , "1"])
SSWZmmCuts.append(["MjjL<400."            , "1"])
SSWZmmCuts.append(["DetajjL<1.5"          , "1"])
SSWZmmCuts.append(["abs(Mjj-80)<15."      , "1"])
SSWZmmCuts.append(["nSFOSinZ>0"           , "1"])

########################################################################################
# Three Lepton Regions
########################################################################################

TL0SFOSCuts = []
TL0SFOSCuts.extend(TL0SFOSPreselCuts)
TL0SFOSCuts.append(["nj<=1"                   , "1"])
TL0SFOSCuts.append(["nb==0"                   , "1"])
TL0SFOSCuts.append(["met_pt>30."              , "1"])
TL0SFOSCuts.append(["DPhi3lMET>2.7"           , "1"])
TL0SFOSCuts.append(["abs(M3l-91.1876)>10."    , "1"])
TL0SFOSCuts.append(["Mll3L>20."               , "1"])
TL0SFOSCuts.append(["abs(Mee3L-91.1876)>15."  , "1"])

TL1SFOSCuts = []
TL1SFOSCuts.extend(TL1SFOSPreselCuts)
TL1SFOSCuts.append(["nj<=1"                   , "1"])
TL1SFOSCuts.append(["nb==0"                   , "1"])
TL1SFOSCuts.append(["Pt3l>60."                , "1"])
TL1SFOSCuts.append(["DPhi3lMET>2.5"           , "1"])
TL1SFOSCuts.append(["MT3rd>90."               , "1"])
TL1SFOSCuts.append(["abs(M3l-91.1876)>10."    , "1"])
TL1SFOSCuts.append(["met_pt>45."              , "1"])
TL1SFOSCuts.append(["Mll3L>20."               , "1"])
TL1SFOSCuts.append(["nSFOSinZ>0"              , "1"])

TL2SFOSCuts = []
TL2SFOSCuts.extend(TL2SFOSPreselCuts)
TL2SFOSCuts.append(["nj<=1"                   , "1"])
TL2SFOSCuts.append(["nb==0"                   , "1"])
TL2SFOSCuts.append(["Pt3l>60."                , "1"])
TL2SFOSCuts.append(["DPhi3lMET>2.5"           , "1"])
TL2SFOSCuts.append(["abs(M3l-91.1876)>10."    , "1"])
TL2SFOSCuts.append(["met_pt>55."              , "1"])
TL2SFOSCuts.append(["Mll3L>20."               , "1"])
TL2SFOSCuts.append(["Mll3L1>20."              , "1"])
TL2SFOSCuts.append(["nSFOSinZ>0"              , "1"])

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
cuts.addCut(SSWZeeCut)
cuts.addCut(SSWZemCut)
cuts.addCut(SSWZmmCut)
cuts.addCut(TL0SFOSCut)
cuts.addCut(TL1SFOSCut)
cuts.addCut(TL2SFOSCut)
cuts.printCuts("trd")
