#!/bin/bash

# in loop.py there is "twolep_cuts" string that defines the cut applied for the application region
# 
#    twolep_cuts = "(lep_pdgId[0]*lep_pdgId[1]>0)*(nj30>=2)" # if removing bveto
#    twolep_cuts = "(lep_pdgId[0]*lep_pdgId[1]>0)*(nj30>=2)*(nb==0)" # with bveto
#
# One should choose which one to run and run the below code

# To run the looper to first calculate the fake-rate
python loop.py
python printqcdfakerate.py # this script prints out "fake-factors=fr/1-fr" into histograms in a root file
# Now re-run the looper to apply the fake-factors that are just calculated from command above
python loop.py
# Now print out all the plots
python makeplot.py
