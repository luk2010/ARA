////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Core/PluginManager.cpp
//! @date
//!     2024/01/02
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ARA/Core/PluginManager.h"

ARA_BEGIN_NAMESPACE

PluginManager::PluginManager()
{
    mSearchDirectories.push_back(ARAGetCurrentWorkingDir());
    mSearchDirectories.push_back(ARAGetExecutablePath().parent_path());
}

PluginManager& PluginManager::Get()
{
    static PluginManager instance;
    return instance;
}

void PluginManager::addSearchDirectory(const std::string& filePath)
{
    mSearchDirectories.push_back(filePath);
}

void PluginManager::removeSearchDirectory(const std::string& filePath)
{
    auto it = std::find(mSearchDirectories.begin(), mSearchDirectories.end(), filePath);
    
    if (it != mSearchDirectories.end())
        mSearchDirectories.erase(it);
}

const std::vector < std::string >& PluginManager::searchDirectories() const
{
    return mSearchDirectories;
}

Plugin& PluginManager::loadOrFind(const std::string& fileName, bool autoinstall)
{
    std::filesystem::path fileNamePath = std::filesystem::path(fileName).replace_extension(ARA_DYNLIB_EXT);
    
    for (auto& plugin : mPlugins)
        if (plugin->filePath() == fileNamePath)
            return *plugin;
    
    std::filesystem::path filePath;
    
    for (auto& searchDir : mSearchDirectories)
    {
        filePath = std::filesystem::path(searchDir) / fileNamePath;
        
        if (std::filesystem::exists(filePath))
        {
            PluginPtr plugin = MakePtr < Plugin >(filePath.string(), autoinstall);
            
            mPlugins.push_back(plugin);
            
            return *plugin;
        }
    }
    
    throw PluginNotFound("ARA::PluginManager: Plugin '", fileNamePath, "' not found.");
}

Plugin& PluginManager::find(const std::string& fileName) const
{
    std::filesystem::path fileNamePath = std::filesystem::path(fileName).replace_extension(ARA_DYNLIB_EXT);
    
    for (auto& plugin : mPlugins)
        if (plugin->filePath() == fileNamePath)
            return *plugin;
    
    throw PluginNotFound("ARA::PluginManager: Plugin '", fileNamePath, "' not found.");
}

void PluginManager::remove(const std::string& fileName)
{
    std::filesystem::path fileNamePath = std::filesystem::path(fileName).replace_extension(ARA_DYNLIB_EXT);
    
    auto it = std::find_if(mPlugins.begin(), mPlugins.end(), [&](const PluginPtr& plugin)
    {
        return fileNamePath == plugin->filePath();
    });
    
    if (it != mPlugins.end())
        mPlugins.erase(it);
}

void PluginManager::clear()
{
    mSearchDirectories.clear();
    mPlugins.clear();
}

ARA_END_NAMESPACE
