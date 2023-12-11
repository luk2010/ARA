////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Controls/Control.cpp
//! @date
//!     2023/12/10
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Control.h"

ARA_CONTROLS_BEGIN_NS

Control::Control(const Text::String& string):
ARA::Text::Element(string)
{
    
}

bool Control::action()
{
    return false;
}

ControlActionMask Control::actionMask() const
{
    return mActionMask;
}

void Control::setActionMask(ControlActionMask mask)
{
    mActionMask = mask;
}

ControlActionValidatorPtr Control::actionValidator() const
{
    return mActionValidator;
}

void Control::setActionValidator(const ControlActionValidatorPtr& validator)
{
    mActionValidator = validator;
}

bool Control::handleEvent(const Event& event)
{
    if (!ARA::Text::Element::handleEvent(event))
    {
        if (mActionValidator && mActionValidator->validate(*this, event))
            return action();
        
        return false;
    }
    
    return true;
}

bool Control::onMouseDown(const MouseDownEvent& event)
{
    mState.MouseDown = true;
    mState.button = event.button;
    return false;
}

bool Control::onMouseUp(const MouseUpEvent& event)
{
    if (mState.MouseDown)
    {
        mState.MouseDown = false;
        mState.button = MouseButton::None;
        
        if (event.button == MouseButton::Left && mActionMask.Click)
            return action();
        
        else if (event.button == MouseButton::Right && mActionMask.RightClick)
            return action();
    }
    
    return false;
}

bool Control::onKeyDown(const KeyEvent& event)
{
    if (event.character == U'\n' && mActionMask.KeyEnter)
        return action();
    
    mState.KeyDown = true;
    mState.key = event.character;
    
    return false;
}

bool Control::onKeyUp(const KeyEvent& event)
{
    mState.KeyDown = false;
    mState.key = 0;
    return false;
}

void Control::onStateChange(const ControlState& state)
{
    
}

ARA_CONTROLS_END_NS
