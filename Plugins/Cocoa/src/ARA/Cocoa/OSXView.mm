////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Cocoa/OSXView.mm
//! @date
//!     2023/12/08
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "OSXView.h"
#include "OSXNSView.h"

#include "ARA/Core/ViewController.h"

OSXView::OSXView(ARA::Application& app, ARA::ViewController& controller, NSView* handle):
ARA::View(app, controller), mHandle(handle)
{
    if ([handle isKindOfClass:[OSXNSView class]])
        [(OSXNSView*)handle setView:this];
}

NSView* OSXView::handle() const
{
    return mHandle;
}

ARA::Rect2 OSXView::frame() const
{
    NSRect rect = mHandle.frame;
    return {{ rect.origin.x, rect.origin.y }, { rect.size.width, rect.size.height }};
}

void OSXView::setFrame(const ARA::Rect2& frame)
{
    [mHandle setFrame:NSMakeRect(frame.origin.x, 
                                 frame.origin.y,
                                 frame.size.width,
                                 frame.size.height)];
    
    setNeedsLayoutChildren(true);
}

void OSXView::setNeedsDraw(bool value)
{
    [mHandle setNeedsDisplay:value];
}

bool OSXView::needsDraw() const
{
    return mHandle.needsDisplay;
}

ARA::Rect2 OSXView::bounds() const
{
    NSRect rect = mHandle.bounds;
    return {{ rect.origin.x, rect.origin.y }, { rect.size.width, rect.size.height }};
}

void OSXView::setBounds(const ARA::Rect2& frame)
{
    [mHandle setBounds:NSMakeRect(frame.origin.x, 
                                  frame.origin.y,
                                  frame.size.width,
                                  frame.size.height)];
    
    setNeedsLayoutChildren(true);
}

bool OSXView::_addChild(const ARA::ViewPtr& child, const ARA::ViewPtr& beforeView)
{
    NSView* hdl = dynamic_cast < const OSXView* >(child.get())->handle();
    NSView* hdlBef = beforeView ? dynamic_cast < const OSXView* >(beforeView.get())->handle() : nil;
    
    [mHandle addSubview:hdl
             positioned:NSWindowBelow
             relativeTo:hdlBef];
    
    return true;
}

bool OSXView::_removeChild(const ARA::ViewPtr& child)
{
    NSView* hdl = dynamic_cast < const OSXView* >(child.get())->handle();
    
    [hdl removeFromSuperview];
    
    return true;
}
