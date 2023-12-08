////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Cocoa/OSXDrawer.h
//! @date
//!     2023/12/08
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_COCOA_OSXDRAWER_H__
#define __ARA_COCOA_OSXDRAWER_H__

#include "ARACocoaPlatform.h"
#include "ARA/Core/ARADrawer.h"

//! @brief
//! A `ARA::Drawer` implemented with `NSGraphicsContext`.
//!
class OSXDrawer : public ARA::Drawer
{
    //! @brief
    //! The context handle.
    //!
    NSGraphicsContext* mHandle;
    
public:
    
    //! @brief
    //! Creates a drawer instance.
    //!
    OSXDrawer(ARA::Application& app, NSGraphicsContext* handle);
    
    //! @brief
    //! Pushes the current drawer graphics state.
    virtual void push();
    
    //! @brief
    //! Restores the previous graphics state.
    virtual void pop();
    
    //! @brief
    //! Sets the current fill color.
    virtual void setFillColor(const ARA::Color& color);
    
    //! @brief
    //! Sets the current stroke color.
    virtual void setStrokeColor(const ARA::Color& color);
    
    //! @brief
    //! Sets the current line width.
    virtual void setLineWidth(ARA::Real width);
    
    //! @brief
    //! Draws a filled path.
    virtual void fillPath(const ARA::Ptr<ARA::Path>& path);
    
    //! @brief
    //! Draws a stroked path.
    virtual void strokePath(const ARA::Ptr<ARA::Path>& path);
    
    //! @brief
    //! Moves the cursor to the given point.
    //!
    virtual void moveTo(const ARA::Point2& point);
    
    //! @brief
    //! Translates the Current Transformation Matrix by given point.
    //!
    virtual void translate(const ARA::Point2& p);
    
    //! @brief
    //! Scales the Current Transformation Matrix by given point.
    //!
    virtual void scale(const ARA::Point2& p);
};

#endif
