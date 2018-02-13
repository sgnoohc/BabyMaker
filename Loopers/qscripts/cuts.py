import ROOT
from QFramework import TQCut

#######################################################################################
# Configuration variables
#######################################################################################
doSyst = False

# Category separations
bkg_types_SS = ["trueSS", "chargeflips", "SSLL", "fakes", "photonfakes", "others"]
bkg_types_3L = ["trueWWW", "true3L", "chargeflips", "3lLL", "fakes", "photonfakes", "others"]

#_______________________________________________________________________________________
def combexpr(exprlist):
    exprlist = [ expr if len(expr) != 0 else "1" for expr in exprlist ]
    return "({})".format(")*(".join(exprlist))

########################################################################################
#
#
# Preliminary selections
#
#
########################################################################################

# The following string is used to define the base weights including the systematic weights.
weight_expressions = [
"weight*lepsf*purewgt",
#"{\"$(variation)\"==\"lepsfup\"?(lepsf+lepsf_err)/lepsf:1}",
#"{\"$(variation)\"==\"lepsfdn\"?(lepsf-lepsf_err)/lepsf:1}",
#"{\"$(variation)\"==\"purewgtup\"?purewgt_up/purewgt:1}",
#"{\"$(variation)\"==\"purewgtdn\"?purewgt_dn/purewgt:1}",
]
weight_expression = combexpr(weight_expressions)

# The following string is used to define the btagging weight
btagwgt_expressions = [
"btagsf",
#"{\"$(variation)\"==\"btaghfup\"?btagsf_hfup:1}",
#"{\"$(variation)\"==\"btaghfdn\"?btagsf_hfdn:1}",
#"{\"$(variation)\"==\"btaglfup\"?btagsf_lfup:1}",
#"{\"$(variation)\"==\"btaglfdn\"?btagsf_lfdn:1}",
]
btagwgt = combexpr(btagwgt_expressions)

# The following string is used to define the fakerate weight and trigger sf
preselwgt_ss_expressions = [
"trigsf",
"{$(usefakeweight)?{\"$(variation)\"==\"fakeup\"?ffwgtss+ffwgtss_err:{\"$(variation)\"==\"fakedn\"?ffwgtss-ffwgtss_err:ffwgtss}}:1}",
]
preselwgt_ss_expression = combexpr(preselwgt_ss_expressions)

preselwgt_3l_expressions = [
"trigsf",
"{$(usefakeweight)?{\"$(variation)\"==\"fakeup\"?ffwgt3l+ffwgt3l_err:{\"$(variation)\"==\"fakedn\"?ffwgt3l-ffwgt3l_err:ffwgt3l}}:1}"
]
preselwgt_3l_expression = combexpr(preselwgt_3l_expressions)

# Variations
commonsystvarwgt = [
["lepsfup"   , "{$(usefakeweight)?1:(lepsf+lepsf_err)/lepsf}"],
["lepsfdn"   , "{$(usefakeweight)?1:(lepsf-lepsf_err)/lepsf}"], 
["purewgtup" , "{$(usefakeweight)?1:purewgt_up/purewgt}"], 
["purewgtdn" , "{$(usefakeweight)?1:purewgt_dn/purewgt}"], 
["btaghfup"  , "{$(usefakeweight)?1:btagsf_hfup}"], 
["btaghfdn"  , "{$(usefakeweight)?1:btagsf_hfdn}"], 
["btaglfup"  , "{$(usefakeweight)?1:btagsf_lfup}"], 
["btaglfdn"  , "{$(usefakeweight)?1:btagsf_lfdn}"], 
]

systvarwgtss = commonsystvarwgt
#systvarwgtss.extend([["fakeup", "(ffwgtss+ffwgtss_err)/ffwgtss"], ["fakedn", "(ffwgtss-ffwgtss_err)/ffwgtss"]])

systvarwgt3l = commonsystvarwgt
#systvarwgt3l.extend([["fakeup", "(ffwgt3l+ffwgt3l_err)/ffwgt3l"], ["fakedn", "(ffwgt3l-ffwgt3l_err)/ffwgt3l"]])


# The following cut is used to split the vh sample.
# Our current signal is defined to include WH->WWW process, however we do not have a signal sample with just WHWWW.
# So we split the VH->non-bb sample and select only the WH->WWW as signal.
# So the following obscure and inconvenient cut is applied.
# Basically if the looper is running for signal events, accept only the events that has the TString branch "sample_name" equal to "WHtoWWW".
# When the looper is running for background events select when "sample_name" branch is not equal to "WHtoWWW".
whwww_configuration_cut = "({\"$(path)\"==\"/sig/whwww\"?sample_name==\"WHtoWWW\":1})*({\"$(path)\"==\"/bkg/VVV/whwww\"?sample_name!=\"WHtoWWW\":1})" # WHtoWWW sample specific
trigger_configuration_cut = "{(process_name_ss==\"Data\"||process_name_3l==\"Data\")?pass_online_trig>0:1}"
configuration_cut = combexpr([whwww_configuration_cut, trigger_configuration_cut])

# The following cut is used to split the SS and 3L channel events.
# The ttree's are split by types but the 3L and SS events have some overlaps in the TTree.
# So per given TTree (e.g. t_prompt, t_qflip, t_fakes, etc.) one needs to use "process_name_ss" or "process_name_3l" branches to filter events.
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
"{\"$(path)\"==\"/closure/fake/ttbar\"?process_name_ss==\"fakes\":1}",
"{\"$(path)\"==\"/closure/fake/W\"?process_name_ss==\"fakes\":1}",
"{\"$(path)\"==\"/closure/mc/ttbar\"?process_name_ss==\"fakes\":1}",
"{\"$(path)\"==\"/closure/mc/W\"?process_name_ss==\"fakes\":1}",
]
typebkg_ss_configuration_cut = combexpr(typebkg_ss_configuration_cuts)
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
typebkg_3l_configuration_cut = combexpr(typebkg_3l_configuration_cuts)

# WZCR building off of SS regions.
# WZCR for SS regions will drop, Mjj window cut and add Z mass window cut + three lepton selection.
ss_wzcr_z_window_cut = "(nj30>=2)*((nSFOS==1)*(abs(Mll1SFOS-91.1876)<10)+(nSFOS==2)*(abs(Mll2SFOS0-91.1876)<10||abs(Mll2SFOS1-91.1876)<10))+(nj30==1)*(MET.pt()<45.)"

########################################################################################
#
#
# Utility functions
#
#
########################################################################################

#_______________________________________________________________________________________
def addCuts(base, prefix_base, cutdefs, systvarwgts=[], doNm1=True):
    cuts = []
    prefix = prefix_base.split("base_")[1]
    for i, cutdef in enumerate(cutdefs):
        cutname = "cut{}_{}".format(i, prefix)
        if i == len(cutdefs) - 1 :
            cutname = "{}".format(prefix)
        cut = TQCut(cutname, cutname, cutdef[0], cutdef[1])
        if doSyst:
            # If last cut add a whole bunch of systematic variations
            if i == len(cutdefs) - 1 :
                for systvarwgt in systvarwgts:
                    systname = systvarwgt[0]
                    systwgt  = systvarwgt[1]
                    cut.addCut(TQCut(cutname + "_" + systname, cutname + "_" + systname, "1", systwgt))
        cuts.append(cut)
    for i in xrange(len(cuts) - 1):
        cuts[i].addCut(cuts[i+1])
    base.addCut(cuts[0])
    if doNm1:
        for i, cutdef in enumerate(cutdefs):
            nm1cuts = [ cut[0] for j, cut in enumerate(cutdefs) if j!=i]
            nm1wgts = [ cut[1] for j, cut in enumerate(cutdefs) if j!=i]
            cutname = "{}_minus_{}".format(prefix, i)
            base.addCut(TQCut(cutname, cutname, combexpr(nm1cuts), combexpr(nm1wgts)))

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
        "n_tight_ss_lep=={$(usefakeweight)?1:2}", # Fake estimation specific
        "n_loose_ss_lep==2",
        "ntrk==0",
        "veto_ss_lep0.Pt()>20.",
        "veto_ss_lep1.Pt()>20.",
        "(abs(veto_ss_lep1_pdgid)==13)*(veto_ss_lep1_ptratio>0.9)+(abs(veto_ss_lep1_pdgid)!=13)*(1)",
#        "veto_ss_lep0_bdt1>(0.6 + 0.004*(55 - 1))",
#        "veto_ss_lep1_bdt1>(0.6 + 0.004*(45 - 1))",
        ]
SSpreselcut = combexpr(SSpreselcuts)
SSpreselwgt = preselwgt_ss_expression

#_______________________________________________________________________________________
def addSSeeCuts(base, prefix, preselcut=SSpreselcut + "*(abs(MllSS-91.1876)>10)", preselwgt=SSpreselwgt, doWZCR=False):
    cutdefs = []
    cutdefs.append(           [preselcut           , preselwgt])
    cutdefs.append(           ["nj30>=2"           , ""       ])
    cutdefs.append(           ["nb==0"             , btagwgt  ])
    cutdefs.append(           ["MllSS > 40."       , ""       ])
    cutdefs.append(           ["MET.Pt()>40."      , ""       ])
    cutdefs.append(           ["MjjL<400."         , ""       ])
    cutdefs.append(           ["Detajj<1.5"        , ""       ])
    if doWZCR: cutdefs.append([ss_wzcr_z_window_cut, ""       ])
    else:      cutdefs.append(["Mjj>60.&&Mjj<100." , ""       ])
    if doWZCR: addCuts(base, prefix, cutdefs, systvarwgt3l)
    else:      addCuts(base, prefix, cutdefs, systvarwgtss)

#_______________________________________________________________________________________
def addSSemCuts(base, prefix, preselcut=SSpreselcut, preselwgt=SSpreselwgt, doWZCR=False):
    cutdefs = []
    cutdefs.append(           [preselcut           , preselwgt])
    cutdefs.append(           ["nj30>=2"           , ""       ])
    cutdefs.append(           ["nb==0"             , btagwgt  ])
    cutdefs.append(           ["MllSS > 30."       , ""       ])
    cutdefs.append(           ["MET.pt()>40."      , ""       ])
    cutdefs.append(           ["MTmax>90."         , ""       ])
    cutdefs.append(           ["MjjL<400."         , ""       ])
    cutdefs.append(           ["Detajj<1.5"        , ""       ])
    if doWZCR: cutdefs.append([ss_wzcr_z_window_cut, ""       ])
    else:      cutdefs.append(["Mjj>60.&&Mjj<100." , ""       ])
    if doWZCR: addCuts(base, prefix, cutdefs, systvarwgt3l)
    else:      addCuts(base, prefix, cutdefs, systvarwgtss)

#_______________________________________________________________________________________
def addSSmmCuts(base, prefix, preselcut=SSpreselcut, preselwgt=SSpreselwgt, doWZCR=False):
    cutdefs = []
    cutdefs.append(           [preselcut           , preselwgt])
    cutdefs.append(           ["nj30>=2"           , ""       ])
    cutdefs.append(           ["nb==0"             , btagwgt  ])
    cutdefs.append(           ["MllSS > 40."       , ""       ])
    cutdefs.append(           ["MjjL<400."         , ""       ])
    cutdefs.append(           ["Detajj<1.5"        , ""       ])
    if doWZCR: cutdefs.append([ss_wzcr_z_window_cut, ""       ])
    else:      cutdefs.append(["Mjj>60.&&Mjj<100." , ""       ])
    if doWZCR: addCuts(base, prefix, cutdefs, systvarwgt3l)
    else:      addCuts(base, prefix, cutdefs, systvarwgtss)

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
        "n_tight_3l_lep=={$(usefakeweight)?2:3}", # Fake estimation specific
        "n_loose_3l_lep==3",
        "ntrk==0"
        ]
TLpreselcut = combexpr(TLpreselcuts)
TLpreselwgt = preselwgt_3l_expression

#_______________________________________________________________________________________
def addTL0SFOSCuts(base, prefix, preselcut=TLpreselcut, preselwgt=TLpreselwgt):
    cutdefs = []
    cutdefs.append([preselcut                 , preselwgt])
    cutdefs.append(["nj30<=1"                 , ""       ])
    cutdefs.append(["nb==0"                   , btagwgt  ])
    cutdefs.append(["Pt3l>60."                , ""       ])
    cutdefs.append(["DPhi3lMET>2.7"           , ""       ])
    cutdefs.append(["abs(M3l-91.1876)>10"     , ""       ])
    cutdefs.append(["Mll0SFOS > 20."          , ""       ])
    cutdefs.append(["abs(Mee0SFOS-91.1876)>15", ""       ])
    addCuts(base, prefix, cutdefs, systvarwgt3l)

#_______________________________________________________________________________________
def addTL1SFOSCuts(base, prefix, preselcut=TLpreselcut, preselwgt=TLpreselwgt, invertZ=False):
    cutdefs = []
    cutdefs.append([preselcut                  , preselwgt])
    cutdefs.append(["nj30<=1"                  , ""       ])
    cutdefs.append(["nb==0"                    , btagwgt  ])
    cutdefs.append(["Pt3l>60."                 , ""       ])
    cutdefs.append(["DPhi3lMET>2.5"            , ""       ])
    cutdefs.append(["abs(M3l-91.1876)>10"      , ""       ])
    cutdefs.append(["MET.pt() > 45"            , ""       ])
    cutdefs.append(["Mll1SFOS > 20."           , ""       ])
    #cutdefs.append(["MT1SFOS  > 85."           , ""       ])
    if invertZ: cutdefs.append(["Mll1SFOS>55&&Mll1SFOS<110", ""       ])
    else:       cutdefs.append(["Mll1SFOS<55||Mll1SFOS>110", ""       ])
    addCuts(base, prefix, cutdefs, systvarwgt3l)

#_______________________________________________________________________________________
def addTL2SFOSCuts(base, prefix, preselcut=TLpreselcut, preselwgt=TLpreselwgt, invertZ=False):
    cutdefs = []
    cutdefs.append([preselcut                   , preselwgt])
    cutdefs.append(["nj30<=1"                   , ""       ])
    cutdefs.append(["nb==0"                     , btagwgt  ])
    cutdefs.append(["Pt3l>60."                  , ""       ])
    cutdefs.append(["DPhi3lMET>2.5"             , ""       ])
    cutdefs.append(["abs(M3l-91.1876)>10"       , ""       ])
    cutdefs.append(["MET.pt() > 55"             , ""       ])
    cutdefs.append(["Mll2SFOS0 > 20."           , ""       ])
    cutdefs.append(["Mll2SFOS1 > 20."           , ""       ])
    if invertZ:
        cutdefs.append(["abs(Mll2SFOS0-91.1876)<20.||abs(Mll2SFOS1-91.1876)<20.", ""       ])
    else:
        cutdefs.append(["abs(Mll2SFOS0-91.1876)>20.", ""       ])
        cutdefs.append(["abs(Mll2SFOS1-91.1876)>20.", ""       ])
    addCuts(base, prefix, cutdefs, systvarwgt3l)

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
        typebkg_ss_configuration_cut,
        #"pass_offline_trig>0",
        "n_veto_3l_lep==3",
        "vetophoton3l==0",
        "n_tight_ss_lep>=2",
        "n_tight_3l_lep==3",
        "n_loose_3l_lep==3",
        "ntrk==0"
        ]
SSWZpreselcut = combexpr(SSWZpreselcuts)
SSWZpreselwgt = preselwgt_3l_expression

#_______________________________________________________________________________________
def addWZCReeCuts(base, prefix):
    preselcut = SSWZpreselcut + "*(abs(MllSS-91.1876)>10)"
    preselwgt = SSWZpreselwgt
    addSSeeCuts(base, prefix, preselcut, preselwgt, doWZCR=True)

#_______________________________________________________________________________________
def addWZCRemCuts(base, prefix):
    preselcut = SSWZpreselcut
    preselwgt = SSWZpreselwgt
    addSSemCuts(base, prefix, preselcut, preselwgt, doWZCR=True)

#_______________________________________________________________________________________
def addWZCRmmCuts(base, prefix):
    preselcut = SSWZpreselcut
    preselwgt = SSWZpreselwgt
    addSSmmCuts(base, prefix, preselcut, preselwgt, doWZCR=True)

########################################################################################
#
#
# Three Lepton WZ CR
#
#
########################################################################################

# Common cuts and weights
TLWZpreselcuts = [
        configuration_cut,
        typebkg_3l_configuration_cut,
        #"pass_offline_trig>0",
        #"n_veto_3l_lep==3", # Three lepton WZCR drops the veto lepton requirement
        "vetophoton3l==0",
        "n_tight_3l_lep=={$(usefakeweight)?2:3}", # Fake estimation specific
        "n_loose_3l_lep==3",
        "ntrk==0"
        ]
TLWZpreselcut = combexpr(TLWZpreselcuts)
TLWZpreselwgt = preselwgt_3l_expression

#_______________________________________________________________________________________
def addTLWZ1SFOSCuts(base, prefix):
    preselcut = TLWZpreselcut
    preselwgt = TLWZpreselwgt
    addTL1SFOSCuts(base, prefix, preselcut, preselwgt, invertZ=True)

#_______________________________________________________________________________________
def addTLWZ2SFOSCuts(base, prefix):
    preselcut = TLWZpreselcut
    preselwgt = TLWZpreselwgt
    addTL2SFOSCuts(base, prefix, preselcut, preselwgt, invertZ=True)

#_______________________________________________________________________________________
def getSSeeCuts     (region_prefix, extracut=None): return getCuts(region_prefix, "lep_flav_prod_ss==121", weight_expression, addSSeeCuts      , extracut)
def getSSemCuts     (region_prefix, extracut=None): return getCuts(region_prefix, "lep_flav_prod_ss==143", weight_expression, addSSemCuts      , extracut)
def getSSmmCuts     (region_prefix, extracut=None): return getCuts(region_prefix, "lep_flav_prod_ss==169", weight_expression, addSSmmCuts      , extracut)
def getWZCReeCuts   (region_prefix, extracut=None): return getCuts(region_prefix, "lep_flav_prod_3l==121", weight_expression, addWZCReeCuts    , extracut)
def getWZCRemCuts   (region_prefix, extracut=None): return getCuts(region_prefix, "lep_flav_prod_3l==143", weight_expression, addWZCRemCuts    , extracut)
def getWZCRmmCuts   (region_prefix, extracut=None): return getCuts(region_prefix, "lep_flav_prod_3l==169", weight_expression, addWZCRmmCuts    , extracut)
def getTL0SFOSCuts  (region_prefix, extracut=None): return getCuts(region_prefix, "nSFOS==0"             , weight_expression, addTL0SFOSCuts   , extracut)
def getTL1SFOSCuts  (region_prefix, extracut=None): return getCuts(region_prefix, "nSFOS==1"             , weight_expression, addTL1SFOSCuts   , extracut)
def getTL2SFOSCuts  (region_prefix, extracut=None): return getCuts(region_prefix, "nSFOS==2"             , weight_expression, addTL2SFOSCuts   , extracut)
def getTLWZ1SFOSCuts(region_prefix, extracut=None): return getCuts(region_prefix, "nSFOS==1"             , weight_expression, addTLWZ1SFOSCuts , extracut)
def getTLWZ2SFOSCuts(region_prefix, extracut=None): return getCuts(region_prefix, "nSFOS==2"             , weight_expression, addTLWZ2SFOSCuts , extracut)

#_______________________________________________________________________________________
def addTypeBasedCuts(base, reg, bkg_types, prockey, func):
    for bkg_type in bkg_types:
        base.addCut(func("{}_{}".format(reg, bkg_type), TQCut("chan_{}_{}".format(reg, bkg_type), "chan_{}_{}".format(reg, bkg_type), "process_name_{}==\"{}\"".format(prockey, bkg_type))))
    base.addCut(func("{}_WWW" .format(reg), TQCut("chan_{}_WWW" .format(reg), "chan_{}_WWW" .format(reg), "sample_name==\"WWW\"||sample_name==\"WHtoWWW\"")))
    base.addCut(func("{}_Bkg" .format(reg), TQCut("chan_{}_Bkg" .format(reg), "chan_{}_Bkg" .format(reg), "(sample_name!=\"WWW\"&&sample_name!=\"WHtoWWW\"&&sample_name!=\"DataMM\"&&sample_name!=\"DataEM\"&&sample_name!=\"DataEE\")")))
    base.addCut(func("{}_Data".format(reg), TQCut("chan_{}_Data".format(reg), "chan_{}_Data".format(reg), "process_name_{}==\"Data\"".format(prockey))))

#_______________________________________________________________________________________
def addAllSSeeCuts     (base): base.addCut(getSSeeCuts     ("SSee"     ))
def addAllSSemCuts     (base): base.addCut(getSSemCuts     ("SSem"     ))
def addAllSSmmCuts     (base): base.addCut(getSSmmCuts     ("SSmm"     ))
def addAllTL0SFOSCuts  (base): base.addCut(getTL0SFOSCuts  ("TL0SFOS"  ))
def addAllTL1SFOSCuts  (base): base.addCut(getTL1SFOSCuts  ("TL1SFOS"  ))
def addAllTL2SFOSCuts  (base): base.addCut(getTL2SFOSCuts  ("TL2SFOS"  ))
def addAllWZCReeCuts   (base): base.addCut(getWZCReeCuts   ("WZCRee"   ))
def addAllWZCRemCuts   (base): base.addCut(getWZCRemCuts   ("WZCRem"   ))
def addAllWZCRmmCuts   (base): base.addCut(getWZCRmmCuts   ("WZCRmm"   ))
def addAllTLWZ1SFOSCuts(base): base.addCut(getTLWZ1SFOSCuts("TLWZ1SFOS"))
def addAllTLWZ2SFOSCuts(base): base.addCut(getTLWZ2SFOSCuts("TLWZ2SFOS"))

#_______________________________________________________________________________________
def addAllCuts(base):
    addAllSSeeCuts(base)
    addAllSSemCuts(base)
    addAllSSmmCuts(base)
    #addAllTL0SFOSCuts(base)
    #addAllTL1SFOSCuts(base)
    #addAllTL2SFOSCuts(base)
    addAllWZCReeCuts(base)
    addAllWZCRemCuts(base)
    addAllWZCRmmCuts(base)
    #addAllTLWZ1SFOSCuts(base)
    #addAllTLWZ2SFOSCuts(base)

#_______________________________________________________________________________________
def getAllCuts():
    base = TQCut("BaseCut", "BaseCut", "1", "1")
    base.addCut(TQCut("dummy", "dummy", "0", "1"))
    addAllCuts(base)
    return base

