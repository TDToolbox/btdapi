#include "core.hpp"
#include "strutil.hpp"

// Narrow string to wide string
std::wstring n2w(std::string str)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wide = converter.from_bytes(str);
    return wide;
}

// Calculate number of bytes wstring occupies
st wstringBytes(std::wstring str)
{
    return str.length() * sizeof(wchar_t) + sizeof(L'\0');
}