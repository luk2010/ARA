////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Text/ARATextElement.cpp
//! @date
//!     2023/12/08
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ARATextElement.h"

ARA_TEXT_BEGIN_NS

Element::Element(const String& string, const ParagraphAttributes& attributes):
mFrame(string, Rect2(), attributes)
{

}

void Element::onViewUpdate(View& view) 
{
    ARA::Element::onViewUpdate(view);

    Rect2 frame = view.bounds();
    frame.origin.x += mPadding.left;
    frame.origin.y += mPadding.top;
    frame.size.width -= mPadding.right + mPadding.left;
    frame.size.height -= mPadding.bottom + mPadding.top;

    if (frame != mFrame.frame()) 
        mFrame.setFrame(frame);

    if (mFrame.needsLayout()) 
    {
        mFrame.layout();
        view.setNeedsDraw(true);
    }
}

void Element::onViewDraw(View& view, Drawer& drawer) const 
{
    ARA::Element::onViewDraw(view, drawer);
    mFrame.draw(drawer, Point2());
}

void Element::onMouseDown(View& view, MouseButton button, const Point2& location) 
{
    // As the location is already relative to the view bounds, we can directly 
    // call Frame::hitTest() with the given mouse location. 

    size_t index = mFrame.hitTest(location);

    if (index != InvalidIndex) 
        onClick(view, button, location, index, mFrame.string().at(index));
}

void Element::setPadding(const Rect2Edges& padding) 
{
    mPadding = padding; 
}

Rect2Edges Element::padding() const 
{
    return mPadding;
}

ARA_TEXT_END_NS