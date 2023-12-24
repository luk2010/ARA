////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Db/DbConditionOperator.h
//! @date
//!     2023/12/21
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_DB_DBCONDITIONOPERATOR_H__
#define __ARA_DB_DBCONDITIONOPERATOR_H__

#include "ARA/Db/DbPlatform.h"

ARA_BEGIN_NAMESPACE

//! @brief 
//! Enumerates the available operators for a DbCondition. 
//! 
enum class DbConditionOperator
{
    Equal,
    NotEqual,
    GreaterThan,
    GreaterThanOrEqual,
    LessThan,
    LessThanOrEqual
};

ARA_END_NAMESPACE

#endif 