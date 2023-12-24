////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Text/ARATextParagraph.cpp
//! @date
//!     2023/11/30
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ARATextParagraph.h"

ARA_TEXT_BEGIN_NS

Paragraph::Paragraph(String& string): 
string(string) 
{

}

Paragraph::Paragraph(const Paragraph& rhs): 
string(rhs.string)
{
    range = rhs.range;
    needsLayout = rhs.needsLayout.load();
    lines = rhs.lines; 
    indentation = rhs.indentation;
    lineBreakMode = rhs.lineBreakMode;
    interline = rhs.interline;
    alignment = rhs.alignment;
}

Paragraph& Paragraph::operator=(const Paragraph& rhs)
{
    range = rhs.range;
    needsLayout = rhs.needsLayout.load();
    lines = rhs.lines;
    indentation = rhs.indentation;
    lineBreakMode = rhs.lineBreakMode;
    interline = rhs.interline;
    alignment = rhs.alignment;
    return *this;
}

ARA_TEXT_END_NS
