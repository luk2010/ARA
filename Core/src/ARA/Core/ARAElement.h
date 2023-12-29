//
//  ARAElement.h
//  lui
//
//  Created by jacques tronconi on 26/11/2023.
//

#ifndef ARAElement_h
#define ARAElement_h

#include "ARAView.h"
#include "ARAElementBorder.h"
#include "ARARectCorner.h"

#include "ARA/Core/ARAError.h"
#include "ARA/Core/ViewController.h"

ARA_BEGIN_NAMESPACE

class Element;
class ElementStyle;

typedef Ptr < Element > ElementPtr;
typedef std::vector < ElementPtr > ElementList;

//! @brief 
//! An error for an element.
//! 
ARA_DECLARE_ERROR(ElementError)

//! @brief
//! An Element is a basic block for drawing native UI elements.
//!
class Element : public ViewController, public std::enable_shared_from_this < Element >
{
    friend class Window;
    friend class View;
    
protected:
    
    //! @brief
    //! A weak pointer to the window that directly owns the controller.
    //!
    Weak < Window > mWindow;
    
    //! @brief
    //! The local background color.
    //!
    Inheritable<Color> mBackgroundColor;
    
    //! @brief
    //! The four borders of the element.
    //!
    ElementBorder mBorders[4];
    
    //! @brief
    //! The four corners radii.
    //!
    Inheritable<Real> mCornerRadius[4];
    
public:
    
    //! @brief
    //! Constructs a new element.
    //!
    Element();
    
public:
    
    //! @brief
    //! Returns the view window.
    //!
    virtual Window& window();
    
    //! @brief
    //! Returns the view window.
    //!
    virtual const Window& window() const;
    
    //! @brief
    //! Returns the element's background color.
    //!
    virtual Color backgroundColor() const;
    
    //! @brief
    //! Sets the background color of the element.
    //!
    virtual void setBackgroundColor(const Color& color);
    
    //! @brief
    //! Returns the local background rectangle.
    //!
    virtual Rect2 backgroundRect() const;
    
    //! @brief
    //! Returns a Path suitable to render the background or the view border.
    //!
    virtual Ptr<Path> borderPath(RectEdge edge) const;
    
    //! @brief
    //! Returns the different Path objects needed to render the view background or border.
    //!
    virtual std::array<Ptr<Path>, 4> borderPathes() const;
    
    //! @brief
    //! Returns the corner radius of a given corner.
    //! 
    virtual Real cornerRadius(RectCorner corner) const;
    
    //! @brief
    //! Sets the corner radius of a given corner.
    virtual void setCornerRadius(RectCorner corner, Real radius);
    
    //! @brief
    //! Returns the border width of a given edge.
    virtual Real borderWidth(RectEdge edge) const;
    
    //! @brief
    //! Sets the border width of one edge.
    virtual void setBorderWidth(RectEdge edge, const Inheritable<Real>& value);
    
    //! @brief
    //! Sets the border width of all edges.
    virtual void setBorderWidth(const Inheritable<Real>& value);
    
    //! @brief
    //! Returns the border color of a given edge.
    virtual Color borderColor(RectEdge edge) const;
    
    //! @brief
    //! Sets the border color of a given edge.
    //!
    virtual void setBorderColor(RectEdge edge, const Inheritable < Color >& color);
    
    //! @brief
    //! Sets the border color of all edges.
    //!
    virtual void setBorderColor(const Inheritable < Color >& color);
    
    //! @brief
    //! Returns the element frame.
    //!
    virtual Rect2 frame() const;
    
    //! @brief
    //! Sets the element frame.
    //!
    virtual void setFrame(const Rect2& frame);
    
    //! @brief
    //! Sets the element frame size.
    //!
    virtual void setFrameSize(const Size2& size);
    
    //! @brief
    //! Sets the element frame origin.
    //!
    virtual void setFrameOrigin(const Point2& origin);
    
    //! @brief
    //! Returns the number of children in the element view.
    //!
    virtual size_t numberOfChildren() const;
    
    //! @brief
    //! Returns the list of children views.
    //!
    virtual ViewList childrenViews() const;
    
    //! @brief
    //! Returns the list of children elements.
    //!
    virtual ElementList children() const;
    
    //! @brief
    //! Returns the parent element, or null if no parent is defined.
    //!
    virtual ElementPtr parent() const;
    
    //! @brief
    //! Adds an element in the children list.
    //!
    virtual ElementPtr add(const ElementPtr& element, const ElementPtr& before = nullptr);
    
    //! @brief
    //! Removes an element from the children list.
    //!
    virtual void remove(const ElementPtr& element);
    
    //! @brief
    //! Returns the element view bounds.
    //!
    virtual Rect2 bounds() const;
    
    //! @brief
    //! Sets if the element should be redisplayed.
    //!
    virtual void setNeedsDisplay(bool value);
    
    //! @brief
    //! Returns if the element currently needs to be redisplayed.
    //!
    virtual bool needsDisplay() const; 
    
    //! @brief
    //! Forces the element to relayout itself.
    //!
    virtual void setNeedsLayout(bool value);
    
    //! @brief
    //! Returns weither the element as a pending layout.
    //!
    virtual bool needsLayout() const;
    
    //! @brief
    //! Sets the given style.
    //!
    virtual void setStyle(const ElementStyle& style);
    
    //! @brief
    //! Sets the given style.
    //!
    virtual void setStyle(const std::string& name);
    
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
    //! Draws the view's background.
    //!
    virtual void drawBackground(const View& view, Drawer& drawer, const Ptr<Path>& path, const Color& color) const;
    
    //! @brief
    //! Draws one view border edge.
    //!
    virtual void drawBorderEdge(const View& view, Drawer& drawer, const Ptr<Path>& path, RectEdge edge, Real lineWidth, const Color& color) const;
    
    //! @brief
    //! Layouts the view children.
    //!
    virtual void layoutChildren() const;
    
    //! @brief
    //! Returns true if the element accepts the given `Window` as its parent window.
    //!
    //! @discussion
    //! When overriding this function, instead of returning `true`, return a call to
    //! this method. The default implementation also sets the `mWindow` property before
    //! returning `true`.
    //!
    virtual bool willMoveToWindow(const Window& window);
    
    //! @brief
    //! Called when the element will become the input element.
    //!
    //! @return
    //! True if the element can become the input element, false otherwise.
    //!
    virtual bool willBecomeInputElement();
    
    //! @brief
    //! Called when the element did became the input element.
    //!
    virtual void didBecomeInputElement();
    
    //! @brief
    //! Called when the element will resign input.
    //!
    //! @return
    //! True if the element can resign input, false otherwise.
    //!
    virtual bool willResignInputElement();
    
    //! @brief
    //! Called when the element did resign input.
    //!
    virtual void didResignInputElement();
};

ARA_END_NAMESPACE

#endif /* ARAElement_h */
