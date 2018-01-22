{

  gROOT->ProcessLine(".L Functions.C+"); 

  //gROOT->ProcessLine(".L Skimmer.C+");
  gROOT->ProcessLine(".L SRLooper.C+");
  //gROOT->ProcessLine(".L Nminus1Looper.C+");
  //gROOT->ProcessLine(".L FakeRateMethod.C+");
  //gROOT->ProcessLine(".L FakeRateBtagVal.C+");
  //gROOT->ProcessLine(".L Check3lWZCR.C+");
  //gROOT->ProcessLine(".L WWTTWSplitter.C+");
  //gROOT->ProcessLine(".L ValidationLooper.C+");
  const unsigned int chainsize = 2;
  TChain *ch[chainsize];
  string dataset[chainsize];

  //lightly skimmed babies
  //string babylocation  = "/nfs-7/userdata/bhashemi/WWW_babies/WWW_v0.1.16/skim/";
  string babylocation  = "/nfs-7/userdata/bhashemi/WWW_babies/WWW_v0.1.17/skim/";
  
  //fully skimmed babies
  //string babylocation = "/nfs-7/userdata/haweber/WWWskims/WWW_v0.1.16/";
  //string babylocation = "/hadoop/cms/store/user/phchang/metis/wwwlooper/v16_skim_v2_5/WWW_v0_1_16_v16_skim_v2_5/";
  //string babylocation = "/hadoop/cms/store/user/phchang/AutoTwopler_babies/merged/VVV/WWW_v0.1.16_bdtbranchv2/skim/";
  string myhelper;
  
  dataset[0] = "WWWv2";
  ch[0] = new TChain("t");
  myhelper = babylocation + "www_incl_amcnlo_*.root";                   ch[0]->Add(myhelper.c_str());//240000
  dataset[1] = "WWW";
  ch[1] = new TChain("t");
  myhelper = babylocation + "www_2l_mia_*.root";                        ch[1]->Add(myhelper.c_str());//91900 //XXX
  myhelper = babylocation + "www_2l_ext1_mia_*.root";                   ch[1]->Add(myhelper.c_str());//164800

  int j = 0;
  for(int i = 0; i<chainsize; ++i){
    //if(i>=3&&i<=15) continue;//don't run over individual samples (but for signal) - run over combined background instead
    //if activating above flag, run over ttV and WW too for validation looper and WWTTW splitter 
    //if (i != 1 ) continue;
    TChain *mych = ch[i];
    string mydataset = dataset[i];
    cout << "Now entering " << mydataset << endl;
    ScanChain(mych,true,-1,mydataset,j); 
    ++j;
  }
}
