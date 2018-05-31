#!/bin/bash
if [ ! -d rooutil ]; then
    git clone git@github.com:sgnoohc/rooutil.git rooutil;
    cd rooutil;
    git submodule update --init --recursive;
    source setup.sh;
    make;
    cd qframework;
    export TQPATH="";
    make -j 15;
    source setup.sh;
    cd ../../;
fi
if [ ! -d plottery ]; then
    git clone git@github.com:sgnoohc/plottery.git
fi
cd rooutil/
source setup.sh
cd qframework/
source setup.sh
cd ../../
