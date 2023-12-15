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

void Element::setPadding(const Rect2Edges& padding) 
{
    mPadding = padding; 
}

Rect2Edges Element::padding() const 
{
    return mPadding;
}

void Element::setString(const String& string)
{
    mFrame.setString(string);
}

const String& Element::string() const
{
    return mFrame.string();
}

String& Element::string()
{
    return mFrame.string();
}

bool Element::onMouseDown(const MouseDownEvent& event)
{
    View& selfView = const_cast < View& >(dynamic_cast < const View& >(event.emitter));
    
    // As the location is already relative to the view bounds, we can directly
    // call Frame::hitTest() with the given mouse location.
    
    size_t index = mFrame.hitTest(event.location, true, 0.5);
    
    if (index != InvalidIndex)
        return onClick(selfView,
                       event.button,
                       event.location,
                       index,
                       index < mFrame.string().length() ?
                            mFrame.string().at(index) :
                            InvalidIndex);
    
    return false;
}

ARA_TEXT_END_NS
