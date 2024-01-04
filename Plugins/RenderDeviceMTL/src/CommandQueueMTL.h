////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     DeviceMTL/CommandQueueMTL.h
//! @date
//!     2024/01/04
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __DEVICEMTL_COMMANDQUEUEMTL_H__
#define __DEVICEMTL_COMMANDQUEUEMTL_H__

#include "Platform.h"
#include "ARA/Hri/CommandQueue.h"

//! @brief
//! Defines a Command Queue with the Metal API.
//!
class CommandQueueMTL : public ARA::Hri::CommandQueue
{
    //! @brief
    //! The MTLCommandQueue handle.
    //!
    id < MTLCommandQueue > mHandle;
    
public:
    
    //! @brief
    //! Creates a new Command Queue instance.
    //!
    CommandQueueMTL(ARA::Hri::RenderDevice& device, id < MTLCommandQueue > handle);
    
    //! @brief
    //! Returns the handle.
    //!
    id < MTLCommandQueue > handle() const;
    
    //! @brief
    //! Creates a new Command to be executed.
    //!
    ARA::Hri::CommandPtr newCommand();
};

#endif
