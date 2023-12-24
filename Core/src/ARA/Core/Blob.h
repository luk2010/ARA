////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Core/Blob.h
//! @date
//!     2023/12/21
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_CORE_BLOB_H__
#define __ARA_CORE_BLOB_H__

#include "ARA/Core/ARAPlatform.h"

ARA_BEGIN_NAMESPACE

//! @brief 
//! Defines an object that retain a block of arbitrary data. 
//! 
class Blob 
{
    //! @brief 
    //! The data size in bytes. 
    //! 
    size_t mSizeInBytes;

    //! @brief 
    //! The data pointer. 
    //! 
    void* mData; 
    
    //! @brief 
    //! A boolean true if the data must be destroyed. 
    //! 
    bool mDestroyData;

public: 

    //! @brief 
    //! Creates a new blob instance. 
    //! 
    //! @param data
    //!     The pointer to the data to retain. 
    //! @param size 
    //!     The data size in bytes. 
    //! @param destroy 
    //!     Boolean true by default that tells if the blob must destroy
    //!     the data or not. 
    //! 
    Blob(void* data, size_t size, bool destroy = true);
    
    //! @brief
    //! Utility constructor from a `std::vector` object.
    //!
    template < class T > Blob(const std::vector < T >& data):
    Blob(&data[0], sizeof(T) * data.size(), false) { }

    //! @brief 
    //! Destroys the blob and the stored data, if allowed to. 
    //! 
    virtual ~Blob(); 

    //! @brief 
    //! Returns the data. 
    //! 
    inline void* data() { return mData; }

    //! @brief 
    //! Returns the data. 
    //! 
    inline const void* data() const { return mData; }

    //! @brief 
    //! Returns the data size. 
    //! 
    inline size_t size() const { return mSizeInBytes; }

    //! @brief 
    //! Returns true if this blob has the same data as another blob.
    //! 
    bool operator == (const Blob& rhs) const; 

    //! @brief 
    //! Returns true if this blob has no data. 
    //! 
    bool isNull() const; 
};

typedef Ptr < Blob > BlobPtr;
typedef std::vector < BlobPtr > BlobList;

ARA_END_NAMESPACE

#endif 
