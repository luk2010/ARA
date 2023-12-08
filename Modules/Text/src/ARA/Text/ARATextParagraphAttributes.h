////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Text/ARATextParagraphAttributes.h
//! @date
//!     2023/12/08
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_TEXT_PARAGRAPH_ATTRIBUTES_H__
#define __ARA_TEXT_PARAGRAPH_ATTRIBUTES_H__

#include "ARATextPlatform.h"
#include "ARATextAlignment.h"

ARA_TEXT_BEGIN_NS

//! @brief 
//! The attributes available for a Paragraph.
//!
struct ParagraphAttributes 
{
    //! @brief 
    //! The indentation margin for the paragraph.
    //!
    std::optional<Real> indentation;
    
    //! @brief
    //! The line break mode.
    //!
    std::optional<LineBreakMode> lineBreakMode;
    
    //! @brief
    //! A space added between two lines.
    //!
    std::optional<Real> interline;
    
    //! @brief
    //! The paragraph text alignment.
    //!
    std::optional<Alignment> alignment;
};

ARA_TEXT_END_NS

#endif 
