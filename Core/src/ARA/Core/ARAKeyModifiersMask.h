////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Core/ARAKeyModifiersMask.h
//! @date
//!     2023/12/11
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_CORE_KEYMODIFIERSMASK_H__
#define __ARA_CORE_KEYMODIFIERSMASK_H__

#include "ARA/Core/ARAPlatform.h"

ARA_BEGIN_NAMESPACE

//! @brief
//! A bitfield structure that defines available modifiers for a key.
//!
struct KeyModifiersMask
{
    bool Shift :1 = false;
    bool Command :1 = false;
    bool Control :1 = false;
    bool Option :1 = false;
    bool Function :1 = false;
};

ARA_END_NAMESPACE

#endif
