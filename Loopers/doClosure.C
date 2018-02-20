{
  gROOT->ProcessLine(".L Functions.C+"); 
  gROOT->ProcessLine(".L FakeRateClosure.C+");
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
  
  dataset[0] = "tt1l";
  ch[0] = new TChain("t");
  myhelper = babylocation + "ttbar_1ltbr_mgmlm_ext1*.root";             ch[0]->Add(myhelper.c_str());//XXX
  myhelper = babylocation + "ttbar_1ltop_mgmlm_ext1*.root";             ch[0]->Add(myhelper.c_str());
//  myhelper = babylocation + "ttbar_dilep_mgmlm_ext1*.root";             ch[5]->Add(myhelper.c_str());

  dataset[1] = "Wjets";
  ch[1] = new TChain("t");
//  myhelper = babylocation + "wjets_incl_mgmlm*.root";                   ch[1]->Add(myhelper.c_str());
  myhelper = babylocation + "wjets_ht100_mgmlm_ext1*.root";             ch[1]->Add(myhelper.c_str());
  myhelper = babylocation + "wjets_ht200_mgmlm_ext1*.root";             ch[1]->Add(myhelper.c_str());
  myhelper = babylocation + "wjets_ht400_mgmlm_ext1*.root";             ch[1]->Add(myhelper.c_str());
  myhelper = babylocation + "wjets_ht600_mgmlm_ext1*.root";             ch[1]->Add(myhelper.c_str());
  myhelper = babylocation + "wjets_ht800_mgmlm_ext1*.root";             ch[1]->Add(myhelper.c_str());
  myhelper = babylocation + "wjets_ht1200_mgmlm_nonext*.root";          ch[1]->Add(myhelper.c_str());
  myhelper = babylocation + "wjets_ht2500_mgmlm_ext1*.root";            ch[1]->Add(myhelper.c_str());
//  myhelper = babylocation + "Wpjj_lnu_madgraph*.root";                  ch[1]->Add(myhelper.c_str());
//  myhelper = babylocation + "Wmjj_lnu_madgraph*.root";                  ch[1]->Add(myhelper.c_str());

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
