////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Controls/Button.cpp
//! @date
//!     2023/12/14
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Button.h"
#include "ARA/Core/ElementStyleManager.h"

ARA_CONTROLS_BEGIN_NS

Button::Button(const Text::String& text):
Control(text), mMouseHover(false)
{
    
}

void Button::setStyle(const ElementStylePtr& style)
{
    if (mDefStyle != style)
    {
        mDefStyle = style;
        onStateChange(state());
    }
}

void Button::setStyle(const std::string& styleName)
{
    ElementStylePtr style = ElementStyleManager::Shared().find(styleName);
    
    ThrowIf < ElementStyleError >(!style, "[ARA::Controls::Button] Cannot find style '", styleName, "'.");
    
    setStyle(style);
}

void Button::setHoverStyle(const ElementStylePtr& style)
{
    if (mHoverStyle != style)
    {
        mHoverStyle = style;
        onStateChange(state());
    }
}

void Button::setHoverStyle(const std::string& styleName)
{
    ElementStylePtr style = ElementStyleManager::Shared().find(styleName);
    
    ThrowIf < ElementStyleError >(!style, "[ARA::Controls::Button] Cannot find style '", styleName, "'.");
    
    setHoverStyle(style);
}

void Button::setFocusStyle(const ElementStylePtr& style)
{
    if (mFocusStyle != style)
    {
        mFocusStyle = style;
        onStateChange(state());
    }
}

void Button::setFocusStyle(const std::string& styleName)
{
    ElementStylePtr style = ElementStyleManager::Shared().find(styleName);
    
    ThrowIf < ElementStyleError >(!style, "[ARA::Controls::Button] Cannot find style '", styleName, "'.");
    
    setFocusStyle(style);
}

bool Button::onMouseEnter(const MouseEnterEvent& event)
{
    mMouseHover = true;
    
    onStateChange(state());
    
    return true;
}

bool Button::onMouseExit(const MouseExitEvent& event)
{
    mMouseHover = false;
    
    onStateChange(state());
    
    return true;
}

void Button::onStateChange(const ControlState& state)
{
    if (state.MouseDown && mFocusStyle)
        mFocusStyle->apply(*this);
    
    else if (mMouseHover && mHoverStyle)
        mHoverStyle->apply(*this);
    
    else if (mDefStyle)
        mDefStyle->apply(*this);
}

ARA_CONTROLS_END_NS
