#!/bin/env python

import os
import sys
import ROOT
from QFramework import TQSampleFolder, TQXSecParser, TQCut, TQAnalysisSampleVisitor, TQSampleInitializer, TQCutflowAnalysisJob, TQCutflowPrinter, TQHistoMakerAnalysisJob, TQHWWPlotter, TQEventlistAnalysisJob
from qutils import *

def main(index):

    #
    #
    # Create the master TQSampleFolder
    #
    #
    samples = TQSampleFolder("samples")

    #
    #
    # Connect input baby ntuple
    #
    #
    connectNtuples(samples, "samples.cfg", "/nfs-7/userdata/phchang/WWW_babies/WWW_v1.0.20/skim/", ">2")

    #
    #
    # Define cuts
    #
    #
    PreselCuts = [
    ["1"                                          , "evt_scale1fb"                  ] ,
    ["1"                                          , "purewgt"                       ] ,
    ["1"                                          , "{$(usefakeweight)?ffwgt:35.9}" ] ,
    ["Flag_AllEventFilters"                       , "1"                             ] ,
    ["vetophoton==0"                              , "1"                             ] ,
    ["lep_pdgId[0]*lep_pdgId[1]<0"                , "1"                             ] ,
    ["MllSS > 10"                                 , "1"                             ] ,
    ]
    PreselCutExpr, PreselWgtExpr = combexpr(PreselCuts)

    tqcuts = {}
    #tqcuts["Base"] = TQCut("Base", "Base", "(nVlep==2)*(nLlep==2)*(lep_relIso03EAv2[0]<0.06)*(lep_relIso03EAv2[1]<0.06)", "1")
    tqcuts["Base"] = TQCut("Base", "Base", "(nVlep==2)*(nLlep==2)*(nTlep==2)", "1")
    tqcuts["Presel"] = TQCut("Presel", "Presel", PreselCutExpr, PreselWgtExpr)
    tqcuts["CutOSee"] = TQCut("CutOSee" , "OS: ee" , "(lep_pdgId[0]*lep_pdgId[1]==-121)*(HLT_DoubleEl_DZ_2==1)" , "trigeff")
    tqcuts["CutOSem"] = TQCut("CutOSem" , "OS: em" , "(lep_pdgId[0]*lep_pdgId[1]==-143)*(HLT_MuEG==1)"          , "trigeff")
    tqcuts["CutOSmm"] = TQCut("CutOSmm" , "OS: mm" , "(lep_pdgId[0]*lep_pdgId[1]==-169)*(HLT_DoubleMu==1)"      , "trigeff")
    tqcuts["CutOSeeLepSF"] = TQCut("CutOSeeLepSF" , "OS: LepSF" , "1" , "lepsf")
    tqcuts["CutOSemLepSF"] = TQCut("CutOSemLepSF" , "OS: LepSF" , "1" , "lepsf")
    tqcuts["CutOSmmLepSF"] = TQCut("CutOSmmLepSF" , "OS: LepSF" , "1" , "lepsf")
    tqcuts["CutOSmmNvtxRewgt"] = TQCut("CutOSmmNvtxRewgt" , "OS: NvtxRewgt" , "1" , "TH1Map:nvtx_rewgt.root:nvtx([nVert])")

    cuts = tqcuts["Base"]
    tqcuts["Base"].addCut(tqcuts["Presel"])
    tqcuts["Presel"].addCut(tqcuts["CutOSee"])
    tqcuts["Presel"].addCut(tqcuts["CutOSem"])
    tqcuts["Presel"].addCut(tqcuts["CutOSmm"])
    tqcuts["CutOSee"].addCut(tqcuts["CutOSeeLepSF"])
    tqcuts["CutOSem"].addCut(tqcuts["CutOSemLepSF"])
    tqcuts["CutOSmm"].addCut(tqcuts["CutOSmmLepSF"])
    tqcuts["CutOSmmLepSF"].addCut(tqcuts["CutOSmmNvtxRewgt"])

    #
    #
    # Define histograms
    #
    #
    f = open(".histo.os.{}.cfg".format(index), "w")
    f.write("""
    TH1F('MllSS' , '' , 180 , 0. , 300.) << (MllSS : '\#it{m}_{ll} [GeV]');
    @*/*: MllSS;

    TH1F('MllZ' , '' , 180 , 0. , 150.) << (MllSS : '\#it{m}_{ll} [GeV]');
    @*/*: MllZ;

    TH1F('nvtx' , '' , 60 , 0. , 60. ) << (nVert : 'Nvtx');
    @*/*: nvtx;

    #TH1F('Mjj' , '' , 180 , 0. , 300.) << (Mjj : '\#it{m}_{jj} [GeV]');
    #@*/*: Mjj;
    #
    #TH1F('MllSS' , '' , 180 , 0. , 300.) << (MllSS : '\#it{m}_{ll} [GeV]');
    #@*/*: MllSS;

    TH1F('MET' , '' , 180 , 0. , 180.) << (met_pt : 'MET [GeV]');
    @*/*: MET;

    TH1F('lep_pt0' , '' , 180 , 0. , 250 ) << (lep_pt[0] : '\#it{p}_{T, lead-lep} [GeV]');
    @*/*: lep_pt0;

    TH1F('lep_pt1' , '' , 180 , 0. , 150 ) << (lep_pt[1] : '\#it{p}_{T, trail-lep} [GeV]');
    @*/*: lep_pt1;

    #TH1F('lep_pt2' , '' , 180 , 0. , 150 ) << (lep_pt[2] : '\#it{p}_{T, trail-lep} [GeV]');
    #@*/*: lep_pt1;

    TH1F('lep_eta0' , '' , 180 , -2.5 , 2.5 ) << (lep_eta[0] : '\#eta_{lead-lep}');
    @*/*: lep_eta0;

    TH1F('lep_eta1' , '' , 180 , -2.5 , 2.5 ) << (lep_eta[1] : '\#eta_{trail-lep}');
    @*/*: lep_eta1;

    #TH1F('lep_eta2' , '' , 180 , -2.5 , 2.5 ) << (lep_eta[2] : '\#eta_{trail-lep}');
    #@*/*: lep_eta1;
    #
    TH1F('lep_phi0' , '' , 180 , -3.1416 , 3.1416 ) << (lep_phi[0] : '\#phi_{lead-lep}');
    @*/*: lep_phi0;

    TH1F('lep_phi1' , '' , 180 , -3.1416, 3.1416 ) << (lep_phi[1] : '\#phi_{trail-lep}');
    @*/*: lep_phi1;

    #TH1F('lep_phi2' , '' , 180 , -3.1416, 3.1416 ) << (lep_phi[2] : '\#phi_{trail-lep}');
    #@*/*: lep_phi1;
    #
    TH1F('nj' , '' , 5 , 0. , 5. ) << (nj : 'N_{jet}');
    @*/*: nj;

    TH1F('nj30' , '' , 5 , 0. , 5. ) << (nj30 : 'N_{jet}');
    @*/*: nj30;

    TH1F('nb' , '' , 5 , 0. , 5. ) << (nb : 'N_{b-jet}');
    @*/*: nb;

    #TH1F('jets_pt0' , '' , 180 , 0. , 250 ) << (jets_p4[0].pt() : '\#it{p}_{T, lead-jet} [GeV]');
    #@*/*: jets_pt0;
    #
    #TH1F('jets_pt1' , '' , 180 , 0. , 150 ) << (jets_p4[1].pt() : '\#it{p}_{T, trail-jet} [GeV]');
    #@*/*: jets_pt1;
    #
    #TH1F('jets_eta0' , '' , 180 , -5.0 , 5.0 ) << (jets_p4[0].eta() : '\#eta_{lead-jet}');
    #@*/*: jets_eta0;
    #
    #TH1F('jets_eta1' , '' , 180 , -5.0 , 5.0 ) << (jets_p4[1].eta() : '\#eta_{trail-jet}');
    #@*/*: jets_eta1;
    #
    #TH1F('jets_phi0' , '' , 180 , -3.1416, 3.1416 ) << (jets_p4[0].phi() : '\#phi_{lead-jet}');
    #@*/*: jets_phi0;
    #
    #TH1F('jets_phi1' , '' , 180 , -3.1416, 3.1416 ) << (jets_p4[1].phi() : '\#phi_{trail-jet}');
    #@*/*: jets_phi1;

    """)
    f.close()

    #
    #
    # Book Analysis Jobs (Histogramming, Cutflow, Event lists)
    #
    #
    histojob = TQHistoMakerAnalysisJob()
    histojob.importJobsFromTextFiles(".histo.os.cfg", cuts, "*")#, True)

    # Analysis jobs
    cutflowjob = TQCutflowAnalysisJob("cutflow")
    cuts.addAnalysisJob(cutflowjob, "*")

    # Eventlist jobs
    #eventlistjob = TQEventlistAnalysisJob("eventlist")
    #eventlistjob.importJobsFromTextFiles("eventlist.cfg", cuts, "*", True)

    # Print cuts and numebr of booked analysis jobs for debugging purpose
    #cuts.printCut("trd")

    #
    #
    # Loop over the samples
    #
    #

    # setup a visitor to actually loop over ROOT files
    vis = TQAnalysisSampleVisitor(cuts,True)

    # Get all sample lists
    sample_names, sample_full_names = getSampleLists(samples)

    # Select the job based on the index
    sample_name = sample_names[index]
    sample_full_name = sample_full_names[sample_name]

    # Run the job!
    samples.visitSampleFolders(vis, "/*/{}".format(sample_full_name))

    # Write the output histograms and cutflow cut values and etc.
    samples.writeToFile(".qos_output_{}.root".format(sample_name), True)


##########################################################################################################


def getNTotalSample():
    # Create the master TQSampleFolder
    samples = TQSampleFolder("samples")

    # Created a sample information parser
    parser = TQXSecParser(samples);

    # Read the configuration file that contains what sample names are and how to categorize them
    parser.readCSVfile("samples.cfg")
    parser.readMappingFromColumn("*path*")
    parser.enableSamplesWithPriorityGreaterThan("priority", 2)
    parser.addAllSamples(True)

    # Decide that path where the root files are sitting
    import socket
    if socket.gethostname().find("pcc007") != -1: # philip's local mac computer
        samplepath = "/Users/phchang/work/analyses/www/code/VVVBabyMaker/Loopers/samples/"
    else:
        samplepath = "/nfs-7/userdata/phchang/WWW_babies/WWW_v1.0.20/skim/"

    # By "visiting" the samples with the initializer we actually hook up the samples with root files
    init = TQSampleInitializer(samplepath, 1)
    samples.visitMe(init)

    # Get all the samples to run
    sample_names = []
    sample_full_names = {}
    for i in samples.getListOfSamples():
        if i.getNSamples(True) == 0:
            sample_name = i.GetName()
            nice_name = sample_name.replace(".root", "")
            sample_names.append(nice_name)
            sample_full_names[nice_name] = sample_name

    print len(sample_names)
    return len(sample_names)

if __name__ == "__main__":

    import multiprocessing

    jobs = []
    for i in range(getNTotalSample()):
        p = multiprocessing.Process(target=main, args=(i,))
        jobs.append(p)
        p.start()

    for job in jobs:
        job.join()

    os.system("rooutil/qframework/share/tqmerge -o output.root -t analysis .qos_output_*.root")

