//
//  ARAInheritable.h
//  ARA
//
//  Created by jacques tronconi on 26/11/2023.
//

#ifndef ARAInheritable_h
#define ARAInheritable_h

#include "ARAPlatform.h"

ARA_BEGIN_NAMESPACE

//! @brief
//! A structure that represents the inherits value.
struct Inherits {};

//! @brief
//! An object that holds a Inherits or another value.
template < class T >
class Inheritable
{
    //! @brief
    //! The internal value.
    std::variant<T, Inherits> mValue;
    
public:
    
    //! @brief
    //! Creates a new value from a value.
    Inheritable(const T& value = {}): mValue(value) {}
    
    //! @brief
    //! Creates a new value from its inheritable value.
    Inheritable(Inherits inherits): mValue(inherits) {}
    
    //! @brief
    //! Returns true if value is a real value.
    bool isValue() const { return mValue.index() == 0; }
    
    //! @brief
    //! Returns true if value is an Inherits.
    bool isInherits() const { return mValue.index() == 1; }
    
    //! @brief
    //! Returns the value.
    const T& value() const { return std::get<0>(mValue); };
    
    //! @brief
    //! Sets the value.
    void setValue(const T& value) { mValue = value; }
    
    //! @brief
    //! Sets the value.
    void setValue(Inherits value) { mValue = value; }
    
    //! @brief
    //! Returns true if the value is equal to a given value.
    bool isEqualTo(const T& value) const { return isValue() ? std::get<0>(mValue) == value : false; }
    
    //! @brief
    //! Returns true if the value is inherits.
    bool isEqualTo(Inherits inherits) const { return isInherits(); }
    
    //! @brief
    //! Returns true if the value is equal to another Inheritable object.
    bool isEqualTo(const Inheritable& rhs) const
    {
        if (isValue() && rhs.isValue())
            return value() == rhs.value();
        
        else if (isInherits() && rhs.isInherits())
            return true;
        
        return false;
    }
};

ARA_END_NAMESPACE

#endif /* ARAInheritable_h */
