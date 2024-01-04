////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Cocoa/Metal/RenderView.mm
//! @date
//!     2023/12/30
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "RenderView.h"
#include "AAViewMTL.h"

RenderViewMTL::RenderViewMTL(ARA::Application& app, ARA::RenderViewController& controller):
ARA::RenderView(app, controller)
{
    AAViewMTL* handle = [[AAViewMTL alloc] initWithView:this];
    handle.metalLayer.device = MTLCreateSystemDefaultDevice();
    handle.metalLayer.pixelFormat = MTLPixelFormatRGBA8Unorm_sRGB;
    handle.paused = NO;
    
    mHandle = handle;
}

NSView* RenderViewMTL::handle() const
{
    return mHandle;
}

ARA::Rect2 RenderViewMTL::frame() const
{
    NSRect rect = mHandle.frame;
    return {{ rect.origin.x, rect.origin.y }, { rect.size.width, rect.size.height }};
}

void RenderViewMTL::setFrame(const ARA::Rect2& frame)
{
    [mHandle setFrame:NSMakeRect(frame.origin.x,
                                 frame.origin.y,
                                 frame.size.width,
                                 frame.size.height)];
    
    setNeedsLayoutChildren(true);
}

void RenderViewMTL::setNeedsDraw(bool value)
{
    [mHandle setNeedsDisplay:value];
}

bool RenderViewMTL::needsDraw() const
{
    return mHandle.needsDisplay;
}

ARA::Rect2 RenderViewMTL::bounds() const
{
    NSRect rect = mHandle.bounds;
    return {{ rect.origin.x, rect.origin.y }, { rect.size.width, rect.size.height }};
}

void RenderViewMTL::setBounds(const ARA::Rect2& frame)
{
    [mHandle setBounds:NSMakeRect(frame.origin.x,
                                  frame.origin.y,
                                  frame.size.width,
                                  frame.size.height)];
    
    setNeedsLayoutChildren(true);
}

ARA::PixelFormat RenderViewMTL::pixelFormat() const
{
    return ARA::PixelFormat::RGBA8UnormSRGB;
}

bool RenderViewMTL::_addChild(const ARA::ViewPtr& child, const ARA::ViewPtr& beforeView)
{
    return false;
}

bool RenderViewMTL::_removeChild(const ARA::ViewPtr& child)
{
    return false;
}
