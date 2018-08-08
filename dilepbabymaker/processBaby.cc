#include "TChain.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TString.h"

#include "ScanChain_v2.h"

#include "hadoopmap.h"

#include <iostream>

int main(int argc, char **argv)
{
    //
    // Parse options
    //
    if (argc < 3)
    {
        std::cout << "USAGE: processBaby <filename> [<max_num_events>] [index] [BabyMode] [type anything to make it verbose]" << std::endl;
        return 1;
    }

    TString infile(argv[1]);
    int max_events = -1;
    int index = 1;
    int babymode = 0;
    bool verbose = false;

    if (argc >= 3)
        max_events = atoi(argv[2]);

    if (argc >= 4)
        index = atoi(argv[3]);

    if (argc >= 5)
        babymode = atoi(argv[4]);

    if (argc >= 6)
        verbose = true;

    std::cout << "set max number of events to: " << max_events << std::endl;
    std::cout << "running on files: " << infile.Data() << std::endl;

    //
    // Run
    //
    babyMaker_v2 *looper = new babyMaker_v2();
    switch (babymode)
    {
        case 0: looper->SetBabyMode(babyMaker_v2::kWWWBaby); break;
        case 1: looper->SetBabyMode(babyMaker_v2::kFRBaby); break;
        case 2: looper->SetBabyMode(babyMaker_v2::kOSBaby);  break;
        case 3: looper->SetBabyMode(babyMaker_v2::kTnPBaby); break;
        case 4: looper->SetBabyMode(babyMaker_v2::kAllBaby); break;
        case 5: looper->SetBabyMode(babyMaker_v2::kPOGBaby); break;
        case 6: looper->SetBabyMode(babyMaker_v2::kHWWBaby); break;

    }
    looper->ProcessCMS4(infile, max_events, index, verbose);
    delete looper;
    return 0;
}
