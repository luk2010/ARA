////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Text/ARATextElement.h
//! @date
//!     2023/12/08
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_TEXT_ELEMENT_H__
#define __ARA_TEXT_ELEMENT_H__

#include "ARATextPlatform.h"
#include "ARATextFrame.h"

ARA_TEXT_BEGIN_NS

//! @brief
//! A ARA::Element that displays a text in a ARA::TextFrame.
//!
class Element : public ARA::Element
{
    //! @brief
    //! The text frame.
    //!
    Frame mFrame;

    //! @brief 
    //! The text padding. 
    //! 
    Rect2Edges mPadding;
    
public:
    
    //! @brief
    //! Creates a new text Element.
    //!
    //! @param string
    //!     The string to initialize the text element.
    //! @param paragraphAttributes
    //!     The attributes for the paragraphs in the element.
    //!
    Element(const String& string, const ParagraphAttributes& paragraphAttributes = {});
    
    //! @brief 
    //! Updates the element frame if needed.
    //! 
    virtual void onViewUpdate(View& view);

    //! @brief 
    //! Draws the element and its text. 
    //! 
    virtual void onViewDraw(View& view, Drawer& drawer) const;

    //! @brief 
    //! Makes a hit test on the text frame and calls the function `onClick`. 
    //! 
    virtual void onMouseDown(View& view, MouseButton button, const Point2& location);

    //! @brief 
    //! Sets the text padding. 
    //! 
    virtual void setPadding(const Rect2Edges& padding);

    //! @brief 
    //! Returns the text padding.
    //! 
    virtual Rect2Edges padding() const; 

    //! @brief 
    //! Called when a mouse button has been pressed and has hit a valid character index in 
    //! the text frame.
    //! 
    virtual void onClick(View& view, MouseButton button, const Point2& location, size_t index, Char32 character);
};

ARA_TEXT_END_NS

#endif 
