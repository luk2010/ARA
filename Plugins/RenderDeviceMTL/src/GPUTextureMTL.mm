////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     DeviceMTL/GPUTextureMTL.mm
//! @date
//!     2024/01/04
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "GPUTextureMTL.h"
#include "Enums.h"

GPUTextureMTL::GPUTextureMTL(ARA::Hri::RenderDevice& device, id < MTLTexture > handle):
ARA::Hri::GPUTexture(device), mHandle(handle)
{
    
}

id < MTLTexture > GPUTextureMTL::handle() const
{
    return mHandle;
}

ARA::Hri::GPUTextureType GPUTextureMTL::type() const
{
    return TextureTypeFromMTL(mHandle.textureType);
}

ARA::PixelFormat GPUTextureMTL::pixelFormat() const
{
    return PixelFormatFromMTL(mHandle.pixelFormat);
}

size_t GPUTextureMTL::width() const
{
    return mHandle.width;
}

size_t GPUTextureMTL::height() const
{
    return mHandle.height;
}

size_t GPUTextureMTL::depth() const
{
    return mHandle.depth;
}

size_t GPUTextureMTL::arrayLength() const
{
    return mHandle.arrayLength;
}

size_t GPUTextureMTL::mipmapLevels() const
{
    return mHandle.mipmapLevelCount;
}

size_t GPUTextureMTL::samplesCount() const
{
    return mHandle.sampleCount;
}

ARA::Hri::GPUTextureUsage GPUTextureMTL::usage() const
{
    return TextureUsageFromMTL(mHandle.usage);
}

ARA::Hri::GPUTexturePtr GPUTextureMTL::newView(ARA::PixelFormat pixelFormat, ARA::Hri::GPUTextureType textureType, const ARA::Range& levels, const ARA::Range& layers) const
{
    MTLPixelFormat _format = PixelFormatToMTL(pixelFormat);
    MTLTextureType _type = TextureTypeToMTL(textureType);
    
    id < MTLTexture > _texture = [mHandle newTextureViewWithPixelFormat:_format
                                                            textureType:_type
                                                                 levels:NSMakeRange(levels.start, levels.length)
                                                                 slices:NSMakeRange(layers.start, layers.length)];
    
    if (!_texture)
        throw ARA::Hri::CannotCreateGPUTexture("GPUTextureMTL: newTextureViewWithPixelFormat failed.");
    
    return ARA::MakePtr < GPUTextureMTL >(const_cast < ARA::Hri::RenderDevice& >(device()), _texture);
}

void GPUTextureMTL::upload(const ARA::Region3u& region, size_t level, size_t layer, const ARA::ByteArray& bytes, const ARA::ImageData& descriptor)
{
    [mHandle replaceRegion:MTLRegionMake3D(region.x, region.y, region.z, region.width, region.height, region.depth)
               mipmapLevel:level
                     slice:layer
                 withBytes:&bytes[0]
               bytesPerRow:descriptor.bytesPerRow
             bytesPerImage:descriptor.bytesPerLayer];
}

ARA::ByteArray GPUTextureMTL::download(const ARA::Region3u &region, size_t mipmapLevel, size_t layer, const ARA::ImageData &descriptor) const
{
    size_t rowCount = region.height - region.y;
    size_t layersCount = region.depth - region.z;
    size_t byteCount = descriptor.bytesPerRow * rowCount * layersCount;
    
    ARA::ByteArray bytes;
    bytes.resize(byteCount, 0);
    
    [mHandle getBytes:&bytes[0]
          bytesPerRow:descriptor.bytesPerRow
        bytesPerImage:descriptor.bytesPerLayer
           fromRegion:MTLRegionMake3D(region.x, region.y, region.z, region.width, region.height, region.depth)
          mipmapLevel:mipmapLevel
                slice:layer];
    
    return bytes;
}
