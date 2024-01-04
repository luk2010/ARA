////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Hri/RenderEncoder.h
//! @date
//!     2024/01/04
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_HRI_RENDERENCODER_H__
#define __ARA_HRI_RENDERENCODER_H__

#include "ARA/Hri/CommandEncoder.h"
#include "ARA/Hri/RenderPass.h"

$ns(ARA, Hri) 
{
    //! @brief 
    //! A Command Encoder that encodes rasterizer commands.
    //! 
    class RenderEncoder : public CommandEncoder
    {
        //! @brief 
        //! The current render pass.
        //! 
        RenderPass mRenderPass; 

    protected:

        //! @brief 
        //! Constructs a new Render Encoder.
        //! 
        RenderEncoder(RenderDevice& device, const RenderPass& renderPass);

    public: 

        //! @brief 
        //! Returns the render pass.
        //! 
        const RenderPass& renderPass() const; 
    };

    typedef Ptr < RenderEncoder > RenderEncoderPtr;
}

#endif 