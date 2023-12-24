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

#include "ARA/Db/DbModel.h"
#include "ARA/Db/DbConnectionPlugin.h"

struct Person 
{
    ARA::DbId uid;
    std::string firstname; 
    std::string lastname;
};

class PersonModel : public ARA::DbModel < Person > 
{
public: 

    PersonModel(ARA::DbConnection& connection): 
    DbModel < Person >(connection, "persons")
    {

    }

    std::future < void > 
    create(const Person& person, ARA::DbResultPfn cbk) 
    {
        return connection().open(":memory:", [&](const ARA::DbResult& res)
        {
            if (res.hasError())
                throw ARA::Error("Cannot open database.");
            
            ARA::DbRequest req (ARA::DbRequestType::Create);

            req.add("id", person.uid);
            req.add("firstname", person.firstname);
            req.add("lastname", person.lastname);

            connection().execute(req, [&](const ARA::DbResultList& res)
            {
                if (res.empty())
                    throw ARA::Error("No result.");

                else if (res.at(0).hasError())
                    throw res.at(0).error();

                cbk(res[0]);
            })
            .get();
        });
    }
};

class MyButtonStyle : public ARA::ElementStyle
{
public:
    
    MyButtonStyle(): ARA::ElementStyle("button")
    {
        setBackgroundColor(ARA::Color{ 0.0, 0.0, 1.0, 0.8 });
        setBorder(1.0, ARA::Color{ 0.0, 0.0, 0.0, 0.8 });
        setCornerRadius(5.0);

        ARA::DbConnectionPlugin SQLPlugin ("libARASQL");
        ARA::DbConnectionPtr connection = SQLPlugin.load();

        PersonModel(*connection)
        .create({ .firstname = "Jacques", .lastname = "Tronconi" })
        .get();

        
    }
};

class MyButtonList : public ARA::Element
{
    ARA::Controls::ButtonList mButtons;
    
public:
    
    MyButtonList()
    {
        auto button = ARA::MakePtr < ARA::Controls::Button >(ARA::Text::String("Button 1"));
        
        button->setFrameSize({ 250, 50 });
        button->setPadding({ 10, 10, 10, 10 });
        
        ARA::ElementStyleManager::Shared().add(ARA::MakePtr < MyButtonStyle >());
        {
            auto hover = ARA::ElementStyleManager::Shared().newStyle("button.hover", "button");
            hover->setBackgroundColor(ARA::Color{ 0.0, 0.0, 0.8, 0.5 });
            
            auto focus = ARA::ElementStyleManager::Shared().newStyle("button.focus", "button");
            focus->setBackgroundColor(ARA::Color{ 0.0, 0.5, 0.5, 0.7 });
            
            button->setStyle("button");
            button->setHoverStyle("button.hover");
            button->setFocusStyle("button.focus");
        }
        
        mButtons.push_back(button);
        add(button);
    }
    
protected:
    
    virtual void layoutChildren() const
    {
        mButtons[0]->setFrameOrigin({ 10, 100 });
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
    
    virtual void layoutChildren() const
    {
        mButtonList->setFrame(bounds());
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
