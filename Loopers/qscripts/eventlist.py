#!/bin/env python

import os
import ROOT
from QFramework import TQSampleFolder, TQEventlistPrinter, TQTaggable
from rooutil import plottery_wrapper as p

from cuts import bkg_types_SS
from cuts import bkg_types_3L

ROOT.gROOT.SetBatch(True)

samples = TQSampleFolder.loadSampleFolder("output.root:samples")
#samples.getSampleFolder("/samples/bkg/mm/ttV").printContents("trd")
printer = TQEventlistPrinter(samples)
printer.addCut("TL2SFOS")
printer.addProcess("/bkg")
printer.addProcess("/typebkg")
printer.writeEventlists("evtlist", "eventlists", "verbose=true");
