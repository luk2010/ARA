//
//  ARADynLib.cpp
//  lui
//
//  Created by jacques tronconi on 26/11/2023.
//

#include "ARADynLib.h"

ARA_BEGIN_NAMESPACE

DynLib::DynLib(const std::string& filePath)
{
    std::filesystem::path path = std::filesystem::path(filePath).replace_extension(ARA_DYNLIB_EXT);
    
    if (!std::filesystem::exists(path))
        throw DynLibError("[ARA::DynLib] FilePath '", path, "' doesn't exists.");
    
    mHandle = ARA_DYNLIB_OPEN(path.c_str());
    
    if (!mHandle)
        throw DynLibError("[ARA::DynLib] ARA_DYNLIB_OPEN() failed with file path '", path, "'");
    
    mFilePath = path.string();
}

ARA_END_NAMESPACE
