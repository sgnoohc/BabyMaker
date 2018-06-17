#!/bin/env python

import os
import sys
import ROOT
from QFramework import TQSampleFolder, TQXSecParser, TQCut, TQAnalysisSampleVisitor, TQSampleInitializer, TQCutflowAnalysisJob, TQCutflowPrinter, TQHistoMakerAnalysisJob
from rooutil import plottery_wrapper as p
from plottery import plottery as ply

ROOT.gROOT.SetBatch(True)
samples = TQSampleFolder.loadSampleFolder("output_sf_applied.root:samples")
#samples = TQSampleFolder.loadSampleFolder("output.root:samples")

output_plot_dir = "plots"

# Categories
# VBSWW, ttW, ttZ, WZ, Other

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
def plot_mainprocess(histname, output_name, systs=None, options={}, plotfunc=p.plot_hist):
    # Options
    alloptions= {
                "ratio_range":[0.0,2.0],
                #"nbins": 30,
                "autobin": True,
                "legend_scalex": 1.8,
                "legend_scaley": 1.1,
                "output_name": "{}/{}_mainprocess.pdf".format(output_plot_dir, output_name),
                "bkg_sort_method": "unsorted",
                }
    alloptions.update(options)
    sigs = [ samples.getHistogram("/sig", histname).Clone("WWW") ]
    bgs  = [ 
             samples.getHistogram("/typebkg/?/Other", histname).Clone("Other"),
             samples.getHistogram("/typebkg/?/ttZ", histname).Clone("ttZ"),
             samples.getHistogram("/typebkg/?/ttW", histname).Clone("ttW"),
             samples.getHistogram("/typebkg/?/WZ", histname).Clone("WZ"),
             samples.getHistogram("/typebkg/?/VBSWW", histname).Clone("VBSWW"),
             ]
    data =   samples.getHistogram("/data", histname).Clone("Data")
    colors = [ 920, 2007, 2005, 2003, 2001 ]
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
                "legend_scalex": 1.8,
                "legend_scaley": 1.1,
                "output_name": "{}/{}_typebkg.pdf".format(output_plot_dir, output_name),
                "bkg_sort_method": "unsorted",
                }
    alloptions.update(options)
    sigs = [ samples.getHistogram("/sig", histname).Clone("WWW") ]
    bgs  = [ 
             samples.getHistogram("/typebkg/photon", histname).Clone("#gamma#rightarrowlepton"),
             samples.getHistogram("/typebkg/qflip", histname).Clone("Charge mis-id"),
             samples.getHistogram("/typebkg/fakes", histname).Clone("Non-prompt"),
             samples.getHistogram("/typebkg/lostlep", histname).Clone("Lost-lep/WZ"),
             samples.getHistogram("/typebkg/prompt", histname).Clone("Irredu."),
             ]
    data =   samples.getHistogram("/data", histname).Clone("Data")
    colors = [ 920, 2007, 2005, 2003, 2001 ]
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
                "ratio_range":[0.0,2.0],
                #"nbins": 30,
                "autobin": True,
                "legend_scalex": 1.8,
                "legend_scaley": 1.1,
                "output_name": "{}/{}_frmethod.pdf".format(output_plot_dir, output_name),
                "bkg_sort_method": "unsorted",
                #"signal_scale": 2
                }
    alloptions.update(options)
    # Fake background
    histnameup = histname.replace("Full", "FullFakeUp")
    fake_cn = samples.getHistogram("/fake", histname).Clone("Non-prompt")
    fake_up = samples.getHistogram("/fake", histnameup).Clone("Non-prompt")
    p.add_diff_to_error(fake_cn, fake_up)
    #p.add_frac_syst(fake_cn, 2.3)

    # other bkg
    prompt = samples.getHistogram("/typebkg/prompt", histname).Clone("Irredu.")
    lostlep = samples.getHistogram("/typebkg/lostlep", histname).Clone("Lost/three lep")
    photon = samples.getHistogram("/typebkg/photon", histname).Clone("#gamma#rightarrowlepton")
    qflip =samples.getHistogram("/typebkg/qflip", histname).Clone("Charge mis-id")
    #p.add_frac_syst(prompt, 0.2)
    #p.add_frac_syst(lostlep, 0.3)
    #p.add_frac_syst(photon, 0.5)
    #p.add_frac_syst(qflip, 1.0)

    www = samples.getHistogram("/sig", histname).Clone("WWW")
    #www.Scale(5)
    sigs = [ www, samples.getHistogram("/bsm/wprime/1200", histname).Clone("W'")  ]
    sigs = [ www ]
    bgs  = [ 
             photon,
             qflip,
             fake_cn,
             lostlep,
             prompt,
             ]
    data =   samples.getHistogram("/data", histname).Clone("Data")
    colors = [ 920, 2007, 2005, 2003, 2001 ]
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
    if hname.find("GCR") != -1: return False
    if hname.find("VBSCR") != -1: return False
    if hname.find("TTWCR") != -1: return False
    if hname.find("TTZCR") != -1: return False
    if hname.find("LMETCR") != -1: return False
    return True

#_____________________________________________________________________________________
def dofrmethod(hname):
    if hname.find("SR") != -1: return True
    if hname.find("BT") != -1: return True
    if hname.find("LMETCR") != -1: return True
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
        proc = multiprocessing.Process(target=plot_typebkg, args=[hname, hfilename], kwargs={"systs":None, "options":{"blind": isblind(hname), "autobin":False, "nbins":30, "lumi_value":35.9, "yaxis_log":False}, "plotfunc": p.plot_hist})
        jobs.append(proc)
        proc.start()

        # Plotting by bkg type
        proc = multiprocessing.Process(target=plot_mainprocess, args=[hname, hfilename], kwargs={"systs":None, "options":{"blind": isblind(hname), "autobin":False, "nbins":30, "lumi_value":35.9, "yaxis_log":False}, "plotfunc": p.plot_hist})
        jobs.append(proc)
        proc.start()

        # Plotting by physics process
        #proc = multiprocessing.Process(target=plot, args=[hname, hfilename], kwargs={"systs":None, "options":{"blind": hname.find("WZ") == -1, "autobin":False, "nbins":30, "lumi_value":35.9, "yaxis_log":False}, "plotfunc": p.plot_hist})
        #jobs.append(proc)
        #proc.start()

        # Plotting by bkg type and fakes are estimated from data
        if dofrmethod(hname):
            proc = multiprocessing.Process(target=plot_frmethod, args=[hname, hfilename], kwargs={"systs":None, "options":{"blind": isblind(hname), "autobin":False, "nbins":30, "lumi_value":35.9, "yaxis_log":False}, "plotfunc": p.plot_hist})
            jobs.append(proc)
            proc.start()

        # For scanning cuts to optimize
        #proc = multiprocessing.Process(target=plot, args=[hname, hfilename], kwargs={"systs":None, "options":{"blind": hname.find("WZ") == -1, "autobin":False, "nbins":30, "lumi_value":35.9, "yaxis_log":False}, "plotfunc": p.plot_cut_scan})
        #jobs.append(proc)
        #proc.start()

    for job in jobs:
        job.join()

if __name__ == "__main__":

    histnames = samples.getListOfHistogramNames()
    histnames = []

    #histnames.extend(["{WZCRSSeeFull,WZCRSSemFull,WZCRSSmmFull,WZCR1SFOSFull,WZCR2SFOSFull}"])
    #histnames.extend(["{WZCRSSeePre,WZCRSSemPre,WZCRSSmmPre,WZCR1SFOSPre,WZCR2SFOSPre}"])

    #histnames.extend(["{ARSSeePre,ARSSemPre,ARSSmmPre,ARSideSSeePre,ARSideSSemPre,ARSideSSmmPre,AR0SFOSPre,AR1SFOSPre,AR2SFOSPre}"])
    #histnames.extend(["{ARSSeeFull,ARSSemFull,ARSSmmFull,ARSideSSeeFull,ARSideSSemFull,ARSideSSmmFull,AR0SFOSFull,AR1SFOSFull,AR2SFOSFull}"])

    histnames.extend(["{SRSSeeFull,SRSSemFull,SRSSmmFull,SideSSeeFull,SideSSemFull,SideSSmmFull,SR0SFOSFull,SR1SFOSFull,SR2SFOSFull}"])
    #histnames.extend(["{SRSSeeFullFakeUp,SRSSemFullFakeUp,SRSSmmFullFakeUp,SideSSeeFullFakeUp,SideSSemFullFakeUp,SideSSmmFullFakeUp,SR0SFOSFullFakeUp,SR1SFOSFullFakeUp,SR2SFOSFullFakeUp}"])

    #histnames.extend(["{GCR0SFOSPre}"])

    #histnames.extend(["{VBSCRSSeeFull,VBSCRSSemFull,VBSCRSSmmFull}"])

    #histnames.extend(["{LMETCRSSeeFull,LMETCRSSemFull,LMETCRSSmmFull}"])

    #histnames.extend(["{BTCRSSeeFull,BTCRSSemFull,BTCRSSmmFull,BTCRSideSSeeFull,BTCRSideSSemFull,BTCRSideSSmmFull,BTCR0SFOSFull,BTCR1SFOSFull,BTCR2SFOSFull}"])
    #histnames.extend(["BTCRSSeeFull/lep_pt0+BTCRSSemFull/lep_pt0+BTCRSSmmFull/lep_pt0"])
    #histnames.extend(["BTCRSideSSeeFull/lep_pt0+BTCRSideSSemFull/lep_pt0+BTCRSideSSmmFull/lep_pt0"])
    #histnames.extend(["BTCRSSeeFull/lep_pt1+BTCRSSemFull/lep_pt1+BTCRSSmmFull/lep_pt1"])
    #histnames.extend(["BTCRSideSSeeFull/lep_pt1+BTCRSideSSemFull/lep_pt1+BTCRSideSSmmFull/lep_pt1"])
    #histnames.extend(["BTCRSSeeFull/MET+BTCRSSemFull/MET+BTCRSSmmFull/MET"])
    #histnames.extend(["BTCRSideSSeeFull/MET+BTCRSideSSemFull/MET+BTCRSideSSmmFull/MET"])
    #histnames.extend(["BTCRSSeeFull/lep_pt0+BTCRSSemFull/lep_pt0+BTCRSSmmFull/lep_pt0+BTCRSideSSeeFull/lep_pt0+BTCRSideSSemFull/lep_pt0+BTCRSideSSmmFull/lep_pt0"])
    #histnames.extend(["BTCRSSeeFull/lep_pt1+BTCRSSemFull/lep_pt1+BTCRSSmmFull/lep_pt1+BTCRSideSSeeFull/lep_pt1+BTCRSideSSemFull/lep_pt1+BTCRSideSSmmFull/lep_pt1"])
    #histnames.extend(["BTCRSSeeFull/MET+BTCRSSemFull/MET+BTCRSSmmFull/MET+BTCRSideSSeeFull/MET+BTCRSideSSemFull/MET+BTCRSideSSmmFull/MET"])

    #histnames.extend(["{LMETCRSSeeFull,LMETCRSSemFull,LMETCRSSmmFull}"])
    #histnames.extend(["LMETCRSSeeFull/lep_pt0+LMETCRSSemFull/lep_pt0+LMETCRSSmmFull/lep_pt0"])
    #histnames.extend(["LMETCRSSeeFull/lep_pt1+LMETCRSSemFull/lep_pt1+LMETCRSSmmFull/lep_pt1"])
    #histnames.extend(["LMETCRSSeeFull/MET+LMETCRSSemFull/MET+LMETCRSSmmFull/MET"])
    #histnames.extend(["LMETCRSSeeFull/Mjj+LMETCRSSemFull/Mjj+LMETCRSSmmFull/Mjj"])



    #histnames.extend(["BTCRSSeeFull/MET"])
    #histnames.extend(["{BTCRSSeePre,BTCRSSemPre,BTCRSSmmPre,BTCR0SFOSPre,BTCR1SFOSPre,BTCR2SFOSPre}"])

    #histnames.extend(["{BTWZCRSSeeFull,BTWZCRSSemFull,BTWZCRSSmmFull}"])

    #histnames.extend(["{TTWCRSSeePre,TTWCRSSemPre,TTWCRSSmmPre}"])

    #histnames.extend(["SRSSeePre/Mlvlvjj+SRSSemPre/Mlvlvjj+SRSSmmPre/Mlvlvjj"])
    #histnames.extend(["SRSSeePre/Mlvlvjj_wide+SRSSemPre/Mlvlvjj_wide+SRSSmmPre/Mlvlvjj_wide"])
    #histnames.extend(["SRSSemPre/Mjj+SRSSmmPre/Mjj"])
    #histnames.extend(["SRSSeePre/Mjj+SRSSemPre/Mjj+SRSSmmPre/Mjj"])
    #histnames.extend(["SRSSmmPre/Mjj"])
    #histnames.extend(["SRSSmmPre/Mjj"])
    #histnames.extend(["SR0SFOSMET/MTmax3L"])
    #histnames.extend(["SR0SFOSZVt/MTmax3L"])
    #histnames.extend(["SR1SFOSZVt/MT3rd"])

    #histnames.extend(["SideSSmmMjj/MjjVBF"])
    #histnames.extend(["SideSSmmMjj/DetajjVBF"])

    #histnames.extend(["{SRSSeeFull,SideSSeeFull,SRSSemFull,SideSSemFull,SRSSmmFull,SideSSmmFull,SR0SFOSFull,SR1SFOSFull,SR2SFOSFull}"])
    #histnames.extend(["{SRSSeePre,SRSSemPre,SRSSmmPre,SR0SFOSPre,SR1SFOSPre,SR2SFOSPre,SideSSeePre,SideSSemPre,SideSSmmPre}"])
    #histnames.extend(["{SRSSeePre,SideSSeePre,SRSSemPre,SideSSemPre,SRSSmmPre,SideSSmmPre,SR0SFOSPre,SR1SFOSPre,SR2SFOSPre}"])
    #histnames.extend(["{ARSSeePre,ARSSemPre,ARSSmmPre,AR0SFOSPre,AR1SFOSPre,AR2SFOSPre,ARSideSSeePre,ARSideSSemPre,ARSideSSmmPre}"])
    #histnames.extend(["{WZCRSSeePre,WZCRSSemPre,WZCRSSmmPre,WZCR1SFOSPre,WZCR2SFOSPre}"])
    #histnames.extend(["{BTCRSSeePre,BTCRSSemPre,BTCRSSmmPre,BTCR0SFOSPre,BTCR1SFOSPre,BTCR2SFOSPre,BTCRSideSSeePre,BTCRSideSSemPre,BTCRSideSSmmPre}"])
    #histnames.extend(["GCR0SFOSPre/M3l"])
    #histnames.extend(["GCR0SFOSPre/MET"])
    #histnames.extend(["GCR0SFOSPre/Pt3l"])
    #histnames.extend(["VBSCRSSeeFull/MjjL+VBSCRSSemFull/MjjL+VBSCRSSmmFull/MjjL"])
    #histnames.extend(["VBSCRSSeeFull/DetajjL+VBSCRSSemFull/DetajjL+VBSCRSSmmFull/DetajjL"])
    #histnames.extend(["TTWCRSSeeMjjW/nb+TTWCRSSemMjjW/nb+TTWCRSSmmMjjW/nb"])
    #histnames.extend(["TTWCRSSeeMjjW/MllSS+TTWCRSSemMjjW/MllSS+TTWCRSSmmMjjW/MllSS"])
    #histnames.extend(["TTZCR0SFOSPre/nb+TTZCR1SFOSPre/nb+TTZCR2SFOSPre/nb"])

    #histnames.extend(["{SRSSeeNb0,SRSSemNb0,SRSSmmNb0,SR0SFOSNb0,SR1SFOSNb0,SR2SFOSNb0}"])
    #histnames.extend(["{ARSSeeNb0,ARSSemNb0,ARSSmmNb0,AR0SFOSNb0,AR1SFOSNb0,AR2SFOSNb0}"])
    #histnames.extend(["{SRSSeeZeeVt,SRSSemMTmax,SRSSmmMllSS,SR0SFOSZVt,SR1SFOSMT3rd,SR2SFOSZVt}"])
    #histnames.extend(["{ARSSeeZeeVt,ARSSemMTmax,ARSSmmMllSS,AR0SFOSZVt,AR1SFOSMT3rd,AR2SFOSZVt}"])
    #histnames.extend(["{BTCRSSeeZeeVt,BTCRSSemMTmax,BTCRSSmmMllSS,BTCR0SFOSZVt,BTCR1SFOSMT3rd,BTCR2SFOSZVt}"])
    #histnames.extend(["{BTCRSSeeNbgeq1,BTCRSSemNbgeq1,BTCRSSmmNbgeq1,BTCR0SFOSNbgeq1,BTCR1SFOSNbgeq1,BTCR2SFOSNbgeq1}"])
    #histnames.extend(["BTCRSSeeZeeVt/MET"])
    #histnames.extend(["BTCRSSemMTmax/MET"])
    #histnames.extend(["BTCRSSmmMllSS/MET"])
    #histnames.extend(["BTCRSSeeZeeVt/MET+BTCRSSemMTmax/MET+BTCRSSmmMllSS/MET"])
    #histnames.extend(["BTCRSSeeZeeVt/Mjj+BTCRSSemMTmax/Mjj+BTCRSSmmMllSS/Mjj"])
    #histnames.extend(["BTCRSSeeZeeVt/MllSS+BTCRSSemMTmax/MllSS+BTCRSSmmMllSS/MllSS"])
    #histnames.extend(["BTCRSSeeNbgeq1/MET"])
    #histnames.extend(["BTCRSSemNbgeq1/MET"])
    #histnames.extend(["BTCRSSmmNbgeq1/MET"])

    plotall(histnames)
