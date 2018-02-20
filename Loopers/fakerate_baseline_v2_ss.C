float fakerate_mu_data_baseline_v2_ss(float eta, float conecorrpt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 1.2 && (conecorrpt) < 25.0) return 0.144792459715 + isyst * 0.00476952533699;
    if (fabs(eta) < 2.4 && (conecorrpt) < 25.0) return 0.140852397509 + isyst * 0.00616446933643;
    if (fabs(eta) < 1.2 && (conecorrpt) < 30.0) return 0.0327313403425 + isyst * 0.00411559947059;
    if (fabs(eta) < 2.4 && (conecorrpt) < 30.0) return 0.0358732333746 + isyst * 0.00428458716022;
    if (fabs(eta) < 1.2 && (conecorrpt) < 40.0) return 0.0290996366605 + isyst * 0.0050111396407;
    if (fabs(eta) < 2.4 && (conecorrpt) < 40.0) return 0.0255106208025 + isyst * 0.00618689681445;
    if (fabs(eta) < 1.2) return 0.0161229892556 + isyst * 0.0184628932709;
    if (fabs(eta) < 2.4) return 0.0112787297598 + isyst * 0.0236908601572;
    printf("WARNING in fakerate_mu_data_baseline_v2_ss(): the given phase-space (%f, %f) did not fall under any range!\n", eta, conecorrpt); 
    return 1;
}

float fakerate_el_data_baseline_v2_ss(float eta, float conecorrpt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 0.8 && (conecorrpt) < 25.0) return 0.157955002957 + isyst * 0.0126560687805;
    if (fabs(eta) < 1.479 && (conecorrpt) < 25.0) return 0.165042650401 + isyst * 0.0198631668033;
    if (fabs(eta) < 2.5 && (conecorrpt) < 25.0) return 0.268290988561 + isyst * 0.042920219621;
    if (fabs(eta) < 0.8 && (conecorrpt) < 30.0) return 0.0886684091472 + isyst * 0.0179478785166;
    if (fabs(eta) < 1.479 && (conecorrpt) < 30.0) return 0.13813708302 + isyst * 0.0339723681191;
    if (fabs(eta) < 2.5 && (conecorrpt) < 30.0) return 0.22427971696 + isyst * 0.0422864409702;
    if (fabs(eta) < 0.8 && (conecorrpt) < 40.0) return 0.0861858268013 + isyst * 0.0199501880553;
    if (fabs(eta) < 1.479 && (conecorrpt) < 40.0) return 0.110414369136 + isyst * 0.0205330447887;
    if (fabs(eta) < 2.5 && (conecorrpt) < 40.0) return 0.225226310161 + isyst * 0.0496776666724;
    if (fabs(eta) < 0.8) return 0.126608930685 + isyst * 0.0354255002482;
    if (fabs(eta) < 1.479) return 0.0913712582353 + isyst * 0.0478883794177;
    if (fabs(eta) < 2.5) return 0.228129817315 + isyst * 0.0925515215435;
    printf("WARNING in fakerate_el_data_baseline_v2_ss(): the given phase-space (%f, %f) did not fall under any range!\n", eta, conecorrpt); 
    return 1;
}

float fakerate_mu_qcd_baseline_v2_ss(float eta, float conecorrpt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 1.2 && (conecorrpt) < 25.0) return 0.151593184848 + isyst * 0.00443788851401;
    if (fabs(eta) < 2.4 && (conecorrpt) < 25.0) return 0.151183787608 + isyst * 0.00607411261847;
    if (fabs(eta) < 1.2 && (conecorrpt) < 30.0) return 0.0319489197978 + isyst * 0.00588922413875;
    if (fabs(eta) < 2.4 && (conecorrpt) < 30.0) return 0.0403525526703 + isyst * 0.00841355501558;
    if (fabs(eta) < 1.2 && (conecorrpt) < 40.0) return 0.0248299107442 + isyst * 0.00463698681776;
    if (fabs(eta) < 2.4 && (conecorrpt) < 40.0) return 0.0258665966197 + isyst * 0.00561841912865;
    if (fabs(eta) < 1.2) return 0.0174739176286 + isyst * 0.00410882907713;
    if (fabs(eta) < 2.4) return 0.0235763337397 + isyst * 0.00482829399556;
    printf("WARNING in fakerate_mu_qcd_baseline_v2_ss(): the given phase-space (%f, %f) did not fall under any range!\n", eta, conecorrpt); 
    return 1;
}

float fakerate_el_qcd_baseline_v2_ss(float eta, float conecorrpt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 0.8 && (conecorrpt) < 25.0) return 0.173538395796 + isyst * 0.0195187419507;
    if (fabs(eta) < 1.479 && (conecorrpt) < 25.0) return 0.20399513303 + isyst * 0.04301942411;
    if (fabs(eta) < 2.5 && (conecorrpt) < 25.0) return 0.330239955239 + isyst * 0.0711886005921;
    if (fabs(eta) < 0.8 && (conecorrpt) < 30.0) return 0.17196800558 + isyst * 0.119951409182;
    if (fabs(eta) < 1.479 && (conecorrpt) < 30.0) return 0.0429979250995 + isyst * 0.019370597834;
    if (fabs(eta) < 2.5 && (conecorrpt) < 30.0) return 0.176727860012 + isyst * 0.0464791905895;
    if (fabs(eta) < 0.8 && (conecorrpt) < 40.0) return 0.19922515673 + isyst * 0.118133166054;
    if (fabs(eta) < 1.479 && (conecorrpt) < 40.0) return 0.297556639308 + isyst * 0.216052619842;
    if (fabs(eta) < 2.5 && (conecorrpt) < 40.0) return 0.213644107614 + isyst * 0.100469602852;
    if (fabs(eta) < 0.8) return 0.105843858734 + isyst * 0.0388205989044;
    if (fabs(eta) < 1.479) return 0.145006245287 + isyst * 0.0483756193883;
    if (fabs(eta) < 2.5) return 0.379901185646 + isyst * 0.112434942291;
    printf("WARNING in fakerate_el_qcd_baseline_v2_ss(): the given phase-space (%f, %f) did not fall under any range!\n", eta, conecorrpt); 
    return 1;
}

