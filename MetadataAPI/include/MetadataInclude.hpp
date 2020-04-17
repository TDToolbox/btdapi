#pragma once
//
// This file is preprocessor voodoo for including metadata headers in extern
// into all of the /vers/ metadata classes.
//

#ifndef MAPI_MVER
#ifndef MAPI_MVER_LATEST
#pragma error Metadata version not given !
#endif
#endif

#if (MAP_MVER > 23)
#ifndef(MAPI_REV)
#pragma error Revision not set!
#endif
#endif

#define STRINGIFY(x) #x
#define IL2CPP_INCLUDE(ver,h) STRINGIFY(ver/h)

#ifdef MAPI_MVER_LATEST
#ifdef MAPI_MVER
#undef MAPI_MVER
#endif

#ifdef MAPI_REV
#undef MAPI_REV
#endif 

#define MAPI_MVER 24
#define MAPI_REV 2
#endif



#if MAPI_MVER > 23
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-api.h)
#if MAPI_MVER == 24

#if MAPI_REV > 0
#pragma error MAPI_VER(MAPI_MVER, MAPI_REV)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-class-internals.h)
#else
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/class-internals.h)
#endif
#else
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-class-internals.h)
#endif
#else
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/class-internals.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/il2cpp-api.h)
#endif




