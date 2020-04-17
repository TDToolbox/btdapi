#include "il2cpp/base.hpp"

#define MAPI_MVER 24
#define MAPI_REV 2
#include "MetadataInclude.hpp"
#undef MAPI_VER

#include "binutils.hpp"
#include <algorithm>
#include <functional>
#include <intrin.h>
#include "g3log/g3log.hpp"



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
                            (Il2CppCodeRegistration*)m_exe->VTO(coderegptr);

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