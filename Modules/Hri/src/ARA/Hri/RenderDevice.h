////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Hri/RenderDevice.h
//! @date
//!     2024/01/01
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_HRI_RENDERDEVICE_H__
#define __ARA_HRI_RENDERDEVICE_H__

#include "ARA/Core/Factory.h"
#include "ARA/Core/Region.h"
#include "ARA/Core/RenderView.h"

#include "ARA/Hri/Platform.h"
#include "ARA/Hri/GPUBuffer.h"
#include "ARA/Hri/GPUTexture.h"
#include "ARA/Hri/CommandQueue.h"

ARA_HRI_BEGIN_NS

//! @brief
//! An interface that defines a rendering device.
//!
class RenderDevice
{
public:
    
    //! @brief
    //! Virtual destructor.
    //!
    virtual ~RenderDevice() = default;
    
    //! @brief
    //! Returns the device's name.
    //!
    virtual std::string name() const = 0;

    //! @brief 
    //! Creates a new GPUBuffer.
    //! 
    virtual GPUBufferPtr newBuffer(size_t length, const void* data = NULL) = 0;
    
    //! @brief
    //! Creates a new Texture.
    //!
    virtual GPUTexturePtr newTexture(GPUTextureType type, 
                                     const Region3u& region,
                                     PixelFormat texPixelFormat,
                                     size_t numLayers,
                                     size_t numMipMapLevels,
                                     const ByteArray& src,
                                     const ImageData& srcDescriptor) = 0;
    
    //! @brief
    //! Creates a RenderPass suitable to draw into the given NativeDrawable.
    //!
    virtual RenderPass newRenderPassWithDrawable(NativeDrawable drawable) = 0;
    
    //! @brief
    //! Creates a RenderPass with the given RenderViewDrawable.
    //!
    virtual RenderPass newRenderPass(const RenderViewDrawablePtr& drawable);
    
    //! @brief
    //! Creates a new CommandQueue.
    //!
    virtual CommandQueuePtr newCommandQueue() = 0;
    
    //! @brief
    //! Returns the maximum number of color attachments.
    //!
    virtual size_t maxNumberOfColorAttachments() const = 0;
};

typedef Ptr < RenderDevice > RenderDevicePtr;
typedef std::function < RenderDevicePtr () > RenderDeviceConstructor;
typedef SingleFactory < std::string, RenderDeviceConstructor > RenderDeviceFactory;

ARA_HRI_END_NS

#endif 
