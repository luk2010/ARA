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

@implementation OSXNSView

- (instancetype)initWithView:(OSXView *)view
{
    self = [super initWithFrame:NSZeroRect];
    
    if (self)
        self->view = view;
    
    return self;
}

- (void)setView:(OSXView*)view
{
    self->view = view; 
}

- (void)drawRect:(NSRect)dirtyRect
{
    auto observer = self->view->observer();
    
    if (observer)
    {
        NSGraphicsContext* context = [NSGraphicsContext currentContext];
        
        CGContextConcatCTM(context.CGContext, CGAffineTransformMakeScale(1, -1));
        CGContextConcatCTM(context.CGContext, CGAffineTransformMakeTranslation(0, -self.frame.size.height));
        
        OSXDrawer drawer(self->view->application(), [NSGraphicsContext currentContext]);
        observer->onViewDraw(*self->view, drawer);
    }
}

- (BOOL)isFlipped
{
    return NO;
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
    location = [self->view->handle() convertPoint:location fromView:nil];
    
    // We should be careful that Y coordinates are inverted on OSX.
    
    CGFloat height = self->view->frame().size.height;
    location.y = height - location.y;
    
    return location;
}

@end
