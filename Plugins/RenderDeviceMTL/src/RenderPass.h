////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     DeviceMTL/RenderPass.h
//! @date
//!     2024/01/04
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __DEVICEMTL_RENDERPASS_H__
#define __DEVICEMTL_RENDERPASS_H__

#include "ARA/Hri/RenderPass.h"
#include "Platform.h"

//! @brief
//! Converts a MTLRenderPassDescriptor to a ARA::Hri::RenderPass.
//!
ARA::Hri::RenderPass RenderPassFromMTL(ARA::Hri::RenderDevice& dev, MTLRenderPassDescriptor* desc);

//! @brief
//! Converts to a MTLRenderPassDescriptor from a ARA::Hri::RenderPass.
//!
MTLRenderPassDescriptor* RenderPassToMTL(const ARA::Hri::RenderPass& pass);

#endif
