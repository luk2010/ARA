////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     DeviceMTL/GPUTextureMTL.h
//! @date
//!     2024/01/04
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __DEVICEMTL_GPUTEXTUREMTL_H__
#define __DEVICEMTL_GPUTEXTUREMTL_H__

#include "Platform.h"
#include "ARA/Hri/GPUTexture.h"

//! @brief
//! A GPUTexture object for Metal.
//!
class GPUTextureMTL : public ARA::Hri::GPUTexture
{
    //! @brief
    //! The MTLTexture handle.
    //!
    id < MTLTexture > mHandle;
    
public:
    
    //! @brief
    //! Wraps a MTLTexture into a GPUTexture.
    //!
    GPUTextureMTL(ARA::Hri::RenderDevice& device, id < MTLTexture > handle);
    
    //! @brief
    //! Returns the MTLTexture handle.
    //!
    id < MTLTexture > handle() const;
    
    //! @brief
    //! Returns the texture type.
    //!
    ARA::Hri::GPUTextureType type() const;
    
    //! @brief
    //! Returns the texture internal pixel format.
    //!
    ARA::PixelFormat pixelFormat() const;
    
    //! @brief
    //! Returns the texture width, in pixels.
    //!
    size_t width() const;
    
    //! @brief
    //! Returns the texture height, in pixels.
    //!
    size_t height() const;
    
    //! @brief
    //! Returns the texture depth, in pixels.
    //!
    size_t depth() const;
    
    //! @brief
    //! The number of layers in an array texture.
    //!
    size_t arrayLength() const;
    
    //! @brief
    //! The number of mipmap levels.
    //!
    size_t mipmapLevels() const;
    
    //! @brief
    //! The number of samples for a multisample texture.
    //!
    size_t samplesCount() const;
    
    //! @brief
    //! The current texture usages.
    //!
    ARA::Hri::GPUTextureUsage usage() const;
    
    //! @brief
    //! Creates a new view of the texture, reinterpreting a subset of its data using a different
    //! type, and pixel format.
    //!
    ARA::Hri::GPUTexturePtr newView(ARA::PixelFormat pixelFormat,
                                    ARA::Hri::GPUTextureType textureType,
                                    const ARA::Range& mipmapLevels = ARA::Range(),
                                    const ARA::Range& arrayLayers = ARA::Range()) const;
    
    //! @brief
    //! Copies pixel data into a region of a texture layer.
    //!
    void upload(const ARA::Region3u& region, size_t mipmapLevel, size_t layer, const ARA::ByteArray& bytes, const ARA::ImageData& descriptor);
    
    //! @brief
    //! Copies texture pixel data into a given buffer.
    //!
    ARA::ByteArray download(const ARA::Region3u& region, size_t mipmapLevel, size_t layer, const ARA::ImageData& descriptor) const;
};

#endif
