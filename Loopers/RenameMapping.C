#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


std::vector<std::string> split(std::string mystring, std::string c)
{
    std::string s = mystring;
    std::vector<std::string> v;
    std::string::size_type i = 0;
    std::string::size_type j = s.find(c);
    while (j != std::string::npos)
    {
        v.push_back(s.substr(i, j - i));
        i = ++j;
        j = s.find(c, j);
        if (j == std::string::npos)
        { v.push_back(s.substr(i, s.length())); }
    }
    return v;
}


void RenameMapping(std::string map, std::string directory)
{
    char buffer[500];
    char char1[500];
    char char2[500];
    std::ifstream IN(map.c_str());
    while (IN.getline(buffer, 500, '\n'))
    {
        sscanf(buffer, "%s\t%s", char1, char2);
        std::ostringstream ss1;
        ss1 << char1;
        std::ostringstream ss2;
        ss2 << char2;
        std::string fullstring1 = ss1.str();
        std::string string2 = ss2.str();
        std::vector<std::string> helpervec = split(fullstring1, "/");
        if (helpervec.size() == 0) { continue; }
        std::string string1 = helpervec[helpervec.size() - 1];
        std::string output = directory + string1;
        std::string input  = directory + string2;
        std::ifstream filename(input.c_str());
        if (filename.good())
        {
            //std::string command = "echo mv " + input + " " + output;
            std::string command = "mv " + input + " " + output;
            system(command.c_str());
        }
    }
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        std::cout << "RenameMapping needs two input parameter - first is path to the mapping list, second is the directory where the output files where stored." << std::endl;
        return 0;
    }
    char* map = argv[1];
    char* dir = argv[2];
    RenameMapping(map, dir);
    return 0;
}
