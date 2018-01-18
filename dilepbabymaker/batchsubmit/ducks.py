import sys, os
sys.path.insert(0,"../../NtupleTools/AutoTwopler")
import run
import params as p
import vvv as vvv

# set tag
vvv.tag = "WWW_v0.1.18"

# make instructions
instructions = []

##
## make instructions by class of sample
##
samples_types = ["backgrounds", "data"]
#samples_types = ["backgrounds"]
#samples_types = ["data"]
for stype in samples_types:
    for ds in vvv.d_ds2name[stype].keys():
        instructions.append({"executable": vvv.executable, "package": vvv.package, "analysis": "VVV", "dataset": ds, "baby_tag": vvv.tag, "type": "BABY", "extra": [-1, "output.root,skim.root"]})

##
## make instructions by sample shortname
##
#todo = "wjets_ht1200_mgmlm_nonext ".strip().split()
#instructions = [inst for inst in instructions if zmet.dataset_to_shortname(inst["dataset"]) in todo]

#print instructions
#sys.exit()

p.dataset_to_shortname = vvv.dataset_to_shortname
p.dashboard_name = vvv.dashboard_name
p.sweepRoot_scripts = vvv.sweepRoot_scripts
p.merging_scripts = vvv.merging_scripts
p.baby_merged_dir = vvv.baby_merged_dir
p.merge_babies_on_condor = vvv.merge_babies_on_condor
p.exit_when_done = True
p.do_cms3 = True

run.main(instructions=instructions, params=p)

# instructions = [ 
#         {
#             "dataset": "/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM",
#             "type": "BABY",
#             "extra": "",
#             "baby_tag": "v0.01",
#             "analysis": "ZMET",
#             "package": ss.package,
#             "executable": ss.executable,
#             }
#         ]

# p.merging_scripts = ["frank/merge.sh", "frank/merge.C"]
# p.dashboard_name = "AutoTwopler_test"
# p.merge_babies_on_condor = True
# run.main(instructions=instructions, params=p, do_one_iteration=True)

if (not os.path.isdir("/nfs-7/userdata/%s/WWW_babies/" % os.getenv("USER") ) ):
  os.system("mkdir -p /nfs-7/userdata/%s/WWW_babies/" % os.getenv("USER"))
os.system("rsync -avz /hadoop/cms/store/user/%s/AutoTwopler_babies/merged/VVV/%s/ /nfs-7/userdata/%s/WWW_babies/%s" % (os.getenv("USER"), vvv.tag, os.getenv("USER"), vvv.tag) ) #Should remake the tarball and ensure running ducks always takes the newest code.
