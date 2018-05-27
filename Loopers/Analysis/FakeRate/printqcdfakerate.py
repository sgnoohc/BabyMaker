#!/bin/env python

import os
import sys
import ROOT
from QFramework import TQSampleFolder, TQXSecParser, TQCut, TQAnalysisSampleVisitor, TQSampleInitializer, TQCutflowAnalysisJob, TQCutflowPrinter, TQHistoMakerAnalysisJob
from rooutil import plottery_wrapper as p
from plottery import plottery as ply
from rooutil.syncfiles.pyfiles.errors import E

def compute_fake_factor(th2):
    for ix in xrange(0, th2.GetNbinsX()+2):
        for iy in xrange(0, th2.GetNbinsY()+2):
            frnom = th2.GetBinContent(ix, iy)
            frerr = th2.GetBinError(ix, iy)
            fr = E(frnom, frerr) 
            if fr.val != 0 and fr.val != 1:
                ff = fr / (E(1., 0.) - fr)
            else:
                ff = E(0., 0.)
            th2.SetBinContent(ix, iy, ff.val)
            th2.SetBinError(ix, iy, ff.err)

def compute_fake_factor_1d(th1):
    for ix in xrange(0, th1.GetNbinsX()+2):
        frnom = th1.GetBinContent(ix)
        frerr = th1.GetBinError(ix)
        fr = E(frnom, frerr) 
        if fr.val != 0 and fr.val != 1:
            ff = fr / (E(1., 0.) - fr)
        else:
            ff = E(0., 0.)
        th1.SetBinContent(ix, ff.val)
        th1.SetBinError(ix, ff.err)

ROOT.gROOT.SetBatch(True)
samples = TQSampleFolder.loadSampleFolder("output.root:samples")

qcdloosemu = samples.getHistogram("/qcd/mu", "OneMuLoose/lep_ptcorrcoarse_vs_etacoarse")
qcdtightmu = samples.getHistogram("/qcd/mu", "OneMuTight/lep_ptcorrcoarse_vs_etacoarse")

qcdlooseel = samples.getHistogram("/qcd/el", "OneElLoose/lep_ptcorrcoarse_vs_etacoarse")
qcdtightel = samples.getHistogram("/qcd/el", "OneElTight/lep_ptcorrcoarse_vs_etacoarse")

qcdlooseelEM = samples.getHistogram("/qcd/el/EM", "OneElLoose/lep_ptcorrcoarse_vs_etacoarse")
qcdtightelEM = samples.getHistogram("/qcd/el/EM", "OneElTight/lep_ptcorrcoarse_vs_etacoarse")

qcdlooseelbcToE = samples.getHistogram("/qcd/el/bcToE", "OneElLoose/lep_ptcorrcoarse_vs_etacoarse")
qcdtightelbcToE = samples.getHistogram("/qcd/el/bcToE", "OneElTight/lep_ptcorrcoarse_vs_etacoarse")

qcdlooseelEM1D = samples.getHistogram("/qcd/el/EM", "OneElLoose/lep_ptcorrvarbincoarse")
qcdtightelEM1D = samples.getHistogram("/qcd/el/EM", "OneElTight/lep_ptcorrvarbincoarse")

qcdtightmu.Divide(qcdloosemu)
compute_fake_factor(qcdtightmu)

qcdtightel.Divide(qcdlooseel)
compute_fake_factor(qcdtightel)

qcdtightelEM.Divide(qcdlooseelEM)
compute_fake_factor(qcdtightelEM)

qcdtightelbcToE.Divide(qcdlooseelbcToE)
compute_fake_factor(qcdtightelbcToE)

qcdtightelEM1D.Divide(qcdlooseelEM1D)
qcdtightelEM1D.Print("all")
compute_fake_factor_1d(qcdtightelEM1D)
qcdtightelEM1D.Print("all")

f = ROOT.TFile("qcd_fakerates.root", "recreate")
qcdtightmu.SetName("qcdmu")
qcdtightmu.Write()
qcdtightel.SetName("qcdel")
qcdtightel.Write()
qcdtightelEM.SetName("qcdelEM")
qcdtightelEM.Write()
qcdtightelbcToE.SetName("qcdelbcToE")
qcdtightelbcToE.Write()
qcdtightelEM1D.SetName("qcdelEM1D")
qcdtightelEM1D.Write()
