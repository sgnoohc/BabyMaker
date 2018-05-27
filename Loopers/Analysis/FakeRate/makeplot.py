#!/bin/env python

import os
import sys
import ROOT
from QFramework import TQSampleFolder, TQXSecParser, TQCut, TQAnalysisSampleVisitor, TQSampleInitializer, TQCutflowAnalysisJob, TQCutflowPrinter, TQHistoMakerAnalysisJob
from rooutil import plottery_wrapper as p
from plottery import plottery as ply

ROOT.gROOT.SetBatch(True)
samples = TQSampleFolder.loadSampleFolder("output.root:samples")
#samples.printContents("trd")

output_plot_dir = "plots"

doW = False
docombinedqcdel = True

testsample = "/top"
testsamplename = "t#bar{t}"
testsamplelegendname = "t#bar{t}"
if doW:
    testsample = "/W/HT"
    #testsample = "/W"
    testsamplename = "W"
    testsamplelegendname = "W"
if docombinedqcdel:
    testsample = "/top+W/HT"
    #testsample = "/W"
    testsamplename = "W and t#bar{t}"
    testsamplelegendname = "W and t#bar{t}"

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
    sigs = []
    bgs  = [ samples.getHistogram("/qcd/mu", histname).Clone("QCD"),
             ]
    data = None
    colors = [ 2005, 920 ]
    plotfunc(
            sigs = sigs,
            bgs  = bgs,
            data = data,
            colors = colors,
            syst = systs,
            options=alloptions)

#_____________________________________________________________________________________
def plot_stack(histname, output_name, systs=None, options={}, plotfunc=p.plot_hist):
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
    sigs = []
    bgs  = [
           samples.getHistogram("/qcd/mu", histname).Clone("QCD"),
           samples.getHistogram("/top", histname).Clone("Top"),
           samples.getHistogram("/W", histname).Clone("W"),
           samples.getHistogram("/Z", histname).Clone("DY"),
           ]
    dataname = "/data"
    if histname.find("El") != -1: dataname = "/data/ee"
    if histname.find("Mu") != -1: dataname = "/data/mm"
    data = samples.getHistogram(dataname, histname).Clone("Data")
    if histname.find("HLT") != -1:
        totalbkg = p.get_total_hist(bgs)
        ratio = samples.getHistogram(dataname, histname).Clone("Data")
        ratio.Rebin(ratio.GetNbinsX())
        totalbkg.Rebin(totalbkg.GetNbinsX())
        totalbkg.Divide(ratio)
        print histname
        totalbkg.Print("all")
    colors = [ 920, 2005, 2001, 2003 ]
    plotfunc(
            sigs = sigs,
            bgs  = bgs,
            data = data,
            colors = colors,
            syst = systs,
            options=alloptions)

#_____________________________________________________________________________________
def fakerate(histname, output_name, systs=None, options={}, plotfunc=p.plot_hist):
    if str(histname).find("Loose") == -1: return
    isqcd = str(histname).find("One") != -1
    ismu = str(histname).find("Mu") != -1
    ispredict = str(histname).find("Predict") != -1

    sample = testsample
    if isqcd and ismu:
        sample = "/qcd/mu"
    elif isqcd and not ismu:
        if doW:
            sample = "/qcd/el/EM"
        else:
            sample = "/qcd/el/bcToE"
        #sample = "/qcd/el"
        if docombinedqcdel:
            sample = "/qcd/el"
    samplename = (("t#bar{t} estimation" if not doW else "W estimation") if not docombinedqcdel else "W + t#bar{t} estimation") if ispredict else ("QCD Loose" if isqcd else ("ttbar Loose" if not doW else "W Loose"))
    color = 920 if isqcd else (2005 if not doW else 2001)
    # Options
    alloptions= {
                "ratio_range":[0.0, 2.0] if ispredict else ([0.0,0.45] if not doW else [0.0, 1.0]),
                #"nbins": 30,
                "autobin": True,
                "legend_scalex": 0.8,
                "legend_scaley": 0.8,
                "legend_datalabel": samplename.replace("estimation", "prediction") if ispredict else samplename.replace("Loose", "Tight"),
                "output_name": "{}/fr_{}.pdf".format(output_plot_dir, output_name),
                "hist_disable_xerrors": True if str(histname).find("varbin") != -1 else False,
                }
    histnum = samples.getHistogram(sample, str(histname).replace("Loose", "Tight")).Clone(samplename)
    histden = samples.getHistogram(sample, histname).Clone(samplename)
    alloptions.update(options)
    sigs = []
    bgs  = [ histden ]
    data = histnum
    colors = [ color ]
    if docombinedqcdel:
        bgs = [
                samples.getHistogram("/top", histname).Clone("t#bar{t} estimation"),
                samples.getHistogram("/W/HT", histname).Clone("W estimation")
              ]
        colors = [ 2005, 2001 ]
    try:
        plotfunc(
                sigs = sigs,
                bgs  = bgs,
                data = data,
                colors = colors,
                syst = systs,
                options=alloptions)
    except:
        print "ERROR: failed plotting {} {}".format(histname, sample)

#_____________________________________________________________________________________
def fakerate2d(histname, output_name, systs=None, options={}, plotfunc=p.plot_hist):
    if str(histname).find("Loose") == -1: return
    isqcd = str(histname).find("One") != -1
    ismu = str(histname).find("Mu") != -1
    ispredict = str(histname).find("Predict") != -1

    sample = testsample
    if isqcd and ismu:
        sample = "/qcd/mu"
    elif isqcd and not ismu:
        if doW:
            sample = "/qcd/el/EM"
        else:
            sample = "/qcd/el/bcToE"
        #sample = "/qcd/el"
        if docombinedqcdel:
            sample = "/qcd/el"
    samplename = (("t#bar{t} estimation" if not doW else "W estimation") if not docombinedqcdel else "W + t#bar{t} estimation") if ispredict else ("QCD Loose" if isqcd else ("ttbar Loose" if not doW else "W Loose"))
    color = 920 if isqcd else (2005 if not doW else 2001)
    # Options
    alloptions= {
                "ratio_range":[0.0, 2.0] if ispredict else [0.0,0.3],
                #"nbins": 30,
                "autobin": True,
                "legend_scalex": 0.8,
                "legend_scaley": 0.8,
                "legend_datalabel": samplename.replace("estimation", "prediction") if ispredict else samplename.replace("Loose", "Tight"),
                "output_name": "{}/fr_{}.pdf".format(output_plot_dir, output_name),
                "hist_disable_xerrors": True if str(histname).find("varbin") != -1 else False,
                }
    #samples.getHistogram(sample, str(histname).replace("Loose", "Tight")).Clone(samplename).Print("all")
    histnum = p.flatten_th2(samples.getHistogram(sample, str(histname).replace("Loose", "Tight")).Clone(samplename))
    histden = p.flatten_th2(samples.getHistogram(sample, histname).Clone(samplename))
    alloptions.update(options)
    sigs = []
    bgs  = [ histden ]
    data = histnum
    colors = [ color ]
    if docombinedqcdel:
        bgs = [
                p.flatten_th2(samples.getHistogram("/top", histname).Clone("t#bar{t} estimation")),
                p.flatten_th2(samples.getHistogram("/W/HT", histname).Clone("W estimation"))
              ]
        colors = [ 2005, 2001 ]
    plotfunc(
            sigs = sigs,
            bgs  = bgs,
            data = data,
            colors = colors,
            syst = systs,
            options=alloptions)
    #histnum.Divide(histden)

#_____________________________________________________________________________________
def fakeratecomp(histname, output_name, systs=None, options={}, plotfunc=p.plot_hist):
    if str(histname).find("Loose") == -1: return
    if str(histname).find("One") == -1: return
    if str(histname).find("varbin") == -1: return
    ismu = str(histname).find("Mu") != -1

    ispredict = str(histname).find("Predict") != -1

    qcdsample = "/qcd/mu" if ismu else (("/qcd/el/bcToE" if not doW else "/qcd/el/EM") if not docombinedqcdel else "/qcd/el")
    ttbarsample = testsample
    qcdsamplename = "QCD" if ismu else "QCD"
    ttbarsamplename = testsamplename

    qcdhistname = histname
    ttbarhistname = histname.replace("One", "Two")
    ttbarhistname = ttbarhistname.replace("lep_", "mu_") if ismu else ttbarhistname.replace("lep_", "el_")

    #print qcdhistname, ttbarhistname

    qcdhistnum = p.move_overflow(samples.getHistogram(qcdsample, str(qcdhistname).replace("Loose", "Tight")).Clone(qcdsamplename))
    qcdhistden = p.move_overflow(samples.getHistogram(qcdsample, qcdhistname).Clone(qcdsamplename))
    ttbarhistnum = p.move_overflow(samples.getHistogram(ttbarsample, str(ttbarhistname).replace("Loose", "Tight")).Clone(ttbarsamplename))
    ttbarhistden = p.move_overflow(samples.getHistogram(ttbarsample, ttbarhistname).Clone(ttbarsamplename))

    qcdhistnum.Divide(qcdhistden)
    ttbarhistnum.Divide(ttbarhistden)

    # Options
    alloptions= {
                "ratio_range":[0.0, 2.0] if ispredict else [0.5 if ismu else 0.0, 1.5 if ismu else 2.0],
                "yaxis_range":[0.0,0.25 if ismu else (0.4 if qcdsample.find("bcToE") != -1 else 1.0)],
                #"nbins": 30,
                "yaxis_log": False,
                "draw_points": True,
                "autobin": True,
                "legend_scalex": 0.8,
                "legend_scaley": 0.8,
                "legend_datalabel": testsamplelegendname,
                "output_name": "{}/fr_closure_{}.pdf".format(output_plot_dir, output_name)
                }
    #samples.getHistogram(sample, str(histname).replace("Loose", "Tight")).Clone(samplename).Print("all")
    #histnum = p.flatten_th2(samples.getHistogram(sample, str(histname).replace("Loose", "Tight")).Clone(samplename))
    #histden = p.flatten_th2(samples.getHistogram(sample, histname).Clone(samplename))
    alloptions.update(options)
    sigs = []
    bgs  = [ qcdhistnum ]
    data = ttbarhistnum
    colors = [ 2 ]
    plotfunc(
            sigs = sigs,
            bgs  = bgs,
            data = data,
            colors = colors,
            syst = systs,
            options=alloptions)

#_____________________________________________________________________________________
def fakerate2dcomp(histname, output_name, systs=None, options={}, plotfunc=p.plot_hist):
    if str(histname).find("Loose") == -1: return
    if str(histname).find("One") == -1: return
    if str(histname).find("corr") == -1: return
    ismu = str(histname).find("Mu") != -1

    qcdsample = "/qcd/mu" if ismu else (("/qcd/el/bcToE" if not doW else "/qcd/el/EM") if not docombinedqcdel else "/qcd/el")
    ttbarsample = testsample
    qcdsamplename = "QCD" if ismu else "QCD"
    ttbarsamplename = testsamplename

    qcdhistname = histname
    ttbarhistname = histname.replace("One", "Two")
    ttbarhistname = ttbarhistname.replace("lep_", "mu_") if ismu else ttbarhistname.replace("lep_", "el_")

    #print qcdhistname, ttbarhistname

    qcdhistnum = p.flatten_th2(samples.getHistogram(qcdsample, str(qcdhistname).replace("Loose", "Tight")).Clone(qcdsamplename))
    qcdhistden = p.flatten_th2(samples.getHistogram(qcdsample, qcdhistname).Clone(qcdsamplename))
    ttbarhistnum = p.flatten_th2(samples.getHistogram(ttbarsample, str(ttbarhistname).replace("Loose", "Tight")).Clone(ttbarsamplename))
    ttbarhistden = p.flatten_th2(samples.getHistogram(ttbarsample, ttbarhistname).Clone(ttbarsamplename))

    qcdhistnum.Divide(qcdhistden)
    ttbarhistnum.Divide(ttbarhistden)

    # Options
    alloptions= {
                "ratio_range":[0.0,2.0 if ismu else 3.0],
                "yaxis_range":[0.0,0.35 if ismu else (0.6 if not doW else 1.0)],
                #"nbins": 30,
                "draw_points": True,
                "autobin": True,
                "legend_scalex": 0.8,
                "legend_scaley": 0.8,
                "legend_datalabel": testsamplelegendname,
                "output_name": "{}/fr_closure_{}.pdf".format(output_plot_dir, output_name)
                }
    #samples.getHistogram(sample, str(histname).replace("Loose", "Tight")).Clone(samplename).Print("all")
    #histnum = p.flatten_th2(samples.getHistogram(sample, str(histname).replace("Loose", "Tight")).Clone(samplename))
    #histden = p.flatten_th2(samples.getHistogram(sample, histname).Clone(samplename))
    alloptions.update(options)
    sigs = []
    bgs  = [ qcdhistnum ]
    data = ttbarhistnum
    colors = [ 2 ]
    plotfunc(
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
            if hname.find("EWKCR") != -1 and hname.find("_vs_") == -1:
                hfilename = hname.replace("/", "_")
#                proc = multiprocessing.Process(target=plot_stack, args=[hname, hfilename], kwargs={"systs":None, "options":{"autobin":False, "nbins":15, "lumi_value":35.9, "yaxis_log":False}, "plotfunc": p.plot_hist})
#                jobs.append(proc)
#                proc.start()
            elif hname.find("HLT") != -1 and hname.find("_vs_") == -1:
                hfilename = hname.replace("/", "_")
#                proc = multiprocessing.Process(target=plot_stack, args=[hname, hfilename], kwargs={"systs":None, "options":{"autobin":False, "nbins":60, "lumi_value":35.9, "yaxis_log":True}, "plotfunc": p.plot_hist})
#                jobs.append(proc)
#                proc.start()
            elif hname.find("_vs_") != -1:
                hfilename = hname.replace("/", "_")
                #proc = multiprocessing.Process(target=fakerate2d, args=[hname, hfilename], kwargs={"systs":None, "options":{}, "plotfunc": ply.plot_hist_2d})
                proc = multiprocessing.Process(target=fakerate2d, args=[hname, hfilename], kwargs={"systs":None, "options":{"autobin":False, "nbins":15, "lumi_value":35.9, "yaxis_log":True}, "plotfunc": p.plot_hist})
                jobs.append(proc)
                proc.start()
                proc = multiprocessing.Process(target=fakerate2dcomp, args=[hname, hfilename], kwargs={"systs":None, "options":{"autobin":False, "nbins":15, "lumi_value":35.9, "yaxis_log":False}, "plotfunc": p.plot_hist})
                jobs.append(proc)
                proc.start()
            else:
                hfilename = hname.replace("/", "_")
                proc = multiprocessing.Process(target=fakerate, args=[hname, hfilename], kwargs={"systs":None, "options":{"autobin":False, "nbins":10, "lumi_value":35.9, "yaxis_log":False}, "plotfunc": p.plot_hist})
                jobs.append(proc)
                proc.start()
                proc = multiprocessing.Process(target=fakeratecomp, args=[hname, hfilename], kwargs={"systs":None, "options":{"autobin":False, "nbins":10, "lumi_value":35.9, "yaxis_log":False}, "plotfunc": p.plot_hist})
                jobs.append(proc)
                proc.start()

        for job in jobs:
            job.join()

    else:
        hname = str(sys.argv[1])
        hfilename = hname.replace("/", "_")
        ratio = plot(hname, hfilename, options={"legend_scalex":1.5, "autobin":False, "blind":False, "nbins":15, "signal_scale":7, "yaxis_log":False, "yaxis_range":[float(sys.argv[2]),float(sys.argv[3])]}, plotfunc=p.plot_hist).Clone("nvtx")
        #ratio.Print("all")

        f = ROOT.TFile("nvtx_rewgt_mm.root","recreate")
        ratio.Write()
