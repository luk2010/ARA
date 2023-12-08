//
//  ARARect2.h
//  ARA
//
//  Created by jacques tronconi on 26/11/2023.
//

#ifndef ARARect2_h
#define ARARect2_h

#include "ARAPoint2.h"
#include "ARASize2.h"

ARA_BEGIN_NAMESPACE

//! @brief
//! A 2d rectangle.
struct Rect2
{
    Point2 origin;
    Size2 size;
    
    //! @brief
    //! Returns the rectangle area.
    inline Real area() const { return size.width * size.height; }
    
    //! @brief
    //! Returns the minimum X of the rectangle.
    inline Real minX() const { return std::min(origin.x, origin.x + size.width); }
    
    //! @brief
    //! Returns the minimum Y of the rectangle.
    inline Real minY() const { return std::min(origin.y, origin.y + size.height); }
    
    //! @brief
    //! Returns the maximum X of the rectangle.
    inline Real maxX() const { return std::max(origin.x, origin.x + size.width); }
    
    //! @brief
    //! Returns the maximum Y of the rectangle.
    inline Real maxY() const { return std::max(origin.y, origin.y + size.height); }

    //! @brief 
    //! Returns true if a point is in the rectangle.
    //! 
    inline bool contains(const Point2& p) const 
    {
        return origin.x <= p.x 
            && origin.y <= p.y 
            && origin.x + size.width >= p.x 
            && origin.y + size.height >= p.y;
    }
    
    //! @brief
    //! Returns true if this rectangle is the same as the provided one.
    inline bool operator == (const Rect2& rhs) const
    {
        return origin == rhs.origin && size == rhs.size;
    }
};

//! @brief
//! Prints a Rect2 instance.
inline std::ostream& operator << (std::ostream& os, const Rect2& rect)
{
    return os << "Rect2(" << rect.origin << ", " << rect.size << ")";
}

ARA_END_NAMESPACE

#endif /* ARARect2_h */
