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
    printer.addCutflowProcess("/os/sig", "WWW")
    #printer.addCutflowProcess("|", "|")
    #printer.addCutflowProcess("/typebkg/prompt", "Prompt")
    #printer.addCutflowProcess("/typebkg/qflip", "Charge flip")
    #printer.addCutflowProcess("/typebkg/photon", "Photon")
    #printer.addCutflowProcess("/typebkg/lostlep", "Lost-lep.")
    #printer.addCutflowProcess("/typebkg/fakes", "Fakes (MC)")
    #printer.addCutflowProcess("|", "|")
    #printer.addCutflowProcess("/typebkg/?", "Bkg. (MC)")
    #printer.addCutflowProcess("|", "|")
    #printer.addCutflowProcess("/fake", "Fakes (Data-Driv.)")
    #printer.addCutflowProcess("|", "|")
    #printer.addCutflowProcess("/fake+typebkg/prompt+typebkg/qflip+typebkg/photon+typebkg/lostlep", "Bkg. w/ est.")
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("/os/bkg/top/singletop", "1top")
    printer.addCutflowProcess("/os/bkg/top/ttbar", "ttincl")
    printer.addCutflowProcess("/os/bkg/ttV", "ttV")
    printer.addCutflowProcess("/os/bkg/VVV", "VVV")
    printer.addCutflowProcess("/os/bkg/VV/ZZ", "ZZ")
    printer.addCutflowProcess("/os/bkg/VV/WW", "WW")
    printer.addCutflowProcess("/os/bkg/VV/WZ,sys", "WZ")
    printer.addCutflowProcess("/os/bkg/W", "W")
    printer.addCutflowProcess("/os/bkg/Z", "Z")
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("/os/bkg", "Bkg. (MC)")
    printer.addCutflowProcess("|", "|")
    if showdata:
        printer.addCutflowProcess("|", "|")
        printer.addCutflowProcess("/os/data", "Data")
        printer.addCutflowProcess("|", "|")
        #printer.addCutflowProcess("$ratio(/data,/fake+typebkg-typebkg/fakes)", "Ratio")
        #printer.addCutflowProcess("$ratio(/data,/typebkg)", "Ratio")
        printer.addCutflowProcess("$ratio(/os/data,/os/bkg)", "Ratio")

########################################################################################
#_______________________________________________________________________________
# Supports only printing out by process boundaries
def printCutflow(samples, regionname):
    cuts = {}
    cutnames = []
    for counter in samples.getListOfCounterNames():
        print counter
        #if str(counter).find(regionname) != -1 and str(counter).find("cut") != -1:
        if str(counter).find(regionname) != -1:
            title = samples.getCounter("/os/data", str(counter)).GetTitle()
            cutnames.append(str(counter))
            cuts[str(counter)] = str(title)
    cutnames.sort(key=natural_keys)
    # Cutflow printing
    printer = TQCutflowPrinter(samples)
    for cut in cutnames:
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
    print "here"
    table.writeCSV("cutflows/{}.csv".format(regionname))
    print "here"
    table.writeHTML("cutflows/{}.html".format(regionname))
    print "here"
    table.writeLaTeX("cutflows/{}.tex".format(regionname))
    print "here"
    table.writePlain("cutflows/{}.txt".format(regionname))
    print "here"

#samples.printContents("r")

# Print cutflow table
printCutflow(samples, "OS")
#blind(samples)
#printSummaryCutflow(samples)
#printCutflow(samples, "SSee")
#printCutflow(samples, "SSem")
#printCutflow(samples, "SSmm")
#printCutflow(samples, "TL0SFOS")
#printCutflow(samples, "TL1SFOS")
#printCutflow(samples, "TL2SFOS")
