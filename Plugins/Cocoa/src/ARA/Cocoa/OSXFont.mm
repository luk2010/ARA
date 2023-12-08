////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Cocoa/OSXFont.mm
//! @date
//!     2023/12/08
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "OSXFont.h"
#include "OSXPath.h"

OSXFont::OSXFont(ARA::Application& app, CTFontRef handle):
ARA::Font(app), mHandle(handle)
{
    
}

OSXFont::~OSXFont()
{
    CFRelease(mHandle);
}

std::string OSXFont::familyName() const
{
    CFStringRef name = CTFontCopyFamilyName(mHandle);
    
    std::string str = [(NSString*)name UTF8String];
    
    CFRelease(name);
    
    return str;
}

ARA::Real OSXFont::size() const
{
    return CTFontGetSize(mHandle);
}

ARA::Font::TraitsMask OSXFont::traits() const
{
    CTFontSymbolicTraits traits = CTFontGetSymbolicTraits(mHandle);
    TraitsMask mask = 0;
    
    if (traits & kCTFontTraitBold) mask |= Bold;
    if (traits & kCTFontTraitItalic) mask |= Italic;
    if (traits & kCTFontTraitCondensed) mask |= Condensed;
    
    return mask;
}

ARA::Charset OSXFont::charset() const
{
    return ARA::Charset::Unicode;
}

ARA::GlyphIndex OSXFont::glyphIndex(ARA::Char32 character) const
{
    CGGlyph index = 0;
    
    if (!CTFontGetGlyphsForCharacters(mHandle, (UniChar*)&character, &index, 1))
        throw CTFontError("[OSXFont] CTFontGetGlyphsForCharacters() failed.");
    
    return (ARA::GlyphIndex) index;
}

ARA::GlyphInfo OSXFont::glyphInfo(ARA::GlyphIndex index) const
{
    auto it = mGlyphInfos.find(index);
    
    if (it != mGlyphInfos.end())
        return it->second;
    
    ARA::GlyphInfo infos;
    
    infos.name = [(__bridge_retained NSString*)CTFontCopyNameForGlyph(mHandle, (CGGlyph)index) UTF8String];
    
    CGRect boundingRect;
    CGSize advance;
    CGPathRef path;
    CGMutablePathRef ppath;
    
    CTFontGetBoundingRectsForGlyphs(mHandle, kCTFontOrientationDefault, (CGGlyph*)&index, &boundingRect);
    CTFontGetAdvancesForGlyphs(mHandle, kCTFontOrientationDefault, (CGGlyph*)&index, &advance);
    path = CTFontCreatePathForGlyph(mHandle, (CGGlyph)index, NULL);
    ppath = CGPathCreateMutableCopy(ppath);
    
    infos.size.width = boundingRect.size.width;
    infos.size.height = boundingRect.size.height;
    infos.advance.width = advance.width;
    infos.advance.height = advance.height;
    infos.path = ARA::MakePtr<OSXPath>(application(), ppath);
    
    CFRelease(path);
    CFRelease(ppath);
    
    mGlyphInfos[index] = infos;
    return infos;
}
