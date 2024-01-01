////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Cocoa/Metal/AAViewMTL.mm
//! @date
//!     2023/12/29
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "AAViewMTL.h"

#include "ARA/Core/RenderView.h"
#include "ARA/Core/RenderViewController.h"

@implementation AAViewMTL
{
    ARA::RenderView* _renderView;
    
    CVDisplayLinkRef _displayLink;
}

@synthesize metalLayer;
@synthesize paused;

- (instancetype)initWithView:(ARA::View*)view
{
    self = [super initWithView:view];
    
    if (self)
    {
        _renderView = dynamic_cast < ARA::RenderView* >(view);
        
        self.wantsLayer = YES;
        self.layerContentsRedrawPolicy = NSViewLayerContentsRedrawDuringViewResize;
        
        metalLayer = (CAMetalLayer*) self.layer;
        self.layer.delegate = self;
    }
    
    return self;
}

- (CALayer*)makeBackingLayer
{
    return [CAMetalLayer layer];
}

- (void)viewDidMoveToWindow
{
    [super viewDidMoveToWindow];
    [self setupCVDisplayLinkForScreen:self.window.screen];
    [self resizeDrawable:self.window.screen.backingScaleFactor];
}

- (BOOL)setupCVDisplayLinkForScreen:(NSScreen*)screen
{
    CVReturn cvReturn;
    
    cvReturn = CVDisplayLinkCreateWithActiveCGDisplays(&_displayLink);
    
    if (cvReturn != kCVReturnSuccess)
        return NO;
    
    cvReturn = CVDisplayLinkSetOutputCallback(_displayLink, &DispatchRenderLoop, (__bridge void*)self);
    
    if (cvReturn != kCVReturnSuccess)
        return NO;
    
    CGDirectDisplayID displayID =
        (CGDirectDisplayID)
            [self.window.screen.deviceDescription[@"NSScreenNumber"] unsignedIntegerValue];
    
    cvReturn = CVDisplayLinkSetCurrentCGDisplay(_displayLink, displayID);
    
    if (cvReturn != kCVReturnSuccess)
        return NO;
    
    CVDisplayLinkStart(_displayLink);
    
    [NSNotificationCenter.defaultCenter addObserver:self
                                           selector:@selector(windowWillClose:)
                                               name:NSWindowWillCloseNotification
                                             object:self.window];
    
    return YES;
}

- (void)resizeDrawable:(CGFloat)scaleFactor
{
    CGSize newSize = self.bounds.size;
    newSize.width *= scaleFactor;
    newSize.height *= scaleFactor;
    
    if(newSize.width <= 0 || newSize.width <= 0)
    {
        return;
    }
  
    // All AppKit and UIKit calls which notify of a resize are called on the main thread.  Use
    // a synchronized block to ensure that resize notifications on the delegate are atomic
    @synchronized(metalLayer)
    {
        if(newSize.width == metalLayer.drawableSize.width &&
           newSize.height == metalLayer.drawableSize.height)
        {
            return;
        }
        
        metalLayer.drawableSize = newSize;
        
        ARA::RenderViewController& controller = 
            dynamic_cast < ARA::RenderViewController& >(_renderView->controller());
        controller.drawableResize({ newSize.width, newSize.height });
    }
}

- (void)render
{
    _renderView->render();
}

- (void)windowWillClose:(NSNotification*)notification
{
    if (notification.object == self.window)
        CVDisplayLinkStop(_displayLink);
}

- (void)stopRenderLoop
{
    if (_displayLink)
    {
        CVDisplayLinkStop(_displayLink);
        CVDisplayLinkRelease(_displayLink);
        _displayLink = NULL;
    }
}

- (void)viewDidChangeBackingProperties
{
    [super viewDidChangeBackingProperties];
    [self resizeDrawable:self.window.screen.backingScaleFactor];
}

- (void)setFrame:(NSRect)frame
{
    [super setFrame:frame];
    [self resizeDrawable:self.window.screen.backingScaleFactor];
}

- (void)setBounds:(NSRect)bounds
{
    [super setBounds:bounds];
    [self resizeDrawable:self.window.screen.backingScaleFactor];
}

// This is the renderer output callback function
static CVReturn DispatchRenderLoop(CVDisplayLinkRef displayLink,
                                   const CVTimeStamp* now,
                                   const CVTimeStamp* outputTime,
                                   CVOptionFlags flagsIn,
                                   CVOptionFlags* flagsOut,
                                   void* displayLinkContext)
{
    @autoreleasepool
    {
        AAViewMTL* customView = (__bridge AAViewMTL*)displayLinkContext;
        [customView render];
    }
    
    return kCVReturnSuccess;
}

@end
