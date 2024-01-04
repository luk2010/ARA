////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     DeviceMTL/RenderEncoderMTL.h
//! @date
//!     2024/01/04
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __DEVICEMTL_RENDERENCODERMTL_H__
#define __DEVICEMTL_RENDERENCODERMTL_H__

#include "Platform.h"
#include "ARA/Hri/RenderEncoder.h"

//! @brief
//! Defines a Render Encoder with Metal.
//!
class RenderEncoderMTL : public ARA::Hri::RenderEncoder
{
    //! @brief
    //! The MTLRenderCommandEncoder handle.
    //!
    id < MTLRenderCommandEncoder > mHandle;
    
public:
    
    //! @brief
    //! Creates a new encoder.
    //!
    RenderEncoderMTL(ARA::Hri::RenderDevice& device, const ARA::Hri::RenderPass& renderPass, id < MTLRenderCommandEncoder > handle);
    
    //! @brief
    //! Returns the handle.
    //!
    id < MTLRenderCommandEncoder > handle() const;
    
    //! @brief
    //! Ends the encoding.
    //!
    void end();
};

#endif
