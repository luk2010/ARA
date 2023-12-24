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

void Window::setInputElement(const ElementPtr& element)
{
    if (mInputElement)
    {
        if (!mInputElement->willResignInputElement())
            return;
        
        mInputElement->didResignInputElement();
        mInputElement.reset();
    }
    
    if (element)
    {
        if (!element->willBecomeInputElement())
            return;
        
        mInputElement = element;
        element->didBecomeInputElement();
    }
}

ElementPtr Window::inputElement() const
{
    return mInputElement;
}

bool Window::handleEvent(const Event& event)
{
    switch (event.type)
    {
        case EventType::KeyDown:
        case EventType::KeyUp:
            if (mInputElement)
                return mInputElement->handleEvent(event);
            break;
        default:
            break;
    }
    
    auto obs = mObserver.lock();
    
    if (obs && obs->handleEvent(event))
        return true;
    
    return EventListener::handleEvent(event);
}

ARA_END_NAMESPACE
