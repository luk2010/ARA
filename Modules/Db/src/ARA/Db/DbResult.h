////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Db/DbResult.h
//! @date
//!     2023/12/22
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_DB_DBRESULT_H__
#define __ARA_DB_DBRESULT_H__

#include "ARA/Db/DbData.h"

ARA_BEGIN_NAMESPACE

//! @brief 
//! A little structure that defines a column in a DbResult. 
//! 
struct DbResultColumn 
{
    //! @brief 
    //! The column name. 
    //! 
    std::string name; 

    //! @brief 
    //! The DbData value associated to the column. 
    //! 
    DbData value; 
};

//! @brief 
//! Defines multiple DbResultColumns. 
//!
typedef std::vector < DbResultColumn > DbResultColumnList;

//! @brief 
//! An object that stores the result of the execution of a `DbRequest` object by
//! a `DbConnection` object. 
//! 
class DbResult 
{
    //! @brief 
    //! The Error if the result is an error. 
    //! 
    Error mError; 

    //! @brief 
    //! The columns resulting from the request, if any. 
    //! 
    DbResultColumnList mColumns; 

    //! @brief 
    //! Boolean true if the result holds an error. 
    //! 
    bool mHasError; 

public: 

    //! @brief 
    //! Creates a new DbResult instance that stands for an error. 
    //! 
    DbResult(const Error& error);

    //! @brief 
    //! Creates a new DbResult instance that stands for a valid result, with columns
    //! or empty. 
    //! 
    DbResult(const DbResultColumnList& columns = {});

    //! @brief 
    //! Returns true if the result contains an error. 
    //! 
    bool hasError() const; 

    //! @brief 
    //! Returns the error in the result. 
    //! 
    const Error& error() const;

    //! @brief 
    //! Returns the number of columns in the result. 
    //! 
    size_t numberOfColumns() const; 

    //! @brief 
    //! Returns the column at given index. 
    //! 
    const DbResultColumn& column(size_t index) const; 

    //! @brief 
    //! Returns the column that has the given name.
    //! 
    const DbResultColumn& column(const std::string& name) const; 

    //! @brief 
    //! Returns an iterator to the first column. 
    //! 
    inline auto begin() const { return mColumns.begin(); }

    //! @brief 
    //! Returns the end iterator. 
    //! 
    inline auto end() const { return mColumns.end(); }
};

typedef std::vector < DbResult > DbResultList;

ARA_END_NAMESPACE

#endif 
