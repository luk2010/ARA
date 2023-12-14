//
//  ARAView.h
//  ARA
//
//  Created by jacques tronconi on 26/11/2023.
//

#ifndef ARAView_h
#define ARAView_h

#include "ARANode.h"
#include "ARADrawer.h"
#include "ARARect2.h"
#include "ARAMouseButton.h"
#include "ARA/Core/ARAEventEmitter.h"

ARA_BEGIN_NAMESPACE

class Window;

//! @brief
//! A base class to create native views.
class View : public std::enable_shared_from_this<View>,
             public Node<View>,
             public ApplicationObject,
             public EventEmitter
{
public:
    
    //! @brief
    //! The View Observer.
    struct Observer : public EventListener
    {
        //! @brief
        //! Destructor.
        virtual ~Observer() = default;
        
        //! @brief
        //! The view window has changed.
        virtual void onViewWindowChange(View& view, const Ptr<Window>& window) {}
        
        //! @brief
        //! The view parent has changed.
        virtual void onViewParentChange(View& view, const Ptr<View>& parent) {}
        
        //! @brief
        //! The view has a new child.
        virtual void onViewAddChild(View& view, const Ptr<View>& child) {}
        
        //! @brief
        //! The view has removed a child view.
        virtual void onViewRemoveChild(View& view, const Ptr<View>& child) {}
        
        //! @brief
        //! The view should update.
        virtual void onViewUpdate(View& view) {}
        
        //! @brief
        //! The view should draw itself.
        virtual void onViewDraw(View& view, Drawer& drawer) const {}
    };
    
protected:
    
    //! @brief
    //! The current window, if this view is in a window.
    Weak<Window> mWindow;
    
    //! @brief
    //! The view observer.
    Weak<Observer> mObserver;
    
    //! @brief
    //! Internally sets the parent node.
    //!
    inline void setParentView(const Ptr<View>& view) { mParentNode = view; }
    
    //! @brief
    //! Internally sets the parent node of another view.
    //!
    inline void setParentView(View& ref, const Ptr<View>& view) { ref.setParentView(view); }
    
    //! @brief
    //! A boolean true if the view accepts mouse moved events.
    //!
    AtomBool mAcceptsMouseMoveEvents;
    
public:
    
    //! @brief
    //! Creates a new View.
    inline View(Application& application): ApplicationObject(application), mAcceptsMouseMoveEvents(false) {}
    
    //! @brief
    //! Returns the window that holds this view, if available.
    inline Ptr<Window> window() { return mWindow.lock(); }
    
    //! @brief
    //! Returns the window that holds this view, if available.
    inline Ptr<const Window> window() const { return mWindow.lock(); }
    
    //! @brief
    //! Adds a child to this view.
    virtual Ptr<View> addChild(const Ptr<View>& child, const Ptr<View>& beforeView = nullptr) = 0;
    
    //! @brief
    //! Removes a child from this view.
    virtual void removeChild(const Ptr<View>& child) = 0;
    
    //! @brief
    //! Returns the current view observer.
    inline Ptr<Observer> observer() { return mObserver.lock(); }
    
    //! @brief
    //! Returns the current view observer.
    inline Ptr<const Observer> observer() const { return mObserver.lock(); }
    
    //! @brief
    //! Sets the view current observer.
    virtual void setObserver(const Ptr<Observer>& observer);
    
    //! @brief
    //! Returns the current view frame.
    virtual Rect2 frame() const = 0;
    
    //! @brief
    //! Sets the current view frame.
    virtual void setFrame(const Rect2& frame) = 0;
    
    //! @brief
    //! Sets weither the view needs a redraw.
    virtual void setNeedsDraw(bool value) = 0;
    
    //! @brief
    //! Returns true if the view currently needs to be redrawn.
    virtual bool needsDraw() const = 0;
    
    //! @brief
    //! Returns the view's bounds.
    virtual Rect2 bounds() const = 0;
    
    //! @brief
    //! Sets the view's bounds.
    virtual void setBounds(const Rect2& rect) = 0;
    
    //! @brief
    //! Updates the view and its children.
    //!
    virtual void update(); 
    
    //! @brief
    //! Returns true if the view accepts mouse moved events.
    //!
    virtual bool acceptsMouseMoveEvents() const;
    
    //! @brief
    //! Sets if the view accepts mouse moved events.
    //!
    virtual void setAcceptsMouseMoveEvents(bool value);
};

ARA_END_NAMESPACE

#endif /* ARAView_h */
