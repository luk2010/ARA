////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Text/ElementStyle.h
//! @date
//!     2023/12/29
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_TEXT_ELEMENTSTYLE_H__
#define __ARA_TEXT_ELEMENTSTYLE_H__

#include "ARA/Text/ARATextElement.h"
#include "ARA/Core/ARAElementStyle.h"
#include "ARA/Core/ARAFont.h"

ARA_TEXT_BEGIN_NS

//! @brief
//! A `ARA::ElementStyle` specialized for `ARA::Text::Element`.
//!
class ElementStyle : public ARA::ElementStyle
{
    //! @brief
    //! The padding used to display the text.
    //!
    Inheritable < Rect2Edges > mPadding;
    
    //! @brief
    //! The default font for the displayed text.
    //!
    Inheritable < FontPtr > mFont;
    
    //! @brief
    //! The default alignment for the displayed text.
    //!
    Inheritable < Alignment > mAlignment;
    
public:
    
    //! @brief
    //! Creates a new instance of the text element style.
    //!
    ElementStyle(const std::string& name, const Ptr < ARA::ElementStyle >& parent = nullptr);
    
    //! @brief
    //! Returns the current padding.
    //!
    virtual Maybe < Rect2Edges > padding() const;
    
    //! @brief
    //! Sets the current padding.
    //!
    virtual void setPadding(const Inheritable < Rect2Edges >& padding);
    
    //! @brief
    //! Returns the style font.
    //!
    virtual Maybe < FontPtr > font() const;
    
    //! @brief
    //! Sets the font used by default to display the text.
    //!
    virtual void setFont(const Inheritable < FontPtr >& font);
    
    //! @brief
    //! Returns the default text alignment.
    //!
    virtual Maybe < Alignment > alignment() const;
    
    //! @brief
    //! Sets the default text alignment.
    //!
    virtual void setAlignment(Alignment value);
    
    //! @brief
    //! Applies the style to an element.
    //!
    virtual void apply(Element& element) const;
};

ARA_TEXT_END_NS

#endif 
