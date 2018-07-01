#!/bin/env python

import glob
import os
import json
import sys
sys.path.insert(0, 'ProjectMetis/scripts')
import dis_client

version = "v1.2.2"

logfiles = glob.glob("ProjectMetis/tasks/*{}/logs/std_logs/*.out".format(version))

logfiles.sort()

list_of_bad_files = []
skipped_fractions = {}

for logfile in logfiles:

    f = open(logfile)

    lines = f.readlines()

    content = ' '.join(lines)
    found = ("[CheckCorrupt]" in content.split())
    hadoopsuccess = (content.find("Hadoop Copy Job Success") != -1)

    if not hadoopsuccess:
        continue
    if found:
        print "=========================================================================="
        print "Found a file with [CheckCorrupt]:", logfile

        badfile_total_events = []
        for line in lines:
            if line.find("event index") != -1:
                badfile_total_events.append(line.strip().split()[-1])
        badfile_total_events = list(set(badfile_total_events))
        print "{} files are bad".format(len(badfile_total_events))
        
        entirely_skipped_files = []
        for line in lines:
            if line.find("Failed") != -1:
                entirely_skipped_files.append(line.split()[3].strip())

        partially_skipped_nevents = {}
        partially_skipped_files = []
        for line in lines:
            if line.find("Skipped") != -1:
                skippednevents = line.strip().rsplit("Skipped")[1].split()[0]
                nevents = line.strip().rsplit("out of")[1].split()[0]
                partially_skipped_files.append(nevents)
                partially_skipped_nevents[nevents] = str(int(skippednevents))

        # Get parent path
        for line in lines:
            if line.find("Add") != -1:
                dirpath = os.path.dirname(line.split()[5])
                break

        # Load Json
        jsonpath = os.path.join(dirpath, "metadata.json")
        data = json.load(open(jsonpath))

        # Loop over files
        nevents_to_file_dict = {}
        file_to_nevents_dict = {}
        for line in lines:
            if line.find("Add") != -1:
                fullfilename = line.split()[5]
                ifile = os.path.basename(fullfilename).split("_")[-1].split(".root")[0]
                nevents_to_file_dict[str(data["ijob_to_nevents"]["{}".format(ifile)][0])] = fullfilename
                file_to_nevents_dict[fullfilename] = str(data["ijob_to_nevents"]["{}".format(ifile)][0])

        # Get dis_client query pattern
        dis_query_dataset_pattern =  "/"+os.path.basename(dirpath.rsplit("MINIAODSIM")[0]+"MINIAODSIM*")
        dis_query_dataset_pattern = dis_query_dataset_pattern.replace("-","_")

        # Use DIS to parse hadoop path from MINIAOD sample name
        result = dis_client.query(q=dis_query_dataset_pattern, typ="snt")
        status = result["response"]["status"]
        if status == "success":
            payloads = result["response"]["payload"]
            for payload in payloads:
                if payload["cms3tag"].find("CMS3") != -1: continue
                loc = payload["location"]
                nevents_out = payload["nevents_out"]
                dataset_name = payload["dataset_name"]
                if dataset_name not in skipped_fractions:
                    skipped_fractions[dataset_name] = 0
                #print nevents_out
                if os.path.normpath(loc) != os.path.normpath(dirpath):
                    print loc
                    print dirpath
                    print "ERROR"


        # Query partially skipped files
        for key in partially_skipped_files:
            fraction = float(partially_skipped_nevents["{}".format(key)]) / float(nevents_out)
            print fraction, partially_skipped_nevents["{}".format(key)], key, nevents_out, nevents_to_file_dict["{}".format(key)]
            skipped_fractions[dataset_name] += fraction
            list_of_bad_files.append(nevents_to_file_dict["{}".format(key)])

        # Query entirely_skipped_files
        for key in entirely_skipped_files:
            fraction = float(file_to_nevents_dict[key]) / float(nevents_out)
            print fraction, file_to_nevents_dict[key], nevents_out, key
            skipped_fractions[dataset_name] += fraction
            list_of_bad_files.append(key)

print ""
print "=========================================================================="
print " Summary of failed jobs"
print "=========================================================================="
print ""
keylist = skipped_fractions.keys()
keylist.sort()
for key in keylist:
    print "{:5.2f}% missing {}".format(skipped_fractions[key]*100., key)

print ""
print "todo: hdfs fsck"
for f in list_of_bad_files:
    os.system("hdfs fsck {} 2>/dev/null  | tail -n1".format(f[7:]))
