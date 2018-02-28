#!/bin/env python

import os
import ROOT
from QFramework import TQSampleFolder, TQEventlistPrinter, TQTaggable
from rooutil import plottery_wrapper as p

from cuts import bkg_types_SS
from cuts import bkg_types_3L

ROOT.gROOT.SetBatch(True)

samples = TQSampleFolder.loadSampleFolder("validate.root:samples")
#samples.getSampleFolder("/samples/bkg/mm/ttV").printContents("trd")
printer = TQEventlistPrinter(samples)
printer.addCut("SSem")
#printer.addProcess("/sig/www")
#printer.addProcess("/typebkg")
printer.addProcess("/samples/lostlep/val_wz_100")
printer.addProcess("/samples/lostlep/val_wz_18")
printer.writeEventlists("evtlist", "eventlists", "verbose=true");
