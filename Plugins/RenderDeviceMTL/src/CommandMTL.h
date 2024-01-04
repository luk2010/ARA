////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     DeviceMTL/CommandMTL.h
//! @date
//!     2024/01/04
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __DEVICEMTL_COMMANDMTL_H__
#define __DEVICEMTL_COMMANDMTL_H__

#include "Platform.h"
#include "ARA/Hri/Command.h"

//! @brief
//! Defines a Command with the Metal API.
//!
class CommandMTL : public ARA::Hri::Command
{
    //! @brief
    //! The MTLCommandBuffer handle.
    //!
    id < MTLCommandBuffer > mHandle;
    
public:
    
    //! @brief
    //! Creates a new CommandMTL instance.
    //!
    CommandMTL(ARA::Hri::RenderDevice& device, id < MTLCommandBuffer > handle);
    
    //! @brief
    //! Returns the handle.
    //!
    id < MTLCommandBuffer > handle() const;
    
    //! @brief
    //! Creates a new RenderEncoder for this Command.
    //!
    ARA::Hri::RenderEncoderPtr newRenderEncoder(const ARA::Hri::RenderPass& renderPass);
    
    //! @brief
    //! Commits the command to its command queue.
    //!
    void commit();
};

#endif
