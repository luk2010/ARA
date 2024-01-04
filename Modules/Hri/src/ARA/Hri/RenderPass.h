////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Hri/RenderPass.h
//! @date
//!     2024/01/04
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_HRI_RENDERPASS_H__
#define __ARA_HRI_RENDERPASS_H__

#include "ARA/Hri/GPUTexture.h"
#include "ARA/Hri/RenderPassColorAttachment.h"
#include "ARA/Hri/RenderPassDepthAttachment.h"
#include "ARA/Hri/RenderPassStencilAttachment.h"

$ns(ARA, Hri)
{
    //! @brief
    //! Defines a descriptor for a rendering pass.
    //!
    struct RenderPass
    {
        //! @brief
        //! The color attachements in the render pass.
        //!
        RenderPassColorAttachmentList colorAttachments;
        
        //! @brief
        //! The depth attachment.
        //!
        RenderPassDepthAttachment depthAttachment;
        
        //! @brief
        //! The stencil attachment.
        //!
        RenderPassStencilAttachment stencilAttachment;
    };
}

#endif 
