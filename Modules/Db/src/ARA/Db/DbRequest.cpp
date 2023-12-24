////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Db/DbRequest.cpp
//! @date
//!     2023/12/21
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ARA/Db/DbRequest.h"

ARA_BEGIN_NAMESPACE

DbRequest::DbRequest(DbRequestType type):
mType(type) 
{

}

void DbRequest::add(const std::string& key, const DbData& value)
{
    mKeyValues[key] = value;
}

void DbRequest::add(const DbCondition& condition)
{
    mConditions.push_back(condition);
}

ARA_END_NAMESPACE