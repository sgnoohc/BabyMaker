#ifndef fakerate_baseline_v2_3l_c
#define fakerate_baseline_v2_3l_c

float fakerate_mu_data_baseline_v2_3l(float eta, float conecorrpt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 1.2 && (conecorrpt) < 25.0) return 0.244737028146 + isyst * 0.0064642772297;
    if (fabs(eta) < 2.4 && (conecorrpt) < 25.0) return 0.24214912042 + isyst * 0.00832140950501;
    if (fabs(eta) < 1.2 && (conecorrpt) < 30.0) return 0.0868470943023 + isyst * 0.00499280338832;
    if (fabs(eta) < 2.4 && (conecorrpt) < 30.0) return 0.100757210538 + isyst * 0.00843374400125;
    if (fabs(eta) < 1.2 && (conecorrpt) < 40.0) return 0.077875647544 + isyst * 0.00628050293857;
    if (fabs(eta) < 2.4 && (conecorrpt) < 40.0) return 0.0811261582513 + isyst * 0.00822389216675;
    if (fabs(eta) < 1.2) return 0.0681734360529 + isyst * 0.0235078478836;
    if (fabs(eta) < 2.4) return 0.0749432345327 + isyst * 0.0313488470032;
    printf("WARNING in fakerate_mu_data_baseline_v2_3l(): the given phase-space (%f, %f) did not fall under any range!\n", eta, conecorrpt); 
    return 1;
}

float fakerate_el_data_baseline_v2_3l(float eta, float conecorrpt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 0.8 && (conecorrpt) < 25.0) return 0.307265103813 + isyst * 0.0169483338215;
    if (fabs(eta) < 1.479 && (conecorrpt) < 25.0) return 0.330535296352 + isyst * 0.0220881663489;
    if (fabs(eta) < 2.5 && (conecorrpt) < 25.0) return 0.240144147687 + isyst * 0.0316529204631;
    if (fabs(eta) < 0.8 && (conecorrpt) < 30.0) return 0.192670747646 + isyst * 0.0207974862647;
    if (fabs(eta) < 1.479 && (conecorrpt) < 30.0) return 0.196570931204 + isyst * 0.0252012996982;
    if (fabs(eta) < 2.5 && (conecorrpt) < 30.0) return 0.21873504844 + isyst * 0.0327976458885;
    if (fabs(eta) < 0.8 && (conecorrpt) < 40.0) return 0.172162470642 + isyst * 0.0302805162542;
    if (fabs(eta) < 1.479 && (conecorrpt) < 40.0) return 0.187044646381 + isyst * 0.0214287278628;
    if (fabs(eta) < 2.5 && (conecorrpt) < 40.0) return 0.223758784276 + isyst * 0.0368017131904;
    if (fabs(eta) < 0.8) return 0.211507490934 + isyst * 0.0588871246054;
    if (fabs(eta) < 1.479) return 0.178934692309 + isyst * 0.0635291559794;
    if (fabs(eta) < 2.5) return 0.220116229534 + isyst * 0.0483889510294;
    printf("WARNING in fakerate_el_data_baseline_v2_3l(): the given phase-space (%f, %f) did not fall under any range!\n", eta, conecorrpt); 
    return 1;
}

float fakerate_mu_qcd_baseline_v2_3l(float eta, float conecorrpt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 1.2 && (conecorrpt) < 25.0) return 0.249076722609 + isyst * 0.0058366758245;
    if (fabs(eta) < 2.4 && (conecorrpt) < 25.0) return 0.251918459579 + isyst * 0.00799128848645;
    if (fabs(eta) < 1.2 && (conecorrpt) < 30.0) return 0.0860040773907 + isyst * 0.00992035063957;
    if (fabs(eta) < 2.4 && (conecorrpt) < 30.0) return 0.114024355344 + isyst * 0.0145211401579;
    if (fabs(eta) < 1.2 && (conecorrpt) < 40.0) return 0.0732679951557 + isyst * 0.00936473855339;
    if (fabs(eta) < 2.4 && (conecorrpt) < 40.0) return 0.0806026775827 + isyst * 0.0118852354524;
    if (fabs(eta) < 1.2) return 0.0624241769567 + isyst * 0.00860465358027;
    if (fabs(eta) < 2.4) return 0.0784880525095 + isyst * 0.0106227001908;
    printf("WARNING in fakerate_mu_qcd_baseline_v2_3l(): the given phase-space (%f, %f) did not fall under any range!\n", eta, conecorrpt); 
    return 1;
}

float fakerate_el_qcd_baseline_v2_3l(float eta, float conecorrpt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 0.8 && (conecorrpt) < 25.0) return 0.324552528025 + isyst * 0.019912690896;
    if (fabs(eta) < 1.479 && (conecorrpt) < 25.0) return 0.345854014572 + isyst * 0.0501426890678;
    if (fabs(eta) < 2.5 && (conecorrpt) < 25.0) return 0.234306992433 + isyst * 0.0331701438468;
    if (fabs(eta) < 0.8 && (conecorrpt) < 30.0) return 0.242466571343 + isyst * 0.10902293545;
    if (fabs(eta) < 1.479 && (conecorrpt) < 30.0) return 0.127413162681 + isyst * 0.0335613864343;
    if (fabs(eta) < 2.5 && (conecorrpt) < 30.0) return 0.190944755621 + isyst * 0.0485993247428;
    if (fabs(eta) < 0.8 && (conecorrpt) < 40.0) return 0.391456388558 + isyst * 0.157663862958;
    if (fabs(eta) < 1.479 && (conecorrpt) < 40.0) return 0.325613485702 + isyst * 0.175108674137;
    if (fabs(eta) < 2.5 && (conecorrpt) < 40.0) return 0.221695641972 + isyst * 0.0732116122155;
    if (fabs(eta) < 0.8) return 0.271489372995 + isyst * 0.0495384605417;
    if (fabs(eta) < 1.479) return 0.314510688439 + isyst * 0.0571795035335;
    if (fabs(eta) < 2.5) return 0.363535548229 + isyst * 0.0634819304504;
    printf("WARNING in fakerate_el_qcd_baseline_v2_3l(): the given phase-space (%f, %f) did not fall under any range!\n", eta, conecorrpt); 
    return 1;
}


#endif
