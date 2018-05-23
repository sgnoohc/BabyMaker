#!/bin/bash

# To run the looper to first calculate the fake-rate
python loop.py
python printqcdfakerate.py # this script prints out "fake-factors=fr/1-fr" into histograms in a root file
# Now re-run the looper to apply the fake-factors that are just calculated from command above
python loop.py
# Now print out all the plots
python makeplot.py
