////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     ARA/Core/RenderView.cpp
//! @date
//!     2023/12/30
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ARA/Core/RenderView.h"
#include "ARA/Core/RenderViewController.h"

ARA_BEGIN_NAMESPACE

RenderView::RenderView(Application& app, RenderViewController& controller):
ARA::View(app, controller), mController(controller)
{
    
}

void RenderView::render()
{
    mController.render(*this);
}

ARA_END_NAMESPACE
