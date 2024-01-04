////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Hri/RenderDevice.cpp
//! @date
//!     2024/01/01
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ARA/Hri/RenderDevice.h"

$ns(ARA, Hri)
{
    RenderPass RenderDevice::newRenderPass(const RenderViewDrawablePtr& drawable)
    {
        return newRenderPassWithDrawable(drawable->handle());
    }
}
