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
#include "ARAView.h"
#include "ARAPath.h"
#include "ARAFont.h"

#include "ARA/Core/ARAWindowStyle.h"
#include "ARA/Core/KeyCode.h"
#include "ARA/Core/RenderApi.h"
#include "ARA/Core/RenderView.h"
#include "ARA/Core/RenderViewController.h"
#include "ARA/Core/Factory.h"

ARA_BEGIN_NAMESPACE

class Window;

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
    static Ptr < Application > mInstance;
    
protected:
    
    //! @brief
    //! Creates a new application.
    Application();
    
public:
    
    //! @brief
    //! Destructs the application.
    virtual ~Application();
    
    //! @brief
    //! Returns the current instance, or create it if none were found.
    //!
    static Application& CreateOrGet();
    
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
    //! Creates a native view instance.
    //!
    //! @param controller
    //!     The `ARA::ViewController` instance that manages this view.
    //!
    virtual Ptr<View> createView(ViewController& controller) = 0;
    
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

    //! @brief 
    //! Returns the KeyCode for the given platform keycode. 
    //! 
    virtual KeyCode convertKeyCode(uint32_t keycode) const = 0;

    //! @brief 
    //! Returns the platform keycode for given KeyCode value.
    //! 
    virtual uint32_t convertKeyCode(KeyCode keycode) const = 0;

    //! @brief 
    //! Returns the default RenderAPI for the current application.
    //! 
    virtual RenderAPI getPreferredRenderAPI() const = 0;

    //! @brief 
    //! Returns the available RenderAPI for the current application.
    //! 
    virtual RenderAPIList getAvailableRenderAPIs() const = 0;
    
    //! @brief
    //! Returns true if the application can create a RenderView with the given
    //! RenderAPI.
    //!
    virtual bool canCreateRenderView(RenderAPI renderApi) const;
    
    //! @brief
    //! Creates a RenderView instance conforming to the given RenderAPI.
    //!
    virtual RenderViewPtr createRenderView(RenderAPI renderApi, RenderViewController& controller) = 0;
};

typedef Ptr < Application > ApplicationPtr;
typedef std::function < ApplicationPtr() > ApplicationConstructor;
typedef SingleFactory < std::string, ApplicationConstructor > ApplicationFactory;

ARA_END_NAMESPACE

#endif /* ARAApplication_h */
