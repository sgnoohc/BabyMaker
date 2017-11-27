#!/bin/env python

import os
import ROOT
from QFramework import TQSampleFolder, TQXSecParser, TQCut, TQAnalysisSampleVisitor, TQSampleInitializer, TQCutflowAnalysisJob, TQCutflowPrinter, TQHistoMakerAnalysisJob
from rooutil import plottery_wrapper as p

from cuts import bkg_types_SS
from cuts import bkg_types_3L

ROOT.gROOT.SetBatch(True)

samples = TQSampleFolder.loadSampleFolder("output.root:samples")
count = 0
#for i in samples.getListOfHistogramNames(): count+=1
#print count

#_____________________________________________________________________________________
def plotFig4():
    # Options
    alloptions= {
                "ratio_range":[0,2],
                "output_name": "plots/fig4.png"
                }
    histname = "{SSee, SSem, SSmm, TL0SFOS, TL1SFOS, TL2SFOS}"
    sigs = [ samples.getHistogram("/sig/mm/www", histname).Clone("WWW") ]
    bgs  = [ samples.getHistogram("/bkg/mm/top", histname).Clone("top"),
             samples.getHistogram("/bkg/mm/ttV", histname).Clone("ttV"),
             samples.getHistogram("/bkg/mm/VVV", histname).Clone("VVV"),
             samples.getHistogram("/bkg/mm/VV", histname).Clone("VV"),
             samples.getHistogram("/bkg/mm/W", histname).Clone("W"),
             samples.getHistogram("/bkg/mm/Z", histname).Clone("Z") ]
    data = samples.getHistogram("/data/mm", histname).Clone("Data")
    data = None
    p.plot_hist(
            sigs = sigs,
            bgs  = bgs,
            data = data,
            options=alloptions)

#_____________________________________________________________________________________
def plotFig5():
    # Options
    alloptions= {
                "ratio_range":[0,2],
                "output_name": "plots/fig4.png"
                }
    histname = "{WZCRee, WZCRem, WZCRmm}"
    sigs = [ samples.getHistogram("/sig/mm/www", histname).Clone("WWW") ]
    bgs  = [ samples.getHistogram("/bkg/mm/top", histname).Clone("top"),
             samples.getHistogram("/bkg/mm/ttV", histname).Clone("ttV"),
             samples.getHistogram("/bkg/mm/VVV", histname).Clone("VVV"),
             samples.getHistogram("/bkg/mm/VV", histname).Clone("VV"),
             samples.getHistogram("/bkg/mm/W", histname).Clone("W"),
             samples.getHistogram("/bkg/mm/Z", histname).Clone("Z") ]
   #data = samples.getHistogram("/samples/data/mm", histname).Clone("Data")
    data = None
    p.plot_hist(
            sigs = sigs,
            bgs  = bgs,
            data = data,
            options=alloptions)

#_____________________________________________________________________________________
def plotFig4ByType():
    # Options
    alloptions= {
                "ratio_range":[0,2],
                "output_name": "plots/fig4bytype.png"
                }
    histname = "{SSee, SSem, SSmm, TL0SFOS, TL1SFOS, TL2SFOS}"
    sigs = [ samples.getHistogram("/sig", histname).Clone("WWW") ]
    bgs  = [ samples.getHistogram("/typebkg/prompt", histname).Clone("Prompt"),
             samples.getHistogram("/typebkg/qflip", histname).Clone("Q-flips"),
             samples.getHistogram("/typebkg/lostlep", histname).Clone("Lost-lepton"),
             samples.getHistogram("/typebkg/fakes", histname).Clone("fakes"),
             samples.getHistogram("/typebkg/photon", histname).Clone("#gamma#rightarrowl"),
             samples.getHistogram("/typebkg/others", histname).Clone("Others")
            ]
    colors = [ 2001, 2007, 2003, 2005, 920, 2012 ]
   #data = samples.getHistogram("/samples/data/mm", histname).Clone("Data")
    data = None
    p.plot_hist(
            sigs = sigs,
            bgs  = bgs,
            data = data,
            colors = colors,
            options=alloptions)

#_____________________________________________________________________________________
def plotFig4ByTypeFakeEst():
    # Options
    alloptions= {
                "ratio_range":[0,2],
                "output_name": "plots/fig4bytypefakeest.png"
                }
    histname = "{SSee, SSem, SSmm, TL0SFOS, TL1SFOS, TL2SFOS}"
    sigs = [ samples.getHistogram("/sig", histname).Clone("WWW") ]
    bgs  = [ samples.getHistogram("/typebkg/prompt", histname).Clone("Prompt"),
             samples.getHistogram("/typebkg/qflip", histname).Clone("Q-flips"),
             samples.getHistogram("/typebkg/lostlep", histname).Clone("Lost-lepton"),
             samples.getHistogram("/fake/", histname).Clone("fakes"),
             samples.getHistogram("/typebkg/photon", histname).Clone("#gamma#rightarrowl"),
             samples.getHistogram("/typebkg/others", histname).Clone("Others")
            ]
    colors = [ 2001, 2007, 2003, 2005, 920, 2012 ]
   #data = samples.getHistogram("/samples/data/mm", histname).Clone("Data")
    data = None
    p.plot_hist(
            sigs = sigs,
            bgs  = bgs,
            data = data,
            colors = colors,
            options=alloptions)

#_____________________________________________________________________________________
def plotByProc(histname, output_name):
    # Options
    alloptions= {
                "ratio_range":[0,2],
                "output_name": "plots/{}.png".format(output_name)
                }
    sigs = [ samples.getHistogram("/sig/mm/www", histname).Clone("WWW") ]
    bgs  = [ samples.getHistogram("/bkg/mm/top", histname).Clone("top"),
             samples.getHistogram("/bkg/mm/ttV", histname).Clone("ttV"),
             samples.getHistogram("/bkg/mm/VVV", histname).Clone("VVV"),
             samples.getHistogram("/bkg/mm/VV", histname).Clone("VV"),
             samples.getHistogram("/bkg/mm/W", histname).Clone("W"),
             samples.getHistogram("/bkg/mm/Z", histname).Clone("Z") ]
    data = samples.getHistogram("/data/mm", histname).Clone("Data")
    p.plot_hist(
            sigs = sigs,
            bgs  = bgs,
            data = data,
            options=alloptions)

plotFig4()
plotFig5()
plotFig4ByType()
plotFig4ByTypeFakeEst()
