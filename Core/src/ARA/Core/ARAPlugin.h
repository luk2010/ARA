//
//  ARAPlugin.h
//  ARA
//
//  Created by jacques tronconi on 26/11/2023.
//

#ifndef ARAPlugin_h
#define ARAPlugin_h

#include "ARADynLib.h"

ARA_BEGIN_NAMESPACE

//! @brief
//! An Error launched by a Plugin.
//!
ARA_DECLARE_ERROR(PluginError)

//! @brief
//! The install or the uninstall function has not been found.
//!
ARA_DECLARE_ERROR(PluginPfnNotFound)

//! @brief
//! The `install` method definition.
//!
typedef bool (*PluginInstallPfn) ();

//! @brief
//! The `uninstall` method definition.
//!
typedef void (*PluginUninstallPfn) ();

//! @brief
//! A Class that uses a DynLib object to load a plugin.
//!
//! A Plugin must have two functions: install() and uninstall. The functions names are
//! defined into `ARAPlatform.h`.
//!
class Plugin
{
    //! @brief
    //! The dynamic library object.
    //!
    Ptr<DynLib> mDynLib;
    
    //! @brief
    //! The `install` function.
    //!
    PluginInstallPfn mInstallPfn;
    
    //! @brief
    //! The `uninstall` function.
    //!
    PluginUninstallPfn mUninstallPfn;
    
    //! @brief
    //! A boolean true if the Plugin has been installed successfully.
    //!
    bool mInstalled;
    
public:
    
    //! @brief
    //! Constructs a new Plugin.
    //!
    //! @param filePath
    //!     The path to the plugin library.
    //! @param autoinstall
    //!     Call `install()` directly after loading the library.
    //!
    Plugin(const std::string& filePath, bool autoinstall = false);
    
    //! @brief
    //! Destroys the Plugin and uninstall it if it was installed.
    //!
    ~Plugin();
    
    //! @brief
    //! Returns the dynamic library file path.
    //!
    const std::string& filePath() const;
    
    //! @brief
    //! Installs the Plugin.
    //!
    bool install();
    
    //! @brief
    //! Uninstall the Plugin.
    //!
    void uninstall();
};

typedef Ptr < Plugin > PluginPtr;

ARA_END_NAMESPACE

#endif /* ARAPlugin_h */
