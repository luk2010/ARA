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
class View;
class ViewController;

typedef Ptr < View > ViewPtr;
typedef std::vector < ViewPtr > ViewList;

//! @brief
//! A base class to create native views.
class View : public std::enable_shared_from_this<View>,
             public Node<View>,
             public ApplicationObject,
             public EventEmitter
{
protected:
    
    friend class Window;
    
    //! @brief
    //! The current window, if this view is in a window.
    Weak<Window> mWindow;
    
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
    
    //! @brief
    //! A boolean true if the view currently needs to layout its children.
    //!
    AtomBool mNeedsLayoutChildren;
    
    //! @brief
    //! The controller that manages this view.
    //!
    ViewController& mController;
    
public:
    
    //! @brief
    //! Creates a new View instance.
    //!
    //! @param application
    //!     The `ARA::Application` that creates this view.
    //! @param controller
    //!     The `ARA::ViewController` instance that manages this view.
    //!
    View(Application& application, ViewController& controller);
    
    //! @brief
    //! Returns the window that holds this view, if available.
    //!
    inline Ptr<Window> window() { return mWindow.lock(); }
    
    //! @brief
    //! Returns the window that holds this view, if available.
    //!
    inline Ptr<const Window> window() const { return mWindow.lock(); }
    
    //! @brief
    //! Returns the view's controller.
    //!
    virtual ViewController& controller();
    
    //! @brief
    //! Returns the view's controller.
    //!
    virtual const ViewController& controller() const;
    
    //! @brief
    //! Adds a child to this view.
    //!
    virtual ViewPtr addChild(const ViewPtr& child, const ViewPtr& beforeView = nullptr);
    
    //! @brief
    //! Removes a child from this view.
    //!
    virtual void removeChild(const ViewPtr& child);
    
    //! @brief
    //! Returns the current view frame.
    virtual Rect2 frame() const = 0;
    
    //! @brief
    //! Sets the current view frame.
    virtual void setFrame(const Rect2& frame);
    
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
    virtual void setBounds(const Rect2& rect);
    
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
    
    //! @brief
    //! Returns true if the view needs to layout its children.
    //!
    virtual bool needsLayoutChildren() const;
    
    //! @brief
    //! Forces the mNeedsLayoutChildren property value.
    //!
    virtual void setNeedsLayoutChildren(bool value);
    
    //! @brief
    //! Calls `controller().draw()` from this public context.
    //!
    virtual void draw(ARA::Drawer& drawer) const;
    
protected:
    
    //! @brief
    //! Internal implementation of `addChild()` to let platform implementations add the
    //! child in the underlying system.
    //!
    virtual bool _addChild(const ViewPtr& child, const ViewPtr& beforeChild) = 0;
    
    //! @brief
    //! Internal implementation of `removeChild()` to let platform implementations remove the
    //! child in the underlying system.
    //!
    virtual bool _removeChild(const ViewPtr& child) = 0;
};

ARA_END_NAMESPACE

#endif /* ARAView_h */
