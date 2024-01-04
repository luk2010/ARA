////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Hri/StoreAction.h
//! @date
//!     2024/01/04
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_HRI_STOREACTION_H__
#define __ARA_HRI_STOREACTION_H__

#include "ARA/Hri/Platform.h"

$ns(ARA, Hri)
{
    enum class StoreAction 
    {
        DontCare,
        Store, 
        Resolve, 
        StoreAndResolve
    };
}

#endif 