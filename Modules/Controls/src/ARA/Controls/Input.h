////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Controls/Input.h
//! @date
//!     2023/12/28
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_CONTROLS_INPUT_H__
#define __ARA_CONTROLS_INPUT_H__

#include "ARA/Controls/Control.h"
#include "ARA/Core/ControlKeys.h"
#include "ARA/Core/KeyCode.h"

ARA_CONTROLS_BEGIN_NS

//! @brief
//! An input interface to display a value as a text.
//!
class Input : public Control
{
    //! @brief
    //! The placeholder string.
    //!
    Text::String mPlaceholder;
    
    //! @brief
    //! A boolean true if the current displayed string is the placeholder.
    //!
    bool mDisplayPlaceholder;
    
    //! @brief
    //! A boolean true if the input has the focus.
    //!
    bool mHasFocus; 
    
    //! @brief
    //! The current cursor position.
    //!
    size_t mCursorPosition;
    
public:
    
    //! @brief
    //! Creates a new input instance.
    //!
    //! @param placeholder
    //!     The placeholder text. The text is displayed when the current text value
    //!     is empty.
    //! @param initialValue
    //!     The initial value for the input text.
    //!
    Input(const Text::String& placeholder, const Text::String& initialValue = {});
    
    //! @brief
    //! Sets the placeholder string.
    //!
    virtual void setPlaceholder(const Text::String& placeholder);
    
    //! @brief
    //! Returns the placeholder string.
    //!
    virtual const Text::String& placeholder() const;
    
protected:
    
    //! @brief
    //! Handles when the mouse is down on the input.
    //!
    //! @discussion
    //! The method sets the control as the current receiving element. It calls
    //! `ARA::Window::setInputElement` to achieve this. Then, it calls the `onGainFocus`
    //! method that resets the value string if the placeholder was displayed.
    //!
    virtual bool onMouseDown(const MouseDownEvent& event);
    
    //! @brief
    //! Called when the input shall gain focus.
    //!
    virtual bool onGainFocus();
    
    //! @brief
    //! Returns true because an input element shall be focusable.
    //!
    virtual bool willBecomeInputElement();
    
    //! @brief
    //! If the input has focus, inserts the character in the string at the current cursor
    //! position.
    //!
    virtual bool onKeyDown(const KeyEvent& event);
    
    //! @brief
    //! Updates the cursor position with the given index.
    //!
    virtual bool onClick(MouseButton button, const Point2& location, size_t index, Char32 character);
    
    //! @brief
    //! Handles a KeyCode before it is handled by the text frame.
    //!
    //! @return
    //! True if the KeyCode should **not** be displayed, false if the keycode can be
    //! inserted in the text frame.
    //!
    virtual bool handleNonPrintable(KeyCode keyCode);
};

typedef Ptr < Input > InputPtr;

ARA_CONTROLS_END_NS

#endif 
