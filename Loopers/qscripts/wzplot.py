#!/bin/env python

import ROOT
from rooutil import plottery_wrapper as p
from plottery import plottery as ply

ROOT.gStyle.SetOptStat(0)

tfile = ROOT.TFile("samples/wz.root")
ttree = tfile.Get("t")

ttree.Draw("nj30>>h_nj30_ss(6,0,6)", "((n_tight_ss_lep==2)&&(n_veto_ss_lep==2))*(weight*lepsf*purewgt)")
ttree.Draw("nj30>>h_nj30_3l(6,0,6)", "((n_tight_3l_lep==3)&&(n_veto_3l_lep==3))*(weight*lepsf*purewgt)")

h_nj30_ss = ROOT.gDirectory.Get("h_nj30_ss")
h_nj30_3l = ROOT.gDirectory.Get("h_nj30_3l")

tfile_v18 = ROOT.TFile("/hadoop/cms/store/user/phchang/metis/wwwanalysis/WWW_v0_1_18_minibaby_v4.2/wz.root")
ttree_v18 = tfile_v18.Get("t")

ttree_v18.Draw("nj30>>h_nj30_ss_v18(6,0,6)", "((n_tight_ss_lep==2)&&(n_veto_ss_lep==2))*(weight*lepsf*purewgt)")
ttree_v18.Draw("nj30>>h_nj30_3l_v18(6,0,6)", "((n_tight_3l_lep==3)&&(n_veto_3l_lep==3))*(weight*lepsf*purewgt)")

h_nj30_ss_v18 = ROOT.gDirectory.Get("h_nj30_ss_v18")
h_nj30_3l_v18 = ROOT.gDirectory.Get("h_nj30_3l_v18")

#h_nj30_ss.Scale(1./h_nj30_ss.Integral())
#h_nj30_ss_v18.Scale(1./h_nj30_ss_v18.Integral())
#
#h_nj30_3l.Scale(1./h_nj30_3l.Integral())
#h_nj30_3l_v18.Scale(1./h_nj30_3l_v18.Integral())

h_nj30_ss_v18.SetName("WZ v0.1.18 (old)")
h_nj30_3l_v18.SetName("WZ v0.1.18 (old)")
p.plot_hist(data=h_nj30_ss, bgs=[h_nj30_ss_v18], colors=[7003], options={"output_name": "wzplots/njet_ss_channel.png", "legend_datalabel":"WZ v1.0.3 (new)", "legend_scalex": 1.6, "xaxis_label":"Njet"})
p.plot_hist(data=h_nj30_3l, bgs=[h_nj30_3l_v18], colors=[7003], options={"output_name": "wzplots/njet_3l_channel.png", "legend_datalabel":"WZ v1.0.3 (new)", "legend_scalex": 1.6, "xaxis_label":"Njet"})


#eof
