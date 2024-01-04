////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Cocoa/Metal/RenderView.h
//! @date
//!     2023/12/30
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_COCOA_METAL_RENDERVIEW_H__
#define __ARA_COCOA_METAL_RENDERVIEW_H__

#include "../OSXView.h"
#include "ARA/Core/RenderView.h"

//! @brief
//! Defines a render view that instantiates a AAViewMTL.
//!
class RenderViewMTL : public ARA::RenderView
{
    //! @brief
    //! The `AAViewMTL*` handle.
    //!
    NSView* mHandle;
    
public:
    
    //! @brief
    //! Creates the RenderViewMTL instance.
    //!
    RenderViewMTL(ARA::Application& app, ARA::RenderViewController& controller);
    
    //! @brief
    //! Returns the NSView handle.
    //!
    NSView* handle() const;
    
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
    
    //! @brief
    //! Returns the PixelFormat used with this RenderView.
    //!
    virtual ARA::PixelFormat pixelFormat() const;
    
protected:
    
    //! @brief
    //! Adds a child to this view.
    //!
    virtual bool _addChild(const ARA::ViewPtr& child, const ARA::ViewPtr& beforeView);
    
    //! @brief
    //! Removes a child from this view.
    //!
    virtual bool _removeChild(const ARA::ViewPtr& child);
};

#endif
