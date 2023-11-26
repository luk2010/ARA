//
//  ARARectCorner.h
//  lui
//
//  Created by jacques tronconi on 26/11/2023.
//

#ifndef ARARectCorner_h
#define ARARectCorner_h

#include "ARAPlatform.h"

ARA_BEGIN_NAMESPACE

//! @brief
//! Constants that define different corner radii.
enum class RectCorner : int
{
    TopLeft = 0,
    TopRight = 1,
    BottomLeft = 2,
    BottomRight = 3
};

ARA_END_NAMESPACE

#endif /* ARARectCorner_h */
