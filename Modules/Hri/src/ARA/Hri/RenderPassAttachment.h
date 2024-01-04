////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Hri/RenderPassAttachment.h
//! @date
//!     2024/01/04
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_HRI_RENDERPASSATTACHMENT_H__
#define __ARA_HRI_RENDERPASSATTACHMENT_H__

#include "ARA/Hri/GPUTexture.h"
#include "ARA/Hri/LoadAction.h"
#include "ARA/Hri/StoreAction.h"

$ns(ARA, Hri)
{
    //! @brief
    //! An attachment in a RenderPass.
    //!
    struct RenderPassAttachment
    {
        GPUTexturePtr texture;
        
        size_t level;
        size_t layer;
        size_t depthPlane = 0;
        
        LoadAction load = LoadAction::Load;
        StoreAction store = StoreAction::Store;
    };
}

#endif 
