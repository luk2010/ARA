//
//  ARAPlugin.h
//  ARA
//
//  Created by jacques tronconi on 26/11/2023.
//

#ifndef ARAPlugin_h
#define ARAPlugin_h

#include "ARADynLib.h"

ARA_BEGIN_NAMESPACE

//! @brief
//! An Error launched by a Plugin.
ARA_DECLARE_ERROR(PluginError)

//! @brief
//! A Class that uses a DynLib object to load a plugin.
template < class T >
class Plugin
{
    //! @brief
    //! The dynamic library object.
    Ptr<DynLib> mDynLib;
    
public:
    
    //! @brief
    //! Constructs a new Plugin.
    //! @param filePath
    //! The path to the plugin library.
    Plugin(const std::string& filePath)
    {
        mDynLib = MakePtr<DynLib>(filePath);
    }
    
    //! @brief
    //! Returns a pointer to the object the plugin should load.
    Ptr<T> load()
    {
        typedef Ptr<T> (*LoadPfn) ();
        LoadPfn function = (LoadPfn) mDynLib->find(ARA_PLUGIN_LOAD_PFN_NAME);
        
        ThrowIf<PluginError>(!function, "Cannot load function of plugin ", mDynLib->filePath(), ".");
        
        return function();
    }
    
    //! @brief
    //! Returns the dynamic library file path.
    const std::string& filePath() const
    {
        return mDynLib->filePath();
    }
};

ARA_END_NAMESPACE

#endif /* ARAPlugin_h */
