##!/bin/env python

################################
# Job tag and output hadoop path
################################

data_year = "2017"
data_year = "2016"

job_tag = "HWW{}_v1.1.0".format(data_year) # 2017 MVA IDs are set to the POG provided ones
job_tag = "HWW{}_v1.1.2".format(data_year) # Failed production
job_tag = "HWW{}_v1.1.4".format(data_year) # No selection (failed production)
job_tag = "HWW{}_v1.1.5".format(data_year) # Apply nlep >= 1 and nak8 >= 1 (cvmfs disaster)
job_tag = "HWW{}_v1.2.1".format(data_year) # Apply nlep >= 1 and nak8 >= 1
job_tag = "HWW{}_v1.3.1".format(data_year) # Added a few variable realted to other side of the isolation
job_tag = "HWW{}_v1.4.1".format(data_year) # Trigger included
job_tag = "HWW{}_v1.5.1".format(data_year) # Fat-jet Trigger included

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
        samples_short_name = dataset.samples_short_name_2016
        dslocs = dataset.dslocscms4_2016
        if job_tag.find("HWW") != -1:
            samples_to_run = dataset.hww_samples_to_run_2016
    elif data_year == "2017":
        samples_short_name = dataset.samples_short_name_2017
        dslocs = dataset.dslocscms4_2017
        if job_tag.find("TnP") != -1:
            samples_to_run = dataset.tnp_samples_to_run_2017
        elif job_tag.find("FR") != -1:
            samples_to_run = dataset.fr_samples_to_run_2017
        else:
            samples_to_run = dataset.samples_to_run_2017

    # file/dir paths
    main_dir             = os.path.dirname(os.path.abspath(__file__))
    metis_path           = os.path.dirname(os.path.dirname(metis.__file__))
    tar_path             = os.path.join(metis_path, "package.tar")
    tar_gz_path          = tar_path + ".gz"
    metis_dashboard_path = os.path.join(metis_path, "dashboard")
    exec_path            = os.path.join(main_dir, "metis.sh")
    merge_exec_path      = os.path.join(main_dir, "merge.sh")
    hadoop_path          = "metis/baby/{}".format(job_tag) # The output goes to /hadoop/cms/store/user/$USER/"hadoop_path"
    if job_tag.find("WWW") != -1:
        args = "0" # WWWBaby
    elif job_tag.find("FR") != -1:
        args = "1" # FRBaby
    elif job_tag.find("OS") != -1:
        args = "2" # OSBaby
    elif job_tag.find("TnP") != -1:
        args = "3" # TnPBaby
    elif job_tag.find("All") != -1:
        args = "4" # AllBaby
    elif job_tag.find("POG") != -1:
        args = "5" # POGBaby
    elif job_tag.find("HWW") != -1:
        args = "6" # HWWBaby

    # Create tarball
    os.chdir(main_dir)
    os.system("tar -chzf {} localsetup.sh processBaby *.so *.pcm rooutil/lib*.so coreutil/data coreutil/lib*.so *.txt btagsf MVAinput jetCorrections leptonSFs puWeight2016.root pileup_jul21_nominalUpDown.root ../CORE/Tools/ mergeHadoopFiles.C xsec_susy_13tev.root roccor.2017.v0/*.txt".format(tar_gz_path))

    # Change directory to metis
    os.chdir(metis_path)

    total_summary = {}

    # Loop over datasets to submit
    while True:

        all_tasks_complete = True

        #for sample in sorted(samples):
        for sample in samples_to_run:

            loc = dslocs[sample]

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
                    files_per_output     = 1,
                    condor_submit_params = {"sites" : "T2_US_UCSD"},
                    open_dataset         = False,
                    flush                = True,
                    #no_load_from_backup  = True,
                    )

#            merge_sample_name = "/MERGE_"+sample[1:]
#            merge_task = CondorTask(
#                    sample                 = DirectorySample(dataset=merge_sample_name, location=maker_task.get_outputdir()),
#                    # open_dataset         = True, flush = True,
#                    executable             = merge_exec_path,
#                    tarfile                = tar_gz_path,
#                    files_per_output       = 100000,
#                    output_dir             = maker_task.get_outputdir() + "/merged",
#                    output_name            = samples_short_name[sample] + ".root",
#                    condor_submit_params   = {"sites":"T2_US_UCSD"},
#                    output_is_tree         = True,
#                    # check_expectedevents = True,
#                    tag                    = job_tag,
#                    cmssw_version          = "CMSSW_9_2_0",
#                    scram_arch             = "slc6_amd64_gcc530",
#                    #no_load_from_backup    = True,
#                    )

            # process the job (either submits, checks for resubmit, or finishes etc.)
            maker_task.process()

#            if maker_task.complete():
#                merge_task.reset_io_mapping()
#                merge_task.update_mapping()
#                merge_task.process()

            # save some information for the dashboard
            total_summary[maker_task.get_sample().get_datasetname()] = maker_task.get_task_summary()
#            total_summary[merge_task.get_sample().get_datasetname()] = merge_task.get_task_summary()

            # Aggregate whether all tasks are complete
#            all_tasks_complete = all_tasks_complete and maker_task.complete() and merge_task.complete()
            all_tasks_complete = all_tasks_complete and maker_task.complete()


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
