#!/bin/env python

import ROOT
import re
import os
import sys
from QFramework import TQSampleFolder, TQXSecParser, TQCut, TQAnalysisSampleVisitor, TQSampleInitializer, TQCutflowAnalysisJob, TQCutflowPrinter, TQHistoMakerAnalysisJob, TQNFCalculator, TQCounter

try:
    samples = TQSampleFolder.loadSampleFolder("{}:samples".format(sys.argv[1]))
except:
    samples = TQSampleFolder.loadSampleFolder("output.root:samples")


########################################################################################
def addCuts(base, prefix_base, cutdefs, doNm1=True):
    doSyst = False
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
    if doNm1:
        for i, cutdef in enumerate(cutdefs):
            nm1cuts = [ cut[0] for j, cut in enumerate(cutdefs) if j!=i]
            nm1wgts = [ cut[1] for j, cut in enumerate(cutdefs) if j!=i]
            cutname = "{}_minus_{}".format(prefix, i)
            base.addCut(TQCut(cutname, cutname, combexpr(nm1cuts), combexpr(nm1wgts)))

########################################################################################
def createTQCut(cutname, cutdefs):

    # To hold the TQCuts
    cuts = []
    for i, cutdef in enumerate(cutdefs):

        # Create cut name
        this_cut_name = "cut{}_{}".format(i, cutname)

        # If last cut, then the cut name is the "cutname"
        if i == len(cutdefs) - 1: this_cut_name = "{}".format(cutname)

        # Create TQCut instance
        cut = TQCut(this_cut_name, this_cut_name, cutdef[0], cutdef[1])

        # Aggregate cuts
        cuts.append(cut)

    # Link all the cuts in steps
    for i in xrange(len(cuts)-1):
        cuts[i].addCut(cuts[i+1])

    return cuts[0]

########################################################################################
def combexpr(exprlist):
    cutlist = [ expr[0] if len(expr) != 0 else "1" for expr in exprlist ]
    wgtlist = [ expr[1] if len(expr) != 0 else "1" for expr in exprlist ]
    return "({})".format(")*(".join(cutlist)), "({})".format(")*(".join(wgtlist))

########################################################################################
def atoi(text):
    return int(text) if text.isdigit() else text

########################################################################################
def natural_keys(text):
    '''
    alist.sort(key=natural_keys) sorts in human order
    http://nedbatchelder.com/blog/200712/human_sorting.html
    (See Toothy's implementation in the comments)
    '''
    return [ atoi(c) for c in re.split('(\d+)', text) ]

########################################################################################
def blind():
    cutnames = []
    for i in samples.getListOfCounterNames():
        cutnames.append(str(i))
    cutnames.sort(key=natural_keys)
    for cutname in cutnames:
        if cutname.find("WZCR") == -1 and cutname.find("TLWZ") == -1:
            samples.setScaleFactor(cutname, 0, 0, "/data")

########################################################################################
def addProcesses(printer, showdata, prettyversion=True):
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("/sig", "WWW")
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
    printer.addCutflowProcess("/bkg", "Bkg. (MC)")
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("/typebkg/prompt", "Prompt")
    printer.addCutflowProcess("/typebkg/qflip", "Charge flip")
    printer.addCutflowProcess("/typebkg/photon", "Photon")
    printer.addCutflowProcess("/typebkg/lostlep", "Lost-lep.")
    printer.addCutflowProcess("/typebkg/fakes", "Fakes (MC)")
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("/fake", "Fakes (Data-Driv.)")
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("/typebkg/?", "Bkg. (MC)")
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("/fake+typebkg/prompt+typebkg/qflip+typebkg/photon+typebkg/lostlep", "Bkg. w/ est.")
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("$signif(/sig,/typebkg)", "Signif. (MC)")
    printer.addCutflowProcess("$signif(/sig,/fake+typebkg/prompt+typebkg/qflip+typebkg/photon+typebkg/lostlep)", "Signif. (w/ Fake est.)")
    if showdata:
        printer.addCutflowProcess("|", "|")
        printer.addCutflowProcess("/data", "Data")
        printer.addCutflowProcess("|", "|")
        printer.addCutflowProcess("$ratio(/data,/fake+typebkg-typebkg/fakes)", "Ratio")


########################################################################################
#_______________________________________________________________________________
# Supports only printing out by process boundaries
def printSummaryCutflow(output_name="srcutflow"):
    # Cutflow printing
    printer = TQCutflowPrinter(samples)
    printer.addCutflowCut("SSee", "SSee", True)
    printer.addCutflowCut("SSem", "SSem", True)
    printer.addCutflowCut("SSmm", "SSmm", True)
    printer.addCutflowCut("|","|")
    printer.addCutflowCut("TL0SFOS", "TL0SFOS", True)
    printer.addCutflowCut("TL1SFOS", "TL1SFOS", True)
    printer.addCutflowCut("TL2SFOS", "TL2SFOS", True)
    printer.addCutflowCut("|","|")
    printer.addCutflowCut("SSWZee", "SSWZee", True)
    printer.addCutflowCut("SSWZem", "SSWZem", True)
    printer.addCutflowCut("SSWZmm", "SSWZmm", True)
    printer.addCutflowCut("|","|")
#    printer.addCutflowCut("WZCRee", "WZCRee")
#    printer.addCutflowCut("WZCRem", "WZCRem")
#    printer.addCutflowCut("WZCRmm", "WZCRmm")
#    printer.addCutflowCut("|","|")
#    printer.addCutflowCut("TLWZ1SFOS", "TLWZ1SFOS")
#    printer.addCutflowCut("TLWZ2SFOS", "TLWZ2SFOS")
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
    table.writeCSV("cutflows/{}.csv".format(output_name))
    table.writeHTML("cutflows/{}.html".format(output_name))
    table.writeLaTeX("cutflows/{}.tex".format(output_name))
    table.writePlain("cutflows/{}.txt".format(output_name))

