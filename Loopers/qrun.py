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
parser.enableSamplesWithPriorityLessThan("priority", 3)
parser.addAllSamples(True)

# Connect to a set of babies
init = TQSampleInitializer("/nfs-7/userdata/phchang/WWW_babies/WWW_v1.0.12/skim/", 1)

# By "visiting" the samples with the initializer we actually hook up the samples with root files
samples.visitMe(init)

# Print the content for debugging purpose
#samples.printContents("rt")

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
cuts.printCut("trd")

# setup a visitor to actually loop over ROOT files
vis = TQAnalysisSampleVisitor(cuts,True)

# Run the job!
#samples.visitSampleFolders(vis)
samples.visitSampleFolders(vis, "/sig")
samples.visitSampleFolders(vis, "/typebkg")
samples.visitSampleFolders(vis, "/data")

# Write the output histograms and cutflow cut values and etc.
samples.writeToFile("output.root", True)

# Print cutflow table
blind(samples)
printSummaryCutflow(samples)
printCutflow(samples, "SSee")
printCutflow(samples, "SSem")
printCutflow(samples, "SSmm")
printCutflow(samples, "TL0SFOS")
printCutflow(samples, "TL1SFOS")
printCutflow(samples, "TL2SFOS")
printCutflow(samples, "SSWZee")
printCutflow(samples, "SSWZem")
printCutflow(samples, "SSWZmm")
