//
//  ARAPath.cpp
//  ARA
//
//  Created by jacques tronconi on 26/11/2023.
//

#include "ARAPath.h"
#include "ARARectCorner.h"

ARA_BEGIN_NAMESPACE

Path& Path::addRoundedRect(const Rect2& rect, Real(&radii)[4])
{
    // Top
    
    Real radiusS = radii[(int)RectCorner::TopLeft];
    Real radiusE = radii[(int)RectCorner::TopRight];
    
    moveTo({ rect.minX() + (radiusS / 2), rect.minY() + (radiusS / 2) });
    addQuad({ rect.minX() + (radiusS / 2), rect.minY() }, { rect.minX() + radiusS, rect.minY() });
    
    lineTo({ rect.maxX() - (radiusE), rect.minY() });
    addQuad({ rect.maxX(), rect.minY() }, { rect.maxX() - (radiusE / 2), rect.minY() + (radiusE / 2) });
    
    // Right
    
    radiusS = radii[(int)RectCorner::TopRight];
    radiusE = radii[(int)RectCorner::BottomRight];
    
    addQuad({ rect.maxX(), rect.minY() + (radiusS / 2) }, { rect.maxX(), rect.minY() + radiusS });
    
    lineTo({ rect.maxX(), rect.maxY() - radiusE });
    addQuad({ rect.maxX(), rect.maxY() - (radiusE / 2) }, { rect.maxX() - (radiusE / 2), rect.maxY() - (radiusE / 2) });
    
    // Bottom
    
    radiusS = radii[(int)RectCorner::BottomRight];
    radiusE = radii[(int)RectCorner::BottomLeft];
    
    addQuad({ rect.maxX(), rect.maxY() }, { rect.maxX() - radiusS, rect.maxY() });
    
    lineTo({ rect.minX() + radiusE, rect.maxY() });
    addQuad({ rect.minX() + (radiusE / 2), rect.maxY() - (radiusE / 2) }, { rect.minX() + (radiusE / 2), rect.maxY() - (radiusE / 2) });
    
    // Left
    
    radiusS = radii[(int)RectCorner::BottomLeft];
    radiusE = radii[(int)RectCorner::TopLeft];
    
    addQuad({ rect.minX(), rect.maxY() - (radiusS / 2) }, { rect.minX(), rect.maxY() - radiusS });
    
    lineTo({ rect.minX(), rect.minY() + radiusE });
    addQuad({ rect.minX(), rect.minY() + (radiusE / 2) }, { rect.minX() + (radiusE / 2), rect.minY() + (radiusE / 2) });
    
    close();
    
    return *this;
}

Path& Path::addRoundedEdge(const Rect2& rect, RectEdge edge, Real (&cornerRadii)[4])
{
    Real radiusS = 0;
    Real radiusE = 0;
    
    switch (edge)
    {
        case RectEdge::Top:
            radiusS = cornerRadii[(int)RectCorner::TopLeft];
            radiusE = cornerRadii[(int)RectCorner::TopRight];
            
            moveTo({ rect.minX() + (radiusS / 2), rect.minY() + (radiusS / 2) });
            addQuad({ rect.minX() + (radiusS / 2), rect.minY() }, { rect.minX() + radiusS, rect.minY() });
            
            lineTo({ rect.maxX() - (radiusE), rect.minY() });
            addQuad({ rect.maxX(), rect.minY() }, { rect.maxX() - (radiusE / 2), rect.minY() + (radiusE / 2) });
            
            break;
            
        case RectEdge::Right:
            radiusS = cornerRadii[(int)RectCorner::TopRight];
            radiusE = cornerRadii[(int)RectCorner::BottomRight];
            
            moveTo({ rect.maxX() - (radiusS / 2), rect.minY() + (radiusS / 2) });
            addQuad({ rect.maxX(), rect.minY() + (radiusS / 2) }, { rect.maxX(), rect.minY() + radiusS });
            
            lineTo({ rect.maxX(), rect.maxY() - radiusE });
            addQuad({ rect.maxX(), rect.maxY() - (radiusE / 2) }, { rect.maxX() - (radiusE / 2), rect.maxY() - (radiusE / 2) });
            
            break;
            
        case RectEdge::Bottom:
            radiusS = cornerRadii[(int)RectCorner::BottomRight];
            radiusE = cornerRadii[(int)RectCorner::BottomLeft];
            
            moveTo({ rect.maxX() - (radiusS / 2), rect.maxY() - (radiusS / 2) });
            addQuad({ rect.maxX(), rect.maxY() }, { rect.maxX() - radiusS, rect.maxY() });
            
            lineTo({ rect.minX() + radiusE, rect.maxY() });
            addQuad({ rect.minX() + (radiusE / 2), rect.maxY() - (radiusE / 2) }, { rect.minX() + (radiusE / 2), rect.maxY() - (radiusE / 2) });
            
            break;
            
        case RectEdge::Left:
            radiusS = cornerRadii[(int)RectCorner::BottomLeft];
            radiusE = cornerRadii[(int)RectCorner::TopLeft];
            
            moveTo({ rect.minX() + (radiusS / 2), rect.maxY() - (radiusS / 2) });
            addQuad({ rect.minX(), rect.maxY() - (radiusS / 2) }, { rect.minX(), rect.maxY() - radiusS });
            
            lineTo({ rect.minX(), rect.minY() + radiusE });
            addQuad({ rect.minX(), rect.minY() + (radiusE / 2) }, { rect.minX() + (radiusE / 2), rect.minY() + (radiusE / 2) });
            
            break;
    }
    
    return *this;
}

ARA_END_NAMESPACE
