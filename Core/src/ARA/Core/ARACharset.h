//
//  ARACharset.h
//  ARACore
//
//  Created by jacques tronconi on 27/11/2023.
//

#ifndef ARACharset_h
#define ARACharset_h

#include "ARAPlatform.h"

ARA_BEGIN_NAMESPACE

//! @brief
//! Defines the known charsets.
enum class Charset
{
    //! @brief The default Unicode charset.
    Unicode,
    
    //! @brief The Latin1 charset.
    Latin1,
    
    //! @brief The ASCII charset.
    ASCII
};

ARA_END_NAMESPACE

#endif /* ARACharset_h */
