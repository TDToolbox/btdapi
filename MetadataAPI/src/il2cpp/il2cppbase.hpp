#pragma once
#include "core.hpp"


class MetadataBinary {
    u8* m_bin; // ToDo generic Bins

  public:
    Il2CppCodeRegistration* m_codeReg;
    Il2CppMetadataRegistration* m_metReg;

    void** GlobalMethodPointers;

    // ToDo: Figure out actual type
    u32* FieldOffsets;

    virtual void loadMetadata(u8* file);
};

class MetadataFile {
};

class MetadataDumper {
    MetadataBinary m_mbin;
    MetadataFile m_mfile;
};