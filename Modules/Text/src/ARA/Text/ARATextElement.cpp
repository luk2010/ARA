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
    setNeedsLayout(true);
}

const String& Element::string() const
{
    return mFrame.string();
}

String& Element::string()
{
    return mFrame.string();
}

const Frame& Element::textFrame() const
{
    return mFrame;
}

Frame& Element::textFrame()
{
    return mFrame;
}

void Element::update()
{
    ARA::Element::update();
    
    Rect2 frame = view().bounds();
    frame.origin.x += mPadding.left;
    frame.origin.y += mPadding.top;
    frame.size.width -= mPadding.right + mPadding.left;
    frame.size.height -= mPadding.bottom + mPadding.top;
    
    if (frame != mFrame.frame())
        mFrame.setFrame(frame);
    
    if (mFrame.needsLayout())
    {
        mFrame.layout();
        view().setNeedsDraw(true);
    }
}

void Element::draw(Drawer& drawer) const
{
    ARA::Element::draw(drawer);
    mFrame.draw(drawer, Point2());
}

bool Element::onMouseDown(const MouseDownEvent& event)
{
    // As the location is already relative to the view bounds, we can directly
    // call Frame::hitTest() with the given mouse location.
    
    size_t index = mFrame.hitTest(event.location, true, 0.5);
    
    return onClick(event.button,
                   event.location,
                   index == InvalidIndex ? 0 : index,
                   index < mFrame.string().length() ?
                        mFrame.string().at(index) :
                        0);
}

ARA_TEXT_END_NS
