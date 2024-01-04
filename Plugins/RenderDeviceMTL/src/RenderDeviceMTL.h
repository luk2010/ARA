////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     DeviceMTL/RenderDeviceMTL.h
//! @date
//!     2024/01/02
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __DEVICEMTL_RENDERDEVICEMTL_H__
#define __DEVICEMTL_RENDERDEVICEMTL_H__

#include "Platform.h"
#include "ARA/Hri/RenderDevice.h"

//! @brief
//! A RenderDevice implemented for Metal.
//!
class RenderDeviceMTL : public ARA::Hri::RenderDevice
{
    //! @brief
    //! The Metal device.
    //!
    id<MTLDevice> mDevice;
    
public:
    
    //! @brief
    //! Creates a new device instance.
    //!
    RenderDeviceMTL();
    
    //! @brief
    //! Returns the device's name.
    //!
    std::string name() const; 
    
    //! @brief
    //! Creates a new GPUBuffer.
    //!
    ARA::Hri::GPUBufferPtr newBuffer(size_t length, const void* data);
    
    //! @brief
    //! Creates a new Texture.
    //!
    ARA::Hri::GPUTexturePtr newTexture(ARA::Hri::GPUTextureType type, 
                                       const ARA::Region3u& region,
                                       ARA::PixelFormat texPixelFormat,
                                       size_t numLayers,
                                       size_t numMipMapLevels,
                                       const ARA::ByteArray& src,
                                       const ARA::ImageData& srcDescriptor);
    
    //! @brief
    //! Creates a RenderPass suitable to draw into the given NativeDrawable.
    //!
    ARA::Hri::RenderPass newRenderPassWithDrawable(ARA::NativeDrawable drawable);
    
    //! @brief
    //! Creates a new CommandQueue.
    //!
    ARA::Hri::CommandQueuePtr newCommandQueue();
    
    //! @brief
    //! Returns the maximum number of color attachments.
    //!
    size_t maxNumberOfColorAttachments() const;
};

#endif
