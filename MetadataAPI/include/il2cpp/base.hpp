#pragma once
#include "core.hpp"
#include "binutils.hpp"

struct Il2CppCodeRegistration;
struct Il2CppMetadataRegistration;
struct Il2CppGlobalMetadataHeader;

class Il2CppDumper {
  protected:
    u8* m_bin;
    u8* m_metadata;

    Il2CppGlobalMetadataHeader* m_hdr;
    ExecFile* m_exe;

    
    int FindVersion();

    std::vector<st> FindPtrs(st val);
    std::vector<st> GetPtrs(st val);


  public:

    virtual void FindMetadataReg() = 0;
    virtual void FindCodeReg() = 0;

    Il2CppMetadataRegistration* m_metreg;
    Il2CppCodeRegistration* m_codereg;

    Il2CppDumper(u8* bin, u8* metadata, ExecFile* exec)
    {
        m_bin = bin;
        m_metadata = metadata;
        m_exe = exec;
    };

};

class Il2CppDumperv150 : public Il2CppDumper {
  public:
    using Il2CppDumper::Il2CppDumper;
    void FindMetadataReg() override;
    void FindCodeReg() override;
};

class Il2CppDumperv230 : public Il2CppDumperv150 {
  public:
    using Il2CppDumperv150::Il2CppDumperv150;
};
class Il2CppDumperv240 : public Il2CppDumperv230 {
  public:
    using Il2CppDumperv230::Il2CppDumperv230;
};
class Il2CppDumperv242 : public Il2CppDumperv240 {
  public:
    using Il2CppDumperv240::Il2CppDumperv240;
    void FindCodeReg() override;
};