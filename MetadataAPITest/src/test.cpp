#include "core.hpp"
#include "gtest/gtest.h"
#include "binutils.hpp"
#include "g3log/g3log.hpp"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <filesystem>


std::vector<char> x86Bin;
std::vector<char> x64Bin;

TEST(BinUtils, CheckArchitecture)
{
    // 64 bit
    std::ifstream x64file("bin/TestBins/BinTest-x64.dll", std::ios::binary | std::ios::ate);
    if (!x64file) {
        FAIL();
    }
    
    std::streamsize x64size = x64file.tellg();
    x64file.seekg(0, std::ios::beg);

    x64Bin = std::vector<char>((size_t)(x64size));
    if (!(x64file.read(x64Bin.data(), x64size))) {
        FAIL();
    }

    PeFile x64pef(x64Bin.data());
    ASSERT_FALSE(x64pef.is32bit);

    // 32 bit
    std::ifstream x86file("bin/TestBins/BinTest-x86.dll", std::ios::binary | std::ios::ate);
    if (!x86file) {
        FAIL();
    }
    std::streamsize x86size = x86file.tellg();
    x86file.seekg(0, std::ios::beg);

    x86Bin = std::vector<char>((size_t)(x86size));
    if (!(x86file.read(x86Bin.data(), x86size))) {
        FAIL();
    }

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