////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Text/ARATextFrame.h
//! @date
//!     2023/11/27
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_TEXT_TEXTFRAME_H__
#define __ARA_TEXT_TEXTFRAME_H__

#include "ARATextPlatform.h"
#include "ARATextString.h"
#include "ARATextParagraph.h"
#include "ARATextParagraphAttributes.h"

ARA_TEXT_BEGIN_NS

//! @brief
//! An error spotted when text frame calculation did wrong.
//!
ARA_DECLARE_ERROR(FrameLayoutError)

//! @brief
//! Defines an object which role is to organize a frame rectangle to display a text with multiple
//! attributes in it.
class Frame
{
    //! @brief
    //! The attributed string to analyze.
    String mString;
    
    //! @brief
    //! The current frame rectangle.
    Rect2 mRect;
    
    //! @brief
    //! The default paragraph attributes.
    //!
    ParagraphAttributes mDefAttributes;
    
    //! @brief
    //! The Paragraphs objects in this frame.
    std::vector<Paragraph> mParagraphs;
    
    //! @brief
    //! The space between two paragraphs.
    //!
    Real mParagraphGap = 0.0;
    
public:
    
    //! @brief
    //! Creates a new Frame.
    //!
    //! @param string
    //!     The attributed string (`ARA::Text::String`) to use.
    //! @param rect
    //!     The rectangle where to display the string.
    Frame(const String& string, const Rect2& rect, const ParagraphAttributes& defaultAttribs = {});
    
    //! @brief
    //! Returns the attributed string.
    inline const String& string() const { return mString; }
    
    //! @brief
    //! Returns the attributed string.
    //!
    inline String& string() { return mString; }
    
    //! @brief
    //! Adds a String to the current String at given index.
    void insert(size_t index, const String& string);
    
    //! @brief
    //! Removes a specified number of characters from given position.
    void remove(size_t index, size_t count = 1);
    
    //! @brief
    //! Returns the number of characters in the String.
    inline size_t charactersCount() const { return mString.length(); }
    
    //! @brief
    //! Sets the String.
    void setString(const String& string);
    
    //! @brief
    //! Returns the current frame rectangle.
    inline const Rect2& frame() const { return mRect; }
    
    //! @brief
    //! Sets the current frame rectangle.
    void setFrame(const Rect2& frame);
    
    //! @brief
    //! Returns the Paragraphs in this frame.
    const std::vector<Paragraph>& paragraphs() const { return mParagraphs; }
    
    //! @brief
    //! Given a UTF-32 attributed string, returns the ranges in the string that defines
    //! a new paragraph.
    //!
    //! @note
    //! A Paragraph is defined when encountering a `\n` character.
    //!
    RangeList getParagraphsRangesInString(const String& string) const;
    
    //! @brief
    //! Returns the paragraph at the given string index.
    //!
    Paragraph& getParagraphAtIndex(size_t index);
    
    //! @brief
    //! Returns the paragraph at the given string index.
    //!
    const Paragraph& getParagraphAtIndex(size_t index) const;
    
    //! @brief
    //! Returns the index of a given paragraph.
    //!
    size_t getIndexOfParagraph(const Paragraph& paragraph) const; 
    
    //! @brief
    //! Draws the whole text at the given point of origin.
    //!
    void draw(Drawer& drawer, const Point2& origin) const;
    
    //! @brief
    //! Draws one paragraph.
    //!
    void drawParagraph(Drawer& drawer, const Point2& origin, const Paragraph& paragraph) const;
    
    //! @brief
    //! Layouts the whole document.
    //!
    void layout();
    
    //! @brief
    //! Layouts one paragraph.
    //!
    void layoutParagraph(Paragraph& paragraph);
    
    //! @brief
    //! Layouts a line.
    //!
    void layoutLine(Line& line, Alignment alignment);
    
    //! @brief
    //! Returns, in a paragraph, the ranges of string where consecutive characters have the
    //! same attributes.
    //!
    RangeList getSharedAttributesRangesForParagraph(const Paragraph& paragraph) const;
    
    //! @brief
    //! Returns the space between two paragraphs.
    //!
    Real paragraphGap() const;
    
    //! @brief
    //! Sets the space between two paragraphs.
    //!
    void setParagraphGap(Real space);

    //! @brief 
    //! Returns true if at least one paragraph needs layout. 
    //! 
    bool needsLayout() const; 

    //! @brief 
    //! Performs a hit test at the given location. 
    //!
    //! @param location
    //!     The location to test the hit.
    //! @param returnCaretIndex
    //!     True if the returned index should be a valid caret index.
    //! @param caretLRRatio
    //!     The ratio to apply to know if the caret should be returned on the left or on the
    //!     right of the hitten character.
    //!
    size_t hitTest(const Point2& location, bool returnCaretIndex = false, Real caretLRRatio = 0.5) const;
    
    //! @brief
    //! For a given character index, return the same index in the above line, or zero if
    //! there is no line above.
    //!
    //! @param index
    //!     The index in the text string.
    //!
    size_t getIndexInLineAbove(size_t index) const; 

    //! @brief
    //! For a given character index, return the same index in the below line, or the last index 
    //! if there is no line below.
    //!
    //! @param index
    //!     The index in the text string.
    //!
    size_t getIndexInLineBelow(size_t index) const; 
    
    //! @brief
    //! Sets the alignment for the paragraphs in the text frame.
    //!
    void setAlignment(Alignment alignment);
};

ARA_TEXT_END_NS

#endif
