import ROOT
from QFramework import TQCut

# Category separations
bkg_types_SS = ["trueSS", "chargeflips", "SSLL", "fakes", "photonfakes", "others"]
bkg_types_3L = ["trueWWW", "true3L", "chargeflips", "3lLL", "fakes", "photonfakes", "others"]

#_______________________________________________________________________________________
def addCuts(base, prefix_base, cutdefs):
    cuts = []
    prefix = prefix_base.split("base_")[1]
    for i, cutdef in enumerate(cutdefs):
        cutname = "cut{}_{}".format(i, prefix)
        if i == len(cutdefs) - 1 :
            cutname = "{}".format(prefix)
        cut = TQCut(cutname, cutname, cutdef[0], cutdef[1])
        cuts.append(cut)
    for i in xrange(len(cuts) - 1):
        cuts[i].addCut(cuts[i+1])
    base.addCut(cuts[0])

#_______________________________________________________________________________________
def getCuts(prefix, basecut, basewgt, addcutfunc, extracut):
    basename = "base_" + prefix
    base = TQCut(basename, basename, basecut, basewgt)
    if extracut:
        base.addCut(extracut)
        addcutfunc(extracut, basename)
    else:
        addcutfunc(base, basename)
    return base

########################################################################################
#
#
# Preliminary selections
#
#
########################################################################################

# The following cut is used to split the vh sample.
# Our current signal is defined to include WH->WWW process, however we do not have a signal sample with just WHWWW.
# So we split the VH->non-bb sample and select only the WH->WWW as signal.
# So the following obscure and inconvenient cut is applied.
# Basically if the looper is running for signal events, accept only the events that has the TString branch "sample_name" equal to "WHtoWWW".
# When the looper is running for background events select when "sample_name" branch is not equal to "WHtoWWW".
whwww_configuration_cut = "({\"$(path)\"==\"/sig/whwww\"&&\"$(name)\"==\"vh_nonbb_amcnlo_skim_1\"?sample_name==\"WHtoWWW\":1})*({\"$(path)\"==\"/bkg/VVV/whwww\"&&\"$(name)\"==\"vh_nonbb_amcnlo_skim_1\"?sample_name!=\"WHtoWWW\":1})" # WHtoWWW sample specific
trigger_configuration_cut = "{(process_name_ss==\"Data\"||process_name_3l==\"Data\")?pass_online_trig>0:1}"
configuration_cut = "({})".format(")*(".join([whwww_configuration_cut, trigger_configuration_cut]))

typebkg_ss_configuration_cuts = [
"{\"$(path)\"==\"/typebkg/prompt\"?process_name_ss==\"trueSS\":1}",
"{\"$(path)\"==\"/typebkg/qflip\"?process_name_ss==\"chargeflips\":1}",
"{\"$(path)\"==\"/typebkg/lostlep\"?process_name_ss==\"SSLL\":1}",
"{\"$(path)\"==\"/typebkg/fakes\"?process_name_ss==\"fakes\":1}",
"{\"$(path)\"==\"/typebkg/photon\"?process_name_ss==\"photonfakes\":1}",
"{\"$(path)\"==\"/typebkg/others\"?process_name_ss==\"others\":1}",
"{\"$(path)\"==\"/typebkg/prompt/WZ\"?process_name_ss==\"trueSS\":1}",
"{\"$(path)\"==\"/typebkg/qflip/WZ\"?process_name_ss==\"chargeflips\":1}",
"{\"$(path)\"==\"/typebkg/lostlep/WZ\"?process_name_ss==\"SSLL\":1}",
"{\"$(path)\"==\"/typebkg/fakes/WZ\"?process_name_ss==\"fakes\":1}",
"{\"$(path)\"==\"/typebkg/photon/WZ\"?process_name_ss==\"photonfakes\":1}",
"{\"$(path)\"==\"/typebkg/others/WZ\"?process_name_ss==\"others\":1}",
]
typebkg_ss_configuration_cut = "({})".format(")*(".join(typebkg_ss_configuration_cuts))

typebkg_3l_configuration_cuts = [
"{\"$(path)\"==\"/typebkg/prompt\"?(process_name_3l==\"true3L\"||process_name_3l==\"trueWWW\"):1}",
"{\"$(path)\"==\"/typebkg/qflip\"?process_name_3l==\"chargeflips\":1}",
"{\"$(path)\"==\"/typebkg/lostlep\"?process_name_3l==\"3lLL\":1}",
"{\"$(path)\"==\"/typebkg/fakes\"?process_name_3l==\"fakes\":1}",
"{\"$(path)\"==\"/typebkg/photon\"?process_name_3l==\"photonfakes\":1}",
"{\"$(path)\"==\"/typebkg/others\"?process_name_3l==\"others\":1}",
"{\"$(path)\"==\"/typebkg/prompt/WZ\"?(process_name_3l==\"true3L\"||process_name_3l==\"trueWWW\"):1}",
"{\"$(path)\"==\"/typebkg/qflip/WZ\"?process_name_3l==\"chargeflips\":1}",
"{\"$(path)\"==\"/typebkg/lostlep/WZ\"?process_name_3l==\"3lLL\":1}",
"{\"$(path)\"==\"/typebkg/fakes/WZ\"?process_name_3l==\"fakes\":1}",
"{\"$(path)\"==\"/typebkg/photon/WZ\"?process_name_3l==\"photonfakes\":1}",
"{\"$(path)\"==\"/typebkg/others/WZ\"?process_name_3l==\"others\":1}",
]
typebkg_3l_configuration_cut = "({})".format(")*(".join(typebkg_3l_configuration_cuts))

########################################################################################
#
#
# Same Sign Regions
#
#
########################################################################################

# Common cuts and weights
SSpreselcuts = [
        configuration_cut,
        typebkg_ss_configuration_cut,
        "n_veto_ss_lep==2",
        "vetophotonss==0",
        "n_tight_ss_lep=={\"$(path)\"==\"/fake\"?1:2}", # Fake estimation specific
        "n_loose_ss_lep==2",
        "ntrk==0"
        ]
SSpreselcut = "({})".format(")*(".join(SSpreselcuts))
SSpreselwgt = "trigsf*({\"$(path)\"==\"/fake\"?ffwgtss:1})"

#_______________________________________________________________________________________
def addSSeeCuts(base, prefix, preselcut=SSpreselcut + "*(abs(MllSS-91.1876)>10)", preselwgt=SSpreselwgt):
    cutdefs = []
    cutdefs.append([preselcut              , preselwgt])
    cutdefs.append(["nj>=2"                , ""       ])
    cutdefs.append(["nb==0"                , "btagsf" ])
    cutdefs.append(["MllSS > 40."          , ""       ])
    cutdefs.append(["MET.Pt()>40."         , ""       ])
    cutdefs.append(["MjjL<400."            , ""       ])
    cutdefs.append(["Detajj<1.5"           , ""       ])
    cutdefs.append(["Mjj>60.&&Mjj<100."    , ""       ])
    addCuts(base, prefix, cutdefs)

#_______________________________________________________________________________________
def addSSemCuts(base, prefix, preselcut=SSpreselcut, preselwgt=SSpreselwgt):
    cutdefs = []
    cutdefs.append([preselcut              , preselwgt])
    cutdefs.append(["nj>=2"                , ""      ])
    cutdefs.append(["nb==0"                , "btagsf"])
    cutdefs.append(["MllSS > 30."          , ""      ])
    cutdefs.append(["MET.pt()>40."         , ""      ])
    cutdefs.append(["MTmax>90."            , ""      ])
    cutdefs.append(["MjjL<400."            , ""      ])
    cutdefs.append(["Detajj<1.5"           , ""      ])
    cutdefs.append(["Mjj>60.&&Mjj<100."    , ""      ])
    addCuts(base, prefix, cutdefs)

#_______________________________________________________________________________________
def addSSmmCuts(base, prefix, preselcut=SSpreselcut, preselwgt=SSpreselwgt):
    cutdefs = []
    cutdefs.append([preselcut              , preselwgt])
    cutdefs.append(["nj>=2"                , ""      ])
    cutdefs.append(["nb==0"                , "btagsf"])
    cutdefs.append(["MllSS > 40."          , ""      ])
    cutdefs.append(["MjjL<400."            , ""      ])
    cutdefs.append(["Detajj<1.5"           , ""      ])
    cutdefs.append(["Mjj>60.&&Mjj<100."    , ""      ])
    addCuts(base, prefix, cutdefs)

########################################################################################
#
#
# Three Lepton Regions
#
#
########################################################################################

# Common cuts and weights
TLpreselcuts = [
        configuration_cut,
        typebkg_3l_configuration_cut,
        #"pass_offline_trig>0",
        "n_veto_3l_lep==3",
        "vetophoton3l==0",
        "n_tight_3l_lep=={\"$(path)\"==\"/fake\"?2:3}", # Fake estimation specific
        "n_loose_3l_lep==3",
        "ntrk==0"
        ]
TLpreselcut = "({})".format(")*(".join(TLpreselcuts))
TLpreselwgt = "trigsf*({\"$(path)\"==\"/fake\"?ffwgtss:1})"

#_______________________________________________________________________________________
def addTL0SFOSCuts(base, prefix):
    cutdefs = []
    preselcut = TLpreselcut
    preselwgt = TLpreselwgt
    cutdefs.append([preselcut                 , preselwgt])
    cutdefs.append(["nj30<=1"                 , ""       ])
    cutdefs.append(["nb==0"                   , "btagsf" ])
    cutdefs.append(["Pt3l>60."                , ""       ])
    cutdefs.append(["DPhi3lMET>2.7"           , ""       ])
    cutdefs.append(["abs(M3l-91.1876)>10"     , ""       ])
    cutdefs.append(["Mll0SFOS > 20."          , ""       ])
    cutdefs.append(["abs(Mee0SFOS-91.1876)>15", ""       ])
    addCuts(base, prefix, cutdefs)

#_______________________________________________________________________________________
def addTL1SFOSCuts(base, prefix):
    cutdefs = []
    preselcut = TLpreselcut
    preselwgt = TLpreselwgt
    cutdefs.append([preselcut                  , preselwgt])
    cutdefs.append(["nj30<=1"                  , ""       ])
    cutdefs.append(["nb==0"                    , "btagsf" ])
    cutdefs.append(["Pt3l>60."                 , ""       ])
    cutdefs.append(["DPhi3lMET>2.5"            , ""       ])
    cutdefs.append(["abs(M3l-91.1876)>10"      , ""       ])
    cutdefs.append(["MET.pt() > 45"            , ""       ])
    cutdefs.append(["Mll1SFOS > 20."           , ""       ])
    cutdefs.append(["Mll1SFOS<55||Mll1SFOS>110", ""       ])
    addCuts(base, prefix, cutdefs)

#_______________________________________________________________________________________
def addTL2SFOSCuts(base, prefix):
    cutdefs = []
    preselcut = TLpreselcut
    preselwgt = TLpreselwgt
    cutdefs.append([preselcut                   , preselwgt])
    cutdefs.append(["nj30<=1"                   , ""       ])
    cutdefs.append(["nb==0"                     , "btagsf" ])
    cutdefs.append(["Pt3l>60."                  , ""       ])
    cutdefs.append(["DPhi3lMET>2.5"             , ""       ])
    cutdefs.append(["abs(M3l-91.1876)>10"       , ""       ])
    cutdefs.append(["MET.pt() > 55"             , ""       ])
    cutdefs.append(["Mll2SFOS0 > 20."           , ""       ])
    cutdefs.append(["Mll2SFOS1 > 20."           , ""       ])
    cutdefs.append(["abs(Mll2SFOS0-91.1876)>20.", ""       ])
    cutdefs.append(["abs(Mll2SFOS1-91.1876)>20.", ""       ])
    addCuts(base, prefix, cutdefs)

########################################################################################
#
#
# Same-Sign WZ Control regions
#
#
########################################################################################

# Common cuts and weights
SSWZpreselcuts = [
        configuration_cut,
        typebkg_3l_configuration_cut,
        #"pass_offline_trig>0",
        "n_veto_3l_lep==3",
        "vetophoton3l==0",
        "n_tight_ss_lep>=2",
        "n_tight_3l_lep==3",
        "n_loose_3l_lep==3",
        "ntrk==0"
        ]
SSWZpreselcut = "({})".format(")*(".join(SSWZpreselcuts))
SSWZpreselwgt = "trigsf*({\"$(path)\"==\"/fake\"?ffwgtss:1})"

#_______________________________________________________________________________________
def addWZCReeCuts(base, prefix):
    preselcut = SSWZpreselcut + "*(abs(MllSS-91.1876)>10)"
    preselwgt = SSWZpreselwgt
    addSSeeCuts(base, prefix, preselcut, preselwgt)

#_______________________________________________________________________________________
def addWZCRemCuts(base, prefix):
    preselcut = SSWZpreselcut
    preselwgt = SSWZpreselwgt
    addSSemCuts(base, prefix, preselcut, preselwgt)

#_______________________________________________________________________________________
def addWZCRmmCuts(base, prefix):
    preselcut = SSWZpreselcut
    preselwgt = SSWZpreselwgt
    addSSmmCuts(base, prefix, preselcut, preselwgt)

#_______________________________________________________________________________________
def getSSeeCuts   (region_prefix, extracut=None): return getCuts(region_prefix, "lep_flav_prod_ss==121", "weight*lepsf*purewgt", addSSeeCuts    , extracut)
def getSSemCuts   (region_prefix, extracut=None): return getCuts(region_prefix, "lep_flav_prod_ss==143", "weight*lepsf*purewgt", addSSemCuts    , extracut)
def getSSmmCuts   (region_prefix, extracut=None): return getCuts(region_prefix, "lep_flav_prod_ss==169", "weight*lepsf*purewgt", addSSmmCuts    , extracut)
def getWZCReeCuts (region_prefix, extracut=None): return getCuts(region_prefix, "lep_flav_prod_3l==121", "weight*lepsf*purewgt", addWZCReeCuts  , extracut)
def getWZCRemCuts (region_prefix, extracut=None): return getCuts(region_prefix, "lep_flav_prod_3l==143", "weight*lepsf*purewgt", addWZCRemCuts  , extracut)
def getWZCRmmCuts (region_prefix, extracut=None): return getCuts(region_prefix, "lep_flav_prod_3l==169", "weight*lepsf*purewgt", addWZCRmmCuts  , extracut)
def getTL0SFOSCuts(region_prefix, extracut=None): return getCuts(region_prefix, "nSFOS==0"             , "weight*lepsf*purewgt", addTL0SFOSCuts , extracut)
def getTL1SFOSCuts(region_prefix, extracut=None): return getCuts(region_prefix, "nSFOS==1"             , "weight*lepsf*purewgt", addTL1SFOSCuts , extracut)
def getTL2SFOSCuts(region_prefix, extracut=None): return getCuts(region_prefix, "nSFOS==2"             , "weight*lepsf*purewgt", addTL2SFOSCuts , extracut)

#_______________________________________________________________________________________
def addTypeBasedCuts(base, reg, bkg_types, prockey, func):
    for bkg_type in bkg_types:
        base.addCut(func("{}_{}".format(reg, bkg_type), TQCut("chan_{}_{}".format(reg, bkg_type), "chan_{}_{}".format(reg, bkg_type), "process_name_{}==\"{}\"".format(prockey, bkg_type))))
    base.addCut(func("{}_WWW" .format(reg), TQCut("chan_{}_WWW" .format(reg), "chan_{}_WWW" .format(reg), "sample_name==\"WWW\"||sample_name==\"WHtoWWW\"")))
    base.addCut(func("{}_Bkg" .format(reg), TQCut("chan_{}_Bkg" .format(reg), "chan_{}_Bkg" .format(reg), "(sample_name!=\"WWW\"&&sample_name!=\"WHtoWWW\"&&sample_name!=\"DataMM\"&&sample_name!=\"DataEM\"&&sample_name!=\"DataEE\")")))
    base.addCut(func("{}_Data".format(reg), TQCut("chan_{}_Data".format(reg), "chan_{}_Data".format(reg), "process_name_{}==\"Data\"".format(prockey))))

#_______________________________________________________________________________________
def addAllSSeeCuts   (base): base.addCut(getSSeeCuts   ("SSee"   ))
def addAllSSemCuts   (base): base.addCut(getSSemCuts   ("SSem"   ))
def addAllSSmmCuts   (base): base.addCut(getSSmmCuts   ("SSmm"   ))
def addAllTL0SFOSCuts(base): base.addCut(getTL0SFOSCuts("TL0SFOS"))
def addAllTL1SFOSCuts(base): base.addCut(getTL1SFOSCuts("TL1SFOS"))
def addAllTL2SFOSCuts(base): base.addCut(getTL2SFOSCuts("TL2SFOS"))
def addAllWZCReeCuts (base): base.addCut(getWZCReeCuts ("WZCRee" ))
def addAllWZCRemCuts (base): base.addCut(getWZCRemCuts ("WZCRem" ))
def addAllWZCRmmCuts (base): base.addCut(getWZCRmmCuts ("WZCRmm" ))

#_______________________________________________________________________________________
def addAllCuts(base):
    addAllSSeeCuts(base)
    addAllSSemCuts(base)
    addAllSSmmCuts(base)
    addAllTL0SFOSCuts(base)
    addAllTL1SFOSCuts(base)
    addAllTL2SFOSCuts(base)
    addAllWZCReeCuts(base)
    addAllWZCRemCuts(base)
    addAllWZCRmmCuts(base)

#_______________________________________________________________________________________
def getAllCuts():
    base = TQCut("BaseCut", "BaseCut", "1", "1")
    addAllCuts(base)
    return base

