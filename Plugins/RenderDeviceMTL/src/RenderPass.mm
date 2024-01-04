////////////////////////////////////////////////////////////////////////////////////////////////////

//! @file
//!     DeviceMTL/RenderPass.mm
//! @date
//!     2024/01/04
//! @author
//!     Luk2010, Atlanti's Corp
//! @copyright
//!     Atlanti's Corp - 2023 - 2024

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "RenderPass.h"
#include "GPUTextureMTL.h"
#include "Enums.h"
#include "RenderDeviceMTL.h"

ARA::Hri::RenderPass RenderPassFromMTL(ARA::Hri::RenderDevice& dev, MTLRenderPassDescriptor* desc)
{
    ARA::Hri::RenderPass pass;
    
    for (size_t i = 0; i < dev.maxNumberOfColorAttachments(); ++i)
    {
        MTLRenderPassColorAttachmentDescriptor* color =
            [desc.colorAttachments objectAtIndexedSubscript:i];
        
        ARA::Hri::RenderPassColorAttachment attach;
        
        if (color.texture)
        {
            attach.texture = ARA::MakePtr < GPUTextureMTL >(dev, color.texture);
            attach.layer = color.slice;
            attach.level = color.level;
            attach.depthPlane = color.depthPlane;
            attach.load = LoadActionFromMTL(color.loadAction);
            attach.store = StoreActionFromMTL(color.storeAction);
            attach.clearColor = { color.clearColor.red, color.clearColor.green, color.clearColor.blue, color.clearColor.alpha };
        }
        
        pass.colorAttachments.push_back(attach);
    }
    
    if (desc.depthAttachment.texture)
    {
        ARA::Hri::RenderPassDepthAttachment attach;
        
        attach.texture = ARA::MakePtr < GPUTextureMTL >(dev, desc.depthAttachment.texture);
        attach.layer = desc.depthAttachment.slice;
        attach.level = desc.depthAttachment.level;
        attach.depthPlane = desc.depthAttachment.depthPlane;
        attach.load = LoadActionFromMTL(desc.depthAttachment.loadAction);
        attach.store = StoreActionFromMTL(desc.depthAttachment.storeAction);
        attach.clearDepth = desc.depthAttachment.clearDepth;
        
        pass.depthAttachment = attach;
    }
    
    if (desc.stencilAttachment.texture)
    {
        ARA::Hri::RenderPassStencilAttachment attach;
        
        attach.texture = ARA::MakePtr < GPUTextureMTL >(dev, desc.stencilAttachment.texture);
        attach.layer = desc.stencilAttachment.slice;
        attach.level = desc.stencilAttachment.level;
        attach.depthPlane = desc.stencilAttachment.depthPlane;
        attach.load = LoadActionFromMTL(desc.stencilAttachment.loadAction);
        attach.store = StoreActionFromMTL(desc.stencilAttachment.storeAction);
        attach.stencilValue = desc.stencilAttachment.clearStencil;
        
        pass.stencilAttachment = attach;
    }
    
    return pass;
}

MTLRenderPassDescriptor* RenderPassToMTL(const ARA::Hri::RenderPass& pass)
{
    MTLRenderPassDescriptor* desc = [MTLRenderPassDescriptor new];
    
    for (size_t i = 0; i < pass.colorAttachments.size(); ++i)
    {
        const auto& attach = pass.colorAttachments[i];
        
        if (!attach.texture)
            continue;
        
        MTLRenderPassColorAttachmentDescriptor* color =
            [desc.colorAttachments objectAtIndexedSubscript:i];
        
        color.texture = dynamic_cast < GPUTextureMTL& >(*attach.texture).handle();
        color.slice = attach.layer;
        color.level = attach.level;
        color.depthPlane = attach.depthPlane;
        color.loadAction = LoadActionToMTL(attach.load);
        color.storeAction = StoreActionToMTL(attach.store);
        color.clearColor = MTLClearColorMake(attach.clearColor.red,
                                             attach.clearColor.green,
                                             attach.clearColor.blue,
                                             attach.clearColor.alpha);
    }
    
    if (pass.depthAttachment.texture)
    {
        MTLRenderPassDepthAttachmentDescriptor* depth = [MTLRenderPassDepthAttachmentDescriptor new];
        const auto& attach = pass.depthAttachment;
        
        depth.texture = dynamic_cast < GPUTextureMTL& >(*attach.texture).handle();
        depth.slice = attach.layer;
        depth.level = attach.level;
        depth.depthPlane = attach.depthPlane;
        depth.loadAction = LoadActionToMTL(attach.load);
        depth.storeAction = StoreActionToMTL(attach.store);
        depth.clearDepth = attach.clearDepth;
        
        desc.depthAttachment = depth;
    }
    
    if (pass.stencilAttachment.texture)
    {
        MTLRenderPassStencilAttachmentDescriptor* depth = [MTLRenderPassStencilAttachmentDescriptor new];
        const auto& attach = pass.stencilAttachment;
        
        depth.texture = dynamic_cast < GPUTextureMTL& >(*attach.texture).handle();
        depth.slice = attach.layer;
        depth.level = attach.level;
        depth.depthPlane = attach.depthPlane;
        depth.loadAction = LoadActionToMTL(attach.load);
        depth.storeAction = StoreActionToMTL(attach.store);
        depth.clearStencil = attach.stencilValue;
        
        desc.stencilAttachment = depth;
    }
    
    return desc;
}
