////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Text/ARATextString.cpp
//! @date
//!     2023/11/27
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ARATextString.h"

ARA_TEXT_BEGIN_NS

static std::vector<Char32> utf8_to_utf32(const std::string_view& utf8_str)
{
    std::vector<Char32> utf32_str;
    
    for (size_t i = 0; i < utf8_str.length(); ) 
    {
        char32_t code_point;
        
        // Check the number of bytes in the current UTF-8 character
        if ((utf8_str[i] & 0b10000000) == 0) 
        {
            // 1-byte character
            code_point = static_cast<char32_t>(utf8_str[i]);
            ++i;
        } 
        else if ((utf8_str[i] & 0b11100000) == 0b11000000)
        {
            // 2-byte character
            code_point = static_cast<char32_t>(utf8_str[i] & 0b00011111) << 6;
            code_point |= static_cast<char32_t>(utf8_str[i + 1] & 0b00111111);
            i += 2;
        } 
        else if ((utf8_str[i] & 0b11110000) == 0b11100000)
        {
            // 3-byte character
            code_point = static_cast<char32_t>(utf8_str[i] & 0b00001111) << 12;
            code_point |= static_cast<char32_t>(utf8_str[i + 1] & 0b00111111) << 6;
            code_point |= static_cast<char32_t>(utf8_str[i + 2] & 0b00111111);
            i += 3;
        } 
        else if ((utf8_str[i] & 0b11111000) == 0b11110000)
        {
            // 4-byte character
            code_point = static_cast<char32_t>(utf8_str[i] & 0b00000111) << 18;
            code_point |= static_cast<char32_t>(utf8_str[i + 1] & 0b00111111) << 12;
            code_point |= static_cast<char32_t>(utf8_str[i + 2] & 0b00111111) << 6;
            code_point |= static_cast<char32_t>(utf8_str[i + 3] & 0b00111111);
            i += 4;
        } 
        else
        {
            // Invalid UTF-8 sequence
            // You may want to handle this case according to your needs
            throw std::invalid_argument("Invalid UTF-8 sequence");
        }
        
        utf32_str.push_back(code_point);
    }
    
    return utf32_str;
}

static std::vector<Char32> utf16_to_utf32(const std::u16string_view& utf16_str)
{
    std::vector<Char32> utf32_str;
    
    for (size_t i = 0; i < utf16_str.length(); ) 
    {
        char32_t code_point;
        
        // Check if it's a surrogate pair
        if (utf16_str[i] >= 0xD800 && utf16_str[i] <= 0xDBFF) 
        {
            // High surrogate
            code_point = static_cast<Char32>(utf16_str[i] - 0xD800) << 10;
            
            if (++i < utf16_str.length() && utf16_str[i] >= 0xDC00 && utf16_str[i] <= 0xDFFF)
                // Low surrogate
                code_point |= utf16_str[i] - 0xDC00;
            else
                // Invalid surrogate pair
                throw std::invalid_argument("Invalid UTF-16 surrogate pair");
        } 
        else
            // Not a surrogate pair
            code_point = utf16_str[i];
        
        utf32_str.push_back(code_point);
        ++i;
    }
    
    return utf32_str;
}

static std::string utf32_to_utf8(const std::vector<Char32>& utf32_str)
{
    std::string utf8_str;
    
    for (char32_t code_point : utf32_str) 
    {
        if (code_point <= 0x7F)
            // 1-byte character
            utf8_str.push_back(static_cast<char>(code_point));
        else if (code_point <= 0x7FF) 
        {
            // 2-byte character
            utf8_str.push_back(static_cast<char>(0xC0 | ((code_point >> 6) & 0x1F)));
            utf8_str.push_back(static_cast<char>(0x80 | (code_point & 0x3F)));
        } 
        else if (code_point <= 0xFFFF)
        {
            // 3-byte character
            utf8_str.push_back(static_cast<char>(0xE0 | ((code_point >> 12) & 0x0F)));
            utf8_str.push_back(static_cast<char>(0x80 | ((code_point >> 6) & 0x3F)));
            utf8_str.push_back(static_cast<char>(0x80 | (code_point & 0x3F)));
        } 
        else if (code_point <= 0x10FFFF) 
        {
            // 4-byte character
            utf8_str.push_back(static_cast<char>(0xF0 | ((code_point >> 18) & 0x07)));
            utf8_str.push_back(static_cast<char>(0x80 | ((code_point >> 12) & 0x3F)));
            utf8_str.push_back(static_cast<char>(0x80 | ((code_point >> 6) & 0x3F)));
            utf8_str.push_back(static_cast<char>(0x80 | (code_point & 0x3F)));
        } 
        else
            // Invalid code point
            throw std::invalid_argument("Invalid UTF-32 code point");
    }
    
    return utf8_str;
}

String::String()
{
    
}

String::String(std::string_view utf8str)
{
    mData = utf8_to_utf32(utf8str);
    mAttributes.resize(mData.size(), CharAttributes());
}

String::String(const void* data, size_t length, StringEncoding encoding)
{
    if (data && length)
    {
        if (encoding == StringEncoding::Ascii)
        {
            mData.resize(length);
            for (size_t i = 0; i < length; ++i)
                mData[i] = static_cast<Char32>(((const char*)data)[i]);
        }
        else if (encoding == StringEncoding::Utf8)
            mData = utf8_to_utf32(std::string_view(data, length));
        else if (encoding == StringEncoding::Utf16)
            mData = utf16_to_utf32(std::u16string_view((const char16_t*)data), length);
        else if (encoding == StringEncoding::Utf32)
            mData.insert(mData.begin(), (const Char32*)data, ((const Char32*)data) + length);
    }
    
    if (mData.size())
        mAttributes.resize(mData.size());
}

void String::setAttributes(const Range& range, const CharAttributes& attributes)
{
    for (size_t i = range.start; i < range.end() && i < mAttributes.size(); ++i)
        mAttributes[i].merge(attributes);
}

void String::insert(size_t index, const std::string_view& utf8str, bool usePreviousAttributes, const CharAttributes& attributes)
{
    auto utf32str = utf8_to_utf32(utf8str);
    
    mData.insert(mData.begin() + index, utf32str.begin(), utf32str.end());
    mAttributes.insert(mAttributes.begin() + index, usePreviousAttributes ? mAttributes[index] : attributes);
}

void String::insert(size_t index, const String& str)
{
    mData.insert(mData.begin() + index, 
                 str.mData.begin(),
                 str.mData.end());
    
    mAttributes.insert(mAttributes.begin() + index,
                       str.mAttributes.begin(),
                       str.mAttributes.end());
}

void String::append(const std::string_view& utf8str, bool usePreviousAttributes, const CharAttributes& attributes)
{
    insert(length(), utf8str, usePreviousAttributes, attributes);
}

void String::append(const String& str)
{
    insert(length(), str);
}

void String::erase(const Range& range)
{
    mData.erase(mData.begin() + range.start, mData.begin() + range.end());
    mAttributes.erase(mAttributes.begin() + range.start, mAttributes.begin() + range.end());
}

void String::clear()
{
    mData.clear();
    mAttributes.clear();
}

std::string String::utf8() const
{
    if (mData.size())
        return utf32_to_utf8(mData);
    return std::string();
}

size_t String::findIndexOfWord(size_t index) const
{
    if (index >= mData.size())
        return std::string::npos;
    
    char32_t c = mData[index];
    
    while (!std::isspace(c) && index > 0)
        c = mData[index--];
    
    return index;
}

std::ostream& operator << (std::ostream& stream, const String& string)
{
    return stream << string.utf8();
}

ARA_TEXT_END_NS

