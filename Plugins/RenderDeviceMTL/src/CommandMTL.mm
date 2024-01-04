////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     DeviceMTL/CommandMTL.mm
//! @date
//!     2024/01/04
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "CommandMTL.h"
#include "RenderPass.h"
#include "RenderEncoderMTL.h"

CommandMTL::CommandMTL(ARA::Hri::RenderDevice& device, id < MTLCommandBuffer > handle):
ARA::Hri::Command(device), mHandle(handle)
{
    
}

id < MTLCommandBuffer > CommandMTL::handle() const
{
    return mHandle;
}

ARA::Hri::RenderEncoderPtr CommandMTL::newRenderEncoder(const ARA::Hri::RenderPass& renderPass)
{
    MTLRenderPassDescriptor* descriptor = RenderPassToMTL(renderPass);
    
    if (!descriptor)
        return nullptr;
    
    id < MTLRenderCommandEncoder > encoder = [mHandle renderCommandEncoderWithDescriptor:descriptor];
    
    if (!encoder)
        return nullptr;
    
    return ARA::MakePtr < RenderEncoderMTL >(device(), renderPass, encoder);
}

void CommandMTL::commit()
{
    [mHandle commit];
}
