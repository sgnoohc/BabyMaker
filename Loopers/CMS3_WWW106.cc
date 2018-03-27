#include "CMS3_WWW106.h"
CMS3 cms3;

void CMS3::Init(TTree *tree) {
  lep_p4_branch = tree->GetBranch("lep_p4");
  if (lep_p4_branch) lep_p4_branch->SetAddress(&lep_p4_);
  jets_p4_branch = tree->GetBranch("jets_p4");
  if (jets_p4_branch) jets_p4_branch->SetAddress(&jets_p4_);
  jets_up_p4_branch = tree->GetBranch("jets_up_p4");
  if (jets_up_p4_branch) jets_up_p4_branch->SetAddress(&jets_up_p4_);
  jets_dn_p4_branch = tree->GetBranch("jets_dn_p4");
  if (jets_dn_p4_branch) jets_dn_p4_branch->SetAddress(&jets_dn_p4_);
  genPart_p4_branch = tree->GetBranch("genPart_p4");
  if (genPart_p4_branch) genPart_p4_branch->SetAddress(&genPart_p4_);

  tree->SetMakeClass(1);

  run_branch = tree->GetBranch("run");
  if (run_branch) run_branch->SetAddress(&run_);
  lumi_branch = tree->GetBranch("lumi");
  if (lumi_branch) lumi_branch->SetAddress(&lumi_);
  evt_branch = tree->GetBranch("evt");
  if (evt_branch) evt_branch->SetAddress(&evt_);
  isData_branch = tree->GetBranch("isData");
  if (isData_branch) isData_branch->SetAddress(&isData_);
  evt_scale1fb_branch = tree->GetBranch("evt_scale1fb");
  if (evt_scale1fb_branch) evt_scale1fb_branch->SetAddress(&evt_scale1fb_);
  evt_passgoodrunlist_branch = tree->GetBranch("evt_passgoodrunlist");
  if (evt_passgoodrunlist_branch) evt_passgoodrunlist_branch->SetAddress(&evt_passgoodrunlist_);
  HLT_DoubleMu_branch = tree->GetBranch("HLT_DoubleMu");
  if (HLT_DoubleMu_branch) HLT_DoubleMu_branch->SetAddress(&HLT_DoubleMu_);
  HLT_DoubleEl_branch = tree->GetBranch("HLT_DoubleEl");
  if (HLT_DoubleEl_branch) HLT_DoubleEl_branch->SetAddress(&HLT_DoubleEl_);
  HLT_DoubleEl_DZ_branch = tree->GetBranch("HLT_DoubleEl_DZ");
  if (HLT_DoubleEl_DZ_branch) HLT_DoubleEl_DZ_branch->SetAddress(&HLT_DoubleEl_DZ_);
  HLT_DoubleEl_DZ_2_branch = tree->GetBranch("HLT_DoubleEl_DZ_2");
  if (HLT_DoubleEl_DZ_2_branch) HLT_DoubleEl_DZ_2_branch->SetAddress(&HLT_DoubleEl_DZ_2_);
  HLT_MuEG_branch = tree->GetBranch("HLT_MuEG");
  if (HLT_MuEG_branch) HLT_MuEG_branch->SetAddress(&HLT_MuEG_);
  mc_HLT_DoubleMu_branch = tree->GetBranch("mc_HLT_DoubleMu");
  if (mc_HLT_DoubleMu_branch) mc_HLT_DoubleMu_branch->SetAddress(&mc_HLT_DoubleMu_);
  mc_HLT_DoubleEl_branch = tree->GetBranch("mc_HLT_DoubleEl");
  if (mc_HLT_DoubleEl_branch) mc_HLT_DoubleEl_branch->SetAddress(&mc_HLT_DoubleEl_);
  mc_HLT_DoubleEl_DZ_branch = tree->GetBranch("mc_HLT_DoubleEl_DZ");
  if (mc_HLT_DoubleEl_DZ_branch) mc_HLT_DoubleEl_DZ_branch->SetAddress(&mc_HLT_DoubleEl_DZ_);
  mc_HLT_DoubleEl_DZ_2_branch = tree->GetBranch("mc_HLT_DoubleEl_DZ_2");
  if (mc_HLT_DoubleEl_DZ_2_branch) mc_HLT_DoubleEl_DZ_2_branch->SetAddress(&mc_HLT_DoubleEl_DZ_2_);
  mc_HLT_MuEG_branch = tree->GetBranch("mc_HLT_MuEG");
  if (mc_HLT_MuEG_branch) mc_HLT_MuEG_branch->SetAddress(&mc_HLT_MuEG_);
  lep_pt_branch = tree->GetBranch("lep_pt");
  if (lep_pt_branch) lep_pt_branch->SetAddress(&lep_pt_);
  lep_eta_branch = tree->GetBranch("lep_eta");
  if (lep_eta_branch) lep_eta_branch->SetAddress(&lep_eta_);
  lep_phi_branch = tree->GetBranch("lep_phi");
  if (lep_phi_branch) lep_phi_branch->SetAddress(&lep_phi_);
  lep_coneCorrPt_branch = tree->GetBranch("lep_coneCorrPt");
  if (lep_coneCorrPt_branch) lep_coneCorrPt_branch->SetAddress(&lep_coneCorrPt_);
  lep_ip3d_branch = tree->GetBranch("lep_ip3d");
  if (lep_ip3d_branch) lep_ip3d_branch->SetAddress(&lep_ip3d_);
  lep_ip3derr_branch = tree->GetBranch("lep_ip3derr");
  if (lep_ip3derr_branch) lep_ip3derr_branch->SetAddress(&lep_ip3derr_);
  lep_isTriggerSafe_v1_branch = tree->GetBranch("lep_isTriggerSafe_v1");
  if (lep_isTriggerSafe_v1_branch) lep_isTriggerSafe_v1_branch->SetAddress(&lep_isTriggerSafe_v1_);
  lep_lostHits_branch = tree->GetBranch("lep_lostHits");
  if (lep_lostHits_branch) lep_lostHits_branch->SetAddress(&lep_lostHits_);
  lep_convVeto_branch = tree->GetBranch("lep_convVeto");
  if (lep_convVeto_branch) lep_convVeto_branch->SetAddress(&lep_convVeto_);
  lep_motherIdSS_branch = tree->GetBranch("lep_motherIdSS");
  if (lep_motherIdSS_branch) lep_motherIdSS_branch->SetAddress(&lep_motherIdSS_);
  lep_pass_VVV_cutbased_3l_fo_branch = tree->GetBranch("lep_pass_VVV_cutbased_3l_fo");
  if (lep_pass_VVV_cutbased_3l_fo_branch) lep_pass_VVV_cutbased_3l_fo_branch->SetAddress(&lep_pass_VVV_cutbased_3l_fo_);
  lep_pass_VVV_cutbased_3l_tight_branch = tree->GetBranch("lep_pass_VVV_cutbased_3l_tight");
  if (lep_pass_VVV_cutbased_3l_tight_branch) lep_pass_VVV_cutbased_3l_tight_branch->SetAddress(&lep_pass_VVV_cutbased_3l_tight_);
  lep_pass_VVV_cutbased_fo_branch = tree->GetBranch("lep_pass_VVV_cutbased_fo");
  if (lep_pass_VVV_cutbased_fo_branch) lep_pass_VVV_cutbased_fo_branch->SetAddress(&lep_pass_VVV_cutbased_fo_);
  lep_pass_VVV_cutbased_tight_branch = tree->GetBranch("lep_pass_VVV_cutbased_tight");
  if (lep_pass_VVV_cutbased_tight_branch) lep_pass_VVV_cutbased_tight_branch->SetAddress(&lep_pass_VVV_cutbased_tight_);
  lep_pass_VVV_cutbased_veto_branch = tree->GetBranch("lep_pass_VVV_cutbased_veto");
  if (lep_pass_VVV_cutbased_veto_branch) lep_pass_VVV_cutbased_veto_branch->SetAddress(&lep_pass_VVV_cutbased_veto_);
  lep_pass_VVV_cutbased_fo_noiso_branch = tree->GetBranch("lep_pass_VVV_cutbased_fo_noiso");
  if (lep_pass_VVV_cutbased_fo_noiso_branch) lep_pass_VVV_cutbased_fo_noiso_branch->SetAddress(&lep_pass_VVV_cutbased_fo_noiso_);
  lep_pass_VVV_cutbased_tight_noiso_branch = tree->GetBranch("lep_pass_VVV_cutbased_tight_noiso");
  if (lep_pass_VVV_cutbased_tight_noiso_branch) lep_pass_VVV_cutbased_tight_noiso_branch->SetAddress(&lep_pass_VVV_cutbased_tight_noiso_);
  lep_pass_VVV_cutbased_veto_noiso_branch = tree->GetBranch("lep_pass_VVV_cutbased_veto_noiso");
  if (lep_pass_VVV_cutbased_veto_noiso_branch) lep_pass_VVV_cutbased_veto_noiso_branch->SetAddress(&lep_pass_VVV_cutbased_veto_noiso_);
  lep_pdgId_branch = tree->GetBranch("lep_pdgId");
  if (lep_pdgId_branch) lep_pdgId_branch->SetAddress(&lep_pdgId_);
  lep_dxy_branch = tree->GetBranch("lep_dxy");
  if (lep_dxy_branch) lep_dxy_branch->SetAddress(&lep_dxy_);
  lep_dz_branch = tree->GetBranch("lep_dz");
  if (lep_dz_branch) lep_dz_branch->SetAddress(&lep_dz_);
  lep_ptRatio_branch = tree->GetBranch("lep_ptRatio");
  if (lep_ptRatio_branch) lep_ptRatio_branch->SetAddress(&lep_ptRatio_);
  lep_ptRel_branch = tree->GetBranch("lep_ptRel");
  if (lep_ptRel_branch) lep_ptRel_branch->SetAddress(&lep_ptRel_);
  lep_pterr_branch = tree->GetBranch("lep_pterr");
  if (lep_pterr_branch) lep_pterr_branch->SetAddress(&lep_pterr_);
  lep_relIso03EAv2_branch = tree->GetBranch("lep_relIso03EAv2");
  if (lep_relIso03EAv2_branch) lep_relIso03EAv2_branch->SetAddress(&lep_relIso03EAv2_);
  lep_relIso04EAv2_branch = tree->GetBranch("lep_relIso04EAv2");
  if (lep_relIso04EAv2_branch) lep_relIso04EAv2_branch->SetAddress(&lep_relIso04EAv2_);
  lep_tightCharge_branch = tree->GetBranch("lep_tightCharge");
  if (lep_tightCharge_branch) lep_tightCharge_branch->SetAddress(&lep_tightCharge_);
  lep_trk_pt_branch = tree->GetBranch("lep_trk_pt");
  if (lep_trk_pt_branch) lep_trk_pt_branch->SetAddress(&lep_trk_pt_);
  lep_charge_branch = tree->GetBranch("lep_charge");
  if (lep_charge_branch) lep_charge_branch->SetAddress(&lep_charge_);
  lep_etaSC_branch = tree->GetBranch("lep_etaSC");
  if (lep_etaSC_branch) lep_etaSC_branch->SetAddress(&lep_etaSC_);
  lep_MVA_branch = tree->GetBranch("lep_MVA");
  if (lep_MVA_branch) lep_MVA_branch->SetAddress(&lep_MVA_);
  lep_isFromW_branch = tree->GetBranch("lep_isFromW");
  if (lep_isFromW_branch) lep_isFromW_branch->SetAddress(&lep_isFromW_);
  lep_isFromZ_branch = tree->GetBranch("lep_isFromZ");
  if (lep_isFromZ_branch) lep_isFromZ_branch->SetAddress(&lep_isFromZ_);
  lep_isFromB_branch = tree->GetBranch("lep_isFromB");
  if (lep_isFromB_branch) lep_isFromB_branch->SetAddress(&lep_isFromB_);
  lep_isFromC_branch = tree->GetBranch("lep_isFromC");
  if (lep_isFromC_branch) lep_isFromC_branch->SetAddress(&lep_isFromC_);
  lep_isFromL_branch = tree->GetBranch("lep_isFromL");
  if (lep_isFromL_branch) lep_isFromL_branch->SetAddress(&lep_isFromL_);
  lep_isFromLF_branch = tree->GetBranch("lep_isFromLF");
  if (lep_isFromLF_branch) lep_isFromLF_branch->SetAddress(&lep_isFromLF_);
  lep_genPart_index_branch = tree->GetBranch("lep_genPart_index");
  if (lep_genPart_index_branch) lep_genPart_index_branch->SetAddress(&lep_genPart_index_);
  jets_csv_branch = tree->GetBranch("jets_csv");
  if (jets_csv_branch) jets_csv_branch->SetAddress(&jets_csv_);
  jets_up_csv_branch = tree->GetBranch("jets_up_csv");
  if (jets_up_csv_branch) jets_up_csv_branch->SetAddress(&jets_up_csv_);
  jets_dn_csv_branch = tree->GetBranch("jets_dn_csv");
  if (jets_dn_csv_branch) jets_dn_csv_branch->SetAddress(&jets_dn_csv_);
  met_pt_branch = tree->GetBranch("met_pt");
  if (met_pt_branch) met_pt_branch->SetAddress(&met_pt_);
  met_phi_branch = tree->GetBranch("met_phi");
  if (met_phi_branch) met_phi_branch->SetAddress(&met_phi_);
  met_up_pt_branch = tree->GetBranch("met_up_pt");
  if (met_up_pt_branch) met_up_pt_branch->SetAddress(&met_up_pt_);
  met_up_phi_branch = tree->GetBranch("met_up_phi");
  if (met_up_phi_branch) met_up_phi_branch->SetAddress(&met_up_phi_);
  met_dn_pt_branch = tree->GetBranch("met_dn_pt");
  if (met_dn_pt_branch) met_dn_pt_branch->SetAddress(&met_dn_pt_);
  met_dn_phi_branch = tree->GetBranch("met_dn_phi");
  if (met_dn_phi_branch) met_dn_phi_branch->SetAddress(&met_dn_phi_);
  firstgoodvertex_branch = tree->GetBranch("firstgoodvertex");
  if (firstgoodvertex_branch) firstgoodvertex_branch->SetAddress(&firstgoodvertex_);
  nTrueInt_branch = tree->GetBranch("nTrueInt");
  if (nTrueInt_branch) nTrueInt_branch->SetAddress(&nTrueInt_);
  nVert_branch = tree->GetBranch("nVert");
  if (nVert_branch) nVert_branch->SetAddress(&nVert_);
  nisoTrack_mt2_cleaned_VVV_cutbased_veto_branch = tree->GetBranch("nisoTrack_mt2_cleaned_VVV_cutbased_veto");
  if (nisoTrack_mt2_cleaned_VVV_cutbased_veto_branch) nisoTrack_mt2_cleaned_VVV_cutbased_veto_branch->SetAddress(&nisoTrack_mt2_cleaned_VVV_cutbased_veto_);
  weight_btagsf_branch = tree->GetBranch("weight_btagsf");
  if (weight_btagsf_branch) weight_btagsf_branch->SetAddress(&weight_btagsf_);
  weight_btagsf_heavy_DN_branch = tree->GetBranch("weight_btagsf_heavy_DN");
  if (weight_btagsf_heavy_DN_branch) weight_btagsf_heavy_DN_branch->SetAddress(&weight_btagsf_heavy_DN_);
  weight_btagsf_heavy_UP_branch = tree->GetBranch("weight_btagsf_heavy_UP");
  if (weight_btagsf_heavy_UP_branch) weight_btagsf_heavy_UP_branch->SetAddress(&weight_btagsf_heavy_UP_);
  weight_btagsf_light_DN_branch = tree->GetBranch("weight_btagsf_light_DN");
  if (weight_btagsf_light_DN_branch) weight_btagsf_light_DN_branch->SetAddress(&weight_btagsf_light_DN_);
  weight_btagsf_light_UP_branch = tree->GetBranch("weight_btagsf_light_UP");
  if (weight_btagsf_light_UP_branch) weight_btagsf_light_UP_branch->SetAddress(&weight_btagsf_light_UP_);
  gen_ht_branch = tree->GetBranch("gen_ht");
  if (gen_ht_branch) gen_ht_branch->SetAddress(&gen_ht_);
  genPart_motherId_branch = tree->GetBranch("genPart_motherId");
  if (genPart_motherId_branch) genPart_motherId_branch->SetAddress(&genPart_motherId_);
  genPart_pdgId_branch = tree->GetBranch("genPart_pdgId");
  if (genPart_pdgId_branch) genPart_pdgId_branch->SetAddress(&genPart_pdgId_);
  genPart_charge_branch = tree->GetBranch("genPart_charge");
  if (genPart_charge_branch) genPart_charge_branch->SetAddress(&genPart_charge_);
  genPart_status_branch = tree->GetBranch("genPart_status");
  if (genPart_status_branch) genPart_status_branch->SetAddress(&genPart_status_);
  ngenLep_branch = tree->GetBranch("ngenLep");
  if (ngenLep_branch) ngenLep_branch->SetAddress(&ngenLep_);
  ngenLepFromTau_branch = tree->GetBranch("ngenLepFromTau");
  if (ngenLepFromTau_branch) ngenLepFromTau_branch->SetAddress(&ngenLepFromTau_);
  Flag_AllEventFilters_branch = tree->GetBranch("Flag_AllEventFilters");
  if (Flag_AllEventFilters_branch) Flag_AllEventFilters_branch->SetAddress(&Flag_AllEventFilters_);
  Flag_EcalDeadCellTriggerPrimitiveFilter_branch = tree->GetBranch("Flag_EcalDeadCellTriggerPrimitiveFilter");
  if (Flag_EcalDeadCellTriggerPrimitiveFilter_branch) Flag_EcalDeadCellTriggerPrimitiveFilter_branch->SetAddress(&Flag_EcalDeadCellTriggerPrimitiveFilter_);
  Flag_HBHEIsoNoiseFilter_branch = tree->GetBranch("Flag_HBHEIsoNoiseFilter");
  if (Flag_HBHEIsoNoiseFilter_branch) Flag_HBHEIsoNoiseFilter_branch->SetAddress(&Flag_HBHEIsoNoiseFilter_);
  Flag_HBHENoiseFilter_branch = tree->GetBranch("Flag_HBHENoiseFilter");
  if (Flag_HBHENoiseFilter_branch) Flag_HBHENoiseFilter_branch->SetAddress(&Flag_HBHENoiseFilter_);
  Flag_badChargedCandidateFilter_branch = tree->GetBranch("Flag_badChargedCandidateFilter");
  if (Flag_badChargedCandidateFilter_branch) Flag_badChargedCandidateFilter_branch->SetAddress(&Flag_badChargedCandidateFilter_);
  Flag_badMuonFilter_branch = tree->GetBranch("Flag_badMuonFilter");
  if (Flag_badMuonFilter_branch) Flag_badMuonFilter_branch->SetAddress(&Flag_badMuonFilter_);
  Flag_eeBadScFilter_branch = tree->GetBranch("Flag_eeBadScFilter");
  if (Flag_eeBadScFilter_branch) Flag_eeBadScFilter_branch->SetAddress(&Flag_eeBadScFilter_);
  Flag_globalTightHalo2016_branch = tree->GetBranch("Flag_globalTightHalo2016");
  if (Flag_globalTightHalo2016_branch) Flag_globalTightHalo2016_branch->SetAddress(&Flag_globalTightHalo2016_);
  Flag_goodVertices_branch = tree->GetBranch("Flag_goodVertices");
  if (Flag_goodVertices_branch) Flag_goodVertices_branch->SetAddress(&Flag_goodVertices_);
  nVlep_branch = tree->GetBranch("nVlep");
  if (nVlep_branch) nVlep_branch->SetAddress(&nVlep_);
  nTlep_branch = tree->GetBranch("nTlep");
  if (nTlep_branch) nTlep_branch->SetAddress(&nTlep_);
  nTlepSS_branch = tree->GetBranch("nTlepSS");
  if (nTlepSS_branch) nTlepSS_branch->SetAddress(&nTlepSS_);
  nLlep_branch = tree->GetBranch("nLlep");
  if (nLlep_branch) nLlep_branch->SetAddress(&nLlep_);
  nSFOS_branch = tree->GetBranch("nSFOS");
  if (nSFOS_branch) nSFOS_branch->SetAddress(&nSFOS_);
  nSFOSinZ_branch = tree->GetBranch("nSFOSinZ");
  if (nSFOSinZ_branch) nSFOSinZ_branch->SetAddress(&nSFOSinZ_);
  nj_branch = tree->GetBranch("nj");
  if (nj_branch) nj_branch->SetAddress(&nj_);
  nj_up_branch = tree->GetBranch("nj_up");
  if (nj_up_branch) nj_up_branch->SetAddress(&nj_up_);
  nj_dn_branch = tree->GetBranch("nj_dn");
  if (nj_dn_branch) nj_dn_branch->SetAddress(&nj_dn_);
  nj30_branch = tree->GetBranch("nj30");
  if (nj30_branch) nj30_branch->SetAddress(&nj30_);
  nj30_up_branch = tree->GetBranch("nj30_up");
  if (nj30_up_branch) nj30_up_branch->SetAddress(&nj30_up_);
  nj30_dn_branch = tree->GetBranch("nj30_dn");
  if (nj30_dn_branch) nj30_dn_branch->SetAddress(&nj30_dn_);
  nb_branch = tree->GetBranch("nb");
  if (nb_branch) nb_branch->SetAddress(&nb_);
  nb_up_branch = tree->GetBranch("nb_up");
  if (nb_up_branch) nb_up_branch->SetAddress(&nb_up_);
  nb_dn_branch = tree->GetBranch("nb_dn");
  if (nb_dn_branch) nb_dn_branch->SetAddress(&nb_dn_);
  Mjj_branch = tree->GetBranch("Mjj");
  if (Mjj_branch) Mjj_branch->SetAddress(&Mjj_);
  Mjj_up_branch = tree->GetBranch("Mjj_up");
  if (Mjj_up_branch) Mjj_up_branch->SetAddress(&Mjj_up_);
  Mjj_dn_branch = tree->GetBranch("Mjj_dn");
  if (Mjj_dn_branch) Mjj_dn_branch->SetAddress(&Mjj_dn_);
  MjjVBF_branch = tree->GetBranch("MjjVBF");
  if (MjjVBF_branch) MjjVBF_branch->SetAddress(&MjjVBF_);
  MjjVBF_up_branch = tree->GetBranch("MjjVBF_up");
  if (MjjVBF_up_branch) MjjVBF_up_branch->SetAddress(&MjjVBF_up_);
  MjjVBF_dn_branch = tree->GetBranch("MjjVBF_dn");
  if (MjjVBF_dn_branch) MjjVBF_dn_branch->SetAddress(&MjjVBF_dn_);
  DetajjVBF_branch = tree->GetBranch("DetajjVBF");
  if (DetajjVBF_branch) DetajjVBF_branch->SetAddress(&DetajjVBF_);
  DetajjVBF_up_branch = tree->GetBranch("DetajjVBF_up");
  if (DetajjVBF_up_branch) DetajjVBF_up_branch->SetAddress(&DetajjVBF_up_);
  DetajjVBF_dn_branch = tree->GetBranch("DetajjVBF_dn");
  if (DetajjVBF_dn_branch) DetajjVBF_dn_branch->SetAddress(&DetajjVBF_dn_);
  MjjL_branch = tree->GetBranch("MjjL");
  if (MjjL_branch) MjjL_branch->SetAddress(&MjjL_);
  MjjL_up_branch = tree->GetBranch("MjjL_up");
  if (MjjL_up_branch) MjjL_up_branch->SetAddress(&MjjL_up_);
  MjjL_dn_branch = tree->GetBranch("MjjL_dn");
  if (MjjL_dn_branch) MjjL_dn_branch->SetAddress(&MjjL_dn_);
  DetajjL_branch = tree->GetBranch("DetajjL");
  if (DetajjL_branch) DetajjL_branch->SetAddress(&DetajjL_);
  DetajjL_up_branch = tree->GetBranch("DetajjL_up");
  if (DetajjL_up_branch) DetajjL_up_branch->SetAddress(&DetajjL_up_);
  DetajjL_dn_branch = tree->GetBranch("DetajjL_dn");
  if (DetajjL_dn_branch) DetajjL_dn_branch->SetAddress(&DetajjL_dn_);
  MllSS_branch = tree->GetBranch("MllSS");
  if (MllSS_branch) MllSS_branch->SetAddress(&MllSS_);
  MeeSS_branch = tree->GetBranch("MeeSS");
  if (MeeSS_branch) MeeSS_branch->SetAddress(&MeeSS_);
  Mll3L_branch = tree->GetBranch("Mll3L");
  if (Mll3L_branch) Mll3L_branch->SetAddress(&Mll3L_);
  Mee3L_branch = tree->GetBranch("Mee3L");
  if (Mee3L_branch) Mee3L_branch->SetAddress(&Mee3L_);
  Mll3L1_branch = tree->GetBranch("Mll3L1");
  if (Mll3L1_branch) Mll3L1_branch->SetAddress(&Mll3L1_);
  M3l_branch = tree->GetBranch("M3l");
  if (M3l_branch) M3l_branch->SetAddress(&M3l_);
  Pt3l_branch = tree->GetBranch("Pt3l");
  if (Pt3l_branch) Pt3l_branch->SetAddress(&Pt3l_);
  M01_branch = tree->GetBranch("M01");
  if (M01_branch) M01_branch->SetAddress(&M01_);
  M02_branch = tree->GetBranch("M02");
  if (M02_branch) M02_branch->SetAddress(&M02_);
  M12_branch = tree->GetBranch("M12");
  if (M12_branch) M12_branch->SetAddress(&M12_);
  isSFOS01_branch = tree->GetBranch("isSFOS01");
  if (isSFOS01_branch) isSFOS01_branch->SetAddress(&isSFOS01_);
  isSFOS02_branch = tree->GetBranch("isSFOS02");
  if (isSFOS02_branch) isSFOS02_branch->SetAddress(&isSFOS02_);
  isSFOS12_branch = tree->GetBranch("isSFOS12");
  if (isSFOS12_branch) isSFOS12_branch->SetAddress(&isSFOS12_);
  DPhi3lMET_branch = tree->GetBranch("DPhi3lMET");
  if (DPhi3lMET_branch) DPhi3lMET_branch->SetAddress(&DPhi3lMET_);
  DPhi3lMET_up_branch = tree->GetBranch("DPhi3lMET_up");
  if (DPhi3lMET_up_branch) DPhi3lMET_up_branch->SetAddress(&DPhi3lMET_up_);
  DPhi3lMET_dn_branch = tree->GetBranch("DPhi3lMET_dn");
  if (DPhi3lMET_dn_branch) DPhi3lMET_dn_branch->SetAddress(&DPhi3lMET_dn_);
  MTmax_branch = tree->GetBranch("MTmax");
  if (MTmax_branch) MTmax_branch->SetAddress(&MTmax_);
  MTmax_up_branch = tree->GetBranch("MTmax_up");
  if (MTmax_up_branch) MTmax_up_branch->SetAddress(&MTmax_up_);
  MTmax_dn_branch = tree->GetBranch("MTmax_dn");
  if (MTmax_dn_branch) MTmax_dn_branch->SetAddress(&MTmax_dn_);
  MTmin_branch = tree->GetBranch("MTmin");
  if (MTmin_branch) MTmin_branch->SetAddress(&MTmin_);
  MTmin_up_branch = tree->GetBranch("MTmin_up");
  if (MTmin_up_branch) MTmin_up_branch->SetAddress(&MTmin_up_);
  MTmin_dn_branch = tree->GetBranch("MTmin_dn");
  if (MTmin_dn_branch) MTmin_dn_branch->SetAddress(&MTmin_dn_);
  MT3rd_branch = tree->GetBranch("MT3rd");
  if (MT3rd_branch) MT3rd_branch->SetAddress(&MT3rd_);
  MT3rd_up_branch = tree->GetBranch("MT3rd_up");
  if (MT3rd_up_branch) MT3rd_up_branch->SetAddress(&MT3rd_up_);
  MT3rd_dn_branch = tree->GetBranch("MT3rd_dn");
  if (MT3rd_dn_branch) MT3rd_dn_branch->SetAddress(&MT3rd_dn_);
  passSSee_branch = tree->GetBranch("passSSee");
  if (passSSee_branch) passSSee_branch->SetAddress(&passSSee_);
  passSSem_branch = tree->GetBranch("passSSem");
  if (passSSem_branch) passSSem_branch->SetAddress(&passSSem_);
  passSSmm_branch = tree->GetBranch("passSSmm");
  if (passSSmm_branch) passSSmm_branch->SetAddress(&passSSmm_);
  lep_idx0_SS_branch = tree->GetBranch("lep_idx0_SS");
  if (lep_idx0_SS_branch) lep_idx0_SS_branch->SetAddress(&lep_idx0_SS_);
  lep_idx1_SS_branch = tree->GetBranch("lep_idx1_SS");
  if (lep_idx1_SS_branch) lep_idx1_SS_branch->SetAddress(&lep_idx1_SS_);
  bkgtype_branch = tree->GetBranch("bkgtype");
  if (bkgtype_branch) bkgtype_branch->SetAddress(&bkgtype_);
  vetophoton_branch = tree->GetBranch("vetophoton");
  if (vetophoton_branch) vetophoton_branch->SetAddress(&vetophoton_);
  purewgt_branch = tree->GetBranch("purewgt");
  if (purewgt_branch) purewgt_branch->SetAddress(&purewgt_);
  purewgt_up_branch = tree->GetBranch("purewgt_up");
  if (purewgt_up_branch) purewgt_up_branch->SetAddress(&purewgt_up_);
  purewgt_dn_branch = tree->GetBranch("purewgt_dn");
  if (purewgt_dn_branch) purewgt_dn_branch->SetAddress(&purewgt_dn_);
  ffwgt_branch = tree->GetBranch("ffwgt");
  if (ffwgt_branch) ffwgt_branch->SetAddress(&ffwgt_);
  ffwgt_up_branch = tree->GetBranch("ffwgt_up");
  if (ffwgt_up_branch) ffwgt_up_branch->SetAddress(&ffwgt_up_);
  ffwgt_dn_branch = tree->GetBranch("ffwgt_dn");
  if (ffwgt_dn_branch) ffwgt_dn_branch->SetAddress(&ffwgt_dn_);
  ffwgtqcd_branch = tree->GetBranch("ffwgtqcd");
  if (ffwgtqcd_branch) ffwgtqcd_branch->SetAddress(&ffwgtqcd_);
  ffwgtqcd_up_branch = tree->GetBranch("ffwgtqcd_up");
  if (ffwgtqcd_up_branch) ffwgtqcd_up_branch->SetAddress(&ffwgtqcd_up_);
  ffwgtqcd_dn_branch = tree->GetBranch("ffwgtqcd_dn");
  if (ffwgtqcd_dn_branch) ffwgtqcd_dn_branch->SetAddress(&ffwgtqcd_dn_);
  lepsf_branch = tree->GetBranch("lepsf");
  if (lepsf_branch) lepsf_branch->SetAddress(&lepsf_);
  lepsf_up_branch = tree->GetBranch("lepsf_up");
  if (lepsf_up_branch) lepsf_up_branch->SetAddress(&lepsf_up_);
  lepsf_dn_branch = tree->GetBranch("lepsf_dn");
  if (lepsf_dn_branch) lepsf_dn_branch->SetAddress(&lepsf_dn_);
  trigeff_branch = tree->GetBranch("trigeff");
  if (trigeff_branch) trigeff_branch->SetAddress(&trigeff_);
  trigeff_up_branch = tree->GetBranch("trigeff_up");
  if (trigeff_up_branch) trigeff_up_branch->SetAddress(&trigeff_up_);
  trigeff_dn_branch = tree->GetBranch("trigeff_dn");
  if (trigeff_dn_branch) trigeff_dn_branch->SetAddress(&trigeff_dn_);

  tree->SetMakeClass(0);
}

void CMS3::GetEntry(unsigned int idx) {
  // this only marks branches as not loaded, saving a lot of time
  index = idx;
  run_isLoaded = false;
  lumi_isLoaded = false;
  evt_isLoaded = false;
  isData_isLoaded = false;
  evt_scale1fb_isLoaded = false;
  evt_passgoodrunlist_isLoaded = false;
  HLT_DoubleMu_isLoaded = false;
  HLT_DoubleEl_isLoaded = false;
  HLT_DoubleEl_DZ_isLoaded = false;
  HLT_DoubleEl_DZ_2_isLoaded = false;
  HLT_MuEG_isLoaded = false;
  mc_HLT_DoubleMu_isLoaded = false;
  mc_HLT_DoubleEl_isLoaded = false;
  mc_HLT_DoubleEl_DZ_isLoaded = false;
  mc_HLT_DoubleEl_DZ_2_isLoaded = false;
  mc_HLT_MuEG_isLoaded = false;
  lep_p4_isLoaded = false;
  lep_pt_isLoaded = false;
  lep_eta_isLoaded = false;
  lep_phi_isLoaded = false;
  lep_coneCorrPt_isLoaded = false;
  lep_ip3d_isLoaded = false;
  lep_ip3derr_isLoaded = false;
  lep_isTriggerSafe_v1_isLoaded = false;
  lep_lostHits_isLoaded = false;
  lep_convVeto_isLoaded = false;
  lep_motherIdSS_isLoaded = false;
  lep_pass_VVV_cutbased_3l_fo_isLoaded = false;
  lep_pass_VVV_cutbased_3l_tight_isLoaded = false;
  lep_pass_VVV_cutbased_fo_isLoaded = false;
  lep_pass_VVV_cutbased_tight_isLoaded = false;
  lep_pass_VVV_cutbased_veto_isLoaded = false;
  lep_pass_VVV_cutbased_fo_noiso_isLoaded = false;
  lep_pass_VVV_cutbased_tight_noiso_isLoaded = false;
  lep_pass_VVV_cutbased_veto_noiso_isLoaded = false;
  lep_pdgId_isLoaded = false;
  lep_dxy_isLoaded = false;
  lep_dz_isLoaded = false;
  lep_ptRatio_isLoaded = false;
  lep_ptRel_isLoaded = false;
  lep_pterr_isLoaded = false;
  lep_relIso03EAv2_isLoaded = false;
  lep_relIso04EAv2_isLoaded = false;
  lep_tightCharge_isLoaded = false;
  lep_trk_pt_isLoaded = false;
  lep_charge_isLoaded = false;
  lep_etaSC_isLoaded = false;
  lep_MVA_isLoaded = false;
  lep_isFromW_isLoaded = false;
  lep_isFromZ_isLoaded = false;
  lep_isFromB_isLoaded = false;
  lep_isFromC_isLoaded = false;
  lep_isFromL_isLoaded = false;
  lep_isFromLF_isLoaded = false;
  lep_genPart_index_isLoaded = false;
  jets_p4_isLoaded = false;
  jets_up_p4_isLoaded = false;
  jets_dn_p4_isLoaded = false;
  jets_csv_isLoaded = false;
  jets_up_csv_isLoaded = false;
  jets_dn_csv_isLoaded = false;
  met_pt_isLoaded = false;
  met_phi_isLoaded = false;
  met_up_pt_isLoaded = false;
  met_up_phi_isLoaded = false;
  met_dn_pt_isLoaded = false;
  met_dn_phi_isLoaded = false;
  firstgoodvertex_isLoaded = false;
  nTrueInt_isLoaded = false;
  nVert_isLoaded = false;
  nisoTrack_mt2_cleaned_VVV_cutbased_veto_isLoaded = false;
  weight_btagsf_isLoaded = false;
  weight_btagsf_heavy_DN_isLoaded = false;
  weight_btagsf_heavy_UP_isLoaded = false;
  weight_btagsf_light_DN_isLoaded = false;
  weight_btagsf_light_UP_isLoaded = false;
  gen_ht_isLoaded = false;
  genPart_p4_isLoaded = false;
  genPart_motherId_isLoaded = false;
  genPart_pdgId_isLoaded = false;
  genPart_charge_isLoaded = false;
  genPart_status_isLoaded = false;
  ngenLep_isLoaded = false;
  ngenLepFromTau_isLoaded = false;
  Flag_AllEventFilters_isLoaded = false;
  Flag_EcalDeadCellTriggerPrimitiveFilter_isLoaded = false;
  Flag_HBHEIsoNoiseFilter_isLoaded = false;
  Flag_HBHENoiseFilter_isLoaded = false;
  Flag_badChargedCandidateFilter_isLoaded = false;
  Flag_badMuonFilter_isLoaded = false;
  Flag_eeBadScFilter_isLoaded = false;
  Flag_globalTightHalo2016_isLoaded = false;
  Flag_goodVertices_isLoaded = false;
  nVlep_isLoaded = false;
  nTlep_isLoaded = false;
  nTlepSS_isLoaded = false;
  nLlep_isLoaded = false;
  nSFOS_isLoaded = false;
  nSFOSinZ_isLoaded = false;
  nj_isLoaded = false;
  nj_up_isLoaded = false;
  nj_dn_isLoaded = false;
  nj30_isLoaded = false;
  nj30_up_isLoaded = false;
  nj30_dn_isLoaded = false;
  nb_isLoaded = false;
  nb_up_isLoaded = false;
  nb_dn_isLoaded = false;
  Mjj_isLoaded = false;
  Mjj_up_isLoaded = false;
  Mjj_dn_isLoaded = false;
  MjjVBF_isLoaded = false;
  MjjVBF_up_isLoaded = false;
  MjjVBF_dn_isLoaded = false;
  DetajjVBF_isLoaded = false;
  DetajjVBF_up_isLoaded = false;
  DetajjVBF_dn_isLoaded = false;
  MjjL_isLoaded = false;
  MjjL_up_isLoaded = false;
  MjjL_dn_isLoaded = false;
  DetajjL_isLoaded = false;
  DetajjL_up_isLoaded = false;
  DetajjL_dn_isLoaded = false;
  MllSS_isLoaded = false;
  MeeSS_isLoaded = false;
  Mll3L_isLoaded = false;
  Mee3L_isLoaded = false;
  Mll3L1_isLoaded = false;
  M3l_isLoaded = false;
  Pt3l_isLoaded = false;
  M01_isLoaded = false;
  M02_isLoaded = false;
  M12_isLoaded = false;
  isSFOS01_isLoaded = false;
  isSFOS02_isLoaded = false;
  isSFOS12_isLoaded = false;
  DPhi3lMET_isLoaded = false;
  DPhi3lMET_up_isLoaded = false;
  DPhi3lMET_dn_isLoaded = false;
  MTmax_isLoaded = false;
  MTmax_up_isLoaded = false;
  MTmax_dn_isLoaded = false;
  MTmin_isLoaded = false;
  MTmin_up_isLoaded = false;
  MTmin_dn_isLoaded = false;
  MT3rd_isLoaded = false;
  MT3rd_up_isLoaded = false;
  MT3rd_dn_isLoaded = false;
  passSSee_isLoaded = false;
  passSSem_isLoaded = false;
  passSSmm_isLoaded = false;
  lep_idx0_SS_isLoaded = false;
  lep_idx1_SS_isLoaded = false;
  bkgtype_isLoaded = false;
  vetophoton_isLoaded = false;
  purewgt_isLoaded = false;
  purewgt_up_isLoaded = false;
  purewgt_dn_isLoaded = false;
  ffwgt_isLoaded = false;
  ffwgt_up_isLoaded = false;
  ffwgt_dn_isLoaded = false;
  ffwgtqcd_isLoaded = false;
  ffwgtqcd_up_isLoaded = false;
  ffwgtqcd_dn_isLoaded = false;
  lepsf_isLoaded = false;
  lepsf_up_isLoaded = false;
  lepsf_dn_isLoaded = false;
  trigeff_isLoaded = false;
  trigeff_up_isLoaded = false;
  trigeff_dn_isLoaded = false;
}

void CMS3::LoadAllBranches() {
  // load all branches
  if (run_branch != 0) run();
  if (lumi_branch != 0) lumi();
  if (evt_branch != 0) evt();
  if (isData_branch != 0) isData();
  if (evt_scale1fb_branch != 0) evt_scale1fb();
  if (evt_passgoodrunlist_branch != 0) evt_passgoodrunlist();
  if (HLT_DoubleMu_branch != 0) HLT_DoubleMu();
  if (HLT_DoubleEl_branch != 0) HLT_DoubleEl();
  if (HLT_DoubleEl_DZ_branch != 0) HLT_DoubleEl_DZ();
  if (HLT_DoubleEl_DZ_2_branch != 0) HLT_DoubleEl_DZ_2();
  if (HLT_MuEG_branch != 0) HLT_MuEG();
  if (mc_HLT_DoubleMu_branch != 0) mc_HLT_DoubleMu();
  if (mc_HLT_DoubleEl_branch != 0) mc_HLT_DoubleEl();
  if (mc_HLT_DoubleEl_DZ_branch != 0) mc_HLT_DoubleEl_DZ();
  if (mc_HLT_DoubleEl_DZ_2_branch != 0) mc_HLT_DoubleEl_DZ_2();
  if (mc_HLT_MuEG_branch != 0) mc_HLT_MuEG();
  if (lep_p4_branch != 0) lep_p4();
  if (lep_pt_branch != 0) lep_pt();
  if (lep_eta_branch != 0) lep_eta();
  if (lep_phi_branch != 0) lep_phi();
  if (lep_coneCorrPt_branch != 0) lep_coneCorrPt();
  if (lep_ip3d_branch != 0) lep_ip3d();
  if (lep_ip3derr_branch != 0) lep_ip3derr();
  if (lep_isTriggerSafe_v1_branch != 0) lep_isTriggerSafe_v1();
  if (lep_lostHits_branch != 0) lep_lostHits();
  if (lep_convVeto_branch != 0) lep_convVeto();
  if (lep_motherIdSS_branch != 0) lep_motherIdSS();
  if (lep_pass_VVV_cutbased_3l_fo_branch != 0) lep_pass_VVV_cutbased_3l_fo();
  if (lep_pass_VVV_cutbased_3l_tight_branch != 0) lep_pass_VVV_cutbased_3l_tight();
  if (lep_pass_VVV_cutbased_fo_branch != 0) lep_pass_VVV_cutbased_fo();
  if (lep_pass_VVV_cutbased_tight_branch != 0) lep_pass_VVV_cutbased_tight();
  if (lep_pass_VVV_cutbased_veto_branch != 0) lep_pass_VVV_cutbased_veto();
  if (lep_pass_VVV_cutbased_fo_noiso_branch != 0) lep_pass_VVV_cutbased_fo_noiso();
  if (lep_pass_VVV_cutbased_tight_noiso_branch != 0) lep_pass_VVV_cutbased_tight_noiso();
  if (lep_pass_VVV_cutbased_veto_noiso_branch != 0) lep_pass_VVV_cutbased_veto_noiso();
  if (lep_pdgId_branch != 0) lep_pdgId();
  if (lep_dxy_branch != 0) lep_dxy();
  if (lep_dz_branch != 0) lep_dz();
  if (lep_ptRatio_branch != 0) lep_ptRatio();
  if (lep_ptRel_branch != 0) lep_ptRel();
  if (lep_pterr_branch != 0) lep_pterr();
  if (lep_relIso03EAv2_branch != 0) lep_relIso03EAv2();
  if (lep_relIso04EAv2_branch != 0) lep_relIso04EAv2();
  if (lep_tightCharge_branch != 0) lep_tightCharge();
  if (lep_trk_pt_branch != 0) lep_trk_pt();
  if (lep_charge_branch != 0) lep_charge();
  if (lep_etaSC_branch != 0) lep_etaSC();
  if (lep_MVA_branch != 0) lep_MVA();
  if (lep_isFromW_branch != 0) lep_isFromW();
  if (lep_isFromZ_branch != 0) lep_isFromZ();
  if (lep_isFromB_branch != 0) lep_isFromB();
  if (lep_isFromC_branch != 0) lep_isFromC();
  if (lep_isFromL_branch != 0) lep_isFromL();
  if (lep_isFromLF_branch != 0) lep_isFromLF();
  if (lep_genPart_index_branch != 0) lep_genPart_index();
  if (jets_p4_branch != 0) jets_p4();
  if (jets_up_p4_branch != 0) jets_up_p4();
  if (jets_dn_p4_branch != 0) jets_dn_p4();
  if (jets_csv_branch != 0) jets_csv();
  if (jets_up_csv_branch != 0) jets_up_csv();
  if (jets_dn_csv_branch != 0) jets_dn_csv();
  if (met_pt_branch != 0) met_pt();
  if (met_phi_branch != 0) met_phi();
  if (met_up_pt_branch != 0) met_up_pt();
  if (met_up_phi_branch != 0) met_up_phi();
  if (met_dn_pt_branch != 0) met_dn_pt();
  if (met_dn_phi_branch != 0) met_dn_phi();
  if (firstgoodvertex_branch != 0) firstgoodvertex();
  if (nTrueInt_branch != 0) nTrueInt();
  if (nVert_branch != 0) nVert();
  if (nisoTrack_mt2_cleaned_VVV_cutbased_veto_branch != 0) nisoTrack_mt2_cleaned_VVV_cutbased_veto();
  if (weight_btagsf_branch != 0) weight_btagsf();
  if (weight_btagsf_heavy_DN_branch != 0) weight_btagsf_heavy_DN();
  if (weight_btagsf_heavy_UP_branch != 0) weight_btagsf_heavy_UP();
  if (weight_btagsf_light_DN_branch != 0) weight_btagsf_light_DN();
  if (weight_btagsf_light_UP_branch != 0) weight_btagsf_light_UP();
  if (gen_ht_branch != 0) gen_ht();
  if (genPart_p4_branch != 0) genPart_p4();
  if (genPart_motherId_branch != 0) genPart_motherId();
  if (genPart_pdgId_branch != 0) genPart_pdgId();
  if (genPart_charge_branch != 0) genPart_charge();
  if (genPart_status_branch != 0) genPart_status();
  if (ngenLep_branch != 0) ngenLep();
  if (ngenLepFromTau_branch != 0) ngenLepFromTau();
  if (Flag_AllEventFilters_branch != 0) Flag_AllEventFilters();
  if (Flag_EcalDeadCellTriggerPrimitiveFilter_branch != 0) Flag_EcalDeadCellTriggerPrimitiveFilter();
  if (Flag_HBHEIsoNoiseFilter_branch != 0) Flag_HBHEIsoNoiseFilter();
  if (Flag_HBHENoiseFilter_branch != 0) Flag_HBHENoiseFilter();
  if (Flag_badChargedCandidateFilter_branch != 0) Flag_badChargedCandidateFilter();
  if (Flag_badMuonFilter_branch != 0) Flag_badMuonFilter();
  if (Flag_eeBadScFilter_branch != 0) Flag_eeBadScFilter();
  if (Flag_globalTightHalo2016_branch != 0) Flag_globalTightHalo2016();
  if (Flag_goodVertices_branch != 0) Flag_goodVertices();
  if (nVlep_branch != 0) nVlep();
  if (nTlep_branch != 0) nTlep();
  if (nTlepSS_branch != 0) nTlepSS();
  if (nLlep_branch != 0) nLlep();
  if (nSFOS_branch != 0) nSFOS();
  if (nSFOSinZ_branch != 0) nSFOSinZ();
  if (nj_branch != 0) nj();
  if (nj_up_branch != 0) nj_up();
  if (nj_dn_branch != 0) nj_dn();
  if (nj30_branch != 0) nj30();
  if (nj30_up_branch != 0) nj30_up();
  if (nj30_dn_branch != 0) nj30_dn();
  if (nb_branch != 0) nb();
  if (nb_up_branch != 0) nb_up();
  if (nb_dn_branch != 0) nb_dn();
  if (Mjj_branch != 0) Mjj();
  if (Mjj_up_branch != 0) Mjj_up();
  if (Mjj_dn_branch != 0) Mjj_dn();
  if (MjjVBF_branch != 0) MjjVBF();
  if (MjjVBF_up_branch != 0) MjjVBF_up();
  if (MjjVBF_dn_branch != 0) MjjVBF_dn();
  if (DetajjVBF_branch != 0) DetajjVBF();
  if (DetajjVBF_up_branch != 0) DetajjVBF_up();
  if (DetajjVBF_dn_branch != 0) DetajjVBF_dn();
  if (MjjL_branch != 0) MjjL();
  if (MjjL_up_branch != 0) MjjL_up();
  if (MjjL_dn_branch != 0) MjjL_dn();
  if (DetajjL_branch != 0) DetajjL();
  if (DetajjL_up_branch != 0) DetajjL_up();
  if (DetajjL_dn_branch != 0) DetajjL_dn();
  if (MllSS_branch != 0) MllSS();
  if (MeeSS_branch != 0) MeeSS();
  if (Mll3L_branch != 0) Mll3L();
  if (Mee3L_branch != 0) Mee3L();
  if (Mll3L1_branch != 0) Mll3L1();
  if (M3l_branch != 0) M3l();
  if (Pt3l_branch != 0) Pt3l();
  if (M01_branch != 0) M01();
  if (M02_branch != 0) M02();
  if (M12_branch != 0) M12();
  if (isSFOS01_branch != 0) isSFOS01();
  if (isSFOS02_branch != 0) isSFOS02();
  if (isSFOS12_branch != 0) isSFOS12();
  if (DPhi3lMET_branch != 0) DPhi3lMET();
  if (DPhi3lMET_up_branch != 0) DPhi3lMET_up();
  if (DPhi3lMET_dn_branch != 0) DPhi3lMET_dn();
  if (MTmax_branch != 0) MTmax();
  if (MTmax_up_branch != 0) MTmax_up();
  if (MTmax_dn_branch != 0) MTmax_dn();
  if (MTmin_branch != 0) MTmin();
  if (MTmin_up_branch != 0) MTmin_up();
  if (MTmin_dn_branch != 0) MTmin_dn();
  if (MT3rd_branch != 0) MT3rd();
  if (MT3rd_up_branch != 0) MT3rd_up();
  if (MT3rd_dn_branch != 0) MT3rd_dn();
  if (passSSee_branch != 0) passSSee();
  if (passSSem_branch != 0) passSSem();
  if (passSSmm_branch != 0) passSSmm();
  if (lep_idx0_SS_branch != 0) lep_idx0_SS();
  if (lep_idx1_SS_branch != 0) lep_idx1_SS();
  if (bkgtype_branch != 0) bkgtype();
  if (vetophoton_branch != 0) vetophoton();
  if (purewgt_branch != 0) purewgt();
  if (purewgt_up_branch != 0) purewgt_up();
  if (purewgt_dn_branch != 0) purewgt_dn();
  if (ffwgt_branch != 0) ffwgt();
  if (ffwgt_up_branch != 0) ffwgt_up();
  if (ffwgt_dn_branch != 0) ffwgt_dn();
  if (ffwgtqcd_branch != 0) ffwgtqcd();
  if (ffwgtqcd_up_branch != 0) ffwgtqcd_up();
  if (ffwgtqcd_dn_branch != 0) ffwgtqcd_dn();
  if (lepsf_branch != 0) lepsf();
  if (lepsf_up_branch != 0) lepsf_up();
  if (lepsf_dn_branch != 0) lepsf_dn();
  if (trigeff_branch != 0) trigeff();
  if (trigeff_up_branch != 0) trigeff_up();
  if (trigeff_dn_branch != 0) trigeff_dn();
}

const int &CMS3::run() {
  if (not run_isLoaded) {
    if (run_branch != 0) {
      run_branch->GetEntry(index);
    } else {
      printf("branch run_branch does not exist!\n");
      exit(1);
    }
    run_isLoaded = true;
  }
  return run_;
}

const int &CMS3::lumi() {
  if (not lumi_isLoaded) {
    if (lumi_branch != 0) {
      lumi_branch->GetEntry(index);
    } else {
      printf("branch lumi_branch does not exist!\n");
      exit(1);
    }
    lumi_isLoaded = true;
  }
  return lumi_;
}

const unsigned long long &CMS3::evt() {
  if (not evt_isLoaded) {
    if (evt_branch != 0) {
      evt_branch->GetEntry(index);
    } else {
      printf("branch evt_branch does not exist!\n");
      exit(1);
    }
    evt_isLoaded = true;
  }
  return evt_;
}

const int &CMS3::isData() {
  if (not isData_isLoaded) {
    if (isData_branch != 0) {
      isData_branch->GetEntry(index);
    } else {
      printf("branch isData_branch does not exist!\n");
      exit(1);
    }
    isData_isLoaded = true;
  }
  return isData_;
}

const float &CMS3::evt_scale1fb() {
  if (not evt_scale1fb_isLoaded) {
    if (evt_scale1fb_branch != 0) {
      evt_scale1fb_branch->GetEntry(index);
    } else {
      printf("branch evt_scale1fb_branch does not exist!\n");
      exit(1);
    }
    evt_scale1fb_isLoaded = true;
  }
  return evt_scale1fb_;
}

const int &CMS3::evt_passgoodrunlist() {
  if (not evt_passgoodrunlist_isLoaded) {
    if (evt_passgoodrunlist_branch != 0) {
      evt_passgoodrunlist_branch->GetEntry(index);
    } else {
      printf("branch evt_passgoodrunlist_branch does not exist!\n");
      exit(1);
    }
    evt_passgoodrunlist_isLoaded = true;
  }
  return evt_passgoodrunlist_;
}

const int &CMS3::HLT_DoubleMu() {
  if (not HLT_DoubleMu_isLoaded) {
    if (HLT_DoubleMu_branch != 0) {
      HLT_DoubleMu_branch->GetEntry(index);
    } else {
      printf("branch HLT_DoubleMu_branch does not exist!\n");
      exit(1);
    }
    HLT_DoubleMu_isLoaded = true;
  }
  return HLT_DoubleMu_;
}

const int &CMS3::HLT_DoubleEl() {
  if (not HLT_DoubleEl_isLoaded) {
    if (HLT_DoubleEl_branch != 0) {
      HLT_DoubleEl_branch->GetEntry(index);
    } else {
      printf("branch HLT_DoubleEl_branch does not exist!\n");
      exit(1);
    }
    HLT_DoubleEl_isLoaded = true;
  }
  return HLT_DoubleEl_;
}

const int &CMS3::HLT_DoubleEl_DZ() {
  if (not HLT_DoubleEl_DZ_isLoaded) {
    if (HLT_DoubleEl_DZ_branch != 0) {
      HLT_DoubleEl_DZ_branch->GetEntry(index);
    } else {
      printf("branch HLT_DoubleEl_DZ_branch does not exist!\n");
      exit(1);
    }
    HLT_DoubleEl_DZ_isLoaded = true;
  }
  return HLT_DoubleEl_DZ_;
}

const int &CMS3::HLT_DoubleEl_DZ_2() {
  if (not HLT_DoubleEl_DZ_2_isLoaded) {
    if (HLT_DoubleEl_DZ_2_branch != 0) {
      HLT_DoubleEl_DZ_2_branch->GetEntry(index);
    } else {
      printf("branch HLT_DoubleEl_DZ_2_branch does not exist!\n");
      exit(1);
    }
    HLT_DoubleEl_DZ_2_isLoaded = true;
  }
  return HLT_DoubleEl_DZ_2_;
}

const int &CMS3::HLT_MuEG() {
  if (not HLT_MuEG_isLoaded) {
    if (HLT_MuEG_branch != 0) {
      HLT_MuEG_branch->GetEntry(index);
    } else {
      printf("branch HLT_MuEG_branch does not exist!\n");
      exit(1);
    }
    HLT_MuEG_isLoaded = true;
  }
  return HLT_MuEG_;
}

const int &CMS3::mc_HLT_DoubleMu() {
  if (not mc_HLT_DoubleMu_isLoaded) {
    if (mc_HLT_DoubleMu_branch != 0) {
      mc_HLT_DoubleMu_branch->GetEntry(index);
    } else {
      printf("branch mc_HLT_DoubleMu_branch does not exist!\n");
      exit(1);
    }
    mc_HLT_DoubleMu_isLoaded = true;
  }
  return mc_HLT_DoubleMu_;
}

const int &CMS3::mc_HLT_DoubleEl() {
  if (not mc_HLT_DoubleEl_isLoaded) {
    if (mc_HLT_DoubleEl_branch != 0) {
      mc_HLT_DoubleEl_branch->GetEntry(index);
    } else {
      printf("branch mc_HLT_DoubleEl_branch does not exist!\n");
      exit(1);
    }
    mc_HLT_DoubleEl_isLoaded = true;
  }
  return mc_HLT_DoubleEl_;
}

const int &CMS3::mc_HLT_DoubleEl_DZ() {
  if (not mc_HLT_DoubleEl_DZ_isLoaded) {
    if (mc_HLT_DoubleEl_DZ_branch != 0) {
      mc_HLT_DoubleEl_DZ_branch->GetEntry(index);
    } else {
      printf("branch mc_HLT_DoubleEl_DZ_branch does not exist!\n");
      exit(1);
    }
    mc_HLT_DoubleEl_DZ_isLoaded = true;
  }
  return mc_HLT_DoubleEl_DZ_;
}

const int &CMS3::mc_HLT_DoubleEl_DZ_2() {
  if (not mc_HLT_DoubleEl_DZ_2_isLoaded) {
    if (mc_HLT_DoubleEl_DZ_2_branch != 0) {
      mc_HLT_DoubleEl_DZ_2_branch->GetEntry(index);
    } else {
      printf("branch mc_HLT_DoubleEl_DZ_2_branch does not exist!\n");
      exit(1);
    }
    mc_HLT_DoubleEl_DZ_2_isLoaded = true;
  }
  return mc_HLT_DoubleEl_DZ_2_;
}

const int &CMS3::mc_HLT_MuEG() {
  if (not mc_HLT_MuEG_isLoaded) {
    if (mc_HLT_MuEG_branch != 0) {
      mc_HLT_MuEG_branch->GetEntry(index);
    } else {
      printf("branch mc_HLT_MuEG_branch does not exist!\n");
      exit(1);
    }
    mc_HLT_MuEG_isLoaded = true;
  }
  return mc_HLT_MuEG_;
}

const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &CMS3::lep_p4() {
  if (not lep_p4_isLoaded) {
    if (lep_p4_branch != 0) {
      lep_p4_branch->GetEntry(index);
    } else {
      printf("branch lep_p4_branch does not exist!\n");
      exit(1);
    }
    lep_p4_isLoaded = true;
  }
  return *lep_p4_;
}

const vector<float> &CMS3::lep_pt() {
  if (not lep_pt_isLoaded) {
    if (lep_pt_branch != 0) {
      lep_pt_branch->GetEntry(index);
    } else {
      printf("branch lep_pt_branch does not exist!\n");
      exit(1);
    }
    lep_pt_isLoaded = true;
  }
  return *lep_pt_;
}

const vector<float> &CMS3::lep_eta() {
  if (not lep_eta_isLoaded) {
    if (lep_eta_branch != 0) {
      lep_eta_branch->GetEntry(index);
    } else {
      printf("branch lep_eta_branch does not exist!\n");
      exit(1);
    }
    lep_eta_isLoaded = true;
  }
  return *lep_eta_;
}

const vector<float> &CMS3::lep_phi() {
  if (not lep_phi_isLoaded) {
    if (lep_phi_branch != 0) {
      lep_phi_branch->GetEntry(index);
    } else {
      printf("branch lep_phi_branch does not exist!\n");
      exit(1);
    }
    lep_phi_isLoaded = true;
  }
  return *lep_phi_;
}

const vector<float> &CMS3::lep_coneCorrPt() {
  if (not lep_coneCorrPt_isLoaded) {
    if (lep_coneCorrPt_branch != 0) {
      lep_coneCorrPt_branch->GetEntry(index);
    } else {
      printf("branch lep_coneCorrPt_branch does not exist!\n");
      exit(1);
    }
    lep_coneCorrPt_isLoaded = true;
  }
  return *lep_coneCorrPt_;
}

const vector<float> &CMS3::lep_ip3d() {
  if (not lep_ip3d_isLoaded) {
    if (lep_ip3d_branch != 0) {
      lep_ip3d_branch->GetEntry(index);
    } else {
      printf("branch lep_ip3d_branch does not exist!\n");
      exit(1);
    }
    lep_ip3d_isLoaded = true;
  }
  return *lep_ip3d_;
}

const vector<float> &CMS3::lep_ip3derr() {
  if (not lep_ip3derr_isLoaded) {
    if (lep_ip3derr_branch != 0) {
      lep_ip3derr_branch->GetEntry(index);
    } else {
      printf("branch lep_ip3derr_branch does not exist!\n");
      exit(1);
    }
    lep_ip3derr_isLoaded = true;
  }
  return *lep_ip3derr_;
}

const vector<int> &CMS3::lep_isTriggerSafe_v1() {
  if (not lep_isTriggerSafe_v1_isLoaded) {
    if (lep_isTriggerSafe_v1_branch != 0) {
      lep_isTriggerSafe_v1_branch->GetEntry(index);
    } else {
      printf("branch lep_isTriggerSafe_v1_branch does not exist!\n");
      exit(1);
    }
    lep_isTriggerSafe_v1_isLoaded = true;
  }
  return *lep_isTriggerSafe_v1_;
}

const vector<int> &CMS3::lep_lostHits() {
  if (not lep_lostHits_isLoaded) {
    if (lep_lostHits_branch != 0) {
      lep_lostHits_branch->GetEntry(index);
    } else {
      printf("branch lep_lostHits_branch does not exist!\n");
      exit(1);
    }
    lep_lostHits_isLoaded = true;
  }
  return *lep_lostHits_;
}

const vector<int> &CMS3::lep_convVeto() {
  if (not lep_convVeto_isLoaded) {
    if (lep_convVeto_branch != 0) {
      lep_convVeto_branch->GetEntry(index);
    } else {
      printf("branch lep_convVeto_branch does not exist!\n");
      exit(1);
    }
    lep_convVeto_isLoaded = true;
  }
  return *lep_convVeto_;
}

const vector<int> &CMS3::lep_motherIdSS() {
  if (not lep_motherIdSS_isLoaded) {
    if (lep_motherIdSS_branch != 0) {
      lep_motherIdSS_branch->GetEntry(index);
    } else {
      printf("branch lep_motherIdSS_branch does not exist!\n");
      exit(1);
    }
    lep_motherIdSS_isLoaded = true;
  }
  return *lep_motherIdSS_;
}

const vector<int> &CMS3::lep_pass_VVV_cutbased_3l_fo() {
  if (not lep_pass_VVV_cutbased_3l_fo_isLoaded) {
    if (lep_pass_VVV_cutbased_3l_fo_branch != 0) {
      lep_pass_VVV_cutbased_3l_fo_branch->GetEntry(index);
    } else {
      printf("branch lep_pass_VVV_cutbased_3l_fo_branch does not exist!\n");
      exit(1);
    }
    lep_pass_VVV_cutbased_3l_fo_isLoaded = true;
  }
  return *lep_pass_VVV_cutbased_3l_fo_;
}

const vector<int> &CMS3::lep_pass_VVV_cutbased_3l_tight() {
  if (not lep_pass_VVV_cutbased_3l_tight_isLoaded) {
    if (lep_pass_VVV_cutbased_3l_tight_branch != 0) {
      lep_pass_VVV_cutbased_3l_tight_branch->GetEntry(index);
    } else {
      printf("branch lep_pass_VVV_cutbased_3l_tight_branch does not exist!\n");
      exit(1);
    }
    lep_pass_VVV_cutbased_3l_tight_isLoaded = true;
  }
  return *lep_pass_VVV_cutbased_3l_tight_;
}

const vector<int> &CMS3::lep_pass_VVV_cutbased_fo() {
  if (not lep_pass_VVV_cutbased_fo_isLoaded) {
    if (lep_pass_VVV_cutbased_fo_branch != 0) {
      lep_pass_VVV_cutbased_fo_branch->GetEntry(index);
    } else {
      printf("branch lep_pass_VVV_cutbased_fo_branch does not exist!\n");
      exit(1);
    }
    lep_pass_VVV_cutbased_fo_isLoaded = true;
  }
  return *lep_pass_VVV_cutbased_fo_;
}

const vector<int> &CMS3::lep_pass_VVV_cutbased_tight() {
  if (not lep_pass_VVV_cutbased_tight_isLoaded) {
    if (lep_pass_VVV_cutbased_tight_branch != 0) {
      lep_pass_VVV_cutbased_tight_branch->GetEntry(index);
    } else {
      printf("branch lep_pass_VVV_cutbased_tight_branch does not exist!\n");
      exit(1);
    }
    lep_pass_VVV_cutbased_tight_isLoaded = true;
  }
  return *lep_pass_VVV_cutbased_tight_;
}

const vector<int> &CMS3::lep_pass_VVV_cutbased_veto() {
  if (not lep_pass_VVV_cutbased_veto_isLoaded) {
    if (lep_pass_VVV_cutbased_veto_branch != 0) {
      lep_pass_VVV_cutbased_veto_branch->GetEntry(index);
    } else {
      printf("branch lep_pass_VVV_cutbased_veto_branch does not exist!\n");
      exit(1);
    }
    lep_pass_VVV_cutbased_veto_isLoaded = true;
  }
  return *lep_pass_VVV_cutbased_veto_;
}

const vector<int> &CMS3::lep_pass_VVV_cutbased_fo_noiso() {
  if (not lep_pass_VVV_cutbased_fo_noiso_isLoaded) {
    if (lep_pass_VVV_cutbased_fo_noiso_branch != 0) {
      lep_pass_VVV_cutbased_fo_noiso_branch->GetEntry(index);
    } else {
      printf("branch lep_pass_VVV_cutbased_fo_noiso_branch does not exist!\n");
      exit(1);
    }
    lep_pass_VVV_cutbased_fo_noiso_isLoaded = true;
  }
  return *lep_pass_VVV_cutbased_fo_noiso_;
}

const vector<int> &CMS3::lep_pass_VVV_cutbased_tight_noiso() {
  if (not lep_pass_VVV_cutbased_tight_noiso_isLoaded) {
    if (lep_pass_VVV_cutbased_tight_noiso_branch != 0) {
      lep_pass_VVV_cutbased_tight_noiso_branch->GetEntry(index);
    } else {
      printf("branch lep_pass_VVV_cutbased_tight_noiso_branch does not exist!\n");
      exit(1);
    }
    lep_pass_VVV_cutbased_tight_noiso_isLoaded = true;
  }
  return *lep_pass_VVV_cutbased_tight_noiso_;
}

const vector<int> &CMS3::lep_pass_VVV_cutbased_veto_noiso() {
  if (not lep_pass_VVV_cutbased_veto_noiso_isLoaded) {
    if (lep_pass_VVV_cutbased_veto_noiso_branch != 0) {
      lep_pass_VVV_cutbased_veto_noiso_branch->GetEntry(index);
    } else {
      printf("branch lep_pass_VVV_cutbased_veto_noiso_branch does not exist!\n");
      exit(1);
    }
    lep_pass_VVV_cutbased_veto_noiso_isLoaded = true;
  }
  return *lep_pass_VVV_cutbased_veto_noiso_;
}

const vector<int> &CMS3::lep_pdgId() {
  if (not lep_pdgId_isLoaded) {
    if (lep_pdgId_branch != 0) {
      lep_pdgId_branch->GetEntry(index);
    } else {
      printf("branch lep_pdgId_branch does not exist!\n");
      exit(1);
    }
    lep_pdgId_isLoaded = true;
  }
  return *lep_pdgId_;
}

const vector<float> &CMS3::lep_dxy() {
  if (not lep_dxy_isLoaded) {
    if (lep_dxy_branch != 0) {
      lep_dxy_branch->GetEntry(index);
    } else {
      printf("branch lep_dxy_branch does not exist!\n");
      exit(1);
    }
    lep_dxy_isLoaded = true;
  }
  return *lep_dxy_;
}

const vector<float> &CMS3::lep_dz() {
  if (not lep_dz_isLoaded) {
    if (lep_dz_branch != 0) {
      lep_dz_branch->GetEntry(index);
    } else {
      printf("branch lep_dz_branch does not exist!\n");
      exit(1);
    }
    lep_dz_isLoaded = true;
  }
  return *lep_dz_;
}

const vector<float> &CMS3::lep_ptRatio() {
  if (not lep_ptRatio_isLoaded) {
    if (lep_ptRatio_branch != 0) {
      lep_ptRatio_branch->GetEntry(index);
    } else {
      printf("branch lep_ptRatio_branch does not exist!\n");
      exit(1);
    }
    lep_ptRatio_isLoaded = true;
  }
  return *lep_ptRatio_;
}

const vector<float> &CMS3::lep_ptRel() {
  if (not lep_ptRel_isLoaded) {
    if (lep_ptRel_branch != 0) {
      lep_ptRel_branch->GetEntry(index);
    } else {
      printf("branch lep_ptRel_branch does not exist!\n");
      exit(1);
    }
    lep_ptRel_isLoaded = true;
  }
  return *lep_ptRel_;
}

const vector<float> &CMS3::lep_pterr() {
  if (not lep_pterr_isLoaded) {
    if (lep_pterr_branch != 0) {
      lep_pterr_branch->GetEntry(index);
    } else {
      printf("branch lep_pterr_branch does not exist!\n");
      exit(1);
    }
    lep_pterr_isLoaded = true;
  }
  return *lep_pterr_;
}

const vector<float> &CMS3::lep_relIso03EAv2() {
  if (not lep_relIso03EAv2_isLoaded) {
    if (lep_relIso03EAv2_branch != 0) {
      lep_relIso03EAv2_branch->GetEntry(index);
    } else {
      printf("branch lep_relIso03EAv2_branch does not exist!\n");
      exit(1);
    }
    lep_relIso03EAv2_isLoaded = true;
  }
  return *lep_relIso03EAv2_;
}

const vector<float> &CMS3::lep_relIso04EAv2() {
  if (not lep_relIso04EAv2_isLoaded) {
    if (lep_relIso04EAv2_branch != 0) {
      lep_relIso04EAv2_branch->GetEntry(index);
    } else {
      printf("branch lep_relIso04EAv2_branch does not exist!\n");
      exit(1);
    }
    lep_relIso04EAv2_isLoaded = true;
  }
  return *lep_relIso04EAv2_;
}

const vector<int> &CMS3::lep_tightCharge() {
  if (not lep_tightCharge_isLoaded) {
    if (lep_tightCharge_branch != 0) {
      lep_tightCharge_branch->GetEntry(index);
    } else {
      printf("branch lep_tightCharge_branch does not exist!\n");
      exit(1);
    }
    lep_tightCharge_isLoaded = true;
  }
  return *lep_tightCharge_;
}

const vector<float> &CMS3::lep_trk_pt() {
  if (not lep_trk_pt_isLoaded) {
    if (lep_trk_pt_branch != 0) {
      lep_trk_pt_branch->GetEntry(index);
    } else {
      printf("branch lep_trk_pt_branch does not exist!\n");
      exit(1);
    }
    lep_trk_pt_isLoaded = true;
  }
  return *lep_trk_pt_;
}

const vector<int> &CMS3::lep_charge() {
  if (not lep_charge_isLoaded) {
    if (lep_charge_branch != 0) {
      lep_charge_branch->GetEntry(index);
    } else {
      printf("branch lep_charge_branch does not exist!\n");
      exit(1);
    }
    lep_charge_isLoaded = true;
  }
  return *lep_charge_;
}

const vector<float> &CMS3::lep_etaSC() {
  if (not lep_etaSC_isLoaded) {
    if (lep_etaSC_branch != 0) {
      lep_etaSC_branch->GetEntry(index);
    } else {
      printf("branch lep_etaSC_branch does not exist!\n");
      exit(1);
    }
    lep_etaSC_isLoaded = true;
  }
  return *lep_etaSC_;
}

const vector<float> &CMS3::lep_MVA() {
  if (not lep_MVA_isLoaded) {
    if (lep_MVA_branch != 0) {
      lep_MVA_branch->GetEntry(index);
    } else {
      printf("branch lep_MVA_branch does not exist!\n");
      exit(1);
    }
    lep_MVA_isLoaded = true;
  }
  return *lep_MVA_;
}

const vector<int> &CMS3::lep_isFromW() {
  if (not lep_isFromW_isLoaded) {
    if (lep_isFromW_branch != 0) {
      lep_isFromW_branch->GetEntry(index);
    } else {
      printf("branch lep_isFromW_branch does not exist!\n");
      exit(1);
    }
    lep_isFromW_isLoaded = true;
  }
  return *lep_isFromW_;
}

const vector<int> &CMS3::lep_isFromZ() {
  if (not lep_isFromZ_isLoaded) {
    if (lep_isFromZ_branch != 0) {
      lep_isFromZ_branch->GetEntry(index);
    } else {
      printf("branch lep_isFromZ_branch does not exist!\n");
      exit(1);
    }
    lep_isFromZ_isLoaded = true;
  }
  return *lep_isFromZ_;
}

const vector<int> &CMS3::lep_isFromB() {
  if (not lep_isFromB_isLoaded) {
    if (lep_isFromB_branch != 0) {
      lep_isFromB_branch->GetEntry(index);
    } else {
      printf("branch lep_isFromB_branch does not exist!\n");
      exit(1);
    }
    lep_isFromB_isLoaded = true;
  }
  return *lep_isFromB_;
}

const vector<int> &CMS3::lep_isFromC() {
  if (not lep_isFromC_isLoaded) {
    if (lep_isFromC_branch != 0) {
      lep_isFromC_branch->GetEntry(index);
    } else {
      printf("branch lep_isFromC_branch does not exist!\n");
      exit(1);
    }
    lep_isFromC_isLoaded = true;
  }
  return *lep_isFromC_;
}

const vector<int> &CMS3::lep_isFromL() {
  if (not lep_isFromL_isLoaded) {
    if (lep_isFromL_branch != 0) {
      lep_isFromL_branch->GetEntry(index);
    } else {
      printf("branch lep_isFromL_branch does not exist!\n");
      exit(1);
    }
    lep_isFromL_isLoaded = true;
  }
  return *lep_isFromL_;
}

const vector<int> &CMS3::lep_isFromLF() {
  if (not lep_isFromLF_isLoaded) {
    if (lep_isFromLF_branch != 0) {
      lep_isFromLF_branch->GetEntry(index);
    } else {
      printf("branch lep_isFromLF_branch does not exist!\n");
      exit(1);
    }
    lep_isFromLF_isLoaded = true;
  }
  return *lep_isFromLF_;
}

const vector<int> &CMS3::lep_genPart_index() {
  if (not lep_genPart_index_isLoaded) {
    if (lep_genPart_index_branch != 0) {
      lep_genPart_index_branch->GetEntry(index);
    } else {
      printf("branch lep_genPart_index_branch does not exist!\n");
      exit(1);
    }
    lep_genPart_index_isLoaded = true;
  }
  return *lep_genPart_index_;
}

const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &CMS3::jets_p4() {
  if (not jets_p4_isLoaded) {
    if (jets_p4_branch != 0) {
      jets_p4_branch->GetEntry(index);
    } else {
      printf("branch jets_p4_branch does not exist!\n");
      exit(1);
    }
    jets_p4_isLoaded = true;
  }
  return *jets_p4_;
}

const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &CMS3::jets_up_p4() {
  if (not jets_up_p4_isLoaded) {
    if (jets_up_p4_branch != 0) {
      jets_up_p4_branch->GetEntry(index);
    } else {
      printf("branch jets_up_p4_branch does not exist!\n");
      exit(1);
    }
    jets_up_p4_isLoaded = true;
  }
  return *jets_up_p4_;
}

const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &CMS3::jets_dn_p4() {
  if (not jets_dn_p4_isLoaded) {
    if (jets_dn_p4_branch != 0) {
      jets_dn_p4_branch->GetEntry(index);
    } else {
      printf("branch jets_dn_p4_branch does not exist!\n");
      exit(1);
    }
    jets_dn_p4_isLoaded = true;
  }
  return *jets_dn_p4_;
}

const vector<float> &CMS3::jets_csv() {
  if (not jets_csv_isLoaded) {
    if (jets_csv_branch != 0) {
      jets_csv_branch->GetEntry(index);
    } else {
      printf("branch jets_csv_branch does not exist!\n");
      exit(1);
    }
    jets_csv_isLoaded = true;
  }
  return *jets_csv_;
}

const vector<float> &CMS3::jets_up_csv() {
  if (not jets_up_csv_isLoaded) {
    if (jets_up_csv_branch != 0) {
      jets_up_csv_branch->GetEntry(index);
    } else {
      printf("branch jets_up_csv_branch does not exist!\n");
      exit(1);
    }
    jets_up_csv_isLoaded = true;
  }
  return *jets_up_csv_;
}

const vector<float> &CMS3::jets_dn_csv() {
  if (not jets_dn_csv_isLoaded) {
    if (jets_dn_csv_branch != 0) {
      jets_dn_csv_branch->GetEntry(index);
    } else {
      printf("branch jets_dn_csv_branch does not exist!\n");
      exit(1);
    }
    jets_dn_csv_isLoaded = true;
  }
  return *jets_dn_csv_;
}

const float &CMS3::met_pt() {
  if (not met_pt_isLoaded) {
    if (met_pt_branch != 0) {
      met_pt_branch->GetEntry(index);
    } else {
      printf("branch met_pt_branch does not exist!\n");
      exit(1);
    }
    met_pt_isLoaded = true;
  }
  return met_pt_;
}

const float &CMS3::met_phi() {
  if (not met_phi_isLoaded) {
    if (met_phi_branch != 0) {
      met_phi_branch->GetEntry(index);
    } else {
      printf("branch met_phi_branch does not exist!\n");
      exit(1);
    }
    met_phi_isLoaded = true;
  }
  return met_phi_;
}

const float &CMS3::met_up_pt() {
  if (not met_up_pt_isLoaded) {
    if (met_up_pt_branch != 0) {
      met_up_pt_branch->GetEntry(index);
    } else {
      printf("branch met_up_pt_branch does not exist!\n");
      exit(1);
    }
    met_up_pt_isLoaded = true;
  }
  return met_up_pt_;
}

const float &CMS3::met_up_phi() {
  if (not met_up_phi_isLoaded) {
    if (met_up_phi_branch != 0) {
      met_up_phi_branch->GetEntry(index);
    } else {
      printf("branch met_up_phi_branch does not exist!\n");
      exit(1);
    }
    met_up_phi_isLoaded = true;
  }
  return met_up_phi_;
}

const float &CMS3::met_dn_pt() {
  if (not met_dn_pt_isLoaded) {
    if (met_dn_pt_branch != 0) {
      met_dn_pt_branch->GetEntry(index);
    } else {
      printf("branch met_dn_pt_branch does not exist!\n");
      exit(1);
    }
    met_dn_pt_isLoaded = true;
  }
  return met_dn_pt_;
}

const float &CMS3::met_dn_phi() {
  if (not met_dn_phi_isLoaded) {
    if (met_dn_phi_branch != 0) {
      met_dn_phi_branch->GetEntry(index);
    } else {
      printf("branch met_dn_phi_branch does not exist!\n");
      exit(1);
    }
    met_dn_phi_isLoaded = true;
  }
  return met_dn_phi_;
}

const int &CMS3::firstgoodvertex() {
  if (not firstgoodvertex_isLoaded) {
    if (firstgoodvertex_branch != 0) {
      firstgoodvertex_branch->GetEntry(index);
    } else {
      printf("branch firstgoodvertex_branch does not exist!\n");
      exit(1);
    }
    firstgoodvertex_isLoaded = true;
  }
  return firstgoodvertex_;
}

const int &CMS3::nTrueInt() {
  if (not nTrueInt_isLoaded) {
    if (nTrueInt_branch != 0) {
      nTrueInt_branch->GetEntry(index);
    } else {
      printf("branch nTrueInt_branch does not exist!\n");
      exit(1);
    }
    nTrueInt_isLoaded = true;
  }
  return nTrueInt_;
}

const int &CMS3::nVert() {
  if (not nVert_isLoaded) {
    if (nVert_branch != 0) {
      nVert_branch->GetEntry(index);
    } else {
      printf("branch nVert_branch does not exist!\n");
      exit(1);
    }
    nVert_isLoaded = true;
  }
  return nVert_;
}

const int &CMS3::nisoTrack_mt2_cleaned_VVV_cutbased_veto() {
  if (not nisoTrack_mt2_cleaned_VVV_cutbased_veto_isLoaded) {
    if (nisoTrack_mt2_cleaned_VVV_cutbased_veto_branch != 0) {
      nisoTrack_mt2_cleaned_VVV_cutbased_veto_branch->GetEntry(index);
    } else {
      printf("branch nisoTrack_mt2_cleaned_VVV_cutbased_veto_branch does not exist!\n");
      exit(1);
    }
    nisoTrack_mt2_cleaned_VVV_cutbased_veto_isLoaded = true;
  }
  return nisoTrack_mt2_cleaned_VVV_cutbased_veto_;
}

const float &CMS3::weight_btagsf() {
  if (not weight_btagsf_isLoaded) {
    if (weight_btagsf_branch != 0) {
      weight_btagsf_branch->GetEntry(index);
    } else {
      printf("branch weight_btagsf_branch does not exist!\n");
      exit(1);
    }
    weight_btagsf_isLoaded = true;
  }
  return weight_btagsf_;
}

const float &CMS3::weight_btagsf_heavy_DN() {
  if (not weight_btagsf_heavy_DN_isLoaded) {
    if (weight_btagsf_heavy_DN_branch != 0) {
      weight_btagsf_heavy_DN_branch->GetEntry(index);
    } else {
      printf("branch weight_btagsf_heavy_DN_branch does not exist!\n");
      exit(1);
    }
    weight_btagsf_heavy_DN_isLoaded = true;
  }
  return weight_btagsf_heavy_DN_;
}

const float &CMS3::weight_btagsf_heavy_UP() {
  if (not weight_btagsf_heavy_UP_isLoaded) {
    if (weight_btagsf_heavy_UP_branch != 0) {
      weight_btagsf_heavy_UP_branch->GetEntry(index);
    } else {
      printf("branch weight_btagsf_heavy_UP_branch does not exist!\n");
      exit(1);
    }
    weight_btagsf_heavy_UP_isLoaded = true;
  }
  return weight_btagsf_heavy_UP_;
}

const float &CMS3::weight_btagsf_light_DN() {
  if (not weight_btagsf_light_DN_isLoaded) {
    if (weight_btagsf_light_DN_branch != 0) {
      weight_btagsf_light_DN_branch->GetEntry(index);
    } else {
      printf("branch weight_btagsf_light_DN_branch does not exist!\n");
      exit(1);
    }
    weight_btagsf_light_DN_isLoaded = true;
  }
  return weight_btagsf_light_DN_;
}

const float &CMS3::weight_btagsf_light_UP() {
  if (not weight_btagsf_light_UP_isLoaded) {
    if (weight_btagsf_light_UP_branch != 0) {
      weight_btagsf_light_UP_branch->GetEntry(index);
    } else {
      printf("branch weight_btagsf_light_UP_branch does not exist!\n");
      exit(1);
    }
    weight_btagsf_light_UP_isLoaded = true;
  }
  return weight_btagsf_light_UP_;
}

const float &CMS3::gen_ht() {
  if (not gen_ht_isLoaded) {
    if (gen_ht_branch != 0) {
      gen_ht_branch->GetEntry(index);
    } else {
      printf("branch gen_ht_branch does not exist!\n");
      exit(1);
    }
    gen_ht_isLoaded = true;
  }
  return gen_ht_;
}

const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &CMS3::genPart_p4() {
  if (not genPart_p4_isLoaded) {
    if (genPart_p4_branch != 0) {
      genPart_p4_branch->GetEntry(index);
    } else {
      printf("branch genPart_p4_branch does not exist!\n");
      exit(1);
    }
    genPart_p4_isLoaded = true;
  }
  return *genPart_p4_;
}

const vector<int> &CMS3::genPart_motherId() {
  if (not genPart_motherId_isLoaded) {
    if (genPart_motherId_branch != 0) {
      genPart_motherId_branch->GetEntry(index);
    } else {
      printf("branch genPart_motherId_branch does not exist!\n");
      exit(1);
    }
    genPart_motherId_isLoaded = true;
  }
  return *genPart_motherId_;
}

const vector<int> &CMS3::genPart_pdgId() {
  if (not genPart_pdgId_isLoaded) {
    if (genPart_pdgId_branch != 0) {
      genPart_pdgId_branch->GetEntry(index);
    } else {
      printf("branch genPart_pdgId_branch does not exist!\n");
      exit(1);
    }
    genPart_pdgId_isLoaded = true;
  }
  return *genPart_pdgId_;
}

const vector<int> &CMS3::genPart_charge() {
  if (not genPart_charge_isLoaded) {
    if (genPart_charge_branch != 0) {
      genPart_charge_branch->GetEntry(index);
    } else {
      printf("branch genPart_charge_branch does not exist!\n");
      exit(1);
    }
    genPart_charge_isLoaded = true;
  }
  return *genPart_charge_;
}

const vector<int> &CMS3::genPart_status() {
  if (not genPart_status_isLoaded) {
    if (genPart_status_branch != 0) {
      genPart_status_branch->GetEntry(index);
    } else {
      printf("branch genPart_status_branch does not exist!\n");
      exit(1);
    }
    genPart_status_isLoaded = true;
  }
  return *genPart_status_;
}

const int &CMS3::ngenLep() {
  if (not ngenLep_isLoaded) {
    if (ngenLep_branch != 0) {
      ngenLep_branch->GetEntry(index);
    } else {
      printf("branch ngenLep_branch does not exist!\n");
      exit(1);
    }
    ngenLep_isLoaded = true;
  }
  return ngenLep_;
}

const int &CMS3::ngenLepFromTau() {
  if (not ngenLepFromTau_isLoaded) {
    if (ngenLepFromTau_branch != 0) {
      ngenLepFromTau_branch->GetEntry(index);
    } else {
      printf("branch ngenLepFromTau_branch does not exist!\n");
      exit(1);
    }
    ngenLepFromTau_isLoaded = true;
  }
  return ngenLepFromTau_;
}

const int &CMS3::Flag_AllEventFilters() {
  if (not Flag_AllEventFilters_isLoaded) {
    if (Flag_AllEventFilters_branch != 0) {
      Flag_AllEventFilters_branch->GetEntry(index);
    } else {
      printf("branch Flag_AllEventFilters_branch does not exist!\n");
      exit(1);
    }
    Flag_AllEventFilters_isLoaded = true;
  }
  return Flag_AllEventFilters_;
}

const int &CMS3::Flag_EcalDeadCellTriggerPrimitiveFilter() {
  if (not Flag_EcalDeadCellTriggerPrimitiveFilter_isLoaded) {
    if (Flag_EcalDeadCellTriggerPrimitiveFilter_branch != 0) {
      Flag_EcalDeadCellTriggerPrimitiveFilter_branch->GetEntry(index);
    } else {
      printf("branch Flag_EcalDeadCellTriggerPrimitiveFilter_branch does not exist!\n");
      exit(1);
    }
    Flag_EcalDeadCellTriggerPrimitiveFilter_isLoaded = true;
  }
  return Flag_EcalDeadCellTriggerPrimitiveFilter_;
}

const int &CMS3::Flag_HBHEIsoNoiseFilter() {
  if (not Flag_HBHEIsoNoiseFilter_isLoaded) {
    if (Flag_HBHEIsoNoiseFilter_branch != 0) {
      Flag_HBHEIsoNoiseFilter_branch->GetEntry(index);
    } else {
      printf("branch Flag_HBHEIsoNoiseFilter_branch does not exist!\n");
      exit(1);
    }
    Flag_HBHEIsoNoiseFilter_isLoaded = true;
  }
  return Flag_HBHEIsoNoiseFilter_;
}

const int &CMS3::Flag_HBHENoiseFilter() {
  if (not Flag_HBHENoiseFilter_isLoaded) {
    if (Flag_HBHENoiseFilter_branch != 0) {
      Flag_HBHENoiseFilter_branch->GetEntry(index);
    } else {
      printf("branch Flag_HBHENoiseFilter_branch does not exist!\n");
      exit(1);
    }
    Flag_HBHENoiseFilter_isLoaded = true;
  }
  return Flag_HBHENoiseFilter_;
}

const int &CMS3::Flag_badChargedCandidateFilter() {
  if (not Flag_badChargedCandidateFilter_isLoaded) {
    if (Flag_badChargedCandidateFilter_branch != 0) {
      Flag_badChargedCandidateFilter_branch->GetEntry(index);
    } else {
      printf("branch Flag_badChargedCandidateFilter_branch does not exist!\n");
      exit(1);
    }
    Flag_badChargedCandidateFilter_isLoaded = true;
  }
  return Flag_badChargedCandidateFilter_;
}

const int &CMS3::Flag_badMuonFilter() {
  if (not Flag_badMuonFilter_isLoaded) {
    if (Flag_badMuonFilter_branch != 0) {
      Flag_badMuonFilter_branch->GetEntry(index);
    } else {
      printf("branch Flag_badMuonFilter_branch does not exist!\n");
      exit(1);
    }
    Flag_badMuonFilter_isLoaded = true;
  }
  return Flag_badMuonFilter_;
}

const int &CMS3::Flag_eeBadScFilter() {
  if (not Flag_eeBadScFilter_isLoaded) {
    if (Flag_eeBadScFilter_branch != 0) {
      Flag_eeBadScFilter_branch->GetEntry(index);
    } else {
      printf("branch Flag_eeBadScFilter_branch does not exist!\n");
      exit(1);
    }
    Flag_eeBadScFilter_isLoaded = true;
  }
  return Flag_eeBadScFilter_;
}

const int &CMS3::Flag_globalTightHalo2016() {
  if (not Flag_globalTightHalo2016_isLoaded) {
    if (Flag_globalTightHalo2016_branch != 0) {
      Flag_globalTightHalo2016_branch->GetEntry(index);
    } else {
      printf("branch Flag_globalTightHalo2016_branch does not exist!\n");
      exit(1);
    }
    Flag_globalTightHalo2016_isLoaded = true;
  }
  return Flag_globalTightHalo2016_;
}

const int &CMS3::Flag_goodVertices() {
  if (not Flag_goodVertices_isLoaded) {
    if (Flag_goodVertices_branch != 0) {
      Flag_goodVertices_branch->GetEntry(index);
    } else {
      printf("branch Flag_goodVertices_branch does not exist!\n");
      exit(1);
    }
    Flag_goodVertices_isLoaded = true;
  }
  return Flag_goodVertices_;
}

const int &CMS3::nVlep() {
  if (not nVlep_isLoaded) {
    if (nVlep_branch != 0) {
      nVlep_branch->GetEntry(index);
    } else {
      printf("branch nVlep_branch does not exist!\n");
      exit(1);
    }
    nVlep_isLoaded = true;
  }
  return nVlep_;
}

const int &CMS3::nTlep() {
  if (not nTlep_isLoaded) {
    if (nTlep_branch != 0) {
      nTlep_branch->GetEntry(index);
    } else {
      printf("branch nTlep_branch does not exist!\n");
      exit(1);
    }
    nTlep_isLoaded = true;
  }
  return nTlep_;
}

const int &CMS3::nTlepSS() {
  if (not nTlepSS_isLoaded) {
    if (nTlepSS_branch != 0) {
      nTlepSS_branch->GetEntry(index);
    } else {
      printf("branch nTlepSS_branch does not exist!\n");
      exit(1);
    }
    nTlepSS_isLoaded = true;
  }
  return nTlepSS_;
}

const int &CMS3::nLlep() {
  if (not nLlep_isLoaded) {
    if (nLlep_branch != 0) {
      nLlep_branch->GetEntry(index);
    } else {
      printf("branch nLlep_branch does not exist!\n");
      exit(1);
    }
    nLlep_isLoaded = true;
  }
  return nLlep_;
}

const int &CMS3::nSFOS() {
  if (not nSFOS_isLoaded) {
    if (nSFOS_branch != 0) {
      nSFOS_branch->GetEntry(index);
    } else {
      printf("branch nSFOS_branch does not exist!\n");
      exit(1);
    }
    nSFOS_isLoaded = true;
  }
  return nSFOS_;
}

const int &CMS3::nSFOSinZ() {
  if (not nSFOSinZ_isLoaded) {
    if (nSFOSinZ_branch != 0) {
      nSFOSinZ_branch->GetEntry(index);
    } else {
      printf("branch nSFOSinZ_branch does not exist!\n");
      exit(1);
    }
    nSFOSinZ_isLoaded = true;
  }
  return nSFOSinZ_;
}

const int &CMS3::nj() {
  if (not nj_isLoaded) {
    if (nj_branch != 0) {
      nj_branch->GetEntry(index);
    } else {
      printf("branch nj_branch does not exist!\n");
      exit(1);
    }
    nj_isLoaded = true;
  }
  return nj_;
}

const int &CMS3::nj_up() {
  if (not nj_up_isLoaded) {
    if (nj_up_branch != 0) {
      nj_up_branch->GetEntry(index);
    } else {
      printf("branch nj_up_branch does not exist!\n");
      exit(1);
    }
    nj_up_isLoaded = true;
  }
  return nj_up_;
}

const int &CMS3::nj_dn() {
  if (not nj_dn_isLoaded) {
    if (nj_dn_branch != 0) {
      nj_dn_branch->GetEntry(index);
    } else {
      printf("branch nj_dn_branch does not exist!\n");
      exit(1);
    }
    nj_dn_isLoaded = true;
  }
  return nj_dn_;
}

const int &CMS3::nj30() {
  if (not nj30_isLoaded) {
    if (nj30_branch != 0) {
      nj30_branch->GetEntry(index);
    } else {
      printf("branch nj30_branch does not exist!\n");
      exit(1);
    }
    nj30_isLoaded = true;
  }
  return nj30_;
}

const int &CMS3::nj30_up() {
  if (not nj30_up_isLoaded) {
    if (nj30_up_branch != 0) {
      nj30_up_branch->GetEntry(index);
    } else {
      printf("branch nj30_up_branch does not exist!\n");
      exit(1);
    }
    nj30_up_isLoaded = true;
  }
  return nj30_up_;
}

const int &CMS3::nj30_dn() {
  if (not nj30_dn_isLoaded) {
    if (nj30_dn_branch != 0) {
      nj30_dn_branch->GetEntry(index);
    } else {
      printf("branch nj30_dn_branch does not exist!\n");
      exit(1);
    }
    nj30_dn_isLoaded = true;
  }
  return nj30_dn_;
}

const int &CMS3::nb() {
  if (not nb_isLoaded) {
    if (nb_branch != 0) {
      nb_branch->GetEntry(index);
    } else {
      printf("branch nb_branch does not exist!\n");
      exit(1);
    }
    nb_isLoaded = true;
  }
  return nb_;
}

const int &CMS3::nb_up() {
  if (not nb_up_isLoaded) {
    if (nb_up_branch != 0) {
      nb_up_branch->GetEntry(index);
    } else {
      printf("branch nb_up_branch does not exist!\n");
      exit(1);
    }
    nb_up_isLoaded = true;
  }
  return nb_up_;
}

const int &CMS3::nb_dn() {
  if (not nb_dn_isLoaded) {
    if (nb_dn_branch != 0) {
      nb_dn_branch->GetEntry(index);
    } else {
      printf("branch nb_dn_branch does not exist!\n");
      exit(1);
    }
    nb_dn_isLoaded = true;
  }
  return nb_dn_;
}

const float &CMS3::Mjj() {
  if (not Mjj_isLoaded) {
    if (Mjj_branch != 0) {
      Mjj_branch->GetEntry(index);
    } else {
      printf("branch Mjj_branch does not exist!\n");
      exit(1);
    }
    Mjj_isLoaded = true;
  }
  return Mjj_;
}

const float &CMS3::Mjj_up() {
  if (not Mjj_up_isLoaded) {
    if (Mjj_up_branch != 0) {
      Mjj_up_branch->GetEntry(index);
    } else {
      printf("branch Mjj_up_branch does not exist!\n");
      exit(1);
    }
    Mjj_up_isLoaded = true;
  }
  return Mjj_up_;
}

const float &CMS3::Mjj_dn() {
  if (not Mjj_dn_isLoaded) {
    if (Mjj_dn_branch != 0) {
      Mjj_dn_branch->GetEntry(index);
    } else {
      printf("branch Mjj_dn_branch does not exist!\n");
      exit(1);
    }
    Mjj_dn_isLoaded = true;
  }
  return Mjj_dn_;
}

const float &CMS3::MjjVBF() {
  if (not MjjVBF_isLoaded) {
    if (MjjVBF_branch != 0) {
      MjjVBF_branch->GetEntry(index);
    } else {
      printf("branch MjjVBF_branch does not exist!\n");
      exit(1);
    }
    MjjVBF_isLoaded = true;
  }
  return MjjVBF_;
}

const float &CMS3::MjjVBF_up() {
  if (not MjjVBF_up_isLoaded) {
    if (MjjVBF_up_branch != 0) {
      MjjVBF_up_branch->GetEntry(index);
    } else {
      printf("branch MjjVBF_up_branch does not exist!\n");
      exit(1);
    }
    MjjVBF_up_isLoaded = true;
  }
  return MjjVBF_up_;
}

const float &CMS3::MjjVBF_dn() {
  if (not MjjVBF_dn_isLoaded) {
    if (MjjVBF_dn_branch != 0) {
      MjjVBF_dn_branch->GetEntry(index);
    } else {
      printf("branch MjjVBF_dn_branch does not exist!\n");
      exit(1);
    }
    MjjVBF_dn_isLoaded = true;
  }
  return MjjVBF_dn_;
}

const float &CMS3::DetajjVBF() {
  if (not DetajjVBF_isLoaded) {
    if (DetajjVBF_branch != 0) {
      DetajjVBF_branch->GetEntry(index);
    } else {
      printf("branch DetajjVBF_branch does not exist!\n");
      exit(1);
    }
    DetajjVBF_isLoaded = true;
  }
  return DetajjVBF_;
}

const float &CMS3::DetajjVBF_up() {
  if (not DetajjVBF_up_isLoaded) {
    if (DetajjVBF_up_branch != 0) {
      DetajjVBF_up_branch->GetEntry(index);
    } else {
      printf("branch DetajjVBF_up_branch does not exist!\n");
      exit(1);
    }
    DetajjVBF_up_isLoaded = true;
  }
  return DetajjVBF_up_;
}

const float &CMS3::DetajjVBF_dn() {
  if (not DetajjVBF_dn_isLoaded) {
    if (DetajjVBF_dn_branch != 0) {
      DetajjVBF_dn_branch->GetEntry(index);
    } else {
      printf("branch DetajjVBF_dn_branch does not exist!\n");
      exit(1);
    }
    DetajjVBF_dn_isLoaded = true;
  }
  return DetajjVBF_dn_;
}

const float &CMS3::MjjL() {
  if (not MjjL_isLoaded) {
    if (MjjL_branch != 0) {
      MjjL_branch->GetEntry(index);
    } else {
      printf("branch MjjL_branch does not exist!\n");
      exit(1);
    }
    MjjL_isLoaded = true;
  }
  return MjjL_;
}

const float &CMS3::MjjL_up() {
  if (not MjjL_up_isLoaded) {
    if (MjjL_up_branch != 0) {
      MjjL_up_branch->GetEntry(index);
    } else {
      printf("branch MjjL_up_branch does not exist!\n");
      exit(1);
    }
    MjjL_up_isLoaded = true;
  }
  return MjjL_up_;
}

const float &CMS3::MjjL_dn() {
  if (not MjjL_dn_isLoaded) {
    if (MjjL_dn_branch != 0) {
      MjjL_dn_branch->GetEntry(index);
    } else {
      printf("branch MjjL_dn_branch does not exist!\n");
      exit(1);
    }
    MjjL_dn_isLoaded = true;
  }
  return MjjL_dn_;
}

const float &CMS3::DetajjL() {
  if (not DetajjL_isLoaded) {
    if (DetajjL_branch != 0) {
      DetajjL_branch->GetEntry(index);
    } else {
      printf("branch DetajjL_branch does not exist!\n");
      exit(1);
    }
    DetajjL_isLoaded = true;
  }
  return DetajjL_;
}

const float &CMS3::DetajjL_up() {
  if (not DetajjL_up_isLoaded) {
    if (DetajjL_up_branch != 0) {
      DetajjL_up_branch->GetEntry(index);
    } else {
      printf("branch DetajjL_up_branch does not exist!\n");
      exit(1);
    }
    DetajjL_up_isLoaded = true;
  }
  return DetajjL_up_;
}

const float &CMS3::DetajjL_dn() {
  if (not DetajjL_dn_isLoaded) {
    if (DetajjL_dn_branch != 0) {
      DetajjL_dn_branch->GetEntry(index);
    } else {
      printf("branch DetajjL_dn_branch does not exist!\n");
      exit(1);
    }
    DetajjL_dn_isLoaded = true;
  }
  return DetajjL_dn_;
}

const float &CMS3::MllSS() {
  if (not MllSS_isLoaded) {
    if (MllSS_branch != 0) {
      MllSS_branch->GetEntry(index);
    } else {
      printf("branch MllSS_branch does not exist!\n");
      exit(1);
    }
    MllSS_isLoaded = true;
  }
  return MllSS_;
}

const float &CMS3::MeeSS() {
  if (not MeeSS_isLoaded) {
    if (MeeSS_branch != 0) {
      MeeSS_branch->GetEntry(index);
    } else {
      printf("branch MeeSS_branch does not exist!\n");
      exit(1);
    }
    MeeSS_isLoaded = true;
  }
  return MeeSS_;
}

const float &CMS3::Mll3L() {
  if (not Mll3L_isLoaded) {
    if (Mll3L_branch != 0) {
      Mll3L_branch->GetEntry(index);
    } else {
      printf("branch Mll3L_branch does not exist!\n");
      exit(1);
    }
    Mll3L_isLoaded = true;
  }
  return Mll3L_;
}

const float &CMS3::Mee3L() {
  if (not Mee3L_isLoaded) {
    if (Mee3L_branch != 0) {
      Mee3L_branch->GetEntry(index);
    } else {
      printf("branch Mee3L_branch does not exist!\n");
      exit(1);
    }
    Mee3L_isLoaded = true;
  }
  return Mee3L_;
}

const float &CMS3::Mll3L1() {
  if (not Mll3L1_isLoaded) {
    if (Mll3L1_branch != 0) {
      Mll3L1_branch->GetEntry(index);
    } else {
      printf("branch Mll3L1_branch does not exist!\n");
      exit(1);
    }
    Mll3L1_isLoaded = true;
  }
  return Mll3L1_;
}

const float &CMS3::M3l() {
  if (not M3l_isLoaded) {
    if (M3l_branch != 0) {
      M3l_branch->GetEntry(index);
    } else {
      printf("branch M3l_branch does not exist!\n");
      exit(1);
    }
    M3l_isLoaded = true;
  }
  return M3l_;
}

const float &CMS3::Pt3l() {
  if (not Pt3l_isLoaded) {
    if (Pt3l_branch != 0) {
      Pt3l_branch->GetEntry(index);
    } else {
      printf("branch Pt3l_branch does not exist!\n");
      exit(1);
    }
    Pt3l_isLoaded = true;
  }
  return Pt3l_;
}

const float &CMS3::M01() {
  if (not M01_isLoaded) {
    if (M01_branch != 0) {
      M01_branch->GetEntry(index);
    } else {
      printf("branch M01_branch does not exist!\n");
      exit(1);
    }
    M01_isLoaded = true;
  }
  return M01_;
}

const float &CMS3::M02() {
  if (not M02_isLoaded) {
    if (M02_branch != 0) {
      M02_branch->GetEntry(index);
    } else {
      printf("branch M02_branch does not exist!\n");
      exit(1);
    }
    M02_isLoaded = true;
  }
  return M02_;
}

const float &CMS3::M12() {
  if (not M12_isLoaded) {
    if (M12_branch != 0) {
      M12_branch->GetEntry(index);
    } else {
      printf("branch M12_branch does not exist!\n");
      exit(1);
    }
    M12_isLoaded = true;
  }
  return M12_;
}

const int &CMS3::isSFOS01() {
  if (not isSFOS01_isLoaded) {
    if (isSFOS01_branch != 0) {
      isSFOS01_branch->GetEntry(index);
    } else {
      printf("branch isSFOS01_branch does not exist!\n");
      exit(1);
    }
    isSFOS01_isLoaded = true;
  }
  return isSFOS01_;
}

const int &CMS3::isSFOS02() {
  if (not isSFOS02_isLoaded) {
    if (isSFOS02_branch != 0) {
      isSFOS02_branch->GetEntry(index);
    } else {
      printf("branch isSFOS02_branch does not exist!\n");
      exit(1);
    }
    isSFOS02_isLoaded = true;
  }
  return isSFOS02_;
}

const int &CMS3::isSFOS12() {
  if (not isSFOS12_isLoaded) {
    if (isSFOS12_branch != 0) {
      isSFOS12_branch->GetEntry(index);
    } else {
      printf("branch isSFOS12_branch does not exist!\n");
      exit(1);
    }
    isSFOS12_isLoaded = true;
  }
  return isSFOS12_;
}

const float &CMS3::DPhi3lMET() {
  if (not DPhi3lMET_isLoaded) {
    if (DPhi3lMET_branch != 0) {
      DPhi3lMET_branch->GetEntry(index);
    } else {
      printf("branch DPhi3lMET_branch does not exist!\n");
      exit(1);
    }
    DPhi3lMET_isLoaded = true;
  }
  return DPhi3lMET_;
}

const float &CMS3::DPhi3lMET_up() {
  if (not DPhi3lMET_up_isLoaded) {
    if (DPhi3lMET_up_branch != 0) {
      DPhi3lMET_up_branch->GetEntry(index);
    } else {
      printf("branch DPhi3lMET_up_branch does not exist!\n");
      exit(1);
    }
    DPhi3lMET_up_isLoaded = true;
  }
  return DPhi3lMET_up_;
}

const float &CMS3::DPhi3lMET_dn() {
  if (not DPhi3lMET_dn_isLoaded) {
    if (DPhi3lMET_dn_branch != 0) {
      DPhi3lMET_dn_branch->GetEntry(index);
    } else {
      printf("branch DPhi3lMET_dn_branch does not exist!\n");
      exit(1);
    }
    DPhi3lMET_dn_isLoaded = true;
  }
  return DPhi3lMET_dn_;
}

const float &CMS3::MTmax() {
  if (not MTmax_isLoaded) {
    if (MTmax_branch != 0) {
      MTmax_branch->GetEntry(index);
    } else {
      printf("branch MTmax_branch does not exist!\n");
      exit(1);
    }
    MTmax_isLoaded = true;
  }
  return MTmax_;
}

const float &CMS3::MTmax_up() {
  if (not MTmax_up_isLoaded) {
    if (MTmax_up_branch != 0) {
      MTmax_up_branch->GetEntry(index);
    } else {
      printf("branch MTmax_up_branch does not exist!\n");
      exit(1);
    }
    MTmax_up_isLoaded = true;
  }
  return MTmax_up_;
}

const float &CMS3::MTmax_dn() {
  if (not MTmax_dn_isLoaded) {
    if (MTmax_dn_branch != 0) {
      MTmax_dn_branch->GetEntry(index);
    } else {
      printf("branch MTmax_dn_branch does not exist!\n");
      exit(1);
    }
    MTmax_dn_isLoaded = true;
  }
  return MTmax_dn_;
}

const float &CMS3::MTmin() {
  if (not MTmin_isLoaded) {
    if (MTmin_branch != 0) {
      MTmin_branch->GetEntry(index);
    } else {
      printf("branch MTmin_branch does not exist!\n");
      exit(1);
    }
    MTmin_isLoaded = true;
  }
  return MTmin_;
}

const float &CMS3::MTmin_up() {
  if (not MTmin_up_isLoaded) {
    if (MTmin_up_branch != 0) {
      MTmin_up_branch->GetEntry(index);
    } else {
      printf("branch MTmin_up_branch does not exist!\n");
      exit(1);
    }
    MTmin_up_isLoaded = true;
  }
  return MTmin_up_;
}

const float &CMS3::MTmin_dn() {
  if (not MTmin_dn_isLoaded) {
    if (MTmin_dn_branch != 0) {
      MTmin_dn_branch->GetEntry(index);
    } else {
      printf("branch MTmin_dn_branch does not exist!\n");
      exit(1);
    }
    MTmin_dn_isLoaded = true;
  }
  return MTmin_dn_;
}

const float &CMS3::MT3rd() {
  if (not MT3rd_isLoaded) {
    if (MT3rd_branch != 0) {
      MT3rd_branch->GetEntry(index);
    } else {
      printf("branch MT3rd_branch does not exist!\n");
      exit(1);
    }
    MT3rd_isLoaded = true;
  }
  return MT3rd_;
}

const float &CMS3::MT3rd_up() {
  if (not MT3rd_up_isLoaded) {
    if (MT3rd_up_branch != 0) {
      MT3rd_up_branch->GetEntry(index);
    } else {
      printf("branch MT3rd_up_branch does not exist!\n");
      exit(1);
    }
    MT3rd_up_isLoaded = true;
  }
  return MT3rd_up_;
}

const float &CMS3::MT3rd_dn() {
  if (not MT3rd_dn_isLoaded) {
    if (MT3rd_dn_branch != 0) {
      MT3rd_dn_branch->GetEntry(index);
    } else {
      printf("branch MT3rd_dn_branch does not exist!\n");
      exit(1);
    }
    MT3rd_dn_isLoaded = true;
  }
  return MT3rd_dn_;
}

const int &CMS3::passSSee() {
  if (not passSSee_isLoaded) {
    if (passSSee_branch != 0) {
      passSSee_branch->GetEntry(index);
    } else {
      printf("branch passSSee_branch does not exist!\n");
      exit(1);
    }
    passSSee_isLoaded = true;
  }
  return passSSee_;
}

const int &CMS3::passSSem() {
  if (not passSSem_isLoaded) {
    if (passSSem_branch != 0) {
      passSSem_branch->GetEntry(index);
    } else {
      printf("branch passSSem_branch does not exist!\n");
      exit(1);
    }
    passSSem_isLoaded = true;
  }
  return passSSem_;
}

const int &CMS3::passSSmm() {
  if (not passSSmm_isLoaded) {
    if (passSSmm_branch != 0) {
      passSSmm_branch->GetEntry(index);
    } else {
      printf("branch passSSmm_branch does not exist!\n");
      exit(1);
    }
    passSSmm_isLoaded = true;
  }
  return passSSmm_;
}

const int &CMS3::lep_idx0_SS() {
  if (not lep_idx0_SS_isLoaded) {
    if (lep_idx0_SS_branch != 0) {
      lep_idx0_SS_branch->GetEntry(index);
    } else {
      printf("branch lep_idx0_SS_branch does not exist!\n");
      exit(1);
    }
    lep_idx0_SS_isLoaded = true;
  }
  return lep_idx0_SS_;
}

const int &CMS3::lep_idx1_SS() {
  if (not lep_idx1_SS_isLoaded) {
    if (lep_idx1_SS_branch != 0) {
      lep_idx1_SS_branch->GetEntry(index);
    } else {
      printf("branch lep_idx1_SS_branch does not exist!\n");
      exit(1);
    }
    lep_idx1_SS_isLoaded = true;
  }
  return lep_idx1_SS_;
}

const TString &CMS3::bkgtype() {
  if (not bkgtype_isLoaded) {
    if (bkgtype_branch != 0) {
      bkgtype_branch->GetEntry(index);
    } else {
      printf("branch bkgtype_branch does not exist!\n");
      exit(1);
    }
    bkgtype_isLoaded = true;
  }
  return *bkgtype_;
}

const int &CMS3::vetophoton() {
  if (not vetophoton_isLoaded) {
    if (vetophoton_branch != 0) {
      vetophoton_branch->GetEntry(index);
    } else {
      printf("branch vetophoton_branch does not exist!\n");
      exit(1);
    }
    vetophoton_isLoaded = true;
  }
  return vetophoton_;
}

const float &CMS3::purewgt() {
  if (not purewgt_isLoaded) {
    if (purewgt_branch != 0) {
      purewgt_branch->GetEntry(index);
    } else {
      printf("branch purewgt_branch does not exist!\n");
      exit(1);
    }
    purewgt_isLoaded = true;
  }
  return purewgt_;
}

const float &CMS3::purewgt_up() {
  if (not purewgt_up_isLoaded) {
    if (purewgt_up_branch != 0) {
      purewgt_up_branch->GetEntry(index);
    } else {
      printf("branch purewgt_up_branch does not exist!\n");
      exit(1);
    }
    purewgt_up_isLoaded = true;
  }
  return purewgt_up_;
}

const float &CMS3::purewgt_dn() {
  if (not purewgt_dn_isLoaded) {
    if (purewgt_dn_branch != 0) {
      purewgt_dn_branch->GetEntry(index);
    } else {
      printf("branch purewgt_dn_branch does not exist!\n");
      exit(1);
    }
    purewgt_dn_isLoaded = true;
  }
  return purewgt_dn_;
}

const float &CMS3::ffwgt() {
  if (not ffwgt_isLoaded) {
    if (ffwgt_branch != 0) {
      ffwgt_branch->GetEntry(index);
    } else {
      printf("branch ffwgt_branch does not exist!\n");
      exit(1);
    }
    ffwgt_isLoaded = true;
  }
  return ffwgt_;
}

const float &CMS3::ffwgt_up() {
  if (not ffwgt_up_isLoaded) {
    if (ffwgt_up_branch != 0) {
      ffwgt_up_branch->GetEntry(index);
    } else {
      printf("branch ffwgt_up_branch does not exist!\n");
      exit(1);
    }
    ffwgt_up_isLoaded = true;
  }
  return ffwgt_up_;
}

const float &CMS3::ffwgt_dn() {
  if (not ffwgt_dn_isLoaded) {
    if (ffwgt_dn_branch != 0) {
      ffwgt_dn_branch->GetEntry(index);
    } else {
      printf("branch ffwgt_dn_branch does not exist!\n");
      exit(1);
    }
    ffwgt_dn_isLoaded = true;
  }
  return ffwgt_dn_;
}

const float &CMS3::ffwgtqcd() {
  if (not ffwgtqcd_isLoaded) {
    if (ffwgtqcd_branch != 0) {
      ffwgtqcd_branch->GetEntry(index);
    } else {
      printf("branch ffwgtqcd_branch does not exist!\n");
      exit(1);
    }
    ffwgtqcd_isLoaded = true;
  }
  return ffwgtqcd_;
}

const float &CMS3::ffwgtqcd_up() {
  if (not ffwgtqcd_up_isLoaded) {
    if (ffwgtqcd_up_branch != 0) {
      ffwgtqcd_up_branch->GetEntry(index);
    } else {
      printf("branch ffwgtqcd_up_branch does not exist!\n");
      exit(1);
    }
    ffwgtqcd_up_isLoaded = true;
  }
  return ffwgtqcd_up_;
}

const float &CMS3::ffwgtqcd_dn() {
  if (not ffwgtqcd_dn_isLoaded) {
    if (ffwgtqcd_dn_branch != 0) {
      ffwgtqcd_dn_branch->GetEntry(index);
    } else {
      printf("branch ffwgtqcd_dn_branch does not exist!\n");
      exit(1);
    }
    ffwgtqcd_dn_isLoaded = true;
  }
  return ffwgtqcd_dn_;
}

const float &CMS3::lepsf() {
  if (not lepsf_isLoaded) {
    if (lepsf_branch != 0) {
      lepsf_branch->GetEntry(index);
    } else {
      printf("branch lepsf_branch does not exist!\n");
      exit(1);
    }
    lepsf_isLoaded = true;
  }
  return lepsf_;
}

const float &CMS3::lepsf_up() {
  if (not lepsf_up_isLoaded) {
    if (lepsf_up_branch != 0) {
      lepsf_up_branch->GetEntry(index);
    } else {
      printf("branch lepsf_up_branch does not exist!\n");
      exit(1);
    }
    lepsf_up_isLoaded = true;
  }
  return lepsf_up_;
}

const float &CMS3::lepsf_dn() {
  if (not lepsf_dn_isLoaded) {
    if (lepsf_dn_branch != 0) {
      lepsf_dn_branch->GetEntry(index);
    } else {
      printf("branch lepsf_dn_branch does not exist!\n");
      exit(1);
    }
    lepsf_dn_isLoaded = true;
  }
  return lepsf_dn_;
}

const float &CMS3::trigeff() {
  if (not trigeff_isLoaded) {
    if (trigeff_branch != 0) {
      trigeff_branch->GetEntry(index);
    } else {
      printf("branch trigeff_branch does not exist!\n");
      exit(1);
    }
    trigeff_isLoaded = true;
  }
  return trigeff_;
}

const float &CMS3::trigeff_up() {
  if (not trigeff_up_isLoaded) {
    if (trigeff_up_branch != 0) {
      trigeff_up_branch->GetEntry(index);
    } else {
      printf("branch trigeff_up_branch does not exist!\n");
      exit(1);
    }
    trigeff_up_isLoaded = true;
  }
  return trigeff_up_;
}

const float &CMS3::trigeff_dn() {
  if (not trigeff_dn_isLoaded) {
    if (trigeff_dn_branch != 0) {
      trigeff_dn_branch->GetEntry(index);
    } else {
      printf("branch trigeff_dn_branch does not exist!\n");
      exit(1);
    }
    trigeff_dn_isLoaded = true;
  }
  return trigeff_dn_;
}


void CMS3::progress( int nEventsTotal, int nEventsChain ){
  int period = 1000;
  if (nEventsTotal%1000 == 0) {
    // xterm magic from L. Vacavant and A. Cerri
    if (isatty(1)) {
      if ((nEventsChain - nEventsTotal) > period) {
        float frac = (float)nEventsTotal/(nEventsChain*0.01);
        printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%"
             "\033[0m\033[32m <---\033[0m\015", frac);
        fflush(stdout);
      }
      else {
        printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%"
               "\033[0m\033[32m <---\033[0m\015", 100.);
        cout << endl;
      }
    }
  }
}

namespace tas {

const int &run() { return cms3.run(); }
const int &lumi() { return cms3.lumi(); }
const unsigned long long &evt() { return cms3.evt(); }
const int &isData() { return cms3.isData(); }
const float &evt_scale1fb() { return cms3.evt_scale1fb(); }
const int &evt_passgoodrunlist() { return cms3.evt_passgoodrunlist(); }
const int &HLT_DoubleMu() { return cms3.HLT_DoubleMu(); }
const int &HLT_DoubleEl() { return cms3.HLT_DoubleEl(); }
const int &HLT_DoubleEl_DZ() { return cms3.HLT_DoubleEl_DZ(); }
const int &HLT_DoubleEl_DZ_2() { return cms3.HLT_DoubleEl_DZ_2(); }
const int &HLT_MuEG() { return cms3.HLT_MuEG(); }
const int &mc_HLT_DoubleMu() { return cms3.mc_HLT_DoubleMu(); }
const int &mc_HLT_DoubleEl() { return cms3.mc_HLT_DoubleEl(); }
const int &mc_HLT_DoubleEl_DZ() { return cms3.mc_HLT_DoubleEl_DZ(); }
const int &mc_HLT_DoubleEl_DZ_2() { return cms3.mc_HLT_DoubleEl_DZ_2(); }
const int &mc_HLT_MuEG() { return cms3.mc_HLT_MuEG(); }
const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &lep_p4() { return cms3.lep_p4(); }
const vector<float> &lep_pt() { return cms3.lep_pt(); }
const vector<float> &lep_eta() { return cms3.lep_eta(); }
const vector<float> &lep_phi() { return cms3.lep_phi(); }
const vector<float> &lep_coneCorrPt() { return cms3.lep_coneCorrPt(); }
const vector<float> &lep_ip3d() { return cms3.lep_ip3d(); }
const vector<float> &lep_ip3derr() { return cms3.lep_ip3derr(); }
const vector<int> &lep_isTriggerSafe_v1() { return cms3.lep_isTriggerSafe_v1(); }
const vector<int> &lep_lostHits() { return cms3.lep_lostHits(); }
const vector<int> &lep_convVeto() { return cms3.lep_convVeto(); }
const vector<int> &lep_motherIdSS() { return cms3.lep_motherIdSS(); }
const vector<int> &lep_pass_VVV_cutbased_3l_fo() { return cms3.lep_pass_VVV_cutbased_3l_fo(); }
const vector<int> &lep_pass_VVV_cutbased_3l_tight() { return cms3.lep_pass_VVV_cutbased_3l_tight(); }
const vector<int> &lep_pass_VVV_cutbased_fo() { return cms3.lep_pass_VVV_cutbased_fo(); }
const vector<int> &lep_pass_VVV_cutbased_tight() { return cms3.lep_pass_VVV_cutbased_tight(); }
const vector<int> &lep_pass_VVV_cutbased_veto() { return cms3.lep_pass_VVV_cutbased_veto(); }
const vector<int> &lep_pass_VVV_cutbased_fo_noiso() { return cms3.lep_pass_VVV_cutbased_fo_noiso(); }
const vector<int> &lep_pass_VVV_cutbased_tight_noiso() { return cms3.lep_pass_VVV_cutbased_tight_noiso(); }
const vector<int> &lep_pass_VVV_cutbased_veto_noiso() { return cms3.lep_pass_VVV_cutbased_veto_noiso(); }
const vector<int> &lep_pdgId() { return cms3.lep_pdgId(); }
const vector<float> &lep_dxy() { return cms3.lep_dxy(); }
const vector<float> &lep_dz() { return cms3.lep_dz(); }
const vector<float> &lep_ptRatio() { return cms3.lep_ptRatio(); }
const vector<float> &lep_ptRel() { return cms3.lep_ptRel(); }
const vector<float> &lep_pterr() { return cms3.lep_pterr(); }
const vector<float> &lep_relIso03EAv2() { return cms3.lep_relIso03EAv2(); }
const vector<float> &lep_relIso04EAv2() { return cms3.lep_relIso04EAv2(); }
const vector<int> &lep_tightCharge() { return cms3.lep_tightCharge(); }
const vector<float> &lep_trk_pt() { return cms3.lep_trk_pt(); }
const vector<int> &lep_charge() { return cms3.lep_charge(); }
const vector<float> &lep_etaSC() { return cms3.lep_etaSC(); }
const vector<float> &lep_MVA() { return cms3.lep_MVA(); }
const vector<int> &lep_isFromW() { return cms3.lep_isFromW(); }
const vector<int> &lep_isFromZ() { return cms3.lep_isFromZ(); }
const vector<int> &lep_isFromB() { return cms3.lep_isFromB(); }
const vector<int> &lep_isFromC() { return cms3.lep_isFromC(); }
const vector<int> &lep_isFromL() { return cms3.lep_isFromL(); }
const vector<int> &lep_isFromLF() { return cms3.lep_isFromLF(); }
const vector<int> &lep_genPart_index() { return cms3.lep_genPart_index(); }
const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &jets_p4() { return cms3.jets_p4(); }
const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &jets_up_p4() { return cms3.jets_up_p4(); }
const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &jets_dn_p4() { return cms3.jets_dn_p4(); }
const vector<float> &jets_csv() { return cms3.jets_csv(); }
const vector<float> &jets_up_csv() { return cms3.jets_up_csv(); }
const vector<float> &jets_dn_csv() { return cms3.jets_dn_csv(); }
const float &met_pt() { return cms3.met_pt(); }
const float &met_phi() { return cms3.met_phi(); }
const float &met_up_pt() { return cms3.met_up_pt(); }
const float &met_up_phi() { return cms3.met_up_phi(); }
const float &met_dn_pt() { return cms3.met_dn_pt(); }
const float &met_dn_phi() { return cms3.met_dn_phi(); }
const int &firstgoodvertex() { return cms3.firstgoodvertex(); }
const int &nTrueInt() { return cms3.nTrueInt(); }
const int &nVert() { return cms3.nVert(); }
const int &nisoTrack_mt2_cleaned_VVV_cutbased_veto() { return cms3.nisoTrack_mt2_cleaned_VVV_cutbased_veto(); }
const float &weight_btagsf() { return cms3.weight_btagsf(); }
const float &weight_btagsf_heavy_DN() { return cms3.weight_btagsf_heavy_DN(); }
const float &weight_btagsf_heavy_UP() { return cms3.weight_btagsf_heavy_UP(); }
const float &weight_btagsf_light_DN() { return cms3.weight_btagsf_light_DN(); }
const float &weight_btagsf_light_UP() { return cms3.weight_btagsf_light_UP(); }
const float &gen_ht() { return cms3.gen_ht(); }
const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genPart_p4() { return cms3.genPart_p4(); }
const vector<int> &genPart_motherId() { return cms3.genPart_motherId(); }
const vector<int> &genPart_pdgId() { return cms3.genPart_pdgId(); }
const vector<int> &genPart_charge() { return cms3.genPart_charge(); }
const vector<int> &genPart_status() { return cms3.genPart_status(); }
const int &ngenLep() { return cms3.ngenLep(); }
const int &ngenLepFromTau() { return cms3.ngenLepFromTau(); }
const int &Flag_AllEventFilters() { return cms3.Flag_AllEventFilters(); }
const int &Flag_EcalDeadCellTriggerPrimitiveFilter() { return cms3.Flag_EcalDeadCellTriggerPrimitiveFilter(); }
const int &Flag_HBHEIsoNoiseFilter() { return cms3.Flag_HBHEIsoNoiseFilter(); }
const int &Flag_HBHENoiseFilter() { return cms3.Flag_HBHENoiseFilter(); }
const int &Flag_badChargedCandidateFilter() { return cms3.Flag_badChargedCandidateFilter(); }
const int &Flag_badMuonFilter() { return cms3.Flag_badMuonFilter(); }
const int &Flag_eeBadScFilter() { return cms3.Flag_eeBadScFilter(); }
const int &Flag_globalTightHalo2016() { return cms3.Flag_globalTightHalo2016(); }
const int &Flag_goodVertices() { return cms3.Flag_goodVertices(); }
const int &nVlep() { return cms3.nVlep(); }
const int &nTlep() { return cms3.nTlep(); }
const int &nTlepSS() { return cms3.nTlepSS(); }
const int &nLlep() { return cms3.nLlep(); }
const int &nSFOS() { return cms3.nSFOS(); }
const int &nSFOSinZ() { return cms3.nSFOSinZ(); }
const int &nj() { return cms3.nj(); }
const int &nj_up() { return cms3.nj_up(); }
const int &nj_dn() { return cms3.nj_dn(); }
const int &nj30() { return cms3.nj30(); }
const int &nj30_up() { return cms3.nj30_up(); }
const int &nj30_dn() { return cms3.nj30_dn(); }
const int &nb() { return cms3.nb(); }
const int &nb_up() { return cms3.nb_up(); }
const int &nb_dn() { return cms3.nb_dn(); }
const float &Mjj() { return cms3.Mjj(); }
const float &Mjj_up() { return cms3.Mjj_up(); }
const float &Mjj_dn() { return cms3.Mjj_dn(); }
const float &MjjVBF() { return cms3.MjjVBF(); }
const float &MjjVBF_up() { return cms3.MjjVBF_up(); }
const float &MjjVBF_dn() { return cms3.MjjVBF_dn(); }
const float &DetajjVBF() { return cms3.DetajjVBF(); }
const float &DetajjVBF_up() { return cms3.DetajjVBF_up(); }
const float &DetajjVBF_dn() { return cms3.DetajjVBF_dn(); }
const float &MjjL() { return cms3.MjjL(); }
const float &MjjL_up() { return cms3.MjjL_up(); }
const float &MjjL_dn() { return cms3.MjjL_dn(); }
const float &DetajjL() { return cms3.DetajjL(); }
const float &DetajjL_up() { return cms3.DetajjL_up(); }
const float &DetajjL_dn() { return cms3.DetajjL_dn(); }
const float &MllSS() { return cms3.MllSS(); }
const float &MeeSS() { return cms3.MeeSS(); }
const float &Mll3L() { return cms3.Mll3L(); }
const float &Mee3L() { return cms3.Mee3L(); }
const float &Mll3L1() { return cms3.Mll3L1(); }
const float &M3l() { return cms3.M3l(); }
const float &Pt3l() { return cms3.Pt3l(); }
const float &M01() { return cms3.M01(); }
const float &M02() { return cms3.M02(); }
const float &M12() { return cms3.M12(); }
const int &isSFOS01() { return cms3.isSFOS01(); }
const int &isSFOS02() { return cms3.isSFOS02(); }
const int &isSFOS12() { return cms3.isSFOS12(); }
const float &DPhi3lMET() { return cms3.DPhi3lMET(); }
const float &DPhi3lMET_up() { return cms3.DPhi3lMET_up(); }
const float &DPhi3lMET_dn() { return cms3.DPhi3lMET_dn(); }
const float &MTmax() { return cms3.MTmax(); }
const float &MTmax_up() { return cms3.MTmax_up(); }
const float &MTmax_dn() { return cms3.MTmax_dn(); }
const float &MTmin() { return cms3.MTmin(); }
const float &MTmin_up() { return cms3.MTmin_up(); }
const float &MTmin_dn() { return cms3.MTmin_dn(); }
const float &MT3rd() { return cms3.MT3rd(); }
const float &MT3rd_up() { return cms3.MT3rd_up(); }
const float &MT3rd_dn() { return cms3.MT3rd_dn(); }
const int &passSSee() { return cms3.passSSee(); }
const int &passSSem() { return cms3.passSSem(); }
const int &passSSmm() { return cms3.passSSmm(); }
const int &lep_idx0_SS() { return cms3.lep_idx0_SS(); }
const int &lep_idx1_SS() { return cms3.lep_idx1_SS(); }
const TString &bkgtype() { return cms3.bkgtype(); }
const int &vetophoton() { return cms3.vetophoton(); }
const float &purewgt() { return cms3.purewgt(); }
const float &purewgt_up() { return cms3.purewgt_up(); }
const float &purewgt_dn() { return cms3.purewgt_dn(); }
const float &ffwgt() { return cms3.ffwgt(); }
const float &ffwgt_up() { return cms3.ffwgt_up(); }
const float &ffwgt_dn() { return cms3.ffwgt_dn(); }
const float &ffwgtqcd() { return cms3.ffwgtqcd(); }
const float &ffwgtqcd_up() { return cms3.ffwgtqcd_up(); }
const float &ffwgtqcd_dn() { return cms3.ffwgtqcd_dn(); }
const float &lepsf() { return cms3.lepsf(); }
const float &lepsf_up() { return cms3.lepsf_up(); }
const float &lepsf_dn() { return cms3.lepsf_dn(); }
const float &trigeff() { return cms3.trigeff(); }
const float &trigeff_up() { return cms3.trigeff_up(); }
const float &trigeff_dn() { return cms3.trigeff_dn(); }

}
