////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Hri/GPUBuffer.h
//! @date
//!     2024/01/02
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_HRI_GPUBUFFER_H__
#define __ARA_HRI_GPUBUFFER_H__

#include "ARA/Hri/GPUResource.h"

ARA_HRI_BEGIN_NS

//! @brief 
//! A continuous block of arbitrary data stored on the GPU memory.
//! 
class GPUBuffer : public GPUResource 
{
public: 

    //! @brief 
    //! Creates a new GPUBuffer instance. 
    //! 
    GPUBuffer(RenderDevice& device);

    //! @brief 
    //! Returns the buffer size in bytes.
    //! 
    virtual size_t length() const = 0;

    //! @brief 
    //! Executes the given callback by reading the buffer data.
    //! 
    virtual void read(std::function < void(const void*) > fun) const = 0;

    //! @brief 
    //! Executes the given callback allowing writing to the buffer data.
    //! 
    virtual void write(std::function < bool(void*) > fun) = 0;
};

typedef Ptr < GPUBuffer > GPUBufferPtr;

ARA_HRI_END_NS

#endif 