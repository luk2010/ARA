//
//  ARADynLib.h
//  lui
//
//  Created by jacques tronconi on 26/11/2023.
//

#ifndef ARADynLib_h
#define ARADynLib_h

#include "ARAPlatform.h"
#include "ARAError.h"

ARA_BEGIN_NAMESPACE

//! @brief
//! An Error launched by a DynLib.
ARA_DECLARE_ERROR(DynLibError)

//! @brief
//! An object that loads a dynamic library.
class DynLib
{
    //! @brief
    //! The loaded library file path.
    std::string mFilePath;
    
    //! @brief
    //! The current handle.
    ARA_DYNLIB_T mHandle;
    
public:
    
    //! @brief
    //! Creates a new dynamic library.
    //! @param filePath
    //! The path where to load the library.
    DynLib(const std::string& filePath);
    
    //! @brief
    //! Closes the library.
    inline ~DynLib() { ARA_DYNLIB_CLOSE(mHandle); }
    
    //! @brief
    //! Returns a symbol in the library.
    inline void* find(const std::string_view& symbol) { return ARA_DYNLIB_DLSYM(mHandle, symbol.data()); }
    
    //! @brief
    //! Returns the dynamic library file path.
    inline const std::string& filePath() const { return mFilePath; }
};

ARA_END_NAMESPACE

#endif /* ARADynLib_h */
