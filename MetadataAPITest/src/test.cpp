#include "core.hpp"
#include "gtest/gtest.h"
#include "binutils.hpp"
#include "g3log/g3log.hpp"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "il2cpp/base.hpp"

std::vector<u8> x86Bin;
std::vector<u8> x64Bin;
std::vector<u8> btd6Bin;
std::vector<u8> btd6Met;

void LoadBin(std::string path, std::vector<u8>& vec) {
    std::ifstream file(path,
                           std::ios::binary | std::ios::ate);
    if (!file) {
        std::wstring cd = std::filesystem::current_path();
        FAIL();
    }

    std::streamsize x64size = file.tellg();
    file.seekg(0, std::ios::beg);

    vec = std::vector<u8>((size_t)(x64size));
    if (!(file.read((char*)(vec.data()), x64size))) {
        FAIL();
    }
}

TEST(BinUtils, CheckArchitecture)
{
    LoadBin("bins/TestBins/BinTest-x64.dll", x64Bin);

    PeFile x64pef(x64Bin.data());
    ASSERT_FALSE(x64pef.is32bit);

    LoadBin("bins/TestBins/BinTest-x86.dll", x86Bin);

    PeFile x86pef(x86Bin.data());
    ASSERT_TRUE(x86pef.is32bit);
}

TEST(BinUtils, Read32bitSections)
{
    PeFile x86pef(x86Bin.data());

    // Values gotten from CFF explorer.
    std::vector<ExecSec> secs = {{0x400, 0x400 + 0xE00},
                                 {0x1200, 0x1200 + 0x800},
                                 {0x1A00, 0x1A00 + 0x200},
                                 {0x1C00, 0x1C00 + 0x200},
                                 {0x1E00, 0x1E00 + 0x200}};

    for (size_t i = 0; i < secs.size(); ++i) {
        ASSERT_EQ(secs[i].start, x86pef.Sections[i].start);
        ASSERT_EQ(secs[i].end, x86pef.Sections[i].end);
    }
}

TEST(BinUtils, Read64bitSections)
{
    PeFile x64pef(x64Bin.data());

    // Values gotten from CFF explorer.
    std::vector<ExecSec> secs = {
        {0x400, 0x400 + 0xE00},   {0x1200, 0x1200 + 0xC00},
        {0x1E00, 0x1E00 + 0x200}, {0x2000, 0x2000 + 0x200}, 
        {0x2200, 0x2200 + 0x200}, {0x2400, 0x2400 + 0x200}};

    for (size_t i = 0; i < secs.size(); ++i) {
        ASSERT_EQ(secs[i].start, x64pef.Sections[i].start);
        ASSERT_EQ(secs[i].end, x64pef.Sections[i].end);
    }
}


// https://github.com/Perfare/Il2CppDumper/blob/master/Il2CppDumper/Utils/PlusSearch.cs#L289
TEST(MetadataAPI, MetadataRegistrations)
{
    LoadBin("bins/TestBins/BTD6.dll", btd6Bin);
    LoadBin("bins/TestBins/global-metadata.dat", btd6Met);


 


}

//
// There are three ways to locate the metadata registration
// ====== First way =====
// Il2cppdumper does <24.2
// https://github.com/Perfare/Il2CppDumper/blob/master/Il2CppDumper/Utils/PlusSearch.cs#L186
// Just searches for the MethodCount in the binary then verifies that the
// pointer is valid.
// 
// ===== Second way =====
// Il2cppDumper does >24.2:
// https://github.com/Perfare/Il2CppDumper/blob/master/Il2CppDumper/Utils/PlusSearch.cs#L351
// 
// At the end of the Il2cppCodeRegistration struct there's the field 
// const Il2CppCodeGenModule** codeGenModules;
// The first module in this is always mscorlib, so the scanning method tries to
// find it.
//
// The first field in Il2cppCodeGenModule is const char* moduleName;
// So first, you need to scan for all instanced of UTF-8 encoded "mscorlib.dll"
// Once you find it, since we're dealing with constant pointers, you need to 
// convert the offset you've found to a virtual address. 
// Hopefully that's the address of the Il2cppCodeGenModule.
// We want the entire list, so we'd search for that virtual address
// And finally, we want the pointer to the list. So we scan for that lists's
// virtual address. Now the pointer left should be the codeGenModules field.
// 
// ===== Third Way =====
// Il2cppInspector does:
// https://github.com/djkaty/Il2CppInspector/tree/master/Il2CppInspector.Common/Architectures
//
// I haven't read too much into it, ARM64 seems to have the best explaination
// for how it works
// This method is not implemented nor supported
//
TEST(MetadataAPI, CodeRegistrations) {
    PeFile btd6pe(btd6Bin.data());

    Il2CppDumperv242 dumper(btd6Bin.data(), btd6Met.data(), &btd6pe);

    dumper.FindVersion();
    dumper.FindCodeReg();
    dumper.FindMetadataReg();
    dumper.DumpHeader();

    SUCCEED();
}