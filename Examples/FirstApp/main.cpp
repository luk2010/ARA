//
//  main.cpp
//  ARA
//
//  Created by jacques tronconi on 21/11/2023.
//

#include "ARA/Core/ARAElement.h"
#include "ARA/Core/ARAApplication.h"
#include "ARA/Core/ARAWindow.h"
#include "ARA/Core/ARAPlugin.h"
#include "ARA/Text/ARATextElement.h"

class MyAppObserver : public ARA::Application::Observer,
                      public ARA::Window::Observer,
                      public ARA::Text::Element
{
    ARA::Ptr<ARA::Window> mWindow;
    ARA::Ptr<ARA::Font> mFont;
    
public:
    
    MyAppObserver():
    ARA::Text::Element(ARA::Text::String("Hello World!"), ARA::Text::ParagraphAttributes{
        .alignment = ARA::Text::Alignment::Justified
    })
    {
        setPadding({ 10.0, 10.0, 10.0, 10.0 });
    }
    
    void onAppReady(ARA::Application& app)
    {
        mWindow = app.createWindow({ 1024, 768 }, { .resizable = true }, "First App With ARA");
        
        mWindow->setObserver(std::dynamic_pointer_cast<ARA::Window::Observer>(shared_from_this()));
        mWindow->setContentView(view());
        
        mWindow->show();
        mWindow->center();
        
        mFont = app.createFont("Courier New", 24, ARA::Font::Italic);
    }
    
    void onWindowClose(ARA::Window& window)
    {
        window.application().terminate();
    }
    
    bool onClick(ARA::View& view, ARA::MouseButton button, const ARA::Point2& location, size_t index, ARA::Char32 character)
    {
        std::cout << "Clicked on index: " << index << std::endl;
        return false;
    }
    
protected:
    
    ARA::Ptr<ARA::View> createView(ARA::Application& app)
    {
        auto view = ARA::Element::createView(app);
        
        setBackgroundColor({ 0.8, 0.3, 0.7, 1.0 });
        setBorderWidth(1.0);
        setCornerRadius(ARA::RectCorner::TopRight, 100.0);
        
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
