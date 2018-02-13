float fakerate_mu_data_baseline_v2_3l(float eta, float conecorrpt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 1.2 && (conecorrpt) < 25.0) return 0.324047628701 + isyst * 0.00837943479841;
    if (fabs(eta) < 2.4 && (conecorrpt) < 25.0) return 0.319529012011 + isyst * 0.00996091486103;
    if (fabs(eta) < 1.2 && (conecorrpt) < 30.0) return 0.0952495474335 + isyst * 0.0054944929123;
    if (fabs(eta) < 2.4 && (conecorrpt) < 30.0) return 0.112222821695 + isyst * 0.00769795251827;
    if (fabs(eta) < 1.2 && (conecorrpt) < 40.0) return 0.0846421803647 + isyst * 0.00692791252437;
    if (fabs(eta) < 2.4 && (conecorrpt) < 40.0) return 0.0882777428896 + isyst * 0.00864205524405;
    if (fabs(eta) < 1.2) return 0.0745120541402 + isyst * 0.0285694058155;
    if (fabs(eta) < 2.4) return 0.0826718258491 + isyst * 0.041394674211;
    printf("WARNING in fakerate_mu_data_baseline_v2_3l(): the given phase-space (%f, %f) did not fall under any range!\n", eta, conecorrpt); 
    return 1;
}

float fakerate_el_data_baseline_v2_3l(float eta, float conecorrpt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 0.8 && (conecorrpt) < 25.0) return 0.383420614729 + isyst * 0.0226666133554;
    if (fabs(eta) < 1.479 && (conecorrpt) < 25.0) return 0.42925092722 + isyst * 0.0306380050719;
    if (fabs(eta) < 2.5 && (conecorrpt) < 25.0) return 0.595922430404 + isyst * 0.0607061729882;
    if (fabs(eta) < 0.8 && (conecorrpt) < 30.0) return 0.253318378478 + isyst * 0.0305868506882;
    if (fabs(eta) < 1.479 && (conecorrpt) < 30.0) return 0.329026167996 + isyst * 0.0371028330186;
    if (fabs(eta) < 2.5 && (conecorrpt) < 30.0) return 0.471736113972 + isyst * 0.0592605226349;
    if (fabs(eta) < 0.8 && (conecorrpt) < 40.0) return 0.205792766212 + isyst * 0.0462275167487;
    if (fabs(eta) < 1.479 && (conecorrpt) < 40.0) return 0.242735219177 + isyst * 0.0406829712023;
    if (fabs(eta) < 2.5 && (conecorrpt) < 40.0) return 0.468858090895 + isyst * 0.0602136273864;
    if (fabs(eta) < 0.8) return 0.248739410514 + isyst * 0.103623990547;
    if (fabs(eta) < 1.479) return 0.227044157577 + isyst * 0.115852910409;
    if (fabs(eta) < 2.5) return 0.545261343018 + isyst * 0.171732019571;
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

