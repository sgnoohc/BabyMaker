float fakerate_mu_data_baseline_v2_3l(float eta, float conecorrpt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 1.2 && (conecorrpt) < 25.0) return 0.244734516779 + isyst * 0.00646433745585;
    if (fabs(eta) < 2.4 && (conecorrpt) < 25.0) return 0.242147987689 + isyst * 0.00834303100214;
    if (fabs(eta) < 1.2 && (conecorrpt) < 30.0) return 0.0868480104583 + isyst * 0.00499342559764;
    if (fabs(eta) < 2.4 && (conecorrpt) < 30.0) return 0.100762367904 + isyst * 0.00843461337542;
    if (fabs(eta) < 1.2 && (conecorrpt) < 40.0) return 0.0778880463631 + isyst * 0.00627667832541;
    if (fabs(eta) < 2.4 && (conecorrpt) < 40.0) return 0.0811342108435 + isyst * 0.00822277931437;
    if (fabs(eta) < 1.2) return 0.068483057353 + isyst * 0.0235030181406;
    if (fabs(eta) < 2.4) return 0.0752528931066 + isyst * 0.0313288425328;
    printf("WARNING in fakerate_mu_data_baseline_v2_3l(): the given phase-space (%f, %f) did not fall under any range!\n", eta, conecorrpt); 
    return 1;
}

float fakerate_el_data_baseline_v2_3l(float eta, float conecorrpt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 0.8 && (conecorrpt) < 25.0) return 0.27489101456 + isyst * 0.0146378225502;
    if (fabs(eta) < 1.479 && (conecorrpt) < 25.0) return 0.300329454357 + isyst * 0.0190002720764;
    if (fabs(eta) < 2.5 && (conecorrpt) < 25.0) return 0.371137244748 + isyst * 0.0321761639034;
    if (fabs(eta) < 0.8 && (conecorrpt) < 30.0) return 0.198792795632 + isyst * 0.0208392341493;
    if (fabs(eta) < 1.479 && (conecorrpt) < 30.0) return 0.239339131805 + isyst * 0.0310202392986;
    if (fabs(eta) < 2.5 && (conecorrpt) < 30.0) return 0.309382379503 + isyst * 0.0323417623284;
    if (fabs(eta) < 0.8 && (conecorrpt) < 40.0) return 0.155650044697 + isyst * 0.0237939755326;
    if (fabs(eta) < 1.479 && (conecorrpt) < 40.0) return 0.199204021739 + isyst * 0.0215428711387;
    if (fabs(eta) < 2.5 && (conecorrpt) < 40.0) return 0.32724960472 + isyst * 0.0436635274713;
    if (fabs(eta) < 0.8) return 0.158835589736 + isyst * 0.0474098527966;
    if (fabs(eta) < 1.479) return 0.168239854116 + isyst * 0.05327769103;
    if (fabs(eta) < 2.5) return 0.356281764666 + isyst * 0.0502555205048;
    printf("WARNING in fakerate_el_data_baseline_v2_3l(): the given phase-space (%f, %f) did not fall under any range!\n", eta, conecorrpt); 
    return 1;
}

float fakerate_mu_qcd_baseline_v2_3l(float eta, float conecorrpt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 1.2 && (conecorrpt) < 25.0) return 0.249061139432 + isyst * 0.00583624110216;
    if (fabs(eta) < 2.4 && (conecorrpt) < 25.0) return 0.251866015147 + isyst * 0.00799145824242;
    if (fabs(eta) < 1.2 && (conecorrpt) < 30.0) return 0.0860040773907 + isyst * 0.00992035063957;
    if (fabs(eta) < 2.4 && (conecorrpt) < 30.0) return 0.114024355344 + isyst * 0.0145211401579;
    if (fabs(eta) < 1.2 && (conecorrpt) < 40.0) return 0.0732653504129 + isyst * 0.00936438011248;
    if (fabs(eta) < 2.4 && (conecorrpt) < 40.0) return 0.0806026775827 + isyst * 0.0118852354524;
    if (fabs(eta) < 1.2) return 0.0624248715139 + isyst * 0.00860475528269;
    if (fabs(eta) < 2.4) return 0.0784512463568 + isyst * 0.010617327892;
    printf("WARNING in fakerate_mu_qcd_baseline_v2_3l(): the given phase-space (%f, %f) did not fall under any range!\n", eta, conecorrpt); 
    return 1;
}

float fakerate_el_qcd_baseline_v2_3l(float eta, float conecorrpt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 0.8 && (conecorrpt) < 25.0) return 0.284553304702 + isyst * 0.0190702988419;
    if (fabs(eta) < 1.479 && (conecorrpt) < 25.0) return 0.321108009434 + isyst * 0.0444281950532;
    if (fabs(eta) < 2.5 && (conecorrpt) < 25.0) return 0.387823007969 + isyst * 0.047962516899;
    if (fabs(eta) < 0.8 && (conecorrpt) < 30.0) return 0.248653054083 + isyst * 0.12009980394;
    if (fabs(eta) < 1.479 && (conecorrpt) < 30.0) return 0.136869587946 + isyst * 0.0333032519624;
    if (fabs(eta) < 2.5 && (conecorrpt) < 30.0) return 0.259694281377 + isyst * 0.0631180564791;
    if (fabs(eta) < 0.8 && (conecorrpt) < 40.0) return 0.386315741419 + isyst * 0.169922996876;
    if (fabs(eta) < 1.479 && (conecorrpt) < 40.0) return 0.345190828552 + isyst * 0.19696749582;
    if (fabs(eta) < 2.5 && (conecorrpt) < 40.0) return 0.290438464652 + isyst * 0.081296484161;
    if (fabs(eta) < 0.8) return 0.255181029113 + isyst * 0.051449911854;
    if (fabs(eta) < 1.479) return 0.284317944601 + isyst * 0.0552001769296;
    if (fabs(eta) < 2.5) return 0.457029356909 + isyst * 0.0781762516258;
    printf("WARNING in fakerate_el_qcd_baseline_v2_3l(): the given phase-space (%f, %f) did not fall under any range!\n", eta, conecorrpt); 
    return 1;
}

