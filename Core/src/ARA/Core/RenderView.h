////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Core/RenderView.h
//! @date
//!     2023/12/29
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_CORE_RENDERVIEW_H__
#define __ARA_CORE_RENDERVIEW_H__

#include "ARA/Core/ARAView.h"
#include "ARA/Core/PixelFormat.h"

ARA_BEGIN_NAMESPACE

class RenderViewController;

//! @brief 
//! A `ARA::View` used as a rendering context. 
//! 
class RenderView : public ARA::View 
{
    //! @brief
    //! The controller for this RenderView.
    //!
    RenderViewController& mController;
    
public:
    
    //! @brief
    //! Creates a new RenderView instance.
    //!
    RenderView(Application& app, RenderViewController& controller);
    
    //! @brief
    //! Calls the controller render function.
    //!
    virtual void render();

    //! @brief 
    //! Returns the PixelFormat used with this RenderView.
    //! 
    virtual PixelFormat pixelFormat() const = 0;
};

typedef Ptr < RenderView > RenderViewPtr;

ARA_END_NAMESPACE

#endif 
