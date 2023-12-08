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

int OSXApplication::run(int argc, char** argv)
{
    [mHandle run];
    return 0;
}

void OSXApplication::terminate()
{
    [mHandle terminate:nil];
}

ARA::Ptr<ARA::Path> OSXApplication::createPath(const ARA::Point2& origin) const
{
    CGMutablePathRef path = CGPathCreateMutable();
    CGPathMoveToPoint(path, NULL, origin.x, origin.y);
    
    return ARA::MakePtr<OSXPath>(*this, path);
}

ARA::Ptr<ARA::Font> OSXApplication::createFont(std::string_view familyName, ARA::Real size, ARA::Font::TraitsMask traits) const
{
    NSFontManager* manager = [NSFontManager sharedFontManager];
    NSFontTraitMask mask = 0;
    
    if (traits & Bold) mask |= NSFontBoldTrait;
    if (traits & Italic) mask |= NSFontItalicTrait;
    if (traits & Condensed) mask |= NSFontCondensedTrait;
    
    NSFont* font = [manager fontWithFamily:[NSString stringWithUTF8String:familyName.data()]
                                    traits:mask
                                    weight:NSFontWeightRegular
                                      size:size];
    
    if (!font)
        return nullptr;
    
    CTFontDescriptorRef descriptor = CTFontDescriptorCreateWithAttributes(@{
        kCTFontNameAttribute: font.fontName,
        kCTFontSizeAttribute: font.pointSize,
        kCTFontTraitsAttribute: [manager traitsOfFont:font]
    });
    
    CTFontRef ffont = CTFontCreateWithFontDescriptor(descriptor, size, NULL);
    
    if (!ffont)
        return nullptr;
    
    return ARA::MakePtr<OSXFont>(*this, ffont);
}
