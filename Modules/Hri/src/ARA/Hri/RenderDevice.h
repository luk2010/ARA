////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Hri/RenderDevice.h
//! @date
//!     2024/01/01
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_HRI_RENDERDEVICE_H__
#define __ARA_HRI_RENDERDEVICE_H__

#include "ARA/Hri/Platform.h"

ARA_HRI_BEGIN_NS

//! @brief
//! An interface that defines a rendering device.
//!
class RenderDevice
{
public:
    
    //! @brief
    //! Virtual destructor.
    //!
    virtual ~RenderDevice() = default;
    
    //! @brief
    //! Returns the device's name.
    //!
    virtual std::string name() const = 0;
};

ARA_HRI_END_NS

#endif 
