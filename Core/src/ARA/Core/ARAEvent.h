////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Core/ARAEvent.h
//! @date
//!     2023/12/10
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_CORE_EVENT_H__
#define __ARA_CORE_EVENT_H__

#include "ARA/Core/ARAPlatform.h"
#include "ARA/Core/ARAMouseButton.h"
#include "ARA/Core/ARARect2.h"
#include "ARA/Core/ARAKeyModifiersMask.h"
#include "ARA/Core/KeyCode.h"

ARA_BEGIN_NAMESPACE

class EventEmitter;

//! @brief
//! Declares the events available in ARA.
//!
enum class EventType
{
    Unknown = 0,

    // Mouse events.
    
    MouseDown,
    MouseUp,
    MouseMove,
    MouseEnter,
    MouseExit,
    MouseWheel,
    
    // Keyboard events.
    
    KeyDown,
    KeyUp
};

//! @brief
//! Defines a basic event from the underlying UI system.
//!
//! Such an event can be sent only by ARA::EventEmitter objects. They send this to a
//! ARA::EventListener object that handles the event and calls one of its protected functions.
//!
struct Event
{
    //! @brief
    //! The event type.
    //!
    EventType type;
    
    //! @brief
    //! The emitter of this event.
    //!
    const EventEmitter& emitter;
    
    //! @brief
    //! Creates a new blanck event.
    //!
    inline Event(const EventEmitter& emitter, EventType type = EventType::Unknown):
        type(type), emitter(emitter) { }
};

//! @brief
//! Defines a base class for Mouse events.
//!
struct MouseEvent : public Event
{
    //! @brief
    //! The button that has been pressed or released.
    //!
    MouseButton button;
    
    //! @brief
    //! The location of the mouse, relative to the current emitter.
    //!
    Point2 location;
    
    //! @brief
    //! The absolute location of the mouse on the screen.
    //!
    Point2 locationOnScreen;
    
    //! @brief
    //! The delta with the previous mouse location, if this is a move event.
    //!
    Size2 delta;
    
    //! @brief
    //! Creates a new MouseEvent.
    //!
    inline MouseEvent(const EventEmitter& emitter, EventType type, MouseButton button, const Point2& location, const Point2& absLocation, const Size2& delta):
        Event(emitter, type), button(button), location(location), locationOnScreen(absLocation), delta(delta) { }
};

//! @brief
//! Shortcut constructor for a MouseDown event.
//!
struct MouseDownEvent : public MouseEvent
{
    //! @brief
    //! Creates a new MouseDownEvent.
    //!
    inline MouseDownEvent(const EventEmitter& emitter, MouseButton button, const Point2& location, const Point2& absLocation):
        MouseEvent(emitter, EventType::MouseDown, button, location, absLocation, Size2()) { }
};

//! @brief
//! Shortcut constructor for a MouseUp event.
//!
struct MouseUpEvent : public MouseEvent
{
    //! @brief
    //! Creates a new MouseUpEvent.
    //!
    inline MouseUpEvent(const EventEmitter& emitter, MouseButton button, const Point2& location, const Point2& absLocation):
        MouseEvent(emitter, EventType::MouseUp, button, location, absLocation, Size2()) { }
};

//! @brief
//! Shortcut constructor for a MouseMove event.
//!
struct MouseMoveEvent : public MouseEvent
{
    //! @brief
    //! Creates a new MouseMoveEvent.
    //!
    inline MouseMoveEvent(const EventEmitter& emitter, const Point2& location, const Point2& absLocation, const Size2& delta):
        MouseEvent(emitter, EventType::MouseMove, MouseButton::None, location, absLocation, delta) { }
};

//! @brief
//! Shortcut constructor for a MouseEnter event.
//!
struct MouseEnterEvent : public MouseEvent
{
    //! @brief
    //! Creates a new MouseEnterEvent.
    //!
    inline MouseEnterEvent(const EventEmitter& emitter, const Point2& location, const Point2& absLocation):
        MouseEvent(emitter, EventType::MouseEnter, MouseButton::None, location, absLocation, Size2()) { }
};

//! @brief
//! Shortcut constructor for a MouseExit event.
//!
struct MouseExitEvent : public MouseEvent
{
    //! @brief
    //! Creates a new MouseExitEvent.
    //!
    inline MouseExitEvent(const EventEmitter& emitter, const Point2& location, const Point2& absLocation):
        MouseEvent(emitter, EventType::MouseExit, MouseButton::None, location, absLocation, Size2()) { }
};

//! @brief
//! Shortcut constructor for a Wheel event.
//!
struct MouseWheelEvent : public MouseEvent
{
    //! @brief
    //! Creates a new MouseWheelEvent.
    //!
    inline MouseWheelEvent(const EventEmitter& emitter, const Point2& location, const Point2& absLocation, const Size2& delta):
        MouseEvent(emitter, EventType::MouseWheel, MouseButton::None, location, absLocation, delta) { }
};

//! @brief
//! A Key event.
//!
struct KeyEvent : public Event
{
    //! @brief
    //! The key pressed, as a unicode character.
    //!
    Char32 character;
    
    //! @brief
    //! The key modifiers pressed with the character.
    //!
    KeyModifiersMask modifiers;
    
    //! @brief
    //! The virtual key code.
    //!
    KeyCode keyCode;
    
    //! @brief
    //! Creates a new Key event instance.
    //!
    inline KeyEvent(const EventEmitter& emitter, 
                    EventType type,
                    Char32 character,
                    KeyCode keyCode,
                    const KeyModifiersMask& modifiers):
        Event(emitter, type), character(character), modifiers(modifiers), keyCode(keyCode) { }
};

ARA_END_NAMESPACE

#endif
