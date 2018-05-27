# Fake background estimation analysis code

## Two versions for closure

The closure test was performed with two different selection. (One is looser)  
This was so that we have more statistics.  
Both show pretty good closure test.  

in loop.py there is "twolep_cuts" string that defines the cut applied for the application region.  
 
    twolep_cuts = "(lep_pdgId[0]*lep_pdgId[1]>0)*(nj30>=2)" # if removing bveto
    twolep_cuts = "(lep_pdgId[0]*lep_pdgId[1]>0)*(nj30>=2)*(nb==0)" # with bveto

One should choose which one to run and run the below code  

## Setup and running the code

First setup the code

    > source setup.sh

Then run the code

    > sh run.sh

Output plots should be located in ```plots```

## Brief explanation of the code

```loop.py``` loops over the samples in nfs area.  
It uses the ```QFramework``` from ```rooutil/qframework```.  
All of the cut definitons, histogram defintions and weight definitions are in the loop.py as strings.  
Not a single for loop is necessary to loop over all the samples.  
N.B. loop.py launches multiprocessing to speed up the looping.  

```printqcdfakerate.py``` prints out the "fake-factor" into a root file.  
Once the fake-factor (= fr / 1 - fr) is printed out into a root file, ```loop.py``` should be called again.  
In the ```loop.py``` there are lines that contains "TH2Map".  
This line tells the QFramework to open up the file and use the histogram and get the weights.  

This above procedure is what is being done in ```run.sh```  

## Checking statuses of samples and selections

The following will check the sample connection status and print the cut selection structure and exit the code without looping

     > python loop.py -1

The key script is the following line in ```loop.py```

    samples.printContents("t[*status]rd")
    cuts.printCut("trd")

Each samples should say ```"[  OK  ]"```

## Few tips

When writing down complex string expression sometimes the code will crash with warning about TQObservable etc.  
What happens under the hood of the ```QFramework``` is that it parses the expression and creates TTreeFormula instances.  
And by putting [] around certain element of expressions can help the code understand how to efficiently parse the expression.  
    e.g. [lep_pt[0]>20.] * [lep_eta[0] < 2.4]
