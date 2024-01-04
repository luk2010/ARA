////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Hri/GPUTexture.h
//! @date
//!     2024/01/04
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_HRI_GPUTEXTURE_H__
#define __ARA_HRI_GPUTEXTURE_H__

#include "ARA/Core/PixelFormat.h"
#include "ARA/Core/ARARange.h"
#include "ARA/Core/Region.h"
#include "ARA/Core/ImageData.h"

#include "ARA/Hri/GPUResource.h"
#include "ARA/Hri/GPUTextureType.h"
#include "ARA/Hri/GPUTextureUsage.h"

ARA_HRI_BEGIN_NS

//! @brief 
//! A GPU resource that defines a data used as a texture.
//! 
class GPUTexture : public GPUResource 
{
protected:

    //! @brief 
    //! Internal constructor.
    //! 
    GPUTexture(RenderDevice& device);

public:
    
    //! @brief
    //! Returns the texture type.
    //!
    virtual GPUTextureType type() const = 0;
    
    //! @brief
    //! Returns the texture internal pixel format.
    //!
    virtual PixelFormat pixelFormat() const = 0;

    //! @brief 
    //! Returns the texture width, in pixels.
    //! 
    virtual size_t width() const = 0;

    //! @brief 
    //! Returns the texture height, in pixels.
    //! 
    virtual size_t height() const = 0;

    //! @brief 
    //! Returns the texture depth, in pixels.
    //! 
    virtual size_t depth() const = 0;

    //! @brief
    //! The number of layers in an array texture.
    //!
    virtual size_t arrayLength() const = 0;
    
    //! @brief
    //! The number of mipmap levels.
    //!
    virtual size_t mipmapLevels() const = 0;
    
    //! @brief
    //! The number of samples for a multisample texture.
    //!
    virtual size_t samplesCount() const = 0;
    
    //! @brief
    //! The current texture usages.
    //!
    virtual GPUTextureUsage usage() const = 0;
    
    //! @brief
    //! Creates a new view of the texture, reinterpreting a subset of its data using a different
    //! type, and pixel format.
    //!
    virtual Ptr < GPUTexture > newView(PixelFormat pixelFormat,
                                       GPUTextureType textureType,
                                       const Range& mipmapLevels = Range(),
                                       const Range& arrayLayers = Range()) const = 0;
    
    //! @brief
    //! Copies pixel data into a region of a texture layer.
    //!
    virtual void upload(const Region3u& region, size_t mipmapLevel, size_t layer, const ByteArray& bytes, const ImageData& descriptor) = 0;
    
    //! @brief
    //! Copies texture pixel data into a given buffer.
    //!
    virtual ByteArray download(const Region3u& region, size_t mipmapLevel, size_t layer, const ImageData& descriptor) const = 0;
};

ARA_DECLARE_ERROR(CannotCreateGPUTexture)

typedef Ptr < GPUTexture > GPUTexturePtr;

ARA_HRI_END_NS

#endif 
