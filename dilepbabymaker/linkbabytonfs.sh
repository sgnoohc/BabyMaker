#!/bin/bash

if [ -z $1 ]; then
    echo "EXAMPLE: sh hadd.sh v1.0.9"
    exit
fi

VERSION=$1
HADOOPDIR=/hadoop/cms/store/user/phchang/metis/baby/${VERSION}/*${VERSION}/
DIR=/nfs-7/userdata/phchang/babies/${VERSION}/link/

for i in $(ls -d $HADOOPDIR); do
    mkdir -p $DIR
    DIRNAME=$(basename $i)
    SAMPLENAME=${DIRNAME/MAKER_/}
    if [[ $SAMPLENAME = *_ext* ]]; then
        HASEXT=${SAMPLENAME#*_ext}
        HASEXT=${HASEXT%%-*}
        HASEXT=_ext${HASEXT}
    else
        HASEXT=""
    fi
    SAMPLENAME=${SAMPLENAME/_${VERSION}/}
    SAMPLENAME=${SAMPLENAME%%-pythia8*}
    SAMPLENAME=${SAMPLENAME%%_pythia8*}
    SAMPLENAME=${SAMPLENAME%%_MINIAOD*}
    SAMPLENAME=${SAMPLENAME}${HASEXT}
    echo $SAMPLENAME
    for file in $(ls $i/*.root); do
        FILENAME=$(basename $file)
        CLEANDIRNAME=$(dirname $DIR)
        CLEANDIRNAME=${CLEANDIRNAME}/$(basename $DIR)
        ln -svf $file ${CLEANDIRNAME}/${SAMPLENAME}_${FILENAME}
    done
done

