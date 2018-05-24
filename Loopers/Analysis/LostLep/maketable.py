#!/bin/env python

import os
import sys
import ROOT
from QFramework import TQSampleFolder, TQXSecParser, TQCut, TQAnalysisSampleVisitor, TQSampleInitializer, TQCutflowAnalysisJob, TQCutflowPrinter, TQHistoMakerAnalysisJob
from rooutil.qutils import *
from errors import E

filename = sys.argv[1]

ROOT.gROOT.SetBatch(True)
samples = TQSampleFolder.loadSampleFolder("{}:samples".format(filename))

########################################################################################
def addProcesses(printer, showdata, prettyversion=True):
    #printer.addCutflowProcess("$signif(/sig,/typebkg)", "Signif. (MC)")
    #printer.addCutflowProcess("$signif(/sig,/fake+typebkg/prompt+typebkg/qflip+typebkg/photon+typebkg/lostlep)", "Signif. (w/ Fake est.)")
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("/sig/whwww", "WHWWW")
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("/sig", "WWW")
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("/typebkg/prompt", "Prompt")
    printer.addCutflowProcess("/typebkg/qflip", "Charge flip")
    printer.addCutflowProcess("/typebkg/photon", "Photon")
    printer.addCutflowProcess("/typebkg/lostlep", "Lost-lep.")
    printer.addCutflowProcess("/typebkg/fakes", "Fakes (MC)")
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("/typebkg/?", "Bkg. (MC)")
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("/fake", "Fakes (Data-Driv.)")
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("/fake+typebkg/prompt+typebkg/qflip+typebkg/photon+typebkg/lostlep", "Bkg. w/ est.")
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("/bkg/top/singletop", "1top")
    printer.addCutflowProcess("/bkg/top/ttbar/tt1l", "tt1l")
    printer.addCutflowProcess("/bkg/top/ttbar/tt2l", "tt2l")
    printer.addCutflowProcess("/bkg/ttV", "ttV")
    printer.addCutflowProcess("/bkg/VVV", "VVV")
    printer.addCutflowProcess("/bkg/VV/ZZ", "ZZ")
    printer.addCutflowProcess("/bkg/VV/WW", "WW")
    printer.addCutflowProcess("/bkg/VV/WZ,sys", "WZ")
    printer.addCutflowProcess("/bkg/W", "W")
    printer.addCutflowProcess("/bkg/Z", "Z")
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("/bkg-sig/whwww", "Bkg. (MC)")
    printer.addCutflowProcess("|", "|")
    if showdata:
        printer.addCutflowProcess("|", "|")
        printer.addCutflowProcess("/data", "Data")
        printer.addCutflowProcess("|", "|")
        #printer.addCutflowProcess("$ratio(/data,/fake+typebkg-typebkg/fakes)", "Ratio")
        #printer.addCutflowProcess("$ratio(/data,/typebkg)", "Ratio")
        printer.addCutflowProcess("$ratio(/data,/bkg)", "Ratio")

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


# Print cutflow table
printCutflow(samples, "SS")
printCutflowSSWZExtrapolation(samples, sys.argv[2])
