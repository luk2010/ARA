////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Core/ARAEventListener.cpp
//! @date
//!     2023/12/11
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ARA/Core/ARAEventListener.h"

ARA_BEGIN_NAMESPACE

bool EventListener::handleEvent(const Event& event)
{
    switch (event.type)
    {
        case EventType::MouseDown:
            return onMouseDown(static_cast < const MouseDownEvent& >(event));
            
        case EventType::MouseUp:
            return onMouseUp(static_cast < const MouseUpEvent& >(event));
            
        case EventType::MouseMove:
            return onMouseMove(static_cast < const MouseMoveEvent& >(event));
            
        case EventType::MouseEnter:
            return onMouseEnter(static_cast < const MouseEnterEvent& >(event));
            
        case EventType::MouseExit:
            return onMouseExit(static_cast < const MouseExitEvent& >(event));
            
        case EventType::MouseWheel:
            return onMouseWheel(static_cast < const MouseWheelEvent& >(event));
            
        case EventType::KeyDown:
            return onKeyDown(static_cast < const KeyEvent& >(event));
            
        case EventType::KeyUp:
            return onKeyUp(static_cast < const KeyEvent& >(event));
            
        default:
            return false;
    }
}

bool EventListener::onMouseDown(const MouseDownEvent& event)
{
    return false;
}

bool EventListener::onMouseUp(const MouseUpEvent& event)
{
    return false;
}

bool EventListener::onMouseMove(const MouseMoveEvent& event)
{
    return false;
}

bool EventListener::onMouseEnter(const MouseEnterEvent& event)
{
    return false;
}

bool EventListener::onMouseExit(const MouseExitEvent& event)
{
    return false;
}

bool EventListener::onMouseWheel(const MouseWheelEvent& event)
{
    return false;
}

bool EventListener::onKeyDown(const KeyEvent& event)
{
    return false;
}

bool EventListener::onKeyUp(const KeyEvent& event)
{
    return false;
}

ARA_END_NAMESPACE
