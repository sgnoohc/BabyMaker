#!/bin/env python

import os
import ROOT
from QFramework import TQSampleFolder, TQXSecParser, TQCut, TQAnalysisSampleVisitor, TQSampleInitializer, TQCutflowAnalysisJob, TQCutflowPrinter, TQHistoMakerAnalysisJob
from rooutil import plottery_wrapper as p
from plottery import plottery as ply

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
    sigs = [ samples.getHistogram("/sig", histname).Clone("WWW") ]
    bgs  = [ samples.getHistogram("/bkg/top", histname).Clone("top"),
             samples.getHistogram("/bkg/ttV", histname).Clone("ttV"),
             samples.getHistogram("/bkg/VVV", histname).Clone("VVV"),
             samples.getHistogram("/bkg/VV", histname).Clone("VV"),
             samples.getHistogram("/bkg/W", histname).Clone("W"),
             samples.getHistogram("/bkg/Z", histname).Clone("Z") ]
   #data = samples.getHistogram("/data", histname).Clone("Data")
    data = None
    colors = [ 2005, 2001, 2012, 2003, 920, 2007 ]
    p.plot_hist(
            sigs = sigs,
            bgs  = bgs,
            data = data,
            colors = colors,
            options=alloptions)

#_____________________________________________________________________________________
def plotFig4a():
    # Options
    alloptions= {
                "ratio_range":[0,2],
                "output_name": "plots/fig4a.png"
                }
    histname = "{SSee+ SSem+ SSmm, TL0SFOS+ TL1SFOS+ TL2SFOS}"
    sigs = [ samples.getHistogram("/sig", histname).Clone("WWW") ]
    bgs  = [ samples.getHistogram("/bkg/top", histname).Clone("top"),
             samples.getHistogram("/bkg/ttV", histname).Clone("ttV"),
             samples.getHistogram("/bkg/VVV", histname).Clone("VVV"),
             samples.getHistogram("/bkg/VV", histname).Clone("VV"),
             samples.getHistogram("/bkg/W", histname).Clone("W"),
             samples.getHistogram("/bkg/Z", histname).Clone("Z") ]
   #data = samples.getHistogram("/data", histname).Clone("Data")
    data = None
    colors = [ 2005, 2001, 2012, 2003, 920, 2007 ]
    p.plot_hist(
            sigs = sigs,
            bgs  = bgs,
            data = data,
            colors = colors,
            options=alloptions)

#_____________________________________________________________________________________
def plotFig5():
    # Options
    alloptions= {
                "ratio_range":[0,2],
                "output_name": "plots/fig5.png"
                }
    histname = "{WZCRee, WZCRem, WZCRmm, dummy, TLWZ1SFOS, TLWZ2SFOS}"
    sigs = [ samples.getHistogram("/sig", histname).Clone("WWW") ]
    bgs  = [ samples.getHistogram("/bkg/top", histname).Clone("top"),
             samples.getHistogram("/bkg/ttV", histname).Clone("ttV"),
             samples.getHistogram("/bkg/VVV", histname).Clone("VVV"),
             samples.getHistogram("/bkg/VV", histname).Clone("VV"),
             samples.getHistogram("/bkg/W", histname).Clone("W"),
             samples.getHistogram("/bkg/Z", histname).Clone("Z") ]
    data = samples.getHistogram("/data", histname).Clone("Data")
    colors = [ 2005, 2001, 2012, 2003, 920, 2007 ]
    p.plot_hist(
            sigs = sigs,
            bgs  = bgs,
            data = data,
            colors = colors,
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
                "nbins": 9,
                "output_name": "plots/{}.png".format(output_name)
                }
    sigs = [ samples.getHistogram("/sig", histname).Clone("WWW") ]
    bgs  = [ samples.getHistogram("/typebkg/prompt", histname).Clone("Prompt"),
             samples.getHistogram("/typebkg/qflip", histname).Clone("Q-flips"),
             samples.getHistogram("/typebkg/lostlep", histname).Clone("Lost-lepton"),
             samples.getHistogram("/typebkg/fakes", histname).Clone("fakes"),
             samples.getHistogram("/typebkg/photon", histname).Clone("#gamma#rightarrowl"),
             samples.getHistogram("/typebkg/others", histname).Clone("Others")
           ]
    #bgs  = [ samples.getHistogram("/bkg/top", histname).Clone("top"),
    #         samples.getHistogram("/bkg/ttV", histname).Clone("ttV"),
    #         samples.getHistogram("/bkg/VVV", histname).Clone("VVV"),
    #         samples.getHistogram("/bkg/VV", histname).Clone("VV"),
    #         samples.getHistogram("/bkg/W", histname).Clone("W"),
    #         samples.getHistogram("/bkg/Z", histname).Clone("Z") ]
    colors = [ 2001, 2007, 2003, 2005, 920, 2012 ]
    data = samples.getHistogram("/data", histname).Clone("Data")
    #data = None
    #sigs[0].Scale(100)
    p.plot_hist(
            sigs = sigs,
            bgs  = bgs,
            data = data,
            colors = colors,
            options=alloptions)

#_____________________________________________________________________________________
def plot_2d_bdt_bkg_scan():
    f = ROOT.TFile("ofile.root")
    ply.plot_hist_2d(f.Get("bkg"), {"output_name": "bkg.png"})

#plotFig4()
#plotFig4a()
#plotFig5()
#plotFig4ByType()
#plotFig4ByTypeFakeEst()
#plotByProc("cut0_SSmm/lepRelIso0", "lepRelIso0")
#plotByProc("cut0_SSmm/lepRelIso1", "lepRelIso1")
plotByProc("WZCRmm/Mjj", "Mjj")
#plotByProc("WZCRee/Mjj", "WZCReeMjj")
