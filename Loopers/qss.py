#!/bin/env python

import os
import sys
import ROOT
from QFramework import TQSampleFolder, TQXSecParser, TQCut, TQAnalysisSampleVisitor, TQSampleInitializer, TQCutflowAnalysisJob, TQCutflowPrinter, TQHistoMakerAnalysisJob, TQHWWPlotter, TQEventlistAnalysisJob
from qutils import *

def main(index):

    #
    #
    # Redirect stdout to log the parallel jobs
    #
    #
    #sys.stdout = open("." + str(os.getpid()) + ".out", "w", buffering=0)

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
    connectNtuples(samples, "samples.cfg", "/nfs-7/userdata/phchang/WWW_babies/WWW_v1.0.23/skim/", "<0")

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
    ["lep_pdgId[0]*lep_pdgId[1]>0"                , "trigsf*lepsf"                  ] ,
    ["MllSS > 10"                                 , "1"                             ] ,
    ]
    PreselCutExpr, PreselWgtExpr = combexpr(PreselCuts)

    tqcuts = {}
    #tqcuts["Base"] = TQCut("Base", "Base", "(nVlep==2)*(nLlep==2)*((abs(lep_pdgId[0])==13)*(lep_ptRatio[0]>0.9)+(abs(lep_pdgId[0])==11)*(lep_ptRatio[0]>0.84))*((abs(lep_pdgId[1])==13)*(lep_ptRatio[1]>0.9)+(abs(lep_pdgId[1])==11)*(lep_ptRatio[1]>0.84))", "1")
    tqcuts["Base"] = TQCut("Base", "Base", "(nVlep==2)*(nLlep==2)*(nTlep==2)", "1")
    tqcuts["Presel"] = TQCut("Presel", "Presel", PreselCutExpr, PreselWgtExpr)
    tqcuts["CutSSee"] = TQCut("CutSSee" , "SS: ee" , "(lep_pdgId[0]*lep_pdgId[1]==121)*(mc_HLT_DoubleEl_DZ_2==1)" , "trigsf")
    tqcuts["CutSSem"] = TQCut("CutSSem" , "SS: em" , "(lep_pdgId[0]*lep_pdgId[1]==143)*(mc_HLT_MuEG==1)" , "trigsf")
    tqcuts["CutSSmm"] = TQCut("CutSSmm" , "SS: mm" , "(lep_pdgId[0]*lep_pdgId[1]==169)*(mc_HLT_DoubleMu==1)" , "trigsf")

    #tqcuts["CutSSee"] = TQCut("CutSSee" , "SS: ee" , "(lep_pdgId[0]*lep_pdgId[1]==121)*(mc_HLT_DoubleEl_DZ_2==1)" , 
    #"""[TH2Map:lepsfrootfiles/trigeff.root:diel_dz_eta_v_eta_sf([(abs(lep_eta[0])>abs(lep_eta[1]))*abs(lep_eta[0])+(abs(lep_eta[0])<=abs(lep_eta[1]))*abs(lep_eta[1])],[(abs(lep_eta[0])>abs(lep_eta[1]))*abs(lep_eta[1])+(abs(lep_eta[0])<=abs(lep_eta[1]))*abs(lep_eta[0])])]*
    #   [TH2Map:lepsfrootfiles/trigeff.root:el_lead_leg_eta_v_pt_sf([abs(lep_eta[0])],[lep_pt[0]])]*
    #   [TH2Map:lepsfrootfiles/trigeff.root:el_lead_leg_eta_v_pt_sf([abs(lep_eta[1])],[lep_pt[1]])]""") # Trail and lead are identical

    #tqcuts["CutSSem"] = TQCut("CutSSem" , "SS: em" , "(lep_pdgId[0]*lep_pdgId[1]==143)*(mc_HLT_MuEG==1)" , 
    #"""[abs(lep_pdgId[0])==11]*
    #   [TH2Map:lepsfrootfiles/trigeff.root:el_lead_leg_eta_v_pt_sf([abs(lep_eta[0])],[lep_pt[0]])]*
    #   [TH2Map:lepsfrootfiles/trigeff.root:mu_trail_leg_eta_v_pt_sf([abs(lep_eta[1])],[lep_pt[1]])]
    #   +[abs(lep_pdgId[0])==13]*
    #   [TH2Map:lepsfrootfiles/trigeff.root:mu_lead_leg_eta_v_pt_sf([abs(lep_eta[0])],[lep_pt[0]])]*
    #   [TH2Map:lepsfrootfiles/trigeff.root:el_lead_leg_eta_v_pt_sf([abs(lep_eta[1])],[lep_pt[1]])]""") # Trail and lead are identical

    #tqcuts["CutSSmm"] = TQCut("CutSSmm" , "SS: mm" , "(lep_pdgId[0]*lep_pdgId[1]==169)*(mc_HLT_DoubleMu==1)" , 
    #"""[TH2Map:lepsfrootfiles/trigeff.root:dimu_dz_eta_v_eta_sf([(abs(lep_eta[0])>abs(lep_eta[1]))*abs(lep_eta[0])+(abs(lep_eta[0])<=abs(lep_eta[1]))*abs(lep_eta[1])],[(abs(lep_eta[0])>abs(lep_eta[1]))*abs(lep_eta[1])+(abs(lep_eta[0])<=abs(lep_eta[1]))*abs(lep_eta[0])])]*
    #   [TH2Map:lepsfrootfiles/trigeff.root:mu_lead_leg_eta_v_pt_sf([abs(lep_eta[0])],[lep_pt[0]])]*
    #   [TH2Map:lepsfrootfiles/trigeff.root:mu_trail_leg_eta_v_pt_sf([abs(lep_eta[1])],[lep_pt[1]])]""")

    #tqcuts["CutSSeeLepSF"] = TQCut("CutSSeeLepSF" , "SS: LepSF" , "1" , 
    #"""[TH2Map:lepsfrootfiles/egammaEffi.txt_EGM2D.root:EGamma_SF2D([lep_eta[0]],[lep_pt[0]])]*
    #   [TH2Map:lepsfrootfiles/egammaEffi.txt_EGM2D.root:EGamma_SF2D([lep_eta[1]],[lep_pt[1]])]*
    #   [TH2Map:lepsfrootfiles/egammaEffi.txt_EGM2D.MVA80.root:EGamma_SF2D([lep_eta[0]],[lep_pt[0]])]*
    #   [TH2Map:lepsfrootfiles/egammaEffi.txt_EGM2D.MVA80.root:EGamma_SF2D([lep_eta[1]],[lep_pt[1]])]*
    #   [TH2Map:lepsfrootfiles/elec_sf.root:sf_pt_vs_eta([abs(lep_eta[0])],[lep_pt[0]])]*
    #   [TH2Map:lepsfrootfiles/elec_sf.root:sf_pt_vs_eta([abs(lep_eta[1])],[lep_pt[1]])]""")

    #tqcuts["CutSSemLepSF"] = TQCut("CutSSemLepSF" , "SS: LepSF" , "1" ,
    #"""[abs(lep_pdgId[0])==11]*
    #   [TH2Map:lepsfrootfiles/egammaEffi.txt_EGM2D.root:EGamma_SF2D([lep_eta[0]],[lep_pt[0]])]*
    #   [TH2Map:lepsfrootfiles/egammaEffi.txt_EGM2D.MVA80.root:EGamma_SF2D([lep_eta[0]],[lep_pt[0]])]*
    #   [TH2Map:lepsfrootfiles/elec_sf.root:sf_pt_vs_eta([abs(lep_eta[0])],[lep_pt[0]])]*
    #   [TH1Map:lepsfrootfiles/muon_trk_sf.root:muon_trk_sf([abs(lep_eta[1])])]*
    #   [TH2Map:lepsfrootfiles/muon_id_sf.root:muon_id_sf([abs(lep_eta[1])],[lep_pt[1]])]*
    #   [TH2Map:lepsfrootfiles/muon_sf.root:sf_pt_vs_eta([abs(lep_eta[1])],[lep_pt[1]])]
    #   +[abs(lep_pdgId[0])==13]*
    #   [TH1Map:lepsfrootfiles/muon_trk_sf.root:muon_trk_sf([abs(lep_eta[0])])]*
    #   [TH2Map:lepsfrootfiles/muon_id_sf.root:muon_id_sf([abs(lep_eta[0])],[lep_pt[0]])]*
    #   [TH2Map:lepsfrootfiles/muon_sf.root:sf_pt_vs_eta([abs(lep_eta[0])],[lep_pt[0]])]*
    #   [TH2Map:lepsfrootfiles/egammaEffi.txt_EGM2D.root:EGamma_SF2D([lep_eta[1]],[lep_pt[1]])]*
    #   [TH2Map:lepsfrootfiles/egammaEffi.txt_EGM2D.MVA80.root:EGamma_SF2D([lep_eta[1]],[lep_pt[1]])]*
    #   [TH2Map:lepsfrootfiles/elec_sf.root:sf_pt_vs_eta([abs(lep_eta[1])],[lep_pt[1]])]""")

    #tqcuts["CutSSmmLepSF"] = TQCut("CutSSmmLepSF", "SS: LepSF" , "1",
    #"""[TH1Map:lepsfrootfiles/muon_trk_sf.root:muon_trk_sf([abs(lep_eta[0])])]*
    #   [TH1Map:lepsfrootfiles/muon_trk_sf.root:muon_trk_sf([abs(lep_eta[1])])]*
    #   [TH2Map:lepsfrootfiles/muon_id_sf.root:muon_id_sf([abs(lep_eta[0])],[lep_pt[0]])]*
    #   [TH2Map:lepsfrootfiles/muon_id_sf.root:muon_id_sf([abs(lep_eta[1])],[lep_pt[1]])]*
    #   [TH2Map:lepsfrootfiles/muon_sf.root:sf_pt_vs_eta([abs(lep_eta[0])],[lep_pt[0]])]*
    #   [TH2Map:lepsfrootfiles/muon_sf.root:sf_pt_vs_eta([abs(lep_eta[1])],[lep_pt[1]])]""")

    tqcuts["CutSSeeZeeVt"] = TQCut("CutSSeeZeeVt", "SS: ZeeVt" , "abs(MllSS-91.1876)>10.", "1");

    cuts = tqcuts["Base"]
    tqcuts["Base"].addCut(tqcuts["Presel"])
    tqcuts["Presel"].addCut(tqcuts["CutSSee"])
    tqcuts["Presel"].addCut(tqcuts["CutSSem"])
    tqcuts["Presel"].addCut(tqcuts["CutSSmm"])
    tqcuts["CutSSee"].addCut(tqcuts["CutSSeeZeeVt"])

    #
    #
    # Define histograms
    #
    #
    f = open(".histo.os.{}.cfg".format(index), "w")
    f.write("""
    TH1F('MllSS' , '' , 180 , 0. , 300.) << (MllSS : '\#it{m}_{ll} [GeV]');
    @*/*: MllSS;

    TH1F('MllZ' , '' , 180 , 60. , 120.) << (MllSS : '\#it{m}_{ll} [GeV]');
    @*/*: MllZ;

    TH1F('MllZZoom' , '' , 180 , 80. , 100.) << (MllSS : '\#it{m}_{ll} [GeV]');
    @*/*: MllZZoom;

    TH1F('nvtx' , '' , 60 , 0. , 60. ) << (nVert : 'Nvtx');
    @*/*: nvtx;

    #TH1F('Mjj' , '' , 180 , 0. , 300.) << (Mjj : '\#it{m}_{jj} [GeV]');
    #@*/*: Mjj;

    #TH1F('MllSS' , '' , 180 , 0. , 300.) << (MllSS : '\#it{m}_{ll} [GeV]');
    #@*/*: MllSS;

    TH1F('MET' , '' , 180 , 0. , 180.) << (met_pt : 'MET [GeV]');
    @*/*: MET;

    TH2F('lep0_pt_vs_eta' , '' , {0, 0.9, 1.6, 1.9, 2.4}, {20, 30, 40, 50, 60, 70, 150, 2000} ) << (lep_eta[0] : '\#eta_{lead-lep}', lep_pt[0] : '\#it{p}_{T, lead-lep} [GeV]');
    @*/*: lep0_pt_vs_eta;

    TH2F('lep1_pt_vs_eta' , '' , {0, 0.9, 1.6, 1.9, 2.4}, {20, 30, 40, 50, 60, 70, 150, 2000} ) << (lep_eta[1] : '\#eta_{trail-lep}', lep_pt[1] : '\#it{p}_{T, trail-lep} [GeV]');
    @*/*: lep1_pt_vs_eta;

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

    TH1F('lep_phi0' , '' , 180 , -3.1416 , 3.1416 ) << (lep_phi[0] : '\#phi_{lead-lep}');
    @*/*: lep_phi0;

    TH1F('lep_phi1' , '' , 180 , -3.1416, 3.1416 ) << (lep_phi[1] : '\#phi_{trail-lep}');
    @*/*: lep_phi1;

    TH1F('lep_ptRatio0' , '' , 180 , 0.6 , 1.2 ) << (lep_ptRatio[0] : '\#it{p}_{T, Ratio}');
    @*/*: lep_ptRatio0;

    TH1F('lep_ptRatio1' , '' , 180 , 0.6 , 1.2 ) << (lep_ptRatio[1] : '\#it{p}_{T, Ratio}');
    @*/*: lep_ptRatio1;

    TH1F('nj' , '' , 7 , 0. , 7. ) << (nj : 'N_{jet}');
    @*/*: nj;

    TH1F('nj30' , '' , 7 , 0. , 7. ) << (nj30 : 'N_{jet}');
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
    histojob.importJobsFromTextFiles(".histo.os.{}.cfg".format(index), cuts, "*", True if index < 0 else False)

    # Analysis jobs
    cutflowjob = TQCutflowAnalysisJob("cutflow")
    cuts.addAnalysisJob(cutflowjob, "*")

    # Eventlist jobs
    eventlistjob = TQEventlistAnalysisJob("eventlist")
    eventlistjob.importJobsFromTextFiles("eventlist.cfg", cuts, "*", True)

    # Print cuts and numebr of booked analysis jobs for debugging purpose
    if index < 0:
        cuts.printCut("trd")

    #
    #
    # Loop over the samples
    #
    #

    # setup a visitor to actually loop over ROOT files
    vis = TQAnalysisSampleVisitor(cuts,True)

    if index >= 0:

        # Get all sample lists
        sample_names, sample_full_names = getSampleLists(samples)

        # Select the job based on the index
        sample_name = sample_names[index]
        sample_full_name = sample_full_names[sample_name]

        # Run the job!
        samples.visitSampleFolders(vis, "/*/{}".format(sample_full_name))

        # Write the output histograms and cutflow cut values and etc.
        samples.writeToFile(".qss_output_{}.root".format(sample_name), True)

    else:
        # Run the job!
        samples.visitSampleFolders(vis)

        # Write the output histograms and cutflow cut values and etc.
        samples.writeToFile("output.root", True)

if __name__ == "__main__":

    if len(sys.argv) < 2:

        import multiprocessing

        jobs = []
        for i in range(55):
            p = multiprocessing.Process(target=main, args=(i,))
            jobs.append(p)
            p.start()

        for index, job in enumerate(jobs):
            #print "{} jobs done out of {}".format(index, len(jobs))
            job.join()

        os.system("rooutil/qframework/share/tqmerge -o output.root -t analysis .qss_output_*.root")

    else:

        main(int(sys.argv[1]))

