////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Text/ARATextLine.cpp
//! @date
//!     2023/12/08
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ARATextLine.h"

ARA_TEXT_BEGIN_NS

Line::Line(const String& string, Real width):
mString(string)
{
    mSize.width = width;
    mSize.height = 0.0;
}

void Line::add(const GlyphRun& run)
{
    mGlyphRuns.push_back(run);
    mSize.height = std::max(mSize.height, run.height());
    
    if (mGlyphRuns.size() == 1)
        mRange = run.range();
    else
        mRange.length += run.range().length;
}

Real Line::height() const
{
    return mSize.height;
}

Real Line::width() const
{
    return mSize.width;
}

void Line::clear()
{
    mGlyphRuns.clear();
    mSize = { 0, 0 };
    mRange = { 0, 0 };
    mOrigin = { 0, 0 };
}

void Line::setOrigin(const Point2& origin)
{
    mOrigin = origin;
}

const Point2& Line::origin() const
{
    return mOrigin;
}

GlyphRun& Line::lastRun()
{
    if (mGlyphRuns.empty())
        throw LineEmpty("[ARA::Text::Line] Line is empty so lastRun() cannot return.");
    
    return mGlyphRuns.at(mGlyphRuns.size() - 1);
}

const GlyphRun& Line::lastRun() const
{
    if (mGlyphRuns.empty())
        throw LineEmpty("[ARA::Text::Line] Line is empty so lastRun() cannot return.");
    
    return mGlyphRuns.at(mGlyphRuns.size() - 1);
}

const GlyphRunList& Line::runs() const
{
    return mGlyphRuns;
}

Line& Line::operator=(const Line& rhs)
{
    mGlyphRuns = rhs.mGlyphRuns;
    mSize = rhs.mSize;
    mOrigin = rhs.mOrigin;
    mRange = rhs.mRange;
    return *this;
}

ARA_TEXT_END_NS
