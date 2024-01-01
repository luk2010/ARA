////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Core/Plugin.cpp
//! @date
//!     2024/01/01
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ARA/Core/ARAPlugin.h"

ARA_BEGIN_NAMESPACE

Plugin::Plugin(const std::string& filePath, bool autoinstall)
{
    mDynLib = MakePtr < DynLib >(filePath);
    mInstalled = false;
    mInstallPfn = (PluginInstallPfn) mDynLib->find(ARA_PLUGIN_INSTALL_PFN_NAME);
    mUninstallPfn = (PluginUninstallPfn) mDynLib->find(ARA_PLUGIN_UNINSTALL_PFN_NAME);
    
    if (!mInstallPfn || !mUninstallPfn)
        throw PluginPfnNotFound("ARA::Plugin: install() or uninstall() methods not found.");
    
    if (autoinstall)
        if (!install())
            throw PluginError("ARA::Plugin: install() failed.");
}

Plugin::~Plugin()
{
    uninstall();
}

const std::string& Plugin::filePath() const
{
    return mDynLib->filePath();
}

bool Plugin::install()
{
    if (!mInstalled)
        mInstalled = mInstallPfn();
    
    return mInstalled;
}

void Plugin::uninstall()
{
    if (mInstalled)
    {
        mUninstallPfn();
        mInstalled = false;
    }
}

ARA_END_NAMESPACE
