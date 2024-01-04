////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Core/PluginManager.h
//! @date
//!     2024/01/02
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_CORE_PLUGINMANAGER_H__
#define __ARA_CORE_PLUGINMANAGER_H__

#include "ARA/Core/ARAPlugin.h"

ARA_BEGIN_NAMESPACE

ARA_DECLARE_ERROR(PluginNotFound)

//! @brief
//! A Singleton Manager that manages all the Plugins loaded by
//! the ARA current instance.
//!
class PluginManager
{
    //! @brief
    //! The Plugins loaded.
    //!
    std::vector < PluginPtr > mPlugins;
    
    //! @brief
    //! The directories pathes where the PluginManager shall search for Plugins.
    //!
    std::vector < std::string > mSearchDirectories;
    
    //! @brief
    //! Constructs the PluginManager instance.
    //!
    PluginManager();
    
public:
    
    //! @brief
    //! Returns the manager's instance.
    //!
    static PluginManager& Get();
    
    //! @brief
    //! Add a directory path where the PluginManager shall search for Plugins.
    //!
    void addSearchDirectory(const std::string& dirPath);
    
    //! @brief
    //! Removes a directory path.
    //!
    void removeSearchDirectory(const std::string& dirPath);
    
    //! @brief
    //! Returns the directories where the PluginManager shall search for Plugins.
    //!
    const std::vector < std::string >& searchDirectories() const;
    
    //! @brief
    //! Loads or return the Plugin with the given filename.
    //!
    Plugin& loadOrFind(const std::string& filePath, bool autoinstall = false);
    
    //! @brief
    //! Return the Plugin with the given filename.
    //!
    Plugin& find(const std::string& filePath) const;
    
    //! @brief
    //! Removes the given Plugin from its filename.
    //!
    void remove(const std::string& filePath);
    
    //! @brief
    //! Clears the manager.
    //!
    void clear();
};

ARA_END_NAMESPACE

#endif 
