#include "CMS3_WWW100.h"
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
  met_T1CHS_miniAOD_CORE_pt_branch = tree->GetBranch("met_T1CHS_miniAOD_CORE_pt");
  if (met_T1CHS_miniAOD_CORE_pt_branch) met_T1CHS_miniAOD_CORE_pt_branch->SetAddress(&met_T1CHS_miniAOD_CORE_pt_);
  met_T1CHS_miniAOD_CORE_phi_branch = tree->GetBranch("met_T1CHS_miniAOD_CORE_phi");
  if (met_T1CHS_miniAOD_CORE_phi_branch) met_T1CHS_miniAOD_CORE_phi_branch->SetAddress(&met_T1CHS_miniAOD_CORE_phi_);
  met_T1CHS_miniAOD_CORE_up_pt_branch = tree->GetBranch("met_T1CHS_miniAOD_CORE_up_pt");
  if (met_T1CHS_miniAOD_CORE_up_pt_branch) met_T1CHS_miniAOD_CORE_up_pt_branch->SetAddress(&met_T1CHS_miniAOD_CORE_up_pt_);
  met_T1CHS_miniAOD_CORE_up_phi_branch = tree->GetBranch("met_T1CHS_miniAOD_CORE_up_phi");
  if (met_T1CHS_miniAOD_CORE_up_phi_branch) met_T1CHS_miniAOD_CORE_up_phi_branch->SetAddress(&met_T1CHS_miniAOD_CORE_up_phi_);
  met_T1CHS_miniAOD_CORE_dn_pt_branch = tree->GetBranch("met_T1CHS_miniAOD_CORE_dn_pt");
  if (met_T1CHS_miniAOD_CORE_dn_pt_branch) met_T1CHS_miniAOD_CORE_dn_pt_branch->SetAddress(&met_T1CHS_miniAOD_CORE_dn_pt_);
  met_T1CHS_miniAOD_CORE_dn_phi_branch = tree->GetBranch("met_T1CHS_miniAOD_CORE_dn_phi");
  if (met_T1CHS_miniAOD_CORE_dn_phi_branch) met_T1CHS_miniAOD_CORE_dn_phi_branch->SetAddress(&met_T1CHS_miniAOD_CORE_dn_phi_);
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
  HLT_DoubleMu_isLoaded = false;
  HLT_DoubleEl_isLoaded = false;
  HLT_DoubleEl_DZ_isLoaded = false;
  HLT_DoubleEl_DZ_2_isLoaded = false;
  HLT_MuEG_isLoaded = false;
  lep_p4_isLoaded = false;
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
  met_T1CHS_miniAOD_CORE_pt_isLoaded = false;
  met_T1CHS_miniAOD_CORE_phi_isLoaded = false;
  met_T1CHS_miniAOD_CORE_up_pt_isLoaded = false;
  met_T1CHS_miniAOD_CORE_up_phi_isLoaded = false;
  met_T1CHS_miniAOD_CORE_dn_pt_isLoaded = false;
  met_T1CHS_miniAOD_CORE_dn_phi_isLoaded = false;
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
  Flag_EcalDeadCellTriggerPrimitiveFilter_isLoaded = false;
  Flag_HBHEIsoNoiseFilter_isLoaded = false;
  Flag_HBHENoiseFilter_isLoaded = false;
  Flag_badChargedCandidateFilter_isLoaded = false;
  Flag_badMuonFilter_isLoaded = false;
  Flag_eeBadScFilter_isLoaded = false;
  Flag_globalTightHalo2016_isLoaded = false;
  Flag_goodVertices_isLoaded = false;
}

void CMS3::LoadAllBranches() {
  // load all branches
  if (run_branch != 0) run();
  if (lumi_branch != 0) lumi();
  if (evt_branch != 0) evt();
  if (isData_branch != 0) isData();
  if (evt_scale1fb_branch != 0) evt_scale1fb();
  if (HLT_DoubleMu_branch != 0) HLT_DoubleMu();
  if (HLT_DoubleEl_branch != 0) HLT_DoubleEl();
  if (HLT_DoubleEl_DZ_branch != 0) HLT_DoubleEl_DZ();
  if (HLT_DoubleEl_DZ_2_branch != 0) HLT_DoubleEl_DZ_2();
  if (HLT_MuEG_branch != 0) HLT_MuEG();
  if (lep_p4_branch != 0) lep_p4();
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
  if (met_T1CHS_miniAOD_CORE_pt_branch != 0) met_T1CHS_miniAOD_CORE_pt();
  if (met_T1CHS_miniAOD_CORE_phi_branch != 0) met_T1CHS_miniAOD_CORE_phi();
  if (met_T1CHS_miniAOD_CORE_up_pt_branch != 0) met_T1CHS_miniAOD_CORE_up_pt();
  if (met_T1CHS_miniAOD_CORE_up_phi_branch != 0) met_T1CHS_miniAOD_CORE_up_phi();
  if (met_T1CHS_miniAOD_CORE_dn_pt_branch != 0) met_T1CHS_miniAOD_CORE_dn_pt();
  if (met_T1CHS_miniAOD_CORE_dn_phi_branch != 0) met_T1CHS_miniAOD_CORE_dn_phi();
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
  if (Flag_EcalDeadCellTriggerPrimitiveFilter_branch != 0) Flag_EcalDeadCellTriggerPrimitiveFilter();
  if (Flag_HBHEIsoNoiseFilter_branch != 0) Flag_HBHEIsoNoiseFilter();
  if (Flag_HBHENoiseFilter_branch != 0) Flag_HBHENoiseFilter();
  if (Flag_badChargedCandidateFilter_branch != 0) Flag_badChargedCandidateFilter();
  if (Flag_badMuonFilter_branch != 0) Flag_badMuonFilter();
  if (Flag_eeBadScFilter_branch != 0) Flag_eeBadScFilter();
  if (Flag_globalTightHalo2016_branch != 0) Flag_globalTightHalo2016();
  if (Flag_goodVertices_branch != 0) Flag_goodVertices();
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

const float &CMS3::met_T1CHS_miniAOD_CORE_pt() {
  if (not met_T1CHS_miniAOD_CORE_pt_isLoaded) {
    if (met_T1CHS_miniAOD_CORE_pt_branch != 0) {
      met_T1CHS_miniAOD_CORE_pt_branch->GetEntry(index);
    } else {
      printf("branch met_T1CHS_miniAOD_CORE_pt_branch does not exist!\n");
      exit(1);
    }
    met_T1CHS_miniAOD_CORE_pt_isLoaded = true;
  }
  return met_T1CHS_miniAOD_CORE_pt_;
}

const float &CMS3::met_T1CHS_miniAOD_CORE_phi() {
  if (not met_T1CHS_miniAOD_CORE_phi_isLoaded) {
    if (met_T1CHS_miniAOD_CORE_phi_branch != 0) {
      met_T1CHS_miniAOD_CORE_phi_branch->GetEntry(index);
    } else {
      printf("branch met_T1CHS_miniAOD_CORE_phi_branch does not exist!\n");
      exit(1);
    }
    met_T1CHS_miniAOD_CORE_phi_isLoaded = true;
  }
  return met_T1CHS_miniAOD_CORE_phi_;
}

const float &CMS3::met_T1CHS_miniAOD_CORE_up_pt() {
  if (not met_T1CHS_miniAOD_CORE_up_pt_isLoaded) {
    if (met_T1CHS_miniAOD_CORE_up_pt_branch != 0) {
      met_T1CHS_miniAOD_CORE_up_pt_branch->GetEntry(index);
    } else {
      printf("branch met_T1CHS_miniAOD_CORE_up_pt_branch does not exist!\n");
      exit(1);
    }
    met_T1CHS_miniAOD_CORE_up_pt_isLoaded = true;
  }
  return met_T1CHS_miniAOD_CORE_up_pt_;
}

const float &CMS3::met_T1CHS_miniAOD_CORE_up_phi() {
  if (not met_T1CHS_miniAOD_CORE_up_phi_isLoaded) {
    if (met_T1CHS_miniAOD_CORE_up_phi_branch != 0) {
      met_T1CHS_miniAOD_CORE_up_phi_branch->GetEntry(index);
    } else {
      printf("branch met_T1CHS_miniAOD_CORE_up_phi_branch does not exist!\n");
      exit(1);
    }
    met_T1CHS_miniAOD_CORE_up_phi_isLoaded = true;
  }
  return met_T1CHS_miniAOD_CORE_up_phi_;
}

const float &CMS3::met_T1CHS_miniAOD_CORE_dn_pt() {
  if (not met_T1CHS_miniAOD_CORE_dn_pt_isLoaded) {
    if (met_T1CHS_miniAOD_CORE_dn_pt_branch != 0) {
      met_T1CHS_miniAOD_CORE_dn_pt_branch->GetEntry(index);
    } else {
      printf("branch met_T1CHS_miniAOD_CORE_dn_pt_branch does not exist!\n");
      exit(1);
    }
    met_T1CHS_miniAOD_CORE_dn_pt_isLoaded = true;
  }
  return met_T1CHS_miniAOD_CORE_dn_pt_;
}

const float &CMS3::met_T1CHS_miniAOD_CORE_dn_phi() {
  if (not met_T1CHS_miniAOD_CORE_dn_phi_isLoaded) {
    if (met_T1CHS_miniAOD_CORE_dn_phi_branch != 0) {
      met_T1CHS_miniAOD_CORE_dn_phi_branch->GetEntry(index);
    } else {
      printf("branch met_T1CHS_miniAOD_CORE_dn_phi_branch does not exist!\n");
      exit(1);
    }
    met_T1CHS_miniAOD_CORE_dn_phi_isLoaded = true;
  }
  return met_T1CHS_miniAOD_CORE_dn_phi_;
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
const int &HLT_DoubleMu() { return cms3.HLT_DoubleMu(); }
const int &HLT_DoubleEl() { return cms3.HLT_DoubleEl(); }
const int &HLT_DoubleEl_DZ() { return cms3.HLT_DoubleEl_DZ(); }
const int &HLT_DoubleEl_DZ_2() { return cms3.HLT_DoubleEl_DZ_2(); }
const int &HLT_MuEG() { return cms3.HLT_MuEG(); }
const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &lep_p4() { return cms3.lep_p4(); }
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
const float &met_T1CHS_miniAOD_CORE_pt() { return cms3.met_T1CHS_miniAOD_CORE_pt(); }
const float &met_T1CHS_miniAOD_CORE_phi() { return cms3.met_T1CHS_miniAOD_CORE_phi(); }
const float &met_T1CHS_miniAOD_CORE_up_pt() { return cms3.met_T1CHS_miniAOD_CORE_up_pt(); }
const float &met_T1CHS_miniAOD_CORE_up_phi() { return cms3.met_T1CHS_miniAOD_CORE_up_phi(); }
const float &met_T1CHS_miniAOD_CORE_dn_pt() { return cms3.met_T1CHS_miniAOD_CORE_dn_pt(); }
const float &met_T1CHS_miniAOD_CORE_dn_phi() { return cms3.met_T1CHS_miniAOD_CORE_dn_phi(); }
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
const int &Flag_EcalDeadCellTriggerPrimitiveFilter() { return cms3.Flag_EcalDeadCellTriggerPrimitiveFilter(); }
const int &Flag_HBHEIsoNoiseFilter() { return cms3.Flag_HBHEIsoNoiseFilter(); }
const int &Flag_HBHENoiseFilter() { return cms3.Flag_HBHENoiseFilter(); }
const int &Flag_badChargedCandidateFilter() { return cms3.Flag_badChargedCandidateFilter(); }
const int &Flag_badMuonFilter() { return cms3.Flag_badMuonFilter(); }
const int &Flag_eeBadScFilter() { return cms3.Flag_eeBadScFilter(); }
const int &Flag_globalTightHalo2016() { return cms3.Flag_globalTightHalo2016(); }
const int &Flag_goodVertices() { return cms3.Flag_goodVertices(); }

}
