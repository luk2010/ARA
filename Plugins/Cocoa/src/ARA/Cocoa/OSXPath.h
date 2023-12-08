////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Cocoa/OSXPath.h
//! @date
//!     2023/12/08
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_COCOA_OSXPATH_H__
#define __ARA_COCOA_OSXPATH_H__

#include "ARACocoaPlatform.h"
#include "ARA/Core/ARAPath.h"

//! @brief
//! A `ARA::Path` implementation with CGPathRef.
//!
class OSXPath : public ARA::Path
{
    //! @brief
    //! The path handle.
    //!
    CGMutablePathRef mHandle;
    
public:
    
    //! @brief
    //! Creates a new path.
    //!
    OSXPath(ARA::Application& app, CGMutablePathRef handle);
    
    //! @brief
    //! Destroys the path.
    //!
    virtual ~OSXPath();
    
    //! @brief
    //! Returns the current cursor point.
    //!
    virtual ARA::Point2 cursor() const;
    
    //! @brief
    //! Moves the current cursor to a given point.
    //!
    virtual ARA::Path& moveTo(const ARA::Point2& point);
    
    //! @brief
    //! Adds a line to the given point.
    //!
    virtual ARA::Path& lineTo(const ARA::Point2& point);
    
    //! @brief
    //! Adds a bezier curve from one control point.
    //!
    virtual ARA::Path& addQuad(const ARA::Point2& control, const ARA::Point2& to);
    
    //! @brief
    //! Adds a Bezier curve from two control points.
    //!
    virtual ARA::Path& addCubic(const ARA::Point2& control1, const ARA::Point2& control2, const ARA::Point2& to);
    
    //! @brief
    //! Closes the Path by returning to the last moveTo point.
    //!
    virtual ARA::Path& close();
    
    //! @brief
    //! Returns the path handle.
    //!
    CGMutablePathRef handle() const;
};

#endif
