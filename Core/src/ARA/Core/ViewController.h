////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Core/ViewController.h
//! @date
//!     2023/12/14
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_CORE_VIEWCONTROLLER_H__
#define __ARA_CORE_VIEWCONTROLLER_H__

#include "ARA/Core/ARAView.h"
#include "ARA/Core/ARAEventListener.h"

ARA_BEGIN_NAMESPACE

//! @brief
//! An object that manages the lifetime of a `ARA::View`.
//!
//! @discussion
//! As `ARA::View` is platform dependent, this class is made to create and destroy automatically
//! the underlying view object.
//!
class ViewController : public EventListener
{
    friend class View;
    
    //! @brief
    //! The view this controller manages.
    //!
    ViewPtr mView;
    
    //! @brief
    //! A class that defines a custom listener that redirects all events to the owning
    //! view controller.
    //!
    //! @discussion
    //! This class is needed because we create the view inside the view controller. Because of
    //! that, `shared_from_this()` is not available.
    //!
    struct CustomListener : public EventListener
    {
        //! @brief
        //! Ourself.
        //!
        ViewController& controller;
        
        //! @brief
        //! Constructs a new instance.
        //!
        inline CustomListener(ViewController& controller): controller(controller) {}
        
        //! @brief
        //! Redirects all events to the controller.
        //!
        inline bool handleEvent(const Event& event) { return controller.handleEvent(event); }
    };
    
    //! @brief
    //! The local event listener used to listen to the view events.
    //!
    EventListenerPtr mLocalListener;
    
protected:
    
    //! @brief
    //! Creates a new controller instance with its own view.
    //!
    ViewController(const Ptr < View >& view);
    
public:
    
    //! @brief
    //! Creates a new controller instance with its own view.
    //!
    ViewController();
    
    //! @brief
    //! Returns the view the controller manages.
    //!
    virtual View& view();
    
    //! @brief
    //! Returns the view the controller manages.
    //!
    virtual const View& view() const;
    
    //! @brief
    //! Returns the view's frame.
    //!
    virtual Rect2 frame() const;
    
    //! @brief
    //! Sets the view's frame.
    //!
    virtual void setFrame(const Rect2& frame);
    
protected:
    
    //! @brief
    //! Updates the view.
    //!
    virtual void update();
    
    //! @brief
    //! Draws the view.
    //!
    virtual void draw(Drawer& drawer) const;
    
    //! @brief
    //! Notifiates the controller the view will be attached to a new window.
    //!
    //! @param window
    //!     The window the view will be attached to.
    //!
    //! @return
    //! True by default, false if the view cannot be attached to the given window.
    //!
    virtual bool willMoveToWindow(const Window& window);
    
    //! @brief
    //! Notifiates the controller the view has been attached to a new window.
    //!
    virtual void didMoveToWindow();
    
    //! @brief
    //! Notifiates the controller the view will be attached to a new parent view.
    //!
    //! @param parent
    //!     The parent the view will be attached to.
    //!
    //! @return
    //! True by default, false if the view cannot be attached to the given parent view.
    //!
    virtual bool willMoveToView(const View& parent);
    
    //! @brief
    //! Notifiates the controller the view has been attached to a new parent view.
    //!
    virtual void didMoveToView();
    
    //! @brief
    //! Notifiates the controller a child has been added to the view.
    //!
    virtual void didAddChild(View& child);
    
    //! @brief
    //! Notifiates the controller a child has been removed from the view.
    //!
    virtual void didRemoveChild(View& child);
    
    //! @brief
    //! Notifiates the view it has been detached from its parent view.
    //!
    virtual void didMoveFromView();
    
    //! @brief
    //! Notifiates the view it has been detached from its parent window.
    //!
    virtual void didMoveFromWindow();
    
    //! @brief
    //! Sets the current view for the controller.
    //!
    virtual void setView(const ViewPtr& view);
};

ARA_END_NAMESPACE

#endif
