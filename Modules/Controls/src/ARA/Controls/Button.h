////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Controls/Button.h
//! @date
//!     2023/12/12
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_CONTROLS_BUTTON_H__
#define __ARA_CONTROLS_BUTTON_H__

#include "Control.h"
#include "ARA/Core/ARAElementStyle.h"

ARA_CONTROLS_BEGIN_NS

//! @brief
//! Defines a button control with three different styles: hover, focus and default.
//! 
class Button : public Control
{
    //! @brief
    //! The default style.
    //!
    ElementStylePtr mDefStyle;
    
    //! @brief
    //! The hover style.
    //!
    ElementStylePtr mHoverStyle;
    
    //! @brief
    //! The focus style.
    //!
    ElementStylePtr mFocusStyle;
    
    //! @brief
    //! True if the mouse is hovering the button.
    //!
    AtomBool mMouseHover;
    
public:
    
    //! @brief
    //! Sets the default style.
    //!
    virtual void setStyle(const ElementStylePtr& style);
    
    //! @brief
    //! Sets the default style.
    //!
    virtual void setStyle(const std::string& styleName);
    
    //! @brief
    //! The mouse entered the button.
    //!
    virtual bool onMouseEnter(const MouseEnterEvent& event);
    
    //! @brief
    //! The mouse exited the button.
    //!
    virtual bool onMouseExit(const MouseExitEvent& event);
    
protected:
    
    //! @brief
    //! Sets the hover, focus or default style depending on the current state.
    //!
    virtual void onStateChange(const ControlState& state);
};

ARA_CONTROLS_END_NS

#endif
