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
float lepsf_MuTightVVV_MuTightVVVMu17(float PT, float Eta)
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
//______________________________________________________________________________________
//______________________________________________________________________________________


//______________________________________________________________________________________
float fakerate_mu_data(float Eta, float conecorrPT)
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
float fakerate_mu_data_unc(float Eta, float conecorrPT)
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
float fakerate_mu_qcd(float Eta, float conecorrPT)
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
float fakerate_mu_qcd_unc(float Eta, float conecorrPT)
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
float fakerate_el_data(float Eta, float conecorrPT)
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
float fakerate_el_data_unc(float Eta, float conecorrPT)
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
float fakerate_el_qcd(float Eta, float conecorrPT)
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
float fakerate_el_qcd_unc(float Eta, float conecorrPT)
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
