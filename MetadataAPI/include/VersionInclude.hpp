#pragma once

#ifndef MAPI_MVER
#pragma error Metadata version not given !
#endif

#define STRINGIFY(x) #x
#define IL2CPP_INCLUDE(ver,h) STRINGIFY(ver/h)


#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/il2cpp-class-internals.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/il2cpp-api.h)

