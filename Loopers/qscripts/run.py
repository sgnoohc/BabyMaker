#!/bin/env python

import os
import sys
import ROOT
from QFramework import TQSampleFolder, TQXSecParser, TQCut, TQAnalysisSampleVisitor, TQSampleInitializer, TQCutflowAnalysisJob, TQCutflowPrinter, TQHistoMakerAnalysisJob, TQHWWPlotter, TQEventlistAnalysisJob
from cuts import *

samples = TQSampleFolder.loadSampleFolder("input.root:samples")

allcuts = getAllCuts()

# Analysis jobs
cutflowjob = TQCutflowAnalysisJob("cutflow")
histojob = TQHistoMakerAnalysisJob()
histojob.importJobsFromTextFiles("histo.cfg", allcuts, "*", True)

allcuts.addAnalysisJob(cutflowjob, "*")
allcuts.printCut("trd")

# Eventlist jobs
eventlistjob = TQEventlistAnalysisJob("eventlist")
eventlistjob.importJobsFromTextFiles("eventlist.cfg", allcuts, "*", True)

# setup a visitor
vis = TQAnalysisSampleVisitor(allcuts,True)

samples.visitSampleFolders(vis, "/sig")
samples.visitSampleFolders(vis, "/typebkg")
samples.visitSampleFolders(vis, "/fake")
samples.visitSampleFolders(vis, "/fakeup")
samples.visitSampleFolders(vis, "/fakedn")
samples.visitSampleFolders(vis, "/data")

#samples.visitSampleFolders(vis)
#samples.visitSampleFolders(vis, "/typebkg/lostlep")
#samples.visitSampleFolders(vis, "/closure")
#samples.visitSampleFolders(vis, "/bkg/W")
#samples.visitSampleFolders(vis, "/bkg/W/WGstar")

samples.writeToFile("output.root", True)
