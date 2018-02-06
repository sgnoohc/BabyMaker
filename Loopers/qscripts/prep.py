#!/bin/env python

import os
import sys
import ROOT
from QFramework import TQSampleFolder, TQXSecParser, TQCut, TQAnalysisSampleVisitor, TQSampleInitializer, TQCutflowAnalysisJob, TQCutflowPrinter, TQHistoMakerAnalysisJob, TQHWWPlotter, TQEventlistAnalysisJob
from cuts import *

def addSampleFolderFromXSecParser(samplefolder):
    parser = TQXSecParser(samplefolder);
    parser.readCSVfile("samples.cfg")
    parser.readMappingFromColumn("*path*")
    parser.enableSamplesWithPriorityLessThan("priority", 2)
    parser.addAllSamples(True)

# File IO related
samples = TQSampleFolder("samples")
addSampleFolderFromXSecParser(samples)

#init = TQSampleInitializer("/hadoop/cms/store/user/phchang/metis/wwwanalysis/WWW_v0_1_16_minibaby_v7/", 1)
#init = TQSampleInitializer("/hadoop/cms/store/user/phchang/metis/wwwanalysis/WWW_v0_1_17_minibaby_v1/", 1)
#init = TQSampleInitializer("/hadoop/cms/store/user/phchang/metis/wwwanalysis/WWW_v0_1_17_minibaby_v6/", 1)
#init = TQSampleInitializer("/hadoop/cms/store/user/phchang/metis/wwwanalysis/WWW_v0_1_17_minibaby_v9/", 1)
#init = TQSampleInitializer("/hadoop/cms/store/user/phchang/metis/wwwanalysis/WWW_v0_1_18_minibaby_v1.1/", 1) # Reproducing old numbers
#init = TQSampleInitializer("/hadoop/cms/store/user/phchang/metis/wwwanalysis/WWW_v0_1_18_minibaby_v1.2/", 1) # Reproducing old numbers with new Functions.h
init = TQSampleInitializer("/hadoop/cms/store/user/phchang/metis/wwwanalysis/WWW_v0_1_18_minibaby_v1.3/", 1) # Version "1" ID from Functions.C but the loose ID is not correct yet
samples.visitMe(init)

samples.printContents("rtd")

samples.writeToFile("input.root", True)
