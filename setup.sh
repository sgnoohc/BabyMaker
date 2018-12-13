#!/bin/bash

#=====================================
# Setup Root and compile everything
#=====================================

# Git checkout submodules
echo "git checkout submodules"
git submodule update --init --recursive

# Setup ROOT
echo "Setting up ROOT"
export CMSSW_VERSION=CMSSW_9_2_0
export SCRAM_ARCH=slc6_amd64_gcc530
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /cvmfs/cms.cern.ch/$SCRAM_ARCH/cms/cmssw/$CMSSW_VERSION/src
eval `scramv1 runtime -sh`
cd - > /dev/null

# Extra for rooutil
export LD_LIBRARY_PATH=$PWD/rooutil:$LD_LIBRARY_PATH

echo "Building CORE, this might take a few minutes..."
cd dilepbabymaker/
source ./localsetup.sh
ln -s ../CORE 
make -j15

echo "Testing the babymaker..."
./dotest.sh
