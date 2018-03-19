#ifndef fakerate_baseline_v2_ss_c
#define fakerate_baseline_v2_ss_c

float fakerate_mu_data_baseline_v2_ss(float eta, float conecorrpt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 1.2 && (conecorrpt) < 25.0) return 0.144791593964 + isyst * 0.00476943572422;
    if (fabs(eta) < 2.4 && (conecorrpt) < 25.0) return 0.140851718457 + isyst * 0.0061644051874;
    if (fabs(eta) < 1.2 && (conecorrpt) < 30.0) return 0.0327317620745 + isyst * 0.00411394866624;
    if (fabs(eta) < 2.4 && (conecorrpt) < 30.0) return 0.0358703986741 + isyst * 0.00428475108121;
    if (fabs(eta) < 1.2 && (conecorrpt) < 40.0) return 0.0290808346112 + isyst * 0.00501414284997;
    if (fabs(eta) < 2.4 && (conecorrpt) < 40.0) return 0.0255040833863 + isyst * 0.00618750546868;
    if (fabs(eta) < 1.2) return 0.0159792974828 + isyst * 0.018470009613;
    if (fabs(eta) < 2.4) return 0.0110645680514 + isyst * 0.0238443697013;
    printf("WARNING in fakerate_mu_data_baseline_v2_ss(): the given phase-space (%f, %f) did not fall under any range!\n", eta, conecorrpt); 
    return 1;
}

float fakerate_el_data_baseline_v2_ss(float eta, float conecorrpt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 0.8 && (conecorrpt) < 25.0) return 0.20559565418 + isyst * 0.0177903964137;
    if (fabs(eta) < 1.479 && (conecorrpt) < 25.0) return 0.193009062388 + isyst * 0.0210069837509;
    if (fabs(eta) < 2.5 && (conecorrpt) < 25.0) return 0.125886392077 + isyst * 0.0418977433369;
    if (fabs(eta) < 0.8 && (conecorrpt) < 30.0) return 0.0869654359214 + isyst * 0.0169752942807;
    if (fabs(eta) < 1.479 && (conecorrpt) < 30.0) return 0.104070788238 + isyst * 0.0256062872415;
    if (fabs(eta) < 2.5 && (conecorrpt) < 30.0) return 0.0762181811446 + isyst * 0.0312119790803;
    if (fabs(eta) < 0.8 && (conecorrpt) < 40.0) return 0.0793201053799 + isyst * 0.0237585108574;
    if (fabs(eta) < 1.479 && (conecorrpt) < 40.0) return 0.0961894023167 + isyst * 0.020034776666;
    if (fabs(eta) < 2.5 && (conecorrpt) < 40.0) return 0.0806949268321 + isyst * 0.0364790551322;
    if (fabs(eta) < 0.8) return 0.136025516951 + isyst * 0.0448171630306;
    if (fabs(eta) < 1.479) return 0.056843098333 + isyst * 0.0702829782833;
    if (fabs(eta) < 2.5) return 0.056843098333 + isyst * 0.0702829782833;
    printf("WARNING in fakerate_el_data_baseline_v2_ss(): the given phase-space (%f, %f) did not fall under any range!\n", eta, conecorrpt); 
    return 1;
}

float fakerate_mu_qcd_baseline_v2_ss(float eta, float conecorrpt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 1.2 && (conecorrpt) < 25.0) return 0.151603015448 + isyst * 0.00443821296913;
    if (fabs(eta) < 2.4 && (conecorrpt) < 25.0) return 0.151250495424 + isyst * 0.00607431629151;
    if (fabs(eta) < 1.2 && (conecorrpt) < 30.0) return 0.0319489197978 + isyst * 0.00588922413875;
    if (fabs(eta) < 2.4 && (conecorrpt) < 30.0) return 0.0403525526703 + isyst * 0.00841355501558;
    if (fabs(eta) < 1.2 && (conecorrpt) < 40.0) return 0.0248306714444 + isyst * 0.00463713261602;
    if (fabs(eta) < 2.4 && (conecorrpt) < 40.0) return 0.0258665966197 + isyst * 0.00561841912865;
    if (fabs(eta) < 1.2) return 0.0174737630596 + isyst * 0.00410879210766;
    if (fabs(eta) < 2.4) return 0.0235763337397 + isyst * 0.00482829399556;
    printf("WARNING in fakerate_mu_qcd_baseline_v2_ss(): the given phase-space (%f, %f) did not fall under any range!\n", eta, conecorrpt); 
    return 1;
}

float fakerate_el_qcd_baseline_v2_ss(float eta, float conecorrpt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 0.8 && (conecorrpt) < 25.0) return 0.181594339908 + isyst * 0.0166754498393;
    if (fabs(eta) < 1.479 && (conecorrpt) < 25.0) return 0.21537788862 + isyst * 0.0508638753184;
    if (fabs(eta) < 2.5 && (conecorrpt) < 25.0) return 0.0833039240091 + isyst * 0.0126312775914;
    if (fabs(eta) < 0.8 && (conecorrpt) < 30.0) return 0.174013045959 + isyst * 0.111685052104;
    if (fabs(eta) < 1.479 && (conecorrpt) < 30.0) return 0.0619223389998 + isyst * 0.0260189653869;
    if (fabs(eta) < 2.5 && (conecorrpt) < 30.0) return 0.0534091217526 + isyst * 0.0276370191365;
    if (fabs(eta) < 0.8 && (conecorrpt) < 40.0) return 0.194267131496 + isyst * 0.112991029629;
    if (fabs(eta) < 1.479 && (conecorrpt) < 40.0) return 0.0477807607205 + isyst * 0.0182440330471;
    if (fabs(eta) < 2.5 && (conecorrpt) < 40.0) return 0.0950319968116 + isyst * 0.0756436376699;
    if (fabs(eta) < 0.8) return 0.138802534906 + isyst * 0.0418502147103;
    if (fabs(eta) < 1.479) return 0.169077659148 + isyst * 0.0531864877235;
    if (fabs(eta) < 2.5) return 0.162745067281 + isyst * 0.0672194347459;
    printf("WARNING in fakerate_el_qcd_baseline_v2_ss(): the given phase-space (%f, %f) did not fall under any range!\n", eta, conecorrpt); 
    return 1;
}


#endif
