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

#if defined(__APPLE__)

#   include <CoreFoundation/CoreFoundation.h>
#   include <CoreGraphics/CoreGraphics.h>
#   include <objc/objc-runtime.h>
#   include <dlfcn.h>

#   define ARA_PLATFORM_NAME "APPLE"
#   define ARA_PLATFORM_REAL_T CGFloat
#   define ARA_PLATFORM_DEFAULT_PLUGIN_NAME "libARACocoa.dylib"

#   define ARA_DYNLIB_T void*
#   define ARA_DYNLIB_OPEN(a) dlopen(a, RTLD_LAZY)
#   define ARA_DYNLIB_CLOSE(a) dlclose(a)
#   define ARA_DYNLIB_DLSYM(a, b) dlsym(a, b)
#   define ARA_DYNLIB_EXT ".dylib"

#endif

//! @brief
//! A macro used to begin the ARA namespace.
#define ARA_BEGIN_NAMESPACE namespace ARA {

//! @brief
//! A macro used to end the ARA namespace.
#define ARA_END_NAMESPACE }

//! @brief
//! The name of the function a Plugin shall declare to be read by ARA::Plugin.
#define ARA_PLUGIN_LOAD_PFN_NAME "PluginLoad"

ARA_BEGIN_NAMESPACE

using Real = ARA_PLATFORM_REAL_T;

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

ARA_END_NAMESPACE

#endif /* ARAPlatform_h */
