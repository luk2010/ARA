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
#include "ARA/Core/ElementStyleManager.h"
#include "ARA/Controls/Controls.h"

class MyButtonList : public ARA::Element
{
    ARA::Controls::ButtonList mButtons;
    
public:
    
    MyButtonList()
    {
        auto button = ARA::MakePtr < ARA::Controls::Button >(ARA::Text::String("Button 1"));
        
        button->setFrameSize({ 200, 40 });
        
        mButtons.push_back(button);
    }
    
protected:
    
    virtual void layoutChildren(ARA::View& view) const
    {
        mButtons[0]->setFrameOrigin({ 100, 10 });
    }
};

class MyAppObserver : public ARA::Application::Observer,
                      public ARA::Window::Observer,
                      public ARA::Text::Element
{
    ARA::Ptr<ARA::Window> mWindow;
    ARA::Ptr<ARA::Font> mFont;
    
    ARA::Ptr < MyButtonList > mButtonList;
    
public:
    
    MyAppObserver():
    ARA::Text::Element(ARA::Text::String("Hello World!"), ARA::Text::ParagraphAttributes{
        .alignment = ARA::Text::Alignment::Justified
    })
    {
        setPadding({ 10.0, 10.0, 10.0, 10.0 });
        setBackgroundColor({ 0.8, 0.3, 0.7, 1.0 });
        setBorderWidth(1.0);
        setCornerRadius(ARA::RectCorner::TopRight, 100.0);
        
        mButtonList = ARA::MakePtr < MyButtonList >();
        add(mButtonList);
    }
    
    void onAppReady(ARA::Application& app)
    {
        mWindow = app.createWindow({ 1024, 768 }, { .resizable = true }, "First App With ARA");
        
        mWindow->setObserver(std::dynamic_pointer_cast<ARA::Window::Observer>(shared_from_this()));
        mWindow->setContentElement(shared_from_this());
        
        mWindow->show();
        mWindow->center();
        
        mFont = app.createFont("Courier", 24, ARA::Font::Italic);
        
        ARA::Text::String str("Hello World!", { .font = mFont });
        setString(str);
        
        ARA::ElementStylePtr style = ARA::ElementStyleManager::Shared().newStyle("root");
        style->setBackgroundColor(ARA::Color{ 1, 1, 1, 0.8 });
        
        style = ARA::ElementStyleManager::Shared().newStyle("button", "root");
        style->setCornerRadius(5.0);
        style->setBorder(1.0, ARA::Color{ 0, 0, 0, 1 });
        
        style->apply(*this);
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
    
    virtual void layoutChildren(ARA::View& view) const
    {
        mButtonList->setFrame(frame());
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
