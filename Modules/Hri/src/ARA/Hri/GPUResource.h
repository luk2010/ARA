////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Hri/GPUResource.h
//! @date
//!     2024/01/02
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_HRI_GPURESOURCE_H__
#define __ARA_HRI_GPURESOURCE_H__

#include "ARA/Hri/Platform.h"

ARA_HRI_BEGIN_NS

class RenderDevice; 

//! @brief 
//! A resource created by a `RenderDevice`.
//! 
class GPUResource 
{
    //! @brief 
    //! The RenderDevice that created this resource.
    //! 
    RenderDevice& mDevice; 

    //! @brief 
    //! The resource name. 
    //! 
    std::string mName;

public:

    //! @brief 
    //! Creates a new resource.
    //! 
    GPUResource(RenderDevice& device);

    //! @brief 
    //! Virtual destructor.
    //! 
    virtual ~GPUResource() = default; 

    //! @brief 
    //! Returns the resource device. 
    //! 
    RenderDevice& device();

    //! @brief 
    //! Returns the resource device. 
    //! 
    const RenderDevice& device() const;

    //! @brief 
    //! Sets the resource's name. 
    //! 
    void setName(const std::string& name);

    //! @brief 
    //! Returns the resource's name. 
    //! 
    const std::string& name() const; 
};

ARA_HRI_END_NS

#endif 