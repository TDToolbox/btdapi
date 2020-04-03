#pragma once

#ifndef MAPI_MVER
#ifndef MAPI_MVER_LATEST
#pragma error Metadata version not given !
#endif
#endif

#define STRINGIFY(x) #x
#define IL2CPP_INCLUDE(ver,h) STRINGIFY(ver/h)

#ifdef MAPI_MVER_LATEST
#ifdef MAPI_MVER
#undef MAPI_MVER
#endif
#define MAPI_MVER 24.2
#endif
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/class-internals.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/il2cpp-api.h)

