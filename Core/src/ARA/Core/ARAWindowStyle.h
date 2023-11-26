//
//  ARAWindowStyle.h
//  ARA
//
//  Created by jacques tronconi on 26/11/2023.
//

#ifndef ARAWindowStyle_h
#define ARAWindowStyle_h

#include "ARAPlatform.h"

ARA_BEGIN_NAMESPACE

//! @brief
//! A bitset that defines common window styles.
struct WindowStyle
{
    bool closable :1 = true;
    bool resizable :1 = false;
    bool titled :1 = true;
    bool fullContentSize :1 = false;
    bool fullScreen :1 = false;
};

ARA_END_NAMESPACE

#endif /* ARAWindowStyle_h */
