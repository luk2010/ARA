////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Db/DbData.cpp
//! @date
//!     2023/12/21
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ARA/Db/DbData.h"
#include "ARA/Core/ARAError.h"

ARA_BEGIN_NAMESPACE

DbData::DbData(const DbDataUnion& data):
mUnion(data)
{
    
}

bool DbData::isBoolean() const
{
    return mUnion.index() == 0;
}

bool DbData::boolean() const
{
    try
    {
        return std::get < 0 >(mUnion);
    }
    catch(const std::exception& err)
    {
        throw BadCast("[DbData] data is not a boolean.");
    }
}

bool DbData::isUInteger() const
{
    return mUnion.index() == 1;
}

DbUInteger DbData::uinteger() const
{
    try
    {
        return std::get < 1 >(mUnion);
    }
    catch(const std::exception& err)
    {
        throw BadCast("[DbData] data is not a DbUInteger.");
    }
}

bool DbData::isInteger() const
{
    return mUnion.index() == 2;
}

DbInteger DbData::integer() const
{
    try
    {
        return std::get < 2 >(mUnion);
    }
    catch(const std::exception& err)
    {
        throw BadCast("[DbData] data is not a DbInteger.");
    }
}

bool DbData::isReal() const
{
    return mUnion.index() == 3;
}

DbReal DbData::real() const
{
    try
    {
        return std::get < 3 >(mUnion);
    }
    catch(const std::exception& err)
    {
        throw BadCast("[DbData] data is not a DbReal.");
    }
}

bool DbData::isString() const
{
    return mUnion.index() == 4;
}

const std::string& DbData::string() const
{
    try
    {
        return std::get < 4 >(mUnion);
    }
    catch(const std::exception& err)
    {
        throw BadCast("[DbData] data is not a std::string.");
    }
}

bool DbData::isBlob() const
{
    return mUnion.index() == 5;
}

BlobPtr DbData::blob() const
{
    try
    {
        return std::get < 5 >(mUnion);
    }
    catch(const std::exception& err)
    {
        throw BadCast("[DbData] data is not a Blob.");
    }
}

bool DbData::isEmpty() const
{
    return mUnion.index() == 6;
}

bool DbData::operator == (const DbData& rhs) const 
{
    if (mUnion.index() != rhs.mUnion.index())
        return false; 
    
    if (isEmpty())
        return true;

    switch (mUnion.index())
    {
        case 0:
            return std::get < 0 >(mUnion) == std::get < 0 >(rhs.mUnion);

        case 1:
            return std::get < 1 >(mUnion) == std::get < 1 >(rhs.mUnion);

        case 2:
            return std::get < 2 >(mUnion) == std::get < 2 >(rhs.mUnion);

        case 3:
            return std::get < 3 >(mUnion) == std::get < 3 >(rhs.mUnion);

        case 4:
            return std::get < 4 >(mUnion) == std::get < 4 >(rhs.mUnion);

        case 5:
            return (*std::get < 5 >(mUnion)) == (*std::get < 5 >(rhs.mUnion));
    }

    return false;
}

bool DbData::operator > (const DbData& rhs) const 
{
    if (mUnion.index() != rhs.mUnion.index() || isEmpty())
        return false;

    switch (mUnion.index())
    {
        case 1: 
            return std::get<1>(mUnion) > std::get<1>(rhs.mUnion);

        case 2: 
            return std::get<2>(mUnion) > std::get<2>(rhs.mUnion);

        case 3: 
            return std::get<3>(mUnion) > std::get<3>(rhs.mUnion);

        default: 
            throw Error("[DbData] data is not numeric and cannot be compared.");
    }
}

ARA_END_NAMESPACE
