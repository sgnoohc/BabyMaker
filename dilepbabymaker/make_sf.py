#!/bin/env python

import ROOT as r

import sys

mc_tfile_path = sys.argv[1]
data_tfile_path = sys.argv[2]
output_func_path = sys.argv[3]

mc_tfile   = r.TFile(mc_tfile_path)
data_tfile = r.TFile(data_tfile_path)

mc_h_eff_pt_vs_eta = mc_tfile.Get("h_eff_pt_vs_eta")
data_h_eff_pt_vs_eta = data_tfile.Get("h_eff_pt_vs_eta")

data_h_eff_pt_vs_eta.Divide(mc_h_eff_pt_vs_eta)

from rooutil import printsf

printsf.printsf_th2(output_func_path, data_h_eff_pt_vs_eta, xvarabs=True)
