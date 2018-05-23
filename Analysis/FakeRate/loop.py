#!/bin/env python

import os
import sys
import ROOT
from QFramework import TQSampleFolder, TQXSecParser, TQCut, TQAnalysisSampleVisitor, TQSampleInitializer, TQCutflowAnalysisJob, TQCutflowPrinter, TQHistoMakerAnalysisJob, TQHWWPlotter, TQEventlistAnalysisJob
from rooutil.qutils import *

samplescfgpath = "../samples.cfg"
nfspath = "/nfs-7/userdata/phchang/WWW_babies/WWW_v1.1.1/skim/"

def main(index, mode):

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
    connectNtuples(samples, samplescfgpath, nfspath, ">4", ">5")

    #
    #
    # Define cuts
    #
    #
    PreselCuts = [
    ["1"                                          , "evt_scale1fb*35.9"       ] , 
    ["1"                                          , "purewgt"                 ] , 
    ["Flag_AllEventFilters"                       , "1"                       ] , 
    ["nj30>=1"                                    , "1"                       ] , 
    ["firstgoodvertex==0"                         , "1"                       ] ,
    ["evt_passgoodrunlist"                        , "1"                       ] ,
    ]
    PreselCutExpr, PreselWgtExpr = combexpr(PreselCuts)
    #["nVlep==1"                                            , "1"                       ] , 

    # complicated string construction
    mu_loosetemp = "(TMath::Abs(lep_eta[{idx}]<2.4))*(lep_dz[{idx}]<0.1)*(lep_dxy[{idx}]<0.05)*(lep_ip3d[{idx}]<0.015)*(abs(lep_ip3derr[{idx}]/lep_ip3d[{idx}])<4.)*(abs(lep_pterr[{idx}]/lep_trk_pt[{idx}])<0.2)*(lep_isMediumPOG[{idx}])*(lep_pt[{idx}]>20.)"
    mu_tighttemp = "({loose})*(lep_relIso03EAv2Lep[{idx}]<0.03)".format(loose=mu_loosetemp, idx="{idx}")
    leadmu_loose = mu_loosetemp.format(idx="0")
    leadmu_tight = mu_tighttemp.format(idx="0")
    trailmu_loose = mu_loosetemp.format(idx="1")
    trailmu_tight = mu_tighttemp.format(idx="1")
    bothmu_loose = "({})&&({})".format(leadmu_loose, trailmu_loose)
    bothmu_tight = "({})&&({})".format(leadmu_tight, trailmu_tight)

    # complicated string construction
    el_loosetemp = "(TMath::Abs(lep_eta[{idx}]<2.4))*(lep_dz[{idx}]<0.1)*(lep_dxy[{idx}]<0.05)*(lep_ip3d[{idx}]<0.01)*(lep_tightCharge[{idx}]==2)*((abs(lep_etaSC[{idx}])<=1.479)*(lep_MVA[{idx}]>0.941)+(abs(lep_etaSC[{idx}])>1.479)*(lep_MVA[{idx}]>0.925))*(lep_isTriggerSafe_v1[{idx}])*(lep_pt[{idx}]>20.)"
    el_tighttemp = "({loose})*(lep_relIso03EAv2Lep[{idx}]<0.03)".format(loose=el_loosetemp, idx="{idx}")
    leadel_loose = el_loosetemp.format(idx="0")
    leadel_tight = el_tighttemp.format(idx="0")
    trailel_loose = el_loosetemp.format(idx="1")
    trailel_tight = el_tighttemp.format(idx="1")
    bothel_loose = "({})&&({})".format(leadel_loose, trailel_loose)
    bothel_tight = "({})&&({})".format(leadel_tight, trailel_tight)

    # One lepton kinematic selection
    onelep_kinematic = "(jets_p4[0].pt()>40.)"
    if mode == 0:
        onelep_kinematic = "(met_pt<20.)*(TMath::Sqrt(2*met_pt*lep_pt[0]*(1.0-TMath::Cos(lep_phi[0]-met_phi))<20.))*(jets_p4[0].pt()>40.)"
    twolep_kinematic = "(lep_pdgId[0]*lep_pdgId[1]>0)*(nj30>=2)"

    # remove muons
    #remove_prompt_mu = "(abs(genPart_motherId[])==24)*(abs(genPart_pdgId[])==11)" # require only real electrons
    #remove_prompt_el = "(abs(genPart_motherId[])==24)*(abs(genPart_pdgId[])==13)" # require only real muons
    remove_prompt_mu = "1" # require only real electrons
    remove_prompt_el = "1" # require only real muons

    #weight_el = "(abs(lep_pdgId[0])==11)*([TH2Map:qcd_fakerates.root:qcdelbcToE([abs(lep_eta[0])],[lep_pt[0]])])+(abs(lep_pdgId[1])==11)*([TH2Map:qcd_fakerates.root:qcdelbcToE([abs(lep_eta[1])],[lep_pt[1]])])"
    #weight_mu = "(abs(lep_pdgId[0])==13)*([TH2Map:qcd_fakerates.root:qcdmu([abs(lep_eta[0])],[lep_pt[0]])])+(abs(lep_pdgId[1])==13)*([TH2Map:qcd_fakerates.root:qcdmu([abs(lep_eta[1])],[lep_pt[1]])])"
    weight_el = "([abs(lep_pdgId[0])==11])*([TH2Map:qcd_fakerates.root:qcdelbcToE([abs(lep_eta[0])],[lep_pt[0]*(1.0+TMath::Max(0.0, lep_relIso03EAv2Lep[0]-0.03))])])+([abs(lep_pdgId[1])==11])*([TH2Map:qcd_fakerates.root:qcdelbcToE([abs(lep_eta[1])],[lep_pt[1]*(1.0+TMath::Max(0.0, lep_relIso03EAv2Lep[1]-0.03))])])"
    weight_mu = "([abs(lep_pdgId[0])==13])*([TH2Map:qcd_fakerates.root:qcdmu([abs(lep_eta[0])],[lep_pt[0]*(1.0+TMath::Max(0.0, lep_relIso03EAv2Lep[0]-0.03))])])+([abs(lep_pdgId[1])==13])*([TH2Map:qcd_fakerates.root:qcdmu([abs(lep_eta[1])],[lep_pt[1]*(1.0+TMath::Max(0.0, lep_relIso03EAv2Lep[1]-0.03))])])"

    # TQCut objects
    tqcuts = {}
    tqcuts["Presel"] = TQCut("Presel", "Presel", PreselCutExpr, PreselWgtExpr)
    tqcuts["RemovePromptMu"] = TQCut("RemovePromptMu", "RemovePromptMu", remove_prompt_mu, "1")
    tqcuts["RemovePromptEl"] = TQCut("RemovePromptEl", "RemovePromptEl", remove_prompt_el, "1")
    tqcuts["OneLep"] = TQCut("OneLep", "OneLep", "(nVlep==1)*({})".format(onelep_kinematic), "1")
    tqcuts["TwoLep"] = TQCut("TwoLep", "TwoLep", "(nVlep==2)*({})".format(twolep_kinematic), "1")

    tqcuts["OneMu"] = TQCut("OneMu", "OneMu", "(abs(lep_pdgId[0])==13)", "1")
    tqcuts["OneMuLoose"] = TQCut("OneMuLoose", "OneMuLoose", leadmu_loose, "1")
    tqcuts["OneMuTight"] = TQCut("OneMuTight", "OneMuTight", leadmu_tight, "1")

    tqcuts["OneEl"] = TQCut("OneEl", "OneEl", "(abs(lep_pdgId[0])==11)", "1")
    tqcuts["OneElLoose"] = TQCut("OneElLoose", "OneElLoose", leadel_loose, "1")
    tqcuts["OneElTight"] = TQCut("OneElTight", "OneElTight", leadel_tight, "1")

    tqcuts["TwoMu"] = TQCut("TwoMu", "TwoMu", "((abs(lep_pdgId[0])==13)+(abs(lep_pdgId[1])==13))*((abs(lep_pdgId[0])==11)*(lep_pass_VVV_cutbased_tight[0]*(lep_motherIdSS[0]>0))+(abs(lep_pdgId[1])==11)*(lep_pass_VVV_cutbased_tight[1]*(lep_motherIdSS[1]>0)))", "1") # one any muon and one real tight electron with two total leptons
    tqcuts["TwoMuLoose"] = TQCut("TwoMuLoose", "TwoMuLoose", "(abs(lep_pdgId[0])==13)*({})+(abs(lep_pdgId[1])==13)*({})".format(leadmu_loose, trailmu_loose), "1")
    tqcuts["TwoMuTight"] = TQCut("TwoMuTight", "TwoMuTight", "(abs(lep_pdgId[0])==13)*({})+(abs(lep_pdgId[1])==13)*({})".format(leadmu_tight, trailmu_tight), "1")
    tqcuts["TwoMuLoosePredict"] = TQCut("TwoMuLoosePredict", "TwoMuLoosePredict", "(abs(lep_pdgId[0])==13)*({})+(abs(lep_pdgId[1])==13)*({})".format(leadmu_tight, trailmu_tight), "1")
    tqcuts["TwoMuTightPredict"] = TQCut("TwoMuTightPredict", "TwoMuTightPredict", "(abs(lep_pdgId[0])==13)*({})*(!({}))+(abs(lep_pdgId[1])==13)*({})*(!({}))".format(leadmu_loose, leadmu_tight, trailmu_loose, trailmu_tight), weight_mu)

    tqcuts["TwoEl"] = TQCut("TwoEl", "TwoEl", "((abs(lep_pdgId[0])==11)+(abs(lep_pdgId[1])==11))*((abs(lep_pdgId[0])==13)*(lep_pass_VVV_cutbased_tight[0]*(lep_motherIdSS[0]>0))+(abs(lep_pdgId[1])==13)*(lep_pass_VVV_cutbased_tight[1]*(lep_motherIdSS[1]>0)))", "1") # one any electron and one real tight muon with two total leptons
    tqcuts["TwoElLoose"] = TQCut("TwoElLoose", "TwoElLoose", "(abs(lep_pdgId[0])==11)*({})+(abs(lep_pdgId[1])==11)*({})".format(leadel_loose, trailel_loose), "1")
    tqcuts["TwoElTight"] = TQCut("TwoElTight", "TwoElTight", "(abs(lep_pdgId[0])==11)*({})+(abs(lep_pdgId[1])==11)*({})".format(leadel_tight, trailel_tight), "1")
    tqcuts["TwoElLoosePredict"] = TQCut("TwoElLoosePredict", "TwoElLoosePredict", "(abs(lep_pdgId[0])==11)*({})+(abs(lep_pdgId[1])==11)*({})".format(leadel_tight, trailel_tight), "1")
    tqcuts["TwoElTightPredict"] = TQCut("TwoElTightPredict", "TwoElTightPredict", "(abs(lep_pdgId[0])==11)*({})*(!({}))+(abs(lep_pdgId[1])==11)*({})*(!({}))".format(leadel_loose, leadel_tight, trailel_loose, trailel_tight), weight_el)

    # Linking TQCut objects
    tqcuts["Presel"].addCut(tqcuts["OneLep"])
    tqcuts["Presel"].addCut(tqcuts["TwoLep"])

    tqcuts["OneLep"].addCut(tqcuts["OneMu"])
    tqcuts["OneMu"].addCut(tqcuts["OneMuLoose"])
    tqcuts["OneMuLoose"].addCut(tqcuts["OneMuTight"])

    tqcuts["OneLep"].addCut(tqcuts["OneEl"])
    tqcuts["OneEl"].addCut(tqcuts["OneElLoose"])
    tqcuts["OneElLoose"].addCut(tqcuts["OneElTight"])

    tqcuts["TwoLep"].addCut(tqcuts["TwoMu"])
    tqcuts["TwoMu"].addCut(tqcuts["TwoMuLoosePredict"])
    tqcuts["TwoMu"].addCut(tqcuts["TwoMuTightPredict"])
    tqcuts["TwoMu"].addCut(tqcuts["TwoMuLoose"])
    tqcuts["TwoMuLoose"].addCut(tqcuts["TwoMuTight"])

    tqcuts["TwoLep"].addCut(tqcuts["TwoEl"])
    tqcuts["TwoEl"].addCut(tqcuts["TwoElLoosePredict"])
    tqcuts["TwoEl"].addCut(tqcuts["TwoElTightPredict"])
    tqcuts["TwoEl"].addCut(tqcuts["TwoElLoose"])
    tqcuts["TwoElLoose"].addCut(tqcuts["TwoElTight"])

    # Grand cut
    cuts = tqcuts["Presel"]

    #
    #
    # Define histograms
    #
    #
    filename = ".histo.mr.{}.cfg".format(index)
    f = open(filename, "w")
    f.write("""
    TH2F('lep_pt_vs_eta' , '' , {0, 0.9, 1.6, 1.9, 2.4}, {20, 30, 40, 50, 60, 70, 150, 2000} ) << (abs(lep_eta[0]) : '|\#eta|', lep_pt[0] : '\#it{p}_{T} [GeV]');
    @OneLep/*: lep_pt_vs_eta;

    TH2F('lep_ptcorr_vs_eta' , '' , {0, 0.9, 1.6, 1.9, 2.4}, {0., 5., 10., 15., 20., 25., 30., 35., 40., 45., 60., 80., 120.} ) << (abs(lep_eta[0]) : '|\#eta|', lep_pt[0]*(1.+TMath::Max(0.,lep_relIso03EAv2Lep[0]-0.03)) : '\#it{p}_{T} [GeV]');
    @OneLep/*: lep_ptcorr_vs_eta;

    TH2F('lep_ptcorrcoarse_vs_eta' , '' , {0, 0.9, 1.6, 1.9, 2.4}, {0., 10., 20., 25., 30., 40., 60., 120.} ) << (abs(lep_eta[0]) : '|\#eta|', lep_pt[0]*(1.+TMath::Max(0.,lep_relIso03EAv2Lep[0]-0.03)) : '\#it{p}_{T} [GeV]');
    @OneLep/*: lep_ptcorrcoarse_vs_eta;

    TH1F('lep_pt' , '' , 180 , 0. , 250 ) << (lep_pt[0] : '\#it{p}_{T} [GeV]');
    @OneLep/*: lep_pt;

    TH1F('lep_pdgId' , '' , 40 , -20. , 20 ) << (lep_pdgId[0] : 'Lepton PDG ID');
    @OneLep/*: lep_pdgId;

    TH1F('lep_ptcorr' , '' , 180 , 0. , 250 ) << (lep_pt[0] * (1. + TMath::Max(0., lep_relIso03EAv2Lep[0]-0.03)) : '\#it{p}_{T, cone-corr} [GeV]');
    @OneLep/*: lep_ptcorr;

    TH1F('lep_ptcorrvarbin' , '' , {0., 5., 10., 15., 20., 25., 30., 35., 40., 45., 60., 80., 120.}) << (lep_pt[0]*(1.+TMath::Max(0.,lep_relIso03EAv2Lep[0]-0.03)) : '\#it{p}_{T, cone-corr} [GeV]');
    @OneLep/*: lep_ptcorrvarbin;

    TH1F('lep_ptcorrvarbincoarse' , '' , {0., 10., 20., 25., 30., 40., 60., 120.}) << (lep_pt[0]*(1.+TMath::Max(0.,lep_relIso03EAv2Lep[0]-0.03)) : '\#it{p}_{T, cone-corr} [GeV]');
    @OneLep/*: lep_ptcorrvarbincoarse;

    TH1F('lep_eta' , '' , 180 , -2.5 , 2.5 ) << (lep_eta[0] : '\#eta');
    @OneLep/*: lep_eta;

    TH1F('lep_etavarbin' , '' , {-2.5, -2.1, -1.6, -1.0, 0.0, 1.0, 1.6, 2.1, 2.5} ) << (lep_eta[0] : '\#eta');
    @OneLep/*: lep_etavarbin;

    TH1F('lep_relIso03EAv2Lep' , '' , 180 , 0.0 , 0.4 ) << (lep_relIso03EAv2Lep[0] : 'I_{R=0.3,EA,Lep}');
    @OneLep/*: lep_relIso03EAv2Lep;

    TH1F('mu_ptcorrvarbin' , '' , {0., 5., 10., 15., 20., 25., 30., 35., 40., 45., 60., 80., 120.}) << ((lep_pt[0]*(1.+TMath::Max(0.,lep_relIso03EAv2Lep[0]-0.03)))*(abs(lep_pdgId[0])==13)+(lep_pt[1]*(1.+TMath::Max(0.,lep_relIso03EAv2Lep[1]-0.03)))*(abs(lep_pdgId[1])==13) : '\#it{p}_{T, cone-corr, mu} [GeV]');
    @TwoMu/*: mu_ptcorrvarbin;

    TH1F('mu_ptcorrvarbincoarse' , '' , {0., 10., 20., 25., 30., 40., 60., 120.}) << ((lep_pt[0]*(1.+TMath::Max(0.,lep_relIso03EAv2Lep[0]-0.03)))*(abs(lep_pdgId[0])==13)+(lep_pt[1]*(1.+TMath::Max(0.,lep_relIso03EAv2Lep[1]-0.03)))*(abs(lep_pdgId[1])==13) : '\#it{p}_{T, cone-corr, mu} [GeV]');
    @TwoMu/*: mu_ptcorrvarbincoarse;

    TH2F('mu_ptcorr_vs_eta' , '' , {0, 0.9, 1.6, 1.9, 2.4}, {0., 5., 10., 15., 20., 25., 30., 35., 40., 45., 60., 80., 120.} ) << ((abs(lep_eta[0]))*(abs(lep_pdgId[0])==13)+(abs(lep_eta[1]))*(abs(lep_pdgId[1])==13) : '|\#eta|', (lep_pt[0]*(1.+TMath::Max(0.,lep_relIso03EAv2Lep[0]-0.03)))*(abs(lep_pdgId[0])==13)+(lep_pt[1]*(1.+TMath::Max(0.,lep_relIso03EAv2Lep[1]-0.03)))*(abs(lep_pdgId[1])==13) : '\#it{p}_{T, cone-corr, mu} [GeV]');
    @TwoMu/*: mu_ptcorr_vs_eta;

    TH2F('mu_ptcorrcoarse_vs_eta' , '' , {0, 0.9, 1.6, 1.9, 2.4}, {0., 10., 20., 25., 30., 40., 60., 120.} ) << ((abs(lep_eta[0]))*(abs(lep_pdgId[0])==13)+(abs(lep_eta[1]))*(abs(lep_pdgId[1])==13) : '|\#eta|', (lep_pt[0]*(1.+TMath::Max(0.,lep_relIso03EAv2Lep[0]-0.03)))*(abs(lep_pdgId[0])==13)+(lep_pt[1]*(1.+TMath::Max(0.,lep_relIso03EAv2Lep[1]-0.03)))*(abs(lep_pdgId[1])==13) : '\#it{p}_{T, cone-corr, mu} [GeV]');
    @TwoMu/*: mu_ptcorrcoarse_vs_eta;

    TH1F('mu_pt' , '' , 180 , 0., 250) << ((lep_pt[0])*(abs(lep_pdgId[0])==13)+(lep_pt[1])*(abs(lep_pdgId[1])==13) : '\#it{p}_{T, \#mu} [GeV]');
    @TwoMu/*: mu_pt;

    TH1F('mu_eta' , '' , 180 , -2.5, 2.5) << ((lep_eta[0])*(abs(lep_pdgId[0])==13)+(lep_eta[1])*(abs(lep_pdgId[1])==13) : '\#eta_{\#mu}');
    @TwoMu/*: mu_eta;

    TH1F('mu_etavarbin' , '' , {-2.5, -2.1, -1.6, -1.0, 0.0, 1.0, 1.6, 2.1, 2.5} ) << (lep_eta[0] : '\#eta');
    @TwoMu/*: mu_etavarbin;

    TH1F('mu_relIso03EAv2Lep' , '' , 180 , 0., 0.4) << ((lep_relIso03EAv2Lep[0])*(abs(lep_pdgId[0])==13)+(lep_relIso03EAv2Lep[1])*(abs(lep_pdgId[1])==13) : 'I_{R=0.3,EA,Lep,\#mu}');
    @TwoMu/*: mu_relIso03EAv2Lep;

    TH2F('el_ptcorr_vs_eta' , '' , {0, 0.9, 1.6, 1.9, 2.4}, {0., 5., 10., 15., 20., 25., 30., 35., 40., 45., 60., 80., 120.} ) << ((abs(lep_eta[0]))*(abs(lep_pdgId[0])==11)+(abs(lep_eta[1]))*(abs(lep_pdgId[1])==11) : '|\#eta|', (lep_pt[0]*(1.+TMath::Max(0.,lep_relIso03EAv2Lep[0]-0.03)))*(abs(lep_pdgId[0])==11)+(lep_pt[1]*(1.+TMath::Max(0.,lep_relIso03EAv2Lep[1]-0.03)))*(abs(lep_pdgId[1])==11) : '\#it{p}_{T, cone-corr, mu} [GeV]');
    @TwoEl/*: el_ptcorr_vs_eta;

    TH2F('el_ptcorrcoarse_vs_eta' , '' , {0, 0.9, 1.6, 1.9, 2.4}, {0., 10., 20., 25., 30., 40., 60., 120.} ) << ((abs(lep_eta[0]))*(abs(lep_pdgId[0])==11)+(abs(lep_eta[1]))*(abs(lep_pdgId[1])==11) : '|\#eta|', (lep_pt[0]*(1.+TMath::Max(0.,lep_relIso03EAv2Lep[0]-0.03)))*(abs(lep_pdgId[0])==11)+(lep_pt[1]*(1.+TMath::Max(0.,lep_relIso03EAv2Lep[1]-0.03)))*(abs(lep_pdgId[1])==11) : '\#it{p}_{T, cone-corr, mu} [GeV]');
    @TwoEl/*: el_ptcorrcoarse_vs_eta;

    TH1F('el_ptcorrvarbin' , '' , {0., 5., 10., 15., 20., 25., 30., 35., 40., 45., 60., 80., 120.}) << ((lep_pt[0]*(1.+TMath::Max(0.,lep_relIso03EAv2Lep[0]-0.03)))*(abs(lep_pdgId[0])==11)+(lep_pt[1]*(1.+TMath::Max(0.,lep_relIso03EAv2Lep[1]-0.03)))*(abs(lep_pdgId[1])==11) : '\#it{p}_{T, cone-corr, el} [GeV]');
    @TwoEl/*: el_ptcorrvarbin;

    TH1F('el_ptcorrvarbincoarse' , '' , {0., 10., 20., 25., 30., 40., 60., 120.}) << ((lep_pt[0]*(1.+TMath::Max(0.,lep_relIso03EAv2Lep[0]-0.03)))*(abs(lep_pdgId[0])==11)+(lep_pt[1]*(1.+TMath::Max(0.,lep_relIso03EAv2Lep[1]-0.03)))*(abs(lep_pdgId[1])==11) : '\#it{p}_{T, cone-corr, mu} [GeV]');
    @TwoEl/*: el_ptcorrvarbincoarse;

    TH1F('el_pt' , '' , 180 , 0., 250) << ((lep_pt[0])*(abs(lep_pdgId[0])==11)+(lep_pt[1])*(abs(lep_pdgId[1])==11) : '\#it{p}_{T, el} [GeV]');
    @TwoEl/*: el_pt;

    TH1F('el_eta' , '' , 180 , -2.5, 2.5) << ((lep_eta[0])*(abs(lep_pdgId[0])==11)+(lep_eta[1])*(abs(lep_pdgId[1])==11) : '\#eta_{el}');
    @TwoEl/*: el_eta;

    TH1F('el_etavarbin' , '' , {-2.5, -2.1, -1.6, -1.0, 0.0, 1.0, 1.6, 2.1, 2.5} ) << (lep_eta[0] : '\#eta');
    @TwoEl/*: el_etavarbin;

    TH1F('el_relIso03EAv2Lep' , '' , 180 , 0., 0.4) << ((lep_relIso03EAv2Lep[0])*(abs(lep_pdgId[0])==11)+(lep_relIso03EAv2Lep[1])*(abs(lep_pdgId[1])==11) : 'I_{R=0.3,EA,Lep,el}');
    @TwoEl/*: el_relIso03EAv2Lep;

    TH1F('Mjj_el' , '' , 180 , 0., 180. ) << (Mjj : '\#it{m}_{jj} [GeV]');
    @TwoEl/*: Mjj_el;

    TH1F('Mjj_mu' , '' , 180 , 0., 180. ) << (Mjj : '\#it{m}_{jj} [GeV]');
    @TwoMu/*: Mjj_mu;

    TH1F('Mll_el' , '' , 180 , 0., 180. ) << (MllSS : '\#it{m}_{ll} [GeV]');
    @TwoEl/*: Mll_el;

    TH1F('Mll_mu' , '' , 180 , 0., 180. ) << (MllSS : '\#it{m}_{ll} [GeV]');
    @TwoMu/*: Mll_mu;

    TH1F('MET_el' , '' , 180 , 0., 180. ) << (met_pt : 'MET [GeV]');
    @TwoEl/*: MET_el;

    TH1F('MET_mu' , '' , 180 , 0., 180. ) << (met_pt : 'MET [GeV]');
    @TwoMu/*: MET_mu;

    TH1F('MTmax_el' , '' , 180 , 0., 180. ) << (MTmax : '\#it{m}_{T,max} [GeV]');
    @TwoEl/*: MTmax_el;

    TH1F('MTmax_mu' , '' , 180 , 0., 180. ) << (MTmax : '\#it{m}_{T,max} [GeV]');
    @TwoMu/*: MTmax_mu;

    """)
    f.close()

    #
    #
    # Book Analysis Jobs (Histogramming, Cutflow, Event lists)
    #
    #
    histojob = TQHistoMakerAnalysisJob()
    histojob.importJobsFromTextFiles(filename, cuts, "*", True if index < 0 else False)

    # Analysis jobs
    cutflowjob = TQCutflowAnalysisJob("cutflow")
    cuts.addAnalysisJob(cutflowjob, "*")

    # Eventlist jobs
    #eventlistjob = TQEventlistAnalysisJob("eventlist")
    #eventlistjob.importJobsFromTextFiles("eventlist.cfg", cuts, "*", True)

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
    #vis.setMaxEvents(30000)

    if index >= 0:

        # Get all sample lists
        sample_names, sample_full_names = getSampleLists(samples)

        # Select the job based on the index
        sample_name = sample_names[index]
        sample_full_name = sample_full_names[sample_name]

        # Run the job!
        samples.visitSampleFolders(vis, "/*/{}".format(sample_full_name))

        # Write the output histograms and cutflow cut values and etc.
        samples.writeToFile(".output_{}.root".format(sample_name), True)

    else:
        # Run the job!
        samples.visitSampleFolders(vis)

        # Write the output histograms and cutflow cut values and etc.
        samples.writeToFile("output.root", True)

if __name__ == "__main__":

    try:
        mode = int(sys.argv[1]) # mode determines which selection to run for QCD
    except:
        print "Usage:"
        print ""
        print " {} MODE"
        print ""
        print "  MODE determines which QCD selection run"
        print "  MODE=0 runs QCD with full one lepton selection including MT < 20. and MET < 20."
        print "  MODE=1 runs QCD without MT < 20. and MET < 20."
        print ""
        print "NOTE : Running with default mode of MODE=0!"
        print "NOTE : Running with default mode of MODE=0!"
        print "NOTE : Running with default mode of MODE=0!"
        print "NOTE : Running with default mode of MODE=0!"
        mode = 0

    import multiprocessing

    samples = TQSampleFolder("samples")
    connectNtuples(samples, samplescfgpath, nfspath, ">4", ">5")
    # Get all sample lists
    sample_names, sample_full_names = getSampleLists(samples)
    njobs = len(sample_names)

    jobs = []
    for i in range(njobs):
        p = multiprocessing.Process(target=main, args=(i, mode,))
        jobs.append(p)
        p.start()

    for index, job in enumerate(jobs):
        #print "{} jobs done out of {}".format(index, len(jobs))
        job.join()

    os.system("rooutil/qframework/share/tqmerge -o output.root -t analysis .output_*.root")
    os.system("rm .output_*.root")
    os.system("rm .histo.mr.*.cfg")
