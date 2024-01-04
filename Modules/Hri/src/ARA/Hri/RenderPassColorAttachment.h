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

#ifndef __ARA_HRI_RENDERPASSCOLORATTACHMENT_H__
#define __ARA_HRI_RENDERPASSCOLORATTACHMENT_H__

#include "ARA/Hri/RenderPassAttachment.h"
#include "ARA/Core/ARAColor.h"

$ns(ARA, Hri)
{
    struct RenderPassColorAttachment : RenderPassAttachment 
    {
        Color clearColor;
    };

    typedef std::vector < RenderPassColorAttachment > RenderPassColorAttachmentList;
}

#endif 