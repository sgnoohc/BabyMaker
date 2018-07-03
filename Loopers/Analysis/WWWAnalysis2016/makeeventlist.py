#!/bin/env python

import os
import sys
import ROOT
from QFramework import TQSampleFolder, TQEventlistPrinter, TQTaggable
from rooutil import plottery_wrapper as p

ROOT.gROOT.SetBatch(True)

path = "eventlists/"
filename = sys.argv[1]

samples = TQSampleFolder.loadSampleFolder("{}:samples".format(filename))
printer = TQEventlistPrinter(samples)
printer.addCut("SRSSeeFull")
printer.addCut("SRSSemFull")
printer.addCut("SRSSmmFull")
printer.addCut("SideSSeeFull")
printer.addCut("SideSSemFull")
printer.addCut("SideSSmmFull")
printer.addCut("SR0SFOSFull")
printer.addCut("SR1SFOSFull")
printer.addCut("SR2SFOSFull")
printer.addCut("WZCRSSeeFull")
printer.addCut("WZCRSSemFull")
printer.addCut("WZCRSSmmFull")
printer.addCut("WZCR1SFOSFull")
printer.addCut("WZCR2SFOSFull")
printer.addProcess("/typebkg")
printer.writeEventlists("lepton", "eventlists", "verbose=true");
