#!/bin/env python

import os
import ROOT
from QFramework import TQSampleFolder, TQXSecParser, TQCut, TQAnalysisSampleVisitor, TQSampleInitializer, TQCutflowAnalysisJob, TQCutflowPrinter, TQHistoMakerAnalysisJob
from rooutil import plottery_wrapper as p
from plottery import plottery as ply

from cuts import bkg_types_SS
from cuts import bkg_types_3L

ROOT.gROOT.SetBatch(True)

import sys

try:
    samples = TQSampleFolder.loadSampleFolder("{}:samples".format(sys.argv[1]))
except:
    samples = TQSampleFolder.loadSampleFolder("output.root:samples")

#_____________________________________________________________________________________
def plot(histname, output_name, doFR=False, doProc=False, blind=True, nbins=20, sigscale=-1):
    # Options
    sigs = [ samples.getHistogram("/sig", histname).Clone("WWW") ]
    if not doProc:
        bgs  = [ samples.getHistogram("/typebkg/prompt", histname).Clone("Prompt"),
                 samples.getHistogram("/typebkg/qflip", histname).Clone("Q-flips"),
                 samples.getHistogram("/typebkg/lostlep", histname).Clone("Lost-lepton"),
                 samples.getHistogram("/typebkg/fakes", histname).Clone("fakes") if not doFR else samples.getHistogram("/fake", histname).Clone("fakes"),
                 samples.getHistogram("/typebkg/photon", histname).Clone("#gamma#rightarrowl"),
                 samples.getHistogram("/typebkg/others", histname).Clone("Others")
               ]
    else:
        bgs  = [ samples.getHistogram("/bkg/top", histname).Clone("top"),
                 samples.getHistogram("/bkg/ttV", histname).Clone("ttV"),
                 samples.getHistogram("/bkg/VVV", histname).Clone("VVV"),
                 samples.getHistogram("/bkg/VV", histname).Clone("VV"),
                 samples.getHistogram("/bkg/W", histname).Clone("W"),
                 samples.getHistogram("/bkg/Z", histname).Clone("Z") ]
    colors = [ 2001, 2007, 2003, 2005, 920, 2012 ]
    if not blind:
        data = samples.getHistogram("/data", histname).Clone("Data")
    else:
        data = None
    total = 0
    for bg in bgs:
        total += bg.Integral()
    if total == 0:
        print histname, "does not have anything to plot"
        return
    #if sigscale < 0:
    #    totalbkg = p.get_total_hist(bgs).Integral()
    #    totalsig = sigs[0].Integral()
    #    sigs[0].Scale(totalbkg / totalsig / 2.0)
    alloptions= {
                "ratio_range":[0,2],
                "legend_smart":False,
                "output_name": "plots/{}.png".format(output_name),
                }
    p.plot_cut_scan(
            sigs = sigs,
            bgs  = bgs,
            syst = [0.10, 0.99, 0.15, 0.5, 0.99, 0],
            data = data,
            colors = colors,
            options=alloptions)
    alloptions= {
                "ratio_range":[0,2],
                "nbins": nbins,
                "output_name": "plots/{}.png".format(output_name),
                #"yaxis_log":True
                }
    p.plot_hist(
            sigs = sigs,
            bgs  = bgs,
            data = data,
            colors = colors,
            options=alloptions)

############################################################################################
############################################################################################
############################################################################################
############################################################################################
############################################################################################

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
def plotByProc(histname, output_name, doFR=False):
    # Options
    alloptions= {
                "ratio_range":[0,2],
                "nbins": 20,
                "output_name": "plots/{}.png".format(output_name)
                }
    sigs = [ samples.getHistogram("/sig", histname).Clone("WWW") ]
    bgs  = [ samples.getHistogram("/typebkg/prompt", histname).Clone("Prompt"),
             samples.getHistogram("/typebkg/qflip", histname).Clone("Q-flips"),
             samples.getHistogram("/typebkg/lostlep", histname).Clone("Lost-lepton"),
             samples.getHistogram("/typebkg/fakes", histname).Clone("fakes") if not doFR else samples.getHistogram("/fake", histname).Clone("fakes"),
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
    total = 0
    for bg in bgs:
        total += bg.Integral()
    if total == 0:
        print histname, "does not have anything to plot"
        return
    #data = None
    #sigs[0].Scale(10)
    p.plot_hist(
            sigs = sigs,
            bgs  = bgs,
            data = data,
            colors = colors,
            options=alloptions)
    #alloptions["yaxis_log"] = True
    #alloptions["output_name"] = alloptions["output_name"].replace(".png", "_logy.png")
    #p.plot_hist(
    #        sigs = sigs,
    #        bgs  = bgs,
    #        data = data,
    #        colors = colors,
    #        options=alloptions)

#_____________________________________________________________________________________
def plotSignifByProc(histname, output_name):
    # Options
    alloptions= {
                "ratio_range":[0,2],
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
    #data = samples.getHistogram("/data", histname).Clone("Data")
    data = None
    p.plot_cut_scan(
            sigs = sigs,
            bgs  = bgs,
            data = data,
            colors = colors,
            options=alloptions)
    #alloptions["yaxis_log"] = True
    #alloptions["output_name"] = alloptions["output_name"].replace(".png", "_logy.png")
    #p.plot_hist(
    #        sigs = sigs,
    #        bgs  = bgs,
    #        data = data,
    #        colors = colors,
    #        options=alloptions)

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
