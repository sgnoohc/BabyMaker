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
    sig  = samples.getCounter("/samples/sig/mm/www", cutname)
    bkg  = samples.getCounter("/samples/bkg/mm", cutname)
    wz   = samples.getCounter("/samples/bkg/mm/VV/WZ", cutname)
    data = samples.getCounter("/samples/data/mm", cutname)
    nf = TQCounter()
    nf.add(data)
    nf.add(wz)
    nf.subtract(bkg)
    nf.subtract(sig)
    nf.divide(wz)
    return nf.getCounter()

#_______________________________________________________________________________
def applyWZNF(ncut):
    for i in xrange(0, ncut):
        nf = getWZNF("WZCRmm_cut{}".format(i))
        samples.setScaleFactor("SSmm_cut{}".format(i), nf, "/samples/bkg/mm/VV/WZ")

#_______________________________________________________________________________
# Supports only printing out by process boundaries
def printCutflow(region_prefix, ncut, output_name):
    # Cutflow printing
    printer = TQCutflowPrinter(samples)
    for i in xrange(0, ncut):
        printer.addCutflowCut("cut{}_{}".format(i, region_prefix), "cut{}_{}".format(i, region_prefix), 1)
    printer.addCutflowCut("{}".format(region_prefix), "{}".format(region_prefix), 1)
    printer.addCutflowProcess("/samples/sig/mm/www", "WWW")
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("/samples/bkg/mm/top/singleTop", "Top")
    printer.addCutflowProcess("/samples/bkg/mm/top/ttbar/tt1l", "Top")
    printer.addCutflowProcess("/samples/bkg/mm/top/ttbar/tt2l", "Top")
    printer.addCutflowProcess("/samples/bkg/mm/ttV", "ttV")
    printer.addCutflowProcess("/samples/bkg/mm/VVV", "VVV")
    printer.addCutflowProcess("/samples/bkg/mm/VV/ZZ", "VV/ZZ")
    printer.addCutflowProcess("/samples/bkg/mm/VV/WW", "VV/WW")
    printer.addCutflowProcess("/samples/bkg/mm/VV/WZ", "VV/WZ")
    printer.addCutflowProcess("/samples/bkg/mm/W", "W")
    printer.addCutflowProcess("/samples/bkg/mm/Z", "Z")
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("/samples/bkg/mm", "total bkg.")
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("/samples/typebkg/prompt", "prompt")
    printer.addCutflowProcess("/samples/typebkg/qflip", "qflip")
    printer.addCutflowProcess("/samples/typebkg/lostlep", "lostlep")
    printer.addCutflowProcess("/samples/typebkg/fakes", "fakes")
    printer.addCutflowProcess("/samples/typebkg/photon", "photon")
    printer.addCutflowProcess("/samples/typebkg/others", "others")
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("/samples/fake/mm", "fake bkg.")
    printer.addCutflowProcess("|", "|")
    printer.addCutflowProcess("/samples/typebkg", "total bkg.")
#    printer.addCutflowProcess("|", "|")
#    printer.addCutflowProcess("/samples/data/mm", "Data")
#    printer.addCutflowProcess("|", "|")
#    printer.addCutflowProcess("$ratio(/samples/data/mm,/samples/bkg/mm)", "Ratio")
    table = printer.createTable()
    table.writeCSV("cutflow/{}.csv".format(output_name))
    table.writeHTML("cutflow/{}.html".format(output_name))
    table.writeLaTeX("cutflow/{}.tex".format(output_name))
    table.writePlain("cutflow/{}.txt".format(output_name))

#_______________________________________________________________________________
# Supports only printing one by one
def printYieldSS(region_prefix, icut, output_name):
    printer = TQCutflowPrinter(samples)
    for bkg_type in bkg_types_SS:
        printer.addCutflowCut("{}_{}_cut{}".format(region_prefix, bkg_type, icut), "{}".format(bkg_type))
    printer.addCutflowCut("|", "|")
    printer.addCutflowCut("{}_Bkg_cut{}".format(region_prefix, icut), "Total Bkg.")
    printer.addCutflowCut("|", "|")
    printer.addCutflowCut("{}_WWW_cut{}".format(region_prefix, icut), "Signal")
    printer.addCutflowCut("|", "|")
    printer.addCutflowCut("{}_DataMM_cut{}".format(region_prefix, icut), "Data")
    printer.addCutflowProcess("/samples", "{}_cut{}".format(region_prefix, icut))
    table = printer.createTable()
    table.writeCSV("cutflow/{}.csv".format(output_name))
    table.writeHTML("cutflow/{}.html".format(output_name))
    table.writeLaTeX("cutflow/{}.tex".format(output_name))
    table.writePlain("cutflow/{}.txt".format(output_name))

#_______________________________________________________________________________
# Supports only printing one by one
def printYield3L(region_prefix, icut, output_name):
    printer = TQCutflowPrinter(samples)
    for bkg_type in bkg_types_3L:
        printer.addCutflowCut("{}_{}_cut{}".format(region_prefix, bkg_type, icut), "{}".format(bkg_type))
    printer.addCutflowCut("|", "|")
    printer.addCutflowCut("{}_Bkg_cut{}".format(region_prefix, icut), "Total Bkg.")
    printer.addCutflowCut("|", "|")
    printer.addCutflowCut("{}_WWW_cut{}".format(region_prefix, icut), "Signal")
    printer.addCutflowCut("|", "|")
    printer.addCutflowCut("{}_DataMM_cut{}".format(region_prefix, icut), "Data")
    printer.addCutflowProcess("/samples", "{}_cut{}".format(region_prefix, icut))
    table = printer.createTable()
    table.writeCSV("cutflow/{}.csv".format(output_name))
    table.writeHTML("cutflow/{}.html".format(output_name))
    table.writeLaTeX("cutflow/{}.tex".format(output_name))
    table.writePlain("cutflow/{}.txt".format(output_name))

#applyWZNF(11)
printCutflow("SSee", 11, "SSee_cutflow")
printCutflow("SSem", 11, "SSem_cutflow")
printCutflow("SSmm", 11, "SSmm_cutflow")
#printCutflow("WZCRmm", 11, "WZCRmm_cutflow")
#printYieldSS("SSmm", 10, "SSmm_type_cutflow")
#printYield3L("WZCRmm", 10, "WZCRmm_type_cutflow")

print getWZNF("WZCRmm_cut5")

#  // addCutflowProcess("$ratio(data/ee,bkg/ee)");
#  //
#  // - the signal significance at a given cut stage
#  //
#  // addCutflowProcess("$signif(sig/ee,bkg/ee)");
#  //
#  // - the pull of two processes
#  //
#  // addCutflowProcess("$pull(data/ee,bkg/ee)");
