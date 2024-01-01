////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Core/Factory.h
//! @date
//!     2024/01/01
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_CORE_FACTORY_H__
#define __ARA_CORE_FACTORY_H__

#include "ARA/Core/ARAPlatform.h"

ARA_BEGIN_NAMESPACE

//! @brief
//! An abstract factory that you can define for each class.
//!
template < class Key, class Constructor >
class Factory
{
    //! @brief
    //! The constructors in the factory.
    //!
    std::map < Key, Constructor > mConstructors;
    
public:
    
    //! @brief
    //! Adds a new constructor to the factory.
    //!
    void add(const Key& key, const Constructor& constructor)
    {
        mConstructors[key] = constructor;
    }
    
    //! @brief
    //! Removes a constructor with given key.
    //!
    void remove(const Key& key)
    {
        auto it = mConstructors.find(key);
        if (it != mConstructors.end())
            mConstructors.erase(it);
    }
    
    //! @brief
    //! Constructs a new object with given key.
    //!
    auto construct(const Key& key) const
    {
        using T = decltype(Constructor()());
        auto it = mConstructors.find(key);
        
        if (it == mConstructors.end())
            return T{};
        
        return it->second();
    }
    
    //! @brief
    //! Returns all the constructors.
    //!
    const auto& constructors() const
    {
        return mConstructors;
    }
};

//! @brief
//! A special factory that has a single instance.
//!
template < class Key, class Constructor >
class SingleFactory : public Factory < Key, Constructor >
{
private:
    
    SingleFactory() {}
    SingleFactory(const SingleFactory&) = delete;
    SingleFactory& operator = (const SingleFactory&) = delete;
    
public:
    
    //! @brief
    //! Returns the single instance.
    //!
    static SingleFactory& Get()
    {
        static SingleFactory < Key, Constructor > instance;
        return instance;
    }
};

ARA_END_NAMESPACE

#endif
