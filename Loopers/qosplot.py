#!/bin/env python

import os
import sys
import ROOT
from QFramework import TQSampleFolder, TQXSecParser, TQCut, TQAnalysisSampleVisitor, TQSampleInitializer, TQCutflowAnalysisJob, TQCutflowPrinter, TQHistoMakerAnalysisJob
from rooutil import plottery_wrapper as p
from plottery import plottery as ply

ROOT.gROOT.SetBatch(True)
#samples = TQSampleFolder.loadSampleFolder("output_w_purewgt.root:samples")
samples = TQSampleFolder.loadSampleFolder("output.root:samples")

output_plot_dir = "plots_powheg"

#_____________________________________________________________________________________
def plot(histname, output_name, systs=None, options={}, plotfunc=p.plot_hist):
    # Options
    alloptions= {
                "ratio_range":[0.4,1.6],
                #"nbins": 30,
                "autobin": True,
                "legend_scalex": 1.4,
                "legend_scaley": 1.1,
                "output_name": "{}/{}.pdf".format(output_plot_dir, output_name)
                }
    alloptions.update(options)
    sigs = [ samples.getHistogram("/os/sig", histname).Clone("WWW") ]
    bgs  = [ samples.getHistogram("/os/bkg/top", histname).Clone("top"),
             samples.getHistogram("/os/bkg/ttV", histname).Clone("ttV"),
             samples.getHistogram("/os/bkg/VVV", histname).Clone("VVV"),
             samples.getHistogram("/os/bkg/VV", histname).Clone("VV"),
             samples.getHistogram("/os/bkg/W", histname).Clone("W"),
             samples.getHistogram("/os/bkg/Z", histname).Clone("Z") ]
    data =   samples.getHistogram("/os/data", histname).Clone("Data")
    colors = [ 2005, 2001, 2012, 2003, 920, 2007 ]
    plotfunc(
            sigs = sigs,
            bgs  = bgs,
            data = data,
            colors = colors,
            syst = systs,
            options=alloptions)

    # Do it twice for png and pdf (TODO should be fixed in plottery)
    alloptions= {
                "ratio_range":[0.4,1.6],
                #"nbins": 30,
                "autobin": True,
                "legend_scalex": 1.4,
                "legend_scaley": 1.1,
                "output_name": "{}/{}.png".format(output_plot_dir, output_name)
                }
    alloptions.update(options)
    sigs = [ samples.getHistogram("/os/sig", histname).Clone("WWW") ]
    bgs  = [ samples.getHistogram("/os/bkg/top", histname).Clone("top"),
             samples.getHistogram("/os/bkg/ttV", histname).Clone("ttV"),
             samples.getHistogram("/os/bkg/VVV", histname).Clone("VVV"),
             samples.getHistogram("/os/bkg/VV", histname).Clone("VV"),
             samples.getHistogram("/os/bkg/W", histname).Clone("W"),
             samples.getHistogram("/os/bkg/Z", histname).Clone("Z") ]
    data =   samples.getHistogram("/os/data", histname).Clone("Data")
    colors = [ 2005, 2001, 2012, 2003, 920, 2007 ]
    return plotfunc(
            sigs = sigs,
            bgs  = bgs,
            data = data,
            colors = colors,
            syst = systs,
            options=alloptions)

if __name__ == "__main__":

    if len(sys.argv) < 2:

        import multiprocessing

        jobs = []
        for histname in samples.getListOfHistogramNames():
            hname = str(histname)
            if hname.find("_vs_") != -1:
                continue
            hfilename = hname.replace("/", "_")
            proc = multiprocessing.Process(target=plot, args=[hname, hfilename], kwargs={"systs":None, "options":{"autobin":False, "nbins":60, "lumi_value":35.9, "yaxis_log":True, "yaxis_range":[1e-2, 1e13]}, "plotfunc": p.plot_hist})
            jobs.append(proc)
            proc.start()

        for job in jobs:
            job.join()

    else:
        hname = str(sys.argv[1])
        hfilename = hname.replace("/", "_")
        ratio = plot(hname, hfilename, options={"legend_scalex":1.5, "autobin":False, "blind":False, "nbins":1, "signal_scale":7, "yaxis_log":False, "yaxis_range":[float(sys.argv[2]),float(sys.argv[3])]}, plotfunc=p.plot_hist).Clone("nvtx")
        ratio.Print("all")

        f = ROOT.TFile("nvtx_rewgt_mm.root","recreate")
        ratio.Write()
