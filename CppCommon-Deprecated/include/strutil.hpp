#pragma once
#include "core.hpp"
#include <locale>
#include <codecvt>
#include <string>

// Narrow to wide
std::wstring n2w(std::string str) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wide = converter.from_bytes(str);
    return wide;
}
