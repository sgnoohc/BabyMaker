#!/bin/env python

import os
import sys
import ROOT
from QFramework import TQSampleFolder, TQXSecParser, TQCut, TQAnalysisSampleVisitor, TQSampleInitializer, TQCutflowAnalysisJob, TQCutflowPrinter, TQHistoMakerAnalysisJob
from rooutil import plottery_wrapper as p
from plottery import plottery as ply

try:
    tqsamplefolderpath = sys.argv[1]
except:
    tqsamplefolderpath = "output.root"

ROOT.gROOT.SetBatch(True)
samples = TQSampleFolder.loadSampleFolder(tqsamplefolderpath+":samples")
samples_up = TQSampleFolder.loadSampleFolder("output_up.root:samples")
samples_dn = TQSampleFolder.loadSampleFolder("output_dn.root:samples")

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

def ewksf(cut, channel):
    data = samples.getHistogram("/data/{}{}".format(channel, channel) , cut+"/MTOneLepFixed").Clone("Data")
    bgs = []
    bgs.append(samples.getHistogram("/top" , cut+"/MTOneLepFixed").Clone("Top"))
    bgs.append(samples.getHistogram("/Zonelep" , cut+"/MTOneLepFixed").Clone("DY"))
    bgs.append(samples.getHistogram("/Wonelep" , cut+"/MTOneLepFixed").Clone("W"))
    totalbkg = p.get_total_hist(bgs)
    data.Rebin(4)
    totalbkg.Rebin(4)
    data.Divide(totalbkg)
    return data.GetBinContent(3)

elsf = 1.21193706989
elsf = ewksf("OneElTightEWKCR", "e")
musf = 1.11639511585
musf = ewksf("OneMuTightEWKCR", "m")

#_____________________________________________________________________________________
def plot(histname, output_name, systs=None, options={}, plotfunc=p.plot_hist):
    # Options
    alloptions= {
                "ratio_range":[0.4,1.6],
                #"nbins": 30,
                "autobin": True,
                "legend_scalex": 1.0,
                "legend_scaley": 1.0,
                "legend_smart": True,
                "legend_alignment": "topleft",
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
    ismu = str(histname).find("Mu") != -1
    is2d = str(histname).find("_vs_") != -1
    # Options
    alloptions= {
                "ratio_range":[0.4,1.6],
                #"nbins": 30,
                #"autobin": True,
                "legend_scalex": 1.0,
                "legend_scaley": 1.0,
                "legend_smart": True,
                "legend_alignment": "topleft",
                "output_name": "{}/{}_stack.pdf".format(output_plot_dir, output_name),
                "bkg_sort_method": "unsorted",
                "divide_by_bin_width": True if output_name.find("varbin") != -1 else False,
                "yaxis_log": True if output_name.find("varbin") != -1 else False,
                "yaxis_range": [1e3, 1e10] if output_name.find("varbin") != -1 else [],
                }
    alloptions.update(options)
    sigs = []
    bgs  = [
           samples.getHistogram("/top", histname).Clone("Top") if not is2d else p.flatten_th2(samples.getHistogram("/top", histname).Clone("Top")),
           samples.getHistogram("/Zonelep", histname).Clone("DY") if not is2d else p.flatten_th2(samples.getHistogram("/Zonelep", histname).Clone("DY")),
           samples.getHistogram("/Wonelep", histname).Clone("W") if not is2d else p.flatten_th2(samples.getHistogram("/Wonelep", histname).Clone("W")),
           samples.getHistogram("/qcd/mu" if ismu else "/qcd/el", histname).Clone("QCD") if not is2d else p.flatten_th2(samples.getHistogram("/qcd/mu" if ismu else "/qcd/el", histname).Clone("QCD")),
           ]
    dataname = "/data"
    if histname.find("El") != -1: dataname = "/data/ee"
    if histname.find("Mu") != -1: dataname = "/data/mm"
    data = samples.getHistogram(dataname, histname).Clone("Data") if not is2d else p.flatten_th2(samples.getHistogram(dataname, histname).Clone("Data"))
    if histname.find("HLT") != -1:
        totalbkg = p.get_total_hist(bgs)
        ratio = samples.getHistogram(dataname, histname).Clone("Data") if not is2d else p.flatten_th2(samples.getHistogram(dataname, histname).Clone("Data"))
        ratio.Rebin(ratio.GetNbinsX())
        totalbkg.Rebin(totalbkg.GetNbinsX())
        totalbkg.Divide(ratio)
        print histname
        totalbkg.Print("all")
    if (histname.find("OneMuTightEWKCR3NoNvtxRewgt/nvtx") != -1 or histname.find("OneElTightEWKCR3NoNvtxRewgt/nvtx") != -1) and options["nbins"] != 5:
        totalbkg = p.get_total_hist(bgs[:-1])
        nvtxweight = samples.getHistogram(dataname, histname).Clone(output_name) if not is2d else p.flatten_th2(samples.getHistogram(dataname, histname).Clone(output_name))
        scale = nvtxweight.Integral() / totalbkg.Integral()
        nvtxweight.Divide(totalbkg)
        nvtxweight.Scale(1./scale)
        #nvtxweight.Print("all")
        #f = ROOT.TFile("{}.root".format(output_name),"recreate")
        #nvtxweight.Write()
        #f.Close()
    if options["nbins"] == 5 and histname.find("TightEWKCR/MT") != -1:
        totalbkg = p.get_total_hist(bgs[:-1])
        ratio = samples.getHistogram(dataname, histname).Clone("Data") if not is2d else p.flatten_th2(samples.getHistogram(dataname, histname).Clone("Data"))
        ratio.Rebin(4)
        totalbkg.Rebin(4)
        ratio.Divide(totalbkg)
        print "EWK NF", histname, ratio.GetBinContent(3), ratio.GetBinError(3)
    colors = [ 2005, 2003, 2001, 920 ]
    sf = musf if ismu else elsf
    if histname.find("MTOneLep") == -1:
        bgs[0].Scale(sf)
        bgs[1].Scale(sf)
        bgs[2].Scale(sf)
    if histname.find("HLT") != -1:
        bgs = bgs[:-1]
    plotfunc(
            sigs = sigs,
            bgs  = bgs,
            data = data,
            colors = colors,
            syst = systs,
            options=alloptions)

#_____________________________________________________________________________________
def plot_datadriven_fakerate(histname, output_name, systs=None, options={}, plotfunc=p.plot_hist):
    if str(histname).find("Loose") == -1: return
    ismu = str(histname).find("Mu") != -1
    is2d = str(histname).find("_vs_") != -1
    # Options
    alloptions= {
                "ratio_range":[0.0,0.3],
                #"nbins": 30,
                "autobin": True,
                "legend_scalex": 1.0,
                "legend_scaley": 1.0,
                "legend_smart": True,
                "legend_alignment": "topleft",
                "legend_datalabel": "Data Tight",
                "output_name": "{}/{}_fakerate.pdf".format(output_plot_dir, output_name),
                "bkg_sort_method": "unsorted",
                }
    alloptions.update(options)
    sigs = []
    # Loose
    bgs  = [
           samples.getHistogram("/top", histname).Clone("Top") if not is2d else p.flatten_th2(samples.getHistogram("/top", histname).Clone("Top")),
           samples.getHistogram("/Zonelep", histname).Clone("DY") if not is2d else p.flatten_th2(samples.getHistogram("/Zonelep", histname).Clone("DY")),
           samples.getHistogram("/Wonelep", histname).Clone("W") if not is2d else p.flatten_th2(samples.getHistogram("/Wonelep", histname).Clone("W")),
           #samples.getHistogram("/qcd/mu" if ismu else "/qcd/el", histname).Clone("QCD") if not is2d else p.flatten_th2(samples.getHistogram("/qcd/mu" if ismu else "/qcd/el", histname).Clone("QCD")),
           ]
    dataname = "/data"
    if histname.find("El") != -1: dataname = "/data/ee"
    if histname.find("Mu") != -1: dataname = "/data/mm"
    ddqcd = samples.getHistogram(dataname, histname).Clone("Data") if not is2d else p.flatten_th2(samples.getHistogram(dataname, histname).Clone("Data"))
    totalbkg = p.get_total_hist(bgs)
    # tight
    bgstight  = [
           samples.getHistogram("/top", str(histname).replace("Loose","Tight")).Clone("Top") if not is2d else p.flatten_th2(samples.getHistogram("/top", str(histname).replace("Loose","Tight")).Clone("Top")),
           samples.getHistogram("/Zonelep", str(histname).replace("Loose","Tight")).Clone("DY") if not is2d else p.flatten_th2(samples.getHistogram("/Zonelep", str(histname).replace("Loose","Tight")).Clone("DY")),
           samples.getHistogram("/Wonelep", str(histname).replace("Loose","Tight")).Clone("W") if not is2d else p.flatten_th2(samples.getHistogram("/Wonelep", str(histname).replace("Loose","Tight")).Clone("W")),
           #samples.getHistogram("/qcd/mu" if ismu else "/qcd/el", str(histname).replace("Loose","Tight")).Clone("QCD") if not is2d else p.flatten_th2(samples.getHistogram("/qcd/mu" if ismu else "/qcd/el", str(histname).replace("Loose","Tight")).Clone("QCD")),
           ]
    dataname = "/data"
    if str(histname).replace("Loose","Tight").find("El") != -1: dataname = "/data/ee"
    if str(histname).replace("Loose","Tight").find("Mu") != -1: dataname = "/data/mm"
    ddqcdtight = samples.getHistogram(dataname, str(histname).replace("Loose","Tight")).Clone("Data") if not is2d else p.flatten_th2(samples.getHistogram(dataname, str(histname).replace("Loose","Tight")).Clone("Data"))
    totalbkgtight = p.get_total_hist(bgstight)
    # Get data-QCD
    sf = -musf if ismu else -elsf
    ddqcd.Add(totalbkg, sf)
    ddqcdtight.Add(totalbkgtight, sf)
    bgs = [ ddqcd.Clone("Data Loose") ]
    data = ddqcdtight
    # Compute data driven fake rate
    colors = [ 2005, 2003, 2001, 920 ]
    plotfunc(
            sigs = sigs,
            bgs  = bgs,
            data = data,
            colors = colors,
            syst = systs,
            options=alloptions)

#_____________________________________________________________________________________
def plot_datadriven_fakeratecomp(histname, output_name, systs=None, options={}, plotfunc=p.plot_hist):
    if str(histname).find("Loose") == -1: return
    ismu = str(histname).find("Mu") != -1
    is2d = str(histname).find("_vs_") != -1
    # Options
    alloptions= {
                "ratio_range":[0.0,2.0],
                #"nbins": 30,
                "autobin": True,
                "legend_scalex": 1.0,
                "legend_scaley": 1.0,
                "legend_smart": True,
                "legend_alignment": "topleft",
                "legend_datalabel": "Data FR",
                "output_name": "{}/{}_fakeratecomp.pdf".format(output_plot_dir, output_name),
                "bkg_sort_method": "unsorted",
                "draw_points": True,
                }
    alloptions.update(options)
    sigs = []
    # Loose
    bgs  = [
           samples.getHistogram("/top", histname).Clone("Top") if not is2d else p.flatten_th2(samples.getHistogram("/top", histname).Clone("Top")),
           samples.getHistogram("/Zonelep", histname).Clone("DY") if not is2d else p.flatten_th2(samples.getHistogram("/Zonelep", histname).Clone("DY")),
           samples.getHistogram("/Wonelep", histname).Clone("W") if not is2d else p.flatten_th2(samples.getHistogram("/Wonelep", histname).Clone("W")),
           #samples.getHistogram("/qcd/mu" if ismu else "/qcd/el", histname).Clone("QCD") if not is2d else p.flatten_th2(samples.getHistogram("/qcd/mu" if ismu else "/qcd/el", histname).Clone("QCD")),
           ]
    dataname = "/data"
    if histname.find("El") != -1: dataname = "/data/ee"
    if histname.find("Mu") != -1: dataname = "/data/mm"
    ddqcd = samples.getHistogram(dataname, histname).Clone("Data") if not is2d else p.flatten_th2(samples.getHistogram(dataname, histname).Clone("Data"))
    qcd = samples.getHistogram("/qcd/mu" if ismu else "/qcd/el", histname).Clone("QCD") if not is2d else p.flatten_th2(samples.getHistogram("/qcd/mu" if ismu else "/qcd/el", histname).Clone("QCD"))
    totalbkg = p.get_total_hist(bgs)
    # tight
    bgstight  = [
           samples.getHistogram("/top", str(histname).replace("Loose","Tight")).Clone("Top") if not is2d else p.flatten_th2(samples.getHistogram("/top", str(histname).replace("Loose","Tight")).Clone("Top")),
           samples.getHistogram("/Zonelep", str(histname).replace("Loose","Tight")).Clone("DY") if not is2d else p.flatten_th2(samples.getHistogram("/Zonelep", str(histname).replace("Loose","Tight")).Clone("DY")),
           samples.getHistogram("/Wonelep", str(histname).replace("Loose","Tight")).Clone("W") if not is2d else p.flatten_th2(samples.getHistogram("/Wonelep", str(histname).replace("Loose","Tight")).Clone("W")),
           #samples.getHistogram("/qcd/mu" if ismu else "/qcd/el", str(histname).replace("Loose","Tight")).Clone("QCD") if not is2d else p.flatten_th2(samples.getHistogram("/qcd/mu" if ismu else "/qcd/el", str(histname).replace("Loose","Tight")).Clone("QCD")),
           ]
    dataname = "/data"
    if str(histname).replace("Loose","Tight").find("El") != -1: dataname = "/data/ee"
    if str(histname).replace("Loose","Tight").find("Mu") != -1: dataname = "/data/mm"
    ddqcdtight = samples.getHistogram(dataname, str(histname).replace("Loose","Tight")).Clone("Data") if not is2d else p.flatten_th2(samples.getHistogram(dataname, str(histname).replace("Loose","Tight")).Clone("Data"))
    qcdtight = samples.getHistogram("/qcd/mu" if ismu else "/qcd/el", str(histname).replace("Loose","Tight")).Clone("QCD") if not is2d else p.flatten_th2(samples.getHistogram("/qcd/mu" if ismu else "/qcd/el", str(histname).replace("Loose","Tight")).Clone("QCD"))
    totalbkgtight = p.get_total_hist(bgstight)
    # Get data fakerate
    p.remove_overflow(totalbkg)
    p.remove_overflow(totalbkgtight)
    p.remove_overflow(ddqcd)
    p.remove_overflow(ddqcdtight)
    sf = -musf if ismu else -elsf
    ddqcd.Add(totalbkg, sf)
    ddqcdtight.Add(totalbkgtight, sf)
    ddqcdtight.Divide(ddqcd)
    # Get QCD fakerate
    p.remove_overflow(qcd)
    p.remove_overflow(qcdtight)
    qcdtight.Divide(qcd)
    bgs = [ qcdtight.Clone("QCD FR") ]
    data = ddqcdtight
    # Compute data driven fake rate
    colors = [ 2 ]
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
                "legend_scalex": 1.4 if ispredict else 0.8,
                "legend_scaley": 0.8,
                "legend_smart": True,
                "legend_alignment": "topleft",
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
                "legend_smart": True,
                "legend_alignment": "topleft",
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
                "legend_smart": True,
                "legend_alignment": "topleft",
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
                "legend_smart": True,
                "legend_alignment": "topleft",
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

    import multiprocessing

    jobs = []

    histograms = [
            "TwoMuHLT17/Mll_Z",
            "TwoElHLT17/Mll_Z",
            "OneMuTightEWKCR3NoNvtxRewgt/nvtx",
            "OneElTightEWKCR3NoNvtxRewgt/nvtx",
            "OneMuTightEWKCR3/nvtx",
            "OneElTightEWKCR3/nvtx",
            "OneMuTightEWKCR/MTOneLepFixed",
            "OneElTightEWKCR/MTOneLepFixed",
            "OneMuLoose/lep_ptcorrvarbincoarse",
            "OneElLoose/lep_ptcorrvarbincoarse",
            "OneMuTight/lep_ptcorrvarbincoarse",
            "OneElTight/lep_ptcorrvarbincoarse",
            "OneElLoose/lep_ptcorrcoarse_vs_etacoarse",
            "OneMuLoose/lep_ptcorrcoarse_vs_etacoarse",
            "OneElTight/lep_ptcorrcoarse_vs_etacoarse",
            "OneMuTight/lep_ptcorrcoarse_vs_etacoarse",
            "TwoMuLoosePredict/mu_yield",
            "TwoElLoosePredictComb/el_yield",
            "TwoMuLoosePredictBVeto/mu_yield",
            "TwoElLoosePredictBVetoComb/el_yield",
            "TwoMuLoosePredict/Mjj_mu",
            "TwoElLoosePredictComb/Mjj_el",
            "TwoMuLoosePredictBVeto/Mjj_mu",
            "TwoElLoosePredictBVetoComb/Mjj_el",
            "TwoMuLoosePredict/MTmax_mu",
            "TwoElLoosePredictComb/MTmax_el",
            "TwoMuLoosePredictBVeto/MTmax_mu",
            "TwoElLoosePredictBVetoComb/MTmax_el",
            ]

    for histname in samples.getListOfHistogramNames():

        #if str(histname).find("OneMuLoose/lep_ptcorrcoarse_vs_etacoarse") == -1:
        #    continue
        #if str(histname) not in histograms:
        #    continue

        hname = str(histname)
        if hname.find("EWKCR") != -1 and hname.find("_vs_") == -1:
            hfilename = hname.replace("/", "_")
            proc = multiprocessing.Process(target=plot_stack, args=[hname, hfilename], kwargs={"systs":None, "options":{"autobin":False, "nbins":15 if hname.find("nvtx") == 1 else 60, "lumi_value":35.9, "yaxis_log":False, "no_ratio": True, "xaxis_ndivisions": 505 if hname.find("MTOneLep") != -1 else 508}, "plotfunc": p.plot_hist})
            jobs.append(proc)
            proc.start()
            hfilename = hname.replace("/", "_")
            if hname.find("MTOneLepFixed") != -1:
                proc = multiprocessing.Process(target=plot_stack, args=[hname, hfilename+"_5bins"], kwargs={"systs":None, "options":{"autobin":False, "nbins":5, "lumi_value":35.9, "yaxis_log":False}, "plotfunc": p.plot_hist})
                jobs.append(proc)
                proc.start()
        elif hname.find("HLT") != -1 and hname.find("_vs_") == -1:
            hfilename = hname.replace("/", "_")
            proc = multiprocessing.Process(target=plot_stack, args=[hname, hfilename], kwargs={"systs":None, "options":{"autobin":False, "nbins":60, "lumi_value":35.9, "yaxis_log":False, "no_ratio":True}, "plotfunc": p.plot_hist})
            jobs.append(proc)
            proc.start()
        elif hname.find("_vs_") != -1:
            hfilename = hname.replace("/", "_")
            #proc = multiprocessing.Process(target=fakerate2d, args=[hname, hfilename], kwargs={"systs":None, "options":{}, "plotfunc": ply.plot_hist_2d})
            #proc = multiprocessing.Process(target=fakerate2d, args=[hname, hfilename], kwargs={"systs":None, "options":{"autobin":False, "nbins":15, "lumi_value":35.9, "yaxis_log":True}, "plotfunc": p.plot_hist})
            #jobs.append(proc)
            #proc.start()
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
        if hname.find("EWKCR") == -1:
            histnamepatterncheck = ["OneMuTight/", "OneMuLoose/", "OneElTight/", "OneElLoose/"]
            pttn_matched = False
            for pttn in histnamepatterncheck:
                if hname.find(pttn) != -1:
                    pttn_matched = True
            if pttn_matched:
                hfilename = hname.replace("/", "_")
                proc = multiprocessing.Process(target=plot_stack, args=[hname, hfilename], kwargs={"systs":None, "options":{"autobin":False, "nbins":15, "lumi_value":35.9, "no_ratio":True}, "plotfunc": p.plot_hist})
                jobs.append(proc)
                proc.start()
                hfilename = hname.replace("/", "_")
                proc = multiprocessing.Process(target=plot_datadriven_fakerate, args=[hname, hfilename], kwargs={"systs":None, "options":{"autobin":False, "nbins":15, "lumi_value":35.9, "yaxis_log":False}, "plotfunc": p.plot_hist})
                jobs.append(proc)
                proc.start()
                proc = multiprocessing.Process(target=plot_datadriven_fakeratecomp, args=[hname, hfilename], kwargs={"systs":None, "options":{"autobin":False, "nbins":15, "lumi_value":35.9, "yaxis_log":False}, "plotfunc": p.plot_hist})
                jobs.append(proc)
                proc.start()

    for job in jobs:
        job.join()

