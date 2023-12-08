////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Cocoa/OSXPath.mm
//! @date
//!     2023/12/08
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "OSXPath.h"

OSXPath::OSXPath(ARA::Application& app, CGMutablePathRef handle):
ARA::Path(app), mHandle(handle)
{
    
}

OSXPath::~OSXPath()
{
    CFRelease(mHandle);
}

ARA::Point2 OSXPath::cursor() const
{
    CGPoint curs = CGPathGetCurrentPoint(mHandle);
    return { curs.x, curs.y };
}

ARA::Path& OSXPath::moveTo(const ARA::Point2& point)
{
    CGPathMoveToPoint(mHandle, NULL, point.x, point.y);
    return *this;
}

ARA::Path& OSXPath::lineTo(const ARA::Point2& point)
{
    CGPathAddLineToPoint(mHandle, NULL, point.x, point.y);
    return *this;
}

ARA::Path& OSXPath::addQuad(const ARA::Point2& control, const ARA::Point2& to)
{
    CGPathAddQuadCurveToPoint(mHandle, NULL, control.x, control.y, to.x, to.y);
    return *this;
}

ARA::Path& OSXPath::addCubic(const ARA::Point2& control1, const ARA::Point2& control2, const ARA::Point2& to)
{
    CGPathAddCurveToPoint(mHandle, NULL, control1.x, control1.y, control2.x, control2.y, to.x, to.y);
    return *this;
}

ARA::Path& OSXPath::close()
{
    CGPathCloseSubpath(mHandle);
    return *this;
}

CGMutablePathRef OSXPath::handle() const
{
    return mHandle;
}
