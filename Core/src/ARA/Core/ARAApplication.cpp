//
//  ARAApplication.cpp
//  lui
//
//  Created by jacques tronconi on 26/11/2023.
//

#include "ARAApplication.h"

ARA_BEGIN_NAMESPACE

ApplicationPtr Application::mInstance;

Application::Application()
{
    
}

Application::~Application()
{

}

Application& Application::CreateOrGet()
{
    if (!mInstance)
    {
        auto& constructors = ApplicationFactory::Get().constructors();
        auto first = (*constructors.begin()).second;
        mInstance = first();
    }
    
    return *mInstance;
}

Application& Application::Get()
{
    return *mInstance;
}

bool Application::canCreateRenderView(RenderAPI renderApi) const
{
    auto apis = getAvailableRenderAPIs();
    
    for (auto api : apis)
        if (api == renderApi)
            return true;
    
    return false;
}

ARA_END_NAMESPACE
