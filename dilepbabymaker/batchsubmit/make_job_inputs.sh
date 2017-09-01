#!/bin/bash

THISDIR=`pwd`
cd ..
tar -czf batchsubmit/job_input/package.tar.gz *.so batchsubmit/hadoopmap.txt puWeight2016.root btagsf leptonSFs jetCorrections processBaby skim_macro.C MVAinput Cert*.txt ../CORE/Tools/jetcorr/data/run2_25ns/
cd $THISDIR
cp wrapper_auto.sh sweeproot.sh sweeproot_macro.C merge_script.sh merge_macro.C job_input/
