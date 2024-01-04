////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Hri/RenderEncoder.cpp
//! @date
//!     2024/01/04
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ARA/Hri/RenderEncoder.h"

$ns(ARA, Hri) 
{
    RenderEncoder::RenderEncoder(RenderDevice& dev, const RenderPass& renderPass):
    CommandEncoder(dev), mRenderPass(renderPass) 
    {
        
    }
}