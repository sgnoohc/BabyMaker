##!/bin/env python

################################
# Job tag and output hadoop path
################################

data_year = "2016"
data_year = "2017"

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
job_tag = "WWW_v1.2.3" # Truth level information of the WWW samples
job_tag = "WWW_v3.0.0" # First test of few samples of 2016 MC in order to validate the changes to accomodate 2017 are ok.
job_tag = "WWW{}_v3.0.1".format(data_year) # First test of few samples of 2016 MC in order to validate the changes to accomodate 2017 are ok.

job_tag = "TnP{}_v3.0.1".format(data_year) # Testing TnP

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

import dataset


def main():

    if data_year == "2016":
        samples_to_run = dataset.samples_to_run_2016
        samples_short_name = dataset.samples_short_name_2017
        dslocs = dataset.dslocscms4_2016
    elif data_year == "2017":
        samples_short_name = dataset.samples_short_name_2017
        dslocs = dataset.dslocscms4_2017
        if job_tag.find("WWW") != -1:
            samples_to_run = dataset.samples_to_run_2017
        elif job_tag.find("TnP") != -1:
            samples_to_run = dataset.tnp_samples_to_run_2017

    # file/dir paths
    main_dir             = os.path.dirname(os.path.abspath(__file__))
    metis_path           = os.path.dirname(os.path.dirname(metis.__file__))
    tar_path             = os.path.join(metis_path, "package.tar")
    tar_gz_path          = tar_path + ".gz"
    metis_dashboard_path = os.path.join(metis_path, "dashboard")
    exec_path            = os.path.join(main_dir, "metis.sh")
    merge_exec_path      = os.path.join(main_dir, "merge.sh")
    hadoop_path          = "metis/wwwbaby/{}".format(job_tag) # The output goes to /hadoop/cms/store/user/$USER/"hadoop_path"
    if job_tag.find("WWW") != -1:
        args = "0" # WWWBaby
    elif job_tag.find("TnP") != -1:
        args = "3" # TnPBaby

    # Create tarball
    os.chdir(main_dir)
    os.system("tar -chzf {} localsetup.sh processBaby *.so *.pcm rooutil/lib*.so coreutil/data coreutil/lib*.so *.txt btagsf MVAinput jetCorrections leptonSFs puWeight2016.root pileup_jul21_nominalUpDown.root ../CORE/Tools/ mergeHadoopFiles.C xsec_susy_13tev.root".format(tar_gz_path))

    # Change directory to metis
    os.chdir(metis_path)

    total_summary = {}

    # Loop over datasets to submit
    while True:

        all_tasks_complete = True

        #for sample in sorted(samples):
        for sample in samples_to_run:

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
                    output_name            = samples_short_name[sample] + ".root",
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

if __name__ == "__main__":
    main()

#eof
