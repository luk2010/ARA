////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Core/ARARect2Edges.h
//! @date
//!     2023/12/08
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_CORE_RECT2EDGES_H__
#define __ARA_CORE_RECT2EDGES_H__

#include "ARAPlatform.h"

ARA_BEGIN_NAMESPACE 

//! @brief 
//! The edges of a Rect2.
//! 
struct Rect2Edges 
{
    Real left = 0.0;
    Real right = 0.0;
    Real top = 0.0;
    Real bottom = 0.0;

    //! @brief 
    //! Returns true if equals.
    //! 
    inline bool operator == (const Rect2Edges& rhs) const 
    {
        return left == rhs.left 
            && right == rhs.right 
            && top == rhs.top 
            && bottom == rhs.bottom;
    }
};

ARA_END_NAMESPACE

#endif 