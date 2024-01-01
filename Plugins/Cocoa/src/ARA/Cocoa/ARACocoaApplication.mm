////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Cocoa/ARACocoaApplication.mm
//! @date
//!     2023/12/08
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ARACocoaApplication.h"
#include "OSXFont.h"
#include "OSXPath.h"
#include "OSXView.h"
#include "OSXNSView.h"
#include "OSXWindow.h"
#include "OSXNSWindow.h"

#if ARA_OSX_WITH_METAL
#include "Metal/RenderView.h"
#endif 

static std::map < uint32_t, ARA::KeyCode > keycodeToARA =
{
    { 0x00, ARA::KeyCode::A },
    { 0x0B, ARA::KeyCode::B },
    { 0x08, ARA::KeyCode::C },
    { 0x02, ARA::KeyCode::D },
    { 0x0E, ARA::KeyCode::E },
    { 0x03, ARA::KeyCode::F },
    { 0x05, ARA::KeyCode::G },
    { 0x04, ARA::KeyCode::H },
    { 0x22, ARA::KeyCode::I },
    { 0x26, ARA::KeyCode::J },
    { 0x28, ARA::KeyCode::K },
    { 0x25, ARA::KeyCode::L },
    { 0x2E, ARA::KeyCode::M },
    { 0x2D, ARA::KeyCode::N },
    { 0x1F, ARA::KeyCode::O },
    { 0x23, ARA::KeyCode::P },
    { 0x0C, ARA::KeyCode::Q },
    { 0x0F, ARA::KeyCode::R },
    { 0x01, ARA::KeyCode::S },
    { 0x11, ARA::KeyCode::T },
    { 0x20, ARA::KeyCode::U },
    { 0x09, ARA::KeyCode::V },
    { 0x0D, ARA::KeyCode::W },
    { 0x07, ARA::KeyCode::X },
    { 0x10, ARA::KeyCode::Y },
    { 0x06, ARA::KeyCode::Z },
    
    { 0x1D, ARA::KeyCode::Zero },
    { 0x12, ARA::KeyCode::One },
    { 0x13, ARA::KeyCode::Two },
    { 0x14, ARA::KeyCode::Three },
    { 0x15, ARA::KeyCode::Four },
    { 0x17, ARA::KeyCode::Five },
    { 0x16, ARA::KeyCode::Six },
    { 0x1A, ARA::KeyCode::Seven },
    { 0x1C, ARA::KeyCode::Eight },
    { 0x19, ARA::KeyCode::Nine },
    
    { 0x30, ARA::KeyCode::Tabulate },
    { 0x39, ARA::KeyCode::CapsLock },
    { 0x38, ARA::KeyCode::Shift },
    { 0x3B, ARA::KeyCode::Control },
    { 0x3A, ARA::KeyCode::Option },
    { 0x37, ARA::KeyCode::Command },
    { 0x33, ARA::KeyCode::Backspace },
    { 0x24, ARA::KeyCode::Return },
    
    { 0x7B, ARA::KeyCode::ArrowLeft },
    { 0x7C, ARA::KeyCode::ArrowRight },
    { 0x7E, ARA::KeyCode::ArrowUp },
    { 0x7D, ARA::KeyCode::ArrowDown },
    
    { 0x7A, ARA::KeyCode::F1 },
    { 0x78, ARA::KeyCode::F2 },
    { 0x63, ARA::KeyCode::F3 },
    { 0x76, ARA::KeyCode::F4 },
    { 0x60, ARA::KeyCode::F5 },
    { 0x61, ARA::KeyCode::F6 },
    { 0x62, ARA::KeyCode::F7 },
    { 0x64, ARA::KeyCode::F8 },
    { 0x65, ARA::KeyCode::F9 },
    { 0x6D, ARA::KeyCode::F10 }
};

static std::map < ARA::KeyCode, uint32_t > araToKeyCode;

@interface OSXAppDelegate : NSObject<NSApplicationDelegate>
{
    OSXApplication* app;
}

- (instancetype) initWithApp:(OSXApplication*)app;

@end

@implementation OSXAppDelegate

- (instancetype)initWithApp:(OSXApplication *)_app
{
    self = [super init];
    
    if (self)
        self->app = _app;
    
    return self;
}

- (void)applicationDidFinishLaunching:(NSNotification *)notification
{
    auto observer = self->app->observer();
    
    if (observer)
        observer->onAppReady(*self->app);
}

- (void)applicationWillTerminate:(NSNotification *)notification
{
    auto observer = self->app->observer();
    
    if (observer)
        observer->onAppTerminate(*self->app);
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender
{
    return TRUE;
}

@end

OSXApplication::OSXApplication()
{
    mHandle = NSApp = [NSApplication sharedApplication];
    mDelegate = [[OSXAppDelegate alloc] initWithApp:this];
    
    mHandle.delegate = mDelegate;
    mHandle.activationPolicy = NSApplicationActivationPolicyRegular;
}

int OSXApplication::run(int argc, const char** argv)
{
    [mHandle run];
    return 0;
}

void OSXApplication::terminate()
{
    [mHandle terminate:nil];
}

ARA::Ptr<ARA::Window> OSXApplication::createWindow(const ARA::Size2& size, const ARA::WindowStyle& style, const std::string& title)
{
    NSWindowStyleMask mask = 0;
    if (style.closable) mask |= NSWindowStyleMaskClosable;
    if (style.fullContentSize) mask |= NSWindowStyleMaskFullSizeContentView;
    if (style.resizable) mask |= NSWindowStyleMaskResizable;
    if (style.titled) mask |= NSWindowStyleMaskTitled;
    
    OSXNSWindow* handle = [[OSXNSWindow alloc] initWithContentRect:NSMakeRect(0, 0, size.width, size.height)
                                                         styleMask:mask
                                                           backing:NSBackingStoreBuffered
                                                             defer:NO];
    
    if (style.fullScreen)
        [handle toggleFullScreen:nil];
    
    if (!title.empty())
        [handle setTitle:[NSString stringWithUTF8String:title.data()]];
    
    auto wnd = ARA::MakePtr<OSXWindow>(*this, handle);
    
    [handle setOSXWindow:wnd.get()];
    
    return wnd;
}

ARA::Ptr<ARA::View> OSXApplication::createView(ARA::ViewController& controller)
{
    return ARA::MakePtr<OSXView>(*this, controller, [[OSXNSView alloc] initWithView:NULL]);
}

ARA::Ptr<ARA::Path> OSXApplication::createPath(const ARA::Point2& origin)
{
    CGMutablePathRef path = CGPathCreateMutable();
    if (origin.x > 0 || origin.y > 0)
        CGPathMoveToPoint(path, NULL, origin.x, origin.y);
    
    return ARA::MakePtr<OSXPath>(*this, path);
}

ARA::Ptr<ARA::Font> OSXApplication::createFont(std::string_view familyName, ARA::Real size, ARA::Font::TraitsMask traits)
{
    NSFontManager* manager = [NSFontManager sharedFontManager];
    NSFontTraitMask mask = 0;
    
    if (traits & ARA::Font::Bold) mask |= NSFontBoldTrait;
    if (traits & ARA::Font::Italic) mask |= NSFontItalicTrait;
    if (traits & ARA::Font::Condensed) mask |= NSFontCondensedTrait;
    
    NSFont* font = [manager fontWithFamily:[NSString stringWithUTF8String:familyName.data()]
                                    traits:mask
                                    weight:NSFontWeightRegular
                                      size:size];
    
    if (!font)
        return nullptr;
    
    return ARA::MakePtr<OSXFont>(*this, font);
}

ARA::KeyCode OSXApplication::convertKeyCode(uint32_t keycode) const
{
    auto it = keycodeToARA.find(keycode);
    
    if (it == keycodeToARA.end())
        return ARA::KeyCode::Unknown;
    
    return it->second;
}

uint32_t OSXApplication::convertKeyCode(ARA::KeyCode keycode) const
{
    if (araToKeyCode.empty())
    {
        for (auto& pair : keycodeToARA)
            araToKeyCode[pair.second] = pair.first;
    }
    
    auto it = araToKeyCode.find(keycode);
    
    if (it == araToKeyCode.end())
        return (uint32_t) -1;
    
    return it->second;
}

ARA::RenderAPI OSXApplication::getPreferredRenderAPI() const
{
    return ARA::RenderAPI::Metal;
}

ARA::RenderAPIList OSXApplication::getAvailableRenderAPIs() const
{
    return {
#       if ARA_OSX_WITH_METAL
        ARA::RenderAPI::Metal,
#       endif
#       if ARA_OSX_WITH_OPENGL
        ARA::RenderAPI::OpenGl,
#       endif
    };
}

ARA::RenderViewPtr OSXApplication::createRenderView(ARA::RenderAPI renderApi, ARA::RenderViewController& controller)
{
    switch (renderApi)
    {
#       if ARA_OSX_WITH_METAL
        case ARA::RenderAPI::Metal:
            return ARA::MakePtr < RenderViewMTL >(*this, controller);
#       endif
        default:
            return nullptr;
    }
}
