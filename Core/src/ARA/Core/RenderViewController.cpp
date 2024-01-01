////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Core/RenderViewController.cpp
//! @date
//!     2023/12/29
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ARA/Core/RenderViewController.h"
#include "ARA/Core/ARAApplication.h"

ARA_BEGIN_NAMESPACE

RenderViewController::RenderViewController(RenderAPI renderApi) 
{
    auto& app = ARA::Application::Get();

    if (!app.canCreateRenderView(renderApi))
        throw RenderAPINotSupported("RenderViewController: RenderAPI ", (int)renderApi, " not supported.");
    
    setView(app.createRenderView(renderApi, *this));
}

void RenderViewController::drawableResize(const Size2& size)
{
    
}

void RenderViewController::render(RenderView& view)
{
    
}

ARA_END_NAMESPACE
