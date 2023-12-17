////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Core/ViewController.cpp
//! @date
//!     2023/12/14
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ARA/Core/ViewController.h"
#include "ARA/Core/ARAApplication.h"

ARA_BEGIN_NAMESPACE

ViewController::ViewController()
{
    mView = Application::Get().createView(*this);
    mLocalListener = MakePtr < CustomListener >(*this);
    mView->addListener(mLocalListener);
}

View& ViewController::view()
{
    return *mView;
}

const View& ViewController::view() const
{
    return *mView;
}

Rect2 ViewController::frame() const
{
    return view().frame();
}

void ViewController::setFrame(const Rect2& frame)
{
    view().setFrame(frame);
}

void ViewController::update()
{
    
}

void ViewController::draw(Drawer& drawer) const
{
    
}

bool ViewController::willMoveToWindow(const Window& window)
{
    return true;
}

void ViewController::didMoveToWindow()
{
    
}

bool ViewController::willMoveToView(const View& view)
{
    return true;
}

void ViewController::didMoveToView()
{
    
}

void ViewController::didAddChild(View& child)
{
    
}

void ViewController::didRemoveChild(View& child)
{
    
}

void ViewController::didMoveFromView()
{
    
}

void ViewController::didMoveFromWindow()
{
    
}

ARA_END_NAMESPACE
