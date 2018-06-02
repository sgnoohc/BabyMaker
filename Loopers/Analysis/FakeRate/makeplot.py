#!/bin/env python

import os
import sys
import ROOT
from QFramework import TQSampleFolder, TQXSecParser, TQCut, TQAnalysisSampleVisitor, TQSampleInitializer, TQCutflowAnalysisJob, TQCutflowPrinter, TQHistoMakerAnalysisJob
from rooutil import plottery_wrapper as p
from plottery import plottery as ply

ROOT.gROOT.SetBatch(True)
samples_cn = TQSampleFolder.loadSampleFolder("output.root:samples")
samples_up = TQSampleFolder.loadSampleFolder("output_up.root:samples")
samples_dn = TQSampleFolder.loadSampleFolder("output_dn.root:samples")

output_plot_dir = "plots"

#___________________________________________________________________________
# Function to retrieve SF
def ewksf(cut, channel, samples):
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

#___________________________________________________________________________
# Retrieve scale factors
# The scale factor variables will be treated as a global variable
elsf_cn = ewksf("OneElTightEWKCR", "e", samples_cn)
musf_cn = ewksf("OneMuTightEWKCR", "m", samples_cn)
elsf_up = ewksf("OneElTightEWKCR", "e", samples_up)
musf_up = ewksf("OneMuTightEWKCR", "m", samples_up)
elsf_dn = ewksf("OneElTightEWKCR", "e", samples_dn)
musf_dn = ewksf("OneMuTightEWKCR", "m", samples_dn)

print "EWK NF el", elsf_cn, elsf_up, elsf_dn
print "EWK NF el", musf_cn, musf_up, musf_dn

#___________________________________________________________________________
# "proc" could be one of ["datael", "datamu", "top", "w", "dy", "qcdel", "qcdmu"]
# "cut" is the cut name that is corresponding to from loop.py
# "variable" is the histogram name
def get_histogram(samples, proc, cut, variable, applysf=False):

    # Check the requested process 
    available_processes = ["data", "top", "w", "dy", "qcd"]
    if proc not in available_processes:
        print "ERROR: unrecognized process", proc
        sys.exit(-1)

    # Check the cut to determine whether this is one lepton process or two lepton
    # This is because the ntuple used for one lepton and two lepton is different
    # Therefore one need to check this to retrieve the right mc ntuple
    isonelep = cut.find("One") != -1

    # Checking the flavor of the lepton this histogram retreival is interested in
    ismu = cut.find("Mu") != -1

    # Checking if it is a 2d histogram
    # The convention is that the histogram names in loop.py all the 2d histogram must have "_vs_" name
    is2d = variable.find("_vs_") != -1

    # Setting the proc path
    tqprocpath = "/"
    if proc == "data": tqprocpath = "/data/mm" if ismu else "/data/ee"
    if proc == "top": tqprocpath = "/top"
    if proc == "w": tqprocpath = "/Wonelep" if isonelep else "/W/HT"
    if proc == "dy": tqprocpath = "/Zonelep" if isonelep else "/Z"
    if proc == "qcd": tqprocpath = "/qcd/mu" if ismu else "/qcd/el"

    # Setting the nice name
    nicename = "/"
    if proc == "data": nicename = "Data"
    if proc == "top": nicename = "t#bar{t}"
    if proc == "w": nicename = "W"
    if proc == "dy": nicename = "DY"
    if proc == "qcd": nicename = "QCD"

    # Retrieve the histograms
    hist = samples.getHistogram(tqprocpath, "{}/{}".format(cut, variable)).Clone(nicename)

    # Apply ewk sf
    if applysf:
        sf = 1.0
        if samples == samples_cn: sf = musf_cn if ismu else elsf_cn
        if samples == samples_up: sf = musf_up if ismu else elsf_up
        if samples == samples_dn: sf = musf_dn if ismu else elsf_dn
        if proc == "top": hist.Scale(sf)
        if proc == "w"  : hist.Scale(sf)
        if proc == "dy" : hist.Scale(sf)

    # If 2D plot, flatten it
    if is2d:
        hist = p.flatten_th2(hist)

    return hist

#___________________________________________________________________________
def hlt_prescale():
    cut = "TwoMuHLT17"
    var = "Mll_Z"

    # Retrieve histograms
    h_cn_data = get_histogram(samples_cn, "data" , cut , var)
    h_cn_top  = get_histogram(samples_cn, "top"  , cut , var)
    h_cn_w    = get_histogram(samples_cn, "w"    , cut , var)
    h_cn_dy   = get_histogram(samples_cn, "dy"   , cut , var)
    h_cn_qcd  = get_histogram(samples_cn, "qcd"  , cut , var)
    b = p.get_total_hist([h_cn_top, h_cn_dy, h_cn_w])
    b.Rebin(b.GetNbinsX())
    h_cn_data.Rebin(h_cn_data.GetNbinsX())
    b.Divide(h_cn_data)
    print cut, var, b.GetBinContent(1), b.GetBinError(1)

    cut = "TwoElHLT17"
    var = "Mll_Z"

    # Retrieve histograms
    h_cn_data = get_histogram(samples_cn, "data" , cut , var)
    h_cn_top  = get_histogram(samples_cn, "top"  , cut , var)
    h_cn_w    = get_histogram(samples_cn, "w"    , cut , var)
    h_cn_dy   = get_histogram(samples_cn, "dy"   , cut , var)
    h_cn_qcd  = get_histogram(samples_cn, "qcd"  , cut , var)
    b = p.get_total_hist([h_cn_top, h_cn_dy, h_cn_w])
    b.Rebin(b.GetNbinsX())
    h_cn_data.Rebin(h_cn_data.GetNbinsX())
    b.Divide(h_cn_data)
    print cut, var, b.GetBinContent(1), b.GetBinError(1)

#___________________________________________________________________________
def compute_nvtx_reweighting():

    f = ROOT.TFile("nvtxreweight.root", "recreate")

    cut = "OneMuTightEWKCR3NoNvtxRewgt"
    var = "nvtx"

    # Retrieve histograms
    h_cn_data = get_histogram(samples_cn, "data" , cut , var)
    h_cn_top  = get_histogram(samples_cn, "top"  , cut , var)
    h_cn_w    = get_histogram(samples_cn, "w"    , cut , var)
    h_cn_dy   = get_histogram(samples_cn, "dy"   , cut , var)
    h_cn_qcd  = get_histogram(samples_cn, "qcd"  , cut , var)
    b = p.get_total_hist([h_cn_top, h_cn_dy, h_cn_w])

    # Get total integral to get the total offset
    bi = b.Integral()
    di = h_cn_data.Integral()
    ratio = di / bi

    # Compute reweighting
    h_cn_data.Divide(b)
    h_cn_data.Scale(1./ratio)
    h_cn_data.SetName(cut+"_"+var)
    h_cn_data.SetTitle(cut+"_"+var)
    h_cn_data.Write()

    cut = "OneElTightEWKCR3NoNvtxRewgt"
    var = "nvtx"

    # Retrieve histograms
    h_cn_data = get_histogram(samples_cn, "data" , cut , var)
    h_cn_top  = get_histogram(samples_cn, "top"  , cut , var)
    h_cn_w    = get_histogram(samples_cn, "w"    , cut , var)
    h_cn_dy   = get_histogram(samples_cn, "dy"   , cut , var)
    h_cn_qcd  = get_histogram(samples_cn, "qcd"  , cut , var)
    b = p.get_total_hist([h_cn_top, h_cn_dy, h_cn_w])

    # Get total integral to get the total offset
    bi = b.Integral()
    di = h_cn_data.Integral()
    ratio = di / bi

    # Compute reweighting
    h_cn_data.Divide(b)
    h_cn_data.Scale(1./ratio)
    h_cn_data.SetName(cut+"_"+var)
    h_cn_data.SetTitle(cut+"_"+var)
    h_cn_data.Write()

    f.Close()


#___________________________________________________________________________
def plot_stack(cut, var, dosf=False, options={}):

    # Setting variables to be used for option setting
    output_name = cut + "_" + var
    isvarbin = output_name.find("varbin") != -1
    divide_by_bin_width = isvarbin
    yaxis_log = isvarbin
    yaxis_range = [1e3, 1e10] if isvarbin else []

    # Options
    alloptions= {
                "ratio_range":[0.4,1.6],
                "legend_scalex": 1.0,
                "legend_scaley": 1.0,
                "legend_smart": True,
                "legend_alignment": "topleft",
                "output_name": "plots/{}_stack.pdf".format(output_name),
                "bkg_sort_method": "unsorted",
                "divide_by_bin_width": divide_by_bin_width,
                "yaxis_log": yaxis_log,
                "yaxis_range": yaxis_range,
                "no_ratio": True,
                }

    # Whatever the option passed through the argument can override anything
    alloptions.update(options)

    # Colors of the MC histograms
    colors = [ 2005, 2003, 2001, 920 ] # in order of top, Z, W, QCD

    # Retrieve histograms
    h_cn_data = get_histogram(samples_cn, "data" , cut , var , dosf)
    h_cn_top  = get_histogram(samples_cn, "top"  , cut , var , dosf)
    h_cn_w    = get_histogram(samples_cn, "w"    , cut , var , dosf)
    h_cn_dy   = get_histogram(samples_cn, "dy"   , cut , var , dosf)
    h_cn_qcd  = get_histogram(samples_cn, "qcd"  , cut , var , dosf)

    # Arrange the histograms
    sigs = []
    bgs = [ h_cn_top, h_cn_dy, h_cn_w, h_cn_qcd ]
    data = h_cn_data

    # Plot!
    p.plot_hist(
            sigs = sigs,
            bgs  = bgs,
            data = data,
            colors = colors,
            options=alloptions)

#___________________________________________________________________________
def plot_closure(cut, var, options={}):

    # Sanity check that the name of the cut contains "Predict"
    # If not, then quietly exit the function without doing anything
    ispredict = cut.find("Predict") != -1
    if not ispredict:
        print "ERROR - requested plot_closure on", cut, var, "but did not find Predict in name"
        return

    # Sanity check that the name of the cut contains "Loose"
    # If not, then quietly exit the function without doing anything
    isloose = cut.find("Loose") != -1
    if not isloose:
        print "ERROR - requested plot_closure on", cut, var, "but did not find Loose in name"
        return

    # Setting variables to be used for option setting
    output_name = cut + "_" + var
    isvarbin = output_name.find("varbin") != -1
    divide_by_bin_width = isvarbin
    yaxis_log = isvarbin
    yaxis_range = [1e3, 1e10] if isvarbin else []

    # Options
    alloptions= {
                "ratio_range":[0.4,1.6],
                "nbins": 15,
                "legend_scalex": 1.4,
                "legend_scaley": 1.0,
                "legend_smart": True,
                "legend_alignment": "topleft",
                "output_name": "plots/{}_closure.pdf".format(output_name),
                "bkg_sort_method": "unsorted",
                "divide_by_bin_width": divide_by_bin_width,
                "yaxis_log": yaxis_log,
                "yaxis_range": yaxis_range,
                "legend_datalabel": "t#bar{t} + W prediction",
                "xaxis_ndivisions": 101,
                }

    # Whatever the option passed through the argument can override anything
    alloptions.update(options)

    # Colors of the MC histograms
    colors = [ 2005, 2001 ] # in order of top, Z, W, QCD

    # Retrieve histograms (loose means "estimation", i.e. apply the "tight" selection. I KNOW IT'S A TERRIBLE NAMING....)
    h_loose_cn_top  = get_histogram(samples_cn, "top"  , cut , var)
    h_loose_cn_w    = get_histogram(samples_cn, "w"    , cut , var)

    # Retrieve histograms (tight means "prediction", i.e. loose!tight * fake-factor)
    h_tight_cn_top  = get_histogram(samples_cn, "top"  , cut.replace("Loose", "Tight") , var)
    h_tight_cn_w    = get_histogram(samples_cn, "w"    , cut.replace("Loose", "Tight") , var)

    # Form the "prediction" which is the sum of 'tight'
    h_tight_cn_top.Add(h_tight_cn_w)

    # Name the histograms
    h_loose_cn_w.SetName("W estimation")
    h_loose_cn_top.SetName("t#bar{t} estimation")

    # Arrange the histograms
    sigs = []
    bgs = [ h_loose_cn_top, h_loose_cn_w ]
    data = h_tight_cn_top

    # Plot!
    p.plot_hist(
            sigs = sigs,
            bgs  = bgs,
            data = data,
            colors = colors,
            options=alloptions)

#___________________________________________________________________________
def get_qcd_fakerate(samples, cutloose, cuttight, var, dosf=False):

    # Retrieve histograms
    h_loose_qcd  = get_histogram(samples, "qcd"  , cutloose , var , dosf)
    h_tight_qcd  = get_histogram(samples, "qcd"  , cuttight , var , dosf)

    # Compute fakerate
    h_tight_qcd.Divide(h_loose_qcd)

    return h_tight_qcd

#___________________________________________________________________________
def get_datadriven_fakerate(samples, cutloose, cuttight, var, dosf=False):

    # Retrieve histograms
    h_loose_data = get_histogram(samples, "data" , cutloose , var , dosf)
    h_loose_top  = get_histogram(samples, "top"  , cutloose , var , dosf)
    h_loose_w    = get_histogram(samples, "w"    , cutloose , var , dosf)
    h_loose_dy   = get_histogram(samples, "dy"   , cutloose , var , dosf)

    # Retrieve histograms
    h_tight_data = get_histogram(samples, "data" , cuttight , var , dosf)
    h_tight_top  = get_histogram(samples, "top"  , cuttight , var , dosf)
    h_tight_w    = get_histogram(samples, "w"    , cuttight , var , dosf)
    h_tight_dy   = get_histogram(samples, "dy"   , cuttight , var , dosf)

    # Get total ewk
    h_loose_ewk = p.get_total_hist([h_loose_top, h_loose_dy, h_loose_w])
    h_tight_ewk = p.get_total_hist([h_tight_top, h_tight_dy, h_tight_w])

    # Get data - ewk
    h_loose_data.Add(h_loose_ewk, -1)
    h_tight_data.Add(h_tight_ewk, -1)

    # Compute fakerate
    h_tight_data.Divide(h_loose_data)

    return h_tight_data


#___________________________________________________________________________
def plot_fakerate(cutloose, cuttight, var, dosf=False, options={}):

    # Setting variables to be used for option setting
    output_name = cutloose + "_" + var
    isvarbin = output_name.find("varbin") != -1
    divide_by_bin_width = isvarbin
    yaxis_log = isvarbin
    yaxis_range = [1e3, 1e10] if isvarbin else []
    ismu = cuttight.find("Mu") != -1

    # Options
    alloptions= {
                "ratio_range":[0.0,2.0 if ismu else 2.5],
                "legend_scalex": 1.0,
                "legend_scaley": 1.0,
                "legend_smart": True,
                "legend_alignment": "topleft",
                "output_name": "plots/{}_fakeratecomp.pdf".format(output_name),
                "bkg_sort_method": "unsorted",
                "divide_by_bin_width": divide_by_bin_width,
                "yaxis_log": yaxis_log,
                "yaxis_range": yaxis_range,
                "yaxis_label": "Fake rate",
                "legend_datalabel": "Data FR",
                "draw_points": True,
                }

    # Whatever the option passed through the argument can override anything
    alloptions.update(options)

    # Retrieve fake rate histograms
    h_data_cn_fakerate = get_datadriven_fakerate(samples_cn, cutloose, cuttight, var, dosf)
    h_data_up_fakerate = get_datadriven_fakerate(samples_up, cutloose, cuttight, var, dosf)
    h_data_dn_fakerate = get_datadriven_fakerate(samples_dn, cutloose, cuttight, var, dosf)

    # Compute error
    p.add_diff_to_error(h_data_cn_fakerate, h_data_up_fakerate, h_data_dn_fakerate)

    # Get QCD fake rate
    h_qcd_fakerate = get_qcd_fakerate(samples_cn, cutloose, cuttight, var, dosf)
    h_qcd_fakerate.SetName("QCD FR")

    # Plot!
    p.plot_hist(
            sigs = [],
            bgs  = [h_qcd_fakerate],
            data = h_data_cn_fakerate,
            colors = [2],
            options=alloptions)



if __name__ == "__main__":

    import multiprocessing

    jobs = []

    # Computing HLT
    jobs.append(multiprocessing.Process(target=hlt_prescale))
    jobs.append(multiprocessing.Process(target=compute_nvtx_reweighting))

    # Computing Nvtx reweighting function
    jobs.append(multiprocessing.Process(target=plot_stack, args=("OneMuTightEWKCR3NoNvtxRewgt", "nvtx")))
    jobs.append(multiprocessing.Process(target=plot_stack, args=("OneElTightEWKCR3NoNvtxRewgt", "nvtx")))
    jobs.append(multiprocessing.Process(target=plot_stack, args=("OneMuTightEWKCR3", "nvtx")))
    jobs.append(multiprocessing.Process(target=plot_stack, args=("OneElTightEWKCR3", "nvtx")))

    # Plotting MT variable
    jobs.append(multiprocessing.Process(target=plot_stack, args=("OneMuTightEWKCR", "MTOneLepFixed")))
    jobs.append(multiprocessing.Process(target=plot_stack, args=("OneElTightEWKCR", "MTOneLepFixed")))

    # Plotting measurement region with loose and tight
    jobs.append(multiprocessing.Process(target=plot_stack, args=("OneMuLoose", "lep_ptcorrcoarse_vs_etacoarse", True)))
    jobs.append(multiprocessing.Process(target=plot_stack, args=("OneElLoose", "lep_ptcorrcoarse_vs_etacoarse", True)))
    jobs.append(multiprocessing.Process(target=plot_stack, args=("OneMuTight", "lep_ptcorrcoarse_vs_etacoarse", True)))
    jobs.append(multiprocessing.Process(target=plot_stack, args=("OneElTight", "lep_ptcorrcoarse_vs_etacoarse", True)))

    # Plotting the fakerate comparison between QCD and data
    jobs.append(multiprocessing.Process(target=plot_fakerate, args=("OneMuLoose", "OneMuTight", "lep_ptcorrcoarse_vs_etacoarse", True)))
    jobs.append(multiprocessing.Process(target=plot_fakerate, args=("OneElLoose", "OneElTight", "lep_ptcorrcoarse_vs_etacoarse", True)))

    # Plotting some closure plots
    jobs.append(multiprocessing.Process(target=plot_closure, args=("TwoMuLoosePredict", "mu_yield")))
    jobs.append(multiprocessing.Process(target=plot_closure, args=("TwoMuLoosePredict", "Mjj_mu")))
    jobs.append(multiprocessing.Process(target=plot_closure, args=("TwoMuLoosePredict", "Mll_mu")))
    jobs.append(multiprocessing.Process(target=plot_closure, args=("TwoMuLoosePredict", "MET_mu")))
    jobs.append(multiprocessing.Process(target=plot_closure, args=("TwoMuLoosePredict", "nb_mu")))
    jobs.append(multiprocessing.Process(target=plot_closure, args=("TwoMuLoosePredict", "nj30_mu")))
    jobs.append(multiprocessing.Process(target=plot_closure, args=("TwoMuLoosePredictBVeto", "mu_yield")))
    jobs.append(multiprocessing.Process(target=plot_closure, args=("TwoMuLoosePredictBVeto", "Mjj_mu")))
    jobs.append(multiprocessing.Process(target=plot_closure, args=("TwoMuLoosePredictBVeto", "Mll_mu")))
    jobs.append(multiprocessing.Process(target=plot_closure, args=("TwoMuLoosePredictBVeto", "MET_mu")))
    jobs.append(multiprocessing.Process(target=plot_closure, args=("TwoMuLoosePredictBVeto", "nb_mu")))
    jobs.append(multiprocessing.Process(target=plot_closure, args=("TwoMuLoosePredictBVeto", "nj30_mu")))
    jobs.append(multiprocessing.Process(target=plot_closure, args=("TwoElLoosePredictComb", "el_yield")))
    jobs.append(multiprocessing.Process(target=plot_closure, args=("TwoElLoosePredictComb", "Mjj_el")))
    jobs.append(multiprocessing.Process(target=plot_closure, args=("TwoElLoosePredictComb", "Mll_el")))
    jobs.append(multiprocessing.Process(target=plot_closure, args=("TwoElLoosePredictComb", "MET_el")))
    jobs.append(multiprocessing.Process(target=plot_closure, args=("TwoElLoosePredictComb", "nb_el")))
    jobs.append(multiprocessing.Process(target=plot_closure, args=("TwoElLoosePredictComb", "nj30_el")))
    jobs.append(multiprocessing.Process(target=plot_closure, args=("TwoElLoosePredictBVetoComb", "el_yield")))
    jobs.append(multiprocessing.Process(target=plot_closure, args=("TwoElLoosePredictBVetoComb", "Mjj_el")))
    jobs.append(multiprocessing.Process(target=plot_closure, args=("TwoElLoosePredictBVetoComb", "Mll_el")))
    jobs.append(multiprocessing.Process(target=plot_closure, args=("TwoElLoosePredictBVetoComb", "MET_el")))
    jobs.append(multiprocessing.Process(target=plot_closure, args=("TwoElLoosePredictBVetoComb", "nb_el")))
    jobs.append(multiprocessing.Process(target=plot_closure, args=("TwoElLoosePredictBVetoComb", "nj30_el")))

    # Multi-thread processing
    for job in jobs:
        job.start()

    for job in jobs:
        job.join()
