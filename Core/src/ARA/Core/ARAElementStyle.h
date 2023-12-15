////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Core/ARAElementStyle.h
//! @date
//!     2023/12/14
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_CORE_ARAELEMENTSTYLE_H__
#define __ARA_CORE_ARAELEMENTSTYLE_H__

#include "ARA/Core/ARAPlatform.h"
#include "ARA/Core/ARAElement.h"

ARA_BEGIN_NAMESPACE

//! @brief
//! Defines a class that stylizes a given ARA::Element.
//!
class ElementStyle
{
    //! @brief
    //! The style name.
    //!
    std::string mName;
    
    //! @brief
    //! The parent style.
    //!
    Weak < ElementStyle > mParent;
    
    //! @brief
    //! The background color.
    //!
    Inheritable < Color > mBackgroundColor;
    
    //! @brief
    //! The border properties.
    //!
    std::array < ElementBorder, 4 > mBorders;
    
    //! @brief
    //! The corner radiuses.
    //!
    std::array < Inheritable < Real >, 4 > mCornerRadiuses;
    
public:
    
    //! @brief
    //! Creates a new style.
    //!
    ElementStyle(const std::string& name, const Ptr < ElementStyle >& parent = nullptr);
    
    //! @brief
    //! Virtual destructor.
    //!
    virtual ~ElementStyle() = default;
    
    //! @brief
    //! Returns the style name.
    //!
    virtual const std::string& name() const;
    
    //! @brief
    //! Returns the style parent.
    //!
    virtual Ptr < ElementStyle > parent() const;
    
    //! @brief
    //! Sets the parent style.
    //!
    virtual void setParent(const Ptr < ElementStyle >& style);
    
    //! @brief
    //! Sets the parent style.
    //!
    virtual void setParent(const std::string& styleName);
    
    //! @brief
    //! Sets the current background color.
    //!
    virtual void setBackgroundColor(const Inheritable < Color >& color);
    
    //! @brief
    //! Returns the background color.
    //!
    virtual Maybe < Color > backgroundColor() const;
    
    //! @brief
    //! Sets the current border properties.
    //!
    virtual void setBorder(RectEdge edge, const Inheritable < Real >& width, const Inheritable < Color >& color);
    
    //! @brief
    //! Sets the current border properties.
    //!
    virtual void setBorder(RectEdge edge, const Inheritable < Real >& width);
    
    //! @brief
    //! Sets the current border properties.
    //!
    virtual void setBorder(RectEdge edge, const Inheritable < Color >& color);
    
    //! @brief
    //! Sets the current border properties.
    //!
    virtual void setBorder(const Inheritable < Real >& width, const Inheritable < Color >& color);
    
    //! @brief
    //! Sets the current border properties.
    //!
    virtual void setBorder(const Inheritable < Color >& color);
    
    //! @brief
    //! Sets the current border properties.
    //!
    virtual void setBorder(const Inheritable < Real >& width);
    
    //! @brief
    //! Returns the borders properties.
    //!
    virtual Maybe < std::array < ElementBorder, 4 > > borders() const;
    
    //! @brief
    //! Sets the corner radii.
    //!
    virtual void setCornerRadius(RectCorner corner, const Inheritable < Real >& radius);
    
    //! @brief
    //! Sets the corner radii.
    //!
    virtual void setCornerRadius(const Inheritable < Real >& radius);
    
    //! @brief
    //! Returns the corner radii.
    //!
    virtual std::array < Maybe < Real >, 4 > cornerRadii() const;
    
    //! @brief
    //! Applies the style to an element.
    //!
    virtual void apply(Element& element) const;
};

typedef Ptr < ElementStyle > ElementStylePtr;
typedef std::vector < ElementStylePtr > ElementStyleList;

ARA_DECLARE_ERROR(ElementStyleError)

ARA_END_NAMESPACE

#endif
