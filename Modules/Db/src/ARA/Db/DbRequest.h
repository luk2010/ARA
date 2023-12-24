////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Db/DbRequest.h
//! @date
//!     2023/12/21
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_DB_DBRREQUEST_H__
#define __ARA_DB_DBRREQUEST_H__

#include "ARA/Db/DbCondition.h"
#include "ARA/Db/DbRequestType.h"

ARA_BEGIN_NAMESPACE

//! @brief 
//! Defines a request object that can be passed to `DbConnection` to execute a 
//! database request. 
//! 
class DbRequest 
{
    //! @brief 
    //! The request type. 
    //! 
    DbRequestType mType; 

    //! @brief 
    //! The dictionnary of data if the request is a create, an update or a delete 
    //! type. Read types generally have conditions instead.
    //!
    DbDataDictionnary mKeyValues; 

    //! @brief 
    //! The conditions to apply to the request. For example, a SQL request will 
    //! define the `WHERE` keyword and apply each condition. 
    //! 
    DbConditionList mConditions;

public: 

    //! @brief 
    //! Creates a new request. 
    //! 
    DbRequest(DbRequestType type);

    //! @brief 
    //! Adds a key/value pair to the request.
    //! 
    void add(const std::string& key, const DbData& value);

    //! @brief 
    //! Adds a key/value pair to the request.
    //! 
    template < class D > 
    void add(const std::string& key, const D& data) 
    { add(key, DbData(data)); }

    //! @brief 
    //! Adds a condition to the request.
    //! 
    void add(const DbCondition& condition);

    //! @brief 
    //! Returns the request type.
    //! 
    inline DbRequestType type() const { return mType; }

    //! @brief 
    //! Returns the request key/values.
    //! 
    inline const DbDataDictionnary& data() const { return mKeyValues; }

    //! @brief 
    //! Returns the request conditions.
    //! 
    inline const DbConditionList& conditions() const { return mConditions; }
};

ARA_END_NAMESPACE

#endif 