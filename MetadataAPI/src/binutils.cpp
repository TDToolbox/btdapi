#include "binutils.hpp"
#include "core.hpp"
#include "g3log/g3log.hpp"
#include <algorithm>

st ExecFile::VTO(st addr)
{
    LOG(FATAL) << "Calling base class \"ExecFile\" instead of one of the "
               << "derivative classes.";

    addr = 0;
    return addr;
}

st ExecFile::OTV(st addr) {
    LOG(FATAL) << "Calling base class \"ExecFile\" instead of one of the "
               << "derivative classes.";

    addr = 0;
    return addr;
}

PE::PE(vp bin)
{
    // Initializes the Is32Bit and headers
    File = bin;

    stub = (IMAGE_DOS_HEADER*)(File);
    if (stub->e_magic != IMAGE_DOS_SIGNATURE) {
        LOG(FATAL) << "PE File given has incorrect signature!";
    }

    hdr64 = (IMAGE_NT_HEADERS64*)((st)(File) + (st)(stub->e_lfanew));

    if (hdr64->Signature != IMAGE_NT_SIGNATURE) {
        LOG(FATAL) << "PE File given is not an NT file!";
    }

    if (hdr64->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR32_MAGIC) {
        is32bit = true;
        hdr32 = (IMAGE_NT_HEADERS32*)((st)(File) + (st)(stub->e_lfanew));
        LOG(INFO) << "Binary is 32 bit!";
    }
    else if (hdr64->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC) {
        is32bit = false;
        LOG(INFO) << "Binary is 64 bit!";
    }
    else {
        LOG(FATAL) << "OptionalHeader was not 32 bit or 64 bit!";
    }
}

template <typename HdrArch>
std::vector<ExecSec> LoadSecs(PE*, ExecSec (*)(IMAGE_SECTION_HEADER*, st));

template <>
std::vector<ExecSec>
LoadSecs<IMAGE_NT_HEADERS32>(PE* pe, ExecSec (*f)(IMAGE_SECTION_HEADER*, st))
{
    std::vector<ExecSec> secs;

    // Both FileHeaders should be the same accross architectures
    // Only sizeof(IMAGE_NT_HEADERSXX) should change
    for (st i = 0; i < pe->hdr64->FileHeader.NumberOfSections; ++i) {

        IMAGE_SECTION_HEADER* sh =
            (IMAGE_SECTION_HEADER*)((st)(pe->File) + (st)(pe->stub->e_lfanew) +
                                    sizeof(IMAGE_NT_HEADERS32) +
                                    (sizeof(IMAGE_SECTION_HEADER) * i));
        secs.push_back(f(sh, pe->hdr32->OptionalHeader.ImageBase));
    }

    return secs;
};

template <>
std::vector<ExecSec>
LoadSecs<IMAGE_NT_HEADERS64>(PE* pe, ExecSec (*f)(IMAGE_SECTION_HEADER*, st))
{
    std::vector<ExecSec> secs;

    // Both FileHeaders should be the same accross architectures
    // Only sizeof(IMAGE_NT_HEADERSXX) should change
    for (st i = 0; i < pe->hdr64->FileHeader.NumberOfSections; ++i) {

        IMAGE_SECTION_HEADER* sh =
            (IMAGE_SECTION_HEADER*)((st)(pe->File) + (st)(pe->stub->e_lfanew) +
                                    sizeof(IMAGE_NT_HEADERS64) +
                                    (sizeof(IMAGE_SECTION_HEADER) * i));
        secs.push_back(f(sh, pe->hdr64->OptionalHeader.ImageBase));
    }

    return secs;
};

PeFile::PeFile(vp bin) : PE::PE(bin)
{
    // First initialize the Sections field.

    if (is32bit) {
        Sections =
            // BAD = base address
            LoadSecs<IMAGE_NT_HEADERS32>(this, [](IMAGE_SECTION_HEADER* sh,
                                                  st bad) {
                return ExecSec{sh->PointerToRawData,
                               sh->PointerToRawData + sh->SizeOfRawData,
                               sh->VirtualAddress + bad,
                               sh->VirtualAddress + sh->SizeOfRawData + bad};
            });
    }
    else {
        Sections = LoadSecs<IMAGE_NT_HEADERS64>(
            this, [](IMAGE_SECTION_HEADER* sh, st bad) {
                return ExecSec{sh->PointerToRawData,
                               (st)sh->PointerToRawData + sh->SizeOfRawData,
                               sh->VirtualAddress + bad,
                               (st)sh->VirtualAddress + sh->SizeOfRawData +
                                   bad};
            });
    }
}

PeMemory::PeMemory(vp bin) : PE::PE(bin)
{

    // First initialize the Sections field.

    if (is32bit) {
        Sections = LoadSecs<IMAGE_NT_HEADERS32>(
            this, [](IMAGE_SECTION_HEADER* sh, st bad) {
                return ExecSec{sh->VirtualAddress,
                               sh->VirtualAddress + sh->Misc.VirtualSize,
                               sh->VirtualAddress,
                               sh->VirtualAddress + sh->SizeOfRawData};
            });
    }
    else {
        Sections = LoadSecs<IMAGE_NT_HEADERS64>(
            this, [](IMAGE_SECTION_HEADER* sh, st bad) {
                return ExecSec{sh->VirtualAddress,
                               sh->VirtualAddress + sh->Misc.VirtualSize + bad,
                               sh->VirtualAddress,
                               sh->VirtualAddress + sh->SizeOfRawData + bad};
            });
    }
}

st PeFile::VTO(st addr)
{
    for (ExecSec sec : Sections) {
        if (sec.vstart <= addr && addr <= sec.vend) {
            return addr - sec.vstart + sec.start;
        }
    }
}

st PeFile::OTV(st addr)
{
    for (ExecSec sec : Sections) {
        if (sec.start <= addr && addr <= sec.end) {
            return addr + sec.vstart - sec.start;
        }
    }
}