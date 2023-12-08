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

@interface OSXAppDelegate : NSObject<NSApplicationDelegate>
{
    OSXApplication* app;
}

- (instancetype) initWithApp:(OSXApplication*)app;

@end

@implementation OSXAppDelegate

- (instancetype)initWithApp:(OSXApplication *)app
{
    self = [super init];
    
    if (self)
        self->app = app;
    
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
    
    NSWindow* handle = [[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, size.width, size.height)
                                                   styleMask:mask
                                                     backing:NSBackingStoreBuffered
                                                       defer:NO];
    
    if (style.fullScreen)
        [handle toggleFullScreen:nil];
    
    if (!title.empty())
        [handle setTitle:[NSString stringWithUTF8String:title.data()]];
    
    return ARA::MakePtr<OSXWindow>(*this, handle);
}

ARA::Ptr<ARA::View> OSXApplication::createView()
{
    return ARA::MakePtr<OSXView>(*this, [[OSXNSView alloc] initWithView:NULL]);
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
