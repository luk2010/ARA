////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Hri/RenderViewController.h
//! @date
//!     2023/12/29
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ARA_HRI_RENDERVIEWCONTROLLER_H__
#define __ARA_HRI_RENDERVIEWCONTROLLER_H__

#include "ARA/Hri/Platform.h"
#include "ARA/Hri/RenderView.h"
#include "ARA/Core/ViewController.h"
#include "ARA/Core/RenderApi.h"

ARA_HRI_BEGIN_NS

//! @brief 
//! A Controller for a `ARA::Hri::RenderView`.
//! 
class RenderViewController : public ARA::ViewController
{
public: 

    //! @brief 
    //! Creates a new RenderViewController instance, along with its RenderView. 
    //! 
    //! @param renderApi 
    //!     The RenderAPI that must be used to create the RenderView. 
    //!
    RenderViewController(RenderAPI renderApi);

protected:

    //! @brief 
    //! Renders the RenderView. 
    //! 
    virtual void render(RenderView& view);
};

ARA_HRI_END_NS

#endif 
