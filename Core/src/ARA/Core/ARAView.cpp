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

void View::setObserver(const Ptr < Observer >& observer)
{
    auto old = mObserver.lock();
    
    if (old != observer)
    {
        if (old)
            removeListener(old);
        
        mObserver = observer;
        
        if (observer)
            addListener(observer);
    }
}

void View::update()
{
    auto controller = observer();
    
    if (controller)
        controller->onViewUpdate(*this);
    
    for (auto& child : mChildrenNodes)
        child->update();
}

bool View::acceptsMouseMoveEvents() const
{
    return mAcceptsMouseMoveEvents.load();
}

void View::setAcceptsMouseMoveEvents(bool value)
{
    mAcceptsMouseMoveEvents.store(value);
}

ARA_END_NAMESPACE
