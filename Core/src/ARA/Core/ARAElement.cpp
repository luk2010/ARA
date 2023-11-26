//
//  ARAElement.cpp
//  ARA
//
//  Created by jacques tronconi on 26/11/2023.
//

#include "ARAElement.h"
#include "ARAApplication.h"

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

Ptr<View> Element::createView(Application& app)
{
    auto view = Controller<Element>::createView(app);
    
    if (view)
        view->setObserver(shared_from_this());
    
    return view;
}

void Element::onViewDraw(View& view, Drawer& drawer) const
{
    Rect2 rect = backgroundRect(view);
    
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
        Ptr<Path> path = view.application().createPath();
        path->addRoundedRect(rect, cornerRadii);
        
        drawBackground(view, drawer, path, backgroundColor);
    }
    
    // borders
    
    for (auto& border : mBorders)
    {
        const Real width = borderWidth(border.edge);
        const Color color = borderColor(border.edge);
        
        if (!width || color.isTransparent())
            continue;
        
        Ptr<Path> borderPath = view.application().createPath();
        borderPath->addRoundedEdge(rect, border.edge, cornerRadii);
        
        drawBorderEdge(view, drawer, borderPath, border.edge, width, color);
    }
}

Color Element::backgroundColor() const
{
    if (mBackgroundColor.isValue())
        return mBackgroundColor.value();
    
    else if (mBackgroundColor.isInherits())
    {
        auto p = mParentNode.lock();
        
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
        view()->setNeedsDraw(true);
    }
}

Rect2 Element::backgroundRect(const View& view) const
{
    return view.bounds();
}

Ptr<Path> Element::borderPath(const View& view, RectEdge edge) const
{
    Rect2 bkgRect = backgroundRect(view);
    Ptr<Path> path = view.application().createPath(bkgRect.origin);
    
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

std::array<Ptr<Path>, 4> Element::borderPathes(const View& view) const
{
    Rect2 bkgRect = backgroundRect(view);
    
    std::array<Ptr<Path>, 4> pathes =
    {
        view.application().createPath(),
        view.application().createPath(),
        view.application().createPath(),
        view.application().createPath()
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
        auto p = mParentNode.lock();
        
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
        
        auto selfView = this->view();
        
        if (!selfView)
            throw ElementError("[ARA::Element] No view for element.");
        
        selfView->setNeedsDraw(true);
    }
}

Real Element::borderWidth(RectEdge edge) const
{
    auto& border = mBorders[(int)edge];
    
    if (border.width.isInherits())
    {
        auto p = mParentNode.lock();
        
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
        view()->setNeedsDraw(true);
    }
}

void Element::setBorderWidth(const Inheritable<Real>& value)
{
    for (auto& border : mBorders)
    {
        if (!border.width.isEqualTo(value))
        {
            border.width = value;
            view()->setNeedsDraw(true);
        }
    }
}

Color Element::borderColor(RectEdge edge) const
{
    auto& border = mBorders[(int)edge];
    
    if (border.color.isInherits())
    {
        auto p = mParentNode.lock();
        
        if (p)
            return p->borderColor(edge);
        
        else
            return Color{ 0, 0, 0, 0 };
    }
    
    return border.color.value();
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

ARA_END_NAMESPACE
