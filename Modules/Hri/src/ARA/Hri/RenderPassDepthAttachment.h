////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Hri/RenderPassColorAttachment.h
//! @date
//!     2024/01/04
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_HRI_RENDERPASSDEPTHATTACHMENT_H__
#define __ARA_HRI_RENDERPASSDEPTHATTACHMENT_H__

#include "ARA/Hri/RenderPassAttachment.h"

$ns(ARA, Hri)
{
    struct RenderPassDepthAttachment : RenderPassAttachment 
    {
        double clearDepth = 1.0;
    };

    typedef std::vector < RenderPassDepthAttachment > RenderPassDepthAttachmentList;
}

#endif