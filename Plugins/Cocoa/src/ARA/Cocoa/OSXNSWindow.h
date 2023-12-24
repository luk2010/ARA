////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Cocoa/OSXNSWindow.h
//! @date
//!     2023/12/24
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_COCOA_OSXNSWINDOW_H__
#define __ARA_COCOA_OSXNSWINDOW_H__

#include "OSXWindow.h"

//! @brief
//! Custom `NSWindow` interface that handles events to our `ARA::Window` object.
//! 
@interface OSXNSWindow : NSWindow
{
    OSXWindow* _window;
}

- (void)setOSXWindow:(OSXWindow*)window;

@end

#endif
