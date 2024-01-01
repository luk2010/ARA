////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Cocoa/OSXNSView.mm
//! @date
//!     2023/12/08
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "OSXNSView.h"
#include "OSXDrawer.h"

#include "ARA/Core/ViewController.h"

@implementation OSXNSView

- (instancetype)initWithView:(ARA::View*)view
{
    self = [super initWithFrame:NSZeroRect];
    
    if (self)
    {
        self->view = view;
        self->trackingRect = 0;
    }
    
    return self;
}

- (void)setView:(ARA::View*)view
{
    self->view = view; 
}

- (void)drawRect:(NSRect)dirtyRect
{
    NSGraphicsContext* context = [NSGraphicsContext currentContext];
    OSXDrawer drawer(self->view->application(), [NSGraphicsContext currentContext]);
    
    view->draw(drawer);
}

- (BOOL)isFlipped
{
    return YES;
}

- (void)mouseDown:(NSEvent *)event
{
    NSPoint location = [self translateEventLocation:event.locationInWindow];

    // Now we can send our event.
    
    ARA::MouseDownEvent e(*self->view,
                          ARA::MouseButton::Left,
                          { location.x, location.y },
                          { NSEvent.mouseLocation.x, NSEvent.mouseLocation.y });
    
    self->view->sendEvent(e);
}

- (void)mouseUp:(NSEvent *)event
{
    NSPoint location = [self translateEventLocation:event.locationInWindow];
    
    // Now we can send our event.
    
    ARA::MouseUpEvent e(*self->view,
                        ARA::MouseButton::Left,
                        { location.x, location.y },
                        { NSEvent.mouseLocation.x, NSEvent.mouseLocation.y });
    
    self->view->sendEvent(e);
}

- (NSPoint)translateEventLocation:(NSPoint)location
{
    location = [self convertPoint:location fromView:nil];
    
    // We should be careful that Y coordinates are inverted on OSX.
    
    // CGFloat height = self->view->frame().size.height;
    // location.y = height - location.y;
    
    return location;
}

- (void)viewDidMoveToWindow
{
    trackingRect = [self addTrackingRect:self.bounds
                                   owner:self
                                userData:NULL
                            assumeInside:NO];
}

- (void)mouseEntered:(NSEvent *)event
{
    wasAcceptingMouseEvent = self.window.acceptsMouseMovedEvents;
    
    if (view->acceptsMouseMoveEvents())
    {
        [self.window setAcceptsMouseMovedEvents:YES];
        [self.window makeFirstResponder:self];
    }
    
    NSPoint location = [self translateEventLocation:event.locationInWindow];
    
    ARA::MouseEnterEvent ev(*view,
                            { location.x, location.y },
                            { event.locationInWindow.x, event.locationInWindow.y });
    
    view->sendEvent(ev);
}

- (void)mouseMoved:(NSEvent *)event
{
    if (view->acceptsMouseMoveEvents())
    {
        NSPoint location = [self translateEventLocation:event.locationInWindow];
        
        ARA::MouseMoveEvent ev(*view,
                               { location.x, location.y },
                               { event.locationInWindow.x, event.locationInWindow.y },
                               { event.deltaX, event.deltaY });
        
        view->sendEvent(ev);
    }
}

- (void)mouseExited:(NSEvent *)event
{
    [self.window setAcceptsMouseMovedEvents:wasAcceptingMouseEvent];
    
    NSPoint location = [self translateEventLocation:event.locationInWindow];
    
    ARA::MouseExitEvent ev(*view,
                           { location.x, location.y },
                           { event.locationInWindow.x, event.locationInWindow.y });
    
    view->sendEvent(ev);
}

- (void)setFrame:(NSRect)frame
{
    [super setFrame:frame];
    [self removeTrackingRect:trackingRect];
    
    trackingRect = [self addTrackingRect:self.bounds
                                   owner:self
                                userData:NULL
                            assumeInside:NO];
}

- (void)setBounds:(NSRect)bounds
{
    [super setBounds:bounds];
    [self removeTrackingRect:trackingRect];
    
    trackingRect = [self addTrackingRect:self.bounds
                                   owner:self
                                userData:NULL
                            assumeInside:NO];
}

- (void)viewWillMoveToWindow:(NSWindow *)newWindow
{
    if (self.window && trackingRect)
    {
        [self removeTrackingRect:trackingRect];
        trackingRect = 0;
    }
}

@end
