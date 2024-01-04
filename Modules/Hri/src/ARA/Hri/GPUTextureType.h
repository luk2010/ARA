////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Hri/GPUTextureType.h
//! @date
//!     2024/01/04
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_HRI_GPUTEXTURETYPE_H__
#define __ARA_HRI_GPUTEXTURETYPE_H__

#include "ARA/Hri/Platform.h"

ARA_HRI_BEGIN_NS

//! @brief
//! Enumerates available texture types.
//!
enum class GPUTextureType
{
    Invalid,
    
    One,
    Two,
    Three,
    
    Array1D,
    Array2D,
    
    MultiSample2D,
    MultiSample3D,
    
    Cube,
    ArrayCube,
    
    Buffer
};

ARA_HRI_END_NS

#endif
