// DumperCLI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define MAPI_MVER 24.2
#include "il2cpp/base.hpp"
#include "core.hpp"
#include "fileutils.hpp"
#include <iostream>
#include <vector>


struct il2cppver {
    u32 ver = 0;
    // Unity doesnt track the subversion, its maintained by the community.
    u32 subver = 0;
};

il2cppver getVersion()
{
    il2cppver ver;

    return ver;
}

int main(int argc, char** argv) {
    // Currently theres not going to be any CLI whilst this tool is under dev
    // Just hardcoded values...
    std::string metPath =
        "C:\\SteamLibrary\\steamapps\\common\\BloonsTD6\\BloonsTD6_"
        "Data\\il2cpp_data\\Metadata\\global-metadata.dat";
    std::string binPath =
        "C:\\SteamLibrary\\steamapps\\common\\BloonsTD6\\GameAssembly.dll";

    std::vector<u8> met = loadFile(metPath);
    std::vector<u8> bin = loadFile(binPath);

    Il2CppDumperv242 xd();
    


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
