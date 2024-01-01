////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Cocoa/ARACocoaPlugin.h
//! @date
//!     2023/12/08
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ARA/Core/ARAPlatform.h"
#include "ARA/Core/ARAApplication.h"
#include "ARACocoaApplication.h"

ARA::ApplicationConstructor OSXAppConstructor = []()
{
    return ARA::MakePtr < OSXApplication >();
};

extern "C" bool PluginInstall(void)
{
    ARA::ApplicationFactory::Get().add("OSXApplication", OSXAppConstructor);
    return true;
}

extern "C" void PluginUninstall(void)
{
    ARA::ApplicationFactory::Get().remove("OSXApplication");
}
