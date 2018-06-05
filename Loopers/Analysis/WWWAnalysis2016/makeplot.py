#!/bin/env python

import os
import sys
import ROOT
from QFramework import TQSampleFolder, TQXSecParser, TQCut, TQAnalysisSampleVisitor, TQSampleInitializer, TQCutflowAnalysisJob, TQCutflowPrinter, TQHistoMakerAnalysisJob
from rooutil import plottery_wrapper as p
from plottery import plottery as ply

ROOT.gROOT.SetBatch(True)
samples = TQSampleFolder.loadSampleFolder("output.root:samples")

output_plot_dir = "plots"

#_____________________________________________________________________________________
def plot(histname, output_name, systs=None, options={}, plotfunc=p.plot_hist):
    # Options
    alloptions= {
                "ratio_range":[0.0,2.0],
                #"nbins": 30,
                "autobin": True,
                "legend_scalex": 1.4,
                "legend_scaley": 1.1,
                "output_name": "{}/{}.pdf".format(output_plot_dir, output_name)
                }
    alloptions.update(options)
    sigs = [ samples.getHistogram("/sig", histname).Clone("WWW") ]
    bgs  = [ samples.getHistogram("/bkg/top", histname).Clone("top"),
             samples.getHistogram("/bkg/ttV", histname).Clone("ttV"),
             samples.getHistogram("/bkg/VVV", histname).Clone("VVV"),
             samples.getHistogram("/bkg/VV", histname).Clone("VV"),
             samples.getHistogram("/bkg/W", histname).Clone("W"),
             samples.getHistogram("/bkg/Z", histname).Clone("Z") ]
    data =   samples.getHistogram("/data", histname).Clone("Data")
    colors = [ 2005, 2001, 2012, 2003, 920, 2007 ]
    plotfunc(
            sigs = sigs,
            bgs  = bgs,
            data = data,
            colors = colors,
            syst = systs,
            options=alloptions)

#_____________________________________________________________________________________
def plot_typebkg(histname, output_name, systs=None, options={}, plotfunc=p.plot_hist):
    # Options
    alloptions= {
                "ratio_range":[0.0,2.0],
                #"nbins": 30,
                "autobin": True,
                "legend_scalex": 1.4,
                "legend_scaley": 1.1,
                "output_name": "{}/{}_typebkg.pdf".format(output_plot_dir, output_name)
                }
    alloptions.update(options)
    sigs = [ samples.getHistogram("/sig", histname).Clone("WWW") ]
    bgs  = [ samples.getHistogram("/typebkg/fakes", histname).Clone("Fakes"),
             samples.getHistogram("/typebkg/prompt", histname).Clone("Prompt"),
             samples.getHistogram("/typebkg/lostlep", histname).Clone("Lost-lep"),
             samples.getHistogram("/typebkg/photon", histname).Clone("#gamma#rightarrowl"),
             samples.getHistogram("/typebkg/qflip", histname).Clone("Q-flip") ]
    data =   samples.getHistogram("/data", histname).Clone("Data")
    colors = [ 2005, 2001, 2003, 920, 2007 ]
    plotfunc(
            sigs = sigs,
            bgs  = bgs,
            data = data,
            colors = colors,
            syst = systs,
            options=alloptions)

#_____________________________________________________________________________________
def plot_frmethod(histname, output_name, systs=None, options={}, plotfunc=p.plot_hist):
    # Options
    alloptions= {
                "ratio_range":[0.4,1.6],
                #"nbins": 30,
                "autobin": True,
                "legend_scalex": 1.4,
                "legend_scaley": 1.1,
                "output_name": "{}/{}_frmethod.pdf".format(output_plot_dir, output_name)
                }
    alloptions.update(options)
    sigs = [ samples.getHistogram("/sig", histname).Clone("WWW") ]
    bgs  = [ samples.getHistogram("/fake", histname).Clone("Fakes"),
             samples.getHistogram("/typebkg/prompt", histname).Clone("Prompt"),
             samples.getHistogram("/typebkg/lostlep", histname).Clone("Lost-lep"),
             samples.getHistogram("/typebkg/photon", histname).Clone("#gamma#rightarrowl"),
             samples.getHistogram("/typebkg/qflip", histname).Clone("Q-flip") ]
    data =   samples.getHistogram("/data", histname).Clone("Data")
    colors = [ 2005, 2001, 2003, 920, 2007 ]
    plotfunc(
            sigs = sigs,
            bgs  = bgs,
            data = data,
            colors = colors,
            syst = systs,
            options=alloptions)

#_____________________________________________________________________________________
def isblind(hname):
    if hname.find("WZ") != -1: return False
    if hname.find("AR") != -1: return False
    if hname.find("BT") != -1: return False
    return True

#_____________________________________________________________________________________
def dofrmethod(hname):
    if hname.find("SR") != -1: return True
    if hname.find("BT") != -1: return True
    return False

#_____________________________________________________________________________________
def plotall(histnames):
    import multiprocessing
    jobs = []
    for histname in histnames:
        hname = str(histname)
        if hname.find("_vs_") != -1:
            continue
        hfilename = hname.replace("/", "_")
        hfilename = hfilename.replace(",", "_")
        hfilename = hfilename.replace("+", "_")
        hfilename = hfilename.replace("{", "_")
        hfilename = hfilename.replace("}", "_")

        # Plotting by bkg type
        proc = multiprocessing.Process(target=plot_typebkg, args=[hname, hfilename], kwargs={"systs":None, "options":{"blind": isblind(hname), "autobin":False, "nbins":15, "lumi_value":35.9, "yaxis_log":False}, "plotfunc": p.plot_hist})
        jobs.append(proc)
        proc.start()

        # Plotting by physics process
        #proc = multiprocessing.Process(target=plot, args=[hname, hfilename], kwargs={"systs":None, "options":{"blind": hname.find("WZ") == -1, "autobin":False, "nbins":15, "lumi_value":35.9, "yaxis_log":False}, "plotfunc": p.plot_hist})
        #jobs.append(proc)
        #proc.start()

        # Plotting by bkg type and fakes are estimated from data
        if dofrmethod(hname):
            proc = multiprocessing.Process(target=plot_frmethod, args=[hname, hfilename], kwargs={"systs":None, "options":{"blind": isblind(hname), "autobin":False, "nbins":15, "lumi_value":35.9, "yaxis_log":False}, "plotfunc": p.plot_hist})
            jobs.append(proc)
            proc.start()

        # For scanning cuts to optimize
        #proc = multiprocessing.Process(target=plot, args=[hname, hfilename], kwargs={"systs":None, "options":{"blind": hname.find("WZ") == -1, "autobin":False, "nbins":15, "lumi_value":35.9, "yaxis_log":False}, "plotfunc": p.plot_cut_scan})
        #jobs.append(proc)
        #proc.start()

    for job in jobs:
        job.join()

if __name__ == "__main__":

    histnames = samples.getListOfHistogramNames()
    histnames = []
    histnames = []
    histnames.extend(["{SRSSeeNb0,SRSSemNb0,SRSSmmNb0,SR0SFOSNb0,SR1SFOSNb0,SR2SFOSNb0}"])
    histnames.extend(["{ARSSeeNb0,ARSSemNb0,ARSSmmNb0,AR0SFOSNb0,AR1SFOSNb0,AR2SFOSNb0}"])
    histnames.extend(["{SRSSeeZeeVt,SRSSemMTmax,SRSSmmMllSS,SR0SFOSZVt,SR1SFOSMT3rd,SR2SFOSZVt}"])
    histnames.extend(["{SRSSeeZeeVt,SRSSemMTmax,SRSSmmMllSS,SR0SFOSMTmax,SR1SFOSMT3rd,SR2SFOSZVt}"])
    histnames.extend(["{ARSSeeZeeVt,ARSSemMTmax,ARSSmmMllSS,AR0SFOSZVt,AR1SFOSMT3rd,AR2SFOSZVt}"])
    histnames.extend(["{ARSSeeZeeVt,ARSSemMTmax,ARSSmmMllSS,AR0SFOSMTmax,AR1SFOSMT3rd,AR2SFOSZVt}"])
    histnames.extend(["{WZCRSSeeZeeVt,WZCRSSemMTmax,WZCRSSmmMllSS,WZCR1SFOSMT3rd,WZCR2SFOSZVt}"])
    histnames.extend(["{BTCRSSeeZeeVt,BTCRSSemMTmax,BTCRSSmmMllSS,BTCR0SFOSZVt,BTCR1SFOSMT3rd,BTCR2SFOSZVt}"])
    histnames.extend(["{BTCRSSeeZeeVt,BTCRSSemMTmax,BTCRSSmmMllSS,BTCR0SFOSZVt,BTCR1SFOSMT3rd,BTCR2SFOSZVt}"])
    histnames.extend(["{BTCRSSeeNb0,BTCRSSemNb0,BTCRSSmmNb0,BTCR0SFOSNb0,BTCR1SFOSNb0,BTCR2SFOSNb0}"])
    histnames.extend(["BTCRSSeeZeeVt/MET"])
    histnames.extend(["BTCRSSemMTmax/MET"])
    histnames.extend(["BTCRSSmmMllSS/MET"])
    histnames.extend(["BTCRSSeeZeeVt/MET+BTCRSSemMTmax/MET+BTCRSSmmMllSS/MET"])
    histnames.extend(["BTCRSSeeZeeVt/Mjj+BTCRSSemMTmax/Mjj+BTCRSSmmMllSS/Mjj"])
    histnames.extend(["BTCRSSeeZeeVt/MllSS+BTCRSSemMTmax/MllSS+BTCRSSmmMllSS/MllSS"])
    histnames.extend(["BTCRSSeeNb0/MET"])
    histnames.extend(["BTCRSSemNb0/MET"])
    histnames.extend(["BTCRSSmmNb0/MET"])
    plotall(histnames)
