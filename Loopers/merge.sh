#!/bin/bash

if [ -z $1 ]; then
    echo "error - must provide the path to the minibabies."
    exit
fi

# removing duplicate data events and copying to the directory
python rooutil/duplicate.py --run run_number --evt event_number --lumi lumiblock_number $1/data_Run2016*_ee_* $1/data_Run2016*_em_* $1/data_Run2016*_mm_*;
cp output.root $1/data.root
rm output.root

# Following script prints out only the background samples
FILES=""
for i in $(cat qscripts/samples.cfg  | grep -v data | grep -v sig | grep -v \# | grep -v -e '^$' | grep -v SampleID | grep -v bkg\ | grep -v wz_1 | grep -v wz_3 | grep -v wz_l | awk '$5==1 {print $1}' | head -n -6); do
    FILES=$FILES" "$1/${i}.root
done
echo $FILES

hadd -f bkg.root $1/ttbar_1ltbr_mgmlm_ext1_skim_1.root $1/ttbar_1ltbr_mgmlm_ext1_skim_2.root $1/ttbar_1ltbr_mgmlm_ext1_skim_3.root $1/ttbar_1ltbr_mgmlm_ext1_skim_4.root $1/ttbar_1ltbr_mgmlm_ext1_skim_5.root $1/ttbar_1ltbr_mgmlm_ext1_skim_6.root $1/ttbar_1ltbr_mgmlm_ext1_skim_7.root $1/ttbar_1ltbr_mgmlm_ext1_skim_8.root $1/ttbar_1ltbr_mgmlm_ext1_skim_9.root $1/ttbar_1ltop_mgmlm_ext1_skim_1.root $1/ttbar_1ltop_mgmlm_ext1_skim_2.root $1/ttbar_1ltop_mgmlm_ext1_skim_3.root $1/ttbar_1ltop_mgmlm_ext1_skim_4.root $1/ttbar_1ltop_mgmlm_ext1_skim_5.root $1/ttbar_1ltop_mgmlm_ext1_skim_6.root $1/ttbar_1ltop_mgmlm_ext1_skim_7.root $1/ttbar_1ltop_mgmlm_ext1_skim_8.root $1/ttbar_1ltop_mgmlm_ext1_skim_9.root $1/ttbar_dilep_mgmlm_ext1_skim_1.root $1/ttbar_dilep_mgmlm_ext1_skim_2.root $1/ttbar_dilep_mgmlm_ext1_skim_3.root $1/ttbar_dilep_mgmlm_ext1_skim_4.root $1/ttbar_dilep_mgmlm_ext1_skim_5.root $1/ttbar_dilep_mgmlm_ext1_skim_6.root $1/ttbar_dilep_mgmlm_ext1_skim_7.root $1/sts_4f_leptonic_amcnlo_skim_1.root $1/stt_antitop_incdec_powheg_skim_1.root $1/stt_antitop_incdec_powheg_skim_2.root $1/stt_top_incdec_powheg_skim_1.root $1/stt_top_incdec_powheg_skim_2.root $1/sttw_antitop_nofullhaddecay_powheg_skim_1.root $1/sttw_top_nofullhaddecay_powheg_skim_1.root $1/sttwll_madgraph_skim_1.root $1/tzq_ll_amcnlo_skim_1.root $1/tzq_ll_amcnlo_skim_2.root $1/tzq_ll_amcnlo_skim_3.root $1/tzq_ll_amcnlo_skim_4.root $1/tzq_ll_amcnlo_skim_5.root $1/tzq_ll_amcnlo_skim_6.root $1/tzq_ll_amcnlo_skim_7.root $1/ttg_incl_amcnlo_skim_1.root $1/tth_bb_powheg_skim_1.root $1/tth_bb_powheg_skim_2.root $1/tth_nonbb_powheg_skim_1.root $1/tth_nonbb_powheg_skim_2.root $1/ttw_incl_mgmlm_skim_1.root $1/ttw_incl_mgmlm_skim_2.root $1/ttz_incl_mgmlm_skim_1.root $1/ttz_incl_mgmlm_skim_2.root $1/ttz_incl_mgmlm_skim_3.root $1/ttz_incl_mgmlm_skim_4.root $1/wwg_incl_amcnlo_skim_1.root $1/wzg_incl_amcnlo_skim_1.root $1/wwz_incl_amcnlo_skim_1.root $1/wzz_incl_amcnlo_skim_1.root $1/zzz_incl_amcnlo_skim_1.root $1/vh_nonbb_amcnlo_skim_1.root $1/wjets_ht100_mgmlm_ext1_skim_1.root $1/wjets_ht200_mgmlm_ext1_skim_1.root $1/wjets_ht400_mgmlm_ext1_skim_1.root $1/wjets_ht600_mgmlm_ext1_skim_1.root $1/wjets_ht800_mgmlm_ext1_skim_1.root $1/wjets_ht1200_mgmlm_nonext_skim_1.root $1/wjets_ht2500_mgmlm_ext1_skim_1.root $1/wjets_incl_mgmlm_skim_1.root $1/Wmjj_lnu_madgraph_skim_1.root $1/Wpjj_lnu_madgraph_skim_1.root $1/dy_m1050_mgmlm_skim_1.root $1/dy_m50_mgmlm_ext1_skim_1.root $1/dy_m50_mgmlm_ht100_ext1_skim_1.root $1/dy_m50_mgmlm_ht200_ext1_skim_1.root $1/dy_m50_mgmlm_ht400_ext1_skim_1.root $1/dy_m50_mgmlm_ht600_nonext_skim_1.root $1/dy_m50_mgmlm_ht600_nonext_skim_2.root $1/dy_m50_mgmlm_ht800_nonext_skim_1.root $1/dy_m50_mgmlm_ht1200_nonext_skim_1.root $1/dy_m50_mgmlm_ht2500_nonext_skim_1.root $1/Zjj_m50_madgraph_skim_1.root $1/wpwpjj_ewk-qcd_madgraph_skim_1.root $1/ww_2l2nu_dbl_scat_skim_1.root $1/ww_2l2nu_powheg_skim_1.root $1/ww_lnuqq_powheg_skim_1.root $1/zz_2l2n_powheg_skim_1.root $1/zz_2l2q_powheg_skim_1.root $1/zz_2q2n_amcnlo_skim_1.root $1/zz_4l_powheg_skim_1.root $1/zz_4l_powheg_skim_2.root $1/wgjets_incl_mgmlm_skim_1.root $1/zgamma_2lG_amc_skim_1.root $1/wgstar_lnee_012jets_madgraph_skim_1.root $1/wgstar_lnmm_012jets_madgraph_skim_1.root
cp bkg.root $1/bkg.root
rm bkg.root

hadd -f wz.root $1/wz_1l3n_amcnlo_skim_1.root $1/wz_3lnu_powheg_skim_1.root $1/wz_lnqq_amcnlo_skim_1.root
cp wz.root $1/wz.root
rm wz.root
