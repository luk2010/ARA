////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Core/ARAIntersectionResult.h
//! @date
//!     2023/11/27
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_CORE_INTERSECTION_RESULT_H__
#define __ARA_CORE_INTERSECTION_RESULT_H__

#include "ARAPlatform.h"

ARA_BEGIN_NAMESPACE

//! @brief 
//! Enumerates available intersection results between two entities.
//!
enum class IntersectionResult 
{
    //! @brief 
    //! The algorithm doesn't know.
    Unknown,
    
    //! @brief 
    //! The left entity is inside the right entity.
    InsideR, 

    //! @brief
    //! The right entity is inside the left entity.
    InsideL, 

    //! @brief 
    //! Both entities do not intersect.
    Outside, 

    //! @brief 
    //! The entities intersect.
    Intersect
};

ARA_END_NAMESPACE

#endif // __ARA_CORE_INTERSECTION_RESULT_H__