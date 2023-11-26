//
//  ARASize2.h
//  lui
//
//  Created by jacques tronconi on 26/11/2023.
//

#ifndef ARASize2_h
#define ARASize2_h

#include "ARAPlatform.h"

ARA_BEGIN_NAMESPACE

//! @brief
//! A 2d size.
struct Size2
{
    Real width = 0;
    Real height = 0;
    
    //! @brief
    //! Returns true if equals a given instance.
    inline bool operator == (const Size2& size) const
    {
        return width == size.width && height == size.height;
    }
};

//! @brief
//! Prints the Size2 object.
inline std::ostream& operator << (std::ostream& os, const Size2& size)
{
    return os << "ARA::Size2(" << size.width << ", " << size.height << ")";
}

ARA_END_NAMESPACE

#endif /* ARASize2_h */
