float fakerate_mu_data_baseline_v2_3l(float eta, float conecorrpt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 1.2 && (conecorrpt) < 25.0) return 0.323906732418 + isyst * 0.00837977835873;
    if (fabs(eta) < 2.4 && (conecorrpt) < 25.0) return 0.319393460305 + isyst * 0.00996120546857;
    if (fabs(eta) < 1.2 && (conecorrpt) < 30.0) return 0.0946133552592 + isyst * 0.00550791112222;
    if (fabs(eta) < 2.4 && (conecorrpt) < 30.0) return 0.111499863092 + isyst * 0.00770750533532;
    if (fabs(eta) < 1.2 && (conecorrpt) < 40.0) return 0.083248031153 + isyst * 0.00701383762705;
    if (fabs(eta) < 2.4 && (conecorrpt) < 40.0) return 0.0866929794202 + isyst * 0.00873836828406;
    if (fabs(eta) < 1.2) return 0.0677759608883 + isyst * 0.0290759672496;
    if (fabs(eta) < 2.4) return 0.0730187386593 + isyst * 0.0421267416634;
    printf("WARNING in fakerate_mu_data_baseline_v2_3l(): the given phase-space (%f, %f) did not fall under any range!\n", eta, conecorrpt); 
    return 1;
}

float fakerate_el_data_baseline_v2_3l(float eta, float conecorrpt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 0.8 && (conecorrpt) < 25.0) return 0.377894893801 + isyst * 0.0226609961302;
    if (fabs(eta) < 1.479 && (conecorrpt) < 25.0) return 0.424194309171 + isyst * 0.0305959368193;
    if (fabs(eta) < 2.5 && (conecorrpt) < 25.0) return 0.586787954077 + isyst * 0.0605554477024;
    if (fabs(eta) < 0.8 && (conecorrpt) < 30.0) return 0.225331615233 + isyst * 0.0305284229283;
    if (fabs(eta) < 1.479 && (conecorrpt) < 30.0) return 0.309940498858 + isyst * 0.0364835263746;
    if (fabs(eta) < 2.5 && (conecorrpt) < 30.0) return 0.445674865083 + isyst * 0.0580132756063;
    if (fabs(eta) < 0.8 && (conecorrpt) < 40.0) return 0.131255244752 + isyst * 0.0504067100128;
    if (fabs(eta) < 1.479 && (conecorrpt) < 40.0) return 0.183965283611 + isyst * 0.0433384920434;
    if (fabs(eta) < 2.5 && (conecorrpt) < 40.0) return 0.395380950603 + isyst * 0.0626923579681;
    if (fabs(eta) < 0.8) return 0.0532971908429 + isyst * 0.114366304455;
    if (fabs(eta) < 1.479) return 0.0127463335785 + isyst * 0.12755451683;
    if (fabs(eta) < 2.5) return 0.242250091146 + isyst * 0.18845961152;
    printf("WARNING in fakerate_el_data_baseline_v2_3l(): the given phase-space (%f, %f) did not fall under any range!\n", eta, conecorrpt); 
    return 1;
}

float fakerate_mu_qcd_baseline_v2_3l(float eta, float conecorrpt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 1.2 && (conecorrpt) < 25.0) return 0.331673726931 + isyst * 0.00807323470199;
    if (fabs(eta) < 2.4 && (conecorrpt) < 25.0) return 0.336727332005 + isyst * 0.0109795845758;
    if (fabs(eta) < 1.2 && (conecorrpt) < 30.0) return 0.0940967845296 + isyst * 0.010905025112;
    if (fabs(eta) < 2.4 && (conecorrpt) < 30.0) return 0.128699198485 + isyst * 0.0165052245145;
    if (fabs(eta) < 1.2 && (conecorrpt) < 40.0) return 0.0791852628968 + isyst * 0.0101279625019;
    if (fabs(eta) < 2.4 && (conecorrpt) < 40.0) return 0.0876690366802 + isyst * 0.0129780360591;
    if (fabs(eta) < 1.2) return 0.0665811939942 + isyst * 0.00919809252735;
    if (fabs(eta) < 2.4) return 0.0851246030236 + isyst * 0.011575653264;
    printf("WARNING in fakerate_mu_qcd_baseline_v2_3l(): the given phase-space (%f, %f) did not fall under any range!\n", eta, conecorrpt); 
    return 1;
}

float fakerate_el_qcd_baseline_v2_3l(float eta, float conecorrpt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 0.8 && (conecorrpt) < 25.0) return 0.412640631473 + isyst * 0.0315200665285;
    if (fabs(eta) < 1.479 && (conecorrpt) < 25.0) return 0.46727925955 + isyst * 0.0779562383596;
    if (fabs(eta) < 2.5 && (conecorrpt) < 25.0) return 0.693567770781 + isyst * 0.0961744611247;
    if (fabs(eta) < 0.8 && (conecorrpt) < 30.0) return 0.360579216701 + isyst * 0.177002914393;
    if (fabs(eta) < 1.479 && (conecorrpt) < 30.0) return 0.161853923983 + isyst * 0.0464717884921;
    if (fabs(eta) < 2.5 && (conecorrpt) < 30.0) return 0.314452837107 + isyst * 0.10703464991;
    if (fabs(eta) < 0.8 && (conecorrpt) < 40.0) return 0.694012301304 + isyst * 0.294202620056;
    if (fabs(eta) < 1.479 && (conecorrpt) < 40.0) return 0.546654713193 + isyst * 0.313049056719;
    if (fabs(eta) < 2.5 && (conecorrpt) < 40.0) return 0.492716940321 + isyst * 0.15682538037;
    if (fabs(eta) < 0.8) return 0.352263864442 + isyst * 0.0745471970536;
    if (fabs(eta) < 1.479) return 0.414669706531 + isyst * 0.0856758259237;
    if (fabs(eta) < 2.5) return 0.867868851751 + isyst * 0.178198450551;
    printf("WARNING in fakerate_el_qcd_baseline_v2_3l(): the given phase-space (%f, %f) did not fall under any range!\n", eta, conecorrpt); 
    return 1;
}

