#!/bin/env python

import os
import sys
import ROOT
from QFramework import TQSampleFolder, TQXSecParser, TQCut, TQAnalysisSampleVisitor, TQSampleInitializer, TQCutflowAnalysisJob, TQCutflowPrinter, TQHistoMakerAnalysisJob
from rooutil.qutils import *
from errors import E

#filename = "output_sf_applied.root"
#filename = "output.root"
filename = sys.argv[1]

ROOT.gROOT.SetBatch(True)
samples = TQSampleFolder.loadSampleFolder("{}:samples".format(filename))

########################################################################################
def getWZNF(cutname):
    wz = samples.getCounter("/typebkg/lostlep", cutname)
    nf = samples.getCounter("/data-typebkg/[qflip+photon+prompt+fakes]-sig", cutname)
    nf.divide(wz)
    return nf.getCounter(), nf.getError()

########################################################################################
def blind():
    cutnames = []
    for i in samples.getListOfCounterNames():
        cutnames.append(str(i))
    cutnames.sort(key=natural_keys)
    for cutname in cutnames:
        if not (cutname.find("AR") != -1 or cutname.find("CR") != -1):
            samples.setScaleFactor(cutname, 0, 0, "/data")

########################################################################################
def addProcesses(printer, showdata, prettyversion=True):
    #printer.addCutflowProcess("$signif(/sig,/typebkg)", "Signif. (MC)")
    #printer.addCutflowProcess("$signif(/sig,/fake+typebkg/prompt+typebkg/qflip+typebkg/photon+typebkg/lostlep)", "Signif. (w/ Fake est.)")
    printer.addCutflowProcess("|", "|")

    ## Wprime sample
    #wprimemasses = [600,800,1000,1200,1400,1600,1800,2000,2500,3500,4000,4500,5000,5500,6000]
    #for wprimemass in wprimemasses:
    #    printer.addCutflowProcess("/bsm/wprime/{}".format(wprimemass), "W'[{}]".format(wprimemass))

    ## Doubly charged higgs samples
    #hpmpmmasses = [200,300,400,500,600,900,1000,1500,2000]
    #for hpmpmmass in hpmpmmasses:
    #    printer.addCutflowProcess("/bsm/hpmpm/{}".format(hpmpmmass), "H++[{}]".format(hpmpmmass))

    ## SUSY c1n2->WH + LSPs samples
    #chimasses = [125 + i*25 for i in xrange(13) ]
    #for chimass in chimasses:
    #    # The LSP mass scans are defined as the following
    #    lspmasses = [ i*25 for i in xrange(((chimass - 125) / 25) + 1) ]
    #    if len(lspmasses) > 1:
    #        lspmasses[0] = lspmasses[0] + 1
    #        lspmasses[-1] = lspmasses[-1] - 1
    #    else:
    #        lspmasses[0] = lspmasses[0] + 1
    #    if chimass == 125: chimass = 127
    #    for lspmass in lspmasses:
    #        printer.addCutflowProcess("/bsm/whsusy/{}/{}".format(chimass, lspmass), "({},{})".format(chimass, lspmass))

    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("/sig", "WWW")
    printer.addCutflowProcess("/sig/www", "non-higgs")
    printer.addCutflowProcess("/sig/whwww", "higgs")
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("/typebkg/prompt", "Prompt")
    printer.addCutflowProcess("/typebkg/qflip", "Charge flip")
    printer.addCutflowProcess("/typebkg/photon", "Photon")
    printer.addCutflowProcess("/typebkg/lostlep", "Lost-lep.")
    printer.addCutflowProcess("/fake", "Fakes (Data-Driv.)")
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("/fake+typebkg/prompt+typebkg/qflip+typebkg/photon+typebkg/lostlep", "Bkg. w/ est.")
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("/fakeup", "Fakes syst up")
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("/typebkg/?", "Bkg. (MC)")
    printer.addCutflowProcess("/typebkg/fakes", "Fakes (MC)")
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("/typebkg/?/ttW", "ttW")
    printer.addCutflowProcess("/typebkg/?/VBSWW", "VBSWW")
    printer.addCutflowProcess("/typebkg/?/ttZ", "ttZ")
    printer.addCutflowProcess("/typebkg/?/WZ", "WZ")
    printer.addCutflowProcess("/typebkg/?/Other/top", "top")
    printer.addCutflowProcess("/typebkg/?/Other/ttV", "tth+ttgamma")
    printer.addCutflowProcess("/typebkg/?/Other/W", "W")
    printer.addCutflowProcess("/typebkg/?/Other/Z", "Z")
    printer.addCutflowProcess("/typebkg/?/Other/VV", "other diboson")
    printer.addCutflowProcess("/typebkg/?/Other/VVV", "other triboson")
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("typebkg/prompt+typebkg/qflip+typebkg/photon+typebkg/lostlep", "Prompt")
    printer.addCutflowProcess("$ratio(typebkg/prompt+typebkg/qflip+typebkg/photon+typebkg/lostlep, /typebkg)", "Prompt Contamination")
#    printer.addCutflowProcess("|", "|")
#    printer.addCutflowProcess("/typebkg/?/Other/top/singletop/tzq_ll_amcnlo", "tzq")
    printer.addCutflowProcess("|", "|")
#    printer.addCutflowProcess("|", "|")
#    printer.addCutflowProcess("/bkg/top/singletop", "1top")
#    printer.addCutflowProcess("/bkg/top/ttbar/tt1l", "tt1l")
#    printer.addCutflowProcess("/bkg/top/ttbar/tt2l", "tt2l")
#    printer.addCutflowProcess("/bkg/ttV", "ttV")
#    printer.addCutflowProcess("/bkg/VVV", "VVV")
#    printer.addCutflowProcess("/bkg/VV/ZZ", "ZZ")
#    printer.addCutflowProcess("/bkg/VV/WW", "WW")
#    printer.addCutflowProcess("/bkg/VV/WZ,sys", "WZ")
#    printer.addCutflowProcess("/bkg/W", "W")
#    printer.addCutflowProcess("/bkg/Z", "Z")
#    printer.addCutflowProcess("|", "|")
#    printer.addCutflowProcess("/bkg", "Bkg. (MC)")
#    printer.addCutflowProcess("/bkg-sig/whwww", "Bkg. (MC)")
    if showdata:
        printer.addCutflowProcess("|", "|")
        printer.addCutflowProcess("/data", "Data")
        printer.addCutflowProcess("|", "|")
        #printer.addCutflowProcess("$ratio(/data,/fake+typebkg-typebkg/fakes)", "Ratio")
        printer.addCutflowProcess("$ratio(/data,/typebkg)", "Ratio")
        #printer.addCutflowProcess("$ratio(/data,/fake+typebkg/prompt+typebkg/qflip+typebkg/photon+typebkg/lostlep)", "Ratio")

########################################################################################
#_______________________________________________________________________________
# Supports only printing out by process boundaries
def printCutflow(samples, regionname):
    cuts = {}
    cutkeys = []
    cutnames = {}
    for counter in samples.getListOfCounterNames():
        #if str(counter).find(regionname) != -1 and str(counter).find("cut") != -1:
        if str(counter).find(regionname) != -1:
            title = samples.getCounter("/sig", str(counter)).GetTitle()
            cutkeys.append(str(title)+str(counter))
            cutnames[cutkeys[-1]] = str(counter)
            cuts[str(counter)] = str(title)
    cutkeys.sort(key=natural_keys)
    #cutnames.sort()
    # Cutflow printing
    printer = TQCutflowPrinter(samples)
    for key in cutkeys:
        cut = cutnames[key]
        printer.addCutflowCut(cut, cuts[cut], True)
    addProcesses(printer, showdata=True)
    table = printer.createTable("style.firstColumnAlign=l")
    path = "cutflows/"
    try:
        os.makedirs(path)
    except OSError as exc:  # Python >2.5
        if exc.errno == errno.EEXIST and os.path.isdir(path):
            pass
        else:
            raise
    table.writeCSV("cutflows/{}.csv".format(regionname))
    table.writeHTML("cutflows/{}.html".format(regionname))
    table.writeLaTeX("cutflows/{}.tex".format(regionname))
    table.writePlain("cutflows/{}.txt".format(regionname))

########################################################################################
#_______________________________________________________________________________
# Supports only printing out by process boundaries
def printCutflowSSWZExtrapolation(samples, variation=""):
    regionname = "WZCRExp"+variation
    printer = TQCutflowPrinter(samples)
    printer.addCutflowCut("[CutSSWZeeMllSS+CutSSWZemMllSS+CutSSWZmmMllSS]", "inclusive", True)
    printer.addCutflowCut("[CutSSWZeeMjjWin+CutSSWZemMjjWin+CutSSWZmmMjjWin]"   , "SSWZ Mjj in" , True)
    printer.addCutflowCut("[CutSSWZeeMjjWout+CutSSWZemMjjWout+CutSSWZmmMjjWout]", "SSWZ Mjj out", True)
    printer.addCutflowCut("CutSSeeMllSS", "ee sr", True)
    printer.addCutflowCut("CutSSWZeeMllSS", "ee inclusive", True)
    printer.addCutflowCut("CutSSemMllSS", "em sr", True)
    printer.addCutflowCut("CutSSWZemMllSS", "em inclusive", True)
    printer.addCutflowCut("CutSSmmMllSS", "mm sr", True)
    printer.addCutflowCut("CutSSWZmmMllSS", "mm inclusive", True)
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("/sig/whwww", "WHWWW")
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("/sig", "WWW")
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("/typebkg/lostlep", "Lost-lep (MC)")
    printer.addCutflowProcess("/data-typebkg/fakes-typebkg/prompt-typebkg/qflip-typebkg/photon", "Lost-lep (data)")
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("/typebkg/?", "Bkg. (MC)")
    #printer.addCutflowProcess("/data", "Data")
    #printer.addCutflowProcess("$ratio(/data,/bkg)", "Ratio")

    printer.addCutflowCut("dummy", "TF-ee {}".format(QE(samples,"/typebkg/lostlep","CutSSeeMllSS") / QE(samples,"/typebkg/lostlep","CutSSWZeeMllSS")), True)
    printer.addCutflowCut("dummy", "TF-em {}".format(QE(samples,"/typebkg/lostlep","CutSSemMllSS") / QE(samples,"/typebkg/lostlep","CutSSWZemMllSS")), True)
    printer.addCutflowCut("dummy", "TF-mm {}".format(QE(samples,"/typebkg/lostlep","CutSSmmMllSS") / QE(samples,"/typebkg/lostlep","CutSSWZmmMllSS")), True)

    table = printer.createTable("style.firstColumnAlign=l")

    path = "cutflows/"
    try:
        os.makedirs(path)
    except OSError as exc:  # Python >2.5
        if exc.errno == errno.EEXIST and os.path.isdir(path):
            pass
        else:
            raise
    table.writeCSV("cutflows/{}.csv".format(regionname))
    table.writeHTML("cutflows/{}.html".format(regionname))
    table.writeLaTeX("cutflows/{}.tex".format(regionname))
    table.writePlain("cutflows/{}.txt".format(regionname))

########################################################################################
#_______________________________________________________________________________
# Supports only printing out by process boundaries
def print9SignalRegions(samples):
    printer = TQCutflowPrinter(samples)
    printer.addCutflowCut("SRSSeeFull", "Full Selection: SRSSee", True)
    printer.addCutflowCut("SRSSemFull", "Full Selection: SRSSem", True)
    printer.addCutflowCut("SRSSmmFull", "Full Selection: SRSSmm", True)
    printer.addCutflowCut("|", "|", True)
    printer.addCutflowCut("SideSSeeFull", "Full Selection: SideSSee", True)
    printer.addCutflowCut("SideSSemFull", "Full Selection: SideSSem", True)
    printer.addCutflowCut("SideSSmmFull", "Full Selection: SideSSmm", True)
    printer.addCutflowCut("|", "|", True)
    printer.addCutflowCut("SR0SFOSFull", "Full Selection: SR0SFOS", True)
    printer.addCutflowCut("SR1SFOSFull", "Full Selection: SR1SFOS", True)
    printer.addCutflowCut("SR2SFOSFull", "Full Selection: SR2SFOS", True)
    addProcesses(printer, showdata=True)
    table = printer.createTable("style.firstColumnAlign=l")
    path = "cutflows/"
    try:
        os.makedirs(path)
    except OSError as exc:  # Python >2.5
        if exc.errno == errno.EEXIST and os.path.isdir(path):
            pass
        else:
            raise
    table.writeCSV("cutflows/9signal.csv")
    table.writeHTML("cutflows/9signal.html")
    table.writeLaTeX("cutflows/9signal.tex")
    table.writePlain("cutflows/9signal.txt")

########################################################################################
#_______________________________________________________________________________
# Supports only printing out by process boundaries
def printTable(samples):
    printer = TQCutflowPrinter(samples)
    printer.addCutflowCut("SRSSeeFull", "Full Selection: SRSSee", True)
    printer.addCutflowCut("SRSSemFull", "Full Selection: SRSSem", True)
    printer.addCutflowCut("SRSSmmFull", "Full Selection: SRSSmm", True)
    printer.addCutflowCut("|", "|", True)
    printer.addCutflowCut("SideSSeeFull", "Full Selection: SideSSee", True)
    printer.addCutflowCut("SideSSemFull", "Full Selection: SideSSem", True)
    printer.addCutflowCut("SideSSmmFull", "Full Selection: SideSSmm", True)
    printer.addCutflowCut("|", "|", True)
    printer.addCutflowCut("SR0SFOSFull", "Full Selection: SR0SFOS", True)
    printer.addCutflowCut("SR1SFOSFull", "Full Selection: SR1SFOS", True)
    printer.addCutflowCut("SR2SFOSFull", "Full Selection: SR2SFOS", True)
    printer.addCutflowCut("|", "|", True)
    printer.addCutflowCut("WZCRSSeeFull", "WZCR: SRSSee", True)
    printer.addCutflowCut("WZCRSSemFull", "WZCR: SRSSem", True)
    printer.addCutflowCut("WZCRSSmmFull", "WZCR: SRSSmm", True)
    printer.addCutflowCut("|", "|", True)
    printer.addCutflowCut("WZCR1SFOSFull", "WZCR: SR1SFOS", True)
    printer.addCutflowCut("WZCR2SFOSFull", "WZCR: SR2SFOS", True)
    printer.addCutflowCut("|", "|", True)
    printer.addCutflowCut("SRSSeePre", "Pre Selection: SRSSee", True)
    printer.addCutflowCut("SRSSemPre", "Pre Selection: SRSSem", True)
    printer.addCutflowCut("SRSSmmPre", "Pre Selection: SRSSmm", True)
    printer.addCutflowCut("|", "|", True)
    printer.addCutflowCut("SideSSeePre", "Pre Selection: SideSSee", True)
    printer.addCutflowCut("SideSSemPre", "Pre Selection: SideSSem", True)
    printer.addCutflowCut("SideSSmmPre", "Pre Selection: SideSSmm", True)
    printer.addCutflowCut("|", "|", True)
    printer.addCutflowCut("SR0SFOSPre", "Pre Selection: SR0SFOS", True)
    printer.addCutflowCut("SR1SFOSPre", "Pre Selection: SR1SFOS", True)
    printer.addCutflowCut("SR2SFOSPre", "Pre Selection: SR2SFOS", True)
    printer.addCutflowCut("|", "|", True)
    printer.addCutflowCut("SRSSeeFullFakeUp", "FullFakeUp Selection: SRSSee", True)
    printer.addCutflowCut("SRSSemFullFakeUp", "FullFakeUp Selection: SRSSem", True)
    printer.addCutflowCut("SRSSmmFullFakeUp", "FullFakeUp Selection: SRSSmm", True)
    printer.addCutflowCut("|", "|", True)
    printer.addCutflowCut("SideSSeeFullFakeUp", "FullFakeUp Selection: SideSSee", True)
    printer.addCutflowCut("SideSSemFullFakeUp", "FullFakeUp Selection: SideSSem", True)
    printer.addCutflowCut("SideSSmmFullFakeUp", "FullFakeUp Selection: SideSSmm", True)
    printer.addCutflowCut("|", "|", True)
    printer.addCutflowCut("SR0SFOSFullFakeUp", "FullFakeUp Selection: SR0SFOS", True)
    printer.addCutflowCut("SR1SFOSFullFakeUp", "FullFakeUp Selection: SR1SFOS", True)
    printer.addCutflowCut("SR2SFOSFullFakeUp", "FullFakeUp Selection: SR2SFOS", True)
    printer.addCutflowCut("|", "|", True)
    printer.addCutflowCut("ARSSeeFull", "AR: SRSSee", True)
    printer.addCutflowCut("ARSSemFull", "AR: SRSSem", True)
    printer.addCutflowCut("ARSSmmFull", "AR: SRSSmm", True)
    printer.addCutflowCut("|", "|", True)
    printer.addCutflowCut("ARSideSSeeFull", "AR: SRSSee", True)
    printer.addCutflowCut("ARSideSSemFull", "AR: SRSSem", True)
    printer.addCutflowCut("ARSideSSmmFull", "AR: SRSSmm", True)
    printer.addCutflowCut("|", "|", True)
    printer.addCutflowCut("AR0SFOSZVt", "AR: SR0SFOS", True)
    printer.addCutflowCut("AR1SFOSMT3rd", "AR: SR1SFOS", True)
    printer.addCutflowCut("AR2SFOSZVt", "AR: SR2SFOS", True)
    printer.addCutflowCut("|", "|", True)
    printer.addCutflowCut("LMETCRSSeeFull", "LMETCR: SRSSee", True)
    printer.addCutflowCut("LMETCRSSemFull", "LMETCR: SRSSem", True)
    printer.addCutflowCut("LMETCRSSmmFull", "LMETCR: SRSSmm", True)
    printer.addCutflowCut("|", "|", True)
    printer.addCutflowCut("BTCRSSeeFull", "BTCR: SRSSee", True)
    printer.addCutflowCut("BTCRSSemFull", "BTCR: SRSSem", True)
    printer.addCutflowCut("BTCRSSmmFull", "BTCR: SRSSmm", True)
    printer.addCutflowCut("|", "|", True)
    printer.addCutflowCut("BTCRSideSSeeFull", "BTCRSide: SRSSee", True)
    printer.addCutflowCut("BTCRSideSSemFull", "BTCRSide: SRSSem", True)
    printer.addCutflowCut("BTCRSideSSmmFull", "BTCRSide: SRSSmm", True)
    printer.addCutflowCut("|", "|", True)
    printer.addCutflowCut("SRSSeeFullFakeRateElUp", "FullFakeRateElUp Selection: SRSSee", True)
    printer.addCutflowCut("SRSSemFullFakeRateElUp", "FullFakeRateElUp Selection: SRSSem", True)
    printer.addCutflowCut("SRSSmmFullFakeRateElUp", "FullFakeRateElUp Selection: SRSSmm", True)
    printer.addCutflowCut("|", "|", True)
    printer.addCutflowCut("SideSSeeFullFakeRateElUp", "FullFakeRateElUp Selection: SideSSee", True)
    printer.addCutflowCut("SideSSemFullFakeRateElUp", "FullFakeRateElUp Selection: SideSSem", True)
    printer.addCutflowCut("SideSSmmFullFakeRateElUp", "FullFakeRateElUp Selection: SideSSmm", True)
    printer.addCutflowCut("|", "|", True)
    printer.addCutflowCut("SR0SFOSFullFakeRateElUp", "FullFakeRateElUp Selection: SR0SFOS", True)
    printer.addCutflowCut("SR1SFOSFullFakeRateElUp", "FullFakeRateElUp Selection: SR1SFOS", True)
    printer.addCutflowCut("SR2SFOSFullFakeRateElUp", "FullFakeRateElUp Selection: SR2SFOS", True)
    printer.addCutflowCut("|", "|", True)
    printer.addCutflowCut("SRSSeeFullFakeRateMuUp", "FullFakeRateMuUp Selection: SRSSee", True)
    printer.addCutflowCut("SRSSemFullFakeRateMuUp", "FullFakeRateMuUp Selection: SRSSem", True)
    printer.addCutflowCut("SRSSmmFullFakeRateMuUp", "FullFakeRateMuUp Selection: SRSSmm", True)
    printer.addCutflowCut("|", "|", True)
    printer.addCutflowCut("SideSSeeFullFakeRateMuUp", "FullFakeRateMuUp Selection: SideSSee", True)
    printer.addCutflowCut("SideSSemFullFakeRateMuUp", "FullFakeRateMuUp Selection: SideSSem", True)
    printer.addCutflowCut("SideSSmmFullFakeRateMuUp", "FullFakeRateMuUp Selection: SideSSmm", True)
    printer.addCutflowCut("|", "|", True)
    printer.addCutflowCut("SR0SFOSFullFakeRateMuUp", "FullFakeRateMuUp Selection: SR0SFOS", True)
    printer.addCutflowCut("SR1SFOSFullFakeRateMuUp", "FullFakeRateMuUp Selection: SR1SFOS", True)
    printer.addCutflowCut("SR2SFOSFullFakeRateMuUp", "FullFakeRateMuUp Selection: SR2SFOS", True)
    printer.addCutflowCut("|", "|", True)
    printer.addCutflowCut("SRSSeeFullFakeClosureElUp", "FullFakeClosureElUp Selection: SRSSee", True)
    printer.addCutflowCut("SRSSemFullFakeClosureElUp", "FullFakeClosureElUp Selection: SRSSem", True)
    printer.addCutflowCut("SRSSmmFullFakeClosureElUp", "FullFakeClosureElUp Selection: SRSSmm", True)
    printer.addCutflowCut("|", "|", True)
    printer.addCutflowCut("SideSSeeFullFakeClosureElUp", "FullFakeClosureElUp Selection: SideSSee", True)
    printer.addCutflowCut("SideSSemFullFakeClosureElUp", "FullFakeClosureElUp Selection: SideSSem", True)
    printer.addCutflowCut("SideSSmmFullFakeClosureElUp", "FullFakeClosureElUp Selection: SideSSmm", True)
    printer.addCutflowCut("|", "|", True)
    printer.addCutflowCut("SR0SFOSFullFakeClosureElUp", "FullFakeClosureElUp Selection: SR0SFOS", True)
    printer.addCutflowCut("SR1SFOSFullFakeClosureElUp", "FullFakeClosureElUp Selection: SR1SFOS", True)
    printer.addCutflowCut("SR2SFOSFullFakeClosureElUp", "FullFakeClosureElUp Selection: SR2SFOS", True)
    printer.addCutflowCut("|", "|", True)
    printer.addCutflowCut("SRSSeeFullFakeClosureMuUp", "FullFakeClosureMuUp Selection: SRSSee", True)
    printer.addCutflowCut("SRSSemFullFakeClosureMuUp", "FullFakeClosureMuUp Selection: SRSSem", True)
    printer.addCutflowCut("SRSSmmFullFakeClosureMuUp", "FullFakeClosureMuUp Selection: SRSSmm", True)
    printer.addCutflowCut("|", "|", True)
    printer.addCutflowCut("SideSSeeFullFakeClosureMuUp", "FullFakeClosureMuUp Selection: SideSSee", True)
    printer.addCutflowCut("SideSSemFullFakeClosureMuUp", "FullFakeClosureMuUp Selection: SideSSem", True)
    printer.addCutflowCut("SideSSmmFullFakeClosureMuUp", "FullFakeClosureMuUp Selection: SideSSmm", True)
    printer.addCutflowCut("|", "|", True)
    printer.addCutflowCut("SR0SFOSFullFakeClosureMuUp", "FullFakeClosureMuUp Selection: SR0SFOS", True)
    printer.addCutflowCut("SR1SFOSFullFakeClosureMuUp", "FullFakeClosureMuUp Selection: SR1SFOS", True)
    printer.addCutflowCut("SR2SFOSFullFakeClosureMuUp", "FullFakeClosureMuUp Selection: SR2SFOS", True)
    printer.addCutflowCut("|", "|", True)
    printer.addCutflowCut("VBSCRSSeeFull", "BTCRSide: SRSSee", True)
    printer.addCutflowCut("VBSCRSSemFull", "BTCRSide: SRSSem", True)
    printer.addCutflowCut("VBSCRSSmmFull", "BTCRSide: SRSSmm", True)
    printer.addCutflowCut("|", "|", True)
    addProcesses(printer, showdata=True)
    table = printer.createTable("style.firstColumnAlign=l")
    path = "cutflows/"
    try:
        os.makedirs(path)
    except OSError as exc:  # Python >2.5
        if exc.errno == errno.EEXIST and os.path.isdir(path):
            pass
        else:
            raise
    table.writeCSV("cutflows/yield.csv")
    table.writeHTML("cutflows/yield.html")
    table.writeLaTeX("cutflows/yield.tex")
    table.writePlain("cutflows/yield.txt")


if __name__ == "__main__":

    # Print cutflow table
    blind()
    print9SignalRegions(samples)
    printTable(samples)
    #printCutflow(samples, "WZCR")
    #printCutflow(samples, "SUSY")
    #printCutflow(samples, "Presel")
