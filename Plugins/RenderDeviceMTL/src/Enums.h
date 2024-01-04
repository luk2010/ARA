////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     DeviceMTL/Enums.h
//! @date
//!     2024/01/04
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __DEVICEMTL_ENUMS_H__
#define __DEVICEMTL_ENUMS_H__

#include "Platform.h"

#include "ARA/Core/PixelFormat.h"

#include "ARA/Hri/GPUTextureType.h"
#include "ARA/Hri/GPUTextureUsage.h"
#include "ARA/Hri/LoadAction.h"
#include "ARA/Hri/StoreAction.h"

inline ARA::PixelFormat PixelFormatFromMTL(MTLPixelFormat format)
{
    switch (format)
    {
        case MTLPixelFormatRGBA8Unorm:
            return ARA::PixelFormat::RGBA8Unorm;
        case MTLPixelFormatRGBA8Unorm_sRGB:
            return ARA::PixelFormat::RGBA8UnormSRGB;
        case MTLPixelFormatRGBA8Snorm:
            return ARA::PixelFormat::RGBA8Snorm;
        case MTLPixelFormatRGBA8Uint:
            return ARA::PixelFormat::RGBA8Uint;
        case MTLPixelFormatRGBA8Sint:
            return ARA::PixelFormat::RGBA8Sint;
        case MTLPixelFormatBGRA8Unorm:
            return ARA::PixelFormat::BGRA8Unorm;
        case MTLPixelFormatBGRA8Unorm_sRGB:
            return ARA::PixelFormat::BGRA8UnormSRGB;
            
        default:
            return ARA::PixelFormat::Unknown;
    }
}

inline MTLPixelFormat PixelFormatToMTL(ARA::PixelFormat format)
{
    switch (format)
    {
        case ARA::PixelFormat::RGBA8Unorm:
            return MTLPixelFormatRGBA8Unorm;
        case ARA::PixelFormat::RGBA8UnormSRGB:
            return MTLPixelFormatRGBA8Unorm_sRGB;
        case ARA::PixelFormat::RGBA8Snorm:
            return MTLPixelFormatRGBA8Snorm;
        case ARA::PixelFormat::RGBA8Uint:
            return MTLPixelFormatRGBA8Uint;
        case ARA::PixelFormat::RGBA8Sint:
            return MTLPixelFormatRGBA8Sint;
        case ARA::PixelFormat::BGRA8Unorm:
            return MTLPixelFormatBGRA8Unorm;
        case ARA::PixelFormat::BGRA8UnormSRGB:
            return MTLPixelFormatBGRA8Unorm_sRGB;
            
        default:
            return MTLPixelFormatInvalid;
    }
}

inline ARA::Hri::GPUTextureType TextureTypeFromMTL(MTLTextureType type)
{
    switch (type)
    {
        case MTLTextureType1D:
            return ARA::Hri::GPUTextureType::One;
        case MTLTextureType2D:
            return ARA::Hri::GPUTextureType::Two;
        case MTLTextureType3D:
            return ARA::Hri::GPUTextureType::Three;
            
        case MTLTextureType1DArray:
            return ARA::Hri::GPUTextureType::Array1D;
        case MTLTextureType2DArray:
            return ARA::Hri::GPUTextureType::Array2D;
            
        case MTLTextureType2DMultisample:
            return ARA::Hri::GPUTextureType::MultiSample2D;
            
        case MTLTextureTypeCube:
            return ARA::Hri::GPUTextureType::Cube;
        case MTLTextureTypeCubeArray:
            return ARA::Hri::GPUTextureType::ArrayCube;
            
        case MTLTextureTypeTextureBuffer:
            return ARA::Hri::GPUTextureType::Buffer;
            
        default:
            return ARA::Hri::GPUTextureType::Invalid;
    }
}

inline MTLTextureType TextureTypeToMTL(ARA::Hri::GPUTextureType type)
{
    switch (type)
    {
        case ARA::Hri::GPUTextureType::One:
            return MTLTextureType1D;
        case ARA::Hri::GPUTextureType::Two:
            return MTLTextureType2D;
        case ARA::Hri::GPUTextureType::Three:
            return MTLTextureType3D;
            
        case ARA::Hri::GPUTextureType::Array1D:
            return MTLTextureType1DArray;
        case ARA::Hri::GPUTextureType::Array2D:
            return MTLTextureType2DArray;
            
        case ARA::Hri::GPUTextureType::MultiSample2D:
            return MTLTextureType2DMultisample;
        case ARA::Hri::GPUTextureType::MultiSample3D:
            return MTLTextureType3D;
            
        case ARA::Hri::GPUTextureType::Cube:
            return MTLTextureTypeCube;
        case ARA::Hri::GPUTextureType::ArrayCube:
            return MTLTextureTypeCubeArray;
            
        case ARA::Hri::GPUTextureType::Buffer:
            return MTLTextureTypeTextureBuffer;
            
        case ARA::Hri::GPUTextureType::Invalid:
            throw ARA::EnumInvalid("TextureTypeToMTL: invalid enum.");
    }
}

inline ARA::Hri::GPUTextureUsage TextureUsageFromMTL(MTLTextureUsage usage)
{
    ARA::Hri::GPUTextureUsage rhs;
    
    rhs.shaderRead = (usage & MTLTextureUsageShaderRead);
    rhs.shaderWrite = (usage & MTLTextureUsageShaderWrite);
    rhs.renderTarget = (usage & MTLTextureUsageRenderTarget);
    rhs.pixelFormatView = (usage & MTLTextureUsagePixelFormatView);
    
    return rhs;
}

inline MTLLoadAction LoadActionToMTL(ARA::Hri::LoadAction action)
{
    switch (action)
    {
        case ARA::Hri::LoadAction::DontCare:
            return MTLLoadActionDontCare;
            
        case ARA::Hri::LoadAction::Load:
            return MTLLoadActionLoad;
            
        case ARA::Hri::LoadAction::Clear:
            return MTLLoadActionClear;
    }
}

inline ARA::Hri::LoadAction LoadActionFromMTL(MTLLoadAction action)
{
    switch (action)
    {
        case MTLLoadActionDontCare:
            return ARA::Hri::LoadAction::DontCare;
            
        case MTLLoadActionLoad:
            return ARA::Hri::LoadAction::Load;
            
        case MTLLoadActionClear:
            return ARA::Hri::LoadAction::Clear;
    }
}

inline MTLStoreAction StoreActionToMTL(ARA::Hri::StoreAction action)
{
    switch (action)
    {
        case ARA::Hri::StoreAction::DontCare:
            return MTLStoreActionDontCare;
            
        case ARA::Hri::StoreAction::Store:
            return MTLStoreActionStore;
            
        case ARA::Hri::StoreAction::Resolve:
            return MTLStoreActionMultisampleResolve;
            
        case ARA::Hri::StoreAction::StoreAndResolve:
            return MTLStoreActionStoreAndMultisampleResolve;
    }
}

inline ARA::Hri::StoreAction StoreActionFromMTL(MTLStoreAction action)
{
    switch (action)
    {
        case MTLStoreActionDontCare:
            return ARA::Hri::StoreAction::DontCare;
            
        case MTLStoreActionStore:
            return ARA::Hri::StoreAction::Store;
            
        case MTLStoreActionMultisampleResolve:
            return ARA::Hri::StoreAction::Resolve;
            
        case MTLStoreActionStoreAndMultisampleResolve:
            return ARA::Hri::StoreAction::StoreAndResolve;
            
        default:
            return ARA::Hri::StoreAction::DontCare;
    }
}

#endif
