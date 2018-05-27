#!/bin/env python

import os
import sys
import ROOT
from QFramework import TQSampleFolder, TQXSecParser, TQCut, TQAnalysisSampleVisitor, TQSampleInitializer, TQCutflowAnalysisJob, TQCutflowPrinter, TQHistoMakerAnalysisJob
from rooutil.qutils import *
from errors import E

ROOT.gROOT.SetBatch(True)
samples = TQSampleFolder.loadSampleFolder("output.root:samples")

printer = TQCutflowPrinter(samples)
printer.addCutflowCut("TwoElLoose", "TwoElLoose", True)
printer.addCutflowCut("TwoElTight", "TwoElTight", True)
printer.addCutflowCut("TwoElLoosePredictEM1D", "TwoElLoosePredictEM1D", True)
printer.addCutflowCut("TwoElTightPredictEM1D", "TwoElTightPredictEM1D", True)
printer.addCutflowCut("TwoMuLoose", "TwoMuLoose", True)
printer.addCutflowCut("TwoMuTight", "TwoMuTight", True)
printer.addCutflowCut("TwoMuLoosePredict", "TwoMuLoosePredict", True)
printer.addCutflowCut("TwoMuTightPredict", "TwoMuTightPredict", True)
printer.addCutflowCut("TwoElLoosePredictHF", "TwoElLoosePredictHF", True)
printer.addCutflowCut("TwoElTightPredictHF", "TwoElTightPredictHF", True)
printer.addCutflowCut("TwoElLoosePredictComb", "TwoElLoosePredictComb", True)
printer.addCutflowCut("TwoElTightPredictComb", "TwoElTightPredictComb", True)
printer.addCutflowCut("TwoElLoosePredictEM1DLF", "TwoElLoosePredictEM1DLF", True)
printer.addCutflowCut("TwoElTightPredictEM1DLF", "TwoElTightPredictEM1DLF", True)
printer.addCutflowProcess("|", "|")
printer.addCutflowProcess("/W/incl", "W incl")
printer.addCutflowProcess("/W/HT", "W HT")
printer.addCutflowProcess("/top", "top")
printer.addCutflowProcess("/top+W/HT", "top+W HT")
table = printer.createTable("style.firstColumnAlign=l")
path = "cutflows/"
try:
    os.makedirs(path)
except OSError as exc:  # Python >2.5
    if exc.errno == errno.EEXIST and os.path.isdir(path):
        pass
    else:
        raise
regionname = "table"
table.writeCSV("cutflows/{}.csv".format(regionname))
table.writeHTML("cutflows/{}.html".format(regionname))
table.writeLaTeX("cutflows/{}.tex".format(regionname))
table.writePlain("cutflows/{}.txt".format(regionname))
