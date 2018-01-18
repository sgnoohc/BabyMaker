#!/bin/env python

import os
import ROOT
from QFramework import TQSampleFolder, TQXSecParser, TQCut, TQAnalysisSampleVisitor, TQSampleInitializer, TQCutflowAnalysisJob, TQCutflowPrinter, TQHistoMakerAnalysisJob, TQNFCalculator, TQCounter
from rooutil import plottery_wrapper as p

from cuts import bkg_types_SS
from cuts import bkg_types_3L

ROOT.gROOT.SetBatch(True)

samples = TQSampleFolder.loadSampleFolder("output.root:samples")

#_______________________________________________________________________________
def getWZNF(cutname):
    sig  = samples.getCounter("/sig/www", cutname)
    bkg  = samples.getCounter("/bkg", cutname)
    wz   = samples.getCounter("/bkg/VV/WZ", cutname)
    data = samples.getCounter("/data", cutname)
    nf = TQCounter()
    nf.add(data)
    nf.add(wz)
    nf.subtract(bkg)
    nf.subtract(sig)
    nf.divide(wz)
    return nf.getCounter(), nf.getError()

#_______________________________________________________________________________
def applyWZNF():
    nf_ee, nferr_ee = getWZNF("WZCRee")
    nf_em, nferr_em = getWZNF("WZCRem")
    nf_mm, nferr_mm = getWZNF("WZCRmm")
    nf_1SFOS, nferr_1SFOS = getWZNF("TLWZ1SFOS")
    nf_2SFOS, nferr_2SFOS = getWZNF("TLWZ2SFOS")
    samples.setScaleFactor("SSee", nf_ee, nferr_ee, "/bkg/VV/WZ")
    samples.setScaleFactor("SSem", nf_em, nferr_em, "/bkg/VV/WZ")
    samples.setScaleFactor("SSmm", nf_mm, nferr_mm, "/bkg/VV/WZ")
    samples.setScaleFactor("SSee", nf_ee, nferr_ee, "/typebkg/?/WZ")
    samples.setScaleFactor("SSem", nf_em, nferr_em, "/typebkg/?/WZ")
    samples.setScaleFactor("SSmm", nf_mm, nferr_mm, "/typebkg/?/WZ")
    samples.setScaleFactor("TL1SFOS", nf_1SFOS, nferr_1SFOS, "/bkg/VV/WZ")
    samples.setScaleFactor("TL2SFOS", nf_2SFOS, nferr_2SFOS, "/bkg/VV/WZ")
    samples.setScaleFactor("TL1SFOS", nf_1SFOS, nferr_1SFOS, "/typebkg/?/WZ")
    samples.setScaleFactor("TL2SFOS", nf_2SFOS, nferr_2SFOS, "/typebkg/?/WZ")

#_______________________________________________________________________________
def addProcesses(printer, showdata):
    printer.loadSystematics("output.root:samples")
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
    printer.addCutflowProcess("/typebkg/prompt", "prompt")
    printer.addCutflowProcess("/typebkg/qflip", "qflip")
    printer.addCutflowProcess("/typebkg/lostlep", "lostlep")
    printer.addCutflowProcess("/typebkg/fakes", "fakes")
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("/fake", "(data-drv. fake)")
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("/typebkg/photon", "photon")
#    printer.addCutflowProcess("/typebkg/others", "others")
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("/bkg", "Tot. MC")
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("/typebkg", "Bkg.")
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("/fake+typebkg-typebkg/fakes", "B. w/ Fake est.")
#    printer.addCutflowProcess("|", "|")
#    printer.addCutflowProcess("$signif(/sig,/bkg)", "Signif. MC")
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("$signif(/sig,/fake+typebkg-typebkg/fakes)", "Signif.")
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
def printCutflow(region_prefix, ncut, output_name, chan, showdata=False):
    # Cutflow printing
    printer = TQCutflowPrinter(samples)
    printer.addCutflowCut("BaseCut", "BaseCut")
    printer.addCutflowCut("base_{}".format(region_prefix), "base_{}".format(region_prefix))
    for i in xrange(0, ncut):
        printer.addCutflowCut("cut{}_{}".format(i, region_prefix), "cut{}_{}".format(i, region_prefix), 1)
    printer.addCutflowCut("{}".format(region_prefix), "{}".format(region_prefix), 1)
    addProcesses(printer, showdata, chan)
    table = printer.createTable()
    table.writeCSV("cutflows/{}.csv".format(output_name))
    table.writeHTML("cutflows/{}.html".format(output_name))
    table.writeLaTeX("cutflows/{}.tex".format(output_name))
    table.writePlain("cutflows/{}.txt".format(output_name))

#applyWZNF()
printSR()
printCR()
