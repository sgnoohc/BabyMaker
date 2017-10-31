import ROOT
import math

f = ROOT.TFile("rootfiles/FakeRateHistograms.root","open")

def sumvar(variations):
    return math.sqrt(sum([x*x for x in variations]))

def histlist(hist):
    content = []
    error = []
    for i in range(0,8):
        content.append(hist.GetBinContent(i))
        error.append(hist.GetBinError(i))
    return content,error
       
nominal,nominale = histlist(f.Get("SRyield_fakesPred"))
frup,frupe = histlist(f.Get("FakeEstimationFRup_fakesPred"))
frdn,frdne = histlist(f.Get("FakeEstimationFRdn_fakesPred"))
closuredn,closuredne = histlist(f.Get("FakeEstimationClosuredn_fakesPred"))
closureup,closureupe = histlist(f.Get("FakeEstimationClosureup_fakesPred"))

bins = ['ee','em','mm','0SFOS','1SFOS','2SFOS']

for i in range(1,7):
    upvars = [nominale[i],frup[i]-nominal[i],closureup[i]-nominal[i]]
    dnvars = [nominale[i],frdn[i]-nominal[i],closuredn[i]-nominal[i]]    
    print bins[i-1],'$%.2f'%nominal[i],'\pm','%.2f$'%sumvar(upvars)
