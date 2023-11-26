//
//  ARAColor.h
//  ARA
//
//  Created by jacques tronconi on 26/11/2023.
//

#ifndef ARAColor_h
#define ARAColor_h

#include "ARAPlatform.h"

ARA_BEGIN_NAMESPACE

//! @brief
//! A RGBA Color.
struct Color
{
    Real red = 0;
    Real green = 0;
    Real blue = 0;
    Real alpha = 1;
    
    inline bool operator == (const Color& rhs) const
    {
        return red == rhs.red &&
               green == rhs.green &&
               blue == rhs.blue &&
               alpha == rhs.alpha;
    }
    
    //! @brief
    //! Returns true if the color is fully transparent.
    inline bool isTransparent() const { return alpha == 0; }
};

//! @brief
//! Prints a Color instance.
inline std::ostream& operator << (std::ostream& os, const Color& color)
{
    return os << "ARA::Color(" << color.red << ", " << color.green << ", " << color.blue << ", " << color.alpha << ")";
}

ARA_END_NAMESPACE

#endif /* ARAColor_h */
