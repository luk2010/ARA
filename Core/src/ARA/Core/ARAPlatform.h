//
//  ARAPlatform.h
//  ARA
//
//  Created by jacques tronconi on 26/11/2023.
//

#ifndef ARAPlatform_h
#define ARAPlatform_h

#include <iostream>
#include <functional>
#include <any>
#include <map>
#include <vector>
#include <string>
#include <filesystem>
#include <exception>
#include <sstream>
#include <optional>
#include <variant>
#include <array>
#include <string_view>
#include <atomic>
#include <future>

#if defined(__APPLE__)

#   include <TargetConditionals.h>
#   include <CoreFoundation/CoreFoundation.h>
#   include <CoreGraphics/CoreGraphics.h>
#   include <objc/objc-runtime.h>
#   include <dlfcn.h>

#   define ARA_PLATFORM_APPLE   1
#   define ARA_PLATFORM_WINDOWS 0
#   define ARA_PLATFORM_LINUX   0

#   if TARGET_OS_OSX
#   define ARA_PLATFORM_OSX     1
#   define ARA_PLATFORM_IPHONE  0
#   elif TARGET_OS_IPHONE
#   define ARA_PLATFORM_OSX     0
#   define ARA_PLATFORM_IPHONE  1
#   endif

#   define ARA_PLATFORM_NAME "APPLE"
#   define ARA_PLATFORM_REAL_T CGFloat
#   define ARA_PLATFORM_DEFAULT_PLUGIN_NAME "libARACocoa.dylib"

#   define ARA_DYNLIB_T void*
#   define ARA_DYNLIB_OPEN(a) dlopen(a, RTLD_LAZY)
#   define ARA_DYNLIB_CLOSE(a) dlclose(a)
#   define ARA_DYNLIB_DLSYM(a, b) dlsym(a, b)
#   define ARA_DYNLIB_EXT ".dylib"

#endif

#if ARA_PLATFORM_OSX
#include "OSX/Config.h"
#endif 

//! @brief
//! A macro used to begin the ARA namespace.
#define ARA_BEGIN_NAMESPACE namespace ARA {

//! @brief
//! A macro used to end the ARA namespace.
#define ARA_END_NAMESPACE }

//! @brief
//! The name of the function a Plugin shall declare to be read by ARA::Plugin.
//!
//! @deprecated
//!
#define ARA_PLUGIN_LOAD_PFN_NAME "PluginLoad"

//! @brief
//! The name of the Plugin install function.
//!
#define ARA_PLUGIN_INSTALL_PFN_NAME "PluginInstall"

//! @brief
//! The name of the Plugin uninstall function.
//!
#define ARA_PLUGIN_UNINSTALL_PFN_NAME "PluginUninstall"

ARA_BEGIN_NAMESPACE

typedef int32_t Char32;
typedef size_t GlyphIndex;

using Real = ARA_PLATFORM_REAL_T;
using AtomBool = std::atomic < bool >;
using Byte = uint8_t;
using ByteArray = std::vector < Byte >;

constexpr auto InvalidIndex = std::string::npos;

template < class T > using Ptr = std::shared_ptr<T>;
template < class T > using Weak = std::weak_ptr<T>;

//! @brief
//! Creates a new Ptr object.
template < class T, class... Params >
inline auto MakePtr(Params&&... params)
{
    return std::make_shared<T>(std::forward<Params>(params)...);
}

//! @brief
//! Returns true if two constant strings are equal.
constexpr bool AreEqual(char const* a, char const* b)
{
    return std::string_view(a) == b;
}

//! @brief
//! A template class that can have a value, or not. Similar to std::optional.
//!
template < class T >
class Maybe
{
    std::optional < T > mValue;
    
public:
    
    Maybe(): mValue(std::nullopt) {}
    Maybe(const T& value): mValue(value) {}
    
    bool hasValue() const { return mValue.has_value(); }
    operator bool() const { return hasValue(); }
    
    T& value() { return mValue.value(); }
    const T& value() const { return mValue.value(); }
};

ARA_END_NAMESPACE

#endif /* ARAPlatform_h */
