////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Core/ARAEventListener.h
//! @date
//!     2023/12/11
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_CORE_EVENTLISTENER_H__
#define __ARA_CORE_EVENTLISTENER_H__

#include "ARA/Core/ARAEvent.h"

ARA_BEGIN_NAMESPACE

//! @brief
//! Defines a base class for an event listener.
//!
struct EventListener
{
    //! @brief
    //! Virtual destructor.
    //!
    virtual ~EventListener() = default;
    
    //! @brief
    //! Handles an event.
    //!
    virtual bool handleEvent(const Event& event);
    
protected:
    
    //! @brief
    //! A mouse button has been pressed.
    //!
    virtual bool onMouseDown(const MouseDownEvent& event);
    
    //! @brief
    //! A mouse button has been released.
    //!
    virtual bool onMouseUp(const MouseUpEvent& event);
    
    //! @brief
    //! The mouse has been moved in a tracked rectangle of the listened emitter.
    //!
    virtual bool onMouseMove(const MouseMoveEvent& event);
    
    //! @brief
    //! The mouse has entered a tracked rectangle of the listened emitter.
    //!
    virtual bool onMouseEnter(const MouseEnterEvent& event);
    
    //! @brief
    //! The mouse has exited a tracked rectangle of the listened emitter.
    //!
    virtual bool onMouseExit(const MouseExitEvent& event);
    
    //! @brief
    //! The mouse wheel has been rolled.
    //!
    virtual bool onMouseWheel(const MouseWheelEvent& event);
    
    //! @brief
    //! A key has been pressed.
    //!
    virtual bool onKeyDown(const KeyEvent& event);
    
    //! @brief
    //! A key has been released.
    //!
    virtual bool onKeyUp(const KeyEvent& event);
};

typedef Ptr < EventListener > EventListenerPtr;
typedef std::vector < EventListenerPtr > EventListenerList;

typedef Weak < EventListener > EventListenerWeak;
typedef std::vector < EventListenerWeak > EventListenerWeakList;

ARA_END_NAMESPACE

#endif
