////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file 
//!     ARA/Text/ARATextFrame.cpp
//! @date
//!     2023/11/27
//! @author 
//!     Luk2010, Atlanti's Corp
//! @copyright 
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ARATextFrame.h"
#include "ARATextGlyphRun.h"
#include "ARA/Core/ARAApplication.h"

ARA_TEXT_BEGIN_NS

constexpr Color Black = { 0, 0, 0, 1 };

Frame::Frame(const String& string, const Rect2& rect, const ParagraphAttributes& defaultAttribs):
mDefAttributes(defaultAttribs)
{
    setFrame(rect);
    insert(0, string);
}

void Frame::insert(size_t index, const String& string)
{
    mString.insert(index, string);
    
    if (string.length())
    {
        // We need to parse the string to know the list of paragraphs.
        
        RangeList paragraphsRanges = getParagraphsRangesInString(string);
        
        if (paragraphsRanges.empty())
            throw std::runtime_error("Error while computing paragraph ranges.");
        
        const Range& firstRange = paragraphsRanges[0];
        size_t startOfRanges = 0;
        size_t indexOfParagraph = std::string::npos;
        size_t rangeIndex = 0;
        
        if (mParagraphs.size() > 0)
        {
            // Now we need to find the paragraph at given range.
            
            Paragraph& paragraphAtIndex = getParagraphAtIndex(index);
            
            // We need to insert the first string range in the paragraph.
            
            paragraphAtIndex.range.length += firstRange.length;
            paragraphAtIndex.needsLayout = true;
            
            startOfRanges = paragraphAtIndex.range.end();
            indexOfParagraph = getIndexOfParagraph(paragraphAtIndex);
            rangeIndex = 1;
        }
        
        std::vector<Paragraph> newParagraphs;
        
        // Now, for each range in the string, we need to create a new paragraph
        // and insert it after the first paragraph.
        
        for (; rangeIndex < paragraphsRanges.size(); ++rangeIndex)
        {

            Paragraph paragraph(mString);
            
            paragraph.needsLayout = true;
            paragraph.alignment = mDefAttributes.alignment.value_or(Alignment::Left);
            paragraph.lineBreakMode = mDefAttributes.lineBreakMode.value_or(LineBreakMode::Letter);
            paragraph.indentation = mDefAttributes.indentation.value_or(0.0);
            paragraph.interline = mDefAttributes.interline.value_or(0.0);
            paragraph.range =
            {
                .start = paragraphsRanges[rangeIndex].start + startOfRanges,
                .length = paragraphsRanges[rangeIndex].length
            };
            
            newParagraphs.push_back(paragraph);
        }
        
        // Now that we have our paragraphs, we inserts them into the paragraphs list.

        auto position = mParagraphs.begin() + (indexOfParagraph + 1);
        auto start = newParagraphs.begin();
        auto end = newParagraphs.end();

        mParagraphs.insert(position, start, end);
    }
}

void Frame::remove(size_t index, size_t count)
{
    mString.erase({ index, count });
    std::vector<size_t> paragraphsToRemove;
    bool breakFor = false;
    
    for (auto it = mParagraphs.begin(); it != mParagraphs.end() && !breakFor; it++)
    {
        switch ((*it).range.intersect({ index, count }))
        {
            case IntersectionResult::InsideL:
                // The current paragraph holds the whole range. Erase the range and see
                // what we have.
                (*it).range.remove({ index, count });
                
                if (!(*it).range.length)
                    paragraphsToRemove.push_back(std::distance(mParagraphs.begin(), it));
                else
                    (*it).needsLayout = true;
                
                breakFor = true;
                break;
                
            case IntersectionResult::InsideR:
                // Erase the paragraph.
                paragraphsToRemove.push_back(std::distance(mParagraphs.begin(), it));
                break;
                
            case IntersectionResult::Intersect:
                // Most difficult case. If the intersection is on the left side, it is a
                // terminating range and we can break the loop. If this is a right side,
                // we only remove the range and check for the paragraph new length.
                
                if ((*it).range.end() > index + count)
                    // Terminating paragraph: break for loop.
                    breakFor = true;
                
                (*it).range.remove({ index, count });
                
                if (!(*it).range.length)
                    paragraphsToRemove.push_back(std::distance(mParagraphs.begin(), it));
                else
                    (*it).needsLayout = true;

                break;
                
            default:
                break;
        }
    }
    
    if (mParagraphs.size() > paragraphsToRemove.size())
    {
        std::vector<Paragraph> newParagraphs;
        newParagraphs.reserve(mParagraphs.size() - paragraphsToRemove.size());
        
        for (size_t i = 0; i < mParagraphs.size(); ++i)
        {
            if (std::find(paragraphsToRemove.begin(), paragraphsToRemove.end(), i) != paragraphsToRemove.end())
                continue;
            
            newParagraphs.push_back(mParagraphs[i]);
        }
        
        mParagraphs = newParagraphs;
    }
    
    else
        mParagraphs.clear();
}

void Frame::setString(const String& string)
{
    mString.clear();
    mParagraphs.clear();
    insert(0, string);
}

void Frame::setFrame(const Rect2& frame)
{
    if (mRect != frame)
    {
        mRect = frame;
        
        for (auto& paragraph : mParagraphs)
            paragraph.needsLayout = true;
    }
}

RangeList Frame::getParagraphsRangesInString(const String& string) const
{
    RangeList ranges;
    Range currentRange;
    Char32 newLineChar = static_cast<Char32>('\n');
    
    for (auto c : string)
    {
        if (c == newLineChar)
        {
            if (currentRange.length > 0)
                ranges.push_back(currentRange);
            
            currentRange.start = currentRange.end();
            currentRange.length = 0;
        }
        else
            currentRange.length++;
    }
    
    // Adds the last range.
    
    if (currentRange.length)
        ranges.push_back(currentRange);
    
    return ranges;
}

Paragraph& Frame::getParagraphAtIndex(size_t index)
{
    for (auto& paragraph : mParagraphs)
    {
        if (paragraph.range.contains(index))
            return paragraph;
    }
    
    throw std::runtime_error("Cannot find a suitable Paragraph for index.");
}

const Paragraph& Frame::getParagraphAtIndex(size_t index) const
{
    for (const auto& paragraph : mParagraphs)
    {
        if (paragraph.range.contains(index))
            return paragraph;
    }
    
    throw std::runtime_error("Cannot find a suitable Paragraph for index.");
}

size_t Frame::getIndexOfParagraph(const Paragraph& paragraph) const
{
    for (auto it = mParagraphs.begin(); it != mParagraphs.end(); it++)
    {
        const Paragraph& rhs = *it;
        
        if (&rhs == &paragraph)
            return std::distance(mParagraphs.begin(), it);
    }
    
    return std::string::npos;
}

void Frame::draw(Drawer& drawer, const Point2& origin) const
{
    for (auto& paragraph : mParagraphs)
        drawParagraph(drawer, paragraph.origin, paragraph);
}

void Frame::drawParagraph(Drawer& drawer, const Point2& origin, const Paragraph& paragraph) const 
{
    if (origin.y >= mRect.maxY())
        return;

    for (auto& line : paragraph.lines) 
    {
        if (line.origin().y >= mRect.maxY())
            break;

        for (auto& run : line.runs())
        {
            if (run.origin().x + run.advance().width > mRect.maxX())
                break;

            drawer.setFillColor(run.attributes().color.value_or(Black));
            
            Point2 pt =
            {
                .x = origin.x + run.origin().x,
                .y = origin.y + line.origin().y + line.height()
            };

            for (auto& info : run.glyphInfos()) 
            {
                drawer.push();
                
                drawer.translate(pt);
                if (info.path)
                    drawer.fillPath(info.path);
                
                pt.x += info.advance.width;
                pt.y += info.advance.height;
                
                drawer.pop();
            }
        }
    }
}

void Frame::layout()
{
    Point2 origin = mRect.origin;
    
    for (auto& paragraph : mParagraphs)
    {
        if (paragraph.origin != origin)
        {
            paragraph.origin = origin;
            paragraph.needsLayout = true;
        }
        
        if (paragraph.needsLayout)
            layoutParagraph(paragraph);
        
        const Line& lastLine = (*paragraph.lines.rbegin());
        origin.y += lastLine.origin().y + lastLine.height();
        origin.y += mParagraphGap;
    }
}

void Frame::layoutParagraph(Paragraph& paragraph)
{
    // First, we must divide the paragraph into blocks that share the same
    // attributes.
    
    RangeList blocksRange = getSharedAttributesRangesForParagraph(paragraph);
    
    // Now we must create one GlyphRun for each block range.
    
    std::vector<GlyphRun> runs;
    
    for (const Range& range : blocksRange)
    {
        GlyphRun run(mString, range, mString.attributesAt(range.start));
        
        if (!run.hasFont())
            run.setFont(Application::Get().createFont("Arial", 18.0));
        
        run.build();
        runs.push_back(run);
    }
    
    // Now, we must create a new line and with a cursor, iterating over each glyph run.
    
    // If the current glyph run advance width is superior to the frame rectangle width + the
    // paragraph indentation margin, we find the glyph that overflow and depending on the paragraph
    // word breaking mode, we take the letter or the word before and create a new line.
    
    std::vector<Line> lines;
    
    Point2 cursor = { paragraph.origin.x + paragraph.indentation, paragraph.origin.y };
    Line line(mString, mRect.size.width - cursor.x);
    
    for (GlyphRun& run : runs)
    {
        run.setOrigin(cursor);
        
        if (cursor.x + run.advance().width > mRect.size.width)
        {
            size_t glyphOverflowIndex = run.findOverflowGlyphIndex(mRect.size.width);
            GlyphRun newLineRun(mString);
            
            if (glyphOverflowIndex == std::string::npos)
                throw FrameLayoutError("[ARA::Text::Frame] Error finding overflow glyph index.");
            
            if (glyphOverflowIndex)
            {
                if (paragraph.lineBreakMode == LineBreakMode::Letter)
                    newLineRun = run.divide(glyphOverflowIndex);
                
                else if (paragraph.lineBreakMode == LineBreakMode::Word)
                {
                    size_t wordBeginIndex = mString.findIndexOfWord(glyphOverflowIndex);
                    newLineRun = run.divide(wordBeginIndex);
                }
                
                line.add(run);
                lines.push_back(line);
                
                cursor.x = paragraph.origin.x + paragraph.indentation;
                cursor.y = cursor.y + paragraph.origin.y + paragraph.interline + line.height();
                
                line.clear();
                line.setOrigin(cursor);
                
                if (!newLineRun.empty())
                    line.add(newLineRun);
            }
            else
            {
                lines.push_back(line);
                
                cursor.x = paragraph.origin.x + paragraph.indentation;
                cursor.y = cursor.y + paragraph.origin.y + paragraph.interline + line.height();
                
                line.clear();
                line.setOrigin(cursor);
                
                if (!run.empty())
                    line.add(run);
            }
            
            continue;
        }
        
        else
        {
            line.add(run);
            cursor.x = cursor.x + run.advance().width;
            cursor.y = cursor.y + run.advance().height;
        }
    }
    
    if (line.runs().size() > 0)
        lines.push_back(line);
    
    // Now we must layout each line depending on the paragraph alignment.
    
    for (auto& line : lines)
        layoutLine(line, paragraph.alignment);
    
    // Now we set the paragraph lines.
    
    paragraph.lines = std::move(lines);
    paragraph.needsLayout = false;
    paragraph.size.width = mRect.size.width - paragraph.origin.x - paragraph.indentation;
    paragraph.size.height = 0.0;

    if (!paragraph.lines.empty()) 
    {
        auto const& lastLine = (*paragraph.lines.rbegin());
        paragraph.size.height = (lastLine.origin().y + lastLine.height()) - paragraph.origin.y;
    }
}

void Frame::layoutLine(Line& line, Alignment alignment)
{
    Point2 cursor = line.origin();
    Real offset = 0.0;
    
    switch (alignment)
    {
        case Alignment::Left:
            break;
            
        case Alignment::Right:
            offset = line.width() - line.lastRun().end().x;
            
            line.forEachRun([&](GlyphRun& run){
                Point2 newOrigin = run.origin();
                newOrigin.x += offset;
                run.setOrigin(newOrigin);
            });
            
            break;
            
        case Alignment::Center:
            offset = (line.width() - line.lastRun().end().x) / 2.0;
            
            line.forEachRun([&](GlyphRun& run){
                Point2 newOrigin = run.origin();
                newOrigin.x += offset;
                run.setOrigin(newOrigin);
            });
            
            break;
            
        case Alignment::Justified:
            
            line.forEachRun([&](GlyphRun& run){
                Point2 newOrigin = run.origin();
                newOrigin.x = offset;
                run.setOrigin(newOrigin);
                
                offset = run.end().x + ((line.width() - line.lastRun().end().x) / (line.runs().size() - 1));
            });
            
            break;
    }
}

RangeList Frame::getSharedAttributesRangesForParagraph(const Paragraph& paragraph) const
{
    RangeList ranges;
    size_t begin = paragraph.range.start;
    CharAttributes currentAttribs = mString.attributesAt(begin);
    
    for (size_t i = begin; i < paragraph.range.end(); ++i)
    {
        const CharAttributes& attribs = mString.attributesAt(i);
        
        if (attribs != currentAttribs)
        {
            ranges.push_back({ begin, i - 1 });
            begin = i;
            currentAttribs = attribs;
        }
    }
    
    ranges.push_back({ begin, paragraph.range.end() - begin });
    
    return ranges;
}

Real Frame::paragraphGap() const
{
    return mParagraphGap;
}

void Frame::setParagraphGap(Real space)
{
    mParagraphGap = space;
    
    for (Paragraph& paragraph : mParagraphs)
        paragraph.needsLayout = true;
}

bool Frame::needsLayout() const 
{
    if (mParagraphs.empty() && mString.length() > 0)
        return true;
    
    for (const Paragraph& paragraph : mParagraphs)
    {
        if (paragraph.needsLayout) 
            return true; 
    }

    return false;
}

size_t Frame::hitTest(const Point2& location) const 
{
    for (auto& paragraph : mParagraphs) 
    {
        Rect2 parRect = { paragraph.origin, paragraph.size };

        if (!parRect.contains(location)) 
            continue;

        for (auto& line : paragraph.lines) 
        {
            Rect2 lineRect = { line.origin(), { line.width(), line.height() }};

            if (!lineRect.contains(location)) 
                continue; 
            
            for (auto& run : line.runs())
            {
                const Rect2 runRect = { run.origin(), run.advance() };

                if (!runRect.contains(location)) 
                    continue; 
                
                Point2 cursor = run.origin();

                for (size_t i = 0; i < run.glyphInfos().size(); ++i) 
                {
                    Rect2 glyphRect = { cursor, run.glyphInfos()[i].size };

                    if (glyphRect.contains(location))
                        return run.range().start + i;
                }
            }
        }
    }

    return InvalidIndex;
}

ARA_TEXT_END_NS
