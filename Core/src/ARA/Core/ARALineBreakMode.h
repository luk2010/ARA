////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Core/ARALineBreakMode.h
//! @date
//!     2023/12/08
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_CORE_LINEBREAKMODE_H__
#define __ARA_CORE_LINEBREAKMODE_H__

#include "ARAPlatform.h"

ARA_BEGIN_NAMESPACE

//! @brief 
//! Declares known line break rules.
//!
enum class LineBreakMode
{
    //! @brief 
    //! The line is broken at the overflow letter.
    Letter,

    //! @brief 
    //! The line is broken at the overflow word.
    Word
};

ARA_END_NAMESPACE

#endif 
