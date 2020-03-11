#pragma once
///////////////////////////////////////////////////////////////////////////////
// Purpose: Core file to be included into every source file. Contains various
// typedefs and macros.
//////////////////////////////////////////////////////////////////////////////

#pragma region typedefs

#include <stdint.h>
#include <string>

// Comments are for intellisense

// 8 bit signed integer
typedef int8_t i8;

// 8 bit unsigned integer
typedef uint8_t u8;

// 16 bit signed integer
typedef int16_t i16;

// 16 bit unsigned integer
typedef uint16_t u16;

// 32 bit signed integer
typedef int32_t i32;

// 32 bit unsigned integer
typedef uint32_t u32;

// 64 bit signed integer
typedef int64_t i64;

// 64 bit unsigned integer
typedef uint64_t u64;

// 32 bit floating point
typedef float f32;

// 64 bit floating point
typedef double f64;

// A ufast8 guarantees to be AT LEAST 8 bits, but if its faster to be
// 32 or 64 bits it will chose that instead.

// Minimum of 8 bits signed integer
typedef int_fast8_t if8;

// Minimum of 8 bits unsigned integer
typedef uint_fast8_t uf8;

// Minimum of 16 bits signed integer
typedef int_fast16_t if16;

// Minimum of 16 bits unsigned integer
typedef uint_fast16_t uf16;

// Minimum of 32 bits signed integer
typedef int_fast32_t if32;

// Minimum of 32 bits unsigned integer
typedef uint_fast32_t uf32;

// Minimum of 64 bits signed integer
typedef int_fast64_t if64;

// minimum of 64 bits unsigned integer
typedef uint_fast64_t uf64;

typedef size_t st;

typedef void* vp;

#pragma endregion

#pragma region platforms

#if (_MSC_VER && !defined(__INTEL_COMPILER))

#define COMPILER_MSVC
#define DLL_PUBLIC __declspec(dllexport)
#define DLL_PRIVATE 
#define DLL_IMPORT __declspec(dllimport)

#if defined(_M_AMD64)
#define ARCH_X64
#else
#define ARCH_X86
#endif

#elif defined(__GNUC__)
#if defined(__CLANG__)
#define COMIPLER_CLANG
#else
#define COMPILER_GCC
#endif
//#define DLL_PUBLIC __attribute__((visibility("default")))
//#define DLL_PRIVATE __attribute__((visibility("hidden")))
#define DLL_PUBLIC __attribute__((dllexport))

#if defined(__x86_64__)
#define ARCH_X64
#else
#define ARCH_X86
#endif
#else
#pargma error Unknown compiler !
#error Unknown compiler!
#endif

#if !defined(NDEBUG) || defined(_DEBUG)
#define DEBUG_BUILD
#endif

#pragma endregion
