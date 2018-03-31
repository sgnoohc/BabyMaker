#!/bin/env python

import ROOT as r

import sys

tfilename = "../../trigeff/trigeff.root"
tfile = r.TFile(tfilename)

dimu_dz_eta_v_eta_data = tfile.Get("dimu_dz_eta_v_eta_data")
diel_dz_eta_v_eta_data = tfile.Get("diel_dz_eta_v_eta_data")
mu_lead_leg_pt_v_eta_data = tfile.Get("mu_lead_leg_pt_v_eta_data")
mu_trail_leg_pt_v_eta_data = tfile.Get("mu_trail_leg_pt_v_eta_data")
el_lead_leg_pt_v_eta_data = tfile.Get("el_lead_leg_pt_v_eta_data")
el_trail_leg_pt_v_eta_data = tfile.Get("el_trail_leg_pt_v_eta_data")
em_muon_leg_pt_v_eta_data = tfile.Get("em_muon_leg_pt_v_eta_data")
emu_dz_etae_v_etam_data = tfile.Get("emu_dz_etae_v_etam_data")

from rooutil import printsf

printsf.printsf_th2("trigeff_dimu_dz", dimu_dz_eta_v_eta_data, xvar="etalead", yvar="etatrail", xvarabs=True, yvarabs=True)
printsf.printsf_th2("trigeff_diel_dz", diel_dz_eta_v_eta_data, xvar="etalead", yvar="etatrail", xvarabs=True, yvarabs=True)
printsf.printsf_th2("trigeff_emu_dz", emu_dz_etae_v_etam_data, xvar="etaelec", yvar="etamuon", xvarabs=True, yvarabs=True)
printsf.printsf_th2("trigeff_mu_lead", mu_lead_leg_pt_v_eta_data, xvar="pt", yvar="eta", yvarabs=True)
printsf.printsf_th2("trigeff_mu_trail", mu_trail_leg_pt_v_eta_data, xvar="pt", yvar="eta", yvarabs=True)
printsf.printsf_th2("trigeff_el_lead", el_lead_leg_pt_v_eta_data, xvar="pt", yvar="eta", yvarabs=True)
printsf.printsf_th2("trigeff_el_trail", el_trail_leg_pt_v_eta_data, xvar="pt", yvar="eta", yvarabs=True)
printsf.printsf_th2("trigeff_mu_muon", em_muon_leg_pt_v_eta_data, xvar="pt", yvar="eta", yvarabs=True)
