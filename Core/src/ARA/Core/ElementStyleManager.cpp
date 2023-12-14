////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Core/ElementStyleManager.cpp
//! @date
//!     2023/12/14
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ARA/Core/ElementStyleManager.h"

ARA_BEGIN_NAMESPACE

ElementStyleManager& ElementStyleManager::Shared()
{
    static ElementStyleManager instance;
    return instance;
}

void ElementStyleManager::add(const ElementStylePtr& style)
{
    auto it = std::find_if(mStyles.begin(), mStyles.end(), [&style](auto& rhs){
        return rhs->name() == style->name();
    });
    
    if (it != mStyles.end())
        throw Error("[ElementStyleManager] Style '", style->name(), "' is already registered.");
    
    mStyles.push_back(style);
}

void ElementStyleManager::remove(const ElementStylePtr& style)
{
    auto it = std::find(mStyles.begin(), mStyles.end(), style);
    
    if (it != mStyles.end())
        mStyles.erase(it);
}

ElementStylePtr ElementStyleManager::find(const std::string& name) const
{
    auto it = std::find_if(mStyles.begin(), mStyles.end(), [&name](auto& rhs){
        return rhs->name() == name;
    });
    
    if (it != mStyles.end())
        return *it;
    
    return nullptr;
}

ElementStylePtr ElementStyleManager::newStyle(const std::string& name, const ElementStylePtr& parent)
{
    ElementStylePtr style = MakePtr < ElementStyle >(name, parent);
    
    add(style);
    
    return style;
}

ElementStylePtr ElementStyleManager::newStyle(const std::string& name, const std::string& parentName)
{
    return newStyle(name, find(parentName));
}

ARA_END_NAMESPACE
