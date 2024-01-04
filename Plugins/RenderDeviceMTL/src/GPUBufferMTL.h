////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     DeviceMTL/GPUBufferMTL.h
//! @date
//!     2024/01/02
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __DEVICEMTL_GPUBUFFERMTL_H__
#define __DEVICEMTL_GPUBUFFERMTL_H__

#include "Platform.h"
#include "ARA/Hri/GPUBuffer.h"

//! @brief
//! A GPU Buffer with Metal.
//!
class GPUBufferMTL : public ARA::Hri::GPUBuffer
{
    //! @brief
    //! The MTLBuffer handle.
    //!
    id<MTLBuffer> mHandle;
    
public:
    
    //! @brief
    //! Creates a new GPU Buffer.
    //!
    GPUBufferMTL(ARA::Hri::RenderDevice& device, id<MTLBuffer> handle);
    
    //! @brief
    //! Returns the handle.
    //!
    id<MTLBuffer> handle() const;
    
    //! @brief
    //! Returns the buffer size in bytes.
    //!
    virtual size_t length() const;
    
    //! @brief
    //! Executes the given callback by reading the buffer data.
    //!
    virtual void read(std::function < void(const void*) > fun) const;
    
    //! @brief
    //! Executes the given callback allowing writing to the buffer data.
    //!
    virtual void write(std::function < bool(void*) > fun);
};

#endif
