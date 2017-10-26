#!/bin/bash

#=====================================
# Setup Root and compile everything
#=====================================

echo "Grabbing Dependancies..."

git clone git@github.com:cmstas/CORE.git
cd CORE/
git checkout CMS3_archive
cd ..
git clone git@github.com:cmstas/NtupleTools.git
git clone git@github.com:cmstas/Software.git
cd Software/
git checkout root6
cd ..

echo "Setting up ROOT"

CMSSW_VERSION=CMSSW_8_0_5
export SCRAM_ARCH=slc6_amd64_gcc530
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /cvmfs/cms.cern.ch/$SCRAM_ARCH/cms/cmssw/$CMSSW_VERSION/src
eval `scramv1 runtime -sh`
cd -

echo "Building CORE, this might take a few minutes..."
cd dilepbabymaker/
ln -s ../CORE 
make -j15

echo "Testing the babymaker..."
./dotest.sh

cd ../NtupleTools/AutoTwopler/
. setup.sh
cd ../../dilepbabymaker/batchsubmit/

echo "You are ready to choose samples and run ducks.py"
