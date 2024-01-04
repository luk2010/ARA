////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     DeviceMTL/RenderEncoderMTL.mm
//! @date
//!     2024/01/04
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "RenderEncoderMTL.h"

RenderEncoderMTL::RenderEncoderMTL(ARA::Hri::RenderDevice& device, const ARA::Hri::RenderPass& renderPass, id < MTLRenderCommandEncoder > handle):
ARA::Hri::RenderEncoder(device, renderPass), mHandle(handle)
{
    
}

id < MTLRenderCommandEncoder > RenderEncoderMTL::handle() const
{
    return mHandle;
}

void RenderEncoderMTL::end()
{
    [mHandle endEncoding];
}
