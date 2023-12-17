////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Cocoa/OSXWindow.h
//! @date
//!     2023/12/08
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_COCOA_OSXWINDOW_H__
#define __ARA_COCOA_OSXWINDOW_H__

#include "ARACocoaPlatform.h"
#include "ARA/Core/ARAWindow.h"

//! @brief
//! A `ARA::Window` implemented with `NSWindow`.
//!
class OSXWindow : public ARA::Window
{
    //! @brief
    //! The NSWindow handle.
    //!
    NSWindow* mHandle;
    
    //! @brief
    //! The delegate handle.
    //!
    id<NSWindowDelegate> mDelegate;
    
public:
    
    //! @brief
    //! Creates a new Window.
    //!
    OSXWindow(ARA::Application& app, NSWindow* handle);
    
    //! @brief
    //! Returns the window handle.
    //!
    NSWindow* handle() const;
    
    //! @brief
    //! Returns the window frame.
    //!
    virtual ARA::Rect2 frame() const;
    
    //! @brief
    //! Sets the window frame.
    //!
    virtual void setFrame(const ARA::Rect2& frame);
    
    //! @brief
    //! Returns the window content frame, i.e. the rectangle available for the window.
    //!
    virtual ARA::Rect2 contentFrame() const;
    
    //! @brief
    //! Returns the current window style.
    //!
    virtual ARA::WindowStyle style() const;
    
    //! @brief
    //! Sets the window style.
    //!
    virtual void setStyle(const ARA::WindowStyle& style);
    
    //! @brief
    //! Returns the window title.
    //!
    virtual std::string title() const;
    
    //! @brief
    //! Sets the window title.
    //!
    virtual void setTitle(std::string_view title);
    
    //! @brief
    //! Shows the window on screen.
    //!
    virtual void show();
    
    //! @brief
    //! Centers the window on the current screen.
    //!
    virtual void center();
    
    //! @brief
    //! Closes the window.
    //!
    virtual void close();
    
protected:
    
    //! @brief
    //! Sets the window's content view.
    //!
    virtual void _setContentView(ARA::View& view);
};

#endif
