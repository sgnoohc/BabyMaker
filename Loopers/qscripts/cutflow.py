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
    #sig  = samples.getCounter("/sig/www", cutname)
    sig  = samples.getCounter("/sig", cutname)
    #bkg  = samples.getCounter("/bkg", cutname)
    #wz   = samples.getCounter("/bkg/VV/WZ", cutname)
    bkg  = samples.getCounter("/typebkg/?/bkg", cutname)
    wz   = samples.getCounter("/typebkg/?/WZ", cutname)
    data = samples.getCounter("/data", cutname)
    #print sig.getCounter(), wz.getCounter(), bkg.getCounter(), data.getCounter()
    nf = samples.getCounter("/data-typebkg/?/bkg-sig", cutname)
    #nf = TQCounter()
    #nf.add(data)
    #nf.add(wz)
    #nf.subtract(bkg)
    #nf.subtract(sig)
    nf.divide(wz)
    print nf.getCounter(), nf.getError(), nf.getError() / nf.getCounter()
    return nf.getCounter(), nf.getError()

#_______________________________________________________________________________
def applyWZNF():
    #nf_ee, nferr_ee = getWZNF("WZCRee")
    #nf_em, nferr_em = getWZNF("WZCRem")
    #nf_mm, nferr_mm = getWZNF("WZCRmm")
    nf_mmnj1, nferr_mmnj1 = getWZNF("WZCRmmNJ1")
    nf_mmnj2, nferr_mmnj2 = getWZNF("WZCRmmNJ2")
    nf_mmnj2sb, nferr_mmnj2sb = getWZNF("WZCRmmNJ2MJJSB")
    nf_mmnj2wd, nferr_mmnj2wd = getWZNF("WZCRmmNJ2MJJWD")
    print samples.getCounter("/typebkg/?/WZ", "SSmmNJ1").getCounter()
    print samples.getCounter("/typebkg/?/WZ", "SSmmNJ2MJJSB").getCounter()
    print samples.getCounter("/typebkg/?/WZ", "SSmmNJ2MJJWD").getCounter()
    print samples.getCounter("/typebkg/?/WZ", "SSmmNJ1").getCounter()      / samples.getCounter("/typebkg/?/WZ", "WZCRmmNJ1").getCounter(), samples.getCounter("/data-typebkg/?/bkg-sig", "WZCRmmNJ1").getCounter(),
    print samples.getCounter("/typebkg/?/WZ", "SSmmNJ2MJJSB").getCounter() / samples.getCounter("/typebkg/?/WZ", "WZCRmmNJ2MJJSB").getCounter(), samples.getCounter("/data-typebkg/?/bkg-sig", "WZCRmmNJ2MJJSB").getCounter()
    print samples.getCounter("/typebkg/?/WZ", "SSmmNJ2MJJWD").getCounter() / samples.getCounter("/typebkg/?/WZ", "WZCRmmNJ2MJJWD").getCounter(), samples.getCounter("/data-typebkg/?/bkg-sig", "WZCRmmNJ2MJJWD").getCounter()
    #nf_1SFOS, nferr_1SFOS = getWZNF("TLWZ1SFOS")
    #nf_2SFOS, nferr_2SFOS = getWZNF("TLWZ2SFOS")
    #samples.setScaleFactor("SSee", nf_ee, nferr_ee, "/bkg/VV/WZ")
    #samples.setScaleFactor("SSem", nf_em, nferr_em, "/bkg/VV/WZ")
    #samples.setScaleFactor("SSmm", nf_mm, nferr_mm, "/bkg/VV/WZ")
    #samples.setScaleFactor("SSee", nf_ee, nferr_ee, "/typebkg/?/WZ")
    #samples.setScaleFactor("SSem", nf_em, nferr_em, "/typebkg/?/WZ")
    #samples.setScaleFactor("SSmm", nf_mm, nferr_mm, "/typebkg/?/WZ")
    #samples.setScaleFactor("TL1SFOS", nf_1SFOS, nferr_1SFOS, "/bkg/VV/WZ")
    #samples.setScaleFactor("TL2SFOS", nf_2SFOS, nferr_2SFOS, "/bkg/VV/WZ")
    #samples.setScaleFactor("TL1SFOS", nf_1SFOS, nferr_1SFOS, "/typebkg/?/WZ")
    #samples.setScaleFactor("TL2SFOS", nf_2SFOS, nferr_2SFOS, "/typebkg/?/WZ")
    samples.setScaleFactor("SSmmNJ1", nf_mmnj1, nferr_mmnj1, "/typebkg/?/WZ")
    samples.setScaleFactor("SSmmNJ2", nf_mmnj2, nferr_mmnj2, "/typebkg/?/WZ")
    samples.setScaleFactor("SSmmNJ2MJJSB", nf_mmnj2sb, nferr_mmnj2sb, "/typebkg/?/WZ")
    samples.setScaleFactor("SSmmNJ2MJJWD", nf_mmnj2wd, nferr_mmnj2wd, "/typebkg/?/WZ")

#_______________________________________________________________________________
def blind():
    cutnames = []
    for i in samples.getListOfCounterNames():
        cutnames.append(str(i))
    cutnames.sort(key=natural_keys)
    for cutname in cutnames:
        if cutname.find("WZCR") == -1:
            samples.setScaleFactor(cutname, 0, 0, "/data")

#_______________________________________________________________________________
def addProcesses(printer, showdata):
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
    if categ == "photon": proc = "/typebkg/photon/bkg"
    if categ == "ss3l": proc = "/typebkg/prompt/bkg+typebkg/lostlep/bkg"
    if categ == "qflip": proc = "/typebkg/qflip/bkg"
    if categ == "wz": proc = "/typebkg/?/WZ"
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
def getStatCardStringWithGmN(cutname, index):
    data = {}
    addCountersToStatCardData("sig", cutname, data)
    addCountersToStatCardData("fake", cutname, data)
    addCountersToStatCardData("photon", cutname, data)
    addCountersToStatCardData("ss3l", cutname, data)
    addCountersToStatCardData("qflip", cutname, data)
    addCountersToStatCardData("wz", cutname, data)
    addFakeRateSystCountersToStatCardData("fakeup", cutname, data)
    wzcr = samples.getCounter("/typebkg/?/WZ", cutname.replace("SSmm", "WZCRmm"), "scaleScheme=.nosf")
    bgcr = samples.getCounter("/typebkg+sig", cutname.replace("SSmm", "WZCRmm"), "scaleScheme=.nosf")
    nzcr = samples.getCounter("/typebkg/?/bkg+sig", cutname.replace("SSmm", "WZCRmm"), "scaleScheme=.nosf")
    wzsr = samples.getCounter("/typebkg/?/WZ", cutname, "scaleScheme=.nosf")
    wzdd = samples.getCounter("/data-typebkg/?/bkg-sig", cutname.replace("SSmm", "WZCRmm"), "scaleScheme=.nosf")
    crdd = samples.getCounter("/data", cutname.replace("SSmm", "WZCRmm"), "scaleScheme=.nosf")
    alpha = TQCounter()
    wzpurity = TQCounter()
    alpha.add(wzsr)
    alpha.divide(wzcr)
    alpha.multiply(wzdd)
    alpha.divide(crdd)
    wzpurity.add(wzdd)
    wzpurity.divide(crdd)
    data["wzcr"] = "{:d}".format(int(samples.getCounter("/data", cutname.replace("SSmm", "WZCRmm")).getCounter()))
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
FakeSyst                lnN        -            1.50         -            -            -            -
FakeRate                lnN        -            {fakeuperr:<13s}-            -            -            -
SSSyst                  lnN        -            -            -            1.15         -            -
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
def getStatCardString(cutname, index):
    data = {}
    addCountersToStatCardData("sig", cutname, data)
    addCountersToStatCardData("fake", cutname, data)
    addCountersToStatCardData("photon", cutname, data)
    addCountersToStatCardData("ss3l", cutname, data)
    addCountersToStatCardData("qflip", cutname, data)
    addCountersToStatCardData("wz", cutname, data)
    nf, nf_err = getWZNF(cutname.replace("SSmm", "WZCRmm"))
    data["wzalpha"] = "{:.3f}".format(nf_err / nf + 1)
    data["I"] = index
    cardstring = """imax 1 number of bins
jmax 5 number of processes minus 1
kmax 18 number of nuisance parameters
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
FakeSyst                lnN        -            1.50         -            -            -            -
SSSyst                  lnN        -            -            -            1.10         -            -
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
blind()
printAllCutflow()
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
