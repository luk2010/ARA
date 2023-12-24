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

extern "C" ARA::Application* PluginLoad(void)
{
    return new OSXApplication;
}
