////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Controls/Input.cpp
//! @date
//!     2023/12/28
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ARA/Controls/Input.h"
#include "ARA/Core/ARAWindow.h"
#include "ARA/Text/ARATextFrame.h"

ARA_CONTROLS_BEGIN_NS

Input::Input(const Text::String& placeholder, const Text::String& initialValue):
Control(initialValue), mPlaceholder(placeholder)
{
    mDisplayPlaceholder = initialValue.isEmpty();
    mHasFocus = false;
    mCursorPosition = 0;
    
    ControlActionMask mask;
    mask.Click = false;
    mask.CustomValidator = false;
    mask.KeyEnter = true;
    mask.RightClick = false;
    setActionMask(mask);
    
    if (mDisplayPlaceholder)
        setString(placeholder);
}

void Input::setPlaceholder(const Text::String& placeholder)
{
    mPlaceholder = placeholder;
    
    if (mDisplayPlaceholder)
        setNeedsDisplay(true);
}

const Text::String& Input::placeholder() const
{
    return mPlaceholder;
}

bool Input::onMouseDown(const MouseDownEvent& event)
{
    bool res = false;
    
    // When we handle a mouse down event, if we don't already have the focus,
    // we call the onGainFocus() method which calls the Window's setInputElement
    // method.
    
    if (!mHasFocus)
    {
        if ((res = onGainFocus()))
            mHasFocus = true;
    }
    
    // We also calls the Control's onMouseDown implementation.
    
    res |= Control::onMouseDown(event);
    
    return res;
}

bool Input::onGainFocus()
{
    // When gaining focus, we try to set the current input element to this
    // element.
    
    auto& window = Element::window();
    
    window.setInputElement(shared_from_this());
    
    // We also sets the displayed string.
    
    if (mDisplayPlaceholder)
    {
        mDisplayPlaceholder = false;
        Control::setString(Text::String());
        setNeedsDisplay(true);
    }
    
    return true;
}

bool Input::willBecomeInputElement()
{
    return true;
}

bool Input::onKeyDown(const KeyEvent& event)
{
    if (!mHasFocus)
        return false;
    
    // We first call Control::onKeyDown. If it returns true, then the key
    // has been used for the action subsystem. If it returns false, then
    // we try to insert the character at the given cursor point.
    
    if (!Control::onKeyDown(event))
    {
        if (handleNonPrintable(event.keyCode))
            return true;
        
        auto& frame = Text::Element::textFrame();
        
        frame.insert(mCursorPosition, Text::String(&event.character, 1, Text::StringEncoding::Utf32));
        
        setNeedsLayout(true);
        mCursorPosition++;
        
        return true;
    }
}

bool Input::onClick(MouseButton button, const Point2& location, size_t index, Char32 character)
{
    if (button == MouseButton::Left)
    {
        mCursorPosition = index;
        return true;
    }
    
    return false;
}

bool Input::handleNonPrintable(KeyCode keyCode)
{
    switch (keyCode)
    {
        case KeyCode::ArrowLeft:
            mCursorPosition = mCursorPosition ? mCursorPosition - 1 : 0;
            return true;
            
        case KeyCode::ArrowRight:
            mCursorPosition = (mCursorPosition < textFrame().string().length()) ? mCursorPosition++ : mCursorPosition;
            return true;
            
        case KeyCode::ArrowUp:
            mCursorPosition = textFrame().getIndexInLineAbove(mCursorPosition);
            return true;
            
        case KeyCode::ArrowDown:
            mCursorPosition = textFrame().getIndexInLineBelow(mCursorPosition);
            return true;
            
        case KeyCode::Backspace:
            if (mCursorPosition > 0)
            {
                textFrame().remove(mCursorPosition - 1);
                mCursorPosition--;
            }
            return true;
            
        default:
            return false;
    }
}

ARA_CONTROLS_END_NS
