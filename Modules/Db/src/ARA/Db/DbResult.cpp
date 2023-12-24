////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Db/DbResult.cpp
//! @date
//!     2023/12/22
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ARA/Db/DbResult.h"

ARA_BEGIN_NAMESPACE

DbResult::DbResult(const Error& error):
mError(error), mHasError(true)
{

}

DbResult::DbResult(const DbResultColumnList& columns):
mColumns(columns), mHasError(false)
{

}

bool DbResult::hasError() const 
{
    return mHasError; 
}

const Error& DbResult::error() const 
{
    if (!mHasError)
        throw Error("DbResult: No error.");

    return mError;
}

size_t DbResult::numberOfColumns() const 
{
    if (mHasError)
        return 0;

    return mColumns.size();
}

const DbResultColumn& DbResult::column(size_t index) const 
{
    if (mHasError) 
        throw Error("DbResult: No column available.");

    return mColumns.at(index);
}

const DbResultColumn& DbResult::column(const std::string& name) const 
{
    for (auto& column : mColumns)
        if (column.name == name)
            return column;
        
    throw Error("DbResult: Column '", name, "' not found.");
}

ARA_END_NAMESPACE