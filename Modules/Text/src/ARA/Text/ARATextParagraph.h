////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Text/ARATextParagraph.h
//! @date
//!     2023/11/30
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_TEXT_PARAGRAPH_H__
#define __ARA_TEXT_PARAGRAPH_H__

#include "ARATextPlatform.h"
#include "ARATextString.h"
#include "ARATextLine.h"
#include "ARATextAlignment.h"

ARA_TEXT_BEGIN_NS

//! @brief
//! Defines a paragraph in a `ARA::Text::Frame`.
//!
struct Paragraph
{
    //! @brief
    //! The String the paragraph refers to.
    String& string;
    
    //! @brief
    //! The range in the string the paragraph refers to.
    Range range;
    
    //! @brief
    //! A boolean true if the paragraph needs to be rebuilt.
    std::atomic<bool> needsLayout;
    
    //! @brief
    //! The lines stored in the paragraph.
    //!
    std::vector<Line> lines;
    
    //! @brief
    //! The paragraph origin.
    //!
    Point2 origin;

    //! @brief 
    //! The paragraph size. 
    //! 
    Size2 size;
    
    //! @brief
    //! The indentation margin for the paragraph.
    //!
    Real indentation = 0.0;
    
    //! @brief
    //! The line break mode.
    //!
    LineBreakMode lineBreakMode = LineBreakMode::Letter;
    
    //! @brief
    //! A space added between two lines.
    //!
    Real interline = 0.0;
    
    //! @brief
    //! The paragraph text alignment.
    //!
    Alignment alignment = Alignment::Left;

    //! @brief 
    //! Creates a new Paragraph. 
    //! 
    Paragraph(String& string);

    //! @brief 
    //! Copies another Paragraph. 
    //! 
    Paragraph(const Paragraph& rhs);
    
    //! @brief
    //! Copies paragraph data.
    //!
    Paragraph& operator = (const Paragraph& rhs);
};

ARA_TEXT_END_NS

#endif
