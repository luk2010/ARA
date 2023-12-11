////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Controls/ControlState.h
//! @date
//!     2023/12/10
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_CONTROLS_CONTROLSTATE_H__
#define __ARA_CONTROLS_CONTROLSTATE_H__

#include "Platform.h"
#include "ARA/Core/ARAMouseButton.h"

ARA_CONTROLS_BEGIN_NS

//! @brief
//! The current mouse and keyboard state of a control.
//!
struct ControlState
{
    //! @brief
    //! A mouse button is currently pressed.
    //!
    bool MouseDown = false;
    
    //! @brief
    //! The current mouse button.
    //!
    MouseButton button = MouseButton::None;
    
    //! @brief
    //! A key is being pressed.
    //!
    bool KeyDown = false;
    
    //! @brief
    //! The key being pressed.
    //!
    Char32 key = 0;
};

ARA_CONTROLS_END_NS

#endif
