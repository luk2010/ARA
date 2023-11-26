//
//  ARAPath.h
//  ARA
//
//  Created by jacques tronconi on 26/11/2023.
//

#ifndef ARAPath_h
#define ARAPath_h

#include "ARAApplicationObject.h"
#include "ARARect2.h"
#include "ARARectEdge.h"

ARA_BEGIN_NAMESPACE

//! @brief
//! A native Path implementation.
class Path : public ApplicationObject
{
public:
    
    //! @brief
    //! Creates a new Path.
    inline Path(Application& app): ApplicationObject(app) { }
    
    //! @brief
    //! Virtual destructor.
    virtual ~Path() = default;
    
    //! @brief
    //! Returns the current cursor point.
    virtual Point2 cursor() const = 0;
    
    //! @brief
    //! Moves the current cursor to a given point.
    virtual Path& moveTo(const Point2& point) = 0;
    
    //! @brief
    //! Adds a line to the given point.
    virtual Path& lineTo(const Point2& point) = 0;
    
    //! @brief
    //! Adds a bezier curve from one control point.
    virtual Path& addQuad(const Point2& control, const Point2& to) = 0;
    
    //! @brief
    //! Adds a Bezier curve from two control points.
    virtual Path& addCubic(const Point2& control1, const Point2& control2, const Point2& to) = 0;
    
    //! @brief
    //! Closes the Path by returning to the last moveTo point.
    virtual Path& close() = 0;
    
    //! @brief
    //! Adds a rounded rectangle.
    virtual Path& addRoundedRect(const Rect2& rect, Real(&radii)[4]);
    
    //! @brief
    //! Adds a given border of a rectangle, given corner radii.
    virtual Path& addRoundedEdge(const Rect2& rect, RectEdge edge, Real(&cornerRadii)[4]);
};

ARA_END_NAMESPACE

#endif /* ARAPath_h */
