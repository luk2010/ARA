////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     DeviceMTL/GPUBufferMTL.mm
//! @date
//!     2024/01/02
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "GPUBufferMTL.h"

GPUBufferMTL::GPUBufferMTL(ARA::Hri::RenderDevice& device, id<MTLBuffer> handle):
ARA::Hri::GPUBuffer(device), mHandle(handle)
{
    
}

id<MTLBuffer> GPUBufferMTL::handle() const
{
    return mHandle;
}

size_t GPUBufferMTL::length() const
{
    return mHandle.length;
}

void GPUBufferMTL::read(std::function<void (const void *)> fun) const
{
    fun([mHandle contents]);
}

void GPUBufferMTL::write(std::function<bool (void *)> fun)
{
    if (fun([mHandle contents]))
        [mHandle didModifyRange:NSMakeRange(0, mHandle.length)];
}
