#pragma once
#include "core.hpp"
#include <locale>
#include <codecvt>
#include <string>

// Narrow string to wide string
std::wstring n2w(std::string str);

// Calculate number of bytes wstring occupies
st wstringBytes(std::wstring str);