#!/bin/bash

# First run the looper once to calculate some relevant quantities (trigger prescale, nvtx reweighting)
python loop.py
python makeplot.py # This will print out and also write out nvtx reweighting function

# Then with this setting run again
python loop.py
python printqcdfakerate.py # this script prints out "fake-factors=fr/1-fr" into histograms in a root file

# Now re-run the looper to apply the fake-factors that are just calculated from command above
python loop.py

# Now re-run the looper for jec variation
python loop.py 1 # variation up
python loop.py 2 # variation down

# Now print out all the relevant plots
python makeplot.py
