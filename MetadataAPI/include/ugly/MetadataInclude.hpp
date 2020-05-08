// clang-format off
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

#if MAPI_MVER > 22
// Not sure if its this ver specifically
#endif


#define ImLazy
#ifndef ImLazy

#if MAPI_MVER > 23
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-api.h)

#if MAPI_MVER == 24

#if MAPI_REV > 0
//#pragma error MAPI_VER(MAPI_MVER, MAPI_REV)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/os/c-api/WaitStatus-c-api.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-class-internals.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-tabledefs.h)
#else
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/class-internals.h)
#endif
#else
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-class-internals.h)
#endif

// Deps maybe required?
#include <stdint.h>
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/NonCopyable.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/os/ErrorCodes.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/os/WaitStatus.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/os/Handle.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-config.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/Assembly.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/Il2CppTypeVector.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/dynamic_array.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/os/Mutex.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-metadata.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/MetadataCache.h)
#ifdef INCLUDE_STATICS
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/MetadataCache.cpp)
#endif

#else


#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/utils/NonCopyable.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/os/ErrorCodes.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/os/WaitStatus.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/os/Handle.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/os/Mutex.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/il2cpp-metadata.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/il2cpp-api.h)
#include <stdint.h>
#include <vector>
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/il2cpp-config.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/vm/Assembly.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/metadata/Il2CppTypeVector.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/metadata.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/class-internals.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/vm/MetadataCache.h)
#ifdef INCLUDE_STATICS
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/vm/MetadataCache.cpp)
#endif

#endif
#endif

#if MAPI_MVER == 23
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <crtdbg.h>
#include <wchar.h>
#include <ctype.h>
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\il2cpp-api-types.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\il2cpp-config.h)
#include <vector>
#include <string>
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\vm\Assembly.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\metadata\Il2CppTypeVector.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\blob.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\il2cpp-metadata.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\metadata.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\class-internals.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\vm\MetadataCache.h)
#include <map>
#include <limits>
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\tabledefs.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\gc\GarbageCollector.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\os\ErrorCodes.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\utils\NonCopyable.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\os\Handle.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\os\WaitStatus.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\os\Mutex.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\metadata\ArrayMetadata.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\metadata\GenericMetadata.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\metadata\GenericMethod.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\utils\KeyWrapper.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\metadata\Il2CppTypeCompare.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\metadata\Il2CppTypeHash.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\metadata\Il2CppGenericContextCompare.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\metadata\Il2CppGenericContextHash.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\metadata\Il2CppGenericInstCompare.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\metadata\Il2CppGenericInstHash.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\metadata\Il2CppGenericMethodCompare.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\metadata\Il2CppGenericMethodHash.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\utils\Memory.h)
#include <algorithm>
#include <memory>
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\utils\dynamic_array.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\metadata\Il2CppSignatureCompare.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\metadata\Il2CppSignatureHash.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\os\Atomic.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\utils\CallOnce.h)
#include <functional>
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\utils\Collections.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\utils\HashUtils.h)
// FUCKING GOOGLES SHIT HERE
#include "external/google/sparsehash/type_traits.h"
#include "external/google/sparsehash/densehashtable.h"
#include "external/google/sparsehash/dense_hash_map.h"
#include "external/google/sparsehash/dense_hash_set.h"
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\utils\Il2CppHashMap.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\utils\Il2CppHashSet.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\object-internals.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\utils\StringView.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\vm\Exception.h)
#include <list>
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\vm\Type.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\vm\Class.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\vm\GenericClass.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\vm\MetadataAlloc.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\vm\MetadataLoader.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\vm\MetadataLock.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\vm\Object.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\il2cpp-string-types.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\utils\StringUtils.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\vm\Runtime.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp\vm\String.h)
#endif


#if MAPI_MVER == 23
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <crtdbg.h>
#include <wchar.h>
#include <ctype.h>
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/il2cpp-api-types.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/il2cpp-config.h)
#include <vector>
#include <string>
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/vm/Assembly.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/metadata/Il2CppTypeVector.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/blob.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/il2cpp-metadata.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/metadata.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/class-internals.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/vm/MetadataCache.h)
#include <map>
#include <limits>
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/tabledefs.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/gc/GarbageCollector.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/os/ErrorCodes.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/utils/NonCopyable.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/os/Handle.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/os/WaitStatus.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/os/Mutex.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/metadata/ArrayMetadata.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/metadata/GenericMetadata.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/metadata/GenericMethod.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/utils/KeyWrapper.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/metadata/Il2CppTypeCompare.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/metadata/Il2CppTypeHash.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/metadata/Il2CppGenericContextCompare.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/metadata/Il2CppGenericContextHash.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/metadata/Il2CppGenericInstCompare.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/metadata/Il2CppGenericInstHash.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/metadata/Il2CppGenericMethodCompare.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/metadata/Il2CppGenericMethodHash.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/utils/Memory.h)
#include <algorithm>
#include <memory>
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/utils/dynamic_array.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/metadata/Il2CppSignatureCompare.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/metadata/Il2CppSignatureHash.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/os/Atomic.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/utils/CallOnce.h)
#include <functional>
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/utils/Collections.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/utils/HashUtils.h)
#include "external/google/sparsehash/type_traits.h"
#include "external/google/sparsehash/densehashtable.h"
#include "external/google/sparsehash/dense_hash_map.h"
#include "external/google/sparsehash/dense_hash_set.h"
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/utils/Il2CppHashMap.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/utils/Il2CppHashSet.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/object-internals.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/utils/StringView.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/vm/Exception.h)
#include <list>
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/vm/Type.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/vm/Class.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/vm/GenericClass.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/vm/MetadataAlloc.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/vm/MetadataLoader.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/vm/MetadataLock.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/vm/Object.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/il2cpp-string-types.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/utils/StringUtils.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/vm/Runtime.h)
#include IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/vm/String.h)
#endif





#if MAPI_MVER == 24
#define MetadataCacheInclude IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/MetadataCache.cpp)
#else
#define MetadataCacheInclude IL2CPP_INCLUDE(MAPI_MVER, libil2cpp/vm/MetadataCache.cpp)
#endif





#if MAPI_MVER == 24
#if MAPI_REV == 0
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <crtdbg.h>
#include <wchar.h>
#include <ctype.h>
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-api-types.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-config.h)
#include <vector>
#include <string>
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/Assembly.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/Il2CppTypeVector.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/blob.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-metadata.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/mono-runtime/il2cpp-mapping.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/class-internals.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/MetadataCache.h)
#include <map>
#include <limits>
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/tabledefs.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/gc/GarbageCollector.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/os/ErrorCodes.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/NonCopyable.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/os/Handle.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/os/WaitStatus.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/os/Mutex.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/ArrayMetadata.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/GenericMetadata.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/GenericMethod.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/KeyWrapper.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/Il2CppTypeCompare.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/Il2CppTypeHash.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/Il2CppGenericContextCompare.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/Il2CppGenericContextHash.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/Il2CppGenericInstCompare.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/Il2CppGenericInstHash.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/Il2CppGenericMethodCompare.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/Il2CppGenericMethodHash.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/Memory.h)
#include <algorithm>
#include <memory>
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/dynamic_array.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/Il2CppSignatureCompare.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/Il2CppSignatureHash.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/os/Atomic.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/CallOnce.h)
#include <functional>
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/Collections.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/HashUtils.h)
#include "external/google/sparsehash/type_traits.h"
#include "external/google/sparsehash/densehashtable.h"
#include "external/google/sparsehash/dense_hash_map.h"
#include "external/google/sparsehash/dense_hash_set.h"
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/Il2CppHashMap.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/Il2CppHashSet.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-string-types.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/StringUtils.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/object-internals.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/StringView.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/Exception.h)
#include <list>
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/Type.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/Class.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/GenericClass.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/MetadataAlloc.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/MetadataLoader.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/MetadataLock.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/Object.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/String.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/mono-runtime/il2cpp-mono-support.h)
#include <cassert>
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/StackTrace.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-vm-support.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm-utils/NativeSymbol.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm-utils/VmStringUtils.h)
#endif
#endif




#if MAPI_MVER == 24
#if MAPI_REV == 1
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <crtdbg.h>
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/os/c-api/il2cpp-config-platforms.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/os/c-api/il2cpp-config-api-platforms.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-api-types.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-config-api.h)
#include <wchar.h>
#include <ctype.h>
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-config.h)
#include <vector>
#include <string>
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/Assembly.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/Il2CppTypeVector.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-blob.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-metadata.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-runtime-metadata.h)
#include <mono/metadata/metadata.h>
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/mono-runtime/il2cpp-mapping.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-class-internals.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/Memory.h)
#include <algorithm>
#include <memory>
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/dynamic_array.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/os/ErrorCodes.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/NonCopyable.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/os/c-api/WaitStatus-c-api.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/os/WaitStatus.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/os/Handle.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/os/Mutex.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/MetadataCache.h)
#include <map>
#include <limits>
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-tabledefs.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/gc/GarbageCollector.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/ArrayMetadata.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/GenericMetadata.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/GenericMethod.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/KeyWrapper.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/Il2CppTypeCompare.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/Il2CppTypeHash.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/Il2CppGenericContextCompare.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/Il2CppGenericContextHash.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/Il2CppGenericInstCompare.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/Il2CppGenericInstHash.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/Il2CppGenericMethodCompare.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/Il2CppGenericMethodHash.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/Il2CppSignatureCompare.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/Il2CppSignatureHash.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/os/c-api/Atomic-c-api.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/os/Atomic.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/CallOnce.h)
#include <functional>
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/Collections.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/HashUtils.h)
#include "external/google/sparsehash/type_traits.h"
#include "external/google/sparsehash/densehashtable.h"
#include "external/google/sparsehash/dense_hash_map.h"
#include "external/google/sparsehash/dense_hash_set.h"
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/Il2CppHashMap.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/Il2CppHashSet.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-string-types.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/StringView.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/StringUtils.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/PathUtils.h)
#include <mono/metadata/object.h>
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-object-internals.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/Exception.h)
#include <list>
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/Type.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/Class.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/GenericClass.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/MetadataAlloc.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/MetadataLoader.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/MetadataLock.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/Method.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/Object.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/String.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/mono-runtime/il2cpp-mono-support.h)
#include <cassert>
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/StackTrace.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/Profiler.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-vm-support.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm-utils/NativeSymbol.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm-utils/VmStringUtils.h)
#endif
#endif




#if MAPI_MVER == 24
#if MAPI_REV == 2
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/os/c-api/il2cpp-config-platforms.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/os/c-api/il2cpp-config-api-platforms.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-api-types.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-config-api.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-sanitizers.h)
#include <wchar.h>
#include <ctype.h>
//#include <emscripten/emscripten.h>
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-config.h)
#include <vector>
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/Assembly.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/Il2CppTypeVector.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-blob.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-tokentype.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-metadata.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-runtime-metadata.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-windowsruntime-types.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/mono-runtime/il2cpp-mapping.h)
#include <limits.h>
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/StringView.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-pinvoke-support.h)
//#include <mono/metadata/metadata.h>
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-class-internals.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/Memory.h)
#include <algorithm>
#include <memory>
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/dynamic_array.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/os/ErrorCodes.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/NonCopyable.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/os/c-api/WaitStatus-c-api.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/os/WaitStatus.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/os/Handle.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/os/Mutex.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/MetadataCache.h)
#include <map>
#include <limits>
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-tabledefs.h)
#include <atomic>
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-runtime-stats.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/gc/GarbageCollector.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/ArrayMetadata.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/GenericMetadata.h)
#include <string>
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/GenericMethod.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/KeyWrapper.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/Il2CppTypeCompare.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/Il2CppTypeHash.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/Il2CppGenericContextCompare.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/Il2CppGenericContextHash.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/Il2CppGenericInstCompare.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/Il2CppGenericInstHash.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/Il2CppGenericMethodCompare.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/Il2CppGenericMethodHash.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/Il2CppSignatureCompare.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/metadata/Il2CppSignatureHash.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/os/c-api/Atomic-c-api.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/os/Atomic.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/CallOnce.h)
#include <functional>
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/Collections.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/HashUtils.h)
#include "external/google/sparsehash/type_traits.h"
#include "external/google/sparsehash/densehashtable.h"
#include "external/google/sparsehash/dense_hash_map.h"
#include "external/google/sparsehash/dense_hash_set.h"
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/Il2CppHashMap.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/Il2CppHashSet.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-string-types.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/StringViewUtils.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/StringUtils.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/utils/PathUtils.h)
//#include <mono/metadata/object.h>
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-object-internals.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/Exception.h)
#include <list>
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/Type.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/Class.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/ClassInlines.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/GenericClass.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/MetadataAlloc.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/MetadataLoader.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/MetadataLock.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/Method.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/Object.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/String.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/mono-runtime/il2cpp-mono-support.h)
#include <cassert>
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/StackTrace.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm/Profiler.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/il2cpp-vm-support.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm-utils/NativeSymbol.h)
#include IL2CPP_INCLUDE(MAPI_MVER.MAPI_REV, libil2cpp/vm-utils/VmStringUtils.h)
#endif
#endif