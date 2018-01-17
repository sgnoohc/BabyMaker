#include <fstream>
#include <sstream>
#include <iostream>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>

using namespace std;

void skim_macro(string inpath = "./", string outpath = "./", string intag = "output", string outtag = "skim")
{
    //--------------------------------------------------
    // cut for output files
    //--------------------------------------------------
    // NOTE: string below doesn't work correctly, implicitly requires all events to have 2 leptons
    //  const char* sel = "((njets >= 2 || njets_up >= 2 || njets_dn >= 2) || (evt_type == 2 && nlep > 0 && abs(lep_pdgId[0]) == 13) || (nlep > 2 && lep_pt[0] > 25 && lep_pt[1] > 20)) ";
    //const char* sel = "((njets >= 2 || njets_up >= 2 || njets_dn >= 2) || (evt_type == 2 && nlep > 0) || (nlep > 2)) ";
    const char* sel = "((evt_type == 1 && nlep == 2) || (nlep > 2)) ";
    //cout << "Skimming with selection : "<<sel<<endl;
    //--------------------------------------------------
    // input and output file
    //--------------------------------------------------
    const char* infilename = Form("%s/%s*.root", inpath.c_str(), intag.c_str());
    const char* outfilename = Form("%s/%s.root", outpath.c_str(), outtag.c_str());
    //--------------------------------------------------
    // cout stuff
    //--------------------------------------------------
    cout << "Reading in : " << infilename << endl;
    cout << "Writing to : " << outfilename << endl;
    cout << "Selection : " << sel << endl;
    //--------------------------------------------------
    // read input file, write to output files
    //--------------------------------------------------
    //long long max_tree_size = 5000000000LL; // 5GB
    //long long max_tree_size = 2500000000LL; // 2.5GB
    //TTree::SetMaxTreeSize(max_tree_size);
    TChain *chain = new TChain("t");
    chain->Add(infilename);
    unsigned int input_entries = chain->GetEntries();
    cout << "Input tree has entries: " << input_entries << endl;
    if (input_entries == 0)
    {
        cout << "ERROR: no entries in input tree, exiting.." << endl;
        return;
    }
    //-------------------
    // skim
    //-------------------
    TFile *outfile = TFile::Open(outfilename, "RECREATE");
    assert(outfile != 0);
    TTree* outtree = chain->CopyTree(sel);
    unsigned int output_entries = outtree->GetEntries();
    cout << "Output tree has entries: " << output_entries << endl
         << "Reduction factor of: " << double(input_entries) / double(output_entries) << endl;
    outtree->Write();
    //-------------------
    // Copy TH1Ds
    //-------------------
    TObjArray *listOfFiles = chain->GetListOfFiles();
    TIter fileIter(listOfFiles);
    std::vector <TH1D*> ourHists;
    TFile *currentFile = 0;
    fileIter.Reset();
    //file loop
    while ((currentFile = (TFile*)fileIter.Next()))
    {
        TFile *currentfile = TFile::Open(currentFile->GetTitle());
        //Hist loop
        for (auto&& keyAsObj : *currentfile->GetListOfKeys())
        {
            auto key = (TKey*)keyAsObj;
            if (strncmp(key->GetClassName(), "TH1D", 1000) != 0) { continue; }
            TH1D *hist = (TH1D*)key->ReadObj();
            //OurHist loop
            bool foundIt = false;
            for (unsigned int i = 0; i < ourHists.size(); i++)
            {
                if (strncmp(ourHists[i]->GetTitle(), hist->GetTitle(), 1000) == 0) { ourHists[i]->Add(hist); foundIt = true; }
            }
            if (!foundIt)
            {
                outfile->cd();
                TH1D* hist_clone = (TH1D*) hist->Clone(hist->GetName());
                ourHists.push_back(hist_clone);
            }
        }
        currentfile->Close();
    }
    cout << "Histograms merged: " << ourHists.size() << endl;
    if (ourHists.size()) { cout << ourHists[0]->GetBinContent(0) << endl; }
    outfile->cd();
    for (unsigned int i = 0; i < ourHists.size(); i++) { ourHists[i]->Write(); }
    //-------------------
    // Cleanup
    //-------------------
    outfile->Close();
}
