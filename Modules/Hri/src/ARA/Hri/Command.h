////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Hri/Command.h
//! @date
//!     2024/01/04
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_HRI_COMMAND_H__
#define __ARA_HRI_COMMAND_H__

#include "ARA/Hri/GPUResource.h"
#include "ARA/Hri/RenderPass.h"
#include "ARA/Hri/RenderEncoder.h"

$ns(ARA, Hri)
{
    //! @brief 
    //! Defines a command executed in a CommandQueue.
    //! 
    class Command : public GPUResource
    {
    protected:
        
        //! @brief
        //! Constructor.
        //!
        Command(RenderDevice& device);
        
        //! @brief
        //! Creates a new RenderEncoder for this Command.
        //!
        virtual RenderEncoderPtr newRenderEncoder(const RenderPass& renderPass) = 0;
        
        //! @brief
        //! Commits the command to its command queue.
        //!
        virtual void commit() = 0;
    };
    
    typedef Ptr < Command > CommandPtr;
}

#endif 
