////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     DeviceMTL/Plugin.mm
//! @date
//!     2024/01/02
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "RenderDeviceMTL.h"

extern "C" bool PluginInstall()
{
    ARA::Hri::RenderDeviceFactory::Get().add("DeviceMTL", []()
    {
        return ARA::MakePtr < RenderDeviceMTL >();
    });
    
    return true;
}

extern "C" void PluginUninstall()
{
    ARA::Hri::RenderDeviceFactory::Get().remove("DeviceMTL");
}
