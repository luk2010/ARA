//
//  ARAGlyphInfo.h
//  ARA-SDK
//
//  Created by jacques tronconi on 27/11/2023.
//

#ifndef ARAGlyphInfo_h
#define ARAGlyphInfo_h

#include "ARASize2.h"
#include "ARAPath.h"

ARA_BEGIN_NAMESPACE

//! @brief
//! Stores informations about a Glyph.
struct GlyphInfo
{
    //! @brief
    //! The Glyph name, if available.
    std::string name;
    
    //! @brief
    //! The Glyph path.
    Ptr<Path> path;
    
    //! @brief
    //! The advance of the glyph.
    Size2 advance;
};

typedef std::vector<GlyphInfo> GlyphInfoList;

ARA_END_NAMESPACE

#endif /* ARAGlyphInfo_h */
