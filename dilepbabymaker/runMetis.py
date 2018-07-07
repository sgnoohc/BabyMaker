##!/bin/env python

################################
# Job tag and output hadoop path
################################

# NOTE: If you want to resubmit the skimming job, you need to delete $ANALYSIS_BASE/tasks and hadoop_path output path

job_tag = "WWW_v1.0.8" # Added lepton scale factors
job_tag = "WWW_v1.0.9" # Added lepton scale factors
job_tag = "WWW_v1.0.10" # Added trigger efficiencies
job_tag = "WWW_v1.0.11" # Clean up some varialbes and turn on the met filters
job_tag = "WWW_v1.0.12" # Zpeak window fixed to 20, pt requirements on leptons
job_tag = "WWW_v1.0.13" # Switch to reliso03 0.4
job_tag = "WWW_v1.0.14" # Added matched jet pt different corrections only for ttbar and www
job_tag = "WWW_v1.0.15" # Redefined a mixed ptratio/reliso isolation for better modeling
job_tag = "WWW_v1.0.16" # Added ptratioEA Incorrectly ran over with v3 id which are not what i want
job_tag = "WWW_v1.0.17" # Failed Campaign
job_tag = "WWW_v1.0.18" # Failed Campaign
job_tag = "WWW_v1.0.19" # v3 id with two ptratio cut values for electron and muons
job_tag = "WWW_v1.0.20" # v3 id with two ptratio cut values for electron and muons and OS events saved as well
job_tag = "WWW_v1.0.21" # v4 id place holder with fake and veto set to relisolep 1.4 cut value but the tight is somewhat aribtrary.
job_tag = "WWW_v1.0.22" # v4 id with new sf new trigeff new fakerate (seemed bugged)
job_tag = "WWW_v1.0.23" # v4 id with new sf new trigeff new fakerate (conecorrpt bugged)
job_tag = "WWW_v1.0.23.patch1" # v4 id with new sf new trigeff new fakerate (conecorrpt fixed, submitted W/ttbar only) 
job_tag = "WWW_v1.0.24" # isTightPOG variable added to check for modeling issue
job_tag = "WWW_v1.0.25" # Added smearing and fakerate, took out a few unnecessary variables, had buggy fakerate
job_tag = "WWW_v1.0.26" # Resubmitting 25 with ffwgt variable fixed Also the tight and loose pt cuts are adjusted in preselection and counting
job_tag = "WWW_v1.0.27" # Failed campaign
job_tag = "WWW_v1.0.28" # B-tagging loose v. medium scale factor fix. ffwgt error fixed. closure error added. tight ss pt changed to 25.
job_tag = "WWW_v1.0.29" # There was a bug that got created due to veto leptons being included in the lepton container.

#job_tag = "WWW_v1.1.0" # Including single leptons with QCD samples (W, ttbar, QCD only) version for closure
#job_tag = "WWW_v1.1.1" # Included MediumPOG ID (W, ttbar, QCD only) for closure
#job_tag = "WWW_v1.1.2" # W, ttbar, QCD, data, WW, WZ for full fake rate study (auxiliary trigger added)
#job_tag = "WWW_v1.1.4" # W, ttbar, WW, WZ for reprocessing single lepton events

job_tag = "WWW_v1.2.1" # CMS4 2016 data for comparison
job_tag = "WWW_v1.2.2" # Fat jet included!

###################################################################################################################
###################################################################################################################
# Below are the Metis submission code that users do not have to care about.
###################################################################################################################
###################################################################################################################

import time
import json
import metis

from time import sleep

from metis.Sample import DirectorySample
from metis.CondorTask import CondorTask

from metis.StatsParser import StatsParser

import sys
import os
import glob
import subprocess

# Will be using dis_client
import sys
sys.path.append('/home/users/phchang/public_html/makers/disMaker')
import dis_client
import json

samples = [

###############################################################################
# CMS4
###############################################################################
# Data
"/DoubleEG/Run2016B-03Feb2017_ver1-v2/CMS4" ,
"/DoubleEG/Run2016B-03Feb2017_ver2-v2/CMS4" ,
"/DoubleEG/Run2016C-03Feb2017-v1/CMS4" ,
"/DoubleEG/Run2016D-03Feb2017-v1/CMS4" ,
"/DoubleEG/Run2016E-03Feb2017-v1/CMS4" ,
"/DoubleEG/Run2016F-03Feb2017-v1/CMS4" ,
"/DoubleEG/Run2016G-03Feb2017-v1/CMS4" ,
"/DoubleEG/Run2016H-03Feb2017_ver2-v1/CMS4" ,
"/DoubleEG/Run2016H-03Feb2017_ver3-v1/CMS4" ,

"/DoubleMuon/Run2016B-03Feb2017_ver1-v2/CMS4" ,
"/DoubleMuon/Run2016B-03Feb2017_ver2-v2/CMS4" ,
"/DoubleMuon/Run2016C-03Feb2017-v1/CMS4" ,
"/DoubleMuon/Run2016D-03Feb2017-v1/CMS4" ,
"/DoubleMuon/Run2016E-03Feb2017-v1/CMS4" ,
"/DoubleMuon/Run2016F-03Feb2017-v1/CMS4" ,
"/DoubleMuon/Run2016G-03Feb2017-v1/CMS4" ,
"/DoubleMuon/Run2016H-03Feb2017_ver2-v1/CMS4" ,
"/DoubleMuon/Run2016H-03Feb2017_ver3-v1/CMS4" ,

"/MuonEG/Run2016B-03Feb2017_ver1-v2/CMS4" ,
"/MuonEG/Run2016B-03Feb2017_ver2-v2/CMS4" ,
"/MuonEG/Run2016C-03Feb2017-v1/CMS4" ,
"/MuonEG/Run2016D-03Feb2017-v1/CMS4" ,
"/MuonEG/Run2016E-03Feb2017-v1/CMS4" ,
"/MuonEG/Run2016F-03Feb2017-v1/CMS4" ,
"/MuonEG/Run2016G-03Feb2017-v1/CMS4" ,
"/MuonEG/Run2016H-03Feb2017_ver2-v1/CMS4" ,
"/MuonEG/Run2016H-03Feb2017_ver3-v1/CMS4" ,

"/PrivateWWW/www-cms4-Private80X-v1/MINIAODSIM" ,
"/PrivateWWW/wwwext-cms4-Private80X-v1/MINIAODSIM" ,

"/SMS-TChiWH_WToLNu_HToVVTauTau_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM",
"/SMS-TChiHH_HToWWZZTauTau_HToWWZZTauTau_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v2/MINIAODSIM",

"/DoublyChargedHiggsGMmodel_HWW_M200_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM",
"/DoublyChargedHiggsGMmodel_HWW_M300_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM",
"/DoublyChargedHiggsGMmodel_HWW_M400_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM",
"/DoublyChargedHiggsGMmodel_HWW_M500_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM",
"/DoublyChargedHiggsGMmodel_HWW_M600_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM",
"/DoublyChargedHiggsGMmodel_HWW_M900_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM",
"/DoublyChargedHiggsGMmodel_HWW_M1000_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM",
"/DoublyChargedHiggsGMmodel_HWW_M1500_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM",
"/DoublyChargedHiggsGMmodel_HWW_M2000_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM",

"/WprimeToWHToWlepHinc_narrow_M-600_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
"/WprimeToWHToWlepHinc_narrow_M-800_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
"/WprimeToWHToWlepHinc_narrow_M-1000_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
"/WprimeToWHToWlepHinc_narrow_M-1200_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
"/WprimeToWHToWlepHinc_narrow_M-1400_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
"/WprimeToWHToWlepHinc_narrow_M-1600_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
"/WprimeToWHToWlepHinc_narrow_M-1800_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
"/WprimeToWHToWlepHinc_narrow_M-2000_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
"/WprimeToWHToWlepHinc_narrow_M-2500_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
"/WprimeToWHToWlepHinc_narrow_M-3500_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
"/WprimeToWHToWlepHinc_narrow_M-4000_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
"/WprimeToWHToWlepHinc_narrow_M-4500_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
"/WprimeToWHToWlepHinc_narrow_M-5000_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
"/WprimeToWHToWlepHinc_narrow_M-5500_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
"/WprimeToWHToWlepHinc_narrow_M-6000_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",


###############################################################################
# CMS3
###############################################################################
## Private from Mia
#"/TEST-www/www-Private80X-v1/USER" ,
#"/TEST-www/wwwext-Private80X-v1/USER" ,
#
## Data
#"/DoubleEG/Run2016B-03Feb2017_ver2-v2/CMS3" ,
#"/DoubleEG/Run2016C-03Feb2017-v1/CMS3" ,
#"/DoubleEG/Run2016D-03Feb2017-v1/CMS3" ,
#"/DoubleEG/Run2016E-03Feb2017-v1/CMS3" ,
#"/DoubleEG/Run2016F-03Feb2017-v1/CMS3" ,
#"/DoubleEG/Run2016G-03Feb2017-v1/CMS3" ,
#"/DoubleEG/Run2016H-03Feb2017_ver2-v1/CMS3" ,
#"/DoubleEG/Run2016H-03Feb2017_ver3-v1/CMS3" ,
#
#"/DoubleMuon/Run2016B-03Feb2017_ver2-v2/CMS3" ,
#"/DoubleMuon/Run2016C-03Feb2017-v1/CMS3" ,
#"/DoubleMuon/Run2016D-03Feb2017-v1/CMS3" ,
#"/DoubleMuon/Run2016E-03Feb2017-v1/CMS3" ,
#"/DoubleMuon/Run2016F-03Feb2017-v1/CMS3" ,
#"/DoubleMuon/Run2016G-03Feb2017-v1/CMS3" ,
#"/DoubleMuon/Run2016H-03Feb2017_ver2-v1/CMS3" ,
#"/DoubleMuon/Run2016H-03Feb2017_ver3-v1/CMS3" ,
#
#"/MuonEG/Run2016B-03Feb2017_ver2-v2/CMS3" ,
#"/MuonEG/Run2016C-03Feb2017-v1/CMS3" ,
#"/MuonEG/Run2016D-03Feb2017-v1/CMS3" ,
#"/MuonEG/Run2016E-03Feb2017-v1/CMS3" ,
#"/MuonEG/Run2016F-03Feb2017-v1/CMS3" ,
#"/MuonEG/Run2016G-03Feb2017-v1/CMS3" ,
#"/MuonEG/Run2016H-03Feb2017_ver2-v1/CMS3" ,
#"/MuonEG/Run2016H-03Feb2017_ver3-v1/CMS3" ,

# ttbar
"/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM" ,
"/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM" ,
"/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM" ,

# single top
"/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,
"/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,
"/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,
"/ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,
"/ST_tW_antitop_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,
"/tZq_ll_4f_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM" ,
"/ST_tWll_5f_LO_13TeV-MadGraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,

# diboson
"/WWTo2L2Nu_13TeV-powheg/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,
"/WWToLNuQQ_13TeV-powheg/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,
"/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v3/MINIAODSIM" ,
"/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,
"/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,
"/WWTo2L2Nu_DoubleScattering_13TeV-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,
"/EWKWPlus2Jets_WToLNu_M-50_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,
"/EWKZ2Jets_ZToLL_M-50_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,
"/EWKWMinus2Jets_WToLNu_M-50_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,
"/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,
"/ZZTo2L2Nu_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,
"/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,
"/ZZTo2Q2Nu_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,
"/ZZTo4L_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,

# ttV
"/ttZJets_13TeV_madgraphMLM/RunIISummer16MiniAODv2-80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,
"/ttWJets_13TeV_madgraphMLM/RunIISummer16MiniAODv2-80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,
"/ttHTobb_M125_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,
"/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,

# ewk gamma contamination
"/WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,
"/WGstarToLNuMuMu_012Jets_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,
"/WGstarToLNuEE_012Jets_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,
"/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM" ,
"/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,

# triboson
"/WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,
"/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,
"/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,
"/WZG_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,
"/WWG_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM" ,

# Higgs
"/VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,

# Wjets
"/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,
"/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM" ,
"/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM" ,
"/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM" ,
"/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM" ,
"/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM" ,
"/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,
"/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM" ,

# DYToLL
"/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,
"/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v2/MINIAODSIM" ,
"/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM" ,
"/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM" ,
"/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM" ,
"/DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM" ,
"/DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,
"/DYJetsToLL_M-50_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,
"/DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" ,

]


samples_short_name = {

###############################################################################
# CMS4
###############################################################################
# Data
"/DoubleEG/Run2016B-03Feb2017_ver1-v2/CMS4"                                                                                                                                     : "data_Run2016B_03feb2017rereco_unmerged_ee_v1",
"/DoubleMuon/Run2016B-03Feb2017_ver1-v2/CMS4"                                                                                                                                   : "data_Run2016B_03feb2017rereco_unmerged_mm_v1",
"/DoubleEG/Run2016B-03Feb2017_ver2-v2/CMS4"                                                                                                                                     : "data_Run2016B_03feb2017rereco_unmerged_ee_v2",
"/DoubleMuon/Run2016B-03Feb2017_ver2-v2/CMS4"                                                                                                                                   : "data_Run2016B_03feb2017rereco_unmerged_mm_v2",
"/DoubleEG/Run2016C-03Feb2017-v1/CMS4"                                                                                                                                          : "data_Run2016C_03feb2017rereco_unmerged_ee_v1",
"/DoubleMuon/Run2016C-03Feb2017-v1/CMS4"                                                                                                                                        : "data_Run2016C_03feb2017rereco_unmerged_mm_v1",
"/DoubleEG/Run2016D-03Feb2017-v1/CMS4"                                                                                                                                          : "data_Run2016D_03feb2017rereco_unmerged_ee_v1",
"/DoubleMuon/Run2016D-03Feb2017-v1/CMS4"                                                                                                                                        : "data_Run2016D_03feb2017rereco_unmerged_mm_v1",
"/DoubleEG/Run2016E-03Feb2017-v1/CMS4"                                                                                                                                          : "data_Run2016E_03feb2017rereco_unmerged_ee_v1",
"/DoubleMuon/Run2016E-03Feb2017-v1/CMS4"                                                                                                                                        : "data_Run2016E_03feb2017rereco_unmerged_mm_v1",
"/DoubleEG/Run2016F-03Feb2017-v1/CMS4"                                                                                                                                          : "data_Run2016F_03feb2017rereco_unmerged_ee_v1",
"/DoubleMuon/Run2016F-03Feb2017-v1/CMS4"                                                                                                                                        : "data_Run2016F_03feb2017rereco_unmerged_mm_v1",
"/DoubleEG/Run2016G-03Feb2017-v1/CMS4"                                                                                                                                          : "data_Run2016G_03feb2017rereco_unmerged_ee_v1",
"/DoubleMuon/Run2016G-03Feb2017-v1/CMS4"                                                                                                                                        : "data_Run2016G_03feb2017rereco_unmerged_mm_v1",
"/DoubleEG/Run2016H-03Feb2017_ver2-v1/CMS4"                                                                                                                                     : "data_Run2016H_03feb2017rereco_unmerged_ee_v2",
"/DoubleEG/Run2016H-03Feb2017_ver3-v1/CMS4"                                                                                                                                     : "data_Run2016H_03feb2017rereco_unmerged_ee_v3",
"/DoubleMuon/Run2016H-03Feb2017_ver2-v1/CMS4"                                                                                                                                   : "data_Run2016H_03feb2017rereco_unmerged_mm_v2",
"/DoubleMuon/Run2016H-03Feb2017_ver3-v1/CMS4"                                                                                                                                   : "data_Run2016H_03feb2017rereco_unmerged_mm_v3",
"/MuonEG/Run2016B-03Feb2017_ver1-v2/CMS4"                                                                                                                                       : "data_Run2016B_03feb2017rereco_unmerged_em_v1",
"/MuonEG/Run2016B-03Feb2017_ver2-v2/CMS4"                                                                                                                                       : "data_Run2016B_03feb2017rereco_unmerged_em_v2",
"/MuonEG/Run2016C-03Feb2017-v1/CMS4"                                                                                                                                            : "data_Run2016C_03feb2017rereco_unmerged_em_v1",
"/MuonEG/Run2016D-03Feb2017-v1/CMS4"                                                                                                                                            : "data_Run2016D_03feb2017rereco_unmerged_em_v1",
"/MuonEG/Run2016E-03Feb2017-v1/CMS4"                                                                                                                                            : "data_Run2016E_03feb2017rereco_unmerged_em_v1",
"/MuonEG/Run2016F-03Feb2017-v1/CMS4"                                                                                                                                            : "data_Run2016F_03feb2017rereco_unmerged_em_v1",
"/MuonEG/Run2016G-03Feb2017-v1/CMS4"                                                                                                                                            : "data_Run2016G_03feb2017rereco_unmerged_em_v1",
"/MuonEG/Run2016H-03Feb2017_ver2-v1/CMS4"                                                                                                                                       : "data_Run2016H_03feb2017rereco_unmerged_em_v2",
"/MuonEG/Run2016H-03Feb2017_ver3-v1/CMS4"                                                                                                                                       : "data_Run2016H_03feb2017rereco_unmerged_em_v3",


###############################################################################
# CMS3
###############################################################################
# Private from Mia
"/TEST-www/www-Private80X-v1/USER"                                                                                                                                              : "www_2l_mia",
"/TEST-www/wwwext-Private80X-v1/USER"                                                                                                                                           : "www_2l_ext1_mia",

"/PrivateWWW/www-cms4-Private80X-v1/MINIAODSIM"                                                                                                                                 : "www_2l_mia",
"/PrivateWWW/wwwext-cms4-Private80X-v1/MINIAODSIM"                                                                                                                              : "www_2l_ext1_mia",
"/SMS-TChiWH_WToLNu_HToVVTauTau_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"             : "whsusy_fullscan",
"/SMS-TChiHH_HToWWZZTauTau_HToWWZZTauTau_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v2/MINIAODSIM"    : "hhsusy_fullscan",

# Data
"/DoubleEG/Run2016B-03Feb2017_ver2-v2/CMS3"                                                                                                                                     : "data_Run2016B_03feb2017rereco_unmerged_ee_v2",
"/DoubleMuon/Run2016B-03Feb2017_ver2-v2/CMS3"                                                                                                                                   : "data_Run2016B_03feb2017rereco_unmerged_mm_v2",
"/DoubleEG/Run2016C-03Feb2017-v1/CMS3"                                                                                                                                          : "data_Run2016C_03feb2017rereco_unmerged_ee_v1",
"/DoubleMuon/Run2016C-03Feb2017-v1/CMS3"                                                                                                                                        : "data_Run2016C_03feb2017rereco_unmerged_mm_v1",
"/DoubleEG/Run2016D-03Feb2017-v1/CMS3"                                                                                                                                          : "data_Run2016D_03feb2017rereco_unmerged_ee_v1",
"/DoubleMuon/Run2016D-03Feb2017-v1/CMS3"                                                                                                                                        : "data_Run2016D_03feb2017rereco_unmerged_mm_v1",
"/DoubleEG/Run2016E-03Feb2017-v1/CMS3"                                                                                                                                          : "data_Run2016E_03feb2017rereco_unmerged_ee_v1",
"/DoubleMuon/Run2016E-03Feb2017-v1/CMS3"                                                                                                                                        : "data_Run2016E_03feb2017rereco_unmerged_mm_v1",
"/DoubleEG/Run2016F-03Feb2017-v1/CMS3"                                                                                                                                          : "data_Run2016F_03feb2017rereco_unmerged_ee_v1",
"/DoubleMuon/Run2016F-03Feb2017-v1/CMS3"                                                                                                                                        : "data_Run2016F_03feb2017rereco_unmerged_mm_v1",
"/DoubleEG/Run2016G-03Feb2017-v1/CMS3"                                                                                                                                          : "data_Run2016G_03feb2017rereco_unmerged_ee_v1",
"/DoubleMuon/Run2016G-03Feb2017-v1/CMS3"                                                                                                                                        : "data_Run2016G_03feb2017rereco_unmerged_mm_v1",
"/DoubleEG/Run2016H-03Feb2017_ver2-v1/CMS3"                                                                                                                                     : "data_Run2016H_03feb2017rereco_unmerged_ee_v2",
"/DoubleEG/Run2016H-03Feb2017_ver3-v1/CMS3"                                                                                                                                     : "data_Run2016H_03feb2017rereco_unmerged_ee_v3",
"/DoubleMuon/Run2016H-03Feb2017_ver2-v1/CMS3"                                                                                                                                   : "data_Run2016H_03feb2017rereco_unmerged_mm_v2",
"/DoubleMuon/Run2016H-03Feb2017_ver3-v1/CMS3"                                                                                                                                   : "data_Run2016H_03feb2017rereco_unmerged_mm_v3",
"/MuonEG/Run2016B-03Feb2017_ver2-v2/CMS3"                                                                                                                                       : "data_Run2016B_03feb2017rereco_unmerged_em_v2",
"/MuonEG/Run2016C-03Feb2017-v1/CMS3"                                                                                                                                            : "data_Run2016C_03feb2017rereco_unmerged_em_v1",
"/MuonEG/Run2016D-03Feb2017-v1/CMS3"                                                                                                                                            : "data_Run2016D_03feb2017rereco_unmerged_em_v1",
"/MuonEG/Run2016E-03Feb2017-v1/CMS3"                                                                                                                                            : "data_Run2016E_03feb2017rereco_unmerged_em_v1",
"/MuonEG/Run2016F-03Feb2017-v1/CMS3"                                                                                                                                            : "data_Run2016F_03feb2017rereco_unmerged_em_v1",
"/MuonEG/Run2016G-03Feb2017-v1/CMS3"                                                                                                                                            : "data_Run2016G_03feb2017rereco_unmerged_em_v1",
"/MuonEG/Run2016H-03Feb2017_ver2-v1/CMS3"                                                                                                                                       : "data_Run2016H_03feb2017rereco_unmerged_em_v2",
"/MuonEG/Run2016H-03Feb2017_ver3-v1/CMS3"                                                                                                                                       : "data_Run2016H_03feb2017rereco_unmerged_em_v3",

# ttbar
"/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                  : "ttbar_1ltop_mgmlm_ext1",
"/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"               : "ttbar_1ltbr_mgmlm_ext1",
"/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                           : "ttbar_dilep_mgmlm_ext1",
# single top
"/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" : "stt_antitop_incdec_powheg",
"/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"     : "stt_top_incdec_powheg",
"/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                    : "sts_4f_leptonic_amcnlo",
"/ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                        : "sttw_top_nofullhaddecay_powheg",
"/ST_tW_antitop_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                    : "sttw_antitop_nofullhaddecay_powheg",
"/tZq_ll_4f_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                                               : "tzq_ll_amcnlo",
"/ST_tWll_5f_LO_13TeV-MadGraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                : "sttwll_madgraph",

# diboson
"/WWTo2L2Nu_13TeV-powheg/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                              : "ww_2l2nu_powheg",
"/WWToLNuQQ_13TeV-powheg/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                              : "ww_lnuqq_powheg",
"/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v3/MINIAODSIM"                                      : "wz_lnqq_amcnlo",
"/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                        : "wz_1l3n_amcnlo",
"/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                  : "wpwpjj_ewk-qcd_madgraph",
"/WWTo2L2Nu_DoubleScattering_13TeV-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                            : "ww_2l2nu_dbl_scat",
"/EWKWPlus2Jets_WToLNu_M-50_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                    : "Wpjj_lnu_madgraph",
"/EWKZ2Jets_ZToLL_M-50_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                         : "Zjj_m50_madgraph",
"/EWKWMinus2Jets_WToLNu_M-50_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                   : "Wmjj_lnu_madgraph",
"/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                          : "wz_3lnu_powheg",
"/ZZTo2L2Nu_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                      : "zz_2l2n_powheg",
"/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                         : "zz_2l2q_powheg",
"/ZZTo2Q2Nu_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                        : "zz_2q2n_amcnlo",
"/ZZTo4L_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                         : "zz_4l_powheg",
# ttV
"/ttZJets_13TeV_madgraphMLM/RunIISummer16MiniAODv2-80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                                       : "ttz_incl_mgmlm",
"/ttWJets_13TeV_madgraphMLM/RunIISummer16MiniAODv2-80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                                       : "ttw_incl_mgmlm",
"/ttHTobb_M125_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                   : "tth_bb_powheg",
"/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                       : "tth_nonbb_powheg",
# ewk gamma contamination
"/WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                     : "wgjets_incl_mgmlm",
"/WGstarToLNuMuMu_012Jets_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                              : "wgstar_lnmm_012jets_madgraph",
"/WGstarToLNuEE_012Jets_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                : "wgstar_lnee_012jets_madgraph",
"/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                                : "zgamma_2lG_amc",
"/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                             : "ttg_incl_amcnlo",
# triboson
"/WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                             : "wwz_incl_amcnlo",
"/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                             : "wzz_incl_amcnlo",
"/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                             : "zzz_incl_amcnlo",
"/WZG_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                             : "wzg_incl_amcnlo",
"/WWG_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                                        : "wwg_incl_amcnlo",
# Higgs
"/VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                   : "vh_nonbb_amcnlo",

# Wjets
"/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                   : "wjets_incl_mgmlm",
"/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                  : "wjets_ht100_mgmlm_ext1",
"/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                  : "wjets_ht200_mgmlm_ext1",
"/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                  : "wjets_ht400_mgmlm_ext1",
"/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                  : "wjets_ht600_mgmlm_ext1",
"/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                 : "wjets_ht800_mgmlm_ext1",
"/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                     : "wjets_ht1200_mgmlm_nonext",
"/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                 : "wjets_ht2500_mgmlm_ext1",
# DYToLL
"/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                          : "dy_m1050_mgmlm",
"/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v2/MINIAODSIM"                         : "dy_m50_mgmlm_ext1",
"/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"             : "dy_m50_mgmlm_ht100_ext1",
"/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"             : "dy_m50_mgmlm_ht200_ext1",
"/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"             : "dy_m50_mgmlm_ht400_ext1",
"/DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM"                  : "dy_m50_mgmlm_ht600_nonext",
"/DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                 : "dy_m50_mgmlm_ht800_nonext",
"/DYJetsToLL_M-50_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                : "dy_m50_mgmlm_ht1200_nonext",
"/DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                 : "dy_m50_mgmlm_ht2500_nonext",

# BSM
"/DoublyChargedHiggsGMmodel_HWW_M200_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM"  : "hpmpm_m200",
"/DoublyChargedHiggsGMmodel_HWW_M300_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM"  : "hpmpm_m300",
"/DoublyChargedHiggsGMmodel_HWW_M400_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM"  : "hpmpm_m400",
"/DoublyChargedHiggsGMmodel_HWW_M500_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM"  : "hpmpm_m500",
"/DoublyChargedHiggsGMmodel_HWW_M600_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM"  : "hpmpm_m600",
"/DoublyChargedHiggsGMmodel_HWW_M900_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM"  : "hpmpm_m900",
"/DoublyChargedHiggsGMmodel_HWW_M1000_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM" : "hpmpm_m1000",
"/DoublyChargedHiggsGMmodel_HWW_M1500_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM" : "hpmpm_m1500",
"/DoublyChargedHiggsGMmodel_HWW_M2000_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM" : "hpmpm_m2000",

"/WprimeToWHToWlepHinc_narrow_M-600_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" : "wprime_m600",
"/WprimeToWHToWlepHinc_narrow_M-800_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" : "wprime_m800",
"/WprimeToWHToWlepHinc_narrow_M-1000_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" : "wprime_m1000",
"/WprimeToWHToWlepHinc_narrow_M-1200_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" : "wprime_m1200",
"/WprimeToWHToWlepHinc_narrow_M-1400_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" : "wprime_m1400",
"/WprimeToWHToWlepHinc_narrow_M-1600_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" : "wprime_m1600",
"/WprimeToWHToWlepHinc_narrow_M-1800_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" : "wprime_m1800",
"/WprimeToWHToWlepHinc_narrow_M-2000_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" : "wprime_m2000",
"/WprimeToWHToWlepHinc_narrow_M-2500_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" : "wprime_m2500",
"/WprimeToWHToWlepHinc_narrow_M-3500_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" : "wprime_m3500",
"/WprimeToWHToWlepHinc_narrow_M-4000_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" : "wprime_m4000",
"/WprimeToWHToWlepHinc_narrow_M-4500_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" : "wprime_m4500",
"/WprimeToWHToWlepHinc_narrow_M-5000_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" : "wprime_m5000",
"/WprimeToWHToWlepHinc_narrow_M-5500_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" : "wprime_m5500",
"/WprimeToWHToWlepHinc_narrow_M-6000_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" : "wprime_m6000",

### Extra samples
#"/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_HCALDebug_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                   : "dy_m50_amcnlo",
#"/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                              : "ttbar_incl_powheg",
#"/WW_TuneCUETP8M1_13TeV-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                       : "ww_incl_pythia",
#"/WZ_TuneCUETP8M1_13TeV-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                       : "wz_incl_pythia",

#"/QCD_Pt_15to20_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_v1"         :  "qcd_mu_pt15", 
#"/QCD_Pt_20to30_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_v1"         :  "qcd_mu_pt20", 
#"/QCD_Pt_30to50_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_v1"         :  "qcd_mu_pt30", 
#"/QCD_Pt_50to80_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_v1"         :  "qcd_mu_pt50", 
#"/QCD_Pt_80to120_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1_v3"   :  "qcd_mu_pt80", 
#"/QCD_Pt_120to170_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_v1"       :  "qcd_mu_pt120", 
#"/QCD_Pt_170to300_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1_v1"  :  "qcd_mu_pt170", 
#"/QCD_Pt_300to470_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2_v1"  :  "qcd_mu_pt300", 
#"/QCD_Pt_470to600_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1_v1"  :  "qcd_mu_pt470", 
#"/QCD_Pt_600to800_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_v1"       :  "qcd_mu_pt600", 
#"/QCD_Pt_800to1000_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_v1"      :  "qcd_mu_pt800", 
#"/QCD_Pt_1000toInf_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1_v3" :  "qcd_mu_pt1000", 
#"/QCD_Pt_20to30_EMEnriched_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_v1"            :  "qcd_em_pt20", 
#"/QCD_Pt_30to50_EMEnriched_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1_v1"       :  "qcd_em_pt30", 
#"/QCD_Pt_50to80_EMEnriched_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1_v1"       :  "qcd_em_pt50", 
#"/QCD_Pt_80to120_EMEnriched_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1_v1"      :  "qcd_em_pt80", 
#"/QCD_Pt_120to170_EMEnriched_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1_v1"     :  "qcd_em_pt120", 
#"/QCD_Pt_170to300_EMEnriched_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_v1"          :  "qcd_em_pt170", 
#"/QCD_Pt_300toInf_EMEnriched_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_v1"          :  "qcd_em_pt300", 
#"/QCD_Pt_15to20_bcToE_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_v1"                 :  "qcd_bctoe_pt15", 
#"/QCD_Pt_20to30_bcToE_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_v1"                 :  "qcd_bctoe_pt20", 
#"/QCD_Pt_30to80_bcToE_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_v1"                 :  "qcd_bctoe_pt30", 
#"/QCD_Pt_80to170_bcToE_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_backup_80X_mcRun2_asymptotic_2016_TrancheIV_v6_v1"         :  "qcd_bctoe_pt80", 
#"/QCD_Pt_170to250_bcToE_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_v1"               :  "qcd_bctoe_pt170", 
#"/QCD_Pt_250toInf_bcToE_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_v1"               :  "qcd_bctoe_pt250", 


## Not used samples

#"/TEST-tth/tth-Private80X-v1/USER"                                                                                                                                              : "tth_mia",
#"/WmWmJJ_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                         : "wmwm_powheg",
#"/ZNuNuGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                       : "znunugamma_ptg40_mgmlm",
#"/ZNuNuGJets_MonoPhoton_PtG-130_TuneCUETP8M1_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                           : "znunugamma_ptg130_mgmlm",

#"/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                               : "wgjets_incl_amcnlo",
#"/WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                           : "wgjets_ptg40_mgmlm",
#"/WGJets_MonoPhoton_PtG-130_TuneCUETP8M1_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                               : "wgjets_ptg130_mgmlm",

#"/WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                          : "www_incl_amcnlo",

#"/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                 : "ggH_4l_powheg",
#"/WminusH_HToBB_WToLNu_M125_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                                 : "WmH_Hbb_Wln_powheg",
#"/ttH_HToZZ_4LFilter_M125_13TeV_powheg2_JHUgenV6_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                              : "ttH_HZZ4l_powheg",
#"/WplusH_HToBB_WToLNu_M125_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                                  : "WpH_Hbb_Wln_powheg",

#"/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"                   : "ttw_ln_amcnlo_ext2",
#"/TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                         : "ttw_qq_amcnlo",
#"/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                           : "ttz_2l2n_amcnlo",

#"/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                    : "dy_m1050_amcnlo",
#"/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_HCALDebug_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                   : "dy_m50_amcnlo",

#"/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                             : "ttbar_dilep_powheg",
#"/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                       : "ttbar_1ltop_mgmlm_nonext",
#"/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                    : "ttbar_1ltbr_mgmlm_nonext",
#"/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                : "ttbar_dilep_mgmlm_nonext",

### QCD pt-binned EM-enriched (to be added)
#"/QCD_Pt-20to30_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                 : "qcdpt20_emenriched_nonext",
#"/QCD_Pt-30to50_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                 : "qcdpt30_emenriched_nonext",
#"/QCD_Pt-30to50_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                            : "qcdpt30_emenriched_ext1",
#"/QCD_Pt-50to80_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                            : "qcdpt50_emenriched_ext1",
#"/QCD_Pt-80to120_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                           : "qcdpt80_emenriched_ext1",
#"/QCD_Pt-170to300_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                               : "qcdpt170_emenriched_nonext",
#"/QCD_Pt-300toInf_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                               : "qcdpt300_emenriched_nonext",
### QCD HT-binned
#"/QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                               : "qcdht100_nonext",
#"/QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                               : "qcdht200_nonext",
#"/QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                          : "qcdht200_ext1",
#"/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                               : "qcdht300_nonext",
#"/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                          : "qcdht300_ext1",
#"/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                               : "qcdht500_nonext",
#"/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v2/MINIAODSIM"                          : "qcdht500_ext1",
#"/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                              : "qcdht700_nonext",
#"/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                         : "qcdht700_ext1",
#"/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                             : "qcdht1000_nonext",
#"/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                        : "qcdht1000_ext1",
#"/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                             : "qcdht1500_nonext",
#"/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                        : "qcdht1500_ext1",
#"/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                              : "qcdht2000_nonext",
#"/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                         : "qcdht2000_ext1",
### GJets dr0p4
#"/GJets_DR-0p4_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_qcut19_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"               : "gjetsht40_dr0p4_mgmlm",
#"/GJets_DR-0p4_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_qcut19_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"              : "gjetsht100_dr0p4_mgmlm",
#"/GJets_DR-0p4_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_qcut19_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"              : "gjetsht200_dr0p4_mgmlm",
#"/GJets_DR-0p4_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_qcut19_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"              : "gjetsht400_dr0p4_mgmlm",
#"/GJets_DR-0p4_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_qcut19_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"              : "gjetsht600_dr0p4_mgmlm",
### GJets dr0p05
#"/GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                        : "gjetsht40_dr0p05_mgmlm_ext1",
#"/GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                            : "gjetsht100_dr0p05_mgmlm_nonext",
#"/GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                       : "gjetsht200_dr0p05_mgmlm_ext1",
#"/GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                            : "gjetsht400_dr0p05_mgmlm_nonext",
#"/GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                            : "gjetsht600_dr0p05_mgmlm_nonext",
#"/GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                       : "gjetsht600_dr0p05_mgmlm_ext1",
# missing        ""                                                                                                                                                             : "wz_2l2q_amcnlo",
# missing        "/TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                : "ttz_qq_amcnlo",
#        "/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                            : "tttt_amcnlo",
# buggy        "/TTGamma_SingleLeptFromT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"   : "ttg_1ltop_mgmlm",
# buggy        "/TTGamma_SingleLeptFromTbar_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM": "ttg_1ltbr_mgmlm",
# buggy        "/TTGamma_Dilept_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"            : "ttg_dilep_mgmlm",
}

dslocscms4 = {

###############################################################################
# CMS4
###############################################################################
"/DoubleEG/Run2016B-03Feb2017_ver1-v2/CMS4"                                                                                                                                     : "/hadoop/cms/store/group/snt/run2_data2016//DoubleEG_Run2016B-03Feb2017_ver1-v1_MINIAOD_CMS4_V00-00-02_data2016/",
"/DoubleEG/Run2016B-03Feb2017_ver2-v2/CMS4"                                                                                                                                     : "/hadoop/cms/store/group/snt/run2_data2016//DoubleEG_Run2016B-03Feb2017_ver2-v2_MINIAOD_CMS4_V00-00-02_data2016/",
"/DoubleEG/Run2016C-03Feb2017-v1/CMS4"                                                                                                                                          : "/hadoop/cms/store/group/snt/run2_data2016//DoubleEG_Run2016C-03Feb2017-v1_MINIAOD_CMS4_V00-00-02_data2016/",
"/DoubleEG/Run2016D-03Feb2017-v1/CMS4"                                                                                                                                          : "/hadoop/cms/store/group/snt/run2_data2016//DoubleEG_Run2016D-03Feb2017-v1_MINIAOD_CMS4_V00-00-02_data2016/",
"/DoubleEG/Run2016E-03Feb2017-v1/CMS4"                                                                                                                                          : "/hadoop/cms/store/group/snt/run2_data2016//DoubleEG_Run2016E-03Feb2017-v1_MINIAOD_CMS4_V00-00-02_data2016/",
"/DoubleEG/Run2016F-03Feb2017-v1/CMS4"                                                                                                                                          : "/hadoop/cms/store/group/snt/run2_data2016//DoubleEG_Run2016F-03Feb2017-v1_MINIAOD_CMS4_V00-00-02_data2016/",
"/DoubleEG/Run2016G-03Feb2017-v1/CMS4"                                                                                                                                          : "/hadoop/cms/store/group/snt/run2_data2016//DoubleEG_Run2016G-03Feb2017-v1_MINIAOD_CMS4_V00-00-02_data2016/",
"/DoubleEG/Run2016H-03Feb2017_ver2-v1/CMS4"                                                                                                                                     : "/hadoop/cms/store/group/snt/run2_data2016//DoubleEG_Run2016H-03Feb2017_ver2-v1_MINIAOD_CMS4_V00-00-02_data2016/",
"/DoubleEG/Run2016H-03Feb2017_ver3-v1/CMS4"                                                                                                                                     : "/hadoop/cms/store/group/snt/run2_data2016//DoubleEG_Run2016H-03Feb2017_ver3-v1_MINIAOD_CMS4_V00-00-02_data2016/",
"/MuonEG/Run2016B-03Feb2017_ver1-v2/CMS4"                                                                                                                                       : "/hadoop/cms/store/group/snt/run2_data2016//MuonEG_Run2016B-03Feb2017_ver1-v1_MINIAOD_CMS4_V00-00-02_data2016/",
"/MuonEG/Run2016B-03Feb2017_ver2-v2/CMS4"                                                                                                                                       : "/hadoop/cms/store/group/snt/run2_data2016//MuonEG_Run2016B-03Feb2017_ver2-v2_MINIAOD_CMS4_V00-00-02_data2016/",
"/MuonEG/Run2016C-03Feb2017-v1/CMS4"                                                                                                                                            : "/hadoop/cms/store/group/snt/run2_data2016//MuonEG_Run2016C-03Feb2017-v1_MINIAOD_CMS4_V00-00-02_data2016/",
"/MuonEG/Run2016D-03Feb2017-v1/CMS4"                                                                                                                                            : "/hadoop/cms/store/group/snt/run2_data2016//MuonEG_Run2016D-03Feb2017-v1_MINIAOD_CMS4_V00-00-02_data2016/",
"/MuonEG/Run2016E-03Feb2017-v1/CMS4"                                                                                                                                            : "/hadoop/cms/store/group/snt/run2_data2016//MuonEG_Run2016E-03Feb2017-v1_MINIAOD_CMS4_V00-00-02_data2016/",
"/MuonEG/Run2016F-03Feb2017-v1/CMS4"                                                                                                                                            : "/hadoop/cms/store/group/snt/run2_data2016//MuonEG_Run2016F-03Feb2017-v1_MINIAOD_CMS4_V00-00-02_data2016/",
"/MuonEG/Run2016G-03Feb2017-v1/CMS4"                                                                                                                                            : "/hadoop/cms/store/group/snt/run2_data2016//MuonEG_Run2016G-03Feb2017-v1_MINIAOD_CMS4_V00-00-02_data2016/",
"/MuonEG/Run2016H-03Feb2017_ver2-v1/CMS4"                                                                                                                                       : "/hadoop/cms/store/group/snt/run2_data2016//MuonEG_Run2016H-03Feb2017_ver2-v1_MINIAOD_CMS4_V00-00-02_data2016/",
"/MuonEG/Run2016H-03Feb2017_ver3-v1/CMS4"                                                                                                                                       : "/hadoop/cms/store/group/snt/run2_data2016//MuonEG_Run2016H-03Feb2017_ver3-v1_MINIAOD_CMS4_V00-00-02_data2016/",
"/DoubleMuon/Run2016B-03Feb2017_ver1-v2/CMS4"                                                                                                                                   : "/hadoop/cms/store/group/snt/run2_data2016//DoubleMuon_Run2016B-03Feb2017_ver1-v1_MINIAOD_CMS4_V00-00-02_data2016/",
"/DoubleMuon/Run2016B-03Feb2017_ver2-v2/CMS4"                                                                                                                                   : "/hadoop/cms/store/group/snt/run2_data2016//DoubleMuon_Run2016B-03Feb2017_ver2-v2_MINIAOD_CMS4_V00-00-02_data2016/",
"/DoubleMuon/Run2016C-03Feb2017-v1/CMS4"                                                                                                                                        : "/hadoop/cms/store/group/snt/run2_data2016//DoubleMuon_Run2016C-03Feb2017-v1_MINIAOD_CMS4_V00-00-02_data2016/",
"/DoubleMuon/Run2016D-03Feb2017-v1/CMS4"                                                                                                                                        : "/hadoop/cms/store/group/snt/run2_data2016//DoubleMuon_Run2016D-03Feb2017-v1_MINIAOD_CMS4_V00-00-02_data2016/",
"/DoubleMuon/Run2016E-03Feb2017-v1/CMS4"                                                                                                                                        : "/hadoop/cms/store/group/snt/run2_data2016//DoubleMuon_Run2016E-03Feb2017-v1_MINIAOD_CMS4_V00-00-02_data2016/",
"/DoubleMuon/Run2016F-03Feb2017-v1/CMS4"                                                                                                                                        : "/hadoop/cms/store/group/snt/run2_data2016//DoubleMuon_Run2016F-03Feb2017-v1_MINIAOD_CMS4_V00-00-02_data2016/",
"/DoubleMuon/Run2016G-03Feb2017-v1/CMS4"                                                                                                                                        : "/hadoop/cms/store/group/snt/run2_data2016//DoubleMuon_Run2016G-03Feb2017-v1_MINIAOD_CMS4_V00-00-02_data2016/",
"/DoubleMuon/Run2016H-03Feb2017_ver2-v1/CMS4"                                                                                                                                   : "/hadoop/cms/store/group/snt/run2_data2016//DoubleMuon_Run2016H-03Feb2017_ver2-v1_MINIAOD_CMS4_V00-00-02_data2016/",
"/DoubleMuon/Run2016H-03Feb2017_ver3-v1/CMS4"                                                                                                                                   : "/hadoop/cms/store/group/snt/run2_data2016//DoubleMuon_Run2016H-03Feb2017_ver3-v1_MINIAOD_CMS4_V00-00-02_data2016/",

"/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                          : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"             : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/DYJetsToLL_M-50_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/DYJetsToLL_M-50_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"             : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                 : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"             : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM"                  : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                 : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v2/MINIAODSIM"                         : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v2_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/EWKWMinus2Jets_WToLNu_M-50_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                   : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/EWKWMinus2Jets_WToLNu_M-50_13TeV-madgraph-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/EWKWPlus2Jets_WToLNu_M-50_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                    : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/EWKWPlus2Jets_WToLNu_M-50_13TeV-madgraph-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/EWKZ2Jets_ZToLL_M-50_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                         : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/EWKZ2Jets_ZToLL_M-50_13TeV-madgraph-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                    : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"     : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/ST_tW_antitop_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                    : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/ST_tW_antitop_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                        : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/ST_tWll_5f_LO_13TeV-MadGraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/ST_tWll_5f_LO_13TeV-MadGraph-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                             : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                              : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                           : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                  : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"               : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                   : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                     : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WGstarToLNuEE_012Jets_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WGstarToLNuEE_012Jets_13TeV-madgraph_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WGstarToLNuMuMu_012Jets_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                              : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WGstarToLNuMuMu_012Jets_13TeV-madgraph_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                  : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                     : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                  : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                 : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                  : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                  : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                 : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                   : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WW_TuneCUETP8M1_13TeV-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                       : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WW_TuneCUETP8M1_13TeV-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WZ_TuneCUETP8M1_13TeV-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                       : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WZ_TuneCUETP8M1_13TeV-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WWG_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                                        : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WWG_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WWTo2L2Nu_13TeV-powheg/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                              : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WWTo2L2Nu_13TeV-powheg_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WWTo2L2Nu_DoubleScattering_13TeV-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                            : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WWTo2L2Nu_DoubleScattering_13TeV-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WWToLNuQQ_13TeV-powheg/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                              : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WWToLNuQQ_13TeV-powheg_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                             : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WZG_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                             : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WZG_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v3/MINIAODSIM"                                      : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v3_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                        : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                          : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                             : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                  : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                                : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/ZZTo2L2Nu_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                      : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/ZZTo2L2Nu_13TeV_powheg_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                         : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/ZZTo2Q2Nu_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                        : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/ZZTo2Q2Nu_13TeV_amcatnloFXFX_madspin_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/ZZTo4L_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                         : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/ZZTo4L_13TeV_powheg_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                             : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/tZq_ll_4f_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                                               : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/tZq_ll_4f_13TeV-amcatnlo-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                       : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/ttHTobb_M125_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                   : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/ttHTobb_M125_13TeV_powheg_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/ttWJets_13TeV_madgraphMLM/RunIISummer16MiniAODv2-80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                                       : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/ttWJets_13TeV_madgraphMLM_RunIISummer16MiniAODv2-80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/ttZJets_13TeV_madgraphMLM/RunIISummer16MiniAODv2-80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                                       : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/ttZJets_13TeV_madgraphMLM_RunIISummer16MiniAODv2-80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                              : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_HCALDebug_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                   : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISummer16MiniAODv2-PUMoriond17_HCALDebug_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/QCD_Pt-15to20_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                              : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/QCD_Pt-15to20_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/QCD_Pt-20to30_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                              : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/QCD_Pt-20to30_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/QCD_Pt-30to50_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                              : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/QCD_Pt-30to50_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/QCD_Pt-50to80_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                              : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/QCD_Pt-50to80_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/QCD_Pt-80to120_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v3/MINIAODSIM"                        : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/QCD_Pt-80to120_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v3_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/QCD_Pt-120to170_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                            : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/QCD_Pt-120to170_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/QCD_Pt-170to300_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                       : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/QCD_Pt-170to300_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/QCD_Pt-300to470_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"                       : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/QCD_Pt-300to470_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/QCD_Pt-470to600_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                       : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/QCD_Pt-470to600_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/QCD_Pt-600to800_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                            : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/QCD_Pt-600to800_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/QCD_Pt-800to1000_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                           : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/QCD_Pt-800to1000_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/QCD_Pt-1000toInf_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v3/MINIAODSIM"                      : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/QCD_Pt-1000toInf_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v3_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/QCD_Pt-20to30_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                 : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/QCD_Pt-20to30_EMEnriched_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/QCD_Pt-30to50_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                            : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/QCD_Pt-30to50_EMEnriched_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/QCD_Pt-50to80_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                            : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/QCD_Pt-50to80_EMEnriched_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/QCD_Pt-80to120_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                           : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/QCD_Pt-80to120_EMEnriched_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/QCD_Pt-120to170_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                          : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/QCD_Pt-120to170_EMEnriched_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/QCD_Pt-170to300_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                               : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/QCD_Pt-170to300_EMEnriched_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/QCD_Pt-300toInf_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                               : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/QCD_Pt-300toInf_EMEnriched_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/QCD_Pt_15to20_bcToE_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                      : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/QCD_Pt_15to20_bcToE_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/QCD_Pt_20to30_bcToE_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                      : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/QCD_Pt_20to30_bcToE_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/QCD_Pt_30to80_bcToE_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                      : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/QCD_Pt_30to80_bcToE_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/QCD_Pt_80to170_bcToE_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_backup_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                              : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/QCD_Pt_80to170_bcToE_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_backup_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/QCD_Pt_170to250_bcToE_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                    : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/QCD_Pt_170to250_bcToE_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/QCD_Pt_250toInf_bcToE_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                    : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/QCD_Pt_250toInf_bcToE_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",

"/PrivateWWW/www-cms4-Private80X-v1/MINIAODSIM"                                                                                                                                 : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/PrivateWWW_www-cms4-Private80X-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/PrivateWWW/wwwext-cms4-Private80X-v1/MINIAODSIM"                                                                                                                              : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/PrivateWWW_wwwext-cms4-Private80X-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/SMS-TChiWH_WToLNu_HToVVTauTau_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"             : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/SMS-TChiWH_WToLNu_HToVVTauTau_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/SMS-TChiHH_HToWWZZTauTau_HToWWZZTauTau_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v2/MINIAODSIM"    : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/SMS-TChiHH_HToWWZZTauTau_HToWWZZTauTau_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v2_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",

"/DoublyChargedHiggsGMmodel_HWW_M200_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM"  : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/DoublyChargedHiggsGMmodel_HWW_M200_13TeV-madgraph_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/DoublyChargedHiggsGMmodel_HWW_M300_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM"  : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/DoublyChargedHiggsGMmodel_HWW_M300_13TeV-madgraph_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/DoublyChargedHiggsGMmodel_HWW_M400_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM"  : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/DoublyChargedHiggsGMmodel_HWW_M400_13TeV-madgraph_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/DoublyChargedHiggsGMmodel_HWW_M500_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM"  : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/DoublyChargedHiggsGMmodel_HWW_M500_13TeV-madgraph_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/DoublyChargedHiggsGMmodel_HWW_M600_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM"  : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/DoublyChargedHiggsGMmodel_HWW_M600_13TeV-madgraph_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/DoublyChargedHiggsGMmodel_HWW_M900_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM"  : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/DoublyChargedHiggsGMmodel_HWW_M900_13TeV-madgraph_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/DoublyChargedHiggsGMmodel_HWW_M1000_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM" : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/DoublyChargedHiggsGMmodel_HWW_M1000_13TeV-madgraph_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/DoublyChargedHiggsGMmodel_HWW_M1500_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM" : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/DoublyChargedHiggsGMmodel_HWW_M1500_13TeV-madgraph_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/DoublyChargedHiggsGMmodel_HWW_M2000_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM" : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/DoublyChargedHiggsGMmodel_HWW_M2000_13TeV-madgraph_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",

"/WprimeToWHToWlepHinc_narrow_M-600_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WprimeToWHToWlepHinc_narrow_M-600_TuneCUETP8M2T4_13TeV-madgraph-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WprimeToWHToWlepHinc_narrow_M-800_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WprimeToWHToWlepHinc_narrow_M-800_TuneCUETP8M2T4_13TeV-madgraph-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WprimeToWHToWlepHinc_narrow_M-1000_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WprimeToWHToWlepHinc_narrow_M-1000_TuneCUETP8M2T4_13TeV-madgraph-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WprimeToWHToWlepHinc_narrow_M-1200_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WprimeToWHToWlepHinc_narrow_M-1200_TuneCUETP8M2T4_13TeV-madgraph-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WprimeToWHToWlepHinc_narrow_M-1400_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WprimeToWHToWlepHinc_narrow_M-1400_TuneCUETP8M2T4_13TeV-madgraph-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WprimeToWHToWlepHinc_narrow_M-1600_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WprimeToWHToWlepHinc_narrow_M-1600_TuneCUETP8M2T4_13TeV-madgraph-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WprimeToWHToWlepHinc_narrow_M-1800_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WprimeToWHToWlepHinc_narrow_M-1800_TuneCUETP8M2T4_13TeV-madgraph-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WprimeToWHToWlepHinc_narrow_M-2000_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WprimeToWHToWlepHinc_narrow_M-2000_TuneCUETP8M2T4_13TeV-madgraph-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WprimeToWHToWlepHinc_narrow_M-2500_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WprimeToWHToWlepHinc_narrow_M-2500_TuneCUETP8M2T4_13TeV-madgraph-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WprimeToWHToWlepHinc_narrow_M-3500_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WprimeToWHToWlepHinc_narrow_M-3500_TuneCUETP8M2T4_13TeV-madgraph-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WprimeToWHToWlepHinc_narrow_M-4000_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WprimeToWHToWlepHinc_narrow_M-4000_TuneCUETP8M2T4_13TeV-madgraph-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WprimeToWHToWlepHinc_narrow_M-4500_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WprimeToWHToWlepHinc_narrow_M-4500_TuneCUETP8M2T4_13TeV-madgraph-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WprimeToWHToWlepHinc_narrow_M-5000_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WprimeToWHToWlepHinc_narrow_M-5000_TuneCUETP8M2T4_13TeV-madgraph-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WprimeToWHToWlepHinc_narrow_M-5500_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WprimeToWHToWlepHinc_narrow_M-5500_TuneCUETP8M2T4_13TeV-madgraph-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",
"/WprimeToWHToWlepHinc_narrow_M-6000_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" : "/hadoop/cms/store/user/namin/run2_moriond17_cms4/ProjectMetis/WprimeToWHToWlepHinc_narrow_M-6000_TuneCUETP8M2T4_13TeV-madgraph-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_CMS4_V00-00-02_2017Sep27/",

}


dslocscms3 = {

###############################################################################
# CMS3
###############################################################################
"/DoubleEG/Run2016B-03Feb2017_ver2-v2/CMS3"                                                                                                                                     : "/nfs-7/userdata/dataTuple/kludge/Run2016B_DoubleEG_MINIAOD_03Feb2017_ver2-v2/merged/V08-00-18/" ,
"/DoubleEG/Run2016C-03Feb2017-v1/CMS3"                                                                                                                                          : "/nfs-7/userdata/dataTuple/kludge/Run2016C_DoubleEG_MINIAOD_03Feb2017-v1/merged/V08-00-18/" ,
"/DoubleEG/Run2016D-03Feb2017-v1/CMS3"                                                                                                                                          : "/nfs-7/userdata/dataTuple/kludge/Run2016D_DoubleEG_MINIAOD_03Feb2017-v1/merged/V08-00-18/" ,
"/DoubleEG/Run2016E-03Feb2017-v1/CMS3"                                                                                                                                          : "/nfs-7/userdata/dataTuple/kludge/Run2016E_DoubleEG_MINIAOD_03Feb2017-v1/merged/V08-00-18/" ,
"/DoubleEG/Run2016F-03Feb2017-v1/CMS3"                                                                                                                                          : "/nfs-7/userdata/dataTuple/kludge/Run2016F_DoubleEG_MINIAOD_03Feb2017-v1/merged/V08-00-18/" ,
"/DoubleEG/Run2016G-03Feb2017-v1/CMS3"                                                                                                                                          : "/nfs-7/userdata/dataTuple/kludge/Run2016G_DoubleEG_MINIAOD_03Feb2017-v1/merged/V08-00-18/" ,
"/DoubleEG/Run2016H-03Feb2017_ver2-v1/CMS3"                                                                                                                                     : "/nfs-7/userdata/dataTuple/kludge/Run2016H_DoubleEG_MINIAOD_03Feb2017_ver2-v1/merged/V08-00-18/" ,
"/DoubleEG/Run2016H-03Feb2017_ver3-v1/CMS3"                                                                                                                                     : "/nfs-7/userdata/dataTuple/kludge/Run2016H_DoubleEG_MINIAOD_03Feb2017_ver3-v1/merged/V08-00-18/" ,
"/DoubleMuon/Run2016B-03Feb2017_ver2-v2/CMS3"                                                                                                                                   : "/nfs-7/userdata/dataTuple/kludge/Run2016B_DoubleMuon_MINIAOD_03Feb2017_ver2-v2/merged/V08-00-18/" ,
"/DoubleMuon/Run2016C-03Feb2017-v1/CMS3"                                                                                                                                        : "/nfs-7/userdata/dataTuple/kludge/Run2016C_DoubleMuon_MINIAOD_03Feb2017-v1/merged/V08-00-18/" ,
"/DoubleMuon/Run2016D-03Feb2017-v1/CMS3"                                                                                                                                        : "/nfs-7/userdata/dataTuple/kludge/Run2016D_DoubleMuon_MINIAOD_03Feb2017-v1/merged/V08-00-18/" ,
"/DoubleMuon/Run2016E-03Feb2017-v1/CMS3"                                                                                                                                        : "/nfs-7/userdata/dataTuple/kludge/Run2016E_DoubleMuon_MINIAOD_03Feb2017-v1/merged/V08-00-18/" ,
"/DoubleMuon/Run2016F-03Feb2017-v1/CMS3"                                                                                                                                        : "/nfs-7/userdata/dataTuple/kludge/Run2016F_DoubleMuon_MINIAOD_03Feb2017-v1/merged/V08-00-18/" ,
"/DoubleMuon/Run2016G-03Feb2017-v1/CMS3"                                                                                                                                        : "/nfs-7/userdata/dataTuple/kludge/Run2016G_DoubleMuon_MINIAOD_03Feb2017-v1/merged/V08-00-18/" ,
"/DoubleMuon/Run2016H-03Feb2017_ver2-v1/CMS3"                                                                                                                                   : "/nfs-7/userdata/dataTuple/kludge/Run2016H_DoubleMuon_MINIAOD_03Feb2017_ver2-v1/merged/V08-00-18/" ,
"/DoubleMuon/Run2016H-03Feb2017_ver3-v1/CMS3"                                                                                                                                   : "/nfs-7/userdata/dataTuple/kludge/Run2016H_DoubleMuon_MINIAOD_03Feb2017_ver3-v1/merged/V08-00-18/" ,
"/MuonEG/Run2016B-03Feb2017_ver2-v2/CMS3"                                                                                                                                       : "/nfs-7/userdata/dataTuple/kludge/Run2016B_MuonEG_MINIAOD_03Feb2017_ver2-v2/merged/V08-00-18/" ,
"/MuonEG/Run2016C-03Feb2017-v1/CMS3"                                                                                                                                            : "/nfs-7/userdata/dataTuple/kludge/Run2016C_MuonEG_MINIAOD_03Feb2017-v1/merged/V08-00-18/" ,
"/MuonEG/Run2016D-03Feb2017-v1/CMS3"                                                                                                                                            : "/nfs-7/userdata/dataTuple/kludge/Run2016D_MuonEG_MINIAOD_03Feb2017-v1/merged/V08-00-18/" ,
"/MuonEG/Run2016E-03Feb2017-v1/CMS3"                                                                                                                                            : "/nfs-7/userdata/dataTuple/kludge/Run2016E_MuonEG_MINIAOD_03Feb2017-v1/merged/V08-00-18/" ,
"/MuonEG/Run2016F-03Feb2017-v1/CMS3"                                                                                                                                            : "/nfs-7/userdata/dataTuple/kludge/Run2016F_MuonEG_MINIAOD_03Feb2017-v1/merged/V08-00-18/" ,
"/MuonEG/Run2016G-03Feb2017-v1/CMS3"                                                                                                                                            : "/nfs-7/userdata/dataTuple/kludge/Run2016G_MuonEG_MINIAOD_03Feb2017-v1/merged/V08-00-18/" ,
"/MuonEG/Run2016H-03Feb2017_ver2-v1/CMS3"                                                                                                                                       : "/nfs-7/userdata/dataTuple/kludge/Run2016H_MuonEG_MINIAOD_03Feb2017_ver2-v1/merged/V08-00-18/" ,
"/MuonEG/Run2016H-03Feb2017_ver3-v1/CMS3"                                                                                                                                       : "/nfs-7/userdata/dataTuple/kludge/Run2016H_MuonEG_MINIAOD_03Feb2017_ver3-v1/merged/V08-00-18/" ,

"/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                          : "/hadoop/cms/store/group/snt/run2_moriond17/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"             : "/hadoop/cms/store/group/snt/run2_moriond17/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/" ,
"/DYJetsToLL_M-50_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                : "/hadoop/cms/store/group/snt/run2_moriond17/DYJetsToLL_M-50_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"             : "/hadoop/cms/store/group/snt/run2_moriond17/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/" ,
"/DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                 : "/hadoop/cms/store/group/snt/run2_moriond17/DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"             : "/hadoop/cms/store/group/snt/run2_moriond17_test/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/" ,
"/DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM"                  : "/hadoop/cms/store/group/snt/run2_moriond17/DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/V08-00-16/" ,
"/DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                 : "/hadoop/cms/store/group/snt/run2_moriond17/DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v2/MINIAODSIM"                         : "/hadoop/cms/store/group/snt/run2_moriond17/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v2/V08-00-16/" ,
"/EWKWMinus2Jets_WToLNu_M-50_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                   : "/hadoop/cms/store/group/snt/run2_moriond17/EWKWMinus2Jets_WToLNu_M-50_13TeV-madgraph-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/EWKWPlus2Jets_WToLNu_M-50_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                    : "/hadoop/cms/store/group/snt/run2_moriond17/EWKWPlus2Jets_WToLNu_M-50_13TeV-madgraph-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/EWKZ2Jets_ZToLL_M-50_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                         : "/hadoop/cms/store/group/snt/run2_moriond17/EWKZ2Jets_ZToLL_M-50_13TeV-madgraph-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                    : "/hadoop/cms/store/group/snt/run2_moriond17/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" : "/hadoop/cms/store/group/snt/run2_moriond17/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"     : "/hadoop/cms/store/group/snt/run2_moriond17/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/ST_tW_antitop_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                    : "/hadoop/cms/store/group/snt/run2_moriond17/ST_tW_antitop_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                        : "/hadoop/cms/store/group/snt/run2_moriond17/ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/ST_tWll_5f_LO_13TeV-MadGraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                : "/hadoop/cms/store/group/snt/run2_moriond17/ST_tWll_5f_LO_13TeV-MadGraph-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/TEST-www/www-Private80X-v1/USER"                                                                                                                                              : "/hadoop/cms/store/group/snt/run2_moriond17/TEST-www_www-Private80X-v1/V08-00-16/" ,
"/TEST-www/wwwext-Private80X-v1/USER"                                                                                                                                           : "/hadoop/cms/store/group/snt/run2_moriond17/TEST-www_wwwext-Private80X-v1/V08-00-16/" ,
"/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                             : "/hadoop/cms/store/group/snt/run2_moriond17/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                              : "/hadoop/cms/store/group/snt/run2_moriond17/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/",
"/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                           : "/hadoop/cms/store/group/snt/run2_moriond17/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/" ,
"/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                  : "/hadoop/cms/store/group/snt/run2_moriond17/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/" ,
"/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"               : "/hadoop/cms/store/group/snt/run2_moriond17/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/" ,
"/VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                   : "/hadoop/cms/store/group/snt/run2_moriond17/VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                     : "/hadoop/cms/store/group/snt/run2_moriond17/WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/WGstarToLNuEE_012Jets_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                : "/hadoop/cms/store/group/snt/run2_moriond17/WGstarToLNuEE_012Jets_13TeV-madgraph_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/WGstarToLNuMuMu_012Jets_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                              : "/hadoop/cms/store/group/snt/run2_moriond17/WGstarToLNuMuMu_012Jets_13TeV-madgraph_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                  : "/hadoop/cms/store/group/snt/run2_moriond17/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/" ,
"/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                     : "/hadoop/cms/store/group/snt/run2_moriond17/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                  : "/hadoop/cms/store/group/snt/run2_moriond17/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/" ,
"/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                 : "/hadoop/cms/store/group/snt/run2_moriond17/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/" ,
"/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                  : "/hadoop/cms/store/group/snt/run2_moriond17/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/" ,
"/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                  : "/hadoop/cms/store/group/snt/run2_moriond17/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/" ,
"/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                 : "/hadoop/cms/store/group/snt/run2_moriond17/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/" ,
"/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                   : "/hadoop/cms/store/group/snt/run2_moriond17/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/WW_TuneCUETP8M1_13TeV-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                       : "/hadoop/cms/store/group/snt/run2_moriond17/WW_TuneCUETP8M1_13TeV-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/",
"/WZ_TuneCUETP8M1_13TeV-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                       : "/hadoop/cms/store/group/snt/run2_moriond17/WZ_TuneCUETP8M1_13TeV-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/",
"/WWG_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                                        : "/hadoop/cms/store/group/snt/run2_moriond17/WWG_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/" ,
"/WWTo2L2Nu_13TeV-powheg/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                              : "/hadoop/cms/store/group/snt/run2_moriond17/WWTo2L2Nu_13TeV-powheg_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/WWTo2L2Nu_DoubleScattering_13TeV-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                            : "/hadoop/cms/store/group/snt/run2_moriond17/WWTo2L2Nu_DoubleScattering_13TeV-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/WWToLNuQQ_13TeV-powheg/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                              : "/hadoop/cms/store/group/snt/run2_moriond17/WWToLNuQQ_13TeV-powheg_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                             : "/hadoop/cms/store/group/snt/run2_moriond17/WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/WZG_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                             : "/hadoop/cms/store/group/snt/run2_moriond17/WZG_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v3/MINIAODSIM"                                      : "/hadoop/cms/store/group/snt/run2_moriond17/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v3/V08-00-16/" ,
"/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                        : "/hadoop/cms/store/group/snt/run2_moriond17/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                          : "/hadoop/cms/store/group/snt/run2_moriond17/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                             : "/hadoop/cms/store/group/snt/run2_moriond17/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                  : "/hadoop/cms/store/group/snt/run2_moriond17/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                                : "/hadoop/cms/store/group/snt/run2_moriond17/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/" ,
"/ZZTo2L2Nu_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                      : "/hadoop/cms/store/group/snt/run2_moriond17/ZZTo2L2Nu_13TeV_powheg_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                         : "/hadoop/cms/store/group/snt/run2_moriond17/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/ZZTo2Q2Nu_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                        : "/hadoop/cms/store/group/snt/run2_moriond17/ZZTo2Q2Nu_13TeV_amcatnloFXFX_madspin_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/ZZTo4L_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                         : "/hadoop/cms/store/group/snt/run2_moriond17/ZZTo4L_13TeV_powheg_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                             : "/hadoop/cms/store/group/snt/run2_moriond17/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/tZq_ll_4f_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"                                               : "/hadoop/cms/store/group/snt/run2_moriond17/tZq_ll_4f_13TeV-amcatnlo-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/" ,
"/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                       : "/hadoop/cms/store/group/snt/run2_moriond17/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/ttHTobb_M125_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                   : "/hadoop/cms/store/group/snt/run2_moriond17/ttHTobb_M125_13TeV_powheg_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/ttWJets_13TeV_madgraphMLM/RunIISummer16MiniAODv2-80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                                       : "/hadoop/cms/store/group/snt/run2_moriond17/ttWJets_13TeV_madgraphMLM_RunIISummer16MiniAODv2-80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
"/ttZJets_13TeV_madgraphMLM/RunIISummer16MiniAODv2-80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                                                       : "/hadoop/cms/store/group/snt/run2_moriond17/ttZJets_13TeV_madgraphMLM_RunIISummer16MiniAODv2-80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/" ,
# Extra samples
"/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                                              : "/hadoop/cms/store/group/snt/run2_moriond17/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/",
"/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_HCALDebug_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"                   : "/hadoop/cms/store/group/snt/run2_moriond17/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISummer16MiniAODv2-PUMoriond17_HCALDebug_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/",
# QCD samples for fake rate
"/QCD_Pt_15to20_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_v1"         : "/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-15to20_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"          , 
"/QCD_Pt_20to30_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_v1"         : "/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-20to30_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"          , 
"/QCD_Pt_30to50_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_v1"         : "/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-30to50_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"          , 
"/QCD_Pt_50to80_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_v1"         : "/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-50to80_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"          , 
"/QCD_Pt_80to120_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1_v3"   : "/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-80to120_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v3/V08-00-16/"    , 
"/QCD_Pt_120to170_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_v1"       : "/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-120to170_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"        , 
"/QCD_Pt_170to300_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1_v1"  : "/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-170to300_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/"   , 
"/QCD_Pt_300to470_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2_v1"  : "/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-300to470_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/V08-00-16/"   , 
"/QCD_Pt_470to600_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1_v1"  : "/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-470to600_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/"   , 
"/QCD_Pt_600to800_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_v1"       : "/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-600to800_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"        , 
"/QCD_Pt_800to1000_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_v1"      : "/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-800to1000_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"       , 
"/QCD_Pt_1000toInf_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1_v3" : "/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-1000toInf_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v3/V08-00-16/"  , 
"/QCD_Pt_20to30_EMEnriched_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_v1"            : "/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-20to30_EMEnriched_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"             , 
"/QCD_Pt_30to50_EMEnriched_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1_v1"       : "/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-30to50_EMEnriched_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/"        , 
"/QCD_Pt_50to80_EMEnriched_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1_v1"       : "/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-50to80_EMEnriched_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/"        , 
"/QCD_Pt_80to120_EMEnriched_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1_v1"      : "/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-80to120_EMEnriched_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/"       , 
"/QCD_Pt_120to170_EMEnriched_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1_v1"     : "/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-120to170_EMEnriched_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/V08-00-16/"      , 
"/QCD_Pt_170to300_EMEnriched_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_v1"          : "/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-170to300_EMEnriched_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"           , 
"/QCD_Pt_300toInf_EMEnriched_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_v1"          : "/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt-300toInf_EMEnriched_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"           , 
"/QCD_Pt_15to20_bcToE_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_v1"                 : "/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt_15to20_bcToE_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"                  , 
"/QCD_Pt_20to30_bcToE_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_v1"                 : "/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt_20to30_bcToE_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"                  , 
"/QCD_Pt_30to80_bcToE_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_v1"                 : "/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt_30to80_bcToE_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"                  , 
"/QCD_Pt_80to170_bcToE_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_backup_80X_mcRun2_asymptotic_2016_TrancheIV_v6_v1"         : "/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt_80to170_bcToE_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_backup_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"          , 
"/QCD_Pt_170to250_bcToE_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_v1"               : "/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt_170to250_bcToE_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"                , 
"/QCD_Pt_250toInf_bcToE_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2_PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_v1"               : "/hadoop/cms/store/group/snt/run2_moriond17/QCD_Pt_250toInf_bcToE_TuneCUETP8M1_13TeV_pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/"                , 
}

dslocs = dslocscms4

# file/dir paths
main_dir = os.path.dirname(os.path.abspath(__file__))
metis_path = os.path.dirname(os.path.dirname(metis.__file__))
tar_path = os.path.join(metis_path, "package.tar")
tar_gz_path = tar_path + ".gz"
metis_dashboard_path = os.path.join(metis_path, "dashboard")
exec_path = os.path.join(main_dir, "metis.sh")
merge_exec_path = os.path.join(main_dir, "merge.sh")
hadoop_path = "metis/wwwbaby/{}".format(job_tag) # The output goes to /hadoop/cms/store/user/$USER/"hadoop_path"
#hadoop_path = "metis/wwwbaby" # The output goes to /hadoop/cms/store/user/$USER/"hadoop_path"
args = ""

doCMS4 = False

# Create tarball
os.chdir(main_dir)
os.system("tar -chzf {} localsetup.sh processBaby *.so *.pcm rooutil/lib*.so coreutil/data coreutil/lib*.so *.txt btagsf MVAinput jetCorrections leptonSFs puWeight2016.root pileup_jul21_nominalUpDown.root ../CORE/Tools/ mergeHadoopFiles.C xsec_susy_13tev.root".format(tar_gz_path))

# Change directory to metis
os.chdir(metis_path)

# Loop over datasets to submit
total_summary = {}
while True:

    all_tasks_complete = True

    #for sample in sorted(samples):
    for sample in samples:

#        # Use DIS to parse hadoop path from MINIAOD sample name
#        loc = ""
#        result = dis_client.query(q=sample, typ="snt")
#        status = result["response"]["status"]
#        if status == "success":
#            payloads = result["response"]["payload"]
#            for payload in payloads:
#                #print payload
#                if not doCMS4:
#                    if payload["cms3tag"].find("CMS4") != -1: continue
#                    loc = payload["location"]
#                else:
#                    if payload["cms3tag"].find("CMS3") != -1: continue
#                    loc = payload["location"]

        loc = dslocs[sample]

        ## If the location is empty after querying via dis, alert the user and skip
        #if loc == "":
        #    print ">>> [WARNING] DIS did not find hadoop path corresponding to the sample = {}".format(sample)
        #    continue

        # define the task
        maker_sample_name = "/MAKER_"+sample[1:]
        maker_task = CondorTask(
                sample               = DirectorySample(dataset=maker_sample_name, location=loc),
                tag                  = job_tag,
                arguments            = args,
                executable           = exec_path,
                tarfile              = tar_gz_path,
                special_dir          = hadoop_path,
                output_name          = "output.root",
                files_per_output     = 4,
                condor_submit_params = {"sites" : "T2_US_UCSD"},
                open_dataset         = False,
                flush                = True,
                #no_load_from_backup  = True,
                )

        merge_sample_name = "/MERGE_"+sample[1:]
        merge_task = CondorTask(
                sample                 = DirectorySample(dataset=merge_sample_name, location=maker_task.get_outputdir()),
                # open_dataset         = True, flush = True,
                executable             = merge_exec_path,
                tarfile                = tar_gz_path,
                files_per_output       = 100000,
                output_dir             = maker_task.get_outputdir() + "/merged",
                output_name            = samples_short_name[sample] + "_skim_1.root",
                condor_submit_params   = {"sites":"T2_US_UCSD"},
                output_is_tree         = True,
                # check_expectedevents = True,
                tag                    = job_tag,
                cmssw_version          = "CMSSW_9_2_0",
                scram_arch             = "slc6_amd64_gcc530",
                #no_load_from_backup    = True,
                )

        # process the job (either submits, checks for resubmit, or finishes etc.)
        maker_task.process()

        if maker_task.complete():
            merge_task.reset_io_mapping()
            merge_task.update_mapping()
            merge_task.process()

        # save some information for the dashboard
        total_summary[maker_task.get_sample().get_datasetname()] = maker_task.get_task_summary()
        total_summary[merge_task.get_sample().get_datasetname()] = merge_task.get_task_summary()

        # Aggregate whether all tasks are complete
        all_tasks_complete = all_tasks_complete and maker_task.complete() and merge_task.complete()


    # parse the total summary and write out the dashboard
    StatsParser(data=total_summary, webdir=metis_dashboard_path).do()

    # Print msummary table so I don't have to load up website
    os.system("msummary -p MAKER | tee summary.txt")
    os.system("chmod -R 755 {}".format(metis_dashboard_path))

    # If all done exit the loop
    if all_tasks_complete:
        print ""
        print "Job={} finished".format(job_tag)
        print ""
        break

    # Neat trick to not exit the script for force updating
    print 'Press Ctrl-C to force update, otherwise will sleep for 300 seconds'
    try:
        for i in range(0,300):
            sleep(1) # could use a backward counter to be preeety :)
    except KeyboardInterrupt:
        raw_input("Press Enter to force update, or Ctrl-C to quit.")
        print "Force updating..."


#eof
