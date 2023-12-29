//
//  ARAFont.h
//  ARA
//
//  Created by jacques tronconi on 27/11/2023.
//

#ifndef ARAFont_h
#define ARAFont_h

#include "ARAApplicationObject.h"
#include "ARAGlyphInfo.h"
#include "ARACharset.h"

ARA_BEGIN_NAMESPACE

//! @brief
//! A Font object interface.
//!
//! A Font object describes a specific font from a family, for a given size and for the specified
//! font traits. You can create a new font by using `ARA::Application::createFont()`.
//!
class Font : public ApplicationObject
{
public:
    
    //! @brief
    //! A Mask that describe the traits of a font.
    enum TraitsMask
    {
        //! @brief The font is italic.
        Italic = 1 << 0,
        
        //! @brief The font is bold.
        Bold = 1 << 1,
        
        //! @brief The font is condensed.
        Condensed = 1 << 2
    };
    
    //! @brief
    //! Creates a new instance.
    inline Font(Application& app): ApplicationObject(app) { }
    
    //! @brief
    //! Returns the font family name.
    virtual std::string familyName() const = 0;
    
    //! @brief
    //! Returns the font size.
    virtual Real size() const = 0;
    
    //! @brief
    //! Returns the font traits.
    virtual TraitsMask traits() const = 0;
    
    //! @brief
    //! Returns the Charset used by this font.
    virtual Charset charset() const = 0;
    
    //! @brief
    //! Returns the Glyph Index for the given UTF-32 character.
    virtual GlyphIndex glyphIndex(Char32 character) const = 0;
    
    //! @brief
    //! Returns the GlyphInfo structure for the given GlyphIndex.
    virtual GlyphInfo glyphInfo(GlyphIndex index) const = 0;
};

typedef Ptr < Font > FontPtr;

ARA_END_NAMESPACE

#endif /* ARAFont_h */
