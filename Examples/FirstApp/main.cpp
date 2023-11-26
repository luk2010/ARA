//
//  main.cpp
//  lui
//
//  Created by jacques tronconi on 21/11/2023.
//

#include "ARA/Core/ARAElement.h"
#include "ARA/Core/ARAApplication.h"
#include "ARA/Core/ARAWindow.h"
#include "ARA/Core/ARAPlugin.h"

class MyAppObserver : public ARA::Application::Observer,
                      public ARA::Window::Observer,
                      public ARA::Element
{
    ARA::Ptr<ARA::Window> mWindow;
    
public:
    
    void onAppReady(ARA::Application& app)
    {
        mWindow = app.createWindow();
        
        mWindow->setObserver(std::dynamic_pointer_cast<ARA::Window::Observer>(shared_from_this()));
        mWindow->setContentView(view());
        
        mWindow->show();
        mWindow->center();
    }
    
    void onWindowClose(ARA::Window& window)
    {
        window.application().terminate();
    }
    
protected:
    
    ARA::Ptr<ARA::View> createView(ARA::Application& app)
    {
        auto view = ARA::Element::createView(app);
        
        setBackgroundColor({ 0.8, 0.3, 0.7, 1.0 });
        setBorderWidth(1.0);
        
        return view;
    }
};

int main(int argc, const char * argv[]) 
{
    std::string pluginAppName;
    
    if constexpr (ARA::AreEqual(ARA_PLATFORM_NAME, "APPLE"))
        pluginAppName = "libARACocoa.dylib";
    else if constexpr (ARA::AreEqual(ARA_PLATFORM_NAME, "WINDOWS"))
        pluginAppName = "libARAWindows.dylib";
    else if constexpr (ARA::AreEqual(ARA_PLATFORM_NAME, "X11"))
        pluginAppName = "libARAX11.dylib";
    
    ARA::Plugin<ARA::Application> pluginApp(pluginAppName);
    ARA::Ptr<ARA::Application> app = pluginApp.load();
    
    ARA::ThrowIf<ARA::Error>(!app, "Cannot load application plugin.");
    
    ARA::Ptr<MyAppObserver> observer = ARA::MakePtr<MyAppObserver>();
    app->setObserver(observer);
    
    return app->run(argc, argv);
}
