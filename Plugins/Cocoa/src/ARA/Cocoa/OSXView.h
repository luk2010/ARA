////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Cocoa/OSXView.h
//! @date
//!     2023/12/08
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_COCOA_OSXVIEW_H__
#define __ARA_COCOA_OSXVIEW_H__

#include "ARACocoaPlatform.h"
#include "ARA/Core/ARAView.h"

//! @brief
//! A `ARA::View` implemented with Cocoa `NSView` handle.
//!
class OSXView : public ARA::View
{
    //! @brief
    //! The view handle.
    //!
    NSView* mHandle;
    
public:
    
    //! @brief
    //! Creates a new view.
    //!
    OSXView(ARA::Application& app, NSView* handle);
    
    //! @brief
    //! Returns the NSView handle.
    //!
    NSView* handle() const; 
    
    //! @brief
    //! Adds a child to this view.
    //!
    virtual ARA::Ptr<ARA::View> addChild(const ARA::Ptr<ARA::View>& child, const ARA::Ptr<ARA::View>& beforeView);
    
    //! @brief
    //! Removes a child from this view.
    //!
    virtual void removeChild(const ARA::Ptr<ARA::View>& child);
    
    //! @brief
    //! Returns the current view frame.
    //!
    virtual ARA::Rect2 frame() const;
    
    //! @brief
    //! Sets the current view frame.
    //!
    virtual void setFrame(const ARA::Rect2& frame);
    
    //! @brief
    //! Sets weither the view needs a redraw.
    //!
    virtual void setNeedsDraw(bool value);
    
    //! @brief
    //! Returns true if the view currently needs to be redrawn.
    //!
    virtual bool needsDraw() const;
    
    //! @brief
    //! Returns the view's bounds.
    //!
    virtual ARA::Rect2 bounds() const;
    
    //! @brief
    //! Sets the view's bounds.
    //!
    virtual void setBounds(const ARA::Rect2& rect);
};

#endif
