////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Hri/RenderViewController.cpp
//! @date
//!     2023/12/29
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ARA/Hri/RenderViewController.h"
#include "ARA/Core/ARAApplication.h"

ARA_HRI_BEGIN_NS

RenderViewController::RenderViewController(RenderAPI renderApi) 
{
    auto& app = ARA::Application::Get();

    if (!app.canCreateRenderView(renderApi))
        throw RenderAPINotSupported("RenderViewController: RenderAPI ", (int)renderApi, " not supported.");
    
    setView(app.createRenderView(renderApi));
}

void RenderViewController::render(RenderView& view)
{
    
}

ARA_HRI_END_NS
