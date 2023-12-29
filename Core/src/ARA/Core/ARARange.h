////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Core/ARARange.h
//! @date
//!     2023/11/29
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_RANGE_H__
#define __ARA_RANGE_H__

#include "ARAPlatform.h"
#include "ARAIntersectionResult.h"

ARA_BEGIN_NAMESPACE 

//! @brief 
//! A Range structure.
struct Range 
{
    size_t start = 0;
    size_t length = 0;

    //! @brief 
    //! Returns the index of the last element + 1 in the range. 
    inline size_t end() const { return start + length; }
    
    //! @brief
    //! Returns true if an index is inside the range.
    inline bool contains(size_t index) const { return start <= index && end() > index; }

    //! @brief 
    //! Returns the intersection result with another range.
    //!
    inline IntersectionResult intersect(const Range& rhs) const 
    {
        if (start <= rhs.start && end() >= rhs.end())
            return IntersectionResult::InsideL;

        else if (rhs.start <= start && rhs.end() >= end())
            return IntersectionResult::InsideR;
        
        else if (end() < rhs.start || rhs.end() < start) 
            return IntersectionResult::Outside;
        
        return IntersectionResult::Intersect;
    }
    
    //! @brief
    //! Removes a range from this range.
    //!
    inline void remove(const Range& rhs)
    {
        if (rhs.start < start)
        {
            if (rhs.end() > end())
            {
                start = 0;
                length = 0;
                return;
            }
            
            start = rhs.end();
            length = end() - start;
            start = start - rhs.length;
            length = length - rhs.length;
            
            return;
        }
        else
        {
            if (rhs.end() >= end())
            {
                length = rhs.start - start;
            }
            else
            {
                size_t end = (start + length) - rhs.length;
                length = end - start;
            }
        }
    }
};

//! @brief
//! A list of Range.
typedef std::vector<Range> RangeList;

ARA_END_NAMESPACE

#endif 
