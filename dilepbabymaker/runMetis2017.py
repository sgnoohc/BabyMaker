##!/bin/env python

################################
# Job tag and output hadoop path
################################

# NOTE: If you want to resubmit the skimming job, you need to delete $ANALYSIS_BASE/tasks and hadoop_path output path

job_tag = "WWW_v2.0.3" # Test version

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

samples = {

"/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM"                                      : "dy_m1050_madgraph",
"/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"            : "dy_m50_madgraph",
"/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"       : "dy_m50_madgraph_ext1",
"/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM" : "sttw_incltop_powheg",
"/ST_tW_top_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"     : "sttw_incltbr_powheg",
"/TTGamma_SingleLeptFromT_TuneCP5_PSweights_13TeV_madgraph_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"        : "ttg_1ltop_madgraph",
"/TTGamma_SingleLeptFromTbar_TuneCP5_PSweights_13TeV_madgraph_pythia8/RunIIFall17MiniAOD-PU2017_94X_mc2017_realistic_v11-v1/MINIAODSIM"                 : "ttg_1ltbr_madgraph",
"/TTHH_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                                     : "tthh_madgraph",
"/TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                               : "ttbar_incl_amcnlo",
"/TTTJ_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                                     : "tttj_incl_madgraph",
"/TTTT_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_pilot_94X_mc2017_realistic_v14-v1/MINIAODSIM"                                         : "tttt_incl_amcnlo",
"/TTTW_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                                     : "tttw_incl_madgraph",
"/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                 : "ttbar_1l_powheg",
"/TTWH_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                                     : "ttwh_incl_madgraph",
"/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                 : "ttw_ln_amcnlo",
"/TTWW_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"                                : "ttww_incl_madgraph_ext1",
"/TTWZ_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                                     : "ttwz_incl_madgraph",
"/TTZH_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                                     : "ttzh_incl_madgraph",
"/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                         : "ttz_m10llnn_amcnlo",
"/TTZToLL_M-1to10_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                          : "ttz_m1to10ll_amcnlo",
"/TTZZ_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                                     : "ttzz_incl_madgraph",
"/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2/MINIAODSIM"                       : "wjets_ln_madgraph_ext1",
"/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                                   : "www_incl_amcnlo",
"/WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                                   : "wwz_incl_amcnlo",
"/WW_DoubleScattering_13TeV-pythia8_TuneCP5/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                               : "ww_dblsctincl_pythia",
"/WW_TuneCP5_13TeV-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"                                                                   : "ww_incl_pythia",
"/WZG_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                                      : "wzg_incl_amcnlo",
"/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                             : "wz_3lnu_amcnlo",
"/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                                      : "wzz_incl_amcnlo",
"/WZ_TuneCP5_13TeV-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                                                : "wz_incl_pythia",
"/ZZTo4L_13TeV_powheg_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                                             : "zz_4l_powheg",
"/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                                      : "zzz_incl_amcnlo",
"/tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"              : "tzq_ll_amcnlo",
"/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"                                               : "tth_nonbb_powheg",

"/DoubleEG/Run2017B-31Mar2018-v1/MINIAOD" : "data_Run2017B_ee",
"/DoubleEG/Run2017C-31Mar2018-v1/MINIAOD" : "data_Run2017C_ee",
"/DoubleEG/Run2017D-31Mar2018-v1/MINIAOD" : "data_Run2017D_ee",
"/DoubleEG/Run2017E-31Mar2018-v1/MINIAOD" : "data_Run2017E_ee",
"/DoubleEG/Run2017F-31Mar2018-v1/MINIAOD" : "data_Run2017F_ee",
"/DoubleMuon/Run2017B-31Mar2018-v1/MINIAOD" : "data_Run2017B_mm",
"/DoubleMuon/Run2017C-31Mar2018-v1/MINIAOD" : "data_Run2017C_mm",
"/DoubleMuon/Run2017D-31Mar2018-v1/MINIAOD" : "data_Run2017D_mm",
"/DoubleMuon/Run2017E-31Mar2018-v1/MINIAOD" : "data_Run2017E_mm",
"/DoubleMuon/Run2017F-31Mar2018-v1/MINIAOD" : "data_Run2017F_mm",
"/MuonEG/Run2017B-31Mar2018-v1/MINIAOD" : "data_Run2017B_em",
"/MuonEG/Run2017C-31Mar2018-v1/MINIAOD" : "data_Run2017C_em",
"/MuonEG/Run2017D-31Mar2018-v1/MINIAOD" : "data_Run2017D_em",
"/MuonEG/Run2017E-31Mar2018-v1/MINIAOD" : "data_Run2017E_em",
"/MuonEG/Run2017F-31Mar2018-v1/MINIAOD" : "data_Run2017F_em",

#"/W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v3/MINIAODSIM"                                              : "/hadoop/cms/store/group/snt/run2_mc2017//W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v3_MINIAODSIM_CMS4_V09-04-12/"
#"/W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                           : "/hadoop/cms/store/group/snt/run2_mc2017//W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/"
#"/W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"                                              : "/hadoop/cms/store/group/snt/run2_mc2017//W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1_MINIAODSIM_CMS4_V09-04-12/"
#"/W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                           : "/hadoop/cms/store/group/snt/run2_mc2017//W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/"
#"/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"                                               : "/hadoop/cms/store/group/snt/run2_mc2017//WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1_MINIAODSIM_CMS4_V09-04-13/"
#"/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM"                                                : "/hadoop/cms/store/group/snt/run2_mc2017//WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2_MINIAODSIM_CMS4_V09-04-13/"

}

dslocs = {

"/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM"                                      : "/hadoop/cms/store/group/snt/run2_mc2017//DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2_MINIAODSIM_CMS4_V09-04-13/",
"/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"            : "/hadoop/cms/store/group/snt/run2_mc2017//DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/" ,
"/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"       : "/hadoop/cms/store/group/snt/run2_mc2017//DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14_ext1-v1_MINIAODSIM_CMS4_V09-04-13/",
"/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM" : "/hadoop/cms/store/group/snt/run2_mc2017//ST_tW_antitop_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/",
"/ST_tW_top_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"     : "/hadoop/cms/store/group/snt/run2_mc2017//ST_tW_top_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/",
"/TTGamma_SingleLeptFromT_TuneCP5_PSweights_13TeV_madgraph_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"        : "/hadoop/cms/store/group/snt/run2_mc2017//TTGamma_SingleLeptFromT_TuneCP5_PSweights_13TeV_madgraph_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/",
"/TTGamma_SingleLeptFromTbar_TuneCP5_PSweights_13TeV_madgraph_pythia8/RunIIFall17MiniAOD-PU2017_94X_mc2017_realistic_v11-v1/MINIAODSIM"                 : "/hadoop/cms/store/group/snt/run2_mc2017//TTGamma_SingleLeptFromTbar_TuneCP5_PSweights_13TeV_madgraph_pythia8_RunIIFall17MiniAOD-PU2017_94X_mc2017_realistic_v11-v1_MINIAODSIM_CMS4_V09-04-13/",
"/TTHH_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                                     : "/hadoop/cms/store/group/snt/run2_mc2017//TTHH_TuneCP5_13TeV-madgraph-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/",
"/TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                               : "/hadoop/cms/store/group/snt/run2_mc2017//TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/",
"/TTTJ_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                                     : "/hadoop/cms/store/group/snt/run2_mc2017//TTTJ_TuneCP5_13TeV-madgraph-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/",
"/TTTT_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_pilot_94X_mc2017_realistic_v14-v1/MINIAODSIM"                                         : "/hadoop/cms/store/group/snt/run2_mc2017//TTTT_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_pilot_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/",
"/TTTW_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                                     : "/hadoop/cms/store/group/snt/run2_mc2017//TTTW_TuneCP5_13TeV-madgraph-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/",
"/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                 : "/hadoop/cms/store/group/snt/run2_mc2017//TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/",
"/TTWH_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                                     : "/hadoop/cms/store/group/snt/run2_mc2017//TTWH_TuneCP5_13TeV-madgraph-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/",
"/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                 : "/hadoop/cms/store/group/snt/run2_mc2017//TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/",
"/TTWW_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"                                : "/hadoop/cms/store/group/snt/run2_mc2017//TTWW_TuneCP5_13TeV-madgraph-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1_MINIAODSIM_CMS4_V09-04-13/",
"/TTWZ_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                                     : "/hadoop/cms/store/group/snt/run2_mc2017//TTWZ_TuneCP5_13TeV-madgraph-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/",
"/TTZH_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                                     : "/hadoop/cms/store/group/snt/run2_mc2017//TTZH_TuneCP5_13TeV-madgraph-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/",
"/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                         : "/hadoop/cms/store/group/snt/run2_mc2017//TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/",
"/TTZToLL_M-1to10_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                          : "/hadoop/cms/store/group/snt/run2_mc2017//TTZToLL_M-1to10_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/",
"/TTZZ_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                                     : "/hadoop/cms/store/group/snt/run2_mc2017//TTZZ_TuneCP5_13TeV-madgraph-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/",
"/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2/MINIAODSIM"                       : "/hadoop/cms/store/group/snt/run2_mc2017//WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2_MINIAODSIM_CMS4_V09-04-13/",
"/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                                   : "/hadoop/cms/store/group/snt/run2_mc2017//WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/",
"/WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                                   : "/hadoop/cms/store/group/snt/run2_mc2017//WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/",
"/WW_DoubleScattering_13TeV-pythia8_TuneCP5/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                               : "/hadoop/cms/store/group/snt/run2_mc2017//WW_DoubleScattering_13TeV-pythia8_TuneCP5_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/",
"/WW_TuneCP5_13TeV-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"                                                                   : "/hadoop/cms/store/group/snt/run2_mc2017//WW_TuneCP5_13TeV-pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1_MINIAODSIM_CMS4_V09-04-13/",
"/WZG_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                                      : "/hadoop/cms/store/group/snt/run2_mc2017//WZG_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/",
"/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                             : "/hadoop/cms/store/group/snt/run2_mc2017//WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/",
"/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                                      : "/hadoop/cms/store/group/snt/run2_mc2017//WZZ_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/",
"/WZ_TuneCP5_13TeV-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                                                : "/hadoop/cms/store/group/snt/run2_mc2017//WZ_TuneCP5_13TeV-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/",
"/ZZTo4L_13TeV_powheg_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                                             : "/hadoop/cms/store/group/snt/run2_mc2017//ZZTo4L_13TeV_powheg_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/",
"/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                                      : "/hadoop/cms/store/group/snt/run2_mc2017//ZZZ_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/",
"/tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"              : "/hadoop/cms/store/group/snt/run2_mc2017//tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/",
"/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"                                               : "/hadoop/cms/store/group/snt/run2_mc2017//ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1_MINIAODSIM_CMS4_V09-04-13/",

"/DoubleEG/Run2017B-31Mar2018-v1/MINIAOD" : "/hadoop/cms/store/group/snt/run2_data2017//DoubleEG_Run2017B-31Mar2018-v1_MINIAOD_CMS4_V09-04-12/",
"/DoubleEG/Run2017C-31Mar2018-v1/MINIAOD" : "/hadoop/cms/store/group/snt/run2_data2017//DoubleEG_Run2017C-31Mar2018-v1_MINIAOD_CMS4_V09-04-12/",
"/DoubleEG/Run2017D-31Mar2018-v1/MINIAOD" : "/hadoop/cms/store/group/snt/run2_data2017//DoubleEG_Run2017D-31Mar2018-v1_MINIAOD_CMS4_V09-04-12/",
"/DoubleEG/Run2017E-31Mar2018-v1/MINIAOD" : "/hadoop/cms/store/group/snt/run2_data2017//DoubleEG_Run2017E-31Mar2018-v1_MINIAOD_CMS4_V09-04-12/",
"/DoubleEG/Run2017F-31Mar2018-v1/MINIAOD" : "/hadoop/cms/store/group/snt/run2_data2017//DoubleEG_Run2017F-31Mar2018-v1_MINIAOD_CMS4_V09-04-12/",
"/DoubleMuon/Run2017B-31Mar2018-v1/MINIAOD" : "/hadoop/cms/store/group/snt/run2_data2017//DoubleMuon_Run2017B-31Mar2018-v1_MINIAOD_CMS4_V09-04-12/",
"/DoubleMuon/Run2017C-31Mar2018-v1/MINIAOD" : "/hadoop/cms/store/group/snt/run2_data2017//DoubleMuon_Run2017C-31Mar2018-v1_MINIAOD_CMS4_V09-04-12/",
"/DoubleMuon/Run2017D-31Mar2018-v1/MINIAOD" : "/hadoop/cms/store/group/snt/run2_data2017//DoubleMuon_Run2017D-31Mar2018-v1_MINIAOD_CMS4_V09-04-12/",
"/DoubleMuon/Run2017E-31Mar2018-v1/MINIAOD" : "/hadoop/cms/store/group/snt/run2_data2017//DoubleMuon_Run2017E-31Mar2018-v1_MINIAOD_CMS4_V09-04-12/",
"/DoubleMuon/Run2017F-31Mar2018-v1/MINIAOD" : "/hadoop/cms/store/group/snt/run2_data2017//DoubleMuon_Run2017F-31Mar2018-v1_MINIAOD_CMS4_V09-04-12/",
"/MuonEG/Run2017B-31Mar2018-v1/MINIAOD" : "/hadoop/cms/store/group/snt/run2_data2017//MuonEG_Run2017B-31Mar2018-v1_MINIAOD_CMS4_V09-04-12/",
"/MuonEG/Run2017C-31Mar2018-v1/MINIAOD" : "/hadoop/cms/store/group/snt/run2_data2017//MuonEG_Run2017C-31Mar2018-v1_MINIAOD_CMS4_V09-04-12/",
"/MuonEG/Run2017D-31Mar2018-v1/MINIAOD" : "/hadoop/cms/store/group/snt/run2_data2017//MuonEG_Run2017D-31Mar2018-v1_MINIAOD_CMS4_V09-04-12/",
"/MuonEG/Run2017E-31Mar2018-v1/MINIAOD" : "/hadoop/cms/store/group/snt/run2_data2017//MuonEG_Run2017E-31Mar2018-v1_MINIAOD_CMS4_V09-04-12/",
"/MuonEG/Run2017F-31Mar2018-v1/MINIAOD" : "/hadoop/cms/store/group/snt/run2_data2017//MuonEG_Run2017F-31Mar2018-v1_MINIAOD_CMS4_V09-04-12/",

#"/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM"                                                : "/hadoop/cms/store/group/snt/run2_mc2017//WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2_MINIAODSIM_CMS4_V09-04-13/"
#"/W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v3/MINIAODSIM"                                              : "/hadoop/cms/store/group/snt/run2_mc2017//W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v3_MINIAODSIM_CMS4_V09-04-12/"
#"/W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                           : "/hadoop/cms/store/group/snt/run2_mc2017//W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/"
#"/W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"                                              : "/hadoop/cms/store/group/snt/run2_mc2017//W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1_MINIAODSIM_CMS4_V09-04-12/"
#"/W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"                           : "/hadoop/cms/store/group/snt/run2_mc2017//W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13/"
#"/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"                                               : "/hadoop/cms/store/group/snt/run2_mc2017//WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1_MINIAODSIM_CMS4_V09-04-13/"

}

# file/dir paths
main_dir = os.path.dirname(os.path.abspath(__file__))
metis_path = os.path.dirname(os.path.dirname(metis.__file__))
tar_path = os.path.join(metis_path, "package.tar")
tar_gz_path = tar_path + ".gz"
metis_dashboard_path = os.path.join(metis_path, "dashboard")
exec_path = os.path.join(main_dir, "metis.sh")
merge_exec_path = os.path.join(main_dir, "merge.sh")
hadoop_path = "metis/wwwbaby/{}".format(job_tag) # The output goes to /hadoop/cms/store/user/$USER/"hadoop_path"
args = ""

doCMS4 = False

# Create tarball
os.chdir(main_dir)
os.system("tar -chzf {} localsetup.sh processBaby *.so *.pcm rooutil/lib*.so coreutil/data coreutil/lib*.so *.txt btagsf MVAinput jetCorrections leptonSFs puWeight2016.root pileup_jul21_nominalUpDown.root ../CORE/Tools/ mergeHadoopFiles.C".format(tar_gz_path))

# Change directory to metis
os.chdir(metis_path)

# Loop over datasets to submit
total_summary = {}
while True:

    all_tasks_complete = True

    for sample in sorted(samples):

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
        maker_task = CondorTask(
                sample               = DirectorySample(dataset=sample, location=loc),
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
                output_name            = samples[sample] + "_skim_1.root",
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
    os.system("msummary -s name -r | tee summary.txt")
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
