# Loopers for VVV, incl. plotting and table making macros

## Setup:
First, this assumes that CORE is set up as in the `setup.sh` script at `VVVBabyMaker` level. Else you need to fix the links in all macros for the dorky/goodrun utilities.

Then, run the setup script, which creates all directories and moves necessary helper files (SF, FR, json) to the correct location.
``` bash
. setup.sh
```
The directories are used to store rootfiles, etc.

## Loopers (doAll.C)

We have many loopers.
All are called from
``` bash
root -l -b -q doAll.C
```

The loopers are quickly described below.
Note, that here I loop over background combined.

Most necessary functions needed are in the file `Functions.h/.C`.

### SRLooper.C

Makes preselection and full selection simulation vs. data histograms for the signal region, WZ control region, and FR application region.
It also creates event lists for all samples (if switched on - see `storeeventnumbers`), and allows to investigate single events (see `addeventtocheck`).
Signal regions can be blinded.

### FakeRateMethod.C

Calculate fake background using application region yields and apply fake rate appropriately. - To be implemented: closure uncertainty variations. Background subraction uncertainty?
Signal regions can be blinded.

### Check3lWZCR.C

Calculate 3l CR yields and variations (same for SR) - actual prediction is done separately (currently mostly done by hand, thus script still needs to be cleaned up.

### WWTTWSplitter.C

As I cluster all WW and all ttV into one histo, this small macro splits these so that we can assign uncertainties properly to VBS, DPS, ttW.
Loop over `WW` and `ttV`.
(This is not strictly needed to do this way.)

### ValidationLooper.C

Create histogram for the Zgamma, ttW, and WW VBS validation regions. One could add Mjj sideband validation region easily here.
Allow to also loop over `WW` and `ttV`.

### Nminus1Looper.C

Create histograms at preselection level and (N-1) level of interesting kinematic variables (I chose the kinematic variables we cut on).

### Skimmer.C

Skim looper by requiring either exactly 2 SS leptons (tight+tight or tight+loose), or at least 3 3l leptons (3tight or 2tight+loose), drop unused branches.
This should do the same as Philip's looper, but Philip's is setup to run on the batch system.

## Plot Making

There are three scripts here. The two C macros are almost the same but for the legend/axes. the python macro should work as the C macro.

### makePlotsProcessSRplot.C

Make the 6 bin SR (or CR/AR) plots.

### makePlotsProcess.C

Make plot of kinematic variables.

### MakePlot.py

python version of C macro.


## Table Maker

There is one table maker file (`makeBigTable.C`) which created table 7 of AN.
