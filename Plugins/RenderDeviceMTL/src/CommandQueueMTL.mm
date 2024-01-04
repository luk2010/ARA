////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     DeviceMTL/CommandQueueMTL.mm
//! @date
//!     2024/01/04
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "CommandQueueMTL.h"
#include "CommandMTL.h"

CommandQueueMTL::CommandQueueMTL(ARA::Hri::RenderDevice& device, id < MTLCommandQueue > handle):
ARA::Hri::CommandQueue(device), mHandle(handle)
{
    
}

id < MTLCommandQueue > CommandQueueMTL::handle() const
{
    return mHandle;
}

ARA::Hri::CommandPtr CommandQueueMTL::newCommand()
{
    return ARA::MakePtr < CommandMTL >(device(), [mHandle commandBuffer]);
}
