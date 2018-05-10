#!/bin/env python

import os
import sys
import ROOT
from QFramework import TQSampleFolder, TQXSecParser, TQCut, TQAnalysisSampleVisitor, TQSampleInitializer, TQCutflowAnalysisJob, TQCutflowPrinter, TQHistoMakerAnalysisJob
from qutils import *

ROOT.gROOT.SetBatch(True)
samples = TQSampleFolder.loadSampleFolder("output.root:samples")

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


# Print cutflow table
printCutflow(samples, "SS")
#blind(samples)
#printSummaryCutflow(samples)
#printCutflow(samples, "SSee")
#printCutflow(samples, "SSem")
#printCutflow(samples, "SSmm")
#printCutflow(samples, "TL0SFOS")
#printCutflow(samples, "TL1SFOS")
#printCutflow(samples, "TL2SFOS")
