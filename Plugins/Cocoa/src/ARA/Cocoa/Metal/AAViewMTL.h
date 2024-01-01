////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Cocoa/Metal/AAViewMTL.h
//! @date
//!     2023/12/29
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_COCOA_METAL_AAVIEWMTL_H__
#define __ARA_COCOA_METAL_AAVIEWMTL_H__

#include "../OSXNSView.h"
#include "Platform.h"

//! @brief
//! A derived class from OSXNSView to handle Metal devices.
//!
@interface AAViewMTL : OSXNSView < CALayerDelegate >

@property (nonatomic, nonnull, readonly) CAMetalLayer* metalLayer;

@property (nonatomic, getter=isPaused) BOOL paused;

@end

#endif
