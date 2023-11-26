//
//  ARAApplicationObject.h
//  lui
//
//  Created by jacques tronconi on 26/11/2023.
//

#ifndef ARAApplicationObject_h
#define ARAApplicationObject_h

#include "ARAPlatform.h"

ARA_BEGIN_NAMESPACE

class Application;

//! @brief
//! A base class for objects created by `ARA::Application`.
class ApplicationObject
{
    //! @brief
    //! The application that created this instance.
    Application& mApp;
    
public:
    
    //! @brief
    //! Creates a new instance.
    inline ApplicationObject(Application& app): mApp(app) {}
    
    //! @brief
    //! Virtual destructor to enable RTTI.
    virtual ~ApplicationObject() = default;
    
    //! @brief
    //! Returns the application.
    inline Application& application() { return mApp; }
    
    //! @brief
    //! Returns the application.
    inline const Application& application() const { return mApp; }
};

ARA_END_NAMESPACE

#endif /* ARAApplicationObject_h */
