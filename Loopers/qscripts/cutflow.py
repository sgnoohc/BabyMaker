#!/bin/env python

import os
import sys

import ROOT
from QFramework import TQSampleFolder, TQXSecParser, TQCut, TQAnalysisSampleVisitor, TQSampleInitializer, TQCutflowAnalysisJob, TQCutflowPrinter, TQHistoMakerAnalysisJob, TQNFCalculator, TQCounter
from rooutil import plottery_wrapper as p

from cuts import bkg_types_SS
from cuts import bkg_types_3L

from cuts import *

import re

from pytable import *

import math

def atoi(text):
    return int(text) if text.isdigit() else text

def natural_keys(text):
    '''
    alist.sort(key=natural_keys) sorts in human order
    http://nedbatchelder.com/blog/200712/human_sorting.html
    (See Toothy's implementation in the comments)
    '''
    return [ atoi(c) for c in re.split('(\d+)', text) ]

ROOT.gROOT.SetBatch(True)

try:
    samples = TQSampleFolder.loadSampleFolder("{}:samples".format(sys.argv[1]))
except:
    samples = TQSampleFolder.loadSampleFolder("output.root:samples")

#_______________________________________________________________________________
def getWZNF(cutname):
    wz   = samples.getCounter("/typebkg/lostlep", cutname)
    nf = samples.getCounter("/data-typebkg/[qflip+photon+prompt+fakes]-sig", cutname)
    #print wz.getCounter(), nf.getCounter()
    nf.divide(wz)
    #print nf.getCounter(), nf.getError(), nf.getError() / nf.getCounter()
    return nf.getCounter(), nf.getError()

#_______________________________________________________________________________
def getWZNF3L(cutname):
    wz   = samples.getCounter("/typebkg/prompt", cutname)
    nf = samples.getCounter("/data-typebkg/[qflip+photon+lostlep+fakes]-sig", cutname)
    #print wz.getCounter(), nf.getCounter()
    nf.divide(wz)
    #print nf.getCounter(), nf.getError(), nf.getError() / nf.getCounter()
    return nf.getCounter(), nf.getError()

#_______________________________________________________________________________
def getFakeError(cutname):
    fake = samples.getCounter("/fake", cutname)
    fakesyst = samples.getCounter("/fakeup-fake", cutname)
    frerror = fakesyst.getCounter() / fake.getCounter()
    frclosuresyst = 0.50
    frerror = math.sqrt(frerror**2 + frclosuresyst**2)
    print 1.0, frerror
    return 1.0, frerror

#_______________________________________________________________________________
def applyWZNF():
    nf_ee, nferr_ee = getWZNF3L("WZCRee")
    nf_em, nferr_em = getWZNF3L("WZCRem")
    nf_mm, nferr_mm = getWZNF3L("WZCRmm")
    #nf_mmnj1, nferr_mmnj1 = getWZNF("WZCRmmNJ1")
    #nf_mmnj2, nferr_mmnj2 = getWZNF("WZCRmmNJ2")
    #nf_mmnj2sb, nferr_mmnj2sb = getWZNF("WZCRmmNJ2MJJSB")
    #nf_mmnj2wd, nferr_mmnj2wd = getWZNF("WZCRmmNJ2MJJWD")
    #print samples.getCounter("/typebkg/?/WZ", "SSmmNJ1").getCounter()
    #print samples.getCounter("/typebkg/?/WZ", "SSmmNJ2MJJSB").getCounter()
    #print samples.getCounter("/typebkg/?/WZ", "SSmmNJ2MJJWD").getCounter()
    #print samples.getCounter("/typebkg/?/WZ", "SSmmNJ1").getCounter()      / samples.getCounter("/typebkg/?/WZ", "WZCRmmNJ1").getCounter(), samples.getCounter("/data-typebkg/?/bkg-sig", "WZCRmmNJ1").getCounter(),
    #print samples.getCounter("/typebkg/?/WZ", "SSmmNJ2MJJSB").getCounter() / samples.getCounter("/typebkg/?/WZ", "WZCRmmNJ2MJJSB").getCounter(), samples.getCounter("/data-typebkg/?/bkg-sig", "WZCRmmNJ2MJJSB").getCounter()
    #print samples.getCounter("/typebkg/?/WZ", "SSmmNJ2MJJWD").getCounter() / samples.getCounter("/typebkg/?/WZ", "WZCRmmNJ2MJJWD").getCounter(), samples.getCounter("/data-typebkg/?/bkg-sig", "WZCRmmNJ2MJJWD").getCounter()
    nf_1SFOS, nferr_1SFOS = getWZNF3L("TLWZ1SFOS")
    nf_2SFOS, nferr_2SFOS = getWZNF3L("TLWZ2SFOS")
    #samples.setScaleFactor("SSee", nf_ee, nferr_ee, "/bkg/VV/WZ")
    #samples.setScaleFactor("SSem", nf_em, nferr_em, "/bkg/VV/WZ")
    #samples.setScaleFactor("SSmm", nf_mm, nferr_mm, "/bkg/VV/WZ")
    samples.setScaleFactor("SSee", nf_ee, nferr_ee, "/typebkg/lostlep")
    samples.setScaleFactor("SSem", nf_em, nferr_em, "/typebkg/lostlep")
    samples.setScaleFactor("SSmm", nf_mm, nferr_mm, "/typebkg/lostlep")
    samples.setScaleFactor("TL0SFOS", nf_1SFOS, nferr_1SFOS, "/typebkg/prompt")
    samples.setScaleFactor("TL1SFOS", nf_1SFOS, nferr_1SFOS, "/typebkg/prompt")
    samples.setScaleFactor("TL2SFOS", nf_2SFOS, nferr_2SFOS, "/typebkg/prompt")
    #samples.setScaleFactor("TL1SFOS", nf_1SFOS, nferr_1SFOS, "/bkg/VV/WZ")
    #samples.setScaleFactor("TL2SFOS", nf_2SFOS, nferr_2SFOS, "/bkg/VV/WZ")
    #samples.setScaleFactor("TL1SFOS", nf_1SFOS, nferr_1SFOS, "/typebkg/?/WZ")
    #samples.setScaleFactor("TL2SFOS", nf_2SFOS, nferr_2SFOS, "/typebkg/?/WZ")
    #samples.setScaleFactor("SSmmNJ1", nf_mmnj1, nferr_mmnj1, "/typebkg/?/WZ")
    #samples.setScaleFactor("SSmmNJ2", nf_mmnj2, nferr_mmnj2, "/typebkg/?/WZ")
    #samples.setScaleFactor("SSmmNJ2MJJSB", nf_mmnj2sb, nferr_mmnj2sb, "/typebkg/?/WZ")
    #samples.setScaleFactor("SSmmNJ2MJJWD", nf_mmnj2wd, nferr_mmnj2wd, "/typebkg/?/WZ")

#_______________________________________________________________________________
def applyFakeError():
    nf_ee, nferr_ee = getFakeError("SSee")
    nf_em, nferr_em = getFakeError("SSem")
    nf_mm, nferr_mm = getFakeError("SSmm")
    nf_0SFOS, nferr_0SFOS = getFakeError("TL0SFOS")
    nf_1SFOS, nferr_1SFOS = getFakeError("TL1SFOS")
    nf_2SFOS, nferr_2SFOS = getFakeError("TL2SFOS")
    #samples.getCounter("/fake", "SSee").setError(100)
    #samples.getCounter("/fake", "SSee").setCounter(100)
    samples.setScaleFactor("SSee", nf_ee, nferr_ee, "/fake")
    samples.setScaleFactor("SSem", nf_em, nferr_em, "/fake")
    samples.setScaleFactor("SSmm", nf_mm, nferr_mm, "/fake")
    samples.setScaleFactor("TL0SFOS", nf_1SFOS, nferr_1SFOS, "/fake")
    samples.setScaleFactor("TL1SFOS", nf_1SFOS, nferr_1SFOS, "/fake")
    samples.setScaleFactor("TL2SFOS", nf_2SFOS, nferr_2SFOS, "/fake")

#_______________________________________________________________________________
def applyPromptBkgSyst():
    samples.setScaleFactor("SSee"    , 1.0    , 0.15    , "/typebkg/prompt")
    samples.setScaleFactor("SSem"    , 1.0    , 0.15    , "/typebkg/prompt")
    samples.setScaleFactor("SSmm"    , 1.0    , 0.15    , "/typebkg/prompt")
    #samples.setScaleFactor("TL0SFOS" , nf_1SFOS , nferr_1SFOS , "/typebkg/lostlep")
    #samples.setScaleFactor("TL1SFOS" , nf_1SFOS , nferr_1SFOS , "/typebkg/lostlep")
    #samples.setScaleFactor("TL2SFOS" , nf_2SFOS , nferr_2SFOS , "/typebkg/lostlep")

#_______________________________________________________________________________
def blind():
    cutnames = []
    for i in samples.getListOfCounterNames():
        cutnames.append(str(i))
    cutnames.sort(key=natural_keys)
    for cutname in cutnames:
        if cutname.find("WZCR") == -1 and cutname.find("TLWZ") == -1:
            samples.setScaleFactor(cutname, 0, 0, "/data")

#_______________________________________________________________________________
def addProcesses(printer, showdata, prettyversion=True):
    if not prettyversion:
        printer.loadSystematics("output.root:samples")
        printer.addCutflowProcess("|", "|")
        printer.addCutflowProcess("/sig/whwww", "only WH")
        printer.addCutflowProcess("/sig/www", "only WWW")
        printer.addCutflowProcess("|", "|")
        printer.addCutflowProcess("/sig", "WWW")
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
        printer.addCutflowProcess("/typebkg/prompt", "justprompt")
        printer.addCutflowProcess("/typebkg/prompt/bkg+typebkg/lostlep/bkg", "prompt")
        printer.addCutflowProcess("/typebkg/qflip/bkg", "qflip")
        printer.addCutflowProcess("/typebkg/photon/bkg", "photon")
        printer.addCutflowProcess("/typebkg/lostlep", "lostleponly")
        printer.addCutflowProcess("/typebkg/qflip", "qfliponly")
        printer.addCutflowProcess("/typebkg/photon", "photononly")
        printer.addCutflowProcess("/typebkg/?/WZ", "WZ")
        printer.addCutflowProcess("/typebkg/lostlep+typebkg/qflip+typebkg/photon+typebkg/prompt", "allbkg1")
        printer.addCutflowProcess("/typebkg/lostlep/bkg+typebkg/qflip/bkg+typebkg/photon/bkg+typebkg/prompt/bkg+typebkg/[prompt+lostlep+photon+qflip]/WZ", "allbkg2")
    #    printer.addCutflowProcess("/typebkg/fakes", "fakes (MC)")
    #    printer.addCutflowProcess("/typebkg/photon", "photon")
    #    printer.addCutflowProcess("/typebkg/[fakes+photon]", "fakes (MC)")
        printer.addCutflowProcess("/fake", "(data-drv. fake)")
        printer.addCutflowProcess("|", "|")
        printer.addCutflowProcess("/typebkg", "Bkg. (MC)")
        printer.addCutflowProcess("/typebkg/fakes", "fakes (MC)")
        printer.addCutflowProcess("|", "|")
        printer.addCutflowProcess("/fake", "(data-drv. fake)")
        printer.addCutflowProcess("|", "|")
        printer.addCutflowProcess("/typebkg/photon", "photon")
    #    printer.addCutflowProcess("/typebkg/others", "others")
    #    printer.addCutflowProcess("|", "|")
        printer.addCutflowProcess("/bkg", "Tot. MC")
        printer.addCutflowProcess("|", "|")
        printer.addCutflowProcess("/typebkg", "Bkg. (MC)")
        printer.addCutflowProcess("|", "|")
        printer.addCutflowProcess("/fake+typebkg-typebkg/fakes", "B. w/ Fake est.")
        printer.addCutflowProcess("|", "|")
        printer.addCutflowProcess("$signif(/sig,/typebkg)", "Signif. (MC)")
        printer.addCutflowProcess("|", "|")
        printer.addCutflowProcess("$signif(/sig,/fake+typebkg-typebkg/fakes)", "Signif. (w/ Fake est.)")
        if showdata:
            printer.addCutflowProcess("|", "|")
            printer.addCutflowProcess("/data", "Data")
            printer.addCutflowProcess("|", "|")
            printer.addCutflowProcess("$ratio(/data,/fake+typebkg-typebkg/fakes)", "Ratio")
    else:
        printer.addCutflowProcess("|", "|")
        printer.addCutflowProcess("/sig", "WWW")
        printer.addCutflowProcess("|", "|")
        printer.addCutflowProcess("/typebkg/prompt", "Prompt")
        printer.addCutflowProcess("/typebkg/qflip", "Charge flip")
        printer.addCutflowProcess("/typebkg/photon", "Photon")
        printer.addCutflowProcess("/typebkg/lostlep", "Lost-lep.")
        #printer.addCutflowProcess("/typebkg/fakes", "Fakes (MC)")
        printer.addCutflowProcess("/fake", "Fakes (Data-Driv.)")
        printer.addCutflowProcess("|", "|")
        printer.addCutflowProcess("/typebkg/?", "Bkg. (MC)")
        printer.addCutflowProcess("|", "|")
        printer.addCutflowProcess("/fake+typebkg/prompt+typebkg/qflip+typebkg/photon+typebkg/lostlep", "Bkg. w/ est.")
        printer.addCutflowProcess("|", "|")
        printer.addCutflowProcess("/typebkg/fakes", "Fakes (MC)")
        #printer.addCutflowProcess("$signif(/sig,/typebkg)", "Signif. (MC)")
        #printer.addCutflowProcess("$signif(/sig,/fake+typebkg/prompt+typebkg/qflip+typebkg/photon+typebkg/lostlep)", "Signif. (w/ Fake est.)")
        if showdata:
            printer.addCutflowProcess("|", "|")
            printer.addCutflowProcess("/data", "Data")
            printer.addCutflowProcess("|", "|")
            printer.addCutflowProcess("$ratio(/data,/fake+typebkg-typebkg/fakes)", "Ratio")

#_______________________________________________________________________________
def printSR(showdata=False):
    printer = TQCutflowPrinter(samples)
    printer.addCutflowCut("|", "|")
    printer.addCutflowCut("SSee", "SS: ee", True)
    printer.addCutflowCut("SSem", "SS: e#mu", True)
    printer.addCutflowCut("SSmm", "SS: #mu#mu", True)
    printer.addCutflowCut("|", "|")
    printer.addCutflowCut("TL0SFOS", "3L: 0SFOS")
    printer.addCutflowCut("TL1SFOS", "3L: 1SFOS", True)
    printer.addCutflowCut("TL2SFOS", "3L: 2SFOS", True)
    printer.addCutflowCut("|", "|")
    printer.addCutflowCut("SSem+SSmm+TL0SFOS+SSee+TL1SFOS+TL2SFOS", "All SRs", True)
    addProcesses(printer, showdata)
    table = printer.createTable("style.firstColumnAlign=l")
    output_name = "cutflow_SR"
    table.writeCSV("cutflows/{}.csv".format(output_name))
    table.writeHTML("cutflows/{}.html".format(output_name))
    table.writeLaTeX("cutflows/{}.tex".format(output_name))
    table.writePlain("cutflows/{}.txt".format(output_name), "format.doubleAndUncertainty.ascii=%.$(ndigits)f, +/-, %.$(ndigits)f")

#_______________________________________________________________________________
def printCR(showdata=True):
    printer = TQCutflowPrinter(samples)
    printer.addCutflowCut("|", "|")
    printer.addCutflowCut("WZCRee", "WZCR: ee")
    printer.addCutflowCut("WZCRem", "WZCR: e#mu")
    printer.addCutflowCut("WZCRmm", "WZCR: #mu#mu")
    printer.addCutflowCut("|", "|")
    printer.addCutflowCut("TLWZ1SFOS", "WZCR: 1SFOS")
    printer.addCutflowCut("TLWZ2SFOS", "WZCR: 2SFOS")
    addProcesses(printer, showdata)
    table = printer.createTable("style.firstColumnAlign=l")
    output_name = "cutflow_CR"
    table.writeCSV("cutflows/{}.csv".format(output_name))
    table.writeHTML("cutflows/{}.html".format(output_name))
    table.writeLaTeX("cutflows/{}.tex".format(output_name))
    table.writePlain("cutflows/{}.txt".format(output_name))

#_______________________________________________________________________________
# Supports only printing out by process boundaries
def printAllCutflow(output_name="allcutflow"):
    # Cutflow printing
    printer = TQCutflowPrinter(samples)
    allcuts = getAllCuts()
    cutnames = []
    for i in samples.getListOfCounterNames():
        if str(i).find("minus_0") != -1: continue
        if str(i).find("BaseCut") != -1: continue
        if str(i).find("dummy") != -1: continue
        if str(i).find("base_") != -1: continue
        if str(i).find("cut") != -1: continue
        cutnames.append(str(i))
    cutnames.sort(key=natural_keys)
    cutflowcutnames = []
    for i in samples.getListOfCounterNames():
        if str(i) in [ "SSee", "SSem", "SSmm", "TL0SFOS", "TL1SFOS", "TL2SFOS", "WZCRmm"]:
            cutflowcutnames.append("cutx_" + str(i))
            continue
        if str(i).find("cut") == -1: continue
        cutflowcutnames.append(str(i))
    cutflowcutnames.sort(key=lambda x: x.split("_")[1]+"_"+x.split("_")[0] if len(x.split("_"))>1 else x)
    for cutname in cutnames:
        tqcut = allcuts.getCut(cutname)
        nchildcut = len(tqcut.getListOfCuts())
        cutexpr = str(tqcut.getCutExpression())
        if cutexpr.find(")*(") != -1:
            cutexpr = ""
        if nchildcut == 1:
            cutexpr = ""
        if len(cutexpr) != 0:
            cutexpr = "_" + cutexpr
        if cutname in [ "SSee", "SSem", "SSmm", "TL0SFOS", "TL1SFOS", "TL2SFOS", "cut0_SSee" ]:
            printer.addCutflowCut("|", "|")
        if cutname.find("NJ1") != -1:
            printer.addCutflowCut("|", "|")
        printer.addCutflowCut(cutname, cutname + cutexpr)
    for cutname in cutflowcutnames:
        cutname = cutname.replace("cutx_","")
        tqcut = allcuts.getCut(cutname)
        nchildcut = len(tqcut.getListOfCuts())
        cutexpr = str(tqcut.getCutExpression())
        if cutexpr.find(")*(") != -1:
            cutexpr = ""
        if len(cutexpr) != 0:
            cutexpr = "_" + cutexpr
        if cutname.find("cut0_") != -1:
            printer.addCutflowCut("|", "|")
        printer.addCutflowCut(cutname, cutname + cutexpr)
    #addProcesses(printer, showdata=False)
    addProcesses(printer, showdata=True)
    table = printer.createTable("style.firstColumnAlign=l")
    table.writeCSV("cutflows/{}.csv".format(output_name))
    table.writeHTML("cutflows/{}.html".format(output_name))
    table.writeLaTeX("cutflows/{}.tex".format(output_name))
    table.writePlain("cutflows/{}.txt".format(output_name))

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
    printer.addCutflowCut("WZCRee", "WZCRee")
    printer.addCutflowCut("WZCRem", "WZCRem")
    printer.addCutflowCut("WZCRmm", "WZCRmm")
    printer.addCutflowCut("|","|")
    printer.addCutflowCut("TLWZ1SFOS", "TLWZ1SFOS")
    printer.addCutflowCut("TLWZ2SFOS", "TLWZ2SFOS")
    addProcesses(printer, showdata=True)
    table = printer.createTable("style.firstColumnAlign=l")
    table.writeCSV("cutflows/{}.csv".format(output_name))
    table.writeHTML("cutflows/{}.html".format(output_name))
    table.writeLaTeX("cutflows/{}.tex".format(output_name))
    table.writePlain("cutflows/{}.txt".format(output_name))

#_______________________________________________________________________________
# Supports only printing out by process boundaries
def printCutflow(region_prefix, ncut, output_name, showdata=False):
    # Cutflow printing
    printer = TQCutflowPrinter(samples)
    for i in samples.getListOfCounterNames():
        print i
    printer.addCutflowCut("BaseCut", "BaseCut")
    printer.addCutflowCut("base_{}".format(region_prefix), "base_{}".format(region_prefix))
    for i in xrange(0, ncut):
        printer.addCutflowCut("cut{}_{}".format(i, region_prefix), "cut{}_{}".format(i, region_prefix), 1)
    printer.addCutflowCut("{}".format(region_prefix), "{}".format(region_prefix), 1)
    printer.addCutflowCut("{}NJ1".format(region_prefix), "{}NJ1".format(region_prefix), 1)
    printer.addCutflowCut("{}NJ2MJJSB".format(region_prefix), "{}NJ2MJJSB".format(region_prefix), 1)
    printer.addCutflowCut("{}NJ2MJJWD".format(region_prefix), "{}NJ2MJJWD".format(region_prefix), 1)
    addProcesses(printer, showdata)
    table = printer.createTable()
    table.writeCSV("cutflows/{}.csv".format(output_name))
    table.writeHTML("cutflows/{}.html".format(output_name))
    table.writeLaTeX("cutflows/{}.tex".format(output_name))
    table.writePlain("cutflows/{}.txt".format(output_name))

#_______________________________________________________________________________
def addCountersToStatCardData(categ, cut, data, zero=False):
    if categ == "sig": proc = "/sig"
    if categ == "fake": proc = "/fake"
    if categ == "photon": proc = "/typebkg/photon"
    if categ == "ss3l": proc = "/typebkg/prompt"
    if categ == "qflip": proc = "/typebkg/qflip"
    if categ == "wz": proc = "/typebkg/lostlep"

    if cut.find("TL") != -1:
        if categ == "ss3l": proc = "/typebkg/lostlep"
        if categ == "wz": proc = "/typebkg/prompt"

    cnt = samples.getCounter(proc, cut).getCounter()
    err = samples.getCounter(proc, cut).getError()
    data["{}".format(categ)] = "{:.3f}".format(cnt) if cnt > 0 else "1e-06"
    data["{}err".format(categ)] = "{:.3f}".format(err / cnt + 1) if cnt > 0 else "1.99"
    if zero:
        data["{}".format(categ)] = "1e-06"
        data["{}err".format(categ)] = "1.99"

#_______________________________________________________________________________
def addFakeRateSystCountersToStatCardData(categ, cut, data):
    if categ == "fakeup": proc = "/fakeup"
    cnt = samples.getCounter(proc, cut).getCounter()
    nomcnt = samples.getCounter("/fake", cut).getCounter()
    data["{}".format(categ)] = "{:.3f}".format(cnt) if cnt > 0 else "1e-06"
    data["{}err".format(categ)] = "{:.3f}".format(cnt / nomcnt) if cnt > 0 else "1.99"

#_______________________________________________________________________________
# Printing stat card
def getStatCardStringWithGmN(cutname, index, version="ss"):
    data = {}
    addCountersToStatCardData("sig", cutname, data)
    addCountersToStatCardData("fake", cutname, data)
    addCountersToStatCardData("photon", cutname, data)
    addCountersToStatCardData("ss3l", cutname, data)
    addCountersToStatCardData("qflip", cutname, data)
    addCountersToStatCardData("wz", cutname, data)
    addFakeRateSystCountersToStatCardData("fakeup", cutname, data)
    if version == "ss":
        wzcr = samples.getCounter("/typebkg/lostlep", cutname.replace("SS", "WZCR"), "scaleScheme=.nosf")
        nzcr = samples.getCounter("/typebkg/[qflip+photon+prompt+fakes]+sig", cutname.replace("SS", "WZCR"), "scaleScheme=.nosf")
        wzsr = samples.getCounter("/typebkg/lostlep", cutname, "scaleScheme=.nosf")
        wzdd = samples.getCounter("/data-typebkg/[qflip+photon+prompt+fakes]-sig", cutname.replace("SS", "WZCR"), "scaleScheme=.nosf")
        crdd = samples.getCounter("/data", cutname.replace("SS", "WZCR"), "scaleScheme=.nosf")
    elif version == "3l":
        if cutname.find("TL0SFOS") != -1: nm = cutname.replace("TL0SFOS", "TLWZ1SFOS")
        if cutname.find("TL1SFOS") != -1: nm = cutname.replace("TL1SFOS", "TLWZ1SFOS")
        if cutname.find("TL2SFOS") != -1: nm = cutname.replace("TL2SFOS", "TLWZ2SFOS")
        print nm
        wzcr = samples.getCounter("/typebkg/prompt", nm, "scaleScheme=.nosf")
        nzcr = samples.getCounter("/typebkg/[qflip+photon+lostlep+fakes]+sig", nm, "scaleScheme=.nosf")
        wzsr = samples.getCounter("/typebkg/prompt", cutname, "scaleScheme=.nosf")
        wzdd = samples.getCounter("/data-typebkg/[qflip+photon+lostlep+fakes]-sig", nm, "scaleScheme=.nosf")
        crdd = samples.getCounter("/data", nm, "scaleScheme=.nosf")
    alpha = TQCounter()
    wzpurity = TQCounter()
    alpha.add(wzsr)
    alpha.divide(wzcr)
    alpha.multiply(wzdd)
    alpha.divide(crdd)
    wzpurity.add(wzdd)
    wzpurity.divide(crdd)
    if version == "ss":
        nm = cutname.replace("SS", "WZCR")
    elif version == "3l":
        if cutname.find("TL0SFOS") != -1: nm = cutname.replace("TL0SFOS", "TLWZ1SFOS")
        if cutname.find("TL1SFOS") != -1: nm = cutname.replace("TL1SFOS", "TLWZ1SFOS")
        if cutname.find("TL2SFOS") != -1: nm = cutname.replace("TL2SFOS", "TLWZ2SFOS")
    data["wzcr"] = "{:d}".format(int(samples.getCounter("/data", nm).getCounter()))
    data["wzalpha"] = "{:.5f}".format(alpha.getCounter())
    data["wzpurity"] = "{:.3f}".format(wzpurity.getError() + 1)
    data["I"] = index
    cardstring = """imax 1 number of bins
jmax 5 number of processes minus 1
kmax 20 number of nuisance parameters
----------------------------------------------------------------------------------------------------------------------------------
shapes *    ch1  FAKE
----------------------------------------------------------------------------------------------------------------------------------
bin          ch1
observation  0.0
----------------------------------------------------------------------------------------------------------------------------------
bin                                ch1          ch1          ch1          ch1          ch1          ch1
process                            sig          Fake         photon       SS3l         chargeflip   WZ
process                            0            1            2            3            4            5
rate                               {sig:<13s}{fake:<13s}{photon:<13s}{ss3l:<13s}{qflip:<13s}{wz:<13s}
----------------------------------------------------------------------------------------------------------------------------------
{I}aSigStat             lnN        {sigerr:<13s}-            -            -            -            -
{I}bFakeStat            lnN        -            {fakeerr:<13s}-            -            -            -
{I}cPhoStat             lnN        -            -            {photonerr:<13s}-            -            -
{I}dSStat3              lnN        -            -            -            {ss3lerr:<13s}-            -
{I}eChFlstat            lnN        -            -            -            -            {qfliperr:<13s}-
{I}fWZStat              lnN        -            -            -            -            -            {wzerr:<13s}
{I}gWZNorm              gmN {wzcr:<6s} -            -            -            -            -            {wzalpha:<13s}
{I}hWZPurity            lnN        -            -            -            -            -            {wzpurity:<13s}
FakeSyst                lnN        -            1.30         -            -            -            -
FakeRate                lnN        -            {fakeuperr:<13s}-            -            -            -
SSSyst                  lnN        -            -            -            1.20         -            -
JECSyst                 lnN        0.990/0.980  -            -            0.990/1.010  -            -
LepSF                   lnN        1.001        -            -            1.001        -            -
LumSyst                 lnN        1.025        -            1.025        1.025        1.025        -
PU                      lnN        1.02         -            -            1.001        -            -
SigPDF                  lnN        0.990/1.010  -            -            -            -            -
SigQsq                  lnN        1.010/0.990  -            -            -            -            -
TrigSyst                lnN        1.01         -            1.01         1.01         1.01         -
XSec                    lnN        1.06         -            -            -            -            -
bSF                     lnN        1.03         -            -            1.04         -            - """.format(**data)
    return cardstring

#_______________________________________________________________________________
# Printing stat card
def getStatCardString(cutname, index, version="ss"):
    data = {}
    addCountersToStatCardData("sig", cutname, data)
    addCountersToStatCardData("fake", cutname, data)
    addCountersToStatCardData("photon", cutname, data)
    addCountersToStatCardData("ss3l", cutname, data)
    addCountersToStatCardData("qflip", cutname, data)
    addCountersToStatCardData("wz", cutname, data)
    addFakeRateSystCountersToStatCardData("fakeup", cutname, data)
    if version == "ss":
        nf, nf_err = getWZNF(cutname.replace("SS", "WZCR"))
    elif version == "3l":
        if cutname.find("TL0SFOS") != -1: nm = cutname.replace("TL0SFOS", "TLWZ1SFOS")
        if cutname.find("TL1SFOS") != -1: nm = cutname.replace("TL1SFOS", "TLWZ1SFOS")
        if cutname.find("TL2SFOS") != -1: nm = cutname.replace("TL2SFOS", "TLWZ2SFOS")
        nf, nf_err = getWZNF3L(nm)
    data["wzalpha"] = "{:.3f}".format(nf_err / nf + 1)
    data["I"] = index
    cardstring = """imax 1 number of bins
jmax 5 number of processes minus 1
kmax 19 number of nuisance parameters
----------------------------------------------------------------------------------------------------------------------------------
shapes *    ch1  FAKE
----------------------------------------------------------------------------------------------------------------------------------
bin          ch1
observation  0.0
----------------------------------------------------------------------------------------------------------------------------------
bin                                ch1          ch1          ch1          ch1          ch1          ch1
process                            sig          Fake         photon       SS3l         chargeflip   WZ
process                            0            1            2            3            4            5
rate                               {sig:<13s}{fake:<13s}{photon:<13s}{ss3l:<13s}{qflip:<13s}{wz:<13s}
----------------------------------------------------------------------------------------------------------------------------------
{I}aSigStat             lnN        {sigerr:<13s}-            -            -            -            -
{I}bFakeStat            lnN        -            {fakeerr:<13s}-            -            -            -
{I}cPhoStat             lnN        -            -            {photonerr:<13s}-            -            -
{I}dSS3lStat            lnN        -            -            -            {ss3lerr:<13s}-            -
{I}eChFlstat            lnN        -            -            -            -            {qfliperr:<13s}-
{I}fWZStat              lnN        -            -            -            -            -            {wzerr:<13s}
{I}gWZNorm              lnN        -            -            -            -            -            {wzalpha:<13s}
FakeSyst                lnN        -            1.30         -            -            -            -
FakeRate                lnN        -            {fakeuperr:<13s}-            -            -            -
SSSyst                  lnN        -            -            -            1.20         -            -
JECSyst                 lnN        0.990/0.980  -            -            0.990/1.010  -            -
LepSF                   lnN        1.001        -            -            1.001        -            -
LumSyst                 lnN        1.025        -            1.025        1.025        1.025        -
PU                      lnN        1.02         -            -            1.001        -            -
SigPDF                  lnN        0.990/1.010  -            -            -            -            -
SigQsq                  lnN        1.010/0.990  -            -            -            -            -
TrigSyst                lnN        1.01         -            1.01         1.01         1.01         -
XSec                    lnN        1.06         -            -            -            -            -
bSF                     lnN        1.03         -            -            1.04         -            - """.format(**data)
    return cardstring


#printAllCutflow()

#applyWZNF()
#applyFakeError()
#applyPromptBkgSyst()
blind()
printSummaryCutflow()
statcardfunc = getStatCardStringWithGmN
f = open("SSee.txt", "write"); f.write(statcardfunc("SSee", "001"))
f = open("SSem.txt", "write"); f.write(statcardfunc("SSem", "002"))
f = open("SSmm.txt", "write"); f.write(statcardfunc("SSmm", "003"))
f = open("TL0SFOS.txt", "write"); f.write(statcardfunc("TL0SFOS", "004", "3l"))
f = open("TL1SFOS.txt", "write"); f.write(statcardfunc("TL1SFOS", "005", "3l"))
f = open("TL2SFOS.txt", "write"); f.write(statcardfunc("TL2SFOS", "006", "3l"))
#printAllCutflow()
#f = open("nj2wd.txt", "write")
#f.write(getStatCardStringWithGmN("SSmmNJ2MJJWD", "001"))
#f = open("nj2sb.txt", "write")
#f.write(getStatCardStringWithGmN("SSmmNJ2MJJSB", "002"))
#f = open("nj1.txt", "write")
#f.write(getStatCardStringWithGmN("SSmmNJ1", "003"))
#printSR()
#printCR()
#printCutflow("SSmm", 11, "SSmm")
#printCutflow("SSem", 8, "SSem")
