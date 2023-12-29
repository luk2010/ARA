////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Cocoa/OSXNSWindow.mm
//! @date
//!     2023/12/24
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "OSXNSWindow.h"
#include "ARA/Core/ARAApplication.h"

@implementation OSXNSWindow

- (void)setOSXWindow:(OSXWindow *)window
{
    _window = window;
}

- (void)keyDown:(NSEvent *)event
{
    ARA::KeyEvent ke(*_window, ARA::EventType::KeyDown,
                     (ARA::Char32)[event.characters characterAtIndex:0],
                     ARA::Application::Get().convertKeyCode(event.keyCode),
                     {});
    
    if (!_window->handleEvent(ke))
        [super keyDown:event];
}

- (void)keyUp:(NSEvent *)event
{
    ARA::KeyEvent ke(*_window, ARA::EventType::KeyUp,
                     (ARA::Char32)[event.characters characterAtIndex:0],
                     ARA::Application::Get().convertKeyCode(event.keyCode),
                     {});
    
    if (!_window->handleEvent(ke))
        [super keyUp:event];
}

@end
