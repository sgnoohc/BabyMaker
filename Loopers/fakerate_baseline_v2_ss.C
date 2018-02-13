float fakerate_mu_data_baseline_v2_ss(float eta, float conecorrpt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 1.2 && (conecorrpt) < 25.0) return 0.169228023174 + isyst * 0.00549301472379;
    if (fabs(eta) < 2.4 && (conecorrpt) < 25.0) return 0.163872587171 + isyst * 0.00645986120503;
    if (fabs(eta) < 1.2 && (conecorrpt) < 30.0) return 0.0334938982993 + isyst * 0.00303350404945;
    if (fabs(eta) < 2.4 && (conecorrpt) < 30.0) return 0.0368903730506 + isyst * 0.00362097946117;
    if (fabs(eta) < 1.2 && (conecorrpt) < 40.0) return 0.0291937544677 + isyst * 0.00470454125375;
    if (fabs(eta) < 2.4 && (conecorrpt) < 40.0) return 0.0253821579617 + isyst * 0.00541823527823;
    if (fabs(eta) < 1.2) return 0.0126176695022 + isyst * 0.0197352836448;
    if (fabs(eta) < 2.4) return 0.00649635310947 + isyst * 0.0261386781647;
    printf("WARNING in fakerate_mu_data_baseline_v2_ss(): the given phase-space (%f, %f) did not fall under any range!\n", eta, conecorrpt); 
    return 1;
}

float fakerate_el_data_baseline_v2_ss(float eta, float conecorrpt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 0.8 && (conecorrpt) < 25.0) return 0.186702304994 + isyst * 0.01492624225;
    if (fabs(eta) < 1.479 && (conecorrpt) < 25.0) return 0.196942176669 + isyst * 0.0195563485884;
    if (fabs(eta) < 2.5 && (conecorrpt) < 25.0) return 0.362611476331 + isyst * 0.0526095408078;
    if (fabs(eta) < 0.8 && (conecorrpt) < 30.0) return 0.0920733629514 + isyst * 0.0191844457123;
    if (fabs(eta) < 1.479 && (conecorrpt) < 30.0) return 0.158270800914 + isyst * 0.0224010099377;
    if (fabs(eta) < 2.5 && (conecorrpt) < 30.0) return 0.283555475043 + isyst * 0.0530217160141;
    if (fabs(eta) < 0.8 && (conecorrpt) < 40.0) return 0.078498452363 + isyst * 0.0372709491084;
    if (fabs(eta) < 1.479 && (conecorrpt) < 40.0) return 0.112191275951 + isyst * 0.0332590025866;
    if (fabs(eta) < 2.5 && (conecorrpt) < 40.0) return 0.272180455401 + isyst * 0.058095170507;
    if (fabs(eta) < 0.8) return 0.108203638965 + isyst * 0.0780099634525;
    if (fabs(eta) < 1.479) return 0.0627882272048 + isyst * 0.0951380915649;
    if (fabs(eta) < 2.5) return 0.210253866261 + isyst * 0.195635136388;
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

