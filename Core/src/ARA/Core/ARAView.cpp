////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Cocoa/ARAView.cpp
//! @date
//!     2023/12/08
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ARAView.h"

ARA_BEGIN_NAMESPACE

void View::update()
{
    auto controller = observer();
    
    if (controller)
        controller->onViewUpdate(*this);
    
    for (auto& child : mChildrenNodes)
        child->update();
}

ARA_END_NAMESPACE
