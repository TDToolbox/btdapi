#pragma once
#include "core.hpp"
#include <vector>

// Include less headers
// TODO: Make header to do arch shit
#define _AMD64_
#include <windef.h>
#include <winnt.h>

// Every executable format I've seen has the concept of sections.
class ExecSec {
  public:
    st start;
    st end;
    st vstart;
    st vend;
};

class ExecFile {
  public:
    vp File;
    std::vector<ExecSec> Sections;

    // Virtual To Offset (VA to Offset)
    virtual st VTO(st addr);
    // Offset to Virtual
    virtual st OTV(st addr);

    virtual ~ExecFile(){};
};

class PE : public ExecFile {
  public:
    IMAGE_DOS_HEADER* stub;
    IMAGE_NT_HEADERS64* hdr64;
    IMAGE_NT_HEADERS32* hdr32;
    bool is32bit;

    PE(vp bin);

    virtual ~PE(){};
};

// Use: PeFile(byte* pBin), a pointer to a file loaded in memory.
class PeFile : public PE {
  public:
    virtual st VTO(st addr) override;
    virtual st OTV(st addr) override;

    PeFile(vp bin);
};

// Use: PeMemory(byte* pBin), a pointer to the loaded DLL's bytes.
class PeMemory : public PE {
  public:
    virtual st VTO(st addr) override { return 0; };

    PeMemory(vp bin);
};