////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Text/ARATextString.h
//! @date
//!     2023/11/27
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_TEXT_STRING_H__
#define __ARA_TEXT_STRING_H__

#include "ARATextPlatform.h"
#include "ARA/Core/ARARange.h"

ARA_TEXT_BEGIN_NS

//! @brief
//! Defines available encoding.
enum class StringEncoding
{
    Ascii,
    Utf8,
    Utf16,
    Utf32
};

//! @brief
//! Defines attributes for a character.
struct CharAttributes
{
    //! @brief
    //! The character color.
    std::optional<ARA::Color> color;
    
    //! @brief
    //! The character font.
    std::optional<ARA::Ptr<Font>> font;
    
    //! @brief
    //! Merges this attributes with a given attributes.
    inline CharAttributes& merge(const CharAttributes& rhs)
    {
        if (rhs.color.has_value())
            color = rhs.color;
        if (rhs.font.has_value() && rhs.font.value())
            font = rhs.font;
        return *this;
    }
    
    //! @brief
    //! Returns true if this attributes are equal to given one.
    //!
    inline bool operator == (const CharAttributes& rhs) const
    {
        return color == rhs.color && font == rhs.font;
    }
};

//! @brief
//! A String Error.
ARA_DECLARE_ERROR(StringError)

//! @brief
//! A UTF-32 encoded string that holds one attribute per character.
class String
{
    //! @brief
    //! The UTF32 data.
    std::vector<Char32> mData;
    
    //! @brief
    //! The attributes for the string characters.
    std::vector<CharAttributes> mAttributes;
    
public:
    
    //! @brief
    //! Creates an empty string.
    String();
    
    //! @brief
    //! Creates a new String from a UTF8 encoded C string.
    String(std::string_view utf8str);
    
    //! @brief
    //! Creates a new String from a buffer of data with the given encoding.
    String(const void* data, size_t length, StringEncoding encoding);
    
    //! @brief
    //! Returns the string length.
    inline size_t length() const
    {
        if (mData.empty())
            return 0;
        return mData.size();
    }
    
    //! @brief
    //! Returns the character at given index.
    inline Char32& at(size_t index)
    {
        if (length() <= index)
            throw StringError("[ARA::Text::String] Invalid index ", index, ".");
        return mData[index];
    }
    
    //! @brief
    //! Returns the character at given index.
    inline const Char32& at(size_t index) const
    {
        if (length() <= index)
            throw StringError("[ARA::Text::String] Invalid index ", index, ".");
        return mData[index];
    }
    
    //! @brief
    //! Returns the attributes at given index.
    inline CharAttributes& attributesAt(size_t index)
    {
        if (length() <= index)
            throw StringError("[ARA::Text::String] Invalid index ", index, "/", mAttributes.size(), ".");
        return mAttributes[index];
    }
    
    //! @brief
    //! Returns the attributes at given index.
    inline const CharAttributes& attributesAt(size_t index) const
    {
        if (length() <= index)
            throw StringError("[ARA::Text::String] Invalid index ", index, "/", mAttributes.size(), ".");
        return mAttributes[index];
    }
    
    //! @brief
    //! Sets the attributes at given range.
    void setAttributes(const Range& range, const CharAttributes& attributes);
    
    //! @brief
    //! Inserts UTF8 C String data in the string.
    //!
    //! @param index
    //!     The index where to insert the data.
    //! @param utf8str
    //!     The C string to insert in the string.
    //! @param usePreviousAttributes
    //!     Boolean true (by default) means that the function will use the
    //!     attributes from the previous character for the inserted string.
    //!     If false, the `attributes` parameter is used instead.
    //! @param attributes
    //!     The attributes used to initialize the inserted range, only
    //!     if `usePreviousAttributes` is false.
    void insert(size_t index, const std::string_view& utf8str, bool usePreviousAttributes = true, const CharAttributes& attributes = {});
    
    //! @brief
    //! Inserts UTF-32 String data in the string.
    //!
    //! @param index
    //!     The index where to insert the data.
    //! @param str
    //!     The UTF-32 string to insert in the string. The attributes in the string are conserved
    //!     and not merged with the current string attributes.
    //!
    void insert(size_t index, const String& str);
    
    //! @brief
    //! Appends a UTF8 C String to the string.
    //!
    //! @param utf8str
    //!     The C string to insert in the string.
    //! @param usePreviousAttributes
    //!     Boolean true (by default) means that the function will use the
    //!     attributes from the previous character for the inserted string.
    //!     If false, the `attributes` parameter is used instead.
    //! @param attributes
    //!     The attributes used to initialize the inserted range, only
    //!     if `usePreviousAttributes` is false.
    //!
    void append(const std::string_view& utf8str, bool usePreviousAttributes = true, const CharAttributes& attributes = {});
    
    //! @brief
    //! Appends a UTF-32 String data to the string.
    //!
    //! @param str
    //!     The UTF-32 string to append to the string. The attributes in the string are conserved
    //!     and not merged with the current string attributes.
    //!
    void append(const String& str);
    
    //! @brief
    //! Erases a given range of characters in the string.
    //!
    void erase(const Range& range);
    
    //! @brief
    //! Clears the current string.
    //!
    void clear();
    
    //! @brief
    //! Returns the string as a UTF8 string.
    std::string utf8() const; 
    
    //! @brief
    //! Returns the index of the first letter of a word at given index.
    //!
    size_t findIndexOfWord(size_t index) const; 
    
    //! @brief
    //! Returns an iterator to the first character of the string.
    inline auto begin() { return mData.begin(); }
    
    //! @brief
    //! Returns an iterator to the first character of the string.
    inline auto begin() const { return mData.begin(); }
    
    //! @brief
    //! Returns an iterator to the end of the string.
    inline auto end() { return mData.end(); }
    
    //! @brief
    //! Returns an iterator to the end of the string.
    inline auto end() const { return mData.end(); }
    
    //! @brief
    //! Returns a reverse iterator to the first character of the string.
    inline auto rbegin() { return mData.rbegin(); }
    
    //! @brief
    //! Returns an iterator to the first character of the string.
    inline auto rbegin() const { return mData.rbegin(); }
    
    //! @brief
    //! Returns a reverse iterator to the end of the string.
    inline auto rend() { return mData.rend(); }
    
    //! @brief
    //! Returns a reverse iterator to the end of the string.
    inline auto rend() const { return mData.rend(); }
};

//! @brief
//! Prints a String into a std::ostream.
std::ostream& operator << (std::ostream& stream, const String& string);

ARA_TEXT_END_NS

#endif 
