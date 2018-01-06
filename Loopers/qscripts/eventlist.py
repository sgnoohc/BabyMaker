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
printer.addCut("SSmmNJ2MJJWD")
printer.addCut("SSmmNJ2MJJSB")
printer.addCut("SSmmNJ1")
#printer.addProcess("/sig")
printer.addProcess("/typebkg/photon")
#printer.addProcess("/typebkg/fakes")
#printer.addProcess("/typebkg/[fakes+photon]")
#printer.addProcess("/typebkg")
printer.writeEventlists("evtlist", "eventlists", "format.nSignificantDigits=5");
#printer.writeEventlists("lepton", "eventlists", "format.nSignificantDigits=20");
