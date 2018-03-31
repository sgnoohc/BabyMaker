#!/bin/bash

PLOTSDIR=/home/users/phchang/public_html/phys/tnp/CMSSW_7_4_2/src/TagAndProbe/Analysis/plots/
DY=www_analysis_dy_eff.root
DATA="www_analysis_single*_eff.root"

IDs="MuMediumPOG_MuTightVVV \
MuMediumPOG_MuTightVVV3l \
EGammaMediumPOGMVA_EGammaVVV3l \
EGammaTightPOGMVA_EGammaVVV"

for ID in ${IDs}; do
    python make_sf.py ${PLOTSDIR}/*_WWW_v2/*/${ID}/${DY} ${PLOTSDIR}/*_WWW_v2/*/${ID}/${DATA} lepsf_${ID}_v2
done
