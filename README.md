TUAFhis repository is used to produce babies for the VVV analysis. It makes use of AutoTwopler from NTupleTools and CORE.

To make babies, first checkout this repository

```bash
git clone git@github.com:cmstas/VVVBabyMaker.git
git checkout <RELEVANT TAG>
```
Then pull in CORE, Software, and NTuple tools in the top level directory:

```bash
cd VVVBabyMaker
git clone git@github.com:cmstas/CORE.git
git clone git@github.com:cmstas/NtupleTools.git
git clone git@github.com:cmstas/Software.git
cd Software/
git checkout root6
cd ..
```

Now the directory structure should have VVVBabyMaker at the top level and CORE, Software, NTupleTools, dilepbabymaker, and json as subdirectories.

Make sure you have ROOT setup. On the grid, the babymaker runs with ``CMSSW_8_0_5``, so it's best to compile all the code with that version:

```bash
CMSSW_VERSION=CMSSW_8_0_5
export SCRAM_ARCH=slc6_amd64_gcc530
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /cvmfs/cms.cern.ch/$SCRAM_ARCH/cms/cmssw/$CMSSW_VERSION/src
eval `scramv1 runtime -sh`
cd -
```

Then, you can compile and test the code works by going into dilepbabymaker and running dotest.sh (you'll need to symlink CORE into this directory as well):

```bash
cd dilepbabymaker/
ln -s ../CORE 
make -j15
./dotest.sh
```

This will test that the looper compiles and there are no seg faults or other book-keeping issues with ScanChain. Submission to the batch system via the AutoTwopler is covered below. 

### Submission to the grid

To submit babymaking jobs to the grid, a few files will need to be edited. We assume that you have tested your code as above and that `dotest.sh` did not return any errors.

At this point, you need to run the setup script for the AutoTwopler:

```bash
cd NtupleTools/AutoTwopler/
. setup.sh
cd ..
```

Note: all the steps up to this point can be completed by sourcing setup.sh from VVVBabyMaker/

If you have made changes to the looper, then you will want to change the tag for the code in AutoTwopler. Go into dilepbabymaker/batchsubmit/ and edit the vvv.tag string in ducks.py to have a descriptive tag name.

Otherwise, you are ready to pick your samples and launch babies.

#### Choosing your samples

The samples are chosen in `dilepbabymaker/batchsubmit/vvv.py`. The dictionary `d_ds2name` contains two entries `background` and `data`, each of which are a dictionary that contains the dataset name a key and a shortname as a value. 
If the sample you'd like to run over is already in the `d_ds2name`, then simply comment out all other samples, go into `ducks.py` and update the `samples_types` list to include `background` and `data` as neccesary. For example, if `sample_types` does not include `data`, then no samples in the `data` dictionary will be processes.

To add a new sample, simply add an entry to the `data` or `background` dictionary with the dataset name (can be found using [DIS](http://uaf-8.t2.ucsd.edu/~namin/makers/disMaker/index.html) ) and a descriptive short name.

#### Launching the jobs

You will almost certainly want to setup a screen instance before you continue since AutoTwopler monitors your jobs but is not daemonized.

Once the screen is setup, from inside `dilepbabymaker/batchsubmit/`, run 

```bash
python ducks.py
```

It may take some time for the jobs to submit, but once they are all submitted, you should be able to access http://uaf-7.t2.ucsd.edu/~<USERNAME>/AutoTwopler_VVVbabies/ to see the progress of your babies.
If some of your jobs are not finishing, it could mean the files are corrupted. In many cases, it's fine to just kill those jobs as it will only have a small effect on the cross section for large datasets.

#### Jobs not finishing:
If some samples on your webpage are stuck at 90 something percent for a long time, it might mean the sample has a corruption. NOTE: 99% means the sample files are merging, do not follow these instructions for samples at 99% unless you want to kill the merge.

You can tell AutoTwopler to disband those "tail jobs" by going into `VVVBabyMaker/NtupleTools/AutoTwopler/` and making a file called `actions.txt`. In `actions.txt`, write a line seperated list of sample names followed by a colon and `baby_skip_tail`.
For instance, to skip the tails of the following two samples:

```bash
/ZZTo2L2Nu_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM
/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM
```

make `actions.txt` read:

```bash
/ZZTo2L2Nu_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM: baby_skip_tail
/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM: baby_skip_tail
```

#### Checking Your Samples

As mentioned previously, you can check on the progress of babymaking through the AutoTwopler web interface at `http://uaf-7.t2.ucsd.edu/~<USERNAME>/AutoTwopler_VVVbabies/`. Once these jobs show 100%, then that means that your babies are merged and ready on hadoop. 
The path where you can find these files is `/hadoop/cms/store/user/bhashemi/AutoTwopler_babies/merged/VVV/<vvv.tag>/`. If you have setup the rsync line properly in `ducks.py`, the files will be automatically synced onto nfs-7 when all the jobs are completed.

#### Useful commands:

Tagging your code

git tag -a <version> -m 'add a message'

git push --tags

