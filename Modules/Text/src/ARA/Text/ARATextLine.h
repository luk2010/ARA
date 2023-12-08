////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Text/ARATextLine.h
//! @date
//!     2023/12/08
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_TEXT_LINE_H__
#define __ARA_TEXT_LINE_H__

#include "ARATextPlatform.h"
#include "ARATextGlyphRun.h"

ARA_TEXT_BEGIN_NS

//! @brief
//! An error for a Line when the line is empty but a GlyphRun is requested.
//!
ARA_DECLARE_ERROR(LineEmpty)

//! @brief 
//! Represents a line in a Paragraph.
//!
class Line 
{
    //! @brief
    //! The string the line refers to.
    //!
    const String& mString;
    
    //! @brief
    //! The runs in the line.
    //!
    GlyphRunList mGlyphRuns;
    
    //! @brief
    //! The line width and height.
    //!
    Size2 mSize;
    
    //! @brief
    //! The characters range that the line displays.
    //!
    Range mRange;
    
    //! @brief
    //! The line origin.
    //!
    Point2 mOrigin;
    
public:
    
    //! @brief
    //! Creates a new line.
    //!
    //! @param string
    //!     The string this line refers to.
    //! @param width
    //!     The line width.
    //!
    Line(const String& string, Real width);
    
    //! @brief
    //! Adds a GlyphRun to the line.
    //!
    //! @note
    //!     The line will also calculate its current height and width. The height is
    //!     calculated from the font informations.
    //!
    void add(const GlyphRun& run);
    
    //! @brief
    //! Returns the line height.
    //!
    Real height() const;
    
    //! @brief
    //! Returns the line width.
    //!
    Real width() const; 
    
    //! @brief
    //! Reinitialize the line.
    //!
    void clear();
    
    //! @brief
    //! Sets the current line origin.
    //!
    void setOrigin(const Point2& origin);
    
    //! @brief
    //! Returns the line current origin.
    //!
    const Point2& origin() const; 
    
    //! @brief
    //! Returns the last GlyphRun in the line.
    //!
    GlyphRun& lastRun(); 
    
    //! @brief
    //! Returns the last GlyphRun in the line.
    //!
    const GlyphRun& lastRun() const;
    
    //! @brief
    //! Returns the runs in the line.
    //!
    const GlyphRunList& runs() const; 
    
    //! @brief
    //! Copies the given line data.
    //!
    Line& operator = (const Line& rhs);
    
    //! @brief
    //! Calls a function for each GlyphRun in the line.
    //!
    template < class Cbk > void forEachRun(Cbk&& cbk)
    {
        for (GlyphRun& run : mGlyphRuns)
            cbk(run);
    }
    
    //! @brief
    //! Calls a function for each GlyphRun in the line.
    //!
    template < class Cbk > void forEachRun(Cbk&& cbk) const
    {
        for (const GlyphRun& run : mGlyphRuns)
            cbk(run);
    }
};

ARA_TEXT_END_NS

#endif 
