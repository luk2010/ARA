////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Db/DbConnection.h
//! @date
//!     2023/12/24
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_DB_DBCONNECTION_H__
#define __ARA_DB_DBCONNECTION_H__

#include "ARA/Db/DbRequest.h"
#include "ARA/Db/DbResult.h"

ARA_BEGIN_NAMESPACE

//! @brief 
//! A function used to give only one result.
//! 
typedef std::function < void(const DbResult&) > DbResultPfn; 

//! @brief 
//! A function used to pass one or more results.
//! 
typedef std::function < void(const DbResultList&) > DbResultListPfn;

//! @brief 
//! Defines an interface to connect the Db Module to a database model.
//! 
class DbConnection 
{
public:

    //! @brief 
    //! Virtual destructor.
    //! 
    virtual ~DbConnection() = default; 

    //! @brief 
    //! Opens a new connection and calls the given callback.
    //! 
    //! @param str
    //!     The connection string to connect to the database. See the database
    //!     documentation (or the plugin documentation).
    //! @param callback
    //!     The function called when the connection is established (or if an error
    //!     occured).
    //! 
    //! @return 
    //! A std::future that you can wait for if you want to be sure everything happened
    //! correctly.
    //! 
    virtual std::future < void > open(const std::string& str, DbResultPfn callback) = 0;

    //! @brief 
    //! Executes a given request. 
    //! 
    //! @param req
    //!     The DbRequest object to execute. 
    //! @param callback 
    //!     The callback to call after the request has been executed. The results depend on 
    //!     the request type. Please refer to your database documentation. 
    //! 
    //! @return 
    //! A std::future that you can wait for if you want to be sure everything happened
    //! correctly.
    //! 
    virtual std::future < void > execute(const DbRequest& req, DbResultListPfn callback) = 0;
};

typedef Ptr < DbConnection > DbConnectionPtr;

ARA_END_NAMESPACE

#endif
