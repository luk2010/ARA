////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Cocoa/ARAView.cpp
//! @date
//!     2023/12/08
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ARAView.h"
#include "ARA/Core/ViewController.h"
#include "ARA/Core/ARAError.h"

ARA_BEGIN_NAMESPACE

View::View(Application& application, ViewController& controller):
ApplicationObject(application), 
mController(controller),
mAcceptsMouseMoveEvents(false),
mNeedsLayoutChildren(true)
{
    
}

ViewController& View::controller()
{
    return mController;
}

const ViewController& View::controller() const
{
    return mController;
}

ViewPtr View::addChild(const ViewPtr& child, const ViewPtr& beforeChild)
{
    ThrowIf < Error >(!child, "[View::addChild] Cannot add null child.");
    
    if (!child->controller().willMoveToView(*this))
        return nullptr;
    
    ThrowIf < Error >(!_addChild(child, beforeChild), "[View::addChild] Cannot add new child.");
    
    mChildrenNodes.insert(std::find(mChildrenNodes.begin(), mChildrenNodes.end(), beforeChild), child);
    
    setParentView(*child, shared_from_this());
    
    controller().didAddChild(*child);
    child->controller().didMoveToView();
    
    return child;
}

void View::removeChild(const ViewPtr& child)
{
    ThrowIf < Error >(!child, "[View::addChild] Cannot remove null child.");
    ThrowIf < Error >(!_removeChild(child), "[View::removeChild] Cannot remove child.");
    
    setParentView(*child, nullptr);
    
    mChildrenNodes.erase(std::find(mChildrenNodes.begin(), mChildrenNodes.end(), child));
    
    controller().didRemoveChild(*child);
    child->controller().didMoveFromView();
}

void View::setFrame(const Rect2& rect)
{
    if (rect != frame())
        setNeedsLayoutChildren(true);
}

void View::setBounds(const Rect2& rect)
{
    if (rect != bounds())
        setNeedsLayoutChildren(true);
}

void View::update()
{
    mController.update();
    
    for (auto& child : mChildrenNodes)
        child->update();
}

bool View::acceptsMouseMoveEvents() const
{
    return mAcceptsMouseMoveEvents.load();
}

void View::setAcceptsMouseMoveEvents(bool value)
{
    mAcceptsMouseMoveEvents.store(value);
}

bool View::needsLayoutChildren() const
{
    return mNeedsLayoutChildren.load();
}

void View::setNeedsLayoutChildren(bool value)
{
    mNeedsLayoutChildren.store(value);
}

void View::draw(ARA::Drawer& drawer) const
{
    controller().draw(drawer);
}

ARA_END_NAMESPACE
