#!/bin/env python

import os
import sys
import ROOT
from QFramework import TQSampleFolder, TQXSecParser, TQCut, TQAnalysisSampleVisitor, TQSampleInitializer, TQCutflowAnalysisJob, TQCutflowPrinter, TQHistoMakerAnalysisJob
from rooutil.qutils import *
from errors import E
ROOT.gROOT.SetBatch(True)

########################################################################################
def getWZNF(samples, cutname):
    wz = samples.getCounter("/typebkg/lostlep", cutname)
    nf = samples.getCounter("/data-typebkg/[qflip+photon+prompt+fakes]-sig", cutname)
    nf.divide(wz)
    return nf.getCounter(), nf.getError()

########################################################################################
def applyWZNF(samples, cutnamesource, cutnametarget):
    wz = samples.getCounter("/typebkg/lostlep", cutnamesource)
    nf = samples.getCounter("/data-typebkg/[qflip+photon+prompt+fakes]-sig", cutnamesource)
    nf.divide(wz)
    samples.setScaleFactor(cutnametarget, nf.getCounter(), nf.getError(), "/typebkg/lostlep")

########################################################################################
def applyttWNF(samples, cutnamesource, cutnametarget):
    ttw = samples.getCounter("/typebkg/?/ttW", cutnamesource)
    nf = samples.getCounter("/data-typebkg/?/[ttZ+WZ+VBSWW+Other]-sig", cutnamesource)
    nf.divide(ttw)
    samples.setScaleFactor(cutnametarget, nf.getCounter(), nf.getError(), "/typebkg/?/ttW")

if __name__ == "__main__":

    # Open output
    samples = TQSampleFolder.loadSampleFolder("output.root:samples")

    # Signal region
    applyWZNF(samples, "WZCRSSeeFull", "SRSSeeFull")
    applyWZNF(samples, "WZCRSSemFull", "SRSSemFull")
    applyWZNF(samples, "WZCRSSmmFull", "SRSSmmFull")
    applyWZNF(samples, "WZCRSSeeFull", "SideSSeeFull")
    applyWZNF(samples, "WZCRSSemFull", "SideSSemFull")
    applyWZNF(samples, "WZCRSSmmFull", "SideSSmmFull")
    applyWZNF(samples, "WZCR1SFOSFull", "SR0SFOSFull")
    applyWZNF(samples, "WZCR1SFOSFull", "SR1SFOSFull")
    applyWZNF(samples, "WZCR2SFOSFull", "SR2SFOSFull")

    applyWZNF(samples, "WZCRSSeeFull", "SRSSeeFullFakeUp")
    applyWZNF(samples, "WZCRSSemFull", "SRSSemFullFakeUp")
    applyWZNF(samples, "WZCRSSmmFull", "SRSSmmFullFakeUp")
    applyWZNF(samples, "WZCRSSeeFull", "SideSSeeFullFakeUp")
    applyWZNF(samples, "WZCRSSemFull", "SideSSemFullFakeUp")
    applyWZNF(samples, "WZCRSSmmFull", "SideSSmmFullFakeUp")
    applyWZNF(samples, "WZCR1SFOSFull", "SR0SFOSFullFakeUp")
    applyWZNF(samples, "WZCR1SFOSFull", "SR1SFOSFullFakeUp")
    applyWZNF(samples, "WZCR2SFOSFull", "SR2SFOSFullFakeUp")

    applyWZNF(samples, "LMETWZCRSSeeFull", "LMETCRSSeeFull")
    applyWZNF(samples, "LMETWZCRSSemFull", "LMETCRSSemFull")
    applyWZNF(samples, "LMETWZCRSSmmFull", "LMETCRSSmmFull")

    applyttWNF(samples, "TTWCRSSeePre", "BTCRSSeeFull")
    applyttWNF(samples, "TTWCRSSemPre", "BTCRSSemFull")
    applyttWNF(samples, "TTWCRSSmmPre", "BTCRSSmmFull")
    applyttWNF(samples, "TTWCRSSeePre", "BTCRSideSSeeFull")
    applyttWNF(samples, "TTWCRSSemPre", "BTCRSideSSemFull")
    applyttWNF(samples, "TTWCRSSmmPre", "BTCRSideSSmmFull")
    applyttWNF(samples, "TTWCRSSeePre", "BTCRSSeePre")
    applyttWNF(samples, "TTWCRSSemPre", "BTCRSSemPre")
    applyttWNF(samples, "TTWCRSSmmPre", "BTCRSSmmPre")

    # Write the files with scale factors applied
    samples.writeToFile("output_sf_applied.root", True)
