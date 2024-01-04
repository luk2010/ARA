////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Hri/CommandEncoder.h
//! @date
//!     2024/01/04
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_HRI_COMMANDENCODER_H__
#define __ARA_HRI_COMMANDENCODER_H__

#include "ARA/Hri/GPUResource.h"

$ns(ARA, Hri)
{
    //! @brief 
    //! An object that encodes commands into a Command object.
    //! 
    class CommandEncoder : public GPUResource 
    {
    protected:

        //! @brief 
        //! Constructor.
        //! 
        CommandEncoder(RenderDevice& device);

    public: 

        //! @brief
        //! Finishes the encoding of the current encoder.
        //! 
        virtual void end() = 0;
    };
}

#endif
