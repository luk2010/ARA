////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Cocoa/ARAWindow.cpp
//! @date
//!     2023/12/11
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ARA/Core/ARAWindow.h"

ARA_BEGIN_NAMESPACE

void Window::setObserver(const Ptr < Observer >& observer)
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

ElementPtr Window::contentElement() const
{
    return mContentElement;
}

void Window::setContentElement(const ElementPtr& element)
{
    if (mContentElement)
        mContentElement->didMoveFromWindow();
    
    mContentElement.reset();
    
    if (element && element->willMoveToWindow(*this))
    {
        mContentElement = element;
        mContentElement->didMoveToWindow();
        _setContentView(mContentElement->view());
    }
}

ARA_END_NAMESPACE
