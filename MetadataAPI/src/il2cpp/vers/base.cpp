#include "il2cpp/base.hpp"

#define MAPI_MVER 15
#include "MetadataInclude.hpp"
#undef MAPI_VER

#include "g3log/g3log.hpp"

const auto Il2cppSanity = 0xFAB11BAF;

int32_t Il2CppDumper::FindVersion()
{
    m_hdr = (Il2CppGlobalMetadataHeader*)m_metadata;

    if (m_hdr->sanity != Il2cppSanity) {
        LOG(FATAL) << "Invalid metadata file provided!";
    }

    if (m_hdr->version <= 15 || m_hdr->version >= 30) {
        LOG(FATAL) << "Invalid version";
    }

    if (m_hdr->version == 24) {
        if (m_hdr->stringLiteralOffset == 0x108) {
            return 242;
        }
        else {
            return 241;
        }
    }
    else {
        LOG(INFO) << "Metadata version was " << m_hdr->version * 10;
        return m_hdr->version * 10;
    }
}

std::vector<st> Il2CppDumper::FindPtrs(st val)
{
    std::vector<st> vals;

    for (ExecSec sec : m_exe->Sections) {
        std::vector<u8> vec(m_bin + sec.start, m_bin + sec.end);

        std::vector<u8> valb((u8*)(&val), (u8*)(&val) + sizeof(val));
        std::vector<u8>::iterator it = vec.begin();

        for (;;) {

            it = std::search(
                it, vec.end(),
                std::boyer_moore_horspool_searcher(valb.begin(), valb.end()));

            if (it == vec.end()) {
                break;
            }

            vals.push_back(sec.vstart + (it - vec.begin()));

            std::advance(it, 1);
        }
    }

    return vals;
}

std::vector<st> Il2CppDumper::GetPtrs(st val)
{
    std::vector<st> vals;

    for (ExecSec sec : m_exe->Sections) {
        std::vector<u8> vec(m_bin + sec.start, m_bin + sec.end);

        std::vector<u8> valb((u8*)(&val), (u8*)(&val) + sizeof(val));
        std::vector<u8>::iterator it = vec.begin();

        for (;;) {

            it = std::search(
                it, vec.end(),
                std::boyer_moore_horspool_searcher(valb.begin(), valb.end()));

            if (it == vec.end()) {
                break;
            }

            vals.push_back(sec.start + (it - vec.begin()));

            std::advance(it, 1);
        }
    }

    return vals;
}