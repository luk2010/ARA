//
//  ARAPoint2.h
//  lui
//
//  Created by jacques tronconi on 26/11/2023.
//

#ifndef ARAPoint2_h
#define ARAPoint2_h

#include "ARAPlatform.h"

ARA_BEGIN_NAMESPACE

//! @brief
//! A 2d Point.
struct Point2
{
    Real x = 0;
    Real y = 0;
    
    //! @brief
    //! Returns true if is equal to another point.
    inline bool operator == (const Point2& rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }
};

//! @brief
//! Prints the Point2 instance.
inline std::ostream& operator << (std::ostream& os, const Point2& point)
{
    return os << "ARA::Point2(" << point.x << ", " << point.y << ")";
}

ARA_END_NAMESPACE

#endif /* ARAPoint2_h */
