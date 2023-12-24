////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Core/Blob.cpp
//! @date
//!     2023/12/21
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ARA/Core/Blob.h"

ARA_BEGIN_NAMESPACE

Blob::Blob(void* data, size_t size, bool destroy)
{
    mData = data; 
    mSizeInBytes = size; 
    mDestroyData = destroy; 
}

Blob::~Blob() 
{
    if (mData && mDestroyData) 
        free(mData);
}

bool Blob::operator==(const Blob& rhs) const 
{
    if (mSizeInBytes != rhs.size()) 
        return false; 

    if (mData == rhs.mData) 
        return true; 
    
    return !memcmp(mData, rhs.mData, mSizeInBytes);
}

bool Blob::isNull() const 
{
    return !mData || !mSizeInBytes; 
}

ARA_END_NAMESPACE