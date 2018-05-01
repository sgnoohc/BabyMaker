#!/bin/env python

import os
import sys
import ROOT
from QFramework import TQSampleFolder, TQXSecParser, TQCut, TQAnalysisSampleVisitor, TQSampleInitializer, TQCutflowAnalysisJob, TQCutflowPrinter, TQHistoMakerAnalysisJob, TQHWWPlotter, TQEventlistAnalysisJob
from qcuts import *

# Create the master TQSampleFolder
samples = TQSampleFolder("samples")

# Created a sample information parser
parser = TQXSecParser(samples);

# Read the configuration file that contains what sample names are and how to categorize them
parser.readCSVfile("samples.cfg")
parser.readMappingFromColumn("*path*")
parser.enableSamplesWithPriorityLessThan("priority", 2)
parser.addAllSamples(True)

# Decide that path where the root files are sitting
import socket
if socket.gethostname().find("pcc007") != -1: # philip's local mac computer
    samplepath = "/Users/phchang/work/analyses/www/code/VVVBabyMaker/Loopers/samples/"
else:
    samplepath = "/nfs-7/userdata/phchang/WWW_babies/WWW_v1.0.20/skim/"

print samplepath

# By "visiting" the samples with the initializer we actually hook up the samples with root files
init = TQSampleInitializer(samplepath, 1)
samples.visitMe(init)

# Print the content for debugging purpose
#samples.printContents("rtd")

# cuts are defined in qcuts.py

# Analysis jobs
cutflowjob = TQCutflowAnalysisJob("cutflow")
cuts.addAnalysisJob(cutflowjob, "*")

histojob = TQHistoMakerAnalysisJob()
histojob.importJobsFromTextFiles("histo.cfg", cuts, "*", True)

# Eventlist jobs
#eventlistjob = TQEventlistAnalysisJob("eventlist")
#eventlistjob.importJobsFromTextFiles("eventlist.cfg", cuts, "*", True)

# Print cuts for debug purpose
#cuts.printCut("trd")

# setup a visitor to actually loop over ROOT files
vis = TQAnalysisSampleVisitor(cuts,True)

# Run the job!
samples.visitSampleFolders(vis)

# Write the output histograms and cutflow cut values and etc.
samples.writeToFile("output.root", True)

# Print cutflow table
printCutflow(samples, "SSWZee")
printCutflow(samples, "SSWZem")
printCutflow(samples, "SSWZmm")
blind(samples)
printSummaryCutflow(samples)
printCutflow(samples, "SSee")
printCutflow(samples, "SSem")
printCutflow(samples, "SSmm")
printCutflow(samples, "TL0SFOS")
printCutflow(samples, "TL1SFOS")
printCutflow(samples, "TL2SFOS")
