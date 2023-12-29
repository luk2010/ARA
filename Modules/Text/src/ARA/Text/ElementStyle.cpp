////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Text/ElementStyle.cpp
//! @date
//!     2023/12/29
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ARA/Text/ElementStyle.h"

ARA_TEXT_BEGIN_NS

ElementStyle::ElementStyle(const std::string& name, const ARA::ElementStylePtr& parent):
ARA::ElementStyle(name, parent)
{
    mFont = Inherits();
    mAlignment = Alignment::Left;
}

Maybe < Rect2Edges > ElementStyle::padding() const
{
    if (mPadding.isInherits())
    {
        auto p = std::dynamic_pointer_cast < Text::ElementStyle >(parent());
        
        if (p)
            return p->padding();
        
        return Maybe < Rect2Edges >();
    }
    
    return mPadding.value();
}

void ElementStyle::setPadding(const Inheritable < Rect2Edges >& padding)
{
    mPadding = padding;
}

Maybe < FontPtr > ElementStyle::font() const
{
    if (mFont.isInherits())
    {
        auto p = std::dynamic_pointer_cast < Text::ElementStyle >(parent());
        
        if (p)
            return p->font();
        
        return Maybe < FontPtr >();
    }
    
    return mFont.value();
}

void ElementStyle::setFont(const Inheritable < FontPtr >& font)
{
    mFont = font;
}

Maybe < Alignment > ElementStyle::alignment() const
{
    if (mAlignment.isInherits())
    {
        auto p = std::dynamic_pointer_cast < Text::ElementStyle >(parent());
        
        if (p)
            return p->alignment();
        
        return Maybe < Alignment >();
    }
    
    return mAlignment.value();
}

void ElementStyle::setAlignment(Alignment value)
{
    mAlignment = value;
}

void ElementStyle::apply(Element& element) const
{
    ARA::ElementStyle::apply(element);
    
    auto* el = dynamic_cast < Text::Element* >(&element);
    
    if (!el)
        return;
    
    const auto _padding = padding();
    const auto _font = font();
    const auto _alignment = alignment();
    
    if (_padding)
        el->setPadding(_padding.value());
    if (_font)
        el->string().setAttributes({}, { .font = _font.value() });
    if (_alignment)
        el->textFrame().setAlignment(_alignment.value());
}

ARA_TEXT_END_NS
