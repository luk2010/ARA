////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Db/DbModel.h
//! @date
//!     2023/12/24
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_DB_DBMODEL_H__
#define __ARA_DB_DBMODEL_H__

#include "ARA/Db/DbConnection.h"

ARA_BEGIN_NAMESPACE

//! @brief 
//! Common interface for a CRUD model. 
//! 
template < class M > 
class DbModel 
{
    //! @brief 
    //! The DbConnection used by the model. 
    //! 
    DbConnection& mConnection; 

    //! @brief 
    //! The model name. This property can be useful when you select a table for
    //! exampe in SQL, or when selecting a database.
    //! 
    std::string mName;  

public: 

    //! @brief 
    //! Creates a new instance of DbModel. 
    //! 
    DbModel(DbConnection& connection, const std::string& name): 
    mConnection(connection), mName(name) {}

    //! @brief 
    //! Returns the model name. 
    //! 
    const std::string& name() const { return mName; }

    //! @brief 
    //! Returns the model connection. 
    //! 
    DbConnection& connection() { return mConnection; }

    //! @brief 
    //! Returns the model connection. 
    //! 
    const DbConnection& connection() const { return mConnection; }

    //! @brief 
    //! Creates a new instance of M in the database. 
    //! 
    virtual std::future < void >
    create(const M& data, DbResultPfn callback = {}) = 0;

    //! @brief 
    //! Reads in the database and returns the selected data that corresponds to the
    //! given condition list. 
    //! 
    virtual std::future < std::vector < M > > 
    read(const DbConditionList& conditions = {}, DbResultListPfn callback = {}) = 0;

    //! @brief 
    //! Updates the given data. 
    //! 
    virtual std::future < void > 
    update(const M& data, DbResultPfn callback = {}) = 0;

    //! @brief 
    //! Deletes the given data. 
    //! 
    virtual std::future < void > 
    destroy(const M& data, DbResultPfn callback = {}) = 0;
};

ARA_END_NAMESPACE

#endif 