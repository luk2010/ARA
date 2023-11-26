//
//  ARADrawer.h
//  lui
//
//  Created by jacques tronconi on 26/11/2023.
//

#ifndef ARADrawer_h
#define ARADrawer_h

#include "ARAPath.h"
#include "ARAColor.h"

ARA_BEGIN_NAMESPACE

//! @brief
//! A base class for a Drawer.
class Drawer : public ApplicationObject
{
public:
    
    //! @brief
    //! Creates a new drawer.
    inline Drawer(Application& app): ApplicationObject(app) {}
    
    //! @brief
    //! Pushes the current drawer graphics state.
    virtual void push() = 0;
    
    //! @brief
    //! Restores the previous graphics state.
    virtual void pop() = 0;
    
    //! @brief
    //! Sets the current fill color.
    virtual void setFillColor(const Color& color) = 0;
    
    //! @brief
    //! Sets the current stroke color.
    virtual void setStrokeColor(const Color& color) = 0;
    
    //! @brief
    //! Sets the current line width.
    virtual void setLineWidth(Real width) = 0;
    
    //! @brief
    //! Draws a filled path.
    virtual void fillPath(const Ptr<Path>& path) = 0;
    
    //! @brief
    //! Draws a stroked path.
    virtual void strokePath(const Ptr<Path>& path) = 0;
};

ARA_END_NAMESPACE

#endif /* ARADrawer_h */
