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

def main(model="sm", mass0=-1, mass1=-1):

    print model, mass0, mass1

    suffix = model
    if int(mass0) > 0: suffix += "_{}".format(mass0)
    if int(mass1) > 0: suffix += "_{}".format(mass1)

    try:
        os.makedirs('statinputs')
    except OSError as exc:  # Python >2.5
        if exc.errno == errno.EEXIST and os.path.isdir('statinputs'):
            pass
        else:
            raise

    filename = "output_sf_applied.root"
    samples = TQSampleFolder.loadSampleFolder("{}:samples".format(filename))
    samples_jec_up = TQSampleFolder.loadSampleFolder("output_jec_up.root:samples")
    samples_jec_dn = TQSampleFolder.loadSampleFolder("output_jec_dn.root:samples")

    histname = "{SRSSeeFull,SRSSemFull,SRSSmmFull,SideSSeeFull,SideSSemFull,SideSSmmFull,SR0SFOSFull,SR1SFOSFull,SR2SFOSFull}"
    if model == "hpmpm":
        histname = "SRSSeeFull/MllSS+SRSSemFull/MllSS+SRSSmmFull/MllSS+SideSSeeFull/MllSS+SideSSemFull/MllSS+SideSSmmFull/MllSS"

    processes = [ "vbsww" , "ttw" , "lostlep" , "photon" , "qflip" , "prompt" , "fake" , "www" ,]

    sigmodel = "/sig"
    if model == "wprime": sigmodel = "/bsm/wprime/{}".format(mass0)
    if model == "hpmpm": sigmodel = "/bsm/hpmpm/{}".format(mass0)
    if model == "whsusy": sigmodel = "/bsm/whsusy/{}/{}".format(mass0, mass1)

    sampledirpaths = {
            "vbsww"   : "/typebkg/?/VBSWW",
            "ttw"     : "/typebkg/?/ttW",
            "lostlep" : "/typebkg/lostlep/[ttZ+WZ+Other]",
            "photon"  : "/typebkg/photon/[ttZ+WZ+Other]",
            "qflip"   : "/typebkg/qflip/[ttZ+WZ+Other]",
            "prompt"  : "/typebkg/prompt/[ttZ+WZ+Other]" if model == "sm" else "/typebkg/prompt/[ttZ+WZ+Other]+sig",
            "fake"    : "/fake",
            "www"     : sigmodel,
            }

    print sigmodel

    # Create output file
    ofile = ROOT.TFile("statinputs/hist_{}.root".format(suffix), "recreate")
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

        # JEC systematic histograms
        samples_jec_up.getHistogram(sampledirpaths[process], histname).Clone(process + "_JECUp").Write()
        samples_jec_dn.getHistogram(sampledirpaths[process], histname).Clone(process + "_JECDown").Write()

        if process == "lostlep":
            lostlep_syst_up   = h_nom.Clone(process + "_LostLepSystUp")
            lostlep_syst_down = h_nom.Clone(process + "_LostLepSystDown")
            apply_lostlep_syst(lostlep_syst_up, True)
            apply_lostlep_syst(lostlep_syst_down, False)
            lostlep_syst_up.Write()
            lostlep_syst_down.Write()


    # Write data histogram
    h_data = samples.getHistogram("/data", histname).Clone("data_obs")
    # is blind for now
    h_data = samples.getHistogram("/fake+typebkg/prompt+typebkg/qflip+typebkg/photon+typebkg/lostlep", histname).Clone("data_obs")
    for i in xrange(h_data.GetNbinsX()):
        bc = h_data.GetBinContent(i+1)
        bc = int(bc)
        be = math.sqrt(bc)
        h_data.SetBinContent(i+1, bc)
        h_data.SetBinError(i+1, be)
    #h_data.Reset() # to blind
    h_data.Write()

    #print 'data', h_data.Integral()

    #for process in processes:
    #    print process, rates[process]

    datacard="""imax 1 number of bins
jmax * number of processes
kmax * number of nuisance parameters
----------------------------------------------------------------------------------------------------------------------------------
shapes * * statinputs/hist_{}.root $PROCESS $PROCESS_$SYSTEMATIC
----------------------------------------------------------------------------------------------------------------------------------
bin          SR
observation  {:.1f}
----------------------------------------------------------------------------------------------------------------------------------
bin                                     SR           SR           SR           SR           SR           SR           SR           SR
process                                 0            1            2            3            4            5            6            7
process                                 www          fake         photon       lostlep      qflip        prompt       ttw          vbsww
rate                                    {:<6.3f}       {:<6.3f}       {:<6.3f}       {:<6.3f}       {:<6.3f}       {:<6.3f}       {:<6.3f}       {:<6.3f}     
----------------------------------------------------------------------------------------------------------------------------------
JEC                     shape           1            -            1            -            1            1            1            1
LepSF                   shape           1            -            1            -            1            1            1            1
TrigSF                  shape           1            -            1            -            1            1            1            1
BTagHF                  shape           1            -            1            -            1            1            1            1
BTagLF                  shape           1            -            1            -            1            1            1            1
Pileup                  shape           1            -            1            -            1            1            1            1
FakeRateEl              shape           -            1            -            -            -            -            -            -
FakeRateMu              shape           -            1            -            -            -            -            -            -
FakeClosureEl           shape           -            1            -            -            -            -            -            -
FakeClosureMu           shape           -            1            -            -            -            -            -            -
LostLepSyst             lnN             -            -            -            1            -            -            -            -
LumSyst                 lnN             1.025        -            1.025        1.025        1.025        1.025        1.025        1.025
SigPDF                  lnN             0.990/1.010  -            -            -            -            -            -            -
SigQsq                  lnN             1.010/0.990  -            -            -            -            -            -            -
XSec                    lnN             1.06         -            -            -            -            -            -            -
vbsww_syst              lnN             -            -            -            -            -            -            -            1.30
ttw_syst                lnN             -            -            -            -            -            -            1.30         -
photon_syst             lnN             -            -            1.50         -            -            -            -            -
www_stat1               shape           1            -            -            -            -            -            -            -
www_stat2               shape           1            -            -            -            -            -            -            -
www_stat3               shape           1            -            -            -            -            -            -            -
www_stat4               shape           1            -            -            -            -            -            -            -
www_stat5               shape           1            -            -            -            -            -            -            -
www_stat6               shape           1            -            -            -            -            -            -            -
www_stat7               shape           1            -            -            -            -            -            -            -
www_stat8               shape           1            -            -            -            -            -            -            -
www_stat9               shape           1            -            -            -            -            -            -            -
fake_stat1              shape           -            1            -            -            -            -            -            -
fake_stat2              shape           -            1            -            -            -            -            -            -
fake_stat3              shape           -            1            -            -            -            -            -            -
fake_stat4              shape           -            1            -            -            -            -            -            -
fake_stat5              shape           -            1            -            -            -            -            -            -
fake_stat6              shape           -            1            -            -            -            -            -            -
fake_stat7              shape           -            1            -            -            -            -            -            -
fake_stat8              shape           -            1            -            -            -            -            -            -
fake_stat9              shape           -            1            -            -            -            -            -            -
photon_stat1            shape           -            -            1            -            -            -            -            -
photon_stat2            shape           -            -            1            -            -            -            -            -
photon_stat3            shape           -            -            1            -            -            -            -            -
photon_stat4            shape           -            -            1            -            -            -            -            -
photon_stat5            shape           -            -            1            -            -            -            -            -
photon_stat6            shape           -            -            1            -            -            -            -            -
photon_stat7            shape           -            -            1            -            -            -            -            -
photon_stat8            shape           -            -            1            -            -            -            -            -
photon_stat9            shape           -            -            1            -            -            -            -            -
lostlep_stat1           shape           -            -            -            1            -            -            -            -
lostlep_stat2           shape           -            -            -            1            -            -            -            -
lostlep_stat3           shape           -            -            -            1            -            -            -            -
lostlep_stat4           shape           -            -            -            1            -            -            -            -
lostlep_stat5           shape           -            -            -            1            -            -            -            -
lostlep_stat6           shape           -            -            -            1            -            -            -            -
lostlep_stat7           shape           -            -            -            1            -            -            -            -
lostlep_stat8           shape           -            -            -            1            -            -            -            -
lostlep_stat9           shape           -            -            -            1            -            -            -            -
qflip_stat1             shape           -            -            -            -            1            -            -            -
qflip_stat2             shape           -            -            -            -            1            -            -            -
qflip_stat3             shape           -            -            -            -            1            -            -            -
qflip_stat4             shape           -            -            -            -            1            -            -            -
qflip_stat5             shape           -            -            -            -            1            -            -            -
qflip_stat6             shape           -            -            -            -            1            -            -            -
qflip_stat7             shape           -            -            -            -            1            -            -            -
qflip_stat8             shape           -            -            -            -            1            -            -            -
qflip_stat9             shape           -            -            -            -            1            -            -            -
prompt_stat1            shape           -            -            -            -            -            1            -            -
prompt_stat2            shape           -            -            -            -            -            1            -            -
prompt_stat3            shape           -            -            -            -            -            1            -            -
prompt_stat4            shape           -            -            -            -            -            1            -            -
prompt_stat5            shape           -            -            -            -            -            1            -            -
prompt_stat6            shape           -            -            -            -            -            1            -            -
prompt_stat7            shape           -            -            -            -            -            1            -            -
prompt_stat8            shape           -            -            -            -            -            1            -            -
prompt_stat9            shape           -            -            -            -            -            1            -            -
ttw_stat1               shape           -            -            -            -            -            -            1            -
ttw_stat2               shape           -            -            -            -            -            -            1            -
ttw_stat3               shape           -            -            -            -            -            -            1            -
ttw_stat4               shape           -            -            -            -            -            -            1            -
ttw_stat5               shape           -            -            -            -            -            -            1            -
ttw_stat6               shape           -            -            -            -            -            -            1            -
ttw_stat7               shape           -            -            -            -            -            -            1            -
ttw_stat8               shape           -            -            -            -            -            -            1            -
ttw_stat9               shape           -            -            -            -            -            -            1            -
vbsww_stat1             shape           -            -            -            -            -            -            -            1
vbsww_stat2             shape           -            -            -            -            -            -            -            1
vbsww_stat3             shape           -            -            -            -            -            -            -            1
vbsww_stat4             shape           -            -            -            -            -            -            -            1
vbsww_stat5             shape           -            -            -            -            -            -            -            1
""".format(suffix, h_data.Integral(), rates["www"], rates["fake"], rates["photon"], rates["lostlep"], rates["qflip"], rates["prompt"], rates["ttw"], rates["vbsww"])

    #print datacard

    f = open('statinputs/datacard_{}.txt'.format(suffix), 'w')
    f.write(datacard)
    f.close()


    ofile.Close()

if __name__ == "__main__":

    def help():
        print "Usage:"
        print ""
        print "  python {} MODEL [MASS] [MASS-LSP]"
        print ""
        print "  MODEL = sm, wprime, hpmpm (doubly charged higgs), whsusy"
        print ""
        sys.exit()

    if len(sys.argv) < 2:
        help()
    else:
        main(*sys.argv[1:])
