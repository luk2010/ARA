////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Cocoa/OSXDrawer.mm
//! @date
//!     2023/12/08
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "OSXDrawer.h"
#include "OSXPath.h"

OSXDrawer::OSXDrawer(ARA::Application& app, NSGraphicsContext* handle):
ARA::Drawer(app), mHandle(handle)
{
    /*CGAffineTransform transform = CGAffineTransformMakeScale(1, -1);
    CGContextSetTextMatrix(mHandle.CGContext, transform);
    CGContextConcatCTM(mHandle.CGContext, transform);*/
}

void OSXDrawer::push()
{
    [mHandle saveGraphicsState];
}

void OSXDrawer::pop()
{
    [mHandle restoreGraphicsState];
}

void OSXDrawer::setFillColor(const ARA::Color& color)
{
    [[NSColor colorWithRed:color.red
                     green:color.green
                      blue:color.blue
                     alpha:color.alpha] setFill];
}

void OSXDrawer::setStrokeColor(const ARA::Color& color)
{
    [[NSColor colorWithRed:color.red
                     green:color.green
                      blue:color.blue
                     alpha:color.alpha] setStroke];
}

void OSXDrawer::setLineWidth(ARA::Real width)
{
    CGContextSetLineWidth(mHandle.CGContext, width);
}

void OSXDrawer::fillPath(const ARA::Ptr<ARA::Path>& path)
{
    const OSXPath* ppath = dynamic_cast < const OSXPath* >(path.get());
    CGContextAddPath(mHandle.CGContext, ppath->handle());
    CGContextFillPath(mHandle.CGContext);
}

void OSXDrawer::strokePath(const ARA::Ptr<ARA::Path>& path)
{
    const OSXPath* ppath = dynamic_cast < const OSXPath* >(path.get());
    CGContextAddPath(mHandle.CGContext, ppath->handle());
    CGContextStrokePath(mHandle.CGContext);
}

void OSXDrawer::moveTo(const ARA::Point2& point)
{
    CGContextMoveToPoint(mHandle.CGContext, point.x, point.y);
}

void OSXDrawer::translate(const ARA::Point2& p)
{
    CGContextTranslateCTM(mHandle.CGContext, p.x, p.y);
}

void OSXDrawer::scale(const ARA::Point2& p)
{
    CGContextScaleCTM(mHandle.CGContext, p.x, p.y);
}
