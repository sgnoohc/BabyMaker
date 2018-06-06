// Auto generated from https://github.com/sgnoohc/rooutil/blob/master/printsf.py
// Created on 2018-06-02 09:36:07
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
    if ((ptcorr) < 25.0 && fabs(eta) < 1.6) return 0.204356357455 + isyst * 0.00598511844991;
    if ((ptcorr) < 30.0 && fabs(eta) < 1.6) return 0.0277132801712 + isyst * 0.00245056125839;
    if ((ptcorr) < 40.0 && fabs(eta) < 1.6) return 0.0161800887436 + isyst * 0.0041514934072;
    if ((ptcorr) < 120.0 && fabs(eta) < 1.6) return 0.0114979678765 + isyst * 0.00589098822564;
    if ((ptcorr) < 10.0) return 0.0 + isyst * 0.0;
    if ((ptcorr) < 20.0) return 0.0 + isyst * 0.0;
    if ((ptcorr) < 25.0) return 0.288886010647 + isyst * 0.0127739745915;
    if ((ptcorr) < 30.0) return 0.0452585816383 + isyst * 0.00581986225682;
    if ((ptcorr) < 40.0) return 0.0291154794395 + isyst * 0.00698790164221;
    if ((ptcorr) < 120.0) return 0.00676774047315 + isyst * 0.0257779370444;
    printf("WARNING in fakerate_mu_data_baseline_v3_ss(): the given phase-space (%f, %f) did not fall under any range!\n", ptcorr, eta); 
    return 1;
}

// Auto generated from https://github.com/sgnoohc/rooutil/blob/master/printsf.py
// Created on 2018-06-02 09:36:09
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
    if ((ptcorr) < 25.0 && fabs(eta) < 1.6) return 0.309797137976 + isyst * 0.0280807677176;
    if ((ptcorr) < 30.0 && fabs(eta) < 1.6) return 0.0873859301209 + isyst * 0.0157521567581;
    if ((ptcorr) < 40.0 && fabs(eta) < 1.6) return 0.0814895927906 + isyst * 0.0252702661406;
    if ((ptcorr) < 120.0 && fabs(eta) < 1.6) return 0.127881407738 + isyst * 0.0391656773484;
    if ((ptcorr) < 10.0) return 0.0 + isyst * 0.0;
    if ((ptcorr) < 20.0) return 0.0 + isyst * 0.0;
    if ((ptcorr) < 25.0) return 0.528843224049 + isyst * 0.0758083015827;
    if ((ptcorr) < 30.0) return 0.20995990932 + isyst * 0.0405970249391;
    if ((ptcorr) < 40.0) return 0.17086724937 + isyst * 0.0417964601655;
    if ((ptcorr) < 120.0) return 0.15302914381 + isyst * 0.290736751511;
    printf("WARNING in fakerate_el_data_baseline_v3_ss(): the given phase-space (%f, %f) did not fall under any range!\n", ptcorr, eta); 
    return 1;
}

// Auto generated from https://github.com/sgnoohc/rooutil/blob/master/printsf.py
// Created on 2018-06-02 09:36:10
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
    if ((ptcorr) < 25.0 && fabs(eta) < 1.6) return 0.483771771193 + isyst * 0.0126579405548;
    if ((ptcorr) < 30.0 && fabs(eta) < 1.6) return 0.0631043240428 + isyst * 0.00264010230266;
    if ((ptcorr) < 40.0 && fabs(eta) < 1.6) return 0.040351845324 + isyst * 0.00484221683912;
    if ((ptcorr) < 120.0 && fabs(eta) < 1.6) return 0.0295603014529 + isyst * 0.00583511009667;
    if ((ptcorr) < 10.0) return 0.0 + isyst * 0.0;
    if ((ptcorr) < 20.0) return 0.0 + isyst * 0.0;
    if ((ptcorr) < 25.0) return 0.706121087074 + isyst * 0.0398454302207;
    if ((ptcorr) < 30.0) return 0.101466365159 + isyst * 0.00777116693401;
    if ((ptcorr) < 40.0) return 0.0651293098927 + isyst * 0.00719395246745;
    if ((ptcorr) < 120.0) return 0.040776450187 + isyst * 0.0258804411309;
    printf("WARNING in fakerate_mu_data_baseline_v3_3l(): the given phase-space (%f, %f) did not fall under any range!\n", ptcorr, eta); 
    return 1;
}

// Auto generated from https://github.com/sgnoohc/rooutil/blob/master/printsf.py
// Created on 2018-06-02 09:36:12
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
    if ((ptcorr) < 25.0 && fabs(eta) < 1.6) return 0.429381877184 + isyst * 0.0345341449854;
    if ((ptcorr) < 30.0 && fabs(eta) < 1.6) return 0.131725862622 + isyst * 0.014200944522;
    if ((ptcorr) < 40.0 && fabs(eta) < 1.6) return 0.133456870914 + isyst * 0.0223997182554;
    if ((ptcorr) < 120.0 && fabs(eta) < 1.6) return 0.226245865226 + isyst * 0.0312229753175;
    if ((ptcorr) < 10.0) return 0.0 + isyst * 0.0;
    if ((ptcorr) < 20.0) return 0.0 + isyst * 0.0;
    if ((ptcorr) < 25.0) return 0.756604075432 + isyst * 0.0845161460393;
    if ((ptcorr) < 30.0) return 0.340676218271 + isyst * 0.04895841245;
    if ((ptcorr) < 40.0) return 0.30008906126 + isyst * 0.0308111959714;
    if ((ptcorr) < 120.0) return 0.597102105618 + isyst * 0.208363805778;
    printf("WARNING in fakerate_el_data_baseline_v3_3l(): the given phase-space (%f, %f) did not fall under any range!\n", ptcorr, eta); 
    return 1;
}

// Auto generated from https://github.com/sgnoohc/rooutil/blob/master/printsf.py
// Created on 2018-06-02 09:36:13
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
// Created on 2018-06-02 09:36:15
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

