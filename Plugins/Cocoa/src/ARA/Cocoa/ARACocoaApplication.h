////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Cocoa/ARACocoaApplication.h
//! @date
//!     2023/12/08
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_COCOA_APPLICATION_H__
#define __ARA_COCOA_APPLICATION_H__

#include "ARACocoaPlatform.h"

#include "ARA/Core/ARAApplication.h"
#include "ARA/Core/ARAWindow.h"

//! @brief
//! An application object implemented for Cocoa.
//!
class OSXApplication : public ARA::Application
{
    //! @brief
    //! The NSApplication handle.
    //!
    NSApplication* mHandle;
    
    //! @brief
    //! The delegate handle.
    //!
    id<NSApplicationDelegate> mDelegate;
    
public:
    
    //! @brief
    //! Creates a new OSX Application.
    //!
    OSXApplication();
    
    //! @brief
    //! Runs the application.
    //!
    virtual int run(int argc = 0, const char** argv = NULL);
    
    //! @brief
    //! Terminates the application.
    //!
    virtual void terminate();
    
    //! @brief
    //! Creates a new window.
    //!
    virtual ARA::Ptr<ARA::Window> createWindow(const ARA::Size2& size, const ARA::WindowStyle& style, const std::string& title);
    
    //! @brief
    //! Creates a native view.
    //!
    virtual ARA::Ptr<ARA::View> createView(ARA::ViewController& controller);
    
    //! @brief
    //! Creates a native Path from an origin point.
    //!
    virtual ARA::Ptr<ARA::Path> createPath(const ARA::Point2& origin);
    
    //! @brief
    //! Creates a new font.
    //!
    //! @param familyName
    //!     The font family name to look for.
    //! @param size
    //!     The font size to load.
    //! @param traits
    //!     The font traits to apply to the font.
    //!
    //! @return
    //! A font instance if the font is found, nullptr otherwise.
    //! 
    virtual ARA::Ptr<ARA::Font> createFont(std::string_view familyName, ARA::Real size, ARA::Font::TraitsMask traits);
    
    //! @brief
    //! Returns the KeyCode for the given platform keycode.
    //!
    virtual ARA::KeyCode convertKeyCode(uint32_t keycode) const;
    
    //! @brief
    //! Returns the platform keycode for given KeyCode value.
    //!
    virtual uint32_t convertKeyCode(ARA::KeyCode keycode) const;
    
    //! @brief
    //! Returns the default RenderAPI for the current application.
    //!
    virtual ARA::RenderAPI getPreferredRenderAPI() const;
    
    //! @brief
    //! Returns the available RenderAPI for the current application.
    //!
    virtual ARA::RenderAPIList getAvailableRenderAPIs() const;
};

#endif
