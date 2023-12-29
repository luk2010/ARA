////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/ControlKeys.h
//! @date
//!     2023/12/29
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_CONTROLKEYS_H__
#define __ARA_CONTROLKEYS_H__

#include "ARA/Core/ARAPlatform.h"

ARA_BEGIN_NAMESPACE

//! @brief
//! Enumerates basic control keys.
//!
enum class ControlKey
{
    Unknown,
    
    ArrowLeft,
    ArrowRight,
    ArrowUp,
    ArrowDown,
    
    Backspace,
    Return,
    
    Tabulate,
    Shift,
    CapsLock,
    Function,
    Control,
    Option,
    Command,
    Windows
};

ARA_END_NAMESPACE

#endif 
