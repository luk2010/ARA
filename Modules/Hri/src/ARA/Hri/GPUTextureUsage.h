////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Hri/GPUTextureUsage.h
//! @date
//!     2024/01/04
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_HRI_GPUTEXTUREUSAGE_H__
#define __ARA_HRI_GPUTEXTUREUSAGE_H__

#include "ARA/Hri/Platform.h"

ARA_HRI_BEGIN_NS

//! @brief
//! Defines the available usages for a GPUTexture.
//!
struct GPUTextureUsage
{
    bool shaderRead :1 = true;
    bool shaderWrite :1 = true;
    bool renderTarget :1 = false;
    bool pixelFormatView :1 = true;
};

ARA_HRI_END_NS

#endif
