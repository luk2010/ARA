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

OSXView::OSXView(ARA::Application& app, NSView* handle):
ARA::View(app), mHandle(handle)
{
    if ([handle isKindOfClass:[OSXNSView class]])
        [(OSXNSView*)handle setView:this];
}

NSView* OSXView::handle() const
{
    return mHandle;
}

ARA::Ptr<ARA::View> OSXView::addChild(const ARA::Ptr<ARA::View>& child, const ARA::Ptr<ARA::View>& beforeView)
{
    NSView* hdl = dynamic_cast < const OSXView* >(child.get())->handle();
    NSView* hdlBef = beforeView ? dynamic_cast < const OSXView* >(child.get())->handle() : nil;
    
    [mHandle addSubview:hdl
             positioned:NSWindowBelow
             relativeTo:hdlBef];
    
    mChildrenNodes.insert(std::find(mChildrenNodes.begin(), mChildrenNodes.end(), beforeView), child);
    setParentView(*child, shared_from_this());
    
    auto observer = this->observer();
    
    if (observer)
        observer->onViewAddChild(*this, child);
    
    observer = child->observer();
    
    if (observer)
        observer->onViewParentChange(*child, shared_from_this());
    
    return child;
}

void OSXView::removeChild(const ARA::Ptr<ARA::View>& child)
{
    NSView* hdl = dynamic_cast < const OSXView* >(child.get())->handle();
    [hdl removeFromSuperview];
    
    setParentView(*child, nullptr);
    
    mChildrenNodes.erase(std::find(mChildrenNodes.begin(), mChildrenNodes.end(), child));
    
    auto observer = this->observer();
    
    if (observer)
        observer->onViewRemoveChild(*this, child);
    
    observer = child->observer();
    
    if (observer)
        observer->onViewParentChange(*child, nullptr);
}

ARA::Rect2 OSXView::frame() const
{
    NSRect rect = mHandle.frame;
    return {{ rect.origin.x, rect.origin.y }, { rect.size.width, rect.size.height }};
}

void OSXView::setFrame(const ARA::Rect2& frame)
{
    [mHandle setFrame:NSMakeRect(frame.origin.x, frame.origin.y, frame.size.width, frame.size.height)];
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
    [mHandle setBounds:NSMakeRect(frame.origin.x, frame.origin.y, frame.size.width, frame.size.height)];
}
