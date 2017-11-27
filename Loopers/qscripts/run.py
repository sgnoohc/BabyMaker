#!/bin/env python

import os
import sys
import ROOT
from QFramework import TQSampleFolder, TQXSecParser, TQCut, TQAnalysisSampleVisitor, TQSampleInitializer, TQCutflowAnalysisJob, TQCutflowPrinter, TQHistoMakerAnalysisJob, TQHWWPlotter, TQEventlistAnalysisJob
from cuts import *

# File IO related
samples = TQSampleFolder("samples")
parser = TQXSecParser(samples);
parser.readCSVfile("samples.cfg")
parser.readMappingFromColumn("*path*")
#parser.addPathVariant("channel","mm")
parser.enableSamplesWithPriorityLessThan("priority", 2)
parser.addAllSamples(True)
init = TQSampleInitializer("/hadoop/cms/store/user/phchang/metis/wwwanalysis/WWW_v0_1_16_minibaby_v7/", 1)
samples.visitMe(init)

samples.writeToFile("input.root", True)

allcuts = getAllCuts()

# Analysis jobs
cutflowjob = TQCutflowAnalysisJob("cutflow")
histojob = TQHistoMakerAnalysisJob()
#histojob.importJobsFromTextFiles("histo.cfg", allcuts, "*", True)

allcuts.addAnalysisJob(cutflowjob, "*")
allcuts.printCut("trd")

# Eventlist jobs
eventlistjob = TQEventlistAnalysisJob("eventlist")
eventlistjob.importJobsFromTextFiles("eventlist.cfg", allcuts, "*", True)

# setup a visitor
vis = TQAnalysisSampleVisitor(allcuts,True)

samples.visitSampleFolders(vis)
#samples.visitSampleFolders(vis, "/samples/bkg/mm/ttV")

samples.writeToFile("output.root", True)

