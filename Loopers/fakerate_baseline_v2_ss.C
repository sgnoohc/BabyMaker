float fakerate_mu_data_baseline_v2_ss(float eta, float conecorrpt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 1.2 && (conecorrpt) < 25.0) return 0.144734833425 + isyst * 0.00464373629147;
    if (fabs(eta) < 2.4 && (conecorrpt) < 25.0) return 0.14079942167 + isyst * 0.00549214966681;
    if (fabs(eta) < 1.2 && (conecorrpt) < 30.0) return 0.0324084142155 + isyst * 0.00267152942685;
    if (fabs(eta) < 2.4 && (conecorrpt) < 30.0) return 0.0355778913803 + isyst * 0.00327692741091;
    if (fabs(eta) < 1.2 && (conecorrpt) < 40.0) return 0.0283656545607 + isyst * 0.00374189588221;
    if (fabs(eta) < 2.4 && (conecorrpt) < 40.0) return 0.0247538518695 + isyst * 0.00450254680118;
    if (fabs(eta) < 1.2) return 0.0129093908632 + isyst * 0.0131033033755;
    if (fabs(eta) < 2.4) return 0.00454171488189 + isyst * 0.0183026955862;
    return 1;
}

float fakerate_el_data_baseline_v2_ss(float eta, float conecorrpt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 0.8 && (conecorrpt) < 25.0) return 0.157581132467 + isyst * 0.0123611328606;
    if (fabs(eta) < 1.479 && (conecorrpt) < 25.0) return 0.164755965653 + isyst * 0.0160990977293;
    if (fabs(eta) < 2.5 && (conecorrpt) < 25.0) return 0.266689350008 + isyst * 0.0373626332249;
    if (fabs(eta) < 0.8 && (conecorrpt) < 30.0) return 0.0859117526322 + isyst * 0.0151036257529;
    if (fabs(eta) < 1.479 && (conecorrpt) < 30.0) return 0.137524132281 + isyst * 0.0178829859229;
    if (fabs(eta) < 2.5 && (conecorrpt) < 30.0) return 0.223400701523 + isyst * 0.0369328473213;
    if (fabs(eta) < 0.8 && (conecorrpt) < 40.0) return 0.0773768674578 + isyst * 0.0228134585964;
    if (fabs(eta) < 1.479 && (conecorrpt) < 40.0) return 0.104311493729 + isyst * 0.0221161032716;
    if (fabs(eta) < 2.5 && (conecorrpt) < 40.0) return 0.218705483607 + isyst * 0.0362627677976;
    if (fabs(eta) < 0.8) return 0.0980771357515 + isyst * 0.0444644095643;
    if (fabs(eta) < 1.479) return 0.067588243779 + isyst * 0.0573208796639;
    if (fabs(eta) < 2.5) return 0.163473635501 + isyst * 0.1006274755;
    return 1;
}

float fakerate_mu_qcd_baseline_v2_ss(float eta, float conecorrpt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 1.2 && (conecorrpt) < 25.0) return 0.151595814709 + isyst * 0.00443797571911;
    if (fabs(eta) < 2.4 && (conecorrpt) < 25.0) return 0.151183787474 + isyst * 0.00607411259164;
    if (fabs(eta) < 1.2 && (conecorrpt) < 30.0) return 0.0319489198218 + isyst * 0.00588922411516;
    if (fabs(eta) < 2.4 && (conecorrpt) < 30.0) return 0.0403525529759 + isyst * 0.00841355517266;
    if (fabs(eta) < 1.2 && (conecorrpt) < 40.0) return 0.0248299109534 + isyst * 0.004636986865;
    if (fabs(eta) < 2.4 && (conecorrpt) < 40.0) return 0.0258665965376 + isyst * 0.00561841909059;
    if (fabs(eta) < 1.2) return 0.0175047462223 + isyst * 0.00412966237618;
    if (fabs(eta) < 2.4) return 0.0236358787966 + isyst * 0.00484498986623;
    return 1;
}

float fakerate_el_qcd_baseline_v2_ss(float eta, float conecorrpt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 0.8 && (conecorrpt) < 25.0) return 0.173557006585 + isyst * 0.0194858305877;
    if (fabs(eta) < 1.479 && (conecorrpt) < 25.0) return 0.2038348358 + isyst * 0.0429820235612;
    if (fabs(eta) < 2.5 && (conecorrpt) < 25.0) return 0.330413832261 + isyst * 0.0709808894049;
    if (fabs(eta) < 0.8 && (conecorrpt) < 30.0) return 0.171541510379 + isyst * 0.119551404186;
    if (fabs(eta) < 1.479 && (conecorrpt) < 30.0) return 0.0429240548374 + isyst * 0.0193052058644;
    if (fabs(eta) < 2.5 && (conecorrpt) < 30.0) return 0.176676068286 + isyst * 0.0461181660889;
    if (fabs(eta) < 0.8 && (conecorrpt) < 40.0) return 0.197906740377 + isyst * 0.117240094625;
    if (fabs(eta) < 1.479 && (conecorrpt) < 40.0) return 0.294776463336 + isyst * 0.213849609416;
    if (fabs(eta) < 2.5 && (conecorrpt) < 40.0) return 0.213189526291 + isyst * 0.100181560808;
    if (fabs(eta) < 0.8) return 0.105332147821 + isyst * 0.0387290256625;
    if (fabs(eta) < 1.479) return 0.143286523667 + isyst * 0.0479787102666;
    if (fabs(eta) < 2.5) return 0.37044553671 + isyst * 0.109950809913;
    return 1;
}

