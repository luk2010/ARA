////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Hri/GPUResource.cpp
//! @date
//!     2024/01/02
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ARA/Hri/GPUResource.h"

ARA_HRI_BEGIN_NS

GPUResource::GPUResource(RenderDevice& device):
mDevice(device) 
{

}

RenderDevice& GPUResource::device() 
{
    return mDevice; 
}

const RenderDevice& GPUResource::device() const 
{
    return mDevice; 
}

void GPUResource::setName(const std::string& name) 
{
    mName = name;
}

const std::string& GPUResource::name() const 
{
    return mName; 
}

ARA_HRI_END_NS