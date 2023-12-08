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

OSXFont::OSXFont(ARA::Application& app, NSFont* handle):
ARA::Font(app), mHandle(handle)
{
    
}

OSXFont::~OSXFont()
{
    
}

std::string OSXFont::familyName() const
{
    CFStringRef name = CTFontCopyFamilyName((CTFontRef)mHandle);
    
    std::string str = [(NSString*)name UTF8String];
    
    CFRelease(name);
    
    return str;
}

ARA::Real OSXFont::size() const
{
    return CTFontGetSize((CTFontRef)mHandle);
}

ARA::Font::TraitsMask OSXFont::traits() const
{
    CTFontSymbolicTraits traits = CTFontGetSymbolicTraits((CTFontRef)mHandle);
    int mask = 0;
    
    if (traits & kCTFontTraitBold) mask |= Bold;
    if (traits & kCTFontTraitItalic) mask |= Italic;
    if (traits & kCTFontTraitCondensed) mask |= Condensed;
    
    return (ARA::Font::TraitsMask) mask;
}

ARA::Charset OSXFont::charset() const
{
    return ARA::Charset::Unicode;
}

ARA::GlyphIndex OSXFont::glyphIndex(ARA::Char32 character) const
{
    CGGlyph index = 0;
    
    if (!CTFontGetGlyphsForCharacters((CTFontRef)mHandle, (UniChar*)&character, &index, 1))
        throw CTFontError("[OSXFont] CTFontGetGlyphsForCharacters() failed.");
    
    return (ARA::GlyphIndex) index;
}

ARA::GlyphInfo OSXFont::glyphInfo(ARA::GlyphIndex index) const
{
    auto it = mGlyphInfos.find(index);
    
    if (it != mGlyphInfos.end())
        return it->second;
    
    ARA::GlyphInfo infos;
    
    infos.name = [(NSString*)CTFontCopyNameForGlyph((CTFontRef)mHandle, (CGGlyph)index) UTF8String];
    
    CGRect boundingRect;
    CGSize advance;
    CGPathRef path;
    CGMutablePathRef ppath;
    
    CTFontGetBoundingRectsForGlyphs((CTFontRef)mHandle, kCTFontOrientationDefault, (CGGlyph*)&index, &boundingRect, 1);
    CTFontGetAdvancesForGlyphs((CTFontRef)mHandle, kCTFontOrientationDefault, (CGGlyph*)&index, &advance, 1);
    path = CTFontCreatePathForGlyph((CTFontRef)mHandle, (CGGlyph)index, NULL);
    CGAffineTransform transform = CGAffineTransformMakeScale(1, -1);
    if (path)
        ppath = CGPathCreateMutableCopyByTransformingPath(path, &transform);
    
    infos.size.width = boundingRect.size.width;
    infos.size.height = boundingRect.size.height;
    infos.advance.width = advance.width;
    infos.advance.height = advance.height;
    
    if (path)
    {
        infos.path = ARA::MakePtr<OSXPath>(const_cast<ARA::Application&>(application()), (CGMutablePathRef) ppath);
        CFRelease(path);
    }
    
    mGlyphInfos[index] = infos;
    return infos;
}
