//
//  ARAApplication.h
//  lui
//
//  Created by jacques tronconi on 26/11/2023.
//

#ifndef ARAApplication_h
#define ARAApplication_h

#include "ARAPlatform.h"
#include "ARAError.h"
#include "ARAWindow.h"
#include "ARAView.h"
#include "ARAPath.h"
#include "ARAFont.h"

ARA_BEGIN_NAMESPACE

//! @brief
//! The Application Error subclass.
ARA_DECLARE_ERROR(ApplicationError)

//! @brief
//! An Application object.
class Application
{
public:
    
    //! @brief
    //! The Application Observer.
    struct Observer
    {
        //! @brief
        //! Destructor.
        virtual ~Observer() = default;
        
        //! @brief
        //! The application has finished its preparation and is ready to run.
        virtual void onAppReady(Application& app) { }
        
        //! @brief
        //! The application will terminate.
        virtual void onAppTerminate(Application& app) { }
    };
    
private:
    
    //! @brief
    //! The observer for this application.
    Weak<Observer> mObserver;
    
    //! @brief
    //! The current application instance.
    static Application* mInstance;
    
public:
    
    //! @brief
    //! Creates a new application.
    Application();
    
    //! @brief
    //! Destructs the application.
    virtual ~Application();
    
    //! @brief
    //! Returns the current application.
    static Application& Get();
    
    //! @brief
    //! Sets the current application observer.
    inline void setObserver(const Ptr<Observer>& observer) { mObserver = observer; }
    
    //! @brief
    //! Returns the current application observer.
    inline Ptr<Observer> observer() { return mObserver.lock(); }
    
    //! @brief
    //! Returns the current application observer.
    inline Ptr<const Observer> observer() const { return mObserver.lock(); }
    
    //! @brief
    //! Runs the application.
    virtual int run(int argc = 0, const char** argv = NULL) = 0;
    
    //! @brief
    //! Terminates the application.
    virtual void terminate() = 0;
    
    //! @brief
    //! Creates a new window.
    virtual Ptr<Window> createWindow(const Size2& size = { 1024, 768 },
                                     const WindowStyle& style = {},
                                     const std::string& title = {}) = 0;
    
    //! @brief
    //! Creates a native view.
    virtual Ptr<View> createView() = 0;
    
    //! @brief
    //! Creates a native Path from an origin point.
    virtual Ptr<Path> createPath(const Point2& origin = { 0, 0 }) = 0;
    
    //! @brief
    //! Creates a new font.
    //!
    //! @param familyName
    //!     The font family name to look for.
    //! @param size
    //!     The font size to load.
    //! @param traits
    //!     The font traits to apply to the font.
    //!
    //! @return
    //! A font instance if the font is found, nullptr otherwise.
    virtual Ptr<Font> createFont(std::string_view familyName, Real size, Font::TraitsMask traits = (Font::TraitsMask)0) = 0;
};

ARA_END_NAMESPACE

#endif /* ARAApplication_h */
