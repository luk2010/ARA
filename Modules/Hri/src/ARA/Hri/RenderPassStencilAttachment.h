////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Hri/RenderPassStencilAttachment.h
//! @date
//!     2024/01/04
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_HRI_RENDERPASSSTENCILATTACHMENT_H__
#define __ARA_HRI_RENDERPASSSTENCILATTACHMENT_H__

#include "ARA/Hri/RenderPassAttachment.h"

$ns(ARA, Hri)
{
    struct RenderPassStencilAttachment : RenderPassAttachment 
    {
        uint32_t stencilValue = 0;
    };

    typedef std::vector < RenderPassStencilAttachment > RenderPassStencilAttachmentList;
}

#endif 