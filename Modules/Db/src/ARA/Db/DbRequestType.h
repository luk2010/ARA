////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Db/DbPlatform.h
//! @date
//!     2023/12/21
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_DB_DBREQUESTTYPE_H__
#define __ARA_DB_DBREQUESTTYPE_H__

#include "ARA/Db/DbPlatform.h"

ARA_BEGIN_NAMESPACE

//! @brief 
//! Enumerates the basic CRUD request types. 
//! 
enum class DbRequestType 
{
    Create,
    Read,
    Update,
    Delete
};

ARA_END_NAMESPACE

#endif 