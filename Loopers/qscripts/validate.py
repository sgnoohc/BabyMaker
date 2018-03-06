#!/bin/env python

import os
import sys
import ROOT
from QFramework import TQSampleFolder, TQXSecParser, TQCut, TQAnalysisSampleVisitor, TQSampleInitializer, TQCutflowAnalysisJob, TQCutflowPrinter, TQHistoMakerAnalysisJob, TQHWWPlotter, TQEventlistAnalysisJob
from cuts import *

f = open("validate.cfg", "w")

sampledir = "/home/users/phchang/public_html/analysis/www/code/VVVBabyMaker/Loopers/"

import glob
#files = glob.glob("{}/tzq.root".format(sampledir))
#files = glob.glob("{}/output.root".format(sampledir))
#files = glob.glob("samples/*".format(sampledir))
files = glob.glob("../val_www_2l_ext*".format(sampledir))
f.write("SampleID , path , priority , usemcweights , treename , usefakeweight , variation\n")

#categs = [ "prompt", "lostlep", "fakes", "photon", "others", "qflip", "www", "total" ]
categs = [ "www" ]

for categ in categs:
    for rf in files:
        name = os.path.splitext(os.path.basename(rf))[0]
        if categ == "total":
            line = "{sample} , /samples/{categ} , 1 , true , t , false , nominal".format(sample=name, categ=categ)
        else:
            line = "{sample} , /samples/{categ} , 1 , true , t_{categ} , false , nominal".format(sample=name, categ=categ)
        f.write(line + "\n")

f.close()

def addSampleFolderFromXSecParser(samplefolder):
    parser = TQXSecParser(samplefolder);
    parser.readCSVfile("validate.cfg")
    parser.readMappingFromColumn("*path*")
    parser.enableSamplesWithPriorityLessThan("priority", 2)
    parser.addAllSamples(True)

# File IO related
samples = TQSampleFolder("samples")
addSampleFolderFromXSecParser(samples)

init = TQSampleInitializer(sampledir, 1) # Old lepton id v17
samples.visitMe(init)

samples.printContents("rtd")

#samples.writeToFile("input.root", True)

#-----

#samples = TQSampleFolder.loadSampleFolder("input.root:samples")

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

samples.visitSampleFolders(vis)

samples.writeToFile("validate.root", True)


printer = TQCutflowPrinter(samples)
printer.addCutflowCut("cut0_SSee", "cut0_SSee", True)
printer.addCutflowCut("cut0_SSem", "cut0_SSem", True)
printer.addCutflowCut("cut0_SSmm", "cut0_SSmm", True)
printer.addCutflowCut("|", "|")
printer.addCutflowCut("cut1_SSee", "cut1_SSee", True)
printer.addCutflowCut("cut1_SSem", "cut1_SSem", True)
printer.addCutflowCut("cut1_SSmm", "cut1_SSmm", True)
printer.addCutflowCut("|", "|")
printer.addCutflowCut("cut2_SSee", "cut2_SSee", True)
printer.addCutflowCut("cut2_SSem", "cut2_SSem", True)
printer.addCutflowCut("cut2_SSmm", "cut2_SSmm", True)
printer.addCutflowCut("|", "|")
printer.addCutflowCut("SSee", "SSee", True)
printer.addCutflowCut("SSem", "SSem", True)
printer.addCutflowCut("SSmm", "SSmm", True)
printer.addCutflowCut("|", "|")
printer.addCutflowCut("TL0SFOS", "TL0SFOS", True)
printer.addCutflowCut("TL1SFOS", "TL1SFOS", True)
printer.addCutflowCut("TL2SFOS", "TL2SFOS", True)
printer.addCutflowCut("|", "|")
printer.addCutflowCut("WZCRee", "WZCRee")
printer.addCutflowCut("WZCRem", "WZCRem")
printer.addCutflowCut("WZCRmm", "WZCRmm")
printer.addCutflowCut("|", "|")
printer.addCutflowCut("TLWZ1SFOS", "TLWZ1SFOS")
printer.addCutflowCut("TLWZ2SFOS", "TLWZ2SFOS")
for categ in categs:
    for rf in files:
        name = os.path.splitext(os.path.basename(rf))[0]
        printer.addCutflowProcess("/samples/{}/{}".format(categ, name), name+"_"+categ)
    printer.addCutflowProcess("|", "|")
table = printer.createTable("style.firstColumnAlign=l")
output_name = "validate"
table.writeCSV("cutflows/{}.csv".format(output_name))
table.writeHTML("cutflows/{}.html".format(output_name))
table.writeLaTeX("cutflows/{}.tex".format(output_name))
table.writePlain("cutflows/{}.txt".format(output_name))

