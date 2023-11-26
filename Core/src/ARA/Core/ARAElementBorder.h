//
//  ARAElementBorder.h
//  lui
//
//  Created by jacques tronconi on 26/11/2023.
//

#ifndef ARAElementBorder_h
#define ARAElementBorder_h

#include "ARAInheritable.h"
#include "ARARectEdge.h"
#include "ARAColor.h"

ARA_BEGIN_NAMESPACE

//! @brief
//! An element border property.
struct ElementBorder
{
    //! @brief
    //! The border edge.
    RectEdge edge;
    
    //! @brief
    //! The border width.
    Inheritable<Real> width = 0;
    
    //! @brief
    //! The border color.
    Inheritable<Color> color;
    
    //! @brief
    //! Returns true if the element border is equal to another border.
    inline bool isEqualTo(const ElementBorder& border) const
    {
        return edge == border.edge
            && width.isEqualTo(border.width)
            && color.isEqualTo(border.color);
    }
};

ARA_END_NAMESPACE

#endif /* ARAElementBorder_h */
