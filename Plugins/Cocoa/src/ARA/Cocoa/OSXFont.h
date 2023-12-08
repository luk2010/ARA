////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Cocoa/OSXFont.h
//! @date
//!     2023/12/08
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_COCOA_OSXFONT_H__
#define __ARA_COCOA_OSXFONT_H__

#include "ARACocoaPlatform.h"
#include "ARA/Core/ARAFont.h"

ARA_DECLARE_ERROR(CTFontError)

//! @brief
//! The implementation of `ARA::Font` for Cocoa.
//!
class OSXFont : public ARA::Font
{
    //! @brief
    //! The Core Text font handle.
    //!
    CTFontRef mHandle;
    
    //! @brief
    //! A cache for already loaded GlyphInfos.
    //!
    mutable std::map<ARA::GlyphIndex, ARA::GlyphInfo> mGlyphInfos; 
    
public:
    
    //! @brief
    //! Wraps a CTFontRef object.
    //!
    OSXFont(ARA::Application& app, CTFontRef handle);
    
    //! @brief
    //! Destroys the font.
    //!
    virtual ~OSXFont();
    
    //! @brief
    //! Returns the font family name.
    virtual std::string familyName() const;
    
    //! @brief
    //! Returns the font size.
    virtual ARA::Real size() const;
    
    //! @brief
    //! Returns the font traits.
    virtual TraitsMask traits() const;
    
    //! @brief
    //! Returns the Charset used by this font.
    virtual ARA::Charset charset() const;
    
    //! @brief
    //! Returns the Glyph Index for the given UTF-32 character.
    virtual ARA::GlyphIndex glyphIndex(ARA::Char32 character) const;
    
    //! @brief
    //! Returns the GlyphInfo structure for the given GlyphIndex.
    virtual ARA::GlyphInfo glyphInfo(ARA::GlyphIndex index) const;
};

#endif
