//
//  ARAElement.h
//  lui
//
//  Created by jacques tronconi on 26/11/2023.
//

#ifndef ARAElement_h
#define ARAElement_h

#include "ARAController.h"
#include "ARAView.h"
#include "ARAElementBorder.h"
#include "ARARectCorner.h"

ARA_BEGIN_NAMESPACE

//! @brief 
//! An error for an element.
//! 
ARA_DECLARE_ERROR(ElementError)

//! @brief
//! An Element is a basic block for drawing native UI elements.
//!
class Element : public Controller<Element>, public View::Observer
{
protected:
    
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
    
protected:
    
    //! @brief
    //! Creates a new native view and automatically sets the observer to this
    //! object.
    //!
    virtual Ptr<View> createView(Application& app);
    
public:
    
    //! @brief
    //! Draws the view by using the element parameters.
    //!
    virtual void onViewDraw(View& view, Drawer& drawer) const;
    
    //! @brief
    //! Returns the element's background color.
    //!
    virtual Color backgroundColor() const;
    
    //! @brief
    //! Sets the background color of the element.
    //!
    virtual void setBackgroundColor(const Color& color);
    
    //! @brief
    //! Returns, for a view, the background frame. Typically, this is the view's
    //! bounds.
    //!
    virtual Rect2 backgroundRect(const View& view) const;
    
    //! @brief
    //! Returns a Path suitable to render the background or the view border.
    virtual Ptr<Path> borderPath(const View& view, RectEdge edge) const;
    
    //! @brief
    //! Returns the different Path objects needed to render the view background or border.
    virtual std::array<Ptr<Path>, 4> borderPathes(const View& view) const;
    
    //! @brief
    //! Returns the corner radius of a given corner.
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
    //! Responds to a view update event.
    //!
    virtual void onViewUpdate(View& view);
    
protected:
    
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
    virtual void layoutChildren(View& view) const;
};

ARA_END_NAMESPACE

#endif /* ARAElement_h */
