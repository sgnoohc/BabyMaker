// Auto generated from https://github.com/sgnoohc/rooutil/blob/master/printsf.py
// Created on 2018-06-20 11:51:25
// Created by the command:
//   > ../rooutil/printsf.py /home/users/phchang/public_html/analysis/www/code/VVVBabyMaker/dilepbabymaker/lepsfrootfiles_20180506/trigeff_v2.root diel_dz_eta_v_eta_sf etamax:etamin trigsf_diel_dz
float trigsf_diel_dz(float etamin_raw, float etamax_raw, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    float etamax = std::min((float) 2.3976, std::max((float) 0.7992, etamax_raw)); // minimum values are just below the first bin upper edge
    float etamin = std::min((float) 2.3976, std::max((float) 0.7992, etamin_raw)); // minimum values are just below the first bin upper edge
    if ((etamin) < 0.8 && (etamax) < 0.8) return 1.00028049946 + isyst * 0.00483495128615;
    if ((etamin) < 1.25 && (etamax) < 0.8) return 0.0 + isyst * 0.0;
    if ((etamin) < 1.6 && (etamax) < 0.8) return 0.0 + isyst * 0.0;
    if ((etamin) < 2.1 && (etamax) < 0.8) return 0.0 + isyst * 0.0;
    if ((etamin) < 2.4 && (etamax) < 0.8) return 0.0 + isyst * 0.0;
    if ((etamin) < 0.8 && (etamax) < 1.25) return 0.99944460392 + isyst * 0.00494549405493;
    if ((etamin) < 1.25 && (etamax) < 1.25) return 0.998993813992 + isyst * 0.0157589431344;
    if ((etamin) < 1.6 && (etamax) < 1.25) return 0.0 + isyst * 0.0;
    if ((etamin) < 2.1 && (etamax) < 1.25) return 0.0 + isyst * 0.0;
    if ((etamin) < 2.4 && (etamax) < 1.25) return 0.0 + isyst * 0.0;
    if ((etamin) < 0.8 && (etamax) < 1.6) return 0.998680591583 + isyst * 0.00817695147214;
    if ((etamin) < 1.25 && (etamax) < 1.6) return 0.996166169643 + isyst * 0.0159527518147;
    if ((etamin) < 1.6 && (etamax) < 1.6) return 1.00009214878 + isyst * 0.0364300043219;
    if ((etamin) < 2.1 && (etamax) < 1.6) return 0.0 + isyst * 0.0;
    if ((etamin) < 2.4 && (etamax) < 1.6) return 0.0 + isyst * 0.0;
    if ((etamin) < 0.8 && (etamax) < 2.1) return 0.999128758907 + isyst * 0.0063914179952;
    if ((etamin) < 1.25 && (etamax) < 2.1) return 1.00214254856 + isyst * 0.0135498574655;
    if ((etamin) < 1.6 && (etamax) < 2.1) return 0.99818778038 + isyst * 0.0249870616275;
    if ((etamin) < 2.1 && (etamax) < 2.1) return 0.999937057495 + isyst * 0.02068548341;
    if ((etamin) < 2.4 && (etamax) < 2.1) return 0.0 + isyst * 0.0;
    if ((etamin) < 0.8) return 1.00001263618 + isyst * 0.0109283085672;
    if ((etamin) < 1.25) return 1.01153898239 + isyst * 0.0274029585483;
    if ((etamin) < 1.6) return 1.00674200058 + isyst * 0.0483432490511;
    if ((etamin) < 2.1) return 1.0038164854 + isyst * 0.0269496096574;
    if ((etamin) < 2.4) return 1.01471173763 + isyst * 0.0919780196749;
    printf("WARNING in trigsf_diel_dz(): the given phase-space (%f, %f) did not fall under any range!\n", etamin, etamax); 
    return 1;
}

// Auto generated from https://github.com/sgnoohc/rooutil/blob/master/printsf.py
// Created on 2018-06-20 11:51:27
// Created by the command:
//   > ../rooutil/printsf.py /home/users/phchang/public_html/analysis/www/code/VVVBabyMaker/dilepbabymaker/lepsfrootfiles_20180506/trigeff_v2.root dimu_dz_eta_v_eta_sf etamax:etamin trigsf_dimu_dz
float trigsf_dimu_dz(float etamin_raw, float etamax_raw, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    float etamax = std::min((float) 2.3976, std::max((float) 0.7992, etamax_raw)); // minimum values are just below the first bin upper edge
    float etamin = std::min((float) 2.3976, std::max((float) 0.7992, etamin_raw)); // minimum values are just below the first bin upper edge
    if ((etamin) < 0.8 && (etamax) < 0.8) return 0.996118366718 + isyst * 0.00681701932655;
    if ((etamin) < 1.25 && (etamax) < 0.8) return 0.0 + isyst * 0.0;
    if ((etamin) < 1.6 && (etamax) < 0.8) return 0.0 + isyst * 0.0;
    if ((etamin) < 2.1 && (etamax) < 0.8) return 0.0 + isyst * 0.0;
    if ((etamin) < 2.4 && (etamax) < 0.8) return 0.0 + isyst * 0.0;
    if ((etamin) < 0.8 && (etamax) < 1.25) return 0.996191799641 + isyst * 0.00666421952969;
    if ((etamin) < 1.25 && (etamax) < 1.25) return 0.996086239815 + isyst * 0.0214403660085;
    if ((etamin) < 1.6 && (etamax) < 1.25) return 0.0 + isyst * 0.0;
    if ((etamin) < 2.1 && (etamax) < 1.25) return 0.0 + isyst * 0.0;
    if ((etamin) < 2.4 && (etamax) < 1.25) return 0.0 + isyst * 0.0;
    if ((etamin) < 0.8 && (etamax) < 1.6) return 0.996351718903 + isyst * 0.00774357095663;
    if ((etamin) < 1.25 && (etamax) < 1.6) return 0.996547758579 + isyst * 0.0182770894763;
    if ((etamin) < 1.6 && (etamax) < 1.6) return 0.995657742023 + isyst * 0.0291970451682;
    if ((etamin) < 2.1 && (etamax) < 1.6) return 0.0 + isyst * 0.0;
    if ((etamin) < 2.4 && (etamax) < 1.6) return 0.0 + isyst * 0.0;
    if ((etamin) < 0.8 && (etamax) < 2.1) return 0.995858967304 + isyst * 0.00721642279339;
    if ((etamin) < 1.25 && (etamax) < 2.1) return 0.997357666492 + isyst * 0.0176345167122;
    if ((etamin) < 1.6 && (etamax) < 2.1) return 0.995307743549 + isyst * 0.018829571909;
    if ((etamin) < 2.1 && (etamax) < 2.1) return 0.996721386909 + isyst * 0.0232543924131;
    if ((etamin) < 2.4 && (etamax) < 2.1) return 0.0 + isyst * 0.0;
    if ((etamin) < 0.8) return 0.996255576611 + isyst * 0.0105509363931;
    if ((etamin) < 1.25) return 0.997964382172 + isyst * 0.027247085075;
    if ((etamin) < 1.6) return 0.998075902462 + isyst * 0.0280089532636;
    if ((etamin) < 2.1) return 0.997106194496 + isyst * 0.0225976187872;
    if ((etamin) < 2.4) return 0.999764502048 + isyst * 0.0433610859445;
    printf("WARNING in trigsf_dimu_dz(): the given phase-space (%f, %f) did not fall under any range!\n", etamin, etamax); 
    return 1;
}

// Auto generated from https://github.com/sgnoohc/rooutil/blob/master/printsf.py
// Created on 2018-06-20 11:51:28
// Created by the command:
//   > ../rooutil/printsf.py /home/users/phchang/public_html/analysis/www/code/VVVBabyMaker/dilepbabymaker/lepsfrootfiles_20180506/trigeff_v2.root mu_lead_leg_eta_v_pt_sf |eta|:pt trigsf_mu_lead
float trigsf_mu_lead(float pt_raw, float eta_raw, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    float eta = std::min((float) 2.3976, std::max((float) 0.7992, eta_raw)); // minimum values are just below the first bin upper edge
    float pt = std::min((float) 199.8, std::max((float) 9.99, pt_raw)); // minimum values are just below the first bin upper edge
    if ((pt) < 10.0 && fabs(eta) < 0.8) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0 && fabs(eta) < 0.8) return 0.975197196007 + isyst * 0.021051708262;
    if ((pt) < 25.0 && fabs(eta) < 0.8) return 0.987936615944 + isyst * 0.0133782911623;
    if ((pt) < 30.0 && fabs(eta) < 0.8) return 0.992974340916 + isyst * 0.00923391620477;
    if ((pt) < 35.0 && fabs(eta) < 0.8) return 0.991539001465 + isyst * 0.00668181020118;
    if ((pt) < 40.0 && fabs(eta) < 0.8) return 0.991355597973 + isyst * 0.00544161818987;
    if ((pt) < 50.0 && fabs(eta) < 0.8) return 0.990868926048 + isyst * 0.00379936453455;
    if ((pt) < 70.0 && fabs(eta) < 0.8) return 0.992579460144 + isyst * 0.00685614918914;
    if ((pt) < 100.0 && fabs(eta) < 0.8) return 0.982521653175 + isyst * 0.0199420522075;
    if ((pt) < 200.0 && fabs(eta) < 0.8) return 0.989154756069 + isyst * 0.0321616232327;
    if ((pt) < 10.0 && fabs(eta) < 1.25) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0 && fabs(eta) < 1.25) return 1.04894685745 + isyst * 0.0330222238927;
    if ((pt) < 25.0 && fabs(eta) < 1.25) return 0.993616163731 + isyst * 0.0201975142736;
    if ((pt) < 30.0 && fabs(eta) < 1.25) return 0.991932332516 + isyst * 0.0142620528169;
    if ((pt) < 35.0 && fabs(eta) < 1.25) return 0.993808209896 + isyst * 0.0102520787787;
    if ((pt) < 40.0 && fabs(eta) < 1.25) return 0.993732154369 + isyst * 0.00781689572383;
    if ((pt) < 50.0 && fabs(eta) < 1.25) return 0.993042886257 + isyst * 0.00518017205895;
    if ((pt) < 70.0 && fabs(eta) < 1.25) return 0.99488312006 + isyst * 0.00927742615113;
    if ((pt) < 100.0 && fabs(eta) < 1.25) return 0.995460748672 + isyst * 0.0279539996213;
    if ((pt) < 200.0 && fabs(eta) < 1.25) return 0.976249098778 + isyst * 0.0430391001621;
    if ((pt) < 10.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0 && fabs(eta) < 1.6) return 1.01391816139 + isyst * 0.0354479093959;
    if ((pt) < 25.0 && fabs(eta) < 1.6) return 1.00988519192 + isyst * 0.0243187650806;
    if ((pt) < 30.0 && fabs(eta) < 1.6) return 1.01178646088 + isyst * 0.0172900968539;
    if ((pt) < 35.0 && fabs(eta) < 1.6) return 1.01553988457 + isyst * 0.0127377889302;
    if ((pt) < 40.0 && fabs(eta) < 1.6) return 1.01530814171 + isyst * 0.00987963493603;
    if ((pt) < 50.0 && fabs(eta) < 1.6) return 1.01014769077 + isyst * 0.00619480644857;
    if ((pt) < 70.0 && fabs(eta) < 1.6) return 0.993604302406 + isyst * 0.0108603764511;
    if ((pt) < 100.0 && fabs(eta) < 1.6) return 0.95081949234 + isyst * 0.031882991904;
    if ((pt) < 200.0 && fabs(eta) < 1.6) return 0.867275297642 + isyst * 0.047315024496;
    if ((pt) < 10.0 && fabs(eta) < 2.1) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0 && fabs(eta) < 2.1) return 0.963060319424 + isyst * 0.0293230622083;
    if ((pt) < 25.0 && fabs(eta) < 2.1) return 0.984658360481 + isyst * 0.020407631396;
    if ((pt) < 30.0 && fabs(eta) < 2.1) return 0.994728863239 + isyst * 0.0149593960982;
    if ((pt) < 35.0 && fabs(eta) < 2.1) return 0.998256385326 + isyst * 0.0111366647228;
    if ((pt) < 40.0 && fabs(eta) < 2.1) return 0.995358586311 + isyst * 0.00893327268644;
    if ((pt) < 50.0 && fabs(eta) < 2.1) return 0.996967792511 + isyst * 0.00572760012051;
    if ((pt) < 70.0 && fabs(eta) < 2.1) return 1.00456023216 + isyst * 0.0102206490507;
    if ((pt) < 100.0 && fabs(eta) < 2.1) return 0.989777088165 + isyst * 0.0316628485442;
    if ((pt) < 200.0 && fabs(eta) < 2.1) return 0.965574264526 + isyst * 0.0515587766573;
    if ((pt) < 10.0) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0) return 0.937939345837 + isyst * 0.0382311116992;
    if ((pt) < 25.0) return 0.928516983986 + isyst * 0.0257906436745;
    if ((pt) < 30.0) return 0.94913315773 + isyst * 0.019398453006;
    if ((pt) < 35.0) return 0.958959817886 + isyst * 0.014651269112;
    if ((pt) < 40.0) return 0.963674902916 + isyst * 0.0121230689827;
    if ((pt) < 50.0) return 0.969935953617 + isyst * 0.0085891701962;
    if ((pt) < 70.0) return 0.976550459862 + isyst * 0.0154124542669;
    if ((pt) < 100.0) return 0.968482613564 + isyst * 0.0475932437943;
    if ((pt) < 200.0) return 0.951705515385 + isyst * 0.0888008033548;
    printf("WARNING in trigsf_mu_lead(): the given phase-space (%f, %f) did not fall under any range!\n", pt, eta); 
    return 1;
}

// Auto generated from https://github.com/sgnoohc/rooutil/blob/master/printsf.py
// Created on 2018-06-20 11:51:30
// Created by the command:
//   > ../rooutil/printsf.py /home/users/phchang/public_html/analysis/www/code/VVVBabyMaker/dilepbabymaker/lepsfrootfiles_20180506/trigeff_v2.root mu_trail_leg_eta_v_pt_sf |eta|:pt trigsf_mu_trail
float trigsf_mu_trail(float pt_raw, float eta_raw, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    float eta = std::min((float) 2.3976, std::max((float) 0.7992, eta_raw)); // minimum values are just below the first bin upper edge
    float pt = std::min((float) 199.8, std::max((float) 9.99, pt_raw)); // minimum values are just below the first bin upper edge
    if ((pt) < 10.0 && fabs(eta) < 0.8) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0 && fabs(eta) < 0.8) return 0.986838579178 + isyst * 0.0175680517141;
    if ((pt) < 25.0 && fabs(eta) < 0.8) return 0.994108080864 + isyst * 0.0134428137195;
    if ((pt) < 30.0 && fabs(eta) < 0.8) return 0.999696552753 + isyst * 0.00928611872251;
    if ((pt) < 35.0 && fabs(eta) < 0.8) return 0.997190892696 + isyst * 0.00671121304884;
    if ((pt) < 40.0 && fabs(eta) < 0.8) return 0.996961116791 + isyst * 0.00546536656952;
    if ((pt) < 50.0 && fabs(eta) < 0.8) return 0.996148407459 + isyst * 0.00381456258875;
    if ((pt) < 70.0 && fabs(eta) < 0.8) return 0.998055815697 + isyst * 0.00688451438586;
    if ((pt) < 100.0 && fabs(eta) < 0.8) return 0.990401387215 + isyst * 0.0200800615317;
    if ((pt) < 200.0 && fabs(eta) < 0.8) return 0.994877099991 + isyst * 0.0322630902311;
    if ((pt) < 10.0 && fabs(eta) < 1.25) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0 && fabs(eta) < 1.25) return 1.00335407257 + isyst * 0.0245286634687;
    if ((pt) < 25.0 && fabs(eta) < 1.25) return 1.00794756413 + isyst * 0.0204110616837;
    if ((pt) < 30.0 && fabs(eta) < 1.25) return 1.00676369667 + isyst * 0.0144291474907;
    if ((pt) < 35.0 && fabs(eta) < 1.25) return 1.00710952282 + isyst * 0.0103539680816;
    if ((pt) < 40.0 && fabs(eta) < 1.25) return 1.00742220879 + isyst * 0.00790074312111;
    if ((pt) < 50.0 && fabs(eta) < 1.25) return 1.00572109222 + isyst * 0.00522993493237;
    if ((pt) < 70.0 && fabs(eta) < 1.25) return 1.00657689571 + isyst * 0.00935513670551;
    if ((pt) < 100.0 && fabs(eta) < 1.25) return 1.01004171371 + isyst * 0.0282848080429;
    if ((pt) < 200.0 && fabs(eta) < 1.25) return 0.991762280464 + isyst * 0.0435696170552;
    if ((pt) < 10.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0 && fabs(eta) < 1.6) return 1.03315198421 + isyst * 0.0283067610666;
    if ((pt) < 25.0 && fabs(eta) < 1.6) return 1.02682197094 + isyst * 0.0246907520872;
    if ((pt) < 30.0 && fabs(eta) < 1.6) return 1.02652442455 + isyst * 0.0175207554542;
    if ((pt) < 35.0 && fabs(eta) < 1.6) return 1.03040349483 + isyst * 0.0129105978574;
    if ((pt) < 40.0 && fabs(eta) < 1.6) return 1.03138744831 + isyst * 0.0100252581687;
    if ((pt) < 50.0 && fabs(eta) < 1.6) return 1.0313668251 + isyst * 0.00631953908532;
    if ((pt) < 70.0 && fabs(eta) < 1.6) return 1.02852964401 + isyst * 0.0112295763796;
    if ((pt) < 100.0 && fabs(eta) < 1.6) return 1.02597737312 + isyst * 0.034337345773;
    if ((pt) < 200.0 && fabs(eta) < 1.6) return 0.990258991718 + isyst * 0.0539182892554;
    if ((pt) < 10.0 && fabs(eta) < 2.1) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0 && fabs(eta) < 2.1) return 1.00831115246 + isyst * 0.023660532171;
    if ((pt) < 25.0 && fabs(eta) < 2.1) return 1.00547719002 + isyst * 0.0207548452654;
    if ((pt) < 30.0 && fabs(eta) < 2.1) return 1.00990927219 + isyst * 0.015141359135;
    if ((pt) < 35.0 && fabs(eta) < 2.1) return 1.01076042652 + isyst * 0.011246404421;
    if ((pt) < 40.0 && fabs(eta) < 2.1) return 1.00764417648 + isyst * 0.00902406223617;
    if ((pt) < 50.0 && fabs(eta) < 2.1) return 1.00737190247 + isyst * 0.00577597794909;
    if ((pt) < 70.0 && fabs(eta) < 2.1) return 1.01454603672 + isyst * 0.0103036616953;
    if ((pt) < 100.0 && fabs(eta) < 2.1) return 1.00005209446 + isyst * 0.0319305840327;
    if ((pt) < 200.0 && fabs(eta) < 2.1) return 0.963351130486 + isyst * 0.0511114339381;
    if ((pt) < 10.0) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0) return 1.00883150101 + isyst * 0.030402631748;
    if ((pt) < 25.0) return 1.00583291054 + isyst * 0.0275271922749;
    if ((pt) < 30.0) return 1.00578463078 + isyst * 0.0203403773409;
    if ((pt) < 35.0) return 1.00688397884 + isyst * 0.015257576007;
    if ((pt) < 40.0) return 1.00515246391 + isyst * 0.0125530147509;
    if ((pt) < 50.0) return 1.00866162777 + isyst * 0.00888368092707;
    if ((pt) < 70.0) return 1.01016926765 + isyst * 0.0158655848246;
    if ((pt) < 100.0) return 0.996241509914 + isyst * 0.048795648058;
    if ((pt) < 200.0) return 0.978178679943 + isyst * 0.0908464221495;
    printf("WARNING in trigsf_mu_trail(): the given phase-space (%f, %f) did not fall under any range!\n", pt, eta); 
    return 1;
}

// Auto generated from https://github.com/sgnoohc/rooutil/blob/master/printsf.py
// Created on 2018-06-20 11:51:32
// Created by the command:
//   > ../rooutil/printsf.py /home/users/phchang/public_html/analysis/www/code/VVVBabyMaker/dilepbabymaker/lepsfrootfiles_20180506/trigeff_v2.root el_lead_leg_eta_v_pt_sf |eta|:pt trigsf_el_lead
float trigsf_el_lead(float pt_raw, float eta_raw, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    float eta = std::min((float) 2.3976, std::max((float) 0.7992, eta_raw)); // minimum values are just below the first bin upper edge
    float pt = std::min((float) 199.8, std::max((float) 9.99, pt_raw)); // minimum values are just below the first bin upper edge
    if ((pt) < 10.0 && fabs(eta) < 0.8) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0 && fabs(eta) < 0.8) return 1.80524885654 + isyst * 1.83352759852;
    if ((pt) < 25.0 && fabs(eta) < 0.8) return 0.996079385281 + isyst * 0.0224382709666;
    if ((pt) < 30.0 && fabs(eta) < 0.8) return 1.01408910751 + isyst * 0.0126051968025;
    if ((pt) < 35.0 && fabs(eta) < 0.8) return 1.00684142113 + isyst * 0.00896884505588;
    if ((pt) < 40.0 && fabs(eta) < 0.8) return 1.0093921423 + isyst * 0.00722940233071;
    if ((pt) < 50.0 && fabs(eta) < 0.8) return 1.00885331631 + isyst * 0.00496409093823;
    if ((pt) < 70.0 && fabs(eta) < 0.8) return 1.01201844215 + isyst * 0.00904518631532;
    if ((pt) < 100.0 && fabs(eta) < 0.8) return 1.00856530666 + isyst * 0.025781056981;
    if ((pt) < 200.0 && fabs(eta) < 0.8) return 1.01176309586 + isyst * 0.0406123785711;
    if ((pt) < 10.0 && fabs(eta) < 1.4) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0 && fabs(eta) < 1.4) return 1.04337739944 + isyst * 1.06352819903;
    if ((pt) < 25.0 && fabs(eta) < 1.4) return 0.872428297997 + isyst * 0.026800028878;
    if ((pt) < 30.0 && fabs(eta) < 1.4) return 1.01646029949 + isyst * 0.0172708513874;
    if ((pt) < 35.0 && fabs(eta) < 1.4) return 1.01307475567 + isyst * 0.0123411229051;
    if ((pt) < 40.0 && fabs(eta) < 1.4) return 1.01660311222 + isyst * 0.00958361389189;
    if ((pt) < 50.0 && fabs(eta) < 1.4) return 1.01473867893 + isyst * 0.00650653902927;
    if ((pt) < 70.0 && fabs(eta) < 1.4) return 1.0156968832 + isyst * 0.0118539673051;
    if ((pt) < 100.0 && fabs(eta) < 1.4) return 1.00990581512 + isyst * 0.0349091788713;
    if ((pt) < 200.0 && fabs(eta) < 1.4) return 1.00422477722 + isyst * 0.0539393355247;
    if ((pt) < 10.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 25.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 30.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 35.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 40.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 50.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 70.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 100.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 200.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 10.0 && fabs(eta) < 2.1) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0 && fabs(eta) < 2.1) return 0.844293832779 + isyst * 0.872388152097;
    if ((pt) < 25.0 && fabs(eta) < 2.1) return 0.778579413891 + isyst * 0.0306814217672;
    if ((pt) < 30.0 && fabs(eta) < 2.1) return 1.01758170128 + isyst * 0.0245827987475;
    if ((pt) < 35.0 && fabs(eta) < 2.1) return 1.01593863964 + isyst * 0.0183047675878;
    if ((pt) < 40.0 && fabs(eta) < 2.1) return 1.02000176907 + isyst * 0.0147699300893;
    if ((pt) < 50.0 && fabs(eta) < 2.1) return 1.016664505 + isyst * 0.00978694278585;
    if ((pt) < 70.0 && fabs(eta) < 2.1) return 1.01920592785 + isyst * 0.0176118271236;
    if ((pt) < 100.0 && fabs(eta) < 2.1) return 1.0130699873 + isyst * 0.0515402983304;
    if ((pt) < 200.0 && fabs(eta) < 2.1) return 1.0221323967 + isyst * 0.0867269750928;
    if ((pt) < 10.0) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0) return 0.0 + isyst * 0.0;
    if ((pt) < 25.0) return 0.50302618742 + isyst * 0.0308027831152;
    if ((pt) < 30.0) return 0.979234993458 + isyst * 0.0368853863856;
    if ((pt) < 35.0) return 1.0042283535 + isyst * 0.0288950163587;
    if ((pt) < 40.0) return 1.01084446907 + isyst * 0.0238268660726;
    if ((pt) < 50.0) return 1.01389193535 + isyst * 0.0168291888501;
    if ((pt) < 70.0) return 1.01002633572 + isyst * 0.030228665191;
    if ((pt) < 100.0) return 1.00445950031 + isyst * 0.092933522291;
    if ((pt) < 200.0) return 1.03309440613 + isyst * 0.17431202791;
    printf("WARNING in trigsf_el_lead(): the given phase-space (%f, %f) did not fall under any range!\n", pt, eta); 
    return 1;
}

// Auto generated from https://github.com/sgnoohc/rooutil/blob/master/printsf.py
// Created on 2018-06-20 11:51:33
// Created by the command:
//   > ../rooutil/printsf.py /home/users/phchang/public_html/analysis/www/code/VVVBabyMaker/dilepbabymaker/lepsfrootfiles_20180506/trigeff_v2.root el_trail_leg_eta_v_pt_sf |eta|:pt trigsf_el_trail
float trigsf_el_trail(float pt_raw, float eta_raw, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    float eta = std::min((float) 2.3976, std::max((float) 0.7992, eta_raw)); // minimum values are just below the first bin upper edge
    float pt = std::min((float) 199.8, std::max((float) 9.99, pt_raw)); // minimum values are just below the first bin upper edge
    if ((pt) < 10.0 && fabs(eta) < 0.8) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0 && fabs(eta) < 0.8) return 0.981039524078 + isyst * 0.0257499610416;
    if ((pt) < 25.0 && fabs(eta) < 0.8) return 1.00071191788 + isyst * 0.0182858253791;
    if ((pt) < 30.0 && fabs(eta) < 0.8) return 1.01488924026 + isyst * 0.0126133666972;
    if ((pt) < 35.0 && fabs(eta) < 0.8) return 1.00685715675 + isyst * 0.00896898349453;
    if ((pt) < 40.0 && fabs(eta) < 0.8) return 1.00939524174 + isyst * 0.00722942416417;
    if ((pt) < 50.0 && fabs(eta) < 0.8) return 1.00885426998 + isyst * 0.00496409551005;
    if ((pt) < 70.0 && fabs(eta) < 0.8) return 1.01201844215 + isyst * 0.00904518631532;
    if ((pt) < 100.0 && fabs(eta) < 0.8) return 1.00856530666 + isyst * 0.025781056981;
    if ((pt) < 200.0 && fabs(eta) < 0.8) return 1.01176309586 + isyst * 0.0406123785711;
    if ((pt) < 10.0 && fabs(eta) < 1.4) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0 && fabs(eta) < 1.4) return 0.982812583447 + isyst * 0.0332581135823;
    if ((pt) < 25.0 && fabs(eta) < 1.4) return 1.001557827 + isyst * 0.0248554152144;
    if ((pt) < 30.0 && fabs(eta) < 1.4) return 1.01931369305 + isyst * 0.0173090746041;
    if ((pt) < 35.0 && fabs(eta) < 1.4) return 1.01313817501 + isyst * 0.0123418872433;
    if ((pt) < 40.0 && fabs(eta) < 1.4) return 1.01661133766 + isyst * 0.00958369041482;
    if ((pt) < 50.0 && fabs(eta) < 1.4) return 1.01474034786 + isyst * 0.00650655011048;
    if ((pt) < 70.0 && fabs(eta) < 1.4) return 1.01570248604 + isyst * 0.0118540328084;
    if ((pt) < 100.0 && fabs(eta) < 1.4) return 1.00990581512 + isyst * 0.0349091788713;
    if ((pt) < 200.0 && fabs(eta) < 1.4) return 1.00422477722 + isyst * 0.0539393355247;
    if ((pt) < 10.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 25.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 30.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 35.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 40.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 50.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 70.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 100.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 200.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 10.0 && fabs(eta) < 2.1) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0 && fabs(eta) < 2.1) return 0.953419625759 + isyst * 0.0440718388036;
    if ((pt) < 25.0 && fabs(eta) < 2.1) return 1.0065882206 + isyst * 0.0339138171602;
    if ((pt) < 30.0 && fabs(eta) < 2.1) return 1.0203204155 + isyst * 0.0246332172719;
    if ((pt) < 35.0 && fabs(eta) < 2.1) return 1.0161536932 + isyst * 0.0183085983262;
    if ((pt) < 40.0 && fabs(eta) < 2.1) return 1.02008295059 + isyst * 0.0147710911841;
    if ((pt) < 50.0 && fabs(eta) < 2.1) return 1.01669347286 + isyst * 0.0097872168233;
    if ((pt) < 70.0 && fabs(eta) < 2.1) return 1.01922380924 + isyst * 0.0176121320951;
    if ((pt) < 100.0 && fabs(eta) < 2.1) return 1.0130699873 + isyst * 0.0515402983304;
    if ((pt) < 200.0 && fabs(eta) < 2.1) return 1.0221323967 + isyst * 0.0867269750928;
    if ((pt) < 10.0) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0) return 0.825999140739 + isyst * 0.0589901647314;
    if ((pt) < 25.0) return 0.936985135078 + isyst * 0.0489588735459;
    if ((pt) < 30.0) return 0.993826746941 + isyst * 0.0374236690943;
    if ((pt) < 35.0) return 1.0043336153 + isyst * 0.0288980064906;
    if ((pt) < 40.0) return 1.01095223427 + isyst * 0.0238293704041;
    if ((pt) < 50.0) return 1.01399612427 + isyst * 0.0168308884646;
    if ((pt) < 70.0) return 1.01009571552 + isyst * 0.0302307009845;
    if ((pt) < 100.0) return 1.00445950031 + isyst * 0.092933522291;
    if ((pt) < 200.0) return 1.03309440613 + isyst * 0.17431202791;
    printf("WARNING in trigsf_el_trail(): the given phase-space (%f, %f) did not fall under any range!\n", pt, eta); 
    return 1;
}

// Auto generated from https://github.com/sgnoohc/rooutil/blob/master/printsf.py
// Created on 2018-06-20 11:51:35
// Created by the command:
//   > ../rooutil/printsf.py /home/users/phchang/public_html/analysis/www/code/VVVBabyMaker/dilepbabymaker/lepsfrootfiles_20180506/trigeff_v2.root diel_dz_eta_v_eta_data etamax:etamin trigdata_diel_dz
float trigdata_diel_dz(float etamin_raw, float etamax_raw, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    float etamax = std::min((float) 2.3976, std::max((float) 0.7992, etamax_raw)); // minimum values are just below the first bin upper edge
    float etamin = std::min((float) 2.3976, std::max((float) 0.7992, etamin_raw)); // minimum values are just below the first bin upper edge
    if ((etamin) < 0.8 && (etamax) < 0.8) return 0.99167329073 + isyst * 0.00202237884279;
    if ((etamin) < 1.25 && (etamax) < 0.8) return 0.0 + isyst * 0.0;
    if ((etamin) < 1.6 && (etamax) < 0.8) return 0.0 + isyst * 0.0;
    if ((etamin) < 2.1 && (etamax) < 0.8) return 0.0 + isyst * 0.0;
    if ((etamin) < 2.4 && (etamax) < 0.8) return 0.0 + isyst * 0.0;
    if ((etamin) < 0.8 && (etamax) < 1.25) return 0.993380784988 + isyst * 0.00207678619608;
    if ((etamin) < 1.25 && (etamax) < 1.25) return 0.9949452281 + isyst * 0.00663357923717;
    if ((etamin) < 1.6 && (etamax) < 1.25) return 0.0 + isyst * 0.0;
    if ((etamin) < 2.1 && (etamax) < 1.25) return 0.0 + isyst * 0.0;
    if ((etamin) < 2.4 && (etamax) < 1.25) return 0.0 + isyst * 0.0;
    if ((etamin) < 0.8 && (etamax) < 1.6) return 0.990169465542 + isyst * 0.00358773783115;
    if ((etamin) < 1.25 && (etamax) < 1.6) return 0.990179359913 + isyst * 0.00692979729748;
    if ((etamin) < 1.6 && (etamax) < 1.6) return 0.988332271576 + isyst * 0.0157868368838;
    if ((etamin) < 2.1 && (etamax) < 1.6) return 0.0 + isyst * 0.0;
    if ((etamin) < 2.4 && (etamax) < 1.6) return 0.0 + isyst * 0.0;
    if ((etamin) < 0.8 && (etamax) < 2.1) return 0.987252056599 + isyst * 0.00288928200473;
    if ((etamin) < 1.25 && (etamax) < 2.1) return 0.988522827625 + isyst * 0.00604690379428;
    if ((etamin) < 1.6 && (etamax) < 2.1) return 0.986233174801 + isyst * 0.0112520511495;
    if ((etamin) < 2.1 && (etamax) < 2.1) return 0.982386767864 + isyst * 0.00935431288644;
    if ((etamin) < 2.4 && (etamax) < 2.1) return 0.0 + isyst * 0.0;
    if ((etamin) < 0.8) return 0.983280599117 + isyst * 0.0054717588547;
    if ((etamin) < 1.25) return 0.988543689251 + isyst * 0.0195371804617;
    if ((etamin) < 1.6) return 0.981931447983 + isyst * 0.0348214928483;
    if ((etamin) < 2.1) return 0.979759395123 + isyst * 0.0192452980226;
    if ((etamin) < 2.4) return 0.983108103275 + isyst * 0.0811573725718;
    printf("WARNING in trigdata_diel_dz(): the given phase-space (%f, %f) did not fall under any range!\n", etamin, etamax); 
    return 1;
}

// Auto generated from https://github.com/sgnoohc/rooutil/blob/master/printsf.py
// Created on 2018-06-20 11:51:36
// Created by the command:
//   > ../rooutil/printsf.py /home/users/phchang/public_html/analysis/www/code/VVVBabyMaker/dilepbabymaker/lepsfrootfiles_20180506/trigeff_v2.root dimu_dz_eta_v_eta_data etamax:etamin trigdata_dimu_dz
float trigdata_dimu_dz(float etamin_raw, float etamax_raw, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    float etamax = std::min((float) 2.3976, std::max((float) 0.7992, etamax_raw)); // minimum values are just below the first bin upper edge
    float etamin = std::min((float) 2.3976, std::max((float) 0.7992, etamin_raw)); // minimum values are just below the first bin upper edge
    if ((etamin) < 0.8 && (etamax) < 0.8) return 0.8464230299 + isyst * 0.000633248210511;
    if ((etamin) < 1.25 && (etamax) < 0.8) return 0.0 + isyst * 0.0;
    if ((etamin) < 1.6 && (etamax) < 0.8) return 0.0 + isyst * 0.0;
    if ((etamin) < 2.1 && (etamax) < 0.8) return 0.0 + isyst * 0.0;
    if ((etamin) < 2.4 && (etamax) < 0.8) return 0.0 + isyst * 0.0;
    if ((etamin) < 0.8 && (etamax) < 1.25) return 0.873307883739 + isyst * 0.000640227361499;
    if ((etamin) < 1.25 && (etamax) < 1.25) return 0.897286653519 + isyst * 0.00210225034977;
    if ((etamin) < 1.6 && (etamax) < 1.25) return 0.0 + isyst * 0.0;
    if ((etamin) < 2.1 && (etamax) < 1.25) return 0.0 + isyst * 0.0;
    if ((etamin) < 2.4 && (etamax) < 1.25) return 0.0 + isyst * 0.0;
    if ((etamin) < 0.8 && (etamax) < 1.6) return 0.85926169157 + isyst * 0.000739905533876;
    if ((etamin) < 1.25 && (etamax) < 1.6) return 0.877065479755 + isyst * 0.00179605811619;
    if ((etamin) < 1.6 && (etamax) < 1.6) return 0.858474969864 + isyst * 0.00285828484821;
    if ((etamin) < 2.1 && (etamax) < 1.6) return 0.0 + isyst * 0.0;
    if ((etamin) < 2.4 && (etamax) < 1.6) return 0.0 + isyst * 0.0;
    if ((etamin) < 0.8 && (etamax) < 2.1) return 0.82297706604 + isyst * 0.000672927354893;
    if ((etamin) < 1.25 && (etamax) < 2.1) return 0.841432511806 + isyst * 0.00166855197768;
    if ((etamin) < 1.6 && (etamax) < 2.1) return 0.824828624725 + isyst * 0.00178413618768;
    if ((etamin) < 2.1 && (etamax) < 2.1) return 0.791739761829 + isyst * 0.00209469661641;
    if ((etamin) < 2.4 && (etamax) < 2.1) return 0.0 + isyst * 0.0;
    if ((etamin) < 0.8) return 0.836181819439 + isyst * 0.00103221183516;
    if ((etamin) < 1.25) return 0.862843751907 + isyst * 0.00269080793508;
    if ((etamin) < 1.6) return 0.843576312065 + isyst * 0.00270671351058;
    if ((etamin) < 2.1) return 0.811420619488 + isyst * 0.00217863515995;
    if ((etamin) < 2.4) return 0.832342028618 + isyst * 0.00433814912672;
    printf("WARNING in trigdata_dimu_dz(): the given phase-space (%f, %f) did not fall under any range!\n", etamin, etamax); 
    return 1;
}

// Auto generated from https://github.com/sgnoohc/rooutil/blob/master/printsf.py
// Created on 2018-06-20 11:51:38
// Created by the command:
//   > ../rooutil/printsf.py /home/users/phchang/public_html/analysis/www/code/VVVBabyMaker/dilepbabymaker/lepsfrootfiles_20180506/trigeff_v2.root mu_lead_leg_eta_v_pt_data |eta|:pt trigdata_mu_lead
float trigdata_mu_lead(float pt_raw, float eta_raw, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    float eta = std::min((float) 2.3976, std::max((float) 0.7992, eta_raw)); // minimum values are just below the first bin upper edge
    float pt = std::min((float) 199.8, std::max((float) 9.99, pt_raw)); // minimum values are just below the first bin upper edge
    if ((pt) < 10.0 && fabs(eta) < 0.8) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0 && fabs(eta) < 0.8) return 0.478672713041 + isyst * 0.00214955547882;
    if ((pt) < 25.0 && fabs(eta) < 0.8) return 0.923292994499 + isyst * 0.00261568426726;
    if ((pt) < 30.0 && fabs(eta) < 0.8) return 0.925851583481 + isyst * 0.00179862773612;
    if ((pt) < 35.0 && fabs(eta) < 0.8) return 0.926776170731 + isyst * 0.00129862325979;
    if ((pt) < 40.0 && fabs(eta) < 0.8) return 0.926838457584 + isyst * 0.00104417308337;
    if ((pt) < 50.0 && fabs(eta) < 0.8) return 0.92600029707 + isyst * 0.000720804330712;
    if ((pt) < 70.0 && fabs(eta) < 0.8) return 0.924240112305 + isyst * 0.00128550069933;
    if ((pt) < 100.0 && fabs(eta) < 0.8) return 0.919629693031 + isyst * 0.00349354641279;
    if ((pt) < 200.0 && fabs(eta) < 0.8) return 0.911630868912 + isyst * 0.005460428127;
    if ((pt) < 10.0 && fabs(eta) < 1.25) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0 && fabs(eta) < 1.25) return 0.436684340239 + isyst * 0.00270982654724;
    if ((pt) < 25.0 && fabs(eta) < 1.25) return 0.928256571293 + isyst * 0.00384368294922;
    if ((pt) < 30.0 && fabs(eta) < 1.25) return 0.929984033108 + isyst * 0.00271233750153;
    if ((pt) < 35.0 && fabs(eta) < 1.25) return 0.93038392067 + isyst * 0.0019587792055;
    if ((pt) < 40.0 && fabs(eta) < 1.25) return 0.930424451828 + isyst * 0.00150239961106;
    if ((pt) < 50.0 && fabs(eta) < 1.25) return 0.930815398693 + isyst * 0.000991746746393;
    if ((pt) < 70.0 && fabs(eta) < 1.25) return 0.930238008499 + isyst * 0.00176169573298;
    if ((pt) < 100.0 && fabs(eta) < 1.25) return 0.928259670734 + isyst * 0.00491019260888;
    if ((pt) < 200.0 && fabs(eta) < 1.25) return 0.921125710011 + isyst * 0.00774141462348;
    if ((pt) < 10.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0 && fabs(eta) < 1.6) return 0.430942744017 + isyst * 0.00298993999172;
    if ((pt) < 25.0 && fabs(eta) < 1.6) return 0.961563050747 + isyst * 0.004561684942;
    if ((pt) < 30.0 && fabs(eta) < 1.6) return 0.96415913105 + isyst * 0.00327712821127;
    if ((pt) < 35.0 && fabs(eta) < 1.6) return 0.964199542999 + isyst * 0.00244843786455;
    if ((pt) < 40.0 && fabs(eta) < 1.6) return 0.963147044182 + isyst * 0.00192108481257;
    if ((pt) < 50.0 && fabs(eta) < 1.6) return 0.958740651608 + isyst * 0.00121658309362;
    if ((pt) < 70.0 && fabs(eta) < 1.6) return 0.944894552231 + isyst * 0.00213483789783;
    if ((pt) < 100.0 && fabs(eta) < 1.6) return 0.900297224522 + isyst * 0.00588152353686;
    if ((pt) < 200.0 && fabs(eta) < 1.6) return 0.828313231468 + isyst * 0.00910693469183;
    if ((pt) < 10.0 && fabs(eta) < 2.1) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0 && fabs(eta) < 2.1) return 0.389967679977 + isyst * 0.00234321365877;
    if ((pt) < 25.0 && fabs(eta) < 2.1) return 0.912961065769 + isyst * 0.00381891170918;
    if ((pt) < 30.0 && fabs(eta) < 2.1) return 0.922979354858 + isyst * 0.00280534919422;
    if ((pt) < 35.0 && fabs(eta) < 2.1) return 0.92571169138 + isyst * 0.00211222313625;
    if ((pt) < 40.0 && fabs(eta) < 2.1) return 0.927835345268 + isyst * 0.00171856949441;
    if ((pt) < 50.0 && fabs(eta) < 2.1) return 0.929073929787 + isyst * 0.00113316650339;
    if ((pt) < 70.0 && fabs(eta) < 2.1) return 0.930434525013 + isyst * 0.00202419806773;
    if ((pt) < 100.0 && fabs(eta) < 2.1) return 0.925391376019 + isyst * 0.00587530008893;
    if ((pt) < 200.0 && fabs(eta) < 2.1) return 0.889071822166 + isyst * 0.00976452971355;
    if ((pt) < 10.0) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0) return 0.331754356623 + isyst * 0.00287613381802;
    if ((pt) < 25.0) return 0.82733720541 + isyst * 0.00496433448;
    if ((pt) < 30.0) return 0.858947336674 + isyst * 0.00373602263843;
    if ((pt) < 35.0) return 0.877158403397 + isyst * 0.002881592023;
    if ((pt) < 40.0) return 0.88671630621 + isyst * 0.00244971974101;
    if ((pt) < 50.0) return 0.896263122559 + isyst * 0.00179797659277;
    if ((pt) < 70.0) return 0.900450646877 + isyst * 0.00323035977617;
    if ((pt) < 100.0) return 0.907149612904 + isyst * 0.00955089294127;
    if ((pt) < 200.0) return 0.878123819828 + isyst * 0.0178055259929;
    printf("WARNING in trigdata_mu_lead(): the given phase-space (%f, %f) did not fall under any range!\n", pt, eta); 
    return 1;
}

// Auto generated from https://github.com/sgnoohc/rooutil/blob/master/printsf.py
// Created on 2018-06-20 11:51:40
// Created by the command:
//   > ../rooutil/printsf.py /home/users/phchang/public_html/analysis/www/code/VVVBabyMaker/dilepbabymaker/lepsfrootfiles_20180506/trigeff_v2.root mu_trail_leg_eta_v_pt_data |eta|:pt trigdata_mu_trail
float trigdata_mu_trail(float pt_raw, float eta_raw, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    float eta = std::min((float) 2.3976, std::max((float) 0.7992, eta_raw)); // minimum values are just below the first bin upper edge
    float pt = std::min((float) 199.8, std::max((float) 9.99, pt_raw)); // minimum values are just below the first bin upper edge
    if ((pt) < 10.0 && fabs(eta) < 0.8) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0 && fabs(eta) < 0.8) return 0.920872926712 + isyst * 0.00339814941781;
    if ((pt) < 25.0 && fabs(eta) < 0.8) return 0.934034824371 + isyst * 0.00263819264841;
    if ((pt) < 30.0 && fabs(eta) < 0.8) return 0.935821413994 + isyst * 0.00181296037721;
    if ((pt) < 35.0 && fabs(eta) < 0.8) return 0.936419546604 + isyst * 0.00130862458267;
    if ((pt) < 40.0 && fabs(eta) < 0.8) return 0.936534643173 + isyst * 0.00105225833912;
    if ((pt) < 50.0 && fabs(eta) < 0.8) return 0.935491979122 + isyst * 0.00072627214129;
    if ((pt) < 70.0 && fabs(eta) < 0.8) return 0.934029996395 + isyst * 0.00129557417944;
    if ((pt) < 100.0 && fabs(eta) < 0.8) return 0.930490911007 + isyst * 0.00352404337691;
    if ((pt) < 200.0 && fabs(eta) < 0.8) return 0.925472199917 + isyst * 0.00552160700337;
    if ((pt) < 10.0 && fabs(eta) < 1.25) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0 && fabs(eta) < 1.25) return 0.948898017406 + isyst * 0.0046524458998;
    if ((pt) < 25.0 && fabs(eta) < 1.25) return 0.955552458763 + isyst * 0.00392729130991;
    if ((pt) < 30.0 && fabs(eta) < 1.25) return 0.954921245575 + isyst * 0.00276616146186;
    if ((pt) < 35.0 && fabs(eta) < 1.25) return 0.954522132874 + isyst * 0.00199639208067;
    if ((pt) < 40.0 && fabs(eta) < 1.25) return 0.953561842442 + isyst * 0.0015300531376;
    if ((pt) < 50.0 && fabs(eta) < 1.25) return 0.953604578972 + isyst * 0.00100972039121;
    if ((pt) < 70.0 && fabs(eta) < 1.25) return 0.952963709831 + isyst * 0.00179355081294;
    if ((pt) < 100.0 && fabs(eta) < 1.25) return 0.951306581497 + isyst * 0.00500039164634;
    if ((pt) < 200.0 && fabs(eta) < 1.25) return 0.947101056576 + isyst * 0.00790269808945;
    if ((pt) < 10.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0 && fabs(eta) < 1.6) return 0.974151551723 + isyst * 0.00528013542692;
    if ((pt) < 25.0 && fabs(eta) < 1.6) return 0.982259869576 + isyst * 0.0046347760973;
    if ((pt) < 30.0 && fabs(eta) < 1.6) return 0.981830060482 + isyst * 0.00332186592723;
    if ((pt) < 35.0 && fabs(eta) < 1.6) return 0.981713593006 + isyst * 0.00248156506182;
    if ((pt) < 40.0 && fabs(eta) < 1.6) return 0.981789171696 + isyst * 0.00194877493336;
    if ((pt) < 50.0 && fabs(eta) < 1.6) return 0.981189370155 + isyst * 0.00123777624309;
    if ((pt) < 70.0 && fabs(eta) < 1.6) return 0.980906546116 + isyst * 0.00219518438351;
    if ((pt) < 100.0 && fabs(eta) < 1.6) return 0.976019561291 + isyst * 0.00624469166744;
    if ((pt) < 200.0 && fabs(eta) < 1.6) return 0.94797372818 + isyst * 0.0100563251462;
    if ((pt) < 10.0 && fabs(eta) < 2.1) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0 && fabs(eta) < 2.1) return 0.941268801689 + isyst * 0.00430224269445;
    if ((pt) < 25.0 && fabs(eta) < 2.1) return 0.946330308914 + isyst * 0.00392184180004;
    if ((pt) < 30.0 && fabs(eta) < 2.1) return 0.947584271431 + isyst * 0.00286062332388;
    if ((pt) < 35.0 && fabs(eta) < 2.1) return 0.946399211884 + isyst * 0.00214713536192;
    if ((pt) < 40.0 && fabs(eta) < 2.1) return 0.946510136127 + isyst * 0.00174416531272;
    if ((pt) < 50.0 && fabs(eta) < 2.1) return 0.94539475441 + isyst * 0.00114790148859;
    if ((pt) < 70.0 && fabs(eta) < 2.1) return 0.945910274982 + isyst * 0.00204912724366;
    if ((pt) < 100.0 && fabs(eta) < 2.1) return 0.941394150257 + isyst * 0.00595045849224;
    if ((pt) < 200.0 && fabs(eta) < 2.1) return 0.909736037254 + isyst * 0.00993123003279;
    if ((pt) < 10.0) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0) return 0.934750020504 + isyst * 0.00581900716201;
    if ((pt) < 25.0) return 0.945064783096 + isyst * 0.00547404350699;
    if ((pt) < 30.0) return 0.945610463619 + isyst * 0.00401029908246;
    if ((pt) < 35.0) return 0.948687791824 + isyst * 0.00305334459618;
    if ((pt) < 40.0) return 0.949368298054 + isyst * 0.00257652920031;
    if ((pt) < 50.0) return 0.949946165085 + isyst * 0.00187705836722;
    if ((pt) < 70.0) return 0.947215974331 + isyst * 0.00335369998566;
    if ((pt) < 100.0) return 0.944848656654 + isyst * 0.00984319670994;
    if ((pt) < 200.0) return 0.919261813164 + isyst * 0.0184162647743;
    printf("WARNING in trigdata_mu_trail(): the given phase-space (%f, %f) did not fall under any range!\n", pt, eta); 
    return 1;
}

// Auto generated from https://github.com/sgnoohc/rooutil/blob/master/printsf.py
// Created on 2018-06-20 11:51:42
// Created by the command:
//   > ../rooutil/printsf.py /home/users/phchang/public_html/analysis/www/code/VVVBabyMaker/dilepbabymaker/lepsfrootfiles_20180506/trigeff_v2.root el_lead_leg_eta_v_pt_data |eta|:pt trigdata_el_lead
float trigdata_el_lead(float pt_raw, float eta_raw, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    float eta = std::min((float) 2.3976, std::max((float) 0.7992, eta_raw)); // minimum values are just below the first bin upper edge
    float pt = std::min((float) 199.8, std::max((float) 9.99, pt_raw)); // minimum values are just below the first bin upper edge
    if ((pt) < 10.0 && fabs(eta) < 0.8) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0 && fabs(eta) < 0.8) return 0.00050448521506 + isyst * 8.92037169391e-05;
    if ((pt) < 25.0 && fabs(eta) < 0.8) return 0.461387574673 + isyst * 0.00222976242116;
    if ((pt) < 30.0 && fabs(eta) < 0.8) return 0.934977531433 + isyst * 0.00245368717683;
    if ((pt) < 35.0 && fabs(eta) < 0.8) return 0.947184741497 + isyst * 0.00173999542634;
    if ((pt) < 40.0 && fabs(eta) < 0.8) return 0.957806050777 + isyst * 0.00136262942254;
    if ((pt) < 50.0 && fabs(eta) < 0.8) return 0.96155244112 + isyst * 0.000920512359847;
    if ((pt) < 70.0 && fabs(eta) < 0.8) return 0.965367615223 + isyst * 0.00166941835984;
    if ((pt) < 100.0 && fabs(eta) < 0.8) return 0.969835579395 + isyst * 0.00447161707115;
    if ((pt) < 200.0 && fabs(eta) < 0.8) return 0.969730913639 + isyst * 0.00682288006359;
    if ((pt) < 10.0 && fabs(eta) < 1.4) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0 && fabs(eta) < 1.4) return 0.000588128867093 + isyst * 0.000115375468997;
    if ((pt) < 25.0 && fabs(eta) < 1.4) return 0.405426889658 + isyst * 0.00261904837259;
    if ((pt) < 30.0 && fabs(eta) < 1.4) return 0.948272705078 + isyst * 0.00329260887274;
    if ((pt) < 35.0 && fabs(eta) < 1.4) return 0.961216688156 + isyst * 0.00244412176778;
    if ((pt) < 40.0 && fabs(eta) < 1.4) return 0.966700553894 + isyst * 0.00192295412348;
    if ((pt) < 50.0 && fabs(eta) < 1.4) return 0.96971642971 + isyst * 0.00126339672505;
    if ((pt) < 70.0 && fabs(eta) < 1.4) return 0.971560001373 + isyst * 0.00228190386615;
    if ((pt) < 100.0 && fabs(eta) < 1.4) return 0.976942360401 + isyst * 0.00624462078774;
    if ((pt) < 200.0 && fabs(eta) < 1.4) return 0.980085432529 + isyst * 0.00981719292445;
    if ((pt) < 10.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 25.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 30.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 35.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 40.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 50.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 70.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 100.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 200.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 10.0 && fabs(eta) < 2.1) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0 && fabs(eta) < 2.1) return 0.000714830355719 + isyst * 0.000184634357698;
    if ((pt) < 25.0 && fabs(eta) < 2.1) return 0.434408068657 + isyst * 0.00398518478312;
    if ((pt) < 30.0 && fabs(eta) < 2.1) return 0.96294426918 + isyst * 0.00494792838285;
    if ((pt) < 35.0 && fabs(eta) < 2.1) return 0.971165657043 + isyst * 0.00374962837805;
    if ((pt) < 40.0 && fabs(eta) < 2.1) return 0.974741280079 + isyst * 0.00305453358961;
    if ((pt) < 50.0 && fabs(eta) < 2.1) return 0.976086974144 + isyst * 0.00220542216985;
    if ((pt) < 70.0 && fabs(eta) < 2.1) return 0.976740777493 + isyst * 0.00407077719629;
    if ((pt) < 100.0 && fabs(eta) < 2.1) return 0.97973382473 + isyst * 0.010832308584;
    if ((pt) < 200.0 && fabs(eta) < 2.1) return 0.986845970154 + isyst * 0.016928373979;
    if ((pt) < 10.0) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0) return 0.000214247455006 + isyst * 0.000151512056785;
    if ((pt) < 25.0) return 0.288551717997 + isyst * 0.00492066383934;
    if ((pt) < 30.0) return 0.913588643074 + isyst * 0.00770747072602;
    if ((pt) < 35.0) return 0.953131556511 + isyst * 0.00609843556427;
    if ((pt) < 40.0) return 0.960922896862 + isyst * 0.00525047877651;
    if ((pt) < 50.0) return 0.964273512363 + isyst * 0.00413014478686;
    if ((pt) < 70.0) return 0.967056334019 + isyst * 0.0079481212044;
    if ((pt) < 100.0) return 0.970224559307 + isyst * 0.0219625096789;
    if ((pt) < 200.0) return 0.974473536015 + isyst * 0.0350409747407;
    printf("WARNING in trigdata_el_lead(): the given phase-space (%f, %f) did not fall under any range!\n", pt, eta); 
    return 1;
}

// Auto generated from https://github.com/sgnoohc/rooutil/blob/master/printsf.py
// Created on 2018-06-20 11:51:43
// Created by the command:
//   > ../rooutil/printsf.py /home/users/phchang/public_html/analysis/www/code/VVVBabyMaker/dilepbabymaker/lepsfrootfiles_20180506/trigeff_v2.root el_trail_leg_eta_v_pt_data |eta|:pt trigdata_el_trail
float trigdata_el_trail(float pt_raw, float eta_raw, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    float eta = std::min((float) 2.3976, std::max((float) 0.7992, eta_raw)); // minimum values are just below the first bin upper edge
    float pt = std::min((float) 199.8, std::max((float) 9.99, pt_raw)); // minimum values are just below the first bin upper edge
    if ((pt) < 10.0 && fabs(eta) < 0.8) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0 && fabs(eta) < 0.8) return 0.877000212669 + isyst * 0.00509426142776;
    if ((pt) < 25.0 && fabs(eta) < 0.8) return 0.930303752422 + isyst * 0.00363888337738;
    if ((pt) < 30.0 && fabs(eta) < 0.8) return 0.936275362968 + isyst * 0.00245621290149;
    if ((pt) < 35.0 && fabs(eta) < 0.8) return 0.947199523449 + isyst * 0.00174001559731;
    if ((pt) < 40.0 && fabs(eta) < 0.8) return 0.957808971405 + isyst * 0.00136263256927;
    if ((pt) < 50.0 && fabs(eta) < 0.8) return 0.96155333519 + isyst * 0.000920513000743;
    if ((pt) < 70.0 && fabs(eta) < 0.8) return 0.965367615223 + isyst * 0.00166941835984;
    if ((pt) < 100.0 && fabs(eta) < 0.8) return 0.969835579395 + isyst * 0.00447161707115;
    if ((pt) < 200.0 && fabs(eta) < 0.8) return 0.969730913639 + isyst * 0.00682288006359;
    if ((pt) < 10.0 && fabs(eta) < 1.4) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0 && fabs(eta) < 1.4) return 0.872624874115 + isyst * 0.00607979240802;
    if ((pt) < 25.0 && fabs(eta) < 1.4) return 0.944443106651 + isyst * 0.00470184863292;
    if ((pt) < 30.0 && fabs(eta) < 1.4) return 0.952896773815 + isyst * 0.00330454153895;
    if ((pt) < 35.0 && fabs(eta) < 1.4) return 0.961276888847 + isyst * 0.00244423582999;
    if ((pt) < 40.0 && fabs(eta) < 1.4) return 0.966708362103 + isyst * 0.00192296566459;
    if ((pt) < 50.0 && fabs(eta) < 1.4) return 0.96971809864 + isyst * 0.0012633983498;
    if ((pt) < 70.0 && fabs(eta) < 1.4) return 0.971565425396 + isyst * 0.0022819133972;
    if ((pt) < 100.0 && fabs(eta) < 1.4) return 0.976942360401 + isyst * 0.00624462078774;
    if ((pt) < 200.0 && fabs(eta) < 1.4) return 0.980085432529 + isyst * 0.00981719292445;
    if ((pt) < 10.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 25.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 30.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 35.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 40.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 50.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 70.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 100.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 200.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((pt) < 10.0 && fabs(eta) < 2.1) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0 && fabs(eta) < 2.1) return 0.826439201832 + isyst * 0.00848132923258;
    if ((pt) < 25.0 && fabs(eta) < 2.1) return 0.959271073341 + isyst * 0.0069211953016;
    if ((pt) < 30.0 && fabs(eta) < 2.1) return 0.967710614204 + isyst * 0.00496617718441;
    if ((pt) < 35.0 && fabs(eta) < 2.1) return 0.971371293068 + isyst * 0.0037502209587;
    if ((pt) < 40.0 && fabs(eta) < 2.1) return 0.974818825722 + isyst * 0.0030547150868;
    if ((pt) < 50.0 && fabs(eta) < 2.1) return 0.976114690304 + isyst * 0.0022054689854;
    if ((pt) < 70.0 && fabs(eta) < 2.1) return 0.97675794363 + isyst * 0.00407083064138;
    if ((pt) < 100.0 && fabs(eta) < 2.1) return 0.97973382473 + isyst * 0.010832308584;
    if ((pt) < 200.0 && fabs(eta) < 2.1) return 0.986845970154 + isyst * 0.016928373979;
    if ((pt) < 10.0) return 0.0 + isyst * 0.0;
    if ((pt) < 20.0) return 0.728869855404 + isyst * 0.0116184710407;
    if ((pt) < 25.0) return 0.88838237524 + isyst * 0.0104521561727;
    if ((pt) < 30.0) return 0.927452504635 + isyst * 0.00779381211613;
    if ((pt) < 35.0) return 0.953231453896 + isyst * 0.00609891107417;
    if ((pt) < 40.0) return 0.961025297642 + isyst * 0.00525089566696;
    if ((pt) < 50.0) return 0.964372575283 + isyst * 0.00413046109066;
    if ((pt) < 70.0) return 0.967122733593 + isyst * 0.00794852833318;
    if ((pt) < 100.0) return 0.970224559307 + isyst * 0.0219625096789;
    if ((pt) < 200.0) return 0.974473536015 + isyst * 0.0350409747407;
    printf("WARNING in trigdata_el_trail(): the given phase-space (%f, %f) did not fall under any range!\n", pt, eta); 
    return 1;
}

// Auto generated from https://github.com/sgnoohc/rooutil/blob/master/printsf.py
// Created on 2018-06-20 11:51:45
// Created by the command:
//   > ../rooutil/printsf.py /home/users/phchang/public_html/analysis/www/code/VVVBabyMaker/dilepbabymaker/lepsfrootfiles_20180506/egammaEffi.txt_EGM2D.root EGamma_SF2D eta:pt lepsf_elec_reco
float lepsf_elec_reco(float pt_raw, float eta_raw, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    float eta = std::min((float) 2.4975, std::max((float) -2.45245, eta_raw)); // minimum values are just below the first bin upper edge
    float pt = std::min((float) 499.5, std::max((float) 499.5, pt_raw)); // minimum values are just below the first bin upper edge
    if ((pt) < 500.0 && (eta) < -2.45) return 1.31760430336 + isyst * 0.0182387273858;
    if ((pt) < 500.0 && (eta) < -2.4) return 1.11378002167 + isyst * 0.0110667218714;
    if ((pt) < 500.0 && (eta) < -2.3) return 1.02462530136 + isyst * 0.00815834887034;
    if ((pt) < 500.0 && (eta) < -2.2) return 1.013641119 + isyst * 0.00713343470588;
    if ((pt) < 500.0 && (eta) < -2.0) return 1.00727653503 + isyst * 0.00420281345299;
    if ((pt) < 500.0 && (eta) < -1.8) return 0.994818627834 + isyst * 0.00649266791838;
    if ((pt) < 500.0 && (eta) < -1.63) return 0.994786262512 + isyst * 0.00516608222797;
    if ((pt) < 500.0 && (eta) < -1.566) return 0.991631805897 + isyst * 0.00551198189805;
    if ((pt) < 500.0 && (eta) < -1.444) return 0.963128507137 + isyst * 0.026030162586;
    if ((pt) < 500.0 && (eta) < -1.2) return 0.989701330662 + isyst * 0.00359897172237;
    if ((pt) < 500.0 && (eta) < -1.0) return 0.985655725002 + isyst * 0.00506368027448;
    if ((pt) < 500.0 && (eta) < -0.6) return 0.981595098972 + isyst * 0.00331156908452;
    if ((pt) < 500.0 && (eta) < -0.4) return 0.984678268433 + isyst * 0.00612870275792;
    if ((pt) < 500.0 && (eta) < -0.2) return 0.981613874435 + isyst * 0.0063584778335;
    if ((pt) < 500.0 && (eta) < 0.0) return 0.980432569981 + isyst * 0.00530156031977;
    if ((pt) < 500.0 && (eta) < 0.2) return 0.984552025795 + isyst * 0.00530156031977;
    if ((pt) < 500.0 && (eta) < 0.4) return 0.988764047623 + isyst * 0.0063584778335;
    if ((pt) < 500.0 && (eta) < 0.6) return 0.987742602825 + isyst * 0.00612870275792;
    if ((pt) < 500.0 && (eta) < 1.0) return 0.987742602825 + isyst * 0.00331156908452;
    if ((pt) < 500.0 && (eta) < 1.2) return 0.987742602825 + isyst * 0.00506368027448;
    if ((pt) < 500.0 && (eta) < 1.444) return 0.98767966032 + isyst * 0.00359897172237;
    if ((pt) < 500.0 && (eta) < 1.566) return 0.967597782612 + isyst * 0.026030162586;
    if ((pt) < 500.0 && (eta) < 1.63) return 0.989626526833 + isyst * 0.00551198189805;
    if ((pt) < 500.0 && (eta) < 1.8) return 0.992761135101 + isyst * 0.00516608222797;
    if ((pt) < 500.0 && (eta) < 2.0) return 0.991761088371 + isyst * 0.00649266791838;
    if ((pt) < 500.0 && (eta) < 2.2) return 0.99794024229 + isyst * 0.00420281345299;
    if ((pt) < 500.0 && (eta) < 2.3) return 1.00103735924 + isyst * 0.00713343470588;
    if ((pt) < 500.0 && (eta) < 2.4) return 0.989506840706 + isyst * 0.00815834887034;
    if ((pt) < 500.0 && (eta) < 2.45) return 0.970518887043 + isyst * 0.0110667218714;
    if ((pt) < 500.0) return 0.906666696072 + isyst * 0.0182387273858;
    printf("WARNING in lepsf_elec_reco(): the given phase-space (%f, %f) did not fall under any range!\n", pt, eta); 
    return 1;
}

// Auto generated from https://github.com/sgnoohc/rooutil/blob/master/printsf.py
// Created on 2018-06-20 11:51:47
// Created by the command:
//   > ../rooutil/printsf.py /home/users/phchang/public_html/analysis/www/code/VVVBabyMaker/dilepbabymaker/lepsfrootfiles_20180506/egammaEffi.txt_EGM2D.MVA80.root EGamma_SF2D eta:pt lepsf_elec_mva80
float lepsf_elec_mva80(float pt_raw, float eta_raw, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    float eta = std::min((float) 2.4975, std::max((float) -2.002, eta_raw)); // minimum values are just below the first bin upper edge
    float pt = std::min((float) 499.5, std::max((float) 19.98, pt_raw)); // minimum values are just below the first bin upper edge
    if ((pt) < 20.0 && (eta) < -2.0) return 0.83592402935 + isyst * 0.0322480054373;
    if ((pt) < 35.0 && (eta) < -2.0) return 0.864357888699 + isyst * 0.00742276330779;
    if ((pt) < 50.0 && (eta) < -2.0) return 0.900265932083 + isyst * 0.00815622264742;
    if ((pt) < 90.0 && (eta) < -2.0) return 0.921694457531 + isyst * 0.00974887884185;
    if ((pt) < 150.0 && (eta) < -2.0) return 0.992509365082 + isyst * 0.0223208134252;
    if ((pt) < 500.0 && (eta) < -2.0) return 0.992509365082 + isyst * 0.0225042548118;
    if ((pt) < 20.0 && (eta) < -1.566) return 0.768633544445 + isyst * 0.0221271154581;
    if ((pt) < 35.0 && (eta) < -1.566) return 0.834688365459 + isyst * 0.010869186441;
    if ((pt) < 50.0 && (eta) < -1.566) return 0.874205827713 + isyst * 0.0062304163716;
    if ((pt) < 90.0 && (eta) < -1.566) return 0.902080774307 + isyst * 0.00839197118015;
    if ((pt) < 150.0 && (eta) < -1.566) return 0.941927969456 + isyst * 0.0153952833231;
    if ((pt) < 500.0 && (eta) < -1.566) return 0.941927969456 + isyst * 0.0156600613431;
    if ((pt) < 20.0 && (eta) < -1.444) return 0.786496341228 + isyst * 0.0336145624113;
    if ((pt) < 35.0 && (eta) < -1.444) return 0.857371807098 + isyst * 0.137903935151;
    if ((pt) < 50.0 && (eta) < -1.444) return 0.884180784225 + isyst * 0.00648350524423;
    if ((pt) < 90.0 && (eta) < -1.444) return 0.893296837807 + isyst * 0.0191012661408;
    if ((pt) < 150.0 && (eta) < -1.444) return 0.974358975887 + isyst * 0.0344476342993;
    if ((pt) < 500.0 && (eta) < -1.444) return 0.974358975887 + isyst * 0.0345667800278;
    if ((pt) < 20.0 && (eta) < -0.8) return 0.858884990215 + isyst * 0.0118506204617;
    if ((pt) < 35.0 && (eta) < -0.8) return 0.887640476227 + isyst * 0.0124493643614;
    if ((pt) < 50.0 && (eta) < -0.8) return 0.90706807375 + isyst * 0.00625596556149;
    if ((pt) < 90.0 && (eta) < -0.8) return 0.907692313194 + isyst * 0.0189000207177;
    if ((pt) < 150.0 && (eta) < -0.8) return 0.924223601818 + isyst * 0.021984147993;
    if ((pt) < 500.0 && (eta) < -0.8) return 0.924223601818 + isyst * 0.0221703751806;
    if ((pt) < 20.0 && (eta) < 0.0) return 0.85185188055 + isyst * 0.0252149795407;
    if ((pt) < 35.0 && (eta) < 0.0) return 0.889645755291 + isyst * 0.0097807576954;
    if ((pt) < 50.0 && (eta) < 0.0) return 0.907006382942 + isyst * 0.00562532539257;
    if ((pt) < 90.0 && (eta) < 0.0) return 0.908302366734 + isyst * 0.0158953531306;
    if ((pt) < 150.0 && (eta) < 0.0) return 0.933497548103 + isyst * 0.0198508210577;
    if ((pt) < 500.0 && (eta) < 0.0) return 0.933497548103 + isyst * 0.0200568658902;
    if ((pt) < 20.0 && (eta) < 0.8) return 0.880829036236 + isyst * 0.0252149795407;
    if ((pt) < 35.0 && (eta) < 0.8) return 0.934871077538 + isyst * 0.0097807576954;
    if ((pt) < 50.0 && (eta) < 0.8) return 0.942675173283 + isyst * 0.00562532539257;
    if ((pt) < 90.0 && (eta) < 0.8) return 0.943069279194 + isyst * 0.0158953531306;
    if ((pt) < 150.0 && (eta) < 0.8) return 0.964590966702 + isyst * 0.0198010487578;
    if ((pt) < 500.0 && (eta) < 0.8) return 0.964590966702 + isyst * 0.0200076061681;
    if ((pt) < 20.0 && (eta) < 1.444) return 0.889580070972 + isyst * 0.0118506204617;
    if ((pt) < 35.0 && (eta) < 1.444) return 0.894179880619 + isyst * 0.0124493643614;
    if ((pt) < 50.0 && (eta) < 1.444) return 0.915617108345 + isyst * 0.00625596556149;
    if ((pt) < 90.0 && (eta) < 1.444) return 0.916458845139 + isyst * 0.0189000207177;
    if ((pt) < 150.0 && (eta) < 1.444) return 0.952499985695 + isyst * 0.021984147993;
    if ((pt) < 500.0 && (eta) < 1.444) return 0.952499985695 + isyst * 0.0221703751806;
    if ((pt) < 20.0 && (eta) < 1.566) return 0.867562353611 + isyst * 0.0334678088307;
    if ((pt) < 35.0 && (eta) < 1.566) return 0.837579607964 + isyst * 0.137903935151;
    if ((pt) < 50.0 && (eta) < 1.566) return 0.876750707626 + isyst * 0.00648350524423;
    if ((pt) < 90.0 && (eta) < 1.566) return 0.884239912033 + isyst * 0.0191012661408;
    if ((pt) < 150.0 && (eta) < 1.566) return 0.88289475441 + isyst * 0.0340034647706;
    if ((pt) < 500.0 && (eta) < 1.566) return 0.88289475441 + isyst * 0.0341241613681;
    if ((pt) < 20.0 && (eta) < 2.0) return 0.836363613605 + isyst * 0.0220136501864;
    if ((pt) < 35.0 && (eta) < 2.0) return 0.854271352291 + isyst * 0.010869186441;
    if ((pt) < 50.0 && (eta) < 2.0) return 0.895683467388 + isyst * 0.0062304163716;
    if ((pt) < 90.0 && (eta) < 2.0) return 0.919716656208 + isyst * 0.00839197118015;
    if ((pt) < 150.0 && (eta) < 2.0) return 0.96046513319 + isyst * 0.0153952833231;
    if ((pt) < 500.0 && (eta) < 2.0) return 0.96046513319 + isyst * 0.0156600613431;
    if ((pt) < 20.0) return 0.848623871803 + isyst * 0.0322480054373;
    if ((pt) < 35.0) return 0.867469906807 + isyst * 0.00731642621726;
    if ((pt) < 50.0) return 0.900503754616 + isyst * 0.00815622264742;
    if ((pt) < 90.0) return 0.920731723309 + isyst * 0.00974887884185;
    if ((pt) < 150.0) return 0.996305406094 + isyst * 0.0221023477619;
    if ((pt) < 500.0) return 0.996305406094 + isyst * 0.022287587336;
    printf("WARNING in lepsf_elec_mva80(): the given phase-space (%f, %f) did not fall under any range!\n", pt, eta); 
    return 1;
}

// Auto generated from https://github.com/sgnoohc/rooutil/blob/master/printsf.py
// Created on 2018-06-20 11:51:49
// Created by the command:
//   > ../rooutil/printsf.py /home/users/phchang/public_html/analysis/www/code/VVVBabyMaker/dilepbabymaker/lepsfrootfiles_20180506/egammaEffi.txt_EGM2D.MVA90.root EGamma_SF2D eta:pt lepsf_elec_mva90
float lepsf_elec_mva90(float pt_raw, float eta_raw, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    float eta = std::min((float) 2.4975, std::max((float) -2.002, eta_raw)); // minimum values are just below the first bin upper edge
    float pt = std::min((float) 499.5, std::max((float) 19.98, pt_raw)); // minimum values are just below the first bin upper edge
    if ((pt) < 20.0 && (eta) < -2.0) return 0.918499350548 + isyst * 0.0165222368675;
    if ((pt) < 35.0 && (eta) < -2.0) return 0.931407928467 + isyst * 0.00639739722686;
    if ((pt) < 50.0 && (eta) < -2.0) return 0.955377578735 + isyst * 0.00612332609425;
    if ((pt) < 90.0 && (eta) < -2.0) return 0.966405391693 + isyst * 0.0079340520146;
    if ((pt) < 150.0 && (eta) < -2.0) return 1.02097129822 + isyst * 0.0228791620637;
    if ((pt) < 500.0 && (eta) < -2.0) return 1.02097129822 + isyst * 0.0228850330814;
    if ((pt) < 20.0 && (eta) < -1.566) return 0.877128958702 + isyst * 0.0107431896457;
    if ((pt) < 35.0 && (eta) < -1.566) return 0.902890145779 + isyst * 0.0162333572146;
    if ((pt) < 50.0 && (eta) < -1.566) return 0.93548387289 + isyst * 0.00403097598922;
    if ((pt) < 90.0 && (eta) < -1.566) return 0.952069699764 + isyst * 0.00332851728022;
    if ((pt) < 150.0 && (eta) < -1.566) return 0.982942402363 + isyst * 0.00989418895624;
    if ((pt) < 500.0 && (eta) < -1.566) return 0.982942402363 + isyst * 0.00990775744073;
    if ((pt) < 20.0 && (eta) < -1.444) return 0.900398433208 + isyst * 0.110051401206;
    if ((pt) < 35.0 && (eta) < -1.444) return 0.90537083149 + isyst * 0.0987445020928;
    if ((pt) < 50.0 && (eta) < -1.444) return 0.928909957409 + isyst * 0.00363039693932;
    if ((pt) < 90.0 && (eta) < -1.444) return 0.932870388031 + isyst * 0.0123626110707;
    if ((pt) < 150.0 && (eta) < -1.444) return 0.975056707859 + isyst * 0.023265136195;
    if ((pt) < 500.0 && (eta) < -1.444) return 0.975056707859 + isyst * 0.0232709098355;
    if ((pt) < 20.0 && (eta) < -0.8) return 0.908850729465 + isyst * 0.0143785576042;
    if ((pt) < 35.0 && (eta) < -0.8) return 0.929678201675 + isyst * 0.0114431032118;
    if ((pt) < 50.0 && (eta) < -0.8) return 0.944254815578 + isyst * 0.00413299731628;
    if ((pt) < 90.0 && (eta) < -0.8) return 0.945067286491 + isyst * 0.0125177761594;
    if ((pt) < 150.0 && (eta) < -0.8) return 0.96361631155 + isyst * 0.00591495052111;
    if ((pt) < 500.0 && (eta) < -0.8) return 0.96361631155 + isyst * 0.00593761922571;
    if ((pt) < 20.0 && (eta) < 0.0) return 0.912932157516 + isyst * 0.0179700342135;
    if ((pt) < 35.0 && (eta) < 0.0) return 0.93279260397 + isyst * 0.00955070037102;
    if ((pt) < 50.0 && (eta) < 0.0) return 0.947368443012 + isyst * 0.00395694897139;
    if ((pt) < 90.0 && (eta) < 0.0) return 0.950276255608 + isyst * 0.0128505009388;
    if ((pt) < 150.0 && (eta) < 0.0) return 0.963535904884 + isyst * 0.00971142684041;
    if ((pt) < 500.0 && (eta) < 0.0) return 0.963535904884 + isyst * 0.00972525031446;
    if ((pt) < 20.0 && (eta) < 0.8) return 0.932996213436 + isyst * 0.0179700342135;
    if ((pt) < 35.0 && (eta) < 0.8) return 0.958477497101 + isyst * 0.00955070037102;
    if ((pt) < 50.0 && (eta) < 0.8) return 0.965324401855 + isyst * 0.00395694897139;
    if ((pt) < 90.0 && (eta) < 0.8) return 0.967955827713 + isyst * 0.0128505009388;
    if ((pt) < 150.0 && (eta) < 0.8) return 0.987885475159 + isyst * 0.00971142684041;
    if ((pt) < 500.0 && (eta) < 0.8) return 0.987885475159 + isyst * 0.00972525031446;
    if ((pt) < 20.0 && (eta) < 1.444) return 0.925061404705 + isyst * 0.0142760416881;
    if ((pt) < 35.0 && (eta) < 1.444) return 0.940161108971 + isyst * 0.0114431032118;
    if ((pt) < 50.0 && (eta) < 1.444) return 0.952169060707 + isyst * 0.00413299731628;
    if ((pt) < 90.0 && (eta) < 1.444) return 0.952486217022 + isyst * 0.0125177761594;
    if ((pt) < 150.0 && (eta) < 1.444) return 0.97792494297 + isyst * 0.00591495052111;
    if ((pt) < 500.0 && (eta) < 1.444) return 0.97792494297 + isyst * 0.00593761922571;
    if ((pt) < 20.0 && (eta) < 1.566) return 0.885072648525 + isyst * 0.110051401206;
    if ((pt) < 35.0 && (eta) < 1.566) return 0.890428185463 + isyst * 0.0987445020928;
    if ((pt) < 50.0 && (eta) < 1.566) return 0.926229536533 + isyst * 0.00363039693932;
    if ((pt) < 90.0 && (eta) < 1.566) return 0.926744163036 + isyst * 0.012454124451;
    if ((pt) < 150.0 && (eta) < 1.566) return 0.939597308636 + isyst * 0.0230512269037;
    if ((pt) < 500.0 && (eta) < 1.566) return 0.939597308636 + isyst * 0.0230570541086;
    if ((pt) < 20.0 && (eta) < 2.0) return 0.926182210445 + isyst * 0.0106242501154;
    if ((pt) < 35.0 && (eta) < 2.0) return 0.918798685074 + isyst * 0.0162333572146;
    if ((pt) < 50.0 && (eta) < 2.0) return 0.948051929474 + isyst * 0.00403097598922;
    if ((pt) < 90.0 && (eta) < 2.0) return 0.959314763546 + isyst * 0.00332851728022;
    if ((pt) < 150.0 && (eta) < 2.0) return 0.984076440334 + isyst * 0.00989418895624;
    if ((pt) < 500.0 && (eta) < 2.0) return 0.984076440334 + isyst * 0.00990775744073;
    if ((pt) < 20.0) return 0.918092906475 + isyst * 0.0165222368675;
    if ((pt) < 35.0) return 0.923875451088 + isyst * 0.00639739722686;
    if ((pt) < 50.0) return 0.949999988079 + isyst * 0.00612332609425;
    if ((pt) < 90.0) return 0.959607005119 + isyst * 0.0079340520146;
    if ((pt) < 150.0) return 1.00664448738 + isyst * 0.0228791620637;
    if ((pt) < 500.0) return 1.00664448738 + isyst * 0.0228850330814;
    printf("WARNING in lepsf_elec_mva90(): the given phase-space (%f, %f) did not fall under any range!\n", pt, eta); 
    return 1;
}

// Auto generated from https://github.com/sgnoohc/rooutil/blob/master/printsf.py
// Created on 2018-06-20 11:51:51
// Created by the command:
//   > ../rooutil/printsf.py /home/users/phchang/public_html/analysis/www/code/VVVBabyMaker/dilepbabymaker/lepsfrootfiles_20180506/elec_sf_3l_iso.root sf_pt_vs_eta eta:pt lepsf_elec_3l_iso
float lepsf_elec_3l_iso(float pt_raw, float eta_raw, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    float eta = std::min((float) 2.4975, std::max((float) -2.002, eta_raw)); // minimum values are just below the first bin upper edge
    float pt = std::min((float) 149.85, std::max((float) 29.97, pt_raw)); // minimum values are just below the first bin upper edge
    if ((pt) < 30.0 && (eta) < -2.0) return 0.935190916061 + isyst * 0.0195467583835;
    if ((pt) < 40.0 && (eta) < -2.0) return 0.93671810627 + isyst * 0.00472788000479;
    if ((pt) < 50.0 && (eta) < -2.0) return 0.947656035423 + isyst * 0.00519610196352;
    if ((pt) < 150.0 && (eta) < -2.0) return 0.966931164265 + isyst * 0.00804648920894;
    if ((pt) < 30.0 && (eta) < -1.6) return 0.992152273655 + isyst * 0.014723110944;
    if ((pt) < 40.0 && (eta) < -1.6) return 0.996329843998 + isyst * 0.00551635632291;
    if ((pt) < 50.0 && (eta) < -1.6) return 0.990847408772 + isyst * 0.00332310609519;
    if ((pt) < 150.0 && (eta) < -1.6) return 1.0049649477 + isyst * 0.00561818853021;
    if ((pt) < 30.0 && (eta) < -1.4) return 0.0 + isyst * 0.0;
    if ((pt) < 40.0 && (eta) < -1.4) return 0.0 + isyst * 0.0;
    if ((pt) < 50.0 && (eta) < -1.4) return 0.0 + isyst * 0.0;
    if ((pt) < 150.0 && (eta) < -1.4) return 0.0 + isyst * 0.0;
    if ((pt) < 30.0 && (eta) < -1.0) return 0.997118651867 + isyst * 0.0143043091521;
    if ((pt) < 40.0 && (eta) < -1.0) return 1.00067949295 + isyst * 0.00437404680997;
    if ((pt) < 50.0 && (eta) < -1.0) return 0.999887704849 + isyst * 0.00231113168411;
    if ((pt) < 150.0 && (eta) < -1.0) return 0.997676253319 + isyst * 0.00379535206594;
    if ((pt) < 30.0 && (eta) < 0.0) return 0.991037845612 + isyst * 0.0195161364973;
    if ((pt) < 40.0 && (eta) < 0.0) return 0.98912101984 + isyst * 0.00317544280551;
    if ((pt) < 50.0 && (eta) < 0.0) return 0.990068554878 + isyst * 0.00121353229042;
    if ((pt) < 150.0 && (eta) < 0.0) return 0.996105372906 + isyst * 0.00267374445684;
    if ((pt) < 30.0 && (eta) < 1.0) return 0.994829773903 + isyst * 0.0213389266282;
    if ((pt) < 40.0 && (eta) < 1.0) return 0.989152491093 + isyst * 0.0039043452125;
    if ((pt) < 50.0 && (eta) < 1.0) return 0.993024647236 + isyst * 0.0014128361363;
    if ((pt) < 150.0 && (eta) < 1.0) return 0.995310664177 + isyst * 0.00227889884263;
    if ((pt) < 30.0 && (eta) < 1.4) return 1.01305508614 + isyst * 0.0195604078472;
    if ((pt) < 40.0 && (eta) < 1.4) return 0.99732875824 + isyst * 0.00382308196276;
    if ((pt) < 50.0 && (eta) < 1.4) return 0.997213184834 + isyst * 0.00220580212772;
    if ((pt) < 150.0 && (eta) < 1.4) return 0.993747234344 + isyst * 0.00367907946929;
    if ((pt) < 30.0 && (eta) < 1.6) return 0.0 + isyst * 1.40544736385;
    if ((pt) < 40.0 && (eta) < 1.6) return 0.0 + isyst * 1.41242206097;
    if ((pt) < 50.0 && (eta) < 1.6) return 0.0 + isyst * 1.41122281551;
    if ((pt) < 150.0 && (eta) < 1.6) return 0.0 + isyst * 1.43181884289;
    if ((pt) < 30.0 && (eta) < 2.0) return 0.994179010391 + isyst * 0.0102722523734;
    if ((pt) < 40.0 && (eta) < 2.0) return 0.97640478611 + isyst * 0.00671232398599;
    if ((pt) < 50.0 && (eta) < 2.0) return 0.983581423759 + isyst * 0.00317137362435;
    if ((pt) < 150.0 && (eta) < 2.0) return 0.990202724934 + isyst * 0.00854556448758;
    if ((pt) < 30.0) return 0.924050092697 + isyst * 0.00998185761273;
    if ((pt) < 40.0) return 0.93977022171 + isyst * 0.00463026156649;
    if ((pt) < 50.0) return 0.943002402782 + isyst * 0.0042942869477;
    if ((pt) < 150.0) return 0.962206125259 + isyst * 0.0109452595934;
    printf("WARNING in lepsf_elec_3l_iso(): the given phase-space (%f, %f) did not fall under any range!\n", pt, eta); 
    return 1;
}

// Auto generated from https://github.com/sgnoohc/rooutil/blob/master/printsf.py
// Created on 2018-06-20 11:51:52
// Created by the command:
//   > ../rooutil/printsf.py /home/users/phchang/public_html/analysis/www/code/VVVBabyMaker/dilepbabymaker/lepsfrootfiles_20180506/elec_sf_3l_noiso.root sf_pt_vs_eta eta:pt lepsf_elec_3l_id
float lepsf_elec_3l_id(float pt_raw, float eta_raw, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    float eta = std::min((float) 2.4975, std::max((float) -2.002, eta_raw)); // minimum values are just below the first bin upper edge
    float pt = std::min((float) 149.85, std::max((float) 29.97, pt_raw)); // minimum values are just below the first bin upper edge
    if ((pt) < 30.0 && (eta) < -2.0) return 0.850992679596 + isyst * 0.0136673385277;
    if ((pt) < 40.0 && (eta) < -2.0) return 0.870309829712 + isyst * 0.00867538619787;
    if ((pt) < 50.0 && (eta) < -2.0) return 0.885897278786 + isyst * 0.00825638417155;
    if ((pt) < 150.0 && (eta) < -2.0) return 0.886022746563 + isyst * 0.0154493553564;
    if ((pt) < 30.0 && (eta) < -1.6) return 0.844911515713 + isyst * 0.0121827758849;
    if ((pt) < 40.0 && (eta) < -1.6) return 0.863641440868 + isyst * 0.00668212166056;
    if ((pt) < 50.0 && (eta) < -1.6) return 0.882588028908 + isyst * 0.00628372561187;
    if ((pt) < 150.0 && (eta) < -1.6) return 0.90222120285 + isyst * 0.0103280115873;
    if ((pt) < 30.0 && (eta) < -1.4) return 0.0 + isyst * 0.0;
    if ((pt) < 40.0 && (eta) < -1.4) return 0.0 + isyst * 0.0;
    if ((pt) < 50.0 && (eta) < -1.4) return 0.0 + isyst * 0.0;
    if ((pt) < 150.0 && (eta) < -1.4) return 0.0 + isyst * 0.0;
    if ((pt) < 30.0 && (eta) < -1.0) return 0.952842175961 + isyst * 0.00859240069985;
    if ((pt) < 40.0 && (eta) < -1.0) return 0.94608014822 + isyst * 0.00498400675133;
    if ((pt) < 50.0 && (eta) < -1.0) return 0.949365019798 + isyst * 0.0041166478768;
    if ((pt) < 150.0 && (eta) < -1.0) return 0.949845910072 + isyst * 0.00687224790454;
    if ((pt) < 30.0 && (eta) < 0.0) return 0.967399954796 + isyst * 0.0065890494734;
    if ((pt) < 40.0 && (eta) < 0.0) return 0.970137059689 + isyst * 0.00460708839819;
    if ((pt) < 50.0 && (eta) < 0.0) return 0.973913311958 + isyst * 0.00176400714554;
    if ((pt) < 150.0 && (eta) < 0.0) return 0.968318223953 + isyst * 0.00237361504696;
    if ((pt) < 30.0 && (eta) < 1.0) return 0.979539036751 + isyst * 0.00783915538341;
    if ((pt) < 40.0 && (eta) < 1.0) return 0.979172468185 + isyst * 0.00417774915695;
    if ((pt) < 50.0 && (eta) < 1.0) return 0.979311406612 + isyst * 0.00151191279292;
    if ((pt) < 150.0 && (eta) < 1.0) return 0.97188526392 + isyst * 0.00289487629198;
    if ((pt) < 30.0 && (eta) < 1.4) return 0.939766466618 + isyst * 0.0129429949448;
    if ((pt) < 40.0 && (eta) < 1.4) return 0.934776186943 + isyst * 0.0072449343279;
    if ((pt) < 50.0 && (eta) < 1.4) return 0.938164770603 + isyst * 0.00355068268254;
    if ((pt) < 150.0 && (eta) < 1.4) return 0.938271284103 + isyst * 0.00774512067437;
    if ((pt) < 30.0 && (eta) < 1.6) return 0.0 + isyst * 1.28146290779;
    if ((pt) < 40.0 && (eta) < 1.6) return 0.0 + isyst * 1.33210575581;
    if ((pt) < 50.0 && (eta) < 1.6) return 0.0 + isyst * 1.30742883682;
    if ((pt) < 150.0 && (eta) < 1.6) return 0.0 + isyst * 1.30231380463;
    if ((pt) < 30.0 && (eta) < 2.0) return 0.866164386272 + isyst * 0.013075822033;
    if ((pt) < 40.0 && (eta) < 2.0) return 0.88133251667 + isyst * 0.00521183945239;
    if ((pt) < 50.0 && (eta) < 2.0) return 0.889661312103 + isyst * 0.00506126368418;
    if ((pt) < 150.0 && (eta) < 2.0) return 0.901180744171 + isyst * 0.0113095538691;
    if ((pt) < 30.0) return 0.871748626232 + isyst * 0.0300047937781;
    if ((pt) < 40.0) return 0.875420570374 + isyst * 0.00870532728732;
    if ((pt) < 50.0) return 0.86614793539 + isyst * 0.00887836329639;
    if ((pt) < 150.0) return 0.912270307541 + isyst * 0.0202183779329;
    printf("WARNING in lepsf_elec_3l_id(): the given phase-space (%f, %f) did not fall under any range!\n", pt, eta); 
    return 1;
}

// Auto generated from https://github.com/sgnoohc/rooutil/blob/master/printsf.py
// Created on 2018-06-20 11:51:54
// Created by the command:
//   > ../rooutil/printsf.py /home/users/phchang/public_html/analysis/www/code/VVVBabyMaker/dilepbabymaker/lepsfrootfiles_20180506/elec_sf_iso.root sf_pt_vs_eta eta:pt lepsf_elec_ss_iso
float lepsf_elec_ss_iso(float pt_raw, float eta_raw, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    float eta = std::min((float) 2.4975, std::max((float) -2.002, eta_raw)); // minimum values are just below the first bin upper edge
    float pt = std::min((float) 149.85, std::max((float) 29.97, pt_raw)); // minimum values are just below the first bin upper edge
    if ((pt) < 30.0 && (eta) < -2.0) return 0.908459424973 + isyst * 0.0203018579632;
    if ((pt) < 40.0 && (eta) < -2.0) return 0.919513642788 + isyst * 0.0074216062203;
    if ((pt) < 50.0 && (eta) < -2.0) return 0.918370842934 + isyst * 0.00827861391008;
    if ((pt) < 150.0 && (eta) < -2.0) return 0.941241204739 + isyst * 0.0152767291293;
    if ((pt) < 30.0 && (eta) < -1.6) return 0.981559216976 + isyst * 0.0190107543021;
    if ((pt) < 40.0 && (eta) < -1.6) return 1.00143146515 + isyst * 0.00766854686663;
    if ((pt) < 50.0 && (eta) < -1.6) return 0.984350144863 + isyst * 0.00566048687324;
    if ((pt) < 150.0 && (eta) < -1.6) return 0.998670339584 + isyst * 0.00893246848136;
    if ((pt) < 30.0 && (eta) < -1.4) return 0.0 + isyst * 0.0;
    if ((pt) < 40.0 && (eta) < -1.4) return 0.0 + isyst * 0.0;
    if ((pt) < 50.0 && (eta) < -1.4) return 0.0 + isyst * 0.0;
    if ((pt) < 150.0 && (eta) < -1.4) return 0.0 + isyst * 0.0;
    if ((pt) < 30.0 && (eta) < -1.0) return 1.00658631325 + isyst * 0.0213408730924;
    if ((pt) < 40.0 && (eta) < -1.0) return 0.997109651566 + isyst * 0.00634079333395;
    if ((pt) < 50.0 && (eta) < -1.0) return 0.998712599277 + isyst * 0.00387201085687;
    if ((pt) < 150.0 && (eta) < -1.0) return 0.992906808853 + isyst * 0.00566856795922;
    if ((pt) < 30.0 && (eta) < 0.0) return 0.984210371971 + isyst * 0.0183327179402;
    if ((pt) < 40.0 && (eta) < 0.0) return 0.983319997787 + isyst * 0.00545469345525;
    if ((pt) < 50.0 && (eta) < 0.0) return 0.983346402645 + isyst * 0.00169947580434;
    if ((pt) < 150.0 && (eta) < 0.0) return 0.989158213139 + isyst * 0.00274461344816;
    if ((pt) < 30.0 && (eta) < 1.0) return 0.989642679691 + isyst * 0.0230825021863;
    if ((pt) < 40.0 && (eta) < 1.0) return 0.980925619602 + isyst * 0.00474510621279;
    if ((pt) < 50.0 && (eta) < 1.0) return 0.987295031548 + isyst * 0.00195701303892;
    if ((pt) < 150.0 && (eta) < 1.0) return 0.983801782131 + isyst * 0.00247796950862;
    if ((pt) < 30.0 && (eta) < 1.4) return 1.00412034988 + isyst * 0.0195435658097;
    if ((pt) < 40.0 && (eta) < 1.4) return 0.994419872761 + isyst * 0.00474335439503;
    if ((pt) < 50.0 && (eta) < 1.4) return 0.998956561089 + isyst * 0.00344797736034;
    if ((pt) < 150.0 && (eta) < 1.4) return 0.989374756813 + isyst * 0.00618094438687;
    if ((pt) < 30.0 && (eta) < 1.6) return 0.0 + isyst * 1.42315506935;
    if ((pt) < 40.0 && (eta) < 1.6) return 0.0 + isyst * 1.41308510303;
    if ((pt) < 50.0 && (eta) < 1.6) return 0.0 + isyst * 1.39873981476;
    if ((pt) < 150.0 && (eta) < 1.6) return 0.0 + isyst * 1.42591965199;
    if ((pt) < 30.0 && (eta) < 2.0) return 1.00445044041 + isyst * 0.0173443686217;
    if ((pt) < 40.0 && (eta) < 2.0) return 0.983183503151 + isyst * 0.00769854290411;
    if ((pt) < 50.0 && (eta) < 2.0) return 0.980841457844 + isyst * 0.00524699361995;
    if ((pt) < 150.0 && (eta) < 2.0) return 0.976681888103 + isyst * 0.00868929177523;
    if ((pt) < 30.0) return 0.914859950542 + isyst * 0.0151402018964;
    if ((pt) < 40.0) return 0.922606050968 + isyst * 0.0136738996953;
    if ((pt) < 50.0) return 0.912222087383 + isyst * 0.00715025886893;
    if ((pt) < 150.0) return 0.931365907192 + isyst * 0.016236141324;
    printf("WARNING in lepsf_elec_ss_iso(): the given phase-space (%f, %f) did not fall under any range!\n", pt, eta); 
    return 1;
}

// Auto generated from https://github.com/sgnoohc/rooutil/blob/master/printsf.py
// Created on 2018-06-20 11:51:55
// Created by the command:
//   > ../rooutil/printsf.py /home/users/phchang/public_html/analysis/www/code/VVVBabyMaker/dilepbabymaker/lepsfrootfiles_20180506/elec_sf_noiso.root sf_pt_vs_eta eta:pt lepsf_elec_ss_id
float lepsf_elec_ss_id(float pt_raw, float eta_raw, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    float eta = std::min((float) 2.4975, std::max((float) -2.002, eta_raw)); // minimum values are just below the first bin upper edge
    float pt = std::min((float) 149.85, std::max((float) 29.97, pt_raw)); // minimum values are just below the first bin upper edge
    if ((pt) < 30.0 && (eta) < -2.0) return 0.883120417595 + isyst * 0.0410085655749;
    if ((pt) < 40.0 && (eta) < -2.0) return 0.853896558285 + isyst * 0.0103351194412;
    if ((pt) < 50.0 && (eta) < -2.0) return 0.856656908989 + isyst * 0.0113700097427;
    if ((pt) < 150.0 && (eta) < -2.0) return 0.825048804283 + isyst * 0.0183184538037;
    if ((pt) < 30.0 && (eta) < -1.6) return 0.865676999092 + isyst * 0.0345521941781;
    if ((pt) < 40.0 && (eta) < -1.6) return 0.860525727272 + isyst * 0.00779991224408;
    if ((pt) < 50.0 && (eta) < -1.6) return 0.876830995083 + isyst * 0.00693106791005;
    if ((pt) < 150.0 && (eta) < -1.6) return 0.879117190838 + isyst * 0.0126133970916;
    if ((pt) < 30.0 && (eta) < -1.4) return 0.0 + isyst * 0.0;
    if ((pt) < 40.0 && (eta) < -1.4) return 0.0 + isyst * 0.0;
    if ((pt) < 50.0 && (eta) < -1.4) return 0.0 + isyst * 0.0;
    if ((pt) < 150.0 && (eta) < -1.4) return 0.0 + isyst * 0.0;
    if ((pt) < 30.0 && (eta) < -1.0) return 0.97531837225 + isyst * 0.0142965959385;
    if ((pt) < 40.0 && (eta) < -1.0) return 0.963118612766 + isyst * 0.00627171760425;
    if ((pt) < 50.0 && (eta) < -1.0) return 0.960432350636 + isyst * 0.00440022535622;
    if ((pt) < 150.0 && (eta) < -1.0) return 0.959265232086 + isyst * 0.00955545529723;
    if ((pt) < 30.0 && (eta) < 0.0) return 0.972009539604 + isyst * 0.00476625701413;
    if ((pt) < 40.0 && (eta) < 0.0) return 0.973181843758 + isyst * 0.00174642540514;
    if ((pt) < 50.0 && (eta) < 0.0) return 0.975591123104 + isyst * 0.00152740336489;
    if ((pt) < 150.0 && (eta) < 0.0) return 0.970666646957 + isyst * 0.00300887506455;
    if ((pt) < 30.0 && (eta) < 1.0) return 0.975555300713 + isyst * 0.00561808887869;
    if ((pt) < 40.0 && (eta) < 1.0) return 0.975286841393 + isyst * 0.00203314679675;
    if ((pt) < 50.0 && (eta) < 1.0) return 0.973451316357 + isyst * 0.00148495228495;
    if ((pt) < 150.0 && (eta) < 1.0) return 0.973623454571 + isyst * 0.00247845542617;
    if ((pt) < 30.0 && (eta) < 1.4) return 0.934657216072 + isyst * 0.0143183209002;
    if ((pt) < 40.0 && (eta) < 1.4) return 0.953929543495 + isyst * 0.00982355233282;
    if ((pt) < 50.0 && (eta) < 1.4) return 0.945206224918 + isyst * 0.0040404223837;
    if ((pt) < 150.0 && (eta) < 1.4) return 0.952377796173 + isyst * 0.00700347404927;
    if ((pt) < 30.0 && (eta) < 1.6) return 0.0 + isyst * 1.3037301302;
    if ((pt) < 40.0 && (eta) < 1.6) return 0.0 + isyst * 1.31904411316;
    if ((pt) < 50.0 && (eta) < 1.6) return 0.0 + isyst * 1.29607057571;
    if ((pt) < 150.0 && (eta) < 1.6) return 0.0 + isyst * 1.29151642323;
    if ((pt) < 30.0 && (eta) < 2.0) return 0.871681392193 + isyst * 0.0152326272801;
    if ((pt) < 40.0 && (eta) < 2.0) return 0.876524329185 + isyst * 0.00619420781732;
    if ((pt) < 50.0 && (eta) < 2.0) return 0.884553015232 + isyst * 0.00710215047002;
    if ((pt) < 150.0 && (eta) < 2.0) return 0.885300338268 + isyst * 0.0111562777311;
    if ((pt) < 30.0) return 0.85907959938 + isyst * 0.0226758494973;
    if ((pt) < 40.0) return 0.862013459206 + isyst * 0.00867820624262;
    if ((pt) < 50.0) return 0.835528969765 + isyst * 0.00863196700811;
    if ((pt) < 150.0) return 0.880295813084 + isyst * 0.0221429113299;
    printf("WARNING in lepsf_elec_ss_id(): the given phase-space (%f, %f) did not fall under any range!\n", pt, eta); 
    return 1;
}

// Auto generated from https://github.com/sgnoohc/rooutil/blob/master/printsf.py
// Created on 2018-06-20 11:51:57
// Created by the command:
//   > ../rooutil/printsf.py /home/users/phchang/public_html/analysis/www/code/VVVBabyMaker/dilepbabymaker/lepsfrootfiles_20180506/muon_trk_sf.root muon_trk_sf |eta|:pt lepsf_muon_trk
float lepsf_muon_trk(float pt_raw, float eta_raw, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    float eta = std::min((float) 2.3976, std::max((float) 0.1998, eta_raw)); // minimum values are just below the first bin upper edge
    float pt = std::min((float) 0.999, std::max((float) 0.999, pt_raw)); // minimum values are just below the first bin upper edge
    if ((pt) < 1.0 && fabs(eta) < 0.2) return 0.99699652195 + isyst * 7.28286187344e-05;
    if ((pt) < 1.0 && fabs(eta) < 0.4) return 0.997711777687 + isyst * 8.21768174154e-05;
    if ((pt) < 1.0 && fabs(eta) < 0.6) return 0.998077630997 + isyst * 7.12808736244e-05;
    if ((pt) < 1.0 && fabs(eta) < 0.8) return 0.997803866863 + isyst * 7.44123331227e-05;
    if ((pt) < 1.0 && fabs(eta) < 1.0) return 0.997970819473 + isyst * 0.000106738508724;
    if ((pt) < 1.0 && fabs(eta) < 1.2) return 0.997147738934 + isyst * 0.00018588153158;
    if ((pt) < 1.0 && fabs(eta) < 1.4) return 0.996227443218 + isyst * 0.000181271097783;
    if ((pt) < 1.0 && fabs(eta) < 1.6) return 0.995478630066 + isyst * 0.000170522788649;
    if ((pt) < 1.0 && fabs(eta) < 1.8) return 0.995780825615 + isyst * 0.00017600027424;
    if ((pt) < 1.0 && fabs(eta) < 2.0) return 0.993891835213 + isyst * 0.000234893311697;
    if ((pt) < 1.0 && fabs(eta) < 2.2) return 0.992942690849 + isyst * 0.000328371243032;
    if ((pt) < 1.0) return 0.987313330173 + isyst * 0.000856037281724;
    printf("WARNING in lepsf_muon_trk(): the given phase-space (%f, %f) did not fall under any range!\n", pt, eta); 
    return 1;
}

// Auto generated from https://github.com/sgnoohc/rooutil/blob/master/printsf.py
// Created on 2018-06-20 11:51:59
// Created by the command:
//   > ../rooutil/printsf.py /home/users/phchang/public_html/analysis/www/code/VVVBabyMaker/dilepbabymaker/lepsfrootfiles_20180506/muon_id_sf.root muon_id_sf |eta|:pt lepsf_muon_id
float lepsf_muon_id(float pt_raw, float eta_raw, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    float eta = std::min((float) 2.3976, std::max((float) 0.8991, eta_raw)); // minimum values are just below the first bin upper edge
    float pt = std::min((float) 119.88, std::max((float) 24.975, pt_raw)); // minimum values are just below the first bin upper edge
    if ((pt) < 25.0 && fabs(eta) < 0.9) return 0.996060967445 + isyst * 0.00194326004897;
    if ((pt) < 30.0 && fabs(eta) < 0.9) return 0.99351811409 + isyst * 0.00910576488655;
    if ((pt) < 40.0 && fabs(eta) < 0.9) return 0.999299228191 + isyst * 0.000234670032364;
    if ((pt) < 50.0 && fabs(eta) < 0.9) return 0.996396005154 + isyst * 0.000150277542103;
    if ((pt) < 60.0 && fabs(eta) < 0.9) return 0.992024898529 + isyst * 0.000507900217761;
    if ((pt) < 120.0 && fabs(eta) < 0.9) return 1.00241065025 + isyst * 0.00125503478719;
    if ((pt) < 25.0 && fabs(eta) < 1.2) return 0.993112444878 + isyst * 0.00234635736833;
    if ((pt) < 30.0 && fabs(eta) < 1.2) return 0.990288972855 + isyst * 0.00493595336097;
    if ((pt) < 40.0 && fabs(eta) < 1.2) return 0.99301302433 + isyst * 0.00113384391833;
    if ((pt) < 50.0 && fabs(eta) < 1.2) return 0.994331181049 + isyst * 0.000245711458546;
    if ((pt) < 60.0 && fabs(eta) < 1.2) return 0.992053508759 + isyst * 0.000804403902698;
    if ((pt) < 120.0 && fabs(eta) < 1.2) return 0.994125008583 + isyst * 0.00188029615953;
    if ((pt) < 25.0 && fabs(eta) < 2.1) return 0.989002466202 + isyst * 0.00121397097676;
    if ((pt) < 30.0 && fabs(eta) < 2.1) return 0.988376021385 + isyst * 0.000574301420283;
    if ((pt) < 40.0 && fabs(eta) < 2.1) return 0.990510463715 + isyst * 0.0104544236993;
    if ((pt) < 50.0 && fabs(eta) < 2.1) return 0.99224793911 + isyst * 0.000166640979969;
    if ((pt) < 60.0 && fabs(eta) < 2.1) return 0.989107012749 + isyst * 0.00147855923965;
    if ((pt) < 120.0 && fabs(eta) < 2.1) return 0.992865204811 + isyst * 0.00381004950228;
    if ((pt) < 25.0) return 0.959993004799 + isyst * 0.00487111222708;
    if ((pt) < 30.0) return 0.957284927368 + isyst * 0.00110191449747;
    if ((pt) < 40.0) return 0.955422639847 + isyst * 0.0175965777942;
    if ((pt) < 50.0) return 0.957207322121 + isyst * 0.000599937925587;
    if ((pt) < 60.0) return 0.955536603928 + isyst * 0.00174255990589;
    if ((pt) < 120.0) return 0.958109974861 + isyst * 0.00379279559462;
    printf("WARNING in lepsf_muon_id(): the given phase-space (%f, %f) did not fall under any range!\n", pt, eta); 
    return 1;
}

// Auto generated from https://github.com/sgnoohc/rooutil/blob/master/printsf.py
// Created on 2018-06-20 11:52:01
// Created by the command:
//   > ../rooutil/printsf.py /home/users/phchang/public_html/analysis/www/code/VVVBabyMaker/dilepbabymaker/lepsfrootfiles_20180506/muon_sf.root sf_pt_vs_eta |eta|:pt lepsf_muon_ss
float lepsf_muon_ss(float pt_raw, float eta_raw, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    float eta = std::min((float) 2.3976, std::max((float) 0.8991, eta_raw)); // minimum values are just below the first bin upper edge
    float pt = std::min((float) 199.8, std::max((float) 24.975, pt_raw)); // minimum values are just below the first bin upper edge
    if ((pt) < 25.0 && fabs(eta) < 0.9) return 0.957033455372 + isyst * 0.0273258648813;
    if ((pt) < 30.0 && fabs(eta) < 0.9) return 0.969407081604 + isyst * 0.0117262657732;
    if ((pt) < 40.0 && fabs(eta) < 0.9) return 0.972197830677 + isyst * 0.00572965759784;
    if ((pt) < 50.0 && fabs(eta) < 0.9) return 0.974360883236 + isyst * 0.00567124830559;
    if ((pt) < 60.0 && fabs(eta) < 0.9) return 0.983807206154 + isyst * 0.00943034049124;
    if ((pt) < 200.0 && fabs(eta) < 0.9) return 0.98809581995 + isyst * 0.00743705453351;
    if ((pt) < 25.0 && fabs(eta) < 1.2) return 0.974665522575 + isyst * 0.0305873099715;
    if ((pt) < 30.0 && fabs(eta) < 1.2) return 0.993548929691 + isyst * 0.0148099223152;
    if ((pt) < 40.0 && fabs(eta) < 1.2) return 0.991381108761 + isyst * 0.0103353532031;
    if ((pt) < 50.0 && fabs(eta) < 1.2) return 0.986710488796 + isyst * 0.00587030919269;
    if ((pt) < 60.0 && fabs(eta) < 1.2) return 0.988096535206 + isyst * 0.0071763987653;
    if ((pt) < 200.0 && fabs(eta) < 1.2) return 0.995521485806 + isyst * 0.00889215618372;
    if ((pt) < 25.0 && fabs(eta) < 2.1) return 1.00234997272 + isyst * 0.0187554508448;
    if ((pt) < 30.0 && fabs(eta) < 2.1) return 0.9999319911 + isyst * 0.00884008780122;
    if ((pt) < 40.0 && fabs(eta) < 2.1) return 1.00043547153 + isyst * 0.0101939104497;
    if ((pt) < 50.0 && fabs(eta) < 2.1) return 0.994007408619 + isyst * 0.00574738392606;
    if ((pt) < 60.0 && fabs(eta) < 2.1) return 0.996202290058 + isyst * 0.00716154044494;
    if ((pt) < 200.0 && fabs(eta) < 2.1) return 1.00737679005 + isyst * 0.00699514942244;
    if ((pt) < 25.0) return 0.973362624645 + isyst * 0.0133408084512;
    if ((pt) < 30.0) return 0.973800718784 + isyst * 0.00934141408652;
    if ((pt) < 40.0) return 0.9801440835 + isyst * 0.0101231131703;
    if ((pt) < 50.0) return 0.98609817028 + isyst * 0.00847894139588;
    if ((pt) < 60.0) return 0.974988341331 + isyst * 0.00966404564679;
    if ((pt) < 200.0) return 0.992269873619 + isyst * 0.0127696096897;
    printf("WARNING in lepsf_muon_ss(): the given phase-space (%f, %f) did not fall under any range!\n", pt, eta); 
    return 1;
}

// Auto generated from https://github.com/sgnoohc/rooutil/blob/master/printsf.py
// Created on 2018-06-20 11:52:03
// Created by the command:
//   > ../rooutil/printsf.py /home/users/phchang/public_html/analysis/www/code/VVVBabyMaker/dilepbabymaker/lepsfrootfiles_20180506/muon_sf_3l.root sf_pt_vs_eta |eta|:pt lepsf_muon_3l
float lepsf_muon_3l(float pt_raw, float eta_raw, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    float eta = std::min((float) 2.3976, std::max((float) 0.8991, eta_raw)); // minimum values are just below the first bin upper edge
    float pt = std::min((float) 199.8, std::max((float) 24.975, pt_raw)); // minimum values are just below the first bin upper edge
    if ((pt) < 25.0 && fabs(eta) < 0.9) return 0.980066180229 + isyst * 0.0348992832005;
    if ((pt) < 30.0 && fabs(eta) < 0.9) return 0.983518302441 + isyst * 0.0121328588575;
    if ((pt) < 40.0 && fabs(eta) < 0.9) return 0.985425829887 + isyst * 0.0056755002588;
    if ((pt) < 50.0 && fabs(eta) < 0.9) return 0.989767849445 + isyst * 0.00558190839365;
    if ((pt) < 60.0 && fabs(eta) < 0.9) return 0.989802598953 + isyst * 0.00590769620612;
    if ((pt) < 200.0 && fabs(eta) < 0.9) return 0.994454026222 + isyst * 0.00607071490958;
    if ((pt) < 25.0 && fabs(eta) < 1.2) return 0.981684088707 + isyst * 0.0291706901044;
    if ((pt) < 30.0 && fabs(eta) < 1.2) return 0.989168167114 + isyst * 0.00941023789346;
    if ((pt) < 40.0 && fabs(eta) < 1.2) return 0.991053760052 + isyst * 0.00590242026374;
    if ((pt) < 50.0 && fabs(eta) < 1.2) return 0.994001507759 + isyst * 0.00555418105796;
    if ((pt) < 60.0 && fabs(eta) < 1.2) return 0.993303418159 + isyst * 0.007096957881;
    if ((pt) < 200.0 && fabs(eta) < 1.2) return 0.999513506889 + isyst * 0.00838844384998;
    if ((pt) < 25.0 && fabs(eta) < 2.1) return 1.01257061958 + isyst * 0.0270769204944;
    if ((pt) < 30.0 && fabs(eta) < 2.1) return 1.01111412048 + isyst * 0.0130612328649;
    if ((pt) < 40.0 && fabs(eta) < 2.1) return 0.999891281128 + isyst * 0.00550344213843;
    if ((pt) < 50.0 && fabs(eta) < 2.1) return 1.00323843956 + isyst * 0.00562182161957;
    if ((pt) < 60.0 && fabs(eta) < 2.1) return 1.00625753403 + isyst * 0.00769581506029;
    if ((pt) < 200.0 && fabs(eta) < 2.1) return 1.01454889774 + isyst * 0.00830468256027;
    if ((pt) < 25.0) return 0.992817699909 + isyst * 0.018002236262;
    if ((pt) < 30.0) return 0.987845003605 + isyst * 0.00904605630785;
    if ((pt) < 40.0) return 0.990353882313 + isyst * 0.00795413833112;
    if ((pt) < 50.0) return 0.993920981884 + isyst * 0.007227353286;
    if ((pt) < 60.0) return 0.986302554607 + isyst * 0.00683919154108;
    if ((pt) < 200.0) return 1.00726425648 + isyst * 0.0171289723366;
    printf("WARNING in lepsf_muon_3l(): the given phase-space (%f, %f) did not fall under any range!\n", pt, eta); 
    return 1;
}

