//
//  ARAElement.cpp
//  ARA
//
//  Created by jacques tronconi on 26/11/2023.
//

#include "ARAElement.h"
#include "ARAApplication.h"

#include "ARA/Core/ARAApplication.h"
#include "ARA/Core/ARAWindow.h"
#include "ARA/Core/ARAElementStyle.h"
#include "ARA/Core/ElementStyleManager.h"

ARA_BEGIN_NAMESPACE

Element::Element()
{
    mBackgroundColor.setValue({ 0, 0, 0, 0 });
    
    mBorders[0].edge = RectEdge::Left;
    mBorders[0].width.setValue(0);
    mBorders[0].color.setValue({ 0, 0, 0, 1 });
    
    mBorders[1].edge = RectEdge::Right;
    mBorders[1].width.setValue(0);
    mBorders[1].color.setValue({ 0, 0, 0, 1 });
    
    mBorders[2].edge = RectEdge::Top;
    mBorders[2].width.setValue(0);
    mBorders[2].color.setValue({ 0, 0, 0, 1 });
    
    mBorders[3].edge = RectEdge::Bottom;
    mBorders[3].width.setValue(0);
    mBorders[3].color.setValue({ 0, 0, 0, 1 });
    
    mCornerRadius[0].setValue(0);
    mCornerRadius[1].setValue(0);
    mCornerRadius[2].setValue(0);
    mCornerRadius[3].setValue(0);
}

Window& Element::window()
{
    auto wnd = mWindow.lock();
    
    if (!wnd)
    {
        auto p = parent();
        
        if (!p)
            throw Error("ARA::Element: No window.");
    
        return p->window();
    }
    
    return *wnd;
}

const Window& Element::window() const
{
    auto wnd = mWindow.lock();
    
    if (!wnd)
    {
        auto p = parent();
        
        if (!p)
            throw Error("ARA::Element: No window.");
        
        return p->window();
    }
    
    return *wnd;
}

Color Element::backgroundColor() const
{
    if (mBackgroundColor.isValue())
        return mBackgroundColor.value();
    
    else if (mBackgroundColor.isInherits())
    {
        auto p = parent();
        
        if (p)
            return p->backgroundColor();
    }
    
    return Color{ 0, 0, 0, 0 };
}

void Element::setBackgroundColor(const Color& color)
{
    if (!mBackgroundColor.isEqualTo(color))
    {
        mBackgroundColor.setValue(color);
        view().setNeedsDraw(true);
    }
}

Rect2 Element::backgroundRect() const
{
    return view().bounds();
}

Ptr<Path> Element::borderPath(RectEdge edge) const
{
    Rect2 bkgRect = backgroundRect();
    Ptr<Path> path = Application::Get().createPath(bkgRect.origin);
    
    Real cornerRadii[4] =
    {
        cornerRadius(RectCorner::TopLeft),
        cornerRadius(RectCorner::TopRight),
        cornerRadius(RectCorner::BottomLeft),
        cornerRadius(RectCorner::BottomRight)
    };
    
    path->addRoundedEdge(bkgRect, edge, cornerRadii);
    
    return path;
}

std::array<Ptr<Path>, 4> Element::borderPathes() const
{
    auto& app = Application::Get();
    Rect2 bkgRect = backgroundRect();
    
    std::array<Ptr<Path>, 4> pathes =
    {
        Application::Get().createPath(),
        Application::Get().createPath(),
        Application::Get().createPath(),
        Application::Get().createPath()
    };
    
    Real cornerRadii[4] =
    {
        cornerRadius(RectCorner::TopLeft),
        cornerRadius(RectCorner::TopRight),
        cornerRadius(RectCorner::BottomLeft),
        cornerRadius(RectCorner::BottomRight)
    };
    
    pathes[0]->addRoundedEdge(bkgRect, RectEdge::Left, cornerRadii);
    pathes[1]->addRoundedEdge(bkgRect, RectEdge::Top, cornerRadii);
    pathes[2]->addRoundedEdge(bkgRect, RectEdge::Right, cornerRadii);
    pathes[3]->addRoundedEdge(bkgRect, RectEdge::Bottom, cornerRadii);
    
    return pathes;
}

Real Element::cornerRadius(RectCorner corner) const
{
    auto& radius = mCornerRadius[(int)corner];
    
    if (radius.isInherits())
    {
        auto p = parent();
        
        if (p)
            return p->cornerRadius(corner);
        
        return 0;
    }
    
    return radius.value();
}

void Element::setCornerRadius(RectCorner corner, Real radius)
{
    if (!mCornerRadius[(int)corner].isEqualTo(radius))
    {
        mCornerRadius[(int)corner].setValue(radius);
        view().setNeedsDraw(true);
    }
}

Real Element::borderWidth(RectEdge edge) const
{
    auto& border = mBorders[(int)edge];
    
    if (border.width.isInherits())
    {
        auto p = parent();
        
        if (p)
            return p->borderWidth(edge);
        
        else
            return 0;
    }
    
    return border.width.value();
}

void Element::setBorderWidth(RectEdge edge, const Inheritable<Real>& value)
{
    auto& border = mBorders[(int)edge];
    
    if (!border.width.isEqualTo(value))
    {
        border.width = value;
        view().setNeedsDraw(true);
    }
}

void Element::setBorderWidth(const Inheritable<Real>& value)
{
    for (auto& border : mBorders)
    {
        if (!border.width.isEqualTo(value))
        {
            border.width = value;
            view().setNeedsDraw(true);
        }
    }
}

Color Element::borderColor(RectEdge edge) const
{
    auto& border = mBorders[(int)edge];
    
    if (border.color.isInherits())
    {
        auto p = parent();
        
        if (p)
            return p->borderColor(edge);
        
        else
            return Color{ 0, 0, 0, 0 };
    }
    
    return border.color.value();
}

void Element::setBorderColor(RectEdge edge, const Inheritable < Color >& color)
{
    auto& border = mBorders[static_cast < size_t >(edge)];
    
    if (!border.color.isEqualTo(color))
    {
        border.color = color;
        view().setNeedsDraw(true);
    }
}

void Element::setBorderColor(const Inheritable < Color >& color)
{
    for (auto& border : mBorders)
    {
        if (!border.color.isEqualTo(color))
        {
            border.color = color;
            view().setNeedsDraw(true);
        }
    }
}

Rect2 Element::frame() const
{
    return view().frame();
}

void Element::setFrame(const Rect2& frame)
{
    view().setFrame(frame);
}

void Element::setFrameSize(const Size2& size)
{
    setFrame({ frame().origin, size });
}

void Element::setFrameOrigin(const Point2& origin)
{
    setFrame({ origin, frame().size });
}

size_t Element::numberOfChildren() const
{
    return view().childCount();
}

ViewList Element::childrenViews() const
{
    return view().children();
}

ElementList Element::children() const
{
    ElementList elements;
    ViewList views = childrenViews();
    
    elements.reserve(views.size());
    
    for (auto& view : views)
        elements.push_back(dynamic_cast < Element& >(view->controller()).shared_from_this());
    
    return elements;
}

ElementPtr Element::parent() const
{
    auto pview = view().parent();
    
    if (!pview)
        return nullptr;
    
    auto element = dynamic_cast < Element* >(&pview->controller());
    
    if (!element)
        return nullptr;
    
    return element->shared_from_this();
}

ElementPtr Element::add(const ElementPtr& element, const ElementPtr& before)
{
    ThrowIf < Error >(!element, "[ARA::Element] Null element.");
    
    if (view().addChild(element->view().shared_from_this(),
                        before ? before->view().shared_from_this() : nullptr) != nullptr)
        return element;
    
    return nullptr;
}

void Element::remove(const ElementPtr& element)
{
    view().removeChild(element->view().shared_from_this());
}

Rect2 Element::bounds() const
{
    return view().bounds();
}

void Element::setNeedsDisplay(bool value)
{
    view().setNeedsDraw(value);
}

bool Element::needsDisplay() const
{
    return view().needsDraw();
}

void Element::setNeedsLayout(bool value)
{
    view().setNeedsLayoutChildren(value);
}

bool Element::needsLayout() const
{
    return view().needsLayoutChildren();
}

void Element::setStyle(const ElementStyle& style)
{
    style.apply(*this);
}

void Element::setStyle(const std::string& name)
{
    auto style = ElementStyleManager::Shared().find(name);
    
    if (!style)
        return;
    
    style->apply(*this);
}

void Element::draw(Drawer& drawer) const
{
    auto& app = Application::Get();
    Rect2 rect = backgroundRect();
    
    Real cornerRadii[4] =
    {
        cornerRadius(RectCorner::TopLeft),
        cornerRadius(RectCorner::TopRight),
        cornerRadius(RectCorner::BottomLeft),
        cornerRadius(RectCorner::BottomRight)
    };
    
    // background
    
    const Color backgroundColor = this->backgroundColor();
    
    if (!backgroundColor.isTransparent())
    {
        Ptr<Path> path = app.createPath();
        path->addRoundedRect(rect, cornerRadii);
        
        drawBackground(view(), drawer, path, backgroundColor);
    }
    
    // borders
    
    for (auto& border : mBorders)
    {
        const Real width = borderWidth(border.edge);
        const Color color = borderColor(border.edge);
        
        if (!width || color.isTransparent())
            continue;
        
        Ptr<Path> borderPath = app.createPath();
        borderPath->addRoundedEdge(rect, border.edge, cornerRadii);
        
        drawBorderEdge(view(), drawer, borderPath, border.edge, width, color);
    }
}

void Element::update()
{
    if (view().needsLayoutChildren())
    {
        layoutChildren();
        view().setNeedsLayoutChildren(false);
    }
}

void Element::drawBackground(const View& view, Drawer& drawer,
                             const Ptr<Path>& rect,
                             const Color& color) const
{
    drawer.push();
    
    drawer.setFillColor(color);
    drawer.fillPath(rect);
    
    drawer.pop();
}

void Element::drawBorderEdge(const View &view, Drawer &drawer, const Ptr<Path> &path, RectEdge edge, Real lineWidth, const Color &color) const
{
    drawer.push();
    
    drawer.setStrokeColor(color);
    drawer.setLineWidth(lineWidth);
    drawer.strokePath(path);
    
    drawer.pop();
}

void Element::layoutChildren() const
{
    
}

bool Element::willMoveToWindow(const Window& window)
{
    mWindow = const_cast < Window& >(window).weak_from_this();
    return true;
}

bool Element::willBecomeInputElement()
{
    return false;
}

void Element::didBecomeInputElement()
{
    
}

bool Element::willResignInputElement()
{
    return true;
}

void Element::didResignInputElement()
{
    
}

ARA_END_NAMESPACE
