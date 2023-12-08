////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Text/ARATextGlyphRun.h
//! @date
//!     2023/12/08
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_TEXT_GLYPHRUN_H__
#define __ARA_TEXT_GLYPHRUN_H__

#include "ARATextPlatform.h"
#include "ARATextString.h"

ARA_TEXT_BEGIN_NS

//! @brief
//! An error for when a GlyphRun has an invalid font.
//!
ARA_DECLARE_ERROR(GlyphRunNullFont)

//! @brief
//! An object that stores a range of characters in a string, with the same attributes, and the
//! GlyphInfos objects for that range.
//!
class GlyphRun
{
    //! @brief
    //! The string related to the run.
    //!
    String& mString;
    
    //! @brief
    //! The range of characters the GlyphRun displays.
    //!
    Range mCharacters;
    
    //! @brief
    //! The attributes for those characters.
    //!
    CharAttributes mAttributes;
    
    //! @brief
    //! The GlyphInfos objects.
    //!
    GlyphInfoList mGlyphInfos;
    
    //! @brief
    //! The total advance for the run.
    //!
    Size2 mAdvance;
    
    //! @brief
    //! The run origin.
    //!
    Point2 mOrigin;
    
public:
    
    //! @brief
    //! Creates a new GlyphRun.
    //!
    GlyphRun(String& string);
    
    //! @brief
    //! Creates a new GlyphRun.
    //!
    //! @param string
    //!     The string related to the GlyphRun.
    //! @param range
    //!     The string range the run is effective for.
    //! @param attributes
    //!     The attribuutes for the run.
    //!
    GlyphRun(String& string, const Range& range, const CharAttributes& attributes);
    
    //! @brief
    //! Returns true if the run has a font set.
    //!
    bool hasFont() const; 
    
    //! @brief
    //! Forces the font for the run.
    //!
    void setFont(const Ptr<Font>& font);
    
    //! @brief
    //! Builds the run by getting every glyph infos and calculating the total run advance.
    //!
    void build();
    
    //! @brief
    //! Sets the run origin.
    //!
    void setOrigin(const Point2& origin);
    
    //! @brief
    //! Returns the run origin.
    //!
    Point2 origin() const; 
    
    //! @brief
    //! Returns the advances width and height.
    //!
    const Size2& advance() const; 
    
    //! @brief
    //! Returns the index of the glyph that overflows the given width.
    //!
    size_t findOverflowGlyphIndex(Real width) const;
    
    //! @brief
    //! Divides the run.
    //!
    //! @param index
    //!     The character index where to divide the range. The left range is held in the current
    //!     run and a new run is created for the right range.
    //!
    //! @note
    //!     If the run is already built (mGlyphInfos stores values), the new run will copy the
    //!     current run glyph infos.
    //!
    GlyphRun divide(size_t index);
    
    //! @brief
    //! Returns the GlyphRun height.
    //!
    Real height() const; 
    
    //! @brief
    //! Returns the GlyphRun covered range.
    //!
    const Range& range() const; 
    
    //! @brief
    //! Returns true if the GlyphRun length is zero.
    //!
    bool empty() const; 
    
    //! @brief
    //! Returns a point that corresponds to the origin point translated by the advance size.
    //!
    Point2 end() const; 

    //! @brief 
    //! Returns the GlyphInfo objects for this run. 
    //!
    const GlyphInfoList& glyphInfos() const;

    //! @brief 
    //! Returns the attributes for this run. 
    //! 
    const CharAttributes& attributes() const; 

    //! @brief 
    //! Copies the data in a given GlyphRun. 
    //!
    GlyphRun& operator = (const GlyphRun& run);
};

typedef std::vector<GlyphRun> GlyphRunList;

ARA_TEXT_END_NS

#endif
