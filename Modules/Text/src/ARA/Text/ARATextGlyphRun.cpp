////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Text/ARATextGlyphRun.cpp
//! @date
//!     2023/12/08
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ARATextGlyphRun.h"

ARA_TEXT_BEGIN_NS

GlyphRun::GlyphRun(String& string):
mString(string)
{
    
}

GlyphRun::GlyphRun(String& string, const Range& range, const CharAttributes& attributes):
mString(string), mCharacters(range), mAttributes(attributes)
{
    
}

bool GlyphRun::hasFont() const
{
    return mAttributes.font.has_value() ?
        (bool) mAttributes.font.value() :
        false;
}

void GlyphRun::setFont(const Ptr<Font>& font)
{
    if (!font)
        throw GlyphRunNullFont("[ARA::Text::GlyphRun] Run has invalid font.");
    
    mAttributes.font = font;
}

void GlyphRun::build()
{
    auto font = mAttributes.font.value();
    
    if (!font)
        throw GlyphRunNullFont("[ARA::Text::GlyphRun] Run has invalid font.");
    
    mGlyphInfos.clear();
    mGlyphInfos.reserve(mCharacters.length);
    mAdvance = { 0, 0 };
    
    for (size_t i = mCharacters.start; i < mCharacters.end(); ++i)
    {
        GlyphInfo infos = font->glyphInfo(font->glyphIndex(mString.at(i)));
        mAdvance.width += infos.advance.width;
        mAdvance.height += infos.advance.height;
        mGlyphInfos.push_back(infos);
    }
}

void GlyphRun::setOrigin(const Point2& origin)
{
    mOrigin = origin;
}

Point2 GlyphRun::origin() const
{
    return mOrigin;
}

const Size2& GlyphRun::advance() const
{
    return mAdvance;
}

size_t GlyphRun::findOverflowGlyphIndex(Real width) const
{
    if (mOrigin.x + mAdvance.width <= width)
        return std::string::npos;
    
    Real cursor = mOrigin.x;
    
    for (size_t i = 0; i < mGlyphInfos.size(); ++i)
    {
        if (cursor + mGlyphInfos[i].advance.width > width)
            return i;
        
        cursor += mGlyphInfos[i].advance.width;
    }
    
    return std::string::npos;
}

GlyphRun GlyphRun::divide(size_t index)
{
    if (!mCharacters.contains(index))
        throw IndexError("[ARA::Text::GlyphRun] Index is out of bounds.");
    
    GlyphRun newRun(mString);
    
    if (!index)
        return newRun;
    
    newRun.mCharacters = { index, mCharacters.length - index };
    newRun.mAttributes = mAttributes;
    
    if (!mGlyphInfos.empty())
    {
        newRun.mGlyphInfos.insert(newRun.mGlyphInfos.end(), 
                                  mGlyphInfos.begin() + index,
                                  mGlyphInfos.end());
        mGlyphInfos.erase(mGlyphInfos.begin() + index, 
                          mGlyphInfos.begin() + mCharacters.length - index);
        
        mAdvance = { 0, 0 };
        
        for (const GlyphInfo& infos : newRun.mGlyphInfos)
        {
            newRun.mAdvance.width += infos.advance.width;
            newRun.mAdvance.height += infos.advance.height;
        }
        
        for (const GlyphInfo& infos : mGlyphInfos)
        {
            mAdvance.width += infos.advance.width;
            mAdvance.height += infos.advance.height;
        }
        
        newRun.mOrigin.x = mOrigin.x + mAdvance.width;
        newRun.mOrigin.y = mOrigin.y;
    }
    
    return newRun;
}

Real GlyphRun::height() const
{
    if (!mAttributes.font.has_value())
        return 0.0;
    
    auto font = mAttributes.font.value();
    
    if (!font)
        return 0.0;
    
    return font->size();
}

const Range& GlyphRun::range() const
{
    return mCharacters;
}

bool GlyphRun::empty() const
{
    return mCharacters.length == 0;
}

Point2 GlyphRun::end() const
{
    Point2 pt;
    
    pt.x = mOrigin.x + mAdvance.width;
    pt.y = mOrigin.y + mAdvance.height;
    
    return pt;
}

const GlyphInfoList& GlyphRun::glyphInfos() const 
{
    return mGlyphInfos;
}

const CharAttributes& GlyphRun::attributes() const 
{
    return mAttributes;
}

GlyphRun& GlyphRun::operator = (const GlyphRun& run) 
{
    mCharacters = run.mCharacters;
    mAttributes = run.mAttributes;
    mGlyphInfos = run.mGlyphInfos;
    mAdvance = run.mAdvance;
    mOrigin = run.mOrigin;
    return *this;
}

ARA_TEXT_END_NS
