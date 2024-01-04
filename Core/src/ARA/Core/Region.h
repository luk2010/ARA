////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Core/Region.h
//! @date
//!     2024/01/04
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_CORE_REGION_H__
#define __ARA_CORE_REGION_H__

#include "ARA/Core/ARAPlatform.h"

ARA_BEGIN_NAMESPACE

//! @brief
//! Defines a 2D region.
//!
template < class T > struct Region2
{
    T x = 0;
    T y = 0;
    T width = 0;
    T height = 0;
};

//! @brief
//! Defines a 3D region.
//!
template < class T > struct Region3
{
    T x = 0;
    T y = 0;
    T z = 0;
    T width = 0;
    T height = 0;
    T depth = 0;
};

using Region2i = Region2 < ssize_t >;
using Region2u = Region2 < size_t >;
using Region2f = Region2 < float >;
using Region2d = Region2 < double >;
using Region2r = Region2 < Real >;

using Region3i = Region3 < ssize_t >;
using Region3u = Region3 < size_t >;
using Region3f = Region3 < float >;
using Region3d = Region3 < double >;
using Region3r = Region3 < Real >;

ARA_END_NAMESPACE

#endif
