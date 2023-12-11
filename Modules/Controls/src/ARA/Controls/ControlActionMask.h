////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Controls/ControlActionMask.h
//! @date
//!     2023/12/10
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_CONTROLS_CONTROLACTIONMASK_H__
#define __ARA_CONTROLS_CONTROLACTIONMASK_H__

#include "Platform.h"

ARA_CONTROLS_BEGIN_NS

//! @brief
//! A mask that sets the different events to trigger an action.
//!
struct ControlActionMask
{
    //! @brief
    //! The action is sent on a "click" event.
    //!
    bool Click :1 = true;
    
    //! @brief
    //! The action is sent on a "key-enter" event.
    //!
    bool KeyEnter :1 = true;
    
    //! @brief
    //! The action is sent on a "right click" event.
    //!
    bool RightClick :1 = false;
    
    //! @brief
    //! The action is sent on a custom function.
    //!
    bool CustomValidator :1 = false;
};

ARA_CONTROLS_END_NS

#endif
