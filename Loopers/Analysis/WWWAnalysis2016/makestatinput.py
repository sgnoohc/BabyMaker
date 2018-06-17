#!/bin/env python

import os
import sys
import ROOT
from QFramework import TQSampleFolder, TQXSecParser, TQCut, TQAnalysisSampleVisitor, TQSampleInitializer, TQCutflowAnalysisJob, TQCutflowPrinter, TQHistoMakerAnalysisJob
from rooutil.qutils import *
from errors import E
from cuts import systvars
import math

ROOT.gROOT.SetBatch(True)

def apply_lostlep_syst(th1, isup):
    systs = [0.1350, 0.0840, 0.1099, 0.0892, 0.1025, 0.0769, 0.1227, 0.1090, 0.1094]
    for index, syst in enumerate(systs):
        if isup:
            th1.SetBinContent(index + 1, th1.GetBinContent(index + 1) * (1 + syst))
        else:
            th1.SetBinContent(index + 1, th1.GetBinContent(index + 1) * (1 - syst))

def main():

    filename = "output_sf_applied.root"
    samples = TQSampleFolder.loadSampleFolder("{}:samples".format(filename))

    histname = "{SRSSeeFull,SRSSemFull,SRSSmmFull,SideSSeeFull,SideSSemFull,SideSSmmFull,SR0SFOSFull,SR1SFOSFull,SR2SFOSFull}"

    processes = [ "vbsww" , "ttw" , "lostlep" , "photon" , "qflip" , "prompt" , "fake" , "www" ,]

    sampledirpaths = {
            "vbsww"   : "/typebkg/?/VBSWW",
            "ttw"     : "/typebkg/?/ttW",
            "lostlep" : "/typebkg/lostlep/[ttZ+WZ+Other]",
            "photon"  : "/typebkg/photon/[ttZ+WZ+Other]",
            "qflip"   : "/typebkg/qflip/[ttZ+WZ+Other]",
            "prompt"  : "/typebkg/prompt/[ttZ+WZ+Other]",
            "fake"    : "/fake",
            "www"     : "/sig",
            }

    # Create output file
    ofile = ROOT.TFile("hist.root", "recreate")
    ofile.cd()

    rates = {}

    # Write histograms
    for process in processes:
        #print process, histname

        # Get nominal histogram
        h_nom = samples.getHistogram(sampledirpaths[process], histname).Clone(process)

        # Write nominal histogram
        h_nom.Write()

        rates[process] = h_nom.Integral()

        # Nominal histogram errors are needed to be varied one by one to create an effective uncorrelated histograms
        for i in xrange(len(histname.split(","))):
            ibin = i + 1
            h_statvarup   = h_nom.Clone(process + "_" + process + "_stat" + str(ibin) + "Up")
            h_statvardown = h_nom.Clone(process + "_" + process + "_stat" + str(ibin) + "Down")
            bc = h_statvarup.GetBinContent(ibin)
            be = h_statvarup.GetBinError(ibin)
            varup   = max(bc + be, 1e-6)
            vardown = max(bc - be, 1e-6)
            h_statvarup  .SetBinContent(ibin, varup)
            h_statvardown.SetBinContent(ibin, vardown)
            h_statvarup  .Write()
            h_statvardown.Write()

        # Write systematic histograms
        for systvar in systvars:
            #print systvar
            samples.getHistogram(sampledirpaths[process], histname.replace("Full", "Full" + systvar)).Clone(process + "_" + systvar).Write()

        if process == "lostlep":
            lostlep_syst_up   = h_nom.Clone(process + "_LostLepSystUp")
            lostlep_syst_down = h_nom.Clone(process + "_LostLepSystDown")
            apply_lostlep_syst(lostlep_syst_up, True)
            apply_lostlep_syst(lostlep_syst_down, False)
            lostlep_syst_up.Write()
            lostlep_syst_down.Write()


    # Write data histogram
    h_data = samples.getHistogram("/data", histname).Clone("data_obs")
    h_data.Reset() # to blind
    h_data.Write()

    for process in processes:
        print process, rates[process]

    ofile.Close()

if __name__ == "__main__":

    main()
