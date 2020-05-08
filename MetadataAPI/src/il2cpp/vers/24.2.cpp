#include "il2cpp/base.hpp"

#define INCLUDE_STATICS
#define MAPI_MVER 24
#define MAPI_REV 2
#include "MetadataInclude.hpp"
#include MetadataCacheInclude
#undef MAPI_VER
#undef INCLUDE_STATICS

#include "binutils.hpp"
#include "g3log/g3log.hpp"
#include <algorithm>
#include <functional>
#include <intrin.h>

void Il2CppDumperv242::FindCodeReg()
{
    for (ExecSec sec : m_exe->Sections) {
        std::vector<u8> vec(m_bin + sec.start, m_bin + sec.end);
        const u8 modname[] = "mscorlib.dll";

        std::vector<u8> strBytes(modname, modname + sizeof(modname));

        std::vector<u8>::iterator it = vec.begin();

        for (;;) {

            it = std::search(it, vec.end(),
                             std::boyer_moore_horspool_searcher(
                                 strBytes.begin(), strBytes.end()));

            if (it == vec.end()) {
                break;
            }

            st strptr = sec.vstart + (it - vec.begin());
            std::vector<u8> strptrb((u8*)&strptr,
                                    (u8*)&strptr + sizeof(strptr));

            // Find a pointer to the String (moduleName field)

            for (st ptr : FindPtrs(strptr)) {

                // Find a pointer to the codegen module

                for (st ptr2 : FindPtrs(ptr)) {

                    // Find field that contains pointer
                    for (st ptr3 : GetPtrs(ptr2)) {

                        st ptr4 = m_exe->OTV(ptr3);
                        st coderegptr = ptr4 - offsetof(Il2CppCodeRegistration,
                                                        codeGenModules);
                        m_codereg =
                            (Il2CppCodeRegistration*)(m_bin +
                                                      m_exe->VTO(coderegptr));

                        return;
                    }
                }
            }

            std::advance(it, 1);
        }
    };

    LOG(FATAL) << "Could not find code registration ";
    // We haven't found shit
    return;
}

void Il2CppDumperv242::FindMetadataReg()
{
    st typeDefinitionCount =
        m_hdr->typeDefinitionsCount / sizeof(Il2CppTypeDefinition);

    for (st val : GetPtrs(typeDefinitionCount)) {
        if (!m_exe->CheckPtrRangeRa(val)) {
            break;
        }

        st metadataUsageListCount =
            m_hdr->metadataUsageListsCount / sizeof(Il2CppMetadataUsageList);

        Il2CppMetadataUsageList* metadataUsageLists =
            (Il2CppMetadataUsageList*)(m_metadata + m_hdr->metadataUsageListsOffset);
        Il2CppMetadataUsagePair* metadataUsagePairs =
            (Il2CppMetadataUsagePair*)(m_metadata +
                                       m_hdr->metadataUsagePairsOffset);

        st metadataUsages = 0;

        // Why? I'm not sure, but its how il2cppdumper does it.
        for (auto i = 0; i < metadataUsageListCount; ++i) {
            for (auto k = 0; k < metadataUsageLists[i].count; ++k) {
                auto offset = metadataUsageLists[i].start + k;
                auto metadataUsagePair = metadataUsagePairs[offset];
                
                if (metadataUsages < metadataUsagePair.destinationIndex) {
                    metadataUsages = metadataUsagePair.destinationIndex;
                }
            }
        }

        st* arr = (st*)(m_bin + val);
        for (auto i = 0; i < metadataUsages; i++) {
            if (!m_exe->CheckPtrRangeVa(arr[i])) {
                break;
            }
        }

        st ptr = val - offsetof(Il2CppMetadataRegistration,
                                typeDefinitionsSizesCount);

        m_metreg = (Il2CppMetadataRegistration*)(m_bin + ptr);

        return;
    }
}

void Il2CppDumperv242::DumpHeader()
{
    Il2CppCodeGenOptions codeGenOptions{0};
    il2cpp::vm::MetadataCache::Register(m_codereg, m_metreg, &codeGenOptions);

}