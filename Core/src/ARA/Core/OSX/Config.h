////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Core/OSX/Config.h
//! @date
//!     2024/01/01
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_CORE_OSX_CONFIG_H__
#define __ARA_CORE_OSX_CONFIG_H__

#include <libgen.h>
#include <limits.h>
#include <mach-o/dyld.h>
#include <unistd.h>

inline std::filesystem::path ARAGetExecutablePath()
{
    char rawPathName[PATH_MAX];
    char realPathName[PATH_MAX];
    uint32_t rawPathSize = (uint32_t)sizeof(rawPathName);

    if (!_NSGetExecutablePath(rawPathName, &rawPathSize))
        realpath(rawPathName, realPathName);
    
    return std::string(realPathName);
}

inline std::filesystem::path ARAGetCurrentWorkingDir()
{
    char rawPathName[PATH_MAX];
    char realPathName[PATH_MAX];
    uint32_t rawPathSize = (uint32_t)sizeof(rawPathName);
    
    if (getcwd(rawPathName, PATH_MAX) == NULL)
        throw std::runtime_error("getcwd() failed.");
    
    realpath(rawPathName, realPathName);
    return std::string(realPathName);
}

#endif 
