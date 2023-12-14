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
    if (mDefStyle)
        mDefStyle->apply(*this);
    
    if (mMouseHover && mHoverStyle)
        mHoverStyle->apply(*this);
    
    if (state.MouseDown && mFocusStyle)
        mFocusStyle->apply(*this);
}

ARA_CONTROLS_END_NS
