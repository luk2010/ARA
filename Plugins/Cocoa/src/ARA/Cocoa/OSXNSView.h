////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Cocoa/OSXNSView.h
//! @date
//!     2023/12/08
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_COCOA_OSXNSVIEW_H__
#define __ARA_COCOA_OSXNSVIEW_H__

#include "OSXView.h"

@interface OSXNSView : NSView
{
    OSXView* view;
    NSTrackingRectTag trackingRect;
    bool wasAcceptingMouseEvent;
}

- (instancetype) initWithView:(OSXView*)view;

- (void) setView:(OSXView*)view;

@end 

#endif
