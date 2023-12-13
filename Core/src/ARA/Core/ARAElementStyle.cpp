////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Core/ARAElementStyle.cpp
//! @date
//!     2023/12/14
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ARA/Core/ARAElementStyle.h"

ARA_BEGIN_NAMESPACE

ElementStyle::ElementStyle(const std::string& name, const Ptr < ElementStyle >& parent):
mName(name), mParent(parent)
{
    mBackgroundColor.setValue(Inherits());
    
    mBorders[0].edge = RectEdge::Left;
    mBorders[0].width.setValue(Inherits());
    mBorders[0].color.setValue(Inherits());
    
    mBorders[1].edge = RectEdge::Top;
    mBorders[1].width.setValue(Inherits());
    mBorders[1].color.setValue(Inherits());
    
    mBorders[2].edge = RectEdge::Right;
    mBorders[2].width.setValue(Inherits());
    mBorders[2].color.setValue(Inherits());
    
    mBorders[3].edge = RectEdge::Bottom;
    mBorders[3].width.setValue(Inherits());
    mBorders[3].color.setValue(Inherits());
    
    mCornerRadiuses[0].setValue(Inherits());
    mCornerRadiuses[1].setValue(Inherits());
    mCornerRadiuses[2].setValue(Inherits());
    mCornerRadiuses[3].setValue(Inherits());
}

const std::string& ElementStyle::name() const
{
    return mName;
}

void ElementStyle::setBackgroundColor(const Inheritable < Color >& color)
{
    mBackgroundColor = color;
}

Maybe < Color > ElementStyle::backgroundColor() const
{
    if (mBackgroundColor.isInherits())
    {
        auto p = mParent.lock();
        
        if (p)
            return p->backgroundColor();
        
        return Maybe < Color >();
    }
    
    return mBackgroundColor.value();
}

void ElementStyle::setBorder(RectEdge edge, const Inheritable < Real >& width, const Inheritable < Color >& color)
{
    const size_t i = static_cast < size_t >(edge);
    mBorders[i].width = width;
    mBorders[i].color = color;
}

void ElementStyle::setBorder(RectEdge edge, const Inheritable < Real >& width)
{
    mBorders[static_cast < size_t >(edge)].width = width;
}

void ElementStyle::setBorder(RectEdge edge, const Inheritable < Color >& color)
{
    mBorders[static_cast < size_t >(edge)].color = color;
}

void ElementStyle::setBorder(const Inheritable < Real >& width, const Inheritable < Color >& color)
{
    for (auto& border : mBorders)
    {
        border.width = width;
        border.color = color;
    }
}

void ElementStyle::setBorder(const Inheritable < Color >& color)
{
    for (auto& border : mBorders)
        border.color = color;
}

void ElementStyle::setBorder(const Inheritable < Real >& width)
{
    for (auto& border : mBorders)
        border.width = width;
}

Maybe < std::array < ElementBorder, 4 > > ElementStyle::borders() const
{
    return mBorders;
}

void ElementStyle::setCornerRadius(RectCorner corner, const Inheritable < Real >& radius)
{
    mCornerRadiuses[static_cast < size_t >(corner)] = radius;
}

void ElementStyle::setCornerRadius(const Inheritable < Real >& radius)
{
    for (auto& corner : mCornerRadiuses)
        corner = radius;
}

std::array < Maybe < Real >, 4 > ElementStyle::cornerRadii() const
{
    std::array < Maybe < Real >, 4 > radii;
    Ptr < ElementStyle > p;
    
    for (size_t i = 0; i < 4; ++i)
    {
        const auto& radius = mCornerRadiuses[i];
        
        if (radius.isInherits())
        {
            if (!p)
                p = mParent.lock();
            
            if (p)
                radii[i] = p->cornerRadii()[i];
        }
        
        else
            radii[i] = radius.value();
    }
    
    return radii;
}

void ElementStyle::apply(Element& element) const
{
    auto backCol = backgroundColor();
    auto borders = this->borders();
    auto radii = this->cornerRadii();
    
    if (backCol)
        element.setBackgroundColor(backCol.value());
    
    if (borders)
    {
        for (auto& border : borders.value())
        {
            element.setBorderWidth(border.edge, border.width);
            element.setBorderColor(border.edge, border.color);
        }
    }
    
    for (size_t i = 0; i < 4; ++i)
    {
        auto& radius = radii[i];
        
        if (radius)
            element.setCornerRadius(static_cast < RectCorner >(i), radius.value());
    }
}

ARA_END_NAMESPACE
