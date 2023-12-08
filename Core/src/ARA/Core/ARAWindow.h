//
//  ARAWindow.h
//  ARA
//
//  Created by jacques tronconi on 26/11/2023.
//

#ifndef ARAWindow_h
#define ARAWindow_h

#include "ARAView.h"
#include "ARAWindowStyle.h"

ARA_BEGIN_NAMESPACE

//! @brief
//! A Window common class.
class Window : public ApplicationObject,
               public std::enable_shared_from_this<Window>
{
public:
    
    //! @brief
    //! The Window Observer.
    struct Observer
    {
        //! @brief
        //! Destructor.
        virtual ~Observer() = default;
        
        //! @brief
        //! A Window has been moved.
        virtual void onWindowMove(Window& window, const Point2& location) {}
        
        //! @brief
        //! A Window has been resized.
        virtual void onWindowResize(Window& window, const Size2& size) {}
        
        //! @brief
        //! A Window will close.
        virtual void onWindowClose(Window& window) {}
    };
    
protected:
    
    //! @brief
    //! The Window Observer.
    Weak<Observer> mObserver;
    
    //! @brief
    //! The content view.
    Ptr<View> mContentView;
    
public:
    
    //! @brief
    //! Creates a new window.
    //! @param app
    //! The application that creates the window.
    inline Window(Application& app): ApplicationObject(app) {}
    
    //! @brief
    //! Returns the window frame.
    virtual Rect2 frame() const = 0;
    
    //! @brief
    //! Sets the window frame.
    virtual void setFrame(const Rect2& frame) = 0;
    
    //! @brief
    //! Returns the window content frame, i.e. the rectangle available for the window.
    virtual Rect2 contentFrame() const = 0;
    
    //! @brief
    //! Returns the current window style.
    virtual WindowStyle style() const = 0;
    
    //! @brief
    //! Sets the window style.
    virtual void setStyle(const WindowStyle& style) = 0;
    
    //! @brief
    //! Returns the window title.
    virtual std::string title() const = 0;
    
    //! @brief
    //! Sets the window title.
    virtual void setTitle(std::string_view title) = 0;
    
    //! @brief
    //! Shows the window on screen.
    virtual void show() = 0;
    
    //! @brief
    //! Centers the window on the current screen.
    virtual void center() = 0;
    
    //! @brief
    //! Closes the window.
    virtual void close() = 0;
    
    //! @brief
    //! Returns the window observer.
    inline Ptr<Observer> observer() { return mObserver.lock(); }
    
    //! @brief
    //! Returns the window observer.
    inline Ptr<const Observer> observer() const { return mObserver.lock(); }
    
    //! @brief
    //! Sets the current window observer.
    inline void setObserver(const Ptr<Observer>& observer) { mObserver = observer; }
    
    //! @brief
    //! Returns the window's content view.
    inline Ptr<View> contentView() { return mContentView; }
    
    //! @brief
    //! Returns the window's content view.
    inline Ptr<const View> contentView() const { return mContentView; }
    
    //! @brief
    //! Sets the window's content view.
    virtual void setContentView(const Ptr<View>& view) = 0;
};

ARA_END_NAMESPACE

#endif /* ARAWindow_h */
