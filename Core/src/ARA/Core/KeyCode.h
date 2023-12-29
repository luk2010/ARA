////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Core/KeyCode.h
//! @date
//!     2023/12/29
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_CORE_KEYCODE_H__
#define __ARA_CORE_KEYCODE_H__

#include "ARA/Core/ARAPlatform.h"

ARA_BEGIN_NAMESPACE

//! @brief 
//! Enumerates device independant key codes.
//! 
enum class KeyCode 
{
    Unknown = 0, 

    A, 
    B, 
    C, 
    D, 
    E, 
    F, 
    G, 
    H, 
    I, 
    J, 
    K, 
    L, 
    M, 
    N, 
    O, 
    P, 
    Q, 
    R, 
    S, 
    T, 
    U, 
    V, 
    W, 
    X, 
    Y, 
    Z, 

    Zero, 
    One, 
    Two, 
    Three, 
    Four, 
    Five, 
    Six, 
    Seven, 
    Eight, 
    Nine, 

    Tabulate, 
    CapsLock, 
    Shift, 
    Control, 
    Option, 
    Command, 
    Backspace, 
    Return, 

    ArrowLeft,
    ArrowRight,
    ArrowUp,
    ArrowDown,

    F1, 
    F2, 
    F3, 
    F4, 
    F5, 
    F6, 
    F7, 
    F8, 
    F9, 
    F10
};

ARA_END_NAMESPACE

#endif 
