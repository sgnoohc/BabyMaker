# Measurement Region / Fake rate / Closure test code

## Setup and running the code

First setup the code

    > source setup.sh

Then run the code

    > sh run.sh

Output plots should be located in ```plots```

# Brief explanation of the code

```loop.py``` loops over the samples in nfs area.
It uses the ```QFramework``` from rooutil/qframework.
All of the cut definitons, histogram defintions and weight definitions are in the loop.py as strings.
Not a single for loop is necessary to loop over all the samples.
N.B. loop.py launches multiprocessing to speed up the looping.

```printqcdfakerate.py``` prints out the "fake-factor" into a root file.
Once the fake-factor (= fr / 1 - fr) is printed out into a root file, ```loop.py``` should be called again.
In the ```loop.py``` there are lines that contains "TH2Map".
This line tells the QFramework to open up the file and use the histogram and get the weights.

This above procedure is what is being done in ```run.sh```
