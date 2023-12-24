////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Db/DbData.h
//! @date
//!     2023/12/21
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_DB_DBDATA_H__
#define __ARA_DB_DBDATA_H__

#include "ARA/Db/DbPlatform.h"

ARA_BEGIN_NAMESPACE

typedef std::variant < bool, DbUInteger, DbInteger, DbReal, std::string, BlobPtr > 
DbDataUnion; 

//! @brief 
//! Defines an object that represents a storable data in a database. 
//! 
class DbData 
{
    //! @brief 
    //! The data variant. 
    //! 
    DbDataUnion mUnion; 

public: 

    //! @brief 
    //! Creates a DbData from a union value.
    //! 
    DbData(const DbDataUnion& data);

    //! @brief 
    //! Returns true if the data is a boolean. 
    //! 
    bool isBoolean() const; 

    //! @brief 
    //! Returns the boolean value. 
    //! 
    bool boolean() const;

    //! @brief 
    //! Returns true if the data is a DbUInteger. 
    //! 
    bool isUInteger() const; 

    //! @brief 
    //! Returns the DbUInteger value. 
    //! 
    DbUInteger uinteger() const;

    //! @brief 
    //! Returns true if the data is a DbInteger. 
    //! 
    bool isInteger() const; 

    //! @brief 
    //! Returns the DbInteger value. 
    //! 
    DbInteger integer() const;

    //! @brief 
    //! Returns true if the data is a DbReal. 
    //! 
    bool isReal() const; 

    //! @brief 
    //! Returns the DbReal value. 
    //! 
    DbReal real() const;

    //! @brief 
    //! Returns true if the data is a std::string. 
    //! 
    bool isString() const; 

    //! @brief 
    //! Returns the std::string value. 
    //! 
    const std::string& string() const;

    //! @brief 
    //! Returns true if the data is a `ARA::Blob`. 
    //! 
    bool isBlob() const; 

    //! @brief 
    //! Returns the `ARA::Blob value. 
    //! 
    BlobPtr blob() const;

    //! @brief 
    //! Returns true if this data is equal to a given data. 
    //! 
    bool operator == (const DbData& rhs) const;

    //! @brief 
    //! Returns true if this data is greater than another data. 
    //! 
    bool operator > (const DbData& rhs) const; 
};

typedef std::vector < DbData > DbDataList;
typedef std::map < std::string, DbData > DbDataDictionnary;

ARA_END_NAMESPACE

#endif 
