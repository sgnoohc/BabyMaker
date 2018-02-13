float fakerate_mu_data_baseline_v2_ss(float eta, float conecorrpt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 1.2 && (conecorrpt) < 25.0) return 0.169317619951 + isyst * 0.0054925103234;
    if (fabs(eta) < 2.4 && (conecorrpt) < 25.0) return 0.163953990186 + isyst * 0.00645934452686;
    if (fabs(eta) < 1.2 && (conecorrpt) < 30.0) return 0.0338838209251 + isyst * 0.00301788199566;
    if (fabs(eta) < 2.4 && (conecorrpt) < 30.0) return 0.037248476634 + isyst * 0.00360805953026;
    if (fabs(eta) < 1.2 && (conecorrpt) < 40.0) return 0.0300719775511 + isyst * 0.00464951474228;
    if (fabs(eta) < 2.4 && (conecorrpt) < 40.0) return 0.0262802509278 + isyst * 0.005360471061;
    if (fabs(eta) < 1.2) return 0.0168722416722 + isyst * 0.0194158458789;
    if (fabs(eta) < 2.4) return 0.0120332592678 + isyst * 0.0257036581259;
    printf("WARNING in fakerate_mu_data_baseline_v2_ss(): the given phase-space (%f, %f) did not fall under any range!\n", eta, conecorrpt); 
    return 1;
}

float fakerate_el_data_baseline_v2_ss(float eta, float conecorrpt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 0.8 && (conecorrpt) < 25.0) return 0.187921014022 + isyst * 0.014917769843;
    if (fabs(eta) < 1.479 && (conecorrpt) < 25.0) return 0.198013897805 + isyst * 0.0195540071896;
    if (fabs(eta) < 2.5 && (conecorrpt) < 25.0) return 0.365232916327 + isyst * 0.0526323824742;
    if (fabs(eta) < 0.8 && (conecorrpt) < 30.0) return 0.0986215957675 + isyst * 0.0190298326879;
    if (fabs(eta) < 1.479 && (conecorrpt) < 30.0) return 0.162318827269 + isyst * 0.0224692394348;
    if (fabs(eta) < 2.5 && (conecorrpt) < 30.0) return 0.292185286121 + isyst * 0.0533888253703;
    if (fabs(eta) < 0.8 && (conecorrpt) < 40.0) return 0.0968410121335 + isyst * 0.035982040521;
    if (fabs(eta) < 1.479 && (conecorrpt) < 40.0) return 0.126788625959 + isyst * 0.0324039541698;
    if (fabs(eta) < 2.5 && (conecorrpt) < 40.0) return 0.294177860449 + isyst * 0.0572341409624;
    if (fabs(eta) < 0.8) return 0.153873255863 + isyst * 0.0749104268992;
    if (fabs(eta) < 1.479) return 0.117157170912 + isyst * 0.0912702061489;
    if (fabs(eta) < 2.5) return 0.316081506665 + isyst * 0.187984610738;
    printf("WARNING in fakerate_el_data_baseline_v2_ss(): the given phase-space (%f, %f) did not fall under any range!\n", eta, conecorrpt); 
    return 1;
}

float fakerate_mu_qcd_baseline_v2_ss(float eta, float conecorrpt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 1.2 && (conecorrpt) < 25.0) return 0.178683482664 + isyst * 0.00530445737933;
    if (fabs(eta) < 2.4 && (conecorrpt) < 25.0) return 0.178111333644 + isyst * 0.00722696148359;
    if (fabs(eta) < 1.2 && (conecorrpt) < 30.0) return 0.0330033408889 + isyst * 0.00608679289178;
    if (fabs(eta) < 2.4 && (conecorrpt) < 30.0) return 0.0420493513348 + isyst * 0.00877384293473;
    if (fabs(eta) < 1.2 && (conecorrpt) < 40.0) return 0.0254621332399 + isyst * 0.00475683347607;
    if (fabs(eta) < 2.4 && (conecorrpt) < 40.0) return 0.0265534438404 + isyst * 0.00577048666536;
    if (fabs(eta) < 1.2) return 0.0177846857627 + isyst * 0.00418254756346;
    if (fabs(eta) < 2.4) return 0.0241455984265 + isyst * 0.00494790616341;
    printf("WARNING in fakerate_mu_qcd_baseline_v2_ss(): the given phase-space (%f, %f) did not fall under any range!\n", eta, conecorrpt); 
    return 1;
}

float fakerate_el_qcd_baseline_v2_ss(float eta, float conecorrpt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 0.8 && (conecorrpt) < 25.0) return 0.210004813217 + isyst * 0.0234075703814;
    if (fabs(eta) < 1.479 && (conecorrpt) < 25.0) return 0.256020788315 + isyst * 0.0537672097095;
    if (fabs(eta) < 2.5 && (conecorrpt) < 25.0) return 0.492350034075 + isyst * 0.10127969104;
    if (fabs(eta) < 0.8 && (conecorrpt) < 30.0) return 0.207061074776 + isyst * 0.142684969708;
    if (fabs(eta) < 1.479 && (conecorrpt) < 30.0) return 0.0448491639015 + isyst * 0.0204622666622;
    if (fabs(eta) < 2.5 && (conecorrpt) < 30.0) return 0.214588769221 + isyst * 0.0571485635625;
    if (fabs(eta) < 0.8 && (conecorrpt) < 40.0) return 0.246737813025 + isyst * 0.14583860484;
    if (fabs(eta) < 1.479 && (conecorrpt) < 40.0) return 0.417990114792 + isyst * 0.291997902979;
    if (fabs(eta) < 2.5 && (conecorrpt) < 40.0) return 0.270954105673 + isyst * 0.137528283719;
    if (fabs(eta) < 0.8) return 0.11722545622 + isyst * 0.042931192921;
    if (fabs(eta) < 1.479) return 0.167658985254 + isyst * 0.0558607424022;
    if (fabs(eta) < 2.5) return 0.592090925696 + isyst * 0.178804170406;
    printf("WARNING in fakerate_el_qcd_baseline_v2_ss(): the given phase-space (%f, %f) did not fall under any range!\n", eta, conecorrpt); 
    return 1;
}

