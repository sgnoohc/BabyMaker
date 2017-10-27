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
float lepsf_EGammaTightPOG_EGammaVVV(float PT, float Eta)
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

//______________________________________________________________________________________
float lepsf_EGammaVVV_EGammaVVVEle12(float PT, float Eta, int isyst=0)
{
    float pt  = std::min((float)1999.,PT);
    float eta = std::min((float)2.49,std::max((float)-2.49,Eta));
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if ((pt) < 30.0   && fabs(eta) < 1.0   ) return 0.938784837723 + isyst * 0.00219590521361;
    if ((pt) < 40.0   && fabs(eta) < 1.0   ) return 0.956399559975 + isyst * 0.00127861103515;
    if ((pt) < 50.0   && fabs(eta) < 1.0   ) return 0.962966561317 + isyst * 0.000316125299188;
    if ((pt) < 2000.0 && fabs(eta) < 1.0   ) return 0.967466413975 + isyst * 0.00155382971572;
    if ((pt) < 30.0   && fabs(eta) < 1.4442) return 0.94966250658  + isyst * 0.00368355725231;
    if ((pt) < 40.0   && fabs(eta) < 1.4442) return 0.96033769846  + isyst * 0.00197332068038;
    if ((pt) < 50.0   && fabs(eta) < 1.4442) return 0.965217530727 + isyst * 0.000220183866521;
    if ((pt) < 2000.0 && fabs(eta) < 1.4442) return 0.969266951084 + isyst * 0.00265256114334;
    if ((pt) < 30.0   && fabs(eta) < 1.56  ) return 0.957857549191 + isyst * 0.0115744391104;
    if ((pt) < 40.0   && fabs(eta) < 1.56  ) return 0.962614357471 + isyst * 0.0059518655469;
    if ((pt) < 50.0   && fabs(eta) < 1.56  ) return 0.964548945427 + isyst * 0.0055577892749;
    if ((pt) < 2000.0 && fabs(eta) < 1.56  ) return 0.962951600552 + isyst * 0.00883849432663;
    if ((pt) < 30.0   && fabs(eta) < 2.0   ) return 0.958219587803 + isyst * 0.00428889366748;
    if ((pt) < 40.0   && fabs(eta) < 2.0   ) return 0.96611481905  + isyst * 0.00169359181774;
    if ((pt) < 50.0   && fabs(eta) < 2.0   ) return 0.971387922764 + isyst * 0.00208029227053;
    if ((pt) < 2000.0 && fabs(eta) < 2.0   ) return 0.974559724331 + isyst * 1.84578668625e-05;
    if ((pt) < 30.0   && fabs(eta) < 2.5   ) return 0.910284698009 + isyst * 0.00477846357209;
    if ((pt) < 40.0   && fabs(eta) < 2.5   ) return 0.947666943073 + isyst * 0.00277335535449;
    if ((pt) < 50.0   && fabs(eta) < 2.5   ) return 0.955771327019 + isyst * 0.00289434846743;
    if ((pt) < 2000.0 && fabs(eta) < 2.5   ) return 0.962957322598 + isyst * 0.00532928187002;
    return 1;
}

//______________________________________________________________________________________
float lepsf_EGammaVVV_EGammaVVVEleLead(float PT, float Eta, int isyst=0)
{
    float pt  = std::min((float)1999.,PT);
    float eta = std::min((float)2.49,std::max((float)-2.49,Eta));
    if (isyst != 1 && isyst != -1 && isyst != 0)
      printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if ((pt) < 30.0   && fabs(eta) < 1.0   ) return 0.902300655842 + isyst * 0.00213228896962;
    if ((pt) < 40.0   && fabs(eta) < 1.0   ) return 0.956393837929 + isyst * 0.00130303273575;
    if ((pt) < 50.0   && fabs(eta) < 1.0   ) return 0.962963223457 + isyst * 0.000868854723185;
    if ((pt) < 2000.0 && fabs(eta) < 1.0   ) return 0.967466413975 + isyst * 0.00155382971572;
    if ((pt) < 30.0   && fabs(eta) < 1.4442) return 0.903473079205 + isyst * 0.0035448160487;
    if ((pt) < 40.0   && fabs(eta) < 1.4442) return 0.960295259953 + isyst * 0.00197019492648;
    if ((pt) < 50.0   && fabs(eta) < 1.4442) return 0.965217530727 + isyst * 0.000220183866521;
    if ((pt) < 2000.0 && fabs(eta) < 1.4442) return 0.969266951084 + isyst * 0.00265256114334;
    if ((pt) < 30.0   && fabs(eta) < 1.56  ) return 0.914313673973 + isyst * 0.0113559311569;
    if ((pt) < 40.0   && fabs(eta) < 1.56  ) return 0.962467074394 + isyst * 0.00602194977727;
    if ((pt) < 50.0   && fabs(eta) < 1.56  ) return 0.964522898197 + isyst * 0.00558842549423;
    if ((pt) < 2000.0 && fabs(eta) < 1.56  ) return 0.962951600552 + isyst * 0.00883849432663;
    if ((pt) < 30.0   && fabs(eta) < 2.0   ) return 0.920680880547 + isyst * 0.00415683064104;
    if ((pt) < 40.0   && fabs(eta) < 2.0   ) return 0.966320037842 + isyst * 0.00231408855426;
    if ((pt) < 50.0   && fabs(eta) < 2.0   ) return 0.971381902695 + isyst * 0.00210118701395;
    if ((pt) < 2000.0 && fabs(eta) < 2.0   ) return 0.970944464207 + isyst * 1.80491030395e-05;
    if ((pt) < 30.0   && fabs(eta) < 2.5   ) return 0.867845416069 + isyst * 0.00461339431639;
    if ((pt) < 40.0   && fabs(eta) < 2.5   ) return 0.947629570961 + isyst * 0.00278310457802;
    if ((pt) < 50.0   && fabs(eta) < 2.5   ) return 0.955740690231 + isyst * 0.00208964389036;
    if ((pt) < 2000.0 && fabs(eta) < 2.5   ) return 0.962957322598 + isyst * 0.00532928187002;
    return 1;
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
float lepsf_MuMediumPOG_MuTightVVV(float PT, float Eta)
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

//______________________________________________________________________________________
float lepsf_MuTightVVV_MuTightVVVMu17(float PT, float Eta, int isyst=0)
{
    float pt  = std::min((float)1199.,PT);
    float eta = std::min((float)2.39,std::max((float)-2.39,Eta));
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if ((pt) < 25.0   && fabs(eta) < 0.9) return 0.922722399235 + isyst * 0.00250782468408;
    if ((pt) < 30.0   && fabs(eta) < 0.9) return 0.923307836056 + isyst * 0.000366351007182;
    if ((pt) < 40.0   && fabs(eta) < 0.9) return 0.924030900002 + isyst * 0.000730909831923;
    if ((pt) < 50.0   && fabs(eta) < 0.9) return 0.923241138458 + isyst * 0.000768592171557;
    if ((pt) < 60.0   && fabs(eta) < 0.9) return 0.921180009842 + isyst * 0.00080159636303;
    if ((pt) < 120.0  && fabs(eta) < 0.9) return 0.918352901936 + isyst * 0.00185961188485;
    if ((pt) < 200.0  && fabs(eta) < 0.9) return 0.910844266415 + isyst * 0.00739344058835;
    if ((pt) < 1200.0 && fabs(eta) < 0.9) return 0.894463002682 + isyst * 0.016525458852;
    if ((pt) < 25.0   && fabs(eta) < 1.2) return 0.942260980606 + isyst * 0.00458041035964;
    if ((pt) < 30.0   && fabs(eta) < 1.2) return 0.945485949516 + isyst * 0.00346783935787;
    if ((pt) < 40.0   && fabs(eta) < 1.2) return 0.946832001209 + isyst * 0.00141910674422;
    if ((pt) < 50.0   && fabs(eta) < 1.2) return 0.946245908737 + isyst * 0.000673513472744;
    if ((pt) < 60.0   && fabs(eta) < 1.2) return 0.945586264133 + isyst * 0.00240884834276;
    if ((pt) < 120.0  && fabs(eta) < 1.2) return 0.945138394833 + isyst * 0.00318644606928;
    if ((pt) < 200.0  && fabs(eta) < 1.2) return 0.933813333511 + isyst * 0.014169270918;
    if ((pt) < 1200.0 && fabs(eta) < 1.2) return 0.931742787361 + isyst * 0.0243677246898;
    if ((pt) < 25.0   && fabs(eta) < 2.1) return 0.934685409069 + isyst * 0.00235550744943;
    if ((pt) < 30.0   && fabs(eta) < 2.1) return 0.940949559212 + isyst * 0.0017736671693;
    if ((pt) < 40.0   && fabs(eta) < 2.1) return 0.941943407059 + isyst * 0.000142803887399;
    if ((pt) < 50.0   && fabs(eta) < 2.1) return 0.943855106831 + isyst * 0.000241549432239;
    if ((pt) < 60.0   && fabs(eta) < 2.1) return 0.94069480896  + isyst * 0.00167134522243;
    if ((pt) < 120.0  && fabs(eta) < 2.1) return 0.926266431808 + isyst * 0.00212335629489;
    if ((pt) < 200.0  && fabs(eta) < 2.1) return 0.873467862606 + isyst * 0.00932832611851;
    if ((pt) < 1200.0 && fabs(eta) < 2.1) return 0.823928773403 + isyst * 0.0230251207295;
    if ((pt) < 25.0   && fabs(eta) < 2.4) return 0.837569534779 + isyst * 0.00488000441924;
    if ((pt) < 30.0   && fabs(eta) < 2.4) return 0.866438448429 + isyst * 0.00319838676876;
    if ((pt) < 40.0   && fabs(eta) < 2.4) return 0.885224223137 + isyst * 0.00194770815806;
    if ((pt) < 50.0   && fabs(eta) < 2.4) return 0.898686885834 + isyst * 0.00179089574024;
    if ((pt) < 60.0   && fabs(eta) < 2.4) return 0.901396632195 + isyst * 0.00355735499739;
    if ((pt) < 120.0  && fabs(eta) < 2.4) return 0.906494557858 + isyst * 0.00504503993108;
    if ((pt) < 200.0  && fabs(eta) < 2.4) return 0.884702563286 + isyst * 0.0182467487213;
    if ((pt) < 1200.0 && fabs(eta) < 2.4) return 0.80960047245  + isyst * 0.0950186278378;
    return 1;
}

//______________________________________________________________________________________
float lepsf_MuTightVVV_MuTightVVVMu8(float PT, float Eta, int isyst=0)
{
    float pt  = std::min((float)1199.,PT);
    float eta = std::min((float)2.39,std::max((float)-2.39,Eta));
    if (isyst != 1 && isyst != -1 && isyst != 0)
        printf(Form("WARNING - in function=%s, isyst=%d is not recommended!\n", __FUNCTION__, isyst));
    if ((pt) < 25.0   && fabs(eta) < 0.9) return 0.933527767658 + isyst * 0.00252632647732;
    if ((pt) < 30.0   && fabs(eta) < 0.9) return 0.933456897736 + isyst * 0.00152941158904;
    if ((pt) < 40.0   && fabs(eta) < 0.9) return 0.934123814106 + isyst * 5.7151570156e-05;
    if ((pt) < 50.0   && fabs(eta) < 0.9) return 0.933176159859 + isyst * 0.000533302705251;
    if ((pt) < 60.0   && fabs(eta) < 0.9) return 0.931691288948 + isyst * 0.00134394291184;
    if ((pt) < 120.0  && fabs(eta) < 0.9) return 0.929507613182 + isyst * 0.00175162047452;
    if ((pt) < 200.0  && fabs(eta) < 0.9) return 0.924368977547 + isyst * 0.00746803644143;
    if ((pt) < 1200.0 && fabs(eta) < 0.9) return 0.910157442093 + isyst * 0.0167671085273;
    if ((pt) < 25.0   && fabs(eta) < 1.2) return 0.96690428257  + isyst * 0.00463995182995;
    if ((pt) < 30.0   && fabs(eta) < 1.2) return 0.968839883804 + isyst * 0.000296189435009;
    if ((pt) < 40.0   && fabs(eta) < 1.2) return 0.968176484108 + isyst * 0.00147301227187;
    if ((pt) < 50.0   && fabs(eta) < 1.2) return 0.967356085777 + isyst * 0.0012252910266;
    if ((pt) < 60.0   && fabs(eta) < 1.2) return 0.966672122478 + isyst * 0.00253712385559;
    if ((pt) < 120.0  && fabs(eta) < 1.2) return 0.965913832188 + isyst * 0.00324173670128;
    if ((pt) < 200.0  && fabs(eta) < 1.2) return 0.962421000004 + isyst * 0.0145629366561;
    if ((pt) < 1200.0 && fabs(eta) < 1.2) return 0.961861371994 + isyst * 0.0236944487724;
    if ((pt) < 25.0   && fabs(eta) < 2.1) return 0.961845993996 + isyst * 0.00034315722064;
    if ((pt) < 30.0   && fabs(eta) < 2.1) return 0.962982833385 + isyst * 0.00180503994187;
    if ((pt) < 40.0   && fabs(eta) < 2.1) return 0.962533831596 + isyst * 0.000139178337978;
    if ((pt) < 50.0   && fabs(eta) < 2.1) return 0.963077664375 + isyst * 0.0008053328847;
    if ((pt) < 60.0   && fabs(eta) < 2.1) return 0.963417887688 + isyst * 0.00160263939342;
    if ((pt) < 120.0  && fabs(eta) < 2.1) return 0.962129116058 + isyst * 0.000363735247895;
    if ((pt) < 200.0  && fabs(eta) < 2.1) return 0.935746133327 + isyst * 0.0082700842047;
    if ((pt) < 1200.0 && fabs(eta) < 2.1) return 0.89957177639  + isyst * 0.0245530433342;
    if ((pt) < 25.0   && fabs(eta) < 2.4) return 0.944805383682 + isyst * 0.00573946175886;
    if ((pt) < 30.0   && fabs(eta) < 2.4) return 0.948861658573 + isyst * 0.0148002473209;
    if ((pt) < 40.0   && fabs(eta) < 2.4) return 0.949180960655 + isyst * 0.00205940031199;
    if ((pt) < 50.0   && fabs(eta) < 2.4) return 0.949977576733 + isyst * 0.00186501847954;
    if ((pt) < 60.0   && fabs(eta) < 2.4) return 0.947516798973 + isyst * 0.00371860765466;
    if ((pt) < 120.0  && fabs(eta) < 2.4) return 0.948109149933 + isyst * 0.00521480251546;
    if ((pt) < 200.0  && fabs(eta) < 2.4) return 0.926202654839 + isyst * 0.0195444637705;
    if ((pt) < 1200.0 && fabs(eta) < 2.4) return 0.865132570267 + isyst * 0.532614728793;
    return 1;
}

