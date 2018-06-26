#!/bin/env python

ntuplepath = "/nfs-7/userdata/phchang/WWW_babies/WWW_v1.2.1/skim/"

#########################################################################################

import os
import sys
import ROOT
from QFramework import TQSampleFolder, TQXSecParser, TQCut, TQAnalysisSampleVisitor, TQSampleInitializer, TQCutflowAnalysisJob, TQCutflowPrinter, TQHistoMakerAnalysisJob, TQHWWPlotter, TQEventlistAnalysisJob
from rooutil.qutils import *
sys.path.append("..")
from cuts import *

def main(samples, sample_to_run, extra_args):

    index = int(extra_args[0])

    sample_to_run_prefix = sample_to_run.replace("/","-")

    isparallel = (sample_to_run != "")

    #
    #
    # Define cuts
    #
    #
    if index ==-1: cuts = getWWWAnalysisCuts()
    if index == 0: cuts = getWWWAnalysisCuts()
    if index == 1: cuts = getWWWAnalysisCuts(jecvar_suffix="_up")
    if index == 2: cuts = getWWWAnalysisCuts(jecvar_suffix="_dn")

    #
    #
    # Define histograms
    #
    #
    histojob_filename = ".histo.{}.cfg".format(sample_to_run_prefix)
    f = open(histojob_filename, "w")
    f.write("""
    TH1F('MllSS' , '' , 180 , 0. , 300.) << (MllSS : '\#it{m}_{ll} [GeV]');
    #@*/*: MllSS;

    TH1F('MllSS_wide' , '' , 180 , 0. , 2000.) << (MllSS : '\#it{m}_{ll} [GeV]');
    #@*/*: MllSS_wide;

    TH1F('MllZ' , '' , 180 , 60. , 120.) << (MllSS : '\#it{m}_{ll} [GeV]');
    #@*/*: MllZ;

    TH1F('MllZZoom' , '' , 180 , 80. , 100.) << (MllSS : '\#it{m}_{ll} [GeV]');
    #@*/*: MllZZoom;

    TH1F('M3l' , '' , 180 , 0. , 150.) << (M3l : '\#it{m}_{lll} [GeV]');
    #@*/*: M3l;

    TH1F('Pt3lGCR' , '' , 180 , 0. , 100.) << (Pt3l : '\#it{p}_{T,lll} [GeV]');
    #@*/*: Pt3lGCR;

    TH1F('Pt3l' , '' , 180 , 0. , 300.) << (Pt3l : '\#it{p}_{T,lll} [GeV]');
    #@*/*: Pt3l;

    TH1F('Ptll' , '' , 180 , 0. , 300.) << (Pt3l : '\#it{p}_{T,lll} [GeV]');
    #@*/*: Ptll;

    TH1F('nvtx' , '' , 60 , 0. , 60. ) << (nVert : 'Nvtx');
    #@*/*: nvtx;

    TH1F('Mjj' , '' , 180 , 0. , 300.) << (Mjj : '\#it{m}_{jj} [GeV]');
    #@*/*: Mjj;

    TH1F('MjjL' , '' , 180 , 0. , 750.) << (MjjL : '\#it{m}_{jj,central,leading} [GeV]');
    #@*/*: MjjL;

    TH1F('DetajjL' , '' , 180 , 0. , 5.) << (DetajjL : '\#it{m}_{jj,central,leading} [GeV]');
    #@*/*: DetajjL;

    TH1F('MjjVBF' , '' , 180 , 0. , 750.) << (MjjVBF : '\#it{m}_{jj,central,leading} [GeV]');
    #@*/*: MjjVBF;

    TH1F('DetajjVBF' , '' , 180 , 0. , 8.) << (DetajjVBF : '\#it{m}_{jj,central,leading} [GeV]');
    #@*/*: DetajjVBF;

    TH1F('MET' , '' , 180 , 0. , 180.) << (met_pt : 'MET [GeV]');
    #@*/*: MET;

    TH2F('lep0_pt_vs_eta' , '' , {0, 0.9, 1.6, 1.9, 2.4}, {20, 30, 40, 50, 60, 70, 150, 2000} ) << (lep_eta[0] : '\#eta_{lead-lep}', lep_pt[0] : '\#it{p}_{T, lead-lep} [GeV]');
    #@*/*: lep0_pt_vs_eta;

    TH2F('lep1_pt_vs_eta' , '' , {0, 0.9, 1.6, 1.9, 2.4}, {20, 30, 40, 50, 60, 70, 150, 2000} ) << (lep_eta[1] : '\#eta_{trail-lep}', lep_pt[1] : '\#it{p}_{T, trail-lep} [GeV]');
    #@*/*: lep1_pt_vs_eta;

    TH1F('lep_pt0' , '' , 180 , 0. , 250 ) << (lep_pt[0] : '\#it{p}_{T, lead-lep} [GeV]');
    #@*/*: lep_pt0;

    TH1F('lep_pt1' , '' , 180 , 0. , 150 ) << (lep_pt[1] : '\#it{p}_{T, trail-lep} [GeV]');
    #@*/*: lep_pt1;

    #TH1F('lep_pt2' , '' , 180 , 0. , 150 ) << (lep_pt[2] : '\#it{p}_{T, trail-lep} [GeV]');
    ##@*/*: lep_pt1;

    TH1F('lep_eta0' , '' , 180 , -2.5 , 2.5 ) << (lep_eta[0] : '\#eta_{lead-lep}');
    #@*/*: lep_eta0;

    TH1F('lep_eta1' , '' , 180 , -2.5 , 2.5 ) << (lep_eta[1] : '\#eta_{trail-lep}');
    #@*/*: lep_eta1;

    TH1F('lep_phi0' , '' , 180 , -3.1416 , 3.1416 ) << (lep_phi[0] : '\#phi_{lead-lep}');
    #@*/*: lep_phi0;

    TH1F('lep_phi1' , '' , 180 , -3.1416, 3.1416 ) << (lep_phi[1] : '\#phi_{trail-lep}');
    #@*/*: lep_phi1;

    TH1F('lep_relIso03EAv2Lep0' , '' , 180 , 0.0 , 0.2 ) << (lep_relIso03EAv2Lep[0] : 'I_{R=0.3,EA,Lep, lead-lep}');
    #@*/*: lep_relIso03EAv2Lep0;

    TH1F('lep_relIso03EAv2Lep1' , '' , 180 , 0.0 , 0.2 ) << (lep_relIso03EAv2Lep[1] : 'I_{R=0.3,EA,Lep, trail-lep}');
    #@*/*: lep_relIso03EAv2Lep1;

    TH1F('lep_relIso03EAv2Lep2' , '' , 180 , 0.0 , 0.2 ) << (lep_relIso03EAv2Lep[2] : 'I_{R=0.3,EA,Lep, trail-lep}');
    #@*/*: lep_relIso03EAv2Lep2;

    #TH1F('nj' , '' , 7 , 0. , 7. ) << (nj : 'N_{jet}');
    #@*/*: nj;

    #TH1F('nj30' , '' , 7 , 0. , 7. ) << (nj30 : 'N_{jet}');
    #@*/*: nj30;

    #TH1F('nb' , '' , 5 , 0. , 5. ) << (nb : 'N_{b-jet}');
    #@*/*: nb;

    TH1F('jets_pt0' , '' , 180 , 0. , 250 ) << (jets_p4[0].pt() : '\#it{p}_{T, lead-jet} [GeV]');
    #@*/*: jets_pt0;

    TH1F('jets_pt1' , '' , 180 , 0. , 150 ) << (jets_p4[1].pt() : '\#it{p}_{T, trail-jet} [GeV]');
    #@*/*: jets_pt1;

    TH1F('jets_eta0' , '' , 180 , -5.0 , 5.0 ) << (jets_p4[0].eta() : '\#eta_{lead-jet}');
    #@*/*: jets_eta0;

    TH1F('jets_eta1' , '' , 180 , -5.0 , 5.0 ) << (jets_p4[1].eta() : '\#eta_{trail-jet}');
    #@*/*: jets_eta1;

    TH1F('jets_phi0' , '' , 180 , -3.1416, 3.1416 ) << (jets_p4[0].phi() : '\#phi_{lead-jet}');
    #@*/*: jets_phi0;

    TH1F('jets_phi1' , '' , 180 , -3.1416, 3.1416 ) << (jets_p4[1].phi() : '\#phi_{trail-jet}');
    #@*/*: jets_phi1;

    TH1F('MTmax3L' , '' , 180 , 0. , 300.) << ([MTMax3L] : '\#it{m}_{T,max} [GeV]');
    #@*/*: MTmax3L;

    TH1F('MT3rd' , '' , 180 , 0. , 300.) << (MT3rd : '\#it{m}_{T,3rd} [GeV]');
    #@*/*: MT3rd;

    TH1F('Mlvlvjj' , '' , 180 , 0. , 1000.) << ([MTlvlvjj] : '\#it{m}_{lvlvjj} [GeV]');
    #@*/*: Mlvlvjj;

    TH1F('Mlvlvjj_wide' , '' , 180 , 0. , 3000.) << ([MTlvlvjj] : '\#it{m}_{lvlvjj} [GeV]');
    #@*/*: Mlvlvjj_wide;

    TH1F('MTlvlv' , '' , 180 , 0. , 1000.) << ([MTlvlv] : '\#it{m}_{T,lvlv} [GeV]');
    #@*/*: MTlvlv;

    @SRSSeeFull/*: MllSS_wide, MTlvlv, Mjj, Mlvlvjj_wide;
    @SRSSemFull/*: MllSS_wide, MTlvlv, Mjj, Mlvlvjj_wide;
    @SRSSmmFull/*: MllSS_wide, MTlvlv, Mjj, Mlvlvjj_wide;
    @SideSSeeFull/*: MllSS_wide, MTlvlv, Mjj, Mlvlvjj_wide;
    @SideSSemFull/*: MllSS_wide, MTlvlv, Mjj, Mlvlvjj_wide;
    @SideSSmmFull/*: MllSS_wide, MTlvlv, Mjj, Mlvlvjj_wide;
    @SR0SFOSFull/* :MllSS_wide, MTlvlv;
    @SR1SFOSFull/* :MllSS_wide, MTlvlv;
    @SR2SFOSFull/* :MllSS_wide, MTlvlv;

    """)
    f.close()

    #
    #
    # Book Analysis Jobs (Histogramming, Cutflow, Event lists, etc.)
    #
    #
    histojob = TQHistoMakerAnalysisJob()
    histojob.importJobsFromTextFiles(histojob_filename, cuts, "*", True if not isparallel else False)

    # Analysis jobs
    cutflowjob = TQCutflowAnalysisJob("cutflow")
    cuts.addAnalysisJob(cutflowjob, "*")

    # Eventlist jobs (use this if we want to print out some event information in a text format e.g. run, lumi, evt or other variables.)
    eventlistjob = TQEventlistAnalysisJob("eventlist")
    eventlist_filename = ".eventlist.{}.cfg".format(sample_to_run_prefix)
    f = open(eventlist_filename, "w")
    f.write("""
    lepton: run << run, lumi << lumi, evt << evt;
    @SRSSeeFull: lepton;
    @SRSSemFull: lepton;
    @SRSSmmFull: lepton;
    @SideSSeeFull: lepton;
    @SideSSemFull: lepton;
    @SideSSmmFull: lepton;
    @SR0SFOSFull: lepton;
    @SR1SFOSFull: lepton;
    @SR2SFOSFull: lepton;
    """)
    f.close()
    eventlistjob.importJobsFromTextFiles(eventlist_filename, cuts, "*", True if not isparallel else False)

    #
    #
    # Add custom tqobservable that can do more than just string based draw statements
    #
    #
    from QFramework import TQObservable, TQWWWMTMax3L, TQWWWClosureEvtType, TQWWWVariables
    customobservables = {}
    customobservables["MTMax3L"] = TQWWWMTMax3L("")
    customobservables["MTMax3L_up"] = TQWWWMTMax3L("_up")
    customobservables["MTMax3L_dn"] = TQWWWMTMax3L("_dn")
    customobservables["MTlvlvjj"] = TQWWWVariables("MTlvlvjj")
    customobservables["MTlvlv"] = TQWWWVariables("MTlvlv")
    TQObservable.addObservable(customobservables["MTMax3L"], "MTMax3L")
    TQObservable.addObservable(customobservables["MTMax3L_up"], "MTMax3L_up")
    TQObservable.addObservable(customobservables["MTMax3L_dn"], "MTMax3L_dn")
    TQObservable.addObservable(customobservables["MTlvlvjj"], "MTlvlvjj")
    TQObservable.addObservable(customobservables["MTlvlv"], "MTlvlv")

    # Print cuts and numebr of booked analysis jobs for debugging purpose
    if not isparallel:
        cuts.printCut("trd")

    #
    #
    # Set object "generalization" (i.e. merging histograms)
    #
    #
    samples.getSampleFolder("/typebkg/prompt/Other").setTagBool(".asv.generalize.counter", True)
    samples.getSampleFolder("/typebkg/prompt/Other").setTagBool(".asv.generalize.histograms", True)
    samples.getSampleFolder("/typebkg/lostlep/Other").setTagBool(".asv.generalize.counter", True)
    samples.getSampleFolder("/typebkg/lostlep/Other").setTagBool(".asv.generalize.histograms", True)
    samples.getSampleFolder("/typebkg/qflip/Other").setTagBool(".asv.generalize.counter", True)
    samples.getSampleFolder("/typebkg/qflip/Other").setTagBool(".asv.generalize.histograms", True)
    samples.getSampleFolder("/typebkg/photon/Other").setTagBool(".asv.generalize.counter", True)
    samples.getSampleFolder("/typebkg/photon/Other").setTagBool(".asv.generalize.histograms", True)
    samples.getSampleFolder("/typebkg/fakes/Other").setTagBool(".asv.generalize.counter", True)
    samples.getSampleFolder("/typebkg/fakes/Other").setTagBool(".asv.generalize.histograms", True)

    #
    #
    # Loop over the samples
    #
    #

    # setup a visitor to actually loop over ROOT files
    vis = TQAnalysisSampleVisitor(cuts, True)

    # Run the job!
    if sample_to_run:
        samples.visitSampleFolders(vis, "{}".format(sample_to_run))
    else:
        samples.visitSampleFolders(vis)

    # Write the output histograms and cutflow cut values and etc.
    prefix = "output"
    if sample_to_run: prefix = ".output_{}".format(sample_to_run_prefix)
    if index == 0: samples.writeToFile("{}_normal.root".format(prefix), True)
    if index == 1: samples.writeToFile("{}_jec_up.root".format(prefix), True)
    if index == 2: samples.writeToFile("{}_jec_dn.root".format(prefix), True)

    os.system("rm {}".format(eventlist_filename))
    os.system("rm {}".format(histojob_filename))

def addBSMsamples(samples):

    #
    #
    # Connect bsm samples
    #
    #

    header_str = "SampleID , path , priority , usemcweights , treename , usefakeweight , variation"

    # Wprime sample
    wprimemasses = [600,800,1000,1200,1400,1600,1800,2000,2500,3500,4000,4500,5000,5500,6000]
    config_strs = [header_str]
    for wprimemass in wprimemasses:
        config_strs.append("wprime_m{mass}_*, /bsm/wprime/{mass}, -2, true, t_ss, false, nominal".format(mass=wprimemass))

    # Doubly charged higgs samples
    hpmpmmasses = [200,300,400,500,600,900,1000,1500,2000]
    for hpmpmmass in hpmpmmasses:
        config_strs.append("hpmpm_m{mass}_*, /bsm/hpmpm/{mass}, -2, true, t_ss, false, nominal".format(mass=hpmpmmass))

    # SUSY c1n2->WH + LSPs samples
    chimasses = [125 + i*25 for i in xrange(13) ]
    for chimass in chimasses:
        # The LSP mass scans are defined as the following
        lspmasses = [ i*25 for i in xrange(((chimass - 125) / 25) + 1) ]
        if len(lspmasses) > 1:
            lspmasses[0] = lspmasses[0] + 1
            lspmasses[-1] = lspmasses[-1] - 1
        else:
            lspmasses[0] = lspmasses[0] + 1
        if chimass == 125: chimass = 127
        for lspmass in lspmasses:
            config_strs.append("whsusy_fullscan*, /bsm/whsusy/{mchi}/{mlsp}, -2, true, t_ss, false, nominal".format(mchi=chimass, mlsp=lspmass))

    # Add BSM samples
    config_filename = ".temp.{}.samples.cfg".format(os.getpid())
    addNtuples(samples, "\n".join(config_strs), ntuplepath, config_filename)

    # For SUSY samples, set mchi and mlsp tag
    chimasses = [125 + i*25 for i in xrange(13) ]
    for chimass in chimasses:
        # The LSP mass scans are defined as the following
        lspmasses = [ i*25 for i in xrange(((chimass - 125) / 25) + 1) ]
        if len(lspmasses) > 1:
            lspmasses[0] = lspmasses[0] + 1
            lspmasses[-1] = lspmasses[-1] - 1
        else:
            lspmasses[0] = lspmasses[0] + 1
        if chimass == 125: chimass = 127
        for lspmass in lspmasses:
            samples.getSampleFolder("/bsm/whsusy/{}/{}".format(chimass, lspmass)).setTagInteger("mchi", chimass)
            samples.getSampleFolder("/bsm/whsusy/{}/{}".format(chimass, lspmass)).setTagInteger("mlsp", lspmass)

    os.system(config_filename)

if __name__ == "__main__":

    if len(sys.argv) < 2:
        print "Usage:"
        print "  python {} INDEX [SAMPLE]".format(sys.argv[0])
        print ""
        print "  INDEX determines which variation to run"
        print " -1 : print cuts and samples and exit"
        print "  0 : nominal"
        print "  1 : jec_up"
        print "  2 : jec_dn"
        print ""
        sys.exit()

    # Create the master TQSampleFolder
    samples = TQSampleFolder("samples")

    # Connect input baby ntuple
    connectNtuples(samples, "../samples.cfg", ntuplepath, "<-1")

    # Add BSM samples
    addBSMsamples(samples)

    if len(sys.argv) >= 3:
        # Run single job
        main(samples, str(sys.argv[2]), [int(sys.argv[1])])
    else:
        # Run parallel jobs
        runParallel(16, main, samples, [sys.argv[1]])
        if int(sys.argv[1]) == 0: os.system("python rooutil/qframework/share/tqmerge -o output.root -t analysis .output_-*normal.root")
        if int(sys.argv[1]) == 1: os.system("python rooutil/qframework/share/tqmerge -o output_jec_up.root -t analysis .output_-*jec_up.root")
        if int(sys.argv[1]) == 2: os.system("python rooutil/qframework/share/tqmerge -o output_jec_dn.root -t analysis .output_-*jec_dn.root")
        os.system("rm .output_-*")
        os.system("rm .temp.*")

