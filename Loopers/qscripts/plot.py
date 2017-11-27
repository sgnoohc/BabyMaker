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
    sigs = [ samples.getHistogram("/samples/sig/mm/www", histname).Clone("WWW") ]
    bgs  = [ samples.getHistogram("/samples/bkg/mm/top", histname).Clone("top"),
             samples.getHistogram("/samples/bkg/mm/ttV", histname).Clone("ttV"),
             samples.getHistogram("/samples/bkg/mm/VVV", histname).Clone("VVV"),
             samples.getHistogram("/samples/bkg/mm/VV", histname).Clone("VV"),
             samples.getHistogram("/samples/bkg/mm/W", histname).Clone("W"),
             samples.getHistogram("/samples/bkg/mm/Z", histname).Clone("Z") ]
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
    sigs = [ samples.getHistogram("/samples/sig", histname).Clone("WWW") ]
    bgs  = [ samples.getHistogram("/samples/typebkg/prompt", histname).Clone("Prompt"),
             samples.getHistogram("/samples/typebkg/qflip", histname).Clone("Q-flips"),
             samples.getHistogram("/samples/typebkg/lostlep", histname).Clone("Lost-lepton"),
             samples.getHistogram("/samples/typebkg/fakes", histname).Clone("fakes"),
             samples.getHistogram("/samples/typebkg/photon", histname).Clone("#gamma#rightarrowl"),
             samples.getHistogram("/samples/typebkg/others", histname).Clone("Others")
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
    sigs = [ samples.getHistogram("/samples/sig", histname).Clone("WWW") ]
    bgs  = [ samples.getHistogram("/samples/typebkg/prompt", histname).Clone("Prompt"),
             samples.getHistogram("/samples/typebkg/qflip", histname).Clone("Q-flips"),
             samples.getHistogram("/samples/typebkg/lostlep", histname).Clone("Lost-lepton"),
             samples.getHistogram("/samples/fake/", histname).Clone("fakes"),
             samples.getHistogram("/samples/typebkg/photon", histname).Clone("#gamma#rightarrowl"),
             samples.getHistogram("/samples/typebkg/others", histname).Clone("Others")
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
    sigs = [ samples.getHistogram("/samples/sig/mm/www", histname).Clone("WWW") ]
    bgs  = [ samples.getHistogram("/samples/bkg/mm/top", histname).Clone("top"),
             samples.getHistogram("/samples/bkg/mm/ttV", histname).Clone("ttV"),
             samples.getHistogram("/samples/bkg/mm/VVV", histname).Clone("VVV"),
             samples.getHistogram("/samples/bkg/mm/VV", histname).Clone("VV"),
             samples.getHistogram("/samples/bkg/mm/W", histname).Clone("W"),
             samples.getHistogram("/samples/bkg/mm/Z", histname).Clone("Z") ]
    data = samples.getHistogram("/samples/data/mm", histname).Clone("Data")
    p.plot_hist(
            sigs = sigs,
            bgs  = bgs,
            data = data,
            options=alloptions)

#_____________________________________________________________________________________
def plotByType(fullname, output_name, dataset, bkg_types):
    # Options
    alloptions= {
                "ratio_range":[0,2],
                "nbins": 15,
                "output_name": "plots/{}.png".format(output_name)
                }
    
    cutname = fullname.split("/")[0]
    histname = fullname.split("/")[1]
    cutname += "_{}"
    histname = cutname + "/" + histname
    sigs = [ samples.getHistogram("/samples", histname.format("WWW")).Clone("WWW") ]
    bgs  = [ samples.getHistogram("/samples", histname.format(bkgtype)).Clone(bkgtype) for bkgtype in bkg_types ]
    data = samples.getHistogram("/samples", histname.format(dataset)).Clone("Data")
    colors = [ 2001, 2007, 2003, 2005, 920, 2012 ]
    
    p.plot_hist(
            sigs = sigs,
            bgs  = bgs,
            data = data,
            colors = colors,
            options=alloptions)

#_____________________________________________________________________________________
def plotSSByType(histname, output_name): plotByType(histname, output_name, "Data", bkg_types_SS)

#plotFig4()
plotFig4ByType()
plotFig4ByTypeFakeEst()
#plotByProc("SSmm_cut5/Mll", "Mll")
#plotByProc("SSee_cut5/Mll", "SSee_cut5_Mll")
#plotByProc("SSem_cut5/Mll", "SSem_cut5_Mll")
#plotByProc("SSmm_cut5/Mll", "SSmm_cut5_Mll")
#plotSSByType("cut8_SSmm/Mll", "SSmm_type_cut10_Mll")
#plotSSByType("cut8_SSem/Mll", "SSem_type_cut12_Mll")
#plotSSByType("cut8_SSee/Mll", "SSee_type_cut12_Mll")
#plotSSemByType("SSem_cut5/Mll", "SSem_type_cut5_Mll")
#plotSSeeByType("SSee_cut5/Mll", "SSee_type_cut5_Mll")
