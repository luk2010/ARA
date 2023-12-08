//
//  ARAError.h
//  ARA
//
//  Created by jacques tronconi on 26/11/2023.
//

#ifndef ARAError_h
#define ARAError_h

#include "ARAPlatform.h"

ARA_BEGIN_NAMESPACE

//! @brief
//! An Error launched by the ARA engine.
class Error : public std::exception
{
    //! @brief
    //! The error message.
    std::string mError;
    
public:
    
    //! @brief
    //! Creates a new Error.
    template < class... Params >
    Error(Params&&... params)
    {
        std::stringstream ss;
        ((ss << params), ...);
        mError = ss.str();
    }
    
    //! @brief
    //! Returns the error message.
    inline const char* what() const noexcept { return mError.data(); }
    
    //! @brief
    //! Returns the error message.
    inline const std::string& message() const { return mError; }
};

//! @brief
//! Throws an error only if a condition is true.
template < class T, class... Params >
inline void ThrowIf(bool cnd, Params&&... params)
{
    if (cnd)
        throw T(std::forward<Params>(params)...);
}

//! @brief
//! Declares a new ARA Error name.
#define ARA_DECLARE_ERROR(Name) struct Name : public ARA::Error { using ARA::Error::Error; };

//! @brief
//! An error for an invalid index.
//!
ARA_DECLARE_ERROR(IndexError) 

ARA_END_NAMESPACE

#endif /* ARAError_h */
