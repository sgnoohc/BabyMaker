#!/bin/env python

import ROOT as r

import sys

tfilename = "../../trigeff/trigeff.root"
tfile = r.TFile(tfilename)

dimu_dz_eta_v_eta_sf = tfile.Get("dimu_dz_eta_v_eta_sf")
diel_dz_eta_v_eta_sf = tfile.Get("diel_dz_eta_v_eta_sf")
mu_lead_leg_eta_v_pt_sf = tfile.Get("mu_lead_leg_eta_v_pt_sf")
mu_trail_leg_eta_v_pt_sf = tfile.Get("mu_trail_leg_eta_v_pt_sf")
el_lead_leg_eta_v_pt_sf = tfile.Get("el_lead_leg_eta_v_pt_sf")
el_trail_leg_eta_v_pt_sf = tfile.Get("el_trail_leg_eta_v_pt_sf")

from rooutil import printsf

printsf.printsf_th2("trigeff_dimu_dz", dimu_dz_eta_v_eta_sf, xvar="etalead", yvar="etatrail", xvarabs=True, yvarabs=True)
printsf.printsf_th2("trigeff_diel_dz", diel_dz_eta_v_eta_sf, xvar="etalead", yvar="etatrail", xvarabs=True, yvarabs=True)
printsf.printsf_th2("trigeff_mu_lead", mu_lead_leg_eta_v_pt_sf, xvar="eta", yvar="pt", xvarabs=True)
printsf.printsf_th2("trigeff_mu_trail", mu_trail_leg_eta_v_pt_sf, xvar="eta", yvar="pt", xvarabs=True)
printsf.printsf_th2("trigeff_el_lead", el_lead_leg_eta_v_pt_sf, xvar="eta", yvar="pt", xvarabs=True)
printsf.printsf_th2("trigeff_el_trail", el_trail_leg_eta_v_pt_sf, xvar="eta", yvar="pt", xvarabs=True)
