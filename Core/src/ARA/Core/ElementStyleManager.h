////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Core/ElementStyleManager.h
//! @date
//!     2023/12/14
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_CORE_ELEMENTSTYLEMANAGER_H__
#define __ARA_CORE_ELEMENTSTYLEMANAGER_H__

#include "ARA/Core/ARAElementStyle.h"

ARA_BEGIN_NAMESPACE

//! @brief
//! A Manager that registers ElementStyles objects.
//!
class ElementStyleManager
{
    //! @brief
    //! The registered styles.
    //!
    ElementStyleList mStyles;
    
public:
    
    //! @brief
    //! Returns the shared manager instance.
    //!
    static ElementStyleManager& Shared();
    
    //! @brief
    //! Adds a style.
    //!
    void add(const ElementStylePtr& style);
    
    //! @brief
    //! Removes a style.
    //!
    void remove(const ElementStylePtr& style);
    
    //! @brief
    //! Finds a style with a given name.
    //!
    ElementStylePtr find(const std::string& name) const;
    
    //! @brief
    //! Creates a new style.
    //!
    //! @param name
    //!     The style name.
    //! @param parent
    //!     The parent style.
    //!
    ElementStylePtr newStyle(const std::string& name, const ElementStylePtr& parent = nullptr);
    
    //! @brief
    //! Creates a new style.
    //!
    //! @param name
    //!     The style name.
    //! @param parentName
    //!     The parent style name.
    //!
    ElementStylePtr newStyle(const std::string& name, const std::string& parentName);
};

ARA_END_NAMESPACE

#endif
