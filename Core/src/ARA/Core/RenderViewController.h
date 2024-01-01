////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Core/RenderViewController.h
//! @date
//!     2023/12/29
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_CORE_RENDERVIEWCONTROLLER_H__
#define __ARA_CORE_RENDERVIEWCONTROLLER_H__

#include "ARA/Core/RenderView.h"
#include "ARA/Core/ViewController.h"
#include "ARA/Core/RenderApi.h"
#include "ARA/Core/ARAError.h"

ARA_BEGIN_NAMESPACE

ARA_DECLARE_ERROR(RenderAPINotSupported)

//! @brief 
//! A Controller for a `ARA::RenderView`.
//! 
class RenderViewController : public ARA::ViewController
{
    friend class RenderView;
    
public:

    //! @brief 
    //! Creates a new RenderViewController instance, along with its RenderView. 
    //! 
    //! @param renderApi 
    //!     The RenderAPI that must be used to create the RenderView. 
    //!
    RenderViewController(RenderAPI renderApi);
    
    //! @brief
    //! Called when the RenderView is resized.
    //!
    virtual void drawableResize(const Size2& size);

protected:

    //! @brief 
    //! Renders the RenderView. 
    //! 
    virtual void render(RenderView& view);
};

ARA_END_NAMESPACE

#endif 
