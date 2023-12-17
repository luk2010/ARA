////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Cocoa/OSXWindow.mm
//! @date
//!     2023/12/08
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "OSXWindow.h"
#include "OSXView.h"

@interface OSXWindowDel : NSObject < NSWindowDelegate >
{
    OSXWindow* window;
}

- (instancetype)initWithWin:(OSXWindow*)window;

@end

@implementation OSXWindowDel

- (instancetype)initWithWin:(OSXWindow *)window
{
    self = [super init];
    self->window = window;
    return self;
}

- (void)windowDidMove:(NSNotification *)notification
{
    auto observer = self->window->observer();
    NSPoint location = ((NSWindow*)(notification.object)).frame.origin;
    
    if (observer)
        observer->onWindowMove(*self->window, { location.x, location.y });
}

- (void)windowDidResize:(NSNotification *)notification
{
    auto observer = self->window->observer();
    NSSize size = ((NSWindow*)(notification.object)).frame.size;
    NSSize ssize = ((NSWindow*)(notification.object)).contentLayoutRect.size;
    
    if (observer)
        observer->onWindowResize(*self->window, { size.width, size.height });
    
    auto content = window->contentElement();
    
    if (content)
        content->setFrame({{}, { ssize.width, ssize.height }});
}

- (void)windowWillClose:(NSNotification *)notification
{
    auto observer = self->window->observer();
    
    if (observer)
        observer->onWindowClose(*self->window);
}

- (void)windowDidUpdate:(NSNotification *)notification
{
    auto content = window->contentElement();
    
    if (!content)
        return;
    
    content->view().update();
}

@end

OSXWindow::OSXWindow(ARA::Application& app, NSWindow* handle):
ARA::Window(app), mHandle(handle)
{
    mDelegate = [[OSXWindowDel alloc] initWithWin:this];
    mHandle.delegate = mDelegate;
    mHandle.releasedWhenClosed = NO;
}

NSWindow* OSXWindow::handle() const
{
    return mHandle;
}

ARA::Rect2 OSXWindow::frame() const
{
    NSRect rect = mHandle.frame;
    return {{ rect.origin.x, rect.origin.y }, { rect.size.width, rect.size.height }};
}

void OSXWindow::setFrame(const ARA::Rect2& frame)
{
    [mHandle setFrame:NSMakeRect(frame.origin.x, frame.origin.y, frame.size.width, frame.size.height)
              display:TRUE
              animate:TRUE];
}

ARA::Rect2 OSXWindow::contentFrame() const
{
    NSRect rect = mHandle.contentLayoutRect;
    return {{ rect.origin.x, rect.origin.y }, { rect.size.width, rect.size.height }};
}

ARA::WindowStyle OSXWindow::style() const
{
    NSWindowStyleMask mask = mHandle.styleMask;
    ARA::WindowStyle style = { false };
    
    if (mask & NSWindowStyleMaskClosable) style.closable = true;
    if (mask & NSWindowStyleMaskResizable) style.resizable = true;
    if (mask & NSWindowStyleMaskTitled) style.titled = true;
    if (mask & NSWindowStyleMaskFullSizeContentView) style.fullContentSize = true;
    if (mask & NSWindowStyleMaskFullScreen) style.fullScreen = true;
    
    return style;
}

void OSXWindow::setStyle(const ARA::WindowStyle& style)
{
    NSWindowStyleMask mask = 0;
    
    if (style.closable) mask |= NSWindowStyleMaskClosable;
    if (style.fullContentSize) mask |= NSWindowStyleMaskFullSizeContentView;
    if (style.resizable) mask |= NSWindowStyleMaskResizable;
    if (style.titled) mask |= NSWindowStyleMaskTitled;
    
    [mHandle setStyleMask:mask];
    
    if (style.fullScreen != (mHandle.styleMask & NSWindowStyleMaskFullScreen))
        [mHandle toggleFullScreen:nil];
}

std::string OSXWindow::title() const
{
    return mHandle.title.UTF8String;
}

void OSXWindow::setTitle(std::string_view title)
{
    mHandle.title = [NSString stringWithUTF8String:title.data()];
}

void OSXWindow::show()
{
    [mHandle makeKeyAndOrderFront:nil];
}

void OSXWindow::center()
{
    [mHandle center];
}

void OSXWindow::close()
{
    [mHandle performClose:nil];
}

void OSXWindow::_setContentView(ARA::View& view)
{
    NSView* handle = dynamic_cast < OSXView& >(view).handle();
    ARA::ThrowIf < OSXError >(!handle, "[OSXWindow::_setContentView] Given view has no NSView handle.");
    
    mHandle.contentView = handle;
    view.setFrame(contentFrame());
}
