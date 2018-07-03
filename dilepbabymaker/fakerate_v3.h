// Auto generated from https://github.com/sgnoohc/rooutil/blob/master/printsf.py
// Created on 2018-06-09 13:17:44
// Created by the command:
//   > rooutil/printsf.py /home/users/phchang/public_html/analysis/www/code/VVVBabyMaker/Loopers/Analysis/FakeRate/data_fakerates.root fr_mu |eta|:ptcorr fakerate_mu_data_baseline_v3_ss
float fakerate_mu_data_baseline_v3_ss(float ptcorr_raw, float eta_raw, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    float eta = std::min((float) 2.3976, std::max((float) 1.5984, eta_raw)); // minimum values are just below the first bin upper edge
    float ptcorr = std::min((float) 119.88, std::max((float) 9.99, ptcorr_raw)); // minimum values are just below the first bin upper edge
    if ((ptcorr) < 10.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((ptcorr) < 20.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((ptcorr) < 25.0 && fabs(eta) < 1.6) return 0.204356357455 + isyst * 0.00586995720994;
    if ((ptcorr) < 30.0 && fabs(eta) < 1.6) return 0.0277132801712 + isyst * 0.00186925572179;
    if ((ptcorr) < 40.0 && fabs(eta) < 1.6) return 0.0161800887436 + isyst * 0.00270972512824;
    if ((ptcorr) < 120.0 && fabs(eta) < 1.6) return 0.0114979678765 + isyst * 0.00513308462426;
    if ((ptcorr) < 10.0) return 0.0 + isyst * 0.0;
    if ((ptcorr) < 20.0) return 0.0 + isyst * 0.0;
    if ((ptcorr) < 25.0) return 0.288886010647 + isyst * 0.0112512738883;
    if ((ptcorr) < 30.0) return 0.0452585816383 + isyst * 0.00411437188538;
    if ((ptcorr) < 40.0) return 0.0291154794395 + isyst * 0.00472066609013;
    if ((ptcorr) < 120.0) return 0.00676774047315 + isyst * 0.0167540756481;
    printf("WARNING in fakerate_mu_data_baseline_v3_ss(): the given phase-space (%f, %f) did not fall under any range!\n", ptcorr, eta); 
    return 1;
}

// Auto generated from https://github.com/sgnoohc/rooutil/blob/master/printsf.py
// Created on 2018-06-09 13:17:46
// Created by the command:
//   > rooutil/printsf.py /home/users/phchang/public_html/analysis/www/code/VVVBabyMaker/Loopers/Analysis/FakeRate/data_fakerates.root fr_el |eta|:ptcorr fakerate_el_data_baseline_v3_ss
float fakerate_el_data_baseline_v3_ss(float ptcorr_raw, float eta_raw, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    float eta = std::min((float) 2.3976, std::max((float) 1.5984, eta_raw)); // minimum values are just below the first bin upper edge
    float ptcorr = std::min((float) 119.88, std::max((float) 9.99, ptcorr_raw)); // minimum values are just below the first bin upper edge
    if ((ptcorr) < 10.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((ptcorr) < 20.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((ptcorr) < 25.0 && fabs(eta) < 1.6) return 0.309797137976 + isyst * 0.0268324851875;
    if ((ptcorr) < 30.0 && fabs(eta) < 1.6) return 0.0873859301209 + isyst * 0.0133586249979;
    if ((ptcorr) < 40.0 && fabs(eta) < 1.6) return 0.0814895927906 + isyst * 0.0195733113013;
    if ((ptcorr) < 120.0 && fabs(eta) < 1.6) return 0.127881407738 + isyst * 0.0367197345472;
    if ((ptcorr) < 10.0) return 0.0 + isyst * 0.0;
    if ((ptcorr) < 20.0) return 0.0 + isyst * 0.0;
    if ((ptcorr) < 25.0) return 0.528843224049 + isyst * 0.0704701613071;
    if ((ptcorr) < 30.0) return 0.20995990932 + isyst * 0.0342089448609;
    if ((ptcorr) < 40.0) return 0.17086724937 + isyst * 0.0378647226194;
    if ((ptcorr) < 120.0) return 0.15302914381 + isyst * 0.185998993334;
    printf("WARNING in fakerate_el_data_baseline_v3_ss(): the given phase-space (%f, %f) did not fall under any range!\n", ptcorr, eta); 
    return 1;
}

// Auto generated from https://github.com/sgnoohc/rooutil/blob/master/printsf.py
// Created on 2018-06-09 13:17:47
// Created by the command:
//   > rooutil/printsf.py /home/users/phchang/public_html/analysis/www/code/VVVBabyMaker/Loopers/Analysis/FakeRate/data_fakerates.root fr_mu3l |eta|:ptcorr fakerate_mu_data_baseline_v3_3l
float fakerate_mu_data_baseline_v3_3l(float ptcorr_raw, float eta_raw, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    float eta = std::min((float) 2.3976, std::max((float) 1.5984, eta_raw)); // minimum values are just below the first bin upper edge
    float ptcorr = std::min((float) 119.88, std::max((float) 9.99, ptcorr_raw)); // minimum values are just below the first bin upper edge
    if ((ptcorr) < 10.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((ptcorr) < 20.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((ptcorr) < 25.0 && fabs(eta) < 1.6) return 0.48353227973 + isyst * 0.011442785231;
    if ((ptcorr) < 30.0 && fabs(eta) < 1.6) return 0.0630224868655 + isyst * 0.00227679301314;
    if ((ptcorr) < 40.0 && fabs(eta) < 1.6) return 0.040212508291 + isyst * 0.0032852172247;
    if ((ptcorr) < 120.0 && fabs(eta) < 1.6) return 0.0288660917431 + isyst * 0.00549266204283;
    if ((ptcorr) < 10.0) return 0.0 + isyst * 0.0;
    if ((ptcorr) < 20.0) return 0.0 + isyst * 0.0;
    if ((ptcorr) < 25.0) return 0.705864429474 + isyst * 0.0294177682575;
    if ((ptcorr) < 30.0) return 0.101365849376 + isyst * 0.00562971648942;
    if ((ptcorr) < 40.0) return 0.0649619996548 + isyst * 0.00526385712672;
    if ((ptcorr) < 120.0) return 0.0398565120995 + isyst * 0.0176853537312;
    printf("WARNING in fakerate_mu_data_baseline_v3_3l(): the given phase-space (%f, %f) did not fall under any range!\n", ptcorr, eta); 
    return 1;
}

// Auto generated from https://github.com/sgnoohc/rooutil/blob/master/printsf.py
// Created on 2018-06-09 13:17:49
// Created by the command:
//   > rooutil/printsf.py /home/users/phchang/public_html/analysis/www/code/VVVBabyMaker/Loopers/Analysis/FakeRate/data_fakerates.root fr_el3l |eta|:ptcorr fakerate_el_data_baseline_v3_3l
float fakerate_el_data_baseline_v3_3l(float ptcorr_raw, float eta_raw, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    float eta = std::min((float) 2.3976, std::max((float) 1.5984, eta_raw)); // minimum values are just below the first bin upper edge
    float ptcorr = std::min((float) 119.88, std::max((float) 9.99, ptcorr_raw)); // minimum values are just below the first bin upper edge
    if ((ptcorr) < 10.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((ptcorr) < 20.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((ptcorr) < 25.0 && fabs(eta) < 1.6) return 0.421735733747 + isyst * 0.0299751021681;
    if ((ptcorr) < 30.0 && fabs(eta) < 1.6) return 0.126379713416 + isyst * 0.0121868417559;
    if ((ptcorr) < 40.0 && fabs(eta) < 1.6) return 0.119257897139 + isyst * 0.0173315435036;
    if ((ptcorr) < 120.0 && fabs(eta) < 1.6) return 0.180079296231 + isyst * 0.0304947451864;
    if ((ptcorr) < 10.0) return 0.0 + isyst * 0.0;
    if ((ptcorr) < 20.0) return 0.0 + isyst * 0.0;
    if ((ptcorr) < 25.0) return 0.749650001526 + isyst * 0.0747893754887;
    if ((ptcorr) < 30.0) return 0.335791289806 + isyst * 0.0372068455554;
    if ((ptcorr) < 40.0) return 0.28735268116 + isyst * 0.0305755165904;
    if ((ptcorr) < 120.0) return 0.53127849102 + isyst * 0.141100381585;
    printf("WARNING in fakerate_el_data_baseline_v3_3l(): the given phase-space (%f, %f) did not fall under any range!\n", ptcorr, eta); 
    return 1;
}

// Auto generated from https://github.com/sgnoohc/rooutil/blob/master/printsf.py
// Created on 2018-06-09 13:17:50
// Created by the command:
//   > rooutil/printsf.py /home/users/phchang/public_html/analysis/www/code/VVVBabyMaker/Loopers/Analysis/FakeRate/qcd_fakerates.root qcdmu |eta|:ptcorr fakerate_mu_qcd_baseline_v3_ss
float fakerate_mu_qcd_baseline_v3_ss(float ptcorr_raw, float eta_raw, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    float eta = std::min((float) 2.3976, std::max((float) 1.5984, eta_raw)); // minimum values are just below the first bin upper edge
    float ptcorr = std::min((float) 119.88, std::max((float) 9.99, ptcorr_raw)); // minimum values are just below the first bin upper edge
    if ((ptcorr) < 10.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((ptcorr) < 20.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((ptcorr) < 25.0 && fabs(eta) < 1.6) return 0.194474771619 + isyst * 0.0190081212329;
    if ((ptcorr) < 30.0 && fabs(eta) < 1.6) return 0.0339916609228 + isyst * 0.00440772582831;
    if ((ptcorr) < 40.0 && fabs(eta) < 1.6) return 0.0189852416515 + isyst * 0.00297458573756;
    if ((ptcorr) < 120.0 && fabs(eta) < 1.6) return 0.00933861359954 + isyst * 0.00204356043238;
    if ((ptcorr) < 10.0) return 0.0 + isyst * 0.0;
    if ((ptcorr) < 20.0) return 0.0 + isyst * 0.0;
    if ((ptcorr) < 25.0) return 0.296469211578 + isyst * 0.0343076085477;
    if ((ptcorr) < 30.0) return 0.0514997243881 + isyst * 0.00840915172667;
    if ((ptcorr) < 40.0) return 0.0308733098209 + isyst * 0.00564363826688;
    if ((ptcorr) < 120.0) return 0.0164834763855 + isyst * 0.00390325337509;
    printf("WARNING in fakerate_mu_qcd_baseline_v3_ss(): the given phase-space (%f, %f) did not fall under any range!\n", ptcorr, eta); 
    return 1;
}

// Auto generated from https://github.com/sgnoohc/rooutil/blob/master/printsf.py
// Created on 2018-06-09 13:17:52
// Created by the command:
//   > rooutil/printsf.py /home/users/phchang/public_html/analysis/www/code/VVVBabyMaker/Loopers/Analysis/FakeRate/qcd_fakerates.root qcdel |eta|:ptcorr fakerate_el_qcd_baseline_v3_ss
float fakerate_el_qcd_baseline_v3_ss(float ptcorr_raw, float eta_raw, int isyst=0)
{
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf("%s",Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    float eta = std::min((float) 2.3976, std::max((float) 1.5984, eta_raw)); // minimum values are just below the first bin upper edge
    float ptcorr = std::min((float) 119.88, std::max((float) 9.99, ptcorr_raw)); // minimum values are just below the first bin upper edge
    if ((ptcorr) < 10.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((ptcorr) < 20.0 && fabs(eta) < 1.6) return 0.0 + isyst * 0.0;
    if ((ptcorr) < 25.0 && fabs(eta) < 1.6) return 0.478862434626 + isyst * 0.33010264909;
    if ((ptcorr) < 30.0 && fabs(eta) < 1.6) return 0.167991176248 + isyst * 0.118381736351;
    if ((ptcorr) < 40.0 && fabs(eta) < 1.6) return 0.080632135272 + isyst * 0.0235373177756;
    if ((ptcorr) < 120.0 && fabs(eta) < 1.6) return 0.0480629131198 + isyst * 0.0196991094085;
    if ((ptcorr) < 10.0) return 0.0 + isyst * 0.0;
    if ((ptcorr) < 20.0) return 0.0 + isyst * 0.0;
    if ((ptcorr) < 25.0) return 0.45722129941 + isyst * 0.202222506469;
    if ((ptcorr) < 30.0) return 0.389234244823 + isyst * 0.204998753117;
    if ((ptcorr) < 40.0) return 0.219195067883 + isyst * 0.118145032006;
    if ((ptcorr) < 120.0) return 0.53896009922 + isyst * 0.22273289;
    printf("WARNING in fakerate_el_qcd_baseline_v3_ss(): the given phase-space (%f, %f) did not fall under any range!\n", ptcorr, eta); 
    return 1;
}


//______________________________________________________________________________________
float fakerate_baseline_v3_ss_mu_data(float conecorrPt, float Eta)
{
    return fakerate_mu_data_baseline_v3_ss(conecorrPt, Eta);
}
float fakerate_baseline_v3_ss_mu_data_unc(float conecorrPt, float Eta)
{
    return fakerate_mu_data_baseline_v3_ss(conecorrPt, Eta, 1) - fakerate_mu_data_baseline_v3_ss(conecorrPt, Eta);
}
//______________________________________________________________________________________
float fakerate_baseline_v3_ss_mu_qcd(float conecorrPt, float Eta)
{
    return fakerate_mu_qcd_baseline_v3_ss(conecorrPt, Eta);
}
float fakerate_baseline_v3_ss_mu_qcd_unc(float conecorrPt, float Eta)
{
    return fakerate_mu_qcd_baseline_v3_ss(conecorrPt, Eta, 1) - fakerate_mu_qcd_baseline_v3_ss(conecorrPt, Eta);
}

//______________________________________________________________________________________
float fakerate_baseline_v3_ss_el_data(float conecorrPt, float Eta)
{
    return fakerate_el_data_baseline_v3_ss(conecorrPt, Eta);
}
float fakerate_baseline_v3_ss_el_data_unc(float conecorrPt, float Eta)
{
    return fakerate_el_data_baseline_v3_ss(conecorrPt, Eta, 1) - fakerate_el_data_baseline_v3_ss(conecorrPt, Eta);
}
//______________________________________________________________________________________
float fakerate_baseline_v3_ss_el_qcd(float conecorrPt, float Eta)
{
    return fakerate_el_qcd_baseline_v3_ss(conecorrPt, Eta);
}
float fakerate_baseline_v3_ss_el_qcd_unc(float conecorrPt, float Eta)
{
    return fakerate_el_qcd_baseline_v3_ss(conecorrPt, Eta, 1) - fakerate_el_qcd_baseline_v3_ss(conecorrPt, Eta);
}

//______________________________________________________________________________________
float fakerate_baseline_v3_3l_mu_data(float conecorrPt, float Eta)
{
    return fakerate_mu_data_baseline_v3_3l(conecorrPt, Eta);
}
float fakerate_baseline_v3_3l_mu_data_unc(float conecorrPt, float Eta)
{
    return fakerate_mu_data_baseline_v3_3l(conecorrPt, Eta, 1) - fakerate_mu_data_baseline_v3_3l(conecorrPt, Eta);
}
//______________________________________________________________________________________
// We will not test closure in 3lepton
float fakerate_baseline_v3_3l_mu_qcd(float conecorrPt, float Eta)
{
    return 0;
}
float fakerate_baseline_v3_3l_mu_qcd_unc(float conecorrPt, float Eta)
{
    return 0;
}

//______________________________________________________________________________________
float fakerate_baseline_v3_3l_el_data(float conecorrPt, float Eta)
{
    return fakerate_el_data_baseline_v3_3l(conecorrPt, Eta);
}
float fakerate_baseline_v3_3l_el_data_unc(float conecorrPt, float Eta)
{
    return fakerate_el_data_baseline_v3_3l(conecorrPt, Eta, 1) - fakerate_el_data_baseline_v3_3l(conecorrPt, Eta);
}
//______________________________________________________________________________________
// We will not test closure in 3lepton
float fakerate_baseline_v3_3l_el_qcd(float conecorrPt, float Eta)
{
    return 0;
}
float fakerate_baseline_v3_3l_el_qcd_unc(float conecorrPt, float Eta)
{
    return 0;
}

//______________________________________________________________________________________
float fakerate_mu_data(float conecorrPt, float Eta, int version=0)
{
    if (version == -2)
    {
        return fakerate_baseline_v3_3l_mu_data(conecorrPt, Eta);
    }
    if (version == 2)
    {
        return fakerate_baseline_v3_ss_mu_data(conecorrPt, Eta);
    }
    return 0;
}
float fakerate_mu_data_unc(float conecorrPt, float Eta, int version=0)
{
    if (version == -2)
    {
        return fakerate_baseline_v3_3l_mu_data_unc(conecorrPt, Eta);
    }
    if (version == 2)
    {
        return fakerate_baseline_v3_ss_mu_data_unc(conecorrPt, Eta);
    }
    return 0;
}
//______________________________________________________________________________________
float fakerate_mu_qcd(float conecorrPt, float Eta, int version=0)
{
    if (version == -2)
    {
        return fakerate_baseline_v3_3l_mu_qcd(conecorrPt, Eta);
    }
    if (version == 2)
    {
        return fakerate_baseline_v3_ss_mu_qcd(conecorrPt, Eta);
    }
    return 0;
}
float fakerate_mu_qcd_unc(float conecorrPt, float Eta, int version=0)
{
    if (version == -2)
    {
        return fakerate_baseline_v3_3l_mu_qcd_unc(conecorrPt, Eta);
    }
    if (version == 2)
    {
        return fakerate_baseline_v3_ss_mu_qcd_unc(conecorrPt, Eta);
    }
    return 0;
}

//______________________________________________________________________________________
float fakerate_el_data(float conecorrPt, float Eta, int version=0)
{
    if (version == -2)
    {
        return fakerate_baseline_v3_3l_el_data(conecorrPt, Eta);
    }
    if (version == 2)
    {
        return fakerate_baseline_v3_ss_el_data(conecorrPt, Eta);
    }
    return 0;
}
float fakerate_el_data_unc(float conecorrPt, float Eta, int version=0)
{
    if (version == -2)
    {
        return fakerate_baseline_v3_3l_el_data_unc(conecorrPt, Eta);
    }
    if (version == 2)
    {
        return fakerate_baseline_v3_ss_el_data_unc(conecorrPt, Eta);
    }
    return 0;
}
//______________________________________________________________________________________
float fakerate_el_qcd(float conecorrPt, float Eta, int version=0)
{
    if (version == -2)
    {
        return fakerate_baseline_v3_3l_el_qcd(conecorrPt, Eta);
    }
    if (version == 2)
    {
        return fakerate_baseline_v3_ss_el_qcd(conecorrPt, Eta);
    }
    return 0;
}
float fakerate_el_qcd_unc(float conecorrPt, float Eta, int version=0)
{
    if (version == -2)
    {
        return fakerate_baseline_v3_3l_el_qcd_unc(conecorrPt, Eta);
    }
    if (version == 2)
    {
        return fakerate_baseline_v3_ss_el_qcd_unc(conecorrPt, Eta);
    }
    return 0;
}

