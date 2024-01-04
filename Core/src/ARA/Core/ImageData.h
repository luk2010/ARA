////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Core/ImageData.h
//! @date
//!     2024/01/04
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_CORE_IMAGEDATA_H__
#define __ARA_CORE_IMAGEDATA_H__

#include "ARA/Core/ARAPlatform.h"
#include "ARA/Core/PixelFormat.h"

ARA_BEGIN_NAMESPACE

//! @brief
//! A descriptor for data in an image data.
//!
struct ImageData
{
    //! @brief
    //! The current image pixel format.
    //!
    PixelFormat format;
    
    //! @brief
    //! The number of bytes per rows.
    //!
    size_t bytesPerRow;
    
    //! @brief
    //! The number of bytes per layer.
    //!
    size_t bytesPerLayer;
};

ARA_END_NAMESPACE

#endif 
