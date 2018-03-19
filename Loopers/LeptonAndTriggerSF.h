#ifndef LeptonAndTriggerSF_h
#define LeptonAndTriggerSF_h

#include "fakerate_baseline_v2_ss.C"
#include "fakerate_baseline_v2_3l.C"

float trigeff_dimu_dz(float etatrail, float etalead, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(etatrail) < 0.8 && fabs(etalead) < 0.8) return 0.958495616913 + isyst * 0.00546260719797;
    if (fabs(etatrail) < 1.25 && fabs(etalead) < 0.8) return 0.0 + isyst * 0.0;
    if (fabs(etatrail) < 1.6 && fabs(etalead) < 0.8) return 0.0 + isyst * 0.0;
    if (fabs(etatrail) < 2.1 && fabs(etalead) < 0.8) return 0.0 + isyst * 0.0;
    if (fabs(etatrail) < 2.4 && fabs(etalead) < 0.8) return 0.0 + isyst * 0.0;
    if (fabs(etatrail) < 0.8 && fabs(etalead) < 1.25) return 0.958122730255 + isyst * 0.00546046056872;
    if (fabs(etatrail) < 1.25 && fabs(etalead) < 1.25) return 0.958429932594 + isyst * 0.0176314346933;
    if (fabs(etatrail) < 1.6 && fabs(etalead) < 1.25) return 0.0 + isyst * 0.0;
    if (fabs(etatrail) < 2.1 && fabs(etalead) < 1.25) return 0.0 + isyst * 0.0;
    if (fabs(etatrail) < 2.4 && fabs(etalead) < 1.25) return 0.0 + isyst * 0.0;
    if (fabs(etatrail) < 0.8 && fabs(etalead) < 1.6) return 0.947062015533 + isyst * 0.00645058084178;
    if (fabs(etatrail) < 1.25 && fabs(etalead) < 1.6) return 0.946415901184 + isyst * 0.0147614055914;
    if (fabs(etatrail) < 1.6 && fabs(etalead) < 1.6) return 0.931489229202 + isyst * 0.0240560712592;
    if (fabs(etatrail) < 2.1 && fabs(etalead) < 1.6) return 0.0 + isyst * 0.0;
    if (fabs(etatrail) < 2.4 && fabs(etalead) < 1.6) return 0.0 + isyst * 0.0;
    if (fabs(etatrail) < 0.8 && fabs(etalead) < 2.1) return 0.948736727238 + isyst * 0.00683121074294;
    if (fabs(etatrail) < 1.25 && fabs(etalead) < 2.1) return 0.954986155033 + isyst * 0.0146794964116;
    if (fabs(etatrail) < 1.6 && fabs(etalead) < 2.1) return 0.934047341347 + isyst * 0.0159555285106;
    if (fabs(etatrail) < 2.1 && fabs(etalead) < 2.1) return 0.943475961685 + isyst * 0.0220071955461;
    if (fabs(etatrail) < 2.4 && fabs(etalead) < 2.1) return 0.0 + isyst * 0.0;
    if (fabs(etatrail) < 0.8) return 0.946924805641 + isyst * 0.0102463712706;
    if (fabs(etatrail) < 1.25) return 0.952153086662 + isyst * 0.0228724522651;
    if (fabs(etatrail) < 1.6) return 0.94414126873 + isyst * 0.0242746719209;
    if (fabs(etatrail) < 2.1) return 0.944147527218 + isyst * 0.0221479045306;
    if (fabs(etatrail) < 2.4) return 0.948979616165 + isyst * 0.0434429235866;
    printf("WARNING in trigeff_dimu_dz(): the given phase-space (%f, %f) did not fall under any range!\n", etatrail, etalead);
    return 1;
}

float trigeff_diel_dz(float etatrail, float etalead, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(etatrail) < 0.8 && fabs(etalead) < 0.8) return 0.992154300213 + isyst * 0.00203163606519;
    if (fabs(etatrail) < 1.25 && fabs(etalead) < 0.8) return 0.0 + isyst * 0.0;
    if (fabs(etatrail) < 1.6 && fabs(etalead) < 0.8) return 0.0 + isyst * 0.0;
    if (fabs(etatrail) < 2.1 && fabs(etalead) < 0.8) return 0.0 + isyst * 0.0;
    if (fabs(etatrail) < 2.4 && fabs(etalead) < 0.8) return 0.0 + isyst * 0.0;
    if (fabs(etatrail) < 0.8 && fabs(etalead) < 1.25) return 0.993901968002 + isyst * 0.00212507876017;
    if (fabs(etatrail) < 1.25 && fabs(etalead) < 1.25) return 0.995324671268 + isyst * 0.00681363620605;
    if (fabs(etatrail) < 1.6 && fabs(etalead) < 1.25) return 0.0 + isyst * 0.0;
    if (fabs(etatrail) < 2.1 && fabs(etalead) < 1.25) return 0.0 + isyst * 0.0;
    if (fabs(etatrail) < 2.4 && fabs(etalead) < 1.25) return 0.0 + isyst * 0.0;
    if (fabs(etatrail) < 0.8 && fabs(etalead) < 1.6) return 0.990763425827 + isyst * 0.00325640447262;
    if (fabs(etatrail) < 1.25 && fabs(etalead) < 1.6) return 0.990844190121 + isyst * 0.00714279079965;
    if (fabs(etatrail) < 1.6 && fabs(etalead) < 1.6) return 0.988755106926 + isyst * 0.0149449686468;
    if (fabs(etatrail) < 2.1 && fabs(etalead) < 1.6) return 0.0 + isyst * 0.0;
    if (fabs(etatrail) < 2.4 && fabs(etalead) < 1.6) return 0.0 + isyst * 0.0;
    if (fabs(etatrail) < 0.8 && fabs(etalead) < 2.1) return 0.989297926426 + isyst * 0.00332681036547;
    if (fabs(etatrail) < 1.25 && fabs(etalead) < 2.1) return 0.988601565361 + isyst * 0.00625359984571;
    if (fabs(etatrail) < 1.6 && fabs(etalead) < 2.1) return 0.986697733402 + isyst * 0.00879642239202;
    if (fabs(etatrail) < 2.1 && fabs(etalead) < 2.1) return 0.985203206539 + isyst * 0.0107807543243;
    if (fabs(etatrail) < 2.4 && fabs(etalead) < 2.1) return 0.0 + isyst * 0.0;
    if (fabs(etatrail) < 0.8) return 0.986127853394 + isyst * 0.00767700752112;
    if (fabs(etatrail) < 1.25) return 0.988208055496 + isyst * 0.0203401438854;
    if (fabs(etatrail) < 1.6) return 0.988068580627 + isyst * 0.0270632436227;
    if (fabs(etatrail) < 2.1) return 0.98489266634 + isyst * 0.0227624791057;
    if (fabs(etatrail) < 2.4) return 0.982456147671 + isyst * 0.106723565089;
    printf("WARNING in trigeff_diel_dz(): the given phase-space (%f, %f) did not fall under any range!\n", etatrail, etalead);
    return 1;
}

float trigeff_emu_dz(float etamuon, float etaelec, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(etamuon) < 0.8 && fabs(etaelec) < 0.8) return 1.0 + isyst * 0.0148988450118;
    if (fabs(etamuon) < 1.25 && fabs(etaelec) < 0.8) return 1.0 + isyst * 0.0224563228222;
    if (fabs(etamuon) < 1.6 && fabs(etaelec) < 0.8) return 1.0 + isyst * 0.0299812675598;
    if (fabs(etamuon) < 2.1 && fabs(etaelec) < 0.8) return 1.0 + isyst * 0.0367855946389;
    if (fabs(etamuon) < 2.4 && fabs(etaelec) < 0.8) return 1.0 + isyst * 0.0632455532034;
    if (fabs(etamuon) < 0.8 && fabs(etaelec) < 1.25) return 1.0 + isyst * 0.0219053977169;
    if (fabs(etamuon) < 1.25 && fabs(etaelec) < 1.25) return 1.0 + isyst * 0.0341792963512;
    if (fabs(etamuon) < 1.6 && fabs(etaelec) < 1.25) return 1.0 + isyst * 0.0422200330921;
    if (fabs(etamuon) < 2.1 && fabs(etaelec) < 1.25) return 1.0 + isyst * 0.0508986598559;
    if (fabs(etamuon) < 2.4 && fabs(etaelec) < 1.25) return 1.0 + isyst * 0.084818892968;
    if (fabs(etamuon) < 0.8 && fabs(etaelec) < 1.6) return 1.0 + isyst * 0.0326250816902;
    if (fabs(etamuon) < 1.25 && fabs(etaelec) < 1.6) return 1.0 + isyst * 0.0467780269725;
    if (fabs(etamuon) < 1.6 && fabs(etaelec) < 1.6) return 1.0 + isyst * 0.0625;
    if (fabs(etamuon) < 2.1 && fabs(etaelec) < 1.6) return 1.0 + isyst * 0.0707106781187;
    if (fabs(etamuon) < 2.4 && fabs(etaelec) < 1.6) return 1.0 + isyst * 0.125491161028;
    if (fabs(etamuon) < 0.8 && fabs(etaelec) < 2.1) return 1.0 + isyst * 0.0327824804786;
    if (fabs(etamuon) < 1.25 && fabs(etaelec) < 2.1) return 1.0 + isyst * 0.0485071250073;
    if (fabs(etamuon) < 1.6 && fabs(etaelec) < 2.1) return 1.0 + isyst * 0.0597081434027;
    if (fabs(etamuon) < 2.1 && fabs(etaelec) < 2.1) return 1.0 + isyst * 0.0658664921939;
    if (fabs(etamuon) < 2.4 && fabs(etaelec) < 2.1) return 1.0 + isyst * 0.108465228909;
    if (fabs(etamuon) < 0.8) return 1.0 + isyst * 0.105117666246;
    if (fabs(etamuon) < 1.25) return 1.0 + isyst * 0.162221421131;
    if (fabs(etamuon) < 1.6) return 1.0 + isyst * 0.178174161275;
    if (fabs(etamuon) < 2.1) return 1.0 + isyst * 0.215665546407;
    if (fabs(etamuon) < 2.4) return 1.0 + isyst * 0.408248290464;
    printf("WARNING in trigeff_emu_dz(): the given phase-space (%f, %f) did not fall under any range!\n", etamuon, etaelec);
    return 1;
}

float trigeff_mu_lead(float eta, float pt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 0.8 && (pt) < 10.0) return 0.0 + isyst * 0.0;
    if (fabs(eta) < 1.25 && (pt) < 10.0) return 0.0 + isyst * 0.0;
    if (fabs(eta) < 1.6 && (pt) < 10.0) return 0.0 + isyst * 0.0;
    if (fabs(eta) < 2.1 && (pt) < 10.0) return 0.0 + isyst * 0.0;
    if (fabs(eta) < 2.4 && (pt) < 10.0) return 0.0 + isyst * 0.0;
    if (fabs(eta) < 0.8 && (pt) < 20.0) return 0.485289096832 + isyst * 0.00217619814201;
    if (fabs(eta) < 1.25 && (pt) < 20.0) return 0.442688703537 + isyst * 0.00286556291153;
    if (fabs(eta) < 1.6 && (pt) < 20.0) return 0.432150036097 + isyst * 0.00320639407397;
    if (fabs(eta) < 2.1 && (pt) < 20.0) return 0.382266998291 + isyst * 0.00292072228902;
    if (fabs(eta) < 2.4 && (pt) < 20.0) return 0.328791469336 + isyst * 0.00390191679523;
    if (fabs(eta) < 0.8 && (pt) < 25.0) return 0.923819541931 + isyst * 0.00257577554411;
    if (fabs(eta) < 1.25 && (pt) < 25.0) return 0.928004562855 + isyst * 0.00395023657835;
    if (fabs(eta) < 1.6 && (pt) < 25.0) return 0.962020993233 + isyst * 0.00487367049199;
    if (fabs(eta) < 2.1 && (pt) < 25.0) return 0.916795015335 + isyst * 0.00487240686941;
    if (fabs(eta) < 2.4 && (pt) < 25.0) return 0.821739792824 + isyst * 0.00662717857136;
    if (fabs(eta) < 0.8 && (pt) < 30.0) return 0.925402164459 + isyst * 0.00174825335843;
    if (fabs(eta) < 1.25 && (pt) < 30.0) return 0.930361151695 + isyst * 0.00274203158045;
    if (fabs(eta) < 1.6 && (pt) < 30.0) return 0.964953124523 + isyst * 0.00346462035417;
    if (fabs(eta) < 2.1 && (pt) < 30.0) return 0.925271034241 + isyst * 0.00350501941534;
    if (fabs(eta) < 2.4 && (pt) < 30.0) return 0.853314638138 + isyst * 0.00477973668153;
    if (fabs(eta) < 0.8 && (pt) < 35.0) return 0.926691830158 + isyst * 0.0012517373;
    if (fabs(eta) < 1.25 && (pt) < 35.0) return 0.930585741997 + isyst * 0.00195093174202;
    if (fabs(eta) < 1.6 && (pt) < 35.0) return 0.965024650097 + isyst * 0.00255296891033;
    if (fabs(eta) < 2.1 && (pt) < 35.0) return 0.927997112274 + isyst * 0.00257300858657;
    if (fabs(eta) < 2.4 && (pt) < 35.0) return 0.872729957104 + isyst * 0.00355997246416;
    if (fabs(eta) < 0.8 && (pt) < 40.0) return 0.92677205801 + isyst * 0.000999646687114;
    if (fabs(eta) < 1.25 && (pt) < 40.0) return 0.93065148592 + isyst * 0.00148070164706;
    if (fabs(eta) < 1.6 && (pt) < 40.0) return 0.963970661163 + isyst * 0.00197602971094;
    if (fabs(eta) < 2.1 && (pt) < 40.0) return 0.929808735847 + isyst * 0.00203236888152;
    if (fabs(eta) < 2.4 && (pt) < 40.0) return 0.884106934071 + isyst * 0.00292662165442;
    if (fabs(eta) < 0.8 && (pt) < 50.0) return 0.925964653492 + isyst * 0.000687396907038;
    if (fabs(eta) < 1.25 && (pt) < 50.0) return 0.931133925915 + isyst * 0.000969411929169;
    if (fabs(eta) < 1.6 && (pt) < 50.0) return 0.959052085876 + isyst * 0.00123406162104;
    if (fabs(eta) < 2.1 && (pt) < 50.0) return 0.930562853813 + isyst * 0.00128939078806;
    if (fabs(eta) < 2.4 && (pt) < 50.0) return 0.894406437874 + isyst * 0.00207138069792;
    if (fabs(eta) < 0.8 && (pt) < 70.0) return 0.924016833305 + isyst * 0.00122157806112;
    if (fabs(eta) < 1.25 && (pt) < 70.0) return 0.930401027203 + isyst * 0.00170846691762;
    if (fabs(eta) < 1.6 && (pt) < 70.0) return 0.945301949978 + isyst * 0.00213169493654;
    if (fabs(eta) < 2.1 && (pt) < 70.0) return 0.93123704195 + isyst * 0.00220691347254;
    if (fabs(eta) < 2.4 && (pt) < 70.0) return 0.899564743042 + isyst * 0.00354156911912;
    if (fabs(eta) < 0.8 && (pt) < 100.0) return 0.919343531132 + isyst * 0.00333540537524;
    if (fabs(eta) < 1.25 && (pt) < 100.0) return 0.928387224674 + isyst * 0.0047459653979;
    if (fabs(eta) < 1.6 && (pt) < 100.0) return 0.899892091751 + isyst * 0.00579193484437;
    if (fabs(eta) < 2.1 && (pt) < 100.0) return 0.924907147884 + isyst * 0.00607713544489;
    if (fabs(eta) < 2.4 && (pt) < 100.0) return 0.90477001667 + isyst * 0.00989260560718;
    if (fabs(eta) < 0.8 && (pt) < 200.0) return 0.914235055447 + isyst * 0.00559716791167;
    if (fabs(eta) < 1.25 && (pt) < 200.0) return 0.922193586826 + isyst * 0.00796320023675;
    if (fabs(eta) < 1.6 && (pt) < 200.0) return 0.833148777485 + isyst * 0.00943439712422;
    if (fabs(eta) < 2.1 && (pt) < 200.0) return 0.89550948143 + isyst * 0.0102324535902;
    if (fabs(eta) < 2.4 && (pt) < 200.0) return 0.881266474724 + isyst * 0.018343723994;
    if (fabs(eta) < 0.8 && (pt) < 300.0) return 0.894565224648 + isyst * 0.019194723831;
    if (fabs(eta) < 1.25 && (pt) < 300.0) return 0.915387988091 + isyst * 0.0277247948717;
    if (fabs(eta) < 1.6 && (pt) < 300.0) return 0.792071819305 + isyst * 0.0325832406518;
    if (fabs(eta) < 2.1 && (pt) < 300.0) return 0.816182911396 + isyst * 0.0361071590549;
    if (fabs(eta) < 2.4 && (pt) < 300.0) return 0.804444432259 + isyst * 0.0803208927751;
    if (fabs(eta) < 0.8) return 0.897703528404 + isyst * 0.0421694465755;
    if (fabs(eta) < 1.25) return 0.895491778851 + isyst * 0.0589768878915;
    if (fabs(eta) < 1.6) return 0.780821919441 + isyst * 0.0690072654786;
    if (fabs(eta) < 2.1) return 0.764367818832 + isyst * 0.0880381962027;
    if (fabs(eta) < 2.4) return 0.833333313465 + isyst * 0.252304196175;
    printf("WARNING in trigeff_mu_lead(): the given phase-space (%f, %f) did not fall under any range!\n", eta, pt);
    return 1;
}

float trigeff_mu_trail(float eta, float pt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 0.8 && (pt) < 10.0) return 0.0 + isyst * 0.0;
    if (fabs(eta) < 1.25 && (pt) < 10.0) return 0.0 + isyst * 0.0;
    if (fabs(eta) < 1.6 && (pt) < 10.0) return 0.0 + isyst * 0.0;
    if (fabs(eta) < 2.1 && (pt) < 10.0) return 0.0 + isyst * 0.0;
    if (fabs(eta) < 2.4 && (pt) < 10.0) return 0.0 + isyst * 0.0;
    if (fabs(eta) < 0.8 && (pt) < 20.0) return 0.920952677727 + isyst * 0.0034093349455;
    if (fabs(eta) < 1.25 && (pt) < 20.0) return 0.947876632214 + isyst * 0.0048722664975;
    if (fabs(eta) < 1.6 && (pt) < 20.0) return 0.974800229073 + isyst * 0.00565489783158;
    if (fabs(eta) < 2.1 && (pt) < 20.0) return 0.939942836761 + isyst * 0.00542570385713;
    if (fabs(eta) < 2.4 && (pt) < 20.0) return 0.932220518589 + isyst * 0.00792276896744;
    if (fabs(eta) < 0.8 && (pt) < 25.0) return 0.934387803078 + isyst * 0.00259757226009;
    if (fabs(eta) < 1.25 && (pt) < 25.0) return 0.954212427139 + isyst * 0.00403276077213;
    if (fabs(eta) < 1.6 && (pt) < 25.0) return 0.982256352901 + isyst * 0.00494999071162;
    if (fabs(eta) < 2.1 && (pt) < 25.0) return 0.946583449841 + isyst * 0.00498925336209;
    if (fabs(eta) < 2.4 && (pt) < 25.0) return 0.942261993885 + isyst * 0.00732753823596;
    if (fabs(eta) < 0.8 && (pt) < 30.0) return 0.935320436954 + isyst * 0.00176211818029;
    if (fabs(eta) < 1.25 && (pt) < 30.0) return 0.954345822334 + isyst * 0.00279435112274;
    if (fabs(eta) < 1.6 && (pt) < 30.0) return 0.982160031796 + isyst * 0.00351064508737;
    if (fabs(eta) < 2.1 && (pt) < 30.0) return 0.947456598282 + isyst * 0.00356716807749;
    if (fabs(eta) < 2.4 && (pt) < 30.0) return 0.944064855576 + isyst * 0.00514909700966;
    if (fabs(eta) < 0.8 && (pt) < 35.0) return 0.936251997948 + isyst * 0.00126129513922;
    if (fabs(eta) < 1.25 && (pt) < 35.0) return 0.953760504723 + isyst * 0.00198689391209;
    if (fabs(eta) < 1.6 && (pt) < 35.0) return 0.981917738914 + isyst * 0.00258626292823;
    if (fabs(eta) < 2.1 && (pt) < 35.0) return 0.946613013744 + isyst * 0.00261120384268;
    if (fabs(eta) < 2.4 && (pt) < 35.0) return 0.947488427162 + isyst * 0.00378262695704;
    if (fabs(eta) < 0.8 && (pt) < 40.0) return 0.936363339424 + isyst * 0.00100730389182;
    if (fabs(eta) < 1.25 && (pt) < 40.0) return 0.953175842762 + isyst * 0.00150722907887;
    if (fabs(eta) < 1.6 && (pt) < 40.0) return 0.982085347176 + isyst * 0.00200368689638;
    if (fabs(eta) < 2.1 && (pt) < 40.0) return 0.94696521759 + isyst * 0.00206013036206;
    if (fabs(eta) < 2.4 && (pt) < 40.0) return 0.948359966278 + isyst * 0.00308235478177;
    if (fabs(eta) < 0.8 && (pt) < 50.0) return 0.935382962227 + isyst * 0.000692571181002;
    if (fabs(eta) < 1.25 && (pt) < 50.0) return 0.953191936016 + isyst * 0.000986412869397;
    if (fabs(eta) < 1.6 && (pt) < 50.0) return 0.98130685091 + isyst * 0.00125536795772;
    if (fabs(eta) < 2.1 && (pt) < 50.0) return 0.945464909077 + isyst * 0.00130468041521;
    if (fabs(eta) < 2.4 && (pt) < 50.0) return 0.949369609356 + isyst * 0.0021648142322;
    if (fabs(eta) < 0.8 && (pt) < 70.0) return 0.933903753757 + isyst * 0.00123124745683;
    if (fabs(eta) < 1.25 && (pt) < 70.0) return 0.95255190134 + isyst * 0.00173857463051;
    if (fabs(eta) < 1.6 && (pt) < 70.0) return 0.981103420258 + isyst * 0.00219157954421;
    if (fabs(eta) < 2.1 && (pt) < 70.0) return 0.945890903473 + isyst * 0.00223263209912;
    if (fabs(eta) < 2.4 && (pt) < 70.0) return 0.946820616722 + isyst * 0.00367831810352;
    if (fabs(eta) < 0.8 && (pt) < 100.0) return 0.930257022381 + isyst * 0.00336466945025;
    if (fabs(eta) < 1.25 && (pt) < 100.0) return 0.951008379459 + isyst * 0.00483152930378;
    if (fabs(eta) < 1.6 && (pt) < 100.0) return 0.975963890553 + isyst * 0.00615134895603;
    if (fabs(eta) < 2.1 && (pt) < 100.0) return 0.940444350243 + isyst * 0.00615264827311;
    if (fabs(eta) < 2.4 && (pt) < 100.0) return 0.943725168705 + isyst * 0.0102061163659;
    if (fabs(eta) < 0.8 && (pt) < 200.0) return 0.927840054035 + isyst * 0.00565866274554;
    if (fabs(eta) < 1.25 && (pt) < 200.0) return 0.947699785233 + isyst * 0.0081259551571;
    if (fabs(eta) < 1.6 && (pt) < 200.0) return 0.95267790556 + isyst * 0.0104121966551;
    if (fabs(eta) < 2.1 && (pt) < 200.0) return 0.915432989597 + isyst * 0.0103998834342;
    if (fabs(eta) < 2.4 && (pt) < 200.0) return 0.921656191349 + isyst * 0.01895968127;
    if (fabs(eta) < 0.8 && (pt) < 300.0) return 0.910869538784 + isyst * 0.0194520197345;
    if (fabs(eta) < 1.25 && (pt) < 300.0) return 0.946953117847 + isyst * 0.0284301619911;
    if (fabs(eta) < 1.6 && (pt) < 300.0) return 0.914734482765 + isyst * 0.036193959849;
    if (fabs(eta) < 2.1 && (pt) < 300.0) return 0.855760753155 + isyst * 0.0373729130747;
    if (fabs(eta) < 2.4 && (pt) < 300.0) return 0.866666674614 + isyst * 0.0847945956815;
    if (fabs(eta) < 0.8) return 0.915448844433 + isyst * 0.0427828357578;
    if (fabs(eta) < 1.25) return 0.926229536533 + isyst * 0.0604649100592;
    if (fabs(eta) < 1.6) return 0.890410959721 + isyst * 0.0759244991468;
    if (fabs(eta) < 2.1) return 0.781609177589 + isyst * 0.0894594922053;
    if (fabs(eta) < 2.4) return 0.916666686535 + isyst * 0.270566107483;
    printf("WARNING in trigeff_mu_trail(): the given phase-space (%f, %f) did not fall under any range!\n", eta, pt);
    return 1;
}

float trigeff_el_lead(float eta, float pt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 0.8 && (pt) < 10.0) return 0.0 + isyst * 0.0;
    if (fabs(eta) < 1.25 && (pt) < 10.0) return 0.0 + isyst * 0.0;
    if (fabs(eta) < 1.6 && (pt) < 10.0) return 0.0 + isyst * 0.0;
    if (fabs(eta) < 2.1 && (pt) < 10.0) return 0.0 + isyst * 0.0;
    if (fabs(eta) < 2.4 && (pt) < 10.0) return 0.0 + isyst * 0.0;
    if (fabs(eta) < 0.8 && (pt) < 20.0) return 0.000498351582792 + isyst * 9.77591410645e-05;
    if (fabs(eta) < 1.25 && (pt) < 20.0) return 0.000817813444883 + isyst * 0.000174429698169;
    if (fabs(eta) < 1.6 && (pt) < 20.0) return 0.00960683170706 + isyst * 0.000928847543939;
    if (fabs(eta) < 2.1 && (pt) < 20.0) return 0.000702881836332 + isyst * 0.000265757703883;
    if (fabs(eta) < 2.4 && (pt) < 20.0) return 0.000397456286009 + isyst * 0.00039753525771;
    if (fabs(eta) < 0.8 && (pt) < 25.0) return 0.467286527157 + isyst * 0.00241510456174;
    if (fabs(eta) < 1.25 && (pt) < 25.0) return 0.419471412897 + isyst * 0.00335631913246;
    if (fabs(eta) < 1.6 && (pt) < 25.0) return 0.405463665724 + isyst * 0.00516747514884;
    if (fabs(eta) < 2.1 && (pt) < 25.0) return 0.448543071747 + isyst * 0.00587240240429;
    if (fabs(eta) < 2.4 && (pt) < 25.0) return 0.267077684402 + isyst * 0.00913534578149;
    if (fabs(eta) < 0.8 && (pt) < 30.0) return 0.937598764896 + isyst * 0.00259272692697;
    if (fabs(eta) < 1.25 && (pt) < 30.0) return 0.951536655426 + isyst * 0.00404617646382;
    if (fabs(eta) < 1.6 && (pt) < 30.0) return 0.956267118454 + isyst * 0.00645411941432;
    if (fabs(eta) < 2.1 && (pt) < 30.0) return 0.970133125782 + isyst * 0.00700898559933;
    if (fabs(eta) < 2.4 && (pt) < 30.0) return 0.897065758705 + isyst * 0.0141897125284;
    if (fabs(eta) < 0.8 && (pt) < 35.0) return 0.949110031128 + isyst * 0.00180451711962;
    if (fabs(eta) < 1.25 && (pt) < 35.0) return 0.963108778 + isyst * 0.00292329819428;
    if (fabs(eta) < 1.6 && (pt) < 35.0) return 0.968120276928 + isyst * 0.00477060305206;
    if (fabs(eta) < 2.1 && (pt) < 35.0) return 0.975660085678 + isyst * 0.00509831159628;
    if (fabs(eta) < 2.4 && (pt) < 35.0) return 0.948072373867 + isyst * 0.0105725279428;
    if (fabs(eta) < 0.8 && (pt) < 40.0) return 0.959196925163 + isyst * 0.00139179074846;
    if (fabs(eta) < 1.25 && (pt) < 40.0) return 0.968025922775 + isyst * 0.00224937868662;
    if (fabs(eta) < 1.6 && (pt) < 40.0) return 0.971206903458 + isyst * 0.00372249359467;
    if (fabs(eta) < 2.1 && (pt) < 40.0) return 0.978650867939 + isyst * 0.00398827777346;
    if (fabs(eta) < 2.4 && (pt) < 40.0) return 0.960192859173 + isyst * 0.00852058192282;
    if (fabs(eta) < 0.8 && (pt) < 50.0) return 0.962568759918 + isyst * 0.000927823528439;
    if (fabs(eta) < 1.25 && (pt) < 50.0) return 0.970576584339 + isyst * 0.00145078072605;
    if (fabs(eta) < 1.6 && (pt) < 50.0) return 0.973040103912 + isyst * 0.0024068292189;
    if (fabs(eta) < 2.1 && (pt) < 50.0) return 0.980077683926 + isyst * 0.00272619100454;
    if (fabs(eta) < 2.4 && (pt) < 50.0) return 0.965013444424 + isyst * 0.00613965346778;
    if (fabs(eta) < 0.8 && (pt) < 70.0) return 0.965936183929 + isyst * 0.00165980347205;
    if (fabs(eta) < 1.25 && (pt) < 70.0) return 0.97201359272 + isyst * 0.00257142441851;
    if (fabs(eta) < 1.6 && (pt) < 70.0) return 0.974364995956 + isyst * 0.00417665070298;
    if (fabs(eta) < 2.1 && (pt) < 70.0) return 0.98047554493 + isyst * 0.00473081370246;
    if (fabs(eta) < 2.4 && (pt) < 70.0) return 0.968735396862 + isyst * 0.0105571300454;
    if (fabs(eta) < 0.8 && (pt) < 100.0) return 0.969938099384 + isyst * 0.0044036627819;
    if (fabs(eta) < 1.25 && (pt) < 100.0) return 0.975994884968 + isyst * 0.00688721550919;
    if (fabs(eta) < 1.6 && (pt) < 100.0) return 0.973707675934 + isyst * 0.0110610221474;
    if (fabs(eta) < 2.1 && (pt) < 100.0) return 0.981661677361 + isyst * 0.0116687716932;
    if (fabs(eta) < 2.4 && (pt) < 100.0) return 0.971915721893 + isyst * 0.02531338826;
    if (fabs(eta) < 0.8 && (pt) < 200.0) return 0.969920158386 + isyst * 0.00716663026926;
    if (fabs(eta) < 1.25 && (pt) < 200.0) return 0.979286432266 + isyst * 0.0115877950809;
    if (fabs(eta) < 1.6 && (pt) < 200.0) return 0.97321587801 + isyst * 0.0183953880798;
    if (fabs(eta) < 2.1 && (pt) < 200.0) return 0.987339615822 + isyst * 0.0181995985321;
    if (fabs(eta) < 2.4 && (pt) < 200.0) return 0.975920677185 + isyst * 0.0369551241269;
    if (fabs(eta) < 0.8 && (pt) < 300.0) return 0.963103115559 + isyst * 0.0244179854831;
    if (fabs(eta) < 1.25 && (pt) < 300.0) return 0.980341851711 + isyst * 0.0407348323478;
    if (fabs(eta) < 1.6 && (pt) < 300.0) return 0.982683956623 + isyst * 0.0649400621504;
    if (fabs(eta) < 2.1 && (pt) < 300.0) return 0.989495813847 + isyst * 0.0643094823766;
    if (fabs(eta) < 2.4 && (pt) < 300.0) return 0.985507249832 + isyst * 0.168399618706;
    if (fabs(eta) < 0.8) return 0.969696998596 + isyst * 0.0537954766423;
    if (fabs(eta) < 1.25) return 0.995433807373 + isyst * 0.0952363610997;
    if (fabs(eta) < 1.6) return 0.984615385532 + isyst * 0.173386311244;
    if (fabs(eta) < 2.1) return 1.0 + isyst * 0.16552117772;
    if (fabs(eta) < 2.4) return 1.0 + isyst * 0.57735026919;
    printf("WARNING in trigeff_el_lead(): the given phase-space (%f, %f) did not fall under any range!\n", eta, pt);
    return 1;
}

float trigeff_el_trail(float eta, float pt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 0.8 && (pt) < 10.0) return 0.0 + isyst * 0.0;
    if (fabs(eta) < 1.25 && (pt) < 10.0) return 0.0 + isyst * 0.0;
    if (fabs(eta) < 1.6 && (pt) < 10.0) return 0.0 + isyst * 0.0;
    if (fabs(eta) < 2.1 && (pt) < 10.0) return 0.0 + isyst * 0.0;
    if (fabs(eta) < 2.4 && (pt) < 10.0) return 0.0 + isyst * 0.0;
    if (fabs(eta) < 0.8 && (pt) < 20.0) return 0.885743319988 + isyst * 0.005658176435;
    if (fabs(eta) < 1.25 && (pt) < 20.0) return 0.881825983524 + isyst * 0.00785410952808;
    if (fabs(eta) < 1.6 && (pt) < 20.0) return 0.871997892857 + isyst * 0.0120500429515;
    if (fabs(eta) < 2.1 && (pt) < 20.0) return 0.823978304863 + isyst * 0.0122845671572;
    if (fabs(eta) < 2.4 && (pt) < 20.0) return 0.647058844566 + isyst * 0.0205812201646;
    if (fabs(eta) < 0.8 && (pt) < 25.0) return 0.933126926422 + isyst * 0.00391730486697;
    if (fabs(eta) < 1.25 && (pt) < 25.0) return 0.948862016201 + isyst * 0.00591481034768;
    if (fabs(eta) < 1.6 && (pt) < 25.0) return 0.953001260757 + isyst * 0.00933879018087;
    if (fabs(eta) < 2.1 && (pt) < 25.0) return 0.965341567993 + isyst * 0.0100347727148;
    if (fabs(eta) < 2.4 && (pt) < 25.0) return 0.839210867882 + isyst * 0.0195099374148;
    if (fabs(eta) < 0.8 && (pt) < 30.0) return 0.938782811165 + isyst * 0.00259515617398;
    if (fabs(eta) < 1.25 && (pt) < 30.0) return 0.955618619919 + isyst * 0.00405908440555;
    if (fabs(eta) < 1.6 && (pt) < 30.0) return 0.963593065739 + isyst * 0.00649091434542;
    if (fabs(eta) < 2.1 && (pt) < 30.0) return 0.974039971828 + isyst * 0.00703004454684;
    if (fabs(eta) < 2.4 && (pt) < 30.0) return 0.909962117672 + isyst * 0.0143398396985;
    if (fabs(eta) < 0.8 && (pt) < 35.0) return 0.949124097824 + isyst * 0.0018045370249;
    if (fabs(eta) < 1.25 && (pt) < 35.0) return 0.963153958321 + isyst * 0.00292340044249;
    if (fabs(eta) < 1.6 && (pt) < 35.0) return 0.968454778194 + isyst * 0.00477183238945;
    if (fabs(eta) < 2.1 && (pt) < 35.0) return 0.975835382938 + isyst * 0.00509899579765;
    if (fabs(eta) < 2.4 && (pt) < 35.0) return 0.948253929615 + isyst * 0.0105740329937;
    if (fabs(eta) < 0.8 && (pt) < 40.0) return 0.959200024605 + isyst * 0.00139179409029;
    if (fabs(eta) < 1.25 && (pt) < 40.0) return 0.968031227589 + isyst * 0.00224938789357;
    if (fabs(eta) < 1.6 && (pt) < 40.0) return 0.971272051334 + isyst * 0.00372267994448;
    if (fabs(eta) < 2.1 && (pt) < 40.0) return 0.978733003139 + isyst * 0.00398852793835;
    if (fabs(eta) < 2.4 && (pt) < 40.0) return 0.960308611393 + isyst * 0.00852134685407;
    if (fabs(eta) < 0.8 && (pt) < 50.0) return 0.962569653988 + isyst * 0.00092782418312;
    if (fabs(eta) < 1.25 && (pt) < 50.0) return 0.970577657223 + isyst * 0.00145078195362;
    if (fabs(eta) < 1.6 && (pt) < 50.0) return 0.973040103912 + isyst * 0.0024068292189;
    if (fabs(eta) < 2.1 && (pt) < 50.0) return 0.980093002319 + isyst * 0.00272622285588;
    if (fabs(eta) < 2.4 && (pt) < 50.0) return 0.965112805367 + isyst * 0.00614012492631;
    if (fabs(eta) < 0.8 && (pt) < 70.0) return 0.965936183929 + isyst * 0.00165980347205;
    if (fabs(eta) < 1.25 && (pt) < 70.0) return 0.972020506859 + isyst * 0.00257143804231;
    if (fabs(eta) < 1.6 && (pt) < 70.0) return 0.974364995956 + isyst * 0.00417665070298;
    if (fabs(eta) < 2.1 && (pt) < 70.0) return 0.980487048626 + isyst * 0.004730855274;
    if (fabs(eta) < 2.4 && (pt) < 70.0) return 0.968793809414 + isyst * 0.0105576051563;
    if (fabs(eta) < 0.8 && (pt) < 100.0) return 0.969938099384 + isyst * 0.0044036627819;
    if (fabs(eta) < 1.25 && (pt) < 100.0) return 0.975994884968 + isyst * 0.00688721550919;
    if (fabs(eta) < 1.6 && (pt) < 100.0) return 0.973707675934 + isyst * 0.0110610221474;
    if (fabs(eta) < 2.1 && (pt) < 100.0) return 0.981661677361 + isyst * 0.0116687716932;
    if (fabs(eta) < 2.4 && (pt) < 100.0) return 0.971915721893 + isyst * 0.02531338826;
    if (fabs(eta) < 0.8 && (pt) < 200.0) return 0.969920158386 + isyst * 0.00716663026926;
    if (fabs(eta) < 1.25 && (pt) < 200.0) return 0.979286432266 + isyst * 0.0115877950809;
    if (fabs(eta) < 1.6 && (pt) < 200.0) return 0.97321587801 + isyst * 0.0183953880798;
    if (fabs(eta) < 2.1 && (pt) < 200.0) return 0.987339615822 + isyst * 0.0181995985321;
    if (fabs(eta) < 2.4 && (pt) < 200.0) return 0.975920677185 + isyst * 0.0369551241269;
    if (fabs(eta) < 0.8 && (pt) < 300.0) return 0.963103115559 + isyst * 0.0244179854831;
    if (fabs(eta) < 1.25 && (pt) < 300.0) return 0.980341851711 + isyst * 0.0407348323478;
    if (fabs(eta) < 1.6 && (pt) < 300.0) return 0.982683956623 + isyst * 0.0649400621504;
    if (fabs(eta) < 2.1 && (pt) < 300.0) return 0.989495813847 + isyst * 0.0643094823766;
    if (fabs(eta) < 2.4 && (pt) < 300.0) return 0.985507249832 + isyst * 0.168399618706;
    if (fabs(eta) < 0.8) return 0.969696998596 + isyst * 0.0537954766423;
    if (fabs(eta) < 1.25) return 0.995433807373 + isyst * 0.0952363610997;
    if (fabs(eta) < 1.6) return 0.984615385532 + isyst * 0.173386311244;
    if (fabs(eta) < 2.1) return 1.0 + isyst * 0.16552117772;
    if (fabs(eta) < 2.4) return 1.0 + isyst * 0.57735026919;
    printf("WARNING in trigeff_el_trail(): the given phase-space (%f, %f) did not fall under any range!\n", eta, pt);
    return 1;
}

float trigeff_mu_muon(float eta, float pt, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if (fabs(eta) < 0.8 && (pt) < 10.0) return 0.0 + isyst * 0.0;
    if (fabs(eta) < 1.25 && (pt) < 10.0) return 0.0 + isyst * 0.0;
    if (fabs(eta) < 1.6 && (pt) < 10.0) return 0.0 + isyst * 0.0;
    if (fabs(eta) < 2.1 && (pt) < 10.0) return 0.0 + isyst * 0.0;
    if (fabs(eta) < 2.4 && (pt) < 10.0) return 0.0 + isyst * 0.0;
    if (fabs(eta) < 0.8 && (pt) < 20.0) return 0.0181972403079 + isyst * 0.00119526848508;
    if (fabs(eta) < 1.25 && (pt) < 20.0) return 0.0176960453391 + isyst * 0.00176760473795;
    if (fabs(eta) < 1.6 && (pt) < 20.0) return 0.017584098503 + isyst * 0.00213540719849;
    if (fabs(eta) < 2.1 && (pt) < 20.0) return 0.0156885534525 + isyst * 0.00215162356892;
    if (fabs(eta) < 2.4 && (pt) < 20.0) return 0.0140405613929 + isyst * 0.0033325439905;
    if (fabs(eta) < 0.8 && (pt) < 25.0) return 0.377397894859 + isyst * 0.0082362595628;
    if (fabs(eta) < 1.25 && (pt) < 25.0) return 0.366666674614 + isyst * 0.0122122975578;
    if (fabs(eta) < 1.6 && (pt) < 25.0) return 0.363084107637 + isyst * 0.015207508362;
    if (fabs(eta) < 2.1 && (pt) < 25.0) return 0.324675321579 + isyst * 0.0159339210893;
    if (fabs(eta) < 2.4 && (pt) < 25.0) return 0.302649945021 + isyst * 0.0234490132231;
    if (fabs(eta) < 0.8 && (pt) < 30.0) return 0.932249307632 + isyst * 0.0148961177474;
    if (fabs(eta) < 1.25 && (pt) < 30.0) return 0.906476736069 + isyst * 0.0215508427316;
    if (fabs(eta) < 1.6 && (pt) < 30.0) return 0.894642829895 + isyst * 0.0275083485621;
    if (fabs(eta) < 2.1 && (pt) < 30.0) return 0.841351687908 + isyst * 0.0297875666758;
    if (fabs(eta) < 2.4 && (pt) < 30.0) return 0.698412716389 + isyst * 0.0433917737013;
    if (fabs(eta) < 0.8 && (pt) < 35.0) return 0.928998529911 + isyst * 0.0149406596043;
    if (fabs(eta) < 1.25 && (pt) < 35.0) return 0.907245576382 + isyst * 0.0220869189574;
    if (fabs(eta) < 1.6 && (pt) < 35.0) return 0.90794980526 + isyst * 0.0283788101143;
    if (fabs(eta) < 2.1 && (pt) < 35.0) return 0.828695118427 + isyst * 0.0306135033025;
    if (fabs(eta) < 2.4 && (pt) < 35.0) return 0.759999990463 + isyst * 0.045363489216;
    if (fabs(eta) < 0.8 && (pt) < 40.0) return 0.92997610569 + isyst * 0.0154429315447;
    if (fabs(eta) < 1.25 && (pt) < 40.0) return 0.903132259846 + isyst * 0.0223268025375;
    if (fabs(eta) < 1.6 && (pt) < 40.0) return 0.926670014858 + isyst * 0.0299454328104;
    if (fabs(eta) < 2.1 && (pt) < 40.0) return 0.853503167629 + isyst * 0.0317431056864;
    if (fabs(eta) < 2.4 && (pt) < 40.0) return 0.788944721222 + isyst * 0.0486221975168;
    if (fabs(eta) < 0.8 && (pt) < 50.0) return 0.926731348038 + isyst * 0.0116314387466;
    if (fabs(eta) < 1.25 && (pt) < 50.0) return 0.910960018635 + isyst * 0.0169895079832;
    if (fabs(eta) < 1.6 && (pt) < 50.0) return 0.916197955608 + isyst * 0.0222194843578;
    if (fabs(eta) < 2.1 && (pt) < 50.0) return 0.845889210701 + isyst * 0.0231759236185;
    if (fabs(eta) < 2.4 && (pt) < 50.0) return 0.814382910728 + isyst * 0.0378940571833;
    if (fabs(eta) < 0.8 && (pt) < 70.0) return 0.92620575428 + isyst * 0.00960852138474;
    if (fabs(eta) < 1.25 && (pt) < 70.0) return 0.908558964729 + isyst * 0.014104923717;
    if (fabs(eta) < 1.6 && (pt) < 70.0) return 0.908719360828 + isyst * 0.0183733722779;
    if (fabs(eta) < 2.1 && (pt) < 70.0) return 0.854216873646 + isyst * 0.0195362087315;
    if (fabs(eta) < 2.4 && (pt) < 70.0) return 0.822591364384 + isyst * 0.0315622878459;
    if (fabs(eta) < 0.8 && (pt) < 100.0) return 0.917802810669 + isyst * 0.0107670782505;
    if (fabs(eta) < 1.25 && (pt) < 100.0) return 0.902871012688 + isyst * 0.0156652558873;
    if (fabs(eta) < 1.6 && (pt) < 100.0) return 0.88211786747 + isyst * 0.0203629028433;
    if (fabs(eta) < 2.1 && (pt) < 100.0) return 0.846651017666 + isyst * 0.0214313658185;
    if (fabs(eta) < 2.4 && (pt) < 100.0) return 0.800921678543 + isyst * 0.0364609147821;
    if (fabs(eta) < 0.8 && (pt) < 200.0) return 0.919220805168 + isyst * 0.0123589448133;
    if (fabs(eta) < 1.25 && (pt) < 200.0) return 0.895772457123 + isyst * 0.0181888953127;
    if (fabs(eta) < 1.6 && (pt) < 200.0) return 0.841079950333 + isyst * 0.0230047655697;
    if (fabs(eta) < 2.1 && (pt) < 200.0) return 0.837361752987 + isyst * 0.0251055650399;
    if (fabs(eta) < 2.4 && (pt) < 200.0) return 0.818181812763 + isyst * 0.0467037099035;
    if (fabs(eta) < 0.8 && (pt) < 300.0) return 0.880402028561 + isyst * 0.0407900582694;
    if (fabs(eta) < 1.25 && (pt) < 300.0) return 0.854117631912 + isyst * 0.0610426004009;
    if (fabs(eta) < 1.6 && (pt) < 300.0) return 0.821739137173 + isyst * 0.080676334791;
    if (fabs(eta) < 2.1 && (pt) < 300.0) return 0.87634408474 + isyst * 0.094023648453;
    if (fabs(eta) < 2.4 && (pt) < 300.0) return 0.676470577717 + isyst * 0.182634563202;
    if (fabs(eta) < 0.8) return 0.886363625526 + isyst * 0.0974680638906;
    if (fabs(eta) < 1.25) return 0.85526317358 + isyst * 0.14449267998;
    if (fabs(eta) < 1.6) return 0.741935491562 + isyst * 0.204182377845;
    if (fabs(eta) < 2.1) return 0.925925910473 + isyst * 0.256995802403;
    if (fabs(eta) < 2.4) return 0.0 + isyst * 0.0;
    printf("WARNING in trigeff_mu_muon(): the given phase-space (%f, %f) did not fall under any range!\n", eta, pt);
    return 1;
}

float lepsf_MuMediumPOG_MuTightVVV_v2(float pt, float eta, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if ((pt) < 25.0 && fabs(eta) < 0.9) return 0.925597071648 + isyst * 0.00149392509654;
    if ((pt) < 30.0 && fabs(eta) < 0.9) return 0.935978472233 + isyst * 0.00110756404918;
    if ((pt) < 40.0 && fabs(eta) < 0.9) return 0.953309178352 + isyst * 0.000470867389614;
    if ((pt) < 50.0 && fabs(eta) < 0.9) return 0.964556634426 + isyst * 0.000349571697355;
    if ((pt) < 60.0 && fabs(eta) < 0.9) return 0.970992326736 + isyst * 0.00028242928435;
    if ((pt) < 120.0 && fabs(eta) < 0.9) return 0.983958184719 + isyst * 0.000634456097094;
    if ((pt) < 1200.0 && fabs(eta) < 0.9) return 0.998649656773 + isyst * 0.000961262600414;
    if ((pt) < 25.0 && fabs(eta) < 1.2) return 0.914257586002 + isyst * 0.00337676832016;
    if ((pt) < 30.0 && fabs(eta) < 1.2) return 0.933219134808 + isyst * 0.00232727214725;
    if ((pt) < 40.0 && fabs(eta) < 1.2) return 0.94868272543 + isyst * 0.000980580532727;
    if ((pt) < 50.0 && fabs(eta) < 1.2) return 0.96019166708 + isyst * 0.000677483868841;
    if ((pt) < 60.0 && fabs(eta) < 1.2) return 0.968595445156 + isyst * 0.00113420287253;
    if ((pt) < 120.0 && fabs(eta) < 1.2) return 0.982807934284 + isyst * 0.00124166255845;
    if ((pt) < 1200.0 && fabs(eta) < 1.2) return 0.995942592621 + isyst * 0.00370077843517;
    if ((pt) < 25.0 && fabs(eta) < 2.1) return 0.92449337244 + isyst * 0.00244436980171;
    if ((pt) < 30.0 && fabs(eta) < 2.1) return 0.936849117279 + isyst * 0.00173741444398;
    if ((pt) < 40.0 && fabs(eta) < 2.1) return 0.947120904922 + isyst * 0.000809172482436;
    if ((pt) < 50.0 && fabs(eta) < 2.1) return 0.959933876991 + isyst * 0.000574496176315;
    if ((pt) < 60.0 && fabs(eta) < 2.1) return 0.968874752522 + isyst * 0.000988507251817;
    if ((pt) < 120.0 && fabs(eta) < 2.1) return 0.983020961285 + isyst * 0.00110401331352;
    if ((pt) < 1200.0 && fabs(eta) < 2.1) return 1.00674164295 + isyst * 0.00371229386528;
    if ((pt) < 25.0) return 0.799259185791 + isyst * 0.0041982245494;
    if ((pt) < 30.0) return 0.823484182358 + isyst * 0.00312842585282;
    if ((pt) < 40.0) return 0.854889392853 + isyst * 0.00157464275873;
    if ((pt) < 50.0) return 0.879745423794 + isyst * 0.00131191233773;
    if ((pt) < 60.0) return 0.904842376709 + isyst * 0.00230472703078;
    if ((pt) < 120.0) return 0.931934773922 + isyst * 0.00274829269756;
    if ((pt) < 1200.0) return 1.00346159935 + isyst * 0.0124157090494;
    printf("WARNING in lepsf_MuMediumPOG_MuTightVVV_v2(): the given phase-space (%f, %f) did not fall under any range!\n", pt, eta);
    return 1;
}

float lepsf_MuMediumPOG_MuTightVVV3l_v2(float pt, float eta, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if ((pt) < 25.0 && fabs(eta) < 0.9) return 0.94525462389 + isyst * 0.00136056937261;
    if ((pt) < 30.0 && fabs(eta) < 0.9) return 0.960446059704 + isyst * 0.000777744646118;
    if ((pt) < 40.0 && fabs(eta) < 0.9) return 0.976442217827 + isyst * 0.000304648180747;
    if ((pt) < 50.0 && fabs(eta) < 0.9) return 0.98465770483 + isyst * 0.00020383373952;
    if ((pt) < 60.0 && fabs(eta) < 0.9) return 0.988770961761 + isyst * 0.000344183459314;
    if ((pt) < 120.0 && fabs(eta) < 0.9) return 0.994172751904 + isyst * 0.00040507092635;
    if ((pt) < 1200.0 && fabs(eta) < 0.9) return 0.999082803726 + isyst * 0.00193518161167;
    if ((pt) < 25.0 && fabs(eta) < 1.2) return 0.933608353138 + isyst * 0.00288189540584;
    if ((pt) < 30.0 && fabs(eta) < 1.2) return 0.956573188305 + isyst * 0.00105858280735;
    if ((pt) < 40.0 && fabs(eta) < 1.2) return 0.97286516428 + isyst * 0.000629017215926;
    if ((pt) < 50.0 && fabs(eta) < 1.2) return 0.982085347176 + isyst * 0.000388054852022;
    if ((pt) < 60.0 && fabs(eta) < 1.2) return 0.985915184021 + isyst * 0.000642751942934;
    if ((pt) < 120.0 && fabs(eta) < 1.2) return 0.992436408997 + isyst * 0.000772290903332;
    if ((pt) < 1200.0 && fabs(eta) < 1.2) return 0.999902963638 + isyst * 0.00160911104624;
    if ((pt) < 25.0 && fabs(eta) < 2.1) return 0.954884111881 + isyst * 0.00302796515213;
    if ((pt) < 30.0 && fabs(eta) < 2.1) return 0.967316865921 + isyst * 0.000639207420765;
    if ((pt) < 40.0 && fabs(eta) < 2.1) return 0.980427980423 + isyst * 0.0005072644198;
    if ((pt) < 50.0 && fabs(eta) < 2.1) return 0.990154087543 + isyst * 0.00016492350584;
    if ((pt) < 60.0 && fabs(eta) < 2.1) return 0.995615124702 + isyst * 0.000568600610674;
    if ((pt) < 120.0 && fabs(eta) < 2.1) return 1.00136506557 + isyst * 0.000696219628136;
    if ((pt) < 1200.0 && fabs(eta) < 2.1) return 1.00947761536 + isyst * 0.00311826624537;
    if ((pt) < 25.0) return 0.875713825226 + isyst * 0.00334365530581;
    if ((pt) < 30.0) return 0.907857954502 + isyst * 0.00112338481774;
    if ((pt) < 40.0) return 0.939255356789 + isyst * 0.00104863909459;
    if ((pt) < 50.0) return 0.960826158524 + isyst * 0.00083715871379;
    if ((pt) < 60.0) return 0.969234347343 + isyst * 0.00150125228949;
    if ((pt) < 120.0) return 0.979165613651 + isyst * 0.00198287256778;
    if ((pt) < 1200.0) return 1.00263929367 + isyst * 0.0114839491566;
    printf("WARNING in lepsf_MuMediumPOG_MuTightVVV3l_v2(): the given phase-space (%f, %f) did not fall under any range!\n", pt, eta);
    return 1;
}

float lepsf_EGammaMediumPOGMVA_EGammaVVV3l_v2(float pt, float eta, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if ((pt) < 30.0 && fabs(eta) < 1.0) return 0.954154133797 + isyst * 0.00143712383466;
    if ((pt) < 40.0 && fabs(eta) < 1.0) return 0.967395663261 + isyst * 0.000611815232638;
    if ((pt) < 50.0 && fabs(eta) < 1.0) return 0.972688913345 + isyst * 0.000459584202635;
    if ((pt) < 2000.0 && fabs(eta) < 1.0) return 0.971450805664 + isyst * 0.000715516298791;
    if ((pt) < 30.0 && fabs(eta) < 1.4442) return 0.928322196007 + isyst * 0.00285288574254;
    if ((pt) < 40.0 && fabs(eta) < 1.4442) return 0.938621044159 + isyst * 0.00134062629996;
    if ((pt) < 50.0 && fabs(eta) < 1.4442) return 0.947251141071 + isyst * 0.00100572949582;
    if ((pt) < 2000.0 && fabs(eta) < 1.4442) return 0.949140846729 + isyst * 0.00149810977307;
    if ((pt) < 30.0 && fabs(eta) < 1.56) return 0.984156966209 + isyst * 0.00979809229708;
    if ((pt) < 40.0 && fabs(eta) < 1.56) return 0.984381318092 + isyst * 0.00554469338609;
    if ((pt) < 50.0 && fabs(eta) < 1.56) return 0.960480153561 + isyst * 0.00209633094793;
    if ((pt) < 2000.0 && fabs(eta) < 1.56) return 0.94547688961 + isyst * 0.00617510158806;
    if ((pt) < 30.0 && fabs(eta) < 2.0) return 0.827958226204 + isyst * 0.00470557878145;
    if ((pt) < 40.0 && fabs(eta) < 2.0) return 0.865741193295 + isyst * 0.00179886648022;
    if ((pt) < 50.0 && fabs(eta) < 2.0) return 0.887886404991 + isyst * 0.00147118323875;
    if ((pt) < 2000.0 && fabs(eta) < 2.0) return 0.903809905052 + isyst * 0.00258680521333;
    if ((pt) < 30.0) return 0.723212182522 + isyst * 0.00406150326347;
    if ((pt) < 40.0) return 0.763825893402 + isyst * 0.00214794247781;
    if ((pt) < 50.0) return 0.813915252686 + isyst * 0.00202700865459;
    if ((pt) < 2000.0) return 0.873283565044 + isyst * 0.00381863723574;
    printf("WARNING in lepsf_EGammaMediumPOGMVA_EGammaVVV3l_v2(): the given phase-space (%f, %f) did not fall under any range!\n", pt, eta);
    return 1;
}

float lepsf_EGammaTightPOGMVA_EGammaVVV_v2(float pt, float eta, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if ((pt) < 30.0 && fabs(eta) < 1.0) return 0.937993526459 + isyst * 0.00186250539227;
    if ((pt) < 40.0 && fabs(eta) < 1.0) return 0.948573231697 + isyst * 0.00079991772711;
    if ((pt) < 50.0 && fabs(eta) < 1.0) return 0.95408308506 + isyst * 0.000586800118303;
    if ((pt) < 2000.0 && fabs(eta) < 1.0) return 0.962138712406 + isyst * 0.000857039759975;
    if ((pt) < 30.0 && fabs(eta) < 1.4442) return 0.932696223259 + isyst * 0.00392172588756;
    if ((pt) < 40.0 && fabs(eta) < 1.4442) return 0.937459051609 + isyst * 0.00186365028397;
    if ((pt) < 50.0 && fabs(eta) < 1.4442) return 0.940408110619 + isyst * 0.00136372058286;
    if ((pt) < 2000.0 && fabs(eta) < 1.4442) return 0.946673810482 + isyst * 0.00209300378748;
    if ((pt) < 30.0 && fabs(eta) < 1.56) return 0.985139966011 + isyst * 0.0158431249836;
    if ((pt) < 40.0 && fabs(eta) < 1.56) return 0.978415548801 + isyst * 0.00807562538375;
    if ((pt) < 50.0 && fabs(eta) < 1.56) return 0.962861895561 + isyst * 0.00607426910695;
    if ((pt) < 2000.0 && fabs(eta) < 1.56) return 0.94798797369 + isyst * 0.00947013122544;
    if ((pt) < 30.0 && fabs(eta) < 2.0) return 0.804668962955 + isyst * 0.00680292264433;
    if ((pt) < 40.0 && fabs(eta) < 2.0) return 0.824794232845 + isyst * 0.00279962950591;
    if ((pt) < 50.0 && fabs(eta) < 2.0) return 0.840912163258 + isyst * 0.00227706613553;
    if ((pt) < 2000.0 && fabs(eta) < 2.0) return 0.861829400063 + isyst * 0.00349987495151;
    if ((pt) < 30.0) return 0.611690700054 + isyst * 0.00626353597885;
    if ((pt) < 40.0) return 0.617916941643 + isyst * 0.00325818329423;
    if ((pt) < 50.0) return 0.644828796387 + isyst * 0.00298628727302;
    if ((pt) < 2000.0) return 0.714055359364 + isyst * 0.00508280205632;
    printf("WARNING in lepsf_EGammaTightPOGMVA_EGammaVVV_v2(): the given phase-space (%f, %f) did not fall under any range!\n", pt, eta);
    return 1;
}

//______________________________________________________________________________________
float lepsf_EGammaReco(float PT, float Eta)
{
    float pt  = std::min((float)499.,PT);
    float eta = std::min((float)2.49,Eta);
    if (pt < 500.0 && fabs(eta) < -2.45 ) return 1.31760430336;
    if (pt < 500.0 && fabs(eta) < -2.4  ) return 1.11378002167;
    if (pt < 500.0 && fabs(eta) < -2.3  ) return 1.02462530136;
    if (pt < 500.0 && fabs(eta) < -2.2  ) return 1.013641119;
    if (pt < 500.0 && fabs(eta) < -2.0  ) return 1.00727653503;
    if (pt < 500.0 && fabs(eta) < -1.8  ) return 0.994818627834;
    if (pt < 500.0 && fabs(eta) < -1.63 ) return 0.994786262512;
    if (pt < 500.0 && fabs(eta) < -1.566) return 0.991631805897;
    if (pt < 500.0 && fabs(eta) < -1.444) return 0.963128507137;
    if (pt < 500.0 && fabs(eta) < -1.2  ) return 0.989701330662;
    if (pt < 500.0 && fabs(eta) < -1.0  ) return 0.985655725002;
    if (pt < 500.0 && fabs(eta) < -0.6  ) return 0.981595098972;
    if (pt < 500.0 && fabs(eta) < -0.4  ) return 0.984678268433;
    if (pt < 500.0 && fabs(eta) < -0.2  ) return 0.981613874435;
    if (pt < 500.0 && fabs(eta) < 0.0   ) return 0.980432569981;
    if (pt < 500.0 && fabs(eta) < 0.2   ) return 0.984552025795;
    if (pt < 500.0 && fabs(eta) < 0.4   ) return 0.988764047623;
    if (pt < 500.0 && fabs(eta) < 0.6   ) return 0.987742602825;
    if (pt < 500.0 && fabs(eta) < 1.0   ) return 0.987742602825;
    if (pt < 500.0 && fabs(eta) < 1.2   ) return 0.987742602825;
    if (pt < 500.0 && fabs(eta) < 1.444 ) return 0.98767966032;
    if (pt < 500.0 && fabs(eta) < 1.566 ) return 0.967597782612;
    if (pt < 500.0 && fabs(eta) < 1.63  ) return 0.989626526833;
    if (pt < 500.0 && fabs(eta) < 1.8   ) return 0.992761135101;
    if (pt < 500.0 && fabs(eta) < 2.0   ) return 0.991761088371;
    if (pt < 500.0 && fabs(eta) < 2.2   ) return 0.99794024229;
    if (pt < 500.0 && fabs(eta) < 2.3   ) return 1.00103735924;
    if (pt < 500.0 && fabs(eta) < 2.4   ) return 0.989506840706;
    if (pt < 500.0 && fabs(eta) < 2.45  ) return 0.970518887043;
    if (pt < 500.0 && fabs(eta) < 2.5   ) return 0.906666696072;
    return 1;
}

float lepsf_EGammaReco_unc(float PT, float Eta)
{
    float pt  = std::min((float)499.,PT);
    float eta = std::min((float)2.49,Eta);
    if(eta< -2.45) return 0.0182387;
    if(eta<  -2.4) return 0.0110667;
    if(eta<  -2.3) return 0.00815835;
    if(eta<  -2.2) return 0.00713343;
    if(eta<  -2.0) return 0.00420281;
    if(eta<  -1.8) return 0.00649267;
    if(eta< -1.63) return 0.00516608;
    if(eta<-1.566) return 0.00551198;
    if(eta<-1.444) return 0.0260302;
    if(eta<  -1.2) return 0.00359897;
    if(eta<  -1.0) return 0.00506368;
    if(eta<  -0.6) return 0.00331157;
    if(eta<  -0.4) return 0.0061287;
    if(eta<  -0.2) return 0.00635848;
    if(eta<   0.0) return 0.00530156;
    if(eta<   0.2) return 0.00530156;
    if(eta<   0.4) return 0.00635848;
    if(eta<   0.6) return 0.0061287;
    if(eta<   1.0) return 0.00331157;
    if(eta<   1.2) return 0.00506368;
    if(eta< 1.444) return 0.00359897;
    if(eta< 1.566) return 0.0260302;
    if(eta<  1.63) return 0.00551198;
    if(eta<   1.8) return 0.00516608;
    if(eta<   2.0) return 0.00649267;
    if(eta<   2.2) return 0.00420281;
    if(eta<   2.3) return 0.00713343;
    if(eta<   2.4) return 0.00815835;
    if(eta<  2.45) return 0.0110667;
    if(eta<   2.5) return 0.0182387;
    return 0;
}

//______________________________________________________________________________________
float lepsf_EGammaTightID(float PT, float Eta)
{
    float pt  = std::min((float)499.,PT);
    float eta = std::min((float)2.49,Eta);
    if (pt < 20.0  && fabs(eta) < -2.0  ) return 0.806557357311;
    if (pt < 35.0  && fabs(eta) < -2.0  ) return 0.88245934248;
    if (pt < 50.0  && fabs(eta) < -2.0  ) return 0.918840587139;
    if (pt < 90.0  && fabs(eta) < -2.0  ) return 0.940397322178;
    if (pt < 150.0 && fabs(eta) < -2.0  ) return 1.05108559132;
    if (pt < 500.0 && fabs(eta) < -2.0  ) return 1.05108559132;
    if (pt < 20.0  && fabs(eta) < -1.566) return 0.828571438789;
    if (pt < 35.0  && fabs(eta) < -1.566) return 0.927487373352;
    if (pt < 50.0  && fabs(eta) < -1.566) return 0.966987609863;
    if (pt < 90.0  && fabs(eta) < -1.566) return 0.980964481831;
    if (pt < 150.0 && fabs(eta) < -1.566) return 1.00592422485;
    if (pt < 500.0 && fabs(eta) < -1.566) return 1.00592422485;
    if (pt < 20.0  && fabs(eta) < -1.444) return 1.03286385536;
    if (pt < 35.0  && fabs(eta) < -1.444) return 1.00759494305;
    if (pt < 50.0  && fabs(eta) < -1.444) return 0.988195598125;
    if (pt < 90.0  && fabs(eta) < -1.444) return 0.995391726494;
    if (pt < 150.0 && fabs(eta) < -1.444) return 1.10410559177;
    if (pt < 500.0 && fabs(eta) < -1.444) return 1.10410559177;
    if (pt < 20.0  && fabs(eta) < -0.8  ) return 1.00775194168;
    if (pt < 35.0  && fabs(eta) < -0.8  ) return 0.972039461136;
    if (pt < 50.0  && fabs(eta) < -0.8  ) return 0.974666655064;
    if (pt < 90.0  && fabs(eta) < -0.8  ) return 0.971674859524;
    if (pt < 150.0 && fabs(eta) < -0.8  ) return 0.98948597908;
    if (pt < 500.0 && fabs(eta) < -0.8  ) return 0.98948597908;
    if (pt < 20.0  && fabs(eta) < 0.0   ) return 0.94072163105;
    if (pt < 35.0  && fabs(eta) < 0.0   ) return 0.952998399734;
    if (pt < 50.0  && fabs(eta) < 0.0   ) return 0.953457474709;
    if (pt < 90.0  && fabs(eta) < 0.0   ) return 0.953086435795;
    if (pt < 150.0 && fabs(eta) < 0.0   ) return 0.975495934486;
    if (pt < 500.0 && fabs(eta) < 0.0   ) return 0.975495934486;
    if (pt < 20.0  && fabs(eta) < 0.8   ) return 0.945876300335;
    if (pt < 35.0  && fabs(eta) < 0.8   ) return 0.981996715069;
    if (pt < 50.0  && fabs(eta) < 0.8   ) return 0.979811549187;
    if (pt < 90.0  && fabs(eta) < 0.8   ) return 0.977528095245;
    if (pt < 150.0 && fabs(eta) < 0.8   ) return 1.0118906498;
    if (pt < 500.0 && fabs(eta) < 0.8   ) return 1.0118906498;
    if (pt < 20.0  && fabs(eta) < 1.444 ) return 0.989769816399;
    if (pt < 35.0  && fabs(eta) < 1.444 ) return 0.975206613541;
    if (pt < 50.0  && fabs(eta) < 1.444 ) return 0.97463285923;
    if (pt < 90.0  && fabs(eta) < 1.444 ) return 0.97893434763;
    if (pt < 150.0 && fabs(eta) < 1.444 ) return 1.01072704792;
    if (pt < 500.0 && fabs(eta) < 1.444 ) return 1.01072704792;
    if (pt < 20.0  && fabs(eta) < 1.566 ) return 1.03398060799;
    if (pt < 35.0  && fabs(eta) < 1.566 ) return 0.974874377251;
    if (pt < 50.0  && fabs(eta) < 1.566 ) return 0.966386556625;
    if (pt < 90.0  && fabs(eta) < 1.566 ) return 0.979907274246;
    if (pt < 150.0 && fabs(eta) < 1.566 ) return 1.00716328621;
    if (pt < 500.0 && fabs(eta) < 1.566 ) return 1.00716328621;
    if (pt < 20.0  && fabs(eta) < 2.0   ) return 0.827485382557;
    if (pt < 35.0  && fabs(eta) < 2.0   ) return 0.908937633038;
    if (pt < 50.0  && fabs(eta) < 2.0   ) return 0.95782315731;
    if (pt < 90.0  && fabs(eta) < 2.0   ) return 0.968553483486;
    if (pt < 150.0 && fabs(eta) < 2.0   ) return 0.988262891769;
    if (pt < 500.0 && fabs(eta) < 2.0   ) return 0.988262891769;
    if (pt < 20.0  && fabs(eta) < 2.5   ) return 0.797014951706;
    if (pt < 35.0  && fabs(eta) < 2.5   ) return 0.863321781158;
    if (pt < 50.0  && fabs(eta) < 2.5   ) return 0.907801389694;
    if (pt < 90.0  && fabs(eta) < 2.5   ) return 0.937662363052;
    if (pt < 150.0 && fabs(eta) < 2.5   ) return 1.02135682106;
    if (pt < 500.0 && fabs(eta) < 2.5   ) return 1.02135682106;
    return 1;
}

float lepsf_EGammaTightID_unc(float PT, float Eta)
{
    float pt  = std::min((float)499.,PT);
    float eta = std::min((float)2.49,Eta);
    if(pt<20.0 && eta<  -2.0) return 0.0180196;
    if(pt<35.0 && eta<  -2.0) return 0.0101198;
    if(pt<50.0 && eta<  -2.0) return 0.00903908;
    if(pt<90.0 && eta<  -2.0) return 0.00700136;
    if(pt<150. && eta<  -2.0) return 0.0222742;
    if(pt<500. && eta<  -2.0) return 0.0224318;
    if(pt<20.0 && eta<-1.566) return 0.0182791;
    if(pt<35.0 && eta<-1.566) return 0.0176261;
    if(pt<50.0 && eta<-1.566) return 0.00730306;
    if(pt<90.0 && eta<-1.566) return 0.00561478;
    if(pt<150. && eta<-1.566) return 0.0215596;
    if(pt<500. && eta<-1.566) return 0.0217223;
    if(pt<20.0 && eta<-1.444) return 0.106279;
    if(pt<35.0 && eta<-1.444) return 0.109913;
    if(pt<50.0 && eta<-1.444) return 0.0166871;
    if(pt<90.0 && eta<-1.444) return 0.0240068;
    if(pt<150. && eta<-1.444) return 0.0495689;
    if(pt<500. && eta<-1.444) return 0.0496399;
    if(pt<20.0 && eta<  -0.8) return 0.0272663;
    if(pt<35.0 && eta<  -0.8) return 0.0132931;
    if(pt<50.0 && eta<  -0.8) return 0.00686833;
    if(pt<90.0 && eta<  -0.8) return 0.0186735;
    if(pt<150. && eta<  -0.8) return 0.00867578;
    if(pt<500. && eta<  -0.8) return 0.00907265;
    if(pt<20.0 && eta<   0.0) return 0.025741;
    if(pt<35.0 && eta<   0.0) return 0.0150816;
    if(pt<50.0 && eta<   0.0) return 0.00472981;
    if(pt<90.0 && eta<   0.0) return 0.0168857;
    if(pt<150. && eta<   0.0) return 0.0126071;
    if(pt<500. && eta<   0.0) return 0.0128834;
    if(pt<20.0 && eta<   0.8) return 0.025741;
    if(pt<35.0 && eta<   0.8) return 0.0150816;
    if(pt<50.0 && eta<   0.8) return 0.00472981;
    if(pt<90.0 && eta<   0.8) return 0.0168857;
    if(pt<150. && eta<   0.8) return 0.0127268;
    if(pt<500. && eta<   0.8) return 0.0130006;
    if(pt<20.0 && eta< 1.444) return 0.0272663;
    if(pt<35.0 && eta< 1.444) return 0.0132931;
    if(pt<50.0 && eta< 1.444) return 0.00686833;
    if(pt<90.0 && eta< 1.444) return 0.0186735;
    if(pt<150. && eta< 1.444) return 0.0088888;
    if(pt<500. && eta< 1.444) return 0.00927657;
    if(pt<20.0 && eta< 1.566) return 0.106279;
    if(pt<35.0 && eta< 1.566) return 0.109913;
    if(pt<50.0 && eta< 1.566) return 0.0166871;
    if(pt<90.0 && eta< 1.566) return 0.0240068;
    if(pt<150. && eta< 1.566) return 0.049435;
    if(pt<500. && eta< 1.566) return 0.0495061;
    if(pt<20.0 && eta<   2.0) return 0.0182791;
    if(pt<35.0 && eta<   2.0) return 0.0176261;
    if(pt<50.0 && eta<   2.0) return 0.00730306;
    if(pt<90.0 && eta<   2.0) return 0.00561478;
    if(pt<150. && eta<   2.0) return 0.0215596;
    if(pt<500. && eta<   2.0) return 0.0217223;
    if(pt<20.0 && eta<   2.5) return 0.0180196;
    if(pt<35.0 && eta<   2.5) return 0.0101198;
    if(pt<50.0 && eta<   2.5) return 0.00903908;
    if(pt<90.0 && eta<   2.5) return 0.00700136;
    if(pt<150. && eta<   2.5) return 0.0222742;
    if(pt<500. && eta<   2.5) return 0.0224318;
    return 0;
}

//______________________________________________________________________________________
float lepsf_EGammaTightPOG_EGammaVVV_v1(float PT, float Eta)
{
    float pt  = std::min((float)1999.,PT);
    float eta = std::min((float)2.49,std::max((float)-2.49,Eta));
    if (pt < 30.0   && fabs(eta) < 1.0   ) return 0.980376899242;
    if (pt < 40.0   && fabs(eta) < 1.0   ) return 0.981454670429;
    if (pt < 50.0   && fabs(eta) < 1.0   ) return 0.980952382088;
    if (pt < 2000.0 && fabs(eta) < 1.0   ) return 0.976341068745;
    if (pt < 30.0   && fabs(eta) < 1.4442) return 0.945449829102;
    if (pt < 40.0   && fabs(eta) < 1.4442) return 0.94911891222;
    if (pt < 50.0   && fabs(eta) < 1.4442) return 0.95356208086;
    if (pt < 2000.0 && fabs(eta) < 1.4442) return 0.949157774448;
    if (pt < 30.0   && fabs(eta) < 1.56  ) return 0.938438951969;
    if (pt < 40.0   && fabs(eta) < 1.56  ) return 0.941834270954;
    if (pt < 50.0   && fabs(eta) < 1.56  ) return 0.947787821293;
    if (pt < 2000.0 && fabs(eta) < 1.56  ) return 0.952665507793;
    if (pt < 30.0   && fabs(eta) < 2.0   ) return 0.963943779469;
    if (pt < 40.0   && fabs(eta) < 2.0   ) return 0.971829116344;
    if (pt < 50.0   && fabs(eta) < 2.0   ) return 0.975824117661;
    if (pt < 2000.0 && fabs(eta) < 2.0   ) return 0.980078279972;
    if (pt < 30.0   && fabs(eta) < 2.5   ) return 0.984203636646;
    if (pt < 40.0   && fabs(eta) < 2.5   ) return 0.998542606831;
    if (pt < 50.0   && fabs(eta) < 2.5   ) return 1.00013875961;
    if (pt < 2000.0 && fabs(eta) < 2.5   ) return 1.00487089157;
    return 1;
}

float lepsf_EGammaTightPOG_EGammaVVV(float PT, float Eta, int version=0)
{
    float pt  = std::min((float)1199.,PT);
    float eta = std::min((float)2.39,std::max((float)-2.39,Eta));
    if (version == 0)
        return lepsf_EGammaTightPOG_EGammaVVV_v1(pt, eta);
    else if (version == 1)
        return lepsf_EGammaTightPOGMVA_EGammaVVV_v2(pt, eta);
    else if (version == -1)
        return lepsf_EGammaMediumPOGMVA_EGammaVVV3l_v2(pt, eta);
}


//______________________________________________________________________________________
float lepsf_EGammaVVV_EGammaVVVEle12(float PT, float Eta)
{
    float pt  = std::min((float)1999.,PT);
    float eta = std::min((float)2.49,std::max((float)-2.49,Eta));
    if ((pt) < 30.0   && fabs(eta) < 1.0   ) return 0.938784837723;
    if ((pt) < 40.0   && fabs(eta) < 1.0   ) return 0.956399559975;
    if ((pt) < 50.0   && fabs(eta) < 1.0   ) return 0.962966561317;
    if ((pt) < 2000.0 && fabs(eta) < 1.0   ) return 0.967466413975;
    if ((pt) < 30.0   && fabs(eta) < 1.4442) return 0.94966250658;
    if ((pt) < 40.0   && fabs(eta) < 1.4442) return 0.96033769846;
    if ((pt) < 50.0   && fabs(eta) < 1.4442) return 0.965217530727;
    if ((pt) < 2000.0 && fabs(eta) < 1.4442) return 0.969266951084;
    if ((pt) < 30.0   && fabs(eta) < 1.56  ) return 0.957857549191;
    if ((pt) < 40.0   && fabs(eta) < 1.56  ) return 0.962614357471;
    if ((pt) < 50.0   && fabs(eta) < 1.56  ) return 0.964548945427;
    if ((pt) < 2000.0 && fabs(eta) < 1.56  ) return 0.962951600552;
    if ((pt) < 30.0   && fabs(eta) < 2.0   ) return 0.958219587803;
    if ((pt) < 40.0   && fabs(eta) < 2.0   ) return 0.96611481905;
    if ((pt) < 50.0   && fabs(eta) < 2.0   ) return 0.971387922764;
    if ((pt) < 2000.0 && fabs(eta) < 2.0   ) return 0.974559724331;
    if ((pt) < 30.0   && fabs(eta) < 2.5   ) return 0.910284698009;
    if ((pt) < 40.0   && fabs(eta) < 2.5   ) return 0.947666943073;
    if ((pt) < 50.0   && fabs(eta) < 2.5   ) return 0.955771327019;
    if ((pt) < 2000.0 && fabs(eta) < 2.5   ) return 0.962957322598;
    return 1;
}

float lepsf_EGammaVVV_EGammaVVVEle12_unc(float PT, float Eta)
{
    float pt  = std::min((float)1999.,PT);
    float eta = std::min((float)2.49,std::max((float)-2.49,Eta));
    if ((pt) < 30.0   && fabs(eta) < 1.0   ) return 0.00219590521361;
    if ((pt) < 40.0   && fabs(eta) < 1.0   ) return 0.00127861103515;
    if ((pt) < 50.0   && fabs(eta) < 1.0   ) return 0.000316125299188;
    if ((pt) < 2000.0 && fabs(eta) < 1.0   ) return 0.00155382971572;
    if ((pt) < 30.0   && fabs(eta) < 1.4442) return 0.00368355725231;
    if ((pt) < 40.0   && fabs(eta) < 1.4442) return 0.00197332068038;
    if ((pt) < 50.0   && fabs(eta) < 1.4442) return 0.000220183866521;
    if ((pt) < 2000.0 && fabs(eta) < 1.4442) return 0.00265256114334;
    if ((pt) < 30.0   && fabs(eta) < 1.56  ) return 0.0115744391104;
    if ((pt) < 40.0   && fabs(eta) < 1.56  ) return 0.0059518655469;
    if ((pt) < 50.0   && fabs(eta) < 1.56  ) return 0.0055577892749;
    if ((pt) < 2000.0 && fabs(eta) < 1.56  ) return 0.00883849432663;
    if ((pt) < 30.0   && fabs(eta) < 2.0   ) return 0.00428889366748;
    if ((pt) < 40.0   && fabs(eta) < 2.0   ) return 0.00169359181774;
    if ((pt) < 50.0   && fabs(eta) < 2.0   ) return 0.00208029227053;
    if ((pt) < 2000.0 && fabs(eta) < 2.0   ) return 1.84578668625e-05;
    if ((pt) < 30.0   && fabs(eta) < 2.5   ) return 0.00477846357209;
    if ((pt) < 40.0   && fabs(eta) < 2.5   ) return 0.00277335535449;
    if ((pt) < 50.0   && fabs(eta) < 2.5   ) return 0.00289434846743;
    if ((pt) < 2000.0 && fabs(eta) < 2.5   ) return 0.00532928187002;
    return 0;
}

//______________________________________________________________________________________
float lepsf_EGammaVVV_EGammaVVVEleLead(float PT, float Eta)
{
    float pt  = std::min((float)1999.,PT);
    float eta = std::min((float)2.49,std::max((float)-2.49,Eta));
    if ((pt) < 30.0   && fabs(eta) < 1.0   ) return 0.938784837723;
    if ((pt) < 40.0   && fabs(eta) < 1.0   ) return 0.956399559975;
    if ((pt) < 50.0   && fabs(eta) < 1.0   ) return 0.962966561317;
    if ((pt) < 2000.0 && fabs(eta) < 1.0   ) return 0.967466413975;
    if ((pt) < 30.0   && fabs(eta) < 1.4442) return 0.94966250658;
    if ((pt) < 40.0   && fabs(eta) < 1.4442) return 0.96033769846;
    if ((pt) < 50.0   && fabs(eta) < 1.4442) return 0.965217530727;
    if ((pt) < 2000.0 && fabs(eta) < 1.4442) return 0.969266951084;
    if ((pt) < 30.0   && fabs(eta) < 1.56  ) return 0.957857549191;
    if ((pt) < 40.0   && fabs(eta) < 1.56  ) return 0.962614357471;
    if ((pt) < 50.0   && fabs(eta) < 1.56  ) return 0.964548945427;
    if ((pt) < 2000.0 && fabs(eta) < 1.56  ) return 0.962951600552;
    if ((pt) < 30.0   && fabs(eta) < 2.0   ) return 0.958219587803;
    if ((pt) < 40.0   && fabs(eta) < 2.0   ) return 0.96611481905;
    if ((pt) < 50.0   && fabs(eta) < 2.0   ) return 0.971387922764;
    if ((pt) < 2000.0 && fabs(eta) < 2.0   ) return 0.974559724331;
    if ((pt) < 30.0   && fabs(eta) < 2.5   ) return 0.910284698009;
    if ((pt) < 40.0   && fabs(eta) < 2.5   ) return 0.947666943073;
    if ((pt) < 50.0   && fabs(eta) < 2.5   ) return 0.955771327019;
    if ((pt) < 2000.0 && fabs(eta) < 2.5   ) return 0.962957322598;
    return 1;
}

float lepsf_EGammaVVV_EGammaVVVEleLead_unc(float PT, float Eta)
{
    float pt  = std::min((float)1999.,PT);
    float eta = std::min((float)2.49,std::max((float)-2.49,Eta));
    if ((pt) < 30.0   && fabs(eta) < 1.0   ) return 0.00219590521361;
    if ((pt) < 40.0   && fabs(eta) < 1.0   ) return 0.00127861103515;
    if ((pt) < 50.0   && fabs(eta) < 1.0   ) return 0.000316125299188;
    if ((pt) < 2000.0 && fabs(eta) < 1.0   ) return 0.00155382971572;
    if ((pt) < 30.0   && fabs(eta) < 1.4442) return 0.00368355725231;
    if ((pt) < 40.0   && fabs(eta) < 1.4442) return 0.00197332068038;
    if ((pt) < 50.0   && fabs(eta) < 1.4442) return 0.000220183866521;
    if ((pt) < 2000.0 && fabs(eta) < 1.4442) return 0.00265256114334;
    if ((pt) < 30.0   && fabs(eta) < 1.56  ) return 0.0115744391104;
    if ((pt) < 40.0   && fabs(eta) < 1.56  ) return 0.0059518655469;
    if ((pt) < 50.0   && fabs(eta) < 1.56  ) return 0.0055577892749;
    if ((pt) < 2000.0 && fabs(eta) < 1.56  ) return 0.00883849432663;
    if ((pt) < 30.0   && fabs(eta) < 2.0   ) return 0.00428889366748;
    if ((pt) < 40.0   && fabs(eta) < 2.0   ) return 0.00169359181774;
    if ((pt) < 50.0   && fabs(eta) < 2.0   ) return 0.00208029227053;
    if ((pt) < 2000.0 && fabs(eta) < 2.0   ) return 1.84578668625e-05;
    if ((pt) < 30.0   && fabs(eta) < 2.5   ) return 0.00477846357209;
    if ((pt) < 40.0   && fabs(eta) < 2.5   ) return 0.00277335535449;
    if ((pt) < 50.0   && fabs(eta) < 2.5   ) return 0.00289434846743;
    if ((pt) < 2000.0 && fabs(eta) < 2.5   ) return 0.00532928187002;
    return 0;
}

//______________________________________________________________________________________
float lepsf_MuReco(float PT, float Eta){
    float eta = std::min((float)2.39,std::max((float)-2.39,Eta));
    if(fabs(eta)<0.2) return 0.996996;
    if(fabs(eta)<0.4) return 0.997712;
    if(fabs(eta)<0.6) return 0.998078;
    if(fabs(eta)<0.8) return 0.997804;
    if(fabs(eta)<1.0) return 0.997971;
    if(fabs(eta)<1.2) return 0.997148;
    if(fabs(eta)<1.4) return 0.996227;
    if(fabs(eta)<1.6) return 0.995479;
    if(fabs(eta)<1.8) return 0.995781;
    if(fabs(eta)<2.0) return 0.993892;
    if(fabs(eta)<2.2) return 0.992943;
    if(fabs(eta)<2.4) return 0.987313;
    return 1;
}

float lepsf_MuReco_unc(float PT, float Eta){
    float eta = std::min((float)2.39,std::max((float)-2.39,Eta));
    if(fabs(eta)<0.2) return 7.28286e-05;
    if(fabs(eta)<0.4) return 8.21768e-05;
    if(fabs(eta)<0.6) return 7.12809e-05;
    if(fabs(eta)<0.8) return 7.44123e-05;
    if(fabs(eta)<1.0) return 0.000106739;
    if(fabs(eta)<1.2) return 0.000185882;
    if(fabs(eta)<1.4) return 0.000181271;
    if(fabs(eta)<1.6) return 0.000170523;
    if(fabs(eta)<1.8) return 0.000176;
    if(fabs(eta)<2.0) return 0.000234893;
    if(fabs(eta)<2.2) return 0.000328371;
    if(fabs(eta)<2.4) return 0.000856037;
    return 0;
}

//______________________________________________________________________________________
float lepsf_MuMediumID_BtoF(float PT, float Eta){
    float pt  = std::min((float)119.,PT);
    float eta = std::min((float)2.39,std::max((float)-2.39,Eta));
    if(pt<25.0 && fabs(eta)<0.9) return 0.991851;
    if(pt<25.0 && fabs(eta)<1.2) return 0.987454;
    if(pt<25.0 && fabs(eta)<2.1) return 0.98239;
    if(pt<25.0 && fabs(eta)<2.4) return 0.940947;
    if(pt<30.0 && fabs(eta)<0.9) return 0.991988;
    if(pt<30.0 && fabs(eta)<1.2) return 0.983919;
    if(pt<30.0 && fabs(eta)<2.1) return 0.981643;
    if(pt<30.0 && fabs(eta)<2.4) return 0.939569;
    if(pt<40.0 && fabs(eta)<0.9) return 0.997672;
    if(pt<40.0 && fabs(eta)<1.2) return 0.989657;
    if(pt<40.0 && fabs(eta)<2.1) return 0.984756;
    if(pt<40.0 && fabs(eta)<2.4) return 0.940388;
    if(pt<50.0 && fabs(eta)<0.9) return 0.99433;
    if(pt<50.0 && fabs(eta)<1.2) return 0.99157;
    if(pt<50.0 && fabs(eta)<2.1) return 0.989071;
    if(pt<50.0 && fabs(eta)<2.4) return 0.942787;
    if(pt<60.0 && fabs(eta)<0.9) return 0.9909;
    if(pt<60.0 && fabs(eta)<1.2) return 0.990928;
    if(pt<60.0 && fabs(eta)<2.1) return 0.987527;
    if(pt<60.0 && fabs(eta)<2.4) return 0.943489;
    if(pt<120. && fabs(eta)<0.9) return 1.00388;
    if(pt<120. && fabs(eta)<1.2) return 0.990419;
    if(pt<120. && fabs(eta)<2.1) return 0.991048;
    if(pt<120. && fabs(eta)<2.4) return 0.947859;
    return 1;
}

float lepsf_MuMediumID_BtoF_unc(float PT, float Eta){
    float pt  = std::min((float)119.,PT);
    float eta = std::min((float)2.39,std::max((float)-2.39,Eta));
    if(pt<25.0 && fabs(eta)<0.9) return 0.00288185;
    if(pt<25.0 && fabs(eta)<1.2) return 0.00329208;
    if(pt<25.0 && fabs(eta)<2.1) return 0.00164757;
    if(pt<25.0 && fabs(eta)<2.4) return 0.0027989;
    if(pt<30.0 && fabs(eta)<0.9) return 0.0165188;
    if(pt<30.0 && fabs(eta)<1.2) return 0.00146363;
    if(pt<30.0 && fabs(eta)<2.1) return 0.000785475;
    if(pt<30.0 && fabs(eta)<2.4) return 0.00159779;
    if(pt<40.0 && fabs(eta)<0.9) return 0.00027511;
    if(pt<40.0 && fabs(eta)<1.2) return 0.00139717;
    if(pt<40.0 && fabs(eta)<2.1) return 0.0183884;
    if(pt<40.0 && fabs(eta)<2.4) return 0.000857228;
    if(pt<50.0 && fabs(eta)<0.9) return 0.000217227;
    if(pt<50.0 && fabs(eta)<1.2) return 0.000355018;
    if(pt<50.0 && fabs(eta)<2.1) return 0.000247195;
    if(pt<50.0 && fabs(eta)<2.4) return 0.000839974;
    if(pt<60.0 && fabs(eta)<0.9) return 0.000770698;
    if(pt<60.0 && fabs(eta)<1.2) return 0.00110865;
    if(pt<60.0 && fabs(eta)<2.1) return 0.00081421;
    if(pt<60.0 && fabs(eta)<2.4) return 0.00254097;
    if(pt<120. && fabs(eta)<0.9) return 0.00193668;
    if(pt<120. && fabs(eta)<1.2) return 0.00258008;
    if(pt<120. && fabs(eta)<2.1) return 0.00196132;
    if(pt<120. && fabs(eta)<2.4) return 0.00543996;
    return 0;
}

float lepsf_MuMediumID_GH(float PT, float Eta){
    float pt  = std::min((float)119.,PT);
    float eta = std::min((float)2.39,std::max((float)-2.39,Eta));
    if(pt<25.0 && fabs(eta)<0.9) return 1.0012;
    if(pt<25.0 && fabs(eta)<1.2) return 1.00002;
    if(pt<25.0 && fabs(eta)<2.1) return 0.997079;
    if(pt<25.0 && fabs(eta)<2.4) return 0.983256;
    if(pt<30.0 && fabs(eta)<0.9) return 0.995387;
    if(pt<30.0 && fabs(eta)<1.2) return 0.998069;
    if(pt<30.0 && fabs(eta)<2.1) return 0.996599;
    if(pt<30.0 && fabs(eta)<2.4) return 0.978924;
    if(pt<40.0 && fabs(eta)<0.9) return 1.00129;
    if(pt<40.0 && fabs(eta)<1.2) return 0.997112;
    if(pt<40.0 && fabs(eta)<2.1) return 0.997539;
    if(pt<40.0 && fabs(eta)<2.4) return 0.973786;
    if(pt<50.0 && fabs(eta)<0.9) return 0.99892;
    if(pt<50.0 && fabs(eta)<1.2) return 0.997704;
    if(pt<50.0 && fabs(eta)<2.1) return 0.996128;
    if(pt<50.0 && fabs(eta)<2.4) return 0.974821;
    if(pt<60.0 && fabs(eta)<0.9) return 0.993398;
    if(pt<60.0 && fabs(eta)<1.2) return 0.993429;
    if(pt<60.0 && fabs(eta)<2.1) return 0.991036;
    if(pt<60.0 && fabs(eta)<2.4) return 0.970252;
    if(pt<120. && fabs(eta)<0.9) return 1.00062;
    if(pt<120. && fabs(eta)<1.2) return 0.998652;
    if(pt<120. && fabs(eta)<2.1) return 0.995085;
    if(pt<120. && fabs(eta)<2.4) return 0.97063;
    return 1;
}

float lepsf_MuMediumID_GH_unc(float PT, float Eta){
    float pt  = std::min((float)119.,PT);
    float eta = std::min((float)2.39,std::max((float)-2.39,Eta));
    if(pt<25.0 && fabs(eta)<0.9) return 0.00249895;
    if(pt<25.0 && fabs(eta)<1.2) return 0.00331648;
    if(pt<25.0 && fabs(eta)<2.1) return 0.0017952;
    if(pt<25.0 && fabs(eta)<2.4) return 0.0102665;
    if(pt<30.0 && fabs(eta)<0.9) return 0.00144252;
    if(pt<30.0 && fabs(eta)<1.2) return 0.010818;
    if(pt<30.0 && fabs(eta)<2.1) return 0.000840914;
    if(pt<30.0 && fabs(eta)<2.4) return 0.00147755;
    if(pt<40.0 && fabs(eta)<0.9) return 0.000398547;
    if(pt<40.0 && fabs(eta)<1.2) return 0.00185251;
    if(pt<40.0 && fabs(eta)<2.1) return 0.0059074;
    if(pt<40.0 && fabs(eta)<2.4) return 0.039075;
    if(pt<50.0 && fabs(eta)<0.9) return 0.000202595;
    if(pt<50.0 && fabs(eta)<1.2) return 0.000331509;
    if(pt<50.0 && fabs(eta)<2.1) return 0.000214178;
    if(pt<50.0 && fabs(eta)<2.4) return 0.000850608;
    if(pt<60.0 && fabs(eta)<0.9) return 0.000621969;
    if(pt<60.0 && fabs(eta)<1.2) return 0.00116595;
    if(pt<60.0 && fabs(eta)<2.1) return 0.0031303;
    if(pt<60.0 && fabs(eta)<2.4) return 0.00231345;
    if(pt<120. && fabs(eta)<0.9) return 0.00147552;
    if(pt<120. && fabs(eta)<1.2) return 0.00274147;
    if(pt<120. && fabs(eta)<2.1) return 0.00811754;
    if(pt<120. && fabs(eta)<2.4) return 0.00518057;
    return 0;
}

//______________________________________________________________________________________
float lepsf_MuMediumPOG_MuTightVVV_v1(float PT, float Eta)
{
    float pt  = std::min((float)1199.,PT);
    float eta = std::min((float)2.39,std::max((float)-2.39,Eta));
    if (pt < 25.0   && fabs(eta) < 0.9) return 0.972987830639;
    if (pt < 30.0   && fabs(eta) < 0.9) return 0.980633199215;
    if (pt < 40.0   && fabs(eta) < 0.9) return 0.986259222031;
    if (pt < 50.0   && fabs(eta) < 0.9) return 0.989767193794;
    if (pt < 60.0   && fabs(eta) < 0.9) return 0.990144252777;
    if (pt < 120.0  && fabs(eta) < 0.9) return 0.992544472218;
    if (pt < 200.0  && fabs(eta) < 0.9) return 1.00607073307;
    if (pt < 1200.0 && fabs(eta) < 0.9) return 1.00708353519;
    if (pt < 25.0   && fabs(eta) < 1.2) return 0.982158899307;
    if (pt < 30.0   && fabs(eta) < 1.2) return 0.99262791872;
    if (pt < 40.0   && fabs(eta) < 1.2) return 0.994507312775;
    if (pt < 50.0   && fabs(eta) < 1.2) return 0.994486868382;
    if (pt < 60.0   && fabs(eta) < 1.2) return 0.995231330395;
    if (pt < 120.0  && fabs(eta) < 1.2) return 0.996162414551;
    if (pt < 200.0  && fabs(eta) < 1.2) return 0.998247504234;
    if (pt < 1200.0 && fabs(eta) < 1.2) return 1.00434410572;
    if (pt < 25.0   && fabs(eta) < 2.1) return 0.992021918297;
    if (pt < 30.0   && fabs(eta) < 2.1) return 0.999400854111;
    if (pt < 40.0   && fabs(eta) < 2.1) return 0.999857544899;
    if (pt < 50.0   && fabs(eta) < 2.1) return 0.999814629555;
    if (pt < 60.0   && fabs(eta) < 2.1) return 1.00330460072;
    if (pt < 120.0  && fabs(eta) < 2.1) return 1.00755393505;
    if (pt < 200.0  && fabs(eta) < 2.1) return 1.01337754726;
    if (pt < 1200.0 && fabs(eta) < 2.1) return 1.02070629597;
    if (pt < 25.0   && fabs(eta) < 2.4) return 0.969161331654;
    if (pt < 30.0   && fabs(eta) < 2.4) return 0.975010037422;
    if (pt < 40.0   && fabs(eta) < 2.4) return 0.990625023842;
    if (pt < 50.0   && fabs(eta) < 2.4) return 0.994753956795;
    if (pt < 60.0   && fabs(eta) < 2.4) return 0.992071866989;
    if (pt < 120.0  && fabs(eta) < 2.4) return 0.994121670723;
    if (pt < 200.0  && fabs(eta) < 2.4) return 0.994795560837;
    if (pt < 1200.0 && fabs(eta) < 2.4) return 1.01750481129;
    return 1;
}

float lepsf_MuMediumPOG_MuTightVVV(float PT, float Eta, int version=0)
{
    float pt  = std::min((float)1199.,PT);
    float eta = std::min((float)2.39,std::max((float)-2.39,Eta));
    if (version == 0)
        return lepsf_MuMediumPOG_MuTightVVV_v1(pt, eta);
    else if (version == 1)
        return lepsf_MuMediumPOG_MuTightVVV_v2(pt, eta);
    else if (version == -1)
        return lepsf_MuMediumPOG_MuTightVVV3l_v2(pt, eta);
}

//______________________________________________________________________________________
float lepsf_MuTightVVV_MuTightVVVMu17_v1(float PT, float Eta)
{
    float pt  = std::min((float)1199.,PT);
    float eta = std::min((float)2.39,std::max((float)-2.39,Eta));
    if ((pt) < 25.0   && fabs(eta) < 0.9) return 0.922722399235;
    if ((pt) < 30.0   && fabs(eta) < 0.9) return 0.923307836056;
    if ((pt) < 40.0   && fabs(eta) < 0.9) return 0.924030900002;
    if ((pt) < 50.0   && fabs(eta) < 0.9) return 0.923241138458;
    if ((pt) < 60.0   && fabs(eta) < 0.9) return 0.921180009842;
    if ((pt) < 120.0  && fabs(eta) < 0.9) return 0.918352901936;
    if ((pt) < 200.0  && fabs(eta) < 0.9) return 0.910844266415;
    if ((pt) < 1200.0 && fabs(eta) < 0.9) return 0.894463002682;
    if ((pt) < 25.0   && fabs(eta) < 1.2) return 0.942260980606;
    if ((pt) < 30.0   && fabs(eta) < 1.2) return 0.945485949516;
    if ((pt) < 40.0   && fabs(eta) < 1.2) return 0.946832001209;
    if ((pt) < 50.0   && fabs(eta) < 1.2) return 0.946245908737;
    if ((pt) < 60.0   && fabs(eta) < 1.2) return 0.945586264133;
    if ((pt) < 120.0  && fabs(eta) < 1.2) return 0.945138394833;
    if ((pt) < 200.0  && fabs(eta) < 1.2) return 0.933813333511;
    if ((pt) < 1200.0 && fabs(eta) < 1.2) return 0.931742787361;
    if ((pt) < 25.0   && fabs(eta) < 2.1) return 0.934685409069;
    if ((pt) < 30.0   && fabs(eta) < 2.1) return 0.940949559212;
    if ((pt) < 40.0   && fabs(eta) < 2.1) return 0.941943407059;
    if ((pt) < 50.0   && fabs(eta) < 2.1) return 0.943855106831;
    if ((pt) < 60.0   && fabs(eta) < 2.1) return 0.94069480896;
    if ((pt) < 120.0  && fabs(eta) < 2.1) return 0.926266431808;
    if ((pt) < 200.0  && fabs(eta) < 2.1) return 0.873467862606;
    if ((pt) < 1200.0 && fabs(eta) < 2.1) return 0.823928773403;
    if ((pt) < 25.0   && fabs(eta) < 2.4) return 0.837569534779;
    if ((pt) < 30.0   && fabs(eta) < 2.4) return 0.866438448429;
    if ((pt) < 40.0   && fabs(eta) < 2.4) return 0.885224223137;
    if ((pt) < 50.0   && fabs(eta) < 2.4) return 0.898686885834;
    if ((pt) < 60.0   && fabs(eta) < 2.4) return 0.901396632195;
    if ((pt) < 120.0  && fabs(eta) < 2.4) return 0.906494557858;
    if ((pt) < 200.0  && fabs(eta) < 2.4) return 0.884702563286;
    if ((pt) < 1200.0 && fabs(eta) < 2.4) return 0.80960047245;
    return 1;
}

float lepsf_MuTightVVV_MuTightVVVMu17_v2(float PT, float Eta)
{
    float pt  = std::min((float)1199.,PT);
    float eta = std::min((float)2.39,std::max((float)-2.39,Eta));
    if ((pt) < 25.0   && fabs(eta) < 0.9) return 0.922722399235;
    if ((pt) < 30.0   && fabs(eta) < 0.9) return 0.923307836056;
    if ((pt) < 40.0   && fabs(eta) < 0.9) return 0.924030900002;
    if ((pt) < 50.0   && fabs(eta) < 0.9) return 0.923241138458;
    if ((pt) < 60.0   && fabs(eta) < 0.9) return 0.921180009842;
    if ((pt) < 120.0  && fabs(eta) < 0.9) return 0.918352901936;
    if ((pt) < 200.0  && fabs(eta) < 0.9) return 0.910844266415;
    if ((pt) < 1200.0 && fabs(eta) < 0.9) return 0.894463002682;
    if ((pt) < 25.0   && fabs(eta) < 1.2) return 0.942260980606;
    if ((pt) < 30.0   && fabs(eta) < 1.2) return 0.945485949516;
    if ((pt) < 40.0   && fabs(eta) < 1.2) return 0.946832001209;
    if ((pt) < 50.0   && fabs(eta) < 1.2) return 0.946245908737;
    if ((pt) < 60.0   && fabs(eta) < 1.2) return 0.945586264133;
    if ((pt) < 120.0  && fabs(eta) < 1.2) return 0.945138394833;
    if ((pt) < 200.0  && fabs(eta) < 1.2) return 0.933813333511;
    if ((pt) < 1200.0 && fabs(eta) < 1.2) return 0.931742787361;
    if ((pt) < 25.0   && fabs(eta) < 2.1) return 0.934685409069;
    if ((pt) < 30.0   && fabs(eta) < 2.1) return 0.940949559212;
    if ((pt) < 40.0   && fabs(eta) < 2.1) return 0.941943407059;
    if ((pt) < 50.0   && fabs(eta) < 2.1) return 0.943855106831;
    if ((pt) < 60.0   && fabs(eta) < 2.1) return 0.94069480896;
    if ((pt) < 120.0  && fabs(eta) < 2.1) return 0.926266431808;
    if ((pt) < 200.0  && fabs(eta) < 2.1) return 0.873467862606;
    if ((pt) < 1200.0 && fabs(eta) < 2.1) return 0.823928773403;
    if ((pt) < 25.0   && fabs(eta) < 2.4) return 0.837569534779;
    if ((pt) < 30.0   && fabs(eta) < 2.4) return 0.866438448429;
    if ((pt) < 40.0   && fabs(eta) < 2.4) return 0.885224223137;
    if ((pt) < 50.0   && fabs(eta) < 2.4) return 0.898686885834;
    if ((pt) < 60.0   && fabs(eta) < 2.4) return 0.901396632195;
    if ((pt) < 120.0  && fabs(eta) < 2.4) return 0.906494557858;
    if ((pt) < 200.0  && fabs(eta) < 2.4) return 0.884702563286;
    if ((pt) < 1200.0 && fabs(eta) < 2.4) return 0.80960047245;
    return 1;
}

float lepsf_MuTightVVV_MuTightVVVMu17(float PT, float Eta, int version=0)
{
    float pt  = std::min((float)1199.,PT);
    float eta = std::min((float)2.39,std::max((float)-2.39,Eta));
    if (version == 0)
        return lepsf_MuTightVVV_MuTightVVVMu17_v1(pt, eta);
    else if (version == 1)
        return lepsf_MuTightVVV_MuTightVVVMu17_v2(pt, eta);
}

float lepsf_MuTightVVV_MuTightVVVMu17_unc(float PT, float Eta)
{
    float pt  = std::min((float)1199.,PT);
    float eta = std::min((float)2.39,std::max((float)-2.39,Eta));
    if ((pt) < 25.0   && fabs(eta) < 0.9) return 0.00250782468408;
    if ((pt) < 30.0   && fabs(eta) < 0.9) return 0.000366351007182;
    if ((pt) < 40.0   && fabs(eta) < 0.9) return 0.000730909831923;
    if ((pt) < 50.0   && fabs(eta) < 0.9) return 0.000768592171557;
    if ((pt) < 60.0   && fabs(eta) < 0.9) return 0.00080159636303;
    if ((pt) < 120.0  && fabs(eta) < 0.9) return 0.00185961188485;
    if ((pt) < 200.0  && fabs(eta) < 0.9) return 0.00739344058835;
    if ((pt) < 1200.0 && fabs(eta) < 0.9) return 0.016525458852;
    if ((pt) < 25.0   && fabs(eta) < 1.2) return 0.00458041035964;
    if ((pt) < 30.0   && fabs(eta) < 1.2) return 0.00346783935787;
    if ((pt) < 40.0   && fabs(eta) < 1.2) return 0.00141910674422;
    if ((pt) < 50.0   && fabs(eta) < 1.2) return 0.000673513472744;
    if ((pt) < 60.0   && fabs(eta) < 1.2) return 0.00240884834276;
    if ((pt) < 120.0  && fabs(eta) < 1.2) return 0.00318644606928;
    if ((pt) < 200.0  && fabs(eta) < 1.2) return 0.014169270918;
    if ((pt) < 1200.0 && fabs(eta) < 1.2) return 0.0243677246898;
    if ((pt) < 25.0   && fabs(eta) < 2.1) return 0.00235550744943;
    if ((pt) < 30.0   && fabs(eta) < 2.1) return 0.0017736671693;
    if ((pt) < 40.0   && fabs(eta) < 2.1) return 0.000142803887399;
    if ((pt) < 50.0   && fabs(eta) < 2.1) return 0.000241549432239;
    if ((pt) < 60.0   && fabs(eta) < 2.1) return 0.00167134522243;
    if ((pt) < 120.0  && fabs(eta) < 2.1) return 0.00212335629489;
    if ((pt) < 200.0  && fabs(eta) < 2.1) return 0.00932832611851;
    if ((pt) < 1200.0 && fabs(eta) < 2.1) return 0.0230251207295;
    if ((pt) < 25.0   && fabs(eta) < 2.4) return 0.00488000441924;
    if ((pt) < 30.0   && fabs(eta) < 2.4) return 0.00319838676876;
    if ((pt) < 40.0   && fabs(eta) < 2.4) return 0.00194770815806;
    if ((pt) < 50.0   && fabs(eta) < 2.4) return 0.00179089574024;
    if ((pt) < 60.0   && fabs(eta) < 2.4) return 0.00355735499739;
    if ((pt) < 120.0  && fabs(eta) < 2.4) return 0.00504503993108;
    if ((pt) < 200.0  && fabs(eta) < 2.4) return 0.0182467487213;
    if ((pt) < 1200.0 && fabs(eta) < 2.4) return 0.0950186278378;
    return 0;
}

//______________________________________________________________________________________
float lepsf_MuTightVVV_MuTightVVVMu8(float PT, float Eta)
{
    float pt  = std::min((float)1199.,PT);
    float eta = std::min((float)2.39,std::max((float)-2.39,Eta));
    if ((pt) < 25.0   && fabs(eta) < 0.9) return 0.933527767658;
    if ((pt) < 30.0   && fabs(eta) < 0.9) return 0.933456897736;
    if ((pt) < 40.0   && fabs(eta) < 0.9) return 0.934123814106;
    if ((pt) < 50.0   && fabs(eta) < 0.9) return 0.933176159859;
    if ((pt) < 60.0   && fabs(eta) < 0.9) return 0.931691288948;
    if ((pt) < 120.0  && fabs(eta) < 0.9) return 0.929507613182;
    if ((pt) < 200.0  && fabs(eta) < 0.9) return 0.924368977547;
    if ((pt) < 1200.0 && fabs(eta) < 0.9) return 0.910157442093;
    if ((pt) < 25.0   && fabs(eta) < 1.2) return 0.96690428257;
    if ((pt) < 30.0   && fabs(eta) < 1.2) return 0.968839883804;
    if ((pt) < 40.0   && fabs(eta) < 1.2) return 0.968176484108;
    if ((pt) < 50.0   && fabs(eta) < 1.2) return 0.967356085777;
    if ((pt) < 60.0   && fabs(eta) < 1.2) return 0.966672122478;
    if ((pt) < 120.0  && fabs(eta) < 1.2) return 0.965913832188;
    if ((pt) < 200.0  && fabs(eta) < 1.2) return 0.962421000004;
    if ((pt) < 1200.0 && fabs(eta) < 1.2) return 0.961861371994;
    if ((pt) < 25.0   && fabs(eta) < 2.1) return 0.961845993996;
    if ((pt) < 30.0   && fabs(eta) < 2.1) return 0.962982833385;
    if ((pt) < 40.0   && fabs(eta) < 2.1) return 0.962533831596;
    if ((pt) < 50.0   && fabs(eta) < 2.1) return 0.963077664375;
    if ((pt) < 60.0   && fabs(eta) < 2.1) return 0.963417887688;
    if ((pt) < 120.0  && fabs(eta) < 2.1) return 0.962129116058;
    if ((pt) < 200.0  && fabs(eta) < 2.1) return 0.935746133327;
    if ((pt) < 1200.0 && fabs(eta) < 2.1) return 0.89957177639;
    if ((pt) < 25.0   && fabs(eta) < 2.4) return 0.944805383682;
    if ((pt) < 30.0   && fabs(eta) < 2.4) return 0.948861658573;
    if ((pt) < 40.0   && fabs(eta) < 2.4) return 0.949180960655;
    if ((pt) < 50.0   && fabs(eta) < 2.4) return 0.949977576733;
    if ((pt) < 60.0   && fabs(eta) < 2.4) return 0.947516798973;
    if ((pt) < 120.0  && fabs(eta) < 2.4) return 0.948109149933;
    if ((pt) < 200.0  && fabs(eta) < 2.4) return 0.926202654839;
    if ((pt) < 1200.0 && fabs(eta) < 2.4) return 0.865132570267;
    return 1;
}

float lepsf_MuTightVVV_MuTightVVVMu8_unc(float PT, float Eta)
{
    float pt  = std::min((float)1199.,PT);
    float eta = std::min((float)2.39,std::max((float)-2.39,Eta));
    if ((pt) < 25.0   && fabs(eta) < 0.9) return 0.00252632647732;
    if ((pt) < 30.0   && fabs(eta) < 0.9) return 0.00152941158904;
    if ((pt) < 40.0   && fabs(eta) < 0.9) return 5.7151570156e-05;
    if ((pt) < 50.0   && fabs(eta) < 0.9) return 0.000533302705251;
    if ((pt) < 60.0   && fabs(eta) < 0.9) return 0.00134394291184;
    if ((pt) < 120.0  && fabs(eta) < 0.9) return 0.00175162047452;
    if ((pt) < 200.0  && fabs(eta) < 0.9) return 0.00746803644143;
    if ((pt) < 1200.0 && fabs(eta) < 0.9) return 0.0167671085273;
    if ((pt) < 25.0   && fabs(eta) < 1.2) return 0.00463995182995;
    if ((pt) < 30.0   && fabs(eta) < 1.2) return 0.000296189435009;
    if ((pt) < 40.0   && fabs(eta) < 1.2) return 0.00147301227187;
    if ((pt) < 50.0   && fabs(eta) < 1.2) return 0.0012252910266;
    if ((pt) < 60.0   && fabs(eta) < 1.2) return 0.00253712385559;
    if ((pt) < 120.0  && fabs(eta) < 1.2) return 0.00324173670128;
    if ((pt) < 200.0  && fabs(eta) < 1.2) return 0.0145629366561;
    if ((pt) < 1200.0 && fabs(eta) < 1.2) return 0.0236944487724;
    if ((pt) < 25.0   && fabs(eta) < 2.1) return 0.00034315722064;
    if ((pt) < 30.0   && fabs(eta) < 2.1) return 0.00180503994187;
    if ((pt) < 40.0   && fabs(eta) < 2.1) return 0.000139178337978;
    if ((pt) < 50.0   && fabs(eta) < 2.1) return 0.0008053328847;
    if ((pt) < 60.0   && fabs(eta) < 2.1) return 0.00160263939342;
    if ((pt) < 120.0  && fabs(eta) < 2.1) return 0.000363735247895;
    if ((pt) < 200.0  && fabs(eta) < 2.1) return 0.0082700842047;
    if ((pt) < 1200.0 && fabs(eta) < 2.1) return 0.0245530433342;
    if ((pt) < 25.0   && fabs(eta) < 2.4) return 0.00573946175886;
    if ((pt) < 30.0   && fabs(eta) < 2.4) return 0.0148002473209;
    if ((pt) < 40.0   && fabs(eta) < 2.4) return 0.00205940031199;
    if ((pt) < 50.0   && fabs(eta) < 2.4) return 0.00186501847954;
    if ((pt) < 60.0   && fabs(eta) < 2.4) return 0.00371860765466;
    if ((pt) < 120.0  && fabs(eta) < 2.4) return 0.00521480251546;
    if ((pt) < 200.0  && fabs(eta) < 2.4) return 0.0195444637705;
    if ((pt) < 1200.0 && fabs(eta) < 2.4) return 0.532614728793;
    return 0;
}




//______________________________________________________________________________________
float fakerate_baseline_v1_mu_data(float Eta, float conecorrPT)
{
    float conecorrpt  = std::min((float)9999.,conecorrPT);
    float eta = std::min((float)2.39,std::max((float)-2.39,Eta));
    if (fabs(eta) < 1.2 && (conecorrpt) < 20.0 ) return 0.18162853637;
    if (fabs(eta) < 2.1 && (conecorrpt) < 20.0 ) return 0.228556342818;
    if (fabs(eta) < 2.4 && (conecorrpt) < 20.0 ) return 0.284501936043;
    if (fabs(eta) < 1.2 && (conecorrpt) < 30.0 ) return 0.0593080016201;
    if (fabs(eta) < 2.1 && (conecorrpt) < 30.0 ) return 0.0812573899031;
    if (fabs(eta) < 2.4 && (conecorrpt) < 30.0 ) return 0.120471940997;
    if (fabs(eta) < 1.2 && (conecorrpt) < 50.0 ) return 0.0502796544514;
    if (fabs(eta) < 2.1 && (conecorrpt) < 50.0 ) return 0.0755524005305;
    if (fabs(eta) < 2.4 && (conecorrpt) < 50.0 ) return 0.102110577821;
    if (fabs(eta) < 1.2 && (conecorrpt) < 10000) return 0.0504603068665;
    if (fabs(eta) < 2.1 && (conecorrpt) < 10000) return 0.0699800116561;
    if (fabs(eta) < 2.4 && (conecorrpt) < 10000) return 0.0699800116561;
    return 1;
}
float fakerate_baseline_v1_mu_data_unc(float Eta, float conecorrPT)
{
    float conecorrpt  = std::min((float)9999.,conecorrPT);
    float eta = std::min((float)2.39,std::max((float)-2.39,Eta));
    if (fabs(eta) < 1.2 && (conecorrpt) < 20.0 ) return 0.00419139178595;
    if (fabs(eta) < 2.1 && (conecorrpt) < 20.0 ) return 0.00643408235926;
    if (fabs(eta) < 2.4 && (conecorrpt) < 20.0 ) return 0.0138531422818;
    if (fabs(eta) < 1.2 && (conecorrpt) < 30.0 ) return 0.00429931883058;
    if (fabs(eta) < 2.1 && (conecorrpt) < 30.0 ) return 0.00690133585711;
    if (fabs(eta) < 2.4 && (conecorrpt) < 30.0 ) return 0.0154600921933;
    if (fabs(eta) < 1.2 && (conecorrpt) < 50.0 ) return 0.00337692471616;
    if (fabs(eta) < 2.1 && (conecorrpt) < 50.0 ) return 0.00454099610916;
    if (fabs(eta) < 2.4 && (conecorrpt) < 50.0 ) return 0.0116371933399;
    if (fabs(eta) < 1.2 && (conecorrpt) < 10000) return 0.0223031276198;
    if (fabs(eta) < 2.1 && (conecorrpt) < 10000) return 0.0249675245212;
    if (fabs(eta) < 2.4 && (conecorrpt) < 10000) return 0.0249675245212;
    return 0;
}
//______________________________________________________________________________________
float fakerate_baseline_v1_mu_qcd(float Eta, float conecorrPT)
{
    float conecorrpt  = std::min((float)9999.,conecorrPT);
    float eta = std::min((float)2.39,std::max((float)-2.39,Eta));
    if (fabs(eta) < 1.2 && (conecorrpt) < 20.0 ) return 0.192454320571;
    if (fabs(eta) < 2.1 && (conecorrpt) < 20.0 ) return 0.25212783352;
    if (fabs(eta) < 2.4 && (conecorrpt) < 20.0 ) return 0.299959325364;
    if (fabs(eta) < 1.2 && (conecorrpt) < 30.0 ) return 0.0592032661673;
    if (fabs(eta) < 2.1 && (conecorrpt) < 30.0 ) return 0.109370893274;
    if (fabs(eta) < 2.4 && (conecorrpt) < 30.0 ) return 0.124618041094;
    if (fabs(eta) < 1.2 && (conecorrpt) < 50.0 ) return 0.0455410037998;
    if (fabs(eta) < 2.1 && (conecorrpt) < 50.0 ) return 0.0673590936047;
    if (fabs(eta) < 2.4 && (conecorrpt) < 50.0 ) return 0.067457120855;
    if (fabs(eta) < 1.2 && (conecorrpt) < 10000) return 0.0317322626443;
    if (fabs(eta) < 2.1 && (conecorrpt) < 10000) return 0.0554220997027;
    if (fabs(eta) < 2.4 && (conecorrpt) < 10000) return 0.0583591616584;
    return 1;
}
float fakerate_baseline_v1_mu_qcd_unc(float Eta, float conecorrPT)
{
    float conecorrpt  = std::min((float)9999.,conecorrPT);
    float eta = std::min((float)2.39,std::max((float)-2.39,Eta));
    if (fabs(eta) < 1.2 && (conecorrpt) < 20.0 ) return 0.00435651562103;
    if (fabs(eta) < 2.1 && (conecorrpt) < 20.0 ) return 0.00673523309854;
    if (fabs(eta) < 2.4 && (conecorrpt) < 20.0 ) return 0.0139496576752;
    if (fabs(eta) < 1.2 && (conecorrpt) < 30.0 ) return 0.00397245526891;
    if (fabs(eta) < 2.1 && (conecorrpt) < 30.0 ) return 0.00733365179432;
    if (fabs(eta) < 2.4 && (conecorrpt) < 30.0 ) return 0.0126552722177;
    if (fabs(eta) < 1.2 && (conecorrpt) < 50.0 ) return 0.00546544224618;
    if (fabs(eta) < 2.1 && (conecorrpt) < 50.0 ) return 0.00792283130924;
    if (fabs(eta) < 2.4 && (conecorrpt) < 50.0 ) return 0.0151418937682;
    if (fabs(eta) < 1.2 && (conecorrpt) < 10000) return 0.00831418957152;
    if (fabs(eta) < 2.1 && (conecorrpt) < 10000) return 0.0171941451909;
    if (fabs(eta) < 2.4 && (conecorrpt) < 10000) return 0.0227115872818;
    return 0;
}

//______________________________________________________________________________________
float fakerate_baseline_v1_el_data(float Eta, float conecorrPT)
{
    float conecorrpt  = std::min((float)9999.,conecorrPT);
    float eta = std::min((float)2.49,std::max((float)-2.49,Eta));
    if (fabs(eta) < 0.8   && (conecorrpt) < 20.0 ) return 0.180862610834;
    if (fabs(eta) < 1.479 && (conecorrpt) < 20.0 ) return 0.151654211681;
    if (fabs(eta) < 2.5   && (conecorrpt) < 20.0 ) return 0.166856924948;
    if (fabs(eta) < 0.8   && (conecorrpt) < 30.0 ) return 0.133459584075;
    if (fabs(eta) < 1.479 && (conecorrpt) < 30.0 ) return 0.108987284034;
    if (fabs(eta) < 2.5   && (conecorrpt) < 30.0 ) return 0.127048887898;
    if (fabs(eta) < 0.8   && (conecorrpt) < 50.0 ) return 0.115077619378;
    if (fabs(eta) < 1.479 && (conecorrpt) < 50.0 ) return 0.0997162232625;
    if (fabs(eta) < 2.5   && (conecorrpt) < 50.0 ) return 0.106395503788;
    if (fabs(eta) < 0.8   && (conecorrpt) < 10000) return 0.0793935587448;
    if (fabs(eta) < 1.479 && (conecorrpt) < 10000) return 0.0794240499611;
    if (fabs(eta) < 2.5   && (conecorrpt) < 10000) return 0.0995944944707;
    return 1;
}
float fakerate_baseline_v1_el_data_unc(float Eta, float conecorrPT)
{
    float conecorrpt  = std::min((float)9999.,conecorrPT);
    float eta = std::min((float)2.49,std::max((float)-2.49,Eta));
    if (fabs(eta) < 0.8   && (conecorrpt) < 20.0 ) return 0.011780565611;
    if (fabs(eta) < 1.479 && (conecorrpt) < 20.0 ) return 0.00866843935974;
    if (fabs(eta) < 2.5   && (conecorrpt) < 20.0 ) return 0.0086750832925;
    if (fabs(eta) < 0.8   && (conecorrpt) < 30.0 ) return 0.0146960861119;
    if (fabs(eta) < 1.479 && (conecorrpt) < 30.0 ) return 0.0112594175795;
    if (fabs(eta) < 2.5   && (conecorrpt) < 30.0 ) return 0.0116391553635;
    if (fabs(eta) < 0.8   && (conecorrpt) < 50.0 ) return 0.0116121608794;
    if (fabs(eta) < 1.479 && (conecorrpt) < 50.0 ) return 0.0099509146269;
    if (fabs(eta) < 2.5   && (conecorrpt) < 50.0 ) return 0.00678263788235;
    if (fabs(eta) < 0.8   && (conecorrpt) < 10000) return 0.0340196244843;
    if (fabs(eta) < 1.479 && (conecorrpt) < 10000) return 0.0289512048486;
    if (fabs(eta) < 2.5   && (conecorrpt) < 10000) return 0.0122391050471;
    return 0;
}
//______________________________________________________________________________________
float fakerate_baseline_v1_el_qcd(float Eta, float conecorrPT)
{
    float conecorrpt  = std::min((float)9999.,conecorrPT);
    float eta = std::min((float)2.49,std::max((float)-2.49,Eta));
    if (fabs(eta) < 0.8   && (conecorrpt) < 20.0 ) return 0.230089425906;
    if (fabs(eta) < 1.479 && (conecorrpt) < 20.0 ) return 0.187918774855;
    if (fabs(eta) < 2.5   && (conecorrpt) < 20.0 ) return 0.181326427551;
    if (fabs(eta) < 0.8   && (conecorrpt) < 30.0 ) return 0.173060172437;
    if (fabs(eta) < 1.479 && (conecorrpt) < 30.0 ) return 0.127839209154;
    if (fabs(eta) < 2.5   && (conecorrpt) < 30.0 ) return 0.106022264846;
    if (fabs(eta) < 0.8   && (conecorrpt) < 50.0 ) return 0.0515026065715;
    if (fabs(eta) < 1.479 && (conecorrpt) < 50.0 ) return 0.141963824743;
    if (fabs(eta) < 2.5   && (conecorrpt) < 50.0 ) return 0.0987933061792;
    if (fabs(eta) < 0.8   && (conecorrpt) < 10000) return 0.0854687145457;
    if (fabs(eta) < 1.479 && (conecorrpt) < 10000) return 0.101560108062;
    if (fabs(eta) < 2.5   && (conecorrpt) < 10000) return 0.0892398734513;
    return 1;
}
float fakerate_baseline_v1_el_qcd_unc(float Eta, float conecorrPT)
{
    float conecorrpt  = std::min((float)9999.,conecorrPT);
    float eta = std::min((float)2.49,std::max((float)-2.49,Eta));
    if (fabs(eta) < 0.8   && (conecorrpt) < 20.0 ) return 0.013635548062;
    if (fabs(eta) < 1.479 && (conecorrpt) < 20.0 ) return 0.0301966750315;
    if (fabs(eta) < 2.5   && (conecorrpt) < 20.0 ) return 0.0229038017929;
    if (fabs(eta) < 0.8   && (conecorrpt) < 30.0 ) return 0.0540543730729;
    if (fabs(eta) < 1.479 && (conecorrpt) < 30.0 ) return 0.0578526851684;
    if (fabs(eta) < 2.5   && (conecorrpt) < 30.0 ) return 0.0311610831766;
    if (fabs(eta) < 0.8   && (conecorrpt) < 50.0 ) return 0.0163129257811;
    if (fabs(eta) < 1.479 && (conecorrpt) < 50.0 ) return 0.0705629823265;
    if (fabs(eta) < 2.5   && (conecorrpt) < 50.0 ) return 0.022152759532;
    if (fabs(eta) < 0.8   && (conecorrpt) < 10000) return 0.0367682367283;
    if (fabs(eta) < 1.479 && (conecorrpt) < 10000) return 0.0386388851491;
    if (fabs(eta) < 2.5   && (conecorrpt) < 10000) return 0.0199718234062;
    return 0;
}

//______________________________________________________________________________________
float fakerate_baseline_v2_ss_mu_data(float Eta, float conecorrPT)
{
    return fakerate_mu_data_baseline_v2_ss(Eta, conecorrPT);
}
float fakerate_baseline_v2_ss_mu_data_unc(float Eta, float conecorrPT)
{
    return fakerate_mu_data_baseline_v2_ss(Eta, conecorrPT, 1) - fakerate_mu_data_baseline_v2_ss(Eta, conecorrPT);
}
//______________________________________________________________________________________
float fakerate_baseline_v2_ss_mu_qcd(float Eta, float conecorrPT)
{
    return fakerate_mu_qcd_baseline_v2_ss(Eta, conecorrPT);
}
float fakerate_baseline_v2_ss_mu_qcd_unc(float Eta, float conecorrPT)
{
    return fakerate_mu_qcd_baseline_v2_ss(Eta, conecorrPT, 1) - fakerate_mu_qcd_baseline_v2_ss(Eta, conecorrPT);
}

//______________________________________________________________________________________
float fakerate_baseline_v2_ss_el_data(float Eta, float conecorrPT)
{
    return fakerate_el_data_baseline_v2_ss(Eta, conecorrPT);
}
float fakerate_baseline_v2_ss_el_data_unc(float Eta, float conecorrPT)
{
    return fakerate_el_data_baseline_v2_ss(Eta, conecorrPT, 1) - fakerate_el_data_baseline_v2_ss(Eta, conecorrPT);
}
//______________________________________________________________________________________
float fakerate_baseline_v2_ss_el_qcd(float Eta, float conecorrPT)
{
    return fakerate_el_qcd_baseline_v2_ss(Eta, conecorrPT);
}
float fakerate_baseline_v2_ss_el_qcd_unc(float Eta, float conecorrPT)
{
    return fakerate_el_qcd_baseline_v2_ss(Eta, conecorrPT, 1) - fakerate_el_qcd_baseline_v2_ss(Eta, conecorrPT);
}

//______________________________________________________________________________________
float fakerate_baseline_v2_3l_mu_data(float Eta, float conecorrPT)
{
    return fakerate_mu_data_baseline_v2_3l(Eta, conecorrPT);
}
float fakerate_baseline_v2_3l_mu_data_unc(float Eta, float conecorrPT)
{
    return fakerate_mu_data_baseline_v2_3l(Eta, conecorrPT, 1) - fakerate_mu_data_baseline_v2_3l(Eta, conecorrPT);
}
//______________________________________________________________________________________
float fakerate_baseline_v2_3l_mu_qcd(float Eta, float conecorrPT)
{
    return fakerate_mu_qcd_baseline_v2_3l(Eta, conecorrPT);
}
float fakerate_baseline_v2_3l_mu_qcd_unc(float Eta, float conecorrPT)
{
    return fakerate_mu_qcd_baseline_v2_3l(Eta, conecorrPT, 1) - fakerate_mu_qcd_baseline_v2_3l(Eta, conecorrPT);
}

//______________________________________________________________________________________
float fakerate_baseline_v2_3l_el_data(float Eta, float conecorrPT)
{
    return fakerate_el_data_baseline_v2_3l(Eta, conecorrPT);
}
float fakerate_baseline_v2_3l_el_data_unc(float Eta, float conecorrPT)
{
    return fakerate_el_data_baseline_v2_3l(Eta, conecorrPT, 1) - fakerate_el_data_baseline_v2_3l(Eta, conecorrPT);
}
//______________________________________________________________________________________
float fakerate_baseline_v2_3l_el_qcd(float Eta, float conecorrPT)
{
    return fakerate_el_qcd_baseline_v2_3l(Eta, conecorrPT);
}
float fakerate_baseline_v2_3l_el_qcd_unc(float Eta, float conecorrPT)
{
    return fakerate_el_qcd_baseline_v2_3l(Eta, conecorrPT, 1) - fakerate_el_qcd_baseline_v2_3l(Eta, conecorrPT);
}

//______________________________________________________________________________________
//______________________________________________________________________________________
//______________________________________________________________________________________

//______________________________________________________________________________________
float fakerate_mu_data(float Eta, float conecorrPT, int version=0)
{
    if (version == -1)
    {
        return fakerate_baseline_v2_3l_mu_data(Eta, conecorrPT);
    }
    if (version == 1)
    {
        return fakerate_baseline_v2_ss_mu_data(Eta, conecorrPT);
    }
    return fakerate_baseline_v1_mu_data(Eta, conecorrPT);
}
float fakerate_mu_data_unc(float Eta, float conecorrPT, int version=0)
{
    if (version == -1)
    {
        return fakerate_baseline_v2_3l_mu_data_unc(Eta, conecorrPT);
    }
    if (version == 1)
    {
        return fakerate_baseline_v2_ss_mu_data_unc(Eta, conecorrPT);
    }
    return fakerate_baseline_v1_mu_data_unc(Eta, conecorrPT);
}
//______________________________________________________________________________________
float fakerate_mu_qcd(float Eta, float conecorrPT, int version=0)
{
    if (version == -1)
    {
        return fakerate_baseline_v2_3l_mu_qcd(Eta, conecorrPT);
    }
    if (version == 1)
    {
        return fakerate_baseline_v2_ss_mu_qcd(Eta, conecorrPT);
    }
    return fakerate_baseline_v1_mu_qcd(Eta, conecorrPT);
}
float fakerate_mu_qcd_unc(float Eta, float conecorrPT, int version=0)
{
    if (version == -1)
    {
        return fakerate_baseline_v2_3l_mu_qcd_unc(Eta, conecorrPT);
    }
    if (version == 1)
    {
        return fakerate_baseline_v2_ss_mu_qcd_unc(Eta, conecorrPT);
    }
    return fakerate_baseline_v1_mu_qcd_unc(Eta, conecorrPT);
}

//______________________________________________________________________________________
float fakerate_el_data(float Eta, float conecorrPT, int version=0)
{
    if (version == -1)
    {
        return fakerate_baseline_v2_3l_el_data(Eta, conecorrPT);
    }
    if (version == 1)
    {
        return fakerate_baseline_v2_ss_el_data(Eta, conecorrPT);
    }
    return fakerate_baseline_v1_el_data(Eta, conecorrPT);
}
float fakerate_el_data_unc(float Eta, float conecorrPT, int version=0)
{
    if (version == -1)
    {
        return fakerate_baseline_v2_3l_el_data_unc(Eta, conecorrPT);
    }
    if (version == 1)
    {
        return fakerate_baseline_v2_ss_el_data_unc(Eta, conecorrPT);
    }
    return fakerate_baseline_v1_el_data_unc(Eta, conecorrPT);
}
//______________________________________________________________________________________
float fakerate_el_qcd(float Eta, float conecorrPT, int version=0)
{
    if (version == -1)
    {
        return fakerate_baseline_v2_3l_el_qcd(Eta, conecorrPT);
    }
    if (version == 1)
    {
        return fakerate_baseline_v2_ss_el_qcd(Eta, conecorrPT);
    }
    return fakerate_baseline_v1_el_qcd(Eta, conecorrPT);
}
float fakerate_el_qcd_unc(float Eta, float conecorrPT, int version=0)
{
    if (version == -1)
    {
        return fakerate_baseline_v2_3l_el_qcd_unc(Eta, conecorrPT);
    }
    if (version == 1)
    {
        return fakerate_baseline_v2_ss_el_qcd_unc(Eta, conecorrPT);
    }
    return fakerate_baseline_v1_el_qcd_unc(Eta, conecorrPT);
}


//______________________________________________________________________________________
//______________________________________________________________________________________
//______________________________________________________________________________________


float puWeight(int nPUVtx, int variation=0){
  if(nPUVtx<0) return 0;
  if(variation==0){
    if(nPUVtx== 0) return 0.366077;
    if(nPUVtx== 1) return 0.893925;
    if(nPUVtx== 2) return 1.19772;
    if(nPUVtx== 3) return 0.9627;
    if(nPUVtx== 4) return 1.12098;
    if(nPUVtx== 5) return 1.16486;
    if(nPUVtx== 6) return 0.795599;
    if(nPUVtx== 7) return 0.495824;
    if(nPUVtx== 8) return 0.742182;
    if(nPUVtx== 9) return 0.878856;
    if(nPUVtx==10) return 0.964232;
    if(nPUVtx==11) return 1.0725;
    if(nPUVtx==12) return 1.12534;
    if(nPUVtx==13) return 1.17603;
    if(nPUVtx==14) return 1.20208;
    if(nPUVtx==15) return 1.20764;
    if(nPUVtx==16) return 1.20018;
    if(nPUVtx==17) return 1.18268;
    if(nPUVtx==18) return 1.144;
    if(nPUVtx==19) return 1.09663;
    if(nPUVtx==20) return 1.0656;
    if(nPUVtx==21) return 1.05117;
    if(nPUVtx==22) return 1.0516;
    if(nPUVtx==23) return 1.05063;
    if(nPUVtx==24) return 1.04986;
    if(nPUVtx==25) return 1.05817;
    if(nPUVtx==26) return 1.07216;
    if(nPUVtx==27) return 1.08303;
    if(nPUVtx==28) return 1.09569;
    if(nPUVtx==29) return 1.10787;
    if(nPUVtx==30) return 1.09462;
    if(nPUVtx==31) return 1.08262;
    if(nPUVtx==32) return 1.04125;
    if(nPUVtx==33) return 0.985752;
    if(nPUVtx==34) return 0.910807;
    if(nPUVtx==35) return 0.820923;
    if(nPUVtx==36) return 0.716787;
    if(nPUVtx==37) return 0.610013;
    if(nPUVtx==38) return 0.503118;
    if(nPUVtx==39) return 0.404841;
    if(nPUVtx==40) return 0.309195;
    if(nPUVtx==41) return 0.22792;
    if(nPUVtx==42) return 0.16369;
    if(nPUVtx==43) return 0.11318;
    if(nPUVtx==44) return 0.0773005;
    if(nPUVtx==45) return 0.0509221;
    if(nPUVtx==46) return 0.0318936;
    if(nPUVtx==47) return 0.0200936;
    if(nPUVtx==48) return 0.0122631;
    if(nPUVtx==49) return 0.00742646;
    if(nPUVtx==50) return 0.00438028;
    if(nPUVtx==51) return 0.00260777;
    if(nPUVtx==52) return 0.00156599;
    if(nPUVtx==53) return 0.000971358;
    if(nPUVtx==54) return 0.000729206;
    if(nPUVtx==55) return 0.000672709;
    if(nPUVtx==56) return 0.000730459;
    if(nPUVtx==57) return 0.000948791;
    if(nPUVtx==58) return 0.00135533;
    if(nPUVtx==59) return 0.00189419;
    if(nPUVtx==60) return 0.00308244;
    if(nPUVtx==61) return 0.00409665;
    if(nPUVtx==62) return 0.00487449;
    if(nPUVtx==63) return 0.00525606;
    if(nPUVtx==64) return 0.00578498;
    if(nPUVtx==65) return 0.00551468;
    if(nPUVtx==66) return 0.00500046;
    if(nPUVtx==67) return 0.00440983;
    if(nPUVtx==68) return 0.00401224;
    if(nPUVtx==69) return 0.00354754;
    if(nPUVtx==70) return 0.00310751;
    if(nPUVtx==71) return 0.00270211;
    if(nPUVtx==72) return 0.00233691;
    if(nPUVtx==73) return 0.00202529;
    if(nPUVtx>=74) return 0.00172328;
  }
  if(variation<0){//down
    if(nPUVtx== 0) return 0.379278;
    if(nPUVtx== 1) return 1.14117;
    if(nPUVtx== 2) return 1.25988;
    if(nPUVtx== 3) return 1.0989;
    if(nPUVtx== 4) return 1.25006;
    if(nPUVtx== 5) return 1.28085;
    if(nPUVtx== 6) return 0.920142;
    if(nPUVtx== 7) return 0.767693;
    if(nPUVtx== 8) return 1.09257;
    if(nPUVtx== 9) return 1.3374;
    if(nPUVtx==10) return 1.48624;
    if(nPUVtx==11) return 1.52827;
    if(nPUVtx==12) return 1.49779;
    if(nPUVtx==13) return 1.50093;
    if(nPUVtx==14) return 1.49728;
    if(nPUVtx==15) return 1.4437;
    if(nPUVtx==16) return 1.36783;
    if(nPUVtx==17) return 1.29894;
    if(nPUVtx==18) return 1.22733;
    if(nPUVtx==19) return 1.16569;
    if(nPUVtx==20) return 1.12543;
    if(nPUVtx==21) return 1.09059;
    if(nPUVtx==22) return 1.06406;
    if(nPUVtx==23) return 1.03996;
    if(nPUVtx==24) return 1.01924;
    if(nPUVtx==25) return 1.00604;
    if(nPUVtx==26) return 0.996975;
    if(nPUVtx==27) return 0.984886;
    if(nPUVtx==28) return 0.972847;
    if(nPUVtx==29) return 0.95656;
    if(nPUVtx==30) return 0.914677;
    if(nPUVtx==31) return 0.872239;
    if(nPUVtx==32) return 0.807112;
    if(nPUVtx==33) return 0.734267;
    if(nPUVtx==34) return 0.65103;
    if(nPUVtx==35) return 0.561399;
    if(nPUVtx==36) return 0.466396;
    if(nPUVtx==37) return 0.374559;
    if(nPUVtx==38) return 0.288558;
    if(nPUVtx==39) return 0.214518;
    if(nPUVtx==40) return 0.149749;
    if(nPUVtx==41) return 0.0998954;
    if(nPUVtx==42) return 0.0643477;
    if(nPUVtx==43) return 0.0395894;
    if(nPUVtx==44) return 0.0238912;
    if(nPUVtx==45) return 0.0138223;
    if(nPUVtx==46) return 0.00756684;
    if(nPUVtx==47) return 0.004156;
    if(nPUVtx==48) return 0.00221556;
    if(nPUVtx==49) return 0.00118683;
    if(nPUVtx==50) return 0.000642772;
    if(nPUVtx==51) return 0.000384094;
    if(nPUVtx==52) return 0.000272857;
    if(nPUVtx==53) return 0.000243368;
    if(nPUVtx==54) return 0.000289656;
    if(nPUVtx==55) return 0.000395793;
    if(nPUVtx==56) return 0.000543963;
    if(nPUVtx==57) return 0.00078281;
    if(nPUVtx==58) return 0.00115137;
    if(nPUVtx==59) return 0.00160404;
    if(nPUVtx==60) return 0.00256812;
    if(nPUVtx==61) return 0.0033401;
    if(nPUVtx==62) return 0.00387997;
    if(nPUVtx==63) return 0.00407904;
    if(nPUVtx==64) return 0.00437327;
    if(nPUVtx==65) return 0.00405792;
    if(nPUVtx==66) return 0.00357906;
    if(nPUVtx==67) return 0.00306806;
    if(nPUVtx==68) return 0.00271159;
    if(nPUVtx==69) return 0.0023274;
    if(nPUVtx==70) return 0.00197776;
    if(nPUVtx==71) return 0.00166723;
    if(nPUVtx==72) return 0.00139694;
    if(nPUVtx==73) return 0.00117213;
    if(nPUVtx>=74) return 0.000964963;
  }
  if(variation>0){
    if(nPUVtx== 0) return 0.356705;
    if(nPUVtx== 1) return 0.703874;
    if(nPUVtx== 2) return 1.1331;
    if(nPUVtx== 3) return 0.84596;
    if(nPUVtx== 4) return 1.01965;
    if(nPUVtx== 5) return 1.04908;
    if(nPUVtx== 6) return 0.72572;
    if(nPUVtx== 7) return 0.347758;
    if(nPUVtx== 8) return 0.500583;
    if(nPUVtx== 9) return 0.603052;
    if(nPUVtx==10) return 0.632203;
    if(nPUVtx==11) return 0.732849;
    if(nPUVtx==12) return 0.827779;
    if(nPUVtx==13) return 0.912507;
    if(nPUVtx==14) return 0.959919;
    if(nPUVtx==15) return 0.988481;
    if(nPUVtx==16) return 1.02442;
    if(nPUVtx==17) return 1.05282;
    if(nPUVtx==18) return 1.05104;
    if(nPUVtx==19) return 1.02729;
    if(nPUVtx==20) return 1.00559;
    if(nPUVtx==21) return 0.99799;
    if(nPUVtx==22) return 1.01493;
    if(nPUVtx==23) return 1.03752;
    if(nPUVtx==24) return 1.05812;
    if(nPUVtx==25) return 1.0855;
    if(nPUVtx==26) return 1.12067;
    if(nPUVtx==27) return 1.15508;
    if(nPUVtx==28) return 1.1925;
    if(nPUVtx==29) return 1.23145;
    if(nPUVtx==30) return 1.24627;
    if(nPUVtx==31) return 1.26784;
    if(nPUVtx==32) return 1.25902;
    if(nPUVtx==33) return 1.23373;
    if(nPUVtx==34) return 1.18149;
    if(nPUVtx==35) return 1.10478;
    if(nPUVtx==36) return 1.00239;
    if(nPUVtx==37) return 0.889404;
    if(nPUVtx==38) return 0.769071;
    if(nPUVtx==39) return 0.653862;
    if(nPUVtx==40) return 0.532499;
    if(nPUVtx==41) return 0.422593;
    if(nPUVtx==42) return 0.329801;
    if(nPUVtx==43) return 0.249936;
    if(nPUVtx==44) return 0.188554;
    if(nPUVtx==45) return 0.138154;
    if(nPUVtx==46) return 0.096836;
    if(nPUVtx==47) return 0.0686432;
    if(nPUVtx==48) return 0.0473417;
    if(nPUVtx==49) return 0.0324882;
    if(nPUVtx==50) return 0.021705;
    if(nPUVtx==51) return 0.0145288;
    if(nPUVtx==52) return 0.00958437;
    if(nPUVtx==53) return 0.00616762;
    if(nPUVtx==54) return 0.00427747;
    if(nPUVtx==55) return 0.00307056;
    if(nPUVtx==56) return 0.00224154;
    if(nPUVtx==57) return 0.00192254;
    if(nPUVtx==58) return 0.00202293;
    if(nPUVtx==59) return 0.00239738;
    if(nPUVtx==60) return 0.00365154;
    if(nPUVtx==61) return 0.00477849;
    if(nPUVtx==62) return 0.00572481;
    if(nPUVtx==63) return 0.0062735;
    if(nPUVtx==64) return 0.00704536;
    if(nPUVtx==65) return 0.00686592;
    if(nPUVtx==66) return 0.00637147;
    if(nPUVtx==67) return 0.00575494;
    if(nPUVtx==68) return 0.00536637;
    if(nPUVtx==69) return 0.00486586;
    if(nPUVtx==70) return 0.0043736;
    if(nPUVtx==71) return 0.0039046;
    if(nPUVtx==72) return 0.00346908;
    if(nPUVtx==73) return 0.00309034;
    if(nPUVtx==74) return 0.00270442;
  }
  return 1;//should not happen
}
#endif
