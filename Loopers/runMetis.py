#!/bin/env python

################################
# Job tag and output hadoop path
################################

# NOTE: If you want to resubmit the skimming job, you need to delete $ANALYSIS_BASE/tasks and hadoop_path output path

job_tag = "v2"
hadoop_path = "metis/wwwlooper/{}".format(job_tag) # The output goes to /hadoop/cms/store/user/$USER/"hadoop_path"

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
sys.path.append('/home/users/namin/public_html/makers/disMaker')
import dis_client
import json

# file/dir paths
main_dir = os.path.dirname(os.path.abspath(__file__))
metis_path = os.path.dirname(os.path.dirname(metis.__file__))
tar_path = os.path.join(metis_path, "package.tar")
tar_gz_path = tar_path + ".gz"
metis_dashboard_path = os.path.join(metis_path, "dashboard")
exec_path = os.path.join(main_dir, "metis.sh")

# Create tarball
os.chdir(main_dir)
os.system("tar -chzf {} localsetup.sh wwwana rooutil/lib*.so data".format(tar_gz_path))

# Configurations
args = ""

# Change directory to metis
os.chdir(metis_path)

# Loop over datasets to submit
total_summary = {}
while True:

    # define the task
    task = CondorTask(
            sample               = DirectorySample(
                dataset="/WWW_v0_1_16",
                location="/hadoop/cms/store/user/bhashemi/AutoTwopler_babies/merged/VVV/WWW_v0.1.16/skim/",
                globber="*.root"),
            tag                  = job_tag,
            arguments            = args,
            executable           = exec_path,
            tarfile              = tar_gz_path,
            special_dir          = hadoop_path,
            output_name          = "merged.root",
            files_per_output     = 1,
            condor_submit_params = {"sites" : "UAF,T2_US_UCSD"},
            open_dataset         = False,
            flush                = True
            )

    # process the job (either submits, checks for resubmit, or finishes etc.)
    task.process()

    # save some information for the dashboard
    total_summary["WWW_v0_1_16"] = task.get_task_summary()

    # parse the total summary and write out the dashboard
    StatsParser(data=total_summary, webdir=metis_dashboard_path).do()

    # Print msummary table so I don't have to load up website
    os.system("msummary | tee summary.txt")
    #os.system("chmod -R 755 {}".format(metis_dashboard_path))

    # If all done exit the loop
    if task.complete():
        print ""
        print "Job={} finished".format(job_tag)
        print ""
        break

    # Neat trick to not exit the script for force updating
    print 'Press Ctrl-C to force update, otherwise will sleep for 30 seconds'
    try:
        for i in range(0,30):
            sleep(1) # could use a backward counter to be preeety :)
    except KeyboardInterrupt:
        raw_input("Press Enter to force update, or Ctrl-C to quit.")
        print "Force updating..."

#eof
