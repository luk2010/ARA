////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Core/PixelFormat.h
//! @date
//!     2024/01/02
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_CORE_PIXELFORMAT_H__
#define __ARA_CORE_PIXELFORMAT_H__

#include "ARA/Core/ARAPlatform.h"

ARA_BEGIN_NAMESPACE

//! @brief 
//! Enumerates the common pixel formats. 
//! 
enum class PixelFormat 
{
    Unknown,

    RGBA8Unorm,
    RGBA8UnormSRGB,
    RGBA8Snorm,
    RGBA8Uint,
    RGBA8Sint,
    BGRA8Unorm,
    BGRA8UnormSRGB,
};

ARA_END_NAMESPACE

#endif 