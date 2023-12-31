////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     DeviceMTL/RenderDeviceMTL.mm
//! @date
//!     2024/01/02
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "RenderDeviceMTL.h"
#include "Enums.h"

#include "GPUBufferMTL.h"
#include "GPUTextureMTL.h"
#include "CommandQueueMTL.h"

RenderDeviceMTL::RenderDeviceMTL()
{
    mDevice = MTLCreateSystemDefaultDevice();
}

std::string RenderDeviceMTL::name() const
{
    return mDevice.name.UTF8String;
}

ARA::Hri::GPUBufferPtr RenderDeviceMTL::newBuffer(size_t length, const void* data)
{
    id<MTLBuffer> handle = nil;
    
    if (data)
        handle = [mDevice newBufferWithBytes:data length:length options:MTLResourceStorageModeManaged];
    else
        handle = [mDevice newBufferWithLength:length options:MTLResourceStorageModeManaged];
    
    return ARA::MakePtr < GPUBufferMTL >(*this, handle);
}

ARA::Hri::GPUTexturePtr RenderDeviceMTL::newTexture(ARA::Hri::GPUTextureType type, const ARA::Region3u& region, ARA::PixelFormat texPixelFormat, size_t numLayers, size_t numMipMapLevels, const ARA::ByteArray& src, const ARA::ImageData& srcDescriptor)
{
    MTLTextureDescriptor* desc = [MTLTextureDescriptor new];
    desc.textureType = TextureTypeToMTL(type);
    desc.pixelFormat = PixelFormatToMTL(texPixelFormat);
    desc.width = region.width;
    desc.height = region.height;
    desc.depth = region.depth;
    desc.mipmapLevelCount = numMipMapLevels;
    desc.arrayLength = numLayers;
    
    id < MTLTexture > _texture = [mDevice newTextureWithDescriptor:desc];
    
    if (!_texture)
        throw ARA::Hri::CannotCreateGPUTexture("RenderDeviceMTL: newTextureWithDescriptor failed.");
    
    ARA::Hri::GPUTexturePtr texture = ARA::MakePtr < GPUTextureMTL >(*this, _texture);
    
    if (!src.empty())
        texture->upload(region, 0, 0, src, srcDescriptor);
    
    return texture;
}

ARA::Hri::RenderPass RenderDeviceMTL::newRenderPassWithDrawable(ARA::NativeDrawable _drawable)
{
    id < CAMetalDrawable > drawable = (__bridge id) _drawable;
    
    ARA::Hri::RenderPass pass;
    
    ARA::Hri::RenderPassColorAttachment color0;
    color0.texture = ARA::MakePtr < GPUTextureMTL >(*this, drawable.texture);
    color0.layer = 0;
    color0.level = 0;
    color0.load = ARA::Hri::LoadAction::Clear;
    color0.store = ARA::Hri::StoreAction::Store;
    pass.colorAttachments.push_back(color0);
    
    return pass;
}

ARA::Hri::CommandQueuePtr RenderDeviceMTL::newCommandQueue()
{
    return ARA::MakePtr < CommandQueueMTL >(*this, [mDevice newCommandQueue]);
}

size_t RenderDeviceMTL::maxNumberOfColorAttachments() const
{
    return 8;
}
