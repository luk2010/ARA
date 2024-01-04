////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Hri/CommandQueue.h
//! @date
//!     2024/01/04
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_HRI_COMMANDQUEUE_H__
#define __ARA_HRI_COMMANDQUEUE_H__

#include "ARA/Hri/Platform.h"
#include "ARA/Hri/GPUResource.h"
#include "ARA/Hri/Command.h"

ARA_HRI_BEGIN_NS

//! @brief 
//! A Queue that executes Commands on the GPU. 
//! 
class CommandQueue : public GPUResource 
{
protected:
    
    //! @brief
    //! Constructor.
    //!
    CommandQueue(RenderDevice& device);
    
public:
    
    //! @brief
    //! Creates a new Command to be executed.
    //!
    virtual CommandPtr newCommand() = 0;
};

typedef Ptr < CommandQueue > CommandQueuePtr;

ARA_HRI_END_NS

#endif 
