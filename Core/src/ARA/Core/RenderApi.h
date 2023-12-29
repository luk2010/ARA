////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Core/RenderApi.h
//! @date
//!     2023/12/29
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_CORE_RENDERAPI_H__
#define __ARA_CORE_RENDERAPI_H__

#include "ARA/Core/ARAPlatform.h"

ARA_BEGIN_NAMESPACE

//! @brief 
//! Enumrates known popular low level render APIs. 
//! 
enum class RenderAPI
{
    Unknown,
    D3D10,
    D3D11,
    D3D12,
    OpenGl,
    OpenGlES,
    Vulkan,
    Metal 
};

typedef std::vector < RenderAPI > RenderAPIList;

ARA_END_NAMESPACE

#endif 